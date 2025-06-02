void ProcessDialogEvent()
{
	ref NPChar, sld, location;
	aref Link, NextDiag;
	string sTemp, sTemp1, str, str1;
	int s1, s2, s3, s4, s5, p1, iColony, crewWhoreCost, charWhoreCost = 0;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Brothel\" + NPChar.City + "_Brothel.c ";
						 if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--
	crewWhoreCost = 50 + 7 * MOD_SKILL_ENEMY_RATE - hrand(40);
	charWhoreCost = 2460 + sti(pchar.rank) * 40;

	switch (Dialog.CurrentNode)
	{
	// ============= хозяйка борделя =============
	case "First time":
		if (LAi_grp_playeralarm > 0)
		{
			dialog.text = NPCharRepPhrase(pchar, LinkRandPhrase("" + GetSexPhrase("¿Qué chicas, querido?! ¡La mitad de la guarnición te persigue, y vienes directamente al burdel!", "¡Piérdete, lo harás? ¡La mitad de la guarnición está tras de ti!") + "", "Cada guardia de la ciudad te está buscando. No soy un tonto para ofrecerte servicios en este momento...", "¡No tienes nada que hacer aquí!"), LinkRandPhrase("" + GetSexPhrase("¡Solo atrévete a tocar a mis chicas y te desollaré vivo!", "¡Piérdete, desgraciado!") + "", "Sucio" + GetSexPhrase("", "") + "¡Asesino, sal de mi establecimiento, ahora! ¡Guardias!!!", "No tengo miedo de ti, " + GetSexPhrase("granuja", "rata") + "¡Pronto serás colgado en nuestro fuerte, no llegarás lejos..."));
			link.l1 = NPCharRepPhrase(pchar, RandPhraseSimple("Je, una alarma nunca es un problema para mí...", "Jamás me atraparán."), RandPhraseSimple("Solo cállate, vieja estúpida.", "Cállate si no quieres problemas..."));
			link.l1.go = "exit";
			break;
		}
		//--> прибыла инспекция на Святом Милосердии
		if (CheckAttribute(npchar, "quest.SantaMisericordia"))
		{
			dialog.text = "Oh, " + GetSexPhrase("joven", "dulce niño") + ", estamos cerrados hoy.";
			link.l1 = "¿Cerrado?";
			link.l1.go = "SantaMisericordia_1";
			break;
		}
		//<-- прибыла инспекция на Святом Милосердии
		//--> Мерзкий Божок
		if (CheckAttribute(pchar, "questTemp.ChickenGod.HostessDialog"))
		{
			dialog.text = "¡Oh, Dios mío! ¿Cómo entraste aquí? Querido capitán, por favor vete, te lo ruego ¡Nuestro establecimiento está cerrado en este momento!";
			link.l1 = "Encantado de verte, querido " + npchar.name + ". Estaba en la lista de invitados. Sin embargo, en tales establecimientos, incluso los invitados tienen que pagar, así que... Por favor, no me lo hagas demasiado difícil, pero quiero pagar por una habitación.";
			link.l1.go = "chicken_god";

			DeleteAttribute(pchar, "questTemp.ChickenGod.HostessDialog");
			break;
		}
		//<-- Мерзкий Божок
		//--> туториал Мартиника
		if (CheckAttribute(pchar, "questTemp.Sharlie.Gigolo") && pchar.questTemp.Sharlie.Gigolo == "start" && npchar.location == "FortFrance_SecBrRoom")
		{
			DelLandQuestMark(npchar);
			link.l1 = "Escucha, Aurora, necesito una chica para la noche. Y quiero llevarla a casa conmigo. ¿Puedes arreglar eso?";
			link.l1.go = "Gigolo";
			break;
		}
		//<-- туториал Мартиника
		// Jason --> Заносчивый аристократ
		if (!CheckAttribute(pchar, "GenQuest.Badboy") && !CheckAttribute(npchar, "quest.Badboy") && !CheckAttribute(pchar, "questTemp.ZA.Block") && makeint(environment.time) > 15.0 && makeint(environment.time) < 21.0 && sti(pchar.questTemp.HorseQty) > 4)
		{
			dialog.text = "Eres un hombre tan distinguido. Además, a mis chicas les gustas mucho. Me gustaría pedirte un pequeño favor para mi establecimiento.";
			link.l5 = "Me halaga, eso es seguro. ¿Con qué necesitas mi ayuda?";
			link.l5.go = "Badboy";
			link.l8 = "Lo siento, pero estoy ocupado en este momento.";
			link.l8.go = "exit";
			npchar.quest.Badboy = "true";
			break;
		}

		if (CheckAttribute(pchar, "GenQuest.Badboy.Complete") || CheckAttribute(pchar, "GenQuest.Badboy.Continue"))
		{
			if (npchar.City == pchar.GenQuest.Badboy.Brothel.City)
			{
				dialog.text = "¡Oh, has regresado! ¿Has arreglado eso de que " + pchar.GenQuest.Badboy.Brothel.Name + "¿para dejar en paz a mis chicas?";
				link.l5 = "Sí. No mostrará su cara aquí nunca más.";
				link.l5.go = "Badboy_complete";
				break;
			}
		}
		// <-- Заносчивый аристократ

		//--> Jason Португалец
		if (CheckAttribute(pchar, "questTemp.HWIC.Detector") || SandBoxMode)
		{
			bool bOk = (pchar.questTemp.HWIC.Detector == "holl_win") || (pchar.questTemp.HWIC.Detector == "eng_win") || (pchar.questTemp.HWIC.Detector == "self_win") || SandBoxMode;
			if (!CheckAttribute(pchar, "questTemp.Portugal") && bOk && !CheckAttribute(npchar, "quest.Portugal") && npchar.location == "Marigo_SecBrRoom" && makeint(environment.time) > 6.0 && makeint(environment.time) < 22.0)
			{
				DelMapQuestMarkCity("marigo");
				DelLandQuestMark(npchar);
				dialog.text = "Capitán, ¿puedo pedirte un favor?";
				link.l5 = "Para usted, señora, ¡lo que quiera! ¡Estoy a su servicio!";
				link.l5.go = "Portugal";
				link.l8 = "Lo siento, pero estoy ocupado en este momento.";
				link.l8.go = "exit";
				npchar.quest.Portugal = "true";
				break;
			}
		}
		if (CheckAttribute(pchar, "questTemp.Portugal") && pchar.questTemp.Portugal == "HostressMoney" && npchar.location == "Marigo_SecBrRoom")
		{
			DelLandQuestMark(npchar);
			dialog.text = "¿Ha hablado con Hugo, mi capitán señor?";
			if (sti(pchar.money) >= 10000)
			{
				link.l1 = "Además, señora, aquí está su dinero. Todo salió de la manera más favorable...";
				link.l1.go = "Portugal_3";
			}
			else
			{
				link.l1 = "Sí, le transmití tu solicitud.";
				link.l1.go = "Portugal_exit";
			}
			break;
		}
		//<--Португалец
		// Addon 2016-1 Jason пиратская линейка
		if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel" && npchar.location == "Tortuga_SecBrRoom")
		{
			dialog.text = "¡Vaya, mira esto! ¡Charlie Prince, un famoso corsario! ¡En carne y hueso!";
			link.l1 = RandSwear() + "Hola, Janette. Estoy aquí en la misión para Marcus Tyrex.";
			link.l1.go = "mtraxx_R";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.Mtraxx.Retribution") && pchar.questTemp.Mtraxx.Retribution == "brothel_repeat" && npchar.location == "Tortuga_SecBrRoom")
		{
			dialog.text = "¿Estás listo para un tratamiento restaurador inolvidable, mi valiente corsario?";
			if (sti(pchar.money) >= 31000)
			{
				link.l1 = "¡Lo estoy! Charlie Prince no malgasta palabras como malgasta dinero, ¡ja-ja!";
				link.l1.go = "mtraxx_R2";
			}
			else
			{
				link.l1 = "Casi... Supongo que he perdido una bolsa en tu establecimiento... ¡Volveré con dinero!";
				link.l1.go = "exit";
			}
			break;
		}

		if (npchar.quest.meeting == "0")
		{
			dialog.text = RandPhraseSimple(TimeGreeting() + ". Bienvenido a mi casa de amor. Mi nombre es " + npchar.name + ", y soy el propietario. " + GetSexPhrase("¿Qué puedo hacer por ti, " + GetAddress_Form(NPChar) + "?", "Sinceramente, estoy un poco sorprendido de verte aquí, " + GetAddress_Form(NPChar) + ", pero te aseguro que prestamos servicios no solo para hombres.") + "", TimeGreeting() + ". Te doy la bienvenida, " + GetSexPhrase("desconocido", "señorita") + ", a mi humilde establecimiento. Permíteme presentarme, soy " + NPChar.Name + ", titular de este asilo para hombres hambrientos de un toque femenino. " + GetSexPhrase("¿Qué puedo hacer por ti?", "Aunque también tenemos una cosa o dos para las damas...") + "");
			npchar.quest.meeting = "1";
		}
		else
		{
			dialog.text = RandPhraseSimple(TimeGreeting() + ". ¿Cómo puedo ayudarte, " + GetAddress_Form(NPChar) + "?", TimeGreeting() + ". ¿Qué puedo hacer por ti, " + GetAddress_Form(NPChar) + "?");
		}
		if (!CheckAttribute(pchar, "questTemp.Sharlie.Gigolo")) // не идёт квест девочки
		{
			if (!CheckAttribute(pchar, "GenQuest.BrothelLock")) // нет запрета от Мэри 280313
			{
				link.l2 = npchar.name + ", quiero pasar un buen rato con una de tus chicas.";
				link.l2.go = "Hostess_1";
			}
		}
		if (!CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // не идёт старт Шарля
		{
			if (sti(pchar.ship.type) != SHIP_NOTUSED && GetCrewQuantity(pchar) > 0) // Rebbebion - а смысл, если нет как корабля, так и команды?
			{
				link.l3 = "Hace un tiempo desde la última vez que mimé a mis hombres. ¿Puedo hacer un pedido grande de chicas para mis chicos?";
				link.l3.go = "ForCrew";
			}
		}
		link.l4 = "Tengo una pregunta.";
		if (CheckCharacterItem(pchar, "CaptainBook") && !CheckAttribute(pchar, "questTemp.different.GiveShipLetters.speakBrothelMadam"))
		{
			if ((pchar.questTemp.different.GiveShipLetters.city == npchar.city) && CheckAttribute(pchar, "questTemp.different.GiveShipLetters"))
			{
				link.l4.go = "ShipLetters_1"; // генератор  "Найденные документы"
			}
			else
			{
				link.l4.go = "quests";
			}
		}
		else
		{
			link.l4.go = "quests"; //(перессылка в файл города)
		}
		//-->> квест поиска кольца мэра
		if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
		{
			link.l5 = "Escucha, " + npchar.name + ", estoy buscando el anillo del gobernador. Él descansó en tu establecimiento y probablemente lo perdió aquí.";
			link.l5.go = "TakeMayorsRing_H1";
			SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
		}
		//<<-- квест поиска кольца мэра

		// belamour ночной приключенец -->
		if (CheckAttribute(pchar, "GenQuest.NightAdventureVar") && pchar.GenQuest.NightAdventureVar == "NightAdventure_NobleWhoreMoney")
		{
			link.l8 = "Mira, me gustaría llevarme a la mejor chica que tengas.";
			link.l8.go = "NA_Girl";
		}
		// <-- приключенец
		link.l9 = "Sin importar, ya me voy.";
		link.l9.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "ShipLetters_1":
		pchar.questTemp.different.GiveShipLetters.speakBrothelMadam = true;
		dialog.text = RandPhraseSimple("¿Qué quieres, guapo?", "Te estoy escuchando, Capitán.");
		link.l1 = "Escucha, " + npchar.name + ", encontré estos papeles en una habitación privada de tu institución ...";
		link.l1.go = "ShipLetters_2";
		break;

	case "ShipLetters_2":
		if (sti(pchar.questTemp.different.GiveShipLetters.variant) == 0)
		{
			dialog.text = "¡Déjame ver! Hmm... algún capitán ha perdido sus documentos, ¿verdad? Creo que deberías preguntarle al maestro del puerto sobre esto.";
			link.l1 = "Quizás, quizás...";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "¡Permíteme echar un vistazo! ¡Oh! Por el nombre, pertenecen a mi estimado cliente y un digno ciudadano de nuestra ciudad. Yo mismo puedo entregarle estos documentos.";
			link.l1 = "Probablemente, no...";
			link.l1.go = "exit";
			link.l2 = "¡Excelente! Siempre feliz de ayudar a una buena persona y a un establecimiento digno.";
			link.l2.go = "ShipLetters_3";
		}
		break;

	case "ShipLetters_3":
		TakeItemFromCharacter(pchar, "CaptainBook");
		pchar.questTemp.different = "free";
		pchar.quest.GiveShipLetters_null.over = "yes"; // снимаем таймер
		AddQuestRecord("GiveShipLetters", "2");
		CloseQuestHeader("GiveShipLetters");
		DeleteAttribute(pchar, "questTemp.different.GiveShipLetters");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "Hostess_1":
		if (!CheckAttribute(npchar, "quest.selected"))
		{
			if (CheckNPCQuestDate(npchar, "quest.date"))
			{
				dialog.text = "" + GetSexPhrase("Siempre estamos felices de atender a un cliente. Ahora dime, guapo, ¿ya has elegido a alguien o no te importa mucho?", "Bueno, mis chicas ciertamente pueden... ayudarte. ¿Ya has escogido a alguien o no te importa mucho?") + "";
				Link.l1 = "" + GetSexPhrase("Je, solo necesito una puta y la necesito ahora mismo. No me importa cuál, todas tus chicas me parecen buenas...", "Cualquiera estará bien si conoce sus deberes, por supuesto...") + "";
				Link.l1.go = "Hostess_NotChoice";
				Link.l2 = "Sí, hay una " + GetSexPhrase("que despertó mi interés...", ", sería la más agradable...") + "";
				Link.l2.go = "Hostess_Choice";
			}
			else
			{
				dialog.text = "No tengo chicas libres para ti hoy, ya tenemos demasiados clientes. ¡Ven mañana y no te arrepentirás!";
				Link.l1 = "Lástima, acababa de empezar a disfrutarlo.";
				Link.l1.go = "exit";
			}
		}
		else
		{
			dialog.text = "Hmm. Ya has pagado por la chica. No me distraigas, por favor.";
			Link.l1 = "Está bien, voy.";
			Link.l1.go = "exit";
		}
		break;

	case "Hostess_NotChoice":
		sld = GetFreeHorseRef(npchar.city);
		location = &locations[FindLocation(npchar.city + "_Brothel")];
		if (sld.id == "none" || GetNpcQuestPastDayParam(location, "Brothel_date") > 98)
		{
			dialog.text = "No tengo chicas libres ahora, tendrás que volver en un par de días.";
			Link.l1 = "Bien, como tú dices.";
			Link.l1.go = "exit";
		}
		else
		{
			// belamour legendary edition Орден Святого Людовика -->
			if (IsEquipTalisman9() && npchar.nation == FRANCE)
			{
				dialog.text = "" + GetSexPhrase("¡Bueno, semental, es excelente!", "Los tengo a todos hábiles, puedes estar segura.") + " Puedo ofrecer a una hermosa chica llamada " + GetFullName(sld) + ", ella está libre ahora.\n¡Oh!, ¿qué es esto que escondes tan modestamente allí? ¿Es esta la máxima condecoración en Francia? Se rumorea que los portadores de esta insignia son legendarios no solo en el campo de batalla... Bueno, sabes a lo que me refiero, mi filibustero... Además, cualquiera consideraría un honor tocar tu 'Orden', así que hoy descansas a cuenta de mi institución. No se aceptan rechazos, guapo.";
				Link.l1 = "¡Por supuesto que estoy de acuerdo!, ¿qué duda puede haber?";
				Link.l1.go = "Hostess_NotChoice_agree";
				npchar.quest.choiceIdx = sld.index;
				break;
			}
			// <-- legendary edition
			dialog.text = "" + GetSexPhrase("¡Bueno, excelente, mi semental!", "Todos ellos son muy hábiles en lo que hacen, no tengas dudas.") + " Puedo ofrecerte a una chica muy bonita, su nombre es " + GetFullName(sld) + ", y ella está libre en este momento. Ese placer te costará " + FindRussianMoneyString(sti(sld.quest.price) + charWhoreCost) + ". ¿De acuerdo?";
			Link.l1 = "No. Supongo que no. Es demasiado caro...";
			Link.l1.go = "exit";
			if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
			{
				Link.l2 = "¡Por supuesto!, ¿cómo podría negarme?";
				Link.l2.go = "Hostess_NotChoice_agree";
				npchar.quest.choiceIdx = sld.index;
			}
			else
			{
				Link.l1 = "Rayos, no tengo tanto dinero conmigo...";
				Link.l1.go = "exit";
			}
		}
		break;

	case "Hostess_NotChoice_agree":
		sld = &characters[sti(npchar.quest.choiceIdx)];
		if (sti(pchar.money) >= (sti(sld.quest.price) + charWhoreCost))
		{
			dialog.text = "Bien, " + GetSexPhrase("guapo", "hermosa") + ". " + sld.name + " te estará esperando en una habitación privada en el segundo piso.";
			Link.l1 = "" + GetSexPhrase("Bien, entonces voy", "Bien, entonces voy") + "...";
			Link.l1.go = "exit";
			// belamour legendary edition деньги только без ордена или адмиральского мундира
			if (IsEquipTalisman9())
			{
				if (npchar.nation != FRANCE)
					AddMoneyToCharacter(pchar, -(sti(sld.quest.price) + charWhoreCost));
			}
			else
			{
				AddMoneyToCharacter(pchar, -(sti(sld.quest.price) + charWhoreCost));
			}
			sld.dialog.currentnode = "Horse_ReadyFack";
			//--> таймер на возврат, чтобы не вечно ждали
			str = npchar.city;
			pchar.quest.(str).win_condition.l1 = "Timer";
			pchar.quest.(str).win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
			pchar.quest.(str).win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.(str).win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
			pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
			pchar.quest.(str).HorseId = sld.id;
			pchar.quest.(str).locator = sld.location.locator;
			//<-- таймер на возврат, чтобы не вечно ждали
			ChangeCharacterAddressGroup(sld, npchar.city + "_Brothel_room", "goto", "goto" + (rand(2) + 1));
			LocatorReloadEnterDisable(npchar.city + "_Brothel", "reload2_back", false); // открываем комнату
			npchar.quest.selected = true;												// флаг взял девку у хозяйки
			SetNPCQuestDate(npchar, "quest.date");										// дату взятия запишем
			for (int n = 0; n < MAX_CHARACTERS; n++)
			{
				makeref(sld, Characters[n]);
				if (sld.location == npchar.city + "_Brothel" && CheckAttribute(sld, "CityType") && sld.CityType == "horse")
				{
					sld.dialog.currentnode = "Horse_4";
				}
			}

			// генератор найденных бумаг

			// belamour legendary edition не давать квесты губернатору и адмиралу
			bool MCGovernon = CheckAttribute(pchar, "questTemp.Patria.GenGovernor");
			bool MCAdmiral = isMainCharacterPatented() && sti(Items[sti(pchar.EquipedPatentId)].TitulCur) > 4;

			if ((rand(4) == 1) && (pchar.questTemp.different == "free") && (!CheckCharacterItem(pchar, "CaptainBook")) && GetNpcQuestPastDayWOInit(npchar, "questShipLetters") > 10 && !MCGovernon && !MCAdmiral)
			{
				pchar.questTemp.different = "GiveShipLetters";
				pchar.questTemp.different.GiveShipLetters = "toBrothel";
				pchar.questTemp.different.GiveShipLetters.Id = GetFullName(npchar);
				pchar.questTemp.different.GiveShipLetters.city = npchar.city;
				pchar.questTemp.different.GiveShipLetters.variant = rand(2);
				p1 = rand(20 - MOD_SKILL_ENEMY_RATE) + 1; // даем хотя бы один день
				s1 = rand(80 - pchar.rank - p1) * 50 + rand(100);
				s2 = s1 * 2;
				s3 = s1 * rand(GetCharacterSPECIAL(pchar, "Luck")) + s1;
				s4 = s2 + s3;
				s5 = s4 * GetCharacterSPECIAL(pchar, "Charisma");
				pchar.questTemp.different.GiveShipLetters.price1 = s1;
				pchar.questTemp.different.GiveShipLetters.price2 = s2;
				pchar.questTemp.different.GiveShipLetters.price3 = s3;
				pchar.questTemp.different.GiveShipLetters.price4 = s4;
				pchar.questTemp.different.GiveShipLetters.price5 = s5;

				sld = ItemsFromID("CaptainBook");
				sld.CityName = XI_ConvertString("Colony" + npchar.city + "Gen");
				// ложим бумаги в итем
				sTemp = "_Brothel_room";
				sTemp1 = "_town";
				sld.shown = true;
				sld.startLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp;
				sld.startLocator = "item" + (rand(4) + 1);
				sld.endLocation = pchar.questTemp.different.GiveShipLetters.city + sTemp1;
				pchar.questTemp.different.GiveShipLetters.item = true; // флаг -  бумаги валяются в итемах
				Log_QuestInfo("Los papeles están en la ubicación " + sld.startLocation + ", localizados en " + sld.startLocator + " p1 : " + p1);

				pchar.quest.CheckShipLetters.win_condition.l1 = "location";
				pchar.quest.CheckShipLetters.win_condition.l1.location = sld.endLocation;
				pchar.quest.CheckShipLetters.function = "CheckShipLetters";

				SetTimerFunction("GiveShipLetters_null", 0, 0, p1); // освобождаем разрешалку на миниквесты
				SaveCurrentNpcQuestDateParam(npchar, "questShipLetters");
			}
			// генератор - "Повод для спешки"
			if ((rand(5) == 2) && !CheckAttribute(pchar, "questTemp.ReasonToFast") && GetNpcQuestPastDayWOInit(npchar, "questReasonToFast") > 20 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock") && !MCGovernon && !MCAdmiral) // Addon-2016 Jason
			{
				iColony = FindColony(npchar.city);
				if (sti(Colonies[iColony].HeroOwn) == false && npchar.city != "Panama" && npchar.city != "Charles")
				{
					pchar.questTemp.ReasonToFast = "Begin";
					pchar.questTemp.ReasonToFast.city = npchar.city;
					sTemp1 = "_town";
					pchar.quest.CheckReasonToFast.win_condition.l1 = "location";
					pchar.quest.CheckReasonToFast.win_condition.l1.location = npchar.city + sTemp1;
					pchar.quest.CheckReasonToFast.function = "ReasonToFast_CheckHorse";
					SaveCurrentNpcQuestDateParam(npchar, "questReasonToFast");
				}
			}
		}
		else
		{
			dialog.text = "Oh, ves, el problema es que " + sld.name + " no es una chica barata, su precio es " + FindRussianMoneyString(sti(sld.quest.price) + charWhoreCost) + ". Y veo que simplemente no puedes permitírtela en este momento. Vuelve cuando seas rico" + GetSexPhrase(", querido", "") + "...";
			Link.l1 = "Esa es mi suerte...";
			Link.l1.go = "exit";
		}
		break;

	case "Hostess_Choice":
		dialog.text = "Siempre me alegra cuando las chicas y los clientes desarrollan sentimientos cálidos el uno por el otro... Dime su nombre.";
		Link.l1.edit = 9;
		Link.l1 = "";
		Link.l1.go = "Hostess_Choice_1";
		break;

	case "Hostess_Choice_1":
		sld = CheckHorsesName(npchar.city, 9);
		if (sld.id == "none")
		{
			dialog.text = "Hmm... debes estar equivocado. No tengo a tal chica en mi establecimiento. Quizás te equivocaste de nombre.";
			Link.l1 = "Hmm... pero acabo de hablar con ella.";
			Link.l1.go = "Hostess_Choice_2";
			Link.l2 = "Quizás. Sería mejor preguntarle su nombre una vez más, solo para estar seguro. Hablaré contigo sobre esto más tarde.";
			Link.l2.go = "exit";
		}
		else
		{
			dialog.text = GetFullName(sld) + ", ¿estás hablando de ella?";
			Link.l1 = "Sí, acerca de ella.";
			Link.l1.go = "Hostess_NotChoice_agree";
			Link.l2 = "No, no es ella.";
			Link.l2.go = "Hostess_Choice_2";
			npchar.quest.choiceIdx = sld.index;
		}
		break;

	case "Hostess_Choice_2":
		dialog.text = "Entonces quizás, deberías decirme su nombre una vez más, y tal vez me daré cuenta, de quién estás hablando.";
		Link.l1.edit = 9;
		Link.l1 = "";
		Link.l1.go = "Hostess_Choice_1";
		Link.l2 = "Quizás. Sería mejor preguntarle su nombre una vez más, solo para estar seguro. Hablaré contigo sobre esto más tarde.";
		Link.l2.go = "exit";
		break;
	//==> команда
	case "ForCrew":
		dialog.text = "Hmm... ¿Quieres ayudar a tus chicos a 'desahogarse'? Verás, este establecimiento mío es uno respetable, y tengo a las mejores chicas de aquí. Pero conozco a varias rameras de puerto, y estarán encantadas de complacer a todos tus marineros. Eso te costará " + FindRussianMoneyString(GetCrewQuantity(pchar) * crewWhoreCost) + ".";
		link.l1 = "Bien, estoy de acuerdo.";
		link.l1.go = "ForCrew_1";
		link.l2 = "Supongo que pueden arreglárselas sin ello...";
		link.l2.go = "exit";
		break;

	case "ForCrew_1":
		if (sti(Pchar.money) >= GetCrewQuantity(pchar) * crewWhoreCost && GetCrewQuantity(pchar) > 0)
		{
			AddMoneyToCharacter(Pchar, -makeint(GetCrewQuantity(pchar) * crewWhoreCost));
			AddCrewMorale(Pchar, 10);
			ChangeCharacterComplexReputation(pchar, "authority", 1);
			LAi_Fade("", "");
			AddTimeToCurrent(5 + rand(1), rand(30));
			DialogExit();
		}
		else
		{
			dialog.text = "No es asunto mío, pero creo que primero deberías ganar suficiente dinero para contratar una tripulación, y solo entonces preocuparte por su espíritu.";
			link.l1 = "Probablemente tengas razón...";
			link.l1.go = "exit";
		}
		break;

	case "Woman_FackYou":
		dialog.text = "Querido, ¿¡pero qué estás haciendo?! Y parecías un capitán decente... Esta vez no 'volarás', guapo. Los guardias te cortarán las alas...";
		link.l1 = "Cállate, vieja bruja.";
		link.l1.go = "exit_setOwner";
		LAi_group_Attack(NPChar, Pchar);
		if (rand(3) != 1)
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		break;

	// поиски кольца губернатора
	case "TakeMayorsRing_H1":
		dialog.text = "No he encontrado ningún anillo.";
		link.l1 = "¿Y tus chicas?";
		link.l1.go = "TakeMayorsRing_H2";
		break;

	case "TakeMayorsRing_H2":
		dialog.text = "No lo han hecho. Si un cliente olvida o pierde algo, mis chicas me lo traen. Pero nadie me ha traído el anillo del gobernador.";
		link.l1 = "Ya veo... ¿Pero podría ser que decidieron quedárselo para ellos mismos?";
		link.l1.go = "TakeMayorsRing_H3";
		break;

	case "TakeMayorsRing_H3":
		dialog.text = "Poco probable. A las chicas se les permite conservar los regalos de los clientes, pero eso es todo.";
		link.l1 = "Ya veo. Bueno, gracias, " + npchar.name + ".";
		link.l1.go = "exit";
		break;

	case "Hostess_inSexRoom":
		dialog.text = "Oh, aquí estás...";
		link.l1 = "¡Aquí estoy, mi señora!";
		link.l1.go = "exit";
		pchar.quest.SexWithHostess_null.over = "yes"; // нулим таймер на не пришёл
		NextDiag.TempNode = "First time";
		if (CheckAttribute(pchar, "questTemp.RomNaTroih_Pogovoril"))
		{
			sld = CharacterFromID(pchar.RomNaTroih_Shluha);
			dialog.text = "" + sld.name + "¡Mi héroe, veo que no has desperdiciado tu tiempo abajo!";
			link.l1 = "Espero que me perdonéis esta debilidad, mi reina.";
			link.l1.go = "RomNaTroih_2";
		}
		AddDialogExitQuestFunction("SexWithHostess_fack");
		AddCharacterExpToSkill(pchar, "Leadership", 100);
		DeleteAttribute(pchar, "questTemp.RomNaTroih");
		if (IsEquipCharacterByArtefact(pchar, "totem_03"))
		{
			AddCharacterHealth(pchar, 10);
			AddCharacterMaxHealth(pchar, 1.0);
		}
		else
			AddCharacterHealth(pchar, 5);
		break;

	// ================================== рядовой состав =======================================
	case "Horse_talk":
		if (LAi_grp_playeralarm > 0)
		{
			dialog.text = NPCharRepPhrase(pchar, LinkRandPhrase("¡Será mejor que abandones el establecimiento!", "¡Todos los guardias en la ciudad te están buscando! Será mejor que te vayas...", "¡¿Has hecho un desastre y ahora apareces aquí?! No, no esta vez..."), LinkRandPhrase("¡Pierde el rastro!", "¡Sucio asesino, lárgate de aquí! ¡Guardias!", "No tengo miedo de ti," + GetSexPhrase("granuja", "rata") + "¡Pronto serás colgado en nuestro fuerte, no llegarás lejos..."));
			link.l1 = NPCharRepPhrase(pchar, RandPhraseSimple("Je, una alarma nunca es un problema para mí...", "Jamás me atraparán."), RandPhraseSimple("Je, qué estúpida moza eres...", "Cierra la boca, puta, o la cerraré con algo más..."));
			link.l1.go = "exit";
			break;
		}
		dialog.text = NPCStringReactionRepeat("Hola, " + GetAddress_Form(NPChar) + "" + GetSexPhrase("", ", jeje..") + ". Tienes que ver a la señora y llenar el pedido.", "¿Tú otra vez? Por favor, habla con la alcaide. Está en su oficina.", "Mira, " + GetAddress_Form(NPChar) + "" + GetSexPhrase(", espero que seas tan terco en otras cosas como lo eres al hablar... Otra vez", "Otra vez") + "Te pido que veas al dueño del establecimiento.", "Oh, " + GetAddress_Form(NPChar) + "" + GetSexPhrase("¡, no eres tú un tozudo!", ", Jeje... Eres un testarudo, ¿verdad?") + "Debes ver a la señora y llenar el pedido.", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Está bien, " + GetSexPhrase("belleza, ", "") + "Lo tengo" + GetSexPhrase("", "") + ".", "Sí, claro...", "" + GetSexPhrase("¡No tengas duda, mi bonita, soy tan terco y fuerte como un toro!", "Sí, sí...") + "", "" + GetSexPhrase("Rayos, debo haberme perdido algo... Lo siento, querido.", "Bien, de acuerdo.") + "", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		Link.l2 = "¿Y dónde está ella?";
		Link.l2.go = "Horse_1";
		Link.l3 = LinkRandPhrase("" + GetSexPhrase("Oh, belleza, apuesto a que podría ahogarme en esos ojos tuyos...", "¡Luces hermosa, nena!") + "", "" + GetSexPhrase("¡Sabes, nunca he conocido a una mujer tan hermosa antes!", "Sabes, nunca había conocido a una chica tan agradable antes!") + "", "" + GetSexPhrase("Cariño, te ves hermosa.", "Maldición, estaba tan cansado de todos esos paletos... ¡Y tú eres tan encantador!") + "");
		if (!CheckAttribute(npchar, "quest.choice"))
		{
			Link.l3.go = "Horse_2";
		}
		else
		{
			Link.l3.go = "HorseChoice_" + npchar.quest.choice;
		}
		//-->> квест поиска кольца мэра
		if (pchar.questTemp.different == "TakeMayorsRing" && pchar.questTemp.different.TakeMayorsRing.city == npchar.city && GetNpcQuestPastDayWOInit(npchar, "TakeMayorsRing") > 7)
		{
			link.l5 = LinkRandPhrase("Escucha, " + GetSexPhrase("belleza", "querido") + ", ¿no has encontrado un anillo de boda aquí, por casualidad? Parece que un hombre lo ha perdido...", "Cariño, ¿has visto un anillo de boda o algo parecido por aquí?", "Escucha, " + GetSexPhrase("mi gatito", "cariño") + ", ¿no has visto un anillo de boda por aquí?");
			link.l5.go = "TakeMayorsRing_S1";
			SaveCurrentNpcQuestDateParam(npchar, "TakeMayorsRing");
		}
		//<<-- квест поиска кольца мэра

		// Addon 2016-1 Jason пиратская линейка
		if (pchar.location == "santodomingo_brothel" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_1" && npchar.id == "HorseGen_" + reload_location_index + "_2")
		{
			link.l6 = "Hola, cariño. Marcus Tyrex me envió, echa un vistazo a este collar de ámbar...";
			link.l6.go = "mtraxx";
		}
		NextDiag.TempNode = "Horse_talk";
		break;

	case "Horse_1":
		dialog.text = "Ella está en su oficina. Puedes llegar a ella desde aquí a través de la puerta opuesta a la salida a la calle, o desde la calle del otro lado de la casa. Su nombre es " + characters[GetCharacterIndex(npchar.city + "_Hostess")].name + ".";
		Link.l1 = "Ya veo, " + GetSexPhrase("cariño", "querido") + ", gracias.";
		Link.l1.go = "exit";
		break;

	case "Horse_2":
		if (rand(1))
		{
			dialog.text = LinkRandPhrase("¡Vaya, es tan agradable escuchar tales cosas! Oye, estoy libre en este momento, así que si me eliges, no te arrepentirás...", "¿De verdad lo crees? Sabes, es tan lindo... Escucha, estoy libre en este momento, así que puedes elegirme." + GetSexPhrase("Te prometo un mar de amor y un océano de caricias...", "") + "", "" + GetSexPhrase("¿Piensas eso? Oh, estoy realmente halagado. Sabes, raramente escucho tales cumplidos...", "Oh, chica... si tan solo supieras cuán harto estoy de los paletos...") + "Oye, escucha, estoy libre en este momento, así que puedes elegirme para hacerte feliz. No te decepcionaré, lo prometo...");
			if (CheckAttribute(pchar, "questTemp.RomNaTroih") && !CheckAttribute(pchar, "questTemp.RomNaTroih_Pogovoril"))
			{
				link.l1 = "Mi querida, ¡eso es exactamente lo que iba a hacer! Qué fortuna que tu anfitriona ya haya asegurado una reunión privada conmigo arriba. ¿Te gustaría unirte?";
				Link.l1.go = "RomNaTroih_1";
				pchar.questTemp.RomNaTroih_Pogovoril = true;
				break;
			}
			link.l1 = "¡Bueno, entonces te elijo a ti!";
			Link.l1.go = "Horse_3";
			Link.l2 = "" + GetSexPhrase("No, eso fue solo un cumplido para una dama agradable", "Eso fue solo un cumplido") + ".";
			Link.l2.go = "exit";
			npchar.quest.choice = 0; // был базар, но ГГ потом отказался
		}
		else
		{
			dialog.text = LinkRandPhrase("" + GetSexPhrase("¿Sabes qué digo, cariño? No necesito esta charla barata. ¡Haz negocios o lárgate!", "¡Eso es todo lo que necesitaba! ¡Cumplidos de las mujeres!") + "", "" + GetSexPhrase("¿Eres uno de esos que piensan que las mujeres aman con sus oídos? Bueno, querido, eso simplemente no es cierto. Si me quieres, entonces paga a la madame y sálvame de tus palabras vacías.", "Chica, no malgastes tu tiempo en charlas vacías. Si hablas en serio, entonces paga...") + "", "" + GetSexPhrase("¡Oh, otro amante de la sensualidad... Solo pagas y soy tuya. Es todo así de simple, sin todas estas tonterías de caballerosidad!", "¿Qué te pasa, cariño? Si quieres darte un capricho de placeres, simplemente paga y deja todas esas tonterías!") + "");
			link.l1 = "¡Oh, qué agarre!";
			Link.l1.go = "exit";
			npchar.quest.choice = 2; // ГГ послали
		}
		break;

	case "Horse_3":
		dialog.text = characters[GetCharacterIndex(npchar.city + "_Hostess")].name + " completa todas las formalidades en su gabinete. Ve a verla" + GetSexPhrase(", mi héroe,", "") + " y di mi nombre, " + npchar.name + ". Te estaré esperando...";
		Link.l1 = "Veo, querida, volveré pronto...";
		Link.l1.go = "exit";
		npchar.quest.choice = 1; // она согласная
		SetNPCQuestDate(npchar, "quest.choice");
		break;

	case "Horse_4":
		dialog.text = NPCStringReactionRepeat("Ya has pagado.", "Te dije 'sube las escaleras'.", "Arriba, joven.", "Algunas personas piensan tan despacio...", "block", 1, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Sí, lo sé.", "Recuerdo.", "Oh, no te repitas, recuerdo.", "¿Hmm, qué quieres decir?", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		NextDiag.TempNode = "Horse_4";
		break;

	//===>> реакция на попытки пофлиртовыть, если флирт уже был
	case "HorseChoice_0":
		if (!CheckAttribute(npchar, "quest.sexHappend"))
		{
			dialog.text = NPCStringReactionRepeat("Solo que no te entiendo del todo." + GetSexPhrase("Primero haces cumplidos, y luego te retractas de tus palabras. Qué tipo tan extraño...", "") + "", "¿Otra vez halagos?", "La guardiana está en su oficina. ¿Lo entiendes?", "No se supone que debamos insultar a nuestros clientes, pero realmente lo estás pidiendo" + GetSexPhrase("", "") + "...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Solo ocurrió de la manera en que lo hizo...", "Está bien, lo haré.", "Sí, lo tengo.", "Pido perdón, mi amor.", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "Gracias por el cumplido. Si quieres llevarte a mí, solo ve y consulta a la señora. Negocios como de costumbre.";
			Link.l1 = "Lo veo.";
			Link.l1.go = "exit";
		}
		break;

	case "HorseChoice_1":
		if (!CheckAttribute(npchar, "quest.sexHappend"))
		{
			if (!CheckNPCQuestDate(npchar, "quest.choice"))
			{
				dialog.text = NPCStringReactionRepeat("" + GetSexPhrase("Querido, ya hemos hablado de todo. ", "") + "No me hagas esperar demasiado tiempo...", "" + GetSexPhrase("Hmm... Escucha, querida, yo", "Yo") + " encuentro tus palabras muy bonitas y todo, pero ¿podrías ir al grano...?", "Quizás, ¿discutirás esto con la señora, no es así?", "Um... Ni siquiera sé qué decir...", "block", 1, npchar, Dialog.CurrentNode);
				link.l1 = HeroStringReactionRepeat("¡Nunca haría eso, espérame!", "¡Ciertamente!", "¡Por supuesto, como tú digas!", "Ya estoy corriendo para ver a tu señora...", npchar, Dialog.CurrentNode);
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Te estaba esperando, pero no viniste a buscarme... No puedo decir que me gustó eso...";
				Link.l1 = "Ya ves, simplemente sucedió de la forma en que lo hizo...";
				Link.l1.go = "exit";
				npchar.quest.choice = 0; // был базар, но ГГ потом отказался
			}
		}
		else
		{
			dialog.text = "Oh, eres tú de nuevo, mi " + GetSexPhrase("glorioso corsario", "bella moza") + "¡Si me quieres otra vez, ven a ver a la señora, no te decepcionarás..." + GetSexPhrase("Por cierto, te reconocí, querido, pero nos dicen que debemos hablar con todos los clientes por igual, no debería haber uno favorito, lo siento por eso...", "") + "";
			Link.l1 = "No te preocupes, cariño. Espérame solo un poquito, " + GetSexPhrase("belleza", "belleza") + ", y pronto nos encontraremos en privado de nuevo.";
			Link.l1.go = "exit";
			Link.l2 = "Es muy bonito que me recuerdes, pero no puedo pasar esta noche contigo, lo siento.";
			Link.l2.go = "HorseChoice_1_Add";
		}
		break;

	case "HorseChoice_2":
		if (!CheckAttribute(npchar, "quest.sexHappend"))
		{
			dialog.text = NPCStringReactionRepeat("Entonces," + GetSexPhrase("querido amigo,", "") + "sería mejor que te ocuparas en asuntos. Será más útil que no hacer nada.", "" + GetSexPhrase("¿Hmm, por qué estás tú ", "¿Por qué estás") + "¿diciendo las mismas cosas una y otra vez?", "¡Oye, ¿no es suficiente?!", "Hm, qué sorpresa, nada nuevo" + GetSexPhrase(", una vez más todos esos estúpidos intentos de encanto! Si quieres acostarte conmigo, ve a ver a la madama, cerebro de plumas!", "...") + "", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Sí, he oído" + GetSexPhrase("", "") + " tú...", "Vaya, resulta que es así...", "Hmm, tal vez eso sea suficiente, o tal vez no ...", "Cuida tu lengua" + GetSexPhrase(", cabra", "") + "...", npchar, Dialog.CurrentNode);
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "¡Ohh, eres tú de nuevo! " + GetSexPhrase("Y una vez más todos esos estúpidos cumplidos. Nunca cambia nada en este mundo... Si ", "Solo para recordar: si ") + "quieres" + GetSexPhrase("pasarlo bien", "pasarlo bien") + " conmigo, paga al dueño del establecimiento. Tus palabras me importan un bledo.";
			Link.l1 = "Eso no es una gran sorpresa...";
			Link.l1.go = "exit";
		}
		break;

	case "HorseChoice_1_Add":
		dialog.text = "No puedo decir que me hizo feliz... Una lástima.";
		Link.l1 = "Lo siento...";
		Link.l1.go = "exit";
		npchar.quest.choice = 0;
		break;

	//===>> секс
	case "Horse_ReadyFack":
		// Addon 2016-1 Jason пиратская линейка
		if (pchar.location == "SantoDomingo_Brothel_room" && CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "jewelry_2" && npchar.name == "Gabriela")
		{
			dialog.text = "¡Ah, finalmente has llegado! ¡Genial! Podemos hablar libremente, nadie está escuchando...";
			Link.l1 = "Entonces, ¿fue el español quien te dio el ámbar azul?";
			Link.l1.go = "mtraxx_2";
			DelLandQuestMark(npchar);
			DelMapQuestMarkCity("SantoDomingo");
			break;
		}
		if (!CheckAttribute(npchar, "quest.choice"))
			npchar.quest.choice = 0;
		switch (npchar.quest.choice)
		{
		case "0":
			dialog.text = RandPhraseSimple("Estoy muy feliz de verte. " + GetSexPhrase("Entonces, ¿qué vamos a hacer a continuación?", "¿Qué tal si nos divertimos?") + "", "No seas tímido" + GetSexPhrase(", hazte como en casa al menos por dos horas.", ". Podré entretenerte, no tengas duda.") + "");
			Link.l1 = RandPhraseSimple("No creo que vaya a ser aburrido...", "" + GetSexPhrase("¡Pasemos un buen rato, cariño!", "¡No perdamos tiempo!") + "");
			break;
		case "1":
			dialog.text = "Oh, eres tú de nuevo, mi " + GetSexPhrase("¡glorioso corsario! Te prometí algo y estoy listo para cumplir mi palabra", "¡hermosa doncella! Nunca olvidarás las próximas dos horas") + "...";
			Link.l1 = "Ahora eso suena tentador...";
			break;
		case "2":
			dialog.text = "¡Ohh, aquí estás, finalmente. ¡No perdamos tiempo!";
			Link.l1 = "" + GetSexPhrase("No lo hagamos, cobarde...", "Ahora muéstrame lo que puedes hacer...") + "";
			break;
		}
		if (pchar.sex == "woman")
		{
			Link.l1.go = "exit";
			NextDiag.TempNode = "Horse_AfterSex";
			AddDialogExitQuest("PlaySex_1");
			// кач от борделя
			if (CheckNPCQuestDate(pchar, "BrothelSex"))
			{
				if (IsEquipCharacterByArtefact(pchar, "totem_03"))
					AddCharacterHealth(pchar, 10);
				else
					AddCharacterHealth(pchar, 5);
				SetNPCQuestDate(pchar, "BrothelSex");
			}
			// изменение статусов
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "FencingS", -15);
			AddCharacterExpToSkill(pchar, "Pistol", -15);
		}
		else
		{
			pchar.horsekiss = npchar.id;
			Link.l1.go = "Horse_Kiss";
		}
		//--> кол-во посещений
		if (!CheckAttribute(npchar, "quest.sexHappend"))
			npchar.quest.sexHappend = 1;
		else
			npchar.quest.sexHappend = sti(npchar.quest.sexHappend) + 1;
		pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
		Achievment_SetStat(23, 1);
		//<-- кол-во посещений
		str = npchar.city;
		pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
		pchar.quest.(str).win_condition.l1.location = pchar.location;
		pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
		pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; // счетчик
		break;

	case "Horse_Kiss":
		DialogExit();

		StartQuestMovie(true, false, true);
		LAi_SetActorType(pchar);
		LAi_Fade("Horse_Kiss", "");
		break;

	case "Horse_AfterSex":
		if (CheckAttribute(pchar, "questTemp.ReasonToFast") && pchar.questTemp.ReasonToFast == "Begin")
		{
			dialog.text = "Capitán, ¿por qué estás tan silencioso?";
			link.l1 = LinkRandPhrase("Bueno, ese soy yo.", "Hablaremos la próxima vez.", RandPhraseSimple("No te pago por hablar.", "Pero tú, " + GetSexPhrase("belleza", "cielo") + ", no estuvieron tan callados todo ese tiempo."));
			link.l1.go = "exit";
			link.l2 = "" + GetSexPhrase("¡Estuviste genial, casi pierdo la cabeza! Es una ocasión muy rara cuando una mujer es tan hermosa y apasionada", "Ohh, ciertamente sabes cómo complacer a una mujer... Estoy tan emocionada.") + ".";
			link.l2.go = "Horse_ReasonToFast_1";
		}
		else
		{
			switch (npchar.quest.choice)
			{
			case "0":
				dialog.text = LinkRandPhrase("¿Te gustó?", "Entonces, ¿qué puedes decir? ¿Estaba todo bien?", "Entonces," + GetSexPhrase(" corsario, es, todo", "todo") + "¿bien?");
				Link.l1 = RandPhraseSimple("" + GetSexPhrase("Por supuesto, todo está bien", "Ciertamente conoces tus deberes") + ".", "" + GetSexPhrase("Todo está bien, cariño", "Sabes, estaba bastante complacido") + ".");
				Link.l1.go = "exit";
				break;
			case "1":
				dialog.text = LinkRandPhrase("Entonces, ¿cumplí mi promesa?", "Entonces," + GetSexPhrase("¿me gustaste?", ", ¿te gustó?") + "?", "Espero, " + GetSexPhrase("estabas contento, porque yo estoy mu-u-uy contento", "estabas contento, porque hice lo mejor que pude") + "...");
				Link.l1 = RandPhraseSimple("Sí, me gustó mucho.", "" + GetSexPhrase("¡Lo pasamos genial, estabas hermoso!", "¡Todo fue simplemente magnífico!") + "");
				Link.l1.go = "exit";
				break;

			case "2":
				dialog.text = RandPhraseSimple("Bueno, eso es todo, tienes que irte.", "Tu tiempo ha terminado," + GetSexPhrase("Capitán,", "") + ".");
				Link.l1 = RandPhraseSimple("Sí, hasta la vista...", "Adiós y gracias...");
				Link.l1.go = "exit";
				break;
			}
			NextDiag.TempNode = "Horse_AfterSex_2";
		}
		break;

	case "Horse_AfterSex_2":
		if (CheckAttribute(pchar, "GenQuest.EncGirl") && pchar.GenQuest.EncGirl == "Bag_BrothelRoom" && !CheckCharacterItem(pchar, "leather_bag"))
		{
			dialog.text = "Entonces, ¿cómo te gustó aquí?";
			link.l1 = "Dime belleza, ¿no has visto una maleta por aquí cerca?";
			link.l1.go = "EncGirl_GetBag";
		}
		else
		{
			dialog.text = LinkRandPhrase("Pasa de nuevo a veces...", "Adiós. Te estaremos esperando en cualquier momento...", "Estaremos encantados de verte aquí de nuevo...");
			Link.l1 = "Está bien...";
			Link.l1.go = "exit";
			NextDiag.TempNode = "Horse_AfterSex_2";
		}
		break;

	case "EncGirl_GetBag":
		dialog.text = "¿Fue ese cofre marrón con un asa?";
		link.l1 = "Sí, algo así...";
		link.l1.go = "EncGirl_GetBag1";
		break;

	case "EncGirl_GetBag1":
		dialog.text = "Porque el dueño de ese cofre no ha aparecido, la señora lo ha llevado a su tocador.";
		link.l1 = "Gracias, cariño. Adiós.";
		link.l1.go = "exit";
		pchar.GenQuest.EncGirl = "Bag_BrothelHostess";
		NextDiag.TempNode = "Horse_AfterSex_2";
		break;

	// --> генератор - "Una razón para darse prisa"
	case "Horse_ReasonToFast_1":
		dialog.text = "Entonces pasa en cualquier momento, siempre estaré encantado de verte. Eres tan " + GetSexPhrase("amable, no como esos otros", "suave, no como esos paletos") + " no hola, no adiós, y a menudo incluso intentan lastimar...";
		link.l1 = "¿Qué quieres decir con eso?";
		link.l1.go = "Horse_ReasonToFast_2";
		break;

	case "Horse_ReasonToFast_2":
		pchar.questTemp.ReasonToFast.speakHorse = true;
		dialog.text = "Había un sargento maestro justo antes que tú. Normalmente no nos visita, pero esta vez algún diablo lo trajo aquí. Además, me eligió a mí... Estaba gruñendo mientras estaba sobre mí durante unos minutos, luego me llamó de baja habilidad y se precipitó a alguna cala. Se marchó tan rápidamente que casi deja sus pantalones allí, ja-ja-ja...";
		link.l1 = "¿No sabes, " + GetSexPhrase("belleza", "querida") + ", ¿quién son realmente los hombres? Le había dicho a su esposa que iría al burdel para una 'inspección', luego le dijo a su amante que tenía prisa por llegar a su esposa, pero lo único que siempre quiso es ir a patrullar esa cala. " + GetSexPhrase("¡Ja-ja-ah!..", "¡Ja-ja-ja!") + "";
		link.l1.go = "Horse_ReasonToFast_3";
		break;

	case "Horse_ReasonToFast_3":
		NextDiag.TempNode = "Horse_AfterSex_2";
		ReOpenQuestHeader("ReasonToFast");
		AddQuestRecord("ReasonToFast", "1");
		pchar.questTemp.ReasonToFast = "SpeakHorse";
		pchar.questTemp.ReasonToFast.GuardNation = npchar.nation;
		pchar.questTemp.ReasonToFast.cantSpeakOther = true;
		ReasonToFast_InitVariables();
		string TargetLocation = SelectQuestShoreLocation();
		if (TargetLocation != "")
		{
			Locations[FindLocation(TargetLocation)].DisableEncounters = true;
			LAi_LocationDisableOfficersGen(TargetLocation, true);
			pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1 = "location";
			pchar.quest.ReasonToFast_MeetPatrol.win_condition.l1.location = TargetLocation;
			pchar.quest.ReasonToFast_MeetPatrol.function = "ReasonToFast_MeetPatrolShore";
			pchar.questTemp.ReasonToFast.PatrolLocation = TargetLocation;
		}
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
		// <-- генератор "Una razón para darse prisa"

	case "exit_setOwner":
		LAi_SetOwnerTypeNoGroup(npchar);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	// поиски кольца мэра
	case "TakeMayorsRing_S1":
		if (CheckAttribute(pchar, "questTemp.different.TakeMayorsRing.item")) // если валяется в итемах
		{
			dialog.text = LinkRandPhrase("No, cariño, lo siento, pero no. Me gustaría mucho ayudarte, pero no puedo.", "No, " + GetSexPhrase("guapo", "Joven señorita") + ", no he visto ningún anillo...", "Lo siento, pero no. No he visto ningún anillo.");
			link.l1 = "Lástima... Bueno, gracias de todos modos.";
			link.l1.go = "exit";
		}
		else
		{
			if (npchar.id == "HorseGen_" + reload_location_index + "_1")
			{
				dialog.text = "¿Te refieres al anillo del gobernador?";
				link.l1 = "¡Exactamente, cariño!";
				link.l1.go = "TakeMayorsRing_S2";
			}
			else
			{
				dialog.text = LinkRandPhrase("No, cariño, lo siento, pero no. Me encantaría ayudarte, pero no puedo.", "No, " + GetSexPhrase("guapo", "señorita") + ", no he visto ningún anillo...", "Lo siento, pero no. No he visto ningún anillo.");
				link.l1 = "Lástima... Bueno, gracias de todos modos.";
				link.l1.go = "exit";
			}
		}
		break;

	case "TakeMayorsRing_S2":
		dialog.text = "Lo siento, pero el anillo me fue dado como un regalo, así que no estoy obligado a devolverlo.";
		link.l1 = "¿Un regalo?! ¿Y quién te lo dio?";
		link.l1.go = "TakeMayorsRing_S3";
		break;

	case "TakeMayorsRing_S3":
		dialog.text = "¡El propio gobernador, por supuesto!";
		link.l1 = "Pero él estaba... mareado, por decir lo menos. No puede recordar nada.";
		link.l1.go = "TakeMayorsRing_S4";
		break;

	case "TakeMayorsRing_S4":
		dialog.text = "¿Y qué tengo que ver yo con eso? Si estaba borracho, es su problema, ¡no el mío!";
		link.l1 = "¿Realmente necesitas pelear con él? Es un anillo de matrimonio, y lo sabes... Solo devuélvelo, una cosa tan pequeña no vale la pena ningún problema.";
		link.l1.go = "TakeMayorsRing_S5";
		break;

	case "TakeMayorsRing_S5":
		if (rand(1) && sti(pchar.money) > 5000)
		{
			dialog.text = "Bueno, devolveré el anillo, pero me pagarás cinco mil pesos.";
			link.l1 = "Bien, toma tu dinero y dame el anillo.";
			link.l1.go = "TakeMayorsRing_S6";
		}
		else
		{
			dialog.text = "¡Oh, bueno. Déjale tenerlo!";
			link.l1 = "¡Eso es seguro, cariño!";
			link.l1.go = "exit";
			GiveItem2Character(pchar, "MayorsRing");
			pchar.questTemp.different.TakeMayorsRing = "HorseTakenRing";
			AddQuestRecord("SeekMayorsRing", "3");
			AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
			AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
		}
		break;

	case "TakeMayorsRing_S6":
		dialog.text = "Aquí tienes...";
		link.l1 = "Bien, entonces. Gracias por la ayuda, querido.";
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, -5000);
		GiveItem2Character(pchar, "MayorsRing");
		pchar.questTemp.different.TakeMayorsRing = "HorseTakenRingMoney";
		AddQuestRecord("SeekMayorsRing", "2");
		AddQuestUserData("SeekMayorsRing", "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData("SeekMayorsRing", "sName", GetFullName(npchar));
		break;

	// Jason --> Заносчивый аристократ
	case "Badboy":
		pchar.GenQuest.Badboy.Brothel.City = npchar.city; // город квестодателя
		// log_info(pchar.GenQuest.Badboy.Brothel.City); // patch-6
		pchar.GenQuest.Badboy.Brothel.nation = npchar.nation;
		pchar.GenQuest.Badboy.Brothel.Name = GenerateRandomName_Generator(sti(npchar.nation), "man");
		dialog.text = "Verás, tenemos un cliente desagradable, " + pchar.GenQuest.Badboy.Brothel.Name + ". Y realmente nos molesta cada vez que viene! Primero se emborracha en la taberna, luego viene aquí, elige a una chica y hace un escándalo violento\nY lo peor de todo es que es de noble linaje! Es un pariente lejano de nuestro gobernador, así que estamos obligados a soportar todas sus travesuras. ¿Quizás podrías hacer que ese joven descarado... bueno... se calmara un poco... para que dejara de visitar mi establecimiento?";
		link.l1 = "¿Pariente del gobernador, dices? Hmm... Preferiría no entrar en confrontación con las autoridades. Lo siento mucho.";
		link.l1.go = "exit";
		link.l2 = "Creo que puedo arreglar eso. Dime, ¿dónde puedo encontrar a ese granuja?";
		link.l2.go = "Badboy_1";
		break;

	case "Badboy_1":
		dialog.text = "Por lo general, a esta hora ya está en la taberna. Se emborracha allí y luego viene a visitar.";
		link.l1 = "Ya veo. Bueno, probablemente lo encontraré allí.";
		link.l1.go = "exit";
		// создаем дебошира
		int iRank, iType, b;
		string sBlade, sPistol;
		if (sti(pchar.rank) < 6)
			iType = 0;
		if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 16)
			iType = 1;
		if (sti(pchar.rank) >= 16)
			iType = 2;
		switch (iType)
		{
		case 0:
			iRank = 6;
			sBlade = "blade_12";
			sPistol = "pistol1";
			b = 25;
			break;
		case 1:
			iRank = sti(pchar.rank) + 10;
			sBlade = "blade_09";
			sPistol = "pistol1";
			b = 65;
			break;
		case 2:
			iRank = sti(pchar.rank) + 5;
			sBlade = "blade_14";
			sPistol = "pistol1";
			b = 40;
			break;
		}
		sld = GetCharacter(NPC_GenerateCharacter("Badboy", "citiz_" + (7 + rand(1)), "man", "man", iRank, HOLLAND, -1, true, "citizen"));
		FantomMakeCoolFighter(sld, iRank, b, b, sBlade, sPistol, "bullet", makeint(iRank * 5));
		sld.name = pchar.GenQuest.Badboy.Brothel.Name;
		sld.lastname = "";
		sld.dialog.FileName = "Quest\Other_quests_NPC.c";
		sld.dialog.currentnode = "Badboy";
		sld.greeting = "noble_male"; // patch-6
		LAi_SetLoginTime(sld, 15, 22);
		LAi_SetSitType(sld);
		FreeSitLocator(pchar.GenQuest.Badboy.Brothel.City + "_tavern", "sit1");
		ChangeCharacterAddressGroup(sld, pchar.GenQuest.Badboy.Brothel.City + "_tavern", "sit", "sit1");
		pchar.GenQuest.Badboy.Brothel.Type = iType; // запомним тип
		pchar.GenQuest.Badboy.Brothel = "true";
		break;

	case "Badboy_complete":
		dialog.text = "Ah, eres un verdadero hombre, ¿no? Siempre supe que podía contar contigo..";
		link.l1 = "Siempre estoy feliz de ayudar a una dama tan agradable y a sus... pupilos.";
		link.l1.go = "Badboy_complete_1";
		break;

	case "Badboy_complete_1":
		dialog.text = "No solo eres valiente, sino también muy galante. Me gustaría agradecerte de una manera especial, de una manera que solo una mujer puede agradecer a un hombre. Nunca olvidarás esto, te lo prometo. Sube, valiente marinero...";
		link.l1 = "...";
		link.l1.go = "Badboy_complete_2";
		break;

	case "Badboy_complete_2":
		pchar.questTemp.different.HostessSex.city = pchar.GenQuest.Badboy.Brothel.City;
		AddDialogExitQuestFunction("SexWithHostess_goToRoom");
		SetTimerFunction("SexWithHostess_null", 0, 0, 1);
		DialogExit();
		if (sti(pchar.GenQuest.Badboy.Brothel.Type) != 2)
		{
			DeleteAttribute(pchar, "GenQuest.Badboy");
		}
		else
		{
			pchar.quest.Badboy_Brothel.win_condition.l1 = "location";
			pchar.quest.Badboy_Brothel.win_condition.l1.location = pchar.GenQuest.Badboy.Brothel.City + "_town";
			pchar.quest.Badboy_Brothel.function = "Badboy_friends";
			DeleteAttribute(pchar, "GenQuest.Badboy.Continue"); // patch-6
		}
		SaveCurrentQuestDateParam("questTemp.Badboy");
		if (!CheckAttribute(pchar, "questTemp.RomNaTroih"))
		{
			pchar.questTemp.RomNaTroih = true;
		}
		break;
	// <-- Заносчивый аристократ

	// Португалец
	case "Portugal":
		dialog.text = "Hay un hombre y me debe algo de dinero... No sé cómo decirlo...";
		link.l1 = "¡Sin palabras! Lo encontraré y lo sacudiré hasta el último peso solo por una mirada de tus ojos insondables. ¡Solo dime su nombre!";
		link.l1.go = "Portugal_1";
		break;

	case "Portugal_1":
		dialog.text = "¡No, no, no me has entendido correctamente, Capitán! Este hombre... no le hagas nada malo. Solo recuérdale de sus deudas. Su nombre es Hugo Avendell, y supongo que lo encontrarás allí, donde se vende el licor muy barato. ¡Por el amor de Dios, no le apliques fuerza!\nSolo di... recuérdale que prometió pagar. No quiero contactar a la guardia, pero tengo amigos oficiales, así que dile que estoy esperando, y con todo el respeto que le tengo, me veré obligado a tomar medidas no más tarde de mañana. Solo recuérdale su promesa.";
		link.l1 = "Vuestra palabra es mi ley, señora. Con gusto cumpliré vuestra petición.";
		link.l1.go = "Portugal_2";
		break;

	case "Portugal_2":
		DialogExit();
		// создаем Хьюго
		sld = GetCharacter(NPC_GenerateCharacter("Avendel", "Hugh", "man", "man", 10, HOLLAND, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 20, 50, 50, "blade_04", "pistol1", "bullet", 50);
		sld.name = "Hugo";
		sld.lastname = "Avendell";
		sld.dialog.FileName = "Quest\Portugal_dialog.c";
		sld.dialog.currentnode = "Avendel_tavern";
		sld.greeting = "avendel_1";
		sld.rank = 12;
		LAi_SetHP(sld, 80, 80);
		SetSelfSkill(sld, 10, 12, 10, 10, 70);
		SetShipSkill(sld, 50, 75, 15, 15, 25, 55, 10, 15, 30);
		SetSPECIAL(sld, 3, 8, 3, 10, 10, 3, 6);
		SetCharacterPerk(sld, "BasicCommerce");
		SetCharacterPerk(sld, "AdvancedCommerce");
		SetCharacterPerk(sld, "BasicBattleState");
		SetCharacterPerk(sld, "AdvancedBattleState");
		SetCharacterPerk(sld, "BasicDefense");
		SetCharacterPerk(sld, "Gunman");
		GiveItem2Character(sld, "blade_12");
		sld.equip.blade = "blade_12";
		GiveItem2Character(sld, "pistol1");
		EquipCharacterbyItem(sld, "pistol1");
		TakeNItems(sld, "bullet", 10);
		AddItems(sld, "gunpowder", 10);
		LAi_SetCharacterUseBullet(sld, GUN_ITEM_TYPE, "bullet");
		LAi_group_MoveCharacter(sld, "HOLLAND_CITIZENS");
		LAi_SetImmortal(sld, true);
		LAi_SetSitType(sld);
		FreeSitLocator("Marigo_tavern", "sit_front1");
		ChangeCharacterAddressGroup(sld, "Marigo_tavern", "sit", "sit_front1");
		AddLandQuestMark(sld, "questmarkmain");
		SetFunctionTimerCondition("Portugal_BeginOver", 0, 0, 2, false);
		pchar.questTemp.Portugal = "begin";
		break;

	case "Portugal_exit":
		dialog.text = "Gracias, capitán. Espero sinceramente que él muestre la debida prudencia.";
		link.l1 = "Estoy seguro de eso, señora. Ahora permítame tomar mi licencia.";
		link.l1.go = "exit";
		sld = characterFromId("Avendel");
		sld.lifeday = 0;
		pchar.questTemp.Portugal = "end";
		break;

	case "Portugal_3":
		AddMoneyToCharacter(pchar, -10000);
		dialog.text = "¡Oh no! No me digas que le has hecho algo terrible... ¡No tenía dinero, y lo sabía! Simplemente crecimos en el mismo pueblo pequeño, ¡nunca me iría a los guardias! Solo quería asustarlo un poco... para sacudirlo antes de que se ahogara en la botella.";
		link.l1 = "Hmm... Sin embargo, aquí está tu dinero. Y no te preocupes por Hugo, está bien... Al menos lo estará si se despeja.";
		link.l1.go = "Portugal_4";
		break;

	case "Portugal_4":
		dialog.text = "¡Oh, Capitán, no lo entiendes! Él era uno de... bueno, se les llama cazadores de recompensas, mercenarios, persiguen a piratas y ladrones y los eliminan. Pero, no era el más afortunado, por decir lo menos.\nNo hace mucho, finalmente despilfarró y perdió a su tripulación y barco, desde entonces ha estado flotando en el fondo de su jarra, día tras día. Yo, por viejos recuerdos, le permito venir aquí a veces. Él está tan... tan lamentable ahora. Era el hombre más guapo de nuestro pueblo en la costa de La Mancha, y míralo ahora.\nSé que él te prometió algo, ¡y pagaste de tu bolsillo! Te devolveré este dinero, solo no le hagas nada malo, te lo suplico, capitán!";
		link.l1 = "Bien, está bien, señora, lo entiendo. Mantén el dinero, es tuyo. En cuanto a tu amigo, prometo que no le haré daño. Y ahora permíteme retirarme, tengo algunos asuntos que atender. Además, me alegró poder ayudar a una dama tan hermosa.";
		link.l1.go = "Portugal_5";
		break;

	case "Portugal_5":
		DialogExit();
		sld = characterFromId("Avendel");
		sld.dialog.currentnode = "Avendel_tavern_7";
		AddLandQuestMark(sld, "questmarkmain");
		pchar.questTemp.Portugal = "AvendelTavern";
		break;

	// Addon 2016-1 Jason пиратская линейка
	case "mtraxx":
		dialog.text = "Shh, mantén la voz baja... Ve a pedirle a la Señora Lolita que tenga una cita conmigo. Luego sube las escaleras, donde podremos hablar libremente. Y ni una palabra hasta entonces... ¡Eh, marinero, ve a pagarle a la Señora antes de tocarme! (risitas)";
		link.l1 = "En mi camino, cariño...";
		link.l1.go = "mtraxx_1";
		break;

	case "mtraxx_1":
		DialogExit();
		chrDisableReloadToLocation = false;
		pchar.questTemp.Mtraxx = "jewelry_2";
		break;

	case "mtraxx_2":
		pchar.quest.Mtraxx_JewelrySDMOver.over = "yes"; // снять таймер
		dialog.text = "Nah, no yo. Te contaré toda la historia, solo no me interrumpas.";
		link.l1 = "¡Estoy todo oídos!";
		link.l1.go = "mtraxx_3";
		break;

	case "mtraxx_3":
		dialog.text = "Bueno entonces. Hace una semana, un barco militar llegó a Santo Domingo. Estaba dañado, ya sea por una tormenta o una pelea, por lo que las reparaciones comenzaron de inmediato, y la tripulación se trasladó al fuerte. Su capitán, sin embargo, pasó todo su tiempo libre aquí. Durante dos días seguidos estuvo bebiendo y relajándose acompañado de una de nuestras chicas. Fue ella quien recibió la piedra preciosa, y no solo una. No paraba de presumir de ello, Lolita nos permite quedarnos con los regalos de los clientes\nLa tonta niña ni siquiera sabía el verdadero valor del regalo, mientras que yo lo evalué de inmediato. Cuando me contó cómo el capitán borracho se jactó de una montaña llena de ámbares, envié rápidamente una carta a Tyrex...";
		link.l1 = "";
		link.l1.go = "mtraxx_4";
		break;

	case "mtraxx_4":
		dialog.text = "Para la próxima llegada del capitán, organicé todo para que su chica favorita estuviera ocupada con otro cliente, y conseguí el 'trabajo' para mí. Intenté sacarle las coordenadas, pero no tuve éxito. Solo se jactaba de cómo se volvería tan rico como Craso y regresaría al Viejo Mundo\nNo dijo ni una palabra sobre la ubicación. Lo único que descubrí fue que su barco estaba reparado y que iba a zarpar hacia La Habana, donde intentaría organizar una misión en la dirección correcta. Después de todo, él no es el dueño del barco.";
		link.l1 = "¿Así que, él está en La Habana ahora?";
		link.l1.go = "mtraxx_5";
		break;

	case "mtraxx_5":
		dialog.text = "Zarpó hace dos días al amanecer. Tú eres el marinero aquí, tú haces el conteo.";
		link.l1 = "¿El nombre del capitán, el tipo y nombre de su barco, algo?";
		link.l1.go = "mtraxx_6";
		break;

	case "mtraxx_6":
		dialog.text = "¿Qué, me tomas por un tonto? Su nombre es Esberdo Cabanas, capitán del Cantavro. Creo que los marineros lo llamaban una goleta.";
		link.l1 = "¿Y eso es todo lo que sabes?";
		link.l1.go = "mtraxx_7";
		break;

	case "mtraxx_7":
		dialog.text = "¿Qué más quieres? Estoy seguro de que podrías alcanzarlo antes de La Habana. No pierdas tiempo, no creo que se tome un largo descanso antes de abandonar Cuba hacia su escondite, y luego es una causa perdida. Pensándolo bien, podrías quedarte una hora o dos, después de todo lo pagaste.";
		link.l1 = "Buen punto, cariño. Dos horas no marcarán mucha diferencia...";
		// belamour legendary edition -->
		link.l1.go = "mtraxx_7S";
		link.l2 = "Otra vez, querido. Considera tomarte un descanso para almorzar. Ve a la iglesia, o algo así.";
		link.l2.go = "mtraxx_7NS";
		sTotalTemp = npchar.id;
		AddMapQuestMarkCity("Havana", false);
		AddLandQuestMark(characterFromId("Havana_PortMan"), "questmarkmain");
		break;

	case "mtraxx_7S":
		DialogExit();
		pchar.GenQuest.BrothelCount = sti(pchar.GenQuest.BrothelCount) + 1; // для Данек
		Achievment_SetStat(23, 1);
		//<-- кол-во посещений
		str = npchar.city;
		pchar.quest.(str).win_condition.l1 = "ExitFromLocation";
		pchar.quest.(str).win_condition.l1.location = pchar.location;
		pchar.quest.(str).win_condition = "Brothel_checkVisitTime";
		pchar.questTemp.HorseQty = sti(pchar.questTemp.HorseQty) + 1; // счетчик
		AddDialogExitQuest("PlaySex_1");
		// кач от борделя
		if (CheckNPCQuestDate(pchar, "BrothelSex"))
		{
			if (IsEquipCharacterByArtefact(pchar, "totem_03"))
			{
				AddCharacterHealth(pchar, 10);
				AddCharacterMaxHealth(pchar, 1.0);
			}
			else
				AddCharacterHealth(pchar, 5);
			SetNPCQuestDate(pchar, "BrothelSex");
		}
		// изменение статусов
		ChangeCharacterComplexReputation(pchar, "nobility", -1);
		AddCharacterExpToSkill(pchar, "Leadership", 30);
		AddCharacterExpToSkill(pchar, "FencingS", -15);
		AddCharacterExpToSkill(pchar, "Pistol", -15);
		break;

	case "mtraxx_7NS":
		DialogExit();
		ChangeCharacterComplexReputation(pchar, "nobility", 1);
		AddQuestRecord("Roger_1", "3");
		pchar.questTemp.Mtraxx = "jewelry_3";
		SetFunctionTimerCondition("Mtraxx_JewelryHavanaOver", 0, 0, 7, false); // таймер
		ChangeCharacterAddressGroup(npchar, "none", "", "");
		pchar.quest.mtr_jewelry_havana.win_condition.l1 = "location";
		pchar.quest.mtr_jewelry_havana.win_condition.l1.location = "Cuba2";
		pchar.quest.mtr_jewelry_havana.function = "Mtraxx_HavanaInfo";
		DeleteAttribute(pchar, "questTemp.Mtraxx.AffairOfHonor");
		DeleteAttribute(pchar, "questTemp.ZA.Block");
		break;
	// <-- legendary edition
	case "mtraxx_R":
		dialog.text = "O-oh... Qué pena. Y pensé que estabas aquí de vacaciones. Mis chicas extrañan tanto a los corsarios valientes. Muy bien entonces, habla, ¿cuál es la tarea?..";
		link.l1 = "Marcus me encargó organizar una fiesta infernal en tu establecimiento durante dos días, beber todo el vino y acostarme con todas las chicas. ¿Cuándo comenzaremos?";
		link.l1.go = "mtraxx_R1";
		break;

	case "mtraxx_R1":
		dialog.text = "¡Ah, Charlie Prince, tu humor es tan agudo como tu sable! Casi me haces enfadar... ¡Chicas! Tenemos un invitado, ¡un invitado especial! ¡Traed vino y comida!";
		if (sti(pchar.money) >= 31000)
		{
			link.l1 = "¡Llama a todas las muchachas bonitas aquí! ¡Vamos a descansar y divertirnos! ¡Yo-ho-ho!..";
			link.l1.go = "mtraxx_R2";
		}
		else
		{
			link.l1 = "Espera un minuto, Janette. Necesito agarrar el oro de mi barco para ti y tus damas. ¡Nos vemos en un minuto!";
			link.l1.go = "exit";
			pchar.questTemp.Mtraxx.Retribution = "brothel_repeat";
			chrDisableReloadToLocation = false;
		}
		break;

	case "mtraxx_R2":
		AddMoneyToCharacter(pchar, -30000);
		dialog.text = "Ojalá todos nuestros clientes fueran tan dulces, guapos y generosos como tú... Te daremos una relajación perfecta. ¡Chicas!";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_RetributionInBrothel");
		break;
	// belamour ночной приключенец
	case "NA_Girl":
		dialog.text = "Oh, así que tenemos un conocedor aquí, jeje... Bueno, bueno, tengo a tal chica. Pero ella no viene barata: " + makeint(pchar.GenQuest.NightAdventure_money) + " pesos.";
		link.l1 = "Trato hecho.";
		link.l1.go = "NA_Girl_1";
		break;

	case "NA_Girl_1":
		AddMoneyToCharacter(pchar, -makeint(pchar.GenQuest.NightAdventure_money));
		dialog.text = "Eso es genial, querido. La Sacerdotisa del Amor te estará esperando arriba. Créeme, no te arrepentirás.";
		link.l1 = "Ya no lo hago.";
		link.l1.go = "NA_Girl_2";
		break;

	case "NA_Girl_2":
		DialogExit();
		pchar.GenQuest.NightAdventureVar = "NightAdventure_NobleWhore";
		sld = characterFromId(pchar.GenQuest.NightAdventureId);
		sld.dialog.currentnode = "NightAdventure_NobleWhore_7";
		break;
		// <-- приключенец

	case "chicken_god":
		dialog.text = "¿Para usted y m'lord Agueybana? Claro que sí. Eso serán diez mil, capitán.";
		if (sti(pchar.money) >= 10000)
		{
			link.l1 = "¡Espera, no así!.. ¡Maldición! No importa, aquí está el pago.";
			link.l1.go = "chicken_god_pay";
		}
		else
		{
			link.l2 = "¿Puedo obtener un préstamo?";
			link.l2.go = "chicken_god_notpay";
		}
		break;

	case "chicken_god_pay":
		dialog.text = "Disfruta de tu estancia, capitán. Por favor, regresa de nuevo cuando estemos abiertos. Nuestro establecimiento ofrece todo tipo de ocio para hombres y mujeres nobles.";
		link.l1 = "...";
		link.l1.go = "chicken_god_pay_1";
		break;

	case "chicken_god_pay_1":
		dialog.text = "";
		link.l1 = "Señora " + npchar.name + ", ¿puedes al menos explicar qué está pasando aquí? ¿El gobernador siquiera sabe que has tenido a un nativo a cargo durante un mes? Ningún asentamiento puede sobrevivir al cierre de un burdel por un día, ¡eso te lo puedo asegurar!";
		link.l1.go = "chicken_god_pay_2";
		break;

	case "chicken_god_pay_2":
		dialog.text = "La habitación es suya, capitán. Ahora, si me disculpa.";
		link.l1 = "Encantador. Adiós, señora.";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("ChickenGod_PayForRoom");
		break;

	case "chicken_god_notpay":
		dialog.text = "¿Por qué, Señor, por qué? ¡Sal de aquí! ¡Vete, vete, ya no puedo soportarlo más! ¡Bastardo!";
		link.l1 = "Eso salió bien.";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("ChickenGod_NotPayForRoom");
		break;

	//-->> Sinistra Ром на троих
	case "RomNaTroih_1":
		dialog.text = "Mhm... Normalmente no hago esto... pero estoy dispuesto a arriesgarme por ti. Es tu día de suerte, ¡Capitán!";
		link.l1 = "¡Vamos!";
		link.l1.go = "exit";
		pchar.RomNaTroih_Shluha = npchar.id;
		break;

	case "RomNaTroih_2":
		dialog.text = "Estoy enfadado contigo, Capitán... Pero te mostraré misericordia si trabajas lo suficientemente duro para ello.";
		link.l1 = "Oh, lo haré. ¿Abrimos vino?";
		link.l1.go = "exit";
		Achievment_Set("ach_CL_105");
		break;
	//<<-- Sinistra Ром на троих

	//--> прибыла инспекция на Святом Милосердии
	case "SantaMisericordia_1":
		dialog.text = "Hasta que ese maldito de Alamida se vaya. Maldito hombre santo...";
		link.l1 = "Pero quizás...";
		link.l1.go = "SantaMisericordia_2";
		break;

	case "SantaMisericordia_2":
		dialog.text = "Sin tal vez. ¿Y si entra aquí ahora mismo? Todos fuera.";
		link.l1 = "...";
		link.l1.go = "exit";
		LAi_CharacterDisableDialog(npchar);
		break;
		//<-- прибыла инспекция на Святом Милосердии
	}
}

ref GetFreeHorseRef(string City)
{
	ref rCharacter;
	int storeArray[8];
	int howStore = 0;
	for (int n = 0; n < MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City + "_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse" && rCharacter.horse == "HorseStay")
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0)
		return &NullCharacter;
	return &characters[storeArray[rand(howStore - 1)]];
}

ref CheckHorsesName(string City, int num)
{
	ref rCharacter;
	string sTemp, sSeeked;
	sSeeked = GetStrSmallRegister(dialogEditStrings[num]);
	for (int n = 0; n < MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (rCharacter.location == City + "_Brothel" && CheckAttribute(rCharacter, "CityType") && rCharacter.CityType == "horse")
		{
			sTemp = GetStrSmallRegister(rCharacter.lastname + " " + rCharacter.name);
			if (findsubstr(sSeeked, sTemp, 0) != -1)
				return rCharacter;
			sTemp = GetStrSmallRegister(rCharacter.lastname);
			if (findsubstr(sSeeked, sTemp, 0) != -1)
				return rCharacter;
			sTemp = GetStrSmallRegister(rCharacter.name);
			if (findsubstr(sSeeked, sTemp, 0) != -1)
				return rCharacter;
		}
	}
	return &NullCharacter;
}
