#include "bits/stdc++.h"

using namespace std;
using namespace std::chrono;
int main(){
    vector<int> values(10000);
 
    // Generate Random values
    auto f = []() -> int { return rand() % 10000; };
 
    // Fill up the vector
    generate(values.begin(), values.end(), f);
 
    // Get starting timepoint
    auto start = high_resolution_clock::now();
 
    // Call the function, here sort()
    sort(values.begin(), values.end());
 
    // Get ending timepoint
    auto stop = high_resolution_clock::now();
 
    // Get duration. Substart timepoints to
    // get duration. To cast it to proper unit
    // use duration cast method
    auto duration = duration_cast<microseconds>(stop - start);
 
    cout << "Time taken by function: "
         << duration.count() << " microseconds" << endl;

    return 0;
}