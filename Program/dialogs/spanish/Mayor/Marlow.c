// Захария Марлоу, Чёрный Пастор, Пуэрто-Принсипе, Куба
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sLoc;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// ------------------------------------------блок angry-----------------------------------------------
	if (CheckAttribute(npchar, "angry") && !CheckAttribute(npchar, "angry.ok"))
	{
		npchar.angry.ok = 1;
		if (!CheckAttribute(npchar, "angry.first")) // ловушка первого срабатывания
		{
			NextDiag.TempNode = NextDiag.CurrentNode;
			Dialog.CurrentNode = "AngryExitAgain";
			npchar.angry.first = 1;
		}
		else
		{
			switch (npchar.angry.kind) // сюда расписываем реакцию ангри. В npchar.angry.name пробелы удалены!!!
			{
			case "repeat":
				if (npchar.angry.name == "Firsttime")
					Dialog.CurrentNode = "AngryRepeat_1";
				if (npchar.angry.name == "I_know_you_good")
					Dialog.CurrentNode = "AngryRepeat_2";
				break;
			}
		}
	} //<-- блок angry

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = NPCStringReactionRepeat("¿Tienes algún asunto conmigo? ¡Si no, entonces lárgate de aquí!", "Creo que me he explicado claramente.", "¡Aunque he sido claro, sigues molestándome!", "Vale, me estoy cansando de esta grosería.", "repeat", 3, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Ya me voy.", "Por supuesto, Pastor.", "Lo siento, Pastor.", "Ups...", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";

		if (sti(pchar.GenQuest.Piratekill) > 20)
		{
			dialog.text = RandPhraseSimple("¿Estás loco? ¿Querías jugar al carnicero? Todos los piratas están enfadados contigo, chico, será mejor que abandones este lugar.", "   Parece que te has vuelto loco, chico. ¿Querías estirar un poco las manos? Sin ofender, pero no tienes nada que hacer aquí. ¡Piérdete!");
			link.l1 = RandPhraseSimple("Escucha, quiero arreglar la situación...", "Ayúdame a resolver este problema...");
			link.l1.go = "pirate_town";
			break;
		}

		//--> Сага
		if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && !CheckAttribute(npchar, "quest.sharkbegin"))
		{
			link.l1 = "Estoy tratando de encontrar a Shark Dodson. Dicen que eres el último hombre que lo vio. ¿Puedes ayudarme con eso?";
			link.l1.go = "Shark";
		}
		if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "terrax" && CheckCharacterItem(pchar, "witches_hammer"))
		{
			link.l1 = "¿Por qué eres tan grosero? ¿O no te interesa conseguir el libro que deseas de mí?";
			link.l1.go = "book";
		}
		//<-- Сага
		// поручение капитана - выкуп
		if (CheckAttribute(pchar, "GenQuest.CaptainComission") && NPChar.city == pchar.GenQuest.CaptainComission.PiratesCity)
		{
			if (CheckAttribute(pchar, "GenQuest.CaptainComission.toMayor"))
			{
				link.l1 = "Quiero hablar sobre tu prisionero.";
				link.l1.go = "CapComission1";
				DeleteAttribute(pchar, "GenQuest.CaptainComission.toMayor");
			}
			if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") // лесник. новая проверка. искл. возможность сразу сдать задание,минуя 15 дней.
			{
				link.l1 = "Hola, Pastor. Quiero hablar sobre tu misión.";
				link.l1.go = "CapComission3";
			}
			if (CheckAttribute(pchar, "GenQuest.CaptainComission.RepeatSpeak") && !CheckAttribute(pchar, "GenQuest.CaptainComission.vikupzaplatil"))
			{ // лесник . второй диалог с проверкой ,если ГГ ещё не принес деньги за выкуп.
				link.l1 = "Quiero hablar sobre tu prisionero.";
				link.l1.go = "CapComission6";
			}
		}
		break;

	case "shark":
		dialog.text = "¿Steven Dodson? No sé cómo mi historia te ayudaría porque Shark ha estado desaparecido en los últimos meses y nadie lo ha visto. Sin embargo, no es una sorpresa, mató a Blaze Sharp y desacreditó su propio nombre con esta acción insensata. Se hizo enemigo de algunos corsarios poderosos.";
		link.l1 = "Tengo todas las razones para pensar que Shark es inocente de la muerte de Sharp. No puedo probarlo, quizás Shark pueda hacerlo él mismo. ¿Vas a decirme algo sobre él?";
		link.l1.go = "shark_1";
		break;

	case "shark_1":
		dialog.text = "Hace unos meses, Steven vino a mí y me ofreció un trato muy extraño: dejó su fragata 'Fortuna' en prenda por un mes a cambio de un bergantín completamente cargado de provisiones. Luego, o me devuelve el bergantín y el dinero por las provisiones o me quedo con su fragata. Pasó un mes, ni rastro de Shark, ni de mi bergantín, ni del dinero.\nAdemás, escuché rumores de que Blaze fue asesinado y Shark era el sospechoso. ¿Qué podría pensar? ¡Correcto! Pensé que Steven había escapado de lo peor. Vendí su fragata a un inglés llamado William Patterson, él estaba muy complacido y pagó una gran pila de doblones por el barco.\nPor lo tanto, he compensado completamente mis gastos y no guardo rencor contra él. No me importa la muerte de Sharp, tengo mis propios problemas de los que preocuparme.";
		link.l1 = "¿No crees que si quisiera escapar, no necesitaría tu bergantín? Tenía su propio barco, cien veces mejor que cualquier bergantín. Parece que Shark tenía un plan, pero algo salió mal y no regresó a tiempo.";
		link.l1.go = "shark_2";
		break;

	case "shark_2":
		dialog.text = "Como ya te he dicho, no me importan los problemas de Dodson. He cumplido mi parte del trato. En cuanto al barco, será mejor que le preguntes a él por qué necesitaba la maldita goleta. No le obligué a tomarla.";
		link.l1 = "Está bien, no hablemos más de eso. Tienes razón, por supuesto. Dime, ¿sabes hacia dónde se dirigía Steven en tu bergantín?";
		link.l1.go = "shark_3";
		break;

	case "shark_3":
		dialog.text = "¿Quién sabe con certeza? Pero tengo algunas suposiciones. Navegó al noroeste hacia el Continente. Así que es o la Bahía del Peligro, conocida por sus indios hostiles, o la Nueva España, conocida por sus papistas y la Inquisición. Dudo que él navegue a cualquiera de estos lugares. Pero dicen que hay un lugar extraño llamado 'Ciudad de los Barcos Abandonados' ubicado al noroeste de Cuba. Mucha gente considera esto un mito, pero no yo. No porque sea una persona tan romántica, sino porque hay personas reales que navegan allí en sus chalupas. Al menos solían hacerlo.";
		link.l1 = "¿Y quiénes son ellos?";
		link.l1.go = "shark_4";
		break;

	case "shark_4":
		dialog.text = "Bucaneros de Cuba. Habían estado cargando sus barcas con cadáveres de toros y navegaron hacia el noroeste. Siempre regresaban un poco más tarde con los bolsillos llenos de dinero o con bienes raros y valiosos.";
		link.l1 = "¡Intrigante! ¿Dónde puedo encontrar a esos bucaneros?";
		link.l1.go = "shark_5";
		break;

	case "shark_5":
		dialog.text = "¿Por qué me lo preguntas a mí? Busca en los bosques de Cuba. Incluso si los encuentras, no te dirán nada, ¿por qué habrían de exponer la fuente de su buena vida? Así que no pierdas tu tiempo, nadie los ha visto hacerlo de nuevo desde hace mucho tiempo.\nAdemás, escuché de algunas notas escritas por el marinero español Alvarado que visitó la isla él mismo. Así que tengo curiosidad, quizás Steven navegó allí después de todo.";
		link.l1 = "La isla desconocida que no está en los mapas... Bueno. Esa no es información prometedora.";
		link.l1.go = "shark_6";
		break;

	case "shark_6":
		dialog.text = "Te he dicho desde el principio que mi historia no te ayudaría. ¿Y por qué necesitas a Dodson?";
		link.l1 = "Forest Devil y yo queremos elegirlo como líder de los Hermanos de la Costa. Como ya te he dicho, hay serias razones para sugerir que Blaze fue asesinado por alguien más.";
		link.l1.go = "shark_7";
		break;

	case "shark_7":
		dialog.text = "¡Je! ¿Supongo que Jan está de su lado? Bueno, ya conoces la ley: Dodson tendrá que obtener un voto de cada barón.";
		link.l1 = "Conozco la ley. Mi segunda pregunta entonces. ¿Votarás por Dodson en las elecciones?";
		link.l1.go = "shark_8";
		break;

	case "shark_8":
		dialog.text = "Bueno, primero debería regresar. En realidad, no me importa quién liderará a los Hermanos mientras haga bien su trabajo y no me moleste. Como dije, tengo mis propios problemas. ¿Sabes cuántas brujas y magos hay en nuestra isla? ¿No? Te lo diré: ¡un legión! Además, también hay muchos papistas en Santiago y La Habana.\nHablando de magos. Hay un libro llamado 'Martillo para las Brujas'. Realmente quiero conseguirlo, pero solo en inglés, no necesito traducciones al latín, alemán o español, no conozco esos idiomas. Tráeme el libro y votaré por Dodson.\nTen en cuenta que Jackman también me prometió encontrarlo, así que si él lo consigue primero... no me culpes entonces.";
		link.l1 = "Está bien, lo consideraré. Gracias por tu tiempo. Nos vemos.";
		link.l1.go = "shark_9";
		break;

	case "shark_9":
		DialogExit();
		pchar.questTemp.Saga.SharkHunt = "after_marlow";
		npchar.quest.sharkbegin = "true";
		AddQuestRecord("SharkHunt", "2");
		break;

	case "book":
		dialog.text = "¿El libro? ¿Supongo que estás hablando del 'Martillo para las Brujas'?";
		link.l1 = "Por supuesto. Pude encontrarlo para ti. Está en inglés como pediste.";
		link.l1.go = "book_1";
		break;

	case "book_1":
		dialog.text = "Ja,  perdona por tan ruda bienvenida, camarada. No volverá a pasar... ¡Déjame ver esa maravilla!";
		link.l1 = "Claro, echa un vistazo.";
		link.l1.go = "book_2";
		break;

	case "book_2":
		RemoveItems(pchar, "witches_hammer", 1); // удалить трактат
		dialog.text = "¡Finalmente! ¡Temblad ahora, siervos del Infierno! No os dejaré en paz hasta que mi mano ya no pueda golpear...";
		link.l1 = "Me alegro por ti, Pastor. ¿Y qué hay de tu voto?";
		link.l1.go = "book_3";
		break;

	case "book_3":
		dialog.text = "Como te dije 'No me importa quién se convertirá en el líder'. Estoy seguro de que Svenson no elegirá a un hombre indigno. Así que toma mi voto. Haz lo que quieras con él. Aquí está mi fragmento.";
		link.l1 = "Gracias, Zacarías. ¡Nos vemos allí!";
		link.l1.go = "book_4";
		break;

	case "book_4":
		GiveItem2Character(pchar, "splinter_zm"); // дать осколок
		DialogExit();
		NextDiag.CurrentNode = "I_know_you_good";
		AddQuestRecord("BarbTemptation", "27");
		if (CheckCharacterItem(pchar, "splinter_mt") && CheckCharacterItem(pchar, "splinter_jb") && CheckCharacterItem(pchar, "splinter_zm"))
			Saga_GiveCalendar();
		ChangeCharacterComplexReputation(pchar, "fame", 1);
		break;

	case "Exit":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		break;

	case "I_know_you_good":
		dialog.text = NPCStringReactionRepeat(GetFullName(pchar) + ", ¡Me alegra verte! ¿Qué deseas?", "¿Qué más quieres?", "¿Otra vez? ¡No molestes a la gente si no tienes nada que hacer!", "Eres un " + GetSexPhrase("buen corsario", "buena chica") + ", así que puedes vivir por ahora. Pero no quiero hablar contigo más.", "repeat", 10, npchar, Dialog.CurrentNode);
		link.l1 = HeroStringReactionRepeat("Solo estoy de visita.", "Nada...", "Está bien, Pastor, lo siento...", "¡Maldita sea, mi error!", npchar, Dialog.CurrentNode);
		link.l1.go = "exit";
		NextDiag.TempNode = "I_know_you_good";

		if (sti(pchar.GenQuest.Piratekill) > 20)
		{
			dialog.text = RandPhraseSimple("¿Estás loco? ¿Querías jugar al carnicero? Todos los piratas están enfadados contigo, chico, así que será mejor que te largues de aquí...", "   Parece que te has vuelto loco, muchacho. ¿Querías estirar un poco las manos? Sin ofender, pero no tienes nada que hacer aquí. ¡Piérdete!");
			link.l1 = RandPhraseSimple("Escucha, quiero arreglar la situación...", "Ayúdame a resolver este problema...");
			link.l1.go = "pirate_town";
			break;
		}
		// поручение капитана - выкуп
		if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar, "GenQuest.CaptainComission.toMayor"))
		{
			link.l1 = "Es sobre tu prisionero.";
			link.l1.go = "CapComission1";
			DeleteAttribute(pchar, "GenQuest.CaptainComission.toMayor");
		}
		if (CheckAttribute(pchar, "GenQuest.CaptainComission") && CheckAttribute(pchar, "GenQuest.CaptainComission.toMayor"))
		{
			link.l1 = "Es sobre tu prisionero.";
			link.l1.go = "CapComission1";
			DeleteAttribute(pchar, "GenQuest.CaptainComission.toMayor");
		}
		if (pchar.GenQuest.CaptainComission.PirateShips == "died" || pchar.GenQuest.CaptainComission.PirateShips == "goaway") //  правка лесник,новая проверка ,исключающая тут же сдачу задания
		{
			link.l1 = "Hola, Pastor, estoy aquí por tu misión.";
			link.l1.go = "CapComission3";
		}
		if (CheckAttribute(pchar, "GenQuest.Marginpassenger") && pchar.GenQuest.Marginpassenger == "cabin" && CheckAttribute(pchar, "questTemp.LongHappy"))
		{ // лесник . похититель  ( после ДЛС ДиС ,когда барбазона уже нет)
			link.l1 = "He oído que estás involucrado en negocios relacionados con prisioneros...";
			link.l1.go = "Marginpassenger";
		}
		break;

		//-----------------------------------Поручение капитана - Выкуп-------------------------------------------------
	case "CapComission1":
		dialog.text = "Ja-ja. ¿Crees que tengo solo un prisionero aquí? Nómbralo.";
		link.l1 = pchar.GenQuest.CaptainComission.SlaveName + ". ¿Está aquí?";
		link.l1.go = "CapComission2";
		DeleteAttribute(pchar, "GenQuest.CaptainComission.toMayor");
		break;

	case "CapComission2":
		if (CheckAttribute(pchar, "GenQuest.CaptainComission.DaysLeft"))
		{
			dialog.text = "Lo era. Lo he vendido a ese propietario de plantación de Barbados, el coronel Bishop, cuando estuvo aquí hace una semana.";
			link.l1 = "Maldita sea...";
			link.l1.go = "CapComission2_1";
		}
		else
		{
			dialog.text = "Ah, al fin. Estaba pensando en vendérselo a ese dueño de plantación de Barbados, llegará en una semana o dos... ¿Tienes un rescate?";
			link.l1 = "Mira, hay un pequeño problema... En realidad, no tengo tanto dinero. Pero estoy listo para trabajar.";
			link.l1.go = "CapComission2_2";
			if (makeint(pchar.money) > 150000)
			{
				link.l2 = "Es bueno que no lo hayas vendido. Aquí tienes tus monedas - 150.000 pesos. ¿Dónde puedo conseguirlo?" link.l2.go = "CapComission2_3";
			}
		}
		break;

	case "CapComission2_1":
		dialog.text = "Fuiste demasiado lento... ¿Y por qué te importa él? Solo he estado negociando con sus parientes.";
		link.l1 = "Me han pedido que venga aquí.";
		link.l1.go = "CapComission2_11";
		break;

	case "CapComission2_11":
		dialog.text = "Bueno, llegas tarde. No puedo hacer nada.";
		link.l1 = "Escucha, ¿por cuánto lo has vendido si no es un secreto?";
		link.l1.go = "CapComission2_12";
		break;

	case "CapComission2_12":
		dialog.text = "Eh, no lo es. Pero no te lo diré... te reirás si lo hago. ¡Ja-ja-ja-ja! Adiós.";
		link.l1 = "Nos vemos.";
		link.l1.go = "exit";
		AddQuestRecord("CaptainComission1", "10");
		AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow"); // правка лесник.  в СЖ запись ниже не работает
		// AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
		CaptainComission_GenerateManager();
		break;

	case "CapComission2_2":
		if (rand(3) == 1)
		{
			dialog.text = "Bueno, " + pchar.name + ", sabes, no funciona así. Vuelve con dinero y obtendrás a tu debilucho, ja-ja.";
			link.l1 = "Está bien. Nos vemos.";
			link.l1.go = "CapComission2_4";
		}
		else
		{
			dialog.text = "Bueno, bueno... Tengo un asunto... Ni siquiera sé por dónde empezar. Necesito hundir a un pirata que cruzó la línea.";
			link.l1 = "¿No puede simplemente ser asesinado en la jungla?";
			link.l1.go = "CapComission2_2_1";
		}
		break;

	case "CapComission2_2_1":
		dialog.text = "No es así como funciona el negocio, ¿sabes? No necesito su muerte, necesito enseñar a algunos a no tomar mi parte del botín. Pero no lamentaré su muerte.";
		link.l1 = "¿Por qué no envías a tu propia gente por él?";
		link.l1.go = "CapComission2_2_2";
		break;

	case "CapComission2_2_2":
		CaptainComission_GetRandomShore();
		pchar.GenQuest.CaptainComission.ShipName1 = GenerateRandomNameToShip(sti(NPChar.nation));
		pchar.GenQuest.CaptainComission.ShipName2 = GenerateRandomNameToShip(sti(NPChar.nation));
		pchar.GenQuest.CaptainComission.UnknownPirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
		sLoc = XI_ConvertString(pchar.GenQuest.CaptainComission.Island + "Dat"); // belamour gen
		dialog.text = "Hm... Bueno, " + GetName(NAMETYPE_ORIG, pchar.GenQuest.CaptainComission.UnknownPirateName, NAME_NOM) + " ha convencido a algunos piratas de que su parte del botín se guarda en nuestro escondite no lejos de " + XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Gen") + ". Sus dos barcos '" + pchar.GenQuest.CaptainComission.ShipName1 + "' y '" + pchar.GenQuest.CaptainComission.ShipName2 + " izó anclas no hace mucho y zarpó hacia " + sLoc + "¿Ahora ves por qué no puedo confiar en mis hombres para hacer ese trabajo?";
		link.l1 = "Lo hago. ¿Cuánto tiempo tengo?";
		link.l1.go = "CapComission2_2_3";
		break;

	case "CapComission2_2_3":
		dialog.text = "12 a 15 días, no más, es importante para mí que no lleguen al escondite, o será una tontería hundirlos con una carga valiosa. En ese caso, sería mejor que lo trajeran aquí...";
		link.l1 = "Está bien, estoy dentro. Intentaré atraparlos.";
		link.l1.go = "CapComission2_2_4";
		break;

	case "CapComission2_2_4":
		AddQuestRecord("CaptainComission1", "24");
		AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow"); // правка
		// AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
		AddQuestUserData("CaptainComission1", "sShipName1", pchar.GenQuest.CaptainComission.ShipName1);
		AddQuestUserData("CaptainComission1", "sShipName2", pchar.GenQuest.CaptainComission.ShipName2);
		AddQuestUserData("CaptainComission1", "sShoreName", XI_ConvertString(pchar.GenQuest.CaptainComission.Island.Shore + "Dat"));				 // belamour gen
		AddQuestUserData("CaptainComission1", "sShoreType", XI_ConvertString(GetIslandByArealName(pchar.GenQuest.CaptainComission.Island) + "Voc")); // belamour gen
		pchar.quest.CapComission_PirateAttack.win_condition.l1 = "location";
		pchar.quest.CapComission_PirateAttack.win_condition.l1.location = pchar.GenQuest.CaptainComission.Island;
		pchar.quest.CapComission_PirateAttack.function = "CaptainComission_GeneratePirateShips";
		SetFunctionTimerCondition("CaptainComission_PirateShipsOver", 0, 0, 15, false);
		// pchar.GenQuest.CaptainComission.PirateShips = "sdatkwest";	// лесник - заменил проверку для сдачи сразу.
		DialogExit();
		break;

	case "CapComission2_3":
		dialog.text = "No te preocupes. Mis hombres lo llevarán a tu barco. ¿Y por qué te importa él?";
		link.l1 = "No. Sus parientes me pidieron que lo entregara.";
		link.l1.go = "CapComission2_31";
		break;

	case "CapComission2_31":
		dialog.text = "Ah, está bien. Casi me sentí mal por ofrecer un precio tan bajo por tu hombre. Ja-ja-ja-ja. Adiós.";
		link.l1 = "Nos vemos.";
		link.l1.go = "CapComission2_32";
		break;

	case "CapComission2_32":
		AddQuestRecord("CaptainComission1", "9");
		AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
		AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc")); // belamour gen
		addMoneyToCharacter(pchar, -150000);
		pchar.GenQuest.CaptainComission.vikupzaplatil = true; // новая проверка ,если шарль заплатил выкуп за пленника. лесник
		DialogExit();
		AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

	case "CapComission2_4":
		if (!CheckAttribute(pchar, "GenQuest.CaptainComission.RepeatSpeak"))
		{
			AddQuestRecord("CaptainComission1", "31");
			AddQuestUserData("CaptainComission1", "sName", "Zachary Marlow"); // лесник
																			  // AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));// в СЖ не работает
		}
		pchar.GenQuest.CaptainComission.RepeatSpeak = true;
		DialogExit();
		break;

	case "CapComission3":
		dialog.text = "Entonces, " + GetFullName(pchar) + ", ¿hundiste a mis compinches? Je-je-je...";
		if (pchar.GenQuest.CaptainComission.PirateShips == "goaway")
		{
			link.l1 = "No. Fallé en atraparlos. Y no los encontré al regresar.";
			link.l1.go = "CapComission4";
		}
		if (pchar.GenQuest.CaptainComission.PirateShips == "died")
		{
			link.l1 = "Lo hice. Los envié a alimentar a los tiburones.";
			link.l1.go = "CapComission5";
		}
		DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
		break;

	case "CapComission4":
		dialog.text = "¡Maldita sea! ¡Los hayas conocido o no, eso ya no importa! ¿Y cuál será tu próxima sugerencia?";
		link.l1 = "¿Tal vez tienes un trabajo más sencillo para mí?";
		link.l1.go = "CapComission4_1";
		link.l2 = "Escucha, " + NPChar.name + ", baja el precio del prisionero...";
		link.l2.go = "CapComission4_2";
		break;

	case "CapComission4_1":
		dialog.text = "No.";
		link.l1 = "Adiós entonces...";
		link.l1.go = "CapComission4_3";
		break;

	case "CapComission4_2":
		dialog.text = "¿Bajar el precio?! ¡Acabo de perder mi alijo por tu incompetencia! ¡Y ahora puedo subir el precio! Puedes llevártelo por 200,000 pesos si quieres, o puedes largarte al diablo de aquí.";
		link.l1 = "Es demasiado caro... Adiós...";
		link.l1.go = "CapComission4_4";
		if (sti(pchar.money) >= 200000)
		{
			link.l2 = "Maldición, toma tus monedas.";
			link.l2.go = "CapComission4_5";
		}
		break;

	case "CapComission4_3":
		ChangeCharacterComplexReputation(pchar, "nobility", -2);
		AddQuestRecord("CaptainComission1", "27");
		AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("CaptainComission1", "sName", "Marlow"); // лесник
		// AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_DAT));
		AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
		AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
		DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
		DialogExit();
		break;

	case "CapComission4_4":
		ChangeCharacterComplexReputation(pchar, "nobility", -2);
		AddQuestRecord("CaptainComission1", "28");
		AddQuestUserData("CaptainComission1", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("CaptainComission1", "sName", "Marlow"); // правка	// лесник
		// AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM));
		AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
		AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
		DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
		DialogExit();
		break;

	case "CapComission4_5":
		dialog.text = "Puedes llevarte a este debilucho...";
		link.l1 = "Adiós.";
		link.l1.go = "CapComission4_6";
		break;

	case "CapComission4_6":
		addMoneyToCharacter(pchar, -200000);
		AddQuestRecord("CaptainComission1", "29");
		AddQuestUserData("CaptainComission1", "sName", "Marlow");																			 // правки имени в сж лесник
		AddQuestUserData("CaptainComission1", "sName", ChangeNameCase(NAMETYPE_MAIN, pchar.GenQuest.CaptainComission.PirateName, NAME_NOM)); // в сж не работает
		AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
		AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
		DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
		pchar.GenQuest.CaptainComission.SlaveAddMoney = true;
		DialogExit();
		AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

	case "CapComission5":
		dialog.text = "¡Ja-ja! ¡Bien hecho! Lleva a tu debilucho y buena suerte.";
		link.l1 = "Gracias. Adiós.";
		link.l1.go = "CapComission5_1";
		break;

	case "CapComission5_1":
		AddQuestRecord("CaptainComission1", "34");
		AddQuestUserData("CaptainComission1", "sName", pchar.GenQuest.CaptainComission.SlaveName);
		AddQuestUserData("CaptainComission1", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.CaptainComission.City + "Acc"));
		AddQuestUserData("CaptainComission1", "sCharName", pchar.GenQuest.CaptainComission.Name);
		DeleteAttribute(pchar, "GenQuest.CaptainComission.PirateShips");
		DialogExit();
		AddDialogExitQuestFunction("CaptainComission_GeneratePassengerSlave");
		break;

		/*case "CapComission6":    // ЕСЛИ В ПЕРВЫЙ РАЗ ОТКАЗАЛ В ЗАДАНИИ ,ТО ПУСТЬ БАБКИ ИЩЕТ
		 ИНАЧЕ ПОВТОРНАЯ ДАЧА ЗАДАНИЯ ПРЕВРАЩАЕТ КВЕСТ В КАШУ.. лесник
		dialog.text = "¿Trajiste el rescate?"+GetSexPhrase("","")+"¿Pues yo no estaba bromeando cuando dije que lo vendería a los plantadores?";
		link.l1 = "Escucha, "+NPChar.name+", aquí está el asunto... En fin, no tengo ese dinero. Pero estoy dispuesto"+GetSexPhrase("","а")+" trabajar.";
		link.l1.go = "CapComission2_2";
		if(makeint(pchar.money) > 150000)
		{
			link.l2 = "Es bueno que no lo hayas vendido. Aquí tienes tus monedas - 150000 pesos. ¿Dónde puedo conseguirlo?"link.l2.go ="CapComission2_3";
		}
	break;*/
	case "CapComission6": // лесник . пусть шарль бабло ищет,или забить на пленника.
		dialog.text = "¿Has traído el dinero? No estaba bromeando sobre vender a ese hombre a la plantación.";
		link.l1 = "No tengo el dinero, " + NPChar.name + ", pero estoy trabajando en ello.";
		link.l1.go = "exit";
		if (makeint(pchar.money) > 150000)
		{
			link.l2 = "Es bueno que no lo hayas vendido. Aquí están tus monedas - 150.000 pesos. ¿Dónde puedo encontrarlo?" link.l2.go = "CapComission2_3";
		}
		break;

		//--------------------------------------------Похититель------------------------------------------------------
	case "Marginpassenger":
		dialog.text = "¿Y por qué te importa lo que hago? Sabes, será mejor que te largues...";
		link.l1 = "Tshh, cálmate. Tengo un asunto contigo. Se trata de tu prisionero.";
		link.l1.go = "Marginpassenger_1";
		break;

	case "Marginpassenger_1":
		dialog.text = "Ah, está bien. ¿A quién quieres rescatar?";
		link.l1 = "Espera. No estoy aquí para comprar, estoy aquí para ofrecerte comprar un prisionero. Bueno, y tendrás la oportunidad de obtener un rescate por él.";
		link.l1.go = "Marginpassenger_2";
		break;

	case "Marginpassenger_2":
		dialog.text = "Mm. ¿Y por qué necesitas mi agencia? ¿Por qué no quieres conseguir dinero directamente para ti mismo?";
		link.l1 = "Es bastante arriesgado para mí. Puedo tener problemas con las autoridades.";
		link.l1.go = "Marginpassenger_3";
		break;

	case "Marginpassenger_3":
		dialog.text = "Ja-ja... está bien entonces. Echemos un vistazo. ¿Quién es tu prisionero?";
		link.l1 = "Esto es " + pchar.GenQuest.Marginpassenger.Text + " " + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.City + "Gen") + ".";
		link.l1.go = "Marginpassenger_4";
		break;

	case "Marginpassenger_4":
		int iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon) * 2 * stf(pchar.GenQuest.Marginpassenger.Chance)) * 100;
		dialog.text = "Veo... sería un buen trato si no estás mintiendo. Supongo que puedo pagarte por este hombre " + iTemp + " pesos o dar alguna información interesante en su lugar. Es tu elección.";
		link.l1 = "Mejor tomo pesos. Ya tuve suficiente de este asunto...";
		link.l1.go = "Marginpassenger_money";
		link.l2 = "¡Ja! Cuéntame más. Estoy seguro de que me darás algo interesante.";
		link.l2.go = "Marginpassenger_offer";
		break;

	case "Marginpassenger_money":
		dialog.text = "Dinero entonces. Llévatelos. Ahora, no es tu problema. Entrega el objeto de venta aquí.";
		link.l1 = "Ya debe estar cerca de las puertas de la ciudad. ¡Gracias! Realmente me has ayudado.";
		link.l1.go = "Marginpassenger_money_1";
		break;

	case "Marginpassenger_money_1":
		iTemp = makeint(sti(pchar.GenQuest.Marginpassenger.Dublon) * 2 * stf(pchar.GenQuest.Marginpassenger.Chance)) * 100;
		dialog.text = "De nada, tráeme más... ¡Nos vemos!";
		link.l1 = "Buena suerte...";
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, iTemp);
		sld = characterFromId("MarginPass");
		RemovePassenger(Pchar, sld);
		sld.lifeday = 0;
		AddQuestRecord("Marginpassenger", "12");
		AddQuestUserData("Marginpassenger", "sSum", iTemp);
		CloseQuestHeader("Marginpassenger");
		DeleteAttribute(Pchar, "GenQuest.Marginpassenger");
		break;

	case "Marginpassenger_offer":
		pchar.GenQuest.Marginpassenger.Goods = GetRandomGood(FLAG_GOODS_TYPE_EXPORT, FLAG_GOODS_VALUABLE_WOOD);
		pchar.GenQuest.Marginpassenger.GoodsQty = 200 + rand(10) * 10;
		switch (hrand(1))
		{
		case 0: // бухта на южном мейне
			SelectSouthshore();
			while (!isLocationFreeForQuests(pchar.GenQuest.Marginpassenger.Shore))
				SelectSouthshore();
			dialog.text = "Es bueno hacer negocios con un hombre inteligente. Ahora escucha: en pocos días a " + XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore + "Dat") + " una expedición española llegará desde el continente, cargada de bienes valiosos. Estarán esperando un barco que supuestamente debe recoger la carga. Si llegas allí en una semana, tendrás la oportunidad de quedarte con la carga.\nSi yo fuera tú, ya estaría moviéndome hacia mi barco. Y trae al prisionero aquí.";
			link.l1 = "¡Gracias! Las mercancías serán una buena compensación por mis problemas. Y mi pasajero ya debe estar cerca de las puertas de la ciudad. Será traído a ti.";
			link.l1.go = "Marginpassenger_offer_1";
			break;

		case 1: // просто кораблик
			SelectSouthcity();
			pchar.GenQuest.Marginpassenger.ShipName1 = GenerateRandomNameToShip(SPAIN);
			dialog.text = "Es bueno hacer negocios con un hombre listo. Ahora escucha: en aproximadamente una semana un bergantín español '" + pchar.GenQuest.Marginpassenger.ShipName1 + "' cargado con mercancías valiosas zarpará desde " + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity + "Gen") + " a " + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity1 + "Gen") + ". Si te apresuras, lo atraparás fácilmente.\n¿Todavía estás aquí? Si yo fuera tú, ya estaría yendo a mi barco. Y trae al prisionero aquí.";
			link.l1 = "¡Gracias! Las mercancías serán una buena compensación por mis problemas. Y mi pasajero ya debe estar cerca de las puertas de la ciudad. Te lo traerán.";
			link.l1.go = "Marginpassenger_offer_2";
			break;
		}
		sld = characterFromId("MarginPass");
		RemovePassenger(Pchar, sld);
		sld.lifeday = 0;
		pchar.GenQuest.Marginpassenger = "final";
		break;

	case "Marginpassenger_offer_1":
		DialogExit();
		AddQuestRecord("Marginpassenger", "13");
		AddQuestUserData("Marginpassenger", "sShore", XI_ConvertString(pchar.GenQuest.Marginpassenger.Shore + "Dat")); // лесник - окончание в СЖ // belamour gen: Abl - это к Залив"ом", нужен дательный
			AddQuestUserData("Marginpassenger", "sName", "Zachary Marlow")); // belamour gen : как-то странно, наводку даёт Захар, а в сж Добряк дефолтом
			SetFunctionTimerCondition("Marginpassenger_SouthshoreOver", 0, 0, 7, false);
			pchar.quest.Marginpassenger.win_condition.l1 = "location";
			pchar.quest.Marginpassenger.win_condition.l1.location = pchar.GenQuest.Marginpassenger.Shore;
			pchar.quest.Marginpassenger.function = "Marginpassenger_Southshore";
			break;

	case "Marginpassenger_offer_2":
		DialogExit();
		AddQuestRecord("Marginpassenger", "16");
			AddQuestUserData("Marginpassenger", "sName", "Zachary Marlow")); // belamour gen
			AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity + "Gen"));
			AddQuestUserData("Marginpassenger", "sCity1", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Southcity1 + "Acc")); // лесник - окончание в СЖ
			AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName1);
			SetFunctionTimerCondition("Marginpassenger_SouthshipInWorld", 0, 0, 5 + rand(2), false);
			break;

	// ============== Грабеж среди бела дня, попытка залезть в сундуки =========================
	case "Man_FackYou":
		dialog.text = LinkRandPhrase("¡Robo!!! Eso es inaceptable! Prepárate, " + GetSexPhrase("muchacho", "chica") + "...", "¡Eh, qué demonios haces ahí?! ¿Pensaste que podrías robarme? Estás acabado...", "Espera, ¿qué demonios? ¡Quita tus manos de encima! ¡Resulta que eres un ladrón! Se acabó, bastardo...");
		link.l1 = LinkRandPhrase("¡Mierda!", "¡Carramba!!", "¡Maldita sea!!");
		link.l1.go = "PL_Q3_fight";
		break;

	// ======================== блок нод angry ===============>>>>>>>>>>>>>>>
	case "AngryRepeat_1":
		dialog.text = RandPhraseSimple("" + GetSexPhrase("¡Aléjate! ", "Aléjate") + " ¡de aquí!", "¡Fuera de mi casa!");
		link.l1 = "Ups...";
		link.l1.go = "AngryExitAgainWithOut";
		if (CheckAttribute(npchar, "angry.terms")) // примиряемся через 10 дней.
		{
			if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
			{
				dialog.text = "No me molestes con tus charlas baratas. La próxima vez no te gustará el resultado...";
				link.l1 = "Lo tengo.";
				link.l1.go = NextDiag.TempNode;
				CharacterDelAngry(npchar);
			}
		}
		break;

	case "AngryRepeat_2":
		dialog.text = RandPhraseSimple("Se acabó, no hay más que hablar.", "Ya no quiero hablar contigo, así que será mejor que no me molestes.");
		link.l1 = RandPhraseSimple("Como desees...", "Mm, bien entonces...");
		link.l1.go = "AngryExitAgain";
		if (CheckAttribute(npchar, "angry.terms")) // примиряемся через 10 дней.
		{
			if (GetNpcQuestPastDayParam(npchar, "angry.terms") > sti(npchar.angry.terms))
			{
				dialog.text = "¿Espero que muestres más respeto y dejes de ser grosero?";
				link.l1 = "Puedes estar seguro, Pastor, lo haré.";
				link.l1.go = NextDiag.TempNode;
				CharacterDelAngry(npchar);
			}
		}
		break;

	case "AngryExitAgain":
		DialogExit();
		DeleteAttribute(npchar, "angry.ok");
		break;

	case "AngryExitAgainWithOut":
		DialogExit();
		DeleteAttribute(npchar, "angry.ok");
		DoReloadCharacterToLocation("Puertoprincipe_town", "reload", "reload6");
		break;
	// <<<<<<<<<<<<============= блок нод angry =============================
	case "pirate_town":
		dialog.text = "¿Resolver el problema? ¿Tienes alguna idea de lo que has hecho? De todos modos, tráeme un millón de pesos y persuadiré a los muchachos para que olviden tu hazaña. Si no te gusta la idea, entonces puedes irte al infierno.";
		if (sti(Pchar.money) >= 1000000)
		{
			link.l1 = "Está bien, estoy listo para pagar.";
			link.l1.go = "pirate_town_pay";
		}
		link.l2 = "Entendido. Me voy.";
		link.l2.go = "pirate_town_exit";
		break;

	case "pirate_town_exit":
		DialogExit();
		bDisableFastReload = true; // закрыть переход
		pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
		pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
		pchar.quest.pirate_in_town.function = "TownPirate_battle";
		break;

	case "pirate_town_pay":
		dialog.text = "¡Bien! Considérate limpio de nuevo. Pero espero que no vuelvas a hacer cosas tan asquerosas.";
		link.l1 = "No lo haré. Demasiado caro para mí. Adiós...";
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, -1000000);
		pchar.GenQuest.Piratekill = 0;
		break;
	}
}

void SelectSouthshore()
{
	switch (rand(6))
	{
	case 0:
		pchar.GenQuest.Marginpassenger.Shore = "shore37";
		break;
	case 1:
		pchar.GenQuest.Marginpassenger.Shore = "shore47";
		break;
	case 2:
		pchar.GenQuest.Marginpassenger.Shore = "shore48";
		break;
	case 3:
		pchar.GenQuest.Marginpassenger.Shore = "shore25";
		break;
	case 4:
		pchar.GenQuest.Marginpassenger.Shore = "shore21";
		break;
	case 5:
		pchar.GenQuest.Marginpassenger.Shore = "shore20";
		break;
	case 6:
		pchar.GenQuest.Marginpassenger.Shore = "shore19";
		break;
	}
}

void SelectSouthcity()
{
	switch (hrand(2))
	{
	case 0:
		pchar.GenQuest.Marginpassenger.Southcity = "Maracaibo";
		pchar.GenQuest.Marginpassenger.Southcity1 = "Havana";
		break;

	case 1:
		pchar.GenQuest.Marginpassenger.Southcity = "Cartahena";
		pchar.GenQuest.Marginpassenger.Southcity1 = "Santiago";
		break;

	case 2:
		pchar.GenQuest.Marginpassenger.Southcity = "Portobello";
		pchar.GenQuest.Marginpassenger.Southcity1 = "Santodomingo";
		break;
	}
}
