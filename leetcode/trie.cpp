#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;
class Trie{
    struct TrieNode{


        TrieNode *childNodes[26];

        /// 词频统计
        int freq;

        /// 记录该节点的字符
        char nodeChar;

        /// 插入记录时的编码id
        unordered_set<int> hashSet;

        /// 初始化
        /// </summary>
        TrieNode()
        {
            memset(childNodes,0,sizeof(childNodes));
            freq = 0;
        }
    };

    public:
    TrieNode* root=new TrieNode();
    // Trie() {
    //     TrieNode* root=new TrieNode();
    // }
    

    void AddTrieNode(TrieNode *root, string word, int id)
    {
        if (word.size() == 0)
            return;

        //求字符地址，方便将该字符放入到26叉树中的哪一叉中
        int k = word[0] - 'a';

        //如果该叉树为空，则初始化
        if (root->childNodes[k] == NULL)
        {
            root->childNodes[k] = new TrieNode();

            //记录下字符
            root->childNodes[k]->nodeChar = word[0];
        }

        //该id途径的节点
        root->childNodes[k]->hashSet.insert(id);

        string nextWord = word.substr(1);

        //说明是最后一个字符，统计该词出现的次数
        if (nextWord.size() == 0)
            root->childNodes[k]->freq++;

        AddTrieNode(root->childNodes[k], nextWord, id);
    }

    int search(string word){
        if (word.size() == 0)
            return 0;
        TrieNode *cur = root;
        for(int i=0;i<word.size();i++){
            if(cur->childNodes[word[i]-'a']==NULL)
                return 0;
            cur=cur->childNodes[word[i]-'a'];
        }
        return cur->freq;

    }
      

    void DeleteTrieNode(TrieNode *root, string word, int id)
    {
        if (word.size() == 0)
            return;

        //求字符地址，方便将该字符放入到26叉树种的哪一颗树中
        int k = word[0] - 'a';

        //如果该叉树为空,则说明没有找到要删除的点
        if (root->childNodes[k] == NULL)
            return;

        string nextWord = word.substr(1);

        //如果是最后一个单词，则减去词频
        if (word.size() == 0 && root->childNodes[k]->freq > 0)
            root->childNodes[k]->freq--;

        //删除途经节点
        root->childNodes[k]->hashSet.erase(id);

        DeleteTrieNode(root->childNodes[k], nextWord, id);
    }

    
};

int main(int argc, char *argv[])
    {
        Trie *trie = new Trie();

        vector<string> v={"cpple","banana","pineapple","cpple"};
        for (int i=0;i<v.size();i++)
        {

            trie->AddTrieNode(trie->root,v[i], i);
        }
        int a=trie->search("cpple");
        int b=0;
        // printf(a);
        // printf("耗费时间:{0}", System.time());

        // printf("\n\ngo 出现的次数为:{0}\n\n", trie.WordCount("go"));
        return 0;
    }