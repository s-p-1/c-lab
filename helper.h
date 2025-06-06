#ifndef HELPER_H
#define HELPER_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <limits.h>
#include <stdbool.h>
#include <ctype.h>
#include <unistd.h>
#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))

typedef struct AVLNode {
    int value;    
    int height;
    int count;
    struct AVLNode *left;
    struct AVLNode *right;
} AVLNode;
//display.c
typedef struct {
    char isv;
    char operation;
    short row1; 
    short col1;
    short row2;
    short col2;
    int value; //initially 0
    int sum;
    int sq_sum;
    int count;
    int err_cnt;
    AVLNode *cell_avl;
    AVLNode *range_min_max;
} cell; 

char parser(char * input);

int get_line();

bool is_int(char *s);

//avltree.c

void freeTree(AVLNode *root);
AVLNode* insert(AVLNode* node, int value);
AVLNode* deleteNode(AVLNode* root, int value);
int* inorderTraversal(AVLNode* root);
AVLNode* buildAVLTree(int values[], int size);
AVLNode* minValueNode(AVLNode* node);
AVLNode* maxValueNode(AVLNode* node);

//expcalc.c
void calc_value(cell *cell1);
void update_value(cell *cell1, int row, int col);
void final_update(cell *cell1);

//helper.c
bool stringcomp(const char* s1, const char* s2, char myc);
int cell_handler(char *cell);

//graph.c
void pro_graph(int address);
bool dfs(int address, int lhs, bool flag);
void dfs2(int address);

typedef struct {
    short lrow;
    short lcol;
    short rrow;
    short rcol;
    int x;
} bigdeps;


//global variables
extern int R;
extern int C;
extern cell ** mysheet;
extern bigdeps * bigies;
extern int bigifront;
extern int maxibigi;

#endif
