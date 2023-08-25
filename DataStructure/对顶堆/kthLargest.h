//动态维护一个集合的第k大数，每次操作logn
//spoj RMID2
//维护第k小只要维护第n-k大即可
//另外这个k是可以变化的，不需要固定，复杂度确实是logn

#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

template<typename T>
class KthLargest{
private:
    std::priority_queue<T,std::vector<T>,std::less<T> > big{};
    std::priority_queue<T,std::vector<T>,std::greater<T> > small{};
    size_t kth{};
    size_t size{};
    
    void update(){
        kth = std::min(kth,size);
        while(kth<small.size()){
            big.push(small.top());
            small.pop();
        }
        while(kth>small.size()){
            small.push(big.top());
            big.pop();
        }
    }
    
public:
    KthLargest():kth(1),size(0){}
    
    T findK(size_t k){
		//找到第k大的数字
        kth = k;
        update();
        return small.top();
    }
    
    void eraseK(size_t k){
		//移除第k大的数字
        kth = k;
        update();
        small.pop();
        size--;
        update();
    }
    
    void insert(T x){
		//插入一个数字
        size++;
        if(small.empty() || x>=small.top()){
            small.push(x);
        }
        else{
            big.push(x);
        }
        update();
    }
    
    size_t getSize(){
        return size;
    }
};

KthLargest<int> ddd;
