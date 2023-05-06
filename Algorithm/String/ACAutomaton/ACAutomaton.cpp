//复杂度 文本串长度+模板串长度之和
//AC自动机，luogu P3808

#include <iostream>
#include <queue>

const int MAXN = 1000005;

namespace AC{
	int trie[MAXN][26], total;
	int end[MAXN],fail[MAXN];

	void insert(std::string str){
		int u = 0;
		for(auto c:str){
			if(!trie[u][c-'a']){
				trie[u][c-'a'] = ++total;
			}
			u = trie[u][c-'a'];
		}
		end[u]++;
	}

	std::queue<int> qu;

	void buildFail(){
		for(int i=0;i<26;i++){
			if(trie[0][i]) qu.push(trie[0][i]);
		}

		while(!qu.empty()){
			int u = qu.front();
			qu.pop();

			for(int i=0;i<26;i++){
				if(trie[u][i]){
					fail[trie[u][i]] = trie[fail[u]][i];	
					qu.push(trie[u][i]);
				}
				else{
					trie[u][i] = trie[fail[u]][i];
				}
			}
		}
	}

	int query(std::string str){
		int u = 0, res = 0;
		for(auto c:str){
			u = trie[u][c-'a'];
			for(int j = u;j&&end[j]!=-1;j=fail[j]){
				res += end[j];
				end[j] = -1;
			}
		}

		return res;
	}
}

int main(){
	int n;
	std::cin>>n;
	std::string str;
	for(int i=1;i<=n;i++){
		std::cin>>str;

		AC::insert(str);
	}
	AC::buildFail();
	std::cin>>str;
	std::cout<<AC::query(str)<<"\n";

	return 0;
}
