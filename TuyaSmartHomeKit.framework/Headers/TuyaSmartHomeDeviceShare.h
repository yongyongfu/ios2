//
//  TuyaSmartHomeDeviceShare.h
//  TuyaSmartKit
//
//  Created by 冯晓 on 2018/1/9.
//  Copyright © 2018年 Tuya. All rights reserved.
//

#import <UIKit/UIKit.h>
#import "TuyaSmartShareMemberModel.h"
#import "TuyaSmartShareMemberDetailModel.h"
#import "TuyaSmartReceiveMemberDetailModel.h"
#import "TuyaSmartReceivedShareUserModel.h"
#import "TuyaSmartShareDeviceModel.h"


///  共享设备相关功能 （基于家庭的设备维度的共享）
@interface TuyaSmartHomeDeviceShare : NSObject


/**
 添加共享
 
 @param homeId      家庭Id
 @param countryCode 国家码
 @param userAccount 账号
 @param devId       设备Id
 @param success     操作成功回调
 @param failure     操作失败回调
 */
- (void)addShareWithHomeId:(long long)homeId
               countryCode:(NSString *)countryCode
               userAccount:(NSString *)userAccount
                    devIds:(NSArray <NSString *> *)devIds
                   success:(void(^)(TuyaSmartShareMemberModel *model))success
                   failure:(TYFailureError)failure;


/**
 添加共享 （新增，不覆盖旧的分享）
 
 @param memberId    共享成员ID
 @param devIds      设备列表
 @param success     操作成功回调
 @param failure     操作失败回调
 */
- (void)addShareWithMemberId:(NSInteger)memberId
                      devIds:(NSArray <NSString *> *)devIds
                     success:(TYSuccessHandler)success
                     failure:(TYFailureError)failure;


/**
 获取家庭下所有主动共享的用户列表
 
 @param homeId  家庭Id
 @param success 操作成功回调
 @param failure 操作失败回调
 */
- (void)getShareMemberListWithHomeId:(long long)homeId
                             success:(void(^)(NSArray<TuyaSmartShareMemberModel *> *list))success
                             failure:(TYFailureError)failure;


/**
 获取所有收到共享的用户列表
 
 @param success 操作成功回调
 @param failure 操作失败回调
 */
- (void)getReceiveMemberListWithSuccess:(void(^)(NSArray<TuyaSmartShareMemberModel *> *list))success
                                failure:(TYFailureError)failure;


/**
 获取单个 主动共享 的用户共享数据
 
 @param memberId 共享成员ID
 @param success  操作成功回调
 @param failure  操作失败回调
 */
- (void)getShareMemberDetailWithMemberId:(NSInteger)memberId
                                 success:(void(^)(TuyaSmartShareMemberDetailModel *model))success
                                 failure:(TYFailureError)failure;


/**
 获取单个 收到共享 的用户共享数据
 
 @param memberId    共享成员ID
 @param success     操作成功回调
 @param failure     操作失败回调
 */
- (void)getReceiveMemberDetailWithMemberId:(NSInteger)memberId
                                   success:(void(^)(TuyaSmartReceiveMemberDetailModel *model))success
                                   failure:(TYFailureError)failure;


/**
 删除主动共享者
 
 @param memberId 共享成员ID
 @param success  操作成功回调
 @param failure  操作失败回调
 */
- (void)removeShareMemberWithMemberId:(NSInteger)memberId
                              success:(TYSuccessHandler)success
                              failure:(TYFailureError)failure;


/**
 删除收到共享者
 
 @param memberId 共享成员ID
 @param success  操作成功回调
 @param failure  操作失败回调
 */
- (void)removeReceiveShareMemberWithMemberId:(NSInteger)memberId
                                     success:(TYSuccessHandler)success
                                     failure:(TYFailureError)failure;


/**
 修改某个主动共享用户的昵称
 
 @param memberId 共享成员ID
 @param name     昵称
 @param success  操作成功回调
 @param failure  操作失败回调
 */
- (void)renameShareMemberNameWithMemberId:(NSInteger)memberId
                                     name:(NSString *)name
                                  success:(TYSuccessHandler)success
                                  failure:(TYFailureError)failure;


/**
 修改收到共享者的昵称
 
 @param memberId 共享成员ID
 @param name     昵称
 @param success  操作成功回调
 @param failure  操作失败回调
 */
- (void)renameReceiveShareMemberNameWithMemberId:(NSInteger)memberId
                                            name:(NSString *)name
                                         success:(TYSuccessHandler)success
                                         failure:(TYFailureError)failure;


#pragma mark - 单设备共享操作

/**
 单设备添加共享
 
 @param homeId      家庭Id
 @param countryCode 国家码
 @param userAccount 账号
 @param devIds      设备数组
 @param success     操作成功回调
 @param failure     操作失败回调
 */
- (void)addDeviceShareWithHomeId:(long long)homeId
                     countryCode:(NSString *)countryCode
                     userAccount:(NSString *)userAccount
                           devId:(NSString *)devId
                         success:(void(^)(TuyaSmartShareMemberModel *model))success
                         failure:(TYFailureError)failure;


/**
 删除收到的共享设备
 
 @param devId   设备Id
 @param success 操作成功回调
 @param failure 操作失败回调
 */
- (void)removeReceiveDeviceShareWithDevId:(NSString *)devId
                                  success:(TYSuccessHandler)success
                                  failure:(TYFailureError)failure;


/**
 单设备删除共享
 
 @param memberId    共享成员ID
 @param devId       设备号
 @param success     操作成功回调
 @param failure     操作失败回调
 */
- (void)removeDeviceShareWithMemberId:(NSInteger)memberId
                                devId:(NSString *)devId
                              success:(TYSuccessHandler)success
                              failure:(TYFailureError)failure;


/**
 获取设备共享用户列表
 
 @param devId   设备号
 @param success 操作成功回调
 @param failure 操作失败回调
 */
- (void)getDeviceShareMemberListWithDevId:(NSString *)devId
                                  success:(void(^)(NSArray<TuyaSmartShareMemberModel *> *list))success
                                  failure:(TYFailureError)failure;


/**
 获取设备分享来自哪里
 
 @param devId   设备号
 @param success 操作成功回调
 @param failure 操作失败回调
 */
- (void)getShareInfoWithDevId:(NSString *)devId
                      success:(void(^)(TuyaSmartReceivedShareUserModel *model))success
                      failure:(TYFailureError)failure;


@end
