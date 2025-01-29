#ifndef HELPER_H
#define HELPER_H

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

#endif
