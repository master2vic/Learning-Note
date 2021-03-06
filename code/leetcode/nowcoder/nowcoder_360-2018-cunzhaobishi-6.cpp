
/**
牛客网
2018 360春招笔试6

给你一个图，0节点连接这一个联通块a，1节点连接着一个联通块b,ab仅由01这条边相连。现在我们定义奇异路径为恰好经过0-1这条边一次的路径。在这个图中有无数条奇异路径，问第k长的奇异路径长度是多少？

https://www.nowcoder.com/test/question/done?tid=31796355&qid=535402#summary
 * 
*/
#include <cstdio>
#include <cstring>
#include <vector>
using std::vector;
  
typedef long long ll;
  /*图，邻接表，路径*/
const int MAX = 102;
vector<int> G[MAX];//节点数[5,100]
ll vis[MAX][MAX<<8];
int n, m;
ll k;//k<2^40
  
ll get(int idx, int len) {
    if (vis[idx][len] > 0) {
        return vis[idx][len];
    }
    if (len == 0) {
//      printf("vis[%d][%d]=1\n", idx, len);
        return vis[idx][len] = 1;
    }
    if (len == 1) {
//      printf("vis[%d][%d]=%d\n", idx, len, G[idx].size());
        return vis[idx][len] = (ll)G[idx].size();
    }
  
    ll s = 0LL;
    for (auto it: G[idx]) {
        ll val = get(it, len-1);
        s += val;
//      printf("vis[%d][%d]+=<%d,%d,%lld>=%lld\n", idx, len, it, len-1, val, s);
    }
//  printf("vis[%d][%d]=%lld\n", idx, len, s);
    return vis[idx][len] = s;
}
  
int main() {
    while (~scanf("%d%d%lld", &n, &m, &k)) {
        for (int i = 0; i < n; i++) {
            G[i].clear();
        }
        int u, v;
        for (int i = 0; i < m; i++) {
            scanf("%d%d", &u, &v);
            if ((u == 0 && v == 1) || (u == 1 && v == 0)) {
                continue;
            }
            G[u].push_back(v);
            G[v].push_back(u);
        }
        memset(vis, 0, sizeof(vis));
          
        if (k == 1) {
            puts("1");
            continue;
        }
  
        int ans = 0;
        while (k > 0) {
            ans++;
            for (int i = 0; i <= ans-1; i++) {
                k -= get(0, i) * get(1, ans - 1 - i);
//              printf("ans=%d,k=[%lld],i=<%d,%lld>,ans-i=<%d,%lld>\n", ans, k, i, get(0, i), ans-i, get(1, ans-i));
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}
