#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include <set>
#include <stack>
#include <unordered_map>
using namespace std;

class Solution {
public:
    // vector<string> summaryRanges(vector<int>& nums) {
    //     int n=nums.size();
    //     vector<string> re;
    //     if(n==0) return re;
    //     for(int i=0;i<n;){
    //         int start=i,end=i;
    //         while(nums[end]+1==nums[end+1] && end+1<n) end++;
    //         if(end!=start) re.push_back(to_string(nums[start])+"->"+to_string(nums[end]));
    //         else re.push_back(to_string(nums[start]));
    //         i=end+1;
    //     }
    //     return re;
    // }

    vector<string> removeInvalidParentheses(string s) {
        vector<string> re;
        queue<string> q;
        set<string> visited;
        if(s.size()==0) return re;
        q.push(s);
        visited.insert(s);
        bool flag=false;
        while(!q.empty()){
            string cur = q.front();
            q.pop();
            if(isvalid(cur)){
                re.push_back(cur);
                flag=true;
            }
            if(flag) continue;
            for(int i=0;i<cur.size();i++){
                if(cur[i]!='(' && cur[i]!=')')
                    continue;
                string a=s.substr(0,i);
                string b = s.substr(i+1);
                string cur2=""+s.substr(0,i)+s.substr(i+1);
                
                if(visited.find(cur2)==visited.end()){
                    q.push(cur2);
                    visited.insert(cur2);
                }
            }
        }
        return re;
    }
    bool isvalid(string& cur){
        int count=0;
        for(int i=0;i<cur.size();i++){
            if(cur[i]=='(') count++;
            if(cur[i]==')' && count--==0) return false;
        }
        return count==0;
    }

    //306
    bool isAdditiveNumber(string num) {
        for(int i=1;i<=num.size()/2;i++){
            for(int j=1;j<=(num.size()-i)/2;j++){
                if(check(num.substr(0,i),num.substr(i,j),num.substr(i+j))) return true;
            }
        }
        return false;
    }
    bool check(string s1,string s2, string s3){
        if(s1.size()>0&&s1[0]=='0' || s2.size()>0&&s2[0]=='0') return false;
        long re=stol(s1)+stol(s2);
        string sum=to_string(re);
        if(sum==s3) return true;
        if(sum.size()>s3.size() || sum.compare(s3.substr(0,sum.size()))!=0) return false;
        else return check(s2,sum,s3.substr(sum.size()));
    }
    //84
    int largestRectangleArea(vector<int>& heights) {
        int maxa=0;
        stack<int> stk;
        for(int i=0;i<=heights.size();i++){
            int h=(i==heights.size()?0:heights[i]);
            if(stk.empty() || heights[stk.top()]<=h){
                stk.push(i);
            }else{
                int cur=stk.top();
                stk.pop();
                maxa=max(maxa,(i-(stk.empty()?-1:stk.top())-1)*heights[cur]);
                i--;
            }
        }
        return maxa;
    }
    //42
    int trap(vector<int>& height) {
        if(height.size()==0){
            return 0;
        }
        int re=0,i=0;
        stack<int> stk;
        while(i<height.size()){
            if(stk.empty() || height[stk.top()]>=height[i])
                stk.push(i++);
            else{
                int m=stk.top();
                stk.pop();
                int curmax=stk.empty()?0:(i-stk.top()-1)*(min(height[i],height[stk.top()])-height[m]);
                re+=curmax;
            }
        }
        return re;
    }
//46
    int jump(vector<int>& nums) {
        int n=nums.size();
        if(n==0) return 0;
        vector<int> re(n,n+1);
        re[0]=0;
        for(int i=0;i<n;i++){
            
            for(int j=1;j<=nums[i];j++){
                if(i+j>n) return min(re[n-1],re[i]+1);
                else
                    re[i+j]=min(re[i+j],re[i]+1);
            }
        }
        return re[n-1];
    }

//309
    int maxProfit(vector<int>& prices) {
        int n = prices.size();
        if(n<2) return 0;
        vector<int> buy(n,0);
        vector<int> sell(n,0);
        buy[0]=-prices[0];
        for(int i=1;i<n;i++){
            int presell=(i-2<0)?0:sell[i-2];
            buy[i]=max(presell-prices[i],buy[i-1]);
            sell[i]=max(sell[i-1],buy[i-1]+prices[i]);
        }
        return sell[n-1];
    }
    //300
    int lengthOfLIS(vector<int>& nums) {
        int n=nums.size();
        if(n==0) return 0;
        vector<int> tails(n,0);
        int size=0;
        for(int m:nums){
            int i=0,j=size;
            while(i<j){
                int mid=(i+j)/2;
                if(tails[mid]<m)
                    i=mid+1;
                else
                    j=mid;
            }
            tails[i]=m;
            if(i==size) size++;
        }
        return size;
    }
    int maxCoinsDP(vector<int> &iNums) {
        int n=iNums.size();
        if(n==0) return 0;
        
        vector<int> nums;
        
        nums.push_back(1);
        for(int i=0;i<n;i++){
            nums.push_back(iNums[i]);
        }
        nums.push_back(1);
        n=n+2;
        vector< vector<int> > dp(n,vector<int>(n,0));
        for(int k=1;k<n;k++){
            for(int left=1;left<n-k-1;left++){
                int right=left+k;
                for(int i=left;i<=right;i++){
                    dp[left][right]=max(dp[left][right],nums[left-1]*nums[i]*nums[right+1]
                    +dp[left][i-1]+dp[i+1][right]);
                }
            }
        }
        return dp[1][n-2];
    }

    //315
    vector<int> countSmaller1(vector<int>& nums) {
        vector<int> re;
        vector<int> num2;
        for(int i= nums.size()-1;i>=0;i--){
            int cnt=insert_find(num2,nums[i]);
            re.insert(re.begin(),cnt);
        }
        return re;
    }
    int insert_find(vector<int>& re, int m){
        int start=0,end=re.size()-1;
        if(re.size()==0){
            re.push_back(m);
            return 0;
        }
        else if(re[end]<m){
            re.push_back(m);
            return re.size()-1;
        }else if(re[0]>m){
            re.insert(re.begin(),m);
            return 0;
        }
        // int start=0,end=re.size()-1;
        while(start<end){
            int mid=(start+end)/2;
            if(re[mid]<m)
                start=mid+1;
            else
                end=mid;
        }
        if(re[start]>=m){
            re.insert(re.begin()+start,m);
            return start;
        }
        re.insert(re.begin()+end,m);
        return end;
        // re.push_back(m);
        // int index=re.size()-1;
        // for(;re[index-1]>m&&index>0;index--){
        //     re[index]=re[index-1];
        // }
        // re[index]=m;
        // return index;
    }

    struct BST{
        BST *left,*right;
        int val,sum,dup=1;
        BST(int a,int b):val(a),sum(b){};
    };
    vector<int> countSmaller(vector<int>& nums) {
        size_t n=nums.size();
        vector<int> re(n,0);
        BST *root=NULL;
        for(int i=n-1;i>=0;i--){
            root=insert(re,nums[i],i,root,0);
        }
        return re;
    }
    BST* insert(vector<int>& re,int m, int i, BST* root, int presum){
        if(root==NULL){
            root=new BST(m,0);
            re[i]=presum;
        }else if(root->val==m){
            root->dup++;
            re[i]=root->sum+presum;
        }else if(root->val > m){
            root->sum++;
            root->left=insert(re,m,i,root->left,presum);
        }else{
            root->right=insert(re,m,i,root->right,presum+root->sum+root->dup);
        }
        return root;
    }

//321
vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
        int n=nums1.size();
        int m=nums2.size();
        vector<int> re(k,0);
        for(int i=max(0,k-m);i<=k&&i<=n;i++){
            vector<int> candi=merge(getmax(nums1,i),getmax(nums2,k-i));
            if(greater(candi,re)) re=candi;
        }
        return re;
    }
    vector<int> getmax(vector<int>& nums,int k){
        vector<int> ans(k,0);
        size_t n=nums.size();
        int i=0;
        for(int j=0;j<n;j++){
            while(i>0 && n-j+i>k && nums[j]>ans[i-1]) i--;
            if(i<k) ans[i++]=nums[j];
        }
        return ans;
    }
    bool greater(vector<int> a1,vector<int> a2){
        size_t n=a1.size();
        bool flag=false;
        for(int i=0;i<n;i++){
            if(a1[i]>a2[i]){
                flag=true;
                break;
            }else if(a1[i]<a2[i]){
                flag=false;
                break;
            }
        }
        return flag;
    }
    vector<int> merge(vector<int> a1, vector<int> a2){
        if(a1.size()==0) return a2;
        else if(a2.size()==0) return a1;
        int i=0,j=0;
        vector<int> re;
        while(i<a1.size() && j<a2.size()){
            if(a1[i]>=a2[j])
                re.push_back(a1[i++]);
            else
                re.push_back(a2[j++]);
        }
        while(i<a1.size()){
            re.push_back(a1[i++]);
        }
        while(j<a2.size()){
            re.push_back(a2[j++]);
        }
        return re;
    }

vector<int> combine(vector<int> &a, int m, vector<int> &b,int n){
    int N=a.size();
    m=m-1;
    n=n-1;
    for(int i=N-1;i>=0;i--){
        if(m<0){
            a[i]=b[n--];
            continue;
        }
        if(n<0){
            a[i]=a[m--];
            continue;
        }
        if(a[m]<b[n]){
            a[i]=b[n--];
        }else{
            a[i]=a[m--];
        }
    }
    return a;
}
    
};

bool checkInclusion(string s1, string s2) {
        int m=s1.size();
        int n = s2.size();

        if(m>n) return false;
        unordered_map<char,int> t,win;
        for(char c:s1)
            t[c]++;
        int left=0, right = 0;
        int cnt=0;
        while(right<n){
            char c=s2[right];
            right++;
            if(t.count(c)){
                win[c]++;
                cnt++;
            }
            while(right-left>=m){
                if(cnt=t.size())
                    return true;
                left++;
                char d=s2[left];
                if(t.count(d)){
                    if(win[d]==t[d])
                        cnt--;
                    win[d]--;
                }
            }
        }
        return false;
    }



int main(){
    Solution *s=new Solution();
    // s->removeInvalidParentheses(")(");

    // s->summaryRanges(v);
    // s->isAdditiveNumber("101");
    // int x[4]={186,419,83,408};
    int x[6]={1,2,3,0,0,0};
    vector<int> a(x,x+6);
    // s->largestRectangleArea(a);
    // s->trap(a);

    int x1[3]={2,5,6};
    vector<int> b(x1,x1+3);
    // s->countSmaller(b);

    s->combine(a,3,b,3);

}

