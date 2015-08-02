/*
 *  FFAVParser.h
 *  This file is part of AVPlayerTouch framework.
 *
 *  AV parser & thumbnail generating obj-c wrapper class.
 *
 *  Created by iMoreApps on 2/25/2014.
 *  Copyright (C) 2014 iMoreApps Inc. All rights reserved.
 *  Author: imoreapps <imoreapps@gmail.com>
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

@class FFAVSubtitle;
@class FFAVSubtitleItem;

@interface FFAVParser : NSObject

@property (nonatomic, readonly) NSString *path;
@property (readonly, nonatomic) NSTimeInterval duration;
@property (readonly, nonatomic) NSUInteger frameWidth;
@property (readonly, nonatomic) NSUInteger frameHeight;
@property (readonly, nonatomic) NSUInteger numberOfSubtitleStreams;

/*
 * show supported protocols, formats, decoders, encoders info.
 */
+ (void)showProtocols;
+ (void)showFormats;
+ (void)showDecoders;
+ (void)showEncoders;

/*
 * open av source
 * return YES if success, otherwise return NO.
 */
- (BOOL)open:(NSString *)path;

/*
 * determine whether or not has audio and video stream.
 * return YES or NO.
 */
- (BOOL)hasAudio;
- (BOOL)hasVideo;
- (BOOL)hasSubtitle;

/*
 * generate thumbnail at specified timestamp
 * return an UIImage object if success, otherwise return nil.
 */
- (UIImage *)thumbnailAtTime:(NSTimeInterval)seconds;

/*
 * parse subtitle stream and external subtitle file.
 * return a FFAVSubtitle object that contains a subtitle details,
 * such as start, end time and subtitle text. If subtitle stream is a picture based subtitle type,
 * then returns nil FFAVSubtitle object.
 * "fps" default value is 60.
 */
+ (FFAVSubtitle *)parseSubtitleFile:(NSString *)path
                           encoding:(NSStringEncoding)encoding
                          frameRate:(double)fps;
- (FFAVSubtitle *)parseSubtitleStreamAtIndex:(NSInteger)streamIndex encoding:(NSStringEncoding)encoding; // streamIndex < self.numberOfSubtitleStreams

@end


@interface FFAVSubtitle : NSObject
@property (nonatomic, strong, readonly) NSDictionary *metadata;
@property (nonatomic, strong, readonly) NSArray *items; // FFAVSubtitleItem list
@end

@interface FFAVSubtitleItem : NSObject
@property (nonatomic, readonly) long long startTime;  // in millisecond
@property (nonatomic, readonly) long long duration;   // in millisecond
@property (nonatomic, strong, readonly) NSString *text;
@end
