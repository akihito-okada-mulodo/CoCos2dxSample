//
//  MainScene.h
//  KawazCatch
//
//  Created by giginet on 5/15/14.
//
//

#ifndef __KawazCatch__MainScene__
#define __KawazCatch__MainScene__

#include "cocos2d.h"

class MainScene: public cocos2d::Layer {
protected:

    MainScene();
    virtual ~MainScene();
    bool init() override;

public:

    static cocos2d::Scene* createScene();

    void update(float dt);

    CREATE_FUNC(MainScene);

    CC_SYNTHESIZE_RETAIN(cocos2d::Sprite *, _player, Player);

    CC_SYNTHESIZE(cocos2d::Vector<cocos2d::Sprite *>, _fruits, Fruits);

private:
    /// フルーツの種類を表します
    enum class FruitType {
        /// リンゴ
        APPLE,
        /// ぶどう
        GRAPE,
        /// みかん
        ORANGE,
        /// バナナ
        BANANA,
        /// さくらんぼ
        CHERRY,
        /// 金のリンゴ
        GOLDEN,
        /// 爆弾
        BOMB,
        /// 最大値
        COUNT
    };

    /** 画面にフルーツを新たに配置して、それを返します
     *  @return 新たに作成されたフルーツ
     */
    cocos2d::Sprite* addFruit();

    /** マップからフルーツを取り除きます
     *  @param  fruit 削除するフルーツ
     *  @return 正しく削除されたか
     */
    bool removeFruit(cocos2d::Sprite *fruit);
};

#endif /* defined(__KawazCatch__MainScene__) */
