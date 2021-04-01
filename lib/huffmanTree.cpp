#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>

using namespace std;

const bool RIGHT = 1;
const bool LEST = 0;


struct Node{
    Node* right;
    Node* left;
    char data;
    int count;
};

struct comp
{
    bool operator()(Node* l, Node* r){  // comparator for 2 nodes
        return l->count > r->count;
    }
};

class BinaryTree{
    private:
        Node* _head;
        Node* treeQ;
        unordered_map<char, string> *hashmap;
        void _deleteNodes(Node* cNode);
        void _TranslateHashReq(Node * node, string path);

    public:
        BinaryTree(unordered_map<char,int>* huffList);
        ~BinaryTree();
        unordered_map<char, string> *getHash();
        void TranslateHash();
};

BinaryTree::BinaryTree(unordered_map<char,int>* huffList){
    hashmap = new unordered_map<char,string>;

    priority_queue<Node*, vector<Node *>, comp> prioQ;
    
    for (auto const& pair: *huffList){
        Node* new_node = new Node();
        cout << "pair first : " << pair.first << endl;
        new_node->data = pair.first;
        new_node->count = pair.second;   // build nodes from sorted vector
        prioQ.push(new_node);   // add to priority queue
    }
    while (prioQ.size() > 1) {
        Node* temp_node = new Node();       // create new empty node
        temp_node->right = prioQ.top();     // connect top node in prio queue to right of node
        prioQ.pop();                        // remove top node
        temp_node->left = prioQ.top();      // connect next node to left of empty node
        prioQ.pop();                        // remove top node
        temp_node->count = temp_node->right->count + temp_node->left->count;    // set empty node's count as the sum of the two connected nodes
        prioQ.push(temp_node);  // add newly connected nodes to the back of the priority queue
    }
    _head = prioQ.top();    // when finished building set head
    prioQ.pop();
    TranslateHash();
}

BinaryTree::~BinaryTree(){
    _deleteNodes(_head);
}

void BinaryTree::_deleteNodes(Node* cNode){
    if (cNode == nullptr){
        return;
    }
    _deleteNodes(cNode->right);
    _deleteNodes(cNode->left);
    delete cNode;
}

void BinaryTree::TranslateHash() {
    string path;
    _TranslateHashReq(_head, path);
}

void BinaryTree::_TranslateHashReq(Node* node, string path) {
    if (node == nullptr) {
        return;
    }
    else if (node->data) {
        cout << "node data: " << node->data << endl;
        hashmap->insert({node->data, path});
        return;
    }

    _TranslateHashReq(node->right, path + "1");
    _TranslateHashReq(node->left, path + "0");
}

unordered_map<char, string>* BinaryTree::getHash(){
    return hashmap;
}


