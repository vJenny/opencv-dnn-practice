# Примеры использования модуля imgproc библиотеки OpenCV

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