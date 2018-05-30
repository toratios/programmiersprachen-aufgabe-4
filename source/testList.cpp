#define CATCH_CONFIG_RUNNER
#include <catch.hpp>
#include "list.hpp"

TEST_CASE ("constructor, size, empty", "[aufgabe 4.2]")
{
  List<int> l;
  REQUIRE (l.empty() == true);
  REQUIRE (l.size() == 0);
}

TEST_CASE ("add an element with push_front", "[aufgabe 4.3]")
{
  List<int> l;
  l.push_front(33);
  l.push_front(42);
  REQUIRE (42 == l.front());
}

TEST_CASE ("add an element with push_back", "[aufgabe 4.3]")
{
  List<int> l;
  l.push_back(33);
  l.push_back(42);
  REQUIRE (42 == l.back());
}

TEST_CASE ("remove an element with pop_front", "[aufgabe 4.3]")
{
  List<int> l;
  l.push_front(33);
  l.push_front(42);
  l.pop_front();
  REQUIRE (33 == l.front());
  l.pop_front();
  REQUIRE(l.size() == 0);
}

TEST_CASE ("remove an element with pop_back", "[aufgabe 4.3]")
{
  List<int> l;
  l.push_back(33);
  l.push_back(42);
  l.pop_back();
  REQUIRE (33 == l.back());
  l.pop_back();
  REQUIRE(l.size() == 0);
}

TEST_CASE ("should be empty after clearing", "[aufgabe 4.4]")
{
  List<int>list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  list.push_front(4);
  list.clear();
  REQUIRE(list.empty());
}

TEST_CASE("should be an empty range after default construction", "[aufgabe 4.6]"){
	List<int> list;
	auto b = list.begin();
	auto e = list.end();
	REQUIRE(b==e);
}

TEST_CASE("provide acces to the first element with begin", "[aufgabe 4.6]"){
	List<int> list;
  list.push_front(1);
	list.push_front(42);
	REQUIRE(42 == *list.begin());
}

/*
TEST_CASE("provide acces to the last element with end", "[aufgabe 4.6]"){
	List<int> list;
	list.push_front(42);
  list.push_front(1);
	REQUIRE(nullptr == *list.end());
}*/

TEST_CASE("== and != operator", "[aufgabe 4.7]"){
	List<int> l1;
  List<int> l2;
  List<int> l3;

  REQUIRE(l1 == l2);

  l1.push_front(1);
	l1.push_front(42);
  l2.push_front(1);
	l2.push_front(42);

	REQUIRE(l1 == l2);

  l1.push_front(5);
  l2.push_front(4);

  REQUIRE(l1 != l2);
  REQUIRE(l1 != l3);
}

TEST_CASE("copy constructor", "[aufgabe 4.8]"){
  List<int>list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  list.push_front(4);
  List<int>list2{list};
  REQUIRE(list == list2);
}

TEST_CASE("insert", "[aufgabe 4.9]"){
  List<int>list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  list.push_front(4);
  list.insert(++list.begin(), 5);
  List<int>list2;
  list2.push_front(1);
  list2.push_front(2);
  list2.push_front(3);
  list2.push_front(5);
  list2.push_front(4);
  REQUIRE(list.size() == 5);
  REQUIRE(list == list2);  
}

TEST_CASE("reverse member", "[aufgabe 4.10]"){
	List<int> list;
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);
	list.push_front(4);
	list.reverse();
  List<int> list2;
  list2.push_front(4);
	list2.push_front(3);
	list2.push_front(2);
	list2.push_front(1);
	REQUIRE(list2 == list);
}

TEST_CASE("reverse free", "[aufgabe 4.10]"){
	List<int> list;
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);
	list.push_front(4);
  list.push_front(5);
	List<int> list1 = reverse(list);
  List<int> list2;
  list2.push_front(5);
  list2.push_front(4);
	list2.push_front(3);
	list2.push_front(2);
	list2.push_front(1);
	REQUIRE(list2 == list1);
}


TEST_CASE("copy list to vector", "[aufgabe 4.11]"){
	List<int> list;
	list.push_front(1);
	list.push_front(2);
	list.push_front(3);
	list.push_front(4);
	std::vector<int> vec (list.size());
	std::copy(std::begin(list), std::end(list), std::begin(vec));
	int i = 4;
	for (auto v : vec){
		REQUIRE(i == v);
		--i;
	}
}


TEST_CASE("optional =", "[aufgabe 4.12]"){
	List<int> list1;
	list1.push_front(1);
	list1.push_front(2);
	list1.push_front(3);
	list1.push_front(4);
  list1.push_front(5);
	List<int> list2 = list1;
	REQUIRE(list2 == list1);
  list1.clear();
  REQUIRE(!list2.empty());
}

TEST_CASE ("move constructor", "[aufgabe 4.13]")
{
  List<int> list;
  list.push_front(1);
  list.push_front(2);
  list.push_front(3);
  list.push_front(4);
  List<int> list2(std::move(list));
  REQUIRE (0 == list.size());
  REQUIRE (list.empty());
  REQUIRE (4 == list2.size());
}


int main(int argc, char *argv[])
{
  return Catch::Session().run(argc, argv);
}