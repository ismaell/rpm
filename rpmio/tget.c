#include "system.h"

#include <rpmio_internal.h>
#include <rpmmacro.h>
#include <rpmmessages.h>
#include <popt.h>

#include "debug.h"

static int _debug = 0;

#define	HTTPSPATH	"https://localhost/test.txt"
#define	HTTPPATH	"http://localhost/test.txt"
#define	FTPPATH		"ftp://localhost/test.txt"
#define	DIRPATH		"/var/ftp/test.txt"
static char * httpspath = HTTPSPATH;
static char * httppath = HTTPPATH;
static char * ftppath = FTPPATH;
static char * dirpath = DIRPATH;

static void readFile(const char * path)
{
    FD_t fd;

fprintf(stderr, "===== %s\n", path);
    fd = Fopen(path, "r.ufdio");
    if (fd != NULL) {
	char buf[BUFSIZ];
	size_t len = Fread(buf, 1, sizeof(buf), fd);
	int xx = Fclose(fd);

	if (len > 0)
	    fwrite(buf, 1, len, stderr);
    }
}

static struct poptOption optionsTable[] = {
 { "debug", 'd', POPT_ARG_VAL,	&_debug, -1,		NULL, NULL },
 { "rpmiodebug", '\0', POPT_ARG_VAL|POPT_ARGFLAG_DOC_HIDDEN, &_rpmio_debug, -1,
	N_("debug rpmio I/O"), NULL},
 { "urldebug", '\0', POPT_ARG_VAL|POPT_ARGFLAG_DOC_HIDDEN, &_url_debug, -1,
	N_("debug URL cache handling"), NULL},
 { "verbose", 'v', 0, 0, 'v',				NULL, NULL },
  POPT_AUTOHELP
  POPT_TABLEEND
};

int
main(int argc, const char *argv[])
{
    poptContext optCon = poptGetContext(argv[0], argc, argv, optionsTable, 0);
    int rc;

    while ((rc = poptGetNextOpt(optCon)) > 0) {
	switch (rc) {
	case 'v':
	    rpmIncreaseVerbosity();
	    break;
	default:
            break;
	}
    }

    if (_debug) {
	rpmIncreaseVerbosity();
	rpmIncreaseVerbosity();
    }

#if 1
    readFile(dirpath);
#endif
#if 1
    readFile(ftppath);
    readFile(ftppath);
    readFile(ftppath);
#endif
#if 1
    readFile(httppath);
    readFile(httppath);
    readFile(httppath);
#endif
#if 1
    readFile(httpspath);
    readFile(httpspath);
    readFile(httpspath);
#endif

    return 0;
}
