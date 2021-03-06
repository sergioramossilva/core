﻿/*
 * (c) Copyright Ascensio System SIA 2010-2016
 *
 * This program is a free software product. You can redistribute it and/or
 * modify it under the terms of the GNU Affero General Public License (AGPL)
 * version 3 as published by the Free Software Foundation. In accordance with
 * Section 7(a) of the GNU AGPL its Section 15 shall be amended to the effect
 * that Ascensio System SIA expressly excludes the warranty of non-infringement
 * of any third-party rights.
 *
 * This program is distributed WITHOUT ANY WARRANTY; without even the implied
 * warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR  PURPOSE. For
 * details, see the GNU AGPL at: http://www.gnu.org/licenses/agpl-3.0.html
 *
 * You can contact Ascensio System SIA at Lubanas st. 125a-25, Riga, Latvia,
 * EU, LV-1021.
 *
 * The  interactive user interfaces in modified source and object code versions
 * of the Program must display Appropriate Legal Notices, as required under
 * Section 5 of the GNU AGPL version 3.
 *
 * Pursuant to Section 7(b) of the License you must retain the original Product
 * logo when distributing the program. Pursuant to Section 7(e) we decline to
 * grant you any rights under trademark law for use of our trademarks.
 *
 * All the Product's GUI elements, including illustrations and icon sets, as
 * well as technical writing content are licensed under the terms of the
 * Creative Commons Attribution-ShareAlike 4.0 International. See the License
 * terms at http://creativecommons.org/licenses/by-sa/4.0/legalcode
 *
 */
#pragma once 
#include "Basic.h"

#include "Utils.h"
#include "RtfProperty.h"

class RtfAbsPosTab : public IDocumentElement
{
public: 
	enum Leader
	{	l_none,
		l_ptablnone, //\ptablnone 	Absolute position tab with a blank leading (default).
		l_ptabldot, //\ptabldot 	Absolute position tab with a leading that uses period symbols (.....).
		l_ptablminus, //\ptablminus 	Absolute position tab with a leading that uses minus symbols (-----).
		l_ptabluscore, //\ptabluscore 	Absolute position tab with a leading that uses underscore symbols (_____).
		l_ptablmdot, //\ptablmdot 	Absolute position tab with a leading that uses middle dot symbols (•••••).
	} ;
	enum Alignment
	{	a_none,
		a_left,
		a_center,
		a_right,
	};
 
	enum Relative	
	{	r_none,
		r_margin,
		r_indent,
	} ;

	Leader		m_eLeader;
	Alignment	m_eAlignment;
	Relative	m_eRelative;

	RtfAbsPosTab()
	{
	}
	bool IsValid()
	{
		return a_none != m_eAlignment && r_none != m_eRelative;
	}
	
	CString RenderToRtf(RenderParameter oRenderParameter)
	{
		CString sResult;
		switch( m_eLeader )
		{
			case l_ptablnone:	sResult += _T("\\ptablnone");	break;
			case l_ptabldot:	sResult += _T("\\ptabldot");	break;
			case l_ptablminus:	sResult += _T("\\ptablminus");	break;
			case l_ptabluscore: sResult += _T("\\ptabluscore");	break;
			case l_ptablmdot:	sResult += _T("\\ptablmdo");	break;
		}
		switch( m_eRelative )
		{
			case r_margin: sResult += _T("\\pmartabq");	break;
			case r_indent: sResult += _T("\\pindtabq");	break;
		}
		switch( m_eAlignment )
		{
			case a_left:	sResult += _T("l");	break;
			case a_center:	sResult += _T("c");	break;
			case a_right:	sResult += _T("r");	break;
		}
		if( false == sResult.IsEmpty() )
			sResult = _T("{") + sResult + _T("}");
		return sResult;
	}
	CString RenderToOOX(RenderParameter oRenderParameter)
	{
		CString sResult;
		switch( m_eLeader )
		{
			case l_ptablnone:	sResult += _T(" w:leader=\"none\"");		break;
			case l_ptabldot:	sResult += _T(" w:leader=\"dot\"");			break;
			case l_ptablminus:	sResult += _T(" w:leader=\"hyphen\"");		break;
			case l_ptabluscore: sResult += _T(" w:leader=\"underscore\"");	break;
			case l_ptablmdot:	sResult += _T(" w:leader=\"middleDot\"");	break;
		}
		switch( m_eRelative )
		{
			case r_margin: sResult += _T(" w:relativeTo=\"margin\"");	break;
			case r_indent: sResult += _T(" w:relativeTo=\"indent\"");	break;
		}
		switch( m_eAlignment )
		{
			case a_left:	sResult += _T(" w:alignment=\"left\"");		break;
			case a_center:	sResult += _T(" w:alignment=\"center\"");	break;
			case a_right:	sResult += _T(" w:alignment=\"right\"");	break;
		}
		if( !sResult.IsEmpty() )
			sResult = _T("<w:ptab") + sResult + _T("/>");
		return sResult;
	}
};
class RtfCharSpecial : public IDocumentElement
{
public: 
	typedef enum {
			rsc_none,
			rsc_chdate,//\chdate	Current date (as in headers).
			rsc_chdpl,//\chdpl	Current date in long format (for example, Wednesday, February 20, 2008).
			rsc_chdpa,//\chdpa	Current date in abbreviated format (for example, Wed, Feb 20, 2008).
			rsc_chtime,//\chtime	Current time (as in headers).
			rsc_chpgn,//\chpgn	Current page number (as in headers).
			rsc_sectnum,//\sectnum	Current section number (as in headers).
			rsc_chftn,//\chftn	Automatic footnote reference (footnotes follow in a group).
			rsc_chftnEnd,//Endnote
			rsc_chatn,//\chatn	Annotation reference (annotation text follows in a group).
			rsc_chftnsep,//\chftnsep	Anchoring character for footnote separator.
			rsc_chftnsepc,//\chftnsepc	Anchoring character for footnote continuation.
			rsc_page,//\page	Required page break.
			rsc_column,//\column	Required column break.
			rsc_line,//\line	Required line break (no paragraph break).
			rsc_softpage,//\softpage	Nonrequired page break. Emitted as it appears in galley view.
			rsc_softcol,//\softcol	Nonrequired column break. Emitted as it appears in galley view.
			rsc_softline,//\softline	Nonrequired line break. Emitted as it appears in galley view.
			rsc_tab,//\tab	Tab character. 
			rsc_emspace,//\emspace	Non-breaking space equal to width of character “m” in current font. Some old RTF writers use the construct '{' \emspace '  }' (with two spaces before the closing brace) to trick readers unaware of \emspace into parsing a regular space. A reader should interpret this as an \emspace and a regular space.
			rsc_enspace,//\enspace	Nonbreaking space equal to width of character “n” in current font. Some old RTF writers use the construct '{' \enspace '  }' (with two spaces before the closing brace) to trick readers unaware of \enspace into parsing a regular space. A reader should interpret this as an \enspace and a regular space.
			rsc_qmspace,//\qmspace	One-quarter em space.
			rsc_Formula,//\|	Formula character. (Used by Word 5.1 for the Macintosh as the beginning delimiter for a string of formula typesetting commands.)
			rsc_OptHyphen,//\-	Optional hyphen.
			rsc_NonBrHyphen,//\_	Non-breaking hyphen.
			rsc_NonBrSpace,//\~	Non-breaking space.
			rsc_SubEntry,//\:	Specifies a subentry in an index entry.
			rsc_zwbo,//\zwbo	Zero-width break opportunity. Used to insert break opportunity between two characters.
			rsc_zwnbo,//\zwnbo	Zero-width non-break opportunity. Used to remove break opportunity between two characters.
			rsc_zwj,//\zwj	Zero-width joiner. This is used for ligating (joining) characters.
			rsc_zwnj,//\zwnj	Zero-width nonjoiner. This is used for unligating a character. 
	} RtfSpecChar;   

	int					m_nTextWrapBreak;//\lbrN Text wrapping break of type
	int					m_nSoftHeight;//\softlheightN	Nonrequired line height. This is emitted as a prefix to each line.
	RtfSpecChar			m_eType;
	RtfCharProperty		m_oProperty;
	
	RtfCharSpecial()
	{
		m_eType				= rsc_none;
		m_nTextWrapBreak	= PROP_DEF;
		m_nSoftHeight		= PROP_DEF;
	}
	CString RenderToRtf(RenderParameter oRenderParameter)
	{
		CString sResult;
		sResult += _T("{");
		sResult += m_oProperty.RenderToRtf( oRenderParameter );
		switch( m_eType )
		{
			case rsc_chdate:		sResult += _T("\\chdate");		break;
			case rsc_chdpl:			sResult += _T("\\chdpl");		break;
			case rsc_chdpa:			sResult += _T("\\chdpa");		break;
			case rsc_chtime:		sResult += _T("\\chtime");		break;
			case rsc_chpgn:			sResult += _T("\\chpgn");		break;
			case rsc_sectnum:		sResult += _T("\\sectnum");		break;
			case rsc_chftn:			sResult += _T("\\chftn");		break;
			case rsc_chftnEnd:		sResult += _T("\\chftn");		break;
			case rsc_chatn:			sResult += _T("\\chatn");		break;
			case rsc_chftnsep:		sResult += _T("\\chftnsep");	break;
			case rsc_chftnsepc:		sResult += _T("\\chftnsepc");	break;
			case rsc_page:			sResult += _T("\\page");		break;
			case rsc_column:		sResult += _T("\\column");		break;
			case rsc_line:			sResult += _T("\\line");		break;
			case rsc_softpage:		sResult += _T("\\softpage");	break;
			case rsc_softcol:		sResult += _T("\\softcol");		break;
			case rsc_softline:		sResult += _T("\\softline");	break;
			case rsc_tab:			sResult += _T("\\tab");			break;
			case rsc_Formula:		sResult += _T("\\|");			break;
			case rsc_OptHyphen:		sResult += _T("\\-");			break;
			case rsc_NonBrHyphen:	sResult += _T("\\_");			break;
			case rsc_NonBrSpace:	sResult += _T("\\~");			break;
			case rsc_zwbo:			sResult += _T("\\zwbo");		break;
			case rsc_zwnbo:			sResult += _T("\\zwnbo");		break;
			case rsc_zwj:			sResult += _T("\\zwj");			break;
			case rsc_zwnj:			sResult += _T("\\zwnj");		break;
		}
		if( PROP_DEF != m_nTextWrapBreak )
			sResult += _T("\\par");
		//switch ( m_nTextWrapBreak ) //не воспринимается word
		//{
		//	case 0: sResult += _T("\\lbr0");break;
		//	case 1: sResult += _T("\\lbr1");break;
		//	case 2: sResult += _T("\\lbr2");break;
		//	case 3: sResult += _T("\\lbr3");break;
		//}
		if( PROP_DEF != m_nSoftHeight )
		{
			sResult.AppendFormat( _T("\\softlheight%d"), m_nSoftHeight );
		}
		sResult += _T("}");
		return sResult;
	}
	CString _RenderToOOX(RenderParameter oRenderParameter)
	{
		CString sResult;
		switch( m_eType )
		{
		case rsc_chdate:			sResult += _T("");							break;
			case rsc_chdpl:			sResult += _T("");							break;
			case rsc_chdpa:			sResult += _T("");							break;
			case rsc_chtime:		sResult += _T("");							break;
			case rsc_chpgn:			sResult += _T("<w:pgNum />");				break;
			case rsc_sectnum:		sResult += _T("");							break;
			case rsc_chftn:			sResult += _T("<w:footnoteRef/>");			break;
			case rsc_chftnEnd:		sResult += _T("<w:endnoteRef/>");			break;
			case rsc_chatn:			sResult += _T("<w:annotationRef />");		break;
			case rsc_chftnsep:		sResult += _T("<w:separator />");			break;
			case rsc_chftnsepc:		sResult += _T("<w:continuationSeparator/>");break;
			case rsc_page:			sResult += _T("<w:br w:type=\"page\"/>");	break;
			case rsc_column:		sResult += _T("<w:br w:type=\"column\"/>");	break;
			case rsc_line:			sResult += _T("<w:br w:type=\"textWrapping\" w:clear=\"none\"/>");break;
			case rsc_softpage:		sResult += _T("");									break;
			case rsc_softcol:		sResult += _T("");									break;
			case rsc_softline:		sResult += _T("");									break;
			case rsc_tab:			sResult += _T("<w:tab/>");							break;
			case rsc_emspace:		sResult += _T("");									break;
			case rsc_qmspace:		sResult += _T("");									break;
			case rsc_Formula:		sResult += _T("");									break;
			case rsc_OptHyphen:		sResult += _T("<w:t xml:space=\"preserve\">-</w:t>");break;//<w:softHyphen/>
			case rsc_NonBrHyphen:	sResult += _T("<w:t xml:space=\"preserve\">-</w:t>");break;//<w:nonBreakHyphen/>
			case rsc_NonBrSpace:	sResult += _T("<w:t xml:space=\"preserve\"> </w:t>");break;
			case rsc_zwbo:			sResult += _T("");									break;
			case rsc_zwnbo:			sResult += _T("");									break;
			case rsc_zwj:			sResult += _T("");									break;
			case rsc_zwnj:			sResult += _T("");									break;
		}
		switch ( m_nTextWrapBreak )
		{
			case 0: sResult += _T("<w:br w:type=\"textWrapping\" w:clear=\"none\"/>");	break;
			case 1: sResult += _T("<w:br w:type=\"textWrapping\" w:clear=\"left\"/>");	break;
			case 2: sResult += _T("<w:br w:type=\"textWrapping\" w:clear=\"right\"/>");	break;
			case 3: sResult += _T("<w:br w:type=\"textWrapping\" w:clear=\"all\"/>");	break;
		}
		return sResult;
	}
	CString RenderToOOX(RenderParameter oRenderParameter)
	{
		CString sResult;
		if(RENDER_TO_OOX_PARAM_RUN == oRenderParameter.nType)
		{
			sResult += _T("<w:r>");
			sResult += _T("<w:rPr>");
			sResult += m_oProperty.RenderToOOX(oRenderParameter);
			sResult += _T("</w:rPr>");
			sResult += _RenderToOOX(oRenderParameter);
			sResult += _T("</w:r>");
		}
		else if(RENDER_TO_OOX_PARAM_TEXT == oRenderParameter.nType || 
				RENDER_TO_OOX_PARAM_MATH == oRenderParameter.nType ||
				RENDER_TO_OOX_PARAM_PLAIN == oRenderParameter.nType)
			sResult += _RenderToOOX(oRenderParameter);
		return sResult;
	}
};
typedef boost::shared_ptr<RtfCharSpecial> RtfCharSpecialPtr;

class RtfChar : public IDocumentElement
{            
protected: CString m_sChars;
public: 
	RtfChar()
	{
		m_bRtfEncode = true;
	}
	RtfCharProperty m_oProperty;
	bool m_bRtfEncode;

	int GetType()
	{
		return TYPE_RTF_CHAR;
	}
	void AddText(CString text)
	{
		m_sChars += text;
	}
	void setText(CString text)
	{
		m_sChars = text;
	}

	CString GetText()
	{
		return m_sChars;
	}
    CString RenderToOOX(RenderParameter oRenderParameter)
    {
        CString sResult;
        if(RENDER_TO_OOX_PARAM_RUN == oRenderParameter.nType)
        {
            sResult += _T("<w:r>");
				sResult += _T("<w:rPr>");
					sResult += m_oProperty.RenderToOOX(oRenderParameter);
				sResult += _T("</w:rPr>");
				sResult += renderTextToXML(_T("Text") );
            sResult += _T("</w:r>");
        }
        else if(RENDER_TO_OOX_PARAM_TEXT == oRenderParameter.nType)
            sResult = renderTextToXML( _T("Text") );
        else if( RENDER_TO_OOX_PARAM_MATH == oRenderParameter.nType)
		{
			sResult += _T("<m:r>");
				sResult += m_oProperty.RenderToOOX(oRenderParameter);//w:rPr внутри
				sResult += renderTextToXML( _T("Math") );
			sResult += _T("</m:r>");	
		}
        else if( RENDER_TO_OOX_PARAM_PLAIN == oRenderParameter.nType)
            sResult = m_sChars;
        return sResult;
    }

    static CString renderRtfText( CString& sText, void* poDocument, RtfCharProperty* oCharProperty = NULL );

    CString RenderToRtf(RenderParameter oRenderParameter)
    {
        CString result;
        if( RENDER_TO_RTF_PARAM_CHAR ==  oRenderParameter.nType )
        {
            if( true == m_bRtfEncode )
                result += renderRtfText( m_sChars, oRenderParameter.poDocument, &m_oProperty );
            else
                result += m_sChars;
        }
        else
        {
            CString sText;
            if( true == m_bRtfEncode )
                sText = renderRtfText( m_sChars, oRenderParameter.poDocument, &m_oProperty );
            else
                sText = m_sChars;

			CString sTextProp =  m_oProperty.RenderToRtf( oRenderParameter ) ;
			
			if( !sText.IsEmpty() || !sTextProp.IsEmpty())
            {
                if (oRenderParameter.nType != RENDER_TO_RTF_PARAM_NESTED)
					result += _T("{");
					
					result += sTextProp;
					result += _T(" ");
					result += sText;

				if (oRenderParameter.nType != RENDER_TO_RTF_PARAM_NESTED)
					result += _T("}");
            }
        }
        return result;
    }
private: 
	CString renderTextToXML( CString sParam )
	{
		CString sResult;
		if( _T("Text") == sParam )
        {
            sResult += _T("<w:t xml:space= \"preserve\">");
				sResult += Utils::PrepareToXML( m_sChars );
			sResult += _T("</w:t>");
        }
		else if( _T("Math") == sParam && !m_sChars.IsEmpty())
        {
			sResult += _T("<m:t>");
				sResult += Utils::PrepareToXML( m_sChars );
			sResult += _T("</m:t>");
        }
		return sResult;
	}
};
class RtfCharNative : public RtfChar
{            
public: 
	CString RenderToRtf(RenderParameter oRenderParameter)
	{
		CString result;
		if( RENDER_TO_RTF_PARAM_CHAR ==  oRenderParameter.nType )
		{
			result = m_sChars;
		}
		else
		{
			CString sText = m_sChars;
			if( _T("") != sText )
			{
				result += _T("{");
				result += m_oProperty.RenderToRtf( oRenderParameter );
				result += _T(" ") + sText;
				result += _T("}");
			}
		}
		return result;
	}
};
typedef boost::shared_ptr<RtfCharNative> RtfCharNativePtr;
typedef boost::shared_ptr<RtfChar> RtfCharPtr;
