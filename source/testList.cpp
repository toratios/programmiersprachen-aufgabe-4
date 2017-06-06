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
  l.push_front(33);
  l.push_front(42);
  REQUIRE (42 == l.front ());
}

TEST_CASE ("add an element with push_back", "[modifiers]")
{
  List<int> l;
  l.push_back(33);
  l.push_back(42);
  REQUIRE (42 == l.back ());
}

TEST_CASE ("remove an element with pop_front", "[modifiers]")
{
  List<int> l;
  l.push_front(33);
  l.push_front(42);
  l.pop_front();
  REQUIRE (33 == l.front ());
  l.pop_front();
  l.pop_front();
  REQUIRE(l.size() == 0);
}

TEST_CASE ("remove an element with pop_back", "[modifiers]")
{
  List<int> l;
  l.push_back(33);
  l.push_back(42);
  l.pop_back();
  REQUIRE (33 == l.back ());
  l.pop_back();
  l.pop_back();
  REQUIRE(l.size() == 0);
}

TEST_CASE ("should be empty after clearing", "[modifiers]")
{
  List<int>list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  list.push_front(4);
  list.clear();
  REQUIRE(list.empty());
}

int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}