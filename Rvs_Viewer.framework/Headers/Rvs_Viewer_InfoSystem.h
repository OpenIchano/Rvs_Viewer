//
//  Rvs_Viewer_InfoSystem.h
//  Rvs_Viewer
//
//  Created by lvyi on 3/15/16.
//  Copyright © 2016 ifziv. All rights reserved.
//

#import <Foundation/Foundation.h>


typedef void (^DeviceToCIDBlock)(unsigned long long cid, NSError* error) ;


@interface Rvs_Viewer_InfoSystem : NSObject

- (void)cancelReuquest:(unsigned long long)requestId;


- (unsigned long long)getCID:(DeviceToCIDBlock)blk FromDeviceID:(NSString*)deviceId;

@end
