/*************************************************************************
	> File Name: ORG_dev.h
	> Author: 
	> Mail: 
	> Created Time: 2016年07月07日 星期四 15时08分12秒
 ************************************************************************/

#ifndef _ORG_DEV_H
#define _ORG_DEV_H

//定义布尔类型 c语言没有布尔类型，需要自己定义
typedef enum {
    ORG_FALSE = 0,
    ORG_TRUE  = 1
} ORG_Boolean;

//字符串类
typedef struct ORG_String_tag ORG_String;

//指针信息
typedef struct {
    char *name;
} ORG_NativePointerInfo;

//变量类型
typedef enum {
    ORG_BOOLEAN_VALUE = 1, //布尔类型
    ORG_INT_VALUE,          //整型
    ORG_DOUBLE_VALUE,       //浮点型
    ORG_STRING_VALUE,       //字符串型
    ORG_NATIVE_POINTER_VALUE, //复杂数据类型 任意类型，包括基本数据类型
    ORG_NULL_VALUE,         //空值，未设置类型
} ORG_ValueType;

//任意类型定义
typedef struct {
    ORG_NativePointerInfo *info;
    void *pointer;
} ORG_NativePointer;






#endif
