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
			dialog.text = "Hallottad? Azt mondják, Thomas Morrison lánya már hat hónapja ágyhoz van kötve. Az orvosok teljesen tehetetlenek a betegségével szemben. Az egyetlen, aki segíthet rajta, az a cigányasszony, aki a súlyos betegeket is meggyógyító bájitalairól ismert. Ám a nô határozottan elutasítja, hogy bármit is tegyen a szegény lányért.";
			link.l1 = "Köszönöm, most mennem kell.";
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
			dialog.text = "Két nappal ezelôtt szemtelen merényletet követtek el a kikötôi fônök ellen! A merénylô az irodája ajtajánál leselkedett, de a fônöknek sikerült segítségért kiáltania. Egy muskétás sietve érkezett, és megsebesítette a gazembert, bár a gazembernek sikerült elmenekülnie a város kapuján\nAz a hír járja, hogy a kikötôi fônök szép vérdíjat tûzött ki a gazember fejére! Eddig még nem jelentkeztek elég bátor lelkek.";
			link.l1 = "Köszönöm, most mennem kell.";
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
			dialog.text = "Hallottad a híreket?! Ez egy véres felháborodás! Egy csepp rum vagy bor sem maradt a kocsmában - hogyan is találhatna egy test enyhülést ebben az átkozott hôségben? A fogadós egy hete üres ígéretekkel etet minket, hogy az ital újra folyni fog, de semmi sem történt! Azt várják tôlünk, hogy az Ítélet Napjáig pergessük a torkunkat?";
			link.l1 = "Köszönöm, most mennem kell.";
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
			dialog.text = "A kikötôben az a hír járja, hogy Julie d'Armagnac, a kormányzó unokahúga már csak árnyéka önmagának. Egykor ragyogó és élettel teli volt, most azonban összetéveszthetetlen szomorúsággal az arcán kóborol az utcákon. A városlakók suttognak és azon tûnôdnek, mi történhetett vele, de senki sem tudja az igazságot. Talán egy gazember törte össze a szívét?"+GetSexPhrase(" Talán te voltál az, kapitány?","")+"";
			link.l1 = ""+GetSexPhrase("Kétlem, hogy ","")+". Köszönöm, most mennem kell.";
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
			dialog.text = "Azt beszélik, hogy Pierre Carno halász nyomtalanul eltûnt. Két hajnalban elhajózott a kékbe, és azóta semmi nyoma. A felesége, Lea, magán kívül van a bánattól. Nappal és lámpafénynél is virraszt a mólónál, tekintetét a végtelen vízre szegezve, imádkozik, hogy megpillantsa szerelme vitorláját.";
			link.l1 = "Köszönöm, most mennem kell.";
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
			dialog.text = "Kapitány, hallottad? Új pincérnô dolgozik a kocsmánkban. Azt mondják, nagyon szép. A férfiak mindenhonnan rohannak be, csak hogy megpillanthassák. De három nappal ezelôtt nem jelent meg a munkában, ami nagyon felzaklatta a kocsmárost, aki az érkezése óta hatalmas nyereséget termelt. Állítólag még fizetni is hajlandó annak, aki megtalálja a lányt.";
			link.l1 = "Köszönöm, most mennem kell.";
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
		//--> Оковы азарта
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OZ_Start") && npchar.city == "PortSpein" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OZ_Start") && npchar.city == "PortSpein";
		if (bOk1 || bOk2)
        {
			dialog.text = "Hallotta? A mi kovácsunk kártyán elvesztett mindent Javier Castillo ellen, úgy, hogy az teljesen kifosztotta, és rákényszerítette, hogy valami nagyon értékeset tegyen fel. Azóta a kovács sehogy sem tud magához térni, és nem vállal új megrendeléseket – csak azon bánkódik, hogy az admirális három bőrt lehúz róla. Kár ezért a jámbor emberért, minden helybéli tudja, hogy ezzel a csaló Castillo-val nem szabad játszani!";
			link.l1 = "Köszönöm, most "+ GetSexPhrase("távoznom kell","távoznom kell") +".";
			link.l1.go = "exit";
			
			SetQuestHeader("OZ");
			AddQuestRecord("OZ", "1");
			pchar.questTemp.OZ_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("OZ_Blacksmith", "blacksmith_18", "man", "man", 5, SPAIN, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_31");
			sld.lastname = StringFromKey("Neutral_32");
			sld.City = "PortSpein";
			ChangeCharacterAddressGroup(sld, "PortSpein_town", "quest", "quest3");
			sld.dialog.filename = "Quest\MiniEvents\OkoviAzarta_dialog.c";
			sld.dialog.currentnode = "OZ_Kuznets_1";
			LAi_SetStayType(sld);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Оковы азарта
		//--> Письмо от покойника
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		if (bOk1 || bOk2)
        {
			dialog.text = "Hallotta? Az 'Águila' nevű flöjt kapitánya olyan patáliát csapott a fogadóban a hadnagyának, hogy a falak is beleremegtek! Kiderült, hogy a kapitány dagálykor akart kifutni a tengerre, de a hadnagy az egész legénységet partra engedte. Most a matrózok szétszéledtek a városban, és ha nem térnek vissza időben, a hajó nélkülük fog elindulni – a kapitány nem szándékozik várni! Vajon miért ez a nagy sietség? Jó fuvardíj, előnyös üzlet, sürgős megbízás a kormányzótól?";
			link.l1 = "Köszönöm, most "+ GetSexPhrase("távoznom kell","távoznom kell") +".";
			link.l1.go = "exit";
			
			SetQuestHeader("LFD");
			AddQuestRecord("LFD", "1");
			pchar.questTemp.LFD_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("LFD_sailor", "citiz_33", "man", "man", 10, SPAIN, -1, true, "citizen"));
			ChangeCharacterAddressGroup(sld, "PortoBello_town", "goto", LAi_FindFarLocator2Pchar("goto"));
			sld.dialog.filename = "Quest\MiniEvents\LetterFromDeadman_dialog.c";
			sld.dialog.currentnode = "Sailor_1";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			//LAi_SetLoginTime(sld, 07.00, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Письмо от покойника

		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2 )
        srum = SelectRumourEx("towngirl", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        string posrep1, posrep2, answ1, answ2, answ3, answ4;
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" Ennyi...", " Talán érdekes lehet.");
            posrep2 = " Hé, kapitány, van valami híred a kolóniánknak, amit el tudsz mondani?";
            answ1 = RandPhraseSimple(RandSwear() + "Ez nagyon érdekes, "+GetFullName(NPChar)+".",
                                 "Akkor mesélj nekem...");
            answ2 = RandPhraseSimple(RandSwear() + "Érdekes! Még egy kérdést szeretnék feltenni...","Még egy kérdés.");
            answ3 = RandPhraseSimple("Nos, bármi megtörténhet. Sajnálom, de nincs semmi különös mondanivalóm. ","Eléggé sietek, úgyhogy talán majd legközelebb.");
            answ4 = "";
        }
        else
        {
            posrep1 = " Elég unalmas hely ez itt. Szóval ha valami történik, akkor mindenki beszélni fog róla.";
            posrep2 = " Semmi érdekes. Talán a " + GetAddress_Form(NPChar) + " tudhat valamit?";
            answ1 = RandPhraseSimple("Akkor mesélj nekem...",RandSwear() + "Nem tudsz semmit! Rendben, másik téma...");
            answ2 = RandPhraseSimple("Mindegy, csak mondj valami mást...","Igen, nem sokat segítettél, van még valami, amit meg akarsz osztani velem?");
            answ3 = RandPhraseSimple("Kétlem, hogy bármi érdekeset tudnék mondani.","Örömömre szolgál, de beszéljünk legközelebb.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("Sajnos, nincs több mondanivalóm, hadd menjek tovább.","Elég volt a kérdéseidbôl, bocsáss meg, sok más dolgom van."),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
                                            answ2,
                                            answ3,
                                            answ4,
                                            npchar, Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple("Köszönöm, mennem kell.","Búcsú.");
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
			dialog.text = "Hallottad? Azt mondják, Thomas Morrison lánya már hat hónapja ágyhoz van kötve. Az orvosok teljesen tehetetlenek a betegségével szemben. Az egyetlen, aki segíthet rajta, az a cigányasszony, aki a súlyos betegeket is meggyógyító bájitalairól ismert. Ám a nô határozottan elutasítja, hogy bármit is tegyen a szegény lányért.";
			link.l1 = "Köszönöm, most mennem kell.";
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
			dialog.text = "Két nappal ezelôtt szemtelen merényletet követtek el a kikötôi fônök ellen! A merénylô az irodája ajtajánál leselkedett, de a fônöknek sikerült segítségért kiáltania. Egy muskétás sietve érkezett, és megsebesítette a gazembert, bár a gazembernek sikerült elmenekülnie a város kapuján\nAz a hír járja, hogy a kikötôi fônök szép vérdíjat tûzött ki a gazember fejére! Eddig még nem jelentkeztek elég bátor lelkek. Jól jegyezd meg, még ezer dublonnáért sem kockáztatnám a nyakamat...";
			link.l1 = "Köszönöm, most mennem kell.";
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
			dialog.text = "Hallottad a híreket?! Ez egy véres felháborodás! Egy csepp rum vagy bor sem maradt a kocsmában - hogyan is találhatna egy test enyhülést ebben az átkozott hôségben? A fogadós egy hete üres ígéretekkel etet minket, hogy az ital újra folyni fog, de semmi sem történt! Azt várják tôlünk, hogy az Ítélet Napjáig pergessük a torkunkat?";
			link.l1 = "Köszönöm, most mennem kell.";
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
			dialog.text = "A kikötôben az a hír járja, hogy Julie d'Armagnac, a kormányzó unokahúga már csak árnyéka önmagának. Egykor ragyogó és élettel teli volt, most azonban összetéveszthetetlen szomorúsággal az arcán kóborol az utcákon. A városlakók suttognak és azon tûnôdnek, mi történhetett vele, de senki sem tudja az igazságot. Talán egy gazember törte össze a szívét?"+GetSexPhrase(" Talán te voltál az, kapitány?","")+"";
			link.l1 = ""+GetSexPhrase("Kétlem, hogy ","")+". Köszönöm, most mennem kell.";
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
			dialog.text = "Azt beszélik, hogy Pierre Carno halász nyomtalanul eltûnt. Két hajnalban elhajózott a kékbe, és azóta semmi nyoma. A felesége, Lea, magán kívül van a bánattól. Nappal és lámpafénynél is virraszt a mólónál, tekintetét a végtelen vízre szegezve, imádkozik, hogy megpillantsa szerelme vitorláját.";
			link.l1 = "Köszönöm, most mennem kell.";
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
			dialog.text = "Kapitány, hallottad? Új pincérnô dolgozik a kocsmánkban. Azt mondják, nagyon szép. A férfiak mindenhonnan rohannak be, csak hogy megpillanthassák. De három nappal ezelôtt nem jelent meg a munkában, ami nagyon felzaklatta a kocsmárost, aki az érkezése óta hatalmas nyereséget termelt. Állítólag még fizetni is hajlandó annak, aki megtalálja a lányt.";
			link.l1 = "Köszönöm, most mennem kell.";
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
		//--> Оковы азарта
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OZ_Start") && npchar.city == "PortSpein" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OZ_Start") && npchar.city == "PortSpein";
		if (bOk1 || bOk2)
        {
			dialog.text = "Hallotta? A mi kovácsunk kártyán elvesztett mindent Javier Castillo ellen, úgy, hogy az teljesen kifosztotta, és rákényszerítette, hogy valami nagyon értékeset tegyen fel. Azóta a kovács sehogy sem tud magához térni, és nem vállal új megrendeléseket – csak azon bánkódik, hogy az admirális három bőrt lehúz róla. Kár ezért a jámbor emberért, minden helybéli tudja, hogy ezzel a csaló Castillo-val nem szabad játszani!";
			link.l1 = "Köszönöm, most "+ GetSexPhrase("távoznom kell","távoznom kell") +".";
			link.l1.go = "exit";
			
			SetQuestHeader("OZ");
			AddQuestRecord("OZ", "1");
			pchar.questTemp.OZ_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("OZ_Blacksmith", "blacksmith_18", "man", "man", 5, SPAIN, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_31");
			sld.lastname = StringFromKey("Neutral_32");
			sld.City = "PortSpein";
			ChangeCharacterAddressGroup(sld, "PortSpein_town", "quest", "quest3");
			sld.dialog.filename = "Quest\MiniEvents\OkoviAzarta_dialog.c";
			sld.dialog.currentnode = "OZ_Kuznets_1";
			LAi_SetStayType(sld);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Оковы азарта
		//--> Письмо от покойника
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		if (bOk1 || bOk2)
        {
			dialog.text = "Hallotta? Az 'Águila' nevű flöjt kapitánya olyan patáliát csapott a fogadóban a hadnagyának, hogy a falak is beleremegtek! Kiderült, hogy a kapitány dagálykor akart kifutni a tengerre, de a hadnagy az egész legénységet partra engedte. Most a matrózok szétszéledtek a városban, és ha nem térnek vissza időben, a hajó nélkülük fog elindulni – a kapitány nem szándékozik várni! Vajon miért ez a nagy sietség? Jó fuvardíj, előnyös üzlet, sürgős megbízás a kormányzótól?";
			link.l1 = "Köszönöm, most "+ GetSexPhrase("távoznom kell","távoznom kell") +".";
			link.l1.go = "exit";
			
			SetQuestHeader("LFD");
			AddQuestRecord("LFD", "1");
			pchar.questTemp.LFD_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("LFD_sailor", "citiz_33", "man", "man", 10, SPAIN, -1, true, "citizen"));
			ChangeCharacterAddressGroup(sld, "PortoBello_town", "goto", LAi_FindFarLocator2Pchar("goto"));
			sld.dialog.filename = "Quest\MiniEvents\LetterFromDeadman_dialog.c";
			sld.dialog.currentnode = "Sailor_1";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			//LAi_SetLoginTime(sld, 07.00, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Письмо от покойника

		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2 )
        srum = SelectRumourEx("townman", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" Ennyi...", " Talán érdekes lehet.");
            posrep2 = " Hé, kapitány, van valami híred a kolóniánknak, amit el tudsz mondani?";
            answ1 = RandPhraseSimple(RandSwear() + "Ez nagyon érdekes, "+GetFullName(NPChar)+".",
                                 "Akkor mesélj nekem...");
            answ2 = RandPhraseSimple(RandSwear() + "Érdekes! Még egy kérdést szeretnék feltenni...","Még egy kérdés.");
            answ3 = RandPhraseSimple("Nos, a mi világunkban minden megtörténhet. Sajnálom, de nincs semmi különös mondanivalóm. ","Eléggé sietek, úgyhogy talán majd legközelebb.");
            answ4 = "";
        }
        else
        {
            posrep1 = " Elég unalmas hely ez itt. Szóval ha valami történik, akkor mindenki beszélni fog róla.";
            posrep2 = " Semmi érdekes. Talán a " + GetAddress_Form(NPChar) + " tudhat valamit?";
            answ1 = RandPhraseSimple("Akkor mesélj nekem...",RandSwear() + "Nem tudsz semmit! Rendben, másik téma...");
            answ2 = RandPhraseSimple("Mindegy, csak mondj valami mást...","Igen, nem sokat segítettél, van még valami, amit meg akarsz osztani velem?");
            answ3 = RandPhraseSimple("Kétlem, hogy bármi érdekeset tudnék mondani.","Örömömre szolgál, de beszéljünk legközelebb.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("Sajnos, nincs több mondanivalóm, hadd menjek tovább.","Elég volt a kérdéseidbôl, bocsáss meg, sok más dolgom van."),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
                                            answ2,
                                            answ3,
                                            answ4,
                                            npchar, Dialog.CurrentNode);
		link.l1.go = "new question";
		link.l2 = RandPhraseSimple("Köszönöm, mennem kell.","Búcsú.");
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
            posrep1 = RandPhraseSimple(" Ennyi...", " Talán érdekes lehet.");
            posrep2 = " Hé, kapitány, van valami híred a kolóniánknak, amit el tudsz mondani?";
            answ1 = RandPhraseSimple(RandSwear() + "Ez nagyon érdekes, "+GetFullName(NPChar)+".",
                                 "Akkor mesélj nekem...");
            answ2 = RandPhraseSimple(RandSwear() + "Mindegy, csak mondj valami mást...","Igen, nem sokat segítettél, van még valami, amit meg akarsz osztani velem?");
            answ3 = RandPhraseSimple("Nos, a mi világunkban minden megtörténhet. Sajnálom, de nincs semmi különös mondanivalóm. ","Eléggé sietek, úgyhogy talán majd legközelebb.");
            answ4 = "";
        }
        else
        {
            posrep1 = " Elég unalmas hely ez itt. Szóval ha valami történik, akkor mindenki beszélni fog róla.";
            posrep2 = " Semmi érdekes. Talán a " + GetAddress_Form(NPChar) + " tudhat valamit?";
            answ1 = RandPhraseSimple("Akkor mesélj nekem...",RandSwear() + "Nem tudsz semmit! Rendben, másik téma...");
            answ2 = RandPhraseSimple("Mindegy, csak mondj valami mást...","Igen, nem sokat segítettél, van még valami, amit meg akarsz osztani velem?");
            answ3 = RandPhraseSimple("Kétlem, hogy bármi érdekeset tudnék mondani.","Örömömre szolgál, de beszéljünk legközelebb.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("Sajnos, nincs több mondanivalóm, hadd menjek tovább.","Elég volt a kérdéseidbôl, bocsáss meg, sok más dolgom van."),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Köszönöm, mennem kell.","Búcsú.");
		link.l2.go = "exit";
	break;
	
/////////////////////////////////////////////////---слухи дворян---////////////////////////////////////////////
	case "rumours_nobleman":	
        srum = SelectRumourEx("nobleman", NPChar);
		//--> Украденное воспоминание
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.UV_Start") && npchar.city == "PortPax" && sti(pchar.rank) >= 1 && sti(pchar.reputation.nobility) > 40;
			if (bOk1 || bOk2){
				
			dialog.text = "A kikötôben az a hír járja, hogy Julie d'Armagnac, a kormányzó unokahúga már csak árnyéka önmagának. Egykor ragyogó és élettel teli volt, most azonban összetéveszthetetlen szomorúsággal az arcán kóborol az utcákon. A városlakók suttognak és azon tûnôdnek, mi történhetett vele, de senki sem tudja az igazságot. Talán egy gazember törte össze a szívét?"+GetSexPhrase(" Talán te voltál az, kapitány?","")+"";
			link.l1 = ""+GetSexPhrase("Kétlem, hogy ","")+". Köszönöm, most mennem kell.";
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
            posrep1 = RandPhraseSimple(" Ennyi...", " Talán érdekes lehet.");
            posrep2 = " Hé, kapitány, van valami híred a kolóniánknak, amit el tudsz mondani?";
            answ1 = RandPhraseSimple(RandSwear() + "Ez nagyon érdekes, "+GetFullName(NPChar)+".",
                                 "Akkor mesélj nekem...");
            answ2 = RandPhraseSimple(RandSwear() + "Mindegy, csak mondj valami mást...","Igen, nem sokat segítettél, van még valami, amit meg akarsz osztani velem?");
            answ3 = RandPhraseSimple("Nos, a mi világunkban minden megtörténhet. Sajnálom, de nincs semmi különös mondanivalóm. ","Eléggé sietek, úgyhogy talán majd legközelebb.");
            answ4 = "";
        }
        else
        {
            posrep1 = " Elég unalmas hely ez itt. Szóval ha valami történik, akkor mindenki beszélni fog róla.";
            posrep2 = " Semmi érdekes. Talán a " + GetAddress_Form(NPChar) + " tudhat valamit?";
            answ1 = RandPhraseSimple("Akkor mesélj nekem...",RandSwear() + "Nem tudsz semmit! Rendben, másik téma...");
            answ2 = RandPhraseSimple("Mindegy, csak mondj valami mást...","Igen, nem sokat segítettél, van még valami, amit meg akarsz osztani velem?");
            answ3 = RandPhraseSimple("Kétlem, hogy bármi érdekeset tudnék mondani.","Örömömre szolgál, de beszéljünk legközelebb.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("Bízom benne, hogy kifejtettem a véleményemet - végeztem.","Elegem van a kérdéseibôl, kapitány. Menjen és keressen valami jobb elfoglaltságot!"),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Köszönöm, mennem kell.","Búcsú.");
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
			dialog.text = "A kikötôben az a hír járja, hogy Julie d'Armagnac, a kormányzó unokahúga már csak árnyéka önmagának. Egykor ragyogó és élettel teli volt, most azonban összetéveszthetetlen szomorúsággal az arcán kóborol az utcákon. A városlakók suttognak és azon tûnôdnek, mi történhetett vele, de senki sem tudja az igazságot. Talán egy gazember törte össze a szívét?"+GetSexPhrase(" Talán te voltál az, kapitány?","")+"";
			link.l1 = ""+GetSexPhrase("Kétlem, hogy ","")+". Köszönöm, most mennem kell.";
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
            posrep1 = RandPhraseSimple(" Ennyi...", " Talán érdekes lehet.");
            posrep2 = " Hé, kapitány, van valami híred a kolóniánknak, amit el tudsz mondani?";
            answ1 = RandPhraseSimple(RandSwear() + "Ez nagyon érdekes, "+GetFullName(NPChar)+".",
                                 "Akkor mesélj nekem...");
            answ2 = RandPhraseSimple(RandSwear() + "Mindegy, csak mondj valami mást...","Igen, nem sokat segítettél, van még valami, amit meg akarsz osztani velem?");
            answ3 = RandPhraseSimple("Nos, a mi világunkban minden megtörténhet. Sajnálom, de nincs semmi különös mondanivalóm. ","Eléggé sietek, úgyhogy talán majd legközelebb.");
            answ4 = "";
        }
        else
        {
            posrep1 = " Elég unalmas hely ez itt. Szóval ha valami történik, akkor mindenki beszélni fog róla.";
            posrep2 = " Semmi érdekes. " + GetAddress_Form(NPChar) + " talán tud valamit?";
            answ1 = RandPhraseSimple("Akkor mesélj nekem...",RandSwear() + "Nem tudsz semmit! Rendben, másik téma...");
            answ2 = RandPhraseSimple("Mindegy, csak mondj valami mást...","Igen, nem sokat segítettél, van még valami, amit meg akarsz osztani velem?");
            answ3 = RandPhraseSimple("Kétlem, hogy bármi érdekeset tudnék mondani.","Örömömre szolgál, de beszéljünk legközelebb.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("Bízom benne, hogy kifejtettem a véleményemet - végeztem.","Elegem van a kérdéseibôl, kapitány. Menjen és keressen valami jobb elfoglaltságot!"),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Köszönöm, mennem kell.","Búcsú.");
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
			dialog.text = "Két nappal ezelôtt szemtelen merényletet követtek el a kikötôi fônök ellen! A merénylô az irodája ajtajánál leselkedett, de a fônöknek sikerült segítségért kiáltania. Egy muskétás sietve érkezett, és megsebesítette a gazembert, bár a gazembernek sikerült elmenekülnie a város kapuján\nAz a hír járja, hogy a kikötôi fônök szép vérdíjat tûzött ki a gazember fejére! Eddig még nem jelentkeztek elég bátor lelkek. Vous savez, même s'il offrait mille doublons - je n'accepterais pas...";
			link.l1 = "Köszönöm, most mennem kell.";
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
		
		//--> Письмо от покойника
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		if (bOk1 || bOk2)
        {
			dialog.text = "Hallotta? Az 'Águila' nevű flöjt kapitánya olyan patáliát csapott a fogadóban a hadnagyának, hogy a falak is beleremegtek! Kiderült, hogy a kapitány dagálykor akart kifutni a tengerre, de a hadnagy az egész legénységet partra engedte. Most a matrózok szétszéledtek a városban, és ha nem térnek vissza időben, a hajó nélkülük fog elindulni – a kapitány nem szándékozik várni! Vajon miért ez a nagy sietség? Jó fuvardíj, előnyös üzlet, sürgős megbízás a kormányzótól?";
			link.l1 = "Köszönöm, most "+ GetSexPhrase("távoznom kell","távoznom kell") +".";
			link.l1.go = "exit";
			
			SetQuestHeader("LFD");
			AddQuestRecord("LFD", "1");
			pchar.questTemp.LFD_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("LFD_sailor", "citiz_33", "man", "man", 10, SPAIN, -1, true, "citizen"));
			ChangeCharacterAddressGroup(sld, "PortoBello_town", "goto", LAi_FindFarLocator2Pchar("goto"));
			sld.dialog.filename = "Quest\MiniEvents\LetterFromDeadman_dialog.c";
			sld.dialog.currentnode = "Sailor_1";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			//LAi_SetLoginTime(sld, 07.00, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Письмо от покойника
		
		if (!CheckAttribute(NPChar, "quest.repeat.rumours_citizen") || NPChar.quest.repeat.rumours_citizen != 2) srum = SelectRumourEx("sailor", NPChar);
        else srum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
        if (RumourHasInformation(srum))
        {
            posrep1 = RandPhraseSimple(" Ennyi...", " Talán érdekes lehet.");
            posrep2 = " Hé, kapitány, van valami híred a kolóniánknak, amit el tudsz mondani?";
            answ1 = RandPhraseSimple(RandSwear() + "Ez nagyon érdekes, "+GetFullName(NPChar)+".",
                                 "Akkor mesélj nekem...");
            answ2 = RandPhraseSimple(RandSwear() + "Mindegy, csak mondj valami mást...","Igen, nem sokat segítettél, van még valami, amit meg akarsz osztani velem?");
            answ3 = RandPhraseSimple("Nos, a mi világunkban minden megtörténhet. Sajnálom, de nincs semmi különös mondanivalóm. ","Eléggé sietek, úgyhogy talán majd legközelebb.");
            answ4 = "";
        }
        else
        {
            posrep1 = " Elég unalmas hely ez itt. Szóval ha valami történik, akkor mindenki beszélni fog róla.";
            posrep2 = " Semmi érdekes. " + GetAddress_Form(NPChar) + " talán tud valamit?";
            answ1 = RandPhraseSimple("Akkor mesélj nekem...",RandSwear() + "Nem tudsz semmit! Rendben, másik téma...");
            answ2 = RandPhraseSimple("Mindegy, csak mondj valami mást...","Igen, nem sokat segítettél, van még valami, amit meg akarsz osztani velem?");
            answ3 = RandPhraseSimple("Kétlem, hogy bármi érdekeset tudnék mondani.","Örömömre szolgál, de beszéljünk legközelebb.");
            answ4 = "";
        }
		Dialog.Text = NPCStringReactionRepeat(srum,
            srum+posrep1,
            srum+posrep2,
            RandPhraseSimple("Sajnos, nincs több mondanivalóm, hadd menjek tovább.","Elég volt a kérdéseidbôl, bocsáss meg, sok más dolgom van."),"block", 1, npchar, Dialog.CurrentNode);
        link.l1 = HeroStringReactionRepeat(answ1,
            answ2,
            answ3,
            answ4,
            npchar, Dialog.CurrentNode);
		link.l1.go = "question";
		link.l2 = RandPhraseSimple("Köszönöm, mennem kell.","Búcsú.");
		link.l2.go = "exit";
	break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	case "rumours_habitue":
		//-->работорговец
		if (pchar.questTemp.Slavetrader == "FindRatJamaica_H" && npchar.location == "FortOrange_tavern")
        {
			dialog.text = "(éneklés) Csibészek és gazemberek, gazemberek és gazemberek vagyunk; Igyál meg engem 'fearties, yo ho! Ördögök és fekete bárányok vagyunk, Igazán rossz tojások vagyunk, Igyál meg engem 'earties, yo ho!!! Hé, haver, hogy vagy? Hogy van a tenger?";
            link.l1 = "A tenger? Ugyanaz a ribanc, mint mindig. Sós és nedves. Mondd csak, hová tûnt a haverom, aki nemrég még itt bérelt szobát? Francois Gontier volt a neve.";
            link.l1.go = "Jamaica_ratH_1";
			break;
        }
		if (pchar.questTemp.Slavetrader == "EscapeSlaveVillemstad_H" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "(ing) Bonnie lassie, akarsz velem bandázni, Bonnie lassie, akarsz mellettem feküdni? Reggelre minden szalagodat felcsévélem, mielôtt elhagylak!";
            link.l1 = "Igyál egyet, pajtás! Hogy van a tenger?";
            link.l1.go = "EscapeSlave_Villemstad_H1";
			break;
        }
		//<--работорговец
				
		//Голландский Гамбит, против всех
		if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "LetterToLucasSent" && npchar.location == "Villemstad_tavern")
        {
			dialog.text = "Eh, a tenger... Bárcsak én lennék a helyedben!";
            link.l1 = "Nem látok semmi problémát, barátom. Bármikor csatlakozhatsz a legénységemhez.";
            link.l1.go = "Lucas_Tavern";
			break;
        }
		//Голландский Гамбит
		
		//--> поиск дезертира
		if (CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE && !CheckAttribute(npchar, "quest.fugitive"))
        {
			dialog.text = LinkRandPhrase("Tudod, a rum barátkozik a férfiakkal! Ha-ha!","Egy jó adag rum után még a hóhér is kedvesnek tûnik! Ha-ha!","Ha iszol, alszol, ha alszol, nem vétkezel! Rum és sör a mennyekbe vezet, hát igyál, a fenébe is! Ha!");
            link.l1 = "Persze, igyunk egyet... Mondd csak, jóember, ismered a "+pchar.GenQuest.FindFugitive.Name+"? Ô a régi cimborám. Néhány srác azt mondta, hogy ide költözött...";
            link.l1.go = "FindFugitiveHb";
			break;
        }
		//<-- поиск дезертира
		
		//--> карибские нравы
		if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && npchar.location == "Portobello_tavern")
		{
			dialog.text = "Hírek? Ha! Nem hallottad még? A katonáink elfogtak egy francia kémet. Kibaszott szélhámos, megpróbált kereskedônek tettetni magát, de *hic* - a parancsnokunk egy kemény fattyú!";
            link.l1 = "Nem mondod! És mit próbált kiszagolni az a békaember?";
            link.l1.go = "trial_spy";
			break;
		}
		if(CheckAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash") && PChar.location == PChar.GenQuest.ChurchQuest_2.QuestTown + "_tavern")
	    {
			dialog.text = "Eh, " + GetAddress_Form(pchar) + " milyen világban élünk... Szarháziak mindenhol!";
			link.l1 = "Hogy érted ezt, haver?";
			link.l1.go = "Alcogol_GenQuest_Church_2_1";
			break;
		}
		//<-- карибские нравы
		
		//--> Sinistra Длинные тени старых грехов
		if (CheckAttribute(pchar, "questTemp.DTSG_NightIskat") && npchar.city == "SentJons")
        {
			dialog.text = "Hallottátok?! Nem hiszem el! A híres Fleetwood kapitányt brutálisan meggyilkolták Londonban! A dicsôséget hajszolta, mindent megkapott, de csak a halált találta... Ha itt maradt volna, nagyobb biztonságban lenne. Azt mondom, néha jobb megbecsülni azt, amink van, ahelyett, hogy a pénzt vagy a rangot hajszolnánk, jegyezze meg, amit mondok, uram!";
            link.l1 = "Barátom, ugye tudod, hol lakik mindenki a kolónián?";
            link.l1.go = "DTSG_NightIskat";
			break;
        }
		//<-- Длинные тени старых грехов
		
		//--> Rebbebion, квест "Путеводная звезда"
		if (CheckAttribute(pchar, "questTemp.PZ_Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.PZ_Sotta") && !CheckAttribute(npchar, "questTemp.PZ_Lutter") && npchar.city == "Beliz")
		{
			link.l1 = "Tehát, a nap hôse, Edgardo Sotta kapitány. Mit mondanak róla az emberek? És ön mit gondol? Már nagyon vártam, hogy találkozzam vele.";
			link.l1.go = "Sotta1";
			link.l2 = "Haver, miért iszol egyedül? Mindenki összegyûlt, hogy megnézze a Szélzsák Mattet, akit épp most akasztanak fel.";
			link.l2.go = "Lutter1";
			break;
		}
		
		if (CheckAttribute(pchar, "questTemp.PZ.TortugaCitizensAsk") && !CheckAttribute(pchar, "questTemp.PZ.TortugaHabitueBlock") && npchar.city == "Tortuga")
		{
			link.l1 = "Figyelj, haver, próbáltam találni egy Joep van der Vink nevû embert. Át kell adnom neki egy üzenetet. Tudod, hogy néz ki, vagy tudsz róla valamit?";
			link.l1.go = "Sepp1";
			break;
		}
		//<-- квест "Путеводная звезда"
		
		//--> Тёмные воды исцеления
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.DWH_Start") && npchar.city == "SentJons";
		if (bOk1 || bOk2)
        {
			dialog.text = "Hallottad? Azt mondják, Thomas Morrison lánya már hat hónapja ágyhoz van kötve. Az orvosok teljesen tehetetlenek a betegségével szemben. Az egyetlen, aki segíthet rajta, az a cigányasszony, aki a súlyos betegeket is meggyógyító bájitalairól ismert. Ám a nô határozottan elutasítja, hogy bármit is tegyen a szegény lányért.";
			link.l1 = RandPhraseSimple(RandSwear() + "Ez megér még egy csészét...",
                                 "Rendben, igyunk még egyet.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Köszönöm, mennem kell.",
									 "Eh, pokoli jó rum. Rendben, mennem kell, érezd jól magad itt.");
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
			dialog.text = "Két nappal ezelôtt szemtelen merényletet követtek el a kikötôi fônök ellen! A merénylô az irodája ajtajánál leselkedett, de a fônöknek sikerült segítségért kiáltania. Egy muskétás sietve érkezett, és megsebesítette a gazembert, bár a gazembernek sikerült elmenekülnie a város kapuján\nAz a hír járja, hogy a kikötôi fônök szép vérdíjat tûzött ki a gazember fejére! Eddig még nem jelentkeztek elég bátor lelkek. Jól jegyezd meg, még ezer dublonnáért sem kockáztatnám a nyakamat...";
			link.l1 = RandPhraseSimple(RandSwear() + "Ez megér még egy csészét...",
                                 "Rendben, igyunk még egyet.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Köszönöm, mennem kell.",
									 "Eh, pokoli jó rum. Rendben, mennem kell, érezd jól magad itt.");
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
			dialog.text = "Hallottad a híreket?! Ez egy véres felháborodás! Egy csepp rum vagy bor sem maradt a kocsmában - hogyan is találhatna egy test enyhülést ebben az átkozott hôségben? A fogadós egy hete üres ígéretekkel etet minket, hogy az ital újra folyni fog, de semmi sem történt! Azt várják tôlünk, hogy az Ítélet Napjáig pergessük a torkunkat?";
			link.l1 = RandPhraseSimple(RandSwear() + "Ez megér még egy csészét...",
                                 "Rendben, igyunk még egyet.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Köszönöm, mennem kell.",
									 "Eh, pokoli jó rum. Rendben, mennem kell, érezd jól magad itt.");
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
			dialog.text = "A dokkokban az a hír járja, hogy a kocsmárosunk forró vízben van! Valaki ellopta a ginjét! Nem csak egy üveggel, hanem egy egész hordónyit - olyat, amilyet sehol máshol nem találni a szigeteken! Állítólag Európából hozták. A vén róka nem árulja el, hogy kinek tartogatta, de egy biztos: ha az a hordó nem kerül elô hamarosan, a pokolra kerül szegény szerencsétlen!";
			link.l1 = RandPhraseSimple(RandSwear() + "Ez megér még egy csészét...",
                                 "Rendben, igyunk még egyet.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Köszönöm, mennem kell.",
									 "Eh, pokoli jó rum. Rendben, mennem kell, érezd jól magad itt.");
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
			dialog.text = "A kikötôben az a hír járja, hogy Julie d'Armagnac, a kormányzó unokahúga már csak árnyéka önmagának. Egykor ragyogó és élettel teli volt, most azonban összetéveszthetetlen szomorúsággal az arcán kóborol az utcákon. A városlakók suttognak és azon tûnôdnek, mi történhetett vele, de senki sem tudja az igazságot. Talán egy gazember törte össze a szívét?"+GetSexPhrase(" Talán te voltál az, kapitány?","")+"";
			link.l1 = RandPhraseSimple(RandSwear() + "Ez megér még egy csészét...",
                                 "Rendben, igyunk még egyet.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Köszönöm, mennem kell.",
									 "Eh, pokoli jó rum. Rendben, mennem kell, érezd jól magad itt.");
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
			dialog.text = "Azt beszélik, hogy Pierre Carno halász nyomtalanul eltûnt. Két hajnalban elhajózott a kékbe, és azóta semmi nyoma. A felesége, Lea, magán kívül van a bánattól. Nappal és lámpafénynél is virraszt a mólónál, tekintetét a végtelen vízre szegezve, imádkozik, hogy megpillantsa szerelme vitorláját.";
			link.l1 = RandPhraseSimple(RandSwear() + "Ez megér még egy csészét...",
                                 "Rendben, igyunk még egyet.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Köszönöm, mennem kell.",
									 "Eh, pokoli jó rum. Rendben, mennem kell, érezd jól magad itt.");
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
			dialog.text = "Kapitány, hallottad? Új pincérnô dolgozik a kocsmánkban. Azt mondják, nagyon szép. A férfiak mindenhonnan rohannak be, csak hogy megpillanthassák. De három nappal ezelôtt nem jelent meg a munkában, ami nagyon felzaklatta a kocsmárost, aki az érkezése óta hatalmas nyereséget termelt. Állítólag még fizetni is hajlandó annak, aki megtalálja a lányt.";
			link.l1 = RandPhraseSimple(RandSwear() + "Ez megér még egy csészét...",
                                 "Rendben, igyunk még egyet.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Köszönöm, mennem kell.",
									 "Eh, pokoli jó rum. Rendben, mennem kell, érezd jól magad itt.");
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
		
		//--> Оковы азарта
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.OZ_Start") && npchar.city == "PortSpein" && sti(pchar.rank) >= 1;
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.OZ_Start") && npchar.city == "PortSpein";
		if (bOk1 || bOk2)
        {
			dialog.text = "Hallotta? A mi kovácsunk kártyán elvesztett mindent Javier Castillo ellen, úgy, hogy az teljesen kifosztotta, és rákényszerítette, hogy valami nagyon értékeset tegyen fel. Azóta a kovács sehogy sem tud magához térni, és nem vállal új megrendeléseket – csak azon bánkódik, hogy az admirális három bőrt lehúz róla. Kár ezért a jámbor emberért, minden helybéli tudja, hogy ezzel a csaló Castillo-val nem szabad játszani!";
			link.l1 = RandPhraseSimple(RandSwear() + "Ez megér még egy csészét...",
                                 "Rendben, igyunk még egyet.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Köszönöm, mennem kell.",
									 "Eh, pokoli jó rum. Rendben, mennem kell, érezd jól magad itt.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("OZ");
			AddQuestRecord("OZ", "1");
			pchar.questTemp.OZ_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("OZ_Blacksmith", "blacksmith_18", "man", "man", 5, SPAIN, -1, false, "quest"));
			sld.name = StringFromKey("Neutral_31");
			sld.lastname = StringFromKey("Neutral_32");
			sld.City = "PortSpein";
			ChangeCharacterAddressGroup(sld, "PortSpein_town", "quest", "quest3");
			sld.dialog.filename = "Quest\MiniEvents\OkoviAzarta_dialog.c";
			sld.dialog.currentnode = "OZ_Kuznets_1";
			LAi_SetStayType(sld);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			LAi_SetImmortal(sld, true);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Оковы азарта
		//--> Письмо от покойника
		bOk1 = !SandBoxMode && CheckAttribute(pchar, "questTemp.TrialEnd") && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		bOk2 = SandBoxMode && sti(pchar.rank) >= 1 && !CheckAttribute(pchar, "questTemp.LFD_Start") && npchar.city == "PortoBello";
		if (bOk1 || bOk2)
        {
			dialog.text = "Hallotta? Az 'Águila' nevű flöjt kapitánya olyan patáliát csapott a fogadóban a hadnagyának, hogy a falak is beleremegtek! Kiderült, hogy a kapitány dagálykor akart kifutni a tengerre, de a hadnagy az egész legénységet partra engedte. Most a matrózok szétszéledtek a városban, és ha nem térnek vissza időben, a hajó nélkülük fog elindulni – a kapitány nem szándékozik várni! Vajon miért ez a nagy sietség? Jó fuvardíj, előnyös üzlet, sürgős megbízás a kormányzótól?";
			link.l1 = RandPhraseSimple(RandSwear() + "Ez megér még egy csészét...",
                                 "Rendben, igyunk még egyet.");
			link.l1.go = "sit_3";
			link.l2 = RandPhraseSimple("Köszönöm, mennem kell.",
									 "Eh, pokoli jó rum. Rendben, mennem kell, érezd jól magad itt.");
			link.l2.go = "exit_sit";
			
			SetQuestHeader("LFD");
			AddQuestRecord("LFD", "1");
			pchar.questTemp.LFD_Start = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("LFD_sailor", "citiz_33", "man", "man", 10, SPAIN, -1, true, "citizen"));
			ChangeCharacterAddressGroup(sld, "PortoBello_town", "goto", LAi_FindFarLocator2Pchar("goto"));
			sld.dialog.filename = "Quest\MiniEvents\LetterFromDeadman_dialog.c";
			sld.dialog.currentnode = "Sailor_1";
			LAi_SetCitizenType(sld);
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
			//LAi_SetLoginTime(sld, 07.00, 21.99);
			AddLandQuestMark(sld, "questmarkmain");
			
			pchar.questTemp.MiniEvents = sti(pchar.questTemp.MiniEvents) + 1; // активировано событие
			break;
        }
		//<-- Письмо от покойника

		Dialog.Text = LinkRandPhrase("Nos... hic! ","Ah, jó rum! ","Nos... ")+SelectRumourEx("szokás...", NPChar);
		link.l1 = RandPhraseSimple(RandSwear() + "Ez megér még egy csészét...",
                                 "Rendben, igyunk még egyet.");
		link.l1.go = "sit_3";
		link.l2 = RandPhraseSimple("Köszönöm, mennem kell.",
                                 "Eh, pokoli jó rum. Rendben, mennem kell, érezd jól magad itt.");
		link.l2.go = "exit_sit";
	break;
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_trader":
            if (!CheckAttribute(NPChar, "quest.repeat.rumours_trader") || NPChar.quest.repeat.rumours_trader!= 3 )
            strum = SelectRumourEx("trader", NPChar);
            else strum = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)]; // fix
			Dialog.Text =  NPCStringReactionRepeat(strum, strum+" Aha. Nincs több mondanivaló.",
                strum+" Most már vissza kellene térnem a munkához.",RandPhraseSimple("Már mondtam, hogy nincs idôm olcsó fecsegésre!","Elfoglalt ember vagyok, nincs idôm pletykálkodni!"),"block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(pcharrepphrase(RandSwear() + "Érdekes! De térjünk a lényegre","Hála, itt van még egy dolog."), pcharrepphrase(""+ GetSexPhrase("Fenébe","Érdekes") +"! Szép mesélô. De lenne még egy kérdésem.","Ne vesztegessük tovább az idôt és beszéljünk az üzletrôl."),
pcharrepphrase(RandSwear() +" Még egy dolog és elmegyek.","Igazad van, az idô pénz."),pcharrepphrase("Mindig csak a saját profitodra gondolsz! Rendben, ne ôrülj meg.","Bocsáss meg. Beszéljünk az üzletrôl."),npchar, Dialog.CurrentNode);
			link.l1.go = "business";
			link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Isten veled, te vén részeges.",
"Viszlát, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"."),pcharrepphrase("Caramba! Ne menj messzire. Hamarosan visszajövök.","Örülök, hogy látlak, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"! Viszontlátásra!")),NPCharRepPhrase(npchar,pcharrepphrase("Vesszôt le!","Viszlát!"),pcharrepphrase("Hé! Mit rejtegetsz ott? Rumot? Nem!?! Mindegy, hozok egy kis italt.","Sajnálom, fontos dolgom van a városban.")),NPCharRepPhrase(npchar,pcharrepphrase("Heh! Viszlát!","Mennem kell. Viszlát, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!"),pcharrepphrase("Ne merj velem vitatkozni! Nem kívánom ezt!","Azt hiszem, meg kellene néznem a hajómat. Viszlát, "+GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),NPCharRepPhrase(npchar,pcharrepphrase("Mi a bajod, haver? Én vagyok az - " +GetFullName(pchar)+ "! Aludj egyet, késôbb beszélünk.","Félek, hogy a májad megöl, mielôtt újra idejövök."),pcharrepphrase("Számold meg az ezüstöt, ravasz kutya! Késôbb találkozunk.","Örülök, hogy látlak, " + GetAddress_FormToNPC(NPChar)+" " +GetFullName(npchar)+"!")),npchar, Dialog.CurrentNode);
			link.l2.go = "Exit";
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_capitan":
			Dialog.Text = SelectRumourEx("capitan", NPChar);
			Link.l1 = RandPhraseSimple(RandSwear() + "Érdekes! Van még egy dolog, amit szeretnék megkérdezni...",
                                     "Még egy kérdés.");
			Link.l1.go = "quests";
			Link.l2 = RandPhraseSimple("Köszönöm, mennem kell.",
                                     "Búcsú.");
			Link.l2.go = "exit";
			NextDiag.TempNode = "quests";
            NPChar.talk_date =  lastspeakdate();
		break;
		
		 case "rumours_landcaptain":
			Dialog.Text = SelectRumourEx("landcaptain", NPChar);
			Link.l1 = RandPhraseSimple(RandSwear() + "Érdekes! Van még egy dolog, amit szeretnék megkérdezni...",
                                     "Még egy kérdés.");
			Link.l1.go = "question";
			Link.l2 = RandPhraseSimple("Köszönöm, mennem kell.",
                                     "Búcsú.");
			Link.l2.go = "exit";
			NextDiag.TempNode = "question";
            NPChar.talk_date =  lastspeakdate();
		break;
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		case "rumours_tavern":  // homo 03/08/06
				if(startHeroType == 4)
				{
					Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("Tudja az árat. Az információ olyan, mint a szoba, az étel vagy az ital - ára van. Ez ezer pezó lesz.",
					"Tudod az árát. Az információ olyan, mint egy szoba, étel vagy ital - kerül. Ez ezer pezó lesz.",
					"Tudod az árát. Az információ olyan, mint egy szoba, étel vagy ital - kerül. Ez ezer pezó lesz."),
					"Nincs mit hozzátenni. Most pedig elnézést, mennem kell.",
					"", "", "block", 1, npchar, Dialog.CurrentNode);
				 
					link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Tulajdonképpen miért is kérdezem? Bárki mást is megkérdezhetek errôl. Elnézést a zavarásért.",
											 "Tulajdonképpen miért is kérdezem? Bárki mást is megkérdezhetek róla. Elnézést a zavarásért."), "", "", "", npchar, Dialog.CurrentNode);
					link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);//"rumours_tavern_no";
					NextDiag.CurrentNode = NextDiag.TempNode;
					if (makeint(pchar.money) >= 1000)
					{
						link.l2 = HeroStringReactionRepeat(RandPhraseSimple("Tudom, persze. Itt a fizetésem.", "Tudom, persze. Itt a fizetésem."),
						"", "", "" , npchar, Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
					else
					{
						link.l2 =  HeroStringReactionRepeat("Nincs ennyi pénzem.", "", "", "", npchar, Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_no", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
				}
				else
				{
					Dialog.Text = NPCStringReactionRepeat(LinkRandPhrase("Az információ pénzbe kerül. 1000 pezóért mindent elmondok, amit tudok.",
					"Valami baj van a memóriámmal, 1000 darab pesó talán segít emlékezni valamire.",
					"szívesen megosztom az információkat. De ez 1000 darab pesóba fog kerülni. Nincs alkudozás."),
					"Itt már nincs mit hozzátenni. Most pedig bocsássanak meg, mennem kell.",
					"", "", "block", 1, npchar, Dialog.CurrentNode);
				 
					link.l1 = HeroStringReactionRepeat(RandPhraseSimple(RandSwear() + "Nem fizetek egy értéktelen csevegésért.",
											 "Majd elgondolkodom, hogy mire költsem jobban ezeket a pénzeket."), "Váltsunk témát.", "Váltsunk témát.", "Váltsunk témát.", npchar, Dialog.CurrentNode);
					link.l1.go = HeroStringReactionRepeat("rumours_tavern_no", "first time", "first time", "first time", npchar, Dialog.CurrentNode);//"rumours_tavern_no";
					NextDiag.CurrentNode = NextDiag.TempNode;
					if (makeint(pchar.money) >= 1000 )
					{
						link.l2 = HeroStringReactionRepeat(RandPhraseSimple("Megkapod ôket, ha valami értékeset tanulok tôled.", "Fizetek, ha adsz nekem valami értékeset."),
						 "", "", "" , npchar, Dialog.CurrentNode);
						link.l2.go = HeroStringReactionRepeat("rumours_tavern_yes", "exit", "exit", "exit", npchar, Dialog.CurrentNode);
					}
					else
					{
						link.l2 =  HeroStringReactionRepeat("Nincs ennyi pénzem.", "", "", "", npchar, Dialog.CurrentNode);
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
					Dialog.Text =  "Az ôrjáratunk nemrég megsemmisítette egy Morel nevû francia csempész brigantiját. A férfi most a tömlöcben ül, és halálos ítélet vár rá. A parancsnokunk úgy gondolja, hogy nem volt teljes rakomány a hajóján, ezért még mindig próbálja megtalálni... a francia meghal, ha a parancsnok megtalálja a hiányzó rakományt.";
					link.l1 = "Érdekes... Rendben, fogd a pénzt. Van még valami más mondanivalója?";
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
				Dialog.Text =  "A kormányzó palotájában nagy ünnepség volt. Ôexcellenciája barátja, Don Carlos de Milyar visszatért. Egy tengeri csatában fogságba esett, de egy francia hadnagy segítségével sikerült megszöknie. Don Carlos nemcsak okos, hanem nagyon nagylelkû ember is. Az ô támogatásával lett ez a hadnagy, Jean Deno, a 'Sario'-nak a kaptiánya. Amennyire hallottam, egy kis ültetvényt is kapott ajándékba. Most már a frogeatert Juannak hívják! Micsoda történet!";
				link.l1 = "Érdekes... Rendben, a pénz a tiéd. Fogd ezt. Van még valami, amit el akarsz mondani?";
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
				Dialog.Text =  "A parancsnokunk extra erôket küldött a dzsungelbe járôrözni, és növelte az ôrök számát a városban. Pletykák szerint angolok tervezik, hogy beszivárognak Philipsburgba, és szabadon engedik az elfogott tiszteket.";
				link.l1 = "Ne is mondd! Tényleg van merszük egy ilyen trükkhöz? És pontosan milyen tisztekrôl beszélsz?";
				link.l1.go = "FMQN_r";
				break;
			}	
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_3" && npchar.location == "Havana_tavern")
			{
				AddMoneyToCharacter(pchar, -1000);
				Dialog.Text =  "A minap az egész város felbolydult, mint egy darázsfészek. Egy katonatiszt holtrészegen betért a kocsmámba, és majdnem megerôszakolt egy férjes asszonyt. Aztán megverte a férjét, aki megpróbálta megvédeni a feleségét, és még karddal is megfenyegette. Képzeljék el mindezt a városôrség szeme láttára! Ahogy mondani szokták, a jog tiszteletben tartja az erôt. A katonák csak elfordultak, amíg ez a fattyú tombolt\nDe a gazembert lefegyverezte, ki gondolta volna, néhány matróz egy kereskedôhajóról. Majdnem bebugyolálták, bár a fattyú elmenekült, és elbújt a hajóján. A parancsnok és az alcalde megpróbálta a szônyeg alá söpörni az ügyet, de a felháborodott férj egy köztiszteletben álló polgár, aki Don Diego de Toledo kiválóságához fordult, és zajt csapott a helyi nemesség körében\nEzek elfogatóparancsot adtak ki a tiszt ellen. Azt beszélték, hogy a kapitánya azt javasolta, hagyják el vele együtt a kikötôt, és helyezzék át a gazembert egy másik helyre. A szkúner kapitánya, Esberdo Cabanas azonban becsületes ember. Amint megtudta, mit tett a tisztje, azonnal letartóztatta, és visszaküldte a partra. A szemétláda belátható idôn belül a börtönben rohad, ahová, ha engem kérdezel, tartozik is. És aztán, talán, démonizálják egy közönséges katonává és megkorbácsolják, példaként másoknak.";
				link.l1 = "Várj, Esberdo Cabanas kapitányt mondtál? Huh... izgalmas történet, valóban! Rendben, megdolgoztál a pénzedért, tessék. Van még valami, amit el tudsz mondani?";
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
				Dialog.Text =  "Azt mondják, hogy néhány bûnözôt otthagytak az egyik lakatlan szigeten! Állítólag olyan kegyetlen szörnyetegek, hogy sem a hóhér, sem a szentatyák nem mertek velük foglalkozni! De miért hozzák ôket mindig ide?!";
				link.l1 = "Hmm... milyen érdekes! Talán fel kellene kutatnom és beszerveznem ôket - mindig szükségem van kétségbeesett lelkekre... Miért vagy ilyen fehér, haver? Csak viccelek, csak viccelek... Megdolgoztál a pénzedért - tessék. Hallottál még valamit?";
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
					link.l1 = "Kiderült, hogy mégsem tudsz semmit. Nem számítottam rá, hogy így átversz. Nem túl okos. Nos, viszlát.";
				}
				else
				{
					link.l1 = RandPhraseSimple("Értéktelen szar. Egy pezót sem fogok fizetni neked! Viszlát.", "Az információd nem kerül semmibe, így nem kapsz semmit.");
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
					link.l1 = "Tényleg? Érdekes, köszönöm. Nos, most mennem kell, a következô alkalomig.";
					link.l1.go = "exit";
				}
				else
				{
					link.l1 = RandPhraseSimple("Köszönöm, fogadd el a pénzt. Van még valami mondanivalója?", "Rendben, vegye el a pénzt. Van még valami mondanivalód?");
					link.l1.go = "rumours_tavern";
				}
    			NextDiag.CurrentNode = NextDiag.TempNode;    
            }
		break;

		case "rumours_tavern_no":
			if(startHeroType == 4)
			{
				Dialog.Text = "Segíthettél volna egy kis pénzzel. Veled ellentétben, Helen, engem nem támogat a Testvérek Bárója.";
				link.l1 = "Neked egy egész intézményed van. Én pedig egyedül jutottam el oda, ahol vagyok. Nos, eltekintve a hajótól, az ágyúktól, a legénységtôl és az ellátmánytól, amit a báró adott nekem. Rendben, nem számít.";
				link.l1.go = "exit";
				NextDiag.CurrentNode = NextDiag.TempNode;
			}
			else
			{
				Dialog.Text = "Juttass rendbe, etetnem kell a családomat.";
				link.l1 = "Váltsunk témát.";
				link.l1.go = "first time";
				NextDiag.CurrentNode = NextDiag.TempNode;
				link.l2 = LinkRandPhrase("Köszönöm, mennem kell.",
										 "Viszlát.","Viszlát.");
				link.l2.go = "Exit";
			}
		break;	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_poor":
			if (!CheckAttribute(NPChar, "quest.repeat.rumours_poor") || NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("gyenge", NPChar);
				Link.l1 = RandPhraseSimple(RandSwear() + "Érdekes. Még egy kérdés...",
										"Hm, hadd kérdezzek még valamit...");
				Link.l1.go = "rumours_poor_2";
				Link.l2 = RandPhraseSimple("Nos, viszlát.",
										"Viszlát, haver.");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple("Mindent elmondtam, amit tudtam.", 
					"Nincs több megosztani valóm, sajnálom...");
				Link.l1 = RandPhraseSimple("Értem. Viszontlátásra.",
										"Viszlát, haver...");
				Link.l1.go = "exit";			
			}
            NPChar.talk_date = lastspeakdate();
		break;
        case "rumours_poor_2":
			if (NPChar.quest.repeat.rumours_poor <= 1)
			{
				Dialog.Text = SelectRumourEx("gyenge", NPChar);
				Link.l1 = RandPhraseSimple(RandSwear() + "Érdekes. Még egy kérdés...",
										"Hm, hadd kérdezzek még valamit...");
				Link.l1.go = "rumours_poor";
				Link.l2 = RandPhraseSimple("Nos, viszlát.",
										"Viszlát, haver.");
				Link.l2.go = "exit";
				NPChar.quest.repeat.rumours_poor = sti(NPChar.quest.repeat.rumours_poor) + 1;
			}
			else 
			{
				Dialog.Text = RandPhraseSimple("Mindent elmondtam, amit tudok.", 
					"Nincs több megosztani valóm, sajnálom...");
				Link.l1 = RandPhraseSimple("Értem. Viszontlátásra.",
										"Understood. Viszlát, haver...");
				Link.l1.go = "exit";			
			}
			NPChar.talk_date = lastspeakdate();
		break;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
        case "rumours_LSC":
			if (CheckNPCQuestDate(NPChar, "quest.repeat.rumours"))
			{
				Dialog.Text = SelectRumourExSpecial("LSC", NPChar);
				Link.l1 = RandPhraseSimple("Értettem...",
										"Értem...");
				Link.l1.go = "exit";
				SetNPCQuestDate(NPChar, "quest.repeat.rumours");
			}
			else  
			{
				Dialog.Text = NPCharSexPhrase(npchar, RandPhraseSimple("Mindent elmondtam, amit tudtam.", "Nem hallottam semmi újat, sajnálom..."), 
					RandPhraseSimple("Mindent elmondtam, amit tudtam.", "Nem hallottam semmi újat, sajnálom..."));
				Link.l1 = RandPhraseSimple("Értem, akkor viszlát.", "Understood. Viszlát, haver.");
				Link.l1.go = "exit";			
			}
		break;
		
//Jason -------------слухи смотрителей маяков, идентичны таверне, но бесплатны, по 1 шт за день--------------------
		case "rumours_lighthouse": 
			Dialog.Text = NPCStringReactionRepeat(RandPhraseSimple("Eh, kapitány! Mindig jó veled beszélgetni. Néha elég unalmas itt egyedül lenni...", "Egyedül élek, a látogatók ritkák. Így mindig van kedvem beszélgetni."), "Szeretne beszélgetni, kapitány? Nos, lehet, hogy van még valami mondanivalóm...", "Vigyen magával egy üveg rumot, ha legközelebb meglátogat. A beszélgetések jobbak az italok mellett...", "Sajnos, mindent elmondtam, amit tudok. Nincs mit hozzátennem.", "block", 1, npchar, Dialog.CurrentNode);
    		link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Ezután ossza meg az információit. Szeretek beszélgetni az emberekkel, tudod...", "Mondd el! Ahogy mondják, akié az információ - azé a világ?"), "Mint például?", "Mindenképpen! Van még valami, amit meg szeretnél osztani?", "Rendben, amúgy is jól elbeszélgettünk." , npchar, Dialog.CurrentNode);
    		link.l1.go = HeroStringReactionRepeat("rumours_lighthouse_yes", "rumours_lighthouse_void", "rumours_lighthouse_void", "exit", npchar, Dialog.CurrentNode);
		break;
		
		case "rumours_lighthouse_yes":
            RumText = SelectRumourEx("tavern", NPChar);
		    if(!RumourHasInformation(RumText))
            {
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
                link.l1 = RandPhraseSimple("Köszönöm! Még valami?", "Nagyon érdekes! Még valami?");

			    link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("Hála! Elég szórakoztató volt...", "Köszönöm, hogy elmondtad!");
			    link.l2.go = "exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
            }
            else
            {
                Dialog.Text = RumText;
    			link.l1 = RandPhraseSimple("Köszönöm! Még valami?", "Nagyon érdekes! Még valami?");
    			link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("Hála! Elég szórakoztató volt...", "Köszönöm, hogy elmondtad!");
			    link.l2.go = "exit";
    			NextDiag.CurrentNode = NextDiag.TempNode;    
            }
		break;
		
		case "rumours_lighthouse_void":
                Dialog.Text = NO_RUMOUR_TEXT[rand(SIMPLE_RUMOUR_NUM - 1)];
                link.l1 = RandPhraseSimple("Köszönöm! Még valami?", "Nagyon érdekes! Még valami?");

			    link.l1.go = "rumours_lighthouse";
				link.l2 = RandPhraseSimple("Hála! Elég szórakoztató volt...", "Köszönöm, hogy elmondtad!");
			    link.l2.go = "exit";
			    NextDiag.CurrentNode = NextDiag.TempNode;
		break;
//Jason ------------------------------------почтовый генератор 2 уровня-------------------------------------------
		case "Postcureer_LevelUp_ForAll":
			//начинаем проверять
			if (!CheckCharacterItem(pchar, pchar.questTemp.WPU.Current.Item))
			{
				dialog.text = "De hol van a csomag? Nincs nálad?";
	        	link.l1 = "Hát... Nekem kellett volna átadnom neked. De... hogy teljesen ôszinte legyek, elvették tôlem. Nem tudtam visszavágni, és magam adtam oda a támadóknak a csomagot. ";
	        	link.l1.go = "Postcureer_LevelUp_complete_fail";
				break;
			}
			
			if (sti(pchar.questTemp.WPU.Postcureer.AgentChance) == 4)//раскрыли обман
			{
				dialog.text = "Hm. Elnézést, de a csomagot már kinyitották! Ez kristály nekem. A pecsétet újra lepecsételték...";
	        	link.l1 = "" + GetAddress_FormToNPC(NPChar) + ", ez az a csomag, amit a kikötôi irodában kaptam a " +XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+ ", és fogalmam sincs...";
	        	link.l1.go = "Postcureer_LevelUp_complete_Agentfail";
				break;
			}
			
			if (pchar.questTemp.WPU.Postcureer == "late")//опоздали
			{
				int iTime = makeint(GetQuestPastDayParam("questTemp.Postcureer.Late"))+1;
				pchar.questTemp.WPU.Postcureer.Money = makeint(sti(pchar.questTemp.WPU.Postcureer.Money)/(sti(iTime)+1));//сильно снижаем оплату
				dialog.text = "Már vártam rád. De te " + FindRussianDaysString(iTime)+ " elkéstél! Az információ, amit hordozol, már sokkal kevésbé hasznos... Persze még mindig van némi értéke, ezért fizetek neked " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + ". Kérem, vegye el a pénzt és búcsúzzon el.";
	        	link.l1 = "Köszönöm. Gondolom.";
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
				dialog.text = "Szóval te vagy az! Már régóta vártam rád, még a csomagért is megtettem a szükséges lépéseket. Add ide. Most már tényleg nincs rá szükségem, hála az idôzítésednek, de szeretném megtartani magamnak\nAmint érted, nem tudok neked fizetni semmit, mégis gondoskodom róla, hogy a jó hírneved helyreálljon.";
	        	link.l1 = "Köszönöm... Azt hiszem. Elnézést kérek a késésért, tényleg. Viszontlátásra.";
	        	link.l1.go = "Postcureer_LevelUp_complete_bad";
				break;
			}
			dialog.text = "Már vártam rád. Épp idôben jöttél, az információ, amit hoztál nekem, jó hasznomra válik. Kérem, fogadja el ezt a pénzt a munkájáért - " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.Money)) + ". Köszönöm az idôzítést.";
        	link.l1 = "Szívesen. Viszontlátásra!";
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
			dialog.text = "Eh, tudtam, hogy így fog végzôdni... Egy katonai futárhajót kellett volna felbérelnem, nem egy civil kapitányt... Mindegy, " + GetAddress_Form(NPChar) + ", te nem vagy katona, úgyhogy nincs miért hibáztatni téged. Viszontlátásra.";
			link.l1 = "Viszlát, " + GetAddress_FormToNPC(NPChar) + ".";
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
			dialog.text = "Uram, személyesen ismerem a " +XI_ConvertString("Colony"+pchar.questTemp.WPU.Postcureer.StartCity+"Gen")+ " kikötômesterét, ô egy becsületes ember. Ráadásul nem volt értelme, hogy kinyissa a csomagot. " + GetAddress_Form(NPChar) + ", maga egy csaló! Egyetlen rézpénzt sem fogok fizetni neked. Húzz a picsába!";
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
			dialog.text = "Úgy nézett ki, mint egy két lábon járó szemét. Egy csavargó vagy egy koldus. Nem tudom megmondani, hogy pontosan hova ment, nem akartam követni.";
			link.l1 = "Jobb, mint a semmi. Köszönöm, hogy eljöttél! Mennem kell.";
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
			if (GetNationRelation(SPAIN, ENGLAND) == RELATION_NEUTRAL) { Dialog.Text = "Nem is olyan régen Sint Maarten partjainál feltartóztattak egy angol hajót, amelyen több magas rangú katonatiszt tartózkodott. Úgy döntöttek, hogy Willemstadba küldik őket, amíg a körülményeket tisztázzák, de ideiglenesen börtönbe zárták őket. Azt beszélik, hogy az egyik fogoly katona a szabadságáért cserébe elárulta a parancsnoknak: az angolok szabotázscsoportot akarnak küldeni, és szökést szervezni a raboknak. Még tervük is volt hozzá. Szóval most éberen figyel a mi derék parancsnokunk. Hiszen ha elszállnak azok a fontos madarak – hát biztos lefokozzák sima katonává. Hát ez van! Semmi jóra nem lehet számítani – még a végén megint háború lesz."; }
			else {Dialog.Text =  "Nemrég egy angol hajót fogtak el Sint-Maarten vizein, néhány magas rangú tisztet szállított. Úgy döntöttek, hogy Willemstadba küldik ôket, de jelenleg itt tartják ôket a kényelmes börtönünkben. Azt mondják, hogy az egyik elfogott katona elmondta a parancsnokunknak az angolok azon szándékát, hogy portyázó csapatot küldjenek ide a tisztek kiszabadítására. Ezért a mi jó öreg parancsnokunk készenlétben áll és felfegyverkezve. Miért is ne lenne, ha a foglyok eltûnnek, akkor közönséges katonává fokozzák le!";}
			link.l1 = "Érdekes... Rendben, a pénz a tiéd. Fogd ezt. Van még valami, amit el akarsz mondani?";
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
            Dialog.Text = RandPhraseSimple("Rendben van. Itt van a csomag, kézbesítésre készen. Vegye el\nNe jöjjön ide, és ne beszéljen velem többet, ez túl veszélyes. Vigyázz magadra odakint...", 
				"Hm, remek. Fogd a csomagot, és mindenképpen add át annak az embernek, akirôl az elôbb beszéltünk\nViszlát, és ne beszélj velem többet, túl veszélyes.");
            link.l1 = RandPhraseSimple("Megvan. Viszlát...", "Viszlát és sok szerencsét.");
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
			dialog.text = LinkRandPhrase("Egy rablás a nap közepén!!! Tényleg?! Maradj ott, ahol vagy, haver...", "Hé, mit csinálsz ott?! Úgy tûnik, valaki ki akart rabolni. Végeztél...", "Várj, hova mész? Egy tolvaj! Vége a sornak, haver...");
			link.l1 = LinkRandPhrase("A francba!", "Carramba!", "A francba!");
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
	STR_MAYOR[0] = "Ó, a kormányzó úr kiváló ember. Nagy szakértelemmel irányítja a kolóniánkat, az alapítás napja óta egyetlen konfliktus sem volt\nAz egyetlen hibája... ô... nos... eléggé takarékos. Bár lehet, hogy ez csak egy másik erény.";
	STR_MAYOR[1] = "Ó, a kormányzó úr kiváló ember. Nagy szakértelemmel irányítja a kolóniánkat, az alapítás napja óta egyetlen konfliktus sem volt\nAz egyetlen hibája... ô... nos... eléggé takarékos. Bár lehet, hogy ez csak egy másik erény.";
	STR_MAYOR[2] = "A kormányzó jó ember, de gyenge jellem. Ha lenne egy kis szilárdság a lelkében, a kereskedôink kaphattak volna kisebb adókedvezményeket... És már itt az ideje, hogy az erôd javítására is juttassanak támogatásokat.";
	STR_MAYOR[3] = "Hmm ... Ô lett nemrég a kormányzó. Elég fiatal és ezért nagyon kezdeményezô. Vele a kolóniánk virágzik.";
	STR_MAYOR[4] = "A kormányzó még viszonylag fiatal. Azt mondják, hogy egy spanyol gróf semmirekellô kisebbik fia, akit messzire küldtek az udvarból, hogy ne hozzon szégyent a családjára. Nemrég nevezték ki ide, és nem volt ideje arra, hogy valami emlékezeteset alkosson.";
	STR_MAYOR[5] = "Hmm ... Nemrég lett a kormányzó. Elég fiatal és ezért nagyon kezdeményezô. Vele a kolóniánk virágzik.";
	STR_MAYOR[6] = "Nos... Semmi... Nem tudok semmi rosszat mondani róla...";
	
	string STR_TAVERNKEEPER[MAX_RUMOURS_ABOUT_OWNERS]; // Тавернщики
	STR_TAVERNKEEPER[0] = "Hm, én nem bíznám a tulajdonomat erre a gazemberre. Ne értsen félre, de nekem úgy tûnik, hogy ez a legmegbízhatatlanabb ember a városunkban\nHallottam, hogy kalózokkal és csempészekkel dolgozik együtt, akiket gyakran lehet látni a kocsmájában.";
	STR_TAVERNKEEPER[1] = "Mit is mondhatnánk róla! Gyáva, és nem is a legokosabb ember, akit ismerek. Ráadásul pénzéhes, ezért kerül állandóan különbözô bajba! Viszont mindig naprakész minden hírrel kapcsolatban.";
	STR_TAVERNKEEPER[2] = "Egészen kellemes fickó. Mindig jó a kocsmájában tölteni az idôt, remek humorérzéke is van. A legfontosabb dolog benne, hogy rendben tartja a kocsmát, és megakadályozza, hogy részeg aljanépek zaklassák a jó polgárokat.";
	STR_TAVERNKEEPER[3] = "Hihetetlen ember. Nem kocsmát kellene tartania, hanem a hírszerzés informátorának kellene lennie. Néha úgy tûnik, hogy szó szerint mindent tud, ami a városunkban történik. Még engem is megrémít.";
	STR_TAVERNKEEPER[4] = "Nem tudom, mit mondhatnék. Egy férfi. Kocsmát vezet. Mindent tud a városról és annak lakóiról.";
	STR_TAVERNKEEPER[5] = "Azt mondják, hogy lehet rá támaszkodni. Másrészt azt hallottam, hogy nem szereti a felesleges kockázatot, és mindig óvatosan intézi az ügyeit. Igen, és a sötét ügyek nem az ô asztala.";
	STR_TAVERNKEEPER[6] = "A kocsmát az apjától örökölte. Az apja nem messze innen, egy másik szigetcsoporton, Highrock szigetén tartott egy kocsmát. Aztán az apja ideköltözött, itt épített egy új tavernát, és most a fia vezeti...";
	
	string STR_SHIPYARDER[MAX_RUMOURS_ABOUT_OWNERS]; // Верфисты
	STR_SHIPYARDER[0] = "Hajókat épít. Nem is tudom. Csendes és békés ember. Azt hiszem, jó ember.";
	STR_SHIPYARDER[1] = "Hajókat épít. Nem is tudom. Csendes és békés ember. Azt hiszem, jó ember.";
	STR_SHIPYARDER[2] = "Jó ember, de azt mondják, hogy túl szigorú. Állandóan szidja az alkalmazottakat. Ezért gyakran elmennek. Ennek ellenére kiváló hajóépítô.";
	STR_SHIPYARDER[3] = "Nagyon mûvelt ember. Úgy hallottam, hogy Angliában, majd Hollandiában tanult hajóépítést. És végül itt kötött ki - távol a nagyvárostól, a provinciális szigetvilágban\nAz emberek azt mondják, hogy gondjai voltak a Szent Inkvizícióval, és a gyarmatra kellett menekülnie.";
	STR_SHIPYARDER[4] = "Ennek az öregembernek már nyugdíjba kell vonulnia, és átadni az utat valami friss vérnek. Állandóan a régi idôkrôl álmodozik, és morog, ha valaki karavellákon vagy gályákon kívül mást is rendel tôle.";
	STR_SHIPYARDER[5] = "Nagyszerû fiú. Mindig hajlandó segíteni. Azt kell mondanom, hogy remek hajókat épít egy ilyen szarfészekhez képest, mint ez a hely.";
	STR_SHIPYARDER[6] = "Fogoly volt, Európából számûzték a mi kolóniánkra, amíg ki nem derült, hogy tehetsége van a hajóépítéshez. Miután két csodálatos brigg épült a vezetésével a kolóniánk hajógyárában, megbocsátották neki a vétkeit, és most már teljes jogú tagja a társadalmunknak.";
	
	string STR_TRADER[MAX_RUMOURS_ABOUT_OWNERS]; // Магазинщики
	STR_TRADER[0] = "Semmi rosszat nem mondhatok róla. Tisztességes polgár, gyakran látogatja kápolnánkat. Úgy tûnik, az emberek kedvelik ôt. Soha nem hallottam, hogy bárki haragudott volna rá.";
	STR_TRADER[1] = "Ô a kormányzónk fô szállítója, és ez jó jövedelmet biztosít neki. De tisztességesen intézi az ügyeit. Legalábbis még nem tûnt fel semmi számára szégyenteljes dologban.";
	STR_TRADER[2] = "Ezt a kövér embert nagy tisztelet övezi városunkban. Az áruja mindig kiváló, és nem emlékszem egyetlen esetre sem, hogy valaha is becsapott volna valakit.";
	STR_TRADER[3] = "Ô tényleg semmire sem jó. Kereskedik, de semmi értelme. Néha egy áru elfogyott, néha egy másik, néha egy fél áru... Még az adósságokból sem tudja kiváltani magát.";
	STR_TRADER[4] = "Nem jó ember, uram. Úgy hallottam, hogy ô volt Piere Thiers jobb keze, korábbi kereskedô, de tönkretette az üzletét, majd megvette a boltot. Nem tudom, hogy milyen minôségû árut árul, de mint ember nagyon kellemetlen számomra.";
	STR_TRADER[5] = "Ó! Ô egy csúnya ember, nem tanácsolnám, hogy üzletelj vele\nVárosunk lakóinak felét adósságban tartja! És az áruk, amiket a boltjában árul, mindig rossz minôségûek.";
	STR_TRADER[6] = "Senki sem tud róla semmit. Nemrég költözött ide, és azonnal megnyitotta az üzletét. Tisztességesen kereskedik, nem bukott le csempészésen.";
	
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
