//
//  TuyaSmartGroupModel.h
//  TuyaSmartPublic
//
//  Created by 高森 on 16/4/20.
//  Copyright © 2016年 Tuya. All rights reserved.
//

#ifndef TuyaSmart_TuyaSmartGroupModel
#define TuyaSmart_TuyaSmartGroupModel

typedef enum : NSUInteger {
    TuyaSmartGroupTypeWifi = 0,
    TuyaSmartGroupTypeMesh,
} TuyaSmartGroupType;

#import "TYModel.h"
#import "TuyaSmartDevice.h"

@interface TuyaSmartGroupModel : TYModel

//群组唯一标识符
@property (nonatomic, strong) NSString  *groupId;

//产品唯一标识符
@property (nonatomic, strong) NSString  *productId;

//群组创建时间
@property (nonatomic, assign) long long    time;

//群组名称
@property (nonatomic, strong) NSString  *name;

//群组iconUrl
@property (nonatomic, strong) NSString  *iconUrl;

// 群组类型
@property (nonatomic, assign) TuyaSmartGroupType  type;

//设备在线状态
@property (nonatomic, assign) BOOL      isOnline;

//群组的本地短地址
@property (nonatomic, strong) NSString     *localId;

//大小类
@property (nonatomic, strong) NSString     *pcc;

// mesh
@property (nonatomic, strong) NSString     *meshId;

@property (nonatomic, assign) long long    homeId;

@property (nonatomic, assign) long long    roomId;

//主设备
@property (nonatomic, strong) TuyaSmartDeviceModel *mainDevice;

// 设备列表
@property (nonatomic, strong) NSArray<TuyaSmartDeviceModel *> *deviceList;


@end

#endif
