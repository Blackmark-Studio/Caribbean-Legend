#define DIPLOMAT_SUM 80000

void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	int iSumm = 0;
	string s1;

	if (!CheckAttribute(npchar, "PatentPrice"))
	{
		npchar.PatentPrice = (8000 + rand(6) * 1000);
	}
	int i;
	string attrLoc;
	ref sld;

	attrLoc = Dialog.CurrentNode;

	if (findsubstr(attrLoc, "SetNationPatent_", 0) != -1)
	{
		i = findsubstr(attrLoc, "_", 0);
		NPChar.nation = strcut(attrLoc, i + 1, strlen(attrLoc) - 1); // индех в конце
		Dialog.CurrentNode = "patent_2";
	}

	if (findsubstr(attrLoc, "SetNationLicence_", 0) != -1)
	{
		i = findsubstr(attrLoc, "_", 0);
		NPChar.LicenceNation = strcut(attrLoc, i + 1, strlen(attrLoc) - 1); // индех в конце
		Dialog.CurrentNode = "NationLicenceType";
	}

	if (findsubstr(attrLoc, "NationLicenceType_", 0) != -1)
	{
		i = findsubstr(attrLoc, "_", 0);
		NPChar.LicenceType = strcut(attrLoc, i + 1, strlen(attrLoc) - 1); // индех в конце
		Dialog.CurrentNode = "NationLicenceType2";
	}

	if (findsubstr(attrLoc, "RelationTo_", 0) != -1)
	{
		i = findsubstr(attrLoc, "_", 0);
		npchar.quest.relation = strcut(attrLoc, i + 1, strlen(attrLoc) - 1); // индех в конце
		// проверка на уже договор
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		if (CheckAttribute(Pchar, "GenQuest." + attrLoc) && sti(Pchar.GenQuest.(attrLoc)) == true)
		{
			Dialog.CurrentNode = "RelationYet";
		}
		else
		{
			Dialog.CurrentNode = "RelationAny_Done";
			npchar.quest.relation.summ = CalculateRelationSum(sti(npchar.quest.relation));
		}
	}

	if (findsubstr(attrLoc, "CityPay_", 0) != -1)
	{
		i = findsubstr(attrLoc, "_", 0);
		NPChar.quest.CityIdx = strcut(attrLoc, i + 1, strlen(attrLoc) - 1); // индех в конце
		Dialog.CurrentNode = "CityInfo";
	}

	switch (Dialog.CurrentNode)
	{
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "First time":
		dialog.text = "Me alegra verte de nuevo.";
		link.l1 = "Necesito tus servicios de nuevo.";
		link.l1.go = "relation";
		link.l2 = "Debería irme.";
		link.l2.go = "exit";

		// генератор  "Найденные документы"
		if ((pchar.questTemp.different == "GiveShipLetters") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakAgent"))
		{
			link.l4 = "Quiero ofrecerte un trato." link.l4.go = "D_CartasDeBarco_1";
			pchar.questTemp.different.GiveShipLetters.speakAgent = true;
		}

		if (npchar.quest.meeting == "0")
		{
			dialog.text = "Permíteme presentarme. Soy el hombre que puede hablar bien de ti con cualquier gobernador aquí. No es gratis, por supuesto, pero confía en que mis servicios valen su precio. No te arrepentirás de pagar por mis talentos.";
			link.l1 = "Interesante. Continúa.";
			link.l1.go = "relation";
			link.l2 = "Quizás la próxima vez.";
			link.l2.go = "exit";
			npchar.quest.meeting = "1";
		}

		NextDiag.TempNode = "First time";
		break;

	//*************************** Генератор - "You've found shipping papers." **************
	case "D_ShipLetters_1":
		dialog.text = "¿Cuáles son tus términos?";
		s1 = "Por una afortunada casualidad, he encontrado un paquete legítimo de los documentos del barco. ¿Alguien los está buscando?";
		s1 = s1 + "El buque sigue navegando y en el registro, así que no se preocupe. Ese estúpido propietario acaba de perderlo";
		link.l1 = s1;
		link.l1.go = "D_ShipLetters_2";
		break;
	case "D_ShipLetters_2":
		s1 = "¡Déjame verlo! Sí, las marcas son reales. ¡Eres un afortunado " + GetSexPhrase("hombre", "mujer") + "! ";
		s1 = s1 + "Solo necesito un paquete como este y puedo ofrecerte " + sti(pchar.questTemp.different.GiveShipLetters.price5) + " pesos. ¿Qué me dices?";
		dialog.text = s1;
		link.l1 = "¡Tal generosidad real! ¡Por supuesto que acepto!";
		link.l1.go = "D_ShipLetters_3";
		link.l2 = "No, no hay trato.";
		link.l2.go = "exit";
		break;
	case "D_ShipLetters_3":
		TakeItemFromCharacter(pchar, "CaptainBook");
		addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price5));
		OfficersReaction("bad");
		pchar.questTemp.different = "free";
		pchar.quest.GiveShipLetters_null.over = "yes"; // снимаем таймер
		AddQuestRecord("GiveShipLetters", "9");
		CloseQuestHeader("GiveShipLetters");
		DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "relation":
		dialog.text = "Veamos cómo puedo ayudarte.";
		if (ChangeCharacterNationReputation(pchar, ENGLAND, 0) < 0)
		{
			link.l3 = "Quiero reconciliarme con Inglaterra.";
			link.l3.go = "RelationTo_0";
		}

		if (ChangeCharacterNationReputation(pchar, FRANCE, 0) < 0)
		{
			link.l1 = "Quiero reconciliarme con Francia.";
			link.l1.go = "RelationTo_1";
		}
		if (ChangeCharacterNationReputation(pchar, SPAIN, 0) < 0)
		{
			link.l2 = "Quiero reconciliarme con España.";
			link.l2.go = "RelationTo_2";
		}

		if (ChangeCharacterNationReputation(pchar, HOLLAND, 0) < 0)
		{
			link.l4 = "Quiero reconciliarme con Holanda.";
			link.l4.go = "RelationTo_3";
		}
		if (ChangeContrabandRelation(pchar, 0) <= 5)
		{
			Link.l5 = "Quiero reconciliarme con los contrabandistas.";
			Link.l5.go = "Contraband";
		}
		Link.l8 = "Necesito una patente de corso.";
		Link.l8.go = "patent_0";

		Link.l9 = "¿Tienes alguna licencia de comercio?";
		Link.l9.go = "Licence";

		if (isHeroOwnCity(true))
		{
			Link.l10 = "Tengo una pregunta sobre la propiedad de las colonias.";
			Link.l10.go = "City_Buy";
		}

		link.l99 = "Sabes, creo que sería mejor si me encargo de esto por mi cuenta.";
		link.l99.go = "exit";
		break;

	case "Licence":
		dialog.text = "Siempre los tengo y de diferentes períodos. ¿Licencia de qué país quieres?";
		link.l1 = "De Inglaterra";
		link.l1.go = "SetNationLicence_0";
		link.l2 = "De Francia";
		link.l2.go = "SetNationLicence_1";
		link.l3 = "De España";
		link.l3.go = "SetNationLicence_2";
		link.l4 = "De Holanda";
		link.l4.go = "SetNationLicence_3";
		link.l9 = "Sabes, sería mejor que me ocupara de esto por mí mismo.";
		link.l9.go = "exit";
		break;

	case "NationLicenceType":
		dialog.text = "¿Periodo?";
		link.l1 = "30 días";
		link.l1.go = "NationLicenceType_30";
		link.l2 = "60 días";
		link.l2.go = "NationLicenceType_60";
		link.l3 = "90 días";
		link.l3.go = "NationLicenceType_90";
		link.l9 = "He cambiado de opinión.";
		link.l9.go = "exit";
		break;

	case "NationLicenceType2":
		iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE * 500);
		dialog.text = "Entonces, la licencia de comercio de" + XI_ConvertString(Nations[sti(npchar.LicenceNation)].Name + "Gen") + " para " + sti(npchar.LicenceType) + " días, el precio es " + FindRussianMoneyString(iSumm) + ".";
		link.l1 = "Estoy de acuerdo.";
		if (makeint(Pchar.money) < iSumm)
		{
			Link.l1.go = "No_money";
		}
		else
		{
			link.l1.go = "NationLicenceType3";
		}
		link.l9 = "He cambiado de opinión.";
		link.l9.go = "exit";
		break;

	case "NationLicenceType3":
		iSumm = sti(npchar.LicenceType) * (3000 + MOD_SKILL_ENEMY_RATE * 500);
		dialog.text = "Aquí está. No olvides izar una bandera amigable al entrar a un puerto. Y recuerda que la patrulla puede verificar la fecha de la licencia.";
		link.l9 = "Mi agradecimiento.";
		link.l9.go = "exit";
		AddMoneyToCharacter(pchar, -iSumm);
		GiveNationLicence(sti(npchar.LicenceNation), sti(npchar.LicenceType));
		break;

	case "No_money":
		dialog.text = "¡Excelentísimo! Regresa cuando tengas suficiente dinero.";
		link.l1 = "Bien.";
		link.l1.go = "exit";
		break;

	case "patent_0":
		dialog.text = "Espléndido. Primero que nada tienes que demostrar tu lealtad a la nación" + " por una excelente porción para ello. Ve a cualquier gobernador de" + // NationNameGenitive(sti(NPChar.nation))+" y completa algunas de sus misiones. Entonces él te otorgará una licencia.";
					  link.l1 = "Dime, " + GetAddress_FormToNPC(NPChar) + ", ¿puedo evitar esta aburrida formalidad?";
		link.l1.go = "patent_1";
		link.l2 = "Adiós, " + GetAddress_FormToNPC(NPChar);
		link.l2.go = "exit";
		break;

	case "patent_1":
		dialog.text = "¿Te refieres a un soborno!? ¿Quieres que te haga una licencia yo mismo?";
		link.l1 = "¡Exactamente!";
		if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) > rand(11) || bBettaTestMode)
		{
			link.l1.go = "patent_2_give";
		}
		else
		{
			link.l1.go = "patent_2_none";
		}
		link.l2 = "No. Adiós, " + GetAddress_FormToNPC(NPChar);
		link.l2.go = "exit";
		break;

	case "patent_2_none":
		dialog.text = "No tengo ese tipo de relaciones para hacer esto. Y no puedo conseguirte un permiso en blanco con todos los sellos y signos.";
		link.l1 = "Qué lástima. Adiós." + GetAddress_FormToNPC(NPChar);
		link.l1.go = "exit";
		break;

	case "patent_2_give":
		dialog.text = "Está bien, puedo organizar eso para ti. ¿Qué tipo de licencia necesitas?";
		if (GetPatentNation() != ENGLAND)
		{
			link.l1 = "De Inglaterra";
			link.l1.go = "SetNationPatent_0";
		}
		if (GetPatentNation() != FRANCE)
		{
			link.l2 = "De Francia";
			link.l2.go = "SetNationPatent_1";
		}
		if (GetPatentNation() != SPAIN)
		{
			link.l3 = "De España";
			link.l3.go = "SetNationPatent_2";
		}
		if (GetPatentNation() != HOLLAND)
		{
			link.l4 = "De Holanda";
			link.l4.go = "SetNationPatent_3";
		}
		link.l9 = "Sabes que sería mejor que lo resolviera yo mismo.";
		link.l9.go = "exit";
		break;

	case "patent_2":
		// pchar.PatentPrice = 8000 + (sti(NPChar.PatentPrice) * sti(pchar.rank));
		pchar.PatentPrice = 350000 - GetSummonSkillFromName(pchar, SKILL_LEADERSHIP) * 100 + (5000 + rand(1000)) * sti(pchar.rank) * MOD_SKILL_ENEMY_RATE;
		switch (sti(NPChar.nation))
		{
		case PIRATE:
			dialog.text = "Esto es un error, si lo ves, entonces contacta a ALexusB";
			link.l1 = "Parece bien para mí. ¡Acepto tus términos!";
			break;
		case HOLLAND:
			dialog.text = "Holanda es casi una nación pacífica. Conseguirás muchos amigos y pocos enemigos. Y la licencia te costará " + pchar.PatentPrice + " pesos.";
			link.l1 = "Me parece bien. ¡Acepto tus condiciones!";
			break;
		case FRANCE:
			dialog.text = "Los amigos y enemigos de Francia serán los tuyos. Se te permitirá hundir los barcos de sus enemigos. Y la licencia misma te costará " + pchar.PatentPrice + " pesos.";
			link.l1 = "¡Suena bien! ¡Realmente no me importa a quién debería servir! Francia estará bien.";
			break;
		case SPAIN:
			dialog.text = "España tiene muchos enemigos y también serán los tuyos! España es una nación de guerreros del mar. Y la licencia misma te costará " + pchar.PatentPrice + " pesos.";
			link.l1 = "¡Eso es lo que quería! ¡Toma esta patética suma de monedas por peleas y misiones para gente de alto rango!";
			break;
		case ENGLAND:
			dialog.text = "Para ser honesto, así es como el gobernador general inglés llena su bolsillo. Y la licencia misma te costará " + pchar.PatentPrice + " pesos.";
			link.l1 = "Muy bien. Dale mi dinero de sangre que conseguí a través del contrabando y los abordajes!";
			break;
		}

		if (makeint(Pchar.money) < makeint(pchar.PatentPrice))
		{
			Link.l1.go = "No_money";
		}
		else
		{
			link.l1.go = "patent_3";
		}

		link.l2 = "No, eso no es para mí.";
		link.l2.go = "exit";
		break;

	case "patent_3":
		pchar.PatentNation = NationShortName(sti(NPChar.nation));
		dialog.text = "Me alegra que hayamos hecho un trato.";
		link.l1 = "Adiós, " + GetAddress_FormToNPC(NPChar);
		link.l1.go = "exit";
		AddDialogExitQuest("any_patent_take");
		break;

	case "Contraband":
		Pchar.questTemp.Relations.sum = makeint(0.3 * stf(Pchar.rank) / stf(Pchar.reputation.nobility) * DIPLOMAT_SUM);
		dialog.Text = "Bien. Te costará " + Pchar.questTemp.Relations.sum + " pesos.";
		Link.l1 = "Estoy de acuerdo.";
		if (makeint(Pchar.money) < makeint(Pchar.questTemp.Relations.sum))
		{
			Link.l1.go = "No_money";
		}
		else
		{
			Link.l1.go = "Contraband_Agreed";
		}
		Link.l2 = "He cambiado de opinión.";
		Link.l2.go = "exit";
		break;

	case "Contraband_Agreed":
		dialog.Text = "Muy excelente, resolveré todo. Trabajarán contigo.";
		Link.l99 = "Gracias.";
		Link.l99.go = "exit";
		ChangeContrabandRelation(pchar, GetIntByCondition(HasShipTrait(pchar, "trait23"), 25, 40));
		AddMoneyToCharacter(pchar, -sti(Pchar.questTemp.Relations.sum));
		break;
	// boal <--
	case "RelationAny_Done":
		iSumm = sti(npchar.quest.relation.summ);
		dialog.text = "Hm... Ni siquiera sé qué decir. Claro que puedo cumplir tu petición de hacer las paces con " + XI_ConvertString(Nations[sti(npchar.quest.relation)].Name + "Álzate") + ", te costará " + FindRussianMoneyString(iSumm) + ".";
		if (sti(pchar.money) >= iSumm)
		{
			link.l1 = "No creo que tenga opción. Toma mi dinero.";
			link.l1.go = "relation3";
		}
		link.l2 = "No, es demasiado. Adiós.";
		link.l2.go = "exit";
		break;

	case "relation3":
		dialog.text = "¡Espléndido! Sorprendentemente, es fácil tratar contigo. No te preocupes, resolveré tu problema en 15 días.";
		link.l1 = "Bien.";
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, -sti(npchar.quest.relation.summ));
		ChangeNationRelationFromRelationAgent(npchar);
		attrLoc = "RelationAgent" + GetNationNameByType(sti(npchar.quest.relation));
		Pchar.GenQuest.(attrLoc) = true;
		break;

	case "RelationYet":
		dialog.Text = "Tu problema está a punto de resolverse ahora. Solo siéntate y espera, no puede ir más rápido.";
		Link.l99 = "Gracias.";
		Link.l99.go = "exit";
		break;

	case "City_Buy":
		dialog.Text = "¿De qué colonia quieres discutir la propiedad?";
		for (i = 0; i < MAX_COLONIES; i++)
		{
			if (sti(colonies[i].HeroOwn) == true && sti(colonies[i].isBought) == false)
			{
				sld = GetFortCommander(colonies[i].id);
				attrLoc = "l" + i;
				Link.(attrLoc) = GetCityName(colonies[i].id) + ", " + XI_ConvertString(GetNationNameByType(sti(sld.Default.nation)));
				Link.(attrLoc).go = "CityPay_" + i;
			}
		}
		Link.l99 = "No. Nada.";
		Link.l99.go = "exit";
		break;

	case "CityInfo":
		i = sti(NPChar.quest.CityIdx);
		sld = GetFortCommander(colonies[i].id);
		iSumm = TWN_CityCost(colonies[i].id);
		dialog.Text = "Colonia " + GetCityName(colonies[i].id) + ", ha pertenecido a " + XI_ConvertString(GetNationNameByType(sti(sld.Default.nation)) + "Gen") + ", el rescate para detener los intentos de recaptura es " + FindRussianMoneyString(iSumm) + ".";
		if (sti(pchar.money) >= iSumm)
		{
			Link.l1 = "Sí, exactamente lo que necesito.";
			Link.l1.go = "City_Buy_End";
		}
		Link.l99 = "No gracias. No estoy interesado.";
		Link.l99.go = "exit";
		break;

	case "City_Buy_End":
		i = sti(NPChar.quest.CityIdx);
		TWN_RealeseForMoney(colonies[i].id, true);
		dialog.Text = "Está bien, el trato está en proceso. No habrá intentos de captura " + GetCityName(colonies[i].id) + " de nuevo.";
		Link.l2 = "Gracias. Que tengas un buen día.";
		Link.l2.go = "exit";
		Link.l3 = "Una pregunta más.";
		Link.l3.go = "relation";
		break;
	}
}
