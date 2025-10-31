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
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l1 = "Nézze meg ezeket a fülbevalókat, monsieur. Egy bandita zsebében találtam a dzsungelben. Egyértelmûen egy kiváló ékszerész munkája, aki biztos vagyok benne, hogy nem ebbôl a vadonból való. Mit szól hozzá?";
                link.l1.go = "Sharlie_junglejew";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskiper")
			{
				link.l1 = "Tudom, hogy van egy Folke Deluc nevû adósa. Mondja csak, mennyire súlyos a... tartozása?";
                link.l1.go = "Sharlie";
			}	
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipermoney")
			{
				link.l1 = "Folke Deluc adóssága miatt vagyok itt.";
                link.l1.go = "Sharlie_repeat";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "bankskipercaptive")
			{
				link.l1 = "Elvégeztem a feladatát, uram. Itt van az ön... spanyol barátja.";
                link.l1.go = "Sharlie_14";
			}
			//<-- Бремя гасконца */
			
			//--> Миниквест "Делюк" (Делюк снова попал в тюрьму)
			if (CheckAttribute(pchar, "questTemp.Del_Rostovshik"))
			{
				link.l1 = "Azért jöttem, hogy...";
                link.l1.go = "Del_Deluck";
			}
			if (CheckAttribute(pchar, "questTemp.Del_Rostovshik_repeat"))
			{
				dialog.text = "Hozott 40 dublont?";
				if (PCharDublonsTotal() >= 40)
				{
					link.l1 = "Itt van a pénz a tisztemnek...";
					link.l1.go = "Del_Deluck_5";
				}
				link.l2 = "Nem, még gondolkodom.";
				link.l2.go = "exit";
			}
			//<-- Миниквест "Делюк"
		break;
		
		case "Sharlie":
			DelLandQuestMark(npchar);
			dialog.text = "És miért érdekel ez téged, ha megkérdezhetem?";
			link.l1 = "Szükségem van rá, hogy ez az ember szabad legyen, ne rácsok mögött. És amennyire értesültem, amíg ezt az adósságot nem kapja vissza, addig nem engedik szabadon, engem érdekel, hogy kifizessem ezt az adósságot.";
			link.l1.go = "Sharlie_1";
		break;
		
		case "Sharlie_1":
			dialog.text = "Aha, ez mindent megváltoztat. Az is érdekel, hogy a pénzemet visszakapjam... Ez a Folke Deluc egy furcsa fickó. Viszonylag kis összeget kért kölcsön - ötezer pezót. Csak nem akarta visszaadni, és elkezdett bujkálni. Végül a kamatok egészen az eredeti tartozás áráig szaladtak fel, és rács mögött találta magát.";
			link.l1 = "Ebbôl következik, hogy az adóssága jelenleg tízezer?";
			link.l1.go = "Sharlie_2";
		break;
		
		case "Sharlie_2":
			dialog.text = "Pontosan tízezer-négyszázötven pezó, uram. Tehát a szabadsága ennyibe kerül. Hajlandó kifizetni nekem? Kicsit meglepôdtem...";
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = "Ne lepôdjön meg. Itt a pénz.";
				link.l1.go = "Sharlie_3";
			}
			link.l2 = "Hm... Valóban komoly összeg. Figyeljen, uram, talán meg kellene próbálnunk megegyezni? Például, van valamije, amit én el tudnék intézni, és ön értékelhetné a szívességemet ezen a tízezerötszáz...";
			if (CheckAttribute(pchar, "questTemp.Sharlie.FastStart")) link.l2.go = "Sharlie_5x";
			else link.l2.go = "Sharlie_5"; // Addon 2016-1 Jason пиратскаЯ линейка 1
		break;
		
		case "Sharlie_3":
			AddMoneyToCharacter(pchar, -10450);
			dialog.text = "Igen, úgy tûnik, hogy önnek valóban szüksége van erre a matrózra, ha hajlandó ennyi pénzt kiadni érte. Különben is, ez nem az én dolgom, ugye, monsieur? Itt van az ô adósságlevele, most már önnek joga van a tartozásához, és joga van pénzt kérni tôle. Nos, és természetesen kérvényezze a börtönbôl való szabadulását.";
			link.l1 = "Pontosan ezt akartam. Viszlát, "+npchar.name+"!";
			link.l1.go = "Sharlie_4";
		break;
		
		case "Sharlie_4":
			DialogExit();
			Log_Info("Kaptál egy adósságlevelet");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
			pchar.questTemp.Sharlie = "freeskiper";
			AddLandQuestMark(characterFromId("FortFranceJailOff"), "questmarkmain");
		break;
		
		case "Sharlie_5x": // Addon 2016-1 Jason пиратскаЯ линейка 1
			dialog.text = "Szívességet? Sajnos, nincs szükségem semmilyen szívességre tôled. Legalábbis egyelôre.";
			link.l1 = "Kár. Akkor el kellene hoznom a pénzt Folke-nak. Viszlát!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_5":
			dialog.text = "Kegyelem? Hm... Tudja, monsieur, ha tegnap jött volna, nemleges választ adtam volna, de most... igen, van valami, amit el kell intéznem, de figyelmeztetem, hogy ez elég veszélyes.";
			link.l1 = "Veszélyes mire?";
			link.l1.go = "Sharlie_6";
		break;
		
		case "Sharlie_6":
			dialog.text = "A drága életére, természetesen. Szóval gondolja át, mielôtt beleegyezik, és döntse el, hogy hajlandó-e ilyesmire vagy sem.";
			link.l1 = "Monsieur, a veszély nem idegen tôlem. Már sokszor kerültem veszélyes helyzetbe. Szóval, térjünk rá a részletekre. Amíg nem kell az egész erôd helyôrségét egyedül kiiktatnom, addig talán el tudom érni, amire olyan titokzatosan célozgat.";
			link.l1.go = "Sharlie_7";
		break;
		
		case "Sharlie_7":
			dialog.text = "Jól van. Akkor figyelj. Ma este néhány kalóz és egy fogoly elhagyja Le Francois kalózbarlangját, és a Le Marin-öbölbe megy. A fogoly egy spanyol tiszt, és az erôdítéstechnika nagy szakértôje. Az angolok fel akarják használni a saját céljaikra, ezért egy hadihajót küldenek, hogy elhozzák a férfit az öbölbôl\nA tiszt régi barátom, és nem akarom, hogy angol fogságba kerüljön. Nem kérhetem a helyi hatóságok segítségét, mert háborúban állunk Spanyolországgal. Ha több idôm lenne, felfogadnék olyan embereket, akik képesek lennének visszafoglalni a spanyolt... bocsánat, visszafoglalni a barátomat, de sajnos!\nTe vagy az egyetlen ember, akire rábízhatom ezt a munkát. El kell menned a Le Marin öbölbe és... rávenni a kalózokat, hogy adják át neked a foglyot. Kétlem, hogy sok együttmûködést fognak mutatni, úgyhogy ez rajtad múlik.";
			link.l1 = "Hány kalóz lesz a konvojban?";
			link.l1.go = "Sharlie_8";
		break;
		
		case "Sharlie_8":
			dialog.text = "Nem tudom. Talán ketten, talán hárman vagy négyen. Szóval, mit mondanál?";
			link.l1 = "Már mondtam neked 'a veszély nem idegen számomra' és tudom, melyik oldalról kell kardot ragadni.";
			link.l1.go = "Sharlie_10";
			link.l2 = "Hm. Igazad van, ez veszélyes. Nem fogok egyedül megtámadni egy kalózcsapatot.";
			link.l2.go = "Sharlie_9";
		break;
		
		case "Sharlie_9":
			dialog.text = "Ez a te döntésed. Ha úgy gondolod, hogy nem vagy alkalmas erre a feladatra, akkor jobb, ha azonnal visszautasítod. Akkor várni fogok Deluc adósságpénzére.";
			link.l1 = "Rendben, akkor... Elviszem neki a pénzt. Viszlát késôbb!";
			link.l1.go = "exit";
			pchar.questTemp.Sharlie = "bankskipermoney";
		break;
		
		case "Sharlie_10":
			dialog.text = "Nagyon jó. Ezt örömmel hallom. Akkor menjetek a Le Marin-öbölbe, a kalózok este héttôl hajnali négyig ott lesznek, ne hagyjátok ki ôket! És eszedbe se jusson hajót használni! Az ilyen akciók elijesztik ôket, sétáljatok oda a dzsungelen keresztül!\nHozd elém a foglyot, ha megtalálod, nyitva tartom az ajtót. Javaslom, hogy várj hajnali egyig, mielôtt visszatérsz a városba, mert el kell kerülnöd az ôrök' figyelmét. Legyetek óvatosak és sok szerencsét!";
			link.l1 = "Köszönöm! Nekem mindenképpen szükségem lesz egy kis szerencsére...";
			if (CheckAttribute(pchar,"equip."+GUN_ITEM_TYPE)) link.l1.go = "Sharlie_13";
			else link.l1.go = "Sharlie_11";
		break;
		
		case "Sharlie_11":
			dialog.text = "Várj egy percet! Látom, hogy nincs is fegyvered. Vegyél egyet az enyémbôl. Van hozzá néhány töltényem is. Azt hiszem, jól fog jönni.";
			link.l1 = "Igen, ez biztosan jól fog jönni. Köszönöm, uram.";
			link.l1.go = "Sharlie_12";
		break;
		
		case "Sharlie_12":
			Log_Info("Kaptál egy harci pisztolyt");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "pistol1");
			TakeNItems(pchar, "bullet", 20);
			TakeNItems(pchar, "gunpowder", 20);
			dialog.text = "És most menjen, Isten segítse!";
			link.l1 = "...";
			link.l1.go = "Sharlie_13";
		break;
		
		case "Sharlie_13":
			DialogExit();
			pchar.quest.Sharlie_captive_Tut.win_condition.l1 = "location";
			pchar.quest.Sharlie_captive_Tut.win_condition.l1.location = "Shore39";
			pchar.quest.Sharlie_captive_Tut.function = "Tutorial_Rest_Delay";
			pchar.quest.Sharlie_captive.win_condition.l1 = "HardHour";
			pchar.quest.Sharlie_captive.win_condition.l1.hour = 19.00;
			pchar.quest.Sharlie_captive.function = "Captive_Timer";
			SetFunctionTimerCondition("Captive_CreatePiratesOver", 0, 0, 1, false);
			AddQuestRecord("SharlieD", "1");
			pchar.questTemp.Sharlie = "bankskiperfight";
			pchar.questTemp.Sharlie.Captive = "true";
			pchar.questTemp.Sharlie.Captive.Name = GetFullName(npchar);
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			// Rebbebion, новые марки до места назначения
			QuestPointerToLoc("fortfrance_town", "reload", "gate_back");
			QuestPointerToLoc("fortfrance_exittown", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_01", "reload", "reload1_back");
			QuestPointerToLoc("martinique_jungle_02", "reload", "reload2_back");
			QuestPointerToLoc("martinique_jungle_03", "reload", "reload2_back");
		break;
		
		case "Sharlie_14":
			pchar.quest.Sharlie_captive1.over = "yes";
			pchar.quest.Sharlie_captive2.over = "yes";
			pchar.quest.Sharlie_captive3.over = "yes";
			// Rebbebion, новые марки до места назначения
			QuestPointerDelLoc("shore39", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_03", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_02", "reload", "reload1_back");
			QuestPointerDelLoc("martinique_jungle_01", "reload", "reload2_back");
			QuestPointerDelLoc("fortfrance_exittown", "reload", "reload3");
			QuestPointerDelLoc("fortfrance_town", "reload", "reload8_back");
			DelLandQuestMark(npchar);
			ref sld = characterFromId("CaptiveSpain");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", 5.0);
			sld.lifeday = 0;
			SetNationRelation2MainCharacter(FRANCE, RELATION_FRIEND);
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
			dialog.text = "Csodálatos! Nagyon örülök, hogy sikeresen megoldotta. Gondolom, nem kell tudnom a mûvelet részleteit, ugye?  Szóval, kedves spanyol vendégem most már biztonságban érezheti magát az otthonomban...";
			link.l1 = "Mi van Folke Deluc adósságával?";
			link.l1.go = "Sharlie_15";
		break;
		
		case "Sharlie_15":
			dialog.text = "Természetesen, igen. Vegye el az adósságlevelét, most már joga van az adósságához, és joga van pénzt kérni tôle. Nos, és persze, kérvényezze a börtönbôl való szabadulását. Mindent megtettem, amit ígértem?";
			link.l1 = "Igen, uram. Minden szigorúan a megállapodás szerint történt. Most pedig engedje meg, hogy távozzak.";
			link.l1.go = "Sharlie_4";
			AddQuestRecord("SharlieD", "7");
			CloseQuestHeader("SharlieD");
			DeleteAttribute(pchar, "questTemp.Sharlie.Captive");
		break;
		
		case "Sharlie_repeat":
			dialog.text = "Szóval, kész kifizetni az adósságát?";
			if (sti(pchar.money) >= 10450)
			{
				link.l1 = "Igen. Itt a pénz.";
				link.l1.go = "Sharlie_3";
			}
			link.l2 = "Sajnos, még mindig nem sikerült összegyûjtenem a szükséges összeget...";
			link.l2.go = "exit";
		break;
		
		case "Sharlie_junglejew":
			dialog.text = "Hm. Úgy tûnik, igazad van, ezek drága fülbevalók, és biztosan az Óvilágban készültek... Mit is mondhatnék? Adok érte harminc... nem is harmincöt aranydublont. Fogadd el a pénzt, többért nem adod el ôket.";
			link.l1 = "Harmincöt dublont? Ez nem is rossz ár. Egyetértek. Tessék.";
			link.l1.go = "Sharlie_junglejew_1";
			link.l2 = "Nem. Azt hiszem, ezeket a fülbevalókat inkább magamra hagyom.";
			link.l2.go = "exit";
			npchar.quest.junglejew = "true";
		break;
		
		case "Sharlie_junglejew_1":
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info("Odaadtad a fülbevalót");
			RemoveItems(pchar, "jewelry25", 1);
			TakeNItems(pchar, "gold_dublon", 35);
			AddQuestRecord("SharlieE", "3");
			CloseQuestHeader("SharlieE");
			DeleteAttribute(pchar, "questTemp.Sharlie.Junglejew");
			if(!CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			}
		break;
		
		//--> Миниквест "Делюк"
		case "Del_Deluck":
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik");
			dialog.text = "Tudom, tudom, kapitány. Úgy tûnik, a navigátora szinte minden francia gyarmaton adósságot halmozott fel. Az igazat megvallva, már régóta tisztában voltam vele. Megkérdeztem a kollégáimat, ez a szokásos eljárás, tudja...";
			link.l1 = "És ön nem tartotta elég fontosnak ahhoz, hogy tájékoztasson engem az elôzô megállapodásunk során?";
			link.l1.go = "Del_Deluck_2";
		break;
		
		case "Del_Deluck_2":
			dialog.text = "Miért nem? Akkoriban elsôsorban Deluc adósságával foglalkoztam, ami egyébként a legnagyobb volt. Amint ezt rendezte, azonnal értesítettem a kollégáimat... Hivatásos futárok hatalmas flottája áll rendelkezésünkre, így nem tartott sokáig, mire Deluc számláiból egy halom gyûlt össze az asztalomon.";
			link.l1 = "Értem... Megvetted ôket, tudván, hogy életbevágóan fontos nekem, és tudod, hogy fizetni fogok érte... Ez zsarolás, Monsenior.";
			link.l1.go = "Del_Deluck_3";
		break;
		
		case "Del_Deluck_3":
			dialog.text = "It's just my job, Captain! Your navigator's total debt as of today amounts to 40 doubloons, and, mind you, interest is accruing... Will you be paying?";
			link.l1 = "Még nem állok készen a válaszra, de megfontolom. Viszontlátásra!";
			link.l1.go = "Del_Deluck_4";
		break;
		
		case "Del_Deluck_4":
			DialogExit();
			
			pchar.questTemp.Del_Rostovshik_repeat = true;
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.dialog.currentnode = "Del_Deluck";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
		break;
		
		case "Del_Deluck_5":
			dialog.text = "Kitûnô! Tudod, mit kell tenned - ugyanúgy, mint legutóbb. Itt vannak a dokumentumok - mutassa be a börtönparancsnoknak. Öröm volt önnel üzletelni, kapitány.";
			link.l1 = "Nem sok örömöm van ebben a helyzetben. Viszontlátásra.";
			link.l1.go = "exit";
			RemoveDublonsFromPCharTotal(40);
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik_repeat");
			Log_Info("Kaptál egy adósságlevelet");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_usurer");
			pchar.questTemp.Del_DeluckSvoboda = true;
			AddLandQuestMark(characterFromId("FortFranceJailOff"), "questmarkmain");
			DelLandQuestMark(npchar);
		break;
		//<-- Миниквест "Делюк"
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
