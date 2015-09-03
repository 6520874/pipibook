//
//  ContentList.cpp
//  TangTouGe
//
//  Created by junqingzhu on 15/6/15.
//
//

#include "ContentList.h"
#include "ListScene.h"
#include "DBService.h"
#include "PlayScene.h"

Scene *ContentList::createScene(){
    Scene *scene = Scene::create();
    ContentList *layer = ContentList::create();
    scene->addChild(layer);
    return scene;
}

bool ContentList::init(){
    if (!Layer::init()) {
        return false;
    }
    
    CATEGORYS = DBService::getCategory();
    
    auto dispatcher = CCDirector::getInstance()->getEventDispatcher();
    auto listenerkeyPad = EventListenerKeyboard::create();
    listenerkeyPad->onKeyReleased = CC_CALLBACK_2(ContentList::onKeyReleased, this);
    dispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);
    
    auto bg = LayerColor::create(Color4B(0xff, 0xff, 0xff, 0xff));
    addChild(bg);
    
    auto topBar = Sprite::create("topBar.png");
    topBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    addChild(topBar);
    topBar->setPosition(Vec2(WIDTH/2, HEIGHT));
    
    auto title = Label::createWithSystemFont(CATEGORYS[CATEGORYINDEX]["category"], FONT_NORMAL, FONT_SIZE_BIGGLE);
    title->setPosition(Vec2(WIDTH/2, HEIGHT - 55));
    title->setColor(Color3B::BLACK);
    addChild(title);
    //返回按钮
    auto backBtn = MenuItemImage::create("back_n.png", "back_s.png", CC_CALLBACK_1(ContentList::buttonCallback, this));
    backBtn->setPosition(Vec2(10, HEIGHT - 55));
    backBtn->setTag(3);
    backBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    Menu *backMenu = Menu::create(backBtn, NULL);
    backMenu->setPosition(Vec2::ZERO);
    addChild(backMenu);
    
    addList();
    return true;
}

void ContentList::addList(){
    auto listView = ListView::create();
    listView->setDirection(ui::ScrollView::Direction::VERTICAL);
    listView->setBounceEnabled(true);
    listView->setBackGroundImageScale9Enabled(true);
    listView->setContentSize(Size(WIDTH, HEIGHT-110));
    listView->setPosition(Vec2(0, 0));
    listView->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(ContentList::selectedItemEvent, this));
    this->addChild(listView);
    
    Size cellSize = Size(listView->getContentSize().width, 130);
    for (int i = 0; i < CONTENTS.size(); i++)
    {
        Layout *custom_item = Layout::create();
        custom_item->setContentSize(cellSize);
        listView->addChild(custom_item);
        
        Button* custom_button = Button::create("content_item_bg.png", "content_item_bg_s.png");
        custom_button->setPosition(Vec2(cellSize.width/2, cellSize.height/2));
        custom_item->addChild(custom_button);
        
        Label* labelDetail = Label::createWithSystemFont(CONTENTS[i]["title"], FONT_NORMAL, FONT_SIZE_NORMAL);
//        labelDetail->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
//        labelDetail->setColor(Color3B::BLACK);
        labelDetail->setPosition(Vec2(cellSize.width*0.58, cellSize.height/2));
        custom_item->addChild(labelDetail);
    }
    listView->refreshView();
}


void ContentList::selectedItemEvent(Ref *pSender, ListView::EventType type)
{
    switch (type)
    {
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            int contentIndex = (int)listView->getCurSelectedIndex();
            
            Director::getInstance()->replaceScene(TransitionSlideInR::create(TRANSITIONDELAY, PlayScene::createScene(contentIndex)));
            break;
        }
        default:
            break;
    }
}

void ContentList::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
    if (keycode == EventKeyboard::KeyCode::KEY_BACK)
    {
        buttonCallback(NULL);
    }
    else if (keycode == EventKeyboard::KeyCode::KEY_MENU)
    {
        
    }
}

void ContentList::buttonCallback(cocos2d::Ref *sender){
    Director::getInstance()->replaceScene(TransitionSlideInL::create(TRANSITIONDELAY, ListScene::createScene()));
}
