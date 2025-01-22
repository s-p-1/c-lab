#include <stdio.h>
#include <stdlib.h>

//a file that runs until q and initializes display
int min(int a, int b) {
    return (a < b) ? a : b;
}
char * return_string(int n){
    if (n<26){
        char * s = (char *)malloc(2 * sizeof(char));
        s[0] = 'A' + n;
        s[1] = '\0';
        return s;
    }
    else if (n<26+26*26){
        char * s = (char *)malloc(3 * sizeof(char));
        s[0] = 'A' + n/26 - 1;
        s[1] = 'A' + n%26;
        s[2] = '\0';
        return s;
    }else{
        char * s = (char *)malloc(4 * sizeof(char));
        int q = n/26-1;
        s[0] = 'A' + q/26 - 1;
        s[1] = 'A' + q%26;
        s[2] = 'A' + n%26;
        s[3] = '\0';
        return s;
    }

}

void display (int ** mysheet, int R, int C, int x, int y){
    printf("%15s", return_string(y));
    for (int j = y+1; j < min(C, y+10); j++){
        printf("%12s", return_string(j)); 
    }
    printf("\n");
    for (int i = x; i < min(R, x+10); i++){
        printf("%3d", i);
        for (int j = y; j < min(C, y+10); j++){
            printf("%12d", mysheet[i][j]); 
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
