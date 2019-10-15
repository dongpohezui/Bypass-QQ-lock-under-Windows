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

