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


#csv    

import csv

with open('./resource/test1.csv','r') as f:
    reader = csv.reader(f)
    next(reader) # 헤드 생략 첫줄 생략
    for c in reader :
        print(c)
        print(' : '.join(c))

with open('./resource/test1.csv','r') as f:
    reader = csv.reader(f,delimiter= ',')
    for c in reader :
        print(c)

with open('./resource/test1.csv','r') as f:
    reader = csv.DictReader(f)
    for c in reader:
        print(c)
        for k,v in c.items():
            print(k,v)

w= [[1,2,3],[1,3,5],[2,3,4],[5,6,7],[8,9,0]]

with open('./resource/test2.csv','w') as f:
    wt = csv.writer(f)
    for v in w:
        wt.writerow(v)


with open('./resource/write2.csv','w') as f:
    fields = ['one','two','three']
    wt = csv.DictWriter(f, fieldnames=fields)
    wt.writeheader()
    for v in w:
        wt.writerow({'one': v[0], 'two' : v[1], 'three':v[2]})


