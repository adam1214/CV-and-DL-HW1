
// 2Dlg.cpp : ��@��
//

#include "stdafx.h"
#include "2.h"
#include "2Dlg.h"
#include "afxdialogex.h"
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

using namespace cv;
using namespace std;

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// �� App About �ϥ� CAboutDlg ��ܤ��

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ��ܤ�����
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV �䴩

// �{���X��@
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CMy2Dlg ��ܤ��



CMy2Dlg::CMy2Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY2_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy2Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy2Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy2Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy2Dlg::OnBnClickedButton2)
END_MESSAGE_MAP()


// CMy2Dlg �T���B�z�`��

BOOL CMy2Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// �N [����...] �\���[�J�t�Υ\���C

	// IDM_ABOUTBOX �����b�t�ΩR�O�d�򤧤��C
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != NULL)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// �]�w����ܤ�����ϥܡC�����ε{�����D�������O��ܤ���ɡA
	// �ج[�|�۰ʱq�Ʀ��@�~
	SetIcon(m_hIcon, TRUE);			// �]�w�j�ϥ�
	SetIcon(m_hIcon, FALSE);		// �]�w�p�ϥ�

	// TODO: �b���[�J�B�~����l�]�w

	return TRUE;  // �Ǧ^ TRUE�A���D�z�ﱱ��]�w�J�I
}

void CMy2Dlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// �p�G�N�̤p�ƫ��s�[�J�z����ܤ���A�z�ݭn�U�C���{���X�A
// �H�Kø�s�ϥܡC���ϥΤ��/�˵��Ҧ��� MFC ���ε{���A
// �ج[�|�۰ʧ������@�~�C

void CMy2Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // ø�s���˸m���e

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// �N�ϥܸm����Τ�ݯx��
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// �yø�ϥ�
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ��ϥΪ̩즲�̤p�Ƶ����ɡA
// �t�ΩI�s�o�ӥ\����o�����ܡC
HCURSOR CMy2Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMy2Dlg::OnBnClickedButton1()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	int threshold_value = 80;
	int const max_BINARY_value = 255;
	int threshold_type = 0;

	Mat src1, src2;
	src1 = imread("images/QR.png");
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	imshow("Original Image", src1);
	threshold(src1, src2, threshold_value, max_BINARY_value, threshold_type);
	namedWindow("Adaptive Image", CV_WINDOW_AUTOSIZE);
	imshow("Adaptive Image", src2);
	cvWaitKey(0);
	cvDestroyWindow("Original Image");
	cvDestroyWindow("Adaptive Image");
}


void CMy2Dlg::OnBnClickedButton2()
{
	// TODO: �b���[�J����i���B�z�`���{���X
	int threshold_value = 80;
	double const max_BINARY_value = 255.0;
	int threshold_type = 0;
	int blockSize = 19;
	double offset = -1;

	Mat src1, src2;
	src1 = imread("images/QR.png");
	cvtColor(src1, src1, CV_BGR2GRAY);
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	imshow("Original Image", src1);
	adaptiveThreshold(src1, src2, max_BINARY_value, ADAPTIVE_THRESH_GAUSSIAN_C, threshold_type, blockSize, offset);
	namedWindow("Adaptive Image", CV_WINDOW_AUTOSIZE);
	imshow("Adaptive Image", src2);
	cvWaitKey(0);
	cvDestroyWindow("Original Image");
	cvDestroyWindow("Adaptive Image");
}
