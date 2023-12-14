#pragma once
#include "Settings.h"
#include "FTPInfo.h"
#include "Orders.h"
#include "Login.h"
#include "Album.h"
#include "ProgressDlg.h"

namespace NVIFTP {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Collections::Generic;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;
	using namespace System::Drawing ::Imaging;
	using namespace System::IO;
	using namespace XmlSchemaClassLibrary;
	using namespace System::Configuration;
	using namespace System::Collections::Specialized;
//	using namespace System::Net;
//	using namespace System::Net::Security;
//	using namespace System::Security ::Cryptography ::X509Certificates;
	using namespace System::Data ::Odbc;
//	using namespace System::Diagnostics;
	using namespace CommonFunctionClassLibrary;
	using namespace System::Net ::Mail;
	using namespace Microsoft::Win32;
	using namespace DSConnect;

	/// <summary>
	/// Summary for Form1
	///
	/// WARNING: If you change the name of this class, you will need to change the
	///          'Resource File Name' property for the managed resource compiler tool
	///          associated with all .resx files this class depends on.  Otherwise,
	///          the designers will not be able to interact properly with localized
	///          resources associated with this form.
	/// </summary>
	public ref class Form1 : public System::Windows::Forms::Form
	{
	public:
		ArrayList ^		m_arrDBInfo;
		ArrayList ^		m_arrRuleInfo;
		ArrayList ^		m_arrFTPInfo;
		ArrayList ^		m_arrFileType;

		bool			m_bBusy;

		int				m_nIndex;

		String^			m_strTempFolder;
		int				m_nTimeInterval;

		String^			m_strEmailFromAdd;
		String^			m_strEmailServer;
		String^			m_strEmailPassword;
		ArrayList^		m_arrEmailTo;
		ArrayList^		m_arrEmailCC;

		String^			m_strLogPath;
		String^			m_strLogFile;
        String^			m_strlogDateTimeFormat;

		String^			m_strDatFile;
		String^			m_strKeyFile;

		String^			m_strGuid;
		int				m_nSolutionId;
		String^			m_strSolutionHash;
		String^			m_strUserId;
		String^			m_strUploadTempFolder;
		String^			m_strDomain;
		String^			m_strServiceKey;
		String^			m_strURL;
		String^			m_strSelFolder;
		String^			m_strAlbumName;

		String^			m_strUploadServer;
		String^			m_strUploadUsername;
		String^			m_strUploadPassword;
		String^			m_strUploadBaseDir;
		String^			m_strKey;

		int				m_nConfCounter;
		int				m_nQuality;
		int				m_nProxy;
		String^			m_strProxyServer;
		bool			m_bDownloader;

		bool			m_bWin32;

		ArrayList^		m_arrFiles;


	private: static StreamWriter^ m_swLog;
	private: static System::Threading ::Mutex^ m_mutex;
	private: static System::Threading ::Mutex^ m_logMutex;
	private: static System::Windows::Forms::ListView^  listProgress;












	private: static List<Stopwatch^>^ m_watchList;

	private: System::Windows::Forms::Panel^  progressPanel;
	private: System::Windows::Forms::Panel^  detailsPanel;
	private: System::Windows::Forms::Panel^  donePanel;
	private: System::Windows::Forms::ListView^  listDone;
	private: System::Windows::Forms::Label^  lblCurrentProgress;
	private: System::Windows::Forms::Label^  lblOrdersDwnldUploaded;
	private: System::Windows::Forms::Label^  lblFtpStatus;
	private: System::Windows::Forms::Label^  lblFtpConnection;
	private: System::Windows::Forms::Label^  lblFtpConnectionStatus;
	private: System::Windows::Forms::Label^  lblFtpConnectionTime;
	private: System::Windows::Forms::Label^  lblFtpType;
	private: System::Windows::Forms::ComboBox^  cmbBoxFtpServer;

	private: System::ComponentModel::BackgroundWorker^  downloadWorker;
	private: System::ComponentModel::BackgroundWorker^  uploadWorker;
	private: System::Windows::Forms::Timer^  ftpTimer;
	private: System::Windows::Forms::Label^  lblFtpStatusValue;
	private: System::Windows::Forms::Label^  lblFtpConnectionStatusValue;
	private: System::Windows::Forms::Label^  lblFtpTypeValue;
	private: System::Windows::Forms::Label^  lblFtpConnectionValue;
	private: System::Windows::Forms::Label^  lblFtpServerName;
	private: System::Windows::Forms::Label^  lblFtpServerNameValue;
	private: System::Windows::Forms::Timer^  displayTimer;
	private: System::Windows::Forms::Timer^  diagnosticsTimer;
	private: System::Windows::Forms::FolderBrowserDialog^  folderBrowserDialog;
	private: System::Windows::Forms::OpenFileDialog^  openFileDialog;
	private: System::Windows::Forms::Button^  btnSelectPhotos;
	private: System::Windows::Forms::Button^  btnUpload;
	private: System::Windows::Forms::PictureBox^  pictureBox1;
	private: System::Windows::Forms::PictureBox^  pictureBox2;
	private: System::Windows::Forms::Label^  lblFtpProgressValue;
	private: System::Windows::Forms::Label^  lblFtpProgress;
	private: System::Windows::Forms::Label^  lblFtpConnectionTimeValue;



















	private: System::Windows::Forms::Button^  btnFtpConnect;

	public:
		Form1(void)
		{
			InitializeComponent();
			//
			//TODO: Add the constructor code here
			//


			m_arrDBInfo = gcnew ArrayList();
			m_arrRuleInfo = gcnew ArrayList();
			m_arrFTPInfo = gcnew ArrayList();
			m_arrFileType = gcnew ArrayList();

			m_bBusy = false;

			m_nIndex = -1;
			m_nTimeInterval = 0;

			DateTime dt = DateTime::Now;
			String^ strDate = gcnew String(dt.Day.ToString () + "-" + dt.Month .ToString () + "-" + dt.Year .ToString ());
			m_strLogPath = gcnew String(Application::StartupPath + Path::DirectorySeparatorChar + "LOG");
			m_strLogFile = gcnew String(m_strLogPath + Path::DirectorySeparatorChar + "NVIFTP_" + strDate + ".log");
			m_strDatFile = gcnew String(m_strLogPath + Path::DirectorySeparatorChar + "NVIFTP_" + strDate + ".dat");
			m_strlogDateTimeFormat = gcnew String("yyyy-MM-ddTHH:mm:ss.fffffffK");
			m_strKeyFile = gcnew String(Application::StartupPath + Path::DirectorySeparatorChar + "dk.dat");

			m_watchList = gcnew List<Stopwatch^>();

			m_mutex = gcnew System::Threading::Mutex ();
			m_logMutex = gcnew System::Threading::Mutex ();

			m_nSolutionId = 0;
			m_strSelFolder = gcnew String("c:\\");
			m_nConfCounter = 1;
			m_nQuality = 100;
			m_arrFiles = gcnew ArrayList();

			m_nProxy = 0;
			m_bDownloader = false;
			m_bWin32 = true;
		}

	protected:
		/// <summary>
		/// Clean up any resources being used.
		/// </summary>
		~Form1()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^  btnSettings;
	private: System::ComponentModel::IContainer^  components;
	protected: 

	private:
		/// <summary>
		/// Required designer variable.
		/// </summary>


#pragma region Windows Form Designer generated code
		/// <summary>
		/// Required method for Designer support - do not modify
		/// the contents of this method with the code editor.
		/// </summary>
		void InitializeComponent(void)
		{
			this->components = (gcnew System::ComponentModel::Container());
			System::ComponentModel::ComponentResourceManager^  resources = (gcnew System::ComponentModel::ComponentResourceManager(Form1::typeid));
			this->btnSettings = (gcnew System::Windows::Forms::Button());
			this->listProgress = (gcnew System::Windows::Forms::ListView());
			this->progressPanel = (gcnew System::Windows::Forms::Panel());
			this->lblCurrentProgress = (gcnew System::Windows::Forms::Label());
			this->detailsPanel = (gcnew System::Windows::Forms::Panel());
			this->lblFtpProgressValue = (gcnew System::Windows::Forms::Label());
			this->lblFtpProgress = (gcnew System::Windows::Forms::Label());
			this->lblFtpServerNameValue = (gcnew System::Windows::Forms::Label());
			this->lblFtpServerName = (gcnew System::Windows::Forms::Label());
			this->lblFtpConnectionStatusValue = (gcnew System::Windows::Forms::Label());
			this->lblFtpTypeValue = (gcnew System::Windows::Forms::Label());
			this->lblFtpConnectionValue = (gcnew System::Windows::Forms::Label());
			this->lblFtpStatusValue = (gcnew System::Windows::Forms::Label());
			this->lblFtpType = (gcnew System::Windows::Forms::Label());
			this->lblFtpConnectionTime = (gcnew System::Windows::Forms::Label());
			this->lblFtpConnectionStatus = (gcnew System::Windows::Forms::Label());
			this->lblFtpConnection = (gcnew System::Windows::Forms::Label());
			this->lblFtpStatus = (gcnew System::Windows::Forms::Label());
			this->donePanel = (gcnew System::Windows::Forms::Panel());
			this->lblOrdersDwnldUploaded = (gcnew System::Windows::Forms::Label());
			this->listDone = (gcnew System::Windows::Forms::ListView());
			this->cmbBoxFtpServer = (gcnew System::Windows::Forms::ComboBox());
			this->btnFtpConnect = (gcnew System::Windows::Forms::Button());
			this->downloadWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->uploadWorker = (gcnew System::ComponentModel::BackgroundWorker());
			this->ftpTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->displayTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->diagnosticsTimer = (gcnew System::Windows::Forms::Timer(this->components));
			this->folderBrowserDialog = (gcnew System::Windows::Forms::FolderBrowserDialog());
			this->openFileDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->btnSelectPhotos = (gcnew System::Windows::Forms::Button());
			this->btnUpload = (gcnew System::Windows::Forms::Button());
			this->pictureBox1 = (gcnew System::Windows::Forms::PictureBox());
			this->pictureBox2 = (gcnew System::Windows::Forms::PictureBox());
			this->lblFtpConnectionTimeValue = (gcnew System::Windows::Forms::Label());
			this->progressPanel->SuspendLayout();
			this->detailsPanel->SuspendLayout();
			this->donePanel->SuspendLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->BeginInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->BeginInit();
			this->SuspendLayout();
			// 
			// btnSettings
			// 
			this->btnSettings->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 12, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				safe_cast<System::Byte>(0)));
			this->btnSettings->Location = System::Drawing::Point(829, 10);
			this->btnSettings->Name = L"btnSettings";
			this->btnSettings->Size = System::Drawing::Size(118, 39);
			this->btnSettings->TabIndex = 0;
			this->btnSettings->Text = L"Settings";
			this->btnSettings->UseVisualStyleBackColor = true;
			this->btnSettings->Visible = false;
			this->btnSettings->Click += gcnew System::EventHandler(this, &Form1::btnSettings_Click);
			// 
			// listProgress
			// 
			this->listProgress->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				safe_cast<System::Byte>(0)));
			this->listProgress->Location = System::Drawing::Point(11, 29);
			this->listProgress->Name = L"listProgress";
			this->listProgress->Size = System::Drawing::Size(911, 247);
			this->listProgress->TabIndex = 1;
			this->listProgress->UseCompatibleStateImageBehavior = false;
			this->listProgress->View = System::Windows::Forms::View::Details;
			// 
			// progressPanel
			// 
			this->progressPanel->BackColor = System::Drawing::Color::FromArgb(safe_cast<System::Int32>(safe_cast<System::Byte>(224)), safe_cast<System::Int32>(safe_cast<System::Byte>(224)), 
				safe_cast<System::Int32>(safe_cast<System::Byte>(224)));
			this->progressPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->progressPanel->Controls->Add(this->lblCurrentProgress);
			this->progressPanel->Controls->Add(this->listProgress);
			this->progressPanel->Location = System::Drawing::Point(12, 58);
			this->progressPanel->Name = L"progressPanel";
			this->progressPanel->Size = System::Drawing::Size(934, 287);
			this->progressPanel->TabIndex = 2;
			// 
			// lblCurrentProgress
			// 
			this->lblCurrentProgress->AutoSize = true;
			this->lblCurrentProgress->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, System::Drawing::GraphicsUnit::Point, 
				safe_cast<System::Byte>(0)));
			this->lblCurrentProgress->Location = System::Drawing::Point(8, 5);
			this->lblCurrentProgress->Name = L"lblCurrentProgress";
			this->lblCurrentProgress->Size = System::Drawing::Size(142, 17);
			this->lblCurrentProgress->TabIndex = 2;
			this->lblCurrentProgress->Text = L"Current Progress :";
			// 
			// detailsPanel
			// 
			this->detailsPanel->BackColor = System::Drawing::Color::FromArgb(safe_cast<System::Int32>(safe_cast<System::Byte>(224)), safe_cast<System::Int32>(safe_cast<System::Byte>(224)), 
				safe_cast<System::Int32>(safe_cast<System::Byte>(224)));
			this->detailsPanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->detailsPanel->Controls->Add(this->lblFtpProgressValue);
			this->detailsPanel->Controls->Add(this->lblFtpProgress);
			this->detailsPanel->Controls->Add(this->lblFtpServerNameValue);
			this->detailsPanel->Controls->Add(this->lblFtpServerName);
			this->detailsPanel->Controls->Add(this->lblFtpConnectionTimeValue);
			this->detailsPanel->Controls->Add(this->lblFtpConnectionStatusValue);
			this->detailsPanel->Controls->Add(this->lblFtpTypeValue);
			this->detailsPanel->Controls->Add(this->lblFtpConnectionValue);
			this->detailsPanel->Controls->Add(this->lblFtpStatusValue);
			this->detailsPanel->Controls->Add(this->lblFtpType);
			this->detailsPanel->Controls->Add(this->lblFtpConnectionTime);
			this->detailsPanel->Controls->Add(this->lblFtpConnectionStatus);
			this->detailsPanel->Controls->Add(this->lblFtpConnection);
			this->detailsPanel->Controls->Add(this->lblFtpStatus);
			this->detailsPanel->Location = System::Drawing::Point(12, 356);
			this->detailsPanel->Name = L"detailsPanel";
			this->detailsPanel->Size = System::Drawing::Size(287, 315);
			this->detailsPanel->TabIndex = 3;
			// 
			// lblFtpProgressValue
			// 
			this->lblFtpProgressValue->AutoSize = true;
			this->lblFtpProgressValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				safe_cast<System::Byte>(0)));
			this->lblFtpProgressValue->ForeColor = System::Drawing::Color::Navy;
			this->lblFtpProgressValue->Location = System::Drawing::Point(136, 161);
			this->lblFtpProgressValue->Name = L"lblFtpProgressValue";
			this->lblFtpProgressValue->Size = System::Drawing::Size(0, 15);
			this->lblFtpProgressValue->TabIndex = 13;
			// 
			// lblFtpProgress
			// 
			this->lblFtpProgress->AutoSize = true;
			this->lblFtpProgress->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				safe_cast<System::Byte>(0)));
			this->lblFtpProgress->Location = System::Drawing::Point(9, 159);
			this->lblFtpProgress->Name = L"lblFtpProgress";
			this->lblFtpProgress->Size = System::Drawing::Size(124, 17);
			this->lblFtpProgress->TabIndex = 12;
			this->lblFtpProgress->Text = L"Percent Complete:";
			// 
			// lblFtpServerNameValue
			// 
			this->lblFtpServerNameValue->AutoSize = true;
			this->lblFtpServerNameValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Italic, 
				System::Drawing::GraphicsUnit::Point, safe_cast<System::Byte>(0)));
			this->lblFtpServerNameValue->ForeColor = System::Drawing::Color::Navy;
			this->lblFtpServerNameValue->Location = System::Drawing::Point(136, 194);
			this->lblFtpServerNameValue->Name = L"lblFtpServerNameValue";
			this->lblFtpServerNameValue->Size = System::Drawing::Size(0, 15);
			this->lblFtpServerNameValue->TabIndex = 11;
			this->lblFtpServerNameValue->Visible = false;
			// 
			// lblFtpServerName
			// 
			this->lblFtpServerName->AutoSize = true;
			this->lblFtpServerName->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				safe_cast<System::Byte>(0)));
			this->lblFtpServerName->Location = System::Drawing::Point(9, 193);
			this->lblFtpServerName->Name = L"lblFtpServerName";
			this->lblFtpServerName->Size = System::Drawing::Size(74, 17);
			this->lblFtpServerName->TabIndex = 10;
			this->lblFtpServerName->Text = L"Ftp Server";
			this->lblFtpServerName->Visible = false;
			// 
			// lblFtpConnectionTimeValue
			// 
			this->lblFtpConnectionTimeValue->AutoSize = true;
			this->lblFtpConnectionTimeValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				safe_cast<System::Byte>(0)));
			this->lblFtpConnectionTimeValue->ForeColor = System::Drawing::Color::Navy;
			this->lblFtpConnectionTimeValue->Location = System::Drawing::Point(136, 132);
			this->lblFtpConnectionTimeValue->Name = L"lblFtpConnectionTimeValue";
			this->lblFtpConnectionTimeValue->Size = System::Drawing::Size(0, 15);
			this->lblFtpConnectionTimeValue->TabIndex = 9;
			// 
			// lblFtpConnectionStatusValue
			// 
			this->lblFtpConnectionStatusValue->AutoSize = true;
			this->lblFtpConnectionStatusValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Italic, 
				System::Drawing::GraphicsUnit::Point, safe_cast<System::Byte>(0)));
			this->lblFtpConnectionStatusValue->ForeColor = System::Drawing::Color::Navy;
			this->lblFtpConnectionStatusValue->Location = System::Drawing::Point(136, 100);
			this->lblFtpConnectionStatusValue->Name = L"lblFtpConnectionStatusValue";
			this->lblFtpConnectionStatusValue->Size = System::Drawing::Size(0, 15);
			this->lblFtpConnectionStatusValue->TabIndex = 8;
			// 
			// lblFtpTypeValue
			// 
			this->lblFtpTypeValue->AutoSize = true;
			this->lblFtpTypeValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				safe_cast<System::Byte>(0)));
			this->lblFtpTypeValue->ForeColor = System::Drawing::Color::Navy;
			this->lblFtpTypeValue->Location = System::Drawing::Point(136, 70);
			this->lblFtpTypeValue->Name = L"lblFtpTypeValue";
			this->lblFtpTypeValue->Size = System::Drawing::Size(0, 15);
			this->lblFtpTypeValue->TabIndex = 7;
			// 
			// lblFtpConnectionValue
			// 
			this->lblFtpConnectionValue->AutoSize = true;
			this->lblFtpConnectionValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Italic, 
				System::Drawing::GraphicsUnit::Point, safe_cast<System::Byte>(0)));
			this->lblFtpConnectionValue->ForeColor = System::Drawing::Color::Navy;
			this->lblFtpConnectionValue->Location = System::Drawing::Point(136, 42);
			this->lblFtpConnectionValue->Name = L"lblFtpConnectionValue";
			this->lblFtpConnectionValue->Size = System::Drawing::Size(0, 15);
			this->lblFtpConnectionValue->TabIndex = 6;
			// 
			// lblFtpStatusValue
			// 
			this->lblFtpStatusValue->AutoSize = true;
			this->lblFtpStatusValue->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Italic, System::Drawing::GraphicsUnit::Point, 
				safe_cast<System::Byte>(0)));
			this->lblFtpStatusValue->ForeColor = System::Drawing::Color::Navy;
			this->lblFtpStatusValue->Location = System::Drawing::Point(136, 10);
			this->lblFtpStatusValue->Name = L"lblFtpStatusValue";
			this->lblFtpStatusValue->Size = System::Drawing::Size(0, 15);
			this->lblFtpStatusValue->TabIndex = 5;
			// 
			// lblFtpType
			// 
			this->lblFtpType->AutoSize = true;
			this->lblFtpType->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				safe_cast<System::Byte>(0)));
			this->lblFtpType->Location = System::Drawing::Point(9, 70);
			this->lblFtpType->Name = L"lblFtpType";
			this->lblFtpType->Size = System::Drawing::Size(44, 17);
			this->lblFtpType->TabIndex = 4;
			this->lblFtpType->Text = L"Type:";
			// 
			// lblFtpConnectionTime
			// 
			this->lblFtpConnectionTime->AutoSize = true;
			this->lblFtpConnectionTime->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, safe_cast<System::Byte>(0)));
			this->lblFtpConnectionTime->Location = System::Drawing::Point(9, 130);
			this->lblFtpConnectionTime->Name = L"lblFtpConnectionTime";
			this->lblFtpConnectionTime->Size = System::Drawing::Size(118, 17);
			this->lblFtpConnectionTime->TabIndex = 3;
			this->lblFtpConnectionTime->Text = L"Connection Time:";
			// 
			// lblFtpConnectionStatus
			// 
			this->lblFtpConnectionStatus->AutoSize = true;
			this->lblFtpConnectionStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, 
				System::Drawing::GraphicsUnit::Point, safe_cast<System::Byte>(0)));
			this->lblFtpConnectionStatus->Location = System::Drawing::Point(9, 100);
			this->lblFtpConnectionStatus->Name = L"lblFtpConnectionStatus";
			this->lblFtpConnectionStatus->Size = System::Drawing::Size(127, 17);
			this->lblFtpConnectionStatus->TabIndex = 2;
			this->lblFtpConnectionStatus->Text = L"Connection Status:";
			// 
			// lblFtpConnection
			// 
			this->lblFtpConnection->AutoSize = true;
			this->lblFtpConnection->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				safe_cast<System::Byte>(0)));
			this->lblFtpConnection->Location = System::Drawing::Point(9, 40);
			this->lblFtpConnection->Name = L"lblFtpConnection";
			this->lblFtpConnection->Size = System::Drawing::Size(107, 17);
			this->lblFtpConnection->TabIndex = 1;
			this->lblFtpConnection->Text = L"Ftp Connection:";
			// 
			// lblFtpStatus
			// 
			this->lblFtpStatus->AutoSize = true;
			this->lblFtpStatus->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				safe_cast<System::Byte>(0)));
			this->lblFtpStatus->Location = System::Drawing::Point(9, 10);
			this->lblFtpStatus->Name = L"lblFtpStatus";
			this->lblFtpStatus->Size = System::Drawing::Size(56, 17);
			this->lblFtpStatus->TabIndex = 0;
			this->lblFtpStatus->Text = L"Status: ";
			// 
			// donePanel
			// 
			this->donePanel->BackColor = System::Drawing::Color::FromArgb(safe_cast<System::Int32>(safe_cast<System::Byte>(224)), safe_cast<System::Int32>(safe_cast<System::Byte>(224)), 
				safe_cast<System::Int32>(safe_cast<System::Byte>(224)));
			this->donePanel->BorderStyle = System::Windows::Forms::BorderStyle::FixedSingle;
			this->donePanel->Controls->Add(this->lblOrdersDwnldUploaded);
			this->donePanel->Controls->Add(this->listDone);
			this->donePanel->Location = System::Drawing::Point(310, 356);
			this->donePanel->Name = L"donePanel";
			this->donePanel->Size = System::Drawing::Size(636, 315);
			this->donePanel->TabIndex = 4;
			// 
			// lblOrdersDwnldUploaded
			// 
			this->lblOrdersDwnldUploaded->AutoSize = true;
			this->lblOrdersDwnldUploaded->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Bold, 
				System::Drawing::GraphicsUnit::Point, safe_cast<System::Byte>(0)));
			this->lblOrdersDwnldUploaded->Location = System::Drawing::Point(6, 5);
			this->lblOrdersDwnldUploaded->Name = L"lblOrdersDwnldUploaded";
			this->lblOrdersDwnldUploaded->Size = System::Drawing::Size(241, 17);
			this->lblOrdersDwnldUploaded->TabIndex = 1;
			this->lblOrdersDwnldUploaded->Text = L"Orders downloaded / uploaded :";
			// 
			// listDone
			// 
			this->listDone->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				safe_cast<System::Byte>(0)));
			this->listDone->Location = System::Drawing::Point(8, 29);
			this->listDone->Name = L"listDone";
			this->listDone->Size = System::Drawing::Size(617, 272);
			this->listDone->TabIndex = 0;
			this->listDone->UseCompatibleStateImageBehavior = false;
			this->listDone->View = System::Windows::Forms::View::Details;
			// 
			// cmbBoxFtpServer
			// 
			this->cmbBoxFtpServer->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				safe_cast<System::Byte>(0)));
			this->cmbBoxFtpServer->FormattingEnabled = true;
			this->cmbBoxFtpServer->Location = System::Drawing::Point(622, 19);
			this->cmbBoxFtpServer->Name = L"cmbBoxFtpServer";
			this->cmbBoxFtpServer->Size = System::Drawing::Size(70, 24);
			this->cmbBoxFtpServer->TabIndex = 5;
			this->cmbBoxFtpServer->Visible = false;
			// 
			// btnFtpConnect
			// 
			this->btnFtpConnect->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				safe_cast<System::Byte>(0)));
			this->btnFtpConnect->Location = System::Drawing::Point(534, 12);
			this->btnFtpConnect->Name = L"btnFtpConnect";
			this->btnFtpConnect->Size = System::Drawing::Size(82, 40);
			this->btnFtpConnect->TabIndex = 7;
			this->btnFtpConnect->Text = L"Connect";
			this->btnFtpConnect->UseVisualStyleBackColor = true;
			this->btnFtpConnect->Visible = false;
			this->btnFtpConnect->Click += gcnew System::EventHandler(this, &Form1::btnFtpConnect_Click);
			// 
			// downloadWorker
			// 
			this->downloadWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::downloadWorker_DoWork);
			this->downloadWorker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::downloadWorker_Completed);
			// 
			// uploadWorker
			// 
			this->uploadWorker->DoWork += gcnew System::ComponentModel::DoWorkEventHandler(this, &Form1::uploadWorker_DoWork);
			this->uploadWorker->RunWorkerCompleted += gcnew System::ComponentModel::RunWorkerCompletedEventHandler(this, &Form1::uploadWorker_Completed);
			// 
			// ftpTimer
			// 
			this->ftpTimer->Interval = 300000;
			this->ftpTimer->Tick += gcnew System::EventHandler(this, &Form1::ftpTimer_Up);
			// 
			// displayTimer
			// 
			this->displayTimer->Interval = 15000;
			this->displayTimer->Tick += gcnew System::EventHandler(this, &Form1::displayTimer_Up);
			// 
			// diagnosticsTimer
			// 
			this->diagnosticsTimer->Interval = 7200000;
			this->diagnosticsTimer->Tick += gcnew System::EventHandler(this, &Form1::diagnosticsTimer_Up);
			// 
			// openFileDialog
			// 
			this->openFileDialog->FileName = L"openFileDialog1";
			// 
			// btnSelectPhotos
			// 
			this->btnSelectPhotos->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 9, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				safe_cast<System::Byte>(0)));
			this->btnSelectPhotos->Location = System::Drawing::Point(56, 10);
			this->btnSelectPhotos->Name = L"btnSelectPhotos";
			this->btnSelectPhotos->Size = System::Drawing::Size(82, 40);
			this->btnSelectPhotos->TabIndex = 8;
			this->btnSelectPhotos->Text = L"Select Photos";
			this->btnSelectPhotos->UseVisualStyleBackColor = true;
			this->btnSelectPhotos->Click += gcnew System::EventHandler(this, &Form1::btnSelectPhotos_Click);
			// 
			// btnUpload
			// 
			this->btnUpload->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 10, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point, 
				safe_cast<System::Byte>(0)));
			this->btnUpload->Location = System::Drawing::Point(194, 9);
			this->btnUpload->Name = L"btnUpload";
			this->btnUpload->Size = System::Drawing::Size(82, 40);
			this->btnUpload->TabIndex = 9;
			this->btnUpload->Text = L"Upload";
			this->btnUpload->UseVisualStyleBackColor = true;
			this->btnUpload->Click += gcnew System::EventHandler(this, &Form1::btnUpload_Click);
			// 
			// pictureBox1
			// 
			this->pictureBox1->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.Image")));
			this->pictureBox1->InitialImage = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox1.InitialImage")));
			this->pictureBox1->Location = System::Drawing::Point(9, 7);
			this->pictureBox1->Name = L"pictureBox1";
			this->pictureBox1->Size = System::Drawing::Size(46, 46);
			this->pictureBox1->TabIndex = 10;
			this->pictureBox1->TabStop = false;
			// 
			// pictureBox2
			// 
			this->pictureBox2->Image = (cli::safe_cast<System::Drawing::Image^  >(resources->GetObject(L"pictureBox2.Image")));
			this->pictureBox2->Location = System::Drawing::Point(147, 7);
			this->pictureBox2->Name = L"pictureBox2";
			this->pictureBox2->Size = System::Drawing::Size(46, 46);
			this->pictureBox2->TabIndex = 11;
			this->pictureBox2->TabStop = false;
			// 
			// Form1
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(958, 683);
			this->Controls->Add(this->pictureBox2);
			this->Controls->Add(this->pictureBox1);
			this->Controls->Add(this->btnUpload);
			this->Controls->Add(this->btnSelectPhotos);
			this->Controls->Add(this->btnFtpConnect);
			this->Controls->Add(this->cmbBoxFtpServer);
			this->Controls->Add(this->donePanel);
			this->Controls->Add(this->detailsPanel);
			this->Controls->Add(this->progressPanel);
			this->Controls->Add(this->btnSettings);
			this->Icon = (cli::safe_cast<System::Drawing::Icon^  >(resources->GetObject(L"$this.Icon")));
			this->Name = L"Form1";
			this->StartPosition = System::Windows::Forms::FormStartPosition::CenterScreen;
			this->Text = L"NVI FTP";
			this->Load += gcnew System::EventHandler(this, &Form1::Form1_Load);
			this->FormClosing += gcnew System::Windows::Forms::FormClosingEventHandler(this, &Form1::Form1_Closing);
			this->progressPanel->ResumeLayout(false);
			this->progressPanel->PerformLayout();
			this->detailsPanel->ResumeLayout(false);
			this->detailsPanel->PerformLayout();
			this->donePanel->ResumeLayout(false);
			this->donePanel->PerformLayout();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox1))->EndInit();
			(cli::safe_cast<System::ComponentModel::ISupportInitialize^  >(this->pictureBox2))->EndInit();
			this->ResumeLayout(false);

		}
#pragma endregion

		/// prasann : 8th mar 12
	private: System::Void Form1_Load(System::Object^  sender, System::EventArgs^  e)
			 {
				/// check if running on mono
				 try
				 {
					Type^ type = System::Type::GetType ("Mono.Runtime", true); //
					m_bWin32 = false;
				 }
				catch ( TypeLoadException^ e ) 
				{
//				  Console::WriteLine( e->Message );
				}
				catch ( Exception^ e ) 
				{
//				  Console::WriteLine( e->Message );
				}

				 try
				 {
					Directory::CreateDirectory (m_strLogPath);
				 }
				 catch(Exception^ e)
				 {
				 }

				 /// load transfered list
				 if(File::Exists(m_strDatFile))
				 {
					FileStream^ fs = gcnew FileStream(m_strDatFile, FileMode::Open);
					BinaryFormatter^ formatter = gcnew BinaryFormatter;
					m_arrFTPInfo = (ArrayList^ ) formatter->Deserialize (fs);
					fs->Close ();

					 for(int j=0; j<m_arrFTPInfo->Count ; j++)
					 {
						 CFTPInfo^ info = (CFTPInfo^) m_arrFTPInfo [j];

        				 info->	m_ftpsClient = gcnew FTPSClient();
					 }
				 }

				 /// prasann : 22nd may 13
				 /// load key
				 if(File::Exists(m_strKeyFile))
				 {
					FileStream^ fs = gcnew FileStream(m_strKeyFile, FileMode::Open);
					BinaryFormatter^ formatter = gcnew BinaryFormatter;
					array<Byte>^ bkey = (array<Byte>^) formatter->Deserialize (fs);
					for(int i=0; i<bkey->Length; i++)
					{
						bkey[i] = ~bkey[i];
					}

					System::Text::ASCIIEncoding^ encoder = gcnew System::Text::ASCIIEncoding();
					m_strKey = encoder->GetString (bkey);

					fs->Close ();
				 }

				 /// read app settings
				 NameValueCollection^ appSettings = ConfigurationManager::AppSettings;

				//m_strCompanyID = gcnew String(appSettings["CompanyId"]);
				m_strTempFolder = gcnew String(appSettings["TempFolder"]);
				//m_strTempFilename = gcnew String(appSettings["TempFileName"]);
				//m_strHotFolder = gcnew String(appSettings["HotFolder"]);
				 m_nTimeInterval = Convert::ToInt32 (appSettings["TimeInterval"]);
				 m_nQuality = Convert::ToInt32 (appSettings["Quality"]);

				m_nProxy = Convert::ToInt32 (appSettings["Proxy"]);
				m_strProxyServer = gcnew String(appSettings["ProxyServer"]);
				int nDownloader = 0;
				nDownloader = Convert::ToInt32 (appSettings["Downloader"]);
				if(nDownloader == 1)
					m_bDownloader = true;

				 /// read settings xml
				if(m_bDownloader)
					ReadSettingsXml(Application::StartupPath + Path::DirectorySeparatorChar + "Settings.xml");
				 ReadSendMailXml(Application::StartupPath + Path::DirectorySeparatorChar + "SendMail.xml");
//-------
/*
				m_strGuid = gcnew String(appSettings["GUID"]);
				String^ strReg = gcnew String(Registry::ClassesRoot + "\\CLSID\\" + m_strGuid);
				m_strSolutionHash = safe_cast<String ^> (Registry::GetValue(strReg, "SolutionId", "1"));
				m_nSolutionId = Convert::ToInt32 (m_strSolutionHash);
				m_strSolutionHash = safe_cast<String ^> (Registry::GetValue(strReg, "SolutionHash", "12345"));
				//m_strUploadTempFolder = safe_cast<String ^> (Registry::GetValue(strReg, "UploadTempFolder", "c:\\windows\temp\\nviftp"));
				m_strDomain = safe_cast<String ^> (Registry::GetValue(strReg, "Domain", "www.nvi.co.in"));
				m_strServiceKey = safe_cast<String ^> (Registry::GetValue(strReg, "ServiceKey", "06b1038174e193b8766b3bbf11f3620f"));
				m_strURL = safe_cast<String ^> (Registry::GetValue(strReg, "URL", "http://www.nvi.co.in/xmlrpc.php"));
*/
/// mac specific
				m_nSolutionId = 4;
				m_strSolutionHash = "31799109-36C1-46a0-BAAC-2F46ED03C027";
				m_strDomain = "www.nvi.co.in";
				m_strServiceKey = "06b1038174e193b8766b3bbf11f3620f";
				m_strURL = "http://www.nvi.co.in/xmlrpc.php";
//------
				m_strUploadTempFolder = gcnew String(Path::GetTempPath () + "NVIFTP");
//MessageBox ::Show (m_strUploadTempFolder);

				try
				{
					Directory::CreateDirectory (m_strUploadTempFolder);
				}
				catch(Exception^ e)
				{
					MessageBox ::Show (e->InnerException->Message);
					return;
				}

				//m_strMailServerName = gcnew String(appSettings["MailServerName"]);
				//m_strPopServerName = gcnew String(appSettings["PopServerName"]);
				//m_strEmailToaddress = gcnew String(appSettings["EmailToaddress"]);
				//m_strMailSenderName = gcnew String(appSettings["MailSenderName"]);
				//m_strMailSenderPass = gcnew String(appSettings["MailSenderPass"]);

				//m_strLocalFolder = gcnew String(appSettings["LocalFolder"]);
				//m_strDestFolder = gcnew String(appSettings["DestinationFolder"]);
				//m_strFtpOrderListFolder = gcnew String(appSettings["OrderlistXmlFtpFolderDND"]);
				//m_strLocalOrderListFolder = gcnew String(appSettings["OrderlistXmlLocalFolderDND"]);
				//m_strFtpUpdateXmlFolder = gcnew String(appSettings["UpdateXmlFtpFolderUPd"]);
				//m_strLocalUpdateXmlFolder = gcnew String(appSettings["UpdateXmlLocalFolderUPd"]);
/*
				try
				{
					Directory::CreateDirectory (m_strLocalFolder);
					Directory::CreateDirectory (m_strDestFolder);
					Directory::CreateDirectory (m_strLocalOrderListFolder);
					Directory::CreateDirectory (m_strLocalUpdateXmlFolder);
				}
				catch(Exception^ e)
				{
					MessageBox::Show (e->Message);
				}
 */
				/// create list columns
				 listProgress->FullRowSelect = true;
				 listProgress ->Columns ->Add ("Filename", 320);
				 listProgress ->Columns ->Add ("Album", 130);
				 listProgress ->Columns ->Add ("Size", 110);
				 listProgress ->Columns ->Add ("Rate", 110);
				 listProgress ->Columns ->Add ("Transfered", 100);
				 listProgress ->Columns ->Add ("Status", 110);

				 listDone->FullRowSelect = true;
				 listDone ->Columns ->Add ("Album", 160);
//				 listDone ->Columns ->Add ("Config Name", 105);
				 listDone ->Columns ->Add ("Size", 100);
				 listDone ->Columns ->Add ("Date/Time", 130);
				 listDone ->Columns ->Add ("Type", 100);
				 listDone ->Columns ->Add ("Status", 90);

//m_strUserId = gcnew String("14");

				 if(m_bDownloader) /// prasann : 23rd jan 13
				 {
					m_strUserId = gcnew String("");
				 }
				 else
				 {
				 /// prasann : 26th oct 12
				 /// show login dialog
				 Login login(m_nSolutionId , m_strSolutionHash, m_strDomain, m_strServiceKey, m_strURL, m_strKey);
				 System::Windows::Forms::DialogResult result;
				 result = login.ShowDialog ();

				 if(result == System::Windows ::Forms ::DialogResult ::OK)
				 {
					m_strUserId = gcnew String(login.m_strUserID);
					m_strUploadServer = gcnew String(login.m_strUploadServer);
					m_strUploadUsername = gcnew String(login.m_strUploadUsername);
					m_strUploadPassword = gcnew String(login.m_strUploadPassword);
					m_strUploadBaseDir = gcnew String(login.m_strUploadBaseDir);

					/// set the previous configurations data
					 for(int j=0; j<m_arrFTPInfo->Count ; j++)
					 {
						 CFTPInfo^ info = (CFTPInfo^) m_arrFTPInfo [j];

						 if(!info->m_bDownload && !info->m_ruleInfo ->m_bPreview)
						 {
        					 info->	m_strServerName = gcnew String(m_strUploadServer);
        					 info->	m_strServerUserName = gcnew String(m_strUploadUsername);
        					 info->	m_strServerPassword = gcnew String(m_strUploadPassword);
        					 //info->	m_strServerWorkingDir = gcnew String(strWorkingDir);
        					 info->	m_strServerSlash = gcnew String("/");
        					 info->	m_strDBConnectionName = gcnew String("");
        					 info->	m_strLocalUploadFolder = gcnew String(m_strUploadTempFolder);
        					 info->	m_strServerUploadFolder = gcnew String(m_strUploadBaseDir);

							 info->m_bDownload = false;

							 CRuleInfo^ rule = gcnew CRuleInfo();
							 rule->m_bDeleteSource = true;
							 rule->m_strRuleName = gcnew String("Rule1");
							 rule->m_bRecursive = false;
							 info->m_ruleInfo = rule;

							 String^ strConfigName = gcnew String("Upload" + m_nConfCounter.ToString ());
							 info->m_strConfigName = strConfigName;
							 m_nConfCounter++;
						 }
					 }
				 }
				 else
				 {
					 if(! String::IsNullOrEmpty (login.m_strError) && m_bWin32)
					 {
						SendMail("NVIFTP Login Error", login.m_strError);
					 }

					 if(m_bWin32)
						this->Close ();
					 else
						Application::Exit ();
					 return;
				 }
				 ///
				 }

				 /// set up ftps client parameters
				 InitConfigurations();

				 /// prasann : 30th nov 12
				 /// downloader
				 if(m_bDownloader)
				 {
					 pictureBox1 ->Visible = false;
					 pictureBox2 ->Visible = false;
					 btnSelectPhotos ->Visible = false;
					 btnUpload ->Visible = false;
					 btnSettings ->Visible = true;
				 }

				 //String^ strConfigName = cmbBoxFtpServer->Text;
				 //SetSelectedInfo(strConfigName);
				 //m_dtConnectionStart = DateTime ::DateTime (0);
				 //showConnectionParameters();

				 /// start timers
				 if(m_nTimeInterval > 0)
					ftpTimer ->Interval = m_nTimeInterval  * 60 * 1000;
				 ftpTimer ->Start ();
				 displayTimer ->Start ();
				 diagnosticsTimer->Start ();
			 }

			 /// prasann : 8th mar 12
private: System::Void Form1_Closing(System::Object^  sender, System::Windows::Forms::FormClosingEventArgs^  e)
		 {
			 if( e->CloseReason == System::Windows::Forms::CloseReason::TaskManagerClosing  ||
				 e->CloseReason == System::Windows::Forms::CloseReason::WindowsShutDown )
			 {
				e->Cancel = false;
				return;
			 }
			 else/* if(m_bBusy)*/
			 {
				for(int i=0; i<m_arrFTPInfo->Count; i++)
				{
					CFTPInfo^ info = (CFTPInfo^) m_arrFTPInfo[i];

					if(info->m_bBusy)
					{
						e->Cancel = true;
						return;
					}
				}
			 }

			 /// store the transfered list
			if(File::Exists (m_strDatFile))
				File::Delete (m_strDatFile);
			FileStream^ fs = gcnew FileStream(m_strDatFile, FileMode::Create );
			BinaryFormatter^ formatter = gcnew BinaryFormatter;
			formatter->Serialize(fs, m_arrFTPInfo);
			fs->Close ();

			for(int i=0; i<m_arrFTPInfo->Count; i++)
			{
				CFTPInfo^ info = (CFTPInfo^) m_arrFTPInfo[i];
				if(info->m_bConnected)
					info->m_ftpsClient->Close ();
			}
			if(m_swLog)
				m_swLog->Close ();
			e->Cancel = false;
		 }

		 /// prasann : 8th mar 12
private: System::Void InitConfigurations()
		 {
				m_swLog = gcnew StreamWriter(m_strLogFile, true);

				m_watchList->RemoveRange(0, m_watchList->Count);

				for(int i=0; i<m_arrFTPInfo->Count; i++)
				{
					CFTPInfo^ info = (CFTPInfo^) m_arrFTPInfo[i];
					//info->m_strLogFile = gcnew String(m_strLogPath + Path::DirectorySeparatorChar + info->m_strConfigName + "_" + strDate + ".log");
					info->m_dtConnectionStart = DateTime ::DateTime (0);
					info->m_dtConnectionEnd = DateTime ::DateTime (0);

					info->m_ftpsClient->LogCommand += gcnew LogCommandEventHandler(client_LogCommand);
					info->m_ftpsClient->LogServerReply += gcnew LogServerReplyEventHandler(client_LogServerReply);
					info->m_ftpsClient ->SetIndex (i);
					info->m_ftpsClient ->SetConfigName (info->m_strConfigName);

					Stopwatch^ watch = gcnew Stopwatch();
					m_watchList->Add (watch);
				}
				m_swLog ->WriteLine ("");
				m_swLog ->WriteLine ("******************* NVIFTP *******************");
/*
			DateTime dt = DateTime::Now;
			String^ strDate = gcnew String(dt.Day.ToString () + "-" + dt.Month .ToString () + "-" + dt.Year .ToString ());

			for(int i=0; i<m_arrFTPInfo->Count; i++)
			{
				CFTPInfo^ info = (CFTPInfo^) m_arrFTPInfo[i];
				info->m_strLogFile = gcnew String(m_strLogPath + Path::DirectorySeparatorChar + info->m_strConfigName + "_" + strDate + ".log");
				m_swLog = gcnew StreamWriter(info->m_strLogFile, true);

				info->m_ftpsClient->LogCommand += gcnew LogCommandEventHandler(client_LogCommand);
				info->m_ftpsClient->LogServerReply += gcnew LogServerReplyEventHandler(client_LogServerReply);

				m_swLog ->WriteLine ("");
				m_swLog ->WriteLine ("******************* NVIFTP *******************");
			}
*/
		 }

		 /// prasann : 9th mar 12
private: static void client_LogCommand(System::Object^  sender, LogCommandEventArgs^ args)
		 {
			 FTPSClient^ client = (FTPSClient^) sender;
			 //Form1::m_swLog->WriteLine(DateTime::Now.ToString ());

            // Hide password
            String^ cmdText = args->CommandText;
            if (cmdText->StartsWith("PASS "))
                cmdText = "PASS ********";

			 String^ cmdText1 = gcnew String(DateTime::Now.ToString () + ": " + client->GetHostName () + ": " + client->GetConfigName() + ": " + cmdText);
			 m_logMutex->WaitOne ();
				Form1::m_swLog->WriteLine(cmdText1);
			 m_logMutex->ReleaseMutex ();
        }

		 /// prasann : 9th mar 12
private: static void client_LogServerReply(System::Object^  sender, LogServerReplyEventArgs^ args)
        {
			 FTPSClient^ client = (FTPSClient^) sender;
			//Form1::m_swLog->WriteLine(DateTime::Now.ToString ());
			 m_logMutex->WaitOne ();
				Form1::m_swLog->WriteLine(String::Format("{0}: {1}: {2}: {3} {4}", DateTime::Now.ToString (), client->GetHostName (), client->GetConfigName(), args->ServerReply->Code, args->ServerReply->Message));
			 m_logMutex->ReleaseMutex ();
        }

		 /// prasann : 9th mar 12
private: bool ReadSettingsXml(String^ path)
		 {
			 NVIFTPSettings^ oXml = gcnew NVIFTPSettings();

			 if(File::Exists (path))
			 {
				if(!oXml->ReadXml(path))
				{
					MessageBox ::Show ("Error reading " + path);
					if(m_bWin32)
					SendMail("NVIFTP: Error", "Error reading " + path);
					return false;
				}
			 }
			 else
				 return false;

			 for(int i=0; i< oXml->oFTP->DBConnection ->Count; i++)
			 {
				 CDBInfo^ dbInfo = gcnew CDBInfo();

				 dbInfo->m_strDBConnName = gcnew String(oXml->oFTP->DBConnection[i]->m_strName);
				 dbInfo->m_strDsn = gcnew String(oXml->oFTP->DBConnection[i]->m_strDsn);
				 dbInfo->m_strUid = gcnew String(oXml->oFTP->DBConnection[i]->m_strUid);
				 dbInfo->m_strPwd = gcnew String(oXml->oFTP->DBConnection[i]->m_strPwd);
				 dbInfo->m_strFields = gcnew String(oXml->oFTP->DBConnection[i]->SelectQuery->m_strFields);
				 dbInfo->m_strTable = gcnew String(oXml->oFTP->DBConnection[i]->SelectQuery->m_strTable);
				 dbInfo->m_strWhere = gcnew String(oXml->oFTP->DBConnection[i]->SelectQuery->m_strWhere);

				 m_arrDBInfo->Add (dbInfo);
			 }

			 for(int i=0; i< oXml->oFTP->Rule->Count; i++)
			 {
				 CRuleInfo ^ ruleInfo = gcnew CRuleInfo();

				 ruleInfo->m_strRuleName = gcnew String(oXml->oFTP->Rule[i]->m_strName);
				 ruleInfo->m_bDeleteSource = oXml->oFTP->Rule[i]->m_bDeleteSource ;
				 ruleInfo->m_bDeleteDestination = oXml->oFTP->Rule[i]->m_bDeleteDestination ;
				 ruleInfo->m_strFirstFileDownload = gcnew String(oXml->oFTP->Rule[i]->m_strFirstFileDownload);
				 ruleInfo->m_strLastFileDownload = gcnew String(oXml->oFTP->Rule[i]->m_strLastFileDownload);
				 ruleInfo->m_strFirstFileUpload = gcnew String(oXml->oFTP->Rule[i]->m_strFirstFileUpload);
				 ruleInfo->m_strLastFileUpload = gcnew String(oXml->oFTP->Rule[i]->m_strLastFileUpload);
				 ruleInfo->m_strSkipFileType = gcnew String(oXml->oFTP->Rule[i]->m_strSkipFileType);
				 ruleInfo->m_bOverwrite = oXml->oFTP->Rule[i]->m_bOverwrite;
				 ruleInfo->m_bRecursive = oXml->oFTP->Rule[i]->m_bRecursive ;
				 ruleInfo->m_bPreview = oXml->oFTP->Rule[i]->m_bPreview ;

				 m_arrRuleInfo->Add(ruleInfo);
			 }

			 for(int i=0; i< oXml->oFTP->Server->Count; i++)
			 {
				 CFTPInfo^ ftpInfo = gcnew CFTPInfo();

				 ftpInfo->m_strConfigName = gcnew String(oXml->oFTP->Server[i]->m_strConfigName );
				 ftpInfo->m_strServerName  = gcnew String(oXml->oFTP->Server[i]->m_strServerName);
				 ftpInfo->m_strDBConnectionName = gcnew String(oXml->oFTP->Server[i]->m_strDBConnectionName);
				 ftpInfo->m_strRuleName = gcnew String(oXml->oFTP->Server[i]->m_strRuleName);
				 ftpInfo->m_strServerUserName  = gcnew String(oXml->oFTP->Server[i]->m_strServerUserName);
				 ftpInfo->m_strServerPassword  = gcnew String(oXml->oFTP->Server[i]->m_strServerPassword);
				 ftpInfo->m_strServerSlash = gcnew String(oXml->oFTP->Server[i]->m_strServerSlash);
				 ftpInfo->m_strServerWorkingDir = gcnew String(oXml->oFTP->Server[i]->m_strServerWorkingDir);
				 ftpInfo->m_strLocalDownloadFolder = gcnew String(oXml->oFTP->Server[i]->m_strLocalDownloadFolder);
				 ftpInfo->m_strLocalUploadFolder = gcnew String(oXml->oFTP->Server[i]->m_strLocalUploadFolder);
				 ftpInfo->m_strServerDownloadFolder = gcnew String(oXml->oFTP->Server[i]->m_strServerDownloadFolder);
				 ftpInfo->m_strServerUploadFolder = gcnew String(oXml->oFTP->Server[i]->m_strServerUploadFolder);
				 ftpInfo->m_nTimeInterval = oXml->oFTP->Server[i]->m_nTimeInterval;
				 ftpInfo->m_bDownload = oXml->oFTP->Server[i]->m_bDownload;

				 for(int j=0; j< m_arrDBInfo->Count; j++)
				 {
					 CDBInfo^ info = (CDBInfo^) m_arrDBInfo[j];
					 if(info->m_strDBConnName->CompareTo (ftpInfo->m_strDBConnectionName) == 0)
					 {
						ftpInfo->m_dbInfo = info;
						break;
					 }
				 }
				 for(int j=0; j< m_arrRuleInfo->Count; j++)
				 {
					 CRuleInfo^ info = (CRuleInfo^) m_arrRuleInfo[j];
					 if(info->m_strRuleName->CompareTo (ftpInfo->m_strRuleName) == 0)
					 {
						 ftpInfo->m_ruleInfo = info;
						 break;
					 }
				 }

				 for(int j=0; j<m_arrFTPInfo->Count ; j++)
				 {
					 CFTPInfo^ info = (CFTPInfo^) m_arrFTPInfo [j];
					 if(info->m_strConfigName == ftpInfo->m_strConfigName)
					 {
						 for(int k=0; k<info->m_arrOrders ->Count; k++)
						 {
							 ftpInfo->m_arrOrders ->Add ((String^)info->m_arrOrders [k]);
						 }
						 for(int k=0; k<info->m_arrFiles ->Count; k++)
						 {
							 ftpInfo->m_arrFiles ->Add ((CFileInfo^)info->m_arrFiles [k]);
						 }
						 m_arrFTPInfo->RemoveAt (j);
						 break;
					 }
				 }
				 m_arrFTPInfo ->Add(ftpInfo);
			 }

			 for(int i=0; i< oXml->oFTP->FileType->m_strType->Count; i++)
			 {
				 String^ str = (String^) oXml->oFTP->FileType->m_strType [i];
				 m_arrFileType ->Add (str);
			 }

			 return true;
		 }

		 /// prasann : 9th mar 12
private: bool WriteSettingsXml(String^ path)
		 {
			 NVIFTPSettings^ oXml = gcnew NVIFTPSettings();

			for(int i=0; i<m_arrDBInfo->Count; i++)
			{
				CDBInfo^ info = (CDBInfo^)m_arrDBInfo[i];

				 DBConnection^ connection = gcnew DBConnection();
				 connection->m_strName = gcnew String(info->m_strDBConnName);
				 connection->m_strDsn  = gcnew String(info->m_strDsn);
				 connection->m_strUid  = gcnew String(info->m_strUid);
				 connection->m_strPwd = gcnew String(info->m_strPwd);
				 connection->SelectQuery ->m_strFields  = gcnew String(info->m_strFields );
				 connection->SelectQuery ->m_strTable  = gcnew String(info->m_strTable);
				 connection->SelectQuery ->m_strWhere  = gcnew String(info->m_strWhere);

				 oXml->oFTP->DBConnection ->Add (connection);
			}

			for(int i=0; i<m_arrRuleInfo->Count; i++)
			{
				CRuleInfo^ info = (CRuleInfo^)m_arrRuleInfo[i];

				XmlSchemaClassLibrary::Rule^ rule = gcnew XmlSchemaClassLibrary::Rule();
				 rule->m_strName  = gcnew String(info->m_strRuleName );
				 rule->m_bDeleteDestination   = info->m_bDeleteDestination;
				 rule->m_bDeleteSource   = info->m_bDeleteSource ;
				 rule->m_bOverwrite  = info->m_bOverwrite;
				 rule->m_bRecursive  = info->m_bRecursive;
				 rule->m_bPreview  = info->m_bPreview;
				 rule->m_strFirstFileDownload   = gcnew String(info->m_strFirstFileDownload );
				 rule->m_strLastFileDownload    = gcnew String(info->m_strLastFileDownload);
				 rule->m_strFirstFileUpload   = gcnew String(info->m_strFirstFileUpload);
				 rule->m_strLastFileUpload   = gcnew String(info->m_strLastFileUpload);
				 rule->m_strSkipFileType    = gcnew String(info->m_strSkipFileType);

				 oXml->oFTP->Rule ->Add (rule);
			}

			for(int i=0; i<m_arrFTPInfo ->Count; i++)
			{
				CFTPInfo^ info = (CFTPInfo^)m_arrFTPInfo[i];

				 Server^ server = gcnew Server();
				 server->m_strConfigName   = gcnew String(info->m_strConfigName );
				 server->m_strServerName   = gcnew String(info->m_strServerName );
				 server->m_strServerUserName   = gcnew String(info->m_strServerUserName );
				 server->m_strServerPassword  = gcnew String(info->m_strServerPassword );
				 server->m_strServerWorkingDir   = gcnew String(info->m_strServerWorkingDir );
				 server->m_strServerSlash   = gcnew String(info->m_strServerSlash);
				 server->m_nTimeInterval   = info->m_nTimeInterval;
				 server->m_strDBConnectionName    = gcnew String(info->m_strDBConnectionName );
				 server->m_strRuleName   = gcnew String(info->m_strRuleName);
				 server->m_strLocalDownloadFolder    = gcnew String(info->m_strLocalDownloadFolder );
				 server->m_strLocalUploadFolder    = gcnew String(info->m_strLocalUploadFolder );
				 server->m_strServerDownloadFolder    = gcnew String(info->m_strServerDownloadFolder);
				 server->m_strServerUploadFolder   = gcnew String(info->m_strServerUploadFolder);
				 server->m_bDownload = info->m_bDownload;

				 oXml->oFTP->Server ->Add (server);
			}

			for(int i=0; i<m_arrFileType->Count; i++)
			{
				String^ str = (String^) m_arrFileType[i];
				oXml->oFTP ->FileType ->m_strType ->Add (str);
			}

			try
			{
				oXml->WriteXml(path);
			}
			catch(Exception^ e)
			{
				MessageBox ::Show ("Error saving settings xml: " + e->Message);
				return false;
			}

			 return true;
		 }

		 /// prasann : 9th mar 12
	private: System::Void btnSettings_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				//if(m_bBusy)
				//{
				//  return;
				//}
				for(int i=0; i<m_arrFTPInfo->Count; i++)
				{
					CFTPInfo^ info = (CFTPInfo^) m_arrFTPInfo[i];
					if(info->m_bBusy)
						return;
				}

				m_bBusy = true;

				//for(int i=0; i<m_arrFTPInfo->Count; i++)
				//{
				//	CFTPInfo^ info = (CFTPInfo^) m_arrFTPInfo[i];
				//	m_swLog->Close ();
				//}

				 Settings settings( m_arrDBInfo, m_arrRuleInfo, m_arrFTPInfo, m_arrFileType);
				 System::Windows::Forms::DialogResult result;
				 result = settings.ShowDialog ();

				 if(result == System::Windows ::Forms::DialogResult ::OK)
				 {
					 m_swLog->Close ();
					 m_arrDBInfo ->RemoveRange (0, m_arrDBInfo->Count);
					 for(int i=0; i< settings.m_arrDBInfo ->Count ; i++)
					 {
						 m_arrDBInfo->Add (settings.m_arrDBInfo[i]);
					 }
					 m_arrRuleInfo ->RemoveRange (0, m_arrRuleInfo->Count);
					 for(int i=0; i< settings.m_arrRuleInfo ->Count ; i++)
					 {
						 m_arrRuleInfo->Add (settings.m_arrRuleInfo[i]);
					 }
					 m_arrFTPInfo ->RemoveRange (0, m_arrFTPInfo->Count);
					 for(int i=0; i< settings.m_arrFTPInfo ->Count ; i++)
					 {
						 m_arrFTPInfo->Add (settings.m_arrFTPInfo[i]);
					 }
					 m_arrFileType ->RemoveRange (0, m_arrFileType->Count);
					 for(int i=0; i< settings.m_arrFileType ->Count ; i++)
					 {
						 m_arrFileType->Add (settings.m_arrFileType[i]);
					 }

					 /// write settings xml
					 WriteSettingsXml(Application::StartupPath + Path::DirectorySeparatorChar + "Settings.xml");

					 InitConfigurations();
				 }

				 m_bBusy = false;
			 }

			 /// prasann : 17th mar 12
			 /// do download/upload
	 private: System::Void DoWork()
			  {
//MessageBox::Show ("Do Work");
				  if(m_bBusy)
				  {
					  return;
				  }
/*

				  if(m_nIndex >= m_arrFTPInfo->Count)
				  {
					  m_nIndex = 0;
					  return;
				  }

				  SetSelectedInfo();

					if(m_ftpInfo->m_bDownload)
					{
						Download ();
					}
					else
					{
						Upload ();
					}
*/
				  bool bBusy = false;
				  for(int i=0; i<m_arrFTPInfo->Count; i++)
				  {
					 CFTPInfo^ info = (CFTPInfo^) m_arrFTPInfo [i];
					 if(info->m_bBusy)
					 {
						 bBusy = true;
						 break;
					 }
				  }
				  if(! bBusy)
				  {
					  /// clear the progress list
					  listProgress->Items->Clear();

					  /// flush the dat file contents
						if(File::Exists (m_strDatFile))
							File::Delete (m_strDatFile);
						FileStream^ fs = gcnew FileStream(m_strDatFile, FileMode::Create );
						BinaryFormatter^ formatter = gcnew BinaryFormatter;
						formatter->Serialize(fs, m_arrFTPInfo);
						fs->Close ();

						/// check if new log file is to be created
						DateTime dt = DateTime::Now;
						String^ strDate = gcnew String(dt.Day.ToString () + "-" + dt.Month .ToString () + "-" + dt.Year .ToString ());
						String^ strLogFile = gcnew String(m_strLogPath + Path::DirectorySeparatorChar + "NVIFTP_" + strDate + ".log");
						if(strLogFile == m_strLogFile)
						{
						}
						else
						{
							m_strLogFile = gcnew String(strLogFile);
							m_strDatFile = gcnew String(m_strLogPath + Path::DirectorySeparatorChar + "NVIFTP_" + strDate + ".dat");

							m_swLog->Close ();
							m_swLog = gcnew StreamWriter(m_strLogFile, true);

							  for(int i=0; i<m_arrFTPInfo->Count; i++)
							  {
								 CFTPInfo^ info = (CFTPInfo^) m_arrFTPInfo [i];
								 info->m_arrFiles ->Clear ();
								 info->m_arrOrders ->Clear ();
							  }
						}
				  }

				  /// start the work
				  for(int i=0; i<m_arrFTPInfo->Count; i++)
				  {
					 CFTPInfo^ info = (CFTPInfo^) m_arrFTPInfo [i];
					 if(! info->m_bBusy)
					 {
						 //BackgroundWorker^ worker = gcnew BackgroundWorker();
						 try
						 {
							 info->m_worker = gcnew BackgroundWorker();
							 info->m_worker ->WorkerSupportsCancellation = true;
							 if(info->m_bDownload)
								info->m_worker->DoWork += gcnew DoWorkEventHandler(this, &Form1::downloadWorker_DoWork);
							 else
								 info->m_worker->DoWork += gcnew DoWorkEventHandler(this, &Form1::uploadWorker_DoWork);
							 info->m_worker->RunWorkerAsync (info);
						 }
						 catch(Exception^ e)
						 {
							m_logMutex->WaitOne ();
							  m_swLog->WriteLine (info->m_strConfigName + ": error starting thread: " + e->Message);
							m_logMutex->ReleaseMutex ();
							if(m_bWin32)
							SendMail("NVIFTP error", info->m_strConfigName + ": error starting thread: " + e->Message);
						 }
					 }
				  }
			  }

			 /// prasann : 12th mar 12
			 /// set the currently selected server parameters
	 private: System::Void SetSelectedInfo(/*String^ strConfigName*/)
			  {
				 //for(int i=0; i< m_arrFTPInfo ->Count ; i++)
				 //{
					// CFTPInfo^ info = (CFTPInfo^) m_arrFTPInfo [i];
					// if(info->m_strConfigName ->CompareTo (strConfigName) == 0)
					// {
					//	 m_ftpInfo = info;
					//	 break;
					// }
				 //}
			  }

	private: System::Void ftpTimer_Up(System::Object^  sender, System::EventArgs^  e)
			 {
				 /// do work
				 DoWork ();
			 }

			  /// prasann : 12th mar 12
			  /// connect to the ftp server and start upload/download
	private: System::Void btnFtpConnect_Click(System::Object^  sender, System::EventArgs^  e)
			 {
				 DoWork();
			 }
/*
	private: static bool ValidateTestServerCertificate(System::Object^  sender, X509Certificate^ certificate, X509Chain^ chain, SslPolicyErrors sslPolicyErrors)
			{
				return true;
			}

	private: System::Void Download()
			 {
				 if(! m_bBusy)
				 {
					 if(! downloadWorker->IsBusy )
						 downloadWorker->RunWorkerAsync ();
				 }
			 }

	private: System::Void Upload()
			 {
				 if(! m_bBusy)
				 {
					 if(! uploadWorker->IsBusy )
						 uploadWorker->RunWorkerAsync ();
				 }
			 }
*/
	private: System::Void downloadWorker_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
			 {
//m_logMutex->WaitOne ();
//	m_swLog->WriteLine ("In worker thread");
//	m_swLog->Flush();
//m_logMutex->ReleaseMutex ();
				 CFTPInfo^ ftpInfo = (CFTPInfo^) e->Argument;

				 ftpInfo->m_bBusy = true;
				 ftpInfo->m_dtConnectionStart = DateTime::Now;
				 showConnectionParameters(ftpInfo);
				//listProgress->Items ->Clear ();

//m_logMutex->WaitOne ();
//	m_swLog->WriteLine (ftpInfo->m_strConfigName + ": calling login");
//	m_swLog->Flush();
//m_logMutex->ReleaseMutex ();

				 String^ strRet = ftpInfo->Login();

//m_logMutex->WaitOne ();
//	m_swLog->WriteLine (ftpInfo->m_strConfigName + ": login status: " + ftpInfo->m_bConnected.ToString ());
//m_logMutex->ReleaseMutex ();

				 m_logMutex->WaitOne ();
					m_swLog ->Flush ();
				 m_logMutex->ReleaseMutex ();
				 showConnectionParameters(ftpInfo);
				 if(! ftpInfo->m_bConnected)
				 {
					 ftpInfo->m_bBusy = false;
					ftpInfo->m_dtConnectionEnd = DateTime::Now;
					m_logMutex->WaitOne ();
						m_swLog->WriteLine ("Login error: " + strRet);
						m_swLog->Flush ();
					m_logMutex->ReleaseMutex ();
					 return;
				 }

//m_logMutex->WaitOne ();
//	m_swLog->WriteLine(ftpInfo->m_strConfigName + ": Connected");
//	m_swLog->Flush ();
//m_logMutex->ReleaseMutex ();

				 try
				 {
					 Directory::CreateDirectory (ftpInfo->m_strLocalDownloadFolder);
					 if(!String::IsNullOrEmpty (m_strTempFolder))
					 {
						Directory::CreateDirectory (m_strTempFolder+ Path::DirectorySeparatorChar + ftpInfo->m_strConfigName);
					 }
					 else
					 {
						ftpInfo->m_bBusy = false;
						ftpInfo->m_bConnected = false;
						ftpInfo->m_ftpsClient->Close ();
						ftpInfo->m_dtConnectionEnd = DateTime::Now;
						m_logMutex->WaitOne ();
							m_swLog->WriteLine ("Temp folder is null");
						m_logMutex->ReleaseMutex ();
						return;
					 }
				 }
				 catch(Exception ^ e)
				 {
					m_logMutex->WaitOne ();
						m_swLog->WriteLine (ftpInfo->m_strLocalDownloadFolder + ", " + m_strTempFolder + ", " + ftpInfo->m_strConfigName + " CreateDirectory failed");
					m_logMutex->ReleaseMutex ();
						ftpInfo->m_bBusy = false;
						ftpInfo->m_bConnected = false;
						ftpInfo->m_ftpsClient->Close ();
						ftpInfo->m_dtConnectionEnd = DateTime::Now;
					return;
				 }

//m_logMutex->WaitOne ();
//	m_swLog->WriteLine(ftpInfo->m_strConfigName + ": Calling download");
//	m_swLog->Flush ();
//m_logMutex->ReleaseMutex ();
/*
				 /// download all orders
				 if(String::IsNullOrEmpty (ftpInfo->m_strDBConnectionName))
				 {
					 DownloadOrders(ftpInfo);
				 }
				 else
				 {
					DownloadOrdersDB(ftpInfo);
				 }
*/
				 DownloadNew(ftpInfo);

//m_logMutex->WaitOne ();
//	m_swLog->WriteLine(ftpInfo->m_strConfigName + ": After download");
//m_logMutex->ReleaseMutex ();

				ftpInfo->m_bBusy = false;
				m_logMutex->WaitOne ();
					m_swLog->Flush ();
				m_logMutex->ReleaseMutex ();

				ftpInfo->m_ftpsClient->Close ();
				ftpInfo->m_bConnected = false;
				ftpInfo->m_dtConnectionEnd = DateTime::Now;
				m_logMutex->WaitOne ();
					m_swLog->WriteLine ();
					m_swLog->Flush ();
				m_logMutex->ReleaseMutex ();

			    showConnectionParameters(ftpInfo);

				 //showConnectionParameters();
			 }

	private: System::Void uploadWorker_DoWork(System::Object^  sender, System::ComponentModel::DoWorkEventArgs^  e)
			 {
				 CFTPInfo^ ftpInfo = (CFTPInfo^) e->Argument;

				 ftpInfo->m_bBusy = true;
				 ftpInfo->m_dtConnectionStart = DateTime::Now;
				 showConnectionParameters(ftpInfo);

				 //listProgress->Items ->Clear ();

//				 ftpInfo->Login();
				 String^ str = ftpInfo->Login();
//MessageBox ::Show (str);
				 m_logMutex->WaitOne ();
					m_swLog ->Flush ();
				 m_logMutex->ReleaseMutex ();
				 showConnectionParameters(ftpInfo);
				 if(! ftpInfo->m_bConnected)
				 {
					 ftpInfo->m_bBusy = false;
					ftpInfo->m_dtConnectionEnd = DateTime::Now;
					 return;
				 }

				 /// upload all orders
/*
				 if(String::IsNullOrEmpty (ftpInfo->m_strDBConnectionName))
				 {
					 UploadOrders(ftpInfo);
				 }
				 else
				 {
					 UploadOrdersDB(ftpInfo);
				 }
*/
				 bool bRet = UploadNew(ftpInfo);
				 ///

				ftpInfo->m_bBusy = false;
				m_logMutex->WaitOne ();
					m_swLog->Flush ();
				m_logMutex->ReleaseMutex ();

				ftpInfo->m_ftpsClient->Close ();
				ftpInfo->m_bConnected = false;
				ftpInfo->m_dtConnectionEnd = DateTime::Now;
				m_logMutex->WaitOne ();
					m_swLog->WriteLine ();
					m_swLog->Flush ();
				m_logMutex->ReleaseMutex ();


			    showConnectionParameters(ftpInfo);

				/// remove the upload configuration if finished
				if(bRet && !ftpInfo->m_ruleInfo ->m_bPreview) //not if preview upload
				{
					for(int i=0; i<m_arrFTPInfo->Count; i++)
					{
						CFTPInfo ^ pInfo = (CFTPInfo ^)m_arrFTPInfo[i];
						if(pInfo->m_strConfigName ->CompareTo (ftpInfo->m_strConfigName) == 0)
						{
							m_arrFTPInfo  ->RemoveAt (i);
							break;
						}
					}

				  /// flush the dat file contents
					if(File::Exists (m_strDatFile))
						File::Delete (m_strDatFile);
					FileStream^ fs = gcnew FileStream(m_strDatFile, FileMode::Create );
					BinaryFormatter^ formatter = gcnew BinaryFormatter;
					formatter->Serialize(fs, m_arrFTPInfo);
					fs->Close ();

				}

			 }

	private: System::Void downloadWorker_Completed(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) 
			 {
				 //m_nIndex ++;
				 //DoWork ();
			 }

	private: System::Void uploadWorker_Completed(System::Object^  sender, System::ComponentModel::RunWorkerCompletedEventArgs^  e) 
			 {
				 //m_nIndex ++;
				 //DoWork ();
			 }

			 /// prasann : 11th mar 12
	 private: System::Void showConnectionParameters(CFTPInfo^ info)
			  {
				  if(info->m_bBusy )
					  lblFtpStatusValue->Text = "Progress";
				  else
					  lblFtpStatusValue->Text = "Idle";

				  lblFtpConnectionValue->Text = info->m_strConfigName;
//				  lblFtpServerNameValue->Text = info->m_strServerName;

				  if(info ->m_bDownload)
					lblFtpTypeValue->Text = "Download";
				  else
					lblFtpTypeValue->Text = "Upload";

				  if(info->m_bBusy)
					lblFtpConnectionStatusValue ->Text = info->m_ftpsClient->WelcomeMessage;
				  else
					  lblFtpConnectionStatusValue ->Text = "";

				  if(info->m_dtConnectionStart.Ticks > 0)
				  {
					TimeSpan ts;
					if(info->m_bBusy)
						ts = DateTime::Now - info->m_dtConnectionStart;
					else
						ts = info->m_dtConnectionEnd - info->m_dtConnectionStart;
					String^ strTime = gcnew String(ts.Hours.ToString () + " : " + ts.Minutes.ToString () + " : " + ts.Seconds.ToString ());
					lblFtpConnectionTimeValue->Text = strTime;
				  }
				  else
				  {
					  lblFtpConnectionTimeValue->Text = "0 : 0 : 0";
				  }

				  /// prasann : 19th nov 12
				  /// percent complete
				  if(info->m_nPercentComplete > 0 && info->m_nOrderSize > 0)
				  {
					  int npercent = info->m_nPercentComplete * 100 / info->m_nOrderSize;
					  lblFtpProgressValue->Text = npercent.ToString () + " %";
				  }
				  else
				  {
					  lblFtpProgressValue->Text = "0 %";
				  }
			  }

			  /// prasann : 17th mar 12
			  /// download order without DB support
	  private: bool DownloadOrders(CFTPInfo^ ftpInfo)
			   {
					String^ strRemotePath;
					//if(String::IsNullOrEmpty (m_ftpInfo->m_strServerDownloadFolder))
					//	strRemotePath= gcnew String(m_ftpInfo->m_strServerSlash + m_ftpInfo->m_strServerWorkingDir);
					//else
					//	strRemotePath= gcnew String(m_ftpInfo->m_strServerSlash + m_ftpInfo->m_strServerWorkingDir + m_ftpInfo->m_strServerSlash + m_ftpInfo->m_strServerDownloadFolder);
					if(ftpInfo->m_strServerDownloadFolder->StartsWith (ftpInfo->m_strServerSlash))
						strRemotePath= gcnew String(ftpInfo->m_strServerDownloadFolder);
					else
						strRemotePath= gcnew String(ftpInfo->m_strServerSlash + ftpInfo->m_strServerDownloadFolder);

					String^ strTempFolder = gcnew String(m_strTempFolder + Path::DirectorySeparatorChar + ftpInfo->m_strConfigName);

				   /// get the orders list
					List<DirectoryListItem^>^ list;
					try
					{
						list = (List<DirectoryListItem^>^) ftpInfo->m_ftpsClient->GetDirectoryList (strRemotePath);
					}
					catch(Exception ^e)
					{
						return false;
					}

					String^ strFirstFileType = gcnew String(ftpInfo->m_ruleInfo->m_strFirstFileDownload);
					String^ strLastFileType = gcnew String(ftpInfo->m_ruleInfo->m_strLastFileDownload);
					String^ strSkipFileType = gcnew String(ftpInfo->m_ruleInfo->m_strSkipFileType);
					bool bSkipFileType = false;
					if(! String::IsNullOrEmpty (strSkipFileType))
						bSkipFileType = true;

					ArrayList^ arrDir = gcnew ArrayList();
					ArrayList^ arrFirst = gcnew ArrayList();
					ArrayList^ arrLast = gcnew ArrayList();
					ArrayList^ arrMiddle = gcnew ArrayList();

					/// for all the orders
					__int64 nSize = 0;
					for(int x=0; x< list->Count; x++)
					{
						if(bSkipFileType)
						{
							if(list[x]->Name->EndsWith (strSkipFileType, StringComparison ::CurrentCultureIgnoreCase))
								continue;
						}
						if(list[x]->IsDirectory)
						{
							arrDir->Add (list[x]->Name);
							continue;
						}

						/// check if the file is already downloaded
						 bool bContinue = false;
						if(! ftpInfo->m_ruleInfo ->m_bOverwrite)
						{
							for(int y = 0; y < ftpInfo->m_arrFiles ->Count; y++)
							{
								CFileInfo^ fInfo = (CFileInfo^) ftpInfo->m_arrFiles [y];
								if(fInfo->m_strFileName == list[x]->Name && fInfo->m_nSize == list[x]->Size)
								{
									m_logMutex->WaitOne ();
										m_swLog->WriteLine (strRemotePath + ": File: " + list[x]->Name + " already downloaded");
									m_logMutex->ReleaseMutex ();
									bContinue = true;
									break;
								}
							}
						}
						if(bContinue)
							continue;

						CFileInfo^ info = gcnew CFileInfo();
						info->m_strFileName = gcnew String(list[x]->Name);
						info->m_nSize = list[x]->Size;
						nSize += info->m_nSize;
						if(list[x]->Name->EndsWith (strFirstFileType, StringComparison ::CurrentCultureIgnoreCase) && !String::IsNullOrEmpty(strFirstFileType))
							arrFirst->Add (info);
						else if(list[x]->Name->EndsWith (strLastFileType, StringComparison ::CurrentCultureIgnoreCase) && !String::IsNullOrEmpty(strLastFileType))
							arrLast->Add (info);
						else
							arrMiddle->Add (info);
					}

					 String^ strDownloadName = gcnew String(Path::GetFileName (ftpInfo->m_strServerDownloadFolder));
					 if(String::IsNullOrEmpty (strDownloadName))
						 strDownloadName = ftpInfo->m_strServerSlash;

					/// download all files
					if(arrFirst->Count > 0 || arrLast->Count > 0 || arrMiddle->Count > 0)
					{
						/// check rules
						if(! String::IsNullOrEmpty (strFirstFileType))
						{
							if(arrFirst->Count == 0)
							{
								m_logMutex->WaitOne ();
									m_swLog->WriteLine (strDownloadName + ": First files are missing");
								m_logMutex->ReleaseMutex ();
								if(m_bWin32)
								SendMail("NVIFTP: Files missing", strDownloadName + ": First files are missing");
								return false;
							}
						}
						if(! String::IsNullOrEmpty (strLastFileType))
						{
							if(arrLast->Count == 0)
							{
								m_logMutex->WaitOne ();
									m_swLog->WriteLine (strDownloadName + ": Last files are missing");
								m_logMutex->ReleaseMutex ();
								if(m_bWin32)
								SendMail("NVIFTP: Files missing", strDownloadName + ": Last files are missing");
								return false;
							}
						}

					DateTime dtStart = DateTime ::Now;
					bool bError = false;
					//listProgress->Items ->Clear ();
					 try
					 {
						 unsigned __int64 nTransfered = 0;
						 /// get first files
						for(int i=0; i< arrFirst->Count ; i++)
						{
							CFileInfo^ info = (CFileInfo^) arrFirst[i];
							m_mutex->WaitOne ();
							 ListViewItem^ item = listProgress->Items ->Insert(getProgressListIndex(), info->m_strFileName);
							 listProgress ->Items[item->Index]->SubItems ->Add (ftpInfo->m_strConfigName);
							 listProgress ->Items[item->Index]->SubItems ->Add (info->m_nSize.ToString ());
							 listProgress ->Items[item->Index]->SubItems ->Add ("");
							 listProgress ->Items[item->Index]->SubItems ->Add ("");
							 listProgress ->Items[item->Index]->SubItems ->Add ("Downloading");
							 m_mutex->ReleaseMutex ();

							 ftpInfo->m_ftpsClient->SetFileName (info->m_strFileName);
							nTransfered = ftpInfo->m_ftpsClient->GetFile(strRemotePath + ftpInfo->m_strServerSlash + info->m_strFileName, strTempFolder + Path::DirectorySeparatorChar + info->m_strFileName, gcnew FileTransferCallback(TransferCallback));
							m_mutex->WaitOne ();
							listProgress ->Items[item->Index]->SubItems[5]->Text = "Downloaded";
							m_mutex->ReleaseMutex ();
							if(nTransfered != info->m_nSize)
							{
								m_logMutex->WaitOne ();
									m_swLog->WriteLine (info->m_strFileName + "transfer size does not match");
								m_logMutex->ReleaseMutex ();
								return false;
							}
							ftpInfo->m_arrFiles ->Add(info);
						}
						/// get middle files
						for(int i=0; i< arrMiddle->Count ; i++)
						{
							CFileInfo^ info = (CFileInfo^) arrMiddle[i];
							m_mutex->WaitOne ();
							 ListViewItem^ item = listProgress->Items ->Insert(getProgressListIndex(), info->m_strFileName);
							 listProgress ->Items[item->Index]->SubItems ->Add (ftpInfo->m_strConfigName);
							 listProgress ->Items[item->Index]->SubItems ->Add (info->m_nSize.ToString ());
							 listProgress ->Items[item->Index]->SubItems ->Add ("");
							 listProgress ->Items[item->Index]->SubItems ->Add ("");
							 listProgress ->Items[item->Index]->SubItems ->Add ("Downloading");
							 m_mutex->ReleaseMutex ();

							 ftpInfo->m_ftpsClient->SetFileName (info->m_strFileName);
							nTransfered = ftpInfo->m_ftpsClient->GetFile(strRemotePath + ftpInfo->m_strServerSlash + info->m_strFileName, strTempFolder + Path::DirectorySeparatorChar + info->m_strFileName, gcnew FileTransferCallback(TransferCallback));
							m_mutex->WaitOne ();
							listProgress ->Items[item->Index]->SubItems[5]->Text = "Downloaded";
							m_mutex->ReleaseMutex ();
							if(nTransfered != info->m_nSize)
							{
								m_logMutex->WaitOne ();
									m_swLog->WriteLine (info->m_strFileName + "transfer size does not match");
								m_logMutex->ReleaseMutex ();
								return false;
							}
							ftpInfo->m_arrFiles ->Add(info);
						}
						/// get last files
						for(int i=0; i< arrLast->Count ; i++)
						{
							CFileInfo^ info = (CFileInfo^) arrLast[i];
							m_mutex->WaitOne ();
							 ListViewItem^ item = listProgress->Items ->Insert(getProgressListIndex(), info->m_strFileName);
							 listProgress ->Items[item->Index]->SubItems ->Add (ftpInfo->m_strConfigName);
							 listProgress ->Items[item->Index]->SubItems ->Add (info->m_nSize.ToString ());
							 listProgress ->Items[item->Index]->SubItems ->Add ("");
							 listProgress ->Items[item->Index]->SubItems ->Add ("");
							 listProgress ->Items[item->Index]->SubItems ->Add ("Downloading");
							 m_mutex->ReleaseMutex ();

							 ftpInfo->m_ftpsClient->SetFileName (info->m_strFileName);
							nTransfered = ftpInfo->m_ftpsClient->GetFile(strRemotePath + ftpInfo->m_strServerSlash + info->m_strFileName, strTempFolder + Path::DirectorySeparatorChar + info->m_strFileName, gcnew FileTransferCallback(TransferCallback));
							m_mutex->WaitOne ();
							listProgress ->Items[item->Index]->SubItems[5]->Text = "Downloaded";
							m_mutex->ReleaseMutex ();
							if(nTransfered != info->m_nSize)
							{
								m_logMutex->WaitOne ();
									m_swLog->WriteLine (info->m_strFileName + "transfer size does not match");
								m_logMutex->ReleaseMutex ();
								return false;
							}
							ftpInfo->m_arrFiles ->Add(info);
						}

						/// move the files to dest folder
						for(int x=0; x< list->Count; x++)
						{
							if(list[x]->IsDirectory )
								continue;
							if(File::Exists (strTempFolder+Path::DirectorySeparatorChar+list[x]->Name))
							{
								File::Copy(strTempFolder + Path::DirectorySeparatorChar + list[x]->Name, ftpInfo->m_strLocalDownloadFolder + Path::DirectorySeparatorChar + list[x]->Name, true);
								File::Delete (strTempFolder + Path::DirectorySeparatorChar + list[x]->Name);
							}
						}

						/// delete the source
						if(ftpInfo->m_ruleInfo->m_bDeleteSource)
						{
							for(int x=0; x< list->Count; x++)
							{
								if(list[x]->IsDirectory )
									continue;
								ftpInfo->m_ftpsClient->DeleteFile (strRemotePath + ftpInfo->m_strServerSlash + list[x]->Name);
							}
						}
					 }
					 catch(Exception^ e)
					 {
						 bError = true;
						m_logMutex->WaitOne ();
							m_swLog->WriteLine (strDownloadName + ": Error: " + e->Message);
						m_logMutex->ReleaseMutex ();
						if(m_bWin32)
						 SendMail("NVIFTP: Error", e->Message);
						//return false;
					 }

					 DateTime dtEnd = DateTime ::Now;
					 //TimeSpan ts = dtEnd - dtStart;
					 String^ strTime = gcnew String(dtEnd.Day.ToString () + "-" + dtEnd.Month.ToString () + "-" + dtEnd.Year.ToString () + " " + dtEnd.Hour.ToString () + ":" + dtEnd.Minute.ToString () + ":" + dtEnd.Second.ToString ());

					 //ListViewItem^ item = listDone->Items ->Add (strDownloadName);
					 ListViewItem^ item = listDone->Items ->Insert(0, strDownloadName);
					 listDone ->Items[item->Index]->SubItems ->Add (ftpInfo->m_strConfigName);
					 listDone ->Items[item->Index]->SubItems ->Add (nSize.ToString ());
					 listDone ->Items[item->Index]->SubItems ->Add (strTime);
					 listDone ->Items[item->Index]->SubItems ->Add ("Download");
					 if(! bError )
					 {
						listDone ->Items[item->Index]->SubItems ->Add ("Success");
					 }
					 else
					 {
						listDone ->Items[item->Index]->SubItems ->Add ("Error");
						return false;
					 }
					}
					 
					 showConnectionParameters(ftpInfo);

					 /// download all orders
					 if(ftpInfo->m_ruleInfo->m_bRecursive)
					 {
					 for(int x=0; x< arrDir->Count; x++)
					 {
						 String^ strName = (String^)arrDir[x];
						 bool bContinue = false;
						 if(! ftpInfo->m_ruleInfo->m_bOverwrite)
						 {
							for(int i=0; i< ftpInfo->m_arrOrders ->Count; i++)
							{
								String^ str = (String^) ftpInfo->m_arrOrders [i];
								if(str == strName)
								{
									m_logMutex->WaitOne ();
										m_swLog->WriteLine ("Order: " + str + " already downloaded");
									m_logMutex->ReleaseMutex ();
									bContinue = true;
									break;
								}
							}
						 }
						if(bContinue)
							continue;

						DateTime dtStart = DateTime ::Now;
						//listProgress->Items ->Clear ();
						int nOrderSize = 0;
						 bool bRet = DownloadOrder(ftpInfo, strTempFolder, strRemotePath, strName, nOrderSize);

						 if(bRet)
						 	 bRet = MoveOrder(ftpInfo, strTempFolder, ftpInfo->m_strLocalDownloadFolder,  strName);
						 //DirectoryInfo ^ dirInfo = gcnew DirectoryInfo(m_ftpInfo->m_strLocalDownloadFolder + Path::DirectorySeparatorChar + (String^)arrDir[x]);
						 if(bRet)
							 ftpInfo->m_arrOrders ->Add(strName);

						 DateTime dtEnd = DateTime ::Now;
						 //TimeSpan ts = dtEnd - dtStart;
						 //String^ strTime = gcnew String(ts.Hours.ToString () + " : " + ts.Minutes.ToString () + " : " + ts.Seconds.ToString ());
						String^ strTime = gcnew String(dtEnd.Day.ToString () + "-" + dtEnd.Month.ToString () + "-" + dtEnd.Year.ToString () + " " + dtEnd.Hour.ToString () + ":" + dtEnd.Minute.ToString () + ":" + dtEnd.Second.ToString ());

						 //ListViewItem^ item = listDone->Items ->Add (strName);
						 ListViewItem^ item = listDone->Items ->Insert(0, strName);
						listDone ->Items[item->Index]->SubItems ->Add (ftpInfo->m_strConfigName);
						 listDone ->Items[item->Index]->SubItems ->Add (nOrderSize.ToString ());
						 listDone ->Items[item->Index]->SubItems ->Add (strTime);
						 listDone ->Items[item->Index]->SubItems ->Add ("Download");
						 if(bRet)
							listDone ->Items[item->Index]->SubItems ->Add ("Success");
						 else
							listDone ->Items[item->Index]->SubItems ->Add ("Error");
						 
						 showConnectionParameters(ftpInfo);
					 }
					 }
			   }

			   /// prasann : 19th mar 12
			   /// upload the orders without db support
	   private: bool UploadOrders(CFTPInfo^ ftpInfo)
				{
					String^ strRemotePath;
					//if(String::IsNullOrEmpty (m_ftpInfo->m_strServerUploadFolder))
					//	strRemotePath= gcnew String(m_ftpInfo->m_strServerSlash + m_ftpInfo->m_strServerWorkingDir);
					//else
					//	strRemotePath= gcnew String(m_ftpInfo->m_strServerSlash + m_ftpInfo->m_strServerWorkingDir + m_ftpInfo->m_strServerSlash + m_ftpInfo->m_strServerUploadFolder);
					if(ftpInfo->m_strServerUploadFolder->StartsWith (ftpInfo->m_strServerSlash))
						strRemotePath= gcnew String(ftpInfo->m_strServerUploadFolder);
					else
						strRemotePath= gcnew String(ftpInfo->m_strServerSlash + ftpInfo->m_strServerUploadFolder);

					if(Directory::Exists (ftpInfo->m_strLocalUploadFolder))
					{
						ArrayList arrDir = Directory ::GetDirectories (ftpInfo->m_strLocalUploadFolder);
						ArrayList arrFiles = Directory ::GetFiles (ftpInfo->m_strLocalUploadFolder);

						String^ strFirstFileType = gcnew String(ftpInfo->m_ruleInfo->m_strFirstFileUpload);
						String^ strLastFileType = gcnew String(ftpInfo->m_ruleInfo->m_strLastFileUpload);
						String^ strSkipFileType = gcnew String(ftpInfo->m_ruleInfo->m_strSkipFileType);
						bool bSkipFileType = false;
						if(! String::IsNullOrEmpty (strSkipFileType))
							bSkipFileType = true;
						if(String::IsNullOrEmpty (ftpInfo->m_ruleInfo->m_strLastFileUpload))
						{
							m_logMutex->WaitOne ();
								m_swLog->WriteLine (ftpInfo->m_ruleInfo->m_strRuleName + ": Last file type is empty");
							m_logMutex->ReleaseMutex ();
							if(m_bWin32)
							SendMail("NVIFTP: Rule issue", ftpInfo->m_ruleInfo->m_strRuleName + ": Last file type is empty");
							return false;
						}
						
						ArrayList^ arrFirst = gcnew ArrayList();
						ArrayList^ arrLast = gcnew ArrayList();
						ArrayList^ arrMiddle = gcnew ArrayList();
						
						__int64 nSize = 0;
						for(int x=0; x< arrFiles.Count; x++)
						{
							String^ strName = (String^) arrFiles[x];

							if(bSkipFileType)
							{
								if(strName->EndsWith (strSkipFileType, StringComparison ::CurrentCultureIgnoreCase))
									continue;
							}

							FileInfo^ fileInfo = gcnew FileInfo(strName);

							/// check if the file is already uploaded
							 bool bContinue = false;
							if(! ftpInfo->m_ruleInfo ->m_bOverwrite)
							{
								for(int y = 0; y < ftpInfo->m_arrFiles ->Count; y++)
								{
									CFileInfo^ fInfo = (CFileInfo^) ftpInfo->m_arrFiles [y];
									if(fInfo->m_strFileName == strName && fInfo->m_nSize == fileInfo->Length)
									{
										m_logMutex->WaitOne ();
											m_swLog->WriteLine (ftpInfo->m_strLocalUploadFolder + ": File: " + strName + " already uploaded");
										m_logMutex->ReleaseMutex ();
										bContinue = true;
										break;
									}
								}
							}
							if(bContinue)
								continue;

							CFileInfo^ info = gcnew CFileInfo();
							info->m_strFileName = gcnew String(strName);
							info->m_nSize = fileInfo->Length;
							nSize += info->m_nSize;
							if(strName->EndsWith (strFirstFileType, StringComparison ::CurrentCultureIgnoreCase) && !String::IsNullOrEmpty(strFirstFileType))
								arrFirst->Add (info);
							else if(strName->EndsWith (strLastFileType, StringComparison ::CurrentCultureIgnoreCase) && !String::IsNullOrEmpty(strLastFileType))
								arrLast->Add (info);
							else
								arrMiddle->Add (info);
						}

						String^ strUploadName = gcnew String(Path::GetFileName (ftpInfo->m_strLocalUploadFolder));
						if(String::IsNullOrEmpty (strUploadName))
							strUploadName = ftpInfo->m_strLocalUploadFolder;

						/// upload all files
						if(arrFirst->Count > 0 || arrLast->Count > 0 || arrMiddle->Count > 0)
						{
							/// check rules
							if(! String::IsNullOrEmpty (strFirstFileType))
							{
								if(arrFirst->Count == 0)
								{
									m_logMutex->WaitOne ();
										m_swLog->WriteLine (strUploadName + ": First files are missing");
									m_logMutex->ReleaseMutex ();
									if(m_bWin32)
									SendMail("NVIFTP: Files missing", strUploadName + ": First files are missing");
									return false;
								}
							}
							if(! String::IsNullOrEmpty (strLastFileType))
							{
								if(arrLast->Count == 0)
								{
									m_logMutex->WaitOne ();
										m_swLog->WriteLine (strUploadName + ": Last files are missing");
									m_logMutex->ReleaseMutex ();
									if(m_bWin32)
									SendMail("NVIFTP: Files missing", strUploadName + ": First files are missing");
									return false;
								}
							}

						DateTime dtStart = DateTime ::Now;
						bool bError = false;
						//listProgress->Items ->Clear ();
						 try
						 {
							 unsigned __int64 nTransfered = 0;
							 /// put first files
							for(int i=0; i< arrFirst->Count ; i++)
							{
								CFileInfo^ info = (CFileInfo^) arrFirst[i];
								String^ strName = Path::GetFileName(info->m_strFileName);
								m_mutex->WaitOne ();
								ListViewItem^ item = listProgress->Items ->Insert(getProgressListIndex(), strName);
								 listProgress ->Items[item->Index]->SubItems ->Add (ftpInfo->m_strConfigName);
								 listProgress ->Items[item->Index]->SubItems ->Add (info->m_nSize.ToString ());
								 listProgress ->Items[item->Index]->SubItems ->Add ("");
								 listProgress ->Items[item->Index]->SubItems ->Add ("");
								 listProgress ->Items[item->Index]->SubItems ->Add ("Uploading");
								 m_mutex->ReleaseMutex ();

							 ftpInfo->m_ftpsClient->SetFileName (strName);
								//m_ftpsClient->GetFile(strRemotePath + m_ftpInfo->m_strServerSlash + info->m_strFileName, m_ftpInfo->m_strLocalDownloadFolder + Path::DirectorySeparatorChar + info->m_strFileName, gcnew FileTransferCallback(TransferCallback));
								nTransfered = ftpInfo->m_ftpsClient->PutFile(info->m_strFileName, strRemotePath + ftpInfo->m_strServerSlash + strName, gcnew FileTransferCallback(TransferCallback));
								m_mutex->WaitOne ();
								listProgress ->Items[item->Index]->SubItems[5]->Text = "Uploaded";
								m_mutex->ReleaseMutex ();
								if(nTransfered != info->m_nSize)
								{
									m_logMutex->WaitOne ();
										m_swLog->WriteLine (strName + "transfer size does not match");
									m_logMutex->ReleaseMutex ();
									return false;
								}
								ftpInfo->m_arrFiles ->Add(info);
							}
							/// put middle files
							for(int i=0; i< arrMiddle->Count ; i++)
							{
								CFileInfo^ info = (CFileInfo^) arrMiddle[i];
								String^ strName = Path::GetFileName(info->m_strFileName);
								m_mutex->WaitOne ();
								 ListViewItem^ item = listProgress->Items ->Insert(getProgressListIndex(), strName);
								 listProgress ->Items[item->Index]->SubItems ->Add (ftpInfo->m_strConfigName);
								 listProgress ->Items[item->Index]->SubItems ->Add (info->m_nSize.ToString ());
								 listProgress ->Items[item->Index]->SubItems ->Add ("");
								 listProgress ->Items[item->Index]->SubItems ->Add ("");
								 listProgress ->Items[item->Index]->SubItems ->Add ("Uploading");
								m_mutex->ReleaseMutex ();

							 ftpInfo->m_ftpsClient->SetFileName (strName);
								nTransfered = ftpInfo->m_ftpsClient->PutFile(info->m_strFileName, strRemotePath + ftpInfo->m_strServerSlash + strName, gcnew FileTransferCallback(TransferCallback));
								m_mutex->WaitOne ();
								listProgress ->Items[item->Index]->SubItems[5]->Text = "Uploaded";
								m_mutex->ReleaseMutex ();
								if(nTransfered != info->m_nSize)
								{
									m_logMutex->WaitOne ();
										m_swLog->WriteLine (strName + "transfer size does not match");
									m_logMutex->ReleaseMutex ();
									return false;
								}
								ftpInfo->m_arrFiles ->Add(info);
							}
							/// put last files
							for(int i=0; i< arrLast->Count ; i++)
							{
								CFileInfo^ info = (CFileInfo^) arrLast[i];
								String^ strName = Path::GetFileName(info->m_strFileName);
								m_mutex->WaitOne ();
								 ListViewItem^ item = listProgress->Items ->Insert(getProgressListIndex(), strName);
								 listProgress ->Items[item->Index]->SubItems ->Add (ftpInfo->m_strConfigName);
								 listProgress ->Items[item->Index]->SubItems ->Add (info->m_nSize.ToString ());
								 listProgress ->Items[item->Index]->SubItems ->Add ("");
								 listProgress ->Items[item->Index]->SubItems ->Add ("");
								 listProgress ->Items[item->Index]->SubItems ->Add ("Uploading");
								m_mutex->ReleaseMutex ();

							 ftpInfo->m_ftpsClient->SetFileName (strName);
								nTransfered = ftpInfo->m_ftpsClient->PutFile(info->m_strFileName, strRemotePath + ftpInfo->m_strServerSlash + strName, gcnew FileTransferCallback(TransferCallback));
								m_mutex->WaitOne ();
								listProgress ->Items[item->Index]->SubItems[5]->Text = "Uploaded";
								m_mutex->ReleaseMutex ();
								if(nTransfered != info->m_nSize)
								{
									m_logMutex->WaitOne ();
										m_swLog->WriteLine (strName + "transfer size does not match");
									m_logMutex->ReleaseMutex ();
									return false;
								}
								ftpInfo->m_arrFiles ->Add(info);
							}

							/// delete the source
							if(ftpInfo->m_ruleInfo->m_bDeleteSource)
							{
								for(int x = 0; x < arrFiles.Count ; x++) 
								{
									File::Delete ((String^) arrFiles[x]);
								}
							}
						 }
						 catch(Exception^ e)
						 {
							 bError = true;
							m_logMutex->WaitOne ();
								m_swLog->WriteLine (strUploadName + ": Error: " + e->Message);
							m_logMutex->ReleaseMutex ();
							if(m_bWin32)
							SendMail("NVIFTP: Error", e->Message);
							//return false;
						 }

						 DateTime dtEnd = DateTime ::Now;
						 //TimeSpan ts = dtEnd - dtStart;
						 //String^ strTime = gcnew String(ts.Hours.ToString () + " : " + ts.Minutes.ToString () + " : " + ts.Seconds.ToString ());
						String^ strTime = gcnew String(dtEnd.Day.ToString () + "-" + dtEnd.Month.ToString () + "-" + dtEnd.Year.ToString () + " " + dtEnd.Hour.ToString () + ":" + dtEnd.Minute.ToString () + ":" + dtEnd.Second.ToString ());

						 //ListViewItem^ item = listDone->Items ->Add (strUploadName);
						 ListViewItem^ item = listDone->Items ->Insert(0, strUploadName);
						listDone ->Items[item->Index]->SubItems ->Add (ftpInfo->m_strConfigName);
						 listDone ->Items[item->Index]->SubItems ->Add (nSize.ToString ());
						 listDone ->Items[item->Index]->SubItems ->Add (strTime);
						 listDone ->Items[item->Index]->SubItems ->Add ("Upload");
						 if(! bError)
						 {
							listDone ->Items[item->Index]->SubItems ->Add ("Success");
						 }
						 else
						 {
							listDone ->Items[item->Index]->SubItems ->Add ("Error");
							return false;
						 }
						}
						 
						 showConnectionParameters(ftpInfo);

						 /// upload all orders
						 if(ftpInfo->m_ruleInfo->m_bRecursive)
						 {
						 for(int x=0; x< arrDir.Count; x++)
						 {
							String^ strName = Path::GetFileName((String^)arrDir[x]);

							bool bContinue = false;
							if(! ftpInfo->m_ruleInfo ->m_bOverwrite)
							{
								for(int i=0; i< ftpInfo->m_arrOrders ->Count; i++)
								{
									String^ str = (String^) ftpInfo->m_arrOrders [i];
									if(str == strName)
									{
										m_logMutex->WaitOne ();
											m_swLog->WriteLine ("Order " + str + " already uploaded");
										m_logMutex->ReleaseMutex ();
										bContinue = true;
										break;
									}
								}
							}
							if(bContinue)
								continue;

							DateTime dtStart = DateTime ::Now;
							//listProgress->Items ->Clear ();

							int nOrderSize = 0;
							bool bRet = UploadOrder(ftpInfo, ftpInfo->m_strLocalUploadFolder, strRemotePath, strName, nOrderSize, "");

							 //if(bRet)
							 //	 bRet = MoveOrder(m_strLocalFolder, m_strDestFolder,  ObjDn->m_strOrderID);
							if(bRet)
								ftpInfo->m_arrOrders ->Add (strName);

							 DateTime dtEnd = DateTime ::Now;
							 //TimeSpan ts = dtEnd - dtStart;
							 //String^ strTime = gcnew String(ts.Hours.ToString () + " : " + ts.Minutes.ToString () + " : " + ts.Seconds.ToString ());
							String^ strTime = gcnew String(dtEnd.Day.ToString () + "-" + dtEnd.Month.ToString () + "-" + dtEnd.Year.ToString () + " " + dtEnd.Hour.ToString () + ":" + dtEnd.Minute.ToString () + ":" + dtEnd.Second.ToString ());

							 //ListViewItem^ item = listDone->Items ->Add (strName);
							 ListViewItem^ item = listDone->Items ->Insert(0, strName);
							listDone ->Items[item->Index]->SubItems ->Add (ftpInfo->m_strConfigName);
							 listDone ->Items[item->Index]->SubItems ->Add (nOrderSize.ToString ());
							 listDone ->Items[item->Index]->SubItems ->Add (strTime);
							 listDone ->Items[item->Index]->SubItems ->Add ("Upload");
							 if(bRet)
								listDone ->Items[item->Index]->SubItems ->Add ("Success");
							 else
								listDone ->Items[item->Index]->SubItems ->Add ("Error");
							 
							 showConnectionParameters(ftpInfo);
						 }
						 }
					}
					else
					{
						m_logMutex->WaitOne ();
							m_swLog->WriteLine (ftpInfo->m_strLocalUploadFolder + " directory does not exist");
						m_logMutex->ReleaseMutex ();
						return false;
					}

				}

			  /// prasann : 13th mar 12
			  /// download the orders
	  private: bool DownloadOrdersDB(CFTPInfo^ ftpInfo)
			   {
				   String^ strConnString = gcnew String("Dsn=" + ftpInfo->m_dbInfo->m_strDsn + ";Uid=" + ftpInfo->m_dbInfo->m_strUid + ";Pwd=" + ftpInfo->m_dbInfo->m_strPwd + ";");
				   String^ strQuery = gcnew String("select " + ftpInfo->m_dbInfo->m_strFields + " from " +
					   ftpInfo->m_dbInfo->m_strTable + " where " + ftpInfo->m_dbInfo->m_strWhere);

				   /// code taken from FtpDownloadApp
					OdbcConnection^ conn;
					OdbcDataReader^ dr;

					try
					{
						conn = gcnew OdbcConnection(strConnString);
						//dr = gcnew OdbcDataReader ();
						OdbcCommand^ commandSourceData = gcnew OdbcCommand(strQuery, conn);
						conn->Open();
						dr = commandSourceData->ExecuteReader();
					}
					catch(OdbcException^ e)
					{
						//MessageBox::Show (e->Message);
						m_logMutex->WaitOne ();
							m_swLog->WriteLine (ftpInfo->m_dbInfo->m_strDBConnName + ": " + e->Message);
						m_logMutex->ReleaseMutex ();
						return false;
					}

					ArrayList^ DnOrder = gcnew ArrayList();
	                
					while (dr->Read())
					{
						String^ strOrderid = dr->GetString(0);
						String^ strOrderFolder = dr->GetString(0);
						//String^[] OrderFolderStruct = strOrderFolder.Split('\\');

						//String^ strSourceFolder = gcnew String(m_ftpInfo->m_strServerSlash + m_ftpInfo->m_strServerWorkingDir + m_ftpInfo->m_strServerSlash + strOrderFolder);
						String^ strSourceFolder;
						if(ftpInfo->m_strServerDownloadFolder->StartsWith (ftpInfo->m_strServerSlash))
							strSourceFolder = gcnew String(ftpInfo->m_strServerDownloadFolder + ftpInfo->m_strServerSlash + strOrderFolder);
						else
							strSourceFolder = gcnew String(ftpInfo->m_strServerSlash + ftpInfo->m_strServerDownloadFolder + ftpInfo->m_strServerSlash + strOrderFolder);

						COrders^ objOrder = gcnew COrders();

						objOrder->m_strOrderFoldStruct = strSourceFolder->Substring(1, strSourceFolder->Length - 1);
						objOrder->m_strOrderSubFolder = strOrderFolder;
						objOrder->m_strOrderID = strOrderid;
						DnOrder->Add(objOrder);
					}
					conn->Close();

					return StartDownloadOrder(ftpInfo, DnOrder);
			   }

			 /// prasann : 14th mar 12
	private: bool StartDownloadOrder(CFTPInfo^ ftpInfo, ArrayList^ arrOrders)
        {
			String^ strRemotePath;
			String^ strTempFolder = gcnew String(m_strTempFolder + Path::DirectorySeparatorChar + ftpInfo->m_strConfigName);

            for each (COrders^ ObjDn in arrOrders)
            {
				bool bContinue = false;
				if(! ftpInfo->m_ruleInfo->m_bOverwrite)
				{
					for(int i=0; i< ftpInfo->m_arrOrders ->Count; i++)
					{
						String^ str = (String^) ftpInfo->m_arrOrders [i];
						if(str == ObjDn->m_strOrderID)
						{
							m_logMutex->WaitOne ();
								m_swLog->WriteLine ("Order: " + str + " already downloaded");
							m_logMutex->ReleaseMutex ();
							bContinue = true;
							break;
						}
					}
				}
				if(bContinue)
					continue;

				 DateTime dtStart = DateTime ::Now;

				 //listProgress->Items ->Clear ();

				 //if(String::IsNullOrEmpty (m_ftpInfo->m_strServerDownloadFolder))
					//strRemotePath = gcnew String(m_ftpInfo->m_strServerSlash + m_ftpInfo->m_strServerWorkingDir);
				 //else
					//strRemotePath = gcnew String(m_ftpInfo->m_strServerSlash + m_ftpInfo->m_strServerWorkingDir + m_ftpInfo->m_strServerSlash + m_ftpInfo->m_strServerDownloadFolder);
				 if(ftpInfo->m_strServerDownloadFolder->StartsWith (ftpInfo->m_strServerSlash))
					 strRemotePath = gcnew String(ftpInfo->m_strServerDownloadFolder);
				 else
					 strRemotePath = gcnew String(ftpInfo->m_strServerSlash + ftpInfo->m_strServerDownloadFolder);

				 int nOrderSize = 0;
				 bool bRet = DownloadOrder(ftpInfo, strTempFolder, strRemotePath, ObjDn->m_strOrderID, nOrderSize);

				 if(bRet)
					 bRet = MoveOrder(ftpInfo, strTempFolder, ftpInfo->m_strLocalDownloadFolder,  ObjDn->m_strOrderID);
				 if(bRet)
				 {
					 ftpInfo->m_arrOrders ->Add (ObjDn->m_strOrderID);
				 }
				 
				 DateTime dtEnd = DateTime ::Now;
				 //TimeSpan ts = dtEnd - dtStart;
				 //String^ strTime = gcnew String(ts.Hours.ToString () + " : " + ts.Minutes.ToString () + " : " + ts.Seconds.ToString ());
				 String^ strTime = gcnew String(dtEnd.Day.ToString () + "-" + dtEnd.Month.ToString () + "-" + dtEnd.Year.ToString () + " " + dtEnd.Hour.ToString () + ":" + dtEnd.Minute.ToString () + ":" + dtEnd.Second.ToString ());

				 //ListViewItem^ item = listDone->Items ->Add (ObjDn->m_strOrderID);
				 ListViewItem^ item = listDone->Items ->Insert(0, ObjDn->m_strOrderID);
				 listDone ->Items[item->Index]->SubItems ->Add (ftpInfo->m_strConfigName);
				 listDone ->Items[item->Index]->SubItems ->Add (nOrderSize.ToString ());
				 listDone ->Items[item->Index]->SubItems ->Add (strTime);
				 listDone ->Items[item->Index]->SubItems ->Add ("Download");
				 if(bRet)
					listDone ->Items[item->Index]->SubItems ->Add ("Success");
				 else
					listDone ->Items[item->Index]->SubItems ->Add ("Error");
				 
				 showConnectionParameters(ftpInfo);
			}
			return true;
		}

			  /// prasann : 31st mar 12
			  /// upload the orders
	  private: bool UploadOrdersDB(CFTPInfo^ ftpInfo)
			   {
				   String^ strConnString = gcnew String("Dsn=" + ftpInfo->m_dbInfo->m_strDsn + ";Uid=" + ftpInfo->m_dbInfo->m_strUid + ";Pwd=" + ftpInfo->m_dbInfo->m_strPwd + ";");
				   String^ strQuery = gcnew String("select " + ftpInfo->m_dbInfo->m_strFields + " from " +
					   ftpInfo->m_dbInfo->m_strTable + " where " + ftpInfo->m_dbInfo->m_strWhere);

				   /// code taken from FtpDownloadApp
					OdbcConnection^ conn;
					OdbcDataReader^ dr;

					try
					{
						conn = gcnew OdbcConnection(strConnString);
						//dr = gcnew OdbcDataReader ();
						OdbcCommand^ commandSourceData = gcnew OdbcCommand(strQuery, conn);
						conn->Open();
						dr = commandSourceData->ExecuteReader();
					}
					catch(OdbcException^ e)
					{
						//MessageBox::Show (e->Message);
						m_logMutex->WaitOne ();
							m_swLog->WriteLine (ftpInfo->m_dbInfo->m_strDBConnName + ": " + e->Message);
						m_logMutex->ReleaseMutex ();
						return false;
					}

					ArrayList^ UpOrder = gcnew ArrayList();
	                
					while (dr->Read())
					{
						String^ strOrderid = dr->GetString(0);
						String^ strOrderFolder = dr->GetString(0);

						//String^ strSourceFolder;
						//if(m_ftpInfo->m_strServerDownloadFolder->StartsWith (m_ftpInfo->m_strServerSlash))
						//	strSourceFolder = gcnew String(m_ftpInfo->m_strServerDownloadFolder + m_ftpInfo->m_strServerSlash + strOrderFolder);
						//else
						//	strSourceFolder = gcnew String(m_ftpInfo->m_strServerSlash + m_ftpInfo->m_strServerDownloadFolder + m_ftpInfo->m_strServerSlash + strOrderFolder);

						COrders^ objOrder = gcnew COrders();

						//objOrder->m_strOrderFoldStruct = strSourceFolder->Substring(1, strSourceFolder->Length - 1);
						//objOrder->m_strOrderSubFolder = strOrderFolder;
						objOrder->m_strOrderID = strOrderid;
						UpOrder->Add(objOrder);
					}
					conn->Close();

					return StartUploadOrder(ftpInfo, UpOrder);
			   }

			 /// prasann : 31st mar 12
	private: bool StartUploadOrder(CFTPInfo^ ftpInfo, ArrayList^ arrOrders)
        {
			String^ strRemotePath;
            for each (COrders^ ObjDn in arrOrders)
            {
				bool bContinue = false;
				if(! ftpInfo->m_ruleInfo->m_bOverwrite)
				{
					for(int i=0; i< ftpInfo->m_arrOrders ->Count; i++)
					{
						String^ str = (String^) ftpInfo->m_arrOrders [i];
						if(str == ObjDn->m_strOrderID)
						{
							m_logMutex->WaitOne ();
								m_swLog->WriteLine ("Order: " + str + " already uploaded");
							m_logMutex->ReleaseMutex ();
							bContinue = true;
							break;
						}
					}
				}
				if(bContinue)
					continue;

				 DateTime dtStart = DateTime ::Now;

				 //listProgress->Items ->Clear ();

				if(ftpInfo->m_strServerUploadFolder->StartsWith (ftpInfo->m_strServerSlash))
					strRemotePath= gcnew String(ftpInfo->m_strServerUploadFolder);
				else
					strRemotePath= gcnew String(ftpInfo->m_strServerSlash + ftpInfo->m_strServerUploadFolder);

				 int nOrderSize = 0;
				 bool bRet = UploadOrder(ftpInfo, ftpInfo->m_strLocalUploadFolder, strRemotePath, ObjDn->m_strOrderID, nOrderSize, "");
				 //bool bRet = DownloadOrder(strTempFolder, strRemotePath, ObjDn->m_strOrderID, nOrderSize);

				 //if(bRet)
				//	 bRet = MoveOrder(strTempFolder, m_ftpInfo->m_strLocalDownloadFolder,  ObjDn->m_strOrderID);
				 if(bRet)
				 {
					 ftpInfo->m_arrOrders ->Add (ObjDn->m_strOrderID);
				 }
				 
				 DateTime dtEnd = DateTime ::Now;
				 //TimeSpan ts = dtEnd - dtStart;
				 //String^ strTime = gcnew String(ts.Hours.ToString () + " : " + ts.Minutes.ToString () + " : " + ts.Seconds.ToString ());
				 String^ strTime = gcnew String(dtEnd.Day.ToString () + "-" + dtEnd.Month.ToString () + "-" + dtEnd.Year.ToString () + " " + dtEnd.Hour.ToString () + ":" + dtEnd.Minute.ToString () + ":" + dtEnd.Second.ToString ());

				 ListViewItem^ item = listDone->Items ->Insert(0, ObjDn->m_strOrderID);
				 listDone ->Items[item->Index]->SubItems ->Add (ftpInfo->m_strConfigName);
				 listDone ->Items[item->Index]->SubItems ->Add (nOrderSize.ToString ());
				 listDone ->Items[item->Index]->SubItems ->Add (strTime);
				 listDone ->Items[item->Index]->SubItems ->Add ("Upload");
				 if(bRet)
					listDone ->Items[item->Index]->SubItems ->Add ("Success");
				 else
					listDone ->Items[item->Index]->SubItems ->Add ("Error");
				 
				 showConnectionParameters(ftpInfo);
			}
			return true;
		}

			 /// prasann : 14th mar 12
			 /// download the order according to the current rules
 private: bool DownloadOrder(CFTPInfo^ ftpInfo, String^ strLocalPath, String^ strRemotePath, String^ strOrderID, int % nOrderSize)
		  {
				String^ strRemoteOrderPath = gcnew String(strRemotePath +
					 ftpInfo->m_strServerSlash + strOrderID);

				String^ strFirstFileType = gcnew String(ftpInfo->m_ruleInfo->m_strFirstFileDownload);
				String^ strLastFileType = gcnew String(ftpInfo->m_ruleInfo->m_strLastFileDownload);
				String^ strSkipFileType = gcnew String(ftpInfo->m_ruleInfo->m_strSkipFileType);
				bool bSkipFileType = false;
				if(! String::IsNullOrEmpty (strSkipFileType))
					bSkipFileType = true;

				ArrayList^ arrFirst = gcnew ArrayList ();
				ArrayList^ arrMiddle = gcnew ArrayList ();
				ArrayList^ arrLast = gcnew ArrayList ();
				ArrayList^ arrDir = gcnew ArrayList();
				List<DirectoryListItem^>^ list;
				try
				{
					list = (List<DirectoryListItem^>^) ftpInfo->m_ftpsClient->GetDirectoryList (strRemoteOrderPath);
				}
				catch(Exception ^e)
				{
					m_logMutex->WaitOne ();
						m_swLog->WriteLine (strOrderID + ": Error: " + e->Message);
					m_logMutex->ReleaseMutex ();
					if(m_bWin32)
					SendMail("NVIFTP: Error", e->Message);
					return false;
				}

				/// separate out the first/last file types to be downloaded
				for(int x=0; x< list->Count; x++)
				{
					if(bSkipFileType)
					{
						if(list[x]->Name->EndsWith (strSkipFileType, StringComparison ::CurrentCultureIgnoreCase))
							continue;
					}
					if(list[x]->IsDirectory)
					{
						arrDir->Add (list[x]->Name);
						continue;
					}
					CFileInfo^ info = gcnew CFileInfo();
					info->m_strFileName = gcnew String(list[x]->Name);
					info->m_nSize = list[x]->Size;
					if(list[x]->Name->EndsWith (strFirstFileType, StringComparison ::CurrentCultureIgnoreCase) && !String::IsNullOrEmpty(strFirstFileType))
					{
						arrFirst->Add (info);
					}
					else if(list[x]->Name->EndsWith (strLastFileType, StringComparison ::CurrentCultureIgnoreCase) && !String::IsNullOrEmpty(strLastFileType))
					{
						arrLast->Add (info);
					}
					else
					{
						arrMiddle->Add (info);
					}
				}

				/// check rules
				if(! String::IsNullOrEmpty (strFirstFileType))
				{
					if(arrFirst->Count == 0)
					{
						m_logMutex->WaitOne ();
							m_swLog->WriteLine (strOrderID + ": First files are missing");
						m_logMutex->ReleaseMutex ();
						if(m_bWin32)
						SendMail("NVIFTP: Files missing", strOrderID + ": First files are missing");
						return false;
					}
				}
				if(! String::IsNullOrEmpty (strLastFileType))
				{
					if(arrLast->Count == 0)
					{
						m_logMutex->WaitOne ();
							m_swLog->WriteLine (strOrderID + ": Last files are missing");
						m_logMutex->ReleaseMutex ();
						if(m_bWin32)
						SendMail("NVIFTP: Files missing", strOrderID + ": Last files are missing");
						return false;
					}
				}

				if(/*! bSkipFileType && arrFirst->Count == 0 && arrLast->Count == 0*/0) /// download all files
				{
					 try
					 {
						 String^ strLocalFolder = gcnew String(strLocalPath + Path::DirectorySeparatorChar + strOrderID);
						 Directory::CreateDirectory (strLocalFolder);
						ftpInfo->m_ftpsClient->GetFiles(strRemoteOrderPath, strLocalFolder, "*", EPatternStyle::Wildcard, ftpInfo->m_ruleInfo->m_bRecursive, nullptr);
					 }
					 catch(Exception^ e)
					 {
						return false;
					 }
				}
				else /// download in order: first, middle, last
				{
					String^ strLocalFolder;

					/// create folder
					 try
					 {
						 strLocalFolder = gcnew String(strLocalPath + Path::DirectorySeparatorChar + strOrderID);
						 Directory::CreateDirectory (strLocalFolder);
					 }
					 catch(Exception^ e)
					 {
						m_logMutex->WaitOne ();
							m_swLog->WriteLine (strLocalFolder + " create directory failed");
						m_logMutex->ReleaseMutex ();
						return false;
					 }

					 unsigned __int64 nTransfered = 0;
					 try
					 {
						 /// get first files
						for(int i=0; i< arrFirst->Count ; i++)
						{
							CFileInfo^ info = (CFileInfo^) arrFirst[i];
							if(!ftpInfo->m_ruleInfo->m_bOverwrite)
							{
								if(File::Exists (strLocalFolder + Path::DirectorySeparatorChar + info->m_strFileName))
								{
									FileInfo^ fInfo = gcnew FileInfo(strLocalFolder + Path::DirectorySeparatorChar + info->m_strFileName);
									if(fInfo->Length == info->m_nSize)
										continue;
								}
							}
							m_mutex->WaitOne ();
							 ListViewItem^ item = listProgress->Items ->Insert(getProgressListIndex(), info->m_strFileName);
							 listProgress ->Items[item->Index]->SubItems ->Add (ftpInfo->m_strConfigName);
							 listProgress ->Items[item->Index]->SubItems ->Add (info->m_nSize.ToString ());
							 listProgress ->Items[item->Index]->SubItems ->Add ("");
							 listProgress ->Items[item->Index]->SubItems ->Add ("");
							 listProgress ->Items[item->Index]->SubItems ->Add ("Downloading");
							 m_mutex->ReleaseMutex ();

							 ftpInfo->m_ftpsClient->SetFileName (info->m_strFileName);
							nTransfered = ftpInfo->m_ftpsClient->GetFile(strRemoteOrderPath + ftpInfo->m_strServerSlash + info->m_strFileName, strLocalFolder + Path::DirectorySeparatorChar + info->m_strFileName, gcnew FileTransferCallback(TransferCallback));
							m_mutex->WaitOne ();
							listProgress ->Items[item->Index]->SubItems[5]->Text = "Downloaded";
							m_mutex->ReleaseMutex ();
							if(nTransfered != info->m_nSize)
							{
								m_logMutex->WaitOne ();
									m_swLog->WriteLine (info->m_strFileName + "transfer size does not match");
								m_logMutex->ReleaseMutex ();
								return false;
							}
							nOrderSize += info->m_nSize;
						}
						/// get middle files
						for(int i=0; i< arrMiddle->Count ; i++)
						{
							CFileInfo^ info = (CFileInfo^) arrMiddle[i];
							if(!ftpInfo->m_ruleInfo->m_bOverwrite)
							{
								if(File::Exists (strLocalFolder + Path::DirectorySeparatorChar + info->m_strFileName))
								{
									FileInfo^ fInfo = gcnew FileInfo(strLocalFolder + Path::DirectorySeparatorChar + info->m_strFileName);
									if(fInfo->Length == info->m_nSize)
										continue;
								}
							}
							m_mutex->WaitOne ();
							 ListViewItem^ item = listProgress->Items ->Insert(getProgressListIndex(), info->m_strFileName);
							 listProgress ->Items[item->Index]->SubItems ->Add (ftpInfo->m_strConfigName);
							 listProgress ->Items[item->Index]->SubItems ->Add (info->m_nSize.ToString ());
							 listProgress ->Items[item->Index]->SubItems ->Add ("");
							 listProgress ->Items[item->Index]->SubItems ->Add ("");
							 listProgress ->Items[item->Index]->SubItems ->Add ("Downloading");
							 m_mutex->ReleaseMutex ();

							 ftpInfo->m_ftpsClient->SetFileName (info->m_strFileName);
							nTransfered = ftpInfo->m_ftpsClient->GetFile(strRemoteOrderPath + ftpInfo->m_strServerSlash + info->m_strFileName, strLocalFolder + Path::DirectorySeparatorChar + info->m_strFileName, gcnew FileTransferCallback(TransferCallback));
							m_mutex->WaitOne ();
							listProgress ->Items[item->Index]->SubItems[5]->Text = "Downloaded";
							m_mutex->ReleaseMutex ();
							if(nTransfered != info->m_nSize)
							{
								m_logMutex->WaitOne ();
									m_swLog->WriteLine (info->m_strFileName + "transfer size does not match");
								m_logMutex->ReleaseMutex ();
								return false;
							}
							nOrderSize += info->m_nSize;
						}
						/// get last files
						for(int i=0; i< arrLast->Count ; i++)
						{
							CFileInfo^ info = (CFileInfo^) arrLast[i];
							if(!ftpInfo->m_ruleInfo->m_bOverwrite)
							{
								if(File::Exists (strLocalFolder + Path::DirectorySeparatorChar + info->m_strFileName))
								{
									FileInfo^ fInfo = gcnew FileInfo(strLocalFolder + Path::DirectorySeparatorChar + info->m_strFileName);
									if(fInfo->Length == info->m_nSize)
										continue;
								}
							}
							m_mutex->WaitOne ();
							 ListViewItem^ item = listProgress->Items ->Insert(getProgressListIndex(), info->m_strFileName);
							 listProgress ->Items[item->Index]->SubItems ->Add (ftpInfo->m_strConfigName);
							 listProgress ->Items[item->Index]->SubItems ->Add (info->m_nSize.ToString ());
							 listProgress ->Items[item->Index]->SubItems ->Add ("");
							 listProgress ->Items[item->Index]->SubItems ->Add ("");
							 listProgress ->Items[item->Index]->SubItems ->Add ("Downloading");
							 m_mutex->ReleaseMutex ();

							 ftpInfo->m_ftpsClient->SetFileName (info->m_strFileName);
							nTransfered = ftpInfo->m_ftpsClient->GetFile(strRemoteOrderPath + ftpInfo->m_strServerSlash + info->m_strFileName, strLocalFolder + Path::DirectorySeparatorChar + info->m_strFileName, gcnew FileTransferCallback(TransferCallback));
							m_mutex->WaitOne ();
							listProgress ->Items[item->Index]->SubItems[5]->Text = "Downloaded";
							m_mutex->ReleaseMutex ();
							if(nTransfered != info->m_nSize)
							{
								m_logMutex->WaitOne ();
									m_swLog->WriteLine (info->m_strFileName + "transfer size does not match");
								m_logMutex->ReleaseMutex ();
								return false;
							}
							nOrderSize += info->m_nSize;
						}
					 }
					 catch(Exception^ e)
					 {
						m_logMutex->WaitOne ();
							m_swLog->WriteLine (strOrderID + ": Error: " + e->Message);
						m_logMutex->ReleaseMutex ();
						if(m_bWin32)
						 SendMail("NVIFTP: Error", e->Message);
						return false;
					 }

					/// recursive
					if(ftpInfo->m_ruleInfo->m_bRecursive)
					{
						for(int i=0; i< arrDir->Count; i++) /// for all sub directories
						{
							bool bRet = DownloadOrder (ftpInfo, strLocalFolder, strRemoteOrderPath, (String^)arrDir[i], nOrderSize);
							if(! bRet)
								return false;
						}
					}
				}

				/// delete the source
				if(ftpInfo->m_ruleInfo->m_bDeleteSource)
				{
					try
					{
						for(int x=0; x< list->Count; x++)
						{
							if(list[x]->IsDirectory )
								continue;
							ftpInfo->m_ftpsClient->DeleteFile (strRemoteOrderPath + ftpInfo ->m_strServerSlash + list[x]->Name);
						}
						ftpInfo->m_ftpsClient->RemoveDir (strRemoteOrderPath);
					}
					catch(Exception^ e)
					{
						if(m_bWin32)
						SendMail("NVIFTP: Error deleting source", e->Message);
						return false;
					}
				}

				return true;
		  }

			 /// prasann : 19th mar 12
			 /// upload the order according to the current rules
 private: bool UploadOrder(CFTPInfo^ ftpInfo, String^ strLocalPath, String^ strRemotePath, String^ strOrderID, int % nOrderSize, String^ strOrderName)
		  {
				String^ strRemoteOrderPath = gcnew String(strRemotePath +
					 ftpInfo->m_strServerSlash + strOrderID);

				String^ strFirstFileType = gcnew String(ftpInfo->m_ruleInfo->m_strFirstFileUpload);
				String^ strLastFileType = gcnew String(ftpInfo->m_ruleInfo->m_strLastFileUpload);
				String^ strSkipFileType = gcnew String(ftpInfo->m_ruleInfo->m_strSkipFileType);
				bool bSkipFileType = false;
				if(! String::IsNullOrEmpty (strSkipFileType))
					bSkipFileType = true;
//MessageBox ::Show("before dir exist");

/*
				if(String::IsNullOrEmpty (ftpInfo->m_ruleInfo->m_strLastFileUpload))
				{
					m_logMutex->WaitOne ();
						m_swLog->WriteLine (ftpInfo->m_ruleInfo->m_strRuleName + ": Last file type is empty");
					m_logMutex->ReleaseMutex ();
					SendMail("NVIFTP: Rule issue", ftpInfo->m_ruleInfo->m_strRuleName + ": Last file type is empty");
					return false;
				}
*/
				if(Directory::Exists (strLocalPath + Path::DirectorySeparatorChar + strOrderID))
				{
					ArrayList^ arrFirst = gcnew ArrayList ();
					ArrayList^ arrMiddle = gcnew ArrayList ();
					ArrayList^ arrLast = gcnew ArrayList ();
					ArrayList arrDir = Directory::GetDirectories (strLocalPath + Path::DirectorySeparatorChar + strOrderID);
					ArrayList arrFiles = Directory::GetFiles (strLocalPath + Path::DirectorySeparatorChar + strOrderID);

					/// separate out the first/last file types to be uploaded
					for(int x=0; x< arrFiles.Count; x++)
					{
						String^ strName = (String^) arrFiles[x];
						if(bSkipFileType)
						{
							if(strName->EndsWith (strSkipFileType, StringComparison ::CurrentCultureIgnoreCase))
								continue;
						}
						CFileInfo^ info = gcnew CFileInfo();
						info->m_strFileName = gcnew String(strName);
						FileInfo^ fInfo = gcnew FileInfo(info->m_strFileName);
						info->m_nSize = fInfo->Length;
/*
						if(strName->EndsWith (strFirstFileType, StringComparison ::CurrentCultureIgnoreCase) && !String::IsNullOrEmpty(strFirstFileType))
						{
							arrFirst->Add (info);
						}
						else if(strName->EndsWith (strLastFileType, StringComparison ::CurrentCultureIgnoreCase) && !String::IsNullOrEmpty(strLastFileType))
						{
							arrLast->Add (info);
						}
						else
						{
							arrMiddle->Add (info);
						}
*/
						arrMiddle->Add (info);
					}
					/// check rules
					if(! String::IsNullOrEmpty (strFirstFileType))
					{
						if(arrFirst->Count == 0)
						{
							m_logMutex->WaitOne ();
								m_swLog->WriteLine (strOrderID + ": First files are missing");
							m_logMutex->ReleaseMutex ();
							if(m_bWin32)
							SendMail("NVIFTP: Files missing", strOrderID + ": First files are missing");
							return false;
						}
					}
					if(! String::IsNullOrEmpty (strLastFileType))
					{
						if(arrLast->Count == 0)
						{
							m_logMutex->WaitOne ();
								m_swLog->WriteLine (strOrderID + ": Last files are missing");
							m_logMutex->ReleaseMutex ();
							if(m_bWin32)
							SendMail("NVIFTP: Files missing", strOrderID + ": Last files are missing");
							return false;
						}
					}
//MessageBox ::Show("calling makedir");
					/// create remote folder
					bool bExist = false;
					 String^ strRemoteFilePath = gcnew String(strRemotePath + ftpInfo->m_strServerSlash + strOrderID);
					 try
					 {
						 ftpInfo->m_ftpsClient->MakeDir (strRemoteFilePath);
					 }
					 catch(FTPCommandException^ e)
					 {
						if (e->ErrorCode != 550)
						{
							m_logMutex->WaitOne ();
								m_swLog->WriteLine (strRemoteFilePath + ": MakeDir Error: " + e->Message);
							m_logMutex->ReleaseMutex ();
							if(m_bWin32)
							SendMail("NVIFTP: Error", e->Message);
							return false;
						}
						else
							bExist = true;
					 }

					 List<DirectoryListItem^>^ list;
					 if(bExist)
					 {
						try
						{
							list = (List<DirectoryListItem^>^) ftpInfo->m_ftpsClient->GetDirectoryList (strRemoteFilePath);
						}
						catch(Exception ^e)
						{
							m_logMutex->WaitOne ();
								m_swLog->WriteLine (strRemoteFilePath + ": Dir List Error: " + e->Message);
							m_logMutex->ReleaseMutex ();
							if(m_bWin32)
							SendMail("NVIFTP: Error", e->Message);
							return false;
						}
					 }

					 unsigned __int64 nTransfered = 0;
					 try
					 {
						 /// put first files
						for(int i=0; i< arrFirst->Count ; i++)
						{
							CFileInfo^ info = (CFileInfo^) arrFirst[i];
							String^ strName = Path::GetFileName(info->m_strFileName);
							if(bExist && !ftpInfo->m_ruleInfo->m_bOverwrite)
							{
								bool bfound = false;
								for(int j=0; j< list->Count ; j++)
								{
									if(list[j]->IsDirectory )
										continue;
									if(list[j]->Name == strName && list[j]->Size == info->m_nSize)
									{
										bfound = true;
										break;
									}
								}
								if(bfound)
									continue;
							}
							m_mutex->WaitOne ();
							ListViewItem^ item = listProgress->Items ->Insert(getProgressListIndex(), strName);
							 listProgress ->Items[item->Index]->SubItems ->Add (/*ftpInfo->m_strConfigName*/strOrderName);
							 listProgress ->Items[item->Index]->SubItems ->Add (info->m_nSize.ToString ());
							 listProgress ->Items[item->Index]->SubItems ->Add ("");
							 listProgress ->Items[item->Index]->SubItems ->Add ("");
							 listProgress ->Items[item->Index]->SubItems ->Add ("Uploading");
							 m_mutex->ReleaseMutex ();

							 ftpInfo->m_ftpsClient->SetFileName (strName);
							nTransfered = ftpInfo->m_ftpsClient->PutFile(info->m_strFileName, strRemoteFilePath + ftpInfo->m_strServerSlash + strName, gcnew FileTransferCallback(TransferCallback));
							m_mutex->WaitOne ();
							listProgress ->Items[item->Index]->SubItems[5]->Text = "Uploaded";
							m_mutex->ReleaseMutex ();
							if(nTransfered != info->m_nSize)
							{
								m_logMutex->WaitOne ();
									m_swLog->WriteLine (strName + "transfer size does not match");
								m_logMutex->ReleaseMutex ();
								return false;
							}
							nOrderSize += info->m_nSize;

							ftpInfo->m_nPercentComplete += nTransfered;
						}
						/// put middle files
						for(int i=0; i< arrMiddle->Count ; i++)
						{
							CFileInfo^ info = (CFileInfo^) arrMiddle[i];
							String^ strName = Path::GetFileName(info->m_strFileName);
							if(bExist && !ftpInfo->m_ruleInfo->m_bOverwrite)
							{
								bool bfound = false;
								for(int j=0; j< list->Count ; j++)
								{
									if(list[j]->IsDirectory )
										continue;
									if(list[j]->Name == strName && list[j]->Size == info->m_nSize)
									{
										bfound = true;
										break;
									}
								}
								if(bfound)
									continue;
							}
							m_mutex->WaitOne ();
							 ListViewItem^ item = listProgress->Items ->Insert(getProgressListIndex(), strName);
							 listProgress ->Items[item->Index]->SubItems ->Add (/*ftpInfo->m_strConfigName*/strOrderName);
							 listProgress ->Items[item->Index]->SubItems ->Add (info->m_nSize.ToString ());
							 listProgress ->Items[item->Index]->SubItems ->Add ("");
							 listProgress ->Items[item->Index]->SubItems ->Add ("");
							 listProgress ->Items[item->Index]->SubItems ->Add ("Uploading");
							 m_mutex->ReleaseMutex ();

							 ftpInfo->m_ftpsClient->SetFileName (strName);
							nTransfered = ftpInfo->m_ftpsClient->PutFile(info->m_strFileName, strRemoteFilePath + ftpInfo->m_strServerSlash + strName, gcnew FileTransferCallback(TransferCallback));
							m_mutex->WaitOne ();
							listProgress ->Items[item->Index]->SubItems[5]->Text = "Uploaded";
							m_mutex->ReleaseMutex ();
							if(nTransfered != info->m_nSize)
							{
								m_logMutex->WaitOne ();
									m_swLog->WriteLine (strName + "transfer size does not match");
								m_logMutex->ReleaseMutex ();
								return false;
							}
							nOrderSize += info->m_nSize;

							ftpInfo->m_nPercentComplete += nTransfered;
						}
						/// put last files
						for(int i=0; i< arrLast->Count ; i++)
						{
							CFileInfo^ info = (CFileInfo^) arrLast[i];
							String^ strName = Path::GetFileName(info->m_strFileName);
							if(bExist && !ftpInfo->m_ruleInfo->m_bOverwrite)
							{
								bool bfound = false;
								for(int j=0; j< list->Count ; j++)
								{
									if(list[j]->IsDirectory )
										continue;
									if(list[j]->Name == strName && list[j]->Size == info->m_nSize)
									{
										bfound = true;
										break;
									}
								}
								if(bfound)
									continue;
							}
							m_mutex->WaitOne ();
							 ListViewItem^ item = listProgress->Items ->Insert(getProgressListIndex(), strName);
							 listProgress ->Items[item->Index]->SubItems ->Add (/*ftpInfo->m_strConfigName*/strOrderName);
							 listProgress ->Items[item->Index]->SubItems ->Add (info->m_nSize.ToString ());
							 listProgress ->Items[item->Index]->SubItems ->Add ("");
							 listProgress ->Items[item->Index]->SubItems ->Add ("");
							 listProgress ->Items[item->Index]->SubItems ->Add ("Uploading");
							m_mutex->ReleaseMutex ();

							 ftpInfo->m_ftpsClient->SetFileName (strName);
							nTransfered = ftpInfo->m_ftpsClient->PutFile(info->m_strFileName, strRemoteFilePath + ftpInfo->m_strServerSlash + strName, gcnew FileTransferCallback(TransferCallback));
							m_mutex->WaitOne ();
							listProgress ->Items[item->Index]->SubItems[5]->Text = "Uploaded";
							m_mutex->ReleaseMutex ();
							if(nTransfered != info->m_nSize)
							{
								m_logMutex->WaitOne ();
									m_swLog->WriteLine (strName + "transfer size does not match");
								m_logMutex->ReleaseMutex ();
								return false;
							}
							nOrderSize += info->m_nSize;

							ftpInfo->m_nPercentComplete += nTransfered;
						}
					 }
					 catch(Exception^ e)
					 {
						m_logMutex->WaitOne ();
							m_swLog->WriteLine (strOrderID + ": Error: " + e->Message);
						m_logMutex->ReleaseMutex ();
						if(m_bWin32)
						 SendMail("NVIFTP: Error", e->Message);
						return false;
					 }

						/// recursive
						if(ftpInfo->m_ruleInfo->m_bRecursive)
						{
							for(int i=0; i< arrDir.Count; i++) /// for all sub directories
							{
								bool bRet = UploadOrder (ftpInfo, strLocalPath + Path::DirectorySeparatorChar + strOrderID, strRemoteFilePath, Path::GetFileName ((String^)arrDir[i]), nOrderSize, "");
								if(! bRet)
									return false;
							}
						}
//MessageBox ::Show("deleting  source");

					/// delete the source
					if(ftpInfo->m_ruleInfo->m_bDeleteSource)
					{
						try
						{
							Directory::Delete (strLocalPath + Path::DirectorySeparatorChar + strOrderID, true);
						}
						catch(Exception^ e)
						{
							if(m_bWin32)
							SendMail("NVIFTP: Error deleting source", e->Message);
							return false;
						}
					}
				}
				else
				{
					m_logMutex->WaitOne ();
						m_swLog->WriteLine (strLocalPath + Path::DirectorySeparatorChar + strOrderID + " directory does not exist");
					m_logMutex->ReleaseMutex ();
					return false;
				}
				return true;
		  }

		  /// prasann : 16th mar 12
		  /// update the transfer rate on the list control
		private: static void TransferCallback(FTPSClient^ sender, ETransferActions action, String^ strLocalObjectName, String^ strRemoteObjectName, UInt64 fileTransmittedBytes, Nullable<UInt64 > fileTransferSize, bool % bCancel)
        {
			FTPSClient^ client = (FTPSClient^) sender;
			String^ strFileName = client->GetFileName ();
			Stopwatch^ watch = m_watchList[client->GetIndex ()];

			m_mutex->WaitOne ();
			int index = 0;
			for(int i=0; i<Form1::listProgress->Items ->Count; i++)
			{
				if(Form1::listProgress ->Items [i]->Text == strFileName)
				{
					index = i;
					break;
				}
			}

			double kBs = 0;
			int nPercent = fileTransmittedBytes * 100 / fileTransferSize.Value ;
            switch (action)
            {
			case ETransferActions::FileDownloaded:
			case ETransferActions::FileUploaded:
                    //OnFileTransferCompleted(fileTransmittedBytes, fileTransferSize);                    
					watch->Stop ();
					if (watch->ElapsedMilliseconds > 0)
						kBs = fileTransmittedBytes / 1.024 / watch->ElapsedMilliseconds;
					
					//Form1::listProgress->Items[Form1::listProgress->Items->Count - 1 ]->SubItems[2]->Text = kBs.ToString("N02") + " KB/s";
					//Form1::listProgress->Items[Form1::listProgress->Items->Count - 1 ]->SubItems[3]->Text = nPercent.ToString () + " %";
					Form1::listProgress->Items[index]->SubItems[3]->Text = kBs.ToString("N02") + " KB/s";
					Form1::listProgress->Items[index]->SubItems[4]->Text = nPercent.ToString () + " %";

					Form1::listProgress->Items[index]->ForeColor = Color::Black;
					Form1::listProgress->Items[index]->BackColor = Color::White;
                    break;
			case ETransferActions::FileDownloadingStatus:
			case ETransferActions::FileUploadingStatus:
                    if(fileTransmittedBytes == 0)
					{
						watch->Reset();
						watch->Start();

						Form1::listProgress->Items[index]->ForeColor  = Color::Red;
						Form1::listProgress->Items[index]->BackColor = Color::LightGray;
					}
					else
					{
						if (watch->ElapsedMilliseconds > 0)
							kBs = fileTransmittedBytes / 1.024 / watch->ElapsedMilliseconds;

						//Form1::listProgress->Items[Form1::listProgress->Items->Count - 1 ]->SubItems[2]->Text = kBs.ToString("N02") + " KB/s";
						//Form1::listProgress->Items[Form1::listProgress->Items->Count - 1 ]->SubItems[3]->Text = nPercent.ToString () + " %";
						Form1::listProgress->Items[index]->SubItems[3]->Text = kBs.ToString("N02") + " KB/s";
						Form1::listProgress->Items[index]->SubItems[4]->Text = nPercent.ToString () + " %";

						Form1::listProgress->Items[index]->ForeColor = Color::Red;
						Form1::listProgress->Items[index]->BackColor = Color::LightGray;
					}
                    break;
			case ETransferActions::RemoteDirectoryCreated:
                    break;
			case ETransferActions::LocalDirectoryCreated:
                    break;
            }

			m_mutex ->ReleaseMutex ();
        }

		  /// prasann : 14th mar 12
		  /// move the order to dest folder recursively
  private: bool MoveOrder(CFTPInfo^ ftpInfo, String^ strSource, String^ strDest, String^ strOrder)
		   {
			   if(Directory::Exists (strSource + Path::DirectorySeparatorChar + strOrder))
			   {
				   if(!Directory::Exists (strDest + Path::DirectorySeparatorChar + strOrder))
					   Directory::CreateDirectory (strDest + Path::DirectorySeparatorChar + strOrder);

					String^ strFirstFileType;
					String^ strLastFileType;
					if(ftpInfo->m_bDownload)
					{
						strFirstFileType = gcnew String(ftpInfo->m_ruleInfo->m_strFirstFileDownload);
						strLastFileType= gcnew String(ftpInfo->m_ruleInfo->m_strLastFileDownload);
					}
					else
					{
						strFirstFileType = gcnew String(ftpInfo->m_ruleInfo->m_strFirstFileUpload);
						strLastFileType= gcnew String(ftpInfo->m_ruleInfo->m_strLastFileUpload);
					}

					ArrayList arrDir = Directory ::GetDirectories (strSource + Path::DirectorySeparatorChar + strOrder);
					ArrayList arrFiles = Directory ::GetFiles (strSource + Path::DirectorySeparatorChar + strOrder);

					ArrayList^ arrFirst = gcnew ArrayList ();
					ArrayList^ arrMiddle = gcnew ArrayList ();
					ArrayList^ arrLast = gcnew ArrayList ();

					/// separate out the first/last file types to be moved
					for(int x=0; x< arrFiles.Count; x++)
					{
						String^ str = (String^) arrFiles[x];

						if(str->EndsWith (strFirstFileType, StringComparison ::CurrentCultureIgnoreCase) && ! String::IsNullOrEmpty (strFirstFileType))
							arrFirst->Add (str);
						else if(str->EndsWith (strLastFileType, StringComparison ::CurrentCultureIgnoreCase) && ! String::IsNullOrEmpty (strLastFileType))
							arrLast->Add (str);
						else
							arrMiddle->Add (str);
					}

					 try
					 {
						/// copy first files
						for(int i=0; i< arrFirst->Count ; i++)
						{
							File::Copy((String^)arrFirst[i], strDest + Path::DirectorySeparatorChar + strOrder + Path::DirectorySeparatorChar + Path::GetFileName((String^)arrFirst[i]), true);
						}
						/// copy middle files
						for(int i=0; i< arrMiddle->Count ; i++)
						{
						 	File::Copy((String^)arrMiddle[i], strDest + Path::DirectorySeparatorChar + strOrder + Path::DirectorySeparatorChar + Path::GetFileName((String^)arrMiddle[i]), true);
						}
						/// copy last files
						for(int i=0; i< arrLast->Count ; i++)
						{
						 	File::Copy((String^)arrLast[i], strDest + Path::DirectorySeparatorChar + strOrder + Path::DirectorySeparatorChar + Path::GetFileName((String^)arrLast[i]), true);
						}
					 }
					 catch(Exception^ e)
					 {
						m_logMutex->WaitOne ();
							m_swLog->WriteLine("Move Order: " + strOrder + ": " + e->Message);
						m_logMutex->ReleaseMutex ();
						return false;
					 }

					/// recursive
					for(int i=0; i< arrDir.Count; i++) /// for all sub directories
					{
						bool bRet = MoveOrder (ftpInfo, strSource + Path::DirectorySeparatorChar + strOrder, strDest + Path::DirectorySeparatorChar + strOrder, Path::GetFileName((String^)arrDir[i]));
						if(! bRet)
							return false;
					}

					/// delete source
					try
					{
						Directory::Delete (strSource + Path::DirectorySeparatorChar + strOrder, true);
					}
					catch(Exception^ e)
					{
						m_logMutex->WaitOne ();
							m_swLog ->WriteLine ("Move Order: " + strOrder + ": " + e->Message);
						m_logMutex->ReleaseMutex ();
						return false;
					}
			   }
			   else
				   return false;

				return true;
		   }

/// prasann : 2nd apr 12
private : System::Void ReadSendMailXml(String^ strPath)
	  {
			if(File::Exists (strPath))
			{
				XmlSchemaClassLibrary::SendMail oMailObj;
				oMailObj.ReadMailXml(strPath);

				m_strEmailFromAdd = gcnew String(oMailObj.emailClient->mailProperties->From);
				m_strEmailServer = gcnew String(oMailObj.emailClient->mailProperties->ServerAdd);
				
				m_strEmailPassword = gcnew String("nvicreativestudio"/*oMailObj.emailClient->mailProperties->strPassword*/);

				int nCount = oMailObj.emailClient->mailProperties->To->Count;

				m_arrEmailTo = gcnew ArrayList ();
				for(int i=0; i<nCount; i++)
				{
					m_arrEmailTo->Add (oMailObj.emailClient->mailProperties->To[i]->Addr);
				}

				nCount = oMailObj.emailClient->mailProperties->CC->Count;
				m_arrEmailCC = gcnew ArrayList();
				for(int i=0; i<nCount; i++)
				{
					m_arrEmailCC->Add( oMailObj.emailClient->mailProperties->CC[i]->Addr);
				}
			}
			else
				MessageBox ::Show("SendMail.xml not found");
	  }

private: bool SendMail(String^ strSubject, String^ strMessage)
		 {
		   if(!String::IsNullOrEmpty (m_strEmailServer))
		   {
			   CEmail mail;

			   MailMessage^ msg = gcnew MailMessage();

				///fill the to address list.
				for(int i=0; i<m_arrEmailTo->Count; i++)
				{
					String^ str = gcnew String((String^)m_arrEmailTo[i]);
					msg->To->Add ( str );
				}

				///fill the cc address list.
				for(int i=0; i<m_arrEmailCC->Count; i++)
				{
					String^ str = gcnew String((String^)m_arrEmailCC[i]);
					msg->CC->Add ( str );
				}

				///from address.
				MailAddress ^ addr = gcnew MailAddress(m_strEmailFromAdd);
				msg->From = addr;

				///subject.
				strSubject += ", Solution ID: " + m_nSolutionId.ToString () + ", User ID: " + m_strUserId;
				msg->Subject = strSubject;

				///message.
				msg->Body = strMessage;

				return mail.SendMail (msg, m_strEmailFromAdd, m_strEmailPassword, m_strEmailServer, true);
		   }

		   return false;
	   }

private: System::Void displayTimer_Up(System::Object^  sender, System::EventArgs^  e)
		 {
			 if(m_arrFTPInfo->Count > 0)
			 {
				 m_nIndex ++;
				 if(m_nIndex >= m_arrFTPInfo->Count)
					 m_nIndex = 0;
				  CFTPInfo^ info = (CFTPInfo^ ) m_arrFTPInfo [m_nIndex];

				 showConnectionParameters(info);
			 }
		 }

private: int getProgressListIndex()
		 {
			 int nRet = 0;
			 if(listProgress->Items->Count > 0)
			 {
				 for(int i=0; i< listProgress->Items->Count; i++)
				 {
					 //if(listProgress ->Items[i]->SubItems[5]->Text == "Downloaded")
					 if(listProgress ->Items[i]->SubItems[5]->Text->EndsWith ("ded", StringComparison ::CurrentCultureIgnoreCase))
					 {
						 nRet = i;
						 break;
					 }
				 }
			 }

			 return nRet;
		 }

		 /// prasann : 18th apr 12
		 /// perform some diagnosis
private: System::Void diagnosticsTimer_Up(System::Object^  sender, System::EventArgs^  e)
		 {
			 /// check buzy long connections
			 /// check orders transferred
			  String^ strMsg = gcnew String("");
			  for(int i=0; i<m_arrFTPInfo->Count; i++)
			  {
				 CFTPInfo^ info = (CFTPInfo^) m_arrFTPInfo [i];
				 String^ strTime;
				 TimeSpan ts;

				  if(info->m_dtConnectionStart.Ticks > 0)
				  {
					if(info->m_bBusy)
						ts = DateTime::Now - info->m_dtConnectionStart;
					else
						ts = info->m_dtConnectionEnd - info->m_dtConnectionStart;
					strTime = gcnew String(ts.Hours.ToString () + " : " + ts.Minutes.ToString () + " : " + ts.Seconds.ToString ());

					//String^ strMsg = gcnew String(info->m_strConfigName + ": Connection time: " + strTime);
					//SendMail("NVIFTP Diagnostics", strMsg);
				  }

				  if(String::IsNullOrEmpty (strTime))
				  {
					  if(info->m_bDownload)
						strMsg += info->m_strConfigName + ": Orders downloaded: " + info->m_arrOrders ->Count.ToString () + ", Files downloaded: " + info->m_arrFiles ->Count .ToString ()/* + Environment::NewLine*/;
					  else
						  strMsg += info->m_strConfigName + ": Orders uploaded: " + info->m_arrOrders ->Count.ToString () + ", Files uploaded: " + info->m_arrFiles ->Count .ToString ()/* + Environment::NewLine*/;
				  }
				  else
				  {
					  if(info->m_bDownload)
						strMsg += info->m_strConfigName  + ": Connection time: " + strTime + ", Orders downloaded: " + info->m_arrOrders ->Count.ToString () + ", Files downloaded: " + info->m_arrFiles ->Count .ToString ()/* + Environment::NewLine*/;
					  else
						  strMsg += info->m_strConfigName  + ": Connection time: " + strTime + ", Orders uploaded: " + info->m_arrOrders ->Count.ToString () + ", Files uploaded: " + info->m_arrFiles ->Count .ToString ()/* + Environment::NewLine*/;
				  }

				  if(info->m_bBusy && !info->m_bConnected)
					  strMsg += ", Not connected";

				  /// check if thread is busy
				  if(info->m_worker ->IsBusy)
					  strMsg += ", Busy";

				  strMsg += Environment::NewLine;

				  //if(i == m_arrFTPInfo->Count - 1)
				  //{
						m_logMutex->WaitOne ();
						  m_swLog->Write (strMsg);
						m_logMutex->ReleaseMutex ();
				 // }

					/// check if not connected
				  if(info->m_bBusy && !info->m_bConnected)
				  {
					  strMsg += info->m_strConfigName + ": closing connection (busy and not connected)";
						m_logMutex->WaitOne ();
							m_swLog->WriteLine(strMsg);
						m_logMutex->ReleaseMutex ();

					  try
					  {
						info->m_ftpsClient->Close ();
					  }
					  catch(Exception^ e)
					  {
						  strMsg += ", " + e->Message;
						m_logMutex->WaitOne ();
						  m_swLog->WriteLine ("Diagnostics timer: " + info->m_strConfigName + ": error calling close(): " + e->Message);
						m_logMutex->ReleaseMutex ();
					  }

					info->m_bBusy = false;
					info->m_bConnected = false;
					info->m_dtConnectionEnd = DateTime::Now;
				  }

				  /// check if thread is busy
				  if(info->m_bBusy)
				  {
					  bool bClose = false;
					  if(info->m_worker ->IsBusy )
					  {
						  if(ts.Hours > 4)
						  {
							 strMsg += info->m_strConfigName + " Thread busy for long. closing connection";
							 m_logMutex->WaitOne ();
								m_swLog->WriteLine(strMsg);
							 m_logMutex->ReleaseMutex ();
							 bClose = true;
						  }
					  }
					  else
					  {
						 strMsg += info->m_strConfigName + " Thread idle, closing connection";
						 m_logMutex->WaitOne ();
							m_swLog->WriteLine(strMsg);
						 m_logMutex->ReleaseMutex ();
						 bClose = true;
					  }

					  if(bClose)
					  {
						  try
						  {
							info->m_ftpsClient->Close ();
						  }
						  catch(Exception^ e)
						  {
							strMsg += ", " + e->Message;
							m_logMutex->WaitOne ();
							  m_swLog->WriteLine ("Diagnostics timer: " + info->m_strConfigName + ": error calling close(): " + e->Message);
							m_logMutex->ReleaseMutex ();
						  }
							info->m_bBusy = false;
							info->m_bConnected = false;
							info->m_dtConnectionEnd = DateTime::Now;
					  }
				  }
			  }

			  if(!String::IsNullOrEmpty (strMsg) && m_bWin32)
				  SendMail("NVIFTP Diagnostics", strMsg);

			 /// check log file
			DateTime dt = DateTime::Now;
			String^ strDate = gcnew String(dt.Day.ToString () + "-" + dt.Month .ToString () + "-" + dt.Year .ToString ());
			String^ strLogFile = gcnew String(m_strLogPath + Path::DirectorySeparatorChar + "NVIFTP_" + strDate + ".log");
			if(strLogFile == m_strLogFile)
			{
			}
			else
			{
				if(m_bWin32)
				SendMail("NVIFTP Diagnostics", "New Log file not created, Current: " + m_strLogFile + " Expected: " + strLogFile);
			}
		 }
/*
		private: ImageCodecInfo^ GetEncoder(ImageFormat^ format)
		{
			array<ImageCodecInfo^>^ codecInfo;
	        codecInfo = ImageCodecInfo::GetImageEncoders();
			int numCodecs = codecInfo->GetLength(0);

			if (numCodecs > 0)
			{
				for (int i = 0; i < numCodecs; i++)
				{
					if(codecInfo[i]->FormatID == format->Guid)
					{
						return codecInfo[i];
					}
				}
			}

			return nullptr;
		}
*/
		 /// prasann : 26th oct 12
		 /// select photos
private: System::Void btnSelectPhotos_Click(System::Object^  sender, System::EventArgs^  e)
		 {
			 /// get disk free space
			 __int64 nFree = 0;
			 if(m_bWin32)
			 {
				nFree = GetDiskFreeSpace(m_strUploadTempFolder);
				nFree /= 1024 * 1024;
			 }

				//openFileDialog->InitialDirectory = m_strSelFolder;
				openFileDialog->FileName = nullptr;
				openFileDialog->Multiselect = true;
				openFileDialog->Filter = "Jpeg files|*.jpg;*.jpeg";

				System::Windows::Forms::DialogResult result = openFileDialog->ShowDialog();

				  // OK button was pressed.
				if ( result == System::Windows ::Forms ::DialogResult::OK )
				  {
					  m_arrFiles ->Clear ();
					  m_arrFiles = gcnew ArrayList();

					  ArrayList arr = openFileDialog->FileNames;

					  __int64 nSize = 0;
					  if(arr.Count > 0)
					  {
						bool bFirst = true;
						Collections::IEnumerator^ myEnum1 = arr.GetEnumerator();
						while (myEnum1->MoveNext()) 
						{
							String ^ SourceFilePath = safe_cast<String ^>(myEnum1->Current);
							//Path::GetFileName(SourceFilePath);
							//MessageBox::Show (SourceFilePath);
							if(bFirst)
							{
								bFirst = false;
								m_strSelFolder = Path::GetDirectoryName (SourceFilePath);
							}

							m_arrFiles ->Add (SourceFilePath);

							FileInfo^ info = gcnew FileInfo(SourceFilePath);
							nSize += info->Length;
						}

						nSize /= 1024 * 1024;
//MessageBox ::Show (nSize.ToString ());
						if(m_bWin32)
						{
						if(nFree < nSize)
						{
						 MessageBox ::Show ("Disk Free space is less.");
						 return;
						}
						}

						Album album;
						result = album.ShowDialog();
						if ( result == System::Windows :: Forms ::DialogResult::OK )
						  {
							  m_strAlbumName = gcnew String(album.m_strAlbumName);
							  //MessageBox ::Show (m_strAlbumName);
						  }
					  }
				  }
		 }

		 /// prasann : 26th oct 12
		 /// upload photos
private: System::Void btnUpload_Click(System::Object^  sender, System::EventArgs^  e) 
		 {
/*
ArrayList^ arrFiles1 = gcnew ArrayList();
Collections::IEnumerator^ myEnum1 = m_arrFiles->GetEnumerator();
while (myEnum1->MoveNext()) 
{
	arrFiles1->Add (safe_cast<String ^>(myEnum1->Current));
}

String^ strDir1 = gcnew String(m_strUploadTempFolder + "\\14");
String^ strDirThumb1 = gcnew String(m_strUploadTempFolder + "\\14_thumbnails");
Directory::CreateDirectory (strDir1);
Directory::CreateDirectory (strDirThumb1);

ProgressDlg progress(strDir1, strDirThumb1, m_nQuality, arrFiles1);
progress.ShowDialog ();
return;
*/
//DoWork ();
//return;
			 /// get the album name
			 if(String::IsNullOrEmpty (m_strAlbumName))
			 {
				 if(m_arrFTPInfo->Count > 0)
				 {
					 //start previous upload if pending
					 bool busy = true;
					 for(int i=0; i<m_arrFTPInfo->Count; i++)
					 {
						 CFTPInfo^ ftpinf = (CFTPInfo^) m_arrFTPInfo[i];
						 if(!ftpinf->m_bBusy)
							 busy = false;
					 }
					 if(! busy)
					 {
						 DoWork ();
						 return;
					 }
				 }
				 MessageBox ::Show ("Select photos first.");
				 return;
			 }
			Cursor->Current = Cursors::WaitCursor;

			 String^ strAlbumName = gcnew String(m_strAlbumName);
			 m_strAlbumName->Empty;

			 /// get the files
			 ArrayList^ arrFiles = gcnew ArrayList();
			Collections::IEnumerator^ myEnum = m_arrFiles->GetEnumerator();
			while (myEnum->MoveNext()) 
			{
				arrFiles->Add (safe_cast<String ^>(myEnum->Current));
			}
			m_arrFiles->Clear ();

			if(arrFiles->Count <= 0 )
				return;

			/// call Upload init
			CDSConnect connect;
			int numfiles = arrFiles->Count;
			int nUpload_id = connect.AddUploadMaster (m_nSolutionId, m_strUserId, "1", strAlbumName, numfiles, "Uploading", numfiles);
//MessageBox ::Show (nUpload_id.ToString ());
			if(nUpload_id > 0)
			{
				/// create upload id folder in temp
				String^ strDir = gcnew String(m_strUploadTempFolder + Path::DirectorySeparatorChar + nUpload_id.ToString ());
				String^ strDirThumb = gcnew String(m_strUploadTempFolder + Path::DirectorySeparatorChar + nUpload_id.ToString () + "_thumbnails");
				Directory::CreateDirectory (strDir);
				Directory::CreateDirectory (strDirThumb);

//				array<DSConnect::DesignService ::fileInfo^>^ finfo = gcnew array<DSConnect::DesignService ::fileInfo^>(numfiles);
/*
				/// compress images (quality)
				myEnum = arrFiles->GetEnumerator();
				int ncounter = 1;
				while (myEnum->MoveNext()) 
				{
					String^ strFile = safe_cast<String ^>(myEnum->Current);
					strFile = Path ::GetFileName (strFile);

					 Bitmap^ bmp = gcnew Bitmap(strFile);
					 ImageCodecInfo^ info = GetEncoder(ImageFormat::Jpeg);
					 __int64 nQuality = m_nQuality;
					 EncoderParameter^ param = gcnew EncoderParameter(Encoder::Quality, nQuality);
					 EncoderParameters^ params = gcnew EncoderParameters(1);
					 params->Param[0] = param;
					 bmp->Save(strDir + Path::DirectorySeparatorChar + strFile, info, params);

					 nQuality = 20;
					 param = gcnew EncoderParameter(Encoder::Quality, nQuality);
					 params = gcnew EncoderParameters(1);
					 params->Param[0] = param;
					 bmp->Save(strDirThumb + Path::DirectorySeparatorChar + strFile, info, params);

					 FileInfo^ inf = gcnew FileInfo(strDir + Path::DirectorySeparatorChar + strFile);

					DSConnect::DesignService ::fileInfo^ finfo1 = gcnew DSConnect::DesignService ::fileInfo(); 
					finfo1->sr_no = ncounter;
					finfo1->photo_name = gcnew String(strFile);
					finfo1->file_type = gcnew String("jpeg");
					finfo1->file_size = inf->Length;
					finfo1->width = bmp->Width;
					finfo1->height = bmp->Height;
					//finfo1->path = gcnew String("/FtpTest");

					finfo[ncounter-1] = finfo1;
					ncounter ++;
				}
*/
				ProgressDlg progress(strDir, strDirThumb, m_nQuality, arrFiles);
				progress.ShowDialog ();

				 /// populate the design service db with the uploaded files info
				int nret = connect.AddUploadDetail (m_nSolutionId, m_strUserId, nUpload_id, progress.m_finfo);
//MessageBox ::Show (nret.ToString ());
				 Cursor->Current = Cursors::Default;

				if(nret)
				{
					 /// start upload
					 CFTPInfo^ info = gcnew CFTPInfo();

					 String^ strConfigName = gcnew String("Upload" + m_nConfCounter.ToString ());
					 m_nConfCounter++;

        			 info->	m_strConfigName = gcnew String(strConfigName);
					 if(m_nProxy == 1)
					 {
        				 info->	m_strServerName = gcnew String(m_strProxyServer);
        				 info->	m_strServerUserName = gcnew String(m_strUploadUsername + "@" + m_strUploadServer);
					 }
					 else
					 {
        				 info->	m_strServerName = gcnew String(m_strUploadServer);
        				 info->	m_strServerUserName = gcnew String(m_strUploadUsername);
					 }

        			 info->	m_strServerPassword = gcnew String(m_strUploadPassword);
        			 //info->	m_strServerWorkingDir = gcnew String(strWorkingDir);
        			 info->	m_strServerSlash = gcnew String("/");
        			 //info->	m_strRuleName = gcnew String(cmbFtpRules->Text);
					 //if(m_strDatabaseNone->CompareTo (cmbFtpDbConnections->Text) == 0)
        			 info->	m_strDBConnectionName = gcnew String("");
        			 //info->	m_strLocalDownloadFolder = gcnew String(strLocalDFolder);
        			 info->	m_strLocalUploadFolder = gcnew String(m_strUploadTempFolder);
        			 //info->	m_strServerDownloadFolder = gcnew String(strServerDFolder);
        			 info->	m_strServerUploadFolder = gcnew String(m_strUploadBaseDir);

					 //if(String::IsNullOrEmpty (strTimeInterval))
					//	 info->m_nTimeInterval = 0;
					 //else
					//	info->m_nTimeInterval = Convert::ToInt32 (strTimeInterval);
					 //if(cmbBoxFtpServerType->Text ->CompareTo ("Downloader") == 0)
					//	 info->m_bDownload = true;
					 //else
						 info->m_bDownload = false;

					 //for(int j=0; j< m_arrRuleInfo->Count; j++)
					 //{
						// CRuleInfo^ ruleinfo = (CRuleInfo^) m_arrRuleInfo[j];
						// if(ruleinfo->m_strRuleName->CompareTo (info->	m_strRuleName) == 0)
						// {
						//	 info->m_ruleInfo = ruleinfo;
						//	 break;
						// }
					 //}
					 CRuleInfo^ rule = gcnew CRuleInfo();
					 rule->m_bDeleteSource = true;
					 rule->m_strRuleName = gcnew String("Rule1");
					 rule->m_bRecursive = false;
					 info->m_ruleInfo = rule;

					 info->m_strAlbumName = gcnew String(strAlbumName);
					 info->m_nUploadId = nUpload_id;

					 info->m_dtConnectionStart = DateTime ::DateTime (0);
					 info->m_dtConnectionEnd = DateTime ::DateTime (0);

					 info->m_nOrderSize = progress .m_nSize;

					 info->m_ftpsClient->LogCommand += gcnew LogCommandEventHandler(client_LogCommand);
					 info->m_ftpsClient->LogServerReply += gcnew LogServerReplyEventHandler(client_LogServerReply);
					 info->m_ftpsClient ->SetIndex (m_nConfCounter - 2);
					 info->m_ftpsClient ->SetConfigName (info->m_strConfigName);

					 Stopwatch^ watch = gcnew Stopwatch();
					 m_watchList->Add (watch);

					 m_arrFTPInfo ->Add (info);

					 DoWork ();
				}
			}
		 }

		 /// prasann : 29th oct 12
		 /// return the disk free space of the specified drive
 private: __int64 GetDiskFreeSpace(String^ strDrive)
		  {
			  DriveInfo info(strDrive);
			  return info.AvailableFreeSpace;
		  }

		  /// prasann : 29th oct 12
		  /// upload the photos
private: bool UploadNew(CFTPInfo^ ftpInfo)
		{
			if(ftpInfo->m_ruleInfo ->m_bPreview)
			{
				return UploadPreview(ftpInfo);
			}
			else
			{
				/// create remote folder
				String^ strRemotePath = gcnew String(""/*ftpInfo->m_strServerUploadFolder*/);
				if(!ftpInfo->m_strServerUploadFolder->EndsWith ("/"))
					strRemotePath += ftpInfo->m_strServerUploadFolder;
				for(int i=0; i<2; i++)
				{
					String^ strName;
					if(i == 0)
						strName = gcnew String(m_nSolutionId.ToString ());
					else
						strName = gcnew String(m_strUserId);

					strRemotePath = strRemotePath + ftpInfo->m_strServerSlash + strName;
					 try
					 {
						 ftpInfo->m_ftpsClient->MakeDir (strRemotePath);
					 }
					 catch(FTPCommandException^ e)
					 {
						if (e->ErrorCode != 550)
						{
							m_logMutex->WaitOne ();
								m_swLog->WriteLine (strRemotePath + ": MakeDir Error: " + e->Message);
							m_logMutex->ReleaseMutex ();
							if(m_bWin32)
							SendMail("NVIFTP: Error", e->Message);
							return false;
						}
					 }
				}
				ftpInfo->m_strServerUploadFolder = strRemotePath;

				ArrayList^ UpOrder = gcnew ArrayList();

				COrders^ objOrder = gcnew COrders();
				objOrder->m_strOrderID = gcnew String(ftpInfo->m_nUploadId .ToString ());
				objOrder->m_strName = gcnew String(ftpInfo->m_strAlbumName);
				UpOrder->Add(objOrder);

				COrders^ objOrderThumb = gcnew COrders();
				objOrderThumb->m_strOrderID = gcnew String(ftpInfo->m_nUploadId .ToString ()+"_thumbnails");
				objOrderThumb->m_strName = gcnew String(ftpInfo->m_strAlbumName+"_thumbnails");
				UpOrder->Add(objOrderThumb);

				return StartUploadNew(ftpInfo, UpOrder);
			}

			return false;
		}

		 /// prasann : 29th oct 12
		 /// upload the folders
private: bool StartUploadNew(CFTPInfo^ ftpInfo, ArrayList^ arrOrders)
    {
		String^ strRemotePath;
		String^ strPhotoPath;
		String^ strThumbPath;
		int ncounter = 0;
        for each (COrders^ ObjDn in arrOrders)
        {
			bool bContinue = false;
			if(! ftpInfo->m_ruleInfo->m_bOverwrite)
			{
				for(int i=0; i< ftpInfo->m_arrOrders ->Count; i++)
				{
					String^ str = (String^) ftpInfo->m_arrOrders [i];
					if(str == ObjDn->m_strOrderID)
					{
						m_logMutex->WaitOne ();
							m_swLog->WriteLine ("Order: " + str + " already uploaded");
						m_logMutex->ReleaseMutex ();
						bContinue = true;
						break;
					}
				}
			}
			if(bContinue)
				continue;

			 DateTime dtStart = DateTime ::Now;

			 //listProgress->Items ->Clear ();

			if(ftpInfo->m_strServerUploadFolder->StartsWith (ftpInfo->m_strServerSlash))
				strRemotePath= gcnew String(ftpInfo->m_strServerUploadFolder);
			else
				strRemotePath= gcnew String(ftpInfo->m_strServerSlash + ftpInfo->m_strServerUploadFolder);

//MessageBox ::Show (strRemotePath);
			 int nOrderSize = 0;
			 bool bRet = UploadOrder(ftpInfo, ftpInfo->m_strLocalUploadFolder, strRemotePath, ObjDn->m_strOrderID, nOrderSize, ObjDn->m_strName);
			 if(bRet)
			 {
				 ftpInfo->m_arrOrders ->Add (ObjDn->m_strOrderID);
			 }
			 
			 DateTime dtEnd = DateTime ::Now;
			 //TimeSpan ts = dtEnd - dtStart;
			 //String^ strTime = gcnew String(ts.Hours.ToString () + " : " + ts.Minutes.ToString () + " : " + ts.Seconds.ToString ());
			 String^ strTime = gcnew String(dtEnd.Day.ToString () + "-" + dtEnd.Month.ToString () + "-" + dtEnd.Year.ToString () + " " + dtEnd.Hour.ToString () + ":" + dtEnd.Minute.ToString () + ":" + dtEnd.Second.ToString ());

			 ListViewItem^ item = listDone->Items ->Insert(0, ObjDn->m_strName);
			 //listDone ->Items[item->Index]->SubItems ->Add (ftpInfo->m_strConfigName);
			 listDone ->Items[item->Index]->SubItems ->Add (nOrderSize.ToString ());
			 listDone ->Items[item->Index]->SubItems ->Add (strTime);
			 listDone ->Items[item->Index]->SubItems ->Add ("Upload");
			 if(bRet)
				listDone ->Items[item->Index]->SubItems ->Add ("Success");
			 else
				listDone ->Items[item->Index]->SubItems ->Add ("Error");
			 
			 showConnectionParameters(ftpInfo);

			 if(ncounter == 0)
				strPhotoPath = gcnew String(strRemotePath + ftpInfo->m_strServerSlash + ObjDn->m_strOrderID);
			 else
				strThumbPath = gcnew String(strRemotePath + ftpInfo->m_strServerSlash + ObjDn->m_strOrderID);
			 ncounter ++;

			 if(!bRet)
				 return bRet;
		}

		/// update the upload paths and upload status
		CDSConnect connect;
		int nret = connect.UpdateUploadMaster (m_nSolutionId, m_strUserId, ftpInfo->m_nUploadId, strPhotoPath, strThumbPath);
//		MessageBox ::Show (nret.ToString ());

		return true;
	}

	  /// prasann : 14th nov 12
	  /// download the photos
private: bool DownloadNew(CFTPInfo^ ftpInfo)
	{
//MessageBox ::Show ("DownloadNew: ");
		/// get the new jobs, call getNewJobs
		CDSConnect connect;
		array<String^>^ arr = connect.getNewJobs (m_nSolutionId, m_strSolutionHash, m_strUserId);
		//ArrayList arr = connect.getNewJobs (m_nSolutionId, m_strSolutionHash, m_strUserId);

		if(arr->Length == 0)
			arr = connect.getPendingJobs (m_nSolutionId, m_strSolutionHash, m_strUserId);

		//ArrayList^ arr1 = gcnew ArrayList (arr);

//MessageBox ::Show ("Count: " + arr->Length.ToString ());
		if(arr->Length > 0)
		{
			Collections::IEnumerator^ myEnum = arr->GetEnumerator();
			int cntr = 1;
			while (myEnum->MoveNext()) 
			{
				String^ strJobId = safe_cast<String ^>(myEnum->Current);
				int nJobId = Convert::ToInt32 (strJobId);
//MessageBox ::Show ("JOB_ID: " + nJobId.ToString ());
				if(nJobId > 0)
				{
//nJobId = 33;
					/// get the photo info
					ArrayList arrItems = connect.getJobAlbumPhotos (m_nSolutionId, m_strSolutionHash, m_strUserId, nJobId);
					if(arrItems.Count > 0)
					{
//MessageBox ::Show ("Items: " + arrItems.Count.ToString ());

						int nindex = 0;
						int numItems = 8;
						int ntimes = arrItems.Count / numItems;
						array<CDownloadInfo^ >^ dnInfo = gcnew array<CDownloadInfo^ >(ntimes);
						for(int i=0; i< ntimes; i++)
						{
							String^ strSolnId = safe_cast<String ^>(arrItems[nindex]);
							String^ strUserId = safe_cast<String ^>(arrItems[nindex+1]);
							String^ strAlbPath = safe_cast<String ^>(arrItems[nindex+2]);
							String^ strAlbThumbPath = safe_cast<String ^>(arrItems[nindex+3]);
							String^ strGrouping = safe_cast<String ^>(arrItems[nindex+4]);
							String^ strPhotoName = safe_cast<String ^>(arrItems[nindex+5]);
							String^ strFileSize = safe_cast<String ^>(arrItems[nindex+6]);
							String^ strItemId = safe_cast<String ^>(arrItems[nindex+7]);

							CDownloadInfo^ info = gcnew CDownloadInfo();
							info->m_nSolnId = Convert::ToInt32 (strSolnId);
							info->m_strUserId = gcnew String(strUserId);
							info->m_strAlbPath = gcnew String(strAlbPath);
							info->m_strAlbThumbPath = gcnew String(strAlbThumbPath);
							info->m_strGrouping = gcnew String(strGrouping);
							info->m_strPhotoName = gcnew String(strPhotoName);
							info->m_strNewPhotoName = gcnew String(strPhotoName);
							info->m_nFileSize = Convert::ToInt32 (strFileSize);
							info->m_nItemId = Convert::ToInt32 (strItemId);
							dnInfo[i] = info;

							nindex += numItems;
						}

//MessageBox ::Show ("Calling update status: ");
						/// set the job status to downloading
						int nRet = connect.updateJobStatus (m_nSolutionId, m_strSolutionHash, m_strUserId, nJobId, "Downloading");
//MessageBox ::Show ("nRet: " + nRet.ToString ());
						if(nRet == 1)
						{
							bool bret = DownloadPhotos (ftpInfo, dnInfo, nJobId);
/*
							if(bret)
							{
								nRet = connect.updateJobStatus (m_nSolutionId, m_strSolutionHash, m_strUserId, nJobId, "Downloaded");
								if(nRet == 1)
								{}
								else
									return false;
							}
*/
						}
					}

//					array<DesignService::downloadInfo^>^ dnInfo = connect.getJobAlbumPhotos (m_nSolutionId, m_strSolutionHash, m_strUserId, nJobId);
//					ArrayList^ arrDnInfo = gcnew ArrayList();
/*
					ArrayList arrDnInfo = connect.getJobAlbumPhotos (m_nSolutionId, m_strSolutionHash, m_strUserId, nJobId);
MessageBox ::Show ("Array: " + arrDnInfo.Count.ToString ());
					if(arrDnInfo.Count > 0)
					{
						/// set the job status to downloading
						int nRet = connect.updateJobStatus (m_nSolutionId, m_strSolutionHash, m_strUserId, nJobId, "Downloading");
MessageBox ::Show ("nRet: " + nRet.ToString ());
						if(nRet == 1)
						{
						}
					}
*/
				}
			}
		}

		return true;
	}

	  /// prasann : 16th nov 12
	  /// download photos
private: bool DownloadPhotos(CFTPInfo^ ftpInfo, array<CDownloadInfo^>^ dnInfo, int nJobId)
	   {
//MessageBox ::Show ("DownloadPhotos");
//MessageBox ::Show ("count: " + dnInfo->Length);

//			String^ strRemotePath;
//			if(ftpInfo->m_strServerDownloadFolder->StartsWith (ftpInfo->m_strServerSlash))
//				strRemotePath= gcnew String(ftpInfo->m_strServerDownloadFolder);
//			else
//				strRemotePath= gcnew String(ftpInfo->m_strServerSlash + ftpInfo->m_strServerDownloadFolder);
			String^ strRemotePath = gcnew String("");

			String^ strTempFolder = gcnew String(m_strTempFolder + Path::DirectorySeparatorChar + ftpInfo->m_strConfigName + Path::DirectorySeparatorChar + nJobId.ToString ());
			Directory ::CreateDirectory (strTempFolder);

//			String^ strTempThumbFolder = gcnew String(m_strTempFolder + Path::DirectorySeparatorChar + ftpInfo->m_strConfigName + Path::DirectorySeparatorChar + nJobId.ToString () + "_thumbnails");
//			Directory ::CreateDirectory (strTempThumbFolder);

			ArrayList^ arrMiddle = gcnew ArrayList();

			/// for all the photos
			__int64 nSize = 0;
			for(int x=0; x< dnInfo->Length; x++)
			{
				CDownloadInfo^ dnFile = dnInfo[x];

				/// check if the file is already downloaded
				 bool bContinue = false;
				if(! ftpInfo->m_ruleInfo ->m_bOverwrite)
				{
					for(int y = 0; y < ftpInfo->m_arrFiles ->Count; y++)
					{
						CFileInfo^ fInfo = (CFileInfo^) ftpInfo->m_arrFiles [y];
						if(fInfo->m_strFileName == dnFile->m_strPhotoName && fInfo->m_nSize == dnFile->m_nFileSize)
						{
							m_logMutex->WaitOne ();
								m_swLog->WriteLine (strRemotePath + ": File: " + dnInfo[x]->m_strPhotoName + " already downloaded");
							m_logMutex->ReleaseMutex ();
							bContinue = true;
							break;
						}
					}
				}
				if(bContinue)
					continue;

//				CFileInfo^ info = gcnew CFileInfo();
//				info->m_strFileName = gcnew String(dnInfo[x]->m_strPhotoName);
//				info->m_strGrouping = gcnew String(dnInfo[x]->m_strGrouping);
//				info->m_nSize = dnInfo[x]->m_nFileSize;
				nSize += dnFile->m_nFileSize;

				arrMiddle->Add (dnFile);
			}

			String^ strDownloadName = gcnew String(Path::GetFileName (ftpInfo->m_strServerDownloadFolder));
			if(String::IsNullOrEmpty (strDownloadName))
				strDownloadName = ftpInfo->m_strServerSlash;

			ftpInfo->m_nOrderSize = nSize;
			ftpInfo->m_nPercentComplete = 0;

			/// download all files
			if(/*arrFirst->Count > 0 || arrLast->Count > 0 ||*/ arrMiddle->Count > 0)
			{
//MessageBox ::Show ("Starting download");
/*
				/// check rules
				if(! String::IsNullOrEmpty (strFirstFileType))
				{
					if(arrFirst->Count == 0)
					{
						m_logMutex->WaitOne ();
							m_swLog->WriteLine (strDownloadName + ": First files are missing");
						m_logMutex->ReleaseMutex ();
						SendMail("NVIFTP: Files missing", strDownloadName + ": First files are missing");
						return false;
					}
				}
				if(! String::IsNullOrEmpty (strLastFileType))
				{
					if(arrLast->Count == 0)
					{
						m_logMutex->WaitOne ();
							m_swLog->WriteLine (strDownloadName + ": Last files are missing");
						m_logMutex->ReleaseMutex ();
						SendMail("NVIFTP: Files missing", strDownloadName + ": Last files are missing");
						return false;
					}
				}
*/
				DateTime dtStart = DateTime ::Now;
				bool bError = false;
				//listProgress->Items ->Clear ();
				 try
				 {
					 unsigned __int64 nTransfered = 0;
					/// get middle files
					for(int i=0; i< arrMiddle->Count ; i++)
					{
						//CFileInfo^ info = (CFileInfo^) arrMiddle[i];
						CDownloadInfo^ dnFile = (CDownloadInfo^) arrMiddle[i];

						m_mutex->WaitOne ();
						 ListViewItem^ item = listProgress->Items ->Insert(getProgressListIndex(), dnFile->m_strPhotoName);
						 listProgress ->Items[item->Index]->SubItems ->Add (ftpInfo->m_strConfigName);
						 listProgress ->Items[item->Index]->SubItems ->Add (dnFile->m_nFileSize.ToString ());
						 listProgress ->Items[item->Index]->SubItems ->Add ("");
						 listProgress ->Items[item->Index]->SubItems ->Add ("");
						 listProgress ->Items[item->Index]->SubItems ->Add ("Downloading");
						 m_mutex->ReleaseMutex ();

						 String^ strGrouping = gcnew String(strTempFolder + Path::DirectorySeparatorChar + dnFile->m_nItemId.ToString () + Path::DirectorySeparatorChar + dnFile->m_strGrouping);
						 Directory ::CreateDirectory (strGrouping);
						 String^ strNewFilename = gcnew String(dnFile->m_strPhotoName);
						 if(File::Exists (strGrouping + Path::DirectorySeparatorChar + dnFile->m_strPhotoName))
						 {
							 strNewFilename = getNewFileName(dnFile->m_strPhotoName, strGrouping);
							 dnFile->m_strNewPhotoName = strNewFilename;
						 }

						 ftpInfo->m_ftpsClient->SetFileName (strNewFilename);
						 String^ strRemoteFilePath = gcnew String(strRemotePath + dnFile->m_strAlbPath);
						nTransfered = ftpInfo->m_ftpsClient->GetFile(strRemoteFilePath + ftpInfo->m_strServerSlash + dnFile->m_strPhotoName, strGrouping + Path::DirectorySeparatorChar + strNewFilename, gcnew FileTransferCallback(TransferCallback));
						m_mutex->WaitOne ();
						listProgress ->Items[item->Index]->SubItems[5]->Text = "Downloaded";
						m_mutex->ReleaseMutex ();
						if(nTransfered != dnFile->m_nFileSize)
						{
							m_logMutex->WaitOne ();
								m_swLog->WriteLine (dnFile->m_strPhotoName + "transfer size does not match");
							m_logMutex->ReleaseMutex ();
							bError = true;
							break;
							//return false;
						}

						ftpInfo->m_nPercentComplete += nTransfered;
/*
						/// download thumbnail
						m_mutex->WaitOne ();
						 ListViewItem^ itemThumb = listProgress->Items ->Insert(getProgressListIndex(), dnFile->m_strPhotoName);
						 listProgress ->Items[itemThumb->Index]->SubItems ->Add (ftpInfo->m_strConfigName);
						 listProgress ->Items[itemThumb->Index]->SubItems ->Add ("thumbnail");
						 listProgress ->Items[itemThumb->Index]->SubItems ->Add ("");
						 listProgress ->Items[itemThumb->Index]->SubItems ->Add ("");
						 listProgress ->Items[itemThumb->Index]->SubItems ->Add ("Downloading");
						 m_mutex->ReleaseMutex ();

						 strGrouping = gcnew String(strTempThumbFolder + Path::DirectorySeparatorChar + dnFile->m_strGrouping);
						 Directory ::CreateDirectory (strGrouping);
						 //String^ strNewFilename = gcnew String(dnFile->m_strPhotoName);
						 //if(File::Exists (strGrouping + Path::DirectorySeparatorChar + dnFile->m_strPhotoName))
						 //{
						//	 strNewFilename = getNewFileName(dnFile->m_strPhotoName, strGrouping);
						//	 dnFile->m_strNewPhotoName = strNewFilename;
						 //}

						 ftpInfo->m_ftpsClient->SetFileName (strNewFilename);
						 strRemoteFilePath = gcnew String(strRemotePath + dnFile->m_strAlbThumbPath);
						nTransfered = ftpInfo->m_ftpsClient->GetFile(strRemoteFilePath + ftpInfo->m_strServerSlash + dnFile->m_strPhotoName, strGrouping + Path::DirectorySeparatorChar + strNewFilename, gcnew FileTransferCallback(TransferCallback));
						m_mutex->WaitOne ();
						listProgress ->Items[itemThumb->Index]->SubItems[5]->Text = "Downloaded";
						m_mutex->ReleaseMutex ();
						//if(nTransfered != dnFile->m_nFileSize)
						//{
						//	m_logMutex->WaitOne ();
						//		m_swLog->WriteLine (dnFile->m_strPhotoName + "transfer size does not match");
						//	m_logMutex->ReleaseMutex ();
						//	return false;
						//}
						///
*/
						CFileInfo^ info = gcnew CFileInfo();
						info->m_strFileName = gcnew String(dnFile->m_strPhotoName);
						info->m_strGrouping = gcnew String(dnFile->m_strGrouping);
						info->m_nSize = dnFile->m_nFileSize;

						ftpInfo->m_arrFiles ->Add(info);
					}

					if(!bError)
					{
					String^ strDest = gcnew String(ftpInfo->m_strLocalDownloadFolder);
//MessageBox ::Show ("Dest: " + strDest);

//					String^ strDestThumb = gcnew String(ftpInfo->m_strLocalDownloadFolder + Path::DirectorySeparatorChar + nJobId .ToString () + "_thumbnails");
					Directory::CreateDirectory (strDest);
//					Directory::CreateDirectory (strDestThumb);

					/// move the files to dest folder
					for(int i=0; i< arrMiddle->Count ; i++)
					{
						CDownloadInfo^ dnFile = (CDownloadInfo^) arrMiddle[i];
						/// photos
						 String^ strSrcGrouping = gcnew String(strTempFolder + Path::DirectorySeparatorChar + dnFile->m_nItemId.ToString () + Path::DirectorySeparatorChar+ dnFile->m_strGrouping);
//MessageBox ::Show ("strSrcGrouping: " + strSrcGrouping);

						 if(File::Exists (strSrcGrouping + Path::DirectorySeparatorChar + dnFile->m_strNewPhotoName))
						 {
							String^ strGrouping = gcnew String(strDest + Path::DirectorySeparatorChar + dnFile->m_nSolnId.ToString () + Path::DirectorySeparatorChar + nJobId .ToString () + Path::DirectorySeparatorChar + dnFile->m_nItemId.ToString () + Path::DirectorySeparatorChar + dnFile->m_strGrouping);
							Directory ::CreateDirectory (strGrouping);
//MessageBox ::Show ("source: " + strSrcGrouping + Path::DirectorySeparatorChar + dnFile->m_strNewPhotoName);
//MessageBox ::Show ("dest: " + strGrouping + Path::DirectorySeparatorChar + dnFile->m_strNewPhotoName);
							File::Copy(strSrcGrouping + Path::DirectorySeparatorChar + dnFile->m_strNewPhotoName, strGrouping + Path::DirectorySeparatorChar + dnFile->m_strNewPhotoName, true);
							File::Delete (strSrcGrouping + Path::DirectorySeparatorChar + dnFile->m_strNewPhotoName);
						}
/*
						 /// thumbnails
						 strSrcGrouping = gcnew String(strTempThumbFolder + Path::DirectorySeparatorChar + dnFile->m_strGrouping);
						 if(File::Exists (strSrcGrouping + Path::DirectorySeparatorChar + dnFile->m_strNewPhotoName))
						 {
							String^ strGrouping = gcnew String(strDestThumb + Path::DirectorySeparatorChar + dnFile->m_strGrouping);
							Directory ::CreateDirectory (strGrouping);
							File::Copy(strSrcGrouping + Path::DirectorySeparatorChar + dnFile->m_strNewPhotoName, strGrouping + Path::DirectorySeparatorChar + dnFile->m_strNewPhotoName, true);
							File::Delete (strSrcGrouping + Path::DirectorySeparatorChar + dnFile->m_strNewPhotoName);
						}
*/
					}

					Directory::Delete (strTempFolder, true);
//					Directory::Delete (strTempThumbFolder, true);
/*
					/// delete the source
					if(ftpInfo->m_ruleInfo->m_bDeleteSource)
					{
						for(int x=0; x< dnInfo->Length; x++)
						{
//							if(list[x]->IsDirectory )
//								continue;
							ftpInfo->m_ftpsClient->DeleteFile (strRemotePath + ftpInfo->m_strServerSlash + dnInfo[x]->photo_name);
						}
					}
*/
					}
				 }
				 catch(Exception^ e)
				 {
					 bError = true;
					m_logMutex->WaitOne ();
						m_swLog->WriteLine (strDownloadName + ": Error: " + e->Message);
					m_logMutex->ReleaseMutex ();
					if(m_bWin32)
					 SendMail("NVIFTP: Error", e->Message);
					//return false;
				 }

				 DateTime dtEnd = DateTime ::Now;
				 //TimeSpan ts = dtEnd - dtStart;
				 String^ strTime = gcnew String(dtEnd.Day.ToString () + "-" + dtEnd.Month.ToString () + "-" + dtEnd.Year.ToString () + " " + dtEnd.Hour.ToString () + ":" + dtEnd.Minute.ToString () + ":" + dtEnd.Second.ToString ());

				 //ListViewItem^ item = listDone->Items ->Add (strDownloadName);
				 ListViewItem^ item = listDone->Items ->Insert(0, nJobId.ToString());
				 //listDone ->Items[item->Index]->SubItems ->Add (ftpInfo->m_strConfigName);
				 listDone ->Items[item->Index]->SubItems ->Add (nSize.ToString ());
				 listDone ->Items[item->Index]->SubItems ->Add (strTime);
				 listDone ->Items[item->Index]->SubItems ->Add ("Download");
				 if(! bError )
				 {
					CDSConnect connect;
					int nRet = connect.updateJobStatus (m_nSolutionId, m_strSolutionHash, m_strUserId, nJobId, "Downloaded");
					if(nRet == 1)
					{
						ftpInfo->m_arrFiles ->Clear ();
						listDone ->Items[item->Index]->SubItems ->Add ("Success");
					}
					else
					{
						listDone ->Items[item->Index]->SubItems ->Add ("Error");
						return false;
					}

				 }
				 else
				 {
					listDone ->Items[item->Index]->SubItems ->Add ("Error");
					return false;
				 }
			}
			 
			 showConnectionParameters(ftpInfo);
			 return true;
	   }

	   /// prasann : 21st nov 12
	   /// returns a new filename which is not there at the specified path
public : String^ getNewFileName(String^ strFilename, String^ strPath)
		 {
			 int ncounter = 1;
			 bool bPresent = true;
			 String^ strNewFilename = gcnew String(strFilename);
			 String^ strFile = gcnew String(Path::GetFileNameWithoutExtension (strFilename));
			 String^ strExt = gcnew String(Path::GetExtension (strFilename));
			 while(bPresent)
			 {
				 strNewFilename = strFile + "_" + ncounter.ToString () + strExt;
				 if(File ::Exists (strPath + Path::DirectorySeparatorChar + strNewFilename))
					 ncounter ++;
				 else
				 {
					 bPresent = false;
					 break;
				 }
			 }

			 return strNewFilename;
		 }

		 /// prasann : 15th jan 13
		 /// upload the preview files
private: bool UploadPreview(CFTPInfo^ ftpInfo)
    {
		ArrayList arrDir = Directory ::GetDirectories (ftpInfo->m_strLocalUploadFolder);
		String^ strRemotePath = gcnew String(ftpInfo->m_strServerUploadFolder);
		String^ strPreviewPath = gcnew String("Orders");
		String^ strRemoteLockerPath;
		//String^ strRemotePreviewPath;

		if(strRemotePath->EndsWith (ftpInfo->m_strServerSlash))
			strRemoteLockerPath = gcnew String(strRemotePath + "Orders");
		else
			strRemoteLockerPath = gcnew String(strRemotePath + ftpInfo->m_strServerSlash + "Orders");

		//if(strRemotePath->EndsWith (ftpInfo->m_strServerSlash))
		//	strRemotePreviewPath = gcnew String(strRemotePath + strPreviewPath);
		//else
		//	strRemotePreviewPath = gcnew String(strRemotePath + ftpInfo->m_strServerSlash + "Preview");

		bool bRet = false;

		 for(int x=0; x< arrDir.Count; x++)
		 {
			String^ strName = Path::GetFileName((String^)arrDir[x]);

			/// get the folder files 
			int nFileCount = 0;
			ArrayList arrFiles = Directory::GetFiles ((String^)arrDir[x]);
			for(int y=0; y< arrFiles.Count; y++)
			{
				 String^ strFile = Path::GetFileName((String^)arrFiles[y]);
				 if(strFile->EndsWith("jpg", StringComparison::CurrentCultureIgnoreCase) ||
					 strFile->EndsWith("jpeg", StringComparison::CurrentCultureIgnoreCase))
				 {
						nFileCount++;
				 }
			}

/*
			bool bContinue = false;
			if(! ftpInfo->m_ruleInfo ->m_bOverwrite)
			{
				for(int i=0; i< ftpInfo->m_arrOrders ->Count; i++)
				{
					String^ str = (String^) ftpInfo->m_arrOrders [i];
					if(str == strName)
					{
						m_logMutex->WaitOne ();
							m_swLog->WriteLine ("Order " + str + " already uploaded");
						m_logMutex->ReleaseMutex ();
						bContinue = true;
						break;
					}
				}
			}
			if(bContinue)
				continue;
*/
/*
			/// get the job_id

				int nJobId = 0;
				int nLockerId = 0;
				String^ strThumbFolder;
				array<DSConnect::DesignService ::fileInfo^>^ files;
				nLockerId = Convert::ToInt32 (strName);

				nJobId = connect.getRestorationJobId (m_nSolutionId, m_strSolutionHash, m_strUserId, nLockerId);

				if(nJobId > 0)
				{
					/// create preview thumbnails
					int nMaxThumbWidth = 400;

					strThumbFolder = gcnew String(m_strUploadTempFolder + Path::DirectorySeparatorChar + nJobId.ToString ());

					Directory ::CreateDirectory (strThumbFolder);
					ArrayList arrFiles = Directory ::GetFiles (ftpInfo->m_strLocalUploadFolder + Path::DirectorySeparatorChar + strName);
//MessageBox ::Show (ftpInfo->m_strLocalUploadFolder + Path::DirectorySeparatorChar + strName);
					files = gcnew array<DSConnect::DesignService ::fileInfo^>(arrFiles.Count);

					int ncounter = 0;
					for(int y=0; y< arrFiles.Count; y++)
					{
						 String^ strFile = Path::GetFileName((String^)arrFiles[y]);
						 if(strFile->EndsWith("jpg", StringComparison::CurrentCultureIgnoreCase) ||
							 strFile->EndsWith("jpeg", StringComparison::CurrentCultureIgnoreCase))
						 {
							 Bitmap^ bmp = gcnew Bitmap((String^)arrFiles[y]);
							 //Bitmap bmp((String^)arrFiles[y]);
							 if(bmp->Width > 0 && bmp->Height > 0)
							 {
								 double dratio = ((double)bmp->Width) / (double)bmp->Height;
								 int nNewWidth = bmp->Width ;
								 int nNewHeight = bmp->Height ;
								 if(nNewWidth > nNewHeight)
								 {
									 nNewWidth = nMaxThumbWidth;
									 nNewHeight = nNewWidth / dratio;
								 }
								 else
								 {
									 nNewHeight = nMaxThumbWidth;
									 nNewWidth = nNewHeight * dratio;
								 }

								 Bitmap^ bmpThumb = gcnew Bitmap(nNewWidth, nNewHeight);
								 Graphics^ g = Graphics ::FromImage (bmpThumb);
								 Rectangle srcRect(0,0,bmp->Width, bmp->Height);
								 Rectangle destRect(0,0,nNewWidth, nNewHeight);
								 g->DrawImage (bmp, destRect, srcRect, GraphicsUnit::Pixel);
								 bmpThumb->Save(strThumbFolder + Path::DirectorySeparatorChar + strFile, ImageFormat ::Jpeg);

								DSConnect::DesignService ::fileInfo^ finfo1 = gcnew DSConnect::DesignService ::fileInfo(); 
								finfo1->sr_no = ncounter+1;
								finfo1->photo_name = gcnew String(strFile);
								finfo1->width = nNewWidth ;
								finfo1->height = nNewHeight;
								files[ncounter] = finfo1;

								ncounter ++;

								delete bmp;
								bmp = nullptr;
								delete bmpThumb;
								bmpThumb = nullptr;
							}
						 }
					}
				}
				else
					continue;
			///
*/
			DateTime dtStart = DateTime ::Now;

			int nOrderSize = 0;
			bRet = UploadOrder(ftpInfo, ftpInfo->m_strLocalUploadFolder, strRemoteLockerPath, strName, nOrderSize, "");
			m_swLog->Flush ();

			if(bRet)
			{
				m_logMutex->WaitOne ();
					m_swLog->WriteLine ("Calling getOrderItems for: " + strName);
					m_swLog->Flush ();
				m_logMutex->ReleaseMutex ();

				bRet = false;
				/// set each item status to uploaded and order status to uploaded if last item
				CDSConnect connect;

				/// get order items
				int norder_id = Convert::ToInt32 (strName);
				array<String^>^ arr = connect.getPreviewItems (m_nSolutionId, m_strUserId, norder_id);
				if(arr->Length > 0)
				{
					//Collections::IEnumerator^ myEnum = arr->GetEnumerator();
					//while (myEnum->MoveNext()) 
					//{
					//	String^ strItem = safe_cast<String ^>(myEnum->Current);
					//	int nItemId = Convert::ToInt32 (strItem);
					//}
					m_logMutex->WaitOne ();
						m_swLog->WriteLine ("Calling updateItemStatus");
						m_swLog->Flush ();
					m_logMutex->ReleaseMutex ();

					/// update items status
					int nret = connect.updateItemStatus (m_nSolutionId, m_strSolutionHash, m_strUserId, arr, gcnew String("Uploaded"));
					if(nret)
					{
						/// update order status
						//if(nFileCount == arr->Length)
						//{
							m_logMutex->WaitOne ();
								m_swLog->WriteLine ("Calling updateOrderStatus");
								m_swLog->Flush ();
							m_logMutex->ReleaseMutex ();

							nret = connect.updateOrderStatus (m_nSolutionId, m_strUserId, norder_id, gcnew String("Uploaded"));
							if(nret)
								bRet = true;
						//}

					}
				}

/*
				if(nJobId > 0)
				{
					/// upload preview thumbnails
					int nSize = 0;
					bRet = UploadOrder(ftpInfo, m_strUploadTempFolder, strRemotePreviewPath, nJobId.ToString (), nSize, "");
					if(bRet)
					{
						if(Directory::Exists (strThumbFolder))
							Directory::Delete (strThumbFolder, true);

//MessageBox ::Show ("calling add preview");
						/// add preview
						//DateTime time = DateTime::Now;
						int nret = connect.addPreview(m_nSolutionId, m_strSolutionHash, m_strUserId, nJobId, "", ftpInfo->m_strServerSlash + strPreviewPath + ftpInfo->m_strServerSlash + nJobId.ToString (), DateTime::Now, files);
						if(nret == 1)
						{
							ftpInfo->m_arrOrders ->Add (strName);

							/// update the job status
							int nret = connect.updateJobStatus(m_nSolutionId, m_strSolutionHash, m_strUserId, nJobId, "Awaiting Customer Approval");
							if(nret == 0)
								bRet = false;
						}
						else
							bRet = false;
					}
					///

				}
				else
					bRet = false;
*/
			}

			 DateTime dtEnd = DateTime ::Now;
			 //TimeSpan ts = dtEnd - dtStart;
			String^ strTime = gcnew String(dtEnd.Day.ToString () + "-" + dtEnd.Month.ToString () + "-" + dtEnd.Year.ToString () + " " + dtEnd.Hour.ToString () + ":" + dtEnd.Minute.ToString () + ":" + dtEnd.Second.ToString ());

			 ListViewItem^ item = listDone->Items ->Insert(0, strName);
			//listDone ->Items[item->Index]->SubItems ->Add (ftpInfo->m_strConfigName);
			 listDone ->Items[item->Index]->SubItems ->Add (nOrderSize.ToString ());
			 listDone ->Items[item->Index]->SubItems ->Add (strTime);
			 listDone ->Items[item->Index]->SubItems ->Add ("Upload");
			 if(bRet)
				listDone ->Items[item->Index]->SubItems ->Add ("Success");
			 else
				listDone ->Items[item->Index]->SubItems ->Add ("Error");
			 
			 showConnectionParameters(ftpInfo);
		 }

		return true;
	}
/*
public: bool IsRunningOnMono ()
  {
	  //return System::Type::GetType ("Mono.Runtime") != null;
	  return true;
  }
*/
};
}

