#include "queue.h"

void TaskQueue::addTask(const std::string& task) {
    taskQueue.push(task);
}

std::string TaskQueue::getNextTask() {
    if (taskQueue.empty()) return "";
    std::string task = taskQueue.front();
    taskQueue.pop();
    return task;
}

bool TaskQueue::isEmpty() const {
    return taskQueue.empty();
}
