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
    //Se finaliza si no se detecta la camara
    if (!webCam.open(0))
        return 0;
    for (;;)
    {
        //Creamos los tipos necesarios para que openCV pueda interactuar con la camara
        Mat originalFrame, detecctionFrame;
        //Se setea camara en el fromato correcto para poder interactuar con el
        webCam >> originalFrame;
        //Si no se detecta nada, se finaliza el metodo
        if (originalFrame.empty()) break; 
        //Se aplica el metodo de susbtraccion a las imagnes y se guarda em otra.
        pBackSub->apply(originalFrame, detecctionFrame);
        //Mostramos la camara y la deteccion
        imshow("Camara", originalFrame);
        //Mostramos en una ventana aprte el movimiento que detecta la camara
        imshow("Presiona w para finalizar", detecctionFrame);
        //Al presioanr la tecla ESC se cierra la ventana
        
        if (waitKey(1) == 27) { 
            break;
        }
           
    }

    return 0;
}