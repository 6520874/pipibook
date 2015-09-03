//
//  ContentList.h
//  TangTouGe
//
//  Created by junqingzhu on 15/6/15.
//
//

#ifndef __TangTouGe__ContentList__
#define __TangTouGe__ContentList__

#include "Global.h"

class ContentList : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(ContentList);
    
    void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);//选中某一行回调
    void addList();//添加列表
    void buttonCallback(Ref *sender);//按钮回调
    
    virtual void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
};

#endif /* defined(__TangTouGe__ContentList__) */
