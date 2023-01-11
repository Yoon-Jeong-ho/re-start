#객체지향!
# class 형태로 사용!

class Dog: #object상속
    # 클래스 속성
    species = 'firstdog'
    #초기화/ 인스턴스 속성
    def __init__(self, name, age):
        self.name = name
        self.age = age 
    pass

print(Dog)

# 인스턴스화

a= Dog('abc', 2)
b= Dog('hoo',3)

# 네임 스페이스
print(a.__dict__)
print(b.__dict__)

# 인스턴트 속성 확인
print('{} is {} and {} is {}'.format(a.name, a.age, b.name, b.age))

# self ???
class SelfTest:
    def func1():
        print('1')
    def func2(self):
        print('2')

f = SelfTest()

SelfTest.func1()
f.func2()

class Warehouse:
    #클래스 변수
    stock_num = 0 

    def __init__(self,name):
        #인스턴스 변수
        self.name = name
        Warehouse.stock_num += 1
    
    def __del__(self):
        Warehouse.stock_num -= 1

user1 = Warehouse('kee')
user2 = Warehouse('kim')
print(user1.name)
print('before',Warehouse.stock_num)

del user1

print('after',Warehouse.stock_num)


