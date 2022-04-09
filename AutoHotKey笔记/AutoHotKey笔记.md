<h1 align="center">AutoHotKey笔记</h1>

## 参考网址

[中文网站]:https://wyagd001.github.io/zh-cn/docs/AutoHotkey.htm

[英文网站]：https://www.autohotkey.com/docs/AutoHotkey.htm

## 基本按键

| #    | Win                                                          |
| ---- | ------------------------------------------------------------ |
| !    | Alt                                                          |
| ^    | ctrl                                                         |
| +    | shift                                                        |
| &    | 组合任意两个按键或鼠标按钮                                   |
| <    | 使用左边对应按键才触发                                       |
| >    | 使用右边对应按键才触发                                       |
| *    | 即使附加修饰键被按住也能触发：*#c(Win+c,Shift+Win+c等都能触发) |

**多个按键执行相同动作**

```ahk
^Numpad0::
^Numpad1::
MsgBox Pressing either Control+Numpad0 or Control+Numpad1 will display this message.
return
```

**禁用按键**：

```ahk
Rwin::return
```

**上下文相关按键**

```ahk
#IfWinActive, ahk_class Notepad
^a::MsgBox 你在记事本中按下了 Ctrl-A. 而在其他窗口中按下 Ctrl-A 将原样发送.
#c::MsgBox 你在记事本中按下了 Win-C 组合键.

#IfWinActive
#c::MsgBox 你在非记事本程序中按下了 Win-C .

#If MouseIsOver("ahk_class Shell_TrayWnd") ; 有关 MouseIsOver, 请参阅 #If 示例 1.
WheelUp::Send {Volume_Up}     ; 在任务栏上滚动滚轮: 增加/减小音量.
WheelDown::Send {Volume_Down} 
```

**自定义组合键**

```ahk
Numpad0&Numpad1::WinMaxmize A;最大化活动窗口
```

**最大化当前窗口和还原当前你窗口**

```ahk
!enter::
    WinGet, OutputVar, MinMax, A
    if (OutputVar == 1) {
        WinRestore, A
    } else {
        WinMaximize, A
    }
return
```

**在有一个或多个按钮的小窗口显示指定文本**

```ahk
mgbox[,options,title,text,timeout]
```

| options                   | value |
| ------------------------- | ----- |
| OK                        | 0     |
| OK/Cancel                 | 1     |
| Abort/Retry/Ignore        | 2     |
| Yes/No/Cancel             | 3     |
| Yes/No                    | 4     |
| Retry/Cancel              | 5     |
| Cancel/Try Again/Continue | 6     |

要在消息框中显示一个图标，添加以下值

| 错误图标   | 16   |
| ---------- | ---- |
| 问号图标   | 32   |
| 惊叹号图标 | 48   |
| 星号图标   | 64   |

指定默认按钮：

| 让第二个按钮成为默认按钮 | 256  |
| ------------------------ | ---- |
| 让第三个按钮成为默认按钮 | 512  |

示例：

判断用户在最近的消息框中按下哪个按钮

```ahk
MsgBox, 4,, Would you like to continue? (press Yes or No)
IfMsgBox Yes
    MsgBox You pressed Yes.
else
    MsgBox You pressed No.
```

改变MsgBox按钮名称

```ahk
; 改变 MsgBox 的按钮名称
; https://www.autohotkey.com
; 这是个可运行示例脚本, 它使用计时器改变消息框中按钮的名称.
; 尽管改变了按钮名称, 但 IfMsgBox 命令中仍需要引用它们原始的按钮名称表示的按钮.

#SingleInstance
SetTimer, ChangeButtonNames, 50 
MsgBox, 4, Add or Delete, Choose a button:
IfMsgBox, YES 
	MsgBox, You chose Add. 
else 
	MsgBox, You chose Delete. 
return 

ChangeButtonNames: 
IfWinNotExist, Add or Delete
	return  ; Keep waiting.
SetTimer, ChangeButtonNames, Off 
WinActivate 
ControlSetText, Button1, &Add 
ControlSetText, Button2, &Delete 
return
```

**显示输入框让用户输入字符串**

```ahk
InputBox,输入文本的变量名[,标题,输入框文本，HIDE(屏蔽用户输入，用于输入密码),Width,Height,X,Y,,Timeout]
```

## 鼠标操作



