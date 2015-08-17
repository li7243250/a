//
//  BuyLayer.h
//  TouchFish
//
//  Created by mac mini on 15/8/17.
//
//

#ifndef __TouchFish__BuyLayer__
#define __TouchFish__BuyLayer__

#include "Common.h"
#include "Storage.h"

class BuyLayer:public Layer {
    bool init();
    void clickButton(Ref *ref,Widget::TouchEventType type);
    void refreshList();

    Button *button[5];
    Button *button_ref;
    Button *button_sell;
    Storage *storage;
    
    map<string,int> list;
public:
    CREATE_FUNC(BuyLayer);
};

#endif /* defined(__TouchFish__BuyLayer__) */
