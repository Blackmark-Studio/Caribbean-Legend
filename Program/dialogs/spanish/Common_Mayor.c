// boal 25/04/04 общий диалог мэры
#include "DIALOGS\%language%\Rumours\Common_rumours.c" //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref aData;
	aref Link, NextDiag, arName;

	DeleteAttribute(&Dialog, "Links");

	ref FortChref; // фортовый командер
	ref arItem;

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Mayor\" + NPChar.City + "_Mayor.c ";
						 if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag); // homo 25/06/06

	FortChref = GetFortCommander(NPChar.City); // будет или фортовик или сам губернатор

	ref offref;
	int i, cn, iRank, iDay;
	int qty;
	string attrLoc, QuestName, sTemp;
	bool bOk, bOk1, bOk2;

	if (CheckNPCQuestDate(npchar, "Card_date"))
	{
		SetNPCQuestDate(npchar, "Card_date");
		npchar.money = 5000 + (rand(10) + 1) * makeint(100 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
	}
	// генератор ИДХ по кейсу -->
	attrLoc = Dialog.CurrentNode;
	if (findsubstr(attrLoc, "GetPrisonerIdx_", 0) != -1)
	{
		i = findsubstr(attrLoc, "_", 0);
		pchar.GenQuest.GetPrisonerIdx = strcut(attrLoc, i + 1, strlen(attrLoc) - 1); // индех в конце
		Dialog.CurrentNode = "sell_prisoner_2";
	}
	// генератор ИДХ по кейсу <--

	switch (Dialog.CurrentNode)
	{
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOff");
		break;

	case "fight":
		Pchar.quest.ArestInResidenceEnd.win_condition.l1 = "ExitFromLocation";
		Pchar.quest.ArestInResidenceEnd.win_condition.l1.location = Pchar.location;
		Pchar.quest.ArestInResidenceEnd.win_condition = "ArestInResidenceEnd";
		Pchar.quest.ArestInResidenceEnd.ResidenceLocation = Pchar.location;
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;

		LAi_LockFightMode(Pchar, true); // ножками путь убегает
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		LAi_group_Attack(NPChar, Pchar);							   // не работает на бессмертного мера :(
		i = GetCharIDXByParam("CityType", "location", Pchar.location); // фантом солдат
		if (i != -1)
		{
			LAi_group_Attack(&Characters[i], Pchar);
		}
		break;

	case "First time":
		NextDiag.TempNode = "First time";
		if (LAi_grp_playeralarm > 0)
		{
			dialog.text = NPCharRepPhrase(pchar, LinkRandPhrase("¿Te atreviste a mostrar tu cara en mi hogar? ¡Muy valiente de tu parte, o quizás insensato...!", "¿Cómo permitieron mis idiotas guardias que un enemigo entrara en mi palacio? Exigiré la cabeza de alguien por esto.", "Al parecer, mis guardias no valen ni un penique de cobre, si algún sinvergüenza anda por mi residencia y hurga entre mis cosas..."), LinkRandPhrase("¿Qué necesitas, " + GetSexPhrase("diablo", "canalla") + "? ¡Mis soldados ya están tras tu pista" + GetSexPhrase(", sucio pirata", ", sucia pirata") + "!", +"¡Asesino, sal de mi residencia de inmediato! ¡Guardias!", "No te tengo miedo, " + GetSexPhrase("canalla", "rata") + ". ¡Pronto serás ahorcado en nuestro fuerte!"));
			link.l1 = NPCharRepPhrase(pchar, RandPhraseSimple("Vuestros soldados no valen nada.", "Intenta atraparme."), RandPhraseSimple("Cierra la boca, " + GetWorkTypeOfMan(npchar, "") + ", o lo cerraré por ti!", "Estate quieto, camarada, y seguirás con vida."));
			link.l1.go = "fight";
			break;
		}
		if (sti(NPChar.nation) == PIRATE)
		{
			if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar, "GenQuest.CaptainComission.PiratesCity") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
			{
				dialog.text = "¿Qué necesitas?";
				link.l1 = "Quería hablar con usted sobre un trabajo importante.";
				link.l1.go = "quests";
				break;
			}
			if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && NPChar.city == "LeFransua")
			{
				dialog.text = "¿Qué necesitas?";
				link.l1 = "Quería hablar con usted sobre un trabajo importante.";
				link.l1.go = "quests";
				break;
			}
			dialog.text = "No hay nada de qué hablar, señor. Estoy ocupado.";
			link.l1 = "Mis disculpas.";
			link.l1.go = "Exit";
		}
		if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 10)
		{
			iTotalTemp = ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0);
			dialog.text = "¡Oh, mira quién está ahí! Es" + GetSexPhrase("", "") + " " + GetFullName(pchar) + ". Sabes, hace poco envié cazadores de piratas para traerte de vuelta aquí. Si hubiera sabido que vendrías a mi puerta, me habría ahorrado el dinero.";
			if (sti(pchar.Money) >= iTotalTemp * 6000)
			{
				link.l1 = "Estaba a punto de saldar nuestras cuentas.";
				link.l1.go = "arestFree_1";
			}
			link.l2 = "Es hora de que me retire rápidamente.";
			link.l2.go = "arest_1";
			break;
		}
		if (GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY && sti(NPChar.nation) != PIRATE)
		{
			dialog.text = "¡Un robo! ¡Guardias! ¡Alarma! ¡Asesinato!";
			link.l1 = "¡Mierda!";
			link.l1.go = "fight";
			break;
		}
		//--> Jason, Бремя гасконца
		if (CheckAttribute(pchar, "questTemp.Sharlie.Citcount") && npchar.city == "FortFrance")
		{
			dialog.text = "¿Qué es lo que quieres, monsieur?";
			link.l1 = "Hola, Su Gracia. Soy Charles de Maure, recién llegado de París. Estoy buscando a Michel de Monper.";
			link.l1.go = "Sharlie";
			npchar.quest.meeting = "1"; // patch-6
			DelLandQuestMark(characterFromId("FortFrance_Mayor"));
			break;
		}

		if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && npchar.city == "FortFrance")
		{
			if (CheckAttribute(pchar, "questTemp.Sharlie.Pardon"))
			{
				dialog.text = "Ah, es usted, señor... Debo disculparme por mi descortesía. Mis disculpas, estamos lejos de las cortesías de París aquí en las colonias.";
				link.l1 = "Por supuesto, Su Gracia.";
				link.l1.go = "Sharlie_2";
			}
			else
			{
				dialog.text = "¿Querías algo, Charles?";
				link.l1 = "Tengo una pregunta...";
				link.l1.go = "quests";
				link.l2 = "No, nada.";
				link.l2.go = "exit";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
			{
				link.l3 = "Monsieur, he encontrado el cadáver de un bandido en la jungla. Ha sido asesinado por los indios. Había pendientes en su cuerpo, parece que fueron traídos aquí desde Europa. ¿Quizás pertenecían a uno de los nobles de su ciudad?";
				link.l3.go = "Sharlie_junglejew";
			}
			npchar.quest.meeting = "1"; // patch-6
			break;
		}
		//<-- Бремя гасконца
		//--> Sinistra, Травля крысы
		if (CheckAttribute(pchar, "questTemp.TK_TravlyaKrys") && npchar.city == "FortFrance")
		{
			dialog.text = "Bienvenido al Caribe, Capitán de Maure. Esta vez, de verdad.";
			link.l1 = "Gracias, Su Excelencia.";
			link.l1.go = "TK_TravlyaKrys";
			DelLandQuestMark(npchar);
			break;
		}
		// Jason НСО
		// belamour legendary edition фикс проверки мундира с мушкетом
		if (CheckAttribute(pchar, "questTemp.Patria.Governor") && npchar.city == "Marigo" && IsUniformEquip())
		{
			dialog.text = "¡Es bueno verte, Gobernador! ¿Cómo estáis? Todo está bajo control en Sint Maarten.";
			link.l1 = "No tengo tiempo para quedarme. Sigue con el buen trabajo.";
			link.l1.go = "exit";
			link.l2 = "Quería hablar sobre trabajo.";
			link.l2.go = "quests"; //(перессылка в файл города)
			link.l8 = "¿Qué tal un juego de azar?";
			link.l8.go = "Play_Game";
			break;
		}
		// belamour legendary edition фикс проверки мундира с мушкетом
		if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && npchar.nation == FRANCE && IsUniformEquip())
		{
			dialog.text = "¡Dios mío, me alegra verte, Gobernador General! ¡Todo está de maravilla aquí en nuestra humilde y pequeña colonia! Por favor, toma asiento, ordenaré a los sirvientes que preparen la mesa...";
			link.l1 = "No hay necesidad. No vine para quedarme mucho tiempo. Sigue con el buen trabajo.";
			link.l1.go = "exit";
			link.l2 = "Quería hablar sobre el trabajo.";
			link.l2.go = "quests"; //(перессылка в файл города)
			link.l8 = "¿Qué tal un juego de azar?";
			link.l8.go = "Play_Game";
			break;
		}
		// belamour legendary edition фикс проверки мундира с мушкетом
		if (CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && IsUniformEquip())
		{
			dialog.text = "¡A quién tenemos aquí! ¡Monsieur Gobernador General de las Colonias Francesas! ¿Qué desea, su Gracia? Siéntese, ordenaré a mis sirvientes que traigan vino y fruta fresca.";
			link.l1 = "No te preocupes, solo vine aquí porque estaba visitando la isla, y no podía pasar sin saludar.";
			link.l1.go = "exit";
			link.l2 = "Quería hablar sobre trabajo.";
			link.l2.go = "quests"; //(перессылка в файл города)
			link.l8 = "¿Qué tal un juego de azar?";
			link.l8.go = "Play_Game";
			break;
		}
		//--> Jason, Португалец
		if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "MartiniqueGovernor" && npchar.city == "FortFrance")
		{
			dialog.text = "¡Oh, aquí estás, capitán! Debo decir que te tomaste tu tiempo.";
			link.l1 = "He llegado a la primera oportunidad, su Excelencia. ¿Me dijeron que tiene asuntos urgentes?";
			link.l1.go = "Portugal";
			break;
		}
		//<-- Португалец

		if (npchar.quest.meeting == "0")
		{
			dialog.text = "Mis hombres me dijeron que fuiste muy persistente al solicitar una audiencia. Mi nombre es " + GetFullName(npchar) + ". Soy el gobernador del pueblo de " + GetCityName(NPChar.city) + ", súbdito de " + NationKingsName(npchar) + ". Y ahora, por favor, ¿qué es lo que desea? " + GetAddress_Form(NPChar) + "?";
			link.l1 = "Mi nombre es " + GetFullName(pchar) + ".";
			link.l1.go = "node_1";
			npchar.quest.meeting = "1";
			if (startHeroType == 4 && NPChar.location == "SantaCatalina_townhall")
			{
				dialog.text = TimeGreeting() + ", señorita MacArthur.";
				link.l1 = TimeGreeting() + ", Su Excelencia.";
				link.l1.go = "Helen_node_1"
			}
		}
		else
		{
			// ОСАДЫ homo
			if (CheckAttribute(&Colonies[FindColony(npchar.City)], "Siege"))
			{

				makearef(aData, NullCharacter.Siege);

				if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true)
				{
					dialog.text = "¿Eso es todo?";
					link.l1 = "Sí, señor. No le retraso más.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Lamento molestarte, pero no tengo tiempo para hablar contigo en este momento. Como deberías saber, nuestra colonia fue atacada por " + NationNamePeople(sti(aData.nation)) + ". Todavía estoy ocupándome de nuestras defensas.";
					link.l1 = "Quiero ofrecer mi ayuda en la defensa del fuerte.";
					link.l1.go = "siege_task";
					link.l2 = "Entonces no te demoraré más.";
					link.l2.go = "exit";
				}
			}
			else
			{ //->
				makearef(aData, NullCharacter.Siege);
				if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true)
				{
					AddMoneyToCharacter(Pchar, (sti(aData.iSquadronPower) * 1500));
					ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
					ChangeCharacterComplexReputation(pchar, "nobility", 10);
					AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
					AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
					AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
					AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
					//--> слухи
					SiegeRumour("¡Dicen que nos habías ayudado a repeler a los " + NationNameSK(sti(aData.nation)) + " escuadrón y defender nuestra colonia! Les estamos agradecidos, " + GetAddress_Form(NPChar) + ".", aData.Colony, sti(aData.conation), -1, 15, 3);
					//<-- слухи
					DeleteAttribute(aData, "PlayerHelpMayor");
					DeleteAttribute(aData, "HelpColony");
					dialog.text = "Ah, eres tú, " + GetAddress_Form(NPChar) + " " + GetFullName(pchar) + ", me alegra verte. Buenas noticias para nuestra colonia: logramos repeler el " + NationNameSK(sti(aData.nation)) + " invasores. Tú también tienes parte en esto, así que aquí está tu recompensa, " + (sti(aData.iSquadronPower) * 1500) + " piezas de a ocho. Aquí tienes.";
					link.l1 = "Gracias, " + GetAddress_FormToNPC(NPChar) + "¡Es un placer hacer negocios contigo!";
					link.l1.go = "exit";
				}
				else
				{
					//--> дача квеста найти кольцо в борделе
					if (rand(4) == 4 && pchar.questTemp.different == "free" && GetNpcQuestPastDayWOInit(npchar, "questTakeRing") > 365 && sti(pchar.questTemp.HorseQty) > 10)
					{ // Addon-2016 Jason
						if (npchar.city == "Bridgetown" || npchar.city == "Charles" || npchar.city == "FortFrance" || npchar.city == "Marigo" || npchar.city == "Panama" || npchar.city == "PortRoyal" || npchar.city == "SantoDomingo" || npchar.city == "Tortuga")
						{
							dialog.text = "Tengo una tarea para ti, pero es algo inusual.";
							link.l1 = "Esas son las tareas en las que soy el mejor.";
							link.l1.go = "TakeRing_1";
							SaveCurrentNpcQuestDateParam(npchar, "questTakeRing");
							break;
						}
					}
					//<-- дача квеста найти кольцо в борделе
					dialog.text = RandPhraseSimple("¿Oh, eres tú otra vez? ¿Qué es lo que quieres de mí esta vez?", "Me estás distrayendo de los asuntos de mi ciudad. ¿Qué quieres, " + GetAddress_Form(NPChar) + "?");
					if (npchar.city != "Panama") // Addon-2016 Jason
					{
						link.l1 = "Quiero hablar contigo sobre trabajar para " + NationNameGenitive(sti(NPChar.nation)) + ".";
						link.l1.go = "work";
					}
					// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
					if (CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
					{
						link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Gen") + " He encontrado algunos piratas. Todos " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " están a bordo en este momento. Quiero entregarlos a las autoridades.";
						link.l11.go = "PiratesOnUninhabited_1";
					}

					link.l2 = "Iba a hablar contigo sobre un tema importante.";
					if (CheckAttribute(pchar, "questTemp.ReasonToFast") && !CheckAttribute(pchar, "questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
					{
						link.l2.go = "ReasonToFast_Mayor1";
					}
					else
					{
						link.l2.go = "quests"; //(перессылка в файл города)
					}
					if (CheckAttribute(pchar, "GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
					{
						if (pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar, "GenQuest.CaptainComission.SpeakMayor"))
						{
							link.l12 = "Hay un capitán al mando de la patrulla " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")) + " llamado " + pchar.GenQuest.CaptainComission.Name + ", ¿cómo puedo verlo?";
							link.l12.go = "CapComission_Mayor1";
						}
						if (CheckAttribute(pchar, "GenQuest.CaptainComission.PrisonFree"))
						{
							link.l12 = "Antiguo capitán al mando de la patrulla " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + "aceptó revelar su alijo a las autoridades.";
							link.l12.go = "CapComission_Mayor9";
						}
						if (pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
						{
							link.l12 = "Antiguo capitán al mando de la patrulla " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " me reveló su escondite.";
							link.l12.go = "CapComission_Mayor13";
						}
					}
					if (CheckAttribute(pchar, "GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25 && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
					{
						if (!CheckAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor"))
						{
							iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
							if (CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + " Me encontré con el capitán " + pchar.GenQuest.ShipWreck.Name + " y sus marineros que fueron desembarcados por un pirata " + pchar.GenQuest.ShipWreck.BadName + ". " + "Lamentablemente, ya tenía demasiados hombres en mi barco y no pude llevarlos a bordo. Pero les dejé provisiones y armas. Si un barco de rescate no los recoge dentro de " + (30 - iDay) + " días, entonces no sé si los encontraré vivos o no.";
								link.l13.go = "ShipWreck1";
							}
							else
							{
								link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen")) + " Me encontré con marineros del barco naufragado '" + pchar.GenQuest.ShipWreck.ShipTypeName + " con su capitán. " + "Lamentablemente, ya tenía demasiados hombres en mi barco y no pude llevarlos a bordo. Pero les dejé provisiones y armas. Si un barco de rescate no los recoge dentro de " + (30 - iDay) + " días, entonces no sé si los encontrará vivos o no.";
								link.l13.go = "ShipWreck1";
							}
						}
					}
					if (GetPrisonerQty() > 0)
					{
						link.l3 = "Deseo entregar a un prisionero.";
						link.l3.go = "sell_prisoner";
					}
					if (npchar.Default == npchar.location) // если не в тюрьме
					{
						if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
						{
							link.l4 = "Necesito resolver algunos asuntos financieros contigo.";
							link.l4.go = "LoanForAll"; //(перессылка в кредитный генератор)
						}
					}
					//-->> сдача найденного в борделе кольца
					if (CheckCharacterItem(pchar, "MayorsRing"))
					{
						if (pchar.questTemp.different.TakeMayorsRing == "toBrothel")
						{
							link.l5 = "He logrado encontrar tu anillo. Aquí tienes.";
							link.l5.go = "TakeRing_S1";
						}
						else
						{
							link.l5 = "Tengo tu anillo de bodas. Una de las...chicas de trabajo en el burdel lo tenía.";
							link.l5.go = "TakeRing_S3";
						}
					}
					//<<-- сдача найденного в борделе кольца

					//--> Jason, генер почтового курьера 2 уровня
					if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
					{
						if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
						{
							link.l14 = "Llevo un mensaje de la ciudad de " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.StartCity + "Gen") + ".";
							link.l14.go = "Postcureer_LevelUp_ForAll";
						}
					}
					//<-- генер почтового курьера 2 уровня

					// Warship, 16.05.11. Квест "Правосудие на продажу" -->
					if (CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
					{
						link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar)) + ", he localizado una banda de contrabandistas cuyo cabecilla había sido capturado recientemente por los guardias. Ahora están tramando su fuga. Su barco '" + PChar.GenQuest.JusticeOnSale.ShipName + "está amarrado en " + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Dat") + ".";
						link.l15.go = "JusticeOnSale_1";
					}

					if (CheckAttribute(PChar, "GenQuest.JusticeOnSale.ShipSink") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
					{
						link.l15 = UpperFirst(GetAddress_FormToNPC(NPChar)) + ", ¡la banda de contrabandistas ya no existe!";
						link.l15.go = "JusticeOnSale_7";
					}
					// <--Правосудие на продажу
					// Jason --> Регата
					if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
					{
						link.l16 = "Estoy aquí para la regata. Aquí está mi invitación.";
						link.l16.go = "Regata";
					}
					// link.l7 = "Me gustaría saber dónde está el Gobernador General de "+NationNameGenitive(sti(NPChar.nation))+"es.";
					link.l8 = "Quizás, ¿quieres tomarte un descanso jugando un juego de azar?";
					link.l8.go = "Play_Game";
					link.l10 = "Por favor, discúlpeme, pero el deber me llama.";
					link.l10.go = "exit";
				}
			} //<-
		}
		break;

	// Warship Генер "Пираты на необитайке"
	case "PiratesOnUninhabited_1":
		offref = CharacterFromID("PirateOnUninhabited_0");
		qty = makeint(sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) * (sti(offref.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(offref, "Leadership") * 500 + GetCharacterSkillToOld(PChar, "commerce") * 500) / 20);

		PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates = qty;

		dialog.text = "Muy bien. Debemos combatir esta plaga común con nuestros esfuerzos concertados. Enviaré inmediatamente un barco para recogerlos. Ten la seguridad de que estarán colgando en la horca en menos de una semana. Oh, y una recompensa es debida, por supuesto, " + FindRussianMoneyString(qty) + ".";
		link.l1 = "Gracias, Su Excelencia. Siempre es un placer. ";
		link.l1.go = "PiratesOnUninhabited_2";
		link.l2 = "No. Pensándolo bien, eso no servirá.";
		link.l2.go = "exit";
		break;

	case "PiratesOnUninhabited_2":
		offref = CharacterFromID("PirateOnUninhabited_0");

		AddMoneyToCharacter(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.MoneyForPirates));

		RemovePassenger(PChar, offref);
		RemoveCharacterCrew(PChar, sti(PChar.GenQuest.PiratesOnUninhabited.PiratesCount) - 1);

		sTemp = "PiratesOnUninhabited" + PChar.GenQuest.PiratesOnUninhabited.StartShore;
		AddQuestRecordEx(sTemp, "PiratesOnUninhabited", "12");
		AddQuestUserData(sTemp, "sSex", GetSexPhrase("", ""));
		AddQuestUserData(sTemp, "mayorName", GetFullName(NPChar));
		CloseQuestHeader(sTemp);

		PChar.Quest.PiratesOnUninhabited_OnShore.over = "yes";
		PChar.Quest.PiratesOnUninhabited_OnMayak.over = "yes";

		if (CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
		{
			PChar.Quest.PiratesOnUninhabited_ShipSink.over = "yes";

			PChar.GenQuest.PiratesOnUninhabited.ClearShip = true;
			Map_ReleaseQuestEncounter("PiratesOnUninhabited_BadPirate"); // Убираем с глобалки
		}

		DeleteAttribute(PChar, "GenQuest.PiratesOnUninhabited");

		DialogExit();
		break;

	// ------------------------- Повод для спешки -----------------------------
	case "ReasonToFast_Mayor1":
		dialog.text = "Soy todo oídos, capitán.";
		link.l1 = "Quería hablarte sobre una colusión criminal entre un oficial de tu guarnición y piratas... (explica el asunto).";
		if (sti(pchar.reputation.nobility) < 41)
		{
			link.l1.go = "ReasonToFast_BMayor";
		}
		else
		{
			link.l1.go = "ReasonToFast_GMayor";
		}
		pchar.questTemp.ReasonToFast.SpeakOther = true;
		break;

	case "ReasonToFast_GMayor":
		if (pchar.questTemp.ReasonToFast == "PatrolSuccess_1")
		{
			// вилка_А
			dialog.text = "Gracias, " + GetSexPhrase("señor", "señorita") + "¡De inmediato ordenaré arrestar a ese traidor.\nDebes haber gastado mucho dinero, ay, nuestra tesorería está vacía...";
			link.l1 = "No lo hice por el dinero, su Excelencia.";
			link.l1.go = "ReasonToFast_GMayor_11";
			if (pchar.questTemp.ReasonToFast.chain == "A0")
				ReasonToFast_RemoveVictim();
			if (pchar.questTemp.ReasonToFast.chain == "A1")
				pchar.quest.ReasonToFast_ClearLakey.over = "yes";
		}
		if (pchar.questTemp.ReasonToFast == "PatrolSuccess_2")
		{
			// получена карта
			dialog.text = "¡Te lo agradezco! Haré que arresten a ese sinvergüenza.\n¡Imagínate! ¡Estaba a punto de premiarlo con un sable de empuñadura dorada por sus diez años de servicio! ¡Me has salvado de una vergüenza seria!";
			link.l2 = "La justicia es su propia recompensa.";
			link.l2.go = "ReasonToFast_GMayor_21";
		}
		if (pchar.questTemp.ReasonToFast == "PatrolDied")
		{
			// патруль перебит
			dialog.text = "Señor" + GetSexPhrase("", "ita") + ", ¡no puedes simplemente matar a un sospechoso sin testigos! ¡Ahora ni siquiera podemos obtener pruebas de sus crímenes! Lo único que puedo hacer es evitar que te arresten por homicidio involuntario.";
			link.l3 = "¡Alto, fue en defensa propia, Su Excelencia!";
			link.l3.go = "ReasonToFast_GMayor_31";
			pchar.questTemp.ReasonToFast.speakAfterPatrolDied = true;
			pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
		}
		break;

	case "ReasonToFast_BMayor":
		if (pchar.questTemp.ReasonToFast == "PatrolSuccess_1")
		{
			dialog.text = "¡Capitán, ¿te das cuenta de la maldita mierda que has hecho?!! ¡He estado preparando esta trampa durante más de un mes! ¡Y ahora, solo por tu propio entretenimiento, has arruinado la reunión de nuestra patrulla con " + GetName(NAMETYPE_MAIN, pchar.questTemp.ReasonToFast.p3, NAME_GEN) + "¿y ahora vienes aquí a jactarte de ello?!! ¿Quizás puedas decirme ahora, cómo debería justificar todos los gastos y costos de esta operación?!";
			link.l1 = "Su Gracia, acabo de resolver su problema, ¡si lo piensa debería haberme estado pagando todo este tiempo!";
			link.l1.go = "ReasonToFast_BMayor_1";
			pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
			if (pchar.questTemp.ReasonToFast.chain == "A0")
				ReasonToFast_RemoveVictim();
			if (pchar.questTemp.ReasonToFast.chain == "A1")
				pchar.quest.ReasonToFast_ClearLakey.over = "yes";
		}
		if (pchar.questTemp.ReasonToFast == "PatrolSuccess_2")
		{
			// получена карта
			dialog.text = "Déjame ver este mapa\n¿Hablas en serio ahora mismo? ¿Este pedazo de papel raído es una prueba?";
			link.l2 = "Vamos ahora Su Gracia, sea razonable.";
			link.l2.go = "ReasonToFast_BMayor_1";
			TakeItemFromCharacter(pchar, "mapQuest");
			pchar.questTemp.ReasonToFast = "speakSuccess_chain_B";
		}
		if (pchar.questTemp.ReasonToFast == "PatrolDied")
		{
			// патруль перебит
			dialog.text = "Vaya, vaya, ahora sabemos qué le pasó a mi patrulla. Al menos al venir aquí nos ahorraste la necesidad de buscar al asesino.";
			link.l3 = "¡Su Gracia! Simplemente se niega a ver el punto...";
			link.l3.go = "ReasonToFast_BMayor_1";
			pchar.questTemp.ReasonToFast = "speakSuccess_chain_A";
			pchar.quest.ReasonToFast_SpeakMayor.over = "yes";
		}
		break;

	case "ReasonToFast_GMayor_11":
		dialog.text = "Puede que seas un idiota, pero al menos eres un idiota útil. Aquí, toma este mapa; lo encontré en un pirata que colgamos la semana pasada. Si Dios quiere, quizás encuentres su tesoro, aunque lo veo bastante improbable...";
		link.l1 = "¡Gracias, eso es muy generoso de su parte!";
		link.l1.go = "exit";
		AddQuestRecord("ReasonToFast", "15");
		ChangeCharacterComplexReputation(pchar, "nobility", 1);
		GiveItem2Character(pchar, "mapQuest");
		arItem = ItemsFromID("mapQuest");
		ReasonToFast_GenerateTreasureMap(arItem);
		pchar.questTemp.ReasonToFast.state = "chain_A"; // вилка_А, наводки не генерим
		pchar.questTemp.ReasonToFast = "GetMap";
		ReasonToFast_SetHunterCoastal();
		break;

	case "ReasonToFast_GMayor_21":
		dialog.text = "Tu celo es encomiable. Por favor, acepta esta espada como recompensa, es lo mínimo que puedo hacer. Ah, y puedes quedarte con el mapa. Estoy seguro de que hay muchos de estos falsos en el Caribe.";
		link.l1 = "¡Gracias, eso es muy generoso de su parte!";
		link.l1.go = "exit";
		AddQuestRecord("ReasonToFast", "14");
		ChangeCharacterComplexReputation(pchar, "nobility", 1);
		GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
		pchar.questTemp.ReasonToFast.state = "chain_B"; // была получена карта
		pchar.questTemp.ReasonToFast = "GetMap";
		ReasonToFast_SetHunterCoastal();
		break;
	case "ReasonToFast_GMayor_31":
		dialog.text = "Quizás, quizás... Bueno, digamos que este trato fue decidido por la justicia divina y por la voluntad de nuestro Señor.";
		link.l1 = "¡Gracias, eso es muy generoso de su parte!";
		link.l1.go = "exit";
		ChangeCharacterComplexReputation(pchar, "nobility", 1);
		AddQuestRecord("ReasonToFast", "16");
		CloseQuestHeader("ReasonToFast");
		DeleteAttribute(pchar, "ReasonToFast");
		break;

	case "ReasonToFast_BMayor_1":
		dialog.text = "¡Cierra la boca, muchacho! ¡Estás loco o aliado con nuestros enemigos! ¡Guardias, apresad a este idiota!";
		link.l1 = "¡Ponme una mano encima y la perderás!";
		link.l1.go = "fight";

		pchar.quest.ReasonToFast_ExitFromTown.win_condition.l1 = "EnterToSea";
		pchar.quest.ReasonToFast_ExitFromTown.function = "ReasonToFast_ExitFromTownFight";
		pchar.questTemp.ReasonToFast.canSpeakSailor = true;
		pchar.TownEscape = true;
		Flag_PIRATE();
		break;

	// ------------------------- Повод для спешки -----------------------------

	// --------------------------Операция 'Галеон'-----------------------------
	case "CapComission_Mayor1":
		dialog.text = "Ahora mismo eso es imposible. Está bajo arresto esperando juicio.";
		link.l1 = "¿Lo está? ¿Y de qué se le sospecha?";
		link.l1.go = "CapComission_Mayor2";
		break;

	case "CapComission_Mayor2":
		dialog.text = "Lamentablemente, no es sospecha, sino un hecho comprobado. Tenemos información de que estuvo atacando naves bajo el pretexto de patrullar. Confiscó mercancías de los mercaderes y luego las vendió a contrabandistas y piratas. Es una lástima... pensar que alguna vez fue considerado uno de los mejores capitanes que tenía la Corona...";
		link.l1 = "¿Y quién te proporcionó las pruebas?";
		link.l1.go = "CapComission_Mayor3";
		break;

	case "CapComission_Mayor3":
		dialog.text = "Una de sus víctimas escribió un informe, donde describió el incidente en detalle, incluyendo la fecha, el nombre del barco asaltado y las cantidades de bienes confiscados." + "Confía en mí, los números son bastante impresionantes. Ese día la patrulla " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name"))) + " capitán " + pchar.GenQuest.CaptainComission.Name + "estaba efectivamente de servicio. El capitán describió este incidente como un encuentro con un barco pirata en su informe, pero no mencionó ninguna carga en absoluto.";
		link.l1 = "¿Pero había alguna carga en absoluto?";
		link.l1.go = "CapComission_Mayor4";
		pchar.GenQuest.CaptainComission.SpeakMayor = true;
		break;

	case "CapComission_Mayor4":
		dialog.text = "No hay duda al respecto. La parte agraviada es un hombre muy conocido y no se rebajaría con calumnias y difamaciones. En este momento, nuestras patrullas están buscando el alijo del capitán." + "Una vez que se encuentre, el capitán puede presentarse en la corte\nSi nos presta ayuda en este asunto, le estaremos muy agradecidos.";
		link.l1 = "Probablemente no. No conozco bien la zona como para buscar un escondite. Disculpa, tengo que irme.";
		link.l1.go = "CapComission_Mayor5";
		link.l2 = "Tal vez... ¿Cuánto tiempo tengo?";
		link.l2.go = "CapComission_Mayor6";
		break;

	case "CapComission_Mayor5":
		AddQuestRecord("CaptainComission2", "49");
		AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Gen")));
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		ChangeCharacterComplexReputation(pchar, "nobility", -2);
		pchar.GenQuest.CaptainComission = "MayorTalkBad";
		CaptainComission_GenerateCaptainInPrison();
		DialogExit();
		break;

	case "CapComission_Mayor6":
		dialog.text = "Creo que en dos días las patrullas pueden localizar el escondite sin tu ayuda, así que deberías darte prisa.";
		link.l1 = "Ay, estoy en ello. Pero necesitaré hacer una visita al capitán " + pchar.GenQuest.CaptainComission.Name + "¿Se puede arreglar esto?";
		link.l1.go = "CapComission_Mayor7";
		break;

	case "CapComission_Mayor7":
		dialog.text = "Eso no será un problema. Informaré al comandante del fuerte sobre su visita.";
		link.l1 = "Gracias. Ahora, por favor, discúlpeme.";
		link.l1.go = "CapComission_Mayor8";
		break;

	case "CapComission_Mayor8":
		AddQuestRecord("CaptainComission2", "50");
		AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("CaptainComission2", "sSex1", GetSexPhrase("", ""));
		AddQuestUserData("CaptainComission2", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Gen")));
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
		OfficersReaction("good");
		pchar.GenQuest.CaptainComission.MayorTalkGood = true;
		pchar.GenQuest.CaptainComission = "MayorTalkGood";
		pchar.quest.CaptainComission_TimeIsOver.over = "yes";
		SetFunctionTimerConditionParam("CaptainComission_GetSecretTimeIsOut", 0, 0, 2, MakeInt(24 - GetHour()), false);
		CaptainComission_GenerateCaptainInPrison();
		DialogExit();
		break;

	case "CapComission_Mayor9":
		dialog.text = "¡Excelente! ¿Dónde está el tesoro?";
		link.l1 = "No tengo idea todavía. No me indicó la ubicación exacta.";
		link.l1.go = "CapComission_Mayor10";
		break;

	case "CapComission_Mayor10":
		dialog.text = "Vaya, ¡qué coincidencia! Sabes, él tampoco 'me indicó' la ubicación exacta...";
		link.l1 = "Estoy trabajando en ello.";
		link.l1.go = "CapComission_Mayor11";
		break;

	case "CapComission_Mayor11":
		dialog.text = "Ya no más\n¡Guardias! Llevad al prisionero de vuelta a las cámaras\nPuedes irte, " + GetFullName(pchar) + ".";
		link.l1 = "Pero gobernador...";
		link.l1.go = "CapComission_Mayor12";
		break;

	case "CapComission_Mayor12":
		sld = CharacterFromID("CapComission_1");
		sld.lifeDay = 0;
		LAi_group_MoveCharacter(sld, "EnemyFight");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
		pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1 = "ExitFromLocation";
		pchar.quest.CapComission_DeletePrisonGroup.win_condition.l1.location = pchar.location;
		pchar.quest.CapComission_DeletePrisonGroup.win_condition = "CaptainComission_DeletePrisonGroup";
		ChangeOfficersLoyality("bad_all", 1);
		ChangeCharacterComplexReputation(pchar, "nobility", -4);
		AddQuestRecord("CaptainComission2", "23");
		AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("", ""));
		CloseQuestHeader("CaptainComission2");
		DeleteAttribute(pchar, "GenQuest.CaptainComission");
		DialogExit();
		break;

	case "CapComission_Mayor13":
		pchar.quest.CaptainComission_SpeakMayorGoods.over = "yes";
		dialog.text = "¡Excelente! ¿Y dónde vamos a buscar su tesoro?";
		link.l1 = "En el " + RandPhraseSimple(RandPhraseSimple("norteño", "occidental"), RandPhraseSimple("oriental", "del sur")) + " fin de " + XI_ConvertString(pchar.GenQuest.CaptainComission.ConvoyShore + "Gen") + " al pie del acantilado hay un gran nicho, cuya entrada está cubierta de piedras. Ese es el escondite.";
		link.l1.go = "CapComission_Mayor14";
		break;

	case "CapComission_Mayor14":
		dialog.text = "¡Excelente trabajo! ¿Y dónde está " + pchar.GenQuest.CaptainComission.Name + "¿él mismo? Me dijeron que lo sacaste de las mazmorras del fuerte.";
		link.l1 = "Desafortunadamente, pereció en una escaramuza con los contrabandistas.";
		link.l1.go = "CapComission_Mayor15";
		break;

	case "CapComission_Mayor15":
		dialog.text = "Esto es malo... Esto es muy malo, " + GetSexPhrase("señor", "señorita") + " " + GetFullName(pchar) + ". Iba a ejecutarlo en público, 'para alentar a los demás'." + "De todos modos, no habría evitado la horca.\nAsí que, como técnicamente violaste la ley al liberar ilegalmente a un prisionero, pero aún así no lo salvaste, no puedo arreglar esto en el informe. Por lo tanto, no recibirás una recompensa... Pero me gustaría agradecerte personalmente. Acepta mi regalo: una cosa muy útil para un capitán combatiente.";
		link.l1 = "Gracias. Siempre encantado de servir.";
		link.l1.go = "CapComission_Mayor16";
		break;

	case "CapComission_Mayor16":
		AddQuestRecord("CaptainComission2", "30");
		AddQuestUserData("CaptainComission2", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Gen"));
		CloseQuestHeader("CaptainComission2");
		GiveItem2Character(pchar, pchar.GenQuest.CaptainComission.Prize);
		ChangeCharacterComplexReputation(pchar, "nobility", 4);
		ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
		OfficersReaction("good");
		DeleteAttribute(pchar, "GenQuest.CaptainComission.MayorTalkGood");
		DeleteAttribute(pchar, "GenQuest.CaptainComission");
		DialogExit();
		break;
	// --------------------------Операция 'Галеон'-----------------------------

	// -------------------------- Генератор "Кораблекрушенцы" ------------
	case "ShipWreck1":
		if (iDay > 15)
		{
			dialog.text = RandPhraseSimple("¿Cómo lo haces? ¡Se tarda al menos quince días en llegar a ese lugar incluso navegando con el viento!", "Capitán " + GetFullName(pchar) + ", ¡tu irresponsabilidad me asombra! ¿Por qué no me lo habías dicho antes?");
			link.l1 = "Bueno, ni siquiera sé qué decir...";
			link.l1.go = "ShipWreck2";
		}
		else
		{
			dialog.text = "¡Esta es una gran noticia! Ya habíamos perdido la esperanza de ver " + pchar.GenQuest.ShipWreck.Name + " vivo de nuevo. Enviaré un grupo de rescate de inmediato. Oh, y por favor acepte esta recompensa por su eficiencia y participación en su rescate.";
			link.l1 = "Gracias, Su Gracia. Me alegra haber podido ayudar. Estoy seguro de que la expedición llegará a tiempo.";
			link.l1.go = "ShipWreck3";
		}
		pchar.GenQuest.ShipWreck.SpeakMayor = true;
		pchar.quest.ShipWreck_MeetInShore.over = "yes";
		pchar.quest.ShipWreck_SaveSailors.over = "yes"; // belamour gen таймер на 30 дней тоже нужно снять
		break;

	case "ShipWreck2":
		dialog.text = "Vaya... ¿Qué se puede decir? ¡Ve y estudia la Ley del Mar, muchacho! Sea como sea, haré lo mejor que pueda para salvar a estas personas.";
		link.l1 = "Su Gracia, pero les dejé suficientes provisiones. Tienes tiempo, te lo aseguro ...";
		link.l1.go = "ShipWreck4";
		break;

	case "ShipWreck3":
		addMoneyToCharacter(pchar, sti(pchar.rank) * 300 + 3000 + rand(3000));
		ChangeCharacterComplexReputation(pchar, "nobility", 2);
		AddQuestRecord("ShipWrecked", "14");
		AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + NPChar.city + "Gen"));				// belamour gen просто NPChar.city ничего не даст
		AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen")); // belamour gen
		CloseQuestHeader("ShipWrecked");
		DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");
		DialogExit();
		AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;

	case "ShipWreck4":
		ChangeCharacterComplexReputation(pchar, "nobility", -5);
		AddQuestRecord("ShipWrecked", "13");
		AddQuestUserData("ShipWrecked", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("ShipWrecked", "sCity", XI_ConvertString("Colony" + NPChar.city + "Gen"));				// belamour gen просто NPChar.city ничего не даст
		AddQuestUserData("ShipWrecked", "ShoreName", XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Gen")); // belamour gen
		CloseQuestHeader("ShipWrecked");
		DeleteAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor");
		DialogExit();
		AddDialogExitQuest("ShipWreck_RemoveSailorsFromShore");
		break;
	// -------------------------- Генератор "Кораблекрушенцы" ------------

	// ---------------------- найти кольцо в борделе ----------------------------
	case "TakeRing_1":
		dialog.text = "Soy consciente de que tú, cómo decirlo... " + GetSexPhrase("eres un asiduo de los burdeles", "a veces me gusta visitar burdeles") + ". Y por lo tanto decidí dirigirme a usted para pedir ayuda\n" + "Sabes, me da vergüenza admitirlo, pero estuve allí recientemente...";
		link.l1 = "¿Y qué tiene de malo? El sexo es algo perfectamente natural, ¿sabes...?";
		link.l1.go = "TakeRing_2";
		break;
	case "TakeRing_2":
		dialog.text = "Oh, no, no estoy predicando, no. El asunto es que había bebido demasiado en una ocasión y perdí mi anillo de bodas...";
		link.l1 = "Ahora eso es un problema. Lo siento.";
		link.l1.go = "TakeRing_3";
		break;
	case "TakeRing_3":
		dialog.text = "No necesito que nadie sienta lástima por mí. Necesito que me devuelvan mi anillo. Si logras recuperarlo antes de la medianoche, seré muy generoso. Si fallas, mi esposa me matará.";
		link.l1 = "Ya veo... ¿Y dónde exactamente podrías haberlo perdido? ¿Recuerdas algo en particular?";
		link.l1.go = "TakeRing_4";
		break;
	case "TakeRing_4":
		dialog.text = "Desafortunadamente, no. Nada de nada.";
		link.l1 = "Ya veo. Bueno, busquémoslo, entonces.";
		link.l1.go = "TakeRing_5";
		link.l2 = "Sabes, " + GetAddress_FormToNPC(NPChar) + ", creo que pasaré de esta. Por favor, discúlpame...";
		link.l2.go = "TakeRing_6";
		break;
	case "TakeRing_5":
		dialog.text = "¡Excelente! Pero recuerda, debes encontrarlo antes de la medianoche.";
		link.l1 = "Recuerdo. Volveré pronto.";
		link.l1.go = "exit";
		pchar.questTemp.different = "TakeMayorsRing";
		pchar.questTemp.different.TakeMayorsRing = "toBrothel";
		pchar.questTemp.different.TakeMayorsRing.Id = GetFullName(npchar);
		pchar.questTemp.different.TakeMayorsRing.city = npchar.city;
		pchar.questTemp.different.TakeMayorsRing.price = sti(pchar.rank) * 100 + 1000;
		sld = ItemsFromID("MayorsRing");
		sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
		// ложим кольцо в итем
		if (rand(3) != 2)
		{
			switch (rand(2))
			{
			case 0:
				sTemp = "_Brothel_room";
				break;
			case 1:
				sTemp = "_Brothel";
				break;
			case 2:
				sTemp = "_SecBrRoom";
				break;
			}
			sld.shown = true;
			sld.startLocation = pchar.questTemp.different.TakeMayorsRing.city + sTemp;
			sld.startLocator = "item" + (rand(4) + 1);
			pchar.questTemp.different.TakeMayorsRing.item = true; // флаг кольцо валяется в итемах
			Log_QuestInfo("El anillo está en " + sld.startLocation + ", localizado en " + sld.startLocator);
		}
		SetTimerFunction("TakeMayorsRing_null", 0, 0, 1); // освобождаем разрешалку на миниквесты
		ReOpenQuestHeader("SeekMayorsRing");
		AddQuestRecord("SeekMayorsRing", "1");
		AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData("SeekMayorsRing", "sName", pchar.questTemp.different.TakeMayorsRing.Id);
		break;
	case "TakeRing_6":
		dialog.text = "¿Oh? Bueno, eso fue realmente inesperado... Pues, buena suerte entonces, capitán.";
		link.l1 = "Adiós.";
		link.l1.go = "exit";
		ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;

	case "TakeRing_S1":
		dialog.text = "¡Es mi anillo! ¡Has salvado mi vida!";
		link.l1 = "No es nada, señor.";
		link.l1.go = "TakeRing_S2";
		TakeItemFromCharacter(pchar, "MayorsRing");
		break;
	case "TakeRing_S2":
		dialog.text = "¡Aquí está tu dinero por un trabajo bien hecho! ¡Te estoy muy agradecido!";
		link.l1 = "Feliz de ayudar, señor, por favor tenga más cuidado la próxima vez.";
		link.l1.go = "exit";
		ChangeCharacterComplexReputation(pchar, "nobility", 5);
		ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 10);
		AddCharacterExpToSkill(pchar, "Leadership", 50);
		AddCharacterExpToSkill(pchar, "Fortune", 50);
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
		pchar.questTemp.different = "free";
		pchar.quest.TakeMayorsRing_null.over = "yes"; // снимаем таймер
		AddQuestRecord("SeekMayorsRing", "7");
		AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		CloseQuestHeader("SeekMayorsRing");
		DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
	case "TakeRing_S3":
		dialog.text = "¡Señor, ten piedad! Debería dejar de beber tanto...";
		link.l1 = "¡Eso es seguro! Aquí está tu anillo.";
		link.l1.go = "TakeRing_S4";
		break;
	case "TakeRing_S4":
		dialog.text = "Sí, sí, muchas gracias. ¡Estoy en deuda contigo! ¡Aquí está tu dinero por un trabajo bien hecho!";
		link.l1 = "Gracias " + GetAddress_FormToNPC(NPChar) + ".";
		link.l1.go = "exit";
		TakeItemFromCharacter(pchar, "MayorsRing");
		ChangeCharacterComplexReputation(pchar, "nobility", 3);
		ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 3);
		AddCharacterExpToSkill(pchar, "Leadership", 50);
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.different.TakeMayorsRing.price));
		pchar.questTemp.different = "free";
		pchar.quest.TakeMayorsRing_null.over = "yes"; // снимаем таймер
		AddQuestRecord("SeekMayorsRing", "7");
		AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		CloseQuestHeader("SeekMayorsRing");
		DeleteAttribute(pchar, "questTemp.different.TakeMayorsRing");
		break;
		// ---------------------- найти кольцо в борделе ----------------------------

	case "node_1":
		// ОСАДЫ homo
		if (CheckAttribute(&Colonies[FindColony(npchar.City)], "Siege"))
		{

			makearef(aData, NullCharacter.Siege);

			if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true)
			{
				dialog.text = "Ya hemos discutido todo, ¿no es así?";
				link.l1 = "Correcto. No te demoro más.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Lamento molestarte, pero no tengo tiempo para hablar contigo en este momento. Como debes saber, nuestra colonia fue atacada por " + NationNamePeople(sti(aData.nation)) + "  Tengo que ocuparme de nuestras defensas.";
				link.l1 = "Bueno, solo quería ofrecer mi asistencia en la defensa del fuerte.";
				link.l1.go = "siege_task";
				link.l2 = "Entonces no te retrasaré más.";
				link.l2.go = "exit";
			}
		}
		else
		{ //->
			makearef(aData, NullCharacter.Siege);
			if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true)
			{
				AddMoneyToCharacter(Pchar, (sti(aData.iSquadronPower) * 3000));
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
				ChangeCharacterComplexReputation(pchar, "nobility", 10);
				AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
				AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
				AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
				AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
				//--> слухи
				SiegeRumour("Dicen que nos has ayudado a repeler al escuadrón de " + NationNameSK(sti(aData.nation)) + " y defender nuestra colonia! Te estamos muy agradecidos, " + GetAddress_Form(NPChar) + ".", aData.Colony, sti(aData.conation), -1, 15, 3);
				//<-- слухи
				DeleteAttribute(aData, "PlayerHelpMayor");
				DeleteAttribute(aData, "HelpColony");
				dialog.text = "Ah, eres tú, " + GetAddress_Form(NPChar) + " " + GetFullName(pchar) + ", me alegra verte. Buenas noticias, logramos repeler el " + NationNameSK(sti(aData.nation)) + " invasores. Hiciste tu parte en esto también, y aquí está tu recompensa, " + (sti(aData.iSquadronPower) * 1500) + " piezas de a ocho. Aquí tienes.";
				link.l1 = "Gracias, " + GetAddress_FormToNPC(NPChar) + "¡Un placer hacer negocios contigo!";
				link.l1.go = "exit";
			}
			else
			{
				if (CheckAttribute(aData, "PlayerHelpMayor"))
					DeleteAttribute(aData, "PlayerHelpMayor");
				dialog.text = "¿Cuál fue la razón por la que viniste aquí y me distrajiste de importantes asuntos de estado?";
				if (npchar.city != "Panama") // Addon-2016 Jason
				{
					link.l1 = "Quería trabajar para " + NationNameGenitive(sti(NPChar.nation)) + ".";
					link.l1.go = "work";
				}
				// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
				if (CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
				{
					link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Dat") + " Me encontré con algunos piratas. Todos " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " están a bordo en este momento. Quiero entregarlos a las autoridades.";
					link.l11.go = "PiratesOnUninhabited_1";
				}

				link.l2 = "Iba a hablar contigo sobre un asunto importante.";
				if (CheckAttribute(pchar, "questTemp.ReasonToFast") && !CheckAttribute(pchar, "questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
				{
					link.l2.go = "ReasonToFast_Mayor1";
				}
				else
				{
					link.l2.go = "quests";
				}
				if (CheckAttribute(pchar, "GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
				{
					if (pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar, "GenQuest.CaptainComission.SpeakMayor"))
					{
						link.l12 = "Hay un capitán al mando de la patrulla " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")) + " llamado " + pchar.GenQuest.CaptainComission.Name + ", ¿cómo puedo encontrarlo?";
						link.l12.go = "CapComission_Mayor1";
					}
					if (CheckAttribute(pchar, "GenQuest.CaptainComission.PrisonFree"))
					{
						link.l12 = "Antiguo capitán al mando de la patrulla " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " aceptó revelar su escondite a las autoridades.";
						link.l12.go = "CapComission_Mayor9";
					}
					if (pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
					{
						link.l12 = "Antiguo capitán al mando de la patrulla  " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + "  me reveló su escondite.";
						link.l12.go = "CapComission_Mayor13";
					}
				}
				if (CheckAttribute(pchar, "GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25 && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
				{
					if (!CheckAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor"))
					{
						iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
						if (CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
						{
							link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + " Me encontré con un capitán " + pchar.GenQuest.ShipWreck.Name + " y sus marineros que fueron desembarcados por piratas " + pchar.GenQuest.ShipWreck.BadName + ". " + "Desafortunadamente, ya tenía demasiados hombres en mi barco y, por lo tanto, no podía llevarlos a bordo. Pero les dejé comida y armas. Si el barco de rescate no los recoge dentro de " + (30 - iDay) + " días, entonces no sé si los encontraré todavía con vida o no.";
							link.l13.go = "ShipWreck1";
						}
						else
						{
							link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + " Me encontré con marineros de un naufragio de la nave '" + pchar.GenQuest.ShipWreck.ShipTypeName + " con su capitán. " + "Desafortunadamente, ya tenía demasiados hombres en mi barco y, por lo tanto, no pude llevarlos a bordo. Pero les dejé comida y armas. Si el barco de rescate no los recoge dentro de " + (30 - iDay) + " días, entonces no sé si los encontraré aún con vida o no.";
							link.l13.go = "ShipWreck1";
						}
					}
				}
				//--> Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "Tengo un mensaje del pueblo de " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.StartCity + "Gen") + ".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				}
				//<-- генер почтового курьера 2 уровня

				// --> Warship, 16.05.11. Квест "Правосудие на продажу".
				if (CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
				{
					link.l15 = "Milord, he localizado una banda de contrabandistas cuyo cabecilla ha sido recientemente capturado por los guardias. Ahora están planeando su escape. Su barco '" + PChar.GenQuest.JusticeOnSale.ShipName + "' está atracado en " + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Gen") + ".";
					link.l15.go = "JusticeOnSale_1";
				}
				//<-- Правосудие на продажу

				if (GetPrisonerQty() > 0)
				{
					link.l3 = "Necesito entregar al capitán cautivo a las autoridades.";
					link.l3.go = "sell_prisoner";
				}
				// Jason --> Регата
				if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
				{
					link.l4 = "Estoy aquí para la regata. Aquí está mi invitación.";
					link.l4.go = "Regata";
				}
				link.l5 = "¿Quizás te gustaría tomarte un descanso?";
				link.l5.go = "Play_Game";
				link.l10 = "Solo fue una visita de cortesía, " + GetAddress_FormToNPC(NPChar) + ".";
				link.l10.go = "node_2";
			}
		} //<-
		break;

	case "Helen_node_1":
		// ОСАДЫ homo
		if (CheckAttribute(&Colonies[FindColony(npchar.City)], "Siege"))
		{

			makearef(aData, NullCharacter.Siege);

			if (CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true)
			{
				dialog.text = "Ya hemos discutido todo, ¿no es así?";
				link.l1 = "Correcto. No te demoro más.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Lamento molestarte, pero no tengo tiempo para hablar contigo en este momento. Como debes saber, nuestra colonia fue atacada por " + NationNamePeople(sti(aData.nation)) + " Debo ocuparme de nuestras defensas.";
				link.l1 = "Bueno, solo quería ofrecer mi ayuda en la defensa del fuerte.";
				link.l1.go = "siege_task";
				link.l2 = "Entonces no te retrasaré más.";
				link.l2.go = "exit";
			}
		}
		else
		{ //->
			makearef(aData, NullCharacter.Siege);
			if (CheckAttribute(aData, "PlayerHelpMayor") && sti(aData.PlayerHelpMayor) == true && CheckAttribute(aData, "HelpColony") && sti(aData.HelpColony) == true)
			{
				AddMoneyToCharacter(Pchar, (sti(aData.iSquadronPower) * 3000));
				ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 20);
				ChangeCharacterComplexReputation(pchar, "nobility", 10);
				AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 180);
				AddCharacterExpToSkill(GetMainCharacter(), "Sailing", 200);
				AddCharacterExpToSkill(GetMainCharacter(), "Accuracy", 200);
				AddCharacterExpToSkill(GetMainCharacter(), "Cannons", 200);
				//--> слухи
				SiegeRumour("¡Dicen que nos has ayudado a repeler al escuadrón de " + NationNameSK(sti(aData.nation)) + " y defender nuestra colonia! Te estamos muy agradecidos, " + GetAddress_Form(NPChar) + ".", aData.Colony, sti(aData.conation), -1, 15, 3);
				//<-- слухи
				DeleteAttribute(aData, "PlayerHelpMayor");
				DeleteAttribute(aData, "HelpColony");
				dialog.text = "Oh, eres tú, " + GetAddress_Form(NPChar) + " " + GetFullName(pchar) + ", me alegra verte. Buenas noticias: logramos repeler a los " + NationNameSK(sti(aData.nation)) + " invasores. Tú también hiciste tu parte en esto, y aquí está tu recompensa, " + (sti(aData.iSquadronPower) * 1500) + "piezas de a ocho. Aquí tienes.";
				link.l1 = "Gracias, " + GetAddress_FormToNPC(NPChar) + "¡Un placer hacer negocios contigo!";
				link.l1.go = "exit";
			}
			else
			{
				if (CheckAttribute(aData, "PlayerHelpMayor"))
					DeleteAttribute(aData, "PlayerHelpMayor");
				dialog.text = "¿Qué os trae hacia mí? Pensé que habíais manejado todos vuestros asuntos con vuestro... patrón. Pero hablad, siempre me alegra escucharos.";
				if (npchar.city != "Panama") // Addon-2016 Jason
				{
					link.l1 = "Quería trabajar para " + NationNameGenitive(sti(NPChar.nation)) + ".";
					link.l1.go = "work";
				}
				// Warship Генер "Пираты на необитайке" - сдаём пиратов властям
				if (CheckAttribute(PChar, "Quest.PiratesOnUninhabited_OnShore") || CheckAttribute(PChar, "Quest.PiratesOnUninhabited_ShipSink"))
				{
					link.l11 = XI_ConvertString(PChar.GenQuest.PiratesOnUninhabited.StartShore + "Dat") + " Me encontré con algunos piratas. Todos " + PChar.GenQuest.PiratesOnUninhabited.PiratesCount + " están a bordo en este momento. Quiero entregarlos a las autoridades.";
					link.l11.go = "PiratesOnUninhabited_1";
				}

				link.l2 = "Iba a hablar contigo sobre un asunto importante.";
				if (CheckAttribute(pchar, "questTemp.ReasonToFast") && !CheckAttribute(pchar, "questTemp.ReasonToFast.SpeakOther") && !CheckAttribute(pchar, "questTemp.ReasonToFast.cantSpeakOther") && (pchar.questTemp.ReasonToFast.city == NPChar.city))
				{
					link.l2.go = "ReasonToFast_Mayor1";
				}
				else
				{
					link.l2.go = "quests";
				}
				if (CheckAttribute(pchar, "GenQuest.CaptainComission") && (pchar.GenQuest.CaptainComission.variant == "A2") && (pchar.GenQuest.CaptainComission.City == NPChar.city))
				{
					if (pchar.GenQuest.CaptainComission == "Begin_1" && !CheckAttribute(pchar, "GenQuest.CaptainComission.SpeakMayor"))
					{
						link.l12 = "Hay un capitán al mando de la patrulla " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")) + " llamado " + pchar.GenQuest.CaptainComission.Name + ", ¿cómo puedo conocerlo?";
						link.l12.go = "CapComission_Mayor1";
					}
					if (CheckAttribute(pchar, "GenQuest.CaptainComission.PrisonFree"))
					{
						link.l12 = "Antiguo capitán al mando de la patrulla " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " aceptó revelar su escondite a las autoridades.";
						link.l12.go = "CapComission_Mayor9";
					}
					if (pchar.GenQuest.CaptainComission == "GetGoodsSuccess")
					{
						link.l12 = "Antiguo capitán al mando de la patrulla  " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.CaptainComission.ShipType), "Name") + "Acc")) + " " + pchar.GenQuest.CaptainComission.Name + " me reveló su escondite.";
						link.l12.go = "CapComission_Mayor13";
					}
				}
				if (CheckAttribute(pchar, "GenQuest.ShipWreck") && pchar.GenQuest.ShipWreck == "SailorsOnShore" && GetQuestPastDayParam("GenQuest.ShipWreck") < 25 && sti(npchar.nation) == sti(pchar.GenQuest.ShipWreck.Nation))
				{
					if (!CheckAttribute(pchar, "GenQuest.ShipWreck.SpeakMayor"))
					{
						iDay = GetQuestPastDayParam("GenQuest.ShipWreck");
						if (CheckAttribute(pchar, "GenQuest.ShipWreck.Mutiny"))
						{
							link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + " Me encontré con un capitán " + pchar.GenQuest.ShipWreck.Name + " y sus marineros que fueron desembarcados por piratas " + pchar.GenQuest.ShipWreck.BadName + ". " + "Desafortunadamente, ya tenía demasiados hombres en mi barco y por lo tanto no pude llevarlos a bordo. Pero les dejé comida y armas. Si el barco de rescate no los recoge dentro de " + (30 - iDay) + " días, entonces no sé si los encontraré aún vivos o no.";
							link.l13.go = "ShipWreck1";
						}
						else
						{
							link.l13 = UpperFirst(XI_ConvertString(pchar.GenQuest.ShipWreck.Shore + "Dat")) + " Me encontré con marineros de un naufragio de la nave '" + pchar.GenQuest.ShipWreck.ShipTypeName + " con su capitán. " + "Desafortunadamente, ya tenía demasiados hombres en mi barco y por lo tanto no pude llevarlos a bordo. Pero les dejé comida y armas. Si el barco de rescate no los recoge dentro de " + (30 - iDay) + " días, entonces no sé si los encontraré todavía vivos o no.";
							link.l13.go = "ShipWreck1";
						}
					}
				}
				//--> Jason, генер почтового курьера 2 уровня
				if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
				{
					if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
					{
						link.l14 = "Tengo un mensaje del pueblo de " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.StartCity + "Gen") + ".";
						link.l14.go = "Postcureer_LevelUp_ForAll";
					}
				}
				//<-- генер почтового курьера 2 уровня

				// --> Warship, 16.05.11. Квест "Правосудие на продажу".
				if (CheckAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait") && CheckAttribute(PChar, "GenQuest.JusticeOnSale.CityId") && NPChar.location == PChar.GenQuest.JusticeOnSale.CityId + "_townhall")
				{
					link.l15 = "Milord, he localizado una banda de contrabandistas cuyo cabecilla ha sido capturado recientemente por los guardias. Ahora están planeando su escape. Su barco '" + PChar.GenQuest.JusticeOnSale.ShipName + "' está anclado en " + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Gen") + ".";
					link.l15.go = "JusticeOnSale_1";
				}
				//<-- Правосудие на продажу

				if (GetPrisonerQty() > 0)
				{
					link.l3 = "Necesito entregar al capitán cautivo a las autoridades.";
					link.l3.go = "sell_prisoner";
				}
				// Jason --> Регата
				if (CheckAttribute(pchar, "questTemp.Regata.ToPortRoyal") && NPChar.location == "Portroyal_townhall")
				{
					link.l4 = "Estoy aquí para la regata. Aquí está mi invitación.";
					link.l4.go = "Regata";
				}
				link.l5 = "¿Quizás te gustaría tomarte un descanso?";
				link.l5.go = "Play_Game";
				link.l10 = "Era solo una visita de cortesía, " + GetAddress_FormToNPC(NPChar) + ".";
				link.l10.go = "node_2";
			}
		} //<-
		break;

	case "Play_Game":
		//==> прибыла инспекция на Святом Милосердии
		if (CheckAttribute(npchar, "quest.SantaMisericordia"))
		{
			dialog.text = "¡No ahora! Tenemos una inspección, don de Alamida está en la ciudad. Oh, cada año lo mismo, ¿qué hice para merecer esto?";
			link.l1 = "Como usted diga. No le distraeré.";
			link.l1.go = "exit";
			break;
		}
		//<== прибыла инспекция на Святом Милосердии
		dialog.text = "Hum, ¿y qué tipo de juegos prefieres?";
		link.l1 = "¿Quieres jugar una partida de cartas por una buena cantidad de dinero?";
		link.l1.go = "Card_Game";
		link.l2 = "¿Qué tal si jugamos a los dados en poker-joker?";
		link.l2.go = "Dice_Game";
		link.l10 = "Por favor discúlpame, pero el deber llama.";
		link.l10.go = "exit";
		break;

	//  карты -->
	case "Card_Game":
		if (!CheckNPCQuestDate(npchar, "Card_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
		{
			SetNPCQuestDate(npchar, "Card_date_Yet");
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (IsUniformEquip())
				dialog.text = "Le ruego me disculpe, monseñor, pero no tengo tiempo para eso ahora mismo. Quizás la próxima vez."; // Jason НСО
			else
				dialog.text = "¡No apuesto con piratas!";
			link.l1 = "Como desees.";
			link.l1.go = "exit";
		}
		else
		{
			if (CheckNPCQuestDate(npchar, "Card_date_begin"))
			{
				dialog.text = "¡Por qué no! Relajarse es bueno para el corazón, pero no para la bolsa...";
				link.l1 = "Excelente.";
				link.l1.go = "Cards_begin";
				link.l2 = "¿Cuáles son las reglas de nuestro juego?";
				link.l2.go = "Cards_Rule";
			}
			else
			{
				dialog.text = "No, he terminado por hoy. Tengo cosas que hacer.";
				link.l1 = "Como desees.";
				link.l1.go = "exit";
			}
		}
		break;

	case "Cards_Rule":
		dialog.text = CARDS_RULE;
		link.l1 = "¡Bueno, comencemos entonces!";
		link.l1.go = "Cards_begin";
		link.l3 = "No, no es para mí...";
		link.l3.go = "exit";
		break;

	case "Cards_begin":
		dialog.text = "Primero, acordemos la apuesta.";
		link.l1 = "Juguemos por 1000 piezas de a ocho.";
		link.l1.go = "Cards_Node_100";
		link.l2 = "Juguemos por 5000 piezas de a ocho.";
		link.l2.go = "Cards_Node_500";
		link.l3 = "Supongo que tengo que irme.";
		link.l3.go = "exit";
		break;

	case "Cards_Node_100":
		// belamour legendary edition
		bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
		bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
		bOk = bOk1 || bOk2;
		if (!CheckCardsGameSmallRate() && !bOk)
		{
			dialog.text = "Eres un tramposo notorio. No jugaré contigo.";
			link.l1 = "¡Son todas mentiras!";
			link.l1.go = "exit";
			break;
		}

		if (sti(pchar.Money) < 3000)
		{
			dialog.text = "¿Estás bromeando, " + GetAddress_Form(NPChar) + "? ¡No tienes dinero!";
			link.l1 = "Sucede.";
			link.l1.go = "exit";
			break;
		}
		if (sti(npchar.Money) < 3000)
		{
			dialog.text = "¡Eso es todo! He terminado con las cartas, antes de que me llamen derrochador y me obliguen a dejar mi puesto.";
			link.l1 = "Lástima.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "Bien, juguemos por 1000 piezas de a ocho.";
		link.l1 = "¡Comencemos!";
		link.l1.go = "Cards_begin_go";
		pchar.GenQuest.Cards.npcharIdx = npchar.index;
		pchar.GenQuest.Cards.iRate = 1000;
		pchar.GenQuest.Cards.SitType = false;
		break;

	case "Cards_Node_500":
		// belamour legendary edition
		bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
		bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
		bOk = bOk1 || bOk2;
		if (!CheckCardsGameSmallRate() && !bOk)
		{
			dialog.text = "Eres un notorio tramposo. No apostaré contigo.";
			link.l1 = "¡Son todas mentiras! Bueno, lo que sea.";
			link.l1.go = "exit";
			break;
		}
		if (!CheckCardsGameBigRate())
		{
			dialog.text = "Dicen que eres un muy buen jugador. No jugaré a altas apuestas contigo.";
			link.l1 = "¿Bajamos la apuesta, tal vez?";
			link.l1.go = "Cards_Node_100";
			link.l2 = "Lo siento, pero tengo que irme.";
			link.l2.go = "exit";
			break;
		}

		if (sti(pchar.Money) < 15000)
		{
			dialog.text = "¿Estás bromeando, " + GetAddress_Form(npchar) + "? ¡No tienes 15000 piezas de a ocho!";
			link.l1 = "¡Los conseguiré!";
			link.l1.go = "exit";
			break;
		}
		if (sti(npchar.Money) < 15000)
		{
			dialog.text = "No, estas apuestas vaciarán el tesoro de la ciudad.";
			link.l1 = "Como desees.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "Está bien, juguemos por 5000 piezas de a ocho.";
		link.l1 = "¡Comencemos!";
		link.l1.go = "Cards_begin_go";
		pchar.GenQuest.Cards.npcharIdx = npchar.index;
		pchar.GenQuest.Cards.iRate = 5000;
		pchar.GenQuest.Cards.SitType = false;
		break;

	case "Cards_begin_go":
		SetNPCQuestDate(npchar, "Card_date_begin");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LaunchCardsGame();
		break;
	// карты <--

	//  Dice -->
	case "Dice_Game":
		if (!CheckNPCQuestDate(npchar, "Dice_date_Yet") || sti(PChar.rank) < 4 || isBadReputation(pchar, 50) || GetCharacterSkillToOld(pchar, SKILL_LEADERSHIP) < rand(5))
		{
			SetNPCQuestDate(npchar, "Dice_date_Yet");
			// belamour legendary edition фикс проверки мундира с мушкетом
			if (IsUniformEquip())
				dialog.text = "Le ruego me disculpe, monseñor, pero no tengo tiempo para eso en este momento. Quizás la próxima vez."; // Jason НСО
			else
				dialog.text = "¡No apostaré con piratas!";
			link.l1 = "Como desees.";
			link.l1.go = "exit";
		}
		else
		{
			if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
			{
				dialog.text = "¡Por qué no! Relajarse es bueno para el corazón... pero no para la bolsa...";
				link.l1 = "Excelente.";
				link.l1.go = "Dice_begin";
				link.l2 = "¿Cuáles son las reglas de nuestro juego?";
				link.l2.go = "Dice_Rule";
			}
			else
			{
				dialog.text = "No, he terminado por hoy. Tengo cosas que hacer.";
				link.l1 = "Como desees.";
				link.l1.go = "exit";
			}
		}
		break;

	case "Dice_Rule":
		dialog.text = DICE_RULE;
		link.l1 = "¡Bueno, empecemos entonces!";
		link.l1.go = "Dice_begin";
		link.l3 = "No, no es para mí...";
		link.l3.go = "exit";
		break;

	case "Dice_begin":
		dialog.text = "Primero, acordemos la apuesta.";
		link.l1 = "Juguemos por 500 piezas de a ocho por dado.";
		link.l1.go = "Dice_Node_100";
		link.l2 = "Juguemos por 2000 piezas de a ocho por dado.";
		link.l2.go = "Dice_Node_500";
		link.l3 = "Supongo que tengo que irme.";
		link.l3.go = "exit";
		break;

	case "Dice_Node_100":
		// belamour legendary edition
		bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
		bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
		bOk = bOk1 || bOk2;
		if (!CheckDiceGameSmallRate() && !bOk)
		{
			dialog.text = "Eres un notorio tramposo. No apostaré contigo.";
			link.l1 = "¡Son todas mentiras! Bueno, lo que sea.";
			link.l1.go = "exit";
			break;
		}

		if (sti(pchar.Money) < 3000)
		{
			dialog.text = "¿Estás bromeando, " + GetAddress_Form(NPChar) + "? ¿No tienes dinero?";
			link.l1 = "Sucede.";
			link.l1.go = "exit";
			break;
		}
		if (sti(npchar.Money) < 3000)
		{
			dialog.text = "¡Eso es! He terminado con el juego, antes de que me llamen derrochador y me obliguen a dejar mi puesto...";
			link.l1 = "Lástima.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "Bien, juguemos por 500 piezas de a ocho.";
		link.l1 = "¡Empecemos!";
		link.l1.go = "Dice_begin_go";
		pchar.GenQuest.Dice.npcharIdx = npchar.index;
		pchar.GenQuest.Dice.iRate = 500;
		pchar.GenQuest.Dice.SitType = false;
		break;

	case "Dice_Node_500":
		// belamour legendary edition
		bOk1 = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4 && GetNationRelation(npchar.nation, sti(Items[sti(pchar.EquipedPatentId)].Nation)) != RELATION_ENEMY;
		bOk2 = CheckAttribute(pchar, "questTemp.Patria.GenGovernor") && GetNationRelation(npchar.nation, FRANCE) != RELATION_ENEMY;
		bOk = bOk1 || bOk2;
		if (!CheckDiceGameSmallRate() && !bOk)
		{
			dialog.text = "Eres un tramposo notorio. No jugaré contigo.";
			link.l1 = "¡Son todas mentiras! Bueno, lo que sea.";
			link.l1.go = "exit";
			break;
		}
		if (!CheckDiceGameBigRate())
		{
			dialog.text = "Dicen que eres un jugador muy bueno. No apostaré grandes cantidades contigo.";
			link.l1 = "¿Deberíamos bajar la apuesta, quizás?";
			link.l1.go = "Dice_Node_100";
			link.l2 = "Lo siento, pero tengo que irme.";
			link.l2.go = "exit";
			break;
		}

		if (sti(pchar.Money) < 15000)
		{
			dialog.text = "¿Estás bromeando, " + GetAddress_Form(NPChar) + "? ¡No tienes 15000 piezas de a ocho!";
			link.l1 = "¡Los conseguiré!";
			link.l1.go = "exit";
			break;
		}
		if (sti(npchar.Money) < 15000)
		{
			dialog.text = "No, estas apuestas vaciarán sin duda el tesoro de la ciudad.";
			link.l1 = "Como desees.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "Bien, juguemos por 2000 piezas de a ocho por dado.";
		link.l1 = "¡Empecemos!";
		link.l1.go = "Dice_begin_go";
		pchar.GenQuest.Dice.npcharIdx = npchar.index;
		pchar.GenQuest.Dice.iRate = 2000;
		pchar.GenQuest.Dice.SitType = false;
		break;

	case "Dice_begin_go":
		SetNPCQuestDate(npchar, "Dice_date_begin");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LaunchDiceGame();
		break;
	// Dice <--
	case "node_2":
		dialog.text = "En ese caso, te pediría que salgas de mi estudio y dejes de distraerme de mi trabajo.";
		link.l1 = "Sí, sí, por supuesto. Disculpa por molestarte.";
		link.l1.go = "exit";
		break;

	//---------------------------- генератор квестов мэра -------------------------------
	case "work":
		dialog.text = "Este es un error. Notifica a los desarrolladores sobre esto.";
		link.l1 = "¡Gracias, este es un gran juego!";
		link.l1.go = "exit";

		//==> прибыла инспекция на Святом Милосердии
		if (CheckAttribute(npchar, "quest.SantaMisericordia"))
		{
			dialog.text = "¡Ahora no! Tenemos una inspección, don de Alamida está en la ciudad. Oh, cada año lo mismo, ¿qué hice para merecer esto?";
			link.l1 = "Como usted diga. No lo distraeré.";
			link.l1.go = "exit";
			break;
		}
		//<== прибыла инспекция на Святом Милосердии
		//==> взят ли какой-либо квест
		if (CheckAttribute(pchar, "GenQuest.questName"))
		{
			//--> Федот, да не тот
			QuestName = pchar.GenQuest.questName;
			if (pchar.GenQuest.(QuestName).MayorId != npchar.id)
			{
				dialog.text = RandPhraseSimple("Por lo que puedo decir, ya tienes una misión que te ha dado el gobernador de " + XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city + "Gen") + "Termina el trabajo que ya tienes y hablaremos.", "Hmm, ¿no eras tú en " + XI_ConvertString("Colony" + characters[GetCharacterIndex(pchar.GenQuest.(QuestName).MayorId)].city + "Voc") + " donde has recibido órdenes del gobernador? Sí, eso es correcto. Termina esa misión primero.");
				link.l1 = RandPhraseSimple("Ya veo...", "Entendido..." + GetSexPhrase("", "") + ", " + GetAddress_FormToNPC(NPChar) + ".");
				link.l1.go = "exit";
				break;
			}
			//<--Федот, да не тот
			//-------- взят квест уничтожения банды ---------->>
			if (QuestName == "DestroyGang")
			{
				switch (pchar.GenQuest.DestroyGang)
				{
					makearef(arName, pchar.GenQuest.DestroyGang);
				case "":
					dialog.text = LinkRandPhrase("Una misión para localizar al bandido " + GetFullName(arName) + " ya se te ha otorgado. ¡Ahora cúmplelo!", "Ya tienes una misión para localizar a un bandido llamado " + GetFullName(arName) + "¡Estoy esperando los resultados!", " Mientras pierdes el tiempo en mi residencia, " + GetFullName(arName) + "¡está robando a nuestros colonos! ¡Ponte a trabajar!");
					link.l1 = RandPhraseSimple("Está bien, " + GetAddress_FormToNPC(NPChar) + ".", "Estoy ocupado con ello, " + GetAddress_FormToNPC(NPChar) + ".");
					link.l1.go = "exit";
					break;
				case "Late":
					dialog.text = RandPhraseSimple("El tiempo que se te dio para localizar y eliminar a ese bandido ha terminado. ¿Y qué tipo de informes estoy recibiendo, cómo crees? Y te diré, " + GetFullName(arName) + " ¡todavía está vivo y coleando! Ahora explíquese, " + GetAddress_Form(NPChar) + ".", "El tiempo que se te dio para eliminar a ese canalla llamado " + GetFullName(arName) + ", se ha agotado. Aun así, me están diciendo que no se ha hecho ningún progreso. ¿Qué pasa?");
					link.l1 = "No fui capaz de realizar tu trabajo en el tiempo señalado, " + GetAddress_FormToNPC(NPChar) + ".";
					link.l1.go = "All_Late";
					break;
				case "Found":
					dialog.text = RandPhraseSimple("Entonces, ¿qué dices? ¿Lograste eliminar al bandido mencionado? " + GetFullName(arName) + "¿Finalmente está muerto?", "Dime solo una cosa, ¿es " + GetFullName(arName) + " ¿muerto o vivo?");
					link.l1 = "Desafortunadamente, todavía con vida, " + GetAddress_FormToNPC(NPChar) + ". Logré encontrarlo, pero me superó y tuve que retirarme. Ese bandido es un bastardo realmente duro. Lo siento.";
					link.l1.go = "All_Found";
					break;
				case "Execute":
					dialog.text = RandPhraseSimple("Entonces, ¿qué dices? ¿Lograste eliminar al bandido mencionado? " + GetFullName(arName) + "¿está finalmente muerto?", "Dime solo una cosa, ¿es " + GetFullName(arName) + " ¿muerto o vivo?");
					link.l1 = "Está muerto, " + GetAddress_FormToNPC(NPChar) + ".";
					link.l1.go = "All_Execute";
					AddCharacterExpToSkill(PChar, "Leadership", 180);
					ChangeCharacterComplexReputation(pchar, "authority", 1);
					break;
				}
			}
			//-------- контркурьер ---------->>
			if (QuestName == "TakePostcureer")
			{
				switch (pchar.GenQuest.TakePostcureer)
				{
				case "":
					dialog.text = LinkRandPhrase("¡Ya se te ha asignado una misión para capturar un barco mensajero! ¡Ahora cúmplela!", "¡Ya tienes una misión para capturar un barco mensajero! ¡Estoy esperando los resultados!", "¡Mientras pierdes el tiempo en mi residencia, los documentos que necesito están cayendo directamente en manos de nuestros enemigos! ¡Ponte a trabajar!");
					link.l1 = RandPhraseSimple("Está bien, " + GetAddress_FormToNPC(NPChar) + ".", "Estoy ocupado con ello, " + GetAddress_FormToNPC(NPChar) + ".");
					link.l1.go = "exit";
					break;
				case "Late":
					dialog.text = RandPhraseSimple("El tiempo que se te dio para localizar y capturar ese barco mensajero ha terminado. ¿Y qué tipo de informes estoy recibiendo, cómo crees? Y te lo diré: ¡los documentos que esperaba cayeron directamente en manos de nuestro enemigo! Ahora digna de explicarte, " + GetAddress_Form(NPChar) + ".", "Todos los plazos dados para capturar los documentos del barco del mensajero han expirado. Aún así, no se ha hecho ningún progreso. ¿Qué es esto?");
					link.l1 = "No pude realizar el trabajo a tiempo, " + GetAddress_FormToNPC(NPChar) + ".";
					link.l1.go = "All_Late";
					break;
				case "Found":
					dialog.text = RandPhraseSimple("Entonces, ¿qué dices? ¿Lograste capturar los documentos?", "Dime solo una cosa: ¿has logrado asegurar la correspondencia?");
					link.l1 = "Desafortunadamente, no, " + GetAddress_FormToNPC(NPChar) + ". He localizado el barco, pero los documentos me han eludido.";
					link.l1.go = "All_Found";
					break;
				case "Execute":
					dialog.text = RandPhraseSimple("Entonces, ¿qué dices? ¿Lograste capturar los documentos?", "Dime solo una cosa, ¿has logrado asegurar la correspondencia?");
					link.l1 = "Sí, " + GetAddress_FormToNPC(NPChar) + " .  Los tengo. Aquí tienes.";
					link.l1.go = "All_Execute";
					AddCharacterExpToSkill(PChar, "Leadership", 200);
					AddCharacterExpToSkill(PChar, "Fortune", 300);
					AddCharacterExpToSkill(PChar, "Sneak", 150);
					RemoveItems(pchar, "ContraPostLetters", 1);
					ChangeCharacterComplexReputation(pchar, "authority", 1);
					break;
				}
			}
			//-------- контрфрахт - арсенал ---------->>
			if (QuestName == "TakeArsenalship")
			{
				switch (pchar.GenQuest.TakeArsenalship)
				{
				case "":
					dialog.text = LinkRandPhrase("¡Ya se te ha asignado una misión para destruir un transporte militar. Ahora cúmplela!", "¡Ya tienes una misión para destruir un transporte militar! ¡Estoy esperando los resultados!", "¡Mientras pierdes el tiempo en mi residencia, pólvora y municiones están siendo entregadas directamente a los cañones enemigos! ¡Ponte a trabajar!");
					link.l1 = RandPhraseSimple("Está bien, " + GetAddress_FormToNPC(NPChar) + ".", "Estoy ocupado con ello, " + GetAddress_FormToNPC(NPChar) + ".");
					link.l1.go = "exit";
					break;
				case "Late":
					dialog.text = RandPhraseSimple("El tiempo que se te dio para localizar y destruir ese transporte militar ha terminado. ¿Y qué clase de informes estoy recibiendo, cómo crees? Y te lo diré: ¡el convoy enemigo ha llegado con éxito a su destino! Ahora, ten la bondad de explicarte, " + GetAddress_Form(NPChar) + ".", "Todos los plazos dados para destruir el transporte militar enemigo han expirado. Aún así, no se ha hecho ningún progreso. ¿Qué pasa?");
					link.l1 = "No pude ejecutar tu tarea en el tiempo asignado, " + GetAddress_FormToNPC(NPChar) + ".";
					link.l1.go = "All_Late";
					break;
				case "Found":
					dialog.text = RandPhraseSimple("Entonces, ¿qué dices? ¿Lograste destruir el transporte enemigo?", "Dime solo una cosa: ¿ese inventario enemigo descansa en el fondo del mar?");
					link.l1 = "Desafortunadamente, no, " + GetAddress_FormToNPC(NPChar) + "He localizado el convoy, pero no logré hundir el buque requerido.";
					link.l1.go = "All_Found";
					break;
				case "Execute":
					dialog.text = RandPhraseSimple("Entonces, ¿qué dices? ¿Lograste destruir ese transporte enemigo?", "Dime solo una cosa: ¿el arsenal enemigo descansa en el fondo del mar?");
					link.l1 = "Sí, " + GetAddress_FormToNPC(NPChar) + ". Nuestro enemigo no recibirá esa pólvora y municiones.";
					link.l1.go = "All_Execute";
					AddCharacterExpToSkill(PChar, "Leadership", 220);
					AddCharacterExpToSkill(PChar, "Fortune", 300);
					AddCharacterExpToSkill(PChar, "Sneak", 150);
					ChangeCharacterComplexReputation(pchar, "authority", 1);
					break;
				}
			}
			//-------- ОЗГ - пират ---------->>
			if (QuestName == "TakePirateship")
			{
				switch (pchar.GenQuest.TakePirateship)
				{
				case "":
					dialog.text = LinkRandPhrase("¡Ya se te ha asignado una misión para eliminar a un pirata! ¡Ahora cúmplela!", "¡Ya tienes una misión para destruir un barco pirata! ¡Estoy esperando los resultados!", "¡Mientras pierdes el tiempo en mi residencia, ese sucio pirata está despojando a otra víctima! ¡Ponte a trabajar!");
					link.l1 = RandPhraseSimple("De acuerdo, " + GetAddress_FormToNPC(NPChar) + ".", "Estoy ocupado con ello, " + GetAddress_FormToNPC(NPChar) + ".");
					link.l1.go = "exit";
					break;
				case "Late":
					dialog.text = RandPhraseSimple("El tiempo que te fue dado para localizar y eliminar al pirata ha terminado. ¿Y qué tipo de informes estoy recibiendo, cómo crees? Y te lo diré: ¡ese sucio pirata sigue atacando nuestros barcos! Ahora ten la dignidad de explicarte, " + GetAddress_Form(NPChar) + ".", "Todos los plazos dados para destruir el barco pirata se han agotado. Aún así, no se ha hecho ningún progreso. ¿Qué pasa?");
					link.l1 = "No pude realizar su trabajo a tiempo, " + GetAddress_FormToNPC(NPChar) + ".";
					link.l1.go = "All_Late";
					break;
				case "Found":
					dialog.text = RandPhraseSimple("Entonces, ¿qué dices? ¿Lograste destruir el barco pirata?", "Dime una sola cosa: ¿ese asqueroso pirata finalmente descansa en el fondo del mar?");
					link.l1 = "Desafortunadamente, no, " + GetAddress_FormToNPC(NPChar) + ". Logré encontrar a ese canalla, pero no pude hundir su barco.";
					link.l1.go = "All_Found";
					break;
				case "Execute":
					dialog.text = RandPhraseSimple("Entonces, ¿qué dices? ¿Lograste destruir el barco pirata?", "Dime solo una cosa: ¿ese sucio pirata finalmente está descansando en el fondo del mar?");
					link.l1 = "Sí, " + GetAddress_FormToNPC(NPChar) + "   Ese sinvergüenza ya no molestará a nuestros barcos mercantes.";
					link.l1.go = "All_Execute";
					AddCharacterExpToSkill(PChar, "Leadership", 250);
					AddCharacterExpToSkill(PChar, "Fortune", 300);
					AddCharacterExpToSkill(PChar, "Sneak", 150);
					ChangeCharacterComplexReputation(pchar, "authority", 1);
					break;
				}
			}
			//-------- ОЗГ - пассажир ---------->>
			if (QuestName == "TakePassenger")
			{
				switch (pchar.GenQuest.TakePassenger)
				{
				case "":
					dialog.text = LinkRandPhrase("¡Ya se te ha encomendado una misión para buscar a un criminal. Ahora cúmplela!", "¡Ya tienes una misión para buscar a un criminal! ¡Estoy esperando los resultados!", "¡Mientras pierdes el tiempo en mi residencia, ese vil canalla sigue navegando por ahí! ¡Procede de inmediato con la misión que te ha sido encomendada!");
					link.l1 = RandPhraseSimple("Bien, " + GetAddress_FormToNPC(NPChar) + ".", "Estoy ocupado con ello, " + GetAddress_FormToNPC(NPChar) + ".");
					link.l1.go = "exit";
					break;
				case "Late":
					dialog.text = RandPhraseSimple("El tiempo que se te dio para localizar a ese canalla ha terminado. Y ¿qué tipo de informes estoy recibiendo, cómo crees? Y te lo diré: ¡llegó con éxito a su destino y luego se desvaneció en el aire! Ahora tengas a bien explicarte, " + GetAddress_Form(NPChar) + ".", "Todos los plazos dados para encontrar al criminal han expirado. Aun así, no se ha hecho ningún progreso. ¿Qué pasa?");
					link.l1 = "No pude ejecutar su tarea en el tiempo mencionado, " + GetAddress_FormToNPC(NPChar) + ".";
					link.l1.go = "All_Late";
					break;
				case "Found":
					dialog.text = RandPhraseSimple("Entonces, ¿qué dices? ¿Has capturado al villano?", "Dime solo una cosa: ¿está ese vil canalla en tu bodega, amordazado y encadenado?");
					link.l1 = "Desafortunadamente, no, " + GetAddress_FormToNPC(NPChar) + ". Fallé en capturar al villano. Se hundió con el barco en el que estaba.";
					link.l1.go = "All_Found";
					break;
				case "Execute":
					dialog.text = RandPhraseSimple("Entonces, ¿qué dices? ¿Has capturado al villano?", "Dime solo una cosa: ¿ese vil canalla está en tu bodega, amordazado y encadenado?");
					link.l1 = "Sí, " + GetAddress_FormToNPC(NPChar) + ". Por favor, envíe a sus soldados al muelle, y se lo entregaré.";
					link.l1.go = "All_Execute";
					AddCharacterExpToSkill(PChar, "Leadership", 250);
					AddCharacterExpToSkill(PChar, "Fortune", 300);
					AddCharacterExpToSkill(PChar, "Sneak", 200);
					ChangeCharacterComplexReputation(pchar, "authority", 1);
					sld = &Characters[sti(Pchar.GenQuest.TakePassenger.PrisonerIDX)];
					ReleasePrisoner(sld); // освободили пленника
					sld.lifeday = 0;
					break;
				}
			}
			//-------- таможенный патруль ---------->>
			if (QuestName == "CustomPatrol")
			{
				switch (pchar.GenQuest.CustomPatrol)
				{
				case "":
					dialog.text = LinkRandPhrase("¡Una misión para buscar a los contrabandistas ya te ha sido asignada. Ahora cúmplela!", "¡Ya tienes una misión para encontrar a los contrabandistas! ¡Estoy esperando los resultados!", "¡Mientras pierdes el tiempo en mi residencia, esos contrabandistas se preparan para cerrar otro trato! ¡Procede inmediatamente con la misión que se te ha encomendado!");
					link.l1 = RandPhraseSimple("De acuerdo, " + GetAddress_FormToNPC(NPChar) + ".", "Estoy ocupado con ello, " + GetAddress_FormToNPC(NPChar) + ".");
					link.l1.go = "exit";
					break;
				case "Late":
					dialog.text = RandPhraseSimple("El tiempo que se te dio para localizar a los contrabandistas ha terminado. ¿Y qué tipo de informes estoy recibiendo, cómo crees? Y te diré: ¡han vendido felizmente todas sus mercancías! Ahora ten la bondad de explicarte, " + GetAddress_Form(NPChar) + ".", "Todos los plazos dados para encontrar a los contrabandistas han caducado. Aún así, no se ha hecho ningún progreso. ¿Qué pasa?");
					link.l1 = "No pude ejecutar tu tarea a tiempo, " + GetAddress_FormToNPC(NPChar) + ".";
					link.l1.go = "All_Late";
					break;
				case "Found":
					dialog.text = RandPhraseSimple("Entonces, ¿qué dices? ¿Has tratado con los contrabandistas?", "Dime solo una cosa, ¿has arruinado el trato de esos contrabandistas?");
					link.l1 = "Lamentablemente, no, " + GetAddress_FormToNPC(NPChar) + ". Fracasé en frustrar los planes de esos villanos.";
					link.l1.go = "All_Found";
					break;
				case "Execute":
					dialog.text = RandPhraseSimple("Entonces, ¿qué dices? ¿Has tratado con los contrabandistas?", "Dime solo una cosa, ¿has arruinado el trato de esos contrabandistas?");
					link.l1 = "Sí, " + GetAddress_FormToNPC(NPChar) + ". Los alcancé y eliminé los barcos de ambas partes, comprador y vendedor por igual.";
					link.l1.go = "All_Execute";
					AddCharacterExpToSkill(PChar, "Leadership", 200);
					AddCharacterExpToSkill(PChar, "Fortune", 300);
					AddCharacterExpToSkill(PChar, "Sneak", 300);
					ChangeCharacterComplexReputation(pchar, "authority", 1);
					break;
				}
			}
			//-------- Дезертир ---------->>
			if (QuestName == "FindFugitive")
			{
				switch (pchar.GenQuest.FindFugitive)
				{
				case "":
					dialog.text = LinkRandPhrase("¡Ya se te ha asignado una misión para buscar al desertor. Ahora cúmplela!", "¡Ya tienes una misión para buscar al desertor! ¡Estoy esperando los resultados!", "¡Mientras pierdes el tiempo en mi residencia, ese desertor podría estar traicionando nuestros secretos de estado! ¡Procede inmediatamente con la misión que te ha sido encomendada!");
					link.l1 = RandPhraseSimple("De acuerdo, " + GetAddress_FormToNPC(NPChar) + ".", "Estoy ocupado con ello, " + GetAddress_FormToNPC(NPChar) + ".");
					link.l1.go = "exit";
					break;
				case "Late":
					dialog.text = RandPhraseSimple("El tiempo que se te dio para localizar al desertor ha terminado. Y qué clase de informes estoy recibiendo, ¿cómo crees? Y te diré: ningún resultado, ¡ninguno en absoluto! Ahora ten la bondad de explicarte, " + GetAddress_Form(NPChar) + ".", "Todos los términos dados para encontrar al desertor han expirado. Aún así, no se ha hecho ningún progreso. ¿Qué pasa?");
					link.l1 = "No pude realizar tu encargo a tiempo, " + GetAddress_FormToNPC(NPChar) + ".";
					link.l1.go = "All_Late";
					break;
				case "Found":
					dialog.text = RandPhraseSimple("Entonces, ¿qué dices? ¿Has capturado al desertor?", "Dime sólo una cosa: ¿ese desertor está en tu bodega, amordazado y con grilletes?");
					link.l1 = "Desafortunadamente, no, " + GetAddress_FormToNPC(NPChar) + ". Fracasé en capturar a ese bribón. Encontré su rastro en el asentamiento de " + XI_ConvertString("Colony" + pchar.GenQuest.FindFugitive.City) + ", pero justo el día antes de mi llegada se fue al sur en un barco pirata. Supongo que ahora está con esos caballeros de fortuna.";
					link.l1.go = "All_Found";
					break;
				case "Execute":
					dialog.text = RandPhraseSimple("Oh, bueno... Aquí está nuestro " + pchar.GenQuest.FindFugitive.Name + "... ¡Buen trabajo, capitán! ¿Has tenido dificultades buscando?", "¡Oh, qué invitados tenemos! Hola, " + pchar.GenQuest.FindFugitive.Name + "¡Buen trabajo, capitán! ¿Has empleado mucho esfuerzo en tu búsqueda?");
					link.l1 = "Cómo decir, " + GetAddress_FormToNPC(NPChar) + ".  Cualquiera que fuera, tu misión ha sido cumplida.";
					link.l1.go = "All_Execute";
					AddCharacterExpToSkill(PChar, "Leadership", 300);
					AddCharacterExpToSkill(PChar, "Fortune", 300);
					AddCharacterExpToSkill(PChar, "Sneak", 200);
					ChangeCharacterComplexReputation(pchar, "authority", 1);
					sld = &Characters[sti(Pchar.GenQuest.FindFugitive.PrisonerIDX)];
					ReleasePrisoner(sld); // освободили пленника
					LAi_SetActorType(sld);
					sld.lifeday = 0;
					pchar.quest.FindFugitive_Over.over = "yes"; // снимаем таймер
					chrDisableReloadToLocation = false;			// открыть локацию
					break;
				}
			}
			//------ проникновение во враждебный город ------------>>
			if (QuestName == "Intelligence")
			{
				switch (pchar.GenQuest.Intelligence)
				{
				case "":
					if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
					{
						dialog.text = RandPhraseSimple("El tiempo que se te dio para entregar la carta ha terminado. Y supongo que has fallado.", "El tiempo se ha agotado. Aún así, no se ha hecho ningún progreso. ¿Qué pasa?");
						link.l1 = "No pude realizar tu trabajo, " + GetAddress_FormToNPC(NPChar) + ".";
						link.l1.go = "All_Late";
					}
					else
					{
						dialog.text = LinkRandPhrase("¡Ya se te ha asignado una misión para entregarme una carta! ¡Ahora cúmplela!", "¡Ya tienes una misión para entregarme una carta directamente a mí! Estoy esperando los resultados, ¡necesito esa carta lo antes posible!", "¡Mientras pierdes el tiempo en mi residencia, la información que necesito desesperadamente sigue en manos de la persona que se supone debe enviármela! ¡Procede inmediatamente con la misión que se te ha encomendado!");
						link.l1 = RandPhraseSimple("Está bien, " + GetAddress_FormToNPC(NPChar) + ".", "Me pondré a ello de inmediato, " + GetAddress_FormToNPC(NPChar) + ".");
						link.l1.go = "exit";
					}
					break;
				case "Execute":
					dialog.text = RandPhraseSimple("¿Has entregado la carta que estoy esperando?", "¡Dime ahora, ¿lo tienes?!");
					link.l1 = "Sí, lo hago. Como acordamos, entregado a usted, personalmente.";
					if (GetQuestPastDayParam("GenQuest.Intelligence") > sti(pchar.GenQuest.Intelligence.Terms))
					{
						link.l1.go = "Intelligence_ExecuteLate";
						AddCharacterExpToSkill(PChar, "Sneak", 300);
					}
					else
					{
						link.l1.go = "All_Execute";
						AddCharacterExpToSkill(PChar, "Leadership", 100);
						AddCharacterExpToSkill(PChar, "Sneak", 300);
					}
					TakeItemFromCharacter(pchar, "sicretLetter");
					DeleteAttribute(ItemsFromID("sicretLetter"), "City");
					DeleteAttribute(ItemsFromID("sicretLetter"), "Mayor");
					break;
				}
			}
			break;
		}
		sTemp = npchar.city;
		// занят ПГГ
		i = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONMAYOR);
		if (i != -1)
		{
			dialog.text = "¡Ay, hoy no tengo trabajo para ti. El último ha sido realizado por " + GetFullName(&Characters[i]) + " . Ven mañana, tal vez aparezca algo.";
			link.l1 = "¡Oh, maldición! No hay suerte...";
			link.l1.go = "exit";
			break;
		}
		// navy <--
		if (!CheckAttribute(npchar, "work_date") || GetNpcQuestPastDayParam(npchar, "work_date") > 2 || bBettaTestMode)
		{
			SaveCurrentNpcQuestDateParam(npchar, "work_date");
			if (CheckAttribute(pchar, "questTemp.StatusCity") && pchar.questTemp.StatusCity == npchar.city)
			{
				dialog.text = "Estás justo a tiempo, capitán. Tengo que lidiar con un problema urgente relacionado con el contrabando de mercancías a nuestra colonia. Supongo que tu barco está en condiciones de navegar y listo para la batalla.";
				link.l1 = "Mi barco siempre está en condiciones de navegar y listo para la batalla. Por favor, dígame más sobre la próxima misión, su gracia.";
				link.l1.go = "CustomPatrol";
				break;
			}
			if (rand(5) > 4 && !bBettaTestMode && pchar.location == "Panama_townhall") // patch-5
			{
				dialog.text = LinkRandPhrase("Por ahora no tengo trabajo para ti. Ven mañana, supongo...", "Por desgracia, no tengo trabajo para ti hoy. Por favor, vuelve en un día o dos.", "Hoy no hay nada que pueda proponerte. Me alegrará verte otro día.");
				link.l1 = "Entiendo, " + GetAddress_FormToNPC(NPChar) + ".";
				link.l1.go = "exit";
			}
			else
			{
				sTemp = GetSpyColony(npchar);
				// не даём задание пробраться во вражеский город, если у нации ГГ нет врагов
				if (sTemp == "none")
					i = 1 + hrand(6);
				else
					i = hrand(7);
				switch (i)
				{
				//========== пробраться во вражеский город ============//Jason: оставляем, как годный
				case 0:
					pchar.GenQuest.Intelligence.Terms = hrand(10) + (42 - MOD_SKILL_ENEMY_RATE);					// сроки выполнения задания
					pchar.GenQuest.Intelligence.Money = ((hrand(4) + 6) * 2000) + (sti(pchar.rank) * 1000 + 10000); // вознаграждение
					pchar.GenQuest.Intelligence.City = sTemp;														// враждебная колония
					sTemp = ", que está en " + XI_ConvertString(colonies[FindColony(pchar.GenQuest.Intelligence.City)].islandLable + "Dat");
					dialog.text = "Tengo una misión para ti, que conlleva serios riesgos. Necesito que te infiltras en " + XI_ConvertString("Colony" + pchar.GenQuest.Intelligence.City + "Acc") + sTemp + ", encuentra a cierta persona allí y luego entrégame lo que él te dé.";
					link.l1 = "Hmm, no creo que en " + XI_ConvertString("Colony" + pchar.GenQuest.Intelligence.City + "Dat") + " Seré un invitado bienvenido...";
					link.l1.go = "Intelligence";
					break;
				//========== квест уничтожения банды ============ //Jason: оставляем, как классику
				case 1:
					pchar.GenQuest.DestroyGang.Terms = hrand(2) + 2;											// сроки выполнения задания
					pchar.GenQuest.DestroyGang.Money = ((hrand(6) + 4) * 500) + (sti(pchar.rank) * 300 + 2000); // вознаграждение
					makearef(arName, pchar.GenQuest.DestroyGang);
					arName.nation = PIRATE;
					arName.sex = "man";
					SetRandomNameToCharacter(arName); // имя бандита в структуру квеста
					dialog.text = "Justo ahora tengo una misión para ti. En la jungla cerca de " + XI_ConvertString("Colony" + npchar.city + "Gen") + " ha aparecido una banda de ladrones, y sé que su cabecilla se llama " + GetFullName(arName) + ". Localiza y elimina a esta banda de matones.";
					link.l1 = "¿Estoy de alguna manera limitado en términos?";
					link.l1.go = "DestroyGang";
					break;

				//========== контркурьер - отобрать почту ============
				case 2:
					dialog.text = "Sí, tengo una misión para ti. Para cumplirla, tendrás que demostrar rapidez y también algo de habilidad en el combate naval. ¿Estás listo para demostrar tu valía?";
					link.l1 = "Su Gracia, ¿puede revelar más detalles sobre la misión?";
					link.l1.go = "TakePostcureer";
					break;

				//========== контрфрахт - потопить корабль с боеприпасами ============
				case 3:
					dialog.text = "Sí, tengo una misión para ti. Para cumplirla, deberás demostrar una valentía excepcional y también cierta habilidad en el combate naval. ¿Estás listo para demostrar tu valía?";
					link.l1 = "Su Gracia, ¿puede revelar más detalles sobre la próxima misión?";
					link.l1.go = "TakeArsenalship";
					break;
				//========== ОЗГ - охотник на пирата ============
				case 4:
					dialog.text = "Sí, tengo una misión importante para ti. Para cumplirla, tendrás que usar todas tus habilidades. Esto involucra a piratas...";
					link.l1 = "¿Piratas? ¿Podrías decirme con más detalle qué se espera de mí, entonces?";
					link.l1.go = "TakePirateship";
					break;
				//========== ОЗГ - охотник на пассажира ============
				case 5:
					dialog.text = "Estás justo a tiempo, señor. Tengo una misión urgente que te vendrá de perlas. Se trata de buscar y capturar a cierta persona...";
					link.l1 = "¿Una cacería humana? ¿Puedes contarme con más detalles qué se espera de mí?";
					link.l1.go = "TakePassenger";
					break;
				//========== Патруль - таможенник ============
				case 6:
					dialog.text = "Estás justo a tiempo, capitán. Tengo que lidiar con un problema urgente relacionado con el contrabando de mercancías a nuestra colonia. ¿Supongo que tu barco está en condiciones de navegar y listo para la batalla?";
					link.l1 = "Mi barco siempre está en condiciones de navegar y listo para la batalla. Por favor, cuénteme más sobre la misión que se avecina, su gracia.";
					link.l1.go = "CustomPatrol";
					break;
					//========== Найти дезертира ============
				case 7:
					dialog.text = "Tengo una misión para ti que implica visitar varios asentamientos en el Caribe. ¿Estás listo para un largo viaje?";
					link.l1 = "Sí, ¿mis hombres y yo estamos listos para partir de inmediato? ¿Qué exactamente tendré que hacer?";
					link.l1.go = "FindFugitive";
					break;
				}
			}
		}
		else
		{
			dialog.text = LinkRandPhrase("Hoy no puedo ofrecerte ningún trabajo.", "Hoy no quedan más trabajos para ti.", "Ya no hay más trabajos por hoy, lo siento. Vuelve mañana, y veremos...");
			link.l1 = RandPhraseSimple("Lástima...", "Ah, qué lástima, " + GetAddress_FormToNPC(NPChar) + ". ");
			link.l1.go = "exit";
		}
		//---------------------------- генератор квестов мэра -------------------------------
		break;

	case "sell_prisoner":
		dialog.text = "¿A quién te gustaría rescatar?";

		qty = 1;
		for (i = 0; i < GetPassengersQuantity(pchar); i++)
		{
			cn = GetPassenger(pchar, i);
			if (cn != -1)
			{
				offref = GetCharacter(cn);
				if (CheckAttribute(offref, "prisoned"))
				{
					if (sti(offref.prisoned) == true && GetRemovable(offref)) // ставим только фантомов
					{
						attrLoc = "l" + qty;
						link.(attrLoc) = GetFullName(offref) + ", " + NationNameMan(sti(offref.nation)) + ".";
						link.(attrLoc).go = "GetPrisonerIdx_" + offref.index;
						qty++;
					}
				}
			}
		}
		link.l99 = "Nadie.";
		link.l99.go = "exit";
		break;

	case "sell_prisoner_2":
		offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
		attrLoc = "Así que, este es el capitán " + GetFullName(offref) + ", " + NationNameMan(sti(offref.nation)) + ".";
		// цена зависит от губернатора
		qty = makeint(sti(offref.rank) * (800 + GetCharacterSPECIALSimple(NPChar, SPECIAL_L) * 100) + GetCharacterSkillToOld(offref, "Leadership") * 500 + GetCharacterSkillToOld(pchar, "commerce") * 500);
		if(HasShipTrait(pchar, "trait14")) qty = makeint(qty * 1.35);
		if (sti(offref.nation) == sti(NPChar.nation))
		{
			attrLoc = attrLoc + " Estoy dispuesto a pagar el rescate de mi compatriota por un total de  " + FindRussianMoneyString(qty) + ".";
		}
		else
		{
			if (sti(offref.nation) == PIRATE)
			{
				qty = qty / 5;
				attrLoc = attrLoc + " Puedo darte " + FindRussianMoneyString(qty) + "  por esa sabandija. Y luego ejecutaremos al canalla de inmediato.";
			}
			else
			{
				qty = qty / 2;
				attrLoc = attrLoc + " " + FindRussianMoneyString(qty) + "por ese hombre, ni un peso más.";
			}
		}
		dialog.text = attrLoc;
		pchar.PrisonerSellPrice = qty;
		link.l1 = "Trato hecho. Es todo tuyo, " + GetAddress_FormToNPC(NPChar) + ".";
		link.l1.go = "sell_prisoner_3";
		link.l3 = "No. Esto no servirá.";
		link.l3.go = "exit";
		break;

	case "sell_prisoner_3":
		dialog.text = "Eso es bueno.";
		link.l1 = "Todo lo mejor.";
		link.l1.go = "exit";
		OfficersReaction("bad");

		offref = GetCharacter(sti(pchar.GenQuest.GetPrisonerIdx));
		AddMoneyToCharacter(pchar, sti(pchar.PrisonerSellPrice));
		if (sti(offref.nation) == sti(NPChar.nation))
		{
			AddCharacterExpToSkill(pchar, "Commerce", 25);
		}
		else
		{
			if (sti(offref.nation) == PIRATE)
			{
				ChangeCharacterComplexReputation(pchar, "nobility", -2);
			}
			else
			{
				AddCharacterExpToSkill(pchar, "Commerce", 5);
			}
		}

		offref.location = "";
		ReleasePrisoner(offref); // освободили пленника
		break;
	////   CAPTURE //////////
	case "CAPTURE_Main":
		NextDiag.TempNode = "CAPTURE_Main";
		AfterTownBattle(); // всё, все свободны

		// --> Левассер
		if (pchar.location == "Tortuga_townhall" && CheckAttribute(pchar, "questTemp.Sharlie.Hardcore_Tortuga"))
		{
			dialog.Text = "¡Arrgh! ¿Qué es este ultraje, de Maure? ¿Desde cuándo los franceses atacan a sus propios compatriotas?!";
			Link.l1 = "¡Por orden del Gobernador General François Longvilliers de Poincy, usted, Monsieur Levasseur, es destituido del cargo de gobernador de Tortuga y sentenciado a muerte! ¡Y yo soy quien ejecutará esta sentencia!";
			Link.l1.go = "levasser";
			break;
		}
		// <-- Левассер
		// fix от грабежа 5 раз на дню -->
		if (!CheckNPCQuestDate(npchar, "GrabbingTownDate"))
		{
			dialog.Text = "Ya has tomado todo. ¿Qué más necesitas?";
			Link.l1 = "Sí, claro, ciudad equivocada.";
			Link.l1.go = "Exit_City";

			NPChar.NoGiveMoney = true;

			ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 20);
			// вернём диалог после разговора и спрячем
			SetReturn_Gover_Dialog_Exit(NPChar);
			break;
		}
		SetNPCQuestDate(npchar, "GrabbingTownDate");
		// fix от грабежа 5 раз на дню <--

		if (CheckAttribute(FortChref, "Fort.Mode") && sti(FortChref.Fort.Mode) != FORT_DEAD)
		{ // а форт-то ЖИВ, значит с суши прошли
			dialog.Text = "¡Insolencia sin precedentes! Los refuerzos del fuerte llegarán pronto y pagarás por esto!";
			Link.l2 = "No voy a quedarme aquí hasta que lleguen. Solo págame, y dejaremos esta ciudad.";
			Link.l2.go = "Summ";
			Pchar.HalfOfPaymentByCity = true; // токо половина денег
		}
		else
		{
			dialog.Text = "Ganaste esta vez, pero ¡sepas que un escuadrón de nuestros caza-piratas te perseguirá y arrancará cada peso de tu sucia carne de pirata!";
			if (!bWorldAlivePause || bBettaTestMode)
			{
				int iColony = FindColony(npchar.city);
				if (!CheckAttribute(&colonies[iColony], "notCaptured")) // незахватываемые города
				{
					if (CheckAttribute(FortChref, "Default.Prison"))
					{
						Link.l1 = "¡Silencio! Esta ciudad me pertenece a partir de ahora; en cuanto a sus cazadores de piratas, los enviaré directamente al armario de Davy Jones. Muchachos, agarren a este cerdo y pónganlo tras las rejas.";
					}
					else
					{
						Link.l1 = "Esta ciudad ahora me pertenece. Chicos, escolten al ex-gobernador a sus nuevos 'aposentos', je je.";
					}
					Link.l1.go = "City";
				}
			}
			if (!isCityHasFort(NPChar.City))
			{
				Link.l2 = "¿Refuerzos del fuerte? Solo págame un buen rescate y dejaremos tu ciudad.";
			}
			else
			{
				Link.l2 = "¿Un escuadrón de cazadores de piratas? Hmm... Solo págame y dejaremos tu ciudad.";
			}
			Link.l2.go = "Summ";

			bOk = !bWorldAlivePause || bBettaTestMode;
			if (isMainCharacterPatented() && bOk && !CheckAttribute(&colonies[iColony], "notCaptured")) // не даем захватить колонию
			{
				// восстановим нацию патента
				PChar.nation = GetBaseHeroNation();

				dialog.Text = "¡Insolencia sin precedentes! ¿Cómo te atreves a atacar la colonia perteneciente a " + NationNameGenitive(sti(NPChar.nation)) + "¿¡Pagarás caro por la sangre que has derramado y por el daño que infligiste a nuestro estado!?";
				Link.l1 = "A partir de ahora, esta colonia me pertenece. Quien decida disputar mi autoridad irá directamente al infierno.";
				Link.l1.go = "City_patent";
				Link.l2 = "Apártate. Estoy actuando en nombre de " + NationNameGenitive(sti(PChar.nation)) + ". ¡A partir de este momento esta colonia pertenece a " + NationKingsCrown(PChar) + "!";
				Link.l2.go = "City_nation";
				Link.l3 = "Encantadora ciudad que tiene aquí. Sería una verdadera tragedia si fuera reducida a cenizas y su gobernador colgado en la plaza del pueblo. Deberíamos discutir el tamaño del rescate que está dispuesto a pagar para evitar que esa tragedia ocurra. ";
				Link.l3.go = "Summ_patent";
			}
		}
		break;

	// --> Левассер
	case "levasser":
		dialog.Text = "¿Poincy?! ¡Maldito bastardo papista! Me ocuparé de él... ¡y tú estás acabado, granuja! No saldrás de aquí con vida, ¡yo mismo te acabaré!";
		Link.l1 = "Ahórrame tu sermón, hereje. Cuando envíe tu alma hugonote al infierno, dale mis mejores deseos a Lucifer y a Juan Calvino. ¡En garde!";
		Link.l1.go = "levasser_1";
		break;

	case "levasser_1":
		chrDisableReloadToLocation = true; // закрыть локацию
		DialogExit();
		LAi_SetImmortal(npchar, false);
		ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto6");
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "LevasserDiedResidence");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;
		// <-- Левассер

	case "City":
		ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 40);
		AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 400);

		Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
		AddDialogExitQuest("Residence_Captured_Any");

		Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
		// ремонт
		RepairAllShips();
		Log_Info("Todas las naves han sido reparadas.");
		//  СЖ -->
		ReOpenQuestHeader("Gen_CityCapture");
		AddQuestRecordInfo("Gen_CityCapture", "t3");
		AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
		//  СЖ <--
		NextDiag.CurrentNode = "Prison";
		DialogExit();
		break;

	case "City_patent":
		ChangeCharacterComplexReputation(GetMainCharacter(), "nobility", -20); // пираты мы, но у нас патент
		dialog.Text = "¡Has ganado esta vez, pero sabe que nuestra escuadra llegará pronto y no dejará nada de ti!";
		Link.l1 = "Cierra la boca. Esta ciudad me pertenece a partir de ahora, en cuanto a tu escuadrón, lo enviaré directamente al infierno. Muchachos, escolten al ex-gobernador a sus nuevos 'aposentos', je je.";
		Link.l1.go = "City";
		break;

	case "Exit_for_pay":
		dialog.Text = "¿Qué más necesitas de mí?";
		Link.l1 = "Solo comprobando si me perdí de algo...";
		Link.l1.go = "exit";

		NextDiag.TempNode = "Exit_for_pay";
		break;

	case "Exit_City":
		NextDiag.CurrentNode = "Exit_for_pay";
		Pchar.GenQuestFort.fortCharacterIdx = FortChref.index;
		if (sti(NPChar.NoGiveMoney) == false) // себе берем
		{
			// вернём диалог после разговора и спрячем
			SetReturn_Gover_Dialog_Exit(NPChar);
			AddDialogExitQuestFunction("TWN_ExitForPay");
		}
		DialogExit();
		break;

	case "Summ":
		dialog.Text = "No tengo otra opción que aceptar tus términos. Toma tu maldito dinero y deja nuestra colonia de inmediato.";
		Link.l1 = "Un placer hacer negocios contigo.";
		Link.l1.go = "Exit_City";
		NPChar.NoGiveMoney = false;

		ChangeCharacterHunterScore(GetMainCharacter(), NationShortName(sti(NPChar.nation)) + "hunter", 30);
		AddCharacterExpToSkill(GetMainCharacter(), SKILL_FORTUNE, 300);
		AddCharacterExpToSkill(GetMainCharacter(), "Commerce", 300);

		Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_GrabbingTown", 1);
		//  СЖ -->
		ReOpenQuestHeader("Gen_CityCapture");
		AddQuestRecordInfo("Gen_CityCapture", "t2");
		AddQuestUserData("Gen_CityCapture", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
		//  СЖ <--
		break;

	case "Summ_patent":
		dialog.Text = "Está bien, expón tus términos...";
		Link.l1 = "¡Aye, vae victis! Empieza a contar tu dinero.";
		Link.l1.go = "Summ";
		ChangeCharacterComplexReputation(GetMainCharacter(), "nobility", -10); // не на службе
		break;

	case "City_nation":
		dialog.Text = "Está bien, nos rendimos a vuestra merced.";
		Link.l1 = "Te aconsejaría que abandones la ciudad tan pronto como puedas, los próximos cambios pueden ser bastante malos para tu salud. Adiós.";
		Link.l1.go = "Exit_City";
		NPChar.NoGiveMoney = true;

		ChangeCharacterComplexReputation(GetMainCharacter(), "nobility", 5);
		AddCharacterExpToSkill(GetMainCharacter(), "Leadership", 600);
		AddCharacterExpToSkill(GetMainCharacter(), "Sneak", 400);
		SetNationRelationBoth(sti(PChar.nation), sti(NPChar.nation), RELATION_ENEMY);

		PChar.questTemp.DontSetNewDialogToMayor = true; // иначе может сменить диалог и сбойнуть
		PChar.questTemp.DontNullDeposit = true;			// чтоб не нулили ростовщика
		SetCaptureTownByNation(NPChar.City, sti(PChar.nation));
		DeleteAttribute(PChar, "questTemp.DontSetNewDialogToMayor");
		AddDialogExitQuestFunction("LaunchColonyInfoScreen"); // табличка
															  //  СЖ -->
		sTemp = GetNationNameByType(sti(PChar.nation));
		ReOpenQuestHeader("Gen_CityCapture");
		AddQuestRecordInfo("Gen_CityCapture", "t1");
		AddQuestUserData("Gen_CityCapture", "sCity", XI_ConvertString("colony" + NPChar.City));
		AddQuestUserData("Gen_CityCapture", "sNation", XI_ConvertString(sTemp + "Gen"));
		//  СЖ <--
		AddTitleNextRate(sti(PChar.nation), 1);													  // счетчик звания
		SetCharacterRelationBoth(sti(FortChref.index), GetMainCharacterIndex(), RELATION_FRIEND); // нечего не даёт, тк работает OtherChar - а это губер, но он и так друг
		UpdateRelations();

		// 22.03.05  fix вернём диалог после разговора и спрячем
		//  внутри диалога не работало
		SetReturn_Gover_Dialog_Exit(NPChar);

		Statistic_AddValue(Pchar, NationShortName(sti(NPChar.nation)) + "_TakeTown", 1);
		break;

	case "Prison":
		dialog.Text = "¿Qué más necesitas de mí, bribón?";
		Link.l3 = "¿Cómo disfruta Su Excelencia de su nueva habitación? ¿Es lo suficientemente espaciosa? ¡Bien, ahora tengo que irme!";
		Link.l3.go = "exit";
		NextDiag.TempNode = "Prison";
		break;

	case "arestFree_1":
		dialog.text = "¿Asentarme? ¿Y cómo imaginas eso?";
		link.l1 = "Creo que una suma de " + iTotalTemp * 6000 + " pesos aún pueden salvarme, ¿no es así?";
		link.l1.go = "arestFree_2";
		link.l2 = "No. Y es hora de que me vaya. Mis mejores deseos.";
		link.l2.go = "arest_1";
		break;

	case "arestFree_2":
		if (GetCharacterSkillToOld(PChar, SKILL_FORTUNE) >= hrand(7) && iTotalTemp < 21)
		{
			dialog.text = "Supongo que podríamos resolver nuestro incidente de esa manera. Aún no has llegado tan lejos como para hacer la situación irreparable.";
			link.l1 = "Excelente. Estoy muy contento. Por favor, acepte mi donación.";
			link.l1.go = "Exit";
			AddMoneyToCharacter(pchar, -iTotalTemp * 6000);
			ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", -iTotalTemp);
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		}
		else
		{
			dialog.text = "¿Me estás ofreciendo un soborno? ¡Oh no! Tus malvados actos solo pueden expiarse de una forma... ¡Guardias! Poned " + GetSexPhrase("él", "ella") + "¡en grilletes!";
			link.l1 = "¡Aguanta!";
			link.l1.go = "arest_2";
			AddCharacterExpToSkill(pchar, "Fortune", 10);
		}
		break;

	case "arest_1":
		dialog.text = "Por supuesto, ha llegado la hora. Te despediremos. ¡Guardias! ¡Arrésten" + GetSexPhrase("lo", "la") + "!";
		link.l1 = "¡De ninguna manera!";
		link.l1.go = "fight";
		break;

	case "arest_2":
		dialog.text = "¡Has tenido tiempo de sobra para pensar! ¡Guardias!";
		link.l1 = "¡No me atraparás fácilmente!";
		link.l1.go = "fight";
		break;
	/////////////////////////////////////////////////////////////////////////////////////////////////
	//	Уничтожение банды
	/////////////////////////////////////////////////////////////////////////////////////////////////
	case "DestroyGang":
		dialog.text = "Por supuesto. Para cumplir esta misión, te estoy dando " + FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms)) + ", y tu recompensa en caso de éxito será " + FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money)) + ".";
		link.l1 = "Aye, acepto esta tarea.";
		link.l1.go = "DestroyGang_agree";
		link.l2 = "Hmm... No, creo que lo dejaré pasar. ";
		link.l2.go = "All_disagree";
		break;
	case "DestroyGang_agree":
		npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
		pchar.GenQuest.questName = "DestroyGang";					   // тип квеста
		pchar.GenQuest.DestroyGang.Location = GetGangLocation(npchar); // определяем локацию,где банда
		pchar.GenQuest.DestroyGang.MayorId = npchar.id;				   // Id мэра, чтобы знать, кто дал квест
		if (pchar.GenQuest.DestroyGang.Location == "none")			   // на всякий случай
		{
			dialog.text = "Espera, acabo de olvidar el informe de ayer. El caso es que esta banda ya ha dejado nuestra isla. Así que tengo que cancelar la misión.";
			link.l1 = "Ya veo. Una lástima.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
			DeleteAttribute(pchar, "GenQuest.questName");
		}
		else
		{
			dialog.text = "¡Bueno, magnífico! Estaré esperando en mi residencia por ti y tus informes.";
			link.l1 = "No te haré esperar mucho, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "exit";
			pchar.quest.DestroyGang.win_condition.l1 = "location";
			pchar.quest.DestroyGang.win_condition.l1.location = pchar.GenQuest.DestroyGang.Location;
			pchar.quest.DestroyGang.win_condition = "DestroyGang_fight";
			pchar.quest.DestroyGang.again = true; // тупо дожидаться своего часа бандиты не будут
			SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.DestroyGang.Terms), false);
			//==> энкаунтеров в квестовой локации не будет
			locations[FindLocation(pchar.GenQuest.DestroyGang.Location)].DisableEncounters = true;
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "1");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			makearef(arName, pchar.GenQuest.DestroyGang);
			AddQuestUserData("MayorsQuestsList", "GangName", GetFullName(arName));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.DestroyGang.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.DestroyGang.Money)));
		}
		break;
	/////////////////////////////////////////////////////////////////////////////////////////////////
	//	Контркурьер
	/////////////////////////////////////////////////////////////////////////////////////////////////
	case "TakePostcureer":
		// установка параметров
		pchar.GenQuest.questName = "TakePostcureer"; // тип квеста
		// belamour legendary edition враждебную нацию квестодателя, а не героя -->
		pchar.GenQuest.TakePostcureer.Nation = FindEnemyNation2Character(sti(npchar.index)); // вражеская нация
		iTemp = 1;
		while (iTemp < 10 && sti(pchar.GenQuest.TakePostcureer.Nation) == PIRATE)
		{
			pchar.GenQuest.TakePostcureer.Nation = FindEnemyNation2Character(sti(npchar.index));
			iTemp += 1;
		}
		if (iTemp == 10 && sti(pchar.GenQuest.TakePostcureer.Nation) == PIRATE)
		{
			dialog.text = LinkRandPhrase("Hoy no puedo ofrecerte ningún trabajo.", "Hoy no quedan más trabajos para ti.", "No hay más trabajos por hoy, lo siento. Vuelve mañana, y veremos...");
			link.l1 = RandPhraseSimple("Lástima...", "Ah, qué lástima, " + GetAddress_FormToNPC(NPChar) + ". ");
			link.l1.go = "exit";

			if (CheckAttribute(pchar, "GenQuest.questName"))
			{
				QuestName = pchar.GenQuest.questName;
				DeleteAttribute(pchar, "GenQuest." + QuestName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}

			break;
		}
		pchar.GenQuest.TakePostcureer.City = FindQuestCity(npchar, "enemy", sti(pchar.GenQuest.TakePostcureer.Nation), false, false);
		// <-- legendary edition
		pchar.GenQuest.TakePostcureer.Island = GetArealByCityName(pchar.GenQuest.TakePostcureer.City);
		pchar.GenQuest.TakePostcureer.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakePostcureer.Island) + 5;
		pchar.GenQuest.TakePostcureer.LoginDay = sti(pchar.GenQuest.TakePostcureer.Terms) - 1;
		pchar.GenQuest.TakePostcureer.ShipType = SelectCureerShipType();
		pchar.GenQuest.TakePostcureer.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakePostcureer.Nation));
		pchar.GenQuest.TakePostcureer.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePostcureer.ShipType));
		pchar.GenQuest.TakePostcureer.Money = ((hrand(5) + hrand(6) + 4) * 2000) + (sti(pchar.rank) * 500);
		dialog.text = "Por supuesto. Necesitarás localizar un barco mensajero de " + NationNameGenitive(sti(pchar.GenQuest.TakePostcureer.Nation)) + " de nombre '" + pchar.GenQuest.TakePostcureer.ShipName + ", abórdalo y tráeme los papeles, que deberías poder encontrar en el camarote del capitán. Esta nave estará pasando cerca de " + XI_ConvertString("Colony" + pchar.GenQuest.TakePostcureer.City + "Gen") + " aproximadamente en " + FindRussianDaysString(pchar.GenQuest.TakePostcureer.Terms) + ".";
		link.l1 = "Está bien, acepto esta misión. ¿Y qué tipo de documentos debo buscar?";
		link.l1.go = "TakePostcureer_agree";
		link.l2 = "Mm... No, creo que pasaré.";
		link.l2.go = "All_disagree";
		break;

	case "TakePostcureer_agree":
		npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
		pchar.GenQuest.TakePostcureer.MayorId = npchar.id; // Id мэра, чтобы знать, кто дал квест
		dialog.text = "Correo. Hay papeles muy importantes para mí. Pero no es necesario que busques entre los documentos, solo tráeme todo el paquete. Te pagaré " + FindRussianMoneyString(sti(pchar.GenQuest.TakePostcureer.Money)) + "\nEntonces, te estaré esperando a ti y el resultado de tu trabajo en mi residencia.";
		link.l1 = "No te haré esperar mucho, " + GetAddress_FormToNPC(NPChar) + ".";
		link.l1.go = "exit";
		pchar.quest.TakePostcureer.win_condition.l1 = "location";
		pchar.quest.TakePostcureer.win_condition.l1.location = pchar.GenQuest.TakePostcureer.Island;
		pchar.quest.TakePostcureer.win_condition.l2 = "Timer";
		pchar.quest.TakePostcureer.win_condition.l2.date.hour = sti(GetTime());
		pchar.quest.TakePostcureer.win_condition.l2.date.day = GetAddingDataDay(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
		pchar.quest.TakePostcureer.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
		pchar.quest.TakePostcureer.win_condition.l2.date.year = GetAddingDataYear(0, 0, sti(pchar.GenQuest.TakePostcureer.LoginDay));
		pchar.quest.TakePostcureer.function = "TakePostcureer_CreateShip";
		SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePostcureer.Terms), false);
		ReOpenQuestHeader("MayorsQuestsList");
		AddQuestRecord("MayorsQuestsList", "3");
		AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
		AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.TakePostcureer.City + "Gen"));
		AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakePostcureer.Terms)));
		AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePostcureer.Money)));
		AddQuestUserData("MayorsQuestsList", "sNation", NationNameGenitive(sti(pchar.GenQuest.TakePostcureer.Nation)));
		AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePostcureer.ShipName);
		break;

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//	Контрфрахт - уничтожить корабль с арсеналом
	/////////////////////////////////////////////////////////////////////////////////////////////////
	case "TakeArsenalship":
		// установка параметров
		pchar.GenQuest.questName = "TakeArsenalship"; // тип квеста
		// belamour legendary edition враждебную нацию квестодателя, а не героя -->
		pchar.GenQuest.TakeArsenalship.Nation = FindEnemyNation2Character(sti(npchar.index));
		iTemp = 1;
		while (iTemp < 10 && sti(pchar.GenQuest.TakeArsenalship.Nation) == PIRATE)
		{
			pchar.GenQuest.TakeArsenalship.Nation = FindEnemyNation2Character(sti(npchar.index));
			iTemp += 1;
		}
		if (iTemp == 10 && sti(pchar.GenQuest.TakeArsenalship.Nation) == PIRATE)
		{
			dialog.text = LinkRandPhrase("Hoy no puedo ofrecerte ningún trabajo.", "Hoy no hay más trabajos para ti.", " No más trabajos por hoy, lo siento. Vuelve mañana, y veremos...");
			link.l1 = RandPhraseSimple("Lástima...", "Ah, qué lástima, " + GetAddress_FormToNPC(NPChar) + ". ");
			link.l1.go = "exit";

			if (CheckAttribute(pchar, "GenQuest.questName"))
			{
				QuestName = pchar.GenQuest.questName;
				DeleteAttribute(pchar, "GenQuest." + QuestName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}

			break;
		}
		pchar.GenQuest.TakeArsenalship.City = FindQuestCity(npchar, "enemy", sti(pchar.GenQuest.TakeArsenalship.Nation), false, false);
		// <-- legendary edition
		pchar.GenQuest.TakeArsenalship.Island = GetArealByCityName(pchar.GenQuest.TakeArsenalship.City);
		pchar.GenQuest.TakeArsenalship.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakeArsenalship.Island) + 5;
		pchar.GenQuest.TakeArsenalship.LoginDay = sti(pchar.GenQuest.TakeArsenalship.Terms) - 1;
		pchar.GenQuest.TakeArsenalship.ShipType = SelectArsenalShipType(FLAG_SHIP_TYPE_RAIDER);
		pchar.GenQuest.TakeArsenalship.ShipTypeA = SelectArsenalShipType(FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_UNIVERSAL);
		pchar.GenQuest.TakeArsenalship.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakeArsenalship.Nation));
		pchar.GenQuest.TakeArsenalship.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakeArsenalship.ShipType));
		pchar.GenQuest.TakeArsenalship.CannonA = SelectLevelCannonParameter(sti(pchar.GenQuest.TakeArsenalship.ShipTypeA)); // Addon 2016-1 Jason пиратская линейка
		pchar.GenQuest.TakeArsenalship.Money = ((hrand(5) + hrand(6) + 4) * 1800) + (sti(pchar.rank) * 500);
		dialog.text = "Por supuesto. Necesitarás localizar un transporte militar de " + NationNameGenitive(sti(pchar.GenQuest.TakeArsenalship.Nation)) + ", con pólvora y municiones a bordo; el nombre del buque es '" + pchar.GenQuest.TakeArsenalship.ShipName + "', encontrarlo y destruirlo. Vamos a debilitar a nuestro enemigo haciendo eso.\nEl transporte navegará con escolta hasta la colonia " + XI_ConvertString("Colony" + pchar.GenQuest.TakeArsenalship.City) + ", y será aproximadamente en " + FindRussianDaysString(pchar.GenQuest.TakeArsenalship.Terms) + ", así que deberías darte prisa.";
		link.l1 = "Está bien, acepto. ¿Debo hundir el barco del arsenal o debo intentar capturarlo?";
		link.l1.go = "TakeArsenalship_agree";
		link.l2 = "Hmm... No, creo que pasaré.";
		link.l2.go = "All_disagree";
		break;

	case "TakeArsenalship_agree":
		npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
		pchar.GenQuest.TakeArsenalship.MayorId = npchar.id; // Id мэра, чтобы знать, кто дал квест
		dialog.text = "No me importa, eso depende de ti. Lo importante es que este cargamento no debe llegar a su destino. Si tienes éxito, te pagaré " + FindRussianMoneyString(sti(pchar.GenQuest.TakeArsenalship.Money)) + "... Ya no te estoy retrasando, capitán.";
		link.l1 = "No te haré esperar mucho, " + GetAddress_FormToNPC(NPChar) + ".";
		link.l1.go = "exit";
		pchar.quest.TakeArsenalship.win_condition.l1 = "location";
		pchar.quest.TakeArsenalship.win_condition.l1.location = pchar.GenQuest.TakeArsenalship.Island;
		pchar.quest.TakeArsenalship.win_condition.l2 = "Timer";
		pchar.quest.TakeArsenalship.win_condition.l2.date.hour = sti(GetTime());
		pchar.quest.TakeArsenalship.win_condition.l2.date.day = GetAddingDataDay(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
		pchar.quest.TakeArsenalship.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
		pchar.quest.TakeArsenalship.win_condition.l2.date.year = GetAddingDataYear(0, 0, sti(pchar.GenQuest.TakeArsenalship.LoginDay));
		pchar.quest.TakeArsenalship.function = "TakeArsenalship_CreateShip";
		SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakeArsenalship.Terms), false);
		ReOpenQuestHeader("MayorsQuestsList");
		AddQuestRecord("MayorsQuestsList", "8");
		AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
		AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.TakeArsenalship.City));
		AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakeArsenalship.Terms)));
		AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakeArsenalship.Money)));
		AddQuestUserData("MayorsQuestsList", "sNation", NationNameGenitive(sti(pchar.GenQuest.TakeArsenalship.Nation)));
		AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakeArsenalship.ShipName);
		break;

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//	ОЗГ - уничтожить корабль пиратов
	/////////////////////////////////////////////////////////////////////////////////////////////////
	case "TakePirateship":
		// установка параметров
		pchar.GenQuest.questName = "TakePirateship";									   // тип квеста
		pchar.GenQuest.TakePirateship.City = FindQuestCity(npchar, "all", -1, true, true); // belamour legendary edition
		pchar.GenQuest.TakePirateship.Island = GetArealByCityName(pchar.GenQuest.TakePirateship.City);
		pchar.GenQuest.TakePirateship.Terms = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, pchar.GenQuest.TakePirateship.Island) + 5;
		pchar.GenQuest.TakePirateship.ShipType = SelectPirateShipType();
		pchar.GenQuest.TakePirateship.ShipName = GenerateRandomNameToShip(PIRATE);
		pchar.GenQuest.TakePirateship.Name = GenerateRandomName(PIRATE, "man");
		pchar.GenQuest.TakePirateship.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePirateship.ShipType));
		pchar.GenQuest.TakePirateship.Money = ((hrand(5) + hrand(6) + 4) * 2400) + (sti(pchar.rank) * 500);
		dialog.text = "Por supuesto. Estoy realmente enfurecido por las actividades de un capitán pirata, cuyo nombre es " + pchar.GenQuest.TakePirateship.Name + ". Ese sinvergüenza ha caído en el hábito de asaltar a nuestros mercantes, lo que perjudica enormemente el comercio entre las colonias. Ahora es el momento perfecto para deshacerse de ese bastardo, porque casualmente acabo de saber dónde se esconde en este momento. ¿Estás listo para enviar a este hijo de puta al Juicio de Dios?";
		link.l1 = "¡Sería un honor! ¿Dónde puedo encontrar a ese pirata?";
		link.l1.go = "TakePirateship_agree";
		link.l2 = "Hum... No, creo que pasaré.";
		link.l2.go = "All_disagree";
		break;

	case "TakePirateship_agree":
		npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
		pchar.GenQuest.TakePirateship.MayorId = npchar.id; // Id мэра, чтобы знать, кто дал квест
		dialog.text = "En el más cercano " + FindRussianDaysString(pchar.GenQuest.TakePirateship.Terms) + " su barco llamado '" + pchar.GenQuest.TakePirateship.ShipName + "' estará navegando por las costas cerca de " + XI_ConvertString("Colony" + pchar.GenQuest.TakePirateship.City + "Gen") + ". Encuéntralo y mátalo. Manda alimentar a los peces con el barco, aborda el barco, no me importa. Solo me importa que ese maldito pirata deje de profanar nuestro mar con su presencia\nPor esta tarea estoy dispuesto a pagarte " + FindRussianMoneyString(sti(pchar.GenQuest.TakePirateship.Money)) + ". No pierda tiempo, capitán: este canalla no le estará esperando en " + XI_ConvertString("Colony" + pchar.GenQuest.TakePirateship.City + "Gen") + "Ve, y ¡que Dios te ayude!";
		link.l1 = "¿Levantando anclas ya, " + GetAddress_FormToNPC(NPChar) + "? ¡No esperarás mucho tiempo!";
		link.l1.go = "exit";
		pchar.quest.TakePirateship.win_condition.l1 = "location";
		pchar.quest.TakePirateship.win_condition.l1.location = pchar.GenQuest.TakePirateship.Island;
		pchar.quest.TakePirateship.function = "TakePirateship_CreateShip";
		SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePirateship.Terms), false);
		ReOpenQuestHeader("MayorsQuestsList");
		AddQuestRecord("MayorsQuestsList", "9");
		AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
		AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.TakePirateship.City + "Gen"));
		AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.TakePirateship.Terms)));
		AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePirateship.Money)));
		AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.TakePirateship.Name);
		AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePirateship.ShipName);
		break;

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//	ОЗГ - захватить пассажира
	/////////////////////////////////////////////////////////////////////////////////////////////////
	case "TakePassenger":
		// установка параметров
		pchar.GenQuest.questName = "TakePassenger";											// тип квеста
		pchar.GenQuest.TakePassenger.Nation = FindEnemyNation2Character(sti(npchar.index)); // вражеская нация
		iTemp = 1;
		while (iTemp < 10 && sti(pchar.GenQuest.TakePassenger.Nation) == PIRATE)
		{
			pchar.GenQuest.TakePassenger.Nation = FindEnemyNation2Character(sti(npchar.index));
			iTemp += 1;
		}
		if (iTemp == 10 && sti(pchar.GenQuest.TakePassenger.Nation) == PIRATE)
		{
			dialog.text = LinkRandPhrase("Hoy no puedo ofrecerte ningún trabajo.", "Hoy no hay más trabajos para ti.", "Hoy no hay más trabajos, lo siento. Vuelve mañana y veremos...");
			link.l1 = RandPhraseSimple("Lástima...", "Ah, qué lástima, " + GetAddress_FormToNPC(NPChar) + ". ");
			link.l1.go = "exit";

			if (CheckAttribute(pchar, "GenQuest.questName"))
			{
				QuestName = pchar.GenQuest.questName;
				DeleteAttribute(pchar, "GenQuest." + QuestName);
				DeleteAttribute(pchar, "GenQuest.questName");
			}

			break;
		}
		pchar.GenQuest.TakePassenger.City = FindQuestCity(npchar, "enemy", sti(pchar.GenQuest.TakePassenger.Nation), false, false); // belamour legendary edition
		pchar.GenQuest.TakePassenger.CityA = SelectAnyColony(pchar.GenQuest.TakePassenger.City);
		pchar.GenQuest.TakePassenger.Terms1 = GetMaxDaysFromIsland2Island(Islands[GetCharacterCurrentIsland(PChar)].id, GetArealByCityName(pchar.GenQuest.TakePassenger.City));
		pchar.GenQuest.TakePassenger.Terms2 = GetMaxDaysFromIsland2Island(GetArealByCityName(pchar.GenQuest.TakePassenger.City), GetArealByCityName(pchar.GenQuest.TakePassenger.CityA)) + 1;
		pchar.GenQuest.TakePassenger.Terms = sti(pchar.GenQuest.TakePassenger.Terms1) + sti(pchar.GenQuest.TakePassenger.Terms2);
		pchar.GenQuest.TakePassenger.ShipType = SelectCureerShipType();
		pchar.GenQuest.TakePassenger.ShipName = GenerateRandomNameToShip(sti(pchar.GenQuest.TakePassenger.Nation));
		pchar.GenQuest.TakePassenger.Name = GenerateRandomName(sti(pchar.GenQuest.TakePassenger.Nation), "man");
		pchar.GenQuest.TakePassenger.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.TakePassenger.ShipType));
		pchar.GenQuest.TakePassenger.Money = ((hrand(5) + hrand(6) + 4) * 2200) + (sti(pchar.rank) * 500);
		string sText = SelectPassText();
		dialog.text = "Por supuesto. Estoy hablando de un sinvergüenza llamado " + pchar.GenQuest.TakePassenger.Name + ". " + sText + "  Lo había estado buscando durante bastante tiempo, y ahora finalmente obtuve información confiable sobre dónde se puede encontrar. Necesito que me traigas a ese hombre, por todos los medios, vivo. Quiero colgarlo en público en la plaza de nuestro pueblo. ¿Estás listo para emprender esta misión?";
		link.l1 = "Estoy listo, " + GetAddress_FormToNPC(NPChar) + ". ¿Dónde puedo encontrar a ese canalla?";
		link.l1.go = "TakePassenger_agree";
		link.l2 = "Mm... No, creo que lo dejaré pasar.";
		link.l2.go = "All_disagree";
		break;

	case "TakePassenger_agree":
		npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
		pchar.GenQuest.TakePassenger.MayorId = npchar.id; // Id мэра, чтобы знать, кто дал квест
		dialog.text = "Justo en " + FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms1) + ", él, como pasajero en un barco llamado '" + pchar.GenQuest.TakePassenger.ShipName + ", zarpará de " + XI_ConvertString("Colony" + pchar.GenQuest.TakePassenger.City + "Gen") + " y ve a " + XI_ConvertString("Colony" + pchar.GenQuest.TakePassenger.CityA + "Acc") + ". Tienes " + FindRussianDaysString(pchar.GenQuest.TakePassenger.Terms) + "  para encontrar este barco en el segmento de ruta especificado, abordarlo y apoderarse de este bastardo. Si sigues esta instrucción, te pagaré " + FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money)) + "¡Buena suerte, capitán!";
		link.l1 = "No perderé más tiempo, " + GetAddress_FormToNPC(NPChar) + "¡Zarparé de inmediato!";
		link.l1.go = "exit";
		SetFunctionTimerCondition("TakePassenger_CreateShip", 0, 0, sti(pchar.GenQuest.TakePassenger.Terms1), false);
		SetTimerCondition("AllMayorsQuests_Late", 0, 0, sti(pchar.GenQuest.TakePassenger.Terms), false);
		ReOpenQuestHeader("MayorsQuestsList");
		AddQuestRecord("MayorsQuestsList", "10");
		AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
		AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.TakePassenger.City + "Gen"));
		AddQuestUserData("MayorsQuestsList", "sCityA", XI_ConvertString("Colony" + pchar.GenQuest.TakePassenger.CityA + "Acc"));
		AddQuestUserData("MayorsQuestsList", "sDay1", FindRussianDaysString(sti(pchar.GenQuest.TakePassenger.Terms1)));
		AddQuestUserData("MayorsQuestsList", "sDay2", FindRussianDaysString(sti(pchar.GenQuest.TakePassenger.Terms)));
		AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.TakePassenger.Money)));
		AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.TakePassenger.Name);
		AddQuestUserData("MayorsQuestsList", "sShipName", pchar.GenQuest.TakePassenger.ShipName);
		break;

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//	Таможенный патруль
	/////////////////////////////////////////////////////////////////////////////////////////////////
	case "CustomPatrol":
		// установка параметров
		pchar.GenQuest.questName = "CustomPatrol";				 // тип квеста
		pchar.GenQuest.CustomPatrol.Nation = sti(npchar.nation); // нация
		pchar.GenQuest.CustomPatrol.Island = Islands[GetCharacterCurrentIsland(PChar)].id;
		pchar.GenQuest.CustomPatrol.LoginDay = rand(4) + 1;
		pchar.GenQuest.CustomPatrol.Loginlocator = rand(3) + 4;
		pchar.GenQuest.CustomPatrol.ShipType = SelectCustomPatrolShipType(FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_UNIVERSAL);
		pchar.GenQuest.CustomPatrol.ShipTypeA = SelectCustomPatrolShipType(FLAG_SHIP_TYPE_RAIDER);
		pchar.GenQuest.CustomPatrol.Cannon = SelectLevelCannonParameter(sti(pchar.GenQuest.CustomPatrol.ShipType));
		pchar.GenQuest.CustomPatrol.Money = ((hrand(5) + hrand(6) + 4) * 1400) + (sti(pchar.rank) * 300);
		dialog.text = "Tengo información confiable de que algún capitán ha arreglado una transacción con contrabandistas sobre la venta de algunos esclavos. Como debe ser, tales transacciones por parte de personas privadas en nuestras colonias se consideran como contrabando\nEl problema consiste en que no sé ni el tiempo exacto, ni la fecha ni el lugar donde se encontrarán los contrabandistas. Solo se sabe que la transacción criminal se llevará a cabo durante los próximos cinco días en nuestra isla. Para empeorar las cosas, todos mis barcos patrulla están o bien reparándose o involucrados en otras tareas y no pueden encontrar a estos sinvergüenzas\nLe sugiero que se encargue de esta tarea: rastrear a los contrabandistas y tratar con ellos con los métodos más radicales, hacer de ellos un ejemplo. ¿Está listo para llevar a cabo esta misión?";
		link.l1 = "Estoy listo, " + GetAddress_FormToNPC(NPChar) + ". Dime, ¿tienes alguna información adicional? ¿Como el nombre del capitán, el nombre o el tipo de su barco?";
		link.l1.go = "CustomPatrol_agree";
		link.l2 = "Mm... No, creo que pasaré.";
		link.l2.go = "All_disagree";
		break;

	case "CustomPatrol_agree":
		npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
		pchar.GenQuest.CustomPatrol.MayorId = npchar.id; // Id мэра, чтобы знать, кто дал квест
		dialog.text = "Mi fuente acaba de decirme que se está preparando un trato y se completará. Eso es todo. Así que solo observa más de cerca todos los barcos sospechosos dentro de nuestras aguas. Si tienes éxito, te pagaré una suma de " + FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money)) + "\nAdemás, dadas las circunstancias, te autorizo a recoger toda la carga de contrabando que puedas encontrar. Extraoficialmente, por supuesto, siempre y cuando no la vendas en nuestra ciudad.";
		link.l1 = "Bastante generoso. Muy bien, me pondré a patrullar las aguas de vuestra colonia, " + GetAddress_FormToNPC(NPChar) + ".";
		link.l1.go = "exit";
		SetTimerCondition("AllMayorsQuests_Late", 0, 0, 6, false);
		pchar.quest.CustomPatrol.win_condition.l1 = "location";
		pchar.quest.CustomPatrol.win_condition.l1.location = pchar.GenQuest.CustomPatrol.Island;
		pchar.quest.CustomPatrol.win_condition.l2 = "Timer";
		pchar.quest.CustomPatrol.win_condition.l2.date.hour = sti(GetTime() + rand(8));
		pchar.quest.CustomPatrol.win_condition.l2.date.day = GetAddingDataDay(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
		pchar.quest.CustomPatrol.win_condition.l2.date.month = GetAddingDataMonth(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
		pchar.quest.CustomPatrol.win_condition.l2.date.year = GetAddingDataYear(0, 0, sti(pchar.GenQuest.CustomPatrol.LoginDay));
		pchar.quest.CustomPatrol.function = "CustomPatrol_CreateShip";
		ReOpenQuestHeader("MayorsQuestsList");
		AddQuestRecord("MayorsQuestsList", "11");
		AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
		AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.CustomPatrol.Money)));
		break;

	/////////////////////////////////////////////////////////////////////////////////////////////////
	//	Найти дезертира
	/////////////////////////////////////////////////////////////////////////////////////////////////
	case "FindFugitive":
		// установка параметров
		pchar.GenQuest.questName = "FindFugitive"; // тип квеста
		pchar.GenQuest.FindFugitive.Startcity = npchar.city;
		pchar.GenQuest.FindFugitive.City = SelectFugitiveCity();
		pchar.GenQuest.FindFugitive.Chance = rand(2);
		pchar.GenQuest.FindFugitive.Name = GenerateRandomName(sti(npchar.Nation), "man");
		pchar.GenQuest.FindFugitive.Money = ((hrand(5) + hrand(6) + 4) * 2600) + (sti(pchar.rank) * 600);
		sText = SelectFugitiveText();
		log_testinfo(pchar.GenQuest.FindFugitive.City);
		log_testinfo(FindRussianDaysString(sti(pchar.GenQuest.FindFugitive.Chance)));
		dialog.text = "Te contaré todo en detalle. Ha ocurrido una historia muy fea, " + sText + ". Al entrevistar a sus colegas y amigos, creemos, no sin razón, que el desertor se refugió entre los piratas en uno de sus asentamientos\nTe sugiero visitar el nido de piratas, encontrar al fugitivo, arrestarlo y traerlo aquí. La deserción es un delito grave y no puede quedar impune. ¿Estás listo para aceptar esta misión?";
		link.l1 = "Estoy listo, " + GetAddress_FormToNPC(NPChar) + "¿Puedes decirme el nombre del desertor?";
		link.l1.go = "FindFugitive_agree";
		link.l2 = "Hmm... No, creo que pasaré.";
		link.l2.go = "All_disagree";
		break;

	case "FindFugitive_agree":
		npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
		pchar.GenQuest.FindFugitive.MayorId = npchar.id; // Id мэра, чтобы знать, кто дал квест
		dialog.text = "Sí, por supuesto. Su nombre es " + pchar.GenQuest.FindFugitive.Name + ". Dudo mucho que lleve su uniforme, así que echa un vistazo más de cerca a todo tipo de escoria. Te doy un mes para la búsqueda, porque, me temo, no tendría sentido buscarlo después de eso. Si tienes éxito, te pagaré una suma de " + FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money)) + ".";
		link.l1 = "No perderé más tiempo, " + GetAddress_FormToNPC(NPChar) + "¡Zarparé de inmediato!";
		link.l1.go = "exit";
		SetTimerCondition("AllMayorsQuests_Late", 0, 0, 30, false);
		ReOpenQuestHeader("MayorsQuestsList");
		AddQuestRecord("MayorsQuestsList", "12");
		AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
		AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.FindFugitive.Money)));
		AddQuestUserData("MayorsQuestsList", "sName", pchar.GenQuest.FindFugitive.Name);
		// создаем дезертира
		sld = GetCharacter(NPC_GenerateCharacter("Fugitive", "citiz_" + (21 + rand(9)), "man", "man", sti(pchar.rank) + MOD_SKILL_ENEMY_RATE, sti(npchar.nation), 30, true, "soldier"));
		SetFantomParamFromRank(sld, sti(pchar.rank) + MOD_SKILL_ENEMY_RATE, true);
		sld.name = pchar.GenQuest.FindFugitive.Name;
		sld.lastname = "";
		sld.dialog.FileName = "MayorQuests_dialog.c";
		sld.greeting = "marginal";
		break;
	/////////////////////////////////////////////////////////////////////////////////////////////////
	//	Проникновение во враждебный город
	/////////////////////////////////////////////////////////////////////////////////////////////////
	case "Intelligence":
		dialog.text = "Ya veo. Quizás, una recompensa de " + FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money)) + " será un buen incentivo para ti.";
		link.l1 = "Sí, es un buen dinero... Aceptaré esta misión.";
		link.l1.go = "Intelligence_agree";
		link.l2 = "Hum... No, creo que rechazaré. Es demasiado peligroso.";
		link.l2.go = "All_disagree";
		break;
	case "Intelligence_agree":
		if (pchar.GenQuest.Intelligence.City == "none" || isBadReputation(pchar, 30)) // на всякий случай
		{
			dialog.text = "Aunque, no puedo decir que confíe completamente en ti... Creo que no te daré esta misión.";
			link.l1 = "Oh, bueno... Es una lástima, pero no hay nada que pueda hacer.";
			link.l1.go = "exit";
			DeleteAttribute(pchar, "GenQuest." + pchar.GenQuest.questName);
		}
		else
		{
			npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_complete";
			pchar.GenQuest.questName = "Intelligence"; // тип квеста
			sTemp = pchar.GenQuest.Intelligence.City;
			switch (rand(4))
			{
			case 0:
				sTemp += "_Priest";
				break;
			case 1:
				sTemp += "_trader";
				break;
			case 2:
				sTemp += "_shipyarder";
				break;
			case 3:
				sTemp += "_usurer";
				break;
			case 4:
				sTemp += "_PortMan";
				break;
			}
			pchar.GenQuest.Intelligence.SpyId = sTemp; // Id нашего шпиона в городе
			dialog.text = "¡Estupendo! Ahora, al grano. En " + XI_ConvertString("Colony" + pchar.GenQuest.Intelligence.City + "Dat") + " necesitas encontrar a un lugareño " + GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)], "Gen") + ", su nombre es " + GetFullName(&characters[GetCharacterIndex(sTemp)]) + ". Le dirás mi nombre y él te dará un paquete de documentos. Por entregar este paquete en mis manos te doy " + FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms)) + " Y ten en cuenta que todo tiene que hacerse en secreto. Si tu tapadera se descubre, el agente no arriesgará intentar hacer contacto. ¿Está claro?";
			link.l1 = "Sí, lo tengo, " + GetAddress_FormToNPC(NPChar) + "Empezaré de inmediato.";
			link.l1.go = "exit";
			pchar.GenQuest.Intelligence.MayorId = npchar.id;	// Id мэра, чтобы знать, кто дал квест
			SaveCurrentQuestDateParam("GenQuest.Intelligence"); // запись даты получения квеста
			ReOpenQuestHeader("MayorsQuestsList");
			AddQuestRecord("MayorsQuestsList", "6");
			AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
			AddQuestUserData("MayorsQuestsList", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Intelligence.City + "Acc"));
			AddQuestUserData("MayorsQuestsList", "sIsland", XI_ConvertString(colonies[FindColony(pchar.GenQuest.Intelligence.City)].islandLable + "Dat"));
			AddQuestUserData("MayorsQuestsList", "sWho", GetWorkTypeOfMan(&characters[GetCharacterIndex(sTemp)], "Gen"));
			AddQuestUserData("MayorsQuestsList", "SpyName", GetFullName(&characters[GetCharacterIndex(sTemp)]));
			AddQuestUserData("MayorsQuestsList", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Intelligence.Terms)));
			AddQuestUserData("MayorsQuestsList", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Intelligence.Money)));
			AddQuestUserData("MayorsQuestsList", "sCity2", XI_ConvertString("Colony" + pchar.GenQuest.Intelligence.City + "Dat"));
		}
		break;
	case "Intelligence_ExecuteLate":
		QuestName = pchar.GenQuest.questName;
			pchar.GenQuest.(QuestName).Money = sti(pchar.GenQuest.(QuestName).Money) / 2);
			dialog.text = RandPhraseSimple("No está mal. Pero no cumpliste con el plazo, y por lo tanto tengo que reducir un poco tu recompensa. Ahora tu pago será " + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money)) + " Aquí tienes.", "Eso es bueno. Pero no cumpliste con el plazo, y he estado esperando estas cartas. Has arruinado mis planes, y por lo tanto me veo obligado a reducir un poco tu recompensa. Aun así, me complace entregarte la recompensa que te corresponde, " + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money)) + "  Aquí tienes. ");
			link.l1 = "No diría que me agrada, pero al final, los plazos fueron realmente violados. Así que no tengo quejas, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "All_Execute_1";
			//--> слухи
			AddSimpleRumour(RandPhraseSimple("Sabe que el gobernador " + GetFullName(npchar) + " no está muy contento con la rapidez del capitán " + GetMainCharacterNameGen() + ".",
											 "El gobernador " + GetFullName(npchar) + " no está muy contento con el capitán " + GetMainCharacterNameDat() + ", " + GetSexPhrase("que", "que") + " cumplió sus órdenes, pero no lo hizo a su debido tiempo..."),
							sti(npchar.nation), 5, 1);
			//<-- слухи
			break;

	// -------------- общий набор для всех квестов мэра ------------------
	case "All_disagree":
		dialog.text = "¡Me estás decepcionando!";
		link.l1 = "Lo siento, " + GetAddress_FormToNPC(NPChar) + ", pero no puedo aceptar este trabajo.";
		link.l1.go = "exit";
		ChangeCharacterComplexReputation(pchar, "nobility", -2);

		if (CheckAttribute(pchar, "GenQuest.questName"))
		{
			QuestName = pchar.GenQuest.questName;
			DeleteAttribute(pchar, "GenQuest." + QuestName);
			DeleteAttribute(pchar, "GenQuest.questName");
		}
		break;
	case "All_Late":
		QuestName = pchar.GenQuest.questName;
		dialog.text = RandPhraseSimple("Bueno, muy mal, qué más puedo decir. Contaba contigo y resulta que solo he perdido mi tiempo. Estoy decepcionado.", "Bueno, debo decir que estoy totalmente decepcionado de ti... Hay mucha gente en mi residencia siempre lista para hacer tales recados para mí, y he perdido mi tiempo contigo. En fin...");
		link.l1 = "Lo siento, " + GetAddress_FormToNPC(NPChar) + ", hice todo lo que pude.";
		link.l1.go = "exit";
		//--> слухи
		AddSimpleRumour(LinkRandPhrase("Sabe que el gobernador " + GetFullName(npchar) + " está muy disgustado con el capitán " + GetMainCharacterNameDat() + ". ¡Te lo imaginas, no cumplió su misión a tiempo!",
									   "El Gobernador " + GetFullName(npchar) + " le molesta un poco que el capitán " + GetFullName(pchar) + " arrimara el hombro, pero que no cumpliera su misión a tiempo. Es una lástima...",
									   "He oído que el gobernador " + GetFullName(npchar) + " está muy disgustado con usted, capitán " + GetFullName(pchar) + ", ya que no cumpliste el plazo al intentar cumplir su encargo."),
						sti(npchar.nation), 5, 1);
		//<-- слухи
		ChangeCharacterComplexReputation(pchar, "nobility", -4);
		ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
		DeleteAttribute(pchar, "GenQuest." + QuestName);
		DeleteAttribute(pchar, "GenQuest.questName");
		npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; // реплику вертаем
		SaveCurrentNpcQuestDateParam(npchar, "work_date");					   // сразу еще один не даем
		CloseQuestHeader("MayorsQuestsList");
		break;
	case "All_Found":
		QuestName = pchar.GenQuest.questName;
		dialog.text = RandPhraseSimple("¡Estoy simplemente asombrado! Has logrado localizar tu objetivo, pero no te importaron los medios para asegurar tu superioridad: eso es una imprudencia extrema. ¡Estoy decepcionado!", "Bueno, debo decir que estoy decepcionado contigo... Encontrar tu objetivo no es suficiente, debes tener los medios para destruirlo. Hay muchos matones en mi residencia siempre listos para hacer tales recados por mí. ¿En qué estaba pensando cuando acudí a ti?");
		link.l1 = "Lo siento, " + GetAddress_FormToNPC(NPChar) + ", pero simplemente no estoy dispuesto a arriesgar imprudentemente mi propia vida.";
		link.l1.go = "exit";
		//--> слухи
		AddSimpleRumour(LinkRandPhrase("Sabes que el gobernador " + GetFullName(npchar) + " está muy disgustado con el capitán " + GetMainCharacterNameDat() + ". ¡Te lo imaginas, " + GetSexPhrase("resultó ser un auténtico cobarde.", "resultó ser una auténtica cobarde.") + "!",
									   "Governor " + GetFullName(npchar) + " le molesta un poco que el capitán " + GetFullName(pchar) + " aceptó el trabajo, pero no lo llevó a cabo por su propia indecisión. Hee-hee, ¡cómo son los capitanes!",
									   "He oído que el Gobernador " + GetFullName(npchar) + " está muy disgustado con usted, Capitán " + GetFullName(pchar) + ". Dicen que no eres más que un cobarde" + GetSexPhrase("", "") + "..."),
						sti(npchar.nation), 5, 1);
		//<-- слухи
		ChangeCharacterComplexReputation(pchar, "nobility", -6);
		ChangeCharacterNationReputation(pchar, sti(NPChar.nation), -1);
		DeleteAttribute(pchar, "GenQuest." + QuestName);
		DeleteAttribute(pchar, "GenQuest.questName");
		npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; // реплику вертаем
		SaveCurrentNpcQuestDateParam(npchar, "work_date");					   // сразу еще один не даем
		CloseQuestHeader("MayorsQuestsList");
		AddQuestRecord("MayorsQuestsList", "21");
		AddQuestUserData("MayorsQuestsList", "ColonyName", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData("MayorsQuestsList", "MayorName", GetFullName(npchar));
		break;
	case "All_Execute":
		QuestName = pchar.GenQuest.questName;
		dialog.text = RandPhraseSimple("¡Excelentes noticias! Bueno, es hora de resumirlo todo. Tu tarifa será " + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money)) + " Aquí tienes.", "¡Excelente! Este camino es el mejor para todos... Bueno, estoy feliz de entregarte tu merecida recompensa, " + FindRussianMoneyString(sti(pchar.GenQuest.(QuestName).Money)) + " Aquí tienes.");
		link.l1 = "Gracias, " + GetAddress_FormToNPC(NPChar) + ", " + RandPhraseSimple("¡un placer hacer negocios contigo!", "Me sorprende gratamente la claridad de los asentamientos.");
		link.l1.go = "All_Execute_1";
		//--> слухи
		AddSimpleRumour(LinkRandPhrase("Sabes que el gobernador " + GetFullName(npchar) + ",  elogiaba la diligencia" + GetSexPhrase("de un capitán", "una joven señorita") + " " + GetMainCharacterNameGen() + ".",
									   "El Gobernador " + GetFullName(npchar) + " está alabando al capitán " + GetMainCharacterNameGen() + ", " + GetSexPhrase("éle", "ella") + " siempre es impecable cuando se trata de realizar las tareas de gobernador. Es una persona insustituible para el gobernador, eso digo yo...",
									   "He oído que el gobernador " + GetFullName(npchar) + " está muy contento con usted, capitán " + GetFullName(pchar) + ". Le define como un oficial muy cuidadoso y minucioso. Es muy agradable oír eso, capitán..."),
						sti(npchar.nation), 5, 1);
		//<-- слухи
		break;
	case "All_Execute_1":
		QuestName = pchar.GenQuest.questName;
		dialog.text = RandPhraseSimple("Muy bien. Puedes venir a verme de nuevo; quizás encuentre otro trabajo para ti.", "¡Bueno, genial! Supongo que volveré a ofrecerte tales trabajos.");
		link.l1 = RandPhraseSimple("Estupendo.", "Bien.");
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, sti(pchar.GenQuest.(QuestName).Money));
		CloseQuestHeader("MayorsQuestsList");
		ChangeCharacterComplexReputation(pchar, "nobility", 4);
		ChangeCharacterNationReputation(pchar, sti(NPChar.nation), 1);
		AddCharacterExpToSkill(PChar, "Leadership", 180);
		OfficersReaction("good"); // dlc

		DeleteAttribute(pchar, "GenQuest." + QuestName);
		DeleteAttribute(pchar, "GenQuest.questName");
		npchar.greeting = NationShortName(sti(npchar.nation)) + "_gov_common"; // реплику вертаем
		SaveCurrentNpcQuestDateParam(npchar, "work_date");					   // сразу еще один не даем
		// инкремент в базу заданий мэров
		sTemp = npchar.City;
		if (!CheckAttribute(pchar, "GenQuest.MayorQuestsList." + sTemp))
			pchar.GenQuest.MayorQuestsList.(sTemp) = 0;
		pchar.GenQuest.MayorQuestsList.(sTemp) = sti(pchar.GenQuest.MayorQuestsList.(sTemp)) + 1;
		break;
		//<-- осады homo
	case "siege_task":
		makearef(aData, NullCharacter.Siege);
		aData.HelpColony = true;
		dialog.text = "En estos tiempos terribles, cualquier ayuda sería muy bienvenida. Aceptamos tu ayuda, si nos ayudas a defender nuestra colonia serás recompensado.";
		link.l1 = "Entonces no perdamos tiempo.";
		link.l1.go = "exit";
		break;

	// Jason --> Бремя гасконца
	case "Sharlie":
		dialog.text = "¿Estás buscando a Michel de Monper? Interesante... ¿Y para qué lo necesitas?";
		link.l1 = "Soy su hermano. Mi padre me dijo que Michel está en problemas y necesita ayuda, así que yo...";
		link.l1.go = "Sharlie_1";
		break;

	case "Sharlie_1":
		sld = characterFromId("Benua");
		sld.dialog.currentnode = "First time";
		DelLandQuestMark(sld);
		dialog.text = "¿Ah, sí? No recuerdo que el señor de Monper tuviera hermanos... Sabéis, monsieur, me parecéis muy sospechoso... así que os arresto para una investigación más a fondo. ¡Teniente! ¡Detened a este hombre!";
		link.l1 = "¡Pero su señoría!";
		link.l1.go = "exit";
		if (GetCharacterIndex("SharlieKnown") != -1)
		{
			sld = characterFromId("SharlieKnown");
			sld.lifeday = 0;
		}
		AddDialogExitQuestFunction("Sharlie_enterSoldiers");
		LAi_CharacterDisableDialog(npchar);
		break;

	case "Sharlie_2":
		QuestPointerDelLoc("Fortfrance_town", "reload", "reload3_back");
		dialog.text = "Y aún así me gustaría enmendarlo. Aquí, por favor, toma esta espada, esta pistola y esta armadura ligera, es mi regalo para ti. Creo que encontrarás estas cosas bastante útiles.";
		link.l1 = "Gracias, monsieur. Teniendo en cuenta que tus guardias se llevaron todo lo que poseo, esto será muy útil.";
		// belamour legendary edition -->
		link.l1.go = "Sharlie_5";
		link.l2 = "Gracias, señor. ¿Hay alguna otra manera en que puedas ayudarme? ¿De caballero a caballero? ¡Puedes ver por ti mismo en qué terrible situación me encuentro!";
		link.l2.go = "Sharlie_3";
		break;

	case "Sharlie_3":
		dialog.text = "Bueno, Charles... (hurgando en el escritorio) Aquí, guarda este amuleto sagrado para la buena suerte. No puedo ayudar más, lo siento. Aquí en las colonias tendrás que confiar solo en ti mismo.";
		link.l1 = "Bueno, al menos algo. Gracias por el regalo, señor.";
		link.l1.go = "Sharlie_4";
		break;

	case "Sharlie_4":
		DialogExit();
		ChangeCharacterComplexReputation(pchar, "nobility", -1);
		AddCharacterExpToSkill(pchar, "Commerce", 10);
		Log_Info("Ha recibido material");
		Log_Info("Has recibido el amuleto Agua bendita");
		PlaySound("interface\important_item.wav");
		GiveItem2Character(pchar, "amulet_7");
		TakeNItems(pchar, "blade_08", 1);
		if(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "")
		{
			EquipCharacterbyItem(pchar, "blade_08");
		}
		TakeNItems(pchar, "pistol1", 1);
		TakeNItems(pchar, "cirass5", 1);
		pchar.quest.Sharlie_PardonOver.over = "yes";
		DeleteAttribute(pchar, "questTemp.Sharlie.Pardon");
		if (!CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
		{
			DelLandQuestMark(npchar);
		}
		if (CheckAttribute(pchar, "systeminfo.tutorial.Amulet"))
		{
			DoQuestFunctionDelay("Tutorial_Amulet", 0.1);
		}
		break;

	case "Sharlie_5":
		// <-- legendary edition
		DialogExit();
		ChangeCharacterComplexReputation(pchar, "nobility", 1);
		AddCharacterExpToSkill(pchar, "Leadership", 10);
		Log_Info("Ha recibido material");
		PlaySound("interface\important_item.wav");
		TakeNItems(pchar, "blade_08", 1);
		if(GetCharacterEquipByGroup(pchar, BLADE_ITEM_TYPE) == "")
		{
			EquipCharacterbyItem(pchar, "blade_08");
		}
		TakeNItems(pchar, "pistol1", 1);
		TakeNItems(pchar, "cirass5", 1);
		pchar.quest.Sharlie_PardonOver.over = "yes";
		DeleteAttribute(pchar, "questTemp.Sharlie.Pardon");
		if (!CheckAttribute(pchar, "questTemp.Sharlie.Junglejew"))
		{
			DelLandQuestMark(npchar);
		}
		break;
	//<-- Бремя гасконца

	// Sinistra --> Травля крысы
	case "TK_TravlyaKrys":
		dialog.text = "Vaya giro del destino, Charles... No es común ver a alguien ascender tan rápido en nuestro mundo. Tengo el presentimiento de que tú y yo nos llevaremos muy bien.";
		link.l1 = "Me sentiría honrado. ¿Quizás tiene una tarea para mí?";
		link.l1.go = "TK_TravlyaKrys_2";
		DeleteAttribute(pchar, "questTemp.TK_TravlyaKrys");
		PChar.quest.TK_Timer.over = "yes";
		break;

	case "TK_TravlyaKrys_2":
		dialog.text = "¡Absolutamente! Especialmente después de tu exitoso enfrentamiento con uno de los piratas de Barbazón cerca de Le Francois...";
		link.l1 = "No puedo decir que tenga buenos recuerdos de ese encuentro. ¿Quién es exactamente Barbazon?";
		link.l1.go = "TK_TravlyaKrys_3";
		break;

	case "TK_TravlyaKrys_3":
		dialog.text = "Jacques Barbazon, también conocido como Jacques el Bueno, lidera el nido de bandidos en Le François. Es uno de los llamados barones piratas, causando problemas con la piratería y el contrabando en las Antillas Menores. Es un criminal notorio, y te lo aseguro, ¡un día encontrará su fin en la horca en Saint-Pierre!";
		link.l1 = "Disculpe, ¿pero no es usted la verdadera autoridad en Martinica? ¿No puede simplemente eliminar ese nido? He estado allí, y créame, no es gran cosa.";
		link.l1.go = "TK_TravlyaKrys_4";
		break;

	case "TK_TravlyaKrys_4":
		dialog.text = "Te aconsejaría que no presumas de tu conocimiento de los lugares menos agradables de mi isla, Charles. No es propio de un noble. En cuanto a tu pregunta\nNo todo en nuestro mundo se puede resolver con fuerza bruta. Hay políticas e intereses comerciales en juego. Pero no entremos en detalles innecesarios: tengo una tarea específica que requiere algo de fuerza bruta.";
		link.l1 = "Por favor, continúa.";
		link.l1.go = "TK_TravlyaKrys_5";
		break;

	case "TK_TravlyaKrys_5":
		dialog.text = "Barbazon atrae a tripulaciones de poca monta, hambrientas de oro fácil. A veces les lanza un hueso solo para ver cómo se pelean por él. De vez en cuando pone al superviviente a trabajar, pero más a menudo los expulsa, y créeme, no hay nada más peligroso que un pirata desesperado vagando por ahí.";
		link.l1 = "Creo que entiendo, pero no estoy seguro de estar a la altura. Apenas he tomado el mando de mi barco, y todavía estoy aprendiendo el oficio, por así decirlo...";
		link.l1.go = "TK_TravlyaKrys_6";
		break;

	case "TK_TravlyaKrys_6":
		dialog.text = "¡Tonterías! Ya has probado la victoria, más que la mayoría de los holgazanes entre mis oficiales. La ciudad te recompensará con cinco mil pesos por hundir a otro de los ratas de Barbazon, libre de impuestos. Ocho mil si traes al pirata con vida, para una ejecución adecuada, por supuesto.";
		link.l1 = "Sin duda, podría usar el dinero. ¿Dónde puedo encontrar a este pirata?";
		link.l1.go = "TK_TravlyaKrys_7";
		link.l2 = "Lo siento, pero no creo que esté listo para este tipo de tarea todavía.";
		link.l2.go = "TK_TravlyaKrys_Otkaz";
		break;

	case "TK_TravlyaKrys_Otkaz":
		dialog.text = "Es una pena, Charles. En ese caso, no te retendré más tiempo.";
		link.l1 = "Adiós, Su Excelencia.";
		link.l1.go = "exit";
		break;

	case "TK_TravlyaKrys_7":
		dialog.text = "Me alegra que estés a bordo, Charles. Nuestros informes de inteligencia indican que el Hater, un lanchón, está actualmente preparándose para partir de Le Francois. No podemos permitirnos demorar, así que zarpa y ataca. No te preocupes, amigo mío, tendrás éxito.";
		link.l1 = "Con la gracia de Dios, Su Excelencia.";
		link.l1.go = "TK_TravlyaKrys_8";
		break;

	case "TK_TravlyaKrys_8":
		DialogExit();
		SetQuestHeader("TravlyaKrys");
		AddQuestRecord("TravlyaKrys", "1");

		sld = GetCharacter(NPC_GenerateCharacter("TK_Heiter", "mercen_8", "man", "man", sti(PChar.rank), PIRATE, -1, true, "pirate"));
		sld.name = "Daniel";
		sld.lastname = "Montbars";
		FantomMakeSmallSailor(sld, SHIP_LUGGER, "Hater", CANNON_TYPE_CANNON_LBS3, 20, 40, 20, 25, 35);
		SetCharacterGoods(sld, GOOD_GOLD, 1);
		sld.AlwaysEnemy = true;
		sld.AlwaysSandbankManeuver = true;
		sld.DontRansackCaptain = true;

		Group_FindOrCreateGroup("HeiterAttack");
		Group_SetType("HeiterAttack", "pirate");
		Group_AddCharacter("HeiterAttack", "TK_Heiter");

		Group_SetGroupCommander("HeiterAttack", "TK_Heiter");
		Group_SetTaskAttack("HeiterAttack", PLAYER_GROUP);
		Group_SetAddress("HeiterAttack", "Martinique", "Quest_Ships", "Quest_Ship_6");
		Group_LockTask("HeiterAttack");

		PChar.quest.TK_Potopil.win_condition.l1 = "Character_sink";
		PChar.quest.TK_Potopil.win_condition.l1.character = "TK_Heiter";
		PChar.quest.TK_Potopil.win_condition = "TK_Potopil";
		break;
	//<-- Травля крысы

	// Jason --> Португалец
	case "Portugal":
		dialog.text = "¡Claro que puedes, capitán! Por eso te molesté.";
		link.l1 = "Entonces, soy todo oídos.";
		link.l1.go = "Portugal_1";
		break;

	case "Portugal_1":
		dialog.text = "Los pescadores locales vieron una embarcación extraña cerca de la isla anoche. Según dicen, era un enorme buque de guerra, como un navío de línea, sin ninguna bandera ni faroles de señales. No creo que este barco pueda ser realmente más grande que una fragata, ¡pero incluso eso ya sería demasiado!";
		link.l1 = "El miedo convierte los montículos en montañas, eso es seguro... pero ¿cuál es el sentido?";
		link.l1.go = "Portugal_2";
		break;

	case "Portugal_2":
		dialog.text = "Solo recurro a usted, capitán. Mis socios comerciales están asustados por estos rumores; creen que se trata de piratas o corsarios españoles, y eso es malo para el comercio. Peor que todo lo demás: actualmente no hay buques de guerra en la colonia, solo un par de balandras para protección y una vieja goleta, adecuada para cazar contrabandistas.\nNo puedo dejarlo sin vigilancia... De todos modos, ¡ahora que el rumor sobre el barco misterioso es conocido por la mitad de la ciudad! Por favor, únase con su barco para ayudarnos a encontrarlo; le conozco como un capitán decente, e incluso si realmente solo es una fragata, sus cañones pueden convencerla de buscar presa en otro lugar.";
		link.l1 = "Monsieur... En realidad, tenía otros planes...";
		link.l1.go = "Portugal_3";
		break;

	case "Portugal_3":
		dialog.text = "¡Por favor, capitán! Solo por un par de días, ¡hasta que estos incómodos rumores se calmen! Y se le pagará por su tiempo, por supuesto. ¿Le convendrán 10,000 piezas de a ocho?";
		link.l1 = "Mm... pero, su Excelencia, yo...";
		link.l1.go = "Portugal_4";
		break;

	case "Portugal_4":
		dialog.text = "¡Y la doblaremos si realmente entras en combate con este barco, y la triplicaremos si lo hundes! Ahora, ¿qué dices?";
		link.l1 = "Está bien, planeaba quedarme aquí un par de días de todos modos.";
		link.l1.go = "Portugal_5";
		break;

	case "Portugal_5":
		dialog.text = "¡Excelente, nunca dudé de ti, monsieur capitán! Recuerda, solo dos días en nuestras aguas y el dinero es tuyo. Y si te ves obligado a entrar en batalla, se te pagará según el resultado.";
		link.l1 = "Lo tengo, su Excelencia. Tenemos un trato, y ahora regreso a mi barco.";
		link.l1.go = "Portugal_6";
		break;

	case "Portugal_6":
		dialog.text = "¡Estaré esperando tu regreso, capitán!";
		link.l1 = "Permítame retirarme.";
		link.l1.go = "Portugal_7";
		break;

	case "Portugal_7":
		DialogExit();
		AddQuestRecord("Portugal", "10");
		NextDiag.CurrentNode = "Portugal_8";
		LocatorReloadEnterDisable("Fortfrance_town", "reload1_back", false);
		LocatorReloadEnterDisable("Fortfrance_town", "reload2_back", false);
		LocatorReloadEnterDisable("Fortfrance_town", "gate_back", false); // открыть выходы из города
		bDisableFastReload = true;										  // закрыть быстрый переход
		pchar.GenQuest.CannotWait = true;								  // запрет ожидания
		pchar.quest.Portugal_Seapatrol.win_condition.l1 = "location";
		pchar.quest.Portugal_Seapatrol.win_condition.l1.location = "Martinique";
		pchar.quest.Portugal_Seapatrol.function = "PortugalSeapatrolGo";
		pchar.quest.Portugal_SeapatrolAvendel.win_condition.l1 = "location";
		pchar.quest.Portugal_SeapatrolAvendel.win_condition.l1.location = "Fortfrance_town";
		pchar.quest.Portugal_SeapatrolAvendel.function = "AvendelSpeach";
		break;

	case "Portugal_8":
		dialog.text = "¡Capitán, creo que teníamos un trato para que patrullara nuestras aguas costeras durante dos días!";
		link.l1 = "Sí, por supuesto. Lo recuerdo.";
		link.l1.go = "exit";
		NextDiag.TempNode = "Portugal_8";
		break;

	case "Portugal_9":
		dialog.text = "Bien, has cumplido con tu parte del trato. Aquí está tu recompensa: 10,000 pesos, como acordamos.";
		link.l1 = "¡Gracias! Como puedes ver, tus aprensiones eran infundadas. ¡Buena suerte para ti!";
		link.l1.go = "Portugal_10";
		break;

	case "Portugal_10":
		DialogExit();
		AddMoneyToCharacter(pchar, 10000);
		NextDiag.CurrentNode = "First time";
		pchar.quest.MartiniqueGovernorOver.over = "yes"; // снять таймер
		break;
	//<-- Португалец

	// Warship, 16.05.11. Генер "Правосудие на продажу".
	case "JusticeOnSale_1":
		dialog.text = "Oh " + GetAddress_Form(NPChar) + ", ¡me has sorprendido! ¿Esos sinvergüenzas realmente se han vuelto tan insolentes? ¡Debo notificar al comandante de inmediato y enviar una patrulla costera allí!";
		link.l1 = "Me alegró ayudar. ¿Puedo retirarme ahora?";
		link.l1.go = "JusticeOnSale_2";

		DeleteAttribute(PChar, "GenQuest.JusticeOnSale.MayorWait");
		DeleteAttribute(PChar, "GenQuest.JusticeOnSale.PrisonWait");

		DeleteQuestCondition("JusticeOnSale_MapEnter");
		break;

	case "JusticeOnSale_2":
		dialog.text = "Por supuesto, capitán. Aquí, por favor, acepte esta modesta recompensa personalmente de mi parte.";
		link.l1 = "Gracias.";
		link.l1.go = "JusticeOnSale_3";
		break;

	case "JusticeOnSale_3":
		AddQuestRecord("JusticeOnSale", "5");
		CloseQuestHeader("JusticeOnSale");

		AddMoneyToCharacter(PChar, 1000 + sti(PChar.rank) * 30 * hrand(10));

		DeleteAttribute(PChar, "GenQuest.JusticeOnSale");

		DialogExit();
		break;

	case "JusticeOnSale_4":
		dialog.text = "¡Tienes razón, capitán! ¡No podemos dejarlo así! Te pediría que te dirigieras a " + XI_ConvertString(PChar.GenQuest.JusticeOnSale.ShoreId + "Dat") + ", ¡encuentra su barco y arresta a toda su banda! Si se resisten, usa la fuerza y no dudes en hacerlo!";
		link.l1 = "Permítame retirarme.";
		link.l1.go = "JusticeOnSale_5";
		break;

	case "JusticeOnSale_5":
		dialog.text = "Ahora ve. Navega hasta allí y asegúrate de que nadie escape de la justicia. Creo que primero necesitarás desembarcar en la orilla, y luego podrás encargarte del barco.";
		link.l1 = "...";
		link.l1.go = "JusticeOnSale_6";
		break;

	case "JusticeOnSale_6":
		sld = GetCharacter(NPC_GenerateCharacter("JusticeOnSale_ShipPirate", "", "man", "man", sti(PChar.rank) + 5, PIRATE, -1, true, "quest"));
		sld.Ship.Type = GenerateShipExt(sti(PChar.GenQuest.JusticeOnSale.ShipType), true, sld);
		sld.Ship.Name = PChar.GenQuest.JusticeOnSale.ShipName;
		SetBaseShipData(sld);
		SetCrewQuantityFull(sld);
		Fantom_SetCannons(sld, "pirate");
		Fantom_SetBalls(sld, "pirate");
		Fantom_SetUpgrade(sld, "pirate");
		SetCaptanModelByEncType(sld, "pirate");
		SetRandGeraldSail(sld, PIRATE);

		Character_SetAbordageEnable(sld, false);

		Group_FindOrCreateGroup("JusticeOnSaleGroup");
		Group_AddCharacter("JusticeOnSaleGroup", "JusticeOnSale_ShipPirate");
		Group_SetGroupCommander("JusticeOnSaleGroup", "JusticeOnSale_ShipPirate");
		Group_SetAddress("JusticeOnSaleGroup", PChar.curislandid, "reload", Island_GetLocationReloadLocator(PChar.curislandid, PChar.GenQuest.JusticeOnSale.ShoreId));
		Group_SetTaskNone("JusticeOnSaleGroup");
		Group_LockTask("JusticeOnSaleGroup");

		sld.AlwaysFriend = true;
		SetCharacterRelationBoth(sti(sld.index), GetMainCharacterIndex(), RELATION_FRIEND);

		SetCharacterShipLocation(sld, PChar.GenQuest.JusticeOnSale.ShoreId);

		DeleteAttribute(sld, "SinkTenPercent");
		DeleteAttribute(sld, "SaveItemsForDead");
		DeleteAttribute(sld, "DontClearDead");
		DeleteAttribute(sld, "AboardToFinalDeck");

		sld.AlwaysSandbankManeuver = true;
		sld.AnalizeShips = true;
		sld.DontRansackCaptain = true;

		sld = &Locations[FindLocation(PChar.GenQuest.JusticeOnSale.ShoreId)];
		sld.DisableEncounters = true;

		PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.win_condition.l1 = "location";
		PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.win_condition.l1.location = PChar.GenQuest.JusticeOnSale.ShoreId;
		PChar.Quest.JusticeOnSale_ShoreEnterFromMayor.function = "JusticeOnSale_ShoreEnterFromMayor";

		PChar.Quest.JusticeOnSale_PirateShip_Sink.win_condition.l1 = "Character_sink";
		PChar.Quest.JusticeOnSale_PirateShip_Sink.win_condition.l1.character = "JusticeOnSale_ShipPirate";
		PChar.Quest.JusticeOnSale_PirateShip_Sink.function = "JusticeOnSale_PirateShip_Sink";

		DialogExit();
		break;

	case "JusticeOnSale_7":
		dialog.text = "Gracias por tu ayuda. Esos sinvergüenzas recibieron su merecido. Por favor, permíteme presentarte esta modesta recompensa personalmente de mi parte. Aprecio enormemente el orden y la paz en mi ciudad.";
		link.l1 = "...";
		link.l1.go = "JusticeOnSale_8";
		break;

	case "JusticeOnSale_8":
		AddMoneyToCharacter(PChar, sti(PChar.rank) * 300 + hrand(1000));
		DeleteAttribute(PChar, "GenQuest.JusticeOnSale");
		DialogExit();
		break;
		//<-- Правосудие на продажу

		//--> Jason регата
	case "Regata":
		// belamour legendary edition -->
		if (sti(pchar.rank) < 20)
		{
			notification("Level 20 required", "None");
			dialog.text = "¡Ah, maravilloso, es bueno verte, capitán! He oído hablar de tus talentos, pero ven cuando estés realmente listo.";
			link.l1 = "Sí, claro. Como desees.";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "¡Oh, estupendo, me alegra verte, capitán! Has llegado justo a tiempo: la regata está a punto de empezar en unos días. ¿Has leído las reglas de la regata, que debieron haberte entregado por ordenanza?";
			link.l1 = "Sí, señor, lo hice.";
			link.l1.go = "Regata_1";
			RemoveItems(PChar, "letter_open", 1);					// уберем письмо
			DeleteAttribute(pchar, "questTemp.Regata.ToPortRoyal"); // patch-5
		}
		break;

	case "Regata_1":
		dialog.text = "¿Y has preparado 50000 pesos, tu tarifa de entrada, que contribuirá al dinero del premio?";
		if (makeint(Pchar.money) >= 50000)
		{
			link.l1 = "Sí, por supuesto. Por favor, acepte mi tarifa.";
			link.l1.go = "Regata_2";
		}
		link.l2 = "Estoy un poco corto de dinero en este momento. Pero sin duda reuniré la cantidad requerida.";
		link.l2.go = "Regata_nomoney";
		break;

	case "Regata_2":
		dialog.text = "Muy bien. Si ganas, recuperarás tu dinero cinco veces. Ahora necesitas familiarizarte mejor con las reglas de la regata.\nTodos los detalles los puedes aprender de Sir Henry Stivenson, debería estar en una habitación de la residencia. Ve a él, te lo explicará todo.";
		link.l1 = "Está bien. Haré justo eso.";
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, -50000);
		pchar.quest.Regata_Guber.win_condition.l1 = "location";
		pchar.quest.Regata_Guber.win_condition.l1.location = "Portroyal_Roomtownhall";
		pchar.quest.Regata_Guber.function = "PrepareToRegataInPortroyal";
		pchar.questTemp.Regata.Begin = "true";
		NextDiag.TempNode = "First time";
		break;

	case "Regata_nomoney":
		dialog.text = "Bien, pero por favor, no te demores demasiado, capitán. La regata comienza muy pronto.";
		link.l1 = "Ya veo. Intentaré traerte el dinero tan pronto como pueda.";
		link.l1.go = "exit";
		NextDiag.TempNode = "Regata_1";
		pchar.questTemp.Regata.nomoney = "true";
		break;

	// регата-финал
	case "Regata_Final":
		dialog.text = "¡Ajá! ¡Y aquí tenemos al ganador de la regata! Buen día, Capitán " + GetFullName(pchar) + "¡Permíteme felicitarte por este éxito bien merecido! Los ganadores de la regata siempre han sido populares en las colonias inglesas, y con razón.";
		link.l1 = "¡Gracias, señor!";
		link.l1.go = "Regata_complete";
		break;

	case "Regata_complete":
		dialog.text = "Ahora pasemos a lo más agradable: la ceremonia de recompensas. El premio por el primer lugar es de 250,000 pesos. ¡Felicidades!";
		link.l1 = "¡Gracias!";
		link.l1.go = "Regata_complete_1";
		break;

	case "Regata_complete_1":
		AddMoneyToCharacter(pchar, 250000);
		// belamour legendary edition в регате только один приз -->
		GiveItem2Character(pchar, "blade_26");
		GiveItem2Character(pchar, "cirass4");
		GiveItem2Character(pchar, "bussol");

		dialog.text = "Además, recibirás un conjunto de premios valiosos: la legendaria espada toledana 'Asoleda', un conjunto de armadura milanesa y una brújula fina. Todo tuyo.";
		// <-- legendary edition
		link.l1 = "Me alegra mucho, señor. Realmente, no podría haber esperado tal generosidad.";
		link.l1.go = "Regata_complete_2";
		break;

	case "Regata_complete_2":
		dialog.text = "En nombre de todos los súbditos de las colonias inglesas, te agradezco por participar en la regata y una vez más te felicito por tu victoria. Si hiciste una apuesta, ve a ver a Sir Henry Stevenson y recibe tus ganancias si aún no lo has hecho. ¡Buena suerte para ti, capitán!";
		link.l1 = "¡Gracias por sus amables palabras, señor! A mi vez, permítame agradecerle por brindarme la oportunidad de participar en tan grandioso evento. Ahora, por favor, permítame retirarme.";
		link.l1.go = "Regata_complete_3";
		break;

	case "Regata_complete_3":
		DialogExit();
		NextDiag.CurrentNode = "First time";
		break;
		//<-- регата
	}
}

string GetGangLocation(ref npchar)
{
	int n;
	string island = GetArealByCityName(npchar.city);
	string LocationId, sAreal;
	int storeArray[2];
	SetArraySize(&storeArray, MAX_LOCATIONS);
	int howStore = 0;

	for (n = 0; n < MAX_LOCATIONS; n++)
	{
		if (GiveArealByLocation(&locations[n]) == island)
		{
			//==> на всякий случай
			if (CheckAttribute(&locations[n], "DisableEncounters") && locations[n].DisableEncounters == true)
				continue;
			LocationId = locations[n].id;
			if (findsubstr(LocationId, "jungle", 0) != -1 || findsubstr(LocationId, "Shore", 0) != -1 || findsubstr(LocationId, "CaveEntrance", 0) != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0)
		return "none";
	n = storeArray[hrand(howStore - 1)];
	return locations[n].id;
}

string GetSpyLocation(ref npchar)
{
	aref arCommon, arRld, arRld2;
	int i, n, Qty, Qty2;
	string LocId;
	string storeArray[50];
	int howStore = 0;
	makearef(arRld, Locations[FindLocation(npchar.city + "_town")].reload);
	Qty = GetAttributesNum(arRld);
	if (CheckAttribute(pchar, "questTemp.jailCanMove.Deliver.locationId")) // если взят квест по доставке малявы
	{
		for (i = 0; i < Qty; i++)
		{
			arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
			if (findsubstr(LocId, "Common", 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId)
			{
				storeArray[howStore] = LocId;
				howStore++;
			}
			if (arCommon.label != "Sea")
			{
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n = 0; n < Qty2; n++)
				{
					arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common", 0) != -1 && LocId != pchar.questTemp.jailCanMove.Deliver.locationId && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
					{
						storeArray[howStore] = LocId;
						howStore++;
					}
				}
			}
		}
	}
	else
	{
		for (i = 0; i < Qty; i++)
		{
			arCommon = GetAttributeN(arRld, i);
			LocId = arCommon.go;
			if (findsubstr(LocId, "Common", 0) != -1)
			{
				storeArray[howStore] = LocId;
				howStore++;
			}
			if (arCommon.label != "Sea")
			{
				makearef(arRld2, Locations[FindLocation(LocId)].reload);
				Qty2 = GetAttributesNum(arRld2);
				for (n = 0; n < Qty2; n++)
				{
					arCommon = GetAttributeN(arRld2, n);
					LocId = arCommon.go;
					if (findsubstr(LocId, "Common", 0) != -1 && LocId != "CommonPackhouse_1" && LocId != "CommonPackhouse_2")
					{
						storeArray[howStore] = LocId;
						howStore++;
					}
				}
			}
		}
	}
	if (howStore == 0)
		return "none";
	LocId = storeArray[hrand(howStore - 1)];
	SetOpenDoorCommonLoc(npchar.city, LocId); // открываем дверь
	for (n = 0; n < MAX_CHARACTERS; n++)
	{
		if (CheckAttribute(&characters[n], "locations") && characters[n].locations == LocId)
		{
			characters[n].lifeDay = 0;
		}
	}
	return LocId;
}

string GetSpyColony(ref NPChar)
{
	int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
	int howStore = 0;
	string sChrId;

	for (int n = 0; n < MAX_COLONIES; n++)
	{
		// Rebbebion, чуть изменил функцию, чтобы условно испанцы не просили пробраться к испанцам, французы к французам и т.д
		if (colonies[n].nation != "none" && sti(colonies[n].nation) != PIRATE && GetRelation2BaseNation(sti(colonies[n].nation)) == RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].id != npchar.City && colonies[n].nation != npchar.nation)
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0)
		return "none";
	return colonies[storeArray[Rand(howStore - 1)]].id;
}

int SelectCureerShipType()
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21) iClass = 4 - rand(1);
	
	return GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_RAIDER + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY);
}

int SelectPirateShipType()
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 5;
	if(iRank >= 12 && iRank < 21) iClass = 4;
	if(iRank >= 21 && iRank < 30) iClass = 4 - rand(1);
	if(iRank >= 30) iClass = 2;
	
	return GetRandomShipType(GetClassFlag(iClass), FLAG_SHIP_TYPE_RAIDER + FLAG_SHIP_TYPE_UNIVERSAL + FLAG_SHIP_TYPE_WAR, FLAG_SHIP_NATION_ANY);
}

int SelectCustomPatrolShipType(int iFlagType)
{
	if(CheckAttribute(pchar, "questTemp.StatusCity"))
	{
		return SHIP_CAREERLUGGER;
	}
	
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21) iClass = 4 - rand(1);
	
	return GetRandomShipType(GetClassFlag(iClass), iFlagType, FLAG_SHIP_NATION_ANY);
}

int SelectArsenalShipType(int iFlagType)
{
	int iClass = 6;
	int iRank = sti(pchar.rank);
	
	if(iRank < 6) iClass = 6;
	if(iRank >= 6 && iRank < 12) iClass = 6 - rand(1);
	if(iRank >= 12 && iRank < 21) iClass = 5 - rand(1);
	if(iRank >= 21 && iRank < 30) iClass = 4 - rand(1);
	if(iRank >= 30) iClass = 2;
	
	return GetRandomShipType(GetClassFlag(iClass), iFlagType, FLAG_SHIP_NATION_ANY);
}

string SelectPassText()
{
	string sText;
	switch (hrand(5))
	{
	case 0:
		sText = "Que Judas, valiéndose de su posición, vendió un importante secreto de Estado a una potencia enemiga.";
		break;
	case 1:
		sText = "Ese canalla asqueroso mató a su pariente, un hombre conocido y noble, para heredar su fortuna.";
		break;
	case 2:
		sText = "Ese canalla asqueroso insultó a mi familia y a mí personalmente.";
		break;
	case 3:
		sText = "Este granuja ladrón robó una buena suma de dinero del tesoro de nuestra ciudad.";
		break;
	case 4:
		sText = "Ese villano es culpable de la muerte de casi una docena de nuestros ciudadanos.";
		break;
	case 5:
		sText = "Ese granuja utilizó su conexión para apoderarse de un buque mercante, y luego lo robó y vendió en el astillero vecino.";
		break;
	}
	return sText;
}

string SelectFugitiveCity()
{
	string sCity;
	switch (rand(3))
	{
	case 0:
		sCity = "LaVega";
		break;
	case 1:
		sCity = "PuertoPrincipe";
		break;
	case 2:
		sCity = "LeFransua";
		break;
	case 3:
		sCity = "FortOrange";
		break;
	}
	return sCity;
}

string SelectFugitiveText()
{
	string sText;
	switch (hrand(5))
	{
	case 0:
		sText = "uno de los oficiales subalternos de nuestra guarnición ha desertado y abandonado la colonia a bordo de un barco mercante.";
		break;
	case 1:
		sText = "uno de nuestros oficiales desertó en acto de servicio y escapó a bordo de un barco contrabandista.";
		break;
	case 2:
		sText = "uno de nuestros oficiales de la marina que prestaba servicio en un bergantín de patrulla desertó por motivos desconocidos, secuestró un barco largo y desapareció en él.";
		break;
	case 3:
		sText = "uno de nuestros guardias de prisión renunció a su servicio por razones desconocidas y abandonó nuestra colonia a bordo de un barco privado.";
		break;
	case 4:
		sText = "uno de los soldados de nuestra guarnición abandonó su puesto mientras montaba guardia, se dirigió a la cala y abandonó este lugar a bordo de una embarcación desconocida.";
		break;
	case 5:
		sText = "uno de nuestros oficiales militares, capitán de un lugre de patrulla, abandonó su barco en alta mar y se dirigió al sur en un palangrero de pesca.";
		break;
	}
	return sText;
}
