#pragma once
#include <opencv2/opencv.hpp>
#include <thread>
#include <mutex>
#include <memory>
#include <atomic>
#include <unistd.h>

/**
 *  this class overides all 
 *  constructors presents and some methods in
 *  cv::VideoCapture class 
 *  https://docs.opencv.org/3.4/d8/dfe/classcv_1_1VideoCapture.html
 *  Also adds some thread features
 **/

class ParallelVideoCapture : public cv::VideoCapture
{
    public:
        
        ParallelVideoCapture() = delete;
        
        ParallelVideoCapture(int index, int fps = 30);
        
        ParallelVideoCapture(const cv::String &filename, int fps = 30);
        
        ParallelVideoCapture(const cv::String &filename, int apiPreference,  int fps = 30);

        ~ParallelVideoCapture();
        
        void startCapture();

        void stopCapture();

        bool isRunning() const;
        
        bool isOpened() const;

        friend void captureFromSource(ParallelVideoCapture & cap);

        uint8_t getIntervalMs() const;

        bool read(); // thread safe method for read image from src

        bool read(cv::OutputArray image);

        bool grab(); // base class method

        bool retrieve(cv::OutputArray image, int flag=0); // base class method

        bool retrieve(int flags=0); // thread safe method for retrieve image from src

        void release(); 

        cv::Mat getFrame();
        

    private:

        std::unique_ptr<std::thread> thread_ptr_;

        std::mutex mutex_;  

        std::atomic<bool> running_;

        cv::Mat frame_;

        uint8_t fps_;

        uint8_t interval_ms_;
};

void captureFromSource(ParallelVideoCapture & cap);