//
//  BuyLayer.h
//  TouchFish
//
//  Created by mac mini on 15/8/19.
//
//

#ifndef __TouchFish__BuyLayer__
#define __TouchFish__BuyLayer__

#include "Common.h"

class BuyLayer:public Layer {
    bool init();
    void initList();
    void selectBuilding(Ref* ref,Widget::TouchEventType type);
    ValueMap getConfigByName(string str);

    Button *button_buy;
    ListView *list;
    ImageView *image_select;
    ValueMap config;
    
    int select_price;

public:
    CREATE_FUNC(BuyLayer);
};

#endif /* defined(__TouchFish__BuyLayer__) */
