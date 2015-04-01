/******************************************************
  Heap.h -- Declarations for Basic Heap-of-Pair-of-Ints Class

  Stores pairs <element,priority> of ints.
  Supports O(log n) insertion, O(1) peeking at min priority and element 
  with min priority, and O(log n) extraction of element with min priority.
*******************************************************/
using namespace std;

class Heap{

public:
   // Constructors and Destructor

   // New empty Heap with default capacity.
   Heap();  

   // New empty Heap with capacity c.
   Heap(int c); 

   // New Heap with size s, consisting of pairs <Pi,Vi> where, for 0 < i < s, 
   // Pi is Priorities[i] and Ei is value Elements[i].  
   // Capacity is s + c, where c is the "spare capacity" argument.
   // Requires: Priorities and Elements are of size at least s. 
   Heap( const int * Priorities, const int * Elements, int s, int c); 

   // New Heap with combined contents the two Heap arguments. 
   // Size of the new Heap is the sum of the sizes of argument Heaps.
   // Capacity of the new Heap is its size plus the "spare capacity" c.
   Heap( const Heap & Heap1, const Heap & Heap2, int c ); 

   // Destructor.
   ~Heap(); 

   // Accessors
   bool empty() const {return hSize == 0;}; // True iff Heap is empty.
   int size() const { return hSize ;} ; // Current size of Heap.
   int capacity() const { return hCapacity ;} ; // Current capacity.
   int peekMin() const { return A[0].element ;} // Peek at minimum element.
   int peekMinPriority() const { return A[0].priority ;} // Peek at priority of min element.

   // Modifiers
   void insert( int element, int priority ); // Insert element x.
   int extractMin(); // Remove and return the minimum element.

private:
   class Pair{
      public:
        int element ;
        int priority ;
   };

   Pair* A ; // Array containing heap contents.
   int hCapacity ; // Max number of elements (= size of A).
   int hSize ; // Current number of elements.

   // Repairs ordering invariant after adding leaf at A[i].
   void trickleUp(int i);

   // Repairs ordering invariant for sub-tree rooted at index i,
   //   when A[i] may be smaller than one of its children.
   void trickleDown(int i);

   // Establishes ordering invariant for entire array contents.
   void heapify(); //(Same as "make_heap" in lectures.)

   // Useful for implementing trickle
   void swap(int i,int j);
};

Heap::Heap(){
   hCapacity = 10 ;
   A = new Pair[hCapacity];
   hSize = 0 ; 
}

Heap::Heap(int c){ // New empty Heap with capacity c.
   // Complete this.
   hCapacity = c;
   A = new Pair[hCapacity];
   hSize = 0;
}

// New Heap with capacity c, with s elements, consisting of pairs <Pi,Vi> where 
//  Pi is Priorities[i], Vi is value Values[i], for 0 < i < s.
Heap::Heap( const int * Priorities, const int * Values, int s, int c){ 
   // Complete this.
   hCapacity = c+s;
   A = new Pair[hCapacity];
   hSize = s;
   for(int i = 0; i < s; i++)
   {
	A[i].priority = Priorities[i]; 
	A[i].element = Values[i];
   }
   heapify();
}

// New Heap with combined contents and of the two given heaps.
Heap::Heap( const Heap & Heap1, const Heap & Heap2, int c ){ 
   hCapacity = Heap1.hSize + Heap2.hSize + c ;
   // Complete this.
   Heap New_H(hCapacity);
   
   for(int i = 0; i < hSize; i++)
   {
	New_H.A[i] = A[i];
	New_H.hSize++;
   }
   for(int i = 0; i < Heap1.hSize; i++)
   {
	New_H.A[i+hSize] = Heap1.A[i];
	New_H.hSize++;
   }
   for(int i = 0; i < Heap2.hSize; i++)
   {
	New_H.A[i+hSize] = Heap2.A[i];
	New_H.hSize++;
   }
   New_H.heapify();
}

// Destructor
Heap::~Heap(){
   delete[] A;
}

// Modifiers
void Heap::insert(int element, int priority){
   A[hSize].element = element;
   A[hSize].priority = priority;
   trickleUp(hSize);
   hSize ++;
}

// Repairs the heap ordering invariant after adding a new element.
// Initial call should be trickleUp(hSize-1).
void Heap::trickleUp(int i){
   // Complete this.
    int parent=(i-1)/2;
    
    //condition to stop the recursion when finished repairing the tree
    if( parent>= 0 ){
        
        //move minimum elements to the top of the tree
        if(A[i].priority < A[parent].priority)
	{
            
            swap(i,parent);
            trickleUp(parent);//returns the i of the new parent      
	}
        
    }

}

void Heap::swap(int i, int j){
   Pair temp = A[i];
   A[i] = A[j];
   A[j] = temp ;
}

// Removes and returns minimum element.
int Heap::extractMin(){
   if(hSize == 0)
   {
	return 0;
   }
    
   else{
    
   int temp = A[0].element;
   A[0].element = A[hSize-1].element;
    A[0].priority=A[hSize-1].priority;
   hSize--;
   trickleDown(0);
       return temp;}
        
        
    
}

// Repairs the heap ordering invariant after replacing the root.
// Initial call by insert() is trickleDown(0).
// trickleDown(i) performs the repair on the subtree rooted a A[i].
// heapify() calls trickleDown(i) for i from (hSize/2)-1 down to 0.
void Heap::trickleDown(int i){
   // Complete this.

   int lchild = (2*i)+1;
   int rchild = (2*i)+2;
    
    if (lchild< hSize) {
        if ((rchild < hSize) && (A[lchild].element > A[rchild].element)) {
            swap(lchild,rchild);
        }
            if (A[i].element>A[lchild].element) {
                swap(i,lchild);
                trickleDown(lchild);
            }
        
    }
}

// Turns A[0] .. A[size-1] into a heap.
void Heap::heapify(){
   for( int i = (hSize/2)-1; i>=0 ; i-- ) trickleDown(i);  
}

