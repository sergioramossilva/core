
#include "GlobalsSubstream.h"
#include <Logic/Biff_records/BOF.h>
#include <Logic/Biff_records/WriteProtect.h>
#include <Logic/Biff_records/FilePass.h>
#include <Logic/Biff_records/Template.h>
#include <Logic/Biff_unions/INTERFACE.h>
#include <Logic/Biff_records/WriteAccess.h>
#include <Logic/Biff_records/FileSharing.h>
#include <Logic/Biff_records/CodePage.h>
#include <Logic/Biff_records/Lel.h>
#include <Logic/Biff_records/DSF.h>
#include <Logic/Biff_records/Excel9File.h>
#include <Logic/Biff_records/RRTabId.h>
#include <Logic/Biff_records/ObProj.h>
#include <Logic/Biff_records/ObNoMacros.h>
#include <Logic/Biff_records/CodeName.h>
#include <Logic/Biff_unions/FNGROUPS.h>
#include <Logic/Biff_records/Lbl.h>
#include <Logic/Biff_records/OleObjectSize.h>
#include <Logic/Biff_unions/PROTECTION.h>
#include <Logic/Biff_records/Window1.h>
#include <Logic/Biff_records/Backup.h>
#include <Logic/Biff_records/HideObj.h>
#include <Logic/Biff_records/Date1904.h>
#include <Logic/Biff_records/CalcPrecision.h>
#include <Logic/Biff_records/RefreshAll.h>
#include <Logic/Biff_records/BookBool.h>
#include <Logic/Biff_unions/FORMATTING.h>
#include <Logic/Biff_unions/PIVOTCACHEDEFINITION.h>
#include <Logic/Biff_unions/DOCROUTE.h>
#include <Logic/Biff_records/UserBView.h>
#include <Logic/Biff_records/UsesELFs.h>
#include <Logic/Biff_unions/BUNDLESHEET.h>
#include <Logic/Biff_unions/METADATA.h>
#include <Logic/Biff_records/MTRSettings.h>
#include <Logic/Biff_records/ForceFullCalculation.h>
#include <Logic/Biff_records/Country.h>
#include <Logic/Biff_unions/SUPBOOK.h>
#include <Logic/Biff_unions/LBL.h>
#include <Logic/Biff_unions/RTD.h>
#include <Logic/Biff_records/RecalcId.h>
#include <Logic/Biff_records/HFPicture.h>
#include <Logic/Biff_unions/MSODRAWINGGROUP.h>
#include <Logic/Biff_unions/SHAREDSTRINGS.h>
#include <Logic/Biff_records/ExtSST.h>
#include <Logic/Biff_records/WebPub.h>
#include <Logic/Biff_records/WOpt.h>
#include <Logic/Biff_records/CrErr.h>
#include <Logic/Biff_records/BookExt.h>
#include <Logic/Biff_records/FeatHdr.h>
#include <Logic/Biff_records/DConn.h>
#include <Logic/Biff_unions/THEME.h>
#include <Logic/Biff_records/CompressPictures.h>
#include <Logic/Biff_records/Compat12.h>
#include <Logic/Biff_records/GUIDTypeLib.h>
#include <Logic/Biff_records/EOF.h>
#include <Logic/Biff_records/BOF.h>
#include <Logic/Biff_records/MDTInfo.h>

namespace XLS
{;

GlobalsSubstream::GlobalsSubstream(const unsigned short code_page)
:	code_page_(code_page)
{
}

GlobalsSubstream::~GlobalsSubstream()
{
}


BaseObjectPtr GlobalsSubstream::clone()
{
	return BaseObjectPtr(new GlobalsSubstream(*this));
}


// class Parenthesis_Window1_Backup_HideObj_Date1904 : public ABNFParenthesis
// {
// public:
// 	BaseObjectPtr clone()
// 	{
// 		return BaseObjectPtr(new Parenthesis_OO_order_workaround_1(*this));
// 	}
// 
// 	const bool loadContent(BinProcessor& proc)
// 	{
// 		if(!proc.mandatory<SXAddl_SXCCacheField_SXDCaption>())
// 		{
// 			return false;
// 		}
// 		proc.repeated<Continue_SxaddlSxString>(0, 0);
// 		return true;
// 	};
// };
// 


/*
WORKBOOKCONTENT = [WriteProtect] [FilePass] [Template] INTERFACE WriteAccess [FileSharing] CodePage 
					*2047Lel DSF [Excel9File] RRTabId [ObProj] [ObNoMacros] [CodeName [FNGROUPS] *Lbl 
					[OleObjectSize] PROTECTION 1*Window1 Backup HideObj Date1904 CalcPrecision RefreshAll 
					BookBool FORMATTING *(PIVOTCACHEDEFINITION) [DOCROUTE] *UserBView UsesELFs 1*BUNDLESHEET 
					METADATA [MTRSettings] [ForceFullCalculation] Country *SUPBOOK *LBL *RTD [RecalcId] 
					*HFPicture *MSODRAWINGGROUP [SHAREDSTRINGS] ExtSST *WebPub [WOpt] [CrErr] [BookExt] 
					*FeatHdr *DConn [THEME] [CompressPictures] [Compat12] [GUIDTypeLib] EOF
WORKBOOK = BOF WORKBOOKCONTENT
*/
const bool GlobalsSubstream::loadContent(BinProcessor& proc)
{
	int count = 0;

	if(!proc.mandatory<BOF>())
	{
		return false;
	}

	BOF* bof = dynamic_cast<BOF*>(elements_.back().get());
	
	if (bof->vers < 0x0600) //testdoc01.xls
	{
		proc.getGlobalWorkbookInfo()->Version = bof->vers;
		return false;
	}
	proc.optional<WriteProtect>();
	proc.optional<FilePass>();
	if (proc.optional<Template>())
	{
		m_Template = elements_.back();
		elements_.pop_back();
	}
	proc.mandatory<INTERFACE_T>();
	proc.mandatory<WriteAccess>();
	proc.optional<FileSharing>();
	if (proc.mandatory<CodePage>())
	{
		m_CodePage = elements_.back();
		elements_.pop_back();

		CodePage *CodePage_ = dynamic_cast<CodePage*>(m_CodePage.get());

		if ((CodePage_) && (CodePage_->cv != 0/* && CodePage_->cv != 1200*/))
			code_page_ = CodePage_->cv;

		proc.getGlobalWorkbookInfo()->CodePage = code_page_;
	}
	proc.repeated<Lel>(0, 2047);
	proc.mandatory<DSF>();
	proc.optional<Excel9File>();
	proc.mandatory<RRTabId>(); // Make optional if more than 4112 sheets
	proc.optional<ObProj>();
	proc.optional<ObNoMacros>();
	proc.optional<CodeName>();
	proc.optional<FNGROUPS>();
	proc.repeated<Lbl>(0, 0);
	proc.optional<OleObjectSize>();
	proc.mandatory<PROTECTION>();

	proc.repeated<Window1>(0, 0); // OpenOffice Calc stored files workaround (Window1 must exist at least once according to [MS-XLS])
	proc.mandatory<Backup>();
	proc.mandatory<HideObj>();
	proc.repeated<Window1>(0, 0); // OpenOffice Calc stored files workaround
	proc.mandatory<Date1904>();
	
	proc.mandatory<CalcPrecision>();
	proc.mandatory<RefreshAll>();
	proc.mandatory<BookBool>();
	if (proc.optional<Country>()) // OpenOffice Calc stored files workaround
	{
		m_Country = elements_.back();
		elements_.pop_back();

		Country *Country_ = dynamic_cast<Country*>(m_Country.get());
		if (Country_)
		{
			int countryDef = Country_->iCountryDef;
			int countryWinIni = Country_->iCountryWinIni;

			proc.getGlobalWorkbookInfo()->CodePage;
		}
	}
	proc.optional<UsesELFs>(); // OpenOffice Calc stored files workaround
	proc.optional<RecalcId>(); // OpenOffice Calc stored files workaround
	proc.repeated<Window1>(0, 0); // OpenOffice Calc stored files workaround

	if (proc.mandatory<FORMATTING>())
	{
		m_Formating = elements_.back();
		elements_.pop_back();

		FORMATTING* fmts = dynamic_cast<FORMATTING*>(m_Formating.get());
		if (fmts)
		{
			proc.getGlobalWorkbookInfo()->m_arFonts = &fmts->m_arFonts;
		}
	}

	proc.repeated<PIVOTCACHEDEFINITION>(0, 0);
	proc.optional<DOCROUTE>();
	proc.repeated<UserBView>(0, 0);
	
	proc.optional<UsesELFs>();
	proc.repeated<BUNDLESHEET>(1, 0);
	proc.optional<METADATA>(); // Let it be optional
	proc.optional<MTRSettings>();
	proc.optional<ForceFullCalculation>();

	if (proc.optional<Country>())
	{
		m_Country = elements_.back();
		elements_.pop_back();

		Country *Country_ = dynamic_cast<Country*>(m_Country.get());
		if (Country_)
		{
			int countryDef = Country_->iCountryDef;
			int countryWinIni = Country_->iCountryWinIni;

			proc.getGlobalWorkbookInfo()->CodePage;
		}
	}
	proc.repeated<SUPBOOK>(0, 0);
	
	count = proc.repeated<LBL>(0, 0);
	while(count > 0)
	{
		m_arLBL.insert(m_arLBL.begin(), elements_.back());
		elements_.pop_back();
		count--;
	}
	proc.repeated<RTD>(0, 0);

	proc.optional<RecalcId>();
	
	count = proc.repeated<HFPicture>(0, 0);
	while(count > 0)
	{
		m_arHFPicture.insert(m_arHFPicture.begin(), elements_.back());
		elements_.pop_back();
		count--;
	}
	
    MSODRAWINGGROUP mso_drawiing_group(false);
    count = proc.repeated(mso_drawiing_group, 0, 0);
	while(count > 0)
	{
		m_arMSODRAWINGGROUP.insert(m_arMSODRAWINGGROUP.begin(), elements_.back());
		elements_.pop_back();
		count--;
	}
	proc.repeated<SUPBOOK>(0, 0);//order_history.xls

    SHAREDSTRINGS shared_strings(code_page_);
    if (proc.optional(shared_strings))
	{
		m_SHAREDSTRINGS = elements_.back();
		elements_.pop_back();
	}
	
	proc.optional<ExtSST>(); // OpenOffice Calc stored files workaround (ExtSST is mandatory according to [MS-XLS])
	proc.repeated<WebPub>(0, 0);
	proc.optional<WOpt>();
	proc.optional<CrErr>();
	proc.optional<BookExt>();

    FeatHdr feat_hdr(true);
    proc.repeated(feat_hdr, 0, 0);

    proc.repeated<DConn>(0, 0);
	
	if (proc.optional<THEME>())
	{
		m_Theme = elements_.back();
		elements_.pop_back();
	}
	proc.optional<CompressPictures>();
	proc.optional<Compat12>();
	proc.optional<GUIDTypeLib>();

#pragma message("####################### Some trash records may be skipped here")
	proc.SeekToEOF(); // Thus we skip problems with the trash at the end of the stream (found in Domens.xls)
	
	proc.mandatory<EOF_T>();

	return true;
}

} // namespace XLS
