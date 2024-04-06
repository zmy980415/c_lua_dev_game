#include "zmycollection.h"
#include <stdlib.h>
#include <string.h>

#define STRING_BUFFER_DEFALUT_SIZE 16
#define STRING_BUFFER_DEFALUT_CAPACITY  0.75



ZMY_StringBuffer* ZMY_StringBuffer_new()
{
    ZMY_StringBuffer* sb = (ZMY_StringBuffer*)malloc(sizeof(ZMY_StringBuffer));
    if (sb == NULL)
    {
        return NULL;
    }
    sb->len = 0;
    sb->str = NULL;
    sb->capacity = STRING_BUFFER_DEFALUT_CAPACITY;
    sb->size = STRING_BUFFER_DEFALUT_SIZE;
    char *str = (char*)calloc(16,sizeof(char));
    sb->str = str;
    return sb;
}

void ZMY_StringBuffer_append(ZMY_StringBuffer* sb,const char* str)
{
    if (sb == NULL) {
        exit(-1);
    }
    if (str == NULL) {
        return;
    }
    int str_len = strlen(str);
    //判断是否超出容量 * 负载因子
    while (1) {
        printf("222----222\n");
        if (sb->len + str_len < sb->size * sb->capacity) {
            strcat(sb->str, str);
            return;
        }
        else {
            sb->size = (sb->size  + str_len) * 2;
            char* newStr = (char*)calloc(sb->size,sizeof(char));
            if (newStr == NULL) {
                exit(-1);
            }
            memcpy_s(newStr, sb->size, sb->str, str_len + 1);
            free(sb->str);
            sb->str = newStr;
            strcat(sb->str, str);
            sb->len = sb->len + str_len;
            return;
        }
        
    }
}

