//链表模板题，插入O(1)，不能随机读写
//uva11988
#include <iostream>
#include <cstring>
#include <list>

int main(){
    std::ios::sync_with_stdio(false);
    std::cin.tie(0);
    
    std::string str;
    while(std::cin>>str){
        std::list<char> li;
        auto it = li.end();
        for(auto c:str){
            if(c=='['){
                it=li.begin();
            }
            else if(c==']'){
                it=li.end();
            }
            else{
                li.insert(it,c);
            }
        }
        for(it=li.begin();it!=li.end();it++){
            std::cout<<*it;
        }
        std::cout<<"\n";
    }
    
    return 0;
}