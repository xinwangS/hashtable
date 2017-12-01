#ifdef _SLINKEDLIST_H_

#include <vector>
template <class T>
void SLinkedList<T>::CopyList(const SLinkedList& ll)
{
	size=0;
	front=NULL;
	back=NULL;
	Node<T>* trace=ll.front;
	for(int i=0;i<ll.size;i++)
	{
		this->InsertBack(trace->data);
		trace=trace->next;
	}
}
template <class T>
void SLinkedList<T>::DeleteList()
{
	Node<T>* temp=front;
	while(temp!=NULL)
	{
		temp=front->next;
		delete front;
		front=temp;
	}
	front=NULL;
	back=NULL;
	size=0;
}
template <class T>
 SLinkedList<T>::SLinkedList()
 {
	size=0;
	front=NULL;
	back=NULL;
 }
 template <class T>
 SLinkedList<T>::SLinkedList(const SLinkedList& ll)
 {
	 CopyList(ll);
 }
  template <class T>
 SLinkedList<T>::~SLinkedList()
 {
	 DeleteList();
 }
  template <class T>
 void SLinkedList<T>::InsertFront(T item)
 {
	 Node<T>* newnode=new Node<T>(item);
	 if(front==NULL)
	 {
		 this->front=newnode;
		 this->back=newnode;
		 newnode->next=NULL;
		 size++;
	 }
	 else
	 {
		 newnode->next=this->front;
		 front=newnode;
		 size++;
	 }
 }
 template <class T>
  void SLinkedList<T>::InsertBack(T item)
  {
	  Node<T> *newnode= new Node<T>(item);
	  if(back==NULL)
	  {
		  this->front=newnode;
		  this->back=newnode;
		  newnode->next=NULL;
		  size++;
	  }
	  else
	  {
		  this->back->next=newnode;
		  newnode->next=NULL;
		  back=newnode;
		  size++;
	  }
  }
   template <class T>
  bool SLinkedList<T>::Remove(T item)
  {
	  if(front==NULL)
	  {
		  return false;
	  }
	  Node<T>*trace=front;
	  Node<T>*prev=front;
	  do{
		  if(trace->data==item)
		  {
			  if(trace==front)
			  {
				  front=trace->next;
			  }
		 
		      else
		     {
			    prev->next=trace->next;
		     }
		     delete trace;
		     size--;
		     return true;
		  }
		  else
		  {
			  if(trace==front)
			  {
				  trace=trace->next;
				  continue;
			  }
			  trace=trace->next;
			  prev=prev->next;
		  }
	  }
	  while(trace!=NULL);
	  return false;
  }
  template <class T>
  void SLinkedList<T>::RemoveAll()
  {
	  DeleteList();
  }
   template <class T>
   int SLinkedList<T>::Size() const
   {
	   return size;
   }
    template <class T>

   bool SLinkedList<T>::IsEmpty() const
   {
	   if(this->front==NULL)
	   {
		   return true;
	   }
	   else
	   {
		   return false;
	   }
   }
      template <class T>
   bool SLinkedList<T>::Contains(T item) const
  {
	if(front!=NULL)
	{
		Node<T>* trace=front;
		for(int j=0;j<size;j++)
		{
			if(trace->data==item)
			{
				return true;
			}
			trace=trace->next;
		}
		return false;
	}
	else
	{
		return false;
	}
   }
  template <class T>
  T*SLinkedList<T>:: Retrieve(T item)
  {
		if(!Contains(item))
		{
			return NULL;
		}
		else
		{
			T* value = NULL;
			Node<T>* trace =front;
			while(trace!=NULL)
			{
			  if(trace->data==item)
			  {
				value = &(trace->data);
				return value;
			  }
			  trace=trace->next;
			}
			return NULL;
		}
  }
  

 
  
  template <class T>
   vector<T> SLinkedList<T>::Dump() const
   {
	   vector<T> v;
	   Node<T>* trace=front;
     	while(trace!=NULL)
		{
		  v.push_back(trace->data);
		  trace=trace->next;
		}
	   return v;
   }

  


   template <class T>
 SLinkedList<T>&SLinkedList<T>::operator=(const SLinkedList& ll)
	{
	    if(&ll!=this)
	    {
		 DeleteList();
		 CopyList(ll);
	    }
	    return *this;

	}
  
 
#endif