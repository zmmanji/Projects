import random
import math
import time
import copy

#ZEESHAAN MEHBOOB MANJI
#301228629



#####################################################
#####################################################
# Please enter the number of hours you spent on this
# assignment here
num_hours_i_spent_on_this_assignment = 40
#####################################################
#####################################################
## I thought of my weights in terms of the diagram used in class this helped me understand this assignment ( See figure below to see how "my" neuro network format looks ) I have used this weight format for my neuro network
## My weights are from W(1,3) W(1,4) w(2,3) w(2,4) w(3,5) w(4,5) AND the bias weights W(0,5) W(0,3) W(0,4)
##          [ a5 ]       Ouput Layer
#           /     \
##        [a3]   [a4]  Hidden Layer
##              
##       [a1]      [a2]    Input Layer
## The weights you see in my code comments are relating to this figure above :)


def logistic(x):
    return 1.0 / (1.0 + math.exp(-x))

def logistic_derivative(x):
    return logistic(x) * (1-logistic(x))

class Neuron:
    def __init__(self, attribute_weights, neuron_weights, bias_weight):
        # neuron.attribute_weights[i] = Weight of input attribute i as input to this neuron
        self.attribute_weights = attribute_weights
        # neuron.neuron_weights[i] = Weight of neuron j as input to this neuron
        self.neuron_weights = neuron_weights
        self.bias_weight = bias_weight

class ANN:
    def __init__(self, num_attributes, neurons):
        # Number of input attributes.
        self.num_attributes = num_attributes
        # Number of neurons. neurons[-1] is the output neuron.
        self.neurons = neurons
        for neuron_index, neuron in enumerate(self.neurons):
            for input_neuron, input_weight in neuron.neuron_weights.items():
                assert(input_neuron < neuron_index)
    #Returns list of In[0]=In_3 In[1]=In_4 In[2]=In_5
    #Returns IN FOR EACH EXAMPLE OF ATTRIBUTES ( ONLY ONE PAIR OF ATTRIBUTE)
    def IN_Calculate(self,attributes):
        total=0
        output=[]#Storing the output of a3 and a4
        final=[] #Storing the Final Value A5 in this list
        IN=[] #Storing the IN values in order of IN[0]=IN_3 IN[1]=IN_4 IN[2]=IN_5
        for neuron_index,neuron in enumerate(self.neurons):
            for input_neuron,input_weight in neuron.attribute_weights.items():
                if (neuron_index==0)&(input_neuron==0): #Weights from a1 to a3
                    val1=input_weight*(attributes[0])
                    bias1=neuron.bias_weight
                elif(neuron_index==0)&(input_neuron==1): #Weights from a1 to a4 
                    val2=input_weight*attributes[0]                             
                elif(neuron_index==1)& (input_neuron==0): #Weights from a2 to a3 
                    val1=val1+((input_weight)*(attributes[1]))-(bias1)
                    IN.append(val1) #Updating the Value for IN_3
                    y=logistic(val1)
                    output.append(y)#Updating the Value for a_3
                elif(neuron_index==1)&(input_neuron==1):#Weights from a2 to a4
                    bias2=neuron.bias_weight
                    val2=(val2+((input_weight*attributes[1])))-(bias2)
                    IN.append(val2)
                    y=logistic(val2)
                    output.append(y)#Updating the Value for a_4
            if(neuron_index==2): #Updating the output value for a5 in the final array
                for input_neuron, input_weight in neuron.neuron_weights.items():
                    if(input_neuron==0): #From a3 to a5
                        firstval=input_weight*output[0]
                    elif(input_neuron==1): #From a4 to a5
                        secondval=input_weight*output[1]
                thirdval=neuron.bias_weight #Bias Weight
                total=firstval+secondval-thirdval
                IN.append(total) #Updating In_5 
                y=logistic(total)
                final.append(y) #Updating a5
             
        return IN #IN[0]=in_3  In[1]=in_4 In[2]=in_4
    # Calculates the output of the output neuron for given input attributes.
    def calculate(self, attributes):
        ###########################################
        total=0
        output=[]#Storing the output of a3 and a4
        final=[] #Storing the Value after putting it in the logistic function a_n=g(in_n)
        IN=[] #Storing the IN values in order of IN[0]=IN_3 IN[1]=IN_4 IN[2]=IN_5
        for neuron_index,neuron in enumerate(self.neurons):
            for input_neuron,input_weight in neuron.attribute_weights.items():
                if (neuron_index==0)&(input_neuron==0): 
                    val1=input_weight*(attributes[0])
                    bias1=neuron.bias_weight
                elif(neuron_index==0)&(input_neuron==1):
                    val2=input_weight*(attributes[0])                            
                elif(neuron_index==1)& (input_neuron==0):
                    val1=val1+(input_weight*(attributes[1]))-(bias1)
                    IN.append(val1)
                    y=logistic(val1)
                    output.append(y)
                elif(neuron_index==1)&(input_neuron==1):
                    bias2=neuron.bias_weight
                    val2=val2+(input_weight*(attributes[1]))-(bias2)
                    IN.append(val2)
                    y=logistic(val2)
                    output.append(y)
            if(neuron_index==2): #Updating the output value for a5 in the final array
                for input_neuron, input_weight in neuron.neuron_weights.items():
                    if(input_neuron==0): #From a3 to a5
                        firstval=input_weight*output[0]
                    elif(input_neuron==1): #From a4 to a5
                        secondval=input_weight*output[1]
                thirdval=neuron.bias_weight #Bias Weight
                total=firstval+secondval-thirdval
                IN.append(total) #Updating In_5 
                y=logistic(total)
                final.append(y) #Updating a5
                
        return final[0]  #Printing A5 
        # End your code
        ###########################################
    # Returns the squared error of a collection of examples:
    def squared_error(self, example_attributes, example_labels):
        error=0
        for index in range(len(example_labels)):
            new_output=self.calculate(example_attributes[index])
            y=example_labels[index]
            error=error+(y-new_output)**2
        error=error*0.5
        return error
 
    # Runs backpropagation on a single example in order to
    # update the network weights appropriately.
    def backpropagate_example(self, attributes, label, learning_rate=1.0):
        ###########################################
        #X REPRESENTS THE IN LIST FOR A_3 A_4 AND Y REPRESENTS THE SINGLE OUTPUT
        #PART 1 updating the DELTA
        #X[0]=in_3,X[1]=in_4,X[2]=in_5
        y=self.calculate(attributes) #A5 output is in Y 
        x=self.IN_Calculate(attributes) 
        delta5=(label-y)*logistic_derivative(x[2])
        delta4=logistic_derivative(x[1])*(self.neurons[2].neuron_weights[1])*delta5
        delta3=logistic_derivative(x[0])*(self.neurons[2].neuron_weights[0])*delta5

        #PART 2 Updating the Weights (3,5) and (4,5)
        self.neurons[2].neuron_weights[0]=self.neurons[2].neuron_weights[0]+learning_rate*logistic(x[0])*delta5
        self.neurons[2].neuron_weights[1]=self.neurons[2].neuron_weights[1]+learning_rate*logistic(x[1])*delta5
            
        #PART 2(B) Updating the weights of (1,3) and (1,4) and (2,3) and (2,4)
        self.neurons[0].attribute_weights[0]=(self.neurons[0].attribute_weights[0])+learning_rate*attributes[0]*delta3
        self.neurons[0].attribute_weights[1]=(self.neurons[0].attribute_weights[1])+learning_rate*attributes[0]*delta4
        self.neurons[1].attribute_weights[0]=(self.neurons[1].attribute_weights[0])+learning_rate*attributes[1]*delta3
        self.neurons[1].attribute_weights[1]=(self.neurons[1].attribute_weights[1])+learning_rate*attributes[1]*delta4

        ##Updating your bias weights
        self.neurons[2].bias_weight=(self.neurons[2].bias_weight)+learning_rate*(-1)*delta5
        self.neurons[1].bias_weight=(self.neurons[1].bias_weight)+learning_rate*(-1)*delta4
        self.neurons[0].bias_weight=(self.neurons[0].bias_weight)+learning_rate*(-1)*delta3


   #Print the Weights passing after passing in an object
    def printWeights(self):
        for neuron_index, neuron in enumerate(self.neurons):
            for input_neuron,input_weight in neuron.neuron_weights.items():
                print(neuron_index, input_neuron, input_weight,neuron.bias_weight)
            for input_neuron,input_weight in neuron.attribute_weights.items():
                print(neuron_index, input_neuron, input_weight,neuron.bias_weight)
       
    #ASSUMING YOUR TESTING YOUR DATA WITH ALL THE FOUR ATTRIBUTES AND FOUR LABELS       
    def learn(self, example_attributes, example_labels, learning_rate=10.0, num_epochs=100):
        for i in range(num_epochs):
            for index in range(len(example_attributes)):
                self.backpropagate_example(example_attributes[index],example_labels[index],learning_rate) 
   
example_attributes = [ [0,0],[0,1],[1,0],[1,1]]
example_labels = [0,1,1,0]

def random_ann(num_attributes=2, num_hidden=2):
    neurons = []
    # hidden neurons
    for i in range(num_hidden):
        attribute_weights = {attribute_index: random.uniform(-1.0,1.0) for attribute_index in range(num_attributes)}
        bias_weight = random.uniform(-1.0,1.0)
        neurons.append(Neuron(attribute_weights,{},bias_weight))
    # output neuron
    neuron_weights = {input_neuron: random.uniform(-1.0,1.0) for input_neuron in range(num_hidden)}
    bias_weight = random.uniform(-1.0,1.0)
    neurons.append(Neuron({},neuron_weights,bias_weight))
    ann = ANN(num_attributes, neurons)
    return ann
           
best_ann = None
best_error = float("inf")
for instance_index in range(10):
    ann = random_ann()
    ann.learn(example_attributes, example_labels, learning_rate=10.0, num_epochs=10000)
    error = ann.squared_error(example_attributes, example_labels)
    if error < best_error:
        best_error = error
        best_ann = ann
print(best_error,"This is the Best Error")



#####################################################
#####################################################
# Please hard-code your learned ANN here:
learned_ann = random_ann()
learned_ann.neurons[0].attribute_weights[0] = -8.130716633379427
learned_ann.neurons[0].attribute_weights[1] = 7.792986499552811
learned_ann.neurons[0].bias_weight =4.009942139543631
learned_ann.neurons[1].attribute_weights[0] = 7.559257466059981
learned_ann.neurons[1].attribute_weights[1] = -9.790316482507563
learned_ann.neurons[1].bias_weight =4.020430922497502
learned_ann.neurons[2].neuron_weights[0] = 12.012021907279612
learned_ann.neurons[2].neuron_weights[1] = 11.955005053337585
learned_ann.neurons[2].bias_weight= 5.9655644281707065
error=learned_ann.squared_error(example_attributes,example_labels)

# Enter the squared error of this network here:
final_squared_error = 2.283508301454182e-05
#####################################################
#####################################################


