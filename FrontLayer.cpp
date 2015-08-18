//
//  FrontLayer.cpp
//  TouchFish
//
//  Created by mac mini on 15/8/13.
//
//

#include "FrontLayer.h"
#include "BuyLayer.h"
#include "stdlib.h"

bool FrontLayer::init(){
    if (!Layer::init()) {
        return false;
    }
    
    node_csb = CSLoader::createNode("FrontLayer.csb");
    this->addChild(node_csb);

    storage = Storage::create();
    
    return true;
}

void FrontLayer::bindButton(Button *button){
    vector_button.push_back(button);
}

void FrontLayer::disableAllButton(bool disable){
    for_each(vector_button.begin(), vector_button.end(), [disable](Button *button){
        button->setTouchEnabled(disable);
        button->setBright(disable);
    });
}

void FrontLayer::refreshSellList(){
    list_buy->removeAllChildren();
    map_buylist = storage->getOneList();
    int i = 0;
    for_each(map_buylist.begin(), map_buylist.end(), [this,&i](pair<string, int> p){
        ValueMap config = storage->getConfig();
        string file_highlight = config[p.first].asValueMap().at("image_highlight").asString();
        string file_normal = config[p.first].asValueMap().at("image_normal").asString();
        string file_disable = config[p.first].asValueMap().at("image_disable").asString();
        Button *button = Button::create(file_normal,file_highlight,file_disable);
        button->setName(p.first);
        button->setTitleFontSize(26);
        button->setTitleText(StringUtils::format("%s:%d",p.first.c_str(),p.second));
        button->addTouchEventListener(CC_CALLBACK_2(FrontLayer::clickButton, this));
        list_buy->pushBackCustomItem(button);
        i++;
    });
}

void FrontLayer::clickButton(Ref *ref,Widget::TouchEventType type){
    if (type == Widget::TouchEventType::ENDED) {
        Button *button = dynamic_cast<Button *>(ref);
        if (button == button_buy) {
            
        }else if (button == button_sell){
            storage->sellItem(button->getName(), atoi(text_slider->getString().c_str()));
        }else{
            storage->buyItem(button->getName(), atoi(text_slider->getString().c_str()));
        }
    }
}

void FrontLayer::refreshStorageList(){
    list_storage->removeAllChildren();
    auto list = storage->getStoryage();
    int i = 0;
    for_each(list.begin(), list.end(), [this,&i](pair<string, ItemInfo> p){
        ValueMap config = storage->getConfig();
        string file_highlight = config[p.first].asValueMap().at("image_highlight").asString();
        string file_normal = config[p.first].asValueMap().at("image_normal").asString();
        string file_disable = config[p.first].asValueMap().at("image_disable").asString();
        Button *button = Button::create(file_normal,file_highlight,file_disable);
        button->setName(p.first);
        button->setTitleFontSize(26);
        button->setTitleText(StringUtils::format("%s:%d",p.first.c_str(),p.second.count));
        button->addTouchEventListener(CC_CALLBACK_2(FrontLayer::clickButton, this));
        list_storage->pushBackCustomItem(button);
        i++;
    });
}

void FrontLayer::setSlider(){
    slider->setPercent(100);
    slider->addEventListener([this](Ref* ,Slider::EventType type){
        if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
            float percent = slider->getPercent()/100;
            int current = percent * max;
            text_slider->setString(to_string(current));
        }
    });
}