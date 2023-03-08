#pragma once

#include <thread>
#include <condition_variable>
#include <chrono>
using namespace std::chrono_literals;

class JobHandler
{
protected:
    const int MAX_JOBS = 4;

    typedef std::function<void()> Job;
    typedef  std::unique_lock<std::mutex> Lock;
    bool done = false;
    int numThreads = 0;
    std::mutex access;
    std::condition_variable sleeper;
    std::condition_variable didSomething;
    std::thread* threads=nullptr;
    std::vector<Job> jobs;
    int atJob=0;
    int addJob=0;

public:
    JobHandler(int nThreads=0)
    {
        if (nThreads>0) createThreads(nThreads);
    }

    void createThreads(int nThreads)
    {
        assert(numThreads == 0);  // do not call this fn multiple times
        numThreads = nThreads;
        threads  = new std::thread[numThreads];
        for (int i=0;i<numThreads;i++)
        {
            threads[i] = std::thread([this] { this->run(); });
        }
        jobs.resize(MAX_JOBS); // If the # of jobs is exceeded, enqueueing will block
    }

    // Returns true if ok, false if quitting
    bool wait()
    {
        runOne(false);  // Reusing the thread like this causes deep recursion.
        return !done;
    }

    void append(const Job& job)
    {
        Lock lock(access);
        while (addJob == atJob-1) // we've wrapped around and are approaching the tail.
        {
            sleeper.wait_for(lock,25000ms);
        }
        jobs[addJob] = job;
        addJob++;
        if (addJob == MAX_JOBS) addJob = 0;
        sleeper.notify_one();
    }

    void run()
    {
        while(!done)
        {
            runOne();
        }
        didSomething.notify_all(); // Wake up any stragglers
    }

    void runOne(bool sleepOk=true)
    {
        std::function<void()> next;
        {
            Lock lock(access);
            if (atJob == addJob)
            {
                didSomething.notify_all(); // wake up everybody because nothing to do
                if (sleepOk) sleeper.wait_for(lock,25000ms);
                else return;
            }
            else
            {
                next = jobs[atJob];
                jobs[atJob] = Job();  // clear it
                if (next) // If it is valid, go to the next one
                {
                    atJob++;
                    if (atJob == MAX_JOBS) atJob = 0;
                }
            }
        }
        if (next)
        {
            next();
            didSomething.notify_all();
        }
    }


    ~JobHandler()
    {
        done=true;
        for (int i=0;i<numThreads;i++)
        {
            threads[i].join();
        }
        delete[] threads;
    }
};
