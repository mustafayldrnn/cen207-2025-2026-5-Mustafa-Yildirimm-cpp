@echo off
setlocal enableextensions enabledelayedexpansion
cd /d "%~dp0"

REM --- Build klasörü ve örnek giriş dosyası ---
set "BUILD_DIR=%~dp0build"
if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%" >nul 2>&1

if not exist "%BUILD_DIR%\program.bas" (
  echo 10 LET X = 1 + 2>"%BUILD_DIR%\program.bas"
  echo 20 PRINT X>>"%BUILD_DIR%\program.bas"
  echo [INFO] %BUILD_DIR%\program.bas olusturuldu.
)

REM --- translator.exe yolunu bul ---
set "EXE="
if exist "%BUILD_DIR%\Debug\translator.exe" set "EXE=%BUILD_DIR%\Debug\translator.exe"
if "%EXE%"=="" if exist "%BUILD_DIR%\Release\translator.exe" set "EXE=%BUILD_DIR%\Release\translator.exe"
if "%EXE%"=="" if exist "%~dp0build_win\Debug\translator.exe" set "EXE=%~dp0build_win\Debug\translator.exe"
if "%EXE%"=="" if exist "%~dp0build_win\Release\translator.exe" set "EXE=%~dp0build_win\Release\translator.exe"

REM --- Gerekirse CMake ile derle (testleri kapat) ---
if "%EXE%"=="" (
  echo [INFO] translator.exe bulunamadi. CMake ile derleniyor...
  cmake -S . -B "%BUILD_DIR" -G "Visual Studio 17 2022" -DTRANSLATOR_ENABLE_TESTS=OFF
  if errorlevel 1 goto :fail
  cmake --build "%BUILD_DIR%" --config Debug -j4 --target translator
  if errorlevel 1 goto :fail
  if exist "%BUILD_DIR%\Debug\translator.exe" (
    set "EXE=%BUILD_DIR%\Debug\translator.exe"
  ) else if exist "%BUILD_DIR%\Release\translator.exe" (
    set "EXE=%BUILD_DIR%\Release\translator.exe"
  )
)

if "%EXE%"=="" (
  echo [ERROR] translator.exe bulunamadi. Derleme basarisiz.
  goto :fail
)

echo [INFO] Kullanilacak exe: "%EXE%"
set "INPUT=%BUILD_DIR%\program.bas"
set "OUTPUT=%BUILD_DIR%\cikti.cpp"

"%EXE%" "%INPUT%" -o "%OUTPUT%"
if errorlevel 1 goto :fail

echo [OK] Cikti olusturuldu: "%OUTPUT%"
exit /b 0

:fail
echo [FAIL] Islem sirasinda hata olustu.
exit /b 1

