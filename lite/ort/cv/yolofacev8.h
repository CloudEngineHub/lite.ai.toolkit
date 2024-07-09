//
// Created by ai-test1 on 24-7-8.
//

#ifndef LITE_AI_TOOLKIT_YOLOFACEV8_H
#define LITE_AI_TOOLKIT_YOLOFACEV8_H
#include "lite/ort/core/ort_core.h"
#include "algorithm"
#include <vector>



namespace ortcv{
    class LITE_EXPORTS YoloFaceV8 : public BasicOrtHandler{
    public:
        explicit YoloFaceV8(const std::string &_onnx_path, unsigned int _num_threads = 1) :
                BasicOrtHandler(_onnx_path, _num_threads)
        {};
        ~YoloFaceV8() override = default;

    private:
        // 归一化的值
        float mean = -127.5 / 128.0;
        float scale = 1 / 128.0;
        const float conf_threshold = 0.5f;
        const float iou_threshold = 0.4f;
        float ratio_width;
        float ratio_height;


    private:
        // 需要被重写的方法
        Ort::Value transform(const cv::Mat &mat_rs) override;

        float GetIoU(const lite::types::Bbox box1, const lite::types::Bbox box2);

        std::vector<int> nms(std::vector<lite::types::Bbox> boxes, std::vector<float> confidences, const float nms_thresh);

        cv::Mat normalize(cv::Mat srcImg);

        void generate_box(std::vector<Ort::Value> &ort_outputs,std::vector<lite::types::Bbox> &boxes);


    public:
        // 请保持detect、detect_video等的命名规范，detect是图片级别的检测接口，detect_video是视频级别的检测接口
        void detect(const cv::Mat &mat,std::vector<lite::types::Bbox> &boxes);
    };
}


#endif //LITE_AI_TOOLKIT_YOLOFACEV8_H
