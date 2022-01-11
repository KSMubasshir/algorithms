#include<bits/stdc++.h>
#include<stdio.h>
#define MAX_HEAP_SIZE 100000
#define MAXREAL 999999.0
#include<iostream>
#define FALSE_VALUE 0
#define TRUE_VALUE 1
#include<iomanip>
using namespace std;
struct HeapItem
{
public:
    char data;
    string prefcode;
    float key;
    HeapItem * left; //points to left child
    HeapItem * right; //points to right child
};
//MinHeap class, minimum item stored at the root of heap tree
class MinHeap
{
public:
    HeapItem * A; //stores heap items, e.g., nodes
    int heapLength;
    int * Map;
    MinHeap() //constructor
    {
        A = new HeapItem[MAX_HEAP_SIZE];
        Map = new int[MAX_HEAP_SIZE];
        heapLength=0;
    }
    MinHeap(const MinHeap &source)//copy constructor
    {
        A = new HeapItem[MAX_HEAP_SIZE];
        Map = new int[MAX_HEAP_SIZE];
        heapLength=source.heapLength;
        for(int i=1; i<=heapLength; i++)
        {
            A[i]=source.A[i];
            Map[(int) A[i].data]=i;
        }
    }
    ~MinHeap() //destructor
    {
        if(Map) delete [] Map;
        if(A) 
		{
			delete [] A;
		}
        Map = 0; //set to NULL after deletion
        A = 0; //set to NULL after deletion
    }
    //Fills the heap with an array of integers
    //key values do not maintain heap property
    //May be used in some algorithms such as dijkstra's shortest path
    void initialize(int v[], int n)
    {
        heapLength = n;
        for(int i=0; i<n; i++) //nodes are stored from index 1 instead of 0 in the heap
        {
            A[i+1].data = v[i];
            A[i+1].key = MAXREAL;
            Map[v[i]] = i+1; //Map tracks which vertex is stored at which heap node
        }
    }
    //this function inserts a new (data,key) pair in the heap
    //call to buheapify is required
    void insertItem(char data, float key)
    {
        heapLength++;
        A[heapLength].data=data;
        A[heapLength].key=key;
        Map[(int)data]=heapLength;
        buHeapify(heapLength);
    }
    void insertNode(HeapItem item)
    {
        heapLength++;
        A[heapLength]=item;
        buHeapify(heapLength);
    }
    //this function removes (and returns) the node which contains the minimum key value
    HeapItem removeMin()
    {
        HeapItem ret=A[1];
        A[1]=A[heapLength];
        heapLength--;
        Map[A[1].data]=1;
        heapify(1);
        return ret;
    }
    //The function updates the key value of an existing data
    //stored in the heap
    //Note that updates can result in an increase or decrease of key value
    //Call to heapify or buheapify is required
    void updateKey(char data, float key)
    {
        int index=Map[data];
        bool x;
        if(A[index].key>key) x=true;
        else x=false;
        A[index].key=key;
        if(x)
            buHeapify(index);
        else
            heapify(index);
    }
    //This function returns the key value of a data stored in heap
    float getKey(char data)
    {
        int i = Map[data];
        return A[i].key;
    }
    //This function heapifies the heap
    //When a key value of ith node is increased (because of update), then calling
    //this function will restore heap property
    void heapify(int i)
    {
        int l,r,smallest;
        while(1)
        {
            l=2*i;      //left child index
            r=2*i+1;    //right child index
            smallest=i;

            if(l>heapLength && r>heapLength)
                break; //nothing to do, we are at bottom
            else if(r>heapLength)
                smallest = l;
            else if(l>heapLength)
                smallest = r;
            else if( A[l].key < A[r].key )
                smallest = l;
            else
                smallest = r;

            if(A[i].key <= A[smallest].key)
                break;	//we are done heapifying
            else
            {
                //swap nodes with smallest child, adjust Map array accordingly
                HeapItem t;
                t=A[i];
                A[i]=A[smallest];
                Map[A[i].data]=i;
                A[smallest]=t;
                Map[A[smallest].data]=smallest;
                i=smallest;
            }
        }
    }
    //This function heapifies the heap form bottom to up
    //When a key value of ith node is decreased (because of update), then calling
    //this function will restore heap property
    //In addition, when a new item is inserted at the end of the heap, then
    //calling this function restores heap property
    void buHeapify(int i)
    {
        int p,l,r,smallest;
        if(i==1) return;
        p=i/2;
        l=2*p;
        r=l+1;
        if(l<=heapLength&&r<=heapLength)
        {
            smallest=(A[l].key<A[r].key)?l:r;
            smallest=(A[smallest].key<A[p].key)?smallest:p;
        }
        else if(l<=heapLength&&r>heapLength)
        {
            smallest=A[p].key<A[l].key?p:l;
        }
        else if(r<=heapLength&&l>heapLength)
        {
            smallest=A[p].key<A[r].key?p:r;
        }

        if(A[p].key<=A[smallest].key)
        {
            return;
        }
        else
        {
            HeapItem temp;
            temp=A[p];
            A[p]=A[smallest];
            Map[A[p].data]=p;
            A[smallest]=temp;
            Map[A[smallest].data]=smallest;
            buHeapify(p);
        }
    }
    void printHeap()
    {
        printf("Heap length: %d\n", heapLength);
        for(int i=1; i<=heapLength; i++)
        {
            printf("(%c,%.2f) ", A[i].data, A[i].key);
        }
        printf("\n");
    }
    bool Empty()
    {
        if(heapLength==0)return true;
        else return false;
    }
    int getLength()
    {
        return heapLength;
    }
};

HeapItem HuffmanTree(MinHeap heap)
{
    while(!heap.Empty())
    {
        HeapItem *x=new HeapItem;
        HeapItem *y=new HeapItem;
        HeapItem z;
        *x=heap.removeMin();
        *y=heap.removeMin();
        z.key=x->key+y->key;
        z.left=x;
        z.right=y;
        heap.insertNode(z);
        if((heap.getLength())==1)
            break;
    }
    return heap.A[1];
}

void generateHuffCode(HeapItem *temproot,string code)
{
    HeapItem * curRoot = new HeapItem;
    curRoot = temproot;
    curRoot->prefcode=code;
    if(curRoot==NULL) return;
    else if(curRoot->left==NULL&&curRoot->right==NULL)
    {
        cout<<curRoot->data<<" "<<curRoot->key<<" "<<setw(6)<<curRoot->prefcode<<" "<<curRoot->prefcode.length()<<endl;
        return;
    }
    else
    {
        curRoot->left->prefcode=code+"0";
        curRoot->right->prefcode=code+"1";
        generateHuffCode(curRoot->left,code+"0");
        generateHuffCode(curRoot->right,code+"1");
    }
    delete curRoot;
}

void Huffman(MinHeap heap)
{
    HeapItem root=HuffmanTree(heap);
    generateHuffCode(&root,"");
}
//===========================  main  ============================//
int main()
{
    char data;
    float key;
    MinHeap heap;
    int n;
    cin>>n;
    for(int i=0; i<n; i++)
    {
        cin>>data>>key;
        heap.insertItem(data,key);
    }
    cout<<endl; 
    Huffman(heap);
    return 0;
}
