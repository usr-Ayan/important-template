// Minimum Swaps to Sort
// Difficulty: MediumAccuracy: 38.39%Submissions: 174K+Points: 4Average Time: 20m


// Given an array arr[] of distinct elements. Find the minimum number of swaps required to sort the array in strictly increasing order.

class Solution {
  public:
    // Function to find the minimum number of swaps required to sort the array.
    int minSwaps(vector<int>& arr) {
       vector<pair<int,int>>nums;
        for (int i=0;i<arr.size();i++){
           nums.push_back({arr[i],i});
        }
        sort(nums.begin(),nums.end());
        int i=0;
        int cnt=0;
        while(i<nums.size()){
            if(nums[i].second==i){
                i++;
            }
            else{
                swap(nums[i],nums[nums[i].second]);
                cnt++;
            }
        }
        return cnt;
        
    }
};