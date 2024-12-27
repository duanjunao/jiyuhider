#include<bits/stdc++.h>
#include<windows.h>
#include<tlhelp32.h>
using namespace std;
void abc(DWORD pid)
{
	const char* path = "D:\\Dll1.dll";
	HANDLE hProc = OpenProcess(PROCESS_ALL_ACCESS, FALSE, pid);
	LPVOID lpAddr =  VirtualAllocEx(hProc,NULL, strlen(path)+1, MEM_COMMIT, PAGE_READWRITE);
	WriteProcessMemory(hProc, lpAddr, path,strlen(path), NULL);
	HMODULE sysMod = LoadLibraryA("Kernel32.dll");
	LPTHREAD_START_ROUTINE fp =(LPTHREAD_START_ROUTINE) GetProcAddress(sysMod, "LoadLibraryA");
	CreateRemoteThread(hProc, NULL, NULL,(LPTHREAD_START_ROUTINE)fp, lpAddr, 0, NULL);
}
int bcd(char* mdl)
{
	int n=0;
	HANDLE hd=CreateToolhelp32Snapshot(TH32CS_SNAPPROCESS,0);
	PROCESSENTRY32 pe;
	pe.dwSize=sizeof(PROCESSENTRY32);
	if(Process32First(hd,&pe)==TRUE)
	{
		do
		{
			if(!strcmp(mdl,pe.szExeFile))
			{
				n++;
				cout<<pe.th32ProcessID<<endl;
				abc(pe.th32ProcessID);
			}
		}
		while(Process32Next(hd,&pe));
	}
	CloseHandle(hd);
	return n;
}
int main()
{
	string a;
	cin>>a;
	cout<<bcd((char*)a.c_str());
}
