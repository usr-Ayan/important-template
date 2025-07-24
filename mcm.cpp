class Solution {
public:
    int waysToMakeFair(vector<int>& nums) {
        int n=nums.size();
        vector<int>evenSum(n+1,0);
        vector<int>oddSum(n+1,0);
        int even=0,odd=0;
        for (int i=0;i<=n;i++){
            evenSum[i]=even;
            oddSum[i]=odd;
            if(i>=n)continue;
            if(i%2==0 ){
                even+=nums[i];
            }else{
                //oddSum=odd;
                odd+=nums[i];
            }
        }
        // for (auto it : evenSum)cout<<it<<" ";
        // cout<<endl;
        // for (auto it : oddSum)cout <<it<<" ";
        // cout<<endl;
        int cnt=0;
        for (int i=0;i<n;i++){
            int leftEvenSum=evenSum[i];
            int leftOddSum=oddSum[i];
            int rightEvenSum=oddSum[n]-oddSum[i+1];
            int rightOddSum=evenSum[n]-evenSum[i+1];
            if((leftEvenSum+rightEvenSum)==(leftOddSum+rightOddSum)){
                cnt++;
            }
        }
        return cnt;

        
    }
};

