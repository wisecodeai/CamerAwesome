//
//  CamerawesomeFrameTap.h
//  camerawesome
//
//  FORK: lets another native plugin read the preview frames of the running
//  single-camera session, so a second consumer (a barcode SDK) can share the
//  camera instead of opening it itself.
//

#import <AVFoundation/AVFoundation.h>
#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

@protocol CamerawesomeFrameSink <NSObject>

/// Called for every frame the preview receives, on the queue the video data
/// output delivers on (the main queue). The buffer is only valid for the
/// duration of the call: retain it to use it later. Keep this fast; do any real
/// work on another queue.
///
/// The pixel format is the preview's, `kCVPixelFormatType_32BGRA`.
- (void)camerawesomeDidOutputSampleBuffer:(CMSampleBufferRef)sampleBuffer
                                   device:(AVCaptureDevice *)device;

@end

@interface CamerawesomeFrameTap : NSObject

/// The registered sink, held weakly. Set to nil to stop receiving frames.
@property(class, nonatomic, weak, nullable) id<CamerawesomeFrameSink> sink;

@end

NS_ASSUME_NONNULL_END
