#pragma once
#include <Windows.h>
#include <vector>
#include <iostream>
//#include <utility>

namespace tools {

	
	DWORD applyOffsets(DWORD baseAddress, std::vector<DWORD> offsetList, bool derefLast);


	// Originally used to sigscan for Player class since I had trouble w/ it being multi-level.. Figured it out so these arent used
	int MemCopy(void* lpMem, void* lpSrc, size_t len);
	DWORD FindPattern(DWORD dwAddress, DWORD dwLen, BYTE* bMask, const char* szMask);
	bool bDataCompare(const BYTE* pData, const BYTE* bMask, const char* szMask);
	DWORD GetCodeSize(const char* szModuleName);

}