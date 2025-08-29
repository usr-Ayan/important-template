#include<bits/stdc++.h>
using namespace std;


Travelling Salesman Problem
Difficulty: HardAccuracy: 46.35%Submissions: 28K+Points: 8Average Time: 25m
Given a matrix cost of size n where cost[i][j] denotes the cost of moving from city i to city j. Your task is to complete a tour from city 0 (0-based index) to all other cities such that you visit each city exactly once and then at the end come back to city 0 at minimum cost.

Examples:

Input: cost = [[0, 111], [112, 0]]
Output: 223
Explanation: We can visit 0->1->0 and cost = 111 + 112.
Input: cost = [[0, 1000, 5000], [5000, 0, 1000], [1000, 5000, 0]]
Output: 3000
Explanation: We can visit 0->1->2->0 and cost = 1000+1000+1000 = 3000


//Brute force method

class Solution {
  public:
  int solve(int city,vector<vector<int>>&cost,int cnt,vector<int>&visited){
    if(cnt==cost.size())return cost[city][0];
    int ans=1e9;
    //where should I go from this city optimay that is to be chosen
    for (int i=0;i<cost.size();i++){
        if(!visited[i]){
            visited[i]=1;
            ans=min(ans,cost[city][i]+solve(i,cost,cnt+1,visited));
            visited[i]=0;
        }
    }
    return ans;
  }
  
    int tsp(vector<vector<int>>& cost) {
        int n=cost.size();
        vector<int>visited(n,0);
        visited[0]=1;
        return solve(0,cost,1,visited);
   
    }
};


class Solution {
  public:
  int solve(int city,int bitmask,int &n,vector<vector<int>>&cost,vector<vector<int>>&dp){
    if(bitmask==(1<<n)-1)return cost[city][0];//it means all the bit from 0 to n-1 is set i.e all cities
    //are visited so go back to 0 th city by cost[city][0] as in any other way if u try u end up visiting city twice
    if(dp[city][bitmask]!=-1)return dp[city][bitmask];
    int ans=1e9;
    //where should I go from this city optimay that is to be chosen
    for (int i=0;i<cost.size();i++){
        if((bitmask &(1<<i))==0){
            ans=min(ans,cost[city][i]+solve(i,bitmask|(1<<i),n,cost,dp));
           
        }
    }
    return dp[city][bitmask]=ans;
  }
  
    int tsp(vector<vector<int>>& cost) {
        int n=cost.size();
        vector<vector<int>>dp(n,vector<int>((1<<n),-1));
        return solve(0,1,n,cost,dp);//bitmask 1 bcz the city 0 is visited so 0th bit should be set
   
    }
};