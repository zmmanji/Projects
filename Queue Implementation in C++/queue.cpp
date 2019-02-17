#include <iostream>
#include "queue.h"
using namespace std;

Queue::Queue()
{
    current_size=0;
    front_p=NULL;
    back_p=NULL;
}
Queue::~Queue()
{
    while (front_p!=NULL)
    {
        node *p=front_p;
        front_p=front_p->next;
        delete p;
    }
}
Queue::Queue(const Queue& q)
{
	current_size=0;
    front_p=NULL;
    back_p=NULL;
    node *p=q.front_p;
    while (p!=NULL)
    {
        enqueue(p->data);
        p=p->next;
    }
    
}
void Queue::enqueue(int i)
{
    node *temp;
    temp=new node(i,temp);
    if (front_p==NULL)
    {
        front_p=back_p=temp;
        back_p->next=NULL;
    }
    else
    {
        back_p->next=temp;
        back_p=temp;
        back_p->next=NULL;
    }
    current_size++;
    
    
}
int Queue::dequeue()
{
    node *temp=front_p;
    int temp2=front_p->data;
    front_p=front_p->next;
    delete temp;
    current_size--;
    return temp2;
    
    
}
int Queue::front(){
    return (front_p->data);
    
}
bool Queue::empty(){
    if (current_size==0){
        return true;
        
    }
    else
    {
        return false;
    }
}
int Queue::size()
{
    return (current_size);
}
/*void Queue::removeall()
{
    while (front_p!=NULL)
    {
        node *p=front_p;
        front_p=front_p->next;
        delete p;
    }
}*/
/*void Queue::print(Queue& a) // was only used for testing purposes
{
    node*head=a.front_p;
    while (head!=NULL)
    {
        cout<<head->data<<endl;
        head=head->next;
    }
    cout<<a.front_p->data<<"FRONT"<<endl;
    cout<<a.back_p->data<<"back"<<endl;
    cout<<a.current_size<<""<<endl;

    
}*/
int Queue::makeUnique(int i)
{
    
    int count=0;
    node*temp;
    node *current=front_p;
    node *z;
    node*test=front_p;
    node *back=back_p;
    while (test!=NULL)
    {
        if (test->data==i)
        {
            count++;
        }
        test=test->next;
    }
    if (count>1)
    {
        count=0;
        current=front_p;
        
        if (front_p->data==i)
        {
            count++;
            current=current->next;
            z=front_p;
            
        }
        else
        {
            z=front_p;
            current=current->next;
        }
        while (current!=NULL)
        {
            
            if(current->data==i)
            {
                count++;
                if (count>1)
                {
                    if(current->next==NULL)
                    {
                        back_p=z;
                        current_size--;
                        temp=current;
                        //current=current->next;
                        z->next=current;
                        delete current;
                        z->next=NULL;
                        count=count-1;
                        return count;
                        
                    }
                    else
                    {
                        current_size--;
                        temp=current;
                        current=current->next;
                        z->next=current;
                        delete temp;
                    }
                    
                    
                }
                else
                {
                    z=current;
                    
                    current=current->next;
                    
                }
                
                
            }
            else if (current->next!=NULL)
            {
                current=current->next;
                z=z->next;
            }
            else
            {
                
                break;
            }
            
            
        }
        return count-1;
    }
    else if (count==1)
    {
        return count-1;
    }
    return 0;
    
    
    
}
