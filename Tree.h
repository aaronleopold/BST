/*
    NOTE: A few member functions have a public and a private versions. The intent of this is
          to simplify things for the user. 
*/

#pragma once
#include <iostream>
#include <string>

template <class T>
class Tree
{
    struct Node
    {
        T data;
        Node* left;
        Node* right;
		Node* parent;

        Node()
        {
            data = {};
            left = nullptr;
            right = nullptr;
			parent = nullptr;
        }

        bool isLeaf()
        {
            if (this->left == nullptr && this->right == nullptr)
                return true;
            
            else
                return false;
        }
    };

    Node* root;
    unsigned int nodes;

    ////////////////////////////////////
    //////// Private Functions ////////

    struct Node* get_node(Node* curr, T data)
    {
        if (curr == nullptr)
            return nullptr;
        
        else if (curr->data == data)
            return curr;
        
        else if (data < curr->data)
            get_node(curr->left, data);
        
        else if (data > curr->data)
            get_node(curr->right, data);
    }

	struct Node* get_min_node(Node* curr)
	{
		Node* min = nullptr; 
		while (curr != nullptr)
			min = get_min_node(curr->left);

		return min;
	}

    void print_ascending(Node* curr)
    {
		if (curr != nullptr)
		{
			print_ascending(curr->left);

			std::cout << curr->data << std::endl;

			print_ascending(curr->right);
		}
    }

    void print_descending(Node* curr)
    {
		if (curr != nullptr)
		{
			print_descending(curr->right);

			std::cout << curr->data << std::endl;

			print_descending(curr->left);
		}
    }

    void insert_node(Node* curr, Node* prev, T data)
    {
        if (curr == nullptr)
        {
            curr = new Node();
            curr->data = data;
			curr->parent = prev;

			if (curr->data > prev->data)
				prev->right = curr;
			else if (curr->data < prev->data)
				prev->left = curr;

            nodes++;
        }

        else if (data < curr->data)
            insert_node(curr->left, curr, data);

        else if (data > curr->data)
            insert_node(curr->right, curr, data);
    }

    void remove_node(Node* curr, T data) // doesn't catch all cases FIXME
    {
		Node* prev = curr->parent;

        if (curr->isLeaf()) // node to remove has no branching (is a leaf)
        {
            if (curr->data > prev->data)
                prev->right = nullptr;
            else if (curr->data < prev->data)
                prev->left = nullptr;
            
            delete curr;
        }

        else if (curr == root) // node to remove is the root
        {

        }

        else if ((curr->right != nullptr && curr->left == nullptr)) // node only has right branching
        {
            Node* swap = this->get_min_node(curr->right);
            swap->parent->left = nullptr;
            if (curr->parent->left == curr)
                curr->parent->left = swap;
            else if (curr->parent->right == curr)
                curr->parent->right = swap;
        }

        else if ((curr->right == nullptr && curr-> left != nullptr)) // node only has left branching
        {   
            Node* swap = this->get_min_node(curr->left);
            swap->parent->left = nullptr;
            if (curr->parent->left == curr)
                curr->parent->left = swap;
            else if (curr->parent->right == curr)
                curr->parent->right = swap;
        }

        else if (curr->left != nullptr && curr->right != nullptr) // node has left and right branching
        {
            Node* swap;
        }
    }

    void clear_all(Node* curr)
    {
		if (curr != nullptr)
		{
			clear_all(curr->left);
			clear_all(curr->right);
			delete curr;
		}
    }

public:
    Tree()
    {
        root = nullptr;
        nodes = 0;
    }

    ~Tree()
    {
        clear();

		if (root != nullptr)
		{
			root = nullptr;
			delete root;
		}
    }

    void clear()
    {
        if (root == nullptr)
            return;
        
		clear_all(root);

		if (root != nullptr)
			root = nullptr;
    }

    bool contains(T data)
    {
        if (get_node(root, data) != nullptr)
            return true;
        
        else
            return false;
    }

    /// Accessors ///
    unsigned int size()
    {
        return this->nodes;
    }

    void print(bool ascending)
    {
        if (root == nullptr)
            return;

        else if (ascending)
            print_ascending(root);

        else
            print_descending(root);
    }

    /// Insertion ///
    void insert(T data)
    {
        if (root == nullptr)
        {
            root = new Node();
            root->data = data;
            nodes++;
        }

        else
        {
            insert_node(root, root, data);
        }
    }

    void insert(T* data, unsigned int size)
    {
        for (unsigned int i = 0; i < size; i++)
            insert(data[i]);
    }

	/// Removal ///
    void remove(T data)
    {
        if (root == nullptr)
            return;
        
		Node* target = this->get_node(root, data);
		if (this->contains(target->data))
			remove_node(target, data);
    }

    void remove(T* data, unsigned int size)
    {
        for (unsigned int i = 0; i < size; i++)
        {
            remove(data);
        }
    }
};

/*
    TO DO:
    1). figure out algorithm for removal of nodes
    2). perhaps make a recursive re-order function???
        take in two nodes, original and swap
    3). must implement reordering during/after removal of 
        tree node
*/