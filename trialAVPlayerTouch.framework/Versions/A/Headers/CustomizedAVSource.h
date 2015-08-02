//
//  CustomizedAVSource.h
//  AVPlayerTouch
//
//  Created by apple on 15/6/25.
//  Copyright (c) 2015年 apple. All rights reserved.
//

#import <Foundation/Foundation.h>

@protocol CustomizedAVSource <NSObject>
@required

// translate URI
+ (NSString *)translateURLStringToPath:(NSString *)urlString;

// last error
- (NSError *)lastError;

// open/close av source
- (BOOL)open:(NSString *)uri;
- (void)close;

// query the file size info
- (unsigned long long)fileSize;

// read data from av source
- (unsigned int)read:(void *)buffer size:(unsigned int)size;

// seek av source
- (unsigned long long)seekto:(long long)offset whence:(int)whence;
@end


// Customized av source store
@interface CustomizedAVSourceStore : NSObject
+ (instancetype)sharedInstance;

#pragma mark - AVSource Class Store

// register an av source class for url scheme
- (void)registerAVSourceClass:(Class)avsourceClass forScheme:(NSString *)scheme;

// unregister an av source class for url scheme
- (void)unregisterAVSourceClassWithScheme:(NSString *)scheme;

// query an av source class for url scheme
- (Class)avsourceClassForScheme:(NSString *)scheme;

#pragma mark - URL Context Store

// register av source context for an url key
- (void)registerAVSourceURLContext:(id)context forURLKey:(id)key;

// unregister av source context for an url key
- (void)unregisterAVSourceURLContextWithURLKey:(id)key;

// query av source context for an url key
- (id)avsourceURLContextForURLKey:(id)key;

// clear all av source contexts
- (void)clearAllAVSourceURLContexts;
@end