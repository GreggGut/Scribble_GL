/*
 * File:   InputData.cpp
 * Author: greg
 *
 * Created on May 3, 2012, 10:43 AM
 */

#include "InputData.h"

/*! Default constructor
 *
 * \param *scribble A pointer to a ScribbleArea object
 *
 * This is a default constructor. It requires a pointer to the ScribbleArea so that it can send one of the three actions:
 * - <b>Press event:</b> <br>An event informing ScribbleArea that the screen has been pressed; includes the XY coordinates of the event.<pre></pre>
 * - <b>Move event:</b> <br>An event informing ScribbleArea that a move has occurred on the screen; includes the XY coordinates of the event.<pre></pre>
 * - <b>Release event:</b> <br>An event informing ScribbleArea of a complete release; nothing is touching the screen and no coordinates are sent.<pre></pre>
 */
InputData::InputData(ScreenInterpreter* s) : scribbleAreaAccess(s), stop_request(false), palm(s)
{
    //std::cout<<"Input Data constructed"<<std::endl;

}

InputData::~InputData()
{
    stop();
    std::cout << "Destructor InputData" << std::endl;
    delete mPointsQueue;

    //TODO this should be enabled but crashes the app, we need a nice way to end this
    //close(fd);
    //    /palm.stop();
    //palm.wait();
    //palm.terminate();
    //std::cout << " InputData over: " << palm.isFinished() << std::endl;
}

/*! Open input port
 *
 * \returns <i>File descriptor</i> - An integer representing the file descriptor corresponding to the port
 *
 * An negative value indicates an error
 */
int InputData::open_port()
{

    int fd; /* File descriptor for the port */
    fd = open("/dev/ttyUSB0", O_RDWR | O_NOCTTY | O_NDELAY);
    if (fd == -1)
    {
        //Could not open the port.
        perror("open_port: Unable to open /dev/ttyUSB0 - ");
        //exit(CANNOT_OPEN_PORT);
    } else
    {
        //fcntl(fd, F_SETFL, O_DIRECT); //linux
    }
    return (fd);
}

/*! Stop thread
 *
 * This function stops the thread by exiting the main loop
 *
 * <b>NEED TO FIND A WAY TO EXIT THE MAIN LOOK SINCE FOR NOW IT WILL WAIT UNTIL YOU TOUCH THE SCREEN</b>
 */
void InputData::stop()
{
    stop_request = true;
    //delete this;
}

/*! Run thread
 *
 * This is where the main implementation of the thread occurs. This function runs until the stop function is called at which point it will terminate**
 *
 * Do <b>NOT</b> call this function directly. Use InputData::start() to start the thread.
 *
 * ** Need to be implemented properly. The issue now is that the reading from the port is blocking and wait until something occurs at the USB port.
 */
void InputData::run()
{
    fd = open_port();

    //Used to pass the pointer to the point to the scibblearea to be drawn
    //Point action_Point;
    //    QPoint* tPoint;

    if (fd != -1)
    {
        initialise_port(fd);
        fcntl(fd, F_SETFL, FNDELAY);
    } else
    {
        std::cout << "Cannot open input port..." << std::endl;
        return;
        //exit(CANNOT_OPEN_PORT);
        // return; // (int*) - 1;
    }

    fcntl(fd, F_SETFL, 0); //FASYNC);//0);
    int char_from_serial;

    int start_bit_1;
    int start_bit_2;

    mPointsQueue = new queue<Point* >;

    /*
     * Events:
     * 0 - Touch event
     * 1 - Move event
     * 2 - Up event
     */
    bool event = false;
    int number_of_points;

    while (!stop_request)
    {
        //std::cout<<"running..."<<std::endl;
        read(fd, &start_bit_1, sizeof (char));
        start_bit_1 = start_bit_1 & CROP;

        //This look makes sure we are synchronized with the input data stream
        while (!stop_request)
        {
            read(fd, &start_bit_2, sizeof (char));
            start_bit_2 = start_bit_2 & CROP;

            //std::cout<<"start bit 1 = "<<start_bit_1<< "\n start bit 2 = "<<start_bit_2<<"\n";

            if ((start_bit_1 == 0xc0) && start_bit_2 == 0xf0)
            {
                break;
            }
            start_bit_1 = start_bit_2;
            std::cout << "synchronizing start bits" << std::endl;
        }

        number_of_points = 0;
        /*int c = */read(fd, &number_of_points, sizeof (char));

        if (number_of_points == 0)
        {
            //action_Point = NULL;
            palm.eventRelease();
            //scribbleAreaAccess->eventRelease(/*action_Point*/);
            event = false;
        } else
        {
            //Getting the first Press event
            Point* action_Point = read_data_from_file(fd);
            if (action_Point != NULL)
            {
                mPointsQueue->push(action_Point);
            }

            //std::cout << "x: " << action_Point->getX() << " y: " << action_Point->getY() << " Cx: " << action_Point->getColumn() << " Rx: " << action_Point->getRow() << std::endl;
            //if (action_Point != NULL)
            {
                //std::cout << "x: " << action_Point->getX() << " y: " << action_Point->getY() << " Cx: " << action_Point->getColumn() << " Rx: " << action_Point->getRow() << std::endl;

            }
            //For multi-touch, all points ignored for now
            for (int i = 1; i < number_of_points; i++)
            {
                //Get point and ignore it
                action_Point = read_data_from_file(fd);
                if (action_Point != NULL)
                {
                    mPointsQueue->push(action_Point);
                }
                //if (action_Point != NULL)
                //{
                //    delete action_Point;
                //}
                //std::cout<<"Multiple touch x:"<<action_Point.getX()<<std::endl;
            }
        }

        char_from_serial = 0;
        read(fd, &char_from_serial, sizeof (char));
        char_from_serial = char_from_serial & 0xff;
        if (char_from_serial == 0xf0)
        {
            char_from_serial = 0;
            read(fd, &char_from_serial, sizeof (char));
            char_from_serial = char_from_serial & 0xff;
            if (char_from_serial == 0xc0)
            {
                //send point to be drawn only after receiving the termination bits (0xF0 0xC0)
                while (mPointsQueue->size() > 0)
                {
                    if (event)
                    {
                        //std::cout << "Case 1" << std::endl;
                        palm.eventMove(mPointsQueue);
                        //scribbleAreaAccess->screenPressEvent(mPointsQueue.front());
                        while (!mPointsQueue->empty())
                        {
                            mPointsQueue->pop();
                        }
                        //scribbleAreaAccess->screenMoveEvent(mPointsQueue.front());
                        //mPointsQueue.pop();
                        //std::cout << " Move event" << std::endl;

                    } else
                    {
                        //std::cout << "Case 0" << std::endl;
                        palm.eventTouch(mPointsQueue);
                        //scribbleAreaAccess->screenPressEvent(mPointsQueue.front());
                        while (!mPointsQueue->empty())
                        {
                            mPointsQueue->pop();
                        }
                        event = true;
                        //std::cout << " Touch event" << std::endl;
                    }
                }
                continue;
            } else
            {
                while (mPointsQueue->size() > 0)
                {
                    mPointsQueue->pop();
                }
                continue;
            }
        } else
        {
            while (mPointsQueue->size() > 0)
            {
                mPointsQueue->pop();
            }
            continue;
        }
        char_from_serial = 0;
    }

    delete mPointsQueue;
}

/*! Read data from the port
 *
 * \param fd The integer representing the USB input file descriptor
 *
 * \return <i>Points*</i> - A pointer to the newly created Points object
 *
 * This function gathers the data from the USB port and converts it into a Points object, returning a pointer to it or NULL in the case the conversion failed.
 */
Point* InputData::read_data_from_file(int fd)
{
    //Gathering the X and Y points
    column = 0;
    row = 0;
    read(fd, &column, sizeof (char));
    read(fd, &row, sizeof (char));
    read(fd, &uX, sizeof (char));
    read(fd, &lX, sizeof (char));
    read(fd, &uY, sizeof (char));
    read(fd, &lY, sizeof (char));

    //Removing any possible garbage
    /*
    column = column & CROP;
    row = row & CROP;
     */
    column = column & CROP;
    row = row & CROP;
    uX = uX & CROP;
    lX = lX & CROP;
    uY = uY & CROP;
    lY = lY & CROP;

    //Creating the X and Y point
    uX = uX << 8;
    uY = uY << 8;
    int Y = ((uX + lX) * HEIGHT / 1024); //done to scale to the screen
    int X = ((uY + lY) * WIDTH / 1024); //done to scale to the screen

    //For testing purpose
    //printf(" Before creating object: %x, %x, %x, %x, %x, %x , %x, %x",column, row, uX, lX, uY, lY ,X,Y);
    //std::cout<<std::endl;
    //std::cout<<"Column: "<<column<<" row: "<<row<<std::endl;

    //Point point;
    if (X >= 0 && X <= WIDTH && Y >= 0 && Y <= HEIGHT)
    {
        return new Point(column, row, X, Y);
    }
    std::cout << "Point not created" << std::endl;
    return NULL;
}

/*! Initialize the USB port
 *
 * \param fd The file descriptor corresponding to the open USB port
 *
 * This function initializes the speed and other characteristics of a serial port
 */
void InputData::initialise_port(int fd)
{
    struct termios options;

    //Get the current options for the port...
    tcgetattr(fd, &options);

    //Set the baud rates to 115200...
    cfsetispeed(&options, B115200);
    cfsetospeed(&options, B115200);

    //Set the new options for the port...
    options.c_cflag &= ~PARENB;
    options.c_cflag &= ~CSTOPB;
    options.c_cflag &= ~CSIZE;
    options.c_cflag |= CS8;

    // Raw input, no echo
    options.c_lflag &= ~(ECHO | ECHOE | ECHONL | ICANON | IEXTEN | ISIG);
    options.c_iflag &= ~(IGNBRK | BRKINT | PARMRK | ISTRIP | INLCR | IGNCR | ICRNL | IXON | IXOFF | IXANY | INPCK);

    //Enable the receiver and set local mode...
    options.c_cflag |= (CLOCAL | CREAD);

    // Flush any buffered characters
    tcflush(fd, TCIOFLUSH);

    // Set the new options for the port...
    tcsetattr(fd, TCSAFLUSH, &options);
}