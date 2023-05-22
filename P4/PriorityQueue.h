#ifndef PRIORITYQUEUE_H
#define PRIORITYQUEUE_H

#include <iostream>
#include <vector>
#include <tuple>

class PriorityQueue
{
public:
    PriorityQueue(int maxCount);
    void Init(std::vector<std::tuple<int, int, int>> *vertexList);
    std::tuple<int, int, int> HeapExtractMin();
    bool Modify(int i, int w, int parent);
    bool Contains(int v);
    bool IsEmpty();
    int GetKey(int v);

private:
    int count;
    void Exchange(int a, int b);
    void MinHeapify(int i);
    int Parent(int i);
    int Left(int i);
    int Right(int i);
    std::vector<std::tuple<int, int, int>> arr; // The actual priority queue.
    std::vector<int> locations;                 // References for vertex -> PQ index. Allows indexing PQ in O(1) time.
    const int MAX_UNIQUE_KEYS = 50001;
};

#endif
