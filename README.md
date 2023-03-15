# Fibonacci heap

Fibonacci Heap is a collection of trees with min-heap or max-heap property. In Fibonacci Heap, trees can have any shape even all trees can be single nodes.A Heap is a special Tree-based data structure in which the tree is a complete binary tree.


## Operations

* Make heap from scratch
* Insert element,
* Find minimum element
* Delete minimum element
* Decrease an element
## Code

* Made a node for Fibonacci heap. ( contains key, parent, child, left, right, degree, mark )
* Code accepts input in form of heap trees or in the form of single nodes.
* Made a queue from scratch for making heap of type node pointer. program accepts node value and node degree in text file and then makes a new node. We push it into queue and connected it according to degree. We pop the node and take new node from the queue. 
* Ex. Suppose a node has 3 child then we will read 3 node values (key and degree) from text file and then make 3 nodes and push it into queue, make circular doubly linked list, assign their parent and connect parent to any one child. Then we pop the parent node and take next node from queue.
* Code has 4 class one for fb node, one for queue node, one for queue, one for fb
 

## Demo

To compile code

```
g++ fibonacci_heap.cpp -o fibonacci_heap
```

To run
```
./fibonacci_heap
```

An example for giving input nodes in text file:

```
4          ( no. of roots )
7 3 11 19  ( all-roots )
7 0        ( node-key, degree )
3 1        ( node-key, degree )
8          ( all children of above node ) 
8 0        ( node-key, degree )
11 3       ( node-key,degree )
15 17 100  ( all children of above node )
15 1
18
18 0
17 0
100 0
19 2
20 25
20 1
28
28 0
25 0
```
