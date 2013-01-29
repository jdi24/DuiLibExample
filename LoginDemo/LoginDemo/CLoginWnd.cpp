#include "stdafx.h"
#include "CLoginWnd.h"
#include "debug.h"

CLoginWindow::CLoginWindow()
{
}

CLoginWindow::~CLoginWindow()
{
	PostQuitMessage(0);
}

CDuiString CLoginWindow::GetSkinFolder()
{
	return _T("");
}

CDuiString CLoginWindow::GetSkinFile()
{
	return _T("skin.xml");
}

LPCTSTR CLoginWindow::GetWindowClassName(void) const
{
	return _T("UILogin"); 
}

void CLoginWindow::OnFinalMessage(HWND hWnd) 
{ 
	WindowImplBase::OnFinalMessage(hWnd);
	delete this; 
}

void CLoginWindow::InitWindow()
{
}

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
		else if ( msg.pSender->GetName() == _T("maxbtn") )
		{
			SendMessage(WM_SYSCOMMAND, SC_MAXIMIZE, NULL);
		}
		else if ( msg.pSender->GetName() == _T("restorebtn") )
		{
			SendMessage(WM_SYSCOMMAND, SC_RESTORE, NULL);
		}
	}
}


LRESULT CLoginWindow::HandleMessage(UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	return __super::HandleMessage(uMsg, wParam, lParam);
}

LRESULT CLoginWindow::OnSysCommand(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	BOOL bZoomed = ::IsZoomed(m_hWnd);
	LRESULT lRes = CWindowWnd::HandleMessage(uMsg, wParam, lParam);
	if ( ::IsZoomed(m_hWnd) != bZoomed )
	{
		if ( !bZoomed )
		{
			CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl("maxbtn"));
			if ( pControl ) 
				pControl->SetVisible(false);

			pControl = static_cast<CControlUI*>(m_PaintManager.FindControl("restorebtn"));
			if ( pControl )
				pControl->SetVisible(true);
		}
		else
		{
			CControlUI* pControl = static_cast<CControlUI*>(m_PaintManager.FindControl("maxbtn"));
			if ( pControl )
				pControl->SetVisible(true);

			pControl = static_cast<CControlUI*>(m_PaintManager.FindControl("restorebtn"));
			if ( pControl )
				pControl->SetVisible(false);
		}
	}
	return 0;
}

//LRESULT CLoginWindow::ResponseDefaultKeyEvent(WPARAM wParam)
//{
	//if (wParam == VK_RETURN)
	//{
	//	return FALSE;
	//}
	//else if (wParam == VK_ESCAPE)
	//{
	//	return TRUE;
	//}
	//return FALSE;
//}

UILIB_RESOURCETYPE CLoginWindow::GetResourceType() const
{
	return UILIB_FILE;
}

CControlUI* CLoginWindow::CreateControl(LPCTSTR pstrClass)
{
	return NULL;
}

LRESULT CLoginWindow::HandleCustomMessage(UINT uMsg, WPARAM wParam, LPARAM lParam, BOOL& bHandled)
{
	return 0;
}