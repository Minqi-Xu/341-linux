#include <iostream>
#include <climits>
#include <vector>
#include <cmath>

using namespace std;

struct edge{
    long long endpoint, weight;
};

int main() {
    int n, m, h;
    cin >> n >> m >> h;
    vector<edge> adjacentlist[n+1];
    for(int i = 0; i <= n; i++) {
        edge temp = {i, 0};
        adjacentlist[i].push_back(temp);
    }
    long long u, v, w;
    for(int i = 0; i < m; i++) {
        cin >> u >> v >> w;
        edge temp = {v, w};
        adjacentlist[u].push_back(temp);
    }

    int height = log(h)/log(2);

    long long d0[n+1][n+1];
    long long dp[height + 1][n+1][n+1];
    long long ans[n+1][n+1];

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            if(h >= 1)
                dp[0][i][j] = LONG_LONG_MAX;
            if(i == j) {
                d0[i][j] = 0;
            }
            else {
                d0[i][j] = LONG_LONG_MAX;
             }
        }
    }

    if(h >= 1) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j < adjacentlist[i].size(); j++) {
                dp[0][i][adjacentlist[i][j].endpoint] = min(dp[0][i][adjacentlist[i][j].endpoint], adjacentlist[i][j].weight);
            }
        }
    }

    if(h >= 2) {
        for(int hh = 1; hh <= height; hh++) {
            for(int i = 1; i <= n; i++) {
                for(int j = 1; j <= n; j++) {
                    dp[hh][i][j] = LONG_LONG_MAX;
                    for(int nn = 1; nn <= n; nn++) {
                        if(dp[hh-1][nn][j] == LONG_LONG_MAX || dp[hh-1][i][nn] == LONG_LONG_MAX)
                            dp[hh][i][j] = dp[hh][i][j];
                        else
                            dp[hh][i][j] = min(dp[hh][i][j], dp[hh-1][i][nn] + dp[hh-1][nn][j]);
                    }
                }
            }
        }

    }

    if(h == 0) {
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j < n; j++) {
                if(d0[i][j] == LONG_LONG_MAX)
                    cout << "x  ";
                else
                    cout << d0[i][j] << "  ";
            }
            if(d0[i][n] == LONG_LONG_MAX)
                cout << "x" << endl;
            else
                cout << d0[i][n] << endl;
        }

        return 0;
    }
    for(int i = 1; i <= n; i++) {
        for(int j = 1; j <= n; j++) {
            ans[i][j] = dp[height][i][j];
        }
    }
    int restt = h;
    int ex = log(restt)/log(2);
    restt = h - pow(2, ex);
    long long temp[n+1][n+1];
    while(restt > 0) {
        int depth = log(restt)/log(2);
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                temp[i][j] = LONG_LONG_MAX;
                for(int nn = 1; nn <= n; nn++) {
                    if(ans[i][nn] == LONG_LONG_MAX || dp[depth][nn][j] == LONG_LONG_MAX)
                        continue;
                    temp[i][j] = min(temp[i][j], ans[i][nn] + dp[depth][nn][j]);
                }
            }
        }
        for(int i = 1; i <= n; i++) {
            for(int j = 1; j <= n; j++) {
                ans[i][j] = temp[i][j];
            }
        }
        restt = restt - pow(2,depth);
    }

    for(int i = 1; i <= n; i++) {
        for(int j = 1; j < n; j++) {
            if(ans[i][j] == LONG_LONG_MAX)
                cout << "x  ";
            else
                cout << ans[i][j] << "  ";
        }
        if(ans[i][n] == LONG_LONG_MAX)
            cout << "x" << endl;
        else
            cout << ans[i][n] << endl;
    }

    return 0;
}
