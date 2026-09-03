//
//  PointOfInterestUtils.h
//  camerawesome
//
//  FORK (WISEcode): converts a tap on the preview into AVFoundation's
//  point-of-interest space. See FORK.md.
//

#import <Foundation/Foundation.h>
#import <UIKit/UIKit.h>
#import <CoreGraphics/CoreGraphics.h>

NS_ASSUME_NONNULL_BEGIN

@interface PointOfInterestUtils : NSObject

/// Maps a point normalised against the preview as the user sees it (0,0 top-left,
/// 1,1 bottom-right) to AVFoundation's focus / exposure point-of-interest space,
/// which is normalised against the sensor image held landscape with the home
/// button or charging port on the right.
///
/// `orientation` is the physical device orientation the preview is shown in.
/// Face up, face down and unknown are treated as portrait, since the preview
/// connection is fixed to portrait and a phone held flat over a subject is the
/// usual close-up case. `mirrored` is YES when the preview connection mirrors the
/// frame horizontally, as the front camera does.
+ (CGPoint)devicePointForViewPoint:(CGPoint)viewPoint
                       orientation:(UIDeviceOrientation)orientation
                          mirrored:(BOOL)mirrored;

@end

NS_ASSUME_NONNULL_END
