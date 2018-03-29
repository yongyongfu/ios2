//
//  TuyaSmartScene.h
//  TuyaSmartKit
//
//  Created by xuyongbo on 2017/9/4.
//  Copyright © 2017年 Tuya. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "TuyaSmartSceneModel.h"
#import "TuyaSmartSceneActionModel.h"
#import "TuyaSmartSceneConditionModel.h"

@interface TuyaSmartScene : NSObject

//自定义场景根据id初始化
+ (instancetype)sceneWithSceneId:(NSString *)sceneId;
- (instancetype)initWithSceneId:(NSString *)sceneId;

- (instancetype)init NS_UNAVAILABLE;

/**
 添加场景

 @param name            场景名称
 @param homeId          家庭Id
 @param background      场景背景图片
 @param showFirstPage   是否显示在首页
 @param conditionList   条件list
 @param actionList      任务list
 @param success         操作成功回调，返回场景
 @param failure         操作失败回调
 */
+ (void)addNewSceneWithName:(NSString *)name
                     homeId:(long long)homeId
                 background:(NSString *)background
              showFirstPage:(BOOL)showFirstPage
              conditionList:(NSArray<TuyaSmartSceneConditionModel*> *)conditionList
                 actionList:(NSArray<TuyaSmartSceneActionModel*> *)actionList
                    success:(void (^)(TuyaSmartSceneModel *sceneModel))success
                    failure:(TYFailureError)failure;


/**
 修改场景

 @param name            场景名称
 @param background      场景背景图片
 @param showFirstPage   是否显示在首页
 @param conditionList   条件list
 @param actionList      任务list
 @param success         操作成功回调
 @param failure         操作失败回调
 */
- (void)modifySceneWithName:(NSString *)name
                 background:(NSString *)background
              showFirstPage:(BOOL)showFirstPage
              conditionList:(NSArray<TuyaSmartSceneConditionModel*> *)conditionList
                 actionList:(NSArray<TuyaSmartSceneActionModel*> *)actionList
                    success:(TYSuccessHandler)success
                    failure:(TYFailureError)failure;


/**
 删除场景

 @param success 操作成功回调
 @param failure 操作失败回调
 */
- (void)deleteSceneWithSuccess:(TYSuccessHandler)success
                       failure:(TYFailureError)failure;


/**
 执行场景

 @param success 操作成功回调
 @param failure 操作失败回调
 */
- (void)executeSceneWithSuccess:(TYSuccessHandler)success
                        failure:(TYFailureError)failure;


/**
 失效场景
 
 @param success 操作成功回调
 @param failure 操作失败回调
 */
- (void)disableSceneWithSuccess:(TYSuccessHandler)success
                        failure:(TYFailureError)failure;


/**
 开启场景
 
 @param success 操作成功回调
 @param failure 操作失败回调
 */
- (void)enableSceneWithSuccess:(TYSuccessHandler)success
                       failure:(TYFailureError)failure;


/**
 取消操作
 */
- (void)cancelRequest;


@end
