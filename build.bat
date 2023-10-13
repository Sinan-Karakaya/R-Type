@echo off
setlocal

set "isDebug=%~1"

if "%isDebug%"=="debug" (
    echo Debug build
    set "buildType=Debug"
) else (
    echo Release build
    set "buildType=Release"
)

if not exist build mkdir build
cd build

cmake -G Ninja .. -DCMAKE_BUILD_TYPE=%buildType%
ninja

endlocal
