#include "helper.h"
void calc_value(cell *cell1) {  // Changed to pointer to modify the actual cell
    int val = 0;
    // cell1->sum = 0;     // Initialize sum
    // cell1->sq_sum = 0;  // Initialize square sum
    int count = 0;      // For counting elements in range
    
    // Calculate count of elements
    count = (cell1->row2 - cell1->row1 + 1) * (cell1->col2 - cell1->col1 + 1);
    cell1->err_cnt=100000000*(cell1->err_cnt/100000000);
    if(cell1->operation == '+'){
        freeTree(cell1->range_min_max);
        val = mysheet[cell1->row1][cell1->col1].value+mysheet[cell1->row2][cell1->col2].value;
        cell1->sum = val;  //i will update sum and keep the init_value same while updating so that i can have both final_value and init_value and i don't have to make new variable for this
        if(mysheet[cell1->row1][cell1->col1].err_cnt>0){
            cell1->err_cnt+=1;
        }
        if(mysheet[cell1->row2][cell1->col2].err_cnt >0){
            cell1->err_cnt+=1;
        }
    }

    else if(cell1->operation == '-'){
        freeTree(cell1->range_min_max);
        val = mysheet[cell1->row1][cell1->col1].value-mysheet[cell1->row2][cell1->col2].value;
        cell1->sum = val;
        if(mysheet[cell1->row1][cell1->col1].err_cnt>0){
            cell1->err_cnt+=1;
        }
        if(mysheet[cell1->row2][cell1->col2].err_cnt >0){
            cell1->err_cnt+=1;
        }
    }

    else if(cell1->operation == '*'){
        freeTree(cell1->range_min_max);
        val = mysheet[cell1->row1][cell1->col1].value*mysheet[cell1->row2][cell1->col2].value;
        cell1->sum = val;
        if(mysheet[cell1->row1][cell1->col1].err_cnt>0){
            cell1->err_cnt+=1;
        }
        if(mysheet[cell1->row2][cell1->col2].err_cnt >0){
            cell1->err_cnt+=1;
        }
    }

    else if(cell1->operation == '/'){
        freeTree(cell1->range_min_max);
        if(mysheet[cell1->row1][cell1->col1].err_cnt>0){
            cell1->err_cnt+=1;
        }
        if(mysheet[cell1->row2][cell1->col2].err_cnt >0){
            cell1->err_cnt+=1;
        }
        if(mysheet[cell1->row2][cell1->col2].value == 0){
            if(!(mysheet[cell1->row2][cell1->col2].err_cnt >0))
                cell1->err_cnt+=1;
            return;
        }
        val = mysheet[cell1->row1][cell1->col1].value/mysheet[cell1->row2][cell1->col2].value;
        cell1->sum = val;
    }
    
    // Min operation
    else if(cell1->operation == 'm') {
        val = INT_MAX;  // Initialize with maximum possible value
        freeTree(cell1->range_min_max);
        cell1->range_min_max = NULL;
        for(int i = cell1->row1; i <= cell1->row2; i++) {
            for(int j = cell1->col1; j <= cell1->col2; j++) {
                val = min(mysheet[i][j].value, val);
                cell1->range_min_max = insert(cell1->range_min_max, mysheet[i][j].value);
                if(mysheet[i][j].err_cnt>0){
                    cell1->err_cnt+=1;
                }
            }
        }
        cell1->sum = val;
    }
    
    // Max operation
    else if(cell1->operation == 'M') {
        val = INT_MIN;  // Initialize with minimum possible value
        freeTree(cell1->range_min_max);
        cell1->range_min_max = NULL;
        for(int i = cell1->row1; i <= cell1->row2; i++) {
            for(int j = cell1->col1; j <= cell1->col2; j++) {
                val = max(mysheet[i][j].value, val);
                cell1->range_min_max = insert(cell1->range_min_max, mysheet[i][j].value);
                if(mysheet[i][j].err_cnt>0){
                    cell1->err_cnt+=1;
                }
            }
        }
        cell1->sum = val;
    }
    
    // Sum operation
    else if(cell1->operation == 's') {
        freeTree(cell1->range_min_max);
        for(int i = cell1->row1; i <= cell1->row2; i++) {
            for(int j = cell1->col1; j <= cell1->col2; j++) {
                val += mysheet[i][j].value;
                if(mysheet[i][j].err_cnt>0){
                    cell1->err_cnt+=1;
                }
            }
        }
        cell1->sum = val;  // Store sum for future use

    }
    
    // Average operation
    else if(cell1->operation == 'a') {
        freeTree(cell1->range_min_max);
        for(int i = cell1->row1; i <= cell1->row2; i++) {
            for(int j = cell1->col1; j <= cell1->col2; j++) {
                val += mysheet[i][j].value;
                if(mysheet[i][j].err_cnt>0){
                    cell1->err_cnt+=1;
                }
            }
        }
        cell1->sum = val;  // Store sum for future use
        // val = val / count;
    }
    
    // Standard deviation operation
    else if(cell1->operation == 'S') {
        // First pass: calculate sum and square sum
        freeTree(cell1->range_min_max);
        for(int i = cell1->row1; i <= cell1->row2; i++) {
            for(int j = cell1->col1; j <= cell1->col2; j++) {
                cell1->sum += mysheet[i][j].value;
                cell1->sq_sum += mysheet[i][j].value * mysheet[i][j].value;
                if(mysheet[i][j].err_cnt>0){
                    cell1->err_cnt+=1;
                }
            }
        }
    }
    
    // cell1->value = val;
}

int new_value(int row, int col, int sq_sum) {
    if (row < 0 || col < 0) return sq_sum;
    int new_val =0;
    if (mysheet[row][col].operation == 'S') {
        int count = (mysheet[row][col].row2 - mysheet[row][col].row1 + 1) * (mysheet[row][col].col2 - mysheet[row][col].col1 + 1);
        double mean = (double)mysheet[row][col].sum / count;
        double variance = ((double)mysheet[row][col].sq_sum / count) - (double)(2*(double)mean*(int)mean) + (double)((int)mean * (int)mean);
        double std_dev = sqrt(variance);
        new_val = (int)round(std_dev);
    } else if (mysheet[row][col].operation == 'a') {
        int count = (mysheet[row][col].row2 - mysheet[row][col].row1 + 1) * (mysheet[row][col].col2 - mysheet[row][col].col1 + 1);
        new_val = mysheet[row][col].sum / count;
    } else {
        new_val = mysheet[row][col].sum;
    }
    return new_val;
}

void update_value(cell *cell1, int row, int col){
    printf("started update %d", cell1->err_cnt);
    int new_val = new_value(row, col, 0);
    int old_val = mysheet[row][col].value;
    int err1 = mysheet[row][col].err_cnt/100000000;
    int err2 = mysheet[row][col].err_cnt%100000000;
    if (cell1->operation == 'z') {
        if(err1 > 0 && err2 == 0)
            cell1->err_cnt-=1;
        else if(err1 == 0  && err2 > 0)
            cell1->err_cnt+=1;
        if(cell1->err_cnt%100000000 == 0){
            clock_t curr = clock();
            while (clock()-curr<CLOCKS_PER_SEC*new_val);
        }
        cell1->sum = new_val;
    } else if (cell1->operation == '+') {
        cell1->sum += (new_val - old_val);
        if(err1 > 0 && err2 == 0)
            cell1->err_cnt-=1;
        else if(err1 == 0  && err2 > 0)
            cell1->err_cnt+=1;
    } else if (cell1->operation == '-' || cell1->operation == 'd' || cell1->operation == 'D') {
        if (cell1->row1 == row && cell1->col1 == col) {
            cell1->sum += (new_val - old_val);
        } else {
            cell1->sum -= (new_val - old_val);
        }
        if(err1 > 0 && err2 == 0)
            cell1->err_cnt-=1;
        else if(err1 == 0  && err2 > 0)
            cell1->err_cnt+=1;
    } else if (cell1->operation == '*' || cell1->operation == 't' || cell1->operation == 'T') {
        if (cell1->row1 == row && cell1->col1 == col) {
            cell1->sum = new_val * new_value(cell1->row2, cell1->col2, cell1->sq_sum);
        } else {
            cell1->sum = new_value(cell1->row1, cell1->col1, cell1->sq_sum) * new_val;
        }
        if(err1 > 0 && err2 == 0)
            cell1->err_cnt-=1;
        else if(err1 == 0  && err2 > 0)
            cell1->err_cnt+=1;
    } else if (cell1->operation == '/' || cell1->operation == 'r' || cell1->operation == 'R') {
        if (cell1->row1 == row && cell1->col1 == col) {
            int temp=0;
            if((temp =new_value(cell1->row2, cell1->col2, cell1->sq_sum))!=0)
                cell1->sum = new_val / temp;
            if(mysheet[row][col].err_cnt/100000000 > 0  && mysheet[row][col].err_cnt%100000000 == 0)
                cell1->err_cnt-=1;
            else if(mysheet[row][col].err_cnt/100000000 == 0  && mysheet[row][col].err_cnt%100000000 > 0)
                cell1->err_cnt+=1;
        } else {
            if (new_val != 0) {
                cell1->sum = new_value(cell1->row1, cell1->col1, cell1->sq_sum) / new_val;
                if((old_val == 0 || mysheet[row][col].err_cnt/100000000 > 0)  && mysheet[row][col].err_cnt%100000000 == 0)
                    cell1->err_cnt-=1;
                if(old_val !=0 && mysheet[row][col].err_cnt/100000000 == 0  && mysheet[row][col].err_cnt%100000000 > 0)
                    cell1->err_cnt+=1;
            } else {
                if(old_val != 0 && mysheet[row][col].err_cnt/100000000 == 0)
                    cell1->err_cnt+=1;
            }
        }
    } else if (cell1->operation == 'm') {
        cell1->range_min_max = deleteNode(cell1->range_min_max, old_val);
        cell1->range_min_max = insert(cell1->range_min_max, new_val);
        cell1->sum = (minValueNode(cell1->range_min_max))->value;
        if(mysheet[row][col].err_cnt/100000000 > 0  && mysheet[row][col].err_cnt%100000000 == 0)
            cell1->err_cnt-=1;
        else if(mysheet[row][col].err_cnt/100000000 == 0  && mysheet[row][col].err_cnt%100000000 > 0)
            cell1->err_cnt+=1;
    } else if (cell1->operation == 'M') {
        cell1->range_min_max = deleteNode(cell1->range_min_max, old_val);
        cell1->range_min_max = insert(cell1->range_min_max, new_val);
        cell1->sum = (maxValueNode(cell1->range_min_max))->value;
        if(mysheet[row][col].err_cnt/100000000 > 0  && mysheet[row][col].err_cnt%100000000 == 0)
            cell1->err_cnt-=1;
        else if(mysheet[row][col].err_cnt/100000000 == 0  && mysheet[row][col].err_cnt%100000000 > 0)
            cell1->err_cnt+=1;
    } else if (cell1->operation == 's') {
        cell1->sum += (new_val - old_val);
        if(mysheet[row][col].err_cnt/100000000 > 0  && mysheet[row][col].err_cnt%100000000 == 0)
            cell1->err_cnt-=1;
        else if(mysheet[row][col].err_cnt/100000000 == 0  && mysheet[row][col].err_cnt%100000000 > 0)
            cell1->err_cnt+=1;
    } else if (cell1->operation == 'a') {
        int count = (cell1->row2 - cell1->row1 + 1) * (cell1->col2 - cell1->col1 + 1);
        cell1->sum += (new_val - old_val);
        cell1->value = cell1->sum / count;
        if(mysheet[row][col].err_cnt/100000000 > 0  && mysheet[row][col].err_cnt%100000000 == 0)
            cell1->err_cnt-=1;
        else if(mysheet[row][col].err_cnt/100000000 == 0  && mysheet[row][col].err_cnt%100000000 > 0)
            cell1->err_cnt+=1;
    } else if (cell1->operation == 'S') {
        int count = (cell1->row2 - cell1->row1 + 1) * (cell1->col2 - cell1->col1 + 1);
        cell1->sum += (new_val - old_val);
        cell1->sq_sum += (new_val * new_val - old_val * old_val);
        double mean = (double)cell1->sum / count;
        double variance = ((double)cell1->sq_sum / count) - (mean * mean);
        cell1->value = (int)sqrt(variance);
        if(mysheet[row][col].err_cnt/100000000 > 0  && mysheet[row][col].err_cnt%100000000 == 0)
            cell1->err_cnt-=1;
        else if(mysheet[row][col].err_cnt/100000000 == 0  && mysheet[row][col].err_cnt%100000000 > 0)
            cell1->err_cnt+=1;
    }
}

void final_update(cell *cell1){
    if(cell1->operation == 'S'){
        int count = (cell1->row2 - cell1->row1 + 1) * (cell1->col2 - cell1->col1 + 1);
        double mean = (double)cell1->sum / count;
        double variance = ((double)cell1->sq_sum / count) - (double)(2*(double)mean*(int)mean) + (double)((int)mean * (int)mean);
        cell1->value = (int)round(sqrt(variance));
    }
    else if(cell1->operation == 'a'){
        int count = (cell1->row2 - cell1->row1 + 1) * (cell1->col2 - cell1->col1 + 1);
        cell1->value = cell1->sum / count;
    }
    else{
        cell1->value= cell1->sum;
    }
    if((cell1->err_cnt)%100000000 > 0)
        cell1->err_cnt = (cell1->err_cnt)%100000000 + 100000000;
    else cell1->err_cnt = 0;
}

// int main(){
//     for(int i=0; i<5; i++){
//         for(int j=0; j<2; j++){
//             mysheet[i][j].value=i+j;
//         }
//     }
//     mysheet[5][2].row1 = 0;
//     mysheet[5][2].row2 = 4;
//     mysheet[5][2].col1 = 0;
//     mysheet[5][2].col2 = 1;
//     mysheet[5][2].operation = 'm';
//     calc_value(&mysheet[5][2]);
//     printf("%d", mysheet[5][2].value);
//     return 0;
// }