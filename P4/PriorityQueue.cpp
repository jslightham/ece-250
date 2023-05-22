#include "PriorityQueue.h"
#include <limits>

// Attribution: Some of the Pseudocode used to write these functions is from the CLRS textbook.

PriorityQueue::PriorityQueue(int maxCount)
{
    count = 0;
    locations.reserve(maxCount);
    arr.reserve(maxCount);
    for (int i = 0; i < maxCount; i++)
    {
        locations[i] = -1;
    }
}

/// @brief Initialize the priority queue with the given vector of tuples. The tuples should be in the format: <vertex, weight, parent>
/// @param vertexList The vector of tuples to insert into the priority queue.
void PriorityQueue::Init(std::vector<std::tuple<int, int, int>> *vertexList)
{
    count = vertexList->size();

    for (int i = 0; i < count; i++)
    {
        arr[i] = vertexList->at(i);
        locations[std::get<0>(vertexList->at(i))] = i;
    }
}

/// @brief Modify the weight and/or the parent of vertex v
/// @param v The vertex to modify (not the index in the priority queue)
/// @param w The weight to set
/// @param parent The parent to set
/// @return True if successful, false otherwise
bool PriorityQueue::Modify(int v, int w, int parent)
{
    if (count < 1)
        return false;

    int i = locations[v];
    if (i < 0)
        return false;

    std::get<1>(arr[i]) = w;
    std::get<2>(arr[i]) = parent;
    while (i > 0 && std::get<1>(arr[Parent(i)]) > std::get<1>(arr[i]))
    {

        Exchange(i, Parent(i));
        i = Parent(i);
    }
    return true;
}

/// @brief Extract the smallest value from the priority queue (the topmost element, since this is a min pq).
/// @return The element in the priority queue if not empty, or a tuple of all ints <-1, -1, -1> if empty
std::tuple<int, int, int> PriorityQueue::HeapExtractMin()
{
    // Signal no minimum element if there are no elements.
    if (IsEmpty())
        return std::make_tuple<int, int, int>(-1, -1, -1);

    std::tuple<int, int, int> min = arr[0];

    locations[std::get<0>(arr[count - 1])] = 0;
    locations[std::get<0>(min)] = -1;
    arr[0] = arr[count - 1];
    count--;
    MinHeapify(0);
    return min;
}

/// @brief Run the MinHeapify algorithm on the pq.
/// @param i The index (not the vertex).
void PriorityQueue::MinHeapify(int i)
{
    int l = Left(i);
    int r = Right(i);

    int smallest = i;

    if (l < count && std::get<1>(arr[l]) < std::get<1>(arr[i]))
        smallest = l;

    if (r < count && std::get<1>(arr[r]) < std::get<1>(arr[smallest]))
        smallest = r;

    if (smallest != i)
    {
        Exchange(i, smallest);
        MinHeapify(smallest);
    }
}

/// @brief Get a boolean value to determine if the priority queue is empty
/// @return True if the priority queue is empty, false otherwise.
bool PriorityQueue::IsEmpty()
{
    return count < 1;
}

/// @brief Check if the priority queue contains a vertex v.
/// @param v The vertex (not index) to check.
/// @return True if the vertex (not index) is contained in the priority queue, false otherwise.
bool PriorityQueue::Contains(int v)
{
    return locations[v] != -1;
}

/// @brief Get the key (weight) of a vertex (not index) in the priority queue
/// @param v The vertex (not index) to get the weight for
/// @return The key (weight) of the vertex
int PriorityQueue::GetKey(int v)
{
    return std::get<1>(arr[locations[v]]);
}

/// @brief Swap the elements of index a and index b (not the vertex number)
/// @param a The index (not vertex) of the element to swap
/// @param b The index (not vertex) of the element to swap
void PriorityQueue::Exchange(int a, int b)
{
    locations[std::get<0>(arr[a])] = b;
    locations[std::get<0>(arr[b])] = a;

    std::tuple<int, int, int> temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}

/// @brief Given an index (not vertex), get the parent of that index (not vertex)
/// @param i The index (not vertex) to get the parent of
/// @return The index (not vertex) of the parent
int PriorityQueue::Parent(int i)
{
    return (i - 1) / 2;
}

/// @brief Given an index (not vertex), get the left child of that index (not vertex)
/// @param i The index (not vertex) to get the left child of
/// @return The index (not vertex) of the left child
int PriorityQueue::Left(int i)
{
    return 2 * i + 1;
}

/// @brief Given an index (not vertex), get the right child of that index (not vertex)
/// @param i The index (not vertex) to get the right child of
/// @return The index (not vertex) of the right child
int PriorityQueue::Right(int i)
{
    return 2 * i + 2;
}
