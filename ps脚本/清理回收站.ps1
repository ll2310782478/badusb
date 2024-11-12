# 清理回收站
try {
    Clear-RecycleBin -Confirm:$false
} catch {
    Write-Host "$($_.Exception.Message)"
}
