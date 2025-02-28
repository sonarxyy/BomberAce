@echo off
setlocal

set "SOURCE_DIR=%~dp0"
set "BUILD_DIR=build"

echo Starting build process...

if not exist "%BUILD_DIR%" mkdir "%BUILD_DIR%"
cd "%BUILD_DIR%"

cmake -G "Ninja" "%SOURCE_DIR%"
if %errorlevel% equ 0 (
    ninja
) else (
    echo CMake configuration failed.
)

echo.
echo Build process finished.
pause

endlocal