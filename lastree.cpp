105. Construct Binary Tree from Preorder and Inorder Traversal
Solved
Medium
Topics
premium lock icon
Companies
Given two integer arrays preorder and inorder where preorder is the preorder traversal of a binary tree and inorder is the inorder traversal of the same tree, construct and return the binary tree.

 

Example 1:


Input: preorder = [3,9,20,15,7], inorder = [9,3,15,20,7]
Output: [3,9,20,null,null,15,7]
Example 2:

Input: preorder = [-1], inorder = [-1]
Output: [-1]
 
idea is evrytime we make the root from preorder[idx] and move to next doing idx++ and find the position of current root on inorder
array on the right side of the root everything is right child and left side everything is left child so manage the start end pointer acc to that
 */
class Solution {
public:
    int indexFinder(vector<int>&inorder,int val){
        for (int i=0;i<inorder.size();i++){
            if(inorder[i]==val)return i;
        }
        return 0;
    }
    TreeNode* helper(int start,int end,int &idx,vector<int>&preorder,vector<int>&inorder){
        if(start>end)return NULL;
        TreeNode* root= new TreeNode(preorder[idx]);
        int index=indexFinder(inorder,preorder[idx]);
        idx++;
        root->left=helper(start,index-1,idx,preorder,inorder);
        root->right=helper(index+1,end,idx,preorder,inorder);
        return root;
    }
    TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int start=0;
        int idx=0;
        int end=inorder.size()-1;
        return helper(start,end,idx,preorder,inorder);

    }
};



106. Construct Binary Tree from Inorder and Postorder Traversal
Solved
Medium
Topics
premium lock icon
Companies
Given two integer arrays inorder and postorder where inorder is the inorder traversal of a binary tree and postorder is the postorder traversal of the same tree, construct and return the binary tree.

 

Example 1:


Input: inorder = [9,3,15,20,7], postorder = [9,15,7,20,3]
Output: [3,9,20,null,null,15,7]
Example 2:

Input: inorder = [-1], postorder = [-1]
Output: [-1]


class Solution {
public:
TreeNode* solve(int &idx,int start,int end,vector<int>&inorder,vector<int>&postorder){
    if(start>end)return NULL;
    TreeNode* root=new TreeNode(postorder[idx]);
    idx--;
    int index=0;
    for (int i=0;i<inorder.size();i++){
        if(inorder[i]==root->val){
            index=i;break;
        }
    }

    root->right=solve(idx,index+1,end,inorder,postorder);
    root->left=solve(idx,start,index-1,inorder,postorder);
    return root;
}
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int n=inorder.size();
        int start=0;
        int end=n-1;
        int idx=n-1;
        return solve(idx,start,end,inorder,postorder);
    }
};


236. Lowest Common Ancestor of a Binary Tree
Solved
Medium
Topics
premium lock icon
Companies
Given a binary tree, find the lowest common ancestor (LCA) of two given nodes in the tree.

According to the definition of LCA on Wikipedia: “The lowest common ancestor is defined between two nodes p and q as the lowest node in T that has both p and q as descendants (where we allow a node to be a descendant of itself).”

 

Example 1:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], p = 5, q = 1
Output: 3
Explanation: The LCA of nodes 5 and 1 is 3.


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode(int x) : val(x), left(NULL), right(NULL) {}
 * };
 */
class Solution {
public:
    TreeNode* lca(TreeNode* root,TreeNode* p,TreeNode* q){
        if(!root)return NULL;
        if(root->val==p->val || root->val==q->val)return root;

        TreeNode* rootLeft=lca(root->left,p,q);
        TreeNode* rootRight=lca(root->right,p,q);

        if(rootLeft && rootRight)return root;
        if(rootRight) return rootRight;
        return rootLeft;

    }
    TreeNode* lowestCommonAncestor(TreeNode* root, TreeNode* p, TreeNode* q) {
        return lca(root,p,q);
        
    }
};


958. Check Completeness of a Binary Tree
Solved
Medium
Topics
premium lock icon
Companies
Given the root of a binary tree, determine if it is a complete binary tree.

In a complete binary tree, every level, except possibly the last, is completely filled, and all nodes in the last level are as far left as possible. It can have between 1 and 2h nodes inclusive at the last level h.

 

Example 1:


Input: root = [1,2,3,4,5,6]
Output: true
Explanation: Every level before the last is full (ie. levels with node-values {1} and {2, 3}), and all nodes in the last level ({4, 5, 6}) are as far left as possible.
Example 2:


Input: root = [1,2,3,4,5,null,7]
Output: false
Explanation: The node with value 7 isn't as far left as possible.'

 
class Solution {
public:
//question every valid(not NUll) node if they have seen Null before while doing bfs from l to r
//if yse return false (not complete) else true
    bool isCompleteTree(TreeNode* root) {
        if(root==NULL)return true;
        queue<TreeNode*>q;
        bool past =false;
        q.push(root);
        while(!q.empty()){
            auto node=q.front();
            //cout<<"hi";
            q.pop();
            if(node==NULL){
                past=true;
                //cout<<"{}"<<" ";
            }else{
               // cout<<node->val<<" ";
                if(past)return false;
                q.push(node->left);
                q.push(node->right);
            }
        }
        return true;
        
        
    }
};


1110. Delete Nodes And Return Forest
Solved
Medium
Topics
premium lock icon
Companies
Given the root of a binary tree, each node in the tree has a distinct value.

After deleting all nodes with a value in to_delete, we are left with a forest (a disjoint union of trees).

Return the roots of the trees in the remaining forest. You may return the result in any order.

 

Example 1:


Input: root = [1,2,3,4,5,6,7], to_delete = [3,5]
Output: [[1,2,null,4],[6],[7]]
Example 2:

Input: root = [1,2,4,null,3], to_delete = [3]
Output: [[1,2,4]]
 

Constraints:

The number of nodes in the given tree is at most 1000.
Each node has a distinct value between 1 and 1000.
to_delete.length <= 1000
to_delete contains distinct values between 1 and 1000.

/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    TreeNode* solve(TreeNode* root,vector<TreeNode*>&res,unordered_map<int,bool>&mp){
        if(!root)return NULL;
        root->left=solve(root->left,res,mp);
        root->right=solve(root->right,res,mp);
        
        if(mp[root->val]){
            if(root->left)res.push_back(root->left);
            if(root->right)res.push_back(root->right);
            return NULL;
        }
        return root;

    }
     
     //delete the nodes in the back tracking step as then if there is something to be deleted on the lower portion then
     //they are already been deleted and now you can delete the top one
    //other wise if you delete from the top then the link will be broken and you will not be able to delete the lower element
    vector<TreeNode*> delNodes(TreeNode* root, vector<int>& to_delete) {
        vector<TreeNode*>res;
        unordered_map<int,bool>mp;
        for (auto it :to_delete){
            mp[it]=true;
        }
        solve(root,res,mp);
        if(!mp[root->val])res.push_back(root);
        return res;
        
    }
};





814. Binary Tree Pruning
Solved
Medium
Topics
premium lock icon
Companies
Given the root of a binary tree, return the same tree where every subtree (of the given tree) not containing a 1 has been removed.

A subtree of a node node is node plus every node that is a descendant of node.

 

Example 1:


Input: root = [1,null,0,0,1]
Output: [1,null,0,null,1]
Explanation: 
Only the red nodes satisfy the property "every subtree not containing a 1".
The diagram on the right represents the answer.
Example 2:


Input: root = [1,0,1,0,0,0,1]
Output: [1,null,1,null,1]


class Solution {
public:
TreeNode* solve(TreeNode * root){
    if(!root)return NULL;
//this is same as one we have done before that is prone the nodes in the backtracking step
//so it will only prone cureent node if only the nodes lower than me are processed
    root->left=solve(root->left);
    root->right=solve(root->right);

    if(!root->left && !root->right && !root->val)return NULL;
    return root;
}
    TreeNode* pruneTree(TreeNode* root) {
        return solve(root);
    }
};





112. Path Sum
Solved
Easy
Topics
premium lock icon
Companies
Given the root of a binary tree and an integer targetSum, return true if the tree has a root-to-leaf path such that adding up all the values along the path equals targetSum.

A leaf is a node with no children.

 

Example 1:


Input: root = [5,4,8,11,null,13,4,7,2,null,null,null,1], targetSum = 22
Output: true
Explanation: The root-to-leaf path with the target sum is shown.
Example 2:


Input: root = [1,2,3], targetSum = 5
Output: false
Explanation: There are two root-to-leaf paths in the tree:
(1 --> 2): The sum is 3.
(1 --> 3): The sum is 4.
There is no root-to-leaf path with sum = 5.
Example 3:

Input: root = [], targetSum = 0
Output: false
Explanation: Since the tree is empty, there are no root-to-leaf paths.



class Solution {
public:
    bool solve(TreeNode* root,int curSum,int &targetSum){
        if(!root)return false;
        curSum+=root->val;
        if(!root->left && !root->right){
            return curSum==targetSum;
        }
        //here when we are on the leaf node we already have the sum calculated including that node
        //so we can check the sum and (also return) from that without thinking about making any change to curSum in the 
        //backtracking step bcz curSum here is passed by value not refernce so it will already have prev state val when
        //returned to that state
        return solve(root->left,curSum,targetSum)||solve(root->right,curSum,targetSum);
        
    }
    bool hasPathSum(TreeNode* root, int targetSum) {
        return solve(root,0,targetSum);
        
    }
};

113. Path Sum II
Solved
Medium
Topics
premium lock icon
Companies
Given the root of a binary tree and an integer targetSum, return all root-to-leaf paths where the sum of the node values in the path equals targetSum. Each path should be returned as a list of the node values, not node references.

A root-to-leaf path is a path starting from the root and ending at any leaf node. A leaf is a node with no children.

 

Example 1:


Input: root = [5,4,8,11,null,13,4,7,2,null,null,5,1], targetSum = 22
Output: [[5,4,11,2],[5,8,4,5]]
Explanation: There are two paths whose sum equals targetSum:
5 + 4 + 11 + 2 = 22
5 + 8 + 4 + 5 = 22


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void solve(TreeNode* root,int &sum,vector<int>&curPath,vector<vector<int>>&paths,int &target){
        if(!root)return;
        curPath.push_back(root->val);
        sum+=root->val;
        solve(root->left,sum,curPath,paths,target);
        solve(root->right,sum,curPath,paths,target);
        //you should remember that you are only leaving the value of node when you are going back from node
        if(!root->left && !root->right){

            if(sum==target){
                paths.push_back(curPath);
            }
        }
        sum-=root->val;
        curPath.pop_back();
        return;
    }
    vector<vector<int>> pathSum(TreeNode* root, int target) {
        vector<int>curPath;
        vector<vector<int>>paths;
        int sum=0;
        solve(root,sum,curPath,paths,target);
        return paths;

        
    }
};


437. Path Sum III
Solved
Medium
Topics
premium lock icon
Companies
Given the root of a binary tree and an integer targetSum, return the number of paths where the sum of the values along the path equals targetSum.

The path does not need to start or end at the root or a leaf, but it must go downwards (i.e., traveling only from parent nodes to child nodes).

 

Example 1:


Input: root = [10,5,-3,3,2,null,11,3,-2,null,1], targetSum = 8
Output: 3
Explanation: The paths that sum to 8 are shown.


class Solution {
public:
//no of subarray sum equal to target sum concept used
    int solve(TreeNode* root,int & targetSum,long long curSum,unordered_map<long long,int>&mp){
        if(!root)return 0;
        curSum+=root->val;
        int cnt=0;
        if(curSum==targetSum)cnt++;
        if(mp.find(curSum-targetSum)!=mp.end()){
            cnt+=mp[curSum-targetSum];
        }
        mp[curSum]++;
        cnt+=solve(root->left,targetSum,curSum,mp);
        cnt+=solve(root->right,targetSum,curSum,mp);
        mp[curSum]--;
        return cnt;

    }
    int pathSum(TreeNode* root, int targetSum) {
        unordered_map<long long,int>mp;
        return solve(root,targetSum,0,mp);

    }
};


Code
Testcase
Testcase
Test Result
623. Add One Row to Tree
Solved
Medium
Topics
premium lock icon
Companies
Given the root of a binary tree and two integers val and depth, add a row of nodes with value val at the given depth depth.

Note that the root node is at depth 1.

The adding rule is:

Given the integer depth, for each not null tree node cur at the depth depth - 1, create two tree nodes with value val as cur's left subtree root and right subtree root.
cur's original left subtree should be the left subtree of the new left subtree root.
cur's original right subtree should be the right subtree of the new right subtree root.
If depth == 1 that means there is no depth depth - 1 at all, then create a tree node with value val as the new root of the whole original tree, and the original tree is the new root's left subtree.
 

Example 1:


Input: root = [4,2,6,3,1,5], val = 1, depth = 2
Output: [4,1,1,2,null,null,6,3,1,5]

class Solution {
public:
TreeNode* solve(TreeNode* root,int val,int curDepth,int depth){
    if(!root)return NULL;

    if(curDepth==depth){
        TreeNode* leftTree=root->left;
        TreeNode* rightTree=root->right;
        TreeNode* temp1=new TreeNode(val);
        TreeNode* temp2=new TreeNode(val);
        root->left=temp1;
        root->right=temp2;
        temp1->left=leftTree;
        temp2->right=rightTree;
    }
    root->left=solve(root->left,val,curDepth+1,depth);
    root->right=solve(root->right,val,curDepth+1,depth);
    return root;

}
    TreeNode* addOneRow(TreeNode* root, int val, int depth) {
        if(depth==1){
            TreeNode* head=new TreeNode(val);
            head->left=root;
            return head;
        }
        return solve(root,val,1,depth-1);
    }
};


1026. Maximum Difference Between Node and Ancestor
Solved
Medium
Topics
premium lock icon
Companies
Hint
Given the root of a binary tree, find the maximum value v for which there exist different nodes a and b where v = |a.val - b.val| and a is an ancestor of b.

A node a is an ancestor of b if either: any child of a is equal to b or any child of a is an ancestor of b.

 

Example 1:


Input: root = [8,3,10,1,6,null,14,null,null,4,7,13]
Output: 7
Explanation: We have various ancestor-node differences, some of which are given below :
|8 - 3| = 5
|3 - 7| = 4
|8 - 1| = 7
|10 - 13| = 3
Among all possible differences, the maximum value of 7 is obtained by |8 - 1| = 7.


class Solution {
public:
TreeNode* solve(TreeNode* root,int maxi,int mini,int &res){
    if(!root)return NULL;
    res=max(res,abs(root->val-maxi));
    res=max(res,abs(root->val-mini));
    root->left=solve(root->left,max(maxi,root->val),min(mini,root->val),res);
    root->right=solve(root->right,max(maxi,root->val),min(mini,root->val),res);
    return root;

}
    int maxAncestorDiff(TreeNode* root) {
        //maintain max and min (when you aare on top of a node then max and min upto that node excluding that node 
        //should be computed) and evrytime you visit any node take the max of diff ****/and use maxi and mini call by value
        //***then you do not need to manage them in the backtracking step*****/
        int res=0;
        solve(root,root->val,root->val,res);
        return res;
        
    }
};


1339. Maximum Product of Splitted Binary Tree
Solved
Medium
Topics
premium lock icon
Companies
Hint
Given the root of a binary tree, split the binary tree into two subtrees by removing one edge such that the product of the sums of the subtrees is maximized.

Return the maximum product of the sums of the two subtrees. Since the answer may be too large, return it modulo 109 + 7.

Note that you need to maximize the answer before taking the mod and not after taking it.

 

Example 1:


Input: root = [1,2,3,4,5,6]
Output: 110
Explanation: Remove the red edge and get 2 binary trees with sum 11 and 10. Their product is 110 (11*10)



class Solution {
public:
const int mod=1e9+7;
    int findSum(TreeNode* root){
        if(!root)return 0;
        int leftTree=findSum(root->left);
        int rightTree=findSum(root->right);
        int sum=root->val+leftTree+rightTree;
        return sum;

    }

    int solve(TreeNode * root,int &totalSum,long long &res){
        if(!root)return 0;
        int leftTree=solve(root->left,totalSum,res);
        int rightTree=solve(root->right,totalSum,res);
        int sum=root->val+leftTree+rightTree;
        int anotherSum=totalSum-sum;
        if(res<(1LL*sum*anotherSum)){
            res=(1LL*sum*anotherSum);
        }
        return sum;
    }
    int maxProduct(TreeNode* root) {
        int totalSum=findSum(root);
        cout<<totalSum;
        long long res=0;
        solve(root,totalSum,res);
        return res%mod;

        
    }
};

//best

124. Binary Tree Maximum Path Sum
Solved
Hard
Topics
premium lock icon
Companies
A path in a binary tree is a sequence of nodes where each pair of adjacent nodes in the sequence has an edge connecting them. A node can only appear in the sequence at most once. Note that the path does not need to pass through the root.

The path sum of a path is the sum of the node's values in the path.

Given the root of a binary tree, return the maximum path sum of any non-empty path.

 

Example 1:


Input: root = [1,2,3]
Output: 6
Explanation: The optimal path is 2 -> 1 -> 3 with a path sum of 2 + 1 + 3 = 6.
Example 2:


Input: root = [-10,9,20,null,null,15,7]
Output: 42
Explanation: The optimal path is 15 -> 20 -> 7 with a path sum of 15 + 20 + 7 = 42.
 

Constraints:

The number of nodes in the tree is in the range [1, 3 * 104].
-1000 <= Node.val <= 1000

'

class Solution {
public:
    int solve(TreeNode* root,int &maxi){
        if(!root)return 0;
        int leftTree=solve(root->left,maxi);
        int rightTree=solve(root->right,maxi);
        //we have 3 case 
        int neche_hi_milgaya_answer=root->val+leftTree+rightTree;//case 1 since answer milgaya to isko or upar nahi vej sakte
        int koi_ek_hi_accha=root->val+max(leftTree,rightTree);//case 2
        int only_root_accha=root->val;//case 3
        maxi=max({maxi,neche_hi_milgaya_answer,koi_ek_hi_accha,only_root_accha});
        
        //only case 2 and case 3 can be returned so that we can further explore
        return max(koi_ek_hi_accha,only_root_accha);

    }
    int maxPathSum(TreeNode* root) {
        int maxi=-1e9;
        solve(root,maxi);
        return maxi;
        
        
    }
};

652. Find Duplicate Subtrees
Solved
Medium
Topics
premium lock icon
Companies
Given the root of a binary tree, return all duplicate subtrees.

For each kind of duplicate subtrees, you only need to return the root node of any one of them.

Two trees are duplicate if they have the same structure with the same node values.

 

Example 1:


Input: root = [1,2,3,4,null,2,4,null,null,4]
Output: [[2,4],[4]]
Example 2:


Input: root = [2,1,1]
Output: [[1]]


class Solution {
public:
    string solve(TreeNode* root,vector<TreeNode*>&res,unordered_map<string,int>&mp){
        if(!root)return "N";
        string s=to_string(root->val)+","+solve(root->left,res,mp)+","+solve(root->right,res,mp);
        if(mp[s]==1){//bcz you donot want to push the tree second time in res
            res.push_back(root);
        }
        mp[s]++;
        return s;
    }
    vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
        unordered_map<string,int>mp;
        vector<TreeNode*>res;
        solve(root,res,mp);
        return res;
        
    }
};


129. Sum Root to Leaf Numbers
Solved
Medium
Topics
premium lock icon
Companies
You are given the root of a binary tree containing digits from 0 to 9 only.

Each root-to-leaf path in the tree represents a number.

For example, the root-to-leaf path 1 -> 2 -> 3 represents the number 123.
Return the total sum of all root-to-leaf numbers. Test cases are generated so that the answer will fit in a 32-bit integer.



 */
class Solution {
public:
    int solve(TreeNode* root,int sum){
        if(root==NULL){
           // cout<<sum<<endl;
            return 0;
        }
        sum=sum*10+root->val;
        int leftTree=solve(root->left,sum);
        int rightTree=solve(root->right,sum);
        if(!root->left && !root->right)return sum;
        return leftTree+rightTree;
    }
    int sumNumbers(TreeNode* root) {
        return solve(root,0);
       
    }
};

 

Example 1:


Input: root = [1,2,3]
Output: 25
Explanation:
The root-to-leaf path 1->2 represents the number 12.
The root-to-leaf path 1->3 represents the number 13.
Therefore, sum = 12 + 13 = 25.
Example 2:


Input: root = [4,9,0,5,1]
Output: 1026
Explanation:
The root-to-leaf path 4->9->5 represents the number 495.
The root-to-leaf path 4->9->1 represents the number 491.
The root-to-leaf path 4->0 represents the number 40.
Therefore, sum = 495 + 491 + 40 = 1026.
 

Constraints:

The number of nodes in the tree is in the range [1, 1000].
0 <= Node.val <= 9
The depth of the tree will not exceed 10.


 */
class Solution {
public:
    int solve(TreeNode* root,int sum){
        if(root==NULL){
           // cout<<sum<<endl;
            return 0;
        }
        sum=sum*10+root->val;
        int leftTree=solve(root->left,sum);
        int rightTree=solve(root->right,sum);
        if(!root->left && !root->right)return sum;
        return leftTree+rightTree;
    }
    int sumNumbers(TreeNode* root) {
        return solve(root,0);
       
    }
};


1372. Longest ZigZag Path in a Binary Tree
Solved
Medium
Topics
premium lock icon
Companies
Hint
You are given the root of a binary tree.

A ZigZag path for a binary tree is defined as follow:

Choose any node in the binary tree and a direction (right or left).
If the current direction is right, move to the right child of the current node; otherwise, move to the left child.
Change the direction from right to left or from left to right.
Repeat the second and third steps until you can't move in the tree.
Zigzag length is defined as the number of nodes visited - 1. (A single node has a length of 0).

Return the longest ZigZag path contained in that tree.

 

Example 1:


Input: root = [1,null,1,1,1,null,null,1,1,null,1,null,null,null,1]
Output: 3
Explanation: Longest ZigZag path in blue nodes (right -> left -> right).
Example 2:


Input: root = [1,1,1,null,1,null,null,1,1,null,1]
Output: 4
Explanation: Longest ZigZag path in blue nodes (left -> right -> left -> right).

'


class Solution {
public:
    void helper(TreeNode* root,int stepCnt,bool goLeft,int & maxi){
       // if(!root)return NULL;
        if(goLeft){
            if(root->left){
                maxi=max(maxi,stepCnt+1);
                helper(root->left,stepCnt+1,false,maxi);

            }
            if(root->right){
                maxi=max(maxi,1);
                helper(root->right,1,true,maxi);

            }

        }
        else{
            if(root->right){
                maxi=max(maxi,stepCnt+1);
                helper(root->right,stepCnt+1,true,maxi);

            }
            if(root->left){
                maxi=max(maxi,1);
                helper(root->left,1,false,maxi);
            }

            
        }

    }
    int longestZigZag(TreeNode* root) {
        int maxi=0;
        helper(root,0,false,maxi);
        helper(root,0,true,maxi);
        return maxi;

        
    }
};

662:Maximum Width of Binary Tree
Solved
Medium
Topics
premium lock icon
Companies
Given the root of a binary tree, return the maximum width of the given tree.

The maximum width of a tree is the maximum width among all levels.

The width of one level is defined as the length between the end-nodes (the leftmost and rightmost non-null nodes), where the null nodes between the end-nodes that would be present in a complete binary tree extending down to that level are also counted into the length calculation.

It is guaranteed that the answer will in the range of a 32-bit signed integer.

 

Example 1:


Input: root = [1,3,2,5,3,null,9]
Output: 4
Explanation: The maximum width exists in the third level with length 4 (5,3,null,9).
Example 2:


Input: root = [1,3,2,5,null,null,9,6,null,7]
Output: 7
Explanation: The maximum width exists in the fourth level with length 7 (6,null,null,null,null,null,7).



class Solution {
public:
    typedef unsigned long long ll;
    int widthOfBinaryTree(TreeNode* root) {
        //here we perform the indexing of the nodes left(2i+1) right (2i+2)
        //and the diff btw left and right +1 is the width of that level take the max of it
        int maxWidth=0;
        queue<pair<TreeNode*,ll>>q;
        q.push({root,0});
        while(!q.empty()){
            ll left=q.front().second;
            ll right=q.back().second;
            maxWidth=max(maxWidth,(int)(right-left+1));

            int n=q.size();
            for (int i=0;i<n;i++){
                auto node=q.front().first;
                auto index=q.front().second;
                q.pop();
                if(node->left){
                    q.push({node->left,2*index+1});
                }
                if(node->right){
                    q.push({node->right,2*index+2});
                }
            }
        }
        return maxWidth;

       
    }
};


1161. Maximum Level Sum of a Binary Tree
Solved
Medium
Topics
premium lock icon
Companies
Hint
Given the root of a binary tree, the level of its root is 1, the level of its children is 2, and so on.

Return the smallest level x such that the sum of all the values of nodes at level x is maximal.

 

Example 1:


Input: root = [1,7,0,7,-8,null,null]
Output: 2
Explanation: 
Level 1 sum = 1.
Level 2 sum = 7 + 0 = 7.
Level 3 sum = 7 + -8 = -1.
So we return the level with the maximum sum which is level 2.


/**
 * Definition for a binary tree node.
 * struct TreeNode {
 *     int val;
 *     TreeNode *left;
 *     TreeNode *right;
 *     TreeNode() : val(0), left(nullptr), right(nullptr) {}
 *     TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
 *     TreeNode(int x, TreeNode *left, TreeNode *right) : val(x), left(left), right(right) {}
 * };
 */
class Solution {
public:
    void solve(TreeNode* root,map<int,int>&mp,int level){
        if(!root)return ;
        mp[level]+=root->val;
        solve(root->left,mp,level+1);
        solve(root->right,mp,level+1);

    }

    int maxLevelSum(TreeNode* root) {
        map<int,int>mp;
       // int height=solve(root,mp);
        int maxi=-1e9;
        int res=1;
        solve(root,mp,1);
        for (auto [x,y]: mp){
            if(y>maxi){
                maxi=y;
                res=x;
            }
        }
        return res;

    }
};


863. All Nodes Distance K in Binary Tree
Solved
Medium
Topics
premium lock icon
Companies
Given the root of a binary tree, the value of a target node target, and an integer k, return an array of the values of all nodes that have a distance k from the target node.

You can return the answer in any order.

 

Example 1:


Input: root = [3,5,1,6,2,0,8,null,null,7,4], target = 5, k = 2
Output: [7,4,1]
Explanation: The nodes that are a distance 2 from the target node (with value 5) have values 7, 4, and 1.


class Solution {
public:
int createPointer(TreeNode*root,unordered_map<TreeNode*,TreeNode*>&mp){
    if(!root)return 0;
    if(root->left){
        mp[root->left]=root;
    }
    int left=createPointer(root->left,mp);
    if(root->right){
        mp[root->right]=root;
    }
    int right=createPointer(root->right,mp);
    return 1+ left+right;

}
    vector<int> distanceK(TreeNode* root, TreeNode* target, int k) {
        //since there is no way we can traverse back so we will create pointer to the parent using map mp[node->left]=node
        unordered_map<TreeNode*,TreeNode*>mp;
        int num=createPointer(root,mp);
        int level=0;
        queue<TreeNode*>q;
        unordered_map<int,bool>vis;
        q.push(target);
        vis[target->val]=1;
        //we use target node as a seed to bfs and process every level at a time if level ==k break out and whatever is
        //in the queue is my answer
        while(!q.empty()){
            if(level==k)break;
            int n=q.size();
            for (int i=0;i<n;i++){
                auto node=q.front();
                q.pop();
                if(node->left && !vis[node->left->val]){
                    vis[node->left->val]=1;
                    q.push(node->left);

                }
                if(node->right && !vis[node->right->val]){
                    vis[node->right->val]=1;
                    q.push(node->right);
                }
                if(mp[node] && !vis[mp[node]->val]){
                    vis[mp[node]->val]=1;
                    q.push(mp[node]);
                }
            }
            level++;
        }
        vector<int>res;
        while(!q.empty()){
            auto node=q.front();
            q.pop();
            res.push_back(node->val);
        }
        return res;
    }
};

1361. Validate Binary Tree Nodes
Solved
Medium
Topics
premium lock icon
Companies
Hint
You have n binary tree nodes numbered from 0 to n - 1 where node i has two children leftChild[i] and rightChild[i], return true if and only if all the given nodes form exactly one valid binary tree.

If node i has no left child then leftChild[i] will equal -1, similarly for the right child.

Note that the nodes have no values and that we only use the node numbers in this problem.

 

Example 1:


Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,-1,-1,-1]
Output: true
Example 2:


Input: n = 4, leftChild = [1,-1,3,-1], rightChild = [2,3,-1,-1]
Output: false
Example 3:


Input: n = 2, leftChild = [1,0], rightChild = [-1,-1]
Output: false


class Solution {
public:
int dfs(int node,vector<vector<int>>&adj,vector<int>&visited){
    int cnt=1;
    visited[node]=1;
    for(auto it : adj[node]){
        if(!visited[it]){
            cnt+=dfs(it,adj,visited);

        }
    }
    return cnt;

}
    bool validateBinaryTreeNodes(int n, vector<int>& leftChild, vector<int>& rightChild) {
        //ther are three cond to be satisfied to be a single binary tree

        //first node should have one parent 
        //there should be one root and 
        // traverse to check all of them connected
        
        //first let's check the parent
        unordered_map<int,int>mp;//childToParent;
        vector<vector<int>>adj(n);

        for (int i=0;i<n;i++){
            int node=i;
            int leftC=leftChild[i];
            int rightC=rightChild[i];
            if(mp.find(leftC)==mp.end()){
                if(leftC!=-1){
                    adj[node].push_back(leftC);
                    mp[leftC]=node;
                }
            }
            else{
                //already a parent exist
                return false;
            }
            if(mp.find(rightC)==mp.end()){
                if(rightC!=-1){
                    adj[node].push_back(rightC);

                    mp[rightC]=node;
                }
            }
            else{
                //already a parent exist
                return false;
            }


        }
        int root=-1;
        for (int i=0;i<n;i++){
            if(mp.find(i)==mp.end()){
                if(root!=-1)return false;
                root=i;
            }
        }
        if(root==-1)return false;
        vector<int>visited(n,0);
        int cnt=dfs(root,adj,visited);
        return cnt==n;


        
    }
};





366. Find Leaves of Binary Tree
Leetcode Link
Given the root of a binary tree, collect a tree's nodes as if you were doing this:

Collect all the leaf nodes.
Remove all the leaf nodes.
Repeat until the tree is empty.
Example 1:
Example 1

Input: root = [1,2,3,4,5]
Output: [[4,5,3],[2],[1]]
Explanation:
[[3,5,4],[2],[1]] and [[3,4,5],[2],[1]] are also considered correct answers since per each level it does not matter the order on which elements are returned.

Solution















