#include <stdio.h>
#include <tchar.h>
#include "thread"
#include "windows.h"
#include <TlHelp32.h>
#include <vector>
#include <fstream>
#include <chrono>
#include <shlwapi.h>
#pragma comment(lib,"shlwapi.lib")
#include "shlobj.h"
#include <iostream>
#include <atlstr.h>

using namespace std;

HWND hWnd = NULL;
DWORD procesa_id;
HANDLE process;
DWORD ClientDLL;
DWORD EngineDLL;
DWORD ServerDLL;
DWORD Entity;
DWORD GlowP;
DWORD glowingid;
DWORD LocalPlayer;
DWORD GlowObjectsBase;
DWORD ClientState;
DWORD CSPlayerResource;
DWORD classID;
DWORD pEntity;
DWORD tEntity;
DWORD FFlags = 256;
int scoped;
int tmTeam;
int playerIndex;
int playerhealth;
int isdefusing;
int haveKit;
int isdorm;
int objects = 128;
int team2;
int ingame;
int isplanting;
float color[4] = { 255.0f, 255.0f, 255.0f, 0.5f };
bool bools = true;
DWORD dwCSPlayerResource = 52426432;
DWORD dwLoaclPlayer = 14374364;
DWORD m_dwEntityList = 81595996;
DWORD m_vecOrigin = 312;
DWORD m_vecViewOffset = 264;
DWORD m_iHealth = 256;
DWORD m_iTeamNum = 244;
DWORD ELoopDist = 0x10;
DWORD m_dwBoneMatrix = 9896;
DWORD dwClientState = 5820356;
DWORD ClientState2;
DWORD m_bDormant = 237;
DWORD m_dwIndex = 0x00000064;
DWORD m_fFlags = 260;
DWORD m_dwInGame = 0x108;
DWORD PlayerResource;
DWORD m_bSpotted = 2365;
DWORD offisD = 237;
DWORD offGlow = 87134840;
DWORD Defusing = 39292;
DWORD HaveDefuser = 71644;
DWORD StartedPlanting = 0x3370;
DWORD m_bIsScoped = 39284;
DWORD PLocalPlayer;
DWORD PEntity;
int health;
int index;
int spotted;
int indexc;
int dorm;
int myteam;
DWORD PLocalPlayer2;
DWORD PlayerResource2;
int index2;

DWORD dwGetModuleBaseAddress(DWORD dwProcessID, TCHAR * lpszModuleName)
{
	HANDLE hSnapshot = CreateToolhelp32Snapshot(TH32CS_SNAPMODULE, dwProcessID);
	DWORD dwModuleBaseAddress = 0;
	if (hSnapshot != INVALID_HANDLE_VALUE)
	{
		MODULEENTRY32 ModuleEntry32 = { 0 };
		ModuleEntry32.dwSize = sizeof(MODULEENTRY32);
		if (Module32First(hSnapshot, &ModuleEntry32))
		{
			do
			{
				if (_tcscmp(ModuleEntry32.szModule, lpszModuleName) == 0)
				{
					dwModuleBaseAddress = (DWORD)ModuleEntry32.modBaseAddr;
					break;
				}
			} while (Module32Next(hSnapshot, &ModuleEntry32));
		}
		CloseHandle(hSnapshot);
	}
	return dwModuleBaseAddress;
}

void WaitForCsGo()
{
	//if (hWnd > 0)
	//{

	//	hWnd = FindWindow(0, "Counter-Strike: Global Offensive"); //Atrod counter strike logulog

	//}
	if (hWnd == NULL)
	{

		procesa_id = 0;
		process = 0;
		ClientDLL = 0;
		EngineDLL = 0;

		while (hWnd == NULL)
		{

			Sleep(100);
			hWnd = FindWindowA(0, ("Counter-Strike: Global Offensive - Direct3D 9"));

		}
		std::cout << "1/4 Found something" << '\n';
		while (procesa_id == 0)
		{

			Sleep(100);
			GetWindowThreadProcessId(hWnd, &procesa_id); //Atrod procesa Id

		}
		std::cout << "2/4 Found something id" << '\n';
		while (process == 0)
		{

			Sleep(100);
			process = OpenProcess(PROCESS_ALL_ACCESS, FALSE, procesa_id);

		}
		std::cout << "3/4 Opened something" << '\n';
		while (ClientDLL == 0 || EngineDLL == 0)
		{

			Sleep(100);
			char ClientDLLchar[] = "client.dll";
			char EngineDLLchar[] = "engine.dll";
			//string client = "client.dll";
			//TCHAR* ClientDLLchar = CA2T(client.c_str());
			//string engine = "engine.dll";
			//TCHAR* EngineDLLchar = CA2T(engine.c_str());
			ClientDLL = dwGetModuleBaseAddress(procesa_id, ClientDLLchar);
			EngineDLL = dwGetModuleBaseAddress(procesa_id, EngineDLLchar);

		}
		std::cout << "4/4 Get something" << '\n';
	}
}

int main()
{
	std::cout << "Starting..." << '\n';
	WaitForCsGo();
	std::cout << "Found!!!" << '\n';

	while (true)
	{
		Sleep(3);
		ReadProcessMemory(process, (LPCVOID)(EngineDLL + dwClientState), &ClientState, 4, NULL);
		ReadProcessMemory(process, (LPCVOID)(ClientState + m_dwInGame), &ingame, 4, NULL);
		if (ingame == 6)
		{
			ReadProcessMemory(process, (LPCVOID)(ClientDLL + dwLoaclPlayer), &PLocalPlayer2, 4, NULL);
			ReadProcessMemory(process, (LPCVOID)(PLocalPlayer2 + m_iTeamNum), &myteam, 4, NULL);
			ReadProcessMemory(process, (LPCVOID)(ClientDLL + dwCSPlayerResource), &PlayerResource2, 4, NULL);
			ReadProcessMemory(process, (LPCVOID)(PLocalPlayer2 + m_dwIndex), &index2, 4, NULL);
			ReadProcessMemory(process, (LPCVOID)(ClientDLL + offGlow), &GlowP, 4, NULL);
			ReadProcessMemory(process, (LPCVOID)(ClientDLL + offGlow + 0x4), &objects, 4, NULL);
			for (int x = 0; x < objects; x++)
			{
				ReadProcessMemory(process, (LPCVOID)(GlowP + (x * 0x38 + 0x04)), &pEntity, 4, NULL);
				if (pEntity > 0)
				{
					ReadProcessMemory(process, (LPCVOID)(pEntity + 0x8), &classID, 4, NULL);
					ReadProcessMemory(process, (LPCVOID)(classID + 0x8), &classID, 4, NULL);
					ReadProcessMemory(process, (LPCVOID)(classID + 0x1), &classID, 4, NULL);
					ReadProcessMemory(process, (LPCVOID)(classID + 0x14), &classID, 4, NULL);
					if (classID == 40)
					{
						ReadProcessMemory(process, (LPCVOID)(pEntity + offisD), &isdorm, 4, NULL);
						if (!isdorm)
						{
							ReadProcessMemory(process, (LPCVOID)(pEntity + m_iTeamNum), &team2, 4, NULL);
							ReadProcessMemory(process, (LPCVOID)(pEntity + Defusing), &isdefusing, 4, NULL);
							ReadProcessMemory(process, (LPCVOID)(pEntity + HaveDefuser), &haveKit, 4, NULL);
							ReadProcessMemory(process, (LPCVOID)(pEntity + m_dwIndex), &playerIndex, 4, NULL);
							ReadProcessMemory(process, (LPCVOID)(ClientDLL + dwCSPlayerResource), &CSPlayerResource, 4, NULL);
							ReadProcessMemory(process, (LPCVOID)(pEntity + m_bIsScoped), &scoped, 4, NULL);
							ReadProcessMemory(process, (LPCVOID)(pEntity + m_iHealth), &playerhealth, 4, NULL);
							if (team2 != myteam)
							{
								if (isdefusing == 1)
								{
									if (haveKit == 1)
									{
										color[0] = 0.0f;
										color[1] = 1.0f;
										color[2] = 0.5f;
										color[3] = 0.8f;
									}
									else
									{
										color[0] = 1.0f;
										color[1] = 0.0f;
										color[2] = 0.0f;
										color[3] = 1.0f;
									}
								}
								else if (scoped == 1)
								{
									color[0] = 0.5f;
									color[1] = 0.0f;
									color[2] = 1.0f;
									color[3] = 0.8f;
								}
								else if (playerhealth >= 50)
								{

									color[0] = (100 - playerhealth) * 0.02f;
									color[1] = 1.0f;
									color[2] = 0.0f;
									color[3] = 0.8f;
								}
								else
								{
									color[0] = 1.0f;
									color[1] = playerhealth * 0.02f;
									color[2] = 0.0f;
									color[3] = 0.8f;

								}

							}
							else
							{
								color[0] = 0.0f;
								color[1] = 0.0f;
								color[2] = 0.0f;
								color[3] = 0.0f;
							}
							WriteProcessMemory(process, (LPVOID)(GlowP + ((x * 0x38 + 0x04) + 0x4)), color, sizeof(float) * 4, NULL);
							WriteProcessMemory(process, (LPVOID)(GlowP + ((x * 0x38 + 0x04) + 0x24)), &bools, sizeof(bool), NULL);
						}

					}
				}
			}
		}

	}
	return 0;
}