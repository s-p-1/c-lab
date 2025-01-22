#include <stdio.h>
//a file that runs until q 
main(){
    char c;
    scanf("%c", &c);
    while (c != 'q'){
        printf("Hello, World!\n");
        scanf("%c", &c);
    }
    return 0;
}