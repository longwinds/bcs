#pragma once

class CDevMon
{
public:
	CDevMon(void);
	~CDevMon(void);
	int dev_mon_thread(void);
	int start(void);
	HANDLE m_h_event_dev_mon_exit;
	HANDLE m_h_thread_dev_mon;
	SOCKET m_sock_monitor;
	int m_idevice_hartjump_cnt[256];
	int get_state(int gf);

};

