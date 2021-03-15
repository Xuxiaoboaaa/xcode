/*
最小斯坦纳树板子题
*/
#include<bits/stdc++.h>
using namespace std;
#define pii pair<int, int>
const int INF = 0x3f3f3f3f;
int n, m, x, y, k;
int a[105];
struct node { 
	int to, next, w;
}e[1050];
int head[150], cnt;
void add(int u, int v, int w) { 
	e[++cnt] = node {v, head[u], w};
	head[u] = cnt;
	e[++cnt] = node {u, head[v], w};
	head[v] = cnt;
} 
int dp[105][1025];
priority_queue<pii, vector<pii>, greater<pii> > q;
bool vis[105];
void dij(int s) { 
	memset(vis, 0, sizeof vis);
	while(!q.empty()) { 
		pii nw = q.top(); q.pop();
		int u = nw.second, w = nw.first;
//		cout << u << " "<< w << " " << s << endl;
		if(vis[u]) continue;
		vis[u] = 1;
		for(int i = head[u]; i; i = e[i].next) {
			int v = e[i].to;
			if(dp[v][s] > w + e[i].w) { 
				dp[v][s] =  w + e[i].w;
				if(!vis[v]) q.push(make_pair(dp[v][s], v));
			} 
		} 
	} 
} 
int main() { 
	scanf("%d %d %d %d %d", &n, &m, &k, &x, &y);
	memset(dp, 0x3f, sizeof dp);
	a[x] = k + 1, a[y] = k + 2;
	k += 2;
	int tot = k;
	for(int i = 1, u; i <= n; ++i) { 
		dp[i][0] = 0;
		scanf("%d", &u);
		if(i == x || i == y) continue;
		if(u) a[i] = u;
		else a[i] = ++tot;
	}	
	n = tot;
	
	for(int i = 1, u, v, w; i <= m; ++i) { 
		scanf("%d %d %d", &u, &v, &w);
		if(a[u] == a[v]) continue;
		add(a[u], a[v], w);
	} 
	
	for(int i = 1; i <= k; ++i) { 
		dp[i][1<<(i-1)] = 0;
	} 
	for(int s = 1; s < (1<<k); ++s) { 
		for(int i = 1; i <= n; ++i) { 
			for(int t = s&(s-1); t; t = s&(t-1)) { 
				dp[i][s] = min(dp[i][s], dp[i][t] + dp[i][t^s]);
			} 
			if(dp[i][s] != INF) q.push(make_pair(dp[i][s], i)); 
		}	
		dij(s);
	}
	int ans = INF;
	for(int i = 1; i <= n; ++i) { 
		ans = min(ans, dp[i][(1<<k)-1]);
	} 
	cout << ans << endl;
} 