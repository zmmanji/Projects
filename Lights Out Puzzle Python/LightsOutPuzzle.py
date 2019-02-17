
from random import randint
from Queue import PriorityQueue
from Queue import Queue
from sets import Set
import math
from copy import deepcopy
def create_puzzle(rows,cols):
    grid=[]
    row=[]
    for i in range(rows):
        for j in range(cols):
            #a=randint(0,1)
            row.append(0)
        grid.append(row)
        row=[]
    return grid

def print_puzzle(grid,rows,cols):
    i=0
    j=0
    while i<rows:
        while j<cols:
            print grid[i][j], "   ",
            j=j+1
        j=0
        i=i+1
        print
        
    

def is_solved(puzzle):
    state=True
    b=len(puzzle) # the number of rows
    c=len(puzzle[0]) #the size columns
    for x in range(b):
        for y in range(c):
            if (puzzle[x][y]==1):
                state=False
    return state

def scramble(puzzle):
    b=len(puzzle)#the number of rows
    h=len(puzzle[0])# the size of the columns
    x=0
    c=0
    for x in range(b):
        for c in range(h):
            u=randint(0,1) #need to make this 50-50
            if (u==1):
                perform_move(puzzle,x,c)
    return puzzle
def solve(puzzle):
    status=False
    b=scramble(puzzle)
    c=is_solved(b)
    if(c==True):
        print("Completed")
    else:
        print("Not solvable")
        

            

def checkright(puzzle,row,col):
    c=len(puzzle[0])-1  # Function tested and working
    test=col+1
    if (test>c):
        return False
    else:
        return True

def checkup(puzzle,row,col):
    c=len(puzzle) # Function tested and working
    test=row-1
    if (test<0):
        return False
    else:
        return True
def checkleft(puzzle,row,col):
    c=len(puzzle[0])-1   #Function tested and working
    test=col-1
    if(test<0):
        return False
    else:
        return True
def checkdown(puzzle,row,col):
    c=len(puzzle)-1     #Function tested and working 
    test=row+1
    if (test>c):
        return False
    else:
        return True



def heuristic(puzzle): # My Heuristic is here!!
    b=len(puzzle) #the Length of the row
    c=len(puzzle[0]) #The length of the column
    count=0
    for i in range(b):
        for j in range(c):
            if(puzzle[i][j]==1):
                count=count+1
    
    return count/5.0


def copypuzzle(puzzle):
    
    return deepcopy(puzzle)


def perform_move(puzzle,row,col):
    b=len(puzzle) # Length of Column
    #print (b)
    c=len(puzzle[0]) # Length of Row
    if (puzzle[row][col]==1):
        puzzle[row][col]=0
        if (checkleft(puzzle,row,col)==True):
            if (puzzle[row][col-1]==1):
                puzzle[row][col-1]=0
            else:
                puzzle[row][col-1]=1
        if (checkright(puzzle,row,col)==True):
            if (puzzle[row][col+1]==1):
                puzzle[row][col+1]=0
            else:
                puzzle[row][col+1]=1
        if(checkup(puzzle,row,col)==True):
            if(puzzle[row-1][col]==1):
                puzzle[row-1][col]=0
            else:
                puzzle[row-1][col]=1
        if(checkdown(puzzle,row,col)==True):
            if(puzzle[row+1][col]==1):
                puzzle[row+1][col]=0
            else:
                puzzle[row+1][col]=1
    else:
        puzzle[row][col]=1
        if (checkleft(puzzle,row,col)==True):
            if (puzzle[row][col-1]==1):
                puzzle[row][col-1]=0
            else:
                puzzle[row][col-1]=1
        if (checkright(puzzle,row,col)==True):
            if (puzzle[row][col+1]==1):
                puzzle[row][col+1]=0
            else:
                puzzle[row][col+1]=1
        if(checkup(puzzle,row,col)==True):
            if(puzzle[row-1][col]==1):
                puzzle[row-1][col]=0
            else:
                puzzle[row-1][col]=1
        if(checkdown(puzzle,row,col)==True):
            if(puzzle[row+1][col]==1):
                puzzle[row+1][col]=0
            else:
                puzzle[row+1][col]=1


def astaralgorithm(puzzle,rows,col):
    if (is_solved(puzzle)):
        print("Puzzle is solved")
        return 0,Set()
    count=0
    queue=PriorityQueue() #contains the board states
    queue.put((heuristic(puzzle),puzzle,Set())) # each board state and set of moves
    completedpuzzle=Set() # puzzles already seen
    while not queue.empty(): 
        h,p,moves=queue.get()
        completedpuzzle.add(str(p))
        #print moves
        for a in range(rows):
            for b in range(col):
                if (a,b) not in moves:
                    temp1=copypuzzle(p)
                    perform_move(temp1,a,b)
                    count=count+1
                    if (str(temp1) not in completedpuzzle):
                        if (is_solved(temp1)):
                            moves.add((a,b))
                            #print moves
                            #print ("Found Solution")
                            return count, moves
                        else:
                            temp3=deepcopy(moves)
                            temp3.add((a,b))
                            queue.put((heuristic(temp1), temp1,temp3))
                            completedpuzzle.add(str(temp1))
              
def updated_dfs(puzzle,rows,col):
    count=0
    import time
    start_time = time.time()
    if (is_solved(puzzle)):
        print("Puzzle is solved")
        return 0,Set()
    stack=[] #contains the board states
    stack.append((puzzle,Set())) # each board state and set of moves
    completedpuzzle=Set() # puzzles already seen
    while len(stack)>0: 
        p,moves=stack.pop()
        completedpuzzle.add(str(p))
        #print moves
        for a in range(rows):
            for b in range(col):
                if (a,b) not in moves:
                    temp1=copypuzzle(p)
                    perform_move(temp1,a,b)
                    count=count+1
                    if (str(temp1) not in completedpuzzle):
                        if (is_solved(temp1)):
                            moves.add((a,b))
                            #print temp1
                            #print moves
                            #print ("Found Solution")
                            end_time=time.time()
                            diff=end_time-start_time
                            #print("Time to run Algorithm",diff)
                            return count,moves
                        else:
                            temp3=deepcopy(moves)
                            temp3.add((a,b))
                            stack.append((temp1,temp3))
                            completedpuzzle.add(str(temp1))

def updated_bfs(puzzle,rows,col):
    count=0
    if (is_solved(puzzle)):
        print("Puzzle is solved")
        return 0,Set()
    queue=Queue() #contains the board states
    queue.put((puzzle,Set())) # each board state and set of moves
    completedpuzzle=Set() # puzzles already seen
    while not queue.empty(): 
        p,moves=queue.get()
        completedpuzzle.add(str(p))
        #print moves
        for a in range(rows):
            for b in range(col):
                if (a,b) not in moves:
                    temp1=copypuzzle(p)
                    perform_move(temp1,a,b)
                    count=count+1
                    if (str(temp1) not in completedpuzzle):
                        if (is_solved(temp1)):
                            #print moves
                            #print ("Found Solution")
                            return count,moves
                        else:
                            temp3=deepcopy(moves)
                            temp3.add((a,b))
                            queue.put((temp1,temp3))
                            completedpuzzle.add(str(temp1))


def test1():
    print("Results for A*")
    import time
    start_time = time.time()
    totalLength=0
    
    totalsteps=0

    for a in range(100):
        c=create_puzzle(4,4)
        scramble(c)
        b,c=astaralgorithm(c,4,4)
        totalsteps=totalsteps+b
        totalLength=totalLength+len(c)
    end_time=time.time()

    diff=end_time-start_time

    print "The total steps", totalsteps
    print "The total length",totalLength

    print "The time", diff


def test2():
    print("__________________________________________")
    print("Results for BFS")
    import time
    start_time = time.time()
    
    totalsteps=0
    totalLength=0

    for a in range(100):
        c=create_puzzle(4,4)
        scramble(c)
        b,c=updated_bfs(c,4,4)
        totalsteps=totalsteps+b
        totalLength=totalLength+len(c)
    end_time=time.time()

    diff=end_time-start_time

    print "The total steps", totalsteps
    print "The total length",totalLength

    print "The time", diff
   

def test3():
    print("__________________________________________")
    print("Results for DFS")
    import time
    start_time = time.time()
    
    totalsteps=0
    totalLength=0

    for a in range(100):
        c=create_puzzle(4,4)
        scramble(c)
        b,c=updated_dfs(c,4,4)
        totalsteps=totalsteps+b
        totalLength=totalLength+len(c)
    end_time=time.time()

    diff=end_time-start_time

    print "The total steps", totalsteps
    print "The total length",totalLength

    print "The time", diff
def test4():
    c=create_puzzle(4,4)
    scramble(c)
    print(c)
    b,c=updated_dfs(c,4,4)
    print "The number of moves  ",b
    print "What are the steps  ", c

def test5():   #THIS TESTS ALL PUZZLE FOR 4X4 MATRICES
    print "FOR BFS SOLVING"
    c=create_puzzle(4,4)
    scramble(c)
    print "This is How the Puzzle looks"
    print_puzzle(c,4,4)
    b,d=updated_bfs(c,4,4)
    print " This are the steps required to solve the puzzle"
    print d
    print"_________________________________________________"
    print "FOR DFS SOLVING"
    c=create_puzzle(4,4)
    scramble(c)
    print "This is How the Puzzle looks"
    print_puzzle(c,4,4)
    b,d=updated_dfs(c,4,4)
    scramble(c)
    print " This are the steps required to solve the puzzle"
    print d
    print"________________________________________________"
    print "FOR A* SOLVING"
    c=create_puzzle(4,4)
    scramble(c)
    print "This is How the Puzzle looks"
    print_puzzle(c,4,4)
    b,d=astaralgorithm(c,4,4)
    print " This are the steps required to solve the puzzle"
    print d
    print"________________________________________________"
    
## IMPORTANT##
#MY DFS, BFS, AND ASTAR RETURN 2 VALUES IN EVERY FUNCTION WHICH ONE VALUE IS THE NUMBER OF TIMES PERFORM_MOVE IS CALLED AND THE SET OF MOVES 
    


test5()      
test1()
test2()
test3()

