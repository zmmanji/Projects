import random
import math

##ZEESHAAN MEHBOOB MANJI


#####################################################
#####################################################
# Please enter the number of hours you spent on this
# assignment here
num_hours_i_spent_on_this_assignment = 35
#####################################################
#####################################################

#####################################################
#####################################################
# Give one short piece of feedback about the course so far. What
# have you found most interesting? Is there a topic that you had trouble
# understanding? Are there any changes that could improve the value of the
# course to you? (We will anonymize these before reading them.)
# <Your feedback goes here>
# Lectures are moving too fast I believe since we are approaching the end of the semester it would be nice to do a review on the last week of classes
#####################################################
#####################################################

# Outputs a random integer, according to a multinomial
# distribution specified by probs.
def rand_multinomial(probs):
    # Make sure probs sum to 1
    assert(abs(sum(probs) - 1.0) < 1e-5)
    rand = random.random()
    for index, prob in enumerate(probs):
        if rand < prob:
            return index
        else:
            rand -= prob
    return 0

# Outputs a random key, according to a (key,prob)
# iterator. For a probability dictionary
# d = {"A": 0.9, "C": 0.1}
# call using rand_multinomial_iter(d.items())
def rand_multinomial_iter(iterator):
    rand = random.random()
    for key, prob in iterator:
        if rand < prob:
            return key
        else:
            rand -= prob
    return 0

def printMatrix(row,col,grid): 
    for x in range(row):
        for y in range(col):
            print(grid[x][y],end=',')
            
        print("\n")
#Finding the max given t1 and t1_state + t2 and t2_state
def maxN(t1,t1_state,t2,t2_state):
    if(t1>t2):
        return t1,t1_state
    else:
        return t2,t2_state
#Function to create Matrix for Viterbi and Backtracking       
def matrix(row,col,ini):
    row1=[]
    grid1=[]
    b=row
    for x in range(row):
        for y in range(col):
            row1.append(ini)
        grid1.append(row1)
        row1=[]
    return grid1

def addValue(row,col,grid,val):
    grid[row][col]=val

def findValue(row,col,grid):
    return grid[row][col]

class HMM():

    def __init__(self):
        self.num_states = 2
        self.prior = [0.5, 0.5]
        self.transition = [[0.999, 0.001], [0.01, 0.99]]
        self.emission = [{"A": 0.291, "T": 0.291, "C": 0.209, "G": 0.209},
                         {"A": 0.169, "T": 0.169, "C": 0.331, "G": 0.331}]

    # Generates a sequence of states and characters from
    # the HMM model.
    # - length: Length of output sequence
    def sample(self, length):
        sequence = []
        states = []
        rand = random.random()
        cur_state = rand_multinomial(self.prior)
        for i in range(length):
            states.append(cur_state)
            char = rand_multinomial_iter(self.emission[cur_state].items())
            sequence.append(char)
            cur_state = rand_multinomial(self.transition[cur_state])
        return sequence, states

    # Generates a emission sequence given a sequence of states
    def generate_sequence(self, states):
        sequence = []
        for state in states:
            char = rand_multinomial_iter(self.emission[state].items())
            sequence.append(char)
        return sequence

    # Computes the (natural) log probability of sequence given a sequence of states.
    def logprob(self, sequence, states):
        #Initialization Step
        b=self.emission[0] #State 0 A/T and C/G
        c=self.emission[1] #State 1 A/T and C/G
        t=self.transition #Transition Probability
        x=t[0] #Transition 0/0 and 0/1
        x2=t[1] #Transition 1/0 and 1/1
        viterbi=matrix(self.num_states,len(sequence),0)
        #backpointer=matrix(self.num_states,len(sequence),-1)
        for state in range(self.num_states):    
            if (state==0):
                d=sequence[0]
                x1=math.log(self.prior[0])+math.log(b[d])
                addValue(state,0,viterbi,x1)
                #addValue(state,0,backpointer,-1)
            if (state==1):
                d=sequence[0]
                x1=math.log(self.prior[0])+math.log(c[d])
                addValue(state,0,viterbi,x1)
                #addValue(state,0,backpointer,-1)
        #Recursion Step
        for index in range(1,len(sequence)): 
            for state in range(self.num_states):
                if(state==0):
                    f=sequence[index]
                    t1=findValue(state,index-1,viterbi)+(math.log(b[f]))+(math.log(x[0]))
                    t2=findValue(state+1,index-1,viterbi)+(math.log(b[f]))+(math.log(x2[0]))
                    u,s1=maxN(t1,0,t2,1) #Return Max +State
                    addValue(state,index,viterbi,u)
                    #addValue(state,index,backpointer,s1)
                if(state==1):
                    f=sequence[index] 
                    t1=+findValue(state-1,index-1,viterbi) +(math.log(c[f]))+(math.log(x[1])) 
                    t2=findValue(state,index-1,viterbi)+(math.log(c[f]))+(math.log(x2[1]))
                    u,s1=maxN(t1,0,t2,1) #Return Max +State
                    addValue(state,index,viterbi,u)
                    #addValue(state,index,backpointer,s1)
        n1=viterbi[0][len(sequence)-1] #State 0 last value in matrix
        n2=viterbi[1][len(sequence)-1] #State 1 last value in matrix
        m,n=maxN(n1,0,n2,1)  #Taking the maximum between the last two state numbers     
        return m #Returning the higher probability
    # End your code
        ###########################################
    # Outputs the most likely sequence of states given an emission sequence
    # - sequence: String with characters [A,C,T,G]
    # return: list of state indices, e.g. [0,0,0,1,1,0,0,...]

    def viterbi(self, sequence):
        #Initialization Step
        b=self.emission[0] #State 0 A/T and C/G
        c=self.emission[1] #State 1 A/T and C/G
        t=self.transition #Transition Probability
        x=t[0] #Transition 0/0 and 0/1
        x2=t[1] #Transition 1/0 and 1/1
        viterbi=matrix(self.num_states,len(sequence),0)
        backpointer=matrix(self.num_states,len(sequence),-1)
        for state in range(self.num_states):    
            if (state==0):
                d=sequence[0]
                x1=math.log(self.prior[0])+math.log(b[d])
                addValue(state,0,viterbi,x1)
                addValue(state,0,backpointer,-1)
            if (state==1):
                d=sequence[0]
                x1=math.log(self.prior[0])+math.log(c[d])
                addValue(state,0,viterbi,x1)
                addValue(state,0,backpointer,-1)
        #Recursion Step
        for index in range(1,len(sequence)): 
            for state in range(self.num_states):
                if(state==0):
                    f=sequence[index]
                    t1=findValue(state,index-1,viterbi)+(math.log(b[f]))+(math.log(x[0]))
                    t2=findValue(state+1,index-1,viterbi)+(math.log(b[f]))+(math.log(x2[0]))
                    u,s1=maxN(t1,0,t2,1) #Return Max +State
                    addValue(state,index,viterbi,u)
                    addValue(state,index,backpointer,s1)
                if(state==1):
                    f=sequence[index] 
                    t1=findValue(state-1,index-1,viterbi)+(math.log(c[f]))+(math.log(x[1]))
                    t2=findValue(state,index-1,viterbi)+(math.log(c[f]))+(math.log(x2[1]))
                    u,s1=maxN(t1,0,t2,1) #Return Max +State
                    addValue(state,index,viterbi,u)
                    addValue(state,index,backpointer,s1)
        #Finding the Maximum Number between the last two rows
        n1=viterbi[0][len(sequence)-1]
        n2=viterbi[1][len(sequence)-1]
        m,n=maxN(n1,0,n2,1)
        sequence1=[]
        #Backtracking takes place here for the first values
        #These are for the first values of the array in prev matrix
        #N represents the state here
        if (n==0): #If state is 0 
            t1=backpointer[0][(len(sequence))-1]
            if(t1==0): 
                sequence1.append(t1) #APPEND 0 to the sequence
            else: #If the value is 1 in the prev matrix
                sequence1.append(0) #We are appending the state
                sequence1.append(1) #We append the value of t1 which is 1
                n=1 #We update that we need to look at state 1 now 
        else: # If we are in state 1
            t1=backpointer[1][(len(sequence))-1]
            if(t1==1):
                sequence1.append(t1)
            else:#variable is 0 but we are in state 1 area
                sequence1.append(1) #We add the state first
                sequence1.append(t1)#We add the value then which is t1
                n=1
        #Performing backtracking here
        x=len(sequence)-2 
        while x>=0:
            if(n==0):#The variable is the state either 0/1
                variable=backpointer[0][x]
                if (variable==0):
                    sequence1.append(variable)
                else:
                    sequence1.append(0)
                    n=1 #We look at state 1 now the n represents which state value to look at next
            else: #If n==1 as n can only be 1 or 0 
                variable=backpointer[1][x]
                if(variable==1):
                    sequence1.append(variable)
                elif(variable==-1):
                    break
                else:#variable is 0 but in state 1 area
                    sequence1.append(1)
                    n=0
            x=x-1
        sequence1.reverse()
        return sequence1
def read_sequence(filename):
    with open(filename, "r") as f:
        return f.read().strip()

def write_sequence(filename, sequence):
    with open(filename, "w") as f:
        f.write("".join(sequence))

def write_output(filename, logprob, states):
    with open(filename, "w") as f:
        f.write(str(logprob))
        f.write("\n")
        for state in range(2):
            f.write(str(states.count(state)))
            f.write("\n")
        f.write("".join(map(str, states)))
        f.write("\n")

hmm = HMM()

##
##sequence = read_sequence("small.txt")
##viterbi = hmm.viterbi(sequence)
##logprob = hmm.logprob(sequence, viterbi)
##write_output("my_small_output.txt", logprob,viterbi)
####
##
##
sequence = read_sequence("ecoli.txt")
viterbi = hmm.viterbi(sequence)
logprob = hmm.logprob(sequence, viterbi)
write_output("ecoli_output.txt", logprob, viterbi)



