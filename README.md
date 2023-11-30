# R-Type

This project involves building a game engine to recreate the game R-Type, and add networking features for online coop.

## How to use

Firstly you need to install vcpkg and set the VCPKG_ROOT environnement variable to the directory where you installed vcpkg. The steps
depends on your operating system.

- [vcpkg](https://vcpkg.io/en/getting-started)
- [Environnement variable on Windows](https://phoenixnap.com/kb/windows-set-environment-variable#:~:text=Follow%20the%20steps%20to%20set%20environment%20variables%20using,the%20New%20User%20Variable%20prompt%20and%20click%20OK.)
- [Environnement variable on Linux/Mac](https://phoenixnap.com/kb/linux-set-environment-variable#:~:text=Set%20an%20Environment%20Variable%20in%20Linux%20Permanently%201,file%20in%20the%20%2Fetc%2Fprofile.d%20folder%3A%20...%20%C3%89l%C3%A9ments%20suppl%C3%A9mentaires)

Once you installed vcpkg, in the root of the repository, do the command:

`vcpkg install`

*If vcpkg is not found, you might need to add the path to vcpkg to the PATH environnement*

Then you can do as follow:

```
mkdir build
cmake --preset=default -DCMAKE_BUILD_TYPE=Release -S . -B ./build/
cmake --build ./build/
```
