// Jason общий диалог уличных монахов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp, iTest;
	string sTemp, sTitle;

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

	iTest = FindColony(NPChar.City);
	ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}

	switch (Dialog.CurrentNode)
	{
	case "First time":
		//--> диалог первой встречи
		if (npchar.quest.meeting == "0")
		{
			if (CheckAttribute(npchar, "quest.donation")) // пожертвования
			{
				dialog.text = "Buen día para ti, hijo mío. Te pido que muestres algo de favor y dones unas pocas monedas de plata para el bien de los pobres, tu alma y la Santa Madre Iglesia.";
				link.l1 = "Bien padre, supongo que todos debemos ayudarnos unos a otros como Cristo y Su Iglesia nos enseñan. ¿Puede decirme adónde irá el dinero?";
				link.l1.go = "donation";
				link.l2 = "Perdóname, padre, pero ahora mismo estoy más pobre que una rata de iglesia.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
				DeleteAttribute(npchar, "talker"); // снимаем говорилку
				break;
			}
			bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Monkpassenger") && 7 - sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && 7 - sti(RealShips[sti(Pchar.Ship.Type)].Class) < 3) // монах-пассажир
			{
				dialog.text = "Buen día para ti, hijo mío. Me gustaría pedirte un favor. Pagaré, por supuesto.";
				link.l1 = "Te escucho, padre. ¿Qué necesitas?";
				link.l1.go = "passenger";
				link.l2 = "Lo siento mucho, padre, pero tengo que irme.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
				DeleteAttribute(npchar, "talker"); // снимаем говорилку
				break;
			}
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.capellan") && !CheckAttribute(pchar, "questTemp.ShipCapellan")) // корабельный капеллан
			{
				dialog.text = "Saludos, hijo mío. Supongo que eres capitán. Así que tengo una propuesta para ti.";
				link.l1 = "Estoy escuchando, padre.";
				link.l1.go = "capellan";
				npchar.quest.meeting = "1";
				DeleteAttribute(npchar, "talker"); // снимаем говорилку
				break;
			}
			dialog.text = PCharRepPhrase(LinkRandPhrase("Saludos, hijo mío. ¿Qué te aflige?", "Saludos, hijo mío. Ve al pastor si quieres confesarte.", "Saludos, hijo mío. 'Acuérdate de tu Creador en los días de tu juventud.'"), LinkRandPhrase("Saludos, hijo mío. ¿Qué te aflige?", "¡Buen día para ti, hijo mío, que Dios te bendiga!", "¡Buen día para ti, hijo mío, que el rostro de Dios brille sobre ti!"));
			link.l1 = LinkRandPhrase("Lo mismo para usted, padre. ¿Cómo le va?", "Buen día, padre. ¿Cómo está su parroquia?", "¿Cómo está, padre?");
			link.l1.go = "check"; // на возможную выдачу квестов
			link.l2 = RandPhraseSimple("Tengo una pregunta para usted, padre.", "Necesito información.");
			link.l2.go = "quests"; //(перессылка в файл города)
			if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES) * 10)
			{
				link.l3 = "Padre, tengo gente en mi barco. Son esclavos, tanto cristianos como paganos no bautizados. Quiero que bautices a los paganos y administres la comunión a los cristianos. Después, los liberaré a todos para la gloria de Dios y de nuestra Iglesia.";
				link.l3.go = "slaves";
			}
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7 - sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
			{
				link.l4 = "Padre, quiero que bendiga mi barco y ofrezca misa para mi tripulación. ¿Cuánto costaría eso?";
				link.l4.go = "shipshine";
			}
			link.l10 = LinkRandPhrase("Perdón, padre, pero tengo que irme.", "Perdón por molestarte, padre.", "Necesito regresar a mi barco, padre. ¡Adiós!");
			link.l10.go = "exit";
			npchar.quest.meeting = "1";
		}
		else
		{
			//--> диалог второй встречи
			dialog.text = LinkRandPhrase("¿Tú otra vez, hijo mío? ¿Qué deseas?", "¿Tienes algo más que contarme, hijo mío?", "Es bueno verte de nuevo, hijo mío.");
			link.l1 = LinkRandPhrase("Lo mismo para usted, padre. ¿Cómo está?", "Buen día para usted, padre. ¿Cómo está su parroquia?", "¿Cómo está, padre?");
			link.l1.go = "check"; // на возможную выдачу квестов
			link.l2 = RandPhraseSimple("Tengo una pregunta para usted, padre.", "Necesito información.");
			link.l2.go = "quests"; //(перессылка в файл города)
			if (GetSquadronGoods(pchar, GOOD_SLAVES) > 0 && sti(pchar.money) >= GetSquadronGoods(pchar, GOOD_SLAVES) * 10 && !CheckAttribute(npchar, "quest.slaves"))
			{
				link.l3 = "Padre, tengo personas en mi barco. Son esclavos, tanto cristianos como paganos no bautizados. Quiero que bautices a los paganos y administres la comunión a los cristianos. Después los liberaré a todos para la gloria de Dios y nuestra Iglesia.";
				link.l3.go = "slaves";
			}
			if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && sti(pchar.reputation.nobility) > 41 && !CheckAttribute(pchar, "GenQuest.Shipshine") && 7 - sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0)
			{
				link.l4 = "Padre, quiero que bendigas mi barco y ofrezcas misa por mi tripulación. ¿Cuánto costaría eso?";
				link.l4.go = "shipshine";
			}
			link.l10 = LinkRandPhrase("Perdón, padre, pero tengo que irme.", "Lamento molestarlo, padre.", "Necesito ir a mi barco, padre. ¡Adiós!");
			link.l10.go = "exit";
		}
		NextDiag.TempNode = "First time";
		break;

	case "check":
		if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) < 3 && !CheckAttribute(npchar, "quest.monkletter") && !CheckAttribute(pchar, "GenQuest.Monkletter") && !CheckAttribute(npchar, "quest.passenger")) // церковная депеша
		{
			pchar.GenQuest.Monkletter.City = FindFriendCityToMC(false);
			pchar.GenQuest.Monkletter.StartCity = npchar.city; // город квестодателя
			dialog.text = "Tengo un asunto urgente para ti, hijo mío. Necesito entregar estos documentos al pastor de  " + XI_ConvertString("Colony" + pchar.GenQuest.Monkletter.City + "Gen") + ". ¿Navegas en esa dirección? Los documentos deben ser entregados en dos semanas...";
			link.l1 = "Fácil, padre. Dame esos papeles y los entregaré a " + XI_ConvertString("Colony" + pchar.GenQuest.Monkletter.City + "Gen") + ".";
			link.l1.go = "Monkletter";
			link.l2 = "Me alegraría hacerlo, padre, pero estoy navegando en otra dirección.";
			link.l2.go = "exit_monkletter";
			npchar.quest.monkletter = "true";
			break;
		}
		if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && rand(8) > 5 && sti(pchar.rank < 11) && !CheckAttribute(npchar, "quest.churchbooks") && !CheckAttribute(pchar, "GenQuest.Churchbooks") && !CheckAttribute(npchar, "quest.passenger")) // привезти молитвенники
		{
			pchar.GenQuest.Churchbooks.StartCity = npchar.city; // город квестодателя
			pchar.GenQuest.Churchbooks.Nation = npchar.nation;
			dialog.text = "Hijo mío, ¿estarías dispuesto a ayudarme en un asunto urgente? Nuestra iglesia se está quedando sin Biblias y libros de oraciones que damos a todos los que los necesitan\n¿Podrías navegar hasta la colonia más cercana " + NationNameGenitive(sti(npchar.nation)) + ", recoger algunas Biblias y libros de oraciones de la iglesia y traerlos aquí? Y trata de hacerlo en un mes, no nos quedan muchos.";
			link.l1 = "Con gusto ayudaré a tu iglesia. ¿Puedo obtener estos libros de cualquier pastor?";
			link.l1.go = "Churchbooks";
			link.l2 = "Me alegraría hacerlo, padre, pero no puedo hacerlo ahora.";
			link.l2.go = "exit_churchbooks";
			npchar.quest.churchbooks = "true";
			break;
		}

		dialog.text = RandPhraseSimple("Está bien, hijo mío. Gracias por tus amables palabras.", "Nuestra parroquia está bien, hijo mío. Gracias por tus preocupaciones.");
		link.l1 = "Tengo que irme entonces, padre.";
		link.l1.go = "exit";
		break;

		//-------------------------------------------------пожертвования------------------------------------------------
	case "donation":
		sTemp = DonationType();
		dialog.text = "Claro, hijo mío. " + sTemp + "";
		link.l1 = "¿Qué donación se consideraría suficiente?";
		link.l1.go = "donation_1";
		break;

	case "donation_1":
		dialog.text = "Todo depende de tu bolsa y tu deseo personal, hijo mío. 'Dios ama al dador alegre.' Estamos profundamente agradecidos por cualquier donación.";
		link.l1 = "100 pesos";
		link.l1.go = "donation_rate_1";
		link.l2 = "1000 pesos";
		link.l2.go = "donation_rate_2";
		link.l3 = "5000 pesos";
		link.l3.go = "donation_rate_3";
		link.l4 = "10000 pesos";
		link.l4.go = "donation_rate_4";
		break;

	case "donation_rate_1": // никаких плюшек
		if (sti(pchar.money) >= 100)
		{
			AddMoneyToCharacter(pchar, -100);
			dialog.text = "¡Gracias por las monedas, hijo mío! ¡Serán destinadas a una buena causa!";
			link.l1 = "De nada, santo padre.";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "'No os engañéis, Dios no puede ser burlado. Porque lo que el hombre sembrare, eso también segará. Porque el que siembra para su carne, de la carne segará corrupción. Pero el que siembra para el espíritu, del espíritu segará vida eterna.'";
			link.l1 = "¡Ja, ja! Guarda el sermón, no hago caridad. ¡Piérdete!";
			link.l1.go = "donation_exit";
		}
		break;

	case "donation_rate_2":
		if (sti(pchar.money) >= 1000)
		{
			AddMoneyToCharacter(pchar, -1000);
			dialog.text = "Te agradezco, hijo mío. Esta suma realmente ayudará a nuestra misión parroquial. ¡Dios te bendiga!";
			link.l1 = "¡Buena suerte, padre!";
			link.l1.go = "exit";
			AddCharacterHealth(pchar, 5);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddCrewMorale(pchar, 2);
		}
		else
		{
			dialog.text = "¡La retribución de Dios te espera, bribón! ¡Burlarse de un siervo de la santa iglesia de Cristo es una blasfemia!";
			link.l1 = "¡Ja, ja! No hago caridad. ¡Piérdete!";
			link.l1.go = "donation_exit";
		}
		break;

	case "donation_rate_3":
		if (sti(pchar.money) >= 5000)
		{
			AddMoneyToCharacter(pchar, -5000);
			dialog.text = "¡Ni siquiera podía imaginar que serías tan generoso, hijo mío! ¡Te mencionaré en mi próxima carta a nuestro obispo y rezaremos por ti todos los días! ¡Te bendigo y acepto tu dinero con gratitud!";
			link.l1 = "¡El dinero no es nada a menos que se use para el propósito de Dios! ¡Buena suerte, padre!";
			link.l1.go = "exit";
			AddCharacterHealth(pchar, 5);
			AddCharacterExpToSkill(pchar, "Leadership", 40);
			AddCrewMorale(pchar, 3);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
		}
		else
		{
			dialog.text = "¡La retribución de Dios te espera, bribón! ¡Burlarse de un siervo de la santa iglesia de Cristo es una blasfemia!";
			link.l1 = "¡Ja, ja! No hago caridad. ¡Piérdete!";
			link.l1.go = "donation_exit";
		}
		break;

	case "donation_rate_4":
		if (sti(pchar.money) >= 10000)
		{
			AddMoneyToCharacter(pchar, -10000);
			dialog.text = "¿Qué... Te he oído bien? ¿Realmente donarás diez mil pesos? ¡Te bendigo y acepto tu dinero con gratitud! Te mencionaré en mi próxima carta a nuestro obispo y rezaremos por ti todos los días. ¡Es una gran ayuda para la Iglesia!";
			link.l1 = "'A quien mucho se le da, mucho se le exige,' ¿verdad? Buena suerte, santo padre.";
			link.l1.go = "exit";
			AddCharacterHealth(pchar, 10);
			AddCharacterExpToSkill(pchar, "Leadership", 60);
			AddCrewMorale(pchar, 5);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 2);
			ChangeCrewExp(pchar, "Sailors", 5);
			ChangeCrewExp(pchar, "Cannoners", 5);
			ChangeCrewExp(pchar, "Soldiers", 5);
		}
		else
		{
			dialog.text = "¡La retribución de Dios te espera, bellaco! ¡Burlarse de un siervo de la santa iglesia de Cristo es una blasfemia!";
			link.l1 = "¡Ja, ja! No hago obras de caridad. ¡Lárgate!";
			link.l1.go = "donation_exit";
		}
		break;

	case "donation_exit":
		DialogExit();
		ChangeCharacterComplexReputation(pchar, "nobility", -1);
		AddCharacterHealth(pchar, -5);
		LAi_CharacterDisableDialog(npchar);
		break;

		//-------------------------------------------отпустить рабов---------------------------------------------------
	case "slaves":
		dialog.text = "Por supuesto, hijo mío. Es nuestro deber sagrado ayudar a estas pobres almas miserables. Haré lo que me pides.";
		link.l1 = "Gracias, padre. Donaré diez piezas de a ocho por cada prisionero bautizado y administrado.";
		link.l1.go = "slaves_1";
		break;

	case "slaves_1":
		AddMoneyToCharacter(pchar, -GetSquadronGoods(pchar, GOOD_SLAVES) * 10);
		dialog.text = "Aunque no es necesario, acepto con gratitud tu tarifa por la estola. Tu dinero se destinará a diversas misiones en nuestra parroquia. ¿Podrías guiarme hasta tu barco?";
		link.l1 = "Sí, padre. Sígueme.";
		link.l1.go = "slaves_2";
		break;

	case "slaves_2":
		npchar.quest.slaves = "true";
		DialogExit();
		SetLaunchFrameFormParam("Dos horas después " + NewStr() + ". Han liberado a los esclavos.", "Monk_RemoveSlaves", 0, 4);
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 2, 10); // крутим время
		RecalculateJumpTable();
		break;
		//<-- отпустить рабов

		//----------------------------------------------освятить корабль------------------------------------------------
	case "shipshine":
		// поиск старшего класса
		iTemp = 7;
		for (i = 0; i < COMPANION_MAX; i++)
		{
			int iIdx = GetCompanionIndex(GetMainCharacter(), i);
			if (iIdx >= 0)
			{
				sld = GetCharacter(iIdx);
				if (GetCharacterShipClass(sld) < iTemp)
					iTemp = GetCharacterShipClass(sld);
			}
		}
		switch (GetCompanionQuantity(pchar))
		{
		case 1:
			sTemp = "Sólo tengo un barco en mi escuadrón y es " + iTemp + " rango.";
			pchar.GenQuest.Shipshine.Money = 5000 * (7 - iTemp);
			break;
		case 2:
			sTemp = "Tengo dos barcos en mi escuadrón y el más grande es " + iTemp + " rango.";
			pchar.GenQuest.Shipshine.Money = makeint(1.8 * (5000 * (7 - iTemp)));
			break;
		case 3:
			sTemp = "Tengo tres barcos en mi escuadrón y el más grande es " + iTemp + " rango.";
			pchar.GenQuest.Shipshine.Money = makeint(2.6 * (5000 * (7 - iTemp)));
			break;
		case 4:
			sTemp = "Tengo cuatro barcos en mi escuadrón y el más grande es " + iTemp + " rango.";
			pchar.GenQuest.Shipshine.Money = makeint(3.4 * (5000 * (7 - iTemp)));
			break;
		case 5:
			sTemp = "Tengo cinco barcos en mi escuadrón y el más grande es " + iTemp + " rango.";
			pchar.GenQuest.Shipshine.Money = makeint(4.2 * (5000 * (7 - iTemp)));
			break;
		}
		dialog.text = "Todo depende de la cantidad total de barcos en tu escuadrón y su tamaño.";
		link.l1 = "" + sTemp + " ";
		link.l1.go = "shipshine_1";
		break;

	case "shipshine_1":
		dialog.text = "Te costará " + FindRussianMoneyString(sti(pchar.GenQuest.Shipshine.Money)) + ", hijo mío.";
		if (sti(pchar.money) >= sti(pchar.GenQuest.Shipshine.Money))
		{
			link.l1 = "Puedo pagarle esta suma, padre. Tome el dinero.";
			link.l1.go = "shipshine_2";
		}
		link.l2 = "Desafortunadamente, no llevo tanto dinero conmigo.";
		link.l2.go = "shipshine_exit";
		break;

	case "shipshine_2":
		AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Shipshine.Money));
		dialog.text = "Muy bien, hijo mío. Déjame recoger los vasos sagrados y nos dirigiremos al puerto.";
		link.l1 = "Sígueme, padre.";
		link.l1.go = "shipshine_3";
		break;

	case "shipshine_3":
		DialogExit();
		SetLaunchFrameFormParam("Varias horas después" + NewStr() + "El sacerdote ha ordenado una misa en tu barco y lo ha bendecido...", "Monk_Shipshine", 0, 4);
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, GetCompanionQuantity(pchar), 10); // крутим время
		RecalculateJumpTable();
		break;

	case "shipshine_exit":
		DialogExit();
		DeleteAttribute(Pchar, "GenQuest.Shipshine");
		break;
		//<-- освятить корабль

		//------------------------------------------корабельный капеллан-----------------------------------------------
	case "capellan":
		dialog.text = "Hola capitán, permítame presentarme. Soy un sacerdote y tengo bastante experiencia como capellán a bordo de buques de guerra. Dejé mi último barco porque el capitán y yo tuvimos algunos... desacuerdos morales. ¿Quiere que me una a su tripulación?";
		link.l1 = "¿Un sacerdote a bordo? Dime, padre, ¿qué hace un capellán de barco?";
		link.l1.go = "capellan_1";
		pchar.questTemp.ShipCapellan = "true";
		break;

	case "capellan_1":
		dialog.text = "Pues, es bastante obvio. Rezo a Dios por ti y tu tripulación, celebro misa diariamente, y bendigo a tus hombres y escucho confesiones antes de la batalla. La palabra de Dios otorga fuerza a las manos y espíritus de tu tripulación. Tu tripulación tendrá la oportunidad de recibir la comunión y confesión de manera regular. Créeme, un marinero en estado de gracia se mantendrá firme en situaciones donde uno impío se acobardará\nNo pido mucho para mí: un pago único de cincuenta mil pesos para mi parroquia natal, una simple litera en un camarote y una comida igual a la de tus oficiales. Eso sería todo.";
		if (sti(pchar.money) >= 50000)
		{
			link.l1 = "Interesante... Tienes razón, un buen capitán debe preocuparse no solo por los cuerpos de su tripulación, sino también por sus almas. ¡Bienvenido a bordo, padre!";
			link.l1.go = "capellan_2";
		}
		link.l2 = "No, padre. Lo siento, pero no puedo pagar por tus servicios.";
		link.l2.go = "capellan_exit";
		break;

	case "capellan_exit":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		break;

	case "capellan_2":
		AddMoneyToCharacter(pchar, -50000);
		chrDisableReloadToLocation = true; // закрыть локацию
		dialog.text = "Gracias por tu confianza, hijo mío. Has gastado tu dinero sabiamente. Pero te advierto, solo sirvo a capitanes dignos, ya sea comerciante o corsario, no importa. ¡Pero nunca predicaré a bordo de un barco pirata!\nAsí que si alguna vez izas la bandera negra del diablo, dejaré tu navío de inmediato en el primer puerto.";
		link.l1 = "Lo consideraré, padre, y trataré de no decepcionarte. ¡Por favor, sube a bordo y preséntate a la tripulación!";
		link.l1.go = "capellan_3";
		break;

	case "capellan_3":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "My_Campus", "rld", "loc1", "Monk_Capellan", -1);
		pchar.questTemp.ShipCapellan.id = npchar.id;
		DeleteAttribute(npchar, "LifeDay");
		DeleteAttribute(npchar, "CityType"); // удалить признак фантома
		AddPassenger(pchar, npchar, false);
		SetCharacterRemovable(npchar, false);
		pchar.questTemp.ShipCapellan.Yes = "true"; // капеллан в команде
		Achievment_Set("ach_69");
		ChangeCharacterComplexReputation(pchar, "authority", 5);
		npchar.reputation = 60;
		break;

	case "capellan_4":
		dialog.text = "¿Necesitas algo, hijo mío?";
		link.l1 = "No, no es nada, padre.";
		link.l1.go = "exit";
		link.l2 = "Padre, me gustaría que abandonaras el barco en el próximo puerto. No me explicaré más.";
		link.l2.go = "capellan_5";
		NextDiag.TempNode = "capellan_4";
		break;

	case "capellan_5":
		dialog.text = "Muy bien, hijo mío. Estás a cargo aquí. Dejaré tu barco en el próximo asentamiento.";
		link.l1 = "Gracias por su comprensión, padre.";
		link.l1.go = "capellan_6";
		break;

	case "capellan_6":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		ShipCapellan_Remove();
		break;

	case "capellan_7":
		dialog.text = "¡Ay, capitán! Te advertí que te dejaría si izas la bandera pirata. Dejo tu barco en el próximo puerto. Rezaré por tu inmediato arrepentimiento y regreso al redil de la Santa Madre Iglesia.";
		link.l1 = "Pues maldita sea...";
		link.l1.go = "exit";
		NextDiag.TempNode = "capellan_7";
		break;
		//<-- капеллан

		//--------------------------------------------монах-пассажир---------------------------------------------------
	case "passenger":
		if (hrand(19) < 15)
			SetPassengerParameter("Monkpassenger", false);
		else
			SetPassengerParameter("Monkpassenger", true);
		if (!CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity"))
		{
			dialog.text = "Mi " + GetSexPhrase("hijo", "hija") + ", tengo que llegar a " + XI_ConvertString("Colony" + pchar.GenQuest.Monkpassenger.City) + " está encendido " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City) + "Dat") + ", en el plazo de " + FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty)) + ". Te pagaré " + FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money)) + " para eso. ¿Qué dices?";
		}
		else
		{
			dialog.text = "Mi " + GetSexPhrase("hijo", "hija") + ", el Señor se mueve de maneras misteriosas, y por eso busco un capitán confiable. ¿Puedes ayudarme a llegar a " + XI_ConvertString("Colony" + pchar.GenQuest.Monkpassenger.City) + ", que está en " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City) + "Dat") + "¿Entiendo que es como un viaje al ardiente Gehena, ya que nuestros enemigos nunca duermen? Y entiendo que no eres Jesucristo, pero yo tampoco soy un apóstol, y por lo tanto tengo algunos ahorros. ¿Lo harás " + FindRussianDublonString(sti(pchar.GenQuest.Monkpassenger.Money)) + " ¿será suficiente para ti?";
		}
		link.l1 = "Estoy de acuerdo, padre.";
		link.l1.go = "passenger_1";
		link.l2 = "Lo siento, padre, pero navego en una dirección diferente. No puedo ayudarte.";
		link.l2.go = "passenger_exit";
		npchar.quest.passenger = true;
		break;

	case "passenger_exit":
		dialog.text = "Es la voluntad de Dios para todos, hijo mío. Esperaré otro barco. ¡La paz sea contigo!";
		link.l1 = "Adiós, padre.";
		link.l1.go = "exit";
		DeleteAttribute(pchar, "GenQuest.Monkpassenger");
		break;

	case "passenger_1":
		dialog.text = "¡Dios te bendiga! Recibirás tu pago cuando lleguemos a nuestro destino.";
		link.l1 = "Dirígete a mi barco, padre. Nos vamos pronto.";
		link.l1.go = "passenger_2";
		break;

	case "passenger_2":
		DialogExit();
		pchar.GenQuest.Monkpassenger.id = npchar.id;
		DeleteAttribute(npchar, "LifeDay");
		LAi_RemoveLoginTime(npchar);
		DeleteAttribute(npchar, "CityType"); // удалить признак фантома, иначе - пустые города
		LAi_SetImmortal(npchar, true);
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
		AddPassenger(pchar, npchar, false);
		SetCharacterRemovable(npchar, false);
		sTitle = npchar.index + "Citizpassenger";

		// LDH 13Sep17 - do not add to an existing Citizpassenger record -->
		// "Rename" the quest record by copying it to a new name and deleting the old record
		if (CheckAttribute(pchar, "questinfo." + sTitle))
		{
			string sTempLDH = frand(1);
			sTempLDH = strcut(sTempLDH, 2, 5); // 4 random digits
			string sTitle1 = sTitle + sTempLDH;

			aref arTo, arFrom;
			makearef(arFrom, pchar.questinfo.(sTitle));
			makearef(arTo, pchar.questinfo.(sTitle1));
			CopyAttributes(arTo, arFrom);
			pchar.questinfo.(sTitle1) = "";

			DeleteAttribute(pchar, "questinfo." + sTitle);

			Trace("Duplicate Citizpassenger record " + sTitle + " copied to " + sTitle1 + " **");
		}
		// <--

		AddQuestRecordEx(sTitle, "Citizpassenger", "1");
		AddQuestUserDataForTitle(sTitle, "sType", "monk");
		AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
		sTemp = XI_ConvertString("Colony" + pchar.GenQuest.Monkpassenger.City + "Gen") + ", que está en " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Monkpassenger.City) + "Voc") + "."; // belamour gen
		AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
		AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		AddQuestUserData(sTitle, "sCity", sTemp);
		AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Monkpassenger.DaysQty)));
		AddQuestUserData(sTitle, "sSex", GetSexPhrase("", ""));
		if (!CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity"))
			AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Monkpassenger.Money)));
		else
			AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Monkpassenger.Money)));
		AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		pchar.quest.Monkpassenger.win_condition.l1 = "location";
		pchar.quest.Monkpassenger.win_condition.l1.location = pchar.GenQuest.Monkpassenger.City + "_town";
		pchar.quest.Monkpassenger.function = "Monkpassenger_complete";
		SetFunctionTimerCondition("Monkpassenger_Over", 0, 0, sti(pchar.GenQuest.Monkpassenger.DaysQty), false);
		break;

	case "passenger_3":
		pchar.quest.Monkpassenger_Over.over = "yes"; // снять таймер
		dialog.text = "Gracias, mi " + GetSexPhrase("hijo", "hija") + "Has cumplido tu promesa y ahora es mi turno. Toma tu dinero como te prometí.";
		link.l1 = "Gracias. Buena suerte, padre.";
		link.l1.go = "passenger_4";
		break;

	case "passenger_4":
		DialogExit();
		npchar.lifeday = 0;
		RemovePassenger(Pchar, npchar);
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 20.0);
		ChangeCharacterComplexReputation(pchar, "nobility", 1);
		ChangeCharacterComplexReputation(pchar, "fame", 1);
		OfficersReaction("good");
		AddCharacterExpToSkill(pchar, "Sailing", 80);
		AddCharacterExpToSkill(pchar, "Leadership", 20);
		if (CheckAttribute(pchar, "GenQuest.Monkpassenger.Enemycity"))
		{
			AddCharacterExpToSkill(pchar, "Sneak", 50);
			TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Monkpassenger.Money));
		}
		else
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Monkpassenger.Money));
		sTitle = npchar.index + "Citizpassenger";
		AddQuestRecordEx(sTitle, "Citizpassenger", "3");
		CloseQuestHeader(sTitle);
		DeleteAttribute(Pchar, "GenQuest.Monkpassenger");
		break;
		//<-- монах-пассажир

		//---------------------------------------------церковная депеша-------------------------------------------------
	case "exit_monkletter":
		DialogExit();
		DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;

	case "Monkletter":
		dialog.text = "Aquí. Toma este paquete, hijo mío. Recuerda que tienes solo dos semanas para entregarlo. El pastor lo está esperando. ¡Ve, y que Dios te acompañe!";
		link.l1 = "No te fallaré, padre. Adiós.";
		link.l1.go = "Monkletter_1";
		break;

	case "Monkletter_1":
		DialogExit();
		GiveItem2Character(pchar, "letter_church");
		ReOpenQuestHeader("Monkletter");
		AddQuestRecord("Monkletter", "1");
		AddQuestUserData("Monkletter", "sSex1", GetSexPhrase("", ""));
		AddQuestUserData("Monkletter", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Monkletter.City + "Gen"));
		AddQuestUserData("Monkletter", "sStartCity", XI_ConvertString("Colony" + pchar.GenQuest.Monkletter.StartCity));
		SetFunctionTimerCondition("Monkletter_Over", 0, 0, 15, false);
		OfficersReaction("good");
		break;
		//<-- Церковная депеша

		//-------------------------------------------доставить молитвенники---------------------------------------------
	case "exit_churchbooks":
		DialogExit();
		DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;

	case "Churchbooks":
		dialog.text = "Sí. Puedes conseguirlos en cualquier colonia " + NationNameGenitive(sti(npchar.nation)) + ". Trae todos los libros que encuentres a nuestro párroco en la iglesia. ¡Que Dios te bendiga!";
		link.l1 = "¡Gracias! Recibirás tus libros pronto.";
		link.l1.go = "Churchbooks_1";
		break;

	case "Churchbooks_1":
		DialogExit();
		ReOpenQuestHeader("Churchbooks");
		AddQuestRecord("Churchbooks", "1");
		AddQuestUserData("Churchbooks", "sNation", NationNameGenitive(sti(pchar.GenQuest.Churchbooks.Nation)));
		AddQuestUserData("Churchbooks", "sStartCity", XI_ConvertString("Colony" + pchar.GenQuest.Churchbooks.StartCity));
		SetFunctionTimerCondition("Churchbooks_Over", 0, 0, 30, false);
		pchar.GenQuest.Churchbooks = "go";
		switch (rand(4))
		{
		case 0:
			pchar.GenQuest.Churchbooks.Item = "amulet_2";
			break;
		case 1:
			pchar.GenQuest.Churchbooks.Item = "amulet_3";
			break;
		case 2:
			pchar.GenQuest.Churchbooks.Item = "amulet_6";
			break;
		case 3:
			pchar.GenQuest.Churchbooks.Item = "amulet_7";
			break;
		case 4:
			pchar.GenQuest.Churchbooks.Item = "amulet_10";
			break;
		}
		OfficersReaction("good");
		break;
		//<-- доставить молитвенники

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}

string DonationType()
{
	string sText;
	switch (hrand(9))
	{
	case 0:
		sText = "Estoy reuniendo dinero para construir " + LinkRandPhrase("una capilla", "una casa de beneficencia", "un hospital") + ". Los ciudadanos locales dan poca limosna, así que debo pedir a hombres prósperos como tú." break;
	case 1:
		sText = "Estoy recogiendo donaciones para nuestra iglesia. Los marineros no suelen tener mucho tiempo para visitar la casa de Dios, pero cada uno debe hacer lo posible por salvar su propia alma." break;
	case 2:
		sText = "Estoy reuniendo dinero para comprar alimentos y medicinas para nuestro asilo de enfermos, viudas, huérfanos y enfermos. Por favor done señor, porque allá pero por la gracia de Dios vamos todos nosotros." break;
	case 3:
		sText = "Estoy reuniendo dinero para nuevos vasos sagrados, los que trajimos de Europa están maltrechos por el uso continuo. Es un deber de todo cristiano cuidar de nuestra Iglesia." break;
	case 4:
		sText = "Estoy reuniendo dinero para la renovación de nuestra iglesia, el tejado tiene unas goteras terribles y también hay que reparar los bancos. Es un deber de todo cristiano cuidar de nuestra Iglesia." break;
	case 5:
		sText = "Estoy reuniendo dinero para pagar al buen artista que es capaz de pintar las paredes de nuestra iglesia y dibujar en ellas escenas de la Biblia para aquellos de nuestra parroquia que no saben leer. Es un deber de todo cristiano cuidar de su Iglesia." break;
	case 6:
		sText = "Estoy reuniendo dinero para un nuevo altar mayor para nuestra iglesia. Nuestra parroquia es pobre y nos gustaría tener una sede noble para el Santísimo Sacramento. Espero su ayuda." break;
	case 7:
		sText = "Hay muchos marineros heridos de los ataques piratas en nuestro hospital. Necesitan medicinas y vendas. Por favor, ayúdenles, porque ustedes pueden entender realmente los sufrimientos de los marineros comunes." break;
	case 8:
		sText = "Intento conseguir dinero para ropa y comida para nuestros ciudadanos más pobres. La única esperanza que tienen es nuestra santa iglesia. Por favor, ayúdenles." break;
	case 9:
		sText = "Voy a adentrarme en nuestra isla para realizar una labor misionera y llevar la luz del Evangelio de Cristo a las almas perdidas de los indios paganos. Estoy reuniendo fondos para esta expedición. Por favor, ¡ayuden a nuestra buena obra!" break;
	}
	return sText;
}
