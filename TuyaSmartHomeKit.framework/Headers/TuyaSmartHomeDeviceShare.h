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


///  共享设备相关功能 （基于家庭的设备维度的共享）
@interface TuyaSmartHomeDeviceShare : NSObject


/**
 用户下的多设备分享启用 （全量覆盖）
 
 @param memberId    共享成员ID
 @param devIds      设备列表
 @param success     操作成功回调
 @param failure     操作失败回调
 */
- (void)enableMultiDevShareWithMemberId:(NSInteger)memberId
                                 devIds:(NSArray <NSString *> *)devIds
                                success:(TYSuccessHandler)success
                                failure:(TYFailureError)failure;



/**
 用户下的设备分享启用
 
 @param memberId    共享成员ID
 @param devId       设备号
 @param success     操作成功回调
 @param failure     操作失败回调
 */
- (void)enableDevShareWithMemberId:(NSInteger)memberId
                             devId:(NSString *)devId
                           success:(TYSuccessHandler)success
                           failure:(TYFailureError)failure;


/**
 用户下的设备分享关闭
 
 @param memberId    共享成员ID
 @param devId       设备号
 @param success     操作成功回调
 @param failure     操作失败回调
 */
- (void)disableDevShareWithMemberId:(NSInteger)memberId
                              devId:(NSString *)devId
                            success:(TYSuccessHandler)success
                            failure:(TYFailureError)failure;



/**
 删除收到的共享的设备
 
 @param devId   设备号
 @param success 操作成功回调
 @param failure 操作失败回调
 */
- (void)removeReceivedDevShareWithDevId:(NSString *)devId
                                success:(TYSuccessHandler)success
                                failure:(TYFailureError)failure;



/**
 添加单个设备到共享用户 (增量)
 
 @param homeId      家庭Id
 @param countryCode 国家码
 @param userAccount 账号
 @param devIds      设备数组
 @param success     操作成功回调
 @param failure     操作失败回调
 */
- (void)addDevsToMemberWithHomeId:(long long)homeId
                      countryCode:(NSString *)countryCode
                      userAccount:(NSString *)userAccount
                           devIds:(NSArray *)devIds
                          success:(void(^)(TuyaSmartShareMemberModel *model))success
                          failure:(TYFailureError)failure;


/**
 获取单设备共享用户列表(面板中体现)
 
 @param devId   设备号
 @param success 操作成功回调
 @param failure 操作失败回调
 */
- (void)getDevShareUserListWithDevId:(NSString *)devId
                             success:(void(^)(NSArray<TuyaSmartShareMemberModel *> *list))success
                             failure:(TYFailureError)failure;



/**
 全量分享，选中的分享，没选中的不分享
 
 @param homeId      家庭Id
 @param countryCode 国家码
 @param userAccount 账号
 @param devIds      设备数组
 @param autoSharing 是否开启新添加设备是否自动共享
 @param success     操作成功回调
 @param failure     操作失败回调
 */
- (void)addShareWithHomeId:(long long)homeId
               countryCode:(NSString *)countryCode
               userAccount:(NSString *)userAccount
                    devIds:(NSArray *)devIds
               autoSharing:(BOOL)autoSharing
                   success:(void(^)(TuyaSmartShareMemberModel *model))success
                   failure:(TYFailureError)failure;


/**
 获取单个主动共享的用户共享数据
 
 @param memberId 共享成员ID
 @param success  操作成功回调
 @param failure  操作失败回调
 */
- (void)getUserShareInfoWithMemberId:(NSInteger)memberId
                             success:(void(^)(TuyaSmartShareMemberDetailModel *model))success
                             failure:(TYFailureError)failure;



/**
 获取单个收到共享的用户共享数据
 
 @param memberId    共享成员ID
 @param success     操作成功回调
 @param failure     操作失败回调
 */
- (void)getReceivedUserShareInfoWithMemberId:(NSInteger)memberId
                                     success:(void(^)(TuyaSmartReceiveMemberDetailModel *model))success
                                     failure:(TYFailureError)failure;



/**
 获取当前用户主动共享的用户列表
 
 @param homeId  家庭Id
 @param success 操作成功回调
 @param failure 操作失败回调
 */
- (void)getUserShareListWithHomeId:(long long)homeId
                           success:(void(^)(NSArray<TuyaSmartShareMemberModel *> *list))success
                           failure:(TYFailureError)failure;




/**
 获取所有收到共享的用户列表
 
 @param success 操作成功回调
 @param failure 操作失败回调
 */
- (void)getShareReceivedUserListWithSuccess:(void(^)(NSArray<TuyaSmartShareMemberModel *> *list))success
                                    failure:(TYFailureError)failure;




/**
 获取被分享设备的用户信息
 
 @param devId 设备号
 @param success 操作成功回调
 @param failure 操作失败回调
 */
- (void)getShareDevFromInfoWithDevId:(NSString *)devId
                             success:(void(^)(TuyaSmartReceivedShareUserModel *model))success
                             failure:(TYFailureError)failure;


/**
 修改某个主动共享用户的昵称
 
 @param memberId 共享成员ID
 @param name 昵称
 @param success 操作成功回调
 @param failure 操作失败回调
 */
- (void)renameShareNicknameWithMemberId:(NSInteger)memberId
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
- (void)renameReceivedShareNicknameWithMemberId:(NSInteger)memberId
                                           name:(NSString *)name
                                        success:(TYSuccessHandler)success
                                        failure:(TYFailureError)failure;


/**
 删除主动共享者
 
 @param memberId 共享成员ID
 @param success  操作成功回调
 @param failure  操作失败回调
 */
- (void)removeUserShareWithMemberId:(NSInteger)memberId
                            success:(TYSuccessHandler)success
                            failure:(TYFailureError)failure;


/**
 删除收到共享者
 
 @param memberId 共享成员ID
 @param success  操作成功回调
 @param failure  操作失败回调
 */
- (void)removeReceivedUserShareWithMemberId:(NSInteger)memberId
                                    success:(TYSuccessHandler)success
                                    failure:(TYFailureError)failure;


@end
