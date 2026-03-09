## 文件系统应用

本例是一个提供Web服务的程序，使用htm文件为响应内容。

### 1.使用Flash存储htm文件

用Flash存储的一个区域做文件系统来存储htm文件。

需在partitions.csv文件中匹配存储地址区域，支持Fat、SPIFFIS等格式。

使用相关工具将htm文件上传到上述地区域。

在MyBoard类中，初始化相应格式的文件系统。

### 2.使用SD卡存储htm文件

用SD卡来存储htm文件。

在电脑端用读卡器将htm文件上传到SD卡内。

在MyBoard类中，初始化SD（或SD_MMC）文件系统。