//
//  ListScene.cpp
//  TangTouGe
//
//  Created by junqingzhu on 15/5/6.
//
//

#include "ListScene.h"
#include "DBService.h"
#include "PlayScene.h"
#include "ContentList.h"

Scene *ListScene::createScene(){
    Scene *scene = Scene::create();
    ListScene *layer = ListScene::create();
    scene->addChild(layer);
    return scene;
}

bool ListScene::init(){
    if (!Layer::init()) {
        return false;
    }
    
    CATEGORYS = DBService::getCategory();
    
    auto dispatcher = CCDirector::getInstance()->getEventDispatcher();
    auto listenerkeyPad = EventListenerKeyboard::create();
    listenerkeyPad->onKeyReleased = CC_CALLBACK_2(ListScene::onKeyReleased, this);
    dispatcher->addEventListenerWithSceneGraphPriority(listenerkeyPad, this);
    
    auto bg = LayerColor::create(Color4B(0xff, 0xff, 0xff, 0xff));
    addChild(bg);
    
    auto topBar = Sprite::create("topBar.png");
    topBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    addChild(topBar);
    topBar->setPosition(Vec2(WIDTH/2, HEIGHT));
    
    auto title = Label::createWithSystemFont("被动收入金钥匙", FONT_NORMAL, FONT_SIZE_BIGGLE);
    title->setPosition(Vec2(WIDTH/2, HEIGHT - 55));
    
    title->setColor(Color3B::YELLOW);
    addChild(title);
    
    addList();
    return true;
}

void ListScene::addList(){
    auto listView = ListView::create();
    listView->setDirection(ui::ScrollView::Direction::VERTICAL);
    listView->setBounceEnabled(true);
    listView->setBackGroundImageScale9Enabled(true);
    listView->setContentSize(Size(WIDTH, HEIGHT-110));
    listView->setPosition(Vec2(0, 0));
    listView->addEventListener((ui::ListView::ccListViewCallback)CC_CALLBACK_2(ListScene::selectedItemEvent, this));
    this->addChild(listView);
    
        Size cellSize = Size(listView->getContentSize().width, 130);
        for (int i = 0; i < CATEGORYS.size(); i++)
        {
            Layout *custom_item = Layout::create();
            custom_item->setContentSize(cellSize);
            listView->addChild(custom_item);
            
            Button* custom_button = Button::create("list_item_bg.png", "list_item_bg_s.png");
            custom_button->setPosition(Vec2(cellSize.width/2, cellSize.height/2));
            custom_item->addChild(custom_button);
            
            Label* labelDetail = Label::createWithSystemFont(CATEGORYS[i]["category"], FONT_NORMAL, FONT_SIZE_NORMAL);
//            labelDetail->setColor(Color3B::BLACK);
            labelDetail->setPosition(Vec2(cellSize.width*0.58, cellSize.height/2));
            custom_item->addChild(labelDetail);
        }
        listView->refreshView();
    }


void ListScene::selectedItemEvent(Ref *pSender, ListView::EventType type)
{
    switch (type)
    {
        case cocos2d::ui::ListView::EventType::ON_SELECTED_ITEM_END:
        {
            ListView* listView = static_cast<ListView*>(pSender);
            CC_UNUSED_PARAM(listView);
            CONTENTS.clear();
            CONTENTS = DBService::getContent(CATEGORYS[listView->getCurSelectedIndex()]["_id"]);
            CATEGORYINDEX = (int)listView->getCurSelectedIndex();
            
            Director::getInstance()->replaceScene(TransitionSlideInR::create(TRANSITIONDELAY, ContentList::createScene()));
            CCLOG("select child end index = %ld", listView->getCurSelectedIndex());
            break;
        }
        default:
            break;
    }
}

void ListScene::onKeyReleased(EventKeyboard::KeyCode keycode, cocos2d::Event *event)
{
    if (keycode == EventKeyboard::KeyCode::KEY_BACK)
    {
        if (getChildByTag(101)) {
            Director::getInstance()->end();
        }
        else{
            auto boardBg = Sprite::create("exit_alert.png");
            boardBg->setPosition(Point(WIDTH*0.5, HEIGHT*0.05));
            boardBg->setOpacity(0);
            addChild(boardBg,20,101);
            boardBg->runAction(Sequence::create(Spawn::create(MoveTo::create(0.15, Point(WIDTH*0.5, HEIGHT*0.15)), FadeIn::create(0.15), NULL), MoveTo::create(0.15, Point(WIDTH*0.5, HEIGHT*0.13)),DelayTime::create(1.2f), FadeOut::create(0.3f),CallFuncN::create(CC_CALLBACK_1(ListScene::removeNode, this)), NULL));
        }
    }
    else if (keycode == EventKeyboard::KeyCode::KEY_MENU)
    {
        
    }
}

void ListScene::removeNode(cocos2d::Node *sender){
    sender->removeFromParent();
}

