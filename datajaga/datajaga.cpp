#include <stdafx.h>
#include <tchar.h>
#include <iostream>
#include <SharedFileOut.h>
#include <DtPackets.h>
#include <fstream>
#include <iomanip>
#include <boost/thread.hpp>
#include <boost/asio.hpp>
#include <boost/filesystem.hpp>
#include <boost/range/iterator_range.hpp>
#include <boost/date_time.hpp>
#include <boost/bind/bind.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include<winsock2.h>
#include<cstring>

#pragma comment(lib,"ws2_32.lib") //Winsock Library

namespace bpt = boost::posix_time;
namespace asio = boost::asio;

using namespace std;
using namespace boost::filesystem;


struct SMElement
{
	HANDLE hMapFile;
	unsigned char* mapFileBuffer;
};

bool glb_debug = FALSE;

string glb_ending = ".djbin";

std::ofstream outfile;

SMElement m_graphics;
SMElement m_physics;
SMElement m_static;

SPageFilePhysics* pf;
SPageFileGraphic* gf;
SPageFileStatic* sf;



/*
void writelumptooutfile()
{
	outfile << DtLump(pf->packetId, gf->status, gf->session, pf->gas, pf->brake, pf->fuel, pf->gear, pf->rpms, pf->steerAngle, pf->speedKmh, pf->accG, pf->wheelSlip, pf->wheelLoad, pf->wheelsPressure, pf->tyreCoreTemperature, pf->tyreWear, pf->tyreDirtyLevel, pf->drs, pf->carDamage, pf->numberOfTyresOut, gf->completedLaps, gf->position, gf->iCurrentTime, gf->iLastTime, gf->iBestTime, gf->currentSectorIndex, gf->isInPit, gf->normalizedCarPosition, gf->carCoordinates).todatapacket() << endl;
}
*/

void writelumptooutfile()
{
	DtLump wrlump = DtLump(pf->packetId, gf->status, gf->session, pf->gas, pf->brake, pf->fuel, pf->gear, pf->rpms, pf->steerAngle, pf->speedKmh, pf->accG, pf->wheelSlip, pf->wheelLoad, pf->wheelsPressure, pf->tyreCoreTemperature, pf->tyreWear, pf->tyreDirtyLevel, pf->drs, pf->carDamage, pf->numberOfTyresOut, gf->completedLaps, gf->position, gf->iCurrentTime, gf->iLastTime, gf->iBestTime, gf->currentSectorIndex, gf->isInPit, gf->normalizedCarPosition, gf->carCoordinates);
	if (outfile.bad()) {
		cout << "Error in File Writing" << endl;
	}
	if(glb_debug){
		cout << wrlump.todatapacket() << endl;
	}
	outfile << wrlump.todatapacket() << endl;
}

void writecurrentlaptodisk(const boost::system::error_code&, asio::deadline_timer& t, int& previous)
{
	t.expires_at(t.expires_at() + bpt::millisec(50));
	if (previous == gf->completedLaps)
		t.async_wait(boost::bind(writecurrentlaptodisk, asio::placeholders::error, boost::ref(t), boost::ref(previous)));
	boost::thread bt{ writelumptooutfile };
}

void writecurrentsessiontodisk(const boost::system::error_code&, asio::deadline_timer& t, int& previous)
{
	t.expires_at(t.expires_at() + bpt::millisec(50));
	if (previous == gf->session) {
		if (!(GetAsyncKeyState(0x32) && GetAsyncKeyState(VK_LSHIFT))) {
			t.async_wait(boost::bind(writecurrentsessiontodisk, asio::placeholders::error, boost::ref(t), boost::ref(previous)));
		}
		else {
			cout << "Recording aborted by User" << endl;
		}
	}
	else {
		cout << "Session Over" << endl;
	}
	boost::thread bt{ writelumptooutfile };
}


void initPhysics()
{
	TCHAR szName[] = TEXT("Local\\acpmf_physics");
	m_physics.hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(SPageFilePhysics), szName);
	if (!m_physics.hMapFile)
	{
		MessageBoxA(GetActiveWindow(), "CreateFileMapping failed", "ACS", MB_OK);
	}
	m_physics.mapFileBuffer = (unsigned char*)MapViewOfFile(m_physics.hMapFile, FILE_MAP_READ, 0, 0, sizeof(SPageFilePhysics));
	if (!m_physics.mapFileBuffer)
	{
		MessageBoxA(GetActiveWindow(), "MapViewOfFile failed", "ACS", MB_OK);
	}
}

void initGraphics()
{
	TCHAR szName[] = TEXT("Local\\acpmf_graphics");
	m_graphics.hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(SPageFileGraphic), szName);
	if (!m_graphics.hMapFile)
	{
		MessageBoxA(GetActiveWindow(), "CreateFileMapping failed", "ACS", MB_OK);
	}
	m_graphics.mapFileBuffer = (unsigned char*)MapViewOfFile(m_graphics.hMapFile, FILE_MAP_READ, 0, 0, sizeof(SPageFileGraphic));
	if (!m_graphics.mapFileBuffer)
	{
		MessageBoxA(GetActiveWindow(), "MapViewOfFile failed", "ACS", MB_OK);
	}
}

void initStatic()
{
	TCHAR szName[] = TEXT("Local\\acpmf_static");
	m_static.hMapFile = CreateFileMapping(INVALID_HANDLE_VALUE, NULL, PAGE_READWRITE, 0, sizeof(SPageFileStatic), szName);
	if (!m_static.hMapFile)
	{
		MessageBoxA(GetActiveWindow(), "CreateFileMapping failed", "ACS", MB_OK);
	}
	m_static.mapFileBuffer = (unsigned char*)MapViewOfFile(m_static.hMapFile, FILE_MAP_READ, 0, 0, sizeof(SPageFileStatic));
	if (!m_static.mapFileBuffer)
	{
		MessageBoxA(GetActiveWindow(), "MapViewOfFile failed", "ACS", MB_OK);
	}
}

void preparedata() {
	path p = boost::filesystem::current_path();
	string sp;
	for (auto& entry : boost::make_iterator_range(directory_iterator(p), {})) {
		sp = entry.path().string();
		if (sp.length() >= glb_ending.length()) {
			if (0 == sp.compare(sp.length() - glb_ending.length(), glb_ending.length(), glb_ending)) { //if file ends with ending of datajaga file


			}
		}
	}
}

void dismiss(SMElement element)
{
	UnmapViewOfFile(element.mapFileBuffer);
	CloseHandle(element.hMapFile);
}


int _tmain(int argc, _TCHAR* argv[])
{
	initPhysics();
	initGraphics();
	initStatic();

	asio::io_service io;
	asio::deadline_timer t(io, bpt::seconds(1));

	cout << "Press 1 to write Data of your next Lap to Disk\nPress 2 to write Data of your current Session to Disk\nPress 3 to send Data of your next Lap to DataJaeger\n";

	pf = (SPageFilePhysics*)m_physics.mapFileBuffer;
	gf = (SPageFileGraphic*)m_graphics.mapFileBuffer;
	sf = (SPageFileStatic*)m_static.mapFileBuffer;

	while (true)
	{
		if (GetAsyncKeyState(0x31)) // user pressed 1 Write next Lap to Disk
		{
			cout << "Preparing to write Data of the next Lap to Disk" << endl;
			int previous = gf->completedLaps;
			string ptext = "";
			cout << "Waiting for end of Lap Number: ";
			cout << (previous + 1) << endl;
			while (previous == gf->completedLaps && glb_debug) {
				ptext = to_string(gf->completedLaps);
				cout << ptext;
				for (int i = 0; i < ptext.length(); i++) {
					cout << '\b';
				}
			}
			previous = gf->completedLaps;
			cout << "Writing current Lap: ";
			cout << (previous + 1) << endl;
			outfile.open("out" + glb_ending, ios::out);
			cout << "Initialized Multithreaded extraction Process" << endl;
			t.async_wait(boost::bind(writecurrentlaptodisk, asio::placeholders::error, boost::ref(t), boost::ref(previous)));
			cout << "Running Multithreaded extraction Process" << endl;
			outfile << StLump(sf->carModel, sf->track, sf->playerName, sf->playerNick, sf->playerSurname).todatapacket() << endl;
			io.run();
			outfile.close();
			cout << "Finished current Lap: ";
			cout << previous << endl;
		}
		else if (GetAsyncKeyState(0x32) && !GetAsyncKeyState(VK_LSHIFT)) // user pressed 2 Write Session to Disk
		{
			cout << "Preparing to write Data of the next Lap to Disk" << endl;
			int previous = gf->session;
			cout << "Writing current Session: ";
			cout << previous << endl;
			outfile.open("out" + glb_ending, ios::out);
			cout << "Initialized Multithreaded extraction Process" << endl;
			t.async_wait(boost::bind(writecurrentsessiontodisk, asio::placeholders::error, boost::ref(t), boost::ref(previous)));
			cout << "Running Multithreaded extraction Process" << endl;
			cout << "Recording until end of Session; Press Shift + 2 to abort" << endl;
			outfile << StLump(sf->carModel, sf->track, sf->playerName, sf->playerNick, sf->playerSurname).todatapacket() << endl;
			io.run();
			outfile.close();
			cout << "Finished writing to file" << endl;
		}
		else if (GetAsyncKeyState(0x33)) // user pressed 3 Send Data to Jaeger
		{
			cout << "Currently not implemented" << endl;
		}
		else if (GetAsyncKeyState(0x34) && !GetAsyncKeyState(VK_LSHIFT)) // user pressed 2 Write Session to Disk
		{
			cout << "Preparing to manage bin files." << endl;
			preparedata();
			
		}
		else if (GetAsyncKeyState(0x30)) // user pressed 0 Set User Debug
		{
			if (glb_debug && GetAsyncKeyState(VK_LSHIFT) != 0) {
				cout << "User Debug Deactivated" << endl;
				glb_debug = false;
			}
			else if (!glb_debug) {
				cout << "User Debug Activated" << endl;
				glb_debug = true;
			}
		}
	}

	/*
	WSADATA wsa;
	SOCKET s;
	struct sockaddr_in server;
	
	printf("\nInitialising Winsock...");
	if (WSAStartup(MAKEWORD(2, 2), &wsa) != 0)
	{
		printf("Failed. Error Code : %d", WSAGetLastError());
		return 1;
	}

	printf("Initialised.\n");

	//Create a socket
	if ((s = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET)
	{
		printf("Could not create socket : %d", WSAGetLastError());
	}

	printf("Socket created.\n");


	InetPton(AF_INET, _T("127.0.0.1"), &server.sin_addr.s_addr);
	server.sin_family = AF_INET;
	server.sin_port = htons(80);

	//Connect to remote server
	if (connect(s, (struct sockaddr*)&server, sizeof(server)) < 0)
	{
		puts("connect error");
		return 1;
	}

	puts("Connected");

	SPageFilePhysics* pf = (SPageFilePhysics*)m_physics.mapFileBuffer;
	SPageFileGraphic* gf = (SPageFileGraphic*)m_graphics.mapFileBuffer;
	DtLump datalump = DtLump(pf->packetId, gf->status, gf->session, pf->gas, pf->brake, pf->fuel, pf->gear, pf->rpms, pf->steerAngle, pf->speedKmh, pf->accG, pf->wheelSlip, pf->wheelLoad, pf->wheelsPressure, pf->tyreCoreTemperature, pf->tyreWear, pf->tyreDirtyLevel, pf->drs, pf->carDamage, pf->numberOfTyresOut, gf->completedLaps, gf->position, gf->iCurrentTime, gf->iLastTime, gf->iBestTime, gf->currentSectorIndex, gf->isInPit, gf->normalizedCarPosition, gf->carCoordinates);


	//Send some data
	if (send(s, datalump.todatapacket(), strlen(datalump.todatapacket()), 0) < 0)
	{
		puts("Send failed");
		return 1;
	}
	puts("Data Send\n");

	/*while (false)
	{
		if (GetAsyncKeyState(0x31) != 0) // user pressed 1
		{
			wcout << "---------------PHYSICS INFO---------------" << endl;
			SPageFilePhysics* pf = (SPageFilePhysics*)m_physics.mapFileBuffer;
			printData("acc G", pf->accG);
			printData("brake", pf->brake);
			printData("camber rad", pf->camberRAD);
			printData("damage", pf->carDamage);
			printData("car height", pf->cgHeight);
			printData("drs", pf->drs);
			printData("tc", pf->tc);
			printData("fuel", pf->fuel);
			printData("gas", pf->gas);
			printData("gear", pf->gear);
			printData("number of tyres out", pf->numberOfTyresOut);
			printData("packet id", pf->packetId);
			printData("heading", pf->heading);
			printData("pitch", pf->pitch);
			printData("roll", pf->roll);
			printData("rpms", pf->rpms);
			printData("speed kmh", pf->speedKmh);
			printData("steer ", pf->steerAngle);
			printData("suspension travel", pf->suspensionTravel);
			printData("tyre core temp", pf->tyreCoreTemperature);
			printData("tyre dirty level", pf->tyreDirtyLevel);
			printData("tyre wear", pf->tyreWear);
			printData("velocity", pf->velocity);
			printData("wheel angular speed", pf->wheelAngularSpeed);
			printData("wheel load", pf->wheelLoad);
			printData("wheel slip", pf->wheelSlip);
			printData("wheel pressure", pf->wheelsPressure);
		}

		if (GetAsyncKeyState(0x32) != 0) // user pressed 2
		{
			wcout << "---------------GRAPHICS INFO---------------" << endl;
			SPageFileGraphic* pf = (SPageFileGraphic*)m_graphics.mapFileBuffer;
			printData("packetID ", pf->packetId);
			printData("STATUS ", pf->status);
			printData("session", pf->session);
			printData("completed laps", pf->completedLaps);
			printData("position", pf->position);
			printData("current time s", pf->currentTime);
			printData("current time", pf->iCurrentTime);
			printData("last time", pf->iLastTime);
			printData("best time", pf->iBestTime);
			printData("sessionTimeLeft", pf->sessionTimeLeft);
			printData("distanceTraveled", pf->distanceTraveled);
			printData("isInPit", pf->isInPit);
			printData("currentSectorIndex", pf->currentSectorIndex);
			printData("lastSectorTime", pf->lastSectorTime);
			printData("numberOfLaps", pf->numberOfLaps);
			wcout << "TYRE COMPOUND : " << pf->tyreCompound << endl;
			printData("replayMult", pf->replayTimeMultiplier);
			printData("normalizedCarPosition", pf->normalizedCarPosition);
			printData("carCoordinates", pf->carCoordinates);
		}


		if (GetAsyncKeyState(0x33) != 0) // user pressed 3
		{
			wcout << "---------------STATIC INFO---------------" << endl;
			SPageFileStatic* pf = (SPageFileStatic*)m_static.mapFileBuffer;
			wcout << "SM VERSION " << pf->smVersion << endl;
			wcout << "AC VERSION " << pf->acVersion << endl;

			printData("number of sessions ", pf->numberOfSessions);
			printData("numCars", pf->numCars);
			wcout << "Car model " << pf->carModel << endl;
			wcout << "Car track " << pf->track << endl;
			wcout << "Player Name " << pf->playerName << endl;
			// wcout << "Player Name " << pf->playerNick << endl;
			// wcout << "Player Name " << pf->playerSurname << endl;
			printData("sectorCount", pf->sectorCount);

			printData("maxTorque", pf->maxTorque);
			printData("maxPower", pf->maxPower);
			printData("maxRpm", pf->maxRpm);
			printData("maxFuel", pf->maxFuel);
			printData("suspensionMaxTravel", pf->suspensionMaxTravel);
			printData("tyreRadius", pf->tyreRadius);

		}
	}*/

	dismiss(m_graphics);
	dismiss(m_physics);
	dismiss(m_static);

	return 0;
}


