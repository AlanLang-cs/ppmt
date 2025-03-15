# 个人密码管理软件
人生第一个软件项目，为了解决实际问题，使用软件工程思想进行开发。

使用C、MFC++开发，3000+行代码

---
## 需求分析

开发这款软件的初衷来源于家人们的烦恼：管理多张银行卡和多个网络账户如：网银、证券、APP、电商、支付、网站等等，需要记忆和管理一大堆密码，对于上了年纪的人来讲，是一件痛苦的事！因为各个账户密码往往不同，且不同网站/APP的密码设置规则五花八门。
为了解决这一问题，我设计了一款个人密码管理软件，旨在保障个人隐私信息安全的前提下高效管理各类密码，帮助用户避免因忘记某个账户密码而带来的麻烦。

重点需求如下：

- **使用便捷**：支持多用户场景，提供友好的用户交互界面。
- **安全保障**：对密码进行加密存储，确保数据安全。

---

## 功能模块概述

### 业务功能模块
1. **用户管理**：
   - 支持多用户使用场景
   - 新用户注册：对于每个用户生成独立的密钥文件和个人账户数据文件
   - 用户登录：用户名+密码登录，密码输入需要使用个人密钥加密验证
2. **个人账户记录管理**：
   - 每个用户拥有独立的账户数据文件和管理界面
   - 可分类管理多个账户信息
3. **账户类别管理**：
   - 提供账户类别（如银行卡、网络银行、网站登录、邮箱等），由配置文件定义
   - 用户可直接编辑配置文件修改账户类别。
4. **账户记录管理**：
   - 增加账户记录
   - 删除账户记录
   - 查询账户记录
   - 修改账户记录

### 公共基础模块

   提供公共函数库，供上述业务模块调用。

1. **加密和解密**：
   - 针对每位用户生成独立的密钥文件
   - 使用 DES 算法对密码进行加解密运算。
2. **文件访问与存储**：
   - 每位用户拥有独立的账户数据文件
   - 新用户注册时创建个人账户数据文件
   - 登录时读取文件内容到内存
   - 数据变动时同步写入文件。
3. **日志记录**：
   - 编写 `WriteLog` 函数记录过程信息，便于调试和日后维护。

---

## IO与流程设计

### 用户界面与数据处理流程

详细参见：[https://blog.csdn.net/2301_80045957/article/details/146267061?spm=1011.2124.3001.6209](https://blog.csdn.net/2301_80045957/article/details/146267061?spm=1011.2124.3001.6209)]


### 加解密算法的选择与详解

作为初学菜鸟，本次选用经典对称加密算法DES，采用模块化设计，未来可升级为更为高级的加密算法。

详细参见：
[https://blog.csdn.net/2301_80045957/article/details/146267448?sharetype=blogdetail&sharerId=146267448&sharerefer=PC&sharesource=2301_80045957&spm=1011.2480.3001.8118](https://blog.csdn.net/2301_80045957/article/details/146267448?sharetype=blogdetail&sharerId=146267448&sharerefer=PC&sharesource=2301_80045957&spm=1011.2480.3001.8118)

---

## 数据规划

### 内存数据结构

采用“数组+链表”的结构：

- 数组用于存储账户类别信息。
- 链表用于存储具体账户记录。

### 文件数据结构
#### 文件头
- 用户登录名称（20字节）
- 用户密码（密文形式保存，8字节）
- 账户总记录数（4字节）
- 文件校验码（8字节，预留未来使用）

#### 文件体
按账户类别分为若干块，每块包含账户类别信息和所有该类账户记录。

---

## 开发与调试

### 技术要点
1. **加密算法**：选择传统对称加密算法 DES，实现数据的安全存储。
2. **编程语言**：使用 C 语言实现公共基础模块，利用 Visual Studio 平台和 MFC 类库开发用户交互界面。
3. **数据结构**：采用“数组+链表”结构，灵活高效地管理账户数据。

### 调试方法
1. **日志记录**：编写 `WriteLog` 函数，将重要节点的数据信息以十六进制形式记录到日志文件中，便于跟踪和验证加密模块。
2. **断点调试**：使用 Visual Studio 的 Debug 工具进行单步调试，检查变量值和程序执行流程。
3. **错误排查**：通过逐项注释代码的方式定位问题，结合编译器返回的错误信息进行修复。

---

## 总结

### 成果回顾

本项目历时约一个月完成，主要包括以下几个阶段：

1. **需求确认**：通过与家人讨论，明确开发一款个人密码管理软件的需求。
2. **软件设计**：绘制输入输出界面、划分功能模块和定义函数接口、定义文件格式、明确内部数据结构。
3. **程序编码与调试**：分模块编码和调试，结合 MFC 类库完成用户界面开发。
4. **测试与反馈**：邀请家人使用软件，记录问题并逐一排查解决。

### 收获与体会
1. **技术能力提升**：
   - 学习了数据加密相关知识，掌握了 DES 加密算法的实现。
   - 熟悉了 C、C++ 和 Visual Studio 平台的使用，提高了软件开发的专业性。
2. **解决问题的能力**：
   - 通过查阅资料、请教前辈和实际操作，深入学习了位运算、链表操作、MFC 编程等知识点，并熟悉了跟踪问题和调试故障的方法。
3. **项目开发经验**：
   - 深入体验了软件项目开发的完整流程，包括需求确认、程序设计、程序开发和程序测试。


