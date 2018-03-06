//
//  TYBLEMeshManager.h
//  TuyaSmartKit
//
//  Created by XuChengcheng on 2017/7/26.
//  Copyright © 2017年 Tuya. All rights reserved.
//

#ifndef TuyaSmart_TYBLEMeshManager
#define TuyaSmart_TYBLEMeshManager

#import <Foundation/Foundation.h>
#import "TYBleMeshDeviceModel.h"
#import "TYBLEMeshCommand.h"

#define kInitMeshName @"out_of_mesh"

typedef NS_ENUM(NSInteger, TYBLEMeshOperationType) {
    TYBLEMeshOperationTypeNormal = 1,
    TYBLEMeshOperationTypeLogin,
    TYBLEMeshOperationTypeSet,
    TYBLEMeshOperationTypeCom,
    TYBLEMeshOperationTypeAutoLogin
};

typedef NS_ENUM(NSInteger, TYBLEMeshOperationStatus) {
    TYBLEMeshOperationStatusNormal = 1,
    TYBLEMeshOperationStatusScanSrvFinish,//完成扫描服务uuid
    TYBLEMeshOperationStatusScanCharFinish,//完成扫描特征
    TYBLEMeshOperationStatusLoginStart,
    TYBLEMeshOperationStatusLoginFinish,
    TYBLEMeshOperationStatusSetNameStart,
    TYBLEMeshOperationStatusSetPasswordStart,
    TYBLEMeshOperationStatusSetLtkStart,
    TYBLEMeshOperationStatusSetNetworkFinish,
    TYBLEMeshOperationStatusFireWareVersion
};

@class TYBLEMeshManager;
@protocol TYBLEMeshManagerDelegate <NSObject>

@optional

- (void)centralManagerStatusChange:(CBManagerState)status;
- (void)activeDeviceSuccessWithName:(NSString *)name deviceId:(NSString *)deviceId;
- (void)deviceAddGroupAddress:(uint32_t)address;

- (void)activeWifiDeviceWithName:(NSString *)name address:(NSInteger)address mac:(NSInteger)mac;
- (void)notifyCentralManagerDidDisconnectPeripheral;
- (void)notifyFirmwareWithVersion:(NSString *)version;
- (void)notifyLoginSuccessWithAddress:(uint32_t)address;

@end

@interface TYBLEMeshManager : NSObject

+ (instancetype)sharedInstance;

@property (nonatomic, assign) CBManagerState centerState;
@property (nonatomic, assign) BOOL isLogin;
@property (nonatomic, assign) BOOL isWifiDevice;
@property (nonatomic, assign) uint32_t wifiAddress;
@property (nonatomic, assign) uint32_t otaAddress;
@property (nonatomic, strong) NSString *ssid;
@property (nonatomic, strong) NSString *password;
@property (nonatomic, strong) NSString *token;
@property (nonatomic, strong) NSString *authKey;
@property (nonatomic, strong) NSString *uuid;
@property (nonatomic, strong) NSString *productId;
@property (nonatomic, strong) NSString *version;

@property (nonatomic, weak) id<TYBLEMeshManagerDelegate> delegate;

- (void)startScanWithName:(NSString *)name pwd:(NSString *)pwd active:(BOOL)active wifiAddress:(uint32_t)wifiAddress otaAddress:(uint32_t)otaAddress;

- (void)activeMeshDevice;
- (void)reConnectDevice;
- (void)getLightAllStatus;
- (BOOL)isConnected;
- (void)getDeviceStatusAllWithAddress:(uint32_t)address type:(NSString *)type;
- (void)getDeviceCountdownWithAddress:(uint32_t)address type:(NSString *)type;

- (void)stopScan;
- (void)clearScanData;

// command
- (void)sendCommand:(TYBLEMeshCommand *)command;

- (void)getSensorStateWithAddress:(uint32_t)deviceAddress
                              dps:(NSArray *)dps
                             type:(NSString *)type;
// group
- (void)addDeviceAddress:(uint32_t)deviceAddress type:(NSString *)type groupAddress:(uint32_t)groupAddress;
- (void)deleteDeviceAddress:(uint32_t)deviceAddress type:(NSString *)type groupAddress:(uint32_t)groupAddress;
- (void)deleteGroupAddress:(uint32_t)groupAddress type:(NSString *)type;

// kick out
- (void)kickoutLightWithAddress:(uint32_t)address type:(NSString *)type;

// get device group address
- (void)getGroupAddressWithDeviceAddress:(uint32_t)deviceAddress type:(NSString *)type;
- (void)getDevicesAddressWithGroupAddress:(uint32_t)groupAddress type:(NSString *)type;

// get raw data string
- (NSString *)rawDataDeleteGroupAddress:(uint32_t)groupAddress type:(NSString *)type;
- (NSString *)rawDataDeleteDeviceAddress:(uint32_t)deviceAddress groupAddress:(uint32_t)groupAddress type:(NSString *)type;
- (NSString *)rawDataAddDeviceAddress:(uint32_t)deviceAddress groupAddress:(uint32_t)groupAddress type:(NSString *)type;
- (NSString *)rawDataKickoutLightWithAddress:(uint32_t)address type:(NSString *)type;
- (NSString *)rawDataGetStatusAllWithAddress:(uint32_t)address type:(NSString *)type;
- (NSString *)rawDataCountDownWithAddress:(uint32_t)address type:(NSString *)type;

- (void)startConfigWiFiWithSsid:(NSString *)ssid pwd:(NSString *)pwd token:(NSString *)token;

- (void)readFirmwareFeature;

// ota
- (void)sendOTAPackWithAddress:(NSInteger)address version:(NSString *)version otaData:(NSData *)otaData success:(TYSuccessHandler)success failure:(TYFailureHandler)failure;

@end

#endif
