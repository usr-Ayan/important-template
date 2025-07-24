#include<bits/stdc++.h>
using namespace std;


// let any binary number be x
// => x=a1b    here b=0000000...   a=> binary 0/1 combo 1 is right most set bit
// =>-x=2's complement of 1
//     =x'+1
//     =(a1b)'+1
//     =(a'0b')+1
// 	=a' 0 (111....)+1
// 	=a' 1  000000..
// x&-x=a1b
// 	&a'1000000
// 	=1(the right most set bit)


///in binary index tree every node/index stores sum of a range
//it stores sum from range[ j+1,i] where j is the index we get when we remove right most 1 from the current index
// for eg the index 12 stores sum from from index 9 to 12 both inclusive 
// bcz 12's binary is 1100 removing last set 1 we get 1000=j  so it stores j+1=9 to 12 
//so if we need sum of from 1 to 12 then 
// we add sum =bit[12]bit[8]; (bcz after removind last set bit from 8 we get 0 and indexing starts from 1 in bit)
//so the while loop in query will run as long as we can remove a set bit from the number and for any number with value n
//its length is logn so max tc =log(n)

int sum(int id){//gives sum from (number ,count) whatever you stored from  index 1 to id both inclusive
	int ans=0;
	while(id>0){
		ans+=bit[id];
		id-=(id&-id);
	}
	return ans;
}

//now this function will add any given number and it will update alll the indices that on which after removing the last set bit we get id
//eg 14=1110 conatins sum of 13 to 14 inclusive now if the last set bit removed we get 13 that means we need to add val in index 14 also
int update(int id,int val){// adds val to id th index
	while(id<=n){
		bit[id]+=val;
		id+=(id& -id);
	}
}

///now the question is why can we find count inversion using frnwick tree as it talks about sum , or ,xor but never like greater than less than
//8,4,9,2,8
//idea is use this array element as the index of fenwick tree as index are sorted and index in frnwick tree gives partial sum upto that index
// 1 2 3 4 5 6 7 8 9 10 now assume the index in fenwick tree stores sum of count upto that index => larger element thatb that index= sum(max)-sum (index)
// 0 1 0 1 0 0 0 8 1 0 



int main(){
	int arr={ 8,4,9, 2, 8,10000000};//in this case we cannot take the size = max(array val ) as our bit array as this is so big
	//so first compress the array
	int n=6;
	map<int,int>mp;
	for (int i=0;i<n;i++){
		mp[arr[i]];
	}
	int cnt=1;
	for(auto it :mp){
		it.second=cnt++;
	}
	//successfully compressed

	//building the tree
	int inversionCount=0;

	//we are processing index one by one and adding to the count the value sum(max)-sum(a[i])bcz that represents
	//how many number are greater than a[i] and we add that in count bcz as of now only the left side of the array isprocessed
	//so that means how many number is greater than that of a[i]  at left side of array that i s inversion count 
	for (int i=0;i<n;i++){
		inversionCount+=sum(max)-sum(a[i]);
		update(arr[i],1); 
	} 



}





/// another and more preferred way of doing it is
vector<int>bit;
void makeBitArray(int n){
	bit.resize(n+1,0);
}
int sum(int id){//gives sum from (number ,count) whatever you stored from  index 1 to id both inclusive
	int ans=0;
	while(id>0)
{		ans+=bit[id];
		id-=(id&-id);
	}
	return ans;
}

//now this function will add any given number and it will update alll the indices that on which after removing the last set bit we get id
//eg 14=1110 conatins sum of 13 to 14 inclusive now if the last set bit removed we get 13 that means we need to add val in index 14 also
int update(int id,int val){// adds val to id th index
	while(id<=n){
		bit[id]+=val;
		id+=(id& -id);
	}
}


int main(){
	int arr={3 , 2 , 8 , 6 , 9 ,1 , 1000000};
	int n=7;
	vector<pair<int,int>>temp;
	for (int i=0;i<n;i++){
		temp.push_back({arr[i],i});

	}
	sort(temp.begin(),temp.end());
	int count=0;
	for (auto [val,id]:temp){//we will start from the small element and each time count the range sum of the right
		//that is how many of them are already processed at the right 
		// bcz if they are processed means they are smaller than this node 
		// taking range sum of right bcz we want smaller element count for this node at the right
		//and after that update its count tom corresponding index
		count+=sum(n)-sum(id+1);
		update(id+1,val);
	}
	return count;

}