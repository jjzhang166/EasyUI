#pragma once

class EASY_UI_API CPenFactory
{
protected:
	struct PenID;

private:
	CPenFactory(void){};
public:
	static CPenFactory* GetInst();
	static Gdiplus::Pen* GetPen(Gdiplus::ARGB argb = 0xFF000000, DWORD dwWidth = 3);
	Gdiplus::Pen* GetObject(Gdiplus::ARGB argb = 0xFF000000, DWORD dwWidth = 3);

protected:
	Gdiplus::Pen* GetObject(const PenID& penID);

	struct PenID{
		PenID(Gdiplus::ARGB argb = 0xFF000000, DWORD dwWidth = 3){
			m_argb = argb;
			m_dwWidth = dwWidth;
		}
		bool operator<(const PenID& ref) const {
			return (m_argb<ref.m_argb || (m_argb==ref.m_argb && m_dwWidth<ref.m_dwWidth) );
		}

		Gdiplus::ARGB m_argb;
		DWORD m_dwWidth;
	};

	std::map<PenID, Gdiplus::Pen*> m_mapPen;
	typedef std::map<PenID, Gdiplus::Pen*>::iterator IterMapPen;
};

