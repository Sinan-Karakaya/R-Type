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

scoop bucket add main
scoop install gcc
scoop install cmake
scoop install ninja
winget install LLVM --disable-interactivity --accept-source-agreements

# Reload path
$env:Path = [System.Environment]::GetEnvironmentVariable("Path","Machine") + ";" + [System.Environment]::GetEnvironmentVariable("Path","User") 