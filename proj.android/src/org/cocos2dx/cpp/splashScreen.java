package org.cocos2dx.cpp;
import com.wuchen.tangtouge.R;

import android.app.Activity;  
import android.content.Intent;  
import android.os.Bundle;  
import android.os.Handler;  
import net.youmi.android.AdManager;
import net.youmi.android.spot.SplashView;
import net.youmi.android.spot.SpotDialogListener;
import net.youmi.android.spot.SpotManager;
import android.content.pm.ActivityInfo;
import android.content.res.Configuration;
import android.util.Log;
import android.view.Window;
import android.view.WindowManager;

public class splashScreen extends Activity {  
  
    private final int SPLASH_DISPLAY_LENGHT = 2000; 
//  
//    @Override  
//    protected void onCreate(Bundle savedInstanceState) {  
//        super.onCreate(savedInstanceState);  
//        setContentView(R.layout.splashscreen);  
//  
//        new Handler().postDelayed(new Runnable() {  
//            public void run() {  
//                Intent mainIntent = new Intent(splashScreen.this,  
//                        org.cocos2dx.cpp.AppActivity.class);  
//                splashScreen.this.startActivity(mainIntent);  
//                overridePendingTransition(android.R.anim.fade_in,android.R.anim.fade_out); 
//                splashScreen.this.finish();  
//            }  
//  
//        }, SPLASH_DISPLAY_LENGHT);  
//    }  
	
	@Override
	protected void onCreate(Bundle savedInstanceState) {
		super.onCreate(savedInstanceState);
		this.getWindow().setFlags(WindowManager.LayoutParams.FLAG_FULLSCREEN,
				WindowManager.LayoutParams.FLAG_FULLSCREEN);
		this.requestWindowFeature(Window.FEATURE_NO_TITLE);

		// 初始化接口，应用启动的时候调用
		// 参数：appId, appSecret, 调试模式
		AdManager.getInstance(this).init("7b58f3941a6975ce", "2d9a05a943b192fb", false);

		// 如果仅仅使用开屏，需要取消注释以下注释，如果使用了开屏和插屏，则不需要。
		SpotManager.getInstance(this).loadSplashSpotAds();
		String AdsValue = AdManager.getInstance(this).syncGetOnlineConfig(
				"showads", "0");
		if (AdsValue.equals("0")) {
			setContentView(R.layout.splashscreen);

			new Handler().postDelayed(new Runnable() {
				public void run() {
					Intent mainIntent = new Intent(splashScreen.this,
							org.cocos2dx.cpp.AppActivity.class);
					splashScreen.this.startActivity(mainIntent);
					overridePendingTransition(android.R.anim.fade_in,
							android.R.anim.fade_out);
					splashScreen.this.finish();
				}

			}, SPLASH_DISPLAY_LENGHT);
			return;
		}
		// 开屏的两种调用方式：请根据使用情况选择其中一种调用方式。
		// 1.可自定义化调用：
		// 此方式能够将开屏适应一些应用的特殊场景进行使用。
		// 传入需要跳转的activity
		SplashView splashView = new SplashView(this, org.cocos2dx.cpp.AppActivity.class);

		// 开屏也可以作为控件加入到界面中。
		setContentView(splashView.getSplashView());

		SpotManager.getInstance(this).showSplashSpotAds(this, splashView,
				new SpotDialogListener() {

					@Override
					public void onShowSuccess() {
						Log.i("YoumiAdDemo", "开屏展示成功");
					}

					@Override
					public void onShowFailed() {
						Log.i("YoumiAdDemo", "开屏展示失败。");
					}

					@Override
					public void onSpotClosed() {
						Log.i("YoumiAdDemo", "开屏关闭。");
					}
				});

		// 2.简单调用方式
		// 如果没有特殊要求，简单使用此句即可实现插屏的展示
//		 SpotManager.getInstance(this).showSplashSpotAds(this,
//				 org.cocos2dx.cpp.AppActivity.class);

	}

	// 请务必加上词句，否则进入网页广告后无法进去原sdk
	@Override
	protected void onActivityResult(int requestCode, int resultCode, Intent data) {
		super.onActivityResult(requestCode, resultCode, data);

		if (resultCode == 10045) {
			Intent intent = new Intent(splashScreen.this, org.cocos2dx.cpp.AppActivity.class);
			startActivity(intent);
			finish();
		}
	}

	@Override
	public void onBackPressed() {
		// 取消后退键
	}

	@Override
	protected void onResume() {

		/**
		 * 设置为竖屏
		 */
		if (getRequestedOrientation() != ActivityInfo.SCREEN_ORIENTATION_PORTRAIT) {
			setRequestedOrientation(ActivityInfo.SCREEN_ORIENTATION_PORTRAIT);
		}
		super.onResume();
	}

	@Override
	public void onConfigurationChanged(Configuration newConfig) {
		super.onConfigurationChanged(newConfig);
		if (this.getResources().getConfiguration().orientation == Configuration.ORIENTATION_LANDSCAPE) {
			// land
		} else if (this.getResources().getConfiguration().orientation == Configuration.ORIENTATION_PORTRAIT) {
			// port
		}
	}

}  

