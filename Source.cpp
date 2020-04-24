#include "Windows.h"
#include "Offsets.h"
#include "VmtHook.h"

cVmt Vmt;

void SimpleSourse()
{
	IGame* pGame = SSystemGlobalEnvironment::Singleton()->pGame();
	SCVars* gCvar = SSystemGlobalEnvironment::Singleton()->pGame()->cVars();
	IGameFramework* gFrame = SSystemGlobalEnvironment::Singleton()->pGame()->GetIGameFramework();
	if (!pGame || !gCvar || !gFrame) return;
	IActor* mActor = gFrame->GetClientActor();
	if (!mActor) return;
	mActor->Recoil(0); //Recoil
	gCvar->i_pelletsDisp(1000.0f);//Spread
	gCvar->g_gameroom_afk_timeout(10000000000.0f);// AntiAfk
	gCvar->cl_stand_to_crouch_delay_all(0);//Spam x
}

bool __stdcall SystemUpdate(ISystem* System, int Flags, int Pause)
{
	SimpleSourse();
	return Vmt.GetOrigFuntion<bool(__stdcall*)(ISystem*, int, int)>(4)(System, Flags, Pause);
}

unsigned WINAPI Starting(LPVOID lpParam)
{
	while (!GetModuleHandle("mrac64.dll")) Sleep(5000);
	Vmt.bInitialize((PDWORD64*)(SSystemGlobalEnvironment::Singleton()->pSystem()));
	Vmt.dwHookMethod((DWORD64)SystemUpdate, 4);
	return 0L;
}

BOOL APIPRIVATE DllMain(HINSTANCE hModule, DWORD dwReason, LPVOID lpReserv)
{
	UNREFERENCED_PARAMETER(lpReserv);
	switch (dwReason)
	{
	case DLL_PROCESS_ATTACH:
		CloseHandle(CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Starting, 0, 0, 0));
		return TRUE;
	case DLL_PROCESS_DETACH:
		Vmt.UnHook();
		return TRUE;
	}
	return FALSE;
}