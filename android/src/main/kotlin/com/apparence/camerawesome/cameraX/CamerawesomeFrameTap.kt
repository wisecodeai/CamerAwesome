package com.apparence.camerawesome.cameraX

import androidx.camera.core.ImageProxy

/**
 * FORK: lets another native plugin read the frames of the running
 * single-camera session, so a second consumer (a barcode SDK) can share the
 * camera instead of opening it itself.
 *
 * The analysis use case that feeds the sink is bound only when a sink is set
 * at the time the camera binds its use cases, so set it before the camera
 * starts. Frames are `YUV_420_888`; the plugin closes each one after [sink]
 * returns, so the sink must copy what it needs synchronously.
 */
object CamerawesomeFrameTap {
    @Volatile
    var sink: ((ImageProxy) -> Unit)? = null
}
