// Эркюль Тонзаг, он же Плешивый Гастон
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	string sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_", 0) != -1)
	{
		i = findsubstr(sAttr, "_", 0);
		NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
		Dialog.CurrentNode = "SetGunBullets2";
	}

	switch (Dialog.CurrentNode)
	{
	case "First time":
		if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MainBegin")
		{
			dialog.text = "Bueno, hola, " + pchar.name + ". Me alegra verte vivo.";
			link.l1 = "¡Gastón! ¿Eres tú?";
			link.l1.go = "SJ_talk";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.HWIC.Self") && pchar.questTemp.HWIC.Self == "MeetTonzag")
		{
			dialog.text = "Saludos, " + pchar.name + ". Ya sé sobre tus tratos - John me contó todo. Ni siquiera sé qué decir. ¡Te admiro!";
			link.l1 = "¡Me complace escuchar tales alabanzas de ti, Hércules!";
			link.l1.go = "SJ_talk_11";
			break;
		}
		dialog.text = "Buenas tardes. ¿Tienes algún negocio para mí?";
		link.l1 = "No. Mi error. Lo siento. Adiós. .";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "SJ_talk":
		dialog.text = "Me conocías por ese nombre. Pero mi verdadero nombre es Hércules. Hércules Tonzag.";
		link.l1 = "¡Santo Señor! También me alegra verte... No te reconocí en el calor de la pelea. Llegaste justo a tiempo con tu ayuda.";
		link.l1.go = "SJ_talk_1";
		break;

	case "SJ_talk_1":
		dialog.text = "Justo después de tu partida, recibí noticias de que Fleetwood ha intensificado los esfuerzos para proteger su casa. Sugerí que puede haber una trampa detrás de esto. Inmediatamente zarpé hacia Antigua en mi barco 'Crepúsculo' - y, como ves ahora, por una buena razón.";
		link.l1 = "Verdad. Apenas logré lidiar con los guardias dentro de la casa, pero estaba demasiado exhausto para seguir peleando en la calle...";
		link.l1.go = "SJ_talk_2";
		break;

	case "SJ_talk_2":
		dialog.text = "Después de esta pelea, Fleetwood puso a un espía holandés en la lista de buscados. Pensaron que eras un espía holandés. Él está en una enemistad inveterada con ellos. La peor parte fue que un soldado en la casa sobrevivió y recordó tu cara. Pero, de todos modos, no es un problema ahora. He terminado lo que habías comenzado. Este soldado ya no podrá reconocer a nadie, y nadie lo reconocerá a él...";
		link.l1 = "¿Lo mataste? Ya veo...";
		link.l1.go = "SJ_talk_3";
		break;

	case "SJ_talk_3":
		dialog.text = "Sí. Mientras yacías inconsciente en la casa de John, herí a Fleetwood, pero el cabrón logró sobrevivir. Lo dejé ciego - le eché pimienta en los ojos, y luego le golpeé antes de que pudiera desenfundar su espada. Pero la escoria llevaba una cota de malla bajo su uniforme - le salvó la vida. Astuto. Ahora está en casa en la cama con seguridad reforzada. Es muy desafortunado que haya sobrevivido.";
		link.l1 = "Entonces, ¿tu tarea principal en Antigua era eliminar a Fleetwood?";
		link.l1.go = "SJ_talk_4";
		break;

	case "SJ_talk_4":
		dialog.text = "En general, sí. Ahora parece imposible, sin embargo - la casa está siempre cerrada, hay media docena de guardias seleccionados de servicio las veinticuatro horas del día, y solo permiten que lo vea su confidente - un viejo artillero llamado Charlie, apodado el Knippel.";
		link.l1 = "Eso ya es algo...";
		link.l1.go = "SJ_talk_5";
		break;

	case "SJ_talk_5":
		dialog.text = "Espera un poco... ¿Vas a interferir en este asunto?";
		link.l1 = "¿Por qué no? ¿No necesitas ayuda? Tú me salvaste, y quiero ayudar. Además, todavía necesito monedas.";
		link.l1.go = "SJ_talk_6";
		// belamour legendary edition -->
		link.l2 = "¿Por qué no?  Sois gente seria. Y la gente seria paga generosamente. Sólo busco un trabajo.";
		link.l2.go = "SJ_talk_6a";
		break;

	case "SJ_talk_6a":
		ChangeCharacterComplexReputation(pchar, "nobility", -1);
		AddCharacterExpToSkill(pchar, "Sneak", 120);
		dialog.text = "Créeme, amigo, no lo lograrás. Eres un buen tipo, todo un talento, y el cuaderno de bitácora que conseguiste me ayudó a planear un intento contra la vida de Fleetwood, hiciste un buen trabajo al cortar a los guardias - pero nunca podrás llegar a Fleetwood ahora. Ni siquiera yo tengo la menor idea de cómo hacerlo.";
		if (pchar.Ship.Type == SHIP_NOTUSED)
		{
			link.l1 = "Lo pensaré. Todavía tengo tiempo. Es una pena que mi barco haya sido arrestado, y no tenga una tripulación.";
			link.l1.go = "SJ_talk_7";
		}
		else
		{
			link.l1 = "Pensaré en ello. Tengo tiempo y un barco.";
			link.l1.go = "SJ_talk_8";
		}
		break;

	case "SJ_talk_6":
		AddCharacterExpToSkill(pchar, "Leadership", 120);
		// <-- legendary edition
		dialog.text = "Créeme, amigo, no lo lograrás. Eres un buen tipo, un verdadero talento, y el cuaderno de bitácora que trajiste me ayudó a planear un atentado contra la vida de Fleetwood, hiciste un buen trabajo cortando a los guardias, pero nunca podrás llegar a Fleetwood ahora. Ni siquiera yo tengo la menor idea de cómo hacerlo.";
		if (pchar.Ship.Type == SHIP_NOTUSED)
		{
			link.l1 = "Lo pensaré. Todavía tengo tiempo. Es una pena que mi barco fuera arrestado y no tenga tripulación.";
			link.l1.go = "SJ_talk_7";
		}
		else
		{
			link.l1 = "Lo pensaré. Tengo tiempo y un barco.";
			link.l1.go = "SJ_talk_8";
		}
		break;

	case "SJ_talk_7":
		dialog.text = "No te preocupes por eso. Cuando tu vieja bañera fue arrestada, llevé a todos tus oficiales y a algunos de los marineros a bordo de mi 'Crepúsculo'. Saben que estás vivo y acordaron permanecer en servicio. Y como recompensa por el diario, te cedo mi barco 'Crepúsculo'.";
		link.l1 = "¡Gracias! ¡Recordaré eso!";
		link.l1.go = "SJ_talk_9";
		if (GetSummonSkillFromName(pchar, SKILL_SAILING) < 46)
		{
			pchar.Ship.Type = GenerateShipHand(pchar, SHIP_CAREERLUGGER, 12, 580, 30, 800, 20000, 16.5, 65.5, 1.6);
		}
		else
		{
			pchar.Ship.Type = GenerateShipHand(pchar, SHIP_SCHOONER, 16, 1900, 50, 1350, 25000, 13.5, 55.0, 1.10);
		}
		pchar.Ship.name = "Twilight";
		SetBaseShipData(pchar);
		if (GetSummonSkillFromName(pchar, SKILL_SAILING) < 46)
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS12;
		else
			pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS16;
		SetCrewQuantityFull(pchar);
		pchar.Ship.Crew.Morale = 80;
		pchar.Ship.Crew.Exp.Sailors = 90;
		pchar.Ship.Crew.Exp.Cannoners = 70;
		pchar.Ship.Crew.Exp.Soldiers = 70;
		SetCharacterGoods(pchar, GOOD_BALLS, 100);
		SetCharacterGoods(pchar, GOOD_GRAPES, 100);
		SetCharacterGoods(pchar, GOOD_KNIPPELS, 100);
		SetCharacterGoods(pchar, GOOD_BOMBS, 100);
		SetCharacterGoods(pchar, GOOD_FOOD, 100);
		SetCharacterGoods(pchar, GOOD_POWDER, 300);
		SetCharacterGoods(pchar, GOOD_WEAPON, 60);
		SetCharacterGoods(pchar, GOOD_MEDICAMENT, 60);
		break;

	case "SJ_talk_8":
		AddMoneyToCharacter(pchar, 15000);
		dialog.text = "Sí, me gustaría pagarte por el diario. 15000 pesos - no tengo más por el momento, desafortunadamente. Lo arreglaremos en un día.";
		link.l1 = "No hay necesidad. Esto es suficiente. Si no hubieras llegado a tiempo, de todos modos no habría necesitado dinero.";
		link.l1.go = "SJ_talk_9";
		break;

	case "SJ_talk_9":
		dialog.text = "De acuerdo, " + pchar.name + ", tengo que irme. No voy a regresar a Bridgetown todavía. Si alguna vez me necesitas, pregunta a John. ¡Buena suerte!";
		link.l1 = "¡Buena suerte, Hércules!";
		link.l1.go = "SJ_talk_10";
		break;

	case "SJ_talk_10":
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10);
		DialogExit();
		AddQuestRecord("Holl_Gambit", "3-13");
		pchar.questTemp.HWIC.Self = "HuntFleetwood";
		AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;

	case "SJ_talk_11":
		dialog.text = "Me gustaría presentarte esta armadura por eliminar a Fleetwood. Te protegerá en futuras batallas. Ahora vamos a ver a John. Quiere hablar contigo y ofrecerte... un asunto interesante.";
		link.l1 = "Gracias por el regalo. Bueno, vamos...";
		link.l1.go = "SJ_talk_12";
		break;

	case "SJ_talk_12":
		DialogExit();
		GiveItem2Character(pchar, "cirass7"); // дать вещь
		sld = characterFromId("Merdok");
		AddLandQuestMark(sld, "questmarkmain");
		LAi_SetOwnerType(sld);
		LAi_SetActorType(npchar);
		LAi_ActorFollow(npchar, pchar, "", -1);
		AddQuestRecord("Holl_Gambit", "3-35");
		break;

	case "Tonzag_hired":
		dialog.text = "También me gustaría hablar contigo, capitán. Iba a enseñarte mi oficio, pero ahora veo que soy yo quien debería aprender de ti. Contrátame como oficial en tu barco - no te arrepentirás de esto.";
		link.l1 = "¡Con gusto, Hércules! ¡Bienvenido a la tripulación!";
		link.l1.go = "Tonzag_hired_1";
		link.l2 = "Hercule, no puedo imaginarme siendo tu superior. Gracias por tu oferta, pero simplemente no puedo verte como mi subordinado.";
		link.l2.go = "Tonzag_exit";
		break;

	case "Tonzag_hired_1": // Тонзага - в офицеры
		DialogExit();
		DeleteAttribute(npchar, "LifeDay");
		npchar.quest.OfficerPrice = sti(pchar.rank) * 500;
		npchar.OfficerWantToGo.DontGo = true;
		npchar.loyality = MAX_LOYALITY;
		AddPassenger(pchar, npchar, false);
		SetCharacterRemovable(npchar, true);
		npchar.Payment = true;
		LAi_SetOfficerType(npchar);
		npchar.greeting = "tonzag_hire";
		NextDiag.CurrentNode = "tonzag_officer";
		npchar.quest.meeting = true;
		npchar.HoldEquip = true;
		npchar.OfficerImmortal = true;
		npchar.Health.HP = 60.0;
		npchar.Health.maxHP = 60.0;
		LAi_SetImmortal(npchar, false);
		SetCharacterPerk(npchar, "ShipEscape");
		LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
		break;

	case "Tonzag_exit":
		dialog.text = "Como desees, " + pchar.name + "  Nos vemos.   Quizás nos encontremos de nuevo.   Ha sido un placer trabajar contigo.";
		link.l1 = "¡Buena suerte, amigo!";
		link.l1.go = "Tonzag_exit_1";
		break;

	case "Tonzag_exit_1":
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", -1);
		npchar.lifeday = 0;
		DialogExit();
		break;

	//--> ----------------------------------- офицерский блок ------------------------------------------
	case "tonzag_officer":
		dialog.text = "Te escucho, capitán. ¿Qué tienes que decir?";
		if (CheckAttribute(pchar, "questTemp.Dolly_Tieyasal") && !CheckAttribute(npchar, "quest.Tieyasal"))
		{
			Link.l4 = "Hercule, voy a la antigua ciudad india de Tayasal y, lo que es aún más inusual, mi camino pasa por una estatua de teletransportación. ¿Te unirás a mí?";
			Link.l4.go = "tieyasal";
		}

		////////////////////////казначей///////////////////////////////////////////////////////////
		// boal отчёт о корабле
		if (CheckAttribute(NPChar, "treasurer") && NPChar.treasurer == 1)
		{
			Link.l11 = "Hércules, dame un informe completo del barco.";
			Link.l11.go = "QMASTER_1";

			// Warship. Автозакупка товара
			Link.l12 = "Quiero que compres ciertos bienes cada vez que estemos atracados.";
			Link.l12.go = "QMASTER_2";
		}

		if (CheckAttribute(NPChar, "IsCompanionClone")) //////////////////компаньон//////////////////////////////////////////////
		{
			// dialog.text = "He llegado por su disposición, capitán.";
			Link.l2 = "Necesito darte varias órdenes.";
			Link.l2.go = "Companion_Tasks";
			NextDiag.TempNode = "tonzag_officer"; // не забыть менять в зависисомости от оффа
			break;
		}
		Link.l1 = "¡Escucha mi orden!";
		Link.l1.go = "stay_follow";
		link.l2 = "Nada por el momento. ¡A sus anchas!";
		link.l2.go = "exit";
		NextDiag.TempNode = "tonzag_officer";
		break;

	/////////////////////////// ответы для казначея ///////////////////////////////////
	case "QMASTER_1":
		dialog.Text = "Capitán, lo siento mucho, pero no trato con números y cálculos. Pregunta a van Merden - tiene talento para esas cosas, sin embargo, dudo que le interese dejar su nido.";
		Link.l1 = "Tienes razón, Hércules. Meh, tengo que encontrarme un pagador...";
		Link.l1.go = "exit";
		break;

	case "QMASTER_2":
		dialog.text = "Capitán, cuando era tabernero en Barbados solo compraba ron y provisiones. Y por provisiones, me refiero a alimentos adecuados, no a unas galletas y carne en conserva. Lo siento, pero eso no es de mi incumbencia.";
		link.l1 = "Quizás deberíamos convertir mi barco en una taberna... Solo bromeo, Hercule. No importa, lo haré yo mismo.";
		link.l1.go = "exit";
		break;

	// Указания для компаньона 19.02.08 -->/////////////////////////////////////////////////////////////////////////////////////////
	case "Companion_Tasks":
		dialog.Text = "Te estoy escuchando.";
		Link.l1 = "Esto se trata de abordar.";
		Link.l1.go = "Companion_TaskBoarding";
		Link.l2 = "Esto es sobre tu barco.";
		Link.l2.go = "Companion_TaskChange";
		Link.l8 = "Nada hasta ahora.";
		Link.l8.go = "exit";
		break;

	case "Companion_TaskBoarding":
		dialog.Text = "Entonces, ¿cuál es tu deseo?";
		Link.l1 = "No abordes barcos enemigos. Cuida de ti mismo y de la tripulación.";
		Link.l1.go = "Companion_TaskBoardingNo";
		Link.l2 = "Quiero que abordes los barcos enemigos.";
		Link.l2.go = "Companion_TaskBoardingYes";
		break;

	case "Companion_TaskChange":
		dialog.Text = "Entonces, ¿cuál es tu deseo?";
		Link.l1 = "Me gustaría que no cambiaras tu barco por otro después de abordarlo. Es demasiado valioso.";
		Link.l1.go = "Companion_TaskChangeNo";
		Link.l2 = "Cuando abordes barcos enemigos, puedes tomarlos para ti, si resultan ser decentes.";
		Link.l2.go = "Companion_TaskChangeYes";
		break;

	case "Companion_TaskBoardingNo":
		dialog.Text = "Sí, señor.";
		Link.l1 = "A sus anchas.";
		Link.l1.go = "exit";
		NPChar.Tasks.CanBoarding = false;
		break;

	case "Companion_TaskBoardingYes":
		dialog.Text = "Será hecho.";
		Link.l1 = "A sus anchas.";
		Link.l1.go = "exit";
		NPChar.Tasks.CanBoarding = true;
		break;

	case "Companion_TaskChangeNo":
		dialog.Text = "¡Sí, señor!";
		Link.l1 = "Será hecho.";
		Link.l1.go = "exit";
		NPChar.Tasks.CanChangeShipAfterBoarding = false;
		break;

	case "Companion_TaskChangeYes":
		dialog.Text = "Será hecho.";
		Link.l1 = "A sus órdenes.";
		Link.l1.go = "exit";
		NPChar.Tasks.CanChangeShipAfterBoarding = true;
		break;
		//	<========////////////////////////////////////////

	case "stay_follow":
		dialog.Text = "¿Cuáles son tus órdenes? ?";
		Link.l1 = "¡Quédate aquí!";
		Link.l1.go = "Boal_Stay";
		Link.l2 = "¡Sígueme y no te quedes atrás!";
		Link.l2.go = "Boal_Follow";
		sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
		if (sGun != "")
		{
			rItm = ItemsFromID(sGun);
			if (CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
			{
				Link.l3 = "Cambia el tipo de tus municiones.";
				Link.l3.go = "SetGunBullets";
			}
		}
		break;

	case "SetGunBullets":
		Dialog.Text = "Elección del tipo de munición:";
		sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
		rItm = ItemsFromID(sGun);
		makearef(rType, rItm.type);
		for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
		{
			sAttr = GetAttributeName(GetAttributeN(rType, i));
			sBullet = rItm.type.(sAttr).bullet;
			rItem = ItemsFromID(sBullet);
			attrL = "l" + i;
			Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
			;
			Link.(attrL).go = "SetGunBullets1_" + i;
		}
		break;

	case "SetGunBullets2":
		i = sti(NPChar.SetGunBullets) + 1;
		sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
		rItm = ItemsFromID(sGun);
		sAttr = "t" + i;
		sBullet = rItm.type.(sAttr).bullet;
		LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
		LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
		NextDiag.CurrentNode = NextDiag.TempNode;
		rItem = ItemsFromID(sBullet);
		notification(GetFullName(NPChar) + " " + XI_ConvertString("AmmoSelectNotif") + GetConvertStr(rItem.name, "ItemsDescribe.txt") + "", "AmmoSelect");
		DeleteAttribute(NPChar, "SetGunBullets");
		DialogExit();
		break;

	case "Boal_Stay":
		Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
		AddDialogExitQuestFunction("LandEnc_OfficerStay");
		dialog.Text = "¡Sí!";
		Link.l1 = "Relájate.";
		Link.l1.go = "Exit";
		Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
		break;

	case "Boal_Follow":
		SetCharacterTask_FollowCharacter(Npchar, PChar);
		dialog.Text = "¡Sí!";
		Link.l1 = "A sus anchas.";
		Link.l1.go = "Exit";
		break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------

		// на Тайясаль
	case "tieyasal":
		dialog.text = "Eres un afortunado hijo de perra, capitán. Me alegra haberme unido a ti cuando yo, tú y John trabajábamos juntos. ¡Que un tiburón me trague si no te apoyo en esta empresa!";
		link.l1 = "¡Gracias, Hércules! Me alegra haber tenido razón sobre ti.";
		link.l1.go = "tieyasal_1";
		break;

	case "tieyasal_1":
		dialog.text = "Entonces, ¿cuándo partimos?";
		link.l1 = "Un poco más tarde. Ahora deberíamos prepararnos para el viaje.";
		link.l1.go = "tieyasal_2";
		break;

	case "tieyasal_2":
		DialogExit();
		AddQuestRecord("Tieyasal", "23");
		npchar.quest.Tieyasal = "teleport";
		break;

	case "tonzag_jailed":
		dialog.text = "Prácticamente nada, Cap. Si esto tuviera que ver con nuestro negocio, ya nos habrían puesto en la mesa de tortura.\nDado que no nos llevaron a interrogatorio de inmediato, el asunto aparentemente no es urgente.\nO es una trampa o extorsión.\nNos dejarán aquí marinándonos un par de días sin explicar nada. Y luego vendrán con una oferta que aceptaremos.";
		link.l1 = "¿Experiencia personal?";
		link.l1.go = "tonzag_jailed_1";
		link.l2 = "Bueno, ¿hay alguna manera de hacer que vengan con tal oferta ahora mismo?";
		link.l2.go = "tonzag_jailed_2";
		locCameraFromToPos(-14.82, 0.92, 2.74, true, -60.00, -5.60, -22.70);
		break;

	case "tonzag_jailed_1":
		dialog.text = "Por supuesto. Gruoh una vez fue pagada por los familiares de un hombre muerto para librarlo de las caricias de despedida del verdugo de Trinidad.\nElla pagó al comandante por el derecho a pasear por las celdas de detención. Práctica común: muchos pagan a los soldados por la oportunidad de atormentar a las personas que no pueden defenderse sin testigos.\nEl hombre murió tranquilamente y sin sufrimiento. Trabajo limpio y decente.";
		link.l1 = "¿Gruoh? ¿Quién es ese?";
		link.l1.go = "tonzag_jailed_1_1";
		break;

	case "tonzag_jailed_1_1":
		dialog.text = "Lo siento, Capitán. Lugar equivocado y momento equivocado.";
		link.l1 = "";
		link.l1.go = "exit";
		break;

	case "tonzag_jailed_2":
		dialog.text = "Podemos intentarlo. Esperemos la hora de la comida, y cambiaré unas palabras con el centinela. Verás, todavía no han aprendido a registrar correctamente. Eh...";
		link.l1 = "¿Qué pasa?";
		link.l1.go = "tonzag_jailed_2_1";
		break;

	case "tonzag_jailed_2_1":
		dialog.text = "Extraña sensación, capitán. Incluso lo llamaría una premonición. Disculpe, hablemos más tarde.";
		link.l1 = "";
		link.l1.go = "exit";
		break;

	case "tonzag_killed_hunters":
		dialog.text = "¿Me perdí de algo, Capitán?";
		link.l1 = "Oh, nada especial, solo otro día en el mar. ¡Mira, viejo diablo! Me has hecho un buen lío aquí.";
		link.l1.go = "tonzag_killed_hunters_1";
		break;

	case "tonzag_killed_hunters_1":
		dialog.text = "La sangre se lava con agua fría, Capitán. Necesitamos hablar.";
		link.l1 = "¿Tú crees? No estaría mal sobrevivir este día para empezar.";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("Tonzag_Victory");
		break;

	case "tonzag_after_victory_helena":
		dialog.text = "Me alegra verte también, Rumba. Capitán, no te molestaré, hablaremos más tarde.";
		link.l1 = "";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("Tonzag_HelenBoardingDialog1");
		break;

	case "tonzag_after_victory_mary":
		dialog.text = "Hola, Pelirrojo. Capitán, no molestaré, hablaremos más tarde.";
		link.l1 = "";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("Tonzag_MaryBoardingDialog1");
		break;

	case "tonzag_after_victory_alonso":
		dialog.text = "Capitán, no le molestaré, hablaremos más tarde.";
		link.l1 = "";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("Tonzag_ShowFrame");
		break;

	case "tonzag_drink":
		dialog.text = "¿Listo para escucharme, Capitán?";
		link.l1 = "Ya es hora de que hablemos, Hércules. Acabo de darme cuenta de que no sé casi nada sobre ti.";
		link.l1.go = "tonzag_drink_1";
		break;

	case "tonzag_drink_1":
		dialog.text = "Entonces, es hora de conocernos. Saltemos los primeros años, aunque sea porque no hay nada de qué hablar: un soldado victorioso, un soldado derrotado, un desertor, un saqueador... ya sabes cómo es.";
		link.l1 = "No, en realidad no, pero hasta ahora esto suena bastante ordinario.";
		link.l1.go = "tonzag_drink_2";
		break;

	case "tonzag_drink_2":
		dialog.text = "Las oportunidades de carrera después de tal camino militar eran pocas para mí: un bandido, un ahorcado o un guardia digno de la Compañía Holandesa de las Indias Occidentales. Elegí la última, como entenderás.";
		link.l1 = "¿Desertaste de allí también?";
		link.l1.go = "tonzag_drink_3";
		break;

	case "tonzag_drink_3":
		dialog.text = "Al contrario, hice carrera allí. Recibí una oferta para unirme al ala de combate del departamento de inteligencia de la Compañía, donde conocí a mi futura esposa.";
		link.l1 = "Bien, hasta ahora la historia es bastante tranquila... especialmente si no piensas demasiado en los métodos de los holandeses.";
		link.l1.go = "tonzag_drink_4";
		break;

	case "tonzag_drink_4":
		dialog.text = "No ganarás mucho dinero siendo honesto, y puedes combatir la competencia de varias maneras. Sí, operábamos con métodos especiales...";
		link.l1 = "Creo que sé a qué te refieres...";
		link.l1.go = "tonzag_drink_5";
		break;

	case "tonzag_drink_5":
		dialog.text = "Sí, podría ser cualquier cosa: desde la piratería hasta incendiar almacenes con mercancías. Al final, el esquema fue descubierto, y fuimos disueltos... en papel, por supuesto. Así nació la Liga, conocida y controlada solo por los líderes elegidos de los altos escalones de la Compañía. Para un proscrito caribeño que valía algo, solo había dos opciones: la piratería o la Liga. Y la Liga usualmente pagaba mejor\nEn su mayor parte, la Liga todavía trabajaba para los holandeses, pero también podía aceptar encargos adicionales...";
		link.l1 = "Las cosas empiezan a aclararse...";
		link.l1.go = "tonzag_drink_6";
		break;

	case "tonzag_drink_6":
		dialog.text = "La Liga estaba detrás de esa farsa en Tortuga. Y luego ese grupo de desembarco...";
		link.l1 = "Lo supuse. Pero, ¿por qué?";
		link.l1.go = "tonzag_drink_7";
		break;

	case "tonzag_drink_7":
		dialog.text = "Porque nadie deja la Liga con vida, y no puedes salir impune de las cosas que hicimos allí, Capitán. Quería retirarme, así que lo intenté de todos modos. Como puedes ver, no muy exitosamente.";
		link.l1 = "¿Estás diciendo que tus antiguos colegas asumieron enormes gastos financieros, sacrificaron a casi cien personas, quemaron un brulote y arriesgaron su buque de guerra solo para... matarte por deserción?";
		link.l1.go = "tonzag_drink_8";
		break;

	case "tonzag_drink_8":
		dialog.text = "Yo era más que un don nadie en la Liga, Capitán. Sé demasiado sobre ellos. No pueden simplemente dejarme ir, y necesitan dejar esto claro, para que nadie más piense en dejar el negocio... Intentaron alcanzarme antes... hace bastante tiempo... Mataron a mi esposa y me desfiguraron, aunque les costó caro. No hay un final feliz para esta historia, Capitán. Sólo dé una orden, y dejaré el barco y me ocuparé de ellos por última vez.";
		link.l1 = "No digas tonterías, Hércules... ¿Y qué papel desempeñó Lucas Rodenburg en todo esto? ¡Él debió estar involucrado en estos asuntos! Tu, o más bien su, 'organización', la Liga...";
		link.l1.go = "tonzag_drink_9";
		break;

	case "tonzag_drink_9":
		dialog.text = "Diferentes agencias, Capitán. Admito que a menudo obedecían a la misma persona y trabajaban estrechamente. Pero los agentes especiales de Rodenburg realizaban ataques de precisión, mientras que la Liga llevaba a cabo operaciones masivas. ¿Y qué ha sido de la Liga ahora? La organización ya no existe, como puedes ver: estoy aquí contigo, John Murdock se fue, Longway se escapó, Van Berg está en el fondo del mar, Rodenburg fue ejecutado... Aun así, le debía a ese difunto sinvergüenza. Me notó en la Liga, y cuando intenté dejarla, me sacó de un gran problema y me convirtió en su lugarteniente. Por supuesto, a los demás no les gustó, pero nadie se atrevió a desobedecerle... Y luego, bajo las circunstancias conocidas, decidió deshacerse de Murdock y de mí, pero tú interviniste y me tomaste a tu servicio. Y pensé: 'Aquí está mi segunda oportunidad para romper con el pasado...' Derrotaste a Rodenburg, la Liga perdió a su patrón, ya no había peligro... Pero, por supuesto, me equivoqué... Viejo tonto... Pero basta de eso, Capitán. Pensemos en qué hacer a continuación, si, por supuesto, realmente no planeas dejarme en el primer puerto.";
		link.l1 = "No lo tengo. ¿Supongo que tienes un plan?";
		link.l1.go = "tonzag_drink_10";
		break;

	case "tonzag_drink_10":
		dialog.text = "No es nada especial, en realidad. Nunca podremos acabar con todos ellos, pero podemos infligirles pérdidas tan grandes que no les valdrá la pena seguir viniendo tras de mí... de nosotros.";
		link.l1 = "¿Y cómo hacemos eso? ¿Tienen un campamento?";
		link.l1.go = "tonzag_drink_11";
		break;

	case "tonzag_drink_11":
		dialog.text = "¿Una gran fortaleza? Difícilmente. Sería demasiado llamativa y peligrosa para la Liga. Y por pérdidas, no me refiero a pérdidas humanas - no les importan las personas, pero no disfrutarán perdiendo oro. El dinero de la Compañía ya no les llega, ¿verdad? Dudo que la Liga haya encontrado un nuevo mecenas, así que deben estar exprimiendo oro de algún otro lugar.";
		link.l1 = "¿Y qué lugar sería ese?";
		link.l1.go = "tonzag_drink_12";
		break;

	case "tonzag_drink_12":
		dialog.text = "No lo sé, Capitán.";
		link.l1 = "¡Hercule, pero acabas de decir que te persiguen precisamente porque sabes demasiado!";
		link.l1.go = "tonzag_drink_13";
		break;

	case "tonzag_drink_13":
		dialog.text = "Déjame pensar... Quizás la Liga esté operando actualmente contra los españoles. Son los principales candidatos para un buen sacudón. Hablando de eso, Rodenburg siempre se llevaba bien con los gordos castellanos. A veces dirigía a los chicos de la Liga hacia ellos para varios trabajos y siempre prohibía causarles cualquier daño, lo cual, por cierto, a los chicos no les gustaba mucho...";
		link.l1 = "¿Buenos términos, dices? ¿Y qué hay de ese Hidalgo y su dedo que me hiciste arrastrar a tu taberna?";
		link.l1.go = "tonzag_drink_14";
		break;

	case "tonzag_drink_14":
		dialog.text = "Fue un caso especial, un pedido adicional. Si te sientes culpable, Capitán, puedes estar tranquilo: ese Don recibió lo que merecía... Pero estoy hablando de otra cosa: después de que su empleador desapareció, los operativos de la Liga podrían simplemente ceder a sus deseos e intentar tomar una buena tajada del pastel español. Gracias a trabajar con los españoles bajo Rodenburg, saben dónde y qué tomar.";
		link.l1 = "Hum... podrías tener razón. Pero hasta donde sé, nadie realmente asalta bancos españoles, operando contra los españoles en el mar - eso depende de la dama fortuna... ¿Quizás deberíamos buscar alguna empresa española? ¿Una fábrica?";
		link.l1.go = "tonzag_drink_15";
		break;

	case "tonzag_drink_15":
		dialog.text = "Suposición razonable, Capitán... ¿Tenemos alguna otra pista?";
		link.l1 = "Mm... el barco que nos atacó hoy fue hacia el sur...";
		link.l1.go = "tonzag_drink_16";
		break;

	case "tonzag_drink_16":
		dialog.text = "Es poco probable que su capitán nos moleste de nuevo, pero debe advertir a los otros que las cosas no salieron como se planeó, y tal vez, transportar al personal a otro lugar. ¿Algo más?";
		if (CheckAttribute(pchar, "questTemp.TonzagQuest.KnowMain"))
		{
			link.l1 = "Sí, tuve una charla amistosa con el comandante de la prisión de Tortuga... Mencionó algo sobre el continente.";
			link.l1.go = "tonzag_drink_know";
		}
		else
		{
			link.l1 = "No, nada más.";
			link.l1.go = "tonzag_drink_notknow";
		}
		break;

	case "tonzag_drink_know":
		dialog.text = "¡Excelente, capitán! Sur, continente, españoles - significa que los encontraremos rápidamente. ¿Zarpamos? Y gracias por escuchar mi historia.";
		link.l1 = "Sí, vaya conversación de corazón a corazón que acabamos teniendo tú y yo... ¡Zarpemos!";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("Tonzag_ExitToSea");
		break;

	case "tonzag_drink_notknow":
		dialog.text = "No hay mucho de qué partir. Pero para gente como nosotros, eso es suficiente. ¿Nos dirigimos al sur? ¿Buscamos una empresa comercial española? Y gracias por escuchar mi historia.";
		link.l1 = "Sí, vaya conversación de corazón a corazón que terminamos teniendo tú y yo... ¡Zarpemos!";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("Tonzag_ExitToSea");
		break;

	case "tonzag_dead":
		dialog.text = "Mira, Capitán. Así es como operan.";
		link.l1 = "¿Y tú trabajaste así también?";
		link.l1.go = "tonzag_dead_1";
		break;

	case "tonzag_dead_1":
		dialog.text = "Vamos, veamos qué hay dentro.";
		link.l1 = "";
		link.l1.go = "exit";

		NextDiag.TempNode = "tonzag_officer";
		AddDialogExitQuestFunction("Tonzag_AfterDead");
		break;

	case "tonzag_afterminefight":
		dialog.text = "Un asunto sórdido, Capitán. Despejamos este antro, pero ciertamente no es el último...";
		link.l1 = "¿Qué pasa con la mina, Hércules?! ¡Toda esa gente afuera?! ¡También fueron 'despejados'! ¿Y qué quiso decir ese sinvergüenza?";
		link.l1.go = "tonzag_afterminefight_1";
		break;

	case "tonzag_afterminefight_1":
		dialog.text = "Discutamos esto más tarde, Capitán. Su comandante sobrevivió; necesitamos interrogarlo.";
		link.l1 = "¿Y qué si no sabe nada?";
		link.l1.go = "tonzag_afterminefight_2";
		break;

	case "tonzag_afterminefight_2":
		dialog.text = "Él sabe algo. Piénsalo: nos estaban esperando, se llevaron todo el oro y eliminaron a los testigos. Eso significa que tenían un plan. Quiero echar un vistazo por aquí, más tarde llevaré al canalla al barco yo mismo. Tú también deberías vigilar; quizá se precipitaron demasiado y se les escapó algo.";
		link.l1 = "Está bien, pero cuando volvamos al barco, ¡tenemos que tener una conversación seria!";
		link.l1.go = "exit";

		NextDiag.TempNode = "tonzag_officer";
		locations[FindLocation("LosTeques_town")].locators_radius.reload.gate_back = 1.0;
		DeleteAttribute(&locations[FindLocation("LosTeques_town")], "locators_radius.reload.reload1_back");
		AddDialogExitQuestFunction("Tonzag_PrepareJournal");
		break;

	case "tonzag_in_hold":
		dialog.text = "Buenas noticias, Capitán.";
		link.l1 = "No veo nada bueno en nuestra situación, Hércules. Vamos, necesitamos hablar en privado.";
		link.l1.go = "tonzag_in_hold_1";
		break;

	case "tonzag_in_hold_1":
		dialog.text = "Entonces, ¿es así, eh? Sí, Capitán.";
		link.l1 = "";
		link.l1.go = "exit";

		NextDiag.TempNode = "tonzag_officer";
		AddDialogExitQuestFunction("Tonzag_EnterAlonso");
		break;

	case "tonzag_drink_again":
		dialog.text = "Veo que vamos a tener una conversación seria, capitán.";
		link.l1 = "Sí, y seré yo quien hable. Para empezar, ¿no crees que aquí está surgiendo una cierta tendencia? ¡Montones de cadáveres nos siguen a donde vamos! Primero, te llevas una descarga de metralla en el vientre, y al día siguiente más de un centenar de personas, buenas y no tan buenas, mueren en... ¡No puedo ni llamarlo batalla naval! Un asentamiento fue arrasado hace solo unos días, y hoy hemos contribuido a la creciente pila al masacrar a un montón de personas en las minas.";
		link.l1.go = "tonzag_drink_again_1_1";
		break;

	case "tonzag_drink_again_1_1":
		dialog.text = "";
		link.l1 = "Naturalmente, me preocupa la perspectiva de que el montón se convierta en una montaña mañana, pero lo que realmente me asusta es que toda esta sangre se está derramando por una sola persona. ¡Y esa persona ocupa una posición significativa en mi tripulación!";
		link.l1.go = "tonzag_drink_again_1";
		break;

	case "tonzag_drink_again_1":
		dialog.text = "";
		link.l1 = "Segundo, me mentiste, Hercule. Ningún desertor vale el esfuerzo que tus antiguos colegas están poniendo en eliminarte. ¿Qué gritaba nuestro prisionero en las minas? ¿Traidor? ¿Portobello? ¿Gruoh? Has hecho algo, Hercule, y esta vez quiero la verdad.";
		link.l1.go = "tonzag_drink_again_2";
		break;

	case "tonzag_drink_again_2":
		dialog.text = "¿La verdad? La verdad es que deserté, junto con mi esposa Gruoh. Madame Tonzag no quería dejar la Liga; amaba esa vida, pero me amaba aún más a mí. Debíamos cuidar de un hidalgo español, pero él hizo una oferta mejor. Era nuestra oportunidad, y ambos aceptamos entrar a su servicio. Por supuesto, la Liga pensó que habíamos perecido en una misión y envió un segundo grupo a Portobello para terminar el trabajo y vengarse.";
		link.l1 = "¿Y los mataste a todos?";
		link.l1.go = "tonzag_drink_again_3";
		break;

	case "tonzag_drink_again_3":
		dialog.text = "Primero, mataron a Gruoh y me desfiguraron. El hidalgo ya no quiso tener nada que ver conmigo y me echó. Fue entonces cuando Rodenburg me encontró...";
		link.l1 = "¿Y cómo se supone que debo confiar en ti ahora? ¡Desertaste del ejército, abandonaste la Liga y mataste a tus propios socios! Cuando llegue el momento adecuado, ¿me traicionarás a mí también?";
		link.l1.go = "tonzag_drink_again_4";
		break;

	case "tonzag_drink_again_4":
		dialog.text = "Sí, deserté, rompí el contrato, maté a un par de docenas de miembros de la Liga. Pero he aprendido esa lección, Capitán. Y además, un hombre muerto no puede traicionar a nadie, y he estado muerto durante mucho tiempo, desde Portobello. Y quizás por eso ahora es tan difícil matarme.";
		link.l1 = "Basta por hoy. Siento que todavía no me estás contando todo.";
		link.l1.go = "tonzag_drink_again_5";
		break;

	case "tonzag_drink_again_5":
		dialog.text = "Me encargaré del prisionero yo mismo, ¿o deseas unirte?";
		link.l1 = "Vámonos. Lo interrogaré yo mismo.";
		link.l1.go = "tonzag_drink_again_hold";
		link.l2 = "No, tales asuntos no son para mí. ¡Nos vemos en mi camarote en media hora!";
		link.l2.go = "tonzag_drink_again_cabin";
		break;

	case "tonzag_drink_again_hold":
		DialogExit();

		NextDiag.CurrentNode = "tonzag_officer";
		AddDialogExitQuestFunction("Tonzag_ReturnToHold");
		break;

	case "tonzag_drink_again_cabin":
		DialogExit();

		NextDiag.CurrentNode = "tonzag_officer";
		AddDialogExitQuestFunction("Tonzag_ReturnToCabin");
		break;

	case "tonzag_hold":
		dialog.text = "¿Quién está a cargo ahora? ¿Arno?";
		link.l1 = "";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("Tonzag_HoldDialog1");
		break;

	case "tonzag_hold_1":
		dialog.text = "¿Esa escoria ascendió al poder? No te tomó mucho tiempo degradarte a una vulgar banda de bandidos...";
		link.l1 = "¿Quién es Austin?";
		link.l1.go = "tonzag_hold_2";
		break;

	case "tonzag_hold_2":
		dialog.text = "La pandilla de Austin era famosa por atraer a los capitanes libres hacia la naturaleza, desmembrarlos y despojar completamente sus cadáveres de cualquier dinero o baratija. Buen negocio, y no hay escasez de buscadores de aventuras, así que a nadie le importaba. Pero tropezaron con un Capitán, y así tuvo que llevar a su tripulación bajo el ala de la Compañía. Lo manteníamos controlado y lo soltábamos solo cuando necesitábamos resolver problemas de manera rápida y sencilla.";
		link.l1 = "Dudo que pueda negociar un trato con tal persona.";
		link.l1.go = "tonzag_hold_3";
		break;

	case "tonzag_hold_3":
		dialog.text = "Eso es seguro. Si él y su gente están al mando ahora, pronto la Liga se convertirá en otra pandilla más.";
		link.l1 = "";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("Tonzag_HoldDialog3");
		break;

	case "tonzag_after_hold":
		dialog.text = "Una conversación interesante que tuvimos.";
		link.l1 = "Me gustaría saber cuánto de eso es verdad... ¿Qué hay de la masacre en Portobello? Si no estaba mintiendo, significa que la última vez que tú y yo hablamos, nuevamente omitiste un par de hechos importantes de tu ilustre biografía.";
		link.l1.go = "tonzag_after_hold_1";
		break;

	case "tonzag_after_hold_1":
		dialog.text = "Hacía calor en Portobello, Capitán. Luché por mi vida, por la vida del patrón, por la vida de mi esposa. No tuve tiempo de contar a los muertos ni de llorar a cada campesino que apareció en la calle en el momento equivocado.";
		link.l1 = "¿En ese orden de prioridad?";
		link.l1.go = "tonzag_after_hold_2";
		break;

	case "tonzag_after_hold_2":
		dialog.text = "No, por supuesto que no. Primero las de ella. Siempre.";
		link.l1 = "¿Qué piensas? ¿Deberíamos ir a Caracas?";
		link.l1.go = "tonzag_after_hold_3";
		break;

	case "tonzag_after_hold_3":
		dialog.text = "Yo personalmente no lo haría, Capitán. Y le aconsejaría que no lo hiciera tampoco. Para la Liga, ya no eres un enemigo, y yo no les intereso, al menos por el momento mientras esté a tu servicio. Además, tengo esta desagradable sensación en el fondo...\nSerá malo si vamos allí. Muy malo. Esta historia no tiene un final feliz. Pero estaré contigo hasta el final, Capitán.";
		link.l1 = "Lo consideraré.";
		link.l1.go = "exit";

		if (CheckCharacterItem(pchar, "MerdokArchive"))
		{
			link.l1.go = "tonzag_after_hold_4";
		}

		AddDialogExitQuestFunction("Tonzag_GoToCaracas");
		break;

	case "tonzag_after_hold_4":
		dialog.text = "";
		link.l1 = "Por cierto, tenías razón - no lograron limpiar bien la mina. Mira.";
		link.l1.go = "tonzag_after_hold_5";
		break;

	case "tonzag_after_hold_5":
		dialog.text = "El diario de un oficial... cifrado, pero es una cifra antigua, la conozco \nNada interesante, parece. Era el diario de nuestro prisionero. Ahora está claro por qué estaba tan dispuesto a hablar. ¡Mira aquí, indicaciones de un tesoro escondido! ¡El bribón claramente planeaba retirarse y estaba listo para escabullirse en cualquier momento!";
		link.l1 = "¿Y dónde está este lugar escondido?";
		link.l1.go = "tonzag_after_hold_6";
		break;

	case "tonzag_after_hold_6":
		dialog.text = "Conoces esa isla, Capitán. En sus aguas, acabaste con Van Berd.";
		link.l1 = "Está bien, no está muy lejos, así que vamos a echar un vistazo. En cuanto a Caracas, aún no he decidido, pero creo que tenemos un mes.";
		link.l1.go = "tonzag_after_hold_7";
		break;

	case "tonzag_after_hold_7":
		dialog.text = "Como desees, Capitán. Estoy contigo hasta el final.";
		link.l1 = "";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("Tonzag_CreateLoot");
		break;

	case "tonzag_after_drink":
		dialog.text = "Está hecho, Capitán. Austin está actualmente en Caracas; creo que tenemos un mes.";
		link.l1 = "Primero lo primero. ¿Qué dijo el prisionero? ¿Quién es este Austin? ¿Y por qué deberíamos ir a Caracas?";
		link.l1.go = "tonzag_after_drink_1";
		break;

	case "tonzag_after_drink_1":
		dialog.text = "La banda de Austin era famosa por atraer a capitanes libres al desierto, descuartizarlos y despojar completamente sus cadáveres de cualquier dinero o chucherías. Buen negocio, y no faltan buscadores de aventuras, así que a nadie le importaba. Pero se toparon con un obstáculo con un capitán, y por eso tuvo que llevar a su tripulación bajo el ala de la Compañía. Lo mantuvimos con correa y lo soltamos solo cuando necesitábamos resolver problemas de manera rápida y sencilla.";
		link.l1 = "Dudo que pueda negociar un trato con una persona así.";
		link.l1.go = "tonzag_after_drink_2";
		break;

	case "tonzag_after_drink_2":
		dialog.text = "Eso es seguro. Si él y su gente están al mando ahora, pronto la Liga se convertirá en otra banda más. Pero yo no iría a Caracas, Capitán.";
		link.l1 = "¿En serio? ¿Tienes miedo?";
		link.l1.go = "tonzag_after_drink_3";
		break;

	case "tonzag_after_drink_3":
		dialog.text = "No es así, Capitán. Antes de morir por sus heridas, el prisionero reveló que ya no eres enemigo de la Liga, y yo no les intereso, al menos por el momento mientras esté a tu servicio. La Liga parece tener algún nuevo patrón influyente que ha ordenado dejarnos en paz\nY Caracas... Tengo este mal presentimiento en el fondo... Será malo si vamos allí. Muy malo. Esta historia no tiene un final feliz. Pero estaré contigo hasta el final, Capitán.";
		link.l1 = "Lo pensaré. Por supuesto, me gustaría resolver esta historia de una vez por todas, pero quizás tengas razón. Dudo que, después de los eventos de la semana pasada, se atrevan a acercarse a nosotros de nuevo.";
		link.l1.go = "exit";

		if (CheckCharacterItem(pchar, "MerdokArchive"))
		{
			link.l1.go = "tonzag_after_drink_4";
		}

		AddDialogExitQuestFunction("Tonzag_GoToCaracas");
		break;

	case "tonzag_after_drink_4":
		dialog.text = "";
		link.l1 = "Por cierto, tenías razón - no lograron limpiar bien la mina. Mira.";
		link.l1.go = "tonzag_after_drink_5";
		break;

	case "tonzag_after_drink_5":
		dialog.text = "El diario de un oficial... encriptado, pero es un cifrado antiguo, lo conozco\nNada interesante, parece. Era el diario de nuestro prisionero. ¡Mira las indicaciones de un tesoro escondido! ¡El canalla claramente planeaba retirarse y estaba listo para escabullirse en cualquier momento!";
		link.l1 = "¿Y dónde está este lugar escondido?";
		link.l1.go = "tonzag_after_drink_6";
		break;

	case "tonzag_after_drink_6":
		dialog.text = "Conoces esa isla, Capitán. En sus aguas, acabaste con Van Berd.";
		link.l1 = "Está bien, no está muy lejos, así que echemos un vistazo. En cuanto a Caracas, aún no he decidido, pero creo que tenemos un mes.";
		link.l1.go = "tonzag_after_drink_7";
		break;

	case "tonzag_after_drink_7":
		dialog.text = "Como desees, Capitán.";
		link.l1 = "";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("Tonzag_CreateLoot");
		break;

	case "tonzag_church":
		dialog.text = "Espera, Capitán. Voy allí solo.";
		link.l1 = "¿Y eso por qué? ¿Te sientes heroico ahora? Es demasiado tarde; tú has hecho este desastre, pero tenemos que limpiarlo juntos.";
		link.l1.go = "tonzag_church_1";
		break;

	case "tonzag_church_1":
		dialog.text = "No hay necesidad de que pagues por mis errores, Capitán. Tenías razón: dondequiera que voy, la gente muere y corre sangre inocente. Si entramos juntos a esa iglesia, será otro Portobello, y no quiero eso.";
		link.l1 = "¿Qué sucedió realmente allí?";
		link.l1.go = "tonzag_church_2";
		break;

	case "tonzag_church_2":
		dialog.text = "Una masacre. Quería retirarme, capitán. Quería tomar el oro, a mi esposa, y regresar a casa a Carcassonne. Sabía que la Liga enviaría más gente para terminar mi trabajo y tomé un generoso adelanto de mi nuevo patrón. Entonces todo lo que quedaba era enfrentar a la guardia de la ciudad contra mis antiguos cómplices y el nuevo empleador. En toda esa conmoción, debía desaparecer con el dinero, y quizás, si el tiempo lo permitía, robar a algunos gordos de Portobello.";
		link.l1 = "Buen plan, aunque yo lo habría hecho de otra manera. Demasiadas cosas podrían salir mal.";
		link.l1.go = "tonzag_church_2a";
		link.l2 = "Yo mismo no soy un ángel, pero tu enfoque hace que incluso yo me estremezca. Me sorprende que aún no me hayas traicionado, como hiciste con la Liga, el Hidalgo e incluso con tu propia esposa.";
		link.l2.go = "tonzag_church_2a";
		break;

	case "tonzag_church_2a":
		dialog.text = "Todo lo que podía salir mal, salió mal. Disparar una bala de tres libras hacia el palacio del gobernador fue un error. Apenas le hizo un rasguño al gobernador, pero a su hermosa hija, según he oído, tuvieron que amputarle las dos piernas por debajo de las rodillas para salvarle la vida. La respuesta fue horrible: un baño de sangre; pereció mucha gente, capitán. Ahora está viendo al último testigo vivo de aquellos sucesos, y no hace mucho, usted mismo cortó a otro.";
		link.l1 = "Explica.";
		link.l1.go = "tonzag_church_3";
		break;

	case "tonzag_church_2b":
		dialog.text = "Si Madame Tonzag aún viviera, te habría traicionado sin dudarlo, Capitán. Soy un muerto viviente, te sigo porque no tengo otro lugar en este mundo. Ahora estás mirando al último testigo viviente de esos eventos, y no hace mucho, tú mismo derribaste a otro.";
		link.l1 = "Explica.";
		link.l1.go = "tonzag_church_3";
		break;

	case "tonzag_church_3":
		dialog.text = "Perdóname, Capitán, por no contarte todo en el camino. Cuando nos conocimos, pensé que eras solo otro canalla como yo. ¿Y sabes lo primero que hice? Te envié a limpiar después de mí - a matar a ese Don español que inicialmente no quería matar y luego decidí traicionar. Ese Hidalgo, Rodríguez...";
		link.l1 = "¿Y para qué necesitabas su dedo?";
		link.l1.go = "tonzag_church_4";
		break;

	case "tonzag_church_4":
		dialog.text = "Sin trucos aquí. Solo una prueba, Capitán. Reclutamos docenas de jóvenes rufianes como tú cada año. Solo unos pocos pasaron la verificación básica de honestidad, y aun así murieron en las primeras operaciones. No se suponía que sobrevivieras a la operación con el diario de bitácora de Fleetwood. Planeaba simplemente entrar en la casa, acabar con los supervivientes y tomar el diario.";
		link.l1 = "Si mal no recuerdo, la historia tomó un giro ligeramente diferente.";
		link.l1.go = "tonzag_church_5";
		break;

	case "tonzag_church_5":
		dialog.text = "Así fue, Capitán. No sé qué me impulsó a ayudarte, pero luchaste contra los Zorros con tal entusiasmo por la vida que incluso me contagiaste, aunque solo fuese por un momento. Al final, sin saberlo, me salvaste. No me debes nada, Capitán. Y no dejaré que entres allí. Este es mi asunto, mi redención.";
		link.l1 = "Como desees, Hércules. Duele perder a un luchador así, pero te perdiste a ti mismo hace mucho tiempo, y no vales más sangre derramada. Tampoco me debes nada, y espero que encuentres redención en esa pequeña iglesia.";
		link.l1.go = "tonzag_church_bad";
		link.l2 = "Buen discurso, Hércules. ¡Vete al infierno! Si no lo has notado, tus problemas se han convertido en los míos últimamente. Eres mi oficial, y solo yo decidiré si mereces perdón o no. Así que tendrás que quedarte con nosotros un poco más y ganarte tu redención con valor como parte de mi tripulación.";
		link.l2.go = "tonzag_church_good";
		break;

	case "tonzag_church_bad":
		dialog.text = "Gracias por todo, capitán. ¡Adiós!";
		link.l1 = "";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("Tonzag_ChurchBad");
		break;

	case "tonzag_church_good":
		dialog.text = "¡Sí, sí, Capitán!";
		link.l1 = "";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("Tonzag_ChurchGood");
		break;

	case "tonzag_afterchurchfight":
		dialog.text = "He visto muchos sinvergüenzas en mi tiempo, Capitán, pero por primera vez, sentí un giro de horror dentro de mí. ¿Qué opinas: si un monstruo más pequeño mata a un monstruo más grande, cuenta eso como redención?";
		link.l1 = "¿Diluyen el ron con agua? Dime cuando lo averigües. Vámonos, hemos terminado aquí.";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("Tonzag_ResetTonzag");
		break;
	}
}