//
//  TuyaFirmwareUpgradeInfo.h
//  TuyaSmartKit
//
//  Created by fengyu on 15/9/15.
//  Copyright (c) 2015年 Tuya. All rights reserved.
//

#ifndef TuyaSmart_TuyaSmartFirmwareUpgradeModel
#define TuyaSmart_TuyaSmartFirmwareUpgradeModel

#import "TYModel.h"

@interface TuyaSmartFirmwareUpgradeModel : TYModel

//升级文案
@property (nonatomic, strong) NSString  *desc;

//0:无新版本 1:有新版本 2:在升级中
@property (nonatomic, assign) NSInteger upgradeStatus;

//新版本使用的固件版本
@property (nonatomic, strong) NSString  *version;

//当前在使用的固件版本
@property (nonatomic, strong) NSString  *currentVersion;

//升级超时时间（秒）
@property (nonatomic, assign) NSInteger timeout;

//0:app提醒升级 2:app强制升级 3:检测升级
@property (nonatomic, assign) NSInteger upgradeType;

// WIFI(0, "WiFi"),BLUETOOTH(1, "蓝牙"),GPRS(2, "GPRS"),ZIGBEE(3, "zigbee"),INFRARED(4, "infrared"),MCU(9,"MCU");
@property (nonatomic, assign) NSInteger type;

//如果是蓝牙设备的升级，需要使用以下两个字段

//固件的下载URL
@property (nonatomic, strong) NSString *url;

//固件的md5
@property (nonatomic, strong) NSString *md5;

//固件包的size
@property (nonatomic, strong) NSString *fileSize;


@end

#endif
