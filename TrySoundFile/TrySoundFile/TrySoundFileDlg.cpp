
// TrySoundFileDlg.cpp : implementation file
//

#include "stdafx.h"
#include "TrySoundFile.h"
#include "TrySoundFileDlg.h"
#include "afxdialogex.h"
#include "GeneralUtilities.h"
//#include ".\SoundFile_2_2\soundfile.h"
//#include ".\SoundFile_2_2\soundfile.h"
#include ".\AudioFile\AudioFile.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CTrySoundFileDlg dialog



CTrySoundFileDlg::CTrySoundFileDlg(CWnd* pParent /*=NULL*/)
	: CDialogEx(CTrySoundFileDlg::IDD, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CTrySoundFileDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CTrySoundFileDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON1, &CTrySoundFileDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CTrySoundFileDlg message handlers

BOOL CTrySoundFileDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// Set the icon for this dialog.  The framework does this automatically
	//  when the application's main window is not a dialog
	SetIcon(m_hIcon, TRUE);			// Set big icon
	SetIcon(m_hIcon, FALSE);		// Set small icon

	// TODO: Add extra initialization here

	return TRUE;  // return TRUE  unless you set the focus to a control
}

// If you add a minimize button to your dialog, you will need the code below
//  to draw the icon.  For MFC applications using the document/view model,
//  this is automatically done for you by the framework.

void CTrySoundFileDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // device context for painting

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// Center icon in client rectangle
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// Draw the icon
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// The system calls this function to obtain the cursor to display while the user drags
//  the minimized window.
HCURSOR CTrySoundFileDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void Test1_SplitAudio(const CString & strIn)
{
	CString strOut1 = strIn, strOut2 = strIn;
	strOut1.Replace(".wav", "_1.wav");
	strOut2.Replace(".wav", "_2.wav");

	AudioFile<double> audioFile;

	bool bLoad = audioFile.load(strIn.GetString());
	if (bLoad == false)
	{
		AfxMessageBox("Failed to load input file.");
	}
	int numSamples = audioFile.getNumSamplesPerChannel();
	double lengthInSeconds = audioFile.getLengthInSeconds();

	int numChannels = audioFile.getNumChannels();
	bool isMono = audioFile.isMono();
	bool isStereo = audioFile.isStereo();


	AudioFile<double>::AudioBuffer buffer1,buffer2;
	buffer1.resize(numChannels);
	buffer2.resize(numChannels);
	int i, j;
	for (j = 0; j < numChannels; j++)
	{
		buffer1[j].resize(numSamples / 2);
		buffer2[j].resize(numSamples / 2);
	}

	for (i = 0; i < numSamples / 2; i++)
	{
		for (j = 0; j < numChannels; j++)
		{
			buffer1[j][i] = audioFile.samples[j][i];
			buffer2[j][i] = audioFile.samples[j][(numSamples / 2) + i];
		}
	}

	AudioFile<double> audioFile1, audioFile2;
	// Set both the number of channels and number of samples per channel
	audioFile1.setAudioBufferSize(numChannels, numSamples / 2);
	audioFile2.setAudioBufferSize(numChannels, numSamples / 2);

	// Set the number of samples per channel
	audioFile1.setNumSamplesPerChannel(audioFile.getNumSamplesPerChannel() / 2);
	audioFile2.setNumSamplesPerChannel(audioFile.getNumSamplesPerChannel() / 2);

	// Set the number of channels
	audioFile1.setNumChannels(audioFile.getNumChannels());
	audioFile2.setNumChannels(audioFile.getNumChannels());

	audioFile1.setBitDepth(audioFile.getBitDepth());
	audioFile2.setBitDepth(audioFile.getBitDepth());
	audioFile1.setSampleRate(audioFile.getSampleRate());
	audioFile2.setSampleRate(audioFile.getSampleRate());

	bool bSet1 = audioFile1.setAudioBuffer(buffer1);
	if (bSet1)
	{
		bool bSave = audioFile1.save(strOut1.GetString(), AudioFileFormat::Wave);
		if (bSave)
		{
		}
		else
		{
			AfxMessageBox("Failed to save file1");
		}
	}
	else
	{
		AfxMessageBox("Failed to set buffer1");
	}
	bool bSet2 = audioFile2.setAudioBuffer(buffer2);
	if (bSet1)
	{
		bool bSave = audioFile2.save(strOut2.GetString(), AudioFileFormat::Wave);
		if (bSave)
		{
		}
		else
		{
			AfxMessageBox("Failed to save file2");
		}
	}
	else
	{
		AfxMessageBox("Failed to set buffer2");
	}
}
void Test2_ToText(const CString & strIn)
{
	CString strOut1 = strIn, strOut2 = strIn;
	strOut1.Replace(".wav", "_1.txt");
	strOut2.Replace(".wav", "_2.txt");

	AudioFile<double> audioFile;

	bool bLoad = audioFile.load(strIn.GetString());
	if (bLoad == false)
	{
		AfxMessageBox("Failed to load input file.");
	}
	int numSamples = audioFile.getNumSamplesPerChannel();
	double lengthInSeconds = audioFile.getLengthInSeconds();

	int numChannels = audioFile.getNumChannels();
	bool isMono = audioFile.isMono();
	bool isStereo = audioFile.isStereo();
	if (numChannels >= 1)
	{
		int j = 0;
		FILE * poFile = NULL;
		fopen_s(&poFile, strOut1.GetString(), "wt");
		if (poFile == NULL)
		{
			AfxMessageBox("Failed to open output file1");
		}
		else
		{
			for (int i = 0; i < numSamples; i++)
			{
				if (fprintf_s(poFile, "%d\t%g\n", i, audioFile.samples[j][i]) < 0)
				{
					AfxMessageBox("Failed to write output file1");
					break;

				}
			}
			fclose(poFile);
		}
	}
	if (numChannels >= 2)
	{
		int j = 1;
		FILE * poFile = NULL;
		fopen_s(&poFile, strOut2.GetString(), "wt");
		if (poFile == NULL)
		{
			AfxMessageBox("Failed to open output file2");
		}
		else
		{
			for (int i = 0; i < numSamples; i++)
			{
				if (fprintf_s(poFile, "%d\t%g\n", i, audioFile.samples[j][i]) < 0)
				{
					AfxMessageBox("Failed to write output file2");
					break;

				}
			}
			fclose(poFile);
		}
	}
	if (numChannels >= 3)
	{
		AfxMessageBox("Warning: Numchannels > 3!");
	}
}
void GenerateEnvelope(int iChannel,int numSamples,int nWindowSize,const AudioFile<double>::AudioBuffer & audioBuf, std::vector<std::pair<int, double>> & voEnv)
{
	int nNumWindow = numSamples / nWindowSize;
	int nPartialWindowSize = numSamples % nWindowSize;
	int iSample = 0;
	for (int i = 0; i < nNumWindow; i++)
	{
		std::pair<int, double> pt(iSample + (nWindowSize / 2), 0);
		for (int j = 0; j < nWindowSize; j++)
		{
			if (pt.second < audioBuf[iChannel][iSample])
				pt.second = audioBuf[iChannel][iSample];
			iSample++;
		}
		voEnv.push_back(pt);
	}

	std::pair<int, double> pt(iSample + (nWindowSize / 2), 0);
	for (int j = 0; j < nPartialWindowSize; j++)
	{
		if (pt.second < audioBuf[iChannel][iSample])
			pt.second = audioBuf[iChannel][iSample];
		iSample++;
	}
	voEnv.push_back(pt);
}
void Test3_Envelope(const CString & strIn)
{
	CString strOut1 = strIn, strOut2 = strIn;
	strOut1.Replace(".wav", "_env1.txt");
	strOut2.Replace(".wav", "_env2.txt");

	AudioFile<double> audioFile;

	bool bLoad = audioFile.load(strIn.GetString());
	if (bLoad == false)
	{
		AfxMessageBox("Failed to load input file.");
	}
	int numSamples = audioFile.getNumSamplesPerChannel();
	double lengthInSeconds = audioFile.getLengthInSeconds();
	unsigned int nSamplesRate = audioFile.getSampleRate();
	int numChannels = audioFile.getNumChannels();
	bool isMono = audioFile.isMono();
	bool isStereo = audioFile.isStereo();
	if (numChannels >= 1)
	{
		int j = 0;
		FILE * poFile = NULL;
		fopen_s(&poFile, strOut1.GetString(), "wt");
		if (poFile == NULL)
		{
			AfxMessageBox("Failed to open output file1");
		}
		else
		{
			std::vector<std::pair<int, double>> voEnv;
			GenerateEnvelope(j, numSamples, 250, audioFile.samples, voEnv);
			for (int i = 0; i < (int)voEnv.size(); i++)
			{
				if (fprintf_s(poFile, "%d\t%g\n", voEnv[i].first, voEnv[i].second) < 0)
				{
					AfxMessageBox("Failed to write output file1");
					break;
				}
			}
			fclose(poFile);

		}
	}
	if (numChannels >= 2)
	{
		int j = 1;
		FILE * poFile = NULL;
		fopen_s(&poFile, strOut2.GetString(), "wt");
		if (poFile == NULL)
		{
			AfxMessageBox("Failed to open output file2");
		}
		else
		{
			std::vector<std::pair<int, double>> voEnv;
			GenerateEnvelope(j, numSamples, 250, audioFile.samples, voEnv);
			for (int i = 0; i < (int)voEnv.size(); i++)
			{
				if (fprintf_s(poFile, "%d\t%g\n", voEnv[i].first, voEnv[i].second) < 0)
				{
					AfxMessageBox("Failed to write output file2");
					break;
				}
			}
			fclose(poFile);
		}
	}
	if (numChannels >= 3)
	{
		AfxMessageBox("Warning: Numchannels > 3!");
	}
}

void CTrySoundFileDlg::OnBnClickedButton1()
{
	CString strIn = CGeneralUtilities::GetInputFilePath("Choose File to Split", "Wave", "wav");
	if (strIn == "")
		return;
	Test1_SplitAudio(strIn);
	Test2_ToText(strIn);
	Test3_Envelope(strIn);

}
