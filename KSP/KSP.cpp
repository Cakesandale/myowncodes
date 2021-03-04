#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <cstring>
#include <cstdlib>
#include <queue>
#include <ctime>
#include <stack>
// #include "KSP_Arc.h"
// #include "KSP_Node.h"
// #include "KSP_Graph.h"

using namespace std;
#define maxn 99999
typedef pair<long long,long long> P;

vector<int> visited(10001,0);
vector< vector<int> > a_map(10001,vector<int>(10001,50));
vector<int> dis(10001,99999);//dis数组，存储估计值
vector<int> inarc(10001,0);//每个node的入边数；

vector<int> dijkstra(int n, int s)//
{
    vector<int> path(n,-1);
    
    priority_queue <P,vector<P>,greater<P> > dist_q;
    // memset(dis,88,sizeof(dis));//88不是十进制
    int start=s;//先从源点搜索
    visited[start]=1;//标记源点已经搜索过
    for(int i=0;i<=n;i++)
    {
        dis[i]=min(dis[i],a_map[start][i]);//先更新一遍
        dist_q.push(P(dis[i],i));
    }
    dis[s]=0;
    dist_q.push(P(0,s));
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
    return path;
}

unsigned addNode(int cur, int pre){//add duplicate to map
    vector<int> newrow;
    size_t s=a_map.size();
    for(int i=0;i<a_map.size();i++){
        if(i!= pre){
            a_map[i].push_back(a_map[i][cur]);
        }else{
            a_map[i].push_back(-1);
        }
        newrow.push_back(-1);
    }
    newrow.push_back(-1);
    a_map.push_back(newrow);
    return s++;
}

int KSP(int n, int start, int end, unsigned int k, vector< stack<int> >& kpaths, vector<double>& re_dist){
    vector<int> dup(n,-1);//inode 的duplicate node是哪个
    vector<int> orig(n,-1);//inode 的original node是哪个
    for(int i=0;i<n;i++){
        orig[i]=i;
    }
    vector<int> Path = dijkstra(n,start);//get the shortest path1;
    if(Path[end]==-1) {
        cout<<"no sp."<<endl;
        return 0;//no sp
    }


    re_dist.push_back(dis[end]);

    stack<int> curPath;
    int temp=end;
    while(temp!=-1){
        curPath.push(temp);
        temp=Path[temp];
    }

    kpaths.push_back(curPath);

    //find the 2nd shortest p
    int ki=1;
    while(ki<k){
        //find 1st node with in_arc_num>1
        unsigned curNode=0;
        while(!curPath.empty()){
            int node=curPath.top();
            curPath.pop();
            if(inarc[node]>1){
                curNode = node;
                break;
            }
        }
        if(!curNode){
            cout<<end<<" has no multi-connnected node;"<<endl;
            break;//no alternative path;
        }

        unsigned next_node = 0;
        if(dup[curNode]<0){
            unsigned dup_pos=addNode(curNode, Path[curNode]);

            //compute min-dist form 0 to new_size
            double min_dist=(unsigned) INFINITY;
            int min_node=-1;
            for(int i=0;i<dup_pos-1;i++){
                if(dis[i]+a_map[i][dup_pos]<min_dist){
                    min_dist = dis[i]+a_map[i][dup_pos];
                    min_node = i;
                }
            }
            dis.push_back(min_dist);
            Path.push_back(min_node);
            dup.push_back(-1);
            dup[curNode]=dup_pos;

            int temp=curNode;
            while(temp != orig[temp])
                temp=orig[temp];
            orig.push_back(temp);

            if(!curPath.empty()){
                next_node=curPath.top();
                curPath.pop();
            }
        }else{
            while(curPath.size()){
                next_node=curPath.top();
                curPath.pop();
                if(dup[next_node]<0) break;
            }
        }

        //add other candidate node to duplicate nodes
        while(next_node){
            unsigned pre_next=Path[next_node];
            unsigned dup_pos=addNode(next_node,pre_next);
            if(dup[pre_next]>=0){
                a_map[pre_next][dup_pos] = a_map[pre_next][next_node];//add arc(ni-1,ni)
            }

            double min_dist=(unsigned) INFINITY;
            int min_node=-1;
            for(int i=0;i<dup_pos-1;i++){
                if(dis[i]+a_map[i][dup_pos]<min_dist){
                    min_dist = dis[i]+a_map[i][dup_pos];
                    min_node = i;
                }
            }
            dis.push_back(min_dist);
            Path.push_back(min_node);
            dup.push_back(-1);
            dup[next_node]=dup_pos;

            int temp=next_node;
            while(temp != orig[temp])
                temp=orig[temp];
            orig.push_back(temp);

            if(!curPath.empty()){
                next_node=curPath.top();
                curPath.pop();
            }
        }

        //get the k-th shortest path
        if(!next_node) next_node = curNode;
        stack<int> new_path;
        int length=0;
        int incide_node=dup[next_node];
        while(incide_node >= 0){
            curPath.push(incide_node);
            new_path.push(orig[incide_node]);
            incide_node=Path[incide_node];
        }
        if(new_path.size() < 2){
            cout<<"no new shortest path;"<<endl;
            break;
        }
        kpaths.push_back(new_path);
        ki++;
    }
    return ki;

}



int main()
{
    clock_t time_start=clock();
    int start = 0;
    int end = 107;
    int k=5;
    //读数据
    int n=0;
    // memset(a_map,88,sizeof(a_map));
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
        inarc[data[1]]++;
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

    // vector<int> dis=dijkstra(n,0);//以0为源点。
    // clock_t time_end=clock();
    // cout<<"dij time use:"<<1000*(time_end-time_start)/(double)CLOCKS_PER_SEC<<"ms"<<endl;

    vector< stack<int> > kpaths;
    vector<double> re_dist;
    int path_num=KSP(n,start,end,k,kpaths,re_dist);
    clock_t time_end2=clock();
    cout<<"ksp time use:"<<1000*(time_end2-time_start)/(double)CLOCKS_PER_SEC<<"ms"<<endl;

    ofstream outfile;
    outfile.open("/Users/01384573/Documents/Mycodes/leet_git/myowncodes/KSP/output_ksp.txt");
    outfile<<"time use:"<<1000*(time_end2-time_start)/(double)CLOCKS_PER_SEC<<"ms\n";
    outfile<<"start node and end node are: "<<start<<" "<<end<<".\n";
    for(int i=0;i<=n;i++){
        if(dis[i]==maxn){
            cout<<i<<" has no solution\n";
            outfile<<i<<" has no solution\n";
            continue;
        }
        cout<<i<<"->"<<dis[i]<<"\n";
        // outfile<<"node "<<i<<": pre-node->"<<path[i]<<" shortest-path->"<<dis[i]<<"\n";
        outfile<<"node "<<i<<" shortest-path->"<<dis[i]<<"\n";
    }
    for(int i=0;i<kpaths.size();i++){
        string s="";
        while(!kpaths[i].empty()){
            int m=kpaths[i].top();
            kpaths[i].pop();
            outfile<<m<<" ";
        }
        outfile<<"\n";
    }
    outfile.close();
}
