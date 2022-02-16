
#include <stdlib.h>
#include <string.h>
#include "uthash.h"
#include "SrcCodeListAbout.h"

//--------------------------------------------------


//----------------word tree create----------------

//定义两种数据结构

//词法树结构 有关键词长度，id，字符，四个分支
typedef struct encTree {
    char c;
    int id;
    struct encTree *next1;
    struct encTree *next2;
    struct encTree *next3;
    struct encTree *next4;
} *ptr_ET;

//词法链表结构
typedef struct encList {
    int coordXY[2];
    int id;
    struct encList *next;
} *ptr_EL;

//词法链表包结构
struct encList *head;
struct encList *tail;
//构建词法树

//关键词列表
// "box","pointBox","bigBox","#pb","#bb","#b","start","/","<",">",
// "putNum","putWord","\\lf","\\cr","until"," ","=","+"," " "," ' ","putf","puts",""loop
// "-","*"

//!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!! " 没有入到语法树中！！！！！！！！！！！！！！！！！！！！！！！！
char ptrWord[] = {" \"=\",\"+\",\"-\",\"*\",\"/\",\"\\lf\",\"\\cr\",\"#b\",\"#w\",\"<\",\">\",\"box\",\"pointBox\", "
                  " ,\"when\",\"loop\",\"putB\",\"putW\",\"#pb\",\"#bb\",\"bigBox\",\"word\",\"pointBox\","
                  "\"[\",\"]\",\"{\",\"}\",\"\'\",,\"puts\",\"putf\",\"putPb\",\"vac\",\"core\",\",\""};
int ptrCodeNum;

//构建词法树
ptr_ET BldEncTree() {
//    unsigned int word_size = char_array_size(word);
    //c_root
    ptr_ET ROOT = (ptr_ET) malloc(sizeof(struct encTree));
    memset(ROOT, 0, sizeof(struct encTree));
    ptr_ET tree_head = ROOT;
    int id = 1;

    //提前把\"置入词法树
    tree_head->next1 = (ptr_ET) malloc(sizeof(struct encTree));
    memset(tree_head->next1, 0, sizeof(struct encTree));
    tree_head = tree_head->next1;
    tree_head->c = '\"';
    tree_head->id = id;
    id++;
    tree_head = ROOT;
    ptrCodeNum++;
    //
    int cuePtrFlg = 0;
    for (int i = 0; ptrWord[i] != 0; i++) {
        if (ptrWord[i] == '\"') {
            if (cuePtrFlg == 0) {
                cuePtrFlg = 1;
            } else {
                cuePtrFlg = 0;
                tree_head->id = id;
                id++;
                tree_head = ROOT;
                ptrCodeNum++;
            }
            continue;
        }
        if (cuePtrFlg == 0) {
            continue;
        }

        int flag_4cr = 0;
        if (tree_head->next1 == 0) {
            tree_head->next1 = (ptr_ET) malloc(sizeof(struct encTree));
            memset(tree_head->next1, 0, sizeof(struct encTree));
            tree_head = tree_head->next1;
        } else if (tree_head->next1->c == ptrWord[i]) {
            tree_head = tree_head->next1;
            continue;
        } else if (tree_head->next2 == 0) {
            tree_head->next2 = (ptr_ET) malloc(sizeof(struct encTree));
            memset(tree_head->next2, 0, sizeof(struct encTree));
            tree_head = tree_head->next2;
        } else if (tree_head->next2->c == ptrWord[i]) {
            tree_head = tree_head->next2;
            continue;
        } else if (tree_head->next3 == 0) {
            tree_head->next3 = (ptr_ET) malloc(sizeof(struct encTree));
            memset(tree_head->next3, 0, sizeof(struct encTree));
            tree_head = tree_head->next3;
        } else if (tree_head->next3->c == ptrWord[i]) {
            tree_head = tree_head->next3;
            continue;
        } else if (tree_head->next4 == 0) {
            tree_head->next4 = (ptr_ET) malloc(sizeof(struct encTree));
            memset(tree_head->next4, 0, sizeof(struct encTree));
            tree_head = tree_head->next4;
            flag_4cr = 1;
        } else {
            tree_head = tree_head->next4;
            i--;
            continue;
        }
        if (flag_4cr) {
            i--;
            continue;
        }
        tree_head->c = ptrWord[i];
    }
    return ROOT;
}

struct hash_numList {
    double num;
    int ID;
    UT_hash_handle hh;
};

struct hash_numList *nums = NULL;

struct hash_nonKeyWords {
    char *word;
    int ID;
    UT_hash_handle hh;
};

struct hash_nonKeyWords *nonKeyWords = NULL;

int add_num(int numID, double num) {
    struct hash_numList *s;

    HASH_FIND(hh, nums, &num, sizeof(num), s);
    if (NULL == s) {
        s = malloc(sizeof(struct hash_numList));
        memset(s, 0, sizeof(struct hash_numList));
        s->ID = numID;
        s->num = num;
        HASH_ADD(hh, nums, num, sizeof(num), s);
        return 0;
    }
    return s->ID;
}

int add_word(int nonKeyWordID, char *nonKeyWord) {
    struct hash_nonKeyWords *s;

    HASH_FIND_STR(nonKeyWords, nonKeyWord, s);
    if (NULL == s) {
        s = (struct hash_nonKeyWords *) malloc(sizeof(struct hash_nonKeyWords));
        memset(s, 0, sizeof(struct hash_nonKeyWords));
        s->ID = nonKeyWordID;
        s->word = nonKeyWord;
        HASH_ADD_KEYPTR(hh, nonKeyWords, s->word, strlen(s->word), s);
        return 0;
    }
    return s->ID;
}

int SearchEncTree(ptr_ET encTreeHead, ptr_SCL srcList) {
    const int UNKEYWORD = -1, NUM = -2;
    for (int i = 0; encTreeHead->next1 != 0;) {
        if (encTreeHead->next1->c == srcList->c[i]) {
            encTreeHead = encTreeHead->next1;
            i++;
        } else if (encTreeHead->next2 != 0 && encTreeHead->next2->c == srcList->c[i]) {
            encTreeHead = encTreeHead->next2;
            i++;
        } else if (encTreeHead->next3 != 0 && encTreeHead->next3->c == srcList->c[i]) {
            encTreeHead = encTreeHead->next3;
            i++;
        } else if (encTreeHead->next2 == 0 || encTreeHead->next3 == 0 || encTreeHead->next4 == 0) {
            break;
        } else {
            encTreeHead = encTreeHead->next4;
        }
    }

    if (encTreeHead->c != 0) {
        return encTreeHead->id;
    } else if (srcList->flg_num != 1) {
        return UNKEYWORD;
    } else {
        return NUM;
    }

}

ptr_EL BldEncList(ptr_EL encListTail, int inListID, ptr_SCL srcList) {
    ptr_EL temList = (ptr_EL) malloc(sizeof(struct encList));
    memset(temList, 0, (sizeof(struct encList)));
    temList->id = inListID;
    temList->coordXY[0] = srcList->coordXY[0];
    temList->coordXY[1] = srcList->coordXY[1];
    encListTail->next = temList;
    return temList;
}

ptr_EL ChiEncListID(ptr_ET encTreeHead, ptr_SCL srcListHead) {
    const int UNKEYWORD = -1, NUM = -2;
    int numID = ptrCodeNum + 1;
    int nonKeyWordID = -1;
    ptr_EL encListHead = 0, encListTail = 0;

    for (ptr_SCL tmp_srcListHead = srcListHead; tmp_srcListHead != 0; tmp_srcListHead = tmp_srcListHead->next) {
        int inListID;
        int searchResult = SearchEncTree(encTreeHead, tmp_srcListHead);
        if (searchResult == UNKEYWORD) {
            inListID = add_word(nonKeyWordID, tmp_srcListHead->c);
            if (!inListID) {
                inListID = nonKeyWordID;
                nonKeyWordID--;
            }
        } else if (searchResult == NUM) {
            inListID = add_num(numID, tmp_srcListHead->num);
            if (!inListID) {
                inListID = numID;
                numID++;
            }
        } else {
            inListID = searchResult;
        }

        if (encListHead == 0) {
            ptr_EL tmp_encList = (ptr_EL) malloc(sizeof(struct encList));
            memset(tmp_encList, 0, sizeof(struct encList));
            tmp_encList->coordXY[0] = tmp_srcListHead->coordXY[0];
            tmp_encList->coordXY[1] = tmp_srcListHead->coordXY[1];
            tmp_encList->id = inListID;
            encListHead = encListTail = tmp_encList;
        } else {
            encListTail = BldEncList(encListTail, inListID, tmp_srcListHead);
        }
    }

    return encListHead;
}


//-------------------------------------------------

//------------TEST------------
void PrtNums() {
    struct hash_numList *s;
    printf("\nAll Num Ram List");
    int i = 0;
    for (s = nums; s != NULL; s = s->hh.next) {
        if (i % 5 == 0) {
            printf("\n");
        }
        printf("  Number:%3.3lf---ID:%2d  ", s->num, s->ID);
        i++;
    }
}

void PrtNonKeyWords() {
    struct hash_nonKeyWords *s;
    printf("\nAll Un Key Words Ram List");
    int i = 0;
    for (s = nonKeyWords; s != NULL; s = s->hh.next) {
        if (i % 4 == 0) {
            printf("\n");
        }
        printf("  Words:%s---ID:%-2d  ", s->word, s->ID);

        i++;
    }
}


void EncListTest(ptr_EL encListHead) {
    PrtNonKeyWords();
    PrtNums();
    int i = 0;
    printf("\nEnCode List:");
    for (ptr_EL tmp_encList = encListHead; tmp_encList != 0; tmp_encList = tmp_encList->next) {
        if (i % /*4*/20 == 0) {
            printf("\n");
        }
//        printf("  ID:%-2d---Coord:[%2d,%2d]  ",tmp_encList->id,tmp_encList->coordXY[0],tmp_encList->coordXY[1]);
        printf(" %-2d ", tmp_encList->id);
        i++;
    }
}
//----------------------------

int main() {
    ptr_ET ROOT;

    ROOT = BldEncTree();

    ptr_CL head_charList = bldCharLst();

    ptr_SCL head_srcCodeLst = bld_srcCodeLst(head_charList);

    head_srcCodeLst = numInPut(head_srcCodeLst);

    test(head_srcCodeLst);

    ptr_EL encListHead = ChiEncListID(ROOT, head_srcCodeLst);

    EncListTest(encListHead);

    return 0;
}