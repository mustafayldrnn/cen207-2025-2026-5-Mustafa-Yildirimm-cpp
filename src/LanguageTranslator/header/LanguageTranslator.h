/**
 * @file LanguageTranslator.h
 * @brief Console-based language translator main interface
 * @author Mustafa Yıldırım
 * @date 2025
 * @version 1.0
 */
#ifndef LANGUAGE_TRANSLATOR_H
#define LANGUAGE_TRANSLATOR_H

#include <string>
#include <vector>
#include <unordered_map>
#include <memory>
#include <iostream>
#include "Persistence.h"

namespace Coruh {
namespace LanguageTranslator {

/**
 * @class LanguageTranslatorApp
 * @brief Manages application flow: auth, translation, tips, phrases, pronunciation
 * 
 * Bu sınıf, çok dilli çeviri uygulamasının ana işlevlerini yönetir.
 * Kullanıcı kimlik doğrulama, çeviri işlemleri, öğrenme ipuçları,
 * kelime öbekleri ve telaffuz rehberi gibi özellikleri içerir.
 */
class LanguageTranslatorApp {
private:
    // Multi-language dictionaries
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> wordDictionaries;  ///< Kelime sözlükleri
    std::unordered_map<std::string, std::unordered_map<std::string, std::string>> phraseDictionaries;  ///< Kelime öbeği sözlükleri

    // Language support
    std::vector<std::string> supportedLanguages;  ///< Desteklenen diller listesi
    std::string currentSourceLanguage;  ///< Mevcut kaynak dil
    std::string currentTargetLanguage;  ///< Mevcut hedef dil

    // Other features
    std::vector<std::string> commonPhrases;  ///< Yaygın kullanılan kelime öbekleri
    std::vector<std::string> learningTips;  ///< Öğrenme ipuçları
    std::unordered_map<std::string, std::string> pronunciationGuide;  ///< Telaffuz rehberi

    std::string currentUser;  ///< Mevcut kullanıcı adı
    bool isLoggedIn;  ///< Kullanıcı giriş yapmış mı?
    std::vector<UserProfile> users;   ///< Kayıtlı kullanıcılar
    std::vector<TranslationRecord> history; ///< Çeviri geçmişi

    // API settings
    std::string apiKey;  ///< API anahtarı
    bool useAPI;  ///< API kullanılsın mı?
    std::string apiProvider; ///< API sağlayıcısı ("google" veya "microsoft")

public:
    /**
     * @brief Varsayılan verilerle uygulamayı başlatır
     */
    LanguageTranslatorApp();
    
    /**
     * @brief Destructor
     */
    ~LanguageTranslatorApp() = default;

    /**
     * @brief Ana uygulama döngüsünü çalıştırır (yükle, menü, kaydet)
     */
    void run();
    
    /**
     * @brief Ana menüyü gösterir
     */
    void showMainMenu();
    
    /**
     * @brief Ana menü seçimini işler
     * @param choice Kullanıcının seçimi
     */
    void handleUserChoice(int choice);

    // Translation functions
    /**
     * @brief Aktif dil çiftini kullanarak metni çevirir
     * @param text Çevrilecek metin
     * @return Çevrilmiş metin
     */
    std::string translateText(const std::string& text);
    
    /**
     * @brief Tek bir kelimeyi çevirir
     * @param word Çevrilecek kelime
     * @return Çevrilmiş kelime
     */
    std::string translateWord(const std::string& word);
    
    /**
     * @brief Kelime öbeğini çevirir
     * @param phrase Çevrilecek kelime öbeği
     * @return Çevrilmiş kelime öbeği
     */
    std::string translatePhrase(const std::string& phrase);

    // Language management
    /**
     * @brief Kaynak dili ayarlar
     * @param language Kaynak dil
     */
    void setSourceLanguage(const std::string& language);
    
    /**
     * @brief Hedef dili ayarlar
     * @param language Hedef dil
     */
    void setTargetLanguage(const std::string& language);
    
    /**
     * @brief Desteklenen dilleri döndürür
     * @return Desteklenen diller listesi
     */
    std::vector<std::string> getSupportedLanguages() const;
    
    /**
     * @brief Dil seçim menüsünü gösterir
     */
    void showLanguageSelection();
    
    /**
     * @brief Yeni dil ekler
     * @param language Eklenecek dil
     */
    void addLanguage(const std::string& language);

    // User management
    /**
     * @brief Kullanıcı girişi yapar
     * @param username Kullanıcı adı
     * @param password Şifre
     * @return Giriş başarılı mı?
     */
    bool login(const std::string& username, const std::string& password);
    
    /**
     * @brief Yeni kullanıcı kaydı yapar
     * @param username Kullanıcı adı
     * @param password Şifre
     * @return Kayıt başarılı mı?
     */
    bool registerUser(const std::string& username, const std::string& password);
    
    /**
     * @brief Kullanıcı çıkışı yapar
     */
    void logout();
    
    /**
     * @brief Kullanıcı giriş yapmış mı kontrol eder
     * @return Giriş yapmış mı?
     */
    bool isUserLoggedIn() const;
    
    /**
     * @brief Mevcut kullanıcı adını döndürür
     * @return Kullanıcı adı
     */
    const std::string& currentUsername() const { return currentUser; }

    // Phrase library
    /**
     * @brief Kelime öbeği kütüphanesini gösterir
     */
    void showPhraseLibrary();
    
    /**
     * @brief Yeni kelime öbeği ekler
     * @param phrase Kelime öbeği
     * @param category Kategori
     */
    void addPhrase(const std::string& phrase, const std::string& category);

    // Learning tips
    /**
     * @brief Öğrenme ipuçlarını gösterir
     */
    void showLearningTips();
    
    /**
     * @brief Yeni öğrenme ipucu ekler
     * @param tip Öğrenme ipucu
     */
    void addLearningTip(const std::string& tip);

    // Pronunciation guide
    /**
     * @brief Telaffuz rehberini gösterir
     */
    void showPronunciationGuide();
    
    /**
     * @brief Yeni telaffuz rehberi ekler
     * @param word Kelime
     * @param guide Telaffuz rehberi
     */
    void addPronunciation(const std::string& word, const std::string& guide);

    // History
    /**
     * @brief Çeviri geçmişini gösterir
     */
    void showHistory() const;
    
    /**
     * @brief Çeviri geçmişini temizler
     */
    void clearHistory();

    // Data management
    /**
     * @brief Varsayılan verileri başlatır
     */
    void initializeDefaultData();
    
    /**
     * @brief Verileri kaydeder
     */
    void saveData();
    
    /**
     * @brief Verileri yükler
     */
    void loadData();

    // Dictionary management
    /**
     * @brief Dosyadan sözlük yükler
     * @param sourceLang Kaynak dil
     * @param targetLang Hedef dil
     * @param filename Dosya adı
     * @return Yükleme başarılı mı?
     */
    bool loadDictionaryFromFile(const std::string& sourceLang, const std::string& targetLang, const std::string& filename);
    
    /**
     * @brief Tüm sözlükleri yükler
     */
    void loadAllDictionaries();

    // API Translation
    /**
     * @brief Google API ile çeviri yapar
     * @param text Çevrilecek metin
     * @param sourceLang Kaynak dil
     * @param targetLang Hedef dil
     * @return Çevrilmiş metin
     */
    std::string translateWithGoogleAPI(const std::string& text, const std::string& sourceLang, const std::string& targetLang);
    
    /**
     * @brief Microsoft API ile çeviri yapar
     * @param text Çevrilecek metin
     * @param sourceLang Kaynak dil
     * @param targetLang Hedef dil
     * @return Çevrilmiş metin
     */
    std::string translateWithMicrosoftAPI(const std::string& text, const std::string& sourceLang, const std::string& targetLang);
    
    /**
     * @brief API kullanılabilir mi kontrol eder
     * @return API kullanılabilir mi?
     */
    bool isAPIAvailable();
    
    /**
     * @brief API anahtarını ayarlar
     * @param key API anahtarı
     */
    void setAPIKey(const std::string& key);
    
    /**
     * @brief API kullanım modunu ayarlar
     * @param useAPI API kullanılsın mı?
     */
    void setAPIMode(bool useAPI);
};

} // namespace LanguageTranslator
} // namespace Coruh

#endif // LANGUAGE_TRANSLATOR_H

