class SSystemGlobalEnvironment;
class IGame;
class IActor;
class IGameFramework;
class SCVars;
class ISystem;

template <typename cData> cData vCall(PVOID pCall, __int64 pIndex)
{
	return (*(cData**)pCall)[pIndex];
}

#define VIRTUAL vCall 

class SSystemGlobalEnvironment
{
public:
	static SSystemGlobalEnvironment* Singleton() 
	{
		return *(SSystemGlobalEnvironment**)0x141D132D0; //search string "scandir"
	}
	IGame* pGame() 
	{ 
		return *(IGame**)((DWORD64)this + 0xC8);
	}
	ISystem* pSystem() 
	{
		return*(ISystem**)((DWORD64)this + 0xE8);
	}
};

class IGame
{
public:
	IGameFramework* GetIGameFramework()
	{
		typedef IGameFramework* (__fastcall * GetIGameFramework)(PVOID64);
		return VIRTUAL<GetIGameFramework>(this, 14)(this);
	}
	SCVars* cVars()
	{
		return (SCVars*)*(DWORD64*)((DWORD64)this + 0x130);
	}
};


class IActor
{
public:
	void Recoil(int Rec)
	{
		VIRTUAL<void(__thiscall*)(PVOID, int)>(this, 91)(this, Rec);
	}
};

class IGameFramework
{
public:
	IActor* GetClientActor()
	{
		IActor* pActor = NULL;
		bool Get_recult = VIRTUAL<bool(__thiscall*)(PVOID, IActor**)>(this, 142)(this, &pActor);
		if (!Get_recult) pActor = NULL;
		return pActor;
	}
};

class SCVars
{
public:
	void i_pelletsDisp(float pValue)
	{
		*(float*)((DWORD64)this + 0x130) = pValue;
	}
	void g_gameroom_afk_timeout(float Value)
	{
		*(float*)((DWORD64)this + 0x7A8) = Value;
		*(float*)((DWORD64)this + 0x7AC) = Value;
	}
	void cl_stand_to_crouch_delay_all(__int64 Value)
	{
		*(__int64*)((DWORD64)this + 0xCF8) = Value;
		*(__int64*)((DWORD64)this + 0xCFC) = Value;
		*(__int64*)((DWORD64)this + 0xD00) = Value;
		*(__int64*)((DWORD64)this + 0xD04) = Value;
		*(__int64*)((DWORD64)this + 0xD08) = Value;
		*(__int64*)((DWORD64)this + 0xD0C) = Value;
	}
};