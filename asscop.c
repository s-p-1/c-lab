#include "helper.h"

bool is_int (char *s){
    int i =0;
    if (s[i]=='+' || s[i]=='-') i++; //to allow the optional sign in the beginning
    if (s[i]=='\0') return false; //if the string has no numerals
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
    // printf("row: %d col: %d\n", row, col);
    if (row>=1 && row<=R && col>=1 && col<=C){
        return (col-1)*1000+(row-1);
    }
    
    return -1;
   
}
void deleteDependencies(cell *lhscell, int lhs){
    if (lhscell->operation != '\0'){
        if (lhscell->operation=='+'|| lhscell->operation =='*'|| lhscell->operation=='-'|| lhscell->operation=='/'){
            mysheet[lhscell->row1][lhscell->col1].cell_avl = deleteNode(lhscell->cell_avl, lhs);
            mysheet[lhscell->row2][lhscell->col2].cell_avl = deleteNode(lhscell->cell_avl, lhs);
        }
        else{
            for (int i =lhscell->row1; i<=lhscell->row2; i++){
                for (int j = lhscell->col1; j<=lhscell->col2; j++){
                    mysheet[i][j].cell_avl = deleteNode(mysheet[i][j].cell_avl, lhs);
                    printf("deleted from %d %d: %d\n", i, j, lhs);
                }
            }
        }
    }
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
        deleteDependencies(lhscell, lhs);
        lhscell->sum = atoi(exp);
        lhscell->operation = '\0';
        dfs(lhs, lhs, true);
        pro_graph(lhs);
        return 'c'; // cell assigned a constant value
    }
    else if (strpbrk(exp, "SLEEP")!=NULL){
        char* nub=strtok(exp, "(");
        if(strcmp(nub, "SLEEP")!=0) return 'q';
        char* noob=strtok(NULL, "(");
        char* time=strtok(noob, ")");
        if (strtok(NULL, ")") != NULL) return 'q';
        if (is_int(time)){
            deleteDependencies(lhscell, lhs);
            if (atoi(time)<0){
                lhscell->sum = atoi(time);
                lhscell->operation = '\0';
            }
            else{
                lhscell->sum = atoi(time);
                lhscell->operation = '\0';
                sleep(atoi(time));

            }  
            return 'c'; // cell assigned a constant value
        }
        else if (cell_handler(time) != -1){
            int rhs = cell_handler(time);
        }
        else return 'q';
        

        op = 'z';
    }

    else if (strpbrk(exp, "+-*/")!=NULL){
        if (strpbrk(exp, "+")!=NULL){
            printf("here in +\n");
            cell1=strtok(exp, "+");
            cell2=strtok(NULL, "+");
            if(is_int(cell1) && is_int(cell2)) {
                deleteDependencies(lhscell, lhs);
                lhscell->sum = atoi(cell1) + atoi(cell2);
                lhscell->operation = '\0';
                dfs(lhs, lhs, true);
                pro_graph(lhs);
                return 'c'; // cell assigned a constant value (a sum of two integers)
            }
            else if (is_int(cell1)) {
                op = 'p';
                printf("here in +a\n");
            }
            else if (is_int(cell2)) {
                op = 'P';
                printf("here in +A\n");
            }
            else op = '+';
        }
       
        else if (strpbrk(exp, "*")!=NULL){
            cell1=strtok(exp, "*");
            cell2=strtok(NULL, "*");
            if(is_int(cell1) && is_int(cell2)) {
                deleteDependencies(lhscell, lhs);
                lhscell->sum = atoi(cell1) * atoi(cell2);
                lhscell->operation = '\0';
                dfs(lhs, lhs, true);
                pro_graph(lhs);
                return 'c'; // cell assigned a constant value (a product of two integers)
            }
            else if (is_int(cell1)) op = 't';
            else if (is_int(cell2)) op = 'T';
            else op = '*';
        }
        else if (strpbrk(exp, "/")!=NULL){
            cell1=strtok(exp, "/");
            cell2=strtok(NULL, "/");
            if(is_int(cell1) && is_int(cell2)) {
                deleteDependencies(lhscell, lhs);
                lhscell->sum = atoi(cell1) / atoi(cell2);
                lhscell->operation = '\0';
                dfs(lhs, lhs, true);
                pro_graph(lhs);
                return 'c'; // cell assigned a constant value (a division of two integers)
            }
            else if (is_int(cell1)) op = 'r';
            else if (is_int(cell2)) op = 'R';
            else op = '/';
        }
        else if (strpbrk(exp, "-")!=NULL){
            cell1=strtok(exp, "-");
            cell2=strtok(NULL, "-");
            if(is_int(cell1) && is_int(cell2)) {
                deleteDependencies(lhscell, lhs);
                lhscell->sum = atoi(cell1) - atoi(cell2);
                lhscell->operation = '\0';
                dfs(lhs, lhs, true);
                pro_graph(lhs);
                return 'c'; // cell assigned a constant value (a difference of two integers)
            }
            else if (is_int(cell1)) op = 'd';
            else if (is_int(cell2)) op = 'D';
            else op = '-';
        }
        else return 'q';
        if (op=='+'||op=='-'||op=='*'||op=='/'){
            if (cell_handler(cell1) == -1) return 'q';        
            if (cell_handler(cell2) == -1) return 'q';
        }
    }

    else if (strpbrk(exp, "MINMAXAVGSUMSTDEV")!=NULL){
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
        else return 'q';
    }
    else if (cell_handler(exp) != -1){
        op = 'C'; // cell assigned another cell
        int rhs = cell_handler(exp);
    }
    else return 'q';
    deleteDependencies(lhscell, lhs);
    lhscell->operation = op;
    if (op=='+'|| op =='*'|| op=='-'|| op=='/'){
        lhscell->row1 = cell_handler(cell1)%1000;
        lhscell->col1 = cell_handler(cell1)/1000;
        lhscell->row2 = cell_handler(cell2)%1000;
        lhscell->col2 = cell_handler(cell2)/1000;
        mysheet[lhscell->row1][lhscell->col1].cell_avl = insert(mysheet[lhscell->row1][lhscell->col1].cell_avl, lhs);
        mysheet[lhscell->row2][lhscell->col2].cell_avl = insert(mysheet[lhscell->row2][lhscell->col2].cell_avl, lhs);
    }
    else if (op=='t'|| op=='d'|| op=='p'|| op=='r'){
        lhscell->row2 = cell_handler(cell2)%1000;
        lhscell->col2 = cell_handler(cell2)/1000;
        mysheet[lhscell->row2][lhscell->col2].cell_avl = insert(mysheet[lhscell->row2][lhscell->col2].cell_avl, lhs);
    }
    
    else if (op=='T'|| op=='D'|| op=='P'|| op=='R'){
        lhscell->row1 = cell_handler(cell1)%1000;
        lhscell->col1 = cell_handler(cell1)/1000;
        mysheet[lhscell->row1][lhscell->col1].cell_avl = insert(mysheet[lhscell->row1][lhscell->col1].cell_avl, lhs);
    }
    else if (op=='C'){
        lhscell->row1 = cell_handler(exp)%1000;
        lhscell->col1 = cell_handler(exp)/1000;
        mysheet[lhscell->row1][lhscell->col1].cell_avl = insert(mysheet[lhscell->row1][lhscell->col1].cell_avl, lhs);
    }
    else{
        lhscell->row1 = cell_handler(cell1)%1000;
        lhscell->col1 = cell_handler(cell1)/1000;
        lhscell->row2 = cell_handler(cell2)%1000;
        lhscell->col2 = cell_handler(cell2)/1000;
        for (int i =lhscell->row1; i<=lhscell->row2; i++){
            for (int j = lhscell->col1; j<=lhscell->col2; j++){
                if (mysheet[i][j].cell_avl==NULL) printf("NULL1\n");
                mysheet[i][j].cell_avl = insert(mysheet[i][j].cell_avl, lhs);
                if (mysheet[i][j].cell_avl==NULL) printf("NULL2\n");
            }
        }
    }

    if (!dfs(lhs, lhs, true)) {
        printf("cycle detected\n");
        deleteDependencies(lhscell, lhs);
        dfs2(lhs);
        return 'q';
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
