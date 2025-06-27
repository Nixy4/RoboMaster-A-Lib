# PowerShell �ű����� CMake �ļ��е� main.c �� freertos.c �滻Ϊ��Ӧ�� .cpp �ļ�
# ���ߣ�GitHub Copilot
# ���ڣ�2025��6��27��

$cmakelists_path = ".\cmake\stm32cubemx\CMakeLists.txt"

# ����ļ��Ƿ����
if (-Not (Test-Path $cmakelists_path)) {
    Write-Host "����CMakeLists.txt �ļ�δ�ҵ���·����$cmakelists_path" -ForegroundColor Red
    exit 1
}

Write-Host "��ʼ�����ļ���$cmakelists_path" -ForegroundColor Green

# ��ȡ�ļ�����
$cmakelists_content = Get-Content $cmakelists_path

# ��ʾԭʼ���ݣ���ѡ�����ڵ��ԣ�
Write-Host "`n=== ������Ҫ�滻���� ===" -ForegroundColor Yellow
$lineNumber = 0
$foundLines = @()
foreach ($line in $cmakelists_content) {
    $lineNumber++
    if ($line -match '\$\{CMAKE_SOURCE_DIR\}/Core/Src/main\.c\s*$' -or $line -match '\$\{CMAKE_SOURCE_DIR\}/Core/Src/freertos\.c\s*$') {
        Write-Host "�� $lineNumber ��: $line" -ForegroundColor Cyan
        $foundLines += $lineNumber
    }
}

if ($foundLines.Count -eq 0) {
    Write-Host "δ�ҵ����� main.c �� freertos.c ����" -ForegroundColor Yellow
    exit 0
}

# ִ���滻
Write-Host "`n=== ִ���滻 ===" -ForegroundColor Yellow
$modified_content = $cmakelists_content -replace '\$\{CMAKE_SOURCE_DIR\}/Core/Src/main\.c\s*$', '${CMAKE_SOURCE_DIR}/Core/Src/main.cpp'
$modified_content = $modified_content -replace '\$\{CMAKE_SOURCE_DIR\}/Core/Src/freertos\.c\s*$', '${CMAKE_SOURCE_DIR}/Core/Src/freertos.cpp'

# ��ʾ�޸ĺ�������
Write-Host "`n=== �滻����� ===" -ForegroundColor Yellow
$lineNumber = 0
foreach ($line in $modified_content) {
    $lineNumber++
    if ($foundLines -contains $lineNumber) {
        Write-Host "�� $lineNumber ��: $line" -ForegroundColor Green
    }
}

# ����ԭ�ļ�
$backup_path = $cmakelists_path + ".backup." + (Get-Date -Format "yyyyMMdd_HHmmss")
Copy-Item $cmakelists_path $backup_path
Write-Host "`n�����ļ��Ѵ�����$backup_path" -ForegroundColor Blue

# д���޸ĺ������
$modified_content | Set-Content $cmakelists_path -Encoding UTF8

Write-Host "`n=== �滻��� ===" -ForegroundColor Green
Write-Host "�ѽ� main.c �滻Ϊ main.cpp��freertos.c �滻Ϊ freertos.cpp" -ForegroundColor Green
Write-Host "���޸��� $($foundLines.Count) ��" -ForegroundColor Green

# ��֤�滻���
Write-Host "`n=== ��֤�滻��� ===" -ForegroundColor Yellow
$verification_content = Get-Content $cmakelists_path
$cpp_main_lines = $verification_content | Where-Object { $_ -match '\$\{CMAKE_SOURCE_DIR\}/Core/Src/main\.cpp\s*$' }
$cpp_freertos_lines = $verification_content | Where-Object { $_ -match '\$\{CMAKE_SOURCE_DIR\}/Core/Src/freertos\.cpp\s*$' }
$c_main_lines = $verification_content | Where-Object { $_ -match '\$\{CMAKE_SOURCE_DIR\}/Core/Src/main\.c\s*$' }
$c_freertos_lines = $verification_content | Where-Object { $_ -match '\$\{CMAKE_SOURCE_DIR\}/Core/Src/freertos\.c\s*$' }

if ($cpp_main_lines.Count -gt 0) {
    Write-Host "? �ҵ� $($cpp_main_lines.Count) �� main.cpp ����" -ForegroundColor Green
}
if ($cpp_freertos_lines.Count -gt 0) {
    Write-Host "? �ҵ� $($cpp_freertos_lines.Count) �� freertos.cpp ����" -ForegroundColor Green
}
if ($c_main_lines.Count -eq 0) {
    Write-Host "? ȷ������ main.c ����" -ForegroundColor Green
} else {
    Write-Host "? �Դ��� $($c_main_lines.Count) �� main.c ����" -ForegroundColor Yellow
}
if ($c_freertos_lines.Count -eq 0) {
    Write-Host "? ȷ������ freertos.c ����" -ForegroundColor Green
} else {
    Write-Host "? �Դ��� $($c_freertos_lines.Count) �� freertos.c ����" -ForegroundColor Yellow
}

Write-Host "`n�ű�ִ����ɣ�" -ForegroundColor Green