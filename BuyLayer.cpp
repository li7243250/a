//
//  BuyLayer.cpp
//  TouchFish
//
//  Created by mac mini on 15/8/19.
//
//

#include "BuyLayer.h"

bool BuyLayer::init(){
    if (!Layer::init()) {
        return false;
    }
    
    loadConfig(config, "BuildConfig.plist");
    
    
    return true;
}

void BuyLayer::initList(){
    for (int i = 0; i < config.size(); i++) {
        ValueMap value = config.at(to_string(i)).asValueMap();
        ImageView *image = ImageView::create(value.at("image").asString());
        list->pushBackCustomItem(image);
        image->addTouchEventListener(CC_CALLBACK_2(BuyLayer::selectBuilding,this));
        image->setName(value.at("name").asString());
    }
}

void BuyLayer::selectBuilding(Ref* ref,Widget::TouchEventType type){
    ImageView *image = dynamic_cast<ImageView *>(ref);
    if (type == Widget::TouchEventType::ENDED) {
        string name = image->getName();
        ValueMap buildinfo = getConfigByName(name);
        int price = buildinfo.at("price").asInt();
        select_price = price;
        button_buy->setVisible(true);
        image->addChild(image_select);
    }
}

ValueMap BuyLayer::getConfigByName(string str){
    ValueMap ret;
    for_each(config.begin(), config.end(), [&ret,str](pair<string, Value> it){
        if (str == it.second.asValueMap().at("name").asString()) {
            ret = it.second.asValueMap();
        }
    });
    return ret;
}