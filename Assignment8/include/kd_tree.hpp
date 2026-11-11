#pragma once

#include <array>
#include <cstddef>
#include <cmath>
#include <stdexcept>

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
            int depth;

            // Initialize node
            Node(const array<double, T>& point) : 
                point(point), left(nullptr), right(nullptr) {}
        };

        Node* root;


        Node* build_tree(std::vector<Point> points, int depth){

            int n = sizeof(points);

            // Mod dimensions
            int dim = depth % K;

            // Median index to find
            int median = n - (n / i);

            // Get the left/right leaf via quick select of median
            int i = QS::quick_select(points, l, r, median, dim);

            // Create node and recursively make subtree
            Node n.point(points[i]);
            n.depth = depth;
            n.left = build_tree(points[0 : i-1], depth + 1);
            n.right = build_tree(points[i+1 : n-1], depth + 1)

            // Return the root of the tree
            return n;         
        }


        /**
         * Return the distance between the node and target node.
         * Assume using euclidean distance.
         */
        double dist(Node* node, Point target){

            // 2D point (x,y)
            if (std::size(node->point) == 2){
                return std::sqrt(
                    (node->point(0) - target(0) * node->point(0) - target(0)) + 
                    (node->point(1) - target(1) * node->point(1) - target(1))
                );
            }

            // 3D point (x,y,z)
            if (std::size(node->point) == 3){
                return std::sqrt(
                    (node->point(0) - target(0) * node->point(0) - target(0)) + 
                    (node->point(1) - target(1) * node->point(1) - target(1))
                );
            }


            throw std::out_of_range("Can't be computed using Euclidean distance.");

        }

        
        Node* closest(Point target, Node* a, Node*b){

            // Find smallest distance
            if (dist(a, target) < dist(b, target))
                return a;
            
            // Return node
            return b;
        }


        
    
        public:
            KDTree() : root(nullptr) {}

            /**
             * Find nearest neighbors
             * 
             * @param root: root node
             * @param target: target point, doesn't have to be in the tree
             * @param depth: the total depth of the tree
             * 
             * @return the best (closest) node to the target point
             */

            Node nearestNeighbors(Node* root, const Point& target, int depth){

                // Check valid tree
                if (root == nullptr) return nullptr;

                Node temp;

                if (target(depth % K) < root.point(depth % K)){
                    temp = nearestNeighbors(root->left, target, depth+1);
                    other = root->right;
                } else{
                    temp = nearestNeighbors(root->right, target, depth+1);
                    other = root->left;
                }

                Node best = closest(target, root, temp);

                // Recurse back up the tree and check the other leaf
                temp = nearestNeighbors(other, target, depth+1);
                best = closest(target, best, temp);


                return best;
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