#define CATCH_CONFIG_RUNNER
#include "catch.hpp"
#include "Time.h"
int main(int argc, char* argv[])
{
  return Catch::Session{}.run(argc, argv);
}
