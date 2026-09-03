# WISEcode fork of CamerAwesome

Fork of [Apparence-io/CamerAwesome](https://github.com/Apparence-io/CamerAwesome)
maintained by WISEcode for changes upstream does not carry. It is consumed by our
Flutter apps as a git dependency pinned to a tag:

```yaml
camerawesome:
  git:
    url: https://github.com/wisecodeai/CamerAwesome.git
    ref: v2.5.0-wisecode.1
```

- **Branch `wisecode`** holds our changes. `master` mirrors upstream.
- **Base:** upstream commit `191ce9e`, which is byte-for-byte the pub.dev **2.5.0**
  release.
- **Tags:** `v<upstream version>-wisecode.<n>`. Bump `<n>` for every change to the
  fork and move every app to the new tag; apps never track the branch.

## Why

Upstream's iOS implementation opens the *physical* back wide-angle camera
(`AVCaptureDeviceTypeBuiltInWideAngleCamera`). A physical camera never changes
lens, so when a subject is closer than the wide camera's minimum focus distance
(about 15 cm on an iPhone 13, 20 cm on a 14 Pro, 25 cm on a 16 Pro) autofocus
parks at its near limit and the photo is soft. Apple's automatic close-up
("macro") switch to the ultra-wide camera only exists on the *virtual* devices
`builtInTripleCamera` and `builtInDualWideCamera`. Android already gets the
equivalent because CameraX opens the OEM's logical camera.

## Changes from upstream

iOS only; Android and the Dart layer are untouched. All in
`ios/camerawesome/Sources/camerawesome/CameraPreview/SingleCameraPreview/SingleCameraPreview.m`,
each marked with a `FORK` comment.

1. **Rear camera device selection** (`selectAvailableCamera:`) prefers
   `builtInTripleCamera`, then `builtInDualWideCamera`, then the physical
   wide-angle camera. Only virtual devices that contain the ultra-wide camera are
   considered, so `builtInDualCamera` (wide + telephoto) is deliberately skipped.
   Front camera selection is unchanged. An explicit `Sensor.id(...)` from Dart is
   still honoured as before.

2. **Default zoom on virtual devices** (`defaultVideoZoomFactor`,
   `applyDefaultVideoZoomFactor`). On a virtual device `videoZoomFactor = 1.0` is
   the ultra-wide field of view. After the session preset is configured the zoom is
   raised to the wide camera's switch-over factor (normally 2.0), which is the same
   framing the physical wide camera gave at 1x, so preview and stills look exactly
   as they did before. It only ever raises the zoom, so a value the user set is kept
   across preset changes.

3. **Zoom mapping** (`setZoom:`). The plugin's normalised 0..1 zoom now maps `0`
   to that default framing instead of to `1.0`, and the result is clamped to the
   device's available range. Dart callers see no change: `0` is still "no zoom".
   The ultra-wide field of view is not reachable through zoom; the system engages
   it on its own only for close focus and crops back to the requested framing.

4. **Preview connection limited to video ports** (`initCameraPreview:`). The manual
   `AVCaptureConnection` for the preview receives only the input's video ports. A
   no-op for the physical camera, which has one port; a guard for virtual device
   inputs that expose more.

Behaviour on devices without a macro-capable ultra-wide camera (iPhone 13, 14 and
15 non-Pro, SE) is identical to upstream apart from the device type: the virtual
device is opened but the system has no lens to fall back to.

## Updating from upstream

```bash
git fetch upstream
git checkout master && git merge --ff-only upstream/master && git push origin master
git checkout wisecode && git merge upstream/master   # or rebase onto the new release commit
```

Re-check the `FORK` blocks in `SingleCameraPreview.m`, update the base and tag
names in this file, tag `v<version>-wisecode.<n>`, and move the apps to it.
