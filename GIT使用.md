# GIT使用

## 命令行的使用

1. 文件的新建：touch test.txt    
2. 文件的添加：git add test.txt hello.cpp 
3. 所有文件的添加：git add . 
4. 查看当前目录下的所有文件：ls
5. 编辑当前文档：vim test.txt
6. 退出编辑器：先按ESC，后输入 :q(退出编辑器)、:q!(强制退出不保存)、:wq(保存后退出)、:wq!(强制保存后退出)
7. 回退: git reset HEAD^ (所有内容) // HEAD^hello.php  // 052e(指定版本) 
8. 回退到前几个版本: git reset --soft HEAD^n //回退到上n一个版本(HEAD^n)
9. 删除文件：git rm test.txt
10. 重命名：git mv README README.md
11. 查看提交记录：git log oneline//简洁版本
12. 新建test文件后写入hello：echo 'hello' > test.txt
13. 转到新建的新分支：git checkout -b newBranch
14. 创建带注释的标签：git tag -a v1.0

## 提交到github仓库

git add test.txt

git commit -m "添加test.txt文件"

git remote add origin git@github.com:jjkhl/newbird.git

git push -u origin master



```bash
#创建新的仓库
echo "# jjkhl" >> README.md
git init
git add README.md
git commit -m "first commit"
git branch -M main
git remote add origin https://github.com/jjkhl/jjkhl.git
git push -u origin main

#将存在的仓库移植过来
git remote add origin https://github.com/jjkhl/jjkhl.git
#新建分支
git branch  new
git push -u origin new

#git本地切换分支
git checkout OS
#查看当前远程分支
git branch -r
#查看当前本地分支
git branch
# 设置用户名
git config --global user.name "zhaijihai" 
# 设置用户邮箱
git config --global user.email "zhaijihai@163.com" 
# 查看git版本
git --version
# 查看git配置信息
git config -l

切换到项目文件夹
# 初始化git本地仓库
第一种方法，在项目文件夹下：
git init
第二种
git 项目文件夹名 init
第三种
git clone https://xxx


项目目录就叫做仓库
winddows下查看目录：dir/a

# 查看本地仓库的文件状态
git status

# 将本地文件添加到暂存区
git add 文件名
git add .       （提交仓库下的所有文件）

# 将文件提交到仓库
git commit -m "提交信息描述"
每次commit都会产生一个版本号

# 查看提交的版本记录
git log

# 回退到之间提交的某个节点
git checkout 版本号

# 回退到当前版本
git checkout -

# 查看之前都改了什么
git log -p

# 查看提交信息一行显示
git log --oneline

# 添加版本信息
 git tag -a v1 -m "第一版"

# 给每个节点添加tag
git tag -a v0.5 -m "更早的版本" 5b98fe3

# 版本回退，回溯到标签所在的提交
git checkout 标签名

# 查看所有的版本信息
git log --oneline --all

分支
# 创建分支
git branch 分支名

# 切换分支
git checkout 分支名

# 切换到主分支
git checkout master

# 图形化查看分支
git log --oneline --all --graph

#删除分支
git branch -d 分支名

# 创建一个分支并切换到这个分支
git checkout -b 分支名

# 合并到主分支
git merge 分支名

远程仓库
git remote add 远程名称 远程地址

# 列出所有远程仓库
git remote

# 列出所有远程仓库详细信息
git remote -v

# 上传代码
git push -u 远程名 分支名# 下载代码git pull

多人合作远程仓库
git clone xxx.xxx.xxx whh
git clone xxx.xxx.xxx zjh

#要把两个不同的项目合并，但是两个仓库不同，报错：refusing to merge unrelated histories
git pull origin master --allow-unrelated-histories

#同步远程仓库和本地
git pull origin 远程分支:本地分支
git fetch origin 远程分支:本地分支

#比较本地仓库和下载的temp分支
git diff temp
```

[查看分支操作](https://blog.csdn.net/guo_qiangqiang/article/details/88020656?utm_medium=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-1.base&depth_1-utm_source=distribute.pc_relevant.none-task-blog-2%7Edefault%7EBlogCommendFromMachineLearnPai2%7Edefault-1.base)

[commit操作](https://blog.csdn.net/qq_32281471/article/details/95478314)

## 合并网络仓库和本地仓库

git pull origin master

## 克隆github仓库

git clone https://github.com/gogs/gogs.git 

网速增加: git clone https://gitclone.com/github.com/gogs/gogs.git  

