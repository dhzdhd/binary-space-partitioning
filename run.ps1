$Folder = 'build'
$Executable = 'build/bsp.exe'

if (Test-Path -Path $Folder) {
    Set-Location build;
}
else {
    mkdir build; Set-Location build;
}

cmake .. -G "MinGW Makefiles"
cmake --build .
Set-Location ..

if (Test-Path -Path $Executable) {
    ./build/bsp.exe
}
else {
    Write-Output "Check build folder for executable and run it"
}
