#include "helper.h"

/* code to classify the input strings i.e the formulas
 into the required expressions*/

rowcol cell_handler(char *cell){
    extern R, C;
    rowcol rc;
    int col=0;
    int row=0;
    int flag =0;
    int invalid =0;
    while (*cell){
        if (flag==0){
            if (*cell>='A' && *cell<='Z'){
                col=col*26+(*cell-'A'+1);
                cell++;
            }else if (*cell>='1' && *cell<='9'){
                row=*cell-'0';
                cell++;
                flag=1;
            }else{
                invalid = 1;break;
            }
        }
        else{
            if (*cell>='0' && *cell<='9'){
                row=10*row+(*cell-'0');
                cell++;
            }
            else{
                invalid = 1;break;
            }
        }
    }
    if (invalid==0){
        rc.row=row-1;
        rc.col=col-1;
    }
    if (row>=1 && row<=R && col>=1 && col<=C){
        return rc;
    }
    rc.row=-1;
    rc.col=-1;
    return rc;
    // return 0;
}

char parser(char* input[]){
    char *cell;
    char op = '-1';
    cell=strtok(input, "=");
    if (cell_handler(cell).row==-1){
        op = '1';
        return '1';
    }

    char *exp;
    char *cell1;
    char *cell2;
    
    char *range;
    exp=strtok(NULL, "=");
    // printf("%s\n", exp);
    char *arr[200];
    if (cell_handler(exp).row!=-1){
        op = 'c';
        
        return 'c';
    }
    else if (strpbrk(exp, "+-*/")!=NULL){
        if (strpbrk(exp, "+")!=NULL){
            cell1=strtok(exp, "+");
            cell2=strtok(NULL, "+");
            printf("%s %s\n", cell1, cell2);
            op = '+';
        }
        else if (strpbrk(exp, "-")!=NULL){
            cell1=strtok(exp, "-");
            cell2=strtok(NULL, "-");
            op = '-';
        }
        else if (strpbrk(exp, "*")!=NULL){
            cell1=strtok(exp, "*");
            cell2=strtok(NULL, "*");
            op = '*';
        }
        else if (strpbrk(exp, "/")!=NULL){
            cell1=strtok(exp, "/");
            cell2=strtok(NULL, "/");
            op = '/';
        }
        else{
            op = 'q';
            return 'q';
        }
        if (cell_handler(cell1).row==-1){
            op = '2';
            return '2';
        }
        if (cell_handler(cell2).row==-1){
            op = '3';
            return '3';
        }
        // handle the operations here
        return 's';
        printf("%s %s\n", cell1, cell2);
    }
    else if (strpbrk(exp, "MINMAXAVGSUMSTDEVSLEEP")!=NULL){
        // printf("Function\n");
        char *func;
        char *intmed1;
        char *part1;
        char *part2;
        char *intmed2;
        char *extra;
        func=strtok(exp, "(");
        intmed1=strtok(NULL, "(");
        part1=strtok(intmed1, ":");
        intmed2=strtok(NULL, ":");
        part2=strtok(intmed2, ")");
        extra=strtok(NULL, ")");
        if (*extra == '\0'){
            op = 'q';
            return 'q';
        }
        printf("%s %s\n", part1, part2);
        // char* arr1[3];
        if (strstr(exp, "MIN")!=NULL){
            // printf("MIN\n");
            // arr1[0]='f';
            // arr1[1]='1';
            // arr1[2]='\0';
            return 'm';
        }
        else if (strstr(exp, "MAX")!=NULL){
            return 'M';
        }
        else if (strstr(exp, "AVG")!=NULL){
            return 'a';
        }
        else if (strstr(exp, "SUM")!=NULL){
            return 's';
        }
        else if (strstr(exp, "STDEV")!=NULL){
            return 'S';
        }
        else if (strstr(exp, "SLEEP")!=NULL){
            return '-';
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
