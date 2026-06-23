// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Quelles questions avez-vous ?","Comment puis-je vous aider, "+GetAddress_Form(NPChar)+"?"),"Tu as essayé de me poser une question il n'y a pas longtemps, "+GetAddress_Form(NPChar)+"... ","Pendant toute cette journée, c'est la troisième fois que tu parles d'une question...","Encore des questions, je présume ?","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis...","Je n'ai rien à dire pour le moment."),"Oumph, ou est donc passee ma memoire...","Oui, c'est vraiment la troisième fois...","Non, quelles questions ?...",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";						
			//Jason, Бремя гасконца
			if (CheckAttribute(PChar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "hire" && !CheckAttribute(npchar, "quest.storehelper"))
			{
				link.l1 = "Ecoute, "+npchar.name+", je suis venu vous voir pour une affaire inhabituelle. J'ai besoin de trouver un homme qui aimerait une vie calme et paisible sur la baie en tant qu'assistant de marchand dans une boutique de Saint-Pierre. Le salaire est bon et il aura un toit au-dessus de sa tête. Pourriez-vous me suggérer à qui je pourrais m'adresser ?";
				link.l1.go = "storehelper";
			}
			if (CheckAttribute(PChar, "questTemp.Sharlie") && pchar.questTemp.Sharlie == "seabattle" && !CheckAttribute(npchar, "quest.seabattle") && pchar.location.from_sea == "LeFransua_town")
			{
				link.l1 = "Je suis ici pour les tonneaux de vin que vous allez charger sur mon navire pour livraison à la Guadeloupe...";
				link.l1.go = "seabattle";
			}
			//Бремя гасконца
			//Jason, Португалец
			if (CheckAttribute(PChar, "questTemp.Portugal") && pchar.questTemp.Portugal == "PortugalLeFransua" && !CheckAttribute(npchar, "quest.portugal") && Pchar.location.from_sea == "LeFransua_town")
			{
				link.l1 = "Tu sais, "+npchar.name+", je cherche un ami à moi. Il était censé arriver ici et il ne se sentait pas bien. Peut-être que ses amis l'ont aidé...";
				link.l1.go = "Portugal";
			}
			//Португалец
		break;
		
		case "storehelper":
			dialog.text = "Hm.. Nous avons plusieurs personnes ici qui aimeraient passer de la vie de marin à celle de terrien. Je pourrais vous aider, mais je vous le dis tout de suite : ce ne sera pas gratuit.";
			link.l1 = "Heh ! Et combien veux-tu ?";
			link.l1.go = "storehelper_1";
		break;
		
		case "storehelper_1":
			dialog.text = "Un millier de pièces de huit. Et il n'y a rien que vous ayez à faire, dans une heure vos candidats pour le poste seront dans ma taverne, plusieurs candidats. Vous pourrez leur parler et choisir celui qui vous plaît le plus.";
			if (int(Pchar.money) >= 1000)
			{
				link.l1 = "Ahh... D'accord, tiens, prends mille!";
				link.l1.go = "storehelper_2";
			}
			link.l2 = "Je suis désolé, mais je n'ai pas autant d'argent !";
			link.l2.go = "storehelper_exit";
		break;
		
		case "storehelper_2":
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Ne t'inquiète pas, l'ami. Tu récupéreras la moitié de cette somme auprès du candidat. Je lui dirai que c'est le coût de tes services, hé hé... Ils ne donneront pas plus de cinq cents. Passe à ma taverne dans une heure, à ce moment-là j'aurai trouvé les gens dont tu as besoin ici, qui t'attendront.";
			link.l1 = "D'accord. Je reviendrai dans une heure, "+npchar.name+".";
			link.l1.go = "storehelper_3";
			npchar.quest.storehelper = "true";
			DelLandQuestMark(npchar);
		break;
		
		case "storehelper_3":
			DialogExit();
			SetLaunchFrameFormParam("One hour passed...", "", 0, 5);
			LaunchFrameForm();
			WaitDate("", 0, 0, 0, 1, 0); //крутим время
			RecalculateJumpTable();
			Storehelper_hire("");
		break;
		
		case "storehelper_exit":
			dialog.text = "Je suis désolé que vous n'ayez pas ce genre d'argent non plus. Mais vous savez bien, des affaires comme ça ne se règlent pas juste avec un 'merci'. Alors...";
			link.l1 = "Je comprends. Mais je n'ai vraiment pas l'argent. D'accord, au revoir...";
			link.l1.go = "exit";
			//pchar.quest.storehelper.over = "yes";
			//AddTimeToCurrent(2,0);
			//DeleteAttribute(pchar, "questTemp.Sharlie.Storehelper");
			//CloseQuestHeader("SharlieA");
		break;
		
		case "seabattle":
			DelLandQuestMark(npchar);
			dialog.text = "De quoi parles-tu, l'ami? De quel vin parles-tu?";
			link.l1 = "Un homme nommé Walter Catcher m'a envoyé à vous. Il a dit que vous aviez besoin d'un navire pour transférer une cargaison de vin à la Guadeloupe pour dix mille pesos. Et que vous avez besoin précisément de mon navire pour ce travail...";
			link.l1.go = "seabattle_1";
			npchar.quest.seabattle = "true";
		break;
		
		case "seabattle_1":
			dialog.text = "Écoute, matelot, je ne fais pas dans le vin, je n'ai pas besoin de tes services, et je ne connais aucun Walter Catcher.";
			link.l1 = "Tiens donc ! Alors, ce Traqueur n'a pas été envoyé par vous du tout... Alors, de quoi parle cette comédie ?";
			link.l1.go = "seabattle_2";
		break;
		
		case "seabattle_2":
			dialog.text = "Heh ! Eh bien, c'est soit une sorte d'erreur, soit une mauvaise blague ou...";
			link.l1 = "Où sinon ?";
			link.l1.go = "seabattle_3";
		break;
		
		case "seabattle_3":
			dialog.text = "Ne le comprends-tu pas par toi-même ? Quelqu'un devait t'attirer à Le Francois, pour une raison que j'ignore. A ta place, je me presserais de sortir d'ici en prenant toutes les précautions possibles. Ça sent les affaires louches, camarade...";
			link.l1 = "Je suppose que tu as raison. Je n'aimais pas la trogne de ce Rattrapeur. D'accord, je vais suivre ton conseil. Adieu, Cesar !";
			link.l1.go = "seabattle_4";
		break;
		
		case "seabattle_4":
			DialogExit();
			AddQuestRecord("Sharlie", "16");
			pchar.quest.seabattle.win_condition.l1 = "location";
			pchar.quest.seabattle.win_condition.l1.location = "Martinique";
			pchar.quest.seabattle.function = "SharlieSeabattle_ship";
			
			pchar.quest.NewGameTip4.win_condition.l1 = "location";
			pchar.quest.NewGameTip4.win_condition.l1.location = "LeFransua_town";
			pchar.quest.NewGameTip4.function = "ShowNewGameTip";
			pchar.quest.NewGameTip4.text = "Your first sea battle is coming! Save you game!";					  
		break;
		
		case "Portugal":
			dialog.text = "Oui, votre ami est arrivé ici, capitaine. Il est arrivé hier et a loué une chambre à l'étage. Ses compagnons de bord sont ici aussi, hé hé... Ils sont assis là-bas. Allez leur demander !";
			link.l1 = "... ";
			link.l1.go = "Portugal_1";
		break;
		
		case "Portugal_1":
			DialogExit();
			AddDialogExitQuestFunction("Portugal_enterPirates");
			npchar.quest.portugal = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
