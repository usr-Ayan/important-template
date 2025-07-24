#include<bits/stdc++.h>
using namespace std;


//why the segment tree arrayneeds to be of size 4n explain??

void buildSegmentTree(vector<int>&segment,int arr[],int l,int r,int i){//l,i=0 when passed and r=arr.length-1 
//and  we know that if  a tree is represented as an array the the left child of ith node of tree is (2*i+1) and right child is (2*i+2)
//and since segment tree is represented as array so we are storing value at those index
	if(l==r){
		segment[i]=arr[l];
		return;
	}
	int mid=(l+r)/2;
	buildSegmentTree(segment,arr,index,l,mid,2*i+1);
	buildSegmentTree(segment,arr,index,mid+1,r,2*i+2);
	segment[i]=segment[2*i+1]+segment[2*i+2];
	return;


}

void updateSegementTree(int idx,int val,int i,int arr[],vector<int>&segment){//idx is the index of main array where we want to update
//and val is with what value and i is the node index on segment tree array
	if(l==r){
		segment[i]=val;
	}
	int mid=(l+r)/2;
	if(idx<=mid){
		updateSegementTree(idx,val,2*i+1,arr,segment);
	}else{
		updateSegementTree(idx,val,2*i+2,arr,segment);
	}
	segment[i]=segment[2*i+1]+segment[2*i+2];
	return;


}

//updating value of a range of index
void lazyUpdate(int i,int start,int end,int l,int r,int val,vector<int>&segment,vector<int>&lazy){
	//first check if the node is updated or not 
	if(lazy[i]!=0){
		segment[i]+=(r-l+1)*val;
		if(l!=r){
			lazy[2*i+1]+=val;
			lazy[2*i+2]+=val;
		}
		lazy[i]=0;
	}
	//if node is out of range then just return
	if(l>end || r<start){
		return;
	}
	//if the node is completely inside the range then update the nodes value and give the left and right 
	//lazy child the value with what they need to propagate the lower nodes of tree
	if (l>=start && r<=end){
		segment[i]+=(r-l+1)*val;
		if(l!=r){
			lazy[2*i+1]+=val;
			lazy[2*i+2]+=val;

		}
		return;
	}
	//if node is overlapping then go left and right 
	int mid=(l+r)/2;
	lazyUpdate(2*i+1,start,end,l,mid,val,segment,lazy);
	lazyUpdate(2*i+2,start,end,mid+1,r,val,segment,lazy);
	segment[i]=segment[2*i+1]+segment[2*i+2];
	return;

	
}




int rangeQuery(int l,int r,int ,int start,int end,int i,arr[],vector<int>&segment){//start and end represent the range of which solution asked
//
	if(r<start || l>end){
		return 0;
	}
	if(l>=start && r<=end){
		return segment[i];
	}
	int mid=(l+r)/2;
	return rangeQuery(l,mid,start,end,2*i+1,arr,segment)+rangeQuery(mid+1,r,start,end,2*i+2,arr,segment);
}



int main(){
	int arr[10]={1,7,8,2,5,6,6,4,9,78};
	//to solve range sum query we will use segment tree here
	int n=10;
	vector<int>segment(4*n);
	vector<int>lazy(4*n);




}