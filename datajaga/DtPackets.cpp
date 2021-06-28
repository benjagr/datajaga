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
		void serialize(Archive & ar, const unsigned int version)
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

		int packetId = 0;

		AC_STATUS status = AC_OFF;
		AC_SESSION_TYPE session = AC_PRACTICE;

		float gas;
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
			float carCoordinatesp[3]) {

			packetId = packetIdp;

			status = statusp;
			session = sessionp;

			gas = gasp;
			brake = brakep;
			fuel = fuelp;
			gear = gearp;
			rpms = rpmsp;
			steerAngle = steerAnglep;
			speedKmh = speedKmhp;
			accGx = accGp[0];
			accGy = accGp[1];
			accGz = accGp[2];
			wheelSlipLF = wheelSlipp[0];
			wheelSlipRF = wheelSlipp[1];
			wheelSlipLR = wheelSlipp[2];
			wheelSlipRR = wheelSlipp[3];
			wheelLoadLF = wheelLoadp[0];
			wheelLoadRF = wheelLoadp[1];
			wheelLoadLR = wheelLoadp[2];
			wheelLoadRR = wheelLoadp[3];
			wheelsPressureLF = wheelsPressurep[0];
			wheelsPressureRF = wheelsPressurep[1];
			wheelsPressureLR = wheelsPressurep[2];
			wheelsPressureRR = wheelsPressurep[3];
			tyreCoreTemperatureLF = tyreCoreTemperaturep[0];
			tyreCoreTemperatureRF = tyreCoreTemperaturep[1];
			tyreCoreTemperatureLR = tyreCoreTemperaturep[2];
			tyreCoreTemperatureRR = tyreCoreTemperaturep[3];
			tyreWearLF = tyreWearp[0];
			tyreWearRF = tyreWearp[1];
			tyreWearLR = tyreWearp[2];
			tyreWearRR = tyreWearp[3];
			tyreDirtyLevelLF = tyreDirtyLevelp[0];
			tyreDirtyLevelRF = tyreDirtyLevelp[1];
			tyreDirtyLevelLR = tyreDirtyLevelp[2];
			tyreDirtyLevelRR = tyreDirtyLevelp[3];
			drs = drsp;
			carDamage = carDamagep[0] + carDamagep[1] + carDamagep[2] + carDamagep[3] + carDamagep[4];
			numberOfTyresOut = numberOfTyresOutp;

			completedLaps = completedLapsp;
			position = positionp;
			iCurrentTime = iCurrentTimep;
			iLastTime = iLastTimep;
			iBestTime = iBestTimep;
			currentSectorIndex = currentSectorIndexp;
			isInPit = isInPitp;

			normalizedCarPosition = normalizedCarPositionp;
			carCoordinatesx = carCoordinatesp[0];
			carCoordinatesy = carCoordinatesp[1];
			carCoordinatesz = carCoordinatesp[2];
		}
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

		string actostring(wchar_t acstr[33]) {
			wstring ws(acstr);
			string str(ws.begin(), ws.end());
			return str;
		}

		string carModel;
		string track;
		string playerName;
		string playerSurname;
		string playerNick;
	public:
		StLump(	wchar_t carModelp[33],
				wchar_t trackp[33],
				wchar_t playerNamep[33],
				wchar_t playerSurnamep[33],
				wchar_t playerNickp[33]) {
			carModel = actostring(carModelp);
			track = actostring(trackp);
			playerName = actostring(playerNamep);
			playerSurname = actostring(playerSurnamep);
			playerNick = actostring(playerNickp);
		}
};