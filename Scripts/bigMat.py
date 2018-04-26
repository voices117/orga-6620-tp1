import numpy as np
rows  = 100
cols = 10
low = 0
high = 10
step = 1

matrix = np.random.choice([x for x in xrange(low,high,step)],rows*cols)
matrix.resize(rows,cols)

f = open('bigMat.m','wb')
f.write("%d " %rows)
f.write("%d\n" %cols)
np.savetxt(f, matrix, fmt='%i')
