#include<bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 0x3f3f3f3f3f3f3f3f;
const int N = 1e5+6, M = 1e6+6;
struct edge{
    ll v, w;
};
vector<edge> G[N];
struct Edge{
    ll u, v, w;
} e[M];
ll dis[N], cnt[N], vis[N];
int DEQUE[N];
int L, R;
void Swap(int &a, int &b){a ^= b ^= a ^= b;}
bool spfa(int n, int s){
    L = 1; R = 0;
    dis[s] = 0, vis[s] = 1;
    DEQUE[++R] = s;
    int u;
    ll v, w;
    while(L <= R){
        u = DEQUE[L];
        L++; vis[u] = 0;
        for(auto ed : G[u]){
            v = ed.v, w = ed.w;
            if(dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if(cnt[v] >= n) return 0;
                if(!vis[v]){
                    DEQUE[++R] = v;
                    vis[v] = 1;
                }
            }
        }
    }
    return 1;
}
bool swap_spfa(int n, int s){
    L = 1; R = 0;
    dis[s] = 0, vis[s] = 1;
    DEQUE[++R] = s;
    int u;
    ll v, w;
    while(L <= R){
        u = DEQUE[L];
        L++; vis[u] = 0;
        for(auto ed : G[u]){
            v = ed.v, w = ed.w;
            if(dis[v] > dis[u] + w){
                dis[v] = dis[u] + w;
                cnt[v] = cnt[u] + 1;
                if(cnt[v] >= n) return 0;
                if(!vis[v]){
                    DEQUE[++R] = v;
                    if(DEQUE[L] > DEQUE[R]){
                        // Swap(DEQUE[L], DEQUE[R]);
                        DEQUE[L] ^= DEQUE[R] ^= DEQUE[L] ^= DEQUE[R];
                    }
                    vis[v] = 1;
                }
            }
        }
    }
    return 1;
}
bool bellman_ford(int s, int n, int m){
	dis[s] = 0;
	bool flag = false;
	for(int i = 1; i <= n; i++){
		flag = false;
		for(int j = 1; j <= m; j++){
			ll u = e[j].u, v = e[j].v, w = e[j].w;
			if(dis[u] + w < dis[v] && dis[u] != INF){
				dis[v] = dis[u] + w;
				flag = true;
			}
		}
		if(!flag) break;
	}
	if(flag) return 0;
	return 1;
}
int n, m, s;
ll T, u, v, w;
ll time2[10];
vector<ll> vals;
ll ref(ll a, ll b, ll c, ll d){
    vals = {a, b, c, d};
    sort(vals.begin(), vals.end());
    double median = (vals[1] + vals[2]) / 2.0;
    vector<double> abs_dev;
    for(ll x : vals){
        abs_dev.push_back(abs(static_cast<double>(x) - median));
    }
    sort(abs_dev.begin(), abs_dev.end());
    double mad = (abs_dev[1] + abs_dev[2]) / 2.0;
    if(mad == 0.0){
        return (a+b+c+d) / 4.0;
    }
    double threshold = 2.0 * mad;
    vector<ll> filtered_vals;
    double sum = 0.0;
    int count = 0;
    for(ll x : vals) {
        if(abs(static_cast<double>(x) - median) <= threshold){
            filtered_vals.push_back(x);
            sum += x;
            count++;
        }
    }
    if(count == 0){
        return median;
    }
    return ll(sum/count);
}
int main(){
    freopen("graph.in", "r", stdin);
    freopen("graph_resultprime5.out", "w", stdout);
    // freopen("graph_pos.in", "r", stdin);
    // freopen("graph_pos_resultprime5.out", "w", stdout);
    ll limn = INF, limm = INF;
    for(int I = 1; I <= 118; I++){
        ll time = 0, time_swap = 0, time_bell = 0, Time;
        cin >> T;
        bool flag = 0;
        for(int tt = 1; tt <= T; tt++){
            scanf("%d %d %d", &n, &m, &s);
            for(auto& vec : G) {
                vec.clear();
            }
            for(int i = 1; i <= m; i++){
                scanf("%lld %lld %lld", &e[i].u, &e[i].v, &e[i].w);
                G[e[i].u].push_back({e[i].v, e[i].w});
            }
            memset(time2, 0, sizeof(time2));
            for(int ttt = 1; ttt <= 4; ttt++){
                auto start = std::chrono::steady_clock::now();
                for(int k = 1; k <= 10; k++){
                    memset(dis, 0x3f, sizeof(dis));
                    memset(cnt, 0, sizeof(cnt));
                    memset(vis, 0, sizeof(vis));
                    spfa(n, s);
                }
                auto stop = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
                time2[ttt] = duration.count()/10;
            }
            Time = ref(time2[1], time2[2], time2[3], time2[4]);
            time += Time;
            printf("%lld ", Time);
            memset(time2, 0, sizeof(time2));
            for(int ttt = 1; ttt <= 4; ttt++){
                auto start = std::chrono::steady_clock::now();
                for(int k = 1; k <= 10; k++){
                    memset(dis, 0x3f, sizeof(dis));
                    memset(cnt, 0, sizeof(cnt));
                    memset(vis, 0, sizeof(vis));
                    swap_spfa(n, s);
                }
                auto stop = std::chrono::steady_clock::now();
                auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
                time2[ttt] = duration.count()/10;
            }
            Time = ref(time2[1], time2[2], time2[3], time2[4]);
            time_swap += Time;
            printf("%lld ", Time);
            if(flag || 1LL*n*m > limn*limm){
                printf("%lld ", 100000000LL);
                flag = 1;
            }
            else{
                memset(time2, 0, sizeof(time2));
                for(int ttt = 1; ttt <= 4; ttt++){
                    auto start = std::chrono::steady_clock::now();
                    for(int k = 1; k <= 10; k++){
                        memset(dis, 0x3f, sizeof(dis));
                        memset(cnt, 0, sizeof(cnt));
                        memset(vis, 0, sizeof(vis));
                        bellman_ford(s, n, m);
                    }
                    auto stop = std::chrono::steady_clock::now();
                    auto duration = std::chrono::duration_cast<std::chrono::nanoseconds>(stop - start);
                    time2[ttt] = duration.count()/10;
                    if(time2[ttt] > 100000000LL){
                        flag = 1;
                        limn = n, limm = m;
                        break;
                    }
                }
                Time = ref(time2[1], time2[2], time2[3], time2[4]);
                time_bell += Time;
                printf("%lld ", Time);
            }
        }
        printf("%d %d %lld %lld %lld\n", n, m, time/T, time_swap/T, flag?INF:(time_bell/T));
    }
}