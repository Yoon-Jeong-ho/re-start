f = open('input01.txt','r')
g = open('output01.txt','w')
nn = int(f.readline())
nnn =0
for i in range (0,nn):
    if (i==0):
        a= f.readline().split()
        arow = int(a[1])
        acolumn = int(a[2])

        dap = [[0]*acolumn for x in range(arow)]

    else:
        bline = f.readline().split()
        
        brow = int(bline[1])
        bcolumn = int(bline[2])
        
        if (arow == brow and acolumn == bcolumn):
            nnn=0
        else:
            print("계산불가")
            nnn=1
            g.write('+ 계산 불가')
            g.close()
    
    if (nnn==1):
        break

    for j in range(0,arow):
        aa= f.readline().split()

        
        for k in range(0,acolumn):
            dap[j][k]=dap[j][k]+int(aa[k])
            
            
    f.readline().split()
f. close()


if (nnn==0) :
    for i in range(0,arow):
        
        for j in range(0,acolumn):
            print(dap[i][j],end=' ')
            g.write(str(dap[i][j])+' ')
        print('')
        g.write('\n')

g.close()