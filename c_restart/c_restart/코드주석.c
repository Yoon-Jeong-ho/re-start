# 초안자료

### 4.1.1.Vision을 이용한 추종경로생성(돌로네 삼각형) : 일하면서 코드에 주석 다 달아 놓을게..→ 누구야!![윤정호] 이름좀

input : modelStatesSub(차량 정보(위치)), lidarSub(lidar Subscribers),

modelStatesSub : robotIndex(차량위치)

% ROS master와 연결
clc;
clear;

rosshutdown;
rosinit('[http://localhost:11311](http://localhost:11311/)') % 실제 ROS Master의 IP 주소와 포트를 입력
%%

% Subscribers 생성
lidarSub = rossubscriber('/lidar/points', "DataFormat", "struct");
modelStatesSub = rossubscriber('/gazebo/model_states');

horizontalResolution = 512;
roi = [1.2, 7, -10, 10, -3, 5];% [xmin, xmax, ymin, ymax, zmin, zmax] % roi설정

figure;

modelStatesMsg = receive(modelStatesSub);
robotIndex = find(strcmp([modelStatesMsg.Name](http://modelstatesmsg.name/), 'hunter2_base')); % 

params = lidarParameters('OS1Gen1-64', horizontalResolution);%

% 콘 위치 찾기
coneIndices = contains([modelStatesMsg.Name](http://modelstatesmsg.name/), 'Construction_Cone');
conePoses = modelStatesMsg.Pose(coneIndices);

while true
tic;

% LIDAR 데이터 수신
lidarData = receive(lidarSub);
modelStatesMsg = receive(modelStatesSub);

% LIDAR 데이터를 PointCloud로 변환
xyzData = rosReadXYZ(lidarData);
ptCloud = pointCloud(xyzData);
ptCloudOrg = pcorganize(ptCloud, params);% params만 우리 마음 대로 손봐도 될듯

% 지면 분할 수행
groundPtsIdx = segmentGroundFromLidarData(ptCloudOrg);
groundPtCloud = select(ptCloudOrg, groundPtsIdx);
nonGroundPtCloud = select(ptCloudOrg, ~groundPtsIdx, 'OutputSize', 'full');

indices = findPointsInROI(nonGroundPtCloud, roi);
roiPtCloud = select(nonGroundPtCloud, indices);


roiPtCloud = pcdenoise(roiPtCloud, PreserveStructure = true);
[labels, numClusters] = pcsegdist(roiPtCloud, 0.3);

% ptCloud의 x, y 좌표 추출
xData = roiPtCloud.Location(:, 1);
yData = roiPtCloud.Location(:, 2);

% 차량 위치 추출
robotPose = modelStatesMsg.Pose(robotIndex);% robotindex로 위치정보 받으면
robotPosition = [robotPose.Position.X, robotPose.Position.Y];% 여기서 xy좌표로 변환

clf;
hold on;
innerConePosition = [];
outerConePosition = [];

for i = 1:numClusters % 이전에 roiPtCloud에서 개수 정보 넘겨줌
idx = labels == i;% get indices for current cluster
clusterPoints = [xData(idx), yData(idx), roiPtCloud.Location(idx, 3)];% get points of current cluster

% only consider clusters with more than 20 points
if size(clusterPoints, 1) >= 20
% find the point with the maximum z value
[~, maxZIdx] = max(clusterPoints(:, 3));


% center is the point with the maximum z value
center = clusterPoints(maxZIdx, 1:2);% cluster중 z 최대값만 center에 저장

scatter(center(1), -center(2), "red", "filled");% draw a dot for current cluster center

if center(2) < 0 % 이게 좌우 구분인듯(+는 좌 = outer)
    innerConePosition = [innerConePosition; center(1), center(2)];
else
outerConePosition = [outerConePosition; center(1), center(2)];
end

end
end

### 위 함수에서 modelStatesSub에서 차량 위치와 lidarSub(라이다)에서 콘 정보를 받아서 클러스터링 후 좌표에 표현하여 inner(우), outer(좌) 구분 하는 것 까지.

[~, uniqueIdx_out] = unique(outerConePosition, 'rows');
outerConePosition = outerConePosition(uniqueIdx_out, :);
[~, uniqueIdx_in] = unique(innerConePosition, 'rows');
innerConePosition = innerConePosition(uniqueIdx_in, :);

outerConePosition = sortrows(outerConePosition);
innerConePosition = sortrows(innerConePosition);

innerLength = size(innerConePosition, 1);
outerLength = size(outerConePosition, 1);

% 길이가 더 작은 값으로 두 배열을 자르기
if innerLength > outerLength
innerConePosition = innerConePosition(1:outerLength, : );
elseif outerLength > innerLength
outerConePosition = outerConePosition(1:innerLength, : );
end

xlim([roi(1) roi(2)]);
ylim([-roi(4) - roi(3)]);
daspect([(roi(2) - roi(1)), abs(roi(4) - roi(3)), 1]);% adjust the aspect ratio
view([90 - 90]);% rotate view by 90 degrees counterclockwise

% 꼬깔 좌표 생성
[m, nc] = size(innerConePosition);% size of the inner / outer cone positions data
kockle_coords = zeros(2 * m, nc);% initiate a P matrix consisting of inner and outer coordinates
kockle_coords(1:2 : 2 * m, : ) = innerConePosition;
kockle_coords(2:2 : 2 * m, : ) = outerConePosition;% merge the inner and outer coordinates with alternate values
xp = [];% create an empty numeric xp vector to store the planned x coordinates after each iteration
yp = [];
% 구조 : inner 먼저, 후 outer

% ----------------------여기부터 꼬깔좌표를 가고 들로네삼각측량 시작------------------------------------
interv = 4;
% step 1 : delaunay triangulation
tri = delaunayTriangulation(kockle_coords);
pl = tri.Points;% 좌표
cl = tri.ConnectivityList;% 좌표끼리의 연결
[mc, nc] = size(pl);

% inner and outer constraints when the interval is even
if rem(interv, 2) == 0;% 이건 왜 이렇게 하는지 모르겠지만… 항상 if로 갈듯 싶음
cIn = [2 1; (1:2 : mc - 3)' (3:2:(mc))'; (mc - 1) mc];
cOut = [(2:2 : (mc - 2))' (4:2:mc)'];
else
% inner and outer constraints when the interval is odd
cIn = [2 1; (1:2 : mc - 2)' (3:2:(mc))'; (mc - 1) mc];
cOut = [(2:2 : (mc - 2))' (4:2:mc)'];
end

% step 2 : 외부 삼각형 거
C = [cIn; cOut];
TR = delaunayTriangulation(pl, C);
TRC = TR.ConnectivityList;
TL = isInterior(TR);
TC = TR.ConnectivityList(TL, :);
[~, pt] = sort(sum(TC, 2));
TS = TC(pt, :);
TO = triangulation(TS, pl);

% step 3 : 중간 waypoint 생성
xPo = TO.Points(:, 1);
yPo = TO.Points(:, 2);
E = edges(TO);
iseven = rem(E, 2) == 0;
Eeven = E(any(iseven, 2), :);
isodd = rem(Eeven, 2)~= 0;
Eodd = Eeven(any(isodd, 2), :);
xmp = ((xPo((Eodd(:, 1))) + xPo((Eodd(:, 2)))) / 2);
ymp = ((yPo((Eodd(:, 1))) + yPo((Eodd(:, 2)))) / 2);
Pmp = [xmp ymp];

% step 4 : waypoint 보간
distancematrix = squareform(pdist(Pmp));
distancesteps = zeros(length(Pmp) - 1, 1);
for j = 2:length(Pmp);
distancesteps(j - 1, 1) = distancematrix(j, j - 1);
end
totalDistance = sum(distancesteps);% total distance travelled
distbp = cumsum([0; distancesteps]);% distance for each waypoint
gradbp = linspace(0, totalDistance, 100);
xq = interp1(distbp, xmp, gradbp, 'spline');% interpolate x coordinates
yq = interp1(distbp, ymp, gradbp, 'spline');% interpolate y coordinates
xp = [xp xq] % store obtained x midpoints after each iteration
yp = [yp yq] % store obtained y midpoints after each iteration

% step 5 : 최종 waypoint 생성
waypoints = [xp', yp'] % 여기 일단 오타같긴 한디

% waypoint 잘 생성되는지 확인
plot(waypoints(:, 1), waypoints(:, 2), 'yo', 'MarkerSize', 3)
ylim([-1 1])
hold off;

toc;

end

### 여기까지가 들로네 삼각형 만들어서 waypoint 만들기

go_triangulation 은 다음 방법과 같다.

function waypoints = generate_waypoints(innerConePosition, outerConePosition)

% go_traingulation

[m, nc] = size(innerConePosition);% size of the inner / outer cone positions data
kockle_coords = zeros(2 * m, nc);% initiate a P matrix consisting of inner and outer coordinates
kockle_coords(1:2 : 2 * m, : ) = innerConePosition;% 항상 홀수가 inner
kockle_coords(2:2 : 2 * m, : ) = outerConePosition;
xp = [];
yp = [];

midpoints = zeros(size(kockle_coords, 1) - 1, size(kockle_coords, 2));

for i = 1:size(kockle_coords, 1) - 1 % 중앙 부분 point
midpoints(i, 1) = (kockle_coords(i, 1) + kockle_coords(i + 1, 1)) / 2;
midpoints(i, 2) = (kockle_coords(i, 2) + kockle_coords(i + 1, 2)) / 2;
end

distancematrix = squareform(pdist(midpoints));
distancesteps = zeros(length(midpoints) - 1, 1);
for j = 2:length(midpoints)
distancesteps(j - 1, 1) = distancematrix(j, j - 1);
end
totalDistance = sum(distancesteps);% total distance travelled
distbp = cumsum([0; distancesteps]);% distance for each waypoint
gradbp = linspace(0, totalDistance, 100);
xq = interp1(distbp, midpoints(:, 1), gradbp, 'spline');% interpolate x coordinates
yq = interp1(distbp, midpoints(:, 2), gradbp, 'spline');% interpolate y coordinates
xp = [xp xq];% store obtained x midpoints after each iteration
yp = [yp yq];% store obtained y midpoints after each iteration

waypoints = [xp', yp'];

end

### way point만드는 방식(중앙부분을 point찍어서 간다)

### 4.2.1.pure pursuit을 이용한 최적 경로 추종

Waypoints 추출

> 시뮬레이터 상에서 hunter의 경로추종성을 구현하고 시각화하기 위해, 우선 PathPlanning 알고리즘을 적용하지 않은 상태로 임의의 waypoint를 생성하고, PurePursuit 알고리즘으로 이를 추종하도록 하였다.
>

%%
rosshutdown;
rosinit('[http://localhost:11311](http://localhost:11311/)');

%%
modelStatesSub = rossubscriber('/gazebo/model_states');

pause(1);

figure;
set(gcf, 'WindowStyle', 'normal');% Make the figure window appear outside MATLAB workspace
hold on;

hVel = annotation('textbox', [0.65, 0.15, 0.27, 0.1], 'String', 'X: 0m Y: 0m\nv: 0.00 m/s ω: 0.0 rad/s');% Initialize a text box
hPath = plot(0, 0, 'b', 'LineWidth', 2);% Initialize a plot for path

pathX = [];% Initialize X coordinates of the path
pathY = [];% Initialize Y coordinates of the path

carWidth = 0.98;% Hunter2 width in meters
carLength = 0.745;% Hunter2 length in meters

carX = [0, carWidth, carWidth, 0, 0] - carWidth / 2;% X coordinates of the car
carY = [0, 0, carLength, carLength, 0] - carLength / 2;% Y coordinates of the car

% Create a patch for the car
hCar = patch(carX, carY, [1 0.6471 0]);

% Initialize points for construction cones
hCones = [];

xlabel('X (m)');
ylabel('Y (m)');

while true

modelStatesMsg = receive(modelStatesSub);

robotIndex = find(strcmp(modelStatesMsg.Name, 'hunter2_base'));
if isempty(robotIndex)
disp('Robot model not found.');
else
% Extract robot pose
robotPose = modelStatesMsg.Pose(robotIndex);

% Convert orientation(quaternion) to yaw angle
quat = [robotPose.Orientation.W, robotPose.Orientation.X, robotPose.Orientation.Y, robotPose.Orientation.Z];
euler = quat2eul(quat);
yaw = euler(1);

% Extract robot velocity
robotVel = modelStatesMsg.Twist(robotIndex);
linearVel = robotVel.Linear.X;
angularVel = robotVel.Angular.Z;

% Update the velocities and position in the text box
velString = sprintf('X: %dm Y: %dm\\nv: %.2f m/s ω: %.1f rad/s', round(robotPose.Position.X), round(robotPose.Position.Y), linearVel, angularVel);
set(hVel, 'String', velString);

% Update the path
pathX = [pathX; robotPose.Position.X];% 로봇 x정보를 저장하여 길을 남긴다
pathY = [pathY; robotPose.Position.Y];% 로봇 y정보를 저장하여 길을 남긴다.
set(hPath, 'XData', pathX, 'YData', pathY);

% Draw the car
rotMat = [cos(yaw), -sin(yaw); sin(yaw), cos(yaw)]; % 2D rotation matrix
carCoords = rotMat * [carX; carY];% Rotate the car coordinates according to the yaw angle
carXNew = carCoords(1, :) + robotPose.Position.X;% Translate the car coordinates
carYNew = carCoords(2, :) + robotPose.Position.Y;
set(hCar, 'XData', carXNew, 'YData', carYNew);% Update the car position using the patch

% Update graph limits to center the car
xlim([robotPose.Position.X - 7.5, robotPose.Position.X + 7.5]);
ylim([robotPose.Position.Y - 7.5, robotPose.Position.Y + 7.5]);

drawnow;
end

pause(0.1);

end

%% Waypoints
waypoints = [];

for i = 1:length(pathX)
waypoints = [waypoints; pathX(i), pathY(i)];
end

save('waypoints.mat', 'waypoints')

### 여기까지가 modelStatesMsg의 robotIndex에서 나오는 차량 위치 좌표를 통해 PATH X와 PATH Y를 저장하여 길을 만드는 것.

월드 좌표계 기준 waypoints 경로추종

> controllerPurePursuit 객체에 생성된 waypoints 좌표를 추가하여 제어 메시지를 발행한다.
>

load('waypoints.mat');% waypoint 정보 받기
modelStatesSub = rossubscriber('/gazebo/model_states');

pub = rospublisher('/ackermann_steering_controller/cmd_vel', 'geometry_msgs/Twist');
msg = rosmessage(pub);

pp = controllerPurePursuit;
pp.LookaheadDistance = 1.0;
pp.DesiredLinearVelocity = 1.0;
pp.Waypoints = waypoints;

figure;
plot(waypoints(:, 1), waypoints(:, 2), '.', Color = "b");
hold on;

while true

modelStatesMsg = receive(modelStatesSub);
robotIndex = find(strcmp(modelStatesMsg.Name, 'hunter2_base'));
robotPose = modelStatesMsg.Pose(robotIndex);

% Convert orientation(quaternion) to yaw angle
quat = [robotPose.Orientation.W, robotPose.Orientation.X, robotPose.Orientation.Y, robotPose.Orientation.Z];
euler = quat2eul(quat);
yaw = euler(1);

[v, w] = pp([robotPose.Position.X robotPose.Position.Y yaw]);

msg.Linear.X = v;
msg.Angular.Z = w;

send(pub, msg);
plot(robotPose.Position.X, robotPose.Position.Y, '.', Color = "r");
pause(0.1)

end

차량 좌표계 기준 waypoints 경로추종

> waypoints 좌표를 회전행렬을 이용해 차량 좌표계 기준으로 변환하고, controllerPurePursuit 객체에 추가하여 제어 메시지를 발행한다.
>

load('waypoints.mat');
modelStatesSub = rossubscriber('/gazebo/model_states');
modelStatesMsg = receive(modelStatesSub);
robotIndex = find(strcmp([modelStatesMsg.Name](http://modelstatesmsg.name/), 'hunter2_base'));

pub = rospublisher('/ackermann_steering_controller/cmd_vel', 'geometry_msgs/Twist');
msg = rosmessage(pub);

pp = controllerPurePursuit;
pp.LookaheadDistance = 1.0;
pp.DesiredLinearVelocity = 2.0;

figure;
plot(waypoints(:, 1), waypoints(:, 2), '.', Color = "b");
hold on;

while true
modelStatesMsg = receive(modelStatesSub);
robotPose = modelStatesMsg.Pose(robotIndex);
robotPosition = [robotPose.Position.X, robotPose.Position.Y];

truewayX = [];
truewayY = [];

for i = 1:length(waypoints)

% 차량 좌표계에서 waypoint 위치 계산
wayPosition = [waypoints(i, 1), waypoints(i, 2)];
wayPositionInRobotFrame = wayPosition - robotPosition;

% Convert orientation(quaternion) to yaw angle
quat = [robotPose.Orientation.W, robotPose.Orientation.X, robotPose.Orientation.Y, robotPose.Orientation.Z];
euler = quat2eul(quat);
yaw = euler(1);

% 회전 행렬 계산
R = [cos(yaw) - sin(yaw); sin(yaw) cos(yaw)];

% 차량 좌표계에서의 waypoint 위치 계산
wayPositionInRobotFrameRotated = (R' * wayPositionInRobotFrame')';

% 차량 좌표계에서 waypoint 위치 저장
truewayX = [truewayX; wayPositionInRobotFrameRotated(1)];
truewayY = [truewayY; wayPositionInRobotFrameRotated(2)];
end
pp.Waypoints = [truewayX, truewayY];

% Pure Pursuit 알고리즘으로 조향각 계산
[v, w] = pp([0 0 0]);

msg.Linear.X = v;
msg.Angular.Z = w;

% 'cmd_vel' 토픽에 메시지 발행
send(pub, msg);
plot(robotPose.Position.X, robotPose.Position.Y, '.', Color = "r");
pause(0.1)

end

<aside>
?? 위의 실습들은 PathPlanning 알고리즘의 적용없이 PurePursuit 구현만 먼저 진행한 것이므로, 추후 다음 코드에 추가적인 경로생성 알고리즘 구현이 필요하다.

< / aside>

pub = rospublisher('/ackermann_steering_controller/cmd_vel', 'geometry_msgs/Twist');
msg = rosmessage(pub);

pp = controllerPurePursuit;
pp.LookaheadDistance = 1.0;
pp.DesiredLinearVelocity = 1.0;

figure;
plot(waypoints(:, 1), waypoints(:, 2), '.', Color = "b");
hold on;

while true

% truewayX, truewayY는 차량좌표계 기준 경로
pp.Waypoints = [truewayX, truewayY];

[v, w] = pp([0 0 0]);

msg.Linear.X = v;
msg.Angular.Z = w;

send(pub, msg);
plot(robotPose.Position.X, robotPose.Position.Y, '.', Color = "r");
pause(0.1)

end