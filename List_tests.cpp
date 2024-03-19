#include "list.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

// TEST(test_stub) {
//     // Add test code here
//     ASSERT_TRUE(true);
// }

TEST(test_empty){

    List <int> empty;
    ASSERT_TRUE(empty.empty());
}

TEST(test_size){

    List <int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    ASSERT_TRUE(list.size() == 3);
}

TEST(test_front) {

    List <int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);
    ASSERT_TRUE(list.front() == 1);
}

TEST(test_back) {

    List <int> list;
    list.push_front(5);
    list.push_front(7);
    list.push_front(8);
    ASSERT_TRUE(list.back() == 5);
}

TEST(test_push_front) {

    List <int> list;
    list.push_front(1);
    list.push_front(2);
    list.push_front(3);
    ASSERT_TRUE(list.front() == 3);
}

TEST(test_push_back){

    List <int> list;
    list.push_back(5);
    list.push_back(7);
    list.push_back(8);
    ASSERT_TRUE(list.front() == 5);
}

TEST(test_pop_front){

    List <int> list;
    list.push_back(2);
    list.push_back(3);
    list.push_back(5);
    list.push_back(7);
    list.push_back(8);
    list.pop_front();
    list.pop_front();

    ASSERT_TRUE(list.size() == 3);
    ASSERT_TRUE(list.front() == 5);

}

TEST(test_pop_back){
    List <int> list;
    list.push_back(2);
    list.push_back(3);
    list.push_back(5);
    list.push_back(7);
    list.push_back(8);
    list.pop_back();

    ASSERT_TRUE(list.size() == 4);
    ASSERT_TRUE(list.back() == 7);
}

TEST(test_clear){
    List <int> list;
    list.push_back(2);
    list.push_back(3);
    list.push_back(5);
    list.push_back(7);
    list.push_back(8);
    list.clear();

    ASSERT_TRUE(list.size() == 0);
}

TEST(test_constructors){
    List <int> list1;
    ASSERT_TRUE(list1.empty());
    list1.push_back(2);
    list1.push_back(3);
    list1.push_back(5);
    list1.push_back(7);
    list1.push_back(8);
    List<int> list2(list1);
    ASSERT_TRUE(list1.front() == list2.front());
}

TEST(test_iterators) {
    // Create a list and add some elements
    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    // Test Iterator Construction
    List<int>::Iterator it = list.begin();
    List<int>::Iterator end_it = list.end();

    // Test Iterator Dereferencing
    ASSERT_EQUAL(*it, 1);

    // Test Iterator Increment
    ++it;
    ASSERT_EQUAL(*it, 2);

    // Test Iterator Decrement
    --it;
    ASSERT_EQUAL(*it, 1);

    // Test Iterator Equality and Inequality
    List<int>::Iterator it_copy = it;
    ASSERT_TRUE(it == it_copy);
    ASSERT_FALSE(it != it_copy);

    // Test Iterator Range
    std::vector<int> elements;
    for (;it != end_it; ++it) {
        elements.push_back(*it);
    }
    ASSERT_EQUAL(elements.size(), list.size());
    ASSERT_EQUAL(elements, std::vector<int>({1, 2, 3}));
}

TEST(test_assignment_operator) {
    List<int> list1;
    List<int> list2;

    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    list1.push_back(4);

    list2.push_back(5);
    list2.push_back(6);
    list2.push_back(7);
    list2.push_back(8);

    list2 = list1;
    ASSERT_TRUE(list2.front() == 1);
    ASSERT_TRUE(list2.back() == 4);
}

TEST(test_equals_equals){
    List<int> list1;
    List<int> list2;

    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(3);
    list1.push_back(4);

    list2.push_back(1);
    list2.push_back(2);
    list2.push_back(3);
    list2.push_back(4);

    ASSERT_TRUE(list1 == list2);
}

TEST_MAIN()