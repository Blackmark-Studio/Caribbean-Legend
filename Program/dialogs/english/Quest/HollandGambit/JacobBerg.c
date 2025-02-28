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
				dialog.text = "Argh! Hic... Who the hell are you? Where is the damn Chinese? I am talkin to you, are you deaf? Hic!";
				link.l1 = "I hear you loud and clear, so don't shout. No Chinese will come. I am here instead of him.";
				link.l1.go = "HollJacob_inRoom";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "A bug. Tell the devs.";
			link.l1 = "If you say so...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "HollJacob_inRoom":
			dialog.text = "What? Who are you? What the fuck are you doing here? I asked you a question, scum!";
			link.l1 = "You don't need to know that. I need your ship.";
			link.l1.go = "HollJacob_inRoom_1";			
		break;
		
		case "HollJacob_inRoom_1":
			dialog.text = "Argh... What?! Are you fucking... wait! You are a damn English dog! Screw this! They have tracked me down after all... End of the line for you! I'm not gonna surrender!";
			link.l1 = "Well, I don't need you to surrender...";
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
				dialog.text = "Argh! Fuck! Such a mess! You are not a merchant, aren't you?";
				link.l1 = "Such a smart boy. My crew is full of selected English marines, so you were screwed from the beginning. Richard Fleetwood and I had made up the trader's story and here you are. Your adventures are ended, bastard!";
				link.l1.go = "JacobBerg_abordage_1";
			}
			else
			{
				dialog.text = "At last we have met, captain. You are a clever fellow... It is been too long since I've met such a serious opponent.";
				link.l1 = "And I am your last opponent, Jacob. You won't leave here alive.";
				link.l1.go = "JacobBerg_abordage_3";
			}
		break;
		
		case "JacobBerg_abordage_1":
			dialog.text = "It seems like that. You crew has captured the ship and I am not counting on to be spared. But I will send you to hell before they will come to aid you! Van Berg is going to sell his life for a high price!";
			link.l1 = "That is only your opinion. I think that your life doesn't cost a single penny. Enough of these words, prepare yourself!";
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
			dialog.text = "Oh really? I have made sure that you dont get away. I have fired a fuse to the powder room's. Soon our vessels will be blown to pieces.";
			link.l1 = "I think that only you and your old tub is going to blow. I am going to gut you, release my ship, and watch the fireworks as I sail away.";
			link.l1.go = "JacobBerg_abordage_4";			
		break;
		
		case "JacobBerg_abordage_4":
			dialog.text = "Not if I kill you first, jump out the window, swim to the shore and watch the fireworks myself!";
			link.l1 = "Stake?";
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
