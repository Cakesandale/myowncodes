#include <iostream>
#include<vector>
#include <stack>

using namespace std;

class KSP_Node
{
private:
    /* data */
    int id;
    vector<int> in_arc;
    vector<int> out_arc;
public:
    KSP_Node(/* args */);
    ~KSP_Node();
};

KSP_Node::KSP_Node(/* args */)
{
}

KSP_Node::~KSP_Node()
{
}
