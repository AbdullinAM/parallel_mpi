import sys
from subprocess import Popen, PIPE

# arguments
args = list(sys.argv)
if len(args) < 4:
	sys.exit("Usage: python testparallel.py *programm* *input file* *num repeats*")

programm = args[1]
inputFile = args[2]
numRepeats = int(args[3])

#run programm

allAreas = 0.0
for proc in [1, 2, 4, 8]:
	times = []
	for i in range(numRepeats):
		#process = Popen([programm, inputFile, '1000000', str(proc)], stdout=PIPE) #common
		process = Popen(['mpiexec', '-np', str(proc), programm, inputFile, '1000000'], stdout=PIPE) #mpi
		exit_code = process.wait()
		if exit_code != 0:
			sys.exit("Cannot run programm")

		for line in process.stdout:
			if 'Circles' in line:
				allAreas = allAreas + float(line.split()[-1])
			if 'Elapsed' in line:
				times.append(float(line.split()[-1]))

	av = sum(times) / numRepeats
	disp = 0.0
	for val in times:
		disp = disp + (val - av) ** 2
	if numRepeats == 1:
		disp = disp / numRepeats
	else:
		disp = disp / (numRepeats - 1)

	print("{} threads: average = {}, dispersion = {}".format(proc, av, disp))

print("Average area = {}".format(allAreas / (4 * numRepeats)))