#include <quickopencv.h>
#include <math.h>
#include "opencv2/core/core.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>
#include <fstream>
//第二讲 色彩空间的转换
void QuickDemo::colorSpace_Demo(Mat &image)//色彩空间转换
{
	Mat gray, hsv;
	//cvtColor的三个参数
	cvtColor(image, hsv, COLOR_BGR2HSV);//转hsv
	cvtColor(image, gray, COLOR_BGR2GRAY); //转灰度
	namedWindow("Hsv", WINDOW_FREERATIO);
	namedWindow("灰度图", WINDOW_FREERATIO);
		imshow("Hsv", hsv);        //hsv显示
	imshow("灰度图", gray);    // 灰度图显示
	imwrite("F:\\c++learning\\OpenCVsecond\\hsv.png", hsv);//    hsv保存路径
	imwrite("F:\\c++learning\\OpenCVsecond\\gray.png", gray);//    灰度图保存路径
}

void QuickDemo::video_Demo(Mat&image) //摄像头显示
{
	VideoCapture capture("F:\\c++learning\\OpenCVsecond\\test.mp4");//0时是寻找本机摄像头，可以输入视频连接
	int frame_width = capture.get(CAP_PROP_FRAME_WIDTH);//获取像素宽度
	int frame_height = capture.get(CAP_PROP_FRAME_HEIGHT);
	int count = capture.get(CAP_PROP_FRAME_COUNT);//获取总帧数
	double fps = capture.get(CAP_PROP_FPS);
	std::cout << "frame width:" << frame_width << std::endl;
	std::cout << "frame height:" << frame_height << std::endl;
	std::cout << "count:" << count << std::endl;
	std::cout << "fps:" << fps << std::endl;
	/*VideoWriter writer("F:\\testtest.mp4",capture.get(CAP_PROP_FOURCC),fps,Size(frame_width, frame_height),true);*/
	Mat frame;
	while (true) 
	{	namedWindow("frame",WINDOW_FREERATIO);//使窗口可自由移动
		capture.read(frame);

		flip(frame, frame, 1);//镜像
		if (frame.empty()) 
		{
			break;
		}
		imshow("frame", frame);
	//	colorSpace_Demo(frame);//灰度处理
		
		/*writer.write(frame);*/
		int c = waitKey(10);//等于1使程序有实时性
		if (c == 27) {
			break;
		
		}
		/*capture.release();*/
		/*writer.release();*/
	}
}

void QuickDemo::mat_creation_demo(Mat&image)//创建一个需要的图像，在OpenCV中一切图像都是Mat
{
	Mat m1, m2;
	m1 = image.clone();//两种复制图像的方式
	image.copyTo(m2);

	//创建空白图像
	Mat m3 = Mat::zeros(Size(8, 8), CV_8UC3);//8bit 无符号 单一通道（像素点为1） 灰度图片  若改为3则每行像素点有三个
	//图像数据的长度=通道数乘以宽度    ones只可以用于单通道，多通道下只会把第一个初始化为1
	//m3 = 127;//第一个通道为127
	m3 = Scalar(40,90,0);//对各个通道分别赋值 BGR通道顺序
	std::cout << "width:" << m3.cols << " height:" << m3.rows << " channels:" << m3.channels() << std::endl;
	/*std::cout << m3 << std::endl;*/
	imshow("创建图像", m3);

	Mat m4 = m3.clone();
	m4 = Scalar(0, 255, 255);
	imshow("picture1", m3);//赋值法改变m4其实就是改变m3，需要用克隆才可以创建新图片或者copyto也可以
	imshow("picture2", m4);
	Mat kernel = (Mat_<char>(3, 3) << 0, 1, 0,
		1, 5, 1,
		0, 1, 0);//生成一个矩阵
	std::cout << kernel << std::endl;
	/*imshow("picture3", kernel);*/
	/*Mat m5 = Mat::zeros(Size(512, 512), CV_8UC1);*/

}
    //图像像素读写操作   在这里是改成了取反色
void QuickDemo::pixel_visit_demo(Mat&image) {
	int w = image.cols;
	int h = image.rows;
	int dims = image.channels();
	//for (int row = 0; row < h; row++) {//遍历
	//	for (int col = 0; col < w; col++) {
	//		if (dims == 1) {//单通道的灰度图像
	//			int pv = image.at<uchar>(row, col);//获取像素值以整型方式出现 行代表y列代表x
	//			image.at<uchar>(row, col) = 255 - pv;
	//		}
	//		if (dims == 3) {//彩色图像
	//			Vec3b vgr = image.at<Vec3b>(row, col);//三通道可以vec3b一次行获得三通道的数值(是个数组)
	//			image.at<Vec3b>(row, col)[0] = 255 - vgr[0];
	//			image.at<Vec3b>(row, col)[1] = 255 - vgr[1];
	//			image.at<Vec3b>(row, col)[2] = 255 - vgr[2];
	//		}
	//	}
	//}
	 std::cout << "宽" << w << std::endl;
	for (int row = 0; row < h; row++) {//遍历
		uchar*current_row = image.ptr<uchar>(row);//指针指向第row个元素
		for (int col = 0; col < w; col++) {
			if (dims == 1) {//单通道的灰度图像
				int pv = *current_row;
				*current_row= 255 - pv;
			}
			if (dims == 3) {//彩色图像
				*current_row++ = 255 - *current_row;//赋值完了会往后走（++），三通道就赋值了
				*current_row++ = 255 - *current_row;
				*current_row++ = 255 - *current_row;//是为了指向当前行的下一像素
			}
		}
	}
	namedWindow("像素读写显示", WINDOW_FREERATIO);
	imshow("像素读写显示", image);
}

void QuickDemo::operators_demo(Mat&image) {//图像像素的算术操作
	Mat dst= Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	m = Scalar(2, 2, 2);
	multiply(image,m,dst);//乘法要用函数实现
	////加法
	//int w = image.cols;
	//int h = image.rows;
	//int dims = image.channels();
	//for (int row = 0; row < h; row++) {//遍历
	//	for (int col = 0; col < w; col++) {
	//			Vec3b p1 = image.at<Vec3b>(row, col);//三通道可以vec3b一次行获得三通道的数值(是个数组)
	//			Vec3b p2= m.at<Vec3b>(row, col);
	//			dst.at<Vec3b>(row, col)[0] = saturate_cast<uchar>(p1[0] + p2[0]);//这样相加很容易超过255需要函数帮忙
	//			dst.at<Vec3b>(row, col)[1] = saturate_cast<uchar>(p1[1] + p2[1]);//把里面数据与uchar的范围进行限定到0到255
	//			dst.at<Vec3b>(row, col)[2] = saturate_cast<uchar>(p1[2] + p2[2]);//在各种数据类型的转型中经常用到
	//		
	//	}
	//}
	add(image, m, dst);//加法操作OpenCV中的函数里面是用指针操作的，必然比上方的函数操作快
	subtract(image, m, dst);//减法操作
	divide(image,m,dst);//除法操作
	namedWindow("加法操作", WINDOW_FREERATIO);
	imshow("加法操作", dst);
}



static void on_lightness(int b, void* userdata) {
	Mat image = *((Mat*)userdata);//有前面的*才能把后面的地址变为数据
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	
	addWeighted(image,1.0,m,0,b,dst);//融合两张图并分配其占比
	namedWindow("对比度与亮度调整", WINDOW_AUTOSIZE);
	imshow("对比度与亮度调整", dst);
}

static void on_contrast(int b, void* userdata) {
	Mat image = *((Mat*)userdata);//有前面的*才能把后面的地址变为数据
	Mat dst = Mat::zeros(image.size(), image.type());
	Mat m = Mat::zeros(image.size(), image.type());
	double contrast = b / 100.0;//0到2间的值
	addWeighted(image, contrast, m, 0.0, 0, dst);//融合两张图并分配其占比
	namedWindow("对比度与亮度调整", WINDOW_AUTOSIZE);
	imshow("对比度与亮度调整", dst);
}

void QuickDemo::tracking_bar_demo(Mat&image) {//滚动条调整图片亮度
	namedWindow("对比度与亮度调整", WINDOW_AUTOSIZE);
	
	int lightness = 50;
	int max_value = 100;
	int contrast_value = 100;
	createTrackbar("Value Bar", "对比度与亮度调整", &lightness, max_value, on_lightness,(void*)(&image));//第五个是回调函数,第六个是把图像作为参数
	createTrackbar("Contrast Bar", "对比度与亮度调整", &lightness, 200, on_contrast, (void*)(&image));
	//on_lightness(50, &image);//userdata为指针需要用&来获得image的地址
}

void QuickDemo::bitwrite_demo(Mat&image) {
	Mat m1 = Mat::zeros(256, 256,CV_8UC3);
	Mat m2 = Mat::zeros(256, 256, CV_8UC3);
	rectangle(m1, Rect(100, 100, 80, 80), Scalar(255, 255, 0), -1, LINE_8, 0);//小于0是填充，大于0是绘制
	rectangle(m2, Rect(150, 150, 80, 80), Scalar(0, 255, 255), -1, LINE_8, 0);//画出一个矩形的操作
	imshow("M1", m1);
	imshow("M2", m2);
	Mat dst;
	bitwise_and(m1, m2, dst);//与操作g通道全是255则是绿色（BGR）
	imshow("像素位操作1", dst);
	bitwise_or(m1, m2, dst);
	imshow("像素位操作2", dst);
	bitwise_not(m1, dst);//就是pixel_visit_demo里的取反操作 Mat=~image;
	imshow("像素位操作3", dst);
	bitwise_xor(m1, m2, dst);
	imshow("像素位操作4", dst);
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
		int c = waitKey(2000);//停顿两秒
		if (c == 27) {//退出
			break;
		}
		applyColorMap(image, dst, color_map[index%13]);//0到13循环往复
		index++;
		namedWindow("颜色风格", WINDOW_AUTOSIZE);
		imshow("颜色风格", dst);						//可以配合键盘相应来保存其中的一些照片
	}
}

void QuickDemo::channels_demo(Mat&image) {//通道分量与合并
	std::vector<Mat>mv;//是一个数组可以放mat类型
	split(image,mv);
	imshow("蓝色", mv[0]);
	imshow("绿色", mv[1]);
	imshow("红色", mv[2]);
	Mat dst;
	//mv[1] = 0;
	//mv[2] = 0;//这样写的目的是然其他通道的颜色没有，只剩下蓝色
	merge(mv, dst);
	imshow("蓝色",dst);
	int from_to[] = { 0,2,1,1,2,0 };//0通道去2通道，2通道去0通道，1通道还在1
	mixChannels(&image,1,&dst,1, from_to,3);//1是图像由多少张，改变通道数3对
	imshow("通道混合", dst);
}
void QuickDemo::inrange_demo(Mat&image) {//可做抠图操作
	Mat hsv;
	cvtColor(image, hsv, COLOR_BGR2HSV);
	Mat mask;
	inRange(hsv, Scalar(100,43,46), Scalar(124,255,255), mask);//查hsv色彩空间的表就可以把绿色分离出来(lab、hsi空间都色彩分辨明确)
	imshow("mask1",mask);

	Mat redback = Mat::zeros(image.size(), image.type());
	redback = Scalar(255, 255, 255);//红色
	bitwise_not(mask, mask);//取反
	imshow("mask2", mask);
	//把image图片上不为黑色的迁移到redback，mask把原图中需抠出的目标分离出来了
	image.copyTo(redback, mask);//mask上不为0（黑色）的才迁移过来，其他的就不要了
	imshow("roi区域提取", redback);
}


void QuickDemo::pixel_statistic_demo(Mat&image) {//图像均值、方差、最大最小值提取
	double minv, maxv;
	Point minLoc, maxLoc;//minMaxLoc函数要求是单通道的，要分离通道
	std::vector<Mat>mv;//是一个数组可以放mat类型
	split(image, mv);
	for (int i = 0; i < mv.size(); i++) {
	minMaxLoc(mv[i], &minv, &maxv, &minLoc, &maxLoc,Mat());//在image区域寻找最大最小值并返回值指针和地址指针
	std::cout <<" No.channels:"<<i<< " min value:" << minv << " max value" << maxv << std::endl;
	
	}
	Mat mean, stddev;
	meanStdDev(image, mean, stddev);//均值和方差，一般用来求取ior区域的值（前面有mask来提取ior区域）
	//meam.at<double>(0,0);//可以把值单独打印出来
	std::cout << "mean" << mean << std::endl;
	std::cout<< "stddev" << stddev << std::endl;
}

void QuickDemo::drawing_demo(Mat&image) {//屏幕原点坐标在左上角
	Rect rect;
	rect.x = 50;
	rect.y = 50;//矩形的起点
	rect.width = 200;//矩形边长
	rect.height = 200;
	Mat bg = Mat::zeros(image.size(),image.type());
	rectangle(bg, rect, Scalar(0, 0, 255), -1, 8, 0);
	line(bg, Point(50, 50), Point(250, 250), Scalar(0, 255, 0), 2, LINE_AA, 0);//8还是会有锯齿用line_aa反锯齿
	circle(bg, Point(250, 250), 15, Scalar(0, 255, 0), 2, LINE_AA, 0);//point是圆的中心点
	RotatedRect rrt;
	rrt.center = Point(200, 200);
	rrt.size = Size(100, 200);//弧度的高低
	rrt.angle = 0.0;
	ellipse(bg, rrt, Scalar(0, 255, 255), 2, 8);
	Mat dst;
	addWeighted(image, 0.7, bg, 0.3, 0, dst);//融合两张图并分配其占比
	imshow("绘制矩形", dst);
}
void QuickDemo::random_drawing() {
	Mat canvans = Mat::zeros(Size(512,512),CV_8UC3);
	int w = canvans.cols;
	int h = canvans.rows;
	RNG rng(12345);
	while (true) {
		int c = waitKey(100);
		if (c == 27) {//退出
			break;
		}
		int x1=rng.uniform(0, w);//产生随机数0~w
		int y1 = rng.uniform(0, h);
		int x2 = rng.uniform(0, w);//产生随机数0~w
		int y2 = rng.uniform(0, h);
		int b = rng.uniform(0, 255);
		int g = rng.uniform(0, 255);
		int r = rng.uniform(0, 255);
		canvans = Scalar(0, 0, 0);
		line(canvans, Point(x1, y1), Point(x2, y2), Scalar(b, g, r), 2, LINE_AA, 0);//8还是会有锯齿用line_aa反锯齿
		imshow("随机绘制演示", canvans);
	}


}
void QuickDemo::polyline_drawing_demo() {
	//Mat canvans = Mat::zeros(Size(512, 512), CV_8UC3);
	//Point p1(200, 200);
	//Point p2(350, 100);
	//Point p3(450, 280);
	//Point p4(320, 450);
	//
	//std::vector<Point>pts(4);//生成一个数组来囊括5个点
	//pts.push_back(p1);
	//pts.push_back(p2);
	//pts.push_back(p3);
	//pts.push_back(p4);
	///*pts.push_back(p5);*/
	//polylines(canvans, pts, true, Scalar(0, 0, 255), 2, 8, 0);
	//imshow("多边形绘制", canvans);

	Mat canvas = Mat::zeros(Size(512, 512), CV_8UC3);//两种方式都可以填充多边形
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
	std::vector<std::vector<Point>> contours;//记得要用二维嵌套数组来储存
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
	drawContours(canvas, contours, 0, Scalar(0, 0, 255), -1, 8);//这个函数可以绘制多个多边形，第三0是指绘制第一个多边形（-1的话可以全部绘制），
	drawContours(canvas, contours, 0, Scalar(255, 0, 255), 2, 8);*/
	imshow("绘制", canvas);
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
//			rect.y = ep.y;//矩形的起点
//			rect.width = dx;//矩形边长
//			rect.height = dy;
//			imshow("ROI区域", z(rect));
//			rectangle(z, rect, Scalar(0, 0, 255), 2, 8, 0);
//			imshow("鼠标绘制", z);	
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
//			rect.y = ep.y;//矩形的起点
//			rect.width = dx;//矩形边长
//			rect.height = dy;
//			rectangle(z, rect, Scalar(0, 0, 255), 2, 8, 0);
//			imshow("鼠标绘制", z);
//			}
//		}
//	}
//	}
//void QuickDemo::mouse_drawing_demo(Mat&image) {
//	namedWindow("鼠标绘制",WINDOW_AUTOSIZE);
//	setMouseCallback("鼠标绘制", on_draw,(void*)(&image));
//	imshow("鼠标绘制", image);
//}
Mat temp;
static void on_draw(int event, int x, int y, int flag, void* userdata)
{
	//首先实例化传进来的img
	Mat img = *(Mat*)userdata;
	/*Mat imge=*(Mat*)userdata;*/
	//然后获取鼠标的停留点
	//1.开始点
	if (event == EVENT_LBUTTONDOWN)
	{
		sp.x = x, sp.y = y;
		std::cout << "the start point is (" << sp.x << "," << sp.y << ")" << std::endl;
	}
	else if (event == EVENT_LBUTTONUP)//就是放开鼠标的时候,就要开始计算矩形
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
			imshow("ROI区域", img(box));
			imshow("鼠标操作", img);
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
				imshow("鼠标操作", img);
			}
		}
	}
}

void QuickDemo::mouse_drawing_demo(Mat &img)
{   
	//1.创建窗口，用来显示
	namedWindow("鼠标操作", WINDOW_AUTOSIZE);
	temp = img.clone();
	//2.调用SetmouseCallback,绑定opencv窗口
	setMouseCallback("鼠标操作", on_draw, (void*)(&img));
	//api说明:("窗口名称"(string),将要callback绑定的函数,自定义参数userdata )
	//3.显示窗口imshow("窗口名称",传入图像)
	imshow("鼠标操作", img);
}

void QuickDemo::normalize_demo(Mat& image)
{
	Mat src1, src2, src3,m;
	m = Mat::zeros(image.size(), image.type());
	 m = Scalar(255, 255, 255);
	image.copyTo(src1);
	imshow("原图", src1);

	src1.convertTo(src2, CV_32F);
	/*imshow("格式转换图", src2);*/

	normalize(src2, src3, 0, 1, NORM_MINMAX);
	
	src3.convertTo(src3, CV_8UC3);
	multiply(src3, m, src3);//除法操作
	imshow("格式转换系数修正图", src3);//我的imshow不能显示32位的图像
	waitKey(0);


}


//void QuickDemo::norm_demo(Mat&image) {
//	Mat dst;
//	std::cout << image.type() << std::endl;
//	imshow("图像数据归一化", image);
//	image.convertTo(image, CV_32FC3);//数据类型转换CV_8UC3 变到 CV_32FC3
//	std::cout << image.type() << std::endl;
//	normalize(image, dst, 1.0, 0, NORM_MINMAX);
//	std::cout << dst.type() << std::endl;
//	/*dst.convertTo(dst, CV_8UC3);*/
//	imshow("图像数据归一化2", dst);
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
	flip(image, dst, 0);//上下翻转
	imshow("图像翻转",dst);
	flip(dst, dst, 1);//左右翻转
	imshow("图像翻转", dst);
	flip(dst, dst, -1);//对角线翻转
	imshow("图像翻转", dst);

}
void QuickDemo::rotate_demo(Mat&image) {
	Mat dst, M;
	int w = image.cols;
	int h = image.rows;
	M = getRotationMatrix2D(Point2f((w / 2), (h / 2)*sin(3.14 / 2)), 45, 1.0);//原来图像中心位置，角度，对图像的放大缩小
	double sin = abs(M.at<double>(0, 0));//是一个正数abs
	double cos = abs(M.at<double>(0, 1));//OpenCV很多都是用double
	int nw = cos * w + sin * h;
	int nh = sin * w + cos * h;
	M.at<double>(0, 2) = M.at<double>(0, 2) + (nw / 2 - w / 2);//得到新中心位置
	M.at<double>(1, 2) = M.at<double>(1, 2) + (nh / 2 - h / 2);//.at函数表示是第几行第几列的像素值（单通道）对于多通道用at<Vec3b>(i,j)[第几通道]
	warpAffine(image, dst, M, Size(nw, nh), INTER_LINEAR, 0, Scalar(255, 0, 0));
	imshow("旋转演示", dst);
}

void QuickDemo::showHistogram_demo(Mat&image) {//一维的直方图，opencv可以高纬度的

	std::vector<Mat> bgr_plane;//三通道分离
	split(image, bgr_plane);
	const int channels[1] = { 0 };
	const int bins[1] = { 256 };//256个灰度级别
	float hranges[2] = { 0,256 };//直方图的取值范围
	const float*ranges[1] = { hranges };//直方图的取值范围
	Mat b_hist;
	Mat g_hist;
	Mat r_hist;
	//计算Blue、Green、Red 通道的直方图   //mask：只取有数值的部分就是之前的掩膜     b_hist：直方图的输出
	calcHist(&bgr_plane[0], 1, 0, Mat(), b_hist, 1, bins, ranges);//第一个1是一张图的意思，第二个1是一维，直方图的取值范围0到255
	calcHist(&bgr_plane[1], 1, 0, Mat(), g_hist, 1, bins, ranges);
	calcHist(&bgr_plane[2], 1, 0, Mat(), r_hist, 1, bins, ranges);
	//显示直方图
	int hist_w = 512;
	int hist_h = 400;
	int bin_w = cvRound((double)hist_w / bins[0]);//cvRound返回跟参数最接近的整数值（四舍五入）  bins是指直方图的大小对于像素取值在0~255间的最少有256个
	Mat histImage = Mat::zeros(hist_h, hist_w, CV_8UC3);//创建画布
	//归一化直方图数据
	normalize(b_hist, b_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());//归一到画布宽度那么大
	normalize(g_hist, g_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	normalize(r_hist, r_hist, 0, histImage.rows, NORM_MINMAX, -1, Mat());
	//绘制直方图曲线											//在像素中y轴是向下的
	for (int i = 1; i < bins[0]; i++) {						//bins是俩个像素    图像的高度减去当前该像素值代表的直方图长度从而获得起点的高度  后面的类似
		line(histImage, Point((bin_w*(i - 1)), hist_h - cvRound(b_hist.at<float>(i - 1))), Point(bin_w*(i), hist_h - cvRound(b_hist.at<float>(i))), Scalar(255, 0, 0), 2, 8, 0);
		line(histImage, Point((bin_w*(i - 1)), hist_h - cvRound(g_hist.at<float>(i - 1))), Point(bin_w*(i), hist_h - cvRound(g_hist.at<float>(i))), Scalar(0, 255, 0), 2, 8, 0);
		line(histImage, Point((bin_w*(i - 1)), hist_h - cvRound(r_hist.at<float>(i - 1))), Point(bin_w*(i), hist_h - cvRound(r_hist.at<float>(i))), Scalar(0, 0, 255), 2, 8, 0);
	
	}
	//显示直方图
	namedWindow("Histogram Demo", WINDOW_AUTOSIZE);
	imshow("Histogram Demo", histImage);
}


void QuickDemo::Histogram_2d_demo(Mat&image) {
	Mat hsv, hs_hist;
	cvtColor(image, hsv, COLOR_BGR2HSV);//先转成hsv，h的范围是0~180 s的范围是0~255
	int hbins = 30, sbins = 32;   //h分30间隔，s分32间隔
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
	imshow("灰度图像", gray);
	Mat dst;
	equalizeHist(gray, dst);
	imshow("直方图均衡化演示",dst);
}

void QuickDemo::blur_demo(Mat&image) {
	Mat dst;
	blur(image, dst, Size(13, 13), Point(-1, -1));//均值卷积 13*13的卷积核 且 支持一维卷积
	imshow("图像模糊", dst);
}

void QuickDemo::gaussin_blur_demo(Mat&image) {

	Mat dst;
	GaussianBlur(image, dst, Size(5, 5), 15);//均值卷积 13*13的卷积核 且 支持一维卷积
	imshow("高斯模糊", dst);
}

void QuickDemo::bifilter_demo(Mat&image) {
	Mat dst;
	bilateralFilter(image, dst, 0, 100, 10);
	imshow("高斯双边模糊", dst);
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
	namedWindow("对比度与亮度调整", WINDOW_AUTOSIZE);
	imshow("对比度与亮度调整", dst);
}

void QuickDemo::corrosion_expand(Mat&image) {//滚动条调整图片亮度
	namedWindow("对比度与亮度调整", WINDOW_AUTOSIZE);

	int lightness = 3;
	int max_value = 21;
	int contrast_value = 100;
	createTrackbar("Contrast Bar", "对比度与亮度调整", &lightness, max_value, onn_contrast, (void*)(&image));
	//on_lightness(50, &image);//userdata为指针需要用&来获得image的地址
}