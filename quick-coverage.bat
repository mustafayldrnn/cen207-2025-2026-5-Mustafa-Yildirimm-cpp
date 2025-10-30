@echo off
echo Quick Coverage Update Script
echo ============================

cd /d "%~dp0"

rem Get the current directory path
for %%A in ("%~dp0.") do (
    set "currentDir=%%~fA"
)

echo Checking for built test executable...
if not exist "build_win\tests\Debug\unit_tests.exe" (
    echo ERROR: unit_tests.exe not found!
    echo Please run 7-build-app-windows.bat first to build the tests.
    pause
    exit /b 1
)

echo Found test executable. Running coverage...
echo.

rem Delete old coverage files
del /F /Q translator_tests_unit_win.cov translateapp_unit_win_cobertura.xml 2>nul

echo Generating coverage data...
OpenCppCoverage.exe --export_type=binary:translator_tests_unit_win.cov ^
    --sources "%currentDir%\src" ^
    --sources "%currentDir%\include" ^
    --excluded_sources "Program Files\\*" ^
    --excluded_sources "C:\\Windows\\*" ^
    --excluded_sources "*\\tests\\*" ^
    --excluded_sources "*\\build_win\\*" ^
    --excluded_sources "*\\gtest\\*" ^
    -- build_win\tests\Debug\unit_tests.exe

if errorlevel 1 (
    echo Coverage collection failed!
    pause
    exit /b 1
)

echo.
echo Converting to Cobertura XML...
OpenCppCoverage.exe --input_coverage=translator_tests_unit_win.cov ^
    --export_type=cobertura:translateapp_unit_win_cobertura.xml ^
    --sources "%currentDir%\src" ^
    --sources "%currentDir%\include" ^
    --excluded_sources "Program Files\\*" ^
    --excluded_sources "C:\\Windows\\*" ^
    --excluded_sources "*\\tests\\*" ^
    --excluded_sources "*\\build_win\\*" ^
    --excluded_sources "*\\gtest\\*" ^
    -- build_win\tests\Debug\unit_tests.exe

if errorlevel 1 (
    echo Cobertura export failed!
    pause
    exit /b 1
)

echo.
echo Generating coverage report...
call reportgenerator "-title:translate Library Unit Test Coverage Report (Windows)" ^
    "-targetdir:docs/coveragereportlibwin" ^
    "-reporttypes:Html" ^
    "-reports:**/translateapp_unit_win_cobertura.xml" ^
    "-sourcedirs:src;include" ^
    "-filefilters:+*src/LanguageTranslator/src/*;+*src/LanguageTranslator/header/*;+*src/SafeChronoCalculator.*;+*src/coverage_anchor/*;+*include/ds/*;-*\\tests\\*;-*build*;-*gtest*" ^
    "-historydir:report_test_hist_win"

echo.
echo Coverage report updated successfully!
echo Open: docs\coveragereportlibwin\index.html
echo.
pause

