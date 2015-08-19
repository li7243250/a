//
//  StringConfig.cpp
//  TouchFish
//
//  Created by mac mini on 15/8/19.
//
//

#include "StringConfig.h"

string StringConfig::getString(string id){
    ValueMap config;
    loadConfig(config, "StringConfig.plist");
    string ret = "";
    for_each(config.begin(), config.end(), [id,&ret](pair<string, Value> it){
        string id_ = it.second.asValueMap().at("id").asString();
        if (id_ == id) {
            ret = it.second.asValueMap().at("desc").asString();
        }
    });
    return ret;
}

void setMement(){
    stack<int> stack_foo;
    stack_foo.push(1);
    int current = stack_foo.top();
    stack_foo.pop();
    hash<int> ma;
    
    
}