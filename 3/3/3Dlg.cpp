
// 3Dlg.cpp : 實作檔
//

#include "stdafx.h"
#include "3.h"
#include "3Dlg.h"
#include "afxdialogex.h"
#include "opencv/cv.h"
#include "opencv/highgui.h"
#include <opencv2/opencv.hpp>
#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
#include <stdlib.h>

using namespace cv;
using namespace std;

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


// CMy3Dlg 對話方塊



CMy3Dlg::CMy3Dlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(IDD_MY3_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMy3Dlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMy3Dlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CMy3Dlg::OnBnClickedButton1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMy3Dlg::OnBnClickedButton2)
	ON_EN_CHANGE(IDC_EDIT1, &CMy3Dlg::OnEnChangeEdit1)
	ON_EN_CHANGE(IDC_EDIT2, &CMy3Dlg::OnEnChangeEdit2)
	ON_EN_CHANGE(IDC_EDIT3, &CMy3Dlg::OnEnChangeEdit3)
	ON_EN_CHANGE(IDC_EDIT4, &CMy3Dlg::OnEnChangeEdit4)
END_MESSAGE_MAP()


// CMy3Dlg 訊息處理常式

BOOL CMy3Dlg::OnInitDialog()
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

void CMy3Dlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMy3Dlg::OnPaint()
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
HCURSOR CMy3Dlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


Mat src = imread("images/OriginalTransform.png");
Mat dst = src;
Size src_sz = src.size();
Size dst_sz(src_sz.height, src_sz.width);
int len = max(src.cols, src.rows);
void CMy3Dlg::OnBnClickedButton1()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	AllocConsole();
	freopen("CONOUT$", "w", stdout);
	namedWindow("Original Image", CV_WINDOW_AUTOSIZE);
	imshow("Original Image", src);
	namedWindow("Adaptive Image", CV_WINDOW_AUTOSIZE);
	imshow("Adaptive Image", dst);
	cvWaitKey(0);
	cvDestroyWindow("Original Image");
	cvDestroyWindow("Adaptive Image");
}
int click_cnt = 0;
CvPoint2D32f srcQuad[4], dstQuad[4];
CvMat* warp_matrix = cvCreateMat(3, 3, CV_32FC1);
IplImage *src_2, *dst_2;
void on_mouse(int EVENT, int x, int y, int flags, void* ustc)
{
	//printf("click_cnt=%d\n", click_cnt);
	Point pt = Point(x, y);
	Mat *img = (Mat*)ustc;
	if (EVENT == CV_EVENT_LBUTTONDOWN && click_cnt == 0) //左上
	{
		click_cnt++;
		circle(*img, pt, 30, Scalar(0, 0, 255), CV_FILLED, 50, 0);//劃圓  			
		imshow("org.", *img);
		srcQuad[0].x = x;	//src Top left
		srcQuad[0].y = y;
		dstQuad[0].x = 20; //dst Top left
		dstQuad[0].y = 20;
	}
	else if (EVENT == CV_EVENT_LBUTTONDOWN && click_cnt == 1) //右上
	{
		click_cnt++;
		circle(*img, pt, 30, Scalar(0, 0, 255), CV_FILLED, 50, 0);//劃圓  			
		imshow("org.", *img);
		srcQuad[1].x = x;	//src Top right
		srcQuad[1].y = y;
		dstQuad[1].x = 450; //dst Top right
		dstQuad[1].y = 20;
	}
	else if (EVENT == CV_EVENT_LBUTTONDOWN && click_cnt == 2) //右下
	{
		click_cnt++;
		circle(*img, pt, 30, Scalar(0, 0, 255), CV_FILLED, 50, 0);//劃圓  			
		imshow("org.", *img);
		srcQuad[3].x = x;	//src Bot right
		srcQuad[3].y = y;
		dstQuad[3].x = 450; //dst Bot right
		dstQuad[3].y = 450;
	}
	else if (EVENT == CV_EVENT_LBUTTONDOWN && click_cnt == 3) //左下
	{
		click_cnt++;
		circle(*img, pt, 30, Scalar(0, 0, 255), CV_FILLED, 50, 0);//劃圓  			
		imshow("org.", *img);
		srcQuad[2].x = x;	//src Bot left
		srcQuad[2].y = y;
		dstQuad[2].x = 20; //dst Bot left
		dstQuad[2].y = 450;
	}
	else if (click_cnt > 3)
	{
		cvGetPerspectiveTransform(srcQuad, dstQuad, warp_matrix);
		cvWarpPerspective(src_2, dst_2, warp_matrix);
		cvNamedWindow("Perspective_Warp", 1);
		cvShowImage("Perspective_Warp", dst_2);
	}
}
void CMy3Dlg::OnBnClickedButton2()
{
	// TODO: 在此加入控制項告知處理常式程式碼
	//click_cnt = 0;
	//AllocConsole();
	//freopen("CONOUT$", "w", stdout);

	src_2 = cvLoadImage("images/OriginalPerspective.png");
	cvNamedWindow("org.", 1);
	cvShowImage("org.", src_2);
	Mat mat = cvarrToMat(src_2);
	setMouseCallback("org.", on_mouse, (&mat)); //呼叫回撥函式 

	dst_2 = cvCloneImage(src_2);
	dst_2->origin = src_2->origin;
	cvZero(dst_2);

	cvWaitKey();
	cvDestroyWindow("org.");
	cvDestroyWindow("Perspective_Warp");
}


void CMy3Dlg::OnEnChangeEdit1() //Angle
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialogEx::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

	// TODO:  在此加入控制項告知處理常式程式碼
	CString text;
	GetDlgItem(IDC_EDIT1)->GetWindowText(text); //讀取
	double angle = _wtof(text);
	printf("angle=%f\n", angle);
	Point2f center(130, 125);	//指定旋轉中心
	Mat rot_mat = getRotationMatrix2D(center, angle, 1.0);	//獲取旋轉矩陣
	warpAffine(dst, dst, rot_mat, dst_sz);	//根據旋轉矩陣進行仿射變換
	imshow("Adaptive Image", dst);	//顯示旋轉效果
}


void CMy3Dlg::OnEnChangeEdit2() //scale
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialogEx::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

	// TODO:  在此加入控制項告知處理常式程式碼
	CString text;
	GetDlgItem(IDC_EDIT2)->GetWindowText(text); //讀取
	double scale = _wtof(text);
	printf("scale=%f\n", scale);
	if (scale != 0)
	{
		//定義縮放矩陣
		Mat t_mat = Mat::zeros(2, 3, CV_32FC1);
		t_mat.at<float>(0, 0) = scale;
		t_mat.at<float>(1, 1) = scale;
		//|  1 0 Tx |
		//|  0 1 Ty |
		warpAffine(dst, dst, t_mat, src_sz);
		imshow("Adaptive Image", dst);	//顯示縮放效果
	}
}


void CMy3Dlg::OnEnChangeEdit3() //Tx
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialogEx::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

	// TODO:  在此加入控制項告知處理常式程式碼

	CString text;
	GetDlgItem(IDC_EDIT3)->GetWindowText(text); //讀取
	int Tx = _wtoi(text);
	printf("Tx=%d\n", Tx);
	//定義平移矩陣
	Mat t_mat = Mat::zeros(2, 3, CV_32FC1);
	t_mat.at<float>(0, 0) = 1;
	t_mat.at<float>(0, 2) = Tx; //水平平移量 
	t_mat.at<float>(1, 1) = 1;
	//|  1 0 Tx |
	//|  0 1 Ty |
	warpAffine(dst, dst, t_mat, src_sz);
	imshow("Adaptive Image", dst);	//顯示旋轉效果
}


void CMy3Dlg::OnEnChangeEdit4() //Ty
{
	// TODO:  如果這是 RICHEDIT 控制項，控制項將不會
	// 傳送此告知，除非您覆寫 CDialogEx::OnInitDialog()
	// 函式和呼叫 CRichEditCtrl().SetEventMask()
	// 讓具有 ENM_CHANGE 旗標 ORed 加入遮罩。

	// TODO:  在此加入控制項告知處理常式程式碼
	CString text;
	GetDlgItem(IDC_EDIT4)->GetWindowText(text); //讀取
	int Ty = _wtoi(text);
	printf("Ty=%d\n", Ty);
	//定義平移矩陣
	Mat t_mat = Mat::zeros(2, 3, CV_32FC1);
	t_mat.at<float>(0, 0) = 1;
	t_mat.at<float>(1, 2) = Ty; //垂直平移量 
	t_mat.at<float>(1, 1) = 1;
	//|  1 0 Tx |
	//|  0 1 Ty |
	warpAffine(dst, dst, t_mat, src_sz);
	imshow("Adaptive Image", dst);	//顯示旋轉效果
}
