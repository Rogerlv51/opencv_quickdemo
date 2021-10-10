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
	void colorReduce_demo1(Mat& src, Mat& dst, int div);  // ָ��������ض�����ɫ�����㷨���ٶ����
	void colorReduce_demo2(Mat& src, Mat& dst, int div);  // ��������ʽ����
	void tracking_bar_demo(Mat& image);    // ��������������
	void key_demo(Mat& img);       // ������Ӧ����
	void color_style_demo(Mat& img);    // ��ɫ���任
	void bitwise_demo(Mat& img);     // ͼ�����ص��߼�����
	void channels_demo(Mat& img);     // ͨ��������ϲ�
};