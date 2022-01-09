#include<stdio.h>
#include<stdlib.h>
#define NULL_VALUE -999999
#define INFINITY 999999
#define WHITE 1
#define GREY 2
#define BLACK 3
#include<iostream>
#include<iomanip>
#include<bits/stdc++.h>
using namespace std;

class Queue
{
    int queueInitSize ;
    int queueMaxSize;
    int * data;
    int length;
    int front;
    int rear;
public:
    Queue();
    ~Queue();
    void enqueue(int item); //insert item in the queue
    int dequeue(); //returns the item according to FIFO
    bool empty(); //return true if Queue is empty
};

Queue::Queue()
{
    queueInitSize = 2 ;
    queueMaxSize = queueInitSize;
    data = new int[queueMaxSize] ; //allocate initial memory
    length = 0 ;
    front = 0;
    rear = 0;
}


void Queue::enqueue(int item)
{
    if (length == queueMaxSize)
    {
        int * tempData ;
        //allocate new memory space for tempList
        queueMaxSize = 2 * queueMaxSize ;
        tempData = new int[queueMaxSize] ;
        int i, j;
        j = 0;
        for( i = rear; i < length ; i++ )
        {
            tempData[j++] = data[i] ; //copy items from rear
        }
        for( i = 0; i < rear ; i++ )
        {
            tempData[j++] = data[i] ; //copy items before rear
        }
        rear = 0 ;
        front = length ;
        delete[] data ; //free the memory allocated before
        data = tempData ; //make list to point to new memory
    }

    data[front] = item ; //store new item
    front = (front + 1) % queueMaxSize ;
    length++ ;
}


bool Queue::empty()
{
    if(length == 0) return true ;
    else return false ;
}


int Queue::dequeue()
{
    if(length == 0) return NULL_VALUE ;
    int item = data[rear] ;
    rear = (rear + 1) % queueMaxSize ;
    length-- ;
    return item ;
}


Queue::~Queue()
{
    if(data) delete[] data; //deallocate memory
    data = 0; //set to NULL
}

//****************Queue class ends here************************


//******************Graph class starts here**************************
class Graph
{
    int nVertices, nEdges ;
    bool directed ;
    int ** matrix,*color,*parent,*dist,*f,time ; //adjacency matrix to store the graph
    //define other variables required for bfs such as color, parent, and dist
    //you must use pointers and dynamic allocation

public:
    Graph(bool dir = false);
    ~Graph();
    void setnVertices(int n);
    void addEdge(int u, int v,int w);
    void removeEdge(int u, int v);
    bool isEdge(int u, int v);
    int getDegree(int u);
    bool hasCommonAdjacent(int u, int v);
    int getDist(int u, int v);
    void printGraph();
    void bfs(int source); //will run bfs in the graph
    void dfs(int source);
    void dfs_visit(int source);
};


Graph::Graph(bool dir)
{
    nVertices = 0 ;
    nEdges = 0 ;
    matrix = 0 ;
    color=0;
    parent=0;
    dist=0;
    f=0;
    time=0;
    directed = dir ;//set direction of the graph
    //define other variables to be initialized
}

void Graph::setnVertices(int n)
{
    this->nVertices = n ;

    //allocate space for the matrix
    matrix = new int*[nVertices];
    for(int i=0; i<nVertices; i++)
    {
        matrix[i] = new int[nVertices];
        for(int j=0; j<nVertices; j++)
            matrix[i][j] = 0; //initialize the matrix cells to 0
    }
    color=new int[nVertices];
    parent=new int[nVertices];
    dist=new int[nVertices];
    f=new int[nVertices];
}

void Graph::addEdge(int u, int v,int w)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = w;
    if(!directed) matrix[v][u] = w;
    nEdges++;

}

void Graph::removeEdge(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return;
    matrix[u][v] = 0;
    if(!directed) matrix[v][u] = 0;
    nEdges--;

}

bool Graph::isEdge(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    else if(matrix[u][v]) return true;
    else return false;
}

int Graph::getDegree(int u)
{
    if(u<0 || u>=nVertices) return NULL_VALUE;
    int deg=0;
    for(int i=0; i<nVertices; i++)
    {
        if(matrix[u][i]==1) deg++;
    }
    return deg;
}

bool Graph::hasCommonAdjacent(int u, int v)
{
    if(u<0 || u>=nVertices || v<0 || v>=nVertices) return false;
    for(int i=0; i<nVertices; i++)
    {
        if(matrix[u][i]&&matrix[v][i]) return true;
    }
    return false;
}

void Graph::bfs(int source)
{
    //complete this function
    //initialize BFS variables
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
    }
    Queue q ;
    color[source] = GREY;
    dist[source] = 0 ;
    q.enqueue(source) ;
    while( !q.empty() )
    {
        int u=q.dequeue();
        for(int i=0; i<nVertices; i++)
        {
            int v=i;
            if(matrix[u][v])
            {
                if(color[v]==WHITE)
                {
                    color[v]=GREY;
                    dist[v]=dist[u]+1;
                    parent[v]=u;
                    q.enqueue(v);
                }
            }
        }
        color[u]=BLACK;
    }
//    printf("\nColor\n");
//    for(int i=0; i<nVertices; i++)
//    {
//        printf("%2d",color[i]);
//    }
//    printf("\nParent\n");
//    for(int i=0; i<nVertices; i++)
//    {
//        printf("%2d",parent[i]);
//    }
//    printf("\nDist\n");
//    for(int i=0; i<nVertices; i++)
//   {
//        printf("%2d",dist[i]);
//    }
//    printf("\n");

}

void Graph::dfs(int source)
{
    for(int i=0; i<nVertices; i++)
    {
        color[i] = WHITE ;
        parent[i] = -1 ;
        dist[i] = INFINITY ;
        f[i] = INFINITY ;
    }
    time=0;
    for(int u=0; u<nVertices; u++)
    {
        if(color[u]==WHITE)
            dfs_visit(u);
    }
//
//    printf("\nColor\n");
//    for(int i=0; i<nVertices; i++)
//    {
//        printf("%2d",color[i]);
//    }
//    printf("\nParent\n");
//    for(int i=0; i<nVertices; i++)
//    {
//        printf("%2d",parent[i]);
//    }
//    printf("\nDist\n");
//    for(int i=0; i<nVertices; i++)
//   {
//        printf("%2d",dist[i]);
//    }
//    printf("\n");
//    printf("\nf\n");
//    for(int i=0; i<nVertices; i++)
//    {
//        printf("%2d",f[i]);
//    }
//    printf("\n");
}

void Graph::dfs_visit(int source)
{
    int u=source;
    color[u]=GREY;
    time=time+1;
    dist[u]=time;

    for(int i=0; i<nVertices; i++)
    {
        int v=i;
        if(matrix[u][v])
        {
            if(color[v]==WHITE)
            {
                parent[v]=u;
                dfs_visit(v);
            }
        }
    }
    color[u]=BLACK;
    time=time+1;
    f[u]=time;
}

int Graph::getDist(int u, int v)
{
    //returns the shortest path distance from u to v
    //must call bfs using u as the source vertex, then use distance array to find the distance
    if(u<0 || v<0 || u>=nVertices || v>=nVertices) return NULL_VALUE;
    bfs(u);
    return dist[v];
    //return INFINITY ;
}

void Graph::printGraph()
{
    printf("\nNumber of vertices: %d, Number of edges: %d\n", nVertices, nEdges);
    for(int i=0; i<nVertices; i++)
    {
        printf("%d:", i+1);
        for(int j=0; j<nVertices; j++)
        {
            if(matrix[i][j]!=0)
                printf(" (%d|%d) ", j+1,matrix[i][j]);
        }
        printf("\n");
    }
}

Graph::~Graph()
{

    delete []color;
    delete []parent;
    delete []dist;
    delete []f;
    color=0;
    parent=0;
    dist=0;
    f=0;
    for(int i=0;i<nVertices;i++)
    {
        delete []matrix[i];
    }
    delete []matrix;
}
//**********************Graph class ends here******************************

//============disjoint set union==============
struct edges{
	int u;
	int v;
	int w;
	struct edges *next;
};
typedef struct edges Edges;

bool myCompare(Edges a,Edges b){
	return a.w<b.w;
}

void dsuInitialize(int arr[],int size[],int n){
	for(int i=0;i<n;i++){
		arr[i]=i;
		size[i]=1;
	}
}

int getRoot(int arr[],int i){
	while(arr[i]!=i){
		arr[i]=arr[arr[i]];
		i=arr[i];
	}
	return i;
}

void myUnion(int arr[],int size[],int u,int v){
	int root_u=getRoot(arr,u);
	int root_v=getRoot(arr,v);
	if(size[root_u]<size[root_v]){
		arr[root_u]=arr[root_v];
		size[root_v]+=size[root_u];
	}
	else{
		arr[root_v]=arr[root_u];
		size[root_u]+=size[root_v];
	}
}

bool myFind(int arr[],int u,int v){
	if(getRoot(arr,u)==getRoot(arr,v))
		return true;
	else
		return false;
}


void myPrint(string s,Edges *p){
	int d=0;
	cout<<endl<<s<<endl;
	while(p){
		d+=p->w;
		cout<<(p->u)+1<<" "<<(p->v)+1<<endl;
		p=p->next;
	}
	cout<<d<<endl;
}

//===disjoint set union ends here======

Edges *mySort(Edges *head){
	int i,j,k,temp,data;
	Edges *cur=head;
	Edges *next;
	
	while(cur){
		next=cur->next;
		while(next){
			if(cur->w>next->w){
				temp=cur->u;
				cur->u=next->u;
				next->u=temp;
				temp=cur->v;
				cur->v=next->v;
				next->v=temp;
				temp=cur->w;
				cur->w=next->w;
				next->w=temp;
			}
			next=next->next;
		}
		cur=cur->next;
	}
	return head;
}


Edges *Kruskal_MST1(Edges *root,int n){
	if(root==NULL)
		return root;
	root=mySort(root);
	//sort(root,root+n,myCompare);
	int arr[n];
	int size[n];
	dsuInitialize(arr,size,n);
	Edges *tree=NULL,*q=root;
	int d=0;
	while(q->next){
		q=q->next;
		d++;
	}
	d++;
	q=root;
	int i,u,v,w;
	while(d--){
		u=q->u;
		v=q->v;
		w=q->w;
		if(!myFind(arr,u,v)){
			Edges *p=new Edges;
			p->u=u;
			p->v=v;
			p->w=w;
			p->next=tree;
			tree=p;
			myUnion(arr,size,u,v);
		}
		q=q->next;
	}
	return tree;
}


void Kruskal_MST2(Edges graphEdges[],int n,int m){
	sort(graphEdges,graphEdges+m,myCompare);
	int weight=0,nEdges=0,nI=0;
	int arr[n],size[n];
	dsuInitialize(arr,size,n);
	while((nEdges<n-1)||(nI<m)){
		if(!myFind(arr,graphEdges[nI].u,graphEdges[nI].v)){
			myUnion(arr,size,graphEdges[nI].u,graphEdges[nI].v);
			weight+=graphEdges[nI].w;
			cout<<graphEdges[nI].u+1<<" "<<graphEdges[nI].v+1<<endl;
			nEdges++;
		}
		nI++;
	}
	cout<<weight<<endl;
}


Edges *Kruskal_SBMST(Edges *root,int n){
	int i,u,v,w,min=INFINITY;
	Edges *mstree=Kruskal_MST1(root,n);
	Edges *q,*t,*p;
	p=mstree;
	int minweight=0;
	while(p){
		minweight+=p->w;
		p=p->next;
	}
	p=mstree;
	while(mstree){
		Edges *q1=root,*p1=NULL,*t1;
		while(q1){
			Edges *r1=new Edges;
			while(q1->u==mstree->u&&q1->v==mstree->v&&q1->w==mstree->w){
				q1=q1->next;
			}
			r1->u=q1->u;
			r1->v=q1->v;
			r1->w=q1->w;
			r1->next=p1;
			p1=r1;
			q1=q1->next;	
		}
		t1=p1;
		q=Kruskal_MST1(p1,n);
		p=q;
		int d=0;
		while(p){
			d+=p->w;
			p=p->next;
		}
		if(min>d&&d==minweight){

			min=d;
			t=q;
		}
		mstree=mstree->next;
	}
	return t;
}


int main(){
	int n,m;
	cin>>n>>m;
	Graph g;
	g.setnVertices(n);
	int u,v,w;
	Edges *root=NULL,*p,*tree2;
		
	Edges graphEdges[m];
	for(int i=0;i<m;i++){
		cin>>u>>v>>w;
		g.addEdge(u-1,v-1,w);
		Edges *q=new Edges;
		q->u=u-1;
		q->v=v-1;
		q->w=w;
		graphEdges[i].u=u-1;
		graphEdges[i].v=v-1;
		graphEdges[i].w=w;
		q->next=root;
		root=q;
	}
	
	cout<<endl<<"MST"<<endl;
	Kruskal_MST2(graphEdges,n,m);
	tree2=Kruskal_SBMST(root,n);
	p=tree2;
	myPrint("SBMST",p);

	
	return 0;
}

/*
Input
n m
u v w

5 7
1 2 1
1 3 7
2 3 5
2 4 4
2 5 3
3 5 6
4 5 2

 */