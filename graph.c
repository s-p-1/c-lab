#include "helper.h"

void prograph(int address){
    int *queue = (int *)malloc(5 * sizeof(int));
    int front = 0;
    int rear = 1;
    AVLNode* root = mysheet[address%1000-1][address/1000-1].cell_avl;
    int size = 5;
    while (rear != front) {
        int arr[5]; // this array is from the avl tree code
        //this array contains adddress of the cells
        if (front == -1) {
            front = 0;
        }
        if (rear == size) {
            printf("Queue is full\n");
            break;
        }
        int x;
        scanf("%d", &x);
        queue[rear] = x;
        rear++;
    }
}


int main(){
    return 0;
}