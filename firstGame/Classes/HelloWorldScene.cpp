#include "HelloWorldScene.h"
#include "WelcomeScene.h"
#include "GameOverScene.h"
#include "SimpleAudioEngine.h"
#include "FileOperation.h"
#include "R.h"
#include <ctime>
#include <string>

using namespace cocos2d;

HelloWorld::~HelloWorld()
{
	if (_targets)
	{
		_targets->release();
		_targets = NULL;
	}
	if (_projectiles)
	{
		_projectiles->release();
		_projectiles = NULL;
	}
}

CCScene* HelloWorld::scene()
{
	CCScene * scene = NULL;
	do 
	{
		// 'scene' is an autorelease object
		scene = CCScene::create();
		CC_BREAK_IF(! scene);

		// 'layer' is an autorelease object
		HelloWorld *layer = HelloWorld::create();
		CC_BREAK_IF(! layer);

		// add layer as a child to scene
		scene->addChild(layer);
	} while (0);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
	// FileOperation::saveFile();
	this->_projectilesDestroyed = 0;
	_targets = new CCArray;
	_projectiles = new CCArray;

	bool bRet = false;
	do 
	{
		this->schedule( schedule_selector(HelloWorld::gameLogic), 1.0 );
		this->schedule( schedule_selector(HelloWorld::update));
		//////////////////////////////////////////////////////////////////////////
		// super init first
		//////////////////////////////////////////////////////////////////////////
		CC_BREAK_IF(! CCLayerColor::initWithColor(ccc4(150, 150, 150, 150)));

		//////////////////////////////////////////////////////////////////////////
		// add your codes below...
		//////////////////////////////////////////////////////////////////////////

		// 1. Add a menu item with "X" image, which is clicked to quit the program.

		// Create a "close" menu item with close icon, it's an auto release object.
		CCMenuItemImage *pCloseItem = CCMenuItemImage::create(
			"CloseNormal.png",
			"CloseSelected.png",
			this,
			menu_selector(HelloWorld::menuCloseCallback));
		CC_BREAK_IF(! pCloseItem);

		// Place the menu item bottom-right conner.
		pCloseItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 20));

		// Create a menu with the "close" menu item, it's an auto release object.
		CCMenu* pMenu = CCMenu::create(pCloseItem, NULL);
		pMenu->setPosition(CCPointZero);
		CC_BREAK_IF(! pMenu);
		// Add the menu to HelloWorld layer as a child layer.
		this->addChild(pMenu, 1);

		CCMenuItemImage *pScreenshotItem = CCMenuItemImage::create("Screenshot.png"
					, "ScreenshotSelected.png"
					, this
					, menu_selector(HelloWorld::menuScreenshotCallback));
		pScreenshotItem->setPosition(ccp(CCDirector::sharedDirector()->getWinSize().width - 20, 60));

		CCMenu* pScreenshotMenu = CCMenu::create(pScreenshotItem, NULL);
		pScreenshotMenu->setPosition(CCPointZero);
		
		CC_BREAK_IF(! pMenu);
		this->addChild(pScreenshotMenu, 1);
		

		// 2. Add a label shows "Hello World".

		// Create a label and initialize with string "Hello World".
		CCLabelTTF* pLabel = CCLabelTTF::create("Welcome to the Hell!", "Arial", 24);
		CC_BREAK_IF(! pLabel);

		// Get window size and place the label upper. 
		CCSize size = CCDirector::sharedDirector()->getWinSize();
		pLabel->setPosition(ccp(size.width / 2, size.height - 50));

		// Add the label to HelloWorld layer as a child layer.
		this->addChild(pLabel, 1);

		CCSprite *player = CCSprite::create(PLANT_IMG, PLANT_RECT);
		CC_BREAK_IF(! player);
		player->setPosition(ccp(50, size.height/2));
		this->addChild(player, 1);
		addTarget();

		this->setTouchEnabled(true);
		// CocosDenshion::SimpleAudioEngine::sharedEngine()->playBackgroundMusic("background-music-aac.wav", true);
		// CCActionInterval *actionBy = CCMoveBy::create(5, ccp(200,200));
		// player->runAction(actionBy);

		// 3. Add add a splash screen, show the cocos2d splash image.
		// CCSprite* pSprite = CCSprite::create("HelloWorld.png");
		// CC_BREAK_IF(! pSprite);

		// Place the sprite on the center of the screen
		// pSprite->setPosition(ccp(size.width/2, size.height/2));

		// Add the sprite to HelloWorld layer as a child layer.
		// this->addChild(pSprite, 0);

		bRet = true;
	} while (0);

	return bRet;
}

void HelloWorld::menuCloseCallback(CCObject* pSender)
{
	// "close" menu item clicked
	// CCDirector::sharedDirector()->end();
	CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
	CCDirector::sharedDirector()->replaceScene(WelcomeScene::scene());
}

void HelloWorld::menuScreenshotCallback(CCObject* pSender)
{
	std::time_t now_time;
	now_time = std::time(NULL);
	std::stringstream ss;
	std::string str;
	ss<<now_time;
	ss>>str;
	
	CCSize size = CCDirector::sharedDirector()->getWinSize();
	CCRenderTexture* texture = CCRenderTexture::create((int)size.width, (int)size.height);    
    texture->setPosition(ccp(size.width/2, size.height/2));    
    texture->begin();
    CCDirector::sharedDirector()->getRunningScene()->visit();
    texture->end();
	texture->saveToFile("testscreenshot.png", kCCImageFormatPNG);
}

void HelloWorld::addTarget()
{
	// CCLOG("RAND_MAX=%i, %i, %i", RAND_MAX, rand(), rand());
	CCSprite *target = CCSprite::create("Target.png", CCRectMake(0,0,27,40));

	CCSize winSize = CCDirector::sharedDirector()->getWinSize();
	int minX = target->getContentSize().width;
	int maxX = winSize.width - target->getContentSize().width;
	int minY = 10;
	int maxY = winSize.height - target->getContentSize().height - 10;
	int x = maxX;
	int y = rand() % (maxY - minY) + minY;
	// CCLOG("y = %i", y);
	target->setPosition(ccp(x, y));
	this->addChild(target);
	// CCLOG("1");
	int minTime = 2;
	int maxTime = 4;
	int time = rand() % (maxTime - minTime) + minTime;
	CCAction *moveTo = CCMoveTo::create(time, ccp(100, y));
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create( this, callfuncN_selector(HelloWorld::spriteMoveFinished));
	CCArray *actionArrayList = CCArray::create();
	actionArrayList->addObject(moveTo);
	actionArrayList->addObject(actionMoveDone);
	// CCLOG("2");
	target->runAction( CCSequence::create(actionArrayList) );
	target->setTag(1);
	this->_targets->addObject(target);
	// CCLOG("3");
}

void HelloWorld::spriteMoveFinished(CCNode* sender)
{
	// CCLOG("4");
	this->removeChild(sender, true);
	CCSprite *sprite = dynamic_cast<CCSprite*>(sender);
	if (sprite->getTag() == 1)
	{
		this->_targets->removeObject(sprite);
		// GameOverScene* gameOver = GameOverScene::create();
		// gameOver->getLayer()->getLabel()->setString("game over");
		// CCDirector::sharedDirector()->replaceScene(gameOver);
	}
	else if(sprite->getTag() == 2)
	{
		this->_projectiles->removeObject(sprite);
	}
}

void HelloWorld::gameLogic(float dt)
{
	this->addTarget();
}

void HelloWorld::ccTouchesEnded(CCSet* touches, CCEvent* event)
{
	CCLOG("ccTouchesEnded");

	CCSize size = CCDirector::sharedDirector()->getWinSize();

	CCTouch *touch = (CCTouch*)(touches->anyObject());
	CCPoint location = touch->getLocationInView();
	location = CCDirector::sharedDirector()->convertToGL(location);
	CCLOG("location x=%f, y=%f", location.x, location.y);
	if(location.x < 0) return;

	float finalX = size.height/2 * (location.x - 50) / abs(location.y - size.height/2) + 50;
	float finalY = (location.y - size.height/2) > 0 ? size.height : 0;

	float length = sqrt((finalX - 15)*(finalX - 15) + size.height*size.height/4);
	float velocity = 1500/1;
	float realMoveDuration = length/velocity;

	CCSprite *projectile = CCSprite::create("Projectile.png");
	projectile->setPosition(ccp(70, size.height/2));
	this->addChild(projectile);
	// CCAction *moveTo = CCMoveTo::create(0.5, ccp(location.x, location.y));
	CCAction *moveTo = CCMoveTo::create(realMoveDuration, ccp(finalX, finalY));
	CCFiniteTimeAction* actionMoveDone = CCCallFuncN::create( this, callfuncN_selector(HelloWorld::spriteMoveFinished));
	CCArray *actionArrayList = CCArray::create();
	actionArrayList->addObject(moveTo);
	actionArrayList->addObject(actionMoveDone);
	projectile->runAction(CCSequence::create(actionArrayList));
	projectile->setTag(2);
	this->_projectiles->addObject(projectile);
	CocosDenshion::SimpleAudioEngine::sharedEngine()->playEffect("pew-pew-lei.wav",false);
	//CCARRAY_FOREACH
}

void HelloWorld::update(float dt)
{
	CCArray *targetToDel = new CCArray;
	CCArray *projectileToDel = new CCArray;

	CCObject *i = NULL;
	CCObject *j = NULL;

	CCARRAY_FOREACH(_targets, i)
	{
		CCSprite *target = dynamic_cast<CCSprite*>(i);
		CCRect targetRect = CCRect::CCRect(
			target->getPositionX()-target->getContentSize().width/2
			, target->getPositionY()-target->getContentSize().width/2
			, target->getContentSize().width
			, target->getContentSize().height);
		CCARRAY_FOREACH(_projectiles, j)
		{
			CCSprite *projectile = dynamic_cast<CCSprite*>(j);
			CCRect projectileRect = CCRect::CCRect(
				projectile->getPositionX()-projectile->getContentSize().width/2
				, projectile->getPositionY()-projectile->getContentSize().width/2
				, projectile->getContentSize().width
				, projectile->getContentSize().height);
			if(targetRect.intersectsRect(projectileRect))
			{
				CCParticleSystem* m_emitter;
				m_emitter = CCParticleFlower::create();
				m_emitter->retain();
				this->addChild(m_emitter, 10);
				m_emitter->setTexture( CCTextureCache::sharedTextureCache()->addImage("stars.png") );
				m_emitter->setPosition(ccp(projectile->getPositionX(), projectile->getPositionY()));
				m_emitter->setDuration(0.5);
				m_emitter->setScale(0.5);

				this->_targets->removeObject(target);
				this->removeChild(target, true);
				this->_projectiles->removeObject(projectile);
				this->removeChild(projectile, true);
				this->_projectilesDestroyed += 1;
				if(this->_projectilesDestroyed >= 5) {
					GameOverScene* gameOver = GameOverScene::create();
					gameOver->getLayer()->getLabel()->setString("yeah");
					CocosDenshion::SimpleAudioEngine::sharedEngine()->pauseBackgroundMusic();
					CCDirector::sharedDirector()->replaceScene(gameOver);
				}
			}
		}
	}

}