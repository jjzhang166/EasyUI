#pragma once

class EASY_UI_API CFontFactory
{
protected:
	struct FontID;
private:
	CFontFactory(void){};

public:
	static CFontFactory* GetInst();
	static Gdiplus::Font* GetFont(LPCTSTR szFamily, int nSize,bool bBold = false, bool bUnderline = false, bool bStrikout = false);

	Gdiplus::Font* GetObject(LPCTSTR szFamily, int nSize,bool bBold = false, bool bUnderline = false, bool bStrikout = false);
protected:
	Gdiplus::Font* GetObject(const FontID& fontID);

	struct FontID{
		FontID(LPCTSTR szFamily, int nFontSize, bool bBold = false, bool bUnderline = false, bool bStrikout = false){
			m_strFamily = szFamily;
			m_nSize = nFontSize;
			m_nStyle = Gdiplus::FontStyleRegular;
			if(bBold)m_nStyle |= Gdiplus::FontStyleBold;
			if(bUnderline)m_nStyle |= Gdiplus::FontStyleUnderline;
			if(bStrikout)m_nStyle |= Gdiplus::FontStyleStrikeout;
		}

		bool operator<(const FontID& ref) const{
			return (m_nSize < ref.m_nSize)
					|| (m_nSize == ref.m_nSize && m_nStyle < ref.m_nStyle)
					|| (m_nSize == ref.m_nSize && m_nStyle == ref.m_nStyle && m_strFamily < ref.m_strFamily);
		}

		int m_nSize;
		int m_nStyle;
		std::wstring m_strFamily;
	};

	std::map<FontID, Gdiplus::Font*> m_mapFont;
	typedef std::map<FontID, Gdiplus::Font*>::iterator IterMapFont;
};

