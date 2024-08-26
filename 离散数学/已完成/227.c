#include <stdio.h>
#include <stdbool.h>

#define MAX_NODES 5

// Ѱ�ҳ���Ϊ3�Ļ�·
void find(int matrix[MAX_NODES][MAX_NODES], int n) {
    int i, j, k;
    char nodes[MAX_NODES] = {'a', 'b', 'c', 'd', 'e'};
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                // �ж��Ƿ���ڳ���Ϊ3�Ļ�·
                if (matrix[i][j] && matrix[j][k] && matrix[k][i]) {
                    printf("%c %c %c %c\n", nodes[i], nodes[j], nodes[k], nodes[i]);
                }
            }
        }
    }
}

// �ж��Ƿ���ڳ���Ϊ3�Ļ�·
bool has(int adj_matrix[MAX_NODES][MAX_NODES], int n) {
    int i, j, k;
    
    for (i = 0; i < n; i++) {
        for (j = 0; j < n; j++) {
            for (k = 0; k < n; k++) {
                // �ж��Ƿ���ڳ���Ϊ3�Ļ�·
                if (adj_matrix[i][j] && adj_matrix[j][k] && adj_matrix[k][i]) {
                    return true;
                }
            }
        }
    }
    
    return false;
}

int main() {
    int N, i, j, matrix[MAX_NODES][MAX_NODES];
    
    // ��������
    scanf("%d", &N);
    
    // �����ڽӾ���
    for (i = 0; i < N; i++) {
        for (j = 0; j < N; j++) {
            scanf("%d", &matrix[i][j]);
        }
    }
    
    // �жϲ��������Ϊ3�Ļ�·
    if (has(matrix, N)) {
        find(matrix, N);
    } else {
        printf("Does not exist");
    }
    
    return 0;
}

