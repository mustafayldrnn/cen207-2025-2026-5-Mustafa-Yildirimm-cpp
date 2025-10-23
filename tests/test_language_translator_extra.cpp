// Ek kapsama: LanguageTranslatorApp için kayıt, sözlük yükleme ve çeşitli yollar

#include <gtest/gtest.h>
#include <fstream>
#include <string>
#include "../src/LanguageTranslator/header/LanguageTranslator.h"

using namespace Coruh::LanguageTranslator;

TEST(LanguageTranslatorExtra, RegisterExistingUserFails){
    LanguageTranslatorApp app;
    // 'admin' zaten rezervli kabul ediliyor
    EXPECT_FALSE(app.registerUser("admin", "anything"));
}

TEST(LanguageTranslatorExtra, LoadDictionaryFromRealFile){
    LanguageTranslatorApp app;
    app.setSourceLanguage("English");
    app.setTargetLanguage("Turkish");

    // Geçici sözlük dosyası oluştur
    const std::string fname = "temp_en_tr_dict_test.txt";
    {
        std::ofstream ofs(fname, std::ios::trunc);
        ASSERT_TRUE(ofs.good());
        ofs << "bye:gule\n";
        ofs << "# comment line\n";
        ofs << "  space : bosluk  \n"; // trim testi
    }

    // Yükle ve doğrula
    ASSERT_TRUE(app.loadDictionaryFromFile("English", "Turkish", fname));
    EXPECT_EQ(app.translateWord("bye"), "gule");
    // Trim edilmiş anahtar/değerler de yüklenmiş olmalı
    EXPECT_EQ(app.translateWord("space"), "bosluk");
}

TEST(LanguageTranslatorExtra, AddLanguageNoDuplicate){
    LanguageTranslatorApp app;
    auto before = app.getSupportedLanguages();
    app.addLanguage("Klingon");
    auto afterAdd = app.getSupportedLanguages();
    EXPECT_GE(afterAdd.size(), before.size() + 1);
    // Aynı dili tekrar ekleme — boyut değişmemeli
    app.addLanguage("Klingon");
    auto afterDup = app.getSupportedLanguages();
    EXPECT_EQ(afterDup.size(), afterAdd.size());
}

