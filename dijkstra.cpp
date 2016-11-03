/*
shortest path problem solved using Dijkstra's algorithm
@Author: Shanfang
date: Nov. 3rd 2016
*/

/*
algorith description
step1: 
initiaize distanceFromSource[i] = a[sourceVertex[i]], 1<= i =< n;
set predecessor[i] = sourceVertex for all i adjacent from sourceVertex;
set predecessor[sourceVertex] = 0 and predecessor[i] = -1 for all other vertices;
create a list newReachableVertices of all vertices for which prececessor[i] > 0
(i.e.,newReachableVertices now contains all vertices that are adjacent from sourceVertex);
step2:
if newReachableVertices is empty, terminate. Otherwise, go to step 3'
step3:
delete form newReachableVertices the vertex i with least value of distanceFromSource(ties are broken arbitrarily);
step4:
update distanceFromSource[j] to min{distanceFromSource[j], distanceFromSource[i]+a[i][j]} for alvertices j adjacent from i.
if distanceFromSource[j], set prececessor[j] = i and add j to newReachableVertices in case it isn't already there. Go to step 2;
*/
