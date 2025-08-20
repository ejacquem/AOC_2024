#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

#if DEBUG
 #define LOG(x) do { std::cout << x; } while(0)
#else
 #define LOG(x) 
#endif

using std::vector;
using std::string;