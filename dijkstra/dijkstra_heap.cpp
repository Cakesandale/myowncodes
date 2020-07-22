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
#include "readData.h"

#define maxn 99999
typedef pair<long long,long long> P;
using namespace std;
int a_map[10001][10001];//这就是邻接存储图

int visited[100000];//visited[i]代表这个点有没有被当做源点去搜索过，1为有，0为没有。这样就不会重复搜索了。
vector<int> path(10005,0);




vector<int> dijkstra(int n,int u)//
{
    vector<int> dis(n,maxn);//dis数组，存储估计值
    priority_queue <P,vector<P>,greater<P> > dist_q;
    // memset(dis,88,sizeof(dis));//88不是十进制
    int start=u;//先从源点搜索
    visited[start]=1;//标记源点已经搜索过
    for(int i=0;i<=n;i++)
    {
        dis[i]=min(dis[i],a_map[start][i]);//先更新一遍
        dist_q.push(P(dis[i],i));
    }
    dis[u]=0;
    dist_q.push(P(0,u));
    while(!dist_q.empty())
    {
        int start=dist_q.top().second;
        dist_q.pop();
        //找到离源点最近的点，然后把编号记录下来，用于搜索。
        if(visited[start]) continue;
        visited[start]=1;        
        for(int j=0;j<=n;j++){
            if(dis[j]>dis[start]+a_map[start][j]){
                dis[j]=dis[start]+a_map[start][j];//以新的点来更新dis。
                path[j]=start;
                dist_q.push(P(dis[j],j));
            }
        }
    }
    return dis;
}
int main()
{
    clock_t time_start=clock();
    //读数据
    int n=0;
    memset(a_map,88,sizeof(a_map));
    ///////
    ifstream input;
    input.open("/Users/01384573/Documents/Mycodes/shortestpath/grid_10000.csv");
    string line;
    getline(input,line);
    while(getline(input,line))
    {
        if(line[0]=='o')
            break;
        istringstream Readstr(line);
        string partOfstr;
        int data[3];
        
        for(int i = 0; i < 3; i++)
        {	
            getline(Readstr, partOfstr, ',');
            data[i] = atof(partOfstr.c_str());	
            
        }
        a_map[data[0]][data[1]]=data[2];
        n=max(data[0],n);
        n=max(data[1],n);
        cout<<"input detail: ";
        cout << data[0]<<" " << data[1] <<" " <<data[2] <<endl;
        // break;
    }
    
    n++;
    for(int i=0;i<=n;i++)
        for(int j=0;j<=n;j++)
            if(i==j)
                a_map[i][j]=0;
    vector<int> dis=dijkstra(n,0);//以0为源点。
    clock_t time_end=clock();
    cout<<"time use:"<<1000*(time_end-time_start)/(double)CLOCKS_PER_SEC<<"ms"<<endl;
    ofstream outfile;
    outfile.open("/Users/01384573/Documents/Mycodes/shortestpath/output.txt");
    outfile<<"time use:"<<1000*(time_end-time_start)/(double)CLOCKS_PER_SEC<<"ms\n";
    for(int i=0;i<=n;i++){
        if(dis[i]==maxn){
            cout<<i<<" has no solution\n";
            outfile<<i<<" has no solution\n";
            continue;
        }
        cout<<i<<"->"<<dis[i]<<"\n";
        outfile<<"node "<<i<<": pre-node->"<<path[i]<<" shortest-path->"<<dis[i]<<"\n";
    }
    outfile.close();
}