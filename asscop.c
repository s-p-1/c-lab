#include "helper.h"

bool is_int (char *s){
    int i =0;
    if (s[i]=='+' || s[i]=='-') i++; //to allow the optional sign in the beginning
    if (s[i]=='\0') return false; //if the string has no neumerals
    while (s[i]!='\0'){
        if (s[i]<'0' || s[i]>'9') return false;
        i++; //if the string has any non-numerals
    }
    return true;
}

/* code to classify the input strings i.e the formulas
 into the required expressions*/

int cell_handler(char *cell){

    int col=0, row=0, flag=0, invalid=0;
    while (*cell){

        if (flag==0){

            if (*cell>='A' && *cell<='Z'){
                col=col*26+(*cell-'A'+1);
            }else if (*cell>='1' && *cell<='9'){
                row=*cell-'0';
                flag=1;
            }else return -1;

        }else{

            if (*cell>='0' && *cell<='9'){
                row=10*row+(*cell-'0');
            }
            else return -1;

        }cell++;
    }
    printf("%d %d\n", R, C);
    if (row>=1 && row<=R && col>=1 && col<=C){
        return (col-1)*1000+(row-1);
    }
    
    return -1;
   
}

char parser(char* input){
    char *celll=strtok(input , "=");
    char op = '\0';
    int lhs = cell_handler(celll);
    printf("%d\n", lhs);
    printf("%s\n", celll);
    if (lhs == -1){
        op = '1';
        return '1';
    }
    cell* lhscell=mysheet[lhs/1000]+(lhs%1000);

    char* exp=strtok(NULL, "=");
    printf("%s\n", exp);
    char *cell1;
    char *cell2;
    
    char *range;
    // printf("%s\n", exp);
    if (is_int(exp)) {
        lhscell->value = atoi(exp);
        return 'c';
    }
    if (cell_handler(exp) != -1){
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
        if (cell_handler(cell1) == -1){
            op = '2';
            return 'q';
        }
        if (cell_handler(cell2) == -1){
            op = '3';
            return 'q';
        }
        // handle the operations here
        return 's';
        printf("%s %s\n", cell1, cell2);
    }
    else if (strpbrk(exp, "MINMAXAVGSUMSTDEVSLEEP")!=NULL){
        // printf("Function\n");
        printf("%d\n", 7777);
        char* func=strtok(exp, "(");
        printf("%d\n", 8888);
        char* intmed1 =strtok(NULL, "(");
        printf("%d\n", 7788);
        printf("%s\n", intmed1);
        char* part1=strtok(intmed1, ":");
        printf("%s\n", part1);
        char* intmed2 =strtok(NULL, ":");
        printf("%s\n", intmed2);
        char* part2=strtok(intmed2, ")");
        printf("%s\n", part2);
        if (strtok(NULL, ")") != NULL){
            printf("Invalid\n");
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
    return 'q';
}
// int main() {
//     char result = parser();
//     printf("%c\n", result);
//     return 0;
// }
