* background

设置背景图片

问题报错：插件Fix VSCODE Checksums

```json
"background.customImages": [
        "file:///D:\\pixiv\\1.png"
    ],
    "background.style": {
    
        "content": "''",
        "pointer-events": "none",
        "position": "absolute",
        "z-index": "99999",
        "width": "100%",
        "height": "100%",
        "background-position": "100% 100%",
        "background-size": "100%,100%",
        "background-repeat": "no-repeat",
        "opacity": 0.3
    },
```

* bracket pair colorizer

给括号设置颜色

* Todo Tree

在注释中设置相关事项

```python
#TODO:	设置代办
#TAG:	标签
#FIXME:		代修改
#DONE: 		已完成
#NOTE:		注释
```

* Booksmarks

设置书签，方便跳转

* koroFileHeader

自动生成头文件说明

```json
//korofileheader 注释插件 设置里面找到 Custom Made 写入以下配置 
  "fileheader.customMade": {    //此为头部注释
        "Description": "",
        "Version": "2.0",
        "Autor": "jjkhl",
        "Date": "Do not edit",
        "LastEditors": "jjkhl",
        "LastEditTime": "Do not edit"
    },
    "fileheader.cursorMode": {  //此为函数注释
        "description":"",
        "param": "",
        "return": "",
        "author":"jjkhl"
    },
    "fileheader.configObj": {
        "autoAdd": true, // 默认开启自动添加头部注释，当文件没有设置头部注释时保存会自动添加
        "autoAlready": true, // 默认开启
        "prohibitAutoAdd": [
            "json",
            "md"
        ], // 禁止.json .md文件，自动添加头部注释
        "wideSame": false, // 设置为true开启
        "wideNum": 13 // 字段长度 默认为13
    }
```



* markdown preview enhance

网址：https://shd101wyy.github.io/markdown-preview-enhanced/#/zh-cn/usages

