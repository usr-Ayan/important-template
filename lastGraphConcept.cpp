cycle detection in undirected graph

class Solution {
  public:
  bool Dfs(int node,int parent,vector<vector<int>>& adj,vector<int>&visited){
      visited[node]=1;
      for (auto it : adj[node]){
        if(it==parent)continue;
        if(visited[it])return true;
        if(Dfs(it,node,adj,visited))return true;
      }
      return false;
      
  }
    bool isCycle(int V, vector<vector<int>>& edges) {
        // Code here
        //call dfs from a node it will go to depth and if it is able to find a node that is
        //visited already but it is not the node from which it just came from then cycle exist
        vector<int>visited(V,0);
        vector<vector<int>>adj(V);
        for (int i=0;i<edges.size();i++){
            int u=edges[i][0];
            int v=edges[i][1];
            adj[u].push_back(v);
            adj[v].push_back(u);
            
            
        }
        
        for(int i=0;i<V;i++){
            if(!visited[i]){
                if(Dfs(i,-1,adj,visited))return true;
            }
        
        }
        return false;
    }
};

// using bfs
  bool BFS(int node,vector<vector<int>>& adj,vector<int>&visited){
      queue<pair<int,int>>q;
      q.push({node,-1});
      visited[node]=1;
      while(!q.empty()){
          int node=q.front().first;
          int parent=q.front().second;
          q.pop();
          for (auto it : adj[node]){
              if(!visited[it]){
                  visited[it]=1;
                  q.push({it,node});
              }else{
                  if(it==parent)continue;//if the person I am trying to visit already visited but not my parent=>cycle
                  else{
                      return true;
                  }
                  
              }
          }
      }
      return false;
  }
    bool isCycle(int V, vector<vector<int>>& edges) {
        
        vector<int>visited(V,0);
        vector<vector<int>>adj(V);
        for (int i=0;i<edges.size();i++){
            int u=edges[i][0];
            int v=edges[i][1];
            adj[u].push_back(v);
            adj[v].push_back(u);
            
            
        }
        
        for(int i=0;i<V;i++){
            if(!visited[i]){
                if(BFS(i,adj,visited))return true;
            }
        
        }
        return false;
    }


    // cycle detection in directed graph

    // DFS Solution

  class Solution {
  public:
  bool dfs(int node,vector<int>&visited,vector<int>&inRecursion,vector<vector<int>>&adj){
      visited[node]=true;
      inRecursion[node]=true;
      for(auto it : adj[node]){
          if(visited[it] && inRecursion[it])return true;
          if(dfs(it,visited,inRecursion,adj))return true;
          
      }
      inRecursion[node]=false;//bcz we might still visit this node but from another path
      //so if we do not do this we will conclude that cycle exist where as it is actually a different path
      //that is reaching this node
      return false;
  }
    bool isCyclic(int v, vector<vector<int>> &edges) {
        //here to detect a cycle we need to know if we are visiting a node
        //that is already visited we have to know if it is part of the recursion or not 
        //when we go back from that we remove that node from recursion (if any node visited and still part of recursion
        //that means cycle exist)
        vector<vector<int>>adj(v);
        for (auto it : edges){
            int u=it[0];
            int v=it[1];
            adj[u].push_back(v);
        }
        
        // bool ans=false;
        vector<int>visited(v,0);
        vector<int>inRecursion(v,0);
        for (int i=0;i<v;i++){
            if(!visited[i]){
               if(dfs(i,visited,inRecursion,adj))return true;
            }
        }
        return false;
    }
};

// cycle detection in directed graph

    // BFS solution
Topological Sort – Definition:
Topological Sort (or Topological Ordering) of a Directed Acyclic Graph (DAG) is a linear 
ordering of its vertices such that for every directed edge u → v, vertex u comes before vertex v in the ordering.


if cycle is possible then there is no topsort possible =>we are not able to push all the node in queue so cnt<no of nodes
    bool isCyclic(int V, vector<vector<int>> &edges) {
    
        vector<int>indegree(V,0);
        for (int i=0;i<edges.size();i++){
            int u=edges[i][0];
            int v=edges[i][1];
            indegree[v]++;
        }
        vector<vector<int>>adj(V);
        for (auto it : edges){
            int u=it[0];
            int v=it[1];
            adj[u].push_back(v);
        }
       // vector<int>visited(v,0);;
         int cnt=0;
        queue<int>q;
        for (int i=0;i<V;i++){
            if(indegree[i]==0){
                q.push(i);
                //visited[i]=1;
                cnt++;
            }
        }
       
        while(!q.empty()){
            int node=q.front();
            //cnt++;
            q.pop();
            
            for (auto it : adj[node]){
                indegree[it]--;
                if(indegree[it]==0){
                    cnt++;
                    q.push(it);
                }
            }
            
        }
        
        if(cnt==V)return false;//no cycle
        return true;
    }
};

//eg how the neighbour visiting is done in dfs and bfs when graph is represented as adjacency matrix
class Solution {
public:
    void BFS(int start,vector<int>&visited,vector<vector<int>>& isConnected){
        
        queue<int>q;
        q.push(start);
        visited[start]=1;
        while(!q.empty()){
            int node=q.front();
            q.pop();
            //find adjacent 
            for (int j=0;j<isConnected.size();j++){//same way you can do dfs
                if(isConnected[node][j] && !visited[j]){//checking for every node i if there is j in the col that is its adj
                    visited[j]=1;
                    q.push(j);
                }
            }
        }
    }
    int findCircleNum(vector<vector<int>>& isConnected) {
        int cnt=0;
        int n=isConnected.size();
        // vector<vector<int>>adj(n);
        // for (int i=0;i<n;i++){
        //     for (int j=0;j<n;j++){
        //         if(isConnected[i][j]==1){
        //             adj[i].push_back(j);
        //             adj[j].push_back(i);
        //         }
        //     }
        // }

        vector<int>visited(n,0);
        for (int i=0;i<n;i++){//calling at all nodes i
            if(!visited[i]){
                cnt++;
                BFS(i,visited,isConnected);
            }
        }
        return cnt;
        
    }
};

//if a graph bipartite
bipartite graph=>if we color the graph with just two color and no adjacent element is of same color then graph is bipartite.
=>(and any graph with odd cycle will not be bipartite otherwise it is bipartite)

How do you know if question is from bipartite graph??
=>if we have to divide question in two halves and then do something on them then it is bipartite graph question.


class Solution {
public:

    bool BFS(int start,vector<vector<int>>&graph,vector<int>&visited){
        unordered_map<int,bool>mp;
        queue<pair<int,int>>q;
        bool color=true;
        q.push({start,color});
        mp[start]=color;
        visited[start]=1;
        while(!q.empty()){
            int node=q.front().first;
            bool nodeColor=q.front().second;
            q.pop();

            //main logic is ask every node if there adjacent having different color or not 
            //go to every node ask if all its adjacent are visited or not =>if not visit and assign a color that is opposite
            //to this 
            //and if node is visited that means someone already assigned node a color ,so find out if that color same as 
            //current node color then you cannot give all adjacent node  diff color return false not bipartite else go on
            //finally return true if nobody returns false
            for (auto it : graph[node]){
                if(!visited[it]){
                    visited[it]=1;
                    mp[it]=!nodeColor;
                    q.push({it,!nodeColor});
                }
                else{
                    if(mp[it]==nodeColor)return false;
                }
            }
        }
        return true;

    }
    bool isBipartite(vector<vector<int>>& graph) {
        int n=graph.size();
        vector<int>visited(n,0);
        //bool color=true;
        for (int i=0;i<n;i++){
            if(!visited[i]){
                if(BFS(i,graph,visited)==false)return false;
            }
        }
        return true;

        
    }
};
