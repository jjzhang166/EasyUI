
CComModule _Module;

#include <comutil.h>

class CInternalWebBrowser
	: public CWindowImpl<CInternalWebBrowser, CAxWindow>
{
public:
	CInternalWebBrowser(CUIWebBrowser* pUIWebBrowser)
		: m_pUIWebBrowser(pUIWebBrowser)
	{}
	
	BOOL Show(){
		if(m_hWnd){
			ShowWindow(SW_SHOW);
			CRect rcWnd;
			m_pUIWebBrowser->GetRect(rcWnd);
			return SetWindowPos(NULL, rcWnd, SWP_SHOWWINDOW);
		}
		else{
			return FALSE;
		}
	};

	BOOL Create(){
		assert(m_hWnd==NULL);
		if(m_hWnd == NULL){
			CRect rcWnd;
			CWindowImpl::Create(m_pUIWebBrowser->GetRootHandle(),rcWnd,NULL);
			CreateControl(_T("{8856F961-340A-11D0-A96B-00C04FD705A2}"));
			HRESULT hr = QueryControl(&m_webBrowser2);
			ATLASSERT(SUCCEEDED(hr));
			if(SUCCEEDED(hr)){
				m_webBrowser2->put_Silent(VARIANT_TRUE);
			}
		}

		return TRUE;
	};

	BOOL Hide(){
		if(m_hWnd){
			return ShowWindow(SW_HIDE);
		}
		else{
			return FALSE;
		}
	};

	BOOL RePos(bool bForce = false){
		if(m_hWnd && (bForce || IsWindowVisible())){
			CRect rcWnd;
			m_pUIWebBrowser->GetRect(rcWnd);
			return SetWindowPos(NULL,rcWnd,SWP_SHOWWINDOW);
		}
		else{
			return TRUE;
		}
	}

	BOOL Navigate(LPCTSTR szUrl){
		ATLASSERT(szUrl);

		if(!m_hWnd){
			return FALSE;
		}

		HRESULT hr = -1;
		if(m_hWnd && szUrl && m_webBrowser2 && _tcslen(szUrl)>0){
			variant_t url(szUrl);
			hr = m_webBrowser2->Navigate2(&url, NULL, NULL, NULL, NULL);
		}
		
		return SUCCEEDED(hr)?TRUE:FALSE;
	}

	BEGIN_MSG_MAP(CInternalWebBrowser)
	END_MSG_MAP()

private:
	CUIWebBrowser* m_pUIWebBrowser;
	CComPtr<IWebBrowser2> m_webBrowser2;
};

