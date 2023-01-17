/**
 * @file mq.c
 * @author Khojiakbar Yokubjonov 
 * @brief It contains the implementation details of the MQDecisionTree , which is used in the M-Questions Game.
 * 
    Each MQDecisionTreeNode. represents one question or group of answers. It uses yes/no pointers.
    If it is a question node, the text field is populated with the question, num_answers is
    0, and answers will be NULL. If it instead represents a pool of answers, the text field is not 
    populated, answers will be a pointer to an array of pointers to the logical answer(s) at this point in the tree,
    and num_answers will be given the correct count based on how many answers there are. Only leaf nodes
    will have answers. All other nodes will be question nodes.
 * @version 0.1
 * @date 2022-10-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "mq.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**
 * @brief a helper method that's used to store the questions from the game data file.
 * 
 * @param buffer -a list of str, line from a game data file
 * @param buffer_len - length of the line
 * @param questions a list to store the questions from the a line
 * @return int - number of questions
 */
int save_questions(char buffer[500], int buffer_len,char questions[200][200]){
    int buffer_ind = 0;
    int questions_ind = 0;
    while(buffer_ind < buffer_len ){
        char question[200]; int q_ind=0;
        //extracts each question;
        while(buffer[buffer_ind] != '?'&& buffer_ind < buffer_len){
            question[q_ind++]=buffer[buffer_ind++];
        }
        question[q_ind] = buffer[buffer_ind++];question[q_ind+1] = '\0';
        strcpy(questions[questions_ind++],question);


        buffer_ind++;



    }
    return questions_ind;


}

/**
 * @brief helper method that's used to store  the answers from the game data file
 * it uses the Item data structure to store each answer.
 * 
 * @param buffer a list of str, questions
 * @param buffer_len - length of the line from a file
 * @return Item* return an Item object containing one answer
 */
Item* extract_item(char buffer[500], int buffer_len){
    int end_of_word = FALSE;
    int ind = 0, buffer_ind = 0, pos_ind = 1;

    Item* item = malloc(sizeof(Item));
    item->name = (char*) malloc(100);
    item->position = (int*) calloc(100, sizeof(int));
    item->next = NULL;

    while(buffer_ind < buffer_len){
        if(!end_of_word){
            //extracts the actual answer
            while(buffer[buffer_ind] != ','){
                item->name[ind] = buffer[buffer_ind];
                ind++; buffer_ind++;
            }
            end_of_word = TRUE;
            item->name[ind] = '\0';
        }else{
            //copies the path data (ones and zeroes) from the list of strings.
            if(buffer[buffer_ind]!= ','){
                int dir = (int)buffer[buffer_ind]-'0';
                item->position[pos_ind] = dir; item->position[0] = pos_ind;
                buffer_ind++; pos_ind++;
            }else{
                buffer_ind++;
            }

        }

    }
    return item;

}

/**
 * @brief deletes a line breaker from a string
 * 
 * @param buffer a string
 * @param size size of the string
 */
void strip_line_breaker(char buffer[500], int size){
     if (buffer[size - 1] == '\n')
        {
            buffer[size - 1] = '\0';
        }
}


/**
 * @brief reads the first two lines of game data file.
 *  More specifically, it copies the answer count and the questions.
 * 
 * @param file_name - file containing the game data
 * @param item_count - number of answers
 * @param questions - actual game questions
 * @param q_count - num of questions
 */
void read_first_two_lines(char* file_name, int* item_count, char questions[200][200], int* q_count){
    FILE *file = fopen(file_name, "r");
    char buffer[500];
    fgets(buffer, 499, file);

    strip_line_breaker(buffer, strlen(buffer));

    //copies the number of answers at the top of the file
    char val[10];
    strcpy(val, buffer);
    int count = atoi(val);
    *item_count = count;

    //reads the questions in the file
    fgets(buffer, 499, file);

    strip_line_breaker(buffer, strlen(buffer));
    *q_count = save_questions(buffer, strlen(buffer), questions);

    fclose(file);

}

/**
 * @brief Stores all the game answers from a file.
 *  it uses a helper method to copy the answers from each line in the file
 * 
 * @param file_name - name of the file containing the answers
 * @param count - number of answers.
 * @return Item** a list of Item objs containing the answers and their paths in the decision tree
 */
Item** get_all_items(char* file_name, int* count){
    FILE *file = fopen(file_name, "r");
    char buffer[500];
    fgets(buffer, 499, file);
    int item_count = atoi(buffer);
    fgets(buffer, 499, file);

    Item** items = calloc(item_count, sizeof(Item)); int ind = 0;
    //reads and copies all the answers from the file
    while(fgets(buffer, 499, file) != NULL){

         //getting rid of the new line char
        strip_line_breaker(buffer, strlen(buffer));
        Item* new = extract_item(buffer, strlen(buffer));
        items[ind++] = new;
    }

    *count = item_count;
    fclose(file);

    return items;





}
MQDecisionTreeNode* create_tree_node(char text[50], int item_count){
    MQDecisionTreeNode* tree_node = malloc(sizeof(MQDecisionTreeNode));
    tree_node->text = (char*)malloc(50);
    tree_node->no = NULL; 
    tree_node->yes = NULL;
    tree_node->num_answers = 0;
    if(strlen(text)!=0){
        tree_node->answers = NULL; //question node doesn't store the answers
    }else{
        tree_node->answers = (char**)malloc(sizeof(char*) * item_count); // the answer node
    }
    
    strcpy(tree_node->text, text);
    return tree_node;
}
/*
 helper method to add a node to the decision tree
 head - root node of the decision tree.
 text - a question to put in the node.
 item_count - number of answers
*/
void add_to_tree(MQDecisionTreeNode*head, char text[50], int item_count){

    if (head->yes==NULL && head->no == NULL){
        head->yes = create_tree_node(text, item_count);
        head->no = create_tree_node(text, item_count);
        return;
    }
    else{
        add_to_tree(head->yes, text, item_count);
        add_to_tree(head->no, text, item_count);
    }


}

MQDecisionTree* MQ_build_tree(char* file_name){
    int item_count=0,question_count=0;  char questions[200][200];
    read_first_two_lines(file_name,&item_count,questions, &question_count);
    MQDecisionTree* tree = malloc(sizeof(MQDecisionTree));
    for(int i=0; i< question_count; i++){
        if(i==0){
            tree->root = create_tree_node(questions[i], item_count);
        }else{
            add_to_tree(tree->root, questions[i], item_count);
        }

    }   add_to_tree(tree->root, "", item_count);

    return tree;

}
/**
 * @brief helper method to print the decision tree
 * 
 * @param head root node of the tree
 * @param dir used to manage the spacing in the output
 * @param space leading space count on the level of the tree
 */
void print_tree(MQDecisionTreeNode*head, char dir[5], int space){
    if (head == NULL){return;}
    for(int j=0; j<space; j++){
        printf(" ");
    }

    if(strlen(head->text) > 0){
        printf("%s[%s]\n", dir,head->text);
    }else if(head->num_answers==0){
        printf("%.4s\n", dir);
    }else{
        printf("%.4s |",dir);
        for(int i=0; i<head->num_answers   ; i++){
            printf(" %s |", head->answers[i]);
        }printf("\n");
    }

    print_tree(head->yes, "-y-> ", space+4);
    print_tree(head->no, "-n-> ", space+4);
}
void MQ_print_tree(MQDecisionTree* root){
    char dir[] = ""; 
    print_tree(root->root, dir, -4);
}

/**
 * @brief helper method to populate the decision tree with answers.
 * 
 * @param head root node of the tree
 * @param item answer to be placed
 * @param ind int, used to keep track of ones and zeroes in the answer path
 */
void help_populate_tree(MQDecisionTreeNode* head,Item* item, int ind){
    if(ind == item->position[0]+1){
   
        head->answers[head->num_answers] = (char*)malloc(50*sizeof(char));
        strcpy(head->answers[head->num_answers], item->name);
        head->num_answers+=1;
      
        return;
    }
    else if(item->position[ind]==0){
        help_populate_tree(head->no, item, ind+1);

    }
    else{
        help_populate_tree(head->yes, item, ind+1);

    }


}
void MQ_populate_tree(MQDecisionTree* tree, char* file_name){
    int count;
    Item** items = get_all_items(file_name, &count);
    for(int j=0; j<count; j++){
        help_populate_tree(tree->root,items[j], 1);
    }

/**
 * all the Item obj, which were used to stores the answers, are freed once the 
 * answers are placed in the decision tree
 * 
 */
    for(int i=0; i<count; i++){
        free(items[i]->position);
        free(items[i]->next);
        free(items[i]->name);
        free(items[i]);
    }free(items);

    







}
/**
 * @brief helper method to free the decision tree
 * 
 * @param head root node of the tree
 */
void help_free_tree(MQDecisionTreeNode*head){
    if(head == NULL){
        return;}
    help_free_tree(head->yes);
    help_free_tree(head->no);
    //frees all the answer nodes
    if(head->yes == NULL && head->no == NULL){
        for(int i=0; i<head->num_answers; i++){
            free(head->answers[i]);
        }
    }
    
    if(head->answers != NULL){
        free(head->answers);
    }
    free(head->text);
    free(head);
}

void MQ_free_tree(MQDecisionTree* tree){
    help_free_tree(tree->root);
    free(tree);
}