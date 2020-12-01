#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

struct TreeNode{
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode(int x): val(x),left(NULL), right(NULL) {};
};

class MorrisTraversal{
    void inorder(TreeNode* root){
        TreeNode* cur=root;
        TreeNode* pre=NULL;
        while(cur!=NULL){
            if(cur->left==NULL){
                printf("val:%d",cur->val);
                cur=cur->right;
            }
            else{
                pre=cur->left;
                while(pre->right!=NULL && pre->right!=cur) pre=pre->right;
                if(pre->right==NULL){
                    pre->right=cur;
                    cur=cur->left;
                }
                else{
                    pre->right=NULL;
                    printf("val:%d",cur->val);
                    cur=cur->right;
                }
            }
        }
    }


    void preoder(TreeNode* root){
        TreeNode* cur=root;
        TreeNode* pre=NULL;
        while(cur!=NULL){
            if(cur->left==NULL){
                printf("%d",cur->val);
                cur=cur->right;
            }else{
                pre=cur->left;
                while(pre->right!=NULL && pre->right!=cur){
                    pre=pre->right;
                }
                if(pre->right==NULL){
                    pre->right=cur;
                    printf("%d",cur->val);
                    cur=cur->left;
                }else{
                    pre->right=NULL;
                    cur=cur->right;
                }
            }
        }
    }


    void postorder(TreeNode* root){
        TreeNode *dump(0);
        dump->left=root;
        TreeNode* cur=dump;
        TreeNode* pre=NULL;
        while(cur!=NULL){
            if(cur->left==NULL){
                cur=cur->right;
            }
            else{
                pre=cur->left;
                while(pre->right!=NULL && pre->right!=cur){
                    pre=pre->right;
                }
                if(pre->right==NULL){
                    pre->right=cur;
                    cur=cur->left;
                }else{
                    printReverse(cur->left,pre);
                    pre->right=NULL;
                    cur=cur->right;
                }
            }
        }
    }
    void printReverse(TreeNode* start,TreeNode* end){
        reverse(start,end);
        TreeNode* p=end;
        while(true){
            printf("%d",p->val);
            if(p==start) break;
            p=p->right;
        }
        reverse(end,start);
    }
    void reverse(TreeNode* start,TreeNode* end){
        if(start==end) return;
        TreeNode* x=start, *y=start->right, *z;
        while(true){
            z=y->right;
            y->right=x;
            x=y;
            y=z;
            if(x==end) break;
        }
    }
};


