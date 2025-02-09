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


char parser();

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
    int sum;
    int sq_sum;
    char operation; 
    short row1;
    short col1;
    short row2;
    short col2;
    int count;
    AVLNode *cell_avl;
    AVLNode *range_min_max;
} cell; 

cell ** mysheet;
void calc_value(cell *cell1);
int stringcomp(const char* s1, const char* s2, char myc);
// typedef struct Rowcol
// {
//     int row;
//     int col;
// } rowcol;
int cell_handler(char *cell);




AVLNode* insert(AVLNode* node, int value);
AVLNode* deleteNode(AVLNode* root, int value);
int* inorderTraversal(AVLNode* root);
AVLNode* buildAVLTree(int values[], int size);
AVLNode* minValueNode(AVLNode* node);
AVLNode* maxValueNode(AVLNode* node);
void update_value(cell *cell1, int row, int col);
void final_update(cell *cell1);
#endif
