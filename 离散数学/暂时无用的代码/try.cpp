#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 100
#define K33 1
#define K5 2

typedef struct {
    int u;
    int v;
} Edge;

// �ж��Ƿ����K3,3��ͼ
int hasK33Subgraph(int V, int E, Edge edges[]) {
    int degrees[MAX_VERTICES] = {0};
    int adjMatrix[MAX_VERTICES][MAX_VERTICES] = {0};
    int i ,j,k; 

    for (i= 0; i < E; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        degrees[u]++;
        degrees[v]++;

        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }

    for (i = 1; i <= V; i++) {
        if (degrees[i] != 3) {
            continue;
        }

        for (j = i + 1; j <= V; j++) {
            if (degrees[j] != 3) {
                continue;
            }

            for ( k = j + 1; k <= V; k++) {
                if (degrees[k] != 3) {
                    continue;
                }

                if ((adjMatrix[i][j] && adjMatrix[j][k] && adjMatrix[k][i]) ||
                    (!adjMatrix[i][j] && !adjMatrix[j][k] && !adjMatrix[k][i])) {
                    return K33; // ����K3,3��ͼ
                }
            }
        }
    }

    return 0; // ������K3,3��ͼ
}

// �ж��Ƿ����K5��ͼ
int hasK5Subgraph(int V, int E, Edge edges[]) {
    int degrees[MAX_VERTICES] = {0};
    int i ,j,k,l;
    int adjMatrix[MAX_VERTICES][MAX_VERTICES] = {0};

    for ( i = 0; i < E; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        degrees[u]++;
        degrees[v]++;

        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }

    for ( i = 1; i <= V; i++) {
        if (degrees[i] >= 5) {
            for ( j = i + 1; j <= V; j++) {
                if (degrees[j] >= 5) {
                    for ( k = j + 1; k <= V; k++) {
                        if (degrees[k] >= 5) {
                            for ( l = k + 1; l <= V; l++) {
                                if (degrees[l] >= 5) {
                                    if ((adjMatrix[i][j] && adjMatrix[i][k] && adjMatrix[i][l] && adjMatrix[j][k] &&
                                         adjMatrix[j][l] && adjMatrix[k][l]) ||
                                        (!adjMatrix[i][j] && !adjMatrix[i][k] && !adjMatrix[i][l] && !adjMatrix[j][k] &&
                                         !adjMatrix[j][l] && !adjMatrix[k][l])) {
                                        return K5; // ����K5��ͼ
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }
    }

    return 0; // ������K5��ͼ
}

// �ж��Ƿ�Ϊƽ��ͼ
int isPlanarGraph(int V, int E, Edge edges[]) {
    int k33 = hasK33Subgraph(V, E, edges);
    if (k33) {
        return 0; // ����K3,3��ͼ������ƽ��ͼ
    }

    int k5 = hasK5Subgraph(V, E, edges);
    if (k5) {
        return 0; // ����K5��ͼ������ƽ��ͼ
    }

    return 1; // ��������з�˹��������ƽ��ͼ
}

int main() {
    int V, E;
    int i;
    scanf("%d %d", &V, &E);

    Edge edges[MAX_VERTICES];
    for (i = 0; i < E; i++) {
        scanf("%d %d", &edges[i].u, &edges[i].v);
    }

    int result = isPlanarGraph(V, E, edges);
    if (result) {
        printf("YES\n");
    } else {
        printf("NO\n");
    }

    return 0;
}

