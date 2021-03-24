'''
	Filename: ProcessData.py
	Author: Kyle Bannerman
	Date Created: 03/23/2021
	Date of Last Edit: 03/24/2021
	File Purpose: processing data from spirometer
'''


import pandas as pd
import numpy as np
from os import listdir
from os.path import isfile, join


'''
	Class to store node data
'''
class FlowNode():


	def __init__(self):
		print('create node')
		
		self.startIdx = None

		self.data = list()
		self.zeroCount = 0


	def setStartIdx(self, idx):
		self.startIdx = idx


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


	def __init__(self, inPath='./data', outPath='./output', verbose=True):

		# user input parameters
		self.inPath = inPath
		self.outPath = outPath
		self.verbose = verbose

		# constants
		self.THRESHOLD = 0.1

		# accesible types
		self.data = list()

		# list only files within a directory and ignore hidden files that begin with '.'
		self.listNoHidden = lambda path : [entity for entity in listdir(path) if isfile(join(path, entity)) and not entity.startswith('.')]


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
					currNode.countZero()

				# node inactive
				else:
					self.data.append(currNode.getData())
					currNode = None
					prevVal = val


	'''
		Read in all data files available
	'''
	def readIn(self):

		for filename in self.listNoHidden(self.inPath):

			if self.verbose:
				print('Reading data from \'%s\' . . . ' % filename)

			df = pd.read_csv(join(self.inPath, filename), sep='\t')

			# remove final three columns -- only use raw flow rate 
			df.drop(columns=['0.000000.1', '0.000000.2', '0.000000.3'], inplace=True)
			df.columns = ['FlowRate']

			if self.verbose:
				print('\t[+] Processing data . . . ', end='')

			self.processFrame(df)

			if self.verbose:
				print('done')





if __name__ == "__main__":
	rd = ReadData()
	rd.readIn()