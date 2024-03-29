/* =============================================================================	 Trisoft CMS Web Help Script v1.0
		 Copyright (c) 2008-2009 SDL Trisoft (http://www.trisoftcms.com)
		 Tested on windows with        IE6, IE7, FF2, FF3, Opera 9.62
	 Tested on Linux (ubuntu) with FF3	 
	 You may only use this script library on web help content 	 generated using Trisoft CMS
   ========================================================================== */
function Search(s){
	var resultsFound = false;  try
  {		this.status = searchinglabel;
//		alert("s = |" + s + "|");	}
	catch(err)  {
	  var txt;	  txt="There was an error on this page.\n\n";
	  txt+="Error description: " + err.description + "\n\n";	  txt+="Click OK to continue.\n\n";
	  alert(txt);  }
	if (!s)
  	 return false;  	 
	searchCriteria = distectSearchCriteria(s);	var resultArrIndexPos = new Array();
	var ORoperator = false; // by default all criteria have AND's inbetween. OR operator (,) must be entered by user.	
	for (var criteriaCounter = 0; criteriaCounter < searchCriteria.length; criteriaCounter++) {//		alert("Search for disected criteria: " + searchCriteria[criteriaCounter]);
		var foundDocumentIndexPos = new Array();				if (searchCriteria[criteriaCounter] == "|") 
		{	ORoperator = true; }		else
		{//			ORoperator = false;
			for (var i = 0; i < SearchInfo.length; i++) {				if (SearchInfo[i].toLowerCase().indexOf(searchCriteria[criteriaCounter].toLowerCase(),0)>-1)
	      {					foundDocumentIndexPos.push(i);	      	
	      }      			}
		}		if (ORoperator)
		{			// combine (skip already available references) both (fondDocumentIndexPos / resultArrIndexPos) arrays
					}
		else		{
			// build new union array containing elements existing in both (fondDocumentIndexPos / resultArrIndexPos) arrays			resultArrIndexPos = combineArrays(foundDocumentIndexPos, resultArrIndexPos, ORoperator, criteriaCounter)
		}			
	}	
	//Build result list in browser screen.	showSearchResults(s, resultArrIndexPos, searchCriteria);
	return true;
}
function showSearchResults(searchString, resultArr, searchCriteria){
	var sSearchedText = '';	var pageString='<!DOCTYPE html PUBLIC "-//W3C//DTD XHTML 1.0 Transitional//EN" "http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd">\n';
	pageString+='<html>\n';	pageString+='<head>\n';
	pageString+='	<title>' + searchtitlelabel + '</title>\n';	pageString+='	<base target="_self">\n';
	pageString+='	<meta name="Generator" content="Trisoft CMS 2009" />\n';	pageString+='	<meta http-equiv="Content-Type" content="text/html; charset=ISO-8859-1" />\n';
	pageString+='	<link rel="stylesheet" type="text/css" href="webhelplayout.css" />\n';	pageString+='	<link rel="stylesheet" type="text/css" href="stylesheet.css" />\n';
	pageString+='	<script type="text/javascript" src="searchlabels.js" charset="UTF-8"></script>\n';	pageString+='	<script type="text/javascript" src="search.js" charset="UTF-16"></script>\n';
	pageString+='	<script type="text/javascript" src="searchdata.js" charset="UTF-8"></script>\n';	pageString+='</head>\n';
	pageString+='<body class="framelayout">\n';	pageString+='	<h1 class="heading1">' + searchtitlelabel + '</h1>\n';
	pageString+='	<form action="#" onsubmit="Search(document.forms[\'SearchFrm\'].searchcriteria.value); return false;" name="SearchFrm" id="SearchFrm">\n';	pageString+='		<span>' + entersearchcriterialabel + '</span><br />\n';
	pageString+='		<input type="text" width="145" name="searchcriteria" value=\'' + searchString.replace(/\'/g, "&#39;") + '\' />\n';	pageString+='		<input type="submit" name="searchbutton" value="' + searchbuttonlabel + '" width="50">\n';
	pageString+='	</form>\n';	pageString+='<div id="resultlist">\n';
		if (resultArr.length == 0) 
	{		pageString+='<p>' + nodocumentsfoundlabel + '</p>\n';
	}	else
	{		pageString += '<p>' + followingdocumentsfoundlabel + '</p>\n';
		for (var resultCounter=0; resultCounter<resultArr.length;resultCounter++)		{
			sSearchedText = SearchInfo[resultArr[resultCounter]];			var firstmatchingpos = sSearchedText.length;
			pageString += '<p class="resultitem"><a href="' + SearchFiles[resultArr[resultCounter]] + '" target="contentwin">' + SearchTitles[resultArr[resultCounter]] + '</a><br/>\n';			pageString += '<span>';
			for (var criteriaCounter = 0; criteriaCounter < searchCriteria.length; criteriaCounter++)			{
				var indexpos = sSearchedText.toLowerCase().indexOf(searchCriteria[criteriaCounter].toLowerCase(),0);				if (indexpos >-1)
				{					if (indexpos < firstmatchingpos) {firstmatchingpos = indexpos};
					sSearchedText = highlightText(sSearchedText, searchCriteria[criteriaCounter], indexpos);				}
			}						var sEndString = '...';					
			if (firstmatchingpos > 50)			{
				if(sSearchedText.substr(firstmatchingpos-50,125).toLowerCase().lastIndexOf("<b>") > sSearchedText.substr(firstmatchingpos-50,125).toLowerCase().lastIndexOf("</b>")) {sEndString='</b>...';} //				alert('b pos: ' + sSearchedText.substr(firstmatchingpos-50,125).toLowerCase().lastIndexOf("<b>") + ' | /b pos ' + sSearchedText.substr(firstmatchingpos-50,125).toLowerCase().lastIndexOf("</b>") + ' | Endstring: ' + sEndString); 
			pageString +="..."+ sSearchedText.substr(firstmatchingpos-50,125)+sEndString+"\n";			}
			else			{
				if(sSearchedText.substr(0,125).toLowerCase().lastIndexOf("<b>") > sSearchedText.substr(0,125).toLowerCase().lastIndexOf("</b>")) {sEndString='</b>...';}//				alert('b pos: ' + sSearchedText.substr(0,125).toLowerCase().lastIndexOf("<b>") + ' | /b pos ' + sSearchedText.substr(0,125).toLowerCase().lastIndexOf("</b>") + ' | Endstring: ' + sEndString); 				
				pageString += sSearchedText.substr(0,125)+sEndString+"\n";			}
						pageString += '</span></p>\n';	
		}		
			} /* else */
	pageString+='</div>\n';	
	pageString+="</body></html>";	
	this.status="";	this.document.open();
	this.document.write(pageString);	this.document.close();
}
function highlightText(text, textToHighlight, pos){
	var hiText = text.substr(0,pos);	hiText += text.substr(pos,textToHighlight.length).bold();
		var ipos = text.substr(pos + textToHighlight.length).toLowerCase().indexOf(textToHighlight.toLowerCase(),0);
		if (ipos >- 1)
	{		hiText += highlightText(text.substr(pos + textToHighlight.length), textToHighlight, ipos);
	}	else
	{		hiText += text.substr(pos + textToHighlight.length);
	}	
	return hiText;}
function distectSearchCriteria(s)
{	var SearchItems = new Array();
	var SpacePos = -1;
	var prevSpacePos = 0;	var QuoteEndPos = -1;
	var criteria = "";	var quotedstring = false;
	for (charpos = 0; charpos < s.length; charpos++)
	{		var letter = s[charpos];
		if (letter == undefined) {letter = s.charAt(charpos);}		
		if (quotedstring) {			switch (letter) {
				case "\"":					QuoteEndPos = charpos;
					if (QuoteEndPos>-1) 					{
							criteria = " " + s.substring(QuoteStartPos,QuoteEndPos) + " ";					}
					SearchItems.push(criteria);					quotedstring = false;
					QuoteStartPos = 0;					prevSpacePos = QuoteEndPos+2;
					break;							default:
					break;			}
		}		else {
			switch (letter) {				case " ":
					SpacePos = charpos;					if (SpacePos > prevSpacePos) {
						criteria = s.substring(prevSpacePos,SpacePos);						SearchItems.push(criteria); //SearchItems.push(" " + criteria); in case words have to start with criteria
						prevSpacePos = SpacePos+1;					}
					break;								case "\"":
					QuoteStartPos = charpos+1; 					QuoteEndPos = -1; 
					quotedstring = true;					break;			
				default:					break;
			}		}
	}	if (quotedstring) {alert("When searching for exact matches, you need to supply an equal amount of start and end quotes"); return [];}
	if (prevSpacePos > -1 && prevSpacePos < charpos) {		criteria = s.substring(prevSpacePos,charpos);
		SearchItems.push(criteria); //SearchItems.push(" " + criteria); in case words have to start with criteria	}
//	alert("number of criteria: " + SearchItems.length);
			// TODO: Replace/Escape < > & by entity values.
//	for (var i = 0; i < SearchItems.length; i++) {//		SearchItems[i].replace("<","&lt;");
//		SearchItems[i].replace(">","&gt;");//		SearchItems[i].replace("&","&amp;");
//	}	
	return SearchItems;}
function combineArrays(newArray, existingArray, combinelists, requestNumber)
{	var combinedArray = new Array();
	// First request. So return newArray because this is always correct.
	if (requestNumber == 0)	{
		return newArray;	}
		// Not first array. Check if found document was also found with previous searchCriteria.
	if (requestNumber>0)	{
		for (i=0; i<newArray.length; i++)		{
			var exists = false			for (j=0; j<existingArray.length; j++)
			{				if (newArray[i] == existingArray[j])
				{					exists = true;
					break;				}
			}			
				// AND operator between searchCriteria				// if document already exists in existingArray, copy reference to new item.
				if (exists) {combinedArray.push(newArray[i]);}		}
	}	return combinedArray;
}
/* =============================== End Of File =============================== */   