<h1 align="center">项目基础知识</h1>

视频网址:https://www.bilibili.com/video/BV1tp4y1i7rL

## main函数的参数

```c++
int main(int argc,char *argv[],char *envp[])
```

int argc：存放命令行的参数

char *argv[]：每个元素都是一个字符指针，指向一个字符串，即命令行中的每一个参数。

envp：存放了当前程序运行环境的参数

main函数的参数，不管是输入的是整数还是浮点数，全都被认为是字符串

