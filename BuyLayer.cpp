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
    for (int i = 0; i < 5; i ++) {
        button[i] = Button::create("popover_bonus_bg_weight-hd.png");
        button[i]->setPosition(Vec2(750/2, 50 * i + 200));
        button[i]->addTouchEventListener(CC_CALLBACK_2(BuyLayer::clickButton, this));
        button[i]->setTag(i);
        button[i]->setScale(2);
        this->addChild(button[i]);
    }
    
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
    list = storage->getOneList();
    int i = 0;
    for_each(list.begin(), list.end(), [this,&i](pair<string, int> p){
        button[i]->setName(p.first);
        button[i]->setTitleText(StringUtils::format("%s:%d",p.first.c_str(),p.second));
        i++;
    });
}