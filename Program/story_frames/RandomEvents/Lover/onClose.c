void Lover_Cabin2(ref storyObject)
{
	ResetSound();
	SetLaunchFrameFormParam("", "", 0, 15);
	SetLaunchFrameFormParam("", "Run_Function", 0, 15);
	SetLaunchFrameRunFunctionParam("SetSchemeForMap", 0.0);
	SetLaunchFrameFormPic("loading\inside\censored1.tga");
	if(bSFW) PlayStereoSound("sex\sex_sfw.wav");
	else PlayStereoSound("sex\sex" + (rand(14) + 1) + ".wav");
	LaunchFrameForm();
	WaitDate("", 0, 0, 0, 3, 10);
	RecalculateJumpTable();
	LoveSex_Bonus();

	ref chr = characterFromId(pchar.quest.sex_partner);
	chr.quest.daily_sex = true;
	DeleteAttribute(chr, "quest.iwantsex");
	if (chr.id == "Mary") SetFunctionTimerCondition("Mary_SexReady", 0, 0, 1, false);
	else SetFunctionTimerCondition("Helena_SexReady", 0, 0, 1, false);
}