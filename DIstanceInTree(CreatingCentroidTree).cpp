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
#define          int long long 
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
const int INF = 0x3f3f3f3f3f3f3f3f;

int n,m,k,q , nodes, childs ,ans;
string s;
set<pii> adj[N]; 
int cnt[N] , sz[N] , temp[N] , rmv[N] , vis[N];


void Sz( int i , int p )
{
	sz[i] = 1;
	nodes += 1;

	for( auto j : adj[i] ) 
	{
		if( j.f != p ) Sz(j.f ,i ) , sz[i] += sz[j.f];
	}
}

int getCentroid(int i, int p )
{
	for( auto  j : adj[i] )
	{
		if( j.f != p and sz[j.f] > nodes/2 ) 
		{
			return getCentroid(j.f , i);
		}
	}
	return i;
}

void getAllDis(int i , int p , int sum )
{
	temp[++childs] = sum;

	for( auto j : adj[i] )
	{
		if( j.f != p )
		{
			getAllDis(j.f , i , sum + j.sc );
		}
	}
}

void makeAns(int i , int p )
{
	int dn = 0;
	for( auto j : adj[i] )
	{
		if( j.f != p )
		{
			temp[0] = 1;
			childs = 0;
			getAllDis(j.f ,i , j.sc);

			rfo(k,childs,1)
			{
				if( m >= temp[k] ) 
				{
					ans += cnt[ m - temp[k] ];
				}
			}

			rfo(k,childs,1)
			{
				rmv[++dn] = temp[k];
				cnt[temp[k]]++;
			}
		}
	}
	rfo(j,dn,1) cnt[rmv[j]]--;
}

void centroidTree(int i = 1 , int p = 0)
{
	nodes = 0;
	childs = 0;
	cnt[0] = 1;

	Sz(i,i);
	int centroid = getCentroid(i,i);

	makeAns(centroid , 0);

	vis[i] = 1;

	for( auto j : adj[centroid] )
	{
		if( j.f != p )
		{
			auto xx = adj[j.f].lower_bound({ centroid , -1});
			if( xx != end( adj[j.f] ) )
			adj[j.f].erase(xx);
			centroidTree(j.f , centroid );
		}
	}	
	adj[centroid].clear();
}

void go()
{
	cin >> n >> m;

	fo(i,0,n-1)
	{
		int  u , v , w;
		w = 1;
		cin >> u >> v;
		adj[u].insert({ v , w });
		adj[v].insert({ u , w });
	}	

	centroidTree();

	cout << ans << endl;
}

int32_t main()
{
	INP(); 
	FAST;     
	int t=1; 
	// cin>>t;
	test(t) go();
}

 