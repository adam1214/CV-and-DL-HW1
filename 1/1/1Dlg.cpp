
// 1Dlg.cpp : 實作檔
//

#include "stdafx.h"
#include "1.h"
#include "1Dlg.h"
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


// 對 App About 使用 CAboutDlg 對話方塊

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 對話方塊資料
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支援

// 程式碼實作
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


// CMy1Dlg 對話方塊



CMy1Dlg::CMy1Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY1_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy1Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy1Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy1Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy1Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy1Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMy1Dlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CMy1Dlg 訊息處理常式

BOOL CMy1Dlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 將 [關於...] 功能表加入系統功能表。

	// IDM_ABOUTBOX 必須在系統命令範圍之中。
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

	// 設定此對話方塊的圖示。當應用程式的主視窗不是對話方塊時，
	// 框架會自動從事此作業
	SetIcon(m_hIcon, TRUE);			// 設定大圖示
	SetIcon(m_hIcon, FALSE);		// 設定小圖示

	// TODO: 在此加入額外的初始設定

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CMy1Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果將最小化按鈕加入您的對話方塊，您需要下列的程式碼，
// 以便繪製圖示。對於使用文件/檢視模式的 MFC 應用程式，
// 框架會自動完成此作業。

void CMy1Dlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 繪製的裝置內容

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 將圖示置中於用戶端矩形
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 描繪圖示
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// 當使用者拖曳最小化視窗時，
// 系統呼叫這個功能取得游標顯示。
HCURSOR CMy1Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CMy1Dlg::OnBnClickedButton1()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	// Create some windows to show the input and output images in.
	cvNamedWindow("1 - in");
	// Create a window to show our input image
	IplImage* image = cvLoadImage("images/dog.bmp");
	cvShowImage("1 - in", image);
	printf("Height = %d\n", cvGetSize(image).height);
	printf("Width = %d\n", cvGetSize(image).width);
	// Wait for the user to hit a key, then clean up the windows
	cvWaitKey(0);
	cvDestroyWindow("1 - in");
	fclose(stdout);
}


void CMy1Dlg::OnBnClickedButton2()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	IplImage* image = cvLoadImage("images/color.png", 1);

	cvShowImage("2 - in", image);
	// Wait for the user to hit a key, then clean up the windows
	Mat img = imread("images/color.png");
	Mat channel[3];
	split(img, channel);
	Mat channel_copy[3];
	for (int i = 0; i <= 2; i++)
	{
		channel_copy[i] = channel[i];
	}
	channel[0] = channel_copy[1]; //新的B從原本G位置變來
	channel[1] = channel_copy[2]; //新的G從原本R位置變來
	channel[2] = channel_copy[0]; //新的R從原本B位置變來

	merge(channel, 3, img);
	imshow("BGR->RGB", img);

	cvWaitKey(0);
	cvDestroyWindow("2 - in");
	cvDestroyWindow("BGR->RGB");
}


void CMy1Dlg::OnBnClickedButton3()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	Mat src1, src2;
	src1 = imread("images/dog.bmp");
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	imshow("Original Image", src1);
	flip(src1, src2, 1);
	namedWindow("Flip-y-axis", CV_WINDOW_AUTOSIZE);
	imshow("Flip-y-axis", src2);
	cvWaitKey(0);
	cvDestroyWindow("Original Image");
	cvDestroyWindow("Flip-y-axis");
}

const int alpha_slider_max = 100;
Mat mix1, mix2, mixed;

void on_trackbar(int position, void* callback)
{
	double alpha = (double)position / alpha_slider_max;
	double beta;
	beta = 1 - alpha;
	addWeighted(mix1, alpha, mix2, beta, 0.0, mixed);
	imshow("Linear Blend", mixed);
}
void CMy1Dlg::OnBnClickedButton4()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	mix1 = imread("images/dog.bmp");
	flip(mix1, mix2, 1);
	namedWindow("Linear Blend", 1);
	// Initialize values
	int alpha_slider = 0;
	createTrackbar("Alpha", "Linear Blend", &alpha_slider, alpha_slider_max, on_trackbar);
	on_trackbar(0, 0);
	waitKey(0);
	cvDestroyWindow("Linear Blend");
}

