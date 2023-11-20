include(FetchContent)

FetchContent_Declare(
    nfd
    GIT_REPOSITORY "https://github.com/btzy/nativefiledialog-extended.git"
    GIT_TAG v1.1.0
)

FetchContent_MakeAvailable(nfd)