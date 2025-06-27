# PowerShell 脚本：将 CMake 文件中的 main.c 和 freertos.c 替换为对应的 .cpp 文件
# 作者：GitHub Copilot
# 日期：2025年6月27日

$cmakelists_path = ".\cmake\stm32cubemx\CMakeLists.txt"

# 检测文件是否存在
if (-Not (Test-Path $cmakelists_path)) {
    Write-Host "错误：CMakeLists.txt 文件未找到，路径：$cmakelists_path" -ForegroundColor Red
    exit 1
}

Write-Host "开始处理文件：$cmakelists_path" -ForegroundColor Green

# 读取文件内容
$cmakelists_content = Get-Content $cmakelists_path

# 显示原始内容（可选，用于调试）
Write-Host "`n=== 查找需要替换的行 ===" -ForegroundColor Yellow
$lineNumber = 0
$foundLines = @()
foreach ($line in $cmakelists_content) {
    $lineNumber++
    if ($line -match '\$\{CMAKE_SOURCE_DIR\}/Core/Src/main\.c\s*$' -or $line -match '\$\{CMAKE_SOURCE_DIR\}/Core/Src/freertos\.c\s*$') {
        Write-Host "第 $lineNumber 行: $line" -ForegroundColor Cyan
        $foundLines += $lineNumber
    }
}

if ($foundLines.Count -eq 0) {
    Write-Host "未找到包含 main.c 或 freertos.c 的行" -ForegroundColor Yellow
    exit 0
}

# 执行替换
Write-Host "`n=== 执行替换 ===" -ForegroundColor Yellow
$modified_content = $cmakelists_content -replace '\$\{CMAKE_SOURCE_DIR\}/Core/Src/main\.c\s*$', '${CMAKE_SOURCE_DIR}/Core/Src/main.cpp'
$modified_content = $modified_content -replace '\$\{CMAKE_SOURCE_DIR\}/Core/Src/freertos\.c\s*$', '${CMAKE_SOURCE_DIR}/Core/Src/freertos.cpp'

# 显示修改后的相关行
Write-Host "`n=== 替换后的行 ===" -ForegroundColor Yellow
$lineNumber = 0
foreach ($line in $modified_content) {
    $lineNumber++
    if ($foundLines -contains $lineNumber) {
        Write-Host "第 $lineNumber 行: $line" -ForegroundColor Green
    }
}

# 备份原文件
$backup_path = $cmakelists_path + ".backup." + (Get-Date -Format "yyyyMMdd_HHmmss")
Copy-Item $cmakelists_path $backup_path
Write-Host "`n备份文件已创建：$backup_path" -ForegroundColor Blue

# 写入修改后的内容
$modified_content | Set-Content $cmakelists_path -Encoding UTF8

Write-Host "`n=== 替换完成 ===" -ForegroundColor Green
Write-Host "已将 main.c 替换为 main.cpp，freertos.c 替换为 freertos.cpp" -ForegroundColor Green
Write-Host "共修改了 $($foundLines.Count) 行" -ForegroundColor Green

# 验证替换结果
Write-Host "`n=== 验证替换结果 ===" -ForegroundColor Yellow
$verification_content = Get-Content $cmakelists_path
$cpp_main_lines = $verification_content | Where-Object { $_ -match '\$\{CMAKE_SOURCE_DIR\}/Core/Src/main\.cpp\s*$' }
$cpp_freertos_lines = $verification_content | Where-Object { $_ -match '\$\{CMAKE_SOURCE_DIR\}/Core/Src/freertos\.cpp\s*$' }
$c_main_lines = $verification_content | Where-Object { $_ -match '\$\{CMAKE_SOURCE_DIR\}/Core/Src/main\.c\s*$' }
$c_freertos_lines = $verification_content | Where-Object { $_ -match '\$\{CMAKE_SOURCE_DIR\}/Core/Src/freertos\.c\s*$' }

if ($cpp_main_lines.Count -gt 0) {
    Write-Host "? 找到 $($cpp_main_lines.Count) 个 main.cpp 引用" -ForegroundColor Green
}
if ($cpp_freertos_lines.Count -gt 0) {
    Write-Host "? 找到 $($cpp_freertos_lines.Count) 个 freertos.cpp 引用" -ForegroundColor Green
}
if ($c_main_lines.Count -eq 0) {
    Write-Host "? 确认已无 main.c 引用" -ForegroundColor Green
} else {
    Write-Host "? 仍存在 $($c_main_lines.Count) 个 main.c 引用" -ForegroundColor Yellow
}
if ($c_freertos_lines.Count -eq 0) {
    Write-Host "? 确认已无 freertos.c 引用" -ForegroundColor Green
} else {
    Write-Host "? 仍存在 $($c_freertos_lines.Count) 个 freertos.c 引用" -ForegroundColor Yellow
}

Write-Host "`n脚本执行完成！" -ForegroundColor Green