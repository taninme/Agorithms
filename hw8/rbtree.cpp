// rbtree.cpp implementation file for Red-Black Tree class

#include "rbtree.h"
#include <iostream>
#include <iomanip>


// Constructor
RBTree :: RBTree()
{
  nil = new Node(0) ;  // this seems to work
  nil->color = 'B' ;
  nil->p = nil ;
  nil->left = nil ;
  nil->right = nil ;

  root = nil ;
}


// Other RBTree mutators - not directly used here
void RBTree :: leftRotate( NodePtr x )
{
   NodePtr y = x->right ;
   x->right = y->left;
   if(y->left != nil) y->left->p = x;
   y->p = x->p;
   if(x->p == nil) root = y;
   else if(x == x->p->left) x->p->left = y;
   else x->p->right = y;
   y->left = x;
   x->p = y;
}

void RBTree :: rightRotate( NodePtr y )
{
   NodePtr x = y->left ;
   y->left = x->right;
   if(x->right != nil) x->right->p = y;
   x->p = y->p;
   if(y->p == nil) root = x;
   else if(y == y->p->right) y->p->right = x;
   else y->p->left = x;
   x->right = y;
   y->p = x;
}

void RBTree :: insertFixup( NodePtr z )
{
  NodePtr y ;
  while (z->p->color == 'R' ) {
	if ( z->p == z->p->p->left ) {
	   y = z->p->p->right;
	   if(y->color == 'R'){			//CASE 1
		   z->p->color = 'B';
		   y->color = 'B';
		   z->p->p->color = 'R';
		   z = z->p->p;
	   } else {
			if (z == z->p->right){	//CASE 2
			   z = z->p;
			   leftRotate(z);
		   }
									//CASE 3
		   z->p->color = 'B';
		   z->p->p->color = 'R';
		   rightRotate(z->p->p);
	   }
	} else {
		y = z->p->p->left;
		if(y->color == 'R'){
			z->p->color = 'B';
			y->color = 'B';
			z->p->p->color = 'R';
			z = z->p->p;
		} else{
			if (z == z->p->left){
				z = z->p;
				rightRotate(z);
			}
			z->p->color = 'B';
			z->p->p->color = 'R';
			leftRotate(z->p->p);
		}
	}
  }
  root->color = 'B' ;
}

void RBTree :: deleteFixup( NodePtr x )
{
  NodePtr w ;
  while ( ( x != root ) && ( x->color == 'B' ) ) {
	 if ( x == x->p->left ) {  // x is a left child
		w = x->p->right;
		if(w->color == 'R'){
			w->color = 'B';
			x->p->color = 'R';
			leftRotate(x->p);
			w = x->p->right;
		}

		if( (w->left->color == 'B') && (w->right->color == 'B') ){
			w->color = 'R';
			x = x->p;
		}
		else{

			if(w->right->color == 'B'){
				w->left->color = 'B';
				w->color = 'R';
				rightRotate(w);
				w = x->p->right;
			}
			//w is black and w's child is red
			w->color = x->p->color;
			x->p->color = 'B';
			w->right->color = 'B';
			leftRotate(x->p);
			x = root;
		}

	 } else {  // x is a right child
		 w = x->p->left;
		 if(w->color == 'R'){
			 w->color = 'B';
			 x->p->color = 'R';
			 rightRotate(x->p);
			 w = x->p->left;
		 }
		 if( (w->right->color == 'B') && (w->left->color == 'B') ){
			 w->color = 'R';
			 x = x->p;
		 }
		 else{
			 if(w->left->color == 'B'){
				 w->right->color = 'B';
				 w->color = 'R';
				 leftRotate(w);
				 w = x->p->left;
			 }
			 w->color = x->p->color;
			 x->p->color = 'B';
			 w->left->color = 'B';
			 rightRotate(x->p);
			 x = root;
		 }
	 }
  }
  x->color = 'B' ;
}

// Utility used in RBdelete
void RBTree :: RBTransplant( NodePtr u, NodePtr v )
{
   if(u->p == nil) root = v;
   else if(u == u->p->left) u->p->left = v;
   else u->p->right = v;
   v->p = u->p;
}


NodePtr RBTree :: Tree_minimum( NodePtr x )
{
   while ( x->left != nil )
	  x = x->left ;
   return x ;
}

// This is not used.
NodePtr RBTree :: Tree_successor( NodePtr x )
{
   if ( x->right != nil ) return Tree_minimum( x->right ) ;

   NodePtr y = x->p ;
   while ( ( y != nil ) && ( x == y->right ) ) {
	  x = y ;
	  y = y->p ;
   }
   return y ;
}


// RBTree mutators
void RBTree :: RBinsert( NodePtr z )
{
   NodePtr y = nil ;
   NodePtr x = root ;

   while(x != nil){
	   y = x;
	   if(z->key < x->key) x = x->left;
	   else x = x->right;
   }
   z->p = y;
   if(y == nil) root = z;
   else if(z->key < y->key) y->left = z;
   else y->right = z;

   z->left = nil;
   z->right = nil;
   z->color = 'R';

   insertFixup( z ) ;
}

void RBTree :: RBdelete( NodePtr z )
{
   NodePtr x ;
   NodePtr y = z ;
   char y_original_color = y->color ;

   if(z->left == nil){
	   x = z->right;
	   RBTransplant(z,z->right);
   }
   else if(z->right == nil){	//no right node
	   x = z->left;
	   RBTransplant(z,z->left);
   }
   else{
	   y = Tree_minimum(z->right);
	   y_original_color = y->color;
	   x = y->right;
	   if(y->p == z) x->p = y;
	   else{
		   RBTransplant(y,y->right);
		   y->right = z->right;
		   y->right->p = y;
		}
	   RBTransplant(z,y);
	   y->left = z->left;
	   y->left->p = y;
	   y->color = z->color;
   }

   if ( y_original_color == 'B' )
	   deleteFixup( x ) ;
}

// RBTree accessor
NodePtr RBTree :: RBsearch( NodePtr x, KeyType k )
{
   while ( ( x != nil ) && ( k != x->key ) )
	  if ( k < x->key ) x = x->left ;
	  else              x = x-> right ;
   return x ;
}

// RBTree "print" utility routines
void RBTree :: inorderTreeWalk( NodePtr x )
{
   if ( x != nil ) {
	  inorderTreeWalk( x->left ) ;
	  cout << x->key << " " ;
	  inorderTreeWalk( x->right ) ;
   }
}


void RBTree :: PrintTree()
{
   cout << "Tree elements in order:\n" ;
   inorderTreeWalk( root ) ;
   cout << "\n\n" ;
}


void RBTree :: ShowTree( NodePtr x, int depth )
{
   if ( x != nil ) {
	  ShowTree( x->right, depth+1 ) ;
	  cout << setw( depth*7 +4 ) << x->key << x->color << endl ;
	  ShowTree( x->left, depth+1 ) ;
   }
}
