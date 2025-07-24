406. Queue Reconstruction by Height
Solved
Medium
Topics
Companies
Hint
You are given an array of people, people, which are the attributes of some people in a queue (not necessarily in order). Each people[i] = [hi, ki] represents the ith person of height hi with exactly ki other people in front who have a height greater than or equal to hi.

Reconstruct and return the queue that is represented by the input array people. The returned queue should be formatted as an array queue, where queue[j] = [hj, kj] is the attributes of the jth person in the queue (queue[0] is the person at the front of the queue).

 

Example 1:

Input: people = [[7,0],[4,4],[7,1],[5,0],[6,1],[5,2]]
Output: [[5,0],[7,0],[5,2],[6,1],[4,4],[7,1]]








class Solution {
public:
    vector<int>bit;
    void buildBIT(int n){
        bit.resize(n+1,0);
        for (int i=1;i<=n;i++){
            update(i,1,n);
        }
    }
    int sum(int i){
        int ans=0;
        while(i>0){
            ans+=bit[i];
            i-=(i&-i);
        }
        return ans;
    }
    void update(int i,int x,int n){
        while(i<=n){
            bit[i]+=x;
            i+=(i&-i);
        }
    }
    int bs(int start,int end,int k,int n){
        int ans=n-1;
        while(start<=end){
          int mid=start+(end-start)/2;
          if (sum(mid)==k+1){
            ans=mid;
            end=mid-1;
           }
          else if (sum(mid)<k+1){
            start=mid+1;
          }
          else{
            end=mid-1;
          }
        }
        return ans;
    }
   

    vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
        vector<vector<int>>temp;
        for (auto it:people){
            temp.push_back({it[0],-it[1]});
        }
        sort(temp.begin(),temp.end());
       for (int i=0;i<temp.size();i++)temp[i][1]*=-1;
        int n=temp.size();
        buildBIT(n);
        vector<vector<int>>ans(n);

        //we are trying to first arrange the small people at their first kth position bcz large people can go back and adjust
        for (int i=0;i<temp.size();i++){
            int index=bs(1,n,temp[i][1],n);
           //as the index it returns in bit which is one based and I have to put it in ans 0 based
            ans[index-1]=temp[i];
            update(index,-1,n);
        }
        return ans;

    }
};



//prefix sum using BIT

#include <iostream>
#include <vector>
using namespace std;

class FenwickTree {
public:
    vector<int> bit; // Made public
    int n;

    FenwickTree(int size) {
        n = size;
        bit.assign(n + 1, 0);
    }
    
    // Add `val` to index `i`
    void update(int i, int val) {
        for (++i; i <= n; i += i & -i)
            bit[i] += val;
    }
    
    // Build Fenwick Tree from array
    void build(const vector<int>& arr) {
        for (int i = 0; i < arr.size(); ++i) {
            update(i, arr[i]);
        }
    }

    // Get prefix sum [0..i]
    int sum(int i) {
        int res = 0;
        for (++i; i > 0; i -= i & -i)
            res += bit[i];
        return res;
    }
    
    // Get sum of range [l..r]
    int rangeSum(int l, int r) {
        return sum(r) - sum(l - 1);
    }
};

int main() {
    vector<int> arr = {3, 2, -1, 6, 5, 4, -3, 3, 7, 2, 3}; // Example array

    FenwickTree ft(arr.size());
    ft.build(arr); // Build the Fenwick Tree
    
    cout << "BIT array after building:\n";
    for (int i = 0; i < ft.bit.size(); i++) {
        cout << ft.bit[i] << " ";
    }
    cout << "\n";

    // Now querying some prefix sums
    cout << "Prefix sum [0..5]: " << ft.sum(5) << endl;  // sum of arr[0..5]
    cout << "Prefix sum [0..8]: " << ft.sum(8) << endl;  // sum of arr[0..8]
    cout << "Prefix sum [0..10]: " << ft.sum(10) << endl; // sum of arr[0..10]

    return 0;
}
