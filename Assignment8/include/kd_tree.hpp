#pragma once

#include <array>
#include <cstddef>
#include <cmath>
#include <stdexcept>
#include <vector>

#include "quick_select.hpp"


namespace KDTree{

// K-dimensional point
template <std::size_t K>
using Point = std::array<double, K>;

template <std::size_t K>
class KDTree{


    private:

        struct Node{
            Point<K> point;
            Node* left;
            Node* right;

            // Initialize node
            Node(const Point<K>& point) : 
                point(point), left(nullptr), right(nullptr) {}
        };

        // Root node
        Node* root;
        // All points on the tree (BF search)
        std::vector<Point<K>> all_points;


        /**
         * Building subtree from left to right element. 
         * Points at next nodes are detected by quick select
         * 
         * @param points: all points to build tree
         * @param l:
         * @param r: 
         * @param depth:
         * 
         * @return the root of the subtree or null
         */
        Node* build_tree(std::vector<Point<K>>& points, int l, int r, int depth){
                       
            // Add base case for recursion
            if (l > r){
                return nullptr;
            }

            // Mod dimensions
            int dim = depth % K;

            // Median index to find
            int k = (r - l) / 2 + 1;

            // Get the left/right leaf via quick select of median
            int med = QS::quick_select(points, l, r, k, dim);

            // Create node and recursively make subtree
            Node* n = new Node(points[med]);
            n->left = build_tree(points, l, med-1, depth + 1);
            n->right = build_tree(points, med+1, r, depth + 1);

            // Return the root of the tree
            return n;         
        }


        /**
         * Return the squared distance between two points.
         * Assume using euclidean distance.
         *
         * @param a: first K dimensional point
         * @param b: second K dimensional point
         */
        double dist_sq(const Point<K>& a, const Point<K>& b){

            double sum = 0.0;

            // Add the squared difference in each dimension (x, y, z, ...)
            for (std::size_t i = 0; i < K; i++){
                double diff = a[i] - b[i];
                sum += diff * diff;
            }

            return sum;
        }

        
        Node* closest(const Point<K>& target, Node* a, Node*b){

            // Check for null node
            if (a == nullptr) return b;
            if (b == nullptr) return a;

            // Find smallest distance
            if (dist_sq(a->point, target) < dist_sq(b->point, target))
                return a;
            
            // Return node
            return b;
        }

        Point<K> closest(const Point<K>& target, const Point<K>& a, const Point<K>& b){

            // Find smallest distance
            if (dist_sq(a, target) < dist_sq(b, target))
                return a;

            // Return point
            return b;
        }

        /**
         * Find nearest neighbors
         * 
         * @param root: root node
         * @param target: target point, doesn't have to be in the tree
         * @param depth: the total depth of the tree
         * 
         * @return the best (closest) node to the target point
         */

        Node* nearestNeighbors(Node* root, const Point<K>& target, int depth){

            // Check valid tree
            if (root == nullptr) return nullptr;

            Node* temp; 
            Node* other;

            int dim = depth % K;

            if (target[dim] < root->point[dim]){
                temp = nearestNeighbors(root->left, target, depth+1);
                other = root->right;
            } else{
                temp = nearestNeighbors(root->right, target, depth+1);
                other = root->left;
            }

            Node* best = closest(target, root, temp);

            // Recurse back up the tree and check the other leaf
            double diff = target[dim] - root->point[dim];

            if (diff * diff < dist_sq(best->point, target)) {
                // search the other subtree
                temp = nearestNeighbors(other, target, depth+1);
                best = closest(target, best, temp);
            }

            return best;
        }

        /**
         * Free every node in the subtree (post-order: children before parent,
         * so we never read a node after deleting it)
         *
         * @param node: root of the subtree to free, may be null
         */
        void destroy(Node* node){

            // Empty subtree, nothing to free
            if (node == nullptr) return;

            destroy(node->left);
            destroy(node->right);
            delete node;
        }




        public:

            KDTree(std::vector<Point<K>> points) : root(nullptr), all_points(points) {
                // build kd tree
                root = build_tree(points, 0, (int)points.size() - 1, 0);
            }

            // Free all nodes when the tree goes out of scope
            ~KDTree(){
                destroy(root);
            }

            // No copying: a copy would share the same nodes, and both
            // destructors would delete them (double free)
            KDTree(const KDTree&) = delete;
            KDTree& operator=(const KDTree&) = delete;

            /**
             * Find the point in the tree closest to target, using kd trees
             *
             * @param target: target point, doesn't have to be in the tree
             *
             * @return closest point
             */
            Point<K> nearest(const Point<K>& target){

                // Empty tree has no closest point
                if (root == nullptr)
                    throw std::out_of_range("Tree is empty.");

                // Start the search at the root, depth 0
                return nearestNeighbors(root, target, 0)->point;
            }

            /** Find the point in the tree closes to target, using brute force
             * 
             * @param points: all points 
             * @param target: target point
             * 
             * @return closest point
             */
            Point<K> nearestBF(const Point<K>& target){

                // check empty list
                if (all_points.empty())
                    throw std::out_of_range("Tree is empty.");

                Point<K> best = all_points[0];

                for (std::size_t i = 1; i < all_points.size(); i++){
                    // call closest with point params
                    best = closest(target, all_points[i], best);
                }

                return best;
            }

 
};
} // namespace KDTree