/*************************************************************************
	> File Name: parser.c
	> Author: weapon
	> Mail: hongweichen8888@sina.com
	> Created Time: 2016年06月30日 星期四 23时44分37秒
 ************************************************************************/

//语法分析器
#include<stdio.h>
#include <stdlib.h>
#include "token.h"

#define LINE_BUF_SIZE (1024)

static Token st_look_ahead_token;
static int st_look_ahead_token_exists;

static void my_get_token(Token *token) {
    if (st_look_ahead_token_exists) {
        *token = st_look_ahead_token;
        st_look_ahead_token_exists = 0;
    }else {
        get_token(token);
    }
}

// 将记号回退
static void unget_token(Token *token) {
    st_look_ahead_token = *token;
    st_look_ahead_token_exists = 1;
}

double parse_expression(void);

static double parse_primary_expression() {
    Token token;
    double value;
    
    my_get_token(&token);
    if (token.kind == NUMBER_TOKEN) {
        return token.value;
    }else if (token.kind == LEFT_PAREN_TOKEN) {   //遇到括号的情况，解析括号内的表达式，返回double
        value = parse_expression();
        my_get_token(&token);
        if (token.kind != RIGHT_PAREN_TOKEN) {  //如果没有)匹配
            fprintf(stderr, "missing ')' error.\n");
            exit(1);
        }
        return value;
    }
    fprintf(stderr, "syntax error.\n");
    exit(1);
    return 0.0; //让编译通过的return
}

static double parse_term() {
    double v1;
    double v2;
    Token token;

    v1 = parse_primary_expression();
    for (;;) {
        my_get_token(&token);//如果始终保持预读，这行可以省略
        if (token.kind != MUL_OPERATOR_TOKEN && token.kind != DIV_OPERATOR_TOKEN) {
            unget_token(&token);
            break;
        }

        v2 = parse_primary_expression();
        if (token.kind == MUL_OPERATOR_TOKEN) {
            v1 *= v2;
        }else if (token.kind == DIV_OPERATOR_TOKEN) {
            v1 /= v2;
        }
    }
    return v1;
}

double parse_expression() {
    double v1;
    double v2;
    Token token;

    v1 = parse_term();
    for (;;) {
        my_get_token(&token);
        if (token.kind != ADD_OPERATOR_TOKEN && token.kind != SUB_OPERATOR_TOKEN) {
            unget_token(&token);
            break;
        }
        v2 = parse_term();
        if (token.kind == ADD_OPERATOR_TOKEN) {
            v1 += v2;
        }else if (token.kind == SUB_OPERATOR_TOKEN) {
            v1 -= v2;
        }else {
            unget_token(&token);
        }
    }
    return v1;
}


double parse_line(void) {
    double value;
    st_look_ahead_token_exists = 0;
    value = parse_expression();
    return value;
}

int main(int argc, char **argv) {
    char line[LINE_BUF_SIZE];
    double value;
    while (fgets(line, LINE_BUF_SIZE, stdin) != NULL) {
        set_line(line);
        value = parse_line();
        printf(">>%lf\n", value);
    }
    return 0;
}
