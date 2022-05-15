#vscode导出文件格式
网址:https://shd101wyy.github.io/markdown-preview-enhanced/#/zh-cn/pandoc-pdf
MD文件开头添加以下内容，path表示存储的路径，toc是支持自动生成目录
```markdown
---
title:"test"
output:
    word_document:
        path: test.docx
        toc: true
        toc_depth: 6
        number_selection: true
---
```



# 表格合并：

table表示表格    tr表示行   td表示列

英文横排为row，竖排为column
<center>
<table style="text-align: center;">
    <caption align="center">这是一个测试表格</caption>
    <tr>
        <td rowspan="2">第一行</td>
        <td>a</td>
        <td colspan="2">b</td>
    </tr>
    <tr>
        <td>a</td>
        <td>b</td>
        <td>c</td>
    </tr>
    <tr>
        <td>第三行</td>
        <td>a</td>
        <td>b</td>
        <td>c</td>
    </tr>
</table>
</center>
<div style="text-align: center;">
<table style="margin:auto;">
    <caption >这是一个测试表格</caption>
    <tr>
        <td rowspan="2">第一行</td>
        <td>a</td>
        <td colspan="2">b</td>
    </tr>
    <tr>
        <td>a</td>
        <td>b</td>
        <td>c</td>
    </tr>
    <tr>
        <td>第三行</td>
        <td>a</td>
        <td>b</td>
        <td>c</td>
    </tr>
</table>
</div>

//表格整体居中
<center>
</style>
<table>
<tr>
    <td>nihao</td>
    <td>foo</td>
<tr>
</table>
</center>
# 标题居中

<h1 align ="center">居中显示标题</h1>
<center> hell</center>

# 将字体变色

$\textcolor{red}{红色}$

<font color='red'>红色</font>

```
第三种<span style='color:文字颜色;background:背景颜色;font-size:文字大小;font-family:字体;'>文字</span>
```

<span style='color:red;'>红色</span>

$\textcolor{green}{绿色}$​

<strong style="color:red">红色加粗</strong>

# 页面跳转

方法1：[123](#表格合并: )

方法2：设置id ——<span id="jump1">跳转点</span>

​    		[跳转至跳转点](#jump1)



## LATEX公式
$$
\left\{
	\begin{array}{c}
		\Huge a=\frac{\sum_{i=1}^n(x_i-\overline{x})(y_i-\overline{y})}{\sum_{i=1}^n(x_i-\overline{x})^{2}} \tag{aa}\\
		\Huge b=\overline{y}-a\overline{x} \\
	\end{array}
\right.
$$

调整大小
$$
S=\pi r^2
\tiny \pi r^2
\scriptsize \pi r^2
\small\pi r^2
\normalsize \pi r^2
\large \pi r^2
\Large \pi r^2
\LARGE \pi r^2
\huge \pi r^2
\Huge \pi r^2
$$
插入的图片带有链接：
`[![](.//img/01.png '百度')](http://www.baidu.com)`

