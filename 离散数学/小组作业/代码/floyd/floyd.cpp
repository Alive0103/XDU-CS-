#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <set>
#include <map>
#include <queue>
#include <vector>
#define rep(a, b, c) for (int a = b; a <= c; a++)
#define IOS cin.tie(0)->sync_with_stdio(false)
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
const int MAXN = 1e3 + 5;
const int INF = 0x3f3f3f3f;
int read()
{
    int X = 0, f = 1;
    char c = getchar();
    while (!isdigit(c) && c != '-')
        c = getchar();
    if (c == '-')
        c = getchar(), f = -1;
    while (isdigit(c))
        X = X * 10 + (c ^ 48), c = getchar();
    return X * f;
}
int f[MAXN][MAXN]; // f[i][j]����ڵ�i���ڵ�j�����·
int main()
{
    int n, m; //nΪͼ�е��������mΪͼ�бߵ�����
    cin >> n >> m;
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            f[i][j] = 1e9; //��ʼÿ���ڵ��֮�䶼�ǲ��ɴ��Ϊ���ֵ
        }
    }
    for (int i = 1; i <= n; i++)
        f[i][i] = 0; // �Լ����Լ����·Ϊ0
    for (int i = 0; i < m; i++)
    {
        int x, y, w;
        cin >> x >> y >> w;    // �ֱ�����㣬�յ�ͱ�Ȩ
        f[x][y] = f[y][x] = w; // ���ͼΪ����ͼ
    }
    for (int k = 1; k <= n; k++) // ö��ת�ƽڵ�
        for (int i = 1; i <= n; i++)
            for (int j = 1; j <= n; j++)
            {
                f[i][j] = min(f[i][j], f[i][k] + f[k][j]);
                // ö��k��Ϊi>j��ת�ƽڵ����
            }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= n; j++)
        {
            printf("%d ", f[i][j]);
            // ���i��j�����·
        }
        puts("");
    }
    return 0;
}
