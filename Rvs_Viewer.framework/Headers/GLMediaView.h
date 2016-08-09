//
//  Refactor_RTSPStreamRender.h
//  AtHomeCam
//
//  Created by Circlely Networks on 15/12/13.
//
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

extern NSString *KErrorStreamParam;
extern NSString *KErrorRecordingDomain;
extern NSString *KErrorStreamStatus;

typedef enum {
    PTZ_TYPE_RESET          = 0,
    PTZ_TYPE_PAN_HORIZONTAL = 1,
    PTZ_TYPE_PAN_VERTICAL   = 2,
    PTZ_TYPE_ZOOM           = 3,
    PTZ_TYPE_TAP_SINGLE     = 4
} PTZ_TYPE;

/**
 * 视频渲染方式
 *
 * RvsVideoRenderTypeFitCenter          居中最大化显示在View中间，并保持视频宽高比
 * RvsVideoRenderTypeFitXY              拉伸显示，跟View一样大
 * RvsVideoRenderTypeFitXYWithRatio     拉伸显示，按照原比例按最大宽高显示，超出部分不显示
 */
typedef enum : NSUInteger {
    RvsVideoRenderTypeFitCenter = 1,
    RvsVideoRenderTypeFitXY,
    RvsVideoRenderTypeFitXYWithRatio,
} RvsVideoRenderType;

typedef void (^RenderCompletionBlock)(NSDictionary *returnCode);
typedef void (^RenderFinishedBlock)(NSError *error);
typedef void (^RenderFailureBlock)(int error);
typedef void (^RenderTimeStampChangedBlock)(unsigned int timeStamp);
typedef void (^SaveCompletionBlock)(void);
typedef void (^SaveFailureBlock)(NSError *error);


/**
 *  手势控制IPC摄像头事件回调
 *  如果实现则调用否则采用默认处理方式
 */
@protocol GLMediaViewGestureDelegate <NSObject>

@optional
- (void)onPanGestureTrigger:(PTZ_TYPE)gesType withTranslation:(CGFloat)value;

@end


@interface GLMediaView : NSObject

@property (nonatomic, weak) id<GLMediaViewGestureDelegate> gestrueDelegate;

@property (nonatomic, assign) BOOL isScreenRotating;
@property (nonatomic, assign, readonly) NSUInteger streamWidth;
@property (nonatomic, assign, readonly) NSUInteger streamHeight;
@property (nonatomic, assign, readonly) BOOL isStreamRecording;
@property (nonatomic, assign, readonly) BOOL isAudioPlaying;
@property (nonatomic, assign, readonly) BOOL isAudioRecording;
@property (nonatomic, assign, readonly) BOOL isHighQuality;

/// 视频渲染方式
@property (nonatomic, assign) RvsVideoRenderType videoRenderType;

/**
 *  是否启用手势来垂直或水平方向移动IPC摄像头。
 */
@property (nonatomic, assign, getter = isEnableGestureMoveIPCamera) BOOL enableGestureMoveIPCamera;

@property (nonatomic, assign) UIColor* backgroundColor;

/**
 *  初始化一个实时视频流
 *
 *  @param cid         采集端CID
 *  @param cameraIndex 摄像头的index
 *  @param streamIndex 流的index
 *  @param targetView  展示view
 *
 *  @return GLMediaView *
 */
- (id)initRealTimeStreamWithCID:(unsigned long long)cid
                    CameraIndex:(int)cameraIndex
                    StreamIndex:(int)streamIndex
                     TargetView:(UIView *)targetView;

/**
 *  初始化一个已录制视频流
 *
 *  @param cid        采集端CID
 *  @param fileName   视频名称
 *  @param targetView 展示view
 *
 *  @return GLMediaView *
 */
- (id)initRecordStreamStreamWithCID:(unsigned long long)cid
                           FileName:(NSString *)fileName
                         TargetView:(UIView *)targetView;

/**
 *  初始化一个云端视频流
 *
 *  @param cid        采集端CID
 *  @param eid        视频eid
 *  @param targetView 展示view
 *
 *  @return GLMediaView *
 */
- (id)initCloudStreamWithCID:(unsigned long long)cid
                         EID:(NSString *)eid
                  TargetView:(UIView *)targetView;

/**
 *  开始视频播放
 *
 *  @param streamChannelCreatedBlock 创建完成block
 *  @param firstVideoFrameShowBlock  获得第一帧视频回调block
 *  @param playEndedBlock            播放结束回调block
 */
-(void)startStreamOnStreamChannelCreated:(RenderCompletionBlock)streamChannelCreatedBlock
                     FirstVideoFrameShow:(RenderCompletionBlock)firstVideoFrameShowBlock
                               PlayEnded:(RenderFinishedBlock)playEndedBlock;
/**
 *  开始视频播放
 *
 *  @param streamChannelCreatedBlock 创建完成block
 *  @param firstVideoFrameShowBlock  获得第一帧视频回调block
 *  @param playEndedBlock            播放结束回调block
 *  @param timeStampChangedBlock     时间轴回调block
 */
-(void)startStreamOnStreamChannelCreated:(RenderCompletionBlock)streamChannelCreatedBlock
                     FirstVideoFrameShow:(RenderCompletionBlock)firstVideoFrameShowBlock
                               PlayEnded:(RenderFinishedBlock)playEndedBlock
                        TimeStampChanged:(RenderTimeStampChangedBlock)timeStampChangedBlock;

/**
 *  切换播放流
 *
 *  @param cid                       采集端CID
 *  @param cameraIndex               摄像头的index
 *  @param streamIndex               流的index
 *  @param streamChannelCreatedBlock 创建成功回调block
 *  @param firstVideoFrameShowBlock  获得第一帧画面回调block
 *  @param playEndedBlock            播放结束回调block
 */
-(void)switchStreamWithCID:(unsigned long long)cid
               CameraIndex:(int)cameraIndex
               StreamIndex:(int)streamIndex
    OnStreamChannelCreated:(RenderCompletionBlock)streamChannelCreatedBlock
       FirstVideoFrameShow:(RenderCompletionBlock)firstVideoFrameShowBlock
                 PlayEnded:(RenderFinishedBlock)playEndedBlock;


/**
 *  暂停录像播放
 */
- (void)pauseRecordStream;

/**
 *  继续视频
 */
- (void)resumeRecordStream;

/**
 *  滑动滑块
 */
- (void)moveRecordStreamToTimePoint:(unsigned int)milliSecond;

/**
 *  结束视频采集
 */
- (void)stopStream;

/**
 *  激活voice，一般在拿到第一帧画面时调用
 */
- (void)activateVoice;

/**
 *  开始讲话
 */
- (void)startTalk;

/**
 *  结束讲话
 */
- (void)stopTalk;

/**
 *  开始静音
 */
- (void)startMute;

/**
 *  结束静音
 */
- (void)stopMute;

/**
 *  截取一张本地流图片
 *
 */
- (UIImage *)caputreVideoImage;

/**
 *  保存一张图片到相册
 *
 *  @param image           要保存的图片
 *  @param image           要保存的相册文件夹名称
 *  @param completionBlock 保存成功回调block
 *  @param failureBlock    保存失败回调block
 */
- (void)saveImageToLocalAlbum:(UIImage *)image
                         path:(NSString *)path
          WithCompletionBlock:(SaveCompletionBlock)completionBlock
                 FailureBlock:(SaveFailureBlock)failureBlock;


/**
 *  开始录制视频
 *
 *  @param filePath 录制文件名，需要以.mp4结尾
 */
- (BOOL)startRecordAtPath:(NSString *)filePath;

/**
 *  结束视频录制
 *
 *  @param completionBlock 录制完成回调block
 *  @param failureBlock    录制失败回调block
 */
- (void)stopRecordWithCompletionBlock:(RenderCompletionBlock)completionBlock
                        failureBlock:(RenderFailureBlock)failureBlock;
/**
 *  视频旋转
 *
 *  @param completionBlock 旋转完成回调block
 *  @param failureBlock    旋转失败回调block
 */
- (void)cameraRotateWithCompletionBlock:(RenderCompletionBlock)completionBlock
                           FailureBlock:(RenderFailureBlock)failureBlock;

/**
 *  切换摄像头
 *
 *  @param completionBlock 切换成功回到block
 *  @param failureBlock    切换失败回调block
 */
- (void)cameraSwitchWithCompletionBlock:(RenderCompletionBlock)completionBlock
                           FailureBlock:(RenderFailureBlock)failureBlock;

/**
 *  切换闪光灯
 */
- (void)torchSwitchWithCompletionBlock:(RenderCompletionBlock)completionBlock
                           FailureBlock:(RenderFailureBlock)failureBlock;

/**
 *  针对安卓黑白图像
 */
- (void)colorModeSwitchWithCompletionBlock:(RenderCompletionBlock)completionBlock
                           FailureBlock:(RenderFailureBlock)failureBlock;

/**
 *  PTZ流
 */
- (void)PTZMoveCtrlWithPTZType:(PTZ_TYPE)ptztype
                  PTZDirection:(CGFloat)direction
              CompletionBlock:(RenderCompletionBlock)completionBlock
                 FailureBlock:(RenderFailureBlock)failureBlock;


/**
 *  切换画质
 */
- (void)QualitySwitchWithQuality:(BOOL)bHD
                 CompletionBlock:(RenderCompletionBlock)completionBlock
                    FailureBlock:(RenderFailureBlock)failureBlock;

/**
 *  请求第一帧IDR
 */
- (void)forceIFrame;

@end
