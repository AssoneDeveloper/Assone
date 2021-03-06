class cVmt
{
public:
	void bInitialize(PDWORD64* ppdwClassBase)
	{
		m_ppdwClassBase = ppdwClassBase;
		m_pdwOldVMT = *ppdwClassBase;
		m_dwVMTSize = dwGetVMTCount(*ppdwClassBase);
		m_pdwNewVMT = new DWORD64[m_dwVMTSize];
		memcpy(m_pdwNewVMT, m_pdwOldVMT, sizeof(DWORD64) * m_dwVMTSize);
		*ppdwClassBase = m_pdwNewVMT;
	}
	void ReLoad(PDWORD64* ppdwClassBase)
	{
		m_ppdwClassBase = ppdwClassBase;
		m_pdwOldVMT = *ppdwClassBase;
		*ppdwClassBase = m_pdwNewVMT;
	}
	void bInitialize(PDWORD64** pppdwClassBase)
	{
		bInitialize(*pppdwClassBase);
	}
	void UnHook(void)
	{
		if (m_ppdwClassBase)*m_ppdwClassBase = m_pdwOldVMT;
	}
	void ReHook(void)
	{
		if (m_ppdwClassBase)*m_ppdwClassBase = m_pdwNewVMT;
	}
	int iGetFuncCount(void)
	{
		return (int)m_dwVMTSize;
	}
	DWORD64 dwGetMethodAddress(int Index)
	{
		if (Index >= 0 && Index <= (int)m_dwVMTSize && m_pdwOldVMT != 0)
			return m_pdwOldVMT[Index];
		return 0;
	}
	PDWORD64 pdwGetOldVMT(void) { return m_pdwOldVMT; }
	PDWORD64 pdwGetNewVMT(void) { return m_pdwNewVMT; }
	DWORD64 dwHookMethod(DWORD64 dwNewFunc, unsigned int iIndex)
	{
		if (m_pdwNewVMT && m_pdwOldVMT && iIndex <= m_dwVMTSize && iIndex >= 0)
		{
			m_pdwNewVMT[iIndex] = dwNewFunc;
			return m_pdwOldVMT[iIndex];
		}
		return 0;
	}
	template <class cData> cData GetOrigFuntion(UINT index)
	{
		return (cData)m_pdwOldVMT[index];
	}
private:
	DWORD64 dwGetVMTCount(PDWORD64 pdwVMT)
	{
		DWORD64 dwIndex = 0;
		for (dwIndex = 0; pdwVMT[dwIndex]; dwIndex++)
			if ((IsBadCodePtr)((FARPROC)pdwVMT[dwIndex]))
				break;
		return dwIndex;
	}
	PDWORD64* m_ppdwClassBase;
	PDWORD64	m_pdwNewVMT, m_pdwOldVMT;
	DWORD64	m_dwVMTSize;
};