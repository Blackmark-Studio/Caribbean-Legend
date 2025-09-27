// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;   
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Milyen kérdések, "+ GetSexPhrase("fiatalember","fiatal hölgy") +"?", "Mire van szükséged, "+ GetSexPhrase("jóképû","csinos") +"? Kérdezz csak!"), "Ismét kérdések", "Tee-hee, ha neked mindegy - kérdések...",
                          ""+ GetSexPhrase("Hm, miért nem választasz magadnak egy szépséget? Kezdek gyanút fogni veled kapcsolatban...","Hm, miért nem választasz magadnak egy szépséget? Attól tartok, itt nincsenek fiúk, te-hee...") +"", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("Meggondoltam magam, elnézést.", "Igazából, nem érdekes."), "Én... elnézést, egyelôre nincs kérdésem.",
                      "Igaza van, ez már a harmadik alkalom. Bocsásson meg.", "Talán legközelebb, asszonyom.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start")
			{
				DelLandQuestMark(npchar);
				link.l1 = "Figyelj, Aurora, szükségem van egy lányra az éjszakára. És haza akarom vinni magammal. Meg tudod ezt oldani?";
                link.l1.go = "Gigolo";
			}	
			//<-- Бремя гасконца */
		break;
		
		//--> Бремя гасконца
		case "Gigolo":
			dialog.text = "Természetesen, kedvesem. Találtál már egy megfelelô leányt, vagy nekem kellene?";
			link.l1 = "Valóban találtam. Egy Lucille nevû lányra vetettem szemet.";
			link.l1.go = "Gigolo_1";
		break;
		
		case "Gigolo_1":
			dialog.text = "Lucille Montaigne-re gondolsz?";
			link.l1 = "Az igazat megvallva, nem kérdeztem a vezetéknevét. Csak annyit tudok, hogy egy fiatal, szép és szôke hajú lány, akit Lucille-nak hívnak.";
			link.l1.go = "Gigolo_2";
		break;
		
		case "Gigolo_2":
			dialog.text = "Igen, ez nagyon jól jellemzi ôt. Rendben. De mondja, miért pont ô? A többi lány nem tetszik neked?";
			link.l1 = "Hát, tudja... még csak most kezdett itt dolgozni, úgyhogy úgy gondolom, még nem elég tapasztalt a 'Trade' ahhoz, hogy túlságosan megterhelje a pénztárcámat.";
			link.l1.go = "Gigolo_2_1";
			link.l2 = "Tudja, imádom a szôke, világos bôrû lányokat. Lucille ebbôl a szempontból tökéletes lesz.";
			link.l2.go = "Gigolo_2_2";
		break;
		
		case "Gigolo_2_1":
			if (sti(pchar.questTemp.Sharlie.Gigolo.Rand1) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 5000;
				dialog.text = "Nos, Monsieur, ez nem igaz! fiatal, csinos és tapasztalt, az ügyfeleim szinte csodálják ôt. sokba fog kerülni önnek. Ötezer pezó egy éjszakáért vele, és egy pezóval sem kevesebb.";
				if (sti(pchar.money) >= 5000)
				{
					link.l1 = "Drága, de nagyon jó. Tessék a pénzed.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "Ez drága! Nekem nincs ennyi pénzem. Majd késôbb beszélünk.";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 2500;
				dialog.text = "Sóhaj, igaza van, uram, csinos és fiatal, de nincs tapasztalata. Az ügyfeleim általában nem veszik észre, ezért kérdeztem. De ha tényleg szereti a szerény lányokat, azt mondom, ô egy jó választás. Kétezer-ötszáz pezóba fog kerülni.";
				if (sti(pchar.money) >= 2500)
				{
					link.l1 = "Sajnos, ô is jó lesz. Tessék a pénzed.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "Ez drága! Nekem nincs ennyi pénzem. Majd késôbb beszélünk.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_2_2":
			if (sti(pchar.questTemp.Sharlie.Gigolo.Rand2) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 4500;
				dialog.text = "Nem te lennél az elsô, szépfiú. Idônként az ügyfeleim sorban állnak érte, mert nagyon különbözik a szigeteink sötét bôrû lányaitól. Négyezer-ötszáz pezóba fog kerülni.";
				if (sti(pchar.money) >= 4500)
				{
					link.l1 = "Drága, de nagyon jó. Tessék a pénzed.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "Ez drága! Nekem nincs ennyi pénzem. Majd késôbb beszélünk.";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 3000;
				dialog.text = "Tényleg, Monsieur? Máris honvágya van? Az én kreoljaim és különösen a mulattjaim szenvedélyesebbek, mint ez a laza párizsi sikátorlány. De sajnos, ez az ön döntése. Háromezer pezóba fog kerülni.";
				if (sti(pchar.money) >= 3000)
				{
					link.l1 = "Drága, de nagyon jó. Tessék a pénzed.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "Ez drága! Nekem nincs ennyi pénzem. Majd késôbb beszélünk.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_3":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Sharlie.Gigolo.Money));
			dialog.text = "Ahogy kívánod, kedvesem. Lucille este tizenegy órakor már nagyon várja önt. Ezenkívül nem térhet vissza reggel hét óránál késôbb. Ha nem érkezel meg éjfél elôtt, akkor egy másik ügyféllel fog foglalkozni, és akkor meg kell várnod a következô estét, hogy elvihesd.\nÉs eszedbe ne jusson... megbántani ôt bármilyen módon, a legkevésbé sem bánod meg. Egy tisztességes figyelmeztetés, kedvesem.";
			link.l1 = "Ne fáradj, úgy fogok vele bánni, mint egy szeretôvel, nem mint egy vadállattal. Tizenegy órakor elviszem. Mit csináljak addig?";
			link.l1.go = "Gigolo_4a";
		break;
		
		case "Gigolo_4a":
			dialog.text = "Hát, nem is tudom, kedvesem. Ugorj be a  kocsmába, beszélgess a csapossal...";
			link.l1 = "Nem rossz ötlet. Pontosan ezt fogom tenni. Szép napot!";
			link.l1.go = "Gigolo_4";
		break;
		
		case "Gigolo_4":
			//DeleteAttribute(pchar, "GenQuest.CannotWait");
			DialogExit();
			AddQuestRecord("SharlieC", "2");
			pchar.questTemp.Sharlie.Gigolo = "girl";
			Sharlie_CreateGigoloGirl();
			QuestPointerDelLoc("fortfrance_town", "reload", "reload9_back");
			QuestPointerDelLoc("fortfrance_brothel", "reload", "reload3");
			QuestPointerToLoc("fortfrance_town", "reload", "reload4_back");
			SetCurrentTime(17, 30);
			//NewGameTip("Az idô visszatekerés funkció elérhetô! A mûvelet menü 'hangosan gondolkodni' opcióján keresztül érhetô el (ENTER).");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
