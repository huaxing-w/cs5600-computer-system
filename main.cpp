#include "bits/stdc++.h"

#include "mlfq.h"
using namespace std;

int main(){
    cout<<"***************MLFQ simulator***************"<<endl;
    cout<<"How many level of queues do you want to have in MLFQ?"<<endl;
    int numOfQueue;
    cin>>numOfQueue;
    mlfq m(numOfQueue);
    m.numOfQueue=numOfQueue;
    cout<<"Do you want to config each queue's time quantum (default is 10)? (Y/N)"<<endl;
    string configQuantum;
    cin>>configQuantum;
    if(configQuantum=="Y"||configQuantum=="y"){
        for(int i=0;i<numOfQueue;i++){
            cout<<"Please enter the time quantum for queue "<<i+1<<endl;
            cout<<"Note: queue 2 has higher priority than queue 1"<<endl;
            int quantum;
            cin>>quantum;
            m.jobQueue[i]->quantum=quantum;
           
        }
    }
    cout<<"Do you want to config boost time (default is 100)? (Y/N)"<<endl;
    string configBoost;
    cin>>configBoost;
    if(configBoost=="Y"||configBoost=="y"){
        cout<<"Please enter the boost time"<<endl;
        int boostTime;
        cin>>boostTime;
        m.boostTime=boostTime;
    }

    cout<<"How many jobs do you want to have in MLFQ?"<<endl;
    int numOfJobs;
    cin>>numOfJobs;
    m.totalNumOfJobs=numOfJobs;
    for(int i=0;i<numOfJobs;i++){
        cout<<"Please enter "<<i+1<<"th job's start time, run time and io frequency(enter 0 means no IO) (seperated by space)"<<endl;
        int startTime,runTime,ioFreq;
        cin>>startTime>>runTime>>ioFreq;
        //Job* j=new Job(i+1,startTime,runTime,ioFreq);
        auto j=make_shared<Job>(i+1,startTime,runTime,ioFreq);
        if(ioFreq>0){
            cout<<"Please enter the IO time"<<endl;
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