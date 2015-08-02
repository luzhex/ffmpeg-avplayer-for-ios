/*
 *  FFAVPlayerController.h
 *  This file is part of AVPlayerTouch framework.
 *
 *  Player obj-c wrapper class.
 *
 *  Created by iMoreApps on 2/24/2014.
 *  Copyright (C) 2014 iMoreApps Inc. All rights reserved.
 *  Author: imoreapps <imoreapps@gmail.com>
 */

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>

/**
 * AV player states
 **/
typedef enum {
  kAVPlayerStateInitialized=0,
  kAVPlayerStatePlaying,
  kAVPlayerStatePaused,
  kAVPlayerStateFinishedPlayback,
  kAVPlayerStateStoped,
  kAVPlayerStateUnknown=0xff
} AVPlayerState;

/**
 * AV stream discard option
 **/
typedef enum {
  kAVStreamDiscardOptionNone=0,
  kAVStreamDiscardOptionAudio=1,
  kAVStreamDiscardOptionVideo=2,
  kAVStreamDiscardOptionSubtitle=4,
} AVStreamDiscardOption;

/**
 * AV Options name
 *
 * Please be careful, you must know what you are doing,
 * the default option value is enough for the most situations.
 **/
extern NSString *const AVOptionNameAVFormatName;    // set input av format short name, such as "mjpeg", it's optional. Please reference the "showFormats" method of "FFAVParse" class.
extern NSString *const AVOptionNameAVProbeSize;     // set probing size (Must be an integer not lesser than 32, default is 5Mb)
extern NSString *const AVOptionNameAVAnalyzeduration;// Specify how many seconds are analyzed to probe the input. A higher value will enable detecting more accurate information, but will increase latency (It defaults to 5 seconds).

extern NSString *const AVOptionNameHttpUserAgent;   // (HTTP) override User-Agent header
extern NSString *const AVOptionNameHttpHeader;      // (HTTP) set custom HTTP headers
extern NSString *const AVOptionNameHttpContentType; // (HTTP) force a content type
extern NSString *const AVOptionNameHttpTimeout;     // (HTTP) set timeout of socket I/O operations
extern NSString *const AVOptionNameHttpMimeType;    // (HTTP) set MIME type
extern NSString *const AVOptionNameHttpCookies;     // (HTTP) set cookies to be sent in applicable future requests

@protocol FFAVPlayerControllerDelegate;
@class FFAVSubtitleItem;

/**
 * !!! FFAVPlayerController component is NOT thread-safe !!!
 **/
@interface FFAVPlayerController : NSObject

@property (nonatomic, readonly) NSURL *mediaURL;
@property (nonatomic, weak) id <FFAVPlayerControllerDelegate> delegate;

@property (nonatomic, assign) BOOL allowBackgroundPlayback;  // default NO
@property (nonatomic, assign) BOOL enableBuiltinSubtitleRender; // default YES

/**
 * "shouldAutoPlay" and "streamDiscardOption" properties
 * can only be changed before you open media.
 **/
@property (nonatomic, assign) BOOL shouldAutoPlay;          // default NO
@property (nonatomic, assign) AVStreamDiscardOption streamDiscardOption;  // default kAVStreamDiscardOptionNone

@property (nonatomic, readonly) NSInteger currentAudioTrack;
@property (nonatomic, readonly) NSArray *audioTracks;

@property (nonatomic, readonly) NSInteger currentSubtitleTrack;
@property (nonatomic, readonly) NSArray *subtitleTracks;

/**
 * Adjust contrast and saturation of the video display.
 * @contrast: 0.0 to 4.0, default 1.0
 * @saturation: 0.0 to 2.0, default 1.0
 **/
@property (nonatomic, assign) float contrast;
@property (nonatomic, assign) float saturation;

/*
 * Adjust the screen's brightness.
 */
@property (nonatomic, assign) float brightness;


/*
 * Convert ISO 639-1/2B/2T language code to full english name.
 * @langCode: ISO 639 language code.
 * @isLeft: YES - show negative symbol.
 * @return full english name of the ISO language code or "Unknown".
 */
+ (NSString *)convertISO639LanguageCodeToEnName:(NSString *)langCode;

/*
 * Format second to human readable time string.
 * @seconds: number of seconds
 * @isLeft: YES - show negative symbol.
 * @return formatted time string.
 */
+ (NSString *)formatTimeInterval:(CGFloat)seconds isLeft:(BOOL)isLeft;

/*
 * Init FFAVPlayerController object.
 * @If failed, return nil, otherwise return initialized FFAVPlayerController instance.
 */
- (id)init;

/*
 * Open media file at path.
 * @url - path to media source.
 * @options - A dictionary filled with AVFormatContext and demuxer-private options.
 * @If failed, return NO, otherwise return YES.
 */
- (BOOL)openMedia:(NSURL *)url withOptions:(NSDictionary *)options;

/*
 * Get drawable view object
 */
- (UIView *)drawableView;

/*
 * Enter or exit full screen mode.
 * @enter - YES to enter, NO to exit.
 * @This function does not return a value.
 */
- (void)fullScreen:(BOOL)enter;

/*
 * Determine AVPlayer whether or not is in full screen mode.
 * @If it is in full screen mode, return YES, otherwise return NO.
 */
- (BOOL)isFullscreen;

/*
 * Has Dolby Digital, audio, video, subtitle stream.
 * @If media has video or audio stream this function return YES, otherwise return NO.
 */
- (BOOL)hasDolby;
- (BOOL)hasAudio;
- (BOOL)hasVideo;
- (BOOL)hasSubtitle;

/*
 * Switch to special audio tracker
 * @index: index of the audio tracker.
 */
- (void)switchAudioTracker:(int)index;

/*
 * Switch to special subtitle stream
 * @index: index of the subtitle stream.
 */
- (void)switchSubtitleStream:(int)index;

/*
 * Open or close external subtitle file support.
 * @path: subtitle file path.
 * @encoding: encoding of the file.
 */
- (BOOL)openSubtitleFile:(NSString *)path encoding:(CFStringEncoding)encoding;
- (void)closeSubtitleFile;

/*
 * Set subtitle display font.
 * @font: subtitle font.
 */
- (void)setSubtitleFont:(UIFont *)font;

/*
 * Set subtitle text/background color.
 * @textColor: subtitle text color.
 * @backgroundColor: subtitle background color.
 */
- (void)setSubtitleTextColor:(UIColor *)textColor;
- (void)setSubtitleBackgroundColor:(UIColor *)backgroundColor;

/*
 * Query video frame size.
 * @This function return a CGSize value.
 */
- (CGSize)videoFrameSize;

/*
 * Query AVPlayer current state.
 * @This function return AVPlayer current state info.
 */
- (AVPlayerState)playerState;

/*
 * Query media total duration.
 * @This function return media total duration info.
 */
- (NSTimeInterval)duration;

/*
 * Query AVPlayer current playback time.
 * @This function return current playback time info.
 */
- (NSTimeInterval)currentPlaybackTime;

/*
 * Start playback.
 * @fact - playback start position, 0~1.0f
 * @If failed, return NO, otherwise return YES.
 */
- (BOOL)play:(double)fact;

/*
 * Fast forward.
 * @This function does not return a value.
 */
- (void)fastforward;

/*
 * Fast backward.
 * @This function does not return a value.
 */
- (void)fastbackward;

/*
 * Pause playback.
 * @This function does not return a value.
 */
- (void)pause;

/*
 * Resume playback.
 * @This function does not return a value.
 */
- (void)resume;

/*
 * Stop playback.
 * @This function does not return a value.
 */
- (void)stop;

/*
 * Seek to position.
 * @fact - 0~1.0f
 * @This function does not return a value.
 */
- (void)seekto:(double)fact;

/*
 * Enable real frame rate calculator.
 * @enable - YES to enable or NO to disable.
 * @This function does not return a value.
 */
- (void)enableCalcFramerate:(BOOL)enable;

/*
 * Get real frame rate.
 * @This function return real frame rate.
 */
- (int)framerate;

/*
 * Enable bit rate calculator.
 * @enable - YES to enable or NO to disable.
 * @This function does not return a value.
 */
- (void)enableCalcBitrate:(BOOL)enable;

/*
 * Get real bit rate.
 * @This function return real bit rate.
 */
- (int)bitrate;

/*
 * Get buffering progress.
 * @This function return buffering progress (0~1.0f).
 */
- (int)bufferingProgress;

/*
 * Get playback speed.
 * @This function return current playback speed (0.5~2.0f).
 */
- (float)playbackSpeed;

/*
 * Get playback speed.
 * @speed - new playback speed.
 * @This function does not return a value.
 */
- (void)setPlaybackSpeed:(float)speed;

/*
 * Volume control - GET.
 * @This function returns the current volume factor (0~1).
 */
+ (float)currentVolume;

/*
 * Volume control - SET.
 * @fact - volume factor (0~1).
 * @This function does not return a value.
 */
+ (void)setVolume:(float)fact;

/*
 * Audio session interruption handle.
 * began/ended interruption.
 * @This function does not return a value.
 */
- (void)beganInterruption;
- (void)endedInterruption;

@end


@protocol FFAVPlayerControllerDelegate

@optional

// will load av resource
- (void)FFAVPlayerControllerWillLoad:(FFAVPlayerController *)controller;

// did load av resource
// @error: nil indicates that loaded successfully.
//         non-nil indicates failure.
- (void)FFAVPlayerControllerDidLoad:(FFAVPlayerController *)controller error:(NSError *)error;

// state was changed
- (void)FFAVPlayerControllerDidStateChange:(FFAVPlayerController *)controller;

// current play time was changed
- (void)FFAVPlayerControllerDidCurTimeChange:(FFAVPlayerController *)controller position:(NSTimeInterval)position;

// current buffering progress was changed
- (void)FFAVPlayerControllerDidBufferingProgressChange:(FFAVPlayerController *)controller progress:(double)progress;

// current subtitle was changed
- (void)FFAVPlayerControllerDidSubtitleChange:(FFAVPlayerController *)controller subtitleItem:(FFAVSubtitleItem *)subtitleItem;

// enter or exit full screen mode
- (void)FFAVPlayerControllerDidEnterFullscreenMode:(FFAVPlayerController *)controller;
- (void)FFAVPlayerControllerDidExitFullscreenMode:(FFAVPlayerController *)controller;

@end
