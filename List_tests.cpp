#include "List.hpp"
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
    ASSERT_TRUE(list1.size() == list2.size());
    ASSERT_TRUE(list1.front() == list2.front());
    ASSERT_TRUE(list1.back() == list2.back());
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

    // it++;
    // ASSERT_EQUAL(*it, 2);

    // Test Iterator Assignment and Equality and Inequality
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
    
    //same size
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
    ASSERT_TRUE(list2.front() + 1 == 2);
    ASSERT_TRUE(list2.back() == 4);
    ASSERT_TRUE(list2.back() - 1 == 3);

    //empty
    List<int> list3;
    List<int> list4;

    list3.push_back(1);
    list3.push_back(2);
    list3.push_back(3);
    list3.push_back(4);

    list3 = list4;
    ASSERT_TRUE(list3.empty());

    //different size
    List<int> list5;
    List<int> list6;

    list5.push_back(1);
    list5.push_back(2);
    list5.push_back(3);

    list6.push_back(5);
    list6.push_back(6);
    list6.push_back(7);
    list6.push_back(8);

    list5 = list6;
    ASSERT_TRUE(list5.size() == 4);
    ASSERT_TRUE(list5.front() == 5);
    ASSERT_TRUE(list5.back() == 8);

    //self assignment
    List<int> list7;

    List<int> & copy = list7;
    copy = list7;

    ASSERT_TRUE(copy.size() == 0);

}

TEST(test_erase){

    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    List<int>::Iterator it = list.begin();
    ++it;
    //erased_next is the value after the term that was erased
    List<int>::Iterator erased_next = list.erase(it);

    ASSERT_TRUE(list.size() == 2);
    ASSERT_TRUE(*erased_next == 3);

    erased_next = list.erase(list.begin());

    ASSERT_TRUE(list.size() == 1);
    ASSERT_TRUE(*erased_next == 3);

    //test erasing the back
    //***Causing issues for now as well
    List<int> list2;
    list2.push_back(1);
    list2.push_back(2);
    list2.push_back(3);

    List<int>::Iterator it2 = list2.end();
    --it2;
    List<int>::Iterator erased_next2 = list2.erase(it2);
    ASSERT_TRUE(list2.size() == 2);
    ASSERT_TRUE(erased_next2 == list2.end());

}

TEST(test_insert){

    List<int> list;
    list.push_back(1);
    list.push_back(2);
    list.push_back(3);

    List<int>::Iterator it = list.begin();
    ++it;

    //insert in the middle
    List<int>::Iterator inserted = list.insert(it, 7);
    ASSERT_TRUE(list.size() == 4);
    ASSERT_TRUE(*inserted == 7);

    //insert in the front
    it = list.begin();
    inserted = list.insert(it, 8);
    ASSERT_TRUE(list.size() == 5);
    ASSERT_TRUE(list.front() == 8);

    //insert in the end
    it = list.end();
    inserted = list.insert(it, 9);
    ASSERT_TRUE(list.size() == 6);
    ASSERT_TRUE(list.back() == 9);

}



TEST_MAIN()