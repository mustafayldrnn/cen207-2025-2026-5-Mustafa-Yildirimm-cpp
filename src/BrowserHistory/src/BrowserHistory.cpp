#include "../header/BrowserHistory.h"
#include <iostream>

using namespace Coruh::Applications;

BrowserHistory::BrowserHistory() : currentUrl("") {}

void BrowserHistory::navigateTo(const std::string& url) {
    if (!url.empty()) {
        history.append(url);
        currentUrl = url;
    }
}

std::string BrowserHistory::goBack() {
    if (history.canMoveBackward()) {
        history.moveBackward();
        currentUrl = history.getCurrent();
        return currentUrl;
    }
    return "";
}

std::string BrowserHistory::goForward() {
    if (history.canMoveForward()) {
        history.moveForward();
        currentUrl = history.getCurrent();
        return currentUrl;
    }
    return "";
}

std::string BrowserHistory::getCurrentUrl() const {
    return currentUrl;
}

bool BrowserHistory::canGoBack() const {
    return history.canMoveBackward();
}

bool BrowserHistory::canGoForward() const {
    return history.canMoveForward();
}

size_t BrowserHistory::getHistorySize() const {
    return history.getSize();
}

void BrowserHistory::displayHistory() const {
    std::cout << "Browser History:" << std::endl;
    history.display();
    std::cout << "Current URL: " << currentUrl << std::endl;
}

void BrowserHistory::clearHistory() {
    history.clear();
    currentUrl = "";
}
