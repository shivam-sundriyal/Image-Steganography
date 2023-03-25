#include <iostream>
#include <fstream>

#include <opencv2/highgui.hpp>
#include <opencv2/opencv.hpp>
#include <opencv2/imgproc.hpp>

using namespace std;
using namespace cv;

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

    // Enter path of input image here -->
    auto filename = "D:/Stegano/IMAGE.jpg";
    Mat image = imread(filename);
    if (image.empty())
    {
        cout << "Cannot load Image.\n";
        exit(-1);
    }
    imshow("Image", image);

    waitKey();

    // Enter path of text file here->
    auto filename2 = "D:/Stegano/hidden_text.txt";
    ifstream file(filename2);
    if (!file.is_open())
    {
        cout << "Cannot open file.\n";
        exit(-1);
    }

    // char to work on
    char ch;
    // reads the first char from the file
    file.get(ch);
    // contains information about which bit of char to work on
    int count_bits = 0;
    // to check whether file has ended
    bool end_file = false;
    // to check if the whole message is encoded or not
    bool encoded = false;

    for (int rows = 0; rows < image.rows; rows++)
    {
        for (int cols = 0; cols < image.cols; cols++)
        {
            for (int colour = 0; colour < 3; colour++)
            {

                // stores the pixel details
                Vec3b pixels = image.at<Vec3b>(Point(rows, cols));

                // if bit is 1 : change LSB of present color value to 1.
                // if bit is 0 : change LSB of present color value to 0.
                if (Bitset(ch, 7 - count_bits))
                    pixels.val[colour] |= 1;
                else
                    pixels.val[colour] &= ~1;

                // update the image with the changed pixel values
                image.at<Vec3b>(Point(rows, cols)) = pixels;

                // increment bit_count to work on next bit
                count_bits++;

                // if last_null_char is true and bit_count is 8, then our message is successfully encode.
                if (end_file && count_bits == 8)
                {
                    encoded = true;
                    goto ENDLOOP;
                }

                // if bit_count is 8 we pick the next char from the file and work on it
                if (count_bits == 8)
                {
                    count_bits = 0;
                    file.get(ch);

                    // if EndOfFile(EOF) is encountered insert NULL char to the image
                    if (file.eof())
                    {
                        end_file = true;
                        ch = '\0';
                    }
                }
            }
        }
    }
ENDLOOP:;

    // whole message was not encoded
    if (!encoded)
    {
        cout << "Message too big .Cannot Encode . Try with larger image or try shorter text.\n";
        exit(-1);
    }

    destroyAllWindows();

    // Writes the stegnographic image
    // Create a local output image file with no content in it.
    auto filename3 = "______________";

    bool check = imwrite(filename3, image);

    if (check == false)
    {
        cout << "Mission- SAVING THE ENCRYPTED IMAGE failed successfully." << endl;
        cin.get(); // Waiting for user to press any key.
        return -1;
    }
    cout << "Sucessfully encrypted the image" << endl;

    String geek_window = "My Saved Image.";

    namedWindow(geek_window);
    imshow(geek_window, image);

    waitKey(0);

    destroyWindow(geek_window);

    return 0;
}

