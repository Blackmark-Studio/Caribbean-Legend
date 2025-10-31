// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    ref sld;   
	switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("What kind of questions, "+GetSexPhrase("young man","young lady")+"?","What is it you need, "+GetSexPhrase("handsome","pretty one")+"? Ask away."),"Questions again","Tee-hee, if it's all the same to you - questions...",""+GetSexPhrase("Hm, why don't you pick a beauty for yourself? I'm starting to get suspicious about you...","Hm, why don't you pick a beauty for yourself? I'm afraid we don't have any boys here, tee-hee...")+"","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("I've changed my mind, excuse me.","Actually, never mind."),"I... apologies, I have no questions for now.","You're right, it's the third time already. Pardon me.","Maybe next time, Madam.",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			/* //--> Бремя гасконца
			if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start")
			{
				DelLandQuestMark(npchar);
				link.l1 = "Listen, Aurora, I need a girl for the night. And I want to take her home with me. Can you arrange that?";
                link.l1.go = "Gigolo";
			}	
			//<-- Бремя гасконца */
		break;
		
		//--> Бремя гасконца
		case "Gigolo":
			dialog.text = "Of course, dear. Have you already found a suitable maiden or should I?";
			link.l1 = "Indeed I did. I have my eye on a girl named Lucille.";
			link.l1.go = "Gigolo_1";
		break;
		
		case "Gigolo_1":
			dialog.text = "Are you referring to Lucille Montaigne?";
			link.l1 = "Truth be told, I didn't ask her surname. All I know is that she is a young, beautiful, blonde-haired girl by the name of Lucille.";
			link.l1.go = "Gigolo_2";
		break;
		
		case "Gigolo_2":
			dialog.text = "Yes, that does describe her very well. Alright. But tell me, why her? Are the other girls not to your liking?";
			link.l1 = "Well, you see... she just started working here, so I believe she is not yet experienced enough in the 'Trade' to be too much of a burden on my purse.";
			link.l1.go = "Gigolo_2_1";
			link.l2 = "You see, I adore blondes with fair skin. Lucille will be perfect in that regard.";
			link.l2.go = "Gigolo_2_2";
		break;
		
		case "Gigolo_2_1":
			if (sti(pchar.questTemp.Sharlie.Gigolo.Rand1) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 5000;
				dialog.text = "Now Monsieur, that isn't true! She is young, pretty, and experienced; my clients all but admire her. She will cost you a lot. Five thousand pesos for a night with her, and not a single peso less.";
				if (sti(pchar.money) >= 5000)
				{
					link.l1 = "Expensive, but very well. Here is your coin.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "That is expensive! I don't have that much. I'll talk to you later.";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 2500;
				dialog.text = "Sigh, you're right, Monsieur, she's pretty and young but lacks experience. My clients usually don't notice her, hence why I asked. But if you truly are fond of modest girls, I'd say she's a good choice. She will cost you two thousand and five hundred pesos.";
				if (sti(pchar.money) >= 2500)
				{
					link.l1 = "Alas, she will do just fine. Have your coin.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "That's expensive! I don't have that much. I'll talk to you later.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_2_2":
			if (sti(pchar.questTemp.Sharlie.Gigolo.Rand2) == 0)
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 4500;
				dialog.text = "You wouldn't be the first, handsome. At times my clients stand in queue for her attention, as she is very distinct from the dark-skinned daughters of our islands. She will cost you four thousand and five hundred pesos.";
				if (sti(pchar.money) >= 4500)
				{
					link.l1 = "Expensive, but very well. Take your coin.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "That's expensive! I don't have that much. I'll talk to you later.";
					link.l1.go = "exit";
				}
			}
			else
			{
				pchar.questTemp.Sharlie.Gigolo.Money = 3000;
				dialog.text = "Truly, Monsieur? Homesick already? My Creoles and especially my mulattos are more passionate than this laid-back Parisian alleycat. But alas, it is your choice. She will cost you three thousand pesos.";
				if (sti(pchar.money) >= 3000)
				{
					link.l1 = "Expensive, but very well. Here is your coin.";
					link.l1.go = "Gigolo_3";
				}
				else
				{
					link.l1 = "That's expensive! I don't have that much. I'll talk to you later.";
					link.l1.go = "exit";
				}
			}
		break;
		
		case "Gigolo_3":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Sharlie.Gigolo.Money));
			dialog.text = "As you wish, dear. Lucille will be waiting for you eagerly at eleven o'clock in the evening. Additionally, she must not return later than seven o'clock in the morning. If you don't arrive before midnight, she will attend to another client, and then you will have to wait until the next evening to see her. And don't you dare... hurt her in any way, lest you regret it. A fair warning, dear.";
			link.l1 = "Don't trouble yourself, I'll treat her like a lover, not a brute. I'll take her at eleven o'clock. Now, what should I do until then?";
			link.l1.go = "Gigolo_4a";
		break;
		
		case "Gigolo_4a":
			dialog.text = "Well, I don't even know, dear. Stop by the tavern, have a chat with the bartender...";
			link.l1 = "Not a bad idea. I'll do just that. Have a nice day!";
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
			//NewGameTip("Доступна функция перемотки времени! Она доступна через опцию 'мысли вслух' в меню действий (ENTER).");
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
