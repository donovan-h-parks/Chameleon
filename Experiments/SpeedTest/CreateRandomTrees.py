from Bio.Nexus.Trees import Tree
import os, time, sys
import random

numSequences = int(sys.argv[1])
numSamples = int(sys.argv[2])

seqList = []
for i in xrange(1, numSequences+1):
	seqList.append('Seq' + str(i))

# create random trees and save to file
fout = open('RandomTree.tre', 'w')

tree = Tree()
tree.randomize(ntax = numSequences, taxon_list = seqList[0:numSequences], branchlength_sd=0.5)
treeStr = tree.to_string(branchlengths_only = True, plain_newick = True)
fout.write(treeStr + ';\n')		
fout.close()
	
# create environment file
fout = open('RandomTree.env', 'w')
additionalSeqs = numSequences
for i in xrange(0, numSequences):
	# ensure there are the desired number of unique sequences
	rndSampleId = random.randint(1,numSamples)
	fout.write(seqList[i] + '\tSample' + str(rndSampleId) + '\t' + str(random.randint(1,100)) + '\n')
	
	# the file will also contain additional sequences so there are sequences that come from multiple samples
	if additionalSeqs > 0:
		numSamplesForSeq = random.randint(0, int(numSamples*0.5))
		additionalSeqs -= numSamplesForSeq
		
		sampleIds = range(1, numSamples+1)
		sampleIds.remove(rndSampleId)
		for dummy in xrange(0, numSamplesForSeq):			
			rndIndex = random.randint(0, len(sampleIds)-1)					
			fout.write(seqList[i] + '\tSample' + str(sampleIds[rndIndex]) + '\t' + str(random.randint(1,100)) + '\n') 
			sampleIds.remove(sampleIds[rndIndex])
	
	
fout.close()
