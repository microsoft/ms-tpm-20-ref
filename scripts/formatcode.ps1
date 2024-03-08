
function Format-Folder
{
    param ([string]$FolderName)
    Write-Host "Scanning Folder" $FolderName
    Get-ChildItem -Path $FolderName -File -Recurse -Include *.h, *.c, *.cpp, *.inl |
    foreach {
        Write-Host "Formatting " $_
        clang-format -i -style=file $_.FullName
    }
}

foreach ($subdir in "TPMCmd/tpm", "TPMCmd/Platform", "TPMCmd/Simulator")
{
    Get-ChildItem -Path $subdir -Directory |
    foreach {
        Format-Folder -FolderName $_.FullName
    }
}
