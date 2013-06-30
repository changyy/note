# -*- coding: UTF-8 -*-
import json
import md5
import sys

reload(sys)
sys.setdefaultencoding('utf-8')
raw = json.loads( open('blogger.log','r').read() )

print "var newsite_link = {};"

for key in raw:
	#print key
	#print raw[key]
	newkey = key.replace("'", "\\'")
	print "newsite_link['"+newkey+"'] = '"+raw[key]+"';"

print """
function newSiteURL(title) {
	if( newsite_link[title] != undefined )
		return newsite_link[title];
	return '';
}

if( document.title != "第二十四個夏天後 :: 痞客邦 PIXNET ::" ) {

	article_title = document.title.replace(" @ 第二十四個夏天後 :: 痞客邦 PIXNET ::", "");

	//console.log("Title:["+article_title+"]");
	//console.log(newSiteURL(article_title));
	newSiteURLLocation = newSiteURL(article_title);
	if( newSiteURLLocation != '' )
        	document.getElementById("new_site_search").innerHTML= '新版網站此篇文章網址：<a href="'+newSiteURLLocation+'">'+article_title+'</a>' ;
}
"""
