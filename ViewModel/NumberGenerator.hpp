/*
 * The MIT License
 *
 * Copyright 2018 Andrea Vouk.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
 * THE SOFTWARE.
 */

#ifndef NumberGenerator_hpp
#define NumberGenerator_hpp

#include <CtrlLib/CtrlLib.h>

using namespace Upp;

#include <Core/t_.h>
#define TFILE <NumberGenerator/T/lang.t>
#include <Core/t.h>

#define LAYOUTFILE <NumberGenerator/View/NumberGenerator.lay>
#include <CtrlCore/lay.h>

#include <NumberGenerator/Model/iv_generator.hpp>

class MainWnd : public WithMainWndLayout<TopWindow>
{
public:
	typedef MainWnd CLASSNAME;
	MainWnd();

	void MainMenu();
	void Quit();
	void About();

	void SaveSettings();
	void LoadSettings();

	void ChangeLang(int lang, bool prompt = true);

	void Generate();

private:
	MenuBar m_menu;
	int m_lang;
	String m_settingsFilename;

	Ivg::Generator m_gen;
};

#endif
