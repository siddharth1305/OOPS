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
const int MAXN=5005;
const int MOD=998244353 ;

struct  charNode
{
	char ch;
	charNode *next,*prev;
	charNode(char c){
		ch=c;
		next=NULL;
		prev=NULL;
	}
};

struct Edit
{
	string edition;
	charNode* data;
	Edit(string e,charNode* c){
		data=c;
		edition=e;
	}
};

class textEditor
{

	stack <Edit *> undo_stack;
	charNode *cursor,*end;
	
 public: 
 	textEditor(){
 		// undo_stack = new stack();
		stack <Edit *> undo_stack;
		end= new charNode('\0');
		cursor=end;
	}
	void moveCursorLeft(){
		if(cursor->prev==NULL)
			return;
		cursor=cursor->prev;
		Edit *temp= new Edit("Right",NULL);
		undo_stack.push(temp);
	}
	void moveCursorRight(){
		if(cursor->next==NULL)
			return;
		cursor=cursor->next;
		undo_stack.push(new Edit("Left",NULL));
	}


	void insertCharacter(char ch){
		charNode *newNode = new charNode(ch);
		insert(newNode);
		undo_stack.push(new Edit("del",NULL));
	}
	void backSpace(){
		if(cursor->prev==NULL)
			return;
		undo_stack.push(new Edit("INS",deleteChar(cursor->prev)));
	}

	void undo(){
		if(undo_stack.empty())
			return;
		Edit *edit=undo_stack.top();
		undo_stack.pop();
		map <string , int > mp;
		mp["Left"]=1;
		mp["Right"]=2;
		mp["del"]=3;
		mp["INS"]=4;

		switch(mp[edit->edition]){
			case 1:
			cursor=cursor->prev;break;
			case 2:
			cursor=cursor->next;break;
			case 3:
			deleteChar(cursor->prev);break;
			case 4:
			insert(edit->data);break;
			default:
			return;
		}
	}

	string toString(){
		string s="";
		charNode *n=end->prev;
		if(cursor==end)
			s+="|";
		while(n){
			s=n->ch+s;
			if(cursor==n){
				s="|"+s;
			}
			n=n->prev;
		}
		return s;
	}
	
	void insert(charNode *node){
		charNode *prevNode = cursor->prev;
		node->next=cursor;
		cursor->prev=node;
		if(prevNode!=NULL){
			prevNode->next=node;
			node->prev=prevNode;
		}
	}

	charNode* deleteChar(charNode *del){
		charNode *prevNode= del->prev;
		if(prevNode!=NULL){
			del->next->prev=prevNode;
			prevNode->next=del->next; 
		}
		cursor->prev=del->prev;
		return del;
	}
	
}; 



int main() {
	textEditor TD= textEditor();
	TD.insertCharacter('a');
	TD.insertCharacter('b');
	TD.insertCharacter('z');
	cout<<TD.toString()<<endl;
	TD.insertCharacter('b');
	TD.insertCharacter('b');
	cout<<TD.toString()<<endl;
	TD.backSpace();
	cout<<TD.toString()<<endl;
	TD.moveCursorLeft();
	cout<<TD.toString()<<endl;
	TD.moveCursorRight();
	cout<<TD.toString()<<endl;
	return 0;
}   