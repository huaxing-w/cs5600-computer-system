#include "bits/stdc++.h"

#include "mlfq.h"
using namespace std;

int main(){
    cout<<"***************MLFQ simulator***************\n"<<endl;
    cout<<"How many level of queues do you want to have in MLFQ? (default is 3)\n"<<endl;
    int numOfQueue;
    cin>>numOfQueue;
    mlfq m(numOfQueue);
    m.numOfQueue=numOfQueue;
    cout<<"How many jobs do you want to have in MLFQ?\n"<<endl;
    int numOfJobs;
    cin>>numOfJobs;
    m.totalNumOfJobs=numOfJobs;
    for(int i=0;i<numOfJobs;i++){
        cout<<"Please enter "<<i+1<<"th job's start time, run time and io frequency(enter 0 means no IO) (seperated by space)\n"<<endl;
        int startTime,runTime,ioFreq;
        cin>>startTime>>runTime>>ioFreq;
        Job* j=new Job(i+1,startTime,runTime,ioFreq);
        if(ioFreq>0){
            cout<<"Please enter the IO time\n"<<endl;
            int IOTime;
            cin>>IOTime;
            j->IOTime=IOTime;
        }
        m.waitingJobs.push(j);
    }
    m.run();
    m.printFinialResult();
    return 0;
}