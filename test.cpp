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

void solve(){
	vector<int> a;
	fstream f("fileinput.txt", ios::in);
	while(!f.eof()){
		string s; getline(f, s);
		a.pb(s);
	}

	f.close();

	fstream result_out("result.txt", ios::out)
	for(string file: a) {
		f.open(file, ios::in);
		int n; f >> n;
		vector<int> array;
		cin >> array;
		sort(all(array));
		result_out << n << '\n' << array << '\n';
	}

	result_out.close();

	delete[] a;
}

int main(){
	fastio();
	int t = 1; //cin >> t;
	while(t--) solve();
	return 0;
}