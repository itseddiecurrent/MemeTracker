## Team members: Edward Tang, Jack Shao, John Wachala

### Functionality and Description

In our dataset obtained from MemeTracker http://snap.stanford.edu/data/memetracker9.html, each primary link is denoted by a capital letter "P" in the front, and each primary link has a corresponding timestamp on its next line, denoted by "T". The goal of this project is to find the correlation of any two primary links in the dataset based on the timestamp. The smaller the correlations are, the closer the timestamps of the links are. 

The algorithms we have used include DFS Traversal, Iterative Deepening DFS, and Prim's Algorithm. In main.cpp, we insert all the primary links from a chosen dataset in the format of MemeTracker. We connect each two vertices with an edge and initialize their edge weight to the number of vertices. For each two vertices with the same identical timestamp, we decrease their edge weight in order for the Prim's Algorithm to take priority with them when generating the Minimum Spanning Tree. Then we use DFS traversal to the MST to return a vector of vertices being visited with the DFS Traversal. Then, we find the minimum correlation of the vertices by applying the Iterative Deepening DFS, in which it returns whether or not one vertex can reach another within a certain limit of depth. The minimum number for which the Iterative Deepening DFS returns true between two vertices represents their correlation. 

### Algorithm and Runtime

We have decided not to implement the Fiboacci heap in our Prim's Algorithm implementation for its complexity and difficulty to make them agree with the class design of our graph class, mostly obtained from lab_ml except the additional algorithm. The decision of not using Fibonacci heaps comes at the expense of the runtime efficiency, and also the runtime of inserting edges among vertices is expected to be long. The original dataset could be as big as 4.12GB, in which most terminals won't be able to handle the runtime facing the huge amount of vertices, so we encourage users to truncate the dataset to a smaller subset if possible. 
