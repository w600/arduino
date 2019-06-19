# 准备（Python环境安装[可选] - Windows）
	0）目前针对 Windows 环境，我们已经提供了可供烧录的exe程序，但是由于一些版本上的问题，对 xp 环境支持的不是很好，建议开发者使用win7进行W600 Arduino的开发。
	1）建议使用 3.4 版本的 Python 解析器，可以从 python 官网自行下载（其一下载链接为：https://www.python.org/ftp/python/3.4.4/python-3.4.4.msi）；
	2）双击安装 python-3.4.4.msi（这里不再详述）；
	3）必要时，在 Windows 的 Path 环境变量中添加“;C:\Python34;C:\Python34\Scripts”（具体路径，根据实际安装情况进行确定）；
	4）在 cmd 命令行窗口执行命令：pip install pyserial；
	5）在 cmd 命令行窗口执行命令：pip install pyprind。

# 安装
	0） 在 w600-arduino-x.x.x/examples/ 目录下，保存了一些您的测试程序，您可以使用；Arduino IDE 版本建议为 1.8.7（含）以上；
	1） 将 package_wmcom_index.json 拷贝至 AppData\Local\Arduino15（或通过我司官网获得该 JSON 文件（位于http://www.winnermicro.com 的【解决方案】->【参考设计】->【Arduino 接口开发板】->【软件资料】板块））；
	2） Arduino IDE 中，在开发板管理器中，选择 w600 开发板，选择特定版本后，点击“安装”按钮，更新到 w600-arduino-x.x.x和wmtools-x.x.x版本；
	3） 开发板选择 Generic W600 board，选择方法为：【工具】->【开发板】；
	4） 可以使用 Arduino IDE 创建 您的 sketch 测试您的相关功能。

# API 
当前的板级支持包提供的可用类、命名空间、方法等 API 帮助信息，请参考 doc/W60X_Arduino.chm.
	
# 样例程序
为了方便使用，当前发布包中提供了一些 example，路径为：AppData\Local\Arduino15\packages\w600\hardware\w600\x.x.x\examples（部分示例代码可以通过Arduino IDE打开）
- sketch_led_ap.ino: 按下 USER_BTN 按键，RGB-LED 灯被点亮，并且创建软 AP；释放 USER_BTN 按键，RGB-LED 熄灭，软 AP 销毁。
- sketch_sta.ino: 将 W600 Arduino 最为 WiFi Station 使用，连接到 AP，并且尝试解析 www.baidu.com 域名。
- sketch_cloud.ino：通过机智云App，借助机智云的基础设施完成控制 w600 Arduino LEDs 功能的示例程序。

# 注意事项
- 第一次使用 W600 Arduino 开发板，建议首先烧录 FLS 文件（wmtools-0.3.0 版本可以在不存在固件的情况下自动烧录 FLS）；
- 为了有效使用 Arduino IDE 的自动烧录功能，请确保升级之前的固件可以正常工作，并且运行中的各个内置任务可以正常调度；
- 如果自动烧录功能失败，或长时间没有返回（大于45秒），请考虑使用手动方式进行固件升级。