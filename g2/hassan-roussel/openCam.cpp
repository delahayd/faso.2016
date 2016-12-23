/**
 * @openCam.cpp
 * @brief People counting system with Raspberry Pi
 * @author Kévin Hassan Godefroi Roussel
 */
#include <math.h>
#include <iostream>
#include <vector>

#include "opencv2/objdetect.hpp"
#include "opencv2/videoio.hpp"
#include "opencv2/highgui.hpp"
#include "opencv2/opencv.hpp"

using namespace cv;
using namespace std;

/* Global variables*/
const char* window_title1 = "Camera-Normal";
const char* faces_cascade_name = "haarcascade_frontalface_alt.xml";

int main( int argc, char** argv)
{
  VideoCapture capture;
  Mat frame;
  CascadeClassifier faces_cascade;
  String text_window;
  vector<Rect> faces;
  int peopleInRoom = 0;

  //Si on arrive pas à lancer le fichier XML on retourne une erreur
  if( !faces_cascade.load( faces_cascade_name ) )
  {
    cerr<<"Error loading faces cascade"<<endl;
    exit(EXIT_FAILURE);
  };
  capture.open(0); //Ouvrir la caméra par défault

  //Si la caméra ne marche pas on retourne une erreur s
  if (!capture.isOpened()){
    cerr<<"Error opening video capture !"<<endl;
    exit(EXIT_FAILURE);
  }
  const int height_cam = capture.get(CV_CAP_PROP_FRAME_HEIGHT);
  const int width_cam = capture.get(CV_CAP_PROP_FRAME_WIDTH);

  cout<<"La caméra filme avec "<<capture.get(CV_CAP_PROP_FPS)<<" FPS et une résolution de "<<width_cam<<"x"<<height_cam<<endl;

  namedWindow(window_title1);
  cout<<"Appuyez sur ESC ou Q pour fermer la fenêtre "<<endl;

  while(capture.read(frame)){
    if( frame.empty() )
    {
      printf("No captured frame -- Break!");
      exit(EXIT_FAILURE);
    }
    //cvtColor( frame, frame, COLOR_BGR2GRAY );
    //equalizeHist( frame, frame );
    flip(frame,frame,1);//horizontal inversion

    faces_cascade.detectMultiScale( frame, faces, 1.1, 2, 0, Size(100, 100),Size(width_cam, height_cam) );
    putText(frame,to_string(faces.size())+" visage(s)",Point(15, 15),FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,0,0)); //Image, string, origine, fontFace, fontScale, color

    if(faces.size()>0){
      for(int i=0;i<faces.size();i++){
        circle(frame, Point(faces[i].x+faces[i].width/2,faces[i].y+faces[i].height/2),faces[i].height/2 , Scalar(0,0,255));// Dessiner un cercle autours du visage des personnes
        text_window = "x = "+to_string(faces[i].x)+" y= "+to_string(faces[i].y);
        putText(frame,text_window,Point(15, 40*(i+1)),FONT_HERSHEY_SIMPLEX, 0.5 , cv::Scalar(0,255,0));
      }
    }
    imshow(window_title1, frame);// Ajouter l'image à la fenetre
    char key = (char) waitKey(30);   // explicit cast
    if (key == 27 || key == 'q' || key == 'Q') break;            // break if `esc' key was pressed.
  }
  destroyAllWindows() ;
  return 0;
}
