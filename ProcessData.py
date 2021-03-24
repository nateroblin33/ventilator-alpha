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
	Class to read in .data file format of spirometry data
'''
class ReadData():


	def __init__(self, inPath='./data', outPath='./output', verbose=True):
		
		self.inPath = inPath
		self.outPath = outPath
		self.verbose = verbose

		# list only files within a directory and ignore hidden files that begin with '.'
		self.listNoHidden = lambda path : [entity for entity in listdir(path) if isfile(join(path, entity)) and not entity.startswith('.')]


	'''
		Process the flow rate dataframe
	'''
	def processFrame(self, df):
		#TODO process data
		pass


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