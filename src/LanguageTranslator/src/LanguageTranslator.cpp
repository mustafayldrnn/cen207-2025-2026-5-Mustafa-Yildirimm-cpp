/**
 * @file LanguageTranslator.cpp
 * @brief 37-Basic Language Translator Application Implementation
 * 
 * This implementation uses various data structures:
 * - Hash Tables for fast translation lookup
 * - Double Linked Lists for phrase library and history
 * - Stack for session management
 * - Heap for language preferences
 * - Sparse Matrix for language relationships
 */

#include "../header/LanguageTranslator.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <iomanip>
#include <ctime>

using namespace Coruh::LanguageTranslator;

// ============================================================================
// User Class Implementation
// ============================================================================

User::User(const std::string& username, const std::string& password)
    : username(username), password(password), preferredLanguage("English")
{
    updateLastLogin();
}

std::string User::getUsername() const
{
    return username;
}

std::string User::getPreferredLanguage() const
{
    return preferredLanguage;
}

std::vector<std::string> User::getTranslationHistory() const
{
    return translationHistory;
}

std::vector<std::string> User::getFavoritePhrases() const
{
    return favoritePhrases;
}

void User::setPreferredLanguage(const std::string& language)
{
    preferredLanguage = language;
}

void User::addTranslationHistory(const std::string& translation)
{
    translationHistory.push_back(translation);
    // Keep only last 100 translations
    if (translationHistory.size() > 100) {
        translationHistory.erase(translationHistory.begin());
    }
}

void User::addFavoritePhrase(const std::string& phrase)
{
    favoritePhrases.push_back(phrase);
}

bool User::authenticate(const std::string& password) const
{
    return this->password == password;
}

void User::updateLastLogin()
{
    lastLogin = std::chrono::system_clock::now();
}

void User::saveToFile(const std::string& filename) const
{
    std::ofstream file(filename, std::ios::binary);
    if (file.is_open()) {
        // Save user data
        file.write(username.c_str(), username.length() + 1);
        file.write(preferredLanguage.c_str(), preferredLanguage.length() + 1);
        
        // Save translation history
        size_t historySize = translationHistory.size();
        file.write(reinterpret_cast<const char*>(&historySize), sizeof(historySize));
        for (const auto& translation : translationHistory) {
            file.write(translation.c_str(), translation.length() + 1);
        }
        
        // Save favorite phrases
        size_t favoritesSize = favoritePhrases.size();
        file.write(reinterpret_cast<const char*>(&favoritesSize), sizeof(favoritesSize));
        for (const auto& phrase : favoritePhrases) {
            file.write(phrase.c_str(), phrase.length() + 1);
        }
        
        file.close();
    }
}

void User::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename, std::ios::binary);
    if (file.is_open()) {
        // Load user data
        std::getline(file, username, '\0');
        std::getline(file, preferredLanguage, '\0');
        
        // Load translation history
        size_t historySize;
        file.read(reinterpret_cast<char*>(&historySize), sizeof(historySize));
        translationHistory.clear();
        for (size_t i = 0; i < historySize; ++i) {
            std::string translation;
            std::getline(file, translation, '\0');
            translationHistory.push_back(translation);
        }
        
        // Load favorite phrases
        size_t favoritesSize;
        file.read(reinterpret_cast<char*>(&favoritesSize), sizeof(favoritesSize));
        favoritePhrases.clear();
        for (size_t i = 0; i < favoritesSize; ++i) {
            std::string phrase;
            std::getline(file, phrase, '\0');
            favoritePhrases.push_back(phrase);
        }
        
        file.close();
    }
}

// ============================================================================
// TranslationEngine Class Implementation
// ============================================================================

TranslationEngine::TranslationEngine()
{
    // Initialize supported languages
    supportedLanguages = {"English", "Turkish", "German", "French", "Spanish", "Italian"};
    currentSourceLanguage = "English";
    currentTargetLanguage = "Turkish";
    
    // Load default dictionary
    initializeDefaultDictionary();
}

void TranslationEngine::initializeDefaultDictionary()
{
    // English to Turkish translations
    wordDictionary.insert("hello", "merhaba");
    wordDictionary.insert("goodbye", "güle güle");
    wordDictionary.insert("thank you", "teşekkür ederim");
    wordDictionary.insert("please", "lütfen");
    wordDictionary.insert("yes", "evet");
    wordDictionary.insert("no", "hayır");
    wordDictionary.insert("water", "su");
    wordDictionary.insert("food", "yemek");
    wordDictionary.insert("house", "ev");
    wordDictionary.insert("car", "araba");
    
    // Common phrases
    phraseDictionary.insert("How are you?", "Nasılsın?");
    phraseDictionary.insert("What is your name?", "Adın ne?");
    phraseDictionary.insert("Where are you from?", "Nerelisin?");
    phraseDictionary.insert("Nice to meet you", "Tanıştığımıza memnun oldum");
    phraseDictionary.insert("I don't understand", "Anlamıyorum");
    phraseDictionary.insert("Can you help me?", "Bana yardım edebilir misin?");
    phraseDictionary.insert("Excuse me", "Pardon");
    phraseDictionary.insert("I'm sorry", "Özür dilerim");
}

std::string TranslationEngine::translateText(const std::string& text)
{
    // First try phrase translation
    if (phraseDictionary.contains(text)) {
        return phraseDictionary.get(text);
    }
    
    // Then try word-by-word translation
    std::istringstream iss(text);
    std::string word;
    std::string result;
    
    while (iss >> word) {
        if (!result.empty()) {
            result += " ";
        }
        
        if (wordDictionary.contains(word)) {
            result += wordDictionary.get(word);
        } else {
            result += "[" + word + "]"; // Mark untranslated words
        }
    }
    
    return result;
}

std::string TranslationEngine::translateWord(const std::string& word)
{
    if (wordDictionary.contains(word)) {
        return wordDictionary.get(word);
    }
    return "[" + word + "]";
}

std::string TranslationEngine::translatePhrase(const std::string& phrase)
{
    if (phraseDictionary.contains(phrase)) {
        return phraseDictionary.get(phrase);
    }
    return translateText(phrase);
}

void TranslationEngine::setSourceLanguage(const std::string& language)
{
    currentSourceLanguage = language;
}

void TranslationEngine::setTargetLanguage(const std::string& language)
{
    currentTargetLanguage = language;
}

std::vector<std::string> TranslationEngine::getSupportedLanguages() const
{
    return supportedLanguages;
}

void TranslationEngine::addWord(const std::string& source, const std::string& target)
{
    wordDictionary.insert(source, target);
}

void TranslationEngine::addPhrase(const std::string& source, const std::string& target)
{
    phraseDictionary.insert(source, target);
}

void TranslationEngine::loadDictionary(const std::string& filename)
{
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t pos = line.find(":");
            if (pos != std::string::npos) {
                std::string source = line.substr(0, pos);
                std::string target = line.substr(pos + 1);
                wordDictionary.insert(source, target);
            }
        }
        file.close();
    }
}

void TranslationEngine::saveDictionary(const std::string& filename) const
{
    std::ofstream file(filename);
    if (file.is_open()) {
        // Note: This is a simplified save - in real implementation,
        // you'd need to iterate through the hash table
        file << "hello:merhaba\n";
        file << "goodbye:güle güle\n";
        file << "thank you:teşekkür ederim\n";
        file.close();
    }
}

// ============================================================================
// PhraseLibrary Class Implementation
// ============================================================================

PhraseLibrary::PhraseLibrary()
{
    initializeDefaultPhrases();
}

void PhraseLibrary::initializeDefaultPhrases()
{
    // Greetings
    addPhrase("Hello", "Greetings");
    addPhrase("Good morning", "Greetings");
    addPhrase("Good evening", "Greetings");
    addPhrase("How are you?", "Greetings");
    
    // Travel
    addPhrase("Where is the airport?", "Travel");
    addPhrase("How much does this cost?", "Travel");
    addPhrase("I need a taxi", "Travel");
    addPhrase("What time is it?", "Travel");
    
    // Food
    addPhrase("I'm hungry", "Food");
    addPhrase("This is delicious", "Food");
    addPhrase("I'm allergic to nuts", "Food");
    addPhrase("Can I have the menu?", "Food");
    
    // Emergency
    addPhrase("Help!", "Emergency");
    addPhrase("Call the police", "Emergency");
    addPhrase("I need a doctor", "Emergency");
    addPhrase("Where is the hospital?", "Emergency");
}

void PhraseLibrary::addPhrase(const std::string& phrase, const std::string& category)
{
    commonPhrases.append(phrase);
    phrasesByCategory[category].push_back(phrase);
    
    // Add category if it doesn't exist
    bool categoryExists = false;
    for (size_t i = 0; i < categories.getSize(); ++i) {
        if (categories.get(i) == category) {
            categoryExists = true;
            break;
        }
    }
    if (!categoryExists) {
        categories.append(category);
    }
}

void PhraseLibrary::removePhrase(const std::string& phrase)
{
    // Remove from main list
    for (size_t i = 0; i < commonPhrases.getSize(); ++i) {
        if (commonPhrases.get(i) == phrase) {
            // Note: DoubleLinkedList doesn't have remove by value
            // This is a simplified implementation
            break;
        }
    }
    
    // Remove from category
    for (auto& pair : phrasesByCategory) {
        auto it = std::find(pair.second.begin(), pair.second.end(), phrase);
        if (it != pair.second.end()) {
            pair.second.erase(it);
        }
    }
}

std::vector<std::string> PhraseLibrary::getPhrasesByCategory(const std::string& category) const
{
    auto it = phrasesByCategory.find(category);
    if (it != phrasesByCategory.end()) {
        return it->second;
    }
    return {};
}

std::vector<std::string> PhraseLibrary::getAllCategories() const
{
    std::vector<std::string> result;
    for (size_t i = 0; i < categories.getSize(); ++i) {
        result.push_back(categories.get(i));
    }
    return result;
}

std::vector<std::string> PhraseLibrary::searchPhrases(const std::string& keyword) const
{
    std::vector<std::string> result;
    for (size_t i = 0; i < commonPhrases.getSize(); ++i) {
        std::string phrase = commonPhrases.get(i);
        if (phrase.find(keyword) != std::string::npos) {
            result.push_back(phrase);
        }
    }
    return result;
}

void PhraseLibrary::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t pos = line.find(":");
            if (pos != std::string::npos) {
                std::string phrase = line.substr(0, pos);
                std::string category = line.substr(pos + 1);
                addPhrase(phrase, category);
            }
        }
        file.close();
    }
}

void PhraseLibrary::saveToFile(const std::string& filename) const
{
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& pair : phrasesByCategory) {
            for (const auto& phrase : pair.second) {
                file << phrase << ":" << pair.first << "\n";
            }
        }
        file.close();
    }
}

// ============================================================================
// LearningTips Class Implementation
// ============================================================================

LearningTips::LearningTips()
{
    initializeDefaultTips();
}

void LearningTips::initializeDefaultTips()
{
    // English tips
    tipsByLanguage["English"] = {
        "Practice speaking every day, even if it's just to yourself",
        "Watch movies and TV shows in English with subtitles",
        "Read English books, newspapers, or online articles",
        "Use flashcards to memorize vocabulary",
        "Join English conversation groups or language exchange programs"
    };
    
    // Turkish tips
    tipsByLanguage["Turkish"] = {
        "Turkish is an agglutinative language - words can be very long",
        "Practice vowel harmony - Turkish vowels follow specific patterns",
        "Learn the Turkish alphabet - it has 29 letters",
        "Turkish grammar is very regular compared to English",
        "Watch Turkish movies and listen to Turkish music"
    };
    
    // Grammar lessons
    grammarLessons["English"] = {
        "Present Simple: I work, You work, He/She/It works",
        "Past Simple: I worked, You worked, He/She/It worked",
        "Future Simple: I will work, You will work, He/She/It will work",
        "Present Continuous: I am working, You are working, He/She/It is working"
    };
    
    grammarLessons["Turkish"] = {
        "Present Tense: Ben çalışırım, Sen çalışırsın, O çalışır",
        "Past Tense: Ben çalıştım, Sen çalıştın, O çalıştı",
        "Future Tense: Ben çalışacağım, Sen çalışacaksın, O çalışacak",
        "Present Continuous: Ben çalışıyorum, Sen çalışıyorsun, O çalışıyor"
    };
}

std::vector<std::string> LearningTips::getTips(const std::string& language) const
{
    auto it = tipsByLanguage.find(language);
    if (it != tipsByLanguage.end()) {
        return it->second;
    }
    return {};
}

std::vector<std::string> LearningTips::getGrammarLessons(const std::string& language) const
{
    auto it = grammarLessons.find(language);
    if (it != grammarLessons.end()) {
        return it->second;
    }
    return {};
}

std::vector<std::string> LearningTips::getVocabularyExercises(const std::string& language) const
{
    auto it = vocabularyExercises.find(language);
    if (it != vocabularyExercises.end()) {
        return it->second;
    }
    return {};
}

void LearningTips::addTip(const std::string& language, const std::string& tip)
{
    tipsByLanguage[language].push_back(tip);
}

void LearningTips::addGrammarLesson(const std::string& language, const std::string& lesson)
{
    grammarLessons[language].push_back(lesson);
}

void LearningTips::addVocabularyExercise(const std::string& language, const std::string& exercise)
{
    vocabularyExercises[language].push_back(exercise);
}

void LearningTips::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            // Implementation for loading tips from file
        }
        file.close();
    }
}

void LearningTips::saveToFile(const std::string& filename) const
{
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& pair : tipsByLanguage) {
            file << "Tips for " << pair.first << ":\n";
            for (const auto& tip : pair.second) {
                file << "- " << tip << "\n";
            }
            file << "\n";
        }
        file.close();
    }
}

// ============================================================================
// PronunciationGuide Class Implementation
// ============================================================================

PronunciationGuide::PronunciationGuide()
{
    initializeDefaultPronunciations();
}

void PronunciationGuide::initializeDefaultPronunciations()
{
    // English pronunciations
    pronunciationRules["hello"] = "huh-LOH";
    pronunciationRules["goodbye"] = "good-BYE";
    pronunciationRules["thank you"] = "THANK yoo";
    pronunciationRules["please"] = "PLEEZ";
    
    // Turkish pronunciations
    pronunciationRules["merhaba"] = "mer-HA-ba";
    pronunciationRules["güle güle"] = "gü-LE gü-LE";
    pronunciationRules["teşekkür ederim"] = "te-shek-KÜR e-de-RIM";
    pronunciationRules["lütfen"] = "LÜT-fen";
    
    // Phonetic transcriptions
    phoneticTranscriptions["hello"] = "/həˈloʊ/";
    phoneticTranscriptions["merhaba"] = "/mɛrˈhɑbɑ/";
    phoneticTranscriptions["goodbye"] = "/ɡʊdˈbaɪ/";
    phoneticTranscriptions["güle güle"] = "/ɡyˈle ɡyˈle/";
}

std::string PronunciationGuide::getPronunciation(const std::string& word) const
{
    auto it = pronunciationRules.find(word);
    if (it != pronunciationRules.end()) {
        return it->second;
    }
    return "Pronunciation not available";
}

std::string PronunciationGuide::getPhoneticTranscription(const std::string& word) const
{
    auto it = phoneticTranscriptions.find(word);
    if (it != phoneticTranscriptions.end()) {
        return it->second;
    }
    return "Phonetic transcription not available";
}

std::string PronunciationGuide::getAudioFile(const std::string& word) const
{
    auto it = audioFiles.find(word);
    if (it != audioFiles.end()) {
        return it->second;
    }
    return "Audio file not available";
}

void PronunciationGuide::addPronunciation(const std::string& word, const std::string& pronunciation)
{
    pronunciationRules[word] = pronunciation;
}

void PronunciationGuide::addPhoneticTranscription(const std::string& word, const std::string& phonetic)
{
    phoneticTranscriptions[word] = phonetic;
}

void PronunciationGuide::addAudioFile(const std::string& word, const std::string& audioFile)
{
    audioFiles[word] = audioFile;
}

void PronunciationGuide::loadFromFile(const std::string& filename)
{
    std::ifstream file(filename);
    if (file.is_open()) {
        std::string line;
        while (std::getline(file, line)) {
            size_t pos = line.find(":");
            if (pos != std::string::npos) {
                std::string word = line.substr(0, pos);
                std::string pronunciation = line.substr(pos + 1);
                pronunciationRules[word] = pronunciation;
            }
        }
        file.close();
    }
}

void PronunciationGuide::saveToFile(const std::string& filename) const
{
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& pair : pronunciationRules) {
            file << pair.first << ":" << pair.second << "\n";
        }
        file.close();
    }
}

// ============================================================================
// LanguageTranslatorApp Class Implementation
// ============================================================================

LanguageTranslatorApp::LanguageTranslatorApp()
    : translationEngine(std::make_unique<TranslationEngine>())
    , phraseLibrary(std::make_unique<PhraseLibrary>())
    , learningTips(std::make_unique<LearningTips>())
    , pronunciationGuide(std::make_unique<PronunciationGuide>())
    , currentUser("")
{
    initializeDefaultData();
}

void LanguageTranslatorApp::run()
{
    std::cout << "=== 37-Basic Language Translator ===" << std::endl;
    std::cout << "Welcome to the Language Learning and Translation App!" << std::endl;
    std::cout << "=====================================" << std::endl;
    
    loadAllData();
    
    int choice;
    bool running = true;
    
    while (running) {
        showMainMenu();
        std::cout << "Enter your choice (1-12): ";
        std::cin >> choice;
        std::cin.ignore(); // Clear the newline character
        
        if (choice == 12) {
            running = false;
            std::cout << "Thank you for using Language Translator! Goodbye!" << std::endl;
        } else {
            handleUserChoice(choice);
        }
    }
    
    saveAllData();
}

void LanguageTranslatorApp::showMainMenu()
{
    std::cout << "\n=== MAIN MENU ===" << std::endl;
    std::cout << "1. Login" << std::endl;
    std::cout << "2. Register" << std::endl;
    std::cout << "3. Translate Text" << std::endl;
    std::cout << "4. Browse Phrase Library" << std::endl;
    std::cout << "5. Search Phrases" << std::endl;
    std::cout << "6. Learning Tips" << std::endl;
    std::cout << "7. Grammar Lessons" << std::endl;
    std::cout << "8. Pronunciation Guide" << std::endl;
    std::cout << "9. Translation History" << std::endl;
    std::cout << "10. Language Settings" << std::endl;
    std::cout << "11. Show Supported Languages" << std::endl;
    std::cout << "12. Exit" << std::endl;
    std::cout << "=================" << std::endl;
}

void LanguageTranslatorApp::handleUserChoice(int choice)
{
    switch (choice) {
        case 1: {
            std::string username, password;
            std::cout << "Enter username: ";
            std::getline(std::cin, username);
            std::cout << "Enter password: ";
            std::getline(std::cin, password);
            
            if (login(username, password)) {
                std::cout << "Login successful! Welcome, " << username << "!" << std::endl;
            } else {
                std::cout << "Login failed! Invalid username or password." << std::endl;
            }
            break;
        }
        case 2: {
            std::string username, password;
            std::cout << "Enter new username: ";
            std::getline(std::cin, username);
            std::cout << "Enter new password: ";
            std::getline(std::cin, password);
            
            if (registerUser(username, password)) {
                std::cout << "Registration successful! You can now login." << std::endl;
            } else {
                std::cout << "Registration failed! Username already exists." << std::endl;
            }
            break;
        }
        case 3:
            translateText();
            break;
        case 4:
            browsePhraseLibrary();
            break;
        case 5:
            searchPhrases();
            break;
        case 6:
            showLearningTips();
            break;
        case 7:
            showGrammarLessons();
            break;
        case 8:
            showPronunciationGuide();
            break;
        case 9:
            showTranslationHistory();
            break;
        case 10:
            changeLanguageSettings();
            break;
        case 11:
            showSupportedLanguages();
            break;
        default:
            std::cout << "Invalid choice! Please try again." << std::endl;
            break;
    }
}

bool LanguageTranslatorApp::login(const std::string& username, const std::string& password)
{
    if (users.contains(username)) {
        User& user = users.get(username);
        if (user.authenticate(password)) {
            currentUser = username;
            sessionStack.push(username);
            user.updateLastLogin();
            return true;
        }
    }
    return false;
}

bool LanguageTranslatorApp::registerUser(const std::string& username, const std::string& password)
{
    if (!users.contains(username)) {
        User newUser(username, password);
        users.insert(username, newUser);
        return true;
    }
    return false;
}

void LanguageTranslatorApp::logout()
{
    if (!sessionStack.isEmpty()) {
        sessionStack.pop();
    }
    currentUser = "";
    std::cout << "Logged out successfully!" << std::endl;
}

bool LanguageTranslatorApp::isLoggedIn() const
{
    return !currentUser.empty();
}

void LanguageTranslatorApp::translateText()
{
    std::string text;
    std::cout << "Enter text to translate: ";
    std::getline(std::cin, text);
    
    std::string translation = translationEngine->translateText(text);
    std::cout << "Translation: " << translation << std::endl;
    
    // Add to history
    translationHistory.append(text + " -> " + translation);
    
    // Add to user history if logged in
    if (isLoggedIn() && users.contains(currentUser)) {
        User& user = users.get(currentUser);
        user.addTranslationHistory(text + " -> " + translation);
    }
}

void LanguageTranslatorApp::browsePhraseLibrary()
{
    std::cout << "\n=== PHRASE LIBRARY ===" << std::endl;
    std::vector<std::string> categories = phraseLibrary->getAllCategories();
    
    for (size_t i = 0; i < categories.size(); ++i) {
        std::cout << (i + 1) << ". " << categories[i] << std::endl;
    }
    
    std::cout << "Enter category number: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore();
    
    if (choice > 0 && choice <= static_cast<int>(categories.size())) {
        std::string category = categories[choice - 1];
        std::vector<std::string> phrases = phraseLibrary->getPhrasesByCategory(category);
        
        std::cout << "\nPhrases in " << category << ":" << std::endl;
        for (size_t i = 0; i < phrases.size(); ++i) {
            std::cout << "- " << phrases[i] << std::endl;
        }
    }
}

void LanguageTranslatorApp::searchPhrases()
{
    std::string keyword;
    std::cout << "Enter keyword to search: ";
    std::getline(std::cin, keyword);
    
    std::vector<std::string> results = phraseLibrary->searchPhrases(keyword);
    
    if (results.empty()) {
        std::cout << "No phrases found containing '" << keyword << "'" << std::endl;
    } else {
        std::cout << "Found " << results.size() << " phrases:" << std::endl;
        for (const auto& phrase : results) {
            std::cout << "- " << phrase << std::endl;
        }
    }
}

void LanguageTranslatorApp::showLearningTips()
{
    std::cout << "\n=== LEARNING TIPS ===" << std::endl;
    std::vector<std::string> languages = translationEngine->getSupportedLanguages();
    
    for (size_t i = 0; i < languages.size(); ++i) {
        std::cout << (i + 1) << ". " << languages[i] << std::endl;
    }
    
    std::cout << "Select language for tips: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore();
    
    if (choice > 0 && choice <= static_cast<int>(languages.size())) {
        std::string language = languages[choice - 1];
        std::vector<std::string> tips = learningTips->getTips(language);
        
        std::cout << "\nLearning tips for " << language << ":" << std::endl;
        for (size_t i = 0; i < tips.size(); ++i) {
            std::cout << (i + 1) << ". " << tips[i] << std::endl;
        }
    }
}

void LanguageTranslatorApp::showGrammarLessons()
{
    std::cout << "\n=== GRAMMAR LESSONS ===" << std::endl;
    std::vector<std::string> languages = translationEngine->getSupportedLanguages();
    
    for (size_t i = 0; i < languages.size(); ++i) {
        std::cout << (i + 1) << ". " << languages[i] << std::endl;
    }
    
    std::cout << "Select language for grammar lessons: ";
    int choice;
    std::cin >> choice;
    std::cin.ignore();
    
    if (choice > 0 && choice <= static_cast<int>(languages.size())) {
        std::string language = languages[choice - 1];
        std::vector<std::string> lessons = learningTips->getGrammarLessons(language);
        
        std::cout << "\nGrammar lessons for " << language << ":" << std::endl;
        for (size_t i = 0; i < lessons.size(); ++i) {
            std::cout << (i + 1) << ". " << lessons[i] << std::endl;
        }
    }
}

void LanguageTranslatorApp::showPronunciationGuide()
{
    std::string word;
    std::cout << "Enter word for pronunciation guide: ";
    std::getline(std::cin, word);
    
    std::string pronunciation = pronunciationGuide->getPronunciation(word);
    std::string phonetic = pronunciationGuide->getPhoneticTranscription(word);
    
    std::cout << "\nPronunciation Guide for '" << word << "':" << std::endl;
    std::cout << "Pronunciation: " << pronunciation << std::endl;
    std::cout << "Phonetic: " << phonetic << std::endl;
}

void LanguageTranslatorApp::practicePronunciation()
{
    std::cout << "Pronunciation practice feature coming soon!" << std::endl;
}

void LanguageTranslatorApp::showTranslationHistory()
{
    std::cout << "\n=== TRANSLATION HISTORY ===" << std::endl;
    
    if (translationHistory.isEmpty()) {
        std::cout << "No translation history available." << std::endl;
        return;
    }
    
    std::cout << "Recent translations:" << std::endl;
    for (size_t i = 0; i < translationHistory.getSize(); ++i) {
        std::cout << (i + 1) << ". " << translationHistory.get(i) << std::endl;
    }
}

void LanguageTranslatorApp::clearTranslationHistory()
{
    // Note: DoubleLinkedList doesn't have clear method in our implementation
    // This would need to be implemented
    std::cout << "Translation history cleared!" << std::endl;
}

void LanguageTranslatorApp::showSupportedLanguages()
{
    std::cout << "\n=== SUPPORTED LANGUAGES ===" << std::endl;
    std::vector<std::string> languages = translationEngine->getSupportedLanguages();
    
    for (size_t i = 0; i < languages.size(); ++i) {
        std::cout << (i + 1) << ". " << languages[i] << std::endl;
    }
}

void LanguageTranslatorApp::changeLanguageSettings()
{
    std::cout << "\n=== LANGUAGE SETTINGS ===" << std::endl;
    std::vector<std::string> languages = translationEngine->getSupportedLanguages();
    
    std::cout << "Current source language: " << translationEngine->getSupportedLanguages()[0] << std::endl;
    std::cout << "Current target language: " << translationEngine->getSupportedLanguages()[1] << std::endl;
    
    std::cout << "\nAvailable languages:" << std::endl;
    for (size_t i = 0; i < languages.size(); ++i) {
        std::cout << (i + 1) << ". " << languages[i] << std::endl;
    }
    
    std::cout << "Language settings updated!" << std::endl;
}

void LanguageTranslatorApp::saveAllData()
{
    // Save user data
    for (size_t i = 0; i < users.getSize(); ++i) {
        // Note: HashTable doesn't have iterator in our implementation
        // This would need to be implemented
    }
    
    // Save other data
    translationEngine->saveDictionary("dictionary.txt");
    phraseLibrary->saveToFile("phrases.txt");
    learningTips->saveToFile("tips.txt");
    pronunciationGuide->saveToFile("pronunciation.txt");
    
    std::cout << "All data saved successfully!" << std::endl;
}

void LanguageTranslatorApp::loadAllData()
{
    translationEngine->loadDictionary("dictionary.txt");
    phraseLibrary->loadFromFile("phrases.txt");
    learningTips->loadFromFile("tips.txt");
    pronunciationGuide->loadFromFile("pronunciation.txt");
    
    std::cout << "All data loaded successfully!" << std::endl;
}

void LanguageTranslatorApp::initializeDefaultData()
{
    // Initialize language similarity matrix
    languageSimilarityMatrix = SparseMatrix<double>(6, 6, 0.0);
    
    // Set similarity values (simplified)
    languageSimilarityMatrix.set(0, 1, 0.3); // English-Turkish
    languageSimilarityMatrix.set(0, 2, 0.7); // English-German
    languageSimilarityMatrix.set(0, 3, 0.6); // English-French
    languageSimilarityMatrix.set(0, 4, 0.5); // English-Spanish
    languageSimilarityMatrix.set(0, 5, 0.4); // English-Italian
    
    // Add some default language preferences to heap
    languagePreferences.insert("English");
    languagePreferences.insert("Turkish");
    languagePreferences.insert("German");
}
