#pragma once

#include <iostream>
#include <unordered_set>
#include <unordered_map>

namespace Graph{

// name of graph node can be any type
template <typename T, typename Cost = double>
class DirectedGraph{
    
    private:
        std::unordered_set<T> verticies;        // list of verticies
        std::unordered_map<T, std::unordered_map<T, Cost>> adjacency; // from: (to, cost)
        

    public:

        /*
        * @return all vertices in the graph (a const reference)
        */
        const std::unordered_set<T>& getVerticies() const{
            return verticies;
        }
        
        /*
        * Add an edge between [from] and [to] with edge weight [cost]
        */
        void addEdge(T from, T to, Cost cost){

            // Cretaing new node auto checks if from/to node exists
            verticies.insert(from);
            verticies.insert(to);

            // add edge to adjacency matrix -- currently overwrites cost
            adjacency[from][to] = cost;
        }

        /*
        * @return a map where each key represents a vertex connected to [from] and the value represents the edge weight
        */
        std::unordered_map<T, Cost> getEdges(T from) const{

            // Check if it is a valid vertex
            if (verticies.find(from) == verticies.end()){
                std::cerr << "Error: Graph vertex does not exist, no valid edges." << std::endl;
                return {};
            }

            // Check if its an end vertex
            auto it = adjacency.find(from);
            if (it == adjacency.end()) {
                return {};   // vertex exists but has no outgoing edges
            }
            return it->second;
        }

        /*
        * remove all edges and vertivies from the graph
        */
        void clear(){
            verticies.clear();
            adjacency.clear();
        }
};
}