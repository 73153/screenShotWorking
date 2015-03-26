#ifndef _GAMEOVER_SCENE_H
#define _GAMEOVER_SCENE_H

#include "cocos2d.h"

class GameOverLayer:public cocos2d::CCLayerColor
{
public:
	// GameOverLayer():_label(NULL) {};

	bool init();

	CREATE_FUNC(GameOverLayer);

	CC_SYNTHESIZE_READONLY(cocos2d::CCLabelTTF*, _label, Label);
	
	void gameOverDone();
};

class GameOverScene:public cocos2d::CCScene
{
public:
	bool init();

	CREATE_FUNC(GameOverScene);
	
	CC_SYNTHESIZE_READONLY(GameOverLayer*, _layer, Layer);

	~GameOverScene();
};

#endif