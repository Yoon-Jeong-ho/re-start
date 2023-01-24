# 동시 선언 가능
x = y= z = 100
print(x,y,z)
r='asdf'
print(type(x))
print(type(r))

# id(identity) : 객체 고유값
print(id(x))
print(id(y))
print(id(r))

# 변수 선언
# camel case : numberOfCollegeGraduates -> Method
# pascal case : NumberOfCollegeGraduates -> class
# snake case : number_of_college_graduates -> python

# 예약어는 변수명으로 불가능 (for, as ....)