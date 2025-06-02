void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, Diag;
	int i;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(Diag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "exit":
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		break;
	//----------------- уничтожение банды ----------------------
	case "DestroyGang_begin":
		chrDisableReloadToLocation = false;
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);							 // боевке можно
		DeleteAttribute(&locations[FindLocation(pchar.GenQuest.DestroyGang.Location)], "DisableEncounters"); // энкаунтеры можно
		for (i = 1; i <= 3; i++)
		{
			if (GetCharacterIndex("MayorQuestGang_" + i) == -1)
				continue;
			sld = CharacterFromID("MayorQuestGang_" + i);
			LAi_type_actor_Reset(sld);
			LAi_RemoveCheckMinHP(sld);
		}
		sTemp = GetFullName(&characters[GetCharacterIndex(pchar.GenQuest.DestroyGang.MayorId)]);
		dialog.text = LinkRandPhrase("Dinero en el barril " + GetSexPhrase("camarada", "chica") + "¡Mi nombre es " + GetFullName(npchar) + ", y no estoy acostumbrado a objeciones...", "Ahora muéstrame tu bolsa, " + GetSexPhrase("compañero", "muchacha") + ", ¡y date prisa! Mi nombre es  " + GetFullName(npchar) + ", y espero que hayas oído hablar de mí...", "Entrégame todo lo valioso que tengas, también requiso el contenido de tu bolsa. Y apúrate, la paciencia no es mi fuerte. ¡No puedo decir lo mismo de mi sed de sangre!");
		Link.l1 = LinkRandPhrase("Je, entonces tú eres ese famoso bandido " + GetFullName(npchar) + ", sobre quien el gobernador " + sTemp + "¿nunca deja de hablar?", "Oh, ¿entonces eres ese bandido perseguido por el gobernador " + sTemp + "?", "Contento" + GetSexPhrase("", "") + " verte, " + GetFullName(npchar) + ". El gobernador, " + sTemp + " solo habla de ti.");
		Link.l1.go = "DestroyGang_1";
		break;
	case "DestroyGang_1":
		dialog.text = LinkRandPhrase("Sí, soy bien conocido en estas tierras, je-je... Espera, ¿no eres tú otro " + GetSexPhrase("perro asqueroso", "perra asquerosa") + "¿del gobernador que ha enviado para buscarme?", "El gobernador es mi buen amigo, eso es cierto. ¿Y tú, no serás por casualidad, " + GetSexPhrase("otro héroe, enviado", "otra heroína, enviada") + "¿por él por mi cabeza?", "El gobernador es mi mejor amigo, no es un secreto, je-je. ¿Pero cómo sabes eso? Tal vez, ¿él te envió tras de mí?");
		Link.l1 = LinkRandPhrase("Exactamente, malandrín. ¡Prepárate para morir!", "¡Vaya, qué astuto eres! Bueno, es hora de proceder con tu liquidación. Basta de hablar.", "Sí, ese soy yo. ¡Saca tu arma, compañero! Veamos de qué color es tu sangre.");
		Link.l1.go = "DestroyGang_ExitFight";
		Link.l2 = LinkRandPhrase("¡Oh, no importa! No necesito tales problemas en absoluto...", "No, no, no soy un héroe, de ninguna manera...", "No, no, ¡nunca! No necesito problemas...");
		Link.l2.go = "DestroyGang_2";
		break;
	case "DestroyGang_2":
		dialog.text = LinkRandPhrase("Eso es mejor, " + GetSexPhrase("compañero", "chica") + "... ¡Y ahora piérdete!", "Y esa es una decisión acertada. Ojalá supieras cuántos héroes he enviado al otro mundo... Bueno, menos palabras. ¡Piérdete, " + GetSexPhrase("pedazo de mierda", "perra") + "!", "Buen" + GetSexPhrase(" chico", "a chica") + ". Una decisión muy sabia, no interferir en los asuntos de los demás... Bueno, ya lárgate, " + GetSexPhrase("compañero", "chica") + ".");
		Link.l1 = "Adiós y buena suerte para ti...";
		Link.l1.go = "DestroyGang_ExitAfraid";
		break;

	case "DestroyGang_ExitAfraid":
		pchar.GenQuest.DestroyGang = "Found"; // флаг нашёл, но струсил
		npchar.money = AddMoneyToCharacter(npchar, sti(pchar.money));
		pchar.money = 0;
		LAi_SetWarriorType(npchar);
		LAi_SetImmortal(npchar, false);
		LAi_SetCheckMinHP(npchar, LAi_GetCharacterHP(npchar) - 1, false, "DestroyGang_SuddenAttack");
		for (i = 1; i < 4; i++)
		{
			if (GetCharacterIndex("MayorQuestGang_" + i) == -1)
				continue;
			sld = CharacterFromID("MayorQuestGang_" + i);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, npchar, "", -1);
			LAi_SetImmortal(sld, true);
			LAi_SetCheckMinHP(sld, LAi_GetCharacterHP(sld) - 1, false, "DestroyGang_SuddenAttack");
		}
		DialogExit();
		break;

	case "DestroyGang_ExitFight":
		for (i = 0; i < 4; i++)
		{
			if (GetCharacterIndex("MayorQuestGang_" + i) == -1)
				continue;
			sld = CharacterFromID("MayorQuestGang_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "DestroyGang_Afrer");
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	// ОЗГ - пассажир
	case "ContraPass_abordage":
		dialog.text = "¡Arghh, tú malandrín! ¿Cómo te atreviste a atacar mi barco?! ¡Lo pagarás por eso!";
		link.l1 = "Por el contrario, en realidad me están pagando por ello. Tienes a un hombre a bordo, llamado " + pchar.GenQuest.TakePassenger.Name + ". Él es el que necesito.";
		link.l1.go = "ContraPass_abordage_1";
		break;

	case "ContraPass_abordage_1":
		dialog.text = "¡Sabía que este pillo nos traería problemas... Pero no me capturarás tan fácilmente! ¡Defiéndete, pirata asqueroso!";
		link.l1 = "Es tú quien necesita pensar en defensa, canalla.";
		link.l1.go = "ContraPass_abordage_2";
		break;

	case "ContraPass_abordage_2":
		DialogExit();
		LAi_SetCurHPMax(npchar);
		QuestAboardCabinDialogFree();
		LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck(LAI_GROUP_BRDENEMY, "ContraPass_GivePrisoner");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "Tempsailor":
		dialog.text = "Capitán, hemos registrado las cabinas y la bodega, como usted ordenó. Ese sinvergüenza intentó esconderse, pero lo hemos encontrado.";
		link.l1 = "¡Excelente! ¿Dónde está ahora?";
		link.l1.go = "Tempsailor_1";
		break;

	case "Tempsailor_1":
		dialog.text = "Él está en la bodega, como nos ordenaste.";
		link.l1 = "¡Excelente! Ahora vámonos de este viejo cascarón. Es hora de regresar.";
		link.l1.go = "Tempsailor_2";
		break;

	case "Tempsailor_2":
		dialog.text = "¡Inmediatamente, capitán!";
		link.l1 = "...";
		link.l1.go = "Tempsailor_3";
		break;

	case "Tempsailor_3":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", 10.0);
		sld = GetCharacter(NPC_GenerateCharacter("ContraPass", "citiz_" + (rand(9) + 11), "man", "man", 10, sti(pchar.GenQuest.TakePassenger.Nation), -1, true, "quest"));
		sld.name = pchar.GenQuest.TakePassenger.Name;
		sld.lastname = "";
		pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(sld);
		SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
		Pchar.GenQuest.TakePassenger.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
		break;

	case "Fugitive_city":							   // ходит по городу
		pchar.quest.AllMayorsQuests_Late.over = "yes"; // снимаем общий таймер
		dialog.text = "¿Qué desea, señor?";
		link.l1 = "Bueno-bueno... Así que tú eres " + pchar.GenQuest.FindFugitive.Name + ", ¿no es así? Estoy muy contento de verte...";
		link.l1.go = "Fugitive_city_1";
		break;

	case "Fugitive_city_1":
		dialog.text = "Bueno, ese soy yo, en efecto, aunque ¿por qué te alegra verme? Me parece extraño, ya que nunca te he visto antes... ¿Te importaría explicarte?";
		link.l1 = "Pero por supuesto. Yo vengo de " + XI_ConvertString("Colony" + pchar.GenQuest.FindFugitive.Startcity + "Gen") + ", por órdenes del gobernador. Estás arrestado y debo entregarte a la misma ciudad... Oh, ¡y mantén las manos alejadas de tu sable! No intentes nada estúpido buen hombre, ¡o te irá mal!";
		link.l1.go = "Fugitive_city_2";
		break;

	case "Fugitive_city_2":
		dialog.text = "Entonces, me has encontrado después de todo... Señor, escúchame y, quizás, cambiarás de opinión. Sí, he desertado del destacamento. ¡Pero no podía ver la degradación de nuestro ejército!\nQuería una vida tranquila y encontré tal vida aquí, en este pueblo... Déjame en paz, diles que no has logrado encontrarme o que escapé con piratas al mar abierto. A cambio te daré este saquito de ámbar. Un objeto muy valioso, debo decir...";
		link.l1 = "¡Ni siquiera pienses en sobornarme, señor! ¡Entrega tu arma y sígueme!";
		link.l1.go = "Fugitive_city_fight";
		link.l2 = "¿Hmm ... Degradación? ¿Vida tranquila y pacífica? Bueno, supongo que puedo hacer realidad tu deseo. ¿Dónde está tu ámbar?";
		link.l2.go = "Fugitive_city_gift";
		break;

	case "Fugitive_city_fight":
		dialog.text = "¡Entonces desenvaina tu espada, mercenario! ¡No me atraparás tan fácilmente!";
		link.l1 = "¡Vale, veamos tu valía!";
		link.l1.go = "Fugitive_fight_1";
		break;

	case "Fugitive_city_gift":
		TakeNItems(pchar, "jewelry8", 50 + hrand(25));
		TakeNItems(pchar, "jewelry7", 2 + hrand(5));
		PlaySound("interface\important_item.wav");
		Log_Info("Has recibido ámbar");
		dialog.text = "Aquí... Y espero que nunca vuelva a ver ni a ti ni a otros 'envíados'.";
		link.l1 = "Os aseguro que no lo haréis. ¡Adiós, señor!";
		link.l1.go = "Fugitive_gift_exit";
		break;

	case "Fugitive_gift_exit":
		DialogExit();
		npchar.lifeday = 0;
		LAi_CharacterDisableDialog(npchar);
		pchar.GenQuest.FindFugitive = "Found"; // флаг провалил
		AddQuestRecord("MayorsQuestsList", "12-4");
		AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + pchar.GenQuest.FindFugitive.Startcity));
		break;

	case "Fugitive_fight_1":			   // в городе и бухте
		chrDisableReloadToLocation = true; // закрыть локацию
		DialogExit();
		Diag.currentnode = "Fugitive_afterfight";
		LAi_SetImmortal(npchar, false);
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "Fugitive_afterfight":
		dialog.text = "¡Arrgh! Has ganado, ¡maldita sea! Me rindo...";
		link.l1 = "¡Cuida tu lengua, señor! Y ahora, dame tu sable, por favor... Sígueme, y sin trucos tontos!";
		link.l1.go = "Fugitive_afterfight_1";
		break;

	case "Fugitive_afterfight_1":
		DialogExit();
		RemoveAllCharacterItems(npchar, true);
		LAi_SetActorType(npchar);
		LAi_ActorFollow(npchar, pchar, "", -1);
		// DeleteAttribute(npchar, "LifeDay");
		npchar.lifeday = 0;
		LAi_SetImmortal(npchar, true);
		pchar.GenQuest.LastQuestPrisonerIdx = SetCharToPrisoner(npchar);
		SetCharacterRemovable(&characters[sti(pchar.GenQuest.LastQuestPrisonerIdx)], false);
		Pchar.GenQuest.FindFugitive.PrisonerIDX = sti(pchar.GenQuest.LastQuestPrisonerIdx);
		pchar.GenQuest.FindFugitive = "Execute"; // флаг выполнил успешно
		pchar.quest.FindFugitive1.win_condition.l1 = "location";
		pchar.quest.FindFugitive1.win_condition.l1.location = pchar.GenQuest.FindFugitive.Startcity + "_townhall";
		pchar.quest.FindFugitive1.function = "FindFugitive_inResidence";
		SetFunctionTimerCondition("FindFugitive_Over", 0, 0, 30, false);
		break;

	case "Fugitive_shore":							   // в бухте
		pchar.quest.AllMayorsQuests_Late.over = "yes"; // снимаем общий таймер
		dialog.text = "Señor, no estoy de humor para hablar contigo, así que...";
		link.l1 = "Sin embargo, tendrás que hablar conmigo. Eres " + pchar.GenQuest.FindFugitive.Name + ", ¿no es así? Creo que no deberías negarlo.";
		link.l1.go = "Fugitive_shore_1";
		break;

	case "Fugitive_shore_1":
		dialog.text = "Y no voy a negarlo, ese soy yo. ¿Pero qué quieres?";
		link.l1 = "Necesito llevarte a " + XI_ConvertString("Colony" + pchar.GenQuest.FindFugitive.Startcity) + ", el gobernador se muere por verte. ¡No hagas tonterías, por favor! Ríndete tu arma y sígueme!";
		link.l1.go = "Fugitive_shore_2";
		break;

	case "Fugitive_shore_2":
		dialog.text = "Ya veo... Señor, antes de que dispare sin pensar, permítame decirle algo. Sí, he desertado del cuartel. Pero tenía razones para hacerlo. ¡No puedo seguir en el servicio, es más de lo que puedo soportar! ¿Me entiende? ¡No puedo! \nQuiero una vida tranquila y he encontrado tal vida aquí, en esta aldea... Déjeme en paz, dígales que no ha logrado encontrarme o que he escapado con piratas al mar abierto. A cambio, le daré mi captura semanal de perlas. Eso es todo lo que tengo.";
		link.l1 = "¡Ni siquiera piense en sobornarme, señor! ¡Entregue su arma y sígame!";
		link.l1.go = "Fugitive_city_fight";
		link.l2 = "Hmm... ¿Estás cansado del servicio militar? ¿Quieres una vida tranquila? Bueno, supongo que puedo hacer realidad tu deseo. ¿Dónde están tus perlas?";
		link.l2.go = "Fugitive_shore_gift";
		break;

	case "Fugitive_shore_gift":
		TakeNItems(pchar, "jewelry52", 100 + hrand(40));
		TakeNItems(pchar, "jewelry53", 400 + hrand(100));
		PlaySound("interface\important_item.wav");
		Log_Info("Has recibido perlas");
		dialog.text = "Aquí... Y espero que nunca vuelva a ver ni a ti ni a otros 'envíos' nunca más.";
		link.l1 = "Le aseguro que no lo hará. ¡Adiós, señor!";
		link.l1.go = "Fugitive_gift_exit";
		break;

	case "Fugitive_tavern":							   // в таверне
		pchar.quest.AllMayorsQuests_Late.over = "yes"; // снимаем общий таймер
		dialog.text = "Ehhh... ¡hic! Señor, no estoy buscando compañía, especialmente la tuya. ¡Pierde de vista!";
		link.l1 = "Pero ESTOY buscando tu compañía, " + pchar.GenQuest.FindFugitive.Name + "¡Y tolerarás mi compañía en la bodega de mi barco. Nos vamos a  " + XI_ConvertString("Colony" + pchar.GenQuest.FindFugitive.Startcity) + ", al gobernador del pueblo. Está casi muriendo por verte.";
		link.l1.go = "Fugitive_tavern_1";
		break;

	case "Fugitive_tavern_1":
		dialog.text = "¡H-Hip!" + RandSwear() + "¡Así que finalmente me ha perseguido! Escucha, compadre, no sabes lo que pasó, ¡no estabas allí! No podía quedarme en el servicio, ¡simplemente no podía! Todavía me emborracho todas las noches para olvidar eso\nMira, hagamos un trato. Dile que has fallado en encontrarme o que he escapado con piratas al mar abierto. A cambio te daré todas las pepitas que encontré en la cueva. Eso es todo lo que tengo, ves, te lo doy todo, solo para nunca ver" + XI_ConvertString("Colony" + pchar.GenQuest.FindFugitive.Startcity) + "...";
		link.l1 = "¡Ni siquiera pienses en sobornarme, señor! ¡Entrega tu arma y sígueme!";
		link.l1.go = "Fugitive_tavern_fight";
		link.l2 = "¿Hmm... Una historia desagradable? ¿Estás atormentado por pesadillas o remordimientos de conciencia? Bueno, supongo que puedo dejarte con esto por tu cuenta. ¿Dónde están tus pepitas?";
		link.l2.go = "Fugitive_tavern_gift";
		break;

	case "Fugitive_tavern_gift":
		TakeNItems(pchar, "jewelry5", 50 + hrand(30));
		TakeNItems(pchar, "jewelry6", 100 + hrand(50));
		PlaySound("interface\important_item.wav");
		Log_Info("Has recibido pepitas");
		dialog.text = "Aquí... Y espero que nunca vuelva a ver ni a ti ni a otros 'envíos' nunca más.";
		link.l1 = "Te aseguro que no lo harás. ¡Adiós, señor!";
		link.l1.go = "Fugitive_gift_exit";
		break;

	case "Fugitive_tavern_fight":
		dialog.text = "¡Entonces desenvaina tu espada, mercenario! ¡No me atraparás tan fácilmente!";
		link.l1 = "¡Bien, vamos a ver tu valor!";
		link.l1.go = "Fugitive_fight_2";
		break;

	case "Fugitive_fight_2": // в таверне
		DialogExit();
		chrDisableReloadToLocation = true;										   // закрыть локацию
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
		LAi_SetImmortal(npchar, false);
		LAi_SetStayType(npchar);
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(npchar, pchar.location, "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
		Diag.currentnode = "Fugitive_afterfight";
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_SetCheckMinHP(npchar, 10.0, true, "Fugitive_afterfight");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;
	}
}
