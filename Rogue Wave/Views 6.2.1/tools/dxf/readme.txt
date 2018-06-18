	                Rogue Wave Views version 6.2.1

			tools/dxf README File

This directory contains the needed source files to read DXF data and
translate it to Rogue Wave Views 2D objects, or the reverse operation.

--------------------------------------------------------------------------
To read a DXF file, use the IlvDXFInput class (declared in dxfincl/dxread.h):

    class IlvDXFInput
    {
    public:
        IlvDXFInput(istream& stream);
        // ____________________________________________________________
	IlBoolean isBad() const;
        IlvGraphic** readObjects(IlvUInt& count, IlvDisplay& display);
	void setViewsExtents(const IlvRect& size, IlBoolean keepRatio = IlTrue);
	const IlvFloatPoint& getExtmin() const;
	const IlvFloatPoint& getExtmax() const;
	const IlvTransformer& getTransformer() const;
	void translate(IlFloat dx, IlFloat dy);
	void  scale(IlFloat fixedx, IlFloat fixedy,
		    IlFloat sx, IlFloat sy);
	void rotate(IlFloat centerx, IlFloat centery, IlFloat angle);
    };

Once the IlvDXFInput instance is create, the file header is loaded, so
that you can get some information about the extents of the original
DXF data.
Before you read the objects (using readObjects), you are able to
specify some geometric transformation to the DXF entities to make them
fit some Rogue Wave Views extents:
	Use 'setViewsExtents' if you know what destination rectangle
	should be the final bounding box, in the Rogue Wave Views
	coordinates system, of the DXF objects.
	Use 'scale' and 'translate' modify the DXF coordinates
	according to your needs, for that particular DXF file.

To write a DXF file from a set of objects that are stored in a manager, use
the IlvDXFOutput class (declared in dxfincl/dxwrite.h):

    class IlvDXFOutput
    {
    public:
        IlvDXFOutput(ostream& stream);
        void save(IlvManager* manager);
    };

--------------------------------------------------------------------------
Three sample programs can be built:
	readdxf: Reads and displays a DXF file.
	    Usage:
		readdxf [-scale scaleFactor] [-translate dx dy] [dxffilename]

	dxf2ilv: Reads a DXF file, and converts it into Rogue Wave Views format.
	    Usage:
		dxf2ilv dxffilename ilvfilename [maxdim]
	    The parameter maxdim indicates the width and height
	    of the destination Rogue Wave Views bounding box.
	    This will be used if and only if the DXF file contains
	    an extents information.

	ilv2dxf: Reads a Rogue Wave Views file, and converts it into DXF format.
	    Usage:
		ilv2dxf ilvfilename dxffilename

--------------------------------------------------------------------------
See the file src/readdxf.cpp for more details.

--------------------------------------------------------------------------
The data directory contains a dxf version of elefante.ilv, that you
can find in the data directory.
