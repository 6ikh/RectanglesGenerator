#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
using namespace std;

// Structure (struct) is being defined to represent a rectangle
struct Rectangle {
//declaring two double variables, x & y, that will be used to represent the coordinates of the center of the rectangle
    double x, y; 
//declaring two double variables, width & height, that will be used for the width and height of the actual rectangle
    double width, height;
//declaring variable, angle, used to represent the orientation angle of the rectangle in degrees 
    double angle; 
};

// Function to generate random double in a specified range
double randomDouble(double min, double max) {
    return min + static_cast <double> (rand()) / (static_cast <double> (RAND_MAX / (max - min)));
}

// Function to check if two rectangles overlap
bool doRectanglesOverlap(const Rectangle& rect1, const Rectangle& rect2) {
    double dx = abs(rect1.x - rect2.x);
    double dy = abs(rect1.y - rect2.y);
    double halfWidthSum = (rect1.width + rect2.width) / 2;
    double halfHeightSum = (rect1.height + rect2.height) / 2;
    return dx <= halfWidthSum && dy <= halfHeightSum;
}

// Function to calculate the occlusion angle of a rectangle from the origin
double calculateOcclusionAngle(const Rectangle& rect) {
    double halfWidth = rect.width / 2;
    double halfHeight = rect.height / 2;
    double dist = sqrt(halfWidth * halfWidth + halfHeight * halfHeight);
    return atan2(dist, sqrt(rect.x * rect.x + rect.y * rect.y)) * 2 * 180 / M_PI;
}

int main() {
    int n;
    cout << "Enter the number of rectangles (n): ";
    cin >> n;

    vector<Rectangle> rectangles;

    for (int i = 0; i < n; ++i) {
        Rectangle rect;
        rect.width = randomDouble(1.0, 5.0); // Random width between 1 and 5
        rect.height = randomDouble(1.0, 5.0); // Random height between 1 and 5
        rect.x = randomDouble(-50.0, 50.0); // Random x-coordinate between -50 and 50
        rect.y = randomDouble(-50.0, 50.0); // Random y-coordinate between -50 and 50
        rect.angle = randomDouble(0.0, 360.0); // Random orientation angle between 0 and 360

        bool isOverlap = false;
        for (const Rectangle& existingRect : rectangles) {
            if (doRectanglesOverlap(rect, existingRect)) {
                isOverlap = true;
                break;
            }
        }

        if (!isOverlap) {
            rectangles.push_back(rect);
        } else {
            --i; // Retry generating this rectangle
        }
    }

    // Write the rectangle data to a text file
    ofstream outputFile("rectangles.txt");
    if (outputFile.is_open()) {
        for (const Rectangle& rect : rectangles) {
            outputFile << "Center: (" << rect.x << ", " << rect.y << "), Width: " << rect.width << ", Height: " << rect.height << ", Angle: " << rect.angle << " degrees\n";
        }
        outputFile.close();
        cout << "Rectangle data written to 'rectangles.txt'" << endl;
    } else {
        cerr << "Unable to open the output file." << endl;
    }

    double totalOcclusionAngle = 0.0;
    for (const Rectangle& rect : rectangles) {
        totalOcclusionAngle += calculateOcclusionAngle(rect);
    }

    cout << "Total occlusion angle over all rectangles: " << totalOcclusionAngle << " degrees" << endl;

    return 0;
}
