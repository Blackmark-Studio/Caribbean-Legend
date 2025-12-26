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
				dialog.text = "Argh! Hic... Quem diabos é você? Onde está aquele chinês maldito? Estou falando com você, está surdo? Hic!";
				link.l1 = "Estou ouvindo perfeitamente, então não grite. Nenhum chinês vai aparecer. Eu vim no lugar dele.";
				link.l1.go = "HollJacob_inRoom";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Um bug. Avise os desenvolvedores.";
			link.l1 = "Se você diz...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "HollJacob_inRoom":
			dialog.text = "O quê? Quem é você? Que diabos está fazendo aqui? Eu fiz uma pergunta, seu verme!";
			link.l1 = "Você não precisa saber disso. Eu preciso do seu navio.";
			link.l1.go = "HollJacob_inRoom_1";			
		break;
		
		case "HollJacob_inRoom_1":
			dialog.text = "Argh... O quê?! Você tá de sacanagem... espera! Você é um maldito cachorro inglês! Droga! Eles me acharam afinal... Chegou o seu fim! Eu não vou me render!";
			link.l1 = "Bem, não preciso que você se renda...";
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
				dialog.text = "Argh! Merda! Que bagunça! Você não é um comerciante, né?";
				link.l1 = "Que garoto esperto. Minha tripulação é formada por fuzileiros navais ingleses escolhidos a dedo, então você estava condenado desde o começo. Richard Fleetwood e eu inventamos a história do comerciante, e aqui está você. Suas aventuras acabaram, bastardo!";
				link.l1.go = "JacobBerg_abordage_1";
			}
			else
			{
				dialog.text = "Finalmente nos encontramos, capitão. Você é um sujeito astuto... Faz tempo que não enfrento um adversário tão sério.";
				link.l1 = "E eu sou seu último oponente, Jacob. Você não vai sair daqui vivo.";
				link.l1.go = "JacobBerg_abordage_3";
			}
		break;
		
		case "JacobBerg_abordage_1":
			dialog.text = "Parece que sim. Sua tripulação capturou o navio e não espero ser poupado. Mas vou te mandar para o inferno antes que venham te ajudar! Van Berg vai lutar até o fim!";
			link.l1 = "Essa é só a sua opinião. Eu acho que sua vida não vale nem um centavo. Chega de conversa, prepare-se!";
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
			dialog.text = "Ah, é mesmo? Eu tratei de garantir que você não fuja. Acendi o pavio do paiol. Logo nossos navios vão pelos ares.";
			link.l1 = "Acho que só você e esse seu barco velho vão pelos ares. Eu vou te abrir, pegar meu navio de volta e assistir ao espetáculo enquanto vou embora velejando.";
			link.l1.go = "JacobBerg_abordage_4";			
		break;
		
		case "JacobBerg_abordage_4":
			dialog.text = "Não se eu te matar primeiro, pular pela janela, nadar até a praia e assistir ao espetáculo de fogos eu mesmo!";
			link.l1 = "Aposta?";
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
