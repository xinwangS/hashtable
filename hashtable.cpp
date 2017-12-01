#include "hashtable.h"

int HashTable::Hash(string input) const
{
	int h=0;
	int exp=input.size();
	int* a=new int[input.size()];
	for(unsigned int i=0;i<input.size();i++)
	{
		a[i]=input[i]-96;
	}
	int sum=0;
	for(unsigned int i=0;i<input.size();i++)
	{
		if(input.size()==1)
		{
			sum=(a[i])%maxsize;
		}
		else
		{
			if(i==0)
			{
				sum=a[i]*32;
			}
			else if(i==input.size()-1)
			{
				sum=((sum+a[i])%maxsize);
			}
			else
			{
				sum=((sum+a[i])%maxsize)*32;

			}
		}
	}
	return sum;

}

int HashTable::SmallestPrime(int n) const
{
	int i = n+1;
	while(IsPrime(i)!= true)
	{
		i++;
	}
	return i;

}

bool HashTable::IsPrime(int n) const
{
	int count = 0;
	for(int i = 1; i <= n; i++)
	{
		if(n%i == 0)
			count++;
	}
	if(count == 2)
		return true;
	return false;

}



bool HashTable::Resize(int n)
{
	
	if(n<maxsize||n<0)
	{
		return false;
	}
	else
	{
		int newmaxsize=this->SmallestPrime(n);
		SLinkedList<UserAccount>* newtable=new SLinkedList<UserAccount>[newmaxsize];
		vector <UserAccount> content;
		vector <UserAccount> content2;
		for( int i=0;i<maxsize;i++)
		{
			content=table[i].Dump();
			for(unsigned int j=0;j<content.size();j++)
			{
				content2.push_back(content[j]);
			}
			table[i].RemoveAll();
		}
		
		delete[]table;
		size=0;
		maxsize=newmaxsize;
		table=newtable;
		for(int i=0;i<maxsize;i++)
		{
			for(int i = (content2.size()-1); i >= 0 ; i--)
			{
				table[i].InsertBack(content2[i]);
			}
		}
		return true;
	}
	
}







HashTable::HashTable()
{
	size=0;
	maxsize=101;
	table=new SLinkedList<UserAccount>[maxsize];
}

HashTable::HashTable(int n)
{
	size=0;
	maxsize=this->SmallestPrime(2*n);
	table=new SLinkedList<UserAccount>[maxsize];
}

HashTable::HashTable(const HashTable& sourceht)
{
	size=sourceht.Size();
	maxsize=sourceht.MaxSize();
	table=new SLinkedList<UserAccount>[sourceht.maxsize];
	for(int i=0;i<sourceht.MaxSize();i++)
	{
		table[i]=sourceht.table[i];
	}
	
}


HashTable::~HashTable()
{
	if(table->Size()==0)
		return;
	table->RemoveAll();

}

HashTable&HashTable::operator=(const HashTable& sourceht)
{
	if(this!=&sourceht){
		maxsize=sourceht.maxsize;
		size=sourceht.size;
		table=new SLinkedList<UserAccount>[maxsize];
		for(int i=0;i<maxsize;i++){
			table[i]=sourceht.table[i];
		}
	}
	return *this;
}

bool HashTable::Insert(UserAccount acct)
{
    if(!table->Contains(acct))
	{
		int hashvalue=this->Hash(acct.GetUsername());
		size++;
		while( LoadFactor() >= (float)2/3)
		{
			Resize(maxsize);
			return false;
		}
		table [hashvalue].InsertBack(acct);
		return true;
	}
	return false;
	
}


bool HashTable::Remove(UserAccount acct)
{
	int h=Hash(acct.GetUsername());
	if(table[h].Contains(acct))
	{
		size--;
		return table[h].Remove(acct);
	}
	return false;
	
}


bool HashTable::Search(UserAccount acct) const
{
	int hasusername=this->Hash(acct.GetUsername());
	if( hasusername<=maxsize)
	{
		if(table[hasusername].Contains(acct))
		{
			return true;
		}
	}
	return false;
}

UserAccount*HashTable::Retrieve(UserAccount acct)
{
	if(!Search(acct))
	{
		return NULL;
	}
	int position=this->Hash(acct.GetUsername());
	UserAccount* value=table[position].Retrieve(acct);
	return value;
}


int HashTable::Size() const
{
	return size;
}

int HashTable::MaxSize() const
{
	return maxsize;
}

double HashTable::LoadFactor() const
{
	double doublesize=(double)size;
	double doublemaxsize=(double)maxsize;
	return doublesize/doublemaxsize;
}
