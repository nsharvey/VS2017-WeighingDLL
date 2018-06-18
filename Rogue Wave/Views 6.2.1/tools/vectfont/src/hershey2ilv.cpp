// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: tools/vectfont/src/hershey2ilv.cpp
// --------------------------------------------------------------------------
//
// Licensed Materials - Property of Rogue Wave Software, Inc.
// (c) Copyright Rogue Wave Software, Inc. 2012, 2018
// (c) Copyright IBM Corp. 2009, 2011
// (c) Copyright ILOG 1992, 2009
// All Rights Reserved.
//
// Note to U.S. Government Users Restricted Rights:
// The Software and Documentation were developed at private expense and
// are "Commercial Items" as that term is defined at 48 CFR 2.101,
// consisting of "Commercial Computer Software" and
// "Commercial Computer Software Documentation", as such terms are
// used in 48 CFR 12.212 or 48 CFR 227.7202-1 through 227.7202-4,
// as applicable.
//
// --------------------------------------------------------------------------
// Converts Hershey fonts data to C++ code for Rogue Wave Views vectorial
// fonts usage
// --------------------------------------------------------------------------

#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define DY 91

#if !defined(DATADIR)
#define DATADIR "../data/"
#endif

// --------------------------------------------------------------------------
int
main(int argc, char* argv[])
{
    if (argc != 2) {
	printf("Usage: %s fontname\n\
Creates fontname.cpp, Rogue Wave Views format for vectorial Hershey fonts.\n",
		      argv[0]);
	return 1;
    }
    char filename[128];
    FILE* fin,
	* fout;
    strcpy(filename, DATADIR);
    strcat(filename, argv[1]);
    if ((fin = fopen(filename, "r")) == 0) {
	printf("Couldn't open %s for reading\n", filename);
	return 1;
    }
    strcpy(filename, argv[1]);
    strcat(filename,
#if defined(VMS)
	   ".cxx"
#else  /* !VMS */
	   ".cpp"
#endif /* !VMS */
	   );
    if ((fout = fopen(filename, "w")) == 0) {
	fclose(fin);
	printf("Couldn't open %s for writing\n", filename);
	return 1;
    }

    fprintf(fout,
	    "// -------------------------------------------------------------- -*- C++ -*-\n");
    fprintf(fout, "// File produced by %s\n", argv[0]);
    fprintf(fout, "// %s hershey font conversion for Rogue Wave Views\n", argv[1]);
    fprintf(fout, "// --------------------------------------------------------------------------\n");
    fprintf(fout,"\n");
    fprintf(fout,"#include <vfincl/vect.h>\n");
    fprintf(fout,"\nextern \"C\"\nIlvVirtualVectFont*\n");
    fprintf(fout, "IlvVirtualVectFont_%s()\n{\n", argv[1]);
    fprintf(fout, "    IlvVirtualVectFont* font = new IlvVirtualVectFont(\"%s\");\n",
	    argv[1]);
    int charcount = 32;
    while (1) {
	char w[6], n[4];
	if (fread(w, 1, 5, fin) != 5)
	    break;
	w[5] = 0;
	if (fread(n, 1, 3, fin) != 3)
	    break;
	n[3] = 0;
	int nn = atoi(n);
	char* chars = new char [2*nn];
	int skips = 0;
	int xmin =  1000,
	    xmax = -1000,
	    ymin =  1000,
	    ymax = -1000;
	for (int loop = 0; loop < nn; ++loop) {
	    char c1 = (char)fgetc(fin);
	    if (c1 == '\n')
		c1 = (char)fgetc(fin);
	    char c2 = (char)fgetc(fin);
	    chars[loop*2]   = c1;
	    chars[loop*2+1] = c2;
	    if (c1 == ' ')
		++skips;
	    else {
		if (c1 < xmin)
		    xmin = c1;
		if (c1 > xmax)
		    xmax = c1;
		if (c2 < ymin)
		    ymin = c2;
		if (c2 > ymax)
		    ymax = c2;
	    }
	}
	fgetc(fin); // Skip '\n'
	if (nn > 1) {
	    fprintf(fout, "    font->setCharDesc(%3d, new IlvStrokeCharDesc(%d, %d, // %d skips",
		    charcount, xmax-xmin+4, nn-2-2*skips, skips);
	    int skipped = 0;
	    int oldx    = chars[0]-xmin,
                oldy    = chars[1]-DY;
	    for (int loop = 1; loop < nn; ++loop) {
		if (chars[loop*2] == ' ')
		    skipped = 0;
		else {
		    int x = chars[loop*2]-xmin, y = chars[loop*2+1]-DY;
		    if (skipped)
			fprintf(fout, ",\n\t\t\t\t\t\t %d, %d, %d, %d",
				oldx, oldy, x, y);
		    oldx = x;
		    oldy = y;
		    skipped = 1;
		}
	    }
	    fprintf(fout, ")");
	} else {
	    fprintf(fout, "    font->setCharDesc(%3d, new IlvStrokeCharDesc(%d, 0) // Space char?\n\t\t      ",
		    charcount, xmax-xmin+20);
	}
	fprintf(fout, ");\n");
	delete chars;
	++charcount;
    }
    fprintf(fout, "\n    return font;\n}\n");
    fclose(fin);
    fclose(fout);
    printf("Done\n");

    return 0;
}
