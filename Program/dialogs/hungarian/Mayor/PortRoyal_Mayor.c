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
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_8")
			{
				link.l1 = "Excellenciás uram, egy illegális kereskedelmi tevékenységet szeretnék bejelenteni ezen a szigeten.";
                link.l1.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_12")
			{
				link.l1 = "Szeretnék jelentést hallani a selyem vitorlavászon csempészettel kapcsolatos küldetésérôl.";
                link.l1.go = "Mtraxx_4";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_10_continue" && !CheckAttribute(npchar, "quest.slaveships"))
			{
				link.l1 = "Phillipe de Poincy fôkormányzó nevében érkeztem. Az a feladatom, hogy elhozzam önnek a hollandoktól elfogott rabszolgákat, igaz?";
                link.l1.go = "patria_Sl";
			}
			if (CheckAttribute(npchar, "quest.slaveships.wait") && GetSquadronGoods(pchar, GOOD_SLAVES) >= 3000)
			{
				link.l1 = "Elhoztam a rabszolgákat, ahogy megbeszéltük.";
                link.l1.go = "patria_Sl_2";
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_11_start" && CheckAttribute(pchar, "questTemp.Patria.Curacao.DoilyReady"))
			{
				link.l1 = "Phillipe de Poincy fôkormányzó utasítására érkeztem, hogy részt vegyek a hollandok elleni közös curacaói expedícióban.";
                link.l1.go = "patria_Sl_4";
			}
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_11_wait" && GetCompanionQuantity(pchar) < 3)
			{
				link.l1 = "A squardonom csökkent, most már elindulhatunk.";
                link.l1.go = "patria_Sl_6";
			}
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "Mtraxx":
            dialog.text = "Érdekes. Csupa fül vagyok.";
			link.l1 = "Biztos forrásból tudom, hogy egy holland brigantin, a 'Utrecht' angol színek alatt már régóta nagy mennyiségû selyemvitorlavászon kirakodását végzi a Portland-öbölben. Több mint egy éve mûködnek, éjszakai idôszakban, minden hónap 10. és 15. napja között.";
			link.l1.go = "Mtraxx_1";
		break;
		
		case "Mtraxx_1":
            dialog.text = "Biztos, hogy a forrása megbízható?";
			link.l1 = "Idônként még magamban sem bízom, azonban egy olyan ember, aki nyilvánosságra hozta ezt az információt, megbízható. Különben is, nem volt oka hazudni.";
			link.l1.go = "Mtraxx_2";
		break;
		
		case "Mtraxx_2":
			string sTemp = "ez";
			if (sti(pchar.questTemp.Mtraxx.month == 1)) sTemp = "következô";
            dialog.text = "Rendben, kapitány. Ez egy komoly ügy, és a bemutatott információ alapján kell cselekednem, még akkor is, ha az informátora hazudott, vagy egyszerûen csak tévedett. A megadott idôpontban parti ôrjáratot küldök, és ha az információi beigazolódnak, bôkezû jutalmat kap, az ilyen illegális tevékenységeket szigorúan el kell fojtani.";
			link.l1 = "Találkozunk "+sTemp+" hónap 16-án. Addigra biztosan megoldódik a helyzet.";
			link.l1.go = "Mtraxx_3";
		break;
		
		case "Mtraxx_3":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_11";
			int month = sti(pchar.questTemp.Mtraxx.month);
			pchar.quest.mtr_silk_smuggler.over = "yes";
			pchar.quest.mtr_silk_smuggler_over.over = "yes";
			DeleteQuestCondition("Mtraxx_SilkCreateSmuggler");
			DeleteQuestCondition("Mtraxx_SilkSmugglerFail");
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1 = "Timer";
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.hour  = 6;
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.day   = 16;
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.month = GetAddingDataMonth(0, month, 0);
			pchar.quest.mtr_silk_smuggler_patrol.win_condition.l1.date.year  = GetAddingDataYear(0, month, 0);
			pchar.quest.mtr_silk_smuggler_patrol.function = "Mtraxx_SilkSmugglerPatrol";
			sTemp = "ez";
			if (sti(pchar.questTemp.Mtraxx.month == 1)) sTemp = "következô";
			AddQuestRecord("Roger_2", "19");
			AddQuestUserData("Roger_2", "sDate", sTemp);
			if (CharacterIsAlive("Mtr_Utreht"))
			{
				sld = CharacterFromID("Mtr_Utreht");
				sld.lifeday = 0;
			}
		break;
		
		case "Mtraxx_4":
            dialog.text = "Az információi helyesnek bizonyultak, kapitány. A tranzakció során rajtaütöttünk a bûnözôkön. A 'Utrecht' megpróbált elmenekülni és harcolt, de a járôrkorvettünk elsüllyesztette. Négy vevô ellenállt a letartóztatásnak. Az egyiket egy lövéssel megölték, a másik három pedig a dzsungelbe menekült. A 80 tekercs selyem teljes rakományát átadták Port Royal kincstárának. Bár a hálózat vezetôjét nem sikerült meghatározni, a halottat nem sikerült azonosítani, a többiek pedig elmenekültek, az akciót teljes sikernek nyilvánítom. Kétlem, hogy ezek a gazemberek valaha is vissza mernek majd térni ide.\nNagy szolgálatot tett nekünk, kapitány, hogy szorgalmas volt, és rámutatott a csalókra. Itt van 10.000 pezó a jutalmad.";
			link.l1 = "Nagyon hálás vagyok, excellenciád. Örülök, hogy minden a terv szerint ment, és a csempészek megkapták, amit megérdemeltek. Ezzel búcsúzom, szép napot kívánok.";
			link.l1.go = "Mtraxx_5";
		break;
		
		case "Mtraxx_5":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_13";
			AddQuestRecord("Roger_2", "20");
			AddMoneyToCharacter(pchar, 10000);
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			ChangeCharacterNationReputation(pchar, ENGLAND, 5);
			AddCharacterExpToSkill(pchar, "Leadership", 200);
		break;
		
		// Jason НСО
		case "patria_Sl":
			if (GetSquadronGoods(pchar, GOOD_SLAVES) < 500)
			{
				dialog.text = "Ez pontos. Hány rabszolgát hoztál?";
				link.l1 = "Még dolgozom rajta. Hamarosan visszatérek az eredményekkel.";
				link.l1.go = "patria_Sl_wait";
				break;
			}
			dialog.text = "Ez pontos. Hány rabszolgát hoztál?";
			link.l1 = ""+FindRussianQtyString(GetSquadronGoods(pchar, GOOD_SLAVES))+".";
			if (GetSquadronGoods(pchar, GOOD_SLAVES) >= 3000) link.l1.go = "patria_Sl_2";
			else link.l1.go = "patria_Sl_1";
		break;
		
		case "patria_Sl_wait":
			DialogExit();
			npchar.quest.slaveships.wait = "true";
		break;
		
		case "patria_Sl_1":
			dialog.text = "Hmm, Chevalier azt ígérte, hogy nem kevesebb, mint 3000 rabszolga lesz...";
			link.l1 = "Igen, így van. Ez az én hibám: a rabszolgák egy része egy ellenséges hajó ágyútüze alatt halt meg, mások az úton haltak meg. Kijavítom a hibámat, és visszatérek hozzátok. Minden a szerzôdés szerint fog történni.";
			link.l1.go = "patria_Sl_wait";
		break;
		
		case "patria_Sl_2":
			DeleteAttribute(npchar, "quest.slaveships.wait");
			dialog.text = "Kiváló! Chevalier de Poincyval tényleg lehet üzletelni. Mondja meg a fôkormányzónak, hogy a Curacao elleni támadáshoz szükséges századom egy hónapon belül készen áll. Biztos vagyok benne, hogy erre a hadjáratra hozzám fogja küldeni, úgyhogy hamarosan találkozunk, Monsieur de Maure.";
			link.l1 = "Örülnék, ha újra találkozhatnánk, ezredes úr. És most hadd búcsúzzam el tôle.";
			link.l1.go = "patria_Sl_3";
		break;
		
		case "patria_Sl_3":
			DialogExit();
			npchar.quest.slaveships = "true";
			RemoveCharacterGoods(pchar, GOOD_SLAVES, GetSquadronGoods(pchar, GOOD_SLAVES));
			AddQuestRecord("Patria", "57");
			pchar.questTemp.Patria = "epizode_10_return";
			pchar.quest.Patria_SlaveShipsJamaicaTimeOver.over = "yes"; //снять таймер на доставку рабов
			SetFunctionTimerCondition("Patria_CuracaoDoilyReady", 0, 0, 30, false); // таймер на 1 месяц на готовность эскадры д'Ойли
			SetFunctionTimerCondition("Patria_CuracaoTimeOver", 0, 0, 62, false); // таймер на 2 месяца на туда-обратно к Пуанси
			SaveCurrentQuestDateParam("questTemp.Patria.Curacao.Date"); // запоминаем дату
			// меняем отношение наций
			pchar.questTemp.Patria.Friend = "true";
			LaunchNationLegend();
			DeleteAttribute(pchar, "questTemp.Patria.Friend");
			DoQuestCheckDelay("sea_victory", 0.2);
		break;
		
		case "patria_Sl_4":
			dialog.text = "Nem kételkedtem benne, hogy ön lesz az. Még jobb! A századunk készen áll. Elsô rangú csatahajó és két negyedik rangú hajó. A teljes század maximális mérete nem haladhatja meg az öt hajót.";
			if (GetCompanionQuantity(pchar) > 2)
			{
				link.l1 = "Akkor a plusz hajókat a dokkokban hagyom, és csak kettôt tartok meg. Így öt hajót fogunk kapni.";
				link.l1.go = "patria_Sl_5";
			}
			else
			{
				link.l1 = "Igen, pontosan öt, és nem több. Indulnunk kell.";
				link.l1.go = "patria_Sl_6";
			}
		break;
		
		case "patria_Sl_5":
			DialogExit();
			pchar.questTemp.Patria = "epizode_11_wait";
		break;
		
		case "patria_Sl_6":
			dialog.text = "Tökéletes. Most elmagyarázom neked a tervet, amely szerint cselekedni fogunk: talán valamit változtatni vagy hozzátenni akarsz valamit, akkor majd megbeszéljük.";
			link.l1 = "Csupa fül vagyok, ezredes.";
			link.l1.go = "patria_Sl_7";
		break;
		
		case "patria_Sl_7":
			dialog.text = "Curacaót nincs értelme elfoglalni: ez a szigetcsoport legfôbb holland gyarmata, és még ha el is foglaljuk a zászlójukat Willemstad erôdjében, és kitûzünk egy angol vagy francia zászlót, nagyon nehéz lesz megtartani a szigetet. A hollandok mindent meg fognak tenni, hogy visszaszerezzék, és katonai századokkal fogják célba venni. Általában nincs értelme elfoglalni, mivel nem kötelezô. Sokkal fontosabb számunkra, hogy Steivesant rákényszerítsük a szerzôdés aláírására a számunkra elônyös feltételekkel, és ehhez elegendô lesz az ellenség fô védelmi erôit megsemmisíteni, és a hollandokat Willemstad kolónia teljes megsemmisítésének veszélye alá helyezni.";
			link.l1 = "Mirôl fog szólni a szerzôdés?";
			link.l1.go = "patria_Sl_8";
		break;
		
		case "patria_Sl_8":
			dialog.text = "A szerzôdést én és Chevalier de Poincy írtuk. A kereskedelem különbözô aspektusaihoz, a Társaság és Anglia közötti 'kereskedelmi háború' végéhez, Stuyvesant Sint Maarten szigetére vonatkozó igényeinek tagadásához és más, önöket kevéssé érdeklô politikai kérdésekhez kapcsolódik.";
			link.l1 = "Megértettem.";
			link.l1.go = "patria_Sl_9";
		break;
		
		case "patria_Sl_9":
			dialog.text = "A terv a következô: elôször is, minden erôvel megtámadjuk az erôdöt és leromboljuk. A hollandok csapatok partraszállására számítanak majd, de mi nem fogunk ilyet tenni, a legnagyobb veszteségeket általában egy bástya tenger felôli bevétele közben szenvedjük el. Ehelyett a sziget két pontján fogunk partra szállni rohamcsapatokkal: a Santa Maria-foknál és a Blanca-lagúnánál, és szárazföldön haladunk Willemstad városkapuja felé. Utasítottam, hogy a hajókra vigyük magunkkal a tábori tüzérséget - Curacaón nincsenek nehezen megközelíthetô sûrûségek, és az ágyúkat kerekeken gurulva minden nehézség nélkül végig tudjuk majd gurítani a földön.\nMíg a hollandok értetlenül állnak majd a történtek elôtt, mi a dzsungelbôl látótávolság alatt bevesszük a várost, és elzárunk minden lehetôséget, hogy az erôdbôl a szárazföldrôl erôsítést küldjenek. Ezután ágyútûz alá vesszük a várost. Az erôd helyôrsége biztosan megpróbál majd támadni, de a tábori ágyúkkal és a muskétásainkkal szemben semmit sem fognak tenni, és ha az erôdben tartott ágyúik még mûködôképesek lesznek, nem fogják tudni a dzsungelbe vinni ôket.\nEzeken kívül a hajóink szimulálni fogják a tengerrôl érkezô csapatok partraszállásának elôkészületeit, hogy félelmet keltsenek az ellenségben és csökkentsék a moráljukat. Egy idô után, amikor a hollandok teljesen tisztában lesznek kétségbeejtô helyzetükkel, tárgyalásra hívjuk a parlamenti képviselôket. Mit gondol, kapitány?";
			link.l1 = "Briliáns terv! És a legjobb benne, hogy nem fogunk katonákat veszíteni az erôd falainál.";
			link.l1.go = "patria_Sl_10";
		break;
		
		case "patria_Sl_10":
			dialog.text = "Örülök, hogy tetszett az ötletem. Akkor induljunk!";
			link.l1 = "Gyerünk!";
			link.l1.go = "patria_Sl_11";
		break;
		
		case "patria_Sl_11":
			DialogExit();
			chrDisableReloadToLocation = true;
			pchar.questTemp.Patria = "epizode_11_continue";
			AddQuestRecord("Patria", "60");
			pchar.quest.Patria_CuracaoTimeOver.over = "yes"; // снять таймер 2 месяца
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "PortRoyal_townhall", "goto", "goto4");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 7.0);
			Patria_CuracaoSail();
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
