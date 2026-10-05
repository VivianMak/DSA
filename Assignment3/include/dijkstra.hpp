#pragma once
#include "graph.hpp"
#include <unordered_map>


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
Keep track of the algorithm compute as a struct

@param graph: 
@param source:
*/

template <typename T, typename Cost>
DijkstraResult<T, Cost> dijkstra(const DirectedGraph<T, Cost>& graph, const T& source) {

}


} // namespace graph