// диалоги прочих НПС по квесту LSC
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "¿Quieres algo?";
		link.l1 = "No, no es nada.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	//-----------------------------------бандосы Акулы в трюме с припасами--------------------------------------
	case "PantryGuard":
		dialog.text = "¡Ho, ho, miren esto, muchachos! ¡Quién ha venido a visitarnos! ¡Un ladrón saqueando los cofres del pueblo! ¡Ven aquí! Y tú, amigo, ni siquiera intentes hacerte el tonto y sacar tu espada, no fallaré desde tan cerca... ¡Chad estará realmente encantado de verte!";
		link.l1 = "¡Pero yo... yo acabo de llegar!";
		link.l1.go = "PantryGuard_1";
		break;

	case "PantryGuard_1":
		dialog.text = "¡Tienes razón, ja, ja! Te has metido en un buen lío, camarada... Y no podrás escapar de él. Ahora, entrega tus armas y sígueme. ¡La jaula del 'Tártaro' ha estado esperándote por tanto tiempo, ladrón!";
		link.l1 = "...";
		link.l1.go = "PantryGuard_2";
		break;

	case "PantryGuard_2":
		DialogExit();
		chrDisableReloadToLocation = false;
		SetLaunchFrameFormParam("Unas pocas horas después...", "", 0, 3);
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 7, 10); // крутим время
		RecalculateJumpTable();
		DoQuestFunctionDelay("LSC_GotoPrison", 3.0);
		break;

	case "CommonGuard":
		dialog.text = "No intentes robar nada de aquí. Te estaré vigilando.";
		link.l1 = "Eres más que bienvenido.";
		link.l1.go = "exit";
		NextDiag.TempNode = "CommonGuard";
		break;

	case "ChadGuard":
		dialog.text = "Ve y haz lo que Chad te dijo. ¡No hables demasiado!";
		link.l1 = "Sí, estoy en camino...";
		link.l1.go = "exit";
		NextDiag.TempNode = "ChadGuard";
		break;

	case "ChadGuard_Attack":
		dialog.text = "¡Oye! ¿Qué demonios estás haciendo ahí? ¡Bastardo! ¡Ahora sí que estás acabado!";
		link.l1 = "...";
		link.l1.go = "ChadGuard_Attack_1";
		break;

	case "ChadGuard_Attack_1":
		DialogExit();
		sld = characterFromId("Chimiset");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "afraid", "", -1);
		for (i = 1; i <= 3; i++)
		{
			sld = CharacterFromID("ChadGuard_" + i);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		sld = characterFromId("Capper");
		LAi_SetWarriorType(sld);
		ChangeCharacterAddressGroup(sld, "Tartarusprison", "goto", "goto8");
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "LSC_ChadGuard_Die");
		AddDialogExitQuest("MainHeroFightModeOn");
		pchar.GenQuest.Notsearchbody = true; // запрет обыска трупов
		break;

	// ----------------------------------Марчелло Циклоп--------------------------------
	// если ждали в каюте
	case "Cabin":
		dialog.text = "¿Qué diablos haces aquí, maldita sea? ¿Dónde está Barbier?";
		link.l1 = "Nuestro amigo Adolfo está... enfermo. No pudo venir a la reunión, así que me pidió que me quedara un poco en su camarote y te esperara.";
		link.l1.go = "Cabin_1";
		break;

	case "Cabin_A":
		dialog.text = "¿Qué diablos estás haciendo aquí, maldita sea?";
		link.l1 = "Nuestro amigo Adolfo está... enfermo. No pudo venir a la reunión, así que me pidió que estuviera en su lugar. Por así decirlo.";
		link.l1.go = "Cabin_1";
		break;

	case "Cabin_1":
		dialog.text = "Suena extraño... él estaba bien esta mañana y ahora está enfermo.";
		link.l1 = "Bueno, ya sabes cómo suceden las cosas. El ataque repentino de fiebre...";
		link.l1.go = "Cabin_2";
		break;

	case "Cabin_2":
		dialog.text = "Oh, no me gusta tu cara. Estás mintiendo. Barbier nunca confiaría esta reunión a nadie más. Habla, bastardo, ¿quién eres y qué le hiciste?";
		link.l1 = "Sabes, tú tampoco eres un rostro bonito. Ya te he dicho que Barbier está enfermo. ¿Eres del tipo de pensamiento lento o debo repetirme? Se suponía que debía darte la llave y...";
		link.l1.go = "Cabin_3";
		break;

	case "Cabin_3":
		DialogExit();
		sld = characterFromId("Mary");
		LAi_SetActorType(sld);
		LAi_CharacterEnableDialog(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

	// на Церес Смити - спасаем Мэри
	case "mary":
		dialog.text = "¡Maldita sea! Me has encontrado...";
		link.l1 = "¡Sí, escoria! ¡No pondrás un dedo sobre ella! ¡Prepárate para morir!";
		link.l1.go = "mary_1";
		break;

	case "mary_1":
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
		DialogExit();
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "LSC_KillCyclop_CS");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	// посланник от Акулы по варианту N
	case "SharkCureer":
		dialog.text = "¿Eres tú " + GetFullName(pchar) + "?";
		link.l1 = "Sí, soy yo. ¿Cuál es el asunto?";
		link.l1.go = "SharkCureer_1";
		break;

	case "SharkCureer_1":
		dialog.text = "Shark me ha enviado. Te pide que lo veas lo antes posible. Tiene algo importante para ti.";
		link.l1 = "¿Cuál es la prisa?.. Está bien, voy al 'San Agustín' inmediatamente.";
		link.l1.go = "SharkCureer_2";
		break;

	case "SharkCureer_2":
		// сюда можно поставить таймер на гибель Акулы, если не придёт до конца суток
		DialogExit();
		LAi_SetActorType(npchar);
		npchar.lifeday = 0;
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		sld = characterFromId("Dodson");
		sld.dialog.currentnode = "entrance_20"; // ноду Акуле
		break;

	// посланник от Акулы по варианту M
	case "SharkCureer_3":
		dialog.text = "¿Eres tú " + GetFullName(pchar) + "?";
		link.l1 = "Sí, soy yo. ¿Cuál es el asunto?";
		link.l1.go = "SharkCureer_4";
		break;

	case "SharkCureer_4":
		if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
		{
			dialog.text = "Uh, estoy cansado de buscarte... Shark y Layton Dexter. Te piden que los veas de inmediato. Es un asunto muy importante, así que date prisa.";
			link.l1 = "¿Es así? Bien, voy al 'San Agustín' inmediatamente.";
			link.l1.go = "SharkCureer_6";
		}
		else
		{
			dialog.text = "Uh, estoy cansado de buscarte... El almirante Layton Dexter te pide que lo veas de inmediato. Es un asunto muy importante, así que date prisa.";
			link.l1 = "¿Almirante?";
			link.l1.go = "SharkCureer_5";
		}
		break;

	case "SharkCureer_5":
		dialog.text = "Sí. Al ser el segundo al mando, se ha convertido en nuestro almirante tras la muerte dShark.";
		link.l1 = "Ya veo. Bien, me voy al 'San Agustín' inmediatamente.";
		link.l1.go = "SharkCureer_6";
		break;

	case "SharkCureer_6":
		DialogExit();
		LAi_SetActorType(npchar);
		npchar.lifeday = 0;
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		break;

	// тюремщик вместо Каппера
	case "Prisonboss":
		if (npchar.quest.meeting == "0")
		{
			dialog.text = "Ah, aquí estás... Te recuerdo, eres el último hombre que habló con Chimiset. ¿Lo has matado?";
			link.l1 = "¡Deja de decir tonterías! Sabes perfectamente que no fui yo. Creo que sabes quién es el asesino.";
			link.l1.go = "meeting";
			npchar.quest.meeting = "1";
		}
		else
		{
			dialog.text = "¡Eh, es tan aburrido quedarse aquí todo el día! Si tan solo trajeras ron y cartas, amigo, podríamos echarnos una partida...";
			link.l1 = "Lo siento, amigo, no tengo tiempo para esto. Quizás, más tarde.";
			link.l1.go = "exit";
		}
		NextDiag.TempNode = "Prisonboss";
		break;

	case "meeting":
		dialog.text = "Tengo algunas suposiciones, sí, pero no tengo ningún hecho. Nadie vio la muerte del negro. Hay rumores por toda la isla de que nosotros, la gente dShark, somos responsables y dicen que algún novato hizo esto por orden del almirante. ¿Lo ves ahora? Así que no vayas a Rivados, especialmente ahora. Están demasiado enojados.";
		link.l1 = "Está bien. Lo entendí.";
		link.l1.go = "exit";
		NextDiag.TempNode = "Prisonboss";
		break;

	case "Prisonboss_M":
		dialog.text = "¡Eh, es tan aburrido quedarse aquí todo el día! Si tan solo trajeras ron y cartas, amigo, podríamos echar una partida...";
		link.l1 = "Lo siento, amigo, no tengo tiempo para esto. Quizás, más tarde.";
		link.l1.go = "exit";
		NextDiag.TempNode = "Prisonboss_M";
		break;

	// заместитель Акселя в магазине
	case "AxelHelper":
		dialog.text = "¿Qué quieres, amigo?";
		link.l1 = "Mm. ¿Y cuál es tu negocio aquí? ¿Dónde está Axel?";
		link.l1.go = "AxelHelper_1";
		break;

	case "AxelHelper_1":
		dialog.text = "Axel está ocupado. Está teniendo una reunión con Donald Greenspen y se quedará con él hasta el final del día. Así que si quieres comprar algo, habla con él mañana por la mañana. Y yo estoy cuidando la tienda, así que no intentes robar nada...";
		link.l1 = "Ya veo. ¿Y por qué lo hace hoy? Bien, vendré aquí mañana por la mañana.";
		link.l1.go = "exit";
		NextDiag.TempNode = "AxelHelper_2";
		break;

	case "AxelHelper_2":
		dialog.text = NPCStringReactionRepeat("Ya te he dicho todo. Ven aquí mañana.", "¡No me molestes, amigo.  Piérdete!", "¡No me hagas enojar, imbécil!", "¡Vete!!", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Bien.", "Lo tengo, lo tengo.", "Cállate...", "¿Qué?!", npchar, Dialog.CurrentNode);
		link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		break;

	// мать Белого Мальчика - Агнес Кристиансен
	case "agnes":
		dialog.text = "¿Qué quieres, señor?";
		link.l1 = "Hum... Lo siento, señora. Perdóname por mi impertinencia y malos modales, pero quiero preguntarte algo: ¿conoces a un hombre llamado Ole Christiansen?";
		link.l1.go = "agnes_1";
		break;

	case "agnes_1":
		dialog.text = "Repite de nuevo lo que has dicho... ¿Ole Christiansen? ¿¡Ole?!";
		link.l1 = "Sí. También lo llaman el Chico Blanco por un color especial de su cabello. ¿Lo conoces?";
		link.l1.go = "agnes_2";
		break;

	case "agnes_2":
		dialog.text = "¿Lo conozco yo?! ¡Es mi hijo y ha estado desaparecido durante una década! ¿Sabes dónde está, señor? ¡Dime ya dónde está, qué le ha pasado?!";
		link.l1 = "Tranquila, señora, no te preocupes así. Él está bien. Está en mi barco. Todo lo que necesita es desembarcar y venir aquí.";
		link.l1.go = "agnes_3";
		break;

	case "agnes_3":
		dialog.text = "¡Oh... Parece que el Señor finalmente ha escuchado mis plegarias! No puedes imaginarte lo preocupado que estaba cuando él desapareció. ¡Y fue mi culpa, solo mi culpa! ¿Dónde lo has encontrado? No es un chico común... bueno, debes saber de qué estoy hablando.";
		link.l1 = "Lo hago. Sí, es especial. Y no ha cambiado. Parece que todavía es un niño. Lo encontré en una isla. Nos encontramos por accidente. Me pidió una cuenta blanca... ¡maldita sea!... Por una perla.";
		link.l1.go = "agnes_4";
		break;

	case "agnes_4":
		dialog.text = "¿Una perla? ¡Oh, Dios! ¡Las perlas fueron la razón por la que mi chico desapareció! ¡Todo es por ese maldito collar!";
		link.l1 = "¿Es cierto que Ole... se ha ido de su casa por romper tu collar de perlas?... ¡Cálmate, señora, no llores!";
		link.l1.go = "agnes_5";
		break;

	case "agnes_5":
		dialog.text = "Sí, es cierto. Ole rompió mi collar en el muelle y todas las perlas cayeron al agua. Le maldije tanto y mi difunto esposo... lo castigó. Ole desapareció al día siguiente. ¡No puedes imaginar cómo me culpaba por esto!";
		link.l1 = "Ole ha estado recolectando perlas durante años. Las llama las cuentas blancas. Las ha recogido todas para ti y me pidió que te llevara a él. No tenía más detalles excepto la casa con techo rojo. Pero finalmente logré encontrarte.";
		link.l1.go = "agnes_6";
		break;

	case "agnes_6":
		dialog.text = "¿Recolectando perlas?! ¡Oh, Dios! ¡Soy tan culpable ante mi pobre chico! ¡Yo... y él ha estado recolectando perlas! ¡Oh!";
		link.l1 = "Supongo que será mejor que llame a su hijo, señora. Estaba tan ansioso por verte. Dijo que te alegrarás de ver perlas. Pero creo que te alegrarás no por ellas...";
		link.l1.go = "agnes_7";
		break;

	case "agnes_7":
		dialog.text = "Mynheer... ¿serías tan amable? Trae a mi Ole conmigo. Quiero abrazarlo y pedirle perdón...";
		link.l1 = "Claro, señora. Lo traerán aquí de inmediato.";
		link.l1.go = "agnes_8";
		break;

	case "agnes_8":
		DialogExit();
		SetLaunchFrameFormParam("Una hora más tarde", "", 0, 5);
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 1, 10); // крутим время
		RecalculateJumpTable();
		DoQuestFunctionDelay("LSC_OleGoHome", 5.0);
		break;

	case "agnes_9":
		dialog.text = "";
		link.l1 = "Bueno, señora, aquí está su hijo: Ole Christiansen. ¿Lo reconoce?";
		link.l1.go = "agnes_10";
		break;

	case "agnes_10": // перекидываем pchar
		DialogExit();
		LAi_SetActorType(pchar);
		LAi_ActorTurnToCharacter(pchar, characterFromID("Agnes"));
		ChangeShowIntarface();
		SetMainCharacterIndex(GetCharacterIndex("Agnes"));
		PChar = GetMainCharacter();
		LAi_SetPlayerType(PChar);
		sld = characterFromId("Ole");
		sld.dialog.currentnode = "home";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

	case "agnes_11":
		dialog.text = "Mynheer... Lo siento, no pregunté por su nombre... ¿" + pchar.name + "?";
		link.l1 = "" + GetFullName(pchar) + ", señora. Capitán " + GetFullName(pchar) + ".";
		link.l1.go = "agnes_12";
		break;

	case "agnes_12":
		dialog.text = "¡Capitán, no puedes imaginar lo agradecido que estoy por mi hijo! Le has ayudado y le has traído aquí. ¡Me has hecho vivir de nuevo! Haré todo por mi muchacho, le daré todo mi amor que le faltó todos estos años.";
		link.l1 = "Me alegro por ti, señora. Y también por Ole. Es un buen chico y me ayudó en una situación difícil. Tiene un corazón bondadoso. Conozco a un hombre al que Ole salvó de la muerte.";
		link.l1.go = "agnes_13";
		break;

	case "agnes_13":
		dialog.text = "Mynheer, insisto en que debe venir aquí mañana o en cualquier momento que tenga tiempo. Quiero darle las gracias por mi hijo. En este momento estoy un poco... bueno, ya sabe.";
		link.l1 = "Lo hago, señora.";
		link.l1.go = "agnes_14";
		break;

	case "agnes_14":
		dialog.text = "Vuelve aquí mañana. Te recompensaré adecuadamente por todo el bien que has hecho por mi hijo y por mí.";
		link.l1 = "Está bien. ¡Te visitaré seguro!";
		link.l1.go = "agnes_15";
		break;

	case "agnes_15":
		DialogExit();
		bDisableCharacterMenu = false;		// лоченые интерфейсы
		chrDisableReloadToLocation = false; // открыть локацию
		LAi_SetOwnerType(npchar);
		LocatorReloadEnterDisable("Marigo_town", "houseSp2", true);
		NextDiag.CurrentNode = "agnes_16";
		pchar.quest.LSC_Ole_return.win_condition.l1 = "Timer";
		pchar.quest.LSC_Ole_return.win_condition.l1.date.hour = 8.0;
		pchar.quest.LSC_Ole_return.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.LSC_Ole_return.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.LSC_Ole_return.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.LSC_Ole_return.function = "LSC_OleAgnesRegard";
		// удаляем Оле из пассажиров
		sld = characterFromId("Ole");
		RemovePassenger(Pchar, sld);
		DeleteAttribute(pchar, "GenQuest.Ole");
		DoQuestReloadToLocation("Marigo_town", "reload", "houseSp2", "");
		break;

	case "agnes_16":
		dialog.text = "Ah, aquí estás, señor " + GetFullName(pchar) + "¡ Ven, toma asiento...";
		link.l1 = "¡Gracias! ¿Cómo está Ole?";
		link.l1.go = "agnes_17";
		break;

	case "agnes_17":
		dialog.text = "¡Oh, no puedes imaginar lo que has hecho! Fuiste un alivio para el corazón adolorido de una madre... Te debo y rezaré por ti para siempre.";
		link.l1 = "Me haces sonrojar, señora...";
		link.l1.go = "agnes_18";
		break;

	case "agnes_18":
		dialog.text = "Siempre supe que la modestia es lo que hace a la gente noble... noble. He preparado regalos por lo que has hecho. ¡Sí, sí! ¡Y ni se te ocurra rechazarlo! Aquí, toma esto... Primero, hay un cofre lleno de doblones. Segundo, toma este amuleto encantado, lo llaman Escarabajo.\nMi esposo lo poseía, y estoy segura de que estaría encantado de saber que su tesoro pertenecerá a un capitán tan noble, quien me devolvió a mi hijo. Mi esposo era carpintero, solía decir que el Escarabajo aceleraba su trabajo.\nEspero que este anillo te sirva bien. ¡Mereces llevarlo, sin duda! Y finalmente, toma mis herramientas de sastrería. Es un buen conjunto. Podrás elaborar muchas cosas buenas con ellas.";
		link.l1 = "¡Oh! ¡Estos son regalos realmente valiosos para cualquier capitán! Gracias, señora.";
		link.l1.go = "agnes_19";
		break;

	case "agnes_19":
		PlaySound("interface\important_item.wav");
		Log_Info("Has recibido un cofre con doblones");
		Log_Info("Has recibido el amuleto 'Escarabajo'");
		Log_Info("Has recibido un set de sastrería");
		GiveItem2Character(pchar, "chest");
		GiveItem2Character(pchar, "talisman7");
		GiveItem2Character(pchar, "tailor_tool");
		dialog.text = "Y quiero que sepas que las puertas de mi casa siempre están abiertas para ti en cualquier momento. Aquí siempre encontrarás comida, una botella de buen vino y cualquier otra cosa que desees.";
		link.l1 = "Gracias por tus amables palabras, señora. Estaré encantado de verte cuando vuelva a visitar esta ciudad.";
		link.l1.go = "agnes_20";
		break;

	case "agnes_20":
		dialog.text = "¡No faltes a venir!";
		link.l1 = "Y ahora tengo que irme. ¡Adiós y buena suerte!";
		link.l1.go = "agnes_21";
		break;

	case "agnes_21":
		DialogExit();
		NextDiag.CurrentNode = "agnes_22";
		AddCharacterExpToSkill(pchar, "Fortune", 350);
		AddCharacterExpToSkill(pchar, "Leadership", 500);
		ChangeCharacterComplexReputation(pchar, "nobility", 10);
		ChangeCharacterComplexReputation(pchar, "authority", 4);
		break;

	case "agnes_22":
		dialog.text = "Ah, capitán " + GetFullName(pchar) + "¡Estoy tan contento de verte! Ven y siéntate, te serviré una bebida...";
		link.l1 = "¡Gracias! Solo quería saludarte y saber cómo estabas. Me alegra que tú y Ole estén bien.";
		link.l1.go = "exit";
		NextDiag.TempNode = "agnes_22";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	//----------------------------------------- специальные реакции -----------------------------------------------
	// обнаружение ГГ в сундуках
	case "Man_FackYou":
		dialog.text = LinkRandPhrase("¿Qué haces ahí, eh? ¡Ladrón!", "¡Solo mira eso! En cuanto me perdí en la contemplación, ¡decidiste revisar mi cofre!", "¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!");
		link.l1 = "¡Maldita sea!";
		link.l1.go = "fight";
		break;

	case "Woman_FackYou":
		dialog.text = "¿Qué?! ¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!";
		link.l1 = "¡Chica tonta!";
		link.l1.go = "exit_setOwner";
		LAi_group_Attack(NPChar, Pchar);
		break;

	case "fight":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetOwnerTypeNoGroup(npchar);
		LAi_group_Attack(NPChar, Pchar);
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "exit_setOwner":
		LAi_SetOwnerTypeNoGroup(npchar);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
