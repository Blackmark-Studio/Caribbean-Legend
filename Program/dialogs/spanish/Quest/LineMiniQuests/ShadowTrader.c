// Бесчестный конкурент
void ProcessDialogEvent()
{
	ref sld, NPChar;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "Esto es un error. Informa a los desarrolladores.";
		link.l1 = "¡Claro!";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "ShadowGuarder":
		dialog.text = "¿Qué necesitas?";
		link.l1 = "¿Eres tú " + pchar.questTemp.Shadowtrader.Guardername + "? El mercader me envia y espera impacientemente tu presencia en este mismo momento.";
		link.l1.go = "ShadowGuarder_1";
		DelLandQuestMark(npchar);
		break;

	case "ShadowGuarder_1":
		dialog.text = "¡A-ah, pero lo estaba esperando aquí! ¡Me dijeron que vendría a una taberna! Lo siento, voy de camino de inmediato.";
		link.l1 = "¡Muy bien!";
		link.l1.go = "ShadowGuarder_2";
		break;

	case "ShadowGuarder_2":
		DialogExit();
		chrDisableReloadToLocation = true;
		sld = characterFromId("ShadowGuarder");
		LAi_SetStayType(sld);
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(sld, pchar.questTemp.Shadowtrader.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload1_back", pchar.questTemp.Shadowtrader.City + "_store", "goto", "goto2", "OpenTheDoors", -1);
		pchar.questTemp.Shadowtrader = "begin";
		AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;

	case "ShadowAgent":
		dialog.text = "Buenas noches, capitán. ¿Quieres conseguir algunas mercancías baratas, eh? ¡Sígueme!";
		link.l1 = "Guía el camino.";
		link.l1.go = "ShadowAgent_1";
		break;

	case "ShadowAgent_1":
		DeleteAttribute(pchar, "questTemp.Shadowtrader.SeekTrader");
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "houseS4", "CommonFlamHouse", "barmen", "stay", "Shadow_inRoom", 40);
		break;

	case "ShadowTrader":
		dialog.text = "Buenas noches, señor. Es bueno conocer a un nuevo cliente, ¡ja! Permítame presentarme: soy " + GetFullName(npchar) + " . Tengo las mercancías más baratas de este pueblo, te lo aseguro.";
		link.l1 = "Finalmente nos hemos encontrado..." + npchar.name + " Supongo que te decepcionaré: no te buscaba para comerciar, sino para acabar con tu sucio chanchullo. Has sido un gran dolor en el trasero de un hombre importante. El dolor se ha vuelto tan grande que está ansioso por cerrarte... por cualquier medio necesario.";
		link.l1.go = "ShadowTrader_1";
		if (IsCharacterPerkOn(pchar, "Trustworthy"))
		{
			notification("Trustworthy", "Trustworthy");
			link.l2 = "¡Detente ahí, escoria criminal! ¿No sabías que tienes que pagar impuestos por operar un negocio comercial? ¡Nadie infringe la ley bajo mi vigilancia!" + GetFullName(npchar) + ", ¡violaste la ley y tus bienes robados ahora están confiscados! Hay soldados armados justo detrás de mí afuera de la puerta, ¡así que ni siquiera intentes hacerte el tonto!";
			link.l2.go = "ShadowTrader_2";
		}
		AddLandQuestMark(characterFromId("BasTer_trader"), "questmarkmain");
		break;

	case "ShadowTrader_1":
		dialog.text = "¿De veras? No esperaba... ¿Quién diablos eres tú?! ¡Esto es una trampa! ¡Supongo que sé quién es el responsable de esto! ¡Por todos los medios necesarios... muchachos, mátenlo!";
		link.l1 = "¡Bailemos, bribón!";
		link.l1.go = "ShadowTrader_fight";
		NextDiag.currentnode = "ShadowTrader_6";
		break;

	case "ShadowTrader_2":
		dialog.text = "Oh Dios... ¡oficial, escuche! Hagamos un trato. ¡Eres un hombre sabio y misericordioso! Te pagaré 5000 piezas de a ocho y nos dejarás escapar por el segundo piso. También te llevarás las mercancías, las necesitas, ¿verdad? ¿Para qué me necesitas a mí? Dejaré la ciudad ahora mismo y nadie nos volverá a ver. Y tú obtendrás tu dinero. ¿Qué dices, oficial?";
		link.l1 = "¿Realmente piensas, escoria, que deshonraré mi deber por una suma tan insignificante?";
		link.l1.go = "ShadowTrader_3";
		break;

	case "ShadowTrader_3":
		dialog.text = "Está bien, está bien, oficial, llévese todo lo que tengo - 10,000 pesos. Es todo lo que tengo, ¡lo juro!";
		link.l1 = "Mm... Si te arresto, todo tu dinero será confiscado... ¡Muy bien! Este puesto de contrabando está cerrado y todos los bienes son confiscados... Dame la moneda y piérdete. ¡No muestres tu cara por aquí de nuevo!";
		link.l1.go = "ShadowTrader_4";
		break;

	case "ShadowTrader_4":
		dialog.text = "¡Gracias, gracias, gracias oficial! Aquí está tu dinero, y no me volverás a ver aquí. ¡Vámonos!";
		link.l1 = "¡Sal o tendré que arrestarte!";
		link.l1.go = "ShadowTrader_escape";
		break;

	case "ShadowTrader_fight":
		LAi_SetPlayerType(pchar);
		for (i = 1; i <= 2; i++)
		{
			sld = characterFromId("ShadowAgent_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			sld.nation = PIRATE;
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "ShadowTrader_afterfight");
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "ShadowTrader_escape": // напугали
		AddMoneyToCharacter(pchar, 10000);
		LAi_SetPlayerType(pchar);
		for (i = 1; i <= 2; i++)
		{
			sld = characterFromId("ShadowAgent_" + i);
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 7.0);
		}
		sld = characterFromID("ShadowTrader");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 7.0);
		DialogExit();
		DoQuestFunctionDelay("ShadowTrader_final", 9.0);
		pchar.questTemp.Shadowtrader.End.Escape = "true";
		AddQuestRecord("Shadowtrader", "8");
		AddCharacterExpToSkill(pchar, "Leadership", 200); // авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 250);	  // везение
		AddCharacterExpToSkill(pchar, "Sneak", 300);	  // скрытность
		break;

	case "ShadowTrader_6":
		dialog.text = "¡Ah! ¡Misericordia, no me mates! ¡Te daré todo lo que tengo!";
		link.l1 = "Todos tus bienes serán confiscados por las autoridades. ¿Realmente crees que tendré piedad de ti después de lo que acaba de suceder aquí?";
		link.l1.go = "ShadowTrader_7";
		break;

	case "ShadowTrader_7":
		dialog.text = "¡Yo... te daré todo mi dinero y pertenencias! ¡Solo déjame ir! ¡Dejaré la isla hoy y no me volverás a ver aquí!";
		link.l1 = "Muy bien. Dame todo lo que tengas y piérdete. Y no vuelvas a intentar hacer negocios aquí nunca más - la próxima vez no perdonaré tu patética vida, bribón.";
		link.l1.go = "ShadowTrader_free";
		link.l2 = "¡De ninguna manera, bastardo, no me comprarás! ¡La única forma de tratar con los de tu calaña es con acero frío y plomo caliente!";
		link.l2.go = "ShadowTrader_killed";
		break;

	case "ShadowTrader_free": // отпустили
		AddMoneyToCharacter(pchar, 20550);
		TakeNItems(pchar, "jewelry1", rand(5));
		TakeNItems(pchar, "jewelry2", rand(20));
		TakeNItems(pchar, "jewelry5", rand(20));
		PlaySound("interface\important_item.wav");
		Log_Info("Has recibido artículos");
		LAi_SetPlayerType(pchar);
		sld = characterFromID("ShadowTrader");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload3", "none", "", "", "", 5.0);
		DialogExit();
		DoQuestFunctionDelay("ShadowTrader_final", 7.0);
		pchar.questTemp.Shadowtrader.End.Free = "true";
		AddQuestRecord("Shadowtrader", "9");
		ChangeCharacterComplexReputation(pchar, "nobility", 5);
		AddComplexSelfExpToScill(70, 70, 70, 70);
		AddCharacterExpToSkill(pchar, "Leadership", 100); // авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);	  // везение
		break;

	case "ShadowTrader_killed":
		DialogExit();
		LAi_SetImmortal(npchar, false);
		LAi_SetActorType(pchar);
		//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
		if (!CheckAttribute(pchar, "equip." + GUN_ITEM_TYPE) || !CheckAttribute(pchar, "equip." + MUSKET_ITEM_TYPE))
		{
			GiveItem2Character(pchar, "pistol1");
			EquipCharacterbyItem(pchar, "pistol1");
		}
		// <-- legendary edition
		LAi_ActorAnimation(pchar, "Shot", "ShadowTrader_killed_end", 1.3);
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
