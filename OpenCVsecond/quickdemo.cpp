#include <quickopencv.h>
#include <math.h>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <fstream>
//�ڶ��� ɫ�ʿռ��ת��
void QuickDemo::colorSpace_Demo(Mat &image)//ɫ�ʿռ�ת��
{
	Mat gray, hsv;
	//cvtColor����������
	cvtColor(image, hsv, COLOR_BGR2HSV);//תhsv
	cvtColor(image, gray, COLOR_BGR2GRAY); //ת�Ҷ�
	namedWindow("Hsv", WINDOW_FREERATIO);
	namedWindow("�Ҷ�ͼ", WINDOW_FREERATIO);
		imshow("Hsv", hsv);        //hsv��ʾ
	imshow("�Ҷ�ͼ", gray);    // �Ҷ�ͼ��ʾ
	imwrite("F:\\c++learning\\OpenCVsecond\\hsv.png", hsv);//    hsv����·��
	imwrite("F:\\c++learning\\OpenCVsecond\\gray.png", gray);//    �Ҷ�ͼ����·��
}

void QuickDemo::video_Demo(Mat&image) //����ͷ��ʾ
{
	VideoCapture capture("F:\\c++learning\\OpenCVsecond\\test.mp4");//0ʱ��Ѱ�ұ�������ͷ������������Ƶ����
	int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);//��ȡ���ؿ��
	int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);
	int count = capture.get(CAP_PROP_FRAME_COUNT);//��ȡ��֡��
	double fps = capture.get(CAP_PROP_FPS);
	std::cout << "frame width:" << frame_width << std::endl;
	std::cout << "frame height:" << frame_height << std::endl;
	std::cout << "count:" << count << std::endl;
	std::cout << "fps:" << fps << std::endl;
	/*VideoWriter writer("F:\\testtest.mp4",capture.get(CAP_PROP_FOURCC),fps,Size(frame_width, frame_height),true);*/
	Mat frame;
	while (true) 
	{	namedWindow("frame",WINDOW_FREERATIO);//ʹ���ڿ������ƶ�
		capture.read(frame);

		flip(frame, frame, 1);//����
		if (frame.empty()) 
		{
			break;
		}
		imshow("frame", frame);
	//	colorSpace_Demo(frame);//�Ҷȴ���
		
		/*writer.write(frame);*/
		int c = waitKey(10);//����1ʹ������ʵʱ��
		if (c == 27) {
			break;
		
		}
		/*capture.release();*/
		/*writer.release();*/
	}
}

void QuickDemo::mat_creation_demo(Mat&image)//����һ����Ҫ��ͼ����OpenCV��һ��ͼ����Mat
{
	Mat m1, m2;
	m1 = image.clone();//���ָ���ͼ��ķ�ʽ
	image.copyTo(m2);

	//�����հ�ͼ��
	Mat m3 = Mat::zeros(Size(8, 8), CV_8UC3);//8bit �޷��� ��һͨ�������ص�Ϊ1�� �Ҷ�ͼƬ  ����Ϊ3��ÿ�����ص�������
	//ͼ�����ݵĳ���=ͨ�������Կ��    onesֻ�������ڵ�ͨ������ͨ����ֻ��ѵ�һ����ʼ��Ϊ1
	//m3 = 127;//��һ��ͨ��Ϊ127
	m3 = Scalar(40,90,0);//�Ը���ͨ���ֱ�ֵ BGRͨ��˳��
	std::cout << "width:" << m3.cols << " height:" << m3.rows << " channels:" << m3.channels() << std::endl;
	/*std::cout << m3 << std::endl;*/
	imshow("����ͼ��", m3);

	Mat m4 = m3.clone();
	m4 = Scalar(0, 255, 255);
	imshow("picture1", m3);//��ֵ���ı�m4��ʵ���Ǹı�m3����Ҫ�ÿ�¡�ſ��Դ�����ͼƬ����copytoҲ����
	imshow("picture2", m4);
	Mat kernel = (Mat_<char>(3, 3) << 0, 1, 0,
		1, 5, 1,
		0, 1, 0);//����һ������
	std::cout << kernel << std::endl;
	/*imshow("picture3", kernel);*/
	/*Mat m5 = Mat::zeros(Size(512, 512), CV_8UC1);*/

}
    //ͼ�����ض�д����   �������Ǹĳ���ȡ��ɫ
void QuickDemo::pixel_visit_demo(Mat&image) {
	int w = image.cols;
	int h = image.rows;
	int dims = image.channels();
	//for (int row = 0; row < h; row++) {//����
	//	for (int col = 0; col < w; col++) {
	//		if (dims == 1) {//��ͨ���ĻҶ�ͼ��
	//			int pv = image.at<uchar>(row, col);//��ȡ����ֵ�����ͷ�ʽ���� �д���y�д���x
	//			image.at<uchar>(row, col) = 255 - pv;
	//		}
	//		if (dims == 3) {//��ɫͼ��
	//			Vec3b vgr = image.at<Vec3b>(row, col);//��ͨ������vec3bһ���л����ͨ������ֵ(�Ǹ�����)
	//			image.at<Vec3b>(row, col)[0] = 255 - vgr[0];
	//			image.at<Vec3b>(row, col)[1] = 255 - vgr[1];
	//			image.at<Vec3b>(row, col)[2] = 255 - vgr[2];
	//		}
	//	}
	//}
	 std::cout << "��" << w << std::endl;
	for (int row = 0; row < h; row++) {//����
		uchar*current_row = image.ptr<uchar>(row);//ָ��ָ���row��Ԫ��
		for (int col = 0; col < w; col++) {
			if (dims == 1) {//��ͨ���ĻҶ�ͼ��
				int pv = *current_row;
				*current_row= 255 - pv;
			}
			if (dims == 3) {//��ɫͼ��
				*current_row++ = 255 - *current_row;//��ֵ���˻������ߣ�++������ͨ���͸�ֵ��
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;//��Ϊ��ָ��ǰ�е���һ����
			}
		}
	}
	namedWindow("���ض�д��ʾ", WINDOW_FREERATIO);
	imshow("���ض�д��ʾ", image);
}

void QuickDemo::operators_demo(Mat&image) {//ͼ�����ص���������
	Mat dst= Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(2, 2, 2);
	multiply(image,m,dst);//�˷�Ҫ�ú���ʵ��
	////�ӷ�
	//int w = image.cols;
	//int h = image.rows;
	//int dims = image.channels();
	//for (int row = 0; row < h; row++) {//����
	//	for (int col = 0; col < w; col++) {
	//			Vec3b p1 = image.at<Vec3b>(row, col);//��ͨ������vec3bһ���л����ͨ������ֵ(�Ǹ�����)
	//			Vec3b p2= m.at<Vec3b>(row, col);
	//			dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(p1[0] + p2[0]);//������Ӻ����׳���255��Ҫ������æ
	//			dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(p1[1] + p2[1]);//������������uchar�ķ�Χ�����޶���0��255
	//			dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(p1[2] + p2[2]);//�ڸ����������͵�ת���о����õ�
	//		
	//	}
	//}
	add(image, m, dst);//�ӷ�����OpenCV�еĺ�����������ָ������ģ���Ȼ���Ϸ��ĺ���������
	subtract(image, m, dst);//��������
	divide(image,m,dst);//��������
	namedWindow("�ӷ�����", WINDOW_FREERATIO);
	imshow("�ӷ�����", dst);
}



static void on_lightness(int b, void* userdata) {
	Mat image = *((Mat*)userdata);//��ǰ���*���ܰѺ���ĵ�ַ��Ϊ����
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	
	addWeighted(image,1.0,m,0,b,dst);//�ں�����ͼ��������ռ��
	namedWindow("�Աȶ������ȵ���", WINDOW_AUTOSIZE);
	imshow("�Աȶ������ȵ���", dst);
}

static void on_contrast(int b, void* userdata) {
	Mat image = *((Mat*)userdata);//��ǰ���*���ܰѺ���ĵ�ַ��Ϊ����
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	double contrast = b / 100.0;//0��2���ֵ
	addWeighted(image, contrast, m, 0.0, 0, dst);//�ں�����ͼ��������ռ��
	namedWindow("�Աȶ������ȵ���", WINDOW_AUTOSIZE);
	imshow("�Աȶ������ȵ���", dst);
}

void QuickDemo::tracking_bar_demo(Mat&image) {//����������ͼƬ����
	namedWindow("�Աȶ������ȵ���", WINDOW_AUTOSIZE);
	
	int lightness = 50;
	int max_value = 100;
	int contrast_value = 100;
	createTrackbar("Value Bar", "�Աȶ������ȵ���", &lightness, max_value, on_lightness,(void*)(&image));//������ǻص�����,�������ǰ�ͼ����Ϊ����
	createTrackbar("Contrast Bar", "�Աȶ������ȵ���", &lightness, 200, on_contrast, (void*)(&image));
	//on_lightness(50, &image);//userdataΪָ����Ҫ��&�����image�ĵ�ַ
}

void QuickDemo::bitwrite_demo(Mat&image) {
	Mat m1 = Mat::zeros(256, 256,CV_8UC3);
	Mat m2 = Mat::zeros(256, 256, CV_8UC3);
	rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0);//С��0����䣬����0�ǻ���
	rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);//����һ�����εĲ���
	imshow("M1", m1);
	imshow("M2", m2);
	Mat dst;
	bitwise_and(m1, m2, dst);//�����gͨ��ȫ��255������ɫ��BGR��
	imshow("����λ����1", dst);
	bitwise_or(m1, m2, dst);
	imshow("����λ����2", dst);
	bitwise_not(m1, dst);//����pixel_visit_demo���ȡ������ Mat=~image;
	imshow("����λ����3", dst);
	bitwise_xor(m1, m2, dst);
	imshow("����λ����4", dst);
}

void QuickDemo::color_style_demo(Mat&image) {
	int color_map[] = {
		  COLORMAP_AUTUMN,
		  COLORMAP_BONE,
	/*	  COLORMAP_CIVIDIS,*/
		  COLORMAP_COOL,
		/*  COLORMAP_DEEPGREEN,*/
		  COLORMAP_HOT,
		  COLORMAP_HSV,
	/*	  COLORMAP_INFERNO,*/
		  COLORMAP_JET,
		/*  COLORMAP_MAGMA,*/
		  COLORMAP_OCEAN,
		  COLORMAP_PARULA,
		  COLORMAP_PINK,
		/*  COLORMAP_PLASMA,*/
		  COLORMAP_RAINBOW,
		  COLORMAP_SPRING,
		  COLORMAP_SUMMER,
	/*	  COLORMAP_TURBO,
		  COLORMAP_TWILIGHT,
		  COLORMAP_TWILIGHT_SHIFTED,
		  COLORMAP_VIRIDIS,*/
		  COLORMAP_WINTER
			};
	Mat dst;
	int index = 0;
	while (true) {
		int c = waitKey(2000);//ͣ������
		if (c == 27) {//�˳�
			break;
		}
		applyColorMap(image, dst, color_map[index%13]);//0��13ѭ������
		index++;
		namedWindow("��ɫ���", WINDOW_AUTOSIZE);
		imshow("��ɫ���", dst);						//������ϼ�����Ӧ���������е�һЩ��Ƭ
	}
}

void QuickDemo::channels_demo(Mat&image) {//ͨ��������ϲ�
	std::vector<Mat>mv;//��һ��������Է�mat����
	split(image,mv);
	imshow("��ɫ", mv[0]);
	imshow("��ɫ", mv[1]);
	imshow("��ɫ", mv[2]);
	Mat dst;
	//mv[1] = 0;
	//mv[2] = 0;//����д��Ŀ����Ȼ����ͨ������ɫû�У�ֻʣ����ɫ
	merge(mv, dst);
	imshow("��ɫ",dst);
	int from_to[] = { 0,2,1,1,2,0 };//0ͨ��ȥ2ͨ����2ͨ��ȥ0ͨ����1ͨ������1
	mixChannels(&image,1,&dst,1, from_to,3);//1��ͼ���ɶ����ţ��ı�ͨ����3��
	imshow("ͨ�����", dst);
}
void QuickDemo::inrange_demo(Mat&image) {//������ͼ����
	Mat hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	Mat mask;
	inRange(hsv, Scalar(100,43,46), Scalar(124,255,255), mask);//��hsvɫ�ʿռ�ı�Ϳ��԰���ɫ�������(lab��hsi�ռ䶼ɫ�ʷֱ���ȷ)
	imshow("mask1",mask);

	Mat redback = Mat::zeros(image.size(), image.type());
	redback = Scalar(255, 255, 255);//��ɫ
	bitwise_not(mask, mask);//ȡ��
	imshow("mask2", mask);
	//��imageͼƬ�ϲ�Ϊ��ɫ��Ǩ�Ƶ�redback��mask��ԭͼ����ٳ���Ŀ����������
	image.copyTo(redback, mask);//mask�ϲ�Ϊ0����ɫ���Ĳ�Ǩ�ƹ����������ľͲ�Ҫ��
	imshow("roi������ȡ", redback);
}


void QuickDemo::pixel_statistic_demo(Mat&image) {//ͼ���ֵ����������Сֵ��ȡ
	double minv, maxv;
	Point minLoc, maxLoc;//minMaxLoc����Ҫ���ǵ�ͨ���ģ�Ҫ����ͨ��
	std::vector<Mat>mv;//��һ��������Է�mat����
	split(image, mv);
	for (int i = 0; i < mv.size(); i++) {
	minMaxLoc(mv[i], &minv, &maxv, &minLoc, &maxLoc,Mat());//��image����Ѱ�������Сֵ������ֵָ��͵�ַָ��
	std::cout <<" No.channels:"<<i<< " min value:" << minv << " max value" << maxv << std::endl;
	
	}
	Mat mean, stddev;
	meanStdDev(image, mean, stddev);//��ֵ�ͷ��һ��������ȡior�����ֵ��ǰ����mask����ȡior����
	//meam.at<double>(0,0);//���԰�ֵ������ӡ����
	std::cout << "mean" << mean << std::endl;
	std::cout<< "stddev" << stddev << std::endl;
}

void QuickDemo::drawing_demo(Mat&image) {//��Ļԭ�����������Ͻ�
	Rect rect;
	rect.x = 50;
	rect.y = 50;//���ε����
	rect.width = 200;//���α߳�
	rect.height = 200;
	Mat bg = Mat::zeros(image.size(),image.type());
	rectangle(bg, rect, Scalar(0, 0, 255), -1, 8, 0);
	line(bg, Point(50, 50), Point(250, 250), Scalar(0, 255, 0), 2, LINE_AA, 0);//8���ǻ��о����line_aa�����
	circle(bg, Point(250, 250), 15, Scalar(0, 255, 0), 2, LINE_AA, 0);//point��Բ�����ĵ�
	RotatedRect rrt;
	rrt.center = Point(200, 200);
	rrt.size = Size(100, 200);//���ȵĸߵ�
	rrt.angle = 0.0;
	ellipse(bg, rrt, Scalar(0, 255, 255), 2, 8);
	Mat dst;
	addWeighted(image, 0.7, bg, 0.3, 0, dst);//�ں�����ͼ��������ռ��
	imshow("���ƾ���", dst);
}
void QuickDemo::random_drawing() {
	Mat canvans = Mat::zeros(Size(512,512),CV_8UC3);
	int w = canvans.cols;
	int h = canvans.rows;
	RNG rng(12345);
	while (true) {
		int c = waitKey(100);
		if (c == 27) {//�˳�
			break;
		}
		int x1=rng.uniform(0, w);//���������0~w
		int y1 = rng.uniform(0, h);
		int x2 = rng.uniform(0, w);//���������0~w
		int y2 = rng.uniform(0, h);
		int b = rng.uniform(0, 255);
		int g = rng.uniform(0, 255);
		int r = rng.uniform(0, 255);
		canvans = Scalar(0, 0, 0);
		line(canvans, Point(x1, y1), Point(x2, y2), Scalar(b, g, r), 2, LINE_AA, 0);//8���ǻ��о����line_aa�����
		imshow("���������ʾ", canvans);
	}


}
void QuickDemo::polyline_drawing_demo() {
	//Mat canvans = Mat::zeros(Size(512, 512), CV_8UC3);
	//Point p1(200, 200);
	//Point p2(350, 100);
	//Point p3(450, 280);
	//Point p4(320, 450);
	//
	//std::vector<Point>pts(4);//����һ������������5����
	//pts.push_back(p1);
	//pts.push_back(p2);
	//pts.push_back(p3);
	//pts.push_back(p4);
	///*pts.push_back(p5);*/
	//polylines(canvans, pts, true, Scalar(0, 0, 255), 2, 8, 0);
	//imshow("����λ���", canvans);

	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);//���ַ�ʽ�������������
	int w = canvas.cols;
	int h = canvas.rows;
	Point p1(100, 100);
	Point p2(300, 150);
	Point p3(300, 350);
	Point p4(250, 450);
	Point p5(50, 450);
	std::vector<Point> pts;
	pts.push_back(p1);
	pts.push_back(p2);
	pts.push_back(p3);
	pts.push_back(p3);
	pts.push_back(p4);
	pts.push_back(p5);
	std::vector<std::vector<Point>> contours;//�ǵ�Ҫ�ö�άǶ������������
	contours.push_back(pts);
	fillPoly(canvas, contours, Scalar(255, 0, 255), 8, 0);
	polylines(canvas, contours, true, Scalar(0, 255, 255), 4, 8, 0);

/*
	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);
	int w = canvas.cols;
	int h = canvas.rows;
	Point p1(100, 100);
	Point p2(300, 150);
	Point p3(300, 350);
	Point p4(250, 450);
	Point p5(50, 450);
	std::vector<Point> pts;
	pts.push_back(p1);
	pts.push_back(p2);
	pts.push_back(p3);
	pts.push_back(p3);
	pts.push_back(p4);
	pts.push_back(p5);
	std::vector<std::vector<Point>> contours;
	contours.push_back(pts);
	drawContours(canvas, contours, 0, Scalar(0, 0, 255), -1, 8);//����������Ի��ƶ������Σ�����0��ָ���Ƶ�һ������Σ�-1�Ļ�����ȫ�����ƣ���
	drawContours(canvas, contours, 0, Scalar(255, 0, 255), 2, 8);*/
	imshow("����", canvas);
}
Point sp(-1, -1);
Point ep(-1, -1);
//static void on_draw(int event, int x, int y, int flags, void* userdata) {
//	Mat z = *((Mat*)userdata);
//
//	if (event == EVENT_LBUTTONDOWN) {
//		sp.x = x;
//		sp.y = y;
//		std::cout << "start point" << sp << std::endl;
//	}
//	else if (event == EVENT_LBUTTONUP) {
//		ep.x = x;
//		ep.y = y;
//		std::cout << "end point" << ep << std::endl;
//		int dx = ep.x - sp.x;
//		int dy = ep.y - ep.y;
//		if (dx > 0 && dy > 0) {
//			Rect rect;
//			rect.x = ep.x;
//			rect.y = ep.y;//���ε����
//			rect.width = dx;//���α߳�
//			rect.height = dy;
//			imshow("ROI����", z(rect));
//			rectangle(z, rect, Scalar(0, 0, 255), 2, 8, 0);
//			imshow("������", z);	
//			sp.x = -1;
//			sp.y = -1;
//
//		}
//	}
//	else if (event == EVENT_MOUSEMOVE) {
//		if(sp.x>0&&sp.y>0){
//			ep.x = x;
//			ep.y = y;
//			int dx = ep.x - sp.x;
//			int dy = ep.y - ep.y;
//			if (dx > 0 && dy > 0) {
//			Rect rect;
//			rect.x = ep.x;
//			rect.y = ep.y;//���ε����
//			rect.width = dx;//���α߳�
//			rect.height = dy;
//			rectangle(z, rect, Scalar(0, 0, 255), 2, 8, 0);
//			imshow("������", z);
//			}
//		}
//	}
//	}
//void QuickDemo::mouse_drawing_demo(Mat&image) {
//	namedWindow("������",WINDOW_AUTOSIZE);
//	setMouseCallback("������", on_draw,(void*)(&image));
//	imshow("������", image);
//}
Mat temp;
static void on_draw(int event, int x, int y, int flag, void* userdata)
{
	//����ʵ������������img
	Mat img = *(Mat*)userdata;
	/*Mat imge=*(Mat*)userdata;*/
	//Ȼ���ȡ����ͣ����
	//1.��ʼ��
	if (event == EVENT_LBUTTONDOWN)
	{
		sp.x = x, sp.y = y;
		std::cout << "the start point is (" << sp.x << "," << sp.y << ")" << std::endl;
	}
	else if (event == EVENT_LBUTTONUP)//���Ƿſ�����ʱ��,��Ҫ��ʼ�������
	{
		ep.x = x, ep.y = y;
		std::cout << "the end point is (" << sp.x << "," << sp.y << ")" << std::endl;
		int dx = ep.x - sp.x;
		int dy = ep.y - sp.y;
		if (dx > 0 && dy > 0)
		{
			Rect box(sp.x, sp.y, dx, dy);
			temp.copyTo(img);
			rectangle(img, box, Scalar(0, 0, 255), 2, LINE_AA, 0);
			imshow("ROI����", img(box));
			imshow("������", img);
			sp.x = -1, sp.y = -1;
		}
	}
	else if (event == EVENT_MOUSEMOVE)
	{
		if (sp.x > 0 && sp.y > 0)
		{
			ep.x = x;
			ep.y = y;
			int dx = ep.x - sp.x;
			int dy = ep.y - sp.y;
			if (dx > 0 && dy > 0)
			{
				Rect box(sp.x, sp.y, dx, dy);
				temp.copyTo(img);
				rectangle(img, box, Scalar(0, 0, 255), 2, LINE_8, 0);
				imshow("������", img);
			}
		}
	}
}

void QuickDemo::mouse_drawing_demo(Mat &img)
{   
	//1.�������ڣ�������ʾ
	namedWindow("������", WINDOW_AUTOSIZE);
	temp = img.clone();
	//2.����SetmouseCallback,��opencv����
	setMouseCallback("������", on_draw, (void*)(&img));
	//api˵��:("��������"(string),��Ҫcallback�󶨵ĺ���,�Զ������userdata )
	//3.��ʾ����imshow("��������",����ͼ��)
	imshow("������", img);
}

void QuickDemo::normalize_demo(Mat& image)
{
	Mat src1, src2, src3,m;
	m = Mat::zeros(image.size(), image.type());
	 m = Scalar(255, 255, 255);
	image.copyTo(src1);
	imshow("ԭͼ", src1);

	src1.convertTo(src2, CV_32F);
	/*imshow("��ʽת��ͼ", src2);*/

	normalize(src2, src3, 0, 1, NORM_MINMAX);
	
	src3.convertTo(src3, CV_8UC3);
	multiply(src3, m, src3);//��������
	imshow("��ʽת��ϵ������ͼ", src3);//�ҵ�imshow������ʾ32λ��ͼ��
	waitKey(0);


}


//void QuickDemo::norm_demo(Mat&image) {
//	Mat dst;
//	std::cout << image.type() << std::endl;
//	imshow("ͼ�����ݹ�һ��", image);
//	image.convertTo(image, CV_32FC3);//��������ת��CV_8UC3 �䵽 CV_32FC3
//	std::cout << image.type() << std::endl;
//	normalize(image, dst, 1.0, 0, NORM_MINMAX);
//	std::cout << dst.type() << std::endl;
//	/*dst.convertTo(dst, CV_8UC3);*/
//	imshow("ͼ�����ݹ�һ��2", dst);
//	waitKey(0);
//
//
//
//}

void QuickDemo::resize_demo(Mat&image) {
	Mat zoomin, zoomout;
	int h = image.rows;
	int w = image.cols;
	resize(image, zoomin, Size(w / 2, h / 2), 0, 0, INTER_LINEAR);
	imshow("zoomin",zoomin);
	resize(image, zoomout, Size(w *1.5, h *1.5), 0, 0, INTER_LINEAR);
	imshow("zooout", zoomout);



}

void QuickDemo::flip_demo(Mat&image) {
	Mat dst;
	flip(image, dst, 0);//���·�ת
	imshow("ͼ��ת",dst);
	flip(dst, dst, 1);//���ҷ�ת
	imshow("ͼ��ת", dst);
	flip(dst, dst, -1);//�Խ��߷�ת
	imshow("ͼ��ת", dst);

}
void QuickDemo::rotate_demo(Mat&image) {
	Mat dst, M;
	int w = image.cols;
	int h = image.rows;
	M = getRotationMatrix2D(Point2f((w / 2), (h / 2)*sin(3.14 / 2)), 45, 1.0);//ԭ��ͼ������λ�ã��Ƕȣ���ͼ��ķŴ���С
	double sin = abs(M.at<double>(0, 0));//��һ������abs
	double cos = abs(M.at<double>(0, 1));//OpenCV�ܶ඼����double
	int nw = cos * w + sin * h;
	int nh = sin * w + cos * h;
	M.at<double>(0, 2) = M.at<double>(0, 2) + (nw / 2 - w / 2);//�õ�������λ��
	M.at<double>(1, 2) = M.at<double>(1, 2) + (nh / 2 - h / 2);//.at������ʾ�ǵڼ��еڼ��е�����ֵ����ͨ�������ڶ�ͨ����at<Vec3b>(i,j)[�ڼ�ͨ��]
	warpAffine(image, dst, M, Size(nw, nh), INTER_LINEAR, 0, Scalar(255, 0, 0));
	imshow("��ת��ʾ", dst);
}

void QuickDemo::showHistogram_demo(Mat&image) {//һά��ֱ��ͼ��opencv���Ը�γ�ȵ�

	std::vector<Mat> bgr_plane;//��ͨ������
	split(image, bgr_plane);
	const int channels[1] = { 0 };
	const int bins[1] = { 256 };//256���Ҷȼ���
	float hranges[2] = { 0,256 };//ֱ��ͼ��ȡֵ��Χ
	const float*ranges[1] = { hranges };//ֱ��ͼ��ȡֵ��Χ
	Mat b_hist;
	Mat g_hist;
	Mat r_hist;
	//����Blue��Green��Red ͨ����ֱ��ͼ   //mask��ֻȡ����ֵ�Ĳ��־���֮ǰ����Ĥ     b_hist��ֱ��ͼ�����
	calcHist(&bgr_plane[0], 1, 0, Mat(), b_hist, 1, bins, ranges);//��һ��1��һ��ͼ����˼���ڶ���1��һά��ֱ��ͼ��ȡֵ��Χ0��255
	calcHist(&bgr_plane[1], 1, 0, Mat(), g_hist, 1, bins, ranges);
	calcHist(&bgr_plane[2], 1, 0, Mat(), r_hist, 1, bins, ranges);
	//��ʾֱ��ͼ
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / bins[0]);//cvRound���ظ�������ӽ�������ֵ���������룩  bins��ֱָ��ͼ�Ĵ�С��������ȡֵ��0~255���������256��
	Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);//��������
	//��һ��ֱ��ͼ����
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());//��һ�����������ô��
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	//����ֱ��ͼ����											//��������y�������µ�
	for (int i = 1; i < bins[0]; i++) {						//bins����������    ͼ��ĸ߶ȼ�ȥ��ǰ������ֵ�����ֱ��ͼ���ȴӶ�������ĸ߶�  ���������
		line(histImage, Point((bin_w*(i - 1)), hist_h - cvRound(b_hist.at<float>(i - 1))), Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point((bin_w*(i - 1)), hist_h - cvRound(g_hist.at<float>(i - 1))), Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point((bin_w*(i - 1)), hist_h - cvRound(r_hist.at<float>(i - 1))), Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
	
	}
	//��ʾֱ��ͼ
	namedWindow("Histogram Demo", WINDOW_AUTOSIZE);
	imshow("Histogram Demo", histImage);
}


void QuickDemo::Histogram_2d_demo(Mat&image) {
	Mat hsv, hs_hist;
	cvtColor(image, hsv, COLOR_BGR2HSV);//��ת��hsv��h�ķ�Χ��0~180 s�ķ�Χ��0~255
	int hbins = 30, sbins = 32;   //h��30�����s��32���
	int hist_bins[] = { hbins ,sbins };
	float h_range[] = { 0,180 };
	float s_range[] = { 0,256 };
	const float* hs_ranges[] = { h_range,s_range };
	int hs_channels[] = { 0,1 };
	calcHist(&hsv, 1, hs_channels, Mat(), hs_hist, 2, hist_bins, hs_ranges, true, false);
	double maxVal = 0;
	minMaxLoc(hs_hist, 0, &maxVal, 0, 0);
	int scale = 10;
	Mat hist2d_image = Mat::zeros(sbins*scale, hbins*scale, CV_8SC3);
	for (int h = 0; h < hbins; h++) {
		for (int s = 0; s < sbins; s++) {

			float binVal = hs_hist.at<float>(h, s);
			int intensity = cvRound(binVal * 255 / maxVal);
			rectangle(hist2d_image, Point(h*scale, s*scale), Point((h + 1)*scale - 1, (s + 1)*scale - 1), Scalar::all(intensity), -1);
		}
	}
	imshow("H-S Hidyogram", hist2d_image);
	imwrite("D:/hist_2d.png", hist2d_image);
}

void QuickDemo::histogram_eq_demo(Mat&image) {

	Mat gray;
	cvtColor(image, gray, COLOR_BGR2GRAY);
	imshow("�Ҷ�ͼ��", gray);
	Mat dst;
	equalizeHist(gray, dst);
	imshow("ֱ��ͼ���⻯��ʾ",dst);
}

void QuickDemo::blur_demo(Mat&image) {
	Mat dst;
	blur(image, dst, Size(13, 13), Point(-1, -1));//��ֵ��� 13*13�ľ���� �� ֧��һά���
	imshow("ͼ��ģ��", dst);
}

void QuickDemo::gaussin_blur_demo(Mat&image) {

	Mat dst;
	GaussianBlur(image, dst, Size(5, 5), 15);//��ֵ��� 13*13�ľ���� �� ֧��һά���
	imshow("��˹ģ��", dst);
}

void QuickDemo::bifilter_demo(Mat&image) {
	Mat dst;
	bilateralFilter(image, dst, 0, 100, 10);
	imshow("��˹˫��ģ��", dst);
}

int element_size = 3;
int max_size = 21;
//void CallBack_Demo(int, void *userdata) {
//	Mat image = *((Mat*)userdata);
//	Mat src,dst;
//	 src = Mat::zeros(image.size(), image.type());
//	src.copyTo(image);
//	 dst = Mat::zeros(image.size(), image.type());
//	int s = element_size * 2 + 1;
//	Mat structureElement = getStructuringElement(MORPH_RECT, Size(s, s), Point(-1, -1));
//	dilate(src,dst,structureElement,Point(-1,-1));
//	imshow("OUTWINDOW", dst);
//	return ;
//}
//void QuickDemo::corrosion_expand(Mat&image) {
//	
//	namedWindow("OUTWINDOW", WINDOW_AUTOSIZE);
//	createTrackbar("Element Size :", "OUTWINDOW", &element_size, max_size, CallBack_Demo, (void*)(&image));
//	
//
//}

static void onn_contrast(int b, void* userdata) {
	Mat image = *((Mat*)userdata);
	Mat src, dst;
	src = Mat::zeros(image.size(), image.type());
	src.copyTo(image);
	dst = Mat::zeros(image.size(), image.type());
	int s = element_size * 2 + 1;
	Mat structureElement = getStructuringElement(MORPH_RECT, Size(s, s), Point(-1, -1));
	dilate(src, dst, structureElement, Point(-1, -1),1);
	/*erode(src, dst, structureElement);*/
	namedWindow("�Աȶ������ȵ���", WINDOW_AUTOSIZE);
	imshow("�Աȶ������ȵ���", dst);
}

void QuickDemo::corrosion_expand(Mat&image) {//����������ͼƬ����
	namedWindow("�Աȶ������ȵ���", WINDOW_AUTOSIZE);

	int lightness = 3;
	int max_value = 21;
	int contrast_value = 100;
	createTrackbar("Contrast Bar", "�Աȶ������ȵ���", &lightness, max_value, onn_contrast, (void*)(&image));
	//on_lightness(50, &image);//userdataΪָ����Ҫ��&�����image�ĵ�ַ
}