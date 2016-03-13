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

template<typename T, typename V>
class ActiveObject{
public:
    struct RequestWrapper{
        shared_ptr<promise<V>> p;
        T value;
        RequestWrapper(T &value_) :value(value_), p(make_shared<promise<V>>()){}
    };



    ActiveObject() : activeFlag(false){}

    future<V> Enqueue(T& request){
        RequestWrapper requestWrapper(request);
        future<V> res = requestWrapper.p->get_future();
        requestQueue.push(requestWrapper);
        return res;
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
    virtual V Service(T& request) = 0;

private:
    void RunService(){
        while (activeFlag){
            shared_ptr<RequestWrapper> requestWrapper = requestQueue.TryPop();
            if (!requestWrapper){
                this_thread::yield();
                continue;
            }
            else{
                V res = Service(requestWrapper->value);
                requestWrapper->p->set_value(res);
            }
        }
    }


    thread workerThread_;
    ThreadSafeQueue<RequestWrapper> requestQueue;
    bool activeFlag;
};

#endif
