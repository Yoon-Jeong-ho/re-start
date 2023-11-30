def det(mat, n):
    if (n==3):
            a=mat[0][0]*(mat[1][1]*mat[2][2]-mat[1][2]*mat[2][1])
            aa=mat[0][1]*(mat[1][0]*mat[2][2]-mat[1][2]*mat[2][0])
            aaa=mat[0][2]*(mat[1][0]*mat[2][1]-mat[1][1]*mat[2][0])
            return a-aa+aaa
    else:
        dap=0
        for i in range (0,n):
            mat1=[[0]*(n-1) for x in range(n-1)]
            s=mat[0][i]
            for j in range(1,n):
                nn = 0
                for k in range(0,n):
                    if i==k:
                        nn=1
                        continue
                    else :
                        mat1[j-1][k-nn]=mat[j][k]
                dap=dap+s*det(mat1,n-1)*((-1)**(i))
        return dap
    return 0

f = open('input.txt','r')
g = open('output.txt','w')
ff = open('input.txt','r')

a= f.readline().split()
acolumn = len(a)
arow = 1
aaa=0
while True :
    a= f.readline().split()        
    if len(a) ==0 :
        if (arow != acolumn) :
            for i in range (0,arow+1) :
                b=ff.readline()
            print("계산불가")
            g.write("계산불가")
            aaa=1
        
        break
    arow = 1 + arow

if (aaa==0) :
    ahang = [[0]*acolumn for x in range(arow)]
    for i in range(0, arow):
        aa= ff.readline().split()
        for j in range(0, acolumn):
            ahang[i][j]=int(aa[j])
    
    
    for x in range(arow):
        for y in range(acolumn):
            print(ahang[x][y],end=' ')
        print(' ')
    
    x = det(ahang,arow)
    print(x)
    g.write(str(x)+'\n')
    aa= ff.readline().split()



a= f.readline().split()
acolumn = len(a)
arow = 1
aaa=0
while True :
    a= f.readline().split()        
    if len(a) ==0 :
        if (arow != acolumn) :
            for i in range (0,arow+1) :
                b=ff.readline()
            print("계산불가")
            g.write("계산불가")
            aaa=1
        
        break
    arow = 1 + arow

if (aaa==0) :
    ahang = [[0]*acolumn for x in range(arow)]
    for i in range(0, arow):
        aa= ff.readline().split()
        for j in range(0, acolumn):
            ahang[i][j]=int(aa[j])
    
    
    for x in range(arow):
        for y in range(acolumn):
            print(ahang[x][y],end=' ')
        print(' ')
    
    x = det(ahang,arow)
    print(x)
    g.write(str(x)+'\n')
    aa= ff.readline().split()


a= f.readline().split()
acolumn = len(a)
arow = 1
aaa=0
while True :
    a= f.readline().split()        
    if len(a) ==0 :
        if (arow != acolumn) :
            for i in range (0,arow+1) :
                b=ff.readline()
            print("계산불가")
            g.write("계산불가")
            aaa=1
        
        break
    arow = 1 + arow

if (aaa==0) :
    ahang = [[0]*acolumn for x in range(arow)]
    for i in range(0, arow):
        aa= ff.readline().split()
        for j in range(0, acolumn):
            ahang[i][j]=int(aa[j])
    
    
    for x in range(arow):
        for y in range(acolumn):
            print(ahang[x][y],end=' ')
        print(' ')
    
    x = det(ahang,arow)
    print(x)
    g.write(str(x))
    aa= ff.readline().split()
