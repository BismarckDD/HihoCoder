#include<cstdio>
#include<iostream>
using namespace std;

int ans = 0, n;
struct TrieNode 
{
	int count;
	TrieNode* next[26];
	TrieNode() :count(0) { for (size_t i = 0; i < 26; ++i) next[i] = NULL; };
	TrieNode(int x) :count(x) { for (size_t i = 0; i < 26; ++i) next[i] = NULL; };
	~TrieNode() 
	{
		for (size_t i = 0; i < 26; ++i)
			if (next[i])
				delete next[i];
	}
};

void InsertWord(char *word, int pos, TrieNode *p)
{
	if (word[pos] == '\0') 
		return;
	else
	{
		if (p->next[word[pos] - 'a'] == NULL)
			p->next[word[pos] - 'a'] = new TrieNode();
		p->next[word[pos] - 'a']->count++;
		InsertWord(word, pos + 1, p->next[word[pos] - 'a']);
	}
}

void dfs(TrieNode *root)
{
	if (root->count <= 5)
		ans++;
	else
		for (size_t i = 0; i < 26; ++i)
			if (root->next[i])
				dfs(root->next[i]);
}

int main()
{
	TrieNode* root = new TrieNode();
	root->count = ~(1 << 31);
	char word[1000002];
	scanf("%d", &n);
	for (int i = 0; i < n; i++)
	{
		scanf("%s", word);
		InsertWord(word, 0, root);
	}
	ans = 0;
	dfs(root);
	printf("%d\n", ans);
	delete root;
	return  0;
}
