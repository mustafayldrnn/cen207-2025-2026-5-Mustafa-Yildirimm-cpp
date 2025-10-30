@echo off
echo Building ONLY unit tests...
echo =============================

cd /d "%~dp0"

rem Get the current directory path
for %%A in ("%~dp0.") do (
    set "currentDir=%%~fA"
)

rem Delete build_win to force clean configuration
if exist "build_win" (
    echo Cleaning old build directory...
    rd /S /Q build_win
)

echo Configuring CMake...
call cmake -B build_win -DCMAKE_BUILD_TYPE=Debug -G "Visual Studio 17 2022" -DCMAKE_INSTALL_PREFIX:PATH=publish_win

if errorlevel 1 (
    echo CMake configuration failed!
    pause
    exit /b 1
)

echo Building unit_tests...
call cmake --build build_win --config Debug --target unit_tests -j4

if errorlevel 1 (
    echo Build failed!
    pause
    exit /b 1
)

echo.
echo Test executable built successfully!
echo Location: build_win\tests\Debug\unit_tests.exe
echo.
echo Now you can run quick-coverage.bat to generate the coverage report.
pause

