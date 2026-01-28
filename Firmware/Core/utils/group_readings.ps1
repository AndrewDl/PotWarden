# Combine all CSV files by given id in temp/readings into a single file
# Usage: .\group_readings.ps1 <id>

param(
    [Parameter(Mandatory=$true, Position=0)]
    [string]$id
)

$folder = "temp/readings"
$output = $folder + "/combined_${id}.csv"

# Get all files matching the pattern for the given id
$files = Get-ChildItem -Path $folder -Filter "*_${id}.csv" | Sort-Object Name

if ($files.Count -eq 0) {
    Write-Host "No files found for id $id"
    exit 1
}

# Combine all files into one output file
Get-Content $files.FullName | Set-Content $output

Write-Host "Combined $($files.Count) files into $output"