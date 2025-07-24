Count the number of possible triangles
Difficulty: MediumAccuracy: 28.53%Submissions: 136K+Points: 4Average Time: 15m
Given an integer array arr[]. Find the number of triangles that can be formed with three different array elements as lengths of three sides of the triangle. 

A triangle with three given sides is only possible if sum of any two sides is always greater than the third side.




when the taking start at the start and end at the end does not work
//mine

class Solution {
  public:
    // Function to count the number of possible triangles.

    int countTriangles(vector<int>& arr) {
        // code here
        int cnt=0;
        int n=arr.size();
        sort(arr.begin(),arr.end());
        for (int i=0;i<n-2;i++){
            int start=i+1;
            int end=i+2;
            while(end<n){
                int sum=arr[i]+arr[start];
                if(sum<=arr[end]){
                    if(start<end-1){
                        start++;
                    }
                    else{
                        start++;
                        end++;
                    }
                }
                else{
                    cnt+=end-start;
                    end++;
                }
            }
        }
        return cnt; 
        
    }
};


//good solution


// C++ code to count the number of possible triangles
// using Two Pointers Technique

#include <algorithm>
#include <iostream>
#include <vector>
using namespace std;

// Function to count the number of valid triangles.
int countTriangles(vector<int> &arr) {
    int res = 0;
    sort(arr.begin(), arr.end());

    // Iterate through the array, fixing the largest side at arr[i]
    for (int i = 2; i < arr.size(); ++i) {
      
      	// Initialize pointers for the two smaller sides
        int left = 0, right = i - 1; 

        while (left < right) {
          
            if (arr[left] + arr[right] > arr[i]) {
              
                // arr[left] + arr[right] satisfies the triangle inequality,
				// so all pairs (x, right) with (left <= x < right) are valid
                res += right - left; 
              
              	// Move the right pointer to check smaller pairs
                right--; 
            } 
          	else {
              
              	// Move the left pointer to increase the sum
                left++; 
            }
        }
    }

    return res;
}

int main() {
    vector<int> arr = {4, 6, 3, 7};
    cout << countTriangles(arr);
    return 0;
}