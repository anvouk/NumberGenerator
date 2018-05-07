#include "NumberGenerator.hpp"

MainWnd::MainWnd()
	: m_settingsFilename("Settings.xml")
{
	LoadSettings();

	CtrlLayout(*this, t_("Random Number Generator"));
	SetAppName(t_("Random Number Generator"));
	Sizeable();
	MaximizeBox();
	MinimizeBox();

	WhenClose << THISBACK(Quit);
	generateButton <<= THISBACK(Generate);

	MainMenu();
}

void MainWnd::MainMenu()
{
	AddFrame(m_menu);
	m_menu.Set([=](Bar& bar) {
		bar.Sub(t_("Info"), [=](Bar& bar) {
			bar.Add(t_("About"), THISBACK(About));
			bar.Sub(t_("Language"), [=](Bar& bar) {
				bar.Add("English", THISBACK2(ChangeLang, LNG_ENGLISH, true))
					.Check(m_lang == LNG_ENGLISH);
				bar.Add("Italiano", THISBACK2(ChangeLang, LNG_('I', 'T', 'I', 'T'), true))
					.Check(m_lang == LNG_('I', 'T', 'I', 'T'));
			});
			bar.Separator();
			bar.Add(t_("Quit"), THISBACK(Quit)).Key(K_CTRL_Q);
		});
	});
}

void MainWnd::Quit()
{
	SaveSettings();
	Break();
}

void MainWnd::About()
{
	PromptOK(Format("%s - %s", t_("Random Number Generator"), "Andrea Vouk - 2018"));
}

void MainWnd::SaveSettings()
{
	String xml;
	xml << XmlTag("Language").Text(LNGAsText(m_lang));
	if (!SaveFile(m_settingsFilename, XmlDoc("Settings", xml)))
		Exclamation(t_("Error saving the settings!"));
}

void MainWnd::LoadSettings()
{
	String d;
	if (!(d = LoadFile(m_settingsFilename)).IsEmpty()) {
		try {
			String d = LoadFile(m_settingsFilename);
			XmlParser p(d);
			while (!p.IsTag())
				p.Skip();
			p.PassTag("Settings");
			while (!p.IsEof()) {
				if (p.Tag("Language")) {
					ChangeLang(LNGFromText(p.ReadText()), false);
				} else {
					p.Skip();
				}
			}
		} catch (XmlError& err) {
			Exclamation(t_("Failed loading settings") + String(": ") + err.ToString());
		}
	} else {
		ChangeLang(LNG_ENGLISH, false);
	}
}

void MainWnd::ChangeLang(int lang, bool prompt)
{
	if (m_lang != lang) {
		m_lang = lang;
		SetLanguage(lang);
		if (prompt) {
			PromptOK(t_("Restart to complete the operation"));
		}
	}
}

void MainWnd::Generate()
{
	textOutput.Clear();
	m_gen.clear();
	if (textInput.GetText().IsEmpty()) {
		Exclamation(t_("Empty value!"));
		return;
	}

	if (!m_gen.load(textInput.GetText().ToString())) {
		Exclamation(Format("%s: %s",
						   t_("Invalid Input"), m_gen.error()));
	}
	Vector<int> nums;
	for (const auto& i : m_gen.nums()) {
		nums.Add(i);
	}
	String res = nums.ToString();
	res.Remove(0);
	res.Remove(res.GetCount() - 1);
	textOutput = res;
}
