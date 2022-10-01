class Job{
public:
    int id;
    int initTime;
    int startTime;
    int runTime;
    int ioFreq=0;
    int IOTime=0;
    int curQueue=-1;
    int ticksLeft;
    int allotLeft;
    int workedTime=0;
    bool doingIO=false;
    int endTime;
    int firstRunTime=-1;
    Job(int id, int startTime, int runTime);
    Job(int id, int startTime, int runTime, int ioFreq);
};

Job::Job(int id, int startTime, int runTime){
    this->id=id;
    this->startTime=startTime;
    this->initTime=startTime;
    this->runTime=runTime;
}

Job::Job(int id, int startTime, int runTime, int ioFreq){
    this->id=id;
    this->startTime=startTime;
    this->initTime=startTime;
    this->runTime=runTime;
    this->ioFreq=ioFreq;
}