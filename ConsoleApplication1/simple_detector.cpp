#include <iostream>
#include <sstream>
#include <opencv2/imgcodecs.hpp>
#include <opencv2/imgproc.hpp>
#include <opencv2/videoio.hpp>
#include <opencv2/highgui.hpp>
#include <opencv2/video.hpp>
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;


int main(int argc, char** argv)
{
    //Creamos un consturctor para el backgroud substactor
    Ptr<BackgroundSubtractor> pBackSub;
    //Creamos que tipo de background substactor se va a usar
    //pBackSub = createBackgroundSubtractorKNN();
    pBackSub = createBackgroundSubtractorMOG2();

    //Se inicializa la camara del sistema
    VideoCapture webCam;

    if (!webCam.open(0))
        return 0;
    //Se finaliza si se deja de detectar la camara
    for (;;)
    {
        //Creamos los tipos necesarios para que openCV pueda interactuar con la camara
        Mat originalFrame, detecctionFrame;
        //Se setea camara en el fromato correcto para poder interactuar con el
        webCam >> originalFrame;
        
        if (originalFrame.empty()) break; 
        //Se aplica el metodo de susbtraccion a las imagnes y se guarda em otra.
        pBackSub->apply(originalFrame, detecctionFrame);
        //Metodo para tener los dos tracks de la camara en una misma ventana
        rectangle(originalFrame, cv::Point(10, 2), cv::Point(100, 20),
            cv::Scalar(255, 255, 255), -1);
        //mostramos la camara y la deteccion
        imshow("Camara", originalFrame);

        imshow("Presiona w para finalizar", detecctionFrame);

        if (waitKey(1) == 'w') break;  
    }

    return 0;
}