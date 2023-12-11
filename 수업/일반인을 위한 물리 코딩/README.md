# 1주차
## 백터의 내적
x1*x2 + y1*y2  
스칼라
## 백터의 외적
크기는 a와 b백터가 이루는 평행사변형의 넓이  
> x = (x1,x2,x3), y = (y1,y2,y3)  
x 외적 y = (x2y3 -x3y2, x3y1 - x1y3, x1y2 - x2y1)  
# 2주차
## 뉴턴의 운동법칙
- 제1법칙: 관성의 법칙
- 제2법칙: 가속도의 법칙
- 제3법칙: 작용 반작용의 법칙
## 공의 위치 변화
ball.pos = ball.pos + ball.v*dt  
t = t + dt  
### rate(1/dt)
while루프를 초당 몇번 실행하는지 보여준다.  
인간의 눈은 초당 30번이상 변화하면 연속된 것으로 인식한다.  
ex - rate(100) = 100분의 1 초마다 실행  
# 3주차
## 가속도의 법칙
$\vec{F} = m\vec{a}$
- 물체의 힘에 비례하여 가속도 발생
- 질량이 무거우면 가속도 적게 발생
- 힘의 방향과 가속도의 방향은 같다.
## 가속도
일정 시간 동안 물체의 속도가 변한 정도
- 속도와 위치의 관계 = 가속도와 속도의 관계
### 오일러-크로머 방법
시간에 지남에 따라 속도가 일정하지 않음  
여러가지 방법이 있는데 바뀐 이후의 속도를 사용하는 오일러-크로머 방식을 사용할 수 있다.
- 시간에 따라 힘이 변할 경우 오차가 커지지 않는다.
- 물리 현상에 있어서 에너지를 잘 보존한다.
### 움직임 표현
ball.v = ball.v + ball.a *dt  
ball.pos = ball.pos + ball.v*dt  
t = t + dt  
# 4주차
## 만유인력

$\vec{F}_{grav} = -G\frac{m_1m_2} {|\vec{r}|^2}\hat{r}$  

만유인력 상수 $G = 6.67 * 10^{-11} Nm^2/kg^2$

### 만유인력을 통한 달의 힘 표시
Moon.f = G* Earth.mass *Moon.mass/mag(r)^ 2 * norm(r)  
Earth.f = Moon.f  
Moon.v = Moon.v + Moon.f/Moon.mass * dt  
Earth.v = Earth.v + Earth.f/Earth.mass *dt  
Moon.pos = Moon.pos + Moon.v * dt  
Earth.pos = Earth.pos + Earth.v * dt  
t = t+ dt
# 5주차
## 탈출속도
중력을 이기고 탈출할 정도의 속력

# 6주차
## 축구공이 받는 힘

$\vec{F_g} = -m_{ball}g\hat{r}$

### 공기저항력
$\vec{F}_d = -0.5*C_d\rho Av^2\hat{v} $
- $\hat{v}$ 속도와 반대 방향
- $C_d$ 저항계수, 물체의 형태, 표면의 거칠기의 영향
- $\rho$ 공기의 밀도
- A 축구공의 단면적
- $v^2$ 속력이 빨라지면 급격히 공기 저항력이 증가
## 코드로 표현
ball.v = ball.speed * vec(cos(ball.angle),sin(ball.angle),0) #초기 속도   


grav = ball.m * vec(0,g,0)  
drag = 0.5 * rho * Cd * (pi * ball.radius **2) * mag(ball.v) ** 2 * norm(ball.v)  
ball.f = grav + drag  
ball.v = ball.v + ball.f / ball.m * dt   
ball.pos = ball.pos + ball.v * dt  
### 바람이 불면?
wind_speed = 5  
wind_v = wind_speed*vec(1,0,0)   
ball.v_w = ball.v - wind_v  
dag_wind = -0.5 * rho * Cd * (pi * ball.radius ** 2) * mag(ball.v_w) ** 2 * norm(ball.v_w)  

# 8주차
## 마그누스 효과
$\vec{F_m} = 0.5C_m \rho AR \omega (\hat{\omega} * \hat{v})$
- $\omega $ 공의 회전을 나타내는 속도의 크기  (1초당 1회전 = 2 $\pi$)
- $(\hat{\omega} * \hat{v})$ 외적   
### 코드로 짜기
g = - 9.8  
rho = 1.204  
Cd = 0.3  
Cm = 1  
w = 10 * 2 * pi  
magnus = 0.5 * rho * Cm * (pi * ball.radius ** 2) * ball.radius * w * mag(ball.v) * cross(vec(0,1,0), norm(ball.v))  
ball.f = grav + drag + magnus  

# 9주차
## 용수철
용수철의 변형한 정도에 따라 힘의 크기와 방향이 계속 변한다.
### 훅의 법칙 = 용수철 힘
$$F_{spr}=-K_s(l-l_0)$$
용수철이 변형된 거리에 비례하여 반대 방향에 힘이 작용한다.  
$k_s$ 용수철 상수: 용수철의 뻣뻣한 정도이다.  
#### 3차원 힘의 크기
$$|\vec{F}_{spr}| = k_s(|\vec{l}| - l_0)$$
#### 힘의 방향
$$\hat{F}_{spr} = -\hat{l}$$
#### 다 붙이면
$$\vec{F}_{spr} = - k_s(|\vec{l}| - l_0)\hat{l}$$

### 코드로 짜기
spring = helix(pos = ceiling.pos, axis = ball.pos - ceiling.pos, color = color.black, thickness = .003, coils = 30, radius = 0.01)  
g = 9.8  
ball.m = 1.0  
l0 = 0.3  
ks = 100  
Fgrav = ball.m * g * vector(0,-1,0)  
while True:
    rate(1/dt)  
    l = mag(ball.pos - ceiling.pos)  
    s = l - l0  
    lhat = norm(ball.pos)  
    Fspr = -ks * s * lhat  
    Fnet = Fspr + Fgrav  
    ball.v = ball.v + Fnet / ball.m * dt  
    ball.pos = ball.pos + ball.v * dt  
    spring.axis = ball.pos - ceiling.pos  
    t = t + dt  

### 용수철 감쇠 힘 
$\vec{F}_{damp} = - K_d(\vec{v_l} \hat{l}) \hat{l}$
- $K_d$ 감쇠계수: 크면 용수철의 진동은 빠르게 멈춘다.
#### 다 합친 코드
Fdamp = -kd * dot(ball.v, lhat) * lhat  
Fnet = Fgrav + Fspr + Fdamp  

# 11주차
## 부력
물 위로 뜨려는 힘  
중력 == 부력일시 가만히 있는다.
## 아르키메데스의 원리   

$$\vec{F}_{buoy} = {\rho}Vg\hat{y} $$  

$$\vec{F}_{grav} = -mg\hat{y} $$  

$$\vec{F}_{drag} = -0.5C_d \rho Av^2\hat{v}$$   

### 코드로 구현하기
wood.rho = 500  
water.rho = 1000  
air_rho = 1.2  
rho = air_rho  
Cd = 1.06  
g = vec(0,-9.8,0)  
t = 0  
dt = 0.001  


grav = wood.m*g  
bouy = -water.rho * wood.volum_im * g  
drag = -0.5 * rho * Cd * (wood.size.x * wood.size.y) * mag(wood.v) ** 2 * norm(wood.v)  
wood.f = grav + bouy + drag  

def calc_im(pBox, pbox):
    float_height = (pbox.pos.y + 0.5 * pbox.size.y) - (pBox.pos.y + 0.5 * pBox.size.y)  
    if float_height < 0 :  
        pbox.volume_im = pbox.volume    
    else:  
        pbos.volume_im = max(0, pbox.volume - float_height * pbox.size.x * pbox.size.z)  
    if pbox.volume_im > 0:  
        rho = water.rho  
    else :    
        rho = air_rho  
    return pbox.volume_im, rho  

# 12주차
## 일
물체의 힘을 작용시켜 힘의 방향과 평행한 방향으로 이동시키는 것

$$W = \vec{F} \delta\vec{r}$$

### 포텐셜 에너지

$$U = mgh$$

#### 중력에 의한 포텐셜 에너지

$$U = -\frac{GMm}{r}$$

### 운동에너지

$$ k = \frac{1}{2}mv^2$$

K + U는 일정하다.

## 오일러 크로마 방식의 오류
힘의 변화가 심할 때 정확한 시뮬레이션 불가하다.  
시간 간격을 크게한다.
## 탈출속도
K+ U > 0  
- 최소 탈출 에너지 : $\sqrt{\frac{2gm}{r}}$
## 용수철의 탄성 에너지
$$U = 0.5k_s(|\vec{l}|-l_0)^2$$

# 13주차

$$\vec{v_f} = \vec{v_i} + \frac{\vec{F}}{m}\delta{t}$$

$$m\vec{v_f} = m\vec{v_i} + \vec{F}\delta{t}$$

$$m\vec{v_f}-m\vec{v_i}  = \vec{F}\delta{t} = \vec{J}$$

충격량 : $\vec{F}\delta{t}$  

## 반발계수
물체의 충돌 전 후 상대 속력의 비율

$$e = -\frac{v_{1,f}-v_{2,f}}{v_{1,i} - v_{2,i}}$$

- e == 1 완전 탄성 충돌 : 충돌 시 에너지 손실 없음

- 0 < e < 1 비탄성 충돌 : 충돌 후 두 물체의 상대 속력 줄어듦
- e == 0 완전 비탄성 충돌 : 에너지 손실 최대 발생
### 운동량 보존 법칙 충돌 전후로 같다.

$$m_1v_{1,i}+m_2v_{2,i} == m_1v_{1,f}+m_2v_{2,f}$$

## 물체의 충돌

$$m_1v_{1,f} - m_1v_{1,i} = j\hat{n}$$

$$m_2v_{2,f} - m_2v_{2,i} = -j\hat{n}$$

$$e = -\frac{(v_{1,f}-v_{2,f})\hat{n}}{(v_{1,i} - v_{2,i})\hat{n}}$$

$$j = - \frac{(1+e)(v_{1,i}+v_{2,i})\hat{n}}{\frac{1}{m_1}+\frac{1}{m_2}}$$

### 충돌 시 코드
j = -(1+e) * v_relm  
j = j / (1/b1.m + 1 / b2.m)  
b1.v = b1.v + j * n_hat/b1.m  
b2.v = b2.v - j * n_hat / b2.m  
b1.pos = b1.pos + n_hat * (tot_radius - dist) * b2.m / (t1.m + b2.m)  
b2.pos = b2.pos - n_hat * (tot_radius - dist) * b1.m / (t1.m + b2.m)  
## 마찰력
물체와 물체가 닿으면 두 물체의 접촉면에서 물체의 운동을 방해하는 힘

$$\vec{F_t} =- \mu|\vec{N}|\hat{v} $$

- $\mu$ : 마찰계수 : 두 물체의 표면의 재질에 따라 다르다. 구름 마찰계수는 마찰계수보다 훨씬 작다.
### 표현
ball1.f = - ball1.mu * ball1.m * g * norm(ball1.v)

# 14주차
## 각속력

$$\omega = \frac{\delta\theta}{\delta{t}}$$

$$\theta = \omega{t}$$

$$ v = r\omega$$

## 각 가속도

$$\vec{\alpha} = \frac{\delta\vec{\omega}}{\delta{t}}$$

$$\omega_{n+1} = \omega_n + \vec{\alpha_n}\delta{t}$$

## 회전 관성
회전하는 물체의 각속도를 변화시키는 것이 얼마나 어려운지에 대한 척도

## 돌림힘

$$\vec{\tau}= \vec{r} \vec{F}$$

## 각 운동량

$$I\vec{\omega}$$

회전관성(I)이 커지면 각속도가 느려진다.