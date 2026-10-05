#pragma once

#include "graph.hpp"
#include "priority_queue.hpp"

#include <unordered_map>
#include <limits>
#include <vector>
#include <algorithm>


// header only since we are using template types
namespace Graph{


/*
Keep track of the algorithm compute as a struct

dist: length of shortest known path
prev: for each vertex, the vertex's predescesor on shortest path
*/

template <typename T, typename Cost = double>
struct DijkstraResult {
    std::unordered_map<T, Cost> dist;
    std::unordered_map<T, T> prev;
};


/* 
* Dijkstra's algorithm
* 
* @param graph: adjacency graph to search thorugh
* @param source: the beginning vertex to start from
* 
* @return DijkstraResult which contains a set of distances and predecessors
*/
template <typename T, typename Cost>
DijkstraResult<T, Cost> dijkstra(const DirectedGraph<T, Cost>& graph, const T& source) {

    DijkstraResult<T, Cost> result;

    // Check if source exists
    if(graph.getVerticies().count(source) == 0){
        return result;
    }

    // Set all verticies at inf distance
    for (const T& v : graph.getVerticies()) {
        result.dist[v] = std::numeric_limits<int>::max();
    }

    // Set source vertex to 0 -- initializes to 0 dependant on the type
    result.dist[source] = Cost{};

    // Initialize priority queue 
    PriorityQueue::MinPriorityQueue<T, Cost> queue;
    queue.addWithPriority(source, Cost{});

    while (!queue.isEmpty()){
        // Deference the value to next (because we check empty already, deferencing is safe; could do .next().value() to throw error)
        T vertex = *queue.next();
    

        // Find all neighbors of current vertex
        for (const auto& [neighbor, weight]: graph.getEdges(vertex)){

            // Calc cost of neighbors through vertex
            Cost c = result.dist[vertex] + weight;

            // Check if its better than prev route or inf
            if (c < result.dist[neighbor]){
                result.dist[neighbor] = c;         // save new shortest distance
                result.prev[neighbor] = vertex;    // save predecescor
            }

            // Adjust its priority queue or add
            if (!queue.addWithPriority(neighbor, c)) {
                queue.adjustPriority(neighbor, c);
            } else {
                queue.addWithPriority(neighbor, c);
            }
        }
    }
    
    return result;

} // end dijkstra

/*
* Rebuild the shortest path from the source to [target] using the prev map.
*
* @param result: the processed graph
* @param target: the end node
*
* @return the vertices from source to target in order, or an empty vector
*/
template <typename T, typename Cost>
std::vector<T> reconstructPath(const DijkstraResult<T, Cost>& result, const T& target) {

    std::vector<T> path;

    // Check if target is a reachable path
    if (result.dist.find(target) == result.dist.end() || 
        result.dist.find(target)->second == std::numeric_limits<int>::max()){
            return path;
        }

    // Retrace steps
    T curr_vertex = target;
    path.push_back(curr_vertex);

    auto p = result.prev.find(curr_vertex);
    while (p != result.prev.end()) {
        curr_vertex = p->second;
        path.push_back(curr_vertex);
        p = result.prev.find(curr_vertex);
    }


    // Unflip the target to source path
    std::reverse(path.begin(), path.end());
    return path;

}


} // namespace graph