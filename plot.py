#! /usr/bin/env python3

import sys
import csv
import six
import numpy as np
from   mpl_toolkits.mplot3d import Axes3D
import matplotlib.pyplot as plt
import matplotlib.animation as anim

#x = np.arange(-3, 3, 0.25)
#y = np.arange(-3, 3, 0.25)
#X, Y = np.meshgrid(x, y)
#Z = np.sin(X) + np.cos(Y)

#fig = plt.figure()
#ax = Axes3D(fig)
#ax.plot_wireframe(X,Y,Z)
#ax.scatter3D(np.ravel(X), np.ravel(Y), np.ravel(Z))
#plt.show()

class Point(object):
	def __init__(self):
		self.x	= 0.0
		self.y	= 0.0
		self.z	= 0.0

def plot(data, fformat, dim, fnum, xlim, ylim):
	if plot.count == 1:
		input('>>')
	
	if plot.count > fnum:
		print('plot end.')
		input('')
		return
	
#	plt.cla()
	plt.title('num = ' + str(plot.count))
	plt.xlim(-1*xlim, xlim)
	plt.ylim(-1*ylim, ylim)
	
	# file load
	fname = fformat % plot.count
	file = open(fname, 'r')
	time = float(file.readline())
	nP   = int(file.readline())
	
	points = []
	j = 0
	for line in file:
		points.append(Point())
		itemlist = line[:-1].split(' ')
#		print(itemlist)
		x = float(itemlist[0])
		y = float(itemlist[1])
		z = float(itemlist[2])
		
		points[j].x = x
		points[j].y = y
		points[j].z = z
		j += 1
	
	for i in range(0,nP):
		if dim == 2:
			plt.plot(points[i].x, points[i].y, 'o')
		if dim == 3:
			plt.plot(points[i].x, points[i].y, points[i].z, 'o')
	
	plot.count += 1


plot.count = 0


def main(argv):
	xlim = 1000
	ylim = 1000
	
	argc = len(argv)
	if argc == 1 or argc == 2 or argc == 3 or argc > 6 :
		print('usage> ./plot.py dim_number file_format file_number [xlim] [ylim]')
		return
	
	if argc == 5:
		xlim = int(argv[4])
	if argc == 6:
		xlim = int(argv[4])
		ylim = int(argv[5])
	
	dim = int(argv[1])
	fformat = argv[2]
	fnum = int(argv[3])
	
	print('dim = ' + str(dim))
	
	dim = 2
	
	fig = plt.figure()
	ani = anim.FuncAnimation(fig, plot, interval=10, fargs=(fformat, dim, fnum, xlim, ylim))
	plt.show()
	
#	for i in range(0,fnum):
#		fname = fformat % i
#		print('loading : ' + fname)
		
		
#		csv_reader = csv.reader(open(fname, 'r'), delimiter=' ')
		
#		for row in csv_reader:
#			six.print_(row)
#			print(row)

if __name__ == '__main__':
	main(sys.argv)

