print(' -3 abs =', abs(-3))

print('all([1,2,""])', all([1,2,'']))

print('any([1,2,3,"",""])', any([1,2,3,'','']))

print('ord(\'c\') : {} ord(\'C\') : {} chr(6): {}'.format(ord('c'),ord('C'),chr(67)))

for i, name in enumerate(['abc','bad','adeb','aeb']):
    print(i,name)

def conv_pos(x):
    return abs(x)>2
print('conv_pos(3) =',conv_pos(3))
print("list(filter(conv_pos,[1 , -3, 5 , -05]))) = ",list(filter(conv_pos,[1 , -3, 5 , -5])))
#위의 것을 람다로
print(list(filter(lambda x: abs(x) > 2, [1 , -3, 5, -5])))

print(list(map(conv_pos,[1,2,3,4,5,6])))
print(list(map(lambda x:abs(x), [ 1 , -2, -3, -5,-77])))

print('range(1,10,3) =', range(1,10,3))

print('round(3.333333, 3)=',round(3.333333, 3))
print('round(3.33) =',round(3.33))

import sys
#강제종료 sys.exit()

#파이썬 패키지 위치
print(sys.path)

# pickle : 객체 파일 쓰기 = 자료 저장? 데이터 타입 저장?
import pickle

#쓰기
f= open('test.obj','wb')
obj = {1:'python', 2:'study', 3:'basic'}
pickle.dump(obj, f)
f.close()

# 읽기
f= open('test.obj','rb')
data = pickle.load(f)
print(data, type(data))
f.close()

# os
import os
print('>>>>>>os version',os.environ)

# 현재 경로
print(os.getcwd())

# time
import time

print(time.time())
print(time.localtime(time.time()))
print('간단 표현 = ', time.ctime())
#원하는 형식으로 표현
print(time.strftime('%Y-%m-%d %H:%M:%S', time.localtime(time.time())))

#시간 간격 발생
for i in range(5):
    print(i)
    time.sleep(0.5)

# random
import random
print('random.random() =',random.random())
print('random.randint(1,50) =',random.randint(1,50))
print('random.randrange(1,50) =',random.randrange(1,50)) # 50포함 안함

# 섞기
d = [1,2,3,4,5]
a=d
c=a
random.shuffle(d)
print('random.shuffle(d) =',d)
c= random.choice(d)
print('random.choice(d) =',c)

import webbrowser

webbrowser.open_new("http://www.naver.com")
