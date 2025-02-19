#include "helper.h"

bool dfs (int address, int parent, bool isbase){
    //detects for cycles and returns false if cycle is detected
    if (!isbase && address == parent){
        return false;
    }
    //objective of this function is to count the number of incoming 
    //edges for each cell and detect the precence of cycles
    bool myb=true;

    if (mysheet[address%1000][address/1000].isv == 1){
        return true;
    }

    mysheet[address%1000][address/1000].isv = 1;

    AVLNode* root = mysheet[address%1000][address/1000].cell_avl;
    int* myl= inorderTraversal(root);
    //doing dfs on the children    

    while (*myl!=-1){

        int addr1= *myl;
        mysheet[addr1%1000][addr1/1000].count += 1;
        // printf("Added now count of child %d : %d\n", addr1, mysheet[addr1%1000][addr1/1000].count);
        // printf("parent %d\n", address);
        if (!dfs(*myl, parent, false)) myb = false;

        myl++;
    }
    
    return myb;

}

void dfs2 (int address){
    //reset all the variables to 0
    if (mysheet[address%1000][address/1000].isv == 0) return;   
    mysheet[address%1000][address/1000].isv = 0;

    AVLNode* root = mysheet[address%1000][address/1000].cell_avl;
    int* myl= inorderTraversal(root);

    while (*myl!=-1){
        int addr1= *myl;
        mysheet[addr1%1000][addr1/1000].count = 0;
        dfs2(*myl);
        myl++;
    }
    return ;
}



void pro_graph(int address){

    // printf("donedfs\n");
    int size = 5;
    int *queue = (int *)malloc(size * sizeof(int));
    
    queue[0] = address;
    int front = 0;
    int rear = 1;
    AVLNode* root = mysheet[address%1000][address/1000].cell_avl;
    // printf("front, rear %d %d\n", front, rear);
    while (rear != front) {

        int address = queue[front];
        // printf("%d address of front\n", address);
        // printf("%d count of front\n", mysheet[address%1000][address/1000].count);
        cell* ptr = mysheet[address%1000]+(address/1000);
        AVLNode* root = mysheet[address%1000][address/1000].cell_avl;

        int* myl= inorderTraversal(root);
        //this array contains adddress of the cells

        while (*myl!=-1){

            int addr1= *myl;
            // printf("count of child %d : %d\n", addr1, mysheet[addr1%1000][addr1/1000].count);
            update_value(mysheet[addr1%1000]+(addr1/1000), address%1000, address/1000);
            mysheet[addr1%1000][addr1/1000].count -= 1;
            
            if (mysheet[addr1%1000][addr1/1000].count <= 0){
                // printf("dfs %d\n", addr1);
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
        // printf("%d %d before final update\n", ptr->sum, address);
        final_update(ptr);
        
    }

    dfs2(address);
}

