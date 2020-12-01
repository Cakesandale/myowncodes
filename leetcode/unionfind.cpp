
#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <ctime>

using namespace std;
class Unionfind{
    public:
    vector<int> father;
    int num;
    
    Unionfind(vector<vector<char>>& grid,int m,int n){
        num=0;
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]=='1'){
                    num++;
                }
            }
        }
        int product=m*(n);
        father.resize(product,0);
        for(int i=0;i<product;i++){
            father[i]=i;
        }
    }
    
    int find(int x){
        while(father[x]!=x){
            father[x]=father[father[x]];
            x=father[x];
        }
        return x;
    }
    void Union(int x1,int x2){
        int a=find(x1);
        int b=find(x2);
        if(a!=b){
            father[b]=a;
            num--;
        }
    }
    
};

class Solution {
public:
    int numIslands(vector<vector<char>>& grid) {
        int m=grid.size();
        if(m==0) return 0;
        int n=grid[0].size();
        if(n==0) return 0;
        Unionfind *uf=new Unionfind(grid,m,n);
        for(int i=0;i<m;i++){
            for(int j=0;j<n;j++){
                if(grid[i][j]=='1'){
                    if(i!=(m-1)&&grid[i+1][j]=='1')
                        uf->Union(i*n+j,(i+1)*n+j);
                    if(j!=(n-1)&&grid[i][j+1]=='1')
                        uf->Union(i*n+j,i*n+j+1);
                }
            }
        }
        return uf->num;
    }
    // int main(int argc, char *argv[])
    
};

int main(){
        vector<vector<char>> c={{'1','1','1','1','0'},{'1','1','1','1','0'},{'1','1','1','1','0'},{'1','1','1','1','0'}};
        Solution *s=new Solution;

        // =[["1","1","1","1","0"],["1","1","0","1","0"],["1","1","0","0","0"],["0","0","0","0","0"]];
        return s->numIslands(c);
    }
