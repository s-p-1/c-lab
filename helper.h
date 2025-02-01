#ifndef HELPER_H
#define HELPER_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#include <math.h>
#include <time.h>


char parser(char* input);

int get_line();
int R;
int C;

typedef struct AVLNode {
    int value;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
    int count;
} AVLNode;
typedef struct {
    int value; //initially 0
    short my_row;
    short my_col;
    int sum;
    int sq_sum;
    char operation; 
    short row1;
    short col1;
    short row2;
    short col2;
    AVLNode *cell_avl;
} cell; 

cell ** mysheet;
void calc_value(cell *cell1);

// typedef struct Rowcol
// {
//     int row;
//     int col;
// } rowcol;
int cell_handler(char *cell);




AVLNode* insert(AVLNode* node, int value);
AVLNode* deleteNode(AVLNode* root, int value);
void inorderTraversal(AVLNode* root);
AVLNode* buildAVLTree(int values[], int size);
AVLNode* minValueNode(AVLNode* node);
AVLNode* maxValueNode(AVLNode* node);

#endif
