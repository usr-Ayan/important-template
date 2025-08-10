995. Minimum Number of K Consecutive Bit Flips
Solved
Hard
Topics
premium lock icon
Companies
You are given a binary array nums and an integer k.

A k-bit flip is choosing a subarray of length k from nums and simultaneously changing every 0 in the subarray to 1, and every 1 in the subarray to 0.

Return the minimum number of k-bit flips required so that there is no 0 in the array. If it is not possible, return -1.

A subarray is a contiguous part of an array.



class Solution {
public:
    int minKBitFlips(vector<int>& nums, int k) {
        //brute would be two loop O(n*k)
        int n=nums.size();
        int flip=0;
        //greedy approach
        deque<int>q;
        for (int i=0;i<n;i++){
            //remove invalid effects of previous flips done by other indeces
            while(!q.empty() && i>=q.front()+k){
                q.pop_front();
                
            }

            //effective value of our current number=0; then only try to flip
            if((nums[i]+q.size())%2==0){//here q.size the number of flips affecting this index
                if(i+k>n)return -1;
                flip++;
                q.push_back(i);                        
            }
        }
        return flip;

        
    }
};



1007. Minimum Domino Rotations For Equal Row
Solved
Medium
Topics
premium lock icon
Companies
In a row of dominoes, tops[i] and bottoms[i] represent the top and bottom halves of the ith domino. (A domino is a tile with two numbers from 1 to 6 - one on each half of the tile.)

We may rotate the ith domino, so that tops[i] and bottoms[i] swap values.

Return the minimum number of rotations so that all the values in tops are the same, or all the values in bottoms are the same.

If it cannot be done, return -1.



Note:

whenever you see there are valid number of values our variable can take 
then greedily try to take all the values
This "limited candidate values" + greedy filtering idea is extremely common in algorithm problems.
🧠 How to Recognize the Pattern
Ask:

Is the set of possible target values small (bounded domain)?

Can I check if a given value is feasible in linear time?

Is it valid to try all possibilities and pick the minimum?

If yes → brute-force all valid values greedily.





class Solution {
public:

    int minDominoRotations(vector<int>& tops, vector<int>& bottoms) {
        int n=tops.size();
        int result=1e9;
        for (int i=1;i<=6;i++){
            int swapTop=0,swapBottom=0;
            bool canMake=true;
            for (int j=0;j<n;j++){
                if(tops[j]!=i && bottoms[j]!=i){
                    canMake=false;
                    break;

                }
                else if(bottoms[j]==i && tops[j]!=i){
                  
                    swapTop++;
                  

                }
                else if(tops[j]==i && bottoms[j]!=i){
                    swapBottom++;
                }
            }
            if(canMake){
                result=min({result,swapTop,swapBottom});
            }
            

        }
        return result==1e9?-1:result;
        
    }
};



238. Product of Array Except Self
Solved
Medium
Topics
premium lock icon
Companies
Hint
Given an integer array nums, return an array answer such that answer[i] is equal to the product of all the elements of nums except nums[i].

The product of any prefix or suffix of nums is guaranteed to fit in a 32-bit integer.

You must write an algorithm that runs in O(n) time and without using the division operation




class Solution {
public:
    vector<int> productExceptSelf(vector<int>& nums) {
        int n=nums.size();
        vector<int> prefix(n,1);
        vector<int>suffix(n,1);
       // int prefix[0]=1;
       vector<int>ans(n,1);
       int left=1;
        for (int i=0;i<n;i++){
            ans[i]*=left;//since current is calcullated using previos therefore there is always
            left*=nums[i];//a scope of space optimisation
        }
        int right=1;
        for(int i=n-1;i>=0;i--){
            ans[i]*=right;
            right*=nums[i];

        }
        // vector<int>ans(n,0);
        /*for (int i=0;i<n;i++){
            ans[i]=prefix[i]*suffix[i];
        }*/
        return ans;
        
    }
};

1864. Minimum Number of Swaps to Make the Binary String Alternating
Solved
Medium
Topics
premium lock icon
Companies
Hint
Given a binary string s, return the minimum number of character swaps to make it alternating, or -1 if it is impossible.

The string is called alternating if no two adjacent characters are equal. For example, the strings "010" and "1010" are alternating, while the string "0100" is not.

Any two characters may be swapped, even if they are not adjacent.

 

 class Solution {
public:
int solve(string & s, char firstChar){
    int swap=0;
    for (auto it: s){
        if((it-'0')!=firstChar)swap++;
        firstChar^=1;
    }
    return swap/2;
}
    int minSwaps(string s) {
        //invalid cases where answer is -1
        int oneCnt=0,zeroCnt=0;
        for (auto &it: s){
            if(it=='1')oneCnt++;
            else zeroCnt++;
        }
        if(abs(oneCnt-zeroCnt)>1)return -1;
        int res=1e9;

        //valid different cases
        if(oneCnt==zeroCnt){
            res=min({res,solve(s,1),solve(s,0)});
            
        }
        else if (oneCnt>zeroCnt){
            res=min(res,solve(s,1));

        }
        else if(zeroCnt>oneCnt){
            res=min(res,solve(s,0));
        }
        return res;
       
        
    }
};


921. Minimum Add to Make Parentheses Valid
Solved
Medium
Topics
premium lock icon
Companies
A parentheses string is valid if and only if:

It is the empty string,
It can be written as AB (A concatenated with B), where A and B are valid strings, or
It can be written as (A), where A is a valid string.
You are given a parentheses string s. In one move, you can insert a parenthesis at any position of the string.

For example, if s = "()))", you can insert an opening parenthesis to be "(()))" or a closing parenthesis to be "())))".
Return the minimum number of moves required to make s valid.

Example 1:

Input: s = "())"
Output: 1
Example 2:

Input: s = "((("
Output: 3

soln in O(n) space

class Solution {
public:
    int minAddToMakeValid(string s) {
        int cnt=0;
        stack<char>st;
        for (auto it : s){
            if(it=='('){
                st.push('(');
            }
            else{
                if(st.empty())cnt++;//need to add (  beforee it 
                else{
                    st.pop();
                }
            }
        }
        cnt+=st.size();
        return cnt;
        
    }
};
soln in O(1) space

class Solution {
public:
    int minAddToMakeValid(string s) {
        int cnt=0;
       // stack<char>st;
       int open=0, close=0;
        for (auto it : s){
            if(it=='('){
                open++;
            }
            else{
                if(open>0){
                    open--;
                }
                else{
                    cnt++;
                }
            }
        }
        cnt+=open;
        return cnt;
        
    }
};



1541. Minimum Insertions to Balance a Parentheses String
Solved
Medium
Topics
premium lock icon
Companies
Hint
Given a parentheses string s containing only the characters '(' and ')'. A parentheses string is balanced if:

Any left parenthesis '(' must have a corresponding two consecutive right parenthesis '))'.
Left parenthesis '(' must go before the corresponding two consecutive right parenthesis '))'.
In other words, we treat '(' as an opening parenthesis and '))' as a closing parenthesis.

For example, "())", "())(())))" and "(())())))" are balanced, ")()", "()))" and "(()))" are not balanced.
You can insert the characters '(' and ')' at any position of the string to balance it if needed.

Return the minimum number of insertions needed to make s balanced.

 

Example 1:

Input: s = "(()))"
Output: 1
Explanation: The second '(' has two matching '))', but the first '(' has only ')' matching. We need to add one more ')' at the end of the string to be "(())))" which is balanced.
Example 2:

Input: s = "())"
Output: 0
Explanation: The string is already balanced.




class Solution {
public:

    int minInsertions(string s) {
        //since ()) it is called balanced now we push all both '(' and ')' on stack and then check balanced or not 
        //if balanced pop 
        stack<char>st;
        //here the techique I will follow is I will make sure the stack maintains a valid parenthesis acc to question
        int insertionNeeded=0;
        for (auto it : s){
            if(it=='('){
                if(st.empty()){
                    st.push(it);
                }
                else{
                    if(st.top()=='('){
                        st.push(it);//add one more and make ((
                    }
                    else{//when : ) we have this on top means () present already that we made sure
                        insertionNeeded++;//make ()) and pop all
                        st.pop();
                        st.pop();
                        st.push(it);
                        
                    }
                }

            }
            else{//when our current element is )
                if(st.empty()){
                    insertionNeeded++;
                    st.push('(');//insert (
                    st.push(it);//make ()
                }
                else{
                    if(st.top()=='('){
                        st.push(it);//make()
                    }
                    else{
                        //we have : )=>means we already have ()
                        st.pop();
                        st.pop();
                    }
                }
            }
        }
        if(st.empty()){
            return insertionNeeded;
        }
        while(!st.empty()){
            char c= st.top();
            st.pop();
            if(c=='('){
                insertionNeeded+=2;
            }
            else{
                insertionNeeded++;// bcz we already have () one needed to make ()) i.e balanced
                st.pop();// pop the (
            }
        }
        return insertionNeeded;
        
    }
};



1963. Minimum Number of Swaps to Make the String Balanced
Solved
Medium
Topics
premium lock icon
Companies
Hint
You are given a 0-indexed string s of even length n. The string consists of exactly n / 2 opening brackets '[' and n / 2 closing brackets ']'.

A string is called balanced if and only if:

It is the empty string, or
It can be written as AB, where both A and B are balanced strings, or
It can be written as [C], where C is a balanced string.
You may swap the brackets at any two indices any number of times.

Return the minimum number of swaps to make s balanced.

 

Example 1:

Input: s = "][]["
Output: 1
Explanation: You can make the string balanced by swapping index 0 with index 3.
The resulting string is "[[]]".
Example 2:

Input: s = "]]][[["
Output: 2
Explanation: You can do the following to make the string balanced:
- Swap index 0 with index 4. s = "[]][][".
- Swap index 1 with index 5. s = "[[][]]".
The resulting string is "[[][]]".


class Solution {
public:
    int minSwaps(string s) {
        stack<char>st;
        int unbalanced=0;
        for (auto it :s){
            if(it=='['){
                st.push('[');
            }
            else{
                if(!st.empty())st.pop();
                else unbalanced++;

            }
        }
        return (unbalanced+1)/2;

    }
};

or 


class Solution {
public:
    int minSwaps(string s) {
        //stack<char>st;
        int unbalanced=0;
        int open=0;
        for (auto it :s){
            if(it=='['){
                open++;
            }
            else{
                
                if(open>0)open--;
                else unbalanced++;

            }
        }
        return (unbalanced+1)/2;

    }
};

249. Minimum Remove to Make Valid Parentheses
Solved
Medium
Topics
premium lock icon
Companies
Hint
Given a string s of '(' , ')' and lowercase English characters.

Your task is to remove the minimum number of parentheses ( '(' or ')', in any positions ) so that the resulting parentheses string is valid and return any valid string.

Formally, a parentheses string is valid if and only if:

It is the empty string, contains only lowercase characters, or
It can be written as AB (A concatenated with B), where A and B are valid strings, or
It can be written as (A), where A is a valid string.
 

Example 1:

Input: s = "lee(t(c)o)de)"
Output: "lee(t(c)o)de"
Explanation: "lee(t(co)de)" , "lee(t(c)ode)" would also be accepted.
Example 2:

Input: s = "a)b(c)d"
Output: "ab(c)d"
Example 3:

Input: s = "))(("
Output: ""

class Solution {
public:
    string minRemoveToMakeValid(string s) {
        stack<int>st;
        //int n=s.size();
        string temp;
        for (int i=0;i<s.size();i++){
            if (s[i]=='('){
                st.push(i);
            }
            else if (s[i]==')'){
                if(!st.empty())st.pop();
                else{
                    s[i]='A';
                    
                }
               
            }
        }
        cout<<s<<endl;
        while(!st.empty()){
            int idx=st.top();
            s[idx]='A';
            st.pop();
        }
        for(auto it :s){
            if(it!='A')temp.push_back(it);
        }
        return temp;;
        
        
    }
};

2171. Removing Minimum Number of Magic Beans
Solved
Medium
Topics
premium lock icon
Companies
Hint
You are given an array of positive integers beans, where each integer represents the number of magic beans found in a particular magic bag.

Remove any number of beans (possibly none) from each bag such that the number of beans in each remaining non-empty bag (still containing at least one bean) is equal. Once a bean has been removed from a bag, you are not allowed to return it to any of the bags.

Return the minimum number of magic beans that you have to remove.

 

Example 1:

Input: beans = [4,1,6,5]
Output: 4
Explanation: 
- We remove 1 bean from the bag with only 1 bean.
  This results in the remaining bags: [4,0,6,5]
- Then we remove 2 beans from the bag with 6 beans.
  This results in the remaining bags: [4,0,4,5]
- Then we remove 1 bean from the bag with 5 beans.
  This results in the remaining bags: [4,0,4,4]
We removed a total of 1 + 2 + 1 = 4 beans to make the remaining non-empty bags have an equal number of beans.
There are no other solutions that remove 4 beans or fewer.
Example 2:

Input: beans = [2,10,3,2]
Output: 7
Explanation:
- We remove 2 beans from one of the bags with 2 beans.
  This results in the remaining bags: [0,10,3,2]
- Then we remove 2 beans from the other bag with 2 beans.
  This results in the remaining bags: [0,10,3,0]
- Then we remove 3 beans from the bag with 3 beans. 
  This results in the remaining bags: [0,10,0,0]
We removed a total of 2 + 2 + 3 = 7 beans to make the remaining non-empty bags have an equal number of beans.
There are no other solutions that removes 7 beans or fewer.


class Solution {
public:
    long long minimumRemoval(vector<int>& beans) {
        int n=beans.size();
        sort(beans.begin(),beans.end());
        long long mini=LLONG_MAX;
        long long total=accumulate(beans.begin(),beans.end(),0LL);
        for (int i=0;i<n;i++){
            mini=min(mini,total-(1LL*(n-i)*beans[i]));
        }
        return mini;

        
    }
};


2391. Minimum Amount of Time to Collect Garbage
Solved
Medium
Topics
premium lock icon
Companies
Hint
You are given a 0-indexed array of strings garbage where garbage[i] represents the assortment of garbage at the ith house. garbage[i] consists only of the characters 'M', 'P' and 'G' representing one unit of metal, paper and glass garbage respectively. Picking up one unit of any type of garbage takes 1 minute.

You are also given a 0-indexed integer array travel where travel[i] is the number of minutes needed to go from house i to house i + 1.

There are three garbage trucks in the city, each responsible for picking up one type of garbage. Each garbage truck starts at house 0 and must visit each house in order; however, they do not need to visit every house.

Only one garbage truck may be used at any given moment. While one truck is driving or picking up garbage, the other two trucks cannot do anything.

Return the minimum number of minutes needed to pick up all the garbage.

 

Example 1:

Input: garbage = ["G","P","GP","GG"], travel = [2,4,3]
Output: 21
Explanation:
The paper garbage truck:
1. Travels from house 0 to house 1
2. Collects the paper garbage at house 1
3. Travels from house 1 to house 2
4. Collects the paper garbage at house 2
Altogether, it takes 8 minutes to pick up all the paper garbage.
The glass garbage truck:
1. Collects the glass garbage at house 0
2. Travels from house 0 to house 1
3. Travels from house 1 to house 2
4. Collects the glass garbage at house 2
5. Travels from house 2 to house 3
6. Collects the glass garbage at house 3
Altogether, it takes 13 minutes to pick up all the glass garbage.
Since there is no metal garbage, we do not need to consider the metal garbage truck.
Therefore, it takes a total of 8 + 13 = 21 minutes to collect all the garbage.
Example 2:

Input: garbage = ["MMM","PGM","GP"], travel = [3,10]
Output: 37
Explanation:
The metal garbage truck takes 7 minutes to pick up all the metal garbage.
The paper garbage truck takes 15 minutes to pick up all the paper garbage.
The glass garbage truck takes 15 minutes to pick up all the glass garbage.
It takes a total of 7 + 15 + 15 = 37 minutes to collect all the garbage.


class Solution {
public:
    int garbageCollection(vector<string>& garbage, vector<int>& travel) {
        int n=garbage.size();
        int res=0;
        //all garbage cost are added together 
        for (int i=0;i<n;i++){
            res+=garbage[i].size();
        }
        cout<<res<<endl;
        int metal=0,paper=0,glass=0;
        //now we are going to add all the travelcost of each truck
        for (int i=n-1;i>0;i--){
            
            metal=metal||garbage[i].find("M")!=string::npos;
            paper=paper||garbage[i].find("P")!=string::npos;
            glass=glass||garbage[i].find("G")!=string::npos;
            res+=travel[i-1]*(metal?1:0);
            res+=travel[i-1]*(paper?1:0);
            res+=travel[i-1]*(glass?1:0);


        }
        return res;
    }
};


2024. Maximize the Confusion of an Exam
Solved
Medium
Topics
premium lock icon
Companies
Hint
A teacher is writing a test with n true/false questions, with 'T' denoting true and 'F' denoting false. He wants to confuse the students by maximizing the number of consecutive questions with the same answer (multiple trues or multiple falses in a row).

You are given a string answerKey, where answerKey[i] is the original answer to the ith question. In addition, you are given an integer k, the maximum number of times you may perform the following operation:

Change the answer key for any question to 'T' or 'F' (i.e., set answerKey[i] to 'T' or 'F').
Return the maximum number of consecutive 'T's or 'F's in the answer key after performing the operation at most k times.

 Note: since values are limited we are brute forcing in the limited values

Example 1:

Input: answerKey = "TTFF", k = 2
Output: 4
Explanation: We can replace both the 'F's with 'T's to make answerKey = "TTTT".
There are four consecutive 'T's.
Example 2:

Input: answerKey = "TFFT", k = 1
Output: 3
Explanation: We can replace the first 'T' with an 'F' to make answerKey = "FFFT".
Alternatively, we can replace the second 'T' with an 'F' to make answerKey = "TFFF".
In both cases, there are three consecutive 'F's.
Example 3:

Input: answerKey = "TTFTTFTT", k = 1
Output: 5
Explanation: We can replace the first 'F' to make answerKey = "TTTTTFTT"
Alternatively, we can replace the second 'F' to make answerKey = "TTFTTTTT". 
In both cases, there are five consecutive 'T's.

class Solution {
public:
    int maxConsecutiveAnswers(string answerKey, int k) {
        int n=answerKey.size();
        //considering we will make consequtive true
        int i=0,j=0;
        int maxLen1=0;
        int key=k;
        while(j<n){
            
            if(answerKey[j]=='F'){
                key--;
            }
            while(key<0){
                if(answerKey[i]=='F'){
                    key++;
                }
                i++;
            }
            maxLen1=max(maxLen1,j-i+1);
            j++;
        }
        //considering we will make consequtive false
        i=0;j=0;
        int maxLen2=0;
        key=k;
        while(j<n){
            if(answerKey[j]=='T'){
                key--;
            }

            while(key<0){
                if(answerKey[i]=='T'){
                    key++;
                }
                i++;
            }
            maxLen2=max(maxLen2,j-i+1);
            j++;
        }
        return max(maxLen1,maxLen2);
    }
};


2348. Number of Zero-Filled Subarrays
Solved
Medium
Topics
premium lock icon
Companies
Hint
Given an integer array nums, return the number of subarrays filled with 0.

A subarray is a contiguous non-empty sequence of elements within an array.

 

Example 1:

Input: nums = [1,3,0,0,2,0,0,4]
Output: 6
Explanation: 
There are 4 occurrences of [0] as a subarray.
There are 2 occurrences of [0,0] as a subarray.
There is no occurrence of a subarray with a size more than 2 filled with 0. Therefore, we return 6.
Example 2:

Input: nums = [0,0,0,2,0,0]
Output: 9
Explanation:
There are 5 occurrences of [0] as a subarray.
There are 3 occurrences of [0,0] as a subarray.
There is 1 occurrence of [0,0,0] as a subarray.
There is no occurrence of a subarray with a size more than 3 filled with 0. Therefore, we return 9.
Example 3:

Input: nums = [2,10,2019]
Output: 0
Explanation: There is no subarray filled with 0. Therefore, we return 0.



class Solution {
public:
    long long zeroFilledSubarray(vector<int>& nums) {
        int n=nums.size();
        int i=0,j=0;
        long long cnt=0;
        int zeroCnt=0;
        while(j<n){
            if(nums[j]==0){
                zeroCnt++;
            }
            while(zeroCnt<(j-i+1)){
                if(nums[i]==0){
                    zeroCnt--;
                }
                i++;
            }
            cnt+=(j-i+1);
            j++;


        }
        return cnt;
        
    }
};




169. Majority Element
Solved
Easy
Topics
premium lock icon
Companies
Given an array nums of size n, return the majority element.

The majority element is the element that appears more than ⌊n / 2⌋ times. You may assume that the majority element always exists in the array.

 

Example 1:

Input: nums = [3,2,3]
Output: 3
Example 2:

Input: nums = [2,2,1,1,1,2,2]
Output: 2
 

Constraints:

n == nums.length
1 <= n <= 5 * 104
-109 <= nums[i] <= 109
 

Follow-up: Could you solve the problem in linear time and in O(1) space?

class Solution {
public:
    int majorityElement(vector<int>& nums) {
        int n=nums.size();
        int cnt=0;
        int candidate=0;//it could be assumed anything
        for(int i=0;i<n;i++){
            if(nums[i]==candidate){
                cnt++;
            }
            else if (cnt==0){
                candidate=nums[i];
                cnt=1;
            }
            else{
                cnt--;
            }
            

        }
        cnt=0;
        for (int i=0;i<n;i++){
            if(nums[i]==candidate)cnt++;
        }
        if(cnt>n/2)return candidate;
        return -1;
        
    }
};


229. Majority Element II
Solved
Medium
Topics
premium lock icon
Companies
Hint
Given an integer array of size n, find all elements that appear more than ⌊ n/3 ⌋ times.

 

Example 1:

Input: nums = [3,2,3]
Output: [3]
Example 2:

Input: nums = [1]
Output: [1]
Example 3:

Input: nums = [1,2]
Output: [1,2]
 

Constraints:

1 <= nums.length <= 5 * 104
-109 <= nums[i] <= 109
 

Follow up: Could you solve the problem in linear time and in O(1) space?

class Solution {
public:
//     So the critical observation is:
// ❗ You only reduce counts when the number does not match either candidate and both candidates are currently "strong" (non-zero).
// If the number matches candidate2, there's no reason to penalize candidate1, because candidate1 is irrelevant to this comparison. You're not trying to make the two candidates fight each other — you're trying to eliminate non-majority noise.
   
    vector<int> majorityElement(vector<int>& nums) {
        int n=nums.size();
        int cnt1=0;
        int cnt2=0;
        int candidate1=0,candidate2=0;//since we are not yet started so we can assume anything as our candidate

        for (int i=0;i<n;i++){
            if(nums[i]==candidate1){
                cnt1++;
            }
            else if (nums[i]==candidate2){
                cnt2++;
            }
            else if(cnt1==0){
                candidate1=nums[i];
                cnt1=1;
            }
            else if(cnt2==0 ){
                candidate2=nums[i];
                cnt2=1;
            }
            else{
                cnt1--;
                cnt2--;
            }

        }
        //at the end of the day both candidate can contain same number so
        //it is really important to handle that in check

        //check
        int freq1=0,freq2=0;
        for (auto it :nums){
            if(it==candidate1)freq1++;
            else if(it==candidate2)freq2++;//this condition should be in else if not if bcz if two
            //candidates are same we do not want to calculate twice so if first executes and
            //both candidate same second cond will never execute resulting only one candidate
            
        }
        vector<int>res;
        if(freq1>n/3)res.push_back(candidate1);
        if(freq2>n/3)res.push_back(candidate2);
        return res;
        
    }
};


1497. Check If Array Pairs Are Divisible by k
Solved
Medium
Topics
premium lock icon
Companies
Hint
Given an array of integers arr of even length n and an integer k.

We want to divide the array into exactly n / 2 pairs such that the sum of each pair is divisible by k.

Return true If you can find a way to do that or false otherwise.

 

Example 1:

Input: arr = [1,2,3,4,5,10,6,7,8,9], k = 5
Output: true
Explanation: Pairs are (1,9),(2,8),(3,7),(4,6) and (5,10).
Example 2:

Input: arr = [1,2,3,4,5,6], k = 7
Output: true
Explanation: Pairs are (1,6),(2,5) and(3,4).
Example 3:

Input: arr = [1,2,3,4,5,6], k = 10
Output: false
Explanation: You can try all possible pairs to see that there is no way to divide arr into 3 pairs each with sum divisible by 10.

class Solution {
public:
    bool canArrange(vector<int>& nums, int k) {
        int n=nums.size();
        if(n%2!=0)return false;

        unordered_map<int,int>mp;
       // int cnt=0;
        for (int i=0;i<nums.size();i++){
            int curr=nums[i]%k;
            if(curr<0)curr+=k;
            int need=(k-curr)%k;
            if(mp.find(need)!=mp.end()){
                mp[need]--;
                if(mp[need]==0)mp.erase(need);
            }else{
                mp[curr]++;
            }
        }
        return mp.size()==0;
        
    }
};


1657. Determine if Two Strings Are Close
Solved
Medium
Topics
premium lock icon
Companies
Hint
Two strings are considered close if you can attain one from the other using the following operations:

Operation 1: Swap any two existing characters.
For example, abcde -> aecdb
Operation 2: Transform every occurrence of one existing character into another existing character, and do the same with the other character.
For example, aacabb -> bbcbaa (all a's turn into b's, and all b's turn into a's)
You can use the operations on either string as many times as necessary.

Given two strings, word1 and word2, return true if word1 and word2 are close, and false otherwise.

 

Example 1:

Input: word1 = "abc", word2 = "bca"
Output: true
Explanation: You can attain word2 from word1 in 2 operations.
Apply Operation 1: "abc" -> "acb"
Apply Operation 1: "acb" -> "bca"
Example 2:

Input: word1 = "a", word2 = "aa"
Output: false
Explanation: It is impossible to attain word2 from word1, or vice versa, in any number of operations.
Example 3:

Input: word1 = "cabbba", word2 = "abbccc"
Output: true
Explanation: You can attain word2 from word1 in 3 operations.
Apply Operation 1: "cabbba" -> "caabbb"
Apply Operation 2: "caabbb" -> "baaccc"
Apply Operation 2: "baaccc" -> "abbccc"
 

Constraints:

1 <= word1.length, word2.length <= 105
word1 and word2 contain only lowercase English letters."

class Solution {
public:
    bool closeStrings(string word1, string word2) {
       int n=word1.size();
       int m=word2.size();
       if(n!=m)return false;
       vector<int>freq1(26,0);
       vector<int>freq2(26,0);
       for (auto & it : word1){
          freq1[it-'a']++;
       }
       for (auto & it : word2){
          freq2[it-'a']++;
       }
        //checking if  characters are present in both string
       for (int i=0;i<26;i++){
            if((freq1[i]==0 && freq2[i]!=0) || (freq1[i]!=0 && freq2[i]==0)){
                return false;
            }

       }
       sort(freq1.begin(),freq1.end());
       sort(freq2.begin(),freq2.end());
       return freq1==freq2;

        
    }
};


1399. Count Largest Group
Solved
Easy
Topics
premium lock icon
Companies
Hint
You are given an integer n.

We need to group the numbers from 1 to n according to the sum of its digits. For example, the numbers 14 and 5 belong to the same group, whereas 13 and 3 belong to different groups.

Return the number of groups that have the largest size, i.e. the maximum number of elements.

 

Example 1:

Input: n = 13
Output: 4
Explanation: There are 9 groups in total, they are grouped according sum of its digits of numbers from 1 to 13:
[1,10], [2,11], [3,12], [4,13], [5], [6], [7], [8], [9].
There are 4 groups with largest size.
Example 2:

Input: n = 2
Output: 2
Explanation: There are 2 groups [1], [2] of size 1.
 

Constraints:

1 <= n <= 104


class Solution {
public:
int digitSum(int n){
    int sum=0;
    while(n){
        int rem=n%10;
        sum+=rem;
        n/=10;
    }
    return sum;
}
    int countLargestGroup(int n) {
        unordered_map<int,int>mp;
        for (int i=1;i<=n;i++){
            int val=digitSum(i);
            mp[val]++;

        }
        int maxi=0;//maxi will hold the value of longest group
        for (auto &[x,y]:mp){//here a pair in map denotes how long is the group with digitsum x
            maxi=max(maxi,y);
        }
        cout<<maxi;
        int cnt=0;
        for (auto &[x,y]:mp){
            if(y==maxi)cnt++;
        }
        return cnt;
    }
};


1653. Minimum Deletions to Make String Balanced
Medium
Topics
premium lock icon
Companies
Hint
You are given a string s consisting only of characters 'a' and 'b'​​​​.

You can delete any number of characters in s to make s balanced. s is balanced if there is no pair of indices (i,j) such that i < j and s[i] = 'b' and s[j]= 'a'.

Return the minimum number of deletions needed to make s balanced.

 

Example 1:

Input: s = "aababbab"
Output: 2
Explanation: You can either:
Delete the characters at 0-indexed positions 2 and 6 ("aababbab" -> "aaabbb"), or
Delete the characters at 0-indexed positions 3 and 6 ("aababbab" -> "aabbbb").
Example 2:

Input: s = "bbaaaaabb"
Output: 2
Explanation: The only solution is to delete the first two characters."


class Solution {
public:
    int minimumDeletions(string s) {
        int n=s.size();
        vector<int>left(n,0);
        vector<int>right(n,0);
        int b_count=0;
        for (int i=0;i<n;i++){
            left[i]=b_count;
            if(s[i]=='b')b_count++;
        }
        int a_count=0;
        for (int i=n-1;i>=0;i--){
            right[i]=a_count;
            if(s[i]=='a')a_count++;
        }
        //any occurrence of b at the left of current index and any occurence of a at the right 
        //of current index will make string invalid so delete all occurence of b on left and all occurence of 
        //a on the right and try on every index and take the minimum out of all
        int mini=1e9;
        for (int i=0;i<n;i++){
            mini=min(mini,left[i]+right[i]);
        }
        return mini;
    }
};

or another solution

class Solution {
public:
    int minimumDeletions(string s) {
        //whenever we see in string we have to delete something or 
        //maintain some order just think about stack
        stack<char>st;
        int n=s.size();
        int delCnt=0;
        for (int i=0;i<n;i++){
            if(!st.empty() && s[i]=='a'){
                delCnt++;
                st.pop();
            }
            if(s[i]=='b'){
                st.push(s[i]);
            }
        }
        return delCnt;

    }
};

2433. Find The Original Array of Prefix Xor
Solved
Medium
Topics
premium lock icon
Companies
Hint
You are given an integer array pref of size n. Find and return the array arr of size n that satisfies:

pref[i] = arr[0] ^ arr[1] ^ ... ^ arr[i].
Note that ^ denotes the bitwise-xor operation.

It can be proven that the answer is unique.

 

Example 1:

Input: pref = [5,2,0,3,1]
Output: [5,7,2,3,2]
Explanation: From the array [5,7,2,3,2] we have the following:
- pref[0] = 5.
- pref[1] = 5 ^ 7 = 2.
- pref[2] = 5 ^ 7 ^ 2 = 0.
- pref[3] = 5 ^ 7 ^ 2 ^ 3 = 3.
- pref[4] = 5 ^ 7 ^ 2 ^ 3 ^ 2 = 1.
Example 2:

Input: pref = [13]
Output: [13]
Explanation: We have pref[0] = arr[0] = 13.
 

Constraints:

1 <= pref.length <= 105
0 <= pref[i] <= 106


class Solution {
public:
    vector<int> findArray(vector<int>& pref) {
        //ulta karke jo karna hota hai
        int n=pref.size();
        vector<int>res(n,0);
        int prev=0;
        for (int i=0;i<n;i++){
            res[i]=prev^pref[i];
            prev=pref[i];
        }
        return res;
        
    }
};

2453. Destroy Sequential Targets
Solved
Medium
Topics
premium lock icon
Companies
Hint
You are given a 0-indexed array nums consisting of positive integers, representing targets on a number line. You are also given an integer space.

You have a machine which can destroy targets. Seeding the machine with some nums[i] allows it to destroy all targets with values that can be represented as nums[i] + c * space, where c is any non-negative integer. You want to destroy the maximum number of targets in nums.

Return the minimum value of nums[i] you can seed the machine with to destroy the maximum number of targets.

 

Example 1:

Input: nums = [3,7,8,1,1,5], space = 2
Output: 1
Explanation: If we seed the machine with nums[3], then we destroy all targets equal to 1,3,5,7,9,... 
In this case, we would destroy 5 total targets (all except for nums[2]). 
It is impossible to destroy more than 5 targets, so we return nums[3].
Example 2:

Input: nums = [1,3,5,2,4,6], space = 2
Output: 1
Explanation: Seeding the machine with nums[0], or nums[3] destroys 3 targets. 
It is not possible to destroy more than 3 targets.
Since nums[0] is the minimal integer that can destroy 3 targets, we return 1.
Example 3:

Input: nums = [6,2,5], space = 100
Output: 2
Explanation: Whatever initial seed we select, we can only destroy 1 target. The minimal seed is nums[1].
 

Constraints:

1 <= nums.length <= 105
1 <= nums[i] <= 109
1 <= space <= 109

class Solution {
public:
    int destroyTargets(vector<int>& nums, int space) {
        int n= nums.size();
        unordered_map<int,int>mp;
        for (int i=0;i<n;i++){
            mp[nums[i]%space]++;//frequency how of how many numbers are destroyed by selected%space
        }
        int maxi=0;
        for (auto &[x,y]:mp)maxi=max(maxi,y);
        int res=1e9;
        for (auto i=0;i<n;i++){
            if(mp[nums[i]%space]==maxi)res=min(res,nums[i]);
        }
        return res;
      
    }
};


Code


Testcase
Testcase
Test Result
2593. Find Score of an Array After Marking All Elements
Solved
Medium
Topics
premium lock icon
Companies
Hint
You are given an array nums consisting of positive integers.

Starting with score = 0, apply the following algorithm:

Choose the smallest integer of the array that is not marked. If there is a tie, choose the one with the smallest index.
Add the value of the chosen integer to score.
Mark the chosen element and its two adjacent elements if they exist.
Repeat until all the array elements are marked.
Return the score you get after applying the above algorithm.

 Input: nums = [2,1,3,4,5,2]
Output: 7
Explanation: We mark the elements as follows:
- 1 is the smallest unmarked element, so we mark it and its two adjacent elements: [2,1,3,4,5,2].
- 2 is the smallest unmarked element, so we mark it and its left adjacent element: [2,1,3,4,5,2].
- 4 is the only remaining unmarked element, so we mark it: [2,1,3,4,5,2].
Our score is 1 + 2 + 4 = 7.

class Solution {
public:
    long long findScore(vector<int>& nums) {
        long long res=0;
        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<pair<int,int>>>pq;
        for (int i=0;i<nums.size();i++){
            pq.push({nums[i],i});
        }
        vector<int>visited(nums.size(),0);
        while(!pq.empty()){
            int val=pq.top().first;
            int index=pq.top().second;
            pq.pop();
            if(!visited[index]){
                visited[index]=1;
                if(index+1<nums.size())visited[index+1]=1;
                if(index-1>=0)visited[index-1]=1;
                res+=val;
            }

        }
        return res;
        
    }
};


1664. Ways to Make a Fair Array
Solved
Medium
Topics
premium lock icon
Companies
Hint
You are given an integer array nums. You can choose exactly one index (0-indexed) and remove the element. Notice that the index of the elements may change after the removal.

For example, if nums = [6,1,7,4,1]:

Choosing to remove index 1 results in nums = [6,7,4,1].
Choosing to remove index 2 results in nums = [6,1,4,1].
Choosing to remove index 4 results in nums = [6,1,7,4].
An array is fair if the sum of the odd-indexed values equals the sum of the even-indexed values.

Return the number of indices that you could choose such that after the removal, nums is fair.

 

Example 1:

Input: nums = [2,1,6,4]
Output: 1
Explanation:
Remove index 0: [1,6,4] -> Even sum: 1 + 4 = 5. Odd sum: 6. Not fair.
Remove index 1: [2,6,4] -> Even sum: 2 + 4 = 6. Odd sum: 6. Fair.
Remove index 2: [2,1,4] -> Even sum: 2 + 4 = 6. Odd sum: 1. Not fair.
Remove index 3: [2,1,6] -> Even sum: 2 + 6 = 8. Odd sum: 1. Not fair.
There is 1 index that you can remove to make nums fair.
Example 2:

Input: nums = [1,1,1]
Output: 3
Explanation: You can remove any index and the remaining array is fair.


class Solution {
public:
    int waysToMakeFair(vector<int>& nums) {
        int n=nums.size();
        vector<int>evenSum(n+1,0);
        vector<int>oddSum(n+1,0);
        int even=0,odd=0;
        for (int i=0;i<=n;i++){
            evenSum[i]=even;
            oddSum[i]=odd;
            if(i>=n)continue;
            if(i%2==0 ){
                even+=nums[i];
            }else{
                //oddSum=odd;
                odd+=nums[i];
            }
        }
        // for (auto it : evenSum)cout<<it<<" ";
        // cout<<endl;
        // for (auto it : oddSum)cout <<it<<" ";
        // cout<<endl;
        int cnt=0;
        for (int i=0;i<n;i++){
            int leftEvenSum=evenSum[i];
            int leftOddSum=oddSum[i];
            int rightEvenSum=oddSum[n]-oddSum[i+1];
            int rightOddSum=evenSum[n]-evenSum[i+1];
            if((leftEvenSum+rightEvenSum)==(leftOddSum+rightOddSum)){
                cnt++;
            }
        }
        return cnt;

        
    }
};


"✅ Yes, you're absolutely right — in both cases, two problems given below either method 
(line sweep or event sorting(arrival,departure) ) but in case of event sorting you should do it independently
can be used."


line sweep
Meeting rooms
Programming
Greedy Algorithm
medium
59.7% Success

394

20

Bookmark
Asked In:
Problem Description
 
 

Given an 2D integer array A of size N x 2 denoting time intervals of different meetings.

 

Where:

 

A[i][0] = start time of the ith meeting.
A[i][1] = end time of the ith meeting.
 

Find the minimum number of conference rooms required so that all meetings can be done.

Note :- If a meeting ends at time t, another meeting starting at time t can use the same conference room

 



Problem Constraints
1 <= N <= 105

 

0 <= A[i][0] < A[i][1] <= 2 * 109

 



Input Format
The only argument given is the matrix A.



Output Format
Return the minimum number of conference rooms required so that all meetings can be done.



Example Input
Input 1:

 A = [      [0, 30]
            [5, 10]
            [15, 20]
     ]

Input 2:

 A =  [     [1, 18]
            [18, 23]
            [15, 29]
            [4, 15]
            [2, 11]
            [5, 13]
      ]


Example Output
Output 1:

 2
Output 2:

 4


Example Explanation
Explanation 1:

 Meeting one can be done in conference room 1 form 0 - 30.
 Meeting two can be done in conference room 2 form 5 - 10.
 Meeting three can be done in conference room 2 form 15 - 20 as it is free in this interval.
Explanation 2:

 Meeting one can be done in conference room 1 from 1 - 18.
 Meeting five can be done in conference room 2 from 2 - 11.
 Meeting four can be done in conference room 3 from 4 - 15.
 Meeting six can be done in conference room 4 from 5 - 13.
 Meeting three can be done in conference room 2 from 15 - 29 as it is free in this interval.
 Meeting two can be done in conference room 4 from 18 - 23 as it is free in this interval.




int Solution::solve(vector<vector<int> > &arr) {
    int n=arr.size();
    map<int,int>mp;
    int overlap=0;
    for (int i=0;i<n;i++){
        auto cur=arr[i];
        mp[cur[0]]+=1;
        mp[cur[1]]-=1;
    }
    int maxOverlap=0;
    for (auto &[x,y]:mp){
        overlap+=y;
        maxOverlap=max(maxOverlap,overlap);
    }
    return maxOverlap;

}

or
int minMeetingRooms(vector<vector<int>>& intervals) {
    vector<int> start, end;
    for (auto &i : intervals) {
        start.push_back(i[0]);
        end.push_back(i[1]);
    }
    sort(start.begin(), start.end());
    sort(end.begin(), end.end());

    int rooms = 0, maxRooms = 0;
    int i = 0, j = 0;
    int n = start.size();

    while (i < n && j<n) {
        if (start[i] < end[j]) {
            rooms++;
            maxRooms = max(maxRooms, rooms);
            i++;
        } else {
            rooms--;
            j++;
        }
    }
    return maxRooms;
}


Minimum Platforms

You are given the arrival times arr[] and departure times dep[] of all trains that arrive at a railway station on the same day. Your task is to determine the minimum number of platforms required at the station to ensure that no train is kept waiting.

At any given time, the same platform cannot be used for both the arrival of one train and the departure of another. Therefore, when two trains arrive at the same time, or when one arrives before another departs, additional platforms are required to accommodate both trains.

Examples:

Input: arr[] = [900, 940, 950, 1100, 1500, 1800], dep[] = [910, 1200, 1120, 1130, 1900, 2000]
Output: 3
Explanation: There are three trains during the time 9:40 to 12:00. So we need a minimum of 3 platforms.
Input: arr[] = [900, 1235, 1100], dep[] = [1000, 1240, 1200]
Output: 1
Explanation: All train times are mutually exclusive. So we need only one platform
Input: arr[] = [1000, 935, 1100], dep[] = [1200, 1240, 1130]
Output: 3
Explanation: All 3 trains have to be there from 11:00 to 11:30


class Solution{
    public:
    //Function to find the minimum number of platforms required at the
    //railway station such that no train waits.
    int findPlatform(int arr[], int dept[], int n)
    {
        // Your code here
        sort(arr,arr+n);
        sort(dept,dept+n);
        int cnt=0;int maxCount=0;
        int i=0;int j=0;
        while(j<n && i<n){
            if(arr[i]<=dept[j]){
                cnt++;
                i++;
                maxCount=max(maxCount,cnt);
            }
            else{
                cnt--;
                j++;
            }
        }
        return maxCount;
        
    }
};



447. Number of Boomerangs
Solved
Medium
Topics
premium lock icon
Companies
You are given n points in the plane that are all distinct, where points[i] = [xi, yi]. A boomerang is a tuple of points (i, j, k) such that the distance between i and j equals the distance between i and k (the order of the tuple matters).

Return the number of boomerangs.

 

Example 1:

Input: points = [[0,0],[1,0],[2,0]]
Output: 2
Explanation: The two boomerangs are [[1,0],[0,0],[2,0]] and [[1,0],[2,0],[0,0]].
Example 2:

Input: points = [[1,1],[2,2],[3,3]]
Output: 2
Example 3:

Input: points = [[1,1]]
Output: 0
 

Constraints:

n == points.length
1 <= n <= 500
points[i].length == 2
-104 <= xi, yi <= 104
All the points are unique.



#define ll long long int
class Solution {
public:
    int numberOfBoomerangs(vector<vector<int>>& arr) {
        int n=arr.size();
        int cnt=0;
       
        for (int i=0;i<n;i++){
            unordered_map<int,int>mp;
            for (int j=0;j<n;j++){
                if(i==j)continue;
                ll dx=arr[j][0]-arr[i][0];
                ll dy=arr[j][1]-arr[i][1];
                ll dist=dx*dx+dy*dy;
                mp[dist]++;
            }
            for (auto &[_,y]:mp){
                cnt+=(y*(y-1));
            }
        }
        return cnt;
      
        
        
    }
};

390. Elimination Game
Solved
Medium
Topics
premium lock icon
Companies
You have a list arr of all integers in the range [1, n] sorted in a strictly increasing order. Apply the following algorithm on arr:

Starting from left to right, remove the first number and every other number afterward until you reach the end of the list.
Repeat the previous step again, but this time from right to left, remove the rightmost number and every other number from the remaining numbers.
Keep repeating the steps again, alternating left to right and right to left, until a single number remains.
Given the integer n, return the last number that remains in arr.

 

Example 1:

Input: n = 9
Output: 6
Explanation:
arr = [1, 2, 3, 4, 5, 6, 7, 8, 9]
arr = [2, 4, 6, 8]
arr = [2, 6]
arr = [6]
Example 2:

Input: n = 1
Output: 1

class Solution {
public:
    int lastRemaining(int n) {
        int remaining=n;
        int step=1;
        int head=1;
        bool lToR=true;
        while(remaining>1){
           // remaining/=2;
            if(lToR ||remaining%2==1 ){

                head=head+step;
            }
            remaining/=2;
            step=step*2;
            lToR=!lToR;
        }
        return head;
    }
};


632. Smallest Range Covering Elements from K Lists
Solved
Hard
Topics
premium lock icon
Companies
You have k lists of sorted integers in non-decreasing order. Find the smallest range that includes at least one number from each of the k lists.

We define the range [a, b] is smaller than range [c, d] if b - a < d - c or a < c if b - a == d - c.

 

Example 1:

Input: nums = [[4,10,15,24,26],[0,9,12,20],[5,18,22,30]]
Output: [20,24]
Explanation: 
List 1: [4, 10, 15, 24,26], 24 is in range [20,24].
List 2: [0, 9, 12, 20], 20 is in range [20,24].
List 3: [5, 18, 22, 30], 22 is in range [20,24].
Example 2:

Input: nums = [[1,2,3],[1,2,3],[1,2,3]]
Output: [1,1]
 

Constraints:

nums.length == k
1 <= k <= 3500
1 <= nums[i].length <= 50
-105 <= nums[i][j] <= 105


class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {

       int k=nums.size();
       vector<int>pointers(k,0);
       
       //int miniPtr=0;
       vector<int>ans={-1000000,1000000};
       //int elementIdx=0;
        int maxi=-1e9;
        priority_queue<vector<int>,vector<vector<int>>,greater<vector<int>>>pq;
        for (int i=0;i<k;i++){
            pq.push({nums[i][pointers[i]],pointers[i],i});//value,elementIdx,listIdx
            maxi=max(maxi,nums[i][pointers[i]]);
        }
        while(true){
            auto node=pq.top();
            int listIdx=node[2];
            int elementIdx=node[1];
            int mini=node[0];
            pq.pop();

            if(maxi-mini<ans[1]-ans[0]){
                ans[0]=mini;ans[1]=maxi;
            }
            int nextIdx=elementIdx+1;
            if(nextIdx>=nums[listIdx].size())break;
            else{
                pointers[listIdx]=nextIdx;
                maxi=max(maxi,nums[listIdx][pointers[listIdx]]);
                pq.push({nums[listIdx][pointers[listIdx]],pointers[listIdx],listIdx});
            }
        }
        return ans;

       
    }
};

or

class Solution {
public:
    vector<int> smallestRange(vector<vector<int>>& nums) {

       int k=nums.size();
       vector<int>pointers(k,0);
       
       int miniPtr=0;
       vector<int>ans={-1000000,1000000};
       int listIdx=0,elementIdx=0;
        while(true){
            int maxi=-1e9;int mini=1e9;
            for (int i=0;i<k;i++){
                if(mini>nums[i][pointers[i]]){
                    mini=nums[i][pointers[i]];
                    listIdx=i;
                    elementIdx=pointers[i];
                }
                maxi=max(maxi,nums[i][pointers[i]]);
            }

            if(maxi-mini<ans[1]-ans[0]){
                ans[0]=mini;ans[1]=maxi;
            }
            int nextIdx=elementIdx+1;
            if(nextIdx>=nums[listIdx].size())break;
            else{
                pointers[listIdx]=nextIdx;
            }
        }
        return ans;

       
    }
};

1717. Maximum Score From Removing Substrings
Solved
Medium
Topics
premium lock icon
Companies
Hint
You are given a string s and two integers x and y. You can perform two types of operations any number of times.

Remove substring "ab" and gain x points.
For example, when removing "ab" from "cabxbae" it becomes "cxbae".
Remove substring "ba" and gain y points.
For example, when removing "ba" from "cabxbae" it becomes "cabxe".
Return the maximum points you can gain after applying the above operations on s.

 

Example 1:

Input: s = "cdbcbbaaabab", x = 4, y = 5
Output: 19
Explanation:
- Remove the "ba" underlined in "cdbcbbaaabab". Now, s = "cdbcbbaaab" and 5 points are added to the score.
- Remove the "ab" underlined in "cdbcbbaaab". Now, s = "cdbcbbaa" and 4 points are added to the score.
- Remove the "ba" underlined in "cdbcbbaa". Now, s = "cdbcba" and 5 points are added to the score.
- Remove the "ba" underlined in "cdbcba". Now, s = "cdbc" and 5 points are added to the score.
Total score = 5 + 4 + 5 + 5 = 19.
Example 2:

Input: s = "aabbaaxybbaabb", x = 5, y = 4
Output: 20
 

class Solution {
public:
    //with stack
    string  removeSubString(string &s,string target,int point,int & cnt){
        stack<char>st;
        for (auto it : s){
            if(it==target[1]){
                if(!st.empty() && st.top()==target[0]){
                    st.pop();
                }else{
                    st.push(it);
                }
            }else{
                st.push(it);
            }
        }
        int diff=s.size()-st.size();
        cnt+=(diff/2)*point;
        string temp;
        while(!st.empty()){
            auto ch=st.top();
            st.pop();
            temp.push_back(ch);
        }
        reverse(temp.begin(),temp.end());
        return temp;


    }

    //second approach without using any stack O(1) space complexity
    string removeSubString(string &s,string target,int point,int &cnt){
        //read write method
        //i will write whatever value j gives
        int i=0,j=0;//i write pointer and j read pointer
        while(j<s.size()){
            s[i]=s[j];//write value of j first then check 
            i++;j++;//and increment before checking
            if(i>=2 && s[i-2]==target[0] && s[i-1]==target[1]){
                i=i-2;
            }
        }
        string temp=s.substr(0,i);
        cout<<temp<<endl;
        int diff=s.size()-temp.size();
        cnt+=(diff/2)*point;

        return s.substr(0,i);
    
    }
    int maximumGain(string s, int x, int y) {
        string fTarget="";string sTarget="";
        int point1=0,point2=0;
        if(x>y){
            fTarget="ab";
            sTarget="ba";
            point1=x;point2=y;
        }else{
            fTarget="ba";
            sTarget="ab";
            point1=y;point2=x;
        }
        int cnt=0;
        string remaining=removeSubString(s,fTarget,point1,cnt);
        removeSubString(remaining,sTarget,point2,cnt);
        return cnt;

    }
};

Given two strings s and part, perform the following operation on s until all occurrences of the substring part are removed:

Find the leftmost occurrence of the substring part and remove it from s.
Return s after removing all occurrences of part.

A substring is a contiguous sequence of characters in a string.

 

Example 1:

Input: s = "daabcbaabcbc", part = "abc"
Output: "dab"
Explanation: The following operations are done:
- s = "daabcbaabcbc", remove "abc" starting at index 2, so s = "dabaabcbc".
- s = "dabaabcbc", remove "abc" starting at index 4, so s = "dababc".
- s = "dababc", remove "abc" starting at index 3, so s = "dab".
Now s has no occurrences of "abc".
Example 2:

Input: s = "axxxxyyyyb", part = "xy"
Output: "ab"
Explanation: The following operations are done:
- s = "axxxxyyyyb", remove "xy" starting at index 4 so s = "axxxyyyb".
- s = "axxxyyyb", remove "xy" starting at index 3 so s = "axxyyb".
- s = "axxyyb", remove "xy" starting at index 2 so s = "axyb".
- s = "axyb", remove "xy" starting at index 1 so s = "ab".
Now s has no occurrences of "xy".



class Solution {
public:
    string removeOccurrences(string s, string part) {
        stack<char> stk;
        int strLength = s.length();
        int partLength = part.length();

        // Iterate through each character in the string
        for (int index = 0; index < strLength; index++) {
            // Push current character to stack
            stk.push(s[index]);

            // If stack size is greater than or equal to the part length, check
            // for match
            if (stk.size() >= partLength && checkMatch(stk, part, partLength)) {
                // Pop the characters matching 'part' from the stack
                for (int j = 0; j < partLength; j++) {
                    stk.pop();
                }
            }
        }

        // Convert stack to string with correct order
        string result = "";
        while (!stk.empty()) {
            result = stk.top() + result;
            stk.pop();
        }

        return result;
    }

private:
    // Helper function to check if the top of the stack matches the 'part'
    bool checkMatch(stack<char>& stk, string& part, int partLength) {
        stack<char> temp = stk;

        // Iterate through part from right to left
        for (int partIndex = partLength - 1; partIndex >= 0; partIndex--) {
            // If current stack top doesn't match expected character
            if (temp.top() != part[partIndex]) {
                return false;
            }
            temp.pop();
        }
        return true;
    }
};

//o(1) space solution
class Solution {
public:
    string removeOccurrences(string s, string part) {
        int i=0;int j=0;//i read pointer j write pointer
        int k=part.size();
        
        while(j<s.size()){
            s[i]=s[j];
            i++;j++;
            bool flag=true;
            if(i-k<0)flag=false;
            int idx=0;
            for (int l=i-k;l<i && flag==true;l++){
                if(s[l]!=part[idx])flag=false;
                idx++;
            }
            if(flag){
                i=i-k;
            }
        }
        return s.substr(0,i);

        
    }
};