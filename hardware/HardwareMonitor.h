#pragma once
//#include "../main/RFXtrx.h"
#include "DomoticzHardware.h"
#if defined WIN32
	// for windows system info
	#include <wbemidl.h>
	#pragma comment(lib, "wbemuuid.lib")
#endif

class CHardwareMonitor : public CDomoticzHardwareBase
{
public:
	explicit CHardwareMonitor(const int ID);
	~CHardwareMonitor(void);
	bool WriteToHardware(const char* /*pdata*/, const unsigned char /*length*/) override { return false; };
private:
	bool StartHardware() override;
	bool StopHardware() override;
	double m_lastquerytime;
	std::shared_ptr<std::thread> m_thread;

	void Do_Work();
	void FetchData();
	void GetInternalTemperature();
	void FetchClockSpeeds();
	void GetInternalARMClockSpeed();
	void GetInternalV3DClockSpeed();
	void GetInternalCoreClockSpeed();
	void GetInternalVoltage();
	void GetInternalCurrent();
	void UpdateSystemSensor(const std::string& qType, const int dindex, const std::string& devName, const std::string& devValue);
	void SendCurrent(const unsigned long Idx, const float Curr, const std::string &defaultname);
#ifdef WIN32
	bool InitWMI();
	void ExitWMI();
	bool IsOHMRunning();
	void RunWMIQuery(const char* qTable, const std::string &qType);
	IWbemLocator *m_pLocator;
	IWbemServices *m_pServicesOHM;
	IWbemServices *m_pServicesSystem;
#elif defined (__linux__) || defined(__CYGWIN32__) || defined(__FreeBSD__) || defined(__OpenBSD__)
	void FetchUnixCPU();
	void FetchUnixMemory();
	void FetchUnixDisk();
	void CheckForOnboardSensors();
	double time_so_far();
#if defined (__linux__)
	float GetProcessMemUsage();
	float GetMemUsageLinux();
	bool IsWSL();
#endif
#if defined (__FreeBSD__) || defined(__OpenBSD__)
	float GetMemUsageOpenBSD();
#endif
	long long m_lastloadcpu;
	int m_totcpu;
	std::string m_dfcommand;
#endif
	bool bHasInternalTemperature;
	std::string szInternalTemperatureCommand;

	bool bHasInternalClockSpeeds;
	std::string szInternalARMSpeedCommand;
	std::string szInternalV3DSpeedCommand;
	std::string szInternalCoreSpeedCommand;

	bool bHasInternalVoltage;
	std::string szInternalVoltageCommand;

	bool bHasInternalCurrent;
	std::string szInternalCurrentCommand;
};
