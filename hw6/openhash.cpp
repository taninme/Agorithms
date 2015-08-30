// openhash.cpp implementation file for OpenHash open address hashing class

#include "openhash.h"
#include <iostream>
#include <iomanip>


// Constructor
OpenHash :: OpenHash( int mNew )
{
   m = mNew ;
   Array = new KeyType[m] ;
   for ( int i = 0 ; i < m ; i++ ) {
      Array[i] = NIL ;
   }
}


// OpenHash mutators
int OpenHash :: OHinsert( KeyType k )
{
   int i = 0 ;
   int j ;
   do {
        j= h(k,i);
        if((Array[j]==NIL) || (Array[j]== DELETED))
        {
            Array[j]=k;
            return j;
        }
    else
        i = i +1;
      // You fill in the details here
   } while ( i < m );{
   return NIL ;
   cout << "hash table overflow\n\n" ; }
}

int OpenHash :: OHdelete( KeyType k )
{
   int i = 0 ;
   int j ;
   do {
        j= h(k,i);
    if((Array[j]==k))
    {
        Array[j]==DELETED;

    }
    i++;
      //You fill in the details here

   } while ( ( Array[j] != NIL ) && ( i < m ) ) ;
   return NIL ;
}

// OpenHash accessor
int OpenHash :: OHsearch( KeyType k )
{
   int i = 0 ;
   int j ;
   do {
      // You fill in the details here
      j=h(k,i);
    if(Array[j]==k)
    {
        return j;
    }
    i = i + 1;
   } while ( ( Array[j] != NIL ) && ( i < m ) ) ;
   return NIL ;
}


/* Shows the structure of the list */
void OpenHash :: ShowTable( )
{
   cout << "Hash table:\n" ;
   for ( int i = 0 ; i < m ; i++ ) {
      cout << "T[" << i << "]: " << Array[i] << endl ;
   }
   cout << "\n" ;
}

