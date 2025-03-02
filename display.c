#include "helper.h"
int maxibigi = 2000000;
int R, C;
bigdeps * bigies;
int bigifront=0;
cell ** mysheet; //2D array of cells
//a file that runs until q and initializes display

char * print_string(int n, int padding){
    if (n<26){
        char * s = (char *)malloc(2 * sizeof(char));
        s[0] = 'A' + n;
        s[1] = '\0';
        printf("%*s", padding, s);
        free(s);
    }
    else if (n<26+26*26){
        char * s = (char *)malloc(3 * sizeof(char));
        s[0] = 'A' + n/26 - 1;
        s[1] = 'A' + n%26;
        s[2] = '\0';
        printf("%*s", padding, s);
        free(s);
    }else{
        char * s = (char *)malloc(4 * sizeof(char));
        int q = n/26-1;
        s[0] = 'A' + q/26 - 1;
        s[1] = 'A' + q%26;
        s[2] = 'A' + n%26;
        s[3] = '\0';
        printf("%*s", padding, s);
        free(s);
    }
}

void display (cell ** mysheet, int R, int C, int x, int y){
    print_string(y, 15);
    for (int j = y+1; j < min(C, y+10); j++) print_string (j, 12);
    printf("\n");
    for (int i = x; i < min(R, x+10); i++){
        printf("%3d", i+1);
        for (int j = y; j < min(C, y+10); j++){
            if (mysheet[i][j].err_cnt>0) printf("%12s", "ERR");
            else printf("%12d", mysheet[i][j].value);
        }
        printf("\n");

    }
    fflush(stdout);
}


int main(int argc, char *argv[]){
    //timing
    clock_t st = clock();
    //initialization
    if(!is_int(argv[1]) || !is_int(argv[2])) {
        printf("error: write valid number of rows and columns.\n");
        return 0;
    }
    R = atoi (argv[1]);
    C = atoi (argv[2]);
    if(R<1 || R>999 || C<1 || C>18278){
        printf("error: write rows and columns in the specified range.\n");
        return 0;
    }
    int maxbigies = 30000;
    bigies = (bigdeps *)malloc(maxbigies*sizeof(bigdeps));

    mysheet = (cell **)malloc(R * sizeof(cell *));
    for (int i = 0; i < R; i++) mysheet[i] = (cell *)calloc(C , sizeof(cell));
    int x=0, y=0, flag=1;
    display(mysheet, R, C, x, y);
    printf("[%.1f] (ok) > ", (((double)(clock()- st))/CLOCKS_PER_SEC));
    st = clock();

    int gl = get_line();
    while (gl != 5){

        if (gl == 6) flag=0;
        if (gl == 7) flag=1;
        
        if (gl >=1000){
            x=(gl-1000)%1000;
            y=(gl-1000)/1000;
        }

        if (gl == 2) y = max(0, y-10);
        if (gl == 4) y = min(C-10, y+10);
        if (gl == 1) x = max(0, x-10);
        if (gl == 3) x = min(R-10, x+10);
        
        if (flag) display(mysheet, R, C, x, y);
        if (gl ==-1) printf("[%.1f] (invalid cell) > ", ((double)(clock()- st)/CLOCKS_PER_SEC));
        else if (gl ==-2) printf("[%.1f] (cycle detected) > ", ((double)(clock()- st)/CLOCKS_PER_SEC));
        else if (gl ==-3) printf("[%.1f] (unrecognized cmd) > ", ((double)(clock()- st)/CLOCKS_PER_SEC));
        else if (gl ==-4) printf("[%.1f] (Invalid range) > ", ((double)(clock()- st)/CLOCKS_PER_SEC));
        else printf("[%.1f] (ok) > ", ((double)(clock()- st)/CLOCKS_PER_SEC));
        st=clock();
        gl = get_line();
    }
    for (int i = 0; i < R; i++) {
        for (int j = 0; j < C; j++) {
            freeTree(mysheet[i][j].cell_avl);
            freeTree(mysheet[i][j].range_min_max);
        }
        free(mysheet[i]);
    }
    free(mysheet);
    free(bigies);
    return 0;
}
