#include <iostream>
#include <fstream>
#include <string>
#include "Image.hpp"
#include "processing.hpp"

using namespace std;

static void error_print();

static bool error_arg_check(int &argc);

static bool error_dimension_check(const int &new_w, const int &new_h, const int
&width, const int &height);

int main(int argc, char **argv) {
    if (!error_arg_check(argc)) {
        error_print();
        return 1;
    }

    Image *img = new Image;
    ifstream infile{argv[1]};

    if (!infile.is_open()) {
        cout << "Error opening file: " << argv[1] << endl;
        return 1;
    }

    Image_init(img, infile);
    int width = stoi(argv[3]);
    int height = Image_height(img);
    if (argc == 5) {
        height = stoi(argv[4]);
    }

    if (!error_dimension_check(width, height, Image_width(img),
                               Image_height(img))) {
        error_print();
        return 1;
    }

    ofstream outfile{argv[2]};
    seam_carve(img, width, height);
    Image_print(img, outfile);

    delete img;

    return 0;
}

//TODO style checks
//TODO submit to autograder
static void error_print() {
    cout << "Usage: resize.exe IN_FILENAME OUT_FILENAME WIDTH [HEIGHT]\n"
         << "WIDTH and HEIGHT must be less than or equal to original" << endl;
}

static bool error_arg_check(int &argc) {
    return argc == 4 || argc == 5;
}

static bool error_dimension_check(const int &new_w, const int &new_h, const int
&width, const int &height) {
    return new_w > 0 && new_h > 0 && new_w <= width && new_h <= height;
}