#iterable 리턴함수 : range, reversed, enumerate, filter, map, zip

names = ['kim', 'park', 'cho', 'lee'] # list
for i in names :
    print('names :',i)

lotter_numbers = [11, 13, 16,25,36,44]
for i in lotter_numbers:
    print('numbers =',i)

my_info = {
    'name': 'lee',
    'age' : '33',
    'city' : 'seoul'
} # dict
for i in my_info:
    print(i , end =' : ' )
    print( my_info[i])

# a.isupper() > a가 대문자인가 , a.upper() a를 대문자로


# function
print('function>>>>>>>>>>>>>>>>>>>>>')
def first_func(w):
    print("hello, ",w)

word = 'function'
first_func(word)

def second_func(w):
    return 'hello' + str(w)

t=second_func(word)
print(t)
# 튜플 리턴 

def tu(l):
    z=l
    x=l+1
    y=l*30
    return (x , y , z)

x= tu(10)
print('tuple', x)

def li(t):
    z = t*t
    y = t**t
    x = t*t**t*t
    return [ x, y, z]

y = li(2)
print('list ', y)

def dict(k):
    z=k+k
    y=k*k*k
    x=k**k
    return {'x' : x, 'y':y , 'z': z}

z = dict(12)
print('dict',z)

#언팩킹 * 별 하나만 붙이기
def args_func(*aes): 
    for i, v in enumerate(aes):
        print('i =',i,'v =',v)
    print('------')

args_func ('lee','wef','wefwef','489')

# ** 별 두개 붙이기
def kwargs_func (**qewg):
    for v in qewg.keys():
        print(v,qewg[v])
    print('---------')

kwargs_func(awef='wef',aweef='wefwe',qqwfq='qweqf')

def example(a,b,c,*d,**e):
    print(a,b,c,d,e)

example(1,2,3,'asdf','asdfasd','asdf','adfasdf',',asdfasdfsadf','asdfasfa',age=1,birtg=2,cad=3,dedeae=4)

#중첩함수

def nested_func(num):
    def funcinfunc(num):
        print(num)
    print('in func')
    funcinfunc(num+1)

nested_func(100)

# Lambda

qwer = lambda w,y:w**y
print('lambda', qwer(5,5))

def fu_la (x,y,funcc):
    print(x*y*funcc(3,2))

fu_la(6, 7, lambda w,e:w*e+e)

