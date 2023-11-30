import cv2
import numpy as np

# 이동 로봇 클래스 정의
class Robot:
    def __init__(self, position):
        self.position = position
        self.speed = 0.0
        self.direction = 0.0

# Pure Pursuit 알고리즘 클래스 정의
class PurePursuit:
    def __init__(self, lookahead_distance):
        self.lookahead_distance = lookahead_distance
    
    def find_goal(self, robot, path):
        # 현재 위치에서 가장 가까운 경로 상의 지점을 찾습니다.
        closest_distance = float('inf')
        closest_point = None
        for point in path:
            distance = np.linalg.norm(point - robot.position)
            if distance < closest_distance:
                closest_distance = distance
                closest_point = point
        
        # 현재 위치에서 lookahead_distance 만큼 떨어진 경로 상의 지점을 찾습니다.
        lookahead_point = None
        for point in path:
            if np.linalg.norm(point - closest_point) > self.lookahead_distance:
                lookahead_point = point
                break
        
        # lookahead_point가 없는 경우, path의 마지막 지점을 사용합니다.
        if lookahead_point is None:
            lookahead_point = path[-1]
        
        return lookahead_point
    
    def control(self, robot, goal):
        # 로봇과 lookahead_point 사이의 거리와 각도를 계산합니다.
        distance = np.linalg.norm(goal - robot.position)
        angle = np.arctan2(goal[1] - robot.position[1], goal[0] - robot.position[0]) - robot.direction
        
        # 각도 차이가 180도를 넘는 경우, 반대 방향으로 회전합니다.
        if angle > np.pi:
            angle -= 2 * np.pi
        elif angle < -np.pi:
            angle += 2 * np.pi
        
        # 로봇의 속도와 회전 속도를 제어합니다.
        robot.speed = 0.5 * distance
        robot.direction += 0.5 * angle

# 경로 생성
path = np.array([[0, 0], [2, 2], [4, 2], [6, 4], [8, 4], [10, 2], [12, 2]])

# 로봇 생성
robot = Robot(np.array([0, 0]))

# Pure Pursuit 알고리즘 생성
pure_pursuit = PurePursuit(2.0)

# 비디오 캡처 객체 생성
cap = cv2.VideoCapture(0)

while True:
    # 카메라에서 프레임을 읽어옵니다.
    ret, frame = cap.read()
    if not ret:
        break
    
    # 프레임을 HSV 색 공간으로 변환합니다.
    hsv = cv2.cvtColor(frame, cv2.COLOR_BGR2HSV)
    # 라바콘을 추출합니다.
    lower_red = np.array([0, 70, 50])
    upper_red = np.array([10, 255, 255])
    mask = cv2.inRange(hsv, lower_red, upper_red)
    # 모폴로지 연산을 수행합니다.
    kernel = np.ones((5, 5), np.uint8)
    mask = cv2.morphologyEx(mask, cv2.MORPH_OPEN, kernel)
    # 라바콘의 외곽선을 추출합니다.
    contours, _ = cv2.findContours(mask, cv2.RETR_EXTERNAL, cv2.CHAIN_APPROX_SIMPLE)

    # 라바콘을 찾은 경우, 로봇 위치를 업데이트합니다.
    if contours:
        # 가장 큰 외곽선을 선택합니다.
        contour = max(contours, key=cv2.contourArea)

        # 외곽선의 중심점을 계산합니다.
        M = cv2.moments(contour)
        center = (int(M['m10']/M['m00']), int(M['m01']/M['m00']))
        
        # 로봇 위치를 업데이트합니다.
        robot.position = np.array(center)

    # Pure Pursuit 알고리즘을 사용하여 로봇을 제어합니다.
    goal = pure_pursuit.find_goal(robot, path)
    pure_pursuit.control(robot, goal)

    # 로봇의 위치와 방향을 이용하여 이미지에 로봇을 그립니다.
    cv2.circle(frame, tuple(robot.position), 5, (255, 0, 0), -1)
    x2 = int(robot.position[0] + 30 * np.cos(robot.direction))
    y2 = int(robot.position[1] + 30 * np.sin(robot.direction))
    cv2.line(frame, tuple(robot.position), (x2, y2), (0, 255, 0), 2)

    # 경로를 이미지에 그립니다.
    for i in range(len(path) - 1):
        cv2.line(frame, tuple(path[i]), tuple(path[i+1]), (0, 0, 255), 2)

    # 이미지를 출력합니다.
    cv2.imshow('frame', frame)

    # 'q' 키를 누르면 종료합니다.
    if cv2.waitKey(1) & 0xFF == ord('q'):
        break
cap.release()
cv2.destroyAllWindows()