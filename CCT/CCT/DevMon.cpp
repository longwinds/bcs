#include "StdAfx.h"
#include "DevMon.h"
#include "log4z.h"
DWORD WINAPI call_dev_mon_thread(LPVOID pvoid)
{
	LOGFMTT("%s \r\n",__FUNCTION__);
	CDevMon* pobj = (CDevMon*)pvoid;
	pobj->dev_mon_thread();
	return 0;
}

CDevMon::CDevMon(void)
{
	for(int i=0;i<256;i++)
		m_idevice_hartjump_cnt[i] = -1;
}

CDevMon::~CDevMon(void)
{
}

int CDevMon::get_state(int gf)
{
	return m_idevice_hartjump_cnt[gf];

}
int CDevMon::dev_mon_thread(void)
{
	LOGFMTT("%s start\r\n",__FUNCTION__);
	m_sock_monitor = socket(AF_INET,SOCK_DGRAM,0); 
	int nTvlen=5000;  //1s
	setsockopt(m_sock_monitor,SOL_SOCKET,SO_RCVTIMEO,(const char*)&nTvlen, sizeof(nTvlen));
	do
	{
		if(WAIT_OBJECT_0 == WaitForSingleObject(m_h_event_dev_mon_exit,0))
		{
			LOGFMTT("%s exit 0\n",__FUNCTION__);
			return 0;
		}
		struct sockaddr_in addr_remote;
		int sock_len =sizeof(addr_remote);
		addr_remote.sin_family=AF_INET;
		addr_remote.sin_port=htons(1200); ///server的监听端口
		addr_remote.sin_addr.s_addr=inet_addr("192.168.22.255"); ///server的地址 
		char buf[1500] = "get_state\0";
		if (sendto(m_sock_monitor,buf,strlen(buf),0,(struct sockaddr*)&addr_remote,sizeof(addr_remote))!=SOCKET_ERROR)
		{
			int sock_len =sizeof(addr_remote);
			memset(buf,0,1500);
			int rcv_len = recvfrom(m_sock_monitor,(char*)buf,sizeof(buf),0,(struct sockaddr*)&addr_remote,&sock_len);
			if (rcv_len >0 )
			{
				LOGFMTT("rcv[%d]:%s",rcv_len,buf);

			}
			for(int i=1;i<16;i++)
			{
				char flag[16];
				sprintf_s(flag,16,"{DEV_ID:%d}",i);
				if(strstr(buf,flag))
				{
					if(m_idevice_hartjump_cnt[i]<=0)
					{
						LOGFMTT("DEV[%d] online",i);
					//	m_stcState[i-1].SetWindowText(_T("在线"));
					}
					m_idevice_hartjump_cnt[i] = 6;

				}
				else
				{
					m_idevice_hartjump_cnt[i]--;
					if(m_idevice_hartjump_cnt[i]==0)
					{
						//m_idevice_hartjump_cnt[i] = 0;
						LOGFMTT("DEV[%d] Offline",i);
						//m_stcState[i-1].SetWindowText(_T("断开"));
					}
				}
			}
			//UpdateData(0);
		}
		else
		{
			LOGFMTT("%s send err:%d",__FUNCTION__, GetLastError());
		}
	
		Sleep(5000);
	}while (1);
	LOGFMTT("%s exit 1\n",__FUNCTION__);
	return 0;
}

int CDevMon::start(void)
{
	m_h_event_dev_mon_exit = CreateEvent( 
		NULL,               // default security attributes
		FALSE,               // manual-reset event
		FALSE,               // initial state is signaled
		NULL				 // object name
		); 

	if (m_h_event_dev_mon_exit == NULL) 
	{ 
		TRACE("Create receiver exit Event failed (%d)\n", GetLastError());
		return -1;
	}
	DWORD id;
	TRACE("%s \r\n",__FUNCTION__);
	m_h_thread_dev_mon = CreateThread( 
		NULL,              // default security attributes
		0,                 // use default stack size  
		call_dev_mon_thread,          // thread function 
		this,             // argument to thread function 
		0,                 // use default creation flags 
		&id);   // returns the thread identifier 
	if (m_h_thread_dev_mon == NULL) 
	{
		TRACE("create receiver thread err:%d\r\n",GetLastError());
		return -1;
	}
	m_sock_monitor = socket(AF_INET,SOCK_DGRAM,0); 
	// set rcv timeout
	int nTvlen=200;  //1s
	setsockopt(m_sock_monitor,SOL_SOCKET,SO_RCVTIMEO,(const char*)&nTvlen, sizeof(nTvlen));

	return 0;
}

