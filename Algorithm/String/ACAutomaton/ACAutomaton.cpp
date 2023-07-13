//复杂度 文本串长度+模板串长度之和
//AC自动机，luogu P3808

#include <iostream>
#include <queue>

const int MAXN = 1000005;

class AC{
public:
	int trie[MAXN][26], total;
	int end[MAXN],fail[MAXN];

    void init(int m){
        for(int i=0;i<=m;i++){
            end[i] = 0;
            fail[i] = 0;
            for(int j=0;j<26;j++) trie[i][j] = 0;
        }
        total = 0;
    }

	void insert(std::string const & str){
	    //插入模式串
		int u = 0;
		for(auto c:str){
			if(!trie[u][c-'a']){
				trie[u][c-'a'] = ++total;
			}
			u = trie[u][c-'a'];
		}
		end[u]++;
	}

	void buildFail(){
	    //构建fail指针
	    std::queue<int> qu;
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

	int query(std::string const & str){
	    //查询主串str中出现了几个模式串
		int u = 0, res = 0;
		for(auto c:str){
			u = trie[u][c-'a'];
			for(int j = u ; j && end[j] != -1 ; j = fail[j]){
				res += end[j];
				end[j] = -1;
			}
		}

		return res;
	}
};

AC ac;

int main(){
	int n;
	std::cin>>n;
	std::string str;
	ac.init(1e6);
	
	for(int i=1;i<=n;i++){
		std::cin>>str;
		ac.insert(str);
	}
	ac.buildFail();
	std::cin>>str;
	std::cout<<ac.query(str)<<"\n";

	return 0;
}
