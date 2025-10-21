#!/usr/bin/env bash
set -euo pipefail

# Git Bash / WSL uyumlu örnek çalıştırma betiği
# - build/program.bas yoksa oluşturur
# - translator.exe'yi bulur, yoksa CMake ile derler
# - build/cikti.cpp çıktısını üretir

ROOT_DIR="$(cd "$(dirname "$0")" && pwd)"
BUILD_DIR="$ROOT_DIR/build"
INPUT="$BUILD_DIR/program.bas"
OUTPUT="$BUILD_DIR/cikti.cpp"

mkdir -p "$BUILD_DIR"

if [[ ! -f "$INPUT" ]]; then
  printf '10 LET X = 1 + 2\n20 PRINT X\n' > "$INPUT"
  echo "[INFO] $INPUT olusturuldu."
fi

# translator.exe'yi ara
EXE=""
for p in \
  "$BUILD_DIR/Debug/translator.exe" \
  "$BUILD_DIR/Release/translator.exe" \
  "$ROOT_DIR/build_win/Debug/translator.exe" \
  "$ROOT_DIR/build_win/Release/translator.exe"; do
  [[ -f "$p" ]] && EXE="$p" && break
done

# Yoksa CMake ile derle (VS 2022)
if [[ -z "$EXE" ]]; then
  echo "[INFO] translator.exe yok. CMake ile derleniyor..."
  cmake -S "$ROOT_DIR" -B "$BUILD_DIR" -G "Visual Studio 17 2022" -DTRANSLATOR_ENABLE_TESTS=OFF
  cmake --build "$BUILD_DIR" --config Debug -j4 --target translator
  if [[ -f "$BUILD_DIR/Debug/translator.exe" ]]; then
    EXE="$BUILD_DIR/Debug/translator.exe"
  elif [[ -f "$BUILD_DIR/Release/translator.exe" ]]; then
    EXE="$BUILD_DIR/Release/translator.exe"
  fi
fi

if [[ -z "$EXE" ]]; then
  echo "[ERROR] translator.exe bulunamadi. Derleme basarisiz." >&2
  exit 1
fi

# Windows yollarina cevir (Git Bash/MinGW icin guvenli)
EXE_WIN=$(cygpath -w "$EXE")
INPUT_WIN=$(cygpath -w "$INPUT")
OUTPUT_WIN=$(cygpath -w "$OUTPUT")

echo "[INFO] Kullanilacak exe: $EXE_WIN"
cmd.exe /c "\"$EXE_WIN\" \"$INPUT_WIN\" -o \"$OUTPUT_WIN\""
echo "[OK] Cikti olusturuldu: $OUTPUT"

