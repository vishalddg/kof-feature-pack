KofPacks是对VC2008SP1中Ribbon界面加强，让对话框也和多文档、单文档一样有相同的Office样式。

在VS2008 SP1基于对话框工程使用：
【动态库】
1.在"stdafx.h"文件中添加如下代码：
#include "KofPackInc.h"
2.配置好“附加包含目录”和“附加库目录”、“附加依赖项”；
3.打开对话框文件，更改派生类CDialog改为CKofDialogEx
4.打开应用程序App实现文件，在InitInstance函数中，添加如下代码：
CMFCVisualManagerOffice2007::SetStyle(CMFCVisualManagerOffice2007::Office2007_LunaBlue);
CMFCVisualManager::SetDefaultManager(RUNTIME_CLASS(CMFCVisualManagerOffice2007));
CKofStyleHelper::GetInstance()->SetStyle(CKofStyleHelper::KOF_CMFCVisualManagerOffice2007);
5.编译运行后，即可看到Office2007样式的对话框。

【静态库】
还多需一步，在资源视图，右键“资源包括”，在“编译时指令”下添加：

#if !defined(_AFXDLL)
#include "afxribbon.rc"              // MFC ribbon and control bar resources
#include "KofPackRes.rc"
#endif

工程属性设置“资源”→“常规”→“附加包含目录”，增加资源路径，如："$(SolutionDir)Include";