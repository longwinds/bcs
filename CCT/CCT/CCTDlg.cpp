// CCTDlg.cpp : ʵ���ļ�
//

#include "stdafx.h"
#include "CCT.h"
#include "CCTDlg.h"
#include "log4z.h" 
#include "DevMon.h"
#pragma comment(lib, "winmm.lib")
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#define PCM16 1

using namespace zsummer::log4z;  
// ����Ӧ�ó��򡰹��ڡ��˵���� CAboutDlg �Ի���

class CAboutDlg : public CDialog
{
public:
	CAboutDlg();

// �Ի�������
	enum { IDD = IDD_ABOUTBOX };

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV ֧��

// ʵ��
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialog(CAboutDlg::IDD)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialog)
END_MESSAGE_MAP()


// CCCTDlg �Ի���




CCCTDlg::CCCTDlg(CWnd* pParent /*=NULL*/)
	: CDialog(CCCTDlg::IDD, pParent)
	, m_record_on(0)
	, m_spk1(FALSE)
	, m_spk2(FALSE)
	, m_spk3(FALSE)
	, m_spk4(FALSE)
	, m_spk5(FALSE)
	, m_spk6(FALSE)
	, m_spk7(FALSE)
	, m_spk8(FALSE)
	, m_spk9(FALSE)
	, m_spk10(FALSE)
	, m_spk11(FALSE)
	, m_spk12(FALSE)
	, m_spk13(FALSE)
	, m_spk14(FALSE)
	, m_spk15(FALSE)
	, m_mic_enable(0)
	, m_bselect_all(FALSE)
	, m_bselect_near(FALSE)
	
	, m_s32_volume(50)
{
	ILog4zManager::getRef().start();  
	
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);

	LOGT("stream input *** " << "LOGT LOGT LOGT LOGT" << " *** ");  
	LOGD("stream input *** " << "LOGD LOGD LOGD LOGD" << " *** ");  
	LOGI("stream input *** " << "LOGI LOGI LOGI LOGI" << " *** ");  
	LOGW("stream input *** " << "LOGW LOGW LOGW LOGW" << " *** ");  
	LOGE("stream input *** " << "LOGE LOGE LOGE LOGE" << " *** ");  
	LOGA("stream input *** " << "LOGA LOGA LOGA LOGA" << " *** ");  
	LOGF("stream input *** " << "LOGF LOGF LOGF LOGF" << " *** ");
	LOGFMTT("format input *** %s *** %d ***", "LOGFMTT", 123456);  
	LOGFMTD("format input *** %s *** %d ***", "LOGFMTD", 123456);  
	LOGFMTI("format input *** %s *** %d ***", "LOGFMTI", 123456);  
	LOGFMTW("format input *** %s *** %d ***", "LOGFMTW", 123456);  
	LOGFMTE("format input *** %s *** %d ***", "LOGFMTE", 123456);  
	LOGFMTA("format input *** %s *** %d ***", "LOGFMTA", 123456);  
	LOGFMTF("format input *** %s *** %d ***", "LOGFMTF", 123456);  

	LOGA("main quit ...");  
	for(int i=0;i<24;i++)
	{
		 m_pcm_file_len[i] =0;
	}
	htimer_queue = NULL;
	m_current_playlist = 0;
	m_offset = 0;
	file_index = 0;
}

void CCCTDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialog::DoDataExchange(pDX);
	DDX_Check(pDX, IDC_CHECK1, m_spk1);
	DDX_Check(pDX, IDC_CHECK2, m_spk2);
	DDX_Check(pDX, IDC_CHECK3, m_spk3);
	DDX_Check(pDX, IDC_CHECK4, m_spk4);
	DDX_Check(pDX, IDC_CHECK5, m_spk5);
	DDX_Check(pDX, IDC_CHECK6, m_spk6);
	DDX_Check(pDX, IDC_CHECK7, m_spk7);
	DDX_Check(pDX, IDC_CHECK8, m_spk8);
	DDX_Check(pDX, IDC_CHECK9, m_spk9);
	DDX_Check(pDX, IDC_CHECK10, m_spk10);
	DDX_Check(pDX, IDC_CHECK11, m_spk11);
	DDX_Check(pDX, IDC_CHECK12, m_spk12);
	DDX_Check(pDX, IDC_CHECK13, m_spk13);
	DDX_Check(pDX, IDC_CHECK14, m_spk14);
	DDX_Check(pDX, IDC_CHECK15, m_spk15);

	DDX_Control(pDX, IDC_BUTTON_TEST, m_btnMicEnable);
	DDX_Check(pDX, IDC_CHECK_ALL, m_bselect_all);
	DDX_Check(pDX, IDC_CHECK_SELECT_NEAR, m_bselect_near);
	DDX_Control(pDX, IDC_CHECK1, m_chkGF[0]);
	DDX_Control(pDX, IDC_CHECK2, m_chkGF[1]);
	DDX_Control(pDX, IDC_CHECK3, m_chkGF[2]);
	DDX_Control(pDX, IDC_CHECK4, m_chkGF[3]);
	DDX_Control(pDX, IDC_CHECK5, m_chkGF[4]);
	DDX_Control(pDX, IDC_CHECK6, m_chkGF[5]);
	DDX_Control(pDX, IDC_CHECK7, m_chkGF[6]);
	DDX_Control(pDX, IDC_CHECK8, m_chkGF[7]);
	DDX_Control(pDX, IDC_CHECK9, m_chkGF[8]);
	DDX_Control(pDX, IDC_CHECK10, m_chkGF[9]);
	DDX_Control(pDX, IDC_CHECK11, m_chkGF[10]);
	DDX_Control(pDX, IDC_CHECK12, m_chkGF[11]);
	DDX_Control(pDX, IDC_CHECK13, m_chkGF[12]);
	DDX_Control(pDX, IDC_CHECK14, m_chkGF[13]);
	DDX_Control(pDX, IDC_CHECK15, m_chkGF[14]);



	DDX_Control(pDX, IDC_STATIC1, m_stcState[0]);
	DDX_Control(pDX, IDC_STATIC2, m_stcState[1]);
	DDX_Control(pDX, IDC_STATIC3, m_stcState[2]);
	DDX_Control(pDX, IDC_STATIC4, m_stcState[3]);
	DDX_Control(pDX, IDC_STATIC5, m_stcState[4]);
	DDX_Control(pDX, IDC_STATIC6, m_stcState[5]);
	DDX_Control(pDX, IDC_STATIC7, m_stcState[6]);
	DDX_Control(pDX, IDC_STATIC8, m_stcState[7]);
	DDX_Control(pDX, IDC_STATIC9, m_stcState[8]);
	DDX_Control(pDX, IDC_STATIC10, m_stcState[9]);
	DDX_Control(pDX, IDC_STATIC11, m_stcState[10]);
	DDX_Control(pDX, IDC_STATIC12, m_stcState[11]);
	DDX_Control(pDX, IDC_STATIC13, m_stcState[12]);
	DDX_Control(pDX, IDC_STATIC14, m_stcState[13]);
	DDX_Control(pDX, IDC_STATIC15, m_stcState[14]);

	DDX_Control(pDX, IDC_STATIC_LIST1, m_stclist[0]);
	DDX_Control(pDX, IDC_STATIC_LIST2, m_stclist[1]);
	DDX_Control(pDX, IDC_STATIC_LIST3, m_stclist[2]);

	DDX_Control(pDX, IDC_RADIO_LIST1, m_btn_play[0]);
	DDX_Control(pDX, IDC_RADIO_LIST2, m_btn_play[1]);
	DDX_Control(pDX, IDC_RADIO_LIST3, m_btn_play[2]);
	DDX_Control(pDX, IDC_CHECK_CYCLE_PLAY1, m_chk_cycle_play[0]);
	DDX_Control(pDX, IDC_CHECK_CYCLE_PLAY2, m_chk_cycle_play[1]);
	DDX_Control(pDX, IDC_CHECK_CYCLE_PLAY3, m_chk_cycle_play[2]);
	DDX_Control(pDX, IDC_BUTTON_OPEN1, m_btn_open[0]);
	DDX_Control(pDX, IDC_BUTTON_OPEN2, m_btn_open[1]);
	DDX_Control(pDX, IDC_BUTTON_OPEN3, m_btn_open[2]);
	DDX_Control(pDX, IDC_BUTTON_OPEN4, m_btn_open[3]);
	DDX_Control(pDX, IDC_BUTTON_OPEN5, m_btn_open[4]);
	DDX_Control(pDX, IDC_BUTTON_OPEN6, m_btn_open[5]);
	DDX_Control(pDX, IDC_BUTTON_OPEN7, m_btn_open[6]);
	DDX_Control(pDX, IDC_BUTTON_OPEN8, m_btn_open[7]);
	DDX_Control(pDX, IDC_BUTTON_OPEN9, m_btn_open[8]);
	DDX_Control(pDX, IDC_BUTTON_OPEN10, m_btn_open[9]);
	DDX_Control(pDX, IDC_BUTTON_OPEN11, m_btn_open[10]);
	DDX_Control(pDX, IDC_BUTTON_OPEN12, m_btn_open[11]);
	DDX_Control(pDX, IDC_BUTTON_OPEN13, m_btn_open[12]);
	DDX_Control(pDX, IDC_BUTTON_OPEN14, m_btn_open[13]);
	DDX_Control(pDX, IDC_BUTTON_OPEN15, m_btn_open[14]);
	DDX_Control(pDX, IDC_BUTTON_OPEN16, m_btn_open[15]);
	DDX_Control(pDX, IDC_BUTTON_OPEN17, m_btn_open[16]);
	DDX_Control(pDX, IDC_BUTTON_OPEN18, m_btn_open[17]);
	DDX_Control(pDX, IDC_BUTTON_OPEN19, m_btn_open[18]);
	DDX_Control(pDX, IDC_BUTTON_OPEN20, m_btn_open[19]);
	DDX_Control(pDX, IDC_BUTTON_OPEN21, m_btn_open[20]);
	DDX_Control(pDX, IDC_BUTTON_OPEN22, m_btn_open[21]);
	DDX_Control(pDX, IDC_BUTTON_OPEN23, m_btn_open[22]);
	DDX_Control(pDX, IDC_BUTTON_OPEN24, m_btn_open[23]);

	DDX_Control(pDX, IDC_EDIT_FILE1, m_edt_file[0]);
	DDX_Control(pDX, IDC_EDIT_FILE2, m_edt_file[1]);
	DDX_Control(pDX, IDC_EDIT_FILE3, m_edt_file[2]);
	DDX_Control(pDX, IDC_EDIT_FILE4, m_edt_file[3]);
	DDX_Control(pDX, IDC_EDIT_FILE5, m_edt_file[4]);
	DDX_Control(pDX, IDC_EDIT_FILE6, m_edt_file[5]);
	DDX_Control(pDX, IDC_EDIT_FILE7, m_edt_file[6]);
	DDX_Control(pDX, IDC_EDIT_FILE8, m_edt_file[7]);
	DDX_Control(pDX, IDC_EDIT_FILE9, m_edt_file[8]);
	DDX_Control(pDX, IDC_EDIT_FILE10, m_edt_file[9]);
	DDX_Control(pDX, IDC_EDIT_FILE11, m_edt_file[10]);
	DDX_Control(pDX, IDC_EDIT_FILE12, m_edt_file[11]);
	DDX_Control(pDX, IDC_EDIT_FILE13, m_edt_file[12]);
	DDX_Control(pDX, IDC_EDIT_FILE14, m_edt_file[13]);
	DDX_Control(pDX, IDC_EDIT_FILE15, m_edt_file[14]);
	DDX_Control(pDX, IDC_EDIT_FILE16, m_edt_file[15]);
	DDX_Control(pDX, IDC_EDIT_FILE17, m_edt_file[16]);
	DDX_Control(pDX, IDC_EDIT_FILE18, m_edt_file[17]);
	DDX_Control(pDX, IDC_EDIT_FILE19, m_edt_file[18]);
	DDX_Control(pDX, IDC_EDIT_FILE20, m_edt_file[19]);
	DDX_Control(pDX, IDC_EDIT_FILE21, m_edt_file[20]);
	DDX_Control(pDX, IDC_EDIT_FILE22, m_edt_file[21]);
	DDX_Control(pDX, IDC_EDIT_FILE23, m_edt_file[22]);
	DDX_Control(pDX, IDC_EDIT_FILE24, m_edt_file[23]);
	DDX_Control(pDX, IDC_CHECK_PLAY_FILE, m_chk_is_play_file);
	DDX_Slider(pDX, IDC_SLIDER1, m_s32_volume);
	DDX_Control(pDX, IDC_STATIC19, m_stcVolume);
}

BEGIN_MESSAGE_MAP(CCCTDlg, CDialog)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	//}}AFX_MSG_MAP
	ON_BN_CLICKED(IDC_BUTTON_TEST, &CCCTDlg::OnBnClickedButtonTest)
//	ON_BN_CLICKED(IDC_BUTTON_STOP, &CCCTDlg::OnBnClickedButtonStop)
	ON_BN_CLICKED(IDC_CHECK1, &CCCTDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_CHECK2, &CCCTDlg::OnBnClickedCheck2)
	ON_BN_CLICKED(IDC_CHECK3, &CCCTDlg::OnBnClickedCheck3)
	ON_BN_CLICKED(IDC_CHECK4, &CCCTDlg::OnBnClickedCheck4)
	ON_BN_CLICKED(IDC_CHECK5, &CCCTDlg::OnBnClickedCheck5)
	ON_BN_CLICKED(IDC_CHECK6, &CCCTDlg::OnBnClickedCheck6)
	ON_BN_CLICKED(IDC_CHECK7, &CCCTDlg::OnBnClickedCheck7)
	ON_BN_CLICKED(IDC_CHECK8, &CCCTDlg::OnBnClickedCheck8)
	ON_BN_CLICKED(IDC_CHECK9, &CCCTDlg::OnBnClickedCheck9)
	ON_BN_CLICKED(IDC_CHECK10, &CCCTDlg::OnBnClickedCheck10)
	ON_BN_CLICKED(IDC_CHECK11, &CCCTDlg::OnBnClickedCheck11)
	ON_BN_CLICKED(IDC_CHECK12, &CCCTDlg::OnBnClickedCheck12)
	ON_BN_CLICKED(IDC_CHECK13, &CCCTDlg::OnBnClickedCheck13)
	ON_BN_CLICKED(IDC_CHECK14, &CCCTDlg::OnBnClickedCheck14)
	ON_BN_CLICKED(IDC_CHECK15, &CCCTDlg::OnBnClickedCheck15)
	ON_BN_CLICKED(IDC_CHECK_SELECT_NEAR, &CCCTDlg::OnBnClickedCheckSelectNear)
	ON_BN_CLICKED(IDC_CHECK_ALL, &CCCTDlg::OnBnClickedCheckAll)
	ON_WM_TIMER()
	ON_BN_CLICKED(IDC_BUTTON_OPEN1, &CCCTDlg::OnBnClickedButtonOpen1)
	ON_BN_CLICKED(IDC_RADIO_LIST1, &CCCTDlg::OnBnClickedRadioList1)
	ON_BN_CLICKED(IDC_CHECK_PLAY_FILE, &CCCTDlg::OnBnClickedCheckPlayFile)
	ON_BN_CLICKED(IDOK, &CCCTDlg::OnBnClickedOk)
	ON_BN_CLICKED(IDC_BUTTON_OPEN2, &CCCTDlg::OnBnClickedButtonOpen2)
	ON_BN_CLICKED(IDC_BUTTON_OPEN3, &CCCTDlg::OnBnClickedButtonOpen3)
	ON_NOTIFY(TRBN_THUMBPOSCHANGING, IDC_SLIDER1, &CCCTDlg::OnTRBNThumbPosChangingSlider1)
	ON_NOTIFY(NM_CUSTOMDRAW, IDC_SLIDER1, &CCCTDlg::OnNMCustomdrawSlider1)
END_MESSAGE_MAP()


// CCCTDlg ��Ϣ�������

BOOL CCCTDlg::OnInitDialog()
{
	CDialog::OnInitDialog();

	// ��������...���˵�����ӵ�ϵͳ�˵��С�

	// IDM_ABOUTBOX ������ϵͳ���Χ�ڡ�
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		CString strAboutMenu;
		strAboutMenu.LoadString(IDS_ABOUTBOX);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// ���ô˶Ի����ͼ�ꡣ��Ӧ�ó��������ڲ��ǶԻ���ʱ����ܽ��Զ�
	//  ִ�д˲���
	SetIcon(m_hIcon, TRUE);			// ���ô�ͼ��
	SetIcon(m_hIcon, FALSE);		// ����Сͼ��

	// TODO: �ڴ���Ӷ���ĳ�ʼ������
	m_wav_palyer.start();
	udp_client_init();
	memset(m_u8pcm_buf,0xff,34);
	m_u8pcm_buf[0] = 0x5a;
	m_u8pcm_buf[1] = 0x5a;
	SetTimer(0,1000,NULL);
	//SetTimer(2,6,NULL);
	m_dev_mon.start();
	SetWindowPos(NULL,0,0,1160,640,SWP_SHOWWINDOW);
	const int STATIC_LIST_WIDTH = 360;
	const int STATIC_LIST_HEIGHT = 300;
	const int STATIC_LIST_Y = 220;
	const int STATIC_LIST_X_GAP = 20;

	const int RADIO_BUTTON_PLAY_X_START = 50;
	const int RADIO_BUTTON_PLAY_Y = STATIC_LIST_Y+20;
	const int CHK_CYCLE_PLAY_START_X = RADIO_BUTTON_PLAY_X_START+100;
	const int CHK_CYCLE_PLAY_START_Y = RADIO_BUTTON_PLAY_Y;

	//int BTN_OPEN_START_X = STATIC_LIST_X_GAP+10;
	int BTN_OPEN_START_Y = CHK_CYCLE_PLAY_START_Y+30;
	for(int i = 0;i<3;i++)
	{
		m_stclist[i].SetWindowPos(NULL,STATIC_LIST_X_GAP+(STATIC_LIST_WIDTH+STATIC_LIST_X_GAP)*i,STATIC_LIST_Y,STATIC_LIST_WIDTH,STATIC_LIST_HEIGHT,SWP_SHOWWINDOW);
		m_btn_play[i].SetWindowPos(NULL,RADIO_BUTTON_PLAY_X_START+(STATIC_LIST_WIDTH+STATIC_LIST_X_GAP)*i,RADIO_BUTTON_PLAY_Y,64,20,SWP_SHOWWINDOW);
		//m_chk_cycle_play[i].SetWindowPos(NULL,CHK_CYCLE_PLAY_START_X+(STATIC_LIST_WIDTH+STATIC_LIST_X_GAP)*i,CHK_CYCLE_PLAY_START_Y,128,20,SWP_SHOWWINDOW);

		
		int BTN_OPEN_START_X = STATIC_LIST_X_GAP+10+(STATIC_LIST_WIDTH+STATIC_LIST_X_GAP)*i;
		for(int j=0;j<8;j++)
		{
			m_btn_open[i*8+j].SetWindowPos(NULL,BTN_OPEN_START_X,BTN_OPEN_START_Y+30*j,60,30,SWP_SHOWWINDOW);
			m_edt_file[i*8+j].SetWindowPos(NULL,BTN_OPEN_START_X+80,BTN_OPEN_START_Y+30*j,250,30,SWP_SHOWWINDOW);
		}
	}
	return TRUE;  // ���ǽ��������õ��ؼ������򷵻� TRUE
}

void CCCTDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialog::OnSysCommand(nID, lParam);
	}
}

// �����Ի��������С����ť������Ҫ����Ĵ���
//  �����Ƹ�ͼ�ꡣ����ʹ���ĵ�/��ͼģ�͵� MFC Ӧ�ó���
//  �⽫�ɿ���Զ���ɡ�

void CCCTDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ���ڻ��Ƶ��豸������

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// ʹͼ���ڹ����������о���
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// ����ͼ��
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialog::OnPaint();
	}
}

//���û��϶���С������ʱϵͳ���ô˺���ȡ�ù��
//��ʾ��
HCURSOR CCCTDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CCCTDlg::OnBnClickedButtonTest()
{
	LOGFMTT("%s",__FUNCTION__);
	if(m_chk_is_play_file.GetCheck())
	{
		return;
	}
	if(m_mic_enable)
	{
		m_mic_enable = 0;
	}
	else
	{
		m_mic_enable = 1;
	}
	
	if(m_mic_enable)
	{
		
		if(!initRecord())
		{
			m_btnMicEnable.SetWindowText(_T("��˷��Ѵ�"));
		}
	}
	else
	{
		stopRecord();
		m_btnMicEnable.SetWindowText(_T("��˷��ѹر�"));
		
	}
	// TODO: �ڴ���ӿؼ�֪ͨ����������
}

int CCCTDlg::initRecord(void)
{
	LOGFMTT("%s",__FUNCTION__);
	int cap_dev_num = waveInGetNumDevs();
	if(cap_dev_num)
	{
		LOGFMTT("cap_dev_num=%d",cap_dev_num);
	}
	else
	{
		CString str;
		str.Format(_TEXT("û���ҵ�¼���豸"));
		MessageBox(str);
		LOGFMTT("û���ҵ�¼���豸");
		return -1;  
	}
	for(int i=0;i<cap_dev_num;i++)
	{
	
	}
	
	WAVEINCAPSW caps;
	waveInGetDevCaps(WAVE_MAPPER,&caps,sizeof(WAVEINCAPSW));
	CString strfilename;
	strfilename.Format(_T("e:\\rec.snd"));
//	m_sndfile.Open(strfilename,CFile::modeCreate| CFile::modeWrite);

	m_waveform.wFormatTag = WAVE_FORMAT_PCM;//������ʽΪPCM  
	m_waveform.nSamplesPerSec =22050;// 44100;// 22050;//8000;//11025;//48000;//�����ʣ�16000��/�� 
#if PCM16
	m_waveform.wBitsPerSample = 16;//�������أ�16bits/��  
#else
	m_waveform.wBitsPerSample = 8;//�������أ�16bits/��  
#endif
	m_waveform.nChannels = 2;//������������2����  
	m_waveform.nBlockAlign = (m_waveform.wBitsPerSample/8)*2;//һ����Ĵ�С������bit���ֽ�������������  
	m_waveform.nAvgBytesPerSec =m_waveform.nSamplesPerSec * m_waveform.nBlockAlign;//ÿ��������ʣ�����ÿ���ܲɼ������ֽڵ�����  
	m_waveform.cbSize = 0;//һ��Ϊ0  
	LOGFMTI("%s, sample=%d, bits=%d, ch=%d, block=%d, bytes_per_sec=%d",__FUNCTION__, m_waveform.nSamplesPerSec,m_waveform.wBitsPerSample,m_waveform.nChannels ,m_waveform.nBlockAlign,m_waveform.nAvgBytesPerSec);
	//ʹ��waveInOpen����������Ƶ�ɼ�  
	MMRESULT mmr = waveInOpen(&m_hWaveIn,WAVE_MAPPER,&m_waveform,  
		(DWORD)(MicCallback), DWORD(this), CALLBACK_FUNCTION);  
	if(mmr != MMSYSERR_NOERROR)  
	{
		CString str;
		str.Format(_TEXT("������ʧ��:%d"),mmr);
		MessageBox(str);
		return false;  
	}
	//�����������飨������Խ���������飩����������Ƶ����  
	m_record_on = 1;
	DWORD bufsize = 640*2;  
	m_pBuffer1 = new BYTE[bufsize];  
	m_pBuffer2 = new BYTE[bufsize];  
	m_wHdr1.lpData = (LPSTR)m_pBuffer1;  
	m_wHdr1.dwBufferLength = bufsize;  
	m_wHdr1.dwBytesRecorded = 0;  
	m_wHdr1.dwUser = 0;  
	m_wHdr1.dwFlags = 0;  
	m_wHdr1.dwLoops = 1;  
	m_wHdr1.lpNext = NULL;  
	m_wHdr1.reserved = 0;  
	//�������õ�m_wHdr1��Ϊ����  
	waveInPrepareHeader(m_hWaveIn,&m_wHdr1,sizeof(WAVEHDR));  
	m_wHdr2.lpData = (LPSTR)m_pBuffer2;  
	m_wHdr2.dwBufferLength = bufsize;  
	m_wHdr2.dwBytesRecorded = 0;  
	m_wHdr2.dwUser = 0;  
	m_wHdr2.dwFlags = 0;  
	m_wHdr2.dwLoops = 1;  
	m_wHdr2.lpNext = NULL;  
	m_wHdr2.reserved = 0;  
	//�������õ�m_wHdr2��Ϊ����  
	waveInPrepareHeader(m_hWaveIn,&m_wHdr2,sizeof(WAVEHDR));  
	//������wHdr��ӵ�waveIn��ȥ  
	waveInAddBuffer (m_hWaveIn, &m_wHdr1, sizeof (WAVEHDR)) ;  
	waveInAddBuffer (m_hWaveIn, &m_wHdr2, sizeof (WAVEHDR)) ;  
	//��ʼ��Ƶ�ɼ�  
	waveInStart(m_hWaveIn);  
	return 0;
}


//���������callback���������ڲɼ�������Ƶ���ݶ�����������д���  

DWORD CALLBACK  
CCCTDlg::MicCallback(HWAVEIN hwavein, UINT uMsg, DWORD dwInstance, DWORD dwParam1, DWORD dwParam2)  
{  
	//���CIMAADPCMDlg���������Ƶ�ɼ���  
	CCCTDlg*pWnd = (CCCTDlg*)dwInstance;  
	int re(0); 
	
	int sample = 0;
	INT16 i16smaple = 0;
	UINT16 u16smaple = 0;
	switch(uMsg)   
	{  
	case WIM_OPEN:  
		LOGFMTT("WIM_OPEN");
		pWnd->m_cap_cnt=0;
		break;  

	case WIM_DATA: 
		pWnd->m_cap_cnt++;
		//LOGFMTT("%d,WIM_DATA\t",GetTickCount());
		//������ǶԲɼ���������������ĵط����������˷��ʹ���  
		//((PWAVEHDR)dwParam1)->lpData����ǲɼ���������ָ��  
		//((PWAVEHDR)dwParam1)->dwBytesRecorded����ǲɼ��������ݳ���  
		//re = send(pWnd->sends,((PWAVEHDR)dwParam1)->lpData,((PWAVEHDR)dwParam1)->dwBytesRecorded,0);  
		pWnd->m_u8pcm_buf[1] = pWnd->m_u8pcm_buf[1]++;
		
		
		memcpy(pWnd->m_u8pcm_buf+34,(char*)((PWAVEHDR)dwParam1)->lpData,1280);
		
#if PCM16
		for(int i=34;i<1314;i+=4)
		{

			i16smaple = (pWnd->m_u8pcm_buf[i]) | (pWnd->m_u8pcm_buf[i+1]<<8);
			sample = i16smaple+32768;
			sample = sample*pWnd->m_s32_volume/100;
			u16smaple = sample;
		//	u16smaple = u16smaple>>4;
			pWnd->m_u8pcm_buf[i] = u16smaple&0x00ff;
			pWnd->m_u8pcm_buf[i+1] = (u16smaple>>8);//&0xf0;
			pWnd->m_u8pcm_buf[i+2] = pWnd->m_u8pcm_buf[i];
			pWnd->m_u8pcm_buf[i+3] = pWnd->m_u8pcm_buf[i+1];
			//pWnd->m_u8pcm_buf[i] = pWnd->m_u8pcm_buf[i]>>4;
		}
		//memset(pWnd->m_u8pcm_buf+34,0x00,1280);
		
#else
	/*	for(int i=34;i<1314;i+=2)
		{
			pWnd->m_u8pcm_buf[i+1] = pWnd->m_u8pcm_buf[i];
		}*/
#endif
		//pWnd->m_sndfile.Write(pWnd->m_u8pcm_buf+34,1280);
		if (sendto(pWnd->m_sock,
				(const char*)pWnd->m_u8pcm_buf,
				1314,0,
				(struct sockaddr*)&pWnd->m_addr_remote,
				sizeof(pWnd->m_addr_remote))!=SOCKET_ERROR)
		{
		}
		//memcpy(pWnd->m_u8pcm_buf_copy,pWnd->m_u8pcm_buf,1314);
		if(pWnd->m_cap_cnt%320==0)
			LOGFMTT("%d,cap len=%d",GetTickCount(),((PWAVEHDR)dwParam1)->dwBytesRecorded);
		//pWnd->SetTimer(2,3,NULL);
		
		//��������֮��Ҫ�ٰ������������ӻ�ȥ  
		//pWnd->win�����Ƿ�����ɼ�����Ϊ��ֹͣ�ɼ���ʱ��ֻ�е����е�  
		//�������鶼�ڳ���֮�����close��������Ҫֹͣ�ɼ�ʱ�Ͳ�Ҫ��waveInAddBuffer��  
		if(pWnd->m_record_on)  
			waveInAddBuffer (hwavein, (PWAVEHDR) dwParam1, sizeof (WAVEHDR)) ;  
		//LOGFMTT("%d",re);  
		break;  

	case WIM_CLOSE:  
		LOGFMTT("WIM_CLOSE");  
	/*	pWnd->m_sndfile.Flush();
		pWnd->m_sndfile.Close();*/
		break;  
	default:  
		break;  
	}  
	return 0;  
}  
int CCCTDlg::stopRecord(void)
{
	LOGFMTT("%s",__FUNCTION__);
	m_record_on = 0;
	if(m_hWaveIn)
	{
		waveInStop(m_hWaveIn);
		waveInReset(m_hWaveIn);
		int ret = waveInClose(m_hWaveIn);
		if(!ret)
			LOGFMTT("wav in close ok");
		else
			LOGFMTI("wav in close err:%d",ret);
	}
	else
	{
		LOGFMTT("m_hWavaIn is null");
	}
	return 0;
}

void CCCTDlg::OnBnClickedButtonStop()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	LOGFMTT("%s",__FUNCTION__);
	stopRecord();
}

int CCCTDlg::udp_client_init(void)
{
	LOGFMTT("%s",__FUNCTION__);
	m_sock = socket(AF_INET,SOCK_DGRAM,0); 
	
	// set rcv timeout
	int nTvlen=20;  //1s
	setsockopt(m_sock,SOL_SOCKET,SO_RCVTIMEO,(const char*)&nTvlen, sizeof(nTvlen));
	
	int sock_len =sizeof(m_addr_remote);
	m_addr_remote.sin_family=AF_INET;
	m_addr_remote.sin_port=htons(1200); ///server�ļ����˿�
	m_addr_remote.sin_addr.s_addr=inet_addr("192.168.22.255"); ///server�ĵ�ַ 

	return 0;
}

unsigned char bitclr(unsigned char num,unsigned char bit) /*���ĳһλ*/
{
	unsigned char bit_value[]={1,2,4,8,16,32,64,128};
	return num&~bit_value[bit];
}


unsigned char bitset(unsigned char num,unsigned char bit) /*����ĳһλ*/
{
	unsigned char bit_value[]={1,2,4,8,16,32,64,128};
	return num|bit_value[bit];
}
int CCCTDlg::set_speaker(int speaker, int onoff)
{
	LOGFMTT("%s, spk=%d, onoff=%d",__FUNCTION__, speaker, onoff);
	int addr = speaker/8+2;
	int bit  = speaker%8;
	if(onoff)
		m_u8pcm_buf[addr] =  bitset(m_u8pcm_buf[addr],bit);
	else
		m_u8pcm_buf[addr] =  bitclr(m_u8pcm_buf[addr],bit);
	return 0;
}

void CCCTDlg::OnBnClickedCheck1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(1);
	LOGFMTT("spk1 %d",m_spk1);
	set_speaker(1,m_spk1);
	if(m_bselect_near&& m_spk1)
	{
		set_speaker(0,1);
		set_speaker(2,1);
		//m_spk0 = 1;
		m_spk2 = 1;
		UpdateData(0);
	}
}

void CCCTDlg::OnBnClickedCheck2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData(1);
	LOGFMTT("%s %d",__FUNCTION__, m_spk2);
	set_speaker(2,m_spk2);
	if(m_bselect_near&& m_spk2)
	{
		set_speaker(1,1);
		set_speaker(3,1);
		m_spk1 = 1;
		m_spk3 = 1;
		UpdateData(0);
	}
}

void CCCTDlg::OnBnClickedCheck3()
{
	UpdateData(1);
	LOGFMTT("%s %d",__FUNCTION__, m_spk3);
	set_speaker(3,m_spk3);
	if(m_bselect_near&& m_spk3)
	{
		set_speaker(2,1);
		set_speaker(4,1);
		m_spk2 = 1;
		m_spk4 = 1;
		UpdateData(0);
	}
}

void CCCTDlg::OnBnClickedCheck4()
{
	UpdateData(1);
	LOGFMTT("%s %d",__FUNCTION__, m_spk4);
	set_speaker(4,m_spk4);
	if(m_bselect_near&& m_spk4)
	{
		set_speaker(3,1);
		set_speaker(5,1);
		m_spk3 = 1;
		m_spk5 = 1;
		UpdateData(0);
	}
}

void CCCTDlg::OnBnClickedCheck5()
{
	UpdateData(1);
	LOGFMTT("%s %d",__FUNCTION__, m_spk5);
	set_speaker(5,m_spk5);
	if(m_bselect_near&& m_spk5)
	{
		set_speaker(4,1);
		set_speaker(6,1);
		m_spk4 = 1;
		m_spk6 = 1;
		UpdateData(0);
	}
}

void CCCTDlg::OnBnClickedCheck6()
{
	UpdateData(1);
	LOGFMTT("%s %d",__FUNCTION__, m_spk6);
	set_speaker(6,m_spk6);
	if(m_bselect_near&& m_spk6)
	{
		set_speaker(5,1);
		set_speaker(7,1);
		m_spk5 = 1;
		m_spk7 = 1;
		UpdateData(0);
	}
}

void CCCTDlg::OnBnClickedCheck7()
{
	UpdateData(1);
	LOGFMTT("%s %d",__FUNCTION__, m_spk7);
	set_speaker(7,m_spk7);
	if(m_bselect_near&& m_spk7)
	{
		set_speaker(6,1);
		set_speaker(8,1);
		m_spk6 = 1;
		m_spk8 = 1;
		UpdateData(0);
	}
}

void CCCTDlg::OnBnClickedCheck8()
{
	UpdateData(1);
	LOGFMTT("%s %d",__FUNCTION__, m_spk8);
	set_speaker(8,m_spk8);
	if(m_bselect_near&& m_spk8)
	{
		set_speaker(7,1);
		set_speaker(9,1);
		m_spk7 = 1;
		m_spk9 = 1;
		UpdateData(0);
	}
}

void CCCTDlg::OnBnClickedCheck9()
{
	UpdateData(1);
	LOGFMTT("%s %d",__FUNCTION__, m_spk9);
	set_speaker(9,m_spk9);
	if(m_bselect_near&& m_spk9)
	{
		set_speaker(8,1);
		set_speaker(10,1);
		m_spk8 = 1;
		m_spk10 = 1;
		UpdateData(0);
	}
}

void CCCTDlg::OnBnClickedCheck10()
{
	UpdateData(1);
	LOGFMTT("%s %d",__FUNCTION__, m_spk10);
	set_speaker(10,m_spk10);
	if(m_bselect_near&& m_spk10)
	{
		set_speaker(9,1);
		set_speaker(11,1);
		m_spk9 = 1;
		m_spk11 = 1;
		UpdateData(0);
	}
}

void CCCTDlg::OnBnClickedCheck11()
{
	UpdateData(1);
	LOGFMTT("%s %d",__FUNCTION__, m_spk11);
	set_speaker(11,m_spk11);
	if(m_bselect_near&& m_spk11)
	{
		set_speaker(10,1);
		set_speaker(12,1);
		m_spk10 = 1;
		m_spk12 = 1;
		UpdateData(0);
	}
}

void CCCTDlg::OnBnClickedCheck12()
{
	UpdateData(1);
	LOGFMTT("%s %d",__FUNCTION__, m_spk12);
	set_speaker(12,m_spk12);
	if(m_bselect_near&& m_spk12)
	{
		set_speaker(11,1);
		set_speaker(13,1);
		m_spk11 = 1;
		m_spk13 = 1;
		UpdateData(0);
	}
}

void CCCTDlg::OnBnClickedCheck13()
{
	UpdateData(1);
	LOGFMTT("%s %d",__FUNCTION__, m_spk13);
	set_speaker(13,m_spk13);
	if(m_bselect_near&& m_spk13)
	{
		set_speaker(12,1);
		set_speaker(14,1);
		m_spk12 = 1;
		m_spk14 = 1;
		UpdateData(0);
	}
}

void CCCTDlg::OnBnClickedCheck14()
{
	UpdateData(1);
	LOGFMTT("%s %d",__FUNCTION__, m_spk14);
	set_speaker(14,m_spk14);
	if(m_bselect_near&& m_spk14)
	{
		set_speaker(13,1);
		set_speaker(15,1);
		m_spk13 = 1;
		m_spk15 = 1;
		UpdateData(0);
	}
}

void CCCTDlg::OnBnClickedCheck15()
{
	UpdateData(1);
	LOGFMTT("%s %d",__FUNCTION__, m_spk15);
	set_speaker(15,m_spk15);
	if(m_bselect_near&& m_spk15)
	{
		set_speaker(14,1);
		set_speaker(16,1);
		m_spk14 = 1;
//		m_spk16 = 1;
		UpdateData(0);
	}
}

void CCCTDlg::OnBnClickedCheckSelectNear()
{
	UpdateData(1);
	LOGFMTT("%s %d",__FUNCTION__, m_bselect_near);
}

void CCCTDlg::OnBnClickedCheckAll()
{
	UpdateData(1);
	LOGFMTT("%s %d",__FUNCTION__, m_bselect_all);
	for(int i=1;i<255;i++)
	{
		set_speaker(i,m_bselect_all);
	}
	m_spk1 = m_bselect_all;
	m_spk2 = m_bselect_all;
	m_spk3 = m_bselect_all;
	m_spk4 = m_bselect_all;
	m_spk5 = m_bselect_all;
	m_spk6 = m_bselect_all;
	m_spk7 = m_bselect_all;
	m_spk8 = m_bselect_all;
	m_spk9 = m_bselect_all;
	m_spk10 = m_bselect_all;
	m_spk11 = m_bselect_all;
	m_spk12 = m_bselect_all;
	m_spk13 = m_bselect_all;
	m_spk14 = m_bselect_all;
	m_spk15 = m_bselect_all;
	
	UpdateData(0);
}

void CCCTDlg::OnTimer(UINT_PTR nIDEvent)
{
	// TODO: �ڴ������Ϣ�����������/�����Ĭ��ֵ
	if(nIDEvent==0)
	{
		for(int i=1;i<16;i++)
		{
			int state = m_dev_mon.get_state(i);
			if(state>0)
			{
				m_stcState[i-1].SetWindowText(_T("����"));
			}
			else
			{
				m_stcState[i-1].SetWindowText(_T("�Ͽ�"));
			}
		}	
	}
	CDialog::OnTimer(nIDEvent);
}

void CCCTDlg::OnBnClickedButtonOpen1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR szFilter[] = _T("��Ƶ�ļ�(*.MP3)|*.MP3|�����ļ�(*.*)|*.*||");  
	CFileDialog fd(TRUE, _T("mp3"), NULL, 0, szFilter, this);
	fd.m_ofn.lpstrInitialDir= _T("."); //ָ���ļ���     
	CString strFilePath;
	if (IDOK == fd.DoModal())   
	{   
		strFilePath = fd.GetPathName();
		m_edt_file[0].SetWindowText(strFilePath);
		CString cmd;
		cmd.Format(_T("ffmpeg.exe -i \"%s\" -f s16le -ac 1 -ar 22050 1.cache -y"),strFilePath,fd.GetFileTitle());
		char tmp[1024];
		WideCharToMultiByte(CP_UTF8,0,cmd.GetBuffer(),-1,tmp,1024,0,0);
		WinExec(tmp,SW_HIDE);
		cmd = "./1.cache";
		CFile file(cmd,CFile::modeRead);//����CFile����   
		m_pcm_file_len[0] = file.GetLength();
		m_p_pcm_file_buf[0] = (unsigned char*)malloc(m_pcm_file_len[0]);
		memset(m_p_pcm_file_buf[0],0,m_pcm_file_len[0]);//��ʼ��FileContent   
		file.Read(m_p_pcm_file_buf[0],m_pcm_file_len[0]);//��������   
		file.Close();//�ر��ļ�����   
		
	}   

}

int file_index_start=0;
int file_index_end=8;
void CCCTDlg::OnBnClickedRadioList1()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	m_current_playlist = 0;
	m_offset = 0;
	if(file_index>7)
		file_index = 0;
	file_index_start = 0;
	file_index_end = 8;
}
VOID CALLBACK TimerRoutine(PVOID lpParam, BOOLEAN TimerOrWaitFired) ;
void CCCTDlg::OnBnClickedCheckPlayFile()
{
	if(m_chk_is_play_file.GetCheck())
	{
		stopRecord();
		m_btnMicEnable.SetWindowText(_T("��˷��ѹر�"));
		htimer_queue = CreateTimerQueue();
		if(NULL==htimer_queue)
		{
			LOGFMTT("CreateTimerQueue failed (%d)\n", GetLastError());  
		}
		// Set a timer to call the timer routine in 10 seconds.
	
		if (!CreateTimerQueueTimer( &hplay_pcm_timer, htimer_queue,   
			(WAITORTIMERCALLBACK)TimerRoutine, this , 3000, 14, 0))  //����һ��TimerQueueTimer  
		{  
			LOGFMTT("CreateTimerQueueTimer failed (%d)\n", GetLastError());  
		}  
	}
	else
	{
		DeleteTimerQueue(htimer_queue);  
		LOGFMTT("DeleteTimerQueue");
	}
}

int timer_period = 14;

VOID CALLBACK TimerRoutine(PVOID lpParam, BOOLEAN TimerOrWaitFired)  
{  
	int sample = 0;
	INT16 i16smaple = 0;
	UINT16 u16smaple = 0;
	if (lpParam == NULL)  
	{  
		LOGFMTT("TimerRoutine lpParam is NULL");  
		
	}  
	else  
	{  
		// lpParam points to the argument; in this case it is an int  

		//LOGFMTT("Timer routine called. Parameter is %d.",   	*(int*)lpParam);  
		CCCTDlg*pWnd = (CCCTDlg*)lpParam; 
		if(timer_period==14)
			timer_period = 15;
		else
			timer_period = 14;
		if(!ChangeTimerQueueTimer(pWnd->htimer_queue,pWnd->hplay_pcm_timer,timer_period,timer_period))
		{
			LOGFMTT("ChangeTimerQueueTimer err:%d", GetLastError());
		}
		if(pWnd->m_pcm_file_len[pWnd->file_index])
		{
			if(pWnd->m_offset+640>pWnd->m_pcm_file_len[pWnd->file_index])
			{
				pWnd->m_offset = 0;
				LOGFMTT("file[%d] play stop",pWnd->file_index);
				for (int i=file_index_start;i<file_index_end;i++)
				{
					if(++pWnd->file_index>=file_index_end)
					{
						pWnd->file_index = file_index_start;
					}
					if(pWnd->m_pcm_file_len[pWnd->file_index])
					{
						LOGFMTT("play file change to  %d",pWnd->file_index);
						break;
					}
				/*	else
					{
						file_index = 0;
					}*/
				}			
			}
		}
		else
		{
			if(++pWnd->file_index>=file_index_end)
			{
				pWnd->file_index = file_index_start;
			}
			return;

		}
		
		
		pWnd->m_cap_cnt++;
		pWnd->m_u8pcm_buf[1] = pWnd->m_u8pcm_buf[1]++;
		//memcpy(pWnd->m_u8pcm_buf+34,(char*)(pWnd->m_p_pcm_file_buf[file_index]+m_offset),1280);
		// mono to stretro
		unsigned char* pbuf = pWnd->m_p_pcm_file_buf[pWnd->file_index]+pWnd->m_offset;
		int mono_index = 0;
#if 1
		for(int i=34;i<1314;i+=4)
		{
			//i16smaple = (pWnd->m_u8pcm_buf[i]) | (pWnd->m_u8pcm_buf[i+1]<<8);
			i16smaple = (pbuf[mono_index] | pbuf[mono_index+1]<<8);
			sample = i16smaple+32768;
			sample = sample*pWnd->m_s32_volume/100;
			u16smaple = sample;
			
			//u16smaple = u16smaple>>4;
			pWnd->m_u8pcm_buf[i] =	u16smaple&0x00ff;
			pWnd->m_u8pcm_buf[i+1] = (u16smaple>>8);//&0xf0;
			pWnd->m_u8pcm_buf[i+2] = pWnd->m_u8pcm_buf[i];
			pWnd->m_u8pcm_buf[i+3] = pWnd->m_u8pcm_buf[i+1];
			//pWnd->m_u8pcm_buf[i] = pWnd->m_u8pcm_buf[i]>>4;
			mono_index += 2;
		}
#else
		memcpy(pWnd->m_u8pcm_buf+34,(char*)(pbuf),1280);
#endif
		pWnd->m_offset += 640;
		//pWnd->m_sndfile.Write(pWnd->m_u8pcm_buf+34,1280);
		if (sendto(pWnd->m_sock,
			(const char*)pWnd->m_u8pcm_buf,
			1314,0,
			(struct sockaddr*)&pWnd->m_addr_remote,
			sizeof(pWnd->m_addr_remote))!=SOCKET_ERROR)
		{
		}
	}  


}  
void CCCTDlg::OnBnClickedOk()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	if(htimer_queue)
		DeleteTimerQueue(htimer_queue);  
	OnOK();
}

void CCCTDlg::OnBnClickedButtonOpen2()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR szFilter[] = _T("��Ƶ�ļ�(*.MP3)|*.MP3|�����ļ�(*.*)|*.*||");  
	CFileDialog fd(TRUE, _T("mp3"), NULL, 0, szFilter, this);
	fd.m_ofn.lpstrInitialDir= _T("."); //ָ���ļ���     
	CString strFilePath;
	if (IDOK == fd.DoModal())   
	{   
		strFilePath = fd.GetPathName();
		m_edt_file[1].SetWindowText(strFilePath);
		CString cmd;
		cmd.Format(_T("ffmpeg.exe -i \"%s\" -f s16le -ac 1 -ar 22050 2.cache -y"),strFilePath,fd.GetFileTitle());
		char tmp[1024];
		WideCharToMultiByte(CP_UTF8,0,cmd.GetBuffer(),-1,tmp,1024,0,0);
		WinExec(tmp,SW_HIDE);
		cmd = "./2.cache";
		CFile file(cmd,CFile::modeRead);//����CFile����   
		m_pcm_file_len[1] = file.GetLength();
		m_p_pcm_file_buf[1] = (unsigned char*)malloc(m_pcm_file_len[1]);
		memset(m_p_pcm_file_buf[1],0,m_pcm_file_len[1]);//��ʼ��FileContent   
		file.Read(m_p_pcm_file_buf[1],m_pcm_file_len[1]);//��������   
		file.Close();//�ر��ļ�����   

	}   

}

void CCCTDlg::OnBnClickedButtonOpen3()
{
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	TCHAR szFilter[] = _T("��Ƶ�ļ�(*.MP3)|*.MP3|�����ļ�(*.*)|*.*||");  
	CFileDialog fd(TRUE, _T("mp3"), NULL, 0, szFilter, this);
	fd.m_ofn.lpstrInitialDir= _T("."); //ָ���ļ���     
	CString strFilePath;
	if (IDOK == fd.DoModal())   
	{   
		strFilePath = fd.GetPathName();
		m_edt_file[2].SetWindowText(strFilePath);
		CString cmd;
		cmd.Format(_T("ffmpeg.exe -i \"%s\" -f s16le -ac 1 -ar 22050 3.cache -y"),strFilePath,fd.GetFileTitle());
		char tmp[1024];
		WideCharToMultiByte(CP_UTF8,0,cmd.GetBuffer(),-1,tmp,1024,0,0);
		WinExec(tmp,SW_HIDE);
		cmd = "./3.cache";
		CFile file(cmd,CFile::modeRead);//����CFile����   
		m_pcm_file_len[2] = file.GetLength();
		m_p_pcm_file_buf[2] = (unsigned char*)malloc(m_pcm_file_len[2]);
		memset(m_p_pcm_file_buf[2],0,m_pcm_file_len[2]);//��ʼ��FileContent   
		file.Read(m_p_pcm_file_buf[2],m_pcm_file_len[2]);//��������   
		file.Close();//�ر��ļ�����   

	}   

}

void CCCTDlg::OnTRBNThumbPosChangingSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	// �˹���Ҫ�� Windows Vista ����߰汾��
	// _WIN32_WINNT ���ű��� >= 0x0600��
	NMTRBTHUMBPOSCHANGING *pNMTPC = reinterpret_cast<NMTRBTHUMBPOSCHANGING *>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	*pResult = 0;
}

void CCCTDlg::OnNMCustomdrawSlider1(NMHDR *pNMHDR, LRESULT *pResult)
{
	LPNMCUSTOMDRAW pNMCD = reinterpret_cast<LPNMCUSTOMDRAW>(pNMHDR);
	// TODO: �ڴ���ӿؼ�֪ͨ����������
	UpdateData();
	CString str;
	str.Format(_T("����:%d"),m_s32_volume);
	m_stcVolume.SetWindowText(str);
	LOGFMTT("m_s32_volume=%d",m_s32_volume);
	*pResult = 0;
}
