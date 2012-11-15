/*
 * File:   PalmRejection.cpp
 * Author: greg
 *
 * Created on May 23, 2012, 12:39 PM
 */

#include "PalmRejection.h"

/** Default constructor
 * 
 * @param scribbleA This is a pointer to the a ScribbleArea
 */

PalmRejection::PalmRejection(ScribbleArea* scribbleA) : scribble(scribbleA), stopRequest(false), position(0), sampling(0), penPresent(false), mX(-1), mY(-1)
{
    //for now limit vector to 5, analyze data and decide what to do with it
    pointToAnalyze.resize(ANALYZE_BUFFER);

    //Timer used for palm reset
    //The palm will be fully reset after x seconds of 0 activity on the screen
    palmResetTimer = new boost::asio::deadline_timer(io_service);
    palmResetTimer->expires_from_now(boost::posix_time::seconds(RESET_TIMER));
    palmResetTimer->async_wait(boost::bind(&PalmRejection::resetPalm, this,_1)); 
}

/** Default destructor
 *
 * Deletes all Point object available in the pointToAnalyze buffer
 */
PalmRejection::~PalmRejection()
{
    palmResetTimer->cancel();
    delete palmResetTimer;
    
    flushPointBuffer();
}

/** Reset palm
 * 
 * This function is called x seconds after the last event on the screen (when resetTimer expires). Once called it will reset the palm area.
 * 
 * The resetTimer is only set once there is a complete release on the screen and is stopped as soon as the a new activity occurs. If the timer doesn't have the time to expire
 * this function will not be called and no reset will occur. 
 */
void PalmRejection::resetPalm(const boost::system::error_code &ec)
{
    mPalm.clearMatrix();
    //std::cout << "RESET PALM" << std::endl;

    //FOR TESTING
    //mPen.clearMatrix();
    
    palmResetTimer->cancel();
}

/** Touch event
 * 
 * @param mPointsQueue This is a queue of Point pointers (std::queue<Point* >)
 * 
 * This function is called when the first set of points is available.
 */
void PalmRejection::eventTouch(std::queue<Point* > *mPointsQueue)
{
    //Copy all points from the received queue to a local queue
    while (!mPointsQueue->empty())
    {
        pointToAnalyze[position].push_back(mPointsQueue->front());
        mPointsQueue->pop();
    }

    //Stop the palm reset timer
    palmResetTimer->cancel();

    //Remove possible duplicated points and find the palm and/or pen
    analyzeNewSetOfPoints();
}

/** Move event
 * 
 * @param mPointsQueue This is a queue of Point pointers (std::queue<Point* >)
 * 
 * This function is called by the InpitData whenever a new set of points is available, however not when it is the first set of points available
 * Calling this function does not mean that a move occurred since all previous points could have been considered as the palm 
 */
void PalmRejection::eventMove(std::queue<Point* > *mPointsQueue)
{
    //Copy all points from the received queue to a local queue
    while (!mPointsQueue->empty())
    {
        pointToAnalyze[position].push_back(mPointsQueue->front());
        mPointsQueue->pop();
    }

    //Remove possible duplicated points
    analyzeNewSetOfPoints();
    compact_pointToAnalyze();
    if ( penPresent )
    {
        findNextPoint();
    }

    else if ( !penPresent && !mPalm.isSet() )
    {
        //std::cout << "from Event move" << std::endl;
        firstTryFindingPenAndPalm();
        //std::cout<<"Find palm"<<std::endl;
        //findPalm();
    }
    else
    {
        findPen();
    }

    compact_pointToAnalyze();
    updatePosition();
}

bool PalmRejection::firstTryFindingPenAndPalm()
{
    //    //Used for set comparison to find possible points that will result in a pen. 
    int firstSet = mod(position - 3);
    int secondSet = mod(firstSet + 1);
    int thirdSet = mod(secondSet + 1);
    int forthSet = mod(thirdSet + 1);

    bool toBeReturned = false;

    int pos[] = { firstSet, secondSet, thirdSet, forthSet };

    //If all 4 last points set contain 1 point each then we have a pen
    if ( pointToAnalyze[firstSet].size() == 1 && pointToAnalyze[secondSet].size() == 1 && pointToAnalyze[thirdSet].size() == 1 && pointToAnalyze[forthSet].size() == 1 )
    {
        if ( !( mPalm.isSet(pointToAnalyze[pos[0]][0]->getColumn(), pointToAnalyze[pos[0]][0]->getRow()) || mPalm.isSet(pointToAnalyze[pos[1]][0]->getColumn(), pointToAnalyze[pos[1]][0]->getRow()) || mPalm.isSet(pointToAnalyze[pos[2]][0]->getColumn(), pointToAnalyze[pos[2]][0]->getRow()) || mPalm.isSet(pointToAnalyze[pos[3]][0]->getColumn(), pointToAnalyze[pos[3]][0]->getRow()) ) )
        {
            //We found a pen
            penPresent = true;
            //std::cout << "Been here, pen found only 1 point in each set" << std::endl;

            //Send events to the drawing area
            scribble->screenPressEvent(pointToAnalyze[pos[0]][0]);
            for ( int i = 1; i < 4; i++ )
            {
                scribble->screenMoveEvent(pointToAnalyze[pos[i]][0]);
            }

            mPen.clearMatrix();
            mPen.setArea(pointToAnalyze[forthSet][0]->getColumn(), pointToAnalyze[forthSet][0]->getRow());
            mX = pointToAnalyze[forthSet][0]->getX();
            mY = pointToAnalyze[forthSet][0]->getY();

            //Releasing ownership of the pass points. 
            pointToAnalyze[firstSet][0] = NULL;
            pointToAnalyze[secondSet][0] = NULL;
            pointToAnalyze[thirdSet][0] = NULL;
            pointToAnalyze[forthSet][0] = NULL;

            toBeReturned = true;
        }
    }
        //if all of the sets have less than 3 points but not 0 then we assume (could be a very bad assumption) that we have a palm
    else if ( pointToAnalyze[firstSet].size() < 3 && pointToAnalyze[firstSet].size() != 0 && pointToAnalyze[secondSet].size() < 3 && pointToAnalyze[secondSet].size() != 0 && pointToAnalyze[thirdSet].size() < 3 && pointToAnalyze[thirdSet].size() != 0 && pointToAnalyze[forthSet].size() < 3 && pointToAnalyze[forthSet].size() != 0 )
    {
        for ( int i = 0; i < 4; i++ )
        {
            for ( uint j = 0; j < pointToAnalyze[pos[i]].size(); j++ )
            {
                if ( pointToAnalyze[pos[i]][j] != NULL )
                {
                    mPalm.set(pointToAnalyze[pos[i]][j]->getColumn(), pointToAnalyze[pos[i]][j]->getRow());
                }
            }
        }
    }
        //we find the furthest point possible within each set, try to match 4 points in consecutive sets so they act as a pen, if if found we have a pen, otherwise we have a palm
    else if ( pointToAnalyze[firstSet].size() > 2 && pointToAnalyze[secondSet].size() > 2 && pointToAnalyze[thirdSet].size() > 2 && pointToAnalyze[forthSet].size() > 2 )
    {
        int index[] = { -1, -1, -1, -1 };

        for ( int i = 0; i < 4; i++ )
        {
            int maxDistance = 0;
            for ( ushort j = 0; j < pointToAnalyze[pos[i]].size(); j++ )
            {
                float currentDistance = getDistance(pos[i], j);
                //std::cout << "Distance" << currentDistance << std::endl;
                //std::cout<<"mPalm.isSet(pointToAnalyze[pos[i]][j]->getColumn(), pointToAnalyze[pos[i]][j]->getRow()) "<<mPalm.isSet(pointToAnalyze[pos[i]][j]->getColumn(), pointToAnalyze[pos[i]][j]->getRow())<<std::endl;
                if ( currentDistance > maxDistance && !mPalm.isSet(pointToAnalyze[pos[i]][j]->getColumn(), pointToAnalyze[pos[i]][j]->getRow()) )
                {
                    maxDistance = currentDistance;
                    index[i] = j;
                }
            }
        }

        if ( index[0] != -1 && index[1] != -1 && index[2] != -1 && index[3] != -1 )
        {
            std::cout << "GOT T" << std::endl;

            //Set true as before but if one point goes out of bound we set it to false... see below
            bool foundNewPen = true;
            for ( int i = 0; i < 3; i++ )
            {
                //                if ( mPalm.isSet(pointToAnalyze[pos[i]][index[i]]->getColumn(), pointToAnalyze[pos[i]][index[i]]->getRow()) )
                //                {
                //                    std::cout << "Palm is set" << std::endl;
                //                    foundNewPen = false;
                //                    continue;
                //                }
                //                if ( !mPalm.isSet(pointToAnalyze[pos[i]][index[i]]->getColumn(), pointToAnalyze[pos[i]][index[i]]->getRow()) )
                //                {
                int rx = pointToAnalyze[pos[i]][index[i]]->getX() - pointToAnalyze[pos[i + 1]][index[i + 1]]->getX();
                int ry = pointToAnalyze[pos[i]][index[i]]->getY() - pointToAnalyze[pos[i + 1]][index[i + 1]]->getY();
                float radius = sqrt(rx * rx + ry * ry);

                if ( !( ( radius > MINIMUM_RADIUS ) && ( radius < MAXIMUM_RADIUS ) ) )
                {
                    std::cout << "Not within the radius range" << std::endl;
                    foundNewPen = false;
                    break;
                }
                //  }
            }

            if ( foundNewPen )
            {
                std::cout << "Found Pen in GOT T" << std::endl;
                penPresent = true;
                mPen.clearMatrix();
                mPen.setArea(pointToAnalyze[forthSet][index[3]]->getColumn(), pointToAnalyze[forthSet][index[3]]->getRow());
                mPalm.reset(pointToAnalyze[forthSet][index[3]]->getColumn(), pointToAnalyze[forthSet][index[3]]->getRow());

                mX = pointToAnalyze[forthSet][index[3]]->getX();
                mY = pointToAnalyze[forthSet][index[3]]->getY();

                scribble->screenPressEvent(pointToAnalyze[pos[0]][index[0]]);
                pointToAnalyze[pos[0]][index[0]] = NULL;
                for ( int i = 1; i < 4; i++ )
                {
                    scribble->screenMoveEvent(pointToAnalyze[pos[i]][index[i]]);
                    pointToAnalyze[pos[i]][index[i]] = NULL;
                }

                toBeReturned = true;
            }
            else
            {
                for ( int i = 0; i < 4; i++ )
                {
                    mPalm.set(pointToAnalyze[pos[i]][index[i]]->getColumn(), pointToAnalyze[pos[i]][index[i]]->getRow());
                }

            }
        }
    }

    return toBeReturned;
}

/**
 * Removing all NULL from the pointToAnalyze[position]
 */
void PalmRejection::compact_pointToAnalyze()
{
    std::vector<Point *> tmpPoints;
    for ( ushort i = 0; i < pointToAnalyze[position].size(); i++ )
    {
        if ( pointToAnalyze[position][i] != NULL )
        {
            tmpPoints.push_back(pointToAnalyze[position][i]);
        }
    }

    pointToAnalyze[position].clear();

    for ( ushort i = 0; i < tmpPoints.size(); i++ )
    {
        pointToAnalyze[position].push_back(tmpPoints[i]);
    }
}

/** Release event
 *
 * This function is called by the inputData only when there was a complete release on the screen i.e: nothing is touching it.
 *
 * This function will reset the palm detection but keep the area where the pen was last. This is done so that the user can make small 
 * adjustments (points, commas...). If the pen area would not be saved then the pen would need to be re-detected causing a slowdown 
 * in user writing and not allowing the user to add small writing
 */
void PalmRejection::eventRelease(/*Points *point*/)
{
    //Disable penPresent, send release event to scribbleArea, clean buffer, and start palm reset timer
    if (penPresent)
    {
        scribble->screenReleaseEvent();
    }
   
    penPresent = false;
    flushPointBuffer();
    palmResetTimer->expires_from_now(boost::posix_time::seconds(RESET_TIMER));
    palmResetTimer->async_wait(boost::bind(&PalmRejection::resetPalm, this,_1));
}

/** Modulo function (always positive)
 * 
 * @param x The number to be divided (dividend)
 * @param m The "limit" (divisor) - If not entered it will automatically be the value of ANALYZEBUFFER
 * @return The positive modulo of input x
 * 
 * This function returns a positive modulo of x.
 * Default divisor is ANALYZEBUFFER however passing a second parameter to the function will overwrite it
 */
int PalmRejection::mod(int x, const int m)
{
    return (x % m + m) % m;
}

/** Absolute value function
 * 
 * @param x The integer of which we want the absolute value
 * @return The absolute value of x
 * 
 * This function return the absolute value of any integer
 */
int PalmRejection::abs(int x)
{
    if (x < 0)
        return -x;
    else
        return x;
}

/** Square root of an integer
 * 
 * @param x The integer that we need the square root of
 * @return The square root of the x parameter
 * 
 * This function is about 5 times faster than the sqrt() on the cmath library. It is less precise however this is not an issue in our case
 */
inline float PalmRejection::sqrt(const int x)
{

    union
    {
        int i;
        float x;
    } u;
    u.x = x;
    u.i = (1 << 29) + (u.i >> 1) - (1 << 22);
    return u.x;
}

float PalmRejection::getDistance(int currentPosition, int ignore)
{
    int size = pointToAnalyze[currentPosition].size();

    int x = 0;
    int y = 0;

    for ( int i = 0; i < size; i++ )
    {
        if ( i != ignore )
        {

            x += pointToAnalyze[currentPosition][i]->getX();
            y += pointToAnalyze[currentPosition][i]->getY();
        }
    }

    x = x / ( size - 1 );
    y = y / ( size - 1 );

    int distanceX = abs(x - pointToAnalyze[currentPosition][ignore]->getX());
    int distanceY = abs(y - pointToAnalyze[currentPosition][ignore]->getY());

    return sqrt(distanceX * distanceX + distanceY * distanceY);


}


/** Find the Pen
 *
 * This function determines which 4 consecutive points can be assumed to be a pen.
 *
 * The presence of a pen can be assumed whenever there are four points (in four different sets) that meet the following criteria:
 * - Two consecutive points have to be a minimum distance from each other without exceeding a maximum distance
 * - The total total distance between the four points need to be a minimum of 6 times the minimum distance between two consecutive points. 
 *
 */
void PalmRejection::findPen()
{

    //check in a point in the current set falls into the mPen area. If yes, assume it is the pen
    bool foundPen = false;
    for (int i = 0; i < (int) pointToAnalyze[position].size(); i++)
    {
        if (pointToAnalyze[position][i] != NULL)
        {
            //std::cout << "(pointToAnalyze[position][i]->getRow(): " << pointToAnalyze[position][i]->getRow() << " pointToAnalyze[position][i]->getColumn(): " << pointToAnalyze[position][i]->getColumn() << std::endl;
            if ( ( mPalm.possiblePen(pointToAnalyze[position][i]->getColumn(), pointToAnalyze[position][i]->getRow()) || mPen.isSet(pointToAnalyze[position][i]->getColumn(), pointToAnalyze[position][i]->getRow()) ) && !foundPen )// || ( pointToAnalyze[position][i]->getRow() > 4 ) ) )
            {


                scribble->screenPressEvent(pointToAnalyze[position][i]);
                //std::cout<<"Press -         findPen() first loop"<<std::endl;

                //NEW
                mPen.clearMatrix();

                mPen.setArea(pointToAnalyze[position][i]->getColumn(), pointToAnalyze[position][i]->getRow());

                mX = pointToAnalyze[position][i]->getX();
                mY = pointToAnalyze[position][i]->getY();

                pointToAnalyze[position][i] = NULL;
                penPresent = true;
                foundPen = true;

                //compact_pointToAnalyze();
                //updatePosition();
                //return;
            }
            else if ( pointToAnalyze[position][i] != NULL )
            {
                mPalm.setArea(pointToAnalyze[position][i]->getColumn(), pointToAnalyze[position][i]->getRow());
            }
        }
    }
    if ( foundPen )
    {
        return;
    }

    compact_pointToAnalyze();

    //std::cout << "from find pen" << std::endl;
    if ( firstTryFindingPenAndPalm() )
    {
        return;
    }
    //std::cout << "firstTryFindingPenAndPalm failed" << std::endl;

    compact_pointToAnalyze();

    //std::cout << "All failed, failing back on old method" << std::endl;

    //Used for set comparison to find possible points that will result in a pen. 
    int firstSet = mod(position - 3);
    int secondSet = mod(firstSet + 1);
    int thirdSet = mod(secondSet + 1);
    int forthSet = mod(thirdSet + 1);

    bool completeBreak = false;

    //    int pos[] = { firstSet, secondSet, thirdSet, forthSet };
    int where = 0;

    //for each point is the first set
    for ( ushort i = 0; i < pointToAnalyze[firstSet].size(); i++ )
    {
        if ( ( pointToAnalyze[firstSet][i] != NULL ) )
        {
            where = 1;
            //check if the point is in a possible pen area. If yes keep comparing points, otherwise set it as Palm area
            if ( !mPalm./*possiblePen*/isSet(pointToAnalyze[firstSet][i]->getColumn(), pointToAnalyze[firstSet][i]->getRow()) )
            {
                //for each point in the second set
                for ( ushort j = 0; j < pointToAnalyze[secondSet].size(); j++ )
                {
                    if ( ( pointToAnalyze[secondSet][j] != NULL ) )
                    {
                        where = 2;
                        //check if the point is in a possible pen area. If yes keep comparing points, otherwise set it as Palm area
                        if ( !mPalm./*possiblePen*/isSet(pointToAnalyze[secondSet][j]->getColumn(), pointToAnalyze[secondSet][j]->getRow()) )
                        {
                            //find which point corresponds to a possible pen, with limits (max and min)
                            //if found  do the same comparison between second and third
                            int deltaX_ij = pointToAnalyze[firstSet][i]->getX() - pointToAnalyze[secondSet][j]->getX();
                            int deltaY_ij = pointToAnalyze[firstSet][i]->getY() - pointToAnalyze[secondSet][j]->getY();
                            int radius_ij = sqrt(deltaX_ij * deltaX_ij + deltaY_ij * deltaY_ij);

                            //within acceptable movement of a pen
                            if ( radius_ij > MINIMUM_RADIUS && radius_ij < MAXIMUM_RADIUS )
                            {
                                //found 2 points that can be considered as a pen
                                //for each point in the third set
                                for ( ushort k = 0; k < pointToAnalyze[thirdSet].size(); k++ )
                                {
                                    if ( ( pointToAnalyze[thirdSet][k] != NULL ) )
                                    {
                                        where = 3;
                                        //check if the point is in a possible pen area. If yes keep comparing points, otherwise set it as Palm area
                                        if ( !mPalm./*possiblePen*/isSet(pointToAnalyze[thirdSet][k]->getColumn(), pointToAnalyze[thirdSet][k]->getRow()) )
                                        {
                                            //find which point corresponds to a possible pen, with limits (max and min)
                                            //if found do the same comparison between third and forth
                                            int deltaX_jk = pointToAnalyze[secondSet][j]->getX() - pointToAnalyze[thirdSet][k]->getX();
                                            int deltaY_jk = pointToAnalyze[secondSet][j]->getY() - pointToAnalyze[thirdSet][k]->getY();
                                            int radius_jk = sqrt(deltaX_jk * deltaX_jk + deltaY_jk * deltaY_jk);

                                            //within acceptable movement of a pen
                                            if ( radius_jk > MINIMUM_RADIUS && radius_jk < MAXIMUM_RADIUS )
                                            {
                                                //found 3 points that can be considered as a pen
                                                //for each point in the forth set
                                                for ( ushort l = 0; l < pointToAnalyze[forthSet].size(); l++ )
                                                {
                                                    if ( ( pointToAnalyze[forthSet][l] != NULL ) )
                                                    {
                                                        where = 4;
                                                        //check if the point is in a possible pen area. If yes keep comparing points, otherwise set it as Palm area
                                                        if ( !mPalm./*possiblePen*/isSet(pointToAnalyze[forthSet][l]->getColumn(), pointToAnalyze[forthSet][l]->getRow()) )
                                                        {
                                                            //find which point corresponds to a possible pen, with limits (max and min)
                                                            int deltaX_kl = pointToAnalyze[thirdSet][k]->getX() - pointToAnalyze[forthSet][l]->getX();
                                                            int deltaY_kl = pointToAnalyze[thirdSet][k]->getY() - pointToAnalyze[forthSet][l]->getY();
                                                            int radius_kl = sqrt(deltaX_kl * deltaX_kl + deltaY_kl * deltaY_kl);

                                                            int distance = radius_ij + radius_jk + radius_kl;

                                                            //Four points in four consecutive sets are determined to be a pen, use the point 
                                                            if ( ( radius_kl > MINIMUM_RADIUS ) && ( radius_kl < MAXIMUM_RADIUS ) && ( distance > ( 5 * MINIMUM_RADIUS ) ) )
                                                            {
                                                                //found 4 points that look like a pen
                                                                penPresent = true;

                                                                //NEW
                                                                mPen.clearMatrix();

                                                                //Save the last point coordinates and set the pen area
                                                                mPen.setArea(pointToAnalyze[forthSet][l]->getColumn(), pointToAnalyze[forthSet][l]->getRow());
                                                                mX = pointToAnalyze[forthSet][l]->getX();
                                                                mY = pointToAnalyze[forthSet][l]->getY();

                                                                //Send the four points to the acribbleArea for drawing
                                                                scribble->screenPressEvent(pointToAnalyze[firstSet][i]);
                                                                // std::cout<<"Press -         findPen() second loop"<<std::endl;
                                                                scribble->screenMoveEvent(pointToAnalyze[secondSet][j]);
                                                                scribble->screenMoveEvent(pointToAnalyze[thirdSet][k]);
                                                                scribble->screenMoveEvent(pointToAnalyze[forthSet][l]);

                                                                //Update palm matrix
                                                                mPalm.clearMatrix();

                                                                updatePalmMatrix(firstSet, i);
                                                                updatePalmMatrix(secondSet, j);
                                                                updatePalmMatrix(thirdSet, k);
                                                                updatePalmMatrix(forthSet, l);

                                                                mPalm.resetArea(pointToAnalyze[forthSet][l]->getColumn(), pointToAnalyze[forthSet][l]->getRow());

                                                                //set the used points to NULL since they belong to the scribble area now
                                                                pointToAnalyze[firstSet][i] = NULL;
                                                                pointToAnalyze[secondSet][j] = NULL;
                                                                pointToAnalyze[thirdSet][k] = NULL;
                                                                pointToAnalyze[forthSet][l] = NULL;

                                                                std::cout << "Got pen in old code" << std::endl;
                                                                completeBreak = true;
                                                                break;
                                                            }
                                                        }
                                                        else
                                                        {
                                                            mPalm.set(pointToAnalyze[forthSet][l]->getColumn(), pointToAnalyze[forthSet][l]->getRow());
                                                        }
                                                    }
                                                }
                                                if ( completeBreak )
                                                {
                                                    break;
                                                }
                                            }
                                        }
                                        else
                                        {
                                            mPalm.set(pointToAnalyze[thirdSet][k]->getColumn(), pointToAnalyze[thirdSet][k]->getRow());
                                        }
                                    }
                                }
                                if ( completeBreak )
                                {
                                    break;
                                }
                            }
                        }
                        else
                        {
                            mPalm.set(pointToAnalyze[secondSet][j]->getColumn(), pointToAnalyze[secondSet][j]->getRow());
                        }
                    }
                }
                if ( completeBreak )
                {
                    break;
                }
            }
            else
            {
                mPalm.set(pointToAnalyze[firstSet][i]->getColumn(), pointToAnalyze[firstSet][i]->getRow());
            }
        }
    }

    //if we didn't completely break it means we didn't find a pen, setting the value accordingly
    if ( !completeBreak )
    {
        scribble->screenReleaseEvent();
        penPresent = false;

        //        for ( int i = 0; i < where; i++ )
        //        {
        //            for ( int j = 0; j < pointToAnalyze[i].size(); j++ )
        //            {
        //                if(pointToAnalyze[pos[i]][j]!=NULL)
        //                {
        //                    mPalm.set(pointToAnalyze[pos[i]][j]->getColumn(), pointToAnalyze[pos[i]][j]->getRow());
        //                }                
        //            }
        //        }
    }

    //updatePosition();
}

/** Find adjacent points
 *
 * This function looks at a set of points and eliminates the adjacent ones.
 * The function will eliminate all the points in adjacent columns and/or rows with the exception of the one that is the furthest with respect to the previous acknowledge point
 */
void PalmRejection::analyzeNewSetOfPoints()
{
    int size = pointToAnalyze[position].size();

    //For each pair of point, verify if they are in adjacent areas
    // if yes:
    //  - if they are at a distance less that MIN_R eliminate one (eliminating the one furthest from the last point and keeping the closest one)
    //if no:
    //  - leave both points and let other functions (findPalm(), findPen()) take care of it
    for (int i = 0; i < size - 1; i++)
    {
        if (pointToAnalyze[position][i] != NULL)
        {
            for (int j = i + 1; j < size; j++)
            {
                if (pointToAnalyze[position][j] != NULL)
                {
                    int deltaColumn = abs(pointToAnalyze[position][i]->getColumn() - pointToAnalyze[position][j]->getColumn());
                    int deltaRow = abs(pointToAnalyze[position][i]->getRow() - pointToAnalyze[position][j]->getRow());

                    //If the points in the same set are in adjacent areas
                    if (deltaColumn == 1 || deltaRow == 1)
                    {
                        //If the radius is less than MIN_R, delete the point that is the furthest from last touch point
                        //and if that point does not exist eliminate the second point from the set
                        int deltaX = pointToAnalyze[position][i]->getX() - pointToAnalyze[position][j]->getX();
                        int deltaY = pointToAnalyze[position][i]->getY() - pointToAnalyze[position][j]->getY();

                        int radius = sqrt(deltaX * deltaX + deltaY * deltaY);

                        if (radius < MIN_R)
                        {
                            if (penPresent == true)// pen exists
                            {
                                int deltaXi = mX - pointToAnalyze[position][i]->getX();
                                int deltaYi = mY - pointToAnalyze[position][i]->getY();

                                int distance_i = sqrt(deltaXi * deltaXi + deltaYi * deltaYi);

                                int deltaXj = mX - pointToAnalyze[position][j]->getX();
                                int deltaYj = mY - pointToAnalyze[position][j]->getY();

                                int distance_j = sqrt(deltaXj * deltaXj + deltaYj * deltaYj);

                                if (distance_i < distance_j)
                                {
                                    delete pointToAnalyze[position][j];
                                    pointToAnalyze[position][j] = NULL;
                                }
                                else
                                {
                                    delete pointToAnalyze[position][i];
                                    pointToAnalyze[position][i] = NULL;
                                    break;
                                }
                            }//If no previous point then delete always delete the second point (how accurate is that?)
                            else // No Pen
                            {
                                delete pointToAnalyze[position][j];
                                pointToAnalyze[position][j] = NULL;
                            }
                        }
                    }
                }
            }
        }
    }
}

/** Update palm matrix
 * 
 * @param slot slot This variable represents the position in pointToAnalyze from which we need to update the palm matrix. Usually it will
 * correspond to the position variable however, at occasions, it can represent an older position
 * @param ignore ignore This variable represents which position in a given set of points corresponds to the pen point and should not be present on the palm matrix
 * 
 * This function updates the palm matrix by setting high all the areas pressed on the last sampling set with the exception
 * of the area where the pen has been determined to be present
 */
void PalmRejection::updatePalmMatrix(ushort slot, ushort ignore)
{
    for (ushort i = 0; i < pointToAnalyze[slot].size(); i++)
    {
        if ((pointToAnalyze[slot][i] != NULL) && (i != ignore))
        {
            mPalm.setArea(pointToAnalyze[slot][i]->getColumn(), pointToAnalyze[slot][i]->getRow());
        }
    }
}

/** Update variable position
 *
 * This function updates the position variable while making sure to delete all Point object that will no longer be needed
 */
void PalmRejection::updatePosition()
{
    position = mod(++position);

    for (uint i = 0; i < pointToAnalyze[position].size(); i++)
    {
        //Do not need to check for NULL since delete NULL has not effect
        delete pointToAnalyze[position][i];
    }
    pointToAnalyze[position].clear();
}

/** Find the next valid point
 *
 * This function iterates through the new set of points and determines which is the next valid point
 * It is possible that we do not find the next point which will cause a new search for the pen
 */
void PalmRejection::findNextPoint()
{
    //for all points available in pointToAnalyze[position]
    //compare distance to last saved mX and mY in mPen area
    //choose min?
    bool found = false;
    for (ushort i = 0; i < pointToAnalyze[position].size(); i++)
    {
        if (pointToAnalyze[position][i] != NULL)
        {
            //if the point is in the pen area and not in the palm area
            if ( mPen.isSet(pointToAnalyze[position][i]->getColumn(), pointToAnalyze[position][i]->getRow()) && !mPalm.isSet(pointToAnalyze[position][i]->getColumn(), pointToAnalyze[position][i]->getRow()) )
            {
                //std::cout << "Next point 
                // We should find the radius from the last point and make sure that we do not exceed a MAXIMUM (minimum not necessary)
                int Dx = mX - pointToAnalyze[position][i]->getX();
                int Dy = mY - pointToAnalyze[position][i]->getY();



                //if the new pen point is within the 
                if ( sqrt(Dx * Dx + Dy * Dy) < 2 * MAXIMUM_RADIUS ) //This was 2*MAXIMUM_RADIUS and worked well. testing with different values
                {
                    mX = pointToAnalyze[position][i]->getX();
                    mY = pointToAnalyze[position][i]->getY();
                    //Move the pen area to correspond to the newly found pen point
                    mPen.clearMatrix();
                    mPen.setArea(pointToAnalyze[position][i]->getColumn(), pointToAnalyze[position][i]->getRow());

                    //Update the palm area with the point(s) that do not correspond to the pen
                    mPalm.clearMatrix();

                    updatePalmMatrix(position, i);
                    mPalm.reset(pointToAnalyze[position][i]->getColumn(), pointToAnalyze[position][i]->getRow());

                    scribble->screenMoveEvent(pointToAnalyze[position][i]);
                    found = true;
                    pointToAnalyze[position][i] = NULL;
                    break;
                }//otherwise assume the new point represents a "new" pen by sending a release followed by a press events to the scribble area
                else
                {
                    continue;
                    //scribble->screenReleaseEvent();
                    //scribble->screenPressEvent(pointToAnalyze[position][i]);
                    //delete pointToAnalyze[position][i];
                    //std::cout<<"Press -         findNextPoint"<<std::endl;
                }

                //Set the sent point pointer to NULL since it is own by the scribble area now

                //break;

            }
        }
    }

    //if the pen was not found in the above loop then set penPresent to false which will initialize a search for a pen at the next event
    if (found == false)
    {
        scribble->screenReleaseEvent();
        penPresent = false;
    }
}

/** Flush the pointToAnalyze buffer
 *
 * This function is called whenever we want to completely flush all the points in the whole pointToAnalyze buffer
 */
void PalmRejection::flushPointBuffer()
{
    for (uint i = 0; i < ANALYZE_BUFFER; i++)
    {
        for (uint j = 0; j < pointToAnalyze[i].size(); j++)
        {
            delete pointToAnalyze[i][j];
        }
        pointToAnalyze[i].clear();
    }
    position = 0;
}
