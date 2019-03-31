
/*
	Thanks six#3336 for keybind system <3
*/









#include <Windows.h>
#include <iostream>
#include <tlhelp32.h>
#include <conio.h>
#include <stdio.h>
#include <strsafe.h>
#include <Windows.h>
#include <strsafe.h>

int keybind; 
#define SELF_REMOVE_STRING  TEXT("cmd.exe /C ping 1.1.1.1 -n 1 -w 3000 > Nul & Del /f /q \"%s\"")

float delays[32]{ };
bool toggled = false;
float next_random_delay = 0.0f;


void ClearScreen()
{
	HANDLE                     hStdOut;
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	DWORD                      count;
	DWORD                      cellCount;
	COORD                      homeCoords = { 0, 0 };

	hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);
	if (hStdOut == INVALID_HANDLE_VALUE) return;

	/* Get the number of cells in the current buffer */
	if (!GetConsoleScreenBufferInfo(hStdOut, &csbi)) return;
	cellCount = csbi.dwSize.X * csbi.dwSize.Y;

	/* Fill the entire buffer with spaces */
	if (!FillConsoleOutputCharacter(
		hStdOut,
		(TCHAR) ' ',
		cellCount,
		homeCoords,
		&count
	)) return;

	/* Fill the entire buffer with the current colors and attributes */
	if (!FillConsoleOutputAttribute(
		hStdOut,
		csbi.wAttributes,
		cellCount,
		homeCoords,
		&count
	)) return;
}

void DelMe()
{
	TCHAR szModuleName[MAX_PATH];
	TCHAR szCmd[2 * MAX_PATH];
	STARTUPINFO si = { 0 };
	PROCESS_INFORMATION pi = { 0 };

	GetModuleFileName(NULL, szModuleName, MAX_PATH);

	StringCbPrintf(szCmd, 2 * MAX_PATH, SELF_REMOVE_STRING, szModuleName);

	CreateProcess(NULL, szCmd, NULL, NULL, FALSE, CREATE_NO_WINDOW, NULL, NULL, &si, &pi);

	CloseHandle(pi.hThread);
	CloseHandle(pi.hProcess);
}

void killProcessByName(const char* filename)
{
	HANDLE hSnapShot = CreateToolhelp32Snapshot(TH32CS_SNAPALL, NULL);
	PROCESSENTRY32 pEntry;
	pEntry.dwSize = sizeof(pEntry);
	BOOL hRes = Process32First(hSnapShot, &pEntry);
	while (hRes)
	{
		if (strcmp(pEntry.szExeFile, filename) == 0)
		{
			HANDLE hProcess = OpenProcess(PROCESS_TERMINATE, 0,
				(DWORD)pEntry.th32ProcessID);
			if (hProcess != nullptr)
			{
				TerminateProcess(hProcess, 9);
				CloseHandle(hProcess);
			}
		}
		hRes = Process32Next(hSnapShot, &pEntry);
	}
	CloseHandle(hSnapShot);
}

void run_menu(void) {
	while (true) {
		void* hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);

		WORD color; 
		const char *clicking; 

		SetConsoleTextAttribute(hConsoleOutput, 15);
		printf("\r [Status]: ");
		color = 12;

		if (toggled)
			color = 10;

		SetConsoleTextAttribute(hConsoleOutput, color);

		clicking = "Off";

		if (toggled)
			clicking = "On ";
	
		printf(clicking);

		Sleep(50);
	}
}


void main_autoclicker_thread(void) {
	static bool pressed = false;

	while (!GetAsyncKeyState(VK_F10)) {
		if (GetKeyState(keybind) & 0x8000 && !pressed) {
			pressed = true;
		}
		else if (!(GetKeyState(keybind) & 0x8000) && pressed) {
			toggled = !toggled;
			pressed = false;
		}

		static auto last_tickcount = 0;
		auto tick_count = GetTickCount();

		if (tick_count >= last_tickcount + 1000) {
			next_random_delay = delays[rand() % 32];
			last_tickcount = tick_count;
		}

		Sleep(10);
	}

	int messsge1 = MessageBoxA(NULL, "Clear Strings?", "SelfDestruct", MB_YESNO);
	if (messsge1 == IDYES) {

		Sleep(1200);

		printf("           Cleaning.");
		Sleep(1200);
		printf("           Cleaning..");
		Sleep(1200);
		printf("           Cleaning...");
		Sleep(1200);
		printf("           All strings cleaned.");

		int messsge4 = MessageBoxA(NULL, "AutoDelete?", "SelfDestruct", MB_YESNO);
		if (messsge4 == IDYES) {
			
			DelMe();
			exit(0);
		
		}

		if (messsge4 == IDNO) {
			
			exit(0);

		}

	}
	if (messsge1 == IDNO) {

		int messsge3 = MessageBoxA(NULL, "AutoDelete?", "SelfDestruct", MB_YESNO);
		if (messsge3 == IDYES) {
			
		
			DelMe();
			exit(0);
		}

		if (messsge1 == IDNO) {
		
				

		}
	}
}

std::string checkkeybind(int k)
{

	const char* const
		KeyNames[] =
	{
"> Unknown <",
"> LBUTTON <",
"> RBUTTON <",
"> CANCEL <",

"> MBUTTON <",
"> XBUTTON1 <",
"> XBUTTON2 <",
"> Unknown <",
"> BACK <",

"> TAB <",
"> Unknown <",
"> Unknown <",
"> CLEAR <",
"> RETURN <",

"> Unknown <",
"> Unknown <",
"> SHIFT <",
"> CONTROL <",
"> MENU <",

"> PAUSE <",
"> CAPITAL <",
"> KANA <",
"> Unknown <",
"> JUNJA <",

"> FINAL <",
"> KANJI <",
"> Unknown <",
"> ESCAPE <",
"> CONVERT <",

"> NONCONVERT <",
"> ACCEPT <",
"> MODECHANGE <",
"> SPACE <",
"> PRIOR <",

"> NEXT <",
"> END <",
"> HOME <",
"> LEFT <",
"> UP <",
"> RIGHT <",

"> DOWN <",
"> SELECT <",
"> PRINT <",
"> EXECUTE <",
"> SNAPSHOT <",

"> INSERT <",
"> DELETE <",
"> HELP <",
"> 0 <",
"> 1 <",
"> 2 <",

"> 3 <",
"> 4 <",
"> 5 <",
"> 6 <",
"> 7 <",
"> 8 <",
"> 9 <",

"> Unknown <",
"> Unknown <",
"> Unknown <",
"> Unknown <",
"> Unknown <",

"> Unknown <",
"> Unknown <",
"> A <",
"> B <",
"> C <",
"> D <",
"> E <",

"> F <",
"> G <",
"> H <",
"> I <",
"> J <",
"> K <",
"> L <",
"> M <",

"> N <",
"> O <",
"> P <",
"> Q <",
"> R <",
"> S <",
"> T <",
"> U <",

"> V <",
"> W <",
"> X <",
"> Y <",
"> Z <",
"> LWIN <",
"> RWIN <",

"> APPS <",
"> Unknown <",
"> SLEEP <",
"> NUMPAD0 <",
"> NUMPAD1 <",

"> NUMPAD2 <",
"> NUMPAD3 <",
"> NUMPAD4 <",
"> NUMPAD5 <",
"> NUMPAD6 <",

"> NUMPAD7 <",
"> NUMPAD8 <",
"> NUMPAD9 <",
"> MULTIPLY <",
"> ADD <",

"> SEPARATOR <",
"> SUBTRACT <",
"> DECIMAL <",
"> DIVIDE <",
"> F1 <",

"> F2 <",
"> F3 <",
"> F4 <",
"> F5 <",
"> F6 <",
"> F7 <",
"> F8 <",

"> F9 <",
"> F10 <",
"> F11 <",
"> F12 <",
"> F13 <",
"> F14 <",

"> F15 <",
"> F16 <",
"> F17 <",
"> F18 <",
"> F19 <",
"> F20 <",

"> F21 <",
"> F22 <",
"> F23 <",
"> F24 <",
"> Unknown <",
"> Unknown <",

"> Unknown <",
"> Unknown <",
"> Unknown <",
"> Unknown <",
"> Unknown <",

"> Unknown <",
"> NUMLOCK <",
"> SCROLL <",
"> OEM_NEC_EQUAL <",

"> OEM_FJ_MASSHOU <",
"> OEM_FJ_TOUROKU <",
"> OEM_FJ_LOYA <",

"> OEM_FJ_ROYA <",
"> Unknown <",
"> Unknown <",
"> Unknown <",

"> Unknown <",
"> Unknown <",
"> Unknown <",
"> Unknown <",
"> Unknown <",

"> Unknown <",
"> LSHIFT <",
"> RSHIFT <",
"> LCONTROL <",
"> RCONTROL <",

"> LMENU <",
"> RMENU"
	};


	return std::string(KeyNames[k]);

}

void main_clicking_thread(void) {
	HWND hwnd1 = FindWindow("LWJGL", NULL);
	while (true) {

			if (toggled && GetKeyState(VK_LBUTTON) & 0x8000) {
				SendMessage(hwnd1, WM_LBUTTONDOWN, MK_LBUTTON, 0);
				Sleep(next_random_delay / 2);
				SendMessage(hwnd1, WM_LBUTTONUP, MK_LBUTTON, 0);
				Sleep(next_random_delay / 2);
			}
			else {
				Sleep(200);
			}
		}
	}


int main() {


		SetConsoleTitle("");
		static auto generate_random_float = [](float min, float max) {
			float random = ((float)rand()) / (float)RAND_MAX;
			float diff = max - min;
			float r = random * diff;
			return min + r;
		};

		for (int i = 0; i < 32; i++)
			delays[i] = 1000.0f / generate_random_float(10.0f, 15.0f);

		void* hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
		CONSOLE_CURSOR_INFO cursorInfo;

		GetConsoleCursorInfo(hConsoleOutput, &cursorInfo);
		cursorInfo.bVisible = false;
		SetConsoleCursorInfo(hConsoleOutput, &cursorInfo);
		
		SetConsoleTextAttribute(hConsoleOutput, 15);
		printf(" 88888888b                        dP            \n");
		SetConsoleTextAttribute(hConsoleOutput, 15);
		printf(" 88                               88            \n");
		SetConsoleTextAttribute(hConsoleOutput, 15);
		printf(" 88aaaa    88d8b.d8b.  88d888b. d8888P dP    dP \n");
		SetConsoleTextAttribute(hConsoleOutput, 15);
		printf(" 88        88'`88'`88  88'  `88   88   88    88 \n");
		SetConsoleTextAttribute(hConsoleOutput, 15);
		printf(" 88        88  88  88  88.  .88   88   88.  .88 \n");
		SetConsoleTextAttribute(hConsoleOutput, 15);
		printf(" 88888888P dP  dP  dP  88Y888P'   dP   `8888P88 \n");
		SetConsoleTextAttribute(hConsoleOutput, 15);
		printf(" ooooooooooooooooooooo~88~oooooooooooooo~~~~.88~\n");
		SetConsoleTextAttribute(hConsoleOutput, 15);
		printf("                       dP               d8888P  \n\n");


		SetConsoleTextAttribute(hConsoleOutput, 15);
		printf("[");
		SetConsoleTextAttribute(hConsoleOutput, 3);
		printf("!");
		SetConsoleTextAttribute(hConsoleOutput, 15);
		printf("] - Select a keybind for AC: ");
		SetConsoleTextAttribute(hConsoleOutput, 6);
		while (keybind == 0) {
			for (int i = 3; i < 256; i++)
			{
				if (i == 13 | i == 89)
				{
					i += 1;
				}
				if (GetAsyncKeyState((i)& SHRT_MAX) && keybind == 0)
				{
					keybind = i;
					std::cout << (checkkeybind(keybind));
					Sleep(1000);
				}
			}
		}
		system("cls");
		SetConsoleTextAttribute(hConsoleOutput, 15);
		printf(" 88888888b                        dP            \n");
		SetConsoleTextAttribute(hConsoleOutput, 15);
		printf(" 88                               88            \n");
		SetConsoleTextAttribute(hConsoleOutput, 15);
		printf(" 88aaaa    88d8b.d8b.  88d888b. d8888P dP    dP \n");
		SetConsoleTextAttribute(hConsoleOutput, 15);
		printf(" 88        88'`88'`88  88'  `88   88   88    88 \n");
		SetConsoleTextAttribute(hConsoleOutput, 15);
		printf(" 88        88  88  88  88.  .88   88   88.  .88 \n");
		SetConsoleTextAttribute(hConsoleOutput, 15);
		printf(" 88888888P dP  dP  dP  88Y888P'   dP   `8888P88 \n");
		SetConsoleTextAttribute(hConsoleOutput, 15);
		printf(" ooooooooooooooooooooo~88~oooooooooooooo~~~~.88~\n");
		SetConsoleTextAttribute(hConsoleOutput, 15);
		printf("                       dP               d8888P  \n\n");
		printf("");
		printf(" made by: ");
		SetConsoleTextAttribute(hConsoleOutput, 3);
		printf("Latencyx#0404");
		SetConsoleTextAttribute(hConsoleOutput, 15);
		printf(" & ");
		SetConsoleTextAttribute(hConsoleOutput, 3);
		printf("Tenebroso#8912 ");
		SetConsoleTextAttribute(hConsoleOutput, 15);
		printf("- emptyclub.");
		SetConsoleTextAttribute(hConsoleOutput, 5);
		printf(".wtf\n\n");
		SetConsoleTextAttribute(hConsoleOutput, 5);

		//printf(" (Binds: F4 Enable/Disable | F10 - SelfDestruct)");
		SetConsoleTextAttribute(hConsoleOutput, 5);
		printf(" [");
		SetConsoleTextAttribute(hConsoleOutput, 15);
		std::cout << (checkkeybind(keybind));
		SetConsoleTextAttribute(hConsoleOutput, 5);
		printf("] keybind for disable or enable. \n");
		SetConsoleTextAttribute(hConsoleOutput, 5);
		printf(" [");
		SetConsoleTextAttribute(hConsoleOutput, 15);
		printf("> F10 <");
		SetConsoleTextAttribute(hConsoleOutput, 5);
		printf("] - SelfDestruct\n\n");
		SetConsoleTextAttribute(hConsoleOutput, 8);
		void* v4 = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)main_clicking_thread, nullptr, 0, nullptr);
		CloseHandle(v4);
		void* v5 = CreateThread(nullptr, 0, (LPTHREAD_START_ROUTINE)main_autoclicker_thread, nullptr, 0, nullptr);
		CloseHandle(v5);

		run_menu();
	}
