void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "¿Qué quieres?";
		link.l1 = "Nada.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////----------------------------------------- работорговец -----------------------------------------------------
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//--> пинас
	case "TakeShoreCap":
		dialog.text = "¡Sinvergüenza! ¡Gran sorpresa para ti!";
		link.l1 = "¿Qué?";
		link.l1.go = "Node_1";
		break;

	case "Node_1":
		dialog.text = "¡Ja, ja! ¡No hay esclavos aquí! Estás aquí por ellos, ¿verdad?";
		link.l1 = "Maldita sea. Y yo pensando por qué demonios había tantos soldados en un pinaza de comercio... ¡Una trampa!";
		link.l1.go = "Node_2";
		break;

	case "Node_2":
		dialog.text = "Sí, bastardo, es una trampa. ¡No soy un comerciante, soy un oficial militar! Aunque hayas ganado la pelea, ¡no escaparás del juicio!";
		link.l1 = "¿Y por qué eso? Te acabaré ahora, hundiré tu barco y nadie sabrá nada.";
		link.l1.go = "Node_3";
		break;

	case "Node_3":
		dialog.text = "Estás equivocado. Tu negocio con ese banquero fue revelado. Pronto, el gobernador general se enterará de tu pequeño negocio y no escaparás de la horca. ¡Pero te haré un favor matándote aquí y ahora!";
		link.l1 = "¡Intenta, perro del gobernador!";
		link.l1.go = "Node_4";
		break;

	case "Node_4":
		pchar.questTemp.Slavetrader = "TakeShoreCap_end"; // это состояние квеста для проверки у квестодателя
		AddQuestRecord("Slavetrader", "13");
		AddQuestUserData("Slavetrader", "sShipName", pchar.questTemp.Slavetrader.ShipName);
		pchar.quest.Slavetrader_DieHard.over = "yes";
		pchar.quest.Slavetrader_AfterBattle.over = "yes";
		pchar.quest.Slavetrader_ShoreShipsOver.over = "yes";
		Island_SetReloadEnableGlobal(pchar.questTemp.Slavetrader.Island, true);
		LAi_SetCurHPMax(NPChar);
		LAi_GetCharacterMaxEnergy(NPChar);
		QuestAboardCabinDialogExitWithBattle("");
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "Slave_arest":
		dialog.text = "" + GetFullName(pchar) + "¡, en el nombre de la ley, estás bajo arresto! ¡Rinde tus armas y síguenos!";
		link.l1 = "¿Qué está pasando, oficial? ¿Rendirse en qué condiciones?";
		link.l1.go = "Slave_arest_1";
		break;

	case "Slave_arest_1":
		dialog.text = "¡No intentes hacerte el tonto, capitán! Tu sucio negocio fue revelado. Y por la masacre que has cometido y por el barco de " + NationNameGenitive(sti(npchar.nation)) + " que hundiste, ¡te veremos colgado!";
		link.l1 = "Bueno, ya que lo pones así... ¡Vete a la mierda!";
		link.l1.go = "Slave_arest_2";
		break;

	case "Slave_arest_2":
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		LAi_SetWarriorTypeNoGroup(npchar);
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	//--> крыса в доме
	case "Rat_bandos":
		dialog.text = "¡Oye, ¿qué haces aquí?!";
		link.l1 = "¿Por qué eres tan grosero, buen señor? ¿Está ese maldito Gontier escondido por aquí, eh?";
		link.l1.go = "Node_rat_1";
		break;

	case "Node_rat_1":
		dialog.text = "¡No, él no es! ¡Fuera!";
		link.l1 = "Parece que estás mintiendo. Realizaré un registro de la casa y veré...";
		link.l1.go = "Node_rat_2";
		break;

	case "Node_rat_2":
		dialog.text = "¡Que te jodan! ¡Francois! ¡Corre! ¡Chicos, ayudadme!";
		link.l1 = "¡Mierda!";
		link.l1.go = "Node_rat_3";
		break;

	case "Node_rat_3":
		LAi_SetPlayerType(pchar);
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Slavetrader_findTortugaRat1");
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "Rat_lover":
		dialog.text = "¡Oh! ¡No me violes!";
		link.l1 = "¿Qué demonios...? ¿Dónde está Francois Gontier? ¡Respóndeme, puta asquerosa, o acabarás igual que esos compinches tuyos!";
		link.l1.go = "Rat_lover_1";
		break;

	case "Rat_lover_1":
		dialog.text = "No, no, ¡te contaré todo! Ha saltado por la ventana y ha huido a su barco.";
		link.l1 = "¿Qué barco? Sé que no hay su barco en el puerto. No me mientas, muchacha, o se pondrá peor...";
		link.l1.go = "Rat_lover_2";
		break;

	case "Rat_lover_2":
		dialog.text = "¡No estoy mintiendo, lo juro! Dijo que desembarcó en una pequeña isla y llegó aquí en un bote... ¡Debe estar allí! ¡No me hagas daño!";
		link.l1 = "Está bien, parece que dices la verdad. Quédate aquí y mantente callado. Y trata de hacer amigos de una forma más inteligente en el futuro. Pero, lo veo en tus ojos y me dicen que no tienes sesos.";
		link.l1.go = "Rat_lover_3";
		pchar.quest.Slavetrader_RatAttack.win_condition.l1 = "location";
		pchar.quest.Slavetrader_RatAttack.win_condition.l1.location = "Tortuga"; // отправляем в локацию
		pchar.quest.Slavetrader_RatAttack.function = "Slavetrader_RatCorvette";	 // создание корвета
		if (bImCasual)
			NewGameTip("Modo exploración: el temporizador no está desactivado. ¡Cumple el plazo!");
		SetFunctionTimerCondition("Slavetrader_RatCorvetteOver", 0, 0, 1, false);
		break;

	case "Rat_lover_3":
		LAi_SetPlayerType(pchar);
		SetCharacterRemovable(npchar, false);
		LAi_SetActorType(npchar);
		npchar.lifeday = 0;
		AddQuestRecord("Slavetrader", "21_9");
		DialogExit();
		break;

	//--> беглые рабы
	case "Slave_woman":
		dialog.text = "¡Perdónanos! ¡Misericordia! ¡Nos rendimos!";
		link.l1 = "¿Oh, en serio? ¡Ve al almacén ahora! ¡Dispararé a cualquiera que intente hacerse el tonto!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Slavetrader_Slavewoman");
		break;
		//<--работорговец

		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		/////----------------------------------------- Генераторы -----------------------------------------------------
		//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		//--> Jason ------------------------ Сомнительное предложение -------------------------------------------
		int iCGood;
	case "Contraoffer_patrol":
		chrDisableReloadToLocation = false;
		iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
		pchar.GenQuest.Contraoffer.Trader.PatrolSumm = sti(pchar.GenQuest.Contraoffer.Trader.Summ) / 3;
		dialog.text = "Bueno, bueno... ¿Qué tenemos aquí? ¿No sabes que comerciar bienes con y entre individuos no autorizados está prohibido en nuestra colonia?";
		link.l1 = "¿Es así, oficial? Para ser honesto, es la primera vez que oigo hablar de eso. Este decreto fue aprobado hace poco, ¿verdad?";
		link.l1.go = "Contraoffer_patrol_1";
		link.l2 = "¿Qué, comerciando " + GetGoodsNameAlt(iCGood) + "¿ No veo nada " + GetGoodsNameAlt(iCGood) + " alrededor, oficial. Solo veo estas monedas relucientes... Y él ve lo mismo. ¿Por qué no echan un vistazo usted y sus soldados a nuestras monedas también?";
		link.l2.go = "Contraoffer_patrol_pay1";
		break;

	case "Contraoffer_patrol_1":
		if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > hrand(120))
		{
			dialog.text = "¿No lo sabías, eh? Hmm... parece que no estás mintiendo. Pero, sin embargo, has violado la ley. No te arrestaré, pero debo hacer que pagues una multa. Y la carga... hablaremos de ella con el segundo participante del trato.";
			link.l1 = "¿Y cuánto es esa multa?";
			link.l1.go = "Contraoffer_patrol_pay2";
		}
		else
		{
			dialog.text = "¡No te hagas el tonto, capitán! Todos lo saben ya, y desde hace mucho tiempo, debo añadir. Estoy arrestándoles a ambos por contrabando y su carga será confiscada.";
			link.l1 = "No me gustan las casamatas, oficial. Me gusta el mar abierto... y voy a navegar allí ahora. Pero parece que tendría que hacerlo solo sobre tu cadáver.";
			link.l1.go = "Contraoffer_patrol_fight";
			link.l2 = "No tengo otra opción que rendirme. ¡Pero realmente no tenía idea!";
			link.l2.go = "Contraoffer_patrol_jail";
		}
		break;

	case "Contraoffer_patrol_pay1":
		iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
		if (GetSummonSkillFromName(pchar, SKILL_FORTUNE) > hrand(120))
		{
			dialog.text = "Ahora estás hablando... Vamos a ver tus monedas... Creo que he oído un número bastante específico, " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)) + ". Ya que ahora tenemos tres participantes, me gustaría obtener " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm)) + ". Eso es de ti y lo mismo de tu amigo.";
			link.l1 = "Claro, oficial. Aquí están mis monedas relucientes, o, lo siento, tus monedas relucientes. Las acabas de dejar caer en la playa por accidente... Y no hay " + GetGoodsNameAlt(iCGood) + " aquí, ja-ja, como te he dicho.";
			link.l1.go = "Contraoffer_patrol_complete1";
			link.l2 = "¡Caray! Eres demasiado codicioso, oficial. ¿No te enseñó tu madre que la avaricia no es buena? Supongo que me saldría más barato lidiar contigo con mi espada.";
			link.l2.go = "Contraoffer_patrol_fight";
		}
		else
		{
			dialog.text = "¿Está bromeando, capitán? ¿Quiere ofrecerme un soborno? ¡Está arrestado! ¡Captúrenlo!";
			link.l1 = "¡Bueno, si no quieres echar un vistazo a mi dinero, entonces echa un vistazo a mi espada!";
			link.l1.go = "Contraoffer_patrol_fight";
			link.l2 = "No tengo elección, más que rendirme. ¡Pero realmente no tenía idea!";
			link.l2.go = "Contraoffer_patrol_jail";
		}
		break;

	case "Contraoffer_patrol_complete1":
		dialog.text = "Sí, parece que tienes razón... Nada de interés aquí excepto varios caballeros y mis monedas brillantes. Eres libre de ir, capitán, y hablaremos con tu socio.";
		link.l1 = "Nos vemos, oficial. No le hagas daño.";
		link.l1.go = "Contraoffer_patrol_complete";
		break;

	case "Contraoffer_patrol_pay2":
		dialog.text = "" + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm)) + ". Agradece mi buen humor.";
		link.l1 = "Gracias, oficial. Realmente no tenía idea... Aquí, estoy listo para pagar mi multa.";
		link.l1.go = "Contraoffer_patrol_complete2";
		link.l2 = "Tengo la impresión de que usted tampoco es tan honesto, oficial. Su multa es demasiado grande. Supongo que ayudaré a esta colonia librándola de su existencia.";
		link.l2.go = "Contraoffer_patrol_fight";
		break;

	case "Contraoffer_patrol_complete2":
		dialog.text = "Bien. Puedes irte ahora. Y te aconsejo que estudies las leyes locales para evitar situaciones como esta en el futuro. Vete ahora, tenemos que lidiar con el segundo participante de este comercio, él estaba al tanto de todo, eso es seguro.";
		link.l1 = "Bueno, en ese caso, buen día para usted, oficial.";
		link.l1.go = "Contraoffer_patrol_complete";
		break;

	case "Contraoffer_patrol_complete":
		AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Contraoffer.Trader.PatrolSumm));
		AddQuestRecord("Contraoffer", "6");
		CloseQuestHeader("Contraoffer");
		LAi_CharacterDisableDialog(npchar);
		DialogExit();
		break;

	case "Contraoffer_patrol_fight":
		AddQuestRecord("Contraoffer", "7");
		CloseQuestHeader("Contraoffer");
		ChangeCharacterNationReputation(pchar, sti(npchar.Nation), -5);
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		LAi_SetWarriorTypeNoGroup(npchar);
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "Contraoffer_patrol_jail":
		dialog.text = "¡El comandante se encargará de ti. Sígueme!";
		link.l1 = "...";
		link.l1.go = "Contraoffer_patrol_jail_exit";
		break;

	case "Contraoffer_patrol_jail_exit":
		GoToPrison(pchar.GenQuest.Contraoffer.Trader.City, sti(pchar.GenQuest.Contraoffer.Trader.Summ), 7);
		DialogExit();
		AddQuestRecord("Contraoffer", "8");
		CloseQuestHeader("Contraoffer");
		pchar.GenQuest.Contraoffer.Jail = "true";
		break;
		//<-- Сомнительное предложение

		// Jason --> ----------------------------------- Неудачливый вор --------------------------------------------
	case "Device_poorman":
		dialog.text = "Buen día. ¿Quieres algo?";
		link.l1 = "Así es, amigo. Supongo que eres a quien busco. ¿Fuiste tú quien ha robado " + pchar.GenQuest.Device.Shipyarder.Type + " del astillero? Todo lleva a ti, así que no discutas.";
		link.l1.go = "Device_poorman_1";
		break;

	case "Device_poorman_1":
		switch (sti(pchar.GenQuest.Device.Shipyarder.Chance3))
		{
		case 0: // выбросил
			if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) != 1)
			{
				dialog.text = "¡Le ruego, mi señor! Sí, he robado esa cosa extraña del astillero. Pero no pude venderla, nadie necesita tal objeto. Así que me deshice de ella. Perdóneme, buen señor, culpe a mi hambre, no a mí... ¡Nunca me atrevería a robar nada de otra manera!";
				link.l1 = "Eso es un problema... Y tampoco te necesito. Necesito encontrar ese " + pchar.GenQuest.Device.Shipyarder.Type + ". Dime ¿dónde lo tiraste?";
				link.l1.go = "Device_poorman_0_1";
			}
			else // просто отдаст
			{
				dialog.text = "¡Te lo ruego, mi señor! Sí, he robado esta cosa extraña del astillero. Pero no logré venderla, nadie necesita tal objeto. Te lo daré. Aquí, tómalo, solo no me hagas daño y no llames a los soldados.";
				link.l1 = "Está bien, puedes vivir, matón. No necesito tu pellejo, necesito ese instrumento. ¡Dámelo inmediatamente y piérdete!";
				link.l1.go = "Device_poorman_0_2";
			}
			break;
		case 1: // упирается, хитрый или храбрый
			dialog.text = "¿Qué quieres decir? ¿Qué es " + pchar.GenQuest.Device.Shipyarder.Type + "? ¡No lo entiendo!";
			link.l1 = "¡Lo obtendré cuando te registre a ti o a tu cadáver! ¡Dámelo ahora!";
			link.l1.go = "Device_poorman_1_1";
			break;
		case 2: // трусливый
			dialog.text = "Oh... ¿Qué es " + pchar.GenQuest.Device.Shipyarder.Type + "? Oye... ¡¡¿QUÉ ES ESO?!!";
			link.l1 = "No intentes hacerte el tonto o escapar, te atraparé de todos modos. Déjame revisar tus bolsillos...";
			link.l1.go = "Device_poorman_2_1";
			break;
		}
		break;

	case "Device_poorman_0_1": // идем на поиски
		dialog.text = "Justo detrás de las puertas de la ciudad, no muy lejos de las selvas. ¡Le ruego, buen señor! Si realmente necesita esa cosa, puede recogerla usted mismo. Todavía debe estar por allí, estoy seguro.";
		link.l1 = "Debería obligarte a encontrarlo y traérmelo, pero temo que pasaría más tiempo buscándote que el " + pchar.GenQuest.Device.Shipyarder.Type + " Yo lo haré yo mismo. ¡Pero te encontraré si me mentiste!";
		link.l1.go = "exit";
		AddQuestRecord("Device", "3");
		string sCity = pchar.GenQuest.Device.Shipyarder.City + "_ExitTown";
		ref rItm = ItemsFromID("Tool");
		rItm.shown = true;
		rItm.startLocation = sCity;
		rItm.startLocator = "item" + (rand(14) + 1);
		Log_TestInfo("El dispositivo está en el localizador " + rItm.startLocator);
		npchar.lifeday = 0;
		LAi_CharacterDisableDialog(npchar);
		break;

	case "Device_poorman_0_2": // получили девайс
		dialog.text = "Aquí, tómalo. ¡Gracias, buen señor!";
		link.l1 = "Bueno, debe ser lo que estaba buscando... ¡ja! Ahora eres libre de irte. Muévete. Y ten cuidado la próxima vez.";
		link.l1.go = "exit";
		TakeNItems(pchar, "Tool", 1);
		Log_Info("Has recibido el instrumento robado");
		PlaySound("interface\important_item.wav");
		AddQuestRecord("Device", "4");
		npchar.lifeday = 0;
		LAi_CharacterDisableDialog(npchar);
		break;

	case "Device_poorman_1_1":
		pchar.GenQuest.Device.Shipyarder.Poorsumm = 1000 + hrand(1000);
		dialog.text = "Escucha, ¿estás hablando de este instrumento? ¡Pertenece a mí y no lo he robado! Y no te lo voy a dar gratis. Si lo quieres, págame " + FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Poorsumm)) + ".";
		if (sti(pchar.money) >= sti(pchar.GenQuest.Device.Shipyarder.Poorsumm))
		{
			link.l1 = "Mm... Está bien. Te pagaré. ¡Aquí están tus monedas y dame el instrumento!";
			link.l1.go = "Device_poorman_1_2";
		}
		link.l2 = "Oh, ¿de veras? ¿Realmente pensaste que confiaría en ti, miserable ladrón? Da el " + pchar.GenQuest.Device.Shipyarder.Type + " a mí ahora o llamaré a los guardias, así podremos ir juntos al astillero y decidir de quién es realmente este instrumento.";
		link.l2.go = "Device_poorman_1_3";
		link.l3 = "¿Eres estúpido o qué? Escucha, bastardo, tienes dos opciones: o me das la " + pchar.GenQuest.Device.Shipyarder.Type + " o te apuñalo y tomo el instrumento de tu cadáver muerto!";
		link.l3.go = "Device_poorman_1_4";
		break;

	case "Device_poorman_1_2":
		dialog.text = "¡Buen trato, capitán! Supongo que todos obtendremos nuestras ganancias, je-je... tómalo.";
		link.l1 = "¡Menos charla, ladrón! No pienses que me has engañado, solo quiero hacerlo pacíficamente y con menos problemas. Estas monedas no te traerán nada bueno de todos modos. ¡Lárgate!";
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Device.Shipyarder.Poorsumm));
		TakeNItems(pchar, "Tool", 1);
		Log_Info("Has recibido el instrumento robado");
		PlaySound("interface\important_item.wav");
		AddQuestRecord("Device", "5");
		AddQuestUserData("Device", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Poorsumm)));
		AddQuestUserData("Device", "sName", pchar.GenQuest.Device.Shipyarder.Type);
		npchar.lifeday = 0;
		LAi_CharacterDisableDialog(npchar);
		break;

	case "Device_poorman_1_3":
		if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) == 0) // если мы в городе
		{
			dialog.text = "¡No! ¡No llames a los guardias! Yo...yo te daré este maldito instrumento. ¡Aquí, tómalo!";
			link.l1 = "¡Eso es mucho mejor ahora! ¡Lárgate ya! O acabarás colgado en la horca, es solo cuestión de tiempo.";
			link.l1.go = "exit_device";
		}
		else // храбрый попался
		{
			dialog.text = "¿Qué guardias, capi? Sólo estamos tú y yo aquí. Discutes demasiado, así que tendré que calmarte... con mi espada.";
			link.l1 = "¿Te atreves a amenazarme, escoria?!";
			link.l1.go = "Device_poorman_fight";
		}
		break;

	case "Device_poorman_1_4":
		if (sti(pchar.GenQuest.Device.Shipyarder.Chance2) == 0) // если мы в городе
		{
			dialog.text = "¡Ah! ¡Ayúdame! ¡Asesino!";
			link.l1 = "¡Detente ahí mismo, perro!";
			link.l1.go = "exit";
			sld = characterFromId("Device_poorman");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			sld.lifeday = 0;
			AddQuestRecord("Device", "7");
			CloseQuestHeader("Device");
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		}
		else // храбрый попался
		{
			dialog.text = "Bueno, ¡veamos quién apuñalará a quién, capitán!";
			link.l1 = "¿Te atreves a amenazarme, escoria?";
			link.l1.go = "Device_poorman_fight";
		}
		break;

	case "Device_poorman_2_1":
		dialog.text = "¿Buscando? ¡Por favor, buen señor!";
		link.l1 = "Ahora escucha, o me entregas pacíficamente lo que acabas de robar del astillero o te llevaré a la oficina del comandante. Me darás eso de todos modos, pero primero tus talones serán quemados con un hierro al rojo vivo. Quizás incluso te cuelguen después de eso. La elección es tuya.";
		link.l1.go = "Device_poorman_2_2";
		link.l2 = "Dame lo que has robado inmediatamente, bastardo, ¡o te mataré justo donde estás!";
		link.l2.go = "Device_poorman_2_3";
		break;

	case "Device_poorman_2_2":
		if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) < 2) // тут уж как повезёт
		{
			dialog.text = "Bueno, tendrás que atraparme primero si quieres llevarme a la oficina del comandante ...";
			link.l1 = "¡Detente ahí, perro!";
			link.l1.go = "exit";
			AddQuestRecord("Device", "7");
			sld = characterFromId("Device_poorman");
			LAi_SetActorType(sld);
			LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
			sld.lifeday = 0;
			CloseQuestHeader("Device");
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		}
		else
		{
			dialog.text = "¡No, no me lleves a la oficina del comandante! ¡Lo daré yo mismo! Aquí, tómalo, seguro que estás buscando esta cosa. De todos modos, nadie la compraría...";
			link.l1 = "Eh, supongo que podría llevarte al fuerte de todas formas... Está bien, dame la herramienta y ¡fuera de aquí!";
			link.l1.go = "exit_device";
		}
		break;

	case "Device_poorman_2_3": // напугали
		dialog.text = "¡Ay! ¡No me hagas daño, te daré todo lo que tengo! ¡Aquí, tómalo!";
		link.l1 = "¡Ahora estás hablando! Piérdete, te entregaré al comandante si te vuelvo a ver en esta ciudad. ¡Adiós!";
		link.l1.go = "exit_device";
		break;

	case "exit_device":
		npchar.lifeday = 0;
		TakeNItems(pchar, "Tool", 1);
		Log_Info("Has recibido el instrumento robado");
		PlaySound("interface\important_item.wav");
		AddQuestRecord("Device", "6");
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		break;

	case "Device_poorman_fight":
		chrDisableReloadToLocation = true;
		sld = characterFromId("Device_poorman");
		TakeNItems(sld, "Tool", 1);
		sld.SaveItemsForDead = true; // сохранять на трупе вещи
		sld.DontClearDead = true;	 // не убирать труп через 200с
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		AddQuestRecord("Device", "8");
		AddComplexSelfExpToScill(30, 30, 30, 50);
		break;
		//<-- Неудачливый вор
		//-------------------------------------------почтовый генератор 2 уровня------------------------------------
	case "PostGopHunters":
		dialog.text = "¡Detente ahí mismo, amigo! Necesitamos algo que llevas contigo. Dánoslo y luego sigue tu camino.";
		link.l1 = "¿De qué cosa estás hablando?";
		link.l1.go = "PostGopHunters_1";
		link.l2 = "Estos callejeros son demasiado insolentes hoy en día... ¡Prepárense, sinvergüenzas!";
		link.l2.go = "PostHunters_fight";
		break;

	case "PostGopHunters_1":
		dialog.text = "¡No te hagas el tonto! Danos el paquete y vivirás. De lo contrario... ¡lo tomaremos de tu cadáver!";
		link.l1 = "Las probabilidades están a tu favor... tómalo, bastardos, no tengo otra opción.";
		link.l1.go = "PostGopHunters_2";
		link.l2 = "¡Bueno, puedes intentarlo!";
		link.l2.go = "PostHunters_fight";
		break;

	case "PostGopHunters_2":
		dialog.text = "Cuida tu lengua, amigo... Es astuto de tu parte no desafiar tu suerte. ¡El final habría sido el mismo, ja, ja! Vivirás por un tiempo... Nos vemos.";
		link.l1 = "...";
		link.l1.go = "exit_gophunter";
		break;

	case "PostProfHunters":
		dialog.text = "Espera, " + GetAddress_Form(NPChar) + ",  no te apresures así. Tengo un negocio para ti.";
		link.l1 = "¿Qué negocio? No te conozco.";
		link.l1.go = "PostProfHunters_1";
		break;

	case "PostProfHunters_1":
		dialog.text = "Te conozco, capitán. Ahora directo al grano. Acabas de recibir " + pchar.questTemp.WPU.Current.Add + " en " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.City + "Gen") + ". No trates de negarlo, lo sabemos con certeza. Después de todo, hemos estado buscando este documento durante unos días.";
		link.l1 = "Ahora veo. ¿Y qué?";
		link.l1.go = "PostProfHunters_2";
		break;

	case "PostProfHunters_2":
		dialog.text = "Dame el paquete y nuestra breve reunión terminará. No intentes hacerte el héroe, capitán, tenemos la intención de obtener estos papeles y estamos listos para luchar contra la guarnición de la ciudad si es necesario\nComo podrás entender, morirás primero si comienza la escaramuza. Así que danos los documentos y nos separaremos como amigos.";
		link.l1 = "Las probabilidades están a vuestro favor... tomadlo, bastardos, no tengo otra opción.";
		link.l1.go = "PostProfHunters_3";
		link.l2 = "¿Intentas asustarme? ¡He visto peces pequeños que pelean más que tú jamás podrías! Lárgate.";
		link.l2.go = "PostProfHunters_4";
		break;

	case "PostProfHunters_3":
		dialog.text = "Me alegra que hayas sido razonable, capitán. Te has puesto en un gran peligro al aceptar este trabajo. Ahora me voy a retirar, si no te importa.";
		link.l1 = "...";
		link.l1.go = "exit_profhunter";
		break;

	case "PostProfHunters_4":
		dialog.text = "Fue tu decisión...";
		link.l1 = "...";
		link.l1.go = "PostHunters_fight";
		TraderHunterOnMap(false); // если деремся - запускаем ДУ вдогонку
		break;

	case "PostHunters_fight":
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "exit_gophunter":
		chrDisableReloadToLocation = false;
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
		for (i = 1; i <= 4; i++)
		{
			sld = characterFromId("PostHunters" + i);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
		}
		AddQuestRecord("Postcureer", "11");
		AddQuestUserData("Postcureer", "sSex", GetSexPhrase("", ""));
		DialogExit();
		break;

	case "exit_profhunter":
		chrDisableReloadToLocation = false;
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
		for (i = 1; i <= 2; i++)
		{
			sld = characterFromId("PostHunters" + i);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
		}
		AddQuestRecord("Postcureer", "12");
		AddQuestUserData("Postcureer", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("", ""));
		pchar.questTemp.WPU.Postcureer.fail = "true";
		DialogExit();
		break;

	case "PostAgent":
		bDisableFastReload = true;
		dialog.text = "Espera, " + GetAddress_Form(NPChar) + ", no te apresures así. Tengo un negocio para ti.";
		link.l1 = "¿Qué asunto? Habla rápido, tengo prisa.";
		link.l1.go = "PostAgent_1";
		break;

	case "PostAgent_1":
		dialog.text = "Yo sé quién eres. Y también sé que acabas de recibir un " + pchar.questTemp.WPU.Current.Add + " " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.City + "Gen") + "Estos papeles son la razón por la que estoy tan ansioso por hablar contigo.";
		link.l1 = "Y no quiero discutir este asunto con personas que no conozco. ¿Quieres obtener esos papeles? Solo dame una razón...";
		link.l1.go = "PostAgent_2";
		break;

	case "PostAgent_2":
		dialog.text = "¡Basta, capitán! ¿Acaso parezco un ladrón? Soy un hombre de negocios y represento los intereses de " + NationNameGenitive(sti(pchar.questTemp.WPU.Postcureer.EnemyNation)) + " Quiero ofrecerte un trato muy rentable, pero no aquí. Vamos a la habitación de la taberna y discutamos este asunto. No te tomará mucho tiempo.";
		link.l1 = "Eso es demasiado sospechoso... ¡No voy a hacer negocios contigo, señor! ¡Piérdete!";
		link.l1.go = "PostAgent_getout";
		link.l2 = "Hm.. Veamos qué puedes ofrecerme. Pero ni se te ocurra atacarme, no terminará bien. Vamos, te seguiré.";
		link.l2.go = "PostAgent_3";
		break;

	case "PostAgent_getout":
		dialog.text = "¡Eres un hombre terco y necio, capitán! Te he ofrecido una oportunidad de ganar dinero fácil. Y tú... lo lamentarás.";
		link.l1 = "¡Lárgate!";
		link.l1.go = "PostAgent_getout_exit";
		break;

	case "PostAgent_3":
		dialog.text = "¡Espléndido! Sígueme.";
		link.l1 = "...";
		link.l1.go = "exit";
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		NextDiag.TempNode = "PostAgent_inTavern";
		sld = characterFromId("PostAgent");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload4_back", pchar.questTemp.WPU.Postcureer.StartCity + "_tavern_upstairs", "goto", "goto1", "PostAgent_inTavern_Room", -1);
		break;

	case "PostAgent_getout_exit":
		bDisableFastReload = false;
		chrDisableReloadToLocation = false;
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		sld = characterFromId("PostAgent");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10);
		pchar.questTemp.WPU.Postcureer.AgentIslandID = GetCharacterCurrentIslandId(pchar);
		pchar.quest.Postcureer_Hunter.win_condition.l1 = "Location";
		pchar.quest.Postcureer_Hunter.win_condition.l1.location = pchar.questTemp.WPU.Postcureer.AgentIslandID;
		pchar.quest.Postcureer_Hunter.function = "PostcureerAgent_ShipAttack";
		AddQuestRecord("Postcureer", "13");
		AddQuestUserData("Postcureer", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("Postcureer", "sSex1", GetSexPhrase("", ""));
		DialogExit();
		break;

	case "PostAgent_inTavern":
		dialog.text = "Ahora podemos hablar libremente.";
		link.l1 = "¿Y cuál es tu propuesta?";
		link.l1.go = "PostAgent_inTavern_1";
		break;

	case "PostAgent_inTavern_1":
		dialog.text = "Como dije, esto tiene que ver con los documentos que has recibido en la oficina del puerto. Todo lo que necesito es una copia de ellos, eso es todo.\nTú te quedarás con el original, así que te pagarán por el trabajo. Nadie jamás sabrá lo que ocurrió, además te pagaré bien.";
		link.l1 = "Disculpe... Pero el paquete está sellado. ¡No podrá hacer copias sin romper un sello!";
		link.l1.go = "PostAgent_inTavern_2";
		break;

	case "PostAgent_inTavern_2":
		dialog.text = "Esperaba esta pregunta. Tendré que romper el sello, pero no te preocupes, podré restaurarlo. Tengo un cliché duplicado y lacre, por supuesto. Nadie notará que el paquete fue abierto.";
		link.l1 = "¿Tienes un cliché falso sobre la administración del puerto de " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.StartCity + "Gen") + "?";
		link.l1.go = "PostAgent_inTavern_3";
		break;

	case "PostAgent_inTavern_3":
		pchar.questTemp.WPU.Postcureer.AgentMoney = sti(pchar.rank) * 3500;
		dialog.text = "¿Por qué preguntas, capitán? Sí, tengo uno. ¿De verdad crees que solo estoy jugando? Te estoy ofreciendo " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney)) + " por una posibilidad de ver estos papeles. Entonces, ¿me darás el paquete al fin? Por favor.";
		link.l1 = "¡Tómalo, pero necesito que me los devuelvas y sellados!";
		link.l1.go = "PostAgent_inTavern_4";
		link.l2 = "No lo haré, sabes. No me gusta.";
		link.l2.go = "PostAgent_inTavern_getout";
		break;

	case "PostAgent_inTavern_4":
		dialog.text = "No te preocupes. Soy un profesional. Siéntate y descansa. Tomará alrededor de una hora.";
		link.l1 = "Bien.";
		link.l1.go = "PostAgent_inTavern_5";
		break;

	case "PostAgent_inTavern_5":
		NextDiag.currentnode = "PostAgent_inTavern_6";
		RemoveItems(PChar, pchar.questTemp.WPU.Current.Item, 1);
		pchar.questTemp.WPU.Postcureer.AgentChance = hrand(4); // шанс, что раскроют обман - 20%
		DialogExit();
		AddDialogExitQuest("PostAgent_inTavern_Room_end");
		break;

	case "PostAgent_inTavern_getout":
		dialog.text = "Hm... No vi venir esto. Eres demasiado terco, capitán, así que tendré que matarte justo donde estás y tomar el paquete gratis. Ruega, porque trabajo con mi espada tan bien como con falsos clichés.";
		link.l1 = "¡Eres tú quien debería rezar, espía!";
		link.l1.go = "PostAgent_inTavern_fight";
		break;

	case "PostAgent_inTavern_6":
		dialog.text = "Listo. Como dije, se ha hecho de la manera más precisa. Toma el paquete y lo prometido " + FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney)) + ". Y tengo que irme. Buena suerte, capitán, me alegra que hayamos hecho un trato.";
		link.l1 = "Adiós...";
		link.l1.go = "PostAgent_inTavern_7";
		break;

	case "PostAgent_inTavern_7":
		DialogExit();
		bDisableFastReload = false;
		chrDisableReloadToLocation = false;
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.WPU.Postcureer.AgentMoney));
		GiveItem2Character(pchar, pchar.questTemp.WPU.Current.Item);
		sld = characterFromID("PostAgent");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 2);
		AddQuestRecord("Postcureer", "15");
		AddQuestUserData("Postcureer", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("Postcureer", "sMoney", FindRussianMoneyString(sti(pchar.questTemp.WPU.Postcureer.AgentMoney)));
		break;

	case "PostAgent_inTavern_fight":
		bDisableFastReload = false;
		sld = characterFromID("PostAgent");
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		AddQuestRecord("Postcureer", "16");
		break;
		//<-- почтовый генератор 2 уровня

		// --> --------------------------------- эскорт 2 уровень --------------------------------------------------
	case "DisasterCap":
		dialog.text = "¡Saludos! ¡Oh, estoy tan contento de verte!";
		link.l1 = "Buen día. Hm, dime, ¿no estás al mando del " + pchar.questTemp.WPU.Escort.ShipName + "?";
		link.l1.go = "DisasterCap_1";
		break;

	case "DisasterCap_1":
		dialog.text = "¡Oh! ¿Y cómo te enteraste del " + pchar.questTemp.WPU.Escort.ShipName + "? Sí, soy su capitán. O lo era... El barco se hundió no muy lejos de aquí.";
		link.l1 = "Ah, entonces te he encontrado... Permíteme presentarme, " + GetFullName(pchar) + ". Estoy aquí por el pedido del maestro del puerto de " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Escort.StartCity + "Gen") + ".  Me habló brevemente sobre los problemas de tu caravana y me envió a buscar tu barco.";
		link.l1.go = "DisasterCap_2";
		break;

	case "DisasterCap_2":
		dialog.text = "¿Entonces eres un capitán del grupo de rescate?";
		link.l1 = "Algo así. Mi tarea era encontrar tu barco o pruebas de que se hundió o de que es incapaz de navegar. Desafortunadamente, no he encontrado el barco, pero su capitán está vivo, eso es algo bueno, sin duda...";
		link.l1.go = "DisasterCap_3";
		break;

	case "DisasterCap_3":
		dialog.text = "Oh, lo siento, olvidé presentarme. Soy " + GetFullName(npchar) + ". ¿Ya sabes cómo terminamos aquí? La tormenta hizo que nuestro barco fuera incontrolable.\nUnos días después, chocó contra los arrecifes no lejos de esta bahía y el vendaval la destruyó en minutos. Solo unas pocas docenas de mi tripulación sobrevivieron. El resto yace en el fondo. Rezamos por sus almas todos los días...";
		link.l1 = "Acepte mis condolencias, capitán " + GetFullName(npchar) + " . Lo siento mucho.";
		link.l1.go = "DisasterCap_4";
		break;

	case "DisasterCap_4":
		dialog.text = "Gracias... Los sobrevivientes han montado un campamento en la orilla, esperando recibir ayuda. ¡Llegas justo a tiempo, capitán! Los indios locales, que son belicosos, están al tanto de nuestra presencia, no tendremos ninguna oportunidad contra cientos de ellos si nos atacan\nTambién hay un barco pirata, navegando por esta área, parece que nos están buscando. ¿Te has encontrado con este pirata, capitán?";
		link.l1 = "No, no lo he hecho.";
		link.l1.go = "DisasterCap_5";
		break;

	case "DisasterCap_5":
		dialog.text = "Alabado sea el Señor por eso. Es uno de los que nos atacaron antes de esa maldita tormenta. Como una hiena, está ansioso por terminar una presa herida, así que ha llegado aquí, a esta isla.";
		link.l1 = "Ya veo. Ahora es el momento de decidir qué haremos a continuación.";
		link.l1.go = "DisasterCap_6";
		break;

	case "DisasterCap_6":
		dialog.text = "¿Decidir qué, capitán? Llévanos a bordo y alejémonos de este lugar maldito.";
		link.l1 = "Absolutamente. He fallado en salvar el barco, al menos salvaré a su tripulación. Recoge tu campamento y ordenaré enviar botes aquí. ¡Bienvenido a bordo!";
		link.l1.go = "DisasterCap_7";
		break;

	case "DisasterCap_7":
		PlaySound("people fight\rifle_fire1.wav");
		PlaySound("people fight\player_man_shoot_01.wav");
		dialog.text = "¡Gratitud, capitán! No tardará mucho. Espera... ¿Qué diablos? ¡Argh! ¡Esos demonios de piel roja vienen por nosotros otra vez! ¡Alarma! ¡A las armas!";
		link.l1 = "... ";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("DisasterShipCrew_IndianAttack");
		break;

	case "DisasterCap_8":
		dialog.text = "Fuh, lo hemos logrado... Mira, capitán, te dije que esta bahía es el mismo infierno. ¡Ya es el tercer ataque de los indios! Tenemos que dejar este lugar lo antes posible, no sobreviviremos otro ataque.";
		link.l1 = "Sí, tienes razón. ¡Reúne a cada alma viviente y sube a mi barco! ¡Ordenaré que nos envíen botes de inmediato!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("DisasterShipCrew_onBoard");
		AddQuestRecord("Escort", "38");
		AddQuestUserData("Escort", "sIsland", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID));
		AddQuestUserData("Escort", "sSName", pchar.questTemp.WPU.Escort.ShipName);
		AddQuestUserData("Escort", "sShore", XI_ConvertString(pchar.questTemp.WPU.Current.TargetIslandID.Shore));
		break;
		// <-- эскорт 2 уровень

		// Jason --> -------------------------- Заносчивый аристократ ------------------------------------------------
	case "Badboy":
		dialog.text = "¡Hic...! ¿Qué quieres de mí? Piérdete, no tengo deseos de hablar contigo.";
		link.l1 = "¿Eres tú " + pchar.GenQuest.Badboy.Brothel.Name + "?";
		link.l1.go = "Badboy_1";
		break;

	case "Badboy_1":
		dialog.text = "Sí, lo soy. ¿Y cuál es tu negocio?";
		link.l1 = "Es bastante simple. Hay alguien en este pueblo que está harto de tus trucos. Esta persona está cansada de ellos. Ahora te miro y veo por qué. No te vuelvas a presentar en el burdel o tendrás problemas. ¿Entendido?";
		link.l1.go = "Badboy_2";
		break;

	case "Badboy_2":
		switch (sti(pchar.GenQuest.Badboy.Brothel.Type))
		{
		case 0: // или напугается, или будет быковать - от авторитета
			if (GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) < 30)
			{
				dialog.text = "¡Argh! ¿Tú... te atreves a amenazarme, imbécil? ¡Te ensartaré en mi hoja y te cocinaré como un pollo en el asador!";
				link.l1 = "¡Prepárate, cabrón!";
				link.l1.go = "Badboy_fight_1";
				NextDiag.currentnode = "Badboy_after_fight";
			}
			else
			{
				dialog.text = "¿Qué? ¿Qué trucos? No hubo ningún truco. Me emborraché y tuve unas juergas en el burdel. Nadie es perfecto... Está bien, está bien, está bien... Nunca más usaré sus servicios. ¿Contento ahora? Tienes mi palabra.";
				link.l1 = "Espero que la palabra de honor signifique algo para ti y seas consciente de las consecuencias en caso de romperla. Tenlo en cuenta. Adiós por ahora.";
				link.l1.go = "exit";
				pchar.GenQuest.Badboy.Complete = "true";
				LAi_CharacterDisableDialog(npchar);
				npchar.lifeday = 0;
			}
			break;
		case 1: // дуэль за городом
			dialog.text = "¡Eres un hombre tan insolente, señor! Juro que haré que te arrepientas de tus palabras antes del atardecer. ¡Te desafío! Supongo que sería mejor luchar en privado, en algún lugar tranquilo. La jungla estará bien, encuéntrame allí en dos horas.";
			link.l1 = "¡Una gran idea! Al menos no sería un problema esconder tu cadáver.";
			link.l1.go = "Badboy_duel";
			NextDiag.currentnode = "Badboy_duel_1";
			break;
		case 2: // призовет на помощь дружков
			dialog.text = "¿Qué? ¿Qué trucos? No hubo ningún truco. Me emborraché y tuve una juerga unas cuantas veces en el burdel. Nadie es perfecto... Está bien, está bien, está bien... Nunca más utilizaré sus servicios. ¿Satisfecho ahora? Tienes mi palabra.";
			link.l1 = "Espero que la palabra de honor signifique algo para ti y seas consciente de las consecuencias en caso de romperla. Tenlo presente. Adiós por ahora.";
			link.l1.go = "exit_continue";
			pchar.GenQuest.Badboy.Continue = "true";
			NextDiag.currentnode = "Badboy_friends";
			break;
		}
		break;

	case "Badboy_fight_1":
		chrDisableReloadToLocation = true;
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		sld = characterFromId("Badboy");
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		AddDialogExitQuest("MainHeroFightModeOn");
		LAi_SetCheckMinHP(npchar, 10.0, true, "Badboy_capture");
		DialogExit();
		break;

	case "Badboy_after_fight":
		dialog.text = "¡Espera! ¡Detente! ¡Me rindo! ¡Perdóname!";
		link.l1 = "¡Y así es como estás hablando ahora!";
		link.l1.go = "Badboy_after_fight_1";
		break;

	case "Badboy_after_fight_1":
		dialog.text = "¡Te lo suplico, por favor, perdóname! ¡Haré lo que me pidas! ¡Nunca volveré a aparecer en ese burdel!";
		link.l1 = "Esa pose solo le queda a un canalla como tú. Espero que esto sea una lección para ti por el resto de tu vida. Y compórtate adecuadamente en esta ciudad.";
		link.l1.go = "Badboy_exit";
		link.l2 = "Seguro, no lo harás. Tu engaño terminará aquí y ahora.";
		link.l2.go = "Badboy_killed";
		pchar.GenQuest.Badboy.Complete = "true";
		break;

	case "Badboy_exit":
		LAi_SetPlayerType(pchar);
		chrDisableReloadToLocation = false;
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], true);
		LAi_SetActorType(npchar);
		npchar.lifeday = 0;
		LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		DialogExit();
		break;

	case "Badboy_killed":
		DialogExit();
		LAi_SetImmortal(npchar, false);
		//  belamour legendary edition если не надет пистоль или мушкет, то выдадим строевой -->
		if (!CheckAttribute(pchar, "equip." + GUN_ITEM_TYPE) || !CheckAttribute(pchar, "equip." + MUSKET_ITEM_TYPE))
		{
			GiveItem2Character(pchar, "pistol1");
			EquipCharacterbyItem(pchar, "pistol1");
		}
		// <-- legendary edition
		LAi_ActorAnimation(pchar, "shot", "Badboy_killed_end", 2.2);
		break;

	case "Badboy_duel":
		chrDisableReloadToLocation = true;																	// закрыть локацию
		LAi_LocationDisableOfficersGen(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown", true);				// офицеров не пускать
		locations[FindLocation(pchar.GenQuest.Badboy.Brothel.City + "_ExitTown")].DisableEncounters = true; // энкаутеры закроем
		pchar.quest.BadboyDuelTimer.win_condition.l1 = "Timer";
		pchar.quest.BadboyDuelTimer.win_condition.l1.date.hour = sti(GetTime() + 2);
		pchar.quest.BadboyDuelTimer.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
		pchar.quest.BadboyDuelTimer.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
		pchar.quest.BadboyDuelTimer.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
		pchar.quest.BadboyDuelTimer.function = "Badboy_duelstart";
		sld = characterFromId("Badboy");
		LAi_SetActorType(sld);
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
		LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
		TakeNItems(sld, "jewelry5", rand(10));
		TakeNItems(sld, "jewelry3", rand(10));
		TakeNItems(sld, "jewelry1", rand(10));
		sld.money = 24560;
		sld.SaveItemsForDead = true; // сохранять на трупе вещи
		sld.DontClearDead = true;	 // не убирать труп через 200с
		LAi_RemoveLoginTime(sld);	 // удалить время логина
		SetFunctionTimerCondition("Badboy_duelOver", 0, 0, 1, false);
		DialogExit();
		break;

	case "Badboy_duel_1":
		dialog.text = "¡Hora de ir al infierno, cabrón! Reza por ti mismo, pero hazlo rápido, no tengo todo el maldito día...";
		link.l1 = "¡Menos charla, más pelea, escoria!";
		link.l1.go = "Badboy_duel_2";
		break;

	case "Badboy_duel_2":
		chrDisableReloadToLocation = true;
		LAi_SetPlayerType(pchar);
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		LAi_group_SetCheck("EnemyFight", "Badboy_die");
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "exit_continue":
		sld = characterFromID("Badboy");
		LAi_RemoveLoginTime(sld); // patch-6
		LAi_SetActorType(sld);
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
		LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", -1);
		DialogExit();
		break;

	case "Badboy_friends":
		dialog.text = "¡Y ahí está, ese bastardo insolente! ¡Mostremos quién es el dueño de este pueblo, muchachos!";
		link.l1 = "¡Ah, eres un degenerado! Pero te lo he advertido. ¡Tú y tus monos seréis enviados al infierno en un minuto!";
		link.l1.go = "Badboy_friends_fight";
		break;

	case "Badboy_friends_fight":
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "OpenTheDoors");
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		DeleteAttribute(pchar, "GenQuest.Badboy");
		break;
		// Jason <-- Заносчивый аристократ

		// Jason --> ------------------------------- Место под солнцем ----------------------------------------------
	case "Sunplace_Store":
		pchar.quest.SunplaceContinue_Over.over = "yes";
		dialog.text = "Saludos. ¿Qué quieres?";
		link.l1 = "¿No eres tú " + pchar.GenQuest.Sunplace.Trader.Enemyname + "? No me creerás, ja-ja. Quiero tu cabeza...";
		link.l1.go = "Sunplace_Store_1";
		link.l2 = "Mm... No... No es nada. Parece que me equivoqué. Disculpa por molestarte.";
		link.l2.go = "Sunplace_Store_exit";
		break;

	case "Sunplace_Store_1":
		dialog.text = "¡Qué broma tan tonta, señor! Explíquese o yo...";
		link.l1 = "¿Y qué vas a hacer, miserable arenque? Le has hecho una mala jugada a un buen hombre y está realmente molesto. Así que reza ahora y hazlo rápido porque tengo prisa.";
		link.l1.go = "Sunplace_Store_3";
		break;

	case "Sunplace_Store_3":
		dialog.text = "¡Qué... qué está haciendo, señor! ¡Ayuda! ¡Alguien ayude! ¡Asesino!";
		link.l1 = "Y pensé que pasarías tus últimos segundos rezando, al menos habrías tenido una oportunidad de alcanzar el cielo...";
		link.l1.go = "Sunplace_Store_fight";
		break;

	case "Sunplace_Store_exit":
		sld = CharacterFromID("SunplaceTrader");
		sld.lifeday = 0;
		AddQuestRecord("Sunplace", "9");
		CloseQuestHeader("Sunplace");
		DialogExit();
		DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
		NextDiag.currentnode = "Sunplace_Store_repeat";
		break;

	case "Sunplace_Store_repeat":
		dialog.text = "¿Tú otra vez? ¿Por qué no me dices qué es lo que quieres?";
		link.l1 = "Es nada.";
		link.l1.go = "exit";
		break;

	case "Sunplace_Store_fight":
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		sld = CharacterFromID("SunplaceTrader");
		LAi_SetImmortal(sld, false);
		LAi_SetActorType(sld);
		LAi_ActorAfraid(sld, Pchar, true);
		sld = characterFromId(pchar.GenQuest.Sunplace.Trader.CityT + "_trader");
		LAi_group_Attack(sld, Pchar);
		pchar.quest.Kill_SunplaceTrader.win_condition.l1 = "ExitFromLocation";
		pchar.quest.Kill_SunplaceTrader.win_condition.l1.location = pchar.location;
		pchar.quest.Kill_SunplaceTrader.function = "Kill_SunplaceTrader";
		break;
		// <-- место под солнцем

		//------------------------------------- киллеры Лиги-------------------------------------------------------
	case "LigaHunters":
		dialog.text = "";
		link.l1 = "¿Ah?! ¿Qué? ¿Qué diablos haces aquí, maldito seas? ¿Quién te ha dejado entrar?";
		link.l1.go = "LigaHunters_1";
		break;

	case "LigaHunters_1":
		dialog.text = "La liga necesita tu vida, capitán...";
		link.l1 = "¿Qué? ¡Mierda!";
		link.l1.go = "LigaHunters_2";
		break;

	case "LigaHunters_2":
		DialogExit();
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		for (i = 1; i <= 2; i++)
		{
			sld = characterFromId("LigaHunter_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "LigaHunters_Dead");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;
		// <-- киллеры Лиги

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	// замечание по обнажённому оружию от персонажей типа citizen
	case "CitizenNotBlade":
		if (loadedLocation.type == "town")
		{
			dialog.text = NPCharSexPhrase(NPChar, "Escucha, soy ciudadano de esta ciudad y te pediría que envaines tu espada.", "Escucha, soy ciudadano de este pueblo y te pediría que envaines tu espada.");
			link.l1 = LinkRandPhrase("Bien.", "Bien.", "Claro...");
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = NPCharSexPhrase(NPChar, "Ten cuidado, " + GetSexPhrase("compinche", "chica") + ", mientras corro con un arma. Puedo ponerme nervioso...", "No me gusta cuando hay " + GetSexPhrase("hombres que", "gente que") + " están caminando delante de mí con su arma lista. Me asusta...");
			link.l1 = LinkRandPhrase("Lo tengo.", "Está bien.", "No te preocupes...");
		}
		link.l1.go = "exit";
		NextDiag.TempNode = "First Time";
		if (npchar.id == "Device_poorman")
			NextDiag.TempNode = "Device_poorman";
		break;
	}
}
