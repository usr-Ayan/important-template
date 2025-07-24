467. Unique Substrings in Wraparound String
Solved
Medium
Topics
premium lock icon
Companies
Hint
We define the string base to be the infinite wraparound string of "abcdefghijklmnopqrstuvwxyz", so base will look like this:

"...zabcdefghijklmnopqrstuvwxyzabcdefghijklmnopqrstuvwxyzabcd....".
Given a string s, return the number of unique non-empty substrings of s are present in base.


class Solution {
public:
    int findSubstringInWraproundString(string s) {
        //here we will try to find what is the maxlength of the string that is ending 
        //with (a,b,c,.....z)=>that are present in the string s and while doing that we will make sure 
        //next character is in the wraparound order
        vector<int>count(26,0);
        int maxLen=1;
        for (int i=0;i<s.size();i++){
            if(i>0 && (s[i]-s[i-1]==1 || s[i-1]=='z' && s[i]=='a')){
                maxLen++;
            }
            else{
                maxLen=1;
            }
            int index=s[i]-'a';
            count[index]=max(count[index],maxLen);


        }
        //as keeping the maxlen string ending at that chr will give me all the unique string that 
        //could be made using that eg: abcdbcd=>d=4

        int res=accumulate(count.begin(),count.end(),0);
        return res;

        

        
        
    }
};