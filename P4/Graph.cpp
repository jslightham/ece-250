#include "Graph.h"
#include <limits.h>
#include "PriorityQueue.h"
#include "illegal_exception.h"

/// @brief Create a new graph
/// @param maxCount The maximum number of elements the graph is required to store
/// @param mst A flag to enable MST (enabling makes the runtime of the graph worse)
Graph::Graph(int maxCount, bool mst)
{
    vertexList.reserve(maxCount);
    if (!mst)
        pq = new PriorityQueue(maxCount);
    this->maxCount = maxCount;
    this->mstEnabled = mst;
}

Graph::~Graph()
{
    delete pq;
}

/// @brief Insert an edge from vertex a to b, with weight w. When MST flag is true, it is invalid to pass in edges that already exist in the graph.
/// @param a Vertex a
/// @param b Vertex b
/// @param weight The weight of the edge to insert
/// @return True if successful, false otherwise
/// @throws illegal_exception if given invalid input
bool Graph::Insert(int a, int b, int weight)
{
    // Check input validity
    if (a > 50000 || a < 1 || b > 50000 || b < 1 || weight < 1)
    {
        throw illegal_exception();
    }

    // Check if the node already exists. Skip this check when the MST is disabled - allows efficient inserts for building tree.
    int count = adjacencyList[a].size();
    if (!mstEnabled)
    {

        for (int i = 0; i < count; i++)
        {
            int currentData = std::get<0>(adjacencyList[a][i]);
            if (currentData == b)
                return false;
        }
    }

    // Add the b vertex to the adjacency list for a
    adjacencyList[a].push_back(std::make_tuple(b, weight));

    // Add the vertex a to the vertexList, if a has never been added to the graph
    if (count == 0)
        vertexList.insert(vertexList.begin() + vertexList.size(), std::make_tuple(a, INT_MAX, -1));

    // Add a vertex to the adjacency list for b, and insert b into vertexList if required
    count = adjacencyList[b].size();
    adjacencyList[b].push_back(std::make_tuple(a, weight));
    if (count == 0)
        vertexList.insert(vertexList.begin() + vertexList.size(), std::make_tuple(b, INT_MAX, -1));

    return true;
}

/// @brief Delete vertex a from the graph.
/// @param a The vertex to delete from the graph.
/// @return True if successful, false otherwise.
/// @throws illegal_exception if given invalid input.
bool Graph::Delete(int a)
{
    // Check input conditions
    if (a > 50000 || a < 1)
    {
        throw illegal_exception();
    }

    // Ensure the vertex is in the graph
    int count = adjacencyList[a].size();
    if (count == 0)
        return false;

    // Remove all references to the vertex in the adjacency lists of other vertices, and in the vertexList.
    while (count != 0)
    {
        std::tuple<int, int> lastData = adjacencyList[a][count - 1];
        adjacencyList[a].pop_back();

        // Remove vertex from all adjacency lists
        for (int j = 0; j < adjacencyList[std::get<0>(lastData)].size(); j++)
        {
            if (std::get<0>(adjacencyList[std::get<0>(lastData)][j]) == a)
            {
                adjacencyList[std::get<0>(lastData)].erase(adjacencyList[std::get<0>(lastData)].begin() + j);
            }
        }

        // If removing vertex a causes any adjacency lists to become empty, remove that vertex from the vertexList.
        if (adjacencyList[std::get<0>(lastData)].size() < 1)
        {
            for (int j = 0; j < vertexList.size(); j++)
            {
                if (std::get<0>(vertexList[j]) == std::get<0>(lastData))
                    vertexList.erase(vertexList.begin() + j);
            }
        }

        count--;
    }

    // Remove a from the vertex list.
    for (int i = 0; i < vertexList.size(); i++)
    {
        if (std::get<0>(vertexList[i]) == a)
            vertexList.erase(vertexList.begin() + i);
    }

    return true;
}

/// @brief Get a vector containing the adjacent vertices to a
/// @param a The vertex to check
/// @return A vector of all vertices
/// @throws illegal_exception if given invalid input.
std::vector<std::tuple<int, int>> *Graph::GetAdjacent(int a)
{
    if (a > 50000 || a < 1)
    {
        throw illegal_exception();
    }

    return &adjacencyList[a];
}

/// @brief Compute the MST of the graph
/// @param out A vector to output the resulting MST edges in
/// @return The cost of the MST
int Graph::MST(std::vector<std::tuple<int, int, int>> *out)
{
    // If there are no nodes, or somehow only one node.
    if (vertexList.size() < 2)
        return 0;

    // When there is only one edge, that edge is the MST
    if (vertexList.size() < 3)
    {
        out->push_back(std::make_tuple(std::get<0>(vertexList[0]), std::get<0>(vertexList[1]), std::get<1>(adjacencyList[std::get<0>(vertexList[0])][0])));
        return std::get<1>(adjacencyList[std::get<0>(vertexList[0])][0]);
    }

    // Attribution: Some of the Pseudocode used to write this function is from the CLRS textbook.
    int cost = 0;
    pq->Init(&vertexList);

    // Apply Prim's Algorithm using a PriorityQueue.
    // Extract elements from the PQ until it is empty
    while (!pq->IsEmpty())
    {
        // Extract the element with the lowest weight
        std::tuple<int, int, int> u = pq->HeapExtractMin();

        // Prevent insertion of first node (or any infinite weights).
        if (std::get<1>(u) != INT_MAX)
        {
            out->push_back(std::make_tuple(std::get<2>(u), std::get<0>(u), std::get<1>(u)));
            cost += std::get<1>(u);
        }

        // Iterate through all of the adjacent vertices
        for (int i = 0; i < adjacencyList[std::get<0>(u)].size(); i++)
        {
            std::tuple<int, int> v = adjacencyList[std::get<0>(u)][i]; // The vertex being examined

            // If the current path is better than the stored path, update it.
            if (pq->Contains(std::get<0>(v)) && std::get<1>(v) < pq->GetKey(std::get<0>(v)))
            {
                pq->Modify(std::get<0>(v), std::get<1>(v), std::get<0>(u));
            }
        }
    }
    return cost;
}

/// @brief Get the number of vertices in the graph
/// @return The number of vertices in the graph
int Graph::GetVertexCount()
{
    return vertexList.size();
}
