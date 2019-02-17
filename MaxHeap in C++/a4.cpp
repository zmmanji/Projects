//
//  main.cpp
//  Assignment4
//
//  Created by Zeeshaan Manji on 4/3/15.
//  Copyright (c) 2015 Zeeshaan Manji. All rights reserved.
//

#include <iostream>
using namespace std;
class Heap{
    
public:
    // Constructors and Destructor
    
    // New empty Heap with default capacity.
    Heap();
    
    // New empty Heap with capacity c.
    Heap(long int c);
    
    // New Heap with size s, consisting of pairs <Pi,Ei> where,
    // for 0 <= i < s, Pi is Priorities[i] and Ei is value Elements[i].
    // Capacity is s + c, where c is the "spare capacity" argument.
    // Requires: Priorities and Elements are of size at least s.
    Heap( const int * Elements, long int s);
    
    // New Heap with combined contents the two Heap arguments.
    // Size of the new Heap is the sum of the sizes of argument Heaps.
    // Capacity of the new Heap is its size plus the "spare capacity" c.
    Heap( const Heap & Heap1, const Heap & Heap2,  long int c );
    
    // Destructor.
    ~Heap();
    // Accessors
    bool empty() const {return hSize == 0;}; // True iff Heap is empty.
    int size() const { return hSize ;} ; // Current size of Heap.
    int capacity() const { return hCapacity ;} ; // Current capacity.
    int peekMax() const { return A[0].element ;} // Peek at minimum element.
    void compare( const Heap & Heap2);
    bool search  (long int i) const;
    void print();
    int extractMax(); // Remove and return the highest priority element.
    //int peekMinPriority() const { return A[0].priority ;} // Peek at priority of min element.
    
    // Modifiers
    void insert( long int element ); // Insert the pair <element,priority>.
    bool search2() const;
   
    
    
private:
    class Pair{
    public:
        long  element ;
        int priority ;
    };
    
    Pair* A ; // Array containing heap contents.
    long int hCapacity ; // Max number of elements (= size of A).
    long int hSize ; // Current number of elements.
    
    // Repairs ordering invariant after adding leaf at A[i].
    void trickleUp(int i);
    
    // Repairs ordering invariant for sub-tree rooted at index i,
    //   when A[i] may be smaller than one of its children.
    void trickleDown(int i);
    
    // Establishes ordering invariant for entire array contents.
    void heapify(); //(Same as "make_heap" in lectures.)
    
    // Useful for implementing trickle up and down
    void swap(long int i,long int j);
    
    
};

Heap::Heap(){
    hCapacity = 10 ;
    A = new Pair[hCapacity];
    hSize = 0 ;
}

Heap::Heap(long int c){ // New empty Heap with capacity c.// Complete this.
    hCapacity=c;
    A=new Pair[hCapacity];
    hSize=0;
    
    
    
}
int Heap::extractMax()
{
    swap(0,hSize-1);
    hSize--;
    trickleDown(0);
    return A[0].element;
    
}

// New Heap with capacity c+s, with s elements, consisting of pairs <Pi,Vi> where
//  Pi is Priorities[i], Ei is value Elements[i], for 0 <= i < s.
Heap::Heap( const int * Elements,long int s){
    // Complete this.
    hCapacity=s;
    A=new Pair[hCapacity];
    for (int i=0;i<s;i++)
    {
        int a=Elements[i];
        insert(a);
        
    }
    
    
    
    
}
void Heap::print()
{
    while(!empty())
    {
        cout<<peekMax()<<endl;
        extractMax();
    }
}

// New Heap with combined contents and of the two given heaps.
Heap::Heap( const Heap & Heap1, const Heap & Heap2, long int c )
{
    
    hSize=0;
    hCapacity = Heap1.hCapacity + Heap2.hCapacity + c ;
    A=new Pair[hCapacity];
    
    for(int i=0; i<Heap1.hSize;i++)
    {
        insert(Heap1.A[i].element);
        
    }
    for(int i=0; i<Heap2.hSize;i++)
    {
        insert(Heap2.A[i].element);
    }
    //heapify();
    
}




// Destructor
Heap::~Heap(){
    delete[] A;
}

// Modifiers

void Heap::insert(long int element)
{
    if (hSize<hCapacity)
    {
        
        A[hSize].element = element;
        trickleUp(hSize);
        hSize ++;
    }

    
    
}
bool Heap::search2() const
{
    bool status=false;
    
    for (int i=0;i<=hSize;i++)
    {
        cout<<A[i].element<<endl;
        /*if (A[i].element==x)
        {
            
            status=true;
            return status;
        }*/
        
        
    }
    return status;
}
bool Heap::search(long int x) const
{
    bool status=false;
    
    for (int i=0;i<=hSize+1;i++)
    {
        if (A[i].element==x)
        {
            
            status=true;
            return status;
        }
        
        
    }
    return status;
}


// Repairs the heap ordering invariant after adding a new element.
// Initial call should be trickleUp(hSize-1).
void Heap::compare(const Heap &Heap2)
{
    bool output=false;
    bool found=false;
    if (!Heap2.search(peekMax()))
    {
        cout<<peekMax()<<endl;
    }
    else
    {
        while (!empty())
        {
            if (!Heap2.search(peekMax()))
            {
                //Heap2.search2();
                output=true;
                cout<<peekMax()<<endl;
                break;
            }
            extractMax();
        }
        if (output==false)
        {
            cout<<"None"<<endl;
        }
    }
    
    
}

void Heap::trickleUp(int i)
{
    if (i>0)
    {
        if (A[i].element > A[((i-1)/2)].element)
        {
            swap(i,((i-1)/2));
            trickleUp((i-1)/2);
        }
    }
    
}
void Heap::swap(long  int i, long int j)
{
    Pair temp = A[i];
    A[i] = A[j];
    A[j] = temp ;
}

// Removes and returns the element with highest priority.
// (That is, the element associated with the minimum priority value.)
/*int Heap::extractMin()
{
    swap(0,hSize-1);
    hSize--;
    trickleDown(0);
    return A[0].element;
    
}*/
// Repairs the heap ordering invariant after replacing the root.
// Initial call by insert() is trickleDown(0).
// (trickleDown(i) performs the repair on the subtree rooted a A[i].)
// (heapify() calls trickleDown(i) for i from (hSize/2)-1 down to 0.)
void Heap::trickleDown(int i)
{
    
    int swap=(2*(i))+1;
    if ((2*(i))+1 < hSize)
    {
        if (((2*(i))+2 < hSize) && (A[(2*(i))+2].element > A[(2*(i))+1].element))// if right child is smaller than parent
        {
            swap=(2*(i))+2;// swap value becomes the right child
            
        }
        if (A[i].element < A[swap].element)
        {
            Pair temp = A[i];
            A[i] = A[swap];
            A[swap] = temp ;
            trickleDown(swap);
        }
    }
    
    
    
    
    
}

// Turns A[0] .. A[size-1] into a heap.
void Heap::heapify(){
    for( int i = (hSize/2)-1; i>=0 ; i-- ) trickleDown(i);
}



void Run( Heap& A1, Heap& A2)
{

    int count1=0;
    int count2=0;
    long int x;
    bool List2 = false;
    //cout << "List 1:" << endl ;
    
    cin >> x ;
    while( !cin.eof() ){
        if( x == 0 ){
            List2 = true ;
            //cout << "\nlist 2:\n" ;
        }
        
        else{
            // cout << x << " " ;
            if (List2==false){
                A1.insert(x);
                count1++;
                
            }
            else if ((List2==true) && (x!=0))
            {
                A2.insert(x);
                count2++;
               
            }
        }
        cin >> x ;
    }
   
    

    
}
int main()
{
    cout<<"301228629 ,zmmanji, Zeeshaan Manji "<<endl;
    Heap A1(1000000);
    Heap A2(1000000);
    Run(A1,A2);
    A1.compare(A2);
    
    
    
}
