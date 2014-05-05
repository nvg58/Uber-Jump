//
//  PlayScene.h
//  UberJump_v3
//
//  Created by Giap Nguyen on 5/4/14.
//
//

#ifndef __UberJump_v3__PlayScene__
#define __UberJump_v3__PlayScene__

#include "cocos2d.h"
#include "Constant.h"

class PlayScene : public cocos2d::Layer
{
public:
  // there's no 'id' in cpp, so we recommend returning the class instance pointer
  static cocos2d::Scene* createScene();
  
  // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
  virtual bool init();
  
  // implement the "static create()" method manually
  CREATE_FUNC(PlayScene);
  
  cocos2d::Layer * createBackgroundNode();
  cocos2d::Sprite * createPlayer();
  
  void setPhyWorld(cocos2d::PhysicsWorld * world);

  virtual bool onTouchBegan(cocos2d::Touch *touch, cocos2d::Event *event);
private:
  cocos2d::Layer * _backgroundNode;
  cocos2d::Layer * _middlegroundNode;
  cocos2d::Layer * _foregroundNode;
  cocos2d::Layer * _hubNode;
  cocos2d::Sprite * _player;
  cocos2d::Sprite * _tapToStart;
  
  cocos2d::PhysicsWorld * _world;
};

#endif /* defined(__UberJump_v3__PlayScene__) */
