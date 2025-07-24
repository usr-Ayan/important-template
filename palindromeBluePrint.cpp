647. Palindromic Substrings
Solved
Medium
Topics
Companies
Hint
Given a string s, return the number of palindromic substrings in it.

A string is a palindrome when it reads the same backward as forward.

A substring is a contiguous sequence of characters within the string.







#include<bits/stdc++.h>
using namespace std;

//a 2d array that stores palindrome info
//if t[i][j]=true that means the substring 
//s[i......j] is palindrome
vector<vector<int>>t(s.size(),vector<int>(s.size(),-1));

bool isPalindrome(int i,int j,string &s,auto & dp){
	if(i>j){
		return true;
	}
	if(t[i][j])
	if(s[i]==s[j]){
		return isPalindrome(i+1,j-1,s);
	}
	return false;
}



int main(){
	//blueprint which substring palindrome which not
	vector<vector<int>>t(s.size(),vector<int>(s.size(),0));
        for (int len=1;len<=s.size();len++){
            for (int i=0;i+len-1<s.size();i++){
                int j=i+len-1;

                if(i==j){
                    t[i][j]=1;
                }
                else if (i+1==j){
                    t[i][j]=(s[i]==s[j]);
                }
                else{
                    t[i][j]=((s[i]==s[j])& t[i+1][j-1]);
                }
            }
        }



         //similiarly as we seen previously we will create a  table t
        //but here the table t will store values instead just 0 or 1
        //which will represent t[i][j]=1 means substring s[i....j] requires one 
        //character change to make the substring palindrome
        vector<vector<int>>t(s.size(),vector<int>(s.size(),0));
        for (int len=1;len<=s.size();len++){
            for (int i=0;i+len-1<s.size();i++){
                int j=i+len-1;

                if(i==j){
                    t[i][j]=0;
                }
                else if (i+1==j){
                    if(s[i]==s[j]){
                        t[i][j]=0;
                    }
                    else{
                        t[i][j]=1;
                    }
                }
                else{
                    if(s[i]==s[j]){
                        t[i][j]=t[i+1][j-1];
                    }
                    else{
                        t[i][j]=1+t[i+1][j-1];
                    }
                }
            }
        }


}