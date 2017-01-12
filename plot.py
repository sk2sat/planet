#! /usr/bin/env python3

import sys
import csv
import six
import numpy as np
from   mpl_toolkits.mplot3d.axes3d import Axes3D
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

def plot(data, fig, fformat, dim, fnum, xlim, ylim):
	if plot.count == 1:
#		input('>>')
		pass
	
	if plot.count > fnum:
		print('plot end.')
		input('')
		return
	
	plt.cla()
	plt.title('num = ' + str(plot.count))
	plt.xlim(-1*xlim, xlim)
	plt.ylim(-1*ylim, ylim)
	
	# file load
	fname = fformat % plot.count
	file = open(fname, 'r')
	time = float(file.readline())
	nP   = int(file.readline())
	
	points = []
	X = []
	Y = []
	Z = []
	j = 0
	for line in file:
#		points.append(Point())
		X.append(float)
		Y.append(float)
		Z.append(float)
		itemlist = line[:-1].split(' ')
#		print(itemlist)
		x = float(itemlist[0])
		y = float(itemlist[1])
		z = float(itemlist[2])
		
#		points[j].x = x
#		points[j].y = y
#		points[j].z = z
		
		X[j] = x
		Y[j] = y
		Z[j] = z
		j += 1
	
	for i in range(0,nP):
		if dim == 2:
#			plt.plot(points[i].x, points[i].y, 'o')
			plt.plot(X, Y, 'o')
		if dim == 3:
#			plt.plot(points[i].x, points[i].y, points[i].z, 'o')
			ax = Axes3D(fig)
			ax.set_xlim(-1000, 1000)
			ax.set_ylim(-1000, 1000)
			ax.set_zlim(-1000, 1000)
			ax.scatter3D(X, Y, Z)
	
	plot.count += 1


plot.count = 0


def main(argv):
	xlim = 1000
	ylim = 1000
	
	argc = len(argv)
	if argc == 1 or argc == 2 or argc == 3 or argc > 6 :
		print('usage> ./plot.py mode(show/save)  dim file_format file_number [xlim] [ylim]')
		return
	
	if argc == 6:
		xlim = int(argv[5])
	if argc == 7:
		xlim = int(argv[5])
		ylim = int(argv[6])
	
	mode = argv[1]
	dim = int(argv[2])
	fformat = argv[3]
	fnum = int(argv[4])
	
	print('mode : ' + mode)
	print('dim = ' + str(dim))
	
#	dim = 2
	frames = 20
	
	i = 0
	while True:
		fig = plt.figure()
		ani = anim.FuncAnimation(fig, plot, interval=10, fargs=(fig, fformat, dim, fnum, xlim, ylim), frames=frames)
		if mode == 'show':
			plt.show()
		elif mode == 'save':
			fname = 'output%05d.gif' % i
			print('writing: ' + fname)
			ani.save(fname, writer='imagemagick')
		else:
			print('invalid mode : ' + mode)
			return -1
		i += 1

#	for i in range(0,fnum):
#		fname = fformat % i
#		print('loading : ' + fname)
		
		
#		csv_reader = csv.reader(open(fname, 'r'), delimiter=' ')
		
#		for row in csv_reader:
#			six.print_(row)
#			print(row)

if __name__ == '__main__':
	main(sys.argv)

