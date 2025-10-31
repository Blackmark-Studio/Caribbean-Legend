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
			//Jason, Бремя гасконца
			if (CheckAttribute(PChar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "hire" && !CheckAttribute(npchar, "quest.storehelper"))
			{
				link.l1 = "Figyelj, " + npchar.name + ", szokatlan ügyben jöttem hozzád. Olyan férfit keresek, aki szeretne egy csendes, békés életet élni az öbölben, mint kereskedôsegéd egy Saint-Pierre-i üzletben. A fizetés jó, és a tetô a feje fölött gondoskodik róla. Tudna ajánlani nekem valakit, akihez fordulhatnék?";
				link.l1.go = "storehelper";
			}
			if (CheckAttribute(PChar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "seabattle" && !CheckAttribute(npchar, "quest.seabattle") && pchar.location.from_sea == "LeFransua_town")
			{
				link.l1 = "A boroshordók miatt jöttem, amelyeket a hajómra akar rakodni, hogy Guadeloupe-ra szállítsák...";
				link.l1.go = "seabattle";
			}
			//Бремя гасконца
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "PortugalLeFransua" && !CheckAttribute(npchar, "quest.portugal") && Pchar.location.from_sea == "LeFransua_town")
			{
				link.l1 = "Tudja, " + npchar.name + ", egy barátomat keresem. Úgy volt, hogy ide érkezik, de nem érzi jól magát. Talán a barátai segítettek neki...";
				link.l1.go = "Portugal";
			}
			//Португалец
		break;
		
		case "storehelper":
			dialog.text = "Hm... Van itt néhány ember, aki szeretne átállni a tengerész életrôl a szárazföldi életre. Segíthetek, de már most megmondom: nem lesz ingyen.";
			link.l1 = "Heh! És mennyit akarsz?";
			link.l1.go = "storehelper_1";
		break;
		
		case "storehelper_1":
			dialog.text = "Ezer darab pesot. És nem kell semmit sem tenned, egy órán belül a kocsmámban lesznek a jelöltjeid a munkára, több jelölt. Beszélgethetsz majd velük, és kiválaszthatod azt, amelyik jobban tetszik neked, mint a többi.";
			if (sti(Pchar.money) >= 1000)
			{
				link.l1 = "Ahh... Rendben, tessék, vegyél egy ezrest!";
				link.l1.go = "storehelper_2";
			}
			link.l2 = "Sajnálom, de nincs ennyi pénzem!";
			link.l2.go = "storehelper_exit";
		break;
		
		case "storehelper_2":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Ne aggódj, haver. Ennek az összegnek a felét visszakapod a jelölttôl. Majd megmondom neki, hogy ez a te szolgáltatásaid ára, ô, ô, ô... Ötszáznál többet nem adnak. Egy óra múlva ugorj be a kocsmámba, addigra megtalálom azokat az embereket, akikre szükséged van, és itt várnak rád.";
			link.l1 = "Jól van. Egy óra múlva visszajövök, " + npchar.name + ".";
			link.l1.go = "storehelper_3";
			npchar.quest.storehelper = "true";
			DelLandQuestMark(npchar);
		break;
		
		case "storehelper_3":
			DialogExit();
			SetLaunchFrameFormParam("Egy óra telt el...", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0); //крутим время
			RecalculateJumpTable();
			Storehelper_hire("");
		break;
		
		case "storehelper_exit":
			dialog.text = "Sajnálom, hogy neked sincs ennyi pénzed. De tudod te magad is, az ilyen ügyeket nem csak egy 'köszönöm'. ért csinálják...";
			link.l1 = "Megértem. De tényleg nincs rá pénzem. Rendben, viszlát...";
			link.l1.go = "exit";
			//pchar.quest.storehelper.over = "yes";
			//AddTimeToCurrent(2,0);
			//DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
			//CloseQuestHeader("SharlieA");
		break;
		
		case "seabattle":
			DelLandQuestMark(npchar);
			dialog.text = "Mirôl beszélsz, haver? Milyen borról beszélsz?";
			link.l1 = "Egy Walter Elkapó nevû ember küldött magához. Azt mondta, hogy önnek szüksége van egy hajóra, hogy tízezer pezóért egy borszállítmányt szállítson Guadeloupe-ra. És hogy pontosan az én hajómra van szüksége ehhez a munkához...";
			link.l1.go = "seabattle_1";
			npchar.quest.seabattle = "true";
		break;
		
		case "seabattle_1":
			dialog.text = "Figyeljen, haver, én nem foglalkozom borral, nincs szükségem a szolgálataira, és nem ismerek semmilyen Walter Catchert.";
			link.l1 = "Hát ez meg mi a fene! Szóval azt a Catchert nem is maga küldte... Akkor mi ez az egész komédia?";
			link.l1.go = "seabattle_2";
		break;
		
		case "seabattle_2":
			dialog.text = "Heh! Nos, ez vagy valami tévedés, vagy egy rossz vicc, vagy...";
			link.l1 = "Vagy mi?";
			link.l1.go = "seabattle_3";
		break;
		
		case "seabattle_3":
			dialog.text = "Nem érted magadtól? Valakinek át kellett csalogatnia téged Le Francois-hoz, nem tudom miért. A maga helyében én sietnék, és eltûnnék innen, miközben a lehetô legóvatosabb lennék. Ez piszkos üzlet szaga van, haver...";
			link.l1 = "Azt hiszem, igaza van. Nem tetszett a Elkapó bögréje. Rendben, követem a tanácsát. Viszlát, Cesar!";
			link.l1.go = "seabattle_4";
		break;
		
		case "seabattle_4":
			DialogExit();
			AddQuestRecord("Sharlie", "16");
			pchar.quest.seabattle.win_condition.l1 = "location";
			pchar.quest.seabattle.win_condition.l1.location = "Martinique";
			pchar.quest.seabattle.function = "SharlieSeabattle_ship";
			
			pchar.quest.NewGameTip4.win_condition.l1 = "location";
			pchar.quest.NewGameTip4.win_condition.l1.location = "LeFransua_town";
			pchar.quest.NewGameTip4.function = "ShowNewGameTip";
			pchar.quest.NewGameTip4.text = "Jön az elsô tengeri csatád! Mentsd meg a játékot!";					  
		break;
		
		case "Portugal":
			dialog.text = "Igen, a barátja megérkezett, kapitány. Tegnap érkezett, és fent bérelt egy szobát. A társai is itt vannak, ô... Ott ülnek. Kérdezd meg ôket!";
			link.l1 = "...";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			DialogExit();
			AddDialogExitQuestFunction("Portugal_enterPirates");
			npchar.quest.portugal = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
