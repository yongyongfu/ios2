# Tuya Smart iOS SDK

[中文版](README-zh.md) | [English](README.md)

---

## Features Overview

Tuya Smart APP SDK provides the interface package for the communication with hardware and Tuya Cloud to accelerate the application development process, including the following features:

- Hardware functions (network configuration, control, status reporting, regular tasks, groups, firmware upgrades, sharing)
- Account system (phone number, email registration, login, password reset and other general account functions)
- Tuya Cloud HTTP API interface package

## Rapid Integration

### Using CocoaPods integration (version 8.0 or above is supported)

Add the following content in file `Podfile`:

```ruby
platform :ios, '8.0'

target 'your_target_name' do

      pod "TuyaSmartHomeKit", :git => "https://github.com/xuchengcheng/tuyasmart_home_ios_sdk_test.git"

end
```

Execute command `pod update` in the project's root directory to begin integration.

For the instructions of CocoaPods, please refer to: [CocoaPods Guides](https://guides.cocoapods.org/)

## Initializing SDK

Add the following to the project file `PrefixHeader.pch`：

```objc
#import <TuyaSmartKit/TuyaSmartKit.h>
```

Open file `AppDelegate.m`，and use the `App ID` and `App Secret` obtained from the development platform in the `[AppDelegate application:didFinishLaunchingWithOptions:]`method to initialize SDK:

```objc
[[TuyaSmartSDK sharedInstance] startWithAppKey:<#your_app_key#> secretKey:<#your_secret_key#>];
```

Now all the preparatory work has been completed. You can set out to develop your application.

## Doc

Refer to details: [Tuya Smart Doc - iOS SDK](http://docs.tuya.com/develop/app-development/ios-sdk/)

## ChangeLog

[CHANGELOG.md](./CHANGELOG.md)

## SDK Demo Package
[Download Url](http://fir.im/iOSSDKDemo)
