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
// #define          N (int)2e6+5
#define          pb push_back
#define          mod 1000000007
#define          ld long double
#define          vi vector<int>
#define          eb emplace_back
#define          vpii vector<pii>
#define          mii map<int,int>
// #define          int long long 
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
const int N = 2000005;
// const int INF = 0x3f3f3f3f3f3f3f3f;

int n,m,k,q,cn,root,SZ,ans;
string s;
vpii adj[N];
int mx[N] , vis[N] , rmv[N] , sz[N] ,
 judge[N] , dist[N] , tmp[N];

void getRoot(int i = 1, int p = 0)
{
	sz[i] = 1;
	mx[i] = 0;

	for( auto j : adj[i] )
	{
		if( j.f != p and !vis[j.f] )
		{
			getRoot(j.f , i);
			sz[i] += sz[j.f];
			mx[i] = max( mx[i] , sz[j.f] ); // update maximum son size
		}
	}

	mx[i] = max( mx[i] , SZ - sz[i] ); 
	if( mx[i] < mx[root] ) root = i; // check whether this node can be centroid or not
}

void getDis(int i , int p)
{
	tmp[++cn] = dist[i]; // insert path sum in tmp array and cn will give number of paths

	for( auto j: adj[i] )
	{
		if( j.f != p and !vis[j.f] )
		{
			dist[j.f] = dist[i] + j.sc; // update the path sum 
			getDis(j.f , i);
		}
	}
}

void solve(int i )
{
	int dn = 0; // for to count the number of path from root to childs
	for( auto j : adj[i] )
	{
		if( !vis[j.f] )
		{
			cn = 0;
			dist[j.f] = j.sc; // from root to this child path sum
			getDis(j.f,i); // get All path sum in this branch of root

			rfo(k,cn,1) 
			{
				if( m >= tmp[k] ) // check whether the path sum is less than required sum ot not
				{
					ans += ( judge[ m - tmp[k] ] ); // update the answer 
				}
			}
			rfo(k,cn,1)
			{
				rmv[++dn] = tmp[k]; // add to remove array to remove those in the end so 
									//that those won't contribute in other forest of trees
				judge[tmp[k]]++; // for current root add the contribution of this child path 
								//so that other a path from lca of (u,v) can be made
			}
		}
	}	

	fo(i,1,dn+1) judge[rmv[i]]--; // remove all the path sum 

}

void Divide(int i = 1)
{
	getRoot(i,0); // Get the root 

	cn = 0;       // finding number of childs in subtree of root
	judge[0] = 1; // from root to itself distance is zero
	vis[root] = 1;// mark the root -> corresponds to deletion of node

	solve(root); // Solve for that root

	for( auto j : adj[root] )
	{
		if( !vis[j.f] )
		{
			SZ = sz[j.f]; // update the size of new tree
			mx[ root = 0 ] = n; // maximum size son of this tree
			Divide(j.f); 
		}
	}
}

void go()
{
	cin >> n >> m;
	fo(i,0,n-1)
	{
		int u , v , w;
		cin >> u >> v;
		adj[u].pb({ v, 1});
		adj[v].pb({ u , 1});
	}

	SZ = n; 
	root = 0;
	mx[root] = n;

	Divide();

	cout << ans << endl;
}

int main()
{
	INP(); 
	FAST;     
	int t=1; 
	// cin>>t;
	test(t) go();
}

 