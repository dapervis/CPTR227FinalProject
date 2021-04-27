/**
 * @file main.cpp
 * @brief This is the final project made with code from HW11.
 * @details This program is based on the knapsack problem and uses a binary tree to store the data.
 * @author Daniel Pervis and Lee Beckermeyer
 * @date 4/21/2021
 * 
 */

#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <queue>

using namespace std;

/**
   * This is class has 2 different parameters used to make this object
   
   */
class Products {

private:

public:
    double price;
    double weight;
    double ratio;

    Products() {

    }

    /**
   * This is the constructor for this class
   * @param p The price for the product.
   * @param w The weight for the product.
   *
   */
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
   * @param dataVal This is the product that is put into the binary tree.
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

    /**
     * This reports the node's ratio, currently breaks something by converting it to an int, don't use for comparisons.
     */
    int nodeRatio() {
        return(data.ratio);
    }

private:
  char objName; // The object number created
  static char name; //unkown
  Products data; // Data that is stored in the node
};


char BTNode::name = 'A'; // initialize static variable, unkown

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
                //cout << w->nodeData().ratio << " added" << endl;
                w = w->left;
            } else if(n->nodeData().ratio > w->nodeData().ratio) {
                //cout << w->nodeData().ratio << " added" << endl;
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
        //cout << dataval.ratio << " already in tree" << endl;
    } else {
        //cout << dataval.ratio << " succesfully added" << endl;
    }
    return(rootNode);
}


/**
 * Randomly generates a "double"(float in C++) number 
 * 
 * @param min The minimum number that can be generated.
 * @param max The maximum number that can be generated.
 */
int randomGen(int min, int max) {

   double random = rand() % max + min;
    //int random = rand() % max + min;
    //cout << rand() % max << endl;
    return random;
}

/**
 * generates the products.
 * 
 * @param n The amount of products you want generated.
 */
std::vector<Products> genProducts(int n) {
    vector<Products> output;
    for (int i = 0; i < n; i++) {
        output.push_back(Products(randomGen(1,1000), randomGen(5, 200)));
    }
    return output;
}

/**
 * prints a binary tree
 * 
 * @param rootNode The binary tree you want printed.
 */
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

        cout << (isLeft ? "L--" : "R--" );

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

/**
 * creates a binary tree, also checks if the knapsack is full, if the knapsack isn't full it continues until the end of the vector.
 * 
 * @param tree a vector of products you want to turn into a tree.
 * @param index the size of the vector, needed with the current implementation.
 */
void createTreeBruteForce(vector<Products>& tree, int index) {
    BTNode* root = new BTNode(tree[index]);
    int weight = 0;
    int price = 0;
    for (Products x : tree){
            int newweight = x.weight + weight;
            int newprice = x.price + price;
            if(newweight>=500){
                continue;
            }
            else{
                weight = newweight;
                price = newprice;
                addNode(root, x);
                x.weight + weight;
                x.price + price;
            }
        
            
        };    
    cout << "Tree generated using a brute force algorithm after sorting the object's ratios" << endl;
    cout << "Weight of the Knapsack: " << weight << " lbs" << endl;
    cout << "Price of the Knapsack: " << price << "$" << endl;
    cout << "Ratio of the Tree(weight/price): " << (double)500/price << endl;
    printBT(root);
};

/**
 * creates a binary tree, also checks if the knapsack is full, if the knapsack isn't full it continues until the end of the vector.
 * 
 * @param tree a vector of products you want to turn into a tree.
 * @param index the size of the vector, needed with the current implementation.
 */
void RandomTree(vector<Products>& tree, int index) {
    BTNode* root = new BTNode(tree[index]);
    cout << tree[index].ratio << endl;
    int weight = 0;
    int price = 0;
    int n = 0;
    while(n < 10){
        n++;
        Products x = tree[randomGen(0,index)];
        int newweight = x.weight + weight;
        int newprice = x.price + price;
        if(newweight>=500){
                    continue;
                }
                else{
                    weight = newweight;
                    price = newprice;
                    addNode(root, x);
                    x.weight + weight;
                    x.price + price;
                } 
    }  
    cout << "Tree generated using a random algorithm" << endl;
    cout << "Weight of the Knapsack: " << weight << " lbs" << endl;
    cout << "Price of the Knapsack: $" << price << endl;
    cout << "Ratio of the Tree(weight/price): " << (double)500/price << endl;
    printBT(root);
};

/**
 * creates a binary tree
 * 
 * @param tree a vector of products you want to turn into a tree.
 * @param index the size of the vector, needed with the current implementation.
 */
void createTree(vector<Products>& tree, int index) {
    BTNode* root = new BTNode(tree[index]);
    for (Products x : tree){
        addNode(root, x); 
    }
    printBT(root);
}

/**
 * compares 2 products
 * @param a product a
 * @param b product b
 * 
 */
bool comparator(const Products& a, const Products& b) {
    return a.ratio > b.ratio;
}

int main(int, char**) {
    srand(time(NULL));
    vector<Products> products = genProducts(50);
    auto max = std::max_element(products.begin(), products.end(), [](const Products& a, const Products& b){
        return a.ratio < b.ratio;
    });
    int index = distance(products.begin(), max);
    cout << max->ratio << endl;
    cout << products[index].ratio << endl;
    //sort(products.begin(), products.end(), &comparator); NO TOUCHY
    for (int i = 0; i < products.size(); i++) {
        cout << i << " : " << products[i].ratio << endl;
    }

    //for (Products x : products){
    //    cout << x.ratio << endl;
    //}
    RandomTree(products, index);
    createTreeBruteForce(products, index);
    
}
