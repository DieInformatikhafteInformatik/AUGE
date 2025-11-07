#include <iostream>
#include <memory>
#include <functional>

#include <opencv2/core.hpp>
#include <opencv2/highgui.hpp>

#include "command.h"
#include "stringutils.h"
#include "auge.h"

int main()
{
    std::cout << "Willkommen!!!" << std::endl;
    cv::VideoCapture cap(0);
    if(!cap.isOpened())
    {
        std::cerr << "Fehler: Kamera kann nicht geöffnet werden!" << std::endl;
        return -1;
    }

    cv::Mat frame;
    while(true)
    {
        cap >> frame;
        if(frame.empty())
        {
            std::cerr << "Fehler: Frame ist leer!" << std::endl;
            break;
        }

        cv::imshow("Kamera", frame);
        if((char) cv::waitKey(30) == 'q')
        {
            break;
        }
    }

    cap.release();
    cv::destroyAllWindows();
}