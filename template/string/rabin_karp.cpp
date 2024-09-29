int rabinKarp(string& s)
{
    //return cur string's hash val
	int curHash = 0;
	int len = (int)s.length();
	for (int i = 0; i < len; i++) {
		curHash = ((curHash * a) % p + s[i]) % p;
	}

	return curHash;
}