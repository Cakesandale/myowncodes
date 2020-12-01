
#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

class Solution {
public:
    string shortestPalindrome(string s) {
        string s2=s;
        reverse(s2.begin(),s2.end());
        string ss=s+'*'+s2;
        int m=s.size(),n=ss.size();
        int i=0,j=-1;
        vector<int> next(n+1,0);
        next[0]=-1;
        while(i<n){
            if(j==-1 || ss[i]==ss[j]){
                i++;
                j++;
                next[i]=j;
            }
            else
                j=next[j];
        }
        return s2.substr(0,m-next[n-1])+s;
    }
};

int main(int argc, char *argv[]){
    Solution *solu=new Solution();
    string a=solu->shortestPalindrome("aacecaaa");
    cout<<a;
}


