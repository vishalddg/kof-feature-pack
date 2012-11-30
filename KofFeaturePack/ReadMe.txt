KofPacks是对VC2008SP1中Ribbon界面加强，让对话框也和多文档、单文档一样有相同的Office样式。

在VS2008 SP1基于对话框工程使用：
【动态库】
1.在"stdafx.h"文件中添加如下代码：
#include "KofPackInc.h"
2.配置好附加头文件目录和附加库目录；
3.打开对话框文件，更改派生类CDialog改为CKofDialogEx
4.打开应用程序App实现文件，在InitInstance函数中，添加如下代码：
CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
CKofStyleHelper::GetInstance()->SetStyle(CKofStyleHelper::KOF_CMFCVisualManagerOffice2007);
5.编译运行后，即可看到Office2007样式的对话框。

【静态库】
还多需一步，在资源视图，右键资源附加，在#include "afxribbon.rc" 之后添加
#include "KofPackRes.rc"
工程设置 资源 常规，增加附加引用目录"$(SolutionDir)Include";