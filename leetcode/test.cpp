#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
#include <queue>
#include <set>
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
};
int main(){
    Solution *s=new Solution();
    s->removeInvalidParentheses(")(");

    // s->summaryRanges(v);
}