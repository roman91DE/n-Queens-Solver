#include "threadedannealing.h"
#include <thread>
#include <cassert>



const auto processor_count = std::thread::hardware_concurrency();
// assert (processor_count>0);