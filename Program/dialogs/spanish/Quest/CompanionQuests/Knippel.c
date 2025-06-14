void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "First time":
		dialog.text = "¿Qué queréis?";
		link.l1 = "Nada.";
		link.l1.go = "exit";
		break;

	// Квест "Длинные тени старых грехов"
	case "DTSG_Knippel_1":
		dialog.text = "¡Oh, qué calor hace hoy! Podrías atarte una bala encadenada a la pierna y saltar al mar, sólo para librarte de este bochorno.";
		link.l1 = "¡Ja, ja, Charlie!.. Esas son medidas extremas, si me preguntas. Pero no me importaría mojar el gaznate - realmente hace demasiado calor hoy. ¿Te animas?";
		link.l1.go = "DTSG_Knippel_2";
		break;

	case "DTSG_Knippel_2":
		dialog.text = "¿Tomar una o dos copas contigo, Capitán? ¡Siempre!";
		link.l1 = "Eso es lo que me gusta escuchar. ¡Vamos!";
		link.l1.go = "DTSG_Knippel_3";
		break;

	case "DTSG_Knippel_3":
		DialogExit();
		chrDisableReloadToLocation = true;
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "", "", "", "DTSG_BasTerTavern", -1);
		FreeSitLocator("BasTer_tavern", "sit_base2");
		FreeSitLocator("BasTer_tavern", "sit_front2");
		break;

	case "DTSG_Ohotnik_1":
		dialog.text = "¡Hola, marinero, pareces haberlo visto todo! ¿Tomamos un trago y compartimos algunas historias? ¡Yo invito!";
		link.l1 = "";
		link.l1.go = "DTSG_Ohotnik_1_Animation";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));

		break;

	case "DTSG_Ohotnik_1_Animation":
		StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_2", "Quest\CompanionQuests\Knippel.c");
		break;

	case "DTSG_Ohotnik_2":
		dialog.text = "Eh, no gracias, camarada. Vine aquí con mi Capitán. Encuentra a alguien más.";
		link.l1 = "";
		link.l1.go = "DTSG_Ohotnik_2_Animation";
		LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		locCameraFromToPos(5.57, 2.39, -4.63, true, 8.53, 2.07, 1.84);
		break;

	case "DTSG_Ohotnik_2_Animation":
		StartInstantDialog("DTSG_Ohotnik", "DTSG_Ohotnik_3", "Quest\CompanionQuests\Knippel.c");
		locCameraSleep(true);
		break;

	case "DTSG_Ohotnik_3":
		dialog.text = "Ja, un pilluelo como tú tiene opiniones tan altas, ¿sólo bebes con capitanes?";
		link.l1 = "";
		link.l1.go = "DTSG_Ohotnik_3_Animation";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
		break;

	case "DTSG_Ohotnik_3_Animation":
		StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_4", "Quest\CompanionQuests\Knippel.c");
		break;

	case "DTSG_Ohotnik_4":
		dialog.text = "¿¡Grandes opiniones?! ¡He servido durante décadas en la Royal Navy! ¡Y no luché por los señores, sino por gente común como tú y yo, para asegurar la ley y el orden en todas partes!..";
		link.l1 = "";
		link.l1.go = "DTSG_Ohotnik_4_Animation";
		LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;

	case "DTSG_Ohotnik_4_Animation":
		StartInstantDialog("DTSG_Ohotnik", "DTSG_Ohotnik_5", "Quest\CompanionQuests\Knippel.c");
		break;

	case "DTSG_Ohotnik_5":
		dialog.text = "¡Hablas en grande, pero solo bebes con capitanes y nobles! ¡Parece que la Marina sí te enseñó a pulir bien los cañones, ja!";
		link.l1 = "";
		link.l1.go = "DTSG_Ohotnik_5_Animation";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, CharacterFromID("Knippel"));
		break;

	case "DTSG_Ohotnik_5_Animation":
		StartInstantDialogNoType("Knippel", "DTSG_Ohotnik_6", "Quest\CompanionQuests\Knippel.c");
		break;

	case "DTSG_Ohotnik_6":
		dialog.text = "¡Te meteré una bala de cadena por la garganta, mocoso!";
		link.l1 = "Charlie, no te pongas así, no vale la pena.";
		link.l1.go = "DTSG_Ohotnik_7";
		LAi_tmpl_SetDialog(npchar, pchar, -1.0);
		break;

	case "DTSG_Ohotnik_7":
		dialog.text = "Déjame manejar esto, Capitán. El honor de la Marina está en juego, debo defenderlo yo mismo y no esconderme detrás de nadie...";
		link.l1 = "";
		link.l1.go = "DTSG_Ohotnik_8";
		break;

	case "DTSG_Ohotnik_8":
		DialogExit();
		EndQuestMovie();
		locCameraSleep(false);
		LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		sld = CharacterFromID("Blaze");
		LAi_SetImmortal(sld, true);
		LAi_CharacterDisableDialog(sld);
		LAi_SetSitType(sld);
		sld = CharacterFromID("Baster_Smuggler");
		LAi_SetImmortal(sld, true);
		SetMainCharacterIndex(GetCharacterIndex("Knippel"));
		PChar = GetMainCharacter();
		LAi_SetPlayerType(PChar);
		sld = CharacterFromID("DTSG_Ohotnik");
		ChangeCharacterAddressGroup(sld, "BasTer_tavern", "tables", "stay7");
		DoQuestReloadToLocation("BasTer_tavern", "tables", "stay6", "DTSG_BasTerTavern_7");
		break;

	case "DTSG_Knippel_l0":
		dialog.text = "Gracias por esperar, Capitán. Espero no haber tardado mucho.";
		link.l1 = "No te preocupes por eso. ¿No estás herido? Ese bribón era bastante bueno.";
		link.l1.go = "DTSG_Knippel_l1";
		break;

	case "DTSG_Knippel_l1":
		dialog.text = "No se preocupe, Capitán. Lo importante es que obtuvo lo que merecía. Recogí una especie de llave de su cuerpo...";
		link.l1 = "";
		link.l1.go = "DTSG_Knippel_l2";
		break;

	case "DTSG_Knippel_l2":
		dialog.text = "Recogí algún tipo de llave de su cuerpo... Me pregunto para qué podría ser.";
		link.l1 = "Elemental, Charlie... Para una puerta o un cofre, ja-ja. Deberíamos hablar con el tabernero sobre este sinvergüenza, podría ser útil.";
		link.l1.go = "DTSG_Knippel_l3";
		AddItems(pchar, "Key1", 1);
		Log_info("Charlie te dio la llave.");
		PlaySound("interface\important_item.wav");
		break;

	case "DTSG_Knippel_l3":
		DialogExit();

		bDisableCharacterMenu = false;
		InterfaceStates.Buttons.Save.enable = true;
		sld = CharacterFromID("Knippel");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
		sld.location = "None";
		pchar.questTemp.DTSG_BasTerTavern = true;
		AddLandQuestMark(characterFromId("BasTer_tavernkeeper"), "questmarkmain");
		break;

	case "DTSG_Knippel_20":
		dialog.text = "Increíble...";
		link.l1 = "¿Estás pensando lo mismo que yo, Charlie?";
		link.l1.go = "DTSG_Knippel_21";
		break;

	case "DTSG_Knippel_21":
		dialog.text = "No sé usted, señor, pero me sorprende la cantidad de dinero que hay aquí - parecía un hombre común, no un comerciante o un noble.";
		link.l1 = "No es mucho, en realidad, pero tienes razón. Lo que me sorprende es esta extraña carta quemada.";
		link.l1.go = "DTSG_Knippel_22";
		break;

	case "DTSG_Knippel_22":
		dialog.text = "Sí, eso no fue muy inteligente de su parte - es como disparar metralla a un casco resistente. Debería haber destruido la carta por completo.";
		link.l1 = "Verdad. Pero no nos ayuda, no sabemos quién era ni con quién se estaba carteando. Vámonos, Charlie, no hay nada más para nosotros aquí.";
		link.l1.go = "DTSG_Knippel_23";
		break;

	case "DTSG_Knippel_23": // КОНЕЦ ЭТАПА 1
		DialogExit();
		Return_KnippelOfficer();
		;

		AddQuestRecord("DTSG", "2");
		bDisableFastReload = false;
		chrDisableReloadToLocation = false;
		pchar.questTemp.DTSG_Nastoroje1 = true;
		break;

	case "DTSG_Ohotnik_10":
		dialog.text = "¡Tanto por tu cacareada Armada Real, pfft!";
		link.l1 = "Charlie era un buen hombre, decente. Y era un artillero, no un marinero.";
		link.l1.go = "DTSG_Ohotnik_11";
		break;

	case "DTSG_Ohotnik_11":
		dialog.text = "¿¡Un artillero?! Entonces, es exactamente como dije, ¡ja-ja-ja! Y no me mires así - deberías haber sabido a quién estabas reclutando en tu tripulación.";
		link.l1 = "Deberías haber sabido con quién te estabas metiendo.";
		link.l1.go = "DTSG_Ohotnik_Agressia_1";
		link.l2 = "Sigues vivo solo porque ganaste justamente, así que guarda tu asquerosa lengua y lárgate de aquí.";
		link.l2.go = "DTSG_Ohotnik_Otpustil_1";
		break;

	case "DTSG_Ohotnik_Otpustil_1":
		dialog.text = "Bueno, pensé que tendría que pelear contigo a continuación. Es agradable saber que el honor significa algo para ti.";
		link.l1 = "No eran solo palabras vacías para Charlie tampoco. Pero en cuanto a ti, tengo mis dudas. De todos modos, ya no importa.";
		link.l1.go = "DTSG_Ohotnik_Otpustil_2";
		break;

	case "DTSG_Ohotnik_Otpustil_2": // ПРОВАЛ ЭТАПА 1
		DialogExit();

		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
		npchar.lifeday = 0;
		LAi_LocationDisableOfficersGen("BasTer_tavern", false);
		bDisableFastReload = false;
		chrDisableReloadToLocation = false;
		bDisableCharacterMenu = false;
		InterfaceStates.Buttons.Save.enable = true;
		ChangeCharacterComplexReputation(pchar, "nobility", 3);
		ChangeCharacterComplexReputation(pchar, "authority", -3);
		ChangeCharacterComplexReputation(pchar, "fame", -3);
		break;

	case "DTSG_Ohotnik_Agressia_1":
		dialog.text = "¿Y con quién me metí, con un débil mimado? ¡¿Has visto siquiera tu propio bigote fino?!..";
		link.l1 = "Sabes bien cómo tocar las fibras sensibles... Será aún más satisfactorio descargar mi ira sobre ti.";
		link.l1.go = "DTSG_Ohotnik_Agressia_2";
		break;

	case "DTSG_Ohotnik_Agressia_2":
		DialogExit();

		LAi_LocationFightDisable(&Locations[FindLocation(PChar.location)], false);
		sld = CharacterFromID("DTSG_Ohotnik");
		DeleteAttribute(sld, "CantLoot");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		LAi_group_SetCheck("EnemyFight", "DTSG_Ohotnik_Agressia_3");
		LAi_SetFightMode(pchar, true);
		break;

	case "DTSG_PiterAdams_1":
		dialog.text = "Espera, Capitán. Veo que eres un hombre digno y noble, ¿puedes ayudarme con algo? Es una cuestión de honor.";
		link.l1 = "Tal vez pueda, pero ¿cuál es el asunto? ¿Y por qué viniste a mí? Hay muchas personas nobles por aquí. ¿Con quién tengo el honor de hablar, por cierto?";
		link.l1.go = "DTSG_PiterAdams_2";
		InterfaceStates.Buttons.Save.enable = true;
		break;

	case "DTSG_PiterAdams_2":
		dialog.text = "Peter. Peter Adams. Puedo ver que no eres un típico descendiente consentido de una vieja familia, sino un hombre fiable con mano firme.";
		link.l1 = "Oh, debería haberme visto cuando llegué por primera vez al Caribe, señor. Pero adelante, ¿con qué necesita ayuda?";
		link.l1.go = "DTSG_PiterAdams_3";
		break;

	case "DTSG_PiterAdams_3":
		dialog.text = "¿Podrías... batirte en duelo en mi nombre, señor? Un alborotador local, Ralph Faggle, insultó a mi esposa. Y la acosó, públicamente. Justo delante de mí. ¿Puedes imaginarte eso?";
		link.l1 = " No hay mucho honor en desafiar a un duelo y luego esconderse detrás de otra persona. Especialmente cuando no solo está en juego tu honor personal, sino el de una mujer, ni más ni menos que tu esposa. ¿No lo crees, Adams? ¿Por qué no puedes luchar por tu mujer tú mismo?";
		link.l1.go = "DTSG_PiterAdams_4";
		break;

	case "DTSG_PiterAdams_4":
		dialog.text = "Y tienes razón, absolutamente razón. Pero recientemente sufrí de una fiebre severa, y apenas puedo mantenerme de pie.\nAdmito que no es fácil para mí pedirte algo así. Si me hubiera insultado, lo habría soportado. ¡Pero no cuando el honor de mi esposa está en juego! No soy un cobarde, señor. Una vez serví en la Armada Real y navegué en el mismo barco con el mismísimo Robert Blake.";
		link.l1 = "Yo...";
		link.l1.go = "DTSG_PiterAdams_5";
		break;

	case "DTSG_PiterAdams_5":
		StartInstantDialog("Knippel", "DTSG_PiterAdams_6", "Quest\CompanionQuests\Knippel.c");
		break;

	case "DTSG_PiterAdams_6":
		dialog.text = "Te ayudaremos.";
		link.l1 = "¿Charlie?..";
		link.l1.go = "DTSG_PiterAdams_7";
		CharacterTurnByChr(npchar, characterFromId("DTSG_PiterAdams")) break;

	case "DTSG_PiterAdams_7":
		dialog.text = "Es un hombre digno, Capitán. ¡Y que me condenen a la eternidad con balas de cañón si no es cierto! Grandes personas sirvieron con el Almirante Blake. Lucharon juntos para que nadie oprimiera al pueblo común\nY gracias a él, Jamaica fue liberada de la tiranía de los españoles.";
		link.l1 = "Aun si ese es el caso, no permitiré que mis tripulantes me interrumpan o tomen decisiones por mí. ¿Está claro?";
		link.l1.go = "DTSG_PiterAdams_8";
		link.l2 = "Entiendo, de verdad. Sin embargo, ni siquiera he tenido la oportunidad de responder. Intenta no ser tan apresurado e interrumpirme en el futuro, ¿de acuerdo?";
		link.l2.go = "DTSG_PiterAdams_8";
		CharacterTurnByChr(npchar, pchar) break;

	case "DTSG_PiterAdams_8":
		dialog.text = "Te diré esto, capitán - si no ayudas a este hombre, ¡el viejo Charlie dejará todo y se batirá en duelo por él mismo, que sea maldito en el acto!";
		if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje1"))
		{
			link.l1 = "Tranquilo ahora, no dije que me niego a ayudar. ¿Verdad, Sr. Adams?";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_1";
		}
		else
		{
			link.l1 = "Honestamente, Charlie, me estás haciendo parecer un cobarde. Y nunca lo he sido. Deberías saber eso.";
			link.l1.go = "DTSG_PiterAdams_NN_1";
		}
		break;

	case "DTSG_PiterAdams_NN_1":
		dialog.text = "Uh, lo siento, Capitán, me dejé llevar.";
		link.l1 = "Está bien. Pero mantén el control, ¿de acuerdo?";
		link.l1.go = "DTSG_PiterAdams_NN_1_1";
		break;

	case "DTSG_PiterAdams_NN_1_1":
		StartInstantDialog("DTSG_PiterAdams", "DTSG_PiterAdams_NN_2", "Quest\CompanionQuests\Knippel.c");
		break;

	case "DTSG_PiterAdams_NN_2":
		dialog.text = "";
		link.l1 = "Lucharé en duelo por usted, Sr. Adams.";
		link.l1.go = "DTSG_PiterAdams_NN_3";
		break;

	case "DTSG_PiterAdams_NN_3":
		dialog.text = "¡Gracias, señor! ¡Dios lo bendiga!";
		link.l1 = "Y bendice también al Lord Protector, ¿verdad, Sr. Adams? No te preocupes, Charles de Maure nunca deja a un hombre honesto en problemas.";
		link.l1.go = "DTSG_PiterAdams_NN_4";
		break;

	case "DTSG_PiterAdams_NN_4":
		dialog.text = "Apreciamos mucho, señor de Maure, ¡señor! ¿Le gustaría venir a cenar con Jane y conmigo?";
		link.l1 = "Bueno, yo...";
		link.l1.go = "DTSG_PiterAdams_NN_5";
		break;

	case "DTSG_PiterAdams_NN_5":
		dialog.text = "¡Insisto!";
		link.l1 = "Bueno, solo si insistes. Gracias, Peter. Conduce el camino.";
		link.l1.go = "DTSG_PiterAdams_IdemKDomu";
		break;

	case "DTSG_PiterAdams_Nastoroje_1":
		StartInstantDialog("DTSG_PiterAdams", "DTSG_PiterAdams_Nastoroje_2", "Quest\CompanionQuests\Knippel.c");
		break;

	case "DTSG_PiterAdams_Nastoroje_2":
		dialog.text = "¡Por supuesto, es verdad, señor! ¿Le gustaría venir con Jane y descansar después de su viaje?";
		link.l1 = "Gracias, pero ¿es correcto aprovecharse de tu hospitalidad?";
		link.l1.go = "DTSG_PiterAdams_Nastoroje_3";
		break;

	case "DTSG_PiterAdams_Nastoroje_3":
		dialog.text = " Oh, al contrario, Capitán, nos sentiríamos ofendidos si no vinieras. ";
		link.l1 = "¿Cómo podría negarme entonces? ¡Después de ti, Peter!";
		link.l1.go = "DTSG_PiterAdams_IdemKDomu";
		break;

	case "DTSG_PiterAdams_IdemKDomu":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocator(npchar, "reload", "houseF1", "DTSG_PiterAdams_VDom", -1);
			LAi_SetActorType(pchar);
			LAi_ActorFollow(pchar, npchar, "", -1);
			sld = CharacterFromID("Knippel");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
	case "DTSG_PiterAdamsRyadomSDomom_1":
		dialog.text = "¡Eso somos nosotros! Por favor, entra.";
		if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje1"))
		{
			link.l1 = "Gracias. ¿Puedo hablar con Jane? Pregúntale cómo sucedió - necesito todos los detalles.";
			link.l1.go = "DTSG_PiterAdamsRyadomSDomom_2";
		}
		link.l2 = "Mis más sinceras disculpas, pero después de pensarlo mejor, debo rechazar. Tengo un duelo para el cual debo prepararme. Por cierto, ¿dónde y cuándo está programado?";
		link.l2.go = "DTSG_PiterAdamsRyadomSDomom_4";
		break;

	case "DTSG_PiterAdamsRyadomSDomom_2":
		dialog.text = "Bueno, por supuesto, señor. Ambos con gusto hablaremos con usted y responderemos a todas sus preguntas. Por favor, sígame.";
		link.l1 = "Gracias, Peter.";
		link.l1.go = "DTSG_PiterAdamsRyadomSDomom_3";
		break;

	case "DTSG_PiterAdamsRyadomSDomom_3":
		DoQuestReloadToLocation("PortPax_houseF1", "reload", "reload1", "DTSG_PiterAdams_VDom_2");
		break;

	case "DTSG_PiterAdamsRyadomSDomom_4":
		dialog.text = "¡Qué lástima! Pero tienes razón, debes prepararte a fondo, por supuesto. Dos horas. Justo afuera de las puertas de la ciudad.";
		link.l1 = "Entendido, gracias. Con gusto vendré una vez que haya terminado. ¡Nos vemos entonces!";
		link.l1.go = "DTSG_PiterAdamsRyadomSDomom_5";
		break;

	case "DTSG_PiterAdamsRyadomSDomom_5":
		DialogExit();
		bDisableFastReload = false;
		chrDisableReloadToLocation = false;

		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "", -1);
		npchar.location = "None";

		sld = CharacterFromID("Knippel");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
		LAi_SetOfficerType(sld);
		sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
		sld.Dialog.CurrentNode = "Knippel_officer";
		sld.location = "None";

		PChar.quest.DTSG_PoP_DuelTime.win_condition.l1 = "Timer";
		PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.hour = sti(GetTime() + 2);
		PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.day = GetAddingDataDay(0, 0, 0);
		PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 0);
		PChar.quest.DTSG_PoP_DuelTime.win_condition.l1.date.year = GetAddingDataYear(0, 0, 0);
		PChar.quest.DTSG_PoP_DuelTime.win_condition = "DTSG_PoP_DuelTime";

		PChar.quest.DTSG_PoP_Duel.win_condition.l1 = "location";
		PChar.quest.DTSG_PoP_Duel.win_condition.l1.location = "PortPax_ExitTown";
		PChar.quest.DTSG_PoP_Duel.win_condition = "DTSG_PoP_Duel";

		AddQuestRecord("DTSG", "3");
		break;

	case "DTSG_JeinAdams_1":
		dialog.text = "¡Bienvenido! Querido, no me dijiste que traerías invitados - me habría preparado adecuadamente.";
		link.l1 = "Gracias, señora, no tardaremos mucho. Charles de Maure, a su servicio. He accedido a escuchar su historia con su esposo. Cuénteme cómo sucedió.";
		link.l1.go = "DTSG_JeinAdams_2";
		break;

	case "DTSG_JeinAdams_2":
		dialog.text = "¡Oh, fue horrible! Ralph estaba completamente borracho. Empezó a acosarme frente a los vecinos, incluso delante de Peter, diciendo cosas obscenas...";
		link.l1 = "¿Qué te dijo exactamente?";
		link.l1.go = "DTSG_JeinAdams_3";
		break;

	case "DTSG_JeinAdams_3":
		dialog.text = "Tengo demasiada vergüenza para hablar de ello. Luego se despejó, y...";
		link.l1 = "¿Se disculpó y pidió cancelar el duelo, quizás?";
		link.l1.go = "DTSG_JeinAdams_4";
		break;

	case "DTSG_JeinAdams_4":
		dialog.text = "Ni una vez.";
		link.l1 = "Lo siento por usted. Me gustaría saber una cosa más, si lo permite, señora.";
		link.l1.go = "DTSG_JeinAdams_5";
		break;

	case "DTSG_JeinAdams_5":
		dialog.text = "¿Y qué es eso, señor?";
		link.l1 = "¿Qué circunstancias de la vida y pruebas os forzaron a ti y a tu esposo a vivir aquí? En cualquier ciudad inglesa, dados los méritos de tu esposo, ya habríais puesto a Ralph en su lugar.";
		link.l1.go = "DTSG_JeinAdams_6";
		break;

	case "DTSG_JeinAdams_6":
		StartInstantDialog("Knippel", "DTSG_JeinAdams_7", "Quest\CompanionQuests\Knippel.c");
		break;

	case "DTSG_JeinAdams_7":
		dialog.text = "¡Le ruego me disculpe, señor, pero ¿cómo se atreve?! Si no fuera usted mi capitán, agarraría una bala encadenada y le daría una buena tunda. \nNo solo desconfía de un hombre tan digno como el Sr. Adams, sino que también se burla de una dama en apuros...";
		link.l1 = "¿Me oíste burlarme de una dama? ¿No? Entonces no me calumnies. Nuestra gente podría haberles ayudado, por eso pregunté.";
		link.l1.go = "DTSG_JeinAdams_8a";
		link.l1 = "¡Cálmate, Charlie! ¿Cómo pudiste...? Solo quería saber más sobre las dificultades de Jane y Peter y solidarizarme con ellos. En las colonias inglesas, seguramente ya les habrían ayudado.";
		link.l1.go = "DTSG_JeinAdams_8b";
		break;

	case "DTSG_JeinAdams_8a":
		dialog.text = "La vida puede tomar muchos caminos... El naufragio. O la calumnia de alguien, que a veces puede obligar incluso a personas tan honestas a esconderse en desgracia\nSi eres tan desconfiado y suspicaz, puedes hablar con los vecinos. Estoy seguro de que confirmarán cada palabra. ¡Pero el viejo Charlie no se rebajaría a discutir las penas de la gente a sus espaldas!";
		link.l1 = "¿No me oíste? Dije que ayudaría a esta gente.";
		link.l1.go = "DTSG_JeinAdams_9";
		ChangeCharacterComplexReputation(pchar, "nobility", -2);
		ChangeCharacterComplexReputation(pchar, "authority", 2);
		break;

	case "DTSG_JeinAdams_8b":
		dialog.text = "La vida puede dar muchas vueltas... El naufragio. O las calumnias de alguien, que a veces pueden obligar incluso a personas tan honestas a esconderse en desgracia.\nSi eres tan desconfiado y suspicaz, puedes hablar con los vecinos. Estoy seguro de que confirmarán cada palabra. ¡Pero el viejo Charlie no se rebajaría a discutir las penas de la gente a sus espaldas!";
		link.l1 = "¿No me oíste? Dije que ayudaría a estas personas.";
		link.l1.go = "DTSG_JeinAdams_9";
		ChangeCharacterComplexReputation(pchar, "nobility", 2);
		ChangeCharacterComplexReputation(pchar, "authority", -2);
		break;

	case "DTSG_JeinAdams_9":
		StartInstantDialog("DTSG_PiterAdams", "DTSG_JeinAdams_10", "Quest\CompanionQuests\Knippel.c");
		break;

	case "DTSG_JeinAdams_10":
		dialog.text = "Gracias desde el fondo de nuestros corazones. Te recordaremos en nuestras oraciones.";
		link.l1 = "Eso es bueno. Por cierto, sobre nuestro asunto. ¿Dónde y cuándo arregló el duelo, señor Adams?";
		link.l1.go = "DTSG_JeinAdams_11";
		break;

	case "DTSG_JeinAdams_11":
		dialog.text = "A las afueras de las puertas de la ciudad, señor. En dos horas.";
		link.l1 = "Lo lograré. Espérame con buenas noticias. ¡Y ni pienses en encender una vela por mi descanso antes de tiempo!";
		link.l1.go = "DTSG_JeinAdams_13";
		break;

	case "DTSG_JeinAdams_13":
		DoQuestReloadToLocation("PortPax_town", "reload", "houseF1", "DTSG_PiterAdams_IsDoma");
		break;

	case "DTSG_Knippel_30":
		dialog.text = "¿Algo le molesta, capitán? Parece muy pensativo.";
		link.l1 = "Sabes, sí. Algo en la historia de Adams no cuadra, y...";
		link.l1.go = "DTSG_Knippel_31";
		break;

	case "DTSG_Knippel_31":
		dialog.text = "¿¡Cuánto tiempo va a continuar esto, señor?! ¿Reacciona usted así cada vez que alguien necesita ayuda?";
		link.l1 = "Por el amor de Dios, habla en voz baja. Lo gritarías a toda la calle. Dije que iría al duelo. ¿No te basta con eso? Ahora escúchame atentamente.";
		link.l1.go = "DTSG_Knippel_32";
		break;

	case "DTSG_Knippel_32":
		dialog.text = "Hmm, está bien, Capitán. Perdón por mi arrebato - me importa el destino de aquellos que sirvieron en la Marina Real. Muchos de nosotros éramos tipos decentes, merecedores de un destino mejor del que la mayoría obtuvo.";
		link.l1 = "Te entiendo, Charlie. Ahora recuerda lo que hay que hacer. Quiero que envíes a algunos de la tripulación a las puertas de la ciudad. A medida que se acerque la hora del duelo, que se reúnan en silencio y estén listos para mi señal.";
		link.l1.go = "DTSG_Knippel_33";
		break;

	case "DTSG_Knippel_33":
		dialog.text = "¿Tienes la intención de convertir un duelo honesto en un asesinato?";
		link.l1 = "Sospecho que no será del todo honesto. Señalaré solo si es necesario. Si todo es realmente transparente, estaré feliz de estar equivocado. ¿Entiendes ahora? ¿Recuerdas lo que pasó hace un mes?";
		link.l1.go = "DTSG_Knippel_34";
		break;

	case "DTSG_Knippel_34":
		dialog.text = "Entendido, señor. Francamente, no estoy muy contento con esto, pero haré lo que sea necesario. No te preocupes.";
		link.l1 = "Eso es lo que quería escuchar.";
		link.l1.go = "DTSG_Knippel_35";
		break;

	case "DTSG_Knippel_35":
		DialogExit();
			
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
		npchar.location = "None";
		AddDialogExitQuestFunction("DTSG_Knippel_36");
	break;

	case "DTSG_RalfFaggl":
		LAi_LocationDisableOfficersGen("PortPax_ExitTown", false);
		PChar.quest.DTSG_PoP_DuelTime.over = "yes";
		PChar.quest.DTSG_PoP_Duel.over = "yes";
		dialog.text = "Así que, de Maure. Llegas temprano. Y todavía estamos en la ciudad. Aunque no importa. Lástima que no trajiste a ese viejo tonto contigo. Pero no te preocupes, eventualmente llegaremos a él.";
		link.l1 = "A su servicio en cualquier momento. ¿Mercenarios, son ustedes? ¿A quién crucé?";
		link.l1.go = "DTSG_RalfFaggl_2";
		break;

	case "DTSG_RalfFaggl_2":
		dialog.text = "Eso es, nadie. Vamos tras ese viejo pedorro, Charlie, y es más fácil encontrarlo a través de ti, ya que nos enteramos de que ahora está en tu barco. Esto no es la jungla, así que tendremos que actuar rápidamente para evitar atraer a la multitud. Pero aquí, al menos, no te escaparás.";
		link.l1 = "¿Supongo que todo este asunto del duelo fue una trampa?";
		link.l1.go = "DTSG_RalfFaggl_3";
		break;

	case "DTSG_RalfFaggl_3":
		dialog.text = "Un poco tarde para darse cuenta de eso, amigo. Habríamos luchado de todos modos - soy Ralph Faggle, a su servicio.";
		link.l1 = "En realidad, lo sospechaba, así que decidí hablar con los vecinos. Por cierto, ¿está Adams involucrado en esto también? ¿Y qué hay de Jane? ¿Podría ella ser...";
		link.l1.go = "DTSG_RalfFaggl_4";
		break;

	case "DTSG_RalfFaggl_4":
		dialog.text = "  La curiosidad mató al gato, ¿no lo has oído? Te dijeron que te presentaras al duelo, no que anduvieras husmeando. Podrías tener una oportunidad de sobrevivir a este lío. \nPor supuesto. Provocar al viejo marino y obligar a su oficial al mando a batirse en duelo: un plan perfecto que se nos ocurrió, Peter, creo. Y Jane también hizo bien su parte.";
		link.l1 = "Dime, ¿quién quería deshacerse de Charlie?";
		link.l1.go = "DTSG_RalfFaggl_5";
		break;

	case "DTSG_RalfFaggl_5":
		dialog.text = "Ja, ¿como si te lo dijera? Defiéndete.";
		link.l1 = "Lástima. Entonces le preguntaré a Peter más tarde.";
		link.l1.go = "DTSG_RalfFaggl_6";
		break;

	case "DTSG_RalfFaggl_6":
		DialogExit();

		sld = CharacterFromID("DTSG_FrederikStouks");
		LAi_SetCheckMinHP(sld, 1, true, "DTSG_FrederikStouks_ranen");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");

		sld = CharacterFromID("DTSG_RalfFaggl");
		LAi_SetCheckMinHP(sld, 1, false, "DTSG_RalfFaggl_ubit");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");

		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		LAi_SetFightMode(pchar, true);
		break;

	case "DTSG_PiterAdams_11":
		dialog.text = "Ah, veo que tomaste mi historia en serio y ya castigaste a Ralph, Capitán.";
		link.l1 = "Por supuesto, ya que como has notado, soy un hombre digno y noble. Y ahora tendré que castigarte por esta traicionera trampa.";
		link.l1.go = "DTSG_PiterAdams_12";
		npchar.SaveItemsForDead = true;
		npchar.DontClearDead = true;
		GiveItem2Character(npchar, "letter_1");
		ChangeItemName("letter_1", "itmname_specialletter");
		ChangeItemDescribe("letter_1", "itmdescr_DTSG_letter2");
		break;

	case "DTSG_PiterAdams_12":
		dialog.text = "Eres bienvenido a intentarlo, Capitán - seguramente ya estás exhausto y herido.";
		link.l1 = "Entonces tomemos un descanso. Mientras tanto, dime, ¿para quién trabajas?";
		link.l1.go = "DTSG_PiterAdams_13";
		break;

	case "DTSG_PiterAdams_13":
		dialog.text = "Lo siento, pero a mi patrón no le gustaría eso, incluso si después me encargara de ti con éxito. Lo cual, por cierto, sucederá ahora.";
		link.l1 = "¡Maldita sea!..";
		link.l1.go = "DTSG_PiterAdams_14";
		break;

	case "DTSG_PiterAdams_14":
		DialogExit();

		if (MOD_SKILL_ENEMY_RATE > 4)
		{
			sld = CharacterFromID("DTSG_FrederikStouks");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			LAi_SetHP(sld, GetCharacterBaseHPValue(sld) / 2, GetCharacterBaseHPValue(sld));
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, false);
		}
		else
		{
			sld = CharacterFromID("DTSG_FrederikStouks");
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, false);
			LAi_KillCharacter(sld);
		}

		sld = CharacterFromID("Knippel");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);

		sld = CharacterFromID("DTSG_PiterAdams");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		LAi_group_SetCheck("EnemyFight", "DTSG_Sosedi_Pobeda");
		LAi_SetFightMode(pchar, true);
		break;

	case "DTSG_Knippel_40":
		dialog.text = "¡No puedo creer que estos... estos canallas no solo nos engañaron, sino que también mintieron sobre la Real Armada! ¡Cómo se atreven! Si no estuvieran muertos, les haría tragar un par de balas encadenadas por tal traición!..";
		link.l1 = "Las personas mienten sobre todo tipo de cosas, Charlie. Pensé que lo sabías bien. Pero lo que seguramente sabes es quién los envió. Esta no es la primera trampa que te tienden recientemente. Tenían una carta con una descripción detallada de ti. ¿A quién enfureciste tanto?";
		link.l1.go = "DTSG_Knippel_41";
		break;

	case "DTSG_Knippel_41":
		dialog.text = "Bueno, yo... ¿Quizás encontremos algo más en la casa de los Adams, señor?";
		link.l1 = "¿Esquivando la pregunta? Pero tienes razón, planeaba buscarlo a fondo de todos modos. Vamos.";
		link.l1.go = "DTSG_Knippel_42";
		break;

	case "DTSG_Knippel_42":
		DialogExit();

		LAi_SetActorType(npchar);
		LAi_ActorFollow(npchar, pchar, "", -1);
		LAi_SetOfficerType(npchar);
		npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
		npchar.Dialog.CurrentNode = "Knippel_officer";
		npchar.location = "None";
		LAi_LocationDisableOfficersGen("PortPax_town", false);
		bDisableFastReload = false;
		chrDisableReloadToLocation = false;

		PChar.quest.DTSG_PoP_ProverimSunduk.win_condition.l1 = "ExitFromLocation";
		PChar.quest.DTSG_PoP_ProverimSunduk.win_condition.l1.location = PChar.location;
		PChar.quest.DTSG_PoP_ProverimSunduk.win_condition = "DTSG_PoP_ProverimSunduk";
		break;

	case "DTSG_Knippel_50":
		dialog.text = "¡Santos cañonazos, tanto oro!";
		link.l1 = "Qué lástima que no hay nada más aquí. 'Jane' tampoco se encuentra por ningún lado. ¿Crees que aún sigue viva?";
		link.l1.go = "DTSG_Knippel_51";
		break;

	case "DTSG_Knippel_51":
		dialog.text = "No sé, señor, esos canallas son capaces de cualquier cosa...";
		link.l1 = "Eso es cierto, pero me parece que sabes más de lo que dices. No es la primera vez que te han cazado. Y cada vez encontramos un montón de dinero en ellos.";
		link.l1.go = "DTSG_Knippel_52";
		break;

	case "DTSG_Knippel_52":
		dialog.text = "No estoy seguro, Capitán, pero tal vez era un prestamista de San Juan.";
		link.l1 = "¿Cómo lo traicionaste?";
		link.l1.go = "DTSG_Knippel_53";
		break;

	case "DTSG_Knippel_53":
		dialog.text = "Bueno... hace algún tiempo, le pedí prestado dinero para pagar todas mis otras deudas. Richard prometió pagarlo, pero...";
		link.l1 = "¿Crees que no lo hizo?";
		link.l1.go = "DTSG_Knippel_54";
		break;

	case "DTSG_Knippel_54":
		dialog.text = "No lo habría creído antes, pero después de lo que te hizo y salió apresuradamente del Caribe con Abi... Tal vez se olvidó de la deuda. O no lo hizo pero se fue de todas formas... Richard actuó como un verdadero imbécil, señor. No me sorprendería pero aún así me decepcionaría si resulta ser cierto otra vez.";
		link.l1 = "No seas tan categórico prematuramente, Charlie. Así que, San Juan es.";
		link.l1.go = "DTSG_Knippel_55";
		break;

	case "DTSG_Knippel_55": // КОНЕЦ ЭТАПА 2
		DialogExit();
		bDisableFastReload = false;
		chrDisableReloadToLocation = false;

		npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
		npchar.Dialog.CurrentNode = "Knippel_officer";
		LAi_SetActorType(npchar);
		LAi_ActorFollow(npchar, pchar, "", -1);
		LAi_SetOfficerType(npchar);
		npchar.location = "None";

		n = Findlocation("PortPax_town");
		locations[n].reload.l31.name = "houseF1";
		locations[n].reload.l31.go = "CommonRoom_MH9";
		locations[n].reload.l31.emerge = "reload1";
		locations[n].reload.l31.autoreload = "0";
		locations[n].reload.l31.label = "House";

		BackItemName("letter_1");
		BackItemDescribe("letter_1");
		TakeItemFromCharacter(pchar, "letter_1");
		AddQuestRecord("DTSG", "5");
		QuestOpenSeaExit()

			AddMapQuestMarkCity("SentJons", true);
		PChar.quest.DTSG_Etap3_Start.win_condition.l1 = "location";
		PChar.quest.DTSG_Etap3_Start.win_condition.l1.location = "Antigua";
		PChar.quest.DTSG_Etap3_Start.win_condition = "DTSG_Etap3_Start";
		break;

	case "DTSG_PiterAdams_20":
		if (CheckAttribute(pchar, "questTemp.DTSG_ZovemMatrosov"))
		{
			dialog.text = "Ah, aquí estás, señor - parece que todos decidieron llegar temprano. A juzgar por tu apariencia, pareces bastante despreocupado, ¿estás tan seguro de tus habilidades?";
			link.l1 = "Naturalmente, este no es mi primer duelo.";
			link.l1.go = "DTSG_PiterAdams_Nastoroje_21";
			ChangeCharacterComplexReputation(pchar, "authority", 1);
		}
		else
		{
			dialog.text = "Tenía miedo de que no vinieras, señor. Los demás ya están aquí.";
			link.l1 = "Un verdadero noble solo puede llegar tarde a su muerte.";
			link.l1.go = "DTSG_PiterAdams_NN_21";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		}
		break;

	case "DTSG_PiterAdams_NN_21":
		dialog.text = "¡Maravillosas palabras, señor! Conozca a nuestro oponente, Ralph Faggle. Y este es nuestro segundo, Frederick Stokes.";
		link.l1 = "";
		link.l1.go = "DTSG_PiterAdams_NN_22";
		break;

	case "DTSG_PiterAdams_NN_22":
		dialog.text = "Conoce...";
		link.l1 = "";
		link.l1.go = "DTSG_PiterAdams_NN_23";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		break;

	case "DTSG_PiterAdams_NN_23":
		dialog.text = "Nuestro oponente, Ralph Faggle.";
		link.l1 = "";
		link.l1.go = "DTSG_PiterAdams_NN_24";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;

	case "DTSG_PiterAdams_NN_24":
		dialog.text = "Y este es nuestro segundo, Frederick Stokes.";
		link.l1 = "";
		link.l1.go = "DTSG_PiterAdams_NN_25";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		SetCameraDialogMode(CharacterFromID("DTSG_FrederikStouks"));
		break;

	case "DTSG_PiterAdams_NN_25":
		dialog.text = "...";
		link.l1 = "¿Entonces este es Ralph? No parece un vecino borracho típico.";
		link.l1.go = "DTSG_PiterAdams_NN_26";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, pchar);
		SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;

	case "DTSG_PiterAdams_NN_26":
		dialog.text = "  Nunca sabes quién podría ser tu vecino, ¿lo has pensado, señor de Maure? Heh-heh-heh.";
		link.l1 = "Entonces, esto es una trampa... Veo que hasta has dejado de temblar. ¿Cansado de hacerte el enfermo?";
		link.l1.go = "DTSG_PiterAdams_NN_27";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, pchar);
		SetCameraDialogMode(npchar);
		break;

	case "DTSG_PiterAdams_NN_27":
		dialog.text = "Lo único que puedo sacudirme ahora es la risa por tu ingenuidad.";
		link.l1 = "Vaya, vaya. Solo lamento que Charlie se haya unido - habría sido más fácil y tranquilo lidiar contigo a solas...";
		link.l1.go = "DTSG_PiterAdams_BitvaDuel";
		break;

	case "DTSG_PiterAdams_Nastoroje_21":
		dialog.text = "¡Bueno, eso es maravilloso!";
		link.l1 = "";
		link.l1.go = "DTSG_PiterAdams_Nastoroje_22";
		break;

	case "DTSG_PiterAdams_Nastoroje_22":
		dialog.text = "Permíteme presentar...";
		link.l1 = "";
		link.l1.go = "DTSG_PiterAdams_Nastoroje_23";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		break;

	case "DTSG_PiterAdams_Nastoroje_23":
		dialog.text = "Señor Stokes, nuestro segundo.";
		link.l1 = "";
		link.l1.go = "DTSG_PiterAdams_Nastoroje_24";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		SetCameraDialogMode(CharacterFromID("DTSG_FrederikStouks"));
		break;

	case "DTSG_PiterAdams_Nastoroje_24":
		dialog.text = "Y este es Ralph Faggle.";
		link.l1 = "¿Así que ese es Ralph? Debo admitir que lo imaginé de otra manera. Pero no importa, he lidiado con peores.";
		link.l1.go = "DTSG_PiterAdams_Nastoroje_25";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, CharacterFromID("DTSG_RalfFaggl2"));
		SetCameraDialogMode(CharacterFromID("DTSG_RalfFaggl2"));
		break;

	case "DTSG_PiterAdams_Nastoroje_25":
		dialog.text = "Hmm, me pregunto, ¿eres ingenuo, que no entiendes nada? ¿O tan seguro de ti mismo?";
		link.l1 = "¿Y qué es lo que no entiendo, señor Adams? Vamos, sorpréndeme.";
		link.l1.go = "DTSG_PiterAdams_Nastoroje_26";
		LAi_SetActorType(npchar);
		LAi_ActorTurnToCharacter(npchar, pchar);
		SetCameraDialogMode(npchar);
		break;

	case "DTSG_PiterAdams_Nastoroje_26":
		dialog.text = "Por lo general, la gente se sorprende o asusta en tales situaciones, pero tú pareces ser de otro tipo. Será aún más placentero borrar esa sonrisa engreída de tu cara, Sr. de Maure.";
		link.l1 = "¡Qué amenazas! ¿No estamos del mismo lado, Peter?";
		link.l1.go = "DTSG_PiterAdams_Nastoroje_27";
		break;

	case "DTSG_PiterAdams_Nastoroje_27":
		dialog.text = "No me digas que esperas derrotarnos a todos con ese viejo. Estás en desventaja numérica, mi querido señor.";
		link.l1 = "Como dije, ERES TÚ quien no entiende. Charlie refunfuñó un poco, pero aún así le dije que trajera a los muchachos aquí por si acaso. Resulta que no fue en vano. ¡¡¡CHICOS, VENID AQUÍ!!!";
		link.l1.go = "DTSG_PiterAdams_Nastoroje_28";
		break;

	case "DTSG_PiterAdams_Nastoroje_28":
		DialogExit();

		StartQuestMovie(true, false, true);
		locCameraFromToPos(0.34, 0.51, 34.93, true, -5.63, -1.20, 57.46);
		DoQuestCheckDelay("DTSG_PoP_Duel_Podkreplenie", 3.0);

		int DTSG_PoP_MK;
		if (MOD_SKILL_ENEMY_RATE == 2)
			DTSG_PoP_MK = 5;
		if (MOD_SKILL_ENEMY_RATE == 4)
			DTSG_PoP_MK = 5;
		if (MOD_SKILL_ENEMY_RATE == 6)
			DTSG_PoP_MK = 4;
		if (MOD_SKILL_ENEMY_RATE == 8)
			DTSG_PoP_MK = 4;
		if (MOD_SKILL_ENEMY_RATE == 10)
			DTSG_PoP_MK = 3;

		for (i = 1; i <= DTSG_PoP_MK; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_PoP_Matrosy_" + i, "citiz_3" + i, "man", "man", sti(pchar.rank) - 5, sti(pchar.nation), -1, false, "quest"));
			GiveItem2Character(sld, "blade_11");
			sld.equip.blade = "blade_11";
			ChangeCharacterAddressGroup(sld, pchar.location, "reload", "reload3");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
			sld.lifeday = 0;
			LAi_SetHP(sld, 120.0, 120.0);
		}
		break;

	case "DTSG_PiterAdams_Nastoroje_29":
		dialog.text = "¿Qué?..";
		link.l1 = "¿Sorprendido y asustado, señor Adams? Bueno saberlo.";
		link.l1.go = "DTSG_PiterAdams_BitvaDuel";
		SetCameraDialogMode(npchar);
		break;

	case "DTSG_PiterAdams_BitvaDuel":
		DialogExit();
		LAi_LocationFightDisable(&Locations[FindLocation("PortPax_ExitTown")], false);
		LAi_SetFightMode(pchar, true);

		for (i = 1; i <= 5; i++)
		{
			if (GetCharacterIndex("DTSG_PoP_Matrosy_" + i) != -1)
			{
				sld = CharacterFromID("DTSG_PoP_Matrosy_" + i);
				LAi_SetWarriorType(sld);
				LAi_CharacterDisableDialog(sld);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
		}

		sld = CharacterFromID("Knippel");
		LAi_SetWarriorType(sld);
		LAi_SetCheckMinHP(sld, 10, true, "KnippelRanen");
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);

		sld = CharacterFromID("DTSG_PiterAdams");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");

		sld = CharacterFromID("DTSG_FrederikStouks");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");

		sld = CharacterFromID("DTSG_RalfFaggl2");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");

		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		LAi_group_SetCheck("EnemyFight", "DTSG_PiterAdams_Duel_Pobeda");
		break;

	case "DTSG_Knippel_60":
		dialog.text = "Así es como deberías tratar con esos bribones mentirosos. ¡Todavía no puedo creer que tuvieran el descaro de mentir sobre la Armada Real! ¡Los estrangularía con una bala encadenada!..";
		link.l1 = "Para ahora, deberías saber que algunas personas no tienen escrúpulos, Charlie. Dije que me encargaría de ello, podrías haberte quedado en el barco. ¿Querías asegurarte de que ayudaría a estas 'personas dignas'? ¿Y quién tenía razón de nuevo, que no era tan sencillo como pensabas?";
		link.l1.go = "DTSG_Knippel_61";
		break;

	case "DTSG_Knippel_61":
		dialog.text = "Tú, señor...";
		link.l1 = "Exactamente. Pero dime, ¿por qué alguien querría cazarte? No es la primera vez.";
		link.l1.go = "DTSG_Knippel_62";
		break;

	case "DTSG_Knippel_62":
		dialog.text = "No lo sé, Capitán. El viejo Charlie es solo un simple artillero.";
		link.l1 = "Hmm, bueno, bueno. Está bien, ya que nuestros pobres duelistas no tenían nada útil con ellos... No, vamos a ver si podemos encontrar algo en la casa de Adams.";
		link.l1.go = "DTSG_Knippel_63";
		break;

	case "DTSG_Knippel_63":
			DialogExit();
			
			LAi_RemoveCheckMinHP(npchar);
			LAi_SetImmortal(npchar, false);
			AddDialogExitQuestFunction("DTSG_Knippel_64");
		break;

	case "DTSG_Knippel_70":
		dialog.text = "Entonces, esta mujer también ha desaparecido... ¿Quizás estaban preparándose para huir de la ciudad justo después de ese 'duelo'? ¡Y con prisa, tanto oro aquí!";
		link.l1 = "Tienes razón, porque el oro no es lo único que dejaron atrás. Otra carta. Tenían tanta prisa que olvidaron quemarla. Mira, te gustará su contenido.";
		link.l1.go = "DTSG_Knippel_71";
		break;

	case "DTSG_Knippel_71":
		TakeItemFromCharacter(pchar, "letter_1");
		dialog.text = "(lee) Bueno, discutiría sobre 'viejo'.";
		link.l1 = "Eso no es el punto ahora. Esta es la segunda vez que te envían mercenarios y les proporcionan dinero e información. Y te quieren a ti específicamente. Dime, simple artillero, ¿a quién podrías haber enfurecido tanto?";
		link.l1.go = "DTSG_Knippel_72";
		break;

	case "DTSG_Knippel_72":
		dialog.text = "Tengo una suposición, señor, solo una, y realmente no quiero que sea cierta.";
		link.l1 = "Entonces, lo más probable es que sea cierto. Habla.";
		link.l1.go = "DTSG_Knippel_73";
		break;

	case "DTSG_Knippel_73":
		dialog.text = "Una vez tuve deudas con varias personas en St. John's, y...";
		link.l1 = " ... ¿y ahora crees que te están cazando? ¿Cuántos pueden permitirse mercenarios y tales sumas?";
		link.l1.go = "DTSG_Knippel_74";
		break;

	case "DTSG_Knippel_74":
		dialog.text = "Está pensando correctamente, señor. Al final, pagué casi todas mis deudas pidiendo prestado a un prestamista. Él puede permitirse todo esto, por supuesto. Pero...";
		link.l1 = "¿Pero qué? Pagaremos tu deuda, y eso es todo. ¿Qué te preocupa?";
		link.l1.go = "DTSG_Knippel_75";
		break;

	case "DTSG_Knippel_75":
		dialog.text = "Verá, Capitán, Richard me prometió que lo pagaría por mí.";
		link.l1 = "¿Crees que no lo hizo?";
		link.l1.go = "DTSG_Knippel_76";
		break;

	case "DTSG_Knippel_76":
		dialog.text = "No sé qué pensar ya, señor. Todo el tiempo que nos conocimos, lo consideré un caballero ejemplar. Pero después de que te dejó y huyó con Abigail... no me sorprendería. Por eso dije que no querría que fuera cierto.";
		link.l1 = "Adivinanzas deben comprobarse primero, luego puedes enfadarte, Charlie. Vamos, volverás a San Juan.";
		link.l1.go = "DTSG_Knippel_77";
		break;

	case "DTSG_Knippel_77": // КОНЕЦ ЭТАПА 2
		DialogExit();

		bDisableFastReload = false;
		chrDisableReloadToLocation = false;

		LAi_SetActorType(npchar);
		LAi_ActorFollow(npchar, pchar, "", -1);
		LAi_SetOfficerType(npchar);
		npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
		npchar.Dialog.CurrentNode = "Knippel_officer";
		npchar.location = "None";

		n = Findlocation("PortPax_town");
		locations[n].reload.l31.name = "houseF1";
		locations[n].reload.l31.go = "CommonRoom_MH9";
		locations[n].reload.l31.emerge = "reload1";
		locations[n].reload.l31.autoreload = "0";
		locations[n].reload.l31.label = "House";

		BackItemName("letter_1");
		BackItemDescribe("letter_1");
		AddQuestRecord("DTSG", "6");
		QuestOpenSeaExit()
			LAi_LocationDisableOfficersGen("PortPax_town", false);
		LAi_LocationDisableOfficersGen("PortPax_ExitTown", false);

		AddMapQuestMarkCity("SentJons", true);
		PChar.quest.DTSG_Etap3_Start.win_condition.l1 = "location";
		PChar.quest.DTSG_Etap3_Start.win_condition.l1.location = "Antigua";
		PChar.quest.DTSG_Etap3_Start.win_condition = "DTSG_Etap3_Start";
		break;

	case "DTSG_Knippel_PoPDuelTime":
		dialog.text = "¡Capitán!!!";
		link.l1 = "¿Qué pasa, Charlie, qué sucedió?";
		link.l1.go = "DTSG_Knippel_PoPDuelTime_2";
		break;

	case "DTSG_Knippel_PoPDuelTime_2":
		dialog.text = "¿¡Ocurrió?! ¡No me digas que olvidaste el duelo, señor! ¡Adams ya podría estar hecho pedazos mientras tú te holgazaneas aquí!";
		link.l1 = "¡Correcto!.. Saldré de la ciudad de inmediato.";
		link.l1.go = "DTSG_Knippel_PoPDuelTime_3";
		break;

	case "DTSG_Knippel_PoPDuelTime_3":
		DialogExit();
		npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
		npchar.Dialog.CurrentNode = "Knippel_officer";
		DoQuestReloadToLocation("PortPax_ExitTown", "reload", "reload3", "");
		break;

	case "DTSG_AntiguaArest":
		dialog.text = "¿Capitán Charles de Maure? ¿Es ese Charlie Knippel contigo?";
		link.l1 = "No, esto...";
		link.l1.go = "DTSG_AntiguaArest_2";
		break;

	case "DTSG_AntiguaArest_2":
		dialog.text = "No lo niegues, señor - todos en esta colonia conocen a Charlie.";
		link.l1 = "Entonces, ¿por qué preguntas? ¿Cómo puedo ayudar?";
		link.l1.go = "DTSG_AntiguaArest_3";
		break;

	case "DTSG_AntiguaArest_3":
		dialog.text = "No puedes. Por favor, no te resistas - Charlie es buscado aquí. Tenemos que llevarlo bajo custodia.";
		link.l1 = "¿Puedo saber de qué se acusa a mi hombre? ¿Es por su deuda? Puedo pagarla por él. Vamos al banquero ahora mismo, en tu presencia.";
		link.l1.go = "DTSG_AntiguaArest_4";
		break;

	case "DTSG_AntiguaArest_4":
		dialog.text = "¿Una deuda? Es la primera vez que oigo hablar de eso. No conozco los detalles, pero por favor, no compliques las cosas - solo sigo órdenes.";
		link.l1 = "Oh, eso es simplemente genial...";
		link.l1.go = "DTSG_AntiguaArest_5";
		break;

	case "DTSG_AntiguaArest_5":
		StartInstantDialog("Knippel", "DTSG_AntiguaArest_6", "Quest\CompanionQuests\Knippel.c");
		break;

	case "DTSG_AntiguaArest_6":
		dialog.text = "Capitán...";
		link.l1 = "¡Charlie, si huimos ahora, la recompensa por nuestras cabezas será aún mayor! ¿Y no podemos abrirnos paso luchando? Intentaré sacarte de aquí, ¡solo no hagas nada estúpido!";
		link.l1.go = "DTSG_AntiguaArest_7";
		break;

	case "DTSG_AntiguaArest_7":
		DialogExit();

		bDisableFastReload = false;
		chrDisableReloadToLocation = false;
		AddQuestRecord("DTSG", "8");
		pchar.questTemp.DTSG_KnippelDolg = true;

		sld = CharacterFromID("Knippel");
		RemovePassenger(pchar, sld);
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload_jail", "", "", "", "", -1);
		sld.location = "None";

		for (i = 1; i <= 3; i++)
		{
			sld = CharacterFromID("DTSG_AntiguaSold_" + i);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload_jail", "", "", "", "", -1);
			sld.location = "None";
		}
		break;

	case "DTSG_AntiguaStrazhBank":
		dialog.text = "¡Deje de hacer ruido y amenazar a este hombre de inmediato, señor! ¡Entregue sus armas y sígame en este instante!";
		link.l1 = "No amenacé a nadie, ha habido un error. Esto es un asunto de negocios, no un intento de asesinato.";
		link.l1.go = "DTSG_AntiguaStrazhBank_2";
		break;

	case "DTSG_AntiguaStrazhBank_2":
		dialog.text = "No me lo parece. Tendrás que responder ante la ley.";
		link.l1 = "¿Y si me disculpo y me voy?";
		link.l1.go = "DTSG_AntiguaStrazhBank_3";
		break;

	case "DTSG_AntiguaStrazhBank_3":
		dialog.text = "¿Para que puedas escabullirte de nuevo y terminar lo que interrumpí? ¿Crees que soy estúpido?";
		link.l1 = "Debes estarlo si no quieres resolver esto pacíficamente. Dios sabe que no quería que llegara a esto...";
		link.l1.go = "DTSG_AntiguaStrazhBank_4";
		break;

	case "DTSG_AntiguaStrazhBank_4":
		DialogExit();
		bDisableFastReload = true;
		chrDisableReloadToLocation = true;

		LAi_LocationFightDisable(&Locations[FindLocation("SentJons_bank")], false);
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		LAi_SetFightMode(pchar, true);
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		LAi_group_SetCheck("EnemyFight", "DTSG_AntiguaStrazhBank_Ubili");
		break;

	case "DTSG_AntiguaUsurer_PosleDraki":
		dialog.text = "¡Lo mataste!..";
		link.l1 = "Considérelo hecho por sus propias manos, señor. Podría haber respondido a mis preguntas en lugar de ponerse histérico. Lo juro, un grito más y te volaré los sesos.";
		link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_V1";
		link.l2 = "Sí, lo maté. Me obligó a hacerlo. Pero tú no eres tan descerebrado como él y no seguirás su ejemplo, ¿verdad?";
		link.l2.go = "DTSG_AntiguaUsurer_PosleDraki_V2";
		break;

	case "DTSG_AntiguaUsurer_PosleDraki_V1":
		dialog.text = "¿Qué quieres?!";
		link.l1 = "Hace algún tiempo, Charlie Knippel te pidió prestado dinero. Su amigo prometió saldar su deuda, pero aparentemente no lo hizo. Exijo que dejes de enviar mercenarios tras nosotros inmediatamente. Estoy listo para pagar la deuda de Charlie ahora mismo si puedo permitírmelo.";
		link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_3";
		AddComplexLandExpToScill(100, 0, 0);
		AddComplexSeaExpToScill(0, 0, 0, 0, 0, 0, 100);
		break;

	case "DTSG_AntiguaUsurer_PosleDraki_V2":
		dialog.text = "¿Qué quieres?!";
		link.l1 = "Hace algún tiempo, Charlie Knippel te pidió dinero prestado. Su amigo prometió pagar su deuda pero aparentemente no lo hizo. Exijo que dejes de enviarnos mercenarios de inmediato. Estoy listo para pagar la deuda de Charlie ahora mismo si puedo permitírmelo.";
		link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_3";
		AddComplexSelfExpToScill(50, 50, 50, 50);
		break;

	case "DTSG_AntiguaUsurer_PosleDraki_3":
		dialog.text = "¡¿Charlie?! Nunca le haría eso; es un hombre bueno y honesto. Además, hace tiempo que saldó su deuda. El Sr. Fleetwood, el capitán del Valkyrie, la saldó hasta el último peso.";
		link.l1 = "¿De veras? Sé quién es. Deberías haberlo dicho de inmediato. Perdona las molestias, adiós.";
		link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_4";
		break;

	case "DTSG_AntiguaUsurer_PosleDraki_4":
		dialog.text = "¿Así nomás?! ¡Me amenazaste! ¡Y mataste a un hombre!..";
		link.l1 = "¿Olvidaste lo que dije? Un grito más y te unirás a él. Adiós.";
		link.l1.go = "DTSG_AntiguaUsurer_PosleDraki_5";
		break;

	case "DTSG_AntiguaUsurer_PosleDraki_5":
		DialogExit();

		LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
		LAi_LocationFightDisable(&Locations[FindLocation("SentJons_bank")], true);
		// LAi_LocationDisableOfficersGen("SentJons_town", false);
		LAi_LocationDisableOfficersGen("SentJons_bank", false);
		npchar.dialog.filename = "Usurer_dialog.c";
		npchar.dialog.currentnode = "First time";
		LAi_SetOwnerType(npchar);

		ChangeCharacterComplexReputation(pchar, "nobility", -2);
		ChangeCharacterComplexReputation(pchar, "fame", 2);

		chrDisableReloadToLocation = false;
		AddQuestRecord("DTSG", "9");
		PChar.quest.DTSG_AntiguaTrevoga.win_condition.l1 = "location";
		PChar.quest.DTSG_AntiguaTrevoga.win_condition.l1.location = "SentJons_town";
		PChar.quest.DTSG_AntiguaTrevoga.win_condition = "DTSG_AntiguaTrevoga";
		break;

	case "DTSG_Killer":
		dialog.text = "¿Todavía aquí y no colgado todavía? Bueno, saludos desde el Sussex, Charlie.";
		link.l1 = "Saludos a ti, quienquiera que seas.";
		link.l1.go = "DTSG_Killer_2";
		CharacterTurnToLoc(npchar, "goto", "goto9");
		break;

	case "DTSG_Killer_2":
		dialog.text = "Ah, Charles de Maure. Qué bueno que viniste a ver al pobre Charlie. Contábamos con eso.";
		link.l1 = "¿Quiénes somos?";
		link.l1.go = "DTSG_Killer_3";
		CharacterTurnByChr(npchar, pchar);
		break;

	case "DTSG_Killer_3":
		dialog.text = "No importa. Nos has costado tiempo y dinero significativo, señor de Maure. Creo que no les importará si trato con Charlie y contigo aquí mismo.";
		link.l1 = "Bueno, ya que ambos estamos muertos de todos modos, ¿podrías decirnos por bondad de tu corazón a quién hemos enfurecido tanto? Prometemos no hacerlo de nuevo. ¿Y quién es Sussex?";
		link.l1.go = "DTSG_Killer_4";
		break;

	case "DTSG_Killer_4":
		dialog.text = "No puedo. El deber llama y, a diferencia de ti, soy un hombre de acción, no de palabras.";
		link.l1 = "¡Por el amor de Dios, ¿alguien me explicará alguna vez qué demonios está pasando?!";
		link.l1.go = "DTSG_Killer_5";
		break;

	case "DTSG_Killer_5":
		DialogExit();
		LAi_SetFightMode(pchar, true);

		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		LAi_SetImmortal(npchar, false);

		for (i = 1; i <= 12; i++)
		{
			if (GetCharacterIndex("SentJonsPrisoner_" + i) != -1)
			{
				sld = CharacterFromID("SentJonsPrisoner_" + i);
				sld.lifeday = 0;
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
		}

		for (i = 0; i < MAX_CHARACTERS; i++)
		{
			sld = GetCharacter(i);
			if (sld.city == "sentjons" && sld.location == "SentJons_prison")
			{
				sld.lifeday = 0;
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
		}

		sld = CharacterFromID("SentJonsJailOff");
		sld.lifeday = 0;
		ChangeCharacterAddressGroup(sld, "none", "", "");

		sld = GetCharacter(NPC_GenerateCharacter("DTSG_SentJonsJailOff", "off_eng_1", "man", "man", 30, PIRATE, 0, true, "soldier"));
		ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto18");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		sld.rank = 30;
		SetSelfSkill(sld, 80, 80, 80, 80, 80);
		LAi_SetHP(sld, 200 + MOD_SKILL_ENEMY_RATE * 20, 200 + MOD_SKILL_ENEMY_RATE * 20);

		for (i = 1; i <= 3; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_AntiguaSoldTurma_" + i, "sold_eng_" + (rand(15) + 1), "man", "man", sti(pchar.rank), PIRATE, 0, true, "soldier"));
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "goto", "goto22");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}

		for (i = 4; i <= 7; i++)
		{
			sld = GetCharacter(NPC_GenerateCharacter("DTSG_AntiguaSoldTurma_" + i, "sold_eng_" + (rand(15) + 1), "man", "man", sti(pchar.rank), PIRATE, 0, true, "soldier"));
			ChangeCharacterAddressGroup(sld, "SentJons_prison", "reload", "reload1");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}

		/*sld = CharacterFromID("SentJons_Mayor");
		LAi_group_Attack(sld, Pchar);*/

		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		LAi_group_SetCheck("EnemyFight", "DTSG_TurmaDayPobeda");
		break;

	case "DTSG_KnippelDaySpasen":
		dialog.text = "¡Pues, que me lleve el diablo, Capitán, qué masacre has hecho aquí!";
		link.l1 = "¿Te opones? ¿Prefieres la horca? ¿O tal vez pudrirte aquí indefinidamente?";
		link.l1.go = "DTSG_KnippelDaySpasen_2";
		DelLandQuestMark(npchar);
		break;

	case "DTSG_KnippelDaySpasen_2":
		dialog.text = "No, señor. Gracias por rescatarme. Para ser honesto, me sorprende que viniera, considerando lo fácilmente que me dejó llevar. Y sorprendido de lo fácilmente que se encargó del guardia - era un Zorro de Mar. Un infante de marina.";
		link.l1 = "Te dije que te sacaría, no debiste haber dudado. Ahora sal de esta celda antes de que llegue toda la guarnición.";
		link.l1.go = "DTSG_KnippelDaySpasen_3";
		break;

	case "DTSG_KnippelDaySpasen_3":
		dialog.text = "Sí, sí, Capitán.";
		link.l1 = "";
		link.l1.go = "DTSG_KnippelDaySpasen_4";
		break;

	case "DTSG_KnippelDaySpasen_4":
		DialogExit();

		Pchar.GenQuest.Hunter2Pause = true;
		LAi_SetActorType(pchar);
		DoQuestCheckDelay("DTSG_TurmaDayPobeda_2", 1.0);
		break;

	case "DTSG_KnippelDaySpasen_5":
		dialog.text = "Mierda, señor, apenas puedo creerlo...";
		link.l1 = "Por cierto, dime, ¿de qué te acusaron? ¿Y quién es Sussex?";
		link.l1.go = "DTSG_KnippelDaySpasen_6";
		break;

	case "DTSG_KnippelDaySpasen_6":
		dialog.text = "No lo sé, señor. No tengo idea a quién se referían con eso...";
		link.l1 = "De acuerdo, lo descubriremos más tarde. Ahora necesitamos salir de aquí.";
		link.l1.go = "DTSG_KnippelDaySpasen_7";
		break;

	case "DTSG_KnippelDaySpasen_7":
		DialogExit();

		ChangeCharacterComplexReputation(pchar, "nobility", 2);
		ChangeCharacterComplexReputation(pchar, "authority", 2);
		LAi_SetActorType(npchar);
		LAi_ActorFollow(npchar, pchar, "", -1);
		AddPassenger(pchar, npchar, false);
		LAi_SetOfficerType(npchar);
		npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
		npchar.Dialog.CurrentNode = "Knippel_officer";
		npchar.location = "None";
		AddQuestRecord("DTSG", "12");

		PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition.l1 = "EnterToSea" PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition = "DTSG_KnippelRazgovorVKaute";
		break;

	case "DTSG_AntiguaNightPirs":
		dialog.text = "¿Cuáles son sus próximos pasos, señor? Golpear a ese chupasangre a plena luz del día es un negocio arriesgado.";
		link.l1 = "Acabas de darme una idea. ¿Por qué sacudirle el sentido a plena luz del día cuando podemos hacerlo ahora, al amparo de la noche?";
		link.l1.go = "DTSG_AntiguaNightPirs_2";
		break;

	case "DTSG_AntiguaNightPirs_2":
		dialog.text = "¡Maldita sea, eso es una idea brillante, capitán!";
		link.l1 = "Exactamente. Dime, Charlie, viviste aquí por un tiempo. ¿Sabes dónde vive el prestamista?";
		link.l1.go = "DTSG_AntiguaNightPirs_3";
		break;

	case "DTSG_AntiguaNightPirs_3":
		dialog.text = "Solía saberlo, señor, pero la última vez que estuve aquí, él estaba vendiendo su casa. No tengo idea de dónde está la nueva.";
		link.l1 = "Bueno, eso es un problema...";
		link.l1.go = "DTSG_AntiguaNightPirs_4";
		break;

	case "DTSG_AntiguaNightPirs_4":
		dialog.text = "¡Estoy seguro de que encontrarás algo, Capitán, después de todo, derrotaste al gran y temible Lucas Rodenburg!";
		link.l2 = "Está bien, yo me encargaré. ¡Aunque, si supieras dónde está la casa del prestamista, sería mejor!";
		link.l2.go = "DTSG_AntiguaIskat_1";
		link.l1 = "Eso hice. Pero la mañana es más sabia que la noche, Charlie. Descansemos del viaje y vayamos de día - no estamos aquí para asesinar al hombre, después de todo.";
		link.l1.go = "DTSG_AntiguaSpat_1";
		break;

	case "DTSG_AntiguaSpat_1":
		dialog.text = "¿Está seguro de eso, señor? Perderemos el elemento de sorpresa.";
		link.l1 = "Estoy seguro y estoy cansado. Además, solo quiero hablar. Asustarlo un poco si es necesario.";
		link.l1.go = "DTSG_AntiguaSpat_2";
		break;

	case "DTSG_AntiguaSpat_2":
		TavernWaitDate("wait_day");
		DoQuestReloadToLocation("SentJons_tavern_upstairs", "goto", "goto2", "DTSG_AntiguaSpat_3");
		break;

	case "DTSG_AntiguaIskat_1":
		dialog.text = "Lo que no sé - no lo sé, lo siento, señor.";
		link.l1 = "Ah, no importa, vamos a buscarlo.";
		link.l1.go = "DTSG_AntiguaIskat_2";
		break;

	case "DTSG_AntiguaIskat_2":
		DialogExit();

		LAi_SetActorType(npchar);
		LAi_ActorFollow(npchar, pchar, "", -1);
		LAi_SetOfficerType(npchar);
		npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
		npchar.Dialog.CurrentNode = "Knippel_officer";

		AddQuestRecord("DTSG", "13");
		pchar.questTemp.DTSG_NightIskat = true;
		bDisableFastReload = false;
		chrDisableReloadToLocation = false;
		pchar.GenQuest.CannotWait = true;
		pchar.questTemp.TimeLock = true;
		break;

	case "DTSG_Knippel_SluhSmertFleetWood":
		dialog.text = "¿Está pensando lo mismo que yo, señor?";
		link.l1 = "Me temo que sí, Charlie. No hay otro capitán famoso con ese nombre en el Caribe. Y Richard fue a Londres. Así que, es poco probable que sea una coincidencia.";
		link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_2";
		break;

	case "DTSG_Knippel_SluhSmertFleetWood_2":
		dialog.text = "Terrible... ¡Aunque dije muchas palabras duras sobre él, nunca le deseé algo así! ¡Y la pobre Abi!.. Ella estaba esperando un hijo. Espero que esté viva...";
		link.l1 = "En efecto, no se lo desearía a nadie. Esperemos que Abi esté bien. ¿Alguna idea de quién podría haberle hecho esto a Dick? ¿Algún enemigo poderoso del que él haya hablado alguna vez?";
		link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_3";
		break;

	case "DTSG_Knippel_SluhSmertFleetWood_3":
		dialog.text = "Debes estar bromeando, Capitán. No sé sobre Europa, pero aquí cada holandés quería muerto a Richard.";
		link.l1 = "Verdad. Quizás alguien aquí gastó mucho y envió asesinos tras él al Viejo Mundo. ¿Podría ser que no sea este mezquino prestamista quien está detrás de los ataques contra ti, sino algún enemigo misterioso de Richard?";
		link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_4";
		break;

	case "DTSG_Knippel_SluhSmertFleetWood_4":
		dialog.text = "No lo sé, señor. Cualquier cosa es posible en este momento. Pero eso complicaría las cosas para todos nosotros...";
		link.l1 = "Sí, tienes razón, a mí tampoco me gusta esta posibilidad.";
		link.l1.go = "DTSG_Knippel_SluhSmertFleetWood_5";
		break;

	case "DTSG_Knippel_SluhSmertFleetWood_5":
		DialogExit();
		npchar.location = "None";

		AddQuestRecord("DTSG", "14");
		pchar.questTemp.DTSG_Nastoroje2 = true;
		chrDisableReloadToLocation = false;

		PChar.quest.DTSG_NightDom.win_condition.l1 = "locator";
		PChar.quest.DTSG_NightDom.win_condition.l1.location = "SentJons_town";
		PChar.quest.DTSG_NightDom.win_condition.l1.locator_group = "reload";
		PChar.quest.DTSG_NightDom.win_condition.l1.locator = "houseSp3";
		PChar.quest.DTSG_NightDom.win_condition = "DTSG_NightDom";
		break;

	case "DTSG_NightRostovshik":
		dialog.text = "¿Qué, quién... QUÉ?! ¿Qué está pasando?.. ¿Quién eres tú?!..";
		link.l1 = "Oh, vamos. Si quisiera matarte, lo haría mientras duermes. Así que no compliquemos ni acortemos nuestras vidas. Asiente si entiendes.";
		link.l1.go = "DTSG_NightRostovshik_2";
		DelLandQuestMark(npchar);
		break;

	case "DTSG_NightRostovshik_2":
		dialog.text = "Ajá...";
		link.l1 = "Muy bien. Cálmate - no estoy aquí para robar, secuestrar o hacerte daño.";
		link.l1.go = "DTSG_NightRostovshik_3";
		break;

	case "DTSG_NightRostovshik_3":
		dialog.text = "Entonces... ¿por qué estás aquí? ¿Por qué no pudiste venir por la mañana?";
		link.l1 = "Porque algún ricachón influyente está cazando a mi amigo. Tenemos razones para creer que eres tú, así que es probable que sea peligroso para él caminar por estas calles a plena luz del día.";
		link.l1.go = "DTSG_NightRostovshik_4";
		break;

	case "DTSG_NightRostovshik_4":
		dialog.text = "Pero realmente no entiendo de qué está hablando, señor...";
		link.l1 = "Charlie Knippel. Todos en el pueblo lo conocen. Piensa bien. Te debe dinero.";
		link.l1.go = "DTSG_NightRostovshik_5";
		break;

	case "DTSG_NightRostovshik_5":
		dialog.text = "¿Nuestro viejo Charlie?? Eso es cierto, pero su deuda fue pagada hace mucho tiempo, aunque no por él personalmente.";
		link.l1 = "¿Y quién fue este benefactor?";
		link.l1.go = "DTSG_NightRostovshik_6";
		break;

	case "DTSG_NightRostovshik_6":
		dialog.text = "Su capitán, lord Richard Fleetwood. Si no me crees, puedo mostrarte mis registros.";
		link.l1 = "¿Fleetwood, dices? Entonces te creo. ¿Así que no enviaste mercenarios tras Charlie?";
		link.l1.go = "DTSG_NightRostovshik_7";
		break;

	case "DTSG_NightRostovshik_7":
		dialog.text = "Por supuesto que no, ¿por qué lo haría?? Y dime, ¿qué sentido tendría?";
		link.l1 = "En efecto. Bueno, disculpa por la visita tardía. Buenas noches.";
		link.l1.go = "DTSG_NightRostovshik_8";
		break;

	case "DTSG_NightRostovshik_8":
		DialogExit();

		PChar.quest.DTSG_NightDom_3.win_condition.l1 = "locator";
		PChar.quest.DTSG_NightDom_3.win_condition.l1.location = "SentJons_houseSP3";
		PChar.quest.DTSG_NightDom_3.win_condition.l1.locator_group = "reload";
		PChar.quest.DTSG_NightDom_3.win_condition.l1.locator = "reload1";
		PChar.quest.DTSG_NightDom_3.win_condition = "DTSG_NightDom_3";

		LAi_CharacterDisableDialog(npchar);
		Pchar.GenQuest.Hunter2Pause = true;
		AddQuestRecord("DTSG", "15");
		break;

	case "DTSG_NightKiller":
		dialog.text = "¿Qué, Charlie, esperabas esconderte con tu antiguo patrón esta noche? No está allí. Pero lo encontrarás pronto. Saludos del Sussex.";
		link.l1 = "Ya lo sabíamos. ¿Y quién es Sussex? ¿Y quién eres tú?";
		link.l1.go = "DTSG_NightKiller_2";
		break;

	case "DTSG_NightKiller_2":
		dialog.text = "Eso no es asunto suyo, Sr. de Maure. Es una pena que se haya involucrado en este lío más de lo que nos gustaría. Es usted una molestia.";
		link.l1 = "¿Una molestia para quién? Por favor, no me digas que me acosté con la esposa de un inglés muy influyente y muy enojado.";
		link.l1.go = "DTSG_NightKiller_3";
		break;

	case "DTSG_NightKiller_3":
		dialog.text = "Muy gracioso. Encontraste tiempo para bromear. Aparentemente, lo que he escuchado sobre ti es cierto\n¿Qué queremos? La cabeza de Charlie sería suficiente. Pero considerando cuántos problemas nos has causado, esta vez te concierne a ti también: sigues metiendo las narices donde no te llaman.";
		link.l1 = "¿Supongo que estamos arrestados?";
		link.l1.go = "DTSG_NightKiller_4";
		break;

	case "DTSG_NightKiller_4":
		dialog.text = "¿Arresto? No, buen señor, el tiempo para las medias tintas ha terminado. Esto es una ejecución, Capitán de Maure.";
		link.l1 = "De acuerdo. La única pregunta es, de quién.";
		link.l1.go = "DTSG_NightKiller_5";
		break;

	case "DTSG_NightKiller_5":
		DialogExit();
		LAi_LocationFightDisable(&Locations[FindLocation("SentJons_town")], false);
		LAi_SetFightMode(pchar, true);
		sld = CharacterFromID("Knippel");
		LAi_SetOfficerType(sld);
		for (i = 1; i <= 4; i++)
		{
			sld = CharacterFromID("DTSG_Killers_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		LAi_group_SetCheck("EnemyFight", "DTSG_NightKiller_Pobeda");
		break;

	case "DTSG_Knippel_80":
		dialog.text = "No pensé que los Zorros del Mar estarían involucrados...";
		link.l1 = "Bueno, siempre hay una primera vez para todo. Dime, Charlie, ¿quién es Sussex?";
		link.l1.go = "DTSG_Knippel_81";
		break;

	case "DTSG_Knippel_81":
		dialog.text = "Yo...";
		link.l1 = "¿No ves hasta dónde ha llegado esto? Y parece que estamos en el mismo barco, Charlie. Así que tengo derecho a conocer los detalles.";
		link.l1.go = "DTSG_Knippel_82";
		break;

	case "DTSG_Knippel_82":
		dialog.text = "Por supuesto, Capitán. Pero no aquí, ¿verdad? Vamos a salir de la isla y hablar en el barco.";
		link.l1 = "Tienes razón. Está bien, apresurémonos.";
		link.l1.go = "DTSG_Knippel_83";
		break;

	case "DTSG_Knippel_83":
		DialogExit();
		AddQuestRecord("DTSG", "16");
		DeleteAttribute(pchar, "GenQuest.CannotWait");
		DeleteAttribute(pchar, "questTemp.TimeLock");
		chrDisableReloadToLocation = false;
		// LAi_LocationDisableOfficersGen("SentJons_town", false);
		LAi_LocationDisableOfficersGen("SentJons_bank", false);

		sld = CharacterFromID("Knippel");
		LAi_SetActorType(sld);
		LAi_ActorFollow(sld, pchar, "", -1);
		LAi_SetOfficerType(npchar);
		npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
		npchar.Dialog.CurrentNode = "Knippel_officer";

		PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition.l1 = "EnterToSea" PChar.quest.DTSG_KnippelRazgovorVKaute.win_condition = "DTSG_KnippelRazgovorVKaute";
		break;

	case "DTSG_KnippelRazgovorOProshlom":
		dialog.text = "¿Llamó, Capitán?";
		link.l1 = "Sí, Charlie. Necesitamos hablar. Creo que ya adivinaste de qué se trata.";
		link.l1.go = "DTSG_KnippelRazgovorOProshlom_2";
		DelLandQuestMark(npchar);
		// LAi_LocationDisableOfficersGen("SentJons_town", true);
		break;

	case "DTSG_KnippelRazgovorOProshlom_2":
		dialog.text = "Sí, señor...";
		link.l1 = "Bien. Dime por qué tus compatriotas, incluidas las fuerzas de élite, te están cazando cuando no eres un criminal ni nada por el estilo.";
		link.l1.go = "DTSG_KnippelRazgovorOProshlom_3";
		break;

	case "DTSG_KnippelRazgovorOProshlom_3":
		dialog.text = "Realmente no lo sé, señor...";
		if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
		{
			link.l1 = "Esto no es una broma, Charlie. Quienquiera que te esté cazando puede dar órdenes a los zorros de mar. Probablemente también esté detrás del asesinato de Richard. Así que si tienes alguna idea, compártela. ¿Qué clase de saludos de Sussex, quién es?";
		}
		else
		{
			link.l1 = "Deja de mirar a otro lado, Charlie. Veo que sabes algo. Como tu capitán, te ordeno que me lo cuentes todo. ¿Quién es Sussex?";
		}
		link.l1.go = "DTSG_KnippelRazgovorOProshlom_4";
		break;

	case "DTSG_KnippelRazgovorOProshlom_4":
		dialog.text = "Está bien, Capitán. Sussex no es una persona. Es... un barco.";
		link.l1 = "¿Saludos desde un barco? Eso es un disparate.";
		link.l1.go = "DTSG_KnippelRazgovorOProshlom_5";
		break;

	case "DTSG_KnippelRazgovorOProshlom_5":
		dialog.text = "Déjame explicar. ¿Puedo sentarme, señor? La historia es larga y no muy agradable.";
		link.l1 = "Por supuesto, Charlie. Adelante.";
		link.l1.go = "DTSG_KnippelRazgovorOProshlom_6";
		break;

	case "DTSG_KnippelRazgovorOProshlom_6":
		DialogExit();
		SetCurrentTime(2, 00);
		RecalculateJumpTable();
		RefreshWeather();
		RefreshLandTime();
		SetMainCharacterIndex(GetCharacterIndex("Knippel"));
		PChar = GetMainCharacter();
		LAi_SetPlayerType(PChar);
		DoQuestReloadToLocation("SentJons_houseH1", "goto", "goto2", "DTSG_KnippelDoma");
		break;

	case "DTSG_Kurier":
		dialog.text = "Hola, Charlie, soy del Capitán Fleetwood. Quiere verte.";
		link.l1 = "Gracias, amigo. ¿Pasó algo? Por lo general, te envía todo de inmediato.";
		link.l1.go = "DTSG_Kurier_2";
		break;

	case "DTSG_Kurier_2":
		dialog.text = "No sé. Dice que quiere discutir esto directamente contigo. Es asunto tuyo, arréglalo tú mismo.";
		link.l1 = "Oh, tengo un mal presentimiento sobre esto...";
		link.l1.go = "DTSG_Kurier_3";
		break;

	case "DTSG_Kurier_3":
		DialogExit();

		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
		npchar.lifeday = 0;
		npchar.location = "None";

		PChar.quest.DTSG_KD1.win_condition.l1 = "locator";
		PChar.quest.DTSG_KD1.win_condition.l1.location = "SentJons_houseH1";
		PChar.quest.DTSG_KD1.win_condition.l1.locator_group = "reload";
		PChar.quest.DTSG_KD1.win_condition.l1.locator = "reload1";
		PChar.quest.DTSG_KD1.win_condition = "DTSG_KD1";

		PChar.quest.DTSG_KD2.win_condition.l1 = "locator";
		PChar.quest.DTSG_KD2.win_condition.l1.location = "SentJons_town";
		PChar.quest.DTSG_KD2.win_condition.l1.locator_group = "reload";
		PChar.quest.DTSG_KD2.win_condition.l1.locator = "houseSp3";
		PChar.quest.DTSG_KD2.win_condition = "DTSG_KD2";

		pchar.questTemp.Knippel.Soldiers_1 = true;
		break;

	case "DTSG_Cortny":
		dialog.text = "...";
		link.l1 = "¡Buenas noches, señor!";
		link.l1.go = "DTSG_Cortny_2";
		break;

	case "DTSG_Cortny_2":
		dialog.text = "Buenas noches. Déjame pasar.";
		link.l1 = "Por supuesto, adelante, me disculpo, señor.";
		link.l1.go = "DTSG_Cortny_3";
		break;

	case "DTSG_Cortny_3":
		DialogExit();

		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
		npchar.lifeday = 0;
		npchar.location = "None";

		PChar.quest.DTSG_KD4.win_condition.l1 = "locator";
		PChar.quest.DTSG_KD4.win_condition.l1.location = "SentJons_houseSP3";
		PChar.quest.DTSG_KD4.win_condition.l1.locator_group = "reload";
		PChar.quest.DTSG_KD4.win_condition.l1.locator = "reload2";
		PChar.quest.DTSG_KD4.win_condition = "DTSG_KD4";

		sld = CharacterFromID("Fleetwood");
		LAi_SetStayType(sld);
		ChangeCharacterAddressGroup(sld, "SentJons_houseSP3_room", "goto", "goto1");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Fleetwood";
		sld.greeting = "";
		AddLandQuestMark(sld, "questmarkmain");
		break;

	case "DTSG_Fleetwood":
		dialog.text = "Ah, eres tú, Charlie. Entra, entra. Cierra la puerta detrás de ti.";
		link.l1 = "Buenas noches, Capitán. ¿Qué está pasando? ¿Y quién era ese hombre? Un pavo real pomposo...";
		link.l1.go = "DTSG_Fleetwood_2";
		DelLandQuestMark(npchar);
		break;

	case "DTSG_Fleetwood_2":
		dialog.text = "Eso, no puedo decir. Tampoco puedo permitir que nadie escuche nuestra conversación. No se lo digas a nadie, ¿entendido?";
		link.l1 = "Sí, señor. ¿Ocurrió algo? Parecéis inusualmente preocupados, eso no es propio de vos.";
		link.l1.go = "DTSG_Fleetwood_3";
		break;

	case "DTSG_Fleetwood_3":
		dialog.text = "Te parece así. Tampoco tienes el mejor aspecto, después de todo es de noche. Pero me temo que tu sueño se ha acabado por esta noche, amigo mío; tenemos una misión urgente y clasificada.";
		link.l1 = "¿Y qué implicará, Capitán?";
		link.l1.go = "DTSG_Fleetwood_4";
		break;

	case "DTSG_Fleetwood_4":
		dialog.text = "Eliminando a un traidor. De los nuestros. Pronto, un barco diplomático del Viejo Mundo aparecerá frente a la costa de Dominica: la fragata 'Sussex'. Oficialmente, deben negociar un buen trato con los holandeses. Pero en realidad...";
		link.l1 = "¿... van a pasar información a nuestros enemigos, señor?";
		link.l1.go = "DTSG_Fleetwood_5";
		break;

	case "DTSG_Fleetwood_5":
		dialog.text = "Aún peor. Desertar completamente a su lado. Y aunque estarán agotados después de cruzar el Atlántico, al final, es una buena fragata que seguramente intentará escapar si atacamos con un barco pesado\nAsí que necesitamos actuar rápida y decisivamente. Solo podemos confiar en la 'Valkyrie' - es la única capaz de tal misión.";
		link.l1 = "¿Podrá la vieja 'Valkyrie' enfrentarse a una fragata?..";
		link.l1.go = "DTSG_Fleetwood_6";
		break;

	case "DTSG_Fleetwood_6":
		dialog.text = "Ja-ja, Charlie, ¿dudas de tu capitán? Además, como dije, estarán exhaustos. Si atacamos de repente, todas las ventajas son nuestras.";
		link.l1 = "¡Jamás lo haría! Pero espero que sepa lo que está haciendo, señor...";
		link.l1.go = "DTSG_Fleetwood_7";
		break;

	case "DTSG_Fleetwood_7":
		dialog.text = "Estoy seguro de ello. Y una cosa más. Este desertor ocupa un alto cargo en el propio Parlamento, ¿entiendes? Puede tener ojos y oídos en todas partes, no solo en casa, sino ya aquí, en el Caribe. Así que no menciones el Sussex ni ningún detalle de nuestra misión en el pueblo.";
		link.l1 = "No tenía que decírmelo, señor. Siempre puede contar con el viejo Charlie.";
		link.l1.go = "DTSG_Fleetwood_8";
		break;

	case "DTSG_Fleetwood_8":
		dialog.text = "Lo sé. Solo que esta vez las apuestas son más altas que nunca. Reúne tus cosas y prepárate: zarpamos al amanecer.";
		link.l1 = "Sí, señor. Buenas noches, señor.";
		link.l1.go = "DTSG_Fleetwood_9";
		break;

	case "DTSG_Fleetwood_9":
		DoQuestReloadToLocation("SentJons_town", "reload", "houseSp3", "");

		PChar.quest.DTSG_KD5.win_condition.l1 = "locator";
		PChar.quest.DTSG_KD5.win_condition.l1.location = "SentJons_town";
		PChar.quest.DTSG_KD5.win_condition.l1.locator_group = "reload";
		PChar.quest.DTSG_KD5.win_condition.l1.locator = "houseH1";
		PChar.quest.DTSG_KD5.win_condition = "DTSG_KD5";
		break;

	case "DTSG_Knippel_SamSoboi":
		dialog.text = " Nunca he visto a Richard así... ¿Estaba tan preocupado o incluso... asustado?";
		link.l1 = "¿Pero por qué? Ni siquiera lo compartió conmigo. Bueno, no importa. Es un gran capitán, así que seguramente manejaremos esta fragata y su tripulación cansada.";
		link.l1.go = "DTSG_Knippel_SamSoboi_2";
		DeleteAttribute(pchar, "questTemp.lockedMusic");
		break;

	case "DTSG_Knippel_SamSoboi_2":
		DialogExit();
		SetLaunchFrameFormParam("17 de agosto de 1654" + NewStr() + ", SE de Dominica", "DTSG_ProshloeDominika", 0, 4.0);
		LaunchFrameForm();
		DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_1");
		DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_2");
		DeleteAttribute(pchar, "questTemp.Knippel.Soldiers_3");
		break;

	case "DTSG_Fleetwood_10":
		dialog.text = "El 'Sussex' está en el horizonte, Charlie, prepárate.";
		link.l1 = "Siempre listo, Capitán.";
		link.l1.go = "DTSG_Fleetwood_11";
		break;

	case "DTSG_Fleetwood_11":
		dialog.text = "Muy bien. Cuento contigo y tus balas encadenadas. Trata de destrozar sus velas lo más rápido posible, o mejor aún, derriba un mástil. Participar en una pelea arriesgada para hundirlos no tiene sentido, así que intentaré abordarlos\nAdemás, necesitamos asegurarnos de que el traidor esté muerto; si los hundimos, aún tendremos que acercarnos y asegurarnos de que nadie sobreviva.";
		link.l1 = "Y matar a tantos compatriotas por un traidor...";
		link.l1.go = "DTSG_Fleetwood_12";
		break;

	case "DTSG_Fleetwood_12":
		dialog.text = "Lamentablemente. A mí también me duele, Charlie. Pero las órdenes son órdenes. Al menos no lo hacemos por diversión. Así que terminemos con esto rápidamente.";
		link.l1 = "Sí, señor...";
		link.l1.go = "DTSG_Fleetwood_13";
		break;

	case "DTSG_Fleetwood_13":
		DialogExit();
		EndQuestMovie();
		AddItems(pchar, "potion4", 10);
		AddItems(pchar, "bullet", 10);
		AddItems(pchar, "GunPowder", 10);
		AddItems(pchar, "grapeshot", 10);
		AddItems(pchar, "cartridge", 10);
		PlaySound("interface\abordage.wav");
		PlaySound("interface\abordage.wav");
		PlaySound("interface\MusketFire1.wav");
		PlaySound("interface\MusketFire1.wav");

		SetLaunchFrameFormParam("2 horas después..." + NewStr() + "A bordo del Sussex", "DTSG_ProshloeDominika_11", 0, 4.0);
		LaunchFrameForm();

		n = Findlocation("Location_reserve_06");
		DeleteAttribute(&locations[n], "IslandId");
		DeleteAttribute(&locations[n], "type");
		DeleteAttribute(&locations[n], "models");
		DeleteAttribute(&locations[n], "environment");
		DeleteAttribute(&locations[n], "Box1");
		DeleteAttribute(&locations[n], "Box2");
		DeleteAttribute(&locations[n], "Box3");
		Locations[n].id.label = "Orlop deck";
		Locations[n].filespath.models = "locations\decks\oldeck";
		Locations[n].image = "loading\Boarding_B" + rand(3) + ".tga";
		// Sound
		locations[n].type = "deck_fight";
		// Models
		// Always
		Locations[n].models.always.ODeck = "oldeck";
		Locations[n].models.always.locators = "oldeck_locators";

		// Day
		Locations[n].models.day.charactersPatch = "oldeck_patch";
		Locations[n].models.day.fonar = "oldeck_fday";
		// Night
		Locations[n].models.night.charactersPatch = "oldeck_patch";
		Locations[n].models.night.fonar = "oldeck_fnight";
		// Environment
		Locations[n].environment.sea = "true";
		Locations[n].environment.weather = "true";
		break;

	case "DTSG_Graf_Sheffild_1":
		StartQuestMovie(true, false, true);
		dialog.text = "¡Suficiente! Estoy listo para rendir mi espada y discutir tus demandas. Pero primero, ¡preséntate! ¿Quién eres y cómo te atreves a atacarnos? ¡Esto es traición!";
		link.l1 = "";
		link.l1.go = "DTSG_Graf_Sheffild_2";
		CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
	case "DTSG_Graf_Sheffild_2":
		DialogExit();
		LAi_SetPlayerType(pchar);
		sld = CharacterFromID("Fleetwood");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Graf_Sheffild_3";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;

	case "DTSG_Graf_Sheffild_3":
		dialog.text = "Capitán Richard Fleetwood. ¿Y usted debe ser Earl Sheffield? Y tiene toda la razón, esto es traición.";
		link.l1 = "";
		link.l1.go = "DTSG_Graf_Sheffild_5";
		CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
	case "DTSG_Graf_Sheffild_5":
		DialogExit();
		sld = CharacterFromID("DTSG_Graf_Sheffild");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Graf_Sheffild_6";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;

	case "DTSG_Graf_Sheffild_6":
		dialog.text = "¿Sabes quién soy? ¡Maldita sea! Sabía que algo así pasaría, ratas por todas partes, así que pedí, incluso rogué por un buque de guerra...";
		link.l1 = "";
		link.l1.go = "DTSG_Graf_Sheffild_7";
		CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
	case "DTSG_Graf_Sheffild_7":
		DialogExit();
		sld = CharacterFromID("Fleetwood");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Graf_Sheffild_8";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;

	case "DTSG_Graf_Sheffild_8":
		dialog.text = "No te habría salvado, solo habría prolongado lo inevitable, ya que encontraría otro enfoque. Y sí, por traición, me refiero a la tuya, Conde Sheffield.";
		link.l1 = "";
		link.l1.go = "DTSG_Graf_Sheffild_9";
		CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
	case "DTSG_Graf_Sheffild_9":
		DialogExit();
		sld = CharacterFromID("DTSG_Graf_Sheffild");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Graf_Sheffild_10";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;

	case "DTSG_Graf_Sheffild_10":
		dialog.text = "¡Entonces no sabe nada de mí, señor! ¡Todos saben que no hay hombre más leal a Inglaterra que yo! Se arrepentirá de este error, marque mis palabras.";
		link.l1 = "";
		link.l1.go = "DTSG_Graf_Sheffild_12";
		CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
	case "DTSG_Graf_Sheffild_12":
		DialogExit();
		sld = CharacterFromID("Fleetwood");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Graf_Sheffild_13";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;

	case "DTSG_Graf_Sheffild_13":
		dialog.text = "No tengo nada de qué arrepentirme, ya que no soy yo quien se está pasando a los holandeses.";
		link.l1 = "";
		link.l1.go = "DTSG_Graf_Sheffild_15";
		CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;
	case "DTSG_Graf_Sheffild_15":
		DialogExit();
		sld = CharacterFromID("DTSG_Graf_Sheffild");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Graf_Sheffild_16";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;

	case "DTSG_Graf_Sheffild_16":
		dialog.text = "¿Qué?! ¿Qué tonterías estás diciendo? ¡Te han engañado, y has seguido un rastro falso como un perro loco\nEjem, es cierto, me dirijo a negociar con la Compañía Holandesa de las Indias Occidentales. Pero en interés de nuestra Inglaterra, Capitán. Este es un error terrible, pero aún podemos corregirlo.";
		link.l1 = "";
		link.l1.go = "DTSG_Graf_Sheffild_17";
		CharacterTurnByChr(npchar, CharacterFromID("Fleetwood"));
		break;
	case "DTSG_Graf_Sheffild_17":
		DialogExit();
		sld = CharacterFromID("Fleetwood");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Graf_Sheffild_18";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;

	case "DTSG_Graf_Sheffild_18":
		dialog.text = "Tengo miedo de que esto no dependa de mí. Y ciertamente no de ti. Habéis elegido el lado equivocado, caballeros. Adiós.";
		link.l1 = "";
		link.l1.go = "DTSG_Graf_Sheffild_19";
		CharacterTurnByChr(npchar, CharacterFromID("DTSG_Graf_Sheffild"));
		break;

	case "DTSG_Graf_Sheffild_19":
		DialogExit();
		LAi_SetActorType(pchar);
		sld = CharacterFromID("Fleetwood");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "Shot", "1", 1.8);
		DoQuestCheckDelay("DTSG_Graf_Sheffild_20", 0.9);
		break;

	case "DTSG_Graf_Sheffild_22":
		dialog.text = "Hemos terminado aquí. Pensé que ese gordo nunca dejaría de chillar. Oh, estos condes, ¿verdad, Charlie?";
		link.l1 = "Solo me pregunto, señor, ¿y si el coronel estaba equivocado? ¿O, Dios no lo quiera, nos mintió para deshacerse del conde?";
		link.l1.go = "DTSG_Graf_Sheffild_23";
		break;

	case "DTSG_Graf_Sheffild_23":
		dialog.text = "Escúchame, amigo mío. Y escucha con atención. Nuestro servicio es muy peligroso y difícil, en todos los sentidos. Cualquier cosa puede suceder: un triste error, una coincidencia ridícula, o una traicionera traición\nServir al país no es solo cargar cañones con balas de cañón, Charlie. Para los poderes que mandan es tomar decisiones difíciles. Y para soldados como nosotros - ejecutar esas decisiones.";
		link.l1 = "¿Pero qué haremos si un día derramamos sangre inocente, Capitán? Eso quedará en nuestras manos, en nuestra conciencia.";
		link.l1.go = "DTSG_Graf_Sheffild_24";
		break;

	case "DTSG_Graf_Sheffild_24":
		dialog.text = "Entonces la sangre estará en sus manos tanto como en las nuestras, si no más. Que eso te consuele. Lo principal es que nuestras intenciones eran puras: eliminar al enemigo de la patria.\nAhora ayúdame, Charlie, todavía necesitamos hacer que parezca un ataque holandés.";
		link.l1 = "Sí, señor...";
		link.l1.go = "DTSG_Graf_Sheffild_25";
		break;

	case "DTSG_Graf_Sheffild_25":
		DialogExit();
		sld = GetCharacter(NPC_GenerateCharacter("DTSG_Kortni", "off_eng_5", "man", "man", 40, ENGLAND, -1, false, "quest"));
		sld.name = "Thomas";
		sld.lastname = "Lynch";
		sld.rank = 40;
		GiveItem2Character(sld, "blade_16");
		EquipCharacterByItem(sld, "blade_16");
		GiveItem2Character(sld, "pistol6");
		EquipCharacterByItem(sld, "pistol6");
		SetSelfSkill(sld, 100, 100, 100, 100, 100);
		LAi_SetHP(sld, 400.0, 400.0);
		FantomMakeCoolSailor(sld, SHIP_HIMERA, "Сhimera", CANNON_TYPE_CANNON_LBS20, 70, 70, 70);
		SetCharacterPerk(sld, "Energaiser");
		SetCharacterPerk(sld, "BasicDefense");
		SetCharacterPerk(sld, "AdvancedDefense");
		SetCharacterPerk(sld, "CriticalHit");
		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "Gunman");
		SetCharacterPerk(sld, "GunProfessional");
		SetCharacterPerk(sld, "Sliding");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "SwordplayProfessional");
		SetCharacterPerk(sld, "ShipSpeedUp");
		SetCharacterPerk(sld, "ShipTurnRateUp");
		SetCharacterPerk(sld, "StormProfessional");
		SetCharacterPerk(sld, "WindCatcher");
		SetCharacterPerk(sld, "SailsMan");
		SetCharacterPerk(sld, "Doctor1");
		SetCharacterPerk(sld, "MusketsShoot");
		SetCharacterPerk(sld, "LongRangeGrappling");
		SetCharacterPerk(sld, "HullDamageUp");
		SetCharacterPerk(sld, "HullDamageUp");
		SetCharacterPerk(sld, "SailsDamageUp");
		SetCharacterPerk(sld, "CrewDamageUp");
		SetCharacterPerk(sld, "CriticalShoot");
		SetCharacterPerk(sld, "BasicCommerce");
		SetCharacterPerk(sld, "AdvancedCommerce");
		sld.Ship.Mode = "war";
		sld.alwaysEnemy = true;
		sld.Coastal_Captain = true;
		sld.AlwaysSandbankManeuver = true;
		sld.DontRansackCaptain = true;

		Group_FindOrCreateGroup("DTSG_KortniAttack");
		Group_SetType("DTSG_KortniAttack", "pirate");
		Group_AddCharacter("DTSG_KortniAttack", "DTSG_Kortni");

		Group_SetGroupCommander("DTSG_KortniAttack", "DTSG_Kortni");
		Group_SetTaskAttack("DTSG_KortniAttack", PLAYER_GROUP);
		Group_SetAddress("DTSG_KortniAttack", "Antigua", "Quest_Ships", "Quest_Ship_10");
		Group_LockTask("DTSG_KortniAttack");

		SetLaunchFrameFormParam("Present time", "DTSG_SegodnyaVremya", 0, 4.0);
		LaunchFrameForm();
		break;

	case "DTSG_Knippel_101":
		dialog.text = "Así que dejamos pruebas falsas para que pareciera que lo hicieron los holandeses. Richard y yo nunca volvimos a hablar de ese día.";
		if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
		{
			link.l1 = "Bueno, ahora muchas cosas tienen sentido. Creo que un pariente o un partidario del Conde está detrás de la muerte de Richard. Pero, ¿por qué apuntar a ti? Eres solo un artillero y no tomaste ninguna decisión ese triste día.";
			link.l1.go = "DTSG_Knippel_ZS_102";
			AddComplexLandExpToScill(50, 50, 50);
			Log_info("Bonificación por experiencia recibida");
		}
		else
		{
			link.l1 = "En efecto. Este asunto es malo y apesta. Tal vez alguien se enteró y decidió vengar al Conde. Pero, ¿vale la pena un artillero tantos gastos? Dinero, mercenarios, contratar a los Zorros del Mar... De ninguna manera, Charlie.";
			link.l1.go = "DTSG_Knippel_NS_102";
		}
		break;

	case "DTSG_Knippel_ZS_102":
		dialog.text = "Tal vez esta persona esté cazando a todos del antiguo equipo de Richard. ¿Qué piensa usted, señor?";
		link.l1 = "Creo que deberíamos alejarnos de Antigua, y cuanto antes, mejor.";
		link.l1.go = "DTSG_Knippel_103";
		break;

	case "DTSG_Knippel_NS_102":
		dialog.text = "Yo también me he hecho esa pregunta, Capitán, pero no he encontrado una respuesta.";
		link.l1 = "Carajo. Alguien viene. ¡Pedí que no me molestaran!";
		link.l1.go = "DTSG_Knippel_103";
		break;

	case "DTSG_Knippel_103":
		DialogExit();

		LAi_SetPlayerType(pchar);
		if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
		{
			sld = characterFromId("Helena");
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Helena_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			break;
		}
		if (GetCharacterIndex("Tichingitu") != -1 && CheckPassengerInCharacter(pchar, "Tichingitu"))
		{
			sld = characterFromId("Tichingitu");
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Tichingitu_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			break;
		}
		else
		{
			sld = GetCharacter(NPC_GenerateCharacter("Alonso", "Alonso", "man", "man", sti(pchar.rank), pchar.nation, 0, true, "soldier"));
			sld.name = "Alonso";
			sld.lastname = "";
			ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
			sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
			sld.dialog.currentnode = "DTSG_Alonso_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 0, 0);
			sld.location = "None";
		}
		break;

	case "DTSG_Helena_1":
		if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
		{
			dialog.text = "¡Charles!..";
			link.l1 = "¿Qué sucede, Helen??";
			link.l1.go = "DTSG_Helena_2";
		}
		else
		{
			dialog.text = "Charles, recuerdo que me pediste que no dejara entrar a nadie y que no te molestara a ti y a Charlie, pero...";
			link.l1 = "... decidiste venir tú mismo. Está bien, está bien, Helen.";
			link.l1.go = "DTSG_Helena_2";
		}
		break;

	case "DTSG_Helena_2":
		if (sti(pchar.questTemp.Saga.HelenRelation) >= 6)
		{
			dialog.text = "¡Un navío de guerra inglés! Fue avistado hace un rato. Al principio, no le presté atención, ¡pero nos alcanzará en cualquier momento! Nunca he visto un barco tan rápido.";
			link.l1 = "Entonces gracias por decírmelo. Espero que tengamos tiempo para prepararnos antes de que se acerque. ¡Helen, Charlie, a sus puestos de combate!";
			link.l1.go = "DTSG_GotovimsyKBitve";
		}
		else
		{
			dialog.text = "... puedes continuar tu reunión secreta más tarde. Un buque de guerra inglés se dirige hacia nosotros. Pensé que era importante.";
			link.l1 = "Bueno, iré a echar un vistazo. Gracias, Helen.";
			link.l1.go = "DTSG_GotovimsyKBitve";
		}
		break;

	case "DTSG_Tichingitu_1":
		dialog.text = "Capitán, un barco rápido se acerca hacia nosotros. Muy rápido. Los espíritus me susurran que sus intenciones son malignas.";
		link.l1 = "Gracias a ti y a los espíritus por la advertencia. Prepárate para la batalla por si acaso. Y pasa este mensaje a los demás de mi parte.";
		link.l1.go = "DTSG_GotovimsyKBitve";
		break;

	case "DTSG_Alonso_1":
		dialog.text = "Disculpe, por la interrupción, Capitán, pero es urgente.";
		link.l1 = " Oh, espero que sea realmente importante, Alonso. Informa.";
		link.l1.go = "DTSG_Alonso_2";
		break;

	case "DTSG_Alonso_2":
		dialog.text = "Un barco inglés se acerca. Es... el 'Mirage', Capitán.";
		link.l1 = "¿Qué? ¿Estás absolutamente seguro? ¿Has estado bebiendo de nuevo, eh?";
		link.l1.go = "DTSG_Alonso_3";
		break;

	case "DTSG_Alonso_3":
		dialog.text = "Estoy seguro, Capitán - no hay otro barco como ese en el Caribe, ya lo sabe.";
		link.l1 = "En efecto. Iré a echar un vistazo yo mismo, veamos si este 'Espejismo' es real.";
		link.l1.go = "DTSG_GotovimsyKBitve";
		break;

	case "DTSG_GotovimsyKBitve":
		DialogExit();
		AddQuestRecord("DTSG", "17");

		if (GetCharacterIndex("Helena") != -1 && CheckPassengerInCharacter(pchar, "Helena"))
		{
			sld = characterFromId("Helena");
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\Saga\Helena.c";
			sld.Dialog.CurrentNode = "Helena_officer";
		}
		if (GetCharacterIndex("Tichingitu") != -1 && CheckPassengerInCharacter(pchar, "Tichingitu"))
		{
			sld = characterFromId("Tichingitu");
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			sld.Dialog.CurrentNode = "Tichingitu_officer";
		}
		if (GetCharacterIndex("Knippel") != -1 && CheckPassengerInCharacter(pchar, "Knippel"))
		{
			sld = characterFromId("Knippel");
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
			sld.Dialog.CurrentNode = "Knippel_officer";
		}

		PChar.quest.DTSG_KortniPotopil.win_condition.l1 = "Character_sink";
		PChar.quest.DTSG_KortniPotopil.win_condition.l1.character = "DTSG_Kortni";
		PChar.quest.DTSG_KortniPotopil.win_condition = "DTSG_KortniPotopil";

		chrDisableReloadToLocation = false;
		bDisableCharacterMenu = false;
		InterfaceStates.Buttons.Save.enable = true;
		DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		DeleteAttribute(pchar, "GenQuest.CannotWait");
		break;

	case "DTSG_Kortni":
		dialog.text = "¡Oh... Pero esto aún no ha terminado! ¡Brian, ahí estás! ¿Dónde diablos has estado?";
		link.l1 = "Esto solo retrasará lo inevitable.";
		link.l1.go = "DTSG_Kortni_Pikar";
		break;

	case "DTSG_Kortni_Pikar":
		DialogExit();
		LAi_SetPlayerType(pchar);
		LAi_SetFightMode(pchar, true);

		LAi_SetWarriorType(npchar);
		LAi_SetCurHPMax(npchar);
		LAi_GetCharacterMaxEnergy(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		LAi_SetCheckMinHP(npchar, 10, true, "DTSG_KortniRanen");
		LAi_SetImmortal(npchar, false);

		sld = GetCharacter(NPC_GenerateCharacter("DTSG_Mrt_Rocur", "citiz_8", "man", "man", sti(pchar.rank), ENGLAND, -1, false, "soldier"));
		sld.name = "Brian";
		sld.lastname = "Tasse";
		GiveItem2Character(sld, "blade_20");
		EquipCharacterByItem(sld, "blade_20");
		GiveItem2Character(sld, "pistol5");
		EquipCharacterByItem(sld, "pistol5");
		AddItems(sld, "purse2", 1);
		sld.SaveItemsForDead = true;
		sld.DontClearDead = true;
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		LAi_SetHP(sld, 300.0, 300.0);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_SetCheckMinHP(sld, 10, true, "DTSG_PikarRanen");
		sld.location = "None";

		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		break;

	case "DTSG_Kortni_1":
		dialog.text = "Charles de Maure. Pensar en lo lejos que has llegado. Lástima. Esperaba atraparte desprevenido en este barco.";
		link.l1 = "¿Sabes quién soy? Entonces, eres tú detrás de nuestros problemas recientes; pareces un ave de altos vuelos obligada a dejar su nido acogedor y salir en persona en lugar de enviar otro buitre.";
		link.l1.go = "DTSG_Kortni_2";

		Island_SetReloadEnableGlobal("Antigua", true);
		bQuestDisableMapEnter = false;
		LAi_LocationDisableOfficersGen("SentJons_town", false);
		DeleteQuestCondition("DTSG_KortniPotopil");
		break;

	case "DTSG_Kortni_2":
		dialog.text = "Correcto, en ambos aspectos. Supongo que un noble puede reconocer a otro desde lejos. Coronel Thomas Lynch. Parece que es hora de hablar como caballeros, en lugar de intentar destruirnos. Quizás podamos llegar a un acuerdo mutuamente beneficioso.";
		link.l1 = "No puedo prometer nada, pero te doy mi palabra como noble que al menos hablaremos como personas civilizadas, coronel.";
		link.l1.go = "DTSG_Kortni_3";
		break;

	case "DTSG_Kortni_3":
		dialog.text = "Muy bien. No podría haber tenido una conversación así con Fleetwood. Aún así, encontramos un punto de presión sobre él, y ya no nos causará problemas. Es una pena que no haya funcionado contigo, pero no importa.";
		if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
		{
			link.l1 = "Todo el Caribe habla de la muerte de Richard. ¡Así que fuiste tú! Y supongo que la ventaja a la que te referías era Abigail. ¿Qué le pasó, por cierto?";
			AddComplexLandExpToScill(50, 50, 50);
			Log_info("Bonificación por experiencia recibida");
		}
		else
		{
			link.l1 = "¿No una amenaza, dices?.. ¿Entonces, lo mataste? ¿Eres partidario del conde?";
		}
		link.l1.go = "DTSG_Kortni_4";
		break;

	case "DTSG_Kortni_4":
		if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
		{
			dialog.text = "¿Abigail? Ah, la joven judía, su prometida. Una vez más, has demostrado ser una persona muy perceptiva. Ella está viva y bien, prometimos y cumplimos con eso a cambio de la cooperación de Fleetwood.";
			link.l1 = "Vaya cooperación, debo decir. Pero ¿por qué lo hiciste? ¿Eres partidario del Conde?";
		}
		else
		{
			dialog.text = "¿Admirador? Oh, todo lo contrario. Pero, ya ves, algunas cartas ya no se pueden jugar, pues se convierten en una carga para el jugador. Desafortunadamente, Richard se convirtió en una de ellas.";
			link.l1 = "Ya veo. Eliminas a todos los testigos. ¿Qué pasó con Abigail? ¿La mataste también?";
		}
		link.l1.go = "DTSG_Kortni_5";
		break;

	case "DTSG_Kortni_5":
		if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
		{
			dialog.text = "En absoluto. Todo lo contrario. Pero Richard sabía demasiado, y al regresar al Viejo Mundo, se volvió peligroso. Debería haberse quedado aquí, y no habríamos tomado su vida.";
			link.l1 = "¿Eliminas a todos los que alguna vez trabajaron para ti, Coronel?";
		}
		else
		{
			dialog.text = "¿Quién? Ah, su prometida, supongo. Ella era la palanca. Su vida por la de ella. Está bien, lo juro por mi honor.";
			link.l1 = "Dudo que sepas qué es el honor, considerando lo que has hecho, Coronel.";
		}
		link.l1.go = "DTSG_Kortni_6";
		break;

	case "DTSG_Kortni_6":
		if (CheckAttribute(pchar, "questTemp.DTSG_Nastoroje2"))
		{
			dialog.text = "No responderé a esa provocación, señor.";
			link.l1 = "Entonces responde a esto: ¿cómo conseguiste este barco? ¿Es... el 'Mirage'?";
		}
		else
		{
			dialog.text = "Pasaré por alto este insulto porque viene de alguien que nunca ha tenido que ejercer poder e influir en el orden de las cosas.";
			link.l1 = " Hablando de cosas, ¿dónde conseguiste el 'Espejismo'? ¿Es ella?";
		}
		link.l1.go = "DTSG_Kortni_7";
		break;

	case "DTSG_Kortni_7":
		dialog.text = "Exactamente. ¿Verdad que es un magnífico barco? Qué lástima que no cumplió con su propósito contra usted. ¿Conoce la historia de este barco, Capitán de Maure?";
		link.l1 = "¿Te refieres al barco fantasma y la caza de mercaderes ingleses?";
		link.l1.go = "DTSG_Kortni_8";
		break;

	case "DTSG_Kortni_8":
		dialog.text = "¿Eso? Oh, no. No estoy hablando de cosas bien conocidas. Me refiero a cosas que están escondidas a la vista. Este queche fue diseñado por Johan van Merden y Lucas Rodenburg\nEsa dulce pareja creó una cadena de intrigas, y el barco finalmente fue lanzado desde el astillero en La Habana. Tuvimos la suerte de conseguir los planos originales. Y al final, recreamos el Mirage en todo su esplendor e incluso la mejoramos, corrigiendo algunos defectos en su diseño.";
		link.l1 = "Lástima que, como usted mismo señaló, no le ayudó mucho, Coronel.";
		link.l1.go = "DTSG_Kortni_9";
		break;

	case "DTSG_Kortni_9":
		dialog.text = "¿Estás de humor para reírte? No lo estés. Lo admito, me superaste tanto como capitán como luchador. Pero todavía tengo la ventaja aquí.";
		link.l1 = "¿Es eso un farol de moribundo? ¿O simplemente la habitual arrogancia de gente como tú? ¿Qué se esconde tras esas palabras?";
		link.l1.go = "DTSG_Kortni_10";
		break;

	case "DTSG_Kortni_10":
		dialog.text = "Excelente pregunta. Me parece que eres más que un mujeriego y duelista, como sugería mi investigación. Tomé medidas para todos los posibles desenlaces de esta reunión. Incluso aquel en el que muero por tu espada, bala, o una bala de cañón perdida. Si muero hoy, tú y Charlie lamentarán no haberse unido a Fleetwood.";
		link.l1 = "¿Más cazarrecompensas? Por favor. Fue desagradable y tedioso, pero no mortal. Los enfrentamos entonces, los enfrentaremos de nuevo.";
		link.l1.go = "DTSG_Kortni_11";
		break;

	case "DTSG_Kortni_11":
		dialog.text = "No tengo dudas. Ahora veo al despreocupado duelista hablando de nuevo. No solo cazadores de recompensas. Toda la fuerza de los Zorros del Mar y la inteligencia naval inglesa se estrellará sobre tu cabeza como una ola de tormenta en el barco de un pescador.";
		link.l1 = "¿Qué quieres de mí? ¿No esperas que me rinda?";
		link.l1.go = "DTSG_Kortni_12";
		break;

	case "DTSG_Kortni_12":
		dialog.text = "Por supuesto que no. Te hemos estudiado bien durante todo este tiempo. Quiero ofrecerte un trato mutuamente beneficioso. Uno que sería imprudente rechazar. Y como dos caballeros, espero que podamos llegar a un acuerdo.";
		link.l1 = "Entonces repito la pregunta, Coronel, ¿qué desea? ¿Supongo que a Charlie?.. ¿Y cree que puede ofrecerme algo a cambio? No traicionaré por unas pocas monedas de oro.";
		link.l1.go = "DTSG_Kortni_13";
		break;

	case "DTSG_Kortni_13":
		dialog.text = "Correcto de nuevo. No se trata solo de unas pocas monedas de oro, como dijiste, sino de toda una montaña - 10,000 doblones. El depósito te estará esperando en el banquero en Port Royal si llegamos a un acuerdo\nPero lo más importante que ofrezco es tu vida, Capitán de Maure. Me escuchaste. Cesearemos toda persecución si todos depusimos las armas ahora, y nos entregas a Charlie\n¿Has escuchado la expresión 'hombre contra la sociedad'? En tu caso, si te niegas, será 'hombre contra el estado'. Decide, Charles. Aquí y ahora.";
		link.l1 = "Puedes usar fácilmente tu título e influencia para intimidar a uno o dos tontos. Pero yo no soy un tonto. Y siento la desesperación a una milla de distancia. Vete. Y agradece que no te maté, te lo mereces más que de sobra.";
		link.l1.go = "DTSG_Kortni_PkCh_1";
		link.l2 = "No necesitas realmente a Charlie, coronel. Necesitas su silencio.";
		link.l2.go = "DTSG_Kortni_LT_1";
		link.l3 = "Estoy de acuerdo con esto por la seguridad mía y de mis hombres, no por codicia por tu dinero, solo para que lo sepas.";
		link.l3.go = "DTSG_Kortni_Sdat";
		break;

	case "DTSG_Kortni_PkCh_1":
		dialog.text = "Has tomado una de las peores decisiones de tu vida, Capitán de Maure. No te envidio. Honestamente. Tendrás que culparte a ti mismo - nadie te hará ofertas similares de nuevo. Especialmente yo no. Adiós.";
		link.l1 = "Espera, Coronel.";
		link.l1.go = "DTSG_Kortni_PkCh_2";
		break;

	case "DTSG_Kortni_PkCh_2":
		dialog.text = "¿Qué, has cambiado de opinión? ¿Mis palabras finalmente tuvieron efecto?";
		link.l1 = "Correcto, justo lo contrario.";
		link.l1.go = "DTSG_Kortni_PkCh_3";
		break;

	case "DTSG_Kortni_PkCh_3":
		dialog.text = "¿Qué quieres decir? Explícate.";
		link.l1 = "Tus palabras solo han fortalecido mi determinación contra ti. No pongas esa cara, no te mataré. Y como dije, incluso te dejaré ir. Pero creo que te las arreglarás sin un barco.";
		link.l1.go = "DTSG_Kortni_PkCh_4";
		break;

	case "DTSG_Kortni_PkCh_4":
		dialog.text = "No lo necesito, ya que tengo un barco.";
		link.l1 = "Tienes razón. Pero solo en cuanto a que no lo necesito. Puede que seas un hombre influyente. Pero te falta sentido de la medida. Y tacto. Haré lo que estás acostumbrado a hacer: ser el amo de la situación.";
		link.l1.go = "DTSG_Kortni_PkCh_5";
		break;

	case "DTSG_Kortni_PkCh_5":
		dialog.text = "No lo eres, Capitán de Maure. No te engañes.";
		link.l1 = "¿Completamente? Tal vez no. Pero tú tampoco - tu vida ahora está en mis manos, Coronel. No importa lo que me pase después - ahora puedo hacer lo que quiera. Y yo... me quedo con este barco. Eres libre. La costa no está lejos.";
		link.l1.go = "DTSG_Kortni_PkCh_6";
		break;

	case "DTSG_Kortni_PkCh_6":
		dialog.text = "No te atreverías. Pero a juzgar por tu mirada... Disfruta de tu pequeña victoria. Has hecho...";
		link.l1 = "Sí, sí, una de las peores decisiones de mi vida. Ya lo he oído. Fuera de este barco. Mi barco. ¿Te lanzarás tú mismo, o deberíamos echarte por la borda?";
		link.l1.go = "DTSG_Kortni_PkCh_7";
		break;

	case "DTSG_Kortni_PkCh_7":
		DialogExit();

		LAi_SetActorType(pchar);
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "goto", "goto4", "", "", "", "DTSG_Kortni_Vyprygnul", 7);
		npchar.lifeday = 0;
		npchar.location = "None";
		break;

	case "DTSG_Kortni_PkCh_8":
		dialog.text = "Jamás pensé que lo vería así - humillado, saltando por la ventana y nadando hasta la orilla a cuatro patas.";
		link.l1 = "¿Lo viste? ¿Satisfecho? Maravilloso. Tú eres el siguiente.";
		link.l1.go = "DTSG_Kortni_PkCh_9";
		break;

	case "DTSG_Kortni_PkCh_9":
		dialog.text = "¿Qué está diciendo, señor? No somos enemigos; ¡sólo seguía órdenes!.. ¿Puedo al menos pedir un barco? ¡Nunca me volverás a ver!";
		link.l1 = " No tendrías piedad de mí si estuvieras en mi lugar y acabas de perder una batalla contra mí. Así que alégrate de que no te maté. Por la ventana. Ahora. Tal vez alcances a tu patrón.";
		link.l1.go = "DTSG_Kortni_PkCh_10";
		break;

	case "DTSG_Kortni_PkCh_10":
		dialog.text = "¡Preferiría morir que enfrentar tal humillación, monsieur!";
		link.l1 = "Como desees.";
		link.l1.go = "DTSG_Kortni_PkCh_11";
		break;

	case "DTSG_Kortni_PkCh_11":
		DialogExit();

		LAi_SetPlayerType(pchar);
		LAi_SetFightMode(pchar, true);

		LAi_RemoveCheckMinHP(npchar);
		LAi_SetImmortal(npchar, false);
		LAi_SetWarriorType(npchar);
		LAi_SetCurHPMax(npchar);
		LAi_GetCharacterMaxEnergy(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");

		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		LAi_group_SetCheck("EnemyFight", "DTSG_Kortni_Vyprygnul_3");
		break;

	case "DTSG_Kortni_PkCh_12":
		dialog.text = "Eso fue el Coronel, ¿verdad, Capitán?";
		link.l1 = "Bien. Mira por la ventana, Charlie, no te arrepentirás.";
		link.l1.go = "DTSG_Kortni_PkCh_13";
		break;

	case "DTSG_Kortni_PkCh_13":
		DialogExit();

		LAi_SetActorType(npchar);
		LAi_ActorGoToLocator(npchar, "goto", "goto4", "DTSG_Kortni_Vyprygnul_5", 6);
		break;

	case "DTSG_Kortni_PkCh_14":
		dialog.text = "¿El Coronel?.. Nunca habría pensado que vería algo así, señor. ¡Que alguien se atrevería a lanzar por la borda a un hombre con semejante título como si fuera un simple marinero! Richard nunca haría eso - respetar el rango era una parte fundamental de él.";
		link.l1 = "Le fue inculcado con años de entrenamiento. Es un hombre militar, con la mentalidad correspondiente. Yo no, y pienso de manera más amplia, sin tales... restricciones.";
		link.l1.go = "DTSG_Kortni_PkCh_15";
		break;

	case "DTSG_Kortni_PkCh_15":
		dialog.text = "¿Y no nos meteremos en problemas por hacerle esto?";
		link.l1 = "Heh, culpas a Richard, pero piensas como él. Nos atrevimos a resistir, así que nos cazarán por un tiempo. Pero tarde o temprano, incluso la armada inglesa nos dejará en paz. Y para Lynch, se convertirá en un asunto personal. Pero nos aseguramos de que la próxima vez no cuente con los recursos del estado.";
		link.l1.go = "DTSG_Kortni_PkCh_16";
		break;

	case "DTSG_Kortni_PkCh_16":
		dialog.text = "Sabes, Capitán, desde este día, te respeto aún más. Nunca lamentaré no haber partido con Dick en el Valkyrie y decidir unirme a ti.";
		link.l1 = "¡Gracias, amigo mío! Prepárate - la tormenta se avecina sobre nosotros. ¿Pero sabes qué? Algo me dice que saldremos victoriosos de nuevo. Vamos, es hora de volver a la cubierta.";
		link.l1.go = "DTSG_Kortni_PkCh_17";
		break;

	case "DTSG_Kortni_PkCh_17":
		DialogExit();

		LAi_SetActorType(npchar);
		LAi_ActorFollow(npchar, pchar, "", -1);
		LAi_SetOfficerType(npchar);
		npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
		npchar.Dialog.CurrentNode = "Knippel_officer";

		DoQuestCheckDelay("DTSG_Kortni_Vyprygnul_7", 3.0);
		Achievment_Set("ach_CL_114");
		break;

	case "DTSG_Kortni_LT_1":
		dialog.text = "No es del todo cierto, aunque personalmente, no me importa Charlie si mantiene la boca cerrada a partir de ahora. Pero a mis colegas les gustaría ver su cuerpo. Y saben cómo se ve\nEsta es la vida real, Charles, no un cuento de hadas infantil o un poema caballeresco que nos leían las niñeras en la infancia, y no veo una solución que agrade a todos.";
		link.l1 = "Pero yo sí. Siempre puedes encontrar un cuerpo similar. Y comprar ropa similar. Engrasar algunas ruedas. Y hablaré con Charlie. Y te doy mi palabra como garantía.";
		link.l1.go = "DTSG_Kortni_LT_2";
		break;

	case "DTSG_Kortni_LT_2":
		if (sti(pchar.reputation.nobility) > 70)
		{
			notification("Reputation Check Passed", "None");
			dialog.text = "Es... un gran riesgo. Y no se trata solo de si puedo confiar en tu palabra. Sino de si mis colegas me creerán cuando vean un cuerpo que se parezca al de Charlie. Y no asumiré ese riesgo... así como así.";
			link.l1 = "¿Cuánto?";
			link.l1.go = "DTSG_Kortni_LT_4";
		}
		else
		{
			notification("Reputation Too Low! (" + XI_ConvertString(GetReputationName(71)) + ")", "None");
			dialog.text = "La palabra de un hombre con tu reputación? Estás bromeando. El nacimiento noble por sí solo no es suficiente para confiar.";
			link.l1 = "Escuchar esto de otro hombre con un nacimiento y acciones similares, perdóname, Coronel.";
			link.l1.go = "DTSG_Kortni_LT_3";
		}
		break;

	case "DTSG_Kortni_LT_3":
		dialog.text = "Tienes razón, por supuesto. Pero en este caso, se trata de mi confianza, no de la de nadie más. Y tú como garante no me sirves\nTe lo digo una última vez. Dame a Charlie. Si, por supuesto, no quieres compartir el destino de Fleetwood.";
		link.l1 = "Puedes usar fácilmente tu título e influencia para intimidar a un tonto o dos. Pero yo no soy un tonto. Y percibo la desesperación a una milla de distancia. Lárgate. Y alégrate de que no te maté - bien que lo mereces.";
		link.l1.go = "DTSG_Kortni_PkCh_1";
		break;

	case "DTSG_Kortni_LT_4":
		dialog.text = "Finalmente, directo al grano. Un millón de pesos. Oferta final.";
		if (sti(pchar.Money) >= 1000000)
		{
			link.l1 = "Te pagaré el dinero. No pienses que soy pobre o que no valoro la vida de mis hombres. Ninguna de las dos cosas es cierta. Tómalo.";
			link.l1.go = "DTSG_Kortni_LT_7";
		}
		else
		{
			link.l1 = " Tienes buen apetito, aunque no esperaba menos. Pero ahora mismo, no tengo tanto, y...";
			link.l1.go = "DTSG_Kortni_LT_5";
		}
		break;

	case "DTSG_Kortni_LT_5":
		dialog.text = "Sin plata, no hay trato. ¿Pensaste que mostraría misericordia? ¿Acaso tengo cara de santo, señor?";
		link.l1 = "¿Pero quizá podrías esperar un poco? ¿Dónde y cuándo sería conveniente volver a encontrarnos? Podría pedir prestados los doblones a un prestamista.";
		link.l1.go = "DTSG_Kortni_LT_6";
		break;

	case "DTSG_Kortni_LT_6":
		dialog.text = "Entonces piensas que soy aún más ingenua de lo que pensaba\nNo soy una muchacha del campo dispuesta a esperar eternamente a alguien que una vez se salió con la suya con ella\n¿No hay dinero? No lo pedí de todos modos. Solo quiero a Charlie. No me sirves de nada a pesar de todos los problemas que has causado.";
		link.l1 = "Puedes usar fácilmente tu título e influencia para intimidar a un tonto o dos. Pero yo no soy un tonto. Y detecto la desesperación a una milla de distancia. Lárgate. Y alégrate de que no te maté - más que lo mereces.";
		link.l1.go = "DTSG_Kortni_PkCh_1";
		break;

	case "DTSG_Kortni_LT_7":
		dialog.text = "¿Estás realmente tan apegado al pobre Charlie? En cualquier caso, tu nobleza merece respeto. Asegúrate de que tu artillero sea tan silencioso como una tumba. O ambos terminaréis allí.";
		link.l1 = "Lo prometo. Y tú mantienes tu palabra y detienes toda persecución.";
		link.l1.go = "DTSG_Kortni_LT_8";
		AddMoneyToCharacter(pchar, -1000000);
		break;

	case "DTSG_Kortni_LT_8":
		dialog.text = "Lo prometo también. Y una cosa más. A pesar de tu honesta victoria, me llevaré mi barco conmigo. Es una pieza hecha a medida, ¿sabes? Y muy cara.";
		link.l1 = "¿Qué pasa con el derecho del vencedor? Pero no tentaré a la suerte. Esta vez.";
		link.l1.go = "DTSG_Kortni_LT_9";
		break;

	case "DTSG_Kortni_LT_9":
		DialogExit();

		LAi_Fade("DTSG_Kortni_Otkup_1", "");
		break;

	case "DTSG_Kortni_LT_10":
		dialog.text = "Casi me duele decir esto, Brian, pero me temo que nuestra cooperación termina aquí.";
		link.l1 = "";
		link.l1.go = "DTSG_Kortni_LT_11";
		CharacterTurnToLoc(npchar, "rld", "aloc0");
		break;
	case "DTSG_Kortni_LT_11":
		DialogExit();
		LAi_SetPlayerType(pchar);
		sld = CharacterFromID("DTSG_Mrt_Rocur");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Kortni_LT_12";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;

	case "DTSG_Kortni_LT_12":
		dialog.text = "¿Soy libre, coronel? ¿Levantaréis la recompensa por mi cabeza, y podré empezar de nuevo como si fuera un hombre respetuoso de la ley?";
		link.l1 = "";
		link.l1.go = "DTSG_Kortni_LT_13";
		CharacterTurnToLoc(npchar, "rld", "loc0");
		break;
	case "DTSG_Kortni_LT_13":
		DialogExit();
		sld = CharacterFromID("DTSG_KortniClone");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Kortni_LT_14";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;

	case "DTSG_Kortni_LT_14":
		dialog.text = "Diría que has visto demasiado, igual que el difunto Fleetwood. Básicamente acabo de recibir un soborno justo delante de ti.";
		link.l1 = "";
		link.l1.go = "DTSG_Kortni_LT_15";
		CharacterTurnToLoc(npchar, "rld", "aloc0");
		break;
	case "DTSG_Kortni_LT_15":
		DialogExit();
		sld = CharacterFromID("DTSG_Mrt_Rocur");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Kortni_LT_16";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;

	case "DTSG_Kortni_LT_16":
		dialog.text = "Yo... no le diré a nadie nada, ¡lo juro por Dios!";
		link.l1 = "";
		link.l1.go = "DTSG_Kortni_LT_17";
		CharacterTurnToLoc(npchar, "rld", "loc0");
		break;
	case "DTSG_Kortni_LT_17":
		DialogExit();
		sld = CharacterFromID("DTSG_KortniClone");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Kortni_LT_18";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;

	case "DTSG_Kortni_LT_18":
		dialog.text = "Por supuesto que no.";
		link.l1 = "";
		link.l1.go = "DTSG_Kortni_LT_19";
		CharacterTurnToLoc(npchar, "rld", "aloc0");
		break;
	case "DTSG_Kortni_LT_19":
		DialogExit();
		sld = CharacterFromID("DTSG_Mrt_Rocur");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Kortni_LT_20";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", 0, 0);
		break;

	case "DTSG_Kortni_LT_20":
		dialog.text = "¡No!..";
		link.l1 = "";
		link.l1.go = "DTSG_Kortni_LT_21";
		CharacterTurnToLoc(npchar, "rld", "loc0");
		break;
	case "DTSG_Kortni_LT_21":
		DialogExit();

		sld = CharacterFromID("DTSG_KortniClone");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "Shot", "1", 1.8);
		DoQuestCheckDelay("DTSG_Kortni_Otkup_3", 0.9);

		LAi_SetActorType(NPChar);
		LAi_ActorAttack(NPChar, sld, "");
		break;

	case "DTSG_Kortni_LT_22":
		dialog.text = "No me mires así, Charles. Si me preocupo constantemente por si Brian soltará la lengua, no podré dormir en absoluto.";
		link.l1 = "No sé ni siquiera si debería sorprenderme por lo que he visto o no.";
		link.l1.go = "DTSG_Kortni_LT_23";
		break;

	case "DTSG_Kortni_LT_23":
		dialog.text = "No deberíais. Estoy comprometido. Todo lo que requiero de vosotros dos es que mantengáis la boca cerrada sobre lo que ocurrió. Intentaré encontrar un cuerpo similar, arreglarle bien la cara, hacer buen uso del dinero y persuadir a mis colegas.";
		link.l1 = "Gracias, Coronel.";
		link.l1.go = "DTSG_Kortni_LT_24";
		break;

	case "DTSG_Kortni_LT_24":
		dialog.text = "Aún no hay nada por lo que agradecerme. Siempre existe el riesgo de que no me crean, y entonces la caza se reabrirá. Por ahora, adiós, Capitán de Maure. Me voy a navegar en mi barco. No hay objeciones aquí - ya les he hecho a usted y a Charlie un gran favor.";
		link.l1 = "Bueno, adiós entonces.";
		link.l1.go = "DTSG_Kortni_LT_25";

		pchar.GenQuest.CannotTakeShip = true;
		PChar.quest.DTSG_Kortni_KechNeNash.win_condition.l1 = "MapEnter";
		PChar.quest.DTSG_Kortni_KechNeNash.win_condition = "DTSG_Kortni_KechNeNash";
		break;

	case "DTSG_Kortni_LT_25":
		DialogExit();

		// sld = CharacterFromID("Knippel");
		sld = GetCharacter(CreateCharacterClone(CharacterFromID("Knippel"), 0));
		sld.id = "KnippelClone";
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Kortni_LT_26";
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		LAi_SetActorType(pchar);
		LAi_SetActorType(sld);
		SetActorDialogAny2Pchar(sld.id, "", -1, 0.0);
		LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
		LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
		break;

	case "DTSG_Kortni_LT_26":
		dialog.text = "¿Sabes siquiera con quién estabas hablando, Capitán? ¡Un coronel! ¿Fue él quien orquestó todo este lío?";
		link.l1 = "Lo sé, se presentó. Y tienes razón, lo era.";
		link.l1.go = "DTSG_Kortni_LT_27";
		break;

	case "DTSG_Kortni_LT_27":
		dialog.text = "Es extraño, señor, porque una vez lo conocí como el superior de Richard. ¿Cómo es esto posible? ¿Y por qué se va como si nada hubiera pasado? ¿Qué quería, de todos modos?";
		link.l1 = "En realidad, no hay nada extraño en ello. Aquellos que llevan a cabo órdenes turbias a menudo arriesgan sus vidas no tanto por los enemigos, sino por sus superiores. Y él quería tu cabeza, Charlie.";
		link.l1.go = "DTSG_Kortni_LT_28";
		break;

	case "DTSG_Kortni_LT_28":
		dialog.text = "No entiendo, Capitán. ¿Por qué se va entonces? ¿Aceptó la derrota?";
		link.l1 = "Ese no es su estilo en absoluto. Tuve que darle oro que pesa más o menos como tu cabeza. Quizás un poco más que eso. Un millón de pesos, para ser exactos.";
		link.l1.go = "DTSG_Kortni_LT_29";
		break;

	case "DTSG_Kortni_LT_29":
		dialog.text = "¿Y tú... le pagaste esa cantidad enorme? ¿Por mí?..";
		link.l1 = "Bueno, no solo por ti. También por mí mismo. Y por todos los chicos, también. Pero sí, Charlie, principalmente por ti. Si lo hubiéramos matado, habríamos enfrentado expediciones punitivas por la eternidad después.";
		link.l1.go = "DTSG_Kortni_LT_30";
		break;

	case "DTSG_Kortni_LT_30":
		dialog.text = "Yo... no puedo creer esto, señor. Solo... gracias. No pensé que Fleetwood haría eso en su lugar.";
		link.l1 = "Eres demasiado parcial contra él después de su fuga. Richard solo quería una vida tranquila y pacífica con Abigail. Lamento que no haya funcionado para él. Además, cumplió su palabra y pagó tu deuda. Je, yo, Fleetwood - seguro que tienes suerte con los capitanes, ¿eh, Charlie?";
		link.l1.go = "DTSG_Kortni_LT_31";
		break;

	case "DTSG_Kortni_LT_31":
		dialog.text = "Sin bromas, Capitán. Entonces, ¿ya se ha terminado todo?";
		link.l1 = "Sí, mi muy caro amigo. Al menos por ahora. La pelea ha terminado - puedes decirles a los muchachos que guarden sus armas. Y que se preparen para izar las velas.";
		link.l1.go = "DTSG_Kortni_LT_32";
		break;

	case "DTSG_Kortni_LT_32":
		DialogExit();

		InterfaceStates.Buttons.Save.enable = true;
		LAi_SetPlayerType(pchar);
		LAi_SetOfficerType(npchar);
		npchar.Dialog.Filename = "Quest\HollandGambit\Knippel.c";
		npchar.Dialog.CurrentNode = "Knippel_officer";
		npchar.location = "None";

		AddQuestRecord("DTSG", "19");
		CloseQuestHeader("DTSG");
		LAi_ReloadBoarding();
		Achievment_Set("ach_CL_114");
		sld = CharacterFromID("Knippel");
		SetCharacterPerk(sld, "Bombardier");
		notification("Bombardier Unlocked", "Knippel");
		break;

	case "DTSG_Kortni_Sdat":
		dialog.text = "No me importa por qué estás de acuerdo, ya sea por codicia, miedo o deber hacia tus hombres. Lo principal es que estás de acuerdo. Enviaré a mi hombre a Port Royal con instrucciones para el banquero.";
		link.l1 = "Bien. No puedo creer que esto finalmente haya terminado.";
		link.l1.go = "DTSG_Kortni_Dengi_1";
		link.l2 = "¿Sabes qué? Al diablo con el dinero. Siempre se puede encontrar más. Hay algo más que quiero de ti a cambio de Charlie, coronel.";
		link.l2.go = "DTSG_Kortni_Kech_1";
		break;

	case "DTSG_Kortni_Kech_1":
		dialog.text = "¿Oh? Debo admitir que me sorprendes, Capitán de Maure. Y, ¿qué, en tu opinión, sería equivalente a la calva del viejo artillero si una montaña de oro no te conviene?";
		link.l1 = "Lo dijiste tú mismo: una magnífica nave, con defectos de diseño corregidos. Estoy ansioso por probarla yo mismo. Todavía tienes los planos. Pero solo hay un Charlie. Además, te conviene mantenerme satisfecho.";
		link.l1.go = "DTSG_Kortni_Kech_2";
		break;

	case "DTSG_Kortni_Kech_2":
		if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
		{
			dialog.text = "Eres un negociador duro. ¿Tienes idea de cuánto nos costó construir solo uno de estos?";
			link.l1 = " (Confiable) (Honor) Lo sé perfectamente, por eso pregunto. Tu mano está en mis fauces hasta el codo. Puedes intentar dispararle a este lobo. Pero perderás la mano. Y no solo eso.";
		}
		else
		{
			dialog.text = "Tengo miedo de que construir uno de estos cueste mucho más que el oro que preparamos para ti. Pero me has divertido, Charles. De una buena manera.";
			link.l1 = "Valió la pena intentarlo.";
			if (!IsCharacterPerkOn(pchar, "Trustworthy"))
				notification("Perk Check Failed", "Trustworthy");
			if (sti(pchar.reputation.nobility) < 71)
				notification("Reputation Too Low! (" + XI_ConvertString(GetReputationName(71)) + ")", "None");
		}
		link.l1.go = "DTSG_Kortni_Kech_3";
		break;

	case "DTSG_Kortni_Kech_3":
		if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) > 70)
		{
			dialog.text = "Veo que sabes lo que quieres y persigues tus metas en la vida\nBueno, está bien. El queche es tuyo. Pero olvídate del dinero - el prestamista te dirá que no sabe nada.";
			link.l1 = "Eso me conviene.";
			link.l1.go = "DTSG_Kortni_Kech_4";
			pchar.questTemp.DTSG_Kech = true;
		}
		else
		{
			dialog.text = "Definitivamente. Mi vida ha sido una historia de aprovechar oportunidades y protegerme de los riesgos\nAsí que trae a Charlie aquí, y nos separaremos en paz. Después de eso, incluso puedes tomar el depósito. Pero me voy en este barco.";
			link.l1 = "Entonces, resolvámoslo.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
			pchar.questTemp.DTSG_depozit = true;
		}
		break;

	case "DTSG_Kortni_Kech_4":
		dialog.text = "No puedo decir que esté completamente satisfecho. Pero quiero terminar con esto rápidamente. Ahora dame lo que quiero.";
		link.l1 = "No 'qué', sino 'quién'. Pero como desees.";
		link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
		break;

	case "DTSG_Kortni_Dengi_1":
		dialog.text = "Ni yo puedo. Empiezo a creer que no se trata solo de lo que es un hombre, sino de con quién se rodea; un simple trabajo de capturar a un viejo artillero se convirtió en un dolor de cabeza por culpa de su capitán, es decir, tú, Charles\nLlama aquí a Charlie. Este lío terminará de una vez por todas; levaremos anclas, y nuestros barcos se separarán.";
		link.l1 = "¿Separarnos, dices?";
		link.l1.go = "DTSG_Kortni_Dengi_2";
		break;

	case "DTSG_Kortni_Dengi_2":
		dialog.text = "¿Parece sorprendido? ¿Pensó que el ketch era su legítimo premio? No somos piratas, Capitán de Maure. La gente civilizada vive según reglas diferentes, mucho más complejas. El barco se queda conmigo.";
		link.l1 = "Pues entonces...";
		link.l1.go = "DTSG_Kortni_VizyvaemKnippel";
		pchar.questTemp.DTSG_depozit = true;
		break;

	case "DTSG_Kortni_VizyvaemKnippel":
		DialogExit();

		// sld = CharacterFromID("Knippel");
		sld = GetCharacter(CreateCharacterClone(CharacterFromID("Knippel"), 0));
		sld.id = "KnippelClone";
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Kortni_VizyvaemKnippel_2";
		ChangeCharacterAddressGroup(sld, PChar.location, "reload", "reload1");
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

	case "DTSG_Kortni_VizyvaemKnippel_2":
		dialog.text = "¿Está bien, señor? ¿Es ese... el coronel?";
		link.l1 = "Sí, Charlie, es el coronel. Llegaste justo a tiempo - estaba a punto de ir a buscarte yo mismo.";
		link.l1.go = "DTSG_Kortni_VizyvaemKnippel_3";
		break;

	case "DTSG_Kortni_VizyvaemKnippel_3":
		dialog.text = "¿Buscarme, Capitán?.. ¿Ahora mismo? ¿Por qué has estado hablando con este... hombre tanto tiempo? Pensé que estabas en problemas, así que vine aquí yo mismo.";
		link.l1 = "Correcto. Todavía estamos en problemas a pesar de la victoria. Y continuaríamos así si el coronel y yo no hubiéramos encontrado una solución.";
		link.l1.go = "DTSG_Kortni_VizyvaemKnippel_4";
		break;

	case "DTSG_Kortni_VizyvaemKnippel_4":
		dialog.text = "¿Lograste convencerlo de que nos dejara en paz, señor?";
		link.l1 = "Desafortunadamente, solo yo. No nosotros. Tú... irás con él, Charlie.";
		link.l1.go = "DTSG_Kortni_VizyvaemKnippel_5";
		break;

	case "DTSG_Kortni_VizyvaemKnippel_5":
		dialog.text = "¿Qué?.. ¿Pero por qué?.. ¡Ganamos!";
		link.l1 = "¿No entiendes? No podemos seguir ganando constantemente, no se detendrán hasta tener tu cabeza.";
		link.l1.go = "DTSG_Kortni_VizyvaemKnippel_6";
		break;

	case "DTSG_Kortni_VizyvaemKnippel_6":
		dialog.text = "No puedo creer que le estés haciendo esto al viejo Charlie, Capitán. Eres igual que Dick. Ambos me dijeron una vez que eran mis amigos. Y ambos me abandonaron a mí y a todos los que estaban cerca de ellos.";
		link.l1 = "Eso es la carga de un capitán, su responsabilidad. Veo que no puedes entender eso porque todo lo que tenías que hacer era cargar los cañones con balas de cañón.";
		link.l1.go = "DTSG_Kortni_VizyvaemKnippel_7";
		break;

	case "DTSG_Kortni_VizyvaemKnippel_7":
		dialog.text = "¿No entiendes?.. ¿Quizás simplemente no soy un traidor como tú? ¿Sabes a dónde deberías ir?";
		link.l1 = "¿Al infierno? Tal vez tengas razón. Todos lo merecemos.";
		link.l1.go = "DTSG_Kortni_VizyvaemKnippel_8";
		break;

	case "DTSG_Kortni_VizyvaemKnippel_8":
		dialog.text = "¡Métase eso por donde le quepa, señor!";
		link.l1 = "...";
		link.l1.go = "DTSG_Kortni_VizyvaemKnippel_9";
		break;

	case "DTSG_Kortni_VizyvaemKnippel_9":
		DialogExit();

		sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Kortni_VizyvaemKnippel_10";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);

		sld = CharacterFromID("KnippelClone");
		LAi_SetActorType(sld);
		sld = CharacterFromID("Knippel");
		RemovePassenger(pchar, sld);
		break;

	case "DTSG_Kortni_VizyvaemKnippel_10":
		dialog.text = "Divertidísimo. Casi me reí. ¿Lo oíste, Brian?\nA veces escuchar a simples campesinos hablar se siente como una brisa y no irrita en absoluto. Has tomado la decisión correcta, Charles. Entiendo lo difícil que es para ti. Pero consuélate sabiendo que ni tú ni ninguno de tus hombres sufrirán ahora.";
		link.l1 = "Espero que mantengas esta promesa, Coronel.";
		link.l1.go = "DTSG_Kortni_VizyvaemKnippel_11";
		break;

	case "DTSG_Kortni_VizyvaemKnippel_11":
		dialog.text = "Soy un hombre de palabra. El destino de Abigail es una prueba de ello. Mira a Brian también. Un pirata francés, pero tomó la decisión correcta cuando era el momento de unirse al lado correcto. Y nadie lo toca mientras nos sirva fielmente. Como él, estás moviéndote en la dirección correcta, Capitán de Maure.";
		if (CheckAttribute(pchar, "questTemp.DTSG_Kech"))
		{
			link.l1 = "Hablando de mudanza. Quiero salir de aquí lo antes posible. En este, sin duda, rápido barco que me prometiste, Coronel.";
		}
		else
		{
			link.l1 = "No soy un pirata. Y no planeo unirme a la flota inglesa todavía. Pero sí tengo la intención de reclamar la recompensa prometida.";
		}
		link.l1.go = "DTSG_Kortni_VizyvaemKnippel_12";
		break;

	case "DTSG_Kortni_VizyvaemKnippel_12":
		if (CheckAttribute(pchar, "questTemp.DTSG_Kech"))
		{
			dialog.text = "No lo ocultaré, es como arrancarla de mi corazón. Tendré que gastar en uno nuevo, pero quizá merezca la pena. Llevo demasiado tiempo preocupada por la idea de que Charlie se entere...\nSi no habla o comete delitos graves contra Inglaterra, considere que ya no somos enemigos. Disfruta del nuevo barco; es realmente hermoso. Adiós, Charles. Brian, prepara un barco para nosotros. Charlie, sígueme ya que no tienes nada que decir al respecto.";
			link.l1 = "Adiós.  Todos ustedes.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_13";
		}
		else
		{
			dialog.text = "Una lástima, siempre necesitamos gente capaz, sin importar su nacionalidad. Pero, por supuesto, aún mereces la recompensa. Puedes ir a Port Royal con tranquilidad, llegaré allí antes que cualquier otro barco en este balandro.";
			link.l1 = "Eso espero. Y espero que no haya una escolta armada esperándome en Port Royal.";
			link.l1.go = "DTSG_Kortni_VizyvaemKnippel_14";
		}
		break;

	case "DTSG_Kortni_VizyvaemKnippel_13":
		DialogExit();

		AddQuestRecord("DTSG", "20");
		CloseQuestHeader("DTSG");
		ChangeOfficersLoyality("bad_all", 5);
		ChangeCharacterComplexReputation(pchar, "nobility", -5);
		ChangeCharacterComplexReputation(pchar, "fame", -10);
		AddCrewMorale(Pchar, -10);
		LAi_ReloadBoarding();
		break;

	case "DTSG_Kortni_VizyvaemKnippel_14":
		dialog.text = "¿Dudas de mi palabra otra vez? Qué vergüenza. Te has ganado la gratitud de toda la marina inglesa. Si alguna vez necesitas algo, o decides unirte a nosotros, contáctame, Capitán de Maure.";
		link.l1 = "Una vez, intenté obtener apoyo y conexiones con la inteligencia inglesa. No funcionó. Así que adiós, coronel.";
		link.l1.go = "DTSG_Kortni_VizyvaemKnippel_15";
		break;

	case "DTSG_Kortni_VizyvaemKnippel_15":
		DialogExit();

		if (CheckAttribute(pchar, "questTemp.DTSG_depozit"))
		{
			ChangeCharacterNationReputation(pchar, ENGLAND, 30);
		}
		pchar.GenQuest.CannotTakeShip = true;
		PChar.quest.DTSG_Kortni_KechNeNash.win_condition.l1 = "MapEnter";
		PChar.quest.DTSG_Kortni_KechNeNash.win_condition = "DTSG_Kortni_KechNeNash";
		AddQuestRecord("DTSG", "21");
		CloseQuestHeader("DTSG");
		ChangeOfficersLoyality("bad_all", 5);
		ChangeCharacterComplexReputation(pchar, "nobility", -5);
		ChangeCharacterComplexReputation(pchar, "fame", -10);
		AddCrewMorale(Pchar, -10);
		LAi_ReloadBoarding();
		Achievment_Set("ach_CL_114");
		break;
	}
}
