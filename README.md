# algorithms
Collections of Different Algorithms implemented in c++
## Algorithms Implemented
* Skyline
* Kruskal's Algorithm to find Minimum Spanning Tree
* Set Cover Problem
## Description
### Skyline
Given n rectangular buildings in a 2-dimensional city, computes the skyline of these buildings, eliminating hidden lines. 
The main task is to view buildings from aside and remove all sections that are not visible. 
#### Input
All buildings share common bottom and every building is represented by a pair (left, ht)
* left: is x coordinated on the left side (or wall).
* ht: is the height of the building.
#### Output
A skyline is a collection of rectangular strips. 
A rectangular strip is represented as a pair (left, ht) where left is x coordinate of the left side of strip and ht is the height of strip.<br/>
![output_skyline](images/output_skyline.png)
###  Minimum Spanning Tree
#### Spanning tree
A spanning tree is a sub-graph of an undirected connected graph, which includes all the vertices of the graph with a minimum possible number of edges. If a vertex is missed, then it is not a spanning tree.

The edges may or may not have weights assigned to them.
#### Minimum Spanning Tree
A minimum spanning tree is a spanning tree in which the sum of the weight of the edges is as minimum as possible.
![min_spanning_tree_example](images/mst.jpg)
##### Kruskal’s Algorithm
Kruskal’s Algorithm builds the spanning tree by adding edges one by one into a growing spanning tree. Kruskal's algorithm follows greedy approach as in each iteration it finds an edge which has least weight and add it to the growing spanning tree.

##### Algorithm Steps:
* Sort the graph edges with respect to their weights.
* Start adding edges to the MST from the edge with the smallest weight until the edge of the largest weight.
* Only add edges which doesn't form a cycle , edges which connect only disconnected components.

#### Set Cover Problem
Given a universe U of n elements, a collection of subsets of U say S = {S1, S2…,Sm} where every subset Si has an associated cost. Find a minimum cost subcollection of S that covers all elements of U.
##### Input
  U = {1,2,3,4,5}
  
  S = {S1,S2,S3}
   
  S1 = {4,1,3},    Cost(S1) = 5
  
  S2 = {2,5},      Cost(S2) = 10
  
  S3 = {1,4,3,2},  Cost(S3) = 3

##### Output
Minimum cost of set cover is 13 and set cover is {S2, S3}

There are two possible set covers {S1, S2} with cost 15
and {S2, S3} with cost 13.

##### Approximate Greedy Algorithm:
Let U be the universe of elements, {S1, S2, … Sm} be collection of subsets of U and Cost(S1), C(S2), … Cost(Sm) be costs of subsets.

1. Let I represents set of elements included so far.  Initialize I = {}

2. Do following while I is not same as U.


    a. Find the set Si in {S1, S2, ... Sm} whose cost effectiveness is 
       smallest, i.e., the ratio of cost C(Si) and number of newly added 
       elements is minimum. 
       Basically we pick the set for which following value is minimum.
           Cost(Si) / |Si - I|
           
           
    b. Add elements of above picked Si to I, i.e.,  I = I U Si

