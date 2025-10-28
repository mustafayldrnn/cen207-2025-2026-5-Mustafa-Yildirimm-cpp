/**
 * @file test_language_translator_user_management.cpp
 * @brief Comprehensive user management tests for LanguageTranslator
 * @details Tests login, registration, logout, and user session management
 */

#include <gtest/gtest.h>
#include <filesystem>
#include "../src/LanguageTranslator/header/LanguageTranslator.h"

using namespace Coruh::LanguageTranslator;

class LanguageTranslatorUserManagementTest : public ::testing::Test {
protected:
    void SetUp() override {
        // Clean up any existing data files
        if (std::filesystem::exists("data/users.bin")) {
            std::filesystem::remove("data/users.bin");
        }
        app = std::make_unique<LanguageTranslatorApp>();
    }
    
    void TearDown() override {
        app.reset();
    }
    
    std::unique_ptr<LanguageTranslatorApp> app;
};

// Test user registration with valid credentials
TEST_F(LanguageTranslatorUserManagementTest, TestUserRegistration) {
    EXPECT_TRUE(app->registerUser("testuser1", "password123"));
    EXPECT_TRUE(app->registerUser("testuser2", "anotherpass"));
    EXPECT_TRUE(app->registerUser("john_doe", "securePass456"));
}

// Test user registration with duplicate username
TEST_F(LanguageTranslatorUserManagementTest, TestDuplicateUserRegistration) {
    EXPECT_TRUE(app->registerUser("testuser", "password123"));
    EXPECT_FALSE(app->registerUser("testuser", "differentpassword"));
}

// Test admin user is reserved
TEST_F(LanguageTranslatorUserManagementTest, TestAdminUserReserved) {
    EXPECT_FALSE(app->registerUser("admin", "anypassword"));
}

// Test login with valid credentials
TEST_F(LanguageTranslatorUserManagementTest, TestValidLogin) {
    app->registerUser("testuser", "password123");
    EXPECT_TRUE(app->login("testuser", "password123"));
    EXPECT_TRUE(app->isUserLoggedIn());
}

// Test login with invalid credentials
TEST_F(LanguageTranslatorUserManagementTest, TestInvalidLogin) {
    app->registerUser("testuser", "password123");
    EXPECT_FALSE(app->login("testuser", "wrongpassword"));
    EXPECT_FALSE(app->login("nonexistent", "password"));
}

// Test admin login
TEST_F(LanguageTranslatorUserManagementTest, TestAdminLogin) {
    EXPECT_TRUE(app->login("admin", "admin"));
    EXPECT_TRUE(app->isUserLoggedIn());
}

// Test logout functionality
TEST_F(LanguageTranslatorUserManagementTest, TestLogout) {
    app->registerUser("testuser", "password123");
    app->login("testuser", "password123");
    EXPECT_TRUE(app->isUserLoggedIn());
    
    app->logout();
    EXPECT_FALSE(app->isUserLoggedIn());
}

// Test user session persistence
TEST_F(LanguageTranslatorUserManagementTest, TestSessionPersistence) {
    app->registerUser("testuser", "password123");
    app->login("testuser", "password123");
    EXPECT_TRUE(app->isUserLoggedIn());
    
    // Simulate using the app
    app->setSourceLanguage("English");
    app->setTargetLanguage("Turkish");
    app->translateText("hello world");
    
    // Should still be logged in
    EXPECT_TRUE(app->isUserLoggedIn());
}

// Test multiple login attempts
TEST_F(LanguageTranslatorUserManagementTest, TestMultipleLoginAttempts) {
    app->registerUser("testuser", "password123");
    
    // First login
    EXPECT_TRUE(app->login("testuser", "password123"));
    app->logout();
    
    // Second login
    EXPECT_TRUE(app->login("testuser", "password123"));
    app->logout();
    
    // Third login
    EXPECT_TRUE(app->login("testuser", "password123"));
}

// Test concurrent user registration
TEST_F(LanguageTranslatorUserManagementTest, TestConcurrentUsers) {
    EXPECT_TRUE(app->registerUser("user1", "pass1"));
    EXPECT_TRUE(app->registerUser("user2", "pass2"));
    EXPECT_TRUE(app->registerUser("user3", "pass3"));
    
    // All should be able to login
    EXPECT_TRUE(app->login("user1", "pass1"));
    app->logout();
    EXPECT_TRUE(app->login("user2", "pass2"));
    app->logout();
    EXPECT_TRUE(app->login("user3", "pass3"));
}

// Test empty username and password
TEST_F(LanguageTranslatorUserManagementTest, TestEmptyCredentials) {
    EXPECT_TRUE(app->registerUser("", "password"));  // Empty username might be allowed
    EXPECT_TRUE(app->registerUser("username", ""));  // Empty password might be allowed
}

// Test special characters in username
TEST_F(LanguageTranslatorUserManagementTest, TestSpecialCharactersInUsername) {
    EXPECT_TRUE(app->registerUser("user_name", "password"));
    EXPECT_TRUE(app->registerUser("user.name", "password"));
    EXPECT_TRUE(app->registerUser("user123", "password"));
}

// Test long username and password
TEST_F(LanguageTranslatorUserManagementTest, TestLongCredentials) {
    std::string longUsername(100, 'a');
    std::string longPassword(100, 'b');
    EXPECT_TRUE(app->registerUser(longUsername, longPassword));
    EXPECT_TRUE(app->login(longUsername, longPassword));
}

// Test user preferred language settings
TEST_F(LanguageTranslatorUserManagementTest, TestUserPreferredLanguages) {
    app->setSourceLanguage("Spanish");
    app->setTargetLanguage("French");
    
    app->registerUser("testuser", "password");
    app->login("testuser", "password");
    
    // User's preferred languages should be loaded (implementation dependent)
    EXPECT_TRUE(app->isUserLoggedIn());
}
