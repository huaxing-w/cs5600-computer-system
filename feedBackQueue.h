#include "Job.h"
using namespace std;
class feedBackQueue{
public:
    deque<shared_ptr<Job>> q;
    int quantum=10;
    int allotment=1;
    feedBackQueue();
    feedBackQueue(int quantum, int allotment);

};

feedBackQueue::feedBackQueue(){

}

feedBackQueue::feedBackQueue(int quantum, int allotment){
    this->quantum=quantum;
    this->allotment=allotment;
}
