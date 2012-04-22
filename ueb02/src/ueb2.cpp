#include <MT/array.h>

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

inline double str2dbl(std::string& str)
{
    std::istringstream iss(str);
    double v;
    iss >> v;
    return v;
}

inline std::vector<double> parseLine(std::string const& line)
{
    std::vector<double> v;
    std::string current_token;
    for(unsigned int i = 0; i < line.length(); i++) {
        if(line[i] == ' ') {
            if(current_token.length() > 0) {
                v.push_back(str2dbl(current_token));
            }
            current_token.erase();
        } else {
            current_token += line[i];
        }
    }
    
    if(current_token.length() > 0)
        v.push_back(str2dbl(current_token));
    
    return v;
}

// user provides x+y arrays, no error handling.
void readFromFile(const char* fn, MT::Array<double>& x, MT::Array<double>& y)
{
    std::ifstream fin(fn);        
    bool firstLine = true;
    int count = 0;
    while(!fin.eof()) {        
        std::string line;
        std::getline(fin, line);
        std::vector<double> v = parseLine(line);
        
        // Not sure if we need any of this.
        if(firstLine) {
            x.resize(0, v.size() - 1);
            y.resize(0, 1);
            firstLine = false;    
        }

        x.insRows(count, 1);
        for(unsigned int i = 0; i < v.size() - 1; i++)
            x(count, i) = v[i];
        
        y.insRows(count, 1);
        y(count, 0) = v.back();  
        
        count++; 
    }
}

int main(int, char**)
{
    /*
    // Watch out: Different short-hands.
    // ARR creates double vector with given elements
    // arr creates matrix with given n,m dimensions
    
    // scalar product
    MT::Array<double> a = ARR(1.0, 2.0);     
    MT::Array<double> b = ARR(3.0, 4.0);

    // random 2x3 matrix
    MT::Array<double> c = arr(2, 3);
    rndInteger(c, -5, 5, false);
    std::cout << c << std::endl;
    */
    
    // read dataLinReg1D.txt
    MT::Array<double> x;
    MT::Array<double> y;
    readFromFile("dataLinReg1D.txt", x, y);
    std::cout << x << std::endl;
    std::cout << y << std::endl;
    
    return 0;
}

