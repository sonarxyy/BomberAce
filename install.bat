@echo off
setlocal

echo Installing CMake and Ninja...

:: Ask user for CMake installation
echo I recommend you choosing Y if you haven't installed CMake.
choice /M "Do you want to download and install CMake? (Y/N)"
if errorlevel 2 goto ninja_ask

:: Define CMake installation path (adjust as needed)
set "INSTALL_DIR=%USERPROFILE%\Downloads\Tools"
set "CMAKE_INSTALL_DIR=%INSTALL_DIR%\CMake"

:: CMake Download URL (find the latest release from cmake.org/download)
set "CMAKE_DOWNLOAD_URL=https://github.com/Kitware/CMake/releases/download/v3.31.6/cmake-3.31.6-windows-x86_64.zip"

:: Temporary download location
set "CMAKE_ZIP=%TEMP%\cmake.zip"

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
    goto ninja_ask
)

:: Extract CMake
echo Extracting CMake...
powershell -Command "Expand-Archive -Path '%CMAKE_ZIP%' -DestinationPath '%CMAKE_INSTALL_DIR%'"
if errorlevel 1 goto error

:ninja_ask
:: Ask user for Ninja installation
echo I recommend you choosing Y if you haven't installed Ninja.
choice /M "Do you want to download and install Ninja? (Y/N)"
if errorlevel 2 goto path_add

:: Define Ninja installation path (adjust as needed)
set "NINJA_INSTALL_DIR=%INSTALL_DIR%\Ninja"

:: Ninja Download URL (find the latest release from github.com/ninja-build/ninja/releases)
set "NINJA_DOWNLOAD_URL=https://github.com/ninja-build/ninja/releases/download/v1.12.1/ninja-win.zip"

:: Temporary download location
set "NINJA_ZIP=%TEMP%\ninja.zip"

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
:: Add CMake and Ninja to USER PATH using .NET
echo Adding CMake and Ninja to USER PATH...

set "CMAKE_BIN_PATH=%CMAKE_INSTALL_DIR%\cmake-3.31.6-windows-x86_64\bin"
set "NINJA_PATH=%NINJA_INSTALL_DIR%"

powershell -Command ^
    "$Path = [Environment]::GetEnvironmentVariable('PATH', 'User');" ^
    "if ('%CMAKE_BIN_PATH%' -ne '') { if ($Path -notlike '*%CMAKE_BIN_PATH%*') { $Path += [IO.Path]::PathSeparator + '%CMAKE_BIN_PATH%'; }; };" ^
    "if ('%NINJA_PATH%' -ne '') { if ($Path -notlike '*%NINJA_PATH%*') { $Path += [IO.Path]::PathSeparator + '%NINJA_PATH%'; }; };" ^
    "[Environment]::SetEnvironmentVariable('PATH', $Path, 'User');"

if errorlevel 1 goto error

:: Clean up temporary files
echo Cleaning up temporary files...
if exist "%CMAKE_ZIP%" del "%CMAKE_ZIP%"
if exist "%NINJA_ZIP%" del "%NINJA_ZIP%"

echo CMake and Ninja installation process completed, please run the build.bat to build the game.
pause

:end
endlocal