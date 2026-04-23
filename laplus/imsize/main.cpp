#include "img.hpp"
#include <iostream>

using namespace std;

void demonstrateImage() {
    cout << "\n=== Demonstration 1: Creating image and basic operations ===\n";
    Image img1(800, 600);
    cout << img1 << endl;

    cout << "\n=== Demonstration 2: Changing size WITHOUT proportions ===\n";
    img1.setProportionsMode(false);
    img1.setWidth(1920);
    cout << img1 << endl;
    img1.setHeight(1080);
    cout << img1 << endl;

    cout << "\n=== Demonstration 3: Changing size WITH proportions ===\n";
    Image img2(800, 600);
    cout << "Initial: " << img2 << endl;
    img2.setWidth(400);
    cout << img2 << endl;
    img2.setHeight(200);
    cout << img2 << endl;

    cout << "\n=== Demonstration 4: Fit to frame WITH proportions ===\n";
    Image img3(1920, 1080);
    cout << "Original: " << img3 << endl;
    img3.fitToFrame(800, 600);
    cout << img3 << endl;

    cout << "\n=== Demonstration 5: Fit to frame WITHOUT proportions ===\n";
    Image img4(1920, 1080);
    img4.setProportionsMode(false);
    cout << "Original: " << img4 << endl;
    img4.fitToFrame(800, 600);
    cout << img4 << endl;

    cout << "\n=== Demonstration 6: Trying to set invalid sizes ===\n";
    Image img5(100, 100);
    cout << img5 << endl;
    img5.setHeight(0);  
    img5.setWidth(-50); 
    cout << img5 << endl; 

    cout << "\n=== Demonstration 7: Square image proportion handling ===\n";
    Image img6(400, 400);
    cout << "Square image: " << img6 << endl;
    img6.setWidth(800);
    cout << "After width change: " << img6 << endl;
    img6.setHeight(200);
    cout << "After height change: " << img6 << endl;

    cout << "\n=== Demonstration 8: Switching modes dynamically ===\n";
    Image img7(1000, 500);
    cout << "Original: " << img7 << endl;
    img7.setWidth(2000);
    cout << img7 << endl;
    img7.setProportionsMode(false);
    img7.setHeight(3000);
    cout << img7 << endl;
    img7.setProportionsMode(true);
    img7.fitToFrame(500, 500);
    cout << img7 << endl;
}

int main() {
    demonstrateImage();
    return 0;
}