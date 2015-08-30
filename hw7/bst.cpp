// bst.cpp implementation file for Binary Search Tree class

#include "bst.h"
#include <iostream>
#include <iomanip>


NodePtr BST :: BSTminimum( NodePtr x )
{
   while(x->left != NIL)
       x= (x->left);
   return x;
   // You write this
}

NodePtr BST :: BSTsuccessor( NodePtr x )
{
   NodePtr y ;

   if(x->right != NIL)
   {
       return BSTminimum(x->right);
   }
   y = x->p;
   while(y!= NIL && x==y->right)
   {
       x=y;
       y=y->p;
   }
   return y;
   // You write the rest of this
}

void BST :: BSTinsert( NodePtr z )
{
   NodePtr y ;
   NodePtr x ;
   y = NIL;
   x = root;
   while(x != NIL)
   {
       y=x;
       if(z->key < x->key)
       {
           x = x->left;
       }
       else
       {
            x=x->right;
       }

   }
    z->p = y;
    if(y == NIL)
    {
        root = z;
    }
    else if (z->key < y->key)
    {
        y->left =z;
    }
    else
        y->right = z;
   // You write the rest of this
}

// Utility used in BSTdelete
void BST :: Transplant( NodePtr u, NodePtr v )
{
    if(u->p == NIL)
    {
        root=v;
    }
    else if(u==u->p->left)
    {
        u->p->left= v;
    }
    else
    {
        u->p->right=v;
    }
    if(v!= NIL)
    {
        v->p = u->p;
    }
   // You write the rest of this
}

void BST :: BSTdelete( NodePtr z )
{
   NodePtr y ;
   if(z->left==NIL)
   {
       Transplant(z,z->right);
   }
   else if(z->right==NIL)
   {
       Transplant(z,z->left);
   }
   else
   {
       y = BSTminimum(z->right);
       if(y->p != z)
       {
           Transplant(y,y->right);
           y->right = z->right;
           y->right->p=y;
       }
        Transplant(z,y);
        y->left=z->left;
        y->left->p = y;
   }

   // You write the rest of this
}

NodePtr BST :: BSTsearch( NodePtr x, KeyType k )
{
    if((x == NIL) || (k == x->key))
    {
        return x;
    }
    if(k< x->key)
    {
        return BSTsearch(x->left,k);
    }
    else
    {
        return BSTsearch(x->right,k);
    }
   // You write this
}

void BST :: inorderTreeWalk( NodePtr x )
{
    if(x != NIL)
    {
        inorderTreeWalk(x->left);
        cout<<x->key<<" ";
        inorderTreeWalk(x->right);
    }

   // You write this - it should print x->key (and a space) using cout
}

/* Just prints tree in order as a horizontal list; may be used for debugging */
void BST :: PrintTree()
{
   cout << "Tree elements in order:\n" ;
   inorderTreeWalk(root) ;
   cout << "\n\n" ;
}

/* Shows the structure of the binary search tree */
void BST :: ShowTree( NodePtr x, int depth )
{
   if ( x != NIL ) {
      ShowTree( x->right, depth+1 ) ;
      cout << setw( depth*6 +4 ) << x->key << endl ;
      ShowTree( x->left, depth+1 ) ;
   }
}

