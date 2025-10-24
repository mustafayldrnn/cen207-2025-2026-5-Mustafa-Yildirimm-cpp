/**
 * @file BrowserHistory.h
 * @brief Browser History System using Double Linked List
 */

#ifndef BROWSER_HISTORY_H
#define BROWSER_HISTORY_H

#include <string>
// Fix relative include path to shared data structure
#include "../../DoubleLinkedList/header/DoubleLinkedList.h"

namespace Coruh
{
    namespace Applications
    {
        /**
         * @class BrowserHistory
         * @brief Browser history system with backward/forward navigation
         */
        class BrowserHistory
        {
        private:
            DataStructures::DoubleLinkedList<std::string> history;
            std::string currentUrl;
            
        public:
            /**
             * Constructor
             */
            BrowserHistory();
            
            /**
             * Navigate to a new URL
             * @param url URL to navigate to
             */
            void navigateTo(const std::string& url);
            
            /**
             * Go back to previous page
             * @return URL of previous page, empty if can't go back
             */
            std::string goBack();
            
            /**
             * Go forward to next page
             * @return URL of next page, empty if can't go forward
             */
            std::string goForward();
            
            /**
             * Get current URL
             * @return Current URL
             */
            std::string getCurrentUrl() const;
            
            /**
             * Check if can go back
             * @return true if can go back
             */
            bool canGoBack() const;
            
            /**
             * Check if can go forward
             * @return true if can go forward
             */
            bool canGoForward() const;
            
            /**
             * Get history size
             * @return Number of pages in history
             */
            size_t getHistorySize() const;
            
            /**
             * Display current history
             */
            void displayHistory() const;
            
            /**
             * Clear history
             */
            void clearHistory();
        };
    }
}

#endif // BROWSER_HISTORY_H
