原文链接：https://blog.csdn.net/weixin_42815609/article/details/103830253

1. 安装code runner；matlab；matlab-format插件
2. 在vscode的setting.json中加入

```
"matlab.mlintpath": "你的bin\\win64\\mlint.exe安装路径",
"matlab.matlabpath": "你的bin\\matlab.exe安装路径",
"matlab.linterEncoding": "gb2312",
```

表示vscode调用matlab插件，运行matlab/查看补全/纠错验错时，去上述路径中寻找matlab的引擎



```
"code-runner.executorMap":{
        "matlab": "cd $dir && matlab -nosplash -nodesktop -r $fileNameWithoutExt",
}
#解释说明
cd $dir
# 进入当前文件夹

matlab -nosplash -nodesktop -r $fileNameWithoutExt
# -nosplash表示启动时不显示图标
# -nodesktop表示只启动命令行形式的matlab
# -r表示只读该文件
# $fileNameWithoutExt表示该文件的名称，并且不带后缀名
```

表示使用code runner运行m文件时，想进入文件所在文件夹，然后调用matlab



```
	"files.associations": {
        "*.m": "matlab",
    },
    
    "code-runner.runInTerminal": true,

    "[matlab]" : {
        "files.encoding": "gb2312",
    },

    "files.autoGuessEncoding": true,

```

“files.associations"让VSC识别.m文件为matlab文件；
		“code-runner.runInTerminal”: true让code-runner的结果在Terminal中显示；
		剩下两项为编码选项，matlab使用gb2312编码。

