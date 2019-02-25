#include "random.h"
#include <iostream>

using namespace std;
using namespace coen79_lab2;

// Main Functions

void printNumbers(rand_gen &r, int num) {
    
    for (int i = 0; i < num; i++) {
        r.print_info();
        cout << "Next: " << r.next() << endl;
    }
    cout << endl;
}

int main(int argc, const char * argv[])
{
    rand_gen rg(1, 40, 725, 729);
    
    printNumbers(rg, 5);
    
    rg.set_seed(1);
    printNumbers(rg, 5);
    
    rg.set_seed(15);
    printNumbers(rg, 5);
    
    
    rand_gen rg2(14, 85, 637, 1947);
    
    printNumbers(rg2, 5);
    
    rg2.set_seed(14);
    printNumbers(rg2, 5);
    
    
    return 0;
}
