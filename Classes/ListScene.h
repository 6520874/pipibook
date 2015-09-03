//
//  ListScene.h
//  TangTouGe
//
//  Created by junqingzhu on 15/5/6.
//
//

#ifndef __TangTouGe__ListScene__
#define __TangTouGe__ListScene__

#include "Global.h"

class ListScene : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();
    virtual bool init();
    CREATE_FUNC(ListScene);
    
    void removeNode(Node *sender);
    
    void selectedItemEvent(Ref* pSender, cocos2d::ui::ListView::EventType type);//选中某一行回调
    void addList();//添加列表
    
    virtual void onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event);
};


#endif /* defined(__TangTouGe__ListScene__) */
