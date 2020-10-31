#include <bits/stdc++.h>
#define ll long long int


using namespace std;


struct segment {
	//value is index
	int left;
	int right;
};

typedef int item;
// struct item {
// 	ll seg, pref, suf, sum;
// };

struct segtree { 
	int size;

	vector<item> values;

	void init(int n) {
		size = 1;
		while (size < n) 
			size *= 2;
		values.assign(2*size, NEUTRAL_ELEMENT);
	}

	void build(vector<int> &a, int s, int ls, int rs) {
		if (rs - ls == 1) {
			if (ls < (int)a.size())
				values[s] = single(a[ls]);
			return;
		}
		int mid  = ls + (rs - ls)/2;

	item NEUTRAL_ELEMENT = 0;

	item merge(item a, item b) {
		return a + b;
	}

	item single(int v) {
		return v;
	}

		build(a, 2*s + 1, ls, mid);
		build(a, 2*s + 2, mid, rs);

		values[s] = merge(values[2*s + 1], values[2*s + 2]);
	}

	void build(vector<int> &a) {
		build(a, 0, 0, size);
	}

	void set(int i, ll v, int s, int ls, int rs) {
		if (rs - ls == 1) {
			values[s] = single(v);
			return;
		}

		int mid  = ls + (rs - ls)/2;
		if (i < mid)
			set(i, v, 2*s + 1, ls, mid);
		else
			set(i, v, 2*s + 2, mid, rs);

		values[s] = merge(values[2*s + 1], values[2*s + 2]);
	}

	void set(int i, int v) {
		set(i, v, 0, 0, size);
	}

	item calc(int l, int r, int s, int ls, int rs) {
		if (r <= ls || l >= rs)
			return NEUTRAL_ELEMENT;
		if (ls >= l && rs <= r)
			return values[s];

		int mid = ls + (rs - ls)/2;
	
		item a1 = calc(l, r, 2*s + 1, ls, mid);
		item a2 = calc(l, r, 2*s + 2, mid, rs);
		return merge(a1, a2);
	}

	item calc(int l, int r) {
		return calc(l, r, 0, 0, size);
	}

	int find(int k, int s, int ls, int rs) {
		if (rs - ls == 1)
			return ls;

		int mid = ls + (rs - ls)/2;
		int sl = values[2 * s + 1];
		if (k < sl)
			find(k, 2*s + 1, ls, mid);
		else
			find(k - sl, 2*s + 2, mid, rs);
	}

	int find(int k) {
		return find(k, 0, 0, size);
	}

};

void solver() {
	//set left borders as 1
	for (int i = 0; i < n; ++i) {
		//right border
		if (dict[i] != -1) {
			//left border is zero 
			int j = dict[i];
			int r = p[j].second;
			int l = p[j].first;
			result[j] += st.calc(l, r);
			st.set(l, 0);
		}
	}
}

int main(int argc, char const *argv[]) {
	int n, m;
	segtree st;
	cin>> n;
	segment s[n+1];
	vector<int> a(2*n+1), result(n+1), right_val(2*n+1, -1);
	st.init(2*n);
	//ini
	for (int i = 1; i <= n; ++i) 
		s[i] = {-1, -1};
	for (int i = 1; i < 2*n; ++i) {
		int val;
		cin>> val;
		a[i] = val;
		if (s[val].left == -1)
			s[val].left = i;
		else {
			s[val].right = i;
			right_val[i] = val;
		}
	}
	// for (int i = 0; i < n; ++i)
	// 	cout<< p[i].first<<" "<< p[i].second<<endl;
	// for (int i = 0; i < st.size; ++i) 
	// 	printf("%d ", st.values[i]);
	// printf("\n");
	// while (m--) {
	// 	int operation;
	// 	cin>> operation;
	// 	if (operation == 1) {
	// 		int i;
	// 		cin>> i;
	// 		a[i] = 1 - a[i];
	// 		st.set(i, a[i]);
	// 	} else {
	// 		int k;
	// 		cin>> k;
	// 		printf("%d\n", st.find(k));
	// 	}
			
	// }
	// for (int i = 0; i < 2*n; ++i)
	// 	cout<< dict[i]<<" ";
	// cout<< endl;
	for (int i = 0; i < 2*n; ++i) {
		if (dict[i] != -1) { //it is a right end
			int j = dict[i];
			int r = p[j].second;
			int l = p[j].first;
			result[j] = st.calc(l, r);
			st.set(l, 1);
			// for (int i = 0; i < st.size; ++i)
			// 	cout<< st.values[i]<<" ";
			// cout<< endl;
			// cout<<j+1<<" ";
		}
	}
	for (int i = 0; i < n; ++i)
		cout<< result[i]<< " ";
	return 0;
}

