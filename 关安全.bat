@echo off
setlocal

rem 禁用实时保护
reg add "HKEY_LOCAL_MACHINE\SOFTWARE\Policies\Microsoft\Windows Defender" /v DisableRealtimeMonitoring /t REG_DWORD /d 1 /f

rem 重启 Windows Defender 服务
net stop WinDefend
net start WinDefend

endlocal
