// ����Ȳ�� ���� ���� �۾�, �÷�����
/*
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    // ��������
    Mat img_Original;
    img_Original = imread("GoJong.jpg", IMREAD_COLOR);

    // ����þ� ��
    Mat img_Gaussian;
    GaussianBlur(img_Original, img_Gaussian, Size(3, 3), 0);

    // ����� ����
    Mat img_Bilateral;
    bilateralFilter(img_Original, img_Bilateral, -1, 10, 5);

    // �������� ��� ��
    Mat img_NonLocalMeans;
    fastNlMeansDenoisingColored(img_Bilateral, img_NonLocalMeans, 10, 10, 7, 21);

    // ���� ���� ���� �� ������
    Mat img_Sharpened;
    Mat kernel = (Mat_<float>(3, 3) <<
        0, -1, 0,
        -1, 5, -1,
        0, -1, 0);
    filter2D(img_NonLocalMeans, img_Sharpened, -1, kernel);

    // ��� ����
    Mat img_Contrast;
    cvtColor(img_Sharpened, img_Contrast, COLOR_BGR2YCrCb);
    vector<Mat> channels(3);
    split(img_Contrast, channels);
    equalizeHist(channels[0], channels[0]); // Y ä�� ��� ����
    merge(channels, img_Contrast);
    cvtColor(img_Contrast, img_Contrast, COLOR_YCrCb2BGR);


    // ��� ǥ��
    imshow("����", img_Original);
    imshow("����þ� ��", img_Gaussian);
    imshow("����� ����", img_Bilateral);
    imshow("�������� ��� ��", img_NonLocalMeans);
    imshow("������", img_Sharpened);
    imshow("��� ����", img_Contrast);

    waitKey(0);

    return 0;
}
*/


// �豸, ������ �ǻ� ���� ���� �۾�

#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    // ��������
    Mat img_Original;
    img_Original = imread("KimGu.png", IMREAD_COLOR);

    // ����þ� ��
    Mat img_Gaussian;
    GaussianBlur(img_Original, img_Gaussian, Size(3, 3), 0);

    // ����� ����
    Mat img_Bilateral;
    bilateralFilter(img_Original, img_Bilateral, -1, 10, 5);

    // �������� ��� ��
    Mat img_NonLocalMeans;
    fastNlMeansDenoisingColored(img_Bilateral, img_NonLocalMeans, 10, 10, 7, 21);

    // ���ʸ��� ���� �� ü���� BGR�и�
    vector<Mat> bgr_planes;
    split(img_NonLocalMeans, bgr_planes);
    
    // �������� ������ ���� Ŀ��
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));

    morphologyEx(bgr_planes[0], bgr_planes[0], MORPH_CLOSE, kernel);
    morphologyEx(bgr_planes[1], bgr_planes[1], MORPH_CLOSE, kernel);
    morphologyEx(bgr_planes[2], bgr_planes[2], MORPH_CLOSE, kernel);

    // ����� ä�ε��� �ٽ� �ϳ��� �̹����� �����մϴ�.
    Mat img_mergedImg;
    merge(bgr_planes, img_mergedImg);

    // ��� ǥ��
    imshow("����", img_Original);
    imshow("����þ� ��", img_Gaussian);
    imshow("����� ����", img_Bilateral);
    imshow("�������� ��� ��", img_NonLocalMeans);
    imshow("�� ä�� �� ��������", img_mergedImg);
   
    waitKey(0);

    return 0;
}




