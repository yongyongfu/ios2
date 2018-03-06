title: iOS SDK 开发指南
subtitle: iOS SDK 开发指南 
published: true    
---

# 涂鸦智能iOS SDK接入指南

## 功能概述

涂鸦智能APP SDK提供了与硬件设备、涂鸦云通讯的接口封装，加速应用开发过程，主要包括了以下功能：

- 硬件设备相关（配网、控制、状态上报、定时任务、群组、固件升级、共享）
- 账户体系（手机号、邮箱的注册、登录、重置密码等通用的账户功能）
- 涂鸦云HTTP API接口封装 (参见[涂鸦云api调用](https://docs.tuya.com/cn/cloudapi/appAPI/index.html)）

## 准备工作

### 注册开发者账号
前往 [涂鸦智能开发平台](https://developer.tuya.com) 注册开发者账号、创建产品、创建功能点等，具体流程请参考[接入流程](https://docs.tuya.com/cn/overview/dev-process.html)

### 获取iOS的App ID和App Secret
前往 开发平台 - 应用管理 - 新建应用 获取`iOS`的`App ID`、`App Secret`初始化SDK

![cmd-markdown-logo](http://images.airtakeapp.com/smart_res/developer_default/sdk_zh.jpeg) 

### 联调方式
- 通过硬件控制板 进行真机调试
- 通过开发平台 - 模拟设备 进行模拟调试

### SDK Demo
SDK Demo 是一个完整的APP，包含了登录、注册、共享、配网、控制等主流程，可参看Demo代码进行开发。 [下载地址](https://github.com/TuyaInc/tuyasmart_ios_sdk)

## 集成SDK

### 使用CocoaPods快速集成（SDK最低支持系统版本8.0）

在`Podfile`文件中添加以下内容：

```ruby
platform :ios, '8.0'

target 'Your_Project_Name' do
	pod "TuyaSmartKit", :git => "https://github.com/TuyaInc/tuyasmart_ios_sdk.git"
end
```

![Podfile](./images/ios-sdk-podfile.png)

然后在项目根目录下执行`pod install`命令进行集成。

_CocoaPods的使用请参考：[CocoaPods Guides](https://guides.cocoapods.org/)_
_CocoaPods建议更新至最新版本_

### 初始化SDK

在项目的`PrefixHeader.pch`文件添加以下内容：

```objc
#import <TuyaSmartKit/TuyaSmartKit.h>
```

打开`AppDelegate.m`文件，在`[AppDelegate application:didFinishLaunchingWithOptions:]`方法中使用开发平台获取的`App ID`和`App Secret`初始化SDK：

```objc
[[TuyaSmartSDK sharedInstance] startWithAppKey:<#your_app_key#> secretKey:<#your_secret_key#>];
```

至此，准备工作已经全部完毕，可以开始App开发啦。

### 示例代码约定

在以下示例代码中，如果没有特殊说明，所有实例均位于`ViewController`类的实现文件中

```objc
@interface ViewController : UIViewController

@end

@implementation ViewController

// 所有示例代码均位于此处

@end
```

对于像`self.prop`这样的引用，我们约定`prop`属性在`ViewController`类中已经有了正确的实现。例如：

```objc
self.device = [[TuyaSmartDevice alloc] initWithDeviceId:@"your_device_id"];
```
若想让它正确执行，需要在当前的`ViewController`类中添加一个 `TuyaSmartDevice`属性：

```objc
@property (nonatomic, strong) TuyaSmartDevice *device;
```

以此类推。

### 错误信息返回的约定
SDK使用中，接口返回的错误信息通过`error.localizedDescription`来获取

```objc
[[TuyaSmartUser sharedInstance] sendVerifyCode:@"your_country_code" phoneNumber:@"your_phone_number" type:0 success:^{
	NSLog(@"sendVerifyCode success");
} failure:^(NSError *error) {
    //输出具体的错误信息
	NSLog(@"error message: %@", error.localizedDescription);
}];
```

### 通用参数的设置
给SDK传递公共参数，现在支持`latitude`(纬度)、`longitude`(经度)

如需收集设备的位置信息，需要上报经纬度：

```objc 
[[TuyaSmartSDK sharedInstance] setValue:<#latitude#> forKey:@"latitude"];
[[TuyaSmartSDK sharedInstance] setValue:<#longitude#> forKey:@"longitude"];
```

## 用户管理

涂鸦云支持多种用户体系：手机、邮箱、UID。其中手机支持验证码登录和密码登录两种方式，每种体系的注册登录会在后面单独介绍。

在注册登录方法中，需要提供`countryCode`参数（国家区号），用于就近选择涂鸦云的可用区。各个可用区的数据是相互独立的，因此在`中国大陆（86）`注册的账号，在`美国(1)`无法使用（用户不存在）。

可用区相关概念请查看：[涂鸦云-可用区](https://docs.tuya.com/cn/cloudapi/api/cloudapi/)

用户相关的所有功能对应`TuyaSmartUser`类（单例）。

### 用户注册

_注：注册方法调用成功后，就可以正常使用SDK的所有功能了（注册成功即为登录成功），不需要再次调用登录方法。_

#### 手机注册

手机注册需要以下两个步骤：

- 发送验证码到手机

```objc
- (void)sendVerifyCode {
	[[TuyaSmartUser sharedInstance] sendVerifyCode:@"your_country_code" phoneNumber:@"your_phone_number" type:1 success:^{
		NSLog(@"sendVerifyCode success");
	} failure:^(NSError *error) {
		NSLog(@"sendVerifyCode failure: %@", error);
	}];
}
```

- 手机收到验证码后，使用验证码注册

```objc
- (void)registerByPhone {
	[[TuyaSmartUser sharedInstance] registerByPhone:@"your_country_code" phoneNumber:@"your_phone_number" password:@"your_password" code:@"verify_code" success:^{
		NSLog(@"register success");
	} failure:^(NSError *error) {
		NSLog(@"register failure: %@", error);
	}];
}
```

#### 邮箱注册

邮箱注册不需要发送验证码，直接注册即可：

```objc
- (void)registerByEmail {
	[[TuyaSmartUser sharedInstance] registerByEmail:@"your_country_code" email:@"your_email" password:@"your_password" success:^{
		NSLog(@"register success");
	} failure:^(NSError *error) {
		NSLog(@"register failure: %@", error);
	}];
}
```

#### UID注册

涂鸦智能提供UID登陆体系。如果客户自有用户体系，那么可以通过UID登陆体系，接入我们的SDK。客户需要自己保证UID的唯一性。

```objc
- (void)registerByUid {
	[[TuyaSmartUser sharedInstance] registerByUid:@"your_unique_id" password:@"your_password" countryCode:@"your_country_code" success:^{
	    NSLog(@"register success");
	} failure:^(NSError *error) {
	    NSLog(@"register failure: %@", error);
	}];
}
```

### 用户登录

用户登录接口调用成功之后，SDK会将用户Session储存在本地，下次启动APP时即默认已经登录，不需要再次登录。

长期未使用的情况下Session会失效，因此需要对Session过期的通知进行处理，提示用户重新登录。参见[Session过期的处理](#session-invalid)

#### 手机登录

手机登录有两种方式：验证码登录（无需注册，直接可以登录），密码登录（需要注册）

##### 验证码登录（无需注册，直接可以登录）

手机验证码登录的流程和手机注册类似：

- 发送验证码：

```objc
- (void)sendVerifyCode {
	[[TuyaSmartUser sharedInstance] sendVerifyCode:@"your_country_code" phoneNumber:@"your_phone_number" type:0 success:^{
		NSLog(@"sendVerifyCode success");
	} failure:^(NSError *error) {
		NSLog(@"sendVerifyCode failure: %@", error);
	}];
}
```

- 登录:

```objc
- (void)loginByPhoneAndCode {
	[[TuyaSmartUser sharedInstance] login:@"your_country_code" phoneNumber:@"your_phone_number" code:@"verify_code" success:^{
		NSLog(@"login success");
	} failure:^(NSError *error) {
		NSLog(@"login failure: %@", error);
	}];
}
```

#### 密码登录（需要注册）

```objc
- (void)loginByPhoneAndPassword {
	[[TuyaSmartUser sharedInstance] loginByPhone:@"your_country_code" phoneNumber:@"your_phone_number" password:@"your_password" success:^{
		NSLog(@"login success");
	} failure:^(NSError *error) {
		NSLog(@"login failure: %@", error);
	}];
}
```

#### 邮箱登录

```objc
- (void)loginByEmail {
	[[TuyaSmartUser sharedInstance] loginByEmail:@"your_country_code" email:@"your_email" password:@"your_password" success:^{
		NSLog(@"login success");
	} failure:^(NSError *error) {
		NSLog(@"login failure: %@", error);
	}];
}
```

#### UID登录

```objc
- (void)loginByUid {
	[[TuyaSmartUser sharedInstance] loginByUid:@"your_unique_id" password:@"your_password" countryCode:@"your_country_code" success:^{
		NSLog(@"login success");
	} failure:^(NSError *error) {
		NSLog(@"login failure: %@", error);
	}];
}
```


### 第三方登录
需要在 `涂鸦开发者平台` - `应用开发` - `第三方登录` 配置对应的`AppID`和`AppSecret`; 
客户端按照各平台要求进行开发，获取到对应的code之后，调用tuyaSDK对应的登录接口。

#### 微信登录
```objc
- (void)loginByWechat {
  	/**
	 *  微信登录
	 *
	 *  @param countryCode 国家区号
	 *  @param code 微信授权登录获取的code
	 *  @param success 操作成功回调
	 *  @param failure 操作失败回调
	 */
    [[TuyaSmartUser sharedInstance] loginByWechat:@"your_country_code" code:@"wechat_code" success:^{
        NSLog(@"login success");
    } failure:^(NSError *error) {
		NSLog(@"login failure: %@", error);
    }];
}

```

#### QQ登录
```objc
- (void)loginByQQ {
    /**
	 *  QQ登录
	 *
	 *  @param countryCode 国家区号
	 *  @param userId QQ授权登录获取的userId
	 *  @param accessToken QQ授权登录获取的accessToken
	 *  @param success 操作成功回调
	 *  @param failure 操作失败回调
	 */
    [[TuyaSmartUser sharedInstance] loginByQQ:@"your_country_code" openId:@"qq_open_id" accessToken:@"access_token" success:^{
        NSLog(@"login success");
    } failure:^(NSError *error) {
        NSLog(@"login failure: %@", error);
    }];
 
}

```


#### Facebook登录
```objc
- (void)loginByFacebook {
	/**
	 *  facebook登录
	 *
	 *  @param countryCode 国家区号
	 *  @param token facebook授权登录获取的token
	 *  @param success 操作成功回调
	 *  @param failure 操作失败回调
	 */
    [[TuyaSmartUser sharedInstance] loginByFacebook:@"your_country_code" token:@"facebook_token" success:^{
        NSLog(@"login success");
    } failure:^(NSError *error) {
        NSLog(@"login failure: %@", error);
    }];
}

```


#### Twitter登录
```objc

- (void)loginByTwitter {
	/**
	 *  twitter登录
	 *
	 *  @param countryCode 国家区号
	 *  @param key twitter授权登录获取的key
	 *  @param secret twitter授权登录获取的secret
	 *  @param success 操作成功回调
	 *  @param failure 操作失败回调
	 */
    [[TuyaSmartUser sharedInstance] loginByTwitter:@"your_country_code" key:@"twitter_key" secret:@"twitter_secret" success:^{
        NSLog(@"login success");
    } failure:^(NSError *error) {
        NSLog(@"login failure: %@", error);
    }];
   
}
```

### 4.3 用户重置密码

#### 手机号重置密码

手机号重置密码流程和注册流程类似：

- 发送验证码：

```objc
- (void)sendVerifyCode {
	[TuyaSmartUser sharedInstance] sendVerifyCode:@"your_country_code" phoneNumber:@"your_phone_number" type:2 success:^{
		NSLog(@"sendVerifyCode success");
	} failure:^(NSError *error) {
		NSLog(@"sendVerifyCode failure: %@", error);
	}];
}
```

- 重置密码：

```objc
- (void)resetPasswordByPhone {
	[TuyaSmartUser sharedInstance] resetPasswordByPhone:@"your_country_code" phoneNumber:@"your_phone_number" newPassword:@"your_password" code:@"verify_code" success:^{
		NSLog(@"resetPasswordByPhone success");
	} failure:^(NSError *error) {
		NSLog(@"resetPasswordByPhone failure: %@", error);
	}];
}
```

#### 邮箱重置密码

邮箱重置密码需要两个步骤：

- 发送验证码到邮箱

```objc
- (void)sendVerifyCodeByEmail {
	[TuyaSmartUser sharedInstance] sendVerifyCodeByEmail:@"your_country_code" email:@"your_email" success:^{
		NSLog(@"sendVerifyCodeByEmail success");
	} failure:^(NSError *error) {
		NSLog(@"sendVerifyCodeByEmail failure: %@", error);
	}];
}
```

- 收到验证码后，使用验证码重置密码

```objc
- (void)resetPasswordByEmail {
	[TuyaSmartUser sharedInstance] resetPasswordByEmail:@"your_country_code" email:@"your_email" newPassword:@"your_password" code:@"verify_code" success:^{
		NSLog(@"resetPasswordByEmail success");
	} failure:^(NSError *error) {
		NSLog(@"resetPasswordByEmail failure: %@", error);
	}];
}
```

#### UID重置密码

uid重置密码不需要验证码

```objc
- (void)resetPasswordByUid {
	[TuyaSmartUser sharedInstance] resetPasswordByUid:@"uid" newPassword:@"your_password" countryCode:@"your_country_code" success:^{
		NSLog(@"resetPasswordByUid success");
	} failure:^(NSError *error) {
		NSLog(@"resetPasswordByUid failure: %@", error);
	}];
}
```

### <span id='sync-device'>更新用户设备列表</span>

使用`[TuyaSmartUser syncDeviceWithCloud]`方法会更新当前用户的设备列表`deviceArray`和群组列表`groupList`。


```objc
- (void)reloadDeviceList {
	[[TuyaSmartUser sharedInstance] syncDeviceWithCloud:^{
	    NSLog(@"syncDeviceWithCloud success");
	    NSLog(@"deviceArray: %@", [TuyaSmartUser sharedInstance].deviceArray);
	    NSLog(@"groupList: %@", [TuyaSmartUser sharedInstance].groupList);
	} failure:^{
	    NSLog(@"syncDeviceWithCloud failure");
	}];
}
```

### 设备列表变更的处理
监听`TuyaSmartUserNotificationDeviceArrayChanged `通知，在设备列表`[TuyaSmartUser sharedInstance].deviceArray`数据有变更的时候，会接收到通知。

```objc
//注册通知
- (instancetype)init {
    if (self = [super init]) {
		[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(reloadData) name: TuyaSmartUserNotificationDeviceArrayChanged object:nil];
    }
    return self;
}

- (void) reloadData {
	//可以在这里刷新UI
}

- dealloc {
	[[NSNotificationCenter defaultCenter] removeObserver:self];
}

```



### 修改昵称

```objc
- (void)modifyNickname:(NSString *)nickname {
	[[TuyaSmartUser sharedInstance] updateNickname:nickname success:^{
		NSLog(@"updateNickname success");
	} failure:^(NSError *error) {
		NSLog(@"updateNickname failure: %@", error);
	}];
}
```

### 登出

```objc
- (void)loginOut {
	[TuyaSmartUser sharedInstance] loginOut:^{
		NSLog(@"logOut success");
	} failure:^(NSError *error) {
		NSLog(@"logOut failure: %@", error);
	}];
}
```

### <span id='session-invalid'>Session过期的处理</span>

长期未登录的账号，在访问服务端接口的时候会返回Session过期的错误，需要监听`TuyaSmartUserNotificationUserSessionInvalid`通知，跳转至登录页面重新登录。

```objc

- (void)loadNotification {
	[[NSNotificationCenter defaultCenter] addObserver:self selector:@selector(sessionInvalid) name:TuyaSmartUserNotificationUserSessionInvalid object:nil];
}

- (void)sessionInvalid {
	if ([[TuyaSmartUser sharedInstance] isLogin]) {
		NSLog(@"sessionInvalid");
		// 注销用户
		[[TuyaSmartUser sharedInstance] loginOut:nil failure:nil];
		
		//跳转至登录页面
		MyLoginViewController *vc = [[MyLoginViewController alloc] init];
		self.window.rootViewController = vc;
	    [self.window makeKeyAndVisible];
	}
}
```

## 设备配网

涂鸦硬件模块支持两种配网模式：快连模式（TLink，简称EZ模式）、热点模式（AP模式）。快连模式操作较为简便，建议在配网失败后，再使用热点模式作为备选方案。

**EZ模式配网流程：**

手机连上路由器WiFi -> 将设备切换至EZ模式 -> 手机开始配网（发送配置信息） -> 设备收到配置信息 -> 设备连上路由器WiFi -> 设备进行激活 -> 配网成功

**AP模式配网流程：**

将设备切换至AP模式 -> 手机连上设备的热点 -> 手机开始配网（发送配置信息） -> 设备收到配置信息 -> 设备自动关闭热点 -> 设备连上路由器WiFi -> 设备进行激活 -> 配网成功

配网相关的所有功能对应`TuyaSmartActivator`类（单例）。

### 准备工作

开始配网之前，SDK需要在联网状态下从涂鸦云获取配网Token，然后才可以开始EZ/AP模式配网。Token的有效期为5分钟，且配置成功后就会失效（再次配网需要重新获取）。

```
- (void)getToken {
	[[TuyaSmartActivator sharedInstance] getToken:^(NSString *token) {
		NSLog(@"getToken success: %@", token);
		// TODO: startConfigWiFi
	} failure:^(NSError *error) {
		NSLog(@"getToken failure: %@", error.localizedDescription);
	}];
}
```

### 开始配网

EZ模式配网：

```objc
- (void)startConfigWiFi:(NSString *)ssid password:(NSString *)password token:(NSString *)token {
	// 设置 TuyaSmartActivator 的 delegate，并实现 delegate 方法
	[TuyaSmartActivator sharedInstance].delegate = self;
	
	// 开始配网
	[[TuyaSmartActivator sharedInstance] startConfigWiFi:TYActivatorModeEZ ssid:ssid password:password token:token timeout:100];
}

#pragma mark - TuyaSmartActivatorDelegate
- (void)activator:(TuyaSmartActivator *)activator didReceiveDevice:(TuyaSmartDeviceModel *)deviceModel error:(NSError *)error {
	
	if (!error && deviceModel) {
		//配网成功
    }
    
    if (error) {
        //配网失败
    }	

}

```

AP模式配网与EZ类似，把`[TuyaSmartActivator startConfigWiFi:ssid:password:token:timeout:]`的第一个参数改为`TYActivatorModeAP`即可。注意`ssid`和`password`需要填写的是路由器的热点名称和密码，并不是设备的热点名称和密码。

### 停止配网

开始配网操作后，APP会持续广播配网信息（直到配网成功，或是超时）。如果需要中途取消操作或配网完成，需要调用`[TuyaSmartActivator stopConfigWiFi]`方法。

```objc
- (void)stopConfigWifi {
	[TuyaSmartActivator sharedInstance].delegate = nil;
	[[TuyaSmartActivator sharedInstance] stopConfigWiFi];
}
```

## 设备控制

设备控制相关的所有功能对应`TuyaSmartDevice`类，需要使用设备Id进行初始化。错误的设备Id可能会导致初始化失败，返回`nil`。

设备Id指的是`TuyaSmartDeviceModel`下的`devId`字段，可以从[用户设备列表](#sync-device)中获取。

### 更新设备信息

#### 更新单个设备信息

```objc
- (void)updateDeviceInfo {
	// self.device = [TuyaSmartDevice deviceWithDeviceId:@"your_device_id"];
	
	__weak typeof(self) weakSelf = self;
	[self.device syncWithCloud:^{
		NSLog(@"syncWithCloud success");
		NSLog(@"deviceModel: %@", weakSelf.device.deviceModel);
	} failure:^{
		NSLog(@"syncWithCloud failure");
	}];
}
```

#### 更新所有设备信息

参见[用户管理-更新设备列表](#sync-device)

### 设备功能点

`TuyaSmartDeviceModel`类的`dps`属性（`NSDictionary`类型）定义了当前设备的状态，称作数据点（DP点）或功能点。

`dps`字典里的每个`key`对应一个功能点的`dpId`，`value`对应一个功能点的`dpValue `，`dpValue`为该功能点的值。<br />

产品功能点定义参见[涂鸦开发者平台](https://developer.tuya.com/)的产品功能，如下图所示：

![功能点](./images/ios_dp_sample.jpeg)


发送控制指令按照以下格式：

`{"<dpId>":"<dpValue>"}`

根据后台该产品的功能点定义，示例代码如下:

```objc
- (void)publishDps {
    // self.device = [TuyaSmartDevice deviceWithDeviceId:@"your_device_id"];
    
    NSDictionary *dps;
	//设置dpId为1的布尔型功能点示例 作用:开关打开 
	dps = @{@"1": @(YES)};
	
	//设置dpId为4的字符串型功能点示例 作用:设置RGB颜色为ff5500
	dps = @{@"4": @"ff5500"};

	//设置dpId为5的枚举型功能点示例 作用:设置档位为2档
	dps = @{@"5": @"2"};

	//设置dpId为6的数值型功能点示例 作用:设置温度为20°
	dps = @{@"6": @(20)};
	
	//设置dpId为15的透传型(byte数组)功能点示例 作用:透传红外数据为1122
	dps = @{@"15": @"1122"};
	
	//多个功能合并发送
	dps = @{@"1": @(YES), @"4": @(ff5500)};
	
	[self.device publishDps:dps success:^{
		NSLog(@"publishDps success");
		
		//下发成功，状态上报通过 deviceDpsUpdate方法 回调
		
	} failure:^(NSError *error) {
		NSLog(@"publishDps failure: %@", error);
	}];
	
	
}
```
##### 注意事项：
- 控制命令的发送需要特别注意数据类型。<br />
比如功能点的数据类型是数值型（value），那控制命令发送的应该是 `@{@"2": @(25)}`  而不是  `@{@"2": @"25"}`<br />
- 透传类型传输的byte数组是字符串格式、字母需小写并且必须是偶数位。<br />
比如正确的格式是: `@{@"1": @"011f"}` 而不是 `@{@"1": @"11f"}`

功能点更多概念参见[快速入门-功能点相关概念](https://docs.tuya.com/cn/creatproduct/#_7)

#### 设备状态更新

实现`TuyaSmartDeviceDelegate`代理协议后，可以在设备状态更变的回调中进行处理，刷新APP设备控制面板的UI。

```objc
- (void)initDevice {
	self.device = [TuyaSmartDevice deviceWithDeviceId:@"your_device_id"];
	self.device.delegate = self;
}

#pragma mark - TuyaSmartDeviceDelegate

- (void)device:(TuyaSmartDevice *)device dpsUpdate:(NSDictionary *)dps {
	NSLog(@"deviceDpsUpdate: %@", dps);
	// TODO: 刷新界面UI
}

- (void)deviceInfoUpdate:(TuyaSmartDevice *)device {
	//当前设备信息更新 比如 设备名、设备在线状态等
}

- (void)deviceRemoved:(TuyaSmartDevice *)device {
	//当前设备被移除
}

```

### 修改设备名称

```objc
- (void)modifyDeviceName:(NSString *)mame {
	// self.device = [TuyaSmartDevice deviceWithDeviceId:@"your_device_id"];
	
	[self.device updateName:name success:^{
		NSLog(@"updateName success");
	} failure:^(NSError *error) {
		NSLog(@"updateName failure: %@", error);
	}];
}
```

### 移除设备

设备被移除后，会重新进入待配网状态（快连模式）。

```objc
- (void)removeDevice {
	// self.device = [TuyaSmartDevice deviceWithDeviceId:@"your_device_id"];
	
	[self.device remove:^{
		NSLog(@"remove success");
	} failure:^(NSError *error) {
		NSLog(@"remove failure: %@", error);
	}];
}
```

### 固件升级

**固件升级流程:**

获取设备升级信息 -> 下发联网模块升级指令 -> 联网模块升级成功 -> 下发设备控制模块升级指令 -> 设备控制模块升级成功

#### 获取设备升级信息：

```objc
- (void)getFirmwareUpgradeInfo {
	// self.device = [TuyaSmartDevice deviceWithDeviceId:@"your_device_id"];
	
	[self.device getFirmwareUpgradeInfo:^(TuyaSmartFirmwareUpgradeModel *devModel, TuyaSmartFirmwareUpgradeModel *gwModel) {
		NSLog(@"getFirmwareUpgradeInfo success");
	} failure:^(NSError *error) {
		NSLog(@"getFirmwareUpgradeInfo failure: %@", error);
	}];
}
```

#### 下发升级指令：

```objc
- (void)upgradeFirmware {
	// self.device = [TuyaSmartDevice deviceWithDeviceId:@"your_device_id"];
	
	NSInteger type = 1;
	[self.device upgradeFirmware:type success:^{
		NSLog(@"upgradeFirmware success"); 
	} failure:^(NSError *error) {
		NSLog(@"upgradeFirmware failure: %@", error); 
	}];
}
```
注: type 1 升级联网模块 2 升级设备控制模块

#### 回调接口：
```objc
- (void)deviceFirmwareUpgradeSuccess:(TuyaSmartDevice *)device {
	//固件升级成功
}

- (void)deviceFirmwareUpgradeFailure:(TuyaSmartDevice *)device {
	//固件升级失败
}

- (void)device:(TuyaSmartDevice *)device firmwareUpgradeProgress:(NSInteger)type progress:(double)progress {
	//升级进度回调 type 1 - 联网模块 2 - 设备控制模块
}

```

## 共享设备

我们提供了两种共享方式：
一种是到用户的共享，主要用于把设备共享给家人，设备拥有者一旦把设备共享给了自己的家人，家人就拥有了该用户所有设备的控制权限。
另一种是到设备的共享，有时候需要把某些设备共享给家人，这时可以只把相应的设备共享给朋友，朋友不会拥有其它设备的控制权限，并且可以设置

被共享的设备不能进行改名、移除设备、固件升级、恢复出厂设置等操作（只能发送设备控制指令、获取状态更新）。

### 用户共享 （基于用户维度的共享）

用户共享相关的所有功能对应`TuyaSmartMember`类

#### 添加共享

手机、邮箱共享

```objc
- (void)addShare {
	// self.member = [[TuyaSmartMember alloc] init];
	
	[self.member addNewMember:@"member_name" phoneCode:@"member_country_code" userAccount:@"member_phone_or_email" relationship:TYRelationshipFriend success:^{
		NSLog(@"addNewMember success");
	} failure:^(NSError *error) {
		NSLog(@"addNewMember failure: %@", error);
	}];
}
```

UID共享

```objc
- (void)addShare {
	// self.member = [[TuyaSmartMember alloc] init];
	
	[self.member addNewMember:@"member_name" uid:@"member_unique_id" relationship:TYRelationshipFriend success:^{
		NSLog(@"addNewMember success");
	} failure:^(NSError *error) {
		NSLog(@"addNewMember failure: %@", error);
	}];
}
```

####  获取共享列表

获取共享列表（即这些人可以控制你的设备）：

```objc
- (void)initMemberList {
	// self.member = [[TuyaSmartMember alloc] init];
	
	[self.member getMemberList:^(NSArray<TuyaSmartMemberModel *> *list) {
		NSLog(@"getMemberList success: %@", list);
	} failure:^{
		NSLog(@"getMemberList failure");
	}];
}
```

获取收到的共享列表（即你可以控制他们共享的设备）：

```objc
- (void)initReceiveMemberList {
	// self.member = [[TuyaSmartMember alloc] init];
	
	[self.member getReceiveMemberList:^(NSArray<TuyaSmartMemberModel *> *list) {
		NSLog(@"getReceiveMemberList success: %@", list);
	} failure:^{
		NSLog(@"getReceiveMemberList failure");
	}];
}
```

#### 修改备注

修改共享成员名称：

```objc
- (void)modifyMemberName:(TuyaSmartMemberModel *)memberModel name:(NSString *)name {
	// self.member = [[TuyaSmartMember alloc] init];
	
	[self.member modifyMemberName:memberModel.memberId name:name success:^{
	    NSLog(@"modifyMemberName success");
	} failure:^(NSError *error) {
	    NSLog(@"modifyMemberName failure: %@", error);
	}];
}
```

修改收到的共享成员名称：

```objc
- (void)modifyReceiveMemberName:(TuyaSmartMemberModel *)memberModel name:(NSString *)name {
	// self.member = [[TuyaSmartMember alloc] init];
	
	[self.member modifyReceiveMemberName:memberModel.memberId name:name success:^{
	    NSLog(@"modifyReceiveMemberName success");
	} failure:^(NSError *error) {
	    NSLog(@"modifyReceiveMemberName failure: %@", error);
	}];
```

#### 删除共享

删除共享后，你将不能使用对方的设备，或者对方将不能使用你的设备。

```objc
- (void)removeMember:(TuyaSmartMemberModel *)memberModel {
	// self.member = [[TuyaSmartMember alloc] init];
	
	[self.member removeMember:memberModel.memberId success:^{
	    NSLog(@"removeMember success");
	} failure:^(NSError *error) {
	    NSLog(@"removeMember failure: %@", error);
	}];
}
```


### 设备共享 （基于设备维度的共享）

设备共享相关的所有功能对应`TuyaSmartDeviceShare`类

#### 添加共享

```objc

- (void)addMemberShare {
	//self.shareService = [TuyaSmartDeviceShare new];
	
    [self.shareService addMemberShare:@"country_code" userAccount:@"user_account" devIds:@"devId list" autoSharing:YES success:^(TuyaSmartShareMemberModel *model) {
    
		NSLog(@"addShare success");
    
	} failure:^(NSError *error) {
	           
		NSLog(@"addShare failure: %@", error);
	
	}];
	
}
	
```


#### 获取共享的用户列表

获取所有主动共享的用户列表

```objc

- (void)getShareMemberList {
	//self.shareService = [TuyaSmartDeviceShare new];
		
	[self.shareService getShareMemberList:^(NSArray<TuyaSmartShareMemberModel *> *list) {
	    
		NSLog(@"getShareMemberList success");
	
	} failure:^(NSError *error) {
	    
		NSLog(@"getShareMemberList failure: %@", error);

	}];
	
}
	
```

获取所有收到共享的用户列表

```objc

- (void)getReceiveMemberList {
	//self.shareService = [TuyaSmartDeviceShare new];
		
	[self.shareService getReceiveMemberList:^(NSArray<TuyaSmartShareMemberModel *> *list) {
	    
		NSLog(@"getReceiveMemberList success");
	
	} failure:^(NSError *error) {
	    
		NSLog(@"getReceiveMemberList failure: %@", error);

	}];
    
}
```

#### 获取用户共享数据

获取单个主动共享的用户共享数据

```objc

- (void)getShareMemberDetail {
	 //self.shareService = [TuyaSmartDeviceShare new];
		
    [self.shareService getShareMemberDetail:@"member_id" success:^(TuyaSmartShareMemberDetailModel *model) {
    
    	NSLog(@"getShareMemberDetail success");
        
    } failure:^(NSError *error) {

    	NSLog(@"getShareMemberDetail failure: %@", error);

    }];
    
}
```


获取单个收到共享的用户共享数据

```objc

- (void)getReceiveMemberDetail {
    //self.shareService = [TuyaSmartDeviceShare new];
		
    [self.shareService getReceiveMemberDetail:@"member_id" success:^(TuyaSmartShareMemberDetailModel *model) {
    
    	NSLog(@"getReceiveMemberDetail success");
        
    } failure:^(NSError *error) {

    	NSLog(@"getReceiveMemberDetail failure: %@", error);

    }];
    
}
```

#### 删除共享

删除主动共享者

```objc

- (void)removeShareMember {
	 //self.shareService = [TuyaSmartDeviceShare new];
		
    [self.shareService removeShareMember:@"member_id" success:^{
        
    	NSLog(@"removeShareMember success");

    } failure:^(NSError *error) {
    
    	NSLog(@"removeShareMember failure: %@", error);

    }];
    
}
     
```


删除收到共享者

```objc

- (void)removeReceiveMember {
	 //self.shareService = [TuyaSmartDeviceShare new];
		
    [self.shareService removeReceiveMember:@"member_id" success:^{
        
    	NSLog(@"removeReceiveMember success");

    } failure:^(NSError *error) {
    
    	NSLog(@"removeReceiveMember failure: %@", error);

    }];
    
} 
```

#### 修改昵称

修改主动共享者的昵称

```objc

- (void)updateShareMemberName {
	 //self.shareService = [TuyaSmartDeviceShare new];
		
    [self.shareService updateShareMemberName:@"member_id" name:@"name" success:^{
        
    	NSLog(@"updateShareMemberName success");
    	
    } failure:^(NSError *error) {
        
    	NSLog(@"updateShareMemberName failure: %@", error);

    }];
     
```

修改收到共享者的昵称

```objc

- (void)updateReceiveMemberName {
	 //self.shareService = [TuyaSmartDeviceShare new];
		
    [self.shareService updateReceiveMemberName:@"member_id" name:@"name" success:^{
        
    	NSLog(@"updateReceiveMemberName success");
    	
    } failure:^(NSError *error) {
        
    	NSLog(@"updateReceiveMemberName failure: %@", error);

    }];
     
}
```

#### 单设备共享操作

单设备添加共享

```objc

- (void)addDeviceShare {
	 //self.shareService = [TuyaSmartDeviceShare new];
		
    [self.shareService addDeviceShare:@"member_id" devId:@"dev_id" success:^{
        
    	NSLog(@"addDeviceShare success");
            	
    } failure:^(NSError *error) {
        
		NSLog(@"addDeviceShare failure: %@", error);
        
    }];
    
}
     
```

单设备删除共享

```objc

- (void)removeDeviceShare {
	 //self.shareService = [TuyaSmartDeviceShare new];
		
    [self.shareService removeDeviceShare:@"member_id" devId:@"dev_id" success:^{
        
    	NSLog(@"removeDeviceShare success");
            	
    } failure:^(NSError *error) {
        
		NSLog(@"removeDeviceShare failure: %@", error);
        
    }];
     
 }
```


单设备删除共享 

```objc

- (void)removeDeviceShare {
	 //self.shareService = [TuyaSmartDeviceShare new];
		
    [self.shareService removeDeviceShare:@"dev_id" success:^{
        
    	NSLog(@"removeDeviceShare success");
            	
    } failure:^(NSError *error) {
        
		NSLog(@"removeDeviceShare failure: %@", error);
        
    }];
    
}
     
```


#### 自动共享

设置新添加设备是否自动共享

```objc

- (void)enableNewDeviceAutoShare {
	 //self.shareService = [TuyaSmartDeviceShare new];
		
    [self.shareService enableNewDeviceAutoShare:YES memberId:@"member_id" success:^{
        
	 	NSLog(@"enableNewDeviceAutoShare success");
	
    } failure:^(NSError *error) {
        
    	NSLog(@"enableNewDeviceAutoShare failure: %@", error);

   }];
         
}
```

#### 获取设备共享用户列表

```objc

- (void)getDeviceShareMemberList {
	 //self.shareService = [TuyaSmartDeviceShare new];
		
    [self.shareService getDeviceShareMemberList:@"dev_id" success:^(NSArray<TuyaSmartShareMemberModel *> *list) {
        
        NSLog(@"getDeviceShareMemberList success");
        
    } failure:^(NSError *error) {
        
        NSLog(@"getDeviceShareMemberList failure: %@", error);
	
    }];
    
}
         
```

#### 获取当前用户所有可分享的设备

```objc

- (void)getShareDeviceList {
	 //self.shareService = [TuyaSmartDeviceShare new];
		
	 NSArray *list = self.shareService.getShareDeviceList;
	 
}
         
```



## 定时任务

设计思路如下图所示：

![Timer](./images/ios-sdk-timer.jpg)

定时任务相关的所有功能对应`TuyaSmartTimer`类。

_注：loops: @"0000000", 每一位 0:关闭,1:开启, 从左至右依次表示: 周日 周一 周二 周三 周四 周五 周六_

### 增加定时任务

增加一个timer到指定device的指定task下

```objc
- (void)addTimer {
	// self.timer = [[TuyaSmartTimer alloc] init];
	NSDictionary *dps = @{@"1": @(YES)};
	
	[self.timer addTimerWithTask:@"timer_task_name" loops:@"1000000" devId:@"device_id" time:@"18:00" dps:dps success:^{
		NSLog(@"addTimerWithTask success");
	} failure:^(NSError *error) {
		NSLog(@"addTimerWithTask failure: %@", error);
	}];
}
```

### 获取定时任务状态

获取指定device下所有task模型

```objc
- (void)getTimer {
	// self.timer = [[TuyaSmartTimer alloc] init];
	
	[self.timer getTimerTaskStatusWithDeviceId:@"device_id" success:^(NSArray<TPTimerTaskModel *> *list) {
		NSLog(@"getTimer success %@:", list);
	} failure:^(NSError *error) {
		NSLog(@"getTimer failure: %@", error);
	}];
}
```

### 更新定时任务状态

更新指定device下的指定task的状态 0:关闭,1:开启

```objc
- (void)updateTimer {
	// self.timer = [[TuyaSmartTimer alloc] init];
	
	[self.timer updateTimerTaskStatusWithTask:@"timer_task_name" devId:@"device_id" status:1 success:^{
		NSLog(@"updateTimer success");
	} failure:^(NSError *error) {
		NSLog(@"updateTimer failure: %@", error);
	}];
}
```

### 更新定时钟状态

更新指定device下的指定task下的指定timer的状态 0:关闭,1:开启

```objc
- (void)updateTimer {
	// self.timer = [[TuyaSmartTimer alloc] init];

	[self.timer updateTimerStatusWithTask:@"timer_task_name" devId:@"device_id" timerId:@"timer_id" status:1 success:^{
		NSLog(@"updateTimer success");
	} failure:^(NSError *error) {
		NSLog(@"updateTimer failure: %@", error);
	}];
}
```

### 删除定时钟

删除指定device下的指定task下的指定timer

```objc
- (void)removeTimer {
	// self.timer = [[TuyaSmartTimer alloc] init];
	
	[self.timer removeTimerWithTask:@"timer_task_name" devId:@"device_id" timerId:@"timer_id" success:^{
		NSLog(@"removeTimer success");
	} failure:^(NSError *error) {
		NSLog(@"removeTimer failure: %@", error);
	}];
}
```

### 更新定时钟

更新指定device下的指定task下的指定timer

```objc
- (void)updateTimer {
	// self.timer = [[TuyaSmartTimer alloc] init];
	NSDictionary *dps = @{@"1": @(YES)};
	
	[self.timer updateTimerWithTask:@"timer_task_name" loops:@"1000000" devId:@"device_id" timerId:@"timer_id" time:@"18:00" dps:dps success:^{
		NSLog(@"updateTimer success");
	} failure:^(NSError *error) {
		NSLog(@"updateTimer failure: %@", error);
	}];
}
```

### 获取定时任务下所有定时钟

获取指定device下的指定task下所有timer模型

```objc
- (void)getTimer {
	// self.timer = [[TuyaSmartTimer alloc] init];

	[self.timer getTimerWithTask:@"timer_task_name" devId:@"device_id" success:^(NSArray<TPTimerModel *> *list) {
		NSLog(@"getTimer success %@:", list); 
	} failure:^(NSError *error) {
		NSLog(@"getTimer failure: %@", error);
	}];
}
```

### 获取设备所有定时任务下所有定时钟

获取指定device下所有task下所有timer模型

```objc
- (void)getTimer {
	// self.timer = [[TuyaSmartTimer alloc] init];

	[self.timer getAllTimerWithDeviceId:@"device_id" success:^(NSDictionary *dict) {
		NSLog(@"getTimer success %@:", list); 
	} failure:^(NSError *error) {
		NSLog(@"getTimer failure: %@", error);
	}];
}
```

## 群组管理

涂鸦云支持群组管理体系：可以创建群组，修改群组名称，管理群组设备，通过群组管理多个设备，解散群组。

群组相关的所有功能对应`TuyaSmartGroup`类，需要使用群组Id进行初始化。错误的群组Id可能会导致初始化失败，返回`nil`。

群组Id指的是`TuyaSmartGroupModel`下的`groupId`字段，可以从[用户设备列表](#sync-device)中获取。

### 创建群组
```objc
- (void)createNewGroup {
    //self.smartGroup = [[TuyaSmartGroup alloc] init];
    [self.smartGroup createGroupWithName:@"your_group_name" productId:@"your_group_product_id" devIdList:(NSArray<NSString *> *)selectedDevIdList success:^(TuyaSmartGroup *group) {
        NSLog(@"create new group success %@:", group); 
    } failure:^(NSError *error) {
        NSLog(@"create new group failure");
    }];
}
```

### 获取群组的设备列表
群组没有创建，获取产品的设备列表

```objc
- (void)getGroupDevList {
    //self.smartGroup = [[TuyaSmartGroup alloc] init];
    [self.smartGroup getGroupDevList:nil productId:@"your_group_product_id" success:^(NSArray<TYGroupDevListModel *> *list) {
        NSLog(@"get group dev list success %@:", list); 
    } failure:^(NSError *error) {
        NSLog(@"get group dev list failure");
    }];
}
```

群组已经创建，获取群组的设备列表

```objc
- (void)getGroupDevList {
//    self.smartGroup = [TuyaSmartGroup groupWithGroupId:@"your_group_id"];
    [self.smartGroup getGroupDevList:@"your_group_id" productId:@"your_group_product_id" success:^(NSArray<TYGroupDevListModel *> *list) {
        NSLog(@"get group dev list success %@:", group); 
    } failure:^(NSError *error) {
        NSLog(@"get group dev list failure");
    }];
}
```

### 群组dp命令下发

```objc
- (void)publishDps {
//    self.smartGroup = [TuyaSmartGroup groupWithGroupId:@"your_group_id"];
	
	NSDictionary *dps = @{@"1": @(YES)};
	[self.smartGroup publishDps:dps success:^{
		NSLog(@"publishDps success");
	} failure:^(NSError *error) {
		NSLog(@"publishDps failure: %@", error);
	}];
```
### 修改群组名称

```objc
- (void)updateGroupName {
//    self.smartGroup = [TuyaSmartGroup groupWithGroupId:@"your_group_id"];

    [self.smartGroup updateGroupName:@"your_group_name" success:^{
        NSLog(@"update group name success");
    } failure:^(NSError *error) {
        NSLog(@"update group name failure: %@", error);
    }];
}
```
### 修改群组设备列表

```objc
- (void)updateGroupRelations {
//    self.smartGroup = [TuyaSmartGroup groupWithGroupId:@"your_group_id"];

    [self.smartGroup updateGroupRelations:(NSArray<NSString *> *)selectedDevIdList success:^ {
        NSLog(@"update group relations success");
    } failure:^(NSError *error) {
        NSLog(@"update group relations failure: %@", error);
    }];
}
```
### 解散群组

```objc
- (void)dismissGroup {
//    self.smartGroup = [TuyaSmartGroup groupWithGroupId:@"your_group_id"];

    [self.smartGroup dismissGroup:^{
      NSLog(@"dismiss group success");
    } failure:^(NSError *error) {
      NSLog(@"dismiss group failure: %@", error);
    }];
}
```


### 回调接口
群组DP下发之后的数据回调更新

```objc

#pragma mark - TuyaSmartGroupDelegate

- (void)group:(TuyaSmartGroup *)group dpsUpdate:(NSDictionary *)dps {
	//可以在这里刷新群组操作面板的UI
}

```

## 智能场景
涂鸦云支持用户根据实际生活场景，通过设置气象或设备条件，当条件满足时，让一个或多个设备执行相应的任务。

场景相关的功能对应`TuyaSmartScene`和`TuyaSmartSceneManager`两个类，`TuyaSmartScene`提供了单个场景的添加、编辑、删除、执行4种操作，需要使用场景id进行初始化，场景id指的是`TuyaSmartSceneModel`的`sceneId`字段，可以从场景列表中获取。`TuyaSmartSceneManager`类（单例）则主要提供了场景里条件、任务、设备、城市相关的所有数据。

在使用智能场景相关的接口之前，需要首先了解场景条件和场景任务这两个概念。

### 场景条件
场景条件对应`TuyaSmartSceneConditionModel`类，涂鸦云支持两种条件类型：

- 气象条件：包括温度、湿度、天气、PM2.5、空气质量、日落日出，用户选择气象条件时，可以选择当前城市。
- 设备条件：指用户可预先选择一个设备的功能状态，当该设备达到该状态时，会触发当前场景里的任务，但同一设备不能同时作为条件和任务，避免操作冲突。

### 场景任务
场景任务是指当该场景满足已经设定的气象或设备条件时，让一个或多个设备执行某种操作，对应`TuyaSmartSceneActionModel`类。

### 获取场景列表
```objc
- (void)getSmartSceneList {
    [[TuyaSmartSceneManager sharedInstance] getSceneList:^(NSArray<TuyaSmartSceneModel *> *list) {
        NSLog(@"get scene list success %@:", list);
    } failure:^(NSError *error) {
        NSLog(@"get scene list failure: %@", error);
    }];
}
```
### 添加场景

添加场景需要传入场景名称，条件（目前只支持一个条件），任务列表（至少一个任务），也可以只设置名称和任务，不设置条件，但是需要手动执行。构造条件可使用
`[TuyaSmartSceneConditionModel initWithSceneDPModel:]`方法，构造任务可使用`[TuyaSmartSceneActionModel initWithSceneDPModel:]`方法。

```objc
- (void)addSmartScene {
    [TuyaSmartScene addNewScene:@"your_scene_name" condition:(TuyaSmartSceneConditionModel *)condition actionList:(NSArray<TuyaSmartSceneActionModel*> *)actionList success:^(TuyaSmartSceneModel *sceneModel) {
        NSLog(@"add scene success %@:", sceneModel);
    } failure:^(NSError *error) {
        NSLog(@"add scene failure: %@", error);
    }];
}

```
### 编辑场景

编辑场景的名称、条件或任务

```objc
- (void)modifySmartScene {
//    self.smartScene = [TuyaSmartScene sceneWithSceneId:@"your_scene_id"];
    [self.smartScene modifyScene:@"your_scene_name" condition:condition actionList:self.dataSource success:^{
        NSLog(@"modify scene success");
    } failure:^(NSError *error) {
        NSLog(@"modify scene failure: %@", error);
    }];
}
```
### 删除场景

```objc
- (void)deleteSmartScene {
//    self.smartScene = [TuyaSmartScene sceneWithSceneId:@"your_scene_id"];
	[self.smartScene deleteScene:^{
        NSLog(@"delete scene success");
    } failure:^(NSError *error) {
        NSLog(@"delete scene failure: %@", error);
    }];
}
```
### 执行场景
```objc
- (void)executeSmartScene {
//    self.smartScene = [TuyaSmartScene sceneWithSceneId:@"your_scene_id"];
	[self.smartScene exeuteScene:^{
   		NSLog(@"execute scene success");    
    } failure:^(NSError *error) {
        NSLog(@"execute scene failure: %@", error);
    }];
}
```
### 获取条件列表

获取条件列表，如温度、湿度、天气、PM2.5、日落日出等，注意：设备也可作为条件。

```objc
- (void)getConditionList {
	[[TuyaSmartSceneManager sharedInstance] getConditionList:^(NSArray<TuyaSmartSceneDPModel *> *list) {
        NSLog(@"get condition list success:%@", list);
    } failure:^(NSError *error) {
        NSLog(@"get condition list failure: %@", error);
    }];
}
```
### 获取任务设备列表

添加任务时，需获取任务的设备列表，用来选择执行相应的任务。

```objc
- (void)getActionDeviceList {
	[[TuyaSmartSceneManager sharedInstance] getActionDeviceList:^(NSArray<TuyaSmartDeviceModel *> *list) {
		NSLog(@"get action device list success:%@", list);
	} failure:^(NSError *error) {
		NSLog(@"get action device list failure: %@", error);
	}];
}
```
### 获取条件设备列表

添加条件时，除了温度、湿度、天气等这些气象条件可以作为任务执行条件外，设备也可以作为条件，即获取条件设备列表，然后选择一个设备执行相应的任务作为条件。

```objc
- (void)getConditionDeviceList {
	[[TuyaSmartSceneManager sharedInstance] getConditionDeviceList:^(NSArray<TuyaSmartDeviceModel *> *list) {
		NSLog(@"get condition device list success:%@", list);
	} failure:^(NSError *error) {
		NSLog(@"get condition device list failure: %@", error);
	}];
}
```
### 获取任务设备的dp列表

添加或编辑场景任务时，选择设备后，需要根据选择设备的deviceId获取设备dp列表，进而选择某一个dp功能点，即指定该设备执行该项任务。

```objc
- (void)getActionDeviceDPList {
	[[TuyaSmartSceneManager sharedInstance] getActionDeviceDPList:@"your_device_id" success:^(NSArray<TuyaSmartSceneDPModel *> *list) {
		NSLog(@"get action device dp list success:%@", list);
	} failure:^(NSError *error) {
		NSLog(@"get action device dp list failure: %@", error);
	}];
}
```
### 获取条件设备的dp列表

选择场景条件时，选择了设备，需要根据选择设备的deviceId获取设备dp列表，进而选择某一个dp功能点，即指定该设备执行该dp功能作为该场景的执行条件。

```objc
- (void)getCondicationDeviceDPList {
	[[TuyaSmartSceneManager sharedInstance] getCondicationDeviceDPList:@"your_device_id" success:^(NSArray<TuyaSmartSceneDPModel *> *list) {
		NSLog(@"get condition device dp list success:%@", list);
	} failure:^(NSError *error) {
		NSLog(@"get condition device dp list failure: %@", error);
	}];
}    
```
### 获取城市列表

选择场景气象条件时，根据国家码获取城市列表，用户可以选择当前城市。（注：国外部分国家的城市列表可能暂时不全，如果是国外用户，建议根据经纬度获取城市信息。）

```objc
- (void)getCityList {
	[[TuyaSmartSceneManager sharedInstance] getCityList:@"your_country_code" success:^(NSArray<TuyaSmartCityModel *> *list) {
		NSLog(@"get city list success:%@", list);
	} failure:^(NSError *error) {
   		NSLog(@"get city list failure: %@", error);    
	}];
}
```
### 根据经纬度获取城市信息

```objc
- (void)getCityInfo {
	[[TuyaSmartSceneManager sharedInstance] getCityInfo:@"your_location_latitude" longitude:@"your_location_longitude" success:^(TuyaSmartCityModel *city) {
		NSLog(@"get city info success:%@", city);
	} failure:^(NSError *error) {
		NSLog(@"get city info failure:%@", error);       
	}];
}
```
### 根据城市id获取城市信息

根据城市id获取城市信息，城市id可以从城市列表获取。

```objc
- (void) getCityInfo {
	[[TuyaSmartSceneManager sharedInstance] getCityInfoByCityId:@"your_city_id" success:^(TuyaSmartCityModel *city) {
		NSLog(@"get city info success:%@", city);     
	} failure:^(NSError *error) {
		NSLog(@"get city info failure:%@", error);       
	}];
}
```

## 消息中心

消息中心相关的所有功能对应`TuyaSmartMessage`类，支持获取消息列表，批量删除消息，以及是否有消息更新。

### 获取消息列表
```objc
- (void)getMessageList {
//    self.smartMessage = [[TuyaSmartMessage alloc] init];
	[self.smartMessage getMessageList:^(NSArray<TuyaSmartMessageListModel *> *list) {
		NSLog(@"get message list success:%@", list);
	} failure:^(NSError *error) {
		NSLog(@"get message list failure:%@", error);
	}];
}
```
### 删除消息
批量删除消息，`messgeIdList`是要删除消息的id数组，消息id可以从消息列表中获取。

```objc
- (void)deleteMessage {
//    self.smartMessage = [[TuyaSmartMessage alloc] init];
    [self.smartMessage deleteMessage:(NSArray <NSString *> *)messgeIdList success:^{
		NSLog(@"delete message success");
    } failure:^(NSError *error) {
    	NSLog(@"delete message failure:%@", error);
    }];
}
```
### 获取最新一条消息的时间戳
获取最新一条消息的时间戳，可以用于与本地最新一条消息的时间戳比较，大于本地最新消息时间，则展示红点，表示有新消息。

```objc
- (void)getMessageMaxTime {
//    self.smartMessage = [[TuyaSmartMessage alloc] init];
	[self.smartMessage getMessageMaxTime:^(int result) {
		NSLog(@"get message max time success:%d", result);
	} failure:^(NSError *error) {
		NSLog(@"get message max time failure:%@", error);
	}];
}
```

## 意见反馈

当用户有问题需要反馈时，可添加反馈，添加反馈时应先选择反馈类型，然后撰写反馈内容进行提交，提交后会按照之前选择的反馈类型生成相应的反馈会话，同时用户也可以在该会话中继续撰写反馈内容并提交，显示在该会话的反馈列表中。

意见反馈相关的所有功能对应`TuyaSmartFeedback`类，支持获取反馈会话列表，获取会话中反馈内容列表，获取反馈类型列表，以及添加反馈。

### 获取反馈会话列表
获取用户已提交反馈会话列表。

```objc
- (void)getFeedbackTalkList {
//    self.feedBack = [[TuyaSmartFeedback alloc] init];
	[self.feedBack getFeedbackTalkList:^(NSArray<TuyaSmartFeedbackTalkListModel *> *list) {
		NSLog(@"get feedback talk list success:%@", list);
	} failure:^(NSError *error) {
		NSLog(@"get feedback talk list failure:%@", error);
	}];
}
```
### 获取反馈列表
获取反馈会话中对应的反馈内容列表，`hdId`和`hdType`字段可以从`TuyaSmartFeedbackTalkListModel`中获取。

```objc
- (void)getFeedbackList {
//    self.feedBack = [[TuyaSmartFeedback alloc] init];
	[self.feedBack getFeedbackList:@"your_hdId" hdType:(NSInteger)hdType success:^(NSArray<TuyaSmartFeedbackModel *> *list) {
		NSLog(@"get feedback list success:%@", list);
	} failure:^(NSError *error) {
		NSLog(@"get feedback list failure:%@", error);
	}];
}
```
### 获取反馈类型列表
添加反馈时，可先选择反馈类型。

```objc
- (void)getFeedbackTypeList {
//    self.feedBack = [[TuyaSmartFeedback alloc] init];
	[self.feedBack getFeedbackTypeList:^(NSArray<TuyaSmartFeedbackTypeListModel *> *list) {
		NSLog(@"get feedback type list success:%@", list);
	} failure:^(NSError *error) {
		NSLog(@"get feedback type list failure:%@", error);
	}];
}
```
### 添加反馈
添加反馈，提交用户输入的反馈的内容，`hdId`和`hdType`字段可以从`TuyaSmartFeedbackTalkListModel`中获取。

```objc
- (void)addFeedback {
//    self.feedBack = [[TuyaSmartFeedback alloc] init];
	[self.feedBack addFeedback:@"your_feedback_content" hdId:@"your_hdId" hdType:(NSInteger)hdType success:^{
		NSLog(@"add feedback success");
	} failure:^(NSError *error) {
		NSLog(@"add feedback failure:%@", error);
	}];
}
```
## 通用接口
调用服务端的api接口

```objc

- (void)load {
    //self.request = [TuyaSmartRequest alloc] init];

    /**
	 *  请求服务端接口
	 *
	 *  @param apiName	接口名称
	 *  @param postData 业务入参
	 *  @param version  接口版本号
	 *  @param success  操作成功回调
	 *  @param failure  操作失败回调
	 */
    [self.request requestWithApiName:@"api_name" postData:@"post_data" version:@"api_version" success:^(id result) {
        
    } failure:^(NSError *error) {
        
    }];
	
}


```

## 集成Push
基于Tuya SDK开发的app，Tuya平台支持Push功能，支持给用户发送运营Push和产品的告警Push。

### Xcode配置

点击项目 - `TARGETS` - `Capabilities`, 将这里的 `Push Notification `的开关打开，效果如下图所示：

![ios-push](./images/ios-push.png)


### 涂鸦开发者平台配置
登录涂鸦开发者平台 - 进入对应APP - 推送配置 - 上传push证书

![ios-push-setting](./images/ios-push-setting.png)



### 初始化
在 `didFinishLaunchingWithOptions` 方法中初始化push

```objc
    
- (BOOL)application:(UIApplication *)application didFinishLaunchingWithOptions:(NSDictionary *)launchOptions {
	
	
    [application registerForRemoteNotifications];
    [application registerUserNotificationSettings:[UIUserNotificationSettings settingsForTypes:UIUserNotificationTypeAlert|UIUserNotificationTypeBadge|UIUserNotificationTypeSound categories:nil]];
   	
    
    if ([[[UIDevice currentDevice] systemVersion] floatValue] >= 10.0) {
        //iOS10需要加下面这段代码。
        UNUserNotificationCenter *center = [UNUserNotificationCenter currentNotificationCenter];
        center.delegate = self;
        UNAuthorizationOptions types10 = UNAuthorizationOptionBadge|UNAuthorizationOptionAlert|UNAuthorizationOptionSound;
        [center requestAuthorizationWithOptions:types10 completionHandler:^(BOOL granted, NSError * _Nullable error) {
            if (granted) {
                //点击允许
            } else {
                //点击不允许
            }
        }];
    }
    
}

```

### 注册pushId
在`didRegisterForRemoteNotificationsWithDeviceToken`中注册pushId到Tuya SDK

```objc

- (void)application:(UIApplication *)application didRegisterForRemoteNotificationsWithDeviceToken:(NSData *)deviceToken {
    
        
    NSString *pushId = [[[[deviceToken description]
                 stringByReplacingOccurrencesOfString:@" " withString:@""]
                stringByReplacingOccurrencesOfString:@"<" withString:@""]
               stringByReplacingOccurrencesOfString:@">" withString:@""];
    
    NSLog(@"pushId is %@",pushId);
    
    [[TuyaSmartSDK sharedInstance] setValue:pushId forKey:@"deviceToken"];
}

```


### 接收通知
接收到远程通知，在代理方法didReceiveRemoteNotification中执行

```objc
- (void)application:(UIApplication *)application didReceiveRemoteNotification:(NSDictionary *)userInfo {


}
```

### 发送Push

#### 新增运营Push
涂鸦开发者平台 - 用户运营 - 消息中心 - 新增消息

#### 新增告警Push
涂鸦开发者平台 - 对应产品 - 扩展功能 - 告警设置 - 新增告警规则(应用推送方式)

 
## FAQ

1、 为什么执行`pod install`会报错？  
确认cocoapod是最新版本，执行`pod --version`命令查看pod版本，确认版本是1.3.0以上

2、为什么调用SDK接口以后，会报`Error Domain=NSURLErrorDomain Code=-999 "已取消"`的错误? 
确认请求的对象是全局变量，否则会被提早释放，例如： `self.feedBack = [[TuyaSmartFeedback alloc] init];`

3、如何开启调试模式，打印日志？
在初始化SDK之后，调用以下代码：`[[TuyaSmartSDK sharedInstance] setDebugMode:YES];`

4、下发控制指令，设备没有上报状态。  
确认功能点的数据类型是否正确，比如功能点的数据类型是数值型（value），那控制命令发送的应该是 @{@"2": @(25)} 而不是 @{@"2": @"25"}。

