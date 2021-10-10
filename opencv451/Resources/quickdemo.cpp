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

// ����һЩmat����
void QuickDemo::mat_creation_demo(Mat &img) {
	Mat m1, m2;
	m1 = img.clone(); // ���ֿ�¡��ʽ��ǳ���������ֱ�Ӹ�ֵ����������һ������ȫ����
	img.copyTo(m2);
	// �����յ�Matͼ��
	Mat m3 = Mat::zeros(Size(8, 8), CV_8UC3);  //8λ3ͨ���հ�ͼ��, ones��ȫ1
	m3 = Scalar(255, 0, 0); //3ͨ����ֵ
	cout << "width: " << m3.cols << "  height: " << m3.rows << "  channels: " << m3.channels() << endl;
	cout << m3 << endl;  // IO���
	namedWindow("����ͼ��", WINDOW_FREERATIO);
	imshow("����ͼ��", m3);

	Mat m4 = m3;
	m4 = Scalar(0, 0, 255);  // �൱�������һ����ȫ����
	namedWindow("ֱ���õȺŸ�ֵ", WINDOW_FREERATIO);
	imshow("ֱ���õȺŸ�ֵ", m3);

}


void QuickDemo::pixel_visit_demo(Mat& img) {
	// ����ͼ���е������ص㺯������ֵ����
	int w = img.cols;
	int h = img.rows;
	int dims = img.channels();
	for (int row = 0; row < h; row++) {
		for (int col = 0; col < w; col++) {
			if (dims == 1) {  // ����ͨ���Ҷ�ͼ��
				int pv = img.at<uchar>(row, col);  // һ������8λ���ݼ�һ���ֽ�uchar
				img.at<uchar>(row, col) = 255 - pv;   // һ����ֵ������ʵ���Ͼ���ȡ��(��ɫ)
			}
			if (dims == 3) {
				Vec3b bgr = img.at<Vec3b>(row, col); 
				img.at<Vec3b>(row, col)[0] = 255 - bgr[0];   // ͬ���ĸ�ֵ����
				img.at<Vec3b>(row, col)[1] = 255 - bgr[1];
				img.at<Vec3b>(row, col)[2] = 255 - bgr[2];
			}
		}
	}
	namedWindow("���ض�д��ʾ", WINDOW_FREERATIO);
	imshow("���ض�д��ʾ", img);
}

// ��ָ����д��δ��������ٶȸ��죬���Լ��ܲ������
/*
void QuickDemo::pixel_visit_demo(Mat& img) {
	// ����ͼ���е������ص㺯������ֵ����
	int w = img.cols;
	int h = img.rows;
	int dims = img.channels();
	for (int row = 0; row < h; row++) {
		uchar* current_row = img.ptr<uchar>(row);  //��ȡ��ǰ�е�ָ�룬��ʼ�ڵ�һ�е�һ�У�0��0����ֵ
		for (int col = 0; col < w; col++) {
			if (dims == 1) { // �Ҷ�ͼ��
				int pv = *current_row;
				*current_row++ = 255 - pv;       // ָ����ƣ������ڵ�һ�У���������������
			}
			if (dims == 3) { // ��ɫͼ��
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;
			}
		}
	}
}*/


// ͼ��������������
void QuickDemo::operators_demo(Mat& img) {
	Mat dst;
	dst = img + Scalar(50, 50, 50);      // mat�ӷ�������ͼ�������
	// �˷���������΢�е㸴��
	Mat m = Mat::zeros(img.size(), img.type());
	m = Scalar(2, 2, 2);
	multiply(dst, m, dst);    //add,subtract,divide
	namedWindow("��������", WINDOW_FREERATIO);
	imshow("��������", dst);
}


void QuickDemo::colorReduce_demo1(Mat& src, Mat& dst, int div) {
	dst = src.clone();
	int rows = dst.rows;
	int cols = dst.cols * dst.channels();   // ��ͨ����ͼ������Ҫ����ͨ��������������
	for (int i = 0; i < rows; i++) {
		uchar* data = dst.ptr<uchar>(i);      // ��ȡ��ǰ�е��׵�ַ��ָ��ָ���˵�ǰ��
		for (int j = 0; j < cols; j++) {
			data[j] = data[j] / div * div + div / 2;   // ��ɫ����������dst�����ص�ֱ�ӱ����������
		}
	}
}


void QuickDemo::colorReduce_demo2(Mat& src, Mat& dst, int div) {

	dst = src.clone();
	Mat_<Vec3b>::iterator it = dst.begin<Vec3b>();   // ������3ά
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
	addWeighted(image, 1.0, m, 0, b, dst);  //�ӷ�����
	imshow("������Աȶȵ���", dst);
}

static void on_contrast(int b, void* userdata) {
	Mat image = *((Mat*)userdata);
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	double contrast = b / 100.0;
	addWeighted(image, contrast, m, 0.0, 0, dst);   // �˷�����
	imshow("������Աȶȵ���", dst);
}

void QuickDemo::tracking_bar_demo(Mat& image) {
	namedWindow("������Աȶȵ���", WINDOW_AUTOSIZE);
	int lightness = 50;
	int max_value = 100;
	int contrast_value = 100;
	createTrackbar("Value Bar:", "������Աȶȵ���", &lightness, max_value, on_lightness, (void*)(&image));
	createTrackbar("Contrast Bar:", "������Աȶȵ���", &contrast_value, 200, on_contrast, (void*)(&image));
	on_lightness(50, &image);   // ����ص�����һ����������ͬʱ���������trackbar
}


// ͨ����ͬ���������ﵽ���Ʋ�ͬ���ܵ�Ч��
void QuickDemo::key_demo(Mat& img) {
	Mat dst = Mat::zeros(img.size(), img.type());
	namedWindow("������Ӧ");
	for (;;) {
		int key = waitKey(80);
		if (key == 27) {
			cout << "ESC�˳�����" << endl;
			break;
		}
		if (key == 9) {   // ����tab��
			cout << "����tab��" << endl;
			cvtColor(img, dst, COLOR_BGR2GRAY);
			imshow("������Ӧ", dst);
		}
		
		if (key == 113) {    //����q��
			cout << "����q��" << endl;
			Mat m = Mat::zeros(img.size(), img.type());
			addWeighted(img, 2, m, 0, 50, dst);
			imshow("������Ӧ", dst);
		}

		if (key == 49) {   //����1��
			cout << "����1��" << endl;
			cvtColor(img, dst, COLOR_BGR2HSV);
			imshow("������Ӧ", dst);
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
		if (c == 27) { // �˳�
			break;
		}
		applyColorMap(img, dst, colormap[index % 19]);
		index++;
		imshow("��ɫ���", dst);
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
	bitwise_and(m1, m2, dst);   //ͬ��or,not,xor
	imshow("����λ�����", dst);
}


void QuickDemo::channels_demo(Mat& img) {
	vector<Mat> mv;
	split(img, mv);   // ����
	imshow("Bͨ��", mv[0]);
	imshow("Gͨ��", mv[1]);
	imshow("Rͨ��", mv[2]);
	Mat dst;
	mv[0] = 0;
	mv[1] = 0;
	merge(mv, dst);   // �ϲ�
	imshow("�ϲ�ͨ����ɫ", dst);
	int from_to[] = { 0,2,1,1,2,0 };   // ��Bͨ����Rͨ������һ��
	mixChannels(&img, 1, &dst, 1, from_to, 3);   // ����Ϊ1��mat�����Ϊ1��mat��3ͨ��
	imshow("ͨ�����", dst);
}