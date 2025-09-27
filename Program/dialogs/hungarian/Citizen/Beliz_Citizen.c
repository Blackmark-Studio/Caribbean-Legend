// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
            dialog.text = RandPhraseSimple("Milyen kérdések?", "Mit akarsz?");
			link.l1 = RandPhraseSimple("Meggondoltam magam.'", "Most már nincs mit mondanom.");
		    link.l1.go = "exit";
			// Rebbebion, квест "Путеводная звезда" ==>
			if (CheckAttribute(pchar, "questTemp.PZ_Beliz.AskForLatterAndSotta") && !CheckAttribute(npchar, "questTemp.PZ_Sotta") && !CheckAttribute(npchar, "questTemp.PZ_Lutter"))
			{
				if (rand(1) == 0)
				{
					link.l1 = "Nem találkozott véletlenül Edgardo Sotta kapitánnyal? Tudna valamit mondani róla? Úgy hangzik, mint akit érdemes ismerni.";
					link.l1.go = "Sotta1";
					link.l2 = "Nem akarja megnézni a Szélzsák kivégzését?";
					link.l2.go = "Lutter1";
				}
				else
				{
					link.l1 = "Mondja, látta a nap hôsét, Edgardo Sotta kapitányt? Sajnos lemaradtam róla. Hogy néz ki? Nem hiszem el, hogy egy kereskedô elkapta a hírhedt Szélzsák Mattet!";
					link.l1.go = "Sotta1_1";
					link.l2 = "Látom, az egész város ünnepli Lutter elfogását, még azok is, akik soha nem mennek ki a tengerre."
					link.l2.go = "Lutter1_1";
				}
			}
			// <== квест "Путеводная звезда"
		break;
		
		case "info":
        // заменить на описание неких НПС, по квестам
			dialog.text = "Azt hiszi, hogy a "+NationNameGenitive(sti(NPChar.nation))+"titkosszolgálatának dolgozom?";
			link.l1 = "Nos... nem. Akkor viszlát.";
			link.l1.go = "exit";
			link.l2 = "Van még kérdésed?";
			link.l2.go = "new question";
		break;
		
		case "town":
        // заменить на описание как пройти, по квестам
			dialog.text = "Úgy nézek ki, mint a nyomozóiroda? Nem tudom, nem tudok semmit.";

            link.l1 = "Maga olyan zavarosfejû! Távozz.";
			link.l1.go = "exit";
			link.l2 = "Van még kérdésed?";
			link.l2.go = "new question";
		break;
		
		// Квест "Путеводная звезда" ==>
		case "Sotta1":
			dialog.text = "Nem tudtam beszélni vele, de láttam a hajóját - egy nehéz gályát. Veszélyes egyedül hajózni ezeken a vizeken, de Sotta kíséret nélkül teszi.";
			link.l1 = "Valószínûleg minden aranyérmére vadászik, és ott spórol, ahol csak tud. Nos, nem tartalak fel. Szép napot!";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Sotta1_1":
			dialog.text = "Igen, nehéz elhinni! De ne higgyen el mindent, amit hall, uram. Láttam ôt, olyan tisztán, mint ahogy most magát látom. Jó, hogy elkapta Luttert, de minek ez az egész kereskedôi színjáték? Úgy viselkedik, mint egy katona. Mindig meg tudom mondani - egy rokonom évekig szolgált.";
			link.l1 = "Érdekes. Nos, mindenkinek megvannak a maga titkai. Jobb, ha megyek. Köszönöm a felvilágosítást.";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Sotta = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1":
			dialog.text = "Már láttam a férfit. Nehéz elhinni, hogy ez ugyanaz a kalóz, aki évekig terrorizálta a kereskedôinket. Egyáltalán, hogy kapta meg a saját parancsnokságát? Láttam a katonákat, akik kísérték - kiabáltak, sírtak, nevettek. Egy ôrült.";
			link.l1 = "Talán a vereség és a közelgô halál valósága túl sok volt neki. De ez nem számít. Viszontlátásra!";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		
		case "Lutter1_1":
			dialog.text = "Igen, és én is ünnepelek - jó néhány honfitársam meghalt a keze által. A szerencsétlenek apát, testvért, fiút veszítettek - érted a képet. Ez a barbárság túl sokáig tartott! Matt az utóbbi évek egyik legszerencsésebb kalóza lehetett, ha engem kérdeztek.";
			link.l1 = "A szerencse elôbb-utóbb mindig elfogy. Még találkozunk.";
			link.l1.go = "Exit";
			
			npchar.questTemp.PZ_Lutter = true;
			pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
			AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;
		// <== Квест "Путеводная звезда"
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
