/*
 * File:   screenAreas.cpp
 * Author: greg
 *
 * Created on May 28, 2012, 3:16 PM
 */

#include "ScreenAreas.h"

/** Default constructor
 * 
 * The are no parameters for the default constructor. The whole matrix (10 columns and 7 rows) will be set to 0
 */
ScreenAreas::ScreenAreas()
{
    clearMatrix();
}

/** Copy constructor
 * 
 * @param orig The original object
 * 
 * @return An exact copy of the original object
 */
ScreenAreas::ScreenAreas(const ScreenAreas& orig)
{
    for (int i = 0; i < N_ROW; i++)
    {
        R[i] = orig.R[i];
    }
}

ScreenAreas::~ScreenAreas()
{
}

/** Clear matrix
 * 
 * This function clears the whole matrix (10 columns and 7 rows). 
 */
void ScreenAreas::clearMatrix()
{
    for (int i = 0; i < N_ROW; i++)
    {
        R[i] = 0;
    }
}

/** Set an area of the matrix as palm is present
 * 
 * @param Column The column of the matrix to be set high
 * @param Row The row of the matrix be be set high
 * 
 * @return  True if set was successful, otherwise false
 * 
 * This function sets the Column/Row combination.
 * A false will be return if and only if the Column/Row combination does not exist
 */
bool ScreenAreas::set(int Column, int Row)
{
    if ((Column < 0) || (Column >= N_COLUMN) || (Row < 0) || (Row >= N_ROW))
    {
        return false;
    }
    R[Row] = R[Row] | (1 << Column);

    return true;
}

/** Reset an area of the matrix as palm is no longer present
 * 
 * @param Column The column of the matrix to be set low
 * @param Row The row of the matrix be be set low
 * @return  True if reset was successful, otherwise false
 * 
 * A false will be return if and only if the Column/Row combination does not exist
 */
bool ScreenAreas::reset(int Column, int Row)
{
    if ((Column < 0) || (Column >= N_COLUMN) || (Row < 0) || (Row >= N_ROW))
    {
        return false;
    }
    R[Row] = R[Row]&~(1 << Column);
    return true;

}

/** Determine if a given area of a matrix is set
 * 
 * @param Column The column of the matrix to verify
 * @param Row The row of the matrix to verify
 * 
 * @return True if the Column/Row combination is set, otherwise false
 * 
 * A false will be return in the case where the Column/Row combination does not exist
 */
bool ScreenAreas::isSet(int Column, int Row)
{
    if ((Column < 0) || (Column >= N_COLUMN) || (Row < 0) || (Row >= N_ROW))
    {
        return false;
    }

    return R[Row] & (1 << Column);
}

/** Determines if there is at least one bit set on the whole matrix
 * 
 * @return True if there is at least 1 bit set on the whole matrix
 * 
 * A false will be return if and only if all Column/Row combination are reset; the whole matrix needs to be 0
 */
bool ScreenAreas::isSet()
{
    for (int i = 0; i < N_ROW; i++)
    {
        if (R[i] > 0)
        {
            return true;
        }
    }
    return false;
}

/** Set area function
 * 
 * @param Column Column number (between 0 and 9, inclusive)
 * @param Row Row number (between 0 and 6, inclusive)
 * 
 * @return True if the operation succeeded and false it is failed
 * 
 * This function sets to high an area around the given column and row with a radius of 1.
 * 
 * A false will be return if and only if the the Column/Row input combination does not exist
 */
bool ScreenAreas::setArea(int Column, int Row)
{

    if ((Column < 0) || (Column >= N_COLUMN) || (Row < 0) || (Row >= N_ROW))
    {
        return false;
    }


    /* Ideal condition. 
     * takes care of all 0
     * 
     *          ----------
     *          -00000000-
     *          -00000000-
     *          -00000000-
     *          -00000000-
     *          -00000000-
     *          ----------
     * 
     */
    if ((Column > 0) && (Column < N_COLUMN - 1) && (Row > 0) && (Row < N_ROW - 1))
    {
        R[Row - 1] = R[Row - 1] | (7 << (Column - 1));
        R[Row] = R[Row] | (7 << (Column - 1));
        R[Row + 1] = R[Row + 1] | (7 << (Column - 1));

        return true;
    }
        /* Takes care of all 0
         * 
         *          ----------
         *          0---------
         *          0---------
         *          0---------
         *          0---------
         *          0---------
         *          ----------
         * 
         */
    else if (Column == 0 && Row != 0 && Row != (N_ROW - 1))
    {
        R[Row - 1] = R[Row - 1] | (3 << Column);
        R[Row] = R[Row] | (3 << Column);
        R[Row + 1] = R[Row + 1] | (3 << Column);

        return true;
    }
        /* Takes care of all 0
         * 
         *          ----------
         *          ---------0
         *          ---------0
         *          ---------0
         *          ---------0
         *          ---------0
         *          ----------
         * 
         */
    else if (Column == (N_COLUMN - 1) && Row != 0 && Row != (N_ROW - 1))
    {
        R[Row - 1] = R[Row - 1] | (3 << (Column - 1));
        R[Row] = R[Row] | (3 << (Column - 1));
        R[Row + 1] = R[Row + 1] | (3 << (Column - 1));

        return true;
    }
        /* Takes care of all 0
         * 
         *          -00000000-
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         * 
         */
    else if (Row == 0 && Column != 0 && Column != (N_COLUMN - 1))
    {
        R[Row] = R[Row] | (3 << Column);
        R[Row + 1] = R[Row + 1] | (3 << Column);

        return true;
    }
        /* Takes care of all 0
         * 
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          -00000000-         
         */
    else if (Row == (N_ROW - 1) && Column != 0 && Column != (N_COLUMN - 1))
    {
        R[Row - 1] = R[Row - 1] | (7 << (Column - 1));
        R[Row] = R[Row] | (7 << (Column - 1));

        return true;
    }
        /* Takes care of the 0
         * 
         *          0---------
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          ----------  
         */
    else if (Column == 0 && Row == 0)
    {
        R[Row] = R[Row] | (3 << Column);
        R[Row + 1] = R[Row + 1] | (3 << Column);

        return true;
    }
        /* Takes care of the 0
         * 
         *          ---------0
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          ----------  
         */
    else if (Column == (N_COLUMN - 1) && Row == 0)
    {
        R[Row] = R[Row] | (3 << (Column - 1));
        R[Row + 1] = R[Row + 1] | (3 << (Column - 1));

        return true;
    }
        /* Takes care of the 0
         * 
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          0---------  
         */
    else if (Column == 0 && Row == (N_ROW - 1))
    {
        R[Row - 1] = R[Row - 1] | (3 << Column);
        R[Row] = R[Row] | (3 << Column);

        return true;
    }
        /* Takes care of the 0
         * 
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          ---------0  
         */
    else if (Column == (N_COLUMN - 1) && Row == (N_ROW - 1))
    {
        R[Row - 1] = R[Row - 1] | (3 << (Column - 1));
        R[Row] = R[Row] | (3 << (Column - 1));

        return true;
    }

    return false;
}

/** Reset area function
 * 
 * @param Column Column number (between 0 and 9, inclusive)
 * @param Row Row number (between 0 and 6, inclusive)
 * 
 * @return True if the operation succeeded and false it is failed
 * 
 * This function resets to low an area around the given column and row with a radius of 1
 * 
 * A false will be return if and only if the Column/Row input combination does not exist
 */
bool ScreenAreas::resetArea(int Column, int Row)
{
    if ((Column < 0) || (Column >= N_COLUMN) || (Row < 0) || (Row >= N_ROW))
    {
        return false;
    }


    /* Ideal condition. 
     * takes care of all 0
     * 
     *          ----------
     *          -00000000-
     *          -00000000-
     *          -00000000-
     *          -00000000-
     *          -00000000-
     *          ----------
     * 
     */
    if ((Column > 0) && (Column < N_COLUMN - 1) && (Row > 0) && (Row < N_ROW - 1))
    {
        R[Row - 1] = R[Row - 1] &~(7 << (Column - 1));
        R[Row] = R[Row] &~(7 << (Column - 1));
        R[Row + 1] = R[Row + 1] &~(7 << (Column - 1));

        return true;
    }
        /* Takes care of all 0
         * 
         *          ----------
         *          0---------
         *          0---------
         *          0---------
         *          0---------
         *          0---------
         *          ----------
         * 
         */
    else if (Column == 0 && Row != 0 && Row != (N_ROW - 1))
    {
        R[Row - 1] = R[Row - 1] &~(3 << Column);
        R[Row] = R[Row] &~(3 << Column);
        R[Row + 1] = R[Row + 1] &~(3 << Column);

        return true;
    }
        /* Takes care of all 0
         * 
         *          ----------
         *          ---------0
         *          ---------0
         *          ---------0
         *          ---------0
         *          ---------0
         *          ----------
         * 
         */
    else if (Column == (N_COLUMN - 1) && Row != 0 && Row != (N_ROW - 1))
    {
        R[Row - 1] = R[Row - 1] &~(3 << (Column - 1));
        R[Row] = R[Row] &~(3 << (Column - 1));
        R[Row + 1] = R[Row + 1] &~(3 << (Column - 1));

        return true;
    }
        /* Takes care of all 0
         * 
         *          -00000000-
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         * 
         */
    else if (Row == 0 && Column != 0 && Column != (N_COLUMN - 1))
    {
        R[Row] = R[Row] &~(3 << Column);
        R[Row + 1] = R[Row + 1] &~(3 << Column);

        return true;
    }
        /* Takes care of all 0
         * 
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          -00000000-         
         */
    else if (Row == (N_ROW - 1) && Column != 0 && Column != (N_COLUMN - 1))
    {
        R[Row - 1] = R[Row - 1] &~(7 << (Column - 1));
        R[Row] = R[Row] &~(7 << (Column - 1));

        return true;
    }
        /* Takes care of the 0
         * 
         *          0---------
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          ----------  
         */
    else if (Column == 0 && Row == 0)
    {
        R[Row] = R[Row] &~(3 << Column);
        R[Row + 1] = R[Row + 1] &~(3 << Column);

        return true;
    }
        /* Takes care of the 0
         * 
         *          ---------0
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          ----------  
         */
    else if (Column == (N_COLUMN - 1) && Row == 0)
    {
        R[Row] = R[Row] &~(3 << (Column - 1));
        R[Row + 1] = R[Row + 1] &~(3 << (Column - 1));

        return true;
    }
        /* Takes care of the 0
         * 
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          0---------  
         */
    else if (Column == 0 && Row == (N_ROW - 1))
    {
        R[Row - 1] = R[Row - 1] &~(3 << Column);
        R[Row] = R[Row] &~(3 << Column);

        return true;
    }
        /* Takes care of the 0
         * 
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          ----------
         *          ---------0  
         */
    else if (Column == (N_COLUMN - 1) && Row == (N_ROW - 1))
    {
        R[Row - 1] = R[Row - 1] &~(3 << (Column - 1));
        R[Row] = R[Row] &~(3 << (Column - 1));

        return true;
    }
    return false;

}

/** Print Matrix
 * 
 * This is a test function that will print the matrix allowing the user to visualize it
 */
void ScreenAreas::printMatrix()
{

    bool p;
    for (int i = 0; i < N_ROW; i++)
    {
        for (int j = 0; j < N_COLUMN; j++)
        {
            p = R[i]&(1 << j);
            std::cout << p;
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

/** Possible Pen
 * 
 * @param Column Column number
 * @param Row Row number
 * @return True if the column/row combination is in a possible pen area, otherwise false
 * 
 * This function is useful only of this object is used to map the palm. It returns true or false depending if the new point is in the possible area of a pen.
 * Things that are looked at are:
 * <ul><li>Is the new point on the edge of the palm (cannot be in the middle)
 * <li>Is it mostly to the left of the palm (should not to completely to the right) <i>(assuming right handed person)</i>
 */
bool ScreenAreas::possiblePen(int Column, int Row)
{
    //Checking if column and/or row is out of bound
    if ((Column < 0) || (Column >= N_COLUMN) || (Row < 0) || (Row >= N_ROW))
    {
        //std::cout<<"Out of bound"<<std::endl;
        return false;
    }

    //checking if the column/row combination is set
    if (isSet(Column, Row))
    {
        //std::cout<<"Column/Row is set "<<rand() %10<<std::endl;
        return false;
    }

    //checking if the pen is 
    for (int i = Row + 3; i < N_ROW; i++)
    {
        if (R[i] > 0)
        {
            // std::cout<<"Not pen area: "<<i<<std::endl;
            return false;
        }
    }

    return true;
}

/** Logical OR
 * 
 * @param area1 First area
 * @param area2 Second area
 * 
 * A logical OR occurs between the 2 areasThe resulting area replaces area1 (first area)
 */
void ScreenAreas::orAreas(ScreenAreas* area1, ScreenAreas* area2)
{
    //ScreenAreas area;
    for (int i = 0; i < N_ROW; i++)
    {
        area1->R[i] = area1->R[i] | area2->R[i];
    }
}

/** Overlap
 * 
 * @param area1 First area
 * @param area2 Second area
 * @return True is at least 1 area overlaps, otherwise false
 * 
 * Does at least 1 area of the 2 ScreenAreas overlap?
 */
bool ScreenAreas::overlap(ScreenAreas* area1, ScreenAreas* area2)
{
    for (int i = 0; i < N_ROW; i++)
    {
        int a = area1->R[i] & area2->R[i];
        if (a > 0)
        {
            return true;
        }
    }
    return false;
}