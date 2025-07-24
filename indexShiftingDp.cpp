3578. Count Partitions With Max-Min Difference at Most K
Attempted
Medium
Topics
premium lock icon
Companies
Hint
You are given an integer array nums and an integer k. Your task is to partition nums into one or more non-empty contiguous segments such that in each segment, the difference between its maximum and minimum elements is at most k.

Return the total number of ways to partition nums under this condition.

Since the answer may be too large, return it modulo 109 + 7.






this is not about the question infact this solution will not pass just to show how index shifting work


class Solution {
public:
const int MOD=1e9+7;
int dp[50001];
int solve(int idx,vector<int>&nums,int &k){
    if(idx==-1)return 1;
    if(dp[idx]!=-1)return dp[idx];
    int ans=0;
    int maxi=0;int mini=1e9;
    for (int i=idx;i>=0;i--){
        maxi=max(maxi,nums[i]);
        mini=min(mini,nums[i]);
        long long diff=maxi-mini;
        if(diff<=k){
            ans=(ans+solve(i-1,nums,k)%MOD)%MOD;
        }
        else{
            break;
        }
    }
    return dp[idx]=ans;

}
    int countPartitions(vector<int>& nums, int k) {
        //memset(dp,-1,sizeof(dp));
        int n=nums.size();
        //return solve(n-1,nums,k);

        vector<int>dp(n+1,0);
        dp[0]=1;              BASE CASE
        for (int i=1;i<=n;i++){
            int maxi=0;int mini=1e9;
            for (int j=i;j>=1;j--){    j goes to 1 not zero bcz we are shifting index and assuming array starts from 1 instead 0
                maxi=max(maxi,nums[j-1]);  here you should be careful where you are accessing element from the array
                mini=min(mini,nums[j-1]);  I forgot to do (j-1) and written j but it should be (j-1) as element should be same if you would have been accessing any element using 'i' then also you had to do nums[i-1] not nums[i] since here we do not have that requriment we are fine with what we have now
                if(maxi-mini<=k){
                    dp[i]=(dp[i]%MOD+dp[j-1]%MOD)%MOD;
                }
                else{
                    break;
                }

            }
        }
        return dp[n];
        
        
    }
};



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