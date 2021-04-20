/**
 * @file main.cpp
 * @brief This is a test of CMake, doxygen, and GitHub.
 * @details This is the long brief at the top of main.cpp.
 * @author Seth McNeill
 * @date 1/28/2021
 * 
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <queue>

using namespace std;

class Products {

private:

public:
    double price;
    double weight;
    double ratio;

    Products() {

    }

    Products(double p, double w) {
        price = p;
        weight = w;
        ratio = w/p;
    }
};

class BTNode {
public:
  BTNode* left;
  BTNode* right;
  BTNode* parent;

  
  /**
   * BTNode constructor
   */
  BTNode(Products dataVal) {
      //cout << "name = " << name << endl;
      left = NULL;
      right = NULL;
      parent = NULL;
      objName = name++;
      data = dataVal;
  }

    /**
     * This reports the node's name
     */
    char nodeName() {
        return(objName);
    }

    /**
     * This reports the node's data
     */
    Products nodeData() {
        return(data);
    }

private:
  char objName; // The object number created
  static char name;
  Products data; // Data that is stored in the node
};


char BTNode::name = 'A'; // initialize static variable

/**
 * This function adds a node to a binary search tree.
 * 
 * @param rootNode is the pointer to the tree's root node
 * @param n is the node to add
 * @returns pointer to rootNode if successful, NULL otherwise
 */
BTNode* addNode(BTNode* rootNode, BTNode* n) {
    BTNode* prev = NULL;
    BTNode* w = rootNode;
    if(rootNode == NULL) { // starting an empty tree
        rootNode = n;
    } else {
        // Find the node n belongs under, prev, n's new parent
        while(w != NULL) {
            prev = w;
            if(n->nodeData().ratio < w->nodeData().ratio){
                w = w->left;
            } else if(n->nodeData().ratio > w->nodeData().ratio) {
                w = w->right;
            } else { // data already in the tree
                return(NULL);
            }
        }
        // now prev should contain the node that should be n's parent
        // Add n to prev
        if(n->nodeData().ratio < prev->nodeData().ratio) {
            prev->left = n;
        } else {
            prev->right = n;
        }
    }
    return(rootNode);
}


/**
 * Adds a new node with the passed data value
 * 
 * @param rootNode pointer to root node
 * @param dataval an integer for the new node's data
 * @returns pointer to root node or NULL if not successful
 */
BTNode* addNode(BTNode* rootNode, Products dataval) {
    BTNode* newNode = new BTNode(dataval);
    if(addNode(rootNode, newNode) == NULL) {
        cout << dataval.ratio << " already in tree" << endl;
    } else {
        cout << dataval.ratio << " succesfully added" << endl;
    }
    return(rootNode);
}

int randomGen(int min, int max) {

    double random = rand() % max + min;
    //cout << rand() % max << endl;
    return random;
}

std::vector<Products> genProducts(int n) {
    vector<Products> output;
    for (int i = 0; i < n; i++) {
        output.push_back(Products(randomGen(1,1000), randomGen(5, 200)));
    }
    return output;
}

void printTree(BTNode* rootNode) {
    queue<BTNode*> todo; // the queue of nodes left to visit
    BTNode* cur; // current node
    BTNode* prev; // The previous node

    todo.push(rootNode);

    while(!todo.empty()) {
        cur = todo.front();
        // Print current node
        cout << cur->nodeName() << ':' << cur->nodeData().ratio << '\t';
        // add cur->left to queue
        if(cur->left != NULL) {
            todo.push(cur->left);
        }
        // add cur->right to queue
        if(cur->right != NULL) {
            todo.push(cur->right);
        }
        // remove cur from queue
        todo.pop();
    }
    cout << endl;
}

/**
 * Print a binary tree
 * 
 * This example is modified from:
 * https://stackoverflow.com/a/51730733
 * 
 * @param prefix is a string of characters to start the line with
 * @param node is the current node being printed
 * @param isLeft bool true if the node is a left node
 */

void printBT(const string& prefix, BTNode* node, bool isLeft)
{
    if( node != NULL )
    {
        cout << prefix;

        cout << (isLeft ? "|--" : "--" );

        // print the value of the node
        //cout << node->nodeName() << ':' << node->nodeData() << std::endl;
        cout << node->nodeData().ratio << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "|   " : "    "), node->left, true);
        printBT( prefix + (isLeft ? "|   " : "    "), node->right, false);
    }
}

/**
 * An overload to simplify calling printBT
 * 
 * @param node is the root node of the tree to be printed
 */

void printBT(BTNode* node)
{
    printBT("", node, false);
}


void createTree(vector<Products>& tree, int index) {
    BTNode* root = new BTNode(tree[index]);
    for (int i = 0; i < tree.size(); i++) {
        addNode(root, tree[i]);
    }
    printBT(root);
}

bool comparator(const Products& a, const Products& b) {
    return a.ratio < b.ratio;
}

int main(int, char**) {
    srand(time(NULL));
    vector<Products> products = genProducts(50);
    auto max = std::max_element(products.begin(), products.end(), [](const Products& a, const Products& b){
        return a.ratio < b.ratio;
    });
    int index = distance(products.begin(), max);
    cout << max->ratio << endl;
    //sort(products.begin(), products.end(), &comparator);
    for (int i = 0; i < products.size(); i++) {
        cout << i << " : " << products[i].ratio << endl;
    }
    createTree(products, index);
}
