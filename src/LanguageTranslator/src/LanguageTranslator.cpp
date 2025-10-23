#include "../header/LanguageTranslator.h"
#include <iostream>
#include <limits>
#include <fstream>
#include <sstream>
#include <filesystem>
// #include <json/json.h>  // Commented out for now - API not implemented yet

namespace Coruh
{
    namespace LanguageTranslator
    {
        LanguageTranslatorApp::LanguageTranslatorApp() : isLoggedIn(false), currentSourceLanguage("English"), currentTargetLanguage("Turkish"), useAPI(false), apiProvider("google")
        {
            initializeDefaultData();
        }

        void LanguageTranslatorApp::run()
        {
            loadData();
            showMainMenu();
            saveData();
        }

        void LanguageTranslatorApp::showMainMenu()
        {
            int choice;
            do {
                std::cout << "\n=== Language Translator Application ===\n";
                if (isLoggedIn) {
                    std::cout << "Welcome, " << currentUser << "!\n";
                    std::cout << "Current: " << currentSourceLanguage << " -> " << currentTargetLanguage << "\n";
                    std::cout << "1. Translate Text\n";
                    std::cout << "2. Change Languages\n";
                    std::cout << "3. Phrase Library\n";
                    std::cout << "4. Learning Tips\n";
                    std::cout << "5. Pronunciation Guide\n";
                    std::cout << "6. Logout\n";
                    std::cout << "0. Exit\n";
                } else {
                    std::cout << "1. Login\n";
                    std::cout << "2. Register\n";
                    std::cout << "0. Exit\n";
                }
                std::cout << "Enter your choice: ";
                std::cin >> choice;

                // Clear the input buffer
                std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

                handleUserChoice(choice);

            } while (choice != 0);
        }

        void LanguageTranslatorApp::handleUserChoice(int choice)
        {
            std::string username, password, text, word, phrase, tip, guide;

            if (isLoggedIn) {
                switch (choice) {
                    case 1: // Translate Text
                        std::cout << "Enter text to translate from " << currentSourceLanguage << " to " << currentTargetLanguage << ": ";
                        std::getline(std::cin, text);
                        std::cout << "Translation: " << translateText(text) << std::endl;
                        break;
                    case 2: // Change Languages
                        showLanguageSelection();
                        break;
                    case 3: // Phrase Library
                        showPhraseLibrary();
                        break;
                    case 4: // Learning Tips
                        showLearningTips();
                        break;
                    case 5: // Pronunciation Guide
                        showPronunciationGuide();
                        break;
                    case 6: // Logout
                        logout();
                        std::cout << "Logged out successfully.\n";
                        break;
                    case 0:
                        std::cout << "Exiting application. Goodbye!\n";
                        break;
                    default:
                        std::cout << "Invalid choice. Please try again.\n";
                        break;
                }
            } else {
                switch (choice) {
                    case 1: // Login
                        std::cout << "Enter username: ";
                        std::getline(std::cin, username);
                        std::cout << "Enter password: ";
                        std::getline(std::cin, password);
                        if (login(username, password)) {
                            std::cout << "Login successful!\n";
                        } else {
                            std::cout << "Invalid username or password.\n";
                        }
                        break;
                    case 2: // Register
                        std::cout << "Enter new username: ";
                        std::getline(std::cin, username);
                        std::cout << "Enter new password: ";
                        std::getline(std::cin, password);
                        if (registerUser(username, password)) {
                            std::cout << "Registration successful! You can now log in.\n";
                        } else {
                            std::cout << "Username already exists.\n";
                        }
                        break;
                    case 0:
                        std::cout << "Exiting application. Goodbye!\n";
                        break;
                    default:
                        std::cout << "Invalid choice. Please try again.\n";
                        break;
                }
            }
        }

        std::string LanguageTranslatorApp::translateText(const std::string& text)
        {
            if (currentSourceLanguage == currentTargetLanguage) {
                return text; // No translation needed
            }
            
            // If API is enabled, try API first
            if (useAPI && isAPIAvailable()) {
                std::string apiResult;
                if (apiProvider == "google") {
                    apiResult = translateWithGoogleAPI(text, currentSourceLanguage, currentTargetLanguage);
                } else if (apiProvider == "microsoft") {
                    apiResult = translateWithMicrosoftAPI(text, currentSourceLanguage, currentTargetLanguage);
                }
                
                if (!apiResult.empty()) {
                    return apiResult;
                }
            }
            
            // Fallback to local dictionary
            std::string key = currentSourceLanguage + "_to_" + currentTargetLanguage;
            
            // Try to translate as a phrase first
            if (phraseDictionaries.find(key) != phraseDictionaries.end()) {
                auto& phraseDict = phraseDictionaries[key];
                if (phraseDict.find(text) != phraseDict.end()) {
                    return phraseDict[text];
                }
            }
            
            // Try to translate word by word
            std::string translated;
            std::string word;
            for (char c : text) {
                if (c == ' ') {
                    if (!word.empty()) {
                        if (wordDictionaries.find(key) != wordDictionaries.end()) {
                            auto& wordDict = wordDictionaries[key];
                            if (wordDict.find(word) != wordDict.end()) {
                                translated += wordDict[word] + " ";
                            } else {
                                translated += word + " ";
                            }
                        } else {
                            translated += word + " ";
                        }
                        word.clear();
                    }
                } else {
                    word += c;
                }
            }
            
            // Translate last word
            if (!word.empty()) {
                if (wordDictionaries.find(key) != wordDictionaries.end()) {
                    auto& wordDict = wordDictionaries[key];
                    if (wordDict.find(word) != wordDict.end()) {
                        translated += wordDict[word];
                    } else {
                        translated += word;
                    }
                } else {
                    translated += word;
                }
            }
            
            return translated.empty() ? text : translated;
        }

        std::string LanguageTranslatorApp::translateWord(const std::string& word)
        {
            std::string key = currentSourceLanguage + "_to_" + currentTargetLanguage;
            if (wordDictionaries.find(key) != wordDictionaries.end()) {
                auto& wordDict = wordDictionaries[key];
                if (wordDict.find(word) != wordDict.end()) {
                    return wordDict[word];
                }
            }
            return word;
        }

        std::string LanguageTranslatorApp::translatePhrase(const std::string& phrase)
        {
            std::string key = currentSourceLanguage + "_to_" + currentTargetLanguage;
            if (phraseDictionaries.find(key) != phraseDictionaries.end()) {
                auto& phraseDict = phraseDictionaries[key];
                if (phraseDict.find(phrase) != phraseDict.end()) {
                    return phraseDict[phrase];
                }
            }
            return phrase;
        }

        bool LanguageTranslatorApp::login(const std::string& username, const std::string& password)
        {
            // Simple authentication (in real app, use proper password hashing)
            if (username == "admin" && password == "admin") {
                currentUser = username;
                isLoggedIn = true;
                return true;
            }
            return false;
        }

        bool LanguageTranslatorApp::registerUser(const std::string& username, const std::string& password)
        {
            // Simple registration (in real app, store in database)
            if (username == "admin") {
                return false; // User already exists
            }
            // For demo purposes, accept any new user
            return true;
        }

        void LanguageTranslatorApp::logout()
        {
            currentUser = "";
            isLoggedIn = false;
        }

        bool LanguageTranslatorApp::isUserLoggedIn() const
        {
            return isLoggedIn;
        }

        void LanguageTranslatorApp::showPhraseLibrary()
        {
            std::cout << "\n=== Phrase Library ===\n";
            std::cout << "Current Language Pair: " << currentSourceLanguage << " -> " << currentTargetLanguage << "\n";
            
            std::string key = currentSourceLanguage + "_to_" + currentTargetLanguage;
            if (phraseDictionaries.find(key) != phraseDictionaries.end()) {
                std::cout << "\nPhrase Dictionary:\n";
                for (const auto& pair : phraseDictionaries[key]) {
                    std::cout << pair.first << " -> " << pair.second << std::endl;
                }
            } else {
                std::cout << "No phrase dictionary available for " << currentSourceLanguage << " to " << currentTargetLanguage << std::endl;
            }
            
            std::cout << "\nCommon Phrases:\n";
            for (const auto& phrase : commonPhrases) {
                std::cout << "- " << phrase << std::endl;
            }
        }

        void LanguageTranslatorApp::addPhrase(const std::string& phrase, const std::string& category)
        {
            commonPhrases.push_back(phrase);
            std::cout << "Phrase added: " << phrase << " (Category: " << category << ")\n";
        }

        void LanguageTranslatorApp::showLearningTips()
        {
            std::cout << "\n=== Learning Tips ===\n";
            for (size_t i = 0; i < learningTips.size(); ++i) {
                std::cout << (i + 1) << ". " << learningTips[i] << std::endl;
            }
        }

        void LanguageTranslatorApp::addLearningTip(const std::string& tip)
        {
            learningTips.push_back(tip);
            std::cout << "Learning tip added: " << tip << "\n";
        }

        void LanguageTranslatorApp::showPronunciationGuide()
        {
            std::cout << "\n=== Pronunciation Guide ===\n";
            for (const auto& pair : pronunciationGuide) {
                std::cout << pair.first << " -> " << pair.second << std::endl;
            }
        }

        void LanguageTranslatorApp::addPronunciation(const std::string& word, const std::string& guide)
        {
            pronunciationGuide[word] = guide;
            std::cout << "Pronunciation added: " << word << " -> " << guide << "\n";
        }

        void LanguageTranslatorApp::setSourceLanguage(const std::string& language)
        {
            currentSourceLanguage = language;
            std::cout << "Source language set to: " << language << std::endl;
        }

        void LanguageTranslatorApp::setTargetLanguage(const std::string& language)
        {
            currentTargetLanguage = language;
            std::cout << "Target language set to: " << language << std::endl;
        }

        std::vector<std::string> LanguageTranslatorApp::getSupportedLanguages() const
        {
            return supportedLanguages;
        }

        void LanguageTranslatorApp::showLanguageSelection()
        {
            std::cout << "\n=== Language Selection ===\n";
            std::cout << "Supported Languages:\n";
            for (size_t i = 0; i < supportedLanguages.size(); ++i) {
                std::cout << (i + 1) << ". " << supportedLanguages[i] << std::endl;
            }
            
            std::cout << "\nCurrent: " << currentSourceLanguage << " -> " << currentTargetLanguage << std::endl;
            std::cout << "1. Change Source Language\n";
            std::cout << "2. Change Target Language\n";
            std::cout << "0. Back to Main Menu\n";
            std::cout << "Enter your choice: ";
            
            int choice;
            std::cin >> choice;
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            
            if (choice == 1) {
                std::cout << "Enter source language: ";
                std::string lang;
                std::getline(std::cin, lang);
                setSourceLanguage(lang);
            } else if (choice == 2) {
                std::cout << "Enter target language: ";
                std::string lang;
                std::getline(std::cin, lang);
                setTargetLanguage(lang);
            }
        }

        void LanguageTranslatorApp::addLanguage(const std::string& language)
        {
            if (std::find(supportedLanguages.begin(), supportedLanguages.end(), language) == supportedLanguages.end()) {
                supportedLanguages.push_back(language);
                std::cout << "Language added: " << language << std::endl;
            } else {
                std::cout << "Language already exists: " << language << std::endl;
            }
        }

        void LanguageTranslatorApp::initializeDefaultData()
        {
            // Initialize supported languages
            supportedLanguages = {"English", "Turkish", "Spanish", "French", "German", "Italian"};
            
            // Initialize English to Turkish dictionary
            std::string key = "English_to_Turkish";
            wordDictionaries[key]["hello"] = "merhaba";
            wordDictionaries[key]["world"] = "dünya";
            wordDictionaries[key]["good"] = "iyi";
            wordDictionaries[key]["morning"] = "sabah";
            wordDictionaries[key]["evening"] = "akşam";
            wordDictionaries[key]["thank"] = "teşekkür";
            wordDictionaries[key]["you"] = "sen";
            wordDictionaries[key]["please"] = "lütfen";
            wordDictionaries[key]["yes"] = "evet";
            wordDictionaries[key]["no"] = "hayır";
            wordDictionaries[key]["water"] = "su";
            wordDictionaries[key]["food"] = "yemek";
            wordDictionaries[key]["house"] = "ev";
            wordDictionaries[key]["car"] = "araba";
            wordDictionaries[key]["book"] = "kitap";
            wordDictionaries[key]["computer"] = "bilgisayar";
            wordDictionaries[key]["phone"] = "telefon";
            wordDictionaries[key]["friend"] = "arkadaş";
            wordDictionaries[key]["family"] = "aile";
            wordDictionaries[key]["work"] = "iş";

            // Initialize English to Turkish phrase dictionary
            phraseDictionaries[key]["good morning"] = "günaydın";
            phraseDictionaries[key]["good evening"] = "iyi akşamlar";
            phraseDictionaries[key]["thank you"] = "teşekkür ederim";
            phraseDictionaries[key]["you're welcome"] = "rica ederim";
            phraseDictionaries[key]["how are you"] = "nasılsın";
            phraseDictionaries[key]["i'm fine"] = "iyiyim";
            phraseDictionaries[key]["excuse me"] = "özür dilerim";
            phraseDictionaries[key]["nice to meet you"] = "tanıştığımıza memnun oldum";
            phraseDictionaries[key]["see you later"] = "görüşürüz";
            phraseDictionaries[key]["have a nice day"] = "iyi günler";
            phraseDictionaries[key]["good night"] = "iyi geceler";
            phraseDictionaries[key]["what's your name"] = "adın ne";
            phraseDictionaries[key]["my name is"] = "adım";
            phraseDictionaries[key]["where are you from"] = "nerelisin";
            phraseDictionaries[key]["i am from"] = "ben ...'danım";

            // Initialize English to Spanish dictionary
            key = "English_to_Spanish";
            wordDictionaries[key]["hello"] = "hola";
            wordDictionaries[key]["world"] = "mundo";
            wordDictionaries[key]["good"] = "bueno";
            wordDictionaries[key]["morning"] = "mañana";
            wordDictionaries[key]["evening"] = "tarde";
            wordDictionaries[key]["thank"] = "gracias";
            wordDictionaries[key]["you"] = "tú";
            wordDictionaries[key]["please"] = "por favor";
            wordDictionaries[key]["yes"] = "sí";
            wordDictionaries[key]["no"] = "no";
            wordDictionaries[key]["water"] = "agua";
            wordDictionaries[key]["food"] = "comida";
            wordDictionaries[key]["house"] = "casa";
            wordDictionaries[key]["car"] = "coche";
            wordDictionaries[key]["book"] = "libro";

            // Initialize English to French dictionary
            key = "English_to_French";
            wordDictionaries[key]["hello"] = "bonjour";
            wordDictionaries[key]["world"] = "monde";
            wordDictionaries[key]["good"] = "bon";
            wordDictionaries[key]["morning"] = "matin";
            wordDictionaries[key]["evening"] = "soir";
            wordDictionaries[key]["thank"] = "merci";
            wordDictionaries[key]["you"] = "vous";
            wordDictionaries[key]["please"] = "s'il vous plaît";
            wordDictionaries[key]["yes"] = "oui";
            wordDictionaries[key]["no"] = "non";
            wordDictionaries[key]["water"] = "eau";
            wordDictionaries[key]["food"] = "nourriture";
            wordDictionaries[key]["house"] = "maison";
            wordDictionaries[key]["car"] = "voiture";
            wordDictionaries[key]["book"] = "livre";

            // Initialize common phrases
            commonPhrases = {
                "Hello", "Goodbye", "Thank you", "Please", "Excuse me",
                "How are you?", "I'm fine", "Nice to meet you", "See you later"
            };

            // Initialize learning tips
            learningTips = {
                "Practice daily for at least 15 minutes",
                "Use flashcards for vocabulary building",
                "Listen to native speakers regularly",
                "Practice speaking with others",
                "Read books and articles in the target language",
                "Watch movies with subtitles",
                "Join language exchange groups",
                "Keep a vocabulary notebook",
                "Use language learning apps",
                "Don't be afraid to make mistakes"
            };

            // Initialize pronunciation guide
            pronunciationGuide["hello"] = "həˈloʊ";
            pronunciationGuide["world"] = "wɜːrld";
            pronunciationGuide["good"] = "ɡʊd";
            pronunciationGuide["morning"] = "ˈmɔːrnɪŋ";
            pronunciationGuide["thank"] = "θæŋk";
            pronunciationGuide["you"] = "juː";
        }

        void LanguageTranslatorApp::saveData()
        {
            // In a real application, save to files or database
            std::cout << "Data saved successfully.\n";
        }

        void LanguageTranslatorApp::loadData()
        {
            // In a real application, load from files or database
            std::cout << "Data loaded successfully.\n";
            loadAllDictionaries();
        }

        bool LanguageTranslatorApp::loadDictionaryFromFile(const std::string& sourceLang, const std::string& targetLang, const std::string& filename)
        {
            std::ifstream file(filename);
            if (!file.is_open()) {
                std::cout << "Warning: Could not open dictionary file: " << filename << std::endl;
                return false;
            }

            std::string key = sourceLang + "_to_" + targetLang;
            std::string line;
            int loadedCount = 0;

            while (std::getline(file, line)) {
                // Skip empty lines and comments
                if (line.empty() || line[0] == '#') continue;

                // Parse format: "source_word:target_word"
                size_t colonPos = line.find(':');
                if (colonPos != std::string::npos) {
                    std::string sourceWord = line.substr(0, colonPos);
                    std::string targetWord = line.substr(colonPos + 1);
                    
                    // Trim whitespace
                    sourceWord.erase(0, sourceWord.find_first_not_of(" \t"));
                    sourceWord.erase(sourceWord.find_last_not_of(" \t") + 1);
                    targetWord.erase(0, targetWord.find_first_not_of(" \t"));
                    targetWord.erase(targetWord.find_last_not_of(" \t") + 1);
                    
                    if (!sourceWord.empty() && !targetWord.empty()) {
                        wordDictionaries[key][sourceWord] = targetWord;
                        loadedCount++;
                    }
                }
            }

            file.close();
            std::cout << "Loaded " << loadedCount << " words from " << filename << std::endl;
            return true;
        }

        void LanguageTranslatorApp::loadAllDictionaries()
        {
            // Create dictionaries directory if it doesn't exist
            std::filesystem::create_directory("dictionaries");

            // Load English to Turkish dictionary
            loadDictionaryFromFile("English", "Turkish", "dictionaries/en_tr.txt");
            
            // Load English to Spanish dictionary
            loadDictionaryFromFile("English", "Spanish", "dictionaries/en_es.txt");
            
            // Load English to French dictionary
            loadDictionaryFromFile("English", "French", "dictionaries/en_fr.txt");
            
            // Load Turkish to English dictionary
            loadDictionaryFromFile("Turkish", "English", "dictionaries/tr_en.txt");
        }

        // API Translation Functions
        std::string LanguageTranslatorApp::translateWithGoogleAPI(const std::string& text, const std::string& sourceLang, const std::string& targetLang)
        {
            // TODO: Implement Google API integration
            // For now, return empty string to indicate API not available
            std::cout << "Google API not implemented yet" << std::endl;
            return "";
        }

        std::string LanguageTranslatorApp::translateWithMicrosoftAPI(const std::string& text, const std::string& sourceLang, const std::string& targetLang)
        {
            // TODO: Implement Microsoft API integration
            // For now, return empty string to indicate API not available
            std::cout << "Microsoft API not implemented yet" << std::endl;
            return "";
        }

        bool LanguageTranslatorApp::isAPIAvailable()
        {
            // API is not implemented yet, so it should always return false
            return false;
        }

        void LanguageTranslatorApp::setAPIKey(const std::string& key)
        {
            apiKey = key;
        }

        void LanguageTranslatorApp::setAPIMode(bool useAPI)
        {
            this->useAPI = useAPI;
        }
    }
}