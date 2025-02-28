@echo off
setlocal

echo Installing CMake and Ninja...

:: Define installation paths (adjust as needed)
set "INSTALL_DIR=%USERPROFILE%\Downloads\Tools"
set "CMAKE_INSTALL_DIR=%INSTALL_DIR%\CMake"
set "NINJA_INSTALL_DIR=%INSTALL_DIR%\Ninja"

:: CMake Download URL (find the latest release from cmake.org/download)
set "CMAKE_DOWNLOAD_URL=https://github.com/Kitware/CMake/releases/download/v3.31.6/cmake-3.31.6-windows-x86_64.zip"

:: Ninja Download URL (find the latest release from github.com/ninja-build/ninja/releases)
set "NINJA_DOWNLOAD_URL=https://github.com/ninja-build/ninja/releases/download/v1.12.1/ninja-win.zip"

:: Temporary download locations
set "CMAKE_ZIP=%TEMP%\cmake.zip"
set "NINJA_ZIP=%TEMP%\ninja.zip"

:: Create Tools Directory
if not exist "%INSTALL_DIR%" mkdir "%INSTALL_DIR%"

:: Download CMake
echo Downloading CMake...
curl -L -o "%CMAKE_ZIP%" "%CMAKE_DOWNLOAD_URL%"
if errorlevel 1 goto error

:: Create CMake install directory
if not exist "%CMAKE_INSTALL_DIR%" mkdir "%CMAKE_INSTALL_DIR%"

:: Check if CMake install directory is empty before extracting.
echo Checking if CMake install directory is empty...
for /f "delims=" %%a in ('dir /b "%CMAKE_INSTALL_DIR%"') do (
    echo CMake install directory is not empty. Skipping CMake extraction.
    goto ninja_download
)

:: Extract CMake
echo Extracting CMake...
powershell -Command "Expand-Archive -Path '%CMAKE_ZIP%' -DestinationPath '%CMAKE_INSTALL_DIR%'"
if errorlevel 1 goto error

:ninja_download
:: Download Ninja
echo Downloading Ninja...
curl -L -o "%NINJA_ZIP%" "%NINJA_DOWNLOAD_URL%"
if errorlevel 1 goto error

:: Create Ninja install directory
if not exist "%NINJA_INSTALL_DIR%" mkdir "%NINJA_INSTALL_DIR%"

:: Check if Ninja install directory is empty before extracting.
echo Checking if Ninja install directory is empty...
for /f "delims=" %%a in ('dir /b "%NINJA_INSTALL_DIR%"') do (
    echo Ninja install directory is not empty. Skipping Ninja extraction.
    goto path_add
)

:: Extract Ninja
echo Extracting Ninja...
powershell -Command "Expand-Archive -Path '%NINJA_ZIP%' -DestinationPath '%NINJA_INSTALL_DIR%'"
if errorlevel 1 goto error

:path_add
:: Add CMake and Ninja to PATH
echo Adding CMake and Ninja to PATH...
setx PATH "%PATH%;%CMAKE_INSTALL_DIR%\bin;%NINJA_INSTALL_DIR%" /M
if errorlevel 1 goto error

:: Clean up temporary files
echo Cleaning up temporary files...
del "%CMAKE_ZIP%"
del "%NINJA_ZIP%"

echo CMake and Ninja installation process completed.

:: Run build.bat
set "SOURCE_DIR=%~dp0"
echo.
echo Launching build process...
start "Build Process" /D "%SOURCE_DIR%" cmd /c "build.bat"

goto end

:error
echo Error occurred during installation.
pause

:end
endlocal