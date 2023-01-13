# 읽기모드 : r 쓰기모드 :w 추가모드 : a
# 상대경로(../ 상위폴더, ./현재폴더) 절대경로(파일 주소)

#파일 읽기
f=open('git 수업.txt','r',encoding='UTF-8')
print(f.encoding,f.name,f.mode)
a= f.read()
print(a)
f.close()

with open('git 수업.txt','r',encoding='UTF-8') as f:
    c= f.read(15)
    print(c, iter(c), list(c))
    print(c)
    c= f.read(15)
    print(c)
    c= f.seek(0,0)
    c= f.read(15)
    print(c)

    
with open('git 수업.txt','r',encoding='UTF-8') as f:
    line = f.readline()
    print('line=',line)
    line = f.readline()
    print('line=',line)

with open('git 수업.txt','r',encoding='UTF-8') as f:
    cts = f. readlines()
    print(cts)  
    for c in cts :
        print(c, end = '')

# 쓰기 > 원문 다 사라지고 적기
with open('test.txt','w') as f:
    f.write('hello\n')
# a = add 즉 원문에 첨가
with open('test.txt','a') as f:
    f.write('hello22\n')

with open('test.txt','a') as f:
    list=['qwer','qwer\n','qwerqwe','qewr\n']
    f.writelines(list)

with open('test.txt','a') as f:
    print('asdf',file=f)
    print('asdf',file=f)
    print('asdf',file=f)


    


