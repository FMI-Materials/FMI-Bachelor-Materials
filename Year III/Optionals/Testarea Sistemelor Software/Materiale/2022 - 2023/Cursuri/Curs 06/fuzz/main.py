# this is from Charlie Miller's "Babysitting an Army of Monkeys"
# John Regehr's (Udacity course instructor) comments

# load a file into buffer

# at a random position of the buffer 
# change the byte to a random one (5 lines of python code)
numwrites = random.randrange(math.ceil((float(len(buf)) / FuzzFactor))) + 1
for j in range(numwrites):
	rbyte = random.randrange(256)
	rn = random.randrange(len(buf))
	buf[rn] = "%c"%(rbyte)

# save the buffer

# run the process

# look at the exit code

# if it doesn't die (no bug found), kill it

# start over