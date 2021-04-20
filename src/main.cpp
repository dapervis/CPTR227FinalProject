/**
 * @file main.cpp
 * @brief This is an implementation of the knapsack problem
 * @details This is an implementation of the knapsack problem, using a binary tree to store the data.
 * @author Seth McNeill
 * @date 1/28/2021
 * 
 */

#include <iostream>
#include <queue>
#include <algorithm>    // std:: shuffle
#include <array>        // std::array
#include <random>       // std::default_random_engine
#include <chrono>       // std::chrono::system_clock
using namespace std;

/**
 * Binary Tree Node
 * 
 * This is from Open Data Structures in C++ by Pat Morin
 */
class BTNode {
public:
  BTNode* left;
  BTNode* right;
  BTNode* parent;
  int weight;
  int price;
  

  /**
   * BTNode constructor
   */
  BTNode(int dataVal) {
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
    int nodeData() {
        return(data);
    }

private:
  char objName; // The object number created
  static char name;
  int data; // Data that is stored in the node
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
            if(n->nodeData() < w->nodeData()){
                w = w->left;
            } else if(n->nodeData() > w->nodeData()) {
                w = w->right;
            } else { // data already in the tree
                return(NULL);
            }
        }
        // now prev should contain the node that should be n's parent
        // Add n to prev
        if(n->nodeData() < prev->nodeData()) {
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
BTNode* addNode(BTNode* rootNode, int dataval) {
    BTNode* newNode = new BTNode(dataval);
    if(addNode(rootNode, newNode) == NULL) {
        //cout << dataval << " already in tree" << endl;
    } else {
        //cout << dataval << " succesfully added" << endl;
    }
    return(rootNode);
}

/**
 * This generates a simple tree to play with
 * 
 * It is a bit of a hack.
 */
BTNode* genExampleTree(BTNode* root) {
    //int inData[] = {1,2,3,4,5,6,7};
    int inData[] = {4,6,5,7,2,1,3};
    int classData[] = {1,3,4,5,6,7,8,9,11,12,13,14};
    for(int ii = 0; ii < 7; ii++) {
        addNode(root, inData[ii]);
    }
    return root;
}

/** This is a tree generated using a vector.
 * 
 */
BTNode* genTree(vector<int> Supplier){
    BTNode* newNode = new BTNode(0);
    for (int x : Supplier)
            addNode(newNode, x);
    cout << endl;
    return newNode;

};

/**
 * Prints out a representtation of a binary search tree
 * 
 * @param rootNode is a pointer to the root node
 */
void printTree(BTNode* rootNode) {
    queue<BTNode*> todo; // the queue of nodes left to visit
    BTNode* cur; // current node
    BTNode* prev; // The previous node

    todo.push(rootNode);

    while(!todo.empty()) {
        cur = todo.front();
        // Print current node
        cout << cur->nodeName() << ':' << cur->nodeData() << '\t';
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
        cout << node->nodeData() << std::endl;

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
 * This calculates the height (max number of steps until leaf node)
 * 
 * @param pointer to a BTNode
 * @returns integer count of height
 */
int height(BTNode* u) {
    if (u == NULL) {
        return(-1);
    }
    return(1 + max(height(u->left), height(u->right)));
}

/** randTreeGen takes a integer, n and makes a BT tree from 1 to n that is randomly shuffled.
 * 
 * @param n refers to the amount of data in those trees from 1 to n
 */ 
BTNode* randTreeGen(int n){
    int arr[n];
    for(int k = 1; k < n+1; k++){
        arr[k-1] = k;
    };
    int size = sizeof(arr) / sizeof(arr[0]); //gets size of array

    vector<int> Vect(arr, arr + n);

    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count(); //gets a seed based on time to shuffle Vect by
    shuffle (Vect.begin(), Vect.end(), std::default_random_engine(seed)); //shuffles the vector
    BTNode* Final = genTree(Vect);
    //printBT(Final);
    return(Final);
}

/** Takes two integers, generates random binary trees off of them, and returns the minimum height, maximum height, and average height.
 * 
 * @param m refers to the number of trees you want to make
 * @param n refers to the amount of data in those trees from 1 to n
 * 
 */
int randTreeTest(int m, int n){
    float total = 0;
    int min = 0;
    int max = 0;
    float a = m;
    float average = 0.0;
    BTNode* minTree = new BTNode(0);
    for(int x = 0; x < m; x++) { 
       BTNode* testNode = randTreeGen(n);
       int hi = height(testNode);
       //cout << "height: " << hi << endl; 
       if(min == 0){
           min = hi;
           max = hi;
           minTree = testNode;
           //cout << "test min " << min << endl;
       }
       else if(hi > max)
       {  
           max = hi;
           //cout << " test max" << endl;
       }
       else if (hi < min)
       {
           min = hi;
           minTree = testNode;
           //cout << " test min" << endl;
       }
       total += hi;
       cout << "tree " << x+1 << " has been successfully generated." << endl;
    }
    average = total/a;
    cout << endl;
    cout << "one of the smallest BT, heightwise: " << endl;
    printBT(minTree);
    //cout << "total: " << total << endl;
    cout << " min: " << min << " max: " << max << " average: " << average << endl;
    return(0);     
}

int main(int, char**) {
    randTreeTest(100,26);    
}
