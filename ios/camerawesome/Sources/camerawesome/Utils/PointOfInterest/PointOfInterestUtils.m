//
//  PointOfInterestUtils.m
//  camerawesome
//
//  FORK (WISEcode): see PointOfInterestUtils.h and FORK.md.
//

#import "PointOfInterestUtils.h"

@implementation PointOfInterestUtils

+ (CGPoint)devicePointForViewPoint:(CGPoint)viewPoint
                       orientation:(UIDeviceOrientation)orientation
                          mirrored:(BOOL)mirrored {
  CGFloat x = MIN(MAX(viewPoint.x, 0.0), 1.0);
  CGFloat y = MIN(MAX(viewPoint.y, 0.0), 1.0);
  
  // A mirrored preview shows the frame flipped left-to-right, so undo the flip
  // before rotating into sensor space.
  if (mirrored) {
    x = 1.0 - x;
  }
  
  // Same mapping as Flutter's camera_avfoundation plugin. The sensor image is
  // landscape; a portrait preview is that image turned 90 degrees, so the axes
  // swap. Only the centre point is unchanged by the transform.
  switch (orientation) {
    case UIDeviceOrientationPortraitUpsideDown:
      return CGPointMake(1.0 - y, x);
    case UIDeviceOrientationLandscapeRight:
      return CGPointMake(1.0 - x, 1.0 - y);
    case UIDeviceOrientationLandscapeLeft:
      return CGPointMake(x, y);
    case UIDeviceOrientationPortrait:
    case UIDeviceOrientationFaceUp:
    case UIDeviceOrientationFaceDown:
    case UIDeviceOrientationUnknown:
    default:
      return CGPointMake(y, 1.0 - x);
  }
}

@end
