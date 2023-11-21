#include "List.hpp"
#include "unit_test_framework.hpp"

using namespace std;

// Add your test cases here

TEST(test_stub) {
    // Add test code here
    ASSERT_TRUE(true);
}

TEST(test_push) {
    List<int> l;
    List<int>::Iterator i = l.begin();
    ASSERT_TRUE(l.empty())
    ASSERT_EQUAL(l.size(), 0)

    l.push_front(3);
    ASSERT_FALSE(l.empty())
    ASSERT_EQUAL(l.size(), 1)

    l.push_back(6);
    ASSERT_EQUAL(l.size(), 2)

    i = l.begin();
    ASSERT_EQUAL(*i, 3)
    ASSERT_EQUAL(*(++i), 6)

    l.clear();
    ASSERT_TRUE(l.empty())
    ASSERT_EQUAL(l.size(), 0)
    i = l.begin();
    ASSERT_EQUAL(i, l.end())

    l.push_back(4);
    ASSERT_FALSE(l.empty())
    ASSERT_EQUAL(l.size(), 1)

    l.push_front(5);
    ASSERT_EQUAL(l.size(), 2)

    i = l.begin();
    ASSERT_EQUAL(*i, 5)
    ASSERT_EQUAL(*(++i), 4)

    l.push_front(3);
    l.push_back(6);

    i = l.begin();
    ASSERT_EQUAL(*i, 3)
    ASSERT_EQUAL(*(++i), 5)
    ASSERT_EQUAL(*(++i), 4)
    ASSERT_EQUAL(*(++i), 6)
}

TEST(test_pop) {
    List<int> l;
    List<int>::Iterator i = l.begin();

    l.push_back(16);
    l.push_front(9);
    l.push_front(4);
    l.push_back(1);
    // 4, 9, 16, 1
    ASSERT_EQUAL(l.size(), 4)

    l.pop_back();
    ASSERT_EQUAL(l.size(), 3)
    i = l.begin();
    ASSERT_EQUAL(*i, 4)
    ASSERT_EQUAL(*(++i), 9)
    ASSERT_EQUAL(*(++i), 16)

    l.pop_front();
    ASSERT_EQUAL(l.size(), 2)
    i = l.begin();
    ASSERT_EQUAL(*i, 9)
    ASSERT_EQUAL(*(++i), 16)

    l.pop_front();
    ASSERT_EQUAL(l.size(), 1)
    i = l.begin();
    ASSERT_EQUAL(*i, 16)

    l.pop_back();
    ASSERT_EQUAL(l.size(), 0)
    ASSERT_TRUE(l.empty())

    l.push_back(11);
    l.push_back(13);
    // 11, 13

    l.pop_back();
    ASSERT_EQUAL(l.size(), 1)
    i = l.begin();
    ASSERT_EQUAL(*i, 11)

    l.pop_front();
    ASSERT_EQUAL(l.size(), 0)
    ASSERT_TRUE(l.empty())
}

TEST(test_iterator) {
    List<char> l;
    l.push_front('s');
    l.push_front('c');
    l.push_front('e');
    l.push_front('e');
    // 'e','e','c','s'

    List<char>::Iterator i = l.begin();
    ASSERT_EQUAL(*i, 'e');
    ++i;
    ASSERT_EQUAL(*i, 'e');
    ++i;
    ASSERT_EQUAL(*i, 'c');
    ++i;
    ASSERT_EQUAL(*i, 's');
    ASSERT_NOT_EQUAL(i, l.end())
    ++i;
    ASSERT_EQUAL(i, l.end())

    i = l.begin();
    ++i;
    ++i;
    List<char>::Iterator j = l.begin();
    ++j;
    ASSERT_FALSE(i == j)
    ASSERT_TRUE(i != j)
    ++j;
    ASSERT_TRUE(i == j)
    ASSERT_FALSE(i != j)
}

TEST(test_erase) {
    List<int> l;
    l.push_back(4);
    l.push_back(55);
    l.push_back(21);
    l.push_back(8);

    List<int>::Iterator i = l.begin();
    ++ ++i;
    l.erase(i);

    i = l.begin();
    ASSERT_EQUAL(*i, 4)
    ASSERT_EQUAL(*(++i), 55)
    ASSERT_EQUAL(*(++i), 8)

    ASSERT_EQUAL(l.size(), 3)

    i = l.begin();
    ++ ++i;
    l.erase(i);

    i = l.begin();
    ASSERT_EQUAL(*i, 4)
    ASSERT_EQUAL(*(++i), 55)

    ASSERT_EQUAL(l.size(), 2)

    l.erase(l.begin());
    i = l.begin();
    ASSERT_EQUAL(*i, 55)

    l.erase(l.begin());
    ASSERT_TRUE(l.empty())
}

TEST(test_insert) {
    List<int> l;
    l.insert(l.begin(), 7);
    ASSERT_EQUAL(l.back(), 7);
    ASSERT_EQUAL(l.size(), 1)

    l.pop_front();
    l.insert(l.end(), 9);
    ASSERT_EQUAL(l.front(), 9)
    ASSERT_EQUAL(l.size(), 1)

    l.insert(l.begin(), 8);
    ASSERT_EQUAL(l.front(), 8)
    ASSERT_EQUAL(l.back(), 9)
    ASSERT_EQUAL(l.size(), 2)

    l.pop_back();
    l.insert(l.end(), 10);
    ASSERT_EQUAL(l.front(), 8)
    ASSERT_EQUAL(l.back(), 10)
    ASSERT_EQUAL(l.size(), 2)

    l.insert(++l.begin(), 22);
    List<int>::Iterator i = l.begin();
    ASSERT_EQUAL(*i, 8)
    ASSERT_EQUAL(*(++i), 22)
    ASSERT_EQUAL(*(++i), 10)
}

TEST(test_front_back) {
    List<double> l;
    l.push_front(3.14);
    l.push_back(2.71828);

    ASSERT_EQUAL(l.front(), 3.14)
    ASSERT_EQUAL(l.back(), 2.71828)

    l.clear();
    l.push_back(1.618);

    ASSERT_EQUAL(l.front(), 1.618)
    ASSERT_EQUAL(l.back(), 1.618)
}

TEST(test_copy_ctor) {
    List<int> l;
    l.push_back(3);
    l.push_back(4);
    l.push_back(8);

    List<int> l2(l);
    ASSERT_EQUAL(l2.size(), 3)

    List<int>::Iterator i = l.begin();
    List<int>::Iterator i2 = l2.begin();

    for (; i != l.end(); ++i, ++i2) {
        ASSERT_EQUAL(*i, *i2)
    }

    l.push_back(5);
    ASSERT_EQUAL(l2.size(), 3)

    i2 = l2.begin();
    ASSERT_EQUAL(*i2, 3)
    ASSERT_EQUAL(*(++i2), 4)
    ASSERT_EQUAL(*(++i2), 8)
    ASSERT_TRUE(++i2 == l2.end())
}

TEST(test_assign_op) {
    List<int> l;
    l.push_back(-3);
    l.push_back(-4);
    l.push_back(-8);

    List<int> l2 = l;
    ASSERT_EQUAL(l2.size(), 3)

    List<int>::Iterator i = l.begin();
    List<int>::Iterator i2 = l2.begin();

    for (; i != l.end(); ++i, ++i2) {
        ASSERT_EQUAL(*i, *i2)
    }

    l.push_back(-5);
    ASSERT_EQUAL(l2.size(), 3)

    i2 = l2.begin();
    ASSERT_EQUAL(*i2, -3)
    ASSERT_EQUAL(*(++i2), -4)
    ASSERT_EQUAL(*(++i2), -8)
    ASSERT_TRUE(++i2 == l2.end())
}

TEST_MAIN()
