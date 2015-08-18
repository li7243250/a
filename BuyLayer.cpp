//
//  BuyLayer.cpp
//  TouchFish
//
//  Created by mac mini on 15/8/17.
//
//

#include "BuyLayer.h"


bool BuyLayer::init(){
    if (!Layer::init()) {
        return false;
    }
//    for (int i = 0; i < 5; i ++) {
//        button[i] = Button::create("b1.png","b2.png","b3.png");
//        button[i]->setPosition(Vec2(750/2, 100 * i + 200));
//        button[i]->addTouchEventListener(CC_CALLBACK_2(BuyLayer::clickButton, this));
//        button[i]->setTag(i);
//        vector_button.push_back(button[i]);
//        this->addChild(button[i]);
//    }
    
    button_ref = Button::create("popover_bonus_bg_weight-hd.png");
    button_ref->setPosition(Vec2(750/3, 600));
    button_ref->addTouchEventListener(CC_CALLBACK_2(BuyLayer::clickButton, this));
    this->addChild(button_ref);
    
    button_sell = Button::create("cocosres/Default/Button_Press.png");
    button_sell->setPosition(Vec2(750/3, 400));
    button_sell->loadTextureDisabled("cocosres/Default/Button_Disable.png");
    button_sell->addTouchEventListener(CC_CALLBACK_2(BuyLayer::clickButton, this));
    this->addChild(button_sell);
    button_sell->setTouchEnabled(false);
    button_sell->setBright(false);
    storage = new Storage;
    storage->init();
    return true;
}

void BuyLayer::clickButton(Ref *ref,Widget::TouchEventType type){
    if (type == Widget::TouchEventType::ENDED) {
        if (button_ref == ref) {
            refreshList();
        }else if (button_sell == ref){
            auto it = storage->getStoryage().begin();
            storage->sellItem(it->first, 0);
        }else{
            Button *bt = dynamic_cast<Button *>(ref);
            storage->buyItem(bt->getName(), 0);
            
        }
    }
}

void BuyLayer::refreshList(){
    
    for_each(vector_button.begin(), vector_button.end(), [](Button *button){
        button->removeFromParent();
    });
    vector_button.clear();
    list_buy->removeAllChildren();
    
    list = storage->getOneList();
    int i = 0;
    for_each(list.begin(), list.end(), [this,&i](pair<string, int> p){
        ValueMap config = storage->getConfig();
        string file_highlight = config[p.first].asValueMap().at("image_highlight").asString();
        string file_normal = config[p.first].asValueMap().at("image_normal").asString();
        string file_disable = config[p.first].asValueMap().at("image_disable").asString();
        Button *button = Button::create(file_normal,file_highlight,file_disable);
        button->setName(p.first);
        button->setTitleFontSize(26);
        button->setTitleText(StringUtils::format("%s:%d",p.first.c_str(),p.second));
        button->setPosition(Vec2(750/2, 100 * i + 200));
        button->addTouchEventListener(CC_CALLBACK_2(BuyLayer::clickButton, this));
        this->addChild(button);
        vector_button.push_back(button);
        i++;
        list_buy->pushBackCustomItem(button);
    });
}

void BuyLayer::getStarFunc(){
    static int i = 0;
    int time = rand()%300;
    i++;
    if (time == 1) {
        log("[get start] %d",i);
        i = 0;
    }
}