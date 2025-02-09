#include "helper.h"

void dfs (int address){
    AVLNode* root = mysheet[address%1000][address/1000].cell_avl;
    printf("dfs\n");
    int* myl= inorderTraversal(root);
    
    printf("dfs\n");
    while (*myl!=-1){
        
        printf("dfs %d\n", *myl);
        int addr1= *myl;
        mysheet[addr1%1000][addr1/1000].count += 1;
        printf("dfs count %d %d\n", addr1, mysheet[addr1%1000][addr1/1000].count);
        printf("%d ", *myl);
        dfs(*myl);
        myl++;
    }
    return;

}



void pro_graph(int address){

    dfs(address);
    printf("donedfs\n");
    int size = 5;
    int *queue = (int *)malloc(size * sizeof(int));
    
    queue[0] = address;
    int front = 0;
    int rear = 1;
    queue[0] = address;
    AVLNode* root = mysheet[address%1000][address/1000].cell_avl;
    
    while (rear != front) {
        
        int address = queue[front];
        printf("%d address of front\n", address);
        printf("%d count of front\n", mysheet[address%1000][address/1000].count);
        cell* ptr = mysheet[address%1000]+(address/1000);
        AVLNode* root = mysheet[address%1000][address/1000].cell_avl;
        int* myl= inorderTraversal(root);
        //this array contains adddress of the cells
        while (*myl!=-1){
            int addr1= *myl;
            printf("%d count of child\n", mysheet[addr1%1000][addr1/1000].count);
            update_value(mysheet[addr1%1000]+(addr1/1000), address%1000, address/1000);
            //update the value here
            mysheet[addr1%1000][addr1/1000].count -= 1;
            if (mysheet[addr1%1000][addr1/1000].count == 0){
                printf("dfs %d\n", addr1);
                queue[rear] = addr1;
                rear++;
                if (rear == size){
                    size = size*2;
                    queue = (int *)realloc(queue, size * sizeof(int));
                }
            }
            myl++;
        }
        front++;
        printf("%d %d before final update\n", ptr->sum, address);
        final_update(ptr);
        
    }
}

