#include <bits/stdc++.h>
#define ll long long int


using namespace std;

struct segtree { 
	int size;

	vector<ll> sums;
	void init(int n) {
		size = 1;
		while (size < n) 
			size *= 2;
		sums.assign(2*size, 0LL);
	}

	void build(vector<int> &a, int s, int ls, int rs) {
		if (rs - ls == 1) {
			if (ls < (int)a.size())
				sums[s] = a[ls];
			return;
		}
		int mid  = ls + (rs - ls)/2;

		build(a, 2*s + 1, ls, mid);
		build(a, 2*s + 2, mid, rs);

		sums[s] = sums[2*s + 1] + sums[2*s + 2];
	}

	void build(vector<int> &a) {
		build(a, 0, 0, size);
	}

	void set(int i, int v, int s, int ls, int rs) {
		if (rs - ls == 1) {
			sums[s] = v;
			return;
		}

		int mid  = ls + (rs - ls)/2;
		if (i < mid)
			set(i, v, 2*s + 1, ls, mid);
		else
			set(i, v, 2*s + 2, mid, rs);

		sums[s] = sums[2*s + 1] + sums[2*s + 2];
	}

	void set(int i, int v) {
		set(i, v, 0, 0, size);
	}

	ll sum(int l, int r, int s, int ls, int rs) {
		if (r <= ls || l >= rs)
			return 0;
		if (ls >= l && rs <= r)
			return sums[s];

		int mid = ls + (rs - ls)/2;
		ll a1 = sum(l, r, 2*s + 1, ls, mid);
		ll a2 = sum(l, r, 2*s + 2, mid, rs);
		return a1 + a2;
	}

	ll sum(int l, int r) {
		return sum(l, r, 0, 0, size);
	}
};

int main(int argc, char const *argv[]) {
	int n, m;
	segtree st;
	cin>> n>> m;
	vector<int> a(n);
	st.init(n);
	for (int i = 0; i < n; ++i) 
		cin>> a[i];

	st.build(a);

	while (m--) {
		int operation;
		cin>> operation;
		if (operation == 1) {
			int i, v;
			cin>> i>> v;
			st.set(i, v);
		} else {
			int l, r;
			cin>> l>> r;
			cout<< st.sum(l, r)<<"\n";
		}
	}
	return 0;
}

