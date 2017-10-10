#include <opencv2/dnn.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/highgui.hpp>
#include <fstream>
#include <iostream>

using namespace cv;

int main(int argc, char** argv)
{
	/* task 6 */
	const String keys =
		"{@image		 |      | image for processing }"
		"{@description   |      | model description }"
		"{@params        |	    | trained model hyperparameters }"
		"{@classes       |      | file with classes description }"
		;
	CommandLineParser parser(argc, argv, keys);
	parser.about("DNN sampel application v1.0.0");
	String imgpath = parser.get<String>(0);
	String model_descrption = parser.get<String>(1);
	String model_params = parser.get<String>(2);
	String classes = parser.get<String>(3);
	if (!parser.check())
	{
		parser.printErrors();
		return 0;
	}

	/* task 7 */
	Mat img = imread(imgpath);

	/* task 8 */
	dnn::Net network = dnn::readNetFromCaffe(model_descrption, model_params);

	/* task 9 */
	Mat blob = dnn::blobFromImage(img, 1, Size(224, 224), Scalar(), true);

	/* task 10 */
	network.setInput(blob, "data");

	/* task 11 */
	Mat out = network.forward("prob");
	

	/* task 12 */
	double max_val;
	Point max_loc;
	minMaxLoc(out, NULL, &max_val, NULL, &max_loc); 
	std::cout << max_loc.x;

	std::ifstream file(classes.c_str());
	std::string line;
	int linecount = 0;
	while (std::getline(file, line)) {
		std::istringstream stream(line);
		while (stream)
		{
			std::string s;
			if (!std::getline(stream, s)) break;
			if (linecount == max_loc.x)
				std::cout << s << std::endl;
		}
		++linecount;
	}

    return 0;
 }
