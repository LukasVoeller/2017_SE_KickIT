//============================================================================
// Name        : Test5.cpp
// Author      : Unbekannt
// Version     : Überarbeitet & Kommentiert, Lukas Völler
// Copyright   : Your copyright notice
// Description : Programm for an autonomus Soccertable
//============================================================================
#include <string.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <net/if.h>
#include <linux/can.h>
#include <linux/can/raw.h>
#include <string.h>
#include <unistd.h>
#include <pylon/PylonIncludes.h>
#include <pylon/gige/BaslerGigEInstantCamera.h>
#include <opencv2/opencv.hpp>
#include <opencv2/objdetect/objdetect.hpp>
#include <opencv2/video/video.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <fstream>
#include <stdio.h>
#include <cstdio>
#include <chrono>

using namespace cv;
using namespace std;
using namespace Pylon;

int BlueLow = 234;
int GreenLow = 206;
int RedLow = 0;

int BlueHigh = 255;
int GreenHigh = 255;
int RedHigh = 255;
int soc;
int read_can_port;
int nibble = 1;		//Wozu ist der gut???

//Datei für Mittelpunkt-Koordinate des Balles
double lastx = 0;
double lasty = 0;
double x, y;

//Datei für Torwart-Abweichung
fstream TW("Torwart.txt", ios::out);

Point TorwartSoll;
Point TorwartMax;
Point TorwartMin;
Point TorwartMitte;
int TorwartAbweichung;

int exitCode = 0;
Pylon::PylonAutoInitTerm autoInitTerm;
CGrabResultPtr ptrGrabResult;

int open_port(const char *port) {
	struct ifreq ifr;
	struct sockaddr_can addr;

	//open socket
	soc = socket(PF_CAN, SOCK_RAW, CAN_RAW);
	if (soc < 0) {
		return -1;
	}

	addr.can_family = AF_CAN;
	strcpy(ifr.ifr_name, port);
	if (ioctl(soc, SIOCGIFINDEX, &ifr) < 0) {
		return (-1);
	}

	addr.can_ifindex = ifr.ifr_ifindex;
	fcntl(soc, F_SETFL, O_NONBLOCK);
	if (bind(soc, (struct sockaddr *) &addr, sizeof(addr)) < 0) {
		return -1;
	}

	return 0;
}

int send_port(struct can_frame *frame) {
	int retval = write(soc, frame, sizeof(struct can_frame));

	if (retval != sizeof(struct can_frame)) {
		return -1;
	}

	return 0;
}

void read_port() {
	struct can_frame frame_rd;
	int recvbytes = 0;

	read_can_port = 1;
	while (read_can_port) {
		struct timeval timeout = { 1, 0 };
		fd_set readSet;
		FD_ZERO(&readSet);
		FD_SET(soc, &readSet);

		if (select((soc + 1), &readSet, NULL, NULL, &timeout) >= 0) {
			if (!read_can_port) {
				break;
			}

			if (FD_ISSET(soc, &readSet)) {
				recvbytes = read(soc, &frame_rd, sizeof(struct can_frame));

				if (recvbytes) {
					printf("dlc = %d, data = %s\n", frame_rd.can_dlc, frame_rd.data);
					read_can_port = 0;
				}
			}
		}
	}
}

int close_port() {
	close(soc);
	return 0;
}

void frame_init(int ID, int DLC, int Data_0, int Data_1, int Data_2, int Data_3,
	int Data_4, int Data_5, int Data_6, int Data_7) {
	int ret = open_port("can0");
	//printf("open: %d\n", ret);
	struct can_frame frame;
	frame.can_id = ID;		//COB ID 200 für RxPDO1 + Can ID 1
	frame.can_dlc = DLC; 	//Datenanzahl
	frame.data[0] = Data_0; //Daten
	frame.data[1] = Data_1; //Daten
	frame.data[2] = Data_2; //...
	frame.data[3] = Data_3;
	frame.data[4] = Data_4;
	frame.data[5] = Data_5;
	frame.data[6] = Data_6;
	frame.data[7] = Data_7;
	ret = send_port(&frame);
	//printf("sent: %d\n", ret);
	close_port();
}

//Menupunkt 1) Motor initialisieren
void driver_init() {
	cout << "Reseten" << endl;
	frame_init(0x601, 0x8, 0x23, 0x00, 0x20, 0xB, 0x00, 0x00, 0x00, 0x00); 	//Reset Command
	sleep(20);
	cout << "Operational" << endl;
	frame_init(0x00, 0x2, 0x01, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	sleep(2);
	cout << "ready to switch on" << endl;
	frame_init(0x201, 0x8, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	sleep(2);
	cout << "switch on" << endl;
	frame_init(0x201, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); 	//Sync
	sleep(2);
	cout << "homen: " << endl;
	frame_init(0x201, 0x8, 0x3F, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);	//Homen Command an RXPD0 1
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); 	//Sync
	sleep(25);
	cout << "gehomed" << endl;
	frame_init(0x201, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);	//Sync
}

int pixel_to_driverin(int Pixel) {
	if (Pixel <= 160) {
		return 10 * 5;
	} else if (Pixel >= 252) {
		return 10 * 160;
	} else {
		return 10 * (((Pixel - 160) * 1.75) + 5);	//1 Pixel entspricht 1,807 Millimeter 5mm Offset bei 169 haben wir 5mm
	}
}

void sent_position_to_driver(int driverin) {
	//An den Nibble denken!
	nibble = !nibble;
	int UpperPos = (driverin >> 8);		//Die unteren 8 Bit rausschieben
	//printf("Upper Pos :%i\n", UpperPos);
	int LowerPos = (driverin & 255);	//Die Oberen 8 Bit verschwinden lassen
	//printf("Lower Pos : %i\n", LowerPos);
	//Sende an RXPD0 1 = 0x201( Addresse/ ID), 0x8 = Datenbits, 0x3F 0x00 Controlword, 0x09 nibble Wort das den Befehl überträgt,
	//LowerPos die unteren 8 Bit der Zielposition, UpperPos die oberen 8 Bit der Zielposition , 0xBB 0x08 Max Geschwindigkeit
	frame_init(0x201, 0x8, 0x3F, 0x00, nibble, 0x09, LowerPos, UpperPos, 0xBB, 0x08);
	//Sende an RXPDO 2 den Rest des Befehls
	//0x301 die Adresse von RXPDO 2 ,0x8 = Anzahl Datenbits
	//0x2c 0x01 Beschleunigung, 0x2c 0x01 Abbremsen
	frame_init(0x301, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	//Jetzt noch die Sync Message damit der Befehl ausgeführt wird.
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);	//Sync
	return;
}

void sent_position_to_driver2(int driverin) {
	//An den Nibble denken!
	nibble = !nibble;
	int UpperPos = (driverin >> 8);		//Die unteren 8 Bit rausschieben
	//printf("Upper Pos :%i\n", UpperPos);
	int LowerPos = (driverin & 255);	//Die Oberen 8 Bit verschwinden lassen
	//printf("Lower Pos : %i\n", LowerPos);
	//Sende an RXPD0 1 = 0x201( Addresse/ ID), 0x8 = Datenbits, 0x3F 0x00 Controlword, 0x09 nibble Wort das den Befehl überträgt,/ Ball Tracking testen
	//LowerPos die unteren 8 Bit der Zielposition, UpperPos die oberen 8 Bit der Zielposition , 0xBB 0x08 Max Geschwindigkeit
	frame_init(0x201, 0x8, 0x3F, 0x00, nibble, 0x09, LowerPos, UpperPos, 0xFF, 0x00);
	//Sende an RXPDO 2 den Rest des Befehls
	//0x301 die Adresse von RXPDO 2 ,0x8 = Anzahl Datenbits
	//0x2c 0x01 Beschleunigung, 0x2c 0x01 Abbremsen
	frame_init(0x301, 0x8, 0xAC, 0x00, 0xAC, 0x00, 0x00, 0x00, 0x00, 0x00);
	//Jetzt noch die Sync Message damit der Befehl ausgeführt wird.
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);	//Sync
	return;
}

//Menupunkt 3) Motor per Hand steuern
void motor_by_hand() {
	int i, position, pos1, pos2;
	cout << "Ziel Position eingeben und mit enter bestaetigen" << endl;

	cin >> position;
	position *= 10;

	pos1 = (position& 255);
	pos2 = (position >> 8);

	nibble = !(nibble);
	cout << "nibble: " <<  nibble << endl;
	//FRAME_INIT Can_ID, DLC , Data, Data, Data, Data, Data, Data, Data, Data,
	//Nibble muss sich jedes neue COmmand ändern, deswegen nibble =! Nibble
	//Position wird mit zwei HexDaten Übertragen deswegen Pos1 pos2. pos 1 sind die unteren 8 Bit
	//50 mm entspricht dann 500 im Datenwort als Hex-Zahl
	//Die letzten beiden Datenworte im 0x201 Frame sind für die maximale Geschwindigkeit
	frame_init(0x201, 0x8, 0x3F, 0x00, nibble, 0x09, pos1, pos2, 0xBB, 0x08); // RXPDO 1
	// Dieser Frame gehört noch zum Got To Pos Command und wird an RXPDO 2 geschickt deswegen 0x301
	// Die Daten Wörter 0 und 1 sind hier für die Beschleunigung 100 in Dec entspricht einer Beschleunigung von 10m/s²
	//Die nächsten beiden Daten Wörter sind für das Bremsen der Maßstab ist genau wie beim Beschleunigen
	frame_init(0x301, 0x8, 0x2C, 0x01, 0x2C, 0x01, 0x00, 0x00, 0x00, 0x00);
	frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync
}

//Menupunkt 4) Balltracking setzen
void traction() {
	fstream Daten("Daten.txt", ios::out);
	//Eigenschaften für Bildanalyse
	Mat imgThresholded;
	//namedWindow("circles", 1);

	TorwartMax.x = TorwartSoll.x;	//Maximale und Minimale Werte für Torwart-Bewegung
	TorwartSoll.x = 35;
	TorwartSoll.y = 0;
	TorwartMax.y = 270;
	TorwartMin.x = TorwartSoll.x;
	TorwartMin.y = 158;
	TorwartMitte.x = TorwartSoll.x;
	TorwartMitte.y = TorwartMin.y + (TorwartMax.y - TorwartMin.y) / 2;

	try {
		CInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());
		cout << "Using device " << camera.GetDeviceInfo().GetModelName()
		<< endl;
		camera.Open();

		GenApi::CIntegerPtr width(camera.GetNodeMap().GetNode("Width"));
		GenApi::CIntegerPtr height(camera.GetNodeMap().GetNode("Height"));
		Mat cv_img(width->GetValue(), height->GetValue(), CV_8UC3);

		camera.StartGrabbing();
		CPylonImage image;
		CImageFormatConverter fc;
		fc.OutputPixelFormat = PixelType_RGB8packed;
		vector<Vec3f> circles;

		while (1) {
			while (camera.IsGrabbing()) {

				camera.RetrieveResult(5000, ptrGrabResult, TimeoutHandling_ThrowException);
				if (ptrGrabResult->GrabSucceeded()) {
					fc.Convert(image, ptrGrabResult);

					cv_img = cv::Mat(ptrGrabResult->GetHeight(),
						ptrGrabResult->GetWidth(), CV_8UC3,
						(uint8_t*) image.GetBuffer());
					Point Ballcenter(0, 0);
					Mat imgHSV;
					//cvtColor(cv_img, imgHSV, COLOR_BGR2HSV); //Convert the captured frame from BGR to HSV

					inRange(cv_img, Scalar(BlueLow, GreenLow,RedLow), Scalar(BlueHigh, GreenHigh, RedHigh),imgThresholded); //Threshold the image
					//morphological opening (remove small objects from the foreground)
					erode(imgThresholded, imgThresholded,getStructuringElement(MORPH_ELLIPSE, Size(15, 15)));
					dilate(imgThresholded, imgThresholded,getStructuringElement(MORPH_ELLIPSE, Size(15, 15)));

					//morphological closing (fill small holes in the foreground)
					// dilate(imgThresholded, imgThresholded,getStructuringElement(MORPH_ELLIPSE, Size(10, 10)));
					// erode(imgThresholded, imgThresholded,getStructuringElement(MORPH_ELLIPSE, Size(10, 10)));

					vector<Point> nonzero;
					//Mat nonzero;

					//cout << "nonzero:" << nonzero << endl;
					if (countNonZero(imgThresholded) > 0) {
						findNonZero(imgThresholded, nonzero);
						Ballcenter = (nonzero.front() + nonzero.back());
						Ballcenter.x = Ballcenter.x /2;
						Ballcenter.y = Ballcenter.y /2;
						if(abs(Ballcenter.y-lasty) < 2){Ballcenter.y = lasty;}
						if(abs(Ballcenter.x-lastx) < 2){Ballcenter.x = lastx;}
						cout << Ballcenter << endl;
						// draw the circle center
						circle(cv_img, Ballcenter, 3, Scalar(0, 255, 0), -1, 8, 0);
						// draw the circle outline
						circle(cv_img, Ballcenter, 10, Scalar(0, 0, 255), 3, 8, 0);
						lasty = Ballcenter.y;
						lastx = Ballcenter.x;
					}

					//imshow("dif",dif);
					imshow("circles", cv_img);

					waitKey(1);
				}
			}
		}
	} catch (GenICam::GenericException &e) {
		//Error handling.
		cerr << "An exception occurred." << endl << e.GetDescription() << endl;
		exitCode = 1;
	}

	Daten.close();
	return;
}

//Menupunkt 2) Spiel starten
void traction_and_motor() {
	int lvl;
	int dummy = 0;
	cout<<("Schwirigkeitsgrad:\n1:Normal\n2:Kinder")<<endl;
	cin>>lvl;
	fstream Daten("Daten.txt", ios::out); //Leere Textdatei

	//Eigenschaften für Bildanalyse
	Mat imgThresholded;
	Mat imgHSV;

	//namedWindow("circles", 1);

	// Variablen Global initialisiert
	Point Ballcenter(500,2);
	TorwartMax.x = TorwartSoll.x; //maximale/minimale Werte für Torwart-Bewegung
	TorwartSoll.x = 35;
	TorwartSoll.y = 215;
	TorwartMax.y = 253;
	TorwartMin.x = 35;
	TorwartMin.y = 158;
	TorwartMitte.x = TorwartSoll.x;
	TorwartMitte.y = TorwartMin.y + (TorwartMax.y - TorwartMin.y) / 2;

	int count = 0;

	try {
		CInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());
		cout << "Using device " << camera.GetDeviceInfo().GetModelName()
		<< endl;
		camera.Open();

		GenApi::CIntegerPtr width(camera.GetNodeMap().GetNode("Width"));
		GenApi::CIntegerPtr height(camera.GetNodeMap().GetNode("Height"));
		Mat cv_img(width->GetValue(), height->GetValue(), CV_8UC3);

		camera.StartGrabbing();
		CPylonImage image;
		CImageFormatConverter fc;
		fc.OutputPixelFormat = PixelType_RGB8packed;
		vector<Vec3f> circles;

		while (1) {
			while (camera.IsGrabbing()) {
				auto t0 = std::chrono::high_resolution_clock::now();
				camera.RetrieveResult(5000, ptrGrabResult, TimeoutHandling_ThrowException);
				auto t1 = std::chrono::high_resolution_clock::now();

				if (ptrGrabResult->GrabSucceeded()) {
					fc.Convert(image, ptrGrabResult);
					cv_img = cv::Mat(ptrGrabResult->GetHeight(),ptrGrabResult->GetWidth(), CV_8UC3,(uint8_t*) image.GetBuffer());
					auto t2 = std::chrono::high_resolution_clock::now();

					inRange(cv_img, Scalar(BlueLow, GreenLow,RedLow), Scalar(BlueHigh, GreenHigh, RedHigh),imgThresholded); //Threshold the image First Scalar Lower BGR Value Second Scalar Higher BGR Value							//morphological opening (remove small objects from the foreground)
					erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );
					dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );

					//morphological closing (fill small holes in the foreground)
					//dilate( imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );
					//erode(imgThresholded, imgThresholded, getStructuringElement(MORPH_ELLIPSE, Size(10, 10)) );

					auto t3 = std::chrono::high_resolution_clock::now();
					chrono::time_point<chrono::high_resolution_clock> t4;
					vector <Point> nonzero;
					//cout << "nonzero:" << nonzero << endl;

					if(countNonZero(imgThresholded) > 0) {
						findNonZero(imgThresholded, nonzero);
						t4 = std::chrono::high_resolution_clock::now();

						Ballcenter = (nonzero.front() + nonzero.back());
						Ballcenter.x = Ballcenter.x /2;
						Ballcenter.y = Ballcenter.y /2;

						if(abs(Ballcenter.y-lasty) < 2){ Ballcenter.y = lasty; } // Kleine Hysterese für die Ballerkennung
						if(abs(Ballcenter.x-lastx) < 2){ Ballcenter.x = lastx; }

						if(Ballcenter.x == lastx || Ballcenter.y == lasty) {
							TorwartSoll.y = Ballcenter.y; // Wenn der Ball Steht
						}
						//else if(Ballcenter.x > lastx);//TorwartSoll.y = lasty; // Wenn der Ball zurückrollt
			 			else {
			 				TorwartSoll.y= (lasty-Ballcenter.y)/(lastx-Ballcenter.x)*TorwartSoll.x+(lastx*Ballcenter.y-Ballcenter.x*lasty)/(lastx-Ballcenter.x); //Geradengleichung

			 				if(TorwartSoll.y < TorwartMin.y || TorwartSoll.y > TorwartMax.y) {
			 					TorwartSoll.y = lasty;
			 				}
			 			}

			 			if(abs(TorwartSoll.y-lasty) < 2) {
			 				TorwartSoll.y = lasty; // Kleine Hysterese, dass der Motor nicht bei jedem neuen angesteuerten Pixel verfährt
			 			}

						dummy = 0;
					}
					else{
						dummy++;
						
						if(dummy == 80){
							TorwartSoll.y = TorwartMitte.y;
							dummy = 0;
						}
					}

					//Daten << Ballcenter.x << ";" << Ballcenter.y << endl;
					//y = (y2-y1)/(x2-x1)*25+(x2*y1-x1*y2)/(x2-x1)
					//int driverin = pixel_to_driverin(TorwartSoll.y);
			 		if(lvl==1) {
						sent_position_to_driver(pixel_to_driverin(TorwartSoll.y)); // Driver ansteuern! Motor verfahren. Pixel to driverin rechnet um von Pixel auf Hex für den Driver
					}
					else{
						sent_position_to_driver2(pixel_to_driverin(TorwartSoll.y));
					}

					lastx = Ballcenter.x;
					lasty = Ballcenter.y;

					auto t5 = std::chrono::high_resolution_clock::now();

					//draw the circle center ------------------------- Zum debuggen und Traction Beobachten
					circle(cv_img, Ballcenter, 3, Scalar(0, 255, 0), -1, 8, 0);
					//draw the circle outline
					circle(cv_img, Ballcenter, 10, Scalar(0, 0, 255), 3, 8,0);

					circle(cv_img, TorwartSoll, 10, Scalar(255,0,0), 3, 8, 0);
					line(cv_img, Ballcenter, TorwartSoll, Scalar(100, 100, 100), 2, 1, 0);
					//break;

					/*
						cout << "camera grab: " << chrono::duration_cast<chrono::microseconds>(t1-t0).count()
				    	<< "\nimage convert: " << chrono::duration_cast<chrono::microseconds>(t2-t1).count()
					    << "\nimage threshold: " << chrono::duration_cast<chrono::microseconds>(t3-t2).count()
					    << "\npixel detect: " << chrono::duration_cast<chrono::microseconds>(t4-t3).count()
					    << "\nmotor position: " << chrono::duration_cast<chrono::microseconds>(t5-t4).count()
					 	<< "\ntotal: " << chrono::duration_cast<chrono::microseconds>(t5-t0).count() << endl << endl;
		 	  		*/
				}

				imshow("circles", cv_img);
				waitKey(1);
				count++;
				//if(count > 10)
					//break;
			}
			//if(count > 10)
				//break;
		}
	}
	//Error handling
	catch (GenICam::GenericException &e) {
		cerr << "An exception occurred." << endl << e.GetDescription() << endl;
		exitCode = 1;
	}

	Daten.close();
	return;
}

//Kameraeinstellungen auslesen
void get_camerasettings() {
	CInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());
	cout << "Using device " << camera.GetDeviceInfo().GetModelName() << endl;
	camera.Open();

	GenApi::CIntegerPtr width(camera.GetNodeMap().GetNode("Width"));
	GenApi::CIntegerPtr height(camera.GetNodeMap().GetNode("Height"));
	GenApi::CIntegerPtr packetsize(camera.GetNodeMap().GetNode("GevSCPSPacketSize"));
	GenApi::CFloatPtr exposuretime(camera.GetNodeMap().GetNode("ExposureTimeAbs"));

	cout << endl << "Aktuelle Kameraparameter:" << endl;
	camera.GetNodeMap().GetNode("Height");
	cout << "Höhe: " << width->GetValue() << endl;
	cout << "Weite: " << height->GetValue() << endl;
	cout << "Packetsize: " << packetsize->GetValue() << endl;
	cout << "Belichtungszeit: " << exposuretime->GetValue() << endl << endl;

	return;
}

//Kameraeinstellungen vornehmen
void set_camerasettings() {
	char c;			//Eingabewert für I/O
	int i = 0;		//Eingabewert für Höhe, Weite und Paketgröße
	double j = 0;	//Eingabewert für Belichtungszeit

	CInstantCamera camera(CTlFactory::GetInstance().CreateFirstDevice());
	cout << "Using device " << camera.GetDeviceInfo().GetModelName() << endl;
	camera.Open();

	GenApi::CIntegerPtr width(camera.GetNodeMap().GetNode("Width"));
	GenApi::CIntegerPtr height(camera.GetNodeMap().GetNode("Height"));
	GenApi::CIntegerPtr packetsize(camera.GetNodeMap().GetNode("GevSCPSPacketSize"));
	GenApi::CFloatPtr exposuretime(camera.GetNodeMap().GetNode("ExposureTimeAbs"));

	cout << "Wollen Sie die Höhe verändern? y/n" << endl;
	cin >> c;
	if(c == 'y'){
		cout << "Geben Sie den Wert für die Höhe ein" << endl;
		cin >> i;
		height->SetValue(i);
	}
	y = 'q';		//Was ist y, und warum wird ihm ein 'q' zugewiesen?

	cout << "Wollen Sie die Weite verändern? y/n" << endl;
	cin >> c;
	if(c == 'y'){
		cout << "Die Werte können nur in 16er Schritten veraendert werden!" << endl;
		cout << "Zum Beispiel 608 , 624 , 640 usw." << endl;
		cout << "Geben Sie den Wert für die Weite ein" << endl;
		cin >> i;
		width->SetValue(i);
	}
	y = 'q';		//Was ist y, und warum wird ihm ein 'q' zugewiesen?

	cout << "Wollen Sie die Packetsize verändern? y/n" << endl;
	cin >> c;
	if(c == 'y'){
		cout << "Die Werte können nur in 4er Schritten veraendert werden!" << endl;
		cout << "Zum Beispiel 996 , 1000 , 1004 usw." << endl;
		cout << "Geben Sie den Wert für die Packetsize ein" << endl;
		cin >> i;
		packetsize->SetValue(i);
	}
	y = 'q';		//Was ist y, und warum wird ihm ein 'q' zugewiesen?

	cout << "Wollen Sie die Belichtungszeit verändern? y/n" << endl;
	cin >> c;
	if(c == 'y'){
		cout << "Geben Sie den Wert für die Belichtungszeit ein" << endl;
		cin >> j;
		exposuretime->SetValue(j);
	}
	y = 'q';		//Was ist y, und warum wird ihm ein 'q' zugewiesen?

	return;
}

//Menupunkt 7) Motor sperren oder entsperren. Zweck?
void motor_switchon(){
	int i = 0;

	cout << "Was möchten Sie machen?" << endl;
	cout << "1) Sperren" << endl;
	cout << "2) Entsperren" << endl;

	cin >> i;
	switch (i) {
		case 1:
			frame_init(0x201, 0x8, 0x3E, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
			frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
		break;
		case 2:
			frame_init(0x201, 0x8, 0x3F, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00);
			frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync
		break;
		default:
			cout << "Falsche Eingabe erneut versuchen!" << endl;
		break;
	}

	return;
}

//Menupunkt 5) Kameraoperationen
void camera_settings() {
	int i = 0;

	cout << "Kameraeinstellungen" << endl;
	cout << "Was moechten Sie tun:" << endl;
	cout << "1) Kameraparameter abfragen" << endl;
	cout << "2) Kameraparameter einstellen" << endl;

	cin >> i;
	switch (i) {
		case 1:
			get_camerasettings();
		break;
		case 2:
			set_camerasettings();
		break;
		default:
			cout << "Falsche Eingabe erneut versuchen!" << endl;
		break;
	}

	return;
}

//Hauptmenü zur Programmsteuerung
void Menue() {
	int i = 0;

	while (1) {
		cout << "Herzlich Willkommen!" << endl;
		cout << "Was moechten Sie machen:" << endl;
		cout << "1) Motor Initialisieren" << endl;
		cout << "2) Spielen" << endl;
		cout << "3) Motor per Hand ansteuern" << endl;
		cout << "4) Ball Tracking testen" << endl;
		cout << "5) Kamera einstellen" << endl;
		cout << "6) Motor Homen" << endl;
		cout << "7) Motor sperren/entsperren" << endl;
		cout << "8) Beenden" << endl;

		cin >> i;
		switch (i) {
			case 1:
				driver_init();
			break;
			case 2:
				traction_and_motor();
			break;
			case 3:
				motor_by_hand();
			break;
			case 4:
				traction();
			break;
			case 5:
				camera_settings();
			break;
			case 6:
				cout << "Homen" << endl;
				frame_init(0x201, 0x8, 0x3F, 0x08, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Homen Command an RXPD0 1
				frame_init(0x80, 0x0, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00); // Sync
				sleep(25);
				cout << "Gehomed" << endl;
			break;
			case 7:
				motor_switchon();
			break;
			case 8:
				cout << "Programm beendet" << endl << endl;
			return;
			default:
				cout << "Falsche Eingabe erneut versuchen!" << endl;
			break;
		}
	}
}

int main(int argc, char** argv) {
	Menue();
}

