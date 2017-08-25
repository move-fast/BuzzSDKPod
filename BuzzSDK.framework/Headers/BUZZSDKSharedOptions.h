//
//  BUZZSDKOptions.h
//  AdDeckSDK
//
//  Created by mdv on 09/02/16.
//  Copyright © 2016 Move Fast UG. All rights reserved.
//

#import <Foundation/Foundation.h>

#import "BUZZSDKOptions.h"

@interface BUZZSDKSharedOptions : NSObject

+ (void)setSDKOptions:(NSDictionary *)options;
+ (id)optionForKey:(NSString *)key;

@end
