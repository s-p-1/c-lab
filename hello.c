#include <stdio.h>
#include <stdlib.h>

int min(int a, int b) {
    return (a < b) ? a : b;
}
//a file that runs until q 
void display (int ** mysheet, int R, int C, int x, int y){
    for (int i = x; i < min(R, x+10); i++){
        for (int j = y; j < min(C, y+10); j++){
            printf("%d ", mysheet[i][j]);
        }
        printf("\n");

    }
    fflush(stdout);
}


int main(int argc, char *argv[]){
    int R = atoi (argv[1]);
    int C = atoi (argv[2]);
    int ** mysheet = (int **)malloc(R * sizeof(int *));
    for (int i = 0; i < R; i++){
        mysheet[i] = (int *)calloc(C * sizeof(int), 0);
    }
    int x, y;
    x=0;
    y=0;
    display(mysheet, R, C, x, y);

    char s[100];
    scanf("%s", &s);
    while (s[0] != 'q'){
        printf("Hello, World!\n");
        scanf("%s", &s);
    }
    return 0;
}
