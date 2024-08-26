#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// ����������볤��
#define MAX_INPUT_LENGTH 1000

// ���庯������
typedef struct {
    int* domain;  // ���嶨��������
    int domainSize;  // �������С
    int* codomain;  // ֵ������
    int codomainSize;  // ֵ���С
    int** relation;  // ��ϵ����
    int relationSize;  // ��ϵ��С
} Function;

// ��������
Function* createFunction(int domainSize, int codomainSize);
void destroyFunction(Function* function);
void parseSet(char* input, int** set, int* setSize);
void parseRelation(char* input, Function* function);
int isFunction(Function* function);
int isInjection(Function* function);
int isSurjection(Function* function);

int main() {
    char input[MAX_INPUT_LENGTH];

    // ���뼯��A
    fgets(input, MAX_INPUT_LENGTH, stdin);
    int* setA;
    int setSizeA;
    parseSet(input, &setA, &setSizeA);

    // ���뼯��B
    fgets(input, MAX_INPUT_LENGTH, stdin);
    int* setB;
    int setSizeB;
    parseSet(input, &setB, &setSizeB);

    // �����ϵR
    fgets(input, MAX_INPUT_LENGTH, stdin);
    Function* function = createFunction(setSizeA, setSizeB);
    parseRelation(input, function);

    // �жϺ�������
    if (isFunction(function)) {
    	int i;
        if (isInjection(function) && isSurjection(function)) {
            printf("{ ");
            for (i = 0; i < setSizeA; i++) {
                printf("%d ", setA[i]);
            }
            printf("} -> { ");
            for ( i = 0; i < setSizeB; i++) {
                printf("%d ", setB[i]);
            }
            printf("}:s\n");
        } else if (isInjection(function)) {
            printf("{ ");
            for ( i = 0; i < setSizeA; i++) {
                printf("%d ", setA[i]);
            }
            printf("} -> { ");
            for ( i = 0; i < setSizeB; i++) {
                printf("%d ", setB[i]);
            }
            printf("}:d\n");
        } else if (isSurjection(function)) {
            printf("{ ");
            for ( i = 0; i < setSizeA; i++) {
                printf("%d ", setA[i]);
            }
            printf("} -> { ");
            for (i = 0; i < setSizeB; i++) {
                printf("%d ", setB[i]);
            }
            printf("}:m\n");
        } else {
            printf("{ ");
            for (i = 0; i < setSizeA; i++) {
                printf("%d ", setA[i]);
            }
            printf("} -> { ");
            for ( i = 0; i < setSizeB; i++) {
                printf("%d ", setB[i]);
            }
            printf("}:f\n");
        }
    } else {
        printf("{ ");
        int i;
        for (i = 0; i < setSizeA; i++) {
            printf("%d ", setA[i]);
        }
        printf("} -> { ");
        for (i = 0; i < setSizeB; i++) {
            printf("%d ", setB[i]);
        }
        printf("}:nf\n");
    }

    // �ͷ��ڴ�
    destroyFunction(function);
    free(setA);
    free(setB);

    return 0;
}

// ��������
Function* createFunction(int domainSize, int codomainSize) {
    Function* function = (Function*)malloc(sizeof(Function));
    function->domain = (int*)malloc(sizeof(int) * domainSize);
    function->domainSize = domainSize;
    function->codomain = (int*)malloc(sizeof(int) * codomainSize);
    function->codomainSize = codomainSize;
    function->relation = NULL;
    function->relationSize = 0;
    return function;
}

// ���ٺ���
void destroyFunction(Function* function) {
	int i;
    free(function->domain);
    free(function->codomain);
    for ( i = 0; i < function->relationSize; i++) {
        free(function->relation[i]);
    }
    free(function->relation);
    free(function);
}

// ��������
void parseSet(char* input, int** set, int* setSize) {
    char* token = strtok(input, "{}, \n");
    int count = 0;
    *setSize = 0;
    while (token != NULL) {
        (*setSize)++;
        token = strtok(NULL, "{}, \n");
    }

    *set = (int*)malloc(sizeof(int) * (*setSize));
    token = strtok(input, "{}, \n");
    while (token != NULL) {
        (*set)[count] = atoi(token);
        count++;
        token = strtok(NULL, "{}, \n");
    }
}

// ������ϵ
void parseRelation(char* input, Function* function) {
    char* token = strtok(input, "<>, \n");
    int count = 0;
    function->relationSize = 0;
    while (token != NULL) {
        (function->relationSize)++;
        token = strtok(NULL, "<>, \n");
    }

    function->relation = (int**)malloc(sizeof(int*) * function->relationSize);
    token = strtok(input, "<>, \n");
    while (token != NULL) {
        function->relation[count] = (int*)malloc(sizeof(int) * 2);
        function->relation[count][0] = atoi(token);
        token = strtok(NULL, "<>, \n");
        function->relation[count][1] = atoi(token);
        count++;
        token = strtok(NULL, "<>, \n");
    }
}

// �ж��Ƿ�Ϊ����
int isFunction(Function* function) {
	int i,j;
    for (i = 0; i < function->domainSize; i++) {
        int count = 0;
        for (j = 0; j < function->relationSize; j++) {
            if (function->relation[j][0] == function->domain[i]) {
                count++;
            }
        }
        if (count != 1) {
            return 0;
        }
    }
    return 1;
}

// �ж��Ƿ�Ϊ����
int isInjection(Function* function) {
	int i,j;
    for (i = 0; i < function->domainSize; i++) {
        int count = 0;
        for (j = 0; j < function->relationSize; j++) {
            if (function->relation[j][0] == function->domain[i]) {
                count++;
            }
        }
        if (count > 1) {
            return 0;
        }
    }
    return 1;
}

// �ж��Ƿ�Ϊ����
int isSurjection(Function* function) {
	int i,j;
    for (i = 0; i < function->codomainSize; i++) {
        int count = 0;
        for (j = 0; j < function->relationSize; j++) {
            if (function->relation[j][1] == function->codomain[i]) {
                count++;
            }
        }
        if (count == 0) {
            return 0;
        }
    }
    return 1;
}

