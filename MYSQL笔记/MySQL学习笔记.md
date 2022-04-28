# MySQL安装
[Window端安装](https://www.php.cn/mysql-tutorials-454993.html)
[Linux端安装](https://www.runoob.com/mysql/mysql-install.html)
# 参考资料
* 《MySQL必知必会》
* [黑马程序员_MySQL数据库入门](https://b23.tv/BV1Kr4y1i7ru)
# 基本语法
## SQL通用语法
* SQL语句可以单行或多行书写，以分号结尾
* SQL语句可以使用空格或缩进来增强语句的可读性
* MySQL数据库不区分大小写，关键字建议大写
* 注释
```mysql

--注释内容或#注释内容

/*注释内容*/
```
## SQL分类
- DDL(Data Definition Language): 数据定义语言，用来定义数据库对象（数据库、表、字段）
- DML(Data Manipulation Language): 数据操作语言，用来对数据库表中的数据进行增删改
- DQL(Data Query Language): 数据查询语言，用来查询数据库中表的记录
- DCL(Data Control Language): 数据控制语言，用来创建数据库用户、控制数据库的控制权限

### 数据类型
<h5 align="center">数值类型</h5>

|类型|大小|有符号范围|无符号范围|
|:--:|:--:|:--:|:--:|
|tinyint|1 byte|(-128,127)|(0,255)|
|smallint|2 bytes|(-32768,32767)|(0,65535)|
|mediumint|3 bytes|(-8388608,8388607)|(0,16777215)|
|int或integer|4 bytes|(-2147483648,2147483647)|(4294967295)|
|bigint|8 bytes|(-2<sup>63</sup> , 2<sup>63</sup>-1)|(0,2<sup>64</sup>-1)|
|float|4 bytes|(-3.402823466E+38,3.402823466351E+38)|(0,1.175494351E-38)和(0,3.402823466E+38)|
|double|8 bytes|(-1.7976931348623157E+308,1.7976931348623457E+308)|(0,2.2250738585072014E-308)和(0,1.7976931348623157E+308)|

<h5 align="center">字符串类型</h5>

|类型|大小|
|:--:|:--:|
|char|0-255 bytes|
|varchar|0-65535 bytes|
|tinyblob|0-255 bytes|
|tinytext|0-255 bytes|
|blob|0-65535 bytes|
|text|0-65535 bytes|
|mediumblob|0-16777215 bytes|
|mediumtext|0-16777215 bytes|
|longblob|0-4294967295 bytes|
|longtext|0-4294967295 bytes|

<h5 align="center">日期类型</h5>

|类型|大小|范围|格式|
|:--:|:--:|:--:|:--:|
|date|3|1000-01-01至9999-12-31|YYYY-MM-DD|
|time|3|-838:59:59至838:59:59|HH:MM:SS|
|year|1|1901-2155|YYYY|
|datetime|8|1000-01-01 00:00:00至9999-12-31 23:59:59|YYYY-MM-DD HH:MM:SS|
|timestamp|4|1970-01-01 00:00:01至2038-01-19 03:14:07|YYYY-MM-DD HH:MM:SS|

### DDL(数据定义语言)
#### 数据库操作
查询所有数据库：
`SHOW DATABASES;`
查询当前数据库：
`SELECT DATABASE();`
创建数据库：
`CREATE DATABASE [ IF NOT EXISTS ] 数据库名 [ DEFAULT CHARSET 字符集] [COLLATE 排序规则 ];`

> UTF8字符集长度为3字节，有些符号占4字节，所以推荐用utf8mb4字符集


删除数据库：
`DROP DATABASE [ IF EXISTS ] 数据库名;`
使用数据库：
`USE 数据库名;`

#### 表操作

查询当前数据库所有表：
`SHOW TABLES;`
查询表结构：
`DESC 表名;`
查询指定表的建表语句：
`SHOW CREATE TABLE 表名;`

* 创建表：
```mysql
CREATE TABLE 表名(
	字段1 字段1类型 [COMMENT 字段1注释],
	字段2 字段2类型 [COMMENT 字段2注释],
	字段3 字段3类型 [COMMENT 字段3注释],
	...
	字段n 字段n类型 [COMMENT 字段n注释]
)[ COMMENT 表注释 ];

#注意最后字段n没有逗号

示例操作：
create table tb_user(
id int comment '编号',
name varchar(50) comment '姓名',
age int comment '年龄',
gender varchar(1) comment '性别'
)comment '用户表';
```

* 修改表

添加字段：
`ALTER TABLE 表名 ADD 字段名 类型(长度) [COMMENT 注释] [约束];`
例：`ALTER TABLE emp ADD nickname varchar(20) COMMENT '昵称';`

修改数据类型：
`ALTER TABLE 表名 MODIFY 字段名 新数据类型(长度);`
修改字段名和字段类型：
`ALTER TABLE 表名 CHANGE 旧字段名 新字段名 类型(长度) [COMMENT 注释] [约束];`
例：将emp表的nickname字段修改为username，类型为varchar(30)
`ALTER TABLE emp CHANGE nickname username varchar(30) COMMENT '昵称';`

删除字段：
`ALTER TABLE 表名 DROP 字段名;`

修改表名：
`ALTER TABLE 表名 RENAME TO 新表名`

删除表：
`DROP TABLE [IF EXISTS] 表名;`
删除表，并重新创建该表：
`TRUNCATE TABLE 表名;`

### DML(数据操作语言)
#### 添加数据
`INSERT INTO 表名 (字段名1, 字段名2, ...) VALUES (值1, 值2, ...);`
全部字段：
`INSERT INTO 表名 VALUES (值1, 值2, ...);`

批量添加数据：
`INSERT INTO 表名 (字段名1, 字段名2, ...) VALUES (值1, 值2, ...), (值1, 值2, ...), (值1, 值2, ...);`
`INSERT INTO 表名 VALUES (值1, 值2, ...), (值1, 值2, ...), (值1, 值2, ...);`

> 字符串和日期类型数据应该包含在引号中；
> 插入的数据大小应该在字段的规定范围内；

#### 更新和删除数据

修改数据：
`UPDATE 表名 SET 字段名1 = 值1, 字段名2 = 值2, ... [ WHERE 条件 ];`
例：修改所有人的时间
`update employee set entrydate = '2018-01-01';`


删除数据：
`DELETE FROM 表名 [ WHERE 条件 ];`

### DQL(数据查询语言)
语法：
```mysql
SELECT
	字段列表
FROM
	表名字段
WHERE
	条件列表
GROUP BY
	分组字段列表
HAVING
	分组后的条件列表
ORDER BY
	排序字段列表
LIMIT
	分页参数
```
#### 基础查询
* 查询多个字段
`SELECT 字段1,字段2... FROM 表名;`
`SELECT * FROM 表名;`

* 设置别名
`SELECT 字段1 [AS 别名1],字段2 [AS 别名2]... FROM 表名;`
`SELECT 字段1 [别名1],字段2 [别名2]... FROM 表名;`

* 去除重复记录
`SELECT DISTINCT 字段列表 FROM 表名;`