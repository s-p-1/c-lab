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
    if (row>=1 && row<=R && col>=1 && col<=C){
        return (col-1)*1000+(row-1);
    }
    
    return -1;
   
}

char parser(char* input){
    char *celll=strtok(input , "=");
    char op = 'q';
    int lhs = cell_handler(celll);
    if (lhs == -1) return 'q';
    cell* lhscell=mysheet[lhs%1000]+(lhs/1000);
    char* exp=strtok(NULL, "=");
    char *cell1;
    char *cell2;    
    char *range;
    if (is_int(exp)) {
        printf("done_parser\n");
        op=lhscell->operation;
        if (op != '\0'){
            if (op=='+'|| op =='*'|| op=='-'|| op=='/'){
                mysheet[lhscell->row1][lhscell->col1].cell_avl = deleteNode(lhscell->cell_avl, lhs);
                mysheet[lhscell->row2][lhscell->col2].cell_avl = deleteNode(lhscell->cell_avl, lhs);
            }
            else{
                for (int i =lhscell->row1; i<=lhscell->row2; i++){
                    for (int j = lhscell->col1; j<=lhscell->col2; j++){
                        mysheet[i][j].cell_avl = deleteNode(mysheet[i][j].cell_avl, lhs);
                    }
                }
            }
        } 
        lhscell->sum = atoi(exp);
        lhscell->operation = '\0';

        pro_graph(lhs);

        return 'c';
    }
    if (cell_handler(exp) != -1){
        op = 'C';
    }
    else if (strpbrk(exp, "+-*/")!=NULL){
        if (strpbrk(exp, "+")!=NULL){
            cell1=strtok(exp, "+");
            cell2=strtok(NULL, "+");
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
        else return 'q';
        if (cell_handler(cell1) == -1) return 'q';        
        if (cell_handler(cell2) == -1) return 'q';
        
        // handle the operations here
    }
    else if (strpbrk(exp, "MINMAXAVGSUMSTDEVSLEEP")!=NULL){
        char* func=strtok(exp, "(");
        char* intmed1 =strtok(NULL, "(");
        cell1=strtok(intmed1, ":");
        char* intmed2 =strtok(NULL, ":");
        cell2=strtok(intmed2, ")");
        if (strtok(NULL, ")") != NULL) return 'q';
        if (stringcomp("MIN", exp, '\0')==1) op='m';
        else if (stringcomp("MAX", exp, '\0')==1) op='M';
        else if (stringcomp("AVG", exp, '\0')==1) op='a';
        else if (stringcomp("SUM", exp, '\0')==1) op='s';
        else if (stringcomp("STDEV", exp, '\0')==1) op='S';
        else if (stringcomp("SLEEP", exp, '\0')==1) op='-';
        else return 'q';
    }
    if (lhscell->operation != '\0'){
        if (lhscell->operation=='+'|| lhscell->operation =='*'|| lhscell->operation=='-'|| lhscell->operation=='/'){
            mysheet[lhscell->row1][lhscell->col1].cell_avl = deleteNode(lhscell->cell_avl, lhs);
            mysheet[lhscell->row2][lhscell->col2].cell_avl = deleteNode(lhscell->cell_avl, lhs);
        }
        else{
            for (int i =lhscell->row1; i<=lhscell->row2; i++){
                for (int j = lhscell->col1; j<=lhscell->col2; j++){
                    mysheet[i][j].cell_avl = deleteNode(mysheet[i][j].cell_avl, lhs);
                }
            }
        }
    } 
    printf("done_parserop\n");
    lhscell->operation = op;
    printf("%d\n", 1);
    printf("%s %s\n", cell1, cell2);
    lhscell->row1 = cell_handler(cell1)%1000;
    lhscell->col1 = cell_handler(cell1)/1000;
    lhscell->row2 = cell_handler(cell2)%1000;
    lhscell->col2 = cell_handler(cell2)/1000;
    if (op=='+'|| op =='*'|| op=='-'|| op=='/'){
        mysheet[lhscell->row1][lhscell->col1].cell_avl = insert(lhscell->cell_avl, lhs);
        mysheet[lhscell->row2][lhscell->col2].cell_avl = insert(lhscell->cell_avl, lhs);
    }
    else{
        for (int i =lhscell->row1; i<=lhscell->row2; i++){
            for (int j = lhscell->col1; j<=lhscell->col2; j++){
                mysheet[i][j].cell_avl = insert(mysheet[i][j].cell_avl, lhs);
            }
        }
    }
    printf("done_calc1\n");
    calc_value(lhscell);
    printf("done_calc\n");
    pro_graph(lhs);
    printf("done_parser\n");
    return op;
}
// int main() {
//     char result = parser();
//     printf("%c\n", result);
//     return 0;
// }
