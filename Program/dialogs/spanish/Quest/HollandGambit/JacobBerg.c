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
				dialog.text = "¡Argh! Hic... ¿Quién demonios eres tú? ¿Dónde está el maldito chino? Te estoy hablando, ¿estás sordo? ¡Hic!";
				link.l1 = "Te oigo alto y claro, así que no grites. No vendrá ningún chino. Estoy aquí en su lugar.";
				link.l1.go = "HollJacob_inRoom";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "Un error. Díselo a los desarrolladores.";
			link.l1 = "Si tú lo dices...";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "HollJacob_inRoom":
			dialog.text = "¿Qué? ¿Quién eres tú? ¡¿Qué diablos haces aquí?! ¡Te he hecho una pregunta, escoria!";
			link.l1 = "No necesitas saber eso. Necesito tu barco.";
			link.l1.go = "HollJacob_inRoom_1";			
		break;
		
		case "HollJacob_inRoom_1":
			dialog.text = "¡Argh... ¿Qué?! ¿Estás demente?... ¡Espera! ¡Eres un maldito perro inglés! ¡Al diablo con esto! Me han rastreado después de todo... ¡Es el final del camino para ti! ¡No voy a rendirme!";
			link.l1 = "Bueno, no necesito que te rindas...";
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
				dialog.text = "¡Argh! ¡Maldita sea! ¡Qué desastre! No eres un comerciante, ¿verdad?";
				link.l1 = "Qué chico tan listo. Mi tripulación está llena de marines ingleses seleccionados, así que estabas jodido desde el principio. Richard Fleetwood y yo inventamos la historia del comerciante y aquí estás. ¡Tus aventuras han terminado, bastardo!";
				link.l1.go = "JacobBerg_abordage_1";
			}
			else
			{
				dialog.text = "Por fin nos encontramos, capitán. Eres un tipo astuto... Ha pasado mucho tiempo desde que me encontré con un oponente tan serio.";
				link.l1 = "Y yo soy tu último oponente, Jacob. No saldrás de aquí con vida.";
				link.l1.go = "JacobBerg_abordage_3";
			}
		break;
		
		case "JacobBerg_abordage_1":
			dialog.text = "Así parece. Tu tripulación ha capturado el barco y no cuento con que me perdonen. ¡Pero te mandaré al infierno antes de que vengan a ayudarte! ¡Van Berg va a vender su vida a un alto precio!";
			link.l1 = "Esa es solo tu opinión. Creo que tu vida no vale ni un solo centavo. ¡Basta de palabras, prepárate!";
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
			dialog.text = "¿De veras? Me he asegurado de que no escapes. He encendido una mecha hacia el polvorín. Pronto nuestros navíos volarán en pedazos.";
			link.l1 = "Creo que solo tú y tu vieja bañera van a volar. Voy a destriparte, liberar mi barco y ver los fuegos artificiales mientras navego lejos.";
			link.l1.go = "JacobBerg_abordage_4";			
		break;
		
		case "JacobBerg_abordage_4":
			dialog.text = "¡No si te mato primero, salto por la ventana, nado hacia la orilla y veo los fuegos artificiales yo mismo!";
			link.l1 = "¿Apuesta?";
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
