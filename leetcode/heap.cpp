#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include <set>
#include <stack>
using namespace std;

struct HeapStruct{
    vector<int> elements;
     
    int size;
    int capacity;
    HeapStruct(int sz): size(0), capacity(sz)
    {
        elements=vector<int>(sz+1,0);
        // elements.push_back(INT_MAX);
        elements[0]=INT_MAX;// 哨兵元素，比大顶堆中最大的元素大
    };
};

void insert(HeapStruct* hp, int m){
    if(hp->capacity==hp->size){
        printf("heap is full.");
        return;
    }
    int i=++hp->size;
    for(;hp->elements[i/2]<m; i/=2){//swim()
        hp->elements[i]=hp->elements[i/2];//faster than swap data;
    }
    hp->elements[i]=m;
}

int pop_max(HeapStruct* hp){
    if(hp->size==0){
        printf("heap is empty.");
        return 0;
    }
    int maxitm=hp->elements[1];
    //sink()
    int last=hp->elements[hp->size--];
    int parent;
    for(parent=1;parent*2<=hp->size;){
        int child=parent*2;
        if(child<hp->size && hp->elements[child]<hp->elements[child+1])
            child++;//choose the larger child;
        if(last >= hp->elements[child]) {
            break;
        }
        hp->elements[parent] = hp->elements[child];
        parent=child;
    }
    hp->elements[parent] = last;
    return maxitm;
}

int main(){
    HeapStruct *hp=new HeapStruct(10);
    int m[6]={4,7,10,3,6,1};
    for(int x:m){
        insert(hp,x);
    }
    for(int n:hp->elements){
        cout<<n;
    }
    int b=pop_max(hp);
    cout<<"max: "<<b<<endl;
    return 0;
}

