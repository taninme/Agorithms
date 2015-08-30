// graph.cpp - implementation file for Graph structure

#include "graph.h"
#include <iostream>
#include <iomanip>
// queue.h is needed for BFS
#include "queue.h"

// using namespace std ;


Graph :: Graph( int size , bool wgted, int inf )
{
   int i, j ;

   n = size ;
   weighted = wgted ;
   INFINITY = inf ;
   color = new Color[ n+1 ] ;
   pi = new int[ n+1 ] ;
   d = new int[ n+1 ] ;
   f = new int[ n+1 ] ;
   Adj = new Node*[ n+1 ] ;
   for ( i = 1 ; i <= n ; i++ ) {
      Adj[i] = NIL ;
   }
}


void Graph :: BFS( int s )
{
// you provide this
}

int dfsTime ; // Global variable used in Depth-First Search
// Use this instead of time to avoid conflict with system time() 

void Graph :: DFSvisit( int u )
{
// you provide this
}

void Graph :: DFS( int s )
{
   for ( int u = 1 ; u <= n ; u++ ) {
      color[u] = WHITE ;
      pi[u] = NIL ;
   }
   dfsTime = 0 ;
   DFSvisit( s ) ;
}


void Graph :: readEdges()
{
   int u, v, wt ;

   if ( weighted ) cin >> u >> v >> wt ;
   else            cin >> u >> v ; 
   while ( !cin.eof() ) {
      Node * x = new Node ;
      x->v = v ;
      if ( weighted ) x->wuv = wt ;
      x->next = Adj[u] ;
      Adj[u] = x ;
      if ( weighted ) cin >> u >> v >> wt ;
      else            cin >> u >> v ; 
   } // while ( !cin.eof() ) ;
}

void Graph :: printPath( int s, int v )
{
// you provide this
}

void Graph :: showDists()
{
   cout << "Distances (for BFS)" ;
   for ( int v = 1 ; v <= n ; v++ ) {
      cout << ", d[" << v << "] = " << d[v] ; 
   }
   cout << "\n\n" ;
}

void Graph :: showPreds()
{
   cout << "Predecessors" ;
   for ( int v = 1 ; v <= n ; v++ ) {
      cout << ", pi[" << v << "] = " << pi[v] ; 
   }
   cout << "\n\n" ;
}

void Graph :: showAdj()
{
   cout << "The Adjacency lists:\n" ;
   for ( int v = 1 ; v <= n ; v++ ) {
      cout << "Adj[" << v << "]" ; 
      for ( Node * x = Adj[v] ; x != NIL ; x = x->next ) {
         cout << "->[" << x->v ;
         if ( weighted ) cout << "," << x->wuv ;
         cout << "]" ;
      }
      cout << endl ;
   }
   cout << "\n\n" ;
}

