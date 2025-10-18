#include "../header/TaskScheduler.h"
#include <iostream>

using namespace Coruh::Applications;

TaskScheduler::TaskScheduler() {}

void TaskScheduler::addTask(const Task& task) {
    taskQueue.enqueue(task);
    std::cout << "Task added: " << task.id << " - " << task.description << std::endl;
}

Task TaskScheduler::executeNextTask() {
    if (taskQueue.isEmpty()) {
        throw std::runtime_error("No tasks to execute");
    }
    
    Task task = taskQueue.dequeue();
    completedTasks.push(task);
    undoStack.push(task);
    
    std::cout << "Executed task: " << task.id << " - " << task.description << std::endl;
    return task;
}

Task TaskScheduler::undoLastOperation() {
    if (!canUndo()) {
        throw std::runtime_error("Nothing to undo");
    }
    
    Task undoneTask = undoStack.pop();
    taskQueue.enqueue(undoneTask);
    
    // Remove from completed tasks
    if (!completedTasks.isEmpty()) {
        completedTasks.pop();
    }
    
    std::cout << "Undone task: " << undoneTask.id << " - " << undoneTask.description << std::endl;
    return undoneTask;
}

bool TaskScheduler::canUndo() const {
    return !undoStack.isEmpty();
}

Task TaskScheduler::peekNextTask() const {
    if (taskQueue.isEmpty()) {
        throw std::runtime_error("No tasks in queue");
    }
    return taskQueue.front();
}

size_t TaskScheduler::getQueueSize() const {
    return taskQueue.size();
}

size_t TaskScheduler::getUndoStackSize() const {
    return undoStack.size();
}

void TaskScheduler::displayPendingTasks() const {
    std::cout << "Pending Tasks (" << getQueueSize() << "):" << std::endl;
    if (taskQueue.isEmpty()) {
        std::cout << "No pending tasks" << std::endl;
    } else {
        std::cout << "Next: " << taskQueue.front().id << " - " << taskQueue.front().description << std::endl;
    }
}

void TaskScheduler::displayCompletedTasks() const {
    std::cout << "Completed Tasks (" << completedTasks.size() << "):" << std::endl;
    if (completedTasks.isEmpty()) {
        std::cout << "No completed tasks" << std::endl;
    } else {
        std::cout << "Last completed: " << completedTasks.top().id << " - " << completedTasks.top().description << std::endl;
    }
}

void TaskScheduler::clearAll() {
    undoStack.clear();
    taskQueue.clear();
    completedTasks.clear();
    std::cout << "All tasks cleared" << std::endl;
}
