#include "feedBackQueue.h"
#include "bits/stdc++.h"
using namespace std;

struct CompareJob{
    bool operator()(Job* a,Job* b){
        return a->startTime>b->startTime;
    }
};


class mlfq{
public:
    //key is priority, value is queue
    map<int,feedBackQueue*> jobQueue;

    vector<Job*> finishedJobs;

    priority_queue<Job*,vector<Job*>,CompareJob>waitingJobs;

    int totalNumOfJobs=0;
    int totalNumOfFinishedJobs=0;
    int curTime=0;
    int numOfQueue=3;
    int boostTime=100;

    int lastRunJob=-1;

    //assign the number of queue
    mlfq(int numOfQueue);

    
    int findQueue();
    void boost();
    void addJob(Job* j);
    void run();
    void printFinialResult();
};

mlfq::mlfq(int numOfQueue){
    
    this->numOfQueue=numOfQueue;
    for(int i=0;i<numOfQueue;i++){
        feedBackQueue* f1=new feedBackQueue();
        jobQueue[i]=f1;
    }
}

int mlfq::findQueue(){
    for(int i=numOfQueue-1;i>=0;i--){
        if(jobQueue[i]->q.size()>0){
            return i;
        }
    }
    return -1;
}

void mlfq::boost(){
    for(int i=0;i<numOfQueue-1;i++){
        if(jobQueue[i]->q.size()>0){
            while(!jobQueue[i]->q.empty()){
                Job* j=jobQueue[i]->q.front();
                j->curQueue=numOfQueue-1;
                j->ticksLeft=jobQueue[numOfQueue-1]->quantum;
                j->allotLeft=jobQueue[numOfQueue-1]->allotment;
                jobQueue[i]->q.pop_front();
                jobQueue[numOfQueue-1]->q.push_back(j);
            }
        }
    }
    cout<<"Boosting at time "<<curTime<<endl;
}

void mlfq::addJob(Job* j){

    if(j->curQueue==-1){
        j->curQueue=numOfQueue-1;
        jobQueue[numOfQueue-1]->q.push_front(j);
    }
    else{
        if(j->doingIO){
            cout<<"Job "<<j->id<<" IO finishes at time "<<"["<<curTime<<"]"<<endl;
            j->doingIO=false;
            jobQueue[j->curQueue]->q.push_front(j);
            j->ticksLeft=jobQueue[j->curQueue]->quantum;
            j->allotLeft=jobQueue[j->curQueue]->allotment;

        }
        else{

            jobQueue[j->curQueue]->q.push_back(j);

        }
    }
    
}

void mlfq::run(){
    while(totalNumOfFinishedJobs<totalNumOfJobs){
        //check if there is any job waiting to be added to the queue
        while(!waitingJobs.empty() && waitingJobs.top()->startTime<=curTime){
            Job* j=waitingJobs.top();
            waitingJobs.pop();
            addJob(j);
        }
        
        //find the queue with the highest priority
        int queueIndex=findQueue();
        if(queueIndex==-1){
            curTime++;
            continue;
        }
        //get the job from the queue
        Job* j=jobQueue[queueIndex]->q.front();
        jobQueue[queueIndex]->q.pop_front();
        

        if(lastRunJob==-1 || j->id!=lastRunJob){
            lastRunJob=j->id;
            j->ticksLeft=jobQueue[j->curQueue]->quantum;
            j->allotLeft=jobQueue[j->curQueue]->allotment;
        }
        //check if this is the first time running the job
        if(j->firstRunTime==-1){
            j->firstRunTime=curTime;
            cout<<"Job "<<j->id<<" starts to run at time "<<"["<<curTime<<"]"<<endl;
        }

        j->workedTime+=jobQueue[j->curQueue]->allotment;
        j->ticksLeft-=j->allotLeft;
        cout<<"["<<curTime<<"] "<<"Run Job "<<j->id<<" at priority "<<j->curQueue<<" [Ticks "<<j->ticksLeft<<" Allot "<<j->allotLeft<<" worked "<<j->workedTime<<" of "<<j->runTime<<" ]"<<endl;

        //check if the job is finished
        if(j->workedTime>=j->runTime){
            cout<<"Job "<<j->id<<" finished at time "<<"["<<curTime+1<<"]"<<endl;
            finishedJobs.push_back(j);
            totalNumOfFinishedJobs++;
            j->endTime=curTime;
            curTime++;
            continue;

            
        }
        
        //check if the job is using up its allotment
        if(j->ticksLeft<=0){
            int nxtQueue=max(0,j->curQueue-1);
            j->curQueue=nxtQueue;
            jobQueue[j->curQueue]->q.push_back(j);
            j->ticksLeft=jobQueue[j->curQueue]->quantum;
            j->allotLeft=jobQueue[j->curQueue]->allotment;
            cout<<"Job "<<j->id<<" is moved to priority "<<j->curQueue<<" at time "<<"["<<curTime+1<<"]"<<endl;

            
        }
        else{
            jobQueue[j->curQueue]->q.push_front(j);
            
        }

        //check if the job is doing IO
        if(j->ioFreq!=0 && j->workedTime % j->ioFreq==0){
            j->doingIO=true;
            cout<<"Job "<<j->id<<" starts to do IO at time "<<"["<<curTime+1<<"]"<<endl;
            j->startTime=curTime+j->IOTime;
            waitingJobs.push(j);
            curTime++;
            continue;

        }
        
        

        //check if boost
        if(curTime!=0 && curTime%boostTime==0){
            boost();
        }
        curTime++;

    }
}


void mlfq::printFinialResult(){
    cout<<"Finial Result:"<<endl;
    for(int i=0;i<finishedJobs.size();i++){
        Job* j=finishedJobs[i];
        cout<<"Job "<<j->id<<" starts at "<<"["<<j->initTime<<"] "<<"response time at "<<"["<<j->firstRunTime<<"] "<<"turnaround time is "<<j->endTime-j->initTime<<endl;
    }
}  