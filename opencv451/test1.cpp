#include <opencv2/opencv.hpp>
#include <iostream>
#include "Resources/quickopencv.h"


using namespace std;
using namespace cv;

void main()
{
	String path = "Resources/7080ab5bgy1gs9dm8cl69j20j60nwn4c.jpg";
	Mat img = imread(path);
	Mat dst;
	namedWindow("window1", WINDOW_FREERATIO);  // �����������ڴ��ڴ�Сģʽ
	imshow("window1", img);  // ����һ��Ҫ��namedWindow��ͬ����Ȼ��д������������
	double time0 = static_cast<double>(getTickCount());  // ��¼��������ʱ�ӿ�ʼ
	QuickDemo qd;
	//qd.colorspace_demo(img);
	//qd.mat_creation_demo(img);
	//qd.pixel_visit_demo(img);
	//qd.operators_demo(img);
	//qd.colorReduce_demo1(img, dst, 32);
	//qd.colorReduce_demo2(img, dst, 32);
	//qd.tracking_bar_demo(img);
	//qd.key_demo(img);
	//qd.color_style_demo(img);
	//qd.bitwise_demo(img);
	//qd.channels_demo(img);
	
	//namedWindow("window2", WINDOW_FREERATIO);
	//imshow("window2", dst);
	time0 = ((double)getTickCount() - time0) / getTickFrequency();
	cout << "����ʱ��Ϊ�� " << time0 << "��" << endl;
	waitKey(0);
	destroyAllWindows();
}
