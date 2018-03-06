#include "stdafx.h"
#include "GeneralUtilities.h"


CGeneralUtilities::CGeneralUtilities()
{
}


CGeneralUtilities::~CGeneralUtilities()
{
}
CString CGeneralUtilities::GetInputFilePath(CString strTitle, CString strFileDesc, CString strFileExt)
{
	CString ss = strFileDesc + " Files (*." + strFileExt + ")|*." + strFileExt + "||";
	CFileDialog fd(TRUE, strFileExt, "", OFN_HIDEREADONLY | OFN_OVERWRITEPROMPT, ss, NULL);
	fd.m_ofn.lpstrTitle = strTitle;

	if (fd.DoModal() == IDOK)
	{
		return fd.GetPathName().MakeLower();
	}
	return "";
}