#ifndef TRIE_H
#define TRIE_H

#include <iostream>
#include <vector>
#include <tuple>
#include "PriorityQueue.h"

class Graph
{
public:
    Graph(int maxCount, bool mst);
    ~Graph();
    bool Insert(int a, int b, int weight);
    bool Delete(int a);
    std::vector<std::tuple<int, int>> *GetAdjacent(int a);
    int GetVertexCount();
    int MST(std::vector<std::tuple<int, int, int>> *outList);

private:
    PriorityQueue *pq;
    std::vector<std::tuple<int, int>> adjacencyList[50001]; // An array of vectors of tuples <node2, weight>
    std::vector<std::tuple<int, int, int>> vertexList;      // List of all vertices in the graph stored as <node1, inf, -1>
    int maxCount;
    bool mstEnabled;
};
#endif
