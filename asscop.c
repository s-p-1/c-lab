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
    printf("deleting dependencies op code %d\n", lhscell->operation);
    if (lhscell->operation != '\0'){
        if (lhscell->operation=='+'|| lhscell->operation =='*'|| lhscell->operation=='-'|| lhscell->operation=='/'){
            printf("deleted from %d %d: %d\n", lhscell->row1, lhscell->col1, lhs);
            mysheet[lhscell->row1][lhscell->col1].cell_avl = deleteNode(mysheet[lhscell->row1][lhscell->col1].cell_avl, lhs);
            mysheet[lhscell->row2][lhscell->col2].cell_avl = deleteNode(mysheet[lhscell->row2][lhscell->col2].cell_avl, lhs);
        }
        else if (lhscell->operation=='t'|| lhscell->operation=='d'|| lhscell->operation=='r'){
            printf("deleted from %d %d: %d\n", lhscell->row2, lhscell->col2, lhs);
            mysheet[lhscell->row2][lhscell->col2].cell_avl = deleteNode(mysheet[lhscell->row2][lhscell->col2].cell_avl, lhs);
        }
        else if (lhscell->operation=='T'|| lhscell->operation=='D'|| lhscell->operation=='R'){
            printf("deleted from %d %d: %d\n", lhscell->row1, lhscell->col1, lhs);
            mysheet[lhscell->row1][lhscell->col1].cell_avl = deleteNode(mysheet[lhscell->row1][lhscell->col1].cell_avl, lhs);
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


bool edgehandler (int cellhandle, int lhs, cell* lhscell, int extra){
    deleteDependencies(lhscell, lhs);
    printf("Adding to cellhandle: %d, lhs: %d\n", cellhandle, lhs);
    mysheet[cellhandle%1000][cellhandle/1000].cell_avl = insert(mysheet[cellhandle%1000][cellhandle/1000].cell_avl, lhs);
    lhscell->operation = 's';
    if (!dfs(lhs, lhs, true)) {
        printf("cycle detected\n");
        deleteDependencies(lhscell, lhs);
        dfs2(lhs);
        if (mysheet[0][0].cell_avl==NULL) printf("NULL 0 0\n");
        if (mysheet[0][1].cell_avl==NULL) printf("NULL 0 1\n");
        printf("mysheet[0][0].count = %d, mysheet[0][1].count = %d\n", mysheet[0][0].count, mysheet[0][1].count);
        return false;
    }
    lhscell->sum = mysheet[cellhandle%1000][cellhandle/1000].value + extra;

    lhscell->row1 = cellhandle%1000;
    lhscell->col1 = cellhandle/1000;
    lhscell->row2 = cellhandle%1000;
    lhscell->col2 = cellhandle/1000;
    pro_graph(lhs);
    return true;
}


char parser(char* input){
    char *celll=strtok(input , "=");
    char op = 'q';
    int lhs = cell_handler(celll);
    if (lhs == -1) return -1;
    cell* lhscell=mysheet[lhs%1000]+(lhs/1000);
    char* exp=strtok(NULL, "=");
    char *cell1;
    char *cell2;
    char *range;
    int cellhandle=cell_handler(exp);
    if (is_int(exp)) {
        deleteDependencies(lhscell, lhs);
        lhscell->err_cnt=0;
        lhscell->sum = atoi(exp);
        lhscell->operation = '\0';
        dfs(lhs, lhs, true);
        pro_graph(lhs);
        return 'c'; // cell assigned a constant value
    }
    else if (cellhandle!=-1){
        if (!edgehandler(cellhandle, lhs, lhscell, 0)) return -2;
        lhscell->err_cnt=0;
        return '+'; // cell assigned another cell
    }
    else if (strpbrk(exp, "SLEEP")!=NULL){
        char* nub=strtok(exp, "(");
        if(strcmp(nub, "SLEEP")!=0) return -3;
        char* noob=strtok(NULL, "(");
        char* time=strtok(noob, ")");
        if (strtok(NULL, ")") != NULL) return -3;
        if (is_int(time)){
            lhscell->err_cnt=0;
            clock_t curr = clock();
            while (clock()-curr<CLOCKS_PER_SEC*atoi(time));
            deleteDependencies(lhscell, lhs);
            lhscell->sum = atoi(time);
            lhscell->operation = '\0';
            dfs(lhs, lhs, true);
            pro_graph(lhs);
            return 'c'; // cell sleeped for a constant value
        }
        else if (cell_handler(time) != -1){
            int rhs = cell_handler(time);
            if (!edgehandler(rhs, lhs, lhscell, 0)) return -2;
            lhscell->err_cnt=0;
            int timer = mysheet[rhs%1000][rhs/1000].value;
            int err = mysheet[rhs%1000][rhs/1000].err_cnt%100000000;
            if(err > 0)
                lhscell->err_cnt+=1;
            if(lhscell->err_cnt%100000000 == 0){
                clock_t curr = clock();
                while (clock()-curr<CLOCKS_PER_SEC*timer);
            }
            lhscell->operation = 'z';
            return 'z'; //sleep of cell

        }
        else return -3;
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
                lhscell->err_cnt=0;
                dfs(lhs, lhs, true);
                pro_graph(lhs);
                return 'c'; // cell assigned a constant value (a sum of two integers)
            }
            else if (is_int(cell1)) {
                int cell2handle = cell_handler(cell2);
                if (cell2handle == -1) return -1;
                if (!edgehandler(cell2handle, lhs, lhscell, atoi(cell1))) return -2;
                lhscell->err_cnt=0;
                return '+';
            }
            else if (is_int(cell2)) {
                int cell1handle = cell_handler(cell1);
                if (cell1handle == -1) return -1;
                if (!edgehandler(cell1handle, lhs, lhscell, atoi(cell2))) return -2;
                lhscell->err_cnt=0;
                return '+';
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
                lhscell->err_cnt=0;
                dfs(lhs, lhs, true);
                pro_graph(lhs);
                return 'c'; // cell assigned a constant value (a product of two integers)
            }
            else if (is_int(cell1)) {
                int cell2handle = cell_handler(cell2);
                if (cell2handle == -1) return -1;
                lhscell->sum = atoi(cell1)*mysheet[cell2handle%1000][cell2handle/1000].value;
                op = 't';

            }
            else if (is_int(cell2)) {
                op = 'T';
                int cell1handle = cell_handler(cell1);
                if (cell1handle == -1) return -1;
                lhscell->sum = mysheet[cell1handle%1000][cell1handle/1000].value*atoi(cell2);
            }
            else op = '*';
        }
        else if (strpbrk(exp, "/")!=NULL){
            cell1=strtok(exp, "/");
            cell2=strtok(NULL, "/");
            if(is_int(cell1) && is_int(cell2)) {
                deleteDependencies(lhscell, lhs);
                lhscell->sum = atoi(cell1) / atoi(cell2);
                lhscell->operation = '\0';
                lhscell->err_cnt=0;
                dfs(lhs, lhs, true);
                pro_graph(lhs);
                return 'c'; // cell assigned a constant value (a division of two integers)
            }
            else if (is_int(cell1)) {
                op = 'r';
                int cell2handle = cell_handler(cell2);
                if (cell2handle == -1) return -1;
                lhscell->sum= atoi(cell1)/mysheet[cell2handle%1000][cell2handle/1000].value;
            }
            else if (is_int(cell2)) {
                op = 'R';
                int cell1handle = cell_handler(cell1);
                if (cell1handle == -1) return -1;
                lhscell->sum = mysheet[cell1handle%1000][cell1handle/1000].value/atoi(cell2);
            }
            else op = '/';
        }
        else if (strpbrk(exp, "-")!=NULL){
            cell1=strtok(exp, "-");
            cell2=strtok(NULL, "-");
            if(is_int(cell1) && is_int(cell2)) {
                deleteDependencies(lhscell, lhs);
                lhscell->sum = atoi(cell1) - atoi(cell2);
                lhscell->operation = '\0';
                lhscell->err_cnt=0;
                dfs(lhs, lhs, true);
                pro_graph(lhs);
                return 'c'; // cell assigned a constant value (a difference of two integers)
            }
            else if (is_int(cell1)) {
                op = 'd';
                int cell2handle = cell_handler(cell2);
                if (cell2handle == -1) return -1;
                lhscell->sum = atoi(cell1)-mysheet[cell2handle%1000][cell2handle/1000].value;
            }
            else if (is_int(cell2)) {
                op = 'D';
                int cell1handle = cell_handler(cell1);
                if (cell1handle == -1) return -1;
                lhscell->sum = mysheet[cell1handle%1000][cell1handle/1000].value/atoi(cell2);
            }
            else op = '-';
        }
        else return -3;
        if (op=='+'||op=='-'||op=='*'||op=='/'){
            if (cell_handler(cell1) == -1) return -1;
            if (cell_handler(cell2) == -1) return -1;
        }
    }

    else if (strpbrk(exp, "MINMAXAVGSUMSTDEV")!=NULL){
        char* func=strtok(exp, "(");
        char* intmed1 =strtok(NULL, "(");
        cell1=strtok(intmed1, ":");
        char* intmed2 =strtok(NULL, ":");
        cell2=strtok(intmed2, ")");

        if (strtok(NULL, ")") != NULL) return -3;
        if (stringcomp("MIN", exp, '\0')==1) op='m';
        else if (stringcomp("MAX", exp, '\0')==1) op='M';
        else if (stringcomp("AVG", exp, '\0')==1) op='a';
        else if (stringcomp("SUM", exp, '\0')==1) op='s';
        else if (stringcomp("STDEV", exp, '\0')==1) op='S';
        else return -3;
        int cellh1 = cell_handler(cell1);
        int cellh2 = cell_handler(cell2);
        if (cellh1 == -1) return -1;
        if (cellh2 == -1) return -1;
        printf("cellh1, %d, cellh2, %d\n", cellh1, cellh2);
        if (cellh1>cellh2) return -4;
    }
    else return -3;
    
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
    else if (op=='t'|| op=='d'|| op=='r'){
        lhscell->row1 =-1;
        lhscell->col1 =-1;
        lhscell->row2 = cell_handler(cell2)%1000;
        lhscell->col2 = cell_handler(cell2)/1000;
        lhscell->sq_sum = atoi(cell1);
        mysheet[lhscell->row2][lhscell->col2].cell_avl = insert(mysheet[lhscell->row2][lhscell->col2].cell_avl, lhs);
    }

    else if (op=='T'|| op=='D'|| op=='R'){
        lhscell->row2 =-1;
        lhscell->col2 =-1;
        lhscell->row1 = cell_handler(cell1)%1000;
        lhscell->col1 = cell_handler(cell1)/1000;
        lhscell->sq_sum = atoi(cell2);
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
        return -2;
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