#include "bits/stdc++.h"
#include "Job.h"
using namespace std;

int main(){
    Job* j1=new Job(1, 0, 10);
    Job* j2=new Job(2, 0, 10, 5);
    cout<<j1->id<<" "<<j1->startTime<<" "<<j1->runTime<<" "<<j1->ioFreq<<endl;
    cout<<j2->id<<" "<<j2->startTime<<" "<<j2->runTime<<" "<<j2->ioFreq<<endl;
    return 0;
}