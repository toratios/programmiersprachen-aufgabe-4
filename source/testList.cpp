#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "list.hpp"

TEST_CASE ("constructor, size, empty", "[aufgabe 4.2]")
{
  List<int> l;
  REQUIRE (l.empty() == true);
  REQUIRE (l.size() == 0);
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}