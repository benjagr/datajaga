#include "stdafx.h"
#include <tchar.h>
#include <iostream>
#include <SharedFileOut.h>
#include <DtPackets.h>
#include <iostream>
#include <iomanip>
#include <boost/asio.hpp>
#include <boost/date_time.hpp>
#include <boost/bind/bind.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

namespace bpt = boost::posix_time;
namespace asio = boost::asio;


using namespace std;

struct SMElement
{
	HANDLE hMapFile;
	unsigned char* mapFileBuffer;
};

SMElement m_graphics;
SMElement m_physics;
SMElement m_static;

void f()
{
	std::cout << "Called at " << bpt::microsec_clock::local_time().time_of_day() << '\n';
}

void caller(const boost::system::error_code&, asio::deadline_timer& t, int& count)
{
	f();
	t.expires_at(t.expires_at() + bpt::seconds(1));
	if (++count < 5)
		t.async_wait(boost::bind(caller, asio::placeholders::error, boost::ref(t), boost::ref(count)));
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
	int count = 0;
	t.async_wait(boost::bind(caller, asio::placeholders::error, boost::ref(t), boost::ref(count)));
	io.run();

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


