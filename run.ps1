$Folder = 'build'

if (Test-Path -Path $Folder) {
    Set-Location build;
}
else {
    mkdir build
    Set-Location build
}

cmake .. -G "MinGW Makefiles"
cmake --build .
Set-Location ..

$Executable = Get-ChildItem -Path bsp.exe -Recurse -File | ForEach-Object { $_.FullName }
& $Executable
