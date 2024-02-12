#define PLAY_IMPLEMENTATION
#define PLAY_USING_GAMEOBJECT_MANAGER
#include "Play.h"

int DISPLAY_WIDTH = 360;
int DISPLAY_HEIGHT = 360;
int DISPLAY_SCALE = 4;

void MainGameEntry(PLAY_IGNORE_COMMAND_LINE)
{
    Play::CreateManager(DISPLAY_WIDTH, DISPLAY_HEIGHT, DISPLAY_SCALE);
}

int exampleId = 0;

bool MainGameUpdate(float elapsedTime)
{

    Play::ClearDrawingBuffer(Play::cBlack);

    const Vector2f center = { DISPLAY_WIDTH / 2, DISPLAY_HEIGHT / 2 };
    const float unitLength = center.x / 2;

    if (Play::KeyPressed(KEY_PAGE_UP))
    {
        exampleId++;
    }
    else if (Play::KeyPressed(KEY_PAGE_DOWN))
    {
        exampleId--;
        if (exampleId < 0)
            exampleId = 0;
    }

    switch (exampleId)
    {
    case 0:
    {
        Play::Window::SetTitle("Sine and Cosine");

        static float radians = 0;

        static bool paused = false;
        if (!paused)
        {
            radians += Play::DegToRad(1);
        }
        if (Play::KeyPressed(KEY_P))
        {
            paused = !paused;
        }

        Play::DrawCircle(center, unitLength, { 20.0f, 20.0f, 20.0f });

        Play::DrawLine({ 0, center.y }, { DISPLAY_WIDTH, center.y }, Play::cGrey);
        Play::DrawLine({ center.x, 0 }, { center.x, DISPLAY_HEIGHT }, Play::cGrey);
        
        Play::DrawPixel(center, { 30.0f, 30.0f, 30.0f });

        float c = center.x + cosf(radians) * unitLength;
        float s = center.y + sinf(radians) * unitLength;

        Play::DrawCircle({c, center.y}, 4, Play::cRed);
        Play::DrawCircle({center.x, s}, 4, Play::cGreen);

        static bool showPointOnCircle = false;
        if (Play::KeyPressed(KEY_SPACE))
        {
            showPointOnCircle = !showPointOnCircle;
        }
        if (showPointOnCircle)
        {
            Play::DrawLine(center, { c, s }, Play::cBlue);
        }

        std::string degText = "Deg    = " + std::to_string(((int)Play::RadToDeg(radians) % 360));
        std::string radText = "R      = " + std::to_string(radians);
        std::string sinText = "sin(R) = " + std::to_string(sinf(radians));
        std::string cosText = "cos(R) = " + std::to_string(cosf(radians));
        Play::DrawDebugText({ 2, 8 }, sinText.c_str(), Play::cGreen, false);
        Play::DrawDebugText({ 2, 22 }, cosText.c_str(), Play::cRed, false);
        Play::DrawDebugText({ 2, 36 }, radText.c_str(), Play::cBlue, false);
        Play::DrawDebugText({ 2, 50 }, degText.c_str(), Play::cWhite, false);

        Play::DrawDebugText({ 2, DISPLAY_HEIGHT - 10 }, "<P> to pause", Play::cWhite, false);
        Play::DrawDebugText({ 2, DISPLAY_HEIGHT - 26 }, "<SPACE> to show R vector", Play::cWhite, false);

        break;
    }
    case 1:
    {
        Play::Window::SetTitle("Sinewave");

        static float radians = 0;

        static bool paused = false;
        if (!paused)
        {
            radians += Play::DegToRad(2);
        }
        if (Play::KeyPressed(KEY_P))
        {
            paused = !paused;
        }

        Play::DrawCircle(center, unitLength, { 20.0f, 20.0f, 20.0f });

        Play::DrawLine({ 0, center.y }, { DISPLAY_WIDTH, center.y }, Play::cGrey);
        Play::DrawLine({ center.x, 0 }, { center.x, DISPLAY_HEIGHT }, Play::cGrey);

        Play::DrawPixel(center, { 30.0f, 30.0f, 30.0f });

        float s = center.y + sinf(radians) * unitLength;

        static std::vector<Point2D> points;

        Vector2f newPoint = { center.x, s };
        Play::DrawCircle(newPoint, 4, Play::cGreen);

        if (!paused)
            points.push_back(newPoint);

        if (points.size() > DISPLAY_WIDTH / 2)
            points.erase(points.begin());

        for (auto& point : points)
        {
            point.x -= 1 * (int)(!paused); // only scroll if not paused
            Play::DrawPixel(point, Play::cGreen);
        }

        std::string degText = "Deg    = " + std::to_string(((int)Play::RadToDeg(radians) % 360));
        std::string radText = "R      = " + std::to_string(radians);
        std::string sinText = "sin(R) = " + std::to_string(sinf(radians));
        Play::DrawDebugText({ 2, 8 }, sinText.c_str(), Play::cGreen, false);
        Play::DrawDebugText({ 2, 22 }, radText.c_str(), Play::cBlue, false);
        Play::DrawDebugText({ 2, 36 }, degText.c_str(), Play::cWhite, false);

        Play::DrawDebugText({ 2, DISPLAY_HEIGHT - 10 }, "<P> to pause", Play::cWhite, false);

        break;
    }
    case 2:
    {
        Play::Window::SetTitle("Rotating X and Y axis");
        static float totalTime = 0;
        totalTime += elapsedTime;

        Vector2f start = center;
        Vector2f end = start;
        end += Vector2f{ cosf(totalTime), sinf(totalTime) } * unitLength;
        Play::DrawLine(start, end, Play::cRed);
        Play::DrawDebugText(end, "x");
        end = start + Vector2f{ -sinf(totalTime), cosf(totalTime) } * unitLength;
        Play::DrawLine(start, end, Play::cGreen);
        Play::DrawDebugText(end, "y");
        break;
    }
    case 3:
    {
        Play::Window::SetTitle("Drawing a grid and random points");
        
        int gridSize = 8;

        for (int x = 0; x < DISPLAY_WIDTH; x += gridSize)
        {
            Vector2f start = { x, 0 };
            Vector2f end = { x, DISPLAY_HEIGHT };
            Play::DrawLine(start, end, Play::cGrey);
        }
        for (int y = 0; y < DISPLAY_HEIGHT; y += gridSize)
        {
            Vector2f start = { 0, y };
            Vector2f end = { DISPLAY_WIDTH, y };
            Play::DrawLine(start, end, Play::cGrey);
        }

        static int x_coords[10] = {
            RandomRoll(DISPLAY_WIDTH),
            RandomRoll(DISPLAY_WIDTH),
            RandomRoll(DISPLAY_WIDTH),
            RandomRoll(DISPLAY_WIDTH),
            RandomRoll(DISPLAY_WIDTH),
            RandomRoll(DISPLAY_WIDTH),
            RandomRoll(DISPLAY_WIDTH),
            RandomRoll(DISPLAY_WIDTH),
            RandomRoll(DISPLAY_WIDTH),
            RandomRoll(DISPLAY_WIDTH)
        };
        static int y_coords[10] = {
            RandomRoll(DISPLAY_HEIGHT),
            RandomRoll(DISPLAY_HEIGHT),
            RandomRoll(DISPLAY_HEIGHT),
            RandomRoll(DISPLAY_HEIGHT),
            RandomRoll(DISPLAY_HEIGHT),
            RandomRoll(DISPLAY_HEIGHT),
            RandomRoll(DISPLAY_HEIGHT),
            RandomRoll(DISPLAY_HEIGHT),
            RandomRoll(DISPLAY_HEIGHT),
            RandomRoll(DISPLAY_HEIGHT)
        };

        for (int i = 0; i < 10; i++)
        {
            Vector2f point = { x_coords[i], y_coords[i] };
            Play::DrawCircle(point, 2, Play::cRed);
        }

        break;
    }
    case 4:
    {
        Play::Window::SetTitle("Vector length");

        Play::DrawCircle(center, unitLength, { 30.0f, 30.0f, 30.0f });
        Play::DrawPixel(center, { 30.0f, 30.0f, 30.0f });

        static Vector2f start = center;
        static Vector2f end = center + Vector2f{ unitLength, 0 };

        Vector2f mPos = Play::GetMousePos();

        static int selected = 0;

        if (Play::GetMouseButton(Play::LEFT))
        {
            if ((mPos - start).Length() < 4.0f)
            {
                selected = 1;
            }
            else if ((mPos - end).Length() < 4.0f)
            {
                selected = 2;
            }
        }
        else
        {
            selected = 0;
        }

        if (selected == 1)
            start = mPos;
        else if (selected == 2)
            end = mPos;

        Vector2f v = (end - start);
        float length = v.Length() / unitLength;
        
        std::string lenStr = "length = " + std::to_string(length);
        Play::DrawDebugText(((start + end) / 2) + Vector2f(0, 12), lenStr.c_str(), Play::cWhite);
        Play::DrawCircle(start, 4, Play::cGrey);
        Play::DrawCircle(end, 4, Play::cGrey);
        Play::DrawLine(start, end, Play::cRed);

        break;
    }
    case 5:
    {
        Play::Window::SetTitle("Dot product");

        Play::DrawCircle(center, unitLength, { 30.0f, 30.0f, 30.0f });
        
        static Vector2f a = center + Vector2f{ unitLength, 0 };
        static Vector2f b = center + Vector2f{ 0, unitLength };

        Vector2f mPos = Play::GetMousePos();
        
        static int selected = 0;

        if (Play::GetMouseButton(Play::LEFT))
        {
            if ((mPos - b).Length() < 4.0f)
            {
                selected = 1;
            }
            else if ((mPos - a).Length() < 4.0f)
            {
                selected = 2;
            }
        }
        else
        {
            selected = 0;
        }

        if (selected == 1)
            b = mPos;
        else if (selected == 2)
            a = mPos;

        Vector2f A = (center - a) / unitLength;
        Vector2f B = (center - b) / unitLength;
        float adotb = A.Dot(B);

        Play::DrawCircle(a, 4, Play::cGrey);
        Play::DrawCircle(b, 4, Play::cGrey);
        Play::DrawLine(center, a, Play::cRed);
        Play::DrawLine(center, b, Play::cGreen);
        Play::DrawDebugText(a - (Play::normalize(A) * 8), "a", Play::cWhite);
        Play::DrawDebugText(b - (Play::normalize(B) * 8), "b", Play::cWhite);

        static bool showDotVector = false;
        if (Play::KeyPressed(KEY_SPACE))
        {
            showDotVector = !showDotVector;
        }
        if (showDotVector)
        {
            DrawLine(center, center - A * adotb * unitLength, Play::cCyan);
        }

        std::string dotStr = "a.Dot(b) = " + std::to_string(adotb);
        Play::DrawDebugText({ 2, 8 }, dotStr.c_str(), Play::cWhite, false);

        break;
    }
    case -1:
        exampleId = 0; // Set this to last example to be able to loop backwards
        break;
    default:
        exampleId = 0;
        break;
    }

    Play::PresentDrawingBuffer();
    return Play::KeyDown(KEY_ESCAPE);
}

int MainGameExit(void)
{
    Play::DestroyManager();
    return PLAY_OK;
}
