#include "arrays.hpp"
#include "unit_test_framework.hpp"

// We define a test case with the TEST(<test_name>) macro.
// <test_name> can be any valid C++ function name.
TEST(true_is_true) {
    ASSERT_TRUE(true);
}

TEST(numbers_are_equal) {
    ASSERT_EQUAL(42, 42);
}

// User-created tests
bool compare_arrays(int arr1[], int size1, int arr2[], int size2) {
    if (size1 != size2) {
        return false;
    }

    for (int i = 0; i < size1; ++i) {
        if (arr1[i] != arr2[i]) {
            return false;
        }
    }

    return true;
}

TEST(test_slide_right_1) {
    int testing[] = { 4, 0, 1, 3, 3 };
    int correct[] = { 3, 4, 0, 1, 3 };
    slideRight(testing, 5);
    ASSERT_TRUE(compare_arrays(testing, 5, correct, 5));
}

TEST(test_flip_1) {
    int testing[] = { 4, 0, 1, 3, 3 };
    int correct[] = { 3, 3, 1, 0, 4 };
    flip(testing, 5);
    ASSERT_TRUE(compare_arrays(testing, 5, correct, 5));
}

TEST(test_slide_right_2) {
    int testing[] = { 3, 3, 3, 3, 3 };
    int correct[] = { 3, 3, 3, 3, 3 };
    slideRight(testing, 5);
    ASSERT_TRUE(compare_arrays(testing, 5, correct, 5));
}

TEST(test_slide_right_3) {
    int testing[] = { 4};
    int correct[] = { 4 };
    slideRight(testing, 1);
    ASSERT_TRUE(compare_arrays(testing, 1, correct, 1));
}

TEST(test_flip_2) {
    int testing[] = { 4, 0, 1, 3 };
    int correct[] = { 3, 1, 0, 4 };
    flip(testing, 4);
    ASSERT_TRUE(compare_arrays(testing, 4, correct, 4));
}

TEST(test_flip_3) {
    int testing[] = { 4};
    int correct[] = { 4};
    flip(testing, 1);
    ASSERT_TRUE(compare_arrays(testing, 1, correct, 1));
}

TEST_MAIN() // No semicolon!