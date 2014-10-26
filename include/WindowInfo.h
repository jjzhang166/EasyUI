#pragma once

class CUITopWindow;

//窗口信息类，与TopWindow一一对应
class CWindowInfo{
public:
	CWindowInfo(CUITopWindow* pTopWindow);

	void SetSkinPath(LPCTSTR szPath);
	const std::wstring& GetSkinPath() const { return m_strSkinPath; }
	const std::wstring& GetSkinDir() const { return m_strSkinDir; }//this will call frequently

protected:
	CUITopWindow* m_pTopWindow;//cann't use sp，because maybe stack var, 
	std::wstring m_strSkinPath;
	std::wstring m_strSkinDir;//皮肤文件所在文件夹的路径，之所有用成员变量，是因为静态变量不能适应多窗口程序
};

