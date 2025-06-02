// Якоб ван Берг - злодей и пират, капитан Миража
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl") && pchar.questTemp.HWIC.Holl == "JacobInRoom")
			{
				dialog.text = "Argh! Hic... Chi diavolo sei tu? Dov’è finito quel dannato cinese? Ti sto parlando, sei sordo? Hic!";
				link.l1 = "Ti sento forte e chiaro, quindi non urlare. Nessun cinese verrà. Sono qui al suo posto.";
				link.l1.go = "HollJacob_inRoom";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Un maledetto errore. Avvisa quei diavoli di sviluppatori.";
			link.l1 = "Se lo dici tu...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "HollJacob_inRoom":
			dialog.text = "Cosa? Chi diavolo sei? Che cazzo ci fai qui? Ti ho fatto una domanda, lurido bastardo!";
			link.l1 = "Non t’interessa saperlo. Mi serve la tua nave.";
			link.l1.go = "HollJacob_inRoom_1";			
		break;
		
		case "HollJacob_inRoom_1":
			dialog.text = "Argh... Cosa?! Sei proprio... aspetta! Sei un dannato cane inglese! Maledizione! Mi hanno trovato alla fine... Qui finisce la tua corsa! Non mi arrenderò mai!";
			link.l1 = "Beh, non ho bisogno che tu ti arrenda...";
			link.l1.go = "HollJacob_inRoom_fight";			
		break;
		
		case "HollJacob_inRoom_fight":
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.questTemp.HWIC.Holl.JacobCity+"_tavern_upstairs")], false);
			pchar.quest.JacobOnMainOver.over = "yes";//снять таймер
			chrDisableReloadToLocation = true;
			LAi_group_MoveCharacter(npchar, "EnemyFight");
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
            LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
            LAi_group_SetCheck("EnemyFight", "HollJacob_dead");
			DialogExit();
			AddDialogExitQuest("MainHeroFightModeOn");	
		break;
		
		case "JacobBerg_abordage":
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				dialog.text = "Argh! Maledizione! Che casino! Non sei certo un mercante, vero?";
				link.l1 = "Che ragazzo sveglio. La mia ciurma è piena di marines inglesi scelti, quindi eri spacciato fin dall’inizio. Richard Fleetwood ed io abbiamo inventato la storia del mercante e guarda dove sei finito. Le tue avventure sono finite, bastardo!";
				link.l1.go = "JacobBerg_abordage_1";
			}
			else
			{
				dialog.text = "Finalmente ci incontriamo, capitano. Siete un tipo astuto... Da troppo tempo non mi capitava un avversario tanto degno.";
				link.l1 = "E io sono il tuo ultimo avversario, Jacob. Da qui non ne uscirai vivo.";
				link.l1.go = "JacobBerg_abordage_3";
			}
		break;
		
		case "JacobBerg_abordage_1":
			dialog.text = "Pare proprio di sì. La tua ciurma ha preso la nave e non conto certo sulla clemenza. Ma ti trascinerò all’inferno prima che arrivino ad aiutarti! Van Berg venderà cara la sua pelle!";
			link.l1 = "Questa è solo la tua opinione. Io credo che la tua vita non valga nemmeno un soldo bucato. Basta chiacchiere, preparati!";
			link.l1.go = "JacobBerg_abordage_2";			
		break;
		
		case "JacobBerg_abordage_2":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle(""); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
		break;
		
		case "JacobBerg_abordage_3":
			dialog.text = "Oh davvero? Mi sono assicurato che tu non possa scappare. Ho acceso una miccia nella santabarbara. Tra poco le nostre navi salteranno in aria.";
			link.l1 = "Penso che solo tu e la tua vecchia carcassa siete destinati a saltare per aria. Ti sventrerò, riprenderò la mia nave, e guarderò i fuochi d’artificio mentre me ne vado a vele spiegate.";
			link.l1.go = "JacobBerg_abordage_4";			
		break;
		
		case "JacobBerg_abordage_4":
			dialog.text = "Non se ti ammazzo prima io, salto dalla finestra, nuoto fino a riva e mi godo lo spettacolo coi miei occhi!";
			link.l1 = "Puntata?";
			link.l1.go = "JacobBerg_abordage_5";			
		break;
		
		case "JacobBerg_abordage_5":
			LAi_SetCurHPMax(NPChar);
			LAi_GetCharacterMaxEnergy(NPChar);			
			QuestAboardCabinDialogExitWithBattle("PrepareToBoom2"); 
			DialogExit();	
			AddDialogExitQuest("MainHeroFightModeOn");
			pchar.GenQuest.Detonation = true; // patch-4
		break;
}
}
