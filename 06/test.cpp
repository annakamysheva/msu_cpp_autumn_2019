#include "format.h"
#include <iostream>

#define checkEqual(x, y) \
    do { \
        if ((x) != (y)) \
        { \
            cout << "at line " << __LINE__ << ": " << (x) << " != " << (y) << '\n'; \
        } \
    } while(0);

#define checkThrow(x) \
    do { \
        try { (x); } \
        catch (const runtime_error&) { break; } \
        catch (...) {} \
        cout << "expected runtime_error at line " << __LINE__ << '\n'; \
    } while(0);

using namespace std;
    
int main(){

    checkEqual(format("{1}+{1} = {0}", 2, "one"), "one+one = 2");

    // checkEqual(format("{1}", 1, 2), "2");

    // checkEqual(format("{0}{0}", "a"), "aa");

    // checkEqual(format("{0}{11}", "a",0,0,0,0,0,0,0,0,0,0,1), "a1");
    
    // checkThrow(format("{", 1));
    // checkThrow(format("{0", 1));
    // checkThrow(format("}", 1));
    // checkThrow(format("{1}", 1));
    // checkThrow(format("{0}{1}{3}", 1, 2));
    // checkThrow(format("{10}", 1));
    
    cout << "All test successfully past";
    
    return 0;
    }