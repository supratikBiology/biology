#include <iostream>

using namespace std;

#include "BitGraph.h"

int main()
{
  BitGraph* graph = new BitGraph();

  for (unsigned int i = 1; i < 16; i++)
  {
     graph->addEdge(i, 2 * i);
     graph->addEdge(2*i, 10 * i);
  }
  cout << *graph << endl;

  delete graph;

  return 0;
}