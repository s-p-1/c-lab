#include "helper.h"

void dfs (int address){
    AVLNode* root = mysheet[address%1000-1][address/1000-1].cell_avl;
    int* myl= inorderTraversal(root);
    while (*myl!=-1){
        int addr1= *myl;
        mysheet[addr1%1000-1][addr1/1000-1].count += 1;
        printf("%d ", *myl);
        myl++;
    }

}



void prograph(int address){
    int size = 5;
    int *queue = (int *)malloc(size * sizeof(int));
    
    queue[0] = address;
    int front = 0;
    int rear = 1;
    queue[0] = address;
    AVLNode* root = mysheet[address%1000-1][address/1000-1].cell_avl;
    int size = 5;
    while (rear != front) {
        int address = queue[front];
        cell* ptr = mysheet[address%1000-1]+(address/1000-1);
        AVLNode* root = mysheet[address%1000-1][address/1000-1].cell_avl;
        int* myl= inorderTraversal(root);
        //this array contains adddress of the cells

        while (*myl!=-1){
            int addr1= *myl;
            update_value(ptr, address%1000-1, address/1000-1);
            //update the value here
            mysheet[addr1%1000-1][addr1/1000-1].count -= 1;
            if (mysheet[addr1%1000-1][addr1/1000-1].count == 0){
                queue[rear] = addr1;
                rear++;
            }
            myl++;
        }

        if (rear == size) {
            printf("Queue is full\n");
            break;
        }
    }
}


int main(){
    return 0;
}