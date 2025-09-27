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
			if (pchar.questTemp.Slavetrader == "FindRatJamaica")
            {
                link.l1 = "Egy Francois Gontier nevû férfi megfordult a városában? Nagy szükségem van rá.";
                link.l1.go = "Jamaica_ratF_1";
            }
			// Addon 2016-1 Jason пиратская линейка
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_4")
            {
                link.l1 = "Figyelj, haver, van egy hajó Port Royalból, aki selymet vásárol a hajógyárának... nagyon különleges selymet, biztosan hallottál már róla. Azt mondják, hogy egy ilyen selyem eladója valahol ebben a településben lakik. Van valami ötleted, hogyan találhatnánk meg? Van egy üzleti ajánlatom a számára.";
                link.l1.go = "mtraxx";
			}
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_5" && (PCharDublonsTotal() >= 50))
            {
                link.l1 = "Ötven dublont hoztam magammal. Fogd ôket és kezdj el beszélgetni.";
                link.l1.go = "mtraxx_4_1";
			}
		break;

		case "Jamaica_ratF_1":
			dialog.text = "Nála van. Pár napra kibérelt egy szobát. Nem a legkellemesebb fickó, meg kell mondjam. Ráadásul megszállottan paranoiás volt, hogy keresik. Állandóan félt és körülnézett. Maga az az ember, akitôl annyira félt?";
			link.l1 = "Nem, nem én voltam. Tudja, a kalózoknak sok ellenségük van. Szóval, hol találom ôt? Úgy döntöttünk, hogy megegyezünk, de úgy tûnik, hogy a föld elnyelte ôt.";
			link.l1.go = "Jamaica_ratF_2";
		break;
		
		case "Jamaica_ratF_2":
			dialog.text = "Elindult a tengerre a saját hajóján. Nem tudom, hová. Errôl nem tájékoztatott.";
			link.l1 = "Ah, milyen kár! Hol fogom most keresni ôt?";
			link.l1.go = "Jamaica_ratF_3";
		break;
		
		case "Jamaica_ratF_3":
			dialog.text = "Nem tudom, pajtás. Megmondanám, ha tudnám.";
			link.l1 = "Rendben, értem. Megyek, megkérdezek pár embert...";
			link.l1.go = "exit";
			AddQuestRecord("Slavetrader", "21_4");
			pchar.questTemp.Slavetrader = "FindRatJamaica_H";
		break;
		
		// Addon 2016-1 Jason пиратская линейка
		case "mtraxx":
            dialog.text = "Huh, ha a mi kereskedônkre gyanakszol, aki a boltot tartja, meg tudom mondani, hogy nem ô az, ô nem kereskedik selyem vitorlavászonnal. Csempészek sem járnak ide, nincs rájuk szükség, ha nincs vámház. Különben is, a kereskedônkön kívül senki más nem kereskedik itt. Nézzen körül, mi nem vagyunk olyanok, ha-ha!";
			link.l1 = "De valaki selymet szállít Port Royalba - ez cáfolhatatlan. Van valami ötleted, hogy ki lehet a szállító?";
			link.l1.go = "mtraxx_1";
		break;
		
		case "mtraxx_1":
            dialog.text = "Talán csempészek Port Royalból? Vagy szélhámos kalózok? Biztos valami rejtett öbölben rakodják ki a zsákmányt... Ha! Van egy ötletem, haver. Van egy helybéli, aki mindent tud, ami ezeken a vizeken történik. Ha ô nem feltételez semmit, akkor nincsenek selyemkereskedôk.";
			link.l1 = "Pompás! Hogy hívják a fickót?";
			link.l1.go = "mtraxx_2";
		break;
		
		case "mtraxx_2":
            dialog.text = "Hm... Próbálom felidézni a nevét, de valamiért nem jön elô...";
			link.l1 = "Mit szólna 'néhány érméhez, hogy segítse a memóriáját?";
			link.l1.go = "mtraxx_3";
		break;
		
		case "mtraxx_3":
            dialog.text = "Azt hiszem, az segíthetne... Ötven aranydublon biztosan megvilágítja ezt a vén fejet.";
			if (PCharDublonsTotal() >= 50) // Rebbebion, учёт количества дублонов из рундука
			{
				link.l1 = "Értem. Tessék, fogd az érméket.";
				link.l1.go = "mtraxx_4_1";
			}
			else
			{
				link.l1 = "Értem, értem. Visszajövök...";
				link.l1.go = "mtraxx_4_2";
			}
		break;
		
		case "mtraxx_4_1":
			RemoveDublonsFromPCharTotal(50);
			PlaySound("interface\important_item.wav");
            dialog.text = "Husky Billy az az ember, akire szükséged van. Mintha örökké Jamaicán élne, minden kutyát ismer az utcán. Kalóz volt, és a britek seggében volt, amíg meg nem sebesült három évvel ezelôtt. Most leginkább halászik, cápákra vadászik és borostyánt gyûjt Jamaica öbleiben. Csak azért hagyja el a régi hosszú hajóját, hogy újabb rumot és kekszet vegyen\nJamaika környéki vizeken keressék ôt. Azt mondják, az északi oldalon hajózik, egészen a legkeletibb pontig. De egy hosszú hajót üldözni bolondság, jobb, ha a délnyugati sarok környékén leselkedik, azt mondják, hetente egyszer látták a Negril-fok közelében. A csónakját úgy hívják, hogy 'The Fly Fish'..";
			link.l1 = "Kösz, haver. Megérdemelted az aranyat.";
			link.l1.go = "mtraxx_5";
		break;
		
		case "mtraxx_5":
            dialog.text = "Sok szerencsét, haver! Remélem, megtalálod, amit keresel!";
			link.l1 = "...";
			link.l1.go = "mtraxx_6";
		break;
		
		case "mtraxx_4_2":
            DialogExit();
			AddQuestRecord("Roger_2", "6");
			pchar.questTemp.Mtraxx = "silk_5";
		break;
		
		case "mtraxx_6":
            DialogExit();
			AddQuestRecord("Roger_2", "7");
			pchar.questTemp.Mtraxx = "silk_6";
			/*pchar.quest.mtr_negril.win_condition.l1 = "Timer";
			pchar.quest.mtr_negril.win_condition.l1.date.hour  = 12+rand(12);
			pchar.quest.mtr_negril.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 2+rand(3));
			pchar.quest.mtr_negril.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 2+rand(3));
			pchar.quest.mtr_negril.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 2+rand(3));*/
			PChar.quest.mtr_negril.win_condition.l1 = "ExitFromLocation";
			PChar.quest.mtr_negril.win_condition.l1.location = PChar.location;
			pchar.quest.mtr_negril.function = "Mtraxx_CreateBilly";
			SetFunctionTimerCondition("Mtraxx_BillySeaTimeOver", 0, 0, 7, false);
			if(bImCasual) NewGameTip("Felfedezô mód: az idôzítô nincs kikapcsolva. Tartsd be a határidôt!");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
