#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "list.hpp"

TEST_CASE ("constructor, size, empty", "[aufgabe 4.2]")
{
  List<int> l;
  REQUIRE (l.empty() == true);
  REQUIRE (l.size() == 0);
}

TEST_CASE ("add an element with push_front", "[modifiers]")
{
  List<int> l;
  l.push_front(42);
  REQUIRE (42 == l.front ());
}


int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}