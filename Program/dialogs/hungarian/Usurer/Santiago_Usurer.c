// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdései vannak?", "Miben segíthetek?"), "Nemrég próbálta ezt a kérdést feltenni nekem...", "Igen, hadd találjam ki... Már megint körbe-körbe jársz?",
                          "Figyelj, én itt a pénzügyekkel foglalkozom, nem válaszolok kérdésekre...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Jelenleg nincs mirôl beszélnem."), "Umph, hová tûnt a memóriám...",
                      "Kitaláltad, sajnálom...", "Megértem...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит, Голландия
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "SantiagoTripBegin")
			{
				link.l1 = "Senior, én vagyok a kapitány " + GetFullName(pchar) + ", és Lucas Rodenburg megbízásából vagyok itt. Egy csomagot hoztam tôle önnek.";
				link.l1.go = "SantiagoTripBank";	
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "SantiagoTripReturn")
			{
				link.l1 = "Lucas Rodenburg válaszáért jöttem.";
				link.l1.go = "SantiagoTripBank_3";	
			}
			//Голландский гамбит, Голландия
		break;
		
		case "SantiagoTripBank":
			if (GetCharacterItem(pchar, "Chest") >= 5)
			{
			dialog.text = "Képzelje csak el... egy csomag! Nos, adja ide, rangidôs.";
			link.l1 = "Továbbá, Rodenburg rangidôs megkért, hogy adjam át önnek ezt...";
			link.l1.go = "SantiagoTripBank_1";
			RemoveItems(PChar, "NPC_Letter", 1);
			RemoveItems(PChar, "Chest", 5);
			DelLandQuestMark(npchar);
			}
			else
			{
			dialog.text = "Amennyire én tudom, a csomagon kívül még valami mást is meg kellett volna kapnom, kapitány. Szóval... hol van? Érti, mirôl beszélek?";
			link.l1 = "De hát persze! A ládák biztonságos ôrzés alatt vannak a hajómon. Azonnal átadom önnek.";
			link.l1.go = "exit";
			}
		break;
		
		case "SantiagoTripBank_1":
			dialog.text = "Hm-m... érdekes. Szóval ô 'küldi a sajnálkozását'. Nos-lássék. Bár, Rodenburg rangidôs sajnálkozása elég meggyôzô, nehéz tagadni. Senior, idôbe fog telni, amíg megírom a megfelelô választ, el tudna jönni holnap dél körül újra, hogy felvehesse a választ? Pihenjetek egy kocsmában, sétáljatok a városban. Santiago sok mindent kínál.";
			link.l1 = "Rendben, holnap dél körül visszajövök. Akkor találkozunk, senor.";
			link.l1.go = "SantiagoTripBank_2";
		break;
		
		case "SantiagoTripBank_2":
			DialogExit();
			pchar.quest.SantiagoTripOver.over = "yes"; //снять таймер
			bDisableFastReload = true;
			pchar.quest.Santiago_Trip.win_condition.l1 = "location";
			pchar.quest.Santiago_Trip.win_condition.l1.location = "Santiago_town";
			pchar.quest.Santiago_Trip.function = "SantiagoTrip_Attack";
			pchar.questTemp.HWIC.Holl = "SantiagoTripAttack";
			LAi_LocationDisableOfficersGen("Santiago_town", true);//офицеров не пускать // 291112
		break;
		
		case "SantiagoTripBank_3":
			dialog.text = "Igen, persze... de azt hiszem, hogy az írott konvenciók nélkül is boldogulhatunk. Csak mondja meg neki ezeket a szavakat 'ez az embernek meg kell halnia'. Ez lenne a tisztességes, és nem lesz semmi gondunk, figyelembe véve a 'érték' a kapott bocsánatkéréseket. És az esetet teljes mértékben elintézettnek tekintjük.";
			link.l1 = "Rendben, emlékezni fogok rá, senor. Még valami?";
			link.l1.go = "SantiagoTripBank_4";
			DelLandQuestMark(npchar);
		break;
		
		case "SantiagoTripBank_4":
			dialog.text = "Igen, természetesen. Amit mondtam, az a Giraldi család akarata. És természetesen átadhatja üdvözletemet Senor Lucasnak. Jó szelet kívánok, kapitány " + GetFullName(pchar) + ".";
			link.l1 = "Értem. Viszlát, rangidôs "+npchar.name+".";
			link.l1.go = "SantiagoTripBank_5";
		break;
		
		case "SantiagoTripBank_5":
			DialogExit();
			pchar.questTemp.HWIC.Holl = "SantiagoTripFinal";
			LAi_LocationDisableOfficersGen("Santiago_town", false);//офицеров пускать // 291112
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			AddMapQuestMarkCity("Villemstad", true);
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
