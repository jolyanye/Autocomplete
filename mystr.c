// a = "sssss" 

#include <stdio.h> 
#include <string.h> 
#include <stdlib.h>
#include "mystr.h"

void mystr_create(mystr *p_s, const char *str, int len)
{
    // mystr s -> local variable 
    // use pointer to modify contents of string that is passed 

    // could say p_s->str = str; 
    // BUT, 
    // if str is a const char, won't know that we're not allowed to modify it 
    // (could crash program)
    // also, don't know if need to free p_s->str later

    // p_s->str and str are now different pointers, but 
    // with p_s->str = str, they are equal (so strings are aliases)
    p_s->len = len; // same as (*p_s).len = len 
    p_s->str = (char *)malloc(len * sizeof(char) + 1); 

    if (p_s->str == NULL) {
        printf("Malloc failed\n"); 
        exit(1); 
    }

    strcpy(p_s->str, str);
}


void mystr_cat(mystr *p_dest, const mystr *p_src) {
    p_dest->str = (char *)realloc(p_dest->str, (p_dest->len + p_src->len + 1) 
                    * sizeof(char));

    if (p_dest->str == NULL) {
        printf("Realloc failed\n"); 
        exit(1); 
    }

    p_dest->len += p_src->len;
    strcat(p_dest->str, p_src->str);

} 

void mystr_destory(mystr *p_s)
{
    free(p_s->str);
    p_s->str = NULL;
    p_s->len = 0;
}


int main() 
{
    mystr s; 
    mystr_create(&s, "EngSci", 6);
    // now s.str points to a string "EngSci", s.len is 6
    mystr praxis; 

    mystr_create(&praxis, "Praxis!!!", 9);

    mystr_cat(&s, &praxis);
    printf("%s\n", s.str);
    
    mystr_destory(&s);
    mystr_destory(&praxis);
}
