#include<bits/stdc++.h>
using namespace std;



int solve(int idx,string &s,vector<string>&dict){
	if(idx==s.size())return 0;

	int res=0;
	for (int i=idx;i<s.size();i++){
		string temp=s.substr(idx,i);
		if(st.count(temp)>0){
			res=max(res,1+solve(i+1,s,dict));

		}
	}
	return res;
}
int maxCount(String &s,vector<string>&dict){

}