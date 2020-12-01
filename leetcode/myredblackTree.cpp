#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;


enum RBTColor{RED, BLACK};

template <class T>
class RBTNode{
    public:
        RBTColor color;    // 颜色
        T key;            // 关键字(键值)
        RBTNode *left;    // 左孩子
        RBTNode *right;    // 右孩子
        RBTNode *parent; // 父结点

        RBTNode(T value, RBTColor c, RBTNode *p, RBTNode *l, RBTNode *r):
            key(value),color(c),parent(),left(l),right(r) {}
};


template<class T>
class redblackTree{
private:

    RBTNode<T> *mRoot;    // 根结点
public:
    redblackTree();
    ~redblackTree();

    // (递归实现)查找"红黑树"中键值为key的节点
    RBTNode<T>* search(T key);
    // (非递归实现)查找"红黑树"中键值为key的节点
    RBTNode<T>* iterativeSearch(T key);

    // 将结点(key为节点键值)插入到红黑树中
    void insert(T key);
    // 删除结点(key为节点键值)
    void remove(T key);
    
private:
    // 插入函数
    void insert(RBTNode<T>* &root, RBTNode<T>* node);
    // 插入修正函数
    void insertFixUp(RBTNode<T>* &root, RBTNode<T>* node);
    // 删除函数
    void remove(RBTNode<T>* &root, RBTNode<T> *node);
    // 删除修正函数
    void removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent);

    // 左旋
    void rotateLeft(RBTNode<T>* &root, RBTNode<T>* x);
    // 右旋
    void rotateRight(RBTNode<T>* &root, RBTNode<T>* y);  
};

template <class T>
void redblackTree<T>::rotateLeft(RBTNode<T>* &root,RBTNode<T>* p){
    if(p!=NULL){
        TT right=p->right;
        p->right=right->left;
        if(right->left!=NULL)
            right->left->parent=p;
        right->parent=p->parent;
        if(p->parent==NULL)
            root=right;
        else{
            
            if(p->parent->left==p)
                p->parent->left=right;
            else
            {
                p->parent->right=right;
            }
        }
        p->parent=right;
        right->left=p;
    }
}

template<typename T>
void rotateright(RBTNode<T>* &root,RBTNode<T>* p){
    if(p!=NULL){
        T left=p->left;
        p->left=left->right;
        if(left->right!=NULL)
            left->right->parent=p;
        left->parent=p->parent;
        if(p->parent==NULL)
            root=left;
        else{
            
            if(p->parent->left==p)
                p->parent->left=left;
            else
            {
                p->parent->right=left;
            }
        }
        p->parent=left;
        left->right=p;
    }
}

template <class T>
void insert(RBTNode<T>* &root, RBTNode<T>* node)
{
    RBTNode<T> *y = NULL;
    RBTNode<T> *x = root;

    // 1. 将红黑树当作一颗二叉查找树，将节点添加到二叉查找树中。
    while (x != NULL)
    {
        y = x;
        if (node->key < x->key)
            x = x->left;
        else
            x = x->right;
    }

    node->parent = y;
    if (y!=NULL)
    {
        if (node->key < y->key)
            y->left = node;
        else
            y->right = node;
    }
    else
        root = node;

    // 2. 设置节点的颜色为红色
    node->color = RED;

    // 3. 将它重新修正为一颗二叉查找树
    insertFixUp(root, node);
}
template <class T>
void insert(T key)
{
    RBTNode<T> *z=NULL;

    // 如果新建结点失败，则返回。
    if ((z=new RBTNode<T>(key,BLACK,NULL,NULL,NULL)) == NULL)
        return ;

    insert(mRoot, z);
}

template <class T>
void insertFixUp(RBTNode<T>* &root, RBTNode<T>* node)
{
    RBTNode<T> *parent, *gparent;

    // 若“父节点存在，并且父节点的颜色是红色”
    while (node->parent!=NULL && node->parent->color==RED)
    {
        parent=node->parent;
        gparent = parent->parent;

        //若“父节点”是“祖父节点的左孩子”
        if (parent == gparent->left)
        {
            // Case 1条件：叔叔节点是红色
            {
                RBTNode<T> *uncle = gparent->right;
                if (uncle && uncle->color==RED)
                {
                    uncle->color=BLACK;
                    parent->color=BLACK;
                    gparent->color=RED;
                    node = gparent;
                    continue;
                }
            }

            // Case 2条件：叔叔是黑色，且当前节点是右孩子
            if (parent->right == node)
            {
                RBTNode<T> *tmp;
                rotateLeft(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            // Case 3条件：叔叔是黑色，且当前节点是左孩子。
            parent->color=BLACK;
            gparent->color=RED;
            rotateRight(root, gparent);
        } 
        else//若“z的父节点”是“z的祖父节点的右孩子”
        {
            // Case 1条件：叔叔节点是红色
            {
                RBTNode<T> *uncle = gparent->left;
                if (uncle && uncle->color==RED)
                {
                    uncle->color=BLACK;
                    parent->color=BLACK;
                    gparent->color=RED;
                    node = gparent;
                    continue;
                }
            }

            // Case 2条件：叔叔是黑色，且当前节点是左孩子
            if (parent->left == node)
            {
                RBTNode<T> *tmp;
                rotateRight(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            // Case 3条件：叔叔是黑色，且当前节点是右孩子。
            parent->color=BLACK;
            gparent->color=RED;
            rotateLeft(root, gparent);
        }
    }

    // 将根节点设为黑色
    root->color=BLACK;
}


template <class T>
void remove(RBTNode<T>* &root, RBTNode<T> *node)
{
    RBTNode<T> *child, *parent;
    RBTColor color;

    // 被删除节点的"左右孩子都不为空"的情况。
    if ( (node->left!=NULL) && (node->right!=NULL) ) 
    {
        //replace取代node
        // 被删节点的后继节点。(称为"取代节点")
        // 用它来取代"被删节点"的位置，然后再将"被删节点"去掉。
        RBTNode<T> *replace = node;

        // 获取后继节点
        replace = replace->right;
        while (replace->left != NULL)
            replace = replace->left;

        // "node节点"不是根节点(只有根节点不存在父节点)
        if (node->parent)
        {
            if (node->parent->left == node)
                node->parent->left = replace;
            else
                node->parent->right = replace;
        } 
        else 
            // "node节点"是根节点，更新根节点。
            root = replace;

        //删除replace
        // child是"取代节点"的右孩子，也是需要"调整的节点"。
        // "取代节点"肯定不存在左孩子！因为它是一个后继节点。
        child = replace->right;
        parent = replace->parent;
        // 保存"取代节点"的颜色
        color = replace->color;

        // "被删除节点"是"它的后继节点的父节点"
        if (parent == node)
        {
            parent = replace;
        } 
        else
        {
            // child不为空
            if (child)
                child->parent=parent;
            parent->left = child;

            replace->right = node->right;
            node->right->parent=replace;
        }

        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;

        if (color == BLACK)
            removeFixUp(root, child, parent);

        delete node;
        return ;
    }

    if (node->left !=NULL)
        child = node->left;
    else 
        child = node->right;

    parent = node->parent;
    // 保存"取代节点"的颜色
    color = node->color;

    if (child)
        child->parent = parent;

    // "node节点"不是根节点
    if (parent)
    {
        if (parent->left == node)
            parent->left = child;
        else
            parent->right = child;
    }
    else
        root = child;

    if (color == BLACK)
        removeFixUp(root, child, parent);
    delete node;
}
template <class T>
void remove(T key)
{
    RBTNode<T> *node; 

    // 查找key对应的节点(node)，找到的话就删除该节点
    if ((node = search(mRoot, key)) != NULL)
        remove(mRoot, node);
}


template <class T>
void removeFixUp(RBTNode<T>* &root, RBTNode<T> *node, RBTNode<T> *parent)
{
    RBTNode<T> *sib;

    while ((!node || node->color==black) && node != root)
    {
        if (parent->left == node)
        {
            sib = parent->right;
            if (sib->color==RED)
            {
                // Case 1: x的兄弟w是红色的  
                sib->color=BLACK;
                parent->color=RED;
                rotateLeft(root, parent);
                sib = parent->right;
            }
            if ((!sib->left || sib->left->color==BLACK) &&
                (!sib->right || sib->right->color==BLACK))
            {
                // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的  
                sib->color=RED;
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (!other->right || sib->right==BLACK)
                {
                    // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
                    sib->left->color=BLACK;
                    sib->color=RED;
                    rotateRight(root, sib);
                    sib = parent->right;
                }
                // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
                
                sib->color = parent->color;
                parent->color=BLACK;
                sib->right->color=BLACK;
                rotateLeft(root, parent);
                node = root;
                break;
            }
        }
        else
        {
            sib = parent->left;
            if (sib->color==RED)
            {
                // Case 1: x的兄弟w是红色的  
                sib->color=BLACK;
                parent->color=RED;
                rotateRight(root, parent);
                sib = parent->left;
            }
            if ((!other->left || (sib->left->color==BLACK)) &&
                (!other->right || (sib->right->color==BLACK)))
            {
                // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的  
                sib->color=RED;
                node = parent;
                parent = node->parent;
            }
            else
            {
                if (!other->left || (sib->left->color==BLACK))
                {
                    // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。  
                    sib->right->color=BLACK;
                    sib->color=RED;
                    rotateLeft(root, sib);
                    sib = parent->left;
                }
                // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
                sib->color= parent->color;
                parent->color=BLACK;
                sib->left->color=BLACK;
                rotateRight(root, parent);
                node = root;
                break;
            }
        }
    }
    if (node)
        node->color=BLACK;
}