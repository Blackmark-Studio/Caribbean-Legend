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
			dialog.text = "Słyszeliście? Mówią, że córka Thomasa Morrisona od pół roku nie wstaje z łóżka. Lekarze są całkowicie bezradni wobec jej choroby. Jedyną osobą, która mogłaby jej pomóc, jest cyganka słynąca z mikstur, które stawiają na nogi nawet ciężko chorych. Ale stanowczo odmówiła zrobienia czegokolwiek dla biedaczki.";
			link.l1 = "Interesujące, dziękuje za informacje.";
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
			dialog.text = "Przedwczoraj miała miejsce zuchwała próba zamachu na naczelnika portu! Zabójca czekał na niego przy wyjściu z biura, ale zdążył wezwać pomoc. Muszkieter przybył na czas i ranił napastnika, ale przestępcy udało się uciec z miasta\nMówią, że naczelnik portu oferuje hojną nagrodę za jego głowę! Jak dotąd, żadne odważne dusze się nie zgłosiły.";
			link.l1 = "Dziękuję, muszę się pożegnać.";
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
			dialog.text = "Słyszeliście te wieści?! To istne bezprawie! Ani kropli rumu czy wina w tawernie - jak człowiek ma znaleźć ulgę w ten przeklęty upał? Karczmarz już tydzień karmi nas pustymi obietnicami, że trunek znów popłynie, ale jak dotąd nic! Czy mamy chodzić z wysuszonymi gardłami aż do Sądu Ostatecznego?";
			link.l1 = "Myślałem, że każdy trzyma jakieś ukryte zapasy na czarną godzine. Wasz problem najwyraźniej.";
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
			dialog.text = "Wieści krążące po porcie mówią, że Julie d'Armagnac, siostrzenica gubernatora, stała się jedynie cieniem dawnej siebie. Niegdyś promieniejąca i pełna życia, teraz snuje się po ulicach z wyraźnym smutkiem wypisanym na twarzy. Mieszkańcy szepczą i zastanawiają się, co mogło ją spotkać, ale nikt nie zna prawdy. Być może jakiś niegodziwiec złamał jej serce?"+GetSexPhrase(" Może to był pan, kapitanie?","")+"";
			link.l1 = ""+GetSexPhrase("Wątpię w to. ","")+"Dziękuję za informację.";
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
			dialog.text = "Krążą słuchy, że rybak Pierre Carno zniknął bez śladu. Dwa świty temu wypłynął w morze i dotąd nie ma po nim śladu. Jego żona, Lea, jest zrozpaczona. Dniem i nocą pełni wartę na molo, wpatrując się w bezkresne wody, modląc się o choćby cień żagla ukochanego.";
			link.l1 = "Hm, może warto się tym zainteresować?... Dziękuję za informację.";
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
			dialog.text = "Kapitanie, słyszałeś? W naszej tawernie pracuje nowa kelnerka. Mówią, że to prawdziwa piękność. Mężczyźni z całej okolicy zbiegali się, by na nią spojrzeć. Ale trzy dni temu nie przyszła do pracy, co bardzo zasmuciło właściciela tawerny, który od jej pojawienia się zaczął osiągać ogromne zyski. Mówią, że jest nawet gotów zapłacić temu, kto zdoła znaleźć dziewczynę.​";
			link.l1 = "Doprawdy? Chyba nie zaszkodzi spróbować.";
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
            posrep1 = RandPhraseSimple(" Wystarczy...", " Może Cię to zainteresować.");
            posrep2 = " Hej, kapitanie, czy masz jakieś wieści dla naszej kolonii?";
            answ1 = RandPhraseSimple(RandSwear() + "That's very interesting, "+GetFullName(NPChar)+".",
                                 "Opowiedz mi zatem o...");
            answ2 = RandPhraseSimple(RandSwear() + "Interesujące! Jest jeszcze jedno pytanie, które chcę zadać...","Jeszcze jedno pytanie.");
            answ3 = RandPhraseSimple("Cóż, wszystko może się zdarzyć. Przepraszam, ale nie mam nic specjalnego do powiedzenia. ","Bardzo się spieszę, więc może następnym razem.");
            answ4 = "";
        }
        else
        {
            posrep1 = " Tutaj jest dość nudno. Więc jeśli coś się wydarzy, to wszyscy będą o tym mówić.";
            posrep2 = " Nic ciekawego. Może " + GetAddress_Form(NPChar) + " będzie coś wiedzieć?";
            answ1 = RandPhraseSimple("Opowiedz mi zatem o...",RandSwear() + "Nic nie wiesz! Dobra, inny temat...");
            answ2 = RandPhraseSimple("No cóż, powiedz mi coś jeszcze...","No cóż, nie byłeś zbyt pomocny, masz coś jeszcze, czym chciałbyś się ze mną podzielić?");
            answ3 = RandPhraseSimple("Wątpię, żebym miał ci coś interesującego do powiedzenia.","Będzie mi bardzo miło, ale porozmawiamy następnym razem.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("Niestety, nie mam ci nic więcej do powiedzenia, pozwól mi przejść.","Mam już dość twoich pytań, wybacz, mam jeszcze mnóstwo innych spraw do zrobienia."),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
                                            answ2,
                                            answ3,
                                            answ4,
                                            npchar, Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple("Dziękuję, muszę już iść.","Dziękuje, do widzenia.");
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
			dialog.text = "Słyszeliście? Mówią, że córka Thomasa Morrisona od pół roku nie wstaje z łóżka. Lekarze są całkowicie bezradni wobec jej choroby. Jedyną osobą, która mogłaby jej pomóc, jest cyganka słynąca z mikstur, które stawiają na nogi nawet ciężko chorych. Ale stanowczo odmówiła zrobienia czegokolwiek dla biedaczki.";
			link.l1 = "Dziękuję, muszę się pożegnać.";
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
			dialog.text = "Przedwczoraj miała miejsce zuchwała próba zamachu na naczelnika portu! Zabójca czekał na niego przy wyjściu z biura, ale zdążył wezwać pomoc. Muszkieter przybył na czas i ranił napastnika, ale przestępcy udało się uciec z miasta\nMówią, że naczelnik portu oferuje hojną nagrodę za jego głowę! Jak dotąd, żadne odważne dusze się nie zgłosiły. Wiecie co, nawet gdyby zaoferował tysiąc dubonów - nie zgodziłbym się...";
			link.l1 = "Dziękuję, muszę się pożegnać.";
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
			dialog.text = "Słyszeliście te wieści?! To istne bezprawie! Ani kropli rumu czy wina w tawernie - jak człowiek ma znaleźć ulgę w ten przeklęty upał? Karczmarz już tydzień karmi nas pustymi obietnicami, że trunek znów popłynie, ale jak dotąd nic! Czy mamy wysuszyć gardła aż do Sądu Ostatecznego?";
			link.l1 = "Myślałem, że każdy trzyma jakieś ukryte zapasy na czarną godzine. Wasz problem najwyraźniej.";
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
			dialog.text = "Wieści krążące po porcie mówią, że Julie d'Armagnac, siostrzenica gubernatora, stała się jedynie cieniem dawnej siebie. Niegdyś promieniejąca i pełna życia, teraz snuje się po ulicach z wyraźnym smutkiem wypisanym na twarzy. Mieszkańcy szepczą i zastanawiają się, co mogło ją spotkać, ale nikt nie zna prawdy. Być może jakiś niegodziwiec złamał jej serce?"+GetSexPhrase(" Może to był pan, kapitanie?","")+"";
			link.l1 = ""+GetSexPhrase("Wątpię w to. ","")+"Dziękuję za informacje.";
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
			dialog.text = "Krążą słuchy, że rybak Pierre Carno zniknął bez śladu. Dwa świty temu wypłynął w morze i dotąd nie ma po nim śladu. Jego żona, Lea, jest zrozpaczona. Dniem i nocą pełni wartę na molo, wpatrując się w bezkresne wody, modląc się o choćby cień żagla ukochanego.";
			link.l1 = "Dziękuję, muszę się pożegnać.";
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
			dialog.text = "Kapitanie, słyszałeś? W naszej tawernie pracuje nowa kelnerka. Mówią, że to prawdziwa piękność. Mężczyźni z całej okolicy zbiegali się, by na nią spojrzeć. Ale trzy dni temu nie przyszła do pracy, co bardzo zasmuciło właściciela tawerny, który od jej pojawienia się zaczął osiągać ogromne zyski. Mówią, że jest nawet gotów zapłacić temu, kto zdoła znaleźć dziewczynę.​";
			link.l1 = "Dziękuję, muszę się pożegnać.";
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
            posrep1 = RandPhraseSimple(" To wszystko...", " Może Cię to zainteresować.");
            posrep2 = " Hej, kapitanie, czy masz jakieś wieści dla naszej kolonii?";
            answ1 = RandPhraseSimple(RandSwear() + "To bardzo interesujące., "+GetFullName(NPChar)+".",
                                 "A teraz opowiedz mi o...");
            answ2 = RandPhraseSimple(RandSwear() + "Nieważne, powiedz mi coś jeszcze...","Tak, nie byłeś zbyt pomocny, masz coś jeszcze do powiedzenia?");
            answ3 = RandPhraseSimple("Cóż, w naszym świecie może zdarzyć się wszystko. Przepraszam, ale nie mam nic specjalnego do powiedzenia. ","Bardzo się spieszę, więc może następnym razem.");
            answ4 = "";
        }
        else
        {
            posrep1 = " Tutaj jest dość nudno. Więc jeśli coś się wydarzy, to wszyscy będą o tym mówić.";
            posrep2 = " Nic interesującego. " + GetAddress_Form(NPChar) + " może coś wiedzieć?";
            answ1 = RandPhraseSimple("Opowiedz mi zatem o...",RandSwear() + "Nic nie wiesz! Dobra, inny temat...");
            answ2 = RandPhraseSimple("Nieważne, powiedz mi coś jeszcze...", "Tak, nie byłeś zbyt pomocny, masz coś jeszcze do powiedzenia?");
            answ3 = RandPhraseSimple("Wątpię, żebym miał ci coś ciekawego do powiedzenia.","To będzie dla mnie przyjemność, ale porozmawiajmy następnym razem.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("Niestety, nie mam już nic więcej do powiedzenia, pozwól mi przejść.","Mam już dość twoich pytań, wybacz, mam jeszcze wiele innych spraw do zrobienia."),"block", 1, npchar, Dialog.CurrentNode);
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
            posrep1 = RandPhraseSimple(" To wszystko...", " Może Cię to zainteresować.");
            posrep2 = " Hej, kapitanie, czy masz jakieś wieści dla naszej kolonii?";
            answ1 = RandPhraseSimple(RandSwear() + "To bardzo interesujące., "+GetFullName(NPChar)+".",
                                 "A teraz opowiedz mi o...");
            answ2 = RandPhraseSimple(RandSwear() + "Nieważne, powiedz mi coś jeszcze...","Tak, nie byłeś zbyt pomocny, masz coś jeszcze do powiedzenia?");
            answ3 = RandPhraseSimple("Cóż, w naszym świecie może zdarzyć się wszystko. Przepraszam, ale nie mam nic specjalnego do powiedzenia. ","Bardzo się spieszę, więc może następnym razem.");
            answ4 = "";
        }
        else
        {
            posrep1 = " Tutaj jest dość nudno. Więc jeśli coś się wydarzy, to wszyscy będą o tym mówić.";
            posrep2 = " Nic interesującego. " + GetAddress_Form(NPChar) + " może coś wiedzieć?";
            answ1 = RandPhraseSimple("Opowiedz mi zatem o...",RandSwear() + "Nic nie wiesz! Dobra, inny temat...");
            answ2 = RandPhraseSimple("Nieważne, powiedz mi coś jeszcze...", "Tak, nie byłeś zbyt pomocny, masz coś jeszcze do powiedzenia?");
            answ3 = RandPhraseSimple("Wątpię, żebym miał ci coś ciekawego do powiedzenia.","To będzie dla mnie przyjemność, ale porozmawiajmy następnym razem.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("Niestety, nie mam już nic więcej do powiedzenia, pozwól mi przejść.","Mam już dość twoich pytań, wybacz, mam jeszcze wiele innych spraw do zrobienia."),"block", 1, npchar, Dialog.CurrentNode);
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
		if (bOk1 || bOk2)
        {
			dialog.text = "Wieści krążące po porcie mówią, że Julie d'Armagnac, siostrzenica gubernatora, stała się jedynie cieniem dawnej siebie. Niegdyś promieniejąca i pełna życia, teraz snuje się po ulicach z wyraźnym smutkiem wypisanym na twarzy. Mieszkańcy szepczą i zastanawiają się, co mogło ją spotkać, ale nikt nie zna prawdy. Być może jakiś niegodziwiec złamał jej serce?"+GetSexPhrase(" Może to był pan, kapitanie?","")+"";
			link.l1 = ""+GetSexPhrase("Wątpię w to. ","")+"Dziękuję, muszę się pożegnać.";
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
            posrep1 = RandPhraseSimple(" To wszystko...", " Może Cię to zainteresować.");
            posrep2 = " Hej, kapitanie, czy masz jakieś wieści dla naszej kolonii?";
            answ1 = RandPhraseSimple(RandSwear() + "To bardzo interesujące., "+GetFullName(NPChar)+".",
                                 "A teraz opowiedz mi o...");
            answ2 = RandPhraseSimple(RandSwear() + "Nieważne, powiedz mi coś jeszcze...","Tak, nie byłeś zbyt pomocny, masz coś jeszcze do powiedzenia?");
            answ3 = RandPhraseSimple("Cóż, w naszym świecie może zdarzyć się wszystko. Przepraszam, ale nie mam nic specjalnego do powiedzenia. ","Bardzo się spieszę, więc może następnym razem.");
            answ4 = "";
        }
        else
        {
            posrep1 = " Tutaj jest dość nudno. Więc jeśli coś się wydarzy, to wszyscy będą o tym mówić.";
            posrep2 = " Nic interesującego. " + GetAddress_Form(NPChar) + " może coś wiedzieć?";
            answ1 = RandPhraseSimple("Opowiedz mi zatem o...",RandSwear() + "Nic nie wiesz! Dobra, inny temat...");
            answ2 = RandPhraseSimple("Nieważne, powiedz mi coś jeszcze...", "Tak, nie byłeś zbyt pomocny, masz coś jeszcze do powiedzenia?");
            answ3 = RandPhraseSimple("Wątpię, żebym miał ci coś ciekawego do powiedzenia.","To będzie dla mnie przyjemność, ale porozmawiajmy następnym razem.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("Mam nadzieję, że wyraziłem swoje zdanie – skończyłem.","Mam już dość twoich pytań, kapitanie. Znajdź sobie coś lepszego do roboty!"),"block", 1, npchar, Dialog.CurrentNode);
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
			dialog.text = "Wieści krążące po porcie mówią, że Julie d'Armagnac, siostrzenica gubernatora, stała się jedynie cieniem dawnej siebie. Niegdyś promieniejąca i pełna życia, teraz snuje się po ulicach z wyraźnym smutkiem wypisanym na twarzy. Mieszkańcy szepczą i zastanawiają się, co mogło ją spotkać, ale nikt nie zna prawdy. Być może jakiś niegodziwiec złamał jej serce?"+GetSexPhrase(" Może to był pan, kapitanie?","")+"";
			link.l1 = ""+GetSexPhrase("Wątpię w to. ","")+"Dziękuję, muszę się pożegnać.";
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
            posrep1 = RandPhraseSimple(" To wszystko...", " Może Cię to zainteresować.");
            posrep2 = " Hej, kapitanie, czy masz jakieś wieści dla naszej kolonii?";
            answ1 = RandPhraseSimple(RandSwear() + "To bardzo interesujące., "+GetFullName(NPChar)+".",
                                 "A teraz opowiedz mi o...");
            answ2 = RandPhraseSimple(RandSwear() + "Nieważne, powiedz mi coś jeszcze...","Tak, nie byłeś zbyt pomocny, masz coś jeszcze do powiedzenia?");
            answ3 = RandPhraseSimple("Cóż, w naszym świecie może zdarzyć się wszystko. Przepraszam, ale nie mam nic specjalnego do powiedzenia. ","Bardzo się spieszę, więc może następnym razem.");
            answ4 = "";
        }
        else
        {
            posrep1 = " Tutaj jest dość nudno. Więc jeśli coś się wydarzy, to wszyscy będą o tym mówić.";
            posrep2 = " Nic interesującego. " + GetAddress_Form(NPChar) + " może coś wiedzieć?";
            answ1 = RandPhraseSimple("Opowiedz mi zatem o...",RandSwear() + "Nic nie wiesz! Dobra, inny temat...");
            answ2 = RandPhraseSimple("Nieważne, powiedz mi coś jeszcze...", "Tak, nie byłeś zbyt pomocny, masz coś jeszcze do powiedzenia?");
            answ3 = RandPhraseSimple("Wątpię, żebym miał ci coś ciekawego do powiedzenia.","To będzie dla mnie przyjemność, ale porozmawiajmy następnym razem.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("Mam nadzieję, że wyraziłem swoje zdanie – skończyłem.","Mam już dość twoich pytań, kapitanie. Znajdź sobie coś lepszego do roboty!"),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Dziękuję, muszę już iść.","Żegnaj.");
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
			dialog.text = "Przedwczoraj miała miejsce zuchwała próba zamachu na naczelnika portu! Zabójca czekał na niego przy wyjściu z biura, ale zdążył wezwać pomoc. Muszkieter przybył na czas i ranił napastnika, ale przestępcy udało się uciec z miasta\nMówią, że naczelnik portu oferuje hojną nagrodę za jego głowę! Jak dotąd, żadne odważne dusze się nie zgłosiły. Wiecie co, nawet gdyby zaoferował tysiąc dubonów - nie zgodziłbym się...";
			link.l1 = "Dziękuję, muszę się pożegnać.";
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
            posrep1 = RandPhraseSimple(" To wszystko...", " Może Cię to zainteresować.");
            posrep2 = " Hej, kapitanie, czy masz jakieś wieści dla naszej kolonii?";
            answ1 = RandPhraseSimple(RandSwear() + "To bardzo interesujące., "+GetFullName(NPChar)+".",
                                 "A teraz opowiedz mi o...");
            answ2 = RandPhraseSimple(RandSwear() + "Nieważne, powiedz mi coś jeszcze...","Tak, nie byłeś zbyt pomocny, masz coś jeszcze do powiedzenia?");
            answ3 = RandPhraseSimple("Cóż, w naszym świecie może zdarzyć się wszystko. Przepraszam, ale nie mam nic specjalnego do powiedzenia. ","Bardzo się spieszę, więc może następnym razem.");
            answ4 = "";
        }
        else
        {
            posrep1 = " Tutaj jest dość nudno. Więc jeśli coś się wydarzy, to wszyscy będą o tym mówić.";
            posrep2 = " Nic interesującego. " + GetAddress_Form(NPChar) + " może coś wiedzieć?";
            answ1 = RandPhraseSimple("Zatem opowiedz mi o...",RandSwear() + "Nic nie wiesz! Dobra, inny temat...");
            answ2 = RandPhraseSimple("Nieważne, powiedz mi coś jeszcze...","Tak, nie byłeś zbyt pomocny, masz coś jeszcze do powiedzenia?");
            answ3 = RandPhraseSimple("Wątpię, żebym miał ci coś ciekawego do powiedzenia.","To będzie dla mnie przyjemność, ale porozmawiajmy następnym razem.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("Niestety, nie mam już nic więcej do powiedzenia, pozwól mi przejść.","Mam już dość twoich pytań, wybacz, mam jeszcze wiele innych spraw do zrobienia."),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Dziękuję, muszę już iść.","Do widzenia.");
		link.l2.go = "exit";
	break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case "rumours_habitue":
		//-->работорговец
		if (pchar.questTemp.Slavetrader == "FindRatJamaica_H" && npchar.location == "FortOrange_tavern")
        {
			dialog.text = "(śpiewa) Hej, ha! Kolejkę nalej! Hej, ha! Kielichy wznieśmy!To zrobi doskonale morskim opowieściom! Hej, kolego, jak się masz? Jak tam morze?";
            link.l1 = "Morze? Ta sama suka co zawsze. Słona i mokra. Powiedz mi, dokąd poszedł mój kumpel, ten, który niedawno wynajął tu pokój? Nazywał się Francois Gontier.";
            link.l1.go = "Jamaica_ratH_1";
			break;
        }
		if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_H" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "(śpiewa) Szkołeś mi dało twardą, uczyłoś łodzią pływać! Żagle pięknie cerować, żagle pięknie cerować, codziennie pokład zmywać! Hej, kolego, jak się masz? Jak tam morze?";
            link.l1 = "Wypij drinka, kolego! Jak tam morze?";
            link.l1.go = "EscapeSlave_Villemstad_H1";
			break;
        }
		//<--работорговец
				
		//Голландский Гамбит, против всех
		if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "LetterToLucasSent" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "Ech, morze... Chciałbym być na twoim miejscu!";
            link.l1 = "Nie widzę żadnych problemów, przyjacielu. Dołącz do mojej ekipy w każdej chwili.";
            link.l1.go = "Lucas_Tavern";
			break;
        }
		//Голландский Гамбит
		
		//--> поиск дезертира
		if (CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE && !CheckAttribute(npchar, "quest.fugitive"))
        {
			dialog.text = LinkRandPhrase("Wiesz, rum czyni ludzi przyjaciółmi! Ha-ha!","Po porządnej porcji rumu nawet kat wyda się uroczy! Ha-ha!","Kiedy pijesz, śpisz, kiedy śpisz, nie grzeszysz! Rum i piwo zaprowadzą cię do nieba, więc pij, do cholery! Ha!");
            link.l1 = "Jasne, napijmy się... Powiedz mi, dobry człowieku, czy znasz może "+pchar.GenQuest.FindFugitive.Name+"? To mój stary kumpel. Kilku facetów powiedziało mi, że przeprowadził się w to miejsce...";
            link.l1.go = "FindFugitiveHb";
			break;
        }
		//<-- поиск дезертира
		
		//--> карибские нравы
		if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && npchar.location == "Portobello_tavern")
		{
			dialog.text = "Wiadomości? Ha! Nie słyszeliście już? Nasi żołnierze złapali francuskiego szpiega. Pieprzony oszust, próbował udawać kupca, ale *hic* - nasz dowódca to twardy drań!";
            link.l1 = "Nie mów tak! A co ta żabka próbowała wywęszyć?";
            link.l1.go = "trial_spy";
			break;
		}
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	    {
			dialog.text = "Eh, " + GetAddress_Form(pchar) + " W jakim świecie żyjemy... Same podłe dranie dookoła!";
			link.l1 = "Co masz na myśli, kolego?";
			link.l1.go = "Alcogol_GenQuest_Church_2_1";
			break;
		}
		//<-- карибские нравы
		
		//--> Sinistra Длинные тени старых грехов
		if (CheckAttribute(pchar, "questTemp.DTSG_NightIskat") && npchar.city == "SentJons")
        {
			dialog.text = "Słyszałeś?! Nie mogę w to uwierzyć! Słynny kapitan Fleetwood został brutalnie zamordowany w Londynie! Gonił za chwałą, miał wszystko i znalazł tylko śmierć... Gdyby został tutaj, byłby bezpieczniejszy. Mówię, że czasami lepiej docenić to, co się ma, niż gonić za pieniędzmi lub rangą, zapamiętaj moje słowa, sir!";
            link.l1 = "Przyjacielu, wiesz gdzie wszyscy mieszkają w kolonii, prawda?";
            link.l1.go = "DTSG_NightIskat";
			break;
        }
		//<-- Длинные тени старых грехов
		
		//--> Rebbebion, квест "Путеводная звезда"
		if (CheckAttribute(pchar, "questTemp.Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.Sotta") && !CheckAttribute(npchar, "questTemp.Lutter") && npchar.city == "Beliz")
		{
			link.l1 = "Więc bohater dnia, kapitan Edgardo Sotta. Co ludzie o nim mówią? A co ty o nim myślisz? Nie mogłem się doczekać, żeby go poznać.";
			link.l1.go = "Sotta1";
			link.l2 = "Kolego, czemu pijesz sam? Wszyscy zbierają się, żeby oglądać powieszenie Windbaga Matta.";
			link.l2.go = "Lutter1";
			break;
		}
		
		if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && !CheckAttribute(pchar, "questTemp.PZ.TortugaHabitueBlock") && npchar.city == "Tortuga")
		{
			link.l1 = "Słuchaj, kolego, próbowałem znaleźć kogoś o imieniu Joep van der Vink. Muszę mu przekazać wiadomość. Czy wiesz, jak wygląda lub cokolwiek o nim wiesz?";
			link.l1.go = "Sepp1";
			break;
		}
		//<-- квест "Путеводная звезда"
		
		//--> Тёмные воды исцеления
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "Słyszeliście? Mówią, że córka Thomasa Morrisona od pół roku nie wstaje z łóżka. Lekarze są całkowicie bezradni wobec jej choroby. Jedyną osobą, która mogłaby jej pomóc, jest cyganka słynąca z mikstur, które stawiają na nogi nawet ciężko chorych. Ale stanowczo odmówiła zrobienia czegokolwiek dla biedaczki.";
			link.l1 = RandPhraseSimple(RandSwear() + "Za to trzeba wypić jeszcze jeden kufel...",
                                 "Dobrze. Wypijmy jeszcze jeden kufel rumu.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Dziękuję, muszę się pożegnać.",
									 "Ech, mocny rum... No dobrze, pora mi już iść. Miłego wieczoru!");
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
			dialog.text = "Przedwczoraj miała miejsce zuchwała próba zamachu na naczelnika portu! Zabójca czekał na niego przy wyjściu z biura, ale zdążył wezwać pomoc. Muszkieter przybył na czas i ranił napastnika, ale przestępcy udało się uciec z miasta\nMówią, że naczelnik portu oferuje hojną nagrodę za jego głowę! Jak dotąd, żadne odważne dusze się nie zgłosiły. Wiecie co, nawet gdyby zaoferował tysiąc dubonów - nie zgodziłbym się...";
			link.l1 = RandPhraseSimple(RandSwear() + "Za to trzeba wypić jeszcze jeden kufel...",
                                 "Dobrze. Wypijmy jeszcze jeden kufel rumu.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Dziękuję, muszę się pożegnać.",
									 "Ech, mocny rum... No dobrze, pora mi już iść. Miłego wieczoru!");
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
			dialog.text = "Słyszeliście te wieści?! To istne bezprawie! Ani kropli rumu czy wina w tawernie - jak człowiek ma znaleźć ulgę w ten przeklęty upał? Karczmarz już tydzień karmi nas pustymi obietnicami, że trunek znów popłynie, ale jak dotąd nic! Czy mamy wysuszyć gardła aż do Sądu Ostatecznego?";
			link.l1 = RandPhraseSimple(RandSwear() + "Za to trzeba wypić jeszcze jeden kufel...",
                                 "Dobrze. Wypijmy jeszcze jeden kufel rumu.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Dziękuję, muszę się pożegnać.",
									 "Ech, mocny rum... No dobrze, pora mi już iść. Miłego wieczoru!");
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
			dialog.text = "Wieści krążące po dokach mówią, że nasz karczmarz ma kłopoty! Ktoś zwędził mu gin! Nie butelkę, ale całą beczkę tego trunku - takiego, którego nie znajdziesz nigdzie indziej na tych wyspach! Podobno przywieziony prosto z Europy. Stary lis nie zdradza, dla kogo go trzymał, ale jedno jest pewne: jeśli ta beczka szybko się nie odnajdzie, biedak słono za to zapłaci!";
			link.l1 = RandPhraseSimple(RandSwear() + "Za to trzeba wypić jeszcze jeden kufel...",
                                 "Dobrze. Wypijmy jeszcze jeden kufel rumu.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Dziękuję, muszę się pożegnać.",
									 "Ech, mocny rum... No dobrze, pora mi już iść. Miłego wieczoru!");
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
			dialog.text = "Wieści krążące po porcie mówią, że Julie d'Armagnac, siostrzenica gubernatora, stała się jedynie cieniem dawnej siebie. Niegdyś promieniejąca i pełna życia, teraz snuje się po ulicach z wyraźnym smutkiem wypisanym na twarzy. Mieszkańcy szepczą i zastanawiają się, co mogło ją spotkać, ale nikt nie zna prawdy. Być może jakiś niegodziwiec złamał jej serce?"+GetSexPhrase(" Może to pan był, kapitanie?","")+"";
			link.l1 = RandPhraseSimple(RandSwear() + "Za to trzeba wypić jeszcze jeden kufel...",
                                 "Dobrze. Wypijmy jeszcze jeden kufel rumu.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Dziękuję, muszę się pożegnać.",
									 "Ech, mocny rum... No dobrze, pora mi już iść. Miłego wieczoru!");
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
			dialog.text = "Krążą słuchy, że rybak Pierre Carno zniknął bez śladu. Dwa świty temu wypłynął w morze i dotąd nie ma po nim śladu. Jego żona, Lea, jest zrozpaczona. Dniem i nocą pełni wartę na molo, wpatrując się w bezkresne wody, modląc się o choćby cień żagla ukochanego.";
			link.l1 = RandPhraseSimple(RandSwear() + "Za to trzeba wypić jeszcze jeden kufel...",
                                 "Dobrze. Wypijmy jeszcze jeden kufel rumu.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Dziękuję, muszę się pożegnać.",
									 "Ech, mocny rum... No dobrze, pora mi już iść. Miłego wieczoru!");
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
			link.l1 = RandPhraseSimple(RandSwear() + "Za to trzeba wypić jeszcze jeden kufel...",
                                 "Dobrze. Wypijmy jeszcze jeden kufel rumu.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Dziękuję, muszę się pożegnać.",
									 "Ech, mocny rum... No dobrze, pora już iść. Miłego wieczoru!");
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
		
		Dialog.Text = LinkRandPhrase("Cóż... hic! ","Ah, dobry rum! ","Cóż... ")+SelectRumourEx("habitue", NPChar);
		link.l1 = RandPhraseSimple(RandSwear() + "To jest warte kolejnego kufla...",
                                 "No dobrze, napijmy się jeszcze raz.");
		link.l1.go = "sit_3";
		link.l2 = RandPhraseSimple("Dziękuję, muszę już iść.",
                                 "Eh, cholerny rum. Dobra, powinienem iść, baw się dobrze.");
		link.l2.go = "exit_sit";
	break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_trader":
            if (!CheckAttribute(NPChar, "quest.repeat.rumours_trader") || NPChar.quest.repeat.rumours_trader!= 3 )
            strum = SelectRumourEx("trader", NPChar);
            else strum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
			Dialog.Text =  NPCStringReactionRepeat(strum, strum+" Yup. Nothing more to tell.",
                strum+" Teraz powinienem wrócić do interesów.",RandPhraseSimple("Już mówiłem, że nie mam czasu na tanie gadki!","Jestem zajętym człowiekiem, nie mam czasu na plotki!"),"block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(pcharrepphrase(RandSwear() + "Interesujące! Ale przejdźmy do sedna","Dzięki, to jeszcze jedna rzecz."), pcharrepphrase(""+ GetSexPhrase("A niech mnie","Interesujące") +"! Ładny gawędziarz. Ale mam jeszcze jedno pytanie.","Nie marnujmy więcej czasu i porozmawiajmy o interesach."),
pcharrepphrase(RandSwear() +" Jeszcze jedno i pójdę.","Masz rację, czas to pieniądz."),pcharrepphrase("Zawsze myślisz tylko o swoich zyskach! Dobra, nie szalej.","Wybacz mi. Porozmawiajmy o interesach."),npchar, Dialog.CurrentNode);
			link.l1.go = "business";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Żegnaj, stary pijaku.",
"Narazie, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"."),pcharrepphrase("Karamba! Nie odchodź daleko. Wrócę wkrótce.","Miło było Cię widzieć, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"! Do widzenia!")),NPCharRepPhrase(npchar,pcharrepphrase("Odpłyń!","Żegnaj!"),pcharrepphrase("Hej! Co tam ukrywasz? Rum? Nie!?! Nieważne, pójdę po coś do picia.","Przepraszam, mam ważną sprawę do załatwienia w mieście.")),NPCharRepPhrase(npchar,pcharrepphrase("Heh! Do zobaczenia!","Powinienem iść. Narazie, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!"),pcharrepphrase("Nie ośmielaj się ze mną kłócić! Nie mam na to ochoty!","Chyba powinienem sprawdzić mój statek. Do zobaczenia, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),NPCharRepPhrase(npchar,pcharrepphrase("Co się stało, kolego? To ja - " +GetFullName(pchar)+ "! Zdrzemnij się, porozmawiamy później.","Boję się, że twoja wątroba cię zabije, zanim tu znowu przyjdę."),pcharrepphrase("Policz swoje srebro, chytry psie! Zobaczę cię później.","Miło cię widzieć, " + GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),npchar, Dialog.CurrentNode);
			link.l2.go = "Exit";
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_capitan":
			Dialog.Text = SelectRumourEx("capitan", NPChar);
			Link.l1 = RandPhraseSimple(RandSwear() + "Interesujące! Jest jeszcze jedna rzecz, o którą chcę zapytać...",
                                     "Jeszcze jedno pytanie.");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("Dziękuję, muszę już iść.",
                                     "Do widzenia.");
			Link.l2.go = "exit";
			NextDiag.TempNode = "quests";
            NPChar.talk_date =  lastspeakdate();
		break;
		
		 case "rumours_landcaptain":
			Dialog.Text = SelectRumourEx("landcaptain", NPChar);
			Link.l1 = RandPhraseSimple(RandSwear() + "Interesujące! Jest jeszcze jedna rzecz, o którą chcę zapytać...",
                                     "Jeszcze jedno pytanie.");
			Link.l1.go = "question";
			Link.l2 = RandPhraseSimple("Dziękuję, muszę już iść.",
                                     "Do widzenia.");
			Link.l2.go = "exit";
			NextDiag.TempNode = "question";
            NPChar.talk_date =  lastspeakdate();
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_tavern":  // homo 03/08/06
				if(startHeroType == 4)
				{
					Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("Znasz cenę. Informacje są jak pokój, jedzenie lub napój - kosztują. To będzie tysiąc pesos.",
					"Znasz cenę. Informacje są jak pokój, jedzenie lub napój - kosztują. To będzie tysiąc pesos.",
					"Znasz cenę. Informacje są jak pokój, jedzenie lub napój - kosztują. To będzie tysiąc pesos."),
					"Nic więcej nie do dodania. A teraz przepraszam, muszę iść.",
					"", "", "block", 1, npchar, Dialog.CurrentNode);
				 
					link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Właściwie, dlaczego w ogóle pytam? Mogę zapytać o to każdego. Przepraszam, że przeszkadzam.",
											 "Właściwie, dlaczego w ogóle pytam? Mogę zapytać o to każdego. Przepraszam, że przeszkadzam."), "", "", "", npchar, Dialog.CurrentNode);
					link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);//"rumours_tavern_no";
					NextDiag.CurrentNode = NextDiag.TempNode;
					if (makeint(pchar.money) >= 1000)
					{
						link.l2 = HeroStringReactionRepeat(RandPhraseSimple("Wiem, oczywiście. Oto moja zapłata.", "Wiem, oczywiście. Oto moja zapłata."),
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
					Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("Informacje kosztują. Za 1000 pesos powiem ci wszystko, co wiem.",
					"Coś jest nie tak z moją pamięcią. 1000 pesos mogłoby mi pomóc coś zapamiętać.",
					"Chętnie podzielę się informacjami. Ale będzie cię to kosztowało 1000 pesos. Bez targowania się."),
					"Nic więcej nie do dodania. A teraz przepraszam, muszę iść.",
					"", "", "block", 1, npchar, Dialog.CurrentNode);
				 
					link.l1 = HeroStringReactionRepeat(RandPhraseSimple(RandSwear() + "Nie będę płacić za bezwartościowe pogawędki.",
											 "Pomyślę o lepszych sposobach na wydanie tych pieniędzy."), "Zmieńmy temat.", "Zmieńmy temat.", "Zmieńmy temat.", npchar, Dialog.CurrentNode);
					link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);//"rumours_tavern_no";
					NextDiag.CurrentNode = NextDiag.TempNode;
					if (makeint(pchar.money) >= 1000 )
					{
						link.l2 = HeroStringReactionRepeat(RandPhraseSimple("Dostaniesz je, jeśli dowiem się od ciebie czegoś wartościowego.", "Zapłacę jeśli dasz mi coś wartościowego."),
						 "", "", "" , npchar, Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
					else
					{
						link.l2 =  HeroStringReactionRepeat("Nie mam takiej sumy.", "", "", "", npchar, Dialog.CurrentNode);
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
					Dialog.Text =  "Nasz patrol niedawno zniszczył brygantynę pewnego francuskiego przemytnika o nazwisku Morel. Mężczyzna siedzi teraz w lochach i grozi mu wyrok śmierci. Nasz komendant uważa, że ​​na jego statku nie było pełnego ładunku, więc nadal próbuje go znaleźć... Francuz umrze, gdy komendant znajdzie zaginiony ładunek.";
					link.l1 = "Interesujące... Dobra, weź pieniądze. Coś jeszcze?";
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
				Dialog.Text =  "W pałacu gubernatora odbyło się wielkie przyjęcie. Przyjaciel Jego Ekscelencji, Don Carlos de Milyar powrócił. Został pojmany w bitwie morskiej, ale udało mu się uciec z pomocą francuskiego porucznika. Don Carlos jest nie tylko mądry, ale także bardzo hojny. Dzięki jego wsparciu ten porucznik, Jean Deno, został teraz kapitanem „Sario”. O ile słyszałem, został również obdarowany przez małą plantację. Teraz frogeater nazywa się Juan! Cóż za historia!";
				link.l1 = "Intrygujące... Dobra, pieniądze są twoje. Weź je. Masz mi coś jeszcze do powiedzenia?";
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
				Dialog.Text =  "Nasz komendant wysłał dodatkowe siły do ​​patrolowania dżungli i zwiększył liczbę strażników w mieście. Krążą pogłoski, że Anglicy planują infiltrację Philipsburga i uwolnienie pojmanych oficerów.";
				link.l1 = "Co ty gadasz! Czy oni naprawdę mają jaja, żeby zrobić taki numer? I o jakich oficerach dokładnie mówisz?";
				link.l1.go = "FMQN_r";
				break;
			}	
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && npchar.location == "Havana_tavern")
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text =  "Pewnego dnia całe miasto było wzburzone jak gniazdo szerszeni. Oficer z wojskowego skupu upił się do nieprzytomności w mojej tawernie i prawie zgwałcił mężatkę. Następnie pobił jej męża, który próbował bronić żony, a nawet groził mu mieczem. Wyobraź sobie to wszystko na oczach straży miejskiej! Jak mawiają, prawo szanuje moc. Żołnierze po prostu się odwrócili, podczas gdy ten drań szalał\nAle łobuza rozbroili, kto by pomyślał, marynarze ze statku kupieckiego. Prawie owinęli go w kokardę, chociaż skurwiel uciekł i ukrył się na swoim statku. Komendant i Alcalde próbowali zamieść sprawę pod dywan, ale oburzony mąż jest szanowanym obywatelem, który zwrócił się do Jego Ekscelencji Don Diego de Toledo i narobił trochę hałasu wśród miejscowej szlachty\nWydali nakaz aresztowania oficera. Krążyły pogłoski, że jego kapitanowi zasugerowano opuszczenie portu z nim i przeniesienie łajdaka w inne miejsce. Jednak kapitan szkunera, Esberdo Cabanas, jest człowiekiem honoru. Gdy tylko dowiedział się, co zrobił jego oficer, natychmiast go aresztował i odesłał na brzeg. Ten drań gnije w więzieniu w przewidywalnej przyszłości, gdzie jego miejsce, jeśli mnie pytasz. A potem, być może, zostanie zdemobilizowany i wychłostany, po prostu jako przykład dla innych.";
				link.l1 = "Czekaj, powiedziałeś Kapitan Esberdo Cabanas? Huh... ekscytująca historia, rzeczywiście! Dobra, zarobiłeś swoje pieniądze, proszę bardzo. Czy mógłbyś mi jeszcze coś powiedzieć?";
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
				Dialog.Text =  "Mówią, że na jednej z niezamieszkanych wysp porzucono przestępców! Podobno są tak bezwzględnymi potworami, że ani kat, ani święci ojcowie nie odważyli się z nimi rozprawić! Ale dlaczego zawsze kończą na tym, że przywożą ich tutaj?!";
				link.l1 = "Hmm... ciekawe! Może powinienem ich wytropić i zrekrutować - zawsze potrzebuję zdesperowanych dusz... Czemu jesteś taki blady, kolego? Żartuję, żartuję... Zasłużyłeś na swoje pieniądze - proszę bardzo. Słyszałeś coś jeszcze godnego uwagi?";
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
					link.l1 = "Okazuje się, że jednak nic nie wiesz. Nie spodziewałam się, że mnie tak oszukasz. Nie za sprytne. No cóż, żegnaj.";
				}
				else
				{
					link.l1 = RandPhraseSimple("Bezwartościowe pomyje. Nie zapłacę ci ani jednego peso! Pa.", "Twoje informacje nic nie kosztują, więc nic nie otrzymasz.");
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
					link.l1 = "Naprawdę? Interesujące, dzięki. Cóż, muszę iść, do następnego razu.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = RandPhraseSimple("Dzięki, weź pieniądze. Masz coś jeszcze do powiedzenia?", "Dobra, weź pieniądze. Masz coś jeszcze do powiedzenia?");
					link.l1.go = "rumours_tavern";
				}
    			NextDiag.CurrentNode = NextDiag.TempNode;    
            }
		break;

		case "rumours_tavern_no":
			if(startHeroType == 4)
			{
				Dialog.Text = "Mogłabyś troche pomóc, sypiąc groszem. W przeciwieństwie do ciebie, Helen, nie mam Barona Bractwa, który by mnie wspierał.";
				link.l1 = "Masz cały zakład. A ja sam doszłam do tego, gdzie jestem. Cóż, oprócz statku, armat, załogi i zapasów, które dał mi Baron. Dobra, nieważne.";
				link.l1.go = "exit";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
			else
			{
				Dialog.Text = "Zrozum mnie dobrze, muszę wyżywić moją rodzinę.";
				link.l1 = "Zmieńmy temat.";
				link.l1.go = "first time";
				NextDiag.CurrentNode = NextDiag.TempNode;
				link.l2 = LinkRandPhrase("Nieważne.",
										 "Żegnam.","Do widzenia.");
				link.l2.go = "Exit";
			}
		break;	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_poor":
			if (!CheckAttribute(NPChar, "quest.repeat.rumours_poor") || NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("poor", NPChar);
				Link.l1 = RandPhraseSimple(RandSwear() + "Interesujące. Jeszcze jedno pytanie...",
										"Hm, pozwól, że zapytam o coś jeszcze...");
				Link.l1.go = "rumours_poor_2";
				Link.l2 = RandPhraseSimple("Cóż, do widzenia.",
										"Narazie, kolego");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple("Powiedziałem ci wszystko, co wiedziałem.", 
					"Niestety nie mam nic więcej do przekazania...");
				Link.l1 = RandPhraseSimple("Rozumiem, do widzenia.",
										"Zrozumiano. Żegnaj, kolego...");
				Link.l1.go = "exit";			
			}
            NPChar.talk_date = lastspeakdate();
		break;
        case "rumours_poor_2":
			if (NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("poor", NPChar);
				Link.l1 = RandPhraseSimple(RandSwear() + "Interesujące. Jeszcze jedno pytanie...",
										"Hm, pozwól, że zapytam o coś jeszcze...");
				Link.l1.go = "rumours_poor";
				Link.l2 = RandPhraseSimple("Well, farewell.",
										"Narazie, kolego.");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple("Powiedziałem ci wszystko, co wiedziałem.", 
					"Niestety nie mam nic więcej do przekazania...");
				Link.l1 = RandPhraseSimple("Rozumiem, do widzenia.",
										"Zrozumiano. Żegnaj, kolego...");
				Link.l1.go = "exit";			
			}
			NPChar.talk_date = lastspeakdate();
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_LSC":
			if (CheckNPCQuestDate(NPChar, "quest.repeat.rumours"))
			{
				Dialog.Text = SelectRumourExSpecial("LSC", NPChar);
				Link.l1 = RandPhraseSimple("Rozumiem...",
										"Rozumiem...");
				Link.l1.go = "exit";
				SetNPCQuestDate(NPChar, "quest.repeat.rumours");
			}
			else  
			{
				Dialog.Text = NPCharSexPhrase(npchar, RandPhraseSimple("Powiedziałem ci wszystko, co wiedziałem.", "Nie słyszałem nic nowego, przepraszam..."), 
					RandPhraseSimple("Powiedziałem ci wszystko, co wiedziałem.", "Nie słyszałem nic nowego, przepraszam..."));
				Link.l1 = RandPhraseSimple("Rozumiem, zatem do widzenia.", "Zrozumiano. Żegnaj, kolego.");
				Link.l1.go = "exit";			
			}
		break;
		
//Jason -------------слухи смотрителей маяков, идентичны таверне, но бесплатны, по 1 шт за день--------------------
		case "rumours_lighthouse": 
			Dialog.Text = NPCStringReactionRepeat(RandPhraseSimple("Ech, kapitanie! Zawsze miło z tobą pogawędzić. Bycie tu samemu jest czasami dość nudne...", "Mieszkam sam, a goście zdarzają się rzadko. Więc zawsze mam ochotę na rozmowę."), "Lubisz rozmawiać, kapitanie? Cóż, może mam coś jeszcze do powiedzenia...", "Weź butelkę rumu następnym razem, gdy mnie odwiedzisz. Rozmowy są lepsze przy drinkach...", "Niestety, powiedziałem ci wszystko, co wiedziałem. Nie mam nic do dodania.", "block", 1, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("To podziel się swoimi informacjami. Lubię rozmawiać z ludźmi, wiesz...", "Powiedz mi! Jak mówią, kto jest włada informacjami - włada światem."), "Na przykład co?", "Oczywiście! Masz coś jeszcze do przekazania?", "No cóż, w każdym razie miło nam się rozmawiało." , npchar, Dialog.CurrentNode);
    		link.l1.go = HeroStringReactionRepeat("rumours_lighthouse_yes", "rumours_lighthouse_void", "rumours_lighthouse_void", "exit", npchar, Dialog.CurrentNode);
		break;
		
		case "rumours_lighthouse_yes":
            RumText = SelectRumourEx("tavern", NPChar);
		    if(!RumourHasInformation(RumText))
            {
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
                link.l1 = RandPhraseSimple("Dziękuję! Coś jeszcze?", "Bardzo interesujące! Coś jeszcze?");

			    link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("Dzięki! To było całkiem zabawne...", "Dziękuję, że mi powiedziałeś!");
			    link.l2.go = "exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
            }
            else
            {
                Dialog.Text = RumText;
    			link.l1 = RandPhraseSimple("Dziękuję! Coś jeszcze?", "Bardzo interesujące! Coś jeszcze?");
    			link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("Dzięki! To było całkiem zabawne...", "Dziękuję, że mi powiedziałeś!");
			    link.l2.go = "exit";
    			NextDiag.CurrentNode = NextDiag.TempNode;    
            }
		break;
		
		case "rumours_lighthouse_void":
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
                link.l1 = RandPhraseSimple("Dziękuję! Coś jeszcze?", "Bardzo interesujące! Coś jeszcze?");

			    link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("Dzięki! To było całkiem zabawne...", "Dziękuję, że mi powiedziałeś!");
			    link.l2.go = "exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
		break;
//Jason ------------------------------------почтовый генератор 2 уровня-------------------------------------------
		 case "Postcureer_LevelUp_ForAll":
			//начинаем проверять
			if (!CheckCharacterItem(pchar, pchar.questTemp.WPU.Current.Item))
			{
				dialog.text = "Ale gdzie jest paczka? Nie masz jej?";
	        	link.l1 = "Cóż... Miałem ci to dostarczyć. Ale... szczerze mówiąc, zostało mi to odebrane. Nie mogłem się bronić i sam dałem tym napastnikom paczkę. ";
	        	link.l1.go = "Postcureer_LevelUp_complete_fail";
				break;
			}
			
			if (sti(pchar.questTemp.WPU.Postcureer.AgentChance) == 4)//раскрыли обман
			{
				dialog.text = "Hm. Przepraszam, ale paczka była już wcześniej otwierana! Pieczęć została ponownie ostemplowana...";
	        	link.l1 = "" + GetAddress_FormToNPC(NPChar) + ", to jest paczka, którą dostałem w administracji portowej " +XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+ ", więc nie mam pojęcia...";
	        	link.l1.go = "Postcureer_LevelUp_complete_Agentfail";
				break;
			}
			
			if (pchar.questTemp.WPU.Postcureer == "late")//опоздали
			{
				int iTime = makeint(GetQuestPastDayParam("questTemp.Postcureer.Late"))+1;
				pchar.questTemp.WPU.Postcureer.Money = makeint(sti(pchar.questTemp.WPU.Postcureer.Money)/(sti(iTime)+1));//сильно снижаем оплату
				dialog.text = "Czekałem na ciebie. Jesteś spóźniony o " + FindRussianDaysString(iTime)+ " dni! Informacje, które nosisz, stały się o wiele mniej przydatne... Oczywiście nadal mają jakąś wartość, więc zapłacę ci " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + ". Proszę wziąć pieniądze i do widzenia.";
	        	link.l1 = "Dzięki. Chyba.";
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
				dialog.text = "Więc to ty! Czekałem na ciebie dość długo, nawet podjąłem kroki, aby odzyskać paczkę. Daj mi ją. Teraz jej naprawdę nie potrzebuję, dzięki twojemu wyczuciu czasu, ale chciałbym ją zatrzymać dla siebie\nJak rozumiesz, nie mogę ci nic zapłacić, ale upewnię się, że twoje dobre imię zostanie przywrócone.";
	        	link.l1 = "Dzięki... Chyba. Przepraszam za opóźnienie, naprawdę. Żegnam.";
	        	link.l1.go = "Postcureer_LevelUp_complete_bad";
				break;
			}
			dialog.text = "Czekałem na ciebie. Jesteś w samą porę, informacje, które mi przyniosłeś, będą niezwykle przydatne. Proszę, przyjmij te pieniądze za swoją pracę - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + ". Dziękuję za poświęcony czas.";
        	link.l1 = "Proszę bardzo. Do widzenia!";
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
			dialog.text = "Ech, wiedziałem, że tak się to skończy... Powinienem był wynająć wojskowy statek kurierski, a nie cywilnego kapitana... nieważne, " + GetAddress_Form(NPChar) + ", nie jesteś żołnierzem, więc nie ma za co cię obwiniać. Żegnaj.";
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
			dialog.text = "Panie, znam nadzorce portu " +XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+ " osobiście. Jest uczciwym człowiekiem. Poza tym nie było sensu, żeby otwierał paczkę. " + GetAddress_Form(NPChar) + ", jesteś oszustem! Nie zapłacę ci ani jednego miedziaka. Spieprzaj!";
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
			dialog.text = "Wyglądał jak chodzące śmieci. Włóczęga albo żebrak. Nie potrafię powiedzieć, dokąd dokładnie poszedł, nie zależało mi na tym, żeby za nim pójść.";
			link.l1 = "Lepsze to niż nic. Dziękuję! Powinienem iść.";
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
			Dialog.Text =  "Niedawno angielski statek został schwytany na wodach Sint-Maarten, na pokładzie znajdowało się kilku wysoko postawionych oficerów. Postanowiono wysłać ich do Willemstad, ale w tej chwili są przetrzymywani tutaj, w naszych wygodnych lochach. Mówią, że jeden ze schwytanych żołnierzy powiedział naszemu komendantowi o zamiarze Anglików wysłania tutaj oddziału łupieżczego w celu uratowania oficerów. Dlatego nasz dobry stary komendant jest gotowy i uzbrojony. Dlaczego nie miałby być, jeśli więźniowie znikną, zostanie zdegradowany do szeregowego żołnierza!";
			link.l1 = "Intrygujące... Dobra, pieniądze są twoje. Weź to. Masz mi coś jeszcze do powiedzenia?";
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
            Dialog.Text = RandPhraseSimple("Bardzo dobrze. Mam tu paczkę gotową do dostarczenia. Weź ją\nNie przychodź tu i nie rozmawiaj ze mną więcej, to zbyt niebezpieczne. Uważaj tam na siebie...", 
				"Hm, świetnie. Weź paczkę i upewnij się, że dostarczysz ją mężczyźnie, o którym właśnie rozmawialiśmy\nŻegnaj i nie rozmawiaj ze mną więcej, to zbyt niebezpieczne.");
            link.l1 = RandPhraseSimple("Zrozumiano. Do widzenia...", "Żegnaj i powodzenia.");
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
       /* case "Man_FackYou":
			dialog.text = LinkRandPhrase("Kradzież w środku dnia!!! Naprawdę?! Zostań tam, gdzie jesteś, kolego...", "Hej, co tam robisz?! Wygląda na to, że ktoś zamierzał mnie okraść. Jesteś skończony...", "Czekaj, co ty robisz? Złodziej! Koniec drogi, kolego...");
			link.l1 = LinkRandPhrase("O w morde! Pora na mnie", "Karamba! Czas spierdalać!", "Cholera! Nie przemyślałem tego.");
			link.l1.go = "fight_owner";
		break;
		case "fight_owner":
			LAi_SetOwnerTypeNoGroup(NPChar);
			LAi_group_Attack(NPChar, Pchar);
			if (rand(3) != 1) SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
			NextDiag.CurrentNode = "First time";
			DialogExit();
		break; */
	}
}

string sRumourAboutOwners_CityRumour(string sCity, string sOwnerType) // Здесь идёт распределение по городам
{
	string sRetRumour = "Coś się popsuło, poinformuj twórców.";
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
	STR_MAYOR[0] = "Och, gubernator jest doskonałym człowiekiem. Zarządza naszą kolonią z wielką umiejętnością, nigdy nie miał ani jednego konfliktu od dnia założenia\nJego jedyną wadą jest... on jest... cóż... on jest dość oszczędny. Może to być jednak kolejna zaleta.";
	STR_MAYOR[1] = "Och, gubernator jest doskonałym człowiekiem. Zarządza naszą kolonią z wielką umiejętnością, nigdy nie miał ani jednego konfliktu od dnia założenia\nJego jedyną wadą jest... on jest... cóż... on jest dość oszczędny. Może to być jednak kolejna zaleta.";
	STR_MAYOR[2] = "Nasz gubernator jest dobrym człowiekiem, ale ma słaby charakter. Gdyby miał odrobinę stanowczości w duszy, nasi kupcy mogliby dostać małe ulgi podatkowe... I już czas przydzielić dotacje na naprawę fortu.";
	STR_MAYOR[3] = "Hmm... Niedawno został naszym gubernatorem. Jest dość młody, a więc bardzo inicjatywny. Z nim nasza kolonia rozkwita.";
	STR_MAYOR[4] = "Nasz gubernator jest wciąż stosunkowo młody. Mówią, że jest nic niewartym młodszym synem hiszpańskiego hrabiego, wysłanym daleko od podwórza, by przestać zawstydzać swoją rodzinę. Został tu mianowany całkiem niedawno i nie miał czasu, by stworzyć coś pamiętnego.";
	STR_MAYOR[5] = "Hmm... Niedawno został naszym gubernatorem. Jest dość młody, a więc bardzo inicjatywny. Z nim nasza kolonia rozkwita";
	STR_MAYOR[6] = "No cóż... Nic... Nie mogę powiedzieć o nim nic złego...";
	
	string STR_TAVERNKEEPER[MAX_RUMOURS_ABOUT_OWNERS]; // Тавернщики
	STR_TAVERNKEEPER[0] = "Hm, nie powierzyłbym swojej własności temu łobuzowi. Nie zrozum mnie źle, ale wydaje mi się, że to najbardziej niegodna zaufania osoba w naszym mieście\nSłyszałem, że współpracuje z piratami i przemytnikami, których często można zobaczyć w jego tawernie.";
	STR_TAVERNKEEPER[1] = "Cóż można o nim powiedzieć! Tchórzliwy, nie jest też najmądrzejszą osobą, jaką znam. Poza tym jest pazerny na pieniądze, dlatego ciągle wpada w różne tarapaty! Ale zawsze jest na bieżąco ze wszystkimi nowinkami.";
	STR_TAVERNKEEPER[2] = "Całkiem przyjemny facet. Zawsze miło jest spędzać czas w jego karczmie, ma też świetne poczucie humoru. Najważniejsze w nim jest to, że utrzymuje tawernę w porządku i nie pozwala pijanym łajdakom napadać na dobrych obywateli.";
	STR_TAVERNKEEPER[3] = "Niesamowity człowiek. Nie powinien prowadzić karczmy, ale być informatorem dla wywiadu. Czasami wydaje się, że wie dosłownie wszystko, co dzieje się w naszym mieście. To mnie nawet przeraża.";
	STR_TAVERNKEEPER[4] = "Nie wiem, co ci powiedzieć. Mężczyzna. Prowadzi karczmę. Wie wszystko o mieście i jego mieszkańcach.";
	STR_TAVERNKEEPER[5] = "Mówią, że można na nim polegać. Z drugiej strony słyszałem, że nie lubi niepotrzebnego ryzyka i zawsze jest ostrożny w prowadzeniu interesów. Tak, a ciemne sprawy to nie jest jego typ biznesu.";
	STR_TAVERNKEEPER[6] = "Karczmę ma po ojcu. Jego ojciec prowadził karczmę niedaleko stąd, na wyspie Highrock na innym archipelagu. Potem jego ojciec przeprowadził się tutaj, zbudował nową karczmę, a teraz prowadzi ją jego syn.";
	
	string STR_SHIPYARDER[MAX_RUMOURS_ABOUT_OWNERS]; // Верфисты
	STR_SHIPYARDER[0] = "Buduje statki. Nie wiem. Jest cichy i spokojny. Chyba jest dobrym człowiekiem.";
	STR_SHIPYARDER[1] = "Buduje statki. Nie wiem. Jest cichy i spokojny. Chyba jest dobrym człowiekiem.";
	STR_SHIPYARDER[2] = "Dobry człowiek, ale mówią, że jest zbyt surowy. Ciągle łaje wszystkich pracowników. Dlatego często odchodzą. Mimo to jest znakomitym stoczniowcem.";
	STR_SHIPYARDER[3] = "Jest bardzo wykształconą osobą. Słyszałem, że studiował budowę statków w Anglii, potem w Holandii. A na końcu trafił tutaj - daleko od metropolii, na prowincjonalnym archipelagu\nLudzie mówią, że miał kłopoty ze Świętą Inkwizycją i musiał uciekać do kolonii.";
	STR_SHIPYARDER[4] = "Ten starzec musi już iść na emeryturę i dać drogę świeżej krwi. Ciągle śni o minionych czasach i narzeka, gdy ktoś zamawia u niego coś poza karawelami i galeonami.";
	STR_SHIPYARDER[5] = "Świetny chłopak. Zawsze chętny do pomocy. Muszę przyznać, że buduje świetne statki na taką dziurę jak ta.";
	STR_SHIPYARDER[6] = "Był więźniem, wygnanym z Europy do naszej kolonii, dopóki nie okazało się, że ma talent do budowy statków. Po tym, jak pod jego kierownictwem zbudowano dwa wspaniałe brygi w stoczni naszej kolonii, wybaczono mu jego występki i teraz jest pełnoprawnym członkiem naszego społeczeństwa.";
	
	string STR_TRADER[MAX_RUMOURS_ABOUT_OWNERS]; // Магазинщики
	STR_TRADER[0] = "Nie mogę powiedzieć o nim nic złego. Porządny obywatel, często odwiedza naszą kaplicę. Ludzie wydają się go lubić. Nigdy nie słyszałem, żeby ktoś był na niego zły.";
	STR_TRADER[1] = "Jest głównym dostawcą naszego gubernatora, a to daje mu dobry dochód. Ale prowadzi swoje sprawy uczciwie. Cóż, przynajmniej nie został zauważony w niczym, co by go zawstydziło.";
	STR_TRADER[2] = "Ten grubas ma wielki szacunek w naszym mieście. Jego towary są zawsze doskonałe i nie przypominam sobie ani jednego przypadku, żeby kogoś oszukał.";
	STR_TRADER[3] = "On jest do niczego, naprawdę. Handluje, ale bez sensu. Czasem jednego towaru nie ma na stanie, czasem innego, czasem połowy towaru... Nawet nie potrafi wyjść z długów.";
	STR_TRADER[4] = "On nie jest dobrym człowiekiem, monsieur. Słyszałem, że był prawą ręką Pierre Thiersa, poprzedniego handlarza, zrujnował jego interes, a potem kupił sklep. Nie wiem, jak z jakością towarów, które sprzedaje, ale jako osoba jest dla mnie bardzo nieprzyjemny.";
	STR_TRADER[5] = "Och! To paskudny człowiek, nie radziłbym ci robić z nim interesów\nTrzyma połowę mieszkańców naszego miasta w długach! A towary, które są sprzedawane w jego sklepie, są zawsze kiepskiej jakości.";
	STR_TRADER[6] = "Nikt tak naprawdę nic o nim nie wie. Niedawno się tu przeprowadził i od razu otworzył swój biznes. Handluje szczerze, nie został złapany na przemycie.";
	
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
