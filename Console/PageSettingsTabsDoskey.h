
#pragma once

#include "PageSettingsTab.h"

class PageSettingsTabsDoskey
	: public CDialogImpl<PageSettingsTabsDoskey>
	, public CWinDataExchange<PageSettingsTabsDoskey>
	, public PageSettingsTab
{
	public:

		enum { IDD = IDD_SETTINGS_TABS_DOSKEY };

		PageSettingsTabsDoskey();

		BEGIN_DDX_MAP(PageSettingsTabsDoskey)
		END_DDX_MAP()

		BEGIN_MSG_MAP(PageSettingsTabsDoskey)
			MESSAGE_HANDLER(WM_INITDIALOG, OnInitDialog)

			COMMAND_ID_HANDLER(IDC_BTN_DOSKEY_ADD,    OnClickedBtnDoskeyAdd)
			COMMAND_ID_HANDLER(IDC_BTN_DOSKEY_DELETE, OnClickedBtnDoskeyDelete)
			COMMAND_ID_HANDLER(IDC_BTN_DOSKEY_EDIT,   OnClickedBtnDoskeyEdit)
		END_MSG_MAP()

		LRESULT OnInitDialog(UINT /*uMsg*/, WPARAM /*wParam*/, LPARAM /*lParam*/, BOOL& /*bHandled*/);

		LRESULT OnClickedBtnDoskeyAdd   (WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
		LRESULT OnClickedBtnDoskeyDelete(WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);
		LRESULT OnClickedBtnDoskeyEdit  (WORD /*wNotifyCode*/, WORD /*wID*/, HWND /*hWndCtl*/, BOOL& /*bHandled*/);

		void Load(std::shared_ptr<TabData>& tabData);
		void Save();

	private:

		std::shared_ptr<TabData> m_tabData;

		CListViewCtrl       m_listCtrl;
		CEdit               m_editAlias;
		CEdit               m_editCommand;
};

//////////////////////////////////////////////////////////////////////////////
