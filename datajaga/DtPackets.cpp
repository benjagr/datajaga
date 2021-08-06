#include "DtPackets.h"
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

int DtLump::getpacketid(){
	return packetId;
}

int DtLump::getiCurrentTime() {
	return iCurrentTime;
}

string DtLump::makeheader() {
	return "packetId;status;session;gas;clutch;brake;fuel;gear;rpms;steerAngle;speedKmh;accGx;accGy;accGz;wheelSlipLF;wheelSlipRF;wheelSlipLR;wheelSlipRR;wheelLoadLF;wheelLoadRF;wheelLoadLR;wheelLoadRR;wheelsPressureLF;wheelsPressureRF;wheelsPressureLR;wheelsPressureRR;tyreCoreTemperatureLF;tyreCoreTemperatureRF;tyreCoreTemperatureLR;tyreCoreTemperatureRR;tyreWearLF;tyreWearRF;tyreWearLR;tyreWearRR;tyreDirtyLevelLF;tyreDirtyLevelRF;tyreDirtyLevelLR;tyreDirtyLevelRR;drs;carDamage;numberOfTyresOut;completedLaps;position;iCurrentTime;iLastTime;iBestTime;currentSectorIndex;isInPit;normalizedCarPosition;carCoordinatesx;carCoordinatesy;carCoordinatesz;key";
}

string DtLump::makestring() {
	return	"packetId\t" + std::to_string(packetId) + "\n"

			"status\t" + std::to_string(status) + "\n"
			"session\t" + std::to_string(session) + "\n"


			"gas\t" + std::to_string(gas) + "\n"
			"clutch\t" + std::to_string(clutch) + "\n"
			"brake\t" + std::to_string(brake) + "\n"
			"fuel\t" + std::to_string(fuel) + "\n"
			"gear\t" + std::to_string(gear) + "\n"
			"rpms\t" + std::to_string(rpms) + "\n"
			"steerAngle\t" + std::to_string(steerAngle) + "\n"
			"speedKmh\t" + std::to_string(speedKmh) + "\n"
			"accGx\t" + std::to_string(accGx) + "\n"
			"accGy\t" + std::to_string(accGy) + "\n"
			"accGz\t" + std::to_string(accGz) + "\n"
			"wheelSlipLF\t" + std::to_string(wheelSlipLF) + "\n"
			"wheelSlipRF\t" + std::to_string(wheelSlipRF) + "\n"
			"wheelSlipLR\t" + std::to_string(wheelSlipLR) + "\n"
			"wheelSlipRR\t" + std::to_string(wheelSlipRR) + "\n"
			"wheelLoadLF\t" + std::to_string(wheelLoadLF) + "\n"
			"wheelLoadRF\t" + std::to_string(wheelLoadRF) + "\n"
			"wheelLoadLR\t" + std::to_string(wheelLoadLR) + "\n"
			"wheelLoadRR\t" + std::to_string(wheelLoadRR) + "\n"
			"wheelsPressureLF\t" + std::to_string(wheelsPressureLF) + "\n"
			"wheelsPressureRF\t" + std::to_string(wheelsPressureRF) + "\n"
			"wheelsPressureLR\t" + std::to_string(wheelsPressureLR) + "\n"
			"wheelsPressureRR\t" + std::to_string(wheelsPressureRR) + "\n"
			"tyreCoreTemperatureLF\t" + std::to_string(tyreCoreTemperatureLF) + "\n"
			"tyreCoreTemperatureRF\t" + std::to_string(tyreCoreTemperatureRF) + "\n"
			"tyreCoreTemperatureLR\t" + std::to_string(tyreCoreTemperatureLR) + "\n"
			"tyreCoreTemperatureRR\t" + std::to_string(tyreCoreTemperatureRR) + "\n"
			"tyreWearLF\t" + std::to_string(tyreWearLF) + "\n"
			"tyreWearRF\t" + std::to_string(tyreWearRF) + "\n"
			"tyreWearLR\t" + std::to_string(tyreWearLR) + "\n"
			"tyreWearRR\t" + std::to_string(tyreWearRR) + "\n"
			"tyreDirtyLevelLF\t" + std::to_string(tyreDirtyLevelLF) + "\n"
			"tyreDirtyLevelRF\t" + std::to_string(tyreDirtyLevelRF) + "\n"
			"tyreDirtyLevelLR\t" + std::to_string(tyreDirtyLevelLR) + "\n"
			"tyreDirtyLevelRR\t" + std::to_string(tyreDirtyLevelRR) + "\n"
			"drs\t" + std::to_string(drs) + "\n"
			"carDamage\t" + std::to_string(carDamage) + "\n"
			"numberOfTyresOut\t" + std::to_string(numberOfTyresOut) + "\n"

			"completedLaps\t" + std::to_string(completedLaps) + "\n"
			"position\t" + std::to_string(position) + "\n"
			"iCurrentTime\t" + std::to_string(iCurrentTime) + "\n"
			"iLastTime\t" + std::to_string(iLastTime) + "\n"
			"iBestTime\t" + std::to_string(iBestTime) + "\n"
			"currentSectorIndex\t" + std::to_string(currentSectorIndex) + "\n"
			"isInPit\t" + std::to_string(isInPit) + "\n"

			"normalizedCarPosition\t" + std::to_string(normalizedCarPosition) + "\n"
			"carCoordinatesx\t" + std::to_string(carCoordinatesx) + "\n"
			"carCoordinatesy\t" + std::to_string(carCoordinatesy) + "\n"
			"carCoordinatesz\t" + std::to_string(carCoordinatesz) + "\n";
}

string DtLump::todatapacket() {
	string sDatapacket =	std::to_string(packetId) + ";" +

							std::to_string(status) + ";" +
							std::to_string(session) + ";" +


							std::to_string(gas) + ";" +
							std::to_string(clutch) + ";" +
							std::to_string(brake) + ";" +
							std::to_string(fuel) + ";" +
							std::to_string(gear) + ";" +
							std::to_string(rpms) + ";" +
							std::to_string(steerAngle) + ";" +
							std::to_string(speedKmh) + ";" +
							std::to_string(accGx) + ";" +
							std::to_string(accGy) + ";" +
							std::to_string(accGz) + ";" +
							std::to_string(wheelSlipLF) + ";" +
							std::to_string(wheelSlipRF) + ";" +
							std::to_string(wheelSlipLR) + ";" +
							std::to_string(wheelSlipRR) + ";" +
							std::to_string(wheelLoadLF) + ";" +
							std::to_string(wheelLoadRF) + ";" +
							std::to_string(wheelLoadLR) + ";" +
							std::to_string(wheelLoadRR) + ";" +
							std::to_string(wheelsPressureLF) + ";" +
							std::to_string(wheelsPressureRF) + ";" +
							std::to_string(wheelsPressureLR) + ";" +
							std::to_string(wheelsPressureRR) + ";" +
							std::to_string(tyreCoreTemperatureLF) + ";" +
							std::to_string(tyreCoreTemperatureRF) + ";" +
							std::to_string(tyreCoreTemperatureLR) + ";" +
							std::to_string(tyreCoreTemperatureRR) + ";" +
							std::to_string(tyreWearLF) + ";" +
							std::to_string(tyreWearRF) + ";" +
							std::to_string(tyreWearLR) + ";" +
							std::to_string(tyreWearRR) + ";" +
							std::to_string(tyreDirtyLevelLF) + ";" +
							std::to_string(tyreDirtyLevelRF) + ";" +
							std::to_string(tyreDirtyLevelLR) + ";" +
							std::to_string(tyreDirtyLevelRR) + ";" +
							std::to_string(drs) + ";" +
							std::to_string(carDamage) + ";" +
							std::to_string(numberOfTyresOut) + ";" +

							std::to_string(completedLaps) + ";" +
							std::to_string(position) + ";" +
							std::to_string(iCurrentTime) + ";" +
							std::to_string(iLastTime) + ";" +
							std::to_string(iBestTime) + ";" +
							std::to_string(currentSectorIndex) + ";" +
							std::to_string(isInPit) + ";" +

							std::to_string(normalizedCarPosition) + ";" +
							std::to_string(carCoordinatesx) + ";" +
							std::to_string(carCoordinatesy) + ";" +
							std::to_string(carCoordinatesz) + ";";
	const char* cDatapacket = sDatapacket.c_str();
	return	cDatapacket;
}

DtLump::DtLump(int packetIdp) {
	packetId = packetIdp;
}

DtLump::DtLump(
	int packetIdp,

	AC_STATUS statusp,
	AC_SESSION_TYPE sessionp,

	float gasp,
	float clutch,
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


string StLump::makeheader() {
	return "carmodel;track;playername;playersurname;playernick;key";
}

string StLump::todatapacket() {
	string sDatapacket = carModel + ";" +
		track + ";" +
		playerName + ";" +
		playerSurname + ";" +
		playerNick + ";";
	const char* cDatapacket = sDatapacket.c_str();
	return	cDatapacket;
}

string StLump::actostring(wchar_t acstr[33]) {
	wstring ws(acstr);
	string str(ws.begin(), ws.end());
	return str;
}

StLump::StLump(wchar_t carModelp[33],
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