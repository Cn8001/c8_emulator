#include "common.h"
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

void fatal(const char *text){
    char error_buf[80];
    strncpy(error_buf,"[!!] Fatal Error: ",18);
    strncpy(error_buf,text,72);
    perror(error_buf);
    exit(-1);
}