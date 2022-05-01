# MySQL��װ
[Window�˰�װ](https://www.php.cn/mysql-tutorials-454993.html)
[Linux�˰�װ](https://www.runoob.com/mysql/mysql-install.html)
# �ο�����
* ��MySQL��֪�ػᡷ
* [�������Ա_MySQL���ݿ�����](https://b23.tv/BV1Kr4y1i7ru)
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