#include "WelcomeScene.h"
#include "HelloWorldScene.h"

USING_NS_CC;

CCScene* WelcomeScene::scene()
{
	CCScene *scene = NULL;
	do {
		scene = CCScene::create();
		CC_BREAK_IF(!scene);

		WelcomeLayer *layer = WelcomeLayer::create();
		CC_BREAK_IF(!layer);
		scene->addChild(layer);

	} while(0);
	return scene;
}

bool WelcomeLayer::init()
{
	bool bRet = false;
	do 
	{
		CC_BREAK_IF(!CCLayerColor::initWithColor(ccc4(150, 150, 150, 150)));

		CCSize winSize = CCDirector::sharedDirector()->getWinSize();

		CCMenuItemImage *pStartItem = CCMenuItemImage::create(
			"start_game_button_1.jpg",
			"start_game_button_2.jpg",
			this,
			menu_selector(WelcomeScene::startGame));
		CC_BREAK_IF(!pStartItem);
		pStartItem->setPosition(ccp(winSize.width/2, winSize.height/2+42));
		CCMenu* pStartMenu = CCMenu::create(pStartItem, NULL);
		pStartMenu->setPosition(CCPointZero);
		CC_BREAK_IF(!pStartMenu);
		this->addChild(pStartMenu, 1);

		CCMenuItemImage *pEndItem = CCMenuItemImage::create(
			"exit_game_button_1.jpg",
			"exit_game_button_2.jpg",
			this,
			menu_selector(WelcomeScene::endGame));
		CC_BREAK_IF(!pStartItem);
		pEndItem->setPosition(ccp(winSize.width/2, winSize.height/2-42));
		CCMenu* pEndMenu = CCMenu::create(pEndItem, NULL);
		pEndMenu->setPosition(CCPointZero);
		CC_BREAK_IF(!pEndMenu);
		this->addChild(pEndMenu, 1);

		bRet = true;
	} while(0);
	return bRet;
}

void WelcomeScene::startGame(CCObject* pSender)
{
	CCDirector::sharedDirector()->replaceScene(HelloWorld::scene());
}

void WelcomeScene::endGame(CCObject* pSender)
{
	CCDirector::sharedDirector()->end();
}