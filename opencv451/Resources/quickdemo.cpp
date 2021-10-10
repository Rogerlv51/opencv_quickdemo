#include <quickopencv.h>
#include <iostream>

using namespace cv;
using namespace std;

void QuickDemo::colorspace_demo(Mat &img) {
	Mat gray, hsv;
	cvtColor(img, gray, COLOR_BGR2GRAY);
	cvtColor(img, hsv, COLOR_BGR2HSV);
	namedWindow("window2", WINDOW_FREERATIO);
	namedWindow("window3", WINDOW_FREERATIO);
	imshow("window2", gray);
	imshow("window3", hsv);
	imwrite("C:/Users/94960/Desktop/gray.png", gray);
	imwrite("C:/Users/94960/Desktop/hsv.png", hsv);
}

// 进行一些mat操作
void QuickDemo::mat_creation_demo(Mat &img) {
	Mat m1, m2;
	m1 = img.clone(); // 两种克隆方式，浅拷贝，如果直接赋值则会是深拷贝，一个变了全都变
	img.copyTo(m2);
	// 创建空的Mat图像
	Mat m3 = Mat::zeros(Size(8, 8), CV_8UC3);  //8位3通道空白图像, ones是全1
	m3 = Scalar(255, 0, 0); //3通道赋值
	cout << "width: " << m3.cols << "  height: " << m3.rows << "  channels: " << m3.channels() << endl;
	cout << m3 << endl;  // IO输出
	namedWindow("创建图像", WINDOW_FREERATIO);
	imshow("创建图像", m3);

	Mat m4 = m3;
	m4 = Scalar(0, 0, 255);  // 相当于深拷贝，一个变全都变
	namedWindow("直接用等号赋值", WINDOW_FREERATIO);
	imshow("直接用等号赋值", m3);

}


void QuickDemo::pixel_visit_demo(Mat& img) {
	// 处理图像中单个像素点函数，赋值操作
	int w = img.cols;
	int h = img.rows;
	int dims = img.channels();
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			if (dims == 1) {  // 处理单通道灰度图像
				int pv = img.at<uchar>(row, col);  // 一个点有8位数据即一个字节uchar
				img.at<uchar>(row, col) = 255 - pv;   // 一个赋值操作，实际上就是取反(反色)
			}
			if (dims == 3) {
				Vec3b bgr = img.at<Vec3b>(row, col); 
				img.at<Vec3b>(row, col)[0] = 255 - bgr[0];   // 同样的赋值操作
				img.at<Vec3b>(row, col)[1] = 255 - bgr[1];
				img.at<Vec3b>(row, col)[2] = 255 - bgr[2];
			}
		}
	}
	namedWindow("像素读写显示", WINDOW_FREERATIO);
	imshow("像素读写显示", img);
}

// 用指针来写这段代码运行速度更快，看自己能不能理解
/*
void QuickDemo::pixel_visit_demo(Mat& img) {
	// 处理图像中单个像素点函数，赋值操作
	int w = img.cols;
	int h = img.rows;
	int dims = img.channels();
	for (int row = 0; row < h; row++) {
		uchar* current_row = img.ptr<uchar>(row);  //获取当前行的指针，初始在第一行第一列（0，0）的值
		for (int col = 0; col < w; col++) {
			if (dims == 1) { // 灰度图像
				int pv = *current_row;
				*current_row++ = 255 - pv;       // 指针后移（还是在第一行），列数往后移了
			}
			if (dims == 3) { // 彩色图像
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
			}
		}
	}
}*/


// 图像像素算术操作
void QuickDemo::operators_demo(Mat& img) {
	Mat dst;
	dst = img + Scalar(50, 50, 50);      // mat加法操作，图像变亮了
	// 乘法操作，稍微有点复杂
	Mat m = Mat::zeros(img.size(), img.type());
	m = Scalar(2, 2, 2);
	multiply(dst, m, dst);    //add,subtract,divide
	namedWindow("算术操作", WINDOW_FREERATIO);
	imshow("算术操作", dst);
}


void QuickDemo::colorReduce_demo1(Mat& src, Mat& dst, int div) {
	dst = src.clone();
	int rows = dst.rows;
	int cols = dst.cols * dst.channels();   // 三通道的图像，所以要乘以通道数才是总列数
	for (int i = 0; i < rows; i++) {
		uchar* data = dst.ptr<uchar>(i);      // 获取当前行的首地址，指针指向了当前行
		for (int j = 0; j < cols; j++) {
			data[j] = data[j] / div * div + div / 2;   // 颜色缩减操作，dst中像素点直接被运算操作了
		}
	}
}


void QuickDemo::colorReduce_demo2(Mat& src, Mat& dst, int div) {

	dst = src.clone();
	Mat_<Vec3b>::iterator it = dst.begin<Vec3b>();   // 向量有3维
	Mat_<Vec3b>::iterator itend = dst.end<Vec3b>();

	for (; it != itend; ++it) {
		(*it)[0] = (*it)[0] / div * div + div / 2;
		(*it)[1] = (*it)[1] / div * div + div / 2;
		(*it)[2] = (*it)[2] / div * div + div / 2;
	}
}

static void on_lightness(int b, void* userdata) {
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	addWeighted(image, 1.0, m, 0, b, dst);  //加法操作
	imshow("亮度与对比度调整", dst);
}

static void on_contrast(int b, void* userdata) {
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	double contrast = b / 100.0;
	addWeighted(image, contrast, m, 0.0, 0, dst);   // 乘法操作
	imshow("亮度与对比度调整", dst);
}

void QuickDemo::tracking_bar_demo(Mat& image) {
	namedWindow("亮度与对比度调整", WINDOW_AUTOSIZE);
	int lightness = 50;
	int max_value = 100;
	int contrast_value = 100;
	createTrackbar("Value Bar:", "亮度与对比度调整", &lightness, max_value, on_lightness, (void*)(&image));
	createTrackbar("Contrast Bar:", "亮度与对比度调整", &contrast_value, 200, on_contrast, (void*)(&image));
	on_lightness(50, &image);   // 这里回调其中一个函数即可同时调用两天个trackbar
}


// 通过不同按键操作达到控制不同功能的效果
void QuickDemo::key_demo(Mat& img) {
	Mat dst = Mat::zeros(img.size(), img.type());
	namedWindow("按键响应");
	for (;;) {
		int key = waitKey(80);
		if (key == 27) {
			cout << "ESC退出程序" << endl;
			break;
		}
		if (key == 9) {   // 按下tab键
			cout << "按下tab键" << endl;
			cvtColor(img, dst, COLOR_BGR2GRAY);
			imshow("按键响应", dst);
		}
		
		if (key == 113) {    //按下q键
			cout << "按下q键" << endl;
			Mat m = Mat::zeros(img.size(), img.type());
			addWeighted(img, 2, m, 0, 50, dst);
			imshow("按键响应", dst);
		}

		if (key == 49) {   //按下1键
			cout << "按下1键" << endl;
			cvtColor(img, dst, COLOR_BGR2HSV);
			imshow("按键响应", dst);
		}
	}
}



void QuickDemo::color_style_demo(Mat& img) {
	int colormap[] = {
		COLORMAP_AUTUMN,
		COLORMAP_BONE,
		COLORMAP_JET,
		COLORMAP_WINTER,
		COLORMAP_RAINBOW,
		COLORMAP_OCEAN,
		COLORMAP_SUMMER,
		COLORMAP_SPRING,
		COLORMAP_COOL,
		COLORMAP_PINK,
		COLORMAP_HOT,
		COLORMAP_PARULA,
		COLORMAP_MAGMA,
		COLORMAP_INFERNO,
		COLORMAP_PLASMA,
		COLORMAP_VIRIDIS,
		COLORMAP_CIVIDIS,
		COLORMAP_TWILIGHT,
		COLORMAP_TWILIGHT_SHIFTED
	};

	Mat dst;
	int index = 0;
	while (true) {
		int c = waitKey(600);
		if (c == 27) { // 退出
			break;
		}
		applyColorMap(img, dst, colormap[index % 19]);
		index++;
		imshow("颜色风格", dst);
	}
}


void QuickDemo::bitwise_demo(Mat& img) {
	Mat m1 = Mat::zeros(Size(256, 256), CV_8UC3);
	Mat m2 = Mat::zeros(Size(256, 256), CV_8UC3);
	rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0);
	rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);
	imshow("m1", m1);
	imshow("m2", m2);
	Mat dst;
	bitwise_and(m1, m2, dst);   //同理or,not,xor
	imshow("像素位与操作", dst);
}


void QuickDemo::channels_demo(Mat& img) {
	vector<Mat> mv;
	split(img, mv);   // 分离
	imshow("B通道", mv[0]);
	imshow("G通道", mv[1]);
	imshow("R通道", mv[2]);
	Mat dst;
	mv[0] = 0;
	mv[1] = 0;
	merge(mv, dst);   // 合并
	imshow("合并通道红色", dst);
	int from_to[] = { 0,2,1,1,2,0 };   // 把B通道和R通道互换一下
	mixChannels(&img, 1, &dst, 1, from_to, 3);   // 输入为1个mat，输出为1个mat，3通道
	imshow("通道混合", dst);
}