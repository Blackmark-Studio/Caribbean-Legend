// boal 08/04/06 общий диалог верфи
#include "DIALOGS\%language%\Rumours\Common_rumours.c" //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;
	string s2;

	int iShipClass = GetCharacterShipClass(PChar); // Если корабля нет, вернет 7 (лодка)
	int iRank = sti(PChar.rank);
	int iSumm, iType;

	ref rRealShip;
	ref shTo;
	aref refShip;
	string attr;
	float fTmp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Shipyard\" + NPChar.City + "_Shipyard.c ";
						 if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag); // homo 16/06/06
	bool ok;
	int iTest = FindColony(NPChar.City); // город магазина
	ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}

	int Material, WorkPrice;
	int amount;
	int iCannonDiff;

	// генератор парусов по кейсу -->
	string attrLoc = Dialog.CurrentNode;
	int i;
	if (findsubstr(attrLoc, "SailsColorIdx_", 0) != -1)
	{
		i = findsubstr(attrLoc, "_", 0);
		NPChar.SailsColorIdx = strcut(attrLoc, i + 1, strlen(attrLoc) - 1); // индех в конце
		Dialog.CurrentNode = "SailsColorDone";
	}
	if (findsubstr(attrLoc, "SailsTypeChooseIDX_", 0) != -1)
	{
		i = findsubstr(attrLoc, "_", 0);
		NPChar.SailsTypeChooseIDX = strcut(attrLoc, i + 1, strlen(attrLoc) - 1); // индех в конце
		Dialog.CurrentNode = "SailsTypeChoose2";
	}
	if(!CheckAttribute(NPChar, "ExpMeeting"))
	{
		NPChar.ExpMeeting = true;
		notification("Первое посещение верфи " + XI_ConvertString("Colony" +NPChar.City + "Gen"), "Carpenter");
		AddCharacterExpToSkill(pchar, SKILL_REPAIR, 10.0);
	}
	// генератор парусов по кейсу <--
	switch (Dialog.CurrentNode)
	{
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "ship_tunning_not_now": // аналог выхода, со старых времен, много переделывать.
		LockControl("DlgDown3", false);
		LockControl("DlgUp3", false);
		DialogExit();
		NextDiag.CurrentNode = "First time"; // выход для тюнинга, нужно тут из-за LoadSegment
		break;

	case "ship_tunning_not_now_1":
		LockControl("DlgDown3", false);
		LockControl("DlgUp3", false);
		DialogExit();
		NextDiag.CurrentNode = "First time";
		break;

	case "fight":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		LAi_group_Attack(NPChar, Pchar);
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "First time":
		if (LAi_grp_playeralarm > 0)
		{
			dialog.text = NPCharRepPhrase(pchar, LinkRandPhrase("La alarma se ha dado en el pueblo, y todos te están buscando. Si yo fuera tú, no me quedaría aquí.", "Todos los guardias de la ciudad están peinando el pueblo buscándote. ¡No soy un tonto y no hablaré contigo!", "Corre, " + GetSexPhrase("compañero", "moza") + ", antes de que los soldados te conviertan en un colador..."), LinkRandPhrase("¿Qué necesitas, " + GetSexPhrase("apestoso", "canalla") + "? ¡Los guardias de la ciudad ya tienen tu rastro, no llegarás lejos, sucio pirata!", "¡Asesino, sal de mi casa de inmediato! ¡Guardias!", "No te tengo miedo, " + GetSexPhrase("canalla", "rata") + "¡Pronto serás colgado en nuestro fuerte, no llegarás lejos!"));
			link.l1 = NPCharRepPhrase(pchar, RandPhraseSimple("Je, una alarma no es un problema para mí...", "  Nunca me atraparán.  "), RandPhraseSimple("Cierra la boca, " + GetWorkTypeOfMan(npchar, "") + ", ¡o te arrancaré la lengua!", "Heh, " + GetWorkTypeOfMan(npchar, "") + ", y allí también, ¡para atrapar piratas! Eso es lo que te digo, compañero: ¡estate quieto y no morirás!"));
			link.l1.go = "fight";
			break;
		}

		// Jason ---------------------------------------Бремя гасконца------------------------------------------------
		if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && pchar.location == "Fortfrance_shipyard")
		{
			if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") || CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") || CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter"))
			{
				dialog.text = "¿Desea algo, Monsieur?";
				Link.l1 = "He venido a echar un vistazo a tus barcos... Pero ahora mismo estoy un poco ocupado, todavía tengo un asunto sin terminar. Volveré más tarde, una vez que lo haya terminado.";
				Link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.Sharlie == "ship" || pchar.questTemp.Sharlie == "ship_fast") // Addon 2016-1 Jason пиратская линейка 1
			{
				dialog.text = "¿Quiere algo, Monsieur?";
				Link.l1 = "Escucha, me gustaría comprar un barco de ti.";
				Link.l1.go = "Sharlie";
				break;
			}
			dialog.text = "¿Desea algo más, Monsieur?";
			Link.l1 = "No, supongo que no.";
			Link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			NPChar.quest.meeting = "1";
			break;
		}
		//<-- Бремя гасконца
		// Addon-2016 Jason, французские миниквесты (ФМК) ФМК-Мартиника
		if (CheckAttribute(pchar, "questTemp.FMQM.Oil") && pchar.location == "Fortfrance_shipyard")
		{
			if (pchar.questTemp.FMQM == "remove_oil")
			{
				dialog.text = "Eso es todo, Capitán. El trabajo está hecho. Ahora la parte agradable: el sonido de las monedas. Dame un segundo...";
				link.l1 = "...";
				link.l1.go = "FMQM_oil_1";
				break;
			}
			if (pchar.questTemp.FMQM == "remove_oil1")
			{
				dialog.text = "¡Oficial, espere! ¡Por favor! Esto debe ser algún tipo de error. Monsieur, el Capitán no tiene nada que ver con esto, solo atracó aquí para reparar su barco. Estaba a punto de partir. ¿Y qué barriles? ¿De qué está hablando?";
				link.l1 = "";
				link.l1.go = "FMQM_oil_2";
				break;
			}
			if (pchar.questTemp.FMQM == "remove_oil2")
			{
				dialog.text = "Oficial, lo repito: el Capitán ha venido aquí para pagar por las reparaciones del barco. Estos barriles son de mi propiedad y son solo para fines de producción. Soy un maestro constructor de barcos y esta resina es para las embarcaciones que construyo.";
				link.l1 = "";
				link.l1.go = "FMQM_oil_3";
				break;
			}
			if (pchar.questTemp.FMQM == "remove_oil3")
			{
				dialog.text = "¡Oh, Monsieur Capitán! No tenéis idea de lo mal que lo pasé. ¡Dos días en mazmorras acompañados de ratas, ratones y personajes miserables! Tuve que usar todas mis conexiones para sacarme de allí. ¡Ah, el aire fresco!";
				link.l1 = "Tienes mis condolencias, maestro. ¿Qué pasa con nuestra resina? ¿Y mis monedas?";
				link.l1.go = "FMQM_oil_4";
				DelLandQuestMark(npchar);
				break;
			}
		}
		// Addon 2016-1 Jason пиратская линейка
		if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "silk_13" && pchar.location == "PortRoyal_shipyard")
		{
			dialog.text = "¡Oh, eres tú de nuevo! ¡Te reconozco, joven! Fuiste tú quien preguntó recientemente sobre... aumentar la velocidad de tu barco usando velas de seda, ¿verdad?";
			link.l1 = "Tu memoria te honra, maestro.";
			link.l1.go = "mtraxx_x";
			break;
		}

		if (NPChar.quest.meeting == "0") // первая встреча
		{
			dialog.Text = GetNatPhrase(npchar, LinkRandPhrase("¡Ja! ¡Un verdadero viejo lobo de mar ha venido a mi humilde taller! ¿Es nuevo en estas aguas, capitán?", "¡Bienvenido, señor! Si no eres un extraño al mar y tienes un barco, ¡has venido al lugar correcto!", "¡Hola, señor! Tienes suerte: este es el mejor taller de barcos de todo el Nuevo Mundo británico."), LinkRandPhrase("Monsieur, supongo que eres un capitán apuesto, ¿verdad? Si lo eres, ¡hiciste bien en visitar mi modesto astillero!", "¿Primera vez aquí, Monsieur Capitán? Entra y conoce a este viejo constructor naval.", "¡Tengamos el placer de conocernos, Monsieur! Un barco necesita ser acariciado, al igual que una mujer, ¡y nosotros, los franceses, somos expertos en eso! Créame, no se arrepentirá de venir aquí."), LinkRandPhrase("¡Nunca te he visto por aquí antes, señor. Encantado de conocerte!", "¡Saludo a un valiente conquistador de los mares! ¿Eres un marinero, no es así? Y yo soy el constructor naval, deberíamos conocernos.", "¡Hola, caballero! ¡Me alegra darte la bienvenida a mi taller!"), LinkRandPhrase("Buenas tardes, señor. No lo he visto antes, ¿verdad? ¿Tiene negocios conmigo?", "Hola, señor capitán. No se sorprenda, he conocido a bastantes capitanes, así que me di cuenta de que usted también es capitán a primera vista.", "Entre, señor. Soy el constructor naval. Un placer conocerle."));
			Link.l1 = LinkRandPhrase("También me alegra conocerte. Mi nombre es " + GetFullName(pchar) + ", y soy nuevo en estos lugares. Así que decidí pasarme por aquí.", "Simplemente no podía pasar de largo, el olor a tablones recién cepillados... Yo soy " + GetFullName(pchar) + ", Capitán del barco '" + pchar.ship.name + "'.", "Permítame presentarme, " + GetFullName(pchar) + ", Capitán del barco '" + pchar.ship.name + "Encantado de conocerte. Entonces, estás construyendo y reparando barcos aquí, ¿verdad?");
			Link.l1.go = "meeting";
			NPChar.quest.meeting = "1";
			if (startHeroType == 4 && NPChar.location == "SantaCatalina_shipyard")
			{
				dialog.text = "Saludos, Capitán MacArthur.";
				link.l1 = "Puedes llamarme Helen, señor " + npchar.lastname + ". " + TimeGreeting() + ".";
				Link.l1.go = "Helen_meeting";
			}
		}
		else
		{
			dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("¡Oh! El terror de las aguas locales, Capitán " + GetFullName(pchar) + "¡Qué puedo hacer por ti?", "Vamos directo al grano, " + GetAddress_Form(NPChar) + ", No tengo tiempo para charlar. ¿Necesitas una reparación o solo quieres reemplazar tu bañera?", "¡Oh, no es eso " + GetFullName(pchar) + "¡ Qué pasa, " + GetAddress_Form(NPChar) + "¿Algo malo le pasó a tu bañera?"), LinkRandPhrase("¿Qué necesitas ahí, Capitán? Ni un solo minuto de paz, siempre todos estos bribones, qué día maldito...", "Hola, " + GetAddress_Form(NPChar) + ". Debo decir que tu visita espantó a todos mis clientes. ¿Espero que tu pedido cubra mis daños?", "¿De negocios conmigo, " + GetAddress_Form(NPChar) + "¿Bueno, sigue con ello y hazlo rápido?"), LinkRandPhrase("¿Qué te trae a mí, señor " + GetFullName(pchar) + "¿Puedo entender que tu barco pueda tener dificultades, considerando tu estilo de vida...?", "Me alegra saludar a un noble... oh, disculpe, " + GetAddress_Form(NPChar) + ", te confundí con otra persona. ¿Qué querías?", "No me gusta mucho tu tipo, Capitán, pero no te echaré, de todos modos. ¿Qué querías?")), LinkRandPhrase(LinkRandPhrase("Me alegra mucho verte, señor " + GetFullName(pchar) + "¡Entonces, cómo está funcionando? ¿Necesitas una reparación o careenado?", "Bienvenido, " + GetAddress_Form(NPChar) + "¡ Capitán " + GetFullName(pchar) + " ¡siempre es un huésped bienvenido en mi taller!", "Oh, " + GetAddress_Form(NPChar) + " " + GetFullName(pchar) + "¡Me has visitado de nuevo! Espero que tu belleza esté bien, ¿no es así?"), LinkRandPhrase("" + GetAddress_Form(NPChar) + ", ¡Me alegra tanto verte de nuevo! ¿Cómo está tu hermoso barco? ¿Necesitas ayuda?", "Oh, " + GetAddress_Form(NPChar) + ", ¡saludos! ¿Cómo va todo? ¿Quizás los mástiles crujen o necesitas limpiar la sentina? ¡Mis muchachos harán lo mejor para ti!", "Buenas tardes, Capitán " + GetFullName(pchar) + "Me alegra que hayas venido de nuevo, y siempre estoy dispuesto a ayudarte."), LinkRandPhrase("¡Me alegra tenerte aquí, Capitán! Eres un cliente muy amable, " + GetAddress_Form(NPChar) + ", y deseo que sigas siendo así.", "Oh, " + GetAddress_Form(NPChar) + " " + GetFullName(pchar) + "¡Estoy realmente feliz de tenerte aquí! ¿Qué puedo hacer por ti?", "Capitán, de nuevo has visitado " + XI_ConvertString("Colony" + npchar.City + "Acc") + "¡Créeme, estaremos encantados de ayudarte!")));
			Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("Consigue tus instrumentos, maestro, y mantente en silencio, ¿de acuerdo? No estoy de humor.", "¡Deja de charlar, compañero! Necesito tu ayuda, y no tus tonterías."), RandPhraseSimple("Estoy pagando y tú estás trabajando. Silenciosamente. ¿Está claro?", "¡Eh, camarada, ahuyéntalos a todos, soy tu cliente preferido!")), RandPhraseSimple(RandPhraseSimple("También me alegra verte, maestro. Por desgracia, no tengo mucho tiempo, así que vayamos al grano.", "Y yo también estoy feliz de verte, camarada. ¿Quieres ayudar a tu cliente preferido?"), RandPhraseSimple("Buenas tardes, amigo. Vayamos al grano de inmediato. Prometo, la próxima vez nos sentaremos con una botella, seguro.", "Me alegra verte, maestro. Siempre es un placer verte, pero ahora mismo necesito tu ayuda.")));
			Link.l1.go = "Shipyard";
			if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY)
			{
				link.l11 = "Necesito cañones para mi barco.";
				link.l11.go = "Cannons";
			}

			if (NPChar.city == "PortRoyal" || NPChar.city == "Havana" || NPChar.city == "Villemstad" || NPChar.city == "Charles" || NPChar.city == "PortoBello")
			{
				link.l22 = "¿Podéis ofrecerme algo especial, algo que no se puede encontrar en ningún otro astillero?";
				link.l22.go = "ship_tunning";
			}

			link.l15 = "¿No tienes un trabajo que requiera la ayuda de un extraño?";
			link.l15.go = "Tasks";
			// Jason Исла Мона
			if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "tools" && !CheckAttribute(npchar, "quest.IslaMonaTools"))
			{
				link.l20 = "Quiero comprar un conjunto de herramientas de construcción, forja y medición de calidad europea. ¿Puedes ayudarme?";
				link.l20.go = "IslaMona";
			}
			if (CheckAttribute(npchar, "quest.IslaMonaMoney"))
			{
				link.l20 = "Traje doblones para un juego de herramientas de construcción.";
				link.l20.go = "IslaMona_7";
			}
			// Jason --> генератор Призонер
			if (CheckAttribute(pchar, "GenQuest.Findship.Shipyarder") && NPChar.location == pchar.GenQuest.Findship.Shipyarder.City + "_shipyard")
			{
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
				{
					for (i = 1; i < COMPANION_MAX; i++)
					{
						int iTemp = GetCompanionIndex(PChar, i);
						if (iTemp > 0)
						{
							sld = GetCharacter(iTemp);
							if (GetRemovable(sld) && sti(RealShips[sti(sld.ship.type)].basetype) == sti(pchar.GenQuest.Findship.Shipyarder.ShipType))
							{
								pchar.GenQuest.Findship.Shipyarder.CompanionIndex = sld.Index;
								pchar.GenQuest.Findship.Shipyarder.OK = 1;
								pchar.GenQuest.Findship.Shipyarder.ShipName = sld.Ship.Name;
								pchar.GenQuest.Findship.Shipyarder.Money = makeint(GetShipSellPrice(sld, CharacterFromID(NPChar.city + "_shipyarder")) * 1.5);
							}
						}
					}
				}
				if (sti(pchar.GenQuest.Findship.Shipyarder.OK) == 1)
				{
					link.l16 = "Te he entregado " + pchar.GenQuest.Findship.Shipyarder.ShipBaseName + ", como pediste.";
					link.l16.go = "Findship_check";
				} // <-- генератор Призонер
			}
			// Jason --> генератор Неудачливый вор
			if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && CheckCharacterItem(pchar, "Tool") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_shipyard")
			{
				link.l17 = "He conseguido localizar al ladrón y obtener " + pchar.GenQuest.Device.Shipyarder.Type + ".";
				link.l17.go = "Device_complete";
			}
			// <-- генератор Неудачливый вор
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
			{
				link.l12 = "Quiero cambiar el aspecto de mis velas.";
				link.l12.go = "SailsGerald";
			}
			Link.l2 = "Solo quería hablar.";
			Link.l2.go = "quests"; //(перессылка в файл города)
								   // -->
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l3 = "Me gustaría hablar con usted sobre asuntos financieros.";
				link.l3.go = "LoanForAll";
			}
			if (CheckAttribute(pchar, "GenQuest.Intelligence") && CheckAttribute(pchar, "GenQuest.Intelligence.SpyId") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") // квест мэра - на связь с нашим шпионом
			{
				link.l7 = RandPhraseSimple("Estoy aquí por petición de un hombre. Su nombre es Gobernador " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " me envió a usted. Se supone que debo recoger algo...");
				link.l7.go = "IntelligenceForAll";
			}
			// Jason, генер почтового курьера 2 уровня
			if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
			{
				if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
				{
					link.l14 = "Traje el dibujo del barco desde " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.StartCity + "Gen") + ".";
					link.l14.go = "Postcureer_LevelUp_ForAll";
				}
			} // patch-6
			if (CheckAttribute(pchar, "GenQuest.EncGirl"))
			{
				if (pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
				{
					link.l7 = "Hola, vine por invitación de tu hijo.";
					link.l7.go = "EncGirl_4";
					pchar.quest.EncGirl_GetLoverFather.over = "yes";
				}
				if (pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
				{
					if (pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
					{
						link.l8 = "Esto es sobre tu hija...";
						link.l8.go = "EncGirl_1";
					}
				}
			}
			Link.l9 = "Necesito irme.";
			Link.l9.go = "exit";
		}
		NextDiag.TempNode = "First time";
		break;

	case "Meeting":
		dialog.Text = "Estoy muy contento de conocer a un nuevo cliente. Mi astillero está a su servicio.";
		Link.l1 = "Excelente, " + GetFullName(NPChar) + " Vamos a ver qué puedes ofrecerme.";
		Link.l1.go = "Shipyard";
		if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY)
		{
			link.l13 = "Necesito cañones para mi barco.";
			link.l13.go = "Cannons";
		}
		link.l15 = "¿No tienes un trabajo que requiera la ayuda de un extraño?";
		link.l15.go = "Tasks";

		if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
		{
			link.l12 = "Quiero cambiar el aspecto de mis velas.";
			link.l12.go = "SailsGerald";
		}
		Link.l2 = "Solo quería hablar.";
		link.l2.go = "quests";
		// -->
		if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
		{
			link.l3 = "Me gustaría hablar contigo sobre asuntos financieros.";
			link.l3.go = "LoanForAll"; //(перессылка в файл города)
		}
		if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") // квест мэра - на связь с нашим шпионом
		{
			link.l7 = RandPhraseSimple("Estoy aquí a petición de un hombre. Su nombre es Gobernador " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " me envió a ti. Se supone que debo recoger algo...");
			link.l7.go = "IntelligenceForAll";
		}
		// Jason, генер почтового курьера 2 уровня
		if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
		{
			if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
			{
				link.l14 = "Entregué el dibujo del barco desde el pueblo de " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.StartCity + "Gen") + ".";
				link.l14.go = "Postcureer_LevelUp_ForAll";
			}
		}

		if (CheckAttribute(pchar, "GenQuest.EncGirl"))
		{
			if (pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
			{
				link.l8 = "Hola, vine por invitación de tu hijo.";
				link.l8.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}
			if (pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
			{
				if (pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
				{
					link.l9 = "Esto se trata de tu hija...";
					link.l9.go = "EncGirl_1";
				}
			}
		}
		if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakShipyard"))
		{
			if (CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
			{
				link.l10 = "¿Qué puedes decirme sobre el propietario de estos documentos?";
				link.l10.go = "ShipLetters_6"; // генератор  "Найденные документы"
			}
		}
		Link.l11 = "Debo irme, gracias.";
		Link.l11.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "Helen_Meeting":
		dialog.Text = "Por supuesto, Capitán MacArthur, como desee. ¿Qué necesita hoy?";
		Link.l1 = "Excelente, " + GetFullName(NPChar) + " Veamos qué puedes ofrecerme.";
		Link.l1.go = "Shipyard";
		if (GetNationRelation2MainCharacter(sti(NPChar.nation)) != RELATION_ENEMY)
		{
			link.l13 = "Necesito cañones para mi barco.";
			link.l13.go = "Cannons";
		}
		link.l15 = "¿No tienes un trabajo que requiera la ayuda de un extraño?";
		link.l15.go = "Tasks";

		if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && RealShips[sti(Pchar.Ship.Type)].BaseType != SHIP_CURSED_FDM) // mitrokosta фикс ломаных диалогов
		{
			link.l12 = "Quiero cambiar el aspecto de mis velas.";
			link.l12.go = "SailsGerald";
		}
		Link.l2 = "Solo quería hablar.";
		link.l2.go = "quests";
		// -->
		if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
		{
			link.l3 = "Me gustaría hablar con usted sobre asuntos financieros.";
			link.l3.go = "LoanForAll"; //(перессылка в файл города)
		}
		if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "") // квест мэра - на связь с нашим шпионом
		{
			link.l7 = RandPhraseSimple("Estoy aquí por solicitud de un hombre. Su nombre es Gobernador " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " me envió a ti. Se supone que debo recoger algo...");
			link.l7.go = "IntelligenceForAll";
		}
		// Jason, генер почтового курьера 2 уровня
		if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
		{
			if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
			{
				link.l14 = "Entregué el plano del barco desde el pueblo de " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.StartCity + "Gen") + ".";
				link.l14.go = "Postcureer_LevelUp_ForAll";
			}
		}

		if (CheckAttribute(pchar, "GenQuest.EncGirl"))
		{
			if (pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "shipyard_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
			{
				link.l8 = "Hola, vine por invitación de su hijo.";
				link.l8.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}
			if (pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
			{
				if (pchar.GenQuest.EncGirl.Father == "shipyard_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
				{
					link.l9 = "Esto es sobre tu hija...";
					link.l9.go = "EncGirl_1";
				}
			}
		}
		if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakShipyard"))
		{
			if (CheckAttribute(pchar, "questTemp.different.GiveShipLetters") && (pchar.questTemp.different.GiveShipLetters.city == npchar.city))
			{
				link.l10 = "¿Qué puedes decirme sobre el dueño de estos documentos?";
				link.l10.go = "ShipLetters_6"; // генератор  "Найденные документы"
			}
		}
		Link.l11 = "Debo irme, gracias.";
		Link.l11.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "ship_tunning":
		dialog.text = "Nuestra astillero es conocido por mejorar barcos. ¿Está interesado, Capitán?";
		Link.l1 = LinkRandPhrase("¡Excelente! ¿Quizás pueda echarle un vistazo a mi barco y decirme cómo puede mejorarse?", "¡Eso es muy interesante, maestro! ¿Y qué puedes hacer por mi barco?", "Hum... Sabes, me he acostumbrado a mi barco, pero si me ofreces algo realmente interesante, puedo pensarlo. ¿Qué dices?");
		Link.l1.go = "ship_tunning_start";
		break;

	case "ship_tunning_start":
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
		{
			if (sti(RealShips[sti(pchar.Ship.Type)].Class) >= 7)
			{
				dialog.Text = "Errr... Yo no trato con barcos. Una vieja bañera seguirá siendo una vieja bañera, no importa cuánto esfuerzo le pongas.";
				Link.l1 = "Veo...";
				Link.l1.go = "ship_tunning_not_now_1";
				break;
			}
			// belamour legendary edition -->
			if (!TuningAvailable())
			{
				dialog.Text = "Más o menos... veamos qué tenemos aquí... Sí, " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + "Tu barco ya tiene el máximo número de características mejoradas, me temo que seguir trabajando en él no tiene sentido y solo puede hacer daño.";
				Link.l1 = "Ya veo...";
				Link.l1.go = "ship_tunning_not_now_1";
				break;
			}
			// <-- legendary edition
			if (GetHullPercent(pchar) < 100 || GetSailPercent(pchar) < 100)
			{
				dialog.Text = "Antes de mejorar un barco, debe estar completamente reparado. Esto también se puede hacer aquí en mi astillero.";
				Link.l1 = "Entendido...";
				Link.l1.go = "ship_tunning_not_now_1";
				break;
			}

			s2 = "De acuerdo, veamos que tenemos aquí... Ajá, un " + XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName) + ".";
			// belamour legendary edition -->
			if (NPChar.city == "PortRoyal")
			{
				s2 = s2 + " Nuestro astillero es famoso por mejorar el rendimiento del buque, podemos aumentar tanto la velocidad máxima como el ángulo con respecto al viento.";
			}
			if (NPChar.city == "Havana" || NPChar.city == "PortoBello")
			{
				s2 = s2 + " En nuestro astillero podemos aumentar el número máximo de cañones o la capacidad de carga del barco.";
			}
			if (NPChar.city == "Villemstad")
			{
				s2 = s2 + " Mis chicos pueden reforzar el casco de tu barco o aumentar el número máximo de marineros de tu tripulación.";
			}
			if (NPChar.city == "Charles")
			{
				s2 = s2 + " En este astillero puedes mejorar la maniobrabilidad o reducir el número mínimo de marineros de la tripulación.";
			}

			dialog.Text = s2;

			if (NPChar.city == "PortRoyal")
			{
				// belamour legendary edition -->
				ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.SpeedRate")) &&
					 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.WindAgainst"));
				if (ok)
				{
					Link.l1 = "Aumenta la velocidad.";
					Link.l1.go = "ship_tunning_SpeedRate";
					Link.l2 = "Aumentar el ángulo al viento.";
					Link.l2.go = "ship_tunning_WindAgainst";
					Link.l3 = "¡Espera! He cambiado de opinión.";
					Link.l3.go = "ship_tunning_not_now_1";
					break;
				}
				else
				{
					if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.SpeedRate"))
					{
						Link.l1 = "Aumentar la velocidad.";
						Link.l1.go = "ship_tunning_SpeedRate";
						Link.l2 = "¡Espera! He cambiado de opinión.";
						Link.l2.go = "ship_tunning_not_now_1";
						break;
					}
					if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.WindAgainst"))
					{
						Link.l1 = "Aumenta el ángulo con el viento.";
						Link.l1.go = "ship_tunning_WindAgainst";
						Link.l2 = "¡Espera! He cambiado de opinión.";
						Link.l2.go = "ship_tunning_not_now_1";
						break;
					}
					Link.l1 = LinkRandPhrase("¡Oh! Mi embarcación ya está mejorada de esta manera. Bueno, ¡gracias por tu tiempo!", "Gracias, maestro, pero ya tengo una mejora, y es exactamente lo que me has mencionado. ¡Buena suerte con otros barcos y sus Capitanes!", "¡Eh! Supongo que mi barco ya había sido reacondicionado antes por un dueño anterior, debe haber sido en este mismo astillero. Bueno, supongo que debo agradecerle por su previsión, y a ti y a tus muchachos por su excelente trabajo.");
					Link.l1.go = "ship_tunning_not_now_1";
				}
				// <-- legendary edition
			}
			if (NPChar.city == "Havana" || NPChar.city == "PortoBello")
			{
				ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon")) &&
					 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Capacity"));
				if (ok)
				{
					if (GetPossibilityCannonsUpgrade(pchar, true) > 0)
					{
						Link.l1 = "Aumentar el número máximo de cañones.";
						Link.l1.go = "ship_c_quantity";
					}
					Link.l2 = "Aumenta el peso muerto.";
					Link.l2.go = "ship_tunning_Capacity";
					Link.l3 = "¡Espera! Cambié de opinión.";
					Link.l3.go = "ship_tunning_not_now_1";
					break;
				}
				else
				{
					if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Cannon"))
					{
						if (GetPossibilityCannonsUpgrade(pchar, true) > 0)
						{
							Link.l1 = "Aumenta el número máximo de cañones.";
							Link.l1.go = "ship_c_quantity";
							Link.l2 = "¡Espera! Cambié de opinión.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
					}
					if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.Capacity"))
					{
						Link.l1 = "Aumenta el peso muerto.";
						Link.l1.go = "ship_tunning_Capacity";
						Link.l2 = "¡Espera! Cambié de opinión.";
						Link.l2.go = "ship_tunning_not_now_1";
						break;
					}
					Link.l1 = LinkRandPhrase("¡Oh! Mi embarcación ya está mejorada de esta manera. Bueno, ¡gracias por tu tiempo!", "Gracias, maestro, pero ya tengo una mejora, y es exactamente lo que me mencionaste. ¡Buena suerte con otros barcos y sus Capitanes!", "¡Je! Supongo que mi barco ya había sido reacondicionado antes por un propietario anterior, debió ser en este mismo astillero. Bueno, supongo que debo agradecerle por su previsión, y a ti y a tus muchachos por su excelente trabajo!");
					Link.l1.go = "ship_tunning_not_now_1";
					// <-- legendary edition
				}
			}
			if (NPChar.city == "Villemstad")
			{
				ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.HP")) &&
					 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MaxCrew"));
				if (ok)
				{
					Link.l1 = "Aumenta la durabilidad del casco.";
					Link.l1.go = "ship_tunning_HP";
					Link.l2 = "Aumentar espacio para la tripulación.";
					Link.l2.go = "ship_tunning_MaxCrew";
					Link.l3 = "¡Espera! Cambié de opinión.";
					Link.l3.go = "ship_tunning_not_now_1";
					break;
				}
				else
				{
					// belamour legendary edition -->
					if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.HP"))
					{
						Link.l1 = "Aumenta la durabilidad del casco.";
						Link.l1.go = "ship_tunning_HP";
						Link.l2 = "¡Espera! Cambié de opinión.";
						Link.l2.go = "ship_tunning_not_now_1";
						break;
					}
					if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MaxCrew"))
					{
						Link.l1 = "Aumentar espacio para la tripulación.";
						Link.l1.go = "ship_tunning_MaxCrew";
						Link.l2 = "¡Espera! He cambiado de opinión.";
						Link.l2.go = "ship_tunning_not_now_1";
						break;
					}
					Link.l1 = LinkRandPhrase("¡Oh! Mi embarcación ya está mejorada de esta manera. ¡Bueno, gracias por tu tiempo!", "Gracias, maestro, pero ya tengo una mejora, y es exactamente lo que me has mencionado. ¡Buena suerte con otros barcos y sus Capitanes!", "¡Je! Supongo que mi barco ya había sido reacondicionado antes por un dueño anterior, debe haber sido en este mismo astillero. Bueno, supongo que debo agradecerle por su previsión, y a usted y a sus muchachos por su excelente trabajo!");
					Link.l1.go = "ship_tunning_not_now_1";
					// <-- legendary edition
				}
			}
			if (NPChar.city == "Charles")
			{
				ok = (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.TurnRate")) &&
					 (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MinCrew"));
				if (ok)
				{
					Link.l1 = "Aumentar la maniobrabilidad.";
					Link.l1.go = "ship_tunning_TurnRate";
					if (sti(RealShips[sti(pchar.Ship.Type)].Class) < 5)
					{
						Link.l2 = "Disminuir el tamaño mínimo de la tripulación.";
						Link.l2.go = "ship_tunning_MinCrew";
					}
					Link.l3 = "¡Espera! Cambié de opinión.";
					Link.l3.go = "ship_tunning_not_now_1";
					break;
				}
				else
				{
					// belamour legendary edition -->
					if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.TurnRate"))
					{
						Link.l1 = "Aumentar maniobrabilidad.";
						Link.l1.go = "ship_tunning_TurnRate";
						Link.l2 = "¡Espera! Cambié de opinión.";
						Link.l2.go = "ship_tunning_not_now_1";
						break;
					}
					if (!CheckAttribute(&RealShips[sti(Pchar.Ship.Type)], "Tuning.MinCrew"))
					{
						if (sti(RealShips[sti(pchar.Ship.Type)].Class) < 5)
						{
							Link.l1 = "Disminuye el tamaño mínimo de la tripulación.";
							Link.l1.go = "ship_tunning_MinCrew";
							Link.l2 = "¡Espera! Cambié de opinión.";
							Link.l2.go = "ship_tunning_not_now_1";
							break;
						}
					}
					// <-- legendary edition
				}
				Link.l1 = LinkRandPhrase("¡Oh! Mi nave ya está mejorada de esta manera. ¡Bien, gracias por tu tiempo!", "Gracias, maestro, pero ya tengo una mejora, y es exactamente lo que me mencionaste. ¡Buena suerte con otros barcos y sus Capitanes!", "¡Je! Supongo que mi barco ya había sido reacondicionado antes por un propietario anterior; debió ser en este mismo astillero. Bueno, supongo que debo agradecerle por su previsión, y a ti y a tus muchachos por su excelente trabajo.");
				Link.l1.go = "ship_tunning_not_now_1";
			}
		}
		else
		{
			dialog.Text = "¿Dónde está el barco? ¿Me estás tomando el pelo o qué?";
			Link.l1 = "Oh, mi error, en verdad... Lo siento.";
			Link.l1.go = "ship_tunning_not_now_1";
		}
		break;

	////////////////////////////////////////// Capacity ////////////////////////////////////////////////////
	case "ship_tunning_Capacity":
		Material = GetMaterialQtyUpgrade(pchar, NPChar, 1);
		WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2);
		s2 = "Bueno, veamos qué podemos hacer. En este momento el peso muerto de su buque es de " + sti(RealShips[sti(pchar.Ship.Type)].Capacity);
		s2 = s2 + ". Para mamparos más ligeros necesitaré: Sándalo -" + Material + ".";
		s2 = s2 + " Como pago por mi trabajo pido: " + WorkPrice + " cofres de doblones para cubrir mis gastos. Eso es todo. Ah, el dinero será por adelantado.";
		dialog.Text = s2;
		Link.l1 = "Acordado. Acepto tus términos. Te traeré lo que necesites.";
		Link.l1.go = "ship_tunning_Capacity_start";
		Link.l2 = "No. Eso no me conviene.";
		Link.l2.go = "ship_tunning_not_now_1";
		break;

	case "ship_tunning_Capacity_start":
		amount = GetMaterialQtyUpgrade(pchar, NPChar, 2);
		// belamour legendary edition туда сюда бегать - та еще морока -->
		if (GetCharacterItem(pchar, "chest") + CheckItemMyCabin("chest") >= amount)
		{
			if (GetCharacterItem(pchar, "chest") >= amount)
			{
				TakeNItems(pchar, "chest", -amount);
			}
			else
			{
				iSumm = amount - sti(GetCharacterItem(pchar, "chest"));
				TakeNItems(pchar, "chest", -sti(GetCharacterItem(pchar, "chest")));
				GetItemMyCabin("chest", iSumm);
				Log_Info("Cofres retirados del camarote: " + iSumm + " und.");
			}
			// <-- legendary edtion
			NPChar.Tuning.Money = amount;
			NPChar.Tuning.Matherial = GetMaterialQtyUpgrade(pchar, NPChar, 1);
			NPChar.Tuning.ShipType = Pchar.Ship.Type;
			NPChar.Tuning.ShipName = RealShips[sti(Pchar.Ship.Type)].BaseName;
			NextDiag.TempNode = "ship_tunning_Capacity_again";
			dialog.text = "Excelente. Estaré esperando el material.";
			link.l1 = LinkRandPhrase("Te aseguro que no tendrás que esperar mucho tiempo. Puedo resolver tales asuntos, ¿de acuerdo?", "Considera que ya los tienes y reserva el muelle para mí. Seré tan rápido como el viento.", "Por supuesto. Solo tendré que visitar a un par de personas que tienen lo que pediste, ¡ja, ja!");
			link.l1.go = "Exit";
			ReOpenQuestHeader("ShipTuning");
			AddQuestRecord("ShipTuning", "t1");
			AddQuestUserData("ShipTuning", "sText", "Por el trabajo para aumentar el tonelaje de " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" + " el astillero requiere: Sándalo, " + NPChar.Tuning.Matherial + ". Se me pagará una fianza por adelantado por importe de " + NPChar.Tuning.Money + " cofres de doblones.");
		}
		else
		{
			NextDiag.TempNode = "ship_tunning_not_now_1";
			dialog.text = "No veo el depósito...";
			link.l1 = "Pasaré más tarde.";
			link.l1.go = "Exit";
		}
		break;

	case "ship_tunning_Capacity_again":
		if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		{
			NextDiag.TempNode = "ship_tunning_Capacity_again";
			dialog.Text = "El tiempo pasa, y el barco está esperando. ¿Has traído todo lo que pedí?";
			Link.l1 = "Sí, logré encontrar algo.";
			Link.l1.go = "ship_tunning_Capacity_again_2";
			Link.l2 = "No, todavía estoy en ello.";
			Link.l2.go = "Exit";
		}
		else
		{
			DeleteAttribute(NPChar, "Tuning");
			NextDiag.TempNode = "First time";
			dialog.Text = "Señor" + GetSexPhrase("", "ita") + ", ¿has cambiado tu barco desde que hicimos nuestro acuerdo? No deberías haberlo hecho.";
			Link.l1 = "¡Ay, son las circunstancias! Lástima que el depósito se haya perdido...";
			Link.l1.go = "Exit";
			DeleteAttribute(pchar, "achievment.Tuning");
			AddQuestRecord("ShipTuning", "Lose");
			CloseQuestHeader("ShipTuning");
		}
		break;

	case "ship_tunning_Capacity_again_2":
		checkMatherial(Pchar, NPChar, GOOD_SANDAL);
		if (sti(NPChar.Tuning.Matherial) < 1)
		{
			DeleteAttribute(NPChar, "Tuning");
			NextDiag.TempNode = "First time";
			dialog.text = "Excelente, ahora tengo todo lo que necesito. Empezaré a trabajar, entonces.";
			link.l1 = "Estoy esperando.";
			link.l1.go = "ship_tunning_Capacity_complite";
		}
		else
		{
			NextDiag.TempNode = "ship_tunning_Capacity_again";
			dialog.Text = "Todavía necesito: sándalo, " + sti(NPChar.Tuning.Matherial) + ".";
			link.l1 = "Bien.";
			link.l1.go = "Exit";
			AddQuestRecord("ShipTuning", "t1");
			AddQuestUserData("ShipTuning", "sText", "Necesito que traigas: Sándalo " + sti(NPChar.Tuning.Matherial) + ".");
		}
		break;

	case "ship_tunning_Capacity_complite":
		AddTimeToCurrent(6, 30);
		shTo = &RealShips[sti(Pchar.Ship.Type)];
		DeleteAttribute(NPChar, "Tuning");
		// изменим
		if(!CheckAttribute(shTo, "Bonus_Capacity"))
		{
			if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
			{
				shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)* 0.65);
			}
			else
			{
				shTo.Capacity        = sti(shTo.Capacity) + makeint(sti(shTo.Capacity)/5);
			}
		}
		else
		{
			
			if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
			{
				shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.35 + sti(shTo.Bonus_Capacity));
			}
			else
			{
				shTo.Capacity        = makeint((sti(shTo.Capacity) - sti(shTo.Bonus_Capacity)) * 1.2 + sti(shTo.Bonus_Capacity));
			}
		}
		shTo.Tuning.Capacity = true;

		// finish <--
		NextDiag.TempNode = "First time";
		dialog.Text = "...Eso parece ser todo... Ahora puedes cargar tu bodega completamente, garantizo la calidad de mi trabajo.";
		Link.l1 = "¡Gracias! Lo probaré.";
		Link.l1.go = "Exit";
		if (!CheckAttribute(pchar, "achievment.Tuning.stage2") && CheckAttribute(shTo, "Tuning.Cannon") && CheckAttribute(shTo, "Tuning.Capacity"))

		{
			pchar.achievment.Tuning.stage2 = true;
		}
		TuningAvailable();
		AddQuestRecord("ShipTuning", "End");
		CloseQuestHeader("ShipTuning");
		notification("Вы узнали много нового о строении корабля!", "none");
		AddCharacterExpToSkill(pchar, SKILL_COMMERCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;

	////////////////////////////////////////// SpeedRate ////////////////////////////////////////////////////
	case "ship_tunning_SpeedRate":
		Material = GetMaterialQtyUpgrade(pchar, NPChar, 1);
		WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2);
		s2 = "Veamos qué podemos hacer. En este momento la velocidad de su nave es de " + stf(RealShips[sti(Pchar.Ship.Type)].SpeedRate);
		s2 = s2 + " nudos. Para sustituir las velas necesitaré: Seda para velas, " + Material + ".";
		s2 = s2 + " Como pago por mi trabajo pido: " + WorkPrice + " cofres de doblones para cubrir mis gastos. Eso es todo. Ah, el dinero será por adelantado.";
		dialog.Text = s2;
		Link.l1 = "Acordado. Acepto tus términos. Te traeré lo que necesites.";
		Link.l1.go = "ship_tunning_SpeedRate_start";
		Link.l2 = "No. Eso no me conviene.";
		Link.l2.go = "ship_tunning_not_now_1";
		break;

	case "ship_tunning_SpeedRate_start":
		amount = GetMaterialQtyUpgrade(pchar, NPChar, 2);
		// belamour legendary edition туда сюда бегать - та еще морока -->
		if (GetCharacterItem(pchar, "chest") + CheckItemMyCabin("chest") >= amount)
		{
			if (GetCharacterItem(pchar, "chest") >= amount)
			{
				TakeNItems(pchar, "chest", -amount);
			}
			else
			{
				iSumm = amount - sti(GetCharacterItem(pchar, "chest"));
				TakeNItems(pchar, "chest", -sti(GetCharacterItem(pchar, "chest")));
				GetItemMyCabin("chest", iSumm);
				Log_Info("Cofres retirados del camarote: " + iSumm + " und.");
			}
			// <-- legendary edtion
			NPChar.Tuning.Money = amount;
			NPChar.Tuning.Matherial = GetMaterialQtyUpgrade(pchar, NPChar, 1);
			NPChar.Tuning.ShipType = Pchar.Ship.Type;
			NPChar.Tuning.ShipName = RealShips[sti(Pchar.Ship.Type)].BaseName;
			NextDiag.TempNode = "ship_tunning_SpeedRate_again";
			dialog.text = "Excelente. Estaré esperando el material.";
			link.l1 = LinkRandPhrase("Te aseguro que no tendrás que esperar mucho. Puedo resolver tales asuntos, ¿de acuerdo?", "Considera que ya los tienes y reserva el muelle para mí. Seré tan rápido como el viento.", "Por supuesto. Solo tendré que visitar a un par de personas que tienen lo que pediste, ¡ja, ja!");
			link.l1.go = "Exit";
			ReOpenQuestHeader("ShipTuning");
			AddQuestRecord("ShipTuning", "t1");
			AddQuestUserData("ShipTuning", "sText", "Por mi trabajo para aumentar la velocidad a " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " del '" + pchar.ship.name + "'" + " el astillero requiere: Seda de barco, " + NPChar.Tuning.Matherial + ". Como un depósito de " + NPChar.Tuning.Money + " cofres con doblones.");
		}
		else
		{
			NextDiag.TempNode = "ship_tunning_not_now_1";
			dialog.text = "No veo el depósito...";
			link.l1 = "Pasaré más tarde.";
			link.l1.go = "Exit";
		}
		break;

	case "ship_tunning_SpeedRate_again":
		if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		{
			NextDiag.TempNode = "ship_tunning_SpeedRate_again";
			dialog.Text = "El tiempo pasa, y el barco está esperando. ¿Has traído todo lo que pedí?";
			Link.l1 = "Sí, logré encontrar algo.";
			Link.l1.go = "ship_tunning_SpeedRate_again_2";
			Link.l2 = "No, todavía estoy en ello.";
			Link.l2.go = "Exit";
		}
		else
		{
			DeleteAttribute(NPChar, "Tuning");
			NextDiag.TempNode = "First time";
			dialog.Text = "Señor" + GetSexPhrase("", "ita") + ", ¿has cambiado tu barco desde que hicimos nuestro arreglo? No deberías haberlo hecho.";
			Link.l1 = "¡Ay, son todas las circunstancias! Lástima que el depósito se perdió...";
			Link.l1.go = "Exit";
			DeleteAttribute(pchar, "achievment.Tuning");
			AddQuestRecord("ShipTuning", "Lose");
			CloseQuestHeader("ShipTuning");
		}
		break;

	case "ship_tunning_SpeedRate_again_2":
		checkMatherial(Pchar, NPChar, GOOD_SHIPSILK);
		if (sti(NPChar.Tuning.Matherial) < 1)
		{
			DeleteAttribute(NPChar, "Tuning");
			NextDiag.TempNode = "First time";
			dialog.text = "Excelente, ahora tengo todo lo que necesito. Empezaré a trabajar, entonces.";
			link.l1 = "Estoy esperando.";
			link.l1.go = "ship_tunning_SpeedRate_complite";
		}
		else
		{
			NextDiag.TempNode = "ship_tunning_SpeedRate_again";
			dialog.Text = "Todavía necesito: seda de barco, " + sti(NPChar.Tuning.Matherial) + ".";
			link.l1 = "Bien.";
			link.l1.go = "Exit";
			AddQuestRecord("ShipTuning", "t1");
			AddQuestUserData("ShipTuning", "sText", "Necesito que traigas: Seda de barco " + sti(NPChar.Tuning.Matherial) + ".");
		}
		break;

	case "ship_tunning_SpeedRate_complite":
		AddTimeToCurrent(6, 30);
		shTo = &RealShips[sti(Pchar.Ship.Type)];
		DeleteAttribute(NPChar, "Tuning");
		// изменим
		if(!CheckAttribute(shTo, "Bonus_SpeedRate"))
		{
			if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
			{
				shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate) * 0.65);
			}
			else
			{
				shTo.SpeedRate        = (stf(shTo.SpeedRate) + stf(shTo.SpeedRate)/5.0);
			}
		}
		else
		{
			if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
			{
				shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.35 + stf(shTo.Bonus_SpeedRate);
			}
			else
			{
				shTo.SpeedRate        = (stf(shTo.SpeedRate) - stf(shTo.Bonus_SpeedRate)) * 1.2 + stf(shTo.Bonus_SpeedRate);
			}
		}
		shTo.Tuning.SpeedRate = true;

		if (!CheckAttribute(pchar, "achievment.Tuning.stage1") && CheckAttribute(shTo, "Bonus_SpeedRate") && CheckAttribute(shTo, "Tuning.WindAgainst"))
		{
			pchar.achievment.Tuning.stage1 = true;
		}
		TuningAvailable();
		NextDiag.TempNode = "First time";
		dialog.Text = "... Todo está listo, Capitán. Atrapa el viento a toda vela. ¡Compruébalo si lo deseas!";
		Link.l1 = "¡Gracias! Lo probaré.";
		Link.l1.go = "Exit";
		AddQuestRecord("ShipTuning", "End");
		CloseQuestHeader("ShipTuning");
		notification("Вы узнали много нового о строении корабля!", "none");
		AddCharacterExpToSkill(pchar, SKILL_SAILING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;

	////////////////////////////////////////// TurnRate ////////////////////////////////////////////////////
	case "ship_tunning_TurnRate":
		Material = GetMaterialQtyUpgrade(pchar, NPChar, 1);
		WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2);
		s2 = "Veamos qué podemos hacer, entonces. De momento la maniobrabilidad de su nave es de " + stf(RealShips[sti(Pchar.Ship.Type)].TurnRate);
		s2 = s2 + " Para añadir nuevas velas que lo mejoren necesitaré: Cuerdas, " + Material + ".";
		s2 = s2 + " Como pago por mi trabajo pido: " + WorkPrice + " cofres de doblones para cubrir mis gastos. Eso es todo. Ah, el dinero será por adelantado.";
		dialog.Text = s2;
		Link.l1 = "Acordado. Acepto tus términos. Te traeré lo que necesites.";
		Link.l1.go = "ship_tunning_TurnRate_start";
		Link.l2 = "No. Eso no me conviene.";
		Link.l2.go = "ship_tunning_not_now_1";
		break;

	case "ship_tunning_TurnRate_start":
		amount = GetMaterialQtyUpgrade(pchar, NPChar, 2);
		// belamour legendary edition туда сюда бегать - та еще морока
		if (GetCharacterItem(pchar, "chest") + CheckItemMyCabin("chest") >= amount)
		{
			if (GetCharacterItem(pchar, "chest") >= amount)
			{
				TakeNItems(pchar, "chest", -amount);
			}
			else
			{
				iSumm = amount - sti(GetCharacterItem(pchar, "chest"));
				TakeNItems(pchar, "chest", -sti(GetCharacterItem(pchar, "chest")));
				GetItemMyCabin("chest", iSumm);
				Log_Info("Cofres retirados del camarote: " + iSumm + " und.");
			}
			// <-- legendary edtion
			NPChar.Tuning.Money = amount;
			NPChar.Tuning.Matherial = GetMaterialQtyUpgrade(pchar, NPChar, 1);
			NPChar.Tuning.ShipType = Pchar.Ship.Type;
			NPChar.Tuning.ShipName = RealShips[sti(Pchar.Ship.Type)].BaseName;
			NextDiag.TempNode = "ship_tunning_TurnRate_again";
			dialog.text = "Excelente. Estaré esperando el material.";
			link.l1 = LinkRandPhrase("Te aseguro que no tendrás que esperar mucho. Puedo resolver tales asuntos, ¿de acuerdo?", "Considera que ya los tienes y reserva el muelle para mí. Seré tan rápido como el viento.", "Por supuesto. Solo tendré que visitar a un par de personas que tienen las cosas que solicitaste, ¡ja-ja!");
			link.l1.go = "Exit";
			ReOpenQuestHeader("ShipTuning");
			AddQuestRecord("ShipTuning", "t1");
			AddQuestUserData("ShipTuning", "sText", "Por su trabajo para aumentar la agilidad " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" + " el astillero requiere: Cuerdas, " + NPChar.Tuning.Matherial + ". Se me abonará una fianza por adelantado por importe de  " + NPChar.Tuning.Money + " cofres con doblones.");
		}
		else
		{
			NextDiag.TempNode = "ship_tunning_not_now_1";
			dialog.text = "No veo el depósito...";
			link.l1 = "Pasaré más tarde.";
			link.l1.go = "Exit";
		}
		break;

	case "ship_tunning_TurnRate_again":
		if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		{
			NextDiag.TempNode = "ship_tunning_TurnRate_again";
			dialog.Text = "El tiempo pasa, y el barco está esperando. ¿Has traído todo lo que pedí?";
			Link.l1 = "Sí, logré entregar algo.";
			Link.l1.go = "ship_tunning_TurnRate_again_2";
			Link.l2 = "No, todavía estoy en ello.";
			Link.l2.go = "Exit";
		}
		else
		{
			DeleteAttribute(NPChar, "Tuning");
			NextDiag.TempNode = "First time";
			dialog.Text = "Señor" + GetSexPhrase("", "ita") + ", ¿has cambiado tu barco desde que hicimos nuestro arreglo? No deberías haberlo hecho.";
			Link.l1 = "¡Ay, son todas las circunstancias! Lástima que se perdiera el depósito...";
			Link.l1.go = "Exit";
			DeleteAttribute(pchar, "achievment.Tuning");
			AddQuestRecord("ShipTuning", "Lose");
			CloseQuestHeader("ShipTuning");
		}
		break;

	case "ship_tunning_TurnRate_again_2":
		checkMatherial(Pchar, NPChar, GOOD_ROPES);
		if (sti(NPChar.Tuning.Matherial) < 1)
		{
			DeleteAttribute(NPChar, "Tuning");
			NextDiag.TempNode = "First time";
			dialog.text = "Excelente, ahora tengo todo lo que necesito. Empezaré a trabajar, entonces.";
			link.l1 = "Estoy esperando.";
			link.l1.go = "ship_tunning_TurnRate_complite";
		}
		else
		{
			NextDiag.TempNode = "ship_tunning_TurnRate_again";
			dialog.Text = "Todavía necesito: cuerdas, " + sti(NPChar.Tuning.Matherial) + ".";
			link.l1 = "Bien.";
			link.l1.go = "Exit";
			AddQuestRecord("ShipTuning", "t1");
			AddQuestUserData("ShipTuning", "sText", "Necesito que traigas: Cuerdas " + sti(NPChar.Tuning.Matherial) + ".");
		}
		break;

	case "ship_tunning_TurnRate_complite":
		AddTimeToCurrent(6, 30);
		shTo = &RealShips[sti(Pchar.Ship.Type)];
		DeleteAttribute(NPChar, "Tuning");
		// изменим
		if (!CheckAttribute(shTo, "Bonus_TurnRate"))
		{
			shTo.TurnRate = (stf(shTo.TurnRate) + stf(shTo.TurnRate) / 5.0);
		}
		else
		{
			shTo.TurnRate = (stf(shTo.TurnRate) - stf(shTo.Bonus_TurnRate)) * 1.2 + stf(shTo.Bonus_TurnRate);
		}

		shTo.Tuning.TurnRate = true;
		if (!CheckAttribute(pchar, "achievment.Tuning.stage4") && CheckAttribute(shTo, "Tuning.TurnRate") && CheckAttribute(shTo, "Tuning.MinCrew"))
		{
			pchar.achievment.Tuning.stage4 = true;
		}
		TuningAvailable();
		dialog.Text = "... Todo debería estar listo ahora... ¡Comprueba el timón ahora, Capitán!";
		Link.l1 = "¡Gracias! Lo probaré.";
		Link.l1.go = "Exit";
		AddQuestRecord("ShipTuning", "End");
		CloseQuestHeader("ShipTuning");
		break;

	////////////////////////////////////////// MaxCrew ////////////////////////////////////////////////////
	case "ship_tunning_MaxCrew":
		Material = GetMaterialQtyUpgrade(pchar, NPChar, 1);
		WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2);
		s2 = "Veamos qué podemos hacer, entonces. Por el momento, el número máximo de marineros en su tripulación, incluyendo la sobrecarga, es de " + sti(RealShips[sti(Pchar.Ship.Type)].MaxCrew) + " hombres.";
		s2 = s2 + " Necesitaré: Sándalo, " + Material + ".";
		s2 = s2 + " Como pago por mi trabajo pido: " + WorkPrice + " cofres de doblones para cubrir mis gastos. Eso es todo. Ah, el dinero será por adelantado.";
		dialog.Text = s2;
		Link.l1 = "Acordado. Acepto tus términos. Te traeré lo que necesites.";
		Link.l1.go = "ship_tunning_MaxCrew_start";
		Link.l2 = "No. Eso no me conviene.";
		Link.l2.go = "ship_tunning_not_now_1";
		break;

	case "ship_tunning_MaxCrew_start":
		amount = GetMaterialQtyUpgrade(pchar, NPChar, 2);
		// belamour legendary edition туда сюда бегать - та еще морока -->
		if (GetCharacterItem(pchar, "chest") + CheckItemMyCabin("chest") >= amount)
		{
			if (GetCharacterItem(pchar, "chest") >= amount)
			{
				TakeNItems(pchar, "chest", -amount);
			}
			else
			{
				iSumm = amount - sti(GetCharacterItem(pchar, "chest"));
				TakeNItems(pchar, "chest", -sti(GetCharacterItem(pchar, "chest")));
				GetItemMyCabin("chest", iSumm);
				Log_Info("Cofres retirados del camarote: " + iSumm + " und.");
			}
			// <-- legendary edtion
			NPChar.Tuning.Money = amount;
			NPChar.Tuning.Matherial = GetMaterialQtyUpgrade(pchar, NPChar, 1);
			NPChar.Tuning.ShipType = Pchar.Ship.Type;
			NPChar.Tuning.ShipName = RealShips[sti(Pchar.Ship.Type)].BaseName;
			NextDiag.TempNode = "ship_tunning_MaxCrew_again";
			dialog.text = "Excelente. Estaré esperando el material.";
			link.l1 = LinkRandPhrase("Te aseguro que no tendrás que esperar mucho. Puedo resolver tales problemas, ¿de acuerdo?", "Considera que ya los tienes y reserva el muelle para mí. Seré tan rápido como el viento.", "Por supuesto. Solo tendré que visitar a un par de personas que tienen las cosas que solicitaste, ¡ja-ja!");
			link.l1.go = "Exit";
			ReOpenQuestHeader("ShipTuning");
			AddQuestRecord("ShipTuning", "t1");
			AddQuestUserData("ShipTuning", "sText", "Por sus esfuerzos para aumentar la tripulación del " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" + " el  astillero requiere: Sándalo, " + NPChar.Tuning.Matherial + ". Se me abonará una fianza por adelantado por importe de " + NPChar.Tuning.Money + " cofres con doblones.");
		}
		else
		{
			NextDiag.TempNode = "ship_tunning_not_now_1";
			dialog.text = "No veo el depósito...";
			link.l1 = "Pasaré más tarde.";
			link.l1.go = "Exit";
		}
		break;

	case "ship_tunning_MaxCrew_again":
		if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		{
			NextDiag.TempNode = "ship_tunning_MaxCrew_again";
			dialog.Text = "El tiempo pasa, y el barco está esperando. ¿Has traído todo lo que pedí?";
			Link.l1 = "Sí, logré encontrar algo.";
			Link.l1.go = "ship_tunning_MaxCrew_again_2";
			Link.l2 = "No, todavía estoy en eso.";
			Link.l2.go = "Exit";
		}
		else
		{
			DeleteAttribute(NPChar, "Tuning");
			NextDiag.TempNode = "First time";
			dialog.Text = "Señor" + GetSexPhrase("", "ita") + ", ¿has cambiado tu barco desde que hicimos nuestro acuerdo? No deberías haberlo hecho.";
			Link.l1 = "¡Ay, son todas las circunstancias! Lástima que el depósito se haya perdido...";
			Link.l1.go = "Exit";
			DeleteAttribute(pchar, "achievment.Tuning");
			AddQuestRecord("ShipTuning", "Lose");
			CloseQuestHeader("ShipTuning");
		}
		break;

	case "ship_tunning_MaxCrew_again_2":
		checkMatherial(Pchar, NPChar, GOOD_SANDAL);
		if (sti(NPChar.Tuning.Matherial) < 1)
		{
			DeleteAttribute(NPChar, "Tuning");
			NextDiag.TempNode = "First time";
			dialog.text = "Excelente, ahora tengo todo lo que necesito. Empezaré a trabajar, entonces.";
			link.l1 = "Estoy esperando.";
			link.l1.go = "ship_tunning_MaxCrew_complite";
		}
		else
		{
			NextDiag.TempNode = "ship_tunning_MaxCrew_again";
			dialog.Text = "Todavía necesito: sándalo, " + sti(NPChar.Tuning.Matherial) + ".";
			link.l1 = "Bien.";
			link.l1.go = "Exit";
			AddQuestRecord("ShipTuning", "t1");
			AddQuestUserData("ShipTuning", "sText", "Necesito que traigas: Sándalo " + sti(NPChar.Tuning.Matherial) + ".");
		}
		break;

	case "ship_tunning_MaxCrew_complite":
		AddTimeToCurrent(6, 30);
		shTo = &RealShips[sti(Pchar.Ship.Type)];
		DeleteAttribute(NPChar, "Tuning");

		if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
		{
			shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew) * 0.65);
		}
		else
		{
			shTo.MaxCrew        = sti(shTo.MaxCrew) + makeint(sti(shTo.MaxCrew)/5);
		}
		shTo.Tuning.MaxCrew = true;
		if (!CheckAttribute(pchar, "achievment.Tuning.stage3") && CheckAttribute(shTo, "Tuning.MaxCrew") && CheckAttribute(shTo, "Tuning.HP"))

		{
			pchar.achievment.Tuning.stage3 = true;
		}
		TuningAvailable();
		NextDiag.TempNode = "First time";
		dialog.Text = "... Está hecho, Capitán. Ahora puede contratar más marineros, habrá suficiente espacio para todos.";
		Link.l1 = "¡Gracias! Lo probaré.";
		Link.l1.go = "Exit";

		AddQuestRecord("ShipTuning", "End");
		CloseQuestHeader("ShipTuning");
		notification("Вы узнали много нового о строении корабля!", "none");
		AddCharacterExpToSkill(pchar, SKILL_DEFENCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;

	////////////////////////////////////////// MinCrew ////////////////////////////////////////////////////
	case "ship_tunning_MinCrew":
		Material = GetMaterialQtyUpgrade(pchar, NPChar, 1);
		WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2);
		s2 = "Veamos qué podemos hacer, entonces. Por el momento, el número mínimo de marineros necesarios en su tripulación es de " + sti(RealShips[sti(Pchar.Ship.Type)].MinCrew) + " hombres.";
		s2 = s2 + " Para mejorar el control del barco y reducir el número necesario de marineros en la tripulación necesitaré: Cuerdas, " + Material + ".";
		s2 = s2 + " Como pago por mi trabajo pido: " + WorkPrice + " cofres de doblones para cubrir mis gastos. Eso es todo. Ah, el dinero será por adelantado.";
		dialog.Text = s2;
		Link.l1 = "De acuerdo. Acepto tus términos. Te traeré lo que necesites.";
		Link.l1.go = "ship_tunning_MinCrew_start";
		Link.l2 = "No. Eso no me conviene.";
		Link.l2.go = "ship_tunning_not_now_1";
		break;

	case "ship_tunning_MinCrew_start":
		amount = GetMaterialQtyUpgrade(pchar, NPChar, 2);
		// belamour legendary edition туда сюда бегать - та еще морока -->
		if (GetCharacterItem(pchar, "chest") + CheckItemMyCabin("chest") >= amount)
		{
			if (GetCharacterItem(pchar, "chest") >= amount)
			{
				TakeNItems(pchar, "chest", -amount);
			}
			else
			{
				iSumm = amount - sti(GetCharacterItem(pchar, "chest"));
				TakeNItems(pchar, "chest", -sti(GetCharacterItem(pchar, "chest")));
				GetItemMyCabin("chest", iSumm);
				Log_Info("Cofres retirados del camarote: " + iSumm + " und.");
			}
			// <-- legendary edtion
			NPChar.Tuning.Money = amount;
			NPChar.Tuning.Matherial = GetMaterialQtyUpgrade(pchar, NPChar, 1);
			NPChar.Tuning.ShipType = Pchar.Ship.Type;
			NPChar.Tuning.ShipName = RealShips[sti(Pchar.Ship.Type)].BaseName;
			NextDiag.TempNode = "ship_tunning_MinCrew_again";
			dialog.text = "Excelente. Estaré esperando el material.";
			link.l1 = LinkRandPhrase("Te aseguro que no tendrás que esperar mucho. Puedo resolver tales problemas, ¿de acuerdo?", "Considera que ya los tienes y reserva el muelle para mí. Seré rápido como el viento.", "Por supuesto. Solo tendré que visitar a un par de personas que tienen las cosas que pediste, ¡ja, ja!");
			link.l1.go = "Exit";
			ReOpenQuestHeader("ShipTuning");
			AddQuestRecord("ShipTuning", "t1");
			AddQuestUserData("ShipTuning", "sText", "Por su trabajo para reducir el número mínimo requerido de tripulantes en " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" + " el astillero requiere: Cuerdas, " + NPChar.Tuning.Matherial + ". Se me abonará una fianza por adelantado por importe de " + NPChar.Tuning.Money + " cofres con doblones.");
		}
		else
		{
			NextDiag.TempNode = "ship_tunning_not_now_1";
			dialog.text = "No veo el depósito...";
			link.l1 = "Volveré más tarde.";
			link.l1.go = "Exit";
		}
		break;

	case "ship_tunning_MinCrew_again":
		if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		{
			NextDiag.TempNode = "ship_tunning_MinCrew_again";
			dialog.Text = "El tiempo pasa, y el barco está esperando. ¿Has traído todo lo que pedí?";
			Link.l1 = "Sí, logré encontrar algo.";
			Link.l1.go = "ship_tunning_MinCrew_again_2";
			Link.l2 = "No, todavía estoy en ello.";
			Link.l2.go = "Exit";
		}
		else
		{
			DeleteAttribute(NPChar, "Tuning");
			NextDiag.TempNode = "First time";
			dialog.Text = "Señor" + GetSexPhrase("", "ita") + ", ¿has cambiado tu barco desde que hicimos nuestro arreglo? No deberías haberlo hecho.";
			Link.l1 = "¡Ay, son todas las circunstancias! Lástima que el depósito se perdió...";
			Link.l1.go = "Exit";
			DeleteAttribute(pchar, "achievment.Tuning");
			AddQuestRecord("ShipTuning", "Lose");
			CloseQuestHeader("ShipTuning");
		}
		break;

	case "ship_tunning_MinCrew_again_2":
		checkMatherial(Pchar, NPChar, GOOD_ROPES);
		if (sti(NPChar.Tuning.Matherial) < 1)
		{
			DeleteAttribute(NPChar, "Tuning");
			NextDiag.TempNode = "First time";
			dialog.text = "Excelente, ahora tengo todo lo que necesito. Empezaré a trabajar, entonces.";
			link.l1 = "Estoy esperando.";
			link.l1.go = "ship_tunning_MinCrew_complite";
		}
		else
		{
			NextDiag.TempNode = "ship_tunning_MinCrew_again";
			dialog.Text = "Todavía necesito: cuerdas, " + sti(NPChar.Tuning.Matherial) + ".";
			link.l1 = "Bien.";
			link.l1.go = "Exit";
			AddQuestRecord("ShipTuning", "t1");
			AddQuestUserData("ShipTuning", "sText", "Necesito que traigas: Cuerdas " + sti(NPChar.Tuning.Matherial) + ".");
		}
		break;

	case "ship_tunning_MinCrew_complite":
		AddTimeToCurrent(6, 30);
		shTo = &RealShips[sti(Pchar.Ship.Type)];
		DeleteAttribute(NPChar, "Tuning");
		// изменим
		if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
		{
			shTo.MinCrew        = sti(shTo.MinCrew) - makeint(sti(shTo.MinCrew) * 0.65);
		}
		else
		{
			shTo.MinCrew        = sti(shTo.MinCrew) - makeint(sti(shTo.MinCrew)/5);
		}
		if (sti(shTo.MinCrew) < 1)
			shTo.MinCrew = 1;
		shTo.Tuning.MinCrew = true;

		if (!CheckAttribute(pchar, "achievment.Tuning.stage4") && CheckAttribute(shTo, "Tuning.TurnRate") && CheckAttribute(shTo, "Tuning.MinCrew"))
		{
			pchar.achievment.Tuning.stage4 = true;
		}
		TuningAvailable();
		NextDiag.TempNode = "First time";
		dialog.Text = "... ¡Listo, Capitán! Ahora menos marineros pueden manejar el barco con el mismo resultado general.";
		Link.l1 = "¡Gracias! Lo probaré.";
		Link.l1.go = "Exit";

		AddQuestRecord("ShipTuning", "End");
		CloseQuestHeader("ShipTuning");
		notification("Вы узнали много нового о строении корабля!", "none");
		AddCharacterExpToSkill(pchar, SKILL_DEFENCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		AddCharacterExpToSkill(pchar, SKILL_GRAPPLING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;

	////////////////////////////////////////// HP ////////////////////////////////////////////////////
	case "ship_tunning_HP":
		Material = GetMaterialQtyUpgrade(pchar, NPChar, 1);
		WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2);
		s2 = "Veamos qué podemos hacer, entonces. En este momento el casco de la nave es de " + sti(RealShips[sti(Pchar.Ship.Type)].HP);
		s2 = s2 + ". Para reforzar el casco, necesitaré: Resina, " + Material + ".";
		s2 = s2 + " Como pago por mi trabajo pido: " + WorkPrice + " cofres de doblones para cubrir mis gastos. Eso es todo. Ah, el dinero será por adelantado.";
		dialog.Text = s2;
		Link.l1 = "Acordado. Acepto tus términos. Te traeré lo que necesites.";
		Link.l1.go = "ship_tunning_HP_start";
		Link.l2 = "No. Eso no me conviene.";
		Link.l2.go = "ship_tunning_not_now_1";
		break;

	case "ship_tunning_HP_start":
		amount = GetMaterialQtyUpgrade(pchar, NPChar, 2);
		// belamour legendary edition туда сюда бегать - та еще морока -->
		if (GetCharacterItem(pchar, "chest") + CheckItemMyCabin("chest") >= amount)
		{
			if (GetCharacterItem(pchar, "chest") >= amount)
			{
				TakeNItems(pchar, "chest", -amount);
			}
			else
			{
				iSumm = amount - sti(GetCharacterItem(pchar, "chest"));
				TakeNItems(pchar, "chest", -sti(GetCharacterItem(pchar, "chest")));
				GetItemMyCabin("chest", iSumm);
				Log_Info("Cofres retirados del camarote: " + iSumm + " und.");
			}
			// <-- legendary edtion
			NPChar.Tuning.Money = amount;
			NPChar.Tuning.Matherial = GetMaterialQtyUpgrade(pchar, NPChar, 1);
			NPChar.Tuning.ShipType = Pchar.Ship.Type;
			NPChar.Tuning.ShipName = RealShips[sti(Pchar.Ship.Type)].BaseName;
			NextDiag.TempNode = "ship_tunning_HP_again";
			dialog.text = "Excelente. Estaré esperando el material.";
			link.l1 = LinkRandPhrase("Te aseguro que no tendrás que esperar mucho. Puedo resolver tales asuntos, ¿de acuerdo?", "Considera que ya los tienes y reserva el muelle para mí. Seré tan rápido como el viento.", "Por supuesto. Solo tendré que visitar a un par de personas que tienen las cosas que pediste, ¡ja, ja!");
			link.l1.go = "Exit";
			ReOpenQuestHeader("ShipTuning");
			AddQuestRecord("ShipTuning", "t1");
			AddQuestUserData("ShipTuning", "sText", "Por sus esfuerzos para aumentar la resistencia del casco " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" + " el astillero requiere: Resina, " + NPChar.Tuning.Matherial + ". Se me abonará una fianza por adelantado por importe de " + NPChar.Tuning.Money + " cofres con doblones.");
		}
		else
		{
			NextDiag.TempNode = "ship_tunning_not_now_1";
			dialog.text = "No veo el depósito...";
			link.l1 = "Pasaré más tarde.";
			link.l1.go = "Exit";
		}
		break;

	case "ship_tunning_HP_again":
		if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		{
			NextDiag.TempNode = "ship_tunning_HP_again";
			dialog.Text = "El tiempo pasa, y el barco espera. ¿Has traído todo lo que pedí?";
			Link.l1 = "Sí, logré encontrar algo.";
			Link.l1.go = "ship_tunning_HP_again_2";
			Link.l2 = "No, todavía estoy en ello.";
			Link.l2.go = "Exit";
		}
		else
		{
			DeleteAttribute(NPChar, "Tuning");
			NextDiag.TempNode = "First time";
			dialog.Text = "Señor" + GetSexPhrase("", "ita") + ", ¿has cambiado tu barco desde que hicimos nuestro arreglo? No deberías haberlo hecho.";
			Link.l1 = "¡Ay, son todas las circunstancias! Lástima que el depósito se haya perdido...";
			Link.l1.go = "Exit";
			DeleteAttribute(pchar, "achievment.Tuning");
			AddQuestRecord("ShipTuning", "Lose");
			CloseQuestHeader("ShipTuning");
		}
		break;

	case "ship_tunning_HP_again_2":
		checkMatherial(Pchar, NPChar, GOOD_OIL);
		if (sti(NPChar.Tuning.Matherial) < 1)
		{
			DeleteAttribute(NPChar, "Tuning");
			NextDiag.TempNode = "First time";
			dialog.text = "Excelente, ahora tengo todo lo que necesito. Empezaré a trabajar, entonces.";
			link.l1 = "Estoy esperando.";
			link.l1.go = "ship_tunning_HP_complite";
		}
		else
		{
			NextDiag.TempNode = "ship_tunning_HP_again";
			dialog.Text = "Todavía requiero: resina, " + sti(NPChar.Tuning.Matherial) + ".";
			link.l1 = "Bien.";
			link.l1.go = "Exit";
			AddQuestRecord("ShipTuning", "t1");
			AddQuestUserData("ShipTuning", "sText", "Necesito que traigas: Resina " + sti(NPChar.Tuning.Matherial) + ".");
		}
		break;

	case "ship_tunning_HP_complite":
		AddTimeToCurrent(6, 30);
		shTo = &RealShips[sti(Pchar.Ship.Type)];
		DeleteAttribute(NPChar, "Tuning");
		// изменим
		if(!CheckAttribute(shTo, "Bonus_HP"))
		{
			if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
			{
				shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP) * 0.65);
			}
			else
			{
				shTo.HP        = sti(shTo.HP) + makeint(sti(shTo.HP)/5);
			}
		}
		else
		{
			if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
			{
				shTo.HP        = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.35 + sti(shTo.Bonus_HP));
			}
			else
			{
				shTo.HP        = makeint((sti(shTo.HP) - sti(shTo.Bonus_HP)) * 1.2 + sti(shTo.Bonus_HP));
			}
		}
		shTo.Tuning.HP = true;
		shTo.BaseHP = sti(shTo.HP);

		if (!CheckAttribute(pchar, "achievment.Tuning.stage3") && CheckAttribute(shTo, "Tuning.MaxCrew") && CheckAttribute(shTo, "Tuning.HP"))
		{
			pchar.achievment.Tuning.stage3 = true;
		}
		TuningAvailable();
		NextDiag.TempNode = "First time";

		dialog.Text = "... Eso debería bastar... ¡Garantizo que a partir de ahora tus enemigos tendrán mucho más difícil destrozar el casco de tu barco!";
		Link.l1 = "Heh, ¡te tomaré la palabra! Gracias, maestro.";
		Link.l1.go = "Exit";

		AddQuestRecord("ShipTuning", "End");
		CloseQuestHeader("ShipTuning");
		notification("Вы узнали много нового о строении корабля!", "none");
		AddCharacterExpToSkill(pchar, SKILL_DEFENCE, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		AddCharacterExpToSkill(pchar, SKILL_REPAIR, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;

	////////////////////////////////////////// WindAgainst ////////////////////////////////////////////////////
	case "ship_tunning_WindAgainst":
		Material = GetMaterialQtyUpgrade(pchar, NPChar, 1);
		WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2);
		fTmp = 180.0 - (acos(1 - stf(RealShips[sti(Pchar.Ship.Type)].WindAgainstSpeed)) * 180.0/PI);
		s2 = "Veamos qué podemos hacer, entonces. En este momento el ángulo de la vela contra el viento es de " + makeint(fTmp) + " grados.";
		// belamour legendary edition если спускать курс по ветру, то это даунгрейд
		s2 = s2 + " Para acelerar el barco a barlovento, necesitaré: Seda del barco, " + Material + ",";
		s2 = s2 + " Como pago por mi trabajo pido: " + WorkPrice + " cofres de doblones para cubrir mis gastos. Eso es todo. Ah, el dinero será por adelantado.";
		dialog.Text = s2;
		Link.l1 = "De acuerdo. Acepto tus términos. Te traeré lo que necesites.";
		Link.l1.go = "ship_tunning_WindAgainst_start";
		Link.l2 = "No. Eso no me conviene.";
		Link.l2.go = "ship_tunning_not_now_1";
		break;

	case "ship_tunning_WindAgainst_start":
		amount = GetMaterialQtyUpgrade(pchar, NPChar, 2);
		// belamour legendary edition туда сюда бегать - та еще морока -->
		if (GetCharacterItem(pchar, "chest") + CheckItemMyCabin("chest") >= amount)
		{
			if (GetCharacterItem(pchar, "chest") >= amount)
			{
				TakeNItems(pchar, "chest", -amount);
			}
			else
			{
				iSumm = amount - sti(GetCharacterItem(pchar, "chest"));
				TakeNItems(pchar, "chest", -sti(GetCharacterItem(pchar, "chest")));
				GetItemMyCabin("chest", iSumm);
				Log_Info("Cofres retirados del camarote: " + iSumm + " und.");
			}
			// <-- legendary edtion
			NPChar.Tuning.Money = amount;
			NPChar.Tuning.Matherial = GetMaterialQtyUpgrade(pchar, NPChar, 1);
			NPChar.Tuning.ShipType = Pchar.Ship.Type;
			NPChar.Tuning.ShipName = RealShips[sti(Pchar.Ship.Type)].BaseName;
			NextDiag.TempNode = "ship_tunning_WindAgainst_again";
			dialog.text = "Excelente. Estaré esperando el material.";
			link.l1 = LinkRandPhrase("Te aseguro que no tendrás que esperar mucho. Puedo resolver tales problemas, ¿de acuerdo?", "Considera que ya los tienes y reserva el muelle para mí. Seré tan rápido como el viento.", "Por supuesto. Solo tendré que visitar a un par de personas que tienen lo que pediste, ¡ja, ja!");
			link.l1.go = "Exit";

			ReOpenQuestHeader("ShipTuning");
			AddQuestRecord("ShipTuning", "t1");
			AddQuestUserData("ShipTuning", "sText", "Por su trabajo sobre el cambio del ángulo del viento de " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" + " el astillero requiere: Seda de barco, " + NPChar.Tuning.Matherial + ". Se me abonará una fianza por adelantado por importe de " + NPChar.Tuning.Money + " cofres con doblones.");
		}
		else
		{
			NextDiag.TempNode = "ship_tunning_not_now_1";
			dialog.text = "No veo el depósito...";
			link.l1 = "Pasaré más tarde.";
			link.l1.go = "Exit";
		}
		break;

	case "ship_tunning_WindAgainst_again":
		if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		{
			NextDiag.TempNode = "ship_tunning_WindAgainst_again";
			dialog.Text = "El tiempo pasa, y el barco está esperando. ¿Has traído todo lo que pedí?";
			Link.l1 = "Sí, logré entregar algo.";
			Link.l1.go = "ship_tunning_WindAgainst_again_2";
			Link.l2 = "No, todavía estoy en ello.";
			Link.l2.go = "Exit";
		}
		else
		{
			DeleteAttribute(NPChar, "Tuning");
			NextDiag.TempNode = "First time";
			dialog.Text = "Señor" + GetSexPhrase("", "ita") + ", ¿has cambiado de barco desde que hicimos nuestro acuerdo? No deberías haberlo hecho.";
			Link.l1 = "¡Ay, son todas las circunstancias! Lástima que el depósito se perdió...";
			Link.l1.go = "Exit";
			DeleteAttribute(pchar, "achievment.Tuning");
			AddQuestRecord("ShipTuning", "Lose");
			CloseQuestHeader("ShipTuning");
		}
		break;

	case "ship_tunning_WindAgainst_again_2":
		checkMatherial(Pchar, NPChar, GOOD_SHIPSILK);
		if (sti(NPChar.Tuning.Matherial) < 1)
		{
			DeleteAttribute(NPChar, "Tuning");
			NextDiag.TempNode = "First time";
			dialog.text = "Excelente, ahora tengo todo lo que necesito. Entonces, comenzaré a trabajar.";
			link.l1 = "Estoy esperando.";
			link.l1.go = "ship_tunning_WindAgainst_complite";
		}
		else
		{
			NextDiag.TempNode = "ship_tunning_WindAgainst_again";
			dialog.Text = "Aún necesito: seda para el barco, " + sti(NPChar.Tuning.Matherial) + ".";
			link.l1 = "Bien.";
			link.l1.go = "Exit";
			AddQuestRecord("ShipTuning", "t1");
			AddQuestUserData("ShipTuning", "sText", "Necesito que traigas: Seda de barco " + sti(NPChar.Tuning.Matherial) + ".");
		}
		break;

	case "ship_tunning_WindAgainst_complite":
		AddTimeToCurrent(6, 30);
		shTo = &RealShips[sti(Pchar.Ship.Type)];
		DeleteAttribute(NPChar, "Tuning");
		// изменим
		// belamour legendary edtion чем больше WindAgainstSpeed, тем круче к ветру
		if(sti(shTo.Spec) == SHIP_SPEC_UNIVERSAL)
		{
			shTo.WindAgainstSpeed   = stf(shTo.WindAgainstSpeed) + 0.35 * stf(shTo.WindAgainstSpeed);	
		}
		else
		{
			shTo.WindAgainstSpeed   = stf(shTo.WindAgainstSpeed) + 0.20 * stf(shTo.WindAgainstSpeed);
		}
		if (stf(shTo.WindAgainstSpeed) > 1.985)
			shTo.WindAgainstSpeed = 1.985;
		shTo.Tuning.WindAgainst = true;

		if (!CheckAttribute(pchar, "achievment.Tuning.stage1") && CheckAttribute(shTo, "Bonus_SpeedRate") && CheckAttribute(shTo, "Tuning.WindAgainst"))
		{
			pchar.achievment.Tuning.stage1 = true;
		}
		TuningAvailable();
		NextDiag.TempNode = "First time";
		dialog.Text = "... ¡Listo, Capitán!.. Tu barco navegará contra el viento mucho más rápido ahora.";
		Link.l1 = "¡Gracias! Lo probaré.";
		Link.l1.go = "Exit";

		AddQuestRecord("ShipTuning", "End");
		CloseQuestHeader("ShipTuning");
		notification("Вы узнали много нового о строении корабля!", "none");
		AddCharacterExpToSkill(pchar, SKILL_SAILING, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;

	////////////////////////////////////////// только количество орудий  ////////////////////////////////////////////////////
	case "ship_c_quantity":
		Material = GetMaterialQtyUpgrade(pchar, NPChar, 1);
		WorkPrice = GetMaterialQtyUpgrade(pchar, NPChar, 2);
		s2 = "A ver qué se puede hacer. En este momento, el número de cañones en su nave es de " + sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantity) + ", y el número máximo posible es de " + sti(RealShips[sti(Pchar.Ship.Type)].CannonsQuantityMax) + ".";
		s2 = s2 + " Puedo decirte desde ya que no va a ser barato. Necesitaré: Resina, " + Material + ",";
		s2 = s2 + " Como pago por mi trabajo pido: " + WorkPrice + " cofres de doblones para cubrir mis gastos. Eso es todo. Ah, el dinero será por adelantado.";
		dialog.Text = s2;
		Link.l1 = "De acuerdo. Acepto tus términos. Te traeré lo que necesites.";
		Link.l1.go = "ship_c_quantity_start";
		Link.l2 = "No. Eso no me conviene.";
		Link.l2.go = "ship_tunning_not_now_1";
		break;

	case "ship_c_quantity_start":
		amount = GetMaterialQtyUpgrade(pchar, NPChar, 2);
		// belamour legendary edition туда сюда бегать - та еще морока -->
		if (GetCharacterItem(pchar, "chest") + CheckItemMyCabin("chest") >= amount)
		{
			if (GetCharacterItem(pchar, "chest") >= amount)
			{
				TakeNItems(pchar, "chest", -amount);
			}
			else
			{
				iSumm = amount - sti(GetCharacterItem(pchar, "chest"));
				TakeNItems(pchar, "chest", -sti(GetCharacterItem(pchar, "chest")));
				GetItemMyCabin("chest", iSumm);
				Log_Info("Cofres retirados del camarote: " + iSumm + " und.");
			}
			// <-- legendary edtion
			NPChar.Tuning.Money = amount;
			NPChar.Tuning.Cannon = true;
			NPChar.Tuning.Matherial = GetMaterialQtyUpgrade(pchar, NPChar, 1);
			NPChar.Tuning.ShipType = Pchar.Ship.Type;
			NPChar.Tuning.ShipName = RealShips[sti(Pchar.Ship.Type)].BaseName;
			NextDiag.TempNode = "ship_c_quantity_again";
			dialog.text = "Excelente. Estaré esperando el material.";
			link.l1 = LinkRandPhrase("Te aseguro que no tendrás que esperar mucho tiempo. Puedo resolver tales problemas, ¿de acuerdo?", "Considera que ya los tienes y reserva el muelle para mí. Seré tan rápido como el viento.", "Por supuesto. Solo tendré que visitar a un par de personas que tienen las cosas que pediste, ¡ja, ja!");
			link.l1.go = "Exit";
			ReOpenQuestHeader("ShipTuning");
			AddQuestRecord("ShipTuning", "t1");
			AddQuestUserData("ShipTuning", "sText", "Por el trabajo de aumentar el número de cañones del " + GetStrSmallRegister(XI_ConvertString(RealShips[sti(Pchar.Ship.Type)].BaseName + "Voc")) + " '" + pchar.ship.name + "'" + " el astillero requiere: Resina, " + NPChar.Tuning.Matherial + ". Se me abonará una fianza por adelantado por importe de " + NPChar.Tuning.Money + " cofres con doblones.");
		}
		else
		{
			NextDiag.TempNode = "ship_tunning_not_now_1";
			dialog.text = "No veo el depósito...";
			link.l1 = "Pasaré más tarde.";
			link.l1.go = "Exit";
		}
		break;

	case "ship_c_quantity_again":
		if (sti(NPChar.Tuning.ShipType) == sti(Pchar.Ship.Type) && NPChar.Tuning.ShipName == RealShips[sti(Pchar.Ship.Type)].BaseName && TuningAvailable())
		{
			NextDiag.TempNode = "ship_c_quantity_again";
			dialog.Text = "El tiempo pasa, y el barco espera. ¿Has traído todo lo que pedí?";
			Link.l1 = "Sí, logré encontrar algo.";
			Link.l1.go = "ship_c_quantity_again_2";
			Link.l2 = "No, todavía estoy en ello.";
			Link.l2.go = "Exit";
		}
		else
		{
			DeleteAttribute(NPChar, "Tuning");
			NextDiag.TempNode = "First time";
			dialog.Text = "Señor" + GetSexPhrase("", "ita") + ", ¿has cambiado tu barco desde que hicimos nuestro arreglo? No deberías haberlo hecho.";
			Link.l1 = "Lástima, son todas las circunstancias! Es una pena que el depósito se haya perdido...";
			Link.l1.go = "Exit";
			DeleteAttribute(pchar, "achievment.Tuning");
			AddQuestRecord("ShipTuning", "Lose");
			CloseQuestHeader("ShipTuning");
		}
		break;

	case "ship_c_quantity_again_2":
		checkMatherial(Pchar, NPChar, GOOD_OIL);
		if (sti(NPChar.Tuning.Matherial) < 1)
		{
			DeleteAttribute(NPChar, "Tuning");
			NextDiag.TempNode = "First time";
			dialog.text = "Excelente, ahora tengo todo lo que necesito. Empezaré a trabajar, entonces.";
			link.l1 = "Estoy esperando.";
			link.l1.go = "ship_c_quantity_complite";
		}
		else
		{
			NextDiag.TempNode = "ship_c_quantity_again";
			dialog.Text = "Todavía necesito: resina, " + sti(NPChar.Tuning.Matherial) + ".";
			link.l1 = "Bien.";
			link.l1.go = "Exit";
			AddQuestRecord("ShipTuning", "t1");
			AddQuestUserData("ShipTuning", "sText", "Necesito que traigas: Resina " + sti(NPChar.Tuning.Matherial) + ".");
		}
		break;

	case "ship_c_quantity_complite":
		AddTimeToCurrent(6, 30);
		shTo = &RealShips[sti(Pchar.Ship.Type)];
		DeleteAttribute(NPChar, "Tuning");
		makearef(refShip, pchar.Ship);

		iCannonDiff = sti(refShip.CannonDiff);
		iCannonDiff -= 1;

		for (i = 0; i < sti(shTo.cannonr); i++)
		{
			attr = "c" + i;

			if (i < (sti(shTo.cannonr) - iCannonDiff))
			{
				if (stf(refShip.Cannons.Borts.cannonr.damages.(attr)) > 1.0)
				{
					refShip.Cannons.Borts.cannonr.damages.(attr) = 1.0;
				}
			}
		}
		for (i = 0; i < sti(shTo.cannonl); i++)
		{
			attr = "c" + i;
			if (i < (sti(shTo.cannonl) - iCannonDiff))
			{
				if (stf(refShip.Cannons.Borts.cannonl.damages.(attr)) > 1.0)
				{
					refShip.Cannons.Borts.cannonl.damages.(attr) = 1.0;
				}
			}
		}

		if (CheckAttribute(shTo, "CannonsQuantityMax"))
			shTo.Cannons = sti(shTo.CannonsQuantityMax) - iCannonDiff * 2;
		else
			shTo.Cannons = sti(shTo.CannonsQuantity) - iCannonDiff * 2;

		shTo.CannonsQuantity = sti(shTo.Cannons);

		refShip.Cannons = sti(shTo.Cannons);
		refShip.CannonDiff = iCannonDiff;

		shTo.Tuning.Cannon = true;

		if (!CheckAttribute(pchar, "achievment.Tuning.stage2") && CheckAttribute(shTo, "Tuning.Cannon") && CheckAttribute(shTo, "Tuning.Capacity"))
		{
			pchar.achievment.Tuning.stage2 = true;
		}
		TuningAvailable();
		NextDiag.TempNode = "First time";
		dialog.Text = "... Eso es todo, Capitán. Puedes usar cañones adicionales, es decir, si los tienes, je-je.";
		Link.l1 = "¡Gracias!";
		Link.l1.go = "Exit";

		AddQuestRecord("ShipTuning", "End");
		CloseQuestHeader("ShipTuning");
		notification("Вы узнали много нового о строении корабля!", "none");
		AddCharacterExpToSkill(pchar, SKILL_ACCURACY, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		AddCharacterExpToSkill(pchar, SKILL_CANNONS, 5.0 * makefloat(GetMaterialQtyUpgrade(pchar, NPChar, 2 )));
		break;

	case "Tasks":
		//--> Jason генератор Поиск корабля
		if (hrand(4) == 2 && !CheckAttribute(pchar, "GenQuest.Findship.Shipyarder") && sti(pchar.rank) < 19)
		{
			if (!CheckAttribute(npchar, "Findship") || GetNpcQuestPastDayParam(npchar, "Findship") >= 60)
			{
				SelectFindship_ShipType();																																							 // выбор типа корабля
				pchar.GenQuest.Findship.Shipyarder.ShipBaseName = GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Findship.Shipyarder.ShipType), "Name") + "Acc")); // new
				pchar.GenQuest.Findship.Shipyarder.City = npchar.city;																																 // город квестодателя
				dialog.text = "Tengo un asunto que necesita ser resuelto. Tengo un pedido para un barco, " + pchar.GenQuest.Findship.Shipyarder.ShipBaseName + " Sin embargo, en mi astillero no hay tal barco ahora y dentro de dos meses tampoco tengo posibilidad de conseguir uno.\nSi puedes proporcionarme tal barco, te estaré muy agradecido y te pagaré una suma una vez y media mayor que su precio de venta.";
				link.l1 = "Una oferta interesante. ¡Estoy de acuerdo!";
				link.l1.go = "Findship";
				link.l2 = "Esto no me interesa.";
				link.l2.go = "Findship_exit";
				SaveCurrentNpcQuestDateParam(npchar, "Findship");
				break;
			}

		} //<-- генератор Поиск корабля
		// Jason --> генератор Неудачливый вор
		if (hrand(6) == 1 && !CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && sti(pchar.rank) < 10 && npchar.city != "Charles")
		{
			if (!CheckAttribute(npchar, "Device"))
			{
				switch (hrand(4))
				{
				case 0:
					pchar.GenQuest.Device.Shipyarder.Type = "inside gage";
					pchar.GenQuest.Device.Shipyarder.Describe = "dos tiras martilladas, unidas con una junta no remachada en ambos extremos";
					break;
				case 1:
					pchar.GenQuest.Device.Shipyarder.Type = "Swedish broad axe";
					pchar.GenQuest.Device.Shipyarder.Describe = "un hacha de mango largo y recto con una fina hoja semicircular";
					break;
				case 2:
					pchar.GenQuest.Device.Shipyarder.Type = "groover";
					pchar.GenQuest.Device.Shipyarder.Describe = "un hacha pequeña, parecida al azadón de un granjero";
					break;
				case 3:
					pchar.GenQuest.Device.Shipyarder.Type = "stockpile level";
					pchar.GenQuest.Device.Shipyarder.Describe = "dos barras de madera de igual longitud, unidas por la misma tercera, que tiene en el centro una placa giratoria llena de líquido con una burbuja de aire";
					break;
				case 4:
					pchar.GenQuest.Device.Shipyarder.Type = "barsik";
					pchar.GenQuest.Device.Shipyarder.Describe = "un mayal normal, pero la cadena tiene forma de vara y sólo se mueve en una dirección.";
					break;
				}
				dialog.text = "Llegas justo a tiempo. Tal vez podrías ayudarme. Alguien me robó un instrumento muy valioso ayer mismo, " + pchar.GenQuest.Device.Shipyarder.Type + ". No tengo la posibilidad de hacer otro y no puedo permitirme el tiempo ni el costo de pedirlo desde Europa. Y sin él, no puedo construir barcos normalmente, ¿sabes?\nY la parte más molesta es que esta cosa no la necesita nadie excepto los constructores de barcos, y yo soy el único constructor de barcos en la colonia. Este ladrón no se lo venderá a nadie y simplemente lo tirará. Tal vez puedas intentar rastrear al ladrón, preguntar por el pueblo, pero simplemente no tengo tiempo para estar fuera del astillero, necesito completar urgentemente pedidos especiales.";
				link.l1 = "Está bien, lo intentaré. Dime, ¿cómo era ese... artefacto tuyo?";
				link.l1.go = "Device";
				link.l2 = "Esto no me interesa.";
				link.l2.go = "Device_exit";
				SaveCurrentNpcQuestDateParam(npchar, "Device");
				break;
			} //<-- генератор Неудачливый вор
		}
		dialog.text = "No tengo nada de ese tipo.";
		link.l1 = "Como usted diga.";
		link.l1.go = "exit";
		break;

	case "Findship_exit":
		DialogExit();
		DeleteAttribute(pchar, "GenQuest.Findship.Shipyarder");
		break;

	case "Device_exit":
		DialogExit();
		DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		break;

	//--> Jason генератор Поиск корабля
	case "Findship":
		pchar.GenQuest.Findship.Shipyarder = "begin";
		pchar.GenQuest.Findship.Shipyarder.Name = GetFullName(npchar);
		pchar.GenQuest.Findship.Shipyarder.City = npchar.city;
		ReOpenQuestHeader("Findship");
		AddQuestRecord("Findship", "1");
		AddQuestUserData("Findship", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Findship.Shipyarder.City + "Gen"));
		AddQuestUserData("Findship", "sName", pchar.GenQuest.Findship.Shipyarder.Name);
		AddQuestUserData("Findship", "sShip", pchar.GenQuest.Findship.Shipyarder.ShipBaseName);
		SetFunctionTimerCondition("Findship_Over", 0, 0, 60, false);
		DialogExit();
		break;

	case "Findship_check":
		dialog.text = "¡Excelente! Me alegra mucho que lo hayas logrado tan rápido. ¿Dónde está ese barco?";
		link.l1 = "En estos momentos el buque se encuentra en la rada: su nombre es '" + pchar.GenQuest.Findship.Shipyarder.ShipName + "'.";
		link.l1.go = "Findship_complete";
		break;

	case "Findship_complete":
		pchar.quest.Findship_Over.over = "yes"; // снять прерывание
		sld = GetCharacter(sti(pchar.GenQuest.Findship.Shipyarder.CompanionIndex));
		RemoveCharacterCompanion(PChar, sld);
		AddPassenger(PChar, sld, false);
		dialog.text = "Aquí está tu dinero, " + FindRussianMoneyString(sti(pchar.GenQuest.Findship.Shipyarder.Money)) + ". Gracias por el trabajo. No olvides venir a verme de nuevo. ¡Adiós!";
		link.l1 = "Adiós, " + npchar.name + ".";
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Findship.Shipyarder.Money));
		AddQuestRecord("Findship", "3");
		AddQuestUserData("Findship", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Findship.Shipyarder.Money)));
		CloseQuestHeader("Findship");
		DeleteAttribute(pchar, "GenQuest.Findship.Shipyarder");
		break;
	//<-- генератор Поиск корабля

	// Jason --> генератор Неудачливый вор
	case "Device":
		pchar.GenQuest.Device.Shipyarder.Chance1 = rand(6);
		pchar.GenQuest.Device.Shipyarder.Chance2 = rand(3);
		pchar.GenQuest.Device.Shipyarder.Chance3 = rand(2);
		pchar.GenQuest.Device.Shipyarder.Chance4 = rand(4);
		pchar.GenQuest.Device.Shipyarder.Money = 12000 + rand(8000);
		// генерируем тип корабля для бонуса сейчас, чтобы не сливали
		if (sti(pchar.rank) < 5) iType = sti(RandPhraseSimple(its(SHIP_BARKENTINE), its(SHIP_SLOOP)));
		if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 11) iType = sti(RandPhraseSimple(its(SHIP_SHNYAVA), its(SHIP_BARQUE)));
		if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 16) iType = sti(RandPhraseSimple(its(SHIP_BRIG), its(SHIP_FLEUT)));
		if (sti(pchar.rank) >= 16) iType = sti(LinkRandPhrase(its(SHIP_CORVETTE), its(SHIP_POLACRE), its(SHIP_GALEON_L)));
		pchar.GenQuest.Device.Shipyarder.Bonus = iType;
		dialog.text = "Por supuesto, trataré de explicarlo en palabras sencillas. Parece que " + pchar.GenQuest.Device.Shipyarder.Describe + ". Es único en su clase, así que lo reconocerás muy fácilmente. Si me traes ese instrumento, te pagaré generosamente.";
		link.l1 = "Entendido. ¡Empezaré mi búsqueda de inmediato!";
		link.l1.go = "exit";
		pchar.GenQuest.Device.Shipyarder = "begin";
		pchar.GenQuest.Device.Shipyarder.Name = GetFullName(npchar);
		pchar.GenQuest.Device.Shipyarder.City = npchar.city;
		pchar.GenQuest.Device.Shipyarder.Nation = npchar.Nation;
		ReOpenQuestHeader("Device");
		AddQuestRecord("Device", "1");
		AddQuestUserData("Device", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Device.Shipyarder.City + "Voc"));
		AddQuestUserData("Device", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("Device", "sName", pchar.GenQuest.Device.Shipyarder.Type);
		AddQuestUserData("Device", "sDesc", pchar.GenQuest.Device.Shipyarder.Describe);
		SetFunctionTimerCondition("Device_Over", 0, 0, 30, false);
		break;

	case "Device_complete":
		pchar.quest.Device_Over.over = "yes"; // снять прерывание
		dialog.text = "¡Lo has logrado! ¡No tienes idea de cuán agradecido estoy! Ya había perdido toda esperanza de volver a ver mi instrumento.";
		link.l1 = "Aquí tienes.";
		link.l1.go = "Device_complete_1";
		break;

	case "Device_complete_1":
		RemoveItems(PChar, "Tool", 1);
		dialog.text = "Por tus esfuerzos te pagaré " + FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Money)) + ". Espero que eso sea una recompensa merecida.";
		link.l1 = "¡Gracias!";
		link.l1.go = "Device_complete_2";
		break;

	case "Device_complete_2":
		AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Device.Shipyarder.Money));
		ChangeCharacterComplexReputation(pchar, "nobility", 5);
		AddCharacterExpToSkill(pchar, "Leadership", 100); // авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);	  // везение
		AddCharacterExpToSkill(pchar, "Sneak", 100);	  // скрытность
		AddQuestRecord("Device", "10");
		AddQuestUserData("Device", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Device.Shipyarder.Money)));
		CloseQuestHeader("Device");
		if (sti(pchar.GenQuest.Device.Shipyarder.Chance4) == 3)
		{
			dialog.text = "Aparte, me gustaría hacerle una oferta, como agradecimiento adicional.";
			link.l1 = "Eso es interesante. Bueno, adelante, me gustan las sorpresas agradables.";
			link.l1.go = "Device_complete_3";
		}
		else
		{
			DialogExit();
			DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		}
		break;

	case "Device_complete_3":
		iType = sti(pchar.GenQuest.Device.Shipyarder.Bonus);
		dialog.text = "Acabo de lanzar un nuevo barco, " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(iType, "Name") + "Acc")) + "Ya hay varios clientes para este barco, pero te daré prioridad. Si te gusta este barco y no te asusta el precio, puedes comprarlo.";
		link.l1 = "¡Je! ¡Claro, echemos un vistazo!";
		link.l1.go = "Device_complete_4";
		link.l2 = "Gracias, pero mi barco actual me queda bien, y no estoy buscando reemplazarlo.";
		link.l2.go = "Device_complete_5";
		break;

	case "Device_complete_4":
		iType = sti(pchar.GenQuest.Device.Shipyarder.Bonus);
		FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_TARTANE, NPChar), "ship1");
		FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship2");
		FillShipParamShipyard(NPChar, GenerateStoreShipExt(SHIP_LUGGER, NPChar), "ship3");
		FillShipParamShipyard(NPChar, GenerateStoreShipExt(iType, NPChar), "ship10");
		DialogExit();
		LaunchShipyard(npchar);
		DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		SaveCurrentNpcQuestDateParam(npchar, "shipyardDate"); // лесник , митрокоста
		break;

	case "Device_complete_5":
		dialog.text = "Bueno, como desees. Gracias una vez más, ¡y buena suerte!";
		link.l1 = "¡Buena suerte para ti también!";
		link.l1.go = "exit";
		DeleteAttribute(pchar, "GenQuest.Device.Shipyarder");
		break;
		// <-- генератор Неудачливый вор

	case "ShipLetters_6":
		pchar.questTemp.different.GiveShipLetters.speakShipyard = true;
		if (sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
		{
			dialog.text = "Déjame echar un vistazo... No, no hubo nadie como él. Supongo que deberías ver al maestro del puerto respecto a ese asunto.";
			link.l1 = "Por supuesto...";
			link.l1.go = "exit";
		}
		else
		{
			sTemp = "¡Déjeme echar un vistazo, capitán! ¡A-ha! ¡Esos son los documentos del barco de un buen amigo mío, mi cliente favorito! Estoy seguro de que se alegrará muchísimo por tu hallazgo y te recompensará merecidamente.";
			sTemp = sTemp + "Supongo que puedo ofrecerte " + sti(pchar.questTemp.different.GiveShipLetters.price2) + " pesos en su nombre";
			dialog.text = sTemp;
			link.l1 = "No, no lo creo...";
			link.l1.go = "exit";
			link.l2 = "Gracias, " + GetFullName(NPChar) + "¡Por favor, transmita mis respetos a su amigo!";
			link.l2.go = "ShipLetters_7";
		}
		break;

	case "ShipLetters_7":
		TakeItemFromCharacter(pchar, "CaptainBook");
		addMoneyToCharacter(pchar, sti(pchar.questTemp.different.GiveShipLetters.price2));
		pchar.questTemp.different = "free";
		pchar.quest.GiveShipLetters_null.over = "yes"; // снимаем таймер
		AddQuestRecord("GiveShipLetters", "4");
		AddQuestUserData("GiveShipLetters", "sSex", GetSexPhrase("", ""));
		CloseQuestHeader("GiveShipLetters");
		DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "EncGirl_1":
		dialog.text = "Te escucho atentamente.";
		link.l1 = "He traído a tu fugitivo.";
		link.l1.go = "EncGirl_2";
		break;

	case "EncGirl_2":
		dialog.text = "Oh, ¡Capitán, muchas gracias! ¿Cómo está ella? ¿Está herida? ¿Por qué se escapó? ¿Por qué?\n¿No lo entiende? ¡El novio es un hombre rico e importante! La juventud es ingenua y tonta... incluso cruel. ¡Recuérdalo!";
		link.l1 = "Bueno, tú eres su padre y la decisión final es tuya, pero no me apresuraría con la boda...";
		link.l1.go = "EncGirl_3";
		break;

	case "EncGirl_3":
		dialog.text = "¿Qué sabes tú? ¿Tienes tus propios hijos? ¿No? Cuando tengas uno, ven a verme y hablaremos.\nPrometí una recompensa a quien la devolviera a la familia.";
		link.l1 = "Gracias. Deberías vigilarla. Tengo el presentimiento de que no se detendrá ahí.";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;

	case "EncGirl_4":
		if (sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
		{
			dialog.text = "¿Oh, así que eres ese capitán que le ha traído a mi hijo pródigo una joven esposa?";
			link.l1 = "Sí, fui yo.";
			link.l1.go = "EncGirl_5";
		}
		else
		{
			dialog.text = "Oh, allí " + GetSexPhrase("él es, nuestro benefactor", "es, nuestra benefactora") + ". Esperando una recompensa, ¿verdad?";
			link.l1 = "Bueno, estoy bien sin recompensa, tu buena palabra será suficiente.";
			link.l1.go = "EncGirl_6";
		}
		break;

	case "EncGirl_5":
		dialog.text = "Le estoy muy agradecido por no haber abandonado a mi hijo en una situación desesperada y haberle ayudado a encontrar una salida a una situación delicada. Permítame agradecerle y, por favor, acepte esta modesta suma y un regalo de mi parte personalmente.";
		link.l1 = "Gracias. Ayudar a esta joven pareja fue un placer.";
		link.l1.go = "EncGirl_5_1";
		break;

	case "EncGirl_6":
		dialog.text = "¿Gracias? ¿Qué gracias?! ¡Hace medio año que ese cabeza de chorlito anda merodeando sin trabajo, y míralo, tiene tiempo de sobra para amoríos! ¡Cuando yo tenía su edad, ya dirigía mi propio negocio! ¡Pff! ¡Un gobernador tiene una hija casadera, y ese tonto ha traído a una cualquiera sin parientes a mi casa y se atrevió a pedir mi bendición!";
		link.l1 = "Hum... Aparentemente, ¿no crees en los sentimientos sinceros?";
		link.l1.go = "EncGirl_6_1";
		break;

	case "EncGirl_5_1":
		AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
		GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
		AddQuestRecord("JungleGirl", "18");
		CloseQuestHeader("JungleGirl");
		DeleteAttribute(pchar, "GenQuest.EncGirl");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "EncGirl_6_1":
		dialog.text = "¿Qué sentimientos? ¿De qué tipo de sentimientos hablas? Sentimientos... ¿cómo puedes ser tan frívolo a tu edad? ¡Debería darte vergüenza consentir a los jóvenes en sus caprichos y actuar como un alcahuete! No solo te llevaste a una chica de su hogar, sino que también arruinaste la vida de mi novato. No habrá agradecimientos para ti. Adiós.";
		link.l1 = "Está bien, y lo mismo para usted...";
		link.l1.go = "EncGirl_6_2";
		break;

	case "EncGirl_6_2":
		ChangeCharacterComplexReputation(pchar, "nobility", -1);
		AddQuestRecord("JungleGirl", "19");
		AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("", ""));
		CloseQuestHeader("JungleGirl");
		DeleteAttribute(pchar, "GenQuest.EncGirl");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "shipyard":
		if (CheckAttribute(npchar, "TrialDelQuestMark"))
		{
			DeleteAttribute(npchar, "TrialDelQuestMark");
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("PortRoyal");
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if (sti(Pchar.Ship.Type) == SHIP_NOTUSED || ok)
		{
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchShipyard(npchar);
		}
		else
		{
			dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("¿Me estás tomando el pelo? ¿Dónde está tu barco? ¡No lo veo en el puerto!", "¡Juro por el diablo, no me engañarás! ¡Tu barco no está en el puerto!"), pcharrepphrase("No veo tu barco en el puerto, Capitán " + GetFullName(pchar) + ". Espero que no sea el 'Holandés Errante'?", "Capitán, es mucho más fácil cargar la mercancía desde el muelle. Lleva tu barco al puerto y regresa."));
			link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" + RandSwear() + "¡Qué problema! Está bien, viejo zorro, ¡nos vemos pronto!", "No quería engañarte, " + GetFullName(npchar) + ", un barco al otro lado de la isla."), pcharrepphrase("No. ¡Mi barco se llama 'Perla Negra'! ¿Qué le pasó a tu cara? Está pálida... ¡Ja ja! ¡Es broma!", "Gracias por el consejo, me aseguraré de hacerlo."));
			link.l1.go = "exit";
		}
		break;

	case "Cannons":
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
		{
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			LaunchCannons(sti(rColony.StoreNum));
		}
		else
		{
			dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("¿Me estás tomando el pelo? ¿Dónde está tu barco? ¡No lo veo en el puerto!", "¡Juro por el diablo, no me engañarás! ¡Tu barco no está en el puerto!"), pcharrepphrase("No veo su barco en el puerto, Capitán " + GetFullName(pchar) + ". Espero que no sea el 'Holandés Errante'?", "Capitán, es mucho más fácil cargar la mercancía desde el muelle. Lleve su barco al puerto y regrese."));
			link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" + RandSwear() + "¡Qué problema! Está bien, viejo pícaro, ¡nos vemos pronto!", "No quería engañarte, " + GetFullName(npchar) + ", un barco al otro lado de la isla."), pcharrepphrase("No. ¡Mi barco se llama la 'Perla Negra'! ¿Qué le pasó a tu cara? Está pálida... ¡Jaja! ¡Es broma!", "Gracias por el consejo, me aseguraré de hacerlo."));
			link.l1.go = "exit";
		}
		break;

	case "SailsGerald":
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
		{
			dialog.text = "Cambiar el color de las velas cuesta " + FindRussianMoneyString(GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE)) + ", cambiar el escudo de armas cuesta " + FindRussianMoneyString(GetSailsTuningPrice(Pchar, npchar, SAILSGERALD_PRICE_RATE)) + ", reemplazar las velas dependerá del barco.";

			link.l1 = "Elige un nuevo color.";
			link.l1.go = "SailsColorChoose";
			link.l2 = "Dibuja un nuevo escudo de armas.";
			link.l2.go = "SailsGeraldChoose";
			link.l3 = "Instala velas únicas.";
			link.l3.go = "SailsTypeChoose";
			Link.l9 = "He cambiado de opinión.";
			Link.l9.go = "exit";
		}
		else
		{
			dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("¿Me estás tomando el pelo? ¿Dónde está tu barco? ¡No la veo en el puerto!", "¡Juro por el diablo, no me engañarás! ¡Tu barco no está en el puerto!"), pcharrepphrase("No veo su barco en el puerto, Capitán " + GetFullName(pchar) + ". Espero que no sea el 'Holandés Errante'?", "Capitán, es mucho más fácil cargar la mercancía desde el muelle. Lleve su barco al puerto y regrese."));
			link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("Hola, Capitán." + RandSwear() + "¡Qué problema! Está bien, viejo astuto, ¡nos vemos pronto!", "No quería engañarte, " + GetFullName(npchar) + ", un barco al otro lado de la isla."), pcharrepphrase("No. ¡Mi barco se llama 'Perla Negra'! ¿Qué le pasó a tu cara? Está pálida... ¡Jaja! ¡Broma!", "Gracias por el consejo, me aseguraré de hacerlo."));
			link.l1.go = "exit";
		}
		break;

	case "SailsTypeChoose":
		dialog.text = "¿Qué velas quieres instalar? Por el momento tienes " + GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails)) + ".";
		Link.l6 = "Quiero instalar " + GetSailsType(6) + ".";
		Link.l6.go = "SailsTypeChooseIDX_6";
		Link.l7 = "Quiero instalar " + GetSailsType(7) + ".";
		Link.l7.go = "SailsTypeChooseIDX_7";
		Link.l8 = "Quiero instalar " + GetSailsType(8) + ".";
		Link.l8.go = "SailsTypeChooseIDX_8";
		Link.l9 = "Quiero instalar " + GetSailsType(9) + ".";
		Link.l9.go = "SailsTypeChooseIDX_9";
		Link.l10 = "Quiero instalar " + GetSailsType(10) + ".";
		Link.l10.go = "SailsTypeChooseIDX_10";
		Link.l11 = "Quiero instalar " + GetSailsType(11) + ".";
		Link.l11.go = "SailsTypeChooseIDX_11";
		attrLoc = "l" + sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails);
		DeleteAttribute(Link, attrLoc);
		Link.l99 = "He cambiado de opinión.";
		Link.l99.go = "exit";
		break;

	case "SailsTypeChoose2":
		NPChar.SailsTypeMoney = GetSailsTypePrice(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails),
												  sti(NPChar.SailsTypeChooseIDX),
												  stf(NPChar.ShipCostRate),
												  sti(RealShips[sti(Pchar.Ship.Type)].Price));

		dialog.text = "En este momento tienes " + GetSailsType(sti(RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails)) + ", has seleccionado " + GetSailsType(sti(NPChar.SailsTypeChooseIDX)) + " El costo del reemplazo es " + FindRussianMoneyString(sti(NPChar.SailsTypeMoney)) + "¿Proceder?";

		if (sti(NPChar.SailsTypeMoney) <= sti(Pchar.Money))
		{
			Link.l1 = "Sí.";
			Link.l1.go = "SailsTypeChooseDone";
		}
		Link.l99 = "No.";
		Link.l99.go = "exit";
		break;

	case "SailsTypeChooseDone":
		AddMoneyToCharacter(Pchar, -sti(NPChar.SailsTypeMoney));
		dialog.text = "¡Excelente! Todo estará bien.";
		Link.l9 = "Gracias.";
		Link.l9.go = "exit";

		RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = sti(NPChar.SailsTypeChooseIDX);
		WaitDate("", 0, 0, 0, 1, 30);
		break;

	case "SailsColorChoose":
		if (GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE) <= sti(Pchar.Money))
		{
			dialog.text = "¿Qué color escogeremos? El precio es " + FindRussianMoneyString(GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE)) + ".";
			for (i = 0; i < SAILS_COLOR_QUANTITY; i++)
			{
				if (CheckSailsColor(Pchar, i))
				{
					attrLoc = "l" + i;
					Link.(attrLoc) = XI_ConvertString(SailsColors[i].name);
					Link.(attrLoc).go = "SailsColorIdx_" + i;
				}
			}
			Link.l99 = "He cambiado de opinión.";
			Link.l99.go = "exit";
		}
		else
		{
			dialog.text = "Ven cuando tengas el dinero.";
			Link.l9 = "Bien.";
			Link.l9.go = "exit";
		}
		break;

	case "SailsColorDone":
		AddMoneyToCharacter(Pchar, -GetSailsTuningPrice(Pchar, npchar, SAILSCOLOR_PRICE_RATE));
		dialog.text = "De acuerdo. Pintaremos las velas en " + GetStrSmallRegister(XI_ConvertString(SailsColors[sti(NPChar.SailsColorIdx)].name)) + " color.";
		Link.l9 = "Gracias.";
		Link.l9.go = "exit";

		SetSailsColor(Pchar, sti(NPChar.SailsColorIdx));
		WaitDate("", 0, 0, 0, 1, 30);
		break;

	case "SailsGeraldChoose":
		if (GetSailsTuningPrice(Pchar, npchar, SAILSGERALD_PRICE_RATE) <= sti(Pchar.Money))
		{
			if (CheckSailsGerald(Pchar) && CanSetSailsGerald(PChar)) // Warship fix 04.06.09
			{
				NextDiag.CurrentNode = NextDiag.TempNode;
				DialogExit();
				LaunchSailsGeraldScreen(npchar);
			}
			else
			{
				dialog.text = "Lamentablemente, tu barco no puede llevar un escudo de armas.";
				Link.l9 = "Lástima.";
				Link.l9.go = "exit";
			}
		}
		else
		{
			dialog.text = "Vuelve cuando tengas el dinero.";
			Link.l9 = "Bien.";
			Link.l9.go = "exit";
		}
		break;

		//--> -------------------------------------------Бремя гасконца---------------------------------------------------
	case "Sharlie":
		dialog.text = "Lamento decepcionarle, Monsieur, pero ahora mismo no tengo ningún barco a la venta.";
		link.l1 = "Eso es realmente extraño, porque me dijeron que tenías un lugre nuevo en tu astillero.";
		link.l1.go = "Sharlie_1";
		break;

	case "Sharlie_1":
		if (GetQuestPastDayParam("questTemp.Sharlie_ship") > 3)
		{
			dialog.text = "Sabes, probablemente se trate del lugre, por el cual Michel de Monper tenía una fianza de tres mil pesos. Pues este barco ya está vendido, porque según el contrato, el monto total debía ser pagado a más tardar una semana después del descenso del barco al agua.\nTodos los plazos han expirado, y no recibí el dinero, así que el lugre fue vendido. Lo siento mucho, señor.";
			link.l1 = "Sí, eso fue bastante desafortunado, de hecho... Pero ¿estás seguro de que no tienes otros barcos a la venta?";
			link.l1.go = "Sharlie_6";
		}
		else
		{
			dialog.text = "Mm. Sí, en efecto. Pero...";
			link.l1 = "Y ya hay una fianza de cinco mil pesos. Michel de Monper, quien depositó el dinero, me otorgó todos los derechos sobre este barco.";
			link.l1.go = "Sharlie_2";
		}
		break;

	case "Sharlie_2":
		int iDay = 3 - sti(GetQuestPastDayParam("questTemp.Sharlie_ship"));
		sTemp = "Sólo tienes " + FindRussianDaysString(iDay) + "";
		if (iDay == 0)
			sTemp = "Hoy es el último día";
		dialog.text = "Bueno, si es así, entonces continuemos nuestra conversación, señor. Como bien señaló, tengo el depósito de cinco mil pesos por el barco. Pero el valor total del barco, creo, es de quince mil pesos, incluyendo municiones. Así que págueme diez mil y el barco es suyo.\nSegún el contrato, debe pagar el dinero a más tardar una semana después del descenso del barco al agua." + sTemp + ", y luego soy libre de vender este barco a otro cliente. Y, ten en cuenta, que ya hay uno, así que más te vale darte prisa.";
		if (sti(Pchar.money) >= 10000)
		{
			link.l1 = "No habrá necesidad de apresurarse. Tengo la suma requerida conmigo ahora mismo. Aquí tienes.";
			link.l1.go = "Sharlie_4";
		}
		link.l2 = "Está bien, está bien. Tendrás tu dinero, Monsieur. No te haré esperar mucho.";
		link.l2.go = "exit";
		NextDiag.TempNode = "Sharlie_3";
		break;

	case "Sharlie_3":
		if (CheckAttribute(pchar, "questTemp.Sharlie.Rum") || CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") || CheckAttribute(pchar, "questTemp.Sharlie.RescueDaughter"))
		{
			dialog.text = "¿Puedo ayudarle, Monsieur?";
			Link.l1 = "Solo pasé para echar un vistazo a los barcos que tienes disponibles... Pero ahora estoy un poco ocupado, tengo un asunto sin terminar que atender. Volveré tan pronto como lo termine.";
			Link.l1.go = "exit";
			break;
		}
		if (pchar.questTemp.Sharlie == "ship" || pchar.questTemp.Sharlie == "ship_fast") // Addon 2016-1 Jason пиратская линейка 1
		{
			if (GetQuestPastDayParam("questTemp.Sharlie_ship") > 3)
			{
				dialog.text = "Monsieur, te advertí que solo tenías tres días a tu disposición. Se han agotado, y todavía no me trajiste dinero, así que nuestro trato expiró, y vendí el barco a otro cliente. Sin ofender.";
				link.l1 = "Sí, eso fue bastante desafortunado, de hecho... Pero ¿estás seguro de que no tienes otros barcos a la venta?";
				link.l1.go = "Sharlie_6";
			}
			else
			{
				dialog.text = "¿Me has traído diez mil, Monsieur?";
				if (sti(Pchar.money) >= 10000)
				{
					link.l1 = "Claro que tengo. Aquí tienes.";
					link.l1.go = "Sharlie_4";
				}
				link.l2 = "No, todavía estoy trabajando en ello.";
				link.l2.go = "exit";
				NextDiag.TempNode = "Sharlie_3";
			}
		}
		break;

	case "Sharlie_4":
		AddMoneyToCharacter(pchar, -10000);
		DelLandQuestMark(npchar);
		QuestPointerDelLoc("fortfrance_town", "reload", "reload5_back");
		dialog.text = "Entonces permíteme felicitarte por esta exitosa compra. El barco es tuyo. Espero que te sirva bien.";
		link.l1 = "¡Gracias!";
		link.l1.go = "Sharlie_5";
		break;

	case "Sharlie_5":
		NextDiag.CurrentNode = "First time";
		DialogExit();
		pchar.questTemp.Sharlie.Ship = "lugger";
		pchar.questTemp.Sharlie = "crew";
		// стартовый люггер
		pchar.Ship.Type = GenerateShipHand(pchar, SHIP_LUGGER, 6, 800, 40, 610, 16000, 15.2, 58.8, 1.42);
		SetBaseShipData(pchar);
		ResetShipCannonsDamages(pchar);
		SetShipCannonsDamagesNull(pchar);
		NullCharacterGoods(pchar);
		SetCrewQuantityOverMax(PChar, 0);
		/* UpgradeShipParameter(pchar, "SpeedRate");
		UpgradeShipParameter(pchar, "TurnRate");
		UpgradeShipParameter(pchar, "WindAgainstSpeed");
		UpgradeShipParameter(pchar, "HP");
		UpgradeShipParameter(pchar, "MaxCrew");
		UpgradeShipParameter(pchar, "Capacity");
		//UpgradeShipParameter(pchar, "Cannons");
		pchar.ship.HP = 732; */
		// UpgradeShipFull(pchar);
		UpgradeShipParameter(pchar, "Capacity");
		RealShips[sti(pchar.Ship.Type)].ship.upgrades.hull = "q"; // belamour особый скин
		AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		AddCharacterGoods(pchar, GOOD_BALLS, 100);
		AddCharacterGoods(pchar, GOOD_GRAPES, 100);
		AddCharacterGoods(pchar, GOOD_KNIPPELS, 100);
		AddCharacterGoods(pchar, GOOD_BOMBS, 100);
		AddCharacterGoods(pchar, GOOD_POWDER, 220);
		pchar.Ship.name = "Adeline";
		pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS6;
		AddQuestRecord("Sharlie", "6");
		bDisableFastReload = false;					   // открыть переход
		DeleteAttribute(pchar, "GenQuest.CannotWait"); // можно мотать время
		if (GetCharacterIndex("GigoloMan") != -1)
		{
			sld = characterFromId("GigoloMan");
			sld.lifeday = 0;
		}
		pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
		pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин
		bNoEatNoRats = true;					   // отменяем еду и крыс
		GiveItem2Character(pchar, "map_normal");
		break;

	case "Sharlie_6":
		if (sti(Pchar.money) >= 15000)
		{
			dialog.text = "Hmm... Bueno, tengo uno, en realidad, pero no estoy seguro de que te convenga.";
			link.l1 = "Bueno, no puedo permitirme ser muy exigente ahora. ¡Muéstrame lo que tienes!";
			link.l1.go = "Sharlie_7";
		}
		else
		{
			dialog.text = "Escuche, Monsieur, primero haga una fortuna y luego pregunte por los barcos, ¿de acuerdo? Aquí nadie le dará nada gratis. ¿He sido claro?";
			link.l1 = "Perfectamente claro, aunque no había necesidad de ser grosero. Bien, volveré una vez que tenga el dinero.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Sharlie_shipwait";
		}
		break;

	case "Sharlie_7":
		dialog.text = "Entonces mira. Recientemente compré a un precio razonable un balandro. Este era un antiguo barco pirata, sus antiguos dueños ya están colgados de manera segura por numerosos crímenes. El barco, francamente, no es tan bueno como un lanchón y también tiene daños graves, pero aún puede salir al mar.\nNo tengo tiempo para repararlo ahora, todos mis hombres están ocupados construyendo un bergantín que fue ordenado, así que puedes comprarlo de mí en el mismo estado en el que está. Teniendo esto en cuenta, te lo venderé más barato de lo habitual, incluyendo también el contenido de la bodega de carga: quince mil pesos.";
		link.l1 = "Trato hecho. Es apta para navegar, y eso es lo que importa. Guadalupe está a tiro de piedra, lo arreglaré allí si no tienes tal oportunidad.";
		link.l1.go = "Sharlie_8";
		break;

	case "Sharlie_8":
		AddMoneyToCharacter(pchar, -15000);
		DelLandQuestMark(npchar);
		QuestPointerDelLoc("fortfrance_town", "reload", "reload5_back");
		dialog.text = "Entonces permítame felicitarle por esta exitosa compra. El barco es suyo. Espero que le sirva bien.";
		link.l1 = "¡Gracias!";
		link.l1.go = "Sharlie_9";
		break;

	case "Sharlie_9":
		NextDiag.CurrentNode = "First time";
		DialogExit();
		pchar.questTemp.Sharlie.Ship = "sloop";
		pchar.questTemp.Sharlie = "crew";
		// стартовый шлюп
		pchar.Ship.Type = GenerateShipHand(SHIP_SLOOP, 6, 700, 50, 790, 20000, 13.1, 50.1, 1.25);
		SetBaseShipData(pchar);
		ResetShipCannonsDamages(pchar);
		SetShipCannonsDamagesNull(pchar);
		NullCharacterGoods(pchar);
		SetCrewQuantityOverMax(PChar, 0);
		UpgradeShipParameter(pchar, "SpeedRate");
		UpgradeShipParameter(pchar, "TurnRate");
		UpgradeShipParameter(pchar, "WindAgainstSpeed");
		UpgradeShipParameter(pchar, "HP");
		UpgradeShipParameter(pchar, "MaxCrew");
		UpgradeShipParameter(pchar, "Capacity");
		AddCharacterGoods(pchar, GOOD_BALLS, 51);
		AddCharacterGoods(pchar, GOOD_GRAPES, 39);
		AddCharacterGoods(pchar, GOOD_KNIPPELS, 54);
		AddCharacterGoods(pchar, GOOD_BOMBS, 36);
		AddCharacterGoods(pchar, GOOD_POWDER, 231);
		pchar.Ship.name = "Black Hound";
		pchar.Ship.Cannons.Type = CANNON_TYPE_CANNON_LBS3;
		AddQuestRecord("Sharlie", "6");
		bDisableFastReload = false;					   // открыть переход
		DeleteAttribute(pchar, "GenQuest.CannotWait"); // можно мотать время
		if (GetCharacterIndex("GigoloMan") != -1)
		{
			sld = characterFromId("GigoloMan");
			sld.lifeday = 0;
		}
		pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
		pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин
		bNoEatNoRats = true;					   // отменяем еду и крыс
		GiveItem2Character(pchar, "map_normal");
		break;

	case "Sharlie_shipwait":
		dialog.text = "Entonces, Monsieur, ¿ha vuelto con el dinero?";
		if (sti(Pchar.money) >= 15000)
		{
			link.l1 = "Sí, creo que tengo suficiente para permitirme un barco destartalado.";
			link.l1.go = "Sharlie_7";
		}
		else
		{
			link.l1 = "No tengo suficiente todavía. Solo pasé a echar un vistazo...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Sharlie_shipwait";
		}
		break;
		//<-- -----------------------------------------Бремя гасконца-----------------------------------------------------
		// Addon-2016 Jason, французские миниквесты (ФМК) ФМК-Мартиника
	case "FMQM_oil_1":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(npchar, "goto", "goto5", "FMQM_Looking", -1);
		pchar.questTemp.FMQM = "remove_oil1";
		break;

	case "FMQM_oil_2":
		DialogExit();
		LAi_SetActorType(npchar);
		sld = characterFromId("FMQM_officer");
		sld.Dialog.currentnode = "officer_3";
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
		pchar.questTemp.FMQM = "remove_oil2";
		break;

	case "FMQM_oil_3":
		DialogExit();
		LAi_SetActorType(npchar);
		sld = characterFromId("FMQM_officer");
		sld.Dialog.currentnode = "officer_5";
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
		pchar.questTemp.FMQM = "remove_oil3";
		break;

	case "FMQM_oil_4":
		dialog.text = "¡Ay, amigo mío, pero ambos hemos sufrido aquí! Han confiscado la resina, además desperdicié una enorme cantidad de dinero en mi fianza. ¿Y cómo demonios se enteraron de nuestra operación? Debe ser uno de mis trabajadores... ¡Me encargaré de esto, que el Señor tenga piedad del culpable!";
		link.l1 = "Significa que todos mis esfuerzos fueron en vano...";
		link.l1.go = "FMQM_oil_5";
		break;

	case "FMQM_oil_5":
		dialog.text = "Lamento mucho, Capitán. No hay nada que podamos hacer aquí, el destino es una perra a veces.";
		link.l1 = "Ya veo. Bien, me retiraré entonces. ¡Adiós!";
		link.l1.go = "FMQM_oil_6";
		break;

	case "FMQM_oil_6":
		DialogExit();
		AddQuestRecord("FMQ_Martinique", "12");
		pchar.questTemp.FMQM = "officer";
		pchar.quest.FMQM_advice.win_condition.l1 = "location";
		pchar.quest.FMQM_advice.win_condition.l1.location = "FortFrance_town";
		pchar.quest.FMQM_advice.function = "FMQM_GuideAdvice";
		DeleteAttribute(pchar, "questTemp.FMQM.Oil");
		break;

	// Addon 2016-1 Jason пиратская линейка
	case "mtraxx_x":
		dialog.text = "Me gustaría volver a esa conversación. Estoy dispuesto a ofrecer un descuento decente... un descuento muy considerable por cualquier trabajo en tu barco... si me proporcionas un poco de seda extra...";
		link.l1 = "Maestro, vayamos directo al grano. Prometo que no soy un espía ni tampoco uno de los hombres del Coronel D'Oyley. Además, trabajo con Marcus Tyrex, un nombre que debería sonarle familiar. Así que pongamos las cartas sobre la mesa. Sé que necesita un suministro constante de lona de seda, y Marcus Tyrex está dispuesto a traérselo. También de manera constante. Sin embargo, solo en caso de que acordemos el precio. ¿Podemos ir directo a eso entonces, maestro?";
		link.l1.go = "mtraxx_x_1";
		break;

	case "mtraxx_x_1":
		dialog.text = "Está bien. Parece que no tengo otra opción en el asunto: o trabajas para D'Oyley y me enviarás a prisión, o me arruinaré si no encuentro urgentemente un envío considerable de seda. Estoy dispuesto a pagar 25 doblones por pieza, pero solo por envíos grandes, no menos de 100 rollos.";
		link.l1 = "Entonces tenemos un trato. Estoy seguro de que Tyrex podrá proporcionarte envíos de 100 rollos cada mes.";
		link.l1.go = "mtraxx_x_2";
		break;

	case "mtraxx_x_2":
		dialog.text = "¡Eso sería magnífico! Podría comprar el primer lote de inmediato.";
		link.l1 = "No puedo hacerlo ahora mismo, pero no tomará mucho tiempo. Un barco con la carga que necesitas está en Capsterville en este momento, me dirijo allí de inmediato y te la enviaré. ¿Dónde haremos la descarga?";
		link.l1.go = "mtraxx_x_3";
		break;

	case "mtraxx_x_3":
		dialog.text = "Hagámoslo así. Entre el 10 y el 15 de cada mes, por la noche, mi gente estará esperando a tus visitantes en la bahía... no, espera, mejor en el Cabo Negril. Seguro será un largo recorrido, pero hay muchas menos patrullas... La contraseña será: 'Un mercader de Lyon'.";
		link.l1 = "Trato hecho, maestro. Me dirijo a Capsterville de inmediato.";
		link.l1.go = "mtraxx_x_4";
		break;

	case "mtraxx_x_4":
		dialog.text = "Espero que tu barco llegue rápido, tengo una urgente necesidad de nueva seda.";
		link.l1 = "No te preocupes, todo estará bien. ¡Buen viento y buena mar!";
		link.l1.go = "mtraxx_x_5";
		break;

	case "mtraxx_x_5":
		DialogExit();
		AddQuestRecord("Roger_2", "21");
		pchar.questTemp.Mtraxx = "silk_10"; // покупатель найден
		sld = characterFromId("Jeffry");
		sld.DeckDialogNode = "Jeffry_9";
		break;
	// Jason Исла Мона
	case "IslaMona":
		if (CheckAttribute(pchar, "questTemp.IslaMona.Shipyarder") && pchar.questTemp.IslaMona.Shipyarder == npchar.id)
		{
			if (sti(NPChar.nation) != PIRATE && ChangeCharacterHunterScore(Pchar, NationShortName(sti(NPChar.nation)) + "hunter", 0) > 10)
			{
				dialog.text = "No, " + pchar.name + " No tengo nada en contra de ti, pero resuelve tus problemas con mi país primero. Vender un inventario tan valioso a un enemigo de la Corona podría ser malinterpretado.";
				link.l1 = "Sí, y cuando estás contrabandeando mercancías de origen incierto en los barcos, ¿son mejores amigos? Espera a que resuelva este malentendido.";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Digamos. ¿Por qué? ¿Estás construyendo algo?";
				link.l1 = "No, estoy haciendo un viaje muy especial. Para un administrador de plantación.";
				link.l1.go = "IslaMona_1";
			}
		}
		else
		{
			npchar.quest.IslaMonaTools = "true";
			dialog.text = "No puedo ayudarte.";
			link.l1 = "¡Es una lástima!";
			link.l1.go = "exit";
		}
		break;

	case "IslaMona_1":
		dialog.text = "Ya veo. Espero que este gerente te haya proporcionado lo suficiente, ya que cobraría mucho por un conjunto como este. Tienes mucha suerte de haber recibido una importación reciente de la metrópoli.";
		link.l1 = "¿Cuánto?";
		link.l1.go = "IslaMona_2";
		break;

	case "IslaMona_2":
		pchar.questTemp.IslaMona.Shipyarder.Money = 1000;
		dialog.text = "Mil doblones de oro.";
		link.l1 = "Te estás sobrecalentando, veo. Estoy bien. Lo tomaré.";
		link.l1.go = "IslaMona_7";
		link.l2 = "Es demasiado. Dudo que haya otro comprador para todo el conjunto como yo. Algo se venderá, algo será robado por los vagabundos locales. ¿Qué tal un descuento?";
		link.l2.go = "IslaMona_3";
		break;

	case "IslaMona_3":
		if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 60)
		{
			notification("Skill Check Failed (60)", SKILL_COMMERCE);
			dialog.text = "Te garantizo que aparecerá. No hay cambio en el precio. ¿Qué te parece? No esperaré mucho.";
			link.l1 = "Bien, está bien, está bien. Lo tomaré.";
			link.l1.go = "IslaMona_7";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		}
		else
		{
			notification("Skill Check Passed", SKILL_COMMERCE);
			pchar.questTemp.IslaMona.Shipyarder.Money = 900;
			dialog.text = "Está bien, tomaremos cien. Novecientos. No bajaré más. No me pidas que lo haga.";
			link.l1 = "Y no lo haré. Estoy de acuerdo.";
			link.l1.go = "IslaMona_7";
			link.l2 = "¿Por qué no me das un poco más? Como mayorista. Y luego te encargaré reparaciones y pinturas, y la figura de proa más jugosa.";
			link.l2.go = "IslaMona_4";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		}
		break;

	case "IslaMona_4":
		if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 85)
		{
			notification("Skill Check Failed (85)", SKILL_COMMERCE);
			dialog.text = "No me importa si ordenas una moza viva. Novecientos.";
			link.l1 = "Está bien, de acuerdo, de acuerdo. Me lo llevo.";
			link.l1.go = "IslaMona_7";
			AddCharacterExpToSkill(pchar, "Commerce", 400);
		}
		else
		{
			notification("Skill Check Passed", SKILL_COMMERCE);
			pchar.questTemp.IslaMona.Shipyarder.Money = 800;
			dialog.text = "¿Estás seguro? ¿No lo olvidarás? Está bien, cortemos otros cien. ¡Pero eso es todo!";
			link.l1 = "No lo olvidaré. ¡Es un trato!";
			link.l1.go = "IslaMona_7";
			link.l2 = "Bueno, ¿cómo puedo decir esto...?";
			link.l2.go = "IslaMona_5";
			AddCharacterExpToSkill(pchar, "Fortune", 200);
		}
		break;

	case "IslaMona_5":
		dialog.text = "¡Inconcebible! " + pchar.name + ", ¿se olvidaron de sacarte el trozo de perdigón del cráneo? ¡Avaro como un escorpión! ¡Todos hemos oído hablar de tus recientes andanzas! Ya has ganado tu montón de oro, así que no impidas que otros ganen el suyo. Una palabra más y no venderé por menos de mil.";
		link.l1 = "¡Está bien, está bien! Tómalo con calma. Estoy de acuerdo.";
		link.l1.go = "IslaMona_7";
		link.l2 = "Pero, " + npchar.name + ", ¡Tengo niños pequeños! ¡Tengo que pensar en ellos también! No te pagan lo suficiente por el transporte honesto, ¡lo sabes!";
		link.l2.go = "IslaMona_6";
		break;

	case "IslaMona_6":
		if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 100)
		{
			notification("Skill Check Failed (100)", SKILL_COMMERCE);
			pchar.questTemp.IslaMona.Shipyarder.Money = 1000;
			dialog.text = "Los hijos de las chicas del burdel no cuentan, " + pchar.name + ". Estoy harto de ti. Mil doblones sobre el barril, o nos despedimos.";
			link.l1 = "¿Qué quieres decir con que no lo son? Ajá. Estoy de acuerdo, eres un bribón.";
			link.l1.go = "IslaMona_7";
			AddCharacterExpToSkill(pchar, "Commerce", 800);
		}
		else
		{
			notification("Skill Check Passed", SKILL_COMMERCE);
			pchar.questTemp.IslaMona.Shipyarder.Money = 700;
			dialog.text = "No sabía que tenías hijos. Y que las cosas estaban tan mal. Está bien, no te quejes. Setecientos. Es casi una pérdida.";
			link.l1 = "¡No lo olvidaré. Es un trato!";
			link.l1.go = "IslaMona_7";
			AddCharacterExpToSkill(pchar, "Fortune", 400);
			Achievment_SetStat(106, 1);
		}
		break;

	case "IslaMona_7":
		dialog.text = "Entonces, me debes " + sti(pchar.questTemp.IslaMona.Shipyarder.Money) + " escudos.";
		if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.questTemp.IslaMona.Shipyarder.Money))
		{
			link.l1 = "Aquí, te doy lo último, no me queda nada.";
			link.l1.go = "IslaMona_8";
		}
		else
		{
			if (GetCharacterItem(pchar, "gold_dublon") < 1)
			{
				link.l1 = "Espera, voy a ir al usurero para endeudarme.";
				link.l1.go = "IslaMona_money_exit";
			}
			else
			{
				link.l1 = "Todo lo que tengo conmigo " + FindRussianDublonString(GetCharacterItem(pchar, "doblón_de_oro")) + " Toma esto, y me iré a los usureros.";
				link.l1.go = "IslaMona_money";
			}
		}
		break;

	case "IslaMona_money":
		pchar.questTemp.IslaMona.Shipyarder.Money = sti(pchar.questTemp.IslaMona.Shipyarder.Money) - GetCharacterItem(pchar, "gold_dublon");
		Log_Info("Has entregado " + FindRussianDublonString(GetCharacterItem(pchar, "gold_dublon")) + "");
		RemoveItems(pchar, "gold_dublon", GetCharacterItem(pchar, "gold_dublon"));
		PlaySound("interface\important_item.wav");
		dialog.text = "No sientas lástima por mí, tienes un cofre de camarote lleno de oro. Me deberás " + FindRussianDublonString(sti(pchar.questTemp.IslaMona.Shipyarder.Money)) + ".";
		link.l1 = "";
		link.l1.go = "IslaMona_money_exit";
		break;

	case "IslaMona_money_exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		npchar.quest.IslaMonaMoney = "true";
		pchar.questTemp.IslaMona = "dublon";
		break;

	case "IslaMona_8":
		Log_Info("Has entregado " + FindRussianDublonString(sti(pchar.questTemp.IslaMona.Shipyarder.Money)) + "");
		RemoveItems(pchar, "gold_dublon", sti(pchar.questTemp.IslaMona.Shipyarder.Money));
		PlaySound("interface\important_item.wav");
		dialog.text = "Eso es estupendo. La cantidad completa está en su lugar. Las herramientas serán entregadas a su barco. Estas son algunas cajas pesadas.";
		link.l1 = "Gracias, " + npchar.name + ".";
		link.l1.go = "IslaMona_9";
		break;

	case "IslaMona_9":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		GiveItem2Character(pchar, "islamona_toolbox");
		DeleteAttribute(pchar, "questTemp.IslaMona.Shipyarder");
		DeleteAttribute(npchar, "quest.IslaMonaMoney");
		AddQuestRecord("IslaMona", "2");
		pchar.questTemp.IslaMona = "get_tools";
		break;
	}
}

string findShipyardCity(ref NPChar)
{
	int n, nation;
	int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
	int howStore = 0;

	for (n = 0; n < MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(npchar.nation), sti(colonies[n].nation));
		if (sti(colonies[n].nation) != PIRATE && colonies[n].id != "Panama" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) // не на свой остров
		{
			if (GetCharacterIndex(colonies[n].id + "_shipyarder") != -1)
			{
				storeArray[howStore] = n;
				howStore++;
			}
		}
	}
	if (howStore == 0)
		return "none";
	nation = storeArray[rand(howStore - 1)];
	return colonies[nation].id;
}

// проверка какой уже цвет есть
bool CheckSailsColor(ref chr, int col)
{
	int st = GetCharacterShipType(chr);
	ref shref;

	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st);
		st = -1;
		if (!CheckAttribute(shref, "ShipSails.SailsColor"))
			st = 0; // нету - это белый
		if (CheckAttribute(shref, "SailsColorIdx"))
			st = sti(shref.SailsColorIdx);
		if (st == col)
			return false;
	}
	return true;
}

bool CheckSailsGerald(ref chr)
{
	int st = GetCharacterShipType(chr);
	ref shref;
	if (st != SHIP_NOTUSED)
	{
		shref = GetRealShip(st);
		if (CheckAttribute(shref, "GeraldSails"))
			return true;
	}
	return false;
}

string GetSailsType(int _type)
{
	string sSail;

	switch (_type)
	{
	case 1:
		sSail = "" + XI_ConvertString("sails_1") + "";
		break;
	case 2:
		sSail = "" + XI_ConvertString("sails_2") + "";
		break;
	case 3:
		sSail = "" + XI_ConvertString("sails_3") + "";
		break;
	case 4:
		sSail = "" + XI_ConvertString("sails_4") + "";
		break;
	case 5:
		sSail = "" + XI_ConvertString("sails_5") + "";
		break;
	case 6:
		sSail = "" + XI_ConvertString("sails_6") + "";
		break;
	case 7:
		sSail = "" + XI_ConvertString("sails_7") + "";
		break;
	case 8:
		sSail = "" + XI_ConvertString("sails_8") + "";
		break;
	case 9:
		sSail = "" + XI_ConvertString("sails_9") + "";
		break;
	case 10:
		sSail = "" + XI_ConvertString("sails_10") + "";
		break;
	case 11:
		sSail = "" + XI_ConvertString("sails_11") + "";
		break;
	}
	return sSail;
}

int GetSailsTypePrice(int _asis, int _tobe, float _shipCostRate, int _price)
{
	int ret;
	ret = _tobe - _asis;

	if (ret < 0)
		ret = 0;

	return makeint((ret * _price * 0.05 + _price * 0.05) * _shipCostRate / 10) * 10;
}

void SelectFindship_ShipType()
{
	int iRank;
	if (sti(pchar.rank) < 7) iRank = 0;
	if (sti(pchar.rank) >= 7 && sti(pchar.rank) < 11) iRank = 1;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 20) iRank = 2;
	if (sti(pchar.rank) >= 20 && sti(pchar.rank) <= 27) iRank = 3;
	
	int iShip = SHIP_WAR_TARTANE;
	switch (iRank)
	{
		case 0:
			iShip = sti(RandPhraseSimple(its(GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)), 
										 its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
		case 1:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break; 
		case 2:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
		case 3:  
			iShip = sti(LinkRandPhrase(its(GetRandomShipType(FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_WAR + FLAG_SHIP_TYPE_RAIDER, FLAG_SHIP_NATION_ANY)), 
									   its(GetRandomShipType(FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_ANY, FLAG_SHIP_NATION_ANY)),
									   its(GetRandomShipType(FLAG_SHIP_CLASS_2, FLAG_SHIP_TYPE_MERCHANT + FLAG_SHIP_TYPE_UNIVERSAL, FLAG_SHIP_NATION_ANY))));
		break;
	}
	
	pchar.GenQuest.Findship.Shipyarder.ShipType = iShip;
}

// проверка количества материалов для корабельного тюнинга
void checkMatherial(ref Pchar, ref NPChar, int good)
{
	int amount;

	amount = GetSquadronGoods(Pchar, good) - sti(NPChar.Tuning.Matherial);
	if (amount < 0)
	{
		amount = amount + sti(NPChar.Tuning.Matherial);
	}
	else
	{
		amount = sti(NPChar.Tuning.Matherial);
	}
	RemoveCharacterGoods(Pchar, good, amount);
	NPChar.Tuning.Matherial = sti(NPChar.Tuning.Matherial) - amount;
}

/*
  _chr 		- ГГ
  NPChar 	- верфист
  MaterialNum -  номер материала для апгрейда
	 1 - товар
	 2 - цена в дублонах(сундуки)
  Функция возвращает кол-во материала необходимого для данного типа апгрейда
*/

int GetMaterialQtyUpgrade(ref _chr, ref _nchar, int MaterialNum)
{
	if (sti(_chr.Ship.Type) == SHIP_NOTUSED)
		return 0;

	float fQuestShip = 1.0;
	float LEcoeff = 1.0; // legendary edition

	int shipClass = sti(RealShips[sti(_chr.Ship.Type)].Class);
	int shipMinCrew = sti(RealShips[sti(_chr.Ship.Type)].MinCrew);
	int shipPrice = sti(RealShips[sti(_chr.Ship.Type)].Price);

	if (shipClass == 4)
		LEcoeff = 0.38;
	if (shipClass > 4)
		LEcoeff = 0.25;
	if (CheckAttribute(&RealShips[sti(_chr.Ship.Type)], "QuestShip"))
		fQuestShip = 1.3;

	if (MaterialNum == 1)
	{
		int Material = makeint((40 * (8 - shipClass) + 25 * MOD_SKILL_ENEMY_RATE + hrand(shipMinCrew)) * fQuestShip * LEcoeff);
		if (Material < 1)
			Material = 1;
		return Material;
	}
	if (MaterialNum == 2)
	{
		int WorkPrice = 1;
		switch (shipClass)
		{
		case 1:
			WorkPrice = 10;
			break;
		case 2:
			WorkPrice = 7;
			break;
		case 3:
			WorkPrice = 5;
			break;
		case 4:
			WorkPrice = 3;
			break;
		case 5:
			WorkPrice = 2;
			break;
		case 6:
			WorkPrice = 1;
		break;
		}
		return WorkPrice;
	}

	return 0;
}
// belamour legendary edition тюнинг - проверка на сделанное
bool TuningAvailable()
{
	int num = 0;
	ref shTo = &RealShips[sti(Pchar.Ship.Type)];

	if (CheckAttribute(shTo, "Tuning.SpeedRate"))
		num++;
	if (CheckAttribute(shTo, "Tuning.WindAgainst"))
		num++;
	if (CheckAttribute(shTo, "Tuning.Cannon"))
		num++;
	if (CheckAttribute(shTo, "Tuning.Capacity"))
		num++;
	if (CheckAttribute(shTo, "Tuning.HP"))
		num++;
	if (CheckAttribute(shTo, "Tuning.MaxCrew"))
		num++;
	if (CheckAttribute(shTo, "Tuning.TurnRate"))
		num++;
	if (CheckAttribute(shTo, "Tuning.MinCrew"))
		num++;

	if (sti(shTo.Class) > 4 && num == 7 && !CheckAttribute(shTo, "Tuning.MinCrew"))
	{
		if (!CheckAttribute(shTo, "Tuning.All"))
		{
			if (sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_HIMERA)
				Achievment_Set("ach_CL_115");
			if (startHeroType == 4 && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_SCHOONER_W)
			{
				if (pchar.ship.name == "Rainbow")
					Achievment_Set("ach_CL_126");
			}
			shTo.Tuning.All = true;
			Log_Info("¡El barco " + pchar.ship.name + " consigue un 5% más de velocidad en el Mapa Global!");
		}
		return false;
	}

	if (num < 8)
		return true;
	else
	{
		if (!CheckAttribute(shTo, "Tuning.All"))
		{
			if (sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_HIMERA)
				Achievment_Set("ach_CL_115");
			if (startHeroType == 4 && sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_SCHOONER_W)
			{
				if (pchar.ship.name == "Rainbow")
					Achievment_Set("ach_CL_126");
			}
			shTo.Tuning.All = true;
			Log_Info("¡El barco " + pchar.ship.name + " consigue un 5% más de velocidad en el Mapa Global!");
		}
		return false;
	}
}