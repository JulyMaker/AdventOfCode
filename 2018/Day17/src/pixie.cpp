#include <string.h>
#include <ctype.h>
#include <Windows.h>
#include "pixie.h"

#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN

using namespace Pixie;

Window::Window()
{
  m_delta = 0.0f;
  m_pixels = 0;
  m_zoom2x = false;

  assert(sizeof(m_mouseButtonDown) == sizeof(m_lastMouseButtonDown));
  memset(m_mouseButtonDown, 0, sizeof(m_mouseButtonDown));
  memset(m_lastMouseButtonDown, 0, sizeof(m_lastMouseButtonDown));

  memset(m_inputCharacters, 0, sizeof(m_inputCharacters));
  assert(sizeof(m_keyDown) == sizeof(m_lastKeyDown));
  memset(m_lastKeyDown, 0, sizeof(m_lastKeyDown));
  memset(m_keyDown, 0, sizeof(m_keyDown));

  PlatformInit();
}

Window::~Window()
{
  delete[] m_pixels;
}

bool Window::Open(const wchar_t* title, int width, int height, bool zoom2x /*= false*/)
{
  // Create the buffer first because on OSX we need it to exist when initialising.
  m_pixels = new uint32_t[width * height];
  m_width = width;
  m_height = height;
  m_zoom2x = zoom2x;
  m_time = 0.0f;

  if (!PlatformOpen(title, width, height))
  {
    delete[] m_pixels;
    m_pixels = 0;
    return false;
  }

  return true;
}

bool Window::Update()
{
  UpdateMouse();
  UpdateKeyboard();
  bool result = PlatformUpdate();
  m_time += m_delta;
  return result;
}

void Window::Close()
{
  PlatformClose();
}

void Window::UpdateMouse()
{
  memcpy(m_lastMouseButtonDown, m_mouseButtonDown, sizeof(m_mouseButtonDown));
}

void Window::UpdateKeyboard()
{
  memset(m_inputCharacters, 0, sizeof(m_inputCharacters));
  memcpy(m_lastKeyDown, m_keyDown, sizeof(m_keyDown));
}

void Window::AddInputCharacter(char c)
{
  if (!isprint(c))
    return;

  int length = (int)strlen(m_inputCharacters);
  if (length + 1 < sizeof(m_inputCharacters))
  {
    m_inputCharacters[length] = c;
    m_inputCharacters[length + 1] = 0;
  }
}

static const char* PixieWindowClass = "PixieWindowClass";
static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

void Window::PlatformInit()
{
  assert(sizeof(HWND) == sizeof(void*));

  for (int i = 0; i < Key_Num; i++)
    m_keyMap[i] = -1;
  m_keyMap[Key_Escape] = VK_ESCAPE;
  m_keyMap[Key_Up] = VK_UP;
  m_keyMap[Key_Down] = VK_DOWN;
  m_keyMap[Key_Left] = VK_LEFT;
  m_keyMap[Key_Right] = VK_RIGHT;
  m_keyMap[Key_Home] = VK_HOME;
  m_keyMap[Key_End] = VK_END;
  m_keyMap[Key_Backspace] = VK_BACK;
  m_keyMap[Key_Delete] = VK_DELETE;
  m_keyMap[Key_LeftShift] = VK_LSHIFT;
  m_keyMap[Key_RightShift] = VK_RSHIFT;
  m_keyMap[Key_Space] = VK_SPACE;
  m_keyMap[Key_F1] = VK_F1;
  m_keyMap[Key_F2] = VK_F2;
  m_keyMap[Key_F3] = VK_F3;
  m_keyMap[Key_Plus] = VK_OEM_PLUS;
  m_keyMap[Key_Minus] = VK_OEM_MINUS;
  m_keyMap[Key_A] = 'A';
}

bool Window::PlatformOpen(const wchar_t* title, int width, int height)
{
  HINSTANCE hInstance = GetModuleHandle(0);

  WNDCLASS wc;
  wc.style = 0;
  wc.lpfnWndProc = WndProc;
  wc.cbClsExtra = 0;
  wc.cbWndExtra = 0;
  wc.hInstance = hInstance;
  wc.hIcon = NULL;
  wc.hCursor = LoadCursor(NULL, IDC_ARROW);
  wc.hbrBackground = NULL;
  wc.lpszMenuName = NULL;
  wc.lpszClassName = PixieWindowClass;

  if (!RegisterClass(&wc))
    return false;

  if (m_zoom2x)
  {
    width <<= 1;
    height <<= 1;
  }

  int style = WS_BORDER | WS_CAPTION;
  RECT rect;
  rect.left = 0;
  rect.right = width;
  rect.top = 0;
  rect.bottom = height;
  AdjustWindowRect(&rect, style, FALSE);

  int xPos = (GetSystemMetrics(SM_CXSCREEN) - rect.right) >> 1;
  int yPos = (GetSystemMetrics(SM_CYSCREEN) - rect.bottom) >> 1;

  width = rect.right - rect.left;
  height = rect.bottom - rect.top;

  char* titleAux = (char*) title;
  HWND window = CreateWindow(PixieWindowClass, titleAux, style, xPos, yPos, width, height, NULL, NULL, hInstance, NULL);
  m_window = (HWND)window;
  if (window == 0)
    return false;

  SetWindowLongPtr(window, GWLP_USERDATA, (LONG_PTR)this);
  ShowWindow(window, SW_SHOW);

  QueryPerformanceFrequency((LARGE_INTEGER*)&m_freq);
  QueryPerformanceCounter((LARGE_INTEGER*)&m_lastTime);

  return true;
}

bool Window::PlatformUpdate()
{
  // Update mouse cursor location.
  POINT p;
  GetCursorPos(&p);
  ScreenToClient((HWND)m_window, &p);
  m_mouseX = p.x;
  m_mouseY = p.y;

  if (m_zoom2x)
  {
    m_mouseX >>= 1;
    m_mouseY >>= 1;
  }

  __int64 time;
  QueryPerformanceCounter((LARGE_INTEGER*)&time);
  __int64 delta = time - m_lastTime;
  m_delta = (delta / (float)m_freq);
  m_lastTime = time;

  MSG msg;
  while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
  {
    TranslateMessage(&msg);
    DispatchMessage(&msg);

    if (msg.message == WM_QUIT)
      return false;
  }

  // Copy buffer to the window.
  HDC hdc = GetDC((HWND)m_window);
  BITMAPINFO bitmapInfo;
  BITMAPINFOHEADER& bmiHeader = bitmapInfo.bmiHeader;
  bmiHeader.biSize = sizeof(BITMAPINFOHEADER);
  bmiHeader.biWidth = m_width;
  bmiHeader.biHeight = -(int32_t)m_height; // Negative indicates a top-down DIB. Otherwise DIB is bottom up.
  bmiHeader.biPlanes = 1;
  bmiHeader.biBitCount = 32;
  bmiHeader.biCompression = BI_RGB;
  bmiHeader.biSizeImage = 0;
  bmiHeader.biXPelsPerMeter = 0;
  bmiHeader.biYPelsPerMeter = 0;
  bmiHeader.biClrUsed = 0;
  bmiHeader.biClrImportant = 0;
  if (m_zoom2x)
  {
    StretchDIBits(hdc, 0, 0, m_width << 1, m_height << 1, 0, 0, m_width, m_height, m_pixels, &bitmapInfo, DIB_RGB_COLORS, SRCCOPY);
  }
  else
  {
    SetDIBitsToDevice(hdc, 0, 0, m_width, m_height, 0, 0, 0, m_height, m_pixels, &bitmapInfo, DIB_RGB_COLORS);
  }
  ReleaseDC((HWND)m_window, hdc);

  return true;
}

void Window::PlatformClose()
{
  DestroyWindow((HWND)m_window);
}

WPARAM MapLeftRightKeys(WPARAM vk, LPARAM lParam)
{
  WPARAM newVk = vk;
  UINT scancode = (lParam & 0x00ff0000) >> 16;
  int extended = (lParam & 0x01000000) != 0;

  switch (vk)
  {
  case VK_SHIFT:
  {
    newVk = MapVirtualKey(scancode, MAPVK_VSC_TO_VK_EX);
    break;
  }

  case VK_CONTROL:
  {
    newVk = extended ? VK_RCONTROL : VK_LCONTROL;
    break;
  }

  case VK_MENU:
  {
    newVk = extended ? VK_RMENU : VK_LMENU;
    break;
  }

  default:
  {
    // Not a key we map from generic to left/right specialized.
    newVk = vk;
    break;
  }
  }

  return newVk;
}

static LRESULT CALLBACK WndProc(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam)
{
  Window* window = (Window*)GetWindowLongPtr(hWnd, GWLP_USERDATA);
  if (window)
  {
    switch (msg)
    {
    case WM_LBUTTONDOWN:
    case WM_MBUTTONDOWN:
    case WM_RBUTTONDOWN:
    {
      MouseButton button = MouseButton_Left;
      if (msg == WM_MBUTTONDOWN) button = MouseButton_Middle;
      if (msg == WM_RBUTTONDOWN) button = MouseButton_Right;
      window->SetMouseButtonDown(button, true);
      break;
    }

    case WM_LBUTTONUP:
    case WM_MBUTTONUP:
    case WM_RBUTTONUP:
    {
      MouseButton button = MouseButton_Left;
      if (msg == WM_MBUTTONUP) button = MouseButton_Middle;
      if (msg == WM_RBUTTONUP) button = MouseButton_Right;
      window->SetMouseButtonDown(button, false);
      break;
    }

    case WM_KEYDOWN:
    case WM_SYSKEYDOWN:
    {
      if (wParam < 256)
      {
        wParam = MapLeftRightKeys(wParam, lParam);
        window->SetKeyDown((int)wParam, true);
      }
      break;
    }

    case WM_KEYUP:
    case WM_SYSKEYUP:
    {
      if (wParam < 256)
      {
        wParam = MapLeftRightKeys(wParam, lParam);
        window->SetKeyDown((int)wParam, false);
      }
      break;
    }

    case WM_CHAR:
    {
      if (wParam < 256)
        window->AddInputCharacter((char)wParam);
      break;
    }

    case WM_DESTROY:
    {
      PostQuitMessage(0);
      break;
    }
    }
  }

  return DefWindowProc(hWnd, msg, wParam, lParam);
}

#if defined(PIXIE_NORMALISE_MAIN)
extern int main(int argc, char** argv);

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hInstPrev, LPSTR lpCmdLine, int nCmdShow)
{
  return main(__argc, __argv);
}
#endif