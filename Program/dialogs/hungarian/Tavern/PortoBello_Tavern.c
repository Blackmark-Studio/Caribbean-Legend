// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdései vannak?", "Miben segíthetek, " + GetAddress_Form(NPChar) + "?"), "Nemrég próbáltál feltenni nekem néhány kérdést, " + GetAddress_Form(NPChar) + "...", "Az egész nap folyamán ez a harmadik alkalom, hogy valamilyen kérdésrôl beszélsz...",
                          "További kérdések, gondolom?", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Jelenleg nincs mirôl beszélnem."), "Umph, hová tûnt a memóriám...",
                      "Igen, ez tényleg a harmadik alkalom...", "Nem, milyen kérdéseket?...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";			
			if (pchar.questTemp.Slavetrader == "FindRatPortobello")
            {
                link.l1 = "Figyelj, láttál már egy Francois Gontier nevû kalózt? Nemrég járt itt a városban.";
                link.l1.go = "Portobello_rat_1";
            }			
			// карибские нравы
			if (CheckAttribute(pchar, "questTemp.Trial") && pchar.questTemp.Trial == "spy" && !CheckAttribute(npchar, "quest.trial"))
            {
                link.l1 = "Figyeljen, meg tudná mondani, hol találok egy Jaime Silicio nevû kereskedôt? Úgy volt, hogy meglátogatja magát...";
                link.l1.go = "trial";
            }
			// Addon-2016 Jason ФМК-Гваделупа
			if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG == "headhunter_portobello" && !CheckAttribute(npchar, "quest.FMQG"))
            {
                link.l1 = "Nézze, egy Bertrand Pinette nevû embert keresek, hallott róla? Nemrég érkezett Portobellóba. Egy impozáns úriember, göndör parókában. Egy kereskedô. Lehet, hogy itt járt...";
                link.l1.go = "FMQG";
            }
			//--> Письмо от покойника
			if (CheckAttribute(pchar, "questTemp.LFD_Tavern_1"))
            {
                link.l1 = "Meg tudnád mondani, hol találom Marisa Calderát?";
                link.l1.go = "LFD_Tavern_1_1";
            }
			//<-- Письмо от покойника
		break;
		
		case "Portobello_rat_1":
			dialog.text = NPCStringReactionRepeat("Nem, nem tudom. Nem járt a kocsmában, és a városban sem láttam.", "Errôl már kérdeztél, és én már válaszoltam neked.", "Mondtam neked 'már kérdeztél errôl Gontier'.", "Figyelj, menj el, és ne zaklass engem! Teljesen elment az eszed?", "block", 0, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Nos, akkor tovább keresgélek.", "Hm, azt hiszem...", "Igen, persze, ezt már kérdeztem...", "Bocsánat, " + npchar.name + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		break;		

		case "trial":
			DelLandQuestMark(npchar);
			npchar.quest.trial = true;
			
			dialog.text = "Bocsásson meg, senor, de csak egy áruló vagy egy részeges beszélgetne ilyen dolgokról egy idegennel. Nem akarok semmi bajt.";
			link.l1 = "Részeges, azt mondja? Viszlát, haver.";
			link.l1.go = "exit";
		break;
		
		// Addon-2016 Jason ФМК-Гваделупа
		case "FMQG":
			dialog.text = "Sosem hallottam róla, haver.";
			link.l1 = "Ô don Carlos de Milyar egyik ismerôse. Biztos, hogy nem hallott róla?";
			link.l1.go = "FMQG_1";
		break;
		
		case "FMQG_1":
			dialog.text = "De igen. Ha ô de Milyar barátja - menjen el a kormányzóhoz, és kérdezze meg Carlos szenior urat. Ô majd mesél neked errôl a kereskedôdrôl.";
			link.l1 = "Megteszem. Köszönöm a tanácsot!";
			link.l1.go = "FMQG_2";
		break;
		
		case "FMQG_2":
			DialogExit();
			AddQuestRecord("FMQ_Guadeloupe", "9");
			npchar.quest.FMQG = true;
		break;
		
		//--> Письмо от покойника
		case "LFD_Tavern_1_1":
			dialog.text = "Marisát? Hm... Régóta nem láttam őt. Amióta hírt kapott férje haláláról, nem mutatkozott a városban.";
			link.l1 = "Akkor ő özvegy?";
			link.l1.go = "LFD_Tavern_1_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LFD_Tavern_1_2":
			dialog.text = "Igen. A férje a 'Hullámtörő' nevű kereskedelmi pinas kapitánya volt. A Holland Nyugat-Indiai Társaság engedélyének köszönhetően szinte minden kikötő nyitva állt előtte a szigetcsoporton. Azt beszélik, nem élte túl a kalóztámadást, amikor Belize-ből Capsterville felé hajózott. Ez errefelé nem szokatlan, de számára ez súlyos csapás volt.";
			link.l1 = "És csak úgy eltűnt?";
			link.l1.go = "LFD_Tavern_1_3";
		break;
		
		case "LFD_Tavern_1_3":
			dialog.text = "Nos, eltűntnek nevezni túlzás lenne. De azóta alig látták a városban. Furcsa mód... időnként különféle férfiak érdeklődnek utána. Ahogy most te is, kapitány. Ha nem lenne olyan vallásos, azt hinném, hogy... elrejtőzött az emberek szeme elől, és úgy keresi a kenyerét, ahogy tudja. De Marisa, mielőtt a férje meghalt, egy misét sem hagyott ki – gyakorlatilag az egyházban élt, szóval ez aligha valószínű.";
			link.l1 = "Ennyi lenne? Nem tudsz róla többet?";
			link.l1.go = "LFD_Tavern_1_4";
		break;
		
		case "LFD_Tavern_1_4":
			dialog.text = "Amit tudtam, kapitány, már elmondtam.";
			link.l1 = "...";
			link.l1.go = "LFD_Tavern_1_5";
		break;
		
		case "LFD_Tavern_1_5":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Tavern_1");
		break;
		//<-- Письмо от покойника
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
