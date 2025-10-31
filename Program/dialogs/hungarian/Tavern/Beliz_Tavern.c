// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("A "+ GetCityName(npchar.city) +" összes pletykája az Ön rendelkezésére áll. Mit szeretnél megtudni?",
                          "Éppen errôl beszéltünk. Biztos elfelejtette...", "Ez ma már a harmadik alkalom, hogy megkérdezed...",
                          "Ismétled ugyanazt, mint egy papagáj...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Tudod, " + NPChar.name + ", talán legközelebb.", "Rendben, valamiért elfelejtettem...",
                      "Igen, ez tényleg a harmadik alkalom...", "Aye...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Figyelj, volt egy alkimista, aki megérkezett ide a városba, egy orvos? Olasz, körülbelül harminc éves, a neve Gino Gvineili?";
				link.l1.go = "guardoftruth";
			}
			// Калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && !CheckAttribute(npchar, "quest.Caleuche"))
			{
				link.l1 = "Figyelj, szükségem van egy Fergus Hooper nevû vadászra. Azt mondták, hogy itt él. Hol találom meg?";
				link.l1.go = "caleuche";
				DelLandQuestMark(npchar);
			}
			//--> Дикая Роза
			if (CheckAttribute(pchar, "questTemp.WildRose_Etap6_Beliz"))
			{
				link.l1 = "About a month and a half ago a certain Jerome Sauvernier arrived in your town. Do you recall him?";
				link.l1.go = "WildRose_Tavern_1";
			}
			//<-- Дикая Роза
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Nem, még nem. Vannak gyógynövényszakértôink és orvosaink, de egyiküknek sincs ilyen neve.","Most hallottam elôször ilyen furcsa nevet. Nem, még soha nem látogatott meg minket az az ember, akirôl beszél.","Nálunk egyáltalán nincsenek alkimisták. Vannak orvosaink, de ilyen nevûek nincsenek.");
			link.l1 = "Értem. Az nagy kár. Tovább keresgélek!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
		
		// Калеуче
		case "caleuche":
			dialog.text = "Fergus? Gyakran jár hozzám. De tegnap óta a Selva-ban van. Ne aggódj, egy hét múlva visszajön, rumot iszik, és a tengeri kalandjaival henceg. Bár elismerem, hogy átkozottul jó vadász. Nem ismerek senkit, aki olyan jól el tudná kapni a kígyókat, mint ô.";
			link.l1 = "Kígyókat? Hm. Mikor jöjjek vissza ide, hogy megtaláljam ôt?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Legalább három nap múlva. Ne feledd, hogy mindig legkorábban este hatkor jön ide, és legkésôbb tízkor távozik.";
			link.l1 = "Hogy néz ki? Még sosem láttam.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Szakállas, középkorú, barna kabátot, kalapot és hosszú csizmát visel.";
			link.l1 = "Köszönöm! Sokat segítettél nekem, haver. Még találkozunk!";
			link.l1.go = "caleuche_3";
		break;
		
		case "caleuche_3":
			DialogExit();
			AddQuestRecord("Caleuche", "8");
			int iTerms = sti(pchar.questTemp.Caleuche.Belizterms);
			SetFunctionTimerCondition("Caleuche_FergusCome", 0, 0, iTerms, false);
			npchar.quest.Caleuche = "true";
		break;
		
		//--> Дикая Роза
		case "WildRose_Tavern_1":
			dialog.text = "Uh... I think so. Yes, I remember that gentleman. Not dressed to the nines, but he had money.";
			link.l1 = "He was hurt in a brawl in your tavern.";
			link.l1.go = "WildRose_Tavern_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Tavern_2":
			dialog.text = "So what of it? Fights break out here every other day. Sailors get drunk, words are exchanged – and then you can’t stop them. You look like a seasoned man – surely such things don’t surprise you?";
			link.l1 = "Not at all. The thing is, this man is an old acquaintance of mine. We agreed to meet here, but I was a bit late. Could you tell me where I might find him?";
			link.l1.go = "WildRose_Tavern_3";
		break;

		case "WildRose_Tavern_3":
			dialog.text = "Why shouldn’t I tell you, sir? As I said, he had enough coin – so he rented a house near the port authority. A notable one, with a red roof. He’s holed up there, barely goes out, mending his leg. From time to time he drops in here for a drink. But it’s never certain – some days he comes, some days he doesn’t.";
			link.l1 = "Then I’ll call on him at his house. Thank you for the information. Farewell.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_3_tavern");
		break;
		//<-- Дикая Роза
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
