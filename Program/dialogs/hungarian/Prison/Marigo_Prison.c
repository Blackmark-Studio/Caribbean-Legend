// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
 	switch(Dialog.CurrentNode)
	{
        case "quests":
            dialog.text = "Beszélj, hallgatlak.";
			link.l1 = "Tévedtem. Viszontlátásra.";
			link.l1.go = "Exit";
			//искушение барбазона
			if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison"))
            { 
                link.l1 = "Simon Morelle-t letartóztatták. Ô egy csempész, akinek a szkúnáját nemrég elsüllyesztette egy járôr. Beszélhetek vele?";
                link.l1.go = "BarbTemptation";
				DeleteAttribute(pchar, "questTemp.Saga.BarbTemptation.Prison");
            }
			// Addon-2016 Jason ФМК-Сент-Кристофер
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div")
			{
				link.l1 = "Biztos úr, engem Philipsburg kormányzója küldött ide. Megkért, hogy kutassam át a szigetet és a vizeit angol kémek után. Az ô excellenciája azt is mondta, hogy ön hasznos információkkal szolgálhat nekem.";
				link.l1.go = "FMQN";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "way_div_2")
			{
				link.l1 = "Tiszt úr, megtaláltam az eltûnt ôrjáratot. Megtaláltam az angol kémeket is. Itt vannak a szigeten.";
				link.l1.go = "FMQN_3";
			}
			if (CheckAttribute(PChar, "questTemp.FMQN") && pchar.questTemp.FMQN == "hol_peace_rew")
			{
				link.l1 = "Megint én, tiszt úr. Feltartóztatta a kémeket?";
				link.l1.go = "FMQN_8";
			}
		break;
		
		//искушение барбазона
		case "BarbTemptation":
			dialog.text = "És miért van szüksége rá, uram?";
			link.l1 = "Meg akarom mondani neki, hogy egy rohadt szemétláda és gazember. Remélem, hogy ez segíteni fog neki a bitófán.";
			link.l1.go = "BarbTemptation_1";
		break;
		
		case "BarbTemptation_1":
			dialog.text = "Ha-ha! Van humora, uram... Nos, kétezer pezó, és már mehet is tovább.";
			if(sti(Pchar.money) >= 2000)
			{
				link.l1 = "Fogja, biztos úr. Köszönöm, uram.";
				link.l1.go = "BarbTemptation_2";
			}
			link.l2 = "Hm... Tudja, hogy meggondoltam magam. Inkább a kocsmában pazarlom a pénzem.";
			link.l2.go = "BarbTemptation_4";
		break;
		
		case "BarbTemptation_2":
			AddMoneyToCharacter(pchar, -2000);
			dialog.text = "Szívesen... Menjetek tovább!";
			link.l1 = "...";
			link.l1.go = "exit";
			pchar.questTemp.jailCanMove = true;
		break;
		
		case "BarbTemptation_4":
			dialog.text = "Ahogy kívánod, legközelebb nem kapsz ilyen ajánlatot.";
			link.l1 = "Nekem amúgy sincs rá szükségem. Viszlát, biztos úr!";
			link.l1.go = "exit";
		break;
		
		// Addon-2016 Jason ФМК-Сент-Кристофер
		case "FMQN":
			DelLandQuestMark(npchar);
			dialog.text = "Hasznos? Ha! Ha jobban belegondolok, várjon. Valami hasznosat akarok mondani neked. Az egyik ôrjáratunk eltûnt a dzsungelben. Már vissza kellett volna térniük a barakkjukba, de úgy tûnik, hogy inkább egy csapat papagájt választottak. Vagy tényleg történt valami. Ha megtaláljátok ôket a keresésük során, kérlek, mondjátok meg nekik, hogy találjanak ki valami tisztességes indoklást a késésükre, különben nem fogják szeretni a következményeket... Az ôrjárat parancsnokát Jannes Hoffmannak hívják.";
			link.l1 = "Ez minden, biztos úr?";
			link.l1.go = "FMQN_1";
		break;
		
		case "FMQN_1":
			dialog.text = "Igen, a fenébe is. Sajnálom, de nincs más mondanivalóm. Sok szerencsét, kapitány.";
			link.l1 = "Köszönöm...";
			link.l1.go = "FMQN_2";
		break;
		
		case "FMQN_2":
			DialogExit();
			pchar.questTemp.FMQN = "way_div_1";
			AddQuestRecord("FMQ_Nevis", "10");
			FMQN_SetSoldiersInCave();
		break;
		
		case "FMQN_3":
			DelLandQuestMark(npchar);
			dialog.text = "Micsoda?! Remélem, nem viccel? Adjon jelentést!";
			link.l1 = "Találkoztam egy ôrjárattal egy barlang közelében a dzsungelben. Megállítottak, megkérdezték, hová tartok és miért, aztán elengedtek. A fenébe is, ha azok nem a holland egyenruhába öltözött britek voltak! Láttam valami furcsát is a dzsungelben, ami pontosan úgy nézett ki, mint egy csomó bokrokba rejtett meztelen férfi. Feltételezem, a brit portyázó csapat lefegyverezte az ôrjáratukat és elvették az egyenruhájukat.";
			link.l1.go = "FMQN_4";
		break;
		
		case "FMQN_4":
			dialog.text = "...";
			link.l1 = "Mint érted, nem kockáztattam, hogy egy kiképzett vöröskabátos osztag ellen harcoljak, ezért inkább egy jelentéssel siettem hozzád.";
			link.l1.go = "FMQN_5";
		break;
		
		case "FMQN_5":
			dialog.text = "Nos, nos... Egy barlangot mondott? Hányat számoltál meg közülük?";
			link.l1 = "Öt embert. És igen, azt hiszem, bementek abba a barlangba.";
			link.l1.go = "FMQN_6";
		break;
		
		case "FMQN_6":
			dialog.text = "Azonnal küldök egy osztagot a barlanghoz! Kapitány, ha a férfiak, akikkel találkozott, valóban a brit kémek, akkor megérdemelt jutalmat kapnak. Szabadon csatlakozhat az osztaghoz, ha segíteni akar a hatóságoknak a rohadékok letartóztatásában, és extra jutalmat kap, elvégre ezek a kormányzó parancsai. Szóval, te is jössz?";
			link.l1 = "Nem, tiszt úr, a kémek üldözése a maga dolga. Biztos, hogy jól felfegyverzett osztagot fog küldeni, ezek a söpredékek túl veszélyesek...";
			link.l1.go = "FMQN_7";
			link.l2 = "Azt hiszem, meg tudom csinálni. Az embereid gyorsabban megtalálják a kémeket a segítségemmel.";
			link.l2.go = "FMQN_10";
		break;
		
		case "FMQN_7":
			dialog.text = "Ön dönt, kapitány, figyelembe veszem a tanácsát. Jöjjön el hozzám holnap, hogy megtudja az akciónk eredményét.";
			link.l1 = "Holnap találkozunk.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandPeace");
		break;
		
		case "FMQN_8":
			DelLandQuestMark(npchar);
			dialog.text = "Az információi helyesek voltak, kapitány. Megtaláltuk azokat a rohadékokat a barlangban. Nem mutattak megadási szándékot, és harcba bocsátkoztak. Ennek eredményeképpen - mindannyiukat likvidáltuk. Megtaláltuk az eltûnt ôrjáratot is. Jól vannak és élnek, bár egy kicsit megverték ôket... Köszönöm, kapitány, Philipsburg minden jó polgára nevében. Az éberséged meg lesz jutalmazva, ahogy ígérted. Kérem, vegye el.";
			link.l1 = "Köszönöm!";
			link.l1.go = "FMQN_9";
		break;
		
		case "FMQN_9":
			AddMoneyToCharacter(pchar, 10000);
			dialog.text = "Ön mindig szívesen látott vendég Sint-Maartenben. Most pedig kérem, bocsásson meg, más dolgom van.";
			link.l1 = "Nekem is. Viszontlátásra.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("FMQN_HollandPeaceComplete");
		break;
		
		case "FMQN_10":
			dialog.text = "Rendben. Nagyra értékelem a segítségét. Menjetek a városkapuhoz, a büntetô osztag egy órán belül ott lesz összegyûjtve.";
			link.l1 = "Egy apró tanács: a legjobb katonáidat küldd erre a küldetésre. Azok a kémek veszélyesek.";
			link.l1.go = "FMQN_11";
		break;
		
		case "FMQN_11":
			dialog.text = "Ne aggódjatok. A legtapasztaltabb katonáinkat küldöm egy tiszt, Hans Shulte - Philipsburg kardforgató mestere - parancsnoksága alatt.";
			link.l1 = "Nagyszerû! Akkor ne vesztegessük az idôt.";
			link.l1.go = "exit";
			WaitDate("",0,0,0,1,5);
			AddDialogExitQuestFunction("FMQN_HollandBattle");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
