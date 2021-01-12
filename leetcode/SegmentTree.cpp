// 现有如下的问题，给定一个的序列，实现以下操作：

// ①更新序列的某个值。

// ②查询序列的某个区间的最小值(最大值、区间和)线段树常用于解决区间统计问题。求最值，区间和等操作均可使用该数据结构。

// ③更新序列的某个区间内的所有值。
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include <set>
using namespace std;

class SegmentTree{
    struct SegTree{
        int start,end,sum;
        SegTree* left;
        SegTree* right;
        SegTree(int a,int b):start(a),end(b),sum(0),left(nullptr),right(nullptr){}
    };
    public:
    SegTree* buildTree(vector<int> &nums,int a,int b){
        if(a>b) return nullptr;
        SegTree* root=new SegTree(a,b);
        if(a==b){
            root->sum=nums[a];
            return root;
        }
        int mid=(a+b)/2;
        root->left=buildTree(nums,a,mid);
        root->right=buildTree(nums,mid+1,b);
        root->sum=root->left->sum+root->right->sum;
        return root;
    }
    int modifyTree(int i, int val, SegTree* root){
        if(root==nullptr) return 0;
        int diff;
        if(root->start==i && root->end==i){
            diff=val-root->sum;
            root->sum=val;
            return diff;
        }
        int mid=(root->start+root->end)/2;
        if(i<=mid){
            diff=modifyTree(i,val,root->left);
        }
        else{
            diff=modifyTree(i,val,root->right);
        }
        root->sum+=diff;
        return diff;
    }
    int searchTree(int i, int j, SegTree* root){
        if(root==nullptr) return 0;
        if(i==root->start && j==root->end) return root->sum;
        int mid=(root->start + root->end)/2;
        if(j<=mid){
            return searchTree(i,j,root->left);
        }
        else if(i>mid){
            return searchTree(i,j,root->right);
        }
        return searchTree(i,mid,root->left) + searchTree(mid+1,j,root->right);

    }    

    //leetcode 307:
    
    SegTree* root;
    void build(vector<int>& nums) {
        int n=nums.size();
        root=buildTree(nums,0,n-1);
    }
    void update(int i, int val) {
        modifyTree(i,val,root);
    }
    
    int sumRange(int i, int j) {
        return searchTree(i,j,root);
    }


};
int main(){
    SegmentTree *s=new SegmentTree();
    vector<int> a({1,1,2,3,5,8});
    s->build(a);
}



