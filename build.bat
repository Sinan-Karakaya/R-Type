@echo off
setlocal

set "isDebug=%~1"
set "isCI=%~2"

if "%isDebug%"=="debug" (
    echo Debug build
    set "buildType=Debug"
) else (
    echo Release build
    set "buildType=Release"
)

if not exist build mkdir build
cd build

if ("%isCI%"=="ci") (
    cmake .. -DCMAKE_BUILD_TYPE=%buildType%
    cmake --build . --config %buildType%
) else (
    cmake -G Ninja .. -DCMAKE_BUILD_TYPE=%buildType%
    ninja
)

endlocal
