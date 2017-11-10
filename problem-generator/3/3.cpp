#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <iostream>
#include <algorithm>

using namespace std;

#define lt 0
#define eq 1
#define neq 2
#define gt 3

#define maxn 101111

int n, T[4][maxn];
pair<int, int> a[maxn];
char ch1[10], ch2[10];

int stat(char x) {
	switch (x) {
		case '<': return lt;
		case '>': return gt;
		case '=': return eq;
	}
	return -1;
}


void work() {
	scanf("%d", &n);
	for (int i = 1; i <= n; ++i) {
		scanf("%s%d%s", ch1, &a[i].first, ch2);
		a[i].second = stat(ch1[0]);
		if (ch2[0] == 'N') {
			if (a[i].second == lt) {
				a[i].first--;
			}
			if (a[i].second == gt) {
				a[i].first++;
			}
			a[i].second = 3 - a[i].second;
		}

	}
	a[0] = make_pair(0, gt);
	a[n+1] = make_pair(1000000001, lt);
	sort(a + 1, a + n + 1);

	for (int i = 0; i < 4; ++i) {
		for (int j = 1; j <= n + 1; ++j) {
			T[i][j] = T[i][j-1] + (a[j].second == i);
			if (j == n + 1) T[i][j] = T[i][j-1];
		}
	}
	int ans = n;
	for (int i = 1; i <= n + 1; ++i) {
		int l = a[i-1].first, r = a[i].first;
		if (l >= r - 1) continue;
		int tmp = 0;
		for (int j = 0; j < 4; ++j) {
			if (j != neq && j != gt) tmp += T[j][i-1];
			if (j != neq && j != lt) tmp += T[j][n+1] - T[j][i-1];
		}
		ans = min(ans, tmp);
	}
	for (int i = 1; i <= n; ++i) {
		int x = i;
		for (; a[x].first == a[i].first; ++i);
		--i;
		int l = x, r = i;
		int tmp = n;
		tmp -= T[eq][r] - T[eq][l-1];
		tmp -= T[neq][l-1] + (T[neq][n+1] - T[neq][r]);
		tmp -= T[gt][l-1] + (T[lt][n+1] - T[lt][r]);
		ans = min(ans, tmp);
	}
	printf("%d\n", ans);
}


int main() {
	int TC;
	scanf("%d", &TC);
	while (TC--) {
		work();
	}
	return 0;
} 
