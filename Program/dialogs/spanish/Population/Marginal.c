// Jason общий диалог уличных контриков
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Citizen\" + NPChar.City + "_Citizen.c ";
						 if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "¿Qué quieres?";
		link.l1 = "Nada.";
		link.l1.go = "exit";
		link.l2 = RandPhraseSimple("Tengo una pregunta para ti.", "Necesito información.");
		link.l2.go = "quests"; //(перессылка в файл города)

		if (npchar.quest.meeting == "0")
		{
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Marginpassenger")) // захват пассажира
			{
				dialog.text = "¡Eh, capitán! Sí, tú. Ven aquí, tengo un trato para ti...";
				link.l1 = "¿Y cuál es el trato?";
				link.l1.go = "passenger";
				link.l2 = "Tengo prisa, amigo. Quizás la próxima vez.";
				link.l2.go = "exit_quest";
				npchar.quest.meeting = "1";
				DeleteAttribute(npchar, "talker"); // снимаем говорилку
				break;
			}
			dialog.text = LinkRandPhrase("Hola, capitán, estoy ocupado en realidad. ¿Qué necesitas?", "¿Qué quieres, capitán?", "Capitán, no estoy de humor para hablar. ¿Qué quieres?");
			link.l1 = "Saludos, " + GetAddress_FormToNPC(NPChar) + ". Espera un minuto, quiero que me digas algo.";
			link.l1.go = "question";
			link.l2 = RandPhraseSimple("Tengo una pregunta para ti.", "Necesito información.");
			link.l2.go = "quests"; //(перессылка в файл города)
			link.l3 = "No es nada, voy camino a la taberna...";
			link.l3.go = "exit";
			npchar.quest.meeting = "1";
		}
		NextDiag.TempNode = "First time";
		break;

		//----------------------------------------захват пассажиров для выкупа------------------------------------------
	case "passenger":
		DeleteAttribute(npchar, "talker");
		dialog.text = "Hum. Eres capitán de un barco, pero no pareces un mercader. Parece que tienes algunas monedas en el bolsillo... ¿Qué tal si obtienes información interesante a cambio de un puñado de doblones?";
		link.l1 = "Primero, demuestra que tu información vale una pieza de a ocho.";
		link.l1.go = "passenger_1";
		break;

	case "passenger_1":
		dialog.text = "Lo vale, capitán, lo vale. Cuesta mucho más de lo que pido. Tú dame el oro y te diré cuándo y en qué barco zarpará cierta persona muy importante. Podrás pedir un buen rescate por ella por un muy buen precio... Incluso te diré el nombre del comprador. ¿Trato?";
		link.l1 = "¡De ninguna manera! No soy un secuestrador. ¡Lárgate!";
		link.l1.go = "exit_quest";
		link.l2 = "¿Y cómo puedo saber que estás diciendo la verdad?";
		link.l2.go = "passenger_2";
		break;

	case "passenger_2":
		pchar.GenQuest.Marginpassenger.Dublon = 70 + hrand(5) * 10;
		dialog.text = "Sería muy imprudente engañarte, perro de mar. Vivo en esta ciudad y no necesito problemas. Por solo " + sti(pchar.GenQuest.Marginpassenger.Dublon) + " doblones proporcionaré información completa. Ganarás mucho más.";
		if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.GenQuest.Marginpassenger.Dublon))
		{
			link.l1 = "Tienes razón. Toma el oro y empieza a hablar.";
			link.l1.go = "passenger_4";
		}
		link.l2 = "No tengo suficientes monedas conmigo ahora.";
		link.l2.go = "passenger_3";
		link.l3 = "¿Te estás burlando de mí? ¿Pagar oro real por promesas vacías? Piérdete...";
		link.l3.go = "exit_quest";
		break;

	case "passenger_3":
		dialog.text = "¿No lo haces? Bien, capitán. Puedo esperar unos días más y esta información también. Encuéntrame cuando consigas tu oro. No será difícil encontrarme... hoy, ¡ja-ja-ja!";
		link.l1 = "No enseñes los dientes así. Está bien, te traeré el oro... si no cambio de opinión.";
		link.l1.go = "passenger_wait";
		break;

	case "passenger_wait":
		DialogExit();
		SetFunctionTimerCondition("Marginpassenger_Over", 0, 0, 2, false);
		npchar.dialog.currentnode = "passenger_repeat";
		break;

	case "passenger_repeat":
		dialog.text = "¿Trajiste mi oro?";
		if (GetCharacterItem(pchar, "gold_dublon") >= sti(pchar.GenQuest.Marginpassenger.Dublon))
		{
			link.l1 = "Sí. Tómalo. Ni siquiera intentes mentir ahora...";
			link.l1.go = "passenger_4";
		}
		link.l2 = "Aún no. Tal vez más tarde...";
		link.l2.go = "exit";
		Nextdiag.Tempnode = "passenger_repeat";
		break;

	case "passenger_4":								   // установка параметров
		pchar.quest.Marginpassenger_Over.over = "yes"; // снять возможный таймер
		RemoveItems(pchar, "gold_dublon", sti(pchar.GenQuest.Marginpassenger.Dublon));
		pchar.GenQuest.Marginpassenger.Name = GetFullName(npchar);
		pchar.GenQuest.Marginpassenger.City = npchar.city;
		pchar.GenQuest.Marginpassenger.Targetcity = SelectAnyColony(npchar.city);
		pchar.GenQuest.Marginpassenger.Nation = npchar.nation;
		pchar.GenQuest.Marginpassenger.Days = 10 + hrand(5);
		pchar.GenQuest.Marginpassenger.ShipName = GenerateRandomNameToShip(sti(npchar.nation));
		pchar.GenQuest.Marginpassenger.q2Name = GenerateRandomName(sti(npchar.nation), "man");
		pchar.GenQuest.Marginpassenger.Chance = 0.8 + frand(0.4);
		SelectMarginpassengerParameter();
		log_testinfo(pchar.GenQuest.Marginpassenger.Targetcity);
		dialog.text = "Mantén tu pólvora seca, la necesitarás pronto, capitán. Ahora escucha, en " + FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days)) + " un barco zarpará de nuestra colonia, el barco es " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name"))) + " llamado '" + pchar.GenQuest.Marginpassenger.ShipName + "y se dirigirá a " + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Targetcity + "Gen") + ". Habrá un pasajero, " + pchar.GenQuest.Marginpassenger.Text + ", llamado " + pchar.GenQuest.Marginpassenger.q1Name + "\nEl capitán " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name") + "Gen")) + " es un cobarde de barriga amarilla como todos los comerciantes, ¡ja-ja-ja! Quizás incluso evites cualquier pelea. Solo infúndele el miedo del diablo y él mismo debería entregarte el objetivo, je-je\nComo entiendes, " + pchar.GenQuest.Marginpassenger.Text1 + ", probablemente obtendrás tus monedas, sí, pero las autoridades locales te cazarán hasta la muerte después de eso. Será mejor que traigas tu presa a " + XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Targetcity) + ". Allí encontrarás a un hombre llamado " + pchar.GenQuest.Marginpassenger.q2Name + "\n" + pchar.GenQuest.Marginpassenger.Text2 + " y ni siquiera necesitarás decir tu nombre. Es tu decisión dónde rescatar a tu hombre, pero no muerdas más de lo que puedas masticar... Pero " + sti(pchar.GenQuest.Marginpassenger.Dublon) * 4 + "doblones que puedes pedir sin duda. ¿Entendido?";
		link.l1 = "Sí. Voy a volver a mi barco y escribirlo en el diario.";
		link.l1.go = "passenger_5";
		break;

	case "passenger_5":
		dialog.text = "¡Exactamente! Buena elección. Bien, capitán, buena suerte en esta tarea sencilla. Oh sí, casi lo olvido: " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name"))) + " no zarpará desde el puerto, sino desde una de las bahías cercanas. Así que estate atento. ¡Buena suerte y gracias por el oro!";
		link.l1 = "De nada. No lo gastes todo en una noche.";
		link.l1.go = "exit_quest";
		npchar.lifeday = 0;
		ReOpenQuestHeader("Marginpassenger");
		AddQuestRecord("Marginpassenger", "1");
		AddQuestUserData("Marginpassenger", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.City));
		AddQuestUserData("Marginpassenger", "sTargetCity", XI_ConvertString("Colony" + pchar.GenQuest.Marginpassenger.Targetcity));
		AddQuestUserData("Marginpassenger", "sName", pchar.GenQuest.Marginpassenger.Name);
		AddQuestUserData("Marginpassenger", "sName1", pchar.GenQuest.Marginpassenger.q1Name);
		AddQuestUserData("Marginpassenger", "sName2", pchar.GenQuest.Marginpassenger.q2Name);
		AddQuestUserData("Marginpassenger", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Marginpassenger.Days)));
		AddQuestUserData("Marginpassenger", "sShipType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Marginpassenger.ShipType), "Name") + "Voc")));
		AddQuestUserData("Marginpassenger", "sShipName", pchar.GenQuest.Marginpassenger.ShipName);
		AddQuestUserData("Marginpassenger", "sText", pchar.GenQuest.Marginpassenger.Text1);
		pchar.GenQuest.Marginpassenger = "begin";
		SetFunctionTimerCondition("Marginpassenger_InWorld", 0, 0, sti(pchar.GenQuest.Marginpassenger.Days), false);
		break;

	// замечание по обнажённому оружию от персонажей типа citizen
	case "CitizenNotBlade":
		dialog.text = NPCharSexPhrase(NPChar, "Escucha, amigo, cálmate y envaina tu arma.", "Escucha, compañero, cálmate y envaina tu arma.");
		link.l1 = LinkRandPhrase("Bien.", "Bien.", "Como desees.");
		link.l1.go = "exit";
		break;

	case "question":
		dialog.text = LinkRandPhrase("¡No andes con rodeos, capitán. Habla lo que deseas!", "Ah, bien. ¿Qué quieres?", "¿Preguntas? Bien, marinero, estoy escuchando.");
		link.l1 = LinkRandPhrase("¿Puedes contarme los últimos chismes?", "¿Ha ocurrido algo interesante aquí recientemente?", "¿Qué está pasando en el Caribe?");
		link.l1.go = "rumours_marginal";
		break;

	case "exit_quest":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}

void SelectMarginpassengerParameter()
{
	if (hrand(1) == 0)
	{
		pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "woman");
		pchar.GenQuest.Marginpassenger.model = "women_" + (rand(5) + 11);
		pchar.GenQuest.Marginpassenger.sex = "woman";
		pchar.GenQuest.Marginpassenger.ani = "towngirl";
		pchar.GenQuest.Marginpassenger.Text2 = "Quiere casarse con ella y pagará una suma importante por la chica.";
		switch (hrand(4))
		{
		case 0:
			pchar.GenQuest.Marginpassenger.Text = "hija del tendero";
			pchar.GenQuest.Marginpassenger.Text1 = "de su padre, el tendero";
			pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_store";
			break;
		case 1:
			pchar.GenQuest.Marginpassenger.Text = "hija del patrón del astillero";
			pchar.GenQuest.Marginpassenger.Text1 = "de su padre, el maestro del astillero";
			pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_shipyard";
			break;
		case 2:
			pchar.GenQuest.Marginpassenger.Text = "hija del tabernero";
			pchar.GenQuest.Marginpassenger.Text1 = "de su padre, el tabernero";
			pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_tavern";
			break;
		case 3:
			pchar.GenQuest.Marginpassenger.Text = "hija de banquero";
			pchar.GenQuest.Marginpassenger.Text1 = "de su padre, el banquero";
			pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_bank";
			break;
		case 4:
			pchar.GenQuest.Marginpassenger.Text = "hija del capitán del puerto";
			pchar.GenQuest.Marginpassenger.Text1 = "de su padre, el capitán del puerto";
			pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_portoffice";
			break;
		}
	}
	else
	{
		pchar.GenQuest.Marginpassenger.q1Name = GenerateRandomName(sti(pchar.GenQuest.Marginpassenger.Nation), "man");
		pchar.GenQuest.Marginpassenger.model = "citiz_" + (rand(9) + 11);
		pchar.GenQuest.Marginpassenger.sex = "man";
		pchar.GenQuest.Marginpassenger.ani = "man";
		pchar.GenQuest.Marginpassenger.Text2 = "Ha estado planeando congraciarse con esta familia y pagará mucho por el prisionero ";
		switch (hrand(4))
		{
		case 0:
			pchar.GenQuest.Marginpassenger.Text = "pariente del comerciante, del capitán del barco";
			pchar.GenQuest.Marginpassenger.Text1 = "de su pariente, el capitán del barco";
			pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_store";
			break;
		case 1:
			pchar.GenQuest.Marginpassenger.Text = "familiar del capitán del astillero";
			pchar.GenQuest.Marginpassenger.Text1 = "de su pariente, el maestro del astillero";
			pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_shipyard";
			break;
		case 2:
			pchar.GenQuest.Marginpassenger.Text = "pariente del tabernero";
			pchar.GenQuest.Marginpassenger.Text1 = "de su pariente, el tabernero";
			pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_tavern";
			break;
		case 3:
			pchar.GenQuest.Marginpassenger.Text = "pariente del banquero";
			pchar.GenQuest.Marginpassenger.Text1 = "de su pariente, el banquero";
			pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_bank";
			break;
		case 4:
			pchar.GenQuest.Marginpassenger.Text = "pariente del capitán del puerto";
			pchar.GenQuest.Marginpassenger.Text1 = "de su pariente, el capitán del puerto";
			pchar.GenQuest.Marginpassenger.loc = pchar.GenQuest.Marginpassenger.City + "_portoffice";
			break;
		}
	}
	if (sti(pchar.rank) < 5) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_6, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 5 && sti(pchar.rank) < 10) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 10 && sti(pchar.rank) < 17) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_4 + FLAG_SHIP_CLASS_5, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 17 && sti(pchar.rank) < 26) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_3 + FLAG_SHIP_CLASS_4, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
	if (sti(pchar.rank) >= 26) pchar.GenQuest.Marginpassenger.ShipType = GetRandomShipType(FLAG_SHIP_CLASS_2 + FLAG_SHIP_CLASS_3, FLAG_SHIP_TYPE_ANY - FLAG_SHIP_TYPE_MERCHANT, FLAG_SHIP_NATION_ANY);
}
