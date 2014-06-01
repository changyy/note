function FindProxyForURL(url, host) {
	if (
		shExpMatch(url, "http://v.youku.com/player/*") ||
		shExpMatch(url, "http://api.3g.youku.com/layout*") ||
		shExpMatch(url, "http://api.youku.com/player/*") ||
		shExpMatch(url, "http://v2.tudou.com/*") ||
		shExpMatch(url, "http://www.tudou.com/a/*") ||
		shExpMatch(url, "http://www.tudou.com/v/*") ||
		shExpMatch(url, "http://api.3g.tudou.com/*") ||
		shExpMatch(url, "http://s.plcloud.music.qq.com/*") ||
		shExpMatch(url, "http://hot.vrs.sohu.com/*") ||
		shExpMatch(url, "http://live.tv.sohu.com/live/player*") ||
		shExpMatch(url, "http://hot.vrs.letv.com/*") ||
		shExpMatch(url, "http://data.video.qiyi.com/*") ||
		shExpMatch(url, "http://interface.bilibili.tv/player*") ||
		shExpMatch(url, "http://vv.video.qq.com/*") ||
		shExpMatch(url, "http://geo.js.kankan.xunlei.com/*") ||
		shExpMatch(url, "http://web-play.pptv.com/*") ||
		shExpMatch(url, "http://web-play.pplive.cn/*") ||
		shExpMatch(url, "http://dyn.ugc.pps.tv/*") ||
		shExpMatch(url, "http://inner.kandian.com/*") ||
		shExpMatch(url, "http://ipservice.163.com/*") ||
		shExpMatch(url, "http://zb.s.qq.com/*") ||
		shExpMatch(url, "http://ip.kankan.xunlei.com/*") ||
		shExpMatch(url, "http://proxy.music.qq.com/*") ||
		shExpMatch(url, "http://3g.music.qq.com/*") ||
		shExpMatch(url, "http://mqqplayer.3g.qq.com/*") ||
		shExpMatch(url, "http://music.sina.com.cn/yueku/intro/*") ||
		shExpMatch(url, "http://v.iask.com/v_play.php*") ||
		shExpMatch(url, "http://v.iask.com/v_play_ipad.cx.php*") ||
		shExpMatch(url, "http://tv.weibo.com/player/*") ||
		shExpMatch(url, "http://www.yinyuetai.com/insite/*") ||
		shExpMatch(url, "http://www.yinyuetai.com/main/get-video-info*") ||
		shExpMatch(url, "http://*.dpool.sina.com.cn/iplookup*") ||
		shExpMatch(url, "http://*/vrs_flash.action*") ||
		shExpMatch(url, "http://vdn.apps.cntv.cn/api/getHttpVideoInfo.do*")
	) {
		return "PROXY proxy.uku.im:80";
	}
	return "DIRECT";
}
