vector<int> failure(string& s) 
{
    vector<int> f(s.size());
    int j = 0;
    for (int i = 1; i < s.size(); i++) {
        while (j > 0 && s[i] != s[j]) j = f[j - 1];
        if (s[i] == s[j]) f[i] = ++j;
    }
    return f;
}
bool kmp(string& s, string& p)
{
    vector<int> f = failure(p);
    int j = 0;
    for (int i = 0; i < s.size(); i++) {
        while (j > 0 && s[i] != p[j]) j = f[j - 1];
        if (s[i] == p[j]) j++;
        if (j == p.size()) {
            cout << 1;
            return 0;
        }
    }
}
