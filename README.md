# Shortest-Paths
Dijkstra and Bellman Ford sortest paths implemented in C++

------DOCUMENTATION-------
A Makefile has been included. After the make command has been issued you will be prompted for a source node and a destination node, next the criteria for the relevant shortest path algorithm will be evaluated. The result of this will be output along with which shortest path algorithm is being executed. Enter -1 while being prompted for another destination node to exit. The appropriate shortest path algorithm will be preformed and the shortest path will be output in the format destination <-"intermediate Nodes" <- source node. On the very next line the distance of this shortest path will be output. Please note that if a path doesn't exist from your chosen source node to your chosen destination node you will be notified and the distance of the path output will be equal to INT_MAX.

Change the file name being passed to loadFromFile to test all the different input files.

