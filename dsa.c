#include<stdio.h>
void main(){    char array[]="Ashfaq \0 Kayani";    char *str="Ashfaq \0 Kayani";    printf("%s %c\n",array,array[2]);    printf("%s %c\n",str,str[2]);    printf("%d %d\n",sizeof(array),sizeof(str));}
