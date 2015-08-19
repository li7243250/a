//
//  FrontLayer.cpp
//  TouchFish
//
//  Created by mac mini on 15/8/13.
//
//

#include "FrontLayer.h"
#include "stdlib.h"
#include "StringConfig.h"

bool FrontLayer::init(){
    if (!Layer::init()) {
        return false;
    }
    
    node_csb = CSLoader::createNode("FrontLayer.csb");
    this->addChild(node_csb);
    
    auto node_layer = CSLoader::createNode("Layer.csb");
    this->addChild(node_layer);
    
    list_sell = dynamic_cast<ListView *>(node_layer->getChildByName("ListView_1"));
    list_storage = dynamic_cast<ListView *>(node_layer->getChildByName("ListView_1_0"));
    
    cell_sell = dynamic_cast<Widget *>(node_layer->getChildByName("Panel_1"));
    cell_storage = dynamic_cast<Widget *>(node_layer->getChildByName("Panel_1_0"));
    
    text_gold = dynamic_cast<Text*>(node_layer->getChildByName("Text_6"));
    button_change_market = dynamic_cast<Button *>(node_layer->getChildByName("Button_13"));
    button_change_market->addTouchEventListener(CC_CALLBACK_2(FrontLayer::clickButton, this));
    
    panel_buy = dynamic_cast<Widget *>(node_layer->getChildByName("Panel_buy"));
    slider_buy = panel_buy->getChildByName<Slider *>("Slider_1");
    slider_buy->addEventListener(CC_CALLBACK_2(FrontLayer::sliderChange, this));
    button_buy = dynamic_cast<Button *>(panel_buy->getChildByName("Button_12"));
    button_buy->addTouchEventListener(CC_CALLBACK_2(FrontLayer::clickButton, this));
    text_buy_slider = dynamic_cast<Text *>(panel_buy->getChildByName("Text_1"));

    panel_sell = dynamic_cast<Widget *>(node_layer->getChildByName("Panel_sell"));
    slider_sell = panel_sell->getChildByName<Slider *>("Slider_1");
    slider_sell->addEventListener(CC_CALLBACK_2(FrontLayer::sliderChange, this));
    button_sell = dynamic_cast<Button *>(panel_sell->getChildByName("Button_12"));
    button_sell->addTouchEventListener(CC_CALLBACK_2(FrontLayer::clickButton, this));
    text_sell_slider = dynamic_cast<Text *>(panel_sell->getChildByName("Text_1"));
    
    storage = Storage::create();
    refreshSellList();
    refreshGold();
    setCurrentPanel(nullptr);

    
    return true;
}



void FrontLayer::disableAllButton(vector<Button *> bt,bool disable){
    for_each(bt.begin(), bt.end(), [disable](Button *button){
        button->setTouchEnabled(disable);
        button->setBright(disable);
    });
}

void FrontLayer::refreshGold(){
    text_gold->setString(to_string(storage->gold));
}

void FrontLayer::eventSell(){
    string str =storage->sellEvent(select_item);
    panel_news->setVisible(true);
    auto text = dynamic_cast<Text *>(panel_news->getChildByName("Text_12"));
    text->setString(str);
}

void FrontLayer::clickButton(Ref *ref,Widget::TouchEventType type){
    if (type == Widget::TouchEventType::ENDED) {
        Button *button = dynamic_cast<Button *>(ref);
        if (button == button_buy) {
            if (storage->getStoryage().find(select_item) == storage->getStoryage().end() && storage->getStoryage().size() == 5) {
                MessageBox("wtf", "wtf");
                return;
            }
            storage->buyItem(select_item, atoi(text_buy_slider->getString().c_str()));
            refreshStorageList();
            refreshGold();
            setCurrentPanel(nullptr);
            disableAllButton(vector_storage, true);
            disableAllButton(vector_sell, true);
        }else if (button == button_sell){
            storage->sellItem(select_item, atoi(text_sell_slider->getString().c_str()));
            refreshStorageList();
            refreshGold();
            setCurrentPanel(nullptr);
        }else if (button == button_change_market){
            disableAllButton(vector_storage, true);
            refreshSellList();
        }else{
            select_item = button->getName();
            int store_ablity =storage->store - storage->current_store;
            max = storage->gold/map_buylist[select_item]>store_ablity?store_ablity:storage->gold/map_buylist[select_item];
            refreshSlider(slider_buy);
            disableAllButton(vector_sell,true);
            disableAllButton(vector_storage, true);

            button->setBright(false);
            button->setTouchEnabled(false);
            setCurrentPanel(panel_buy);
        }
    }
}

void FrontLayer::clickStoryageButton(Ref *ref,Widget::TouchEventType type){
    Button *button = dynamic_cast<Button *>(ref);
    if (type == Widget::TouchEventType::ENDED) {
        select_item = button->getName();
        max = storage->getStoryage()[select_item].count;
        refreshSlider(slider_sell);
        disableAllButton(vector_sell,true);
        disableAllButton(vector_storage, true);
        button->setBright(false);
        button->setTouchEnabled(false);
        setCurrentPanel(panel_sell);
    }
}

void FrontLayer::setCurrentPanel(Widget *panel){
    panel_buy->setVisible(false);
    panel_sell->setVisible(false);
    if (panel) {
        panel->setVisible(true);
    }

}

void FrontLayer::refreshSellList(){
    vector_sell.clear();
    list_sell->removeAllChildren();
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
        button->setTitleText(StringUtils::format("%s",p.first.c_str()));
        button->addTouchEventListener(CC_CALLBACK_2(FrontLayer::clickButton, this));
        button->setTitleColor(Color3B::BLACK);
        vector_sell.push_back(button);
        auto cell =  cell_sell->clone();
        auto bt_cell = cell->getChildByName<Button *>("Button_2");
        auto text_count = cell->getChildByName<Text *>("Text_3");
        text_count->setString(to_string(p.second));
        button->setPosition(bt_cell->getPosition());
        bt_cell->getParent()->addChild(button);
        bt_cell->removeFromParent();
        
        list_sell->pushBackCustomItem(cell);
        i++;
    });
}



void FrontLayer::refreshStorageList(){
    vector_storage.clear();
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
        button->setTitleText(StringUtils::format("%s",p.first.c_str()));
        button->setTitleColor(Color3B::BLACK);
        button->addTouchEventListener(CC_CALLBACK_2(FrontLayer::clickStoryageButton, this));
        vector_storage.push_back(button);
        auto cell = cell_storage->clone();
        auto bt_cell = cell->getChildByName<Button *>("Button_2");
        auto text_count = cell->getChildByName<Text *>("Text_3");
        auto text_price = cell->getChildByName<Text *>("Text_5");
        
        button->setPosition(bt_cell->getPosition());
        bt_cell->getParent()->addChild(button);
        bt_cell->removeFromParent();
        text_count->setString(to_string(p.second.count));
        text_price->setString(to_string(p.second.price));
        list_storage->pushBackCustomItem(cell);
        i++;
    });
}



void FrontLayer::sliderChange(Ref* ref,Slider::EventType type){
    if (type == Slider::EventType::ON_PERCENTAGE_CHANGED) {
        if (ref == slider_sell) {
            float percent = slider_sell->getPercent()/100.;
            int current = percent * max;
            text_sell_slider->setString(to_string(current));
            Text *text = dynamic_cast<Text *>(panel_sell->getChildByName("Text_8"));
            if (map_buylist.find(select_item) != map_buylist.end()) {
                int earn =current * (map_buylist[select_item] - storage->getStoryage()[select_item].price);
                if (earn>0) {
                    string content = StringUtils::format(StringConfig::getString("1").c_str(),select_item.c_str(),earn);
                    text->setString(content);
                }else{
                    string content = StringUtils::format(StringConfig::getString("2").c_str(),abs(earn));
                    text->setString(content);
                    
                }
            }else{
                text->setString(StringConfig::getString("3"));
            }

        }else if(ref == slider_buy){
            float percent = slider_buy->getPercent()/100.;
            int current = percent * max;
            text_buy_slider->setString(to_string(current));
        }
    }
}

void FrontLayer::refreshSlider(Slider* slider){
    slider->setPercent(100);
    sliderChange(slider, Slider::EventType::ON_PERCENTAGE_CHANGED);
    
}
