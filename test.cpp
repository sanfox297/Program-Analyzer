#include <iostream>

int main() {
    int a = 5;
    int b = 10;
    int c = a + b;
    int d = a * b;
    int e = c - d;
    
    if (e > 0) {
        std::cout << "Result: " << e << std::endl;
    } else {
        std::cout << "Result is non-positive." << std::endl;
    }
    
    return 0;
}

