"""
complex : 복소수
bool : 불린 ?  > true
list : 리스트 (시퀸스?)  > [str , str , str , str]
tuple : 튜플 (시퀸스)  > ( 1 , 2 , 3) 괄호도 없어도 되나 쓰는게 좋음
set : 집합          > { 1 , 2 , 3}
dict :사전  {
    "name":"Machine Learning",
    "version": 2.0
}
// :몫
% : 나머지
abs : 절대값
pow(x,y) = x**y x의 y제곱
"""

x , y = divmod(100,8)
print(x,y)

#외부모듈

import math

print(math.pi)
print(math.ceil(5.1)) 
print(math.ceil(5)) 

# 문자열 str
str1 = '123456789 '
print('len(str1)=',len(str1))

# escape 여러 기능이 있음
# print('i'm boy') 오류난다! 역슬려쉬 (달려표시) 사용
print ('I\'m boy')
print ('a \n b')

# raw string (escape 안하기 위함 )
raw_s1 = r'd:wer\asdf'
print(raw_s1)

# 멀티라인
multi_str = '''
asdf
asdf
asdf
'''
print (multi_str)
multi_str = \
'''
asdf
asdf
asdf
'''
print (multi_str)
multi_str = \
'asdf'\
'asdf'\
'asdf'
print (multi_str)

#문자열 연산
str_o1 = '123'
str_o2 = 'adsf'
str_o3 = 'a1s2'
str_o4 = 'a1s1d213'
print(str_o1+str_o2)
print('1' in str_o1)
print('1' not in str_o1)

print('Capitalize',str_o2.capitalize())
print('endswith?:',str_o2.endswith('f'))
print('endswith?:',str_o2.endswith('1'))
print("replace",str_o2.replace('dsf','repllllace') )
print("sorted",sorted(str_o2))
print("split",str_o4.split('1'))

#sqence
im_str = "hello world"

print(dir(im_str)) #__iter__ 가 있으면 반복 가능

for i in im_str:
    print(i)

#슬라이싱
str_sl = "Nice python"
print(str_sl[0:4])
print(str_sl[0:4:2])
print(str_sl[-5:])
print(str_sl[1:-2])
print(str_sl[-1])

#아스키 코드
a= 'z'
print(ord(a))
print(chr(122))

# id
a = [1 , 2, 3, 4, 5]
b=a
print('id a =',id(a))
print('id b =',id(b))
del a[2]
print(a)
a.append(3.3) # 맨 뒤에 추가
print('append ',a)
a.sort()   # 데이터가 많아지면 작업 시간 증가
print('sort ',a)
a.reverse()
print('reverse ',a)
a.insert (3,3) # 원하는 위치에 추가
print('insert ', a)
a.remove(3.3)
print('remove',a)
print('a.pop()=', a.pop())
print('a=',a)
print('a.count(1) =', a.count(1))
print('b',b)
a.extend(b)  # extend는 따로 실행 시켜 줘야 하는듯?
print('a.extend(b)=',a)
print('b',b) # 왜 b도 같이 변화 시키냐...?

