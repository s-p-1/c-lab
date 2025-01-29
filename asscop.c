#include<stdio.h>
#include<string.h>
/* code to classify the input strings i.e the formulas
 into the required expressions*/

// int cell_handler(char *cell){
//     /*function to determine whether the cell is 
//     in the range or not*/
//     return 1;
//     // return 0;
// }
char* parser(){
    char input[]="a1=a2+a3";
    char *cell;
    cell=strtok(input, "=");
    // if (cell_handler(cell)==0){
    //     printf("Cell out of range\n");
    // }
    
        char *exp;
        char *cell1;
        char *cell2;
        char *range;
        exp=strtok(NULL, "=");
        // printf("%s\n", exp);
        char *arr[200];
        if (strpbrk(exp, "+-*/")!=NULL){
            if (strpbrk(exp, "+")!=NULL){
                cell1=strtok(exp, "+");
                cell2=strtok(NULL, "+");
                printf("%s %s\n", cell1, cell2);
                return "a1";
            }
            else if (strpbrk(exp, "-")!=NULL){
                cell1=strtok(exp, "-");
                cell2=strtok(NULL, "-");
                return "a2";
            }
            else if (strpbrk(exp, "*")!=NULL){
                cell1=strtok(exp, "*");
                cell2=strtok(NULL, "*");
                return "a3";
            }
            else if (strpbrk(exp, "/")!=NULL){
                cell1=strtok(exp, "/");
                cell2=strtok(NULL, "/");
                return "a4";
            }
            printf("%s %s\n", cell1, cell2);
        }
        else if (strpbrk(exp, "MINMAXAVGSUMSTDEVSLEEP")!=NULL){
            // printf("Function\n");
            char *func;
            char *intmed1;
            char *part1;
            char *part2;
            char *intmed2;
            func=strtok(exp, "(");
            intmed1=strtok(NULL, "(");
            part1=strtok(intmed1, ":");
            intmed2=strtok(NULL, ":");
            part2=strtok(intmed2, ")");
            printf("%s %s\n", part1, part2);
            // char* arr1[3];
            if (strstr(exp, "MIN")!=NULL){
                // printf("MIN\n");
                // arr1[0]='f';
                // arr1[1]='1';
                // arr1[2]='\0';
                return "f1";
            }
            else if (strstr(exp, "MAX")!=NULL){
                return "f2";
            }
            else if (strstr(exp, "AVG")!=NULL){
                return "f3";
            }
            else if (strstr(exp, "SUM")!=NULL){
                return "f4";
            }
            else if (strstr(exp, "STDEV")!=NULL){
                return "f5";
            }
            else if (strstr(exp, "SLEEP")!=NULL){
                return "f6";
            }
        }

        else{
            return "a";
        }
    return "a";
}
// int main() {
//     char* result = parser();
//     if (strcmp(result, "a")!=0) {
//         printf("Result: %s\n", result);
//     } else {
//         printf("No match found.\n");
//     }
//     return 0;
// }
