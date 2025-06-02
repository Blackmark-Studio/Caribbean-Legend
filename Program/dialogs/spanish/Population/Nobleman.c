// Jason общий диалог дворян
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int iTemp, iTest;
	string sTemp, sTitle;
	float locx, locy, locz;

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

	iTest = FindColony(NPChar.City); // 170712
	ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}

	switch (Dialog.CurrentNode)
	{
	case "First time":
		//--> проверка межнациональных отношений
		if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
		{
			dialog.text = NPCStringReactionRepeat("Hm. Navegáis bajo la bandera de " + NationNameGenitive(sti(pchar.nation)) + ", camarada. ¿Qué diablos haces aquí, en nuestra ciudad? ¡Piérdete!", "No quiero ser sospechoso de ser amigo de " + NationNameAblative(sti(pchar.nation)) + "¡Lárgate o informaré a los guardias!", "Es tu última oportunidad para escapar. De lo contrario, solo tendrás a ti mismo para culpar.", "Te he advertido. ¡Ahora pagarás por tu insolencia, bastardo!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("¡Vaya patriota, ja!", "Está bien, está bien, cálmate. Me voy.", "No hagas tanto ruido. Me voy.", "¿Qué?!", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
		}

		//--> проверка репутации - дворяне гнобят супернегодяев
		if (sti(pchar.reputation.nobility) < 10)
		{
			dialog.text = NPCStringReactionRepeat("¡Mira eso! ¿Y cómo es que nuestros guardias permiten que un bastardo como tú simplemente ande por la ciudad? Imposible...", "¡Piérdete, ni siquiera quiero hablar contigo! ¡Verdugo...", "Es tu última oportunidad para escapar. De lo contrario, solo te tendrás a ti mismo para culpar.", "Te he advertido. ¡Ahora pagarás por tu insolencia, bastardo!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("¡Eh, eh! ¡Muéstrame más respeto, señor!", "Mírate a ti mismo, santo...", "Calma...", "¿Qué?!", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
			break;
		}

		//--> диалог первой встречи
		if (NPChar.quest.meeting == "0")
		{
			// проверка наличия корабля в порту
			bool ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
			if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Noblepassenger") && CheckAttribute(pchar, "questTemp.StatusCity") && pchar.questTemp.StatusCity == npchar.city) // дворянин-пассажир
			{
				dialog.text = "Saludos, " + GetAddress_Form(NPChar) + ". Veo que eres capitán de un sólido barco. Quiero pedirte que hagas algo. Puedes aceptarlo o dejarlo.";
				link.l1 = "Estoy escuchando, " + GetAddress_FormToNPC(NPChar) + "¿Qué quieres decir?";
				link.l1.go = "passenger";
				link.l2 = "Perdóneme, " + GetAddress_FormToNPC(NPChar) + ", pero tengo prisa.";
				link.l2.go = "exit";
				npchar.quest.meeting = "1";
				DeleteAttribute(npchar, "talker"); // снимаем говорилку
				break;
			}
			if (ok && sti(Pchar.Ship.Type) != SHIP_NOTUSED && CheckAttribute(npchar, "quest.passenger") && !CheckAttribute(pchar, "GenQuest.Noblepassenger") && 4-sti(RealShips[sti(Pchar.Ship.Type)].Class) > 0 && or(IsUniversalShipType(pchar), IsMerchantShipType(pchar)))//дворянин-пассажир
			if (CheckAttribute(npchar, "quest.donation")) // клянчит деньги
			{
				dialog.text = "¡Ahá, es bueno ver a un caballero en nuestra pequeña ciudad! Estoy seguro de que vienes directo de Europa. Escucha, quiero pedirte que me ayudes, de caballero a caballero. Espero que me entiendas correctamente.";
				link.l1 = "Buen día, señor. Estoy escuchando.";
				link.l1.go = "donation";
				npchar.quest.meeting = "1";
				break;
			}
			if (CheckAttribute(npchar, "quest.lombard") && !CheckAttribute(pchar, "GenQuest.Noblelombard")) // семейная реликвия
			{
				dialog.text = "Buen día, " + GetAddress_Form(NPChar) + "¡Es bueno encontrar a un caballero en las calles de nuestra ciudad! ¿Me permitirá tomarle unos minutos?";
				link.l1 = "Claro, señor. Estoy escuchando.";
				link.l1.go = "lombard";
				npchar.quest.meeting = "1";
				break;
			}
			if (CheckAttribute(npchar, "quest.slaves") && !CheckAttribute(&Colonies[FindColony(npchar.city)], "questslaves")) // привезти рабов
			{
				dialog.text = "¡Buen día, capitán! Me alegra verte porque pareces un hombre capaz de resolver problemas.";
				link.l1 = "Depende del problema. Me especializo en resolverlos con violencia. ¿Es eso lo que estás buscando, " + GetAddress_FormToNPC(NPChar) + "?";
				link.l1.go = "slaves";
				npchar.quest.meeting = "1";
				break;
			}
			dialog.text = RandPhraseSimple("Hola, " + GetAddress_Form(NPChar) + "¿Deseas algo de mí?", "¿Qué desea, señor?");
			link.l1 = TimeGreeting() + ", " + GetAddress_FormToNPC(NPChar) + ". No te quitaré mucho tiempo, solo quiero preguntar...";
			link.l1.go = "question";
			link.l2 = RandPhraseSimple("Necesito información sobre vuestra colonia.", "Necesito información.");
			link.l2.go = "quests"; //(перессылка в файл города)
			npchar.quest.meeting = "1";

			//==> прибыла инспекция на Святом Милосердии
			if (CheckAttribute(pchar, "questTemp.SantaMisericordia.ColonyZapret") && pchar.location == pchar.questTemp.SantaMisericordia.ColonyZapret + "_town")
			{
				dialog.Text = LinkRandPhrase(LinkRandPhrase("Toda la ciudad está en vilo... don Fernando de Alamida, el inspector real, ha llegado. Sabes, he visto mucho aquí, pero esto... No es el dolor lo que cambia a las personas, sino cómo lo manejan. Dicen que se convirtió en un hombre diferente después de la muerte de su padre. Ahora no encontrarás un servidor más incorruptible y... despiadado de la Corona en todo el Archipiélago.", "¡Solo mira el 'Santa Misericordia'! Dicen que el mismo rey ordenó construirlo según diseños especiales. Y fíjate, ni un solo rasguño. Como si la misma Virgen María lo protegiera. Aunque he oído rumores... tal vez no sea la Virgen en absoluto.", "¿Sabes cuántas veces han intentado matar a don Fernando? ¡Doce ataques en aguas abiertas, y eso solo en el último año! Bueno, con una tripulación tan leal y entrenada, y bajo la protección del Señor, ¡sobrevivirá al decimotercer ataque también!"), LinkRandPhrase("¿Has oído? Don Fernando de Alamida ha llegado a nuestra ciudad, y dicen que ahora mismo está por las calles. Me encantaría verlo con mis propios ojos...", "Un hombre complicado, este don Fernando. Algunos dicen que es un salvador, limpiando la Madre Patria de la escoria. Otros murmuran que algo se rompió en él después de la muerte de su padre y pronto todos estaremos llorando. Pero te diré esto: no le temas a él. Teme a aquellos que lo hicieron lo que es.", "¡Qué hombre tan apuesto, este don Fernando! ¿Pero sabes qué es extraño? Es como si no notara a nadie. Todo deber y servicio. Oí que había una chica... pero después de reunirse con algún sacerdote, rechazó por completo los placeres mundanos. Como si hubiera hecho un voto."), RandPhraseSimple(RandPhraseSimple("¡Maldito inspector! Mientras él esté aquí, la ciudad parece muerta. No hay comercio, no hay diversión. Incluso respirar, parece, debe ser más silencioso. ¿Y sabes qué es lo más aterrador? Es lo mismo en cada puerto. Como un reloj. ¡Su Majestad Real no podría haber inventado deliberadamente esta tortura para todos nosotros!", "Don Fernando visitó el orfanato de nuevo. Dona generosamente, reza durante horas. ¡Un hombre tan digno debería ser un ejemplo para esos malditos malversadores!"), RandPhraseSimple("¡Ja! El 'santo' Fernando cerró todos los burdeles otra vez. Bueno, no importa, pronto zarpará y los volverán a abrir.", "¡El insp... inspector ha llegado, eso es! ¡Don Fernando de Almeyda, o como se llame, Alamida! Tan importante que el mismo gobernador anda de puntillas a su alrededor. Dicen que te mira a los ojos y ve todos tus pecados de inmediato. ¡Aterrador!")));
				link.l1 = "...";
				link.l1.go = "exit";
				DeleteAttribute(link, "l2");
			}
			//<== прибыла инспекция на Святом Милосердии
			//==> Леди Бет в порту города
				if (CheckAttribute(pchar, "questTemp.LadyBeth.CaptainInColony") && pchar.location == pchar.questTemp.LadyBeth.CaptainInColony + "_town")
				{
					dialog.Text = findLedyBethRumour(npchar);
					link.l1 = "...";
					link.l1.go = "exit";
					DeleteAttribute(link, "l2");
				}
				//<== Леди Бет в порту города
		}
		else //--> повторные обращения
		{
			dialog.text = NPCStringReactionRepeat("¿Qué? ¿Otra vez? No tengo tiempo para ti. Busca a alguien más para hablar. Hay muchos plebeyos deambulando por las calles. Y tengo que irme, habrá un banquete esta noche en la residencia del gobernador y tengo que preparar mi atuendo...", "¡No, ahora es realmente molesto! ¿No lo entiendes? ¿O eres lento de mente?", "Señor, empiezo a sospechar que no solo es un idiota, sino también un patán y un grosero. Le advierto, déjeme en paz o se arrepentirá de molestarme.", "Basta. ¡Te enseñaré, insolente!", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ya veo. Adiós.", "Sí-sí, solo olvidé lo que quería preguntar...", "Me has entendido mal...", "¿Qué?!", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "fight", npchar, Dialog.CurrentNode);
		}
		NextDiag.TempNode = "First time";
		break;

	case "question":
		dialog.text = LinkRandPhrase("Continúa.", "¿Qué quieres?", "¿Preguntas? Bien, marinero, te escucho.");
		link.l1 = LinkRandPhrase("¿No me contarás los últimos chismes de tu pueblo?", "¿Ha ocurrido algo interesante aquí recientemente?", "¿Alguna novedad del Caribe, señor?");
		link.l1.go = "rumours_nobleman";
		NextDiag.TempNode = "First time";
		break;

		//--------------------------------------------дворянин-пассажир---------------------------------------------------
	case "passenger":
		if (hrand(19) > 9)
			SetPassengerParameter("Noblepassenger", false);
		else
			SetPassengerParameter("Noblepassenger", true);
		if (!CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity"))
		{
			dialog.text = "" + GetSexPhrase("Señor", "Señora") + ", necesito llegar a la colonia de " + XI_ConvertString("Colony" + pchar.GenQuest.Noblepassenger.City + "Acc") + ", tan pronto como sea posible que está en " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City) + "Voc") + ", en el plazo de " + FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty)) + ". Tu barco parece robusto y rápido en comparación con la mayoría de estas pequeñas bañeras que navegan aquí. Puedo pagarte " + FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money)) + "¿Qué dirías?"; // belamour gen
		}
		else
		{
			dialog.text = "Hola, " + GetSexPhrase("señor", "señora") + "¡Necesito llegar a " + XI_ConvertString("Colony" + pchar.GenQuest.Noblepassenger.City + "Acc") + "¡Eso está en " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City) + "Voc") + ", por cierto. Sí, sí, sé que esos bastardos están esperando a que aparezcamos allí. ¡Pero tengo una reunión muy urgente e importante allí! No soy una persona tacaña, aunque no me gusta pagar, siempre pago. Deja todo lo que estés haciendo, y tan pronto como lleguemos, te daré " + FindRussianDublonString(sti(pchar.GenQuest.Noblepassenger.Money)) + ".";
		}
		link.l1 = "Hum. Me dirijo a ese rumbo también, así que estoy listo para llevarte a bordo bajo estos términos.";
		link.l1.go = "passenger_1";
		link.l2 = "Lo siento, " + GetAddress_FormToNPC(NPChar) + ", pero estoy navegando en una dirección diferente. No puedo ayudarte.";
		link.l2.go = "passenger_exit";
		break;

	case "passenger_exit":
		dialog.text = "Qué lástima. Bueno, esperaré otro barco. Adiós.";
		link.l1 = "Nos vemos.";
		link.l1.go = "exit";
		DeleteAttribute(pchar, "GenQuest.Noblepassenger");
		break;

	case "passenger_1":
		dialog.text = "¡Genial! Estoy cansado de esperar. Recibirás tu pago cuando lleguemos allí.";
		link.l1 = "Ve a mi barco, " + GetAddress_FormToNPC(NPChar) + ". Nos vamos pronto.";
		link.l1.go = "passenger_2";
		break;

	case "passenger_2":
		DialogExit();
		pchar.GenQuest.Noblepassenger.id = npchar.id;
		LAi_SetImmortal(npchar, true);
		DeleteAttribute(npchar, "LifeDay");
		LAi_RemoveLoginTime(npchar);
		DeleteAttribute(npchar, "CityType"); // удалить признак фантома, иначе - пустые города
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
		AddQuestUserDataForTitle(sTitle, "sType", "noble");
		AddQuestUserDataForTitle(sTitle, "sName", GetFullName(npchar));
		sTemp = XI_ConvertString("Colony" + pchar.GenQuest.Noblepassenger.City + "Gen") + ", a " + XI_ConvertString(GetIslandByCityName(pchar.GenQuest.Noblepassenger.City) + "Dat") + ".";
		AddQuestUserDataForTitle(sTitle, "sCity", sTemp);
		AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		AddQuestUserData(sTitle, "sCity", sTemp);
		AddQuestUserData(sTitle, "sDays", FindRussianDaysString(sti(pchar.GenQuest.Noblepassenger.DaysQty)));
		AddQuestUserData(sTitle, "sSex", GetSexPhrase("", ""));
		if (!CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity"))
			AddQuestUserData(sTitle, "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Noblepassenger.Money)));
		else
			AddQuestUserData(sTitle, "sMoney", FindRussianDublonString(sti(pchar.GenQuest.Noblepassenger.Money)));
		AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		pchar.quest.Noblepassenger.win_condition.l1 = "location";
		pchar.quest.Noblepassenger.win_condition.l1.location = pchar.GenQuest.Noblepassenger.City + "_town";
		pchar.quest.Noblepassenger.function = "Noblepassenger_complete";
		SetFunctionTimerCondition("Noblepassenger_Over", 0, 0, sti(pchar.GenQuest.Noblepassenger.DaysQty), false);
		break;

	case "passenger_3":
		pchar.quest.Noblepassenger_Over.over = "yes"; // снять таймер
		dialog.text = "¡Aquí estamos, excelentísimo! Viajar en su barco fue bastante satisfactorio. ¡Tiene una tripulación disciplinada y cubiertas limpias! Mis gracias. Tome su dinero, señor.";
		link.l1 = "Buena suerte, " + GetAddress_FormToNPC(NPChar) + "¡Adiós!";
		link.l1.go = "passenger_4";
		break;

	case "passenger_4":
		chrDisableReloadToLocation = false; // открыть локацию
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
		if (CheckAttribute(pchar, "GenQuest.Noblepassenger.Enemycity"))
		{
			AddCharacterExpToSkill(pchar, "Sneak", 50);
			TakeNItems(pchar, "gold_dublon", sti(pchar.GenQuest.Noblepassenger.Money));
		}
		else
			AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Noblepassenger.Money));
		sTitle = npchar.index + "Citizpassenger";
		AddQuestRecordEx(sTitle, "Citizpassenger", "3");
		CloseQuestHeader(sTitle);
		DeleteAttribute(Pchar, "GenQuest.Noblepassenger");
		break;
		//<-- дворянин-пассажир

		//-------------------------------------------------помощь деньгами------------------------------------------------
	case "donation":
		sTemp = DonationText();
		dialog.text = "Tengo un negocio bastante delicado..." + sTemp + " Necesito dinero ahora o estaré en un gran apuro. Nunca pediría dinero a otro caballero normalmente, pero la situación es realmente mala.";
		link.l1 = "¿Cuánto necesitas?";
		link.l1.go = "donation_1";
		break;

	case "donation_1":
		iTemp = hrand(4) + 1;
		pchar.GenQuest.Nobledonation.Money = iTemp * 1000 + rand(iTemp) * 150;
		dialog.text = "La suma es bastante pequeña, es " + FindRussianMoneyString(sti(pchar.GenQuest.Nobledonation.Money)) + "¿Entonces qué, puedes ayudarme?";
		if (sti(pchar.money) >= sti(pchar.GenQuest.Nobledonation.Money))
		{
			link.l1 = "Sí, claro. Tómalo.";
			link.l1.go = "donation_2";
		}
		link.l2 = "Estaría encantado de ayudar, pero mis bolsillos también están vacíos, ni un solo peso de sobra.";
		link.l2.go = "donation_exit";
		break;

	case "donation_exit":
		DialogExit();
		ChangeOfficersLoyality("bad_all", 1);
		LAi_CharacterDisableDialog(npchar);
		npchar.lifeday = 0;
		DeleteAttribute(pchar, "GenQuest.Nobledonation");
		break;

	case "donation_2":
		AddMoneyToCharacter(pchar, -sti(pchar.GenQuest.Nobledonation.Money));
		dialog.text = "Mi gratitud, " + GetAddress_Form(NPChar) + "¡Me has salvado! Tengo amigos en la residencia del gobernador y les contaré sobre tu generosidad. ¡Mil gracias de nuevo!";
		link.l1 = "De nada, señor. Estoy seguro de que haría lo mismo por mí.";
		link.l1.go = "donation_3";
		break;

	case "donation_3":
		DialogExit();
		ChangeOfficersLoyality("good_all", rand(2) + 1);
		ChangeCharacterNationReputation(pchar, sti(npchar.Nation), rand(1) + 2);
		LAi_CharacterDisableDialog(npchar);
		npchar.lifeday = 0;
		DeleteAttribute(pchar, "GenQuest.Nobledonation");
		break;
		//<-- помощь деньгами

		//-------------------------------------------------семейная реликвия---------------------------------------------
	case "lombard":
		LombardText();
		dialog.text = "Necesito tu ayuda. Eres rico y un caballero, así que espero que lo entiendas. Tuve una gran necesidad de dinero no hace mucho tiempo, así que tuve que ir al banquero y empeñar " + pchar.GenQuest.Noblelombard.Item + "\nOfreció buenos términos. Diez por ciento por cada mes, tres meses en total. Pero el tiempo se ha agotado y no poseo dinero para redimir el objeto debido a un desafortunado giro de los acontecimientos.\nAhora dice que ha encontrado un comprador para " + pchar.GenQuest.Noblelombard.Item + "y lo va a vender si no pago mi deuda y los intereses de inmediato. Pero no tengo mucho dinero ahora, y el objeto que empeñé es muy caro...";
		link.l1 = "¿Y cómo puedo ayudarte con eso, " + GetAddress_FormToNPC(NPChar) + "?";
		link.l1.go = "lombard_1";
		break;

	case "lombard_1":
		dialog.text = "Te pido que hables con nuestro banquero. Ofrécele dinero, responde por mí... o haz otra cosa. Desafortunadamente, no tengo a quién pedir, todos mis buenos amigos de repente se han 'arruinado'. En tres meses " + pchar.GenQuest.Noblelombard.Text + ", y te devolveré todos tus gastos, ¡doblemente! ¡Tienes mi palabra de caballero!";
		link.l1 = "Bien, intentaré ayudarte en este caso.";
		link.l1.go = "lombard_2";
		link.l2 = "Desafortunadamente, yo también soy un 'quebrado' ahora mismo. Así que no puedo ayudarte, ¡lo siento mucho!";
		link.l2.go = "lombard_exit";
		break;

	case "lombard_exit":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		npchar.lifeday = 0;
		DeleteAttribute(pchar, "GenQuest.Noblelombard");
		break;

	case "lombard_2":
		dialog.text = "Gracias por tu comprensión. Te esperaré en la taberna. Ven allí lo antes posible.";
		link.l1 = "... ";
		link.l1.go = "lombard_3";
		break;

	case "lombard_3":
		DialogExit();
		pchar.GenQuest.Noblelombard = "true" pchar.GenQuest.Noblelombard.Name = GetFullName(npchar);
		pchar.GenQuest.Noblelombard.id = npchar.id;
		pchar.GenQuest.Noblelombard.City = npchar.city;
		pchar.GenQuest.Noblelombard.Money = 20000 + hrand(60) * 500;
		pchar.GenQuest.Noblelombard.Percent = makeint(sti(pchar.GenQuest.Noblelombard.Money) * 0.3);
		pchar.GenQuest.Noblelombard.Summ = sti(pchar.GenQuest.Noblelombard.Money) + sti(pchar.GenQuest.Noblelombard.Percent);
		pchar.GenQuest.Noblelombard.Chance = hrand(9);
		chrDisableReloadToLocation = true; // закрыть локацию
		LAi_SetActorType(npchar);
		LAi_RemoveLoginTime(npchar);
		DeleteAttribute(npchar, "CityType"); // удалить признак фантома
		FreeSitLocator(pchar.GenQuest.Noblelombard.City + "_tavern", "sit1");
		LAi_ActorRunToLocation(npchar, "reload", "reload4_back", pchar.GenQuest.Noblelombard.City + "_tavern", "sit", "sit1", "Nobleman_lombardTavern", 10);
		SetFunctionTimerCondition("Noblelombard_Over", 0, 0, 1, false); // таймер до конца суток
		ReOpenQuestHeader("Noblelombard");
		AddQuestRecord("Noblelombard", "1");
		AddQuestUserData("Noblelombard", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Noblelombard.City));
		AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
		break;

	case "lombard_4":
		if (CheckAttribute(pchar, "GenQuest.Noblelombard.Regard"))
		{
			pchar.quest.Noblelombard_Over.over = "yes"; // снять таймер
			dialog.text = "¿Qué puedes decir, " + GetAddress_Form(NPChar) + "¿Has estado en el banco? ¿Tienes buenas o malas noticias?";
			if (pchar.GenQuest.Noblelombard == "full")
				link.l1 = "He cumplido. He pagado toda tu deuda en sí. Puedes ir allí y recuperar tu reliquia.";
			if (pchar.GenQuest.Noblelombard == "maxpercent")
				link.l1 = "He pagado. He pagado todos los intereses de los últimos tres meses y aunque para los próximos tres. Puedes esperar tu dinero con seguridad. Solo no olvides pagar tu deuda principal en tres meses.";
			if (pchar.GenQuest.Noblelombard == "minpercent")
				link.l1 = "He pagado. He pagado todos los intereses de los últimos tres meses. El banquero acordó esperar tres meses más hasta que consigas la suma total.";
			link.l1.go = "lombard_5";
			break;
		}
		if (pchar.GenQuest.Noblelombard == "fail")
		{
			dialog.text = "¿Qué puedes decir, " + GetAddress_Form(NPChar) + "¿Has estado en el banco? ¿Buenas noticias o malas?";
			link.l1 = "He tenido. Este avaro ha pedido una suma increíble. Rechazó cualquier petición de concesiones y no tengo la suma requerida. Así que no pude ayudarte. Lo siento.";
			link.l1.go = "lombard_fail";
		}
		else
		{
			dialog.text = "¿Qué puedes decir, " + GetAddress_Form(NPChar) + "¿Has estado en el banco? ¿Buenas noticias o malas?";
			link.l1 = "Estoy en ello. Espera.";
			link.l1.go = "exit";
			NextDiag.TempNode = "lombard_4";
		}
		break;

	case "lombard_fail":
		pchar.quest.Noblelombard_Over.over = "yes"; // снять таймер
		dialog.text = "Meh, " + GetAddress_Form(NPChar) + "... Ahora también eres testigo de la insaciable codicia de estos malditos usureros sedientos de sangre. ¡Por Dios, señor, avergüenzan a los judíos! Recuerda eso cuando intentes pedirles dinero prestado, como lo hice yo. Gracias por intentarlo al menos...";
		link.l1 = "Nunca me gustaron. Bueno, ¿a quién le gustan los usureros? Lo siento, " + GetAddress_FormToNPC(NPChar) + " Adiós.";
		link.l1.go = "lombard_fail_1";
		break;

	case "lombard_fail_1":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		npchar.lifeday = 0;
		AddQuestRecord("Noblelombard", "4");
		AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
		CloseQuestHeader("Noblelombard");
		sld = characterFromId(pchar.GenQuest.Noblelombard.City + "_usurer");
		DeleteAttribute(sld, "quest.noblelombard");
		DeleteAttribute(Pchar, "GenQuest.Noblelombard");
		break;

	case "lombard_5":
		dialog.text = "¡Increíble! Me acabas de salvar, " + GetAddress_Form(NPChar) + "¡Nunca lo olvidaré! Te aseguro que todos tus gastos serán doblemente reembolsados. Ven a ver a nuestro banquero en tres meses. Abriré un depósito a tu nombre.";
		link.l1 = "Está bien, haré lo que dices. ¡Nos vemos!";
		link.l1.go = "lombard_6";
		break;

	case "lombard_6":
		dialog.text = "Gracias de nuevo, capitán. ¡Buena suerte!";
		link.l1 = "...";
		link.l1.go = "lombard_7";
		break;

	case "lombard_7":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		npchar.lifeday = 0;
		ChangeCharacterComplexReputation(pchar, "authority", 2);
		ChangeOfficersLoyality("good_all", 1);
		AddQuestRecord("Noblelombard", "5");
		AddQuestUserData("Noblelombard", "sName", pchar.GenQuest.Noblelombard.Name);
		SetFunctionTimerCondition("Noblelombard_Regard", 0, 0, 90, false); // таймер
		break;
		//<-- семейная реликвия

		//------------------------------------------привезти рабов под заказ--------------------------------------------
	case "slaves":
		npchar.quest.slaves.price = 3 + hrand(1);	  // цена на рабов в дублонах
		npchar.quest.slaves.qty = 50 + hrand(5) * 10; // количество
		npchar.quest.slaves.money = sti(npchar.quest.slaves.qty) * sti(npchar.quest.slaves.price);
		dialog.text = "Soy dueño de una " + LinkRandPhrase("fábrica", "factoría", "plantación") + " y siempre tengo necesidad de esclavos frescos porque el clima los afecta seriamente. Ahora mismo necesito " + sti(npchar.quest.slaves.qty) + " almas. Estoy dispuesto a encargarte un lote y te pagaré " + sti(npchar.quest.slaves.price) + " doblones por cabeza.\nNo hay prisa, no te meteré prisa si obtienes lo que necesito. Bueno, dentro de lo razonable, no lo prolongues más de medio año. ¿Entonces, qué me dices? ¿Hay trato?";
		link.l1 = "¡Trato hecho! La esclavitud es un negocio sucio, pero vale la pena el riesgo.";
		link.l1.go = "slaves_1";
		link.l2 = "Perdóname, pero no soy traficante de esclavos. No es mi línea de trabajo.";
		link.l2.go = "exit_slaves";
		break;

	case "exit_slaves":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		npchar.lifeday = 0;
		break;

	case "slaves_1":
		dialog.text = "Muy bien entonces. Te estaré esperando cuando traigas la carga. Puedes encontrarme en la iglesia desde las 11 AM hasta la 1 PM todos los días. Estoy ocupado o trabajando el resto del día.";
		link.l1 = "Está bien. Lo recordaré. Nos vemos, " + GetAddress_FormToNPC(NPChar) + ".";
		link.l1.go = "slaves_2";
		break;

	case "slaves_2":
		DialogExit();
		sGlobalTemp = npchar.id;
		DeleteAttribute(npchar, "LifeDay");
		DeleteAttribute(npchar, "CityType");				 // удалить признак фантома, иначе - пустые города
		SaveCurrentNpcQuestDateParam(npchar, "slaves_date"); // запоминаем дату
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload4_back", npchar.city + "_church", "sit", "sit" + (1 + rand(5)), "Nobleslaves_Place", 10.0);
		chrDisableReloadToLocation = true; // закрыть локацию
		Colonies[FindColony(npchar.city)].questslaves = true;
		sTitle = npchar.city + "Nobleslaves";
		ReOpenQuestHeader(sTitle);
		AddQuestRecordEx(sTitle, "Nobleslaves", "1");
		AddQuestUserDataForTitle(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData(sTitle, "sCity", XI_ConvertString("Colony" + npchar.city + "Gen"));
		AddQuestUserData(sTitle, "sName", GetFullName(npchar));
		AddQuestUserData(sTitle, "sQty", sti(npchar.quest.slaves.qty));
		AddQuestUserData(sTitle, "sMoney", sti(npchar.quest.slaves.money));
		break;

	case "slaves_3":
		if (GetNpcQuestPastDayParam(npchar, "slaves_date") < 180)
		{
			dialog.text = "¿Has traído " + sti(npchar.quest.slaves.qty) + " esclavos como te he pedido, capitán?";
			if (GetSquadronGoods(pchar, GOOD_SLAVES) >= sti(npchar.quest.slaves.qty))
			{
				link.l1 = "Sí. Todo el lote está en mi bodega. Estoy listo para entregártelos.";
				link.l1.go = "slaves_4";
			}
			else
			{
				link.l1 = "No, estoy en ello.";
				link.l1.go = "exit";
				NextDiag.TempNode = "slaves_3";
			}
		}
		else
		{
			dialog.text = "Capitán, si está aquí por esos esclavos... ya he comprado suficientes y no necesito más por ahora. Tardaste demasiado, lo siento.";
			link.l1 = "¡Qué lástima! Pero tienes razón, no fui lo suficientemente rápido. ¡Adiós!";
			link.l1.go = "slaves_8";
		}
		break;

	case "slaves_4":
		dialog.text = "Excelente. Enviaré un bote para ellos de inmediato.";
		link.l1 = "¿Qué hay de mi pago?";
		link.l1.go = "slaves_5";
		break;

	case "slaves_5":
		dialog.text = "No te preocupes, lo recuerdo. Aquí, toma la suma, " + sti(npchar.quest.slaves.price) + "doblones por cabeza. ¿Un buen trato para ambos, sí?";
		link.l1 = "Gracias. Un placer hacer negocios contigo.";
		link.l1.go = "slaves_6";
		break;

	case "slaves_6":
		RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(npchar.quest.slaves.qty));
		TakeNItems(pchar, "gold_dublon", sti(npchar.quest.slaves.money));
		Log_Info("Has recibido " + FindRussianDublonString(sti(npchar.quest.slaves.money)) + "");
		PlaySound("interface\important_item.wav");
		dialog.text = "¡Eso debería decirse... Discúlpame ahora, debo irme. ¡Hasta luego!";
		link.l1 = "Buena suerte, " + GetAddress_FormToNPC(NPChar) + ".";
		link.l1.go = "slaves_7";
		break;

	case "slaves_7":
		DialogExit();
		npchar.lifeday = 0;
		DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
		LAi_SetActorType(npchar);
		GetCharacterPos(pchar, &locx, &locy, &locz);
		ChangeCharacterAddressGroup(npchar, npchar.city + "_church", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
		LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 10.0);
		AddCharacterExpToSkill(pchar, "Commerce", 150); // торговля
		AddCharacterExpToSkill(pchar, "Sailing", 50);	// навигация
		AddCharacterExpToSkill(pchar, "Fortune", 30);	// везение
		ChangeCharacterComplexReputation(pchar, "nobility", -1);
		sTitle = npchar.city + "Nobleslaves";
		AddQuestRecordEx(sTitle, "Nobleslaves", "2");
		CloseQuestHeader(sTitle);
		break;

	case "slaves_8":
		DialogExit();
		npchar.lifeday = 0;
		LAi_CharacterDisableDialog(npchar);
		DeleteAttribute(Colonies[FindColony(npchar.city)], "questslaves");
		sTitle = npchar.city + "Nobleslaves";
		AddQuestRecordEx(sTitle, "Nobleslaves", "3");
		CloseQuestHeader(sTitle);
		break;
		//<-- привезти рабов под заказ

	// замечание по обнажённому оружию от персонажей типа citizen
	case "CitizenNotBlade":
		dialog.text = NPCharSexPhrase(NPChar, "Escucha, como ciudadano de esta ciudad te pido que envaines tu espada.", "Escucha, como ciudadano de esta ciudad te pido que envaines tu espada.");
		link.l1 = LinkRandPhrase("Bien.", "Como desees.", "Bien.");
		link.l1.go = "exit";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "fight":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		LAi_SetHP(NPChar, 400, 400);
		TakeNItems(NPChar, "potion2", 3);
		SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		LAi_group_MoveCharacter(NPChar, "TempFight");
		LAi_group_Attack(NPChar, Pchar);
		AddDialogExitQuest("MainHeroFightModeOn");
		ChangeCharacterNationReputation(pchar, sti(npchar.nation), -3);
		break;
	}
}

string DonationText()
{
	string sText;
	switch (hrand(5))
	{
	case 0:
		sText = "Ayer perdí todo mi dinero en el juego y no tengo suma suficiente para saldar la deuda. ¿Puedes ayudarme?" break;
	case 1:
		sText = "Ayer pasé un buen rato con... cierta dama de la noche, y ahora está intentando chantajearme. Necesito pagarle primero y luego me encargaré de ella... ¿Puedes ayudarme con algo de dinero?" break;
	case 2:
		sText = "Hace poco atravesé a un tonto del pueblo con mi estoque y ahora el comandante exige un soborno para silenciar el suceso. Ahora estoy corto de dinero. ¿Puedes ayudarme?" break;
	case 3:
		sText = "Tuve la mala suerte de perder una apuesta y no tengo una suma insignificante para pagar la deuda de honor. ¿Puedes ayudarme?" break;
	case 4:
		sText = "Algún bastardo sabe de mis... actividades indiscretas con una mujer casada. No tengo suficiente dinero para cerrarle la boca. Sólo necesito unas pocas monedas de oro... " break;
	case 5:
		sText = "Algún cabrón ha robado papeles importantes de mi casa y exige una suma importante para devolverlos. Ya casi lo tengo, solo me faltan unas monedas. ¿Puedes ayudarme?" break;
	}
	return sText;
}

void LombardText()
{
	switch (hrand(5))
	{
	case 0:
		pchar.GenQuest.Noblelombard.Item = "el colgante de diamantes de mi madre hecho por un joyero de Madrid";
		pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("Recibiré mi herencia", "mi barco volverá de África cargado de esclavos");
		break;
	case 1:
		pchar.GenQuest.Noblelombard.Item = "un collar de esmeraldas de mi hermana hecho a mano por un joyero de París";
		pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("Heredaré un condado en Europa", "mi barco volverá de la India cargado de especias y seda");
		break;
	case 2:
		pchar.GenQuest.Noblelombard.Item = "anillo familiar con el emblema de nuestros parientes";
		pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("mi expedición regresará de Tierra Firme con lingotes de oro", "Recibiré mi herencia");
		break;
	case 3:
		pchar.GenQuest.Noblelombard.Item = "una pulsera de rubíes de mi mujer, regalo de su madre";
		pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("Recibiré mi inversión con los intereses de un banco europeo", "Obtendré los beneficios de mi plantación");
		break;
	case 4:
		pchar.GenQuest.Noblelombard.Item = "un collar de oro y diamantes, pieza de trabajo, un orgullo de mi esposa";
		pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("Obtendré beneficios de mi negocio actual", "mi barco volverá de África con la bodega llena de marfil negro");
		break;
	case 5:
		pchar.GenQuest.Noblelombard.Item = "un bastón de marfil con piedras semipreciosas, regalo de mi abuelo";
		pchar.GenQuest.Noblelombard.Text = RandPhraseSimple("mi barco volverá de la India con la bodega llena de sedas y especias", "Recibiré mis intereses de un banco europeo");
		break;
	}
}
