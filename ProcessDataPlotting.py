'''
	Filename: ProcessData.py
	Author: Kyle Bannerman & Nate Roblin (add-ons!)
	Date Created: 03/23/2021
	Date of Last Edit: 03/25/2021
	File Purpose: processing data from spirometer
'''


import pandas as pd
import numpy as np
from os import listdir
from os.path import isfile, join

import matplotlib.pyplot as plt


'''
	Class to store node data
'''
class FlowNode():

	def __init__(self):

		self.startIdx = None

		self.data = list()
		self.zeroCount = 0

	def setStartIdx(self, idx):
		self.startIdx = idx

	def getStartIdx(self):
		return self.startIdx

	def addData(self, val):
		self.data.append(val)

	def countZero(self):
		self.zeroCount += 1

	def getData(self):
		return self.data


'''
	Class to read in .data file format of spirometry data
'''
class ReadData():


	def __init__(self, inPath='./data', outPath='./output', verbose=True, plot=True):

		# user input parameters
		self.inPath = inPath
		self.outPath = outPath
		self.verbose = verbose
		self.plot = plot

		# constants
		self.THRESHOLD = 0.08
		self.STEP = 1 / 500

		# accesible types
		self.data = list()
		self.stats = list()

		# list only files within a directory and ignore hidden files that begin with '.'
		self.listNoHidden = lambda path : [entity for entity in listdir(path) \
										   if isfile(join(path, entity)) and not entity.startswith('.')]


	'''
		Process the flow rate dataframe
	'''
	def processFrame(self, df):

		currNode = None
		prevVal = 0.
		
		for idx, val in df['FlowRate'].iteritems():

			# new node found
			if currNode == None and val >= self.THRESHOLD:

				currNode = FlowNode()
				currNode.setStartIdx(idx)

				prevVal = val

			# currently within a node
			elif currNode != None:

				# node still active
				if val >= self.THRESHOLD:
					currNode.addData(val)
					prevVal = val

				# missing data
				elif val == 0. and prevVal != val:

					# check for erroneous spikes:
					if len(currNode.data) == 1:
						currNode = None
					else:
						currNode.countZero()

				# node inactive
				else:
					self.data.append((currNode.getStartIdx(), currNode.getData()))
					currNode = None
					prevVal = val


	'''
		Calculate area under a node
	'''
	def calcArea(self, node):

		area = 0.

		for i in range(len(node) - 1):

			area += self.STEP * (node[i] + node[i + 1]) / 2

		return area



	'''
		Analyze preprocessed nodes
	'''
	def analyzeNodes(self):

		self.stats = list()

		for idx, node in self.data:

			if len(self.stats) == 0:
				self.stats.append([idx * self.STEP, 
								   self.calcArea(node), 
								   max(node),
								   len(node) * self.STEP,
								   0.,
								   self.calcArea(node),
								   0.])
			else:
				self.stats.append([idx * self.STEP,
								   self.calcArea(node),
								   max(node),
								   len(node) * self.STEP, 
								   idx * self.STEP - self.stats[-1][0],
								   self.calcArea(node) + self.stats[-1][5],
								   self.stats[-1][-1] + idx * self.STEP - self.stats[-1][0]])
			'''
				TotalArea column records cumulative total from each node
			'''
		self.stats = pd.DataFrame(data=self.stats, 
								  columns=['StartTime', 'Volume', 'PeakFlowRate', 'PulseTime', 
										   'TimeBetweenFlow', 'TotalVolume', 'TimeElapsed'])


	'''
		Plot all preprocessed nodes on one figure
	'''
	def plotData(self, filename):
		
		plt.figure(filename)
		plt.title(filename)
		plt.xlabel('Time (s)')
		plt.ylabel('Instantaneous Flow Rate (L/s)')
		
		for idx, node in self.data:
			plt.plot(np.arange(0,(len(node))*self.STEP,self.STEP).tolist(),node)
		
		plt.show(filename)

	'''
		Print specific stat
	'''
	def printStat(self, statStr):
		if statStr == 'Total Volume':
			print('%s:\n\t%1.5f' % (statStr, self.stats[statStr.replace(' ', '')].max()))
		else:
			print('%s:\n\tMean: %1.5f\tSTD: %1.5f' % (statStr, self.stats[statStr.replace(' ', '')].mean(), 
												  self.stats[statStr.replace(' ', '')].std()))

	'''
		Display relevant information about the nodes
	'''
	def displayStats(self, filename):

		print('***************\nSTATISTICS: \'%s\'\n***************' % filename)

		print('Node Count: %d' % len(self.stats.index))

		self.printStat('Volume')
		self.printStat('Peak Flow Rate')
		self.printStat('Pulse Time')
		self.printStat('Time Between Flow')
		self.printStat('Total Volume')

		print('Mean Flow Rate (L/min):\n\t%1.5f' % (self.stats.tail(1)['TotalVolume'] / self.stats.tail(1)['TimeElapsed'] * 60))


	'''
		Read in all data files available
	'''
	def readIn(self):

		for filename in self.listNoHidden(self.inPath):

			self.data = list()
			
			if self.verbose:
				print('Reading data from \'%s\'' % filename)

			df = pd.read_csv(join(self.inPath, filename), sep='\t')

			# remove final three columns -- only use raw flow rate 
			df.drop(columns=df.columns[1:], inplace=True)
			df.columns = ['FlowRate']

			if self.verbose:
				print('\tProcessing data . . . ', end='')

			self.processFrame(df)

			self.analyzeNodes()

			if self.verbose:
				print('done')

			self.displayStats(filename)

			if self.plot:
				self.plotData(filename)




if __name__ == "__main__":
	rd = ReadData()
	rd.readIn()
