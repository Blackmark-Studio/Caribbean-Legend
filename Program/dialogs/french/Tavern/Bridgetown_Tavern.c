// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quelles questions avez-vous ?","Comment puis-je vous aider, "+GetAddress_Form(NPChar)+"?"),"Tu as essayé de me poser une question il n'y a pas longtemps, "+GetAddress_Form(NPChar)+"... ","C'est la troisième fois que tu m'importunes maintenant...","Encore des questions, je suppose ?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Je n'ai rien à dire pour le moment."),"Umph, où est passée ma mémoire...","Oui, c'est vraiment la troisième fois...","Non, quelles questions ?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			//Голландский гамбит /за Англию/
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "GotoBridgetown" && !CheckAttribute(npchar, "quest.HWICTalked"))
            {
                link.l1 = "Je voudrais boire un verre. Verse-moi le meilleur rhum que tu as.";
                link.l1.go = "TavernDone";
            }
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng") && pchar.questTemp.HWIC.Eng == "toBarbados")
            {
                link.l1 = "Écoute, où est Callow Gaston ?";
                link.l1.go = "Tonzag_Letter";
            }
			//Голландский гамбит /против всех/
			if (!CheckAttribute(npchar, "quest.HWICTake") && CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Self") && !CheckAttribute(pchar, "questTemp.HWIC.Eng") && !CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
                link.l1 = "Auriez-vous par hasard du travail ? Ou peut-être pourriez-vous me conseiller quelque chose ?";
                link.l1.go = "Tonzag_check";
            }
			if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "FernandoDie")
			{
                link.l1 = "J'ai terminé le travail. Fernando Rodriguez est mort.";
                link.l1.go = "Task_check";
            }
			// Страж Истины
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "merdok" && !CheckAttribute(npchar, "quest.jino"))
			{
				link.l1 = "Écoutez, est-ce qu'un alchimiste est arrivé ici dans cette ville, un médecin ? Il est italien, environ trente ans, il s'appelle Gino Gvineili. Avez-vous entendu quelque chose à ce sujet ?";
				link.l1.go = "guardoftruth";
			}
		break;
		
		//Голландский гамбит /за Англию/
		case "TavernDone":
			dialog.text = "Voici votre boisson. Le meilleur rhum pour notre nouvel invité ! Est-ce une occasion spéciale ou êtes-vous simplement passé pour vous rincer le gosier ?";
			link.l1 = "Oui, on peut dire que c'est une occasion spéciale. J'emmène quelques nègres à Blueweld. J'ai récemment modifié la cale de mon nouveau brigantin spécialement pour cela. Je viens de m'arrêter dans une plantation et j'ai parlé avec le contremaître, il m'a commandé un beau lot d' 'ivoire noir'. Alors attends-moi bientôt dans ta taverne. Je livrerai la marchandise à Blueweld et ensuite je ferai encore quelques affaires ici à la Barbade, yo ho !";
			link.l1.go = "TavernDone_1";
		break;
		
		case "TavernDone_1":
			dialog.text = "Vraiment ? Eh bien, il n'y a pas de honte à boire pour une bonne affaire ! Alors, vous dites que vous allez faire des affaires à la Barbade ? C'est formidable ! À votre santé, capitaine !";
			link.l1 = "Merci bien, l'ami. D'accord... Je vais chercher un endroit où je peux m'asseoir.";
			link.l1.go = "exit";	
			npchar.quest.HWICTalked = "true";
			pchar.questTemp.HWIC.Eng.BridgeCounter = sti(pchar.questTemp.HWIC.Eng.BridgeCounter)+1;
			AddQuestRecord("Holl_Gambit", "2-12");
			DelLandQuestMark(npchar);
			if (sti(pchar.questTemp.HWIC.Eng.BridgeCounter) == 7) 
			{
				AddQuestRecord("Holl_Gambit", "2-6");
				pchar.questTemp.HWIC.Eng = "SeekVanBerg";
				pchar.quest.GotoBridgetownOver.over = "yes";//снять таймер
				DelMapQuestMarkCity("Bridgetown");
				pchar.quest.VanBergAttack_Check.win_condition.l1 = "MapEnter";
				pchar.quest.VanBergAttack_Check.function = "VanBergAttackCheck";
			}
		break;
		
		case "Tonzag_Letter":
			dialog.text = "Gaston a quitté la ville deux jours après votre acte de 'commerçant'. Vous avez fait le spectacle ici, ha ! Votre tromperie a été vite découverte, cette ville est petite et les potins circulent vite. Cela a poussé Gaston à partir. Personne ne l'a revu ici depuis. Cependant, il vous a laissé une lettre\nIl a demandé de vous la remettre en mains propres si vous vous présentiez ici avant lui. En fait, vous n'êtes pas le premier homme à chercher Gaston. Il y avait un grand homme aux yeux étroits et un vieux, qui semblait espagnol ou portugais, je ne peux pas dire avec certitude. Mais je ne peux pas oublier son visage, il y avait quelque chose de très louche chez lui...";
			link.l1 = "Donne-moi cette lettre... Merci !";
			link.l1.go = "Tonzag_Letter_1";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Bridgetown");
		break;
		
		case "Tonzag_Letter_1":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-22");
			AddQuestRecordInfo("LetterFromGaston", "1");
			pchar.questTemp.HWIC.Eng = "toCuracao";
			LocatorReloadEnterDisable("SentJons_town", "houseSP3", true);//закрыть дом Флитвуда
			LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);//закрыть аптеку
			LocatorReloadEnterDisable("SentJons_town", "basement1_back", true);//закрыть подземелье
			pchar.quest.Knippel_Shore.win_condition.l1 = "location";
			pchar.quest.Knippel_Shore.win_condition.l1.location = "Shore24";
			pchar.quest.Knippel_Shore.function = "KnippelOnCuracao";
			AddMapQuestMarkShore("Shore24", true);
		break;
		
		//Голландский гамбит /против всех/
		case "Tonzag_check"://начинаем проверять нашего ГГ по всем статьям
			if(sti(pchar.reputation.nobility) > 48)//высокая репа
			{
				// belamour legendary edition покажем критерии
				notification("Reputation Too Low! (Rogue)", "None");
				PlaySound("Voice\English\hambit\Ercule Tongzag-03.wav");
				dialog.text = "Je n'ai pas besoin des services d'un vaurien. Je n'ai aucune tâche à vous proposer.";
				link.l1 = "Hey, hey. Doucement avec le langage, mate!";
				link.l1.go = "exit";
				break;
			}
			bool bOk = GetSummonSkillFromName(pchar, SKILL_F_LIGHT) > 34 || GetSummonSkillFromName(pchar, SKILL_FENCING) > 34 || GetSummonSkillFromName(pchar, SKILL_F_HEAVY) > 34 || GetSummonSkillFromName(pchar, SKILL_PISTOL) > 34;
			if(!bOk)//слабое фехтование
			{
				// belamour legendary edition покажем критерии -->
				notification("Skill Check Failed (35)", SKILL_F_LIGHT);
				notification("Skill Check Failed (35)", SKILL_FENCING);
				notification("Skill Check Failed (35)", SKILL_F_HEAVY);
				notification("Skill Check Failed (35)", SKILL_PISTOL);
				// <--
				dialog.text = "Capitaine, vous êtes trop tendre. J'ai besoin d'un combattant un peu plus réputé que vous. Revenez quand vous saurez manier ce morceau d'acier qui pend à votre ceinture. Et un peu de précision au tir ne ferait pas de mal non plus.";
				link.l1 = "Je vois. Alors je te rendrai visite plus tard.";
				link.l1.go = "exit";
				break;
			}
			PlaySound("Voice\English\hambit\Ercule Tongzag-02.wav");
			dialog.text = "Hm... Tu es effectivement à l'heure. J'ai une course qui doit être accomplie sur-le-champ. Si tu te montres à la hauteur, je te présenterai à quelques personnes influentes. Maintenant écoute, voici ce que tu dois faire.";
			link.l1 = "Je suis tout ouïe.";
			link.l1.go = "Tonzag_task";
		break;
		
		case "Tonzag_task":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("Bridgetown");
			pchar.questTemp.HWIC.Self.SpainCity = FindSpainCity();
			log_Testinfo(pchar.questTemp.HWIC.Self.SpainCity);
			dialog.text = "Un hidalgo est récemment arrivé de Séville avec l'intention d'éviter quelques conséquences indésirables d'un duel en Europe. Mais la vengeance n'a pas de limites et une famille noble espagnole souhaite la mort de cet hidalgo. Accomplis leur requête par tous les moyens nécessaires. Apporte le doigt de l'homme avec sa bague comme preuve. Apporte aussi tous les autres objets que tu trouveras sur son cadavre. Es-tu prêt à accepter cette mission ?";
			link.l1 = "Si la paie est bonne, alors je suis partant.";
			link.l1.go = "Tonzag_task_1";
			link.l2 = "Travailler comme assassin ? Pas question !";
			link.l2.go = "Tonzag_exit";
			npchar.quest.HWICTake = "true";
			pchar.questTemp.HWIC.CanTake.Self = "true";//признак, что против всех уже бралась
		break;
		
		case "Tonzag_exit":
			dialog.text = "Alors va te faire foutre et oublie ce dont nous avons discuté.";
			link.l1 = "Je m'en vais.";
			link.l1.go = "exit";	
			DeleteAttribute(pchar, "questTemp.HWIC.Self");//откат к двум другим вариантам
			pchar.questTemp.HWIC.Fail3 = "true";
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
			{
				AddMapQuestMarkCity("Villemstad", false);
				AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			}
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
			{
				AddMapQuestMarkCity("SentJons", false);
				AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			}
		break;
		
		case "Tonzag_task_1":
			dialog.text = "Votre récompense sera de 30 000 pièces de huit, une belle somme. En plus de cela, vous pouvez prendre chaque pièce que vous trouverez sur son corps. Maintenant, discutons des détails. Il s'appelle Don Fernando Rodriguez, 35 ans, grand, basané, habillé comme un officier militaire. C'est un bon marin et un escrimeur expérimenté. Je ne peux pas dire où le trouver, tout ce que je sais, c'est qu'il est quelque part dans les Caraïbes. Cherchez dans chaque ville espagnole jusqu'à ce que vous l'attrapiez. Vous avez deux mois. Une dernière chose : je suis au courant de ce qu'il porte sur lui, alors n'envisagez même pas de me cacher quoi que ce soit. Des questions ?";
			link.l1 = "Je n'ai pas de questions. Je suis en route!";
			link.l1.go = "Tonzag_task_2";	
		break;
		
		case "Tonzag_task_2":
			DialogExit();
			pchar.questTemp.HWIC.Self = "start";
			SetFunctionTimerCondition("TargetFernandoOver", 0, 0, 60, false); //таймер
			//SetFunctionExitFromLocationCondition("CreateMapMarksTonzag", pchar.location, false);
			AddQuestRecord("Holl_Gambit", "3-1");
			ReOpenQuestHeader("Holl_Gambit"); // данила . чтобы вышел из архива																				  
			Log_TestInfo(""+XI_ConvertString("Colony"+pchar.questTemp.HWIC.Self.SpainCity)+"");
			DelLandQuestMark(npchar);
			DelLandQuestMark(characterFromId("Lucas"));
			DelLandQuestMark(characterFromId("Knippel"));
			DelMapQuestMarkCity("Bridgetown");
			DelMapQuestMarkCity("Villemstad");
			DelMapQuestMarkCity("SentJons");
			AddMapQuestMarkCity(pchar.questTemp.HWIC.Self.SpainCity, true);
			AddLandQuestMark(characterFromId(pchar.questTemp.HWIC.Self.SpainCity+"_tavernkeeper"), "questmarkmain");
		break;
		
		case "Task_check":
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("bridgetown");
			dialog.text = "Avez-vous un doigt avec une bague dessus avec vous ? Laissez-moi le voir.";
			if (CheckCharacterItem(pchar, "Finger"))
			{
				link.l1 = "Oui, bien sûr. Le voici.";
				link.l1.go = "Task_check_1";	
			}
			else
			{
				link.l1 = "Non. Fernando a sombré dans l'eau avec son navire et le doigt a coulé avec Fernando.";
				link.l1.go = "Task_fail";	
			}
		break;
		
		case "Task_fail":
			dialog.text = "Le doigt avec la bague était une condition obligatoire du contrat. Il devait servir de confirmation de la mort du client. Qui sait si Rodriquez a nagé jusqu'au rivage depuis le navire coulé? As-tu vérifié? Non. Tu as essentiellement échoué à la mission, donc notre accord est terminé. Tous mes voeux.";
			link.l1 = "Mais je l'ai éliminé. Il est parti ! Oh, va te faire foutre... Y'a plein d'autres choses à faire dans les Caraïbes. Adieu.";
			link.l1.go = "exit";
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
			{
				AddMapQuestMarkCity("Villemstad", false);
				AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
			}
			if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
			{
				AddMapQuestMarkCity("SentJons", false);
				AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
			}
			pchar.questTemp.HWIC.Fail3 = "true";
			AddQuestRecord("Holl_Gambit", "3-8");
			CloseQuestHeader("Holl_Gambit");
			DeleteAttribute(pchar, "questTemp.HWIC.Self");//зачищаем для возможности отката к голландскому варианту
		break;
		
		case "Task_check_1":
			RemoveItems(PChar, "Finger", 1);
			dialog.text = "Formidable ! Je garderai le doigt pour moi. Maintenant, voyons le contenu de ses poches. Voyons ce que tu as apporté.";
			link.l1 = "Allez-y, jetez un oeil...";
			link.l1.go = "Task_check_2";	
		break;
		
		case "Task_check_2":
			if (CheckCharacterItem(pchar, "jewelry7") && CheckCharacterItem(pchar, "totem_05") && CheckCharacterItem(pchar, "amulet_1"))
			{
				dialog.text = "Aha, c'est tout ce qu'il me faut. Bien joué ! Tu as fait du bon travail. Je suis très content de toi.";
				link.l1 = "Merci ! C'est toujours agréable d'être félicité pour un travail bien fait.";
				link.l1.go = "Task_complete";	
			}
			else
			{
				dialog.text = "Hm... Je t'ai prévenu que je sais ce dont Rodriguez ne se passerait jamais. Et je ne vois pas ce dont j'ai besoin ici. Aurais-tu empoché ces objets ? Les aurais-tu perdus ? Peu importe de toute façon. Je n'ai plus envie d'avoir affaire à toi. Dégage d'ici.";
				link.l1 = "Oh, va te faire foutre...";
				link.l1.go = "exit";
				pchar.questTemp.HWIC.Fail3 = "true";
				if(!CheckAttribute(pchar, "questTemp.HWIC.Fail1"))
				{
					AddMapQuestMarkCity("Villemstad", false);
					AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
				}
				if(!CheckAttribute(pchar, "questTemp.HWIC.Fail2"))
				{
					AddMapQuestMarkCity("SentJons", false);
					AddLandQuestMark(characterFromId("Knippel"), "questmarkmain");
				}
				AddQuestRecord("Holl_Gambit", "3-9");
				CloseQuestHeader("Holl_Gambit");
				DeleteAttribute(pchar, "questTemp.HWIC.Self");//зачищаем для возможности отката к голландскому варианту
			}
		break;
		
		case "Task_complete":
			RemoveItems(PChar, "jewelry7", 1);
			RemoveItems(PChar, "totem_05", 1);
			RemoveItems(PChar, "amulet_1", 1);
			AddMoneyToCharacter(pchar, 30000);
			dialog.text = "Voici votre récompense comme promis, trente mille. Et j'ai aussi une mission supplémentaire, de haute responsabilité et à haut risque, mais la paye augmentera en conséquence, 40,000 pesos.";
			link.l1 = "Je suis tout ouïe. Qui est le prochain client ?";
			link.l1.go = "Fleetwood_house";	
		break;
		
		//2 задание
		case "Fleetwood_house":
			PlaySound("Voice\English\hambit\Ercule Tongzag-05.wav");
			dialog.text = "Cette fois, tu vas chasser non pas un homme, mais un objet. Tu dois t'introduire dans la maison de Richard Fleetwood à Antigua et voler son journal de bord. Il est un capitaine anglais. L'endroit est étroitement gardé et Richard lui-même visite rarement sa maison.\nLe plan est simple. Le gouverneur de St. Jones organisera une fête privée dans dix jours, Fleetwood y assistera. Tu dois entrer dans sa maison la nuit entre une heure et trois heures. Il n'y aura qu'un soldat à l'intérieur.\nDébarrasse-toi de lui. Cherche un journal dans l'appartement de Richard. Prends cette clé.";
			link.l1 = "Hm... Intéressant. J'ai compris ce que je dois faire. Je suis prêt à y aller !";
			link.l1.go = "Fleetwood_house_1";	
		break;
		
		case "Fleetwood_house_1":
			GiveItem2Character(pchar, "key3");
			dialog.text = "Sois prudent. Ne t'introduis pas dans la maison avant la date que je t'ai indiquée. Sinon, dans le meilleur des cas, ils te mettront simplement à la porte, ou dans le pire des cas, tu te retrouveras derrière les barreaux. Répète-moi la date et l'heure.";
			link.l1 = "Dans exactement dix jours, entre une heure et trois heures du matin.";
			link.l1.go = "Fleetwood_house_2";	
		break;
		
		case "Fleetwood_house_2":
			dialog.text = "Très bien. Tu peux y aller. Bonne chance !";
			link.l1 = "Merci, Gaston.";
			link.l1.go = "Fleetwood_house_3";
		break;
		
		case "Fleetwood_house_3":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-10");
			pchar.questTemp.HWIC.Self = "theft";
			DeleteAttribute(pchar, "questTemp.HWIC.CanTake");//иные варианты более невозможны
			LocatorReloadEnterDisable("SentJons_houseSP3", "reload2", true);//комнату закроем
			pchar.GenQuestBox.SentJons_houseSP3_room = true;
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.FleetwoodJournal = 1;//положим в комод СЖ
			pchar.GenQuestBox.SentJons_houseSP3_room.box1.items.sand_clock = 1;//и песочные часы
			AddDialogExitQuestFunction("CreateFleetwoodSoldiers");//4 солдат в доме
			if(bImCasual) NewGameTip("Exploration mode: timer is not disabled. Meet the deadline!");
			SetFunctionTimerCondition("FleetwoodJournalOver", 0, 0, 11, false);//таймер
			pchar.quest.Fleetwood_Journal.win_condition.l1 = "Timer";
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.hour  = sti(GetTime());
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 9);
			pchar.quest.Fleetwood_Journal.win_condition.l2 = "Hour";
			pchar.quest.Fleetwood_Journal.win_condition.l2.start.hour = 0;
			pchar.quest.Fleetwood_Journal.win_condition.l2.finish.hour = 3;
			pchar.quest.Fleetwood_Journal.win_condition.l3 = "locator";
			pchar.quest.Fleetwood_Journal.win_condition.l3.location = "SentJons_town";
			pchar.quest.Fleetwood_Journal.win_condition.l3.locator_group = "reload";
			pchar.quest.Fleetwood_Journal.win_condition.l3.locator = "houseSP3";//доступно открывание двери
			pchar.quest.Fleetwood_Journal.function = "FleetwoodHouseEnter";
			pchar.quest.Fleetwood_Soldier.win_condition.l1 = "location";
			pchar.quest.Fleetwood_Soldier.win_condition.l1.location = "SentJons_houseSP3";
			pchar.quest.Fleetwood_Soldier.function = "Fleetwood_Soldier";//если надумает раньше заявиться
			AddMapQuestMarkCity("sentjons", true);
		break;
		
		case "guardoftruth":
			dialog.text = LinkRandPhrase("Non, je ne l'ai pas vu. Nous avons des herboristes et des médecins, mais aucun d'eux ne porte un tel nom.","C'est la première fois que j'entends un nom aussi étrange. Non, nous n'avons jamais eu la visite de l'homme dont vous parlez.","Nous n'avons aucun type d'alchimiste ici. Nous avons des médecins, mais aucun avec un nom aussi étrange.");
			link.l1 = "Je vois. C'est dommage. Je vais continuer à chercher !";
			link.l1.go = "exit";
			npchar.quest.jino = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}

string FindSpainCity()//Jason выбрать радномный испанский город - пусть побегает
{
	int n, nation;
    int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
    int howStore = 0;

	for(n=0; n<MAX_COLONIES; n++)
	{
		if (colonies[n].nation == SPAIN && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0) return "none";
	nation = storeArray[hrand(howStore-1)];
	return colonies[nation].id;
}
