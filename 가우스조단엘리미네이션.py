f = open('input1.txt','r')
g = open('output.txt','w')
a= f.readline().split()
g.write(str(a) + "\n")
a= f.readline().split()
row=int(a[0])
column=int(a[1])
ahang = [[0]*(column+2) for x in range(row)]
for i in range(0,row):
    a= f.readline().split()
    for j in range(0,column+1):
        if (j==column):
            ahang[i][j+1]=float(a[j])
            ahang[i][j]='l'
        else:
            ahang[i][j]=float(a[j])
for x in range (row):
    for z in range (column+2):
        g.write(str(ahang[x][z]) + " ")
    g.write("\n")
g.write("\n")

for k in range (0,row-1):
    for i in range (0,row):
        for l in range(0,column):
            if ahang[i][l]== 0:
                u=0
            else :
                u=ahang[i][l]
                break

        for j in range (0,column+1):
            if (j==column):
                ahang[i][j+1]= ahang [i][j+1]/u
            else:
                ahang[i][j]= ahang [i][j]/u
        for x in range (row):
            if (u==1):
                break

            for z in range (column+2):
                g.write(str(ahang[x][z]) + " ")
            g.write("\n")

        else:
            g.write("\n")
    for m in range(k+1, row):
        for n in range(0,column+1):
            if (n == column):
                ahang[m][n+1]=ahang[m][n+1]-ahang[k][n+1]
            else :
                ahang[m][n]=ahang[m][n]-ahang[k][n]
        for x in range (row):
            for z in range (column+2):
                g.write(str(ahang[x][z]) + " ")
            g.write("\n")
        g.write("\n")
for k in range (0,row-1):
    for i in range (0,row):
        for l in range(0,column):
            if ahang[row-1-i][column-1-l]== 0:
                u=0
            else :
                u=ahang[row-1-i][column-1-l]
                
                break
        for j in range (0,column+1):
            if (j==column):
                ahang[row-1-i][j+1]= ahang [row-1-i][j+1]/u
            else:
                ahang[row-1-i][j]= ahang [row-1-i][j]/u
        for x in range (row):
            if (u==1):
                break
            for z in range (column+2):
                g.write(str(ahang[x][z]) + " ")
            g.write("\n")
        g.write("\n")
    for m in range(k+1, row):
        for n in range(0,column+1):
            if (n == column):
                ahang[row-1-m][n+1]=ahang[row-1-m][n+1]-ahang[row-k-1][n+1]
            else :
                ahang[row-1-m][n]=ahang[row-1-m][n]-ahang[row-k-1][n]
        for x in range (row):
            for z in range (column+2):
                if(str(ahang[x][z])=='-0.0'):
                        ahang[x][z]=0
                g.write(str(ahang[x][z]) + " ")
            g.write("\n")
        g.write("\n")
o=float(ahang[0][0])
if o==1 or o==0:
    o=1
else:
    for i in range(0,column+1):
        if ahang[0][0] == 0:
            break
        if i==column:
            ahang[0][i+1]=ahang[0][i+1]/o

        else :
            ahang[0][i]=ahang[0][i]/o
    for x in range (row):
        for z in range (column+2):
            if(str(ahang[x][z])=='-0.0'):
                        ahang[x][z]=0
            g.write(str(ahang[x][z]) + " ")
        g.write("\n")
    g.write("\n")
while 1:
    con = input()
    if (con=='y' or con == 'yes' or con=='1'):
        com = input()
        f=open(com,"r")
        a= f.readline().split()
  
        g.write(str(a) + "\n")
        a= f.readline().split()
   
        row=int(a[1])
        column=int(a[0])
        
        ahang = [[0]*(column+2) for x in range(row)]
       
        for i in range(0,row):
            a= f.readline().split()
         
            for j in range(0,column+1):
                if (j==column):
                    
                    ahang[i][j+1]=float(a[j])
                    ahang[i][j]='l'
                else:
                    ahang[i][j]=float(a[j])
   
        for x in range (row):
            for z in range (column+2):
                g.write(str(ahang[x][z]) + " ")
            g.write("\n")
        g.write("\n")
    
        for k in range (0,row-1):
            for i in range (0,row):
                for l in range(0,column):
                    if ahang[i][l]== 0:
                        u=0
                        
                    else :
                        u=ahang[i][l]
                    
                        break
                for j in range (0,column+1):
                    if (u==0):
                        tg=0
                        break
                    else:
                        tg=1
                    if (j==column):
                        ahang[i][j+1]= ahang [i][j+1]/u
                    else:
                        ahang[i][j]= ahang [i][j]/u
                for x in range (row):
                    if tg==0 or u==1:
                        break
                    for z in range (column+2):
                        g.write(str(ahang[x][z]) + " ")
                    g.write("\n")
                g.write("\n")
            for m in range(k+1, row):
                if tg==0:
                    break
                
                for n in range(0,column+1):
                    if (n == column):
                        ahang[m][n+1]=ahang[m][n+1]-ahang[k][n+1]
                    else :
                        ahang[m][n]=ahang[m][n]-ahang[k][n]
                for x in range (row):
                    for z in range (column+2):
                        g.write(str(ahang[x][z]) + " ")
                    g.write("\n")
                g.write("\n")
        for k in range (0,row-1):
            for i in range (0,row):
                for l in range(0,column):
                    if ahang[row-1-i][l]== 0:
                        u=0
                    else :
                        u=ahang[row-1-i][l]
                
                        break
                for j in range (0,column+1):
                    if(u==0):
                        tg=0
                        break
                    else:
                        tg=1
                    if (j==column):
                        ahang[row-1-i][j+1]= ahang [row-1-i][j+1]/u
                    else:
                        ahang[row-1-i][j]= ahang [row-1-i][j]/u
                for x in range (row):
                    if tg==0 or u==1:
                        break
                    for z in range (column+2):
                        g.write(str(ahang[x][z]) + " ")
                    g.write("\n")
                if tg==0 or u==1:
                    u=1
                else:
                    g.write("\n")
            for m in range(k+1, row):
                if tg==0:
                    break
                for n in range(0,column+1):
                    if (n == column):
                        ahang[row-1-m][n+1]=ahang[row-1-m][n+1]-ahang[row-k-1][n+1]
                    else :
                        ahang[row-1-m][n]=ahang[row-1-m][n]-ahang[row-k-1][n]
                for x in range (row):
                    for z in range (column+2):
                        if(str(ahang[x][z])=='-0.0'):
                            ahang[x][z]=0
                        g.write(str(ahang[x][z]) + " ")
                    g.write("\n")
                g.write("\n")
        o=float(ahang[0][0])
        if o==1 or o==0:
            o=1
        else:
            for i in range(0,column+1):
                if ahang[0][0] == 0:
                    break
                if i==column:
                    ahang[0][i+1]=ahang[0][i+1]/o

                else :
                    ahang[0][i]=ahang[0][i]/o
            for x in range (row):
                for z in range (column+2):
                    if(str(ahang[x][z])=='-0.0'):
                        ahang[x][z]=0
                    g.write(str(ahang[x][z]) + " ")
                g.write("\n")
            g.write("\n")
    else:
        break