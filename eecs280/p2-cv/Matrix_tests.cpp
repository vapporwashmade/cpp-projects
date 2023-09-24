#include "Matrix.hpp"
#include "Matrix_test_helpers.hpp"
#include "unit_test_framework.hpp"

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Fills a 3x5 Matrix with a value and checks
// that Matrix_at returns that value for each element.
TEST(test_fill_basic) {
    Matrix *mat = new Matrix; // create a Matrix in dynamic memory

    const int width = 3;
    const int height = 5;
    const int value = 42;
    Matrix_init(mat, 3, 5);
    Matrix_fill(mat, value);

    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
        }
    }

    delete mat; // delete the Matrix
}

// ADD YOUR TESTS HERE
// You are encouraged to use any functions from Matrix_test_helpers.hpp as needed.
TEST(max_fill) {
    Matrix *mat = new Matrix;

    const int width = MAX_MATRIX_WIDTH;
    const int height = MAX_MATRIX_HEIGHT;
    const int value = 0;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, 0);

    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
        }
    }

    ASSERT_EQUAL(Matrix_max(mat), 0);

    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 100, 200), 100);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 100, 200), 0);

    // fill matrix border
    Matrix_fill_border(mat, -1);

    for (int r = 1; r < height - 1; ++r) {
        for (int c = 1; c < width - 1; ++c) {
            ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
        }
    }

    for (int r = 0; r < height; ++r) {
        ASSERT_EQUAL(*Matrix_at(mat, r, 0), -1);
        ASSERT_EQUAL(*Matrix_at(mat, r, width - 1), -1);
    }

    for (int c = 0; c < width; ++c) {
        ASSERT_EQUAL(*Matrix_at(mat, 0, c), -1);
        ASSERT_EQUAL(*Matrix_at(mat, height - 1, c), -1);
    }

    ASSERT_EQUAL(Matrix_max(mat), 0);

    // for row with all values -1
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 100, 200), 100);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 100, 200), -1);

    // for region with all values 0
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 100, 200), 100);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 100, 200), 0);

    // for mixed region
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 400, 500), 499);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 400, 500), -1);

    // EDGE CASES FOR MIN VALUE FUNCTIONS ABOVE
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, height - 1, width -
    1, width), width - 1);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, height - 1, width - 1, width),
                 -1);

    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, height - 2, width -
                                                                    2, width)
                 , width - 1);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, height - 2, width -
                                                          2, width)
    , -1);

    delete mat;
}

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
