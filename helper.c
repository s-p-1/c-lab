#include <stdlib.h>
#include <stdio.h>
#include "helper.h"

int stringcomp(const char s1[20], const char s2[20], char myc){
        int flag =1;
        for (int i =0; i<20; ++i){
                if (s1[i]==myc){
                        if (s2[i]!=myc) flag=0;
                        break;
                }
                if (s1[i]!=s2[i]){
                        flag=0;
                        break;
                }
        }
        return flag;
}




int mycomp(char s[20]){
        if (stringcomp("w", s, '\0')==1) return 1;
        if (stringcomp("a", s, '\0')==1) return 2;
        if (stringcomp("s", s, '\0')==1) return 3;
        if (stringcomp("d", s, '\0')==1) return 4;
        if (stringcomp("q", s, '\0')==1) return 5;
        if (stringcomp("disable_output", s, '\0')==1) return 6;
        if (stringcomp("enable_output", s, '\0')==1) return 7;
        if (stringcomp("scroll_to ", s, ' ')==1){
                printf("call the print function to the required cell here\n");
                return 8;
        }
        printf("give correct input\n");
        return -1;
}
