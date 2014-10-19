#pragma once

class EASYUI_API CSmartDC{
public:
	CSmartDC(HDC hDC, const LPRECT lprc){
		Init();
		PrepareGdiObject(hDC,NULL,lprc);
	}

	CSmartDC(HDC hDC, HBITMAP hBitmap){
		Init();
		PrepareGdiObject(hDC,hBitmap,NULL);
	}

	~CSmartDC(){
		DestroyGdiObject();
		UnInit();
	}

	HDC GetDC(){
		return m_memDC.m_hDC;
	}

	HBITMAP GetBitmap(){
		return m_hMemBmp;
	}

	void GetBitmapRect(CRect& rcBitmap){
		rcBitmap = m_rcBitmap;
	}

	BOOL BitBlt(const LPRECT lprcDst = NULL,const LPRECT lprcSrc = NULL){
		ATLASSERT(m_hSrcDC && m_memDC.m_hDC);

		CRect rcDst;
		CRect rcSrc;
		if(lprcDst){
			rcDst = *lprcDst;
		}
		else{
			rcDst = m_rcBitmap;
		}

		if(lprcSrc){
			rcSrc = *lprcSrc;
		}
		else{
			rcSrc = m_rcBitmap;
			rcSrc.MoveToXY(0,0);
		}

		::BitBlt(m_hSrcDC,rcDst.left,rcDst.top,rcDst.Width(),rcDst.Height(),m_memDC.m_hDC,rcSrc.left,rcSrc.top,SRCCOPY);

		return TRUE;
	}

private:
	CSmartDC& operator=(const CSmartDC& ref);

protected:
	void Init(){
		m_bNeedDestroyBitmap = false;
		m_hSrcDC = NULL;
		m_hOldBmp = NULL;
		m_hMemBmp = NULL;
	}

	void UnInit(){
		m_bNeedDestroyBitmap = false;
		m_hSrcDC = NULL;
		m_hOldBmp = NULL;
		m_hMemBmp = NULL;
	}

	BOOL PrepareGdiObject(HDC hDC, HBITMAP hBitmap = NULL, const LPRECT lprc = NULL){
		ATLASSERT(hDC && (hBitmap || lprc) );

		m_hSrcDC = hDC;
		m_memDC.CreateCompatibleDC(m_hSrcDC);
		if(hBitmap){
			m_hMemBmp = hBitmap;

			SIZE sz;
			GetBitmapDimensionEx(m_hMemBmp,&sz);
			m_rcBitmap.SetRect(0,0,sz.cx,sz.cy);
		}
		else if(lprc){
			m_hMemBmp = ::CreateCompatibleBitmap(m_hSrcDC, lprc->right-lprc->left, lprc->bottom-lprc->top);
			m_bNeedDestroyBitmap = true;
			m_rcBitmap = *lprc;
		}

		ATLASSERT(m_hMemBmp);
		m_hOldBmp = m_memDC.SelectBitmap(m_hMemBmp);

		return TRUE;
	}

	BOOL DestroyGdiObject(){
		HBITMAP hBitmap = m_memDC.SelectBitmap(m_hOldBmp);
		if(m_bNeedDestroyBitmap){
			::DeleteObject(hBitmap);
		}

		return TRUE;
	}
	
private:
	HDC m_hSrcDC;
	CRect m_rcBitmap;
	HBITMAP m_hOldBmp;
	HBITMAP m_hMemBmp;
	CDC m_memDC;
	bool m_bNeedDestroyBitmap;
};
