#include <MT/array.h>

#include <iostream>

int main(int, char**)
{
    // Watch out: Different short-hands.
    // ARR creates double vector with given elements
    // arr creates matrix with given n,m dimensions
    
    // scalar product
    MT::Array<double> a = ARR(1.0, 2.0);     
    MT::Array<double> b = ARR(3.0, 4.0);
    std::cout << (~a * b) << std::endl;
    
    // random 2x3 matrix
    MT::Array<double> c = arr(2, 3);
    rndInteger(c, -5, 5, false);
    std::cout << c << std::endl;
    
    return 0;
}

