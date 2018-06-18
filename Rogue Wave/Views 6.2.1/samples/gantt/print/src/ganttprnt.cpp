// -------------------------------------------------------------- -*- C++ -*-
//						 Rogue Wave Views source file
// File: samples/gantt/print/src/ganttprnt.cpp
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
// Gantt printing class implementation
// --------------------------------------------------------------------------
//
// This file implements GanttChartPrintingUtility. this class can dump an
// IlvGanttchart instance on an windows printer via the IlvWindowsDevice 
// class, or in Postscript using the IlvPSColorDevice class.
//
// Multiple pages printing is handled by this class. On each page, the gantt 
// lines and scale are printed according to the part of the gantt chart which 
// is supposed to be displayed.
// --------------------------------------------------------------------------

#include <ganttprnt.h>
#include <ilviews/graphics/scale.h>
#if !defined (WINDOWS)
 #define PSPRINT 1
#endif
#if defined(PSPRINT)
 #include <ilviews/util/ps.h>
#else /* WINPRINT */
 #include <ilviews/windows/dump.h>
#endif /* WINPRINT */

// --------------------------------------------------------------------------
#define LINES_WIDTH 200 //width on the page to print the left part of the chart
#define SCALE_HEIGHT 50 //height on the page to reserve for the Gantt scale
#define LINES_PER_PAGE 30 //number of lines per page

// --------------------------------------------------------------------------
// GanttChartPrintingUtility implementation
// --------------------------------------------------------------------------

// --------------------------------------------------------------------------
GanttChartPrintingUtility::GanttChartPrintingUtility(IlvGanttChart * gantt)
   : _gantt(gantt) 
{    
}

// --------------------------------------------------------------------------
GanttChartPrintingUtility::~GanttChartPrintingUtility()
{    
}

// --------------------------------------------------------------------------
// Print the gantt
// --------------------------------------------------------------------------
void GanttChartPrintingUtility::printGantt()
{   

    IlvDisplay* display = _gantt->getDisplay();

    // Create the printing device( subclass of IlvPort)  
#if defined (PSPRINT)
    IlvPSColorDevice printDevice(display);
    printDevice.initDevice("GanttPSDump.ps");
    //printDevice.setPaperWidth(816);
    //printDevice.setPaperHeight(1056);
#else /* WINPRINT */
    const char* printerName = IlvGetWindowsPrinter(IlTrue);
    IlvWindowsDevice printDevice(display);
    if(!printDevice.initDevice(printerName)) {        
        return;
    }
#endif /* WINPRINT */
    
    IlvRect pageSize(0, 0, printDevice.getPaperWidth(),
		      printDevice.getPaperHeight());

    display->initDump(&printDevice);
   
    IlvUShort firstRow = 0;
    IlvUShort lastRow = LINES_PER_PAGE - 1;
    
    int start = _gantt->getShownStart(0);
    int end = _gantt->getShownEnd(0);
    // the number of Pages is automatically computed, but can be set arbitrarily
    int numberOfPages =  ((end - start)
			  / (printDevice.getPaperWidth() - LINES_WIDTH) + 1);
    //int numberOfPages = 2;    

    int delta = (end - start) / numberOfPages;
    
    int newStart = start;    
    int newEnd;

    for (int i = 0 ; i < numberOfPages ; i++) {
        // new page if it's not the first page    
        if (i != 0)
            printDevice.newPage(); 

        // compute the data interval to print on the current page
        if (i != numberOfPages - 1)
            newEnd = newStart + delta;
        else
            newEnd = end;
        
        // show the Interval to print without any reDraw
        _gantt->showInterval(0, newStart, newEnd, IlFalse);

        firstRow = 0;
        lastRow = LINES_PER_PAGE - 1;
        while (firstRow < _gantt->rows()) {
            // new page if it's not the first line
            if (firstRow != 0)
                printDevice.newPage();
            // Print page
            printPage(pageSize, &printDevice, firstRow, lastRow);
            // next line
            firstRow = lastRow + 1;
            lastRow += LINES_PER_PAGE;
        }        
        newStart = newEnd;
    }
    display->endDump();
    printDevice.end();
    // reinitialize gantt displayed interval
    _gantt->showInterval(0, start, end, IlTrue);
}

// --------------------------------------------------------------------------
// Print a page from a line to another
// --------------------------------------------------------------------------
void
GanttChartPrintingUtility::printPage(IlvRect pageSize, 
				     IlvPort* port, 
				     IlUShort fromLine, 
				     IlUShort toLine)
{
    // Activities
    printActivities(pageSize, port, fromLine, toLine);
    // Lines
    printLines(pageSize, port, fromLine, toLine);
    // Scales
    printScale(pageSize, port);    
}

// --------------------------------------------------------------------------
// Print the scale in the top of the page
// --------------------------------------------------------------------------
void
GanttChartPrintingUtility::printScale(IlvRect pageSize,
				      IlvPort* port)
{    
    IlvDisplay * display = _gantt->getDisplay();
    IlvRectangularScale* scale = (IlvRectangularScale*)_gantt->getScale(0);

    // Source rect
    IlvPoint origin;
    scale->getOrigin(origin);
    IlvRect srcRect(origin.getX(), scale->y(), scale->getSize(), scale->h());

    // destination rect
    IlvRect destRect(pageSize.getX() + LINES_WIDTH, 
		     pageSize.getY() , 
		     pageSize.getW() - LINES_WIDTH, 
		     SCALE_HEIGHT);
    // draw the scale
    IlvTransformer t(srcRect, destRect);
    scale->draw(port, &t);
    port->fillRectangle(display->getPalette(display->getColor("white"),
					    display->getColor("white")),
                        IlvRect(pageSize.getX(),
				pageSize.getY(),
				LINES_WIDTH - 1,
				SCALE_HEIGHT));
}

// --------------------------------------------------------------------------
// Print the lines on the left side of the page
// --------------------------------------------------------------------------
void
GanttChartPrintingUtility::printLines(IlvRect pageSize,
				      IlvPort* port, 
				      IlUShort fromLine, 
				      IlUShort toLine)
{
    IlvDisplay * display = _gantt->getDisplay();
    
    if (toLine >= _gantt->rows())
        toLine = _gantt->rows() - 1;

    IlvGanttLine* first = _gantt->getLine(fromLine);
    IlvGanttLine* last = _gantt->getLine(toLine);
    IlvGraphic* firstGraphic = first->getGraphic();
    IlvGraphic* lastGraphic = last->getGraphic();

    // Source rect
    IlvRect firstRect;
    firstGraphic->boundingBox(firstRect);
    IlvRect lastRect;
    lastGraphic->boundingBox(lastRect);
    IlvRect srcRect(firstRect);
    srcRect.add(lastRect);

    // Destination rect
    IlvRect destRect(pageSize.getX(), pageSize.getY() + SCALE_HEIGHT,
		     LINES_WIDTH, pageSize.getH() - SCALE_HEIGHT);
    IlvUShort totalLines = toLine - fromLine + 1;
    if (totalLines < LINES_PER_PAGE)
        destRect.setH(destRect.getH() * totalLines / LINES_PER_PAGE);

    // Draw the lines
    IlvRegion region(srcRect);
    IlvRegion clip(destRect);
    IlvTransformer t(srcRect, destRect);
    _gantt->getManager()->draw(port, &t, 0, &clip);
    port->drawLine(display->getPalette(),
		   IlvPoint(LINES_WIDTH,
			    pageSize.getY()),
		   IlvPoint(LINES_WIDTH,
			    pageSize.getY() + pageSize.getH()));
}

// --------------------------------------------------------------------------
// Print the activities 
// --------------------------------------------------------------------------
void
GanttChartPrintingUtility::printActivities(IlvRect pageSize, 
					   IlvPort* port, 
					   IlUShort fromLine, 
					   IlUShort toLine)
{    
    if (toLine >= _gantt->rows())
        toLine = _gantt->rows() - 1;

    IlvGanttLine* first = _gantt->getLine(fromLine);
    IlvGanttLine* last = _gantt->getLine(toLine);
    IlvGraphic* firstGraphic = first->getGraphic();
    IlvGraphic* lastGraphic = last->getGraphic();

    // rect on the top
    IlvRect firstRect;
    firstGraphic->boundingBox(firstRect);
    IlvRect lastRect;
    lastGraphic->boundingBox(lastRect);
    IlvRect heightRect(firstRect);
    heightRect.add(lastRect);

    // Source rect
    IlvRect srcRect(_gantt->getShownStart(0), heightRect.getY(),
		    _gantt->getShownEnd(0) - _gantt->getShownStart(0),
		    heightRect.getH());

    // Destination rect
    IlvRect destRect(pageSize.getX() + LINES_WIDTH,
		     pageSize.getY() + SCALE_HEIGHT,
		     pageSize.getW() - LINES_WIDTH,
		     pageSize.getH() - SCALE_HEIGHT);
    IlvUShort totalLines = toLine - fromLine + 1;
    if (totalLines < LINES_PER_PAGE)
        destRect.setH(destRect.getH() * totalLines / LINES_PER_PAGE);

    // Prints the activities
    IlvRegion region(srcRect);
    IlvRegion clip(destRect);
    IlvTransformer t(srcRect, destRect);
    _gantt->getGrapher()->draw(port, &t, 0, &clip);
}
