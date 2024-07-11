#ifndef BST_H
#define BST_H

#include <iostream>
#include <functional>
#include <vector>
#include <unordered_set>
#include <queue>
#include <initializer_list>

class BST
{
public:
    BST(); // I) defualt constructor
    BST(BST& bst);// II) copy constructor
    BST(BST &&bst); // III) move constructor
    BST(std::initializer_list<int> list);
    ~BST();
    class Node
    {
    public:
        Node(int value, Node* left, Node* right);
        Node();
        Node(const Node& node);

        int value;
        Node* left;
        Node* right;
        friend std::ostream& operator<<(std::ostream& os, Node& node);
        operator int() const;
    };

    Node*& get_root();
    void bfs(std::function<void(Node*& node)> func);
    size_t length();
    bool add_node(int value);
    Node** find_node(int value);
    Node** find_parrent(int value);
    Node** find_successor(int value);
    bool delete_node(int value);
    friend std::ostream& operator<<(std::ostream& os, BST& bst);
    BST& operator=(BST& other);
    BST& operator=(BST&& other);
    BST& operator++();
    BST operator++(int);

private:
    Node* root = nullptr;
};

// inline std::ostream& operator<<(std::ostream& os, BST& bst)


#endif //BST_H