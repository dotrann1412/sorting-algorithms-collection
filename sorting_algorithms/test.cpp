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

void _swap(int& a, int& b) {
	swap(a, b);
}

int _min(int a, int b) {
	return min(a, b);
}

void shaker_sort(int* begin, int* end) {
	bool flag = true;
	while(begin < end) {
		int *lastSwapped = begin;
		if(flag) {
			for(int* i = begin; i < end - 1; ++i)
				if(*i > *(i + 1)) _swap(*i, *(i + 1)), lastSwapped = i + 1;
			
			if(lastSwapped == begin) break;
			end = lastSwapped;
		} else {
			for(int* i = end - 1; i > begin; --i)
				if(*i < *(i - 1)) _swap(*i, *(i - 1)), lastSwapped = i;

			if(lastSwapped == begin) break;
			begin = lastSwapped;
		}
		
		flag = 1 - flag;
	}
}

void heapfity(int* a, int n, int k) {
	if(2 * k >= n) return;
	int i = 2 * k + 1;
	if(i < n - 1 && a[i] < a[i + 1]) ++i;
	if(i < n && a[k] < a[i]) _swap(a[i], a[k]);
	heapfity(a, n, i);
}

void heap_sort(int* a, int* end) {
	int n = end - a;
	for(int i = n / 2; i >= 0; --i)
		heapfity(a, n, i);
	
	for(int i = n - 1; i > 0; --i) {
		_swap(a[i], a[0]);
		heapfity(a, i, 0);
	}
}

template<class T>
bool _greater(T a, T b)
{
	return a > b;
}

template<class T>
bool _lesser(T a, T b)
{
	return a < b;
}

/*template<class T>
T* partition(T* begin, T* end, bool (*criteria)(T, T))
{
	T* pivot = end - 1, *iter = begin - 1;

	for(T* i = begin; i < end - 1; ++i) {
		if(criteria(*i, *pivot)) _swap(*++iter, *i);
	}

	_swap(*++iter, *pivot);
	return iter;
}

template<class T>
void _sort(T* begin, T* end, bool (*criteria)(T, T) = _lesser){
	if(begin < end) {
		T* pivot = partition(begin, end, criteria);

		_sort(begin, pivot, criteria);
		_sort(pivot + 1, end, criteria);
	}
}*/

int* partition(int* begin, int* end) {
	_swap(*(begin + _min(rand() % (end - begin), end - begin - 1)), *(end - 1));

	int* iter = begin - 1, *pivot = end - 1;
	for (int* i = begin; i < end - 1; ++i)
		if(*i < *pivot) _swap(*++iter, *i);
	
	_swap(*++iter, *pivot);
	return iter;
}

void quick_sort(int* begin, int* end) {
	if(end - begin <= 1) return;

	int* pivot = partition(begin, end);
	quick_sort(begin, pivot);
	quick_sort(pivot + 1, end);
}

void solve(){
	
	int n; cin >> n;
	int* a = new int[n];
	for(int i = 0; i < n; cin >> a[i++]);
	
	//sort(a, a + n, greater<int>());
	quick_sort(a, a + n);
	
	for(int i = 0; i < n - 1; ++i) {
		cout << a[i] << ' ';
	}
	//cout << "AC" << '\n';
	delete[] a;
}

int main(){
	srand(time(nullptr));
	fastio();
	int t = 1; //cin >> t;
	while(t--) solve();
	return 0;
}