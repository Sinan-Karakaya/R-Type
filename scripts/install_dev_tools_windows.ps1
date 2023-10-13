# install scoop

if (Get-Command scoop) {
    Write-Host "Scoop already installed"
} else {
    Write-Host "Scoop not found. Installing..."
    iwr -useb get.scoop.sh | iex
}

if (Get-Command winget) {
    Write-Host "Winget already installed"
} else {
    Write-Host "You must install winget through the Microsoft Store to continue"
    exit 1
}

scoop install gcc
scoop install cmake
winget install LLVM
winget install Ninja-build.Ninja