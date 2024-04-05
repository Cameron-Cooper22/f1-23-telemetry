#ifndef PACKET_DEFS_H
#define PACKET_DEFS_H

#include <cstdint>

/* PACKET INFORMATION
 *
 * uint8_t
 * int8
 * uint16
 * int16_t
 * uint32
 * float
 * Double
 * uint64
 * char
 *
 * All packets will have this header:
 * */
 struct PacketHeader
 {
      uint16_t  m_packetFormat; 		// 2023
      uint8_t   m_gameYear; 	  		// Last 2 digits of game year e.g. 23
      uint8_t   m_gameMajorVersion;		// Game major version - "X.00"
      uint8_t   m_gameMinorVersion; 		// Game minor version = "1.XX"
      uint8_t   m_packetVersion;		// Version of this packet type, all start from 1
      uint8_t	m_packetId;			// Identifier for packet type
      uint64_t  m_sessionUID;			// Unique identifier for the session
      float 	m_sessionTime;			// Session timestamp
      uint32_t  m_frameIdentifier;		// Identifier for the frame the data was retrieved on
      uint32_t  m_overallFrameIdentifier;	// Overall identifier for the frame the data was retrieved
      uint8_t   m_playerCarIndex;       	// Index of player's car in the array
      uint8_t   m_secondaryPlayerCarIndex;	// Index of secondary player's car in the array, 255 if no second 
 						//   player
 };
/*			PACKET IDS
 *  ____________________ _______ _______________________________________________________________________
 * |	PACKET Name	|  VAL	|				DESCRIPTION				|
 * |Motion		|0	|All motion data for player's car. Only sent while player in control.	|
 * |Session		|1	|Data about session - track, time left					|
 * |Lap Data		|2	|Data about all laptimes of cars in session				|
 * |Event		|3	|Various notable events that happen in the session			|
 * |Participants	|4	|List of participants in the session, mostly relevant for multiplayer	|
 * |Car Setups		|5	|Details the car setups for cars in the race				|
 * |Car Telemetry	|6	|Telemetry data for all cars						|
 * |Car Status		|7	|Status data for all cars						|
 * |Final Classification|8	|Final classification confirmation at the end of a race			|
 * |Lobby Info		|9	|Information about players in a multiplayer lobby			|
 * |Car Damage		|10	|Damage status for all cars						|
 * |Session History	|11	|Lap and tyre data for session						|
 * |Tyre Sets		|12	|Extended tyre data set							|
 * |Motion Ex		|13	|Extended motion data for player car					|
 * |____________________|_______|_______________________________________________________________________|
 * */

/* MOTION PACKET */
// Frequency is specified in menus
// 1349 bytes
struct CarMotionData
{
  float   m_worldPositionX; // World space X position
  float   m_worldPositionY; // World space Y position
  float   m_worldPositionV; // World space Z position
  float   m_worldVelocityX; // Velocity in world space X
  float   m_worldVelocityY; // Velocity in world space Y
  float   m_worldVelocityZ; // Velocity in world space Z
			    //
  int16_t   m_worldForwardDirX; // World space forward X direction (normalised)
  int16_t   m_worldForwardDirY; // World space forward Y direction (normalised)
  int16_t   m_worldForwardDirZ; // World space forward Z direction (normalised)
  int16_t   m_worldRightDirX; 	// World space right X direction (normalised)
  int16_t   m_worldRightDirY;	// World space right Y direction (normalised)
  int16_t   m_worldRightDirZ;	// World space right Z direction (normalised)
				
  float   m_gForceLateral; 	// Lateral G-Force component
  float   m_gForceLongitudinal; // Longitudinal G-Force component
  float   m_gForceVertical;	// Vertical G-Force component
  float   m_yaw;		// Yaw angle in radians
  float   m_pitch;		// Pitch angle in radians
  float   m_roll;		// Roll angle in radians
};

struct PacketMotionData
{
  PacketHeader  m_header;		// Header

  CarMotionData m_carMotionData[22];	// Data for all cars on track
};

/* SESSION PACKET */
// Frequency: 2 per second
// 644 bytes

enum ZoneFlag
{
  UnknownFlag = -1,
  None = 0,
  Green = 1,
  Blue = 2,
  Yellow = 3
};

struct MarshalZone 
{
  // TODO look up wtf the marshal zone is
  float   m_zoneStart; 	// Fraction (0 -> 1) of way through the lap the marshal zone starts
  int8_t  m_zoneFlag;	// -1 = invalid/unknown, 0 = none, 1 = green, 2 = blue, 3 = yellow
};

enum WeatherType
{
  Clear,
  LightCloud,
  Overcast,
  LightRain,
  HeavyRain,
  Storm
};

enum SessionType
{
  UnknownSession,
  FP1,
  FP2,
  FP3,
  Short,
  Q1,
  Q2,
  Q3,
  ShortQ,
  OSQ,
  R,
  R2,
  R3,
  TimeTrial
};

enum TempChange
{
  Up,
  Down,
  NoChange
};

struct WeatherForecastSample
{
  uint8_t  m_sessionType;	// 0 = Unknown, 1 = FP1, 2 = FP2, 3 = FP3,
				// 4 = Short,   5 = Q1,  6 = Q2,  7 = Q3,
				// 8 = Short Q, 9 = OSQ, 10= R,   11= R2,
				// 12 = R3,     13= TimeT

  uint8_t  m_timeOffset; 	// Time in minutes the forecast is for
  uint8_t  m_weather;		// 0 = Clear, 1 = light cloud, 2 = overcast
				// 3 = light rain, 4 = heavy rain, 5 = storm
  
  int8_t   m_trackTemperature; 		// Track temperature in Celsius
  int8_t   m_trackTemperatureChange;	// Track temp change. 0 = up, 1 = down, 2 = no change
  
  int8_t   m_airTemperature;		// Air Temperature in Celsius
  int8_t   m_airTemperatureChange;	// Air temp change. 0 = up, 1 = down, 2 = no change

  uint8_t  m_rainPercentage;
};


enum Formula{
  F1Modern,
  F1Classic,
  F2
};

enum SafetyCar {
  NotOnTrack,
  Full,
  Virtual,
  Formation
};

enum SessionLength {
  NoLen,
  VeryShortLen,
  ShortLen,
  MedLen,
  MedLongLen,
  LongLen,
  FullLen
};

struct PacketSessionData
{
  PacketHeader 	m_header;

  // Same as WeatherForecastSample
  uint8_t      	m_weather;
  int8_t	m_trackTemperature;
  int8_t	m_airTemperature;

  uint8_t	m_totalLaps;
  uint16_t	m_trackLength; 	// Meters
  uint8_t	m_sessionType;

  int8_t	m_trackId;	// -1 for unknown TODO check word doc appendix
  uint8_t	m_formula;	// 0 = F1 Modern, 1 = F1 Classic, 2 = F2
  uint16_t	m_sessionTimeLeft; // Seconds
  uint16_t	m_sessionDuration;
  uint8_t	m_pitSpeedLimit;
  uint8_t	m_gamePaused;
  uint8_t	m_isSpectating;
  uint8_t	m_spectatorCarIndex; // Index of car being spectated

  uint8_t  	m_sliProNativeSupport; // 0 = inactive, 1 = active
  uint8_t 	m_numMarshalZones;

  MarshalZone 	m_marshalZones[21]; // List of marshal zones, maxing @ 21
  uint8_t	m_safetyCarStatus;
  uint8_t 	m_networkGame; // 0 = offline, 1 = online

  uint8_t		m_numWeatherForecastSamples; // Num ofweather samples to follow
  WeatherForecastSample m_weatherForecastSamples[56];
  uint8_t		m_forecastAccuracy; // 0 = perfect, 1 = approx

  uint8_t	m_aiDifficulty; // 0-110
  uint32_t	m_seasonLinkIdentifier; // Identifier for season; persists x saves
  uint32_t	m_weekendLinkIdentifier; // Identifier for weekend; persists x saves
  uint32_t	m_sessionLinkIdentifier; // Identifier for season; persists x saves

  uint8_t	m_pitStopWindowIdealLap;
  uint8_t	m_pitStopWindowLatestLap;
  uint8_t 	m_pitStopRejoinPosition;

  uint8_t	m_steeringAssist; // 0 = off, 1 = on
  uint8_t	m_brakingAssist; // 0 = off, 1 = low, 2 = med, 3 = high
  uint8_t	m_gearboxAssist; // 1 = manual, 2 = manual&suggested, 3 = auto
  uint8_t	m_pitAssist; // off/on
  uint8_t 	m_pitReleaseAssist; // off/on
  uint8_t 	m_ERSAssist; // off/on
  uint8_t	m_DRSAssist; // off/on
  uint8_t	m_dynamicRacingLine; // off/cornersOnly/full
  uint8_t	m_dynamicRacingLineType; // 2D/3D
  uint8_t	m_gameMode; // TODO check word doc appendix
  uint8_t	m_ruleSet; //TODO check appendix
  
  uint32_t 	m_timeOfDay; // Minutes since midnight
  uint8_t	m_sessionLength; // 0 = None, 2 = very short, 3 = short, 4 = medium
				 // 5 = med long, 6 = long, 7 = full
  uint8_t 	m_speedUnitsLeadPlayer; // 0 = mph, 1 = kph
  uint8_t	m_temperatureUnitsLeadPlayer; // 0 = celsius, 1 = fahrenheit
  uint8_t	m_speedUnitsSecondaryPlayer;
  uint8_t	m_temperatureUnitesSecondaryPlayer;

  uint8_t 	m_numSafetyCarPeriods; // Number of safety cars called during session
  uint8_t 	m_numVirtualSafetyCarPeriods;
  uint8_t 	m_numRedFlagPeriods;
};

enum DriverStatus
{
  InGarage,
  FlyingLap,
  InLap,
  OutLap,
  OnTrack
};

enum ResultStatus
{
  InvalidResult,
  InactiveResult,
  FinishedResult,
  DNFResult,
  DQResult,
  NotClassifiedResult,
  RetiredResult
};


/* LAP DATA PACKET */
// Rate as specified in menus
// 1131 bytes

struct LapData
{
  uint32_t	m_lastLapTimeInMS;
  uint32_t	m_currentLapTimeInMS;
  uint16_t	m_sector1TimeInMS;
  uint8_t	m_sector1TimeMinutes;
  uint16_t	m_sector2TimeInMS;
  uint16_t	m_sector2TimeInMinutes;
  
  uint16_t	m_deltaToCarInFrontInMS;
  float		m_lapDistance;
  float		m_totalDistance;
  uint8_t	m_carPosition;
  uint8_t	m_currentLapNum;

  uint8_t 	m_pitStatus; // 0 = None, 1 = Pitting, 2 = in pit lane
  uint8_t	m_numPitStops;

  uint8_t	m_sector; // 0 = Sector 1, 1 = Sector 2, 2 = Sector 3
  uint8_t 	m_currentLapInvalid; // 0 = Valid, 1 = Invalid
  uint8_t	m_penalties; // Accumulated time penalties in seconds to be added
  uint8_t 	m_totalWarnings;
  uint8_t	m_cornerCuttingWarnings;
  uint8_t	m_numUnservedDriveThroughPens;
  uint8_t	m_numUnservedStopGoPens;
  uint8_t	m_gridPosition; // Grid position the behicle started the race in
  uint8_t	m_driverStatus;
  uint8_t	m_resultStatus;

  uint8_t	m_pitLaneTimerActive; // 0 = inactive, 1 = active
  uint16_t	m_pitLaneTimeInLaneInMS;
  uint16_t	m_pitStopTimerInMS;
  uint8_t	m_pitStopShouldServePen;
};

struct PacketLapData
{
  PacketHeader 	m_header;
  LapData 	m_lapData[22];
  
  uint8_t	m_timeTrialPBCarIdx; //Index of personal Best car in time trial, 255 if invalid

  uint8_t	m_timeTrialRivalCarIdx; //Index of rival car in time trial, 255 is invalid
};

/* EVENT PACKET */
// Frequency is variable, on event occurence
// Size is 45 bytes

// EventDetails packet is different for each type of event
// Make sure only the correct type is interpreted
union EventDataDetails
{
  struct
  {
    uint8_t	vehicleIdx;
    float	lapTime;
  } FastestLap;

  struct
  {
    uint8_t	vehicleIdx;
  } Retirement;

  struct
  {
    uint8_t	vehicleIdx;
  } TeamMateInPits;

  struct
  {
    uint8_t	VehicleIdx;
  } RaceWinner;

  struct
  {
    uint8_t	penaltyType;
    uint8_t	infringementType;
    uint8_t	vehicleIdx;
    uint8_t	otherVehicleIdx;
    uint8_t	time;
    uint8_t	lapNum;
    uint8_t	placesGained;

  } Penalty;

  struct
  {
    uint8_t	vehicleIdx;
    float	speed;
    uint8_t	isOverallFastestInSession;
    uint8_t	isDriverFastestInSession;
    float	fastestSpeedInSession;
  } SpeedTrap;

  struct
  {
    uint8_t	numLights;
  } StartLights;

  struct
  {
    uint8_t	vehicleIdx;
  } DriveThroughPenaltyServed;

  struct
  {
    uint8_t	vehicleIdx;
  } StopGoPenaltyServed;

  struct
  {
    uint32_t	flashbackFrameIdentifier;
    float flashbackSessionTime;
  } Flashback;

  struct
  {
    uint32_t	buttonStatus;
  } Buttons;

  struct
  {
    uint8_t	overtakingVehicleIdx;
    uint8_t	beingOvertakenVehicleIdx;
  } Overtake;
};

struct PacketEventData
{
  PacketHeader		m_header;
  uint8_t		m_eventStringCode[4]; // TODO check appendix for the values
  EventDataDetails	m_eventDetails; //Interpret differently for each type
};

/* 
 _______________________________
|EVENT			|CODE	|
|_______________________|_______|
|Session Started	|"SSTA" |
|Session Ended		|"SEND" |
|Fastest Lap		|"FLTP" |
|Retirement		|"RTMT" |
|DRS Enabled		|"DRSE" |
|DRS Disabled		|"DRSD" |
|Teammate in pits	|"TMPT" |
|Chequered Flag		|"CHQF" |
|Race Winner		|"RCWN" |
|Penalty Issues		|"PENA" |
|Speed Trap Triggered	|"SPTP" |
|Start Lights		|"STLG" |
|Lights Out		|"LGOT" |
|Drive Through Served	|"DTSV" |
|Stop Go Served		|"SGSV" |
|Flashback		|"FLBK" |
|Button Status		|"BUTN" |
|Red Flag		|"RDFL" |
|Overtake		|"OVTK" |
|_______________________|_______|

*/

enum Platform
{
  Steam = 1,
  PlayStation = 3,
  Xbox = 4,
  Origin = 6,
  UnknownPlatform = 255
};

/* PARTICIPANT DATA PACKET */
// Every 5 seconds
// 1306 bytes

struct ParticipantData
{
  uint8_t	m_aiControlled; // 0 = Human, 1 = AI
  uint8_t	m_driverId; //TODO check appendix
  uint8_t	m_networkId;
  uint8_t	m_teamId;
  
  uint8_t 	m_myTeam; // 1 = my team, 0 = otherwise
  uint8_t 	m_raceNumber;
  uint8_t	m_nationalility;
  char		m_name[48]; // UTF-8 format
  
  uint8_t	m_yourTelemetry; // UDP setting, 0 = restricted, 1 = public
  uint8_t	m_showOnlineNames; // 0 = off, 1 = on
  uint8_t 	m_platform;
};

struct PacketParticipationData
{
  PacketHeader 		m_header;
  uint8_t		m_numActiveCars;
  ParticipantData	m_participants[22];
};

/* CAR SETUP PACKET */
// 2 per second
// 1107 bytes

struct CarSetupData
{
  uint8_t	m_frontWing;
  uint8_t	m_rearWing;
  uint8_t	m_onThrottle;
  uint8_t	m_offThrottle;
  float		m_frontCamber;
  float		m_rearCamber;
  float		m_frontToe;
  float		m_rearToe;
  uint8_t	m_frontSuspension;
  uint8_t	m_rearSuspension;
  uint8_t	m_frontAntiRollBar;
  uint8_t	m_rearAntiRollBar;
  uint8_t	m_frontSuspensionHeight;
  uint8_t	m_rearSuspensionHeight;
  uint8_t	m_brakePressure;
  uint8_t	m_brakeBias;
  float		m_rearLeftTyrePressure;
  float		m_rearRightTyrePressure;
  float		m_frontLeftTyrePressure;
  float		m_frontRightTyrePressure;
  uint8_t	m_ballast;
  float		m_fuelLoad;
};

struct PacketCarSetupData
{
  PacketHeader	m_header;
  CarSetupData	m_carSetups[22];
};

/* CAR TELEMETRY PACKET */
// Rate as specified in menus
// 1352 bytes

struct CarTelemetryData
{
  uint16_t	m_speed;
  float		m_throttle;
  float		m_steer;
  float		m_brake;
  uint8_t	m_clutch;
  int8_t	m_gear;
  uint16_t	m_engineRPM;
  uint8_t	m_drs;
  uint8_t	m_revLightsPercent;
  uint16_t	m_revLightsBitValue;
  uint16_t	m_brakesTemperature[4];
  uint8_t	m_tyresSurfaceTemperature[4];
  uint8_t	m_tyresInnerTemperature[4];
  uint16_t	m_engineTemperature;
  float		m_tyresPressure[4];
  float		m_surfaceType[4]; // TODO Check Appendices
};

struct PacketCarTelemetryData
{
  PacketHeader		m_header;
  CarTelemetryData	m_carTelemetryData[22];

  uint8_t	m_mfdPanelIndex; 
  uint8_t	m_mfdPanelIndexSecondaryPlayer;
  int8_t	m_suggestedGear; // 0 if no gear suggested
};

/* CAR STATUS PACKET */

// Rate specified in menus
// 1239 bytes

struct CarStatusData
{
    uint8_t       m_tractionControl;          // Traction control - 0 = off, 1 = medium, 2 = full
    uint8_t       m_antiLockBrakes;           // 0 (off) - 1 (on)
    uint8_t       m_fuelMix;                  // Fuel mix - 0 = lean, 1 = standard, 2 = rich, 3 = max
    uint8_t       m_frontBrakeBias;           // Front brake bias (percentage)
    uint8_t       m_pitLimiterStatus;         // Pit limiter status - 0 = off, 1 = on
    float       m_fuelInTank;               // Current fuel mass
    float       m_fuelCapacity;             // Fuel capacity
    float       m_fuelRemainingLaps;        // Fuel remaining in terms of laps (value on MFD)
    uint16_t      m_maxRPM;                   // Cars max RPM, point of rev limiter
    uint16_t      m_idleRPM;                  // Cars idle RPM
    uint8_t       m_maxGears;                 // Maximum number of gears
    uint8_t       m_drsAllowed;               // 0 = not allowed, 1 = allowed
    uint16_t      m_drsActivationDistance;    // 0 = DRS not available, non-zero - DRS will be available
                                            // in [X] metres
    uint8_t       m_actualTyreCompound;	   // F1 Modern - 16 = C5, 17 = C4, 18 = C3, 19 = C2, 20 = C1
   					   // 21 = C0, 7 = inter, 8 = wet
   					   // F1 Classic - 9 = dry, 10 = wet
   					   // F2 – 11 = super soft, 12 = soft, 13 = medium, 14 = hard
   					   // 15 = wet
    uint8_t       m_visualTyreCompound;       // F1 visual (can be different from actual compound)
                                            // 16 = soft, 17 = medium, 18 = hard, 7 = inter, 8 = wet
                                            // F1 Classic – same as above
                                            // F2 ‘19, 15 = wet, 19 – super soft, 20 = soft
                                            // 21 = medium , 22 = hard
    uint8_t       m_tyresAgeLaps;             // Age in laps of the current set of tyres
    int8_t        m_vehicleFiaFlags;	   // -1 = invalid/unknown, 0 = none, 1 = green
                                            // 2 = blue, 3 = yellow
    float       m_enginePowerICE;           // Engine power output of ICE (W)
    float       m_enginePowerMGUK;          // Engine power output of MGU-K (W)
    float       m_ersStoreEnergy;           // ERS energy store in Joules
    uint8_t       m_ersDeployMode;            // ERS deployment mode, 0 = none, 1 = medium
   					   // 2 = hotlap, 3 = overtake
    float       m_ersHarvestedThisLapMGUK;  // ERS energy harvested this lap by MGU-K
    float       m_ersHarvestedThisLapMGUH;  // ERS energy harvested this lap by MGU-H
    float       m_ersDeployedThisLap;       // ERS energy deployed this lap
    uint8_t       m_networkPaused;            // Whether the car is paused in a network game
};

struct PacketCarStatusData
{
    PacketHeader    	m_header;	   // Header

    CarStatusData	m_carStatusData[22];
};

/* FINAL CLASSIFICATION PACKET */
// Once at end of race
// 1020 bytes

struct FinalClassificationData
{
    uint8_t     m_position;              // Finishing position
    uint8_t     m_numLaps;               // Number of laps completed
    uint8_t     m_gridPosition;          // Grid position of the car
    uint8_t     m_points;                // Number of points scored
    uint8_t     m_numPitStops;           // Number of pit stops made
    uint8_t     m_resultStatus;          // Result status - 0 = invalid, 1 = inactive, 2 = active
                                       // 3 = finished, 4 = didnotfinish, 5 = disqualified
                                       // 6 = not classified, 7 = retired
    uint32_t    m_bestLapTimeInMS;       // Best lap time of the session in milliseconds
    double    m_totalRaceTime;         // Total race time in seconds without penalties
    uint8_t     m_penaltiesTime;         // Total penalties accumulated in seconds
    uint8_t     m_numPenalties;          // Number of penalties applied to this driver
    uint8_t     m_numTyreStints;         // Number of tyres stints up to maximum
    uint8_t     m_tyreStintsActual[8];   // Actual tyres used by this driver
    uint8_t     m_tyreStintsVisual[8];   // Visual tyres used by this driver
    uint8_t     m_tyreStintsEndLaps[8];  // The lap number stints end on
};

struct PacketFinalClassificationData
{
  PacketHeader 	m_header;

  uint8_t	m_numCars;
  FinalClassificationData m_classificationData[22];
};

/* LOBBY INFO PACKET */
// 2 every second while in lobby
// 1218 bytes


struct LobbyInfoData
{
    uint8_t     m_aiControlled;            // Whether the vehicle is AI (1) or Human (0) controlled
    uint8_t     m_teamId;            // Team id - see appendix (255 if no team currently selected)
    uint8_t     m_nationality;       // Nationality of the driver
    uint8_t     m_platform;          // 1 = Steam, 3 = PlayStation, 4 = Xbox, 6 = Origin, 255 = unknown
    char      m_name[48];	  // Name of participant in UTF-8 format – null terminated
                                   // Will be truncated with ... (U+2026) if too long
    uint8_t     m_carNumber;         // Car number of the player
    uint8_t     m_readyStatus;       // 0 = not ready, 1 = ready, 2 = spectating
};


struct PacketLobbyInfoData
{
    PacketHeader    m_header;                       // Header

    // Packet specific data
    uint8_t               m_numPlayers;               // Number of players in the lobby data
    LobbyInfoData       m_lobbyPlayers[22];
};

/* CAR DAMAGE PACKET */
//10 per second
//953 bytes

struct CarDamageData
{
    float     m_tyresWear[4];                     // Tyre wear (percentage)
    uint8_t     m_tyresDamage[4];                   // Tyre damage (percentage)
    uint8_t     m_brakesDamage[4];                  // Brakes damage (percentage)
    uint8_t     m_frontLeftWingDamage;              // Front left wing damage (percentage)
    uint8_t     m_frontRightWingDamage;             // Front right wing damage (percentage)
    uint8_t     m_rearWingDamage;                   // Rear wing damage (percentage)
    uint8_t     m_floorDamage;                      // Floor damage (percentage)
    uint8_t     m_diffuserDamage;                   // Diffuser damage (percentage)
    uint8_t     m_sidepodDamage;                    // Sidepod damage (percentage)
    uint8_t     m_drsFault;                         // Indicator for DRS fault, 0 = OK, 1 = fault
    uint8_t     m_ersFault;                         // Indicator for ERS fault, 0 = OK, 1 = fault
    uint8_t     m_gearBoxDamage;                    // Gear box damage (percentage)
    uint8_t     m_engineDamage;                     // Engine damage (percentage)
    uint8_t     m_engineMGUHWear;                   // Engine wear MGU-H (percentage)
    uint8_t     m_engineESWear;                     // Engine wear ES (percentage)
    uint8_t     m_engineCEWear;                     // Engine wear CE (percentage)
    uint8_t     m_engineICEWear;                    // Engine wear ICE (percentage)
    uint8_t     m_engineMGUKWear;                   // Engine wear MGU-K (percentage)
    uint8_t     m_engineTCWear;                     // Engine wear TC (percentage)
    uint8_t     m_engineBlown;                      // Engine blown, 0 = OK, 1 = fault
    uint8_t     m_engineSeized;                     // Engine seized, 0 = OK, 1 = fault
};


struct PacketCarDamageData
{
    PacketHeader    m_header;               // Header

    CarDamageData   m_carDamageData[22];
};

/* SESSION HISTORY PACKET */
// 20 persecond, cycles through cars
// 1460 bytes

struct LapHistoryData
{
    uint32_t    m_lapTimeInMS;           // Lap time in milliseconds
    uint16_t    m_sector1TimeInMS;       // Sector 1 time in milliseconds
    uint8_t     m_sector1TimeMinutes;    // Sector 1 whole minute part
    uint16_t    m_sector2TimeInMS;       // Sector 2 time in milliseconds
    uint8_t     m_sector2TimeMinutes;    // Sector 2 whole minute part
    uint16_t    m_sector3TimeInMS;       // Sector 3 time in milliseconds
    uint8_t     m_sector3TimeMinutes;    // Sector 3 whole minute part
    uint8_t     m_lapValidBitFlags;      // 0x01 bit set-lap valid,      0x02 bit set-sector 1 valid
                                       // 0x04 bit set-sector 2 valid, 0x08 bit set-sector 3 valid
};


struct TyreStintHistoryData
{
    uint8_t     m_endLap;                // Lap the tyre usage ends on (255 of current tyre)
    uint8_t     m_tyreActualCompound;    // Actual tyres used by this driver
    uint8_t     m_tyreVisualCompound;    // Visual tyres used by this driver
};


struct PacketSessionHistoryData
{
    PacketHeader  m_header;                   // Header

    uint8_t         m_carIdx;                   // Index of the car this lap data relates to
    uint8_t         m_numLaps;                  // Num laps in the data (including current partial lap)
    uint8_t         m_numTyreStints;            // Number of tyre stints in the data

    uint8_t         m_bestLapTimeLapNum;        // Lap the best lap time was achieved on
    uint8_t         m_bestSector1LapNum;        // Lap the best Sector 1 time was achieved on
    uint8_t         m_bestSector2LapNum;        // Lap the best Sector 2 time was achieved on
    uint8_t         m_bestSector3LapNum;        // Lap the best Sector 3 time was achieved on

    LapHistoryData          m_lapHistoryData[100];	// 100 laps of data max
    TyreStintHistoryData    m_tyreStintsHistoryData[8];
};


struct TyreSetData
{
    uint8_t     m_actualTyreCompound;    // Actual tyre compound used
    uint8_t     m_visualTyreCompound;    // Visual tyre compound used
    uint8_t     m_wear;                  // Tyre wear (percentage)
    uint8_t     m_available;             // Whether this set is currently available
    uint8_t     m_recommendedSession;    // Recommended session for tyre set
    uint8_t     m_lifeSpan;              // Laps left in this tyre set
    uint8_t     m_usableLife;            // Max number of laps recommended for this compound
    int16_t     m_lapDeltaTime;          // Lap delta time in milliseconds compared to fitted set
    uint8_t     m_fitted;                // Whether the set is fitted or not
};


struct PacketTyreSetsData
{
    PacketHeader    m_header;            // Header

    uint8_t           m_carIdx;            // Index of the car this data relates to

    TyreSetData     m_tyreSetData[20];	// 13 (dry) + 7 (wet)

    uint8_t           m_fittedIdx;         // Index into array of fitted tyre
};

/* MOTION EX PACKET */
// rate specified in menus
// 217 bytes

struct PacketMotionExData
{
    PacketHeader    m_header;               	// Header

    // Extra player car ONLY data
    float         m_suspensionPosition[4];       // Note: All wheel arrays have the following order:
    float         m_suspensionVelocity[4];       // RL, RR, FL, FR
    float         m_suspensionAcceleration[4];	// RL, RR, FL, FR
    float         m_wheelSpeed[4];           	// Speed of each wheel
    float         m_wheelSlipRatio[4];           // Slip ratio for each wheel
    float         m_wheelSlipAngle[4];           // Slip angles for each wheel
    float         m_wheelLatForce[4];            // Lateral forces for each wheel
    float         m_wheelLongForce[4];           // Longitudinal forces for each wheel
    float         m_heightOfCOGAboveGround;      // Height of centre of gravity above ground    
    float         m_localVelocityX;         	// Velocity in local space – metres/s
    float         m_localVelocityY;         	// Velocity in local space
    float         m_localVelocityZ;         	// Velocity in local space
    float         m_angularVelocityX;		// Angular velocity x-component – radians/s
    float         m_angularVelocityY;            // Angular velocity y-component
    float         m_angularVelocityZ;            // Angular velocity z-component
    float         m_angularAccelerationX;        // Angular acceleration x-component – radians/s/s
    float         m_angularAccelerationY;	// Angular acceleration y-component
    float         m_angularAccelerationZ;        // Angular acceleration z-component
    float         m_frontWheelsAngle;            // Current front wheels angle in radians
    float         m_wheelVertForce[4];           // Vertical forces for each wheel
};



#endif

/* _____________________________________________________________________________________________________________________
 * ID |TEAM					|ID |TEAM				|ID |TEAM			|
 * 0  |Mercedes					|106|Prema '21				|136|Campos '22			|
 * 1  |Ferrari					|107|Uni-Virtuosi '21			|137|Van Amersfoort Racing '22	|
 * 2  |Red Bull Racing				|108|Carlin '21				|138|Trident '22		|
 * 3  |Williams					|109|Hitech '21				|139|Hitech '22			|
 * 4  |Aston Martin				|110|Art GP '21				|140|Art GP '22			|
 * 5  |Alpine					|111|MP Motorsport '21			|___|___________________________|
 * 6  |Alpha Tauri				|112|Charouz '21			|
 * 7  |Haas					|113|Dams '21				|
 * 8  |McLaren					|114|Campos '21				|
 * 9  |Alfa Romeo				|115|BWT '21				|
 * 85 |Mercedes 2020				|116|Trident '21			|
 * 86 |Ferrari 2020				|117|Mercedes AMG GT Black Series	|
 * 87 |Red Bull 2020				|118|Mercedes '22			|
 * 88 |Williams 2020				|119|Ferrari '22			|
 * 89 |Racing Point 2020			|120|Red Bull Racing '22		|
 * 90 |Renault 2020				|121|Williams '22			|
 * 91 |Alpha Tauri 2-2-				|122|Aston Martin '22			|
 * 92 |Haas 2020				|123|Alpine '22				|
 * 93 |McLaren 2020				|124|Alpha Tauri '22			|
 * 94 |Alfa Romeo 2020				|125|Haas '22				|
 * 95 |Aston Martin DB11 V12			|126|McLaren '22			|
 * 96 |AstonMartin Vantage F1 Edition		|127|Alfa Romeo '22			|
 * 97 |Aston Martin Vantage Safety Car		|128|Konnersport '22			|
 * 98 |Ferrari F8 Tributo			|129|Konnersport			|
 * 99 |Ferrari Roma				|130|Prema '22				|
 * 100|McLaren 720S				|131|Virtuosi '22			|
 * 101|McLaren Artura				|132|Carlin '22				|
 * 102|Mercedes AMG GT Black Series Safety Car	|133|MP Motorsport '22			|
 * 103|Mercedes AMG GTR Pro			|134|Charouz '22			|
 * 104|F1 Custom Team				|135|Dams '22				|
 * ___|_________________________________________|___|___________________________________|
 */
