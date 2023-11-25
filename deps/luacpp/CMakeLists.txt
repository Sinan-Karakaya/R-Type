include(FetchContent)

FetchContent_Declare(
    luacpp
    GIT_REPOSITORY "https://github.com/jordanvrtanoski/luacpp.git"
    GIT_TAG "v0.2.0"
    SOURCE_SUBDIR Source
)

FetchContent_MakeAvailable(luacpp)