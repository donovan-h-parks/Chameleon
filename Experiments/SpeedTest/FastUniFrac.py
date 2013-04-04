import time
from cogent.maths.unifrac.fast_unifrac import fast_unifrac_file
from cogent.maths.unifrac.fast_tree import unnormalized_unifrac

timing = []
for i in xrange(0, 1):	
	treeFile = open('RandomTree.tre')
	envFile = open('RandomTree.env')
	
	t1 = time.time()
	res = fast_unifrac_file(treeFile, envFile, weighted=True, modes=["distance_matrix"])
	t2 = time.time()
	
	treeFile.close()
	envFile.close()
	
	timing.append(t2-t1)
	print t2-t1

fout = open('FastUniFracTiming.txt', 'w')
fout.write(str(min(timing)))
fout.close




