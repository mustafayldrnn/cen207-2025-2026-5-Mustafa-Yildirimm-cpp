/**
 * @file Persistence.h
 * @brief LanguageTranslator verileri için ikili (binary) kalıcılık yardımcıları.
 */

#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace Coruh {
namespace LanguageTranslator {

/** @brief Kullanıcı profili bilgileri. */
struct UserProfile {
    std::string username;
    std::string salt;
    std::string passwordHash; // hex sha256
    std::string preferredSource;
    std::string preferredTarget;
};

/** @brief Çeviri geçmişi kaydı. */
struct TranslationRecord {
    std::string sourceLang;
    std::string targetLang;
    std::string text;
    std::string result;
    std::uint64_t timestamp; // unix seconds
};

/** @brief Öğrenme ipucu girdisi. */
struct TipEntry { std::string tip; };
/** @brief Genel ifade girdisi. */
struct PhraseEntry { std::string phrase; std::string category; };
/** @brief Telaffuz girdisi. */
struct PronunciationEntry { std::string word; std::string ipa; std::string audioPath; };

namespace Persistence {
    // Generic binary vector read/write of simple string-based records
    /** @brief Kullanıcı listesini ikili dosyaya yazar. */
    bool writeUsers(const std::string& path, const std::vector<UserProfile>& data);
    /** @brief Kullanıcı listesini ikili dosyadan okur. */
    bool readUsers(const std::string& path, std::vector<UserProfile>& out);

    /** @brief Çeviri geçmişini yazar. */
    bool writeHistory(const std::string& path, const std::vector<TranslationRecord>& data);
    /** @brief Çeviri geçmişini okur. */
    bool readHistory(const std::string& path, std::vector<TranslationRecord>& out);

    bool writeTips(const std::string& path, const std::vector<TipEntry>& data);
    bool readTips(const std::string& path, std::vector<TipEntry>& out);

    bool writePhrases(const std::string& path, const std::vector<PhraseEntry>& data);
    bool readPhrases(const std::string& path, std::vector<PhraseEntry>& out);

    bool writePronunciations(const std::string& path, const std::vector<PronunciationEntry>& data);
    bool readPronunciations(const std::string& path, std::vector<PronunciationEntry>& out);

    // Utils
    /** @brief Girdi için hex SHA-256 (ders amaçlı pseudo) döndürür. */
    std::string sha256Hex(const std::string& input);
    /** @brief Rastgele salt üretir. */
    std::string randomSalt(std::size_t len = 16);
}

} // namespace LanguageTranslator
} // namespace Coruh
