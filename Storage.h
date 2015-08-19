//
//  Storage.h
//  TouchFish
//
//  Created by mac mini on 15/8/17.
//
//

#ifndef __TouchFish__Storage__
#define __TouchFish__Storage__

#include "Common.h"
struct ItemInfo{
    int count = 0;
    int price = 0;
};

class Storage:public Singleton<Storage> {
    void initItemBase();
    void changePrice();

    ValueMap config_base;
    map<string,int> item_base;
    map<string,int> item_init;
    map<string,int> buy_list;
    map<string,ItemInfo> storage;

public:
    
    bool init();
    static Storage* create();
    void dumpItem();
    
    void buyItem(string item, int count);
    void sellItem(string item,int count);
    
    string changePositionEvent();
    string sellEvent(string item);
    void healthEvent(string item);
    
    map<string,int> getOneList(int size = 5);
    map<string,ItemInfo> getStoryage(){
        return storage;
    }
    ValueMap getConfig(){
        return config_base;
    }
    
    int gold = 3000;
    int health = 100;
    int reputation = 100;
    int store = 100;
    int current_store = 0;

};

#endif /* defined(__TouchFish__Storage__) */
