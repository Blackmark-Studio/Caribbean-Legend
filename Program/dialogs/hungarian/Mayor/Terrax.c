// Маркус Тиракс, барон Ла Веги
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc, sTemp;
	int i;
	bool bOk;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

// ------------------------------------------блок angry-----------------------------------------------
    if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
    {
        npchar.angry.ok = 1;
        if (!CheckAttribute(npchar, "angry.first")) //ловушка первого срабатывания
        {
            NextDiag.TempNode = NextDiag.CurrentNode;
            Dialog.CurrentNode = "AngryExitAgain";
            npchar.angry.first = 1;
        }
        else
        {
            switch (npchar.angry.kind) //сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
            {
                case "repeat":
                    if (npchar.angry.name == "Firsttime") Dialog.CurrentNode = "AngryRepeat_1";
                    if (npchar.angry.name == "I_know_you_good") Dialog.CurrentNode = "AngryRepeat_2";
                break;
            }
        }
    }
// ------------------------------------------блок angry-----------------------------------------------

	switch(Dialog.CurrentNode)
	{
		// ----------------------------------- Диалог первый - первая встреча
		case "First time":
			// Addon 2016-1 Jason пиратская линейка патч 17/1
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && !CheckAttribute(npchar, "quest.mtraxx_complete")) 
			{
				if (pchar.questTemp.Mtraxx == "full_complete_end" || pchar.questTemp.Mtraxx == "full_complete")
				{
					dialog.text = "Ah herceg, végre itt vagy. Legalább egyikôtök eljött! A munka vár, és ti mindannyian eltûntetek! Hol a fenében van mindenki?";
					link.l1 = "Nem tudom... Marcus, kifogytam. Elegem volt. Halottak jönnek hozzám álmomban, és maga Lucifer liheg a hátamon. Túl sok vér folyt mostanában.";
					link.l1.go = "mtraxx_113";
					break;
				}
			}
			// Jason НСО
			// если Сага завалена, то у Маркуса ноды в двух местах и оплата вперед
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Van valami 'ügyed' számomra?";
				link.l1 = "Üdvözletem, Marcus. Igen, van egy 'ügyem'. nyereséges és praktikus.";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "Elhoztad a pénzt?";
				link.l1 = "Hoztam.";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "Ez a mi ügyfelünk! A munkát elvégeztük, a báró egy jól ôrzött börtönben ül. Talán szeretnéd megnézni, he-he?!";
				link.l1 = "Erre bôven lesz idôm, ha-ha. Jól bánnak vele?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, mi a fene?!";
				link.l1 = "Marcus, minden rosszul sült el. Nem tudtam eljönni, és nem tudtalak értesíteni...";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Itt a bábjátékosunk!";
				link.l1 = "Ha-ha! A látvány tökéletes volt!";
				link.l1.go = "patria_x29";
				break;
			}
            dialog.text = NPCStringReactionRepeat(""+ GetSexPhrase("Van valami mondanivalója? Nincs? Akkor hagyj békén!","Ha, " + pchar.name + "! Van valami dolgod velem? Nincs? Akkor ne zavarjon.") +"",
                         "Azt hittem, világosan fejeztem ki magam... Mondtam, hogy menj el, de továbbra is idegesítesz!",
                         "Rendben, kezd elegem lenni ebbôl a bunkóságból.", "repeat", 3, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Én máris elmegyek.",
                                               "Persze, Marcus...",
                                               "Sajnálom, Marcus...",
                                               "Oups...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Megôrültél? Mészárost akartál játszani, mi? Minden kalóz haragszik rád, fiú, jobb, ha elhagyod ezt a helyet...", "Úgy tûnik, hogy egy veszett kutya lett belôled, fiú. Ki akartad nyújtani a kezed egy kicsit? Ne vedd sértésnek, de itt nincs semmi keresnivalód. Tûnj innen!");
				link.l1 = RandPhraseSimple("Figyelj, én helyre akarom hozni a helyzetet.", "Segítsen nekem megoldani ezt a problémát, kérem...");
				link.l1.go = "pirate_town";
				break;
			}
			// Сага - завершаем искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax")
			{
				// Addon 2016-1 Jason пиратская линейка патч 17/1
				if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
				{
					link.l1 = "Marcus, abbahagynád valaha is, hogy haragudj rám? Megmentettem a barátodat, Vincentet, aki velünk együtt rabolta Cartagenát, és a te seggedet is megmentettem! Vagy Bernard nem is mondta neked?";
					link.l1.go = "Temptation_13";
				}
				else
				{
					link.l1 = "Miért vagy ilyen goromba, Marcus? Bernard nem mondott rólam semmit?";
					link.l1.go = "Temptation";
				}
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "to_lavega")
			{
				link.l2 = "Munkát keresek... Van valami jövedelmezô dolog a fejedben?";
				link.l2.go = "Mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Van egy kis selyem, amit eladnék.";
				link.l2.go = "Mtraxx_silktrade";
			}
			if (pchar.questTemp.Mtraxx == "silk_14")
			{
				link.l1 = "Találtam neked egy vevôt. Egy Port Royal-i hajóépítô. Hajóselyemre van szüksége a termeléséhez, és havonta száz tekercsbôl álló tételeket tud majd vásárolni tekercsenként 25 dublonnáért. Az emberei 10. és 15. között, éjszaka fogják átvenni az árut, a helyszín Negril-fok. A jelszó - 'A lyoni kereskedô'. Kopasz Geffrey már az elsô szállítmányt Jamaikába szállította.";
				link.l1.go = "mtraxx_13";
			}
			if (pchar.questTemp.Mtraxx == "silk_15")
			{
				link.l1 = "Találtam neked egy vevôt. Egy Port Royal-i hajóépítô. Hajóselyemre van szüksége a termeléséhez, és havonta száz tekercsbôl álló tételeket tud majd vásárolni tekercsenként 25 dublonnáért. Az emberei 10. és 15. között, éjszaka fogják átvenni az árut, a helyszín Negril-fok. A jelszó - 'A lyoni kereskedô'. Több mint két hónapba telt, mire ilyen vevôt találtam, Geffrey már biztosan eladta a selymet csempészeknek. Sajnálom, Marcus.";
				link.l1.go = "mtraxx_15";
			}
		break;

 		case "Exit":
			DialogExit();
			NextDiag.CurrentNode = NextDiag.TempNode;
		break;

        case "I_know_you_good":
			if (sti(pchar.GenQuest.Piratekill) > 20)
			{
				dialog.text = RandPhraseSimple("Megôrültél? Mészárost akartál játszani? Minden kalóz haragszik rád, fiú, jobb, ha elhagyod ezt a helyet...", "Úgy látszik, ôrült kutyává váltál, fiú. Kinyújtóztatni akartad a kezed egy kicsit? Ne vedd sértésnek, de itt nincs számodra hely. Tûnj innen!");
				link.l1 = RandPhraseSimple("Figyelj, én helyre akarom hozni a helyzetet...", "Segítsen nekem megoldani ezt a problémát, kérem...");
				link.l1.go = "pirate_town";
				break;
			}
			// Jason НСО
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, mi a fene?!";
				link.l1 = "Marcus, minden rosszul sült el. Nem tudtam eljönni, és nem tudtalak értesíteni...";
				link.l1.go = "patria_33";
				break;
			}
			if(!CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Örülök, hogy látlak, barátom!";
				link.l1 = "Én is örülök, hogy látlak. Köszönöm a csodálatos látványt!";
				link.l1.go = "patria_29";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Örülök, hogy látlak, fiam! Miben segíthetek?";
				link.l1 = "Van egy ajánlatom a számodra. Kalóznak való, tudod!";
				link.l1.go = "patria";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "Ez a mi vásárlónk! A munkát elvégeztük, a báród egy jól ôrzött tömlöcben ül. Talán szeretnéd megnézni, he-he?!";
				link.l1 = "Erre bôven lesz idôm, ha-ha. Jól bánnak vele?";
				link.l1.go = "patria_10";
				break;
			}
			// если Сага завалена, то у Маркуса ноды в двух местах и оплата вперед
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_pirates")
			{
				dialog.text = "Van valami ügye a számomra?";
				link.l1 = "Üdvözletem, Marcus. Igen, egy ügy. Nyereséges és kalózos.";
				link.l1.go = "patria_x";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Condotier.NeedMoney") && pchar.questTemp.Patria == "epizode_12_pirates" && sti(pchar.money) >= 100000)
			{
				dialog.text = "Elhoztad a pénzt?";
				link.l1 = "Hoztam.";
				link.l1.go = "patria_x8";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && pchar.questTemp.Patria == "epizode_12_talk")
			{
				dialog.text = "Ez a mi vásárlónk! A munkát elvégeztük, a báród egy jól ôrzött tömlöcben ül. Talán szeretnéd megnézni, he-he?!";
				link.l1 = "Erre bôven lesz idôm, ha-ha. Jól bánnak vele?";
				link.l1.go = "patria_10";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
			{
				dialog.text = "Charles, mi a fene?!";
				link.l1 = "Marcus, minden rosszul sült el. Nem tudtam eljönni, és nem tudtalak értesíteni...";
				link.l1.go = "patria_x33";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax") && CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
			{
				dialog.text = "Itt a bábjátékosunk!";
				link.l1 = "Ha-ha! A látvány tökéletes volt!";
				link.l1.go = "patria_x29";
				break;
			}
			// Тени прошлого
			if(CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "Örülök, hogy látlak, fiam! Miben segíthetek?";
				link.l1 = "Marcus, beszélnem kell veled. Nem vagyok benne biztos, hogy tetszeni fog, de mindenképpen szükségem van a segítségedre.";
				link.l1.go = "shadows";
				break;
			}
			if(CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro" && npchar.location == "Pirates_townhall")
			{
				dialog.text = "Ha, itt vagy, "+pchar.name+". Már vártam az érkezésedet. Az Erdei Ördög zavarba hozott a Tortugával kapcsolatos problémáddal...";
				link.l1 = "Azt mondta, hogy találtál megoldást. Igazam van?";
				link.l1.go = "terrapin";
				break;
			}
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Selymet kell eladnom.";
				link.l2.go = "Mtraxx_silktrade";
			}
            dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + ", örülök, hogy látlak! Ezúttal mire van szükséged, haver?",
                         "Mit akarsz?", "Már megint? Ne zavard az embereket, ha nincs semmi dolgod!",
                         "Te egy "+ GetSexPhrase("jó közlegény vagy","jó lány") +", úgyhogy egyelôre élhetsz. De nem akarok veled többet beszélgetni.", "repeat", 10, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Csak látni akartalak.",
                                               "Semmi.",
                                               "Rendben, Marcus, sajnálom.",
                                               "A fenébe, tényleg sajnálom, Marcus!", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
		break;

		// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
		case "Man_FackYou":
			dialog.text = LinkRandPhrase("Rablás!!! Ez elfogadhatatlan! Készülj a halálra, patkány...", "Hé, mit csinálsz ott?! Azt hitted, hogy kirabolhatsz? Végeztél...", "Várj, mi a fene?! Kiderült, hogy te egy tolvaj vagy! Vége a sornak, te szemétláda...");
			link.l1 = LinkRandPhrase("A francba!", "Carramba!", "Á, a francba!");
			link.l1.go = "PL_Q3_fight";
		break;
					
		// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
		case "AngryRepeat_1":
            dialog.text = RandPhraseSimple(""+ GetSexPhrase("Tûnj el","Tûnj el") +" innen!", "Tûnj el az otthonomból!");
			link.l1 = "Oups...";
		    link.l1.go = "AngryExitAgainWithOut";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Ne vond el a figyelmemet a munkámról az értéktelen beszélgetéseiddel. Legközelebb nem lesz ilyen jó vége neked...";
        			link.l1 = "Megvan, Marcus.";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryRepeat_2":
            dialog.text = RandPhraseSimple("Elegem van belôled.", "Nem akarok veled beszélgetni, úgyhogy jobb, ha távol tartod magad tôlem.");
			link.l1 = RandPhraseSimple("Hát...", "Hm, akkor jó...");
		    link.l1.go = "AngryExitAgain";
            if (CheckAttribute(npchar, "angry.terms")) //примиряемся через 10 дней.
            {
                if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
                {
         			dialog.text = "Remélem, hogy nem zavarsz tovább az üres fecsegéseiddel, különben meg kell, hogy öljelek. Azt mondom, hogy nem fogom örömmel megtenni.";
        			link.l1 = "Biztos lehetsz benne, Marcus, nem fogok...";
        			link.l1.go = NextDiag.TempNode;
        			CharacterDelAngry(npchar);
                }
            }
    	break;
		case "AngryExitAgain":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
		break;
		case "AngryExitAgainWithOut":
            DialogExit();
            DeleteAttribute(npchar, "angry.ok");
            DoReloadCharacterToLocation("Lavega_town","reload","reload6");
		break;
		// <<<<<<<<<<<<============= блок нод angry =============================
		
//--> -----------------------------Сага - Искушение Барбазона завершающие этапы---------------------------
		case "Temptation":
			dialog.text = "Ha! A törökök hôse? Bocsánat a durva üdvözlésért, fiú. Bernard már mesélt nekem a csodálatos részvételedrôl, és mondott valamit egy csapdáról nekem. Szeretném hallani a részleteket...";
			link.l1 = "Valóban csapda volt. Rád vadásztak, nem Bernardra. Ô csak a csali volt.";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_1":
			dialog.text = "";
			link.l1 = "A terv egyszerû volt. Meg kellett volna mentenie a barátját, és elsôként kellett volna felszállnia a 'Separátor'. fedélzetére, és abban a pillanatban lelôtték volna a hajót, és darabokra robbantották volna. A brigantint úgy megtöltötték puskaporral, mint a pokol a kénnel.";
			link.l1.go = "Temptation_2";
		break;
		
		case "Temptation_2":
			dialog.text = "A francba! Kinek az ötlete volt ez az ôrület?! És honnan tudnám meg, hogy hol rejtegetik Bernardot?!";
			link.l1 = "A terv szerzôi Jackman és testvére, David voltak. Egy hírnök értesítette volna, hogy a 'Separátor' a törökök déli öblénél várja a segítségüket. Engem választottak ennek a hírnöknek, és ez volt a hibájuk.";
			link.l1.go = "Temptation_3";
		break;
		
		case "Temptation_3":
			dialog.text = "Én ezt nem értem! Mi a szereped ebben az egészben?";
			link.l1 = "Már régóta figyeltem azt a szemét Jackmant. Jan Svensonnal dolgozom, ha nem tudná. Én és az Erdei Ördög úgy döntöttünk, hogy leleplezzük ôt. Jan biztos benne, hogy ô a hibás Blaze haláláért, és Steven-t a semmiért vádolták meg.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end") link.l1.go = "Temptation_14";
			else link.l1.go = "Temptation_4"; //патч 17/1
		break;
		
		case "Temptation_4":
			dialog.text = "Heh! De Blaze testén találtak egy cápafogat az ô monogramjával - S.D. - ez a dolog Stevené, ezt mindenki tudja...";
			link.l1 = "Elhelyezték. Jackman magas tétet játszott. Megszabadult Nathaniel Hawktól, és átvette a helyét Maroon Townban, majd megölte Sharpot, és Cápát tette felelôssé a gyilkosságért. Elég bizonyítékom van a bûneire. Megtaláltam ôket Jacob ládájában. Ott volt Sharp térképének második része és Hawk szilánkja.";
			link.l1.go = "Temptation_5";
		break;
		
		case "Temptation_5":
			dialog.text = "A fenébe! Tehát Steven ártatlan? És miért tette mindezt Jacob?";
			link.l1 = "Arra számított, hogy ô lesz a Testvériség feje, és arra számított, hogy valami Isla Tesoróval kapcsolatos dologra. Nem tudta megszerezni a te és Svenson támogatását, ezért úgy döntött, hogy megszabadul tôletek. Te voltál az elsô a listán. Jan mint a legveszélyesebb volt a második.";
			link.l1.go = "Temptation_6";
		break;
		
		case "Temptation_6":
			dialog.text = "Hol van ez a szemétláda?! Szét fogom tépni!";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				link.l1 = "Jackman és a testvére halott, akárcsak a többi vadász. Személyesen foglalkoztam velük. Ez a szemétláda nem fog többé senkit sem bántani. Marcus, szavaznál Steven Dodsonra? Ez az én személyes szívességem.";
				link.l1.go = "Temptation_7";
			}
			else
			{
				link.l1 = "Jackman és a testvére halott, ahogy a többi vadász is. Személyesen foglalkoztam velük. Ez a szemétláda nem fog többé senkit sem bántani. Sajnos Steven-t megölték...";
				link.l1.go = "Temptation_10";
			}
		break;
		
		case "Temptation_7":
			dialog.text = "Persze, hogy szavazok! Mindig is Sharkot tartottam a legméltóbbnak közülünk Blaze után. És szinte már hittem a bûnösségében. Mindannyian hittünk benne! Tessék, vedd el a szilánkomat.";
			link.l1 = "Rendben van! Most már szabadon lélegezhetsz.";
			link.l1.go = "Temptation_8";
		break;
		
		case "Temptation_8":
			GiveItem2Character(pchar, "splinter_mt"); // дать осколок
			dialog.text = "Igaz... Ha jól tudom, te képviseled Shark érdekeit?";
			link.l1 = "Igen. Én és Jan Svenson. Rendben, Marcus, viszlát!";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_10":
			dialog.text = "Halott?! Hogyhogy? Jackman munkája is?";
			link.l1 = "Nem. A saját hajóskapitánya tette, Chad Kapper volt a neve. Már megkapta, amit megérdemelt... Marcus, Svenson úgy gondolja, hogy te vagy a legérdemesebb a Testvériség új vezetôje. A többi báró támogatja ezt a döntést. Elfogadod ezt?";
			link.l1.go = "Temptation_11";
		break;
		
		case "Temptation_11":
			dialog.text = "Heh! Nem kell kétszer kérdezned. Nagy megtiszteltetés a Testvériség vezetôjének lenni! Ne is gondoljátok, hogy nem értek egyet.";
			link.l1 = "Nagyszerû. Örülök, hogy ezt elfogadtad.";
			link.l1.go = "Temptation_12";
		break;
		
		case "Temptation_12":
			GiveItem2Character(pchar, "splinter_mt"); // дать осколок
			dialog.text = "Tessék, fogd a szilánkomat. Add át Svensonnak. Gondolom, ô a fônök?";
			link.l1 = "Igen, az. Rendben, Marcus, viszlát!";
			link.l1.go = "Temptation_9";
		break;
		
		case "Temptation_9":
			dialog.text = "Igen, és szeretném megköszönni, hogy megmentetted Bernard barátomat. Tessék, fogd ezt az arannyal teli erszényt.";
			link.l1 = "Köszönöm. Viszontlátásra!";
			link.l1.go = "Temptation_exit";
		break;
		
		case "Temptation_exit":
			DialogExit();
			TakeNItems(pchar, "gold_dublon", 300);
			Log_Info("Kaptál 300 dublont.");
			PlaySound("interface\important_item.wav");
			NextDiag.CurrentNode = "I_know_you_good";
			AddQuestRecord("BarbTemptation", "25");
			if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm")) Saga_GiveCalendar();
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "Temptation_13":
			dialog.text = "Igen, mesélt nekem Charlie herceg pompás érkezésérôl a törököknél... Megmentette a seggemet, azt mondod? Megmentettem a seggemet. Bernard mondott valamit egy csapdáról...";
			link.l1 = "Igen, csapda volt. Te voltál a célpont, Bernard csak a csali...";
			link.l1.go = "Temptation_1";
		break;
		
		case "Temptation_14":
			dialog.text = "Ha-ha-ha, az Erdei Ördögnek dolgozol, mi, herceg? Szóval, jobban keresel vele, mint velem? Mondd meg ôszintén!";
			link.l1 = "Marcus, tegyük félre a múltat örökre. Most már van egy közös célunk, és ez fontosabb, mint a karavánok kifosztása. A francba! Most ez a legfontosabb! A Testvériség jövôje forog kockán!";
			link.l1.go = "Temptation_15";
		break;
		
		case "Temptation_15":
			dialog.text = "Rendben herceg, értem! Végül is szabad magánzó vagy, az Erdei Ördögnek dolgozni a te választásod volt, és jól döntöttél... Steven akkor... Azt mondtad, hogy megrágalmazták, igaz?";
			link.l1 = "Teljesen igazad van.";
			link.l1.go = "Temptation_4";
		break;
		
		// Тени прошлого
		case "shadows":
			dialog.text = "Persze, mindent megteszek, hogy segítsek neked! Gyerünk, menjetek.";
			link.l1 = "Nézd meg, Marcus... Itt van egy cápafog. Mit tudsz mondani róla?";
			link.l1.go = "shadows_1";
		break;
		
		case "shadows_1":
			RemoveItems(pchar, "shark_teeth", 1);
			dialog.text = "Ha! Ez egy fehér cápa foga, amit Steven Dodson ölt meg, mert azt remélte, hogy lenyûgözhet egy lányt. Az emberek azóta Cápának hívják. Csak néhányan tudták ezt megtenni a víz alatt egy egyszerû szablyával. De ô fiatal volt és ostoba, Beatrice Sharp pedig a Karib-tenger legszebb lánya... Szóval, hogy szerezte meg?";
			link.l1 = "Saint John's volt hóhérjától kaptam. Ezzel a foggal öltek meg egy embert. A neve... Joshua Leadbeater.";
			link.l1.go = "shadows_2";
		break;
		
		case "shadows_2":
			dialog.text = "Ez egy régi történet. Steven ölte meg azt az embert. Megdöbbentette Beatrice halála, és úgy gondolta, hogy Leadbeater az egyetlen élô személy, aki felelôs a haláláért. De késôbb talált néhány papírt Joshua holttesténél, tanulmányozta ôket, és megbánta tettét.\nA Maszk nem volt hibáztatható Beatrice haláláért, csak Mészáros kellett neki. Mészáros féltékeny volt barátnôje, Jessica szervezte az egészet.";
			link.l1 = "Olvastad azokat a papírokat?";
			link.l1.go = "shadows_3";
		break;
		
		case "shadows_3":
			dialog.text = "Miért tenném? Hát persze, hogy nem. Nem érdekeltek. De ha van egy kis szabadideje, elmondhatom, miért üldözte a Maszk Butchert. Részeg Steven sokszor mesélte nekem ezt a történetet.";
			link.l1 = "Van idôm. Hidd el, az érdeklôdésemnek célja van. Még meg is tudom írni ezt a történetet.";
			link.l1.go = "shadows_4";
		break;
		
		case "shadows_4":
			dialog.text = "Tudom, hogy soha nem vesztegeted az idôdet. Akkor figyelj. Joshua Leadbeater angol tengerészkapitány volt, és a legendás 'Neptun' az ô parancsnoksága alatt...";
			link.l1 = "...";
			link.l1.go = "shadows_5";
		break;
		
		case "shadows_5":
			DialogExit();
			SetLaunchFrameFormParam("Egy órával késôbb", "Saga_FinalLedbitterStory", 0, 4);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 10); //крутим время
			RecalculateJumpTable();
		break;
		
		case "shadows_6":
			AddQuestRecordInfo("Mask", "1");
			dialog.text = "...de Leadbeater túlélte és felvette egy hajó. A sebe eltorzította, és azóta maszkot visel. Egy idô után az emberek Maszknak kezdték hívni. Életcéljává vált a bosszúállás azon az emberen, aki egy életre megsebezte.";
			link.l1 = "Értem... Mindent leírtam. Azt hiszem, újra kell olvasnom, és párhuzamot vonnom a már meglévô információkkal. Valóban szomorú történet. Láttad már Jessicát?";
			link.l1.go = "shadows_7";
		break;
		
		case "shadows_7":
			dialog.text = "Persze! Butchert minden útjára elkísérte, amíg a férfi nem dobta ôt Beatrice miatt. Jess ezt nem tudta megbocsátani neki. Az emberek Mészáros talizmánjának nevezték, mert mindig szerencséje volt, amíg vele volt.\nHiszed vagy sem, de amint Barbadoson megszabadult tôle, az üzletei rosszul mentek, a zsákmány szegényes lett, és a 'Neptungyakran vendégeskedett az Isla Tesoro hajógyárban. De ez azzal magyarázható, hogy Butcher a legtöbb idôt Beatrice-szal a kabinban töltötte, nem pedig a fedélzeten.\nBeatrice nem olyan volt, mint Jessica, nem volt a kalandok és a háború rabja, bár Nicholas megtanította vívni és vitorlázni. Igen, szerette a tengeri románcokat, de nem volt benne elég keménység. A Butcher' s 'Neptun' nem volt neki való hely. A végén belehalt.";
			link.l1 = "És mi a helyzet Jessicával?";
			link.l1.go = "shadows_8";
		break;
		
		case "shadows_8":
			dialog.text = "Ó, ô aztán nem semmi volt... A 'Neptun' Neptun minden matróza engedelmeskedett a parancsainak, és nem csak azért, mert a kapitány barátnôje volt. Jess mestere volt a vívásnak és a vitorlázásnak, Butcher erôfeszítései nem voltak hiábavalóak. Kemény volt és vakmerô, és annyira gyönyörû.\nMegannyi férfi akart vele ágyba bújni, de ô csak Butchert akarta, ôt zaklatni igazán kockázatos volt, sokan a saját bôrükön érezték meg szó szerint az eredményt, és a legkitartóbbaknak a vívóleckéi az utolsónak bizonyultak az életükben.\nJessnek volt egy nagyon különleges kardja, az egyetlen a maga nemében a Karib-tengeren, fogalmam sincs, honnan szerezte. Lángpengés kard. A pengét nem lehetett kézzel megfogni, és a legkisebb érintés is szörnyû sebet ejtett rajta.\nJess nem születésétôl, hanem hivatásától fogva kalandor volt. Egyébként, ha többet szeretnél megtudni róla, beszélhetsz egy ismerôsöddel. Ô sokkal többet tud róla mondani, mint én.";
			link.l1 = "Tényleg? És ki ez az ember?";
			link.l1.go = "shadows_9";
		break;
		
		case "shadows_9":
			dialog.text = "Jan Svenson. Az erdei ördög sosem vallaná be, de tervei voltak Jessicával. Ez volt az az idô, amikor már magáénak tudhatta Nyugat-Maint, és a hírneve is irigylésre méltó volt, így a tigrislány ugyanolyan jó volt neki.\nMiután Mészáros megszabadult Jess-tôl, Jan gyanúsan gyakran kezdte látogatni Barbadost, a helyôrséget rettegésre késztette, ô. Mint tudja, Jessica a bridgetowni ültetvényes lánya volt.\nMindent összevetve, a terveit magánkörökben jól ismerték, mégsem merte senki szóvá tenni a véleményét. Lehet, hogy Jan manapság Blueweldben ül a hátsó fertályán, de akkoriban egy rossz szó a megszólításában rosszul végzôdhetett.\nA végén nem jött össze nekik. Jess nem tudott együtt élni a fájdalommal, amit Butcher árulása okozott, és egy évvel késôbb a Maszk segítségével bosszút állt. Ez a bosszú mindenki számára szörnyû véget ért: Butcher, Beatrice, a Maszk és saját maga számára is. Mindannyian meghaltak.";
			link.l1 = "Nem. Mészáros még mindig él.";
			link.l1.go = "shadows_10";
		break;
		
		case "shadows_10":
			dialog.text = "Micsoda?! Rosszul hallottam?! Életben van?!";
			link.l1 = "Igen. Mészáros kapitányt nem akasztották fel. Hm, valójában igen, de hála Jacob Jackmannek és a hóhér Henrynek, aki megijesztette a hóhért, élve megúszta. Az akasztás csak egy elôadás volt. Bizonyítékom van rá.";
			link.l1.go = "shadows_11";
		break;
		
		case "shadows_11":
			dialog.text = "Hihetetlen! És hol van most?";
			link.l1 = "Lawrence Beltrop néven ismerik, és Kikötô-Royalban él. De úgy tûnik, hogy nem változott, és még mindig veszélyes. Jackman, aki nagy zajt kavart a Testvériségen belül, az ô parancsait követte.";
			link.l1.go = "shadows_12";
		break;
		
		case "shadows_12":
			dialog.text = "A fenébe! A szállásmester mégiscsak megtalálta a kapitányát! Ennyi év után... Beltrop azt mondod... várj! Most már értem, miért volt Blaze irataiban az a furcsa kihallgatási jegyzôkönyv... Úgy tûnik, hogy Blaze valami érdekeset tudott meg Butcher-Beltropról...";
			link.l1 = "Mirôl beszélsz?";
			link.l1.go = "shadows_13";
		break;
		
		case "shadows_13":
			dialog.text = "Amikor elfoglaltam ezt a rezidenciát, megengedtem magamnak egy kis idôt, hogy átnézzem Blaze papírjait. Találtam egy Samuel Brooks nevû személy kihallgatási jegyzôkönyvét. Rengeteg részletet tartalmazott Thomas Beltrope kalandjairól, aki híres kalóz volt és Nicolas Sharp legközelebbi barátja. Úgy tûnik, hogy ô a Mészáros apja.";
			link.l1 = "Érdekes. Úgy tûnik, Beltrop és Sharp gyermekei folytatták apjuk munkáját...";
			link.l1.go = "shadows_14";
		break;
		
		case "shadows_14":
			dialog.text = "Úgy tûnik... Mondd csak, barátom, miért érdekel téged ennyire olyan emberek múltja, akik már régóta halottak? Mi ez az egész?";
			link.l1 = "Szükségem van olyan iratokra, amelyek bizonyítják, hogy Ellen McArthur Beatrice Sharp lánya és Nicolas Sharp unokája, és minden joga megvan ahhoz, hogy viselje ezt a vezetéknevet. Nem érdekel, hogy a vezetékneve lehet Beltrop.";
			link.l1.go = "shadows_15";
		break;
		
		case "shadows_15":
			dialog.text = "Ellen McArthurról semmit sem találtam a Blaze archívumában. Furcsa, hogy Beatrice nem szólt Blaze-nek az unokahúga születésérôl. Ez nem az ô stílusa.";
			link.l1 = "Figyelj, talán van még valami Sharp irataiban errôl a történetrôl? Minden részletre szükségem van!";
			link.l1.go = "shadows_16";
		break;
		
		case "shadows_16":
			dialog.text = "Hm... Talán. Blaze feljegyzései szerint azt a szigetet próbálta megtalálni, ahol a nôvére meghalt. Vannak másolatok a Leadbeater büntetôexpedíciójára vonatkozó levéltári iratokról. Semmi érdekes, kivéve néhány szélességi számot.\nEz a szélességi kör a Karib-tengert szeli át az északi részén. De a földrajzi hosszúságnak nincs jele. Nyilván Blaze keresései kudarcot vallottak, el sem tudod képzelni, hány kis sziget van ezen a szélességi fokon.";
			link.l1 = "És mi a szélességi fok?";
			link.l1.go = "shadows_17";
		break;
		
		case "shadows_17":
			dialog.text = "Lássuk csak... Tessék: 21 32' North. Nem tudom, hogyan segíthet ez neked.";
			link.l1 = "De igen. Köszönöm szépen, Marcus, az ôszinte történetedet. Viszlát!";
			link.l1.go = "shadows_18";
		break;
		
		case "shadows_18":
			DialogExit();
			pchar.questTemp.Saga.Shadows = "jessika";
			AddQuestRecord("Shadows", "6");
			LAi_SetHuberType(npchar);
			NextDiag.CurrentNode = "I_know_you_good";
			sld = characterFromId("Svenson");
			sld.quest.jessika = "true";
			// рифы доступны для посещения
			i = FindIsland("RockIsland");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			// для любителей самостоятельно добавлять локаторы
			LAi_LocationDisableOfficersGen("Shore67", true);//офицеров не пускать
			// и сразу прерывание
			pchar.quest.Saga_Jess_Island.win_condition.l1 = "location";
			pchar.quest.Saga_Jess_Island.win_condition.l1.location = "Shore67";
			pchar.quest.Saga_Jess_Island.function = "Saga_JessikaIsland"; 
			// активируем квест хронометра Алекса
			pchar.questTemp.AlexClock = "terrax"; // 280912
		break;		
		
		// суп из черепахи
		case "terrapin":
			dialog.text = "Nos, én tehetek valamit érted. Mint tudjátok, Tortuga biztonságáról nemcsak a La Roche erôd gondoskodik, hanem a sziget partjait állandóan ôrzô kalózszázad is. Tortuga kikötôje biztonságos, ezek a legények értik a dolgukat, és erôs hajóik vannak. Levasseur már régóta csalogatja ezeket a kapitányokat.\nAzok képesek harcolni akár egy vonalas hajóraj ellen is, és komoly ellenfelek lesznek. Tehát a Kódex ôrzôjeként és egyben a Parti Testvérek vezetôjeként rávehetem ezeket az ôrkutyákat, hogy hagyják el Tortuga partjait.";
			link.l1 = "És ez minden?";
			link.l1.go = "terrapin_1";
		break;
		
		case "terrapin_1":
			dialog.text = "Ez nem elég? Többet úgysem tudok segíteni. El kell pusztítanod az erôdöt, de legalább nem kell harcolnod azokkal az ôrhajókkal. Hidd el, sokkal veszélyesebbek, mint az erôd, így a segítségemmel minden könnyebb lesz.";
			link.l1 = "Nos, ha mindenképpen meg kell támadnom, a kalózszázad távozása tényleg segíteni fog. Köszönöm, Marcus! Mikor támadhatom meg Tortugát?";
			link.l1.go = "terrapin_2";
		break;
		
		case "terrapin_2":
			dialog.text = "Amikor csak akarod. Az ôrhajók a jelemre indulnak.";
			link.l1 = "Rendben. Akkor mennem kell, hogy felkészüljek.";
			link.l1.go = "terrapin_3";
		break;
		
		case "terrapin_3":
			DialogExit();
			// Левассера - к барьеру!
			sld = characterFromId("Tortuga_Mayor");
			LAi_LoginInCaptureTown(sld, true);
			pchar.questTemp.Sharlie.Hardcore_Tortuga = "true";
			pchar.questTemp.Terrapin = "hardcore";
			pchar.questTemp.Sharlie.DelTerGuard = "true"; // убираем пиратскую эскадру
		break;
		
		case "pirate_town":
            dialog.text = "Megoldani a problémát? Van fogalmad róla, hogy mit tettél? Mindegy, hozz nekem egy millió pezót, és ráveszem a fiúkat, hogy felejtsék el a tettedet. Ha nem tetszik az ötlet, akkor mehetsz a pokolba.";
			if (sti(Pchar.money) >= 1000000)
			{
				link.l1 = "Rendben, kész vagyok fizetni.";
				link.l1.go = "pirate_town_pay";
			}
			link.l2 = "Ég veled...";
			link.l2.go = "pirate_town_exit";
		break;
		
		case "pirate_town_exit":
			DialogExit();
            bDisableFastReload = true;//закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;
		
		case "pirate_town_pay":
            dialog.text = "Jól van! Tekintsd magad újra tisztának. De remélem, hogy nem fogsz többé ilyen undorító dolgokat csinálni.";
			link.l1 = "Nem fogok. Túl drága nekem. Viszlát...";
			link.l1.go = "exit";
			AddMoneyToCharacter(pchar, -1000000);
			pchar.GenQuest.Piratekill = 0;
		break;
		
		// Addon 2016-1 Jason ------------------------- пиратская линейка --------------------------
		case "Mtraxx":
			if (pchar.Ship.Type == SHIP_NOTUSED)
			{
				dialog.text = "Elôször szerezz magadnak egy hajót, aztán kérj munkát. Egy szárazföldi guminak itt semmi keresnivalója. Tûnj el!";
				link.l1 = "Hmm... Értem.";
				link.l1.go = "exit";
				break;
			}
			if(ChangeCharacterHunterScore(Pchar, "spahunter", 0) > 10)
			{
				dialog.text = "Teljesen elment az eszed? A fél spanyol világ fut utánad. Több kárt fogsz okozni, mint hasznot. Oldd meg a problémáidat, aztán jelentkezz. Csak ennyit akartam mondani! Takarodj innen!";
				link.l1 = "Hmm... Értem.";
				link.l1.go = "exit";
				break;
			}
            dialog.text = "Akarsz egy kis akciót, mi? Ha-ha! Jó... Bár figyelmeztetlek, fiú, nem fogsz békét találni nálam. Ha félsz a puskaporszagtól, vagy nem tudsz vért ontani - az ajtó mögötted van. Ki nem állhatom a puhányokat. Akkor sem maradsz velem sokáig, ha besúgó vagy egy patkány vagy, aki szívesen ellopja a társa zsákmányából járó részt. És akkor mi van? Benne vagy?";
			link.l1 = "Benne vagyok, Marcus. Nem félek a harctól, és nincs az a kutya, aki gyávának vagy patkánynak tarthatna.";
			link.l1.go = "Mtraxx_1";
			link.l2 = "Hû, ez túl kemény nekem! Bocsáss meg, Marcus, de jobb, ha most elmegyek...";
			link.l2.go = "Mtraxx_exit";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("LaVega");
		break;
		
		case "Mtraxx_exit":
            DialogExit();
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_wait":
            dialog.text = "Mi az, még mindig itt vagy?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkTrade") && GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
			{
				link.l2 = "Van egy kis selyem, amit eladnék.";
				link.l2.go = "Mtraxx_silktrade";
				link.l1 = "Már megyek is.";
				link.l1.go = "exit";
				break;
			}
			link.l1 = "...";
			link.l1.go = "exit";
		break;
		
		case "Mtraxx_1":
            dialog.text = "Ha-ha, nos- nos, bátor kis kalózom, akkor beszéljük meg az üzletet. A Santo Domingo-i forrásom tájékoztatott egy spanyol kapitányról, aki olyan gazdag kék borostyánnal, hogy kurváknak ajándékozza. Hallottál már a kék borostyánról?";
			link.l1 = "Hallottam. Ritka és értékes kô.";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Pontosan. Még itt is jó pénzt fizetnek érte a bankárok és az ékszerészek, és a régi jó Európában tízszeresét is megkaphatod érte. A borostyán nem ritka kô a Karib-térségben, de a kék ritkaság. És most valami kasztíliai ravasz kutya azzal henceg, hogy neki több kék borostyánja van, mint Kubában és Hispaniolán a bankároknak sárga borostyánja együttvéve.";
			link.l1 = "Meg lehet-e bízni néhány részeg spanyol meséiben? Három dublont talált, és mindenkinek azt mondja, hogy megtalálta El Doradót.";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Én nem hallottam volna, de ô valóban kék borostyánt ajándékozott kurváknak. Valami bizalomgerjesztônek kell lennie a hencegésében. Menjen el Santo Domingóba és járjon utána. Ha megtalálod a kék borostyán lelôhelyet, az még jobb lesz. Ha megteszed, garantálom a jutalmat és a tiszteletet La Vegában.";
			link.l1 = "Mi van, ha az információid értéktelenek?";
			link.l1.go = "mtraxx_4";
		break;
		
		case "mtraxx_4":
            dialog.text = "Akkor bizonyítsd be nekem, hogy Kasztília hazudik.";
			link.l1 = "Rendben. Ki a forrásod Santo Domingóban?";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
			// belamour legendary edition даем флаг и лизензию ГВИК если отсутствует -->
			bOk = IsCharacterPerkOn(pchar,"FlagSpa") || IsCharacterPerkOn(pchar,"FlagHol");
			if(CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 60 && bOk) sTemp = ".";
			else 
			{
				if(bOk) 
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence") || GetDaysContinueNationLicence(HOLLAND) < 60) 
					{
						sTemp = ". Várj egy percet, vegyél egy kereskedelmi engedélyt 60 napra."; 
						GiveNationLicence(HOLLAND, 60);
					}
				}
				else // нет флага
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence")) 
					{
						sTemp = ". Várj egy percet, vegyél egy 60 napos kereskedelmi engedélyt és egy spanyol zászlót, hogy Santo Domingóban landolhass. Innentôl kezdve ajánlom, hogy szerezz sajátot, segít átverni az együgyût a kereskedelmi medencében. Ezt majd visszakapom.";
						GiveNationLicence(HOLLAND, 60);
						SetCharacterPerk(pchar, "FlagSpa");
						log_info("Spanyol zászlót kaptál");
						pchar.questTemp.GiveMeSpaFlag = true;
					}
					else // есть лицензия
					{	
						if(GetDaysContinueNationLicence(HOLLAND) < 60) 
						{
							sTemp = ". Várj, hogy fogsz kereskedni a megfelelô zászló nélkül?! Tessék, egy 60 napos kereskedési engedély, hosszabb, mint a tiéd. Valamint a spanyol zászlót a Santo Domingóban való landoláshoz. Innentôl kezdve ajánlom, hogy szerezz sajátot, segít átverni az együgyût a kereskedési medencében. Ezt visszakapom.";
							GiveNationLicence(HOLLAND, 60);
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("Spanyol zászlót kaptál");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
						else 
						{
							sTemp = ". Várj, hogy fogsz kereskedni a megfelelô zászló nélkül?! Tessék, itt van a spanyol zászló a santo domingói partraszálláshoz. Mostantól ajánlom, hogy szerezzen sajátot, ez segít átverni az együgyût a kereskedelmi medencében. Ezt majd visszakapom.";
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("Spanyol zászlót kaptál");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
					}
				}
			}
			// <-- legendary edition
            dialog.text = "Szükséged van egy Gabriela Chapado nevû bordélyházi lányra. Mondd a nevem és a jelszavam - 'Amber Necklace'. Ô majd megadja a részleteket. És ne vesztegesd az idôt - az információ még friss, de egy-két nap múlva elavulhat."+sTemp;
			link.l1 = "Értettem, Marcus. Santo Domingóba megyek.";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_6":
            DialogExit();
			pchar.questTemp.Mtraxx = "jewelry_1";
			pchar.questTemp.Mtraxx.AffairOfHonor = "true"; // конфликт с делом чести
			pchar.questTemp.ZA.Block = true;			// конфликт с квестом "Заносчивый аристократ"
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_1", "1");
			Mtraxx_JewelryBegin();
			AddMapQuestMarkCity("SantoDomingo", false);
		break;
		
		case "mtraxx_7":
			i = GetCharacterItem(pchar, "jewelry7");
            dialog.text = "Már értesítettek az érkezésedrôl. Jelentést kérek!";
			link.l1 = "Én már megbirkóztam ezzel a kék borostyán szeretôvel, bár nem volt könnyû. Sikerült megtalálnom a lelôhelyeit és kifosztanom ôket. Elhoztam nektek "+FindRussianQtyString(i)+" darab kék borostyánt.";
			link.l1.go = "mtraxx_8";
			DelLandQuestMark(characterFromId("Terrax"));
			DelMapQuestMarkCity("LaVega");
		break;
		
		case "mtraxx_8":
			if (sti(pchar.questTemp.Mtraxx.JewQty) > GetCharacterItem(pchar, "jewelry7"))
			{
				PlaySound("interface\important_item.wav");
				Log_Info("Adtál "+FindRussianQtyString(GetCharacterItem(pchar, "jewelry7"))+" darab kék borostyánból");
				RemoveItems(pchar, "jewelry7", GetCharacterItem(pchar, "jewelry7"));
				dialog.text = "Nos, nos... Fiam, emlékszel a figyelmeztetésemre a patkányság veszélyeirôl? Mit mondtál nekem akkor? Egy kutya sem hibáztathat téged ezért? Azt hiszed, hülye vagyok, kölyök? Tökéletesen tisztában vagyok vele, hogy te fosztogattad "+FindRussianQtyString(sti(pchar.questTemp.Mtraxx.JewQty))+" darab kék borostyánt a Szúnyogok partján. Most pedig fuss, kis patkány, fuss, és imádkozz, hogy soha többé ne találkozzunk!";
				link.l1 = "A francba!";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.Dialog.currentnode = "First time";
				CloseQuestHeader("Roger_1");
				// belamour legendary edition забрать флаг обратно
				if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
				{
					DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
					DeleteAttribute(pchar,"perks.list.FlagSpa"); 
					log_info("Spanyol zászlót adtál");
				}
			}
			else
			{
				PlaySound("interface\important_item.wav");
				Log_Info("Adtál "+FindRussianQtyString(GetCharacterItem(pchar, "jewelry7"))+" darab kék borostyánból");
				RemoveItems(pchar, "jewelry7", sti(pchar.questTemp.Mtraxx.JewQty));
				dialog.text = "Szép munka, fiú! A legjobb oldaladról mutattad meg magad: elintéztél egy nehéz ügyet, és elhoztad mindazt, amit kifosztottál. Szép munka! Örülök, hogy nem tévedtem veled kapcsolatban.";
				link.l1 = "Mi lesz a részemmel, Marcus?";
				link.l1.go = "mtraxx_9";
			}
		break;
		
		case "mtraxx_9":
			i = sti(pchar.questTemp.Mtraxx.JewQty)/2;
			PlaySound("interface\important_item.wav");
			Log_Info("Ön "+FindRussianQtyString(i)+" darab kék borostyánt kapott.");
			TakeNItems(pchar, "jewelry7", i);
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("Spanyol zászlót adtál");
			}
            dialog.text = "Úgy beszélsz, mint egy igazi kalóz, ha-ha-ha-ha! A zsákmány fele a tiéd. Vedd el.";
			link.l1 = "Köszi, sapka. Van még valami más is a számomra?";
			link.l1.go = "mtraxx_10";
			DeleteAttribute(pchar, "questTemp.Mtraxx.JewQty");
			CloseQuestHeader("Roger_1");
			Achievment_Set("ach_57");
		break;
		
		case "mtraxx_10":
            dialog.text = "Mindig vannak feladataim a hozzáértô fiúknak. Van egy kényes ügy, amivel szeretném, ha foglalkoznál. Capsterville-ben állomásozik egy hajó, a 'Snake', , Geffrey Brooke, más néven Kopasz Geffrey parancsnoksága alatt. Ô nekem dolgozik. Kitûnô harcos, mindent tud a fegyverekrôl és a pengékrôl, de az élet minden más területén komplett idióta. De ne legyünk durvák Kopasz Geffreyvel, senki sem tökéletes, ha-ha!\nSzóval. Ez a kemény fickó megtámadott egy holland konvojt Saint Martintól északra, és elfogott egy búzával teli zsákokkal teli kérget. A helyzet az, hogy a zsákok között sikerült rejtett hajóselymet találnia. Egy igazán nagy rakományt. Ez az áru rendkívül értékes és ritka, a hollandok kizárólag a hadseregük igényeihez hozzák Európából. Ezt a selymet speciális vitorlákhoz használják, amelyek növelik a hajó sebességét és a szél által való hajózási képességét.\nMegvenni szinte lehetetlen, eladni nem gond, de nehéz megtalálni a megfelelô árat. Ezek az istenverte kereskedôk mindig csökkentik az árat! Tisztában vagyok vele, hogy vannak olyan emberek a Karib-tengeren, akik készek jó áron dublont adni ezért a selyemért, és a célod az, hogy megtaláld ezeket az embereket.\nMi? Bármilyen bolond képes karavánokat kifosztani, de kereskedni csak olyan emberek tudnak, akiknek legalább egy koponyában van az ész' exisztencia jele. Azt tervezem, hogy havonta fogok hajóselymet árulni, így a célod az, hogy találj egy rendszeres vevôt, aki legalább húsz aranydublont fizet egy tekercsért. Erre két hónapotok van, nem tarthatom a kopasz Geffrey-t örökké Capsterville-ben.\nEz minden. Hajózz Capsterville-be, és beszélj Geffreyvel, mielôtt egy fillérért eladja a rakományt csempészeknek. Már mondtam neked, hogy ô egy kicsit 'egyszerû'..";
			link.l1 = "Hm... Értem. Már úton vagyok.";
			link.l1.go = "mtraxx_11";
		break;
		
		case "mtraxx_11":
            DialogExit();
			pchar.questTemp.Mtraxx = "silk_1";
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_2", "1");
			Mtraxx_SilkBegin();
		break;
		
		case "mtraxx_12":
            dialog.text = "Ha! Itt a bátor kapitány "+GetFullName(pchar)+"! Mi a helyzet a vevôvel?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				link.l1 = "Találtam neked egy vevôt. Egy Port Royal-i hajóépítô. Hajóselyemre van szüksége a termeléséhez, és havonta száz tekercsbôl álló tételeket tud majd vásárolni tekercsenként 25 dublonnáért. Az emberei 10. és 15. között, éjszaka fogják átvenni az árut, a helyszín Negril-fok. A jelszó - 'A lyoni kereskedô'. Több mint két hónapba telt, mire ilyen vevôt találtam, Geffrey már biztosan eladta a selymet csempészeknek. Sajnálom, Marcus.";
				link.l1.go = "mtraxx_15";
			}
			else
			{
				link.l1 = "Találtam neked egy vevôt. Egy Port Royal-i hajóépítô. Hajóselyemre van szüksége a termeléséhez, és havonta száz tekercsbôl álló tételeket tud majd vásárolni tekercsenként 25 dublonnáért. Az emberei 10. és 15. között, éjszaka fogják átvenni az árut, a helyszín Negril-fok. A jelszó - 'A lyoni kereskedô'. Kopasz Geffrey már az elsô szállítmányt Jamaikába szállította.";
				link.l1.go = "mtraxx_13";
			}
		break;
		
		case "mtraxx_13":
            dialog.text = "Ez nagyszerû, barátom! Szép munka. Nehéz olyan embert találni, aki képes mindkét kezét és fejét használni. Találkozzunk 20 nap múlva a jutalmadért. A kopasz Geffrey addigra már az elsô tranzakcióból származó pénzt is elhozza."; // правки прогона 3
			link.l1 = "Nagyon jó, Marcus. Hamarosan találkozunk. Remélem, lesz még egy munkád számomra.";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_14":
            dialog.text = "Úgy lesz. Viszlát késôbb.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "I_know_you_good";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate"))
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 30, false);
				//SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 40, false);
				AddQuestRecord("Roger_2", "23");
			}
			else
			{
				SetFunctionTimerCondition("Mtraxx_SilkPay", 0, 0, 20, false); // правки прогона 3
				//SetFunctionTimerCondition("Mtraxx_SilkPayLate", 0, 0, 30, false);
				AddQuestRecord("Roger_2", "24");
			}
		break;
		
		case "mtraxx_15":
			pchar.quest.Mtraxx_SilkTimeLateAll.over = "yes";
            dialog.text = "Kár, de így is hatalmas siker. Jó munkát végeztél! Nem kapod meg a részed Geffrey tételébôl, de azért megérdemled a jutalmat. Találkozzunk egy hónap múlva, addigra eladom az elsô tételt a vevôdnek, akkor majd beszélünk.";
			link.l1 = "Nagyon jó, Marcus. Hamarosan találkozunk. Remélem, lesz még egy munkád számomra.";
			link.l1.go = "mtraxx_14";
		break;
		
		case "mtraxx_16":
			//pchar.quest.Mtraxx_SilkPayLate.over = "yes";
            dialog.text = "Tessék, "+pchar.name+". Beszéljünk a jutalmadról.";
			link.l1 = "Szeretem az ilyen beszélgetéseket, ha-ha-ha-ha! Csupa fül vagyok.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.SilkLate")) link.l1.go = "mtraxx_19";
			else link.l1.go = "mtraxx_17";
		break;
		
		case "mtraxx_17":
            dialog.text = "Kopasz Geffrey eladta a vevôdnek az elsô adag 105 tekercs hajóselymet. Mivel arra számítottam, hogy húsz dublonnáért adom el egy tekercset, úgy gondolom, tisztességes lenne, ha a különbözetet neked adnám. Ez az én döntésem. A te részed 525 dublont plusz egy bónusz - egy dublont egy tekercsért. Ez összesen 630 dublont jelent. Tessék, vedd el.";
			link.l1 = "Köszönöm, Marcus!";
			link.l1.go = "mtraxx_18";
		break;
		
		case "mtraxx_18":
			TakeNItems(pchar, "gold_dublon", 630);
			Log_Info("630 dublont kaptál.");
			PlaySound("interface\important_item.wav");
            dialog.text = "Még egy dolog. Ebbôl extra profitra tehetsz szert.";
			link.l1 = "Érdekes... Folytasd.";
			link.l1.go = "mtraxx_19";
		break;
		
		case "mtraxx_19":
            dialog.text = "A vevôd több mint 100 tekercs selymet akar szállítani a következô két hónapban. Ha van, akkor hozzon nekem 20-100 tekercset 24 dublonnáért. Az ajánlat két hónapig érvényes.";
			link.l1 = "Rendben! Hozok többet, ha van.";
			link.l1.go = "mtraxx_20";
			pchar.questTemp.Mtraxx.SilkTrade = "true";
			SetFunctionTimerCondition("Mtraxx_SilkTradeOver", 0, 0, 60, false);
		break;
		
		// торговля шелком
		case "mtraxx_silktrade":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_SHIPSILK);
            dialog.text = "Mennyi van nálad?";
			link.l1 = ""+FindRussianQtyString(iTotalTemp)+".";
			if (iTotalTemp > 100) link.l1.go = "mtraxx_silktrade_2";
			else link.l1.go = "mtraxx_silktrade_1";
		break;
		
		case "mtraxx_silktrade_1":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, iTotalTemp);
			TakeNItems(pchar, "gold_dublon", iTotalTemp*24);
            dialog.text = "Nagyon jó. Fogd az aranyat - 24 dublont egy tekercsért, ahogy megegyeztünk.";
			link.l1 = "Köszönetnyilvánítás!";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_2":
			RemoveCharacterGoods(pchar, GOOD_SHIPSILK, 100);
			TakeNItems(pchar, "gold_dublon", 2400);
            dialog.text = "Száz tekercset kérek. Vegye el az aranyat - 24 dublont egy tekercsért, ahogy megegyeztünk.";
			link.l1 = "Köszönetnyilvánítás!";
			link.l1.go = "mtraxx_silktrade_3";
		break;
		
		case "mtraxx_silktrade_3":
            DialogExit();
			npchar.dialog.currentnode = "First time";
			DeleteAttribute(pchar, "questTemp.Mtraxx.SilkTrade");
		break;
		
		case "mtraxx_20":
            dialog.text = "Beszéljünk valami sürgôsebb dologról, akarsz valami veszélyes dologgal foglalkozni?";
			link.l1 = "Persze, hogyne! Én és az embereim készen állunk, hogy azonnal kihajózzunk.";
			link.l1.go = "mtraxx_24";
		break;
		
		case "mtraxx_22":
            dialog.text = "Az isten szerelmére, "+pchar.name+", hol a pokolban voltál? Emlékszel, amikor azt mondtam, hogy gyere el hozzám? Volt egy munkám a számodra, és most elszállt, hála a kiváló idôzítésednek. Nagyon feldühítettél, fiam. Tûnj el, nem dolgozom olyan emberekkel, akikre nem számíthatok.";
			link.l1 = "Hát, a francba...";
			link.l1.go = "mtraxx_23";
		break;
		
		case "mtraxx_23":
			DialogExit();
            npchar.dialog.currentnode = "First time";
			CloseQuestHeader("Roger_2");
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_24":
			// belamour legendary edition даем флаг и лизензию ГВИК если отсутствует -->
			bOk = IsCharacterPerkOn(pchar,"FlagSpa") || IsCharacterPerkOn(pchar,"FlagHol");
			if(CheckCharacterItem(pchar, "HolTradeLicence") && GetDaysContinueNationLicence(HOLLAND) >= 40 && bOk) sTemp = ".";
			else 
			{
				if(bOk) 
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence") || GetDaysContinueNationLicence(HOLLAND) < 40) 
					{
						sTemp = ", ...valamint 40 napra szóló kereskedelmi engedélyt."; 
						GiveNationLicence(HOLLAND, 40);
					}
				}
				else // нет флага
				{
					if(!CheckCharacterItem(pchar, "HolTradeLicence")) 
					{
						sTemp = ", ...valamint egy 40 napos kereskedelmi engedélyt. Különben is, hogy akarod átverni az erôdben lévô csavargót?! Egy nap még cserben fogsz hagyni ilyen hanyagsággal... Tessék... Vissza fogod adni, ha megérkeztél. Az új generáció, pah...";
						GiveNationLicence(HOLLAND, 40);
						SetCharacterPerk(pchar, "FlagSpa");
						log_info("Spanyol zászlót kaptál");
						pchar.questTemp.GiveMeSpaFlag = true;
					}
					else // есть лицензия
					{	
						if(GetDaysContinueNationLicence(HOLLAND) < 40) 
						{
							sTemp = ". Mondd csak, hogy akarod átverni az erôdben a bunkert?! A papírod nem segít a megfelelô zászló nélkül. Úgy érzem, hogy egy nap cserben fogsz hagyni ilyen hanyagsággal... Tessék, egy kereskedelmi engedély 40 napra, több mint a tiéd. Valamint a spanyol zászló a Maracaibo-i partraszálláshoz. Megérkezés után visszaadja. Az új generáció, pah...";
							GiveNationLicence(HOLLAND, 40);
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("Spanyol zászlót kaptál");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
						else 
						{
							sTemp = ". Mondd csak, hogy akarod átverni az erôdben a bunkert?! A papírod nem segít a megfelelô zászló nélkül. Úgy érzem, hogy egy nap cserben fogsz hagyni engem ilyen hanyagsággal... Tessék... Vissza fogod adni, ha megérkeztél. Az új generáció, pah...";
							SetCharacterPerk(pchar, "FlagSpa");
							log_info("Spanyol zászlót kaptál");
							pchar.questTemp.GiveMeSpaFlag = true;
						}
					}
				}
			}
			// <-- legendary edition
            dialog.text = "Aztán hallgasson figyelmesen. Két hónappal ezelôtt találkozóm volt egy Jean Picard nevû kapitánnyal, akit Jean, a jóképûnek is hívnak. Nem jelent meg a találkozón, és mivel komoly dolgokat akartam vele megbeszélni, utánajártam a hollétének. Kiderült, hogy a mi derék, bátor magánhajósunknak és a brigantijának sikerült harcba keverednie egy spanyol nehézgályával, amelynek parancsnoka don Eduardo de Losad volt, és ô egy kemény fickó. Ennek eredményeképpen Jeant és a legénységének maradékát Maracaibóba vitték, és eladták egy helyi ültetvénynek. Jelenleg itt van, becsületes munkával foglalatoskodik.\nA feladatai a következôk: elôször is - derítse ki szerencsétlenségének részleteit, másodszor - hozza ki élve az ültetvényrôl és hozza ide; nagyon szükségem van a történetének részleteire. Egy 'Moray' nevû bárka kapitányát bízom meg azzal, hogy segítsen neked ebben. A kapitány neve Paul Chant, más néven Pelly the Cutlass. Emlékszel Geffreyre? Majdnem olyan buta, mint ô, de harcolni is jól tud.\nVárni fog rád a Ragget-foknál, Barbadoson. Találd meg ôt és az ô 'Moray' ját, és hajózz el Maracaibo felé. Cutlass hülye kérdések nélkül követi majd a parancsaidat. Valójában egyáltalán nem fog kérdezôsködni. Csak végezze el a munkáját, és jöjjön vissza, én várni fogok magára. Itt van tízezer pezó a jövôbeli kiadásokra"+sTemp+". Van kérdés?";
			link.l1 = "Nincs. Minden világos. Barbadosra megyünk.";
			link.l1.go = "mtraxx_25";
		break;
		
		case "mtraxx_25":
			AddMoneyToCharacter(pchar, 10000);
            dialog.text = "Akkor sok szerencsét kívánok. Legyetek gyorsak, ne várakoztassátok meg Cutlass-t és szegény Jeant.";
			link.l1 = "Persze, fônök! Máris megyek.";
			link.l1.go = "mtraxx_26";
		break;
		
		case "mtraxx_26":
            DialogExit();
			CloseQuestHeader("Roger_2");
			npchar.dialog.currentnode = "mtraxx_wait";
			// belamour legendary edition по пути могут заскочить к Московиту, если рабов нет
			pchar.questTemp.Mtraxx.GiveMeSlaves = "Baster";
			AddQuestRecord("Roger_3", "1");
			AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
			AddMapQuestMarkCity("baster", false);
			Mtraxx_PlantBegin();
		break;
		
		case "mtraxx_27":
			pchar.quest.Mtraxx_PlantGoHomeOver.over = "yes"; 
            dialog.text = "Üdvözöllek újra itthon, bátor kalózom, ha-ha! Legyôztél egy spanyol századot? Picard már elmondta. Szép munka!";
			link.l1 = "Igen, a fiaim keményen szétrúgták ôket, amikor elhajóztunk Maracaibótól.";
			link.l1.go = "mtraxx_28";
			if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup3"))
			{
				dialog.text = "Üdvözöllek újra itthon, bátor korzsair, ha-ha! Picard már elmondta. Szép munka!";
				link.l1 = "...";
				link.l1.go = "mtraxx_28";
			}
		break;
		
		case "mtraxx_28":
            dialog.text = "Látom a szemedben, hogy vársz a jutalmadra. Elég tisztességes. Jean meg fogja fizetni, elvégre az ô életét próbáltuk megmenteni. Küldje el neki a számlát, de késôbb - a fiúnak nincs legénysége és hajója. Okos kölyök, akárcsak te, úgyhogy a jelenlegi állapota nem tart sokáig.";
			link.l1 = "Hm... Nos... Kivárom az idômet. Van valami munka számomra, Marcus? Anélkül, hogy megmentenél vagy keresnél valakit?";
			link.l1.go = "mtraxx_29";
		break;
		
		case "mtraxx_29":
            dialog.text = "Eleged van abból, hogy te legyél a legfényesebb gyertya? Itt csalódást kell okoznom: Van elég agyatlan barom, mint a Cutlass, a te tehetségedet ennek megfelelôen fogom felhasználni. Egy hónapon belül lesz munkám a számodra, most pedig hajózz el Isla Tesoróra, és keresd fel Pasquale Lavoisier-t, ô Sharptown kereskedôje.\nKérte, hogy minél hamarabb küldjek neki egy kemény kalózt egy komoly üzlethez - valószínûleg az, amit te akarsz: kevesebb gondolkodást és több lövöldözést. Egy heted van, hogy megmutasd magad neki, szóval ne vesztegesd az idôt, különben elvesztegeted ezt a küldetést. És légy udvarias, ne próbáld meg becsapni, ezt az embert tisztelik a testvérek között. Most pedig menj és találkozzunk egy hónap múlva. Ne késs!";
			link.l1 = "Rendben Marcus. Viszlát!";
			link.l1.go = "mtraxx_30";
		break;
		
		case "mtraxx_30":
            DialogExit();
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("Spanyol zászlót adtál");
			}
			CloseQuestHeader("Roger_3");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_4", "1");
			pchar.questTemp.Mtraxx = "pasq_start";
			Mtraxx_PasqualeBegin();
			SetFunctionTimerCondition("Mtraxx_PlantFithTaskTimer", 0, 0, 35, false);
			SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
		
		case "mtraxx_31":
            dialog.text = "Whoa! Egy halott ember visszatért! Már eltemettünk téged, fiú! De úgy tûnik, még mindig élsz.";
			link.l1 = "Ahogy látod, Marcus...";
			link.l1.go = "mtraxx_32";
		break;
		
		case "mtraxx_32":
            dialog.text = "Akkor miért tartott ilyen sokáig, hogy Maracaibóból Hispaniolára juss? Most már nem tartozol a szervezetemhez, fiam. Nagyon örülök, hogy életben vagy, de itt nincs több munka számodra.";
			link.l1 = "Eh!... Milyen kár...";
			link.l1.go = "mtraxx_33";
		break;
		
		case "mtraxx_33":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "fail";
		break;
		
		case "mtraxx_34x":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_34";
		break;
		
		case "mtraxx_34":
			/*if (GetNpcQuestPastDayParam(npchar, "task_date") >= 35 && !bImCasual) // опоздал
			{
				dialog.text = "A fenébe "+pchar.name+", hol voltál?! Mondtam, hogy egy hónap múlva találkozunk! Ez nem a hadsereg, de egy kis kibaszott fegyelem elvárható! Tûnj el, nem dolgozom veled többet!";
				link.l1 = "Ahogy akarod...";
				link.l1.go = "mtraxx_33";
				break;
			}*/
			if (GetNpcQuestPastDayParam(npchar, "task_date") < 28) // рано пришёл
			{
				dialog.text = ""+pchar.name+", mondtam neked 'látogass meg egy hónap múlva'. most nincs idôm rád.";
				link.l1 = "Rendben...";
				link.l1.go = "mtraxx_34x";
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_angry")
			{
				dialog.text = "Lavoisier egyik ügynöke azt mondta, hogy megdugtad ôt a fekete fával. Figyelmeztettelek, hogy ne legyél patkány, és legyél tisztességes Pasquale-val szemben. Mindkét szabályomat megszegted. Okos kölyök vagy, de ez elfogadhatatlan. Takarodj innen a pokolba, és felejtsd el az ide vezetô utat.";
				link.l1 = "Basszus...";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_fail")
			{
				dialog.text = "Lavoisier egyik ügynöke azt mondta nekem, hogy átbasztad ôt a fekete fával - nem hozta el az egész adagot. Ha egy agyatlan Cutlass vagy Kopasz lett volna, talán elhittem volna, hogy tényleg nem az egész szállítmányt fogták el, de egy ilyen okos gyerek, mint te... Úgy döntött, hogy átveri Pasquale-t? Megkértelek 'ne csapd be'! Nem bízom benned többé, és nincs többé dolgom veled sem. Takarodj innen a pokolba, és felejtsd el az ide vezetô utat!";
				link.l1 = "A maga Lavoisier-je maga is egy patkány!";
				link.l1.go = "AngryExitAgainWithOut";
				pchar.questTemp.Mtraxx = "fail";
				npchar.dialog.currentnode = "First time";
				CloseQuestHeader("Roger_4");
				break;
			}
			if (pchar.questTemp.Mtraxx == "pasq_late" || pchar.questTemp.Mtraxx == "pasq_sink" || pchar.questTemp.Mtraxx == "pasq_esc")
			{
				pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират // правки прогона 3
				dialog.text = "Ha! Charlie Prince, egy bátor kapitány! Ez az új neved La Vegában, ha nem tudnád. Szóval, élvezted, hogy brutális vagy? Nem? A szerencse ezúttal elfordult tôled? Így élnek az olyan agyatlan ügynökeim, mint Cutlass: ma még egy bordélyházban bulizik, elpazarolja minden keresetét, egy hét múlva pedig már a küszöbömön áll, és pár ezerért könyörög, hogy kifizethesse a hozzá hasonló idiótákkal teli legénységét. Mindegy. Beszéljünk az üzletrôl?";
				link.l1 = "Persze!";
				link.l1.go = "mtraxx_36";
				break;
			}
            dialog.text = "Ha! Charlie Prince, egy bátor kapitány! Ha-ha! Lavoisier egyik ügynöke mondta, hogy jól csináltad. Örülök, hogy sikerült némi tiszteletet mutatnod a mi haszonlesônknek.";
			link.l1 = "Nem ártana, ha nagylelkûbb lenne...";
			link.l1.go = "mtraxx_35";
		break;
		
		case "mtraxx_35":
			pchar.questTemp.Mtraxx.Pasquale.Continue = "true"; // правки прогона 3
            dialog.text = "Emlékszel, mit mondtam az agyatlan barmokról és a lopott áru vásárlóiról? Igen, így van. Soha ne vállalj ilyen munkát a jövôben. Hagyd ezt Cutlassra és a hozzá hasonlókra. Mindegy. Beszéljünk az üzletrôl?";
			link.l1 = "Persze!";
			link.l1.go = "mtraxx_36";
		break;
		
		case "mtraxx_36":
            dialog.text = "Nagyszerû! Jean Picard mindjárt itt lesz, ô majd elmondja a részleteket. Te és Jean együtt fogtok dolgozni ezen a küldetésen. Ráadásul itt az alkalom, hogy visszafizesse az adósságát... Itt is van!";
			link.l1 = "...";
			link.l1.go = "mtraxx_37";
		break;
		
		case "mtraxx_37":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_38";
			chrDisableReloadToLocation = true;
			// преобразуем Пикара
			sld = characterFromId("Mrt_Rocur");
			sld.model = "Jan_Pikar";
		
			SetCharacterPerk(sld, "GunProfessional");
			RemoveCharacterEquip(sld, BLADE_ITEM_TYPE);
			RemoveCharacterEquip(sld, GUN_ITEM_TYPE);
			GiveItem2Character(sld, "blade_17");
			EquipCharacterbyItem(sld, "blade_17");
			GiveItem2Character(sld, "pistol6");
			EquipCharacterbyItem(sld, "pistol6");
			TakeNItems(sld, "bullet", 40);
			TakeNItems(sld, "gunpowder", 40);
			LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
			GiveItem2Character(sld, "cirass7");
			EquipCharacterbyItem(sld, "cirass7");
			sld.dialog.currentnode = "rocur_29";
			sld.greeting = "Rocur_03";
			Characters_RefreshModel(sld);
			LAi_SetCheckMinHP(sld, 10, true, "");
			TakeNItems(sld, "potion2", 7);
			TakeNItems(sld, "potion3", 7);
			TakeNItems(sld, "potion4", 7);
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload1");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "mtraxx_38":
            dialog.text = "Az emberem csatlakozik a rajtaütésedhez. A nevem Luka Bayard, leginkább Luke Leprechaun néven ismert. Ô és az emberei kalózok - vadászok, akik életük nagy részét Hispaniola erdeiben töltötték vadászattal. Tehát mesterei a dzsungelben való túrázásnak, add hozzájuk a harcosaidat, és tekintsd Meridát a tiédnek. A zsákmány harmadik részét te viszed el. A többit Jean viszi el.\nJean, a te részedbôl adózol ennek a bátor kapitánynak, aztán hozd el nekem a maradékot. Majd akkor ezt elintézzük egymás között. Kérdés? Nagyszerû! A kobold várni fog rád a kikötônkben. Sok szerencsét, kalózok, ha-ha!";
			link.l1 = "...";
			link.l1.go = "mtraxx_39";
		break;
		
		case "mtraxx_39":
            DialogExit();
			CloseQuestHeader("Roger_4");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_5", "1");
			pchar.questTemp.Mtraxx = "merida_start";
			Mtraxx_MeridaBegin();
			LAi_SetHuberType(npchar);
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "Mtraxx_MeridaAddPicar", 5.0);
			pchar.GenQuest.HunterLongPause = true;
		break;
		
		case "mtraxx_40":
            dialog.text = "Üdvözöllek újra itthon, bátor gyilkosom! A rajtaütésedrôl szóló pletykák már eljutottak hozzánk.";
			link.l1 = "Nem mondhatnám, hogy örömmel hallom. Az ilyen dolgok jobb, ha ismeretlenek maradnak...";
			link.l1.go = "mtraxx_41";
		break;
		
		case "mtraxx_41":
            dialog.text = "Higgye el, soha nem azok, barátom. Mindegy. Picard eltörölte az adósságát?";
			link.l1 = "Igen.";
			link.l1.go = "mtraxx_42";
		break;
		
		case "mtraxx_42":
            dialog.text = "Igen, uram. Nagyon jó. Luke Leprechaun jó benyomást tett rád?";
			link.l1 = "Igen, jó benyomást tett rám.";
			link.l1.go = "mtraxx_43";
		break;
		
		case "mtraxx_43":
            dialog.text = "Akkor tökéletes. Mindenki boldog, mindenki ki van fizetve.";
			link.l1 = "Van valami munkád számomra, Marcus?";
			link.l1.go = "mtraxx_44";
			// belamour legendary edition отказ после событий Мериды
			link.l2 = "Tudod, Marcus, mindent mérlegeltem, és ez a munka nem nekem való. Sajnálom, de már döntöttem.";
			link.l2.go = "mtraxx_44a";
		break;
		
		case "mtraxx_44":
            dialog.text = "Még nincs igazi munka. Bár szeretnék egy személyes szívességet kérni. Érdekel?";
			link.l1 = "Persze, fônök. Milyen szívességet?";
			link.l1.go = "mtraxx_45";
		break;
		
		case "mtraxx_45":
            dialog.text = "A La Vega partjainál van egy csipke 'Kittie' közel. Napok óta ott várakozik, hogy elkísérjék Bridgetownba. Kizárt dolog, hogy egyedül hagyjam oda hajózni, nyilvánvaló okokból. Lenne olyan kedves elkísérni? Lesz egy igazi munkám a számodra, amikor visszatérsz. És persze pénzt, hogy kifizessem a kíséretért.";
			link.l1 = "Áll az alku.";
			link.l1.go = "mtraxx_46";
		break;
		
		case "mtraxx_46":
            dialog.text = "Szép volt! Jó vitorlázást.";
			link.l1 = "Köszönjük!";
			link.l1.go = "mtraxx_47";
		break;
		
		case "mtraxx_47":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			RemovePassenger(pchar, sld);
			sld = characterFromId("Lepricon");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CloseQuestHeader("Roger_5");
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_6", "1");
			pchar.questTemp.Mtraxx = "ignasio_start";
			sld = characterFromId("Mtr_KittyCap");
			DeleteAttribute(sld, "DontDeskTalk");
			LocatorReloadEnterDisable("LaVega_port", "boat", false);
		break;
		// belamour legendary edition -->
		case "mtraxx_44a":
            dialog.text = "Jó hajózást! Az utcáról szedtelek le, és megtöltöttem a zsebeidet borostyánnal és drágakövekkel! Így hálálod meg?";
			link.l1 = "Merida megmutatta nekem, hogy nem vagyok elég szívtelen ehhez a munkához. Nem olyan szívtelen, mint te és a srácaid. Ne légy gonosz.";
			link.l1.go = "mtraxx_45a";
		break;
		
		case "mtraxx_45a":
            dialog.text = "Gyenge! Hát, tûnj el! Menj, bukj le a teherautóra, vagy még jobb, ha halálra iszod magad, mint a többi lúzer!";
			link.l1 = "...";
			link.l1.go = "mtraxx_46a";
		break;
		
		case "mtraxx_46a":
            DialogExit();
			sld = characterFromId("Mrt_Rocur");
			RemovePassenger(pchar, sld);
			sld = characterFromId("Lepricon");
			RemovePassenger(pchar, sld);
			LAi_SetWarriorType(sld);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			CloseQuestHeader("Roger_5");
			npchar.dialog.currentnode = "First time";
			Group_DelCharacter("Mtr_Kitty", "Mtr_KittyCap");
			sld = characterFromId("Mtr_KittyCap");
			sld.lifeday = 0;
			LocatorReloadEnterDisable("LaVega_port", "boat", false);
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.questTemp.Mtraxx = "fail";
			if(CheckAttribute(pchar, "GenQuest.HunterLongPause")) DeleteAttribute(pchar, "GenQuest.HunterLongPause");
			DoQuestReloadToLocation("LaVega_town", "reload", "reload6", ""); // выставим за дверь
		break;
		// <--- legendary edition
		case "mtraxx_48":
			AddMoneyToCharacter(pchar, 10000);
            dialog.text = "Á, hát itt vagy... Már vártam rád. Itt van 10.000 a 'Kittie'.kísérôjéért.";
			link.l1 = "Köszönöm... Valamit meg kell beszélnem veled, Marcus.";
			link.l1.go = "mtraxx_49";
		break;
		
		case "mtraxx_49":
            dialog.text = "Tényleg?! Ha-ha! Lôjj!...";
			link.l1 = "Emlékszel, hogy Jean Picardot hogyan rabszolgasorba taszították? Elôször kifosztott egy holland karavánt egy brit kalózhajóval együtt, majd ugyanezt tette vele egy spanyol nehézgálya.";
			link.l1.go = "mtraxx_50";
		break;
		
		case "mtraxx_50":
            dialog.text = "Emlékezzenek. És?";
			link.l1 = "Bridgetownban Ignacio Marco keresett meg. Ugyanaz a portugál magánhajó, amelyik Angliát szolgálja. Felajánlotta nekem, hogy fosztogassak egy holland karavánt egy Curacao és Trinidad közötti lakott sziget partjainál.";
			link.l1.go = "mtraxx_51";
		break;
		
		case "mtraxx_51":
            dialog.text = "Nos, nos, nos... Beleegyezett?";
			link.l1 = "Igen, beleegyeztem. Elôször is, jó üzlet volt. Másodszor, eszembe jutott Picard története, és úgy döntöttem, hogy utánajárok...";
			link.l1.go = "mtraxx_52";
		break;
		
		case "mtraxx_52":
            dialog.text = "Lefogadom, hogy így volt.";
			link.l1 = "Biztos vagyok benne. Volt egy karaván, szépen és tisztán elvégeztük a munkát. Aztán a parton felosztottuk a zsákmányt, de elôbb csendben felküldtem egy ôrszemet egy távcsôvel egy dombra. És ez kifizetôdött, mivel nem sokkal késôbb egy spanyol hajóraj jelent meg egy nehéz gálya vezetésével.";
			link.l1.go = "mtraxx_53";
		break;
		
		case "mtraxx_53":
            dialog.text = "A társad biztosan elmenekült, így a spanyolok üldöztek téged?";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.LosadaSink")) 
			{
				link.l1 = "Pontosan. Nem is figyeltek rá. Kár értük: olyan keményen harcoltunk a spanyolokkal, hogy ezt soha nem fogják elfelejteni. Ezek a kasztíliaiak jó harcosok voltak, de nekünk sikerült leszednünk az egész századot.";
				link.l1.go = "mtraxx_53x";
			}
			else
			{
				link.l1 = "Pontosan. Nem is figyeltek rá. Bár nekem sikerült elmenekülnöm. Hála az ôrszememnek...";
				link.l1.go = "mtraxx_53y";
			}
		break;
		
		case "mtraxx_53x":
			DeleteAttribute(pchar, "questTemp.Mtraxx.LosadaSink");
            dialog.text = "Heh! Eduardo de Losad hajóhadának levadászása! Te egy tengeri ördög vagy, herceg! Fogadok, hogy a spanyolok már vadászokat küldtek a segged után.";
			link.l1 = "Rossz nekik... Mindazonáltal el kell intéznünk ezt a söpredéket, Ignacio. Ha érted, mire gondolok.";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_53y":
            dialog.text = "Heh! El tudom képzelni, milyen szarvihar kerekedett, amikor a kasztíliaiak rájöttek, hogy elszöktél tôlük! Szép munka!";
			link.l1 = "Az ô problémájuk, nem az enyém. Mindazonáltal el kell bánnunk ezzel a söpredékkel, Ignacio. Ha érted, mire gondolok.";
			link.l1.go = "mtraxx_54";
		break;
		
		case "mtraxx_54":
            dialog.text = "Majd én elintézem. Többet kellene megtudnunk errôl az Ignacio Marcóról. Lehet, hogy valakinek dolgozik. Az 'érdeklôdése' az embereim iránt gyanús. Milyen hajója van?";
			link.l1 = "A polák, a 'Torero'. Egyedi hajó, eredeti tervezésûnek kell lennie.";
			link.l1.go = "mtraxx_55";
		break;
		
		case "mtraxx_55":
            dialog.text = "Jó, akkor könnyebb lesz követni... Megvan. És neked, herceg, van egy munkám. Készen állsz rá?";
			link.l1 = RandSwear()+"Mindenképpen, fônök!";
			link.l1.go = "mtraxx_56";
		break;
		
		case "mtraxx_56":
            dialog.text = "Akkor hallgasson ide. Nemrég egy különös kalóz járt a környékünkön. A neve Wulfric Iogansen, más néven Vörös Farkas. Nagyon színes egyéniség. Észak-Európából jött ide néhány évvel ezelôtt. Ez a viking nem fizette Levasseur védelmi díját, nem barátkozott, és egyedül maradt. Nagyon titokzatos típus, a legénységét még soha senki nem hagyta el élve. Az a hír járta, hogy személyesen vágta le a nyelvét azoknak a legénységébôl, akiknek a kocsmákban elernyedt a nyelve a portyáikról...\nA legtöbb fajtársunkkal ellentétben Wulfric sosem pazarolta a pénzt kurvákra vagy italokra. Soha nem adta el a zsákmányát fillérekért. Soha nem bízott a bankárokban, és soha nem cserélt hajót. Volt egy remek korvettje, a 'Freyja' és egy hûséges legénysége, amelyet jól megfizetett a szolgálatért és a hallgatásért. Azt hiszem, azt tervezte, hogy minél több aranyat elrejt, majd visszatér Európába, és ott királyként él.\nA spanyol vadászoknak köszönhetôen nem jött össze neki. Ez az ember kolosszális károkat és veszteségeket okozott Spanyolországnak, ezért büntetôexpedíciók vadásztak rá Hispaniola vizein belül, és elsüllyesztették a 'Freyját' és megölték az egész legénységet Farkassal együtt. A spanyol hajók által körülzárt sekély vízben Vörös Farkas a halálát lelte.\nTény, hogy La Vegában mindenki tudott Wolf kincseirôl, és még egy elsüllyedt 'Freyja', is talált, de sem a helyi, sem az indián búvárok nem találtak kincseket. Nem volt bolond, és biztos volt valahol azon a helyen egy hatalmas egy rejtekhely, amirôl csak ô és a legénysége tudott, de nem kérdezhetjük meg ôket... nyilvánvaló okokból. De most jön az érdekes rész: Nálam van a sértetlen hajónaplója, ami a hajóján lévô zárt ládában volt elrejtve. Nincs benne nyilvánvaló nyom a kincshez, de megpróbálhatjátok megtalálni ôket a szavak között. Olvassátok el a hajónaplót, derítsétek ki, hová rejtette el a viking a kincseit két évnyi rablás után a Karib-tengeren, és találjátok meg ôket. Ha sikerrel jársz - a kétharmad a tiéd. Benne vagy?";
			link.l1 = "Hm... úgy hangzik, mintha egy fekete macskát keresnél egy sötét szobában. Hol van a napló?";
			link.l1.go = "mtraxx_57";
		break;
		
		case "mtraxx_57":
            dialog.text = "Tessék, vedd el. Sok szerencsét!";
			link.l1 = "Köszönöm, szükségem lesz rá...";
			link.l1.go = "mtraxx_58";
		break;
		
		case "mtraxx_58":
            DialogExit();
			CloseQuestHeader("Roger_6");
			npchar.dialog.currentnode = "mtraxx_wait";
			GiveItem2Character(pchar, "wolfreeks_book");
			AddQuestRecord("Roger_7", "1");
			pchar.questTemp.Mtraxx = "wolfreek_start";
			pchar.questTemp.Mtraxx.Logbook.CanRead = "true";
			pchar.questTemp.Mtraxx.Logbook.Page1 = "true";
			bQuestDisableMapEnter = true;//закрыть карту
			pchar.GenQuest.MapClosedNoBattle = true;
		break;
		
		case "mtraxx_59":
            dialog.text = "Á, ott van a mi bátor kapitányunk. Mi van Vörös Farkas kincseivel?";
			link.l1 = "Dolgozom rajta. Szükségem van a segítségedre.";
			link.l1.go = "mtraxx_60";
		break;
		
		case "mtraxx_60":
            dialog.text = "Csupa fül vagyok.";
			link.l1 = "Wulfric naplójábanGord számomra ismeretlen szó van többször is leírva 'Gord'. Tudnom kell a jelentését, hogy tovább tudjak haladni a nyomozásban.";
			link.l1.go = "mtraxx_61";
		break;
		
		case "mtraxx_61":
            dialog.text = "Hm... Azt mondod Gord... Ezt még sosem hallottam korábban. Rendben, egy hét múlva találkozunk: Konzultálok néhány nagyokossal, akik a hajókon szolgálnak pénztárosként. Ôk legalább tudnak számolni és olvasni. Talán adnak valami ötletet.";
			link.l1 = "Rendben Marcus. Akkor egy hét múlva találkozunk.";
			link.l1.go = "mtraxx_62";
		break;
		
		case "mtraxx_62":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			SetFunctionTimerCondition("Mtraxx_WolfreekTimer", 0, 0, 7, false);
		break;
		
		case "mtraxx_63":
            dialog.text = "Van egy válaszom a számodra. Egy okostojás felvilágosított. Gord egy szabad jarl megerôsített települése.";
			link.l1 = "Egy szabad jarl? Ki az?";
			link.l1.go = "mtraxx_64";
		break;
		
		case "mtraxx_64":
            dialog.text = "Valamiféle kalóz viking admirális. Én például egy szabad jarl vagyok, és La Vega az én gordom. Úgy tûnik, Vörös Farkas élvezte az ôsei történetét, ha-ha! Segítettek ezek az információk?";
			link.l1 = "Még nem tudom. Elôbb össze kellene hasonlítanom a jegyzeteket. A Gord akkor települést jelent... Köszönöm Marcus!";
			link.l1.go = "mtraxx_65";
		break;
		
		case "mtraxx_65":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			Mtraxx_WolfreekReadLogbookFourth();
		break;
		
		case "mtraxx_66":
            dialog.text = "Na és? Az önelégült arcod azt mondja, hogy sikerrel jártál.";
			link.l1 = "Igen, ez az. Vörös Farkas kincsét megtaláltuk! Bár nem volt könnyû.";
			link.l1.go = "mtraxx_67";
		break;
		
		case "mtraxx_67":
            dialog.text = "Mennyit rejtegetett a vikingünk?";
			link.l1 = "750.000 pezó és 900 dublon.";
			link.l1.go = "mtraxx_68";
		break;
		
		case "mtraxx_68":
            dialog.text = "Ho-ho! Jól csináltad, herceg. Mi lesz a részemmel?";
			if (sti(pchar.money) >= 250000 && PCharDublonsTotal() >= 300) // belamour legendary edition
			{
				link.l1 = "Tessék, fogd ezt. A megállapodásunk szerint: 250 000 pezó és 300 dubloon.";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "Az összes pezó és dubloon a kabinomban van. Adj egy percet, hogy idehozzam ôket!";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_68_1":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_68_2";
		break;
		
		case "mtraxx_68_2":
            dialog.text = "Elhozta a részemet?";
			if (sti(pchar.money) >= 250000 && PCharDublonsTotal() >= 300) // belamour legendary edition
			{
				link.l1 = "Tessék, fogd ezt. A megállapodásunk szerint: 250 000 pezó és 300 dubloon.";
				link.l1.go = "mtraxx_69";
			}
			else
			{
				link.l1 = "Igen-igen, már úton vagyok!";
				link.l1.go = "mtraxx_68_1";
			}
		break;
		
		case "mtraxx_69":
			AddMoneyToCharacter(pchar, -250000);
			RemoveDublonsFromPCharTotal(300); // belamour legendary edition
			PlaySound("interface\important_item.wav");
            dialog.text = "Nagyon jó. Megint remekül csináltad. Szép munka!";
			link.l1 = "Marcus, találtál valamit Ignacio Marcóról?";
			link.l1.go = "mtraxx_70";
			// mitrokosta возможность отстройки исламоны
			pchar.questTemp.IslaMona = "start";
		break;
		
		case "mtraxx_70":
            dialog.text = "Igen, de elôbb le kell ellenôriznem...";
			link.l1 = "Micsoda?";
			link.l1.go = "mtraxx_71";
		break;
		
		case "mtraxx_71":
            dialog.text = "Van egy olyan gyanúm, hogy Marco kapcsolatban áll valakivel... És szükségem van rád, hogy kiderítsd. Hajózz Martinique-ra. Hagyd el a hajódat Saint Pierre-ben, és a dzsungelen keresztül menj Le Francoisba. Azt mondták, hogy az emberünket látták ott. Ne kérdezôsködj a kalózoktól, csak figyelj és figyelj. Ha megtaláltátok a fickót, kövessétek, és nézzétek meg, hová megy, vagy kivel találkozik. Ne támadjátok meg ôt vagy a hajóját 'mert ezzel tönkretennétek egy tervet, amire most készülök! Figyelmeztettelek!\nKövessétek és figyeljétek ôt, és amint eleget tudtok, térjetek vissza hozzám. Megértem, hogy a kezed legszívesebben megfojtanád a fattyút, de az eszed maradjon nyugodt. Most pedig menj. Három heted van. Sok szerencsét!";
			link.l1 = "Máris megyek, fônök.";
			link.l1.go = "mtraxx_72";
		break;
		
		case "mtraxx_72":
            DialogExit();
			CloseQuestHeader("Roger_7");
			RemoveItems(pchar, "wolfreeks_book", 1);
			npchar.dialog.currentnode = "mtraxx_wait";
			AddQuestRecord("Roger_8", "1");
			pchar.questTemp.Mtraxx = "corrida_start";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_martinique.win_condition.l1.location = "Martinique";
			pchar.quest.mtraxx_corrida_martinique.function = "Mtraxx_CorridaStart";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1 = "location";
			pchar.quest.mtraxx_pasq_continue.win_condition.l1.location = "LaVega_exittown";
			pchar.quest.mtraxx_pasq_continue.function = "Mtraxx_PasqualeJan";
			bDisableFastReload = true;
			//SaveCurrentNpcQuestDateParam(npchar, "task_date");
		break;
			
		case "mtraxx_73":
			/*if (GetNpcQuestPastDayParam(npchar, "task_date") >= 22) // опоздал
			{
				dialog.text = "A francba, Prince! Bosszút állhatnál és pokolian sok pénzt kaphatnál, ha nem lennél ilyen lassú! Nem ezt vártam tôled, de mivel jó gyerek vagy, megbocsátok neked. Egy hónap múlva lesz esélyed visszaszerezni a jó hírnevedet a szememben. Mindenkit összegyûjtök egy rajtaütésre!\nJöjjetek hozzám egy hónap múlva egyetlen, de erôs hajóval. Luke, Cutlass, Geffrey és Jean is részt vesznek ebben. Ne késsetek, még egy napot se!";
				link.l1 = "Megértem Marcus. Nem fordul elô többet!";
				link.l1.go = "mtraxx_73x";
				break;
			}*/
			dialog.text = "Jó idôzítés! Jelentkezz nálam, most.";
			link.l1 = "Lenyomoztam a kötelezettemet Le Francois-ban. A polákja egy korvettbôl és egy fregattból álló hajóraj tagja volt. Maga Marco is Barbaszonba látogatott, két órán át tárgyaltak nála, a többi látogatót elküldték az ôrei. Aztán két komor fickóval ment ki a házból: az egyik vörös hajú és szakállas volt, reiteres kurírban, a másik bajuszos volt, és nehéz lövészárokpáncélt viselt. Mindannyian a kikötôbe mentek, és elhajóztak, mielôtt Saint Pierre-be értem volna.";
			link.l1.go = "mtraxx_74";
		break;
		
		/*case "mtraxx_73x":
            DialogExit();
            npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "5");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 1, false); // belamour legendary edition увеличим таймер 
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 1, false);
			SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 92, false);
		break;*/
		
		case "mtraxx_74":
            dialog.text = "Ez rendben van. Most már látom a teljes képet. Ez a két szemétláda, akit láttál, Barbazon vagy Jackmannek dolgozik. Majdnem olyanok, mint az én Kopaszom és Vágóhíjam, de jobban harcolnak. A vörös hajút Prowlernek hívják, ô a 'Cuttlefish', egy korvett kapitánya, a bajszos fickó pedig Ghoul, ô vitorlázik a 'Merciless', egy fregatton. Ami Ignacio barátunkat illeti - ô nemcsak a briteknek és a spanyol don Losadnak dolgozik, hanem Barbazonak is. Ezért próbált téged és Picardot bemártani.";
			link.l1 = "Miért?";
			link.l1.go = "mtraxx_75";
		break;
		
		case "mtraxx_75":
            dialog.text = "Barbazon parancsa. Nem tudtad, de Jacques nem hagyja ki az alkalmat, hogy belehugyozzon a zabkásámba. Nyilvánvaló okokból soha nem állna nyíltan ellenem, ezért titokban keresztbe tesz nekem. Tudta, hogy Picard és te az én embereim vagytok. Az, hogy a zsoldosát küldte önök után, az ô stílusa volt, és nem egy idiótát küldött, ahogy arról ön is megbizonyosodott.";
			link.l1 = "Meglátogatom Barbazont, amint elintéztem Marcót...";
			link.l1.go = "mtraxx_76";
		break;
		
		case "mtraxx_76":
            dialog.text = "Szedd ki ezt a szart a fejedbôl! Nincs esélyed Barbazon ellen nyílt összecsapásban. Könnyedén szétbassza a fejedet. A saját cselvetésével fogjuk meghálálni neki - a társai leütésével. Készen állsz erre? Ez egy mocskos ügy.";
			link.l1 = "Úgy hangzik, mint az én üzletem!";
			link.l1.go = "mtraxx_77";
		break;
		
		case "mtraxx_77":
            dialog.text = "Ignacio Marco, Prowler, Goul és egy másik Barbazon fickó, Joker Jim terve, hogy elfoglalják az Aranyflotta egyik spanyol hajóját. Az egész akciót maga Barbazon tervezte ki, és a kémjeimtôl sikerült megtudnom a részleteket. Az Aranyflotta egyik nehéz gályája Havannában vesztegelt a hajógyárban, míg az egész hajóraj elindult Spanyolországba. A gályát megjavították, és hamarosan Európába indul, két másik hajóval együtt. A hajóraj Kubából északkelet felé fog haladni, de nem tudom, milyen útvonalon.\nAzt az információt kaptam, hogy a spanyol hajók Santo Domingóig hajóznak, majd Puerto Rico partjai mentén egészen az óceánig. Barbazon is tudja ezt. Mivel azonban Hispaniolát nemcsak délrôl, hanem északról is meg lehet kerülni, megváltoztatva az útvonalat, és Turkson, vagy Isla-Tesorón keresztül, Santo Domingóba való behajózás nélkül távozhat az óceánba, Jacques úgy döntött, hogy biztosra megy, és a ravasz róka Ignaciót Kubába küldi.\nMarco feladata, hogy megszerezze a Kubából kihajózó spanyol gálya menetrendjét, amelynek késôbb kellene utolérnie a flotta többi tagját. Vannak kapcsolatai a spanyolokon belül, így ez a feladat nem okoz neki gondot. Barbazon bandájának többi tagja Saint Martinban várja Marcót, ami optimális hely arra, hogy elkezdjék a zsákmány vadászatát. Mivel Marco és a hollandok nem túl jó barátok, nem fog tudni bejutni Saint Martin vizein belülre, ezért távoli üzenetet kell küldenie társainak...";
			link.l1 = "Azt hiszem, tudom, mit kell tennem...";
			link.l1.go = "mtraxx_78";
		break;
		
		case "mtraxx_78":
            dialog.text = "Meglep, hogy ilyen okos vagy, de még nem fejeztem be. Gabriela Chapada segítségével megzavartam ezt a tervet. Ismered ôt. Együtt tájékoztattuk a spanyolokat, hogy a kalózok csapdáját Puerto Ricótól nem messze fogják felállítani. Így a gálya nem fog áthajózni azon a területen, hanem titokban egy kalózvadászokból álló századot küldtek oda helyette. Számos feladatuk van. Az elsô az lesz, hogy megtaláljátok és elfogjátok a 'Torero'. Gondolom, tudjátok, mit kell tennetek a kapitányával.";
			link.l1 = "Természetesen...";
			link.l1.go = "mtraxx_79";
		break;
		
		case "mtraxx_79":
            dialog.text = "Másodszor, ki kell derítened a spanyol arany gálya valódi útvonalát. Marcónak tudnia kell a menetrendjét. Szerezd meg és küldd el nekem.";
			link.l1 = "Hogyan?";
			link.l1.go = "mtraxx_80";
		break;
		
		case "mtraxx_80":
			GiveItem2Character(pchar, "Dove"); 
            dialog.text = "Repülôvel. Fogj egy ketrecet... Ô Spyke, egy postagalamb, aki itt született és nôtt fel, La Vegában. Mindig ide fog találni, még Trinidadból is. Ha megkapta a menetrendet, írjon egy cetlit, ragassza a lábára, és engedje szabadon. Spyke néhány órán belül hozzám repül. Vigyázz rá, herceg!";
			link.l1 = "Természetesen, fônök!";
			link.l1.go = "mtraxx_81";
		break;
		
		case "mtraxx_81":
            dialog.text = "Harmadszor, hajózz el Saint Martinra a 'Torero'. Csak rajta egyedül! Különben túl hamar gyanút fognak. Adj nekik jelet, hogy hajózzanak Puerto Ricóba, ahol a spanyolok várnak. A jelkódjuknak ott kell lennie Marco papírjaiban. Vagy személyesen tôle tudod meg ôket.";
			link.l1 = "Értem. Okos húzás Barbazon embereit a spanyolokhoz küldeni, ha-ha!";
			link.l1.go = "mtraxx_82";
		break;
		
		case "mtraxx_82":
            dialog.text = "Pontosan! Az árnyékból fogok neki csapást mérni. Ahogy ô is tette. És még egy utolsó dolog: amint jelet küldesz nekik, azonnal hajózz ki, hogy elfogd a spanyol gályát és kíséretét. Nincs vesztegetni való idônk.";
			link.l1 = "Egy polakre? Egy nehéz gálya és még két hajó ellen, és biztosan nem szkúnerek ellen? Szét fognak tépni!";
			link.l1.go = "mtraxx_83";
		break;
		
		case "mtraxx_83":
            dialog.text = "Ne sírj, mint egy kislány! Miért gondolod, hogy Spyke-ot küldesz? Nem maradsz erôsítés nélkül. Csak ne hagyd, hogy a karaván elmeneküljön, ne engedd, hogy az óceánhoz jussanak. Megértetted?";
			link.l1 = "Igen, fônök.";
			link.l1.go = "mtraxx_84";
		break;
		
		case "mtraxx_84":
            dialog.text = "A jutalmad egy nagy rakás arany lesz, plusz Marco polákja. Az emberek azt mondják, hogy ez egy átkozottul jó hajó. Van kérdés? Megértetted a küldetésedet?";
			link.l1 = "Nem vagyok Cutlass, tudom, mit kell tennem. Hol kell elkapnom a 'Torero'?";
			link.l1.go = "mtraxx_85";
		break;
		
		case "mtraxx_85":
            dialog.text = "Miközben mi ezt a beszélgetést folytatjuk, a hajó gyorsan elhajózik Kubából egyenesen Philipsburgba. Most Tortuga körül lehet, vagy attól keletre. Szóval emeljük fel a horgonyt, és hajózzunk Saint Martin felé, kapjuk el a 'Torerót' nem messze a szigettôl, csak Barbazon emberei ne lássák a harcot, különben a tervemnek annyi.";
			link.l1 = "Azonnal!";
			// belamour legendary edition испанский флаг к выдаче -->
			if(IsCharacterPerkOn(pchar,"FlagSpa")) link.l1.go = "mtraxx_86";
			else link.l1.go = "mtraxx_85f";
		break;
		
		case "mtraxx_85f":
			SetCharacterPerk(pchar, "FlagSpa");
			log_info("Spanyol zászlót kaptál");
			pchar.questTemp.GiveMeSpaFlag = true;
            dialog.text = "Mi a fene? Azzal a kandallóból egy piszkavassal megpattintanálak, herceg. Nem gondoltam, hogy elemi dolgokról kell majd beszélnem. Tartsd a spanyol zászlót, különben az egészet elbukod, anélkül, hogy elkezdenéd. Add vissza nekem. Most pedig tûnj el innen!";
			link.l1 = "Már a tengeren vagyok, fônök.";
			link.l1.go = "mtraxx_86";
		break;
		// <-- legendary edition
		case "mtraxx_86":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			DeleteAttribute(pchar, "GenQuest.CannotWait");
			AddQuestRecord("Roger_8", "6");
			pchar.questTemp.Mtraxx = "corrida_marko";
			/*pchar.quest.mtraxx_corrida_landtimer.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.hour  = sti(GetTime()+1);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 0);
			pchar.quest.mtraxx_corrida_landtimer.function = "Mtraxx_CorridaLandTimer";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1 = "location";
			pchar.quest.mtraxx_corrida_checktime.win_condition.l1.location = "Hispaniola1";
			pchar.quest.mtraxx_corrida_checktime.function = "Mtraxx_CorridaCheckTime";*/
			pchar.quest.mtraxx_corrida_torero.win_condition.l1 = "Timer";
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.hour  = sti(GetTime()+12);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.mtraxx_corrida_torero.function = "Mtraxx_CorridaToreroOnMap";
			SetFunctionTimerCondition("Mtraxx_CorridaTimeFindTorero", 0, 0, 7, false); // время на перехват Тореро, снимать при потоплении или захвате
		break;
		
		case "mtraxx_87":
            dialog.text = "Szóval, Herceg, te mindent elszúrtál, mi?";
			link.l1 = "Igen, így van. Ez a küldetés sokkal nagyobb kihívás volt, mint gondoltam. Mondj egy dühítô beszédet és mutasd meg az ajtót.";
			link.l1.go = "mtraxx_88";
		break;
		
		case "mtraxx_88": // belamour legendary edition увеличиваем срок
            dialog.text = "Gyerünk, hagyd abba. Megtörténik. Te egy jó harcos vagy, és mindannyian elbukunk néha. Kár, hogy nem szereztük meg azt az aranyat... de ha egy helyen nem szereztük meg, akkor máshonnan kellene, ha-ha! Lesz esélyed visszaszerezni a hírnevedet: gyere el hozzám három hét múlva, és lehetôleg egy erôsebb hajón, de csak egy - egy egész század leszünk. Mindenkit összegyûjtök egy rajtaütésre!\nHárom hét múlva gyertek hozzám egyetlen, de erôs hajón. Luke, Cutlass, Geffrey és Jean is részt vesznek ebben. Ne késsetek el!";
			link.l1 = "Nem leszek a fônök!";
			link.l1.go = "mtraxx_89";
		break;
		
		case "mtraxx_89":
            DialogExit();
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("Spanyol zászlót adtál");
			}
			npchar.dialog.currentnode = "First time";
			pchar.questTemp.Mtraxx = "wait_month";
			AddQuestRecord("Roger_8", "22");
			SetFunctionTimerCondition("Mtraxx_CartahenaTavernPrepare", 0, 0, 1, false); // belamour legendary edition увеличим таймер 
			SetFunctionTimerCondition("Mtraxx_CartahenaPrepare", 0, 0, 1, false);
			//SetFunctionTimerCondition("Mtraxx_CartahenaLate", 0, 0, 92, false);
			if (CheckCharacterItem(pchar, "Dove")) RemoveItems(pchar, "Dove", 1);
		break;
		
		case "mtraxx_board":
            dialog.text = "Ho-ho, Ahoy, kölyök! Nem számítottál rá, hogy itt látsz, igaz? Ha-ha-ha! Végül is megtaláltuk a spanyol karavánt...";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Gold")) // был абордаж
			{
				link.l1 = "Igen fônök, megtaláltuk, bár nem volt könnyû.";
				link.l1.go = "mtraxx_board_1";
			}
			else
			{
				link.l1 = "Igen, de az arany gálya elsüllyedt az összes aranyával együtt.";
				link.l1.go = "mtraxx_board_7";
			}
		break;
		
		case "mtraxx_board_1":
			iTotalTemp = GetSquadronGoods(pchar, GOOD_GOLD);
            dialog.text = "Mennyi aranyat szereztünk, herceg?";
			if (iTotalTemp < 1) link.l1 = "Eh... Semmi.";
			else link.l1 = "Heh... "+iTotalTemp+" összesen!";
			link.l1.go = "mtraxx_board_2";
		break;
		
		case "mtraxx_board_2":
			if (iTotalTemp < 20)
			{
				dialog.text = "A francba! A spanyolok biztos a tengerbe dobták, hogy ne kapjuk meg. Legalább fizettek érte. Barbazon embereivel együtt, ami szintén gyôzelem...";
				link.l1 = "Sajnálom az aranyat... Mi a következô Marcus? La Vegába megyünk?";
				link.l1.go = "mtraxx_board_4";
				AddQuestRecord("Roger_8", "18");
				break;
			}
			if (iTotalTemp >= 20 && iTotalTemp < 300)
			{
				dialog.text = "Szánalmas. Ez még csak nem is kompenzálja az itteni túrámat. A spanyolok biztos a tengerbe dobták, hogy ne kapjuk meg. Legalább fizettek érte. Ahogy Barbazon emberei is, ami szintén gyôzelem...";
				link.l1 = "Sajnálom az aranyat... Azért osszuk el.";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				break;
			}
			if (iTotalTemp >= 300 && iTotalTemp < 700)
			{
				dialog.text = "Ez egy szegényes díj. Épp elég a költségek fedezésére. A spanyolok biztos a tengerbe dobták egy részét, hogy ne kapjuk meg. Legalább fizettek érte. Ahogy Barbazon emberei is, ami szintén gyôzelem...";
				link.l1 = "Sajnálom az aranyat... Azért osszuk el.";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "19");
				AddCharacterExpToSkill(pchar, "Fortune", 100);
				break;
			}
			if (iTotalTemp >= 700 && iTotalTemp < 1000)
			{
				dialog.text = "Nem rossz, bár jobbra számítottam. A spanyolok biztos a tengerbe dobták egy részét, hogy ne kapjuk meg. Legalább fizettek érte. Ahogy Barbazon emberei is, ami szintén gyôzelem...";
				link.l1 = "Osszuk fel a nyereményt!";
				link.l1.go = "mtraxx_board_3";
				AddQuestRecord("Roger_8", "20");
				AddCharacterExpToSkill(pchar, "Fortune", 200);
				break;
			}
			dialog.text = "Pompás! Szép nyereményt kaptunk, barátom! És Barbazon emberei megkapták, amit megérdemeltek, ha-ha!";
			link.l1 = "Heh, ez egy rakás arany! Osszuk szét!";
			link.l1.go = "mtraxx_board_3";
			AddQuestRecord("Roger_8", "21");
			AddCharacterExpToSkill(pchar, "Fortune", 300);
		break;
		
		case "mtraxx_board_3":
			RemoveCharacterGoods(pchar, GOOD_GOLD, makeint(iTotalTemp/2));
			WaitDate("", 0, 0, 0, 3, 10);
			LAi_Fade("", "");
            dialog.text = "... ahogyan azt a Testvériségben mindig is szoktuk - mindenkinek tisztességes rész jut. Megtarthatod a 'Torero', ô a tiéd.";
			link.l1 = "Mi a következô Marcus? La Vegába megyünk?";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_board_4": // belamour legendary edition увеличиваем срок до 3х месяцев
            dialog.text = "Én biztosan La Vegában leszek, három hétig ott foglak várni. Gyere, ha készen állsz. Lehetôleg egy erôsebb hajón, de csak egy hajón - egy egész század leszünk. Minden emberemet menetelésre indítom. Ti is az én parancsnokságom alá tartoztok, Jean Szépfiú, Kopasz Geoffrey, Cleaver Pelly és Luke Leprechaun. Készüljetek. Komoly expedíció és meglehetôsen nagy zsákmány vár ránk. A részleteket késôbb fogjátok megtudni.";
			link.l1 = "Remek fônök! Találkozunk La Vegában három hét múlva.";
			link.l1.go = "mtraxx_board_5";
		break;
		
		case "mtraxx_board_5":
            dialog.text = "Viszlát, gyilkosok! Ha-ha!";
			link.l1 = "...";
			link.l1.go = "mtraxx_board_6";
		break;
		
		case "mtraxx_board_6":
            DialogExit();
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Ship_SetTaskRunAway(SECONDARY_TASK, sti(npchar.index), sti(pchar.index));
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.quest.mtraxx_corrida_complete.win_condition.l1 = "MapEnter";
			pchar.quest.mtraxx_corrida_complete.function = "Mtraxx_CorridaComplete";
			RemoveItems(pchar, "wolfreeks_book", 1);
			// belamour legendary edition забрать флаг обратно
			if(CheckAttribute(pchar, "questTemp.GiveMeSpaFlag")) 
			{
				DeleteAttribute(pchar, "questTemp.GiveMeSpaFlag")); 
				DeleteAttribute(pchar,"perks.list.FlagSpa"); 
				log_info("Spanyol zászlót adtál");
			}
		break;
		
		case "mtraxx_board_6x":
            dialog.text = "Még valami?";
			link.l1 = "Nem, nem hiszem. Már megyek is a hajómra.";
			link.l1.go = "mtraxx_board_6y";
		break;
		
		case "mtraxx_board_6y":
            DialogExit();
			npchar.DeckDialogNode = "mtraxx_board_6x";
		break;
		
		case "mtraxx_board_7":
            dialog.text = "Heh! És kinek a hibája ez a herceg? A tiéd volt?";
			link.l1 = "Sajnálom, fônök, de mindketten elég jók voltunk... Te is kiválóan lôttél. Egyébként szépen céloztál...";
			link.l1.go = "mtraxx_board_8";
		break;
		
		case "mtraxx_board_8":
            dialog.text = "Mindegy. Mindketten hibáztunk. Azért nem állunk üres kézzel - Barbazon emberei megkapták, ami nekünk jutott, ez már önmagában is gyôzelem...";
			link.l1 = "Sajnálom az aranyat... Mi a következô Marcus? La Vegába megyünk?";
			link.l1.go = "mtraxx_board_4";
		break;
		
		case "mtraxx_90x":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_90";
		break;
		
		case "mtraxx_90":
			pchar.quest.Mtraxx_CartahenaLate.over = "yes";
			if (GetCompanionQuantity(pchar) > 1)
			{
				dialog.text = "Herceg, agyatlan lettél? Mondtam, hogy csak egy hajót hozzatok! Menj, szabadulj meg a többitôl és gyere vissza, amilyen hamar csak tudsz! Azonnal!";
				link.l1 = "Jól van, jól van!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (RealShips[sti(pchar.Ship.Type)].Type.Merchant) // торговые
			{
				dialog.text = "Herceg, úgy döntöttél, hogy te leszel a második Cutlassom? Miért hoztál nekem egy kereskedelmi hajót? Számítottam rád! Menj, hozz egy rendes hadihajót! Hozd ide a hadihajót!";
				link.l1 = "Jól van, jól van!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) > 3)
			{
				dialog.text = "Herceg, megleptél engem. Mondtam, hogy hozz egy hadihajót! Hogyan fogsz segíteni nekem ezen a kádon? Gyere vissza ide egy harmad- vagy másodrangú hajóval, nem kevesebbel és nem magasabbal! Most! Nem fogok senkire sem várni.";
				link.l1 = "Jól van, jól van!";
				link.l1.go = "mtraxx_90x";
				break;
			}
			if (sti(RealShips[sti(pchar.ship.type)].Class) < 2)
			{
				dialog.text = "Herceg, miért nem hozod ide a Tengerek Uralkodóját? Amikor azt mondtam, hogy hozzatok egy hadihajót, nem úgy értettem, hogy egy kibaszott hadihajót! Gyere vissza ide egy harmad- vagy másodosztályú hajóval! Azonnal! Nem fogok senkire sem várni.";
				link.l1 = "Jól van, jól van!";
				link.l1.go = "mtraxx_90x";
				break;
			}
            dialog.text = "Jó idôzítés, korzikai! Örülök, hogy egy darabban látlak! Készen állsz az utazásra?";
			link.l1 = "Persze, fônök. Mindig készen állok.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx.Corrida.Barbazon")) link.l1.go = "mtraxx_91";
			else link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_91":
            dialog.text = "Egyébként, kíváncsi vagy Barbazon századára, amit Puerto Ricóba küldtél?";
			link.l1 = "Teljesen kiment a fejembôl. Persze, hogy akarom. Megtalálták a végzetüket?";
			link.l1.go = "mtraxx_92";
		break;
		
		case "mtraxx_92":
            dialog.text = "A pokolba is, igen! A zászlóshajó - Joker Jim fregattja 'Owl', porig égett. Maga Joker Jim nyomtalanul eltûnt. A Csavargót és a Ghoult keményen megverték, de sikerült elmenekülniük: a Csavargónak - Tortugára, La Rocha ágyúinak védelme alatt, a Ghoulnak - Isla Tesoróra. Pasquale elmondta, hogy Ghoul is partra szállt a hajójával a Sharptown melletti zátonyokon, és alig tudott lejönni róluk. Alexus mesternek most sok dolga van, hehe. Általában a spanyolok egy kicsit felbosszantottak. Azt hittem, mindenkit megölnek.";
			link.l1 = "Heh. Mindegy, még mindig Barbazon csizmájába pisáltunk. Üzenetet adtunk neki.";
			link.l1.go = "mtraxx_93";
		break;
		
		case "mtraxx_93":
            dialog.text = "Ez igaz. Beszéljünk az üzletrôl.";
			link.l1 = "Csupa fül vagyok.";
			link.l1.go = "mtraxx_94";
		break;
		
		case "mtraxx_94":
            dialog.text = "A hírszerzô szolgálatom jó barátom, Bernard Vensan személyében jelentett egy hatalmas halom aranyrudat, amit a spanyolok Cartagenában tároltak. Pontosabban az erôd alatt. Normális esetben a spanyol aranyflottának tulajdonították volna, de ezúttal a miénk. Elindulunk a déli fôútra, hogy megrohamozzuk Cartagenát.";
			link.l1 = "Argh! Jól hallottam? Egy egész gyarmatot fogunk kifosztani, egy kibaszott erôddel?";
			link.l1.go = "mtraxx_95";
			// belamour legendary edition отказ от великого похода
			link.l2 = "Nem megyek veled Cartagenába, Marcus. Egy egész várost felgyújtani nem az én történetem.";
			link.l2.go = "mtraxx_94a";
		break;
		
		case "mtraxx_95":
            dialog.text = "Jól hallottad. Pontosan ezt fogjuk tenni. A hadihajóm elintézi az erôdöt, természetesen a maga segítségével. Bold Jeffrey szárazföldi csapatokat fog szállítani a hollandoktól lopott új kelet-indiai hajóján. Pelly végre megszabadult az ütött-kopott brigantijától, és szerzett egy rendes korvettet, persze nem az én anyagi segítségem nélkül. Paul Chant és te felelsz a járôrflotta kiiktatásáért, a legénységetek is részt vesz a rohamban, és te, Charles, te olyan jó harcos és kapitány, segítesz nekem az erôd elpusztításában.\nJean Picard nem jelent meg, ami furcsa, hiszen a korvettjét Port Royalban látták. Nos, ha nem érdekli a spanyol arany, az az ô baja, szóval baszódjon meg. Helyette Bernard Vensan barátom csatlakozik a rajtaütéshez. Plusz, Leprechaun a kalózokkal együtt segít a csapatainknak. Elvisszük az aranyat az erôdbôl és a váltságdíjat a városból. Nem fogják elfelejteni, ha-ha!\n Most pedig menjetek pihenni. És gyertek el hozzám és a többi kapitányhoz a tavernába ma este! Igyunk az ügyünkre! Megparancsolom a csaposnak, hogy kergesse ki az összes helyi alkoholistát, így csak mi hatan és néhány bájos lány leszünk a kocsmában. Ma este a bajtársaiddal iszogatsz, holnap reggel pedig te vezeted a századot, te egyengeted az utat. És igyekezz minél hamarabb Cartagenába vinni minket. Minden tiszta?";
			link.l1 = "Igenis, fônök!";
			link.l1.go = "mtraxx_96";
		break;
		
		case "mtraxx_96":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			chrDisableReloadToLocation = true;
			CloseQuestHeader("Roger_8");
			pchar.questTemp.Mtraxx = "cartahena";
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, "LaVega_townhall", "goto", "goto3");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaReloadInTavern", 10.0);
			pchar.worldmapencountersoff = "1"; // уберем враждебные энкаунтеры
		break;
		// belamour legendary edition -->
		case "mtraxx_94a":
            dialog.text = "Te... te... Ôrült herceg! Fel akarsz ültetni?! Tudod mit, a pokolba veled! Megvolt az esélyed, hogy belépj a Testvériségbe, megvolt az esélyed, hogy kiszabadulj ennek a sok haszontalan marhának a soraiból. És te gyáván elszalasztottad ezt a lehetôséget. Tûnj el a nyafogásoddal! Gyenge! Még egyszer meglátod - elengedem a kutyákat!";
			link.l1 = "...";
			link.l1.go = "mtraxx_95a";
		break;
		
		case "mtraxx_95a":
            DialogExit();
			QuestSetCurrentNode("Terrax", "First time");
			CloseQuestHeader("Roger_8");
			DeleteAttribute(pchar, "questTemp.Mtraxx.Corrida");
			DeleteAttribute(pchar, "questTemp.Mtraxx.InTavern");
			LocatorReloadEnterDisable("LaVega_town", "reload6", true); // закрыть на месяц
			SetFunctionTimerCondition("Mtraxx_CartahenaLateOpen", 0, 0, 30, false);
			Mtraxx_TerraxReset(8);
			DoQuestReloadToLocation("LaVega_town", "reload", "reload6", ""); // выставим за дверь
		break;
		// <-- legendary edition
		case "mtraxx_97":
            dialog.text = "Prince, végre! Nézzétek, srácok - készítettünk neki ajándékot, és ô ki tudja, hol bolyong! Üljetek le, kezdjük!\nSzóval, bátor korzók! Cartagena aranya vár ránk, ha-ha! És meg fogjuk szerezni, a mennydörgésre esküszöm! De aki jól dolgozik, annak pihennie is kell! Éppen ezért ma csodásan fogjuk magunkat érezni ebben a remek létesítményben. Öntsön magának egy kis rumot, minél többet, annál jobb! Töltsétek tele a bögréteket! A kincsek szelére, a szerencse szelére! Fenékig iszunk!\nNektek a legfinomabb fôzetet a kocsmánk pincéibôl, és a sziget legszebb hölgyeit, ha-ha-ha!\nÉs neked, Charles, tôlünk - egy pompás kalapot. Próbáld fel, és ne vitatkozz!\nKorzók, énekeljétek a dalunkat! A kedvencünk!...";
			link.l1 = "";
			link.l1.go = "mtraxx_98";
		break;
		
		case "mtraxx_98":
            DialogExit();
			npchar.dialog.currentnode = "mtraxx_wait";
			LAi_SetSitType(npchar);
			GiveItem2Character(PChar, "hat8");
			EquipCharacterByItem(PChar, "hat8");
			DoQuestCheckDelay("Mtraxx_CartahenaTavernSong", 1.0);
		break;
		
		case "mtraxx_99":
            dialog.text = "Ideje megmutatni nekik, kik vagyunk mi, korzikaiak. Koboldok! Fogd az embereidet, és vedd át a város kapuját! Nem akarjuk, hogy erôsítést küldjenek az erôdbe! Üssétek ôket keményen a hátukba, amikor átrohanunk az erôd katonáin!";
			link.l1 = "";
			link.l1.go = "mtraxx_100";
		break;
		
		case "mtraxx_100":
            dialog.text = "Prince és Paul! Láttad a katonai századot három hajóval, szabadulj meg tôlük. Maradjatok távol az erôdtôl, és ne szálljatok fel a hajóikra. Sem idônk, sem pozíciónk nincs arra, hogy zsákmányokkal foglalkozzunk. Minden tiszta?! Herceg, kifejezetten hozzád beszélek, ismerem a hôsiesség iránti szenvedélyedet, erre késôbb lesz lehetôséged!\nNe menj túl közel az erôdhöz, szabadulj meg ezektôl a hajóktól, és gyere vissza! Itt várunk majd rád. Minden világos? Nagyszerû, ha-ha-ha-ha-ha! Támadás!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaSquadronAttack");
		break;
		
		case "mtraxx_101":
            dialog.text = "A spanyol század tehát végleg eltûnt. Most itt az ideje, hogy a 'Vörös Sárkány' is kivegye a részét. Cartagena erôdjét romhalmazzá változtatjuk. Velem vagytok?";
			link.l1 = "Persze!";
			link.l1.go = "mtraxx_102";
		break;
		
		case "mtraxx_102":
            dialog.text = "A 'Vörös Sárkány' egy nagyon erôs hajó, erôs tüzérséggel, a tiéd nem ér fel vele. Szóval vigyázz, ne játssz hôsködj, és maradj távol az ágyúimtól!";
			link.l1 = "...";
			link.l1.go = "mtraxx_103";
		break;
		
		case "mtraxx_103":
            DialogExit();
			
			Weather.Wind.Speed = 16.0;
			pchar.wind.speed = Weather.Wind.Speed;
			fWeatherSpeed = stf(Weather.Wind.Speed);//халява первого выхода
	
			Weather.Wind.Angle = 0.0;
			pchar.wind.angle = Weather.Wind.Angle;
			fWeatherAngle = stf(Weather.Wind.Angle);//халява первого выхода
			
            npchar.dialog.currentnode = "mtraxx_board_6x";
			npchar.DeckDialogNode = "mtraxx_board_6x";
			npchar.DontDeskTalk = true;
			Group_FindOrCreateGroup("Terrax_SeaGroup2");
			Group_DelCharacter("Terrax_SeaGroup", "Jeffry");
			Group_DelCharacter("Terrax_SeaGroup", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Jeffry");
			Group_AddCharacter("Terrax_SeaGroup2", "Mtr_Vensan");
			Group_AddCharacter("Terrax_SeaGroup2", "Pelly");
			Group_SetGroupCommander("Terrax_SeaGroup2", "Jeffry");
			Group_SetTaskNone("Terrax_SeaGroup2");
			Group_LockTask("Terrax_SeaGroup2");
			sld = CharacterFromID("Cartahena Fort Commander");
			LAi_SetImmortal(sld, false);
			Ship_SetTaskAttack(SECONDARY_TASK, sti(npchar.index), sti(sld.index));
			AddQuestRecord("Roger_9", "5");
			DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
			pchar.questTemp.Mtraxx.Cartahena.Fort = "true";
			SetFunctionExitFromLocationCondition("Mtrxtofort", pchar.location, false);
		break;
		
		case "mtraxx_104":
            dialog.text = RandSwear()+"Pokoli harc! Ez az, bátor korzírjaim! Cartagena a miénk! Az ellenállásnak vége! Bátor, kobold! Gyertek velem az erôdbe - Bernie már biztosan megtalálta az aranyat. Herceg, fogd a Bicskát, és tárgyalj a kormányzóval, hogy fizessen nekünk 250.000 pezó váltságdíjat! Megvan a pénz, úgyhogy legyetek kitartóak. Tudom, hogy képes vagy rá.";
			link.l1 = "Heh! Örömmel, fônök!";
			link.l1.go = "mtraxx_105";
		break;
		
		case "mtraxx_105":
            DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "Cartahena_fort", "goto", "goto10", "", 5.0);
			sld = CharacterFromID("Jeffry");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto11", "", 5.0);
			sld = CharacterFromID("Lepricon");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "gate_back", "Cartahena_fort", "goto", "goto12", "", 5.0);
			sld = CharacterFromID("Pelly");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
			AddQuestRecord("Roger_9", "6");
			// запрещаем драки в городе, резиденции, форте
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_fort")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_town")], true);
			LAi_LocationFightDisable(&Locations[FindLocation("Cartahena_townhall")], true);
			LAi_LocationDisableOfficersGen("Cartahena_townhall", true);
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1 = "locator";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.location = "Cartahena_town";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator_group = "reload";
			pchar.quest.mtraxx_cartahena_townhall.win_condition.l1.locator = "reload3_back";
			pchar.quest.mtraxx_cartahena_townhall.function = "Mtraxx_CartahenaToResidence";
		break;
		
		case "mtraxx_106":
            dialog.text = "Hogy vagy, herceg?";
			link.l1 = "Minden nagyszerû. Kényszerítettem Cartagena leggazdagabbjait, hogy fizessenek 350.000 pezót.";
			link.l1.go = "mtraxx_107";
		break;
		
		case "mtraxx_107":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "Ho-ho, ez az én fiam! De hol van a pénz?";
				link.l1 = RandSwear()+"Mindjárt hozom!";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "Ho-ho, ez az én fiam! Te és a Cutlass megtarthattok fejenként 50.000-et a gyorsaságért és a találékonyságért. A többit késôbb elosztjuk egymás között.";
				link.l1 = "Tessék!";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_107x":
           DialogExit();
		   npchar.dialog.currentnode = "mtraxx_108";
		break;
		
		case "mtraxx_108":
            if (sti(Pchar.money) < 350000)
			{
				dialog.text = "Szóval? Hagyd abba a játszadozást és hozd ide az érméket!";
				link.l1 = "Máris megyek!";
				link.l1.go = "mtraxx_107x";
			}
			else
			{
				dialog.text = "Nagyszerû! Te és a Vágóhíd megtarthatjátok fejenként 50.000-et a gyorsaság és a találékonyság bónuszaként. A többit késôbb mindannyiunk között felosztjuk.";
				link.l1 = "Tessék!";
				link.l1.go = "mtraxx_109";
			}
		break;
		
		case "mtraxx_109":
			AddMoneyToCharacter(pchar, -300000);
            dialog.text = "Biztos aggódsz az aranyunk miatt. Megtaláltuk - 5.000 egység, és már szállítják is a hajóinkra. A felosztás már megtörtént, az emberek beleegyeztek, reméljük, hogy Cutlass és te sem fogsz ellenkezni.";
			link.l1 = "Mennyi az én részem?";
			link.l1.go = "mtraxx_110";
		break;
		
		case "mtraxx_110":
            dialog.text = "Mivel az egész akciót én terveztem ki, ráadásul a 'Vörös Sárkány' a legnehezebb munkát végezte az erôddel, én és az embereim kapjuk a zsákmány felét. A másik felét a másik négy hajó kapitányai között osztjuk el a legénységük létszáma szerint. Neked "+GetCrewQuantity(pchar)+" embered áll rendelkezésedre, a te részed "+sti(pchar.questTemp.Mtraxx.Cartahena.Gold)+" egységnyi arany és "+sti(pchar.questTemp.Mtraxx.Cartahena.Money)+" pezó.";
			link.l1 = "Nos, mivel mindenkinek megfelel, akkor nekem is!";
			link.l1.go = "mtraxx_111";
		break;
		
		case "mtraxx_111":
            dialog.text = "Pompás. Gratulálunk ehhez a sikeres úthoz, kalózok! Itt már semmi sem maradt számunkra, ideje hazamenni. Mindannyian, beleértve engem is, egy hónap szabadságot kapunk. De te nem, herceg, van egy másik feladatom számodra. Tudod, Janette, a Tortuga bordélyház egyik madame-ja panaszkodott rád: azt mondta, hogy Charlie herceg nem sok figyelmet és szeretetet fordít a létesítményére. Ezért megparancsolom neked, hogy hajózz el Tortugára, menj el Janette-hez, és pazarold ott a bónuszokat. Megérdemeltétek. Tegyétek boldoggá a Madame-ot és a lányait. Nem akarlak látni, mielôtt Tortugán kipihened magad, ha-ha-ha-ha!";
			link.l1 = "Értettem, fônök. Ez a legkellemesebb megbízás, amit valaha kaptam. Meglesz!";
			link.l1.go = "mtraxx_112";
		break;
		
		case "mtraxx_112":
            dialog.text = "Viszlát, uraim! Szálljanak fel a hajóikra és vitorlát bontani! Találkozunk La Vegában!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Mtraxx_CartahenaFinal");
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "mtraxx_113":
            dialog.text = "Micsoda?! Jean most az angolok szukája, Bold és Cutlass eltûntek, Leprechaun és az emberei sehol sincsenek! És most te?!";
			link.l1 = "Marcus, meghoztam a döntésemet. Jó pénzt kerestem, te is egy egész vagyont kerestél rajtam. De én végeztem. Elmegyek.";
			link.l1.go = "mtraxx_114";
		break;
		
		case "mtraxx_114":
            dialog.text = "Te is, akárcsak Picard, azt hiszed, hogy egyedül is jobban kereshetsz? Igen, uram? Azt hiszed, hogy nélkülem is boldogulsz? Ha-ha-ha-ha! Takarodj innen a pokolba, herceg, nem tartalak itt. Hamarosan, nagyon hamar rá fogsz jönni, hogy mekkorát tévedtél, és akkor majd visszajössz könyörögni, hogy vegyem vissza a szánalmas segged. És tudod mit? Nem fogom! Ha-ha! Tûnj a szemem elôl!";
			link.l1 = "...";
			link.l1.go = "mtraxx_115";
		break;
		
		case "mtraxx_115":
            DialogExit();
		    npchar.quest.mtraxx_complete = "true";
		break;
		
		// Jason НСО
		case "patria":
			dialog.text = "Ho-ho! Jó helyre jöttél! Köpd ki!";
			link.l1 = "Van egy fickó, aki nem fél a kalózoktól. Nem veszi ôket komolyan. Megtanítanák neki a tisztelet leckéjét. Ne feledd, ne öld meg.";
			link.l1.go = "patria_1";
		break;
		
		case "patria_1":
			dialog.text = "Huh! Ez nem más, mint az öreg Charles! Lefogadom, hogy megint valami viszonyba keveredtél! Térjünk rá a részletekre, ki a célpont ezúttal és mire tanítsuk meg?";
			link.l1 = "Egy vendég Európából, a francia pénzügyminisztérium egyik ellenôre - Noel Forget báró. Francia kereskedelmi társaságot akar itt alapítani, de én és egy közeli barátom ellene tiltakozunk. Próbáltuk meggyôzni a bárót, hogy az itteni kereskedelem nagyon kockázatos lenne a hollandok, az angolok és fôleg a kalózok miatt, miután Levasseurt legyôzték, de nem hallgatott ránk. Félelmet kell belé vernünk, hogy a saját bôrén érezze.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_x":
			dialog.text = "Ho-ho! Jó helyre jöttél! Köpd ki!";
			link.l1 = "Van egy fickó, aki nem fél a kalózoktól. Nem veszi ôket komolyan. Megtanítanák neki a tisztelet leckéjét. Ne feledd, ne öld meg.";
			link.l1.go = "patria_x1";
		break;
		
		case "patria_x1":
			dialog.text = "Huh! Miért döntöttetek úgy, hogy hirtelen kalózokat hámoztok be? Rendben, nem érdekel, amíg fizetsz nekem. Térjünk rá a részletekre, ki a célpont ezúttal, és mit kell megtanítanunk neki...";
			link.l1 = "Egy vendég Európából, a francia pénzügyminisztérium egyik ellenôre - Noel Forget báró. Francia kereskedelmi társaságot akar itt alapítani, de én és egy közeli barátom ellene tiltakozunk. Próbáltuk meggyôzni a bárót, hogy az itteni kereskedelem nagyon kockázatos lenne a hollandok, az angolok és fôleg a kalózok miatt, miután Levasseurt legyôzték, de nem hallgatott ránk. Félelmet kell belé vernünk, hogy a saját bôrén érezze.";
			link.l1.go = "patria_2";
		break;
		
		case "patria_2":
			dialog.text = "Igen-igen... Egy igazi báró! Meg kellene támadnunk a hajóját?";
			link.l1 = "A terv a következô: a hajója hamarosan elindul Kikötô-au-Prince-bôl Capsterville-be. Saint Kitts közelében kell elfogni a bárót, és túszul ejteni. Jobb lenne, ha nem süllyesztenéd el a hajót, és elkerülnéd az emberölést. A franciák végül is a barátaink. Képes leszel ezt megoldani?";
			link.l1.go = "patria_3";
		break;
		
		case "patria_3":
			dialog.text = "Nos, nem ígérhetek semmit. De megpróbálom. Milyen hajóról van szó?";
			link.l1 = "A brigg neve 'Favory'.";
			link.l1.go = "patria_4";
		break;
		
		case "patria_4":
			dialog.text = "Egy brigg nem ellenfél az én 'Vörös sárkányomnak'. Könnyen elbánunk velük. Ha megadják magukat, mindenkit életben hagyok.";
			link.l1 = "Tökéletes. Félelmet kelteni és felajánlani nekik, hogy megadják magukat. Utána küldd a bárót a patkányoktól hemzsegô raktérbe. Próbáljatok meg a lehetô legmocskosabb helyet keresni, de egy napnál tovább ne tartsátok ott, különben megbetegedhet és meghalhat. Ezután szállásold el a kabinban, találj neki valami félreesô helyet, és zárd be. Öltöztesd néhány emberedet foglyul ejtett francia kereskedônek, és viselkedj úgy, mintha azok lennének. Három napon keresztül egyfolytában meséljenek neki mindent arról, hogyan üldözik ôket a kegyetlen kalózok, hogyan rabolják ki ôket, hogyan követelnek váltságdíjat, hogyan kínozzák ôket... minden szükséges részletre kiterjedôen.";
			link.l1.go = "patria_5";
		break;
		
		case "patria_5":
			dialog.text = "Ha-ha-ha-ha! Ez lehet a legviccesebb munka, amit nagyon régóta elvállaltam! Hát akkor majd találok ilyen színészeket, fiam. Ne legyenek kétségeid, a történeteik után a báród be fog szarni a nadrágjába! Megmutatják majd neki a késhegyek és a felhevített kosok okozta sebhelyeket...";
			link.l1 = "Tökéletes! Aztán kényszeríteni fogod, hogy írjon egy levelet de Poincy-nak, váltságdíjat kérve. Harmincötszázezer egy ilyen nagyágyúért nem is olyan sok.";
			link.l1.go = "patria_6";
		break;
		
		case "patria_6":
			dialog.text = "Jó, rendben. Mi lesz a következô lépés?";
			link.l1 = "Aztán elviszed a bárót a törökökhöz. Ott felveszed a váltságdíjat, és átadod nekem a bárót. És ráadásul azt is meg kell mondanod neki, hogy Tortugáért és Levasseurért minden francia felelni fog, és nem csak egyszer.";
			if (CheckAttribute(pchar, "questTemp.Patria.Pirate.Terrax")) link.l1.go = "patria_x7";
			else link.l1.go = "patria_7";
		break;
		
		case "patria_7":
			dialog.text = "Ha-ha-ha-ha! Ez aztán a pokoli trükk! Mi személyesen, nos, tudod, mit tettünk Levasseurrel, és most... ha-ha-ha-ha!... Jól van, fiam. Meglesz! Szóval azt mondod, hogy a hajó hamarosan megérkezik?";
			link.l1 = "Hamarosan. Figyelnünk kell.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_x7":
			dialog.text = "Ha-ha-ha-ha! Ez aztán a pokoli trükk! Mennyit kérjek ezért a bohózatért? Rendben, százezerrel megpecsételjük az üzletet. Add ide a pénzt.";
			if (sti(pchar.money) >= 100000) 
			{
				link.l1 = "Vegye el.";
				link.l1.go = "patria_x8";
			}
			else
			{
				link.l1 = "Rendben, hozom.";
				link.l1.go = "patria_xwait";
			}
		break;
		
		case "patria_xwait":
			DialogExit();
			pchar.questTemp.Patria.Condotier.NeedMoney = "true";
		break;
		
		case "patria_x8":
			AddMoneyToCharacter(pchar, -100000);
			dialog.text = "Tökéletes! Azt mondod, hogy a hajó hamarosan megérkezik?";
			link.l1 = "Hamarosan. Figyelnünk kell.";
			link.l1.go = "patria_8";
		break;
		
		case "patria_8":
			dialog.text = "Ne aggódj emiatt, nem hagylak cserben. Személyesen fogom ezt elintézni. Ha hallod a pletykát, hogy a bárót elfogták, gyere hozzám.";
			link.l1 = "A Favory nevû hajó. Köszönöm, Marcus.";
			link.l1.go = "patria_9";
		break;
		
		case "patria_9":
			DialogExit();
			AddQuestRecord("Patria", "71");
			pchar.questTemp.Patria = "epizode_12_wait";
			pchar.questTemp.Patria.Condotier.Success = "true";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
			else LocatorReloadEnterDisable("Lavega_town", "reload6", true);
		break;
		
		case "patria_10":
			dialog.text = "Természetesen, fiam. Ahogy megbeszéltük. Ijesztô történetek gonosz kalózokról, ártatlan francia kereskedôk lemészárlásáról, ostorcsattogás, nyögések és sikolyok. Szénnel teli üst és perzselôdô bilincsek. Pontosan úgy, ahogy lennie kell.";
			link.l1 = "Hé, hé, hé! Álljatok meg! Élve kell nekem.";
			link.l1.go = "patria_11";
		break;
		
		case "patria_11":
			dialog.text = "Ne aggódj, életben marad. Ezt a levelet remegô kézzel írta. Itt is van.";
			link.l1 = "Mi van odaírva? Könyörög Poincy-nak, hogy mentse ki ôt ebbôl?";
			link.l1.go = "patria_12";
		break;
		
		case "patria_12":
			dialog.text = "Így van, fiam! Könyörög, ha!";
			link.l1 = "Dobd el ezt a levelet, vagy jobb, ha elégeted. Egy hét múlva találkozunk a törököknél. Úgy kell tûnnie, hogy idôre van szükségünk, hogy begyûjtsük a váltságdíjat.";
			link.l1.go = "patria_13";
		break;
		
		case "patria_13":
			dialog.text = "Megvan. Egy hét múlva, az északi öbölben, Törökországban. Ne felejtsd el a pénzt: ez jól fog kinézni. Mindezek után gyere el hozzám, és megbeszéljük.";
			link.l1 = "Persze, viszlát késôbb, Marcus!";
			link.l1.go = "patria_14";
		break;
		
		case "patria_14":
			DialogExit();
			AddQuestRecord("Patria", "73");
			pchar.questTemp.Patria = "epizode_12_terks";
			SetFunctionTimerCondition("Patria_CondotierTerks", 0, 0, 7, false);
			SetFunctionTimerCondition("Patria_CondotierTerksOver", 0, 0, 14, false);
			if(bImCasual) NewGameTip("Felfedezô mód: az idôzítô nincs kikapcsolva. Tartsd be a határidôt!");
		break;
		
		case "patria_15":
			pchar.quest.Patria_CondotierTerksOver.over = "yes"; //снять таймер
			dialog.text = "Hé, frogeater! Állj!";
			link.l1 = "Nem mozdulok.";
			link.l1.go = "patria_16";
		break;
		
		case "patria_16":
			dialog.text = "Itt van a báró. Kicsit megviselt, de egy darabban van. Felismerhetô még? Ha-ha-ha-ha!";
			link.l1 = "Igen... valamennyire.";
			link.l1.go = "patria_17";
		break;
		
		case "patria_17":
			dialog.text = "Tökéletes. Most pedig adja át a pénzt, vagy végeztünk! És ne próbálj meg átverni minket, a célkeresztünkben vagy!";
			if (sti(pchar.money) >= 350000)
			{
				link.l1 = "Tessék, vedd el.";
				link.l1.go = "patria_18";
			}
			else
			{
				link.l1 = "A francba! A hajón felejtettem...";
				link.l1.go = "patria_22";
			}
		break;
		
		case "patria_18":
			AddMoneyToCharacter(pchar, -350000);
			dialog.text = "Ha-ha-ha! Okos kölyök vagy, francia. Fogd a 'eminenciádat'. És mondd meg Poincy-nak, hogy készítse elô a pénzt: meg kell fizetned azért, amit Levasseurrel és Tortugával tettél. A ti alkudozóitok pedig az áruikkal és a hajóikkal fognak fizetni nekünk. Ha-ha-ha-ha! Ne felejtsetek el még néhány bárót hozni a szigetvilágba, sok hasznot hoznak nekünk! Ha-ha-ha!";
			link.l1 = "Kérlek, menj a hajómra, báró!";
			link.l1.go = "patria_19";
		break;
		
		case "patria_19":
			sld = CharacterFromID("Noel");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
			dialog.text = "És eszedbe se jusson üldözni minket, kapitány. Tudod, hogy ki vagyok. Több frogeatert tartok fogva, és ha nem térek haza idôben, mindannyiukat kivégzik. Megértetted?";
			link.l1 = "Eljön majd az idô, és elintézünk titeket, átkozott istenkáromlók!";
			link.l1.go = "patria_20";
		break;
		
		case "patria_20":
			dialog.text = "Ha-ha-ha-ha-ha-ha! Hát persze, hogy így lesz!";
			link.l1 = "...";
			link.l1.go = "patria_21";
		break;
		
		case "patria_21":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Patria", "74");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax"))
			{
				LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
				Island_SetReloadEnableGlobal("Bermudes", false); // закрыть остров до отвоза барона
			}
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_baronalive";
			pchar.questTemp.Patria.DodsonAgain = "true";
			sld = CharacterFromID("Noel");
			AddPassenger(pchar, sld, false);//добавить пассажира
			SetCharacterRemovable(sld, false);
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1 = "location";
			pchar.quest.Patria_Condotier_toPuancie.win_condition.l1.location = "Charles_town";
			pchar.quest.Patria_Condotier_toPuancie.function = "Patria_CondotierEnCapstervil";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_22":
			dialog.text = "Viccelsz velem?! Ez valami trükk?!";
			link.l1 = "Egy perc, hozom...";
			link.l1.go = "patria_23";
		break;
		
		case "patria_23":
			DialogExit();
			LAi_SetPlayerType(pchar);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorAnimation(sld, "Shot", "Patria_CondotierBaronDie", 1.0);
		break;
		
		case "patria_24":
			dialog.text = "";
			link.l1 = "Argh, Marcus, mit csinált a te tökfilkód!";
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) link.l1.go = "patria_25";
			else link.l1.go = "patria_x25";
		break;
		
		case "patria_25":
			dialog.text = "Charles, mit csináltál? Hol van a pénz? Nem mondtam a fiaimnak, hogy ez nem igazi... és így ez az idióta úgy döntött, hogy át akarsz verni minket...";
			link.l1 = "Ez egy katasztrófa! A báró meghalt... Mit fog most tenni de Poincy?";
			link.l1.go = "patria_26";
		break;
		
		case "patria_x25":
			dialog.text = "Charles, mit csináltál? Hol a pénz? Nem mondtam a fiaimnak, hogy ez nem igazi... és ez az idióta úgy döntött, hogy át akarod verni ôket...";
			link.l1 = "Ez egy katasztrófa! A báró meghalt... Mit fog most tenni de Poincy?";
			link.l1.go = "patria_x26";
		break;
		
		case "patria_x26":
			dialog.text = "Nos, fiam, ez a te hibád, remélem megérted. Talán így a legjobb, egy halott ember nem tud kárt okozni.";
			link.l1 = "Micsoda idióta vagyok! Mindent elrontottam. Rendben, elmegyek Poincyhoz... Bocsáss meg, hogy bolond voltam, Marcus, viszlát.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_26":
			dialog.text = "Nos, fiam, ez a te hibád, remélem megérted. Talán így a legjobb.";
			link.l1 = "Micsoda idióta vagyok! Mindent elrontottam. Rendben, elmegyek Poincyhoz... Bocsáss meg, hogy bolond voltam, Marcus, viszlát.";
			link.l1.go = "patria_27";
		break;
		
		case "patria_27":
			dialog.text = "Pihenésre van szükséged, kezdesz elveszteni a fejedben. Gyere el hozzám néha, szerzek neked rumot és finom lányokat.";
			link.l1 = "Köszönöm, meglátogatlak, amikor csak tudlak.";
			link.l1.go = "patria_28";
		break;
		
		case "patria_28":
			DialogExit();
			AddQuestRecord("Patria", "75");
			LAi_SetActorType(npchar);
			if (CheckAttribute(pchar, "questTemp.Patria.Saga.Terrax")) LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
			else LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierTerraxNorm", 10.0);
			sld = CharacterFromID("Terks_pirat");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
			pchar.questTemp.Patria = "epizode_12_barondie";
			// Теркс в норму
			LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
			LAi_LocationDisableOfficersGen("Shore56", false);
		break;
		
		case "patria_29":
			dialog.text = "Szívesen, fiam. Nekem ez volt a legszórakoztatóbb az idén! Annyit nevettünk, én és a fiúk! Szóval szeretném megköszönni ezt neked. Itt a pénzed.";
			link.l1 = "Tartsd meg egy részét az elôadásodért.";
			link.l1.go = "patria_30";
		break;
		
		case "patria_x29":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Fogd a pénzed, 'plotter'. Ha-ha! Ez jó móka volt.";
			link.l1 = "Köszönöm a segítségedet, Marcus. Sok szerencsét!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_30":
			AddMoneyToCharacter(pchar, 350000);
			dialog.text = "Felejtsd el. A barátságunk érdekében tettem. A Parti Testvérek sokkal többel tartoznak neked, pedig egyetlen dublont sem kértél.";
			link.l1 = "Mégis, legalább ötvenezret vegyél el a szolgáltatásokért és a kártérítésért. Köszönöm, Marcus!";
			link.l1.go = "patria_31";
		break;
		
		case "patria_31":
			AddMoneyToCharacter(pchar, -50000);
			dialog.text = "Szívesen. Charles, látogass meg, amikor csak idôd engedi!";
			link.l1 = "Örömmel!";
			link.l1.go = "patria_32";
		break;
		
		case "patria_32":
			DialogExit();
			DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;
		
		case "patria_33":
			dialog.text = "Egy hetet késtél! Nem mondtam a fiúknak, hogy ez nem igazi... Nem akartak tovább várni, és úgy döntöttek, hogy véget vetnek a bárónak!";
			link.l1 = "Micsoda idióta vagyok! Mindent elrontottam! Mit fogok mondani Poincy-nak?";
			link.l1.go = "patria_34";
		break;
		
		case "patria_x33":
			dialog.text = "Egy hetet késtél! Nem mondtam a fiúknak, hogy ez nem igazi... Nem akartak tovább várni, és úgy döntöttek, hogy véget vetnek a bárónak!";
			link.l1 = "Micsoda idióta vagyok! Mindent elrontottam! Mit fogok mondani Poincy-nak?";
			link.l1.go = "patria_x34";
		break;
		
		case "patria_34":
			dialog.text = "Nos, fiam, ez a te hibád, remélem megérted. Talán még jobb is lesz neked.";
			link.l1 = "Rendben, elmegyek Poincyba... Bocsáss meg, hogy bolond voltam, Marcus, viszlát...";
			link.l1.go = "patria_35";
		break;
		
		case "patria_x34":
			dialog.text = "Te hoztad magad ebbe a szarba, a te hibád.";
			link.l1 = "Késôbb találkozunk, azt hiszem...";
			link.l1.go = "patria_36";
		break;
		
		case "patria_35":
			dialog.text = "Pihenésre van szükséged, kezdesz elveszteni a fejedben. Gyere el hozzám néha, szerzek neked rumot és finom lányokat.";
			link.l1 = "Köszönöm, majd meglátogatlak, ha tudlak.";
			link.l1.go = "patria_36";
		break;
		
		case "patria_36":
			DialogExit();
			AddQuestRecord("Patria", "75");
			pchar.questTemp.Patria = "epizode_12_barondie";
			DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
		break;
		
		// Rebbebion, квест "Путеводная звезда"
		case "PZ_1":
			DelLandQuestMark(npchar);
			
			if (pchar.questTemp.Mtraxx == "full_complete")
			{
				dialog.text = "Rég láttalak, herceg.";
				link.l1 = "Nem vagyok benne biztos, hogy ez a név csak balszerencsét hozott nekem, Marcus.";
				link.l1.go = "PZ_Prince1";
			}
			else
			{
				dialog.text = "De Maure! Mi szél hozta ide?";
				link.l1 = "Ahoy, Marcus. Kérdezni akartam valamit.";
				link.l1.go = "PZ_DeMaure1";
			}
		break;
		
		case "PZ_Prince1":
			dialog.text = "Látom, hogy az ellenkezôjét. Mi szél hozta ide?";
			link.l1 = "Hallottál az új bordélyházról Tortugában?";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_DeMaure1":
			dialog.text = "Akkor mindenképpen kérdezd meg. Tudja, hogy nem szeretem a formaságokat, úgyhogy térjen a lényegre.";
			link.l1 = "Hallottál az új bordélyházról Tortugában?";
			link.l1.go = "PZ_2";
		break;
		
		case "PZ_2":
			dialog.text = "Részeg vagy? Miféle kérdés ez? Ne vesztegesd az idômet, ha tényleg errôl akartál beszélni.";
			link.l1 = "Gondolom, nem hallottad? Nemrég nyílt ott egy új bordélyház - egy nagyon drága, ahol csak a legszebb, legegészségesebb és legjobban öltözött lányok dolgoznak.";
			link.l1.go = "PZ_3";
		break;
		
		case "PZ_3":
			dialog.text = "Ó, az! Persze, hogy hallottam - ki ne hallotta volna?";
			link.l1 = "Nos, én csak a minap értesültem róla.";
			link.l1.go = "PZ_4";
		break;
		
		case "PZ_4":
			dialog.text = "Ha-ha-ha-ha-ha, te gazember, a fenébe is! De akkor is, miért beszélgetsz velem errôl? Miért nem próbálod ki elôször Hawksot? Hé, hé, hé. Habár... már volt ott egy kis szórakozásod?";
			if (CheckAttribute(pchar, "questTemp.PZ.EliteWhoreFucked"))
			{
				link.l1 = "Már volt. Egyébként csak dublont fogadnak el.";
				link.l1.go = "PZ_Fucked1";
			}
			else
			{
				link.l1 = "Meglátogattam a helyet, de nem vettem részt a szolgáltatásokban. Azonban...";
				link.l1.go = "PZ_NoFucked1";
			}
		break;
		
		case "PZ_Fucked1":
			dialog.text = "Szóval azért jöttél, hogy felvágj! Ha, micsoda gazember.";
			link.l1 = "Igazából nem. Tényleg kérdezni akartam valamit, Marcus.";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_NoFucked1":
			dialog.text = "Tényleg?! Maga egy idióta, De Maure. A maga helyében...";
			link.l1 = "Ha a helyedben lettem volna, akkor egy igazi züllésbe kezdtél volna, tudom. De én nem éppen ezt akartam megbeszélni veled.";
			link.l1.go = "PZ_5";
		break;
		
		case "PZ_5":
			dialog.text = "Akkor mirôl? Gyerünk, ne tartson bizonytalanságban.";
			link.l1 = "Annak a helynek a tulajdonosát keresem. Azt mondták, hogy találkozni akar önnel, és befektetési lehetôséget kínál a kereskedelmében. Nem tévesztheti össze - kínai.";
			link.l1.go = "PZ_6";
		break;
		
		case "PZ_6":
			dialog.text = "Ho ho ho. Nem, mostanában nem volt szerencsém kínai nôkkel találkozni. De nem bánnám, ha találkoznék vele, és befektetnék az üzletébe. Elvégre nem sétálhatsz csak úgy be Levasseur területére, és mint a királyod alattvalója, kénytelen lenne a parti hajóival tüzet nyitni rám 'Dragon' a pillanatban, amikor meglátja ôt.";
			link.l1 = "Úgy tûnik, elôször Kikötô-au-Prince-re gondol...";
			link.l1.go = "PZ_7";
		break;
		
		case "PZ_7":
			dialog.text = "Gondolod? Ez tévedés. Még ha de Mussac-nak több pénze is van, mint nekem, amit kétlek, nem engedheti meg magának, hogy a város költségvetésébôl egy bordélyházra fordítson, bármennyi aranyat is hozna.";
			link.l1 = "Jó érv. Nyilvánvalóan nem gondolta át ezt a törekvését.";
			link.l1.go = "PZ_8";
		break;
		
		case "PZ_8":
			dialog.text = "Tudod, mindig is kíváncsi voltam, hogy más bordélyházak hogyan maradnak talpon. Ez nem egy nô gondolkodási és fôleg uralkodási képessége - jegyezd meg, amit mondok.";
			link.l1 = "Nos, ebben tévedsz. Köszönöm az idejét, Marcus! Ha én találkozom vele elôször, megmondom neki, hogy örömmel látnád.";
			link.l1.go = "Exit";
			
			AddQuestRecord("PZ", "32");
			
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1 = "location";
			pchar.quest.PZ_SetHeavyFrigate.win_condition.l1.location = "Hispaniola1";
			pchar.quest.PZ_SetHeavyFrigate.win_condition = "PZ_SetHeavyFrigate";
			DelMapQuestMarkCity("LaVega");
			AddMapQuestMarkCity("PortPax", false);
			LocatorReloadEnterDisable("LaVega_ExitTown", "reload1_back", true);
			LocatorReloadEnterDisable("PortPax_town", "gate_back", true);
		break;
	}
}