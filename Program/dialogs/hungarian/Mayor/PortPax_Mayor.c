// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Mit akarsz? Kérdezzen csak.", "Figyelek rád, mi a kérdés?"), "Már másodszor próbálsz kérdezni...", "Ez a harmadik alkalom, hogy megpróbálod megkérdezni...",
                          "Mikor lesz ennek vége?! Elfoglalt ember vagyok, gyarmati ügyekkel foglalkozom, és te még mindig zaklatsz!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam...", "Ne most. Rossz helyen és rossz idôben."), "Igaz... De késôbb, nem most...",
                      "Megkérdezem... De egy kicsit késôbb...", "Sajnálom, " + GetAddress_FormToNPC(NPChar) + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_2" && !CheckAttribute(npchar, "quest.patria") && !CheckAttribute(pchar, "questTemp.Patria.Visiter_Late"))
			{
				link.l1 = TimeGreeting()+" Monsieur. Chevalier de Poincy fôkormányzó parancsára vagyok itt. Az a feladatom, hogy Tortugára szállítsak egy Noel Forget nevû bárót, aki az anyaországból érkezett azzal a feladattal, hogy ellenôrizze a gyarmatokat, fô célja egy francia nyugat-indiai kereskedelmi társaság alapítása. Hadd mutassam be önnek... Minden részletet ô maga fog elmagyarázni.";
                link.l1.go = "patria_portpax";
			}
			// Rebbebion, квест "Путеводная звезда"
			if (CheckAttribute(pchar, "questTemp.PZ.PortPaxMayorTalk"))
			{
				link.l1 = "Uraságod, látni akartál?";
				link.l1.go = "PZ_1";
			}
			// Украденное воспоминание
			if (CheckAttribute(pchar, "questTemp.UV_DialogMayor"))
			{
				link.l1 = "Excellenciás uram, egy nagyon érzékeny természetû információval érkeztem, ami az ön figyelmét igényli.";
				link.l1.go = "UV_1";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("Már mindent elvettél. Mit akarsz még?", "Maradt még valami, amit nem vittél el?");
            link.l1 = RandPhraseSimple("Csak körülnézek...", "Csak ellenôrzöm, hátha elfelejtettem valamit...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		// Jason НСО
		case "patria_portpax":
			dialog.text = "Nagyon örülök, hogy megismerhetem önöket, Charles de Maure kapitány és a báró. Mindent megteszek, hogy Monsieur Forget tartózkodása a gyarmatunkon a lehetô legkényelmesebb legyen. És kihasználva azt a tényt, hogy egy ilyen magas rangú úr meglátogatott engem, egy dologban kérni fogom önt.";
			link.l1 = "Nagyon érdekes! Meséljen nekünk az ügyérôl, kegyelmes uram.";
			link.l1.go = "patria_portpax_1";
		break;
		
		case "patria_portpax_1":
			dialog.text = "Az elmúlt hónapokban a fôkormányzó egyetlen képviselôje sem látogatta meg a kolóniánkat, mintha teljesen megfeledkeztek volna rólunk Saint Kitts-en! És eközben a spanyolok, akik arra vágynak, hogy egész Hispaniolát tisztán spanyolokká tegyék, és akiknek a sziget nyugati részén élô francia telepesek és kalózok nagy bosszúságot okoznak, támadásra készülnek! Járôrtisztjeim, kereskedelmi kapitányaink, sôt egyszerû halászok is jelentették, hogy Santiagóban egy erôs spanyol hajóraj gyülekezik, amely Kikötô-au-Prince megtámadására készül!";
			link.l1 = "Elég egyértelmûek a bizonyítékok, felség?";
			link.l1.go = "patria_portpax_2";
		break;
		
		case "patria_portpax_2":
			dialog.text = "Nincsenek pontos információim, de ilyen sok információ teljesen véletlenszerû emberektôl nem lehet puszta pletyka. Gyarmatunk nagyon fontos Franciaország számára, itt vannak a legjobb ültetvényeink, amit a báró személyesen is láthat. Ezt a kolóniát elveszíteni, vagy akár a fosztogatás veszélyének kitenni elfogadhatatlan!";
			link.l1 = "Figyelembe fogom venni a bizonyítékaikat, és tájékoztatom Chevalier de Poincy-t. Biztos vagyok benne, hogy azonnal intézkedni fog.";
			link.l1.go = "patria_portpax_3";
		break;
		
		case "patria_portpax_3":
			dialog.text = "Köszönöm, kapitány...";
			link.l1 = "";
			link.l1.go = "patria_portpax_4";
		break;
		
		case "patria_portpax_4":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_9";
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "governor1");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			npchar.quest.patria = "true";
		break;
		
		case "PZ_1":
			DeleteAttribute(pchar, "questTemp.PZ.PortPaxMayorTalk");
			dialog.text = "Nem, nem én hívtam önt, monsieur. Akart valamit?";
			link.l1 = "Hogy is tehettem volna? De a hírnöke találkozott velünk; azt mondta, hogy elôkészítette nekem az egyik házat a városban...";
			link.l1.go = "PZ_2";
			DelLandQuestMark(npchar);
		break;
		
		case "PZ_2":
			dialog.text = "Miféle ház, miféle küldönc, mi ez a szemtelenség?!";
			link.l1 = "Hogy érti azt, hogy milyen hírnök... A neve Henri Thibaut, és...";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "MICSODA? Tudja egyáltalán, hogy ki ô? Úgy tûnik, nem. De ez nem számít. Mit keres Levasseur unokaöccse a városomban?";
			link.l1 = "Ó, Istenem...";
			link.l1.go = "PZ_4";
		break;
		
		case "PZ_4":
			dialog.text = "De Maure, hall engem? Uram, hall engem?";
			link.l1 = "...";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_5":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorRunToLocator(pchar, "reload", "reload1", "PZ_SharleBezhitObratno", -1);
			bDisableCharacterMenu = true;
			InterfaceStates.Buttons.Save.enable = false;
			SetMusic("music_teleport");
			pchar.questTemp.lockedMusic = true;
		break;
		
		//--> Украденное воспоминание
		case "UV_1":
			dialog.text = "Azt mondja, kényes ügy? Felkeltette az érdeklôdésemet, kapitány. Kérem, folytassa, teljes figyelmemet élvezi.";
			link.l1 = "Az ügy az unokahúgát, Julie-t érinti. Azért kérte a segítségemet, hogy visszaszerezzek egy nyakláncot, amit elloptak tôle.";
			link.l1.go = "UV_2";
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
			DelLandQuestMark(npchar);
		break;

		case "UV_2":
			dialog.text = "Egy nyakláncot? Kíváncsi vagyok. Nem emlékszem, hogy ilyen tárgy lett volna a birtokában.";
			link.l1 = "Engedje meg, hogy sorban ismertessem a tényeket, kormányzó úr. Sikeresen visszaszereztem a szóban forgó nyakláncot. A nyomozásom során kiderült, hogy a tolvaj az unokahúga szobalánya, Giselle volt. A kereskedôvel kapcsolatos megfigyeléseim alapján, aki a lopott tárgyat vásárolta, erôs a gyanúm, hogy ez nem az elsô és nem is az utolsó ilyen jellegû kihágása.";
			link.l1.go = "UV_3";
		break;

		case "UV_3":
			dialog.text = "Nagyon tanulságos. Kérem, folytassa a beszámolóját.";
			link.l1 = "Ami felkeltette a figyelmemet, excellenciás uram, hogy Julie nem az ön segítségét kérte ebben az ügyben. A nyaklánc, úgy tûnik, egy olyan személytôl kapta ajándékba, akivel Ön kifejezetten megtiltotta neki, hogy kapcsolatba lépjen. Mivel úgy gondolom, hogy az Ön korlátozásai a legbölcsebb és legvédôbb szándékból fakadnak, kötelességemnek éreztem, hogy felhívjam a figyelmét erre az ügyre, és közvetlenül Önnek adjam vissza a nyakláncot.";
			link.l1.go = "UV_4";
			TakeItemFromCharacter(pchar, "SM_necklace_Julie");
		break;

		case "UV_4":
			dialog.text = "Az ítélôképessége jónak bizonyul"+GetSexPhrase(", kapitány","")+". Dicsérem a megfontoltságát, hogy ezt közvetlenül hozzám intézte, ahelyett, hogy az unokahúgom ifjúkori indiszkrécióinak engedett volna.";
			link.l1 = "Csak az ô jólétét tartom szem elôtt, kormányzó úr. Nincs kétségem afelôl, hogy az ön útmutatásai is ugyanebbôl a forrásból fakadnak.";
			link.l1.go = "UV_5";
		break;

		case "UV_5":
			dialog.text = "Valóban, kapitány. Mint a nagybátyja és gyámja, az ô jóléte a legfôbb gondom. Kérem, fogadja el ezt a százötven dublont diszkréciója elismeréseként. Továbbá átadom neked ezt a navigációs iránytût is, hogy biztonságban vezessen téged a veszélyes vizeken való utazásod során.";
			link.l1 = "Megtisztel nagylelkûsége, excellenciás uram, bár ilyen jutalomra nem volt szükség. Sajnálatos módon most búcsút kell mondanom önnek - a dagály nem vár egyetlen tengerészre sem, és a hajóm megköveteli a figyelmemet.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("UV_End");
			AddItems(pchar, "gold_dublon", 150);
			GiveItem2Character(PChar, "compass1");
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
		break;
		//<-- Украденное воспоминание
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
