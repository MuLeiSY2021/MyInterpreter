//
// Created by MuLei_SY on 2022/1/29.
//

#ifndef MYINTERPRETER_SRCCODELISTABOUT_H
#define MYINTERPRETER_SRCCODELISTABOUT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "CharListAbout.h"
//----------------create source code----------------

//定义两种类型结构

//定义源码链表结构


typedef struct srcCodeList {
    char *c;
    double num;
    unsigned short flg_num;
    int coordXY[2];
    struct srcCodeList *next;
} *ptr_SCL;

ptr_SCL bld_srcCodeLst(ptr_CL head_charList) {
    const unsigned short num = 1, wrd = 2, chr = 3, alIn = 4;
    unsigned short flg_mod = 0, ptr_charPtr = 0, flg_numPtr = 0, flg_numInCount = 0;
    ptr_SCL head_srcCodeLst = 0, tail_srcCodeLst = 0, bef_srcCodeList = 0;
    char *srcCodeAry;
    for (; head_charList;) {
        if (!head_srcCodeLst) {
            int flg_alIn = 0;
            if ((head_charList->c == ' ' || head_charList->c == '\t' || head_charList->c == '\n')) {
                head_charList = head_charList->next;
                ptr_charPtr = 0;
                continue;
            }
            ptr_SCL fst_srcCodeList = (ptr_SCL) malloc(sizeof(struct srcCodeList));
            memset(fst_srcCodeList, 0, sizeof(struct srcCodeList));
            head_srcCodeLst = fst_srcCodeList;
            tail_srcCodeLst = fst_srcCodeList;
            if (head_charList->c == '\"') {
                flg_mod = chr;
                flg_alIn = 1;
            } else if ((head_charList->c >= 'A' && head_charList->c <= 'Z')
                       || (head_charList->c >= 'a' && head_charList->c <= 'z')
                       || (head_charList->c == '_')) {
                flg_mod = wrd;
            }else if ((head_charList->c == '-' && (head_charList->next->c >= '0' && head_charList->next->c <= '9'))
                       || (head_charList->c >= '0' && head_charList->c <= '9')
                       ||
                       (head_charList->c == '.' && (head_charList->next->c >= '0' && head_charList->next->c <= '9'))) {
                flg_mod = num;
                fst_srcCodeList->flg_num = 1;
                flg_numInCount = 1;
            } else {
                flg_mod = chr;
            }
            srcCodeAry = (char *) malloc(sizeof(char) * 2);
            memset(srcCodeAry, 0, sizeof(char) * 2);
            srcCodeAry[ptr_charPtr] = head_charList->c;
            fst_srcCodeList->c = srcCodeAry;
            ptr_charPtr++;
            fst_srcCodeList->coordXY[0] = head_charList->coordXY[0];
            fst_srcCodeList->coordXY[1] = head_charList->coordXY[1];
            head_charList = head_charList->next;
            bef_srcCodeList = fst_srcCodeList;
            if (flg_alIn) {
                flg_mod = alIn;
                ptr_charPtr = 0;
            }
        } else {
            if (flg_numInCount == 0) {
                flg_numPtr = 0;
            }
            int flg_num = 0, flg_alIn = 0;
            if ((head_charList->c == ' ' || head_charList->c == '\t' || head_charList->c == '\n')
                && !(flg_mod == alIn && (head_charList->c == ' '))) {
                head_charList = head_charList->next;
                ptr_charPtr = 0;
                flg_mod = chr;
                continue;
            } else if (flg_mod == num) {
                int flg_numFlg;
                if ((head_charList->c >= '0' && head_charList->c <= '9')
                    || (head_charList->c == '-' && (head_charList->next->c >= '0' && head_charList->next->c <= '9') &&
                        flg_numInCount == 0)
                    || (head_charList->c == '.' && flg_numPtr == 0 &&
                        (head_charList->next->c >= '0' && head_charList->next->c <= '9'))) {
                    flg_numFlg = 1;
                } else {
                    flg_numFlg = 0;
                }
                if (flg_numFlg == 0) {
                    flg_numInCount = 0;
                    if ((head_charList->c >= 'A' && head_charList->c <= 'Z')
                        || (head_charList->c >= 'a' && head_charList->c <= 'z')
                        || (head_charList->c == '_')) {
                        flg_mod = wrd;
                    } else if (head_charList->c == '\"') {
                        flg_alIn = 1;
                        flg_mod = chr;
                    } else {
                        flg_mod = chr;
                    }
                    ptr_charPtr = 0;
                } else if (head_charList->c == '.'
                           && (head_charList->next->c >= '0' && head_charList->next->c <= '9')) {
                    flg_numPtr = 1;
                    flg_num = 1;
                } else {
                    flg_num = 1;
                }
            } else if (flg_mod == wrd) {
                int flg_wrdFlg = 0;
                if ((head_charList->c >= '0' && head_charList->c <= '9')
                    || (head_charList->c >= 'A' && head_charList->c <= 'Z')
                    || (head_charList->c >= 'a' && head_charList->c <= 'z')
                    || (head_charList->c == '_')) {
                    flg_wrdFlg = 1;
                }
                if (flg_wrdFlg == 0) {
                    if (head_charList->c == '\"') {
                        flg_alIn = 1;
                        flg_mod = chr;
                    } else {

                        flg_mod = chr;
                    }
                    ptr_charPtr = 0;
                } else {
                    flg_numPtr = 0;
                }
            } else if (flg_mod == chr) {
                int flg_chrFlg;
                if ((head_charList->c >= 'A' && head_charList->c <= 'Z')
                    || (head_charList->c >= 'a' && head_charList->c <= 'z')
                    || (head_charList->c == '_')
                    || (head_charList->c >= '0' && head_charList->c <= '9')
                    || (head_charList->c == '-' && (head_charList->next->c >= '0' && head_charList->next->c <= '9') &&
                        flg_numInCount == 0)
                    || (head_charList->c == '.' && flg_numPtr == 0 &&
                        (head_charList->next->c >= '0' && head_charList->next->c <= '9'))) {
                    flg_chrFlg = 0;
                } else {
                    flg_chrFlg = 1;
                }

                if (flg_chrFlg == 0) {
                    if (head_charList->c == '\"') {
                        flg_alIn = 1;
                        flg_mod = chr;
                    } else if ((head_charList->c >= 'A' && head_charList->c <= 'Z') ||
                               (head_charList->c >= 'a' && head_charList->c <= 'z') || (head_charList->c == '_')) {
                        flg_mod = wrd;
                    } else {
                        flg_mod = num;
                        flg_numInCount = 1;
                        flg_num = 1;
                    }
                    ptr_charPtr = 0;
                } else {
                    flg_numPtr = 0;
                    flg_mod = chr;
                }
            } else if (flg_mod == alIn) {
                if (head_charList->c == '\"') {
                    if (head_charList->next->c == '\"') {
                        flg_mod = alIn;
                    } else if ((head_charList->c >= 'A' && head_charList->c <= 'Z') ||
                               (head_charList->c >= 'a' && head_charList->c <= 'z') || (head_charList->c == '_')) {
                        flg_mod = wrd;
                    } else if (head_charList->c >= '0' && head_charList->c <= '9' || (head_charList->c == '.' &&
                                                                                      (head_charList->next->c >= '0' &&
                                                                                       head_charList->next->c <=
                                                                                       '9'))) {
                        flg_mod = num;
                        flg_numInCount = 1;
                        flg_num = 1;
                    } else {
                        flg_mod = chr;
                    }
                    ptr_charPtr = 0;
                }
            }
            ptr_SCL tem_srcCodeList;
            if (ptr_charPtr == 0) {
                tem_srcCodeList = (ptr_SCL) malloc(sizeof(struct srcCodeList));
                memset(tem_srcCodeList, 0, sizeof(struct srcCodeList));
                tail_srcCodeLst->next = tem_srcCodeList;
                tail_srcCodeLst = tem_srcCodeList;
                srcCodeAry = (char *) malloc(sizeof(char) * 2);
                memset(srcCodeAry, 0, sizeof(char) * 2);
                srcCodeAry[ptr_charPtr] = head_charList->c;
                tem_srcCodeList->c = srcCodeAry;
                tem_srcCodeList->coordXY[0] = head_charList->coordXY[0];
                tem_srcCodeList->coordXY[1] = head_charList->coordXY[1];
                bef_srcCodeList = tem_srcCodeList;
            } else {
                srcCodeAry = (char *) realloc(srcCodeAry, sizeof(char) * (ptr_charPtr + 2));
                memset(srcCodeAry + sizeof(char) * (ptr_charPtr + 1), 0, sizeof(char));
                srcCodeAry[ptr_charPtr] = head_charList->c;
                bef_srcCodeList->c = srcCodeAry;
                bef_srcCodeList->coordXY[0] = head_charList->coordXY[0];
                bef_srcCodeList->coordXY[1] = head_charList->coordXY[1];
            }
            if (flg_num) {
                bef_srcCodeList->flg_num = 1;
            }
            if (flg_alIn) {
                flg_mod = alIn;
                ptr_charPtr = 0;
            }
            head_charList = head_charList->next;
            ptr_charPtr++;
        }
    }
    return head_srcCodeLst;
}

ptr_SCL numInPut(ptr_SCL head_srcCodeLst) {
    for (ptr_SCL tem_srcCodeLst = head_srcCodeLst; tem_srcCodeLst; tem_srcCodeLst = tem_srcCodeLst->next) {
        if (!tem_srcCodeLst->flg_num) {
            continue;
        }
        int flg_numPlace = 0;
        double num = 0;
        for (unsigned long long i = strlen(tem_srcCodeLst->c); i >= 0; i--) {
            if (tem_srcCodeLst->c[i] == '.') {
                num *= pow(10, -flg_numPlace);
                flg_numPlace = 0;
                continue;
            }
            if (tem_srcCodeLst->c[i] == '-') {
                num = -num;
                continue;
            }
            num += (tem_srcCodeLst->c[i] - 48) * pow(10, flg_numPlace);
            flg_numPlace++;
        }
        tem_srcCodeLst->num = num;
    }
    return head_srcCodeLst;
}

void test(ptr_SCL head_srcCodeLst) {
    int i = 1;
    for (ptr_SCL ptr_srcCodeList = head_srcCodeLst; ptr_srcCodeList; ptr_srcCodeList = ptr_srcCodeList->next, i++) {
        if (ptr_srcCodeList->flg_num == 0) {
            printf(" Str:%-7s ", ptr_srcCodeList->c);
        } else {
            printf(" Num:%-+4.4lf ", ptr_srcCodeList->num);
        }
        printf(" Coord(%3d,%3d) ", ptr_srcCodeList->coordXY[0], ptr_srcCodeList->coordXY[1]);
        if (i % 3 == 0) {
            i = 0;
            printf("\n");
        }
    }
}

// int main()
// {
//     ptr_CL head_charList=bldCharLst();
//     ptr_SCL head_srcCodeLst=bld_srcCodeLst(head_charList);
//     head_srcCodeLst=numInPut(head_srcCodeLst);
//     test(head_srcCodeLst);

//     return 0;
// }

//--------------------------------------------------------------------//

#endif //MYINTERPRETER_SRCCODELISTABOUT_H

