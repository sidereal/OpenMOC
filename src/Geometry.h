/**
 * @file Geometry.h
 * @brief The Geometry class.
 * @date January 19, 2012
 * @author William Boyd, MIT, Course 22 (wboyd@mit.edu)
 */

#ifndef GEOMETRY_H_
#define GEOMETRY_H_

#ifdef __cplusplus
#include <limits.h>
#include <limits>
#include <sys/types.h>
#include <sys/stat.h>
#include "LocalCoords.h"
#include "Track.h"
#endif


/**
 * @class Geometry Geometry.h "openmoc/src/host/Geometry.h"
 * @brief The master class containing references to all geometry-related
 *        objects (surfaces, cells, universes and lattices) and materials.
 * @details The primary purpose for the geometry is to serve as a collection 
 *          of all geometry-related objects, as well as for ray tracing
 *          of characteristic tracks across the geometry and computing
 *          flat source region - to - cell maps.
 */
class Geometry {

private:

    /** The minimum point along the x-axis contained by geometry in cm */
    double _x_min;

    /** The maximum point along the x-axis contained by geometry in cm */    
    double _y_min;

    /** The minimum point along the y-axis contained by geometry in cm */
    double _x_max;

    /** The maximum point along the y-axis contained by geometry in cm */
    double _y_max;

    /** The boundary conditions at the top of the bounding box containing
     *  the geometry. False is for vacuum and true is for reflective boundary
     *  conditions */
    bool _top_bc;

    /** The boundary conditions at the top of the bounding box containing
     *  the geometry. False is for vacuum and true is for reflective boundary
     *  conditions */
    bool _bottom_bc;

    /** The boundary conditions at the top of the bounding box containing
     *  the geometry. False is for vacuum and true is for reflective boundary
     *  conditions */   
    bool _left_bc;

    /** The boundary conditions at the top of the bounding box containing
     *  the geometry. False is for vacuum and true is for reflective boundary
     *  conditions */   
    bool _right_bc;

    /** The total number of flat source regions in the geometry */
    int _num_FSRs;

    /** The number of energy groups for each material's nuclear data */
    int _num_groups;

    /** An array of cell IDs indexed by flat source region IDs */
    int* _FSRs_to_cells;

    /** An array of material IDs indexed by flat source region IDs */
    int* _FSRs_to_materials;

    /** The maximum track segment length in the geometry */
    double _max_seg_length;

    /** The minimum track segment length in the geometry */
    double _min_seg_length;

    /** A map of material IDs (keys) to material pointers (values) */
    std::map<short int, Material*> _materials;

    /** A map of surface IDs (keys) to surface pointers (values) */
    std::map<short int, Surface*> _surfaces;

    /** A map of cell IDs (keys) to cell pointers (values) */
    std::map<short int, Cell*> _cells;

    /** A map of universe IDs (keys) to universe pointers (values) */
    std::map<short int, Universe*> _universes;

    /** A map of lattice IDs (keys) to lattice pointers (values) */
    std::map<short int, Lattice*> _lattices;

    void initializeCellFillPointers();

    Cell* findFirstCell(LocalCoords* coords, double angle);
    Cell* findNextCell(LocalCoords* coords, double angle);

public:

    Geometry();
    virtual ~Geometry();

    double getWidth();
    double getHeight();
    double getXMin();
    double getXMax();
    double getYMin();
    double getYMax();
    bool getBCTop();
    bool getBCBottom();
    bool getBCLeft();
    bool getBCRight();
    int getNumFSRs();
    int getNumEnergyGroups();
    int getNumMaterials();
    int* getFSRtoCellMap();
    int* getFSRtoMaterialMap();
    double getMaxSegmentLength();
    double getMinSegmentLength();
    std::map<short int, Material*> getMaterials();
    Material* getMaterial(short int id);
    Surface* getSurface(short int id);
    Cell* getCell(short int id);
    Universe* getUniverse(short int id);
    Lattice* getLattice(short int id);

    void addMaterial(Material* material);
    void addSurface(Surface* surface);
    void addCell(Cell *cell);
    void addUniverse(Universe* universe);
    void addLattice(Lattice* lattice);

    Cell* findCellContainingCoords(LocalCoords* coords);
    CellBasic* findCellContainingFSR(int fsr_id);
    Cell* findCell(Universe* univ, int fsr_id);
    int findFSRId(LocalCoords* coords);
    void subdivideCells();
    void initializeFlatSourceRegions();
    void segmentize(Track* track);
    void computeFissionability(Universe* univ=NULL);
    void computePinPowers(FP_PRECISION* FSRs_to_powers,
                          FP_PRECISION* FSRs_to_pin_powers);
    FP_PRECISION computePinPowersInUniverse(Universe* univ, 
					    char* output_file_prefix,
					    int FSR_id, 
					    FP_PRECISION* FSRs_to_powers,
					    FP_PRECISION* FSRs_to_pin_powers);

    std::string toString();
    void printString();
};

#endif /* GEOMETRY_H_ */
