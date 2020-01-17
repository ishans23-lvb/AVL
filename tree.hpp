//
//  tree.hpp
//  AVL
//
//  Created by Ishan Shah on 1/9/20.
//  Copyright © 2020 Ishan Shah. All rights reserved.
//

#ifndef tree_hpp
#define tree_hpp

#include <stdio.h>
#include <iostream>
#include <stack>
using namespace std;

#ifdef DEBUG
#define ASSERT(x) assert(x)
#else
#define ASSERT(x)
#endif

template <typename T>
struct node
{
    T x;
    unsigned long height;//NULL nodes have 0 height
    node<T> *left, *right;
    node(T x):x(x),height(1),left(NULL),right(NULL){}
};

template<typename T>
bool bst_check_lst_vals(const node<T>* const rst,const node<T>* const root);
template<typename T>
bool bst_check_rst_vals(const node<T>* const rst,const node<T>* const root);
template<typename T>
bool bst_validate(const node<T>* const root);

template<typename T>
unsigned long avl_true_height(const node<T>* const root)
{
    if(!root)
        return 0;
    else
    {
        unsigned long lh=avl_true_height(root->left);
        unsigned long rh=avl_true_height(root->right);
        return 1+ ( (rh>=lh) ? rh : lh );
    }
}

template<typename T>
unsigned long avl_height(const node<T>* const root)
{
    ASSERT(bst_validate(root));
    ASSERT((root ? root->height : 0)==avl_true_height(root));
    return root ? root->height : 0;
}

template<typename T>
unsigned long avl_recalc_height(node<T>* root)
{
    ASSERT(root);
    unsigned long lh=avl_height(root->left);
    unsigned long rh=avl_height(root->right);
    return 1+ ( (rh>=lh) ? rh : lh );
}


//Can not be perfomred if !(root->left)
template<typename T>
node<T>* avl_rotate_right(node<T>* root)
{
    ASSERT(bst_validate(root));
    ASSERT(root);
    ASSERT(root->left);
    node<T>* const lc=root->left;
    
    root->left=lc->right;
    lc->right=root;
    
    root->height=avl_recalc_height(root);
    lc->height=avl_recalc_height(lc);
    ASSERT(bst_validate(root));
    return lc;
}

template<typename T>
node<T>* avl_rotate_left(node<T>* root)
{
    ASSERT(bst_validate(root));
    ASSERT(root);
    ASSERT(root->right);
    node<T>* const rc=root->right;
    
    root->right=rc->left;
    rc->left=root;
    
    root->height=avl_recalc_height(root);
    rc->height=avl_recalc_height(rc);
    ASSERT(bst_validate(root));
    return rc;
}
template<typename T>
node<T>* avl_correct(node<T>* root)
{
    ASSERT(bst_validate(root));
    if(!root)
        return root;
    
    unsigned long lh=avl_height(root->left);
    unsigned long rh=avl_height(root->right);
    unsigned long diffh= ( (rh>=lh) ? (rh-lh) : (lh-rh) );
    
    if(diffh>1)
    {
        //Rotate left
        if(rh>lh)
        {
            ASSERT(root->right);
            unsigned long rlh=avl_height(root->right->left);
            unsigned long rrh=avl_height(root->right->right);
            if(rlh>rrh)
            {
                root->right=avl_rotate_right(root->right);
            }
            
            root->height=avl_recalc_height(root);
            root=avl_rotate_left(root);
        }
        else //Rotate Right
        {
            ASSERT(root->left);
            unsigned long llh=avl_height(root->left->left);
            unsigned long lrh=avl_height(root->left->right);
            
            if(lrh>llh)
            {
                root->left=avl_rotate_left(root->left);
            }
            root->height=avl_recalc_height(root);
            root=avl_rotate_right(root);
        }
    }
    
    return root;
}

template<typename T>
node<T>* avl_insert(node<T>* root,node<T>* const nn)
{
    ASSERT(bst_validate(root));
    ASSERT(nn);
    if(!root)
        return nn;
    
    if(root->x>=nn->x)
        root->left=avl_insert(root->left,nn);
    else
        root->right=avl_insert(root->right,nn);
    
    root->height=avl_recalc_height(root);
    ASSERT(bst_validate(root));
    root=avl_correct(root);
    
    ASSERT(bst_validate(root));
    return root;
}

template<typename T>
node<T>* avl_find(const node<T>* root,const T& x)
{
    if(!root || root->x==x)
        return root;
    if(x<root->x)
        return avl_find(root->left,x);
    else
        return avl_find(root->right,x);
}

template<typename T>
bool bst_validate(const node<T>* const root)
{
    if(!root)
        return true;
    
    return bst_check_lst_vals(root->left,root) &&
          bst_check_rst_vals(root->right,root) &&
          (root->height==avl_true_height(root));
}

template<typename T>
bool bst_check_lst_vals(const node<T>* const lst,const node<T>* const root)
{
    ASSERT(root);
    if(!lst)
        return true;
    return lst->x<=root->x && bst_check_lst_vals(lst->left,root) && bst_check_lst_vals(lst->right,root);
}

template<typename T>
bool bst_check_rst_vals(const node<T>* const rst,const node<T>* const root)
{
    if(!rst)
        return true;
    return rst->x>=root->x && bst_check_rst_vals(rst->left,root) && bst_check_rst_vals(rst->right,root);
}

template<typename T>
bool avl_validate(const node<T>* const root)
{
    if(!root)
        return true;
    if(!bst_validate(root))
        return false;
    unsigned long lh=avl_height(root->left);
    unsigned long rh=avl_height(root->right);
    
    return ( (rh>=lh) ? ((rh-lh)<=1) : ((lh-rh)<=1) ) && avl_validate(root->left) && avl_validate(root->right);
}

template<typename T>
void bst_print(const node<T>* const root)
{
    if(!root)
        return;
    bst_print(root->left);
    cout << "(" << root->x << ", " << root->height << ")"<< " ";
    bst_print(root->right);
}

template<typename T>
class tree
{
private:
    node<T>* root;
public:
    
    tree(void)
    :root(nullptr)
    {}
    
    int insert(const T& x)
    {
        ASSERT(validate());
        node<T>* nn=new node<T>(x);
        root=avl_insert(root,nn);
        ASSERT(validate());
        return 0;
    }
    
    
    
    void print(void) const
    {
        ASSERT(validate());
        bst_print(root);
        cout << endl;
    }
    
    class iterator
    {
    private:
        node<T>* cn;
        stack<node<T>*> s;
    public:
        
    };
    
#ifdef DEBUG
    bool validate(void) const
    {
        return avl_validate(root);
    }
#endif
};

#endif /* tree_hpp */
