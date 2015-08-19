//
//  FrontLayer.h
//  TouchFish
//
//  Created by mac mini on 15/8/13.
//
//

#ifndef __TouchFish__FrontLayer__
#define __TouchFish__FrontLayer__

#include "Common.h"
#include "Storage.h"

class FrontLayer:public Layer {
    bool init();
    void timeOut();
    void refreshSellList();
    void refreshStorageList();
    void clickButton(Ref *ref,Widget::TouchEventType type);
    void clickStoryageButton(Ref *ref,Widget::TouchEventType type);
    void setCurrentPanel(Widget *panel);
    
    void sliderChange(Ref* ref,Slider::EventType type);
    void refreshSlider(Slider* slider);
    
    void eventSell();
    
    void disableAllButton(vector<Button *> bt,bool disable);
    void refreshGold();
        
    Node *node_csb;
    Button *button_buy,*button_sell;
    Button *button_change_market;
    ListView *list_sell,*list_storage;
    Widget *cell_sell,*cell_storage;
    Widget *panel_news,*panel_message,*panel_sell,*panel_buy;
    
    Text *text_buy_slider;
    Text *text_sell_slider;
    Slider *slider_buy;
    Slider *slider_sell;
    
    
    Text *text_gold;
    int max;
    Storage *storage;
    map<string,int> map_buylist;
    string select_item;
    
    vector<Button *> vector_button;
    vector<Button *> vector_sell;
    vector<Button *> vector_storage;
    
public:
    CREATE_FUNC(FrontLayer);
};


#endif /* defined(__TouchFish__FrontLayer__) */
