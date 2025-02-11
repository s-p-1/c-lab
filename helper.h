#ifndef HELPER_H
#define HELPER_H

#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>
#include <ctype.h>
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))


//display.c
typedef struct {
    char isv;
    int value; //initially 0
    int sum;
    int sq_sum;
    char operation; 
    short row1; 
    short col1;
    short row2;
    short col2;
    int count;
    int err_cnt;
    AVLNode *cell_avl;
    AVLNode *range_min_max;
} cell; 

char parser();

int get_line();



//avltree.c
typedef struct AVLNode {
    int value;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
    int count;
} AVLNode;
void freeTree(AVLNode *root);
AVLNode* insert(AVLNode* node, int value);
AVLNode* deleteNode(AVLNode* root, int value);
int* inorderTraversal(AVLNode* root);
AVLNode* buildAVLTree(int values[], int size);
AVLNode* minValueNode(AVLNode* node);
AVLNode* maxValueNode(AVLNode* node);


void calc_value(cell *cell1);
bool stringcomp(const char* s1, const char* s2, char myc);
// typedef struct Rowcol
// {
//     int row;
//     int col;
// } rowcol;
int cell_handler(char *cell);


void pro_graph(int address);

void update_value(cell *cell1, int row, int col);
void final_update(cell *cell1);


//global variables
int R;
int C;
cell ** mysheet;

#endif
