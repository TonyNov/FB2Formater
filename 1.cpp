#include <iostream>
#include <fstream>
#include <windows.h>
#include <termmgr.h>
void replaceAll(std::string &str, const std::string &from, const std::string &to)
{
   size_t start_pos = 0;
   while ((start_pos = str.find(from, start_pos)) != std::string::npos)
   {
      str.replace(start_pos, from.length(), to);
      start_pos += to.length();
   }
}
void eraseAllSubStr(std::string &mainStr, const std::string &toErase)
{
   size_t pos = std::string::npos;
   while ((pos = mainStr.find(toErase)) != std::string::npos)
      mainStr.erase(pos, toErase.length());
}
int main()
{
   system("cls");
   SetConsoleCP(CP_UTF8);
   SetConsoleOutputCP(CP_UTF8);
   // SetConsoleOutputCP(1251);
   std::string firstname, lastname, middlename, booktitle, annotationtext;
   int i, j;
   std::string line1 = "", line2;
   std::string filename = "D:\\Download\\Garol-d-Morfin-Gont.fb2";
   std::string shablon = "<?xml version=\"1.0\" encoding=\"utf-8\"?>\n<FictionBook xmlns=\"http://www.gribuser.ru/xml/fictionbook/2.0\" xmlns:l=\"http://www.w3.org/1999/xlink\">\n <description>\n  <title-info>\n    <genre>fanfiction</genre>\n    <author>\n     <first-name>firstname</first-name>\n     <middle-name>middlename</middle-name>\n     <last-name>lastname</last-name>\n    </author>\n    <book-title>booktitle</book-title>\n    <annotation>\nannotationtext\n    </annotation>\n    <date></date>\n    <lang>ru</lang>\n    <sequence name = \"–ù–æ–≤–æ–µ\" />\n  </title-info>\n  <document-info>\n    <author>\n     <first-name>firstname</first-name>\n     <last-name>lastname</last-name>\n     <middle-name>middlename</middle-name>\n    </author>\n    <program-used>FictionBook Editor Release 2.6.7</program-used>\n    <date value=\"2022-10-29\">29 October 2022</date>\n    <id>0C7970A8-2B5C-4451-A983-7F06028C7101</id>\n    <version>1.0</version>\n    <history>\n     <p>1.0 ‚Äî —Å–æ–∑–¥–∞–Ω–∏–µ —Ñ–∞–π–ª–∞</p>\n    </history>\n  </document-info>\n </description>\n <body>\n  <title>\n   <p>firstname middlename lastname</p>\n   <p>booktitle</p>\n  </title>\n";
   try
   {
      std::ifstream file(filename);
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
         // eraseAllSubStr(line1, "<emphasis>");
         // eraseAllSubStr(line1, "</emphasis>");
         // eraseAllSubStr(line1, "<strong>");
         // eraseAllSubStr(line1, "</strong>");
         line1 = shablon + line1;
         i = line1.rfind("<binary");
         j = line1.rfind("</binary>");
         line1.erase(i, j - i + 9);
         // line1 = line1.substr(0, i) + line1.substr(j + 9, line1.size() - j - 8);
         i = filename.rfind("\\");
         std::string s = filename.substr(0, i + 1) + "(new)" + filename.substr(i + 1, filename.size() - i);
         std::cout << "Path: " << s << std::endl;
         std::ofstream outfile(s);
         outfile << line1;
         outfile.close();
      }
      else
      {
         std::cout << "ÕÂ Ì‡È‰ÂÌ Ù‡ÈÎ\n";
      }
   }
   catch (std::exception e)
   {
      std::cout << "Œ¯Ë·Í‡ ˜ÚÂÌËˇ\n";
   };
   system("pause");
}