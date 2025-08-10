Search Pattern (KMP-Algorithm)
Difficulty: HardAccuracy: 45.04%Submissions: 121K+Points: 8
Given two strings, one is a text string txt and the other is a pattern string pat. The task is to print the indexes of all the occurrences of the pattern string in the text string. Use 0-based indexing while returning the indices.
Note: Return an empty list in case of no occurrences of pattern.

Examples :

Input: txt = "abcab", pat = "ab"
Output: [0, 3]
Explanation: The string "ab" occurs twice in txt, one starts at index 0 and the other at index 3. 



class Solution
{
    
    
    public:
        // Function to compute the LPS (Longest Proper Prefix which is also Suffix) array
        void computeLps(string& pat,vector<int>&lps){
            lps[0]=0;
            int i=1;
            int len=0;
            while(i<lps.size()){
                if(pat[i]==pat[len]){
                    len++;
                    lps[i]=len;
                    i++;
                }
                else{
                    if(len!=0){
                        len=lps[len-1];
                    }else{
                        lps[i]=0;
                        i++;
                    }
                }
            }
            
            return;
        }
    
        
        vector <int> search(string pat, string txt) {
            vector<int>res;
            vector<int>lps(pat.size(),0);
            computeLps(pat,lps);
            
            int i=0;//for text 
            int j=0;//for the pat string
            while(i<txt.size()){
                if(txt[i]==pat[j]){
                    i++;j++;
                    if (j==pat.size()){
                        res.push_back(i-j);
                        j=lps[j-1];
                    }
                }
               
                else if (txt[i]!=pat[j]){
                    if(j!=0){
                        j=lps[j-1];
                        
                    }
                    else{
                        i++;
                    }
                }
            }
            return res;
            
        }
     
};




