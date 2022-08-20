#include <opencv2/opencv.hpp>
#include <iostream>
#include <quickopencv.h>
#include <math.h>
#include <iostream>
#include <fstream>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/calib3d/calib3d.hpp"
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/core/core.hpp"

using namespace std;
using namespace cv;

int main(int argc, char** argv)
{
	//获取文件图片
	Mat src = imread("F:\\c++learning\\OpenCVsecond\\2233.png");
	if (src.empty())
	{
		printf("could not load image...\n");
		return -1;
	}
	/*namedWindow("输入窗口",WINDOW_FREERATIO);*/
	imshow("输入窗口", src);
	QuickDemo qd;
	qd.tracking_bar_demo(src);

	/*int cols = (src.cols-1)*src.channels();
	int offsetx = src.channels;
	int rows = src.rows;
	for (int row = 1; row < (row - 1); row++) {
		const uchar* current = src.ptr<uchar>(row);
		const uchar* previous = src.ptr<uchar>(row-1);
		const uchar* next = src.ptr<uchar>(row+1);
		for (int col = offsetx; col < cols; col++) {
			current[col] = 5 * current[col] - (current[col - offsetx] - current[col + offsetx]+previous[col]+next[col]);
		}
	}*/



	waitKey(0);
	destroyAllWindows();
	return 0;
}

