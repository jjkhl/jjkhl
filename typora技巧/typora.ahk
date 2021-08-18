; Typora
; 快捷增加字体颜色
; SendInput {Text} 解决中文输入法问题

#IfWinActive ahk_exe Typora.exe
{
   ; alt+0 黑色
    !0::addFontColor("black")
  
    ; alt+1 红色
    !1::addFontColor("red")

    ; alt+1 橙色
    !2::addFontColor("orange") 

     ; alt+3 黄色
    !3::addFontColor("yellow")

     ; alt+4 绿色
    !4::addFontColor("green")

    ; alt+5 浅蓝色
    !5::addFontColor("cornflowerblue")

     ; alt+6 青色
    !6::addFontColor("cyan") 

   ; alt+7 紫色
    !7::addFontColor("purple") 
}

; 快捷增加字体颜色
addFontColor(color){
    clipboard := "" ; 清空剪切板
    Send {ctrl down}c{ctrl up} ; 复制
    SendInput {TEXT}<strong style="color:%color%">
    SendInput {ctrl down}v{ctrl up} ; 粘贴
    If(clipboard = ""){
        SendInput {TEXT}</strong> ; Typora 在这不会自动补充
    }else{
        SendInput {TEXT}</ ; Typora中自动补全标签
    }
}