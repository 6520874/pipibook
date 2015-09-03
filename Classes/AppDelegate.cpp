#include "AppDelegate.h"
#include "Global.h"
#include "DBService.h"
#include "Utils.h"
#include "ListScene.h"

USING_NS_CC;

AppDelegate::AppDelegate() {

}

AppDelegate::~AppDelegate() 
{
}

//if you want a different context,just modify the value of glContextAttrs
//it will takes effect on all platforms
void AppDelegate::initGLContextAttrs()
{
    //set OpenGL context attributions,now can only set six attributions:
    //red,green,blue,alpha,depth,stencil
    GLContextAttrs glContextAttrs = {8, 8, 8, 8, 24, 8};

    GLView::setGLContextAttrs(glContextAttrs);
}

bool AppDelegate::applicationDidFinishLaunching() {
    // initialize director
    auto director = Director::getInstance();
    auto glview = director->getOpenGLView();
    if(!glview) {
        glview = GLViewImpl::create("My Game");
        director->setOpenGLView(glview);
    }
    Size PRESIZE = CCDirector::getInstance()->getWinSize();
    float currentHeight = 640.f/PRESIZE.width*PRESIZE.height;
    //设置屏幕大小
    glview-> setDesignResolutionSize(640.f, currentHeight, ResolutionPolicy::EXACT_FIT);
    WINSIZE = Director::getInstance()->getWinSize();
    WIDTH = WINSIZE.width;
    HEIGHT = WINSIZE.height;
    // turn on display FPS
    director->setDisplayStats(false);

    // set FPS. the default value is 1.0/60 if you don't call this
    director->setAnimationInterval(1.0 / 60);
    
    if (!UserDefault::getInstance()->getBoolForKey("init_db", false)) {
        Data d = FileUtils::getInstance()->getDataFromFile("tangtouge.db");
        FILE *fp;
        if ((fp = fopen((FileUtils::getInstance()->getWritablePath() + "tangtouge.db").c_str(), "wb"))==0) {
            log("cann't open writablepath");
            fclose(fp);
            return true;
        }
        
        fwrite(d.getBytes(), d.getSize(), 1, fp);
        fclose(fp);
        UserDefault::getInstance()->setBoolForKey("init_db", true);
        UserDefault::getInstance()->flush();
    }
    
    auto scene = ListScene::createScene();
//
//    // run
    director->runWithScene(scene);

    return true;
}

// This function will be called when the app is inactive. When comes a phone call,it's be invoked too
void AppDelegate::applicationDidEnterBackground() {
    Director::getInstance()->stopAnimation();

    // if you use SimpleAudioEngine, it must be pause
     SimpleAudioEngine::getInstance()->pauseBackgroundMusic();
}

// this function will be called when the app is active again
void AppDelegate::applicationWillEnterForeground() {
    Director::getInstance()->startAnimation();

    // if you use SimpleAudioEngine, it must resume here
     SimpleAudioEngine::getInstance()->resumeBackgroundMusic();
}
