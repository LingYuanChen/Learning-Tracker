#include "bst.h"


// Parameterized constructor
BST::Node::Node(int value, Node* left, Node* right)
    : value(value), left(left), right(right) {}

// Default constructor
BST::Node::Node()
    : value(0), left(nullptr), right(nullptr) {}

// Copy constructor
BST::Node::Node(const Node& node)
    : value(node.value), left(node.left), right(node.right) {}

std::ostream& operator<<(std::ostream& os, BST::Node& node){
    os << node.value;
    return os;
};

BST::Node::operator int() const{
    return value;
}

// I) defualt constructor
BST::BST() : root(nullptr) {}

// II) copy constructor
BST::BST(BST& bst):root(nullptr){
    bst.bfs([this](Node* node){this->add_node(node->value);});
};

// III) move constructor
BST::BST(BST &&bst) : root(std::exchange(bst.root, nullptr)) {};

BST::BST(std::initializer_list<int> list): root(nullptr) {
    for(auto value : list) {
        add_node(value);
    }
};

BST::~BST(){
	std::vector<Node*> nodes;
	bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
	for(auto& node: nodes)
		delete node;
}

BST::Node*& BST::get_root(){
    return root;
}

bool BST::add_node(int value){
    if(!root){
        root = new Node{value, nullptr, nullptr};
        return true;
    }
    Node* node_ptr = new Node{value, nullptr, nullptr};
    auto current = &root;
    while (*current){
        if ((*current)->value > value){
            current = &((*current)->left);
        }
        else if((*current)->value < value){
            current = &((*current)->right);
        }
        else return false;
    }
    *current = node_ptr;
    return true;
};

void BST::bfs(std::function<void(Node*& node)> func){
    if(!root) return;
    std::queue<Node*> queue;
    queue.push(root);
    while (queue.size()){
        auto current_node = queue.front();
        queue.pop();
        func(current_node);
        if(current_node->left) queue.push(current_node->left);
        if(current_node->right) queue.push(current_node->right);
    }
};

std::ostream& operator<<(std::ostream& out, BST& bst){
    out << std::string(20, '*') << std::endl;
    bst.bfs([&out](BST::Node*& node) {
        out << "node address : " << node << " value " << node->value << std::endl;
        if(node->left) { out << "node left child address : " << node->left << std::endl; }
        if(node->right) { out << "node right child address : " << node->right << std::endl; }
    });
    out << std::string(20, '*') << std::endl;
    return out;
};

size_t BST::length(){
    auto count = 0;
    BST::bfs([&count](BST::Node*& node){count++;});
    return count;
};

BST::Node** BST::find_node(int value){
    Node** node_ptr = &root;
    while(*node_ptr){
        if (value < (*node_ptr)->value) node_ptr = &((*node_ptr)->left);
        else if (value > (*node_ptr)->value) node_ptr = &((*node_ptr)->right);
        else return node_ptr;
    };
    return nullptr;
};

BST::Node** BST::find_parrent(int value){
    Node** node_ptr = &root;
    Node** parent_node = nullptr;
    while(*node_ptr){
        if (value < (*node_ptr)->value){
            parent_node = node_ptr;
            node_ptr = &((*node_ptr)->left);
        }
        else if (value > (*node_ptr)->value){
            parent_node = node_ptr;
            node_ptr = &((*node_ptr)->right);
        } 
        else return parent_node;
    };
    return nullptr;

};

BST::Node** BST::find_successor(int value){
    Node** node_ptr = find_node(value);
    if (node_ptr == nullptr) return nullptr;
    // Finding the smallest node in the right subtree
    Node** current = &(*node_ptr)->right;
    if (*current) {
        while ((*current)->left) {
            current = &(*current)->left;
        }
        return current;
    }
    else{
        return find_parrent(value);
    }
    
};

bool BST::delete_node(int value){
    Node** node = find_node(value);
    Node** parent = find_parrent(value);
    Node** successor = find_successor(value);    

    if (!node) {return false;}
    Node* delete_node = *node;
    if (!delete_node->left && !delete_node->right){
        if (parent){
            if((*parent)->left && (*parent)->left == delete_node){
                (*parent)->left = nullptr;
            }
            else {(*parent)->right = nullptr;}
        }
        else {
            root = nullptr;
        }
        delete delete_node;
    }
    else if (!delete_node->left || !delete_node->right){
        Node* child = delete_node->left ? delete_node->left:delete_node->right;
        // std::cout <<"child: "<< child->value << std::endl;
        if (parent){
            if((*parent)->left && (*parent)->left->value == value){
                (*parent)->left = child;
            }else{
                (*parent)->right = child;
            }
        }else{
            root = child;
        }
        delete delete_node;
    }
    else {
        // Case 3: Two children - Replace with in-order successor
        Node** successor = find_successor(value);
        if (successor == nullptr || *successor == nullptr) return false;
        
        Node* successor_node = *successor;
        Node** successor_parent = find_parrent(successor_node->value);

        std::swap(delete_node->value, successor_node->value);
        
        if (successor_parent && (*successor_parent)->left == successor_node) {
            (*successor_parent)->left = successor_node->right;
        } else if (successor_parent) {
            (*successor_parent)->right = successor_node->right;
        }
        
        delete successor_node;
    }
    return true;
};

BST& BST::operator=(BST& other) {
    if (this != &other){
        std::vector<Node*> nodes;
        std::vector<int> values;
        this->bfs([&nodes](BST::Node*& node){nodes.push_back(node);});
        for(auto node: nodes){
            delete node;
        }
        other.bfs([this](Node*& node) { this->add_node(node->value); });
    }
    return *this;
}

// BST& BST::operator=(BST& other) {
//     std::vector<Node*> nodes;
//     other.bfs([&nodes](Node*& node) { nodes.push_back(node); });
//     for(auto node : nodes) { this->add_node(node->value); }
//     return *this;
// }

BST& BST::operator=(BST&& other) {
    if (this != &other) {
       root = std::exchange(other.root, nullptr);
    }
    return *this;
}

BST& BST::operator++() {
    bfs([](Node* node){node->value += 1;});
    return *this;
}
BST BST::operator++(int) {
    BST copy = *this;
    bfs([](Node*& node) { node->value += 1; });
    return copy;
}