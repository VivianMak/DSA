#pragma once

#include <array>
#include <cstddef>

#include "quick_select.hpp"


namespace KDTree{

// K-dimensional point
template <std::size_t K>
using Point = std::array<double, K>;

template <std::size_t T>
class KDTree{


    private:

        struct Node{
            Point<T> point;
            Node* left;
            Node* right;

            // Initialize node
            Node(const array<double, T>& point) : 
                point(point), left(nullptr), right(nullptr) {}
        };

        Node* root;


        Node* build_tree(std::vector<points> points, int depth){

            // Get the left/right leaf via quick select of median
            int i = QS:quick_select(points, depth);


        }


        

        /**
         * Return the distance between the node and target node
         */
        double dist_func(Node* node, Node* target){

        }

        Node* nearest_helper(Node* root, const point& target, int depth)


        
    
        public:
            KDTree() : root(nullptr) {}

            /**
             * Find nearest neighbors
             */

            point nearestNeighbors(const point& target){

                // Check valid tree
                if (root == nullptr) return nullptr;

                // Sort list accordig to 1st dimension


                // Get the median


                // Find the 



                // Recurse back up the tree and check the other leaf


                return closest;
            }


    
};
} // namespace KDTree



class KDTree<K>
  private:
    struct Node { point, left, right }
    Node* root
    Node*  build_helper(points, depth)
    Node*  nearest_helper(Node* node, const point& target, int depth)
    double dist_sq(const point& a, const point& b)
    void   destroy(Node* node)
  public:
    KDTree(const vector<point>& points)   // calls build_helper
    ~KDTree()                             // calls destroy
    point nearest(const point& target)    // calls nearest_helper