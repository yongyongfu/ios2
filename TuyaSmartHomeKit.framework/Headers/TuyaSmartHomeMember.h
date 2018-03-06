//
//  TuyaSmartHomeMember.h
//  TuyaSmartKit
//
//  Created by 冯晓 on 2017/12/18.
//  Copyright © 2017年 Tuya. All rights reserved.
//

#import <Foundation/Foundation.h>

@interface TuyaSmartHomeMember : NSObject

/**
 获取家庭成员对象
 
 @param memberId
 */
+ (instancetype)memberWithMemberId:(long long)memberId;

- (instancetype)init NS_UNAVAILABLE;

/**
 *  修改家庭成员信息
 *
 *  @param name        备注名字
 *  @param isAdmin     是否是管理员
 *  @param success     操作成功回调
 *  @param failure     操作失败回调
 */
- (void)updateMemberWithName:(NSString *)name
                     isAdmin:(BOOL)isAdmin
                     success:(TYSuccessHandler)success
                     failure:(TYFailureError)failure;

@end
