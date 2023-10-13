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

cmake .. -DCMAKE_BUILD_TYPE=%buildType%
cmake --build . --config %buildType%

endlocal
