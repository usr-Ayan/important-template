873. Length of Longest Fibonacci Subsequence
Solved
Medium
Topics
Companies
Hint
A sequence x1, x2, ..., xn is Fibonacci-like if:

n >= 3
xi + xi+1 == xi+2 for all i + 2 <= n
Given a strictly increasing array arr of positive integers forming a sequence, return the length of the longest Fibonacci-like subsequence of arr. If one does not exist, return 0.

A subsequence is derived from another sequence arr by deleting any number of elements (including none) from arr, without changing the order of the remaining elements. For example, [3, 5, 8] is a subsequence of [3, 4, 5, 6, 7, 8].

 






class Solution {
public:
    int solve(int j,int i,vector<int>&arr,unordered_map<int,int>&mp,auto &dp){
        if(dp[i][j]!=-1)return dp[i][j];
        int target=arr[i]-arr[j];
        if(mp.count(target) && mp[target]<j){
            int index=mp[target];
            return dp[i][j]=1+solve(index,j,arr,mp,dp);
        }
        return dp[i][j]=2;
    }
    int lenLongestFibSubseq(vector<int>& arr) {
        int n=arr.size();
        unordered_map<int,int>mp;
        for (int i=0;i<n;i++){
            mp[arr[i]]=i;
        }

        vector<vector<int>>dp(n,vector<int>(n,-1));

        int maxLen=0;
        for (int i=1;i<n;i++){
            for (int j=0;j<i;j++){
               int len =solve(j,i,arr,mp,dp);
               if(len>=3){
                maxLen=max(maxLen,len);
               }
            }
        }
        return maxLen;
        
        
    }
};



//tabuled version of the same code 
int lenLongestFibSubseq(vector<int>& arr) {
        int n=arr.size();
        unordered_map<int,int>mp;
        for (int i=0;i<n;i++){
            mp[arr[i]]=i;
        }

        vector<vector<int>>dp(n,vector<int>(n,2));

        int maxLen=0;
        for (int i=1;i<n;i++){
            for (int j=0;j<i;j++){
                int target=arr[i]-arr[j];
                if (mp.count(target) && mp[target]<j){
                    int index=mp[target];
                    dp[i][j]=1+dp[j][index];
                }
                maxLen=max(maxLen,dp[i][j]);
                
            }
            
        }
        return maxLen>=3?maxLen:0;
        
        
    }
};


//largest divisible subset


class Solution {
public:
    vector<int> largestDivisibleSubset(vector<int>& arr) {
        int n=arr.size();
        sort(arr.begin(),arr.end());
        vector<int>dp(n,1);
        vector<int>hash(n,0);
        int maxi=1;
        for (int i=0;i<n;i++)hash[i]=i;
        int last=0;
        for (int i=0;i<n;i++){
            for (int j=0;j<i;j++){
                if(arr[i]%arr[j]==0 && dp[j]+1>dp[i]){
                    dp[i]=1+dp[j];
                    hash[i]=j;
                }

            }
            if(maxi<dp[i]){
                maxi=dp[i]
;                last=i;
            }
        }
        vector<int>temp;
        temp.push_back(arr[last]);
        while(hash[last]!=last){
            last=hash[last];
            temp.push_back(arr[last]);
        }
        reverse(temp.begin(),temp.end());
        return temp;

        
    }
};


673. Number of Longest Increasing Subsequence
Solved
Medium
Topics
premium lock icon
Companies
Given an integer array nums, return the number of longest increasing subsequences.

Notice that the sequence has to be strictly increasing.

class Solution {
public:
    int findNumberOfLIS(vector<int>& arr) {
        int n=arr.size();int maxi=1;
        vector<int>dp(n,1);
        vector<int>cnt(n,1);
        for(int i=0;i<n;i++){
            for (int j=0;j<i;j++){
                if(arr[i]>arr[j] && dp[j]+1>dp[i]){
                    dp[i]=1+dp[j];
                    cnt[i]=cnt[j];
                    
                }
                else if(arr[i]>arr[j] && dp[j]+1==dp[i]){
                    cnt[i]=cnt[i]+cnt[j];
                }
            }
            maxi=max(maxi,dp[i]);
        }
        int count=0;
        for (int i=0;i<n;i++){
            if(dp[i]==maxi){
                count+=cnt[i];
            }
        }
        return count;

    }
};


finding the longest increasing sequence length in O(nlogn) time complexity 
problem is we cannot find the actual lis only the length

int lis(vector<int>nums){
    vector<int>res;
    for (auto it : nums){
        auto itr= lower_bound(res.begin(),res.end(),it);
        if(itr==res.end()){
            res.push_back(it);
        }
        else{
            *itr=it;
        }
    }
    return res.size();
}




tabulation to o(n)convertion using prefix sum of dp

class Solution {
public:
const int MOD=1e9+7;

    int countPartitions(vector<int>& nums, int k) {
        int n=nums.size();

        vector<int>dp(n+1,0);
        dp[0]=1;
        // for (int i=1;i<=n;i++){
        //     int maxi=0;int mini=1e9;
        //     for (int j=i;j>=1;j--){
        //         maxi=max(maxi,nums[j-1]);
        //         mini=min(mini,nums[j-1]);
        //         if(maxi-mini<=k){
        //             dp[i]=(dp[i]%MOD+dp[j-1]%MOD)%MOD;
        //         }
        //         else{
        //             break;
        //         }

        //     }
        // }
        // return dp[n];
        vector<int>prefDp(n+2,0);
        prefDp[1]=1;
        deque<int>maxq,minq;
        int i=1;
        for (int j=1;j<=n;j++){
            int val=nums[j-1];

            //maintaining maxi and mini beforehand as we are not going to traverse and find them
            while(!maxq.empty() && val>maxq.back()){
                maxq.pop_back();
            }
            maxq.push_back(val);

            while(!minq.empty() && val<minq.back()){
                minq.pop_back();
            }
            minq.push_back(val);

            //making sure from j we are going back upto those point such that window is valid not more than that
            //i.e max window size for that i
            while(!maxq.empty() && !minq.empty() && maxq.front()-minq.front()>k){
                if(maxq.front()==nums[i-1])maxq.pop_front();
                if(minq.front()==nums[i-1])minq.pop_front();
                i++;
            }
            dp[j]=(prefDp[j]-prefDp[i-1]+MOD)%MOD;
            prefDp[j+1]=(prefDp[j]+dp[j])%MOD;

        }
        return dp[n];

        
        
    }
};



1425. Constrained Subsequence Sum
Solved
Hard
Topics
premium lock icon
Companies
Hint
Given an integer array nums and an integer k, return the maximum sum of a non-empty subsequence of that array such that for every two consecutive integers in the subsequence, nums[i] and nums[j], where i < j, the condition j - i <= k is satisfied.

A subsequence of an array is obtained by deleting some number of elements (can be zero) from the array, leaving the remaining elements in their original order.

 

Example 1:

Input: nums = [10,2,-10,5,20], k = 2
Output: 37
Explanation: The subsequence is [10, 2, 5, 20].
Example 2:

Input: nums = [-1,-2,-3], k = 1
Output: -1
Explanation: The subsequence must be non-empty, so we choose the largest number.
Example 3:

Input: nums = [10,-2,-10,-5,20], k = 2
Output: 23
Explanation: The subsequence is [10, -2, -5, 20].


class Solution {
public:
    int constrainedSubsetSum(vector<int>& nums, int k) {
        int n=nums.size();
        vector<int>dp(n,0);
       for (int i=0;i<n;i++){
        dp[i]=nums[i];
       }
       
       int maxi=-1e5;
       deque<int>q;
       int i=0;
        for (int j=0;j<n;j++){
            //before calculating dp[j] make sure your q holding data of window<=k
            while((j-i)>k){
                i++;
                if(i>q.front())q.pop_front();
            }
            //find max element in the window of size <=k just before i 
            if(q.empty()|| dp[q.front()]<0){
                dp[j]=0+nums[j];
            }else{
                dp[j]=dp[q.front()]+nums[j];
            }
            maxi=max(maxi,dp[j]);

            while(!q.empty() && dp[j]>dp[q.back()]){//this is not in the top bcz if we would have pushed j
                q.pop_back();//before calculating dp of j then in max calculation we would have taken current index's value 
                //which we do not ewant
            }
            q.push_back(j);

        }
        return maxi;
    }
};