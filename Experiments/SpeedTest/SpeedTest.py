import os, sys, time

numUniqueSeqs = [10000]
numUniqueSamples = [500]

fout = open('SpeedTestResults.csv', 'w')
fout.write('Unique sequences,Samples,Fast UniFrac Time,UniSplit Time (1 core),UniSplit IO (1 core),UniSplit Algo. (1 Core),UniSplit Time (2 cores),UniSplit IO (2 core),UniSplit Algo. (2 core)')
fout.write(',UniSplit Time (3 core),UniSplit IO (3 core),UniSplit Algo. (3 Core),UniSplit Time (4 cores),UniSplit IO (4 core),UniSplit Algo. (4 core)')
fout.write(',UniSplit Time (5 core),UniSplit IO (5 core),UniSplit Algo. (5 Core),UniSplit Time (6 cores),UniSplit IO (6 core),UniSplit Algo. (6 core)')
fout.write(',UniSplit Time (7 core),UniSplit IO (7 core),UniSplit Algo. (7 Core),UniSplit Time (8 cores),UniSplit IO (8 core),UniSplit Algo. (8 core)')

fout.write('\n')

for seqs in numUniqueSeqs:
	print seqs
	for samples in numUniqueSamples:
		print '  ' + str(samples)
		os.system('python CreateRandomTrees.py ' + str(seqs) + ' ' + str(samples))
		#os.system('python FastUniFrac.py')
		
		#fin = open('FastUniFracTiming.txt')
		#fastUniFracTime = float(fin.readline())
		fastUniFracTime = 1.0
		#fin.close()
		
		fout.write(str(seqs) + ',' + str(samples) + ',' + str(fastUniFracTime))
		
		speedUpUF = []
		speedUpUS = []
		for cores in xrange(1, 3):
			os.system('UniSplit.exe --cores ' + str(cores) + ' --sandbox')
		
			fin = open('UniSplitTiming.txt')
			timingInfo = fin.readline().split('\t');
			fin.close()

			fout.write(',' + str(timingInfo[2]) + ',' + str(timingInfo[0]) + ',' + str(timingInfo[1]))			
		
		fout.write('\n')
		
fout.close()
