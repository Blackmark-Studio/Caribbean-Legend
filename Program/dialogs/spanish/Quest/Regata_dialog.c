void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	bool ok;
    int iTest;
    ref rColony;
    string sFrom_sea = "";
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;
		
		//вестовой
		case "Regata_Cureer":
			dialog.text = "Buen día. ¿Eres el capitán "+GetFullName(pchar)+"?";
			link.l1 = "Sí, soy yo. ¿Y cuál es el trato?";
			link.l1.go = "Regata_Cureer_1";
		break;
		
		case "Regata_Cureer_1":
			dialog.text = "Tengo una carta para usted del gobernador de Jamaica, señor Edward Doily.";
			link.l1 = "¡Vaya! No esperaba esto... ¿Y qué quiere el gobernador de mí?";
			link.l1.go = "Regata_Cureer_2";
		break;
		
		case "Regata_Cureer_2":
			dialog.text = "Lea la carta, señor. En resumen, se le ofrece participar en la regata, una carrera a través de todo el archipiélago. Los rumores sobre sus habilidades navales y su notable velocidad en la navegación no han pasado desapercibidos.";
			link.l1 = "¡Increíble! Pues yo... lo consideraré.";
			link.l1.go = "Regata_Cureer_3";
			GiveItem2Character(pchar, "letter_open");
			ChangeItemDescribe("letter_open", "itmdescr_letter_open_Regata");
			AddQuestRecordInfo("RegataLetter", "1");
		break;
		
		case "Regata_Cureer_3":
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND)
			{
				dialog.text = "También debo proporcionarte acceso gratuito al puerto de Port Royal. Aquí tienes una licencia por 30 días. Ahora mi misión está completa. Adiós, capitán.";
				link.l1 = "Gracias. La licencia es muy bienvenida. ¡Adiós!";
				link.l1.go = "Cureer_exit";
				GiveNationLicence(HOLLAND, 30);
			}
			else
			{
				dialog.text = "Bien. Ahora mi misión está completa. Adiós, capitán.";
				link.l1 = "¡Adiós!";
				link.l1.go = "Cureer_exit";
			}
		break;
		
		case "Cureer_exit":
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", -1);
			pchar.questTemp.Regata.ToPortRoyal = "true";
			SetQuestHeader("Regata");
			AddQuestRecord("Regata", "1");
		break;
		
		//распорядитель регаты
		case "Regata_Head":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				dialog.text = "Buen día. Participas en la regata, ¿verdad?";
				link.l1 = "Precisamente, señor. Mi nombre es "+GetFullName(pchar)+" He recibido la invitación.";
				link.l1.go = "Regata_Head_1";
			}
			else
			{
				dialog.text = "¿Quiere algo, señor?";
				link.l1 = "No, no es nada. Ya me voy.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head";
			}
		break;
		
		case "Regata_Head_1":
			iTest = FindColony("PortRoyal"); 
			if (iTest != -1)
			{
				rColony = GetColonyByIndex(iTest);
			}
			ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
			{
				dialog.text = "Me alegra conocerte, capitán "+GetFullName(pchar)+"  Entonces, comencemos. Ya estás al tanto de lo básico por la carta, ¿verdad? Sólo lanchas, y ella tiene que ser la única nave en tu escuadrón para poder participar en la regata. ¿Has cumplido con estos requisitos?";
				// belamour legendary edition допускаем курьерский люггер 
				ok = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
				if((GetCompanionQuantity(pchar) > 1) || !ok)
				{
					link.l1 = "Aún no. Lo haré ahora y volveré pronto.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Regata_Head_repeat";
				}
				else
				{
					link.l1 = "Sí, lo tengo.";
					link.l1.go = "Regata_Head_2";
				}
			}
			else
			{
				dialog.text = "Has venido a participar en la regata, pero ¿dónde está tu barco, capitán?";
				link.l1 = "Disculpe, señor. Llevaré mi barco al puerto de inmediato.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head_repeat";
			}
		break;
		
		case "Regata_Head_repeat":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				iTest = FindColony("PortRoyal"); 
				if (iTest != -1)
				{
					rColony = GetColonyByIndex(iTest);
				}
				ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
				if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
				{
					ok = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
					dialog.text = "Ah, eres tú de nuevo. ¿Has hecho todo para cumplir con los requisitos de la regata?";
					// belamour legendary edition допускаем курьерский люггер 
					if ((GetCompanionQuantity(pchar) > 1) || !ok)
					{
						link.l1 = "Aún no. Lo haré ahora y regresaré pronto.";
						link.l1.go = "exit";
						NextDiag.TempNode = "Regata_Head_repeat";
					}
					else
					{
						link.l1 = "Sí, lo tengo.";
						link.l1.go = "Regata_Head_2";
					}
				}
				else
				{
					dialog.text = "Capitán, no tenemos nada que discutir hasta que vea su barco en una rada. ¿Me entiende o debo repetirlo?";
					link.l1 = "Disculpe, señor. Llevaré mi barco al puerto de inmediato.";
					link.l1.go = "exit";
					NextDiag.TempNode = "Regata_Head_repeat";
				}
			}
			else
			{
				dialog.text = "¿Quiere algo, señor?";
				link.l1 = "No... no es nada. Ya me voy.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Regata_Head";
			}
		break;
		
		case "Regata_Head_2":
			dialog.text = "Bien. Ahora el siguiente punto. ¿Cuál es el nombre de tu barco?";
			link.l1 = "'"+pchar.Ship.Name+"'.";
			link.l1.go = "Regata_Head_3";
		break;
		
		case "Regata_Head_3":
			dialog.text = "Ya que la regata es organizada por las autoridades inglesas y debido a las reglas fijas, el nombre de tu barco debe ser cambiado durante el evento. No te preocupes, esto concierne a todos los participantes.";
			link.l1 = "Dicen que es de mala suerte cambiar el nombre de tu barco.";
			link.l1.go = "Regata_Head_4";
		break;
		
		case "Regata_Head_4":
			dialog.text = "Podrás cambiar el nombre de nuevo después de la regata. Así que tu balandra llevará el nombre de 'Santa Catalina'.";
			link.l1 = "Lo entiendo, señor, cambiaré el nombre.";
			link.l1.go = "Regata_Head_5";
			pchar.Ship.Name = "Saint Catherine";
		break;
		
		case "Regata_Head_5":
			dialog.text = "Ahora hablemos de la regata en sí. Escucha con atención. También te proporcionaré un documento con las reglas.\nLa regata comienza y termina en Port Royal. Hay cinco puntos que tendrás que alcanzar.\nEl primero es de Port Royal a Belice, en Tierra Firme occidental.\nEl segundo es de Belice a Puerto Príncipe, en La Española.\nEl tercero es de Puerto Príncipe a St. John's, en Antigua.\nEl cuarto es de St. John's a Bridgetown, en Barbados.\nY el último es de Bridgetown a Port Royal.\n¿Está claro?";
			link.l1 = "Cristalino claro, señor.";
			link.l1.go = "Regata_Head_6";
		break;
		
		case "Regata_Head_6":
			dialog.text = "Espléndido. Debes registrarte en cada oficina portuaria de las siguientes ciudades: Belice, Puerto Príncipe, San Juan, Bridgetown. Serás descalificado si te saltas alguna de estas ciudades o rompes la secuencia correcta.\nLas oficinas estarán abiertas las veinticuatro horas durante el transcurso de la regata. Llama a la puerta y te dejarán entrar.";
			link.l1 = "Entendido.";
			link.l1.go = "Regata_Head_7";
		break;
		
		case "Regata_Head_7":
			dialog.text = "Está prohibido cambiar de barco y añadir más barcos a tu escuadrón. Esto se verificará en cada ciudad, considéralo.";
			link.l1 = "Lo consideraré. ¿Quién se considera normalmente como ganador y podemos hablar de premios?";
			link.l1.go = "Regata_Head_8";
		break;
		
		case "Regata_Head_8":
			dialog.text = "Solo hay un ganador en la regata: el capitán cuyo barco sea el primero en llegar a Port-Royal. El premio es muy valioso. El ganador obtendrá una gran suma - 250 000 pesos. Además, se le otorgará un conjunto de regalos valiosos.";
			link.l1 = "¿Entonces, los perdedores no obtienen nada?";
			link.l1.go = "Regata_Head_9";
		break;
		
		case "Regata_Head_9":
			dialog.text = "Exactamente. Además, muchos ciudadanos ricos y pobres de las colonias inglesas hacen apuestas sobre el ganador de la regata. También puedes apostar por... ti mismo. Normalmente, cada capitán lo hace. Si ganas, ganarás aún más y no olvides la motivación. Usualmente yo acepto las apuestas\n¿Estás apostando por tu victoria?";
			link.l1 = "¡Ja! Claro que sí. ¿Cuánto puedo apostar?";
			link.l1.go = "Regata_rate";
			link.l2 = "Lo pensaré. Tal vez apueste.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_Head_10":
			if (CheckAttribute(pchar, "questTemp.Regata.Begin"))
			{
				dialog.text = "Piensa si quieres. Tienes algo de tiempo antes de que empiece la regata.";
				link.l1 = "Bien. ¿Cuándo empieza?";
				link.l1.go = "Regata_Head_11";
				DeleteAttribute(pchar, "questTemp.Regata.Rate");
				pchar.questTemp.Regata.Ratenext = "true";
			}
			else
			{
				dialog.text = "Piensa si quieres. Tienes algo de tiempo antes de que empiece la regata.";
				link.l1 = "Bien.";
				link.l1.go = "exit";
			}
		break;
		
		case "Regata_Head_11":
			CreateRegataAdversaries();
			dialog.text = "En tres días, a las doce en punto, mediodía. Ven al muelle, y no llegues tarde. Tendrás cinco competidores.\n"+pchar.questTemp.Regata.AdversaryName.a+", de la "+pchar.questTemp.Regata.AdversaryShipName.a+"\n"+pchar.questTemp.Regata.AdversaryName.b+", del "+pchar.questTemp.Regata.AdversaryShipName.b+"\n"+pchar.questTemp.Regata.AdversaryName.c+", del "+pchar.questTemp.Regata.AdversaryShipName.c+"\n"+pchar.questTemp.Regata.AdversaryName.d+", de la "+pchar.questTemp.Regata.AdversaryShipName.d+"\n"+pchar.questTemp.Regata.AdversaryName.e+", de la "+pchar.questTemp.Regata.AdversaryShipName.e+"\nTodos ellos son capitanes experimentados. Bueno, aparentemente eso es todo. Toma el papel de reglas por si acaso. ¡Nos vemos en el inicio!";
			link.l1 = "Adiós, señor.";
			if (Pchar.BaseNation == SPAIN || Pchar.BaseNation == HOLLAND) link.l1.go = "Regata_Head_13";
			else link.l1.go = "Regata_Head_12";
		break;
		
		case "Regata_Head_12":
			DialogExit();
			pchar.quest.RegataToPortRoyalTimeOver.over = "yes";//снять таймер
			SetFunctionTimerCondition("Regata_SetTime", 0, 0, 3, false);
			pchar.quest.Regata_Lost.win_condition.l1 = "Timer";
			pchar.quest.Regata_Lost.win_condition.l1.date.hour  = 13.0;
			pchar.quest.Regata_Lost.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Regata_Lost.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Regata_Lost.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Regata_Lost.function = "Regata_Lost";
			pchar.quest.Regata_Start.win_condition.l1 = "Timer";
			pchar.quest.Regata_Start.win_condition.l1.date.hour  = 12.0;
			pchar.quest.Regata_Start.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 3);
			pchar.quest.Regata_Start.win_condition.l2 = "locator";
			pchar.quest.Regata_Start.win_condition.l2.location = "Portroyal_town";
			pchar.quest.Regata_Start.win_condition.l2.locator_group = "reload";
			pchar.quest.Regata_Start.win_condition.l2.locator = "reload1_back";
			pchar.quest.Regata_Start.function = "Regata_Start";
			AddQuestRecordInfo("RegataRules", "1");
			NextDiag.CurrentNode = "Regata_Prepare";
			DeleteAttribute(pchar, "questTemp.Regata.Begin");
			pchar.questTemp.Regata.Prepare = "true";
			AddQuestRecord("Regata", "2");
		break;
		
		case "Regata_Head_13":
			dialog.text = "¡Espera! Te daré la licencia de 30 días para visitar puertos ingleses y franceses. La regata no durará más de un mes. Por favor, tómala.";
			link.l1 = "¡Gracias!";
			link.l1.go = "Regata_Head_12";
			GiveNationLicence(HOLLAND, 30);
		break;
		
		case "Regata_rate":
			dialog.text = "¿Cuánto estás apostando?";
			link.l1 = "";
			Link.l1.edit = 4;
			link.l1.go = "Regata_rate_1";
			link.l2 = "Supongo que aún necesito algo de tiempo para pensar.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_rate_1":
			int iQty = sti(dialogEditStrings[4]);
			pchar.questTemp.Regata.Rate = sti(iQty);
			if (iQty < 10000)
			{
				dialog.text = "Señor, esto no es gracioso, ni tampoco divertido. No trabajaré por una suma tan pequeña.";
				link.l1 = "Perdón... Vamos a reconsiderar la apuesta.";
				link.l1.go = "Regata_rate";
				break;
			}
			if (iQty > 100000)
			{
				dialog.text = "Señor, no puedo aceptar tales apuestas debido a las reglas de la regata. Redúzcalo a un valor razonable.";
				link.l1 = "Qué lástima. Reconsideremos la suma.";
				link.l1.go = "Regata_rate";
				break;
			}
			dialog.text = ""+iQty+"¿ Esa es una buena apuesta. Estoy listo para aceptarla. ¿Su dinero, señor?";
			if (makeint(Pchar.money) >= sti(pchar.questTemp.Regata.Rate))
			{
				link.l1 = "Por favor, tómalo.";
				link.l1.go = "Regata_rate_2";
			}
			link.l2 = "No tengo suficientes monedas ahora. Volveré más tarde y haremos una apuesta. Y lo pensaré más, quizás reconsideraré la suma.";
			link.l2.go = "Regata_Head_10";
		break;
		
		case "Regata_rate_2":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.Rate));
			pchar.questTemp.Regata.Advantage = sti(pchar.questTemp.Regata.Rate)*(1.5+frand(1.5)); // dlc
			dialog.text = "¡Espléndido! Ahora todo lo que necesitas hacer es ser el primero y el premio será tuyo. Su valor final podría variar, todo depende de cuántas personas apostarán por ti al final.";
			if (!CheckAttribute(pchar, "questTemp.Regata.Ratenext"))
			{
				link.l1 = "Ya veo. ¿Cuándo empieza la regata?";
				link.l1.go = "Regata_Head_11";
			}
			else
			{
				link.l1 = "Ya veo. Estaré esperando el comienzo. ¡Hasta luego!";
				link.l1.go = "exit";
				DeleteAttribute(pchar, "questTemp.Regata.Ratenext");
				NextDiag.TempNode = "Regata_Prepare";
			}
		break;
		
		case "Regata_Prepare":
			dialog.text = "Ah, estás aquí de nuevo, capitán "+GetFullName(pchar)+"¿ Qué quieres?";
			if (!CheckAttribute(pchar, "questTemp.Regata.Rate"))
			{
				link.l1 = "Quiero apostar por mi victoria.";
				link.l1.go = "Regata_rate";
			}
			link.l2 = "No, no es nada. Solo quería saludarte.";
			link.l2.go = "exit";
			NextDiag.TempNode = "Regata_Prepare";
		break;
		
		//старт регаты
		case "Regata_CitMan":
			dialog.text = RandPhraseSimple(LinkRandPhrase("Capitán, ¿es su primera vez? Déjeme decirle que debería tener cuidado. Sus competidores podrían prepararle algunas sorpresas muy desagradables...","¡Capitán, he apostado por ti. ¡No me decepciones!","Capitán, los lugareños en los puertos de la regata podrían ofrecerle comprar algo. A menudo puede ser realmente útil. Considérelo."),LinkRandPhrase("¡Qué tengas un viaje seguro, capitán!","Capitán, por favor, ten cuidado, los castellanos a menudo cazan las balandras de los participantes en las aguas españolas.","He oído que algunos personajes sospechosos a menudo ofrecen sus 'servicios' a los capitanes de regata. Es tu decisión aceptar sus ofertas o no."));
			link.l1 = "Sí, sí, por supuesto... gracias, supongo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitMan";
		break;
		
		case "Regata_CitWom":
			dialog.text = LinkRandPhrase("¡Capitán, mi esposo y yo hemos apostado diez mil a tu victoria. ¡No nos defraudes! ¡Rezaré por ti!","¡Capitán! ¡Le deseo suerte!","Uhm... eres un capitán tan valiente y audaz...");
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitWom";
		break;
		
		case "Regata_CitHorse":
			dialog.text = LinkRandPhrase("¡Eh, marinero! ¡Saluda a la belleza! ¡Estaré esperando tu regreso!","¡Eh, marinero salado! La dama ha dicho que me dará como premio al ganador de la regata gratis... ¡Intenta ganar, eres tan apuesto!","¡No olvides visitarnos cuando regreses, guapo, te complaceremos según los más altos estándares!");
			link.l1 = "Bueno, ja... lo consideraré, ¡gracias!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_CitHorse";
		break;
		
		case "Regata_Prepare_1":
			if (sti(environment.time) < 12.0)
			{
				dialog.text = "Capitán, la regata comienza a las 12 en punto. Puede descansar ahora, estamos preparando la festividad. Vuelva al mediodía, sus competidores harán lo mismo.";
				link.l1 = "Muy bien, señor! Estaré esperando el comienzo...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Aquí estás, capitán.";
				link.l1 = "¡Yo y mi tripulación estamos listos, señor! Estoy esperando el comienzo...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_Prepare_1";
		break;
		
		case "Regata_Start":
			dialog.text = "Entonces, caballeros, aquí estamos. Anuncio el comienzo de la regata. Conocéis las reglas. Aquel que regrese aquí primero será alabado como vencedor. ¡Damas y caballeros, deseemos suerte a nuestros valientes capitanes!\n¡Caballeros! ¿Listos? ¡Preparados! ¡Listos! ¡Ya!";
			link.l1 = "...";
			link.l1.go = "Regata_Start_1";
		break;
		
		case "Regata_Start_1":
			DialogExit();
			PlaySound("people fight\mushketshot.wav");
			log_info("¡La regata ha comenzado! ¡Sube a bordo! ¡Rumbo a Belice!");
			for (i=1; i <=5; i++)
			{
				sld = characterFromId("Regata_Cap_F"+i);
				LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", -1);
			}
			Island_SetReloadEnableGlobal("Jamaica", false);//на остров нельзя
			SetFunctionTimerCondition("ReturnJamaicaNorm", 0, 0, 1, false);//таймер на возврат нормы
			LocatorReloadEnterDisable("Portroyal_town", "reload1_back", false);//откроем выход в море
			DeleteAttribute(pchar, "questTemp.Regata.Prepare");
			pchar.questTemp.Regata.Go = "true";
			pchar.questTemp.Regata.Town = "Beliz";
			pchar.quest.Regata_PU.win_condition.l1 = "locator";
			pchar.quest.Regata_PU.win_condition.l1.location = "Beliz_town";
			pchar.quest.Regata_PU.win_condition.l1.locator_group = "reload";
			pchar.quest.Regata_PU.win_condition.l1.locator = "reload10_back";
			pchar.quest.Regata_PU.win_condition.l2 = "Night";
			pchar.quest.Regata_PU.function = "RegataPU_Open";//вход в ПУ ночью
			//ситуации
			pchar.quest.Regata_ShYarder.win_condition.l1 = "location";
			pchar.quest.Regata_ShYarder.win_condition.l1.location = "Beliz_town";
			pchar.quest.Regata_ShYarder.function = "RegataShipyarder";
			sld = characterFromId("Beliz_shipyarder");
			LAi_RemoveLoginTime(sld);
			AddQuestRecord("Regata", "3");
		break;
		//старт регаты
		
		//верфист с парусами
		case "Regata_Shipyarder":
			dialog.text = "¡Saludos, capitán! Me han informado que está participando en la regata del Caribe.";
			link.l1 = "Es cierto. Las noticias realmente se esparcen por el archipiélago más rápido que el viento.";
			link.l1.go = "Regata_Shipyarder_1";
		break;
		
		case "Regata_Shipyarder_1":
			dialog.text = "Lo hacen, capitán. Tengo una propuesta para usted. Se trata de su barco y la regata.";
			link.l1 = "¡Je! Interesante. Te estoy escuchando, señor.";
			link.l1.go = "Regata_Shipyarder_2";
		break;
		
		case "Regata_Shipyarder_2":
			dialog.text = "Tengo un juego de velas perfectas para un lugre, están hechas del mejor algodón. Estas velas aumentarán la aceleración de tu barco y te darán una ventaja en tiempo sobre tus oponentes\nEstoy listo para vendértelas, eso es, si quieres comprarlas.";
			link.l1 = "¿Cuánto quieres por estas velas?";
			link.l1.go = "Regata_Shipyarder_3";
		break;
		
		case "Regata_Shipyarder_3":
			dialog.text = "Solo 15 000 pesos. Debes admitir que este es un precio muy modesto para una... situación como esta.";
			if (makeint(Pchar.money) >= 15000)
			{
				link.l1 = "Estoy de acuerdo. Estoy comprando estas nuevas velas para mi balandro. Aquí, tome su dinero, señor. ¿Sería tan amable de entregarlas a mi barco mientras hago el registro?";
				link.l1.go = "Regata_Shipyarder_4";
			}
			link.l2 = "No tengo tal dinero. Así que no podré comprar tus velas.";
			link.l2.go = "Regata_Shipyarder_exit";
		break;
		
		case "Regata_Shipyarder_4":
			AddMoneyToCharacter(pchar, -15000);
			dialog.text = "Se hará, señor. Mis hombres solo esperan la orden, y le prometo que no lo lamentará. Además, estas velas son de un bonito color azul. Su belleza lo apreciará.";
			link.l1 = "¡Está bien entonces! Bueno, tengo que irme y tú te encargas de las velas.";
			link.l1.go = "Shipyarder_exit";
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp))+12;//выиграл 12 часов у всех
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.(sTemp)));
			}
			RealShips[sti(Pchar.Ship.Type)].ship.upgrades.sails = 3;
			SetSailsColor(Pchar, 5);
			AddQuestRecord("Regata", "28");
		break;
		
		case "Regata_Shipyarder_exit":
			dialog.text = "Qué pena. Bueno, es tu elección. Adiós, capitán.";
			link.l1 = "¡Adiós!";
			link.l1.go = "Shipyarder_exit";
			pchar.questTemp.Regata.AdversarySecondTransition.Time.d = sti(pchar.questTemp.Regata.AdversarySecondTransition.Time.d)-16;//четвертый соперник выиграл 16 часов
			log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversarySecondTransition.Time.e));
			AddQuestRecord("Regata", "29");
		break;
		
		case "Shipyarder_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload5_back", "Beliz_Shipyard", "sit", "sit1", "ReturnRegataSYNorm", 5);
		break;
		//верфист с парусами
		
		//контрики с пушками
		case "Regata_Contra":
			dialog.text = "Hola, capitán "+GetFullName(pchar)+". Tenemos que hablar contigo... en realidad es solo una... propuesta de negocios.";
			link.l1 = "Mm. Interesante, ¿y cómo sabes quién soy?";
			link.l1.go = "Regata_Contra_1";
		break;
		
		case "Regata_Contra_1":
			dialog.text = "¿Qué puedo decir? Siempre me dijeron que tenía un don... Ja-ja, pues la Regata está en pleno apogeo y tú participas en ella, ¡eres un capitán famoso!";
			link.l1 = "Ya veo. Bueno, habla lo que piensas.";
			link.l1.go = "Regata_Contra_2";
		break;
		
		case "Regata_Contra_2":
			if (sti(pchar.questTemp.Regata.Index != 1))
			{
				sTemp = pchar.questTemp.Regata.ContraIndex;
				dialog.text = "Somos conscientes de que hay un participante más delante de ti, "+pchar.questTemp.Regata.AdversaryName.(sTemp)+" del "+pchar.questTemp.Regata.AdversaryShipName.(sTemp)+". Él dejó el puerto no hace mucho y pronto estará navegando por el cabo de Gonaives.";
			}
			else
			{
				dialog.text = "Somos conscientes de que hay un participante más justo detrás de ti, "+pchar.questTemp.Regata.AdversaryName.b+" de la "+pchar.questTemp.Regata.AdversaryShipName.b+"Él estará aquí en unas pocas horas.";
			}
			link.l1 = "Mm... estás muy bien informado.";
			link.l1.go = "Regata_Contra_3";
		break;
		
		case "Regata_Contra_3":
			if (sti(pchar.questTemp.Regata.Index != 1)) sTemp = "dejándote pasar por delante de él y tomar su posición";
			else sTemp = "por lo tanto estarás en cabeza durante mucho tiempo";
			dialog.text = "Absolutamente. Ahora vamos al grano. Te ofrecemos nuestra ayuda por tu dinero. Hemos colocado cuatro cañones de nuestro barco en el cabo detrás de la bahía de Gonaives. Cualquier barco de regata debe doblarlo\nLos cañones están cargados con balas encadenadas. Si llegamos a un acuerdo, le diré a nuestros amigos artilleros que arruinen las velas de tu competidor, para que se vea obligado a perder tiempo reparándolas."+sTemp+".";
			link.l1 = "¿Cuánto quieres por este servicio?";
			link.l1.go = "Regata_Contra_4";
			link.l2 = "No. No voy a usar tales métodos para ganar. Os equivocasteis conmigo. Adiós, caballeros.";
			link.l2.go = "Regata_Contra_exit";
		break;
		
		case "Regata_Contra_exit":
			dialog.text = "Bueno capitán, es su elección. Adiós.";
			link.l1 = "Gracias por la información sobre el cabo. Me mantendré alejado de él.";
			link.l1.go = "Contra_exit";
			AddQuestRecord("Regata", "31");
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
		break;
		
		case "Regata_Contra_4":
			if (sti(pchar.questTemp.Regata.Index != 1)) iTemp = 50000;
			else iTemp = 30000;
			dialog.text = "No mucho. Solo "+iTemp+" pesos. Y uno de tus competidores perderá casi dos días debido a... un accidente, ¡ja-ja!";
			if (makeint(Pchar.money) >= iTemp)
			{
				link.l1 = "¡Je! ¡Hablas con sensatez, amigo mío! Yo estoy pagando. Pero, ¿qué garantías tengo de que harás tu trabajo? ¿Y que no dispararás a mi barco cuando pase el cabo?";
				link.l1.go = "Regata_Contra_5";
			}
			link.l2 = "No tengo tanto dinero. Así que no podré usar tus servicios.";
			link.l2.go = "Regata_Contra_exit";
		break;
		
		case "Regata_Contra_5":
			dialog.text = "Capitán, por favor, somos contrabandistas, no unos piratas. Todos somos hombres honestos... a nuestra manera. Debes haber usado nuestros servicios antes, ¿verdad? Tienes mi palabra. Puedes confiar en ella.";
			link.l1 = "Bastante justo, muy bien toma tu dinero.";
			link.l1.go = "Regata_Contra_6";
		break;
		
		case "Regata_Contra_6":
			AddQuestRecord("Regata", "30");
			ChangeCharacterComplexReputation(pchar, "nobility", -3);
			dialog.text = "Os complacerá este trato, capitán. Y haré saber a mis muchachos de las armas sobre esto inmediatamente. ¡Buena suerte!";
			link.l1 = "Igualmente...";
			link.l1.go = "Contra_exit";
			if (sti(pchar.questTemp.Regata.Index != 1))
			{
				AddMoneyToCharacter(pchar, -50000);
				sTemp = pchar.questTemp.Regata.ContraIndex;
				pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp))+48;//задержка на 48 часов
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.(sTemp)));
			}
			else
			{
				AddMoneyToCharacter(pchar, -30000);
				pchar.questTemp.Regata.AdversaryThirdTransition.Time.b = sti(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b)+36;//задержка на 36 часов
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryThirdTransition.Time.b));
			}
		break;
		
		case "Contra_exit":
			DialogExit();
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("RegataContra_"+i);
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "quest", "quest2", "none", "", "", "", 10.0);
			}
		break;
		//контрики с пушками
		
		//падре
		case "Regata_Padre":
			pchar.questTemp.Regata.BranderName = GenerateRandomNameToShip(ENGLAND);
			dialog.text = "Buen día para ti, hijo mío. Quiero saludarte y humildemente preguntarte: ¿quieres contribuir al tesoro parroquial como un leal servidor de Inglaterra y nuestro gran Señor?";
			link.l1 = "Padre, la gente hace obras de caridad por el llamado de sus almas, no por compulsión. Estoy empezando a pensar que todos en el archipiélago han decidido robar a los capitanes de la regata...";
			link.l1.go = "Regata_Padre_exit";
			link.l2 = "Claro, santo padre. ¿Cuánto sería suficiente?";
			link.l2.go = "Regata_Padre_1";
		break;
		
		case "Regata_Padre_1":
			dialog.text = "Todo lo que tus deseos y posibilidades te permitan, hijo mío. Nuestra parroquia estará agradecida incluso por la suma más pequeña.";
			Link.l1.edit = 4;			
			link.l1 = "";
			link.l1.go = "Regata_Padre_2";
		break;
		
		case "Regata_Padre_2":
			iTemp = sti(dialogEditStrings[4]);
			if (iTemp <= 0 || sti(pchar.money) < iTemp)
			{
				dialog.text = "Esta es una actitud equivocada, hijo mío. Todos tenemos pecados, no olvides tu alma. Tendrás que presentarte ante nuestro Creador... y quizás pronto.";
				link.l1 = "No necesito tus sermones, santo padre. Adiós.";
				link.l1.go = "Padre_exit";
				ChangeCharacterComplexReputation(pchar, "nobility", -3);
				AddQuestRecord("Regata", "35");
				break;
			}
			if (iTemp > 0 && iTemp <= 1000)//ничего не скажет
			{
				dialog.text = "Nuestra parroquia y yo te agradecemos por este modesto regalo.";
				link.l1 = "De nada, santo padre.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "35");
			}
			if (iTemp > 1000 && iTemp <= 5000)//1 категория - намекнет
			{
				dialog.text = "Nuestro párroco y yo te agradecemos por este regalo. Y quiero advertirte, hijo mío, que algunos hombres pecadores pretenden hacerte daño. ¡Ten cuidado en el mar!";
				link.l1 = "Padre, todos los días la gente planea hacer algo contra mí... Pero gracias por preocuparte por mi destino.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "34");
				AddQuestUserData("Regata", "sMoney", iTemp);
			}
			if (iTemp > 5000 && iTemp <= 10000)//2 категория - скажет
			{
				dialog.text = "Agradezco en nombre de nuestra parroquia por este valioso regalo. A cambio, quiero advertirte que algunas personas realmente malas están conspirando contra ti. He oído que esos viles apóstatas planean hundir tu nave en este mismo puerto\nYa han preparado un barco lleno de pólvora para este malvado acto. Ten cuidado, hijo mío, estas almas perdidas están decididas en sus viles intenciones... ¡Bendígate!";
				link.l1 = "Gracias, santo padre. Estaré atento.";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -iTemp);
				AddQuestRecord("Regata", "33");
				AddQuestUserData("Regata", "sMoney", iTemp);
			}
			if (iTemp > 10000)//3 категория - расскажет полностью
			{
				dialog.text = "Eres muy generoso, hijo mío. La modestia de un humilde siervo de Dios no me permite aceptar toda la suma que estás dispuesto a donar para el bien de nuestra iglesia. Solo aceptaré 10 000 pesos\nA cambio, quiero advertirte que malas personas están conspirando contra ti. He oído que esos viles apóstatas planean hundir tu barco aquí mismo en este puerto\nHan preparado un lanchón lleno de pólvora llamado '"+pchar.questTemp.Regata.BranderName+", navega bajo la bandera inglesa para acercarse a ti sin causar sospechas. Ten cuidado, hijo mío, estas almas perdidas tienen serias intenciones viles.\nDestrúyelos, te doy absolución por este pecado. ¡Bendiciones! Rezaré por ti, hijo mío.";
				link.l1 = "Gracias, santo padre. ¡Si esos bastardos se atreven a hacer algo malo, los mandaré directo al infierno!";
				link.l1.go = "Padre_exit";
				AddMoneyToCharacter(pchar, -10000);
				ChangeCharacterComplexReputation(pchar, "nobility", 2);
				AddQuestRecord("Regata", "32");
				AddQuestUserData("Regata", "sText", pchar.questTemp.Regata.BranderName);
			}
		break;
		
		case "Regata_Padre_exit":
			dialog.text = "No te enojes, hijo mío. La ira es un pecado. Es tu derecho no hacer caridad. Camina en paz, hijo mío.";
			link.l1 = "Adiós, santo padre.";
			link.l1.go = "Padre_exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddQuestRecord("Regata", "35");					  
		break;
		
		case "Padre_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload7_back", "SentJons_church", "barmen", "stay", "ReturnRegataPadreNorm", 5);
		break;
		
		case "Regata_Spyglass":
			dialog.text = "¡Buen día para ti, capitán! Mi nombre es "+npchar.name+" y me gustaría...";
			link.l1 = "... ofrecerme algo... ¿Tengo razón, jovencita?";
			link.l1.go = "Regata_Spyglass_1";
		break;
		
		case "Regata_Spyglass_1":
			dialog.text = "¡Por supuesto, capitán! ¿Y por qué te sorprendes así? Eres un apuesto marinero y estás participando en la regata, seguro que todos están dispuestos a venderte algunas cosas navales útiles.";
			link.l1 = "Está bien, belleza, tienes razón. ¿Qué tienes para mí?";
			link.l1.go = "Regata_Spyglass_2";
		break;
		
		case "Regata_Spyglass_2":
			if(hrand(11) > 10)//отличная труба
			{
				pchar.questTemp.Regata.Spy = "spyglass4";
				sTemp = "an excellent spyglass";
				pchar.questTemp.Regata.SpyPrice = 20000;
				pchar.questTemp.Regata.SpyIndex = 12;//выигрыш - 12 часов
			}
			else
			{
				if(hrand(11) < 6)//обычная труба
				{
					pchar.questTemp.Regata.Spy = "spyglass2";
					sTemp = "an ordinary spyglass";
					pchar.questTemp.Regata.SpyPrice = 1800;
					pchar.questTemp.Regata.SpyIndex = 4;//выигрыш - 4 часа
				}
				else//хорошая труба - как пригодится
				{
					pchar.questTemp.Regata.Spy = "spyglass3";
					sTemp = "a good spyglass";
					pchar.questTemp.Regata.SpyPrice = 10000;
					pchar.questTemp.Regata.SpyIndex = 8;//выигрыш - 8 часов
				}
			}
			dialog.text = "Aquí, echa un vistazo. Lo he heredado de mi padre. Él también era un marinero como tú, y tenía un montón de cachivaches de navegación. No lo necesito, pero seguramente lo encontrarás útil. Solo pido "+FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice))+" por ello.";
			if (sti(pchar.money) >= sti(pchar.questTemp.Regata.SpyPrice))
			{
				link.l1 = "Vaya, vaya... "+sTemp+" ¡Interesante! Digo, te lo compraré. Por tus bonitos ojos. Entonces, ¿quieres "+FindRussianMoneyString(sti(pchar.questTemp.Regata.SpyPrice))+" por ello? Por favor, toma tu dinero.";
				link.l1.go = "Regata_Spyglass_3";
			}
			link.l2 = "Mm... ¿"+sTemp+"? No, muchacha, lo siento, pero no lo necesito. Ya tengo un catalejo muy bonito. Así que... ¡ay!";
			link.l2.go = "Regata_Spyglass_exit";
		break;
		
		case "Regata_Spyglass_3":
			AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Regata.SpyPrice));
			GiveItem2Character(pchar, pchar.questTemp.Regata.Spy);
			dialog.text = "Gracias, capitán. Espero que le sirva bien. Me alegra que lo haya encontrado útil. ¡Buena suerte en la regata!";
			link.l1 = "Gracias, "+npchar.name+"¡Adiós!";
			link.l1.go = "Spyglass_exit";
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp))+sti(pchar.questTemp.Regata.SpyIndex);//купил трубу - выиграл время
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
			}
		break;
		
		case "Regata_Spyglass_exit":
			dialog.text = "¡Qué lástima, capitán! Esperaba que te sería útil. Bueno, intentaré vendérselo a alguien más. ¡Adiós!";
			link.l1 = "Adiós, "+npchar.name+".";
			link.l1.go = "Spyglass_exit";
			pchar.questTemp.Regata.AdversaryFourthTransition.Time.c = sti(pchar.questTemp.Regata.AdversaryFourthTransition.Time.c)-sti(pchar.questTemp.Regata.SpyIndex);//третий соперник выиграл время
		break;
		
		case "Spyglass_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 10);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "Regata_SiegeOfficer":
			dialog.text = "Saludos, capitán. ¿No eres tú un participante de la regata? ¿Estoy en lo cierto?";
			link.l1 = "Sí. ¿Y cuál es el trato, oficial?";
			link.l1.go = "Regata_SiegeOfficer_1";
		break;
		
		case "Regata_SiegeOfficer_1":
			dialog.text = "Ya debes estar informado de que nuestra colonia está bajo asedio español. Por eso nuestro gobernador quiere hablar contigo. ¿Serías tan amable de hacerle una visita? Ahora mismo, el asunto es muy urgente.";
			link.l1 = "Mm... Muy bien, iré a ver a su Excelencia inmediatamente, aunque realmente no entiendo cómo puedo estar involucrado en las operaciones militares.";
			link.l1.go = "Regata_SiegeOfficer_2";
		break;
		
		case "Regata_SiegeOfficer_2":
			dialog.text = "Eres parte de esto, capitán. No perdamos tiempo y vayamos a la residencia. Sígueme.";
			link.l1.go = "Regata_SiegeOfficer_3";
		break;
		
		case "Regata_SiegeOfficer_3":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload3_back", "Bridgetown_townhall", "goto", "governor1", "RegataSiegeHover", -1);
		break;
		
		case "Regata_SiegeOfficer_4":
			dialog.text = "¡Señor! Estoy listo para enviar a los civiles a su barco. ¿Nos vamos ahora?";
			link.l1 = "Sí, claro. Vamos a zarpar de inmediato. Dile a la gente que suban a los botes.";
			link.l1.go = "Regata_SiegeOfficer_5";
		break;
		
		case "Regata_SiegeOfficer_5":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "RegataSiegeOpen", -1);
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorGoToLocation(sld, "quest", "quest1", "none", "", "", "", 30);
			}
		break;
		
		case "Regata_SiegeOfficer_6":
			dialog.text = "Lo hicimos... Parece que este balandro era un explorador del escuadrón y esos malditos castellanos estaban merodeando. Capitán, por favor, ayúdeme a llevar a las mujeres a las cavernas, hay una posibilidad de que haya más destacamentos españoles.";
			link.l1 = "Está bien. ¡Vamos!";
			link.l1.go = "Regata_SiegeOfficer_7";
		break;
		
		case "Regata_SiegeOfficer_7":
			DialogExit();
			sld = characterFromId("SiegeOfficer");
			LAi_ActorFollowEverywhere(sld, "", -1);
			pchar.quest.Regata_Siege3.win_condition.l1 = "location";
			pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
			pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
		break;
		
		case "Regata_SiegeOfficer_8":
			dialog.text = "¡Gracias por tu ayuda, capitán! Si no fuera por ti y tu valentía... Eres un verdadero héroe, has completado esta operación a pesar de todos los peligros y tus propios intereses. He estado pensando en cómo recompensarte... y hay una manera de mejorar tus posibilidades en la regata.";
			link.l1 = "Interesante. ¿Qué hay por este camino?";
			link.l1.go = "Regata_skiper";
		break;
		
		case "Regata_Hovernor":
			dialog.text = "Saludos, capitán "+GetFullName(pchar)+" . Es bueno que hayas venido. Nuestro pueblo necesita de tu ayuda.";
			link.l1 = "Señor, si habla del escuadrón español que está asaltando su colonia en este momento, entonces no tengo idea de cómo puedo ayudarle. Comando una balandra, no un navío de línea...";
			link.l1.go = "Regata_Hovernor_1";
		break;
		
		case "Regata_Hovernor_1":
			dialog.text = "Escúchame, capitán, y entenderás. Estamos en un grave problema. La ciudad está bajo el asedio español. Una batalla decisiva con el fuerte está a punto de comenzar. Además, unos cientos de españoles ya han desembarcado y bloqueado todas las salidas de la ciudad, ahora pueden atacarnos desde el mar y la tierra\nLa guarnición del fuerte se está preparando para defender la ciudad del escuadrón y no hay suficientes soldados en el asentamiento mismo. Todo hombre capaz de manejar un arma está movilizado, pero ¿qué hay de los demás?\nHay cien almas de mujeres en Bridgetown. ¿Puedes imaginar lo que les sucederá si no logramos proteger nuestra colonia? Creo que lo entiendes.";
			link.l1 = "Señor, le entiendo, pero, de nuevo, ¿cómo puedo ayudar? ¿Qué quiere de mí? ¿Que luche contra navíos de línea o que me aliste con mi tripulación en la milicia de la ciudad?";
			link.l1.go = "Regata_Hovernor_2";
		break;
		
		case "Regata_Hovernor_2":
			switch (sti(Pchar.BaseNation))
			{
				case ENGLAND: sTemp = "Usted es inglés, ayúdenos a salvar a los ciudadanos ingleses y lo que es importante a las mujeres." break;
				case FRANCE: sTemp = "Eres francés, así que básicamente eres nuestro aliado, ayúdanos a salvar a los ciudadanos ingleses y lo que es más importante a las mujeres." break;
				case SPAIN: sTemp = "Sé que sois españoles y que vuestra gente está en el mar, así que sé que te estoy pidiendo mucho, pero estas mujeres son inocentes y no tienen nada que ver con esta batalla. ¡Así que por favor os lo ruego, ayudadlas!" break;
				case HOLLAND: sTemp = "Sé que sois holandeses y que nuestras naciones están en guerra, pero estáis participando en la regata inglesa bajo bandera inglesa. ¿No cree que es justo luchar por gente inocente y pacífica como estas mujeres? ¡Por favor, capitán, ayúdelas!" break;
			}
			dialog.text = "Ni uno ni otro. Te pido solo una cosa. Lleva a las mujeres y los niños lejos de aquí en tu barco. No son muchos, alrededor de cien. Llévalos a Cabo Harrison junto con el teniente Mahony, él se asegurará de que estén seguros en la cueva.\nEstoy seguro de que los españoles no los buscarán. No tengo barcos de sobra, todo lo que teníamos fue hundido por el escuadrón español. Eres mi última esperanza. Puedes llevarlos al cabo en un solo viaje, aunque tu nave estará sobrecargada. Los navíos de línea no te seguirán.\nNo puedo pedirle a nadie más que lo haga."+sTemp+"";
			link.l1 = "Señor, lo siento, pero mi barco ya está sobrecargado y no podrá llevar a tanta gente ni siquiera en dos viajes. Cualquier bala de cañón que caiga cerca enviará mi barco y a sus mujeres al fondo del mar. Perdóneme, pero no puedo ayudarle.";
			link.l1.go = "Regata_Hovernor_exit";
			link.l2 = "Muy bien, señor. Te ayudaré. El honor del marinero me obliga a hacerlo.";
			link.l2.go = "Regata_Hovernor_3";
		break;
		
		case "Regata_Hovernor_3":
			dialog.text = "Me alegra que hayas aceptado. Eres un verdadero soldado. El teniente Mahony llevará a mujeres y niños a tu barco. ¡Buen viaje, Capitán!";
			link.l1 = "Gracias, señor. ¡No perdamos tiempo!";
			link.l1.go = "Regata_Hovernor_4";
		break;
		
		case "Regata_Hovernor_wait":
			dialog.text = "Apresúrate, capitán. El tiempo se acaba.";
			link.l1 = "¡Ya estoy navegando!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_Hovernor_wait";
		break;
		
		case "Regata_Hovernor_exit":
			dialog.text = "Esto es increíble. ¿Ni siquiera vas a intentarlo? Bueno, estás en tu derecho. No puedo exigirte nada. Si fueras solo un capitán ordinario, confiscaría tu barco por el bien de un centenar de mujeres, pero estás participando en una regata, y por lo tanto estás bajo la protección del gobernador general de las colonias inglesas\nEsperaba que tu conciencia te guiara mejor, pero me equivoqué. ¡Ve y que Dios sea misericordioso con tu alma!";
			link.l1 = "Adiós, señor.";
			link.l1.go = "Hovernor_exit";
		break;
		
		case "Hovernor_exit":
			DialogExit();
			pchar.quest.Regata_TH.over = "yes"; // belamour снять прерывание
			pchar.questTemp.Regata.AdversaryFifthTransition.Time.e = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.e)-36;//пятый противник выиграл 36 часов
			ChangeCharacterComplexReputation(pchar, "nobility", -8);
			ChangeCharacterNationReputation(pchar, ENGLAND, -5);
			//вертаем губера в норму
			npchar.Dialog.Filename = "Common_Mayor.c";
			npchar.dialog.currentnode = "First time";
			//удаляем лейтенанта
			sld = characterFromId("SiegeOfficer");
			sld.lifeday = 0;
			//открываем ворота и выход в море
			bDisableFastReload = false;
			LocatorReloadEnterDisable("Bridgetown_town", "reload1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "reload2_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
			LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
			//остров в норму
			n = FindIsland("Barbados");	
			DeleteAttribute(Islands[n], "DontSetShipInPort");
			//осаду снимем через 5 дней
			SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
			for (i=1; i <=9; i++)//девок счистим
			{
				sld = characterFromId("RegataBridgWom_"+i);
				sld.lifeday = 0; // patch-7
				LAi_CharacterDisableDialog(sld);
			}
			AddQuestRecord("Regata", "38");
			AddQuestUserData("Regata", "sName", GetFullName(npchar));
		break;
		
		case "Regata_Hovernor_4":
			DialogExit();
			pchar.quest.Regata_TH.over = "yes"; // belamour снять прерывание
			NextDiag.CurrentNode = "Regata_Hovernor_wait";
			sld = characterFromId("SiegeOfficer");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload2", "Bridgetown_town", "goto", "goto4", "", 10);
			pchar.quest.Regata_evacuation.win_condition.l1 = "location";
			pchar.quest.Regata_evacuation.win_condition.l1.location = "Bridgetown_town";
			pchar.quest.Regata_evacuation.function = "RegataSiegeEvacuation";
			AddQuestRecord("Regata", "36");
			AddQuestUserData("Regata", "sName", GetFullName(npchar));
		break;
		
		case "Regata_BridgWom":
			dialog.text = "¡Los españoles están sobre nosotros! ¡Dios, ayúdanos!";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_BridgWom";
		break;
		
		case "Regata_BridgWom_1":
			dialog.text = "El teniente Mahony está muerto... debe ser una pesadilla. Era un oficial valiente. Capitán, ¿podría llevarnos a una caverna? Solo llévenos allí y nos encargaremos de nosotros mismos.";
			link.l1 = "Claro. ¡Sígueme!";
			link.l1.go = "Regata_BridgWom_2";
		break;
		
		case "Regata_BridgWom_2":
			DialogExit();
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			pchar.quest.Regata_Siege3.win_condition.l1 = "location";
			pchar.quest.Regata_Siege3.win_condition.l1.location = "Barbados_cave";
			pchar.quest.Regata_Siege3.function = "RegataBarbadosCave";
		break;
		
		case "Regata_BridgWom_3":
			dialog.text = "Aquí estamos... ¡gracias, capitán! ¡Acabas de salvarnos a todos! He estado pensando en cómo recompensarte... hay una manera de mejorar tus posibilidades en la regata.";
			link.l1 = "Continúa.";
			link.l1.go = "Regata_skiper";
		break;
		
		case "Regata_skiper":
			pchar.questTemp.Regata.Name = GetFullName(npchar);
			dialog.text = "¿Te diriges a Port Royal? La ruta más corta pasa por Curazao. Regresa a Bridgetown. Busca a un hombre llamado Woodrow Dougherty, es un viejo marinero y un navegante experimentado. Conoce perfectamente la zona entre Barbados y Jamaica, sería de gran ayuda para ti.\nEsto te ahorrará mucho tiempo crítico que tanto necesitas para ganar. Encuentra al hombre en la iglesia y dile que "+GetFullName(npchar)+" te ha enviado, no te rechazará. Llévalo a Port Royal, de todos modos iba a zarpar allí.";
			link.l1 = "¡Muy bien! Un buen navegante me será útil. Adiós.";
			link.l1.go = "Regata_skiper_1";
		break;
		
		case "Regata_skiper_1":
			dialog.text = "¡Adiós, capitán! ¡Buena suerte!";
			link.l1 = "Quizás, nos encontremos de nuevo...";
			link.l1.go = "Regata_skiper_2";
		break;
		
		case "Regata_skiper_2":
			DialogExit();
			AddQuestRecord("Regata", "37");
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			ChangeCharacterNationReputation(pchar, ENGLAND, 10);
			LAi_SetStayType(npchar);
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0; // patch-8
			for (i=1; i <=9; i++)
			{
				sld = characterFromId("RegataBridgWom_"+i);
				LAi_SetStayType(sld);
				LAi_CharacterDisableDialog(sld);
				sld.lifeday = 0; // patch-8
			}
			//вертаем губера в норму
			sld = characterFromId("Bridgetown_Mayor");
			sld.Dialog.Filename = "Common_Mayor.c";
			sld.dialog.currentnode = "First time";
			//открываем ворота и выход в море
			LocatorReloadEnterDisable("Shore4", "boat", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate1_back", false);
			LocatorReloadEnterDisable("Bridgetown_town", "gate_back", false);
			LocatorReloadEnterDisable("Bridgetown_Exittown", "reload3", false);
			LocatorReloadEnterDisable("Barbados_cave", "reload1", false);
			bQuestDisableMapEnter = false;
			//осаду снимем через 5 дней
			SetFunctionTimerCondition("RegataSiegeDelete", 0, 0, 5, false);
			RegataSiegeSkiper();//поставим Вудро в церковь
		break;
		
		case "Regata_SiegeSkiper":
			dialog.text = "Buen día. ¿Quieres algo?";
			link.l1 = "¿Tu nombre es Woodrow Dougherty, verdad?";
			link.l1.go = "Regata_SiegeSkiper_1";
		break;
		
		case "Regata_SiegeSkiper_1":
			dialog.text = "Eres  correcto. ¿Cómo puedo ser de servicio?";
			link.l1 = "Sé que eres un navegante experimentado y conoces bien las aguas entre Barbados y Curazao. También sé que quieres llegar a Port Royal. Soy participante de la regata y hay una última parada: Port Royal. Quiero pedirte que te unas a mi tripulación como navegante para este último viaje.  ";
			link.l1.go = "Regata_SiegeSkiper_2";
		break;
		
		case "Regata_SiegeSkiper_2":
			dialog.text = "Interesante... ¿Y por qué piensas que me uniré a tu tripulación?";
			link.l1 = "Bueno, porque oí hablar de ti por "+pchar.questTemp.Regata.Name+" con todas las garantías de que no te negarás. Y por mi ayuda a Bridgetown en este momento crítico...";
			link.l1.go = "Regata_SiegeSkiper_3";
		break;
		
		case "Regata_SiegeSkiper_3"://а тут - как уж свезет
			if(hrand(2) != 2)
			{
				dialog.text = "¿De "+pchar.questTemp.Regata.Name+"? Ya veo, claro. Está bien, capitán, le ayudaré a navegar por el camino más corto a Port Royal. ¿Piensa zarpar ahora?";
				link.l1 = "Sí.";
				link.l1.go = "Regata_SiegeSkiper_4";
			}
			else
			{
				dialog.text = "¿"+pchar.questTemp.Regata.Name+"? Entiendo. Pero, capitán, no puedo dejar mi ciudad en un momento tan peligroso. Debes entenderme como un soldado que nos brindó una ayuda desinteresada\nNo quiero que la gente murmure a mis espaldas que el viejo Woodrow huyó ante la batalla final contra los españoles. Me quedaré. No guardes rencor, capitán.";
				link.l1 = "¿Y esta es tu última palabra? Pero he ayudado a tu colonia...";
				link.l1.go = "Regata_SiegeSkiper_6";
			}
		break;
		
		case "Regata_SiegeSkiper_4":
			dialog.text = "Entonces no perdamos tiempo. Déjame empacar mis cosas y estaré a tu disposición.";
			link.l1 = "Mis marineros te estarán esperando en el muelle y te llevarán al 'Santa Catalina'. ¡Gracias, Woodrow!";
			link.l1.go = "SiegeSkiper_hire";
		break;
		
		case "Regata_SiegeSkiper_6":
			dialog.text = "Capitán, la regata es un deporte y el asedio español de mi hogar es una vida. No voy a ir contigo a ninguna parte. Y me repetiré, tienes que entenderme: el honor y el deber todavía significan algo en este mundo. Esta es mi última palabra y no voy a cambiarla\nSin embargo, puedo darte un consejo sobre cómo llegar allí en poco tiempo a través de la ruta más segura, navega al noroeste hacia Dominica y desde allí dirígete hacia Martinica o Guadalupe, depende de ti y del viento. Luego navega directamente hacia Port-Royal, o podrías navegar por Curazao, lo cual no recomendaría, pero si te llevas bien con los holandeses, entonces por supuesto que sí.";
			link.l1 = "Bueno, gracias... pero estoy decepcionado. Adiós, Woodrow.";
			link.l1.go = "SiegeSkiper_exit";
		break;
		
		case "SiegeSkiper_exit":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
			npchar.lifeday = 0;
		break;
		
		case "SiegeSkiper_hire":
			chrDisableReloadToLocation = true;//закрыть локацию
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "OpenTheDoors", 10.0);
			npchar.quest.OfficerPrice = sti(pchar.rank)*500;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true; //не пытаться уйти
			npchar.loyality = 25;
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NextDiag.CurrentNode = NextDiag.TempNode;
			//пересчитываем время пятого перехода
			for (i=1; i <=5; i++)
			{
				if (i==1) sTemp = "a";
				if (i==2) sTemp = "b";
				if (i==3) sTemp = "c";
				if (i==4) sTemp = "d";
				if (i==5) sTemp = "e";
				pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) = sti(pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp))+18+(rand(18));//выигрыш до 1.5 суток
				log_testinfo(FindRussianDaysString(pchar.questTemp.Regata.AdversaryFourthTransition.Time.(sTemp)));
			}
			SetFunctionTimerCondition("SiegeSkiperOver", 0, 0, 15, false);//чтобы не присвоил офицера
			DialogExit();
		break;
		
		case "Regata_Finish":
		iTest = FindColony("Portroyal"); 
		if (iTest != -1)
		{
			rColony = GetColonyByIndex(iTest);
			sFrom_sea = rColony.from_sea;
		}
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if(sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)//проверка на наличие корабля в порту
		{
			//снимаем запреты
			bQuestDisableMapEnter = false;//открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			bool bRegLugger = sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_LUGGER || sti(RealShips[sti(pchar.ship.type)].basetype) == SHIP_CAREERLUGGER;
			if (CheckAttribute(pchar, "questTemp.Regata.Breach") || !CheckAttribute(pchar, "questTemp.Regata.Bridgetown") || GetCompanionQuantity(pchar) > 1 || !bRegLugger || pchar.Ship.Name != "Saint Catherine")
			{
				dialog.text = "Has roto las reglas de la regata en la última etapa. Tu resultado fue descalificado. No tengo nada más que decirte, capitán.";
				link.l1 = "Eh...¡qué demonios! Bueno, no hay nada que hacer entonces, fuiste demasiado atento. ¡Adiós!";
				link.l1.go = "exit";
				npchar.lifeday = 1;
				DeleteAttribute(pchar, "questTemp.Regata");
				AddQuestRecord("Regata", "45");
				CloseQuestHeader("Regata");
			}
			else
			{
				n=1;
				for (i=1; i <=5; i++)
				{
					if (i==1) sTemp = "a";
					if (i==2) sTemp = "b";
					if (i==3) sTemp = "c";
					if (i==4) sTemp = "d";
					if (i==5) sTemp = "e";
					if (pchar.questTemp.Regata.AdversaryFifthTransition.Time.(sTemp) < sti(pchar.questTemp.Regata.FifthTransitionTime)) n++;
					pchar.questTemp.Regata.Result = n;//место в регате
				}
				if (n==1)
				{
					dialog.text = "Capitán "+GetFullName(pchar)+", ¡mis felicitaciones! Tomó "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" horas para que termines la regata y has dejado a todos tus oponentes muy atrás. ¡Este es un resultado notable!";
					link.l1 = "¡Gracias por sus amables palabras, señor!";
					link.l1.go = "First_result";
				}
				else
				{
					if (n==6)
					{
						dialog.text = "Capitán, ay, pero tu resultado es el peor, has gastado "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" horas. No estés triste, tuviste oponentes realmente duros.";
						link.l1 = "No estoy triste, señor. Me alegra haber participado en la regata y haber probado mis habilidades.";
						link.l1.go = "Other_result";
						AddQuestRecord("Regata", "44");
						CloseQuestHeader("Regata");
					}
					else
					{
          				dialog.text = "Capitán, estás en "+n+"lugar. Felicitaciones por el exitoso resultado, has demostrado un tiempo digno, "+sti(pchar.questTemp.Regata.FifthTransitionTime)+" horas. ¡Felicidades a pesar de tu pérdida!";
						link.l1 = "Está bien, señor. Me alegra haber mostrado un buen resultado en esta dura competencia.";
						link.l1.go = "Other_result";
						if (n==2) AddQuestRecord("Regata", "40");
						if (n==3) AddQuestRecord("Regata", "41");
						if (n==4) AddQuestRecord("Regata", "42");
						if (n==5) AddQuestRecord("Regata", "43");
						CloseQuestHeader("Regata");
					}
				}
			}
			Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("SiegeSkiper");
			sld = &Characters[sti(Pchar.questTemp.FiringOfficerIDX)];
			CheckForReleaseOfficer(sti(Pchar.questTemp.FiringOfficerIDX));
			RemovePassenger(Pchar, sld);
			DeleteAttribute(sld, "Payment");
			DeleteAttribute(Pchar, "questTemp.FiringOfficerIDX");//удаляем из офицеров
			log_info("Woodrow Dougherty ha desembarcado");
			pchar.quest.SiegeSkiperOver.over = "yes"; //снять таймер
		}
		else
		{
			dialog.text = "Señor, déjeme preguntarle algo, ¿dónde está su barco? No lo veo...";
			link.l1 = "Lo siento, señor. La llevaré al puerto inmediatamente.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Regata_Finish";
		}
		break;
		
		case "First_result":
			if (CheckAttribute(pchar, "questTemp.Regata.Rate")) sTemp = "Venga a verme a mi despacho. Te daré el premio por tu apuesta.";
			else sTemp = "Y si hubieras hecho una apuesta por tu victoria como te ofrecí, también te habrías llevado un premio extra.";
			dialog.text = "Visita al gobernador general mañana y él te dará tus 250 000 pesos y valiosos regalos. "+sTemp+" No abandones el pueblo, según las tradiciones los premios se entregarán al tesoro del pueblo en caso de que el ganador no los reclame en el plazo de una semana.";
			link.l1 = "Lo tengo, señor. ¡Lo visitaré mañana!";
			link.l1.go = "First_result_1";
		break;
		
		case "First_result_1":
			DialogExit();
			//npchar.lifeday = 7;
			Achievment_Set("ach_09");
			npchar.dialog.currentnode = "Other_result_repeat";
			pchar.questTemp.Regata.Win = "true";
			pchar.quest.Regata_Final.win_condition.l1 = "Timer";
			pchar.quest.Regata_Final.win_condition.l1.date.hour  = 6.0;
			pchar.quest.Regata_Final.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Regata_Final.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Regata_Final.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Regata_Final.function = "RegataFinal";
			SetFunctionTimerCondition("RegataFinalOver", 0, 0, 8, false);//таймер не снимаем - через 8 дней подчистится все автоматически
			// слухи
			AddSimpleRumour("¡Ah, eres el legendario capitán, el ganador de la regata! Es un placer verte en persona.", ENGLAND, 60, 10);
			AddSimpleRumour("Ja, mira esto, un maestro del viento y las olas, ¡el ganador de la regata! Tienes mi respeto...", ENGLAND, 60, 10);
			AddSimpleRumour("Oh, un gran navegante, un rey del viento y del mar, ¡el ganador de la regata ha visitado nuestra ciudad! Nos alegramos de verle, capitán.", ENGLAND, 60, 10);
			AddSimpleRumour("Ah, sí, tuve la suerte de charlar con una leyenda viva, el capitán capaz de cruzar el archipiélago en tres días ¡incluso con el viento en contra! ¡Mis respetos, capitán!", ENGLAND, 60, 10);
			AddSimpleRumour("¡Ah, así que usted es el legendario capitán, el ganador de la regata! Encantado de verle.", FRANCE, 60, 10);
			AddSimpleRumour("Ja, ¿no eres tú el maestro del viento y las olas, el ganador de la regata? Tienes mis respetos...", FRANCE, 60, 10);
			AddSimpleRumour("Oh, un gran navegante, un rey del viento y del mar, ¡el ganador de la regata ha visitado nuestra ciudad! Nos alegramos de verle, capitán.", FRANCE, 60, 10);
			AddSimpleRumour("Sí, tuve la suerte de charlar con una leyenda viva, el capitán capaz de cruzar el archipiélago en tres días ¡incluso con el viento en contra! ¡Mis respetos, capitán!", FRANCE, 60, 10);
			// экспа
			AddComplexSeaExpToScill(2000, 300, 300, 0, 500, 500, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 2000);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 1000);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 300);//скрытность
			ChangeCharacterComplexReputation(pchar, "authority", 10);
			ChangeCharacterComplexReputation(pchar, "fame", 15);
			ChangeOfficersLoyality("good_all", 3);
			AddQuestRecord("Regata", "39");
			CloseQuestHeader("Regata");
		break;
		
		case "Other_result":
			dialog.text = "Es bueno escuchar una respuesta honorable. ¡Buena suerte, capitán!";
			link.l1 = "Adiós, señor.";
			link.l1.go = "Other_result_1";
		break;
		
		case "Other_result_1":
			DialogExit();
			npchar.dialog.currentnode = "Other_result_repeat";
			SetFunctionTimerCondition("RegataFinalOver", 0, 0, 1, false);
			// экспа
			AddComplexSeaExpToScill(500, 100, 100, 0, 100, 100, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 200);//авторитет
			AddCharacterExpToSkill(pchar, "Fortune", 100);//везение
			AddCharacterExpToSkill(pchar, "Sneak", 100);//скрытность
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;
		
		case "Other_result_repeat":
			dialog.text = "¿Quieres algo más, capitán?";
			link.l1 = "No... no es nada.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Other_result_repeat";
		break;
		
		case "Give_advantage":
			dialog.text = "Ah, ahí estás, señor "+GetFullName(pchar)+"  Me alegra verte. ¿Estás aquí por tu premio? Está listo para ti.";
			link.l1 = "¡Es bueno oír eso! ¿Cuál es el tamaño de mi premio adicional?";
			link.l1.go = "Give_advantage_1";
		break;
		
		case "Give_advantage_1":
			dialog.text = "Considerando todos los riesgos, tu premio final es "+FindRussianMoneyString(makeint(pchar.questTemp.Regata.Advantage))+" Por favor, tómalo. ¡Felicitaciones!";
			link.l1 = "¡Gracias!";
			link.l1.go = "Give_advantage_2";
		break;
		
		case "Give_advantage_2":
			AddMoneyToCharacter(pchar, makeint(pchar.questTemp.Regata.Advantage));
			dialog.text = "Claro, tu popularidad entre los ciudadanos de Port Royal ha crecido. Creo que puedes ver eso... pero, por desgracia, la memoria del pueblo es corta. ¡Así que báñate en la gloria mientras aún brilla tanto!";
			link.l1 = "Hablas de las cosas más agradables, señor... Bueno, veamos cómo es bañarse en la gloria. ¡Adiós! Fue un placer.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Other_result_repeat";
		break;
		
		case "Regata_CitMan_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "¡Felicidades por tu victoria, capitán! ¡Un resultado excelente!";
						link.l1 = "¡Gracias!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "No estés triste, capitán. No es fácil ganar la regata, ¡incluso participar en ella es un privilegio!";
						link.l1 = "No te preocupes por mí. Estoy satisfecho con mi resultado.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "¡Me alegra verte, capitán! Deberías registrarte hablando con sir Stevenson.";
					link.l1 = "Ya veo. ¡Voy en camino hacia él!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "¡Ah, capitán, por qué has fallado así y en la última etapa!";
				link.l1 = "Sí, qué estúpido de mi parte...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitMan_1";
		break;
		
		case "Regata_CitWom_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "¡Enhorabuena por tu victoria, capitán! ¡Un resultado excelente!";
						link.l1 = "¡Gracias!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "No esté triste, capitán. No es fácil ganar la regata, ¡incluso participar en ella es un privilegio!";
						link.l1 = "No te preocupes por mí. Estoy satisfecho con mi resultado.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "¡Me alegra verte, capitán! Deberías registrarte hablando con sir Stevenson.";
					link.l1 = "Ya veo. ¡Estoy en camino!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "¡Ah, capitán, por qué has fallado así y en la última etapa!";
				link.l1 = "Sí, qué tonto de mi parte...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitWom_1";
		break;
		
		case "Regata_CitHorse_1":
			if (CheckAttribute(pchar, "questTemp.Regata"))
			{
				if (CheckAttribute(pchar, "questTemp.Regata.Result"))
				{
					if (sti(pchar.questTemp.Regata.Result) == 1)
					{
						dialog.text = "¡Felicitaciones por tu victoria, capitán! ¡Un resultado excelente!";
						link.l1 = "¡Gracias!";
						link.l1.go = "exit";
					}
					else
					{
						dialog.text = "No estés triste, capitán. No es fácil ganar en la regata, ¡incluso participar en ella es un privilegio!";
						link.l1 = "No te preocupes por mí. Estoy satisfecho con mi resultado.";
						link.l1.go = "exit";
					}
				}
				else
				{
					dialog.text = "¡Me alegra verte, capitán! Deberías registrarte hablando con el señor Stevenson.";
					link.l1 = "Ya veo. ¡Estoy en camino!";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "¡Ah, capitán, por qué has fracasado así y en la última etapa!";
				link.l1 = "Sí, qué estúpido de mi parte...";
				link.l1.go = "exit";
			}
			NextDiag.TempNode = "Regata_CitHorse_1";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}

void CreateRegataAdversaries()
{
	string sTemp;
	for (int i=0; i<=4; i++)
	{
	if (i==0) sTemp = "a";
	if (i==1) sTemp = "b";
	if (i==2) sTemp = "c";
	if (i==3) sTemp = "d";
	if (i==4) sTemp = "e";
	pchar.questTemp.Regata.AdversaryName.(sTemp) = GenerateRandomName_Generator(i, "man");
	pchar.questTemp.Regata.AdversaryShipName.(sTemp) = GenerateRandomNameToShip(ENGLAND);
	pchar.questTemp.Regata.AdversarySpeed.(sTemp) = 0.4+frand(0.9);
	log_testinfo(FindRussianDaysString(stf(pchar.questTemp.Regata.AdversarySpeed.(sTemp))));
	}
}
