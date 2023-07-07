//维护一个序列的第k大数，每次操作logn

#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

template<typename T>
class KthLargest{
private:
    std::priority_queue<T,std::vector<T>,std::less<T> > big{};
    std::priority_queue<T,std::vector<T>,std::greater<T> > small{};
    int kth{};
    int size{};
    
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
    
    T findK(int k){
        kth = k;
        update();
        return small.top();
    }
    
    void eraseK(int k){
        kth = k;
        update();
        small.pop();
        size--;
        update();
    }
    
    void insert(T x){
        size++;
        if(small.empty() || x>=small.top()){
            small.push(x);
        }
        else{
            big.push(x);
        }
        update();
    }
    
    int getSize(){
        return size;
    }
};

