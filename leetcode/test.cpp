#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include <set>
#include <stack>
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
    vector<int> countSmaller(vector<int>& nums) {
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

};
int main(){
    Solution *s=new Solution();
    // s->removeInvalidParentheses(")(");

    // s->summaryRanges(v);
    // s->isAdditiveNumber("101");
    int x[12]={0,1,0,2,1,0,1,3,2,1,2,1};
    vector<int> a(x,x+12);
    // s->largestRectangleArea(a);
    s->trap(a);

    int x1[4]={5,2,6,1};
    vector<int> b(x1,x1+4);
    s->countSmaller(b);

}

