




332. Reconstruct Itinerary
Solved
Hard
Topics
premium lock icon
Companies
You are given a list of airline tickets where tickets[i] = [fromi, toi] represent the departure and the arrival airports of one flight. Reconstruct the itinerary in order and return it.

All of the tickets belong to a man who departs from "JFK", thus, the itinerary must begin with "JFK". If there are multiple valid itineraries, you should return the itinerary that has the smallest lexical order when read as a single string.

For example, the itinerary ["JFK", "LGA"] has a smaller lexical order than ["JFK", "LGB"].
You may assume all tickets form at least one valid itinerary. You must use all the tickets once and only once.

 

Example 1:


Input: tickets = [["MUC","LHR"],["JFK","MUC"],["SFO","SJC"],["LHR","SFO"]]
Output: ["JFK","MUC","LHR","SFO","SJC"]
Example 2:


Input: tickets = [["JFK","SFO"],["JFK","ATL"],["SFO","ATL"],["ATL","JFK"],["ATL","SFO"]]
Output: ["JFK","ATL","JFK","SFO","ATL","SFO"]
Explanation: Another possible reconstruction is ["JFK","SFO","ATL","JFK","ATL","SFO"] but it is larger in lexical order.



class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        //how I get to know it is a question of euler??=>first we have use ALL tickets EXACTLY ONCE and
        //we have to START from PARTICULAR STARTNODE and NODES are like (FROM one to ANOTHER NODE like an EDGE)
        unordered_map<string,vector<string>>adj;
        unordered_map<string,int>indegree,outdegree;
        for (auto &it :tickets){
            string u=it[0];
            string v=it[1];
            adj[u].push_back(v);
            indegree[v]++;
            outdegree[u]++;
        }

        for (auto &[ke,temp]: adj){
            sort(temp.rbegin(),temp.rend());//as we want lexically smaller and we take nneighbour from end first 
            //so we want small neighbour at the end
        }

        string startNode="JFK";
        //dfs call
        stack<string>st;
        vector<string>path;
        st.push(startNode);
        while(!st.empty()){
            string cur=st.top();
            if(adj[cur].size()>0){//it has ngb
                string ngb=adj[cur].back();
                st.push(ngb);
                adj[cur].pop_back();

            }else{
                path.push_back(st.top());
                st.pop();
            }
        }
        reverse(path.begin(),path.end());
        return path;
        
    }
};


2097. Valid Arrangement of Pairs
Solved
Hard
Topics
premium lock icon
Companies
Hint
You are given a 0-indexed 2D integer array pairs where pairs[i] = [starti, endi]. An arrangement of pairs is valid if for every index i where 1 <= i < pairs.length, we have endi-1 == starti.

Return any valid arrangement of pairs.

Note: The inputs will be generated such that there exists a valid arrangement of pairs.

 

Example 1:

Input: pairs = [[5,1],[4,5],[11,9],[9,4]]
Output: [[11,9],[9,4],[4,5],[5,1]]
Explanation:
This is a valid arrangement since endi-1 always equals starti.
end0 = 9 == 9 = start1 
end1 = 4 == 4 = start2
end2 = 5 == 5 = start3
Example 2:

Input: pairs = [[1,3],[3,2],[2,1]]
Output: [[1,3],[3,2],[2,1]]
Explanation:
This is a valid arrangement since endi-1 always equals starti.
end0 = 3 == 3 = start1
end1 = 2 == 2 = start2
The arrangements [[2,1],[1,3],[3,2]] and [[3,2],[2,1],[1,3]] are also valid.


class Solution {
public:
    vector<vector<int>> validArrangement(vector<vector<int>>& pairs) {
        //you have to visit all the pairs or edges and that will be possible when u start from certain node=>euler path
        unordered_map<int,int>indegree,outdegree;
        unordered_map<int,vector<int>>adj;       
        for (auto & it :pairs){
            int u=it[0];
            int v=it[1];
            adj[u].push_back(v);
            indegree[v]++;
            outdegree[u]++;
        }

        int startNode=pairs[0][0];//remember initialize the startNode with any one of the nodes otherwise wrong
        //as when there exist eulerian circuit then it would not be overriden
        for (auto &it :adj){
            int node=it.first;
            if(outdegree[node]-indegree[node]==1){
                startNode=node;
                break;
            }

        }
        //cout<<startNode;
        //start dfs from startNode to find the euler path
        stack <int>st;
        vector<int>path;
        st.push(startNode);
        while(!st.empty()){
            int curr=st.top();
            if(adj[curr].size()>0){
                int ngb=adj[curr].back();
                st.push(ngb);
                adj[curr].pop_back();
            }else{
                path.push_back(st.top());
                st.pop();
            }
        }
        reverse(path.begin(),path.end());
        vector<vector<int>>res;
        for (int i=0;i<path.size()-1;i++){
            res.push_back({path[i],path[i+1]});
        }
        return res;
    }
};

