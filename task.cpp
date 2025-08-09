#include "image.h"
#include <iostream>
#include <limits>

void clearInput() {
    std::cin.clear();
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

void printMenu() {
    std::cout << "1. Create image\n";
    std::cout << "2. Display image\n";
    std::cout << "3. Horizontally merge images\n";
    std::cout << "4. Vertically merge images\n";
    std::cout << "5. Add images\n";
    std::cout << "6. Multiply the image by a scalar\n";
    std::cout << "7. Crop the image\n";
    std::cout << "8. Subtract one image from another\n";
    std::cout << "9. Divide one image by another\n";
    std::cout << "10. Subtract a scalar from the image\n";
    std::cout << "11. Divide the image by a scalar\n";
    std::cout << "0. Exit\n";
    std::cout << "Enter: ";
}

int main() {
    Image<int>* img1 = nullptr;
    Image<int>* img2 = nullptr;
    int choice;

    do {
        printMenu();
        std::cin >> choice;

        if (std::cin.fail()) {
            clearInput();
            std::cout << "Invalid input. Try again.\n";
            continue;
        }

        switch (choice) {
        case 1:
            if (!img1) {
                img1 = new Image<int>();
                std::cout << "Creating the first image:\n";
                img1->input();
            } else if (!img2) {
                img2 = new Image<int>();
                std::cout << "Creating the second image:\n";
                img2->input();
            } else {
                std::cout << "Both images already created.\n";
            }
            break;

        case 2:
            if (img1) {
                std::cout << "Image 1:\n"; img1->print();
            } else std::cout << "Image 1 not created.\n";
            if (img2) {
                std::cout << "Image 2:\n"; img2->print();
            } else std::cout << "Image 2 not created.\n";
            break;

        case 3:
            if (img1 && img2) {
                try {
                    auto result = img1->concatHorizontal(*img2);
                    std::cout << "Horizontal merge result:\n"; result.print();
                } catch (const std::exception& e) {
                    std::cout << e.what() << "\n";
                }
            } else std::cout << "Create both images first.\n";
            break;

        case 4:
            if (img1 && img2) {
                try {
                    auto result = img1->concatVertical(*img2);
                    std::cout << "Vertical merge result:\n"; result.print();
                } catch (const std::exception& e) {
                    std::cout << e.what() << "\n";
                }
            } else std::cout << "Create both images first.\n";
            break;

        case 5:
            if (img1 && img2) {
                try {
                    auto result = *img1 + *img2;
                    std::cout << "Addition result:\n"; result.print();
                } catch (const std::exception& e) {
                    std::cout << e.what() << "\n";
                }
            } else std::cout << "Create both images first.\n";
            break;

        case 6:
            if (!img1) { std::cout << "Image not created.\n"; break; }
            double scalar;
            std::cout << "Enter scalar: "; std::cin >> scalar;
            try {
                auto result = *img1 * scalar;
                std::cout << "Result:\n"; result.print();
            } catch (...) {
                std::cout << "Error multiplying.\n";
            }
            break;

        case 7:
            if (!img1) { std::cout << "Image not created.\n"; break; }
            int r1, r2, c1, c2;
            std::cout << "Enter r1 r2 c1 c2: "; std::cin >> r1 >> r2 >> c1 >> c2;
            try {
                auto result = img1->subimageDynamic(r1, r2, c1, c2);
                std::cout << "Cropped:\n"; result.print();
            } catch (...) {
                std::cout << "Error cropping.\n";
            }
            break;

        case 8:
            if (img1 && img2) {
                try {
                    auto result = *img1 - *img2;
                    std::cout << "Subtraction result:\n"; result.print();
                } catch (...) {
                    std::cout << "Error subtracting.\n";
                }
            } else std::cout << "Create both images first.\n";
            break;

        case 9:
            if (img1 && img2) {
                try {
                    auto result = *img1 / *img2;
                    std::cout << "Division result:\n"; result.print();
                } catch (...) {
                    std::cout << "Error dividing.\n";
                }
            } else std::cout << "Create both images first.\n";
            break;

        case 10:
            if (!img1) { std::cout << "Image not created.\n"; break; }
            int s;
            std::cout << "Scalar to subtract: "; std::cin >> s;
            try {
                auto result = *img1 - s;
                std::cout << "Result:\n"; result.print();
            } catch (...) {
                std::cout << "Error subtracting scalar.\n";
            }
            break;

        case 11:
            if (!img1) { std::cout << "Image not created.\n"; break; }
            double div;
            std::cout << "Scalar to divide: "; std::cin >> div;
            if (div == 0.0) {
                std::cout << "Cannot divide by zero.\n";
                break;
            }
            try {
                auto result = *img1 / div;
                std::cout << "Result:\n"; result.print();
            } catch (...) {
                std::cout << "Error dividing scalar.\n";
            }
            break;

        case 0:
            std::cout << "Exiting.\n";
            delete img1;
            delete img2;
            break;

        default:
            std::cout << "Unknown option.\n";
        }

    } while (choice != 0);

    return 0;
}