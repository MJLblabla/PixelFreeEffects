//
//  pixelFree_c.hpp
//  PixelFree
//
//  Created by mumu on 2021/9/22.
//

#ifndef pixelFree_c_hpp
#define pixelFree_c_hpp

#include <stdio.h>
#if defined(_WIN32)
#ifdef PF_BUILD_SHARED_LIB
#define PF_CAPI_EXPORT __declspec(dllexport)
#else
#define PF_CAPI_EXPORT
#endif
#else
#define PF_CAPI_EXPORT __attribute__((visibility("default")))
#endif  // _WIN32

#ifdef __cplusplus
extern "C" {
#endif

typedef enum PFDetectFormat{
    PFFORMAT_UNKNOWN = 0,
    PFFORMAT_IMAGE_RGB = 1,
    PFFORMAT_IMAGE_BGR = 2,
    PFFORMAT_IMAGE_RGBA = 3,
    PFFORMAT_IMAGE_BGRA = 4,
    PFFORMAT_IMAGE_ARGB = 5,
    PFFORMAT_IMAGE_ABGR = 6,
    PFFORMAT_IMAGE_GRAY = 7,
    PFFORMAT_IMAGE_YUV_NV12 = 8,
    PFFORMAT_IMAGE_YUV_NV21 = 9,
    PFFORMAT_IMAGE_YUV_I420 = 10,
} PFDetectFormat;

typedef enum PFRotationMode{
  PFRotationMode0 = 0,
  PFRotationMode90 = 1,
  PFRotationMode180 = 2,
  PFRotationMode270 = 3,
} PFRotationMode;

typedef enum PFSrcType{
    PFSrcTypeFilter = 0,
    PFSrcTypeDetect = 1,
    PFSrcTypeAuthFile = 2,
} PFSrcType;

typedef struct {
    const char* modelPath;
    const char* runCachePath;
} PFDetectPath;

typedef struct {

  int textureID;
  int wigth;
  int height;
  void* p_data0;// Y or rgba
  void* p_data1;
  void* p_data2;
  int stride_0;
  int stride_1;
  int stride_2;
    
  PFDetectFormat format;
  PFRotationMode rotationMode;
} PFIamgeInput;

typedef struct {

  char *imagePath;
} PFFiter;

/* 美颜类型 */
typedef enum PFBeautyFiterType{
    PFBeautyFiterTypeFace_EyeStrength = 0,
    //瘦脸
    PFBeautyFiterTypeFace_thinning,
    //窄脸
    PFBeautyFiterTypeFace_narrow,
    //下巴
    PFBeautyFiterTypeFace_chin,
    //v脸
    PFBeautyFiterTypeFace_V,
    //small
    PFBeautyFiterTypeFace_small,
    //鼻子
    PFBeautyFiterTypeFace_nose,
    //额头
    PFBeautyFiterTypeFace_forehead,
    //嘴巴
    PFBeautyFiterTypeFace_mouth,
    //人中
    PFBeautyFiterTypeFace_philtrum,
    //长鼻
    PFBeautyFiterTypeFace_long_nose = 10,
    //眼距
    PFBeautyFiterTypeFace_eye_space,
    //磨皮
    PFBeautyFiterTypeFaceBlurStrength,
    //美白
    PFBeautyFiterTypeFaceWhitenStrength,
    //红润
    PFBeautyFiterTypeFaceRuddyStrength,
    //锐化
    PFBeautyFiterTypeFaceSharpenStrength,
    //新美白算法
    PFBeautyFiterTypeFaceM_newWhitenStrength,
    //画质增强
    PFBeautyFiterTypeFaceH_qualityStrength,
    
    PFBeautyFiterName,
    PFBeautyFiterStrength,
    PFAppBundleId //
    
} PFBeautyFiterType;


PF_CAPI_EXPORT extern const char* PF_Version();


typedef struct PFPixelFree PFPixelFree;

PF_CAPI_EXPORT extern void PF_VLogSetLevel(PFPixelFree* pixelFree,int level,char *path);

PF_CAPI_EXPORT extern PFPixelFree* PF_NewPixelFree();

PF_CAPI_EXPORT extern void PF_DeletePixelFree(PFPixelFree* pixelFree);

//目前仅支持双输入。GPU 纹理由于渲染，cpu buffer 用检测
PF_CAPI_EXPORT extern void PF_processWithBuffer(PFPixelFree* pixelFree,PFIamgeInput inputImage);

PF_CAPI_EXPORT extern void PF_pixelFreeSetBeautyFiterParam(PFPixelFree* pixelFree, PFBeautyFiterType key,void *value);
PF_CAPI_EXPORT extern void PF_createBeautyItemFormBundle(PFPixelFree* pixelFree, void *data,int size,PFSrcType type);
#ifdef __cplusplus
}
#endif
#endif /* pixelFree_c_hpp */
