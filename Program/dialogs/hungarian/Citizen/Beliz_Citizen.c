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
			//--> Дикая Роза
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "About a month and a half ago a certain Jerome Sauvernier arrived in Belize. He was wounded in a brawl at the 'Glass Eye', but survived. Could you tell me where I might find him?";
				link.l1.go = "WildRose_Beliz_Citizen_1";
			}
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_2") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "A month and a half ago, give or take, a gentleman appeared in Belize. His name was Jerome Sauvernier. He was searching for another man – so he must have spoken with townsfolk. Later he was injured in a tavern brawl, but fortunately survived. Can you tell me where I might find him?";
				link.l1.go = "WildRose_Beliz_Citizen_2";
			}
			if(CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz") && CheckAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_3") && !CheckAttribute(npchar, "quest.WildRose_Vopros") && npchar.city == "Beliz")
			{
				link.l1 = "I am trying to find a man who arrived in Belize about two months ago. His name is Jerome Sauvernier. He was looking for a certain gentleman, and I suppose he spoke with the townsfolk about it...";
				link.l1.go = "WildRose_Beliz_Citizen_3";
			}
			//<-- Дикая Роза
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
		
		//--> Дикая Роза
		case "WildRose_Beliz_Citizen_1":
    		dialog.text = "I don’t know such a man, sir. Brawls in the tavern are near daily business, and remembering every fellow who got hurt is a thankless task.";
    		link.l1 = "I see, thank you. All the best.";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen");
			pchar.questTemp.WildRose_Beliz_Citizen_2 = true;
			npchar.quest.WildRose_Vopros;
 		break;
		
		case "WildRose_Beliz_Citizen_2":
    		dialog.text = "Sauvernier? A Frenchman... Yes, there was such a one. He came to me for help, but there was nothing I could do for him. I have not seen him since, forgive me.";
    		link.l1 = "Thank you. Well then, I shall continue asking around.";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_2");
			pchar.questTemp.WildRose_Beliz_Citizen_3 = true;
			npchar.quest.WildRose_Vopros;
 		break;
		
		case "WildRose_Beliz_Citizen_3":
			dialog.text = "Mister Jerome! Of course, of course, I remember him. He was wounded in a tavern brawl. Since then he hardly leaves his house, tending to the wound on his leg.";
			link.l1 = "And where is this house?";
    		link.l1.go = "WildRose_Beliz_Citizen_3_1";
 		break;
		
		case "WildRose_Beliz_Citizen_3_1":
    		dialog.text = "It’s right here, quite nearby, next to the port authority. The house with the red roof. That’s where you’ll find him.";
    		link.l1 = "Thank you, you’ve been a great help! All the very best to you!";
    		link.l1.go = "exit";
			DeleteAttribute(pchar, "questTemp.WildRose_Beliz_Citizen_3");
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_3_citizen");
 		break;
		//<-- Дикая Роза
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
