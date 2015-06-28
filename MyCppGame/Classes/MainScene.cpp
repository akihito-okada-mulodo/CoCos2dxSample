//
//  MainScene.cpp
//  KawazCatch
//
//  Created by giginet on 5/15/14.
//
//
#include "MainScene.h"

USING_NS_CC;

/// マージン
const int FRUIT_TOP_MERGIN = 40;

// フルーツの出現率
const int FRUIT_SPAWN_RATE = 20;

const int FALLING_DURATION = 3;

MainScene::MainScene() :
        _player(NULL) {

}

MainScene::~MainScene() {
    CC_SAFE_RELEASE_NULL(_player);
}

Scene* MainScene::createScene() {
    auto scene = Scene::create();
    auto layer = MainScene::create();
    scene->addChild(layer);
    return scene;
}

bool MainScene::init() {
    if (!Layer::init()) {
        return false;
    }

    // 初期化処理

    // 背景を表示する
    auto director = Director::getInstance();
    auto size = director->getWinSize();
    auto background = Sprite::create("background.png");
    background->setPosition(Vec2(size.width / 2.0, size.height / 2.0));
    this->addChild(background);

    auto player = Sprite::create("player.png");
    this->setPlayer(player);
    player->setPosition(Vec2(size.width / 2.0, size.height - 445));
    this->addChild(player);

    // イベントリスナーの追加
    auto listener = EventListenerTouchOneByOne::create();
    listener->onTouchBegan = [](Touch* touch, Event* event) {
        // タッチされたとき
            log("Touch at (%f, %f)", touch->getLocation().x, touch->getLocation().y);
            return true;
        };
    listener->onTouchMoved = [this, size](Touch* touch, Event* event) {
        // タッチ位置が動いたとき
        // 前回とのタッチ位置との差をベクトルで取得する
            Vec2 delta = touch->getDelta();

        // 現在のかわずたんの座標を取得する
            Vec2 position = _player->getPosition();

        // 現在座標 + 移動量を新たな座標にする
            Vec2 newPosition = position + delta;

        // 画面外に飛び出していたら補正する
            newPosition = newPosition.getClampPoint(Vec2(0, position.y), Vec2(size.width, position.y));

            _player->setPosition(newPosition);
        };
    listener->onTouchEnded = [](Touch* touch, Event* event) {

    };
    this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);

    this->scheduleUpdate();

    return true;
}

Sprite* MainScene::addFruit() {

    auto winSize = Director::getInstance()->getWinSize();
    // フルーツの種類を選択する
    int fruitType = rand() % static_cast<int>(FruitType::COUNT);

    std::string filename = StringUtils::format("fruit%d.png", fruitType);

    auto fruit = Sprite::create(filename);

    fruit->setTag(fruitType);

    auto fruitSize = fruit->getContentSize();

    float fruitXPos = rand() % static_cast<int>(winSize.width);

    fruit->setPosition(Vec2(fruitXPos, winSize.height - FRUIT_TOP_MERGIN - fruitSize.height / 2.0));
    this->addChild(fruit);
    _fruits.pushBack(fruit);

    // フルーツに動きをつける
    auto ground = Vec2(fruitXPos, 0);
    auto fall = MoveTo::create(FALLING_DURATION, ground);
    auto remove = CallFuncN::create([this](Node *n) {
        this->removeFruit(dynamic_cast<Sprite *>(n));
    });

    auto sequence = Sequence::create(fall, remove, NULL);

    fruit->runAction(sequence);

    return fruit;
}

bool MainScene::removeFruit(cocos2d::Sprite *fruit) {
    if (_fruits.contains(fruit)) {
        // _fruits配列から削除する
        _fruits.eraseObject(fruit);
        // 親ノードから削除する
        fruit->removeFromParent();
        return true;
    }
    return false;
}

void MainScene::update(float dt) {

    int random = rand() % FRUIT_SPAWN_RATE;
    if (random == 0) {
        this->addFruit();
    }
}
