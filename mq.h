/**
 * @file mq.h
 * @author Khojiakbar Yokubjonov
 * @brief contains the header info for the M-Questions game library. This game is similar to 
 * popular 20 questions game. It declares the data structures, public methods and other functionalities 
 * used in the game implementation.
 * @date 2022-10-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#ifndef HEADER_FILE
#define HEADER_FILE

#define TRUE 1
#define FALSE 0

/**
 * a decision node stusture used to store the questions and answers for the M-Questions Game.
 * It uses yes/no pointers. Every node will either represent a question or a pool of
answers.

 * 
 */

typedef struct MQDecisionTreeNode {
    char* text; //stores a question or empty string if it is a answer node
    int num_answers; //stores the number of answers present in the node
    char** answers; //stores a list of answers or NULL if it is a question node
    struct MQDecisionTreeNode* yes; 
    struct MQDecisionTreeNode* no;
} MQDecisionTreeNode;

/**
 * It just contains a pointer to the root node of the tree, or NULL if it is an
    empty tree. Used to store the questions & answers in the game
 * 
 */
typedef struct MQDecisionTree {
    MQDecisionTreeNode* root;
} MQDecisionTree;


/**
 * a data structure used to store the answers before they are added to the above tree.
 * it is freed right after it passes its data  to the answer node in the tree.
 * The name field represent an answer to a question.
 * The position field represent a list of ones and zeroes, which serve as a path to the answer.
 *  one = node.yes direction
 *  zero = node.no direction
 * 
 */
typedef struct Item {
    //might increase the name size here
    char* name;
    int* position;
    struct Item* next;

}Item;

/**
 * @brief prints out a text representation of a decision tree
 * 
 * @param root  - decision tree with a pointer to the root of the decision nodes
 */
void MQ_print_tree(MQDecisionTree* root);

/**
 * @brief accepts a char* which represents the name of the file to load the data from. The function
     opens up the file, iterates through the data within and populate a decision tree.
     It doesn't add the answers to the questions during this process.
 * 
 * @param file_name - name of the file containing te game data
 * @return MQDecisionTree* -  yes/no tree structure containing questions and answers.
 */
MQDecisionTree* MQ_build_tree(char* file_name);

/**
 * @brief takes a previously-built tree and a char* with the name of the data file.It populates
the tree with the answers within the correct leaf nodes based on the data from the file, following the correct
yes/no paths through the tree. This function doesn't not *add* any new nodes to the tree. Rather, it only
adds possible answers to the leaf nodes of the tree that is passed into it.
 * 
 * @param tree - decision tree
 * @param file_name - name of the file containing te game data
 */
void MQ_populate_tree(MQDecisionTree* tree, char* file_name);

/**
 * @brief frees all memory associated with this tree.
 * 
 * @param tree - a decision tree to be freed
 */
void MQ_free_tree(MQDecisionTree* tree);


#endif