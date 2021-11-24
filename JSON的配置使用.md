<h1 align="center">JSON的配置使用</h1>

[单文件和多文件的调试]:https://blog.csdn.net/qq_42429142/article/details/113274450

* 多文件下直接修改launch.json

```bash
先运行g++ -g main.cpp swap.cpp -o mytest.exe
后修改launch.json
"program":"${workspaceFolder}/mytest.exe"
注释"preLaunchTask"一行

//或者直接修改tasks.json中
"${file}",改为 "${workspaceFolder}\\*.cpp",
```
* cmake编译多文件

```bash
1.新建CMkaeLists.txt文件
    program(MYWORK)
    add_executable(cmake_swap main.cpp swap.cpp)#输出的exe为cmake_swap.exe
2.F1选择CMake configure,选择GCC 8.2.0 
3.终端输入cmake ..
4.终端输入mingw32-make.exe
5.修改launch.json
“program”："${fileDirname}\\build\\cmake_swap.exe"#修改为cmake_swap.exe路径
##问题：每次编译都需要重复第4步
```

* cmake编译多文件（改进方法）

```bash
#使用cmake编译多文件的方法
#tasks.json中args要与命令行输入对应g++ -g main.cpp swap.cpp -o out.exe
#launch.json中preLaunchTask的名字要与tasks.json中的label对应，这样才能使用tasks.json
"args":[
		"-g",
		"main.cpp",
		"swap.cpp",
		"-o",
		"${fileDirname}\\build\\Cmake_swap.exe"
]
#然后launch.json中的program也要修改为
 "program": "${fileDirname}\\build\\Cmake_swap.exe",
```

* 直接在task.json中使用cd build        cmake ..        mingw32-make.exe
```bash
#F1输入tasks→配置默认生成任务→g++
#默认tasks：
{
	"version": "2.0.0",
	"tasks": [
		{
			"type": "cppbuild",
			"label": "C/C++: g++.exe 生成活动文件",
			"command": "F:\\mingw64\\bin\\g++.exe",
			"args": [
				"-g",
				"${file}",
				"-o",
				"${fileDirname}\\${fileBasenameNoExtension}.exe"
			],
			"options": {
				"cwd": "${fileDirname}"
			},
			"problemMatcher": [
				"$gcc"
			],
			"group": {
				"kind": "build",
				"isDefault": true
			},
			"detail": "编译器: F:\\mingw64\\bin\\g++.exe"
		}
	]
}
```
```bash
{   
    "version": "2.0.0",
    "options": {
        "cwd": "${workspaceFolder}/build"
    },
    "tasks": [
        {
            "type": "shell",
            "label": "cmake",
            "command": "cmake",
            "args": [
                ".."
            ],
        },
        {
            "label": "make",
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "command": "mingw32-make",
            "args": [

            ],
        },
        {
            "label": "Build",
            "dependsOn":[
                "cmake",
                "make"
            ]
        }
    ],

}
```

* tasks.json中args要与命令行输入对应g++ -g main.cpp swap.cpp -o out.exe

  ```bash
  "args":[
  		"-g",
  		"main.cpp",
  		"swap.cpp",
  		"-o",
  		"${fileDirname}\\out.exe"
  ]
  #然后launch.json中的program也要修改为
  "program":"${workspaceFolder}/out.exe"
  ```

