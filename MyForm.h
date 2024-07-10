#pragma once
#include <Windows.h>
#include <vcclr.h>
#include <fstream>
#include <msclr/marshal.h>
#include <msclr\marshal_cppstd.h>
#include <string>
namespace $safeprojectname$ {

	using namespace System;
	using namespace System::ComponentModel;
	using namespace System::Collections;
	using namespace System::Windows::Forms;
	using namespace System::Data;
	using namespace System::Drawing;

	/// <summary>
	/// Сводка для MyForm
	/// </summary>
	public ref class MyForm : public System::Windows::Forms::Form
	{
	public:
		MyForm(void)
		{
			InitializeComponent();
			//
			//TODO: добавьте код конструктора
			//
		}

	protected:
		/// <summary>
		/// Освободить все используемые ресурсы.
		/// </summary>
		~MyForm()
		{
			if (components)
			{
				delete components;
			}
		}
	private: System::Windows::Forms::Button^ button1;
	private: System::Windows::Forms::OpenFileDialog^ openDialog;
	private: System::Windows::Forms::RadioButton^ radioButton1;
	private: System::Windows::Forms::RadioButton^ radioButton2;
	private: System::Windows::Forms::Label^ label1;

	protected:

	private:
		/// <summary>
		/// Обязательная переменная конструктора.
		/// </summary>
		System::ComponentModel::Container^ components;

#pragma region Windows Form Designer generated code
		/// <summary>
		/// Требуемый метод для поддержки конструктора — не изменяйте
		/// содержимое этого метода с помощью редактора кода.
		/// </summary>
		void InitializeComponent(void)
		{
			this->button1 = (gcnew System::Windows::Forms::Button());
			this->openDialog = (gcnew System::Windows::Forms::OpenFileDialog());
			this->radioButton1 = (gcnew System::Windows::Forms::RadioButton());
			this->radioButton2 = (gcnew System::Windows::Forms::RadioButton());
			this->label1 = (gcnew System::Windows::Forms::Label());
			this->SuspendLayout();
			// 
			// button1
			// 
			this->button1->Font = (gcnew System::Drawing::Font(L"Microsoft Sans Serif", 14, System::Drawing::FontStyle::Regular, System::Drawing::GraphicsUnit::Point,
				static_cast<System::Byte>(204)));
			this->button1->Location = System::Drawing::Point(133, 84);
			this->button1->Name = L"button1";
			this->button1->Size = System::Drawing::Size(162, 53);
			this->button1->TabIndex = 0;
			this->button1->Text = L"Выбрать файлы";
			this->button1->UseVisualStyleBackColor = true;
			this->button1->Click += gcnew System::EventHandler(this, &MyForm::button1_Click);
			// 
			// openDialog
			// 
			this->openDialog->Filter = L"Книги|*.fb2";
			this->openDialog->Multiselect = true;
			this->openDialog->ShowReadOnly = true;
			// 
			// radioButton1
			// 
			this->radioButton1->AutoSize = true;
			this->radioButton1->Location = System::Drawing::Point(80, 32);
			this->radioButton1->Name = L"radioButton1";
			this->radioButton1->Size = System::Drawing::Size(110, 17);
			this->radioButton1->TabIndex = 1;
			this->radioButton1->Text = L"Заменяя старые";
			this->radioButton1->UseVisualStyleBackColor = true;
			// 
			// radioButton2
			// 
			this->radioButton2->AutoSize = true;
			this->radioButton2->Checked = true;
			this->radioButton2->Location = System::Drawing::Point(268, 32);
			this->radioButton2->Name = L"radioButton2";
			this->radioButton2->Size = System::Drawing::Size(146, 17);
			this->radioButton2->TabIndex = 2;
			this->radioButton2->TabStop = true;
			this->radioButton2->Text = L"Создавая новые файлы";
			this->radioButton2->UseVisualStyleBackColor = true;
			// 
			// label1
			// 
			this->label1->AutoSize = true;
			this->label1->Location = System::Drawing::Point(196, 9);
			this->label1->Name = L"label1";
			this->label1->Size = System::Drawing::Size(100, 13);
			this->label1->TabIndex = 3;
			this->label1->Text = L"Преобразовывать";
			// 
			// MyForm
			// 
			this->AutoScaleDimensions = System::Drawing::SizeF(6, 13);
			this->AutoScaleMode = System::Windows::Forms::AutoScaleMode::Font;
			this->ClientSize = System::Drawing::Size(443, 149);
			this->Controls->Add(this->label1);
			this->Controls->Add(this->radioButton2);
			this->Controls->Add(this->radioButton1);
			this->Controls->Add(this->button1);
			this->FormBorderStyle = System::Windows::Forms::FormBorderStyle::FixedSingle;
			this->MaximizeBox = false;
			this->MinimizeBox = false;
			this->Name = L"MyForm";
			this->ShowIcon = false;
			this->Text = L"Форматировать книги с ficbook";
			this->ResumeLayout(false);
			this->PerformLayout();

		}
		System::String^ StdStringToSystemString(const std::string& str)
		{
			return  msclr::interop::marshal_as<System::String^>(str);
		}
		std::string SystemStringToStdString(System::String^ str)
		{
			return msclr::interop::marshal_as<std::string>(str);
		}
		void replaceAll(std::string& str, const std::string& from, const std::string& to)
		{
			size_t start_pos = 0;
			while ((start_pos = str.find(from, start_pos)) != std::string::npos)
			{
				str.replace(start_pos, from.length(), to);
				start_pos += to.length();
			}
		}
		void eraseAllSubStr(std::string& mainStr, const std::string& toErase)
		{
			size_t pos = std::string::npos;
			while ((pos = mainStr.find(toErase)) != std::string::npos)
				mainStr.erase(pos, toErase.length());
		}
#pragma endregion
	private:
		System::Void button1_Click(System::Object^ sender, System::EventArgs^ e)
		{
			std::string firstname, lastname, middlename, booktitle, annotationtext;
			int i, j;
			openDialog->ShowDialog();
			array<String^>^ selectedFiles = openDialog->FileNames;
			std::string line1, line2,shablon;
			for each (String ^ filename in selectedFiles)
			{
				line1 = "";
				shablon = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<FictionBook xmlns=\"http://www.gribuser.ru/xml/fictionbook/2.0\" xmlns:l=\"http://www.w3.org/1999/xlink\">\n <description>\n  <title-info>\n    <genre>fanfiction</genre>\n    <author>\n     <first-name>firstname</first-name>\n     <middle-name>middlename</middle-name>\n     <last-name>lastname</last-name>\n    </author>\n    <book-title>booktitle</book-title>\n    <annotation>\nannotationtext\n    </annotation>\n    <date></date>\n    <lang>ru</lang>\n    <sequence name = \"РќРѕРІРѕРµ\" />\n  </title-info>\n  <document-info>\n    <author>\n     <first-name>firstname</first-name>\n     <middle-name>middlename</middle-name>\n     <last-name>lastname</last-name>\n    </author>\n    <program-used>FictionBook Editor Release 2.6.7</program-used>\n    <date value=\"2022-10-29\">29 October 2022</date>\n    <id>0C7970A8-2B5C-4451-A983-7F06028C7101</id>\n    <version>1.0</version>\n    <history>\n     <p>1.0 вЂ” СЃРѕР·РґР°РЅРёРµ С„Р°Р№Р»Р°</p>\n    </history>\n  </document-info>\n </description>\n <body>\n  <title>\n   <p>firstname middlename lastname</p>\n   <p>booktitle</p>\n  </title>\n";
				try
				{
					std::string filenamestd = SystemStringToStdString(filename);
					std::ifstream file(filenamestd);
					if (file.is_open())
					{
						while (std::getline(file, line2))
							line1 += line2 + '\n';
						file.close();
						eraseAllSubStr(line1, "<image xlink:href=\"#ficbook_logo.png\"/>");
						i = line1.find("<first-name>");
						if (i != std::string::npos)
						{
							j = line1.find("</first-name>");
							firstname = line1.substr(i + 12, j - i - 12);
						}
						i = line1.find("<last-name>");
						if (i != std::string::npos)
						{
							j = line1.find("</last-name>");
							lastname = line1.substr(i + 11, j - 11 - i);
						}
						i = line1.find("<middle-name>");
						if (i != std::string::npos)
						{
							j = line1.find("</middle-name>");
							middlename = line1.substr(i + 13, j - i - 13);
						}
						i = line1.find("<annotation>");
						if (i != std::string::npos)
						{
							j = line1.find("</annotation>");
							annotationtext = line1.substr(i + 12, j - i - 12);
						}
						i = line1.find("<book-title>");
						if (i != std::string::npos)
						{
							j = line1.find("</book-title>");
							booktitle = line1.substr(i + 12, j - i - 12);
						}
						i = line1.find("<section>");
						line1 = line1.substr(i, line1.size() - i + 1);
						replaceAll(shablon, "firstname", firstname);
						replaceAll(shablon, "lastname", lastname);
						replaceAll(shablon, "middlename", middlename);
						replaceAll(shablon, "annotationtext", annotationtext);
						replaceAll(shablon, "booktitle", booktitle);
						replaceAll(line1, "xlink:href", "l:href");
						eraseAllSubStr(line1, "</emphasis>");
						eraseAllSubStr(line1, "<emphasis>");
						eraseAllSubStr(line1, "</strong>");
						eraseAllSubStr(line1, "<strong>");
						line1 = shablon + line1;
						i = line1.rfind("<binary");
						if (i != std::string::npos)
						{
							j = line1.rfind("</binary>");
							line1.erase(i, j - i + 9);
						}
						std::ofstream outfile;
						if (radioButton2->Checked)
						{
							i = filenamestd.rfind("\\");
							outfile.open(filenamestd.substr(0, i + 1) + "(" + filenamestd.substr(i + 1, filenamestd.size() - i));
						}
						else
							outfile.open(filenamestd);
						outfile << line1;
						outfile.close();
						
					}
					else
						MessageBox::Show("Ошибка","Не найден файл "+filename, MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
				catch (std::exception e) {
					MessageBox::Show("Ошибка", "Ошибка чтения "+filename, MessageBoxButtons::OK, MessageBoxIcon::Error);
				}
			}
			MessageBox::Show("Программа завершила работу", "Информация", MessageBoxButtons::OK, MessageBoxIcon::Information);
		}
	};
}
