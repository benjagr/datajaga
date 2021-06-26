#pragma once

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>

typedef int AC_STATUS;

#define AC_OFF 0
#define AC_REPLAY 1
#define AC_LIVE 2
#define AC_PAUSE 3

typedef int AC_SESSION_TYPE;

#define AC_UNKNOWN -1
#define AC_PRACTICE 0
#define AC_QUALIFY 1
#define AC_RACE 2
#define AC_HOTLAP 3
#define AC_TIME_ATTACK 4
#define AC_DRIFT 5
#define AC_DRAG 6


class DtLump {
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive & ar, const unsigned int version)
		{
			ar & packetId;

			ar & status;
			ar & session;

			ar & gas;
			ar & brake;
			ar & fuel;
			ar & gear;
			ar & rpms;
			ar & steerAngle;
			ar & speedKmh;
			ar & accG;
			ar & wheelSlip;
			ar & wheelLoad;
			ar & wheelsPressure;
			ar & tyreCoreTemperature;
			ar & tyreWear;
			ar & tyreDirtyLevel;
			ar & drs;
			ar & carDamage;
			ar & numberOfTyresOut;

			ar & completedLaps;
			ar & position;
			ar & iCurrentTime;
			ar & iLastTime;
			ar & iBestTime;
			ar & currentSectorIndex;
			ar & isInPit;

			ar & normalizedCarPosition;
			ar & carCoordinates;
		}

		int packetId = 0;

		AC_STATUS status = AC_OFF;
		AC_SESSION_TYPE session = AC_PRACTICE;

		float gas = 0;
		float brake = 0;
		float fuel = 0;
		int gear = 0;
		int rpms = 0;
		float steerAngle = 0;
		float speedKmh = 0;
		float accG[3];
		float wheelSlip[4];
		float wheelLoad[4];
		float wheelsPressure[4];
		float tyreCoreTemperature[4];
		float tyreWear[4];
		float tyreDirtyLevel[4];
		float drs = 0;
		float carDamage[5];
		int numberOfTyresOut = 0;

		int completedLaps = 0;
		int position = 0;
		int iCurrentTime = 0;
		int iLastTime = 0;
		int iBestTime = 0;
		int currentSectorIndex = 0;
		int isInPit = 0;

		float normalizedCarPosition = 0;
		float carCoordinates[3];
};

class StLump {
	private:
		friend class boost::serialization::access;
		template<class Archive>
		void serialize(Archive& ar, const unsigned int version)
		{
			ar& carModel;
			ar& track;
			ar& playerName;
			ar& playerSurname;
			ar& playerNick;
		}

		wchar_t carModel[33];
		wchar_t track[33];
		wchar_t playerName[33];
		wchar_t playerSurname[33];
		wchar_t playerNick[33];
};