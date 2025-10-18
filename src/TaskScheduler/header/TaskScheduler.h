/**
 * @file TaskScheduler.h
 * @brief Task Scheduler using Stack and Queue
 */

#ifndef TASK_SCHEDULER_H
#define TASK_SCHEDULER_H

#include <string>
#include "../StackQueue/header/StackQueue.h"

namespace Coruh
{
    namespace Applications
    {
        /**
         * @struct Task
         * @brief Task structure for scheduler
         */
        struct Task
        {
            std::string id;
            std::string description;
            int priority;
            
            Task(const std::string& id, const std::string& desc, int priority)
                : id(id), description(desc), priority(priority) {}
        };
        
        /**
         * @class TaskScheduler
         * @brief Task scheduler with undo operations and task queue
         */
        class TaskScheduler
        {
        private:
            DataStructures::Stack<Task> undoStack;
            DataStructures::Queue<Task> taskQueue;
            DataStructures::Stack<Task> completedTasks;
            
        public:
            /**
             * Constructor
             */
            TaskScheduler();
            
            /**
             * Add new task to queue
             * @param task Task to add
             */
            void addTask(const Task& task);
            
            /**
             * Execute next task from queue
             * @return Executed task
             */
            Task executeNextTask();
            
            /**
             * Undo last operation
             * @return Undone task
             */
            Task undoLastOperation();
            
            /**
             * Check if can undo
             * @return true if can undo
             */
            bool canUndo() const;
            
            /**
             * Get next task without executing
             * @return Next task
             */
            Task peekNextTask() const;
            
            /**
             * Get queue size
             * @return Number of pending tasks
             */
            size_t getQueueSize() const;
            
            /**
             * Get undo stack size
             * @return Number of undoable operations
             */
            size_t getUndoStackSize() const;
            
            /**
             * Display all pending tasks
             */
            void displayPendingTasks() const;
            
            /**
             * Display completed tasks
             */
            void displayCompletedTasks() const;
            
            /**
             * Clear all tasks
             */
            void clearAll();
        };
    }
}

#endif // TASK_SCHEDULER_H
