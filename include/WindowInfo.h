#pragma once

class CUITopWindow;

//������Ϣ�࣬��TopWindowһһ��Ӧ
class CWindowInfo{
public:
	CWindowInfo(CUITopWindow* pTopWindow);

	void SetSkinPath(LPCTSTR szPath);
	const std::wstring& GetSkinPath() const { return m_strSkinPath; }
	const std::wstring& GetSkinDir() const { return m_strSkinDir; }//this will call frequently

protected:
	CUITopWindow* m_pTopWindow;//cann't use sp��because maybe stack var, 
	std::wstring m_strSkinPath;
	std::wstring m_strSkinDir;//Ƥ���ļ������ļ��е�·����֮�����ó�Ա����������Ϊ��̬����������Ӧ�ര�ڳ���
};

