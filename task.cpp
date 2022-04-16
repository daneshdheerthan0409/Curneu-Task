#ifdef CAFFE

    cv::Mat inputBlob = cv::dnn::blobFromImage(frameOpenCVDNN, inScaleFactor, cv::Size(inWidth, inHeight), meanVal, false, false);

#else

    cv::Mat inputBlob = cv::dnn::blobFromImage(frameOpenCVDNN, inScaleFactor, cv::Size(inWidth, inHeight), meanVal, true, false);

#endif

 

net.setInput(inputBlob, "data");

cv::Mat detection = net.forward("detection_out");

 

cv::Mat detectionMat(detection.size[2], detection.size[3], CV_32F, detection.ptr<float>());

 

for(int i = 0; i &lt; detectionMat.rows; i++)

{

    float confidence = detectionMat.at&lt;float&gt;(i, 2);

 

    if(confidence &gt; confidenceThreshold)

    {

        int x1 = static_cast<int>(detectionMat.at<float>(i, 3) * frameWidth);

        int y1 = static_cast<int>(detectionMat.at<float>(i, 4) * frameHeight);

        int x2 = static_cast<int>(detectionMat.at<float>(i, 5) * frameWidth);

        int y2 = static_cast<int>(detectionMat.at<float>(i, 6) * frameHeight);

 

        cv::rectangle(frameOpenCVDNN, cv::Point(x1, y1), cv::Point(x2, y2), cv::Scalar(0, 255, 0),2, 4);

    }

}