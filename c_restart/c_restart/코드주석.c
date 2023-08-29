# �ʾ��ڷ�

### 4.1.1.Vision�� �̿��� ������λ���(���γ� �ﰢ��) : ���ϸ鼭 �ڵ忡 �ּ� �� �޾� ������..�� ������!![����ȣ] �̸���

input : modelStatesSub(���� ����(��ġ)), lidarSub(lidar Subscribers),

modelStatesSub : robotIndex(������ġ)

% ROS master�� ����
clc;
clear;

rosshutdown;
rosinit('[http://localhost:11311](http://localhost:11311/)') % ���� ROS Master�� IP �ּҿ� ��Ʈ�� �Է�
%%

% Subscribers ����
lidarSub = rossubscriber('/lidar/points', "DataFormat", "struct");
modelStatesSub = rossubscriber('/gazebo/model_states');

horizontalResolution = 512;
roi = [1.2, 7, -10, 10, -3, 5];% [xmin, xmax, ymin, ymax, zmin, zmax] % roi����

figure;

modelStatesMsg = receive(modelStatesSub);
robotIndex = find(strcmp([modelStatesMsg.Name](http://modelstatesmsg.name/), 'hunter2_base')); % 

params = lidarParameters('OS1Gen1-64', horizontalResolution);%

% �� ��ġ ã��
coneIndices = contains([modelStatesMsg.Name](http://modelstatesmsg.name/), 'Construction_Cone');
conePoses = modelStatesMsg.Pose(coneIndices);

while true
tic;

% LIDAR ������ ����
lidarData = receive(lidarSub);
modelStatesMsg = receive(modelStatesSub);

% LIDAR �����͸� PointCloud�� ��ȯ
xyzData = rosReadXYZ(lidarData);
ptCloud = pointCloud(xyzData);
ptCloudOrg = pcorganize(ptCloud, params);% params�� �츮 ���� ��� �պ��� �ɵ�

% ���� ���� ����
groundPtsIdx = segmentGroundFromLidarData(ptCloudOrg);
groundPtCloud = select(ptCloudOrg, groundPtsIdx);
nonGroundPtCloud = select(ptCloudOrg, ~groundPtsIdx, 'OutputSize', 'full');

indices = findPointsInROI(nonGroundPtCloud, roi);
roiPtCloud = select(nonGroundPtCloud, indices);


roiPtCloud = pcdenoise(roiPtCloud, PreserveStructure = true);
[labels, numClusters] = pcsegdist(roiPtCloud, 0.3);

% ptCloud�� x, y ��ǥ ����
xData = roiPtCloud.Location(:, 1);
yData = roiPtCloud.Location(:, 2);

% ���� ��ġ ����
robotPose = modelStatesMsg.Pose(robotIndex);% robotindex�� ��ġ���� ������
robotPosition = [robotPose.Position.X, robotPose.Position.Y];% ���⼭ xy��ǥ�� ��ȯ

clf;
hold on;
innerConePosition = [];
outerConePosition = [];

for i = 1:numClusters % ������ roiPtCloud���� ���� ���� �Ѱ���
idx = labels == i;% get indices for current cluster
clusterPoints = [xData(idx), yData(idx), roiPtCloud.Location(idx, 3)];% get points of current cluster

% only consider clusters with more than 20 points
if size(clusterPoints, 1) >= 20
% find the point with the maximum z value
[~, maxZIdx] = max(clusterPoints(:, 3));


% center is the point with the maximum z value
center = clusterPoints(maxZIdx, 1:2);% cluster�� z �ִ밪�� center�� ����

scatter(center(1), -center(2), "red", "filled");% draw a dot for current cluster center

if center(2) < 0 % �̰� �¿� �����ε�(+�� �� = outer)
    innerConePosition = [innerConePosition; center(1), center(2)];
else
outerConePosition = [outerConePosition; center(1), center(2)];
end

end
end

### �� �Լ����� modelStatesSub���� ���� ��ġ�� lidarSub(���̴�)���� �� ������ �޾Ƽ� Ŭ�����͸� �� ��ǥ�� ǥ���Ͽ� inner(��), outer(��) ���� �ϴ� �� ����.

[~, uniqueIdx_out] = unique(outerConePosition, 'rows');
outerConePosition = outerConePosition(uniqueIdx_out, :);
[~, uniqueIdx_in] = unique(innerConePosition, 'rows');
innerConePosition = innerConePosition(uniqueIdx_in, :);

outerConePosition = sortrows(outerConePosition);
innerConePosition = sortrows(innerConePosition);

innerLength = size(innerConePosition, 1);
outerLength = size(outerConePosition, 1);

% ���̰� �� ���� ������ �� �迭�� �ڸ���
if innerLength > outerLength
innerConePosition = innerConePosition(1:outerLength, : );
elseif outerLength > innerLength
outerConePosition = outerConePosition(1:innerLength, : );
end

xlim([roi(1) roi(2)]);
ylim([-roi(4) - roi(3)]);
daspect([(roi(2) - roi(1)), abs(roi(4) - roi(3)), 1]);% adjust the aspect ratio
view([90 - 90]);% rotate view by 90 degrees counterclockwise

% ���� ��ǥ ����
[m, nc] = size(innerConePosition);% size of the inner / outer cone positions data
kockle_coords = zeros(2 * m, nc);% initiate a P matrix consisting of inner and outer coordinates
kockle_coords(1:2 : 2 * m, : ) = innerConePosition;
kockle_coords(2:2 : 2 * m, : ) = outerConePosition;% merge the inner and outer coordinates with alternate values
xp = [];% create an empty numeric xp vector to store the planned x coordinates after each iteration
yp = [];
% ���� : inner ����, �� outer

% ----------------------������� ������ǥ�� ���� ��γ׻ﰢ���� ����------------------------------------
interv = 4;
% step 1 : delaunay triangulation
tri = delaunayTriangulation(kockle_coords);
pl = tri.Points;% ��ǥ
cl = tri.ConnectivityList;% ��ǥ������ ����
[mc, nc] = size(pl);

% inner and outer constraints when the interval is even
if rem(interv, 2) == 0;% �̰� �� �̷��� �ϴ��� �𸣰������� �׻� if�� ���� ����
cIn = [2 1; (1:2 : mc - 3)' (3:2:(mc))'; (mc - 1) mc];
cOut = [(2:2 : (mc - 2))' (4:2:mc)'];
else
% inner and outer constraints when the interval is odd
cIn = [2 1; (1:2 : mc - 2)' (3:2:(mc))'; (mc - 1) mc];
cOut = [(2:2 : (mc - 2))' (4:2:mc)'];
end

% step 2 : �ܺ� �ﰢ�� ��
C = [cIn; cOut];
TR = delaunayTriangulation(pl, C);
TRC = TR.ConnectivityList;
TL = isInterior(TR);
TC = TR.ConnectivityList(TL, :);
[~, pt] = sort(sum(TC, 2));
TS = TC(pt, :);
TO = triangulation(TS, pl);

% step 3 : �߰� waypoint ����
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

% step 4 : waypoint ����
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

% step 5 : ���� waypoint ����
waypoints = [xp', yp'] % ���� �ϴ� ��Ÿ���� �ѵ�

% waypoint �� �����Ǵ��� Ȯ��
plot(waypoints(:, 1), waypoints(:, 2), 'yo', 'MarkerSize', 3)
ylim([-1 1])
hold off;

toc;

end

### ��������� ��γ� �ﰢ�� ���� waypoint �����

go_triangulation �� ���� ����� ����.

function waypoints = generate_waypoints(innerConePosition, outerConePosition)

% go_traingulation

[m, nc] = size(innerConePosition);% size of the inner / outer cone positions data
kockle_coords = zeros(2 * m, nc);% initiate a P matrix consisting of inner and outer coordinates
kockle_coords(1:2 : 2 * m, : ) = innerConePosition;% �׻� Ȧ���� inner
kockle_coords(2:2 : 2 * m, : ) = outerConePosition;
xp = [];
yp = [];

midpoints = zeros(size(kockle_coords, 1) - 1, size(kockle_coords, 2));

for i = 1:size(kockle_coords, 1) - 1 % �߾� �κ� point
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

### way point����� ���(�߾Ӻκ��� point�� ����)

### 4.2.1.pure pursuit�� �̿��� ���� ��� ����

Waypoints ����

> �ùķ����� �󿡼� hunter�� ����������� �����ϰ� �ð�ȭ�ϱ� ����, �켱 PathPlanning �˰����� �������� ���� ���·� ������ waypoint�� �����ϰ�, PurePursuit �˰������� �̸� �����ϵ��� �Ͽ���.
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

hVel = annotation('textbox', [0.65, 0.15, 0.27, 0.1], 'String', 'X: 0m Y: 0m\nv: 0.00 m/s ��: 0.0 rad/s');% Initialize a text box
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
velString = sprintf('X: %dm Y: %dm\\nv: %.2f m/s ��: %.1f rad/s', round(robotPose.Position.X), round(robotPose.Position.Y), linearVel, angularVel);
set(hVel, 'String', velString);

% Update the path
pathX = [pathX; robotPose.Position.X];% �κ� x������ �����Ͽ� ���� �����
pathY = [pathY; robotPose.Position.Y];% �κ� y������ �����Ͽ� ���� �����.
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

### ��������� modelStatesMsg�� robotIndex���� ������ ���� ��ġ ��ǥ�� ���� PATH X�� PATH Y�� �����Ͽ� ���� ����� ��.

���� ��ǥ�� ���� waypoints �������

> controllerPurePursuit ��ü�� ������ waypoints ��ǥ�� �߰��Ͽ� ���� �޽����� �����Ѵ�.
>

load('waypoints.mat');% waypoint ���� �ޱ�
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

���� ��ǥ�� ���� waypoints �������

> waypoints ��ǥ�� ȸ������� �̿��� ���� ��ǥ�� �������� ��ȯ�ϰ�, controllerPurePursuit ��ü�� �߰��Ͽ� ���� �޽����� �����Ѵ�.
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

% ���� ��ǥ�迡�� waypoint ��ġ ���
wayPosition = [waypoints(i, 1), waypoints(i, 2)];
wayPositionInRobotFrame = wayPosition - robotPosition;

% Convert orientation(quaternion) to yaw angle
quat = [robotPose.Orientation.W, robotPose.Orientation.X, robotPose.Orientation.Y, robotPose.Orientation.Z];
euler = quat2eul(quat);
yaw = euler(1);

% ȸ�� ��� ���
R = [cos(yaw) - sin(yaw); sin(yaw) cos(yaw)];

% ���� ��ǥ�迡���� waypoint ��ġ ���
wayPositionInRobotFrameRotated = (R' * wayPositionInRobotFrame')';

% ���� ��ǥ�迡�� waypoint ��ġ ����
truewayX = [truewayX; wayPositionInRobotFrameRotated(1)];
truewayY = [truewayY; wayPositionInRobotFrameRotated(2)];
end
pp.Waypoints = [truewayX, truewayY];

% Pure Pursuit �˰������� ���Ⱒ ���
[v, w] = pp([0 0 0]);

msg.Linear.X = v;
msg.Angular.Z = w;

% 'cmd_vel' ���ȿ� �޽��� ����
send(pub, msg);
plot(robotPose.Position.X, robotPose.Position.Y, '.', Color = "r");
pause(0.1)

end

<aside>
?? ���� �ǽ����� PathPlanning �˰����� ������� PurePursuit ������ ���� ������ ���̹Ƿ�, ���� ���� �ڵ忡 �߰����� ��λ��� �˰��� ������ �ʿ��ϴ�.

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

% truewayX, truewayY�� ������ǥ�� ���� ���
pp.Waypoints = [truewayX, truewayY];

[v, w] = pp([0 0 0]);

msg.Linear.X = v;
msg.Angular.Z = w;

send(pub, msg);
plot(robotPose.Position.X, robotPose.Position.Y, '.', Color = "r");
pause(0.1)

end