//NEED TO FIX DELETE MINIMUM
#include<iostream>
#define BIN_TREE_NOT_INITIALIZED -1
#define OPERATION_SUCCESSFUL 0
#define ERROR 1
#define MARKED 1
#define UNMARKED 0
#define INT_MAX 65535

using namespace std;

struct nodePayload
{
	int info;
};

class fibonacciTree
{
	int degree;
	int level; 
	int mark;	
	nodePayload data;	
	
	friend fibonacciTree* consolidate(fibonacciTree*,fibonacciTree*);	
 	fibonacciTree* merge(fibonacciTree*,fibonacciTree*);		
	
	public:
		
		fibonacciTree *parent;
		fibonacciTree *child;
		fibonacciTree *leftSibling;
		fibonacciTree *rightSibling;

		fibonacciTree()
		{
			int i = 0;			

			this->degree = BIN_TREE_NOT_INITIALIZED;
			this->data.info = BIN_TREE_NOT_INITIALIZED;
			this->level = BIN_TREE_NOT_INITIALIZED;		
			this->mark = UNMARKED;			
			
			this->parent = NULL;
			this->child = NULL;
			this->leftSibling = NULL;
			this->rightSibling = NULL;
		}

		fibonacciTree(int degree)
		{
			int i = 0;

			this->degree = degree;
			this->data.info = BIN_TREE_NOT_INITIALIZED;
			this->level = 0;	
			this->mark = UNMARKED;					
			
			this->parent = NULL;
			this->child = NULL;
			this->leftSibling = NULL;
			this->rightSibling = NULL;
		}

		fibonacciTree(int degree,int info)
		{
			int i = 0;

			this->degree = degree;
			this->data.info = info;
			this->level = 0;				
			this->mark = UNMARKED;				
			
			this->parent = NULL;
			this->child = NULL;
			this->leftSibling = NULL;
			this->rightSibling = NULL;
		}		

		int getDegree() 
		{
			return this->degree;
		}

		void setDegree(int degree)
		{
			this->degree = degree;
		}

		void setLevel(int level)
		{
			this->level = level;
		}		

		int getInfo()
		{
			return this->data.info;
		}		

		void setInfo(int info)
		{
			this->data.info = info;
		}	
		
		int getLevel()
		{
			return this->level;
		}		
	
		int getMarked()
		{
			return this->mark;
		}

		void setMarked(int mark)
		{
			this->mark = mark;
		} 		

		void display(fibonacciTree*);

		fibonacciTree* makeFibonacciHeap(int info)
		{
			return new fibonacciTree( 0 , info );
		}

} *minimum;

std::deque<fibonacciTree*> fibonacciHeap;

void fibonacciTree::display(fibonacciTree* node)
{
	
}

fibonacciTree* merge ( fibonacciTree *tree1 , fibonacciTree *tree2 )
{
	if ( tree2 == NULL )
		return tree1;	

	fibonacciTree *iterator;

	iterator = tree2;

	while( iterator->rightSibling != NULL )
		iterator = iterator-> rightSibling;

	iterator->rightSibling = tree1;

	tree1->leftSibling = iterator;

	return tree2;
}

fibonacciTree* mergeTree(fibonacciTree *tree1,fibonacciTree *tree2)
{
	cout<<"Here";	

	if(tree1->getInfo() < tree2->getInfo() )
	{
		cout<<"Tree1 merge works?";		

		tree2->parent = tree1;
		tree2->rightSibling = tree1->child;
		tree1->child->leftSibling = tree2;		
		tree1->child = tree2;	
		
		tree1->setDegree( tree1->getDegree() + 1 );
		
		cout<<"works?";			
		return tree1;
	} 

	else
	{	
		cout<<"Tree2 merge works?";			
		tree1->parent = tree2;
		tree1->rightSibling = tree2->child;
		tree2->child->leftSibling = tree1;		
		tree2->child = tree1;	
	
		tree2->setDegree( tree2->getDegree() + 1 );
			
		cout<<"works?";	
		return tree2;
	}
}

void consolidate()
{
	fibonacciTree *hashTable[ 2 * fibonacciHeap.size()];
	fibonacciTree *temp;
	int k = 0;	
	
	temp = new fibonacciTree( -1 , -1 );	

	std::deque<fibonacciTree*>::iterator i = fibonacciHeap.begin();	

	for( k = 0; k < 2 * fibonacciHeap.size() ; k++ )
		hashTable[k] = NULL;
	
	while( i != fibonacciHeap.end() )
	{
		if( hashTable[(*i)->getDegree()] == NULL )
			hashTable[(*i)->getDegree()] = (*i) ;
		
		else //segfault
		{
			(*i) =  merge( *i , hashTable[(*i)->getDegree()] );			

			while( hashTable[(*i)->getDegree()] !=NULL )			
				(*i) =  merge( *i , hashTable[(*i)->getDegree()] );
			

			if ( hashTable[(temp)->getDegree()] == NULL )
				hashTable[(temp)->getDegree() ] = temp;
		
		} 
	
		i++;
	}
}

int extractMinimum()
{
	fibonacciTree *currentNode = minimum->child;
	int returnVal = minimum->getInfo();

	fibonacciHeap.erase( std::remove( fibonacciHeap.begin() , fibonacciHeap.end()  , minimum ) , fibonacciHeap.end() );	
	
	if( currentNode != NULL )
	{	
		while( currentNode->rightSibling != NULL )
		{
			if( currentNode->getMarked() == MARKED )
				currentNode->setMarked( UNMARKED );		
		
			currentNode->parent = NULL;
			currentNode->leftSibling = fibonacciHeap.at( fibonacciHeap.size() );
		
			fibonacciHeap.push_back(currentNode);
		
			currentNode = currentNode->rightSibling;
		
			if( currentNode->leftSibling == NULL );
		
			else	currentNode->leftSibling->rightSibling = NULL;	
		}
	}
	
	consolidate();

	return returnVal;
}

int main(void)
{
	fibonacciTree *temp;
	fibonacciTree *heapHead;	
	
	int info = 0;
	int i = 0;
	int j = 0;

	minimum = new fibonacciTree( 0 , INT_MAX );	

	heapHead = NULL;	

	do
	{
		cout<<"Enter the nodes info: (ZERO TO QUIT)"<<endl;
		cin>>info;

		if( !info )
			break;		

		temp = makeFibonacciHeap( info );

		heapHead = merge( temp , heapHead );

		if( minimum->getInfo() > temp->getInfo() )
			minimum = temp;	
				
	}while(info);

	info = extractMinimum();	

	cout<<"Minimum node: "<<info<<endl;	

	for( std::deque<fibonacciTree*>::iterator i = fibonacciHeap.begin() ; i != fibonacciHeap.end() ; i++)
		cout<<(*i)->getInfo()<<endl;

	return OPERATION_SUCCESSFUL;
}


	
