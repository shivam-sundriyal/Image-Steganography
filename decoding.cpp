#include <iostream>

#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

// Checks whether the bit is set or not at a particular position.
// Returns true if set
// Returns false if not set
bool Bitset(char ch, int pos)
{
    // 7 6 5 4 3 2 1 0
    ch = ch >> pos;
    if (ch & 1)
        return true;
    return false;
}

int main()
{

    // Add location of encoded image here -->
    auto filename = "D:/Stegano/EncryptedImage.jpg";
    Mat image = imread(filename);

    if (image.empty())
    {
        cout << "Image Error\n";
        exit(-1);
    }

    // char to work on
    char ch = 0;
    // contains information about which bit of char to work on
    int count_bits = 0;

    for (int rows = 0; rows < image.rows; rows++)
    {
        for (int cols = 0; cols < image.cols; cols++)
        {
            for (int colour = 0; colour < 3; colour++)
            {

                // stores the pixel details
                Vec3b pixels = image.at<Vec3b>(Point(rows, cols));

                // manipulate char bits according to the LSB of pixel values
                if (Bitset(pixels.val[colour], 0))
                    ch |= 1;

                // increment bit_count to work on next bit
                count_bits++;

                // bit_count is 8, that means we got our char from the encoded image
                if (count_bits == 8)
                {

                    // NULL char is encountered
                    if (ch == '\0')
                        goto ENDLOOP;

                    count_bits = 0;
                    cout << ch;
                    ch = 0;
                }
                else
                {
                    ch = ch << 1;
                }
            }
        }
    }
ENDLOOP:;

    String geek_window = "Encrypted Image";
    imshow(geek_window, image);

    waitKey(0);

    destroyWindow(geek_window);

    cout << "\nWe were successfully able to decode" << endl;

    return 0;
}
