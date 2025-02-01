#ifndef HELPER_H
#define HELPER_H

char parser(char* input[]);

int get_line();
int R;
int C;
typedef struct {
    int value; //initially 0
    char operation; //0 initially and for value/sleep, 
    //1 for add, 2 for subtract, 3 for multiply, 4 for divide
    //5 for min, 6 for max, 7 for avg, 8 for sum, 9 for stdev
    short row1;
    short col1;
    short row2;
    short col2;
    //above four will be initialized to -1;
} cell; 


typedef struct Rowcol
{
    int row;
    int col;
} rowcol;
rowcol cell_handler(char *cell);


typedef struct AVLNode {
    int value;
    struct AVLNode *left;
    struct AVLNode *right;
    int height;
    int count;
} AVLNode;

AVLNode* insert(AVLNode* node, int value);
AVLNode* deleteNode(AVLNode* root, int value);
void inorderTraversal(AVLNode* root);
AVLNode* buildAVLTree(int values[], int size);
AVLNode* minValueNode(AVLNode* node);

#define max(a, b) ((a) > (b) ? (a) : (b))
#define min(a, b) ((a) < (b) ? (a) : (b))
#include <math.h>
#include <time.h>

#endif
