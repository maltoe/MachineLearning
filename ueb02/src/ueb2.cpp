#include <MT/array.h>

#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

inline std::vector<double> parseLine(std::string& line)
{
    std::vector<double> v;  
    line.erase(0, line.find_first_not_of(" \t"));
    line.erase(line.find_last_not_of(" \t") + 1);
    std::istringstream iss(line);
    double val;
    while(!iss.eof()) {
        iss >> val;
        v.push_back(val);
    }
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

arr prependOne(arr& x)
{
    arr c(x); // copy x to c!
    c.insColumns(0, 1);
    for(unsigned int i = 0; i < c.getDim()(0); i++)
        c(i,0) = 1.0;
    return c;    
}

arr linearFeatures(arr& x)
{
    return prependOne(x);
}

arr quadraticFeatures(arr& x)
{
    arr c(x); // copy x to c!
    int col = x.getDim()(1);
    for(unsigned int i = 0; i < x.getDim()(1); i++) {
        for(unsigned int j = i; j < x.getDim()(1); j++) {
            c.insColumns(col, 1);
            for(unsigned int row = 0; row < x.getDim()(0); row++) {
                c(row, col) = x(row, i) * x(row, j);
            }
            col++;
        }
    }

    return prependOne(c);
}

arr solveForBeta(arr& x, arr& y, arr(*featureFunc)(arr& x))
{
    arr phix = featureFunc(x);
    arr invXtX;
    inverse(invXtX, ~phix * phix);
    arr beta = invXtX * ~phix * y;
    
    return beta;
}

arr matrixZ()
{
    const int n = 10;
    arr z(n * n, 2);
    for(int i = 0; i < n; i++) {
        for(int j = 0; j < n; j++) {
            z(i * n + j, 0) = i - n/2;
            z(i * n + j, 1) = j - n/2;
        }
    }
    return z;
}

int main(int, char**)
{   
    // read dataLinReg1D.txt
    MT::Array<double> x;
    MT::Array<double> y;
    readFromFile("dataLinReg2D.txt", x, y);
    MT::Array<double> beta;
    beta = solveForBeta(x, y, linearFeatures);
    arr Z = matrixZ();
    arr phiZ = prependOne(Z);
    arr ret = phiZ * beta;
//     gnuplot(ret);
    std::cout << ret << std::endl;
    
    return 0;
}

