// реплики солдат на палубе при разговоре в море
// форт-стража и комендант форта
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "exit":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		break;

	case "First time":
		dialog.text = "Habla con nuestro capitán. No tengo nada que decirte.";
		Link.l1 = "Bien.";
		Link.l1.go = "exit";

		NextDiag.TempNode = "first time";
		break;
	//  на палубе -->
	case "On_Deck":
		dialog.text = "Habla con nuestro capitán. No tengo nada que decirte.";
		Link.l1 = "Bien.";
		Link.l1.go = "exit";

		NextDiag.TempNode = "On_Deck";
		/*
					// Первый церковный генератор
					if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.CapWaitOnTavern"))
					{
						if(CheckAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"))
						{
							dialog.text = "Señor, ¿está buscando a alguien?";
							Link.l1 = "Sí, camarada. ¿Puedo ver al capitán?";
							Link.l1.go = "ChurchQuest1_Node1";
						}
						else
						{
							dialog.text = "Si estás buscando a nuestro capitán. Él ha desembarcado recientemente.";
							Link.l1 = "Bien";
							Link.l1.go = "exit";
						}
						break;
					}
		*/
		//--> eddy. квест мэра, закрываем выход с палубы и ноду даем нужную
		if (CheckAttribute(pchar, "GenQuest.DestroyPirate") && pchar.GenQuest.CaptainId == "MQPirate")
		{
			dialog.text = RandPhraseSimple("Oh, has venido aquí solo. ¡Ja! En ese caso, ve a nuestro capitán. Cuéntale sobre tus tristes hazañas...", "Vaya, parece que estás loco, amigo. Ve a nuestro capitán y él hablará contigo.");
			Link.l1 = "Qué lástima...";
			Link.l1.go = "exit";
		}
		//<-- eddy. квест мэра, закрываем выход с палубы
		break;
		/*
				case "ChurchQuest1_Node1":
					dialog.text = "Será mejor que lo busques en el puerto.";
					Link.l1 = "Gracias, mi amigo.";
					Link.l1.go = "exit";
					NextDiag.TempNode = "On_Deck";
					PChar.GenQuest.ChurchQuest_1.CapWaitOnTavern = true;
					DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.NeedToDialogWithSailors"); // Не спрашиваем моряков
				break;
		*/
	//  на палубе <--

	// ugeen --> разговор с боцманом по генератору "Повод для спешки"
	case "On_MyShip_Deck":
		dialog.text = "¡Vaya, eso fue un verdadero desastre, capitán! Estábamos en la taberna, bebiendo como solemos hacer cuando escuchamos gritos. Salimos corriendo de la taberna y vimos que intentaban arrestarte. ¡Que se jodan! Así que decidimos dejar este puerto hostil.";
		link.l1 = "Sí, ciertamente algunas personas tienen una percepción un poco extraña de la justicia.";
		link.l1.go = "On_MyShip_Deck_1";
		break;

	case "On_MyShip_Deck_1":
		if (pchar.questTemp.ReasonToFast == "speakSuccess_chain_A")
		{
			// карты не было
			dialog.text = "¡Capitán! ¡No os preocupéis así! Estaba claro que no había manera de huir en paz, así que hemos decidido visitar al banquero para revisar sus cofres. Aquí está vuestra parte, " + sti(pchar.questTemp.ReasonToFast.p9) + " pesos...";
		}
		if (pchar.questTemp.ReasonToFast == "speakSuccess_chain_B")
		{
			// карту отобрали
			GiveItem2Character(pchar, pchar.questTemp.ReasonToFast.p6);
			dialog.text = "¡Capitán! ¡No se preocupe así! Estaba claro que no había manera de huir en paz, así que hemos decidido visitar al banquero y revisar sus cofres. También había una buena espada en la caja de empeño. Aquí está su parte, " + sti(pchar.questTemp.ReasonToFast.p9) + " pesos y una espada...";
		}
		link.l1 = "¡Bien hecho, muchachos! ¡Bien hecho! Estoy orgulloso de vosotros.";
		link.l1.go = "On_MyShip_Deck_End";
		AddMoneyToCharacter(pchar, sti(pchar.questTemp.ReasonToFast.p9));
		pchar.Ship.Crew.Morale = MORALE_MAX;
		chrDisableReloadToLocation = false; // Откроем выход
		AddQuestRecord("ReasonToFast", "17");
		AddQuestUserData("ReasonToFast", "sSex", GetSexPhrase("", ""));
		CloseQuestHeader("ReasonToFast");
		DeleteAttribute(pchar, "TownEscape");
		DeleteAttribute(pchar, "questTemp.ReasonToFast");
		QuestOpenSeaExit();
		break;

	case "On_MyShip_Deck_End":
		DialogExit();
		AddDialogExitQuest("CanEnterToMap");
		break;

	// разговор с боцманом по генератору 'Операция Галеон'
	case "CapComission_OnShipDeck":
		dialog.text = "Capitán, tu amigo ha escapado.";
		link.l1 = "¿Qué amigo?";
		link.l1.go = "CapComission_OnShipDeck1";
		break;

	case "CapComission_OnShipDeck1":
		dialog.text = "Ese amigo que has sacado de las mazmorras.";
		link.l1 = "¿Cómo demonios lograste perderlo?!";
		link.l1.go = "CapComission_OnShipDeck2";
		break;

	case "CapComission_OnShipDeck2":
		dialog.text = "No fue culpa nuestra, capitán. Se lanzó por la letrina al mar... Intentamos dispararle, pero estaba demasiado oscuro allí...";
		link.l1 = "¡Maldita sea! ¡Realmente se te ha ido de las manos! ¡Todos seréis desembarcados y enviados a trabajar con la caña de azúcar! ¡Perder a un pez gordo tan valioso! ¡Increíble!";
		link.l1.go = "CapComission_OnShipDeck3";
		break;

	case "CapComission_OnShipDeck3":
		chrDisableReloadToLocation = false; // Откроем выход
		AddQuestRecord("CaptainComission2", "25");
		AddQuestUserData("CaptainComission2", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("CaptainComission2", "sName", pchar.GenQuest.CaptainComission.Name);
		CloseQuestHeader("CaptainComission2");
		ChangeOfficersLoyality("bad_all", 1);
		ChangeCharacterComplexReputationABS(pchar, "authority", 1);
		DeleteAttribute(pchar, "TownEscape");
		DeleteAttribute(pchar, "GenQuest.CaptainComission.canSpeakBoatswain");
		DeleteAttribute(pchar, "GenQuest.CaptainComission");
		QuestOpenSeaExit();
		DialogExit();
		AddDialogExitQuest("CanEnterToMap");
		break;
	// <-- ugeen

	// разговор с боцманом по ситуациям в трюме
	case "Hold_GenQuest_OnShipDeck":
		dialog.text = "Capitán, perdónanos, por nuestra culpa el prisionero se ha escapado.";
		link.l1 = "¿Qué prisionero? ¿Quién se ha escapado?";
		link.l1.go = "Hold_GenQuest_OnShipDeck1";
		break;

	case "Hold_GenQuest_OnShipDeck1":
		dialog.text = "Bueno, oh, olvidé su nombre, " + pchar.GenQuest.Hold_GenQuest.CapName + ", ¿verdad?";
		link.l1 = "¡Maldita sea! ¿Dónde estabas mirando?";
		link.l1.go = "Hold_GenQuest_OnShipDeck2";
		break;

	case "Hold_GenQuest_OnShipDeck2":
		dialog.text = "Se salió de la bodega y saltó desde la amurada. No le disparamos para evitar ruido y mientras preparábamos un bote, fue rescatado por malditos pescadores.";
		link.l1 = "¡Y por qué te pago! Azota al jefe de guardia y prívate de ron por una semana. ¡A sus puestos! Estamos levantando anclas...";
		link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;

	case "Hold_GenQuest_OnShipDeck3":
		chrDisableReloadToLocation = false; // Откроем выход
		sld = characterFromId(pchar.GenQuest.Hold_GenQuest.CapId);
		ReleasePrisoner(sld);
		CloseQuestHeader("HoldQuest");
		DeleteAttribute(pchar, "TownEscape");
		DeleteAttribute(pchar, "GenQuest.Hold_GenQuest.canSpeakSailor");
		DeleteAttribute(pchar, "GenQuest.Hold_GenQuest");
		QuestOpenSeaExit();
		DialogExit();
		AddDialogExitQuest("CanEnterToMap");
		break;

	case "Hold_GenQuest_OnShipDeck4":
		dialog.text = "Saludos, capitán. No hubo accidentes durante su...";
		link.l1 = "Bien, bien, lo tengo.... Hay un prisionero en nuestra bodega. Su nombre es " + pchar.GenQuest.Hold_GenQuest.CapName + "  Lleva a unos cuantos hombres y llévalo al puerto. Ahora es libre.";
		link.l1.go = "Hold_GenQuest_OnShipDeck5";
		break;

	case "Hold_GenQuest_OnShipDeck5":
		dialog.text = "¿Está libre de verdad? ¿Debemos entregarlo en un bote?";
		link.l1 = "No en una maldita tortuga... Pensé que había sido bastante claro. ¡Y date prisa! Necesitamos levar anclas al comienzo de la bajamar.";
		link.l1.go = "Hold_GenQuest_OnShipDeck3";
		break;

	// Warship 09.07.09 Базар с нашим матросом на палубе Мэри Селест -->
	case "On_MaryCeleste_Deck":
		Dialog.text = "¡Capitán, no hay gente en absoluto en el barco! Algo está muy mal aquí... Tommy dijo que había visto un gato en el puente y era la única alma viviente...";
		Link.l1 = "Idiota, los gatos no tienen alma. Parece que no ha visitado una iglesia hace mucho tiempo o que nunca ha estado allí. ¿Has estado en el camarote del capitán? Necesito un diario de navegación.";
		Link.l1.go = "On_MaryCeleste_Deck_1";
		break;

	case "On_MaryCeleste_Deck_1":
		Dialog.text = "No, sí tienen almas. No había ningún cuaderno de bitácora ni un solo instrumento de navegación. Ni siquiera un solo bote...";
		Link.l1 = "Ellos no. ¿Fue arrastrado por una tormenta?";
		Link.l1.go = "On_MaryCeleste_Deck_2";
		break;

	case "On_MaryCeleste_Deck_2":
		Dialog.text = "Lo tienen, capitán. Los gatos tienen alma. Capitán, el bote fue cortado y hemos encontrado una espada en el suelo de la cabina. Está oxidada y ensangrentada. Aquí, eche un vistazo...";
		Link.l1 = "Deja de darme esta mierda, tírala, y deja de hablar de gatos, ¡maldita sea! Revisemos la bodega y vámonos... Oh, algo está muy mal aquí y no me gusta un carajo...";
		Link.l1.go = "On_MaryCeleste_Last";
		NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;

	case "On_MaryCeleste_Last":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		LAi_SetCitizenType(NPChar); // Чтоб по палубе ходил

		NPChar = GetRealShip(GetCharacterShipType(CharacterFromID("MaryCelesteCapitan")));
		NPChar.TurnRate = sti(PChar.QuestTemp.MaryCeleste.TurnRate); // Вернем манёвренность, для интерфейса

		chrDisableReloadToLocation = false; // Откроем выход

		LaunchTransferMain(PChar, CharacterFromID("MaryCelesteCapitan"), "MaryCelesteTransfer");
		break;

	case "On_MaryCeleste_Deck_SailorLast":
		switch (rand(2))
		{
		case 0:
			Dialog.text = "Capitán, tengo un mal presentimiento sobre este lugar... ¿Quizás es hora de que nos vayamos?";
			Link.l1 = "Sí... Ve al bote del barco.";
			Link.l1.go = "exit";
			break;

		case 1:
			Dialog.text = "Capitán, no voy a quedarme en este extraño barco si está dispuesto a llevarlo al puerto. Mejor salto al mar yo mismo.";
			Link.l1 = "No estoy dispuesto a hacer eso... También estoy un poco asustado...";
			Link.l1.go = "exit";
			break;

		case 2:
			Dialog.text = "¿Quizás deberíamos hundirlo, capitán?";
			Link.l1 = "¿Para dejar que las almas de los marineros muertos que viven aquí nos visiten en nuestras pesadillas?";
			Link.l1.go = "On_MaryCeleste_Deck_SailorLast_1";
			break;
		}

		NextDiag.TempNode = "On_MaryCeleste_Deck_SailorLast";
		break;

	case "On_MaryCeleste_Deck_SailorLast_1":
		Dialog.text = "¡Santo Dios, no! Capitán... ¿por qué dices eso?";
		Link.l1 = "No te pongas pálido, estaba bromeando... Ve al bote del barco. Y supongo que tienes razón después de todo, quizás los gatos realmente tengan almas...";
		Link.l1.go = "exit";
		break;
	// <-- Базар с нашим матросом на палубе Мэри Селест

	//  на палубе <--
	case "On_Fort":
		dialog.text = RandPhraseSimple("Habla con el jefe. No tengo nada que decirte.", "Estoy en mi puesto. Todas las preguntas van al comandante del fuerte.");
		Link.l1 = "Bien.";
		Link.l1.go = "exit";

		NextDiag.TempNode = "On_Fort";
		break;

	case "On_Fort_Head":
		dialog.text = RandPhraseSimple("Estoy realmente ocupado ahora. Déjame en paz.", "No me distraigas de mi trabajo. No hay nada de qué hablar.");
		Link.l1 = "Lástima...";
		Link.l1.go = "exit";

		NextDiag.TempNode = "On_Fort_Head";
		break;

	case "Morgan_wait_you":
		Dialog.defAni = "dialog_stay1";
		Dialog.defCam = "1";
		Dialog.defSnd = "dialogs\0\017";
		Dialog.defLinkAni = "dialog_1";
		Dialog.defLinkCam = "1";
		Dialog.defLinkSnd = "dialogs\woman\024";
		Dialog.ani = "dialog_stay2";
		Dialog.cam = "1";
		Dialog.snd = "dialogs\0\009";

		dialog.text = RandPhraseSimple("Morgan quería decirte 'una cosa o dos'... Está por aquí, en la cubierta.", "Heh, encuentra a Morgan. Malas noticias te están esperando...");
		Link.l1 = "Bien.";
		Link.l1.go = "exit";

		NextDiag.TempNode = "Morgan_wait_you";
		break;
	}
}
