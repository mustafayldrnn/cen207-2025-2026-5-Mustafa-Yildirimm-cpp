/**
 * @file Persistence.h
 * @brief LanguageTranslator verileri için ikili (binary) kalıcılık yardımcıları
 * @author Mustafa Yıldırım
 * @date 2025
 * @version 1.0
 */

#pragma once

#include <string>
#include <vector>
#include <cstdint>

namespace Coruh {
namespace LanguageTranslator {

/**
 * @brief Kullanıcı profili bilgileri
 * 
 * Bu yapı, kullanıcı kimlik doğrulama ve tercih bilgilerini saklar.
 * Güvenlik için şifre hash'i ve salt değeri içerir.
 */
struct UserProfile {
    std::string username;        ///< Kullanıcı adı
    std::string salt;           ///< Şifre hash'i için salt değeri
    std::string passwordHash;   ///< SHA-256 hex hash'i
    std::string preferredSource; ///< Tercih edilen kaynak dil
    std::string preferredTarget; ///< Tercih edilen hedef dil
};

/**
 * @brief Çeviri geçmişi kaydı
 * 
 * Bu yapı, yapılan çevirilerin geçmişini saklar.
 * Zaman damgası ile birlikte kaynak ve hedef dil bilgilerini içerir.
 */
struct TranslationRecord {
    std::string sourceLang;     ///< Kaynak dil
    std::string targetLang;     ///< Hedef dil
    std::string text;           ///< Çevrilen metin
    std::string result;         ///< Çeviri sonucu
    std::uint64_t timestamp;    ///< Unix zaman damgası (saniye)
};

/**
 * @brief Öğrenme ipucu girdisi
 * 
 * Bu yapı, kullanıcılara sunulan öğrenme ipuçlarını saklar.
 */
struct TipEntry { 
    std::string tip;  ///< Öğrenme ipucu metni
};

/**
 * @brief Genel ifade girdisi
 * 
 * Bu yapı, yaygın kullanılan kelime öbeklerini kategorileriyle birlikte saklar.
 */
struct PhraseEntry { 
    std::string phrase;    ///< Kelime öbeği
    std::string category;  ///< Kategori
};

/**
 * @brief Telaffuz girdisi
 * 
 * Bu yapı, kelimelerin telaffuz bilgilerini saklar.
 * IPA (International Phonetic Alphabet) ve ses dosyası yolu içerir.
 */
struct PronunciationEntry { 
    std::string word;      ///< Kelime
    std::string ipa;       ///< IPA telaffuz gösterimi
    std::string audioPath; ///< Ses dosyası yolu
};

/**
 * @namespace Persistence
 * @brief Veri kalıcılığı işlemleri için yardımcı fonksiyonlar
 * 
 * Bu namespace, uygulama verilerinin ikili dosya formatında
 * kaydedilmesi ve yüklenmesi için gerekli fonksiyonları sağlar.
 */
namespace Persistence {
    // Generic binary vector read/write of simple string-based records
    
    /**
     * @brief Kullanıcı listesini ikili dosyaya yazar
     * @param path Dosya yolu
     * @param data Yazılacak kullanıcı listesi
     * @return Yazma işlemi başarılı mı?
     */
    bool writeUsers(const std::string& path, const std::vector<UserProfile>& data);
    
    /**
     * @brief Kullanıcı listesini ikili dosyadan okur
     * @param path Dosya yolu
     * @param out Okunan verilerin yazılacağı vektör
     * @return Okuma işlemi başarılı mı?
     */
    bool readUsers(const std::string& path, std::vector<UserProfile>& out);

    /**
     * @brief Çeviri geçmişini ikili dosyaya yazar
     * @param path Dosya yolu
     * @param data Yazılacak çeviri geçmişi
     * @return Yazma işlemi başarılı mı?
     */
    bool writeHistory(const std::string& path, const std::vector<TranslationRecord>& data);
    
    /**
     * @brief Çeviri geçmişini ikili dosyadan okur
     * @param path Dosya yolu
     * @param out Okunan verilerin yazılacağı vektör
     * @return Okuma işlemi başarılı mı?
     */
    bool readHistory(const std::string& path, std::vector<TranslationRecord>& out);

    /**
     * @brief Öğrenme ipuçlarını ikili dosyaya yazar
     * @param path Dosya yolu
     * @param data Yazılacak ipuçları listesi
     * @return Yazma işlemi başarılı mı?
     */
    bool writeTips(const std::string& path, const std::vector<TipEntry>& data);
    
    /**
     * @brief Öğrenme ipuçlarını ikili dosyadan okur
     * @param path Dosya yolu
     * @param out Okunan verilerin yazılacağı vektör
     * @return Okuma işlemi başarılı mı?
     */
    bool readTips(const std::string& path, std::vector<TipEntry>& out);

    /**
     * @brief Kelime öbeklerini ikili dosyaya yazar
     * @param path Dosya yolu
     * @param data Yazılacak kelime öbekleri listesi
     * @return Yazma işlemi başarılı mı?
     */
    bool writePhrases(const std::string& path, const std::vector<PhraseEntry>& data);
    
    /**
     * @brief Kelime öbeklerini ikili dosyadan okur
     * @param path Dosya yolu
     * @param out Okunan verilerin yazılacağı vektör
     * @return Okuma işlemi başarılı mı?
     */
    bool readPhrases(const std::string& path, std::vector<PhraseEntry>& out);

    /**
     * @brief Telaffuz rehberini ikili dosyaya yazar
     * @param path Dosya yolu
     * @param data Yazılacak telaffuz rehberi
     * @return Yazma işlemi başarılı mı?
     */
    bool writePronunciations(const std::string& path, const std::vector<PronunciationEntry>& data);
    
    /**
     * @brief Telaffuz rehberini ikili dosyadan okur
     * @param path Dosya yolu
     * @param out Okunan verilerin yazılacağı vektör
     * @return Okuma işlemi başarılı mı?
     */
    bool readPronunciations(const std::string& path, std::vector<PronunciationEntry>& out);

    // Utils
    /**
     * @brief Girdi için hex SHA-256 (ders amaçlı pseudo) döndürür
     * @param input Hash'lenecek girdi
     * @return SHA-256 hex string'i
     * 
     * Bu fonksiyon, eğitim amaçlı basitleştirilmiş bir hash fonksiyonudur.
     * Gerçek uygulamalarda güvenli hash kütüphaneleri kullanılmalıdır.
     */
    std::string sha256Hex(const std::string& input);
    
    /**
     * @brief Rastgele salt üretir
     * @param len Salt uzunluğu (varsayılan: 16)
     * @return Rastgele salt string'i
     * 
     * Bu fonksiyon, şifre hash'leme için güvenli salt değeri üretir.
     */
    std::string randomSalt(std::size_t len = 16);
}

} // namespace LanguageTranslator
} // namespace Coruh
