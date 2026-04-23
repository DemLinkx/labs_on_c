#include "img.hpp"
#include <cmath>

using namespace std;

bool Image::isValidSize(int size) const {
    return size > 0;
}

void Image::updateWithProportions(int newHeight, int newWidth, bool changeHeight) {
    if (changeHeight) {
        if (newHeight > 0 && width > 0) {
            double ratio = static_cast<double>(width) / height;
            int newWidthCalculated = static_cast<int>(round(newHeight * ratio));
            if (newWidthCalculated > 0) {
                height = newHeight;
                width = newWidthCalculated;
            }
        }
    } else {
        if (newWidth > 0 && height > 0) {
            double ratio = static_cast<double>(height) / width;
            int newHeightCalculated = static_cast<int>(round(newWidth * ratio));
            if (newHeightCalculated > 0) {
                width = newWidth;
                height = newHeightCalculated;
            }
        }
    }
}

Image::Image(int h, int w) : keepProportions(true) {
    if (isValidSize(h) && isValidSize(w)) {
        height = h;
        width = w;
        cout << "Image created successfully! Size: " << width << "x" << height << endl;
    } else {
        height = 1;
        width = 1;
        cout << "Warning: Invalid size provided. Image created with default size 1x1" << endl;
    }
}

int Image::getHeight() const {
    return height;
}

int Image::getWidth() const {
    return width;
}

void Image::setHeight(int newHeight) {
    if (!isValidSize(newHeight)) {
        cout << "Error: Height must be positive!" << endl;
        return;
    }

    if (keepProportions) {
        updateWithProportions(newHeight, 0, true);
        cout << "Height changed to " << height << ", width adjusted to " << width << " (proportions kept)" << endl;
    } else {
        height = newHeight;
        cout << "Height changed to " << height << endl;
    }
}

void Image::setWidth(int newWidth) {
    if (!isValidSize(newWidth)) {
        cout << "Error: Width must be positive!" << endl;
        return;
    }

    if (keepProportions) {
        updateWithProportions(0, newWidth, false);
        cout << "Width changed to " << width << ", height adjusted to " << height << " (proportions kept)" << endl;
    } else {
        width = newWidth;
        cout << "Width changed to " << width << endl;
    }
}

void Image::fitToFrame(int frameWidth, int frameHeight) {
    if (!isValidSize(frameWidth) || !isValidSize(frameHeight)) {
        cout << "Error: Frame dimensions must be positive!" << endl;
        return;
    }

    if (keepProportions) {
        double widthRatio = static_cast<double>(frameWidth) / width;
        double heightRatio = static_cast<double>(frameHeight) / height;
        double scale = min(widthRatio, heightRatio);

        int newWidth = static_cast<int>(round(width * scale));
        int newHeight = static_cast<int>(round(height * scale));

        if (newWidth > 0 && newHeight > 0) {
            width = newWidth;
            height = newHeight;
            cout << "Image fitted to frame " << frameWidth << "x" << frameHeight
                 << ". New size: " << width << "x" << height << " (proportions kept)" << endl;
        }
    } else {
        if (frameWidth > 0 && frameHeight > 0) {
            width = frameWidth;
            height = frameHeight;
            cout << "Image fitted to frame " << frameWidth << "x" << frameHeight
                 << ". New size: " << width << "x" << height << " (proportions NOT kept)" << endl;
        }
    }
}

void Image::setProportionsMode(bool keep) {
    keepProportions = keep;
    cout << "Proportions mode changed to: " << (keep ? "KEEP" : "NOT KEEP") << endl;
}

bool Image::getProportionsMode() const {
    return keepProportions;
}

ostream& operator<<(ostream& os, const Image& img) {
    os << "Image[" << img.width << "x" << img.height << "]";
    if (img.keepProportions) {
        os << " (proportions: kept)";
    } else {
        os << " (proportions: not kept)";
    }
    return os;
}
