#include "PCH.h"
#include "LxssUserSession.h"

// | 46 65 47 4F | 12 B4 | 79 45 | B6 4C 12 3D F3 31 E3 D6 | -> {4F476546-B412-4579-B64C-123DF331E3D6}
static const GUID CLSID_LxssUserSession = { 0x4F476546, 0xB412, 0x4579, { 0xB6, 0x4C, 0x12, 0x3D, 0xF3, 0x31, 0xE3, 0xD6 } };

// | CF 6B 6A 53 | 04 FE | D9 41 | B9 78 DC AC A9 A9 B5 B9 | -> {536A6BCF-FE04-41D9-B978-DCACA9A9B5B9}
static const GUID IID_LxssUserSession = { 0x536A6BCF, 0xFE04, 0x41D9, { 0xB9, 0x78, 0xDC, 0xAC, 0xA9, 0xA9, 0xB5, 0xB9 } };

// | 23 81 9E 8F | D4 58 | 4A 48 | AC 25 7E F7 D5 F7 44 8F | -> {8F9E8123-58D4-484A-AC25-7EF7D5F7448F}
static const GUID IID_Lxss = { 0x8F9E8123, 0x58D4, 0x484A, { 0xAC, 0x25, 0x7E, 0xF7, 0xD5, 0xF7, 0x44, 0x8F } };

static const BYTE Keys[] = {
	0x23, 0x81, 0x9E, 0x8F, 0xD4, 0x58, 0x4A, 0x48, 0xAC, 0x25, 0x7E, 0xF7, 0xD5, 0xF7, 0x44, 0x8F,
	0x46, 0x65, 0x47, 0x4F, 0x12, 0xB4, 0x79, 0x45, 0xB6, 0x4C, 0x12, 0x3D, 0xF3, 0x31, 0xE3, 0xD6,
	0xCF, 0x6B, 0x6A, 0x53, 0x04, 0xFE, 0xD9, 0x41, 0xB9, 0x78, 0xDC, 0xAC, 0xA9, 0xA9, 0xB5, 0xB9
};

static void RunLevel3()
{
	HRESULT hr;

	CComPtr<ILxssUserSession> pLxssUserSession;
	hr = pLxssUserSession.CoCreateInstance(__uuidof(LxssUserSession), NULL, CLSCTX_LOCAL_SERVER);
	if (FAILED(hr))
		AtlThrow(hr);

	CComPtr<ILxss1> p;
	hr = pLxssUserSession->Method2(Keys, reinterpret_cast<LPVOID *>(&p));
	if (FAILED(hr))
	{
		AtlThrow(hr);
	}
}

static void RunLevel2()
{
	HRESULT hr;

	CComPtr<ILxssUserSession> pLxssUserSession;
	hr = pLxssUserSession.CoCreateInstance(__uuidof(LxssUserSession), NULL, CLSCTX_LOCAL_SERVER);
	if (FAILED(hr))
		AtlThrow(hr);

	LxssSessionState nState;
	hr = pLxssUserSession->GetState(&nState);
	if (FAILED(hr))
	{
		AtlThrow(hr);
	}

	if (nState != LXSS_SESSION_STATE_OK)
	{
		AtlThrow(E_FAIL);
	}

	RunLevel3();
}

static void RunLevel1()
{
	auto hr = _Module.Init(nullptr, GetModuleHandle(nullptr));
	if (FAILED(hr))
	{
		AtlThrow(hr);
	}

	__try
	{
		RunLevel2();
	}
	__finally
	{
		_Module.Term();
	}
}

int wmain(int argc, wchar_t *argv[])
{
	if (argc != 2)
	{
		std::wcerr << L"Usage: " << argv[0] << L" FILE" << std::endl;
		return EXIT_FAILURE;
	}

	auto hr = CoInitializeEx(nullptr, COINIT_APARTMENTTHREADED);
	if (FAILED(hr))
	{
		std::cerr << "Failed to initialize COM: " << std::system_category().message(hr) << std::endl;
		return EXIT_FAILURE;
	}

	int nResult;

	try
	{
		RunLevel1();
		nResult = EXIT_SUCCESS;
	}
	catch (CAtlException& e)
	{
		std::cerr << std::system_category().message(e) << std::endl;
		nResult = EXIT_FAILURE;
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
		nResult = EXIT_FAILURE;
	}

	CoUninitialize();

	return nResult;
}
