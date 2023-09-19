#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#define  MAX 99999
using namespace std;
unsigned int nodes;
class node{//node的資料與型態
    public:
    unsigned int ID;//node id
    int sdn_type;//是否為sdn 是：1 否：0
    int *neighbor;//node有聯通的鄰居為1否則為0
    map<unsigned int, vector<pair<unsigned int, double> > > mymap;//destination作為key value 對應要傳送的節點與分配％數（double）
    void initial(unsigned int,int **,int);//初始node函數
};
class req{//request
    public:
    unsigned int src;//起始點
    unsigned int dst;//終點
    unsigned int flow;//flow 數量
};
class dst{//destination
    public:
    unsigned int dst_id;//destination id
    int *parent;//經由shortest_path函數獲得各點到destination的父節點
    int *dis;//經由shortest_path函數獲得各點到destination的距離
    void initial(unsigned int);//初始destination函數
};
bool REQcompare(req, req);//將request的destination為基準升序排
bool DSTcompare(dst, dst);//將destination id為基準升序排
void shortest_path(int tag, vector<dst>& dsts,int **G);//dijkstra algorithm
int main(){
    unsigned int sdn_nodes,dst_num,links,pairs,tmp,tmp_i,tmp_j;
    cin>>nodes>>sdn_nodes>>dst_num>>links>>pairs;
    node *node_list=new node[nodes];
    vector<dst> dsts;
    dsts.reserve(dst_num);
    req *reqs=new req[pairs];
    int **G=new int*[nodes];//graph G :Adjacency Matrix
    for(int count=0;count<nodes;count++){
        G[count]=new int[nodes];
        node_list[count].sdn_type=0;
    }
    for(int count=0;count<sdn_nodes;count++){//input
        cin>>tmp;
        node_list[tmp].sdn_type=1;
    }
    for(int count=0;count<dst_num;count++){//input
        cin>>dsts[count].dst_id;
        dsts[count].initial(nodes);
    }
    sort(dsts.begin(),dsts.end(),DSTcompare);//升序排列dsts(以id為基準)
    for(int count=0;count<links;count++){//input
        cin>>tmp>>tmp_i>>tmp_j;
        G[tmp_i][tmp_j]=1;
        G[tmp_j][tmp_i]=1;
    }
    for(int count=0;count<pairs;count++){//input
        cin>>tmp>>reqs[count].src>>reqs[count].dst>>reqs[count].flow;
    }
    sort(reqs, reqs+pairs, REQcompare);//升序排列reqs(以dst為基準)
    for(int count=0;count<nodes;count++)node_list[count].initial(nodes,G,count);//初始化node_list中所有node
    for(int count=0;count<dst_num;count++){
        shortest_path(count, dsts, G);//獲得目前destination的shortest path tree
        int *flow=new int[nodes];
        for(int i=0;i<pairs;i++){//需要傳送到目前destination的flow計算匯流則累加,以shortest path tree為路徑
            if(reqs[i].dst==dsts[count].dst_id){
                for(int start=reqs[i].src;start!=reqs[i].dst;){
                    flow[start]+=reqs[i].flow;
                    start=dsts[count].parent[start];
                }
            }
        }
        for(int i=0;i<nodes;i++){
            if(node_list[i].sdn_type==1 && node_list[i].neighbor[dsts[count].dst_id]!=1){//sdn type node 且paraent並不是destination
                vector<int> path;
                int counter=1;//計算可傳送路徑總數
                path.push_back(dsts[count].parent[i]);//將paraent放入可傳送路徑中
                for(int j=0;j<nodes;j++){
                    if(node_list[i].neighbor[j]!=0 && dsts[count].parent[j]!=node_list[i].ID && j!=path[0] && dsts[count].dis[j]<=dsts[count].dis[i]+2 && node_list[j].sdn_type!=1){//sdn type node的鄰居且其paraent不是自己且到destination的路經長為本身的+2之內且不是sdn type
                        counter++;
                        path.push_back(j);//放入可傳送路徑中
                    }
                }
                if(counter==2 && flow[path[1]]==0){//根據數量與flow大小分配
                    node_list[i].mymap[dsts[count].dst_id].push_back(make_pair(path[0], 0.5));
                    node_list[i].mymap[dsts[count].dst_id].push_back(make_pair(path[1], 0.5));
                }
                if(counter==2 && flow[path[1]]>0){
                    node_list[i].mymap[dsts[count].dst_id].push_back(make_pair(path[0], 0.7));
                    node_list[i].mymap[dsts[count].dst_id].push_back(make_pair(path[1], 0.3));
                }
                if(counter==3){//50 25 25 / 50 30 20
                    node_list[i].mymap[dsts[count].dst_id].push_back(make_pair(path[0], 0.5));
                    if(flow[path[1]]==flow[path[2]]){
                        node_list[i].mymap[dsts[count].dst_id].push_back(make_pair(path[1], 0.25));
                        node_list[i].mymap[dsts[count].dst_id].push_back(make_pair(path[2], 0.25));
                    }
                    if(flow[path[1]]>flow[path[2]]){
                        node_list[i].mymap[dsts[count].dst_id].push_back(make_pair(path[1], 0.3));
                        node_list[i].mymap[dsts[count].dst_id].push_back(make_pair(path[2], 0.2));
                    }
                    if(flow[path[1]]<flow[path[2]]){
                        node_list[i].mymap[dsts[count].dst_id].push_back(make_pair(path[1], 0.2));
                        node_list[i].mymap[dsts[count].dst_id].push_back(make_pair(path[2], 0.3));
                    }
                }
                if(counter==4){//50 30 10 10
                    node_list[i].mymap[dsts[count].dst_id].push_back(make_pair(path[0], 0.5));
                        int minflow=flow[path[1]],min=1;
                        for(int k=2;k<4;k++)if(flow[path[k]]<minflow){minflow=flow[path[k]];min=k;}
                        node_list[i].mymap[dsts[count].dst_id].push_back(make_pair(path[min], 0.3));
                        tmp=1;
                        while(tmp<4){
                            if(tmp!=min)node_list[i].mymap[dsts[count].dst_id].push_back(make_pair(path[tmp], 0.1));
                            tmp++;
                        }
                    }
                if(counter==5){//50 20 10 10 10
                    node_list[i].mymap[dsts[count].dst_id].push_back(make_pair(path[0], 0.5));
                    int minflow=flow[path[1]],min=1;
                    for(int k=2;k<5;k++)if(flow[path[k]]<minflow){minflow=flow[path[k]];min=k;}
                    node_list[i].mymap[dsts[count].dst_id].push_back(make_pair(path[min], 0.2));
                    tmp=1;
                    while(tmp<5){
                        if(tmp!=min)node_list[i].mymap[dsts[count].dst_id].push_back(make_pair(path[tmp], 0.1));
                        tmp++;
                    }
                }
                if(counter>=6){//average
                    node_list[i].mymap[dsts[count].dst_id].push_back(make_pair(path[0], 0.5));
                    double flow_percent=(0.5)/((double)counter-1.0);
                    for(tmp=1;tmp<counter;tmp++)
                        node_list[i].mymap[dsts[count].dst_id].push_back(make_pair(path[tmp], flow_percent));
                }
                if(counter==1)node_list[i].mymap[dsts[count].dst_id].push_back(make_pair(dsts[count].parent[i], 1.0));
            }//非sdn 依據shortest path tree為路徑
            else node_list[i].mymap[dsts[count].dst_id].push_back(make_pair(dsts[count].parent[i], 1.0));
        }
        delete []flow;
    }
    for(int i=0;i<nodes;i++){//output
        cout<<node_list[i].ID<<endl;
        for(auto iter=node_list[i].mymap.begin();iter!=node_list[i].mymap.end();iter++){
            if(node_list[i].sdn_type==1){
                cout<<iter->first<<" ";
                auto end=iter->second.size();
                for(int st=0;st!=end;st++)cout<<iter->second[st].first<<" "<<iter->second[st].second*100.0<<"% ";
                cout<<endl;
            }
            else cout<<iter->first<<" "<<iter->second[0].first<<endl;
        }
    }
    return 0;
}
void node::initial(unsigned int nodes,int **G,int count){//初始化將ID填入編號藉由graph G填入此node的鄰居
    ID=count;
    neighbor=new int[nodes];
    for(int count=0;count<nodes;count++){
        if(G[ID][count]>0)neighbor[count]=1;
    }
}
void dst::initial(unsigned int nodes){
    parent=new int[nodes];
    dis=new int[nodes];
    for(int count=0;count<nodes;count++)parent[count]=-1;
}
bool REQcompare(req in1, req in2){//request compare function
    return in1.dst<in2.dst;
}
bool DSTcompare(dst in1, dst in2){//destination compare function
    return in1.dst_id<in2.dst_id;
}
void shortest_path(int tag, vector<dst>& dsts, int **G){//dijkstra algorithm
    bool visit[nodes];//記錄各個點是否在路徑當中
    for(int count=0;count<nodes;count++){//初始化
        visit[count]=false;
        dsts[tag].dis[count]=MAX;
    }
    dsts[tag].dis[dsts[tag].dst_id]=0;
    dsts[tag].parent[dsts[tag].dst_id]=dsts[tag].dst_id;//起始點設定
    for(int C=0;C<nodes;C++){
        int temp_a=-1, min=MAX;
        for(int i=0;i<nodes;i++){
            if(!visit[i] && dsts[tag].dis[i]<min){
                temp_a=i;
                min=dsts[tag].dis[i];
            }
        }
        if(temp_a==-1)break;//起始點所連通的路徑都已找完則跳出
        visit[temp_a]=true;
        for(int temp_b=0;temp_b<nodes;temp_b++){//尋求較短度路徑並且加入路徑
            if(G[temp_a][temp_b]!=0 && G[temp_b][temp_a]!=0 && !visit[temp_b] && dsts[tag].dis[temp_a]+G[temp_a][temp_b] < dsts[tag].dis[temp_b]){
                dsts[tag].dis[temp_b]=dsts[tag].dis[temp_a]+G[temp_a][temp_b];
                dsts[tag].parent[temp_b]=temp_a;
            }
        }
    }
}
