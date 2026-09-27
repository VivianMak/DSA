#pragma once

#include <vector>
#include <tuple>


namespace Graph{

    using edgeList = std::vector<std::pair<Node*, double>>;

    struct Node
            {
                // int id;

                // max 4 or 8? -- should i preallocate?
                // each vertex is a pair of <node*, and edge weight>
                edgeList parent_verticies;
                edgeList child_verticies;
            };

    class Graph{
        private:
            std::vector<Node> graphNodeList_;
            

        public:

            std::vector<Node> getVerticies(){

            }

            void addEdge(Node* from, Node* to, double weight){
                // check if the "from" node exists
                // if it doesn't exist create it first
                Node* node = new Node(from)
            }

            edgeList getEdges(Node* from){

                // Create an empty vector

            }

            /*
            * remove all edges and vertivies from the graph
            */
            void clear(){
                // recursive??

            }

    }
}

// Functions

void getVerticies()
// return the verticies int he graph

void addEdge(from, to, cost)
// Add edge between from, to with edge weight

woid getEdges(from)
// Get all edges that begin at from
// return a map where each key represents a vertex connected to from and the value represents the edge weight
//Map <vertex, double>

void clear()
// remove all edges and vertivies from the graph