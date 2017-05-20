#include <exception>

using namespace std;

#include <lib/fcgi/params.hpp>
#include <lib/fcgi/base.hpp>

void Throw (string a)
{
	cout << a << "\n";
}

Process proc;

const string googleMapsAPIKey = "AIzaSyDrMTsyXH5f1Ib7GPyKk8aXgnVvWaaKi5E";

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

        proc.set_args (request.envp);
		if (proc.query_string ["type"] == "sent") // send favourite position
		{

		}
		else if (proc.query_string ["type"] == "init") // send station position
		{
			// returns number of station
		}
		else if (proc.query_string ["type"] == "get") // get n-th station position
		{
		}
		else if (proc.query_string ["type"] == "getPath") // get path between i-th and j-th stations
		{
		}
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
