#include "common.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void fatal(char *text){
    char error_buf[80];
    strncpy(error_buf,"[!!] Fatal Error ",18);
    strncat(error_buf,text,72);
    perror(error_buf);
    exit(-1);
}