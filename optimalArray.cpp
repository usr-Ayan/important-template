Optimal Array
Difficulty: MediumAccuracy: 69.73%Submissions: 18K+Points: 4
You are given a sorted array a of length n. For each i(0<=i<=n-1), you have to make all the elements of the array from index 0 till i equal, using minimum number of operations. In one operation you either increase or decrease the array element by 1.

You have to return a list which contains the minimum number of operations for each i, to accomplish the above task.

Note:
1. 0-based indexing.
2. For each index, you need to consider the same array which was given to you at the start.




//brute

//User function Template for C++

class Solution{
public:
    vector<int> optimalArray(int n,vector<int> &a){
        // Code here
        //idea is for every array calculate the median value
        //and make all elements equal to median value so it will take minimum step
        vector<int>result;
        vector<int>prefix(n,0);
        for (int i=0;i<n;i++){
            prefix[i]=prefix[i-1]+i;
        }
        for (int i=0;i<n;i++){
            int median=0;
            int cost=0;
            
            if((i+1)%2==0){
                int n=i+1;
                median=(a[n/2]+a[n/2-1])/2;
            }
            else{
                int n=i+1;
                median=a[n/2];
            }
            
            
            for (int j=0;j<=i;j++){
                cost+=abs(a[j]-median);
            }
            result.push_back(cost);
        }
        return result;
        
        
    }
};




//optimal

//User function Template for C++

class Solution{
public:
    vector<int> optimalArray(int n,vector<int> &a){
        // Code here
        //idea is for every array calculate the median value
        //and make all elements equal to median value so it will take minimum step
       vector<int>result(n,0);
        for (int i=1;i<n;i++){
          int median=a[i/2];
          result[i]=result[i-1]+abs(a[i]-median);
          
        }
        return result;
        
       
     }
};