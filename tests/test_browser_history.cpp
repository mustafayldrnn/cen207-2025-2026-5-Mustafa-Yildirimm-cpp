#include <gtest/gtest.h>
#include "BrowserHistory/header/BrowserHistory.h"

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
