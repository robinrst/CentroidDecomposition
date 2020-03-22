#include        "algorithm"
#include        "iostream"
#include        "numeric"
#include        "iomanip"
#include        "cstring"
#include        "math.h"
#include        "bitset"
#include        "string"
#include        "vector"
#include        "ctime"
#include        "queue"
#include        "stack"
#include        "map"
#include        "set"

#include        "ext/pb_ds/assoc_container.hpp" // Common file
#include        "ext/pb_ds/tree_policy.hpp" // Including tree_order_statistics_node_update
#include        "ext/pb_ds/detail/standard_policies.hpp"

using namespace std;
using namespace __gnu_pbds;


#define          f first
#define          lgn 25
#define          endl '\n'
#define          sc second
#define          N (int)2e5+5
#define          pb push_back
#define          mod 1000000007
#define          ld long double
#define          vi vector<int>
#define          eb emplace_back
#define          vpii vector<pii>
#define          mii map<int,int>
// #define          int long long 
#define          ll long long 
#define          pii pair<int,int>
#define          pq priority_queue
#define          BLOCK (int)sqrt(N)
#define          test(x) while(x--)
#define          all(x) begin(x),end(x)
#define          allr(x) rbegin(x),rend(x)
#define          fo(i,a,n) for(int i=a;i<n;i++)
#define          rfo(i,n,a) for(int i=n;i>=a;i--)
#define          FAST ios::sync_with_stdio(0); cin.tie(0); cout.tie(0);
#define          time() cerr << "Time : " << (double)clock() / (double)CLOCKS_PER_SEC << "s\n"
#define          PI acos(-1.0)
#define 		 bug(...)       __f (#__VA_ARGS__, __VA_ARGS__)

typedef tree< int, null_type, less<int>, rb_tree_tag, tree_order_statistics_node_update > 
OS ;

template <typename Arg1>
void __f (const char* name, Arg1&& arg1) { cout << name << " : " << arg1 << endl; }
template <typename Arg1, typename... Args>
void __f (const char* names, Arg1&& arg1, Args&&... args)
{
     const char* comma = strchr (names + 1, ',');
     cout.write (names, comma - names) << " : " << arg1 << " | "; __f (comma + 1, args...);
}

inline void INP()
{
	#ifndef ONLINE_JUDGE
	    freopen("input.txt","r",stdin);   
	    freopen("output.txt","w",stdout);
	#endif 
}

const int inf = 0x3f3f3f3f;
const ll INF = 0x3f3f3f3f3f3f3f3f;

int n,m,k,q,nodes;
string s;
set<int> adj[N];
int in[N] , out[N] , sz[N] , Dep[N] , up[N][lgn] , ans[N] , par[N] , col[N];
multiset<int> st[N];

void dfsSize(int i = 1, int p = 1)
{
	static int clk = 0;
	up[i][0] = p;
	in[i] = ++clk;

	fo(j,1,lgn)
	{
		up[i][j] = up[ up[i][j-1] ][j-1];
	}

	for( auto j : adj[i] )
	{
		if( j != p ) 
		{
			Dep[j] = Dep[i] + 1;
			dfsSize(j ,i);
		}
	}
	out[i] = clk;
}

int getRoot(int i , int p )
{
	for( auto j : adj[i] )
	{
		if( j  != p and sz[j] > nodes/2 )
		{
			return getRoot(j ,i);
		}
	}
	return i;
}

void Sz(int i, int p)
{
	sz[i] = 1;
	nodes++;
	for( int j : adj[i] )
	{
		if( j != p )
		{
			Sz(j,i);
			sz[i] += sz[j];
		}
	}
}

void centroidTree(int i = 1, int p = 0)
{
	nodes = 0;
	Sz(i,i);
	int centroid = getRoot(i,i);
	par[centroid] = p;

	for( auto j : adj[centroid] )
	{
		adj[j].erase(centroid);
		centroidTree(j , centroid);
	}

	adj[centroid].clear();
}

bool anc(int i ,int j)
{
	return in[i] <= in[j] and out[i] >= out[j];
}

int LCA( int i , int j )
{
	if( anc(i , j) ) return i;
	if( anc(j , i) ) return j;

	rfo(k,lgn-1,0)
	{
		if( !anc( up[i][k] , j ) ) i = up[i][k];
	}

	return up[i][0];
}

int dist(int i ,int j )
{
	return Dep[i] + Dep[j] - 2*Dep[LCA(i,j)];
}

void update(int i)
{
	int p = i;
	col[i] ^= 1;
	int color = col[i];

	while(p)
	{
		if( color ) // white
		{
			st[p].insert( dist(i,p) );
		}
		else
		{
			auto xx = st[p].find( dist(i,p) );
			if( xx != end( st[p]) ) st[p].erase( xx ); 
		}
		p = par[p];
	}
}

int query(int i)
{
	int p = i;
	int sum = inf;

	while( p )
	{
		if( st[p].size() )
		{
			sum = min( sum , *st[p].begin() + dist(i ,p) );
		}
		p = par[p];
	}

	return sum;
}

void go()
{
	cin >> n;
	fo(i,0,n-1) 
	{
		int u ,v ;
		cin >> u >> v;
		adj[u].insert(v);
		adj[v].insert(u);
	}
	cin >> m;
	dfsSize();
	centroidTree();

	while(m--)
	{
		int ch ,v;
		cin >> ch >> v;

		if( !ch )
		{
			update(v);
		}
		else
		{
			int res = query(v);
			if( res == inf ) res = -1;
			cout << res << endl;
		}
	}
}

int32_t main()
{
	INP(); 
	FAST;     
	int t=1; 
	// cin>>t;
	test(t) go();
}

 