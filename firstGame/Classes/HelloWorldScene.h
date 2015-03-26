#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"

#include "SimpleAudioEngine.h"

class HelloWorld : public cocos2d::CCLayerColor
{
public:

	cocos2d::CCArray *_targets;
	cocos2d::CCArray *_projectiles;

	~HelloWorld();

	// Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
	virtual bool init();  

	// there's no 'id' in cpp, so we recommand to return the exactly class pointer
	static cocos2d::CCScene* scene();

	// a selector callback
	void menuCloseCallback(CCObject* pSender);
	void menuScreenshotCallback(CCObject* pSender);

	// add a enemy
	void addTarget();

	void spriteMoveFinished(CCNode* sender);

	void gameLogic(float dt);

	void update	(float dt);	

	void ccTouchesEnded(cocos2d::CCSet* touches, cocos2d::CCEvent* event);

	// implement the "static node()" method manually
	CREATE_FUNC(HelloWorld);

protected:
	int _projectilesDestroyed;
};

#endif  // __HELLOWORLD_SCENE_H__