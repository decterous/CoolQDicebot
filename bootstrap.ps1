$config_type = $args[0]

$start_location = Resolve-Path .

if ($null -eq $config_type) {
    Write-Warning "No configuration specified, using Debug as default, if you want release, use `"bootstrap.ps1 Release`" instead."
    $config_type = "Debug"
}
else{
    Write-Host "Building configuration $config_type"
}

If (-not (Test-Path ".\CMakeLists.txt")) {
    Write-Warning "CMakeList.txt not found."
    exit
}

try {
    "cmake --version" | Out-Null
}
catch {
    Write-Warning "CMake not found!"
    exit
}

$VCPKG_RT = ${env:VCPKG_ROOT}
if ($null -eq $VCPKG_RT) {
    Write-Warning "Could not find VCPKG_ROOT. Please set up vcpkg environment."
    exit
}

try {
    "$VCPKG_RT\vcpkg" | Out-Null
}
catch {
    Write-Warning "Invalid VCPKG_ROOT. Please check vcpkg environment."
    exit
}

Write-Host "VCPKG_ROOT at $VCPKG_RT." -ForegroundColor Green

$target_triplet = "x86-windows-static"

function Test-And-Install-Packages {
    param (
        $_module_name
    )
    $_start_loc = Resolve-Path .
    Set-Location $VCPKG_RT
    $_val = (& .\vcpkg list $_module_name)
    Write-Host "Checking $_module_name"
    if ($null -eq $_val -or $_val -match 'No packages are installed') {

        Write-Host "run .\vcpkg install $_module_name --triplet $target_triplet"

        (& .\vcpkg install $_module_name --triplet $target_triplet)

        $_val = (& .\vcpkg list $_module_name)
        if ($null -eq $_val -or $_val -match 'No packages are installed') {
            Write-Warning "$_val is not installed"
            Set-Location $_start_loc
            return $false
        }
    }

    $_module_good = $false
    $_val | ForEach-Object {
        $_module_good = ($_.SubString($_.IndexOf(":")+1,$_.IndexOf(" "))  -match $target_triplet)
    }
    if ($_module_good) {
        Write-Host "$_module_name is installed" 
    }else {
        Write-Host  "$_module_name is not installed" -ForegroundColor Red 
    }
    Set-Location $_start_loc
    return $_module_good
}

Write-Host "Checking denpendecies..." -ForegroundColor Green
if( -not (Test-And-Install-Packages("sqlite3"))){
    exit
}
Write-Host "Dependencies checked." -ForegroundColor Green

if (-not (Test-Path -Path ".\build")) {
    New-Item -Path ".\build" -ItemType "directory" | Out-Null
}
$build_dir = Resolve-Path ".\build"

Set-Location $build_dir

Write-Host "Configuration begins." -ForegroundColor Green

Write-Host "Env:OS is $Env:OS"
try {
    $is_windows = ($Env:OS -match "Win")
}
catch {
    $is_windows = $false
}

if ($is_windows){
    Write-Host "Build for win32..."
    cmake -A "Win32"`
        -DCMAKE_TOOLCHAIN_FILE="$VCPKG_RT\scripts\buildsystems\vcpkg.cmake" `
        -DCMAKE_CONFIGURATION_TYPES="$config_type" `
        -DVCPKG_TARGET_TRIPLET="$target_triplet" `
        ..
}else {
    Write-Host "Build for anything..."
    cmake `
        -DCMAKE_TOOLCHAIN_FILE="$VCPKG_RT\scripts\buildsystems\vcpkg.cmake" `
        -DCMAKE_BUILD_TYPE="$config_type" `
        ..
}

Write-Host "Build begins." -ForegroundColor Green
cmake --build .  --config $config_type

Set-Location $start_location



