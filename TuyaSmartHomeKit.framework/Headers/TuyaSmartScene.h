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

//默认场景根据code初始化
+ (instancetype)sceneWithSceneCode:(NSString *)sceneCode;
- (instancetype)initWithSceneCode:(NSString *)sceneCode;

- (instancetype)init NS_UNAVAILABLE;

/**
 添加场景

 @param name 场景名称
 @param condition 条件（目前支持一个条件）
 @param actionList 任务
 @param success 操作成功回调，返回场景
 @param failure 操作失败回调
 */
+ (void)addNewScene:(NSString *)name
          condition:(TuyaSmartSceneConditionModel *)condition
         actionList:(NSArray<TuyaSmartSceneActionModel*> *)actionList
            success:(void (^)(TuyaSmartSceneModel *sceneModel))success
            failure:(TYFailureError)failure;


+ (void)addNewScene:(NSString *)name
             homeId:(long long)homeId
         background:(NSString *)background
      showFirstPage:(BOOL)showFirstPage
      conditionList:(NSArray<TuyaSmartSceneConditionModel*> *)conditionList
         actionList:(NSArray<TuyaSmartSceneActionModel*> *)actionList
            success:(void (^)(TuyaSmartSceneModel *sceneModel))success
            failure:(TYFailureError)failure;

/**
 修改场景

 @param name 场景名称
 @param condition 条件（目前支持一个条件）
 @param actionList 任务
 @param success 操作成功回调
 @param failure 操作失败回调
 */
- (void)modifyScene:(NSString *)name
          condition:(TuyaSmartSceneConditionModel *)condition
         actionList:(NSArray<TuyaSmartSceneActionModel*> *)actionList
            success:(TYSuccessHandler)success
            failure:(TYFailureError)failure;

- (void)modifyScene:(NSString *)name
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
- (void)deleteScene:(TYSuccessHandler)success
            failure:(TYFailureError)failure;

/**
 删除默认场景
 
 @param success 操作成功回调
 @param failure 操作失败回调
 */
- (void)deleteDefaultScene:(TYSuccessHandler)success
                   failure:(TYFailureError)failure;

/**
 执行场景

 @param success 操作成功回调
 @param failure 操作失败回调
 */
- (void)executeScene:(TYSuccessHandler)success
             failure:(TYFailureError)failure;

/**
 失效场景
 
 @param success 操作成功回调
 @param failure 操作失败回调
 */
- (void)disableScene:(TYSuccessHandler)success
             failure:(TYFailureError)failure;

/**
 打开场景
 
 @param success 操作成功回调
 @param failure 操作失败回调
 */
- (void)enableScene:(TYSuccessHandler)success
             failure:(TYFailureError)failure;

/**
 取消操作
 */
- (void)cancelRequest;

@end
