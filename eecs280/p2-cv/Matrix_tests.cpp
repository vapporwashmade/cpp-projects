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

    int *elem = Matrix_at(mat, 0, 0);
    ASSERT_EQUAL(Matrix_row(mat, elem), 0)
    ASSERT_EQUAL(Matrix_column(mat, elem), 0)

    elem = Matrix_at(mat, 499, 499);
    ASSERT_EQUAL(Matrix_row(mat, elem), 499)
    ASSERT_EQUAL(Matrix_column(mat, elem), 499)

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
                                                                    1, width),
                 width - 1);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, height - 1, width - 1, width),
                 -1);

    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, height - 2, width -
                                                                    2, width),
                 width - 1);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, height - 2, width -
                                                          2, width), -1);

    ASSERT_EQUAL(Matrix_min_value_in_row(mat, height - 1, 0, 1),
                 *Matrix_at(mat, height - 1, 0))
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, height - 1, 0, 1), 0)
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, width - 1, width),
                 *Matrix_at(mat, 0, width - 1))
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, width - 1, width),
                 width - 1)

    // print test
    ostringstream expected;
    expected << width << ' ' << height << '\n';
    for (int c = 0; c < width; ++c) {
        expected << -1 << ' ';
    }
    expected << '\n';

    for (int r = 1; r < height - 1; ++r) {
        expected << -1 << ' ';
        for (int c = 1; c < width - 1; ++c) {
            expected << 0 << ' ';
        }
        expected << -1 << ' ' << '\n';
    }

    for (int c = 0; c < width; ++c) {
        expected << -1 << ' ';
    }
    expected << '\n';

    ostringstream actual;
    Matrix_print(mat, actual);
    ASSERT_EQUAL(actual.str(), expected.str())

    delete mat;
}

TEST(max_fill_2) {
    Matrix *mat = new Matrix;

    const int width = MAX_MATRIX_WIDTH;
    const int height = MAX_MATRIX_HEIGHT;
    const int value = -2;
    Matrix_init(mat, width, height);
    Matrix_fill(mat, -2);

    for (int r = 0; r < height; ++r) {
        for (int c = 0; c < width; ++c) {
            ASSERT_EQUAL(*Matrix_at(mat, r, c), value);
        }
    }

    int *elem = Matrix_at(mat, 0, 0);
    ASSERT_EQUAL(Matrix_row(mat, elem), 0)
    ASSERT_EQUAL(Matrix_column(mat, elem), 0)

    elem = Matrix_at(mat, 499, 499);
    ASSERT_EQUAL(Matrix_row(mat, elem), 499)
    ASSERT_EQUAL(Matrix_column(mat, elem), 499)

    ASSERT_EQUAL(Matrix_max(mat), -2);

    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 100, 200), 100);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 100, 200), -2);

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

    ASSERT_EQUAL(Matrix_max(mat), -1);

    // for row with all values -1
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 100, 200), 100);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 100, 200), -1);

    // for region with all values 0
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 100, 200), 100);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 100, 200), -2);

    // for mixed region
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 1, 0, 100), 1);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 1, 0, 100), -2);

    // EDGE CASES FOR MIN VALUE FUNCTIONS ABOVE
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, height - 1, width -
                                                                    1, width),
                 width - 1);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, height - 1, width - 1, width),
                 -1);

    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, height - 2, width -
                                                                    2, width),
                 width - 2);
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, height - 2, width -
                                                          2, width), -2);

    ASSERT_EQUAL(Matrix_min_value_in_row(mat, height - 1, 0, 1),
                 *Matrix_at(mat, height - 1, 0))
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, height - 1, 0, 1), 0)
    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, width - 1, width),
                 *Matrix_at(mat, 0, width - 1))
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, width - 1, width),
                 width - 1)

    // print test
    ostringstream expected;
    expected << width << ' ' << height << '\n';
    for (int c = 0; c < width; ++c) {
        expected << -1 << ' ';
    }
    expected << '\n';

    for (int r = 1; r < height - 1; ++r) {
        expected << -1 << ' ';
        for (int c = 1; c < width - 1; ++c) {
            expected << -2 << ' ';
        }
        expected << -1 << ' ' << '\n';
    }

    for (int c = 0; c < width; ++c) {
        expected << -1 << ' ';
    }
    expected << '\n';

    ostringstream actual;
    Matrix_print(mat, actual);
    ASSERT_EQUAL(actual.str(), expected.str())

    delete mat;
}

TEST(test_fill_and_border_basic) {
    auto mat = new Matrix;
    Matrix_init(mat, 3, 3);
    Matrix_fill(mat, 4);

    ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 4)
    ASSERT_EQUAL(*Matrix_at(mat, 0, 2), 4)
    ASSERT_EQUAL(*Matrix_at(mat, 2, 0), 4)
    ASSERT_EQUAL(*Matrix_at(mat, 2, 2), 4)
    ASSERT_EQUAL(*Matrix_at(mat, 1, 1), 4)

    Matrix_fill_border(mat, 6);

    ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 6)
    ASSERT_EQUAL(*Matrix_at(mat, 0, 2), 6)
    ASSERT_EQUAL(*Matrix_at(mat, 2, 0), 6)
    ASSERT_EQUAL(*Matrix_at(mat, 2, 2), 6)
    ASSERT_EQUAL(*Matrix_at(mat, 1, 1), 4)

    Matrix_fill(mat, 8);

    ASSERT_EQUAL(*Matrix_at(mat, 0, 0), 8)
    ASSERT_EQUAL(*Matrix_at(mat, 0, 2), 8)
    ASSERT_EQUAL(*Matrix_at(mat, 2, 0), 8)
    ASSERT_EQUAL(*Matrix_at(mat, 2, 2), 8)
    ASSERT_EQUAL(*Matrix_at(mat, 1, 1), 8)

    delete mat;
}

TEST(test_at_bounds) {
    auto matrix = new Matrix;
    int width = 4;
    int height = 4;
    Matrix_init(matrix, width, height);
    Matrix_fill(matrix, 2);

    // check all edge values
    ASSERT_EQUAL(*Matrix_at(matrix, 0, 0), 2)
    ASSERT_EQUAL(*Matrix_at(matrix, height - 1, width - 1), 2)
    ASSERT_EQUAL(*Matrix_at(matrix, 0, width - 1), 2)
    ASSERT_EQUAL(*Matrix_at(matrix, height - 1, 0), 2)

    // 0, 0 and height - 1, width - 1
    *Matrix_at(matrix, 0, 0) = 5;
    *Matrix_at(matrix, height - 1, width - 1) = 5;

    ASSERT_EQUAL(*Matrix_at(matrix, 0, 0), 5)
    ASSERT_EQUAL(*Matrix_at(matrix, height - 1, width - 1), 5)

    // other two corners
    *Matrix_at(matrix, 0, width - 1) = 6;
    *Matrix_at(matrix, height - 1, 0) = 6;

    ASSERT_EQUAL(*Matrix_at(matrix, 0, width - 1), 6)
    ASSERT_EQUAL(*Matrix_at(matrix, height - 1, 0), 6)

    ostringstream actual{
            "4 4\n5 2 2 6 \n2 2 2 2 \n2 2 2 2 \n6 2 2 5 \n"
    };
    ostringstream expected;
    Matrix_print(matrix, expected);
    ASSERT_EQUAL(expected.str(), actual.str())

    delete matrix;
}

TEST(test_max) {
    auto matrix = new Matrix;
    int width = 4;
    int height = 4;
    Matrix_init(matrix, width, height);
    Matrix_fill(matrix, 3);

    // 0,0 test
    *Matrix_at(matrix, 0, 0) = 5;

    ASSERT_EQUAL(Matrix_max(matrix), 5)

    // height-1,width-1 test
    *Matrix_at(matrix, height - 1, width - 1) = 7;

    ASSERT_EQUAL(Matrix_max(matrix), 7)

    // 0,width-1 test
    *Matrix_at(matrix, 0, width - 1) = 9;

    ASSERT_EQUAL(Matrix_max(matrix), 9)

    // height-1,0 test
    *Matrix_at(matrix, height - 1, 0) = 11;

    ASSERT_EQUAL(Matrix_max(matrix), 11)

    ostringstream actual{
            "4 4\n5 3 3 9 \n3 3 3 3 \n3 3 3 3 \n11 3 3 7 \n"
    };
    ostringstream expected;
    Matrix_print(matrix, expected);
    ASSERT_EQUAL(expected.str(), actual.str())

    delete matrix;
}

TEST(test_smallest_possible) {
    auto mat = new Matrix;
    Matrix_init(mat, 1, 1);
    Matrix_fill(mat, -2);

    ASSERT_EQUAL(*Matrix_at(mat, 0, 0), -2);
    ASSERT_EQUAL(Matrix_max(mat), -2)

    int *elem = Matrix_at(mat, 0, 0);

    ASSERT_EQUAL(Matrix_row(mat, elem), 0)
    ASSERT_EQUAL(Matrix_column(mat, elem), 0)

    Matrix_fill_border(mat, -3);

    ASSERT_EQUAL(Matrix_row(mat, elem), 0)
    ASSERT_EQUAL(Matrix_column(mat, elem), 0)

    ASSERT_EQUAL(*Matrix_at(mat, 0, 0), -3);
    ASSERT_EQUAL(Matrix_max(mat), -3)

    ASSERT_EQUAL(Matrix_min_value_in_row(mat, 0, 0, 1), -3)
    ASSERT_EQUAL(Matrix_column_of_min_value_in_row(mat, 0, 0, 1), 0)

    delete mat;
}

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
