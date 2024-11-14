#ifndef QUEUE_H
#define QUEUE_H

#include <queue>
#include <string>

class TaskQueue {
private:
    std::queue<std::string> taskQueue;
public:
    void addTask(const std::string& task);
    std::string getNextTask();
    bool isEmpty() const;
};

#endif
