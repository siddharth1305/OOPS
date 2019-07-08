#include <bits/stdc++.h>
#define ll long long 
#define ld long double
#define F first
#define S second
#define pb push_back 
#define all(v) v.begin(),v.end()
#define pii pair <int,int >
#define pll pair <ll,ll >
#define pld pair <long double,long double>
#define SET(arr,val) memset(arr,val,sizeof arr)
#define si(a) scanf("%d",&a)
#define sl(a) scanf("%lld",&a)
using namespace std;
const int MAXN=100005;
const int MOD=1000000000+7 ;

struct Trie
{
	bool isEnd;
	Trie *nextChar[30];
	Trie(){
		isEnd=false;
		for(int i=0;i<30;i++)
			nextChar[i]=NULL;
	}
	/* data */
};

void addWord(string s,Trie* root){
	Trie *pcrawl=root;
	for(int i=0;i<s.size();i++){
		int ind=s[i]-'a';
		if(!pcrawl->nextChar[ind]){
			pcrawl->nextChar[ind]=new Trie();
		}
		pcrawl=pcrawl->nextChar[ind];
	}
	pcrawl->isEnd=true;
}

bool search(string s, Trie *root){
	Trie *pcrawl=root;
	for(int i=0;i<s.size();i++){
		int ind=s[i]-'a';
		if(!pcrawl->nextChar[ind]){
			return false;
		}
		pcrawl=pcrawl->nextChar[ind];
	}
	return pcrawl->isEnd==true;
}

bool tetsWord(string s,Trie *root, int index,int count){
	Trie *pcrawl=root;
	int n=s.size();
	for(int i=index;i<n;i++){
		cout<<s[i]<<" "<<count<<endl;
		int ind=s[i]-'a';
		if(pcrawl->nextChar[ind]==NULL)
			return false;
		if(pcrawl->nextChar[ind]->isEnd){
			// cout<<ind<<" "<<
			cout<<"yo";
			if(i==n-1)
				return count>=1;
			if(tetsWord(s,root,i+1,count+1))
				return true;
		}
		pcrawl=pcrawl->nextChar[ind];
	}
	return false;
}

int main()
{
	Trie *root=new Trie();
	addWord("cat",root);
	// addWord("cats",root);
	// addWord("catsdogcats",root);
	addWord("dog",root);
	addWord("dogcatsdog",root);
	addWord("hippopotamuses",root);

	cout<<tetsWord("catsdogcat",root,0,0);
	return 0;
}