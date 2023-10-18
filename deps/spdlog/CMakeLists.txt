include(FetchContent)

set(SPDLOG_BUILD_SHARED OFF)

FetchContent_Declare(
    spdlog
    GIT_REPOSITORY "https://github.com/gabime/spdlog.git"
    GIT_TAG v1.12.0
)

FetchContent_MakeAvailable(spdlog)