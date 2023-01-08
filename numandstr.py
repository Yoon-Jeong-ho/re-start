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