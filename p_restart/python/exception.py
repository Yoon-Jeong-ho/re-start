# SuntaxError 문법 틀림, TypeError 자료형 계산 오류, indexerror, nameError, ValueError
# 문법 예외는 없지만 코드 실행 단계에서 발생하는 예외도 중요
# 예외는 반드시 처리
# 로그는 반드시 남긴다
# 예외는 던져진다 ?
# 예외 무시

# SyntaxError ex) print('error)

# NameError ex) a= 10, print(b)

# ZeroDivisionError ex) print(100/0)

# IndexError ex) x=[10,20], print(x[3])

# keyError ex) dic = {'name': 'lee'}, print (dic['age'])  > 예외 해결 print(dic.get('age'))

# AttributeError : 모듈, 클래스에 있는 잘못된 속성 사용 예외

# ValueError ex) x= [10, 20], x.remove(100)

# FileNotFoundError :없는 파일 열기

# TypeError ex) x=[1,2], y=(2,3), print(x+y)

# 예외처리 기본
# try, except, else, finally

name=['kim','lee','park']

try:
    z = input('inter your name')
    x= name.index(z)
    print('{} Found it {} in name'.format(z, x+1))
except ValueError as e:
    print(e)
    print('Not found it! - occurred ValueError!')
else :
    print('Ok! else.')
finally :
    print('이건 항상 실행된다')


try:
    if name[2]== 'kim':
        print('gogo')
    else:
        raise ValueError
except ValueError:
    print('get out')
else:
    print('hello')


    





