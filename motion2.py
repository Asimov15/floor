from pylab import *
import csv

t = []
x = []
v = []
tke = []
tgpe = []
te   = []
mdata = "/home/dz/programming/nbody/DZ"
ifile1 = open(mdata, "r")
reader1 = csv.reader(ifile1)
toggle = 0
for row in reader1:	
	t.append(row[5])
	x.append(row[3])	
ylim([-8e-5,8e-5])	
xlim([0,7.2e5])
suptitle('Velocity')
scatter(t, x, s=2.0)
show()
