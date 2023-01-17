/**
 * @file mq.c
 * @author Khojiakbar Yokubjonov 
 * @brief It contains the implement details of the M-Questions Game which is similar to the popular 20 questions game. 
 *  it uses a MQDecisionTree from mq.h library to store the questions and the answers of the game.
 *  More info regarding the decision tree can be found in the header file (mq.h).
 * 
 *          About the game:
 *              1 human player thinks of an object from everyday life. Then, the computer gets to ask the
                player a bunch of questions about the object to try to narrow down what the object is.
 * @version 0.1
 * @date 2022-10-26
 * 
 * @copyright Copyright (c) 2022
 * 
 */
#include "mq.h"
#include<stdio.h>
#include<string.h>


/**
 * @brief implements the M-Questions Game.
 *  traverses into the yes/ no children of the decision tree depending on the player's answer
 * to the question. Stops it finds the answer or reaches the end of the decision tree.
 * 
 * @param head root node of the decision tree
 */
void play_game(MQDecisionTreeNode* head){
    char input;
    while(head != NULL){
        if(strlen(head->text)==0){
            //guesses the actual object
            for(int i=0;i<head->num_answers;i++){
                printf("is it a %s? (y/n)\n",head->answers[i]);
                scanf(" %c", &input);
                if(input == 'y'){
                    printf("I guessed it!\n");
                    return;
                }
            }
            printf("You got me :)\n");
            return;
        }else{
            //asks a question from player
            printf("%s (y/n)\n", head->text);
        
            scanf(" %c", &input);
            if(input=='q'){
                printf("Quitting ...\n");
                return;
            //goes either in the yes or no direction based off the user answer
            }else if(input == 'y'){head = head->yes;}
            else if(input == 'n') {head = head->no;}
        }
    }
}
int main(int argc, char *argv[]){
    MQDecisionTree* tree = MQ_build_tree(argv[1]);
    MQ_populate_tree(tree, argv[1]);
    play_game(tree->root);  
    MQ_free_tree(tree);

}