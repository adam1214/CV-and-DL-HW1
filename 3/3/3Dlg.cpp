
// 3Dlg.cpp : ��@��
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


// CMy3Dlg ��ܤ��



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


// CMy3Dlg �T���B�z�`��

BOOL CMy3Dlg::OnInitDialog()
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

// �p�G�N�̤p�ƫ��s�[�J�z����ܤ���A�z�ݭn�U�C���{���X�A
// �H�Kø�s�ϥܡC���ϥΤ��/�˵��Ҧ��� MFC ���ε{���A
// �ج[�|�۰ʧ������@�~�C

void CMy3Dlg::OnPaint()
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
	// TODO: �b���[�J����i���B�z�`���{���X
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
	if (EVENT == CV_EVENT_LBUTTONDOWN && click_cnt == 0) //���W
	{
		click_cnt++;
		circle(*img, pt, 30, Scalar(0, 0, 255), CV_FILLED, 50, 0);//����  			
		imshow("org.", *img);
		srcQuad[0].x = x;	//src Top left
		srcQuad[0].y = y;
		dstQuad[0].x = 20; //dst Top left
		dstQuad[0].y = 20;
	}
	else if (EVENT == CV_EVENT_LBUTTONDOWN && click_cnt == 1) //�k�W
	{
		click_cnt++;
		circle(*img, pt, 30, Scalar(0, 0, 255), CV_FILLED, 50, 0);//����  			
		imshow("org.", *img);
		srcQuad[1].x = x;	//src Top right
		srcQuad[1].y = y;
		dstQuad[1].x = 450; //dst Top right
		dstQuad[1].y = 20;
	}
	else if (EVENT == CV_EVENT_LBUTTONDOWN && click_cnt == 2) //�k�U
	{
		click_cnt++;
		circle(*img, pt, 30, Scalar(0, 0, 255), CV_FILLED, 50, 0);//����  			
		imshow("org.", *img);
		srcQuad[3].x = x;	//src Bot right
		srcQuad[3].y = y;
		dstQuad[3].x = 450; //dst Bot right
		dstQuad[3].y = 450;
	}
	else if (EVENT == CV_EVENT_LBUTTONDOWN && click_cnt == 3) //���U
	{
		click_cnt++;
		circle(*img, pt, 30, Scalar(0, 0, 255), CV_FILLED, 50, 0);//����  			
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
	// TODO: �b���[�J����i���B�z�`���{���X
	//click_cnt = 0;
	//AllocConsole();
	//freopen("CONOUT$", "w", stdout);

	src_2 = cvLoadImage("images/OriginalPerspective.png");
	cvNamedWindow("org.", 1);
	cvShowImage("org.", src_2);
	Mat mat = cvarrToMat(src_2);
	setMouseCallback("org.", on_mouse, (&mat)); //�I�s�^���禡 

	dst_2 = cvCloneImage(src_2);
	dst_2->origin = src_2->origin;
	cvZero(dst_2);

	cvWaitKey();
	cvDestroyWindow("org.");
	cvDestroyWindow("Perspective_Warp");
}


void CMy3Dlg::OnEnChangeEdit1() //Angle
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialogEx::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X
	CString text;
	GetDlgItem(IDC_EDIT1)->GetWindowText(text); //Ū��
	double angle = _wtof(text);
	printf("angle=%f\n", angle);
	Point2f center(130, 125);	//���w���त��
	Mat rot_mat = getRotationMatrix2D(center, angle, 1.0);	//�������x�}
	warpAffine(dst, dst, rot_mat, dst_sz);	//�ھڱ���x�}�i���g�ܴ�
	imshow("Adaptive Image", dst);	//��ܱ���ĪG
}


void CMy3Dlg::OnEnChangeEdit2() //scale
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialogEx::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X
	CString text;
	GetDlgItem(IDC_EDIT2)->GetWindowText(text); //Ū��
	double scale = _wtof(text);
	printf("scale=%f\n", scale);
	if (scale != 0)
	{
		//�w�q�Y��x�}
		Mat t_mat = Mat::zeros(2, 3, CV_32FC1);
		t_mat.at<float>(0, 0) = scale;
		t_mat.at<float>(1, 1) = scale;
		//|  1 0 Tx |
		//|  0 1 Ty |
		warpAffine(dst, dst, t_mat, src_sz);
		imshow("Adaptive Image", dst);	//����Y��ĪG
	}
}


void CMy3Dlg::OnEnChangeEdit3() //Tx
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialogEx::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X

	CString text;
	GetDlgItem(IDC_EDIT3)->GetWindowText(text); //Ū��
	int Tx = _wtoi(text);
	printf("Tx=%d\n", Tx);
	//�w�q�����x�}
	Mat t_mat = Mat::zeros(2, 3, CV_32FC1);
	t_mat.at<float>(0, 0) = 1;
	t_mat.at<float>(0, 2) = Tx; //���������q 
	t_mat.at<float>(1, 1) = 1;
	//|  1 0 Tx |
	//|  0 1 Ty |
	warpAffine(dst, dst, t_mat, src_sz);
	imshow("Adaptive Image", dst);	//��ܱ���ĪG
}


void CMy3Dlg::OnEnChangeEdit4() //Ty
{
	// TODO:  �p�G�o�O RICHEDIT ����A����N���|
	// �ǰe���i���A���D�z�мg CDialogEx::OnInitDialog()
	// �禡�M�I�s CRichEditCtrl().SetEventMask()
	// ���㦳 ENM_CHANGE �X�� ORed �[�J�B�n�C

	// TODO:  �b���[�J����i���B�z�`���{���X
	CString text;
	GetDlgItem(IDC_EDIT4)->GetWindowText(text); //Ū��
	int Ty = _wtoi(text);
	printf("Ty=%d\n", Ty);
	//�w�q�����x�}
	Mat t_mat = Mat::zeros(2, 3, CV_32FC1);
	t_mat.at<float>(0, 0) = 1;
	t_mat.at<float>(1, 2) = Ty; //���������q 
	t_mat.at<float>(1, 1) = 1;
	//|  1 0 Tx |
	//|  0 1 Ty |
	warpAffine(dst, dst, t_mat, src_sz);
	imshow("Adaptive Image", dst);	//��ܱ���ĪG
}
