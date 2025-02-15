package com.hapi.pixelfree_android

import android.os.Bundle
import android.widget.Button
import androidx.appcompat.app.AppCompatActivity
import com.hapi.pixelfree.*
import com.hapi.avcapture.FrameCall
import com.hapi.avcapture.HapiTrackFactory
import com.hapi.avparam.VideoFrame
import com.hapi.avrender.HapiCapturePreView
import com.hapi.pixelfreeuikit.PixeBeautyDialog
import java.nio.ByteBuffer
import java.util.concurrent.CountDownLatch

class MainActivity : AppCompatActivity() {

    private val mPixelFree by lazy {
        PixelFree()
    }
    private val mPixeBeautyDialog by lazy {
        PixeBeautyDialog(mPixelFree)
    }
    val hapiCapturePreView by lazy { findViewById<HapiCapturePreView>(R.id.preview) }

    //摄像头轨道
    private val cameTrack by lazy {
        HapiTrackFactory.createCameraXTrack(this, this, 720, 1280).apply {
            frameCall = object : FrameCall<VideoFrame> {
                //帧回调
                override fun onFrame(frame: VideoFrame) {
                }

                override fun onProcessFrame(frame: VideoFrame): VideoFrame {
                    if (mPixelFree.isCreate()) {
                        val pxInput = PFIamgeInput().apply {
                            wigth = frame.width
                            height = frame.height
                            p_data0 = frame.data
                            p_data1 = frame.data
                            p_data2 = frame.data
                            stride_0 = frame.rowStride
                            stride_1 = frame.rowStride
                            stride_2 = frame.rowStride
                            format = PFDetectFormat.PFFORMAT_IMAGE_RGBA
                            rotationMode = PFRotationMode.PFRotationMode90
                        }
                        mPixelFree.processWithBuffer(pxInput)
                        frame.textureID = pxInput.textureID
                    }
                    return super.onProcessFrame(frame)
                }
            }
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        setContentView(R.layout.activity_main)
        cameTrack.playerView = hapiCapturePreView
        cameTrack.start()

        hapiCapturePreView.mHapiGLSurfacePreview.mOpenGLRender.glCreateCall = {
            //在绑定上下文后初始化
            mPixelFree.create()
            val authData = mPixelFree.readBundleFile(this@MainActivity, "pixelfreeAuth.lic")
            mPixelFree.auth(this.applicationContext, authData, authData.size)
            val face_fiter =
                mPixelFree.readBundleFile(this@MainActivity, "face_fiter.bundle")
            mPixelFree.createBeautyItemFormBundle(
                face_fiter,
                face_fiter.size,
                PFSrcType.PFSrcTypeFilter
            )
            val face_detect =
                mPixelFree.readBundleFile(this@MainActivity, "face_detect.bundle")

            mPixelFree.createBeautyItemFormBundle(
                face_detect,
                face_detect.size,
                PFSrcType.PFSrcTypeDetect
            )
        }
        findViewById<Button>(R.id.showBeauty).setOnClickListener {
            mPixeBeautyDialog.show(supportFragmentManager, "")
        }
    }

    override fun onDestroy() {
        mPixelFree.release()
        super.onDestroy()
    }
}