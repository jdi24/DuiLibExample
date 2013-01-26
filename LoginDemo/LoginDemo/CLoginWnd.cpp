#include "stdafx.h"
#include "CLoginWnd.h"
#include "debug.h"

void CLoginWindow::Notify(TNotifyUI& msg)
{
	if( msg.sType == _T("click") ) {
		if( msg.pSender->GetName() == _T("closebtn") ) {
			Close();
		}
		else if ( msg.pSender->GetName() == _T("minbtn") )
		{
			SendMessage(WM_SYSCOMMAND, SC_MINIMIZE, NULL);
			return;
		}
	}
}


LRESULT CLoginWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	LRESULT lRes = 0;
	BOOL bHandled = TRUE;
	switch( uMsg ) {
	case WM_CREATE:        lRes = OnCreate(uMsg, wParam, lParam, bHandled); break;
	case WM_NCACTIVATE:    lRes = OnNcActivate(uMsg, wParam, lParam, bHandled); break;
	case WM_NCCALCSIZE:    lRes = OnNcCalcSize(uMsg, wParam, lParam, bHandled); break;
	case WM_NCPAINT:       lRes = OnNcPaint(uMsg, wParam, lParam, bHandled); break;
	case WM_NCHITTEST:     lRes = OnNcHitTest(uMsg, wParam, lParam, bHandled); break;
	case WM_DESTROY:       lRes = OnDestroy(uMsg, wParam, lParam, bHandled); break;
	default:
		bHandled = FALSE;
	}
	if( bHandled ) return lRes;
	if( m_pm.MessageHandler(uMsg, wParam, lParam, lRes) ) return lRes;
	return CWindowWnd::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CLoginWindow::OnCreate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	m_pm.Init(m_hWnd);
	CDialogBuilder builder;
	CControlUI* pRoot = builder.Create(_T("Login.xml"), (UINT)0, NULL, &m_pm);
	ASSERT(pRoot && "Failed to parse XML");
	m_pm.AttachDialog(pRoot);
	m_pm.AddNotifier(this);
	m_pm.AddPreMessageFilter(this);
	return 0;
}

LRESULT CLoginWindow::OnNcActivate(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	if( ::IsIconic(*this) ) bHandled = FALSE;//是否是最小化（图标化）的窗口
	return (wParam == 0) ? TRUE : FALSE;
}

LRESULT CLoginWindow::OnNcCalcSize(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CLoginWindow::OnNcPaint(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}

LRESULT CLoginWindow::OnDestroy(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	::PostQuitMessage(0);
	bHandled = FALSE;
	return 0;
}

LRESULT CLoginWindow::MessageHandler(UINT uMsg, WPARAM wParam, LPARAM lParam, bool& bHandled)
{
	if ( uMsg == WM_KEYDOWN )
	{
		if ( wParam == VK_ESCAPE )
		{
			::PostQuitMessage(0);
			return true;
		}
	}
	return false;
}

LRESULT CLoginWindow::OnNcHitTest(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	POINT pt; pt.x = GET_X_LPARAM(lParam); pt.y = GET_Y_LPARAM(lParam);
	::ScreenToClient(*this, &pt);

	RECT rcClient;
	::GetClientRect(*this, &rcClient);

	RECT rcCaption = m_pm.GetCaptionRect();
	if( pt.x >= rcClient.left + rcCaption.left && pt.x < rcClient.right - rcCaption.right \
		&& pt.y >= rcCaption.top && pt.y < rcCaption.bottom ) {
			CControlUI* pControl = static_cast<CControlUI*>(m_pm.FindControl(pt));
			if( pControl && _tcscmp(pControl->GetClass(), _T("ButtonUI")) != 0 )
				return HTCAPTION;
	}

	return HTCLIENT;
}