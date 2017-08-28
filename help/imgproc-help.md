# Примеры использования модуля imgproc библиотеки OpenCV

## Содержание

1. [Функция blur][blur]
1. [Функция filter2D][filter2D]
1. [Функция Sobel][Sobel]
1. [Функция Laplacian][Laplacian]
1. [Функции erode/dilate][erode_dilate]
1. [Функция Canny][Canny]
1. [Функция calcHist][calcHist]

## Функция blur

```cpp
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp> 

using namespace std;
using namespace cv;

const char helper[] = 
    "Sample_blur.exe  <img_file>\n\
    \t<img_file> - image file name\n";

int main(int argc, char* argv[])
{
    const char *initialWinName = "Initial Image", 
               *blurWinName = "blur";
    Mat img, blurImg;
    if (argc < 2)
    {
        cout << helper;
        return 1;
    }
    
    // загрузка изображения
    img = imread(argv[1], 1);
    // применение операции размытия
    blur(img, blurImg, Size(5, 5));

    // отображение исходного изображения и результата размытия
    namedWindow(initialWinName, CV_WINDOW_AUTOSIZE);
    namedWindow(blurWinName, CV_WINDOW_AUTOSIZE);
    imshow(initialWinName, img);
    imshow(blurWinName, blurImg);
    waitKey();

    // закрытие окон
    destroyAllWindows();
    // освобождение ресурсов
    img.release();
    blurImg.release();
    return 0;
}
```

## Функция filter2D

```cpp
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp> 

using namespace std;
using namespace cv;

const char helper[] = 
    "Sample_filter2D.exe <img_file>\n\
    \t<img_file> - image file name\n";

int main(int argc, char* argv[])
{
    // константы для определения названия окон
    const char *initialWinName = "Initial Image", *resultWinName = "Filter2D";    
    // константы для хранения ядра фильтра
    const float kernelData[] = {-0.1f, 0.2f, -0.1f,
                                 0.2f, 3.0f,  0.2f,
                                -0.1f, 0.2f, -0.1f};
    const Mat kernel(3, 3, CV_32FC1, (float *)kernelData);

    // объекты для хранения исходного и результирующего изображений
    Mat src, dst;
    
    // проверка аргументов командной строки
    if (argc < 2)
    {
        cout << helper;
        return 1;
    }
    
    // загрузка изображения
    src = imread(argv[1], 1); 
    
    // применение фильтра
    filter2D(src, dst, -1, kernel);
    
    // отображение исходного изображения и результата применения фильтра
    namedWindow(initialWinName, CV_WINDOW_AUTOSIZE);
    imshow(initialWinName, src);
    namedWindow(resultWinName, CV_WINDOW_AUTOSIZE);
    imshow(resultWinName, dst);
    waitKey();
    
    // закрытие окон
    destroyAllWindows();
    // освобождение ресурсов
    src.release();
    dst.release();
    return 0;
}
```

## Функция Sobel

```cpp
// Пример выделения краев на изображении

#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp> 

using namespace std;
using namespace cv;

const char helper[] = 
    "Sample_Sobel.exe  <img_file>\n\
    \t<img_file> - image file name\n";

int main(int argc, char* argv[])
{
    const char *initialWinName = "Initial Image", 
               *xGradWinName = "Gradient in the direction Ox",
               *yGradWinName = "Gradient in the direction Oy",
               *gradWinName = "Gradient";
    int ddepth = CV_16S;
    double alpha = 0.5, beta = 0.5;
    Mat img, grayImg, xGrad, yGrad, xGradAbs, yGradAbs, grad;
    if (argc < 2)
    {
        cout << helper;
        return 1;
    }
    // загрузка изображения
    img = imread(argv[1], 1);
    // удаление шумов с помощью фильтра Гаусса
    GaussianBlur(img, img, Size(3,3), 0, 0, BORDER_DEFAULT);
    // преобразование в оттенки серого
    cvtColor(img, grayImg, CV_RGB2GRAY);
    // вычисление производных по двум направлениям
    Sobel(grayImg, xGrad, ddepth, 1, 0); // по Ox
    Sobel(grayImg, yGrad, ddepth, 0, 1); // по Oy
    // преобразование градиентов в 8-битные беззнаковые
    convertScaleAbs(xGrad, xGradAbs);
    convertScaleAbs(yGrad, yGradAbs);
    // поэлементное вычисление взвешенной суммы двух массивов
    addWeighted(xGradAbs, alpha, yGradAbs, beta, 0, grad);

    // отображение результата
    namedWindow(initialWinName, CV_WINDOW_AUTOSIZE);
    namedWindow(xGradWinName, CV_WINDOW_AUTOSIZE);
    namedWindow(yGradWinName, CV_WINDOW_AUTOSIZE);
    namedWindow(gradWinName, CV_WINDOW_AUTOSIZE);
    imshow(initialWinName, img);
    imshow(xGradWinName, xGradAbs);
    imshow(yGradWinName, yGradAbs);
    imshow(gradWinName, grad);
    waitKey();

     // закрытие окон
    destroyAllWindows();
    // осовобождение памяти
    img.release();
    grayImg.release();
    xGrad.release();
    yGrad.release();
    xGradAbs.release();
    yGradAbs.release();
    return 0;
}
```

## Функция Laplacian

```cpp
// Пример выделения краев на изображении

#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp> 

using namespace std;
using namespace cv;

const char helper[] = 
    "Sample_Laplacian.exe  <img_file>\n\
    \t<img_file> - image file name\n";

int main(int argc, char* argv[])
{
    const char *initialWinName = "Initial Image",
               *laplacianWinName = "Laplacian";
    Mat img, grayImg, laplacianImg, laplacianImgAbs;
    int ddepth = CV_16S;
    if (argc < 2)
    {
        cout << helper;
        return 1;
    }
    // загрузка изображения
    img = imread(argv[1], 1);
    // удаление шумов с помощью фильтра Гаусса
    GaussianBlur(img, img, Size(3,3), 0, 0, BORDER_DEFAULT);
    // преобразование в оттенки серого
    cvtColor(img, grayImg, CV_RGB2GRAY);
    // применение оператора Лапласа
    Laplacian(grayImg, laplacianImg, ddepth);
    convertScaleAbs(laplacianImg, laplacianImgAbs);
    
    // отображение результата
    namedWindow(initialWinName, CV_WINDOW_AUTOSIZE);
    namedWindow(laplacianWinName, CV_WINDOW_AUTOSIZE);
    imshow(initialWinName, img);
    imshow(laplacianWinName, laplacianImgAbs);
    waitKey();

     // закрытие окон
    destroyAllWindows();
    // осовобождение памяти
    img.release();
    grayImg.release();
    laplacianImg.release();
    laplacianImgAbs.release();
    return 0;
}
```

## Функции erode/dilate

```cpp
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp> 

using namespace std;
using namespace cv;

const char helper[] = 
    "Sample_erode_dilate.exe  <img_file>\n\
    \t<img_file> - image file name\n";

int main(int argc, char* argv[])
{
    const char *initialWinName = "Initial Image", 
               *erodeWinName = "erode", *dilateWinName = "dilate";
    Mat img, erodeImg, dilateImg, element;
    if (argc < 2)
    {
        cout << helper;
        return 1;
    }
    // загрузка изображения
    img = imread(argv[1], 1);
    // вычисление эрозии и дилатации
    element = Mat();
    erode(img, erodeImg, element);
    dilate(img, dilateImg, element);
    // отображение исходного изображения и результата
    // применения морфологических операций "эрозия" и "дилатация"
    namedWindow(initialWinName, CV_WINDOW_AUTOSIZE);
    namedWindow(erodeWinName, CV_WINDOW_AUTOSIZE);
    namedWindow(dilateWinName, CV_WINDOW_AUTOSIZE);
    imshow(initialWinName, img);
    imshow(erodeWinName, erodeImg);
    imshow(dilateWinName, dilateImg);
    waitKey();

    // закрытие окон
    destroyAllWindows();
    // освобождение ресурсов
    img.release();
    erodeImg.release();
    dilateImg.release();
    return 0;
}
```

## Функция Canny

```cpp
// Пример выделения краев на изображении

#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp> 

using namespace std;
using namespace cv;

const char helper[] = 
    "Sample_Canny.exe  <img_file>\n\
    \t<img_file> - image file name\n";

int main(int argc, char* argv[])
{
    const char *cannyWinName = "Canny detector";
    Mat img, grayImg, edgesImg;
    double lowThreshold = 70, uppThreshold = 260;
    if (argc < 2)
    {
        cout << helper;
        return 1;
    }
    // загрузка изображения
    img = imread(argv[1], 1);
    // удаление шумов
    blur(img, img, Size(3,3));
    // преобразование в оттенки серого
    cvtColor(img, grayImg, CV_RGB2GRAY);
    // применение оператора Лапласа
    Canny(grayImg, edgesImg, lowThreshold, uppThreshold);
    
    // отображение результата
    namedWindow(cannyWinName, CV_WINDOW_AUTOSIZE);
    imshow(cannyWinName, edgesImg);
    waitKey();

    // закрытие окон
    destroyAllWindows();
    // осовобождение памяти
    img.release();
    grayImg.release();
    edgesImg.release();
    return 0;
}
```

## Функция calcHist

```cpp
#include <iostream>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp> 

using namespace std;
using namespace cv;

const char helper[] = 
    "Sample_calcHist.exe  <img_file>\n\
    \t<img_file> - image file name\n";

int main(int argc, char* argv[])
{
    const char *initialWinName = "Initial Image",
               *histWinName = "Histogram";
    Mat img, bgrChannels[3], bHist, gHist, rHist, histImg;
    int kBins = 256; // количество бинов гистограммы
    float range[] = {0.0f, 256.0f}; // интервал изменения значений бинов
    const float* histRange = { range };
    bool uniform = true; // равномерное распределение интервала по бинам
    bool accumulate = false; // запрет очищения перед вычислением гистограммы
    int histWidth = 512, histHeight = 400; // размеры для отображения гистограммы
    int binWidth = cvRound((double)histWidth / kBins); // количество пикселей на бин
    int i, kChannels = 3;
    Scalar colors[] = {Scalar(255, 0, 0), Scalar(0, 255, 0), Scalar(0, 0, 255)};
    if (argc < 2)
    {
        cout << helper;
        return 1;
    }
    // загрузка изображения
    img = imread(argv[1], 1);
    // выделение каналов изображения
    split(img, bgrChannels);
    // вычисление гистограммы для каждого канала
    calcHist(&bgrChannels[0], 1, 0, Mat(), bHist, 1, &kBins, 
        &histRange, uniform, accumulate);
    calcHist(&bgrChannels[1], 1, 0, Mat(), gHist, 1, &kBins, 
        &histRange, uniform, accumulate);
    calcHist(&bgrChannels[2], 1, 0, Mat(), rHist, 1, &kBins, 
        &histRange, uniform, accumulate);

    // построение гистограммы
    histImg = Mat(histHeight, histWidth, CV_8UC3, Scalar(0, 0, 0));
    // нормализация гистограмм в соответствии с размерами окна для отображения
    normalize(bHist, bHist, 0, histImg.rows, 
        NORM_MINMAX, -1, Mat());
    normalize(gHist, gHist, 0, histImg.rows, 
        NORM_MINMAX, -1, Mat());
    normalize(rHist, rHist, 0, histImg.rows, 
        NORM_MINMAX, -1, Mat());
    
    for (i = 1; i < kBins; i++)
    {
        line(histImg, Point(binWidth * (i-1), histHeight - cvRound(bHist.at<float>(i-1))) ,
            Point(binWidth * i, histHeight - cvRound(bHist.at<float>(i)) ),
            colors[0], 2, 8, 0);
        line(histImg, Point(binWidth * (i-1), histHeight - cvRound(gHist.at<float>(i-1))) ,
            Point(binWidth * i, histHeight - cvRound(gHist.at<float>(i)) ),
            colors[1], 2, 8, 0);
        line(histImg, Point(binWidth * (i-1), histHeight - cvRound(rHist.at<float>(i-1))) ,
            Point(binWidth * i, histHeight - cvRound(rHist.at<float>(i)) ),
            colors[2], 2, 8, 0);
    }
    // отображение исходного изображения и гистограмм
    namedWindow(initialWinName, CV_WINDOW_AUTOSIZE);
    namedWindow(histWinName, CV_WINDOW_AUTOSIZE);
    imshow(initialWinName, img);
    imshow(histWinName, histImg);
    waitKey();
    
    // закрытие окон
    destroyAllWindows();
    // осовобождение памяти
    img.release();
    for (i = 0; i < kChannels; i++)
    {
        bgrChannels[i].release();
    }
    bHist.release();
    gHist.release();
    rHist.release();
    histImg.release();
    return 0;
}
```

<!-- LINKS -->

[blur]: https://github.com/UNN-VMK-Software/opencv-dnn-practice/help/imgproc-help.md#%D0%A4%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D1%8F-blur
[filter2D]: https://github.com/UNN-VMK-Software/opencv-dnn-practice/help/imgproc-help.md#%D0%A4%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D1%8F-filter2d
[Sobel]: https://github.com/UNN-VMK-Software/opencv-dnn-practice/help/imgproc-help.md#%D0%A4%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D1%8F-Sobel
[Laplacian]: https://github.com/UNN-VMK-Software/opencv-dnn-practice/help/imgproc-help.md#%D0%A4%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D1%8F-Laplacian
[erode_dilate]: https://github.com/UNN-VMK-Software/opencv-dnn-practice/help/imgproc-help.md#%D0%A4%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D1%8F-erodedilate
[Canny]: https://github.com/UNN-VMK-Software/opencv-dnn-practice/help/imgproc-help.md#%D0%A4%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D1%8F-Canny
[calcHist]: https://github.com/UNN-VMK-Software/opencv-dnn-practice/help/imgproc-help.md#%D0%A4%D1%83%D0%BD%D0%BA%D1%86%D0%B8%D1%8F-calcHist
