# algorithms
Collections of Different Algorithms implemented in c++
## Algorithms Implemented
* Skyline
* Kruskal's Algorithm to find Minimum Spanning Tree
* Set Cover Problem
* Evaluation of Postfix Expression
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
S1 = {1, 2}

S2 = {2, 3, 4, 5}

S3 = {6, 7, 8, 9, 10, 11, 12, 13}

S4 = {1, 3, 5, 7, 9, 11, 13}

S5 = {2, 4, 6, 8, 10, 12, 13}

Let the cost of every set be same.

##### Output

The optimal solution is {S4, S5}

#### Evaluation of Postfix Expression
The Postfix notation is used to represent algebraic expressions. The expressions written in postfix form are evaluated faster compared to infix notation as parenthesis are not required in postfix. We have discussed infix to postfix conversion. In this post, evaluation of postfix expressions is discussed.

Following is an algorithm for evaluation postfix expressions.

1) Create a stack to store operands (or values). 
2) Scan the given expression and do the following for every scanned element. 
…..a) If the element is a number, push it into the stack 
…..b) If the element is an operator, pop operands for the operator from the stack. Evaluate the operator and push the result back to the stack 
3) When the expression is ended, the number in the stack is the final answer 

##### Input
Postfix expression: 53+62/*35*+
##### Output
The result is: 39

