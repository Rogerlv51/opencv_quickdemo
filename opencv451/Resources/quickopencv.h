#pragma once
#include <opencv2/opencv.hpp>


using namespace cv;

class QuickDemo
{
public:
	void colorspace_demo(Mat& img);
	void mat_creation_demo(Mat& img);
	void pixel_visit_demo(Mat& img);
	void operators_demo(Mat& img);
	void colorReduce_demo1(Mat& src, Mat& dst, int div);  // 指针访问像素对象，颜色缩减算法，速度最快
	void colorReduce_demo2(Mat& src, Mat& dst, int div);  // 迭代器方式访问
	void tracking_bar_demo(Mat& image);    // 滚动条滑动操作
	void key_demo(Mat& img);       // 键盘响应操作
	void color_style_demo(Mat& img);    // 颜色风格变换
	void bitwise_demo(Mat& img);     // 图像像素的逻辑操作
	void channels_demo(Mat& img);     // 通道分离与合并
};