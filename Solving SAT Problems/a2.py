import random
import time
import copy
##ZEESHAAN MANJI 301228629
#####################################################
#####################################################
# Please enter the number of hours you spent on this
# assignment here
num_hours_i_spent_on_this_assignment = 40
#####################################################

#####################################################
#####################################################


# A clause consists of a set of symbols, each of which is negated
# or not. A clause where
# clause.symbols = {"a": 1, "b": -1, "c": 1}
# corresponds to the statement: a OR (NOT b) OR c .
class Clause:
    def __init__(self):
        pass

    def from_str(self, s):
        s = s.split()
        self.symbols = {}
        for token in s:
            if token[0] == "-":
                sign = -1
                symbol = token[1:]
            else:
                sign = 1
                symbol = token
            self.symbols[symbol] = sign

    def __str__(self):
        tokens = []
        for symbol,sign in self.symbols.items():
            token = ""
            if sign == -1:
                token += "-"
            token += symbol
            tokens.append(token)

        return " ".join(tokens)

# A SAT instance consists of a set of CNF clauses. All clauses
# must be satisfied in order for the SAT instance to be satisfied.
class SatInstance:
    def __init__(self):
        pass

    def from_str(self, s):
        self.symbols = set()
        self.clauses = []
        for line in s.splitlines():
            clause = Clause()
            clause.from_str(line)
            self.clauses.append(clause)
            for symbol in clause.symbols:
                self.symbols.add(symbol)
        self.symbols = sorted(self.symbols)
        

    def __str__(self):
        s = ""
        for clause in self.clauses:
            s += str(clause)
            s += "\n"

        return s

    # Takes as input an assignment to symbols and returns True or
    # False depending on whether the instance is satisfied.
    # Input:
    # - assignment: Dictionary of the format {symbol: sign}, where sign
    #       is either 1 or -1.
    # Output: True or False

    
        
    
    def is_satisfied(self, assignment): #Checking for satisfiability with the instance
        ###########################################
        for clause in self.clauses:
            t=clause.symbols
            for symbol, sign in clause.symbols.items():
                found  = False
                if (symbol in assignment):
                   if(assignment[symbol]==1) and (sign==1):
                       found = True
                       break
                   elif(assignment[symbol]==-1)and(sign==-1):
                       found = True
                       break
            if not found:
                return False                             
        return True                                        
        # End your code
        ###########################################

# Finds a satisfying assignment to a SAT instance,
# using the DPLL algorithm.
# Input: SAT instance
# Output: Dictionary of the format {symbol: sign}, where sign
#         is either 1 or -1.


def unit_clause(instance,clauseRemain, symbols):
   
    count=0
    for t in clauseRemain: #going through all the clauses which are not satisfied
        clause=instance.clauses[t]
        for a,sign in clause.symbols.items(): #checking the if the symbols is part of our symbols 
            if a not in symbols:
                continue
            temp1=a
            temp2=sign
            count=count+1
        if (count==1):
            return (temp1,temp2) # A unit clause is one that has only 1 symbol remaining in the clause
            count=0
        else:
            count=0
    return False,0
   

def delete_variable_list(L,a):
    X=[]
    size=copy.deepcopy(len(L))
    i=0
    for i in range(size):
        #print(i,size)
        if (L[i]!=a):
            X.append(L[i])
    return X


def pure_symbols(instance,clauseRemain,symbols):
    L=[] #To store all symbols
    S=[] # To store all the signs of symbols
    deleted=[]
    for i in clauseRemain: #Checking for clauses which are not satisfied yet
        clause=instance.clauses[i]
        t=clause.symbols
        for symbol,sign in t.items():
            a=symbol
            b=sign
            if a not in symbols:
                continue
            if (a not in L)& (a not in deleted): #It makes sure we dont add the symbol again
                    L.append(a)
                    S.append(b)
            elif( a in L):
                x1=L.index(a)
                if(b!=S[x1]):
                    deleted.append(a)
                    L=delete_variable_list(L,a)
                    del S[x1]
    #print(L, "These are the pure")
    return L,S
        
            
def deleteLiteral(instance,literal): #Removing a literal from each of the clauses
    for clauses in instance.clauses:
        t=clauses.symbols
        f=t.items()
        for symbol,sign in list(t.items()):
            if (symbol==literal):
                
                del t[symbol]
                
    return instance

def symbols_create(instance): #The creation of a symbol list called S
    S=[]
    for clauses in instance.clauses:
        x=clauses.symbols
        for symbol,sign in x.items():
            if( symbol not in S):
                S.append(symbol)
    return S

def First(symbols):
    if (len(symbols)!=0):
        return symbols[0]


def Rest(symbols):
    if (len(symbols)!=0):
        rest=symbols[1:]
    return rest

def Extend(clause,sym,val):
    clause[sym]=val
    return clause

def delete_clause(instance,literal):
    print("hELLO")
    x1=len(instance.clauses)
    for clauses in instance.clauses:
        t=clauses.symbols
        f=t.items()
        for symbol,sign in list(t.items()):
            if (symbol==literal):
                t.clear()
    x2=len(instance.clauses)
    #print(x1,x2,"This is the value of len")
    return instance
    


def DPLL(instance,symbols,model):
    #print(model)
    if(len(symbols)==0):
        return instance.is_satisfied(model)
    symbols = symbols.copy()
    clauseRemain=[]
    #This part below just checks which of the clauses are remaining to be satisfied
    #It stored the indexes in clauseRemain[]
    for i in range(len(instance.clauses)):
        found=-1
        for a,b in instance.clauses[i].symbols.items():
            if a in symbols:
                found=0
            elif model[a]==b:
                found=1
                break
        if found==-1:
            return False
        elif found==0:
            clauseRemain.append(i)
    #If no clauses are remaining this means we have satisfied 
    if(len(clauseRemain)==0):
            return True
    #My pure symbol returns a list of symbols corresponding to their sign in the array a
    pure,a=pure_symbols(instance,clauseRemain,symbols)
    if(len(pure)!=0):
        for i in range(len(pure)):
            model[pure[i]]=a[i]
            symbols.remove(pure[i])
    #Checking for a unit clause in our instance
    p,value=unit_clause(instance,clauseRemain,symbols)
    if p:
        model[p]=value
        symbols.remove(p)
    #Checking if we have either pure clauses or unit clauses
    if len(pure)>0 or p:
        return DPLL(instance, symbols, model)
    #This is where the main recursion takes place
    if(len(symbols)>0):
        x1=First(symbols)
        r=Rest(symbols)
        return DPLL(instance,r,Extend(model,x1,1)) or DPLL(instance,r,Extend(model,x1,-1))

                                 
def solve_dpll(instance):
    ###########################################
    #IF YOU WANT TO  SEE THE RUNNING TIME UNCOMMENT THE LINE BEFORE RETURN ASSIGNMENT
    t0 = time.time()
    assignment={}
    b=symbols_create(instance)
    d=DPLL(instance,b,assignment)
    t1=time.time()
    t2=t1-t0
    #print("Time taken for instance (s) ",t2)
    return assignment
    # Start your code

    # End your code
    ###########################################

with open("big_instances.txt", "r") as input_file:
    instance_strs = input_file.read()

instance_strs = instance_strs.split("\n\n")

with open("big_assignments_inferred.txt", "w") as output_file:
    for instance_str in instance_strs:
        if instance_str.strip() == "":
            continue
        instance = SatInstance()

        instance.from_str(instance_str)
        assignment = solve_dpll(instance)
        for symbol_index, (symbol,sign) in enumerate(assignment.items()):
            if symbol_index != 0:
                output_file.write(" ")
            token = ""
            if sign == -1:
                token += "-"
            token += symbol
            output_file.write(token)
        output_file.write("\n")




















