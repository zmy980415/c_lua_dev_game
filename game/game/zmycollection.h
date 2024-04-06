#ifndef ZMYCOLLOCTION_H_
#define ZMYCOLLOCTION_H_

/*
	这个模块主要做一些集合
*/

/*******StringBuffer start*********/
typedef struct ZMY_StringBuffer {
	int len;
	int size;
	float capacity;
	char *str;
}ZMY_StringBuffer;

ZMY_StringBuffer * ZMY_StringBuffer_new();
void ZMY_StringBuffer_append(ZMY_StringBuffer *sb, const char* str);

/*******StringBuffer end***********/

#endif // !ZMYCOLLOCTION_H_