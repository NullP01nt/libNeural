lines=[]
f=open("out","r+")
for l in f:
    l=l.strip()
    if(l.startswith("util")):
        continue
    dat=l.split(";")
    pnr=int(dat[0])
    if len(lines) < pnr:
        lines.append(dat[1])
    else:
        lines[pnr-1]+=";"+dat[1]
f.close()
print lines

of=open("errors.csv","w+")
for i in range(len(lines)):
    of.write(str(i+1)+";"+lines[i]+"\n")
of.close()
