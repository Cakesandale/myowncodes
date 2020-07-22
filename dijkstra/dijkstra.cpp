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
#include <ctime>
#include "readData.h"

#define maxn 99999
using namespace std;
int a_map[100][100];//这就是邻接存储图

int visited[10000];//visited[i]代表这个点有没有被当做源点去搜索过，1为有，0为没有。这样就不会重复搜索了。




vector<int> dijkstra(int n,int u)//
{
    vector<int> dis(n,maxn);//dis数组，存储估计值
    // memset(dis,88,sizeof(dis));//88不是十进制
    int start=u;//先从源点搜索
    visited[start]=1;//标记源点已经搜索过
    for(int i=1;i<=n;i++)
    {
        dis[i]=min(dis[i],a_map[start][i]);//先更新一遍
    }
    for(int i=1;i<=n-1;i++)
    {
        int minn=maxn;
        for(int j=1;j<=n;j++)
            if(visited[j]==0 && minn>dis[j])
            {
                minn=dis[j];
                start=j;//找到离源点最近的点，然后把编号记录下来，用于搜索。
            }
        visited[start]=1;        
        for(int j=1;j<=n;j++)
            dis[j]=min(dis[j],dis[start]+a_map[start][j]);//以新的点来更新dis。
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
    input.open("/Users/01384573/Documents/Mycodes/shortestpath/算例1.csv");
    string line;
    getline(input,line);
    while(getline(input,line))
    {
        if(line[0]=='o')
            break;
        istringstream Readstr(line);
        string partOfstr;
        int data[3];
        n++;
        for(int i = 0; i < 3; i++)
        {	
            getline(Readstr, partOfstr, ',');
            data[i] = atof(partOfstr.c_str());	
            
        }
        a_map[data[0]][data[1]]=data[2];
        
        cout<<"input detail: ";
        cout << data[0]<<" " << data[1] <<" " <<data[2] <<endl;
        // break;
    }
    /////////
    // const char* path = "/Users/01384573/Documents/Mycodes/shortestpath/算例1.csv";
    // //初始化CSVreader类对象
    // CSVreader reader(path);
    // //读数据,第一行为列名，不做处理
    // reader.readline();
    // while(!reader.readline())
    // {
    //     n++;
    //     a_map[reader.data[0]][reader.data[1]]=reader.data[2];
        
    //     cout<<"input detail: ";
    //     cout << reader.data[0] << reader.data[1] <<reader.data[2] <<endl;
    //     // break;
    // }
   
    // system("pause");

    for(int i=1;i<=n;i++)
        for(int j=1;j<=n;j++)
            if(i==j)
                a_map[i][j]=0;
    vector<int> dis=dijkstra(n,1);//以1为源点。
    clock_t time_end=clock();
    cout<<"time use:"<<1000*(time_end-time_start)/(double)CLOCKS_PER_SEC<<"ms"<<endl;
    for(int i=1;i<=n;i++){
        if(dis[i]==maxn){
            cout<<i<<" has no solution\n";
            continue;
        }
        cout<<i<<"->"<<dis[i]<<"\n";
    }
}