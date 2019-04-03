#include <stdio.h>
#include <Windows.h>
#pragma warning(disable:4996)

BOOL isProcessRunning(DWORD pid)
{
	HANDLE process = OpenProcess(SYNCHRONIZE, false, pid);
	DWORD ret = WaitForSingleObject(process, 0);
	CloseHandle(process);
	return ret == WAIT_TIMEOUT;
}

int main(int argc, char *argv[])
{
	if (argc < 3)
	{
		printf("Usage :\n");
		printf("- PID of the process\n");
		printf("- Absolute path to the dll\n");
		return 0;
	}

	DWORD pid = atoi(argv[1]);
	LPCSTR dllPath = argv[2];

	if (isProcessRunning(pid))
	{
		HANDLE process = OpenProcess(PROCESS_ALL_ACCESS, false, pid);
		LPVOID pdllPath = VirtualAllocEx(process, 0, strlen(dllPath) + 1, MEM_COMMIT, PAGE_READWRITE);
		WriteProcessMemory(process, pdllPath, (LPVOID)dllPath, strlen(dllPath) + 1, 0);

		HANDLE dllThread = CreateRemoteThread(process, 0, 0, (LPTHREAD_START_ROUTINE)GetProcAddress(GetModuleHandleA("Kernel32.dll"),
			"LoadLibraryA"), pdllPath, 0, 0);

		printf("DLL successfully injected ");
	}
	else
	{
		printf("The process %d is not active !", pid);
	}

	return 0;
}