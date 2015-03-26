#include "GameOverScene.h"
#include "WelcomeScene.h"

using namespace cocos2d;

bool GameOverLayer::init()
{

	if(CCLayerColor::initWithColor(ccc4(255, 255, 255, 255)))
	{
		CCSize winSize = CCDirector::sharedDirector()->getWinSize();
		this->_label = CCLabelTTF::create("","Artial", 36);
		this->retain();
		this->_label->setColor( ccc3(0, 0, 0) );
		this->_label->setPosition(ccp(winSize.width/2, winSize.height/2));
		this->addChild(_label);
		CCArray *actions = CCArray::create();
		actions->addObject(CCDelayTime::create(3));
		actions->addObject(CCCallFunc::create(this, callfunc_selector(GameOverLayer::gameOverDone)));
		this->runAction( CCSequence::create(actions));
		return true;
	}
	else {
		return false;}
}

void GameOverLayer::gameOverDone()
{
	CCDirector::sharedDirector()->replaceScene(WelcomeScene::scene());
}

bool GameOverScene::init()
{
	bool bRet = false;
	do
	{
		this->_layer = GameOverLayer::create();
		this->addChild(this->_layer);
		bRet = true;
	} while (0);
	return bRet;
}

GameOverScene::~GameOverScene()
{
	if(this->_layer)
	{
		this->_layer->release();
		this->_layer = NULL;
	}
}