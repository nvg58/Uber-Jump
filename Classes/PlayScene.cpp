//
//  PlayScene.cpp
//  UberJump_v3
//
//  Created by Giap Nguyen on 5/4/14.
//
//

#include "PlayScene.h"

USING_NS_CC;

Scene* PlayScene::createScene()
{
  // 'scene' is an autorelease object
  auto scene = Scene::createWithPhysics();
  scene->getPhysicsWorld()->setDebugDrawMask(PhysicsWorld::DEBUGDRAW_ALL);
    
  // 'layer' is an autorelease object
  auto layer = PlayScene::create();
  layer->setPhyWorld(scene->getPhysicsWorld());
  
  // add layer as a child to scene
  scene->addChild(layer);
  
  // return the scene
  return scene;
}

// on "init" you need to initialize your instance
bool PlayScene::init()
{
  if ( !Layer::init() )
  {
    return false;
  }

  _backgroundNode = createBackgroundNode();
  this->addChild(_backgroundNode);
  
  _foregroundNode = Layer::create();
  this->addChild(_foregroundNode);
  
  _hubNode = Layer::create();
  this->addChild(_hubNode);
  
  _player = createPlayer();
  _foregroundNode->addChild(_player);
  
  _tapToStart = Sprite::create("Assets.atlas/TapToStart@2x.png");
  _tapToStart->setPosition(SCREEN_SIZE.width/2, 300);
  _hubNode->addChild(_tapToStart);
  
  auto touchListener = EventListenerTouchOneByOne::create();
  touchListener->onTouchBegan = CC_CALLBACK_2(PlayScene::onTouchBegan, this);
  _eventDispatcher->addEventListenerWithSceneGraphPriority(touchListener, this);
  
  return true;
}

Layer * PlayScene::createBackgroundNode()
{
  Layer * backgroundNode = Layer::create();
  for (int nodeCount = 1; nodeCount <= NUMBER_BACKGROUND_IMG; ++nodeCount) {
    const char * infix = nodeCount < 10 ? "0" : "";
    Sprite * node =
      Sprite::create(
       __String::createWithFormat("Backgrounds/Background%s%d@2x.png",
                                  infix,
                                  nodeCount)->getCString());
    node->setPosition(SCREEN_SIZE.width/2, 128.0 * (nodeCount - 1));
    
    backgroundNode->addChild(node);
  }
  
  return backgroundNode;
}

Sprite * PlayScene::createPlayer()
{
  Sprite * player = Sprite::create("Assets.atlas/Player@2x.png");
  auto body = PhysicsBody::createCircle(player->getContentSize().width/2);
  player->setPhysicsBody(body);
  
//  auto b = PhysicsBody::createBox(Size(100, 100));
//  player->setPhysicsBody(b);
  
  body->setDynamic(false);
  body->setRotationEnable(false);
  player->setPosition(Point(SCREEN_SIZE.width/2, 100));
  
  return player;
}

void PlayScene::setPhyWorld(cocos2d::PhysicsWorld *world)
{
  _world = world;
//  _world->setGravity(Vect(0, -100.0f));
}


bool PlayScene::onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event)
{
  if (_player->getPhysicsBody()->isDynamic())
    return false;
  
  _tapToStart->removeFromParentAndCleanup(true);
  _player->getPhysicsBody()->applyImpulse(Vect(0, 200));
  
  _player->getPhysicsBody()->setDynamic(true);
  return true;
}


