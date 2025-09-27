// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat("All the rumours of "+GetCityName(npchar.city)+" at your service. What would you like to know?","We were just talking about that. You must have forgotten...","This is the third time today you're asking me...","You're repeating the same thing like a parrot...","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("You know, "+NPChar.name+", maybe next time.","Right, I've forgotten for some reason...","Yes, it really is the third time...","Aye...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Listen, has an alchemist arrived here in this town, a physician? He's Italian, about thirty years old, his name is Gino Gvineili?";
				link.l1.go = "guardoftruth";
			}
			// Калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "hunting" && !CheckAttribute(npchar, "quest.Caleuche"))
			{
				link.l1 = "Listen, I need a hunter named Fergus Hooper. I've been told he lives here. Where can I find him?";
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
			dialog.text = LinkRandPhrase("No, I haven't. We have herbalists and physicians, but none of them by that name.","This is the first time I've heard such a strange name. No, we've never had a visit from the man you speak of.","We don't have any alchemists at all. We've got physicians, but none with a name like that.");
			link.l1 = "I see. That's too bad. I'll keep looking!";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
		
		// Калеуче
		case "caleuche":
			dialog.text = "Fergus? He often visits my place. But he's been in the selva since yesterday. Don't worry, he'll be back in a week, drinking rum and bragging about his sea adventures. Though, I admit, he's a damn good hunter. Don't know anyone who can catch snakes as well as he can.";
			link.l1 = "Snakes? Hm. When should I come back here to find him?";
			link.l1.go = "caleuche_1";
		break;
		
		case "caleuche_1":
			dialog.text = "Three days at least. Be aware that he always comes here no earlier than six p.m. and leaves no later than ten.";
			link.l1 = "What does he look like? Never seen him before.";
			link.l1.go = "caleuche_2";
		break;
		
		case "caleuche_2":
			dialog.text = "Bearded, middle-aged, wears a brown coat, hat and long boots.";
			link.l1 = "Merci! You have helped me a lot, my friend. See you around!";
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
