#include <Windows.h>

DWORD WINAPI func(void* data)
{
	while (true)
	{
		Sleep(1000);
		MessageBox(0, L"DLL Injection message !", L"DLL Injection", MB_ICONINFORMATION);
	}
	return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
		CreateThread(NULL, 0, func, NULL, 0, NULL);
		break;
	case DLL_THREAD_ATTACH:
		break;
	}

	return TRUE;
}