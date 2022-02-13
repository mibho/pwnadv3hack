#include "hack.h"

HINSTANCE DllHandle;

/*
https://stackoverflow.com/questions/7831696/reinterpret-cast-vs-c-style-cast

*/

//Player: [[[[<gamelogic.dll>+97D7C]+4]]+10]-70


DWORD __stdcall EjectThread(LPVOID lpParameter) {
	Sleep(100);
	FreeLibraryAndExitThread(DllHandle, 0);
	return 0;
}

DWORD WINAPI dwHookThreadCopy(HMODULE hModule)
{

	AllocConsole();
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);


	pwnHack cheat;
	bool option1 = false, option2 = false, option3 = false;
	while (true)
	{
		if (GetAsyncKeyState(0x58) & 1) { // x key on keyboard
			option1 = !option1;
			if (option1)
				std::cout << "option1 (movement cheat) is : enabled" << std::endl;
			else
				std::cout << "option1 (movement cheat) is : disabled" << std::endl;
		}
		if (GetAsyncKeyState(0x59) & 1) { // c key on keyboard
			option2 = !option2;
			if (option2)
				std::cout << "option2 (health & mana cheat) is : enabled" << std::endl;
			else
				std::cout << "option2 (health & mana cheat) is : disabled" << std::endl;
		}
		if(option1)
		{ 
			cheat.setPlayerMove(10000, 3000, 50); // arg1 = player speed, arg2 = jump height, arg3 = hold time
		}

		
		if (option2)
		{ 
			cheat.setPlayerHealth(99999);
			cheat.setPlayerMana(99999);
		}
		
			 if (GetAsyncKeyState(VK_F1) & 1){ cheat.teleToRegion(1); }
		else if (GetAsyncKeyState(VK_F2) & 1){ cheat.teleToRegion(2); }
		else if (GetAsyncKeyState(VK_F3) & 1){ cheat.teleToRegion(3); }
		else if (GetAsyncKeyState(VK_F4) & 1){ cheat.teleToRegion(4); }
		else if (GetAsyncKeyState(VK_F5) & 1){ cheat.teleToRegion(5); }
		else if (GetAsyncKeyState(VK_F6) & 1){ cheat.teleToRegion(6); }
		else if (GetAsyncKeyState(VK_F7) & 1){ cheat.teleToRegion(7); }
		else if (GetAsyncKeyState(VK_F8) & 1){ cheat.teleToRegion(8); }
		else {
			Sleep(50);
		}

		if (GetAsyncKeyState(VK_INSERT) & 1) // remove injected dll
		{
			std::cout << "Insert pressed; exiting program." << std::endl;
			fclose(fp);
			FreeConsole();
			CreateThread(0, 0, EjectThread, 0, 0, 0);
			return NULL;
		}
	}
	fclose(fp);
	FreeConsole();
	CreateThread(0, 0, EjectThread, 0, 0, 0);
	return NULL;


}


BOOL APIENTRY DllMain(HMODULE hModule, DWORD dwReason, LPVOID lpReserved)
{

	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		DllHandle = hModule;
		CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)dwHookThreadCopy, NULL, 0, NULL);
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}