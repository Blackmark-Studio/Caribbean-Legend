void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "C'est un bug. Informez les développeurs.";
			link.l1 = "Bien sûr!";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "Wine_fort":
			dialog.text = "As-tu apporté la bouteille ?";
			if (CheckCharacterItem(pchar, "potionwine"))
			{
				link.l1 = "Ouais, c'est ce que j'ai fait. J'ai payé 700 pesos pour ça, alors j'attends 1000 pesos de ta part.";
				link.l1.go = "Wine_fort_1";
			}
			link.l2 = "Non, j'y travaille.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Wine_fort";
		break;
	
		case "Wine_fort_1":
			AddMoneyToCharacter(pchar, 1000);
			RemoveItems(PChar, "potionwine", 1);
			dialog.text = "Dieu soit loué, je commençais à avoir la gorge sèche. Merci bien, monsieur ! Voici vos mille et je prends votre bouteille, haha ! Hé maintenant, puisque nous faisons déjà de bonnes affaires ici, j'ai une autre requête pour vous\nPourriez-vous nous procurer plus de vin pour moi et mes amis pour notre... usage futur ? Nous venons de détrousser une bande de contrebandiers, donc nous avons des pièces à dépenser, hehe...";
			link.l1 = "Désolé, l'ami, je n'ai pas le temps de faire une autre course d'alcool pour toi.";
			link.l1.go = "Wine_fort_exit";
			link.l2 = "L'argent est toujours bienvenu. Combien de bouteilles avez-vous besoin?";
			link.l2.go = "Wine_fort_2";
		break;
	
	case "Wine_fort_exit":
			DelLandQuestMark(npchar);
			WineTraderQMDel();
			dialog.text = "Comme vous le souhaitez. Merci de votre aide quand même ! À la vôtre et à votre bonne santé !";
			link.l1 = "Continuez votre bon travail, soldat !";
			link.l1.go = "exit";
			sld = characterFromId(pchar.questTemp.Wine.id);	
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			pchar.questTemp.Wine.fail = "true";
			CloseQuestHeader("Wine");
	break;
	
		case "Wine_fort_2":
			dialog.text = "À 1000 pièces de huit par bouteille, nous pouvons nous permettre d'acheter soixante bouteilles, mais pas plus. Mais ne nous en apporte pas moins de dix non plus - cela ne ferait que nous donner soif !";
			link.l1 = "Compris, pas plus de 60 bouteilles et pas moins de dix. J'apporterai votre vin.";
			link.l1.go = "Wine_fort_3";
		break;
	
		case "Wine_fort_3":
			dialog.text = "Bénis soient les pieds qui portent la bonne nouvelle d'une bonne boisson ! Je compte sur vous, capitaine. Ah, j'ai presque oublié ! Vous devrez apporter l'alcool ici en moins d'une semaine, car ma compagnie de marins sera transférée à la flotte dans sept jours et nous serons partis pour quelques mois une fois que nous partirons.";
			link.l1 = "Je vois. J'essaierai d'être rapide.";
			link.l1.go = "exit";
			pchar.questTemp.Wine.bottles = "true";
			npchar.lifeday = 7;
			AddQuestRecord("Wine", "1");
			AddQuestUserData("Wine", "sCity", XI_ConvertString("Colony"+pchar.questTemp.Wine.City+"Gen"));
			AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.SName);
			SetFunctionTimerCondition("Soldier_wait", 0, 0, 7, false);
			NextDiag.TempNode = "Wine_fort_check";
			SetFunctionLocationCondition("WineTraderQM", pchar.questTemp.Wine.City+"_town", 0);
		break;
	
		case "Wine_fort_check":
			dialog.text = "Alors, capitaine, avez-vous apporté le vin ?";
			if (int(pchar.items.potionwine) >= 10)
			{
				link.l1 = "Oui, je l'ai fait.";
				link.l1.go = "Wine_take";
			}
			link.l2 = "Non. Je travaille encore dessus.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Wine_fort_check";
		break;
	
		case "Wine_take":
			pchar.questTemp.Wine.Qty = int(pchar.items.potionwine);
			pchar.questTemp.Wine.Money = int(pchar.questTemp.Wine.Qty)*1000;
			if (int(pchar.items.potionwine) > 60)
			{
				dialog.text = "Sainte Arnulf, priez pour nous ! Ça fait beaucoup de vin ! Excellent ! Hélas, comme je l'ai dit, nous ne pouvons nous permettre que soixante bouteilles, malheureusement nous n'avons pas assez d'argent pour en acheter plus. Prenez vos pesos et je prendrai bien soin de ces soixante bouteilles. Veuillez garder le reste.";
				link.l1 = "Merci. Assurez-vous que vous et vos amis soldats portiez un toast à ma santé !";
				link.l1.go = "Wine_take_1";
				pchar.questTemp.Wine.Money = 60000;
				RemoveItems(PChar, "potionwine", 60);
			}
			else
			{
				dialog.text = "Bon retour. Voyons voir... Vous avez apporté "+int(pchar.questTemp.Wine.Qty)+" bouteilles. Super ! Je les prends. Le paiement est "+FindRussianMoneyString(int(pchar.questTemp.Wine.Money))+".";
				link.l1 = "Merci. Assurez-vous que toi et tes amis soldats portiez un toast à ma santé !";
				link.l1.go = "Wine_take_1";
				RemoveItems(PChar, "potionwine", int(pchar.questTemp.Wine.Qty));
			}
		break;
	
		case "Wine_take_1":
			AddMoneyToCharacter(pchar, int(pchar.questTemp.Wine.Money));
			dialog.text = "Nous le ferons certainement, "+GetAddress_Form(NPChar)+" ! Le tambour sonne l'assemblée, je dois y aller maintenant. Adieu !";
			link.l1 = "Bon vent et mer clémente, l'ami !";
			link.l1.go = "Wine_take_2";
		break;
	
		case "Wine_take_2":
			DelLandQuestMark(npchar);
			DialogExit();
			PlaySound("interface\important_item.wav");
			Log_Info ("You handed over the wine");
			pchar.quest.Soldier_wait.over = "yes";//снять прерывание
			DeleteAttribute(pchar, "questTemp.Wine.City");
			sld = characterFromId(pchar.questTemp.Wine.id);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "none", "", "", "", -1);
			sld.lifeday = 0;
			CloseQuestHeader("Wine");
			AddCharacterExpToSkill(pchar, "Commerce", 150);//торговля
			AddCharacterExpToSkill(pchar, "Leadership", 50);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 50);//везение
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
