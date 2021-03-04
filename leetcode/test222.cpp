#include <vector>
vector<int> combine(vector<int> &a, int m, vector<int> &b,int n){
    int N=a.size();
    int k=0;
    for(int i=m;i<N;++i)
        a[i]=b[k]
        for(int j=i;j>0;--j)
             if(a[j]<a[j-1]) swap(a[j],a[j-1]);
             else break;
    return a;
}