#include "ucb1.h"
#include <vector>
#include <math.h>
#include <iostream>

float upper_bounds[] = {0.0f, 0.0f, 0.0f};
std::vector<float> rewards[3];
float R[3] = {0.3f, 0.4f, 0.3f};

int main()
{

  init();

  for(int i = 0; i < 10000; i++)
  {
    updateUpperBounds();
    int index_of_biggest_upperbound = findIndexOfBiggestUB();
    playAction(index_of_biggest_upperbound);
    std::cout << "Step " << (i+1) << ": Chose action " << index_of_biggest_upperbound << std::endl;
  }
  std::cout << "Final upperbounds: " << upper_bounds[0] << ", " << upper_bounds[1] << ", " << upper_bounds[2] << std::endl;
  std::cout << "Played arms 1/2/3: " << rewards[0].size() << " times, " << rewards[1].size() << " times, " << rewards[2].size() << " times." <<  std::endl;
}

void init()
{
  playAction(0);
  playAction(1);
  playAction(2);
}

int findIndexOfBiggestUB()
{
  int i = 0;
  if (upper_bounds[1] > upper_bounds[i])
  {
    i = 1;
  }
  if (upper_bounds[2] > upper_bounds[i])
  {
    i = 2;
  }
  return i;
}

void updateUpperBounds()
{
  for (int i = 0; i < 3; i++)
  {
    float sum = 0.0f;
    for (int j = 0; j < rewards[i].size(); j++)
    {
      sum += rewards[i].at(j);
    }
    int n = rewards[0].size() + rewards[1].size() + rewards[2].size(); 
    upper_bounds[i] = 1.0 / rewards[i].size() * sum + sqrt(2.0f * log(n) / rewards[i].size());  
  }
}

void playAction(int action)
{
  rewards[action].push_back(R[action]);
}
