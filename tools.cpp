#include "tools.h"





DWORD tools::applyOffsets(DWORD baseAddress, std::vector<DWORD> offsetList, bool derefLast)
{

	DWORD* tmp = nullptr;
	DWORD listLength = offsetList.size();
	DWORD addr = 0;
	for (DWORD i = 1; i <= listLength; i++) {
		if (i == 1) {
			addr = baseAddress + offsetList[0];
		}
		else {
			addr += offsetList[i - 1];
		}

		tmp = (DWORD*)addr;

		if (i == listLength && !derefLast)
			break;
		else
			addr = *tmp;

	}

	return addr;

}


int tools::MemCopy(void* lpMem, void* lpSrc, size_t len)
{
	DWORD flNewProtect = PAGE_READWRITE, lpflOldProtect;
	unsigned char* pDst = (unsigned char*)lpMem, * pSrc = (unsigned char*)lpSrc;

	if (VirtualProtect(lpMem, len, flNewProtect, &lpflOldProtect))
	{
		while (len-- > 0) *pDst++ = *pSrc++;
		return 0;
	}

	return 1;
}




DWORD tools::FindPattern(DWORD dwAddress, DWORD dwLen, BYTE* bMask, const char* szMask)
{
	for (DWORD i = 0; i < dwLen; i++)
		if (bDataCompare((BYTE*)(dwAddress + i), bMask, szMask))
			return (DWORD)(dwAddress + i);

	return 0;
}

bool tools::bDataCompare(const BYTE* pData, const BYTE* bMask, const char* szMask)
{
	for (; *szMask; ++szMask, ++pData, ++bMask)
		if (*szMask == 'x' && *pData != *bMask)
			return false;
	return (*szMask) == NULL;
}

DWORD tools::GetCodeSize(const char* szModuleName)
{
	HMODULE hModule = GetModuleHandleA(szModuleName);

	if (!hModule)
		return NULL;

	PIMAGE_DOS_HEADER pDosHeader = PIMAGE_DOS_HEADER(hModule);

	if (!pDosHeader)
		return NULL;

	PIMAGE_NT_HEADERS pNTHeader = PIMAGE_NT_HEADERS((LONG)hModule + pDosHeader->e_lfanew);

	if (!pNTHeader)
		return NULL;

	PIMAGE_OPTIONAL_HEADER pOptionalHeader = &pNTHeader->OptionalHeader;

	if (!pOptionalHeader)
		return NULL;

	return pOptionalHeader->SizeOfCode;
}
