//
//  PlayScene.cpp
//  TangTouGe
//
//  Created by junqingzhu on 15/5/6.
//
//

#include "PlayScene.h"
#include "DBService.h"
#include "Utils.h"
#include "ContentList.h"
#include "MYUtils.h"

Scene *PlayScene::createScene(int index){
    Scene *scene = Scene::create();
    PlayScene *layer = PlayScene::create();
    scene->addChild(layer);
    layer->contentIndex = index;
    layer->addRightScreen();
    return scene;
}

bool PlayScene::init(){
    if (!Layer::init()) {
        return false;
    }
    return true;
}

void PlayScene::addRightScreen(){
    removeAllChildren();
    //添加背景
    auto bg = LayerColor::create(Color4B(0xff, 0xff, 0xff, 0xff));
    addChild(bg);
    
    auto topBar = Sprite::create("topBar.png");
    topBar->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    addChild(topBar);
    topBar->setPosition(Vec2(WIDTH/2, HEIGHT));
    
    //添加标题
    auto title = Label::createWithSystemFont(CONTENTS[contentIndex]["title"], FONT_NORMAL, FONT_SIZE_BIGGLE);
    title->setPosition(Vec2(WIDTH/2, HEIGHT - 55));
    title->setColor(Color3B::BLACK);
    addChild(title);
    //返回按钮
    auto backBtn = MenuItemImage::create("back_n.png", "back_s.png", CC_CALLBACK_1(PlayScene::buttonCallback, this));
    backBtn->setPosition(Vec2(10, HEIGHT - 55));
    backBtn->setTag(3);
    backBtn->setAnchorPoint(Vec2::ANCHOR_MIDDLE_LEFT);
    Menu *backMenu = Menu::create(backBtn, NULL);
    backMenu->setPosition(Vec2::ZERO);
    addChild(backMenu);
    
    float scrollWidth = WIDTH;
    auto scrollView = ui::ScrollView::create();
    scrollView->setDirection(ui::ScrollView::Direction::VERTICAL);
    scrollView->setBounceEnabled(true);
    scrollView->setBackGroundImageScale9Enabled(true);
    scrollView->setContentSize(Size(scrollWidth, HEIGHT - 110));
    scrollView->setPosition(Vec2(0, 0));
    this->addChild(scrollView);
    
    vector<string> content = Utils::splitContent(CONTENTS[contentIndex]["info"]);
    string detail = CONTENTS[contentIndex]["detail"];
    
    auto detailLab = Label::createWithSystemFont(detail, FONT_NORMAL, FONT_SIZE_38, Size(WIDTH*0.85, 0), TextHAlignment::LEFT, TextVAlignment::TOP);
    detailLab->setColor(Color3B::BLUE);
    
    float innerHeight = content.size()*100 + detailLab->getContentSize().height + 150;
    
    if (innerHeight < HEIGHT - 110) {
        innerHeight = HEIGHT - 110;
    }
    scrollView->setInnerContainerSize(Size(scrollWidth, innerHeight));
   
    for (int i = 0; i < content.size(); i++) {
        auto contentLab = Label::createWithSystemFont(content[i], FONT_NORMAL, FONT_SIZE_NORMAL);
        contentLab->setPosition(Vec2(scrollWidth/2, innerHeight - 50 - i*100));
        contentLab->setColor(Color3B::RED);
        scrollView->addChild(contentLab);
    }
    auto line = Sprite::create("line.png");
    line->setPosition(Vec2(WIDTH/2, innerHeight - content.size()*100));
    scrollView->addChild(line);
    
    //添加方剂解析
    detailLab->setAnchorPoint(Vec2::ANCHOR_MIDDLE_TOP);
    detailLab->setPosition(Vec2(scrollWidth/2, innerHeight - content.size()*100 - 20));
    scrollView->addChild(detailLab);
    
    
    auto line1 = Sprite::create("line.png");
    line1->setPosition(Vec2(WIDTH/2, 120));
    scrollView->addChild(line1);
    
    //上一个按钮
    auto lastBtn = Button::create("button_n.png", "button_s.png");
    lastBtn->setScale9Enabled(true);
    lastBtn->setTitleText("上一个");
    lastBtn->setTitleFontSize(FONT_SIZE_NORMAL);
    lastBtn->setContentSize(Size(200, 70));
    lastBtn->setPosition(Vec2(WIDTH*0.3, 60));
    lastBtn->addTouchEventListener(CC_CALLBACK_2(PlayScene::btnCallback, this));
    lastBtn->setTag(0);
    scrollView->addChild(lastBtn);
    
    //下一个按钮
    auto nextBtn = Button::create("button_n.png", "button_s.png");
    nextBtn->setScale9Enabled(true);
    nextBtn->setTitleText("下一个");
    nextBtn->setTitleFontSize(FONT_SIZE_NORMAL);
    nextBtn->setContentSize(Size(200, 70));
    nextBtn->setPosition(Vec2(WIDTH*0.7, 60));
    nextBtn->addTouchEventListener(CC_CALLBACK_2(PlayScene::btnCallback, this));
    nextBtn->setTag(1);
    scrollView->addChild(nextBtn);
}

void PlayScene::buttonCallback(cocos2d::Ref *sender){
//    Node *node = (Node *)sender;
//    if(node->getTag() == 1){
//        if (contentIndex + 1 >= CONTENTS.size()) {
//        }
//        else{
//            Director::getInstance()->replaceScene(PlayScene::createScene(contentIndex + 1));
//        }
//    }
//    else{
    Director::getInstance()->replaceScene(TransitionSlideInL::create(TRANSITIONDELAY, ContentList::createScene()));
//    }
}

void PlayScene::btnCallback(cocos2d::Ref *pSender, Widget::TouchEventType type){
    if (type == Widget::TouchEventType::ENDED)
    {
        Node *node = (Node *)pSender;
        if (node->getTag() == 0) {
            if (contentIndex > 0) {
                Director::getInstance()->replaceScene(TransitionSlideInL::create(TRANSITIONDELAY, PlayScene::createScene(contentIndex - 1)));
            }
            else{
                MessageBox("没有上一条汤剂", "");
                MYUtils::showAds();
            }
        }else if (node->getTag() == 1){
            if (contentIndex < CONTENTS.size() - 1) {
                Director::getInstance()->replaceScene(TransitionSlideInR::create(TRANSITIONDELAY, PlayScene::createScene(contentIndex + 1)));
            }
            else{
                MessageBox("没有下一条汤剂", "");
                MYUtils::showAds();
            }
        }
    }
}




