2523. Closest Prime Numbers in Range
Solved
Medium
Topics
Companies
Hint
Given two positive integers left and right, find the two integers num1 and num2 such that:

left <= num1 < num2 <= right .
Both num1 and num2 are prime numbers.
num2 - num1 is the minimum amongst all other pairs satisfying the above conditions.
Return the positive integer array ans = [num1, num2]. If there are multiple pairs satisfying these conditions, return the one with the smallest num1 value. If no such numbers exist, return [-1, -1].

//two pointer problem



class Solution {
public:
    vector<int> closestPrimes(int left, int right) {
        vector<int>prime(right+1,1)
;        prime[0]=0;
        prime[1]=0;
        for (int i=2;i*i<=right;i++){
            if(prime[i]){
                for (int j=i+i;j<=right;j+=i){
                    prime[j]=0;
                }
            }
        }
        int prev=-1;
        int first=-1,sec=-1;
        int diff=1e9;
        for (int i=left;i<=right;i++){
            if(prime[i]){
                if(prev!=-1){
                    if(i-prev<diff){
                        diff=i-prev;
                        first=prev;
                        sec=i;
                        
                    }
                }
                prev=i;
                
            }
        }
        return ans;

        
        
    }
};