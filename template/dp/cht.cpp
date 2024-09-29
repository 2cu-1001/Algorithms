struct line {
	ll m, k;
	line(ll m, ll k): m(m), k(k){}
};
ld cross(line& l1, line& l2) {
	return 1.0 * (double)(l2.k - l1.k) / (l1.m - l2.m);
}
int getLineIdx(ll pi)
{
	int lo = 0, hi = (int)l.size() - 1, mid;
	while (lo < hi) {
		mid = (lo + hi) / 2;
		if (pi < cross(l[mid], l[mid + 1])) hi = mid;
		else lo = mid + 1;
	}
	return hi;
}
void solve()
{
	for (int i = 1; i <= N; i++) p[i] = p[i - 1] + arr[i];
	ll m, k;
	line init(0, 0);
	l.push_back(init);
	for (int i = 1; i <= N; i++) {
		int idx = getLineIdx(p[i]);

        /*
        d[i] = l[idx].m * p[i] + l[idx].k + p[i] * p[i] * A + p[i] * B + C;
		d[i] = max(d[i], p[i] * p[i] * A + p[i] * B + C);

		m = -2 * p[i] * A;
		k = p[i] * p[i] * A - p[i] * B + d[i];
        */

		line curLine(m, k);
		l.push_back(curLine);
		int sz = (int)l.size() - 1;
		while (sz > 1 && cross(curLine, l[sz - 1]) < cross(l[sz - 1], l[sz - 2])) {
			l[sz - 1] = l.back();
			l.pop_back();
			sz--;
		}
	}
	cout << d[N];
}

//using multiset
struct line {
    mutable ll m, k, p;
    bool operator<(const line& o) const { return m < o.m; }
    bool operator<(ll x) const { return p < x; }
};
struct CHT : multiset<line, less<>> {
    //(for doubles, use inf = 1/.0, div(a,b) = a/b)  
    const static ll inf = LLONG_MAX;
    ll div(ll a, ll b) { return a / b - ((a ^ b) < 0 && a % b); }
    bool isect(iterator x, iterator y) {
        if (y == end()) return x->p = inf, 0;
        if (x->m == y->m) x->p = x->k > y->k ? inf : -inf;
        else x->p = div(y->k - x->k, x->m - y->m);
        return x->p >= y->p;
    }
    void add(ll m, ll k) { //add y = mx + k  
        auto z = insert({ m, k }), y = z++, x = y;
        while (isect(y, z)) z = erase(z);
        if (x != begin() && isect(--x, y)) isect(x, y = erase(y));
        while ((y = x) != begin() && (--x)->p >= y->p) isect(x, erase(y));
    }
    ll query(ll x) {
        auto l = *lower_bound(x);
        return l.m * x + l.k;
    }
    //source : https://ps.mjstudio.net/convex-hull-trick
};