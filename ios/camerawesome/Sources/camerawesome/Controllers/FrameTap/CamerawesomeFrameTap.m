//
//  CamerawesomeFrameTap.m
//  camerawesome
//
//  FORK: see CamerawesomeFrameTap.h.
//

#import "CamerawesomeFrameTap.h"

@implementation CamerawesomeFrameTap

static __weak id<CamerawesomeFrameSink> _sink;

+ (id<CamerawesomeFrameSink>)sink {
  return _sink;
}

+ (void)setSink:(id<CamerawesomeFrameSink>)sink {
  _sink = sink;
}

@end
