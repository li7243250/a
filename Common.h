//
//  Common.h
//  game
//
//  Created by mac mini on 15/4/30.
//
//

#ifndef __game__Common__
#define __game__Common__

#include <iostream>
#include "cocos2d.h"
#include "extensions/cocos-ext.h"
#include "ui/CocosGUI.h"
#include"cocostudio/CocoStudio.h"
#include "SimpleAudioEngine.h"
#include "Singleton.h"
#include "Marcos.h"
#include "Component.h"
USING_NS_CC;
USING_NS_CC_EXT;
using namespace cocos2d::ui;
using namespace cocostudio::timeline;
using namespace std;

#define CREATE_COMPENT(__COMP__NAME__,__VALUE__MAP__) __COMP__NAME__::createWithValueMap(__VALUE__MAP__);


inline void dispatchEvent(string event_name,void* user_data){
    Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(event_name,user_data);
}

inline void formatStringLF(string &str){
    while (str.find("\\n")!=string::npos) {
        size_t index = str.find("\\n");
        str.replace(index, 2, "\n");
    }
}

inline void playEffect(const string& file){
    CocosDenshion::SimpleAudioEngine::getInstance()->preloadEffect(file.c_str());
    CocosDenshion::SimpleAudioEngine::getInstance()->playEffect(file.c_str());
}

inline LanguageType getLanguageType(){
    return Application::getInstance()->getCurrentLanguage();
}

inline bool isLangeuageChinese(){
    return Application::getInstance()->getCurrentLanguage() == LanguageType::CHINESE;
//    Application::getInstance()->getCurrentLanguage() == LanguageType::ENGLISH;
}

inline void loadConfig(ValueMap &config,const string& file){
    std::string fullPath = FileUtils::getInstance()->fullPathForFilename(file);
    config = FileUtils::getInstance()->getValueMapFromFile(fullPath);
//    if (isLangeuageChinese()) {
//        loadConfigWithSuf(config,file,"_en");
//    }
}

inline void loadConfigWithSuf(ValueMap &config,const string& file,const string& suffix){
    string re_file = file;
    if (!isLangeuageChinese()) {
        size_t index = file.find(".plist");
        re_file.insert(index,suffix);
    }
    loadConfig(config,re_file);
};
#endif /* defined(__game__Common__) */
