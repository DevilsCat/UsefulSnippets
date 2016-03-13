//ActiveObject.h : this is an active object class that holds a local thread and a queue of requests.
//It is virtual class that has a Service() function to be overwirtten.
//Service() runs in local thread, it processes the requests of that active object.
//
//Example:
//  class OptActiveObject : public ActiveObject{ ... }
//
//  OptActiveObject optAO(data);
//  optAO.Activate();
//  optAO.Enqueue(request);
//  optAO.Deactivate();


#ifndef ACTIVE_OBJECT_H
#define ACTIVE_OBJECT_H

#include "TheadSafeQueue.h"
#include <thread>
#include <future>

using namespace std;

template<typename T>
class ActiveObject{
public:

    ActiveObject() : activeFlag(false){}

    void Enqueue(T &request){
        requestQueue.push(request);
    }

    void Activate(){
        if (!activeFlag){
            activeFlag = true;
            workerThread_ = thread(&ActiveObject::RunService, this);
        }
    }

    void Deactivate(){
        if (activeFlag){
            activeFlag = false;
            workerThread_.join();
        }
    }

    bool RequestQueueEmpty() {
        return requestQueue.empty();
    }

protected:
    virtual void Service(T& request) = 0;

private:
    void RunService(){
        while (activeFlag){
            //this_thread::sleep_for(chrono::milliseconds(2000));
            shared_ptr<T> request = requestQueue.TryPop();
            if (!request){
                this_thread::yield();
                continue;
            }
            else{
                Service(*request);
            }
        }
    }


    thread workerThread_;
    ThreadSafeQueue<T> requestQueue;
    bool activeFlag;
};

#endif
