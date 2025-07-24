712. Minimum ASCII Delete Sum for Two Strings
Attempted
Medium
Topics
premium lock icon
Companies
Hint
Given two strings s1 and s2, return the lowest ASCII sum of deleted characters to make two strings equal.

 

Example 1:

Input: s1 = "sea", s2 = "eat"
Output: 231
Explanation: Deleting "s" from "sea" adds the ASCII value of "s" (115) to the sum.
Deleting "t" from "eat" adds 116 to the sum.
At the end, both strings are equal, and 115 + 116 = 231 is the minimum sum possible to achieve this.
Example 2:

Input: s1 = "delete", s2 = "leet"
Output: 403
Explanation: Deleting "dee" from "delete" to turn the string into "let",
adds 100[d] + 101[e] + 101[e] to the sum.
Deleting "e" from "leet" adds 101[e] to the sum.
At the end, both strings are equal to "let", and the answer is 100+101+101+101 = 403.
If instead we turned both strings into "lee" or "eet", we would get answers of 433 or 417, which are higher.
 


my version (gives wrong answer for certain cases)

class Solution {
public:
    int solve(int i,int j,string & s1,string & s2){
        if(i<0 && j<0)return 1e9;
        if(i<0){
            int sum=0;
            for (int idx=0;idx<=j;idx++){
                sum+=s2[idx];
            }
            return sum;
        }
        if(j<0){
            int sum=0;
            for (int idx=0;idx<=i;idx++){
                sum+=s1[idx];
            }
            return sum;
        }

        int dlete=1e9;
        int not_dlete=1e9;
        if(s1[i]==s2[j]){
            not_dlete=0+solve(i-1,j-1,s1,s2);
        }
        dlete=min(s1[i]+solve(i-1,j,s1,s2),s2[j]+solve(i,j-1,s1,s2));
        return min(dlete,not_dlete);
    }
    int minimumDeleteSum(string s1, string s2) {
        return solve(s1.size()-1,s2.size()-1,s1,s2);
    }
};


corrected verison


class Solution {
public:
int dp[1001][1001];
    int solve(int i,int j,string & s1,string & s2){
        if(i<0 && j<0)return 0;
        if(i<0){
            int sum=0;
            for (int idx=0;idx<=j;idx++){
                sum+=s2[idx];
            }
            return sum;
        }
        if(j<0){
            int sum=0;
            for (int idx=0;idx<=i;idx++){
                sum+=s1[idx];
            }
            return sum;
        }
        if(dp[i][j]!=-1)return dp[i][j];

        int dlete=1e9;
        int not_dlete=1e9;
        if(s1[i]==s2[j]){
            not_dlete=0+solve(i-1,j-1,s1,s2);
        }
        dlete=min(s1[i]+solve(i-1,j,s1,s2),s2[j]+solve(i,j-1,s1,s2));
        return dp[i][j]=min(dlete,not_dlete);
    }
    int minimumDeleteSum(string s1, string s2) {
        memset(dp,-1,sizeof(dp));
        return solve(s1.size()-1,s2.size()-1,s1,s2);
    }
};




466. Count The Repetitions
Solved
Hard
Topics
premium lock icon
Companies
We define str = [s, n] as the string str which consists of the string s concatenated n times.

For example, str == ["abc", 3] =="abcabcabc".
We define that string s1 can be obtained from string s2 if we can remove some characters from s2 such that it becomes s1.

For example, s1 = "abc" can be obtained from s2 = "abdbec" based on our definition by removing the bolded underlined characters.
You are given two strings s1 and s2 and two integers n1 and n2. You have the two strings str1 = [s1, n1] and str2 = [s2, n2].

Return the maximum integer m such that str = [str2, m] can be obtained from str1.




class Solution {
public:
    int getMaxRepetitions(string s1, int n1, string s2, int n2) {
        int n=s1.size();
        int m=s2.size();
        unordered_map<int,pair<int,int>>mp;//cnt1,cnt2
        int cnt1=0,cnt2=0;
        int j=0;
        while(cnt1<n1){
            for (int idx=0;idx<s1.size();idx++){
                if(s1[idx]==s2[j]){
                    j++;
                    if(j==s2.size()){
                        j=0;
                        cnt2++;
                    }
                }
            }
            cnt1++;

            if(mp.find(j)!=mp.end()){
                int prevCnt=mp[j].second;
                int prevCycle=mp[j].first;
                int cycleLen=cnt1-prevCycle;
                int cycleCnt=cnt2-prevCnt;
                int remaining=(n1-cnt1)/cycleLen;
                cnt1+=remaining*cycleLen;
                cnt2+=remaining* cycleCnt;

            }

            else{
                mp[j]={cnt1,cnt2};
            }
        }
        return cnt2/n2;
    }
};