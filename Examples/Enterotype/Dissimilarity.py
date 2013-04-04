import math

# create dissimilarity matrix
fin = open('Enterotypes.Arumugam.profile.tsv')
data = fin.readlines()
fin.close()

sampleIds = data[0].split('\t')
sampleIds = sampleIds[1:]

print 'Num samples: ' + str(len(sampleIds))

freqs = [ [] for i in range(len(sampleIds)) ]
for i in xrange(1, len(data)):
	line = data[i]
	lineSplit = line.split('\t')
	group = lineSplit[0]
	
	if group.lower() == 'unclassified':
		continue
	
	for j in xrange(1, len(lineSplit)):
		freqs[j-1].append(float(lineSplit[j].strip()))
	
# calculate dissimilarity
fout = open('EnteroGenusDiss.Euclidean.Arumugam.dst', 'w')
for i in xrange(0, len(sampleIds)):
	fout.write(sampleIds[i].strip())
	data1 = freqs[i]
	
	for j in xrange(0, len(sampleIds)):
		data2 = freqs[j]
		
		#kldX = 0
		#kldY = 0
		#for k in xrange(0, len(data1)):
		#	x = data1[k] + 0.000001
		#	y = data2[k] + 0.000001
		#	m = (x + y) / 2
		#	kldX += x * math.log(x / m)
		#	kldY += y * math.log(y / m)
		#diss = 0.5*kldX + 0.5*kldY
		
		diss = 0
		for k in xrange(0, len(data1)):
			diss += (data1[k]-data2[k])*(data1[k]-data2[k])
			
		fout.write(' ' + str(math.sqrt(diss)))
		
	fout.write('\n')

fout.close()