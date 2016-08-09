//
//  RvsViewerInitHelper.h
//  Rvs_Viewer
//
//  Created by GYJ on 16/6/17.
//  Copyright © 2016年 ifziv. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "Rvs_Viewer.h"

@protocol RvsViewerInitHelperDelegate <NSObject>

@optional

/**
 *  观看端sdk登录过程中发生状态变化、错误、登录进度通知
 *
 *  @param loginState   观看端登录状态
 *  @param progressRate 观看端登录过程状态
 *  @param errCode      观看端登录过程中的错误码
 */
- (void)onLoginResultWithLoginState:(EN_RVS_VIEWER_LOGIN_STATE)loginState
                       progressRate:(EN_RVS_VIEWER_LOGIN_PROGRESS)progressRate
                            errCode:(EN_RVS_VIEWER_LOGIN_ERR)errCode;

/**
 *  观看端cid发生变化时通知应用
 *
 *  @param localCID 观看端CID
 */
- (void)onUpdateCID:(unsigned long long)localCID;


/**
 *  观看端与采集端的连接状态变化通知
 *
 *  @param streamerCID       采集端CID
 *  @param streamerConnState 观看端与采集端的连接状态
 */
- (void)onStreamer:(unsigned long long)streamerCID
         connState:(EN_RVS_STREAMER_CONN_STATE)streamerConnState;

/**
 *  与观看端绑定的采集端的配置获取状态变化通知
 *
 *  @param streamerCID       采集端CID
 *  @param streamerConfState 与观看端绑定的采集端的配置获取状态
 */
- (void)onStreamer:(unsigned long long)streamerCID
         confState:(EN_RVS_STREAMER_CONF_STATE)streamerConfState;

/**
 *  采集端的在线状态通知
 *
 *  @param streamerCID           采集端CID
 *  @param streamerPresenceState 采集端的在线状态
 */
- (void)onStreamer:(unsigned long long)streamerCID
     presenceState:(EN_RVS_STREAMER_PRESENCE_STATE)streamerPresenceState;


/**
 *  局域网内搜索采集端的结果反馈
 *
 *  @param streamerCID  搜索到的采集端CID
 *  @param streamerName 搜索到的采集端名称
 *  @param osType       搜索到的采集端系统类型
 */
- (void)onLanSearchStreamer:(unsigned long long)streamerCID
               streamerName:(NSString *)streamerName
                     oSType:(NSUInteger)osType;

@end

@interface RvsViewerInitHelper : NSObject

/**
 *  获取RvsViewerInitHelper对象
 */
+ (RvsViewerInitHelper *)viewerInitHelper;

@property (nonatomic, weak) id<RvsViewerInitHelperDelegate> delegate;

/**
 *  初始化Rvs SDK 工作环境
 *
 *  @param workPath   Rvs SDK 工作配置路径    如果为nil则采用默认
 *  @param cachePath  Rvs SDK 录像缓存路径    如果为nil则采用默认
 *  @param appVersion app版本号              如果为nil则采用默认
 *
 *  @return 0 代表成功，非0代表失败
 */
- (NSInteger)setViewerWithWorkPath:(NSString*)workPath cachePath:(NSString*)cachePath appVersion:(NSString*)appVersion;

/**
 *  设置授权信息
 *
 *  @param companyID  公司ID
 *  @param companyKey 公司key
 *  @param appID      应用ID
 *
 *  @return 0 代表成功，非0代表失败
 */
- (NSInteger)setLoginInfoWithCompanyID:(NSString*)companyID companyKey:(unsigned long long)companyKey appID:(NSString*)appID;

/**
 *  登陆到IChano云视频平台
 */
- (void)login;

/**
 * 退出应用时，请调用以释放资源
 */
- (void)logout;

/**
 *  是否输出log 默认是NO
 */
- (void)setLogEnabled:(BOOL)enable;

@end
