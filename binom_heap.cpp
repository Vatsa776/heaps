#include<iostream>
#include<deque>
#include<algorithm>
#define BIN_TREE_NOT_INITIALIZED -1
#define OPERATION_SUCCESSFUL 0
#define ERROR 1
#define INT_MAX 65535

using namespace std;

struct nodePayload
{
	int info;
};

class binomialTree
{
	int order;
	int level; 
	nodePayload data;	
	
	std::deque<binomialTree*> children;
	
	void increaseLevel(binomialTree*);	
	friend binomialTree* consolidate(binomialTree*,binomialTree*);	
		
	public:
		binomialTree()
		{
			int i = 0;			

			this->order = BIN_TREE_NOT_INITIALIZED;
			this->data.info = BIN_TREE_NOT_INITIALIZED;
			this->level = BIN_TREE_NOT_INITIALIZED;		
		}

		binomialTree(int order)
		{
			int i = 0;

			this->order = order;
			this->data.info = BIN_TREE_NOT_INITIALIZED;
			this->level = 0;	
		}

		binomialTree(int order,int info)
		{
			int i = 0;

			this->order = order;
			this->data.info = info;
			this->level = 0;				
		}		

		int getOrder() 
		{
			return this->order;
		}

		void setOrder(int order)
		{
			this->order = order;
		}

		void setLevel(int level)
		{
			this->level = level;
		}		

		int getInfo()
		{
			return this->data.info;
		}		

		int getLevel()
		{
			return this->level;
		}		
	
		void display(binomialTree*);

		binomialTree* find(binomialTree*,int);

		friend std::deque<binomialTree*> deleteMinimum();
} *minimum;

std::deque<binomialTree*> binomialHeap;
int position = 0;

void binomialTree::display(binomialTree* node)
{
		if( node == NULL ) 
			return;		

		std::deque<binomialTree*>::iterator i = node->children.begin();		
		
		cout<<"Level: "<<node->getLevel()<<endl<<node->getInfo()<<endl;
		
		while( i != node->children.end() )
		{
			cout<<"Level: "<<(*i)->getLevel()<<endl;			

			cout<<(*i)->getInfo()<<endl;
			
			if( (*i)->children.size() != 0 )
			{
				std::deque<binomialTree*>::iterator j = (*i)->children.begin();
				while( j != (*i)->children.end() )
				{					
					display(*j);
					j++;
				}			
			}			

			i++;		
		}
		
		cout<<endl;
}

void binomialTree::increaseLevel(binomialTree* node)
{
	if( node == NULL )
		return;
		
	node->level++;
	
	if( node->children.size() != 0)
	{
		std::deque<binomialTree*>::iterator i = node->children.begin();		

		increaseLevel(*i);

		i++;
	}
} 

binomialTree* consolidate(binomialTree *tree1,binomialTree *tree2)
{
	if(tree1->data.info < tree2->data.info)
	{
		tree1->children.push_front( tree2 );
	
		tree1->order++;
		tree2->increaseLevel(tree2);		

		return tree1;
	} 

	else
	{	
		tree2->children.push_front( tree1 );
	
		tree2->order++;
		tree1->increaseLevel(tree1);		

		return tree2;
	}
}

binomialTree* findMinimum(std::deque<binomialTree*> binomialHeap)
{
	binomialTree* minimum = new binomialTree( 0 , INT_MAX );
	int count = 0; 
	std::deque<binomialTree*>::iterator i = binomialHeap.begin();

	while( i != binomialHeap.end() )
	{
		if( minimum->getInfo() > (*i)->getInfo() )
		{	
			minimum = (*i);
			position = count;
		}	
		
		i++;
		count++;	
	}

	return minimum;	
}

std::deque<binomialTree*> merge(std::deque<binomialTree*> heapOne, std::deque<binomialTree*> heapTwo)
{
	std::deque<binomialTree*> returnHeap;
	std::deque<binomialTree*>::iterator k1 = heapOne.begin();	
	std::deque<binomialTree*>::iterator k2 = heapTwo.begin();

	int i,j;	

	while( k2 != heapTwo.end() || k1 != heapOne.end() )
	{
		returnHeap.push_front( *k1 );
		returnHeap.push_front( *k2 );
	
		if( returnHeap.size() == 1 )
			continue;

		for( i = 0; i < returnHeap.size(); i++ )
			for( j = 0 ; j < returnHeap.size(); j++ )				
			{
				if( returnHeap.at(i) == returnHeap.at(j) );			

				else if( returnHeap.at(i)->getOrder() == returnHeap.at(j)->getOrder() )
				{
					returnHeap.at(i) = consolidate( returnHeap.at(i) , returnHeap.at(j) );
					returnHeap.erase( returnHeap.begin() + (j));
				
					i=0;
				}		
			}
		
		k1++;
		k2++;
	}

	if( k1 == heapOne.end() )
	{
		while( k2 != heapTwo.end() )
		{		
			returnHeap.push_front( *k2 );
	
			if( returnHeap.size() == 1 )
				continue;
	
			for( i = 0; i < returnHeap.size(); i++ )
				for( j = 0 ; j < returnHeap.size(); j++ )				
				{
					if( returnHeap.at(i) == returnHeap.at(j) );			
	
					else if( returnHeap.at(i)->getOrder() == returnHeap.at(j)->getOrder() )
					{
						returnHeap.at(i) = consolidate( returnHeap.at(i) , returnHeap.at(j) );
						returnHeap.erase( returnHeap.begin() + (j));
					
						i=0;
					}		
				}
			
			
			k2++;
		}
	}
	
	else
	{
		while( k1 != heapOne.end() )
		{		
			returnHeap.push_front( *k1 );
	
			if( returnHeap.size() == 1 )
				continue;
	
			for( i = 0; i < returnHeap.size(); i++ )
				for( j = 0 ; j < returnHeap.size(); j++ )				
				{
					if( returnHeap.at(i) == returnHeap.at(j) );			
	
					else if( returnHeap.at(i)->getOrder() == returnHeap.at(j)->getOrder() )
					{
						returnHeap.at(i) = consolidate( returnHeap.at(i) , returnHeap.at(j) );
						returnHeap.erase( returnHeap.begin() + (j));
					
						i=0;
					}		
				}
			
			
			k1++;
		}	

	}	

	return returnHeap;
}

std::deque<binomialTree*> deleteMinimum()
{
	std::deque<binomialTree*> tempHeap;
	int i,j,k;

	for ( k = 0; k < minimum->children.size(); k++ )
	{		
		minimum->children.at(k)->setOrder(0);
		minimum->children.at(k)->setLevel(0);	
		
		tempHeap.push_front( minimum->children.at(k) );
	
		if( tempHeap.size() == 1 )
			continue;

		for( i = 0; i < tempHeap.size(); i++ )
			for( j = 0 ; j < tempHeap.size(); j++ )				
			{
				if( tempHeap.at(i) == tempHeap.at(j) );			

				else if( tempHeap.at(i)->getOrder() == tempHeap.at(j)->getOrder() )
				{
					tempHeap.at(i) = consolidate( tempHeap.at(i) , tempHeap.at(j) );
					tempHeap.erase( tempHeap.begin() + (j));
				
					i=0;
				}		
			}

	}

	cout<<"not here\n";		

	binomialHeap.erase( binomialHeap.begin() + position ); 

	for( std::deque<binomialTree*>::iterator it = tempHeap.begin(); it != tempHeap.end(); it++ )
			cout<<(*it)->getInfo()<<"->";	
		cout<<endl;				

	for( i = 0; i < tempHeap.size(); i++ )
		tempHeap.at(i)->display( tempHeap.at(i) );	

	binomialHeap = merge( binomialHeap , tempHeap );

	return binomialHeap;
}

int main(void)
{
	binomialTree *temp;
	
	int info = 0;
	int i = 0;
	int j = 0;

	do
	{
		cout<<"Enter the nodes info: (ZERO TO QUIT)"<<endl;
		cin>>info;

		if( !info )
			break;		

		temp = new binomialTree( 0 , info );

		binomialHeap.push_front( temp );

		if( binomialHeap.size() == 1 )
			continue;

		for( i = 0; i < binomialHeap.size(); i++ )
			for( j = 0 ; j < binomialHeap.size(); j++ )				
			{
				cout<<"Node "<<i<<" order = "<<binomialHeap.at(i)->getOrder()<<endl;
				cout<<"Node "<<j<<" order = "<<binomialHeap.at(j)->getOrder()<<endl;
				
				if( binomialHeap.at(i) == binomialHeap.at(j) );			

				else if( binomialHeap.at(i)->getOrder() == binomialHeap.at(j)->getOrder() )
				{
					binomialHeap.at(i) = consolidate( binomialHeap.at(i) , binomialHeap.at(j) );
					binomialHeap.erase( binomialHeap.begin() + (j));
				
					cout<<"Consolidated tree "<<i<<" with "<<j<<endl;
				
					cout<<"Size = "<<binomialHeap.size()<<endl;	
				
					i=0;
				}		
			}
		
		for( std::deque<binomialTree*>::iterator it = binomialHeap.begin(); it != binomialHeap.end(); it++ )
			cout<<(*it)->getInfo()<<"->";	
		cout<<endl;			
	
	}while(info);

	for( i = 0; i < binomialHeap.size(); i++ )
		binomialHeap.at(i)->display( binomialHeap.at(i) );
	
	
	minimum = findMinimum(binomialHeap);

	cout<<"The minimum is: "<<minimum->getInfo()<<endl;	

	return OPERATION_SUCCESSFUL;
}


	
