#pragma once

class EASYUI_API CEasyUIApp{
protected:
	CEasyUIApp();
	~CEasyUIApp();

public:
	static CEasyUIApp* GetInst();

	void InitApp(){};

	void SetResourceModule(HMODULE hModule);
	HMODULE GetResourceModule();

	int Run();

private:
	HMODULE m_hResourceModule;
	CGdiplusInit m_gidplusInit;
};


