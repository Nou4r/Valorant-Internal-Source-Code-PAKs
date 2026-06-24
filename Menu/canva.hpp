#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include <Windows.h>
#include <string>
#include <vector>
#include <algorithm>

wchar_t* s2wc(const char* c)
{
	const size_t cSize = strlen(c) + 1;
	wchar_t* wc = new wchar_t[cSize];
	mbstowcs(wc, c, cSize);

	return wc;
}

static float wm_rainbowTime_v2 = 0.0f;
static ULONGLONG wm_lastTick_v2 = 0;

static flinearcolor wm_HSVtoRGB(float h, float s, float v)
{
	float R = 0, G = 0, B = 0;
	int   i = static_cast<int>(h * 6);
	float f = h * 6.0f - i;
	float p = v * (1.0f - s);
	float q = v * (1.0f - f * s);
	float t = v * (1.0f - (1.0f - f) * s);
	switch (i % 6) {
	case 0: R = v; G = t; B = p; break;
	case 1: R = q; G = v; B = p; break;
	case 2: R = p; G = v; B = t; break;
	case 3: R = p; G = q; B = v; break;
	case 4: R = t; G = p; B = v; break;
	default:R = v; G = p; B = q; break;
	}
	return flinearcolor{ R, G, B, 1.0f };
}

namespace menu
{
	// --- EN ÜST KISIM: DEĞİŞKENLER VE TEMEL ÇİZİM FONKSİYONLARI ---
	uobject* font;
	ucanvas* canvas;

	void SetupCanvas(ucanvas* _canvas)
	{
		canvas = _canvas;
	}

	flinearcolor RGBtoFLC(float r, float g, float b, float a = 1.0f)
	{
		float gamma = 1.8f;
		return {
			powf(r / 255.0f, gamma),
			powf(g / 255.0f, gamma),
			powf(b / 255.0f, gamma),
			a
		};
	}

	flinearcolor RGBtoFLC2(float r, float g, float b, float a = 1.0f)
	{
		return { r / 255, g / 255, b / 255, a };
	}

	flinearcolor HSVtoRGB(float h, float s, float v) {
		float r, g, b;

		int i = static_cast<int>(h * 6);
		float f = h * 6 - i;
		float p = v * (1 - s);
		float q = v * (1 - f * s);
		float t = v * (1 - (1 - f) * s);

		switch (i % 6) {
		case 0: r = v; g = t; b = p; break;
		case 1: r = q; g = v; b = p; break;
		case 2: r = p; g = v; b = t; break;
		case 3: r = p; g = q; b = v; break;
		case 4: r = t; g = p; b = v; break;
		case 5: r = v; g = p; b = q; break;
		default: r = g = b = 0.0f;
		}

		return flinearcolor{ r, g, b, 1.0f };
	}

	void xDrawTextRGB(const wchar_t* text, float x, float y, flinearcolor color)
	{
		canvas->k2_drawtext(font, text, { x, y }, { 1.1, 1.1 }, { 1.f,1.f,1.f,1.0f }, 0.f, { 0, 0, 0, 1 }, { 0, 0 }, 0, 0, 0, { 0, 0, 0, 1 });
	}

	void yDrawTextRGB(const wchar_t* text, float x, float y, flinearcolor color)
	{
		canvas->k2_drawtext(font, text, { x, y }, { 1.1, 1.1 }, { 1.f,1.f,1.f,1.0f }, 0.f, { 0, 0, 0, 1 }, { 0, 0 }, 1, 0, 0, { 0, 0, 0, 1 });
	}

	void TextLeft(const wchar_t* name, fvector2d pos, flinearcolor color, bool outline)
	{
		xDrawTextRGB(name, pos.x, pos.y, { 1,1,1,1 });
	}

	void TextCenter(const wchar_t* name, fvector2d pos, flinearcolor color, bool outline, bool kekw = 0)
	{
		if (kekw)
			yDrawTextRGB(name, pos.x, pos.y - 10, color);
		else
			yDrawTextRGB(name, pos.x, pos.y - 10, { 1.f,1.f,1.f,1.0f });
	}

	void Draw_Line(fvector2d from, fvector2d to, int thickness, flinearcolor color)
	{
		canvas->k2_drawline(fvector2d{ from.x, from.y }, fvector2d{ to.x, to.y }, thickness, color);
	}

	void drawFilledRect(fvector2d initial_pos, float w, float h, flinearcolor color)
	{
		for (float i = 0.0f; i < h; i += 1.0f)
			canvas->k2_drawline(fvector2d{ initial_pos.x, initial_pos.y + i }, fvector2d{ initial_pos.x + w, initial_pos.y + i }, 1.0f, color);
	}

	void DrawGradientLine(fvector2d screenpos_a, fvector2d screenpos_b, flinearcolor color_a, flinearcolor color_c, flinearcolor color_b, float thickness, int num_segments)
	{
		for (int i = 0; i < num_segments; i++)
		{
			float t1 = static_cast<float>(i) / num_segments;
			float t2 = static_cast<float>(i + 1) / num_segments;

			fvector2d start = screenpos_a + (screenpos_b - screenpos_a) * t1;
			fvector2d end = screenpos_a + (screenpos_b - screenpos_a) * t2;

			float t_mid = (t1 + t2) / 2.0f;

			flinearcolor color;

			if (t_mid <= 0.5f)
			{
				float u = 2.0f * t_mid;
				color.r = color_a.r * (1.0f - u) + color_c.r * u;
				color.g = color_a.g * (1.0f - u) + color_c.g * u;
				color.b = color_a.b * (1.0f - u) + color_c.b * u;
				color.a = color_a.a * (1.0f - u) + color_c.a * u;
			}
			else
			{
				float v = 2.0f * (t_mid - 0.5f);
				color.r = color_c.r * (1.0f - v) + color_b.r * v;
				color.g = color_c.g * (1.0f - v) + color_b.g * v;
				color.b = color_c.b * (1.0f - v) + color_b.b * v;
				color.a = color_c.a * (1.0f - v) + color_b.a * v;
			}

			canvas->k2_drawline(start, end, thickness, color);
		}
	}

	void drawGradientFilledRect(fvector2d initial_pos, float w, float h, flinearcolor color_a, flinearcolor color_c, flinearcolor color_b, int num_segments)
	{
		for (float i = 0.0f; i < h; i += 1.0f)
			DrawGradientLine(fvector2d{ initial_pos.x, initial_pos.y + i }, fvector2d{ initial_pos.x + w, initial_pos.y + i }, color_a, color_c, color_b, 1.0f, num_segments);
	}

	void drawGradientFilledRectVertical(fvector2d initial_pos, float w, float h, flinearcolor color_a, flinearcolor color_c, flinearcolor color_b, int num_segments)
	{
		for (float i = 0.0f; i < w; i += 1.0f)
			DrawGradientLine(fvector2d{ initial_pos.x + i, initial_pos.y }, fvector2d{ initial_pos.x + i, initial_pos.y + h }, color_a, color_c, color_b, 1.0f, num_segments);
	}

	void draw_filled_rect(ucanvas* canvas, float x, float y, float width, float height, flinearcolor color) {
		for (float i = 0; i < height; i++) {
			canvas->k2_drawline(
				{ x, y + i },
				{ x + width, y + i },
				1.0f,
				color
			);
		}
	}

	void draw_rect(ucanvas* canvas, float x, float y, float width, float height, flinearcolor color) {
		canvas->k2_drawline({ x, y }, { x + width, y }, 1.0f, color);
		canvas->k2_drawline({ x + width, y }, { x + width, y + height }, 1.0f, color);
		canvas->k2_drawline({ x + width, y + height }, { x, y + height }, 1.0f, color);
		canvas->k2_drawline({ x, y + height }, { x, y }, 1.0f, color);
	}

	void drawTriangle(fvector2d p1, fvector2d p2, fvector2d p3, flinearcolor color, int thickness = 1)
	{
		Draw_Line(p1, p2, thickness, color);
		Draw_Line(p2, p3, thickness, color);
		Draw_Line(p3, p1, thickness, color);
	}

	void drawCircle(fvector2d center, float radius, flinearcolor color, int thickness = 1, int segments = 64)
	{
		float angleStep = (2.0f * 3.14159265f) / segments;

		for (int i = 0; i < segments; ++i)
		{
			float angle1 = i * angleStep;
			float angle2 = (i + 1) * angleStep;

			fvector2d p1 = fvector2d(center.x + cosf(angle1) * radius, center.y + sinf(angle1) * radius);
			fvector2d p2 = fvector2d(center.x + cosf(angle2) * radius, center.y + sinf(angle2) * radius);

			Draw_Line(p1, p2, thickness, color);
		}
	}

	void DrawFilledCircle(fvector2d pos, float r, flinearcolor color)
	{
		float smooth = 0.07f;

		double PI = 3.14159265359;
		int size = (int)(2.0f * PI / smooth) + 1;

		float angle = 0.0f;
		int i = 0;

		for (; angle < 2 * PI; angle += smooth, i++)
		{
			Draw_Line(fvector2d{ pos.x, pos.y }, fvector2d{ pos.x + cosf(angle) * r, pos.y + sinf(angle) * r }, 1.0f, color);
		}
	}

	void DrawCircle(fvector2d pos, int radius, int numSides, flinearcolor Color)
	{
		float PI = 3.1415927f;

		float Step = PI * 2.0 / numSides;
		int Count = 0;
		fvector2d V[128];
		for (float a = 0; a < PI * 2.0; a += Step) {
			float X1 = radius * cos(a) + pos.x;
			float Y1 = radius * sin(a) + pos.y;
			float X2 = radius * cos(a + Step) + pos.x;
			float Y2 = radius * sin(a + Step) + pos.y;
			V[Count].x = X1;
			V[Count].y = Y1;
			V[Count + 1].x = X2;
			V[Count + 1].y = Y2;
			Draw_Line(fvector2d{ V[Count].x, V[Count].y }, fvector2d{ X2, Y2 }, 1.0f, Color);// Circle Around
		}
	}

	void cooltext(ucanvas* canvas, const wchar_t* text, fvector2d pos) {
		canvas->k2_drawtext(menu::font, text, fvector2d(pos.x, pos.y), fvector2d(0.99, 0.96),
			flinearcolor{ 1.0f, 1.0f, 1.0f, 1.0f }, 0.0f, RGBtoFLC(0, 0, 0),
			fvector2d(0, 0), false, true, false, RGBtoFLC(0, 0, 0));
	}

	void draw_textyyy(ucanvas* canvas, uobject* font, const wchar_t* text, flinearcolor color, fvector2d pos, bool centered = false) {
		if (!canvas || !font || !text) return;

		canvas->k2_drawtext(
			font,
			text,
			pos,
			{ 1.00f, 1.00f },
			color,
			0.f,
			{ 0, 0, 0, 0.30f },
			{ 0, 0 },
			true,
			true,
			true,
			{ 0, 0, 0, 0.45f }
		);
	}

	fvector2d CalcTextSize(const wchar_t* text) {
		HDC hdc = GetDC(nullptr);
		if (!hdc)
			return { 0, 0 };

		SIZE size;
		GetTextExtentPoint32W(hdc, text, (int)wcslen(text), &size);
		ReleaseDC(nullptr, hdc);

		return fvector2d{ static_cast<float>(size.cx), static_cast<float>(size.cy) };
	}

	void GetColor(flinearcolor* color, float* r, float* g, float* b, float* a)
	{
		*r = color->r;
		*g = color->g;
		*b = color->b;
		*a = color->a;
	}

	UINT32 GetColorUINT(int r, int g, int b, int a)
	{
		UINT32 result = (BYTE(a) << 24) + (BYTE(r) << 16) + (BYTE(g) << 8) + BYTE(b);
		return result;
	}

	// --- NAMESPACELER VE POST RENDERER ---

	namespace input
	{
		bool mouseDown[5];
		bool mouseDownAlready[256];

		bool keysDown[256];
		bool keysDownAlready[256];

		bool is_any_mouse_down()
		{
			if (mouseDown[0]) return true;
			if (mouseDown[1]) return true;
			if (mouseDown[2]) return true;
			if (mouseDown[3]) return true;
			if (mouseDown[4]) return true;

			return false;
		}

		bool is_mouse_clicked(int button, int element_id, bool repeat)
		{
			if (mouseDown[button])
			{
				if (!mouseDownAlready[element_id])
				{
					mouseDownAlready[element_id] = true;
					return true;
				}
				if (repeat)
					return true;
			}
			else
			{
				mouseDownAlready[element_id] = false;
			}
			return false;
		}
		bool is_key_pressed(int key, bool repeat)
		{
			if (keysDown[key])
			{
				if (!keysDownAlready[key])
				{
					keysDownAlready[key] = true;
					return true;
				}
				if (repeat)
					return true;
			}
			else
			{
				keysDownAlready[key] = false;
			}
			return false;
		}

		void handle()
		{
			if (GetAsyncKeyState(0x01))
				mouseDown[0] = true;
			else
				mouseDown[0] = false;
		}
	}

	namespace Accent
	{
		flinearcolor Title = RGBtoFLC(200, 200, 40);
		flinearcolor AccentBar1 = flinearcolor(220.0f / 255.0f, 20.0f / 255.0f, 60.0f / 255.0f);
		flinearcolor ToggleOn = RGBtoFLC(45, 160, 160); // Premium Mavi
		flinearcolor ToggleOff = RGBtoFLC(25, 25, 25);
	}

	namespace Colors
	{
		flinearcolor Text{ 192.0f / 255.0f, 192.0f / 255.0f, 192.0f / 255.0f, 255.0f / 255.0f };
		flinearcolor Text_Shadow{ 0.0f, 0.0f, 0.0f, 1.0f };
		flinearcolor Text_Outline{ 0.0f, 0.0f, 0.0f, 1.0f };
		flinearcolor Text_Active{ 45.0f / 255.0f, 160.0f / 255.0f, 160.0f / 255.0f, 0.8f };

		flinearcolor Button_Idle{ 0.0 / 255.0f, 0.0 / 255.0f, 0.0 / 255.0f, 0.8f / 255.0f };
		flinearcolor Button_Hovered{ 15.0f / 255.0f, 15.0f / 255.0f, 15.0f / 255.0f, 1.f };
		flinearcolor Button_Active{ 45.0f / 255.0f, 160.0f / 255.0f, 160.0f / 255.0f, 0.8f };

		flinearcolor Checkbox_Idle = RGBtoFLC(15, 15, 15);
		flinearcolor Checkbox_Hovered = RGBtoFLC(20, 20, 20);
		flinearcolor Checkbox_Enabled = RGBtoFLC(45, 160, 160);

		flinearcolor Combobox_Idle{ 200.0f / 255.0f, 150.0f / 255.0f, 40.0f / 255.0f };
		flinearcolor Combobox_Hovered{ 200.0f / 255.0f, 150.0f / 255.0f, 40.0f / 255.0f };
		flinearcolor Combobox_Elements{ 0.239f, 0.42f, 0.0f, 0.5f };

		flinearcolor Slider_Idle = RGBtoFLC(8, 8, 8);
		flinearcolor Slider_Hovered = RGBtoFLC(14, 14, 14);
		flinearcolor Slider_Progress = RGBtoFLC(45, 160, 160);
		flinearcolor Slider_Button = RGBtoFLC(45, 180, 180);

		flinearcolor ColorPicker_Background{ 0.006f, 0.006f, 0.006f, 0.4f };
	}

	namespace PostRenderer
	{
		struct DrawList
		{
			int type = -1; //1 = FilledRect, 2 = TextLeft, 3 = TextCenter, 4 = Draw_Line, 5 = Text, 6 = FilledRectEx
			fvector2d pos;
			fvector2d size;
			flinearcolor color;
			const wchar_t* name;
			bool outline;

			fvector2d from;
			fvector2d to;
			int thickness;

			fvector2d scale;
			flinearcolor outline_color;
			fvector2d shadow_offset;
			bool center;

			float width;
			float height;
		};
		DrawList drawlist[128];

		void drawFilledRect(fvector2d pos, float w, float h, flinearcolor color) // OLD
		{
			for (int i = 0; i < 128; i++)
			{
				if (drawlist[i].type == -1)
				{
					drawlist[i].type = 1;
					drawlist[i].pos = pos;
					drawlist[i].size = fvector2d{ w, h };
					drawlist[i].color = color;
					return;
				}
			}
		}

		void FilledRect(fvector2d pos, float w, float h, flinearcolor color) // NEW
		{
			for (int i = 0; i < 128; i++)
			{
				if (drawlist[i].type == -1)
				{
					drawlist[i].type = 6;
					drawlist[i].pos = pos;
					drawlist[i].width = w;
					drawlist[i].height = h;
					drawlist[i].color = color;
					return;
				}
			}
		}

		void TextLeft(const wchar_t* name, fvector2d pos, flinearcolor color, bool outline) // OLD
		{
			for (int i = 0; i < 128; i++)
			{
				if (drawlist[i].type == -1)
				{
					drawlist[i].type = 2;
					drawlist[i].name = name;
					drawlist[i].pos = pos;
					drawlist[i].outline = outline;
					drawlist[i].color = color;
					return;
				}
			}
		}

		void TextCenter(const wchar_t* name, fvector2d pos, flinearcolor color, bool outline) // OLD
		{
			for (int i = 0; i < 128; i++)
			{
				if (drawlist[i].type == -1)
				{
					drawlist[i].type = 3;
					drawlist[i].name = name;
					drawlist[i].pos = pos;
					drawlist[i].outline = outline;
					drawlist[i].color = color;
					return;
				}
			}
		}

		void Draw_Line(fvector2d from, fvector2d to, int thickness, flinearcolor color) // OLD
		{
			for (int i = 0; i < 128; i++)
			{
				if (drawlist[i].type == -1)
				{
					drawlist[i].type = 4;
					drawlist[i].from = from;
					drawlist[i].to = to;
					drawlist[i].thickness = thickness;
					drawlist[i].color = color;
					return;
				}
			}
		}

		void Text(const wchar_t* text, fvector2d pos, fvector2d scale, flinearcolor color, // NEW
			float angle, flinearcolor shadow_color, fvector2d shadow_offset,
			bool center, bool outline, flinearcolor outline_color)
		{
			for (int i = 0; i < 128; i++)
			{
				if (drawlist[i].type == -1)
				{
					drawlist[i].type = 5;
					drawlist[i].name = text;
					drawlist[i].pos = pos;
					drawlist[i].scale = scale;
					drawlist[i].color = color;
					drawlist[i].outline_color = outline_color;
					drawlist[i].shadow_offset = shadow_offset;
					drawlist[i].center = center;
					drawlist[i].outline = outline;
					return;
				}
			}
		}
	}

	// --- ARAYÜZ VE MENÜ DURUM DEĞİŞKENLERİ ---
	bool hover_element = false;
	fvector2d menu_pos = fvector2d{ 0, 0 };
	float offset_x = 0.0f;
	float offset_y = 0.0f;

	fvector2d first_element_pos = fvector2d{ 0, 0 };
	fvector2d last_element_pos = fvector2d{ 0, 0 };
	fvector2d last_element_size = fvector2d{ 0, 0 };

	int current_element = -1;
	fvector2d current_element_pos = fvector2d{ 0, 0 };
	fvector2d current_element_size = fvector2d{ 0, 0 };
	int elements_count = 0;

	bool sameLine = false;

	bool pushY = false;
	float pushYvalue = 0.0f;

	fvector2d CursorPos()
	{
		POINT cursorPos;
		GetCursorPos(&cursorPos);
		return fvector2d{ (float)cursorPos.x, (float)cursorPos.y };
	}

	bool MouseInZone(fvector2d pos, fvector2d size)
	{
		fvector2d cursor_pos = CursorPos();

		if (cursor_pos.x > pos.x && cursor_pos.y > pos.y)
			if (cursor_pos.x < pos.x + size.x && cursor_pos.y < pos.y + size.y)
				return true;

		return false;
	}

	void SameLine()
	{
		sameLine = true;
	}
	void PushNextElementY(float y, bool from_last_element = true)
	{
		pushY = true;
		if (from_last_element)
			pushYvalue = last_element_pos.y + last_element_size.y + y;
		else
			pushYvalue = y;
	}
	void NextColumn(float x)
	{
		offset_x = x;
		PushNextElementY(first_element_pos.y, false);
	}
	void ClearFirstPos()
	{
		first_element_pos = fvector2d{ 0, 0 };
	}

	fvector2d dragPos;

	float GetSmoothTime() {
		return static_cast<float>(GetTickCount64()) / 1000.0f;
	}

	flinearcolor ApplyHueShift(flinearcolor color, float shift)
	{
		float r = color.r;
		float g = color.g;
		float b = color.b;

		float max = max(r, max(g, b));
		float min = min(r, min(g, b));
		float delta = max - min;

		float h = 0.0f;
		float s = (max > 0.0001f) ? delta / max : 0.0f;
		float v = max;

		if (delta > 0.0001f) {
			if (max == r) {
				h = (g - b) / delta;
			}
			else if (max == g) {
				h = 2.0f + (b - r) / delta;
			}
			else {
				h = 4.0f + (r - g) / delta;
			}
			h *= 60.0f;
			if (h < 0.0f) h += 360.0f;
		}

		h += shift * 180.0f / 3.14159265f;
		while (h >= 360.0f) h -= 360.0f;
		while (h < 0.0f) h += 360.0f;

		float c = v * s;
		float x = c * (1.0f - fabsf(fmodf(h / 60.0f, 2.0f) - 1.0f));
		float m = v - c;

		flinearcolor result;
		if (h < 60.0f) {
			result = { c, x, 0.0f };
		}
		else if (h < 120.0f) {
			result = { x, c, 0.0f };
		}
		else if (h < 180.0f) {
			result = { 0.0f, c, x };
		}
		else if (h < 240.0f) {
			result = { 0.0f, x, c };
		}
		else if (h < 300.0f) {
			result = { x, 0.0f, c };
		}
		else {
			result = { c, 0.0f, x };
		}

		result.r += m;
		result.g += m;
		result.b += m;
		result.a = color.a;

		return result;
	}

	inline float smoothstep(float edge0, float edge1, float x)
	{
		float t = std::clamp((x - edge0) / (edge1 - edge0), 0.0f, 1.0f);
		return t * t * (3.0f - 2.0f * t);
	}

	int current_tab;

	// --- GUI KONTROLLERİ VE BİLEŞENLER ---

	bool Window(const wchar_t* name, fvector2d* pos, fvector2d size, bool isOpen)
	{
		elements_count = 0;

		if (!isOpen)
			return false;

		float screen_width = (float)GetSystemMetrics(SM_CXSCREEN);
		float screen_height = (float)GetSystemMetrics(SM_CYSCREEN);

		bool isHovered = MouseInZone(fvector2d{ pos->x, pos->y }, fvector2d{ size.x, 23.0f });

		if (current_element != -1 && !GetAsyncKeyState(0x1))
		{
			current_element = -1;
		}

		if (hover_element && GetAsyncKeyState(0x1))
		{
			// Dragging
		}
		else if ((isHovered || dragPos.x != 0) && !hover_element)
		{
			if (input::is_mouse_clicked(0, elements_count, true))
			{
				fvector2d cursorPos = CursorPos();

				cursorPos.x -= size.x;
				cursorPos.y -= size.y;

				if (dragPos.x == 0)
				{
					dragPos.x = (cursorPos.x - pos->x);
					dragPos.y = (cursorPos.y - pos->y);
				}

				float new_x = cursorPos.x - dragPos.x;
				float new_y = cursorPos.y - dragPos.y;

				if (new_x < 0) new_x = 0;
				if (new_y < 0) new_y = 0;
				if (new_x + size.x > screen_width) new_x = screen_width - size.x;
				if (new_y + size.y > screen_height) new_y = screen_height - size.y;

				pos->x = new_x;
				pos->y = new_y;
			}
			else
			{
				dragPos = fvector2d{ 0, 0 };
			}
		}
		else
		{
			hover_element = false;
		}

		offset_x = 6.0f; offset_y = 2.0f;
		menu_pos = fvector2d{ pos->x, pos->y };
		first_element_pos = fvector2d{ 0, 0 };
		current_element_pos = fvector2d{ 0, 0 };
		current_element_size = fvector2d{ 0, 0 };

		// Outermost: pure black shell
		drawFilledRect(fvector2d(pos->x, pos->y), size.x, size.y, RGBtoFLC(0.0f, 0.0f, 0.0f, 1.0f));
		// 1px inner: pure black border 
		drawFilledRect(fvector2d(pos->x + 1, pos->y + 1), size.x - 2, size.y - 2, RGBtoFLC(0.0f, 0.0f, 0.0f));

		// SOL ÜSTE YAZI 
		canvas->k2_drawtext(font, L"S I K K E V E R", fvector2d(pos->x + size.x / 2 - 80, pos->y + 5), fvector2d(0.95f, 0.95f), RGBtoFLC(45, 160, 160, 1.f), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), false, false, false, RGBtoFLC(0, 0, 0));

		// Top Tab Bars & Content Area
		drawFilledRect(fvector2d(pos->x + 2, pos->y + 2), size.x - 4, 23, RGBtoFLC(0.0f, 0.0f, 0.0f));
		drawFilledRect(fvector2d(pos->x + 2, pos->y + 27), size.x - 4, 23, RGBtoFLC(0.0f, 0.0f, 0.0f));
		drawFilledRect(fvector2d(pos->x + 2, pos->y + 51), size.x - 4, size.y - 53 - 23, RGBtoFLC(0.0f, 0.0f, 0.0f));
		drawFilledRect(fvector2d(pos->x + 2, pos->y + size.y - 23), size.x - 4, 21, RGBtoFLC(0.0f, 0.0f, 0.0f));

		return true;
	}

	bool ButtonTab2(const wchar_t* name, fvector2d size, bool active)
	{
		elements_count++;

		fvector2d padding = fvector2d{ 0, 0 };
		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };

		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x;
			pos.y = last_element_pos.y;
		}

		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}

		bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);

		if (!sameLine)
			offset_y += size.y + padding.y;

		fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };

		if (active)
		{
			canvas->k2_drawtext(font, name, textPos, fvector2d(0.95f, 0.85f), RGBtoFLC(255, 255, 255, 1.f), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), true, true, false, RGBtoFLC(0, 0, 0));
			drawFilledRect(fvector2d{ pos.x, pos.y + size.y - 2 }, size.x, 2, RGBtoFLC(45, 160, 160));
		}
		else if (isHovered)
		{
			drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, RGBtoFLC(10.0f, 10.0f, 10.0f));
			canvas->k2_drawtext(font, name, textPos, fvector2d(0.95f, 0.85f), RGBtoFLC(200, 200, 200), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), true, true, false, RGBtoFLC(0, 0, 0));
			drawFilledRect(fvector2d{ pos.x, pos.y + size.y - 1 }, size.x, 1, RGBtoFLC(50.0f, 50.0f, 50.0f));
		}
		else
		{
			canvas->k2_drawtext(font, name, textPos, fvector2d(0.95f, 0.85f), RGBtoFLC(120, 120, 120), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), true, true, false, RGBtoFLC(0, 0, 0));
		}

		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;

		if (isHovered && input::is_mouse_clicked(0, elements_count, false))
			return true;

		return false;
	}

	void SectionWrapper(const wchar_t* name, fvector2d size)
	{
		fvector2d padding = fvector2d{ 0, 0 };
		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };

		if (sameLine)
		{
			pos.x = menu_pos.x + padding.x + offset_x;
			pos.y = menu_pos.y + padding.y + offset_y;
		}

		drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, size.y, RGBtoFLC(0.0f, 0.0f, 0.0f));
		drawFilledRect(fvector2d{ pos.x, pos.y }, size.x, 1, RGBtoFLC(45, 160, 160));
		canvas->k2_drawtext(font, name, fvector2d(pos.x + 6, pos.y + 4), fvector2d(0.95f, 0.85f), RGBtoFLC(210, 210, 210, 1.2f), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), false, false, false, RGBtoFLC(0, 0, 0));

		offset_y += 25;
		sameLine = false;
	}

	void Checkbox(const wchar_t* name, bool* value, bool risky = false)
	{
		elements_count++;

		fvector2d padding = fvector2d{ 13, 11 };
		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };

		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}

		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}

		float box_size = 10.0f;
		bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, fvector2d{ box_size, box_size });

		fvector2d textPos = fvector2d{ pos.x + box_size + 8, pos.y - 3.0f };

		if (risky) {
			canvas->k2_drawtext(font, name, textPos, fvector2d(0.90f, 0.85f), RGBtoFLC(200, 60, 60, 1.2f), 0.0f,
				RGBtoFLC(0, 0, 0), fvector2d(0, 0), false, false, false, Colors::Text_Outline);
		}
		else {
			canvas->k2_drawtext(font, name, textPos, fvector2d(0.90f, 0.85f), RGBtoFLC(180, 180, 180, 1.2f), 0.0f,
				RGBtoFLC(0, 0, 0), fvector2d(0, 0), false, false, false, Colors::Text_Outline);
		}

		if (!sameLine)
			offset_y += box_size + padding.y;

		// Outer Border
		drawFilledRect(fvector2d{ pos.x, pos.y }, box_size, box_size, RGBtoFLC(0, 0, 0));

		// Inner Fill
		drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, box_size - 2, box_size - 2, RGBtoFLC(20, 20, 20));

		if (*value)
		{
			// Fill Premium Mavi if checked
			drawFilledRect(fvector2d{ pos.x + 2, pos.y + 2 }, box_size - 4, box_size - 4, RGBtoFLC(45, 160, 160));
		}
		else if (isHovered)
		{
			// Subtle hover effect inside the box
			drawFilledRect(fvector2d{ pos.x + 2, pos.y + 2 }, box_size - 4, box_size - 4, RGBtoFLC(35, 35, 35));
		}

		sameLine = false;
		last_element_pos = pos;
		last_element_size = fvector2d{ box_size, box_size };
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;

		if (isHovered && input::is_mouse_clicked(0, elements_count, false))
			*value = !*value;
	}

	bool Button(const wchar_t* name)
	{
		elements_count++;

		fvector2d padding = fvector2d{ 0, 14 };
		float section_start_x = offset_x;
		float section_width = 228.0f;
		float button_width = 176.0f;
		float button_height = 20.0f;
		float button_width_half = button_width / 2.0f;

		fvector2d pos = fvector2d{
			menu_pos.x + section_start_x + (section_width / 2.0f) - button_width_half,
			menu_pos.y + padding.y + offset_y
		};

		if (sameLine) {
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY) {
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}

		bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, fvector2d{ button_width, button_height });

		static DWORD64 clickTime = 0;
		static bool    isAnimating = false;

		float fadeAlpha = 0.0f;
		if (isAnimating) {
			DWORD64 elapsed = GetTickCount64() - clickTime;
			if (elapsed < 1000)
				fadeAlpha = 1.0f - (elapsed / 1000.0f);
			else
				isAnimating = false;
		}

		drawFilledRect(fvector2d{ pos.x, pos.y }, button_width, button_height, RGBtoFLC(0, 0, 0));

		flinearcolor innerColor;
		if (isHovered) {
			innerColor = RGBtoFLC(20, 20, 20);
			hover_element = true;
		}
		else {
			innerColor = RGBtoFLC(10, 10, 10);
		}

		if (isAnimating) {
			float r = 20.0f * (1.0f - fadeAlpha) + fadeAlpha * 45.0f;
			float g = 20.0f * (1.0f - fadeAlpha) + fadeAlpha * 160.0f;
			float b = 20.0f * (1.0f - fadeAlpha) + fadeAlpha * 160.0f;
			innerColor = RGBtoFLC((int)r, (int)g, (int)b);
		}

		drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, button_width - 2, button_height - 2, innerColor);

		if (!sameLine)
			offset_y += button_height + padding.y;

		flinearcolor textColor = RGBtoFLC(200, 200, 200);

		fvector2d textPos = fvector2d{ pos.x + button_width / 2, pos.y + button_height / 2 };
		canvas->k2_drawtext(font, name, textPos, fvector2d(0.95f, 0.80f),
			textColor, 0.0f, Colors::Text_Shadow,
			fvector2d(0, 0), true, true, false, Colors::Text_Outline);

		sameLine = false;
		last_element_pos = pos;
		last_element_size = fvector2d{ button_width, button_height };
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;

		bool clicked = false;
		if (isHovered && menu::input::is_mouse_clicked(0, elements_count, false)) {
			clicked = true;
			isAnimating = true;
			clickTime = GetTickCount64();
		}

		return clicked;
	}

	bool checkbox_enabled[256];
	void Combobox(fvector2d size, int* value, const wchar_t* arg, ...)
	{
		elements_count++;

		fvector2d padding = fvector2d{ 33, 11 };
		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };

		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}

		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 20.0f;
			offset_y = pos.y - menu_pos.y;
		}

		bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);

		float combo_width = size.x;
		float combo_height = size.y;
		float item_content_height = size.y - 2;

		if (!sameLine)
			offset_y += combo_height + padding.y;

		if (!checkbox_enabled[elements_count])
		{
			drawFilledRect(fvector2d{ pos.x, pos.y }, combo_width, combo_height, RGBtoFLC(120, 120, 120));
			drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, combo_width - 2, combo_height - 2, RGBtoFLC(0, 0, 0));

			va_list args;
			va_start(args, arg);
			const wchar_t* current_arg = arg;
			int current_num = 0;
			while (current_arg != NULL && current_num <= *value)
			{
				if (current_num == *value)
				{
					fvector2d selectedTextPos = fvector2d{ pos.x + 5, pos.y + combo_height / 2 };
					canvas->k2_drawtext(font, current_arg, selectedTextPos, fvector2d(0.95f, 0.80f),
						RGBtoFLC(200, 200, 200), 0.0f, RGBtoFLC(0, 0, 0),
						fvector2d(0, 0), false, true, false, Colors::Text_Outline);
					break;
				}
				current_num++;
				current_arg = va_arg(args, const wchar_t*);
			}
			va_end(args);

			float arrow_x = pos.x + combo_width - 15.0f;
			float arrow_y = pos.y + combo_height / 2.0f;

			drawFilledRect(fvector2d{ arrow_x, arrow_y - 1 }, 5.0f, 1.0f, RGBtoFLC(179, 179, 179));
			drawFilledRect(fvector2d{ arrow_x + 1, arrow_y }, 3.0f, 1.0f, RGBtoFLC(179, 179, 179));
			drawFilledRect(fvector2d{ arrow_x + 2, arrow_y + 1 }, 1.0f, 1.0f, RGBtoFLC(179, 179, 179));
		}
		else
		{
			hover_element = true;

			drawFilledRect(fvector2d{ pos.x, pos.y }, combo_width, combo_height, RGBtoFLC(120, 120, 120));
			drawFilledRect(fvector2d{ pos.x + 1, pos.y + 1 }, combo_width - 2, combo_height - 2, RGBtoFLC(0, 0, 0));

			va_list args2;
			va_start(args2, arg);
			const wchar_t* current_arg2 = arg;
			int current_num2 = 0;
			while (current_arg2 != NULL && current_num2 <= *value)
			{
				if (current_num2 == *value)
				{
					fvector2d selectedTextPos = fvector2d{ pos.x + 5, pos.y + combo_height / 2 };
					canvas->k2_drawtext(font, current_arg2, selectedTextPos, fvector2d(0.95f, 0.80f),
						RGBtoFLC(200, 200, 200), 0.0f, RGBtoFLC(0, 0, 0),
						fvector2d(0, 0), false, true, false, Colors::Text_Outline);
					break;
				}
				current_num2++;
				current_arg2 = va_arg(args2, const wchar_t*);
			}
			va_end(args2);

			float arrow_x = pos.x + combo_width - 15.0f;
			float arrow_y = pos.y + combo_height / 2.0f;
			drawFilledRect(fvector2d{ arrow_x, arrow_y + 1 }, 5.0f, 1.0f, RGBtoFLC(179, 179, 179));
			drawFilledRect(fvector2d{ arrow_x + 1, arrow_y }, 3.0f, 1.0f, RGBtoFLC(179, 179, 179));
			drawFilledRect(fvector2d{ arrow_x + 2, arrow_y - 1 }, 1.0f, 1.0f, RGBtoFLC(179, 179, 179));

			fvector2d item_pos = fvector2d{ pos.x, pos.y + combo_height };

			va_list count_args;
			va_start(count_args, arg);
			const wchar_t* count_arg = arg;
			int item_count = 0;
			while (count_arg != NULL)
			{
				item_count++;
				count_arg = va_arg(count_args, const wchar_t*);
			}
			va_end(count_args);

			va_list arguments;
			va_start(arguments, arg);
			int num = 0;

			for (const wchar_t* current_arg3 = arg; current_arg3 != NULL; current_arg3 = va_arg(arguments, const wchar_t*))
			{
				float item_top = item_pos.y;
				float item_height = item_content_height;

				if (num == 0)
				{
					item_top += 0;
					item_height = item_content_height;
				}

				bool isItemHovered = MouseInZone(fvector2d{ item_pos.x, item_top },
					fvector2d{ combo_width, item_height });

				if (isItemHovered && input::is_mouse_clicked(0, elements_count, false))
				{
					*value = num;
					checkbox_enabled[elements_count] = false;
				}

				PostRenderer::drawFilledRect(fvector2d{ item_pos.x, item_top }, 1, item_height, RGBtoFLC(120, 120, 120));
				PostRenderer::drawFilledRect(fvector2d{ item_pos.x + combo_width - 1, item_top }, 1, item_height, RGBtoFLC(120, 120, 120));

				if (num == 0)
					PostRenderer::drawFilledRect(fvector2d{ item_pos.x, item_top }, combo_width, 1, RGBtoFLC(120, 120, 120));
				if (num == item_count - 1)
					PostRenderer::drawFilledRect(fvector2d{ item_pos.x, item_top + item_height - 1 }, combo_width, 1, RGBtoFLC(120, 120, 120));

				float inner_top = item_top + (num == 0 ? 1 : 0);
				float inner_height = item_height - (num == 0 ? 1 : 0) - (num == item_count - 1 ? 1 : 0);

				if (num == *value)
				{
					PostRenderer::drawFilledRect(fvector2d{ item_pos.x + 1, inner_top }, combo_width - 2, inner_height, RGBtoFLC(0, 50, 60)); // Active Dropdown
				}
				else
				{
					PostRenderer::drawFilledRect(fvector2d{ item_pos.x + 1, inner_top }, combo_width - 2, inner_height, RGBtoFLC(0, 0, 0));
				}

				fvector2d itemTextPos = fvector2d{ item_pos.x + 5, inner_top + inner_height / 2 };
				PostRenderer::Text(current_arg3, itemTextPos, fvector2d(0.95, 0.85),
					RGBtoFLC(200, 200, 200), 0.0f, RGBtoFLC(0, 0, 0),
					fvector2d(0, 0), false, false, Colors::Text_Outline);

				item_pos.y += item_content_height;
				num++;
			}
			va_end(arguments);

			if (checkbox_enabled[elements_count])
			{
				current_element_pos = pos;
				current_element_size = fvector2d{ combo_width, item_pos.y - pos.y };
			}
		}

		sameLine = false;
		last_element_pos = pos;
		last_element_size = fvector2d{ combo_width, combo_height };

		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;

		if (isHovered && input::is_mouse_clicked(0, elements_count, false))
			checkbox_enabled[elements_count] = !checkbox_enabled[elements_count];

		if (!isHovered && checkbox_enabled[elements_count] &&
			input::is_mouse_clicked(0, elements_count, false))
			checkbox_enabled[elements_count] = false;
	}

	void SliderFloat(const wchar_t* name, float* value, float min, float max, const char* format = "%.2f")
	{
		elements_count++;

		float outer_width = 152.0f;
		float outer_height = 6.0f;
		float inner_width = 150.0f;
		float inner_height = 4.0f;

		fvector2d size = fvector2d{ outer_width, 38 };
		fvector2d slider_size = fvector2d{ outer_width, outer_height };
		fvector2d adjust_zone = fvector2d{ 0, 20 };
		fvector2d padding = fvector2d{ 33, 11 };

		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };

		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}

		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}

		float slider_y = pos.y + padding.y + 5.0f;
		float inner_x = pos.x + 1 + 2;
		float inner_y = slider_y + 1;

		bool isHovered = MouseInZone(fvector2d{ pos.x + 2, slider_y - adjust_zone.y },
			fvector2d{ outer_width, outer_height + adjust_zone.y * 1.5f });

		if (!sameLine)
			offset_y += size.y + padding.y;

		drawFilledRect(fvector2d{ pos.x + 2, slider_y },
			outer_width, outer_height, RGBtoFLC(100.0f, 100.0f, 100.0f));

		drawFilledRect(fvector2d{ inner_x, inner_y }, inner_width, inner_height, RGBtoFLC(0.0f, 0.0f, 0.0f));

		float fill_percentage = (*value - min) / (max - min);
		float filled_width = inner_width * fill_percentage;

		if (filled_width > 0)
		{
			drawFilledRect(fvector2d{ inner_x, inner_y }, filled_width, inner_height, RGBtoFLC(45.0f, 160.0f, 160.0f));
		}

		if (isHovered || current_element == elements_count)
		{
			if (input::is_mouse_clicked(0, elements_count, true))
			{
				current_element = elements_count;

				fvector2d cursorPos = CursorPos();
				float relative_x = cursorPos.x - inner_x;
				*value = (relative_x / inner_width) * (max - min) + min;

				if (*value < min) *value = min;
				if (*value > max) *value = max;
			}

			hover_element = true;
		}

		fvector2d nameTextPos = fvector2d{ pos.x, pos.y + 1.0f };
		canvas->k2_drawtext(font, name, nameTextPos, fvector2d(0.90f, 0.85f),
			RGBtoFLC(180, 180, 180, 1.2f), 0.0f,
			RGBtoFLC(0, 0, 0), fvector2d(0, 0),
			false, false, false, Colors::Text_Outline);

		char buffer[32];
		sprintf_s(buffer, format, *value);

		float value_text_x = pos.x + outer_width - 15.0f;
		fvector2d valueTextPos = fvector2d{ value_text_x, pos.y + 1.0f };

		canvas->k2_drawtext(font, s2wc(buffer), valueTextPos, fvector2d(0.85f, 0.80f),
			RGBtoFLC(180, 180, 180, 1.2f), 0.0f, Colors::Text_Shadow,
			fvector2d(0, 0), false, false, false, Colors::Text_Outline);

		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;

		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;
	}

	void SliderInt(const wchar_t* name, int* value, int min, int max, const char* format = "%d")
	{
		elements_count++;

		float outer_width = 152.0f;
		float outer_height = 6.0f;
		float inner_width = 150.0f;
		float inner_height = 4.0f;

		fvector2d size = fvector2d{ outer_width, 38 };
		fvector2d slider_size = fvector2d{ outer_width, outer_height };
		fvector2d adjust_zone = fvector2d{ 0, 20 };
		fvector2d padding = fvector2d{ 33, 11 };

		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };

		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}

		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}

		float slider_y = pos.y + padding.y + 5.0f;
		float inner_x = pos.x + 1 + 2;
		float inner_y = slider_y + 1;

		bool isHovered = MouseInZone(fvector2d{ pos.x + 2, slider_y - adjust_zone.y },
			fvector2d{ outer_width, outer_height + adjust_zone.y * 1.5f });

		if (!sameLine)
			offset_y += size.y + padding.y;

		drawFilledRect(fvector2d{ pos.x + 2, slider_y },
			outer_width, outer_height, RGBtoFLC(100.0f, 100.0f, 100.0f));

		drawFilledRect(fvector2d{ inner_x, inner_y }, inner_width, inner_height, RGBtoFLC(0.0f, 0.0f, 0.0f));

		float fill_percentage = (float)(*value - min) / (float)(max - min);
		float filled_width = inner_width * fill_percentage;

		if (filled_width > 0)
		{
			drawFilledRect(fvector2d{ inner_x, inner_y }, filled_width, inner_height, RGBtoFLC(45.0f, 160.0f, 160.0f));
		}

		if (isHovered || current_element == elements_count)
		{
			if (input::is_mouse_clicked(0, elements_count, true))
			{
				current_element = elements_count;

				fvector2d cursorPos = CursorPos();
				float relative_x = cursorPos.x - inner_x;
				float temp_value = (relative_x / inner_width) * (max - min) + min;

				*value = (int)roundf(temp_value);

				if (*value < min) *value = min;
				if (*value > max) *value = max;
			}

			hover_element = true;
		}

		fvector2d nameTextPos = fvector2d{ pos.x, pos.y + 1.0f };
		canvas->k2_drawtext(font, name, nameTextPos, fvector2d(0.90f, 0.85f),
			RGBtoFLC(180, 180, 180, 1.2f), 0.0f,
			RGBtoFLC(0, 0, 0), fvector2d(0, 0),
			false, false, false, Colors::Text_Outline);

		char buffer[32];
		sprintf_s(buffer, format, *value);

		float value_text_x = pos.x + outer_width - 15.0f;
		fvector2d valueTextPos = fvector2d{ value_text_x, pos.y + 1.0f };

		canvas->k2_drawtext(font, s2wc(buffer), valueTextPos, fvector2d(0.85f, 0.80f),
			RGBtoFLC(180, 180, 180, 1.2f), 0.0f, Colors::Text_Shadow,
			fvector2d(0, 0), false, false, false, Colors::Text_Outline);

		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;

		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;
	}

	static int active_textbox = -1;
	bool Textbox(fvector2d size, char* buffer, size_t buffer_size)
	{
		elements_count++;

		float outer_width = 171.0f;
		float outer_height = 20.0f;
		float inner_width = outer_width - 2.0f;
		float inner_height = outer_height - 2.0f;

		fvector2d padding = { 40, 14 };
		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };

		if (sameLine) {
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}

		if (pushY) {
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}

		bool isHovered = MouseInZone(pos, fvector2d{ outer_width, outer_height });

		if (!sameLine)
			offset_y += outer_height + padding.y;

		drawFilledRect(fvector2d{ pos.x, pos.y }, outer_width, outer_height, RGBtoFLC(0, 0, 0, 0.25f));

		float inner_x = pos.x + (outer_width - inner_width) / 2.0f;
		float inner_y = pos.y + (outer_height - inner_height) / 2.0f;

		if (active_textbox == elements_count) {
			drawFilledRect(fvector2d{ inner_x, inner_y }, inner_width, inner_height, RGBtoFLC(0, 50, 60)); // Active Cyan Tint
		}
		else {
			drawFilledRect(fvector2d{ inner_x, inner_y }, inner_width, inner_height, RGBtoFLC(0, 0, 0));
		}

		if (isHovered && active_textbox != elements_count) {
			drawFilledRect(fvector2d{ inner_x + 1, inner_y + 1 }, inner_width - 2, inner_height - 2, RGBtoFLC(20, 20, 20));
		}

		static bool already_pressed = false;
		bool edited = false;

		if (isHovered && input::is_mouse_clicked(0, elements_count, false)) {
			already_pressed = true;
			active_textbox = elements_count;
		}
		else if (!isHovered && input::is_mouse_clicked(0, elements_count, false)) {
			active_textbox = -1;
		}

		std::wstring buffer_wide(buffer, buffer + strlen(buffer));
		fvector2d textPos = fvector2d{ inner_x + 5.0f, inner_y + inner_height / 2.0f };
		canvas->k2_drawtext(font, buffer_wide.c_str(), textPos, fvector2d(0.90f, 0.85f),
			RGBtoFLC(255, 255, 255, 1.2f), 0.0f, Colors::Text_Shadow,
			fvector2d(0, 0), false, true, false, Colors::Text_Outline);

		if (active_textbox == elements_count) {
			if (static_cast<int>(GetTickCount() / 400) % 2)
				canvas->k2_drawtext(font, L"_",
					fvector2d{ textPos.x + buffer_wide.length() * 8.0f, textPos.y },
					fvector2d(0.90f, 0.85f), RGBtoFLC(45, 160, 160, 1.2f), 0,
					Colors::Text_Shadow, fvector2d(0, 0), false, true, false, Colors::Text_Outline);

			BYTE keyboard_state[256];
			GetKeyboardState(keyboard_state);

			bool ctrl_down = (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;

			for (int vkey = 0; vkey < 255; ++vkey) {
				SHORT state = GetAsyncKeyState(vkey);
				bool down = (state & 0x1);

				if (down) {
					if (ctrl_down && (vkey == 'V' || vkey == 'v')) {
						if (OpenClipboard(nullptr)) {
							HANDLE hData = GetClipboardData(CF_UNICODETEXT);
							if (hData) {
								LPCWSTR wstr = (LPCWSTR)GlobalLock(hData);
								if (wstr) {
									char temp[512] = {};
									WideCharToMultiByte(CP_ACP, 0, wstr, -1, temp, sizeof(temp) - 1, nullptr, nullptr);
									size_t space = buffer_size - strlen(buffer) - 1;
									strncat(buffer, temp, space);
									edited = true;
									GlobalUnlock(hData);
								}
							}
							CloseClipboard();
						}
						continue;
					}

					if (vkey == VK_BACK && strlen(buffer) > 0) {
						buffer[strlen(buffer) - 1] = '\0';
						edited = true;
					}
					else if (vkey == VK_RETURN) {
						active_textbox = -1;
					}
					else if (strlen(buffer) < buffer_size - 1) {
						WCHAR unicode_char[4] = {};
						int res = ToUnicode(vkey, MapVirtualKey(vkey, MAPVK_VK_TO_VSC), keyboard_state, unicode_char, 4, 0);
						if (res > 0 && iswprint(unicode_char[0])) {
							char ansi_char[4] = {};
							WideCharToMultiByte(CP_ACP, 0, unicode_char, res, ansi_char, sizeof(ansi_char), nullptr, nullptr);
							strncat(buffer, ansi_char, buffer_size - strlen(buffer) - 1);
							edited = true;
						}
					}
				}
			}
		}

		sameLine = false;
		last_element_pos = pos;
		last_element_size = fvector2d{ outer_width, outer_height };

		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;

		return edited;
	}

	void InputField(const wchar_t* label, std::string* value, size_t max_len)
	{
		elements_count++;

		float outer_width = 171.0f;
		float outer_height = 20.0f;
		float inner_width = outer_width - 2.0f;
		float inner_height = outer_height - 2.0f;

		fvector2d padding = { 33, 11 };
		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x,
								   menu_pos.y + padding.y + offset_y };

		if (sameLine) {
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y;
		}
		if (pushY) {
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}

		bool isHovered = MouseInZone(pos, fvector2d{ outer_width, outer_height });

		if (!sameLine)
			offset_y += outer_height + padding.y + 4.0f;

		// Label au dessus
		canvas->k2_drawtext(font, label,
			fvector2d{ pos.x, pos.y - 12.f },
			fvector2d(0.85f, 0.80f),
			RGBtoFLC(200, 200, 200, 1.f), 0.f,
			Colors::Text_Shadow, fvector2d(0, 0),
			false, false, false, Colors::Text_Outline);

		// Outer border
		drawFilledRect(fvector2d{ pos.x, pos.y }, outer_width, outer_height,
			(active_textbox == elements_count)
			? RGBtoFLC(45, 160, 160)   // active: premium mavi
			: RGBtoFLC(120, 120, 120));   // inactif: gri

		// Inner background
		float inner_x = pos.x + 1.f;
		float inner_y = pos.y + 1.f;
		drawFilledRect(fvector2d{ inner_x, inner_y }, inner_width, inner_height,
			(active_textbox == elements_count)
			? RGBtoFLC(0, 50, 60)
			: RGBtoFLC(0, 0, 0));

		// Clamp value
		if (value->size() > max_len - 1)
			value->resize(max_len - 1);

		// Render text
		std::wstring wval(value->begin(), value->end());
		canvas->k2_drawtext(font, wval.c_str(),
			fvector2d{ inner_x + 5.f, inner_y + inner_height / 2.f },
			fvector2d(0.90f, 0.85f),
			RGBtoFLC(255, 255, 255, 1.2f), 0.f,
			Colors::Text_Shadow, fvector2d(0, 0),
			false, true, false, Colors::Text_Outline);

		// Curseur clignotant
		if (active_textbox == elements_count) {
			if ((int)(GetTickCount() / 400) % 2) {
				float cursor_x = inner_x + 5.f + (float)wval.size() * 7.5f;
				canvas->k2_drawtext(font, L"|",
					fvector2d{ cursor_x, inner_y + inner_height / 2.f },
					fvector2d(0.85f, 0.80f),
					RGBtoFLC(45, 160, 160, 1.f), 0.f,
					Colors::Text_Shadow, fvector2d(0, 0),
					false, true, false, Colors::Text_Outline);
			}
		}

		if (isHovered && input::is_mouse_clicked(0, elements_count, false))
			active_textbox = elements_count;
		else if (!isHovered && input::is_mouse_clicked(0, elements_count, false))
			active_textbox = -1;

		if (active_textbox == elements_count) {
			hover_element = true;

			BYTE kb[256];
			GetKeyboardState(kb);
			bool ctrl = (GetAsyncKeyState(VK_CONTROL) & 0x8000) != 0;

			for (int vk = 0; vk < 255; vk++) {
				if (!(GetAsyncKeyState(vk) & 0x1)) continue;

				if (ctrl && (vk == 'V')) {
					if (OpenClipboard(nullptr)) {
						HANDLE h = GetClipboardData(CF_UNICODETEXT);
						if (h) {
							LPCWSTR ws = (LPCWSTR)GlobalLock(h);
							if (ws) {
								char tmp[512] = {};
								WideCharToMultiByte(CP_UTF8, 0, ws, -1, tmp, 511, nullptr, nullptr);
								size_t space = max_len - value->size() - 1;
								if (space > 0)
									value->append(tmp, min(space, strlen(tmp)));
								GlobalUnlock(h);
							}
						}
						CloseClipboard();
					}
					continue;
				}

				if (vk == VK_BACK) {
					if (!value->empty()) value->pop_back();
				}
				else if (vk == VK_RETURN) {
					active_textbox = -1;
				}
				else if (value->size() < max_len - 1) {
					WCHAR wc[4] = {};
					int r = ToUnicode(vk, MapVirtualKey(vk, MAPVK_VK_TO_VSC), kb, wc, 4, 0);
					if (r > 0 && iswprint(wc[0])) {
						char mb[4] = {};
						WideCharToMultiByte(CP_UTF8, 0, wc, r, mb, 3, nullptr, nullptr);
						value->append(mb);
					}
				}
			}
		}

		sameLine = false;
		last_element_pos = pos;
		last_element_size = fvector2d{ outer_width, outer_height };
		if (first_element_pos.x == 0.f) first_element_pos = pos;
	}

	std::string VirtualKeyCodeToString(UCHAR virtualKey)
	{
		if (virtualKey == 0 || virtualKey == -1)
		{
			return "";
		}

		switch (virtualKey)
		{
		case VK_LBUTTON: return "MB1";
		case VK_RBUTTON: return "MB2";
		case VK_MBUTTON: return "MB3";
		case VK_XBUTTON1: return "MB4";
		case VK_XBUTTON2: return "MB5";
		}

		switch (virtualKey)
		{
		case VK_INSERT: return "INS";
		case VK_DELETE: return "DEL";
		case VK_HOME: return "HOME";
		case VK_END: return "END";
		case VK_PRIOR: return "PGUP";
		case VK_NEXT: return "PGDN";
		case VK_LEFT: return "LEFT";
		case VK_RIGHT: return "RIGHT";
		case VK_UP: return "UP";
		case VK_DOWN: return "DOWN";
		case VK_SPACE: return "SPACE";
		case VK_RETURN: return "ENTER";
		case VK_ESCAPE: return "ESC";
		case VK_BACK: return "BACK";
		case VK_TAB: return "TAB";
		case VK_CAPITAL: return "CAPS";
		case VK_NUMLOCK: return "NUMLK";
		case VK_SCROLL: return "SCRLK";
		case VK_PAUSE: return "PAUSE";
		case VK_SNAPSHOT: return "PRTSC";
		case VK_LSHIFT: return "LSHIFT";
		case VK_RSHIFT: return "RSHIFT";
		case VK_LCONTROL: return "LCTRL";
		case VK_RCONTROL: return "RCTRL";
		case VK_LMENU: return "LALT";
		case VK_RMENU: return "RALT";
		case VK_LWIN: return "LWIN";
		case VK_RWIN: return "RWIN";
		case VK_APPS: return "MENU";
		case VK_ADD: return "+";
		case VK_SUBTRACT: return "-";
		case VK_MULTIPLY: return "*";
		case VK_DIVIDE: return "/";
		case VK_DECIMAL: return ".";
		case VK_OEM_PLUS: return "=";
		case VK_OEM_MINUS: return "-";
		case VK_OEM_COMMA: return ",";
		case VK_OEM_PERIOD: return ".";
		case VK_OEM_1: return ";";
		case VK_OEM_2: return "/";
		case VK_OEM_3: return "`";
		case VK_OEM_4: return "[";
		case VK_OEM_5: return "\\";
		case VK_OEM_6: return "]";
		case VK_OEM_7: return "'";
		}

		if (virtualKey >= VK_NUMPAD0 && virtualKey <= VK_NUMPAD9)
		{
			return "NUM" + std::to_string(virtualKey - VK_NUMPAD0);
		}

		if (virtualKey >= VK_F1 && virtualKey <= VK_F24)
		{
			return "F" + std::to_string(virtualKey - VK_F1 + 1);
		}

		if (virtualKey >= 'A' && virtualKey <= 'Z')
		{
			return std::string(1, (char)virtualKey);
		}

		if (virtualKey >= '0' && virtualKey <= '9')
		{
			return std::string(1, (char)virtualKey);
		}

		UINT scanCode = MapVirtualKey(virtualKey, MAPVK_VK_TO_VSC);
		CHAR szName[128];

		switch (virtualKey)
		{
		case VK_LEFT: case VK_UP: case VK_RIGHT: case VK_DOWN:
		case VK_RCONTROL: case VK_RMENU:
		case VK_LWIN: case VK_RWIN: case VK_APPS:
		case VK_PRIOR: case VK_NEXT:
		case VK_END: case VK_HOME:
		case VK_INSERT: case VK_DELETE:
		case VK_DIVIDE:
		case VK_NUMLOCK:
			scanCode |= KF_EXTENDED;
		}

		int result = GetKeyNameTextA(scanCode << 16, szName, 128);
		std::string keyName = szName;
		std::transform(keyName.begin(), keyName.end(), keyName.begin(), ::toupper);

		return keyName;
	}

	int active_hotkey = -1;
	bool already_pressed = false;

	void Hotkey(const char* name, fvector2d size, int* key)
	{
		elements_count++;
		fvector2d padding = fvector2d{ 158, -2 };
		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };

		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y + (last_element_size.y / 2) - size.y / 2;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}

		bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);

		if (!sameLine)
			offset_y += size.y + padding.y;

		// Input label
		fvector2d labelPos = fvector2d{ pos.x - 145, pos.y + size.y / 2 };
		canvas->k2_drawtext(font, s2wc(name), labelPos,
			fvector2d(0.90f, 0.85f),
			RGBtoFLC(180, 180, 180, 1.2f),
			0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0),
			false, true, false, Colors::Text_Outline);

		if (active_hotkey == elements_count)
		{
			fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
			std::string displayText = "[ ... ]";
			// Active Hotkey uses Premium Mavi color
			canvas->k2_drawtext(font, s2wc(displayText.c_str()), textPos, fvector2d(0.85f, 0.80f), RGBtoFLC(45, 160, 160, 1.2f), 0.0f, Colors::Text_Shadow, fvector2d(0, 0), true, true, false, RGBtoFLC(0, 0, 0));

			if (!menu::input::is_any_mouse_down())
				already_pressed = false;

			if (!already_pressed)
			{
				for (int code = 0; code < 255; code++)
				{
					if (GetAsyncKeyState(code))
					{
						*key = code;
						active_hotkey = -1;
					}
				}
			}
		}
		else
		{
			fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
			std::string displayText;
			if (*key == 0 || *key == -1)
				displayText = "[ - ]";
			else
				displayText = "[ " + VirtualKeyCodeToString(*key) + " ]";

			// Inactive Hotkey uses Gray color
			canvas->k2_drawtext(font, s2wc(displayText.c_str()), textPos, fvector2d(0.85f, 0.80f), RGBtoFLC(120, 120, 120, 1.2f), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), true, true, false, RGBtoFLC(0, 0, 0));

			if (isHovered)
			{
				if (input::is_mouse_clicked(0, elements_count, false))
				{
					already_pressed = true;
					active_hotkey = elements_count;
					for (int code = 0; code < 255; code++)
						if (GetAsyncKeyState(code)) {}
				}
			}
			else
			{
				if (input::is_mouse_clicked(0, elements_count, false))
					active_hotkey = -1;
			}
		}

		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;
	}

	int active_hotkey_labeled = -1;
	bool already_pressed_labeled = false;
	void HotkeyLabeled(const char* name, int* key)
	{
		elements_count++;
		fvector2d padding = fvector2d{ 158, -2 };
		fvector2d size = fvector2d{ 9, 18 };
		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };

		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y + (last_element_size.y / 2) - size.y / 2;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}

		bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);

		if (!sameLine)
			offset_y += size.y + padding.y;

		fvector2d labelPos = fvector2d{ pos.x - 10, pos.y + size.y / 2 };
		canvas->k2_drawtext(font, s2wc(name), labelPos,
			fvector2d(0.80f, 0.75f),
			RGBtoFLC(120, 120, 120, 1.2f),
			0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0),
			true, true, true, RGBtoFLC(0, 0, 0, 0.1f));

		if (active_hotkey_labeled == elements_count)
		{
			fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
			std::string displayText = "[ ... ]";
			canvas->k2_drawtext(font, s2wc(displayText.c_str()), textPos, fvector2d(0.80f, 0.75f), RGBtoFLC(45, 160, 160, 1.2f), 0.0f, Colors::Text_Shadow, fvector2d(0, 0), true, true, true, RGBtoFLC(0, 0, 0, 0.1f));

			if (!menu::input::is_any_mouse_down())
				already_pressed_labeled = false;

			if (!already_pressed_labeled)
			{
				for (int code = 0; code < 255; code++)
				{
					if (GetAsyncKeyState(code))
					{
						*key = code;
						active_hotkey_labeled = -1;
					}
				}
			}
		}
		else
		{
			fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
			std::string displayText;
			if (*key == 0 || *key == -1)
				displayText = "[ - ]";
			else
				displayText = "[ " + VirtualKeyCodeToString(*key) + " ]";

			canvas->k2_drawtext(font, s2wc(displayText.c_str()), textPos, fvector2d(0.80f, 0.75f), RGBtoFLC(120, 120, 120, 1.2f), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), true, true, true, RGBtoFLC(0, 0, 0, 0.1f));

			if (isHovered)
			{
				if (input::is_mouse_clicked(0, elements_count, false))
				{
					already_pressed_labeled = true;
					active_hotkey_labeled = elements_count;
					for (int code = 0; code < 255; code++)
						if (GetAsyncKeyState(code)) {}
				}
			}
			else
			{
				if (input::is_mouse_clicked(0, elements_count, false))
					active_hotkey_labeled = -1;
			}
		}

		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;
	}

	int active_hotkey2 = -1;
	bool already_pressed2 = false;
	void Hotkey2(const char* name, fvector2d size, int* key)
	{
		elements_count++;
		fvector2d padding = fvector2d{ 191, 4 };
		fvector2d pos = fvector2d{ menu_pos.x + padding.x + offset_x, menu_pos.y + padding.y + offset_y };
		if (sameLine)
		{
			pos.x = last_element_pos.x + last_element_size.x + padding.x;
			pos.y = last_element_pos.y + (last_element_size.y / 2) - size.y / 2;
		}
		if (pushY)
		{
			pos.y = pushYvalue;
			pushY = false;
			pushYvalue = 0.0f;
			offset_y = pos.y - menu_pos.y;
		}
		bool isHovered = MouseInZone(fvector2d{ pos.x, pos.y }, size);

		if (!sameLine)
			offset_y += size.y + padding.y;

		if (active_hotkey2 == elements_count)
		{
			fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
			std::string displayText = "[ ... ]";

			canvas->k2_drawtext(font, s2wc(displayText.c_str()), textPos, fvector2d(0.80f, 0.75f), RGBtoFLC(45, 160, 160, 1.2f), 0.0f, Colors::Text_Shadow, fvector2d(0, 0), true, true, true, RGBtoFLC(0, 0, 0, 0.1f));

			if (!menu::input::is_any_mouse_down())
			{
				already_pressed2 = false;
			}

			if (!already_pressed2)
			{
				for (int code = 0; code < 255; code++)
				{
					if (GetAsyncKeyState(code))
					{
						*key = code;
						active_hotkey2 = -1;
					}
				}
			}
		}
		else
		{
			fvector2d textPos = fvector2d{ pos.x + size.x / 2, pos.y + size.y / 2 };
			std::string displayText;
			if (*key == 0 || *key == -1)
			{
				displayText = "[ - ]";
			}
			else
			{
				displayText = "[ " + VirtualKeyCodeToString(*key) + " ]";
			}

			canvas->k2_drawtext(font, s2wc(displayText.c_str()), textPos, fvector2d(0.80f, 0.75f), RGBtoFLC(120, 120, 120, 1.2f), 0.0f, RGBtoFLC(0, 0, 0), fvector2d(0, 0), true, true, true, RGBtoFLC(0, 0, 0, 0.1f));

			if (isHovered)
			{
				if (input::is_mouse_clicked(0, elements_count, false))
				{
					already_pressed2 = true;
					active_hotkey2 = elements_count;

					for (int code = 0; code < 255; code++)
						if (GetAsyncKeyState(code)) {}
				}
			}
			else
			{
				if (input::is_mouse_clicked(0, elements_count, false))
				{
					active_hotkey2 = -1;
				}
			}
		}

		sameLine = false;
		last_element_pos = pos;
		last_element_size = size;
		if (first_element_pos.x == 0.0f)
			first_element_pos = pos;
	}

	void Render()
	{
		for (int i = 0; i < 128; i++)
		{
			if (PostRenderer::drawlist[i].type != -1)
			{
				if (PostRenderer::drawlist[i].type == 1)
				{
					menu::drawFilledRect(PostRenderer::drawlist[i].pos,
						PostRenderer::drawlist[i].size.x,
						PostRenderer::drawlist[i].size.y,
						PostRenderer::drawlist[i].color);
				}
				else if (PostRenderer::drawlist[i].type == 2)
				{
					canvas->k2_drawtext(font, PostRenderer::drawlist[i].name,
						PostRenderer::drawlist[i].pos,
						fvector2d(0.98, 0.98),
						PostRenderer::drawlist[i].color,
						0.0f, Colors::Text_Shadow,
						fvector2d(0, 0), false, false,
						PostRenderer::drawlist[i].outline, Colors::Text_Outline);
				}
				else if (PostRenderer::drawlist[i].type == 3)
				{
					menu::TextCenter(PostRenderer::drawlist[i].name,
						PostRenderer::drawlist[i].pos,
						PostRenderer::drawlist[i].color,
						PostRenderer::drawlist[i].outline);
				}
				else if (PostRenderer::drawlist[i].type == 4)
				{
					Draw_Line(PostRenderer::drawlist[i].from,
						PostRenderer::drawlist[i].to,
						PostRenderer::drawlist[i].thickness,
						PostRenderer::drawlist[i].color);
				}
				else if (PostRenderer::drawlist[i].type == 5)
				{
					canvas->k2_drawtext(font,
						PostRenderer::drawlist[i].name,
						PostRenderer::drawlist[i].pos,
						PostRenderer::drawlist[i].scale,
						PostRenderer::drawlist[i].color,
						0.0f,
						PostRenderer::drawlist[i].outline_color,
						PostRenderer::drawlist[i].shadow_offset,
						PostRenderer::drawlist[i].center,
						true,
						PostRenderer::drawlist[i].outline,
						Colors::Text_Outline);
				}
				else if (PostRenderer::drawlist[i].type == 6)
				{
					menu::drawFilledRect(PostRenderer::drawlist[i].pos,
						PostRenderer::drawlist[i].width,
						PostRenderer::drawlist[i].height,
						PostRenderer::drawlist[i].color);
				}

				PostRenderer::drawlist[i].type = -1;
			}
		}
	}

	// --- RENK GEÇİŞLİ WATERMARK FONKSİYONU ---
	flinearcolor GetAnimatedWatermarkColor(float alpha)
	{
		float t = static_cast<float>(GetTickCount64()) / 1200.0f; // 1.2 saniyede bir renk değiştirir

		struct ColorRGB { float r, g, b; };
		ColorRGB colors[] = {
			{ 255.0f, 255.0f, 0.0f },     // Sarı
			{ 45.0f, 160.0f, 160.0f },    // Premium Mavi
			{ 150.0f, 0.0f, 255.0f },     // Mor
			{ 255.0f, 150.0f, 200.0f },   // Hafif Pembe
			{ 100.0f, 255.0f, 100.0f },   // Hafif Yeşil
			{ 255.0f, 255.0f, 100.0f }    // Parlak Sarı
		};
		int numColors = 6;

		int currentIndex = (int)t % numColors;
		int nextIndex = (currentIndex + 1) % numColors;
		float lerpFactor = t - (float)((int)t);

		float r = colors[currentIndex].r + (colors[nextIndex].r - colors[currentIndex].r) * lerpFactor;
		float g = colors[currentIndex].g + (colors[nextIndex].g - colors[currentIndex].g) * lerpFactor;
		float b = colors[currentIndex].b + (colors[nextIndex].b - colors[currentIndex].b) * lerpFactor;

		return menu::RGBtoFLC(r, g, b, alpha);
	}

	void DrawWatermark()
	{
		float screen_width = (float)GetSystemMetrics(SM_CXSCREEN);
		float wm_x = screen_width - 220.0f; // Ekrana tam sığması için biraz daha sola çekildi
		float wm_y = 20.0f;

		const wchar_t* wmtext = L"Powered by S I K K E V E R";

		flinearcolor blurColor = GetAnimatedWatermarkColor(0.20f);
		flinearcolor mainColor = GetAnimatedWatermarkColor(0.85f);

		canvas->k2_drawtext(font, wmtext, fvector2d(wm_x - 2, wm_y), fvector2d(1.0f, 1.0f), blurColor, 0.0f, flinearcolor{ 0,0,0,0 }, fvector2d(0, 0), false, false, false, flinearcolor{ 0,0,0,0 });
		canvas->k2_drawtext(font, wmtext, fvector2d(wm_x + 2, wm_y), fvector2d(1.0f, 1.0f), blurColor, 0.0f, flinearcolor{ 0,0,0,0 }, fvector2d(0, 0), false, false, false, flinearcolor{ 0,0,0,0 });
		canvas->k2_drawtext(font, wmtext, fvector2d(wm_x, wm_y - 2), fvector2d(1.0f, 1.0f), blurColor, 0.0f, flinearcolor{ 0,0,0,0 }, fvector2d(0, 0), false, false, false, flinearcolor{ 0,0,0,0 });
		canvas->k2_drawtext(font, wmtext, fvector2d(wm_x, wm_y + 2), fvector2d(1.0f, 1.0f), blurColor, 0.0f, flinearcolor{ 0,0,0,0 }, fvector2d(0, 0), false, false, false, flinearcolor{ 0,0,0,0 });

		canvas->k2_drawtext(font, wmtext, fvector2d(wm_x, wm_y), fvector2d(1.0f, 1.0f), mainColor, 0.0f, flinearcolor{ 0,0,0,0.8f }, fvector2d(1, 1), false, false, false, flinearcolor{ 0,0,0,0 });
	}
}