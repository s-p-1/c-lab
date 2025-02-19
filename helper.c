#include "helper.h"

bool stringcomp(const char* s1, const char* s2, char myc){
        bool flag =true;
        int i=0;
        while (i<20){
                if (*s1==myc){
                        if (*s2!=myc) flag=false;
                        break;
                }
                if (*s1!=*s2){
                        flag=false;
                        break;
                }
                ++s1;
                ++s2;
                ++i;
        }
        return flag;
}


int mycomp(char s[20]){
        if (stringcomp("w", s, '\0')) return 1;
        if (stringcomp("a", s, '\0')) return 2;
        if (stringcomp("s", s, '\0')) return 3;
        if (stringcomp("d", s, '\0')) return 4;
        if (stringcomp("q", s, '\0')) return 5;
        if (stringcomp("disable_output", s, '\0')) return 6;
        if (stringcomp("enable_output", s, '\0')) return 7;
        if (stringcomp("scroll_to ", s, ' ')){
                return (1000+cell_handler(s+10));
        }
        printf("give correct input\n");
        return -1;
}

int get_line(){
        char string[20];
        char c = getchar();
        int q = c-'a';
        if (q>=26){
                printf("this is wrong input\n");
                return -1;
        }else if (q>=0){
                int i =0;
                while (c!='\n'){
                        string[i]=c;
                        c=getchar();
                        ++i;
                        if (i==19) {
                                while (getchar()!='\n')
                                break;
                        }
                }
                string[i]='\0';
                return mycomp(string);
        }else{
                char arr[30];
                arr[0]=c;
                int i =1;
                for (i; i<30; ++i){
                        c=getchar();
                        if (c=='\n') break;
                        arr[i]=c;
                }
                arr[i]='\0';
                char myc= parser(arr);
                // printf("%c\n", myc);
                if (myc<0) return myc;
                else return 999;
        }
}

// int main(){
//         int g =get_line();
//         while(g!=5){
//                 printf("%d\n", g);
//                 g=get_line();
//         }
//         return 0;
// }
