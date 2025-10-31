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
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "ToGovernor")
			{
				link.l1 = "Felség, kiváló és sürgôs híreim vannak a számodra! Elfogtam Bartolomeo portugált, a fattyú ôrségben van, és tisztességes tárgyalást vár! Én pedig a Társaság szerény háláját várom...";
				link.l1.go = "Portugal";
			}
			//Португалец
			
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "governor")
			{
				link.l1 = "Mynheer kormányzó úr, ön ragaszkodott hozzá, hogy találkozzunk...";
				link.l1.go = "FMQN";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_battle_complete")
			{
				link.l1 = "Az angol kémek ügyében vagyok itt, Mynheer kormányzó...";
				link.l1.go = "FMQN_7";
			}
		break;

		case "Cupture_after":
            dialog.text = RandPhraseSimple("Már mindent elvettél. Mit akarsz még?", "Maradt még valami, amit nem vittél el?");
            link.l1 = RandPhraseSimple("Csak körülnézek...", "Csak ellenôrzöm, hátha elfelejtettem valamit...");
            link.l1.go = "exit";
            NextDiag.TempNode = "Cupture_after";
		break;
		
		//Jason, Португалец
		case "Portugal":
			dialog.text = "Bartolomeo... Bart, a portugál a városomban van?! Élve?!";
			link.l1 = "Igen, felség, és megbízható ôrségben van. Átadom neked, miután megkaptam a számlát Bart fejérôl, amit a Társaság ígért. Az arany dublonok is megfelelnek...";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			dialog.text = "Számla, dublonok? Megôrültél?! Mit gondoltál, hogy ezt a szörnyeteget a városomba hozod?! Ha itt van, akkor a fregattja nincs messze a szigettôl, és a legénysége akár a városban is lehet, most rögtön!";
			link.l1 = "Megöltem azokat, akik vele voltak, a többiekrôl nem tudok, de ez nem igazán számít, azt hiszem, mert Bartolomeo...";
			link.l1.go = "Portugal_2";
		break;
		
		case "Portugal_2":
			dialog.text = "De igen! Hát nem érted, hogy mit tettél?! A 'Albatrosz' a sziget közelében van, és te elfogtad a kalózt, akinek brutalitása még a saját vérszomjas népét is megrémíti! Tûnjetek el innen! Tûnjetek el a szigetrôl! És vidd magaddal ezt a szörnyeteget!";
			link.l1 = "De figyelj, mi lesz a beígért jutalommal és...";
			link.l1.go = "Portugal_3";
		break;
		
		case "Portugal_3":
			dialog.text = "Nem akarom végignézni, ahogy a városom a ti kapzsiságotok és a Cég bosszúszomja miatt lángol! Csak friss újoncok vannak az erôdömben, és a felük elmenekül, amint megtudják, hogy ki és miért támadja a ravelinjeiket! És akkor kezdôdik a mészárlás... Nem fogom megkockáztatni, halljátok?! Tûnj el, és szállítsd el ôt Curacaóba te magad, ha a Cég ennyire akarja a fejét!\nTedd meg azonnal, mielôtt túl késô lenne! És azt csinálsz vele, amit akarsz, akár ki is dobhatod a hajód fedélzetérôl, csak ne az én városomban tedd!\nHans! Hans, hol vagy, te lusta idióta! Hozz nekem egy valeriána fôzetet vagy valamit, és valaki, az isten szerelmére, dobja ki ezt a kalandort a rezidenciámból!";
			link.l1 = "De felséged...";
			link.l1.go = "Portugal_4";
		break;
		
		case "Portugal_4":
			DialogExit();
			DoQuestReloadToLocation("Marigo_town", "reload", "reload3_back", "PortugalOutResidence");
		break;
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "Rendben van! Mondja kapitány, találkozott angol katonai vagy kereskedelmi hajóval, amikor a szigetünkhöz közeledett?";
			link.l1 = "Nem, Mynheer. Nem láttam sem katonai, sem kereskedelmi hajókat angol zászló alatt a vizeiken.";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "Értem. Meddig szándékozik itt maradni?";
			link.l1 = "Körülbelül három napot...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			dialog.text = "Ebben az esetben van egy ajánlatom az Ön számára. A hírszerzésünk szerint fennáll a veszélye, hogy angol kémek vannak itt. Tízezer pezót adok jutalomként minden olyan információért, amely gyanús hajókra és emberekre vonatkozik a szigeten belül, a városban, annak környékén, a partokon stb. A jutalom jelentôsen megemelkedik abban az esetben, ha a hatóságoknak segítséget nyújtanak egy ellenség elfogásában vagy likvidálásában.\nMinden civil kapitányt szívesen látunk, aki részt vesz a nyomozásban, és a kémek felkutatására portyázik a helyi partokon és a dzsungelben.\nElképzelhetô, hogy találkoznak katonai korvettünkkel, a Zeeparddal, ne féljenek, az éppen járôrözik. Szabadon megszólíthatjátok a kapitányát, ha megtaláljátok a briteket.";
			link.l1 = "Sajnos, az ön kiválósága, de én csak békés kereskedelmi szándékkal vagyok itt. El kell hagynom ezt a szigetet, amint feltöltöttem a készleteimet és befejeztem az itteni dolgaimat.";
			link.l1.go = "FMQN_3";
			link.l2 = "Csábító ajánlat! Azt hiszem, kiveszem a részem, és feldúlom a szigetetek vizeit és partjait. Talán még itt is maradok egy ideig.";
			link.l2.go = "FMQN_5";
		break;
		
		case "FMQN_3":
			dialog.text = "Ez csak információ a semmiért, kapitány. Semmi nyomás. Tudja, kihez fordulhat, ha bármi gyanúsat észlel.";
			link.l1 = "Rendben van, Mynheer, értettem. Viszontlátásra!";
			link.l1.go = "FMQN_4";
		break;
		
		case "FMQN_4":
			DialogExit();
			pchar.questTemp.FMQN = "way_eng_1";
			AddQuestRecord("FMQ_Nevis", "8");
			chrDisableReloadToLocation = false;
			FMQN_SetSoldiersInCave();
		break;
		
		case "FMQN_5":
			dialog.text = "Nagyszerû, kapitány! Ha már ennyire komolyan gondolja, mindenképpen beszéljen a parancsnokunkkal is. Ô a felelôs a kémek elfogásáért, és további információkkal szolgálhat.";
			link.l1 = "Rendben, Mynheer. Megyek, meglátogatom.";
			link.l1.go = "FMQN_6";
		break;
		
		case "FMQN_6":
			DialogExit();
			pchar.questTemp.FMQN = "way_div";
			AddQuestRecord("FMQ_Nevis", "9");
			chrDisableReloadToLocation = false;
			AddLandQuestMarkToPhantom("marigo_prison", "marigoJailOff");
		break;
		
		case "FMQN_7":
			DelLandQuestMark(npchar);
			dialog.text = "Már vártunk rád, Mynheer "+GetFullName(pchar)+". Hadd fejezzem ki hálánkat a veszélyes angol portyázó csapat likvidálásáért. Fogadjátok el ezt a tízezer pezót. Ezen kívül: 200 hajóselymet rakodunk a hajód rakterébe, és egy nagyon különleges jutalmat - a Holland Nyugat-indiai Kereskedelmi Társaság három évre szóló engedélyét. Ez egy rendkívül értékes dokumentum, remélem, tudod ezt?";
			link.l1 = "Természetesen! Egy három évre szóló engedély - ez biztosan nagy dolog.";
			link.l1.go = "FMQN_8";
		break;
		
		case "FMQN_8":
			dialog.text = "Kérem, vegye el a jutalmát. Emellett számíthat az összes holland állampolgár és hatóság hálájára. Ön szenzáció Philipsburgban, örülnénk, ha újra látnánk.";
			link.l1 = "Ilyen meleg szavakat hallani értékesebb, mint a jogosítvány. Köszönöm, öröm volt. És most már mennem kell. Viszontlátásra!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandBattleComplete");
		break;
		
		// Jason НСО
		case "tomas":
			dialog.text = "Megadjuk magunkat! Minden szent nevében kérlek benneteket, ne fosztogassátok és ne fosztogassátok Philipsburgot és polgárait! Kész vagyok meghallgatni a követeléseiket!";
			link.l1 = "Ne aggódjon a polgárok miatt, Mynheer. A francia korona alattvalóinak nem kell félniük a francia katonáktól.";
			link.l1.go = "tomas_1";
		break;
		
		case "tomas_1":
			dialog.text = "A francia korona?";
			link.l1 = "Pontosan. Ez a sziget Franciaországé, és önök itt csak bérlôk. Pimasz bérlôk, akik azt hitték, hogy ez a sziget az ô tulajdonuk lehet. A mai naptól kezdve a holland fennhatóság Saint Maartenen megszûnt. Világos?";
			link.l1.go = "tomas_2";
		break;
		
		case "tomas_2":
			dialog.text = "De... De mi lesz velünk, a holland katonákkal, akik megadták magukat, és a sebesültekkel? És mi lesz...";
			link.l1 = "Ez csak önön múlik, Mynheer Thomas. Ha megteszel nekem egy szívességet, akkor megengedem mindazoknak, akik feladták, hogy fogják a sebesültjeiket, és elinduljanak innen egy vagy több hajón, amelyet a dokkokban találunk, Curacaóba, Mynheer Stuyvesanthoz.";
			link.l1.go = "tomas_2_1";
		break;
		
		case "tomas_2_1":
			dialog.text = "";
			link.l1 = "Ellenkezô esetben a hajóim rakterében és a Saint Kitts-i kazamatákban fogtok maradni. Emellett néhány fontos holland tisztviselôt fel kell majd akasztani, csak hogy Stuyvesant elveszítse az érdeklôdését a gyarmataink meghódítása iránt...";
			link.l1.go = "tomas_3";
		break;
		
		case "tomas_3":
			dialog.text = "(dadogás) Mi... Mi... mi... a k-fajta f-fa... vour?";
			link.l1 = "A sziget mélyén fekszik egy vitás csont - egy sóbánya. Tudom, hogy nemcsak bányászok és rabszolgák vannak ott, hanem holland katonák is, állig felfegyverkezve. Biztosan a Társasági Gárdától vannak, nem igaz, Mynheer? Felajánlom nekik, hogy adják meg magukat, vagy erôszakot alkalmazok, ha visszautasítják. Szükségem van egy vezetôre, aki megmutatja az utat a bányához. Találj nekem egy ilyen vezetôt.";
			link.l1.go = "tomas_4";
		break;
		
		case "tomas_4":
			dialog.text = "S-só....m-bánya?";
			link.l1 = "Pontosan. Ne félj, Mynheer Thomas, ha a bánya ôrei elég bölcsek ahhoz, hogy feladják a fegyvereiket, lehetôséget adok nekik, hogy elhagyják a szigetet. Nincs szükségem felesleges vérontásra. Ne aggódj, a lelkiismereted tiszta lesz: még ha nem is mondod meg, hol van a bánya, Saint Maarten szigete elég kicsi ahhoz, hogy a segítséged nélkül is megtaláljam a bányát, csak nem akarom az idômet pazarolni, sûrûkön és mocsarakon bolyongva. Szóval ez az üzlet neked jobban megéri, mint nekem.";
			link.l1.go = "tomas_5";
		break;
		
		case "tomas_5":
			dialog.text = "F-fi...ne, elmondom, hogyan juthatsz el a bányához, de a szavadat kell adnod, hogy mindannyian... mindannyian elhagyjuk ezt a szigetet!";
			link.l1 = "A szavamat adom, mint tiszt és mint nemes.";
			link.l1.go = "tomas_6";
		break;
		
		case "tomas_6":
			dialog.text = "A Grand Case-öbölben... a túlsó szélén, a víz mellett, ott vannak... ott vannak kövek. Ott ... ott, mögöttük, a part mentén, van egy átjáró a víz mentén, ott ... ott sekély van, derékig érô vagy annál is mélyebb. Meg kell kerülni a sziklát, és egy nagy partra jutsz, ahol ... ahol nem tudsz kikötni a hajóddal, mert zátonyok vannak körülötte. Errôl a partról egy ösvény vezet egyenesen ... ... a bányához.";
			link.l1 = "Kitûnô. Elindulok. Te pedig, Mynheer, itt maradsz a katonáim szorgalmas ôrizete alatt, amíg vissza nem térek.";
			link.l1.go = "tomas_7";
		break;
		
		case "tomas_7":
			DialogExit();
			SetReturn_Gover_Dialog_Exit(NPChar);
			LAi_SetActorType(npchar);
			pchar.quest.Patria_BastionGate.win_condition.l1 = "location";
			pchar.quest.Patria_BastionGate.win_condition.l1.location = "Shore40";
			pchar.quest.Patria_BastionGate.function = "Patria_BastionShore";
			AfterTownBattle();
			AddQuestRecord("Patria", "50_1");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
