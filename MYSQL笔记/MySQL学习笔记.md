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