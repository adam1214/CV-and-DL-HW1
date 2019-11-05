
// 4Dlg.cpp : 實作檔

#include "stdafx.h"
#include "4.h"
#include "4Dlg.h"
#include "afxdialogex.h"
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdlib.h>
#include <math.h>

using namespace std;
using namespace cv;
#ifdef _DEBUG
#define new DEBUG_NEW
#endif
#pragma warning( disable : 4996 ) //enable console window


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


// CMy4Dlg 對話方塊



CMy4Dlg::CMy4Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY4_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy4Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy4Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy4Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy4Dlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON3, &CMy4Dlg::OnBnClickedButton3)
	ON_BN_CLICKED(IDC_BUTTON4, &CMy4Dlg::OnBnClickedButton4)
END_MESSAGE_MAP()


// CMy4Dlg 訊息處理常式

BOOL CMy4Dlg::OnInitDialog()
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
	AllocConsole();
	freopen("CONOUT$", "w", stdout);

	return TRUE;  // 傳回 TRUE，除非您對控制項設定焦點
}

void CMy4Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy4Dlg::OnPaint()
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
HCURSOR CMy4Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}
Mat gauImage;
Mat ori_image = imread("images/School.jpg", IMREAD_COLOR);
Mat grayImage;
unsigned char Sobel_X[510 * 287] = { '0' };
unsigned char Sobel_Y[510 * 287] = { '0' };
void CMy4Dlg::OnBnClickedButton1()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	cvtColor(ori_image, grayImage, CV_BGR2GRAY);
	//namedWindow("Display window", WINDOW_AUTOSIZE);
	//imshow("Display window", ori_image);
	//namedWindow("Gray Image", WINDOW_AUTOSIZE);
	//imshow("Gray Image", grayImage);

	unsigned char* corrupted = grayImage.data;
	unsigned char smooth[510 * 287] = { '0' };

	int templates[9] = { 1, 2, 1,
		2, 4, 2,
		1, 2, 1 };
	int width = 510;
	int height = 287;
	//memcpy(smooth, corrupted, width*height * sizeof(unsigned char));
	for (int j = 1; j < height - 1; j++)
	{
		for (int i = 1; i < width - 1; i++)
		{
			int sum = 0;
			int index = 0;
			for (int m = j - 1; m < j + 2; m++)
			{
				for (int n = i - 1; n < i + 2; n++)
				{
					sum += corrupted[m*width + n] * templates[index++];
				}
			}
			sum /= 16;
			if (sum > 255)
				sum = 255;
			smooth[j*width + i] = sum;
		}
	}

	gauImage = Mat(287, 510, CV_8UC1, smooth);

	namedWindow("Gaussian smoothing filter", WINDOW_AUTOSIZE);
	imshow("Gaussian smoothing filter", gauImage);
	cvWaitKey(0);
	//cvDestroyWindow("Display window");
	//cvDestroyWindow("Gray Image");
	cvDestroyWindow("Gaussian smoothing filter");
}


void CMy4Dlg::OnBnClickedButton2()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	cvtColor(ori_image, grayImage, CV_BGR2GRAY);
	//namedWindow("Display window", WINDOW_AUTOSIZE);
	//imshow("Display window", ori_image);

	unsigned char* corrupted = grayImage.data;
	unsigned char smooth[510 * 287] = { '0' };

	int templates[9] = { 1, 2, 1,
						 2, 4, 2,
						 1, 2, 1 };
	int width = 510;
	int height = 287;
	int max, min;
	float sum_arr[510 * 287];
	for (int j = 1; j < height - 1; j++)
	{
		for (int i = 1; i < width - 1; i++)
		{
			int sum = 0;
			int index = 0;
			for (int m = j - 1; m < j + 2; m++)
			{
				for (int n = i - 1; n < i + 2; n++)
				{
					sum += corrupted[m*width + n] * templates[index++];
				}
			}
			sum /= 16;
			if (sum > 255)
			{
				sum = 255;
			}
			smooth[j*width + i] = sum;
		}
	}
	gauImage = Mat(287, 510, CV_8UC1, smooth);
	//namedWindow("Gaussian smoothing filter", WINDOW_AUTOSIZE);
	//imshow("Gaussian smoothing filter", gauImage);
	
	//unsigned char Sobel_X[510 * 287] = { '0' };
	unsigned char* gau = gauImage.data;
	int X[9] = { 1, 2, 1,
				 0, 0, 0,
				 -1, -2, -1 };
	for (int i = 0; i < 510 * 287; i++)
	{
		sum_arr[i] = 0;
	}
	for (int j = 1; j < height - 1; j++)
	{
		for (int i = 1; i < width - 1; i++)
		{
			int index = 0;
			int sum = 0;
			for (int m = j - 1; m < j + 2; m++)
			{
				for (int n = i - 1; n < i + 2; n++)
				{
					sum += gau[m*width + n] * X[index++];
				}
			}
			//sum /= 16;
			//if (sum > 255)
			//{
				//sum = 255;
			//}
			//Sobel_X[j*width + i] = sum;
			sum_arr[j*width + i] = sum;
		}
	}
	max = sum_arr[0];
	min = sum_arr[0];

	for (int a = 1; a < 287 * 510; a++) 
	{
		if (sum_arr[a] < min) //find min
		{
			min = sum_arr[a];
		}
		if (sum_arr[a] > max) //find max
		{
			max = sum_arr[a];
		}
	}
	printf("max=%d\n", max);
	printf("min=%d\n", min);
	for (int a = 0; a < 287 * 510; a++) //Normalize
	{
		sum_arr[a] = ((sum_arr[a] - min) / (max - min)) * 255;
		Sobel_X[a] = sum_arr[a];
	}
	Mat SobelX = Mat(287, 510, CV_8UC1, Sobel_X);
	namedWindow("Sobel_X", WINDOW_AUTOSIZE);
	imshow("Sobel_X", SobelX);
	
	cvWaitKey(0);
	cvDestroyWindow("Sobel_X");
	//cvDestroyWindow("Display window");
	//cvDestroyWindow("Gaussian smoothing filter");
}


void CMy4Dlg::OnBnClickedButton3()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	cvtColor(ori_image, grayImage, CV_BGR2GRAY);
	//namedWindow("Display window", WINDOW_AUTOSIZE);
	//imshow("Display window", ori_image);

	unsigned char* corrupted = grayImage.data;
	unsigned char smooth[510 * 287] = { '0' };

	int templates[9] = { 1, 2, 1,
		2, 4, 2,
		1, 2, 1 };
	int width = 510;
	int height = 287;
	int max, min;
	float sum_arr[510 * 287];
	for (int j = 1; j < height - 1; j++)
	{
		for (int i = 1; i < width - 1; i++)
		{
			int sum = 0;
			int index = 0;
			for (int m = j - 1; m < j + 2; m++)
			{
				for (int n = i - 1; n < i + 2; n++)
				{
					sum += corrupted[m*width + n] * templates[index++];
				}
			}
			sum /= 16;
			if (sum > 255)
			{
				sum = 255;
			}
			smooth[j*width + i] = sum;
		}
	}
	gauImage = Mat(287, 510, CV_8UC1, smooth);
	//namedWindow("Gaussian smoothing filter", WINDOW_AUTOSIZE);
	//imshow("Gaussian smoothing filter", gauImage);

	//unsigned char Sobel_Y[510 * 287] = { '0' };
	unsigned char* gau = gauImage.data;
	int Y[9] = { 1, 0, -1,
				 2, 0, -2,
				 1, 0, -1 };
	for (int i = 0; i < 510 * 287; i++)
	{
		sum_arr[i] = 0;
	}
	for (int j = 1; j < height - 1; j++)
	{
		for (int i = 1; i < width - 1; i++)
		{
			int index = 0;
			int sum = 0;
			for (int m = j - 1; m < j + 2; m++)
			{
				for (int n = i - 1; n < i + 2; n++)
				{
					sum += gau[m*width + n] * Y[index++];
				}
			}
			//sum /= 16;
			//if (sum > 255)
			//{
			//sum = 255;
			//}
			//Sobel_X[j*width + i] = sum;
			sum_arr[j*width + i] = sum;
		}
	}
	max = sum_arr[0];
	min = sum_arr[0];

	for (int a = 1; a < 287 * 510; a++)
	{
		if (sum_arr[a] < min) //find min
		{
			min = sum_arr[a];
		}
		if (sum_arr[a] > max) //find max
		{
			max = sum_arr[a];
		}
	}
	printf("max=%d\n", max);
	printf("min=%d\n", min);
	for (int a = 0; a < 287 * 510; a++) //Normalize
	{
		sum_arr[a] = ((sum_arr[a] - min) / (max - min)) * 255;
		Sobel_Y[a] = sum_arr[a];
	}
	Mat SobelY = Mat(287, 510, CV_8UC1, Sobel_Y);
	namedWindow("Sobel_Y", WINDOW_AUTOSIZE);
	imshow("Sobel_Y", SobelY);

	cvWaitKey(0);
	cvDestroyWindow("Sobel_Y");
	//cvDestroyWindow("Display window");
	//cvDestroyWindow("Gaussian smoothing filter");
}


void CMy4Dlg::OnBnClickedButton4()
{
	// TODO: 在此加入控制項告知處理常式程式碼

	// TODO: 在此加入控制項告知處理常式程式碼
	cvtColor(ori_image, grayImage, CV_BGR2GRAY);
	//namedWindow("Display window", WINDOW_AUTOSIZE);
	//imshow("Display window", ori_image);

	unsigned char* corrupted = grayImage.data;
	unsigned char smooth[510 * 287] = { '0' };

	int templates[9] = { 1, 2, 1,
		2, 4, 2,
		1, 2, 1 };
	int width = 510;
	int height = 287;
	int max, min;
	float sum_arr[510 * 287];
	for (int j = 1; j < height - 1; j++)
	{
		for (int i = 1; i < width - 1; i++)
		{
			int sum = 0;
			int index = 0;
			for (int m = j - 1; m < j + 2; m++)
			{
				for (int n = i - 1; n < i + 2; n++)
				{
					sum += corrupted[m*width + n] * templates[index++];
				}
			}
			sum /= 16;
			if (sum > 255)
			{
				sum = 255;
			}
			smooth[j*width + i] = sum;
		}
	}
	gauImage = Mat(287, 510, CV_8UC1, smooth);
	//namedWindow("Gaussian smoothing filter", WINDOW_AUTOSIZE);
	//imshow("Gaussian smoothing filter", gauImage);

	//unsigned char Sobel_X[510 * 287] = { '0' };
	unsigned char* gau = gauImage.data;
	int X[9] = { 1, 2, 1,
		0, 0, 0,
		-1, -2, -1 };
	for (int i = 0; i < 510 * 287; i++)
	{
		sum_arr[i] = 0;
	}
	for (int j = 1; j < height - 1; j++)
	{
		for (int i = 1; i < width - 1; i++)
		{
			int index = 0;
			int sum = 0;
			for (int m = j - 1; m < j + 2; m++)
			{
				for (int n = i - 1; n < i + 2; n++)
				{
					sum += gau[m*width + n] * X[index++];
				}
			}
			//sum /= 16;
			//if (sum > 255)
			//{
			//sum = 255;
			//}
			//Sobel_X[j*width + i] = sum;
			sum_arr[j*width + i] = sum;
		}
	}
	max = sum_arr[0];
	min = sum_arr[0];

	for (int a = 1; a < 287 * 510; a++)
	{
		if (sum_arr[a] < min) //find min
		{
			min = sum_arr[a];
		}
		if (sum_arr[a] > max) //find max
		{
			max = sum_arr[a];
		}
	}
	printf("max=%d\n", max);
	printf("min=%d\n", min);
	for (int a = 0; a < 287 * 510; a++) //Normalize
	{
		sum_arr[a] = ((sum_arr[a] - min) / (max - min)) * 255;
		Sobel_X[a] = sum_arr[a];
	}
	Mat SobelX = Mat(287, 510, CV_8UC1, Sobel_X);
	//----------------------------------------------------------
	int Y[9] = { 1, 0, -1,
		2, 0, -2,
		1, 0, -1 };
	for (int i = 0; i < 510 * 287; i++)
	{
		sum_arr[i] = 0;
	}
	for (int j = 1; j < height - 1; j++)
	{
		for (int i = 1; i < width - 1; i++)
		{
			int index = 0;
			int sum = 0;
			for (int m = j - 1; m < j + 2; m++)
			{
				for (int n = i - 1; n < i + 2; n++)
				{
					sum += gau[m*width + n] * Y[index++];
				}
			}
			//sum /= 16;
			//if (sum > 255)
			//{
			//sum = 255;
			//}
			//Sobel_X[j*width + i] = sum;
			sum_arr[j*width + i] = sum;
		}
	}
	max = sum_arr[0];
	min = sum_arr[0];

	for (int a = 1; a < 287 * 510; a++)
	{
		if (sum_arr[a] < min) //find min
		{
			min = sum_arr[a];
		}
		if (sum_arr[a] > max) //find max
		{
			max = sum_arr[a];
		}
	}
	printf("max=%d\n", max);
	printf("min=%d\n", min);
	for (int a = 0; a < 287 * 510; a++) //Normalize
	{
		sum_arr[a] = ((sum_arr[a] - min) / (max - min)) * 255;
		Sobel_Y[a] = sum_arr[a];
	}
	Mat SobelY = Mat(287, 510, CV_8UC1, Sobel_Y);

	
	unsigned char Sobel_XY[510 * 287] = { '0' };
	for (int a = 0; a < 287 * 510; a++) //Normalize
	{
		Sobel_XY[a] = sqrt(Sobel_X[a] * Sobel_X[a] + Sobel_Y[a] * Sobel_Y[a]);
	}
	Mat SobelXY = Mat(287, 510, CV_8UC1, Sobel_XY);
	namedWindow("magnitude", WINDOW_AUTOSIZE);
	imshow("magnitude", SobelXY);
	cvWaitKey(0);
	cvDestroyWindow("magnitude");
	//cvDestroyWindow("Gaussian smoothing filter");
	//cvDestroyWindow("Display window");
}
