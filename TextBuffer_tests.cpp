#include "TextBuffer.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

TEST(test_left) {
    TextBuffer tester;
    tester.insert('a');
    ASSERT_EQUAL(tester.data_at_cursor(), 'a');//its not pointing to first element
    tester.insert('b');
    tester.insert('c');
    tester.insert('d');
    tester.insert('\n');
    ASSERT_EQUAL(tester.data_at_cursor(), '1');//wrong index
    tester.insert('1');
    tester.insert('2');
    tester.move_to_row_end();
    ASSERT_EQUAL(tester.data_at_cursor(), 'd');
    tester.backward();
    ASSERT_EQUAL(tester.data_at_cursor(), 'c');
    tester.forward();
    tester.forward();
    tester.forward();
    ASSERT_EQUAL(tester.data_at_cursor(), '1');//not the right data
    tester.move_to_row_end();
    ASSERT_EQUAL(tester.data_at_cursor(), '2');
    ASSERT_TRUE(true);
}

TEST_MAIN()
