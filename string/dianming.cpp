/* trie */
#include <bits/stdc++.h>
using namespace std;

int trie[1000010][26];
int num[1000010];
int pos = 1;
void insert(char str[]) {
    int p = 0;
    for (int i = 0; str[i]; i++) {
        int n = str[i] - 'a';
        if (!trie[p][n]) trie[p][n] = pos++;
        p = trie[p][n];
    }
    num[p]++;
}
int find(char str[]) {
    int p = 0;
    for (int i = 0; str[i]; i++) {
        int n = str[i] - 'a';
        if (!trie[p][n]) return 0;
        p = trie[p][n];
    }
    return num[p]++;
}

int main() {
    memset(num, 0, sizeof(num));
    int n; scanf("%d", &n);
    char s[100];
    while (n--) {
        scanf("%s", s);
        insert(s);
    }
    int m; scanf("%d", &m);
    while (m--) {
        scanf("%s", s);
        int cnt = find(s);
        if (cnt == 0) printf("WRONG\n");
        else if (cnt == 1) printf("OK\n");
        else printf("REPEAT\n");
    }
    return 0;
}