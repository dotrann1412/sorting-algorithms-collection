#include <bits/stdc++.h>

using namespace std;

#define init(file_name) freopen(filename.in, "r", stdin); freopen(filename.out, "w", stdout)
#define fastio() ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0)
#define all(a) a.begin(), a.end()

#define ll long long
#define vt vector
#define pb push_back
#define fi first
#define se second
#define pii pair<int, int>
#define db double

const ll MaxN = 1e5 + 5;
const ll INF = 1e9;
const ll MOD = 1e9 + 7;
const db eps = 1e-5;
const db pi = acos(-1);

vt<string> split(string s, char key) {
	vector<string> a;
	string cur = "";
	for(auto x: s) 
		if(x == key) a.pb(cur), cur = ""; 
		else cur += x;	
	if(cur != "") a.pb(cur);
	return a;
}

void solve(){
	fstream src("statistic_result.csv", ios::in);
	fstream time_tracking("time_tracking.csv", ios::out);
	fstream cmp_tracking("cmp_tracking.csv", ios::out);

	while(!src.eof()) {
		string s; getline(src, s, '\n');
		vector<string> t = split(s, ',');
		for(int i = 0; i < t.size(); ++i) {
			vector<string> F = split(t[i], '-');
			if(F.size() == 1) time_tracking << F[0] << (i != t.size() - 1 ? "," : "\n"), cmp_tracking << F[0] << (i != t.size() - 1 ? "," : "\n");
			else {
					time_tracking << F[0] << (i != t.size() - 1 ? "," : "\n"), 
					 cmp_tracking << strtoll(F[1].c_str(), nullptr, 10) << (i != t.size() - 1 ? "," : "\n");
			}
		}
	}

	src.close(), time_tracking.close(), cmp_tracking.close();
}

int main(){
	fastio();
	int t = 1; // cin >> t;
	while(t--) solve();
	return 0;
}