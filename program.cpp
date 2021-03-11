#include <bits/stdc++.h>
typedef long long ll;
typedef long double ld;
#define TC    \
	int t;    \
	cin >> t; \
	while (t--)
#define inarr(A, n, k)              \
	for (int i = k; i < n + k; ++i) \
	cin >> A[i]
#define all(v) (v).begin(), (v).end()
#define allr(v) (v).rbegin(), (v).rend()
#define pb push_back
#define mp make_pair
#define F first
#define S second
#define vb vector<bool>
#define vi vector<int>
#define vl vector<ll>
#define pii pair<int, int>
#define vpi vector<pii>
#define MOD ll(1e9 + 7)
#define unordered_set(T) unordered_set<T, custom_hash>
#define unordered_map(T1, T2) unordered_map<T1, T2, custom_hash>

using namespace std;

struct custom_hash
{
	static uint64_t splitmix64(uint64_t x)
	{
		// http://xorshift.di.unimi.it/splitmix64.c
		x += 0x9e3779b97f4a7c15;
		x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9;
		x = (x ^ (x >> 27)) * 0x94d049bb133111eb;
		return x ^ (x >> 31);
	}

	size_t operator()(uint64_t x) const
	{
		static const uint64_t FIXED_RANDOM = chrono::steady_clock::now().time_since_epoch().count();
		return splitmix64(x + FIXED_RANDOM);
	}
};

template <typename T>
void print(T val)
{
	cout << val;
}
template <typename Head, typename... Tail>
void print(Head H, Tail... T)
{
	cout << H << ' ';
	print(T...);
}

template <typename C, typename T = std::decay_t<decltype(*begin(std::declval<C>()))>, typename std::enable_if<!std::is_same<C, std::string>::value>::type * = nullptr>
std::ostream &operator<<(std::ostream &os, const C &container)
{
	bool first = true;
	std::stringstream ss;
	ss << '[';
	for (const auto &x : container)
	{
		if (!first)
		{
			ss << ", ";
		}
		first = false;
		ss << x;
	}
	ss << ']';
	return os << ss.str();
}
template <class T1, class T2>
std::ostream &operator<<(std::ostream &os, const std::pair<T1, T2> &p)
{
	os << '{' << p.first << ", " << p.second << '}';
	return os;
}
vector<string> vec_splitter(string S)
{
	S += ',';
	vector<string> res;
	while (!S.empty())
	{
		res.push_back(S.substr(0, S.find(',')));
		S = S.substr(S.find(',') + 1);
	}
	return res;
}
void debug_out(vector<string> __attribute__((unused)) args, __attribute__((unused)) int idx, __attribute__((unused)) int LINE_NUM)
{
	cerr << "\n";
}
template <typename Head, typename... Tail>
void debug_out(vector<string> args, int idx, int LINE_NUM, Head H, Tail... T)
{
	if (idx > 0)
		cerr << ", ";
	else
		cerr << "Line(" << LINE_NUM << ") ";
	stringstream ss;
	ss << H;
	cerr << args[idx] << " = " << ss.str();
	debug_out(args, idx + 1, LINE_NUM, T...);
}
#ifdef DEBUG
#define debug(...) debug_out(vec_splitter(#__VA_ARGS__), 0, __LINE__, __VA_ARGS__)
#else
#define debug(...) 42
#endif

int d, i, s, v, f;
vector<set<pair<pii, int>>> adj;
unordered_map<string, int> streets;
unordered_map<int, string> streetsInv;
unordered_map<int, int> counts;
vector<vector<int>> paths;

int main()
{
	mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	cout.tie(NULL);

	cin >> d >> i >> s >> v >> f;
	adj.assign(i, set<pair<pii, int>>());
	int st = 0;
	for (int j = 0, b, e, l; j < s; ++j)
	{
		cin >> b >> e;
		string street;
		cin >> street;
		streets[street] = st;
		streetsInv[st] = street;
		cin >> l;
		adj[e].insert({{b, l}, st++});
	}

	paths.assign(v, vector<int>());
	for (int j = 0, p; j < v; ++j)
	{
		cin >> p;
		while (p--)
		{
			string street;
			cin >> street;
			paths[j].pb(streets[street]);
			++counts[streets[street]];
		}
	}

	vector<pair<int, vector<int>>> ans;
	for (int j = 0; j < i; ++j)
	{
		set<pair<pii, int>> st = adj[j];
		vector<int> temp;
		for (auto &v : st)
			if (counts[v.S])
				temp.pb(v.S);
		shuffle(all(temp), rng);
		if (temp.size())
			ans.pb({j, temp});
	}

	cout << ans.size() << '\n';
	for (auto &vec : ans)
	{
		cout << vec.F << '\n'
			 << vec.S.size() << '\n';
		vector<int> temp = vec.S;
		shuffle(all(temp), rng);
		for (auto &v : temp)
			cout << streetsInv[v] << " 1\n";
	}

	return 0;
}
