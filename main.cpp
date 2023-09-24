#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cstdlib>
#include <algorithm> 
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
//This line defines the function doRectanglesOverlap that takes two Rectangle objects, rect1 and rect2, as constant references (to avoid copying)
bool doRectanglesOverlap(const Rectangle& rect1, const Rectangle& rect2) {
//This line calculates the absolute difference between the x-coordinates of the two rectangles (rect1 and rect2) and stores it in the variable x 
//It represents the horizontal distance between the centers of the two rectangles.
    double x = abs(rect1.x - rect2.x);
//This line calculates the absolute difference between the y-coordinates of the two rectangles (rect1 and rect2) and stores it in the variable y 
//It represents the vertical distance between the centers of the two rectangles.
    double y = abs(rect1.y - rect2.y);
//This line calculates half of the sum of the widths of the two rectangles (rect1 and rect2) and stores it in the variable halfWidthSum. 
//This value represents half of the combined horizontal extent of the two rectangles.
    double halfWidthSum = (rect1.width + rect2.width) / 2;
//This line calculates half of the sum of the heights of the two rectangles (rect1 and rect2) and stores it in the variable halfHeightSum. 
//This value represents half of the combined vertical extent of the two rectangles.
    double halfHeightSum = (rect1.height + rect2.height) / 2;
//This line returns a boolean value based on the conditions that check whether the horizontal distance x is less than or equal to half of the combined horizontal extent 
//(halfWidthSum) and whether the vertical distance y is less than or equal to half of the combined vertical extent (halfHeightSum)
//If both conditions are true, it indicates that the two rectangles overlap, and the function returns true. Otherwise, it returns false.
    return x <= halfWidthSum && y <= halfHeightSum;
}
//This line defines the function calculateOcclusionAngle that takes a Rectangle object (rect) as a constant reference (to avoid copying) and returns a double value
double calculateOcclusionAngle(const Rectangle& rect) {
//This line calculates half of the width of the given rectangle (rect) and stores it in the variable halfWidth, It assumes that the width is non-negative
    double halfWidth = rect.width / 2;
//This line calculates half of the height of the given rectangle (rect) and stores it in the variable halfHeight. It assumes that the height is non-negative
    double halfHeight = rect.height / 2;
//This line calculates the Euclidean distance from the center of the rectangle to a point on its boundary (halfway between the center and a corner)
//It uses the Pythagorean theorem to calculate the distance based on the half-width and half-height of the rectangle. The result is stored in the variable dist
    double dist = sqrt(halfWidth * halfWidth + halfHeight * halfHeight);
//This calculates the arctangent of the ratio between dist and the magnitude of the vector defined by rect.x and rect.y, 
//the result of atan2 is then multiplied by 2 to account for the angle span from one side of the rectangle to the other 
//Then the result is multiplied by 180 / M_PI to convert the angle from radians to degrees
    return atan2(dist, sqrt(rect.x * rect.x + rect.y * rect.y)) * 2 * 180 / M_PI;
}
//This line defines the function compareRectangles that takes two Rectangle objects, rect1 and rect2, as constant references and returns a boolean value.
bool compareRectangles(const Rectangle& rect1, const Rectangle& rect2) {
//This compares the angle member variable of rect1 with the angle member variable of rect2.
//The function returns true if rect1.angle is less than rect2.angle, indicating that rect1 has a smaller angle value and should be considered "less" than rect2 in terms of angle.
//It returns false otherwise, indicating that rect1 has a larger angle value or the angles are equal
    return rect1.angle < rect2.angle;
}
//Define the main function
int main() {
//This declares an integer variable n without initializing it
    int n;
//This line prints a message to the standard output (cout) asking the user to enter the number of rectangles they want to generate
    cout << "Enter the number of rectangles (n): ";
//This line reads an integer value entered by the user from the standard input (cin) and assigns it to the variable n
    cin >> n;
//This line declares a vector named rectangles that will hold instances of the Rectangle struct
    vector<Rectangle> rectangles;
//This line starts a loop that will run n times, creating n random rectangles
    for (int i = 0; i < n; ++i) {
//This line declares a variable rect of type Rectangle. It represents the current rectangle being generated.
        Rectangle rect;
//This line assigns a random width value between 1.0 and 5.0 to the width member of the rect struct
        rect.width = randomDouble(1.0, 5.0);
//This line assigns a random height value between 1.0 and 5.0 to the height member of the rect struct
        rect.height = randomDouble(1.0, 5.0);
//This line assigns a random x-coordinate value between -50.0 and 50.0 to the x member of the rect struct
        rect.x = randomDouble(-50.0, 50.0);
//This line assigns a random y-coordinate value between -50.0 and 50.0 to the y member of the rect struct
        rect.y = randomDouble(-50.0, 50.0);
//This line assigns a random angle value between 0.0 and 360.0 degrees to the angle member of the rect struct
        rect.angle = randomDouble(0.0, 360.0);
//This line initializes a boolean variable isOverlap to false. It will be used to check if the current rectangle overlaps with any existing rectangles in the rectangles vector
        bool isOverlap = false;
//This line starts a loop that iterates through each Rectangle object (existingRect) in the rectangles vector. It uses a range-based for loop to simplify the iteration
        for (const Rectangle& existingRect : rectangles) {
//Inside the loop, this line calls the doRectanglesOverlap function to check if the current rect (the one being generated) overlaps with the existingRect (an already generated rectangle)
            if (doRectanglesOverlap(rect, existingRect)) {
//If the condition in the previous line evaluates to true, it means there is an overlap between the current rect and an existing rectangle. 
//This line sets the isOverlap variable to true to indicate that an overlap has been found
                isOverlap = true;
//This line exits the loop as soon as an overlap is detected. It prevents further iterations through the existing rectangles since we've already determined that there's an overlap
                break;
            }
        }
//After the loop that checks for overlap with existing rectangles, this line checks if isOverlap is still false, which means no overlap was found
        if (!isOverlap) {
//If no overlap is found, this line adds the current rect (the one being generated) to the rectangles vector, as it is a non-overlapping rectangle
            rectangles.push_back(rect);
//If an overlap is found, this section of code is executed. It decrements the loop variable i to ensure that the current iteration (generating the overlapping rectangle) is repeated. 
//This essentially discards the current rect and generates a new one in the next iteration to ensure that it does not overlap with existing rectangles.
        } else {
            --i;
        }
    }

// Sort the rectangles based on their angles
    sort(rectangles.begin(), rectangles.end(), compareRectangles);
// Opens a file named "rectangles.txt" for outputing the points using an ofstream object called outputFile
    ofstream outputFile("rectangles.txt");
// Checks if the file was successfully opened for writing using the is_open() method of the ofstream object
    if (outputFile.is_open()) {
// For each Rectangle object in the collection, this writes information about the rectangle's center, width, height, and angle to the output file using the << operator
        for (const Rectangle& rect : rectangles) {
            outputFile << "Center: (" << rect.x << ", " << rect.y << "), Width: " << rect.width << ", Height: " << rect.height << ", Angle: " << rect.angle << " degrees\n";
        }
//After writing all the rectangle data, close the output file
        outputFile.close();
//Print a message to the standard output (cout) indicating that the rectangle data has been written to the file
        cout << "Rectangle point data has been written to 'rectangles.txt'" << endl;
    } else {
//if the file cannot be opened, a error message is outputed
        cout << "Unable to open the output file." << endl;
    }
//This code calculates the total occlusion angle over all rectangles by iterating through the same collection of Rectangle objects and calling the calculateOcclusionAngle(rect) function for each one. 
//The results are accumulated in the totalOcclusionAngle variable
    double totalOcclusionAngle = 0.0;
    for (const Rectangle& rect : rectangles) {
        totalOcclusionAngle += calculateOcclusionAngle(rect);
    }
//Finally, it prints the total occlusion angle over all rectangles to the standard output
    cout << "Total occlusion angle over all rectangles: " << totalOcclusionAngle << " degrees" << endl;
    
    return 0;
}
