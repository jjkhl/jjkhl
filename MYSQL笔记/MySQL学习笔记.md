# MySQL��װ
[Window�˰�װ](https://www.php.cn/mysql-tutorials-454993.html)
Linux�˰�װ��
1. `sudo apt install mysql-server`
> �鿴MySQL�������Ƿ��������У�`sudo systemctl status mysql`

2. �鿴Ĭ�����룺`sudo cat /etc/mysql/debian.cnf`

3. ��root�û�����mysql��`mysql -u root -p`������Ĭ������
4. ����Ĭ�����룺`ALTER  USER  'root'@'localhost'  IDENTIFIED BY '1234';`


* �޸�Ĭ�����������������Ϊ����̫�򵥣���Ҫ�������븴�Ӷ�Ϊ�򵥣����볤��Ϊ4��
`set global validate_password.policy = 0;` 
`set global validate_password.length = 4;`

5. ����Զ�̷����û���`create user 'root'@'%' IDENTIFIED WITH mysql_native_password BY '1234';`
6. ����root�û�Ȩ�ޣ�`grant all on *.* to 'root'@'%';`
7. ��������MySQL��`mysql -u root -p`
8. [ʹ��DataGripԶ������MySQL](https://blog.csdn.net/weixin_42521211/article/details/86546966)
* �鿴IP��ַ�Ͷ˿ں�:`sudo netstat -tap|grep mysql`
* ע�͵������ļ���` sudo vim /etc/mysql/mysql.conf.d/mysqld.cnf`��ע�͵�`bind-address=127.0.0.1`
* ��Ȩ��`grant all privileges on *.* to 'root'@'%'identified by ��������롯 with grant option;`
* ˢ��������Ϣ:`flush privileges;`
* **����SQL**��`service mysql restart`
# �ο�����
* ��MySQL��֪�ػᡷ
* [�������Ա_MySQL���ݿ�����](https://www.bilibili.com/video/BV1Kr4y1i7ru?p=65)
# �����﷨
## SQLͨ���﷨
* SQL�����Ե��л������д���ԷֺŽ�β
* SQL������ʹ�ÿո����������ǿ���Ŀɶ���
* MySQL���ݿⲻ���ִ�Сд���ؼ��ֽ����д
* ע��


```mysql
--ע�����ݻ�#ע������

/*ע������*/
```
## SQL����
- DDL(Data Definition Language): ���ݶ������ԣ������������ݿ�������ݿ⡢���ֶΣ�
- DML(Data Manipulation Language): ���ݲ������ԣ����������ݿ���е����ݽ�����ɾ��
- DQL(Data Query Language): ���ݲ�ѯ���ԣ�������ѯ���ݿ��б�ļ�¼
- DCL(Data Control Language): ���ݿ������ԣ������������ݿ��û����������ݿ�Ŀ���Ȩ��

### ��������
<h5 align="center">��ֵ����</h5>

|����|��С|�з��ŷ�Χ|�޷��ŷ�Χ|
|:--:|:--:|:--:|:--:|
|tinyint|1 byte|(-128,127)|(0,255)|
|smallint|2 bytes|(-32768,32767)|(0,65535)|
|mediumint|3 bytes|(-8388608,8388607)|(0,16777215)|
|int��integer|4 bytes|(-2147483648,2147483647)|(4294967295)|
|bigint|8 bytes|(-2<sup>63</sup> , 2<sup>63</sup>-1)|(0,2<sup>64</sup>-1)|
|float|4 bytes|(-3.402823466E+38,3.402823466351E+38)|(0,1.175494351E-38)��(0,3.402823466E+38)|
|double|8 bytes|(-1.7976931348623157E+308,1.7976931348623457E+308)|(0,2.2250738585072014E-308)��(0,1.7976931348623157E+308)|

<h5 align="center">�ַ�������</h5>

|����|��С|
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

<h5 align="center">��������</h5>

|����|��С|��Χ|��ʽ|
|:--:|:--:|:--:|:--:|
|date|3|1000-01-01��9999-12-31|YYYY-MM-DD|
|time|3|-838:59:59��838:59:59|HH:MM:SS|
|year|1|1901-2155|YYYY|
|datetime|8|1000-01-01 00:00:00��9999-12-31 23:59:59|YYYY-MM-DD HH:MM:SS|
|timestamp|4|1970-01-01 00:00:01��2038-01-19 03:14:07|YYYY-MM-DD HH:MM:SS|

### DDL(���ݶ�������)
#### ���ݿ����
��ѯ�������ݿ⣺
`SHOW DATABASES;`
��ѯ��ǰ���ݿ⣺
`SELECT DATABASE();`
�������ݿ⣺
`CREATE DATABASE [ IF NOT EXISTS ] ���ݿ��� [ DEFAULT CHARSET �ַ���] [COLLATE ������� ];`

> UTF8�ַ�������Ϊ3�ֽڣ���Щ����ռ4�ֽڣ������Ƽ���utf8mb4�ַ���


ɾ�����ݿ⣺
`DROP DATABASE [ IF EXISTS ] ���ݿ���;`
ʹ�����ݿ⣺
`USE ���ݿ���;`

#### �����

��ѯ��ǰ���ݿ����б�
`SHOW TABLES;`
��ѯ��ṹ��
`DESC ����;`
��ѯָ����Ľ�����䣺
`SHOW CREATE TABLE ����;`

* ������
```mysql
CREATE TABLE ����(
	�ֶ�1 �ֶ�1���� [COMMENT �ֶ�1ע��],
	�ֶ�2 �ֶ�2���� [COMMENT �ֶ�2ע��],
	�ֶ�3 �ֶ�3���� [COMMENT �ֶ�3ע��],
	...
	�ֶ�n �ֶ�n���� [COMMENT �ֶ�nע��]
)[ COMMENT ��ע�� ];

#ע������ֶ�nû�ж���

ʾ��������
create table tb_user(
id int comment '���',
name varchar(50) comment '����',
age int comment '����',
gender varchar(1) comment '�Ա�'
)comment '�û���';
```

* �޸ı�

����ֶΣ�
`ALTER TABLE ���� ADD �ֶ��� ����(����) [COMMENT ע��] [Լ��];`
����`ALTER TABLE emp ADD nickname varchar(20) COMMENT '�ǳ�';`

�޸��������ͣ�
`ALTER TABLE ���� MODIFY �ֶ��� ����������(����);`
�޸��ֶ������ֶ����ͣ�
`ALTER TABLE ���� CHANGE ���ֶ��� ���ֶ��� ����(����) [COMMENT ע��] [Լ��];`
������emp���nickname�ֶ��޸�Ϊusername������Ϊvarchar(30)
`ALTER TABLE emp CHANGE nickname username varchar(30) COMMENT '�ǳ�';`

ɾ���ֶΣ�
`ALTER TABLE ���� DROP �ֶ���;`

�޸ı�����
`ALTER TABLE ���� RENAME TO �±���`

ɾ����
`DROP TABLE [IF EXISTS] ����;`
ɾ���������´����ñ�
`TRUNCATE TABLE ����;`

### DML(���ݲ�������)
#### �������
`INSERT INTO ���� (�ֶ���1, �ֶ���2, ...) VALUES (ֵ1, ֵ2, ...);`
ȫ���ֶΣ�
`INSERT INTO ���� VALUES (ֵ1, ֵ2, ...);`

����������ݣ�
`INSERT INTO ���� (�ֶ���1, �ֶ���2, ...) VALUES (ֵ1, ֵ2, ...), (ֵ1, ֵ2, ...), (ֵ1, ֵ2, ...);`
`INSERT INTO ���� VALUES (ֵ1, ֵ2, ...), (ֵ1, ֵ2, ...), (ֵ1, ֵ2, ...);`

> �ַ�����������������Ӧ�ð����������У�
> ��������ݴ�СӦ�����ֶεĹ涨��Χ�ڣ�

#### ���º�ɾ������

�޸����ݣ�
`UPDATE ���� SET �ֶ���1 = ֵ1, �ֶ���2 = ֵ2, ... [ WHERE ���� ];`
�����޸������˵�ʱ��
`update employee set entrydate = '2018-01-01';`


ɾ�����ݣ�
`DELETE FROM ���� [ WHERE ���� ];`

### DQL(���ݲ�ѯ����)
�﷨��
```mysql
SELECT
	�ֶ��б�
FROM
	�����ֶ�
WHERE
	�����б�
GROUP BY
	�����ֶ��б�
HAVING
	�����������б�
ORDER BY
	�����ֶ��б�
LIMIT
	��ҳ����
```
#### ������ѯ
* ��ѯ����ֶ�
`SELECT �ֶ�1,�ֶ�2... FROM ����;`
`SELECT * FROM ����;`

* ���ñ���
`SELECT �ֶ�1 [AS ����1],�ֶ�2 [AS ����2]... FROM ����;`
`SELECT �ֶ�1 [����1],�ֶ�2 [����2]... FROM ����;`

* ȥ���ظ���¼
`SELECT DISTINCT �ֶ��б� FROM ����;`
#### ������ѯ
�﷨��
`SELECT �ֶ��б� FROM ���� WHERE �����б�;`

������

| �Ƚ������          | ����                                        |
| ------------------- | ------------------------------------------- |
| >                   | ����                                        |
| >=                  | ���ڵ���                                    |
| <                   | С��                                        |
| <=                  | С�ڵ���                                    |
| =                   | ����                                        |
| <> �� !=            | ������                                      |
| BETWEEN ... AND ... | ��ĳ����Χ�ڣ�����С�����ֵ��              |
| IN(...)             | ��in֮����б��е�ֵ����ѡһ                |
| LIKE ռλ��         | ģ��ƥ�䣨\_ƥ�䵥���ַ���%ƥ��������ַ��� |
| IS NULL             | ��NULL                                      |

| �߼������         | ����                         |
| ------------------ | ---------------------------- |
| AND �� &&          | ���ң��������ͬʱ������     |
| OR �� &#124;&#124; | ���ߣ������������һ�������� |
| NOT �� !           | �ǣ�����                     |

���ӣ�
```mysql
-- �������30
select * from employee where age = 30;
-- ����С��30
select * from employee where age < 30;
-- С�ڵ���
select * from employee where age <= 30;
-- û�����֤
select * from employee where idcard is null or idcard = '';
-- �����֤
select * from employee where idcard;
select * from employee where idcard is not null;
-- ������
select * from employee where age != 30;
-- ������20��30֮��
select * from employee where age between 20 and 30;
select * from employee where age >= 20 and age <= 30;
-- ������䲻�������鲻���κ���Ϣ
select * from employee where age between 30 and 20;
-- �Ա�ΪŮ������С��30
select * from employee where age < 30 and gender = 'Ů';
-- �������25��30��35
select * from employee where age = 25 or age = 30 or age = 35;
select * from employee where age in (25, 30, 35);
-- ����Ϊ������
select * from employee where name like '__';
-- ���֤���ΪX
select * from employee where idcard like '%X';
```

#### �ۺϺ���
�����ۺϺ�����

| ����  | ����     |
| ----- | -------- |
| count | ͳ������ |
| max   | ���ֵ   |
| min   | ��Сֵ   |
| avg   | ƽ��ֵ   |
| sum   | ���     |

�﷨��
`SELECT �ۺϺ���(�ֶ��б�) FROM ����;`
����
`SELECT count(id) from employee where workaddress = "�㶫ʡ";`


#### �����ѯ

�﷨��
`SELECT �ֶ��б� FROM ���� [ WHERE ���� ] GROUP BY �����ֶ��� [ HAVING �����Ĺ������� ];`

where �� having ������

* ִ��ʱ����ͬ��where�Ƿ���֮ǰ���й��ˣ�������where������������飻having�Ƿ����Խ�����й��ˡ�
* �ж�������ͬ��where���ܶԾۺϺ��������жϣ���having���ԡ�

���ӣ�

```mysql
-- �����Ա���飬ͳ�����Ժ�Ů��������ֻ��ʾ��������������ʾ�ĸ������ĸ���Ů��
select count(*) from employee group by gender;
-- �����Ա���飬ͳ�����Ժ�Ů������
select gender, count(*) from employee group by gender;
-- �����Ա���飬ͳ�����Ժ�Ů�Ե�ƽ������
select gender, avg(age) from employee group by gender;
-- ����С��45�������ݹ�����ַ����
select workaddress, count(*) from employee where age < 45 group by workaddress;
-- ����С��45�������ݹ�����ַ���飬��ȡԱ���������ڵ���3�Ĺ�����ַ
select workaddress, count(*) address_count from employee where age < 45 group by workaddress having address_count >= 3;
```

#### �����ѯ

�﷨��
`SELECT �ֶ��б� FROM ���� ORDER BY �ֶ�1 ����ʽ1, �ֶ�2 ����ʽ2;`

����ʽ��

- ASC: ����Ĭ�ϣ�
- DESC: ����

���ӣ�

```mysql
-- ����������������
SELECT * FROM employee ORDER BY age ASC;
SELECT * FROM employee ORDER BY age;
-- ���ֶ����򣬸�����������������ְʱ�併������
SELECT * FROM employee ORDER BY age ASC, entrydate DESC;
```

**ע������**

����Ƕ��ֶ����򣬵���һ���ֶ�ֵ��ͬʱ���Ż���ݵڶ����ֶν�������
#### ��ҳ��ѯ

�﷨��
`SELECT �ֶ��б� FROM ���� LIMIT ��ʼ����, ��ѯ��¼��;`

���ӣ�

```mysql
-- ��ѯ��һҳ���ݣ�չʾ10��
SELECT * FROM employee LIMIT 0, 10;
-- ��ѯ�ڶ�ҳ
SELECT * FROM employee LIMIT 10, 10;
```

### DCL(���ݿ�������)

#### �����û�

��ѯ�û���

```mysql
USE mysql;
SELECT * FROM user;
```

�����û�:
`CREATE USER '�û���'@'������' IDENTIFIED BY '����';`

�޸��û����룺
`ALTER USER '�û���'@'������' IDENTIFIED WITH mysql_native_password BY '������';`

ɾ���û���
`DROP USER '�û���'@'������';`

���ӣ�

```mysql
-- �����û�test��ֻ���ڵ�ǰ����localhost����
create user 'test'@'localhost' identified by '123456';
-- �����û�test������������������
create user 'test'@'%' identified by '123456';
create user 'test' identified by '123456';
-- �޸�����
alter user 'test'@'localhost' identified with mysql_native_password by '1234';
-- ɾ���û�
drop user 'test'@'localhost';
```

##### ע������

- ����������ʹ�� % ͨ��

#### Ȩ�޿���

����Ȩ�ޣ�

| Ȩ��                | ˵��               |
| ------------------- | ------------------ |
| ALL, ALL PRIVILEGES | ����Ȩ��           |
| SELECT              | ��ѯ����           |
| INSERT              | ��������           |
| UPDATE              | �޸�����           |
| DELETE              | ɾ������           |
| ALTER               | �޸ı�             |
| DROP                | ɾ�����ݿ�/��/��ͼ |
| CREATE              | �������ݿ�/��      |

��ѯȨ�ޣ�
`SHOW GRANTS FOR '�û���'@'������';`

����Ȩ�ޣ�
`GRANT Ȩ���б� ON ���ݿ���.���� TO '�û���'@'������';`

����Ȩ�ޣ�
`REVOKE Ȩ���б� ON ���ݿ���.���� FROM '�û���'@'������';`

##### ע������

- ���Ȩ���ö��ŷָ�
- ��Ȩʱ�����ݿ����ͱ��������� * ����ͨ�䣬��������

## ����
������ָһ�ο���ֱ�ӱ���һ�γ�����õĳ�������
### �ַ�������
| ����  | ����  |
| ------------ | ------------ |
| CONCAT(s1, s2, ..., sn)  | �ַ���ƴ�ӣ���s1, s2, ..., snƴ�ӳ�һ���ַ���  |
| LOWER(str)  | ���ַ���ȫ��תΪСд  |
| UPPER(str)  | ���ַ���ȫ��תΪ��д  |
| LPAD(str, n, pad)  | ����䣬���ַ���pad��str����߽�����䣬�ﵽn���ַ�������  |
| RPAD(str, n, pad)  | ����䣬���ַ���pad��str���ұ߽�����䣬�ﵽn���ַ�������  |
| TRIM(str)  | ȥ���ַ���ͷ����β���Ŀո�  |
| SUBSTRING(str, start, len)  | ���ش��ַ���str��startλ�����len�����ȵ��ַ���  |

ʹ��ʾ����

```mysql
-- ƴ��
SELECT CONCAT('Hello', 'World');
-- Сд
SELECT LOWER('Hello');
-- ��д
SELECT UPPER('Hello');
-- �����
SELECT LPAD('01', 5, '-');
-- �����
SELECT RPAD('01', 5, '-');
-- ȥ���ո�
SELECT TRIM(' Hello World ');
-- ��Ƭ����ʼ����Ϊ1��
SELECT SUBSTRING('Hello World', 1, 5);
```

### ��ֵ����

����������

| ����  | ����  |
| ------------ | ------------ |
| CEIL(x)  | ����ȡ��  |
| FLOOR(x)  | ����ȡ��  |
| MOD(x, y)  | ����x/y��ģ  |
| RAND() | ����0~1�ڵ������ |
| ROUND(x, y) | �����x����������ֵ������yλС�� |
```sql
#����һ����λ���������֤��
select lpad(round(rand()*1e6,0),6,'0');
```

### ���ں���

���ú�����

| ����  | ����  |
| ------------ | ------------ |
| CURDATE()  | ���ص�ǰ����  |
| CURTIME()  | ���ص�ǰʱ��  |
| NOW()  | ���ص�ǰ���ں�ʱ��  |
| YEAR(date)  | ��ȡָ��date�����  |
| MONTH(date)  | ��ȡָ��date���·�  |
| DAY(date)  | ��ȡָ��date������  |
| DATE_ADD(date, INTERVAL expr type)  | ����һ������/ʱ��ֵ����һ��ʱ����expr���ʱ��ֵ  |
| DATEDIFF(date1, date2)  | ������ʼʱ��date1�ͽ���ʱ��date2֮�������  |

���ӣ�

```mysql
-- DATE_ADD
SELECT DATE_ADD(NOW(), INTERVAL 70 YEAR);
```

### ���̺���

���ú�����

| ����  | ����  |
| ------------ | ------------ |
| IF(value, t, f)  | ���valueΪtrue���򷵻�t�����򷵻�f  |
| IFNULL(value1, value2)  | ���value1��Ϊ�գ�����value1�����򷵻�value2  |
| CASE WHEN [ val1 ] THEN [ res1 ] ... ELSE [ default ] END  | ���val1Ϊtrue������res1��... ���򷵻�defaultĬ��ֵ  |
| CASE [ expr ] WHEN [ val1 ] THEN [ res1 ] ... ELSE [ default ] END  | ���expr��ֵ����val1������res1��... ���򷵻�defaultĬ��ֵ  |

���ӣ�

```mysql
select
	name,
	(case when age > 30 then '����' else '����' end)
from employee;
select
	name,
	(case workaddress when '������' then 'һ�߳���' when '�Ϻ���' then 'һ�߳���' else '���߳���' end) as '������ַ'
from employee;
```

## Լ��

���ࣺ

| Լ��  | ����  | �ؼ���  |
| ------------ | ------------ | ------------ |
| �ǿ�Լ��  | ���Ƹ��ֶε����ݲ���Ϊnull  | NOT NULL  |
| ΨһԼ��  | ��֤���ֶε��������ݶ���Ψһ�����ظ���  | UNIQUE  |
| ����Լ��  | ������һ�����ݵ�Ψһ��ʶ��Ҫ��ǿ���Ψһ  | PRIMARY KEY  |
| Ĭ��Լ��  | ��������ʱ�����δָ�����ֶε�ֵ�������Ĭ��ֵ  | DEFAULT  |
| ���Լ����8.0.1�汾��  | ��֤�ֶ�ֵ����ĳһ������  | CHECK  |
| ���Լ��  | ����������ͼ������֮�佨�����ӣ���֤���ݵ�һ���Ժ�������  | FOREIGN KEY  |

Լ���������ڱ����ֶ��ϵģ������ٴ�����/�޸ı��ʱ�����Լ����

### ����Լ��

| Լ������  | �ؼ���  |
| ------------ | ------------ |
| ����  | PRIMARY KEY  |
| �Զ�����  | AUTO_INCREMENT  |
| ��Ϊ��  | NOT NULL  |
| Ψһ  | UNIQUE  |
| �߼�����  | CHECK  |
| Ĭ��ֵ  | DEFAULT  |

���ӣ�

```mysql
create table user(
	id int primary key auto_increment,
	name varchar(10) not null unique,
	age int check(age > 0 and age < 120),
	status char(1) default '1',
	gender char(1)
);
```

### ���Լ��
���������������ű������֮�佨������,�Ӷ���֤���ݵ�һ���Ժ������ԡ�

��������

```mysql
CREATE TABLE ����(
	�ֶ��� �ֶ�����,
	...
	[CONSTRAINT] [�������] FOREIGN KEY(����ֶ���) REFERENCES ����(��������)
);
ALTER TABLE ���� ADD CONSTRAINT ������� FOREIGN KEY (����ֶ���) REFERENCES ����(��������);

-- ����
alter table emp add constraint fk_emp_dept_id foreign key(dept_id) references dept(id);
```

ɾ�������
`ALTER TABLE ���� DROP FOREIGN KEY �����;`

#### ɾ��/������Ϊ

| ��Ϊ  | ˵��  |
| ------------ | ------------ |
| NO ACTION  | ���ڸ�����ɾ��/���¶�Ӧ��¼ʱ�����ȼ��ü�¼�Ƿ��ж�Ӧ����������������ɾ��/���£���RESTRICTһ�£�  |
| RESTRICT  | ���ڸ�����ɾ��/���¶�Ӧ��¼ʱ�����ȼ��ü�¼�Ƿ��ж�Ӧ����������������ɾ��/���£���NO ACTIONһ�£�  |
| CASCADE  | ���ڸ�����ɾ��/���¶�Ӧ��¼ʱ�����ȼ��ü�¼�Ƿ��ж�Ӧ������������Ҳɾ��/����������ӱ��еļ�¼  |
| SET NULL  | ���ڸ�����ɾ��/���¶�Ӧ��¼ʱ�����ȼ��ü�¼�Ƿ��ж�Ӧ�����������������ӱ��и����ֵΪnull��Ҫ����������Ϊnull��  |
| SET DEFAULT  | �����б��ʱ���ӱ������Ϊһ��Ĭ��ֵ��Innodb��֧�֣�  |

����ɾ��/������Ϊ��
`ALTER TABLE ���� ADD CONSTRAINT ������� FOREIGN KEY (����ֶ�) REFERENCES ������(�����ֶ���) ON UPDATE ��Ϊ ON DELETE ��Ϊ;`

## ����ѯ
### ����ϵ

- һ�Զࣨ���һ��
- ��Զ�
- һ��һ

#### һ�Զ�

������������Ա��
��ϵ��һ�����Ŷ�Ӧ���Ա����һ��Ա����Ӧһ������
ʵ�֣��ڶ��һ�����������ָ��һ��һ��������

#### ��Զ�

������ѧ����γ�
��ϵ��һ��ѧ������ѡ���ſγ̣�һ�ſγ�Ҳ���Թ����ѧ��ѡ��
ʵ�֣������������м���м�����ٰ�������������ֱ������������

#### һ��һ

�������û����û�����
��ϵ��һ��һ��ϵ�������ڵ����֣���һ�ű�Ļ����ֶη���һ�ű��У����������ֶη�����һ�ű��У�����������Ч��
ʵ�֣�������һ�������������������һ���������������������ΪΨһ�ģ�UNIQUE��

### ��ѯ

�ϲ���ѯ���ѿ���������չʾ������Ͻ������
`select * from employee, dept;`

> �ѿ���������������A���Ϻ�B���ϵ��������������ڶ���ѯʱ����Ҫ������Ч�ĵѿ�������

������Ч�ѿ�������
`select * from employee, dept where employee.dept = dept.id;`

### �����Ӳ�ѯ

�����Ӳ�ѯ�������ű����Ĳ���

��ʽ�����ӣ�
`SELECT �ֶ��б� FROM ��1, ��2 WHERE ���� ...;`

��ʽ�����ӣ�
`SELECT �ֶ��б� FROM ��1 [ INNER ] JOIN ��2 ON �������� ...;`

��ʽ���ܱ���ʽ��

���ӣ�

```mysql
-- ��ѯԱ���������������Ĳ��ŵ�����
-- ��ʽ
select e.name, d.name from employee (as) e, dept (as) d where e.dept = d.id;
-- ��ʽ
select e.name, d.name from employee (as) e (inner) join dept (as) d on e.dept = d.id;
```

### �����Ӳ�ѯ

�������ӣ�
��ѯ����������ݣ��Լ����ű�����������
`SELECT �ֶ��б� FROM ��1 LEFT [ OUTER ] JOIN ��2 ON ���� ...;`
�൱�ڲ�ѯ��1���������ݣ�������1�ͱ�2������������

�������ӣ�
��ѯ�ұ��������ݣ��Լ����ű�����������
`SELECT �ֶ��б� FROM ��1 RIGHT [ OUTER ] JOIN ��2 ON ���� ...;`

���ӣ�

```mysql
-- ��
select e.*, d.name from employee as e left (outer) join dept as d on e.dept = d.id;

select d.name, e.* from dept d left (outer) join emp e on e.dept = d.id;  -- �����������������Ч��һ��
-- ��
select d.name, e.* from employee as e right outer join dept as d on e.dept = d.id;
```


### �����Ӳ�ѯ

��ǰ������������Ӳ�ѯ�������ӱ���ʹ�ñ����

�﷨��
`SELECT �ֶ��б� FROM ��A ����A JOIN ��A ����B ON ���� ...;`

�����Ӳ�ѯ�������������Ӳ�ѯ��Ҳ�����������Ӳ�ѯ

���ӣ�

```mysql
-- ��ѯԱ�����������쵼������
select a.name '��������',b.name '�쵼����' from emp a,emp b where a.managerid=b.id;
-- û���쵼��Ҳ��ѯ����
select a.name, b.name from employee a left join employee b on a.manager = b.id;
```

### ���ϲ�ѯ union, union all

�Ѷ�β�ѯ�Ľ���ϲ����γ�һ���µĲ�ѯ��

�﷨��

```mysql
SELECT �ֶ��б� FROM ��A ...
UNION [ALL]
SELECT �ֶ��б� FROM ��B ...
```

#### ע������

- ���ű���������ֶ�������Ҫ����һ��
- UNION ALL �����ظ������UNION ����
- ���ϲ�ѯ��ʹ��orЧ�ʸߣ�����ʹ����ʧЧ

### �Ӳ�ѯ

SQL�����Ƕ��SELECT��䣬��νǶ�ײ�ѯ���ֳ��Ӳ�ѯ��
`SELECT * FROM t1 WHERE column1 = ( SELECT column1 FROM t2);`
**�Ӳ�ѯ�ⲿ���������� INSERT / UPDATE / DELETE / SELECT ���κ�һ��**

�����Ӳ�ѯ������Է�Ϊ��

- �����Ӳ�ѯ���Ӳ�ѯ���Ϊ����ֵ��
- ���Ӳ�ѯ���Ӳ�ѯ���Ϊһ�У�
- ���Ӳ�ѯ���Ӳ�ѯ���Ϊһ�У�
- ���Ӳ�ѯ���Ӳ�ѯ���Ϊ���ж��У�

�����Ӳ�ѯλ�ÿɷ�Ϊ��

- WHERE ֮��
- FROM ֮��
- SELECT ֮��

#### �����Ӳ�ѯ

�Ӳ�ѯ���صĽ���ǵ���ֵ�����֡��ַ��������ڵȣ���
���ò�������- < > > >= < <=

���ӣ�

```mysql
-- ��ѯ���۲�����Ա��
select id from dept where name = '���۲�';
-- �������۲�����ID����ѯԱ����Ϣ
select * from employee where dept = 4;
-- �ϲ����Ӳ�ѯ��
select * from employee where dept = (select id from dept where name = '���۲�');

-- ��ѯxxx��ְ֮���Ա����Ϣ
select * from employee where entrydate > (select entrydate from employee where name = 'xxx');
```

#### ���Ӳ�ѯ

���صĽ����һ�У������Ƕ��У���

���ò�������

| ������  | ����  |
| ------------ | ------------ |
| IN  | ��ָ���ļ��Ϸ�Χ�ڣ���ѡһ  |
| NOT IN  | ����ָ���ļ��Ϸ�Χ��  |
| ANY  | �Ӳ�ѯ�����б��У�������һ�����㼴��  |
| SOME  | ��ANY��ͬ��ʹ��SOME�ĵط�������ʹ��ANY  |
| ALL  | �Ӳ�ѯ�����б������ֵ����������  |

���ӣ�

```mysql
-- ��ѯ���۲����г���������Ա����Ϣ
select * from employee where dept in (select id from dept where name = '���۲�' or name = '�г���');
-- ��ѯ�Ȳ��������˹��ʶ��ߵ�Ա����Ϣ
select * from employee where salary > all(select salary from employee where dept = (select id from dept where name = '����'));
-- ��ѯ���з�������һ�˹��ʸߵ�Ա����Ϣ
select * from employee where salary > any (select salary from employee where dept = (select id from dept where name = '�з���'));
```

#### ���Ӳ�ѯ

���صĽ����һ�У������Ƕ��У���
���ò�������=, <, >, IN, NOT IN

���ӣ�

```mysql
-- ��ѯ��xxx��н�ʼ�ֱ���쵼��ͬ��Ա����Ϣ
select * from employee where (salary, manager) = (12500, 1);
select * from employee where (salary, manager) = (select salary, manager from employee where name = 'xxx');
```

#### ���Ӳ�ѯ

���صĽ���Ƕ��ж���
���ò�������IN

���ӣ�

```mysql
-- ��ѯ��xxx1��xxx2��ְλ��н����ͬ��Ա��
select * from employee where (job, salary) in (select job, salary from employee where name = 'xxx1' or name = 'xxx2');
-- ��ѯ��ְ������2006-01-01֮���Ա�������䲿����Ϣ
select e.*, d.* from (select * from employee where entrydate > '2006-01-01') as e left join dept as d on e.dept = d.id;
```

## ����
���壺��һ������ļ��ϣ���һ�����ɷָ�Ĺ�����λ�����������в�����Ϊһ������һ����ϵͳ�ύ�����������󣬼���Щ����Ҫôͬʱ�ɹ���Ҫôͬʱʧ�ܡ�

����������

```mysql
-- 1. ��ѯ�����˻����
select * from account where name = '����';
-- 2. �������˻����-1000
update account set money = money - 1000 where name = '����';
-- �������������Ǯ���ٵ�������Ǯû������
ģ��sql������
-- 3. �������˻����+1000
update account set money = money + 1000 where name = '����';

-- �鿴�����ύ��ʽ
SELECT @@AUTOCOMMIT;
-- ���������ύ��ʽ��1Ϊ�Զ��ύ��0Ϊ�ֶ��ύ��������ֻ�Ե�ǰ�Ự��Ч
SET @@AUTOCOMMIT = 0;
-- �ύ����
COMMIT;
-- �ع�����
ROLLBACK;

-- �����ֶ��ύ����������Ϊ��
select * from account where name = '����';
update account set money = money - 1000 where name = '����';
update account set money = money + 1000 where name = '����';
commit;
```

������ʽ����

��������
`START TRANSACTION �� BEGIN;`
�ύ����
`COMMIT;`
�ع�����
`ROLLBACK;`

����ʵ����

```mysql
start transaction;
select * from account where name = '����';
update account set money = money - 1000 where name = '����';
update account set money = money + 1000 where name = '����';
commit;
```

### �Ĵ�����ACID

- ԭ����(Atomicity)�������ǲ��ɷָ����С������λ��Ҫôȫ���ɹ���Ҫôȫ��ʧ��
- һ����(Consistency)���������ʱ������ʹ�������ݶ�����һ��״̬
- ������(Isolation)�����ݿ�ϵͳ�ṩ�ĸ�����ƣ���֤�����ڲ����ⲿ��������Ӱ��Ķ�������������
- �־���(Durability)������һ���ύ��ع����������ݿ��е����ݵĸı�������õ�

### ��������

| ����  | ����  |
| ------------ | ------------ |
| ���  | һ�����������һ������û�ύ������  |
| �����ظ���  | һ�������Ⱥ��ȡͬһ����¼�������ζ�ȡ�����ݲ�ͬ  |
| �ö�  | һ��������������ѯ����ʱ��û�ж�Ӧ�������У������ٲ�������ʱ���ַ������������Ѿ�����  |


����������뼶��

| ���뼶��  | ���  | �����ظ���  | �ö�  |
| ------------ | ------------ | ------------ | ------------ |
| Read uncommitted  | ��  | ��  | ��  |
| Read committed  | ��  | ��  | ��  |
| Repeatable Read(Ĭ��)  | ��  | ��  | ��  |
| Serializable  | ��  | ��  | ��  |

- �̱�ʾ�ڵ�ǰ���뼶���¸���������
- Serializable ������ͣ�Read uncommitted ������ߣ����ݰ�ȫ�����

�鿴������뼶��
`SELECT @@TRANSACTION_ISOLATION;`
����������뼶��
`SET [ SESSION | GLOBAL ] TRANSACTION ISOLATION LEVEL {READ UNCOMMITTED | READ COMMITTED | REPEATABLE READ | SERIALIZABLE };`
SESSION �ǻỰ���𣬱�ʾֻ��Ե�ǰ�Ự��Ч��GLOBAL ��ʾ�����лỰ��Ч

# ����ƪ
## �洢����
### MySQL��ϵ�ṹ

![](picture/MySQL��ϵ�ṹ.png)
* ���Ӳ�
���ϲ���һЩ�ͻ��˺����ӷ�����Ҫ�����һЩ���������Ӵ�����Ȩ��֤����صİ�ȫ������������Ҳ��Ϊ��ȫ�����ÿ���ͻ�����֤�������еĲ���Ȩ�ޡ�

* �����
�ڶ���ܹ���Ҫ��ɴ�����ĺ��ķ����ܣ���SQL�ӿڣ�����ɻ���Ĳ�ѯ��SQL�ķ������Ż����������ú�����ִ�С����п�洢����Ĺ���Ҳ����һ��ʵ�֣��� ���̡������ȡ�

* �����
�洢���������ĸ�����MySQL�����ݵĴ洢����ȡ��������ͨ��API�ʹ洢�������ͨ�š���ͬ�洢�����в�ͬ�Ĺ��ܣ������Ϳ��Ը����Լ���������ѡȡ���ʵĴ洢���档

* �洢��
��Ҫ�ǽ����ݴ洢���ļ�ϵͳ֮�ϣ��������洢����Ľ���

### �洢�������
�洢������Ǵ洢���ݡ���������������/��ѯ���ݵȼ�����ʵ�ַ�ʽ���洢�����ǻ��ڱ�����ǻ��ڿ�ģ����Դ洢����Ҳ���Ա���Ϊ�����档Ĭ�ϴ洢������InnoDB��

```mysql
-- ��ѯ�������
show create table account;
-- ����ʱָ���洢����
CREATE TABLE ����(
	...
) ENGINE=INNODB;
-- �鿴��ǰ���ݿ�֧�ֵĴ洢����
show engines;
```

### InnoDB

InnoDB ��һ�ּ�˸߿ɿ��Ժ͸����ܵ�ͨ�ô洢���棬�� MySQL 5.5 ֮��InnoDB ��Ĭ�ϵ� MySQL ���档

�ص㣺

- DML ������ѭ ACID ģ�ͣ�֧��**����**
- **�м���**����߲�����������
- ֧��**���**Լ������֤���ݵ������Ժ���ȷ��

�ļ���

- xxx.ibd: xxx���������InnoDB �����ÿ�ű����Ӧ����һ����ռ��ļ����洢�ñ�ı�ṹ��frm��sdi�������ݺ�������

������innodb_file_per_table���������ű���һ����ռ仹��ÿ�ű��Ӧһ����ռ�

֪ʶ�㣺

�鿴 Mysql ������
`show variables like 'innodb_file_per_table';`

Windows��MySQL���ݴ��Ŀ¼��`C:\ProgramData\MySQL\MySQL Server 8.0\Data`
��idb�ļ���ȡ��ṹ���ݣ�
����cmd���У�
`ibd2sdi xxx.ibd`

InnoDB �߼��洢�ṹ��
![InnoDB�߼��洢�ṹ](picture/InnoDB�߼��洢�ṹ.png)

* ��ռ䣺InnoDB�洢�����߼��ṹ����߲㣬ibd�ļ���ʵ���Ǳ�ռ��ļ����ڱ�ռ��п��԰������Segment�Ρ�
* �Σ���ռ����ɸ�������ɵģ������Ķ������ݶΡ������Ρ��ع��εȡ�InnoDB�ж��ڶεĹ�����������������ɣ�����Ҫ��Ϊ������ƣ�һ�����а����������
* �������Ǳ�ռ�ĵ�Ԫ�ṹ��ÿ�����Ĵ�СΪ1M��Ĭ������£��洢����ҳ��СΪ16K����һ������һ����64��������ҳ��
* ҳ��ҳ�����������С��Ԫ��ҳҲ��InnoDB�洢������̹������С��Ԫ��ÿ��ҳ�Ĵ�СĬ��Ϊ16KB��Ϊ�˱�֤ҳ�������ԣ�InnoDB�洢����ÿ�δӴ�������4һ5������
* �У�InnoDB�洢�����������еģ�Ҳ����˵�����ǰ��н��д�ŵģ���ÿһ���г��˶����ʱ��ָ�����ֶ����⣬���������������ֶΡ�


### MyISAM

MyISAM �� MySQL ���ڵ�Ĭ�ϴ洢���档

�ص㣺

- ��֧�����񣬲�֧�����
- ֧�ֱ�������֧������
- �����ٶȿ�

�ļ���

- xxx.sdi: �洢��ṹ��Ϣ
- xxx.MYD: �洢����
- xxx.MYI: �洢����

### Memory

Memory ����ı������Ǵ洢���ڴ��еģ���Ӳ�����⡢�ϵ������Ӱ�죬ֻ�ܽ���Щ����Ϊ��ʱ��򻺴�ʹ�á�

�ص㣺

- ������ڴ��У��ٶȿ�
- hash������Ĭ�ϣ�

�ļ���

- xxx.sdi: �洢��ṹ��Ϣ

### �洢�����ص�

| �ص�  | InnoDB  | MyISAM  | Memory  |
| ------------ | ------------ | ------------ | ------------ |
| �洢����  | 64TB  | ��  | ��  |
| ����ȫ  | ֧��  | -  | -  |
| ������  | ����  | ����  | ����  |
| B+tree����  | ֧��  | ֧��  | ֧��  |
| Hash����  | -  | -  | ֧��  |
| ȫ������  | ֧�֣�5.6�汾֮��  | ֧��  | -  |
| �ռ�ʹ��  | ��  | ��  | N/A  |
| �ڴ�ʹ��  | ��  | ��  | �е�  |
| ���������ٶ�  | ��  | ��  | ��  |
| ֧�����  | ֧��  | -  | -  |

�����⣺InnoDB������MyISAM���������
* InnoDB֧������MyISAM��֧������
* InnoDB֧�������ͱ�����MyISAMֻ֧�ֱ���
* InnoDB֧�������MyISAM��֧�����
### �洢�����ѡ��

��ѡ��洢����ʱ��Ӧ�ø���Ӧ��ϵͳ���ص�ѡ����ʵĴ洢���档���ڸ��ӵ�Ӧ��ϵͳ�������Ը���ʵ�����ѡ����ִ洢���������ϡ�

- InnoDB: ���Ӧ�ö�������������бȽϸߵ�Ҫ���ڲ���������Ҫ�����ݵ�һ���ԣ����ݲ������˲���Ͳ�ѯ֮�⣬�������ܶ�ĸ��¡�ɾ���������� InnoDB �ǱȽϺ��ʵ�ѡ��
- MyISAM: ���Ӧ�����Զ������Ͳ������Ϊ����ֻ�к��ٵĸ��º�ɾ�����������Ҷ�����������ԡ�������Ҫ�󲻸ߣ�������洢�����Ƿǳ����ʵġ�
- Memory: ���������ݱ������ڴ��У������ٶȿ죬ͨ��������ʱ�����档Memory ��ȱ���ǶԱ�Ĵ�С�����ƣ�̫��ı��޷��������ڴ��У������޷��������ݵİ�ȫ��

�����е��㼣�������ʺ�ʹ�� MyISAM ���棬�����ʺ�ʹ�� Memory ���档

## ����
### ����
�����ǰ��� MySQL **��Ч��ȡ����**��**���ݽṹ������**��������֮�⣬���ݿ�ϵͳ��ά���������ض������㷨�����ݽṹ����Щ���ݽṹ��ĳ�ַ�ʽ���ã�ָ�����ݣ������Ϳ�������Щ���ݽṹ��ʵ�ָ߼���ѯ�㷨���������ݽṹ����������

�ŵ㣺
- ������ݼ���Ч�ʣ��������ݿ��IO�ɱ�
- ͨ�������ж����ݽ������򣬽�����������ĳɱ�������CPU������

ȱ�㣺
- ������Ҳ��Ҫռ�ÿռ��
- �����������˲�ѯЧ�ʣ��������˸��µ��ٶȣ����� INSERT��UPDATE��DELETE


### �����ṹ
| �����ṹ  | ����  |
| ------------ | ------------ |
| B+Tree  | ������������ͣ��󲿷����涼֧��B+������  |
| Hash  | �ײ����ݽṹ���ù�ϣ��ʵ�֣�ֻ�о�ȷƥ�������еĲ�ѯ����Ч����֧�ַ�Χ��ѯ  |
| R-Tree(�ռ�����)  | �ռ������� MyISAM �����һ�������������ͣ���Ҫ���ڵ���ռ��������ͣ�ͨ��ʹ�ý���  |
| Full-Text(ȫ������)  | ��һ��ͨ��������������������ƥ���ĵ��ķ�ʽ�������� Lucene, Solr, ES  |

| ����  | InnoDB  | MyISAM  | Memory  |
| ------------ | ------------ | ------------ | ------------ |
| B+Tree����  | ֧��  | ֧��  | ֧��  |
| Hash����  | ��֧��  | ��֧��  | ֧��  |
| R-Tree����  | ��֧��  | ֧��  | ��֧��  |
| Full-text  | 5.6�汾��֧��  | ֧��  | ��֧��  |

���ӻ���վ��https://www.cs.usfca.edu/~galles/visualization/Algorithms.html
### ������
#### B-Tree
![](picture/������.png)

Ϊ�˽���������⣬����ʹ�� B-Tree �ṹ��
B-Tree (��·ƽ�������) ��һ����������max-degree��ָһ���ڵ���ӽڵ������Ϊ5��5�ף��� b-tree Ϊ����ÿ���ڵ����洢4��key��5��ָ�룩

![](picture/B-Tree.png)

#### B+Tree
![](picture/B+Tree.png)

�� B-Tree ������

- ���е����ݶ��������Ҷ�ӽڵ�
- Ҷ�ӽڵ��γ�һ����������

MySQL �������ݽṹ�Ծ���� B+Tree �������Ż�����ԭ B+Tree �Ļ����ϣ�����һ��ָ������Ҷ�ӽڵ������ָ�룬���γ��˴���˳��ָ��� B+Tree�����������ʵ����ܡ�

![MySQL_B+Tree](picture/MySQL-B+.png)

#### Hash
��ϣ�������ǲ���һ����hash�㷨������ֵ������µ�hashֵ��ӳ�䵽��Ӧ�Ĳ�λ�ϣ�Ȼ��洢��hash���С�
�����������������ֵ��ӳ�䵽һ����ͬ�Ĳ�λ�ϣ����ǾͲ�����hash��ͻ��Ҳ��Ϊhash��ײ��������ͨ�������������

![Hash](picture/Hash����ԭ��ͼ.png)

�ص㣺

- Hash����ֻ�����ڶԵȱȽϣ�=��in������֧�ַ�Χ��ѯ��betwwn��>��<��...��
- �޷�������������������
- ��ѯЧ�ʸߣ�ͨ��ֻ��Ҫһ�μ����Ϳ����ˣ�Ч��ͨ��Ҫ���� B+Tree ����

�洢����֧�֣�

- Memory
- InnoDB: ��������Ӧhash���ܣ�hash�����Ǵ洢������� B+Tree ������ָ���������Զ�������

#### ������
���⣺Ϊʲô InnoDB �洢����ѡ��ʹ�� B+Tree �����ṹ��

- ����ڶ��������㼶���٣�����Ч�ʸ�
- ���� B-Tree��������Ҷ�ӽڵ㻹�Ƿ�Ҷ�ӽڵ㣬���ᱣ�����ݣ���������һҳ�д洢�ļ�ֵ���٣�ָ��Ҳ���ż��٣�Ҫͬ������������ݣ�ֻ���������ĸ߶ȣ��������ܽ���
- ����� Hash ������B+Tree ֧�ַ�Χƥ�估�������

### ��������

| ����  | ����  | �ص�  | �ؼ���  |
| ------------ | ------------ | ------------ | ------------ |
| ��������  | ����ڱ�����������������  | Ĭ���Զ�������ֻ����һ��  | PRIMARY  |
| Ψһ����  | ����ͬһ������ĳ�������е�ֵ�ظ�  | �����ж��  | UNIQUE  |
| ��������  | ���ٶ�λ�ض�����  | �����ж��  |   |
| ȫ������  | ȫ���������ҵ����ı��еĹؼ��ʣ������ǱȽ������е�ֵ  | �����ж��  | FULLTEXT  |

�� InnoDB �洢�����У����������Ĵ洢��ʽ���ֿ��Է�Ϊ�������֣�

| ����  | ����  | �ص�  |
| ------------ | ------------ | ------------ |
| �ۼ�����(Clustered Index)  | �����ݴ洢��������һ�飬�����ṹ��Ҷ�ӽڵ㱣����������  | �����У�����ֻ��һ��  |
| ��������(Secondary Index)  | �������������ֿ��洢�������ṹ��Ҷ�ӽڵ�������Ƕ�Ӧ������  | ���Դ��ڶ��  |

![������ʾ](picture/������ʾ.png)

������̣�
1. �����Ǹ���name�ֶν��в�ѯ�������ȸ���name='Arm'��name�ֶεĶ��������н���ƥ����ҡ������ڶ���������ֻ�ܲ��ҵ�Arm��Ӧ������ֵ10��
2. ���ڲ�ѯ���ص�������*�����Ի���Ҫ��������ֵ10�����ۼ������в���10��Ӧ�ļ�¼�������ҵ�10��Ӧ����row��
3. �����õ���һ�е����ݣ�ֱ�ӷ��ؼ���

> �ر��ѯ���뵽���������в������ݣ��ҵ�����ֵ��Ȼ���ٵ��ۼ������и�������ֵ����ȡ���ݡ�

#### ������
1\. ���� SQL ��䣬�ĸ�ִ��Ч�ʸߣ�Ϊʲô��

```mysql
select * from user where id = 10;
select * from user where name = 'Arm';
-- ��ע��idΪ������name�ֶδ�����������
```

�𣺵�һ����䣬��Ϊ�ڶ�����Ҫ�ر��ѯ���൱���������衣

2\. InnoDB ���������� B+Tree �߶�Ϊ���٣�

�𣺼���һ�����ݴ�СΪ1k��һҳ�п��Դ洢16�����������ݡ�InnoDB ��ָ��ռ��6���ֽڵĿռ䣬��������Ϊbigint��ռ���ֽ���Ϊ8.
�ɵù�ʽ��`n * 8 + (n + 1) * 6 = 16 * 1024`������ 8 ��ʾ bigint ռ�õ��ֽ�����n ��ʾ��ǰ�ڵ�洢��key��������(n + 1) ��ʾָ����������key��һ���������nԼΪ1170��

������ĸ߶�Ϊ2����ô���ܴ洢�����������Ϊ��`1171 * 16 = 18736`��
������ĸ߶�Ϊ3����ô���ܴ洢�����������Ϊ��`1171 * 1171 * 16 = 21939856`��

### �﷨
����������
`CREATE [ UNIQUE | FULLTEXT ] INDEX index_name ON table_name (index_col_name, ...);`
������� CREATE ���治���������Ͳ������򴴽����ǳ�������

�鿴������
`SHOW INDEX FROM table_name;`

ɾ��������
`DROP INDEX index_name ON table_name;`

������

```mysql
-- name�ֶ�Ϊ�����ֶΣ����ֶε�ֵ���ܻ��ظ���Ϊ���ֶδ�������
create index idx_user_name on tb_user(name);
-- phone�ֻ����ֶε�ֵ�ǿգ���Ψһ��Ϊ���ֶδ���Ψһ����
create unique index idx_user_phone on tb_user (phone);
-- Ϊprofession, age, status������������
create index idx_user_pro_age_stat on tb_user(profession, age, status);
-- Ϊemail�������ʵ�������������ѯЧ��
create index idx_user_email on tb_user(email);

-- ɾ������
drop index idx_user_email on tb_user;
```

### SQL���ܷ���
#### SQLִ��Ƶ��
�鿴������״̬��Ϣ��`show [session|global] status`
�鿴��ǰ���ݿ�insert��update��delete��select�ķ���Ƶ��
```mysql
-- session �鿴��ǰ�Ự��
-- global ��ѯȫ�����ݣ�
show global status like 'Com_______';# 7��_
```
#### ����ѯ��־
����ѯ��־��¼������ִ��ʱ�䳬��ָ������(long_query_time����λ���룬Ĭ��10��)������SQL������־

MYSQL������ѯ��־Ĭ�Ϲرգ�����ͨ��slow_query_log����(�ļ�λ��:`/etc/my.cnf`)
```mysql
#��������־��ѯ����
slow_query_log=1
#��������־ʱ��Ϊ2s��SQL���ִ��ʱ�䳬��2s���ͻᱻ��¼������ѯ��־
long_query_time=2
```
������ɻ���Ҫ����MYSQL��������`systemctl restart mysqld`

����־���·����`/var/lib/mysql/localhost-slow.log`

#### Profile����
�鿴��ǰMYSQL�Ƿ�֧��profile������`select @@have_profiling;`

����session/global�����profiling��`set profiling=1;`

�鿴profiling�Ƿ��Ѿ��򿪣�`select @@profiling;`

�鿴ÿһ��SQL�ĺ�ʱ�����`show profiles;`

�鿴ָ��query_id��SQL�������׶εĺ�ʱ�����`show profile for query query_id;`

�鿴ָ��query_id��SQL���CPUʹ�������`show profiles cpu for query query_id;`


