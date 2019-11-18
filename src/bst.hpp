#pragma once

// include this library to use NULL, otherwise use nullptr instead
#include <cstddef>
#include <iostream>
#include "node.hpp"

template<class T>
class BST{
public:
    // Constructor for the BST class, creates an empty tree
    BST(void);
    // Destructor for the BST class, destroys the tree
    ~BST(void);
    // Inserts data into the tree
    // param: The data to be inserted into the tree
    void insert(T);
    // Removes data from the tree
    // param: The data to be removed from the tree
    void remove(T);
    // Performs an inorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *inorder(void);
    // Performs an postorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *postorder(void);
    // Performs an preorder traversal
    // returns: pointer to a vector containing the tree traversal
    std::vector<T> *preorder(void);
    // Searches the tree for a given value
    // param: the data to search for
    // returns: a pointer to the node containing the data or NULL if the data
    //          was not found
    Node<T> *search(T);
    // Gets the current number of nodes in the tree
    // returns: the number of nodes in the tree
    int get_size(void);
private:
    // the root node of the tree
    Node<T> *root;
    // the number of nodes in the tree
    int node_count;
};

template<class T>
BST<T>::BST()
{
    root = NULL;
    node_count = 0;
}

template<class T>
BST<T>::~BST()
{
    root = NULL;
    while(root != NULL)
    {
        remove(root->get_data());
    }
}

template<class T>
 std::vector<T> * BST<T>::inorder()
{
    std::vector<T> *vec = new std::vector<T>;
    std::vector<Node<T>*> vec_stack;
    Node<T> * curr = root;

    if (root == NULL) // Get this edge case out of the way
        return NULL;

    while (curr != NULL || !vec_stack.empty()) {
        while (curr != NULL) { // Go all the way left
            vec_stack.push_back(curr);
            curr = curr->get_left();
        }

        curr = vec_stack.back();
        vec_stack.pop_back();

        vec->push_back(curr->get_data());

        curr = curr->get_right();
    }

    return vec;
}


template<class T>
 std::vector<T> * BST<T>::preorder()
{
    std::vector<T> *vec = new std::vector<T>;
    std::vector<Node<T>*> vec_stack;
    Node<T> * curr;

    if (root == NULL) // Get this edge case out of the way
        return NULL;

    vec_stack.push_back(root);

    while (!vec_stack.empty()) {
        curr = vec_stack.back();
        vec->push_back(curr->get_data());
        vec_stack.pop_back();

        if (curr->get_right())
            vec_stack.push_back(curr->get_right());

        if (curr->get_left())
            vec_stack.push_back(curr->get_left());
    }

    return vec;
}


template<class T>
 std::vector<T> * BST<T>::postorder()
{
    std::vector<T> *vec = new std::vector<T>;
    std::vector<Node<T>*> vec_stack;
    Node<T> * curr;
    vec_stack.push_back(root);

    while(!vec_stack.empty()) {
        curr = vec_stack.back();
        vec_stack.pop_back();
        vec->insert(vec->begin(), curr->get_data());

        if (curr->get_left())
            vec_stack.push_back(curr->get_left());

        if (curr->get_right())
            vec_stack.push_back(curr->get_right());
    }
    return vec;
}

template<class T>
void BST<T>::insert(T new_data)
{
    Node<T> * new_node = new Node<T>(new_data);
    Node<T> * traversal_node;

    if (root == NULL) { // Check the case of nothing in the tree
        root = new_node;
        node_count++;
    }

    traversal_node = root;

    // The check above should keep the loop from starting if true
    while (traversal_node->get_data() != new_node->get_data()) {
        if (new_node->get_data() < traversal_node->get_data()) { // Check if the data needs to go left
            if (traversal_node->get_left() != NULL) // If there is a node there, keep going left
                traversal_node = traversal_node->get_left();
            else { // Otherwise it has found its home
                traversal_node->set_left(new_node);
                node_count++;
            }

        } else if (new_node->get_data() > traversal_node->get_data()) { // Check if the data needs to go right
            if (traversal_node->get_right() != NULL) // If there is a node there, keep going right
                traversal_node = traversal_node->get_right();
            else { // Otherwise it has found its home
                traversal_node->set_right(new_node);
                node_count++;
            }
        }
    }
}


template<class T>
Node<T> *BST<T>::search(T val)
{
    Node<T> * traversal_node = root;

    if (traversal_node == NULL)
        return NULL;

    bool kill = false;

    while (traversal_node->get_data() != val && traversal_node != NULL && !kill) {
        if (traversal_node->get_left() == NULL && traversal_node->get_right() == NULL)
            return NULL;

        if (val < traversal_node->get_data()) { // Check if the data needs to go left
            if (traversal_node->get_left() != NULL) // If there is a node there, keep going left
                traversal_node = traversal_node->get_left();
        } else if (val > traversal_node->get_data()) { // Check if the data needs to go right
            if (traversal_node->get_right() != NULL) // If there is a node there, keep going right
                traversal_node = traversal_node->get_right();
        }
    }

    if (traversal_node->get_data() == val)
        return traversal_node;
}

template <class T>
void BST<T>::remove (T val) {
    Node<T> *back;
    Node<T> *temp;
    Node<T> *delParent;    // Parent of node to delete
    Node<T> *delNode;      // Node to delete

    temp = root;
    back = NULL;

    // Find the node to delete
    while((temp != NULL) && (val != temp->get_data()))
    {
        back = temp;
        if(val < temp->get_data())
            temp = temp->get_left();
        else
            temp = temp->get_right();
    }

    if(temp == NULL) // Didn't find the one to delete
    {
        return;
    }
    else
    {
        if(temp == root) // Deleting the root
        {
            delNode = root;
            delParent = NULL;
        }
        else
        {
            delNode = temp;
            delParent = back;
        }
    }

    // Case 1: Deleting node with no children or one child
    if(delNode->get_right() == NULL)
    {
        if(delParent == NULL)    // If deleting the root
        {
            root = delNode->get_left();
            delete delNode;
            node_count--;
            return;
        }
        else
        {
            if(delParent->get_left() == delNode)
                delParent->set_left(delNode->get_left());
            else
                delParent->set_right(delNode->get_left());
            delete delNode;
            node_count--;
            return;
        }
    }
    else // There is at least one child
    {
        if(delNode->get_left() == NULL)    // Only 1 child and it is on the right
        {
            if(delParent == NULL)    // If deleting the root
            {
                root = delNode->get_right();
                delete delNode;
                node_count--;
                return;
            }
            else
            {
                if(delParent->get_left() == delNode)
                    delParent->set_left(delNode->get_right());
                else
                    delParent->set_right(delNode->get_right());
                delete delNode;
                node_count--;
                return;
            }
        }
        else // Case 2: Deleting node with two children
        {
            // Find the replacement value.  Locate the node
            // containing the largest value smaller than the
            // key of the node being deleted.
            temp = delNode->get_left();
            back = delNode;
            while(temp->get_right() != NULL)
            {
                back = temp;
                temp = temp->get_right();
            }
            // Copy the replacement values into the node to be deleted
            T temp_data = temp->get_data();
            delNode->set_data(temp_data);

            // Remove the replacement node from the tree
            if(back == delNode)
                back->set_left(temp->get_left());
            else
                back->set_right(temp->get_left());
            node_count--;
            return;
        }
    }
}

template<class T>
int BST<T>::get_size()
{
    return node_count;
}
