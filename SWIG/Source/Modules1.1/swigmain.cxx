/*******************************************************************************
 * Simplified Wrapper and Interface Generator  (SWIG)
 *
 * Author : David Beazley
 *
 * Department of Computer Science
 * University of Chicago
 * 1100 E 58th Street
 * Chicago, IL  60637
 * beazley@cs.uchicago.edu
 *
 * Please read the file LICENSE for the copyright and terms by which SWIG
 * can be used and distributed.
 *******************************************************************************/

static char cvsroot[] = "$Header$";

/***********************************************************************
 * $Header$
 *
 * swigmain.cxx
 *
 * The main program.
 *
 ***********************************************************************/

#ifndef MACSWIG
#include "swigconfig.h"
#endif
#include "mod11.h"
#include "tcl8.h"
#include "python.h"
#include "perl5.h"
#include "guile.h"
#include "java.h"
#include "mzscheme.h"
#include "ruby.h"
#include "php4.h"

/* #include "htoi.h" */

#include <ctype.h>
#ifdef MACSWIG
#include <console.h>
#include <SIOUX.h>
#endif

#ifndef SWIG_LANG
#define SWIG_LANG PYTHON
#endif

/* Note: this list is in alphabetical order */
static char  *usage = (char*)"\
swig <options> filename\n\n\
Target Language Options:\n\
     -guile          - Generate Guile wrappers.\n\
     -java           - Generate Java wrappers.\n\
     -mzscheme       - Generate Mzscheme wrappers.\n\
     -perl           - Generate Perl wrappers.\n\
     -php            - Generate PHP wrappers.\n\
     -python         - Generate Python wrappers.\n\
     -ruby           - Generate Ruby wrappers.\n\
     -tcl            - Generate Tcl wrappers.\n";

//-----------------------------------------------------------------
// main()
//
// Main program.    Initializes the files and starts the parser.
//-----------------------------------------------------------------


int main(int argc, char **argv) {
  int i;
  Language *dl = new SWIG_LANG;
  extern int SWIG_main(int, char **, Language *);

#ifdef MACSWIG
  SIOUXSettings.asktosaveonclose = false;
  argc = ccommand(&argv);
#endif

  Swig_init_args(argc,argv);

  // Get options
  for (i = 1; i < argc; i++) {
      if (argv[i]) {
          if ((strcmp(argv[i],"-tcl8") == 0) || (strcmp(argv[i],"-tcl") == 0)) {
	      dl = new TCL8;
	      Swig_mark_arg(i);
	  } else if (strcmp(argv[i],"-python") == 0) {
	      dl = new PYTHON;
	      Swig_mark_arg(i);
	  } else if ((strcmp(argv[i],"-perl5") == 0) || (strcmp(argv[i],"-perl") == 0)) {
	      dl = new PERL5;
	      Swig_mark_arg(i);
	  } else if (strcmp(argv[i],"-guile") == 0) {
	      dl = new GUILE;
	      Swig_mark_arg(i);
	  } else if (strcmp(argv[i],"-java") == 0) {
	      dl = new JAVA;
	      Swig_mark_arg(i);
	  } else if (strcmp(argv[i],"-mzscheme") == 0) {
	      dl = new MZSCHEME;
	      Swig_mark_arg(i);
	  } else if (strcmp(argv[i],"-ruby") == 0) {
	      dl = new RUBY;
	      Swig_mark_arg(i);
	  } else if ((strcmp(argv[i],"-php") == 0) || (strcmp(argv[i],"-php4") == 0)) {
	    dl = new PHP4;
	    Swig_mark_arg(i);
	  } else if (strcmp(argv[i],"-nolang") == 0) {
	    dl = new Language;
	    Swig_mark_arg(i);
	      /*	  } else if (strcmp(argv[i],"-htoi") == 0) {
	    dl = new HTOI;
	    Swig_mark_arg(i); */
	  } else if ((strcmp(argv[i],"-dnone") == 0) ||
		     (strcmp(argv[i],"-dhtml") == 0) ||
		     (strcmp(argv[i],"-dlatex") == 0) ||
		     (strcmp(argv[i],"-dascii") == 0) ||
		     (strcmp(argv[i],"-stat") == 0))
	    {
	    Printf(stderr,"swig: Warning. %s option deprecated.\n",argv[i]);
	    Swig_mark_arg(i);
	  } else if (strcmp(argv[i],"-help") == 0) {
	      fputs(usage,stderr);
	      Swig_mark_arg(i);
	  }
      }
  }
  return SWIG_main(argc,argv,dl);
}
