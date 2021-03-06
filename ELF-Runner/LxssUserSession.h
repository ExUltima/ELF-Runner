#pragma once

class DECLSPEC_UUID("4F476546-B412-4579-B64C-123DF331E3D6") LxssSession;

enum LxssSessionState
{
	LXSS_SESSION_STATE_UNKNOWN,
	LXSS_SESSION_STATE_OK,
};

class DECLSPEC_UUID("8F9E8123-58D4-484A-AC25-7EF7D5F7448F") DECLSPEC_NOVTABLE ILxssInstance : public IUnknown
{
};

class DECLSPEC_UUID("536A6BCF-FE04-41D9-B978-DCACA9A9B5B9") DECLSPEC_NOVTABLE ILxssSession : public IUnknown
{
public:
	virtual HRESULT STDMETHODCALLTYPE Method1() = 0;
	virtual HRESULT STDMETHODCALLTYPE StartDefaultInstance(REFIID iid, LPVOID *ppv) = 0;
	virtual HRESULT STDMETHODCALLTYPE Method3() = 0;
	virtual HRESULT STDMETHODCALLTYPE QueryState(LxssSessionState *state) = 0;
	virtual HRESULT STDMETHODCALLTYPE Method5() = 0; // <-- 2
};
