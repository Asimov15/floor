from pylab import *
import csv

t = []
x = []
v = []
tke = []
tgpe = []
te   = []
mdata = "/home/dz/programming/nbody/DZ3"
ifile1 = open(mdata, "r")
reader1 = csv.reader(ifile1)
toggle = 0
for row in reader1:	
	t.append(row[5])
	x.append(row[0])	
ylim([0,7e-7])	
xlim([0,7.2e5])
suptitle('KE')
scatter(t, x, s=2.0)
show()
