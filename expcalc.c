#include<stdio.h>
#include<stdlib.h>
#include<math.h>
#include<limits.h>
#include "helper.h"
void calc_value(cell *cell1) {  // Changed to pointer to modify the actual cell
    int val = 0;
    cell1->sum = 0;     // Initialize sum
    cell1->sq_sum = 0;  // Initialize square sum
    int count = 0;      // For counting elements in range
    
    // Calculate count of elements
    count = (cell1->row2 - cell1->row1 + 1) * (cell1->col2 - cell1->col1 + 1);
    
    // Min operation
    if(cell1->operation == 'm') {  // Changed to match struct comment
        val = INT_MAX;  // Initialize with maximum possible value
        for(int i = cell1->row1; i <= cell1->row2; i++) {
            for(int j = cell1->col1; j <= cell1->col2; j++) {
                val = min(mysheet[i][j].value, val);
            }
        }
    }
    
    // Max operation
    else if(cell1->operation == 'M') {
        val = INT_MIN;  // Initialize with minimum possible value
        for(int i = cell1->row1; i <= cell1->row2; i++) {
            for(int j = cell1->col1; j <= cell1->col2; j++) {
                val = max(mysheet[i][j].value, val);
            }
        }
    }
    
    // Sum operation
    else if(cell1->operation == 's') {
        for(int i = cell1->row1; i <= cell1->row2; i++) {
            for(int j = cell1->col1; j <= cell1->col2; j++) {
                val += mysheet[i][j].value;
            }
        }
        cell1->sum = val;  // Store sum for future use
    }
    
    // Average operation
    else if(cell1->operation == 'a') {
        for(int i = cell1->row1; i <= cell1->row2; i++) {
            for(int j = cell1->col1; j <= cell1->col2; j++) {
                val += mysheet[i][j].value;
            }
        }
        cell1->sum = val;  // Store sum for future use
        val = val / count;
    }
    
    // Standard deviation operation
    else if(cell1->operation == 'S') {
        // First pass: calculate sum and square sum
        for(int i = cell1->row1; i <= cell1->row2; i++) {
            for(int j = cell1->col1; j <= cell1->col2; j++) {
                cell1->sum += mysheet[i][j].value;
                cell1->sq_sum += mysheet[i][j].value * mysheet[i][j].value;
            }
        }
        
        // Calculate mean
        double mean = (double)cell1->sum / count;
        
        // Calculate variance: E(X^2) - (E(X))^2
        double variance = ((double)cell1->sq_sum / count) - (mean * mean);
        
        // Calculate standard deviation
        double x = sqrt(variance);
        val = (int) x;
    }
    
    cell1->value = val;
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