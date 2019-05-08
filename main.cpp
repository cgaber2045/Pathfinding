#include "pathfinder.h"
#include <chrono>

int main() {
  char arr[15][20] =
  {
  	{'e','s','e','e','e','e','e','e','e','e','g','g','e','e','g','e','e','e','e','e'},
  	{'e','w','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e','e'},
  	{'e','w','e','w','w','w','w','w','w','w','w','w','w','w','w','e','e','w','w','w'},
  	{'z','w','e','w','b','e','e','e','e','e','e','e','e','e','e','e','e','w','g','g'},
  	{'e','w','e','w','w','w','w','w','w','w','w','w','w','w','w','w','e','w','g','g'},
  	{'e','w','e','w','e','e','e','e','e','e','e','e','e','e','e','e','e','w','g','g'},
  	{'b','w','e','w','e','w','w','w','w','w','w','w','e','e','e','e','e','w','g','g'},
  	{'e','w','e','w','e','e','e','e','e','e','e','w','e','w','w','w','w','w','w','e'},
  	{'e','w','e','w','e','e','b','e','e','e','w','w','e','w','e','e','e','e','w','e'},
  	{'e','w','e','w','e','g','b','f','e','e','w','e','e','w','e','w','w','e','w','e'},
  	{'e','w','e','w','e','e','b','e','g','g','w','e','e','w','e','e','w','e','w','e'},
  	{'e','w','e','w','e','e','e','e','e','e','w','w','e','w','e','e','w','e','e','e'},
  	{'e','w','e','w','e','e','e','e','e','e','e','w','e','w','e','e','w','e','e','e'},
  	{'e','e','e','w','e','e','e','e','e','e','e','w','e','w','w','w','w','e','e','e'},
  	{'e','w','e','w','e','e','e','e','e','e','w','e','e','e','e','e','e','e','e','e'},
  };

  auto start = chrono::steady_clock::now();

  vector<char> ourPath = pathfinder(arr);
  for (char x: ourPath) cout << x << endl;

  auto finish = chrono::steady_clock::now();

  auto diff = finish - start;

  cout << chrono::duration <double, milli> (diff).count() << " ms" << endl;
  return 0;
}
