import math

x=int(input()) # 아직은 실험용이니까 x좌표와 speed 값 넣어서 어찌 나올지 보기
speed = int(input())

carLength = 2.5 # 우리 차 길이(바퀴사이)
carWidth = 1.5 # 우리 차 너비

#카메라 위치 상 실제 위치 및 각도 찾기 각도는 전부 라디안
cemeraHight = 1.5 # 카메라 높이 m단위
cemeraAngle = math.radians(30) # 카메라 기울은 각도 
cemeraLeftAngle = math.radians(20) # 카메라 좌측 시야 각도 
cemeraTopAngle = math.radians(15) # 카메라 위측 시야 각도
xframe = 1800 # 프레임 총 x좌표수
#yframe = 600 # 프레임 총y좌표 수
#x = 1500 # 목표로 하는 x좌표
#y = 200 # 목표로 하는 y좌표
#yPointDistance = 10 # 아직 이건 못 구하겠네 근데 y좌표는 어차피 거리라서 lookAHeadDistance로 비율 따지면 크게 필요 없을듯? 나중에 레이더 오면 값 집어 넣어도 될듯
distanceAngle = math.atan(2*abs(xframe/2-x)*math.tan(cemeraLeftAngle)/xframe) # x 좌표를 통해 자동차와 목표 사이의 각도 측정

#speed = 00  # 현재 속도 m/s 입력 받아야됨

lookAHeadDistance = speed * 1.0 # 나중에 실험적으로 배수 정하기 목표지점(프레임당 계속 전진, 데이터 많이 먹으면 조절)
if (distanceAngle<math.radians(5) or speed < 20): # 각도도 고민 필요
    acceleration = 10 - distanceAngle # 각도가 작아지면 가속 앞의 값과 배수도 고민 필요
    print('abc')
    
else :
    acceleration = -distanceAngle # 이것도 배수가 필요하겠지만 일단 각도가 커지면 감속도 커짐

wheelAngle = math.atan(carLength*2*math.sin(distanceAngle)/lookAHeadDistance) # 조향각도 
print('distanceAngle',math.degrees(distanceAngle),'lookAHeadDistance ',lookAHeadDistance ,'acceleration',acceleration)
