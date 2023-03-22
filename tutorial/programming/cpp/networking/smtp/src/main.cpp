#include "client.h"
#include <string>

#define MAXINPUT 512

void get_time(char* buffer);

int main()
{
    char buffer[BUFFERSIZE];
    std::string inp;
    std::string port;
    std::string url;
    //url = "smtp.mailtrap.io"; port = "25";

    //465 is SSL port for connect to gmail.
    url = "smtp.gmail.com"; port = "465";


    Client client;
    client.connectServer(url, port);

    //Recving data from server.
    if(client.recvResponse(buffer, 220))
    {
        inp = "HELO gmail.com\r\n";
        if(!client.procMsg(inp, buffer, 250))
            return 0;
        
        //Login....................
        inp = "AUTH LOGIN\r\n";
        if(!client.procMsg(inp, buffer, 334))
            return 0;

        //Username.................
        //inp = "ZjkyYjA4NzcwZmJkYmM=\r\n";
        //pronob.roy07@gmail.com    in base64 format.
        inp = "cHJvbm9iLnJveTA3QGdtYWlsLmNvbQo=\r\n";
        if(!client.procMsg(inp, buffer, 334))
            return 0;
        
        //Password..................
        //inp = "NTE5ZDA2MWMyNzhjZWY=\r\n";
        //smackthat07   in base64 format.
        inp = "c21hY2t0aGF0MDcK\r\n";
        if(!client.procMsg(inp, buffer, 235))
            return 0;
         
        inp = "MAIL FROM:<pronob.roy07@gmail.com>\r\n";
        if(!client.procMsg(inp, buffer, 250))
            return 0;

        inp = "RCPT TO:<pronobroy007@hotmail.com>\r\n";
        if(!client.procMsg(inp, buffer, 250))
            return 0;

        inp = "DATA\r\n";
        client.procMsg(inp, buffer, 354);
        //Sending mail Header.......................
        inp =   "From:<Mail@domain.com>\r\n"
                "To:<pronob.roy07@gmail.com>\r\n"
                "Subject: C++\r\n"
                "MIME-Version: 1.0\r\n"
                "Content-Type: multipart/alternative; boundary=\"SEPARATOR\"\r\n"
                "\r\n"
                
                //Some mail server dosen't support html. 
                //For them use this text/plain..........
                "--SEPARATOR\r\n"
                "Content-Type: text/plain\r\n"
                "\r\n"
                "<h1>This is message body. plain text<h1>\r\n"

                //If smtp server support html.
                //show this...................
                "--SEPARATOR\r\n"
                "Content-Type: text/html\r\n"
                "\r\n"
                "<h1>This is message body<h1>\r\n"

                //This is for file attatchment..................
                "--SEPARATOR\r\n"
                "Content-Disposition: attachment; filename=my_file.txt\r\n"
                "Content-Type: application/octet-stream\r\n"
                "Content-Transfer-Encoding: base64\r\n"
                "\r\n"
                "VGhpcyBpcyBhIHNpbXBsZSB0ZXh0IG1lc3NhZ2Uu\r\n"

                //------ END --------
                "--SEPARATOR--\r\n"
                ".\r\n";
        client.procMsg(inp, buffer, 250);


        //Quit .....................
        inp = "QUIT\r\n";
        client.procMsg(inp, buffer, 221);
    }

    return 0;
}


void get_time(char* buffer)
{
    time_t timer;
    time(&timer);

    struct tm *timeinfo;
    timeinfo = gmtime(&timer);

    strftime(buffer, 128, "Date: %a, %d %b %Y %H:%M:%S +0000\r\n", timeinfo);
}
