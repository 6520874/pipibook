/****************************************************************************
Copyright (c) 2008-2010 Ricardo Quesada
Copyright (c) 2010-2012 cocos2d-x.org
Copyright (c) 2011      Zynga Inc.
Copyright (c) 2013-2014 Chukong Technologies Inc.
 
http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
****************************************************************************/
package org.cocos2dx.cpp;

import org.cocos2dx.lib.Cocos2dxActivity;

import android.content.Context;
import android.os.Bundle;
import android.util.Log;
import net.youmi.android.AdManager;
import net.youmi.android.spot.SpotDialogListener;
import net.youmi.android.spot.SpotManager;
public class AppActivity extends Cocos2dxActivity {
	private static Context _appActiviy;	
	private static String AdsValue = "0";
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
	    _appActiviy = this;
//	    AdManager.getInstance(this).init("7b58f3941a6975ce", "2d9a05a943b192fb", false);
//	    SpotManager.getInstance(this).loadSpotAds();
//	    SpotManager.getInstance(this).setSpotOrientation(
//	            SpotManager.ORIENTATION_PORTRAIT);
//	    SpotManager.getInstance(this).setAnimationType(SpotManager.ANIM_ADVANCE);
//	    AdManager.getInstance(this).setUserDataCollect(true);
//	    AdsValue = AdManager.getInstance(this).syncGetOnlineConfig("showads", "0");
	}

	public static void showAds() {
//		if (AdsValue.equals("1")) {
//			SpotManager.getInstance(_appActiviy).showSpotAds(_appActiviy);
//		}
	}
	
//	@Override
//	public void onBackPressed() {
//	    // 如果有需要，可以点击后退关闭插播广告。
//	    if (!SpotManager.getInstance(this).disMiss()) {
//	        // 弹出退出窗口，可以使用自定义退屏弹出和回退动画,参照demo,若不使用动画，传入-1
//	        super.onBackPressed();
//	    }
//	}
//
//	@Override
//	protected void onStop() {
//	    // 如果不调用此方法，则按home键的时候会出现图标无法显示的情况。
//	    SpotManager.getInstance(this).onStop();
//	    super.onStop();
//	}
//
//	@Override
//	protected void onDestroy() {
//	    SpotManager.getInstance(this).onDestroy();
//	    super.onDestroy();
//	}
}
