#include "stdafx.h"

CDuiLabel::CDuiLabel(CWindowBase* pParent)
	: CWindowBase(pParent)
	, m_bWidthFollowText(false)
	, m_bHeightFollowText(false)
{

}

BOOL CDuiLabel::ParseAttribute( pugi::xml_node& node )
{
	__super::ParseAttribute(node);

	pugi::xml_attribute attr;
	attr = node.attribute(_T("width_follow_text"));
	if(attr){
		m_bWidthFollowText = (_tcsicmp(attr.as_string(),_T("true"))==0);
	}

	attr = node.attribute(_T("height_follow_text"));
	if(attr){
		m_bHeightFollowText = (_tcsicmp(attr.as_string(),_T("true"))==0);
	}

	return TRUE;
}
