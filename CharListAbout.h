//
// Created by MuLei_SY on 2022/2/4.
//

#ifndef MYINTERPRETER_CHARLISTABOUT_H
#define MYINTERPRETER_CHARLISTABOUT_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct charList {
    char c;
    int coordXY[2];
    struct charList *next;
} *ptr_CL;

//build_source_code_list
ptr_CL bldCharLst() {
    ptr_CL head_charLst, tail_charLst;
    int flg_stop = 0;
    char c = (char) getchar();
    int coordXY[2] = {1, 1};
    ptr_CL fst_charLst = (ptr_CL) malloc(sizeof(struct charList));
    memset(fst_charLst, 0, sizeof(struct charList));
    fst_charLst->c = c;
    head_charLst = fst_charLst;
    tail_charLst = fst_charLst;
    fst_charLst->coordXY[0] = coordXY[0];
    coordXY[0]++;
    fst_charLst->coordXY[1] = coordXY[1];
    for (;; coordXY[0]++) {
        c = (char) getchar();
        if (c != '~') {
            ptr_CL tem_charLst = (ptr_CL) malloc(sizeof(struct charList));
            memset(tem_charLst, 0, sizeof(struct charList));
            tem_charLst->c = c;
            tem_charLst->coordXY[0] = coordXY[0];
            tem_charLst->coordXY[1] = coordXY[1];
            tail_charLst->next = tem_charLst;
            tail_charLst = tem_charLst;
        } else {
            flg_stop++;
        }

        if (c == '\n') {
            coordXY[1]++;
            coordXY[0] = 0;
        }
        if (c == '\t') {
            coordXY[0] += 4;
            coordXY[0]--;
        }

        if (flg_stop == 4)
            break;
    }
    return head_charLst;
}


#endif //MYINTERPRETER_CHARLISTABOUT_H


