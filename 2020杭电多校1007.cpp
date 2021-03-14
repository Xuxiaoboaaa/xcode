#include <iostream>
#include <cstdio>
#include <fstream>
#include <algorithm>
#include <cmath>
#include <deque>
#include <vector>
#include <queue>
#include <string>
#include <cstring>
#include <map>
#include <stack>
#include <set>
using namespace std;
typedef long long LL;
const LL INF = 0x3f3f3f3f3f3f3f3f;
const double Pi = acos(-1);
namespace io {
	template <typename T> inline void read(T &x) {
		x = 0;
		T f = 1;
		char s = getchar();
		for(; !isdigit(s); s = getchar()) if(s == '-') f = -1;
		for(;  isdigit(s); s = getchar()) x = (x << 3) + (x << 1) + (s ^ 48);
		x *= f;
	}
	template <typename T> inline void write(T x) {
		if(x < 0) putchar('-'), x = -x;
		if(x > 9) write(x/10);
		putchar(x%10+'0');
	}
};
#define fio ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
#define _for(n,m,i) for (register int i = (n); i <  (m); ++i)
#define _rep(n,m,i) for (register int i = (n); i <= (m); ++i)
#define _srep(n,m,i)for (register int i = (n); i >= (m); i--)
#define _sfor(n,m,i)for (register int i = (n); i >  (m); i--)
#define ef(u, i) for(int i = head[u]; i; i = e[i].next)
#define lson rt << 1, l, mid
#define rson rt << 1 | 1, mid + 1, r
#define lowbit(x) x & (-x)
#define pii pair<int,int>
#define fi first
#define se second
const int N = 1e5+5;
struct node {
  int to, next;
  LL a, b;
}e[N];
int head[N], cnt;
void add(int u, int v, LL a, LL b) {
  e[++cnt] = node {v, head[u], a, b};
  head[u] = cnt;
  e[++cnt] = node {u, head[v], a, b};
  head[v] = cnt;
}
LL f[N][22];
LL tm[22];
int n, k, sz[N];
void dfs(int u, int fa, LL limit) {
  sz[u] = 0;
  for(int i = 0; i <= k; ++i) f[u][i] = 0;
  for(int i = head[u]; i; i = e[i].next) {
    int v = e[i].to;
    if(v == fa) continue;
    dfs(v, u, limit);
    int now = min(sz[u] + sz[v] + 1, k);
    for(int j = 0; j <= now; ++j) tm[j] = limit+1;
    for(int j = 0; j <= sz[u]; ++j) {
      for(int K = 0; K <= sz[v]&& j+K <= k; ++K) {
        if(f[u][j] + f[v][K] + e[i].a <= limit) {
          tm[j+K+1] = min(tm[j+K+1], max(f[u][j], f[v][K] + e[i].a));
        } 
        if(f[u][j] + f[v][K] + e[i].b <= limit) {
          tm[j+K] = min(tm[j+K], max(f[u][j], f[v][K] + e[i].b));
        } 
      }
    }
    for(int j = 0;  j <= now; ++j) f[u][j] = tm[j];
    sz[u] = now;
  }
}
void solve() {
  scanf("%d %d", &n, &k);
  LL l = 1, r = 0;
  for(int i = 1, u, v, a, b; i < n; ++i) {
    scanf("%d %d %d %d", &u, &v, &a, &b);
    add(u, v, a, b);
    r += max(a, b);
  }

  LL ans = r;
  while(l <= r) {
    LL mid = l + r >> 1;
    dfs(1, 0, mid);
    if(f[1][k] <= mid) r = mid-1, ans = mid;
    else l = mid + 1;
  }
  printf("%lld\n", ans);
  for(; cnt; cnt--) head[cnt] = 0;

}
int main() {
  int t; scanf("%d", &t);
  while(t--) {
    solve();
  }
}