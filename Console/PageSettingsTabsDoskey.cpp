#include "stdafx.h"
#include "resource.h"

#include "PageSettingsTabsDoskey.h"

extern std::shared_ptr<SettingsHandler>	g_settingsHandler;

PageSettingsTabsDoskey::PageSettingsTabsDoskey()
: m_tabData()
{
}

LRESULT PageSettingsTabsDoskey::OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/)
{
	ExecuteDlgInit(IDD);

	if (CTheme().IsThemingSupported()) ::EnableThemeDialogTexture(m_hWnd, ETDT_USETABTEXTURE);

	m_listCtrl.Attach(GetDlgItem(IDC_LIST_DOSKEY));
	m_listCtrl.SetExtendedListViewStyle(m_listCtrl.GetExtendedListViewStyle() | LVS_EX_FULLROWSELECT | LVS_EX_CHECKBOXES);

	m_listCtrl.InsertColumn(0, Helpers::LoadStringW(IDS_SETTINGS_ALIAS).c_str());
	m_listCtrl.InsertColumn(1, Helpers::LoadStringW(IDS_SETTINGS_COMMAND2).c_str());

	m_listCtrl.SetColumnWidth(0, 80);
	m_listCtrl.SetColumnWidth(1, LVSCW_AUTOSIZE_USEHEADER);

	m_editAlias.Attach(GetDlgItem(IDC_DOSKEY_ALIAS));
	m_editCommand.Attach(GetDlgItem(IDC_DOSKEY_COMMAND));

	return TRUE;
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

void PageSettingsTabsDoskey::Load(std::shared_ptr<TabData>& tabData)
{
	m_tabData = tabData;

	DoDataExchange(DDX_LOAD);

	m_listCtrl.DeleteAllItems();
	for(size_t i = 0; i < m_tabData->doskeyAliases.size(); ++i)
	{
		int nItem = m_listCtrl.InsertItem(m_listCtrl.GetItemCount(), m_tabData->doskeyAliases[i]->strAlias.c_str());
		m_listCtrl.SetCheckState(nItem, m_tabData->doskeyAliases[i]->bChecked);

		m_listCtrl.SetItemText(nItem, 1, m_tabData->doskeyAliases[i]->strCommand.c_str());
	}
}

void PageSettingsTabsDoskey::Save()
{
	DoDataExchange(DDX_SAVE);

	m_tabData->doskeyAliases.clear();

	for(int nItem = 0; nItem < m_listCtrl.GetItemCount(); ++nItem)
	{
		CString strAlias;
		m_listCtrl.GetItemText(nItem, 0, strAlias);
		CString strCommand;
		m_listCtrl.GetItemText(nItem, 1, strCommand);

		std::shared_ptr<DoskeyAlias> alias(new DoskeyAlias);
		alias->strAlias = strAlias.GetString();
		alias->strCommand = strCommand.GetString();
		alias->bChecked = m_listCtrl.GetCheckState(nItem)? true : false;
		m_tabData->doskeyAliases.push_back(alias);
	}
}

//////////////////////////////////////////////////////////////////////////////


//////////////////////////////////////////////////////////////////////////////

LRESULT PageSettingsTabsDoskey::OnClickedBtnDoskeyAdd(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	CString strAlias;
	m_editAlias.GetWindowText(strAlias);

	CString strCommand;
	m_editCommand.GetWindowText(strCommand);

	LVFINDINFO findInfo;
	findInfo.flags = LVFI_STRING;
	findInfo.psz = strAlias.GetString();
	int nItem = m_listCtrl.FindItem(&findInfo, -1);

	if( nItem == -1 )
	{
		nItem = m_listCtrl.InsertItem(m_listCtrl.GetItemCount(), strAlias);
		m_listCtrl.SetCheckState(nItem, TRUE);
	}

	m_listCtrl.SetItemText(nItem, 1, strCommand);

	return 0;
}

LRESULT PageSettingsTabsDoskey::OnClickedBtnDoskeyDelete(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	int nItem = m_listCtrl.GetSelectedIndex();
	if( nItem < 0 || nItem >= m_listCtrl.GetItemCount() ) return 0;

	m_listCtrl.DeleteItem(nItem);

	return 0;
}

LRESULT PageSettingsTabsDoskey::OnClickedBtnDoskeyEdit(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/)
{
	int nItem = m_listCtrl.GetSelectedIndex();
	if( nItem < 0 || nItem >= m_listCtrl.GetItemCount() ) return 0;

	CString strAlias;
	m_listCtrl.GetItemText(nItem, 0, strAlias);
	CString strCommand;
	m_listCtrl.GetItemText(nItem, 1, strCommand);

	m_editAlias.SetWindowText(strAlias);
	m_editCommand.SetWindowText(strCommand);

	return 0;
}
