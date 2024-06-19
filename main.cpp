// 고종황제 사진 복원 작업, 컬러영상
/*
#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    // 원본영상
    Mat img_Original;
    img_Original = imread("GoJong.jpg", IMREAD_COLOR);

    // 가우시안 블러
    Mat img_Gaussian;
    GaussianBlur(img_Original, img_Gaussian, Size(3, 3), 0);

    // 양방향 필터
    Mat img_Bilateral;
    bilateralFilter(img_Original, img_Bilateral, -1, 10, 5);

    // 비지역적 평균 비교
    Mat img_NonLocalMeans;
    fastNlMeansDenoisingColored(img_Bilateral, img_NonLocalMeans, 10, 10, 7, 21);

    // 세부 사항 강조 및 샤프닝
    Mat img_Sharpened;
    Mat kernel = (Mat_<float>(3, 3) <<
        0, -1, 0,
        -1, 5, -1,
        0, -1, 0);
    filter2D(img_NonLocalMeans, img_Sharpened, -1, kernel);

    // 대비 개선
    Mat img_Contrast;
    cvtColor(img_Sharpened, img_Contrast, COLOR_BGR2YCrCb);
    vector<Mat> channels(3);
    split(img_Contrast, channels);
    equalizeHist(channels[0], channels[0]); // Y 채널 대비 개선
    merge(channels, img_Contrast);
    cvtColor(img_Contrast, img_Contrast, COLOR_YCrCb2BGR);


    // 결과 표시
    imshow("원본", img_Original);
    imshow("가우시안 블러", img_Gaussian);
    imshow("양방향 필터", img_Bilateral);
    imshow("비지역적 평균 비교", img_NonLocalMeans);
    imshow("샤프닝", img_Sharpened);
    imshow("대비 개선", img_Contrast);

    waitKey(0);

    return 0;
}
*/


// 김구, 윤봉길 의사 사진 복원 작업

#include <stdio.h>
#include <opencv2/opencv.hpp>

using namespace cv;
using namespace std;

int main()
{
    // 원본영상
    Mat img_Original;
    img_Original = imread("KimGu.png", IMREAD_COLOR);

    // 가우시안 블러
    Mat img_Gaussian;
    GaussianBlur(img_Original, img_Gaussian, Size(3, 3), 0);

    // 양방향 필터
    Mat img_Bilateral;
    bilateralFilter(img_Original, img_Bilateral, -1, 10, 5);

    // 비지역적 평균 비교
    Mat img_NonLocalMeans;
    fastNlMeansDenoisingColored(img_Bilateral, img_NonLocalMeans, 10, 10, 7, 21);

    // 스필릿을 통해 각 체널을 BGR분리
    vector<Mat> bgr_planes;
    split(img_NonLocalMeans, bgr_planes);
    
    // 모폴로지 연산을 위한 커널
    Mat kernel = getStructuringElement(MORPH_RECT, Size(3, 3));

    morphologyEx(bgr_planes[0], bgr_planes[0], MORPH_CLOSE, kernel);
    morphologyEx(bgr_planes[1], bgr_planes[1], MORPH_CLOSE, kernel);
    morphologyEx(bgr_planes[2], bgr_planes[2], MORPH_CLOSE, kernel);

    // 변경된 채널들을 다시 하나의 이미지로 병합합니다.
    Mat img_mergedImg;
    merge(bgr_planes, img_mergedImg);

    // 결과 표시
    imshow("원본", img_Original);
    imshow("가우시안 블러", img_Gaussian);
    imshow("양방향 필터", img_Bilateral);
    imshow("비지역적 평균 비교", img_NonLocalMeans);
    imshow("각 채널 별 모폴로지", img_mergedImg);
   
    waitKey(0);

    return 0;
}




