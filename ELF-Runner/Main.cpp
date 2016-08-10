#include "PCH.h"
#include "LxssUserSession.h"

static VOID RunLevel2()
{
	HRESULT hr;

	CComPtr<ILxssSession> pLxssSession;
	hr = pLxssSession.CoCreateInstance(__uuidof(LxssSession), NULL, CLSCTX_LOCAL_SERVER);
	if (FAILED(hr))
		AtlThrow(hr);

	CComPtr<ILxssInstance> pLxssInstance;
	hr = pLxssSession->StartDefaultInstance(__uuidof(ILxssInstance), reinterpret_cast<LPVOID *>(&pLxssInstance));
	if (FAILED(hr))
		AtlThrow(hr);
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
