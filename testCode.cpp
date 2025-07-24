#include<bits/stdc++.h>
using namespace std;



void buildTree(int l,int r,int i,vector<int>&arr,bool orOperation,vector<int>&segTree){
	if(l==r){
		segTree[i]=arr[l];
		return;
	}
	int mid=(l+r)/2;
	buildTree(l,mid,2*i+1,arr,!orOperation,segTree);
	buildTree(mid+1,r,2*i+2,arr,!orOperation,segTree);
	if(orOperation){
		segTree[i]=segTree[2*i+1]|segTree[2*i+2];

	}else{
		segTree[i]=segTree[2*i+1]^segTree[2*i+2];
	}
	return;

}
void update(int l,int r,int i,bool orOperation, vector<int>&segTree,int idx,int val){
	if(l==r){
		segTree[i]=val;
		return;
	}
	int mid=(l+r)/2;
	if(idx<=mid){
		update(l,mid,2*i+1,!orOperation, segTree,idx,val);
	}
	else{
		update(mid+1,r,2*i+2,!orOperation, segTree,idx,val);

	}
	if(orOperation){
		segTree[i]=segTree[2*i+1]|segTree[2*i+2];

	}else{
		segTree[i]=segTree[2*i+1]^segTree[2*i+2];
	}
	return;
}


int main(){
	int n,m;
	cin>>n>>m;
	int element=pow(2,n);


	vector<int>arr(element);
	for (int i=0;i<element;i++){
		cin>>arr[i];
	}
	
	vector<int>segTree(4*element);
	if(n%2==0){
		buildTree(0,element-1,0,arr,false, segTree);//l,r,i

	}
	else{
		buildTree(0,element-1,0,arr,true, segTree);//l,r,i
	}
	
	while(m--){
		int idx,val;
		
		cin>>idx>>val;
		/c/out<<idx<<" "<<val<<endl;
		idx--;
		arr[idx]=val;
		int orOperation=false;
		if(n%2)orOperation=true;
		update(0,element-1,0,orOperation,segTree,idx,val);
		cout<<segTree[0]<<endl;
	}


}