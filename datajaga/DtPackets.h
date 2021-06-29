#pragma once

#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <string>

using std::string;
using std::wstring;

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
		void serialize(Archive& ar, const unsigned int version)
		{
			ar& packetId;

			ar& status;
			ar& session;

			ar& gas;
			ar& brake;
			ar& fuel;
			ar& gear;
			ar& rpms;
			ar& steerAngle;
			ar& speedKmh;
			ar& accGx;
			ar& accGy;
			ar& accGz;
			ar& wheelSlipLF;
			ar& wheelSlipRF;
			ar& wheelSlipLR;
			ar& wheelSlipRR;
			ar& wheelLoadLF;
			ar& wheelLoadRF;
			ar& wheelLoadLR;
			ar& wheelLoadRR;
			ar& wheelsPressureLF;
			ar& wheelsPressureRF;
			ar& wheelsPressureLR;
			ar& wheelsPressureRR;
			ar& tyreCoreTemperatureLF;
			ar& tyreCoreTemperatureRF;
			ar& tyreCoreTemperatureLR;
			ar& tyreCoreTemperatureRR;
			ar& tyreWearLF;
			ar& tyreWearRF;
			ar& tyreWearLR;
			ar& tyreWearRR;
			ar& tyreDirtyLevelLF;
			ar& tyreDirtyLevelRF;
			ar& tyreDirtyLevelLR;
			ar& tyreDirtyLevelRR;
			ar& drs;
			ar& carDamage;
			ar& numberOfTyresOut;

			ar& completedLaps;
			ar& position;
			ar& iCurrentTime;
			ar& iLastTime;
			ar& iBestTime;
			ar& currentSectorIndex;
			ar& isInPit;

			ar& normalizedCarPosition;
			ar& carCoordinatesx;
			ar& carCoordinatesy;
			ar& carCoordinatesz;
		}

		int packetId;

		AC_STATUS status = AC_OFF;
		AC_SESSION_TYPE session = AC_PRACTICE;

		float gas = 0;
		float brake = 0;
		float fuel = 0;
		int gear = 0;
		int rpms = 0;
		float steerAngle = 0;
		float speedKmh = 0;
		float accGx;
		float accGy;
		float accGz;
		float wheelSlipLF;
		float wheelSlipRF;
		float wheelSlipLR;
		float wheelSlipRR;
		float wheelLoadLF;
		float wheelLoadRF;
		float wheelLoadLR;
		float wheelLoadRR;
		float wheelsPressureLF;
		float wheelsPressureRF;
		float wheelsPressureLR;
		float wheelsPressureRR;
		float tyreCoreTemperatureLF;
		float tyreCoreTemperatureRF;
		float tyreCoreTemperatureLR;
		float tyreCoreTemperatureRR;
		float tyreWearLF;
		float tyreWearRF;
		float tyreWearLR;
		float tyreWearRR;
		float tyreDirtyLevelLF;
		float tyreDirtyLevelRF;
		float tyreDirtyLevelLR;
		float tyreDirtyLevelRR;
		float drs = 0;
		float carDamage; //simplified sum of Array
		int numberOfTyresOut = 0;

		int completedLaps = 0;
		int position = 0;
		int iCurrentTime = 0;
		int iLastTime = 0;
		int iBestTime = 0;
		int currentSectorIndex = 0;
		int isInPit = 0;

		float normalizedCarPosition = 0;
		float carCoordinatesx;
		float carCoordinatesy;
		float carCoordinatesz;

	public:

		DtLump(int packetIdp);

		DtLump(
			int packetIdp,

			AC_STATUS statusp,
			AC_SESSION_TYPE sessionp,

			float gasp,
			float brakep,
			float fuelp,
			int gearp,
			int rpmsp,
			float steerAnglep,
			float speedKmhp,
			float accGp[3],
			float wheelSlipp[4],
			float wheelLoadp[4],
			float wheelsPressurep[4],
			float tyreCoreTemperaturep[4],
			float tyreWearp[4],
			float tyreDirtyLevelp[4],
			float drsp,
			float carDamagep[5],
			int numberOfTyresOutp,

			int completedLapsp,
			int positionp,
			int iCurrentTimep,
			int iLastTimep,
			int iBestTimep,
			int currentSectorIndexp,
			int isInPitp,

			float normalizedCarPositionp,
			float carCoordinatesp[3]);

		string makestring();

		const char* todatapacket();
};

class StLump {
private:
	friend class boost::serialization::access;
	template<class Archive>
	void serialize(Archive& ar, const unsigned int version);

	string actostring(wchar_t acstr[33]);

	string carModel;
	string track;
	string playerName;
	string playerSurname;
	string playerNick;
public:
	StLump(wchar_t carModelp[33],
		wchar_t trackp[33],
		wchar_t playerNamep[33],
		wchar_t playerSurnamep[33],
		wchar_t playerNickp[33]);
};