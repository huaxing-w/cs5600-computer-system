class Job{
public:
    int id;
    int startTime;
    int runTime;
    int ioFreq=-1;
    
    int currentQueue;
    int ticksLeft;
    int allotLeft;
    int timeLeft;
    bool doingIO=false;
    int endTime;
    int firstRunTime=-1;
    
    Job(int id, int startTime, int runTime);
    Job(int id, int startTime, int runTime, int ioFreq);
};

Job::Job(int id, int startTime, int runTime){
    this->id=id;
    this->startTime=startTime;
    this->runTime=runTime;
}

Job::Job(int id, int startTime, int runTime, int ioFreq){
    this->id=id;
    this->startTime=startTime;
    this->runTime=runTime;
    this->ioFreq=ioFreq;
}