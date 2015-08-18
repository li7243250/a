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
    void setSlider();
    
    void bindButton(Button *button);
    void disableAllButton(bool disable);
    
    Node *node_csb;
    Button *button_buy,*button_sell;
    ListView *list_buy,*list_storage;
    
    Text *text_slider;
    int max;
    Storage *storage;
    Slider *slider;
    map<string,int> map_buylist;

    
    vector<Button *> vector_button;
public:
    CREATE_FUNC(FrontLayer);
};


#endif /* defined(__TouchFish__FrontLayer__) */
