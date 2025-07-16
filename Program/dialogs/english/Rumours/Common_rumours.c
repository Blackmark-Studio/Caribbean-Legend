// Слухи - диалог по типажам

#define MAX_RUMOURS_ABOUT_OWNERS 7

void ProcessCommonDialogRumors(ref NPChar, aref Link, aref NextDiag);
{
    string strum;
    string srum;
	bool bOk1, bOk2;
	switch(Dialog.CurrentNode)
	{
/////////////////////////////////////////////////---слухи мещанок---////////////////////////////////////////////
		case "rumours_towngirl":	
		NextDiag.CurrentNode = "rumours";
		
		//--> Тёмные воды исцеления
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "Have you heard? They say Thomas Morrison's daughter has been bedridden for six months now. Doctors are completely powerless against her ailment. The only one who can help her is the gypsy woman known for her potions that heal even the gravely ill. But she has flatly refused to do anything for the poor girl.";
			link.l1 = "Thank you, I must take my leave.";
			link.l1.go = "exit";
			
			SetQuestHeader("DWH");
			AddQuestRecord("DWH", "1");
			pchar.questTemp.DWH_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("DWH_gypsy", "gipsy_2", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto1");
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "dwh_gypsy_0";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetLoginTime(sld, 07.00, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Тёмные воды исцеления
		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "Two days past, there was a brazen attempt on the Port Chief's life! The would-be assassin lay in wait by his office door, but the Chief managed to cry for help. A musketeer arrived with haste and wounded the villain, though the knave managed to flee the city gates\nWord has it the Port Chief is offering a handsome bounty for the rogue's head! Thus far, no souls brave enough have come forward.";
			link.l1 = "Thank you, I must take my leave.";
			link.l1.go = "exit";
			
			SetQuestHeader("GS");
			AddQuestRecord("GS", "1");
			pchar.questTemp.GS_Start = true;
			pchar.questTemp.GS_Portman = true;
			AddLandQuestMark(characterFromId("Beliz_portman"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Грани справедливости
		//--> Торговля по закону
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		if (bOk1 || bOk2)
        {
			dialog.text = "Heard the news?! It's a bloody outrage! Not a drop of rum or wine left in the tavern - how's a body to find relief in this blasted heat? The innkeeper's been feeding us empty promises for a week that the drink will flow again, but there's been nothing! Are we expected to parch our throats until Judgment Day?";
			link.l1 = "Thank you, I must take my leave.";
			link.l1.go = "exit";
			
			SetQuestHeader("TPZ");
			AddQuestRecord("TPZ", "1");
			pchar.questTemp.TPZ_Start = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Торговля по закону
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
		{
			dialog.text = "Word around the harbor is that Julie d'Armagnac, the governor's niece, has become a mere shadow of her former self. Once radiant and full of life, now she drifts through the streets with unmistakable sorrow etched upon her face. The townsfolk whisper and wonder what might have befallen her, but none know the truth of it. Perhaps some scoundrel has broken her heart?"+GetSexPhrase(" Maybe it was you, captain?","")+"";
			link.l1 = ""+GetSexPhrase("I doubt it ","")+". Thank you, I must take my leave.";
			link.l1.go = "exit";
			
			SetQuestHeader("UV");
			AddQuestRecord("UV", "1");
			pchar.questTemp.UV_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("UV_Juli", "women_4", "woman", "woman", sti(pchar.rank), FRANCE, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_6");
			sld.lastname = StringFromKey("Neutral_7");
			sld.City = "PortPax";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto9");
			sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
			sld.dialog.currentnode = "Juli";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Украденное воспоминание
		//--> В плену великого улова andre39966
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "Word has it that fisherman Pierre Carno has vanished without a trace. Two dawns ago, he sailed into the blue and not a sign of him since. His wife, Lea, is beside herself with grief. By daylight and lamplight, she keeps her vigil at the pier, her eyous fixed on the endless waters, praying for a glimpse of her beloved's sail.";
			link.l1 = "Thank you, I must take my leave.";
			link.l1.go = "exit";
			
			SetQuestHeader("VPVL");
			AddQuestRecord("VPVL", "1");
			pchar.questTemp.VPVL_Start = true;
			AddDialogExitQuest("VPVL_Gegerate_Lea");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- В плену великого улова 
		//--> Тайна Бетси Прайс
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		if (bOk1 || bOk2)
        {
			dialog.text = "Captain, have you heard? There's a new waitress working at our tavern. They say she's quite the beauty. Men from all around have been rushing in just to catch a glimpse of her. But three days ago, she didn't show up for work, which greatly upset the tavern keeper who had been making enormous profits since her arrival. They say he's even willing to pay whoever can find the girl.​";
			link.l1 = "Thank you, I must take my leave.";
			link.l1.go = "exit";
			
			SetQuestHeader("TBP");
			AddQuestRecord("TBP", "1");
			pchar.questTemp.TBP_Start = true;
			pchar.questTemp.TBP_Tavern = true;
			AddLandQuestMark(CharacterFromID("Villemstad_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Тайна Бетси Прайс
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2 )
        srum = SelectRumourEx("towngirl", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        string posrep1, posrep2, answ1, answ2, answ3, answ4;
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Interesting! There is one more question I want to ask...","One more question.");
            answ3 = RandPhraseSimple("Well, anything can happen. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. Maybe " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be a pleasure for me, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("Alas, nothing more to tell you, let me pass.","I had enough of your questions, excuse me, I've got a lot of other matters to do."),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
                                            answ2,
                                            answ3,
                                            answ4,
                                            npchar, Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple("Thanks, I should go.","Farewell.");
		link.l2.go = "exit";
	break;

/////////////////////////////////////////////////---слухи мещан---////////////////////////////////////////////
	case "rumours_townman":	
		NextDiag.CurrentNode = "rumours";
		
		//--> Тёмные воды исцеления
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "Have you heard? They say Thomas Morrison's daughter has been bedridden for six months now. Doctors are completely powerless against her ailment. The only one who can help her is the gypsy woman known for her potions that heal even the gravely ill. But she has flatly refused to do anything for the poor girl.";
			link.l1 = "Thank you, I must take my leave.";
			link.l1.go = "exit";
			
			SetQuestHeader("DWH");
			AddQuestRecord("DWH", "1");
			pchar.questTemp.DWH_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("DWH_gypsy", "gipsy_2", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto1");
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "dwh_gypsy_0";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetLoginTime(sld, 07.00, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Тёмные воды исцеления
		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "Two days past, there was a brazen attempt on the Port Chief's life! The would-be assassin lay in wait by his office door, but the Chief managed to cry for help. A musketeer arrived with haste and wounded the villain, though the knave managed to flee the city gates\nWord has it the Port Chief is offering a handsome bounty for the rogue's head! Thus far, no souls brave enough have come forward. Mind you, even for a thousand doubloons - I'd not risk my neck...";
			link.l1 = "Thank you, I must take my leave.";
			link.l1.go = "exit";
			
			SetQuestHeader("GS");
			AddQuestRecord("GS", "1");
			pchar.questTemp.GS_Start = true;
			pchar.questTemp.GS_Portman = true;
			AddLandQuestMark(characterFromId("Beliz_portman"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Грани справедливости
		
		//--> Торговля по закону
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		if (bOk1 || bOk2)
        {
			dialog.text = "Heard the news?! It's a bloody outrage! Not a drop of rum or wine left in the tavern - how's a body to find relief in this blasted heat? The innkeeper's been feeding us empty promises for a week that the drink will flow again, but there's been nothing! Are we expected to parch our throats until Judgment Day?";
			link.l1 = "Thank you, I must take my leave.";
			link.l1.go = "exit";
			
			SetQuestHeader("TPZ");
			AddQuestRecord("TPZ", "1");
			pchar.questTemp.TPZ_Start = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Торговля по закону
		
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "Word around the harbor is that Julie d'Armagnac, the governor's niece, has become a mere shadow of her former self. Once radiant and full of life, now she drifts through the streets with unmistakable sorrow etched upon her face. The townsfolk whisper and wonder what might have befallen her, but none know the truth of it. Perhaps some scoundrel has broken her heart?"+GetSexPhrase(" Maybe it was you, captain?","")+"";
			link.l1 = ""+GetSexPhrase("I doubt it ","")+". Thank you, I must take my leave.";
			link.l1.go = "exit";
			
			SetQuestHeader("UV");
			AddQuestRecord("UV", "1");
			pchar.questTemp.UV_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("UV_Juli", "women_4", "woman", "woman", sti(pchar.rank), FRANCE, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_6");
			sld.lastname = StringFromKey("Neutral_7");
			sld.City = "PortPax";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto9");
			sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
			sld.dialog.currentnode = "Juli";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Украденное воспоминание
		
		//--> В плену великого улова andre39966
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "Word has it that fisherman Pierre Carno has vanished without a trace. Two dawns ago, he sailed into the blue and not a sign of him since. His wife, Lea, is beside herself with grief. By daylight and lamplight, she keeps her vigil at the pier, her eyous fixed on the endless waters, praying for a glimpse of her beloved's sail.";
			link.l1 = "Thank you, I must take my leave.";
			link.l1.go = "exit";
			
			SetQuestHeader("VPVL");
			AddQuestRecord("VPVL", "1");
			pchar.questTemp.VPVL_Start = true;
			AddDialogExitQuest("VPVL_Gegerate_Lea");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- В плену великого улова 
		//--> Тайна Бетси Прайс
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		if (bOk1 || bOk2)
        {
			dialog.text = "Captain, have you heard? There's a new waitress working at our tavern. They say she's quite the beauty. Men from all around have been rushing in just to catch a glimpse of her. But three days ago, she didn't show up for work, which greatly upset the tavern keeper who had been making enormous profits since her arrival. They say he's even willing to pay whoever can find the girl.​";
			link.l1 = "Thank you, I must take my leave.";
			link.l1.go = "exit";
			
			SetQuestHeader("TBP");
			AddQuestRecord("TBP", "1");
			pchar.questTemp.TBP_Start = true;
			pchar.questTemp.TBP_Tavern = true;
			AddLandQuestMark(CharacterFromID("Villemstad_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Тайна Бетси Прайс
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2 )
        srum = SelectRumourEx("townman", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Interesting! There is one more question I want to ask...","One more question.");
            answ3 = RandPhraseSimple("Well, everything can happen in our world. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. Maybe " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be a pleasure for me, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("Alas, nothing more to tell you, let me pass.","I had enough of your questions, excuse me, I've got a lot of other matters to do."),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
                                            answ2,
                                            answ3,
                                            answ4,
                                            npchar, Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple("Thanks, I should go.","Farewell.");
		link.l2.go = "exit";
	break;
	
	///////////////////////////////////---слухи тёмных личностей---////////////////////////////////////////////
	case "rumours_marginal":	
		NextDiag.CurrentNode = "rumours";

		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2 )
        srum = SelectRumourEx("townman", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("Well, everything can happen in our world. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. Maybe " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be a pleasure for me, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("Alas, nothing more to tell you, let me pass.","I had enough of your questions, excuse me, I've got a lot of other matters to do."),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Thanks, I should go.","Farewell.");
		link.l2.go = "exit";
	break;
	
/////////////////////////////////////////////////---слухи дворян---////////////////////////////////////////////
	case "rumours_nobleman":	
        srum = SelectRumourEx("nobleman", NPChar);
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
			if (bOk1 || bOk2){
				
			dialog.text = "Word around the harbor is that Julie d'Armagnac, the governor's niece, has become a mere shadow of her former self. Once radiant and full of life, now she drifts through the streets with unmistakable sorrow etched upon her face. The townsfolk whisper and wonder what might have befallen her, but none know the truth of it. Perhaps some scoundrel has broken her heart?"+GetSexPhrase(" Maybe it was you, captain?","")+"";
			link.l1 = ""+GetSexPhrase("I doubt it ","")+". Thank you, I must take my leave.";
			link.l1.go = "exit";
			
			SetQuestHeader("UV");
			AddQuestRecord("UV", "1");
			pchar.questTemp.UV_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("UV_Juli", "women_4", "woman", "woman", sti(pchar.rank), FRANCE, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_6");
			sld.lastname = StringFromKey("Neutral_7");
			sld.City = "PortPax";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto9");
			sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
			sld.dialog.currentnode = "Juli";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Украденное воспоминание
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("Well, everything can happen in our world. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. Maybe " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of a help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be a pleasure for me, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("I trust that I have made my point - I am done.","I had enough of your questions, captain. Go find something better to do!"),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Thanks, I should go.","Farewell.");
		link.l2.go = "exit";
	break;
	
/////////////////////////////////////////////////---слухи дворянок---////////////////////////////////////////////
	case "rumours_noblegirl":	
        srum = SelectRumourEx("noblegirl", NPChar);
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "Word around the harbor is that Julie d'Armagnac, the governor's niece, has become a mere shadow of her former self. Once radiant and full of life, now she drifts through the streets with unmistakable sorrow etched upon her face. The townsfolk whisper and wonder what might have befallen her, but none know the truth of it. Perhaps some scoundrel has broken her heart?"+GetSexPhrase(" Maybe it was you, captain?","")+"";
			link.l1 = ""+GetSexPhrase("I doubt it ","")+". Thank you, I must take my leave.";
			link.l1.go = "exit";
			
			SetQuestHeader("UV");
			AddQuestRecord("UV", "1");
			pchar.questTemp.UV_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("UV_Juli", "women_4", "woman", "woman", sti(pchar.rank), FRANCE, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_6");
			sld.lastname = StringFromKey("Neutral_7");
			sld.City = "PortPax";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto9");
			sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
			sld.dialog.currentnode = "Juli";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Украденное воспоминание
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("Well, everything can happen in our world. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be my pleasure, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("I trust that I have made my point - I am done.","I had enough of your questions, captain. Go find something better to do!"),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Thanks, I should go.","Farewell.");
		link.l2.go = "exit";
	break;
	
	///////////////////////////////////////////---слухи матросов---////////////////////////////////////////////
	case "rumours_sailor":	
		NextDiag.CurrentNode = "rumours";

		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "Two days past, there was a brazen attempt on the Port Chief's life! The would-be assassin lay in wait by his office door, but the Chief managed to cry for help. A musketeer arrived with haste and wounded the villain, though the knave managed to flee the city gates\nWord has it the Port Chief is offering a handsome bounty for the rogue's head! Thus far, no souls brave enough have come forward. Vous savez, même s'il offrait mille doublons - je n'accepterais pas...";
			link.l1 = "Thank you, I must take my leave.";
			link.l1.go = "exit";
			
			SetQuestHeader("GS");
			AddQuestRecord("GS", "1");
			pchar.questTemp.GS_Start = true;
			pchar.questTemp.GS_Portman = true;
			AddLandQuestMark(characterFromId("Beliz_portman"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Грани справедливости
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2) srum = SelectRumourEx("sailor", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" That's it...", " You might find it interesting.");
            posrep2 = " Hey, captain, do you have any news for our colony to tell?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Then tell me about...");
            answ2 = RandPhraseSimple(RandSwear() + "Whatever, just tell me something else...","Yeah, you were not much of a help, got anything else to share with me?");
            answ3 = RandPhraseSimple("Well, everything can happen in our world. Sorry, but I have nothing special to tell you. ","I am quite in a hurry, so next time perhaps.");
            answ4 = "";
        }
        else
        {
            posrep1 = " It is quite a dull place here. So if something does happen, then everyone will talk about it.";
            posrep2 = " Nothing of interest. " + GetAddress_Form(NPChar) + " might know something?";
            answ1 = RandPhraseSimple("Then tell me about...",RandSwear() + "You know nothing! Fine, another topic...");
            answ2 = RandPhraseSimple("Whatever, just tell me something else...","Yeah, you were not much of help, got anything else to share with me?");
            answ3 = RandPhraseSimple("I doubt that I've got anything of interest to tell you.","It will be my pleasure, but let's talk next time.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("Alas, nothing more to tell you, let me pass.","I had enough of your questions, excuse me, I've got a lot of other matters to do."),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Thanks, I should go.","Farewell.");
		link.l2.go = "exit";
	break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case "rumours_habitue":
		//-->работорговец
		if (pchar.questTemp.Slavetrader == "FindRatJamaica_H" && npchar.location == "FortOrange_tavern")
        {
			dialog.text = "(singing) We're rascals and scoundrels, we're villains and knaves; Drink up me 'earties, yo ho! We're devils and black sheep, we're really bad eggs, Drink up me 'earties, yo ho!! Hey, matey, how are you doing? How is the sea?";
            link.l1 = "Sea? She's the same bitch as always. Salty and wet. Tell me, where did my mate go, the one who rented a room here not long ago? Francois Gontier was his name.";
            link.l1.go = "Jamaica_ratH_1";
			break;
        }
		if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_H" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "(singing) Bonnie lassie, will you gang with me, bonnie lass, will ye lie near me? I'll get all your ribbons reel In the morning ere I leave ye!";
            link.l1 = "Have a drink, mate! How is the sea?";
            link.l1.go = "EscapeSlave_Villemstad_H1";
			break;
        }
		//<--работорговец
				
		//Голландский Гамбит, против всех
		if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "LetterToLucasSent" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "Eh, the sea... I wish I were in your shoes!";
            link.l1 = "Don't see any problems, friend. Join my crew anytime.";
            link.l1.go = "Lucas_Tavern";
			break;
        }
		//Голландский Гамбит
		
		//--> поиск дезертира
		if (CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE && !CheckAttribute(npchar, "quest.fugitive"))
        {
			dialog.text = LinkRandPhrase("You know, rum makes men friends! Ha-ha!","After a decent tot of rum even the hangman will seem lovely! Ha-ha!","When you drink you sleep, when you sleep you don't sin! Rum and ale will lead you to heavens, so drink, dammit! Ha!");
            link.l1 = "Sure, let's share a drink... Tell me, good man, do you know "+pchar.GenQuest.FindFugitive.Name+"? He is my old messmate. Some fellas told me that he has moved to this place...";
            link.l1.go = "FindFugitiveHb";
			break;
        }
		//<-- поиск дезертира
		
		//--> карибские нравы
		if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && npchar.location == "Portobello_tavern")
		{
			dialog.text = "News? Ha! Haven't you heard already? Our soldiers captured a French spy. Fucking imposter, tried to act like a merchant, but *hic* - our commander is a tough bastard!";
            link.l1 = "You don't say so! And what did that froggie tried to sniff out?";
            link.l1.go = "trial_spy";
			break;
		}
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	    {
			dialog.text = "Eh, " + GetAddress_Form(pchar) + " what a world are we living at... Shitty bastards all around!";
			link.l1 = "What do you mean, matey?";
			link.l1.go = "Alcogol_GenQuest_Church_2_1";
			break;
		}
		//<-- карибские нравы
		
		//--> Sinistra Длинные тени старых грехов
		if (CheckAttribute(pchar, "questTemp.DTSG_NightIskat") && npchar.city == "SentJons")
        {
			dialog.text = "Have you heard?! I can't believe it! The famous Captain Fleetwood was brutally murdered in London! Chased after glory, had it all and found only death... Had  he stayed here, he'd be safer. I say, sometimes it's better to appreciate what you have instead of chasing after money or rank, mark my words, sir!";
            link.l1 = "Friend, you know where everyone lives in the colony, right?";
            link.l1.go = "DTSG_NightIskat";
			break;
        }
		//<-- Длинные тени старых грехов
		
		//--> Rebbebion, квест "Путеводная звезда"
		if (CheckAttribute(pchar, "questTemp.Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.Sotta") && !CheckAttribute(npchar, "questTemp.Lutter") && npchar.city == "Beliz")
		{
			link.l1 = "So, the hero of the day, Captain Edgardo Sotta. What are people saying about him? And what do you think? I've been looking forward to meeting the man.";
			link.l1.go = "Sotta1";
			link.l2 = "Mate, why are you drinking alone? Everyone's gathering to watch the Windbag Matt's hanging right now.";
			link.l2.go = "Lutter1";
			break;
		}
		
		if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && !CheckAttribute(pchar, "questTemp.PZ.TortugaHabitueBlock") && npchar.city == "Tortuga")
		{
			link.l1 = "Listen, mate, I've been trying to find someone named Joep van der Vink. I need to give him a message. Do you know what he looks like or anything about him?";
			link.l1.go = "Sepp1";
			break;
		}
		//<-- квест "Путеводная звезда"
		
		//--> Тёмные воды исцеления
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "Have you heard? They say Thomas Morrison's daughter has been bedridden for six months now. Doctors are completely powerless against her ailment. The only one who can help her is the gypsy woman known for her potions that heal even the gravely ill. But she has flatly refused to do anything for the poor girl.";
			link.l1 = RandPhraseSimple(RandSwear() + "This is worth another cup...",
                                 "Fine, let's drink one more time.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Thanks, I should go.",
									 "Eh, helluva rum. Fine, I should go, have fun here.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("DWH");
			AddQuestRecord("DWH", "1");
			pchar.questTemp.DWH_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("DWH_gypsy", "gipsy_2", "woman", "towngirl", 10, PIRATE, -1, true, "citizen"));
			ChangeCharacterAddressGroup(sld, "SentJons_town", "goto", "goto1");
			sld.dialog.filename = "Quest\MiniEvents\DarkWatersOfHealing_dialog.c";
			sld.dialog.currentnode = "dwh_gypsy_0";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetLoginTime(sld, 07.00, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
		break;
		}
		//<-- Тёмные воды исцеления
		//--> Грани справедливости
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.GS_Start") && npchar.city == "Beliz";
		if (bOk1 || bOk2)
        {
			dialog.text = "Two days past, there was a brazen attempt on the Port Chief's life! The would-be assassin lay in wait by his office door, but the Chief managed to cry for help. A musketeer arrived with haste and wounded the villain, though the knave managed to flee the city gates\nWord has it the Port Chief is offering a handsome bounty for the rogue's head! Thus far, no souls brave enough have come forward. Mind you, even for a thousand doubloons - I'd not risk my neck...";
			link.l1 = RandPhraseSimple(RandSwear() + "This is worth another cup...",
                                 "Fine, let's drink one more time.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Thanks, I should go.",
									 "Eh, helluva rum. Fine, I should go, have fun here.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("GS");
			AddQuestRecord("GS", "1");
			pchar.questTemp.GS_Start = true;
			pchar.questTemp.GS_Portman = true;
			AddLandQuestMark(characterFromId("Beliz_portman"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Грани справедливости
		//--> Торговля по закону
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TPZ_Start") && npchar.city == "BasTer";
		if (bOk1 || bOk2)
        {
			dialog.text = "Heard the news?! It's a bloody outrage! Not a drop of rum or wine left in the tavern - how's a body to find relief in this blasted heat? The innkeeper's been feeding us empty promises for a week that the drink will flow again, but there's been nothing! Are we expected to parch our throats until Judgment Day?";
			link.l1 = RandPhraseSimple(RandSwear() + "This is worth another cup...",
                                 "Fine, let's drink one more time.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Thanks, I should go.",
									 "Eh, helluva rum. Fine, I should go, have fun here.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("TPZ");
			AddQuestRecord("TPZ", "1");
			pchar.questTemp.TPZ_Start = true;
			AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Торговля по закону
		//--> Старые счёты
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OS_Start") && npchar.city == "PuertoPrincipe";
		if (bOk1 || bOk2)
        {
			dialog.text = "Word around the docks is our barkeeper's in hot water! Someone's pilfered his gin! Not just a bottle, mind you, but a whole barrel of the stuff - the kind you won't find anywhere else in these islands! Brought all the way from Europe, they say. The old fox won't say who he was keeping it for, but one thing's certain: if that barrel doesn't turn up soon, there'll be hell to pay for the poor wretch!";
			link.l1 = RandPhraseSimple(RandSwear() + "This is worth another cup...",
                                 "Fine, let's drink one more time.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Thanks, I should go.",
									 "Eh, helluva rum. Fine, I should go, have fun here.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("OS");
			AddQuestRecord("OS", "1");
			pchar.questTemp.OS_Start = true;
			pchar.questTemp.OS_Tavern_1 = true;
			AddLandQuestMark(characterFromId("PuertoPrincipe_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Старые счёты
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		if (bOk1 || bOk2)
        {
			dialog.text = "Word around the harbor is that Julie d'Armagnac, the governor's niece, has become a mere shadow of her former self. Once radiant and full of life, now she drifts through the streets with unmistakable sorrow etched upon her face. The townsfolk whisper and wonder what might have befallen her, but none know the truth of it. Perhaps some scoundrel has broken her heart?"+GetSexPhrase(" Maybe it was you, captain?","")+"";
			link.l1 = RandPhraseSimple(RandSwear() + "This is worth another cup...",
                                 "Fine, let's drink one more time.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Thanks, I should go.",
									 "Eh, helluva rum. Fine, I should go, have fun here.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("UV");
			AddQuestRecord("UV", "1");
			pchar.questTemp.UV_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("UV_Juli", "women_4", "woman", "woman", sti(pchar.rank), FRANCE, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_6");
			sld.lastname = StringFromKey("Neutral_7");
			sld.City = "PortPax";
			ChangeCharacterAddressGroup(sld, "PortPax_town", "goto", "goto9");
			sld.dialog.filename = "Quest\MiniEvents\StolenMemory_dialog.c";
			sld.dialog.currentnode = "Juli";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "FRANCE_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Украденное воспоминание
		//--> В плену великого улова andre39966
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.VPVL_Start") && npchar.city == "FortFrance";
		if (bOk1 || bOk2)
        {
			dialog.text = "Word has it that fisherman Pierre Carno has vanished without a trace. Two dawns ago, he sailed into the blue and not a sign of him since. His wife, Lea, is beside herself with grief. By daylight and lamplight, she keeps her vigil at the pier, her eyous fixed on the endless waters, praying for a glimpse of her beloved's sail.";
			link.l1 = RandPhraseSimple(RandSwear() + "This is worth another cup...",
                                 "Fine, let's drink one more time.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Thanks, I should go.",
									 "Eh, helluva rum. Fine, I should go, have fun here.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("VPVL");
			AddQuestRecord("VPVL", "1");
			pchar.questTemp.VPVL_Start = true;
			AddDialogExitQuest("VPVL_Gegerate_Lea");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- В плену великого улова
		//--> Тайна Бетси Прайс
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.TBP_Start") && npchar.city == "Villemstad" && sti(pchar.rank) >= 1;
		if (bOk1 || bOk2)
        {
			dialog.text = "Captain, have you heard? There's a new waitress working at our tavern. They say she's quite the beauty. Men from all around have been rushing in just to catch a glimpse of her. But three days ago, she didn't show up for work, which greatly upset the tavern keeper who had been making enormous profits since her arrival. They say he's even willing to pay whoever can find the girl.​";
			link.l1 = RandPhraseSimple(RandSwear() + "This is worth another cup...",
                                 "Fine, let's drink one more time.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Thanks, I should go.",
									 "Eh, helluva rum. Fine, I should go, have fun here.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("TBP");
			AddQuestRecord("TBP", "1");
			pchar.questTemp.TBP_Start = true;
			pchar.questTemp.TBP_Tavern = true;
			AddLandQuestMark(CharacterFromID("Villemstad_tavernkeeper"), "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Тайна Бетси Прайс
		
		Dialog.Text = LinkRandPhrase("Well... hic! ","Ah, good rum! ","Well... ")+SelectRumourEx("habitue", NPChar);
		link.l1 = RandPhraseSimple(RandSwear() + "This is worth another cup...",
                                 "Fine, let's drink one more time.");
		link.l1.go = "sit_3";
		link.l2 = RandPhraseSimple("Thanks, I should go.",
                                 "Eh, helluva rum. Fine, I should go, have fun here.");
		link.l2.go = "exit_sit";
	break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_trader":
            if (!CheckAttribute(NPChar, "quest.repeat.rumours_trader") || NPChar.quest.repeat.rumours_trader!= 3 )
            strum = SelectRumourEx("trader", NPChar);
            else strum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
			Dialog.Text =  NPCStringReactionRepeat(strum, strum+" Yup. Nothing more to tell.",
                strum+" Now I should get back to business.",RandPhraseSimple("I have already told you, that I don't have time for cheap talks!","I am a busy man, I don't have time to talk gossip!"),"block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(pcharrepphrase(RandSwear() + "Interesting! But let's get to the point","Gratitude, here is one more thing."), pcharrepphrase(""+ GetSexPhrase("Damn me","Interesting") +"! Nice storyteller. But I have one more question.","Let's not waste more time and talk business."),
pcharrepphrase(RandSwear() +" One more thing and I'll leave.","You are correct, time is money."),pcharrepphrase("Always thinking only about your own profits! Fine, don't go mad.","Forgive me. Let's talk business."),npchar, Dialog.CurrentNode);
			link.l1.go = "business";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Farewell, you old drunkass.",
"Bye, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"."),pcharrepphrase("Caramba! Don't go far away. I'll be back shortly.","Pleasure to see you, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"! Farewell!")),NPCharRepPhrase(npchar,pcharrepphrase("Cast off!","Farewell!"),pcharrepphrase("Hey! What are you hiding there? Rum? No!?! Whatever, I'll get some drink.","I am sorry, I have an important business in the city.")),NPCharRepPhrase(npchar,pcharrepphrase("Heh! See you around!","I should go. Bye, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!"),pcharrepphrase("Don't you dare to argue with me! I have no wish for this!","I guess I should check my ship. See you, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),NPCharRepPhrase(npchar,pcharrepphrase("What's wrong you, pal? It's me - " +GetFullName(pchar)+ "! Have a nap, I will talk to you later.","I fear that your liver will kill you before I come here again."),pcharrepphrase("Count your silver, sly dog! I'll see you later.","Pleasure to see you, " + GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),npchar, Dialog.CurrentNode);
			link.l2.go = "Exit";
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_capitan":
			Dialog.Text = SelectRumourEx("capitan", NPChar);
			Link.l1 = RandPhraseSimple(RandSwear() + "Interesting! There is one more thing I want to ask...",
                                     "One more question.");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("Thanks, I should go.",
                                     "Farewell.");
			Link.l2.go = "exit";
			NextDiag.TempNode = "quests";
            NPChar.talk_date =  lastspeakdate();
		break;
		
		 case "rumours_landcaptain":
			Dialog.Text = SelectRumourEx("landcaptain", NPChar);
			Link.l1 = RandPhraseSimple(RandSwear() + "Interesting! There is one more thing I want to ask...",
                                     "One more question.");
			Link.l1.go = "question";
			Link.l2 = RandPhraseSimple("Thanks, I should go.",
                                     "Farewell.");
			Link.l2.go = "exit";
			NextDiag.TempNode = "question";
            NPChar.talk_date =  lastspeakdate();
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_tavern":  // homo 03/08/06
				if(startHeroType == 4)
				{
					Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("You know the price. Information is just like a room, food, or drink - it costs. That'll be a thousand pesos.",
					"You know the price. Information is just like a room, food, or drink - it costs. That'll be a thousand pesos.",
					"You know the price. Information is just like a room, food, or drink - it costs. That'll be a thousand pesos."),
					"Nothing more to add here. Now, excuse me, I should go.",
					"", "", "block", 1, npchar, Dialog.CurrentNode);
				 
					link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Actually, why am I even asking? I can ask anyone else about it. Sorry to bother you.",
											 "Actually, why am I even asking? I can ask anyone else about it. Sorry to bother you."), "", "", "", npchar, Dialog.CurrentNode);
					link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);//"rumours_tavern_no";
					NextDiag.CurrentNode = NextDiag.TempNode;
					if (makeint(pchar.money) >= 1000)
					{
						link.l2 = HeroStringReactionRepeat(RandPhraseSimple("I know, of course. Here's my payment.", "I know, of course. Here's my payment."),
						"", "", "" , npchar, Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
					else
					{
						link.l2 =  HeroStringReactionRepeat("I don't have such sum.", "", "", "", npchar, Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_no", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
				}
				else
				{
					Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("Information costs money. 1000 pesos and I will tell you everything I know.",
					"Something's wrong with my memory, 1000 pieces of eight might help me remember something.",
					"I am eager to share with information. But it will cost you 1000 pieces of eight. No haggling."),
					"Nothing more to add here. Now, excuse me, I should go.",
					"", "", "block", 1, npchar, Dialog.CurrentNode);
				 
					link.l1 = HeroStringReactionRepeat(RandPhraseSimple(RandSwear() + "I am not paying for a worthless chitchat.",
											 "I'll think about better ways to spend these money."), "Let's change the subject.", "Let's change the subject.", "Let's change the subject.", npchar, Dialog.CurrentNode);
					link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);//"rumours_tavern_no";
					NextDiag.CurrentNode = NextDiag.TempNode;
					if (makeint(pchar.money) >= 1000 )
					{
						link.l2 = HeroStringReactionRepeat(RandPhraseSimple("You will have them if I learn something worthy from you.", "I'll pay if you give me something of value."),
						 "", "", "" , npchar, Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
					else
					{
						link.l2 =  HeroStringReactionRepeat("I don't have such sum.", "", "", "", npchar, Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_no", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
				}

		break;
		
		case "rumours_tavern_yes":
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation"))
			{
				bool bOk = (pchar.questTemp.Saga.BarbTemptation == "silk") || (pchar.questTemp.Saga.BarbTemptation == "give_silk");
				if (bOk && npchar.location == "Marigo_tavern" && !CheckAttribute(npchar, "quest.barbtemptation"))
				{
					AddMoneyToCharacter(pchar, -1000);
					Dialog.Text =  "Our patrol has recently destroyed the brigantine of some French smuggler named Morel. The man is now sitting in the dungeons and facing a death sentence. Our commandant thinks that there wasn't a full cargo on his ship, so he still tries to find it... the Frenchie will die when the commandant find missing cargo.";
					link.l1 = "Interesting... Fine, take the money. Anything else to tell?";
					link.l1.go = "rumours_tavern";
					Saga_CreateMorelle(); //ставим Мореля
					npchar.quest.barbtemptation = "true";
					pchar.questTemp.Saga.BarbTemptation.Prison = "true";
					break;
				}
			}	
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_portobello" && npchar.location == "portobello_tavern")
			{
				DelLandQuestMark(npchar);
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text =  "There was a big party at the governor's palace. His Excellency's friend, Don Carlos de Milyar is back. He was captured in a sea battle, but he managed to escape with help of a French lieutenant. Don Carlos is not only smart, he is also a very generous man. With his support this lieutenant, Jean Deno, has become a captain of the 'Sario' now. As far as I've heard he was also gifted by a small plantation. Now the frogeater is called Juan! What a story!";
				link.l1 = "Intriguing... Fine, the money is yours. Take this. Anything else to tell me?";
				link.l1.go = "rumours_tavern";
				pchar.questTemp.FMQG = "headhunter_juan";
				AddQuestRecord("FMQ_Guadeloupe", "10");
				pchar.quest.FMQG_Juanship.win_condition.l1 = "location";
				pchar.quest.FMQG_Juanship.win_condition.l1.location = "PortoBello";
				pchar.quest.FMQG_Juanship.function = "FMQG_CreateJuanship";
				break;
			}	
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(pchar, "questTemp.FMQN") && pchar.questTemp.FMQN == "town" && npchar.location == "Marigo_tavern")
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text =  "Our commandant has sent extra forces to patrol the jungle and increased the number of guards in the town. There are rumors about Englishmen planning to infiltrate Philipsburg and set the captured officers free.";
				link.l1 = "You don't say so! Do they actually have the balls to pull such a trick? And what officers are you talking about exactly?";
				link.l1.go = "FMQN_r";
				break;
			}	
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && npchar.location == "Havana_tavern")
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text =  "The other day the whole town got stirred up like a hornet's nest. An officer from a military scooner got dead drunk in my tavern, and just about raped a married woman. Then proceeded to beat up her husband who tried to defend his wife, and even threatened him with a sword. Imagine all that right in front of the town's guard! As they say, right respects might. The soldiers just turned away while this bastard was raging\nBut the scoundrel was disarmed by, who could've even thought, some sailors from a merchant's ship. They almost wrapped him in a bow, although the bastard got away and hid on his ship. Commandant and the Alcalde tried to sweep it under the rug, but the outraged husband is a respected citizen, who turned to his Excellence Don Diego de Toledo and made some noise among the local gentry\nThey issued a warrant for the officer's arrest. There were rumors his captain was suggested leaving the port with him, and transferring the scoundrel to a different location. However, the schooner's captain, Esberdo Cabanas, is a man of honor. Once he learned what his officer has done, he immediately arrested him and sent him back to the shore. The bastard is rotting in prison for the foreseeable future, where he belongs if you ask me. And then, maybe, he'll be demonoted to a common soldier and flogged, just like an example for others.";
				link.l1 = "Wait, did you say Captain Esberdo Cabanas? Huh... an exciting story, indeed! Alright, you earned your money, here you go. Anything else you could tell me?";
				link.l1.go = "rumours_tavern";
				Mtraxx_CreateOfficer(); // ставим офицера-негодяя
				pchar.questTemp.Mtraxx = "jewelry_4";
				pchar.GenQuest.PrisonQuestLock = "true";
				AddQuestRecord("Roger_1", "7");
				DelLandQuestMark(characterFromId("Havana_tavernkeeper"));
				AddLandQuestMarkToPhantom("havana_prison", "havanaJailOff");
				break;
			}
			// Jason Исла Мона
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "rumours" && rand(2) == 1)
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text =  "They say some criminals were abandoned on one of the uninhabited islands! Supposedly, they're such ruthless monsters that neither the executioner nor the holy fathers dared deal with them! But why do they always end up bringing them here?!";
				link.l1 = "Hmm... how interesting! Maybe I should track them down and recruit them - I'm always in need of desperate souls... Why so white, mate? I'm joking, I'm joking... You've earned your money - here you go. Anything else of note you've heard?";
				link.l1.go = "rumours_tavern";
				IslaMona_TerksCreateHimenes();
				break;
			}
            string RumText = SelectRumourEx("tavern", NPChar); //fix
			
		    if(!RumourHasInformation(RumText))
            {
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; //fix
				if(startHeroType == 4)
				{
					link.l1 = "Turns out you don't know anything after all. I didn't expect you to trick me like this. Not too clever. Well, goodbye.";
				}
				else
				{
					link.l1 = RandPhraseSimple("Worthless crap. I am not gonna pay you a single peso! Bye.", "Your information costs nothing, so you'll get nothing.");
				}
			    link.l1.go = "Exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
            }
            else
            {
                AddMoneyToCharacter(pchar, -1000);
                Dialog.Text = RumText;
				if(startHeroType == 4)
				{
					link.l1 = "Really? Interesting, thanks. Well, I must be off, until next time.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = RandPhraseSimple("Thanks, take the money. Anything else to tell?", "Fine, take the money. Anything else to tell?");
					link.l1.go = "rumours_tavern";
				}
    			NextDiag.CurrentNode = NextDiag.TempNode;    
            }
		break;

		case "rumours_tavern_no":
			if(startHeroType == 4)
			{
				Dialog.Text = "You could've helped out with some coin. Unlike you, Helen, I don't have the Baron of the Brethren supporting me.";
				link.l1 = "You've got an entire establishment. And I got where I am on my own. Well, aside from the ship, the cannons, the crew, and the supplies the Baron got me. Alright, never mind.";
				link.l1.go = "exit";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
			else
			{
				Dialog.Text = "Get me right, I need to feed my family.";
				link.l1 = "Let's change the subject.";
				link.l1.go = "first time";
				NextDiag.CurrentNode = NextDiag.TempNode;
				link.l2 = LinkRandPhrase("Thanks, I should go.",
										 "Farewell.","Bye.");
				link.l2.go = "Exit";
			}
		break;	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_poor":
			if (!CheckAttribute(NPChar, "quest.repeat.rumours_poor") || NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("poor", NPChar);
				Link.l1 = RandPhraseSimple(RandSwear() + "Interesting. One more question...",
										"Hm, let me ask something else...");
				Link.l1.go = "rumours_poor_2";
				Link.l2 = RandPhraseSimple("Well, farewell.",
										"Bye, mate.");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple("I told you all I knew.", 
					"Nothing more to share, sorry...");
				Link.l1 = RandPhraseSimple("I see. Farewell.",
										"Goodbye, mate...");
				Link.l1.go = "exit";			
			}
            NPChar.talk_date = lastspeakdate();
		break;
        case "rumours_poor_2":
			if (NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("poor", NPChar);
				Link.l1 = RandPhraseSimple(RandSwear() + "Interesting. One more question...",
										"Hm, let me ask something else...");
				Link.l1.go = "rumours_poor";
				Link.l2 = RandPhraseSimple("Well, farewell.",
										"Bye, pal.");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple("I told you all I know.", 
					"Nothing more to share, sorry...");
				Link.l1 = RandPhraseSimple("I see. Farewell.",
										"Understood. Goodbye, mate...");
				Link.l1.go = "exit";			
			}
			NPChar.talk_date = lastspeakdate();
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_LSC":
			if (CheckNPCQuestDate(NPChar, "quest.repeat.rumours"))
			{
				Dialog.Text = SelectRumourExSpecial("LSC", NPChar);
				Link.l1 = RandPhraseSimple("Understood...",
										"I see...");
				Link.l1.go = "exit";
				SetNPCQuestDate(NPChar, "quest.repeat.rumours");
			}
			else  
			{
				Dialog.Text = NPCharSexPhrase(npchar, RandPhraseSimple("I told you all I knew.", "I haven't heard anything new, sorry..."), 
					RandPhraseSimple("I told you all I knew.", "I haven't heard anything new, sorry..."));
				Link.l1 = RandPhraseSimple("I see, bye then.", "Understood. Farewell, matey.");
				Link.l1.go = "exit";			
			}
		break;
		
//Jason -------------слухи смотрителей маяков, идентичны таверне, но бесплатны, по 1 шт за день--------------------
		case "rumours_lighthouse": 
			Dialog.Text = NPCStringReactionRepeat(RandPhraseSimple("Eh, captain! It's always nice chatting with you. Being on my own here is quite dull sometimes...", "I live alone, visitors are a rare occasion. So I am always in a mood to talk."), "Like talking, captain? Well, I might have something else to tell...", "Take a bottle of rum next time you visit me. Talks are better with drinks...", "Alas, I told you everything I knew. I have nothing to add.", "block", 1, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Then share your information. I like talking with people, you know...", "Tell me! Like they say who owns the information - he owns the world?"), "Like what?", "By all means! Got anything else to share?", "Fine, we had a nice chat anyway." , npchar, Dialog.CurrentNode);
    		link.l1.go = HeroStringReactionRepeat("rumours_lighthouse_yes", "rumours_lighthouse_void", "rumours_lighthouse_void", "exit", npchar, Dialog.CurrentNode);
		break;
		
		case "rumours_lighthouse_yes":
            RumText = SelectRumourEx("tavern", NPChar);
		    if(!RumourHasInformation(RumText))
            {
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
                link.l1 = RandPhraseSimple("Thank you! Anything else?", "Very interesting! Anything else?");

			    link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("Gratitude! It was quite entertaining...", "Thank you for telling me!");
			    link.l2.go = "exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
            }
            else
            {
                Dialog.Text = RumText;
    			link.l1 = RandPhraseSimple("Thank you! Anything else?", "Very interesting! Anything else?");
    			link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("Gratitude! It was quite entertaining...", "Thank you for telling me!");
			    link.l2.go = "exit";
    			NextDiag.CurrentNode = NextDiag.TempNode;    
            }
		break;
		
		case "rumours_lighthouse_void":
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
                link.l1 = RandPhraseSimple("Thank you! Anything else?", "Very interesting! Anything else?");

			    link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("Gratitude! It was quite entertaining...", "Thank you for telling me!");
			    link.l2.go = "exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
		break;
//Jason ------------------------------------почтовый генератор 2 уровня-------------------------------------------
		case "Postcureer_LevelUp_ForAll":
			//начинаем проверять
			if (!CheckCharacterItem(pchar, pchar.questTemp.WPU.Current.Item))
			{
				dialog.text = "But where is the package? Don't you have it?";
	        	link.l1 = "Well... I was supposed to deliver it to you. But it was... to be completely honest, it was taken from me. I couldn't fight back and gave those attackers the package by myself. ";
	        	link.l1.go = "Postcureer_LevelUp_complete_fail";
				break;
			}
			
			if (sti(pchar.questTemp.WPU.Postcureer.AgentChance) == 4)//раскрыли обман
			{
				dialog.text = "Hm. Excuse me, but the package was opened before! It's crystal for me. The seal has been re-stamped...";
	        	link.l1 = "" + GetAddress_FormToNPC(NPChar) + ", it is the package I was given at harbor office of " +XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+ ", and I have no clue...";
	        	link.l1.go = "Postcureer_LevelUp_complete_Agentfail";
				break;
			}
			
			if (pchar.questTemp.WPU.Postcureer == "late")//опоздали
			{
				int iTime = makeint(GetQuestPastDayParam("questTemp.Postcureer.Late"))+1;
				pchar.questTemp.WPU.Postcureer.Money = makeint(sti(pchar.questTemp.WPU.Postcureer.Money)/(sti(iTime)+1));//сильно снижаем оплату
				dialog.text = "I was waiting for you. But you are " + FindRussianDaysString(iTime)+ " late! The information you are carrying has become much less useful... It still has some value of course, so I will pay you " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + ". Please, take the money and farewell.";
	        	link.l1 = "Thanks. I guess.";
	        	link.l1.go = "Postcureer_LevelUp_complete";
				pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
				pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-1;//опоздавший рейс не засчитываем
				AddQuestRecord("Postcureer", "8");
				AddQuestUserData("Postcureer", "sDay", FindRussianDaysString(iTime));
				AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)));
				AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
				break;
			}
			
			if (pchar.questTemp.WPU.Postcureer == "lost")//опоздали совсем
			{
				dialog.text = "So it's you! I've been waiting for you quite a while, even took steps to retrieve the package. Give me it. I don't need it now really, thanks to your timing, but I'd like to keep it to myself\nAs you understand, I can't pay you anything, yet I will make sure your good name is restored.";
	        	link.l1 = "Thanks... I guess. I am sorry for the delay, I really am. Goodbye.";
	        	link.l1.go = "Postcureer_LevelUp_complete_bad";
				break;
			}
			dialog.text = "I was waiting for you. You are just in time, the information you brought me will be a good use. Please, accept this money for your job - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + ". My thanks for your timing.";
        	link.l1 = "You are welcome. Goodbye!";
        	link.l1.go = "Postcureer_LevelUp_complete";
			pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			AddQuestRecord("Postcureer", "10");
		break;
		
		case "Postcureer_LevelUp_complete":
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.Money));
			CloseQuestHeader("Postcureer");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
			AddCharacterExpToSkill(pchar, "Sailing", 120);//навигация
			AddCharacterExpToSkill(pchar, "Sneak", 120);//скрытность
			AddCharacterExpToSkill(pchar, "Leadership", 150);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 150);//везение
			ChangeCharacterComplexReputation(pchar,"nobility", 2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 2);
			Group_DeleteGroup("Fraht_Attack");
			DialogExit();
		break;
		
		case "Postcureer_LevelUp_complete_bad":
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddQuestRecord("Postcureer", "9");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", 10);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), 33);
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
			DialogExit();
		break;
		
		case "Postcureer_LevelUp_complete_fail":
			dialog.text = "Eh, I knew it would end this way... I should have hired a military courier vessel, not a civilian captain... Whatever, " + GetAddress_Form(NPChar) + ", you are not a soldier, so there is nothing to blame you for. Goodbye.";
			link.l1 = "Bye, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -2);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;//скрутим счетчик
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			pchar.questTemp.WPU.Postcureer = "complete";
		break;
		
		case "Postcureer_LevelUp_complete_Agentfail":
			dialog.text = "Sir, I know the harbor master of " +XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+ " personally, he is an honest man. Plus, there was no point for him to open the package. " + GetAddress_Form(NPChar) + ", you are a fraud! I am not gonna pay you a single copper. Fuck off!";
			link.l1 = "Hm...";
			link.l1.go = "Postcureer_LevelUp_complete_Agentfail_1";
		break;
		
		case "Postcureer_LevelUp_complete_Agentfail_1":
			if (pchar.questTemp.WPU.Postcureer == "begin") pchar.quest.PostcureerTime_Over.over = "yes";//снять таймер
			if (pchar.questTemp.WPU.Postcureer == "late") pchar.quest.PostcureerTime_FullOver.over = "yes";//снять второй таймер
			RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
			AddQuestRecord("Postcureer", "17");
			AddQuestUserData("Postcureer", "sSex", GetSexPhrase("",""));
			CloseQuestHeader("Postcureer");
			ChangeCharacterComplexReputation(pchar,"nobility", -10);
			ChangeCharacterNationReputation(pchar, sti(pchar.questTemp.WPU.Postcureer.Nation), -2);
			pchar.questTemp.WPU.Postcureer.count = sti(pchar.questTemp.WPU.Postcureer.count)-3;//скрутим счетчик
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.TargetPortmanID");
			DeleteAttribute(pchar, "questTemp.WPU.Current");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.LevelUp");
			DeleteAttribute(pchar, "questTemp.WPU.Postcureer.AgentChance");
			pchar.questTemp.WPU.Postcureer = "complete";
			DialogExit();
		break;
		
// <--почтовый генератор 2 уровня

//Jason --> ---------------------------------генератор Неудачливый вор--------------------------------------------
		case "Device_Common":
			dialog.text = "Looked like walking garbage. A vagrant or a pauper. Can't tell where exactly he went, I didn't care to follow him.";
			link.l1 = "Better than nothing. Thank you! I should go.";
			link.l1.go = "Device_Common_1";
		break;
		
		case "Device_Common_1":
			string sNation = pchar.GenQuest.Device.Shipyarder.Nation;
			sld = GetCharacter(NPC_GenerateCharacter("Device_poorman", "panhandler_"+(rand(5)+1), "man", "man", sti(pchar.rank)+5, sNation, 20, true, "quest"));
			SetFantomParamFromRank(sld, sti(pchar.rank)+5, true);         
			GiveItem2Character(sld, "slave_02");
			EquipCharacterbyItem(sld, "slave_02");
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, sNation+"_CITIZENS");
			sld.Dialog.Filename = "Quest\Other_Quests_NPC.c"; 
			sld.dialog.currentnode = "Device_poorman"; 
			sld.greeting = "Gr_poorman";
			switch (sti(pchar.GenQuest.Device.Shipyarder.Chance2))
			{
				case 0://в городе
					sld = characterFromId("Device_poorman");
					GetCharacterPos(pchar, &locx, &locy, &locz);
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.City +"_town", "goto", LAi_FindFarLocator("goto", locx, locy, locz));
				break;
				case 1://за воротами
					sld = characterFromId("Device_poorman");
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.City + "_ExitTown", "goto", "goto1");
				break;
				case 2://в бухте
					sld = characterFromId("Device_poorman");
					pchar.GenQuest.Device.Shipyarder.Shore = SelectQuestShoreLocation();
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Shore, "goto", "goto1");
				break;
				case 3://в доме
					sld = characterFromId("Device_poorman");
					pchar.GenQuest.Device.Shipyarder.Location = GetDeviceLocation(npchar); //определяем локацию
					ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Location, "goto", "goto1");
					if (pchar.GenQuest.Device.Shipyarder.Location == "none" || CheckAttribute(pchar, "GenQuest.SeekSpy.Location"))//если вдруг мимо или взят поиск шпиона
					{
						pchar.GenQuest.Device.Shipyarder.Shore = SelectQuestShoreLocation();
						ChangeCharacterAddressGroup(sld, pchar.GenQuest.Device.Shipyarder.Shore, "goto", "goto1");
					}
				break;
			}
			pchar.GenQuest.Device.Shipyarder = "inSeek";
			DialogExit();
			AddQuestRecord("Device", "9");
		break;
		//<-- генератор Неудачливый вор
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN_r":
			DelLandQuestMark(npchar);
			Dialog.Text =  "Not long ago an English vessel was captured within waters of Sint-Maarten, she was carrying a few high-ranked officers. There was decided to send them to Willemstad but at this moment they are held here in our comfortable dungeons. They say that one of captured soldiers has told our commandant about intentions of the English to sent here a raiding party to rescue the officers. That's why our good old commandant is ready and armed. Why wouldn't he be, if the prisoners are gone, he will be demoted to a common soldier!";
			link.l1 = "Intriguing... Fine, the money is yours. Take this. Anything else to tell me?";
			link.l1.go = "rumours_tavern";
			pchar.questTemp.FMQN = "governor";
			pchar.quest.FMQN_governor.win_condition.l1 = "location";
			pchar.quest.FMQN_governor.win_condition.l1.location = "Marigo_town";
			pchar.quest.FMQN_governor.function = "FMQN_ToGovernor";
			if (Whr_IsDay()) AddDialogExitQuest("FMQN_GetRumoursDay");
			else AddDialogExitQuest("FMQN_GetRumoursNight");
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Квесты мэра, проникновение во враждебный город
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "IntelligenceForAll":
            Dialog.Text = RandPhraseSimple("Very well then. I have the package here, ready to delivery. Take it\nDon't come here and don't talk to me anymore, it is too dangerous. Watch yourself out there...", 
				"Hm, great. Take the package and make sure you deliver it to the man we've just talked about\nGoodbye and don't talk to me anymore, it is too dangerous.");
            link.l1 = RandPhraseSimple("Got it. Goodbye...", "Farewell and good luck.");
			link.l1.go = "exit";
			pchar.GenQuest.Intelligence = "Execute";
			GiveItem2Character(pchar, "sicretLetter");
			AddCharacterExpToSkill(pchar, "Sneak", 200);
			ref rItem = ItemsFromID("sicretLetter");
			rItem.City = XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen")); 
			rItem.Mayor = GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)); 
			AddQuestRecord("MayorsQuestsList", "7");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony"+characters[GetCharacterIndex(pchar.GenQuest.Intelligence.MayorId)].city+"Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony"+pchar.GenQuest.Intelligence.City+"Voc")); // belamour gen
			AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)], "Gen"));
			AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.Intelligence.SpyId)]));			
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/////////		Грабеж среди бела дня, попытка залезть в сундуки
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "Man_FackYou":
			dialog.text = LinkRandPhrase("A robbery in the middle of the day!!! Really?! Stay where you are, pal...", "Hey, what are doing there?! Seems like someone was going to rob me. You are done...", "Wait, what are you going? A thief! End of the line, pal...");
			link.l1 = LinkRandPhrase("Crap!", "Carramba!", "Dammit!");
			link.l1.go = "fight_owner";
		break;
		case "fight_owner":
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break;
	}
}

string sRumourAboutOwners_CityRumour(string sCity, string sOwnerType) // Здесь идёт распределение по городам
{
	string sRetRumour = "Oh, seems like you've found a bug. Contact Jason and tell him about it, look for a 'Blackmark'.";
	// флаг - PChar.QuestTemp.RumoursAboutOwners.(sOwner) - для проверок, какой вопрос выпал. Ножно будет юзать для квестов
	switch(sCity)
	{
		case "Tortuga":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 0;
		break;
		
		case "PortRoyal":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 1;
		break;
		
		case "FortOrange":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 2;
		break;
		
		case "Beliz":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 3;
		break;
		
		case "PortoBello":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 4;
		break;
		
		case "Cartahena":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 5;
		break;
		
		case "Maracaibo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 6;
		break;
		
		case "Caracas":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 7;
		break;
		
		case "Cumana":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 8;
		break;
		
		case "SantaCatalina":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 9;
		break;
		
		case "SanJuan":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 10;
		break;
		
		case "Marigo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 11;
		break;
		
		case "Charles":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 12;
		break;
		
		case "SentJons":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 13;
		break;
		
		case "FortFrance":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 14;
		break;
		
		case "BasTer":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 15;
		break;
		
		case "Bridgetown":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 2);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 16;
		break;
		
		case "PortSpein":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 3);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 17;
		break;
		
		case "Havana":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 4);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 18;
		break;
		
		case "Villemstad":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 5);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 19;
		break;
		
		case "Santiago":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 6);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 20;
		break;
		
		case "PortPax":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 0);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 21;
		break;
		
		case "SantoDomingo":
			sRetRumour = sRumourAboutOwners_Init(sOwnerType, 1);
			PChar.QuestTemp.RumoursAboutOwners.(sOwnerType) = 22;
		break;
	}
	
	return sRetRumour;
}

string sRumourAboutOwners_Init(string sOwnerType, int iRumourNum) // База слухов жителей. Можно менять без новой игры
{
	
	string STR_MAYOR[MAX_RUMOURS_ABOUT_OWNERS]; // Губернаторы
	STR_MAYOR[0] = "Oh, sir governor is an excellent man. He manages our colony with great skill, never had a single conflict since the day of foundation\nHis only flaw is... he is... well... he is quite thrifty. It might be just another virtue though.";
	STR_MAYOR[1] = "Oh, sir governor is an excellent man. He manages our colony with great skill, never had a single conflict since the day of foundation\nHis only flaw is... he is... well... he is quite thrifty. It might be just another virtue though.";
	STR_MAYOR[2] = "Our governor is a good man but he is weak character. If he had a little firmness in his soul, our merchants could've got small tax breaks ... And it's already time to allocate subsidies for repairing the fort.";
	STR_MAYOR[3] = "Hmm ... He's recently become our governor. He is quite young and therefore very initiative. With him our colony is flourishing.";
	STR_MAYOR[4] = "Our governor is still relatively young. They say he is a good-for-nothing younger son of a Spanish count, sent far away from the yard to stop shaming his family. He has been appointed here quite recently, and didn't have time to create anything memorable.";
	STR_MAYOR[5] = "Hmm ... He's recently become our governor. He is quite young and therefore very initiative. With him our colony is flourishing";
	STR_MAYOR[6] = "Well... Nothing... I can't say anything bad about him...";
	
	string STR_TAVERNKEEPER[MAX_RUMOURS_ABOUT_OWNERS]; // Тавернщики
	STR_TAVERNKEEPER[0] = "Hm, I wouldn't trust my property to this rogue. Don't misunderstand me, but it seems to me that this is the most unreliable person in our town\nI heard he's working with pirates and smugglers whom often can be seen in his tavern.";
	STR_TAVERNKEEPER[1] = "What can we say about him! Cowardly, also not the smartest person I know. Besides, he is greedy for money, which is why he constantly gets into various troubles! But he is always up to date with all the news.";
	STR_TAVERNKEEPER[2] = "Quite a pleasant guy. It is always nice spending time in his tavern, he also got a great sense of humor. The most important thing about him is that he keeps a tavern in order and prevents drunk lowlifes from pestering good citizens.";
	STR_TAVERNKEEPER[3] = "Incredible man. He shouldn't keep a tavern but should be an informant for intelligence office. Sometimes it seems that he knows literally everything that happens in our town. It even scares me.";
	STR_TAVERNKEEPER[4] = "I don't know what to tell you. A man. Keeps a tavern. Knows everything about the town and its citizens.";
	STR_TAVERNKEEPER[5] = "They say that one can rely on it. On the other hand, I heard that he doesn't like unnecessary risk and always careful in doing his business. Yes, and dark affairs is not his type of business.";
	STR_TAVERNKEEPER[6] = "He's got the tavern from his father. His father kept a tavern not far from here, on the island of Highrock on another archipelago. Then his father moved here, built a new tavern here, and now his son runs it..";
	
	string STR_SHIPYARDER[MAX_RUMOURS_ABOUT_OWNERS]; // Верфисты
	STR_SHIPYARDER[0] = "Builds ships. I dunno. He's a quiet and peaceful. I guess, he's a good man.";
	STR_SHIPYARDER[1] = "Builds ships. I dunno. He's a quiet and peaceful. I guess, he's a good man.";
	STR_SHIPYARDER[2] = "A good man, but they say that he is too harsh. Constantly scolds all employees. Therefore, they often leave. Still, in spite of this, he is an excellent shipbuilder.";
	STR_SHIPYARDER[3] = "He is a very educated person. I heard that he studied shipbuilding in England, then in Holland. And in the end, he ended up here - far from the metropolis, in the provincial archipelago\nPeople say that he had troubles with the Holy Inquisition, and he had to flee to the colony.";
	STR_SHIPYARDER[4] = "This old man has to retire already and give the road for some fresh blood. He constantly dreams of past times, and grumbles when someone orders something from him besides caravels or galleons.";
	STR_SHIPYARDER[5] = "Great lad. Always willing to help. I have to say, he builds fine ships for such a shithole like this place.";
	STR_SHIPYARDER[6] = "He was a prisoner, exiled from Europe to our colony until it turned out that he had a talent for shipbuilding. After two magnificent brigs had been built under his leadership at the shipyard of our colony, he was forgiven for his transgressions, and now he is a full member of our society.";
	
	string STR_TRADER[MAX_RUMOURS_ABOUT_OWNERS]; // Магазинщики
	STR_TRADER[0] = "I can't say anything bad about him. A decent citizen, often visits our chapel. People seem to like him. Never heard of anyone being angry at him.";
	STR_TRADER[1] = "He is the main supplier of our governor, and this gives him a good income. But he conducts his affairs honestly. Well, at least he hasn't been noticed in anything shaming for him.";
	STR_TRADER[2] = "This fat man has a big respect in our city. His goods are always excellent, and I don't remember a single case he has ever cheated someone.";
	STR_TRADER[3] = "He's good-for-nothing, really. Trades, but no sense. Sometimes one good is out of stock, sometimes another, sometimes a half of goods... He can't even get himself out of debts.";
	STR_TRADER[4] = "He is not a good man, monsieur. I heard that he was Piere Thiers's right hand, previous trader, but he ruined his business it and then bought the store. I don't know how about the quality of the goods that he sells, but as a person he is very unpleasant to me.";
	STR_TRADER[5] = "Oh! He is an ugly man, I wouldn't advise you to have any business with him\nHe keeps a half of the inhabitants of our city in debt! And the goods those are sold in his store are always of poor quality.";
	STR_TRADER[6] = "Nobody really knows anything about him. He has recently moved here, and immediately opened his business. Trades honestly, wasn't caught at smuggling.";
	
	string sTempMayor = STR_MAYOR[iRumourNum];
	string sTempTavernkeper = STR_TAVERNKEEPER[iRumourNum];
	string sTempShipyarder = STR_SHIPYARDER[iRumourNum];
	string sTempTrader = STR_TRADER[iRumourNum];
	
	if(sOwnerType == "Mayor") return sTempMayor;
	if(sOwnerType == "TavernKeeper") return sTempTavernkeper;
	if(sOwnerType == "ShipYarder") return sTempShipyarder;
	if(sOwnerType == "Trader") return sTempTrader;
}

string GetDeviceLocation(ref npchar)
{
    aref	arCommon, arRld, arRld2;
    int	i, n, Qty, Qty2;
	string LocId; 
	string	storeArray [50];
	int howStore = 0;
    makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
    if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId") || CheckAttribute(pchar, "GenQuest.SeekSpy.Location")) //если взят квест по доставке малявы или шпиона
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != pchar.GenQuest.SeekSpy.Location)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != pchar.GenQuest.SeekSpy.Location && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2" && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	else
	{
		for (i=0; i<Qty; i++)
		{
    		arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
    		if (findsubstr(LocId, "Common" , 0) != -1)
    		{			
				storeArray[howStore] = LocId;
				howStore++; 
			}
			if (arCommon.label != "Sea")
			{	
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n=0; n<Qty2; n++)
				{
    				arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common" , 0) != -1 && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2" && arCommon.name != "reload1") // mitrokosta fix
    				{
						storeArray[howStore] = LocId;
						howStore++; 					
					}
				}
			}	
		}
	}
	if (howStore == 0) return "none";
	LocId = storeArray[hrand(howStore-1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); //открываем дверь
	for(n=0; n<MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId) 
		{			
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}
