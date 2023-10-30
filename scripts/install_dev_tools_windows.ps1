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
    Invoke-Expression "& {$(Invoke-RestMethod get.scoop.sh)} -RunAsAdmin"
}

if (Test-CommandExists winget) {
    Write-Host "Winget already installed"
} else {
    Write-Host "You must install winget through the Microsoft Store to continue"
    exit 1
}

# Install packages
scoop bucket add main

if (Test-CommandExists gcc) {
    Write-Host "GCC already installed"
} else {
    Write-Host "Installing GCC..."
    scoop install gcc
}

if (Test-CommandExists cmake) {
    Write-Host "CMAKE already installed"
} else {
    Write-Host "Installing CMAKE..."
    scoop install cmake
}

if (Test-CommandExists ninja) {
    Write-Host "NINJA already installed"
} else {
    Write-Host "Installing NINJA..."
    scoop install ninja
}

Write-Host "The script will launch an install window for LLVM. When prompted, please select 'Add to Path' in the installer."
Write-Host "Press any key to continue..."
$null = $Host.UI.RawUI.ReadKey("NoEcho,IncludeKeyDown")

winget install LLVM -i --accept-source-agreements

# Reload path
$env:Path = [System.Environment]::GetEnvironmentVariable("Path","Machine") + ";" + [System.Environment]::GetEnvironmentVariable("Path","User")