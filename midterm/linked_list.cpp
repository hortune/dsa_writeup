#include <iostream>
#include <string>
using namespace std;
class linked_list
{
	public:
      	linked_list(int gg)
      	{
      		a=gg;
      	};
      	linked_list();
      	~linked_list()
      	{
      		if(next!=NULL)
			{
				next->~linked_list();
      			cout<<"delete node "<<next->a<<endl;
      			delete next;
      			next=NULL;
      		}
      	};
      	int  a=100;
      	linked_list *next = NULL;
    	static int amount;
    	void reverse();
    	void add(int b)
    	{
    		linked_list *temp;
    		temp = this;
    		while(temp->next!=NULL)
    			{
    				temp=temp->next;
    			}
    		temp->next = new linked_list(sizeof(linked_list));
    		temp = temp->next;
    		temp->a = b;
    		temp->next = NULL;
    		amount++;
    	}
    	void remove(int k)
    	{
    		linked_list* temp = this;
    		linked_list* temp_prev;
    		if(k==0)
    		{
    			amount--;
    			temp = next;
    			a = next->a;
    			next = next->next;
    			temp->next = NULL;
    			delete temp;
    		}
    		else
    		{
    			for(int i=0;i<k;i++)
    			{
    				temp_prev = temp;
    				temp = temp->next;
    			}
    			temp_prev->a = temp->a;
    			temp_prev->next = temp->next;
    			temp->next=NULL;
    			delete temp;
    		}
    	}
    	
};
int linked_list::amount = 1;

int main()
{
	linked_list *head = new linked_list(sizeof(linked_list));
	head->a = 0;
	for(int i=0;i<50;i++)
		head->add(i);
	
	linked_list *temp = head;
	head->remove(20);
	while(temp)
	{
		cout<<temp->a<<endl;
		temp=temp->next;
		//cout<<"hi"<<endl;
	}
	delete head;

}
