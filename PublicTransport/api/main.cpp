#include <exception>

using namespace std;

#include <lib/fcgi/params.hpp>
#include <lib/fcgi/base.hpp>

void Throw (string a)
{
	cout << a << "\n";
}

Process proc;

int main ()
{
    int count = 0;
    long pid = getpid();

    streambuf * cin_streambuf  = cin.rdbuf ();
    streambuf * cout_streambuf = cout.rdbuf ();
    streambuf * cerr_streambuf = cerr.rdbuf ();

    FCGX_Request request;

    FCGX_Init ();
    FCGX_InitRequest (&request, 0, 0);

    while (FCGX_Accept_r (&request) == 0)
    {
        fcgi_streambuf cin_fcgi_streambuf (request.in);
        fcgi_streambuf cout_fcgi_streambuf (request.out);
        fcgi_streambuf cerr_fcgi_streambuf (request.err);

#if HAVE_IOSTREAM_WITHASSIGN_STREAMBUF
        cin  = &cin_fcgi_streambuf;
        cout = &cout_fcgi_streambuf;
        cerr = &cerr_fcgi_streambuf;
#else
        cin.rdbuf (&cin_fcgi_streambuf);
        cout.rdbuf (&cout_fcgi_streambuf);
        cerr.rdbuf (&cerr_fcgi_streambuf);
#endif

        char * content;
        unsigned long clen = gstdin(&request, &content);

		//cout << "Set-coockie: name-value\r\n\r\n";
		//cout <<
        //        "<H1>echo-cpp</H1>\n"
        //        "<H4>PID: " << pid << "</H4>\n"
        //        "<H4>Request Number: " << ++count << "</H4>\n";

        //cout << "<H4>Request Environment</H4>\n";
        proc.set_args (request.envp);
        if (content) delete []content;
    }

#if HAVE_IOSTREAM_WITHASSIGN_STREAMBUF
    cin  = cin_streambuf;
    cout = cout_streambuf;
    cerr = cerr_streambuf;
#else
    cin.rdbuf(cin_streambuf);
    cout.rdbuf(cout_streambuf);
    cerr.rdbuf(cerr_streambuf);
#endif

    return 0;
}
