#ifndef __WELCOME_SCENE_H__
#define __WELCOME_SCENE_H__

#include "cocos2d.h"

class WelcomeLayer : public cocos2d::CCLayerColor
{
public:

	CREATE_FUNC(WelcomeLayer);

	virtual bool init();
};

class WelcomeScene
{
public:

	static cocos2d::CCScene* scene();

	void startGame(cocos2d::CCObject* pSender);

	void endGame(cocos2d::CCObject* pSender);
};


#endif  // __WELCOME_SCENE_H__