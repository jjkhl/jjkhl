<h1 align="center">图解HTTP笔记</h1>

参考笔记地址：

* <https://www.cnblogs.com/DM428/p/11210863.html>
* <https://zhuanlan.zhihu.com/p/64476601>

# 第一章 了解Web及网络基础

## 1.1 使用HTTP协议访问Web

Web使用HTTP(HyperText Transfer Protocol，超文本传输协议)作为规范，完成从客户端到服务端等一系列运作流程。

## 1.3 网络基础TCP/IP

### 1.3.2 TCP/IP的分层管理

* **应用层**，决定向用户提供应用服务时的通信活动。HTTP、FTP（File Transfer Protocol，文件传输协议）和 DNS（Domain Name System，域名解析系统）都属于该层。
* **传输层**，相对于上一层的应用层，该层提供处于网络连接中的两台计算机的数据传输。该层协议主要是 TCP（Transmission Control Protocol） 和 UDP（User Data Protocol）。
* **网络层**，用于处理网络上流动的数据包（数据传输的最小单位），该层规定了通过怎样的路径到达对方计算机，并把数据传送给对方。该层协议主要是 IP 协议和 ARP（Address Solution Protocol） 协议。
* **数据链路层**，用于处理网络连接的硬件部分，包括操作系统、设备驱动等，硬件上的范畴基本都在链路层的范围内。该层主要协议为以太网协议（Ethernet）。

> 关于网络分层的更多内容：<https://www.cnblogs.com/DM428/p/7029467.html>

### 1.3.3 TCP/IP通信传输流

![](picture/httptransfer.png)

利用TCP/IP通信时，会通过分层顺序与对方进行通信。发送方的数据流从应用层往下走，接收方的数据流从数据链路层往上走。

发送端步骤：

* 作为发送端的客户端在应用层(HTTP协议)发送一个想看某个Web页面的HTTP请求。
* 在传输层(TCP协议)把从应用层收到的数据(HTTP请求报文)进行分割，并在各个报文上打上标记序号及端口号后转发给网络层。
* 在网络层(IP协议)，增加作为通信目的地的MAC地址后转发给链路层。这样一来发送网络端的通信请求就准备齐全了。

接收端步骤：

* 作为接收端的服务器在链路层接收到数据，按序往上层发送，一直到应用层。当传输到应用层，才能算真正接收到由客户端发送过来的HTTP请求。

## 1.4 与HTTP关系密切的协议：IP、TCP和DNS

**1. IP协议**
IP 协议负责网络传输，处于网络层。IP 不是 IP 地址，我们通常说的 IP 是一种协议。IP 地址指明了节点被分配到的地址，<strong style="color:red">MAC 地址是网卡所属的固定地址</strong>，每块网卡出厂时，都有一个世界独一无二的MAC地址，长度是48个二进制位，用 12个十六进制位数表示。IP 地址可以和 MAC 地址配对，但是<strong style="color:red">同一台机器 IP 地址可能会变，MAC 是固定不变的</strong>。

IP 间的通信依赖 MAC 地址，实际生活中同一局域网内的网络通信比较少，大部分都是广域网的通信，数据需要经过多个节点路由的转发才能到达目的地。而在中转时，会利用下一站中转设备的 MAC 地址来搜索下一个中转目标。这时会采用 ARP 协议（Address Resolution Protocol），根据对方的 IP 地址即可查出对应的 MAC 地址，但是两台设备必须在同一个子网内。
ARP是一种用以解析地址的协议，根据通讯方的IP地址就可以反查出对应的MAC地址。

数据在网络中的传输类似于现实生活中的快递运输，中转设备就类似于物流中转中心。快递到达一个中转站之后，中转站会判断下一个中转站的地址然后继续进行派送，直到到达客户所在的中转站。

![互联网中的传输方式](picture/tcphandshaking.png)
**2. TCP协议**

TCP 位于传输层，提供可靠的字节流服务。

字节流服务（Byte Stream Service）是指为了传输方便，把大块的数据切割成以报文段（segment）为单位的数据包进行管理。TCP 的可靠之处在于它会确保数据被送到了接收方。

为了确保数据被准确无误地送到了接收方，TCP 采用了三次握手（three-way handshaking）的策略。握手过程中包含了两个重要的标志（flag）——SYN（synchronize，同步请求）和 ACK（acknowledgement）。

发送端会先发送一个带有 SYN 的数据包给对方，接收端接收到数据之后返回一个 带有 SYN/ACK 标志的数据包给发送端，最后发送端再传回一个带有 ACK 标志的数据包表示“握手”结束。如果握手意外结束，那么 TCP 协议会再次以相同的顺序发送相同的数据包。

![三次握手](picture/三次握手.png)

**3. DNS**
DNS 也位于应用层，它提供域名解析服务。能够把域名解析为 IP 地址。

域名是指例如`www.baidu.com`的网址
IP地址是指一组数字的组合
![DNS](picture/DNS过程.png)

**4. 各种协议与HTTP之间的关系**
![协议之间关系](picture/relationship.png)

### 1.7 URI和URL

#### URI

URI(Uniform Resource Identifier，统一资源标识符)

* Uniform，规定统一的格式可方便处理不同的资源，而不用根据上下文环境来识别资源指定的访问方式，另外加入新的协议（http、ftp）也更容易。
* Resource，指任何可标识的东西。不仅限于文档、图片或服务。
* Identifier，表示可标识的对象，也称为标识符。

除了 HTTP 外，URI 还可以使用 mailto、ftp、telnet 等协议方案。

<strong style="color:red">URI 用字符串标识某一互联网资源，而 URL 用字符串标识资源的地点。所以 URL 是 URI 的子集</strong>。

URI示例：

```
ftp://ftp.is.co.za/rfc/rfc1808.txt
http://www.ietf.org/rfc/rfc2396.txt
ldap://[2001:db8::7]/c=GB?objectClass?one
mailto:John.Doe@example.com
news:comp.infosystems.www.servers.unix
tel:+1-816-555-1212
telnet://192.0.2.16:80/
urn:oasis:names:specification:docbook:dtd:xml:4.1.2
```

#### URL

URL(Uniform Resource Locator，统一资源定位符)
**URL格式：**
![URL格式](picture/urlformat.png)

* **登录信息(认证)** 指定用户名密码作为从服务端获取资源时的登录信息，此项可选。
* **服务器地址**，可以是域名、IP。
* **服务器端口号**，指定服务器连接的网络端口号，此项可选，省略时用默认端口号。
* **带层次的文件路径**，指定服务器上资源的文件路径。
* **查询字符串**，通过查询字符串可以传入参数。
* **片段标识符**，指定已获取资源中的子资源（文档内的某个位置）。

# 第二章 简单的HTTP协议

两台机器使用HTTP协议进行通信，在一条通讯线路上必定有一端为客户端，另外一端是服务端。

请求访问文本或图像等资源的一端成为客户端，而提供资源响应的一端成为服务器端。

HTTP协议规定：请求从客户端发出，最后服务器端响应该请求并返回。

## 2.2 请求和响应报文的组成

![HTTP流程](picture/HTTP过程.png)

从客户端发送给的请求报文内容如下：

```
GET /index.htm HTTP/1.1
Host: hackr.jp
```

其中，GET 表示请求访问服务器的类型，称为方法（method）。随后的字符串`/index.htm`表示 请求访问的资源对象，也叫作请求 URI。最后的 HTTP/1.1 表示所使用的 HTTP 版本号，用于提示客户端所使用的 HTTP 版本。

所以上面这段请求头表示使用 GET 方法请求`hackr.jp`服务器上的 index.htm 资源，客户端使用的 HTTP 版本是 1.1。

总结：**请求报文是由请求方法、请求 URI、协议版本、可选的请求首部字段和内容实体构成的**。

![请求报文](picture/requestcontent.png)

接收到请求的服务器，返回了如下内容：

```
HTTP/1.1 200 OK
Date: Tue, 10 Jul 2012 06:50:15 GMT
Content-Length: 362
Content-Type: text/html
<html>
......
```

其中，HTTP/1.1 表示服务器对应的 HTTP 版本；后面的 `200 OK` 表示请求的处理结果的状态码（status code）。下一行表示响应创建的时间，是响应首部字段（header field）的一个属性。空一行之后的内容表示资源主体的实体（entity body）。

总结：**响应报文基本上由协议版本、状态码（表示请求成功或者失败的数字代码）、用以解释状态码的原因短语、可选的响应首部字段以及实体主体构成**。

![响应报文](picture/responsecontent.png)

## 2.3 HTTP是不保存状态(无状态)的协议

HTTP协议自身不对请求和相应之间的通信状态进行保存。每次有新的请求建立时，就会有对应的响应产生，与之前或者之后的请求都没有任何关系。

HTTP 的无状态特点，既有好处也有坏处。好处在于无状态的特点使得 HTTP 不用维护客户端状态，大大简化了协议内容和服务器的工作，确保了协议的可伸缩性。坏处在于随着 Web 的发展，网站应用越来越复杂，无状态的协议需要通过其他手段维持客户端状态（登录信息），比如 Cookie 技术，就是从 HTTP 1.1 开始引入的维持状态的手段。

## 2.5 告知服务器意图的HTTP方法

HTTP 1.1主要包含了以下可以使用的方法：

* GET：请求访问已被URI识别的资源。指定的资源经服务器端解析后返回响应内容。

示例：

```
请求：GET /index.html HTTP/1.1
     Host:www.hackr.jp
     If-Modified-Since:Thu,12 Jul 2012 07:30:00 GMT
响应：只返回2012年7月12日7点39分以后更新过的index.html页面资源。如果没有内容更新，则以状态码304 Not Modified作为响应返回
```

* POST：传输实体的主体。一般使用POST代替GET方法，POST方法的主要目的不是获取响应的主题内容

示例：

```
请求：POST /submit.cgi HTTP/1.1
     Host:www.hackr.jp
     Content-Length:1560(1560字节的数据)
响应：返回submti.cgi接收数据的处理结果
```

* PUT：传输文件。就像 FTP 的文件上传一样，要求在请求报文的主体中包含文件内容，然后保存到 URI 指定位置。由于 HTTP 1.1 的 PUT 方法不带验证机制，任何人都可以上传文件，所以具有安全隐患，一般不采用 PUT 方法。

示例：

```
请求：PUT /example.html HTTP/1.1
     Host:www.hackr.jp
     Content-Type:text/html
     Content-Length:1560(1560字节的数据)
响应：响应返回状态码204 No Content(比如：该html已存在于服务器上)
```

* HEAD：获取报文首部，不返回报文主体部分。用于确认URI的有效性及资源更新的日期时间等。

示例：

```
请求：HEAD /index.html HTTP/1.1
     Host:www.hackr.jp
响应：返回index.html有关的响应首部
```

* DELETE：删除文件，是与PUT相反的方法。DELETE方法按请求URI删除指定的资源。但由于HTTP/1.1的DELETE方法和PUT方法一样不带验证机制，一般也不采用该方法。

示例：

```
请求：DELETE /example.html HTTP/1.1
     Host:www.hackr.jp
响应：响应返回状态码204 No Content(比如：该html已从该服务器上删除)
```

* OPTIONS：查询针对请求URI指定的资源支持的方法。

示例：

```
请求：OPTIONS * HTTP/1.1
     Host:www.hackr.jp
响应：HTTP/1.1 200 OK
     Allow:GET,POST,HEAD,OPTIONS(返回服务器支持的方法)
```

* TRACER：追踪路径。发送请求时，在请求首部字段中加入 `Max-Forwards` 字段，值为数字，每经过一个服务器，该字段就会减一，当到达某个使该字段为 0 的服务器时，就会返回状态码为 200 OK 的响应。通过 TRACE 方法可以查询发送出去的请求是怎样被加工/篡改的。TRACE 方法本身使用场景较少，而且存在跨站追踪攻击的隐患，所以使用场景更加少了。

示例：

```
请求：TRACE /HTTP/1.1
     Host:hackr.jp
     Max-Forwards:2
响应：HTTP/1.1 200 OK
     Content-Type:message/http
     Content-Length:1024

     TRACE /HTTP/1.1
     Host:hackr.jp
     Max-Forwards:2(返回响应包含请求内容)
```

* CONEECT：使用隧道协议与代理服务器进行TCP通信。主要使用SSL(Secure Sockets Layer,安全套接层)和TLS(Transport Layer Security,传输层安全)协议把通信内容加密后经过网络隧道传输。

示例：

```
请求：CONNECT proxy.hackr.jp:8080 HTTP/1.1
     Host:proxy.hackr.jp
响应：HTTP/1.1 200 OK(之后进入网络隧道)
```

需要注意：方法名区分大小写，一定要使用大写字母
![HTTP1.0/HTTP2.0](picture/HTTP1.0和HTTP1.1支持的方法.png)

## 2.7 持久连接节省通信量

我们知道 HTTP 协议基于 TCP 协议，而 TCP 协议每次建立之前都会进行“三次握手”，所以如果每次发送 HTTP 请求都要建立 TCP 连接的话，会造成过多的“握手”浪费服务器资源。而 HTTP 协议的初始版本中，每次 HTTP 通信都需要重新建立 TCP 请求，这是一个很大的缺点。

### 2.7.1 持久连接

为了解决上述问题，HTTP 1.1 引入了持久连接（HTTP Persistent Connections，也成为 HTTP keep-alive 或者 HTTP connection reuse）。持久连接的特点是只要任意一方没有提出断开 TCP 连接，就会一直维持 TCP 的连接状态。

持久连接的好处在于减少了 TCP 连接的重复建立和断开所造成的额外开销，减轻了服务器的负载。**在 HTTP 1.1 中，所有的连接默认都是持久连接**。

### 2.7.2 管线化

以前发送请求后需要等待响应之后才能发送下一个请求，但是管线化技术能不用等待响应就能发送下一个请求，这样能够做到多个请求并行发送，大大减少了页面加载的时间。

## 2.8 使用Cookie的状态管理

Cookie技术通过在请求和响应报文中写入Cookie信息来控制客户端的状态。

Cookie 会根据从服务端发送的响应报文内的一个叫做 `Set-Cookie` 的首部字段信息，通知客户端保存 Cookie。当下次客户端再往该服务器发送请求时，客户端会自动在请求报文中加入 Cookie 值后发送出去。

服务器端发现客户端发送过来的Cookie后，会去检查究竟是从哪一个客户端发来的连接请求，然后对比服务器上的记录，最后得到之前的状态信息。

请求报文(无Cookie信息的状态)：

```
GET /reader/ HTTP/1.1
Host: hackr.jp
首部字段内没有Cookie相关的信息
```

响应报文(服务器端生成Cookie信息)：

```
HTTP/1.1 200 OK
Date: Thu, 12 Jul 2012 07:12:20 GMT
Server: Apache
<Set-Cookie: sid=1342077140226724; path=/; expires=Wed,
10-Oct-12 07:12:20 GMT>
Content-Type: text/plain; charset=UTF-8
```

携带有 Cookie 信息的请求报文：

```
GET /image/ HTTP/1.1
Host: hackr.jp
Cookie: sid=1342077140226724
```

# 第三章 HTTP报文内的HTTP信息

## 3.1 HTTP报文

用于 HTTP 协议交互的信息被称为 HTTP 报文，客户端的 HTTP 报文叫做请求报文，服务器端的叫做响应报文

HTTP 报文大致可分为报文首部和报文主体两块，两者通过空行划分（CR + LF），通常并不一定要有报文主体

![httpBody](picture/httpbody.png)

## 3.2 请求报文及响应报文的结构

![报文结构](picture/bodystructure.png)

* **请求行** 包含用于请求的方法，请求 URL 和 HTTP 版本。
* **状态行** 包含表明响应结果的状态码，原因短语和 HTTP 版本。
* **首部字段** 包含表示请求和响应的各种条件和属性的各类首部。一般包括通用首部、请求首部、响应首部和实体首部。
* **其他** 包含一些未在 RFC 中定义的首部（Cookie 等）。

## 3.3 编码提升传输速率

HTTP 在传输时可以按照原始数据直接传输，也可以预先将数据进行压缩后再传输。编码压缩后可以减少传输的数据量，能够提升传输速率，但是会压缩过程会消耗更多的 CPU 资源。

### 3.3.1 报文主体和实体主体的差异

* **报文(message)** 是HTTP通信中的基本单位，由8位组字节流组成，通过HTTP通信传输
* **实体(entity)** 作为请求或响应的有效载荷数据(补充项)被传输，其内容由实体首部和实体主体组成

HTTP 报文的主体用于传输实体的主体（请求或者响应的）。

**通常情况下，报文主体就是实体主体。但是在进行编码压缩时，实体主体部分会被编码，导致与报文主体不同**。

### 3.3.2 压缩传输的内容编码

内容编码指明应用在实体内容上的编码方式，并保持实体信息原样压缩。内容编码后的实体由客户端接收并负责编码。

常用的内容编码有以下几种：

* gzip（GNU zip）
* compress（UNIX 系统的标准压缩）
* deflate（zlib）
* identity（不进行编码）

### 3.3.3 分割发送的分块传输编码

在传送大容量数据时，通过把数据分割成多块，能够让浏览器逐步显示页面。这种功能成为**分块传输编码（Chunked Transfer Coding）**。

分块传输会将实体主体分割成多个块（chunk）来传输，每一块都用十六进制来标记块的大小，而实体主体的最后一块会使用“0（CR+LF）”来标记。

## 3.4 发送多种数据的多部分对象集合

邮件附件能够同时传送多种内容的数据，是因为采用了 MIME（Multipurpose Internet Mail Extensions，多用途因特网邮件扩展）机制，它允许邮件处理文本、图片、视频等多种类型的数据。相应的，HTTP 也采纳了部分多部分对象集合。

多部分对象集合包含的对象如下：

* **multipart/form-data**：在 Web 表单上传时使用。
* **multipart/byteranges**：状态码 206（Partial Content，部分内容）响应报文包含了多个范围的内容时使用。

我们通过指定 `Content-Type` 请求头来使用多部分对象结合。

## 3.5 获取部分内容的范围请求

指定范围发送的请求叫做**范围请求**

对于一份 10000 字节大小的资源，可以通过范围请求一次只请求 5001 ～ 10000 字节的资源。

执行范围请求时，会通过 Range 首部字段来指定资源的 byte 范围，比如：

* 5000 - 10000 字节：

  ```
  Range: bytes=5001-10000
  ```

* 5000 字节之后的所有内容：

  ```
  Range: bytes=5000-
  ```

* 从一开始到 3000 字节和 5000 字节到 7000 字节的内容：

  ```
  Range: bytes=0-3000,5000-7000
  ```

针对范围请求，响应会返回状态码为 **206 Partial Content** 的响应报文。

对于多重范围的范围请求，响应会在首部字段 `Content-Type` 表明 `multipart/byteranges` 后返回。

![范围请求](picture/范围请求.png)

## 3.6 内容协商返回最合适的内容

内容协商机制是指客户端和服务器端就响应的资源内容进行交涉，然后提供给客户端最为合适的资源。

内容协商会以语言、字符集、编码方式等为基准判断响应的资源。

包含在请求报文中的一些首部字段就是服务端响应的判断标准：

* **Accept**
* **Accept-Charset**
* **Accept-Encoding**
* **Accept-Language**
* **Content-Language**

# 第四章 返回结果的HTTP状态码
## 4.1 状态码告知从服务器端返回的请求结果
状态码的职责是当客户端向服务器端发送请求时，描述返回的请求结果。

状态码从其含以上可以分为五种：

|      | 类别                             | 原因短语                   |
| ---- | -------------------------------- | -------------------------- |
| 1XX  | Informational（信息性状态码）    | 接受的请求正在处理         |
| 2XX  | Success（成功状态码）            | 请求正常处理完毕           |
| 3XX  | Redirection（重定向状态码）      | 需要进行附加操作以完成请求 |
| 4XX  | Client Error（客户端错误状态码） | 服务器无法处理请求         |
| 5XX  | Server Error（服务端错误状态码） | 服务器处理请求出错         |

## 4.2 2XX成功
### 4.2.1 200 OK
表示从客户端发来的请求在服务器端被正常处理了。
### 4.2.2 204 No Content
服务器接收的请求已成功处理，但没有返回的内容，响应报文中不包含实体的主体部分。
### 4.2.3 206 Partial Content
客户端进行了范围请求，而服务器端成功执行了这部分的GET请求。响应报文中包含由Content-Range指定范围的实体内容。

## 4.3 3XX 重定向
3XX 响应结果表示浏览器需要执行某些特殊的处理以正确处理请求。
### 4.3.1 301 Moved Permanently
永久性重定向。
该状态码表示请求的资源已被分配了新的URI，以后应使用资源现在所指的URI。新的URI会在HTTP响应头中的Location首部字段指定。

示例：`http://example.com/sample`
上述URI的指定资源路径最后忘记添加斜杠'/'，就会产生301状态码。

### 4.3.2 302 Found
临时性重定向。
该状态码表示请求的资源已被分配了新的URI，希望用户(本次)能使用新的URI访问。
### 4.3.3 303 See Other
该状态码表示由于请求对应的资源存在其它URI，应使用GET方法定向获取请求的资源。
### 4.3.4 304 Not Modified
该状态码表示客户端发送附带条件的请求时（GET 请求包含 If-Match，If-Modified-Since，If-None-Match，If-Range，If-Unmodified-Since 中任一首部）服务端允许访问请求访问资源，但因为请求没有满足条件，所以发生 304 Not Modified 重定向，直接使用客户端缓存的资源。

### 4.3.5 307 Temporary Redirect
临时重定向，**307 会遵守浏览器标准，不会从 POST 变成 GET**。但是对于处理请求的行为时，不同浏览器还是会出现不同的情况。

## 4.4 4XX 客户端错误
4XX的响应结果表示客户端是发生错误的原因所在。
### 4.4.1 400 Bad Request
该状态码表示请求报文中存在语法错误。
但错误发生时，需修改请求的内容后再次发送请求。
### 4.4.2 401 Unauthorized
该状态码表示发送的请求需要由HTTP认证(BASIC认证、DIGEST认证)的认证信息。
### 4.4.3 403 Forbidden
该状态码表示对请求资源的访问被服务器拒绝了，服务器端没有必要给出详细理由，但是可以在响应报文实体的主体中进行说明。
### 4.4.4 404 Not Found
该状态码表示服务器上无法找到请求的资源，也可以表示服务器端拒绝请求且不想说明理由时。
## 4.5 5XX服务器错误
5XX响应结果表示服务器本身发生错误。
### 4.5.1 500 Internal Server Error
该状态码表示服务器端在执行请求时发生了错误，也有可能是Web应用存在bug或某些临时故障。
### 4.5.2 503 Service Unavailable
该状态码表示服务器暂时处于超负载或正在进行停机维护，现在无法处理请求。

# 第五章 与HTTP协作的Web服务器
一台Web服务器可搭建多个独立域名的Web网址，也可以作为通信路径上的中转服务器提升传输效率。
## 5.1 用单台虚拟主机实现多个域名
HTTP/1.1规范允许一台HTTP服务器搭建多个Web站点。

基于虚拟主机的功能，可以只使用一台物理机实现多个域名的网站部署。

在互联网上，域名通过 DNS 域名解析系统可以映射到具体的 IP 上，<strong style="color:red">多个域名可以映射到同一个 IP，但是一个域名只能映射到一个 IP</strong>。如果服务器想知道请求来自于哪个域名，可以通过请求头中的 Host 首部字段获取

## 5.2 通信数据转发程序：代理、网关、隧道
### 5.2.1 代理
代理是一种有转发功能的应用程序，它是服务器端和客户端的“中间人”。接收由客户端阿松的请求并转发给服务器，同时也接收服务器返回的响应并转发给客户端。

![WebProxy](picture/webproxy.png)

代理服务器的基本行为就是接收客户端发送的请求后转发给其它服务器。代理不改变请求的URI，会直接发送给前方持有资源的目标服务器。

持有资源实体的服务器被称为源服务器。从源服务器返回的响应经过代理服务器后再传回客户端。

![multihttpproxy](picture/multihttpproxy.png)

使用代理服务器的理由：
* 利用缓存计数减少网络带宽的流量
* 组织内部针对特定网址的访问控制
* 以获取访问日志为主要目的

代理的使用方式以是否使用缓存和是否修改报文作为基准分类。
1. **缓存代理**： 代理转发响应时，缓存代理会预先将资源的副本保存在代理服务器上，但代理再接收到对相同资源的请求时，就可以直接返回之前缓存的资源。
2. **透明代理**：转发请求或响应时，不对报文做任何加工的代理类型。反之，不透明代理会对报文内容进行加工的代理。
### 5.2.2 网关
网关是转发其它服务器通信数据的服务器，接收从客户端发送来的请求时，它就像自己拥有资源服务器一样对请求进行处理。

![HTTP的转换](picture/httpgateway.png)

网关的工作机制和代理十分相似，但网关能使通信线路上的服务器提供非HTTP协议服务。

利用网关能提高通信的安全性，因为可以在客户端和网关之间的通信线路上加密以确保连接的安全性。
比如：
* 网关可以连接数据库，使用SQL语句查询数据
* 在Web购物网站上进行信用卡结算时，网卡可以和信用卡结算系统联动

### 5.2.3隧道
隧道是在很远的客户端和服务器两者之间进行中转，并保持双方通信连接的应用程序。

隧道可以按照要求建立起一条与其他服务器的通信线路，届时使用 SSL 等加密手段进行通信。**隧道的目的是确保客户端与服务端能够进行安全的通信**。

隧道本身不会去解析HTTP请求。也就是说，请求保持原样中转给之后的服务器。隧道会在通信双方断开连接时结束。

## 5.3 保存资源的缓存
缓存是指代理服务器或客户端本地磁盘内保存的资源副本。

利用缓存可减少对源服务器的访问，因此也就节省了通信流量和通信时间。

缓存服务器是代理服务器的一种，并归类在缓存代理类型中，也就是说当代理转发从服务器返回的响应时，代理服务器将会保存一份资源的副本。

![httpcache](./picture/httpcache.png)

缓存服务器的优势在于利用缓存可以避免多次从源服务器转发资源。
### 5.3.1 缓存的有效期

即使存在缓存，也会因为客户端的要求、缓存的有效期等因素向源服务器确认资源的有效性。若缓存失效，缓存服务器会再次向源服务器获取“新的”资源。

### 5.3.2 客户端的缓存
缓存不仅可以存在于缓存服务器内，还可以存在客户端浏览器中。

和缓存服务器相同的一点是，当判定缓存过期后，会向源服务器确认资源的有效性。若判断浏览器缓存失效，浏览器会再次请求新资源。


# 第六章 HTTP首部
## 6.1 HTTP报文首部

![HTTP请求报文结构](picture/httpstructure.png)

HTTP请求报文由方法、URI、HTTP版本、HTTP首部字段等部分构成。
下面的示例是访问`http://hackjr.jp`时，请求的报文首部信息：
```
GET / HTTP/1.1
Host: hackr.jp
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:13.0) Gecko/2010010
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*; q=0
Accept-Language: ja,en-us;q=0.7,en;q=0.3
Accept-Encoding: gzip, deflate
DNT: 1
Connection: keep-alive
If-Modified-Since: Fri, 31 Aug 2007 02:02:20 GMT
If-None-Match: "45bae1-16a-46d776ac"
Cache-Control: max-age=0
```
![HTTP响应报文结构](picture/httpresstructure.png)
HTTP 响应报文由 HTTP 版本、状态码（数字和原因短语）、HTTP 首部字段三部分组成。
下面示例为之前请求访问`http://hackjr.jp`返回的响应报文首部信息：
```
HTTP/1.1 304 Not Modified
Date: Thu, 07 Jun 2012 07:21:36 GMT
Server: Apache
Connection: close
Etag: "45bae1-16a-46d776ac"
```

## 6.2 HTTP首部字段
### 6.2.1 HTTP首部字段结构
HTTP首部字段传递重要信息，结构示例：`首部字段名：字段值`
例如，在HTTP首部以Content-Type 这个字段来表示报文主体的对象类型，`Content-Type: text/html`。

另外，有些首部字段可以有多个值：`Keep-Alive: timeout=15, max=100`

### 6.2.2 4种HTTP首部字段类型

按实际用途非为四种类型：
* 通用首部字段：请求报文和响应报文都会使用的首部
* 请求首部字段：从客户端向服务器端发送请求报文时使用的首部。补充了请求的附加内容、客户端信息、响应内容相关优先级等信息。
* 响应首部字段：从服务器端向客户端返回响应报文时使用的首部。补充了响应的附加内容，也会要求客户端附加额外的内容信息。
* 实体首部字段：针对请求报文和响应报文的实体部分使用的首部。补充了资源内容更新时间等与实体有关的信息。

### 6.2.4 HTTP/1.1 首部字段一览
#### 通用首部字段

| 首部字段名        | 说明                       |
| ---- | -------------------------- |
| Cache-Control     | 控制缓存的行为             |
| Connection        | 逐跳首部、连接的管理       |
| Date              | 创建报文的日期时间         |
| Pragma            | 报文指令                   |
| Trailer           | 报文末尾的首部一览         |
| Transfer-Encoding | 指定报文主体的传输编码方式 |
| Upgrade           | 升级为其他协议             |
| Via               | 代理服务器的相关信息       |
| Warning           | 错误通知                   |

#### 请求首部字段

| 首部字段名          | 说明                                            |
| ------------------- | ----------------------------------------------- |
| Accept              | 用户代理可处理的媒体类型                        |
| Accept-Charset      | 优先的字符集                                    |
| Accept-Encoding     | 优先的内容编码                                  |
| Accept-Language     | 优先的语言（自然语言）                          |
| Authorization       | Web 信息认证                                    |
| Expect              | 期待服务器的特定行为                            |
| From                | 用户的电子邮箱地址                              |
| Host                | 请求资源所在的服务器                            |
| If-Match            | 比较实体标记（ETag）                            |
| If-Modified-Since   | 比较资源的更新时间                              |
| If-None-Match       | 比较实体标记（与 If-Match 相反）                |
| If-Range            | 资源未更新时发送实体 Byte 的范围请求            |
| If-Unmodified-Since | 比较资源的更新时间（与 If-Modified-Since 相反） |
| Max-Forwards        | 最大传输逐跳数                                  |
| Proxy-Authorization | 代理服务器要求客户端的认证信息                  |
| Range               | 实体的字节范围请求                              |
| Referer             | 对请求中 URI 的原始获取方                       |
| TE                  | 传输编码的优先级                                |
| User-Agent          | HTTP 客户端程序的信息                           |

#### 响应首部字段 

| 首部字段名         | 说明                         |
| ------------------ | ---------------------------- |
| Accept-Ranges      | 是否接受字节范围请求         |
| Age                | 推算资源创建经过时间         |
| ETag               | 资源的匹配信息               |
| Location           | 令客户端重定向至指定 URI     |
| Proxy-Authenticate | 代理服务器对客户端的认证信息 |
| Retry-After        | 对再次发起请求的时机要求     |
| Server             | HTTP 服务器的安装信息        |
| Vary               | 代理服务器缓存的管理信息     |
| WWW-Authenticate   | 服务器对客户端的认证信息     |

#### 实体首部字段

| 首部字段名       | 说明                   |
| ---------------- | ---------------------- |
| Allow            | 资源可支持的 HTTP 方法 |
| Content-Encoding | 实体主体适用的编码方式 |
| Content-Language | 实体主体的自然语言     |
| Content-Length   | 实体主体的大小（字节） |
| Content-Location | 替代对应资源的 URI     |
| Content-MD5      | 实体主体的报文摘要     |
| Content-Range    | 实体主体的位置范围     |
| Content-Type     | 实体主体的媒体类型     |
| Expires          | 实体主体过期的日期时间 |
| Last-Modified    | 资源的最后修改时间     |

#### 6.2.5 非HTTP/1.1首部字段
Cookie、Set-Cookie和Content-Disposition等其它在RFC中定义的首部字段统一归纳在RFC4229 HTTP Header Field Registrations中。

#### 6.2.6End-to-end首部和Hop-by-hop首部
HTTP首部字段将定义为缓存代理和非缓存代理的行为，分为两种类型：
* **端到端首部**：分在此类别的首部会转发给请求/响应对应的最终接收目标，且必须保存在由缓存生成的响应中，另外规定它必须被转发。
* **逐跳首部**：分在此类别的首部只对单词转发有效，会因通过缓存或代理而不再转发。HTTP/1.1及其之后版本，如果需要使用逐跳首部，则需提供Connection首部字段。

下面这些字段都属于逐跳首部字段，除此之外都为端到端首部
* Connection
* Keep-Alive
* Proxy-Authenticate
* Proxy-Authorization
* Trailer
* TE
* Transfer-Encoding
* Upgrade

### 6.3 HTTP/1.1 通用首部字段
#### 6.3.1 Cache-Control
该指令能操作缓存的工作机制。

Cache-Control 的指令参数是可选的，多个指令之间通过逗号分开。该首部字段在请求和响应时都可以使用。

**Cache-Control 可用指令如下：**

请求指令：

| 指令             | 参数   | 说明                             |
| ---------------- | ------ | -------------------------------- |
| no-cache         | 无     | 强制向源服务器再次验证           |
| no-store         | 无     | 不缓存请求或响应的任何内容       |
| max-age=[秒]     | 必需   | 响应的最大 age 值                |
| max-stale(=[秒]) | 可省略 | 接受已过期的响应                 |
| min-fresh=[秒]   | 必需   | 期望在指定的时间内的响应仍然有效 |
| no-transform     | 无     | 代理不可更改媒体类型             |
| only-if-cached   | 无     | 从缓存获得资源                   |
| cache-extension  | -      | 新指令标记（token）              |

响应指令：

| 指令             | 参数   | 说明                                           |
| ---------------- | ------ | ---------------------------------------------- |
| public           | 无     | 可向任意方提供响应的缓存                       |
| private          | 可省略 | 仅向特定用户返回响应                           |
| no-cache         | 可省略 | 缓存前必须确认其有效性                         |
| no-store         | 无     | 不缓存请求或响应的任何内容                     |
| no-transform     | 无     | 代理不可更改媒体类型                           |
| must-revalidate  | 无     | 可缓存但必须再向源服务器进行确认               |
| proxy-revalidate | 无     | 要求中间缓存服务器对缓存的响应有效性再进行确认 |
| max-age=[秒]     | 必需   | 响应的最大 age 值                              |
| s-maxage=[秒]    | 必需   | 公共缓存服务器响应的最大 age 值                |
| cache-extension  | -      | 新指令标记（token）                            |
----

规定是否缓存的指令：

**public 指令**

```
Cache-Control: public
```

当指定使用 public 指令时，则明确表明其他用户也可利用缓存。

**private 指令**

```
Cache-Control: private
```

当指定 private 指令后响应只以特定的用户作为对象，当该对象向服务器发起请求时，服务器会返回缓存的资源。

**no-cache 指令**

```
Cache-Control: no-cache
```

该指令的目的是为了<strong style="color:red">防止使用过期的缓存资源</strong>。

**如果客户端发送的请求中包含 no-cache 指令**，则表示客户端将不会接受过期的缓存过的响应。于是，中间的代理服务器必须把请求转发给源服务器。

**如果服务器返回的响应中包含 no-cache 指令**，那么缓存服务器不能对资源进行缓存，源服务器以后也将不再对缓存服务器请求中提出的资源有效性进行确认，且禁止其对资源响应进行缓存操作。

****

控制可执行缓存对象的指令：

**no-store 指令**

```
Cache-Control: no-store
```

当使用 no-store 指令时，暗示请求或响应中包含机密信息。

因此该指令规定缓存不能在本地存储请求或响应的任一部分。

**注意**

> 从字面意义来说，很容易把 no-cache 理解为不缓存，但事实上 no-cache 代表的是不缓存过期的资源，缓存会向源服务器确认有效性后再处理资源。no-store 才是真正的不进行缓存。

****

指定缓存期限和认证的指令：

**s-maxage 指令**

```
Cache-Control: smax-age=604800（单位：秒）
```

该指令功能和 max-age 相同，不同点是 s-maxage 指令只适合于供多位用户使用的公共缓存服务器(一般指代理)。

当使用 smax-age 指令之后，直接会忽略 Expires 字段及 max-age 指令的处理。

**max-age 指令**

```
Cache-Control: max-age=604800（单位：秒）
```

**当客户端发送的请求中包含 max-age 指令时**，如果判定缓存资源的缓存时间数值比指定的数值更小，那么客户端就接收缓存的资源。另外，当指定 max-age 值为 0，那么缓存服务器通常需要将请求转发给源服务器（相当于是 no-cache）。

**当服务器返回的响应中包含 max-age 指令时**，缓存服务器将不对资源的有效性再做确认，而 max-age 数值代表的是资源保存为缓存的最长时间。

**应用 HTTP/1.1 版本的缓存的服务器遇到同时存在 Expires 首部字段的情况时，会优先处理 max-age 指令，而忽略掉 Expires 首部字段。而应用 HTTP/1.0 版本的服务器则恰恰相反**。

**min-fresh 指令**

```
Cache-Control: min-fresh=60（单位：秒）
```

min-fresh 指令要求缓存服务器返回至少还未过指定时间的缓存资源（即指定时间过后仍然是未过期的资源）。

**max-stale 指令**

```
Cache-Control: max-stale=3600（单位：秒）
```

使用 max-stale 表示接受过期的缓存资源，后面的值表示具体过期的时长，表示响应不能已经过时超过该给定的时间。如果不传递数值，则表示无论经过多久，客户端都能够接受。

**only-if-cached 指令**

```
Cache-Control: only-if-cached
```

使用该指令表示客户端仅在缓存服务器本地缓存目标资源的情况下才会要求其返回。即只接受已缓存的资源，并且不用向源服务器检查资源的有效性。若代理服务器本地缓存无响应，则返回 504 Gateway Timeout。

**must-revalidate 指令**

```
Cache-Control: must-revalidate
```

使用该指令，代理会向源服务器再次验证即将返回的响应缓存目前是否仍然有效。

使用 must-revalidate 指令会忽略 max-stale 指令。

**proxy-revalidate 指令**

```
Cache-Control: proxy-revalidate
```

该指令要求所有的缓存服务器在接收到客户端带有该指令的请求返回响应之前，必须再验证资源的有效性。

**no-transform 指令**

```
Cache-Control: no-transform
```

该指令规定无论在请求还是响应中缓存都不能改变实体的媒体类型。

这样可以防止缓存或者代理压缩图片等类似操作。

#### 6.3.2 Connection 

这个首部字段有一下两个作用：

* 控制不再转发给代理的首部自担
* 管理持久连接

```
Connection: 不再转发的首部字段名
```

这条语句就表示指定的首部字段不再转发到下一级服务器（可能是代理）。

![httpconn](./picture/httpconn.png)

除了上面的功能以外，该首部还可以管理持久连接：

```
Connection: close
```

该指令明确指定断开当前连接。（HTTP/1.1 的所有连接默认都是长连接）

```
Connection: Keep-Alive
```

以上指令明确指定当前连接为长连接。（适用于 HTTP/1.1 版本之前）


#### 6.3.3 Date
该字段表明创建HTTP报文的日期和时间。

HTTP/1.1协议使用RFC1123规定：`Date: Tue, 03 Jul 2012 04:40:59 GMT`
之前HTTP版本使用RFC850规定：`Date: Tue, 03-Jul-12 04:40:59 GMT`

与C标准库内的asctime()函数输出格式一致：`Date: Tue Jul 03 04:40:59 2012`

#### 6.3.4 Pragma
该字段是HTTP/1.1之前版本的遗留字段，仅作为与HTTP/1.0的向后兼容而定义。

```
Pragma: no-cache

Cache-Control: no-cache
```

#### 6.3.5 Trailer
该字段事先说明在报文主体后记录了哪些首部字段，可用于 HTTP/1.1 版本分块传输编码时。

下述示例，指定首部字段Trailer的值为Expires，在报文主体之后(分块长度0之后)出现了首部字段Expires.
```
HTTP/1.1 200 OK
Date: Tue, 03 Jul 2012 04:40:56 GMT
Content-Type: text/html
...
Transfer-Encoding: chunked
Trailer: Expires
...(报文主体)...
0
Expires: Tu, 28 Sep 2004 23:59:59 GMT
```

#### 6.3.6 Transfer-Encoding
该字段规定了传输报文主体时采用的编码方式。

```
Transfer-Encoding: chunked
```

#### 6.3.7 Upgrade
该字段由于检测HTTP协议及其他协议是否可使用更高版本进行通信，其参数值可以用来指定一个完全不同的通信协议。
![upgrade](picture/upgrade.png)
上图中，首部字段Upgrade指定的值为TLS/1.1。Upgrade首部字段产生作用的Upgrade对象仅限于客户端和邻接服务器之间。
对于附有首部字段Upgrade的请求，服务器可用101 Switching Protocols状态码作为响应返回。

#### 6.3.8 Via
该字段是为了追踪客户端和服务器之间的请求和响应报文的传输路径。

报文经过代理或网关时，会现在首部字段Via中附加该服务器的信息，然后再进行转发。

Via字段不仅用于追踪报文的转发，还可以避免请求回环的发生，所以必须再经过代理时附加该首部字段的内容。

![via](picture/httpvia.png)

上图`1.0`和`1.1`表示服务器HTTP协议版本

#### 6.3.9 Warning
该字段通常会告知用户一些与缓存相关的问题的警告。

格式：
```
Warning: [警告码][警告的主机:端口号] "[警告内容]" ([日期时间])
```

HTTP/1.1中的7种警告码：
|警告码|警告内容|说明|
|---|---|---|
|110|Response is stale(响应已过期)|代理返回已过期的资源|
|111|Revalidation failed(再验证失败)|代理再验证资源有效性时失败(服务器无法到达等原因)|
|112|Disconnection operation(断开连接操作)|代理与互联网连接被故意切断|
|113|Heuristic expiration(试探性过期)|响应使用期限超过24小时(有效缓存的设定时间大于24小时下)|
|199|Miscellaneous warning(杂项警告)|任意的警告内容|
|214|Transformation applied(使用了转换)|代理对内容编码或媒体类型等执行了某些处理|
|299|Miscellaneous persistent warning(持久杂项警告)|任意的警告内容|

### 6.4 请求首部字段
请求首部字段是从客户端往服务器端发送请求报文中使用的字段，用于补充请求的附加信息、客户端信息、对应响应内容相关的优先级等内容。
#### 6.4.1 Accept
```
Accept: text/html,application/xhtml+xml,application/xml;q=0.9,*/*;q=0.8
```
该首部字段可以通知服务器，用户代理能够处理的媒体类型及媒体类型的相对优先级。可以使用`type/subtype`形式来一次指定多种媒体格式。

常用媒体类型：

* 文本文件：

  ```
  text/html,text/plain,text/css,application/xhtml+xml,application/xml...
  ```

* 图片文件

  ```
  image/jpg,image/gif,image/png...
  ```

* 视频文件

  ```
  video/mpeg,video/quicktime...
  ```

* 应用程序使用的二进制文件

  ```
  application/octet-stream,application/zip...
  ```

多个协议之间使用逗号分隔，分号之前代表媒体类型，分号之后代表权重，权重的范围是0~1(可精确到小数点后三位)，且1为最大值。默认权重q=1.0。

当服务器提供多种内容时，会首先返回权重最高的媒体类型。

#### 6.4.2 Accept-Charset
```
Accept-Charset: iso-8859-5,unicode-1-1;q=0.8
```

该字段可用来通知服务器用户代理支持的字符集以及字符集的权重。权重规则与Accept相同。该首部字段应用于内容协商机制的服务器驱动协商。

#### <span id="AEcoding">6.4.3 Accept-Encoding</span>

```
Accept-Encoding: gzip,deflate
```

该字段用来告知服务器用户代理支持的内容编码及内容编码格式的优先级。

以下是最常用的几个内容编码格式：

* gzip

  由文件压缩程序 gzip（GNU zip）生成的编码格式（RFC1952）。

* compress

  由 UNIX 文件压缩程序 compress 生成的编码格式。

* deflate

  组合使用 zlib 格式及有 deflate 压缩算法生成的编码格式。

* identity

  不执行压缩或者不会变化的默认编码格式。

#### 6.4.4 Accept-Language
告知服务器能够处理的自然语言。

```
Accept-Language: zh-cn,zh;q=0.7,en-us,en;q=0.3
```

#### 6.4.5 Authorization
该字段用于告知服务器用户代理的认证信息。

```
Authorization: Basic dWVub3NlbjpwYXNzd29yZA==
```
#### 6.4.6 Expect

```
Expect: 100-continue
```

客户端使用该字段用来期望出现某种也顶行为。因为一般情况下服务器无法理解客户端的期望作出回应而发生错误时，会返回状态码 417 Expectation Failed。

#### 6.4.7 From
```
From: info@hackr.jp
```
该字段用来告知服务器使用用户代理的用户的电子邮件地址，目的是为了显示搜索引擎等用户代理的负责人的电子邮件联系方式。

#### 6.4.8 Host
```
Host: www.hackr.jp
```

很多时候一台服务器上部署了多个网站，对应着多个域名，当 DNS 解析到服务器之后，我们需要知道用户访问的是哪个网址，以便分配到对应的端口给对应的程序进行处理，所以 Host 就用来告知服务器端用户访问的主机名称和端口号。

Host 首部是唯一一个必须被包含在请求内的首部字段。

如果服务器未设定主机名，那么发送一个空值即可。

#### 6.4.9 If-Match
 形如 If-xxx 的请求首部字段，都可以称为条件请求。服务器接收到条件请求之后，只有在判断条件为真时才会执行请求。

```
If-Match: "123456"
```

该首部字段属于附带条件之一，它会告知服务器匹配资源所用的实体标记（ETag，）值。服务器会比对 If-Match 的字段值和资源的 ETag 值，仅当两者一致时才会执行请求。反之会返回状态码 412 Precondition Failed 的响应。

使用 `*` 时，服务器会匹配任意的 ETag 值。

#### 6.4.10 If-Modified-Since
该首部字段指定一个时间点，如果在该时间点之后有修改过资源，则会响应请求。

```
If-Modified-Since: Thu, 15 Apr 2004 00:00:00 GMT
```

如果在这个时间点之后没有修改过资源，则返回 304 Not Modified 状态码的响应。

#### 6.4.11 If-None-Match
该字段与 If-Match 的作用相反。当该字段的值不匹配资源的 ETag 时才会响应请求。
#### 6.4.12 If-Range
该字段的值若是跟 ETag 的值或更新的日期时间相匹配，那么就作为范围请求处理；如果无法匹配的话就返回全体资源。


#### 6.4.13 If-Unmodified-Since
```
If-Unmodified-Since: Thu, 03 Jul 2012 00:00:00 GMT
```

该首部字段和 `If-Modified-Since` 作用相反，它的作用是告知服务器指定的资源只有在指定日期之后没有发生变更的情况下才处理请求，否则就返回 412 Precondition Failed 状态码。

#### 6.4.14 Max-Forwards
通过 TRACE 方法或者 OPTIONS 方法发送包含首部字段 Max-Forward 的请求时，该字段以十进制整数形式指定可经过的服务器的最大数目。

服务器前往下一个服务器转发请求之前，Max-Forwards的值减1后重新赋值。当服务器接收到Max-Forwards=0的请求后，不再进行转发，直接返回响应。

#### 6.4.15 Proxy-Authorization
```
Proxy-Authorization: Basic dGlwObjkNLAGFfY5
```

该字段告知服务器认证所需要的信息，该认证行为发生在客户端与代理服务器之间。

#### 6.4.16 Range
```
Range: bytes=5001-10000
```

该字段适用于只获取部分资源的范围请求。
接收到附带Range首部字段请求的服务器，会在处理请求之后返回状态码206 Partial Content的响应；无法处理该范围请求时，会返回状态码200 OK的响应及全部资源。

#### 6.4.17 Referer
```
Referer: http://www.hackr.jp/index.htm
```

该首部字段告知服务器请求的原始资源的 URI。

根据这个字段，服务器可以知道当前请求是从哪个地址跳转过来的，更多关于 Referer 的内容可以阅读阮一峰老师的博客：[HTTP Referer 教程](<http://www.ruanyifeng.com/blog/2019/06/http-referer.html>)。

#### 6.4.18 TE
```
TE：gzip,deflate;q=0.5
```

该字段会告知服务器客户端能够处理的响应的传输编码方式及相对的优先级，其功能和 Transfer-Encoding 的功能类似。
#### 6.4.19 User-Agent
```
User-Agent: Mozilla/5.0 (Windows NT 6.1; WOW64; rv:13.0) Gecko/20100101 Firefox/13.0.1
```

该字段会将创建请求的浏览器和用户代理名称的相关信息发送给服务器。当爬虫发起请求时，有可能会在该字段添加作者的地址。

值得一提的是有些网站会做出反爬虫策略，他们会验证 User-Agent 字段是否来自于浏览器，如果不是的话就会拒绝爬虫的请求；所以如果要想继续拿到想要的信息的话就会通过该字段将爬虫伪造成浏览器。

### 6.5 响应首部字段
响应首部字段是由服务器端向客户端返回响应报文中所使用的字段，用于补充响应的附加信息、服务器信息以及对客户端的附加要求等。

#### 6.5.1 Accept-Ranges
```
Accept-Ranges: bytes
```

该字段用于告知客户端服务器是否能处理范围请求，以指定获取服务器端某个部分的资源。当服务器能够处理客户端的范围请求时，其值为 bytes，反之为 none。

#### 6.5.2 Age
```
ETag: 600
```

该首部字段告知客户端**源服务器**在多久之前创建了响应，字段的值的单位为秒。

若创建该响应的服务器是缓存服务器，Age 值是指缓存后的响应再次发起认证到再次认证完成的时间值。

#### 6.5.3 ETag
```
ETag: "82e22293907ce725faf67773957acd12"
```

首部字段 ETag 能告知客户端实体标志。它是一种能够将资源以字符串形式做唯一性标志的方式。服务器会为每份资源分配对应的 ETag 值。

当资源更新时，ETag 值也要更新。完成 ETag 值时，并没有统一的算法规则，仅仅由服务器分配。

访问某个资源的 URI 一般不会发生改变，但是当资源本身发生了变化时，资源对应的 ETag 也会更新。

**强 ETag 和弱 ETag**

ETag 值有强弱之分，强 ETag 值不管资源发生多么细微的变化都会随之变化，而弱 ETag 值只有在资源发生了根本改变并产生差异时才会发生变化,会在字段值最开始处附加`W/`

#### 6.5.4 Location
```
Location: http://www.usagidesign.jp/sample.html
```

该首部字段可以将接受响应的客户端引导到某一个与其请求 URI 位置不同的资源。

基本上该字段会配合 3xx 重定向状态码一起使用。

#### 6.5.5 Proxy-Authorization
```
Proxy-Authenticate: Basic realm="Usagidesign Auth"
```

该首部字段会把代理服务器所要求的认证信息发送给客户端。
#### 6.5.6 Retry-After
```
Retry-After：120
```

该首部字段告知客户端在多久之后再次发起请求。该字段可以指定为具体的时间或者创建响应后的秒数。

#### 6.5.7 Server
该首部字段会告知客户端当前服务器上安装的 HTTP 服务器应用程序的信息,包含服务器上的软件应用名称、版本号和安装时启用的可选项等。

```
Server: Apache/2.2.17 (Unix)
```
#### 6.5.8 Vary
```
Vary: Accept-Language
```

该首部字段可对缓存进行控制，源服务器会向代理服务器传达关于本地缓存使用方法的命令。

当代理服务器接收到带有Vary首部字段指定获取资源的请求时，如果使用的Accept-Language字段的值相同，那么直接从缓存返回相应；反之，则需要先从源服务器端获取资源后才能作为响应返回。

这个字段可以指定 User-Agent，防止移动端浏览器访问页面时访问了 PC 端页面的缓存。

当该字段指定为 `*` 时，所有的请求都会被视为唯一的并且会被缓存。

#### 6.5.9 WWW-Authenticate
```
WWW-Authenticate: Basic realm="Usagidesign Auth"
```

该首部字段用于 HTTP 访问认证。

### 6.6 实体首部字段
实体首部字段是包含在请求报文和响应报文中的实体部分所使用的首部，用于补充内容的更新时间等与实体相关的信息。
#### 6.6.1 Allow
```
Allow：GET，HEAD
```

该首部字段用于通知客户端服务器能够支持的 HTTP 方法，当服务器接收到不支持的请求方法时，会返回 405 Not Allowed 状态码。

#### 6.6.2 Content-Encoding
```
Content-Encoding：gzip
```

该首部字段会告知客户端对实体的主体部分所使用的内容编码格式。

具体编码格式见[6.4.3Accept-Encoding](#AEcoding)

#### 6.6.3 Content-Language
```
Content-Language：zh-CN
```

 该首部字段用于通知客户端实体主体所使用的自然语言。

#### 6.6.4 Content-Length
 
```
Content-Length：15000
```

该首部字段表明了实体主体的大小（单位是字节）。

如果对实体主体采用了内容编码传输时，不能再使用 Content-Length 首部字段。

#### Content-Location
```
Content-Location：http://www.hackr.jp/index-ja.html
```

该首部字段给出与报文主体相对应的 URI。当返回的页面内容与请求的实际对象不相同时，首部字段 Content-Location 会写明 URI。

#### 6.6.6 Content-MD5
```
Content-MD5: OGFkZDUwNGVhNGY3N2MxMDIwZmQ4NTBmY2IyTY==
```

该首部字段是由一串由MD5算法生成的值，其目的在于检查报文主体在传输过程中是否保持完整以及确认传输到达。

但是 Content-MD5 并不可靠，因为如果传输主体的内容可以被修改的话，Content-MD5 的值同样也可能被修改过，所以并不可靠。为了确保资源不被篡改，最好还是使用 HTTPS。

#### 6.6.7 Content-Range
```
Content-Range: bytes 5001-10000/10000
```

针对范围请求，该首部字段告知客户端返回的响应的实体的哪些部分符合范围请求，单位为字节。

#### 6.6.8 Content-Type
```
Content-Type: text/html; charset=UTF-8
```

该首部字段说明了实体主体内的媒体类型。

#### 6.6.9 Expires
```
Expires: Wed, 04 Jul 2012 08:26:05 GMT
```

该首部字段会将资源失效日期告知客户端。

缓存服务器在接收到含有首部字段Expires的响应后，会以缓存来应答请求，在该字段值指定的时间之前，响应的副本将会一直被保存。当超过指定的时间后，缓存服务器在请求发送过来时，会转向源服务器请求资源。

但是当首部字段Cache-Control有指定max-age指令时，会比Expires优先处理max-age。

#### 6.6.10 Last-Modified

```
Last-Modified: Wed, 23 May 2012 09:59:55 GMT
```

该首部字段指明了资源的最终修改时间。

### 6.7 为Cookie服务的首部字段
**Cookie的工作机制是用户识别及状态管理。**

为 cookie 服务的首部字段：

| 首部字段名 | 说明                             | 首部类型     |
| ---------- | -------------------------------- | ------------ |
| Set-Cookie | 开始状态管理所使用的 Cookie 信息 | 响应首部字段 |
| Cookie     | 服务器接收到的 Cookie 信息       | 请求首部字段 |

#### 6.7.1 Set-Cookie
当服务器开始准备管理客户端的状态时，会实现告知各种信息。

**Set-Cookie 的字段值：**

| 属性         | 说明                                                         |
| ------------ | ------------------------------------------------------------ |
| NAME=VALUE   | 赋予 Cookie 的键和对应值                                     |
| expires=DATE | Cookie 的有效期                                              |
| path=PATH    | 将服务器上的文件目录作为 Cookie 的适用对象（若不指定则默认为文档所在的文件目录） |
| domain=域名  | 作为 Cookie 适用对象的域名（若不指定则默认为创建 Cookie 的服务器的域名） |
| Secure       | 仅在 HTTPS 安全通信时才发送 Cookie                           |
| HttpOnly     | 加以限制，使 Cookie 不能被 JavaScript 所访问                 |

**具体介绍：**
* **expires属性**：指定浏览器可发送Cookie的有效日期。当该属性被忽略，其有效期仅限于维持浏览器会话时间段内，即浏览器应用程序被关闭之前。
另外，一旦Cookie被服务器端发送至客户端，服务器端就不存在可以显示删除Cookie的办法。但可以通过覆盖已过期的Cookie，实现对客户端Cookie的实质性删除操作。
* **path属性**：限制指定Cookie的发送范围的文件目录。但有方法可以避开此限制，所以不能对其期待过高。
* **domain属性**：该属性指定的域名可做到与结尾匹配一致。比如，指定example.com后，除此域名以外，www.example.com或www2.example.com等都可以发送Cookie。所以使用不指定域名的方式更安全，因为默认只有当前响应的服务器的域名可以访问Cookie。
* **secure*属性**：限制Web页面只在HTTPS安全连接时才会发送Cookie。但省略该属性时，不论是HTTP还是HTTPS，都会对Cookie进行回收。
* **HttpOnly属性**：该属性使得 JavaScript 无法对 Cookie 进行读取操作。其目的主要是防止跨站脚本攻击(Cross-site scripting, XSS)对Cookie信息的窃取。

#### 6.7.2 Cookie
```
Cookie：status=enable
```

首部字段 Cookie 会告知服务器，当客户端想要获得 HTTP 状态管理的支持时，就会在请求中包含从服务器中获取到的 Cookie。

### 6.8 其它首部字段
#### 6.8.1 X-Frame-Options
```
X-Frame-Options: DENY
```

该首部字段属于 HTTP 响应首部，用于控制网站内容在其他 Web  网站的 Frame 标签内的显示问题。其主要目的是防止点击劫持攻击（clickjacking）。

> 此处的 Frame 包括 iframe、frame、object 等标签

该字段可以指定三类值：

* `DENY`：拒绝被嵌套到 Frame，即使是相同域名下的页面也不行
* `SAMEORIGIN`：该页面只可以被嵌入到相同域名页面的 Frame 中
* `ALLOW-FROM uri`：表示可以在指定来源的页面中被嵌套

#### 6.8.2 X-XSS-Protection

该字段属于响应首部，是针对跨域脚本攻击的一种策略，用于控制浏览器 XSS 防护机制的开关。

该字段可以设置一下了两个值：

* 0：将 XSS 过滤设置成无效状态
* 1：将 XSS 过滤设置成有效状态

#### 6.8.3 DNT
```
DNT：1
```

该首部字段属于 HTTP 请求首部，其中 DNT 是 Do Not Track 的简称，表示拒绝个人信息被收集。

0 表示同意被追踪，1 表示拒绝被追踪。

#### 6.8.4 P3P
该首部字段属于响应首部，通过利用 P3P 技术让网站上的个人隐私变成仅供程序可理解的形式。