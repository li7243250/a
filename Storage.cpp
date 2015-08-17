//
//  Storage.cpp
//  TouchFish
//
//  Created by mac mini on 15/8/17.
//
//

#include "Storage.h"

template <typename T1,typename T2>
inline pair<T1, T2> getPairRandom(map<T1,T2> data){
    int i = rand()%data.size();
    auto it = data.begin();
    for (int j = 0; j <i; j++){
        it++;
    }
    return *it;
}

inline pair<string, Value> getPairRandom(ValueMap data){
    int i = rand()%data.size();
    auto it = data.begin();
    for (int j = 0; j <i; j++){
        it++;
    }
    return *it;
}

bool Storage::init(){
    
    setInstance(this);
    initItemBase();
    srand((unsigned)time(NULL));
    return true;
}

void Storage::initItemBase(){
    loadConfig(config_base, "Config.plist");

    for_each(config_base.begin(), config_base.end(), [this](pair<string, Value> it){
        item_base[it.first] = it.second.asValueMap().at("price").asInt();
    });
    
    item_init = item_base;
}

void Storage::changePrice(){
    for_each(item_base.begin(), item_base.end(), [&](pair<string, int> p){
        float factor = rand_0_1()+0.5;
        p.second = p.second * factor;
        if (p.second < item_init.find(p.first)->second) {
            p.second =item_init.at(p.first);
        }
        item_base[p.first] = p.second;
    });
}

map<string,int> Storage::getOneList(int size){
    changePrice();

    map<string,int> ret;
    if (size > item_base.size()) {
        return ret;
    }

    for (int i = 0; i < size; i++) {
        auto it = getPairRandom(item_base);
        while (ret.find(it.first)!=ret.end()) {
            it = getPairRandom(item_base);
        }
        ret.insert(it);
    }
    buy_list = ret;
    return ret;
}

void Storage::buyItem(string item, int count){
    int price = item_base[item];
    gold -= count*price;
    storage[item].count += count;
    dumpItem();
}

void Storage::sellItem(string item,int count){
    
    if (buy_list.find(item) == buy_list.end()) {
        return;
    }
    
    storage[item].count -= count;
    gold+=count*item_base[item];
    if (storage[item].count <= 0) {
        storage.erase(storage.find(item));
    }
    dumpItem();
}

string Storage::changePositionEvent(){
    string random_item = getPairRandom(buy_list).first;

    ValueMap event = config_base[random_item].asValueMap().at("event").asValueMap();
    if (event.size() > 0) {
        pair<string, Value> random_event = getPairRandom(event);
        buy_list[random_item] = random_event.second.asFloat() * buy_list[random_event.first];
        return random_event.first;
        
    }
    return "";
}

void Storage::dumpItem(){
    log("[gold]%d",gold);
    for_each(storage.begin(), storage.end(), [](pair<string, ItemInfo> it){
        log("[storage]%s  %d  %d",it.first.c_str(),it.second.count ,it.second.price);
    });
}

string Storage::sellEvent(string item){
    ValueMap event = config_base[item].asValueMap().at("reputation").asValueMap();
    if (event.size() > 0) {
        pair<string, Value> random_event = getPairRandom(event);
        health+=random_event.second.asInt();
        return random_event.first;
        
    }
    return "";
}

void Storage::healthEvent(){
    
}