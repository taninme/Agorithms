// btree.cpp - implementation file for BTree structures
#include "btree.h"
#include <iostream>
#include <iomanip>
// Constructor
BTree :: BTree( )
{
   NodePtr x = new BTreeNode ;
   x->leaf = true ;
   x->n = 0 ;
   root = x ;
}
// Utility routines for insertion
void copy( NodePtr src, int startSrc, NodePtr dest, int startDest )
{
   int j, offset ;
   offset = startDest - startSrc ;
   for ( j = startSrc ; j < startSrc + t - 1 ; j++ ) {
      dest->key[j + offset] = src->key[j] ;
   }
   if ( !src->leaf ) {
       for ( j = startSrc ; j < startSrc + t ; j++ ) {
          dest->c[j + offset] = src->c[j] ;
       }
   }
}
void shiftUp( NodePtr x, int kStart, int cStart )
{
	for(int j = x->n; j >= kStart; j--){		//move keys up
		x->key[j+1] = x->key[j];
	}
	if(!x->leaf){
		for(int j = x->n+1; j >= cStart; j--){	//move pointers up
			x->c[j+1] = x->c[j];
		}
	}
	x->n++;
}
void shiftDown( NodePtr x, int kStart, int cStart )
{
	for(int j = kStart; j <= x->n+1; j++){
		x->key[j-1] = x->key[j];
	}
	if(!x->leaf){
		for(int j = cStart; j <= x->n+1; j++){
			x->c[j-1] = x->c[j];
		}
	}
	x->n--;
}
void split_child( NodePtr x, int i )
{
   NodePtr z = new BTreeNode ;
   NodePtr y = x->c[i] ;
   z->leaf = y->leaf;
   z->n = t-1;
   copy( y, t+1, z, 1 );	//copy just elements on right from y to z
   shiftUp( x, i, i+1 );
   y->n = t-1;
   x->c[i+1] = z;			//add new node to x.c
   x->key[i] = y->key[t];
}
int iLoc( NodePtr x, KeyType k )
{
   int i = 1 ;
   while ( i <= x->n && k > x->key[i] )
      i++ ;
   return i ;
}
void insert_nonfull( NodePtr x, KeyType k )
{
   int i = iLoc( x, k ) ;
   if ( x->leaf ) {
       shiftUp( x, i, i ) ;
       x->key[i] = k ;
   } else {
	   //if the child is full we need to split it up
	   if(x->c[i]->n == 2*t - 1){
		   split_child(x,i);
		   if(k > x->key[i]) i ++;
	   }
	   //the child has some empty space for new element k
	   insert_nonfull(x->c[i],k);
   }
}
void BTree :: BTinsert( KeyType k )
{
	NodePtr r = root;
	if(root->n == 2*t-1){	//if the root is full, we need to split it
		NodePtr s = new BTreeNode;
		root = s;
		s->leaf = false;
		s->n = 0;
		s->c[1] = r;
		split_child(s,1);
		insert_nonfull(s,k);
	} else
		insert_nonfull(r,k);
}
// Utility routines for deletion
KeyType minimum( NodePtr x )
{
    while(x->leaf == false) x = x->c[1];	//need to find leaf at the very left
	return x->key[1];
}
KeyType maximum( NodePtr x )
{
	while(x->leaf == false) x = x->c[x->n+1];	//need to find leaf at the very right
	return x->key[x->n];
}
void borrowLeft( NodePtr x, int i )
{
   NodePtr y = x->c[i-1] ;
   NodePtr z = x->c[i] ;
   shiftUp( z, 1, 1 ) ;
   //we need to take a node from left child and place it as key in x
   // ... the key from the x goes to right child
   z->c[1] = y->c[y->n+1];
   z->key[1] = x->key[i-1];
   x->key[i-1] = y->key[y->n];
   y->n--;
}
void borrowRight( NodePtr x, int i )
{
   NodePtr y = x->c[i] ;
   NodePtr z = x->c[i+1] ;
   // Same as borrowLeft, but vice versa
   y->c[y->n+2] = z->c[1];
   y->key[y->n+1] = x->key[i];
   x->key[i] = z->key[1];
   y->n++;
   shiftDown( z, 2, 2 );
}
void merge_children( NodePtr x, int i )
{
   NodePtr y = x->c[i] ;
   NodePtr z = x->c[i+1] ;
   copy ( z, 1, y, t+1 ) ;
   // item were copied, now we need to secured that x.k[i] is in the middle of y
   y->key[t] = x->key[i];
   y->n = 2*t - 1;

   shiftDown( x, i+1, i+2 ) ;
   delete z ;
}
void delete_fullenuf( NodePtr x, KeyType k )
{
   int i = iLoc( x, k ) ;
   KeyType k_prime ;
   if ( x->leaf ) {
      if(i <= x->n && k == x->key[i])	//case 1
		  shiftDown(x,i+1,i+1);
	  else
		  cout << k<<" is not in tree.\n";	//case 0
   } else {
       if(i <= x->n && k == x->key[i]){	//case 2
		  if(x->c[i]->n >= t){			//case 2a
			  int kk = maximum(x->c[i]);
			  x->key[i] = kk;
			  delete_fullenuf(x->c[i],kk);
		  }
		  else if(x->c[i+1]->n >= t){	//case 2b
			  int kk = minimum(x->c[i+1]);
			  x->key[i] = kk;
			  delete_fullenuf(x->c[i+1],kk);
			}
		  else{							//case 2c
			  merge_children(x,i);
			  delete_fullenuf(x->c[i],k);
			}
	   } else{	//case 3
		   if(x->c[i]->n < t){
			   if (i>1 && x->c[i-1]->n >= t){	//case 3a i)
				   borrowLeft(x,i);
			   } else if(i < x->n+1 && x->c[i+1]->n >= t){ //case 3a ii)
				   borrowRight(x,i);
			   } else {
				   if(i > 1)	//case 3b
						i--;
				   merge_children(x,i);
			   }
		   }
		   delete_fullenuf(x->c[i], k);
		}
   }
}
void BTree :: BTdelete( KeyType k )
{
   NodePtr r = root ;
   if ( r->n == 0 ) {
       cout << "Deleting from empty tree.\n" ;
   } else {
       delete_fullenuf ( r, k ) ;
       if ( r->n == 0 && !r->leaf ) {
           root = r->c[1] ;
           delete r ;
       }
   }
}
BTreeLocation BTree :: BTsearch( NodePtr x, KeyType k )
{
   int i = iLoc( x, k ) ;
   if ( i <= x->n && k == x->key[i] )
       return BTreeLocation( x, i ) ;
   if ( x->leaf ) {
       return BTreeLocation( NIL, 0 ) ;
   } else {
	   return BTsearch(x->c[i], k);	//if the element is not in x we need to go deeper and search again
   }
}
// Useful routine to show B-Tree structure
void BTree :: ShowTree( NodePtr x, int depth )
{
   if ( x->leaf ) {
       for ( int i = x->n ; i >= 1 ; i-- ) {
          cout << setw( depth*6 + 7 ) << x->key[i] << endl ;
       }
   } else {
       ShowTree( x->c[x->n + 1], depth + 1 ) ;
       for ( int i = x->n ; i >= 1 ; i-- ) {
          cout << setw( depth*6 + 7 ) << x->key[i] << endl ;
          ShowTree( x->c[i], depth + 1 ) ;
       }
   }
}
// Useful routine to show a single node
void BTreeNode :: ShowNode()
{
   cout << "\nLeaf = " << ( ( leaf )? "True" : "False" )
        << ", n = " << n << "\nKeys: " ;
   for ( int i = 1 ; i <= n ; i++ )
      cout << key[i] << ' ' ;
   cout << "\n\n" ;
}
