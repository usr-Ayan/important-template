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