// CCTDlg.h : 头文件
//

#pragma once
#include "wavplayer.h"

#include <Mmsystem.h>
#include "afxwin.h"
#include "DevMon.h"
// CCCTDlg 对话框
class CCCTDlg : public CDialog
{
// 构造
public:
	CCCTDlg(CWnd* pParent = NULL);	// 标准构造函数

// 对话框数据
	enum { IDD = IDD_CCT_DIALOG };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedButtonTest();
	CWavPlayer m_wav_palyer;

	// 
	HWAVEIN m_hWaveIn;  //输入设备  
	WAVEFORMATEX m_waveform; //采集音频的格式，结构体  
	BYTE *m_pBuffer1,*m_pBuffer2;//采集音频时的数据缓存  
	WAVEHDR m_wHdr1,m_wHdr2; //采集音频时包含数据缓存的结构体  
	static DWORD CALLBACK MicCallback(  //消息回掉函数  
		HWAVEIN hWaveIn,   
		UINT  uMsg,   
		DWORD dwInstance,   
		DWORD dwParam1,   
		DWORD dwParam2);  
	int initRecord(void);
	int stopRecord(void);
	afx_msg void OnBnClickedButtonStop();
	int m_record_on;
	int udp_client_init(void);
	SOCKET m_sock,m_sock_monitor;
	struct sockaddr_in m_addr_remote;
	BYTE m_u8pcm_buf[2+32+1280];
	BYTE m_u8pcm_buf_copy[2+32+1280];

	int set_speaker(int speaker, int onoff);
	afx_msg void OnBnClickedCheck1();
	BOOL m_spk1;
	BOOL m_spk2;
	BOOL m_spk3;
	BOOL m_spk4;
	BOOL m_spk5;
	BOOL m_spk6;
	BOOL m_spk7;
	BOOL m_spk8;
	BOOL m_spk9;
	BOOL m_spk10;
	BOOL m_spk11;
	BOOL m_spk12;
	BOOL m_spk13;
	BOOL m_spk14;
	BOOL m_spk15;
	afx_msg void OnBnClickedCheck2();
	afx_msg void OnBnClickedCheck3();
	afx_msg void OnBnClickedCheck4();
	afx_msg void OnBnClickedCheck5();
	afx_msg void OnBnClickedCheck6();
	afx_msg void OnBnClickedCheck7();
	afx_msg void OnBnClickedCheck8();
	afx_msg void OnBnClickedCheck9();
	afx_msg void OnBnClickedCheck10();
	afx_msg void OnBnClickedCheck11();
	afx_msg void OnBnClickedCheck12();
	afx_msg void OnBnClickedCheck13();
	afx_msg void OnBnClickedCheck14();
	afx_msg void OnBnClickedCheck15();
	afx_msg void OnBnClickedCheckSelectNear();
	int m_mic_enable;
	CButton m_btnMicEnable;
	BOOL m_bselect_all;
	afx_msg void OnBnClickedCheckAll();
	BOOL m_bselect_near;
	CButton m_chkGF[16];
	/*CButton m_chkGF2;
	CButton m_chkGF3;
	CButton m_chkGF4;
	CButton m_chkGF5;
	CButton m_chkGF6;
	CButton m_chkGF7;
	CButton m_chkGF8;
	CButton m_chkGF9;
	CButton m_chkGF10;
	CButton m_chkGF11;
	CButton m_chkGF12;
	CButton m_chkGF13;
	CButton m_chkGF14;
	CButton m_chkGF15;*/
	afx_msg void OnTimer(UINT_PTR nIDEvent);
	
	//CString m_strState[15];
	CStatic m_stcState[15];
	CFile m_sndfile;
	int m_cap_cnt;
	CDevMon m_dev_mon;
	CStatic m_stclist[3];
	CButton m_btn_play[3];
	CButton m_chk_cycle_play[3];
	CButton m_btn_open[24];
	CEdit m_edt_file[24];
	afx_msg void OnBnClickedButtonOpen1();
	afx_msg void OnBnClickedRadioList1();
	HANDLE hplay_pcm_timer;
	HANDLE htimer_queue;
	//unsigned char 
	afx_msg void OnBnClickedCheckPlayFile();
	CButton m_chk_is_play_file;
	unsigned char* m_p_pcm_file_buf[24];
	unsigned int m_pcm_file_len[24];
	afx_msg void OnBnClickedOk();
	afx_msg void OnBnClickedButtonOpen2();
	afx_msg void OnBnClickedButtonOpen3();
	afx_msg void OnTRBNThumbPosChangingSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	int m_s32_volume;
	afx_msg void OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult);
	CStatic m_stcVolume;
	int m_current_playlist;
	int m_offset;
	int file_index;
};
