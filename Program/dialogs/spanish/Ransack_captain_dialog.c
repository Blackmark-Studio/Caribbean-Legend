// BOAL диалог пленников - в трюме
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ref offref;
	int i, cn;
	int qty;
	string attrLoc, sTmp;

	switch (Dialog.CurrentNode)
	{
	// -----------------------------------Диалог первый - первая встреча
	case "First time":
		//--> Jason, Ложный след
		if (CheckAttribute(pchar, "questTemp.FalseTrace.Prisoner") && GetFullName(npchar) == pchar.questTemp.FalseTrace.CapName)
		{
			dialog.text = "¿Qué quieres, capitán? ¿Discutir mi rescate? Quiero que sepas que me preocupo por el destino de la chica...";
			link.l1 = "¿Hablas de Katerine Rayner? Ya estoy informado sobre eso, " + pchar.questTemp.FalseTrace.CapName + ". Ella me pidió que hablara contigo.";
			link.l1.go = "FalseTrace_Prisoner";
			break;
		}
		//<-- Ложный след

		// Addon-2016 Jason ФМК-Гваделупа
		if (CheckAttribute(pchar, "questTemp.FMQG") && pchar.questTemp.FMQG != "fail" && CheckAttribute(pchar, "questTemp.FMQG.Prisoner") && GetFullName(npchar) == pchar.questTemp.FMQG.Prisoner)
		{
			dialog.text = "";
			link.l1 = "Mira ahora, don Juan, la traición es mala...";
			link.l1.go = "FMQG";
			break;
		}
		if (sti(NPChar.nation) == PIRATE)
		{
			dialog.text = RandSwear() + "Soy tu prisionero, " + GetAddress_Form(NPChar) + ". Pero quiero que sepas que " + NationNameNominative(sti(NPChar.nation)) + " nunca paga por su gente. Todos estamos por nosotros mismos.";
			link.l1 = "Bueno... Veo que no sacaré ningún beneficio de ti. Al menos puedo rescatarte como un criminal en cualquier colonia.";
			link.l1.go = "offender";
			if (FindFreeRandomOfficer() > 0)
			{
				link.l2 = "Mira, eres un luchador hábil y necesito gente como tú. ¿Te gustaría servir bajo mi mando?";
				link.l2.go = "free_to_officer";
			}
		}
		else
		{
			dialog.text = RandSwear() + "Soy tu prisionero, " + GetAddress_Form(NPChar) + ". " + NationNameNominative(sti(NPChar.nation)) + " pagará un buen precio por mi libertad.";
			if (NPChar.EncType == "trade" && FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
			{
				link.l1 = "Mira, eres un marinero hábil y necesito gente como tú. ¿Te gustaría servir bajo mi mando?";
				link.l1.go = "free_to_officer_trader";
			}
		}
		attrLoc = Sea_FindNearColony();
		if (attrLoc != "none")
		{
			link.l3 = "No estamos lejos de " + GetConvertStr(attrLoc + " Ciudad", "LocLables.txt") + ". Y podría dejarte ir aquí.";
			link.l3.go = "free_withoutFee";
		}
		else
		{
			link.l3 = "Ve al contramaestre, dile que te dé un casillero. Puedes desembarcar en el próximo puerto.";
			link.l3.go = "free_withoutFee_2";
		}
		link.l4 = "Supongo que te convertirás en un gran esclavo, fuerte y obediente.";
		link.l4.go = "Slave_1";
		link.l5 = "Has ignorado una orden de arriar tus velas y has resistido con fuerza. Serás ahorcado por ello. El contramaestre ya ha recibido mis órdenes.";
		link.l5.go = "PunishmentAction";
		link.l99 = "Lo sé.";
		link.l99.go = "exit";
		NextDiag.TempNode = "second time";
		break;

	case "second time":
		if (CheckAttribute(NPChar, "Hold_GenQuest") && !CheckAttribute(pchar, "GenQuest.Hold_GenQuest"))
		{
			switch (sti(NPChar.Hold_GenQuest.variant))
			{
			case 0: // "tip-off"
				dialog.text = RandPhraseSimple("Capitán, ¿le gustaría escuchar mi propuesta sobre una variante más rentable de mi rescate?", "Entiendo que no hay lugar para el regateo en mi lugar, pero ¿te gustaría escuchar mi propuesta?");
				link.l1 = "Estoy escuchando.";
				link.l1.go = "free_tip_off";
				break;

			case 1:
				dialog.text = "Capitán, ¿por qué no me liberas simplemente? No tengo valor para ti. Si me vendes a los esclavistas, solo obtendrás unas pocas monedas y mala fama.";
				link.l1 = "Y si simplemente te libero, no obtendré nada ...";
				link.l1.go = "free_by_hoard";
				attrLoc = Sea_FindNearColony();
				if (attrLoc != "none")
				{
					link.l2 = "Has ignorado una orden de arriar tus velas y has resistido con fuerza. Serás colgado por ello. El contramaestre ya ha recibido mis órdenes.";
					link.l2.go = "PunishmentAction";
				}
				else
				{
					link.l2 = "Eres realmente insistente, así que creo que puedo darte lo que quieres. Eres un hombre libre ahora. Abandona mi barco.";
					link.l2.go = "free_in_sea";
				}
				link.l3 = LinkRandPhrase("No pongas a prueba mi paciencia. Ya eres un hombre afortunado por seguir con vida.", "Tengo mis propios planes para ti.", "Supongo que aún puedes ser útil para mí en el futuro.");
				link.l3.go = "exit";
				break;

			case 2: // "ransom"
				dialog.text = "Capitán, esta incertidumbre me está matando. ¿Puedo saber qué planeas hacer conmigo?";
				link.l1 = "¿Tienes algo que ofrecerme?";
				link.l1.go = "free_buyout";
				link.l2 = RandPhraseSimple("Aún no tengo ninguna idea sobre ti.", RandPhraseSimple("¿Planes? ¿Una bola de cañón en tu cuello? Estoy bromeando, ¡ja!", "Eres mi prisionero y tengo todos los derechos para hacer contigo lo que quiera. Tu propia opinión no tiene valor aquí."));
				link.l2.go = "exit";
				break;
			}
			NextDiag.TempNode = "second time";
		}
		else
		{
			if (sti(NPChar.nation) == PIRATE)
			{
				dialog.text = "Capitán, ¿por qué no me dejas ir? No me necesitas. Elegir ser pirata fue la única opción para mí porque no tengo habilidades valiosas ni educación. Mi deseo era ganar algo de dinero y luego retirarme.";
				if (FindFreeRandomOfficer() > 0)
				{
					link.l2 = "Mira, eres un luchador hábil y necesito gargantas cortadas como tú. ¿Te gustaría ser mi oficial?";
					link.l2.go = "free_to_officer";
				}
				link.l3 = LinkRandPhrase("Sin piedad para ti. Hay muchos matones en el mar. Al menos ahora habrá uno menos navegando allí.", "¿Algún problema, 'lobo de mar'? Quédate aquí y mantén la boca cerrada.", "Las horcas están esperando a todos de tu calaña. Te venderé a las autoridades y eso será una gran lección para cualquier pirata.");
				link.l3.go = "exit";
			}
			else
			{
				if (NPChar.EncType == "trade")
				{
					dialog.text = "Capitán, os lo ruego... Libérame. Tengo familia e hijos y no podrán sobrevivir sin mí.";
					if (FindFreeRandomOfficer() > 0 && CheckAttribute(NPChar, "Back.Ship.Mode") && NPChar.Back.Ship.Mode == "trade")
					{
						link.l2 = "Mira, eres un marinero hábil y necesito gente como tú. ¿Te gustaría servir bajo mi mando?";
						link.l2.go = "free_to_officer_trader";
					}
					link.l3 = LinkRandPhrase("Tengo mis propios planes para ti.", "Supongo que aún puedes ser útil para mí en el futuro.", "Eres mi prisionero y tengo todos los derechos para hacer contigo lo que quiera.");
					link.l3.go = "exit";
				}
				if (NPChar.EncType == "war")
				{
					dialog.text = RandPhraseSimple("Capitán, he perdido una pelea y te suplico por tu misericordia.", "Capitán, imploro su generosidad. Entiendo que no hay razón para que me trate como a un prisionero de guerra, así que le pido que me perdone. Le doy mi palabra de que evitaré encontrarme con usted en el mar.");
					link.l2 = LinkRandPhrase("No pruebes mi paciencia. Ya eres un hombre afortunado por seguir vivo.", RandPhraseSimple("Tengo mis propios planes para ti.", "Supongo que aún puedes ser útil para mí en el futuro."), RandPhraseSimple("Eres mi prisionero y tengo todos los derechos para hacer contigo lo que quiera. Tu propia opinión no tiene valor aquí.", "Eres... bueno, eras un capitán de un barco de guerra y estabas consciente de los riesgos. No intentes representarte a ti mismo como un santo aquí."));
					link.l2.go = "exit";
					if (isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 1)
					{
						if (sti(Items[sti(pchar.EquipedPatentId)].Nation) == sti(NPChar.nation) && FindFreeRandomOfficer() > 0)
						{
							link.l3 = "Mira, eres un luchador habilidoso y necesito degolladores como tú. ¿Te gustaría ser mi oficial?";
							link.l3.go = "free_to_officer";
						}
					}
				}
			}
			attrLoc = Sea_FindNearColony();
			if (attrLoc != "none")
			{
				link.l4 = "No estamos lejos de " + GetConvertStr(attrLoc + " Pueblo", "LocLables.txt") + ". Y podría dejarte ir aquí.";
				link.l4.go = "free_withoutFee";
			}
			else
			{
				if (NPChar.EncType == "trade" || NPChar.EncType == "pirate")
				{
					link.l4 = "Ve al contramaestre, dile que te dé un casillero. Puedes desembarcar en el próximo puerto.";
					link.l4.go = "free_withoutFee_4";
				}
				else
				{
					link.l4 = "¡Maldito seas! Ve al contramaestre, dile que te dé un camarote. Puedes desembarcar en el próximo puerto. Y recuerda que nuestro próximo encuentro será el último.";
					link.l4.go = "free_withoutFee_4";
				}
			}
			link.l5 = "Has ignorado una orden de arriar tus velas y has resistido con fuerza. Serás ahorcado por ello. El contramaestre ya ha recibido mis órdenes.";
			link.l5.go = "PunishmentAction";
			NextDiag.TempNode = "second time";
		}
		break;

	case "offender":
		dialog.text = "¿Criminal? ¿Estás bromeando conmigo," + GetAddress_Form(NPChar) + "?";
		link.l1 = "Sin bromas. Eres un pirata.";
		link.l1.go = "exit";
		break;

	case "free_to_officer":
		if ((GetSummonSkillFromName(pchar, "Leadership") + 20) <= GetSummonSkillFromName(npchar, "Leadership"))
		{
			dialog.text = "¿Servir bajo tu mando? ¡Prefiero alimentar a los tiburones!";
			link.l1 = "Cuida tu lengua o los alimentarás.";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "¿Ser tu oficial, " + GetAddress_Form(NPChar) + "? Estoy de acuerdo. Conozco mi trabajo y no tengo nada que perder.";
			link.l1 = "¡Trato hecho! Ve y haz tu trabajo.";
			link.l1.go = "free_to_officer_Hire";
			link.l2 = "Espera un poco, he cambiado de opinión.";
			link.l2.go = "exit";
		}
		break;

	case "free_to_officer_trader":
		if (GetSummonSkillFromName(pchar, "Leadership") <= GetSummonSkillFromName(npchar, "Leadership"))
		{
			dialog.text = LinkRandPhrase("Es una oferta tentadora... pero debo rechazarla. Por principios.", "Lo siento, pero después de lo que has hecho con mis amigos... Es imposible.", "No, capitán. Después de todo este terror, ya no puedo hacer este trabajo. Hice un voto de que si la Virgen Bendita escucha mis oraciones y me concede la libertad, ya no navegaré más.");
			link.l1 = "Es tu elección. No seré persistente.";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "¿Por qué no? Soy un mal capitán, perdí mi barco y no me queda nada en la costa. Excepto facturas y deudas...";
			link.l1 = "¡Trato hecho! Ve al contramaestre y recoge tus raciones. Te daré una posición en mi barco un poco más tarde.";
			link.l1.go = "free_to_officer_Hire";
			link.l2 = "Espera un poco, he cambiado de opinión.";
			link.l2.go = "exit";
		}
		break;

	case "free_to_officer_Hire":
		NPChar.Dialog.Filename = "Enc_Officer_dialog.c";
		NPChar.greeting = "Gr_Officer";
		NPChar.loyality = 5 + rand(10);
		if (sti(NPChar.reputation) > 41)
		{
			NPChar.alignment = "good";
		}
		else
		{
			NPChar.alignment = "bad";
		}
		ReleasePrisoner(NPChar);		   // освободили пленника
		DeleteAttribute(NPChar, "LifeDay") // постоянный
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
		// тут трем накопивщиеся сабли и корабли 290704 BOAL -->
		DeleteAttribute(Npchar, "Ship");
		Npchar.Ship.Type = SHIP_NOTUSED;
		DeleteAttribute(Npchar, "Fellows");			  // его офицеры
		Npchar.Fellows.Passengers.id0 = Npchar.index; // свой пассажир

		Npchar.Fellows.Passengers.boatswain = "-1";
		Npchar.Fellows.Passengers.navigator = "-1";
		Npchar.Fellows.Passengers.doctor = "-1";
		Npchar.Fellows.Passengers.cannoner = "-1";
		Npchar.Fellows.Passengers.treasurer = "-1";
		Npchar.Fellows.Passengers.carpenter = "-1";

		if (CheckAttribute(NPChar, "Hold_GenQuest"))
			DeleteAttribute(NPChar, "Hold_GenQuest");

		AddDialogExitQuestFunction("LandEnc_OfficerHired");
		DialogExit();
		break;

	case "Slave_1":
		dialog.text = "Pero " + GetAddress_Form(NPChar) + ", ¡no puedes hacer eso! Me he rendido.";
		link.l1 = "¡Cierra tu boca! ... Átale.";
		link.l1.go = "Slave_2";
		link.l99 = "Está bien. Quédate aquí hasta que decida...";
		link.l99.go = "exit";
		break;

	case "Slave_2":
		OfficersReaction("bad");
		ChangeCharacterComplexReputation(pchar, "nobility", -2);
		if (rand(5) == 1)
		{
			dialog.text = "¡De ninguna manera! Mejor me mato antes que convertirme en esclavo.";
			link.l1 = "¡Alto a eso! ¡Es una orden!... ¡Contramaestre! Limpia la carga...";
			link.l1.go = "free_in_sea_4";
		}
		else
		{
			if (rand(1) == 1)
			{
				if (GetPrisonerQty() > 1)
				{
					dialog.text = "¡Carnicero! ¡Chicos, uníos a mí, no tenemos nada que perder!";
					link.l1 = "Elección equivocada, damas. Yo manejo los motines por mí mismo y de una manera muy rápida...";
					link.l1.go = "free_in_sea_battle_all";
				}
				else
				{
					dialog.text = "¡De ninguna manera! ¡Prefiero morir en la lucha!";
					link.l1 = "Como deseas...";
					link.l1.go = "free_in_sea_battle_1";
				}
			}
			else
			{
				dialog.text = "Oh, estoy de acuerdo. No tengo otra opción.";
				link.l1 = "Espléndido. Es mejor ser un esclavo respirando que un héroe muerto.";
				link.l1.go = "Slave_3";
			}
		}
		break;

	case "Slave_3":
		ReleasePrisoner(NPChar); //  пленника в рабы
		LAi_SetActorType(NPChar);
		LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
		ChangeCharacterComplexReputation(pchar, "nobility", -6);
		DialogExit();
		AddCharacterGoodsSimple(pchar, GOOD_SLAVES, 1);
		break;

	case "free_withoutFee":
		dialog.text = "Oh, " + GetAddress_Form(NPChar) + ", ¿realmente eres tan amable y me estás liberando sin rescate?";
		link.l1 = "Sí. Eres libre ahora," + GetFullName(NPChar);
		link.l1.go = "free_withoutFee_2";
		link.l99 = "Hm... ¡Tienes un punto! Necesito más tiempo para decidir.";
		link.l99.go = "exit";
		break;

	case "free_withoutFee_2":
		dialog.text = "Gracias, " + GetFullName(PChar) + "¡Rezaré por ti!";
		link.l1 = "Vete ahora, e intenta mantenerte vivo, de lo contrario mi generosidad será en vano.";
		link.l1.go = "free_withoutFee_3";
		OfficersReaction("good");
		break;

	case "free_withoutFee_3":
		ReleasePrisoner(NPChar); // освободили пленника
		LAi_SetActorType(NPChar);
		LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
		ChangeCharacterComplexReputation(pchar, "nobility", 2);
		DialogExit();
		break;

	case "free_withoutFee_4":
		switch (NPChar.EncType)
		{
		case "pirate":
			dialog.text = RandPhraseSimple("Gracias, capitán. Nunca olvidaré su bondad. Voy a dejar este trabajo y reparar pequeñas embarcaciones en puertos pacíficos. Puedo hacer eso.", "¡Gracias, capitán! Lo juro, abandonaré esta ingrata ocupación y me convertiré en pescador.");
			link.l1 = "Si estás siendo honesto, entonces te deseo suerte, y si no, entonces reza para nunca encontrarme de nuevo...";
			break;
		case "trade":
			dialog.text = "No sé ni cómo agradecerte, capitán. Ya había perdido la esperanza. Voy a contarle a todos sobre tu bondad. ¡Te doy mi palabra de que encenderé una vela por ti! Solo déjame llegar a una iglesia.";
			link.l1 = "Adiós. Y la próxima vez ni siquiera intentes resistirte. Dispara contra mí y será una sentencia de muerte para ti y tu tripulación.";
			break;
		case "war":
			dialog.text = "Mi agradecimiento, capitán. Rezaré por ti.";
			link.l1 = "Buena suerte, y recuerda, si decides cazarme será tu fin.";
			break;
		}
		link.l1.go = "free_withoutFee_3";
		break;

	case "free_in_sea_battle_1":
		ReleasePrisoner(NPChar); // освободили пленника
		LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
		LAi_SetFightMode(Pchar, true);
		LAi_SetWarriorType(NPChar);
		LAi_group_MoveCharacter(NPChar, LAI_GROUP_TmpEnemy);
		LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
		LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
		LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
		LAi_group_SetRelation(LAI_GROUP_TmpEnemy, "Prisoner", LAI_GROUP_NEITRAL);
		DialogExit();
		break;

	case "free_in_sea_battle_all":
		// ugeen --> привет Сиварду !!! после релиза пленников кол-во пассажиров уменьшается и цикл нихрена дальше не срабатывал
		for (int j = GetPassengersQuantity(pchar) - 1; j > -1; j--)
		{
			cn = GetPassenger(pchar, j);
			if (cn != -1)
			{
				offref = GetCharacter(cn);
				if (CheckAttribute(offref, "prisoned"))
				{
					if (sti(offref.prisoned) == true && GetRemovable(offref)) // ставим только фантомов
					{
						ReleasePrisoner(offref); // освободили пленника
						LAi_SetWarriorType(offref);
						LAi_warrior_DialogEnable(offref, false);
						LAi_group_MoveCharacter(offref, LAI_GROUP_TmpEnemy);
					}
				}
			}
		}
		LAi_LocationFightDisable(&Locations[FindLocation("My_Deck")], false);
		LAi_SetFightMode(Pchar, true);
		LAi_group_SetHearRadius(LAI_GROUP_TmpEnemy, 100.0);
		LAi_group_FightGroupsEx(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, true, Pchar, -1, false, false);
		LAi_group_SetRelation(LAI_GROUP_TmpEnemy, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_SetCheck(LAI_GROUP_TmpEnemy, "My_Deck_Battle_End");
		DialogExit();
		break;

	case "free_in_sea_4":
		ReleasePrisoner(NPChar); // освободили пленника
		NPChar.location = "";
		LAi_KillCharacter(NPChar);
		DialogExit();
		break;

	case "PunishmentAction":
		dialog.text = "Pero " + GetAddress_Form(NPChar) + ", ¡no puedes hacer eso! Me he rendido.";
		link.l1 = "Solo después de que tus hombres se fueron. Los traicionaste... ¡Contramaestre! Llévatelo.";
		link.l1.go = "PunishmentAction1";
		link.l2 = "Bueno... Necesito tiempo para pensar en ello. Quédate aquí.";
		link.l2.go = "exit";
		break;

	case "PunishmentAction1":
		OfficersReaction("bad");
		ChangeCharacterComplexReputation(pchar, "nobility", -2);
		AddCharacterExpToSkill(Pchar, "Leadership", -150);
		if (rand(1) == 1)
		{
			if (GetPrisonerQty() > 1)
			{
				dialog.text = "¡Carnicero! Chicos, no tenemos nada que perder!";
				link.l1 = "Mala elección, damas. Yo mismo trato con los motines de manera muy rápida...";
				link.l1.go = "free_in_sea_battle_all";
			}
			else
			{
				dialog.text = "¡De ninguna manera! ¡Prefiero morir en combate!";
				link.l1 = "Como desees...";
				link.l1.go = "free_in_sea_battle_1";
			}
		}
		else
		{
			dialog.text = "Al menos dame algo de tiempo para rezar...";
			link.l1 = "Reza, si quieres.";
			link.l1.go = "PunishmentAction2";
		}
		break;

	case "PunishmentAction2":
		ReleasePrisoner(NPChar); // освободили пленника
		NPChar.location = "";
		NPChar.LifeDay = 0;
		LAi_CharacterDisableDialog(NPChar);
		DialogExit();
		break;

	case "free_tip_off":
		dialog.text = "Tengo una información interesante que puede ser útil para un hombre como tú. Pero necesito tus garantías de que obtendré mi libertad a cambio.";
		link.l1 = "¿Cómo puedo darte mis garantías si ni siquiera conozco tu propuesta? Dudo que tu información me dé algo.";
		link.l1.go = "free_tip_off_0";
		link.l2 = "Solo puedo darte mi palabra.";
		link.l2.go = "free_tip_off_1";
		break;

	case "free_tip_off_0":
		ChangeCharacterComplexReputation(pchar, "nobility", -2);
		DeleteAttribute(NPChar, "Hold_GenQuest");
		DialogExit();
		break;

	case "free_tip_off_1":
		switch (NPChar.EncType)
		{
		case "trade":
			sTmp = "Me propuso un flete, pero este tipo era demasiado codicioso y rechacé la oferta.";
			break;
		case "war":
			sTmp = "Le he escoltado unas cuantas veces como comandante de un convoy.";
			break;
		case "pirate":
			sTmp = "Una vez tuve la idea de robarle, pero nunca he tenido la oportunidad de hacerlo.";
			break;
		}
		dialog.text = "Bien. Es suficiente para mí. Ahora directo al grano, en " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Voc") + " vive un rico comerciante " + NPChar.Hold_GenQuest.Name + ". " + "Hizo su fortuna en su barco '" + NPChar.Hold_GenQuest.ShipName + " vendiendo " + GetStrSmallRegister(XI_ConvertString(Goods[sti(NPChar.Hold_GenQuest.Goods)].Name + "Acc")) + " con ruta : " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.FromCity) + ", " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.ToCity) + ". " + "Cuando tiene demasiada carga, paga por una escolta." + sTmp + "Estoy seguro de que esta información es más valiosa para ti que la vida de un solo hombre.";
		link.l1 = "Dudo que esta información pueda ser útil para mí. No voy a cazar a comerciantes pacíficos.";
		link.l1.go = "free_tip_off_0";
		link.l2 = "No estoy seguro de que esta información me sirva, pero te he dado mi palabra. El contramaestre te colocará con mi tripulación y te dejará ir en el puerto más cercano.";
		link.l2.go = "free_tip_off_2";
		break;

	case "free_tip_off_2":
		dialog.text = "¡Mis agradecimientos, capitán! ¡No tenía dudas de tu honestidad!";
		link.l1 = RandPhraseSimple(RandPhraseSimple("Desearía poder decir lo mismo de ti", "Lo siento pero no puedo decir lo mismo de ti."), RandPhraseSimple("Ve y recuerda que la próxima vez no seré tan generoso.", "Vete y mantente fuera de mi camino. La próxima vez no te creeré tan fácilmente."));
		link.l1.go = "free_tip_off_3";
		break;

	case "free_tip_off_3":
		pchar.GenQuest.Hold_GenQuest.Goods = NPChar.Hold_GenQuest.Goods;
		pchar.GenQuest.Hold_GenQuest.Nation = NPChar.Hold_GenQuest.Nation;
		pchar.GenQuest.Hold_GenQuest.Name = NPChar.Hold_GenQuest.Name;
		pchar.GenQuest.Hold_GenQuest.ToCity = NPChar.Hold_GenQuest.ToCity;
		pchar.GenQuest.Hold_GenQuest.FromCity = NPChar.Hold_GenQuest.FromCity;
		pchar.GenQuest.Hold_GenQuest.ShipName = NPChar.Hold_GenQuest.ShipName;
		pchar.GenQuest.Hold_GenQuest.City = NPChar.Hold_GenQuest.City;
		pchar.GenQuest.Hold_GenQuest.CapName = GetFullName(NPChar);
		pchar.GenQuest.Hold_GenQuest.Island = GetArealByCityName(pchar.GenQuest.Hold_GenQuest.City);
		pchar.GenQuest.Hold_GenQuest.Speak_Tavern = true;

		ReOpenQuestHeader("HoldQuest");
		AddQuestRecord("HoldQuest", "1");
		AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
		AddQuestUserData("HoldQuest", "sGoods", GetStrSmallRegister(XI_ConvertString(Goods[sti(pchar.GenQuest.Hold_GenQuest.Goods)].Name + "Acc")));
		AddQuestUserData("HoldQuest", "sCityFrom", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.FromCity));
		AddQuestUserData("HoldQuest", "sCityTo", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.ToCity));
		AddQuestUserData("HoldQuest", "sShipName", pchar.GenQuest.Hold_GenQuest.ShipName);

		SetFunctionTimerCondition("Hold_GenQuest_SetMerchant_pre", 0, 0, 1 + rand(2), false);
		SetFunctionTimerCondition("Hold_GenQuest_MerchantOver", 0, 0, 30, false);

		ReleasePrisoner(NPChar); // освободили пленника
		LAi_SetActorType(NPChar);
		NPChar.LifeDay = 0;
		LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
		DialogExit();
		break;

	case "free_buyout":
		dialog.text = "Y tengo una propuesta para ti. En " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Voc") + " vive mi amigo, " + NPChar.Hold_GenQuest.Name + " es su nombre. Una vez tuvimos un negocio juntos." + "Encuéntralo allí. Estoy seguro de que te pagará una gran suma. Me debe y me ocuparé de él yo mismo.";
		link.l1 = "¿Tu amigo, eh? Vamos a verlo.";
		link.l1.go = "free_buyout1";
		link.l2 = "¿Por qué debería buscar a tu amigo si puedo conseguir rescate en el primer puerto?";
		link.l2.go = "free_tip_off_0";
		break;

	case "free_buyout1":
		LAi_CharacterDisableDialog(NPChar);

		pchar.GenQuest.Hold_GenQuest.City = NPChar.Hold_GenQuest.City;
		pchar.GenQuest.Hold_GenQuest.Nation = NPChar.Hold_GenQuest.Nation;
		pchar.GenQuest.Hold_GenQuest.Name = NPChar.Hold_GenQuest.Name;
		pchar.GenQuest.Hold_GenQuest.CapName = GetFullName(NPChar);
		pchar.GenQuest.Hold_GenQuest.CapId = NPChar.Id;
		pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1);
		pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;

		ReOpenQuestHeader("HoldQuest");
		AddQuestRecord("HoldQuest", "6");
		AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
		AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Voc"));
		AddQuestUserData("HoldQuest", "sNameChar", NPChar.Hold_GenQuest.Name);
		DialogExit();
		break;

	case "free_by_hoard":
		dialog.text = "De hecho, conozco a un hombre que tiene un gran tesoro, pero no tiene agallas para usarlo.";
		link.l1 = "¿Qué quieres decir?";
		link.l1.go = "free_by_hoard1";
		link.l2 = "Resérvese sus historias. Sería mejor que se preocupara por su alma.";
		link.l2.go = "free_tip_off_0";
		break;

	case "free_by_hoard1":
		dialog.text = "Te estoy contando la historia que lleva a grandes tesoros. Necesito tu palabra a cambio de que me dejarás ir en el próximo puerto.";
		link.l1 = "Decidiré cuándo y qué hacer contigo por mí mismo. Tus 'historias' no marcarán la diferencia.";
		link.l1.go = "free_tip_off_0";
		link.l2 = "Estoy escuchando. Tienes mi palabra.";
		link.l2.go = "free_by_hoard2";
		break;

	case "free_by_hoard2":
		dialog.text = "Confío en un honorable " + GetSexPhrase("hombre", "mujer") + ". ¡La gente como tú siempre cumple su palabra! No importa si el mundo entero está ardiendo, ¡mantendrás tu palabra! ¿Verdad, capitán?";
		link.l1 = "Cuéntame tu historia o te dejaré ir ahora mismo... por la borda y sin cabeza.";
		link.l1.go = "free_by_hoard4";
		break;

	case "free_by_hoard4":
		dialog.text = "Ja-ja, buen chiste... Ahora escucha. Hay un colega en " + XI_ConvertString("Colony" + NPChar.Hold_GenQuest.City + "Voc") + " llamado " + NPChar.Hold_GenQuest.Name + ", era un tipo realmente imprudente en su juventud. Tenía muchos 'tratos' en aquellos días..." + " Una vez en la taberna me contó que era miembro de " + GetName(NAMETYPE_VIP, NPChar.Hold_GenQuest.PirateName, NAME_ACC) + " banda y él vio cómo esos piratas enterraban un tesoro." + " Cinco de sus amigos murieron por ese tesoro... Había rumores de que fue capturado y colgado, pero la verdad es que se retiró del negocio y comenzó una familia. Recordó la ubicación del tesoro, incluso dibujó un mapa. Me ofreció acompañarlo a encontrar el tesoro. Es un hombre supersticioso y el tesoro está cubierto de sangre, así que le teme ir solo allí. Lo admito, tampoco me aventuré por la misma razón. " + "Estaba dispuesto a vender el mapa... ¿Por qué lo necesitaría si nunca voy a ir allí de todos modos...?\nEsa es mi historia... Creo que un hombre tan valiente como tú lo encontrará útil, y el mapa es bastante barato por cierto.";
		link.l1 = "¿Y realmente me sugieres comprar eso? Tu historia no es real, así que rompo nuestro trato.";
		link.l1.go = "free_tip_off_0";
		link.l2 = "Historia interesante, aunque realmente no creo en ella. Pero tienes mi palabra, ve y dile al contramaestre que te dé un casillero. Eres libre.";
		link.l2.go = "free_by_hoard5";
		break;

	case "free_by_hoard5":
		dialog.text = "¡Mis agradecimientos, capitán! Ahora veo el precio de la palabra de uno " + GetSexPhrase("¡caballero!", "¡señora!");
			link.l1 = "Vete y mantente fuera de mi camino. La próxima vez no te dejaré ir tan fácilmente.");
			link.l1.go = "free_by_hoard6";
			break;

	case "free_by_hoard6":
		pchar.GenQuest.Hold_GenQuest.City = NPChar.Hold_GenQuest.City;
		pchar.GenQuest.Hold_GenQuest.Nation = NPChar.Hold_GenQuest.Nation;
		pchar.GenQuest.Hold_GenQuest.Name = NPChar.Hold_GenQuest.Name;
		pchar.GenQuest.Hold_GenQuest.PirateName = NPChar.Hold_GenQuest.PirateName;
		pchar.GenQuest.Hold_GenQuest.CapName = GetFullName(NPChar);
		pchar.GenQuest.Hold_GenQuest.TavernVariant = rand(1) + 2;
		pchar.GenQuest.Hold_GenQuest.Sum = 10000 + rand(10000);
		pchar.GenQuest.Hold_GenQuest.Treasure = rand(1);
		pchar.GenQuest.Hold_GenQuest.Speak_Tavern = false;

		ReOpenQuestHeader("HoldQuest");
		AddQuestRecord("HoldQuest", "12");
		AddQuestUserData("HoldQuest", "sName", GetFullName(NPChar));
		AddQuestUserData("HoldQuest", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Hold_GenQuest.City + "Voc"));
		AddQuestUserData("HoldQuest", "sNameChar", pchar.GenQuest.Hold_GenQuest.Name);
		AddQuestUserData("HoldQuest", "sPirateName", GetName(NAMETYPE_VIP, pchar.GenQuest.Hold_GenQuest.PirateName, NAME_ACC));

		ReleasePrisoner(NPChar); // освободили пленника
		LAi_SetActorType(NPChar);
		NPChar.LifeDay = 0;
		LAi_ActorRunToLocation(NPChar, "reload", "reload1", "none", "", "", "", 4.0);
		DialogExit();
		break;

	case "free_in_sea":
		dialog.text = "Pero, " + GetAddress_Form(NPChar) + ", ¡estamos en alta mar! ¡Es lo mismo que si me ejecutaras!";
		link.l1 = "Eso es lo que querías. Adiós. El contramaestre hará cumplir mi orden.";
		link.l1.go = "PunishmentAction1";
		link.l2 = "Está bien, aún no he decidido.";
		link.l2.go = "exit";
		break;

	//--> Jason, Ложный след
	case "FalseTrace_Prisoner":
		dialog.text = "¡Katerine! ¿Realmente te pidió que vinieras aquí? ¡Qué chica tan maravillosa...";
		link.l1 = "Vamos a alejarnos de la poesía capitán, y hablemos de cosas más serias. Voy a contarte sobre la situación actual y espero una respuesta tuya. Tu respuesta determinará tu destino y el de Katerine.";
		link.l1.go = "FalseTrace_Prisoner_1";
		break;

	case "FalseTrace_Prisoner_1":
		dialog.text = "Estoy escuchando, capitán.";
		link.l1 = "Abordé tu galeón porque Adam Rayner, el esposo de Katerin, me dijo que había mucho plata en tu barco. Este truco le permitió llevarse a una mujer que una vez le perteneció, y que escapó de él hacia ti.";
		link.l1.go = "FalseTrace_Prisoner_2";
		break;

	case "FalseTrace_Prisoner_2":
		dialog.text = "¿Adam? ¿Ese bastardo? ¡Todo era su plan! Ahora veo... Sí, ayudé a Katrine a escapar hace tres meses. Una pobre chica, no tienes idea de cómo la trataba...";
		link.l1 = "Ella era su esposa y no me importaba lo que sucediera, no es asunto mío. Cometí un error al abordar tu galeón pero ya es demasiado tarde para hablar de ello. Adam me ha prometido pagar por mi ayuda.";
		link.l1.go = "FalseTrace_Prisoner_3";
		break;

	case "FalseTrace_Prisoner_3":
		dialog.text = "¿Adam hizo una promesa? ¡Ja-ja! ¿Y tú le has creído? Capitán, ¿siquiera sabes qué tipo de persona es él? Él...";
		link.l1 = "Katerine ya me ha contado mucho sobre él y ha puesto un gran esfuerzo en ello. Pero su propuesta tiene sentido y aunque no tengo ninguna razón para confiar en este bastardo, tal vez esta vez esté diciendo la verdad. Así que vayamos directo al grano...";
		link.l1.go = "FalseTrace_Prisoner_4";
		break;

	case "FalseTrace_Prisoner_4":
		dialog.text = "";
		link.l1 = "Iba a pedirte rescate a las autoridades y a entregar a Adam con Katerine a " + XI_ConvertString("Colony" + pchar.questTemp.FalseTrace.QuestCity + "Acc") + ", luego obtén de Adam la información sobre el oro de Solly el Bizco y navega hacia él. Pero Katerine me ha convencido de hablar contigo primero, ella dijo que podrías ofrecerme algo mejor y más seguro que lo que Adam ofreció, a cambio de vuestras vidas y libertad.";
		link.l1.go = "FalseTrace_Prisoner_5";
		break;

	case "FalseTrace_Prisoner_5":
		dialog.text = "";
		link.l1 = "Por eso estoy aquí parado y hablando contigo. He terminado. Ahora es tu turno. Piensa en mis palabras y en las de Katerine, y dame tus ideas. No tienes mucho tiempo.";
		link.l1.go = "FalseTrace_Prisoner_6";
		break;

	case "FalseTrace_Prisoner_6":
		dialog.text = "¡Capitán! Aunque no creo que seas un buen hombre, escuchaste la súplica de una pobre chica y viniste aquí. Eso me muestra que puedes ser honorable y sentir lástima. No necesito tiempo, estoy lista para darte mi proposición.";
		link.l1 = "¿De verdad? ¡Excelente! Bueno entonces, estoy escuchando.";
		link.l1.go = "FalseTrace_Prisoner_7";
		break;

	case "FalseTrace_Prisoner_7":
		dialog.text = "Arrestarás a Adam Rayner y lo pondrás en cadenas. Luego me llevarás a mí y a Katerine a " + XI_ConvertString("Colony" + pchar.questTemp.FalseTrace.TargetCity) + ". No desembarques en la ciudad, después de todo, fuiste tú quien hundió mi galeón, deja a los tres de nosotros en " + XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore + "Gen") + "\nTambién te pediría un arma. Iremos a la ciudad a través de las junglas y me aseguraré de que esa escoria pague no solo por sus crímenes, sino también por los tuyos. Se lo merece\nTienes mi palabra de que tu nombre no saldrá a la luz. A cambio, te daré información verídica sobre un barco con oro del estado enemigo\nNo será un gran desafío para ti, pero sí tiene dientes, obtendrás un buen botín. Mucho mejor que mi rescate y los tesoros del 'llamado' Solly Bizco. ¿Tenemos un trato?";
		link.l1 = "No me gusta tu plan. Creo que las autoridades locales organizarán una cacería para mí tan pronto como deje las costas de " + XI_ConvertString(pchar.questTemp.FalseTrace.TargetShore + "Gen") + ". No, capitán, no voy a arriesgar mi cabeza. Nuestra conversación ha terminado.";
		link.l1.go = "FalseTrace_Prisoner_8";
		link.l2 = "Bueno, parece que Katerine tenía razón. Me gusta tu propuesta. Adam Rayner será arrestado. Lo haré inmediatamente. Serás liberado después de que arrestemos a Adam. ¡Nos vemos, capitán!";
		link.l2.go = "FalseTrace_Prisoner_9";
		break;

	case "FalseTrace_Prisoner_8":
		DialogExit();
		AddQuestRecord("FalseTrace", "9");
		AddQuestUserData("FalseTrace", "sCity", XI_ConvertString("Colony" + pchar.questTemp.FalseTrace.QuestCity));
		AddDialogExitQuestFunction("SetCheckForSolly");
		bQuestDisableMapEnter = false;
		LAi_CharacterDisableDialog(npchar);
		DeleteAttribute(pchar, "GenQuest.DontSetCabinOfficer");
		break;

	case "FalseTrace_Prisoner_9":
		DialogExit();
		AddQuestRecord("FalseTrace", "10");
		pchar.quest.FalseTraceSollyOver.over = "yes"; // снять таймер
		AddDialogExitQuestFunction("SetCheckForGoldShip");
		LAi_CharacterDisableDialog(npchar);
		pchar.questTemp.FalseTrace.PrisonerID = npchar.id;
		Pchar.questTemp.FalseTrace.PrisonerIDX = GetCharacterIndex(npchar.id);
		break;
	//<-- Ложный след

	// Addon-2016 Jason ФМК-Гваделупа
	case "FMQG":
		dialog.text = "¿Estás aquí para predicar o para hacer negocios?";
		link.l1 = "Para hacer negocios. Necesito a tu compañero en el crimen, Bertrand Pinette. Estoy en un lío profundo por culpa de él. ¿Dónde puedo encontrarlo, eh?";
		link.l1.go = "FMQG_1";
		break;

	case "FMQG_1":
		dialog.text = "¿Por qué crees que te diré esto?";
		link.l1 = "Es tu trasero en la línea. Te llevaré a Basse-Terre, te entregaré al gobernador y recibiré una recompensa por capturar a un desertor que organizó la fuga de Carlos de Milyar. Es tu decisión. O me cuentas sobre la ubicación de Pinette o ambos nos dirigimos a Guadalupe.";
		link.l1.go = "FMQG_2";
		break;

	case "FMQG_2":
		dialog.text = "Entonces lo sabes todo... Bien, te contaré todo lo que sé sobre Bertrand Pinette, pero a cambio me liberarás.";
		link.l1 = "Vamos, cuéntame entonces. Te dejaré en la bahía del Mosquito, igual que la última vez. Pero si me mientes, volveré y prenderé fuego a la plantación que don Carlos te regaló, también informaré a Basse-Terre de tu paradero, así que no seré el único que te caza.";
		link.l1.go = "FMQG_3";
		break;

	case "FMQG_3":
		dialog.text = "Primero, déjame allí. Eso me hará sentir más seguro y juro que te contaré todo.";
		link.l1 = "Bien. No es como si fueras a ir a alguna parte.";
		link.l1.go = "FMQG_4";
		break;

	case "FMQG_4":
		DialogExit();
		AddQuestRecord("FMQ_Guadeloupe", "16");
		LAi_CharacterDisableDialog(npchar);
		pchar.questTemp.FMQG.PrisonerID = npchar.id;
		Pchar.questTemp.FMQG.PrisonerIDX = GetCharacterIndex(npchar.id);
		pchar.quest.FMQG_SailMoskitos.win_condition.l1 = "location";
		pchar.quest.FMQG_SailMoskitos.win_condition.l1.location = "Shore47";
		pchar.quest.FMQG_SailMoskitos.function = "FMQG_ArriveMoskitos";
		pchar.questTemp.FMQG = "to_moskitos";
		AddMapQuestMarkShore("Shore47", true);
		bDisableMapEnter = false; // Rebbebion, теперь можно
		break;

	case "Exit":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		break;
	}
}
