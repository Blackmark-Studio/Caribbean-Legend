// диалог по городам
void ProcessCommonDialogEvent(ref NPChar, aref Link, aref NextDiag)
{
    switch (Dialog.CurrentNode)
	{
		case "quests":
			dialog.text = NPCStringReactionRepeat(RandPhraseSimple("Que voulez-vous? Demandez donc.","Je vous écoute, quelle est la question ?"),"C'est la deuxième fois que vous essayez de demander...","C'est la troisième fois que vous essayez de demander...","Quand cela va-t-il finir ?! Je suis un homme occupé, travaillant sur les affaires de la colonie et vous continuez à me déranger !","block",1,npchar,Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat(RandPhraseSimple("J'ai changé d'avis, désolé.","Pas maintenant. Mauvais endroit et mauvais moment."),"Vrai, je n'ai rien à dire pour le moment, désolé.","Je demanderai, plus tard.","Je suis désolé, "+GetAddress_FormToNPC(NPChar)+"... ",npchar,Dialog.CurrentNode);
			link.l1.go = "exit";
			// Addon-2016 Jason, французские миниквесты (ФМК) Тортуга
			if (CheckAttribute(pchar, "questTemp.FMQT") && pchar.questTemp.FMQT == "huber")
			{
				link.l1 = "Monsieur le Gouverneur, j'ai des nouvelles terribles pour vous. Je serai bref : votre femme veut vous voler. Elle a essayé de me persuader de crocheter l'un de vos coffres. Je pensais que vous deviez le savoir.";
                link.l1.go = "FMQT";
			}
			// Jason НСО
			if (CheckAttribute(pchar, "questTemp.Patria") && pchar.questTemp.Patria == "epizode_2" && !CheckAttribute(npchar, "quest.patria") && !CheckAttribute(pchar, "questTemp.Patria.Visiter_Late"))
			{
				link.l1 = TimeGreeting()+", Monsieur. Je suis ici sur ordre du Gouverneur-Général Chevalier de Poincy. Ma tâche est d'escorter un baron du nom de Noel Forget à Tortuga, arrivé de la métropole avec l'ordre d'inspecter les colonies. Son but principal est d'établir une Compagnie des Indes Occidentales Françaises. Permettez-moi de vous le présenter... Il vous expliquera tous les détails lui-même.";
                link.l1.go = "patria_tortuga";
			}
		break;
		
		case "FMQT":
			dialog.text = "Quoi ? Encore ? Cette garce ! Elle le regrettera, oh je te le jure ! Kampacho la fera crier. Pourquoi es-tu encore là ? Fiche le camp d'ici !";
			link.l1 = "Je pensais...";
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) > 25) link.l1.go = "FMQT_2";
			else link.l1.go = "FMQT_1";
		break;
		
		case "FMQT_1":
			Notification_Skill(false, 26, SKILL_LEADERSHIP);
			AddMoneyToCharacter(pchar, 1000);
			dialog.text = "Toujours la même chose ! Tiens, prends ça ! C'est tout ce que j'ai sur la table ! Maintenant, dehors !";
			link.l1 = "Merci, votre Excellence. Je trouverai la sortie moi-même.";
			link.l1.go = "FMQT_3";
		break;
		
		case "FMQT_2":
			AddMoneyToCharacter(pchar, 1000);
			GiveItem2Character(pchar, "pistol6");
			GiveItem2Character(pchar, "purse1");
			Log_Info("You have received a double barreled pistol and a purse of doubloons");
			dialog.text = "Toujours la même chose ! Tiens, prends ça ! C'est tout ce que j'ai sur la table !.. Cependant, bon, tu ne ressembles pas aux autres imbéciles et perdants dont mon île est remplie. Prends un peu plus... Maintenant, dégage !";
			link.l1 = "Merci, votre Excellence. Je vais me retirer.";
			link.l1.go = "FMQT_3";
		break;
		
		case "FMQT_3":
			DialogExit();
			pchar.quest.FMQT_late1.over = "yes";
			ChangeCharacterNationReputation(pchar, FRANCE, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			pchar.questTemp.FMQT = "end";
			FMQ_Count();
			AddQuestRecord("FMQ_Tortuga", "7");
			CloseQuestHeader("FMQ_Tortuga");
			FMQT_ClearChest();
		break;
		
		// Jason НСО
		case "patria_tortuga":
			dialog.text = "Bien, capitaine Charles de Maure. Le baron sera traité en conséquence et je ferai ce que je peux pour l'aider dans sa tâche.";
			link.l1 = "";
			link.l1.go = "patria_tortuga_1";
		break;
		
		case "patria_tortuga_1":
			DialogExit();
			sld = characterFromId("Noel");
			sld.dialog.currentnode = "noel_5";
			ChangeCharacterAddressGroup(sld, pchar.location, "goto", "governor1");
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 1.0);
			npchar.quest.patria = "true";
		break;
	}
	UnloadSegment(NPChar.FileDialog2);  // если где-то выход внутри switch  по return не забыть сделать анлод
}
