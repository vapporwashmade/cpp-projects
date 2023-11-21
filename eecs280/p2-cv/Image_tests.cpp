#include "Image_test_helpers.hpp"
#include "unit_test_framework.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <fstream>

using namespace std;


// Here's a free test for you! Model yours after this one.
// Test functions have no interface and thus no RMEs, but
// add a comment like the one here to say what it is testing.
// -----
// Sets various pixels in a 2x2 Image and checks
// that Image_print produces the correct output.
TEST(test_print_basic) {
    Image *img = new Image; // create an Image in dynamic memory

    const Pixel red = {255, 0, 0};
    const Pixel green = {0, 255, 0};
    const Pixel blue = {0, 0, 255};
    const Pixel white = {255, 255, 255};

    Image_init(img, 2, 2);
    Image_set_pixel(img, 0, 0, red);
    Image_set_pixel(img, 0, 1, green);
    Image_set_pixel(img, 1, 0, blue);
    Image_set_pixel(img, 1, 1, white);

    // Capture our output
    ostringstream s;
    Image_print(img, s);

    // Correct output
    ostringstream correct;
    correct << "P3\n2 2\n255\n";
    correct << "255 0 0 0 255 0 \n";
    correct << "0 0 255 255 255 255 \n";
    ASSERT_EQUAL(s.str(), correct.str());

    delete img; // delete the Image
}

// IMPLEMENT YOUR TEST FUNCTIONS HERE
// You are encouraged to use any functions from Image_test_helpers.hpp as needed.

TEST(test_get_set_pixel_fill) {
    Image *img = new Image;

    Image_init(img, 2, 2);

    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 1, 1), {0, 0, 0}))

    Image_fill(img, {0, 255, 0});

    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 1, 1), {0, 255, 0}))

    Image_set_pixel(img, 1, 1, {255, 0, 255});

    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 0, 1), {0, 255, 0}))
    ASSERT_TRUE(Pixel_equal(Image_get_pixel(img, 1, 1), {255, 0, 255}))

    delete img;
}

// Tests the Image_width and Image_height functions, along with Image_init
// and Image_print
TEST(test_init_print) {
    Image *img = new Image;
    std::ifstream dogin{"dog.ppm"};

    Image_init(img, dogin);

    ASSERT_EQUAL(Image_width(img), 5)
    ASSERT_EQUAL(Image_height(img), 5)

    ostringstream dogout;
    Image_print(img, dogout);
    string dogoutcorrect{
            "P3\n"
            "5 5\n"
            "255\n"
            "0 0 0 0 0 0 255 255 250 0 0 0 0 0 0 \n"
            "255 255 250 126 66 0 126 66 0 126 66 0 255 255 250 \n"
            "126 66 0 0 0 0 255 219 183 0 0 0 126 66 0 \n"
            "255 219 183 255 219 183 0 0 0 255 219 183 255 219 183 \n"
            "255 219 183 0 0 0 134 0 0 0 0 0 255 219 183 \n"};

    ASSERT_EQUAL(dogout.str(), dogoutcorrect)

    delete img;
}

// NOTE: The unit test framework tutorial in Lab 2 originally
// had a semicolon after TEST_MAIN(). Although including and
// excluding the semicolon are both correct according to the c++
// standard, the version of g++ we are using reports a warning
// when there is a semicolon. Therefore do NOT add a semicolon
// after TEST_MAIN()
TEST_MAIN() // Do NOT put a semicolon here
