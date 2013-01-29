#pragma  once

class CLoginWindow : public WindowImplBase
{

public:
	CLoginWindow();
	~CLoginWindow();

public:
	LPCTSTR GetWindowClassName(void) const;
	virtual void OnFinalMessage(HWND hWnd);
	virtual void InitWindow();
	//virtual LRESULT ResponseDefaultKeyEvent(WPARAM wParam);
	virtual	UILIB_RESOURCETYPE GetResourceType() const;
	virtual CDuiString GetSkinFolder();
	virtual CDuiString GetSkinFile();
	virtual CControlUI* CreateControl(LPCTSTR pstrClass);
	LRESULT HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam);
	LRESULT OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);
	LRESULT HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled);

protected:
	void Notify(TNotifyUI& msg);
};
