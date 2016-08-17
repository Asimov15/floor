from pylab import *
import csv

t = []
x = []
v = []
tke = []
tgpe = []
te   = []
mdata = "/home/dz/programming/floor/DZ"
ifile1 = open(mdata, "r")
reader1 = csv.reader(ifile1)
toggle = 0
for row in reader1:	
	t.append(row[5])
	x.append(row[2])	
ylim([9500,9900])	
xlim([0,4])
suptitle('Total E')
scatter(t, x, s=2.0)
show()
