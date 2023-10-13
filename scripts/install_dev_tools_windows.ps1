# install scoop

Function Test-CommandExists
{
    Param ($command)
    $oldPreference = $ErrorActionPreference
    $ErrorActionPreference = "stop"
    try {
        if (Get-Command $command -ErrorAction SilentlyContinue) {
            return $true
        } else {
            return $false
        }
    } Catch {
        return $false
    } Finally {
        $ErrorActionPreference = $oldPreference
    }
}

if (Test-CommandExists scoop) {
    Write-Host "Scoop already installed"
} else {
    Write-Host "Scoop not found. Installing..."
    iwr -useb get.scoop.sh | iex
}

if (Test-CommandExists winget) {
    Write-Host "Winget already installed"
} else {
    Write-Host "You must install winget through the Microsoft Store to continue"
    exit 1
}

scoop install gcc
scoop install cmake
winget install LLVM
winget install Ninja-build.Ninja