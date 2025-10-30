#include <gtest/gtest.h>
#include "BrowserHistory/header/BrowserHistory.h"
#include <sstream>

using Coruh::Applications::BrowserHistory;

TEST(BrowserHistory, EmptyAndSinglePage) {
    BrowserHistory bh;
    EXPECT_EQ(bh.getHistorySize(), 0u);
    EXPECT_FALSE(bh.canGoBack());
    EXPECT_FALSE(bh.canGoForward());
    EXPECT_EQ(bh.getCurrentUrl(), "");

    bh.navigateTo("a.com");
    EXPECT_EQ(bh.getHistorySize(), 1u);
    EXPECT_EQ(bh.getCurrentUrl(), "a.com");
    EXPECT_FALSE(bh.canGoBack());
    EXPECT_FALSE(bh.canGoForward());
    EXPECT_EQ(bh.goBack(), "");
    EXPECT_EQ(bh.goForward(), "");
}

TEST(BrowserHistory, BackAndForward) {
    BrowserHistory bh;
    bh.navigateTo("a.com");
    bh.navigateTo("b.com");
    bh.navigateTo("c.com");

    EXPECT_TRUE(bh.canGoBack());
    EXPECT_FALSE(bh.canGoForward());

    EXPECT_EQ(bh.goBack(), "b.com");
    EXPECT_EQ(bh.getCurrentUrl(), "b.com");
    EXPECT_TRUE(bh.canGoForward());
    EXPECT_EQ(bh.goForward(), "c.com");
}

TEST(BrowserHistory, NavigateAfterBackPrunesForward) {
    BrowserHistory bh;
    bh.navigateTo("a.com");
    bh.navigateTo("b.com");
    bh.navigateTo("c.com");

    // Go back to b.com then navigate to d.com -> forward (c.com) should be dropped
    EXPECT_EQ(bh.goBack(), "b.com");
    bh.navigateTo("d.com");

    EXPECT_EQ(bh.getCurrentUrl(), "d.com");
    EXPECT_TRUE(bh.canGoBack());
    EXPECT_FALSE(bh.canGoForward());

    EXPECT_EQ(bh.goBack(), "b.com");
    // forward should now be d.com only
    EXPECT_TRUE(bh.canGoForward());
    EXPECT_EQ(bh.goForward(), "d.com");
}

TEST(BrowserHistory, ClearAndDisplay) {
    BrowserHistory bh;
    bh.navigateTo("start.com");
    bh.navigateTo("next.com");
    EXPECT_EQ(bh.getHistorySize(), 2u);

    // Capture display output
    std::ostringstream oss; auto* old = std::cout.rdbuf(oss.rdbuf());
    bh.displayHistory();
    std::cout.rdbuf(old);
    auto out = oss.str();
    EXPECT_FALSE(out.empty());

    // Clear and verify
    bh.clearHistory();
    EXPECT_EQ(bh.getHistorySize(), 0u);
    EXPECT_EQ(bh.getCurrentUrl(), "");
    EXPECT_FALSE(bh.canGoBack());
    EXPECT_FALSE(bh.canGoForward());
}

TEST(BrowserHistory, EmptyNavigateIgnored) {
    BrowserHistory bh;
    bh.navigateTo("");
    EXPECT_EQ(bh.getHistorySize(), 0u);
    EXPECT_EQ(bh.getCurrentUrl(), "");
    EXPECT_EQ(bh.goBack(), "");
    EXPECT_EQ(bh.goForward(), "");
}

TEST(BrowserHistory, LargeNavigationBackAndForth) {
    BrowserHistory bh;
    for (int i = 0; i < 100; ++i) {
        bh.navigateTo("p" + std::to_string(i));
    }
    EXPECT_EQ(bh.getHistorySize(), 100u);
    // Go back to the first
    while (bh.canGoBack()) bh.goBack();
    EXPECT_FALSE(bh.canGoBack());
    // Go forward to the last
    while (bh.canGoForward()) bh.goForward();
    EXPECT_FALSE(bh.canGoForward());
    EXPECT_EQ(bh.getHistorySize(), 100u);
}
