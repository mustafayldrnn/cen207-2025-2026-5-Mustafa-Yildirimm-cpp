#include "../header/BrowserHistory.h"
#include <iostream>

using namespace Coruh::Applications;

BrowserHistory::BrowserHistory() : current_(), currentUrl("") {}

void BrowserHistory::navigateTo(const std::string& url) {
    if (url.empty()) return;

    if (history_.empty()) {
        current_ = history_.push_back(url);
        currentUrl = url;
        return;
    }

    // If we are not at the last item, drop forward history
    auto tmp = current_;
    auto after = tmp; ++after;
    while (after != history_.end()) {
        after = history_.erase(after);
    }

    // Insert new page after current and move current
    current_ = history_.insert_after(current_, url);
    currentUrl = url;
}

std::string BrowserHistory::goBack() {
    if (!canGoBack()) return "";
    --current_;
    currentUrl = *current_;
    return currentUrl;
}

std::string BrowserHistory::goForward() {
    if (!canGoForward()) return "";
    ++current_;
    currentUrl = *current_;
    return currentUrl;
}

std::string BrowserHistory::getCurrentUrl() const {
    return currentUrl;
}

bool BrowserHistory::canGoBack() const {
    if (history_.empty()) return false;
    return !(current_ == history_.begin());
}

bool BrowserHistory::canGoForward() const {
    if (history_.empty()) return false;
    auto tmp = current_;
    ++tmp;
    return tmp != history_.end();
}

size_t BrowserHistory::getHistorySize() const {
    return history_.size();
}

void BrowserHistory::displayHistory() const {
    std::cout << "Browser History:" << std::endl;
    for (auto it = history_.begin(); it != history_.end(); ++it) {
        std::cout << *it << " ";
    }
    std::cout << std::endl;
    std::cout << "Current URL: " << currentUrl << std::endl;
}

void BrowserHistory::clearHistory() {
    history_.clear();
    current_ = ds::DoublyLinkedList<std::string>::iterator();
    currentUrl.clear();
}
