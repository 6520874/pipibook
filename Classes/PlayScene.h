//
//  PlayScene.h
//  TangTouGe
//
//  Created by junqingzhu on 15/5/6.
//
//

#ifndef __TangTouGe__PlayScene__
#define __TangTouGe__PlayScene__

#include "Global.h"

class PlayScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene(int index);
    virtual bool init();
    CREATE_FUNC(PlayScene);

    void addRightScreen();//加载正确界面
    void buttonCallback(Ref *sender);//按钮回调
    void btnCallback(Ref *pSender, Widget::TouchEventType type);//按钮回调方法
    
    int contentIndex;//汤剂索引
};


#endif /* defined(__TangTouGe__PlayScene__) */
