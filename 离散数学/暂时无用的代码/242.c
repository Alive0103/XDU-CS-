#include <stdio.h>
#include <stdlib.h>

#define MAX_VERTICES 11
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
    int i, j, k;

    for (i = 0; i < E; i++) {
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

            int commonNeighbor = 0;
            for (k = 1; k <= V; k++) {
                if (k != i && k != j && adjMatrix[i][k] && adjMatrix[j][k]) {
                    commonNeighbor = 1;
                    break;
                }
            }

            if (commonNeighbor) {
                return K33; // ����K3,3��ͼ
            }
        }
    }

    return 0; // ������K3,3��ͼ
}

// �ж��Ƿ����K5��ͼ
int hasK5Subgraph(int V, int E, Edge edges[]) {
    int degrees[MAX_VERTICES] = {0};
    int adjMatrix[MAX_VERTICES][MAX_VERTICES] = {0};
    int i, j, k, l,n,m;

    for (i = 0; i < E; i++) {
        int u = edges[i].u;
        int v = edges[i].v;

        degrees[u]++;
        degrees[v]++;

        adjMatrix[u][v] = 1;
        adjMatrix[v][u] = 1;
    }

    for (i = 1; i <= V; i++) {
        if (degrees[i] >= 5) {
            for (j = i + 1; j <= V; j++) {
                if (degrees[j] >= 5) {
                    for (k = j + 1; k <= V; k++) {
                        if (degrees[k] >= 5) {
                            for (l = k + 1; l <= V; l++) {
                                if (degrees[l] >= 5) {
                                    int complete = 1;
                                    for (m = i; m <= l; m++) {
                                        for (n = m + 1; n <= l; n++) {
                                            if (!adjMatrix[m][n]) {
                                                complete = 0;
                                                break;
                                            }
                                        }
                                        if (!complete) {
                                            break;
                                        }
                                    }

                                    if (complete) {
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

