#include "MyForm.h"

using namespace System;
using namespace System::Windows::Forms;
[STAThreadAttribute]
int main(array<String^>^) {
   Application::SetCompatibleTextRenderingDefault(false);
   Application::EnableVisualStyles();
   $safeprojectname$::MyForm form;
   Application::Run(% form);
}