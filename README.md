# Windows API 示例程序 - 声音播放与文本显示

## 功能特性
- 创建标准 Windows 窗口
- 播放 WAV 格式音频文件
- 显示蓝色"Hello Windows API!"文本
- 支持窗口尺寸动态调整
- 透明背景文字效果
- 微软雅黑字体支持
- 错误处理机制：
  - 窗口创建失败提示
  - 音频加载失败警告
  - 内存资源自动释放

## 开发环境要求
1. Windows 7 及以上操作系统
2. Visual Studio 2015+（支持C11标准）
3. Windows SDK 10+
4. 必需库文件：
   - Winmm.lib (Windows Multimedia API)
   - Shlwapi.lib (Shell轻量级工具库)

## 快速开始
1. 将`sound.wav`文件置于可执行文件同级目录(建议不要使用这个播放)
2. 推荐使用Visual Studio编译步骤：
   ```bash
   cl main.c /link user32.lib gdi32.lib Winmm.lib Shlwapi.lib