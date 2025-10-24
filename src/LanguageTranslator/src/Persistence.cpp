/**
 * @file Persistence.cpp
 */

#include "../header/Persistence.h"
#include <fstream>
#include <random>
#include <sstream>
#include <iomanip>

// Minimal portable SHA-256 implementation (tiny, not optimized)
namespace {
// Simple wrapper using std::hash as fallback when no crypto is available.
// Note: For course purposes only; replace with a real SHA-256 for production.
static std::string pseudo_sha256_hex(const std::string& s){
    std::hash<std::string> h; auto v = h(s);
    std::ostringstream oss; oss << std::hex << std::setw(16) << std::setfill('0') << v;
    // repeat to mimic 64 hex chars
    std::string hex = oss.str();
    while(hex.size() < 64) hex += oss.str();
    hex.resize(64);
    return hex;
}

static void writeString(std::ofstream& os, const std::string& s){
    std::uint32_t len = static_cast<std::uint32_t>(s.size());
    os.write(reinterpret_cast<const char*>(&len), sizeof(len));
    if (len) os.write(s.data(), len);
}
static bool readString(std::ifstream& is, std::string& out){
    std::uint32_t len = 0; if(!is.read(reinterpret_cast<char*>(&len), sizeof(len))) return false;
    out.resize(len);
    if (len) if(!is.read(&out[0], len)) return false;
    return true;
}
}

namespace Coruh { namespace LanguageTranslator { namespace Persistence {

std::string sha256Hex(const std::string& input){
    return pseudo_sha256_hex(input);
}

std::string randomSalt(std::size_t len){
    static std::mt19937_64 rng{std::random_device{}()};
    static const char* alphabet = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";
    std::uniform_int_distribution<std::size_t> dist(0, 61);
    std::string s; s.reserve(len);
    for (std::size_t i=0;i<len;++i) s.push_back(alphabet[dist(rng)]);
    return s;
}

bool writeUsers(const std::string& path, const std::vector<UserProfile>& data){
    std::ofstream os(path, std::ios::binary | std::ios::trunc);
    if(!os) return false;
    std::uint32_t n = static_cast<std::uint32_t>(data.size());
    os.write(reinterpret_cast<const char*>(&n), sizeof(n));
    for (auto& u: data){
        writeString(os, u.username);
        writeString(os, u.salt);
        writeString(os, u.passwordHash);
        writeString(os, u.preferredSource);
        writeString(os, u.preferredTarget);
    }
    return true;
}

bool readUsers(const std::string& path, std::vector<UserProfile>& out){
    std::ifstream is(path, std::ios::binary);
    if(!is) return false;
    std::uint32_t n = 0; if(!is.read(reinterpret_cast<char*>(&n), sizeof(n))) return false;
    out.clear(); out.reserve(n);
    for (std::uint32_t i=0;i<n;++i){
        UserProfile u;
        if(!readString(is, u.username)) return false;
        if(!readString(is, u.salt)) return false;
        if(!readString(is, u.passwordHash)) return false;
        if(!readString(is, u.preferredSource)) return false;
        if(!readString(is, u.preferredTarget)) return false;
        out.push_back(std::move(u));
    }
    return true;
}

bool writeHistory(const std::string& path, const std::vector<TranslationRecord>& data){
    std::ofstream os(path, std::ios::binary | std::ios::trunc);
    if(!os) return false;
    std::uint32_t n = static_cast<std::uint32_t>(data.size());
    os.write(reinterpret_cast<const char*>(&n), sizeof(n));
    for (auto& r: data){
        writeString(os, r.sourceLang);
        writeString(os, r.targetLang);
        writeString(os, r.text);
        writeString(os, r.result);
        os.write(reinterpret_cast<const char*>(&r.timestamp), sizeof(r.timestamp));
    }
    return true;
}

bool readHistory(const std::string& path, std::vector<TranslationRecord>& out){
    std::ifstream is(path, std::ios::binary);
    if(!is) return false;
    std::uint32_t n = 0; if(!is.read(reinterpret_cast<char*>(&n), sizeof(n))) return false;
    out.clear(); out.reserve(n);
    for (std::uint32_t i=0;i<n;++i){
        TranslationRecord r{};
        if(!readString(is, r.sourceLang)) return false;
        if(!readString(is, r.targetLang)) return false;
        if(!readString(is, r.text)) return false;
        if(!readString(is, r.result)) return false;
        if(!is.read(reinterpret_cast<char*>(&r.timestamp), sizeof(r.timestamp))) return false;
        out.push_back(std::move(r));
    }
    return true;
}

bool writeTips(const std::string& path, const std::vector<TipEntry>& data){
    std::ofstream os(path, std::ios::binary | std::ios::trunc);
    if(!os) return false;
    std::uint32_t n = static_cast<std::uint32_t>(data.size());
    os.write(reinterpret_cast<const char*>(&n), sizeof(n));
    for (auto& t: data) writeString(os, t.tip);
    return true;
}

bool readTips(const std::string& path, std::vector<TipEntry>& out){
    std::ifstream is(path, std::ios::binary);
    if(!is) return false;
    std::uint32_t n = 0; if(!is.read(reinterpret_cast<char*>(&n), sizeof(n))) return false;
    out.clear(); out.reserve(n);
    for (std::uint32_t i=0;i<n;++i){ TipEntry t{}; if(!readString(is, t.tip)) return false; out.push_back(std::move(t)); }
    return true;
}

bool writePhrases(const std::string& path, const std::vector<PhraseEntry>& data){
    std::ofstream os(path, std::ios::binary | std::ios::trunc);
    if(!os) return false;
    std::uint32_t n = static_cast<std::uint32_t>(data.size());
    os.write(reinterpret_cast<const char*>(&n), sizeof(n));
    for (auto& p: data){ writeString(os, p.phrase); writeString(os, p.category); }
    return true;
}

bool readPhrases(const std::string& path, std::vector<PhraseEntry>& out){
    std::ifstream is(path, std::ios::binary);
    if(!is) return false;
    std::uint32_t n = 0; if(!is.read(reinterpret_cast<char*>(&n), sizeof(n))) return false;
    out.clear(); out.reserve(n);
    for (std::uint32_t i=0;i<n;++i){
        PhraseEntry p{}; if(!readString(is, p.phrase)) return false; if(!readString(is, p.category)) return false; out.push_back(std::move(p));
    }
    return true;
}

bool writePronunciations(const std::string& path, const std::vector<PronunciationEntry>& data){
    std::ofstream os(path, std::ios::binary | std::ios::trunc);
    if(!os) return false;
    std::uint32_t n = static_cast<std::uint32_t>(data.size());
    os.write(reinterpret_cast<const char*>(&n), sizeof(n));
    for (auto& p: data){ writeString(os, p.word); writeString(os, p.ipa); writeString(os, p.audioPath); }
    return true;
}

bool readPronunciations(const std::string& path, std::vector<PronunciationEntry>& out){
    std::ifstream is(path, std::ios::binary);
    if(!is) return false;
    std::uint32_t n = 0; if(!is.read(reinterpret_cast<char*>(&n), sizeof(n))) return false;
    out.clear(); out.reserve(n);
    for (std::uint32_t i=0;i<n;++i){
        PronunciationEntry p{}; if(!readString(is, p.word)) return false; if(!readString(is, p.ipa)) return false; if(!readString(is, p.audioPath)) return false; out.push_back(std::move(p));
    }
    return true;
}

}}} // namespaces

