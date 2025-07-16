// boal 25/04/04 общий диалог церковь
#include "DIALOGS\%language%\Rumours\Common_rumours.c" //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Church\" + NPChar.City + "_Church.c ";
						 if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}

	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag); // homo 16/06/06

	string iDay, iMonth, lastspeak_date, eggStr;
	string sTemp, sTitle;

	iDay = environment.date.day;
	iMonth = environment.date.month;
	lastspeak_date = iday + " " + iMonth;
	int iMoneyToCharacter;

	if (!CheckAttribute(npchar, "quest.HealthMonth"))
	{
		npchar.quest.HealthMonth = "";
	}

	if (!CheckAttribute(npchar, "quest.BadMeeting"))
	{
		npchar.quest.BadMeeting = "";
	}
	if (!CheckAttribute(npchar, "quest.GhostShipMonth"))
	{
		npchar.quest.GhostShipMonth = "";
	}

	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = "";
	}

	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_2.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = "";
	}

	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDateParam"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = "";
	}

	if (!CheckAttribute(NPChar, "GenQuest.ChurchQuest_1.GiveQuestDay"))
	{
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = "";
	}

	switch (Dialog.CurrentNode)
	{
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "fight":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		LAi_group_Attack(NPChar, Pchar);
		break;

	case "First time":
		if (LAi_grp_playeralarm > 0)
		{
			dialog.text = NPCharRepPhrase(pchar, LinkRandPhrase("" + GetSexPhrase("Hijo mío", "Hija mía") + ", desafortunadamente, no puedo darte refugio. ¡Corre!", "La guardia de la ciudad está peinando la ciudad buscándote, " + GetSexPhrase("hijo mío", "hija mía") + ". Las puertas de mi iglesia están siempre abiertas para los que sufren, pero no puedo ofrecerte refugio...", "" + GetSexPhrase("Hijo mío", "Hija mía") + ", ¡tienes que correr! ¡No te demores, te lo ruego!"), LinkRandPhrase("¿Qué haces en la iglesia, alma caída? ¡Exijo que te vayas de inmediato, antes de que los soldados te encuentren aquí y perpetren una masacre!", "¡Abandona el templo de inmediato, blasfemo! ¡Nunca protegeré a un villano como tú!", "¡Abandona el templo de nuestro Señor de inmediato! ¡No necesitamos asesinos aquí!"));
			link.l1 = NPCharRepPhrase(pchar, RandPhraseSimple("Oh, vamos, padre...", "No necesito tu ayuda de todos modos..."), LinkRandPhrase("Solo no te interpongas en mi camino, Padre...", "Me iré, no te preocupes...", "Padre, detenga el alboroto, realmente no tengo tiempo para esto"));
			link.l1.go = "fight";
			break;
		}
		if (npchar.quest.BadMeeting != lastspeak_date)
		{
			if (!CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_2.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && NPChar.location != "LosTeques_church" && rand(5) == 1 && !CheckAttribute(pchar, "questTemp.Sharlie.Lock")) // 280313
			{
				dialog.text = "...¡arderán en el infierno ardiente para siempre! Nunca verán...";
				link.l1 = RandPhraseSimple("¡Ejem! ¿Estoy molestando, padre?", "¡Ese es el discurso!");
				link.l1.go = "GenQuest_Church_2_Start_1";
				NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
				break;
			}
			if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.QuestTown") && PChar.GenQuest.ChurchQuest_2.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete"))
			{
				Dialog.Text = "" + GetSexPhrase("Hijo mío", "Hija mía") + ", ¡me alegra verte de nuevo!";
				link.l1 = "Y me alegra verte en buena salud, padre " + NPChar.name + "...";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1";
				break;
			}
			if (CheckAttribute(PChar, "GenQuest.ChurchQuest_1.QuestTown") && PChar.GenQuest.ChurchQuest_1.QuestTown == NPChar.city && CheckAttribute(PChar, "GenQuest.ChurchQuest_1.Complete"))
			{
				Dialog.Text = "" + GetSexPhrase("Hijo mío", "Hija mía") + "¡ Me alegra verte de nuevo con buena salud y buen ánimo. El Señor debe habernos ayudado en nuestro asunto, ¿verdad?";
				link.l1 = "Sí, " + RandPhraseSimple("padre", "Santo Padre") + ", aunque no siempre el viento favorable sople en mis velas, aunque gasté algo más de tiempo, fuerzas y dinero. Tu misión está cumplida.";
				link.l1.go = "GenQuest_Church_1_Complete_1";
				break;
			}
			Dialog.Text = "Bienvenido a nuestro sagrado refugio, " + GetSexPhrase("hijo mío", "hija mía") + ".";
			link.l1 = "Hola, santo Padre.";
			if (startHeroType == 4 && NPChar.location == "SantaCatalina_church")
			{
				dialog.text = "Saludos, Ellen, hija mía.";
				link.l1 = "Y a ti, Padre.";
			}
			link.l1.go = "node_3";
			Link.l2 = "No eres mi padre y no me vuelvas a tratar así nunca más.";
			Link.l2.go = "node_2";
			NPChar.GenQuest.ChurchQuest_2.GiveQuestDay = lastspeak_date; // Если не дал сегодня, то токо на след день.
		}
		else
		{
			Dialog.Text = "¡Aléjate del templo del Señor, blasfemo! ¡No tenemos nada de qué hablar!";
			Link.l1 = "Ni siquiera quería hacerlo.";
			Link.l1.go = "exit";
		}
		NextDiag.TempNode = "First time";
		break;

	case "node_2":
		dialog.text = "¡Oh, blasfemo! ¡Vete! ¡No te atrevas a profanar el templo de nuestro Señor con tu presencia!";
		link.l1 = "No iba ni siquiera a quedarme aquí.";
		link.l1.go = "exit";
		ChangeCharacterComplexReputation(pchar, "nobility", -0.25);
		npchar.quest.BadMeeting = lastspeak_date;
		break;

	case "node_3":
		if (startHeroType == 4 && NPChar.location == "SantaCatalina_church")
		{
			dialog.text = "Me alegra que a pesar de tus... andanzas con Jan, no olvides a nuestro Señor y Su casa. ¿En qué puedo ayudarte?";
		}
		else
		{
			dialog.text = "Que el Señor bendiga a ti y tus asuntos... ¿Has venido a mí por alguna razón en particular?";
		}
		link.l1 = RandPhraseSimple("Me gustaría hacer una donación.", "Quiero donar a una buena causa.");
		link.l1.go = "donation";
		link.l2 = RandPhraseSimple("Creo que es hora de una confesión.", "Quiero confesar, " + RandPhraseSimple("padre.", "Santo Padre."));
		link.l2.go = "ispoved";
		link.l3 = RandPhraseSimple("Tengo asuntos con usted, " + RandPhraseSimple("padre.", "santo Padre."), "He llegado por negocios, " + RandPhraseSimple("padre.", "Santo Padre."));
		link.l3.go = "work";

		//--> Сага
		// Картахена, Чика Гонсалес
		if (CheckAttribute(pchar, "questTemp.Saga") && pchar.questTemp.Saga == "cartahena" && pchar.location == "Cartahena_church" && sti(pchar.money) >= 1000)
		{
			link.l4 = "Quiero encargar un servicio de oración por la paz del alma de una dama.";
			link.l4.go = "saga";
		}
		// поиски исцеления от заклятий
		if (CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location != "Bridgetown_church" && !CheckAttribute(npchar, "quest.seektreatment"))
		{ // все церкви, кроме Бриджтауна
			link.l4 = "Padre, necesito ayuda. Estoy realmente enfermo. Alguna maldición pagana me ha caído encima. Por favor, ayúdame, te lo ruego.";
			link.l4.go = "seektreatment";
		}
		if (CheckAttribute(pchar, "questTemp.Saga.JessSeekTreatment") && pchar.location == "Bridgetown_church")
		{ // попал в Бриджтаун
			link.l4 = "Padre, necesito ayuda. Estoy realmente enfermo. Alguna maldita maldición pagana ha caído sobre mí. ¡Por favor, ayúdame, te lo ruego!";
			link.l4.go = "findtreatment";
		}
		if (CheckAttribute(pchar, "questTemp.Saga.JessFindTreatment") && pchar.location == "Bridgetown_church")
		{ // пришёл в Бриджтаун по направлению
			link.l4 = "Padre, necesito ayuda. Estoy realmente enfermo. Alguna maldita maldición pagana ha caído sobre mí. Me dijeron que usted es quien puede ayudarme. Se lo suplico...";
			link.l4.go = "findtreatment";
		}
		// исцеление от заклятий Джесс
		if (CheckAttribute(pchar, "questTemp.Saga.JessTreatment") && pchar.location == "Bridgetown_church")
		{
			link.l4 = "Padre, necesito ayuda. Estoy realmente enfermo. Alguna vil maldición pagana ha caído sobre mí. Ella me envió a usted... Jessica Rose. Me dijo que usted podría ayudarme.";
			link.l4.go = "treatment";
		}
		if (CheckAttribute(npchar, "quest.candle"))
		{
			link.l4 = "Sobre las velas...";
			link.l4.go = "candle";
		}
		if (CheckAttribute(npchar, "quest.prayer") && GetNpcQuestPastDayParam(npchar, "prayer_date") >= 1 && stf(environment.time) >= 22.0)
		{
			link.l4 = "Estoy listo para rezar, Padre.";
			link.l4.go = "prayer";
		}
		//<-- Сага

		// Warship, 30.05.11. Миниквест из дел чести "Divine justice".
		if (CheckAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest") && AffairOfHonor_GetCurQuest() == "GodJudgement" &&
			NPChar.city == PChar.QuestTemp.AffairOfHonor.GodJudgement.CityId)
		{
			link.l5 = "Terribles cosas están ocurriendo, santo Padre.";
			link.l5.go = "AffairOfHonor_GodJudgement_1";
		}

		link.l6 = "Disculpe, pero tengo que irme.";
		link.l6.go = "exit";
		break;

	case "AffairOfHonor_GodJudgement_1":
		dialog.text = "No te preocupes, hijo mío. El Señor verá tu sufrimiento y te extenderá una mano amiga. Lleva siempre una cruz contigo para fortalecer tu fe.";
		Link.l1 = "Gracias, santo Padre.";
		Link.l1.go = "exit";
		AddItems(PChar, "amulet_3", 15);
		DeleteAttribute(Pchar, "QuestTemp.AffairOfHonor.GodJudgement.CanSpeakPriest");
		break;

		// Jason-------------------------------------------------Сага----------------------------------------------
		//--> Чика Гонсалес
	case "saga":
		dialog.text = "Llevaré a cabo humildemente vuestra voluntad por 1000 pesos.";
		Link.l1 = "Aquí tiene Padre, por favor, tome estas monedas.";
		Link.l1.go = "saga_1";
		break;

	case "saga_1":
		AddMoneyToCharacter(pchar, -1000);
		dialog.text = "Gracias, hijo mío. ¿Cuál es el nombre de la señora por cuya alma debo rezar?";
		Link.l1 = "Su nombre es Chica Gonzales, y dejó este mundo hace muchos años.";
		Link.l1.go = "saga_2";
		break;

	case "saga_2":
		dialog.text = "Eso es extraño... ¿Le ocurrió algo a Álvarez y él te preguntó sobre esto?";
		Link.l1 = "¿Y quién es este Álvarez y qué tiene de extraño mi petición?";
		Link.l1.go = "saga_3";
		break;

	case "saga_3":
		dialog.text = "¡Vaya, cómo! Cada mes, Álvarez, el guardián de nuestro faro durante dos décadas, ordena un servicio de oración por la paz del alma de esta dama. Nadie más que él aún se ha preocupado por Lady Gonzales. Y tú vienes aquí. Así que pensé. Sin embargo, no es asunto mío. Ciertamente, estaré encantado de cumplir humildemente tus deseos para ayudar al alma perdida a encontrar la calma y el camino al paraíso.";
		Link.l1 = "Gracias, santo Padre.";
		Link.l1.go = "saga_4";
		break;

	case "saga_4":
		DialogExit();
		if (CheckAttribute(pchar, "questTemp.Saga7"))
		{
			AddQuestRecord("Saga", "151");
			DeleteAttribute(pchar, "questTemp.Saga7");
		}
		else
			AddQuestRecord("Saga", "15");
		Saga_SetOrtega();
		pchar.questTemp.Saga = "ortega";
		pchar.quest.Saga_Gonsales1.over = "yes"; // снять возможное прерывание
		if (GetCharacterIndex("SagaGonsalesB") != -1)
		{
			sld = characterFromId("SagaGonsalesB");
			sld.lifeday = 0;
		}
		break;

	// belamour участвовал в событиях Картахены
	case "saga_5":
		dialog.text = "¿Hay algún alma por la que te gustaría encargar un réquiem?";
		Link.l1 = "Mmm... No, no lo creo. ¿Necesito pedir por alguien más?";
		Link.l1.go = "saga_6";
		break;

	case "saga_6":
		dialog.text = "Bueno, ¿quizás por los cientos de personas inocentes que cayeron por tu mano o las espadas de tus compañeros impíos cuando saqueaste esta desafortunada ciudad?.. Sin embargo, es poco probable que un humilde sacerdote espere alcanzar la conciencia de un hombre que mató a simples ciudadanos pacíficos sin remordimientos...";
		Link.l1 = "Padre, no entiende... Todo eso es cosa del pasado. Aquí y ahora, no tengo la intención de hacer daño a nadie.";
		Link.l1.go = "saga_7";
		break;

	case "saga_7":
		pchar.questTemp.saga7 = true;
		dialog.text = "¿Puedo confiar en tu palabra...? Pero, en cualquier caso, este es un terreno sagrado que no debería estar cubierto de sangre. Así que, no llamaré a los guardias. Ve en paz. Tal vez antes de enfrentar el juicio de Dios, tengas tiempo de redimir al menos parte de tus pecados.";
		Link.l1 = "Quizás. Que se haga la voluntad de Dios.";
		Link.l1.go = "saga_4";
		break;
	// <-- Чика Гонсалес

	// --> исцеление от заклятий
	case "treatment":
		dialog.text = "¿Jessica? La recuerdo. Pobre pecadora. ¿Pero no murió?";
		link.l1 = "Murió, santo Padre. Ahora está muerta, que el Señor descanse su alma. Pero me aseguró que usted podría ayudarme.";
		link.l1.go = "treatment_1";
		DeleteAttribute(pchar, "questTemp.Saga.JessTreatment");
		break;

	case "treatment_1":
		dialog.text = "¿Quién colocó estos hechizos sobre ti, hijo mío? Dime con sinceridad.";
		link.l1 = "Ella... ella lo hizo. Jessica.";
		link.l1.go = "treatment_2";
		break;

	case "treatment_2":
		dialog.text = "¡Dios nos salve! Eso es lo que pensé. Profundizar en ritos paganos puede lanzar incluso las almas más fuertes al abismo de la oscuridad... Pero... ¿realmente murió? O... ¿no completamente?";
		link.l1 = "Eres extremadamente perspicaz, Padre. Ahora ella está totalmente muerta.";
		link.l1.go = "treatment_3";
		break;

	case "treatment_3":
		dialog.text = "Esta pobre pecadora se confesó muchas veces conmigo. El odio la destruyó completamente desde dentro. Sabía lo que planeaba. Intenté detenerla, traté de hacer que siguiera el buen camino, pero todos mis esfuerzos fueron en vano. La advertí sobre el terrible peligro y las terribles consecuencias de los actos impíos...";
		link.l1 = "Sí, santo Padre. Lo que he visto fue realmente terrible. Pero... ¿cómo puedo ser curado?";
		link.l1.go = "treatment_4";
		break;

	case "treatment_4":
		dialog.text = "Por el poder de la oración, hijo mío. Por el poder de la santa oración purificadora en nuestro templo. Tendrás que orar por mucho tiempo, y no solo por ti. Tendrás que orar por ella también.";
		link.l1 = "¿Para Jessica?";
		link.l1.go = "treatment_5";
		break;

	case "treatment_5":
		dialog.text = "Sí. Por ti mismo y por su alma. Ven aquí a las diez de la noche, para que nadie te distraiga. Tendrás que rezar toda la noche. Trae contigo veinte velas gruesas de cera, enciéndelas y reza hasta que se consuman por completo.";
		link.l1 = "¿Y entonces seré curado?";
		link.l1.go = "treatment_6";
		break;

	case "treatment_6":
		dialog.text = "Todo está en manos del Señor. Te enseñaré a orar y dejaré la Sagrada Escritura para ti. El poder de la santa oración destruirá los hechizos malignos que te han caído, y también limpiará el alma de la pobre Jessica.";
		if (GetCharacterItem(pchar, "mineral3") >= 20)
		{
			link.l1 = "Tengo veinte velas de cera conmigo. Estoy listo para quedarme en el templo y comenzar a orar.";
			link.l1.go = "treatment_9";
		}
		else
		{
			link.l1 = "Aún no tengo veinte velas conmigo. ¡Las conseguiré!";
			link.l1.go = "treatment_7";
		}
		break;

	case "treatment_7":
		dialog.text = "Está bien, hijo mío. Te estaré esperando. ¡No pierdas tiempo!";
		link.l1 = "Estaré aquí pronto...";
		link.l1.go = "treatment_8";
		break;

	case "treatment_8":
		DialogExit();
		npchar.quest.candle = "true";
		break;

	case "candle":
		dialog.text = "¿Has traído veinte velas, hijo mío?";
		if (GetCharacterItem(pchar, "mineral3") >= 20)
		{
			link.l1 = "Sí, Padre. Tengo veinte velas de cera conmigo. Estoy listo para quedarme en el templo y comenzar a orar.";
			link.l1.go = "treatment_9";
			DeleteAttribute(npchar, "quest.candle");
		}
		else
		{
			link.l1 = "Todavía no, pero los conseguiré por todos los medios.";
			link.l1.go = "exit";
		}
		break;

	case "treatment_9":
		dialog.text = "Bueno, hijo mío. Dámelos y vuelve mañana después de las diez de la noche. Te enseñaré las oraciones necesarias y te dejaré en la iglesia por la noche.";
		link.l1 = "Gracias, santo Padre. ¡Nos vemos mañana!";
		link.l1.go = "treatment_10";
		break;

	case "treatment_10":
		DialogExit();
		RemoveItems(pchar, "mineral3", 20);
		LAi_RemoveLoginTime(npchar);
		LAi_SetLoginTime(npchar, 6.0, 22.99);
		npchar.quest.prayer = "true";
		SaveCurrentNpcQuestDateParam(npchar, "prayer_date");
		break;

	case "prayer":
		dialog.text = "Te he preparado los textos de las oraciones, hijo mío. También te he dejado veinte velas y las Sagradas Escrituras. Enciende las velas y empieza a rezar. Reza sin para, reza por tu recuperación y por el alma de esta pobre pecadora Jessica. Si te olvidas de algo o si no lo entiendes, no importa. Reza de corazón, tu deseo sincero es lo que le importa a nuestro Señor.";
		link.l1 = "Gracias, Padre. Lo entiendo.";
		link.l1.go = "prayer_1";
		break;

	case "prayer_1":
		dialog.text = "Volveré por la mañana. También rezaré por ti...";
		link.l1 = "Gracias, santo Padre.";
		link.l1.go = "prayer_2";
		break;

	case "prayer_2":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Saga_BarbadosTreatment", -1);
		chrDisableReloadToLocation = true; // закрыть локацию
		break;

	case "seektreatment":
		dialog.text = "¿Qué hechizos paganos te han afectado, hijo mío?";
		link.l1 = "No sé cómo se llaman. Estoy débil y perezoso, no puedo correr y me resulta muy difícil luchar.";
		link.l1.go = "seektreatment_1";
		break;

	case "seektreatment_1":
		if (sti(pchar.questTemp.Saga.JessSeekTreatment) == 3)
		{
			dialog.text = "He oído hablar de ellos... Fueron traídos a nuestro mundo por brujas impías de esos paganos de piel roja. Te aconsejaría que veas al padre superior de la iglesia de Bridgetown; él pasó varios años estudiando la perniciosa influencia de las maldiciones indias en los cuerpos y almas de los cristianos.";
			link.l1 = "¿Y él sería capaz de ayudarme?!";
			link.l1.go = "seektreatment_4";
		}
		else
		{
			dialog.text = "He oído hablar de ellos... Fueron traídos a nuestro mundo por brujas impías de esos paganos de piel roja. Desafortunadamente, el único consejo que puedo darte es pasar más tiempo rezando, hijo mío, y depositar tus esperanzas en la misericordia de nuestro Señor.";
			link.l1 = "¿Pero realmente no se puede hacer nada al respecto, Padre?! ¿Me quedaré así... hasta el fin de mis días?";
			link.l1.go = "seektreatment_2";
		}
		break;

	case "seektreatment_2":
		dialog.text = "No desesperes, hijo mío. El Señor te escuchará y te enviará ayuda. Pero te recomendaría que preguntaras en otras moradas santas, quizás haya sacerdotes que sepan cómo eliminar maldiciones paganas.";
		link.l1 = "¡Gracias, Padre! Seré sanado, ¡aunque tenga que visitar todas las iglesias del archipiélago!";
		link.l1.go = "seektreatment_3";
		break;

	case "seektreatment_3":
		dialog.text = "Ve, hijo mío, y que el Señor te cuide.";
		link.l1 = "Adiós, padre.";
		link.l1.go = "exit";
		npchar.quest.seektreatment = "true";
		pchar.questTemp.Saga.JessSeekTreatment = sti(pchar.questTemp.Saga.JessSeekTreatment) + 1;
		break;

	case "seektreatment_4":
		dialog.text = "Solo el Señor puede ayudarte y tú mismo, hijo mío. Un sacerdote solo puede enseñarte qué hacer y cómo. Ven a verlo.";
		link.l1 = "¡Gracias, padre! ¡Me has salvado! ¡Zarparé de inmediato hacia Barbados!";
		link.l1.go = "seektreatment_5";
		break;

	case "seektreatment_5":
		dialog.text = "Ve ahora, y que el Señor vele por ti.";
		link.l1 = "Adiós, Padre.";
		link.l1.go = "exit";
		DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment");
		pchar.questTemp.Saga.JessFindTreatment = "true";
		break;

	case "findtreatment":
		dialog.text = "¿Qué maldiciones paganas te han caído, hijo mío? Déjame adivinar: ¿no puedes correr, un sable es demasiado pesado para ti y tus movimientos son lentos y torpes?";
		link.l1 = "¿Cómo lo supiste, Padre?";
		link.l1.go = "findtreatment_1";
		break;

	case "findtreatment_1":
		dialog.text = "No fue difícil verlo, al observar tu paso mientras te acercabas a mí, hijo mío. Que el Señor sea misericordioso con nuestras almas pecadoras... Dime, hijo mío, y sé honesto: ¿quién te ha lanzado estos encantamientos?";
		link.l1 = "¿Necesita un nombre, Padre?";
		link.l1.go = "findtreatment_2";
		break;

	case "findtreatment_2":
		dialog.text = "Si conoces el nombre, entonces dilo.";
		link.l1 = "Su nombre era... Jessica Rose.";
		link.l1.go = "findtreatment_3";
		break;

	case "findtreatment_3":
		dialog.text = "¡Dios nos salve! Profundizar en ritos paganos puede arrojar incluso a las almas más fuertes al abismo de la oscuridad... ¿Qué le sucedió a ella, a esta pobre alma?";
		link.l1 = "Murió, Padre.";
		link.l1.go = "findtreatment_4";
		break;

	case "findtreatment_4":
		dialog.text = "Pero... ¿realmente murió? O... ¿no completamente?";
		link.l1 = "Eres extremadamente perspicaz, santo Padre. Ahora está completamente muerta.";
		link.l1.go = "treatment_3";
		DeleteAttribute(pchar, "questTemp.Saga.JessSeekTreatment"); // если было
		DeleteAttribute(pchar, "questTemp.Saga.JessFindTreatment"); // если было
		break;
	//<-- Сага

	// Church GenQuest_2 -->
	case "GenQuest_Church_2_Start_1":
		dialog.text = "...¡y la misericordia del Señor! Que la oscuridad universal consuma sus almas por sus pecados...";
		link.l1 = LinkRandPhrase("Santo Padre", "Padre", "Padre") + ", ¿no eres un poco demasiado celoso? Sabes, podrías tener un derrame cerebral...";
		link.l1.go = "GenQuest_Church_2_Start_2";
		link.l2 = "Bueno... mierda. Adiós entonces.";
		link.l2.go = "exit";
		break;

	case "GenQuest_Church_2_Start_2":
		dialog.text = "Oh, " + GetSexPhrase("hijo mío", "hija mía") + ", ¡terrible sacrilegio, el más atroz de los crímenes acaba de suceder! ¡Robar de la iglesia!!! ¡Es como meter la mano en el bolsillo del Señor mismo!";
		link.l1 = "Oh, ya veo... ¿Cómo sucedió?";
		link.l1.go = "GenQuest_Church_2_Start_3";
		link.l2 = LinkRandPhrase("Es muy triste y todo eso, pero realmente tengo que irme...", "Mis condolencias, padre, pero tengo que irme...", "Debes haber confiado demasiado en el Todopoderoso. Deberías haber usado cerraduras más seguras. Bueno, tengo que irme...");
		link.l2.go = "exit";
		break;

	case "GenQuest_Church_2_Start_3":
		dialog.text = "¡Bajo el manto de la noche, unos bribones se llevaron todo lo recaudado por la parroquia! ¡Estos blasfemos han tomado incluso el cáliz sacrificial!";
		link.l1 = "¡O tempora, o mores... Pero espero que hayáis emprendido algo en un rastro caliente!";
		link.l1.go = "GenQuest_Church_2_Start_4";
		break;

	case "GenQuest_Church_2_Start_4":
		dialog.text = "¡Pero por supuesto! He excomulgado a esos blasfemos ladrones, ¡y ahora estoy pronunciando una anatematización contra ellos!";
		link.l1 = "No tengo duda de que es una medida muy efectiva. Pero me refería a algo más práctico. Organizar una persecución, por ejemplo.";
		link.l1.go = "GenQuest_Church_2_Start_5";
		break;

	case "GenQuest_Church_2_Start_5":
		dialog.text = "Ah, ¿qué puede hacer un simple sacerdote, atado por el voto de no resistencia al mal? ¡Esos sinvergüenzas seguramente ya están lejos de aquí, bebiendo en tabernas con lo robado o entregándose al desenfreno y la disipación en compañía de mujeres caídas! ¡Espero que allí encuentren su fin!";
		link.l1 = RandPhraseSimple("Estoy seguro de que tal final es mucho más atractivo que ser ahorcado. Sin embargo, no te distraeré más. Todo lo mejor.", "Bueno, tarde o temprano, todos iremos con los antepasados, pero no diría que no a un final más rápido para ellos. Sin embargo, debo irme. Buena suerte.");
		link.l1.go = "exit";
		link.l2 = LinkRandPhrase("Santo Padre", "Padre", "Padre") + ", pero no estoy atado por ningún voto y con disposición ayudaré al Señor a traer el tiempo de la retribución.";
		link.l2.go = "GenQuest_Church_2_Start_5_1";
		break;

	case "GenQuest_Church_2_Start_5_1": // выше - выход из диалога без подтверждения - странно, однако
		dialog.text = "¡Rezaré por ti, hijo mío! ¡Ve ahora y dales a esos estafadores lo que merecen!";
		link.l1 = "No tenga duda, Padre";
		link.l1.go = "GenQuest_Church_2_Start_6";
		break;

	case "GenQuest_Church_2_Start_6":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		PChar.GenQuest.ChurchQuest_2.StartQuest = true;
		PChar.GenQuest.ChurchQuest_2.QuestTown = NPChar.City; // Город, в котором спрашиваем
		PChar.GenQuest.ChurchQuest_2.QuestTown.PriestName = NPChar.name;
		PChar.GenQuest.ChurchQuest_2.IslandId = locations[FindLocation(NPChar.location)].islandId; // На каком острове опрашиваем бандюков
		PChar.GenQuest.ChurchQuest_2.Nation = sti(NPChar.nation);
		PChar.GenQuest.ChurchQuest_2.AskPeople = true;
		PChar.GenQuest.ChurchQuest_2.AskBarmen = true;
		PChar.GenQuest.ChurchQuest_2.AskAlcash = true;
		PChar.GenQuest.ChurchQuest_2.MoneyCount = (sti(pchar.rank) + 8) * 543 + 3210;
		PChar.GenQuest.ChurchQuest_2.MoneyToCharacter = makeint(sti(PChar.GenQuest.ChurchQuest_2.MoneyCount) / 3);
		sQuestTitle = NPChar.City + "ChurchGenQuest2";
		ReOpenQuestHeader(sQuestTitle);
		AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "1");
		AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
		AddQuestUserData(sQuestTitle, "sName", NPChar.name);
		break;

	case "GenQuest_Church_2_Thief_2":
		dialog.text = "Bueno, quizás el omnibenevolente Creador envía a sus hijos necios pestilencia y hambre para castigarlos por sus pecados...";
		link.l1 = "Por orgullo, por ejemplo, o avaricia... ¿Por qué te has puesto pálido, padre?";
		link.l1.go = "GenQuest_Church_2_Thief_3";
		break;

	case "GenQuest_Church_2_Thief_3":
		if (rand(1) == 0) // Священник искренне раскаивается...
		{
			dialog.text = "Jesús, mi Señor, muestra misericordia a tu siervo pecador... ¿Has... has encontrado a los ladrones? ¿Los has matado?";
			link.l1 = "Recordemos los diez mandamientos, conocidos por todo buen cristiano desde la cuna: no matarás, no robarás, no darás falso testimonio. ¿Puede una persona temerosa de Dios violarlos, aunque sea un guía espiritual...?";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_1";
		}
		else
		{
			dialog.text = "Hay un ambiente tan denso aquí... ¿Entonces has encontrado a los ladrones? ¿Los has matado?";
			link.l1 = "Recordemos los diez mandamientos, conocidos por todo buen cristiano desde la cuna: no matarás, no robarás, no darás falso testimonio. ¿Puede una persona temerosa de Dios violarlos, aunque sea un guía espiritual?";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_1";
		}
		break;

	case "GenQuest_Church_2_Thief_4_1_1":
		dialog.text = "" + GetSexPhrase("Hijo mío", "Hija mía") + "... Dios, perdóname... tal dinero, tal tentación... el hombre es débil, ¡verdaderamente débil! No pude soportarlo... Estaba fuera de mí... Recé día y noche, hice penitencia, ayuné rigurosamente, mortifiqué mi carne... Indigno, suplicaba a los Cielos solo para perdonar a esos pobres hombres, a quienes había tentado, impulsado por mi propia avaricia...";
		link.l1 = LinkRandPhrase("Padre", "Padre", "Padre") + ", cálmate. No han dicho nada al respecto... y no lo dirán, eso es seguro. Por cierto, me han devuelto voluntariamente el cáliz de la Comunión, que te traje de vuelta.";
		link.l1.go = "GenQuest_Church_2_Thief_4_1_2";
		break;

	case "GenQuest_Church_2_Thief_4_1_2":
		dialog.text = "¡Señor, te agradezco! ¡Dios mío, has escuchado las oraciones de tu indigno siervo, un pecador tropezado hundido en la inmundicia y los vicios...";
		link.l1 = "Cualquiera podría haber tropezado... Pero ya que tu arrepentimiento parece sincero, diría esto: eres un hombre decente y un buen sacerdote. Si te presentas ante el tribunal, no saldrá nada bueno de ello. Y te corresponde a ti decidir si permaneces al servicio del Señor o no. Solo Él puede decirte eso y guiarte...  ";
		link.l1.go = "GenQuest_Church_2_Thief_4_1_3";
		break;

	case "GenQuest_Church_2_Thief_4_1_3":
		if (rand(1) == 0) // Священник хочет всучить ГГ бабло
		{
			dialog.text = "" + GetSexPhrase("Hijo mío", "Hija mía") + "... Con lágrimas de arrepentimiento y gratitud aceptaré este cáliz de ti. La pureza y nobleza de tu alma realmente me han conmovido. Te bendigo con todo mi corazón y humildemente te ruego que aceptes esta pequeña recompensa de " + FindRussianMoneyString(iMoneyToCharacter) + "... ¿Espero que sea suficiente para cubrir tus gastos?";
			// ГГ не берёт деньги. Плюсанем репу
			link.l1 = "Esto es innecesario, santo Padre " + NPChar.name + ". No soy exactamente la persona más pobre, así que mejor usa este dinero para el bien de tu parroquia.";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
			// ГГ берёт деньги
			link.l2 = "Gracias, " + LinkRandPhrase("Padre", "padre", "Santo Padre") + ", eso es más que suficiente.";
			link.l2.go = "GenQuest_Church_2_Thief_4_1_5";
		}
		else
		{
			dialog.text = "" + GetSexPhrase("Hijo mío", "Hija mía") + "... Con lágrimas de arrepentimiento y gratitud, aceptaré este cáliz de ti como un signo de la misericordia y el perdón del Señor. La pureza y nobleza de tu alma realmente me han conmovido. ¡Te bendigo con todo mi corazón!";
			link.l1 = "Gracias por la bendición, " + LinkRandPhrase("padre.", "Padre.") + ".";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_4";
			link.l1 = "La bendición es ciertamente necesaria, pero no estaría de más apoyarla con algo más material, considerando los considerables gastos que he incurrido...";
			link.l1.go = "GenQuest_Church_2_Thief_4_1_6";
		}
		ChurchGenQuest2_RemoveCup();
		break;

	case "GenQuest_Church_2_Thief_4_1_4":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		ChangeCharacterComplexReputation(PChar, "nobility", 3);
		sQuestTitle = NPChar.City + "ChurchGenQuest2";
		AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_1");
		AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", ""));
		AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
		CloseQuestHeader(sQuestTitle);
		DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		addLiberMisBonus();
		break;

	case "GenQuest_Church_2_Thief_4_1_5":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
		ChangeCharacterComplexReputation(PChar, "nobility", -2);
		sQuestTitle = NPChar.City + "ChurchGenQuest2";
		AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_2");
		AddQuestUserData(sQuestTitle, "sName", NPChar.name);
		CloseQuestHeader(sQuestTitle);
		DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		addLiberMisBonus();
		break;

	case "GenQuest_Church_2_Thief_4_1_6":
		iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
		dialog.text = "Oh, hijo, lo siento mucho... Espero que esta pequeña contribución de " + FindRussianMoneyString(iMoneyToCharacter) + " ¿Será suficiente para cubrir tus gastos?";
		link.l1 = "Sí, " + LinkRandPhrase("padre.", "Padre.") + ", es suficiente, gracias.";
		link.l1.go = "GenQuest_Church_2_Thief_4_1_6_1";
		break;

	case "GenQuest_Church_2_Thief_4_1_6_1":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		ChangeCharacterComplexReputation(PChar, "nobility", -2);
		AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
		sQuestTitle = NPChar.City + "ChurchGenQuest2";
		AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_3");
		AddQuestUserData(sQuestTitle, "sName", NPChar.name);
		CloseQuestHeader(sQuestTitle);
		DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		addLiberMisBonus();
		break;

	case "GenQuest_Church_2_Thief_4_2_1":
		dialog.text = "No entiendo del todo tus insinuaciones, " + GetSexPhrase("hijo mío", "hija mía") + ", ¿de qué estás hablando?!";
		link.l1 = "Estoy hablando de las terribles cosas que la codicia puede hacerle a un hombre y que obtuve de los rufianes que supuestamente robaron tu iglesia... ¿Querías decir algo?";
		link.l1.go = "GenQuest_Church_2_Thief_4_2_2";
		break;

	case "GenQuest_Church_2_Thief_4_2_2":
		dialog.text = "Te diría, hijo, que estás hablando con un clérigo y deberías mostrar un poco más de respeto, o podrías terminar lamentándolo. En cuanto a este cáliz, nunca lo he visto antes, pero si estás dispuesto a donarlo a la parroquia, entonces...";
		link.l1 = "Detente un momento, padre. No lo tendrás hasta que te expliques.";
		link.l1.go = "GenQuest_Church_2_Thief_4_2_3";
		break;

	case "GenQuest_Church_2_Thief_4_2_3":
		if (rand(1) == 0) // Просто несколько разные варианты диалога
		{
			dialog.text = "¿Qué hay que explicar? ¡Ahora, mira eres un " + GetSexPhrase("hombre astuto", "chica lista") + ", ¡y seguramente debes entender que cualquier cosa que esos bribones te hayan dicho, que supuestamente los había contratado, es una mentira descarada! ¡El Señor castigará a estos blasfemos no solo por sacrilegio, sino también por falso testimonio!";
			link.l1 = "¡Deja al Señor en paz! ¿Cómo puedes saber lo que esas pobres almas me han contado, aquellas a quienes me pusiste en contra? Tal vez, las maté antes de que tuvieran tiempo de decirme algo malo sobre ti?";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1";
		}
		else
		{
			dialog.text = "¡No tengo nada que hablar contigo! No has cumplido con tu obligación ante nuestro Señor, juras en el templo y estás intentando chantajear a un sacerdote exhibiendo algunos utensilios de la iglesia... ¡Y está por ver cómo lo conseguiste! ¡Da gracias a Dios que no llamo a los acólitos para que te cojan con las manos en la masa!";
			link.l1 = "Bueno... Veo que te has hundido en el pecado tan profundamente que ya no temes el juicio de los hombres. Pero aún hay justicia divina, y cada uno de nosotros tendrá que responder a ella tarde o temprano. Toma tus 'utensilios de iglesia' y piensa si eres digno de tocarlos, Padre " + NPChar.name + ".";
			link.l1.go = "GenQuest_Church_2_Thief_4_2_4_2_1";
			link.l2 = "Por favor, perdóname mis dudas, Padre, porque un corazón mortal es débil y el alma está confundida. Por favor, toma el cáliz y dame tu bendición.";
			link.l2.go = "GenQuest_Church_2_Thief_4_2_4_2_2";
		}
		break;

	case "GenQuest_Church_2_Thief_4_2_4_1":
		dialog.text = "Mmmm... " + GetSexPhrase("Hijo mío... Señor... Caballero...", "Hija mía... Señorita... Dama...") + " " + PChar.name + "... Estoy listo para inclinarme ante usted... y considerar nuestras discrepancias, por así decirlo... y compensar sus gastos con esta modesta suma de " + FindRussianMoneyString(iMoneyToCharacter) + " ... por supuesto, si no vas a involucrar a otros en este asunto... ";
		// При этом варианте репу плюсуем
		link.l1 = "No voy a involucrar a nadie. ¡Toma el cáliz! ¡Y ni pienses que aceptaría el oro que estabas pellizcando en secreto de los bolsillos de tus feligreses!";
		link.l1.go = "GenQuest_Church_2_Thief_4_2_4_1_1";
		// При этом - минусуем
		link.l2 = "No voy a involucrar a nadie. ¡Toma el cáliz! Este oro lo tomo solo porque gasté en ti mucho tiempo y dinero.";
		link.l2.go = "GenQuest_Church_2_Thief_4_2_4_1_2";
		break;

	case "GenQuest_Church_2_Thief_4_2_4_1_1":
		DialogExit();
		iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
		NextDiag.CurrentNode = NextDiag.TempNode;
		ChangeCharacterComplexReputation(PChar, "nobility", -2);
		AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
		ChurchGenQuest2_RemoveCup();
		sQuestTitle = NPChar.City + "ChurchGenQuest2";
		AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_5");
		AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", ""));
		AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("", ""));
		AddQuestUserData(sQuestTitle, "sSex2", GetSexPhrase("", ""));
		AddQuestUserData(sQuestTitle, "sName", NPChar.name);
		AddQuestUserData(sQuestTitle, "sMoney", FindRussianMoneyString(iMoneyToCharacter));
		CloseQuestHeader(sQuestTitle);
		DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		addLiberMisBonus();
		break;

	case "GenQuest_Church_2_Thief_4_2_4_1_2":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		ChangeCharacterComplexReputation(PChar, "nobility", 3);
		ChurchGenQuest2_RemoveCup();
		sQuestTitle = NPChar.City + "ChurchGenQuest2";
		AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_4");
		AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", ""));
		CloseQuestHeader(sQuestTitle);
		DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		addLiberMisBonus();
		break;

	case "GenQuest_Church_2_Thief_4_2_4_2_1":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		ChurchGenQuest2_RemoveCup();
		ChangeCharacterComplexReputation(PChar, "nobility", 3);
		sQuestTitle = NPChar.City + "ChurchGenQuest2";
		AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_6");
		AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", ""));
		AddQuestUserData(sQuestTitle, "sSex1", GetSexPhrase("", ""));
		AddQuestUserData(sQuestTitle, "sName", NPChar.name);
		CloseQuestHeader(sQuestTitle);
		DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		addLiberMisBonus();
		break;

	case "GenQuest_Church_2_Thief_4_2_4_2_2":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		ChurchGenQuest2_RemoveCup();
		sQuestTitle = NPChar.City + "ChurchGenQuest2";
		AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_7");
		AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", ""));
		AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
		CloseQuestHeader(sQuestTitle);
		DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		addLiberMisBonus();
		break;

	case "GenQuest_Church_2_Finally_Complete_1":
		// ничего не принесли священнику.
		if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Without_All"))
		{
			link.l1 = "Noticias funestas, " + LinkRandPhrase("Padre", "Padre", "Padre") + ": los ladrones eran demasiado traicioneros y astutos, y por eso no logré recuperar el oro de la iglesia...";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_1";
			break;
		}
		// Принесли священнику только чашу.
		if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Only_With_Cup"))
		{
			link.l1 = "Noticias terribles, " + LinkRandPhrase("Padre", "Padre", "Padre") + ": Logré alcanzar a los ladrones, pero mi único trofeo fue este cáliz.";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1";
			ChurchGenQuest2_RemoveCup();
			break;
		}
		// Принесли священнику и деньги и чашу.
		if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.With_All"))
		{
			if (sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
			{
				link.l1 = "Estoy seguro de que te gustarán las noticias: he castigado debidamente a los ladrones y les he quitado el dinero de la parroquia, y también este cáliz.";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
			}
			// Деньги можно заныкать.
			link.l2 = LinkRandPhrase("Padre", "Padre", "Padre") + ", he traído malas noticias... Tuve que pasar mucho tiempo, gastar fuerzas y recursos para cazar a los sinvergüenzas, pero cuando los encontré, descubrí que habían tenido tiempo de beber y gastar todo, excepto este cáliz...";
			link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
			ChurchGenQuest2_RemoveCup();
			break;
		}
		// Священник - вор.
		if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.PriestIsThief"))
		{
			dialog.text = "Oh, " + GetSexPhrase("hijo mío", "hija mía") + ", ¿qué podría haberme pasado? Es tu camino el que está lleno de peligros y ansiedad, y mi celda pacífica, dominio de la reflexión y la oración, es una isla tranquila en un océano tempestuoso de pasiones humanas...";
			link.l1 = "¿Y nada puede perturbar la serenidad de tu dichosa soledad?";
			link.l1.go = "GenQuest_Church_2_Thief_2";
			break;
		}
		// Короткий вариант прохождения квеста.
		if (CheckAttribute(PChar, "GenQuest.ChurchQuest_2.Complete.Short_With_Mon"))
		{
			if (sti(PChar.money) >= sti(PChar.GenQuest.ChurchQuest_2.MoneyCount))
			{
				link.l1 = "Estoy seguro de que esa noticia te alegrará: castigué a los ladrones y traje el dinero de la parroquia.";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_1";
			}
			// Деньги можно заныкать.
			link.l2 = LinkRandPhrase("Padre", "Padre", "Padre") + "... Tengo que decepcionarte. He estado persiguiendo a los ladrones por todo el archipiélago, superé una gran cantidad de peligros y barreras, casi me arruiné, y finalmente los alcancé, pero ay... ya tuvieron tiempo de derrochar el dinero de la iglesia.";
			link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1";
		}
		break;

	case "GenQuest_Church_2_Finally_Complete_1_3_1": // ГГ решил заныкать деньги...
		if (rand(1) == 0)							 // Священник верит ГГ но не даёт денег...
		{
			if (rand(4) == 3) // Более "мягкий" исход событий.
			{
				dialog.text = "Oh, " + GetSexPhrase("hijo mío", "hija mía") + ". Tus palabras me sumieron en una profunda tristeza, pero no en la desesperación, ¡porque la desesperación es un pecado mortal! El Señor nos enfrentó a otra prueba para fortalecer nuestra fe.";
				link.l1 = "Amén, Padre...";
				link.l1.go = "exit";
				sQuestTitle = NPChar.City + "ChurchGenQuest2";
				AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_9");
				AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", ""));
				CloseQuestHeader(sQuestTitle);
				ChangeCharacterComplexReputation(PChar, "nobility", -2);
				DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
				NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
			}
			else
			{
				dialog.text = "" + GetSexPhrase("Hijo mío", "Hija mía") + ", no mientas a tu pastor espiritual.";
				link.l1 = "Lo siento mucho, Padre, pero juro que estoy diciendo la verdad.";
				link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3";
			}
		}
		else
		{
			// Священник даёт деньги ГГ...
			iMoneyToCharacter = sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter);
			dialog.text = "Oh, " + GetSexPhrase("hijo mío", "hija mía") + ". Tus palabras me sumieron en una profunda tristeza, pero no en la desesperación, ¡porque la desesperación es un pecado mortal! El Señor nos enfrentó a otra prueba para fortalecer nuestra fe. Pero tus esfuerzos y gastos deben ser compensados, a pesar de ser infructuosos. Por favor, acepta esta modesta suma, " + FindRussianMoneyString(iMoneyToCharacter) + " y continúa tu camino justo!";
			link.l1 = "¡Hmm!... Gracias, padre, usaré este dinero para una causa virtuosa.";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_1";
			link.l2 = LinkRandPhrase("Padre", "Padre", "Padre") + "... No puedo aceptar una recompensa por un trabajo que no he hecho. Sería mejor que usaras este dinero para renovar el altar.";
			link.l2.go = "GenQuest_Church_2_Finally_Complete_1_3_1_2";
		}
		break;

	case "GenQuest_Church_2_Finally_Complete_1_3_1_3":
		if (rand(6) == 3)
		{
			dialog.text = "Está bien, te creo, " + GetSexPhrase("hijo mío", "hija mía") + "El Señor nos ha visitado con otra prueba para fortalecer nuestra fe.";
			link.l1 = "Amén...";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_1" break;
		}
		dialog.text = "¡Despreciable!, ¿realmente pensaste en engañar a nuestro Señor? ¡Maldito seas" + GetSexPhrase(", bribón!", ", ramera!") + " ¡Sal de aquí y recuerda que este dinero no te traerá ningún beneficio!";
		link.l1 = "¿Cómo es eso? ¡Padre!..";
		link.l1.go = "GenQuest_Church_2_Finally_Complete_1_3_1_3_2";
		break;

	case "GenQuest_Church_2_Finally_Complete_1_3_1_3_1":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		sQuestTitle = NPChar.City + "ChurchGenQuest2";
		AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "5");
		AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", ""));
		CloseQuestHeader(sQuestTitle);
		AddCharacterExpToSkill(PChar, "Sneak", 20);
		ChangeCharacterComplexReputation(PChar, "nobility", -3);
		DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;

	case "GenQuest_Church_2_Finally_Complete_1_3_1_3_2":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		sQuestTitle = NPChar.City + "ChurchGenQuest2";
		AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "6");
		AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", ""));
		CloseQuestHeader(sQuestTitle);
		ChangeCharacterComplexReputation(PChar, "nobility", -6);
		AddCharacterExpToSkill(PChar, "Leadership", -50);
		AddCharacterExpToSkill(PChar, "Fortune", -70);
		AddCharacterExpToSkill(PChar, "Sneak", 20);
		DeleteAttribute(PCHar, "GenQuest.ChurchQuest_2");
		npchar.quest.BadMeeting = lastspeak_date;
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;

	case "GenQuest_Church_2_Finally_Complete_1_4_1":
		if (rand(1) == 0) // Поверил.
		{
			dialog.text = "Oh, " + GetSexPhrase("hijo mío", "hija mía") + ". Tus palabras me sumieron en una profunda tristeza, ¡pero no en la desesperación, porque la desesperación es un pecado mortal! El Señor nos ha enfrentado a otra prueba para fortalecer nuestra fe.";
			link.l1 = "Amén, Padre...";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2"; // Переход сюда, т.к. одно и тоже.
		}
		else
		{
			dialog.text = "Sí, es ese mismo cáliz que fue robado junto con el dinero... Pero... Si lo has conseguido, ¿cómo es que no has traído de vuelta el dinero? Era una suma considerable, y seguramente esos granujas no podrían haberla gastado toda tan rápido... " + GetSexPhrase("Hijo mío", "Hija mía") + ", recuerda que no hay pecado mayor que mentir a tu pastor espiritual y dar falso testimonio en el templo ante Dios!";
			link.l1 = "Santo Padre " + NPChar.name + ", casi pierdo mi vida obteniendo este jarrón, pensando en hacerte feliz. ¡No diré nada sobre cuánto dinero gasté en todo esto!";
			link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2";
		}
		break;

	case "GenQuest_Church_2_Finally_Complete_1_4_1_2":
		dialog.text = "¡Sal y agradece al Todopoderoso, que me dio un corazón manso! ¡Es la única razón por la que aún no estás marcado como ladrón y bribón!";
		link.l1 = "¿Cómo es eso?! " + LinkRandPhrase("Santo Padre", "Padre", "Padre") + "¡..!";
		link.l1.go = "GenQuest_Church_2_Finally_Complete_1_4_1_2_1";
		break;

	case "GenQuest_Church_2_Finally_Complete_1_4_1_2_1":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		ChangeCharacterComplexReputation(PChar, "nobility", -5);
		sQuestTitle = NPChar.City + "ChurchGenQuest2";
		AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_12");
		AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", ""));
		CloseQuestHeader(sQuestTitle);
		DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
		NPChar.quest.BadMeeting = lastspeak_date;
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;

	case "GenQuest_Church_2_Finally_Complete_1_3_1_1":
		DialogExit();
		iMoneyToCharacter = PChar.GenQuest.ChurchQuest_2.MoneyToCharacter;
		NextDiag.CurrentNode = NextDiag.TempNode;
		ChangeCharacterComplexReputation(PChar, "nobility", -2);
		AddMoneyToCharacter(PChar, iMoneyToCharacter);
		sQuestTitle = NPChar.City + "ChurchGenQuest2";
		AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_10");
		AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", ""));
		CloseQuestHeader(sQuestTitle);
		DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;

	case "GenQuest_Church_2_Finally_Complete_1_3_1_2":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		ChangeCharacterComplexReputation(PChar, "nobility", -1);
		sQuestTitle = NPChar.City + "ChurchGenQuest2";
		AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_11");
		AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", ""));
		CloseQuestHeader(sQuestTitle);
		DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;

	case "GenQuest_Church_2_Finally_Complete_1_1_1":
		dialog.text = "Oh, " + GetSexPhrase("hijo mío", "hija mía") + ". Tus palabras me sumieron en una profunda tristeza, pero no en la desesperación, ¡porque la desesperación es un pecado mortal! El Señor nos enfrentó a otra prueba para fortalecer nuestra fe.";
		link.l1 = "Amén, Padre...";
		link.l1.go = "GenQuest_Church_2_Finally_Complete_1_1_2";
		break;

	case "GenQuest_Church_2_Finally_Complete_1_1_2":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		ChangeCharacterComplexReputation(PChar, "nobility", -2);
		sQuestTitle = NPChar.City + "ChurchGenQuest2";
		AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "12_8");
		CloseQuestHeader(sQuestTitle);
		DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		break;

	case "GenQuest_Church_2_Finally_Complete_1_2_1":
		dialog.text = "¡Señor, te doy gracias! ¡En verdad, eras Su herramienta, hijo mío! Sabía que nuestro Padre Celestial te mostraría el camino y te proporcionaría toda la ayuda que necesitabas. Estaba orando sin cesar, y...";
		link.l1 = "Sabes, padre, en asuntos como este, las armas son sin duda más útiles que las oraciones. Pero, al parecer, tus oraciones realmente fueron escuchadas.";
		link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_2";
		break;

	case "GenQuest_Church_2_Finally_Complete_1_2_2":
		dialog.text = "" + GetSexPhrase("Hijo mío", "Hija mía") + ", quiero recompensarte debidamente, tú" + GetSexPhrase(", como un verdadero caballero de la Santa Madre Iglesia,", "") + " hizo todo lo posible para sobreca...";
		link.l1 = "Padre, está exagerando realmente mis humildes logros. Ahora le dejaré para alabar a nuestro Señor...";
		link.l1.go = "GenQuest_Church_2_Finally_Complete_1_2_3";
		break;

	case "GenQuest_Church_2_Finally_Complete_1_2_3":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		ChangeCharacterComplexReputation(PChar, "nobility", 5);
		AddMoneyToCharacter(PChar, -sti(PChar.GenQuest.ChurchQuest_2.MoneyCount));
		AddMoneyToCharacter(PChar, sti(PChar.GenQuest.ChurchQuest_2.MoneyToCharacter));
		sQuestTitle = NPChar.City + "ChurchGenQuest2";
		AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "4");
		AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", ""));
		AddQuestUserData(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
		CloseQuestHeader(sQuestTitle);
		DeleteAttribute(PChar, "GenQuest.ChurchQuest_2");
		NPChar.GenQuest.ChurchQuest_2.GiveQuestDateParam = iMonth;
		addLiberMisBonus();
		break;
		// <-- квесты церкви

	case "donation":
		dialog.Text = "Por supuesto, " + GetSexPhrase("hijo mío", "hija mía") + ". ¿Cuánto le gustaría donar a la Santa Iglesia?";
		Link.l1 = "Lo siento, santo Padre, pero he cambiado de opinión.";
		Link.l1.go = "No donation";
		if (makeint(PChar.money) >= 100)
		{
			Link.l2 = "Mi donación será modesta, solo 100 pesos.";
			Link.l2.go = "donation paid_100";
		}
		if (makeint(PChar.money) >= 1000)
		{
			Link.l3 = "1000 pesos. Creo que eso debería ser suficiente.";
			Link.l3.go = "donation paid_1000";
		}
		if (makeint(PChar.money) >= 5000)
		{
			Link.l4 = "Soy afortunado con el dinero, así que donaré 5000 pesos.";
			Link.l4.go = "donation paid_5000";
		}
		//-->> квест пожертвования хозяйки борделя
		if (pchar.questTemp.different == "HostessChurch_toChurch" && pchar.questTemp.different.HostessChurch.city == npchar.city && sti(pchar.money) >= sti(pchar.questTemp.different.HostessChurch.money))
		{
			Link.l5 = "Padre, quiero hacer una donación no en mi nombre. Lo hago a petición.";
			Link.l5.go = "HostessChurch";
		}
		//<<-- квест пожертвования хозяйки борделя
		break;

	case "No donation":
		dialog.Text = "Hmm... Bueno, esta es tu decisión, y eres libre de cambiar de opinión. Y no olvides que esto será tenido en cuenta en el Día del Juicio.";
		Link.l1 = "Como muchas otras cosas también. Cambiemos de tema.";
		Link.l1.go = "node_3";
		Link.l2 = "Lo siento, Padre, pero es hora de que me vaya.";
		Link.l2.go = "exit";
		break;

	case "donation paid_100":
		AddMoneyToCharacter(pchar, -100);
		pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 100;
		dialog.Text = "En nombre de la Santa Iglesia te agradezco, " + GetSexPhrase("hijo mío", "hija mía") + ", por tu regalo.";
		Link.l1 = "Necesito hablar con usted, Padre.";
		Link.l1.go = "node_3";
		Link.l2 = "Lamento, Padre, pero es hora de que me marche.";
		Link.l2.go = "exit";
		AddDialogExitQuest("donation");
		break;

	case "donation paid_1000":
		AddMoneyToCharacter(pchar, -1000);
		pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 1000;
		dialog.Text = "En nombre de la Santa Iglesia, te doy las gracias.";
		Link.l1 = "Necesito hablar con usted, Padre.";
		Link.l1.go = "node_3";
		Link.l2 = "Lo siento, Padre, pero es hora de que me vaya.";
		Link.l2.go = "exit";
		AddDialogExitQuest("donation");
		break;

	case "donation paid_5000":
		AddMoneyToCharacter(pchar, -5000);
		pchar.questTemp.donate = makeint(pchar.questTemp.donate) + 5000;
		dialog.Text = "En nombre de la Santa Iglesia te agradezco por tu don.";
		Link.l1 = "Necesito hablar con usted, Padre.";
		Link.l1.go = "node_3";
		Link.l2 = "Lo siento, Padre, pero es hora de que me vaya.";
		Link.l2.go = "exit";
		AddDialogExitQuest("donation");
		break;

	case "ispoved":
		dialog.text = "Por supuesto, " + GetSexPhrase("hijo mío", "hija mía") + " , te escucho.";
		link.l1 = "He cambiado de opinión. Quizás la próxima vez.";
		link.l1.go = "exit";
		link.l2 = "Estoy tan lleno de pecados, Padre. Un día no será suficiente para enumerar todas mis fechorías...";
		link.l2.go = "ispoved_1";
		break;

	case "ispoved_1":
		dialog.text = "Todos nosotros somos pecadores, hijo mío...";
		link.l1 = "Sí, pero en mi conciencia la carga de miles de muertes es un grave peso. Robé y hundí barcos...";
		link.l1.go = "ispoved_2";
		break;

	case "ispoved_2":
		dialog.text = "Espero que no haya habido ninguno entre los que navegaron bajo la bandera de " + NationNameGenitive(sti(NPChar.nation)) + "...";
		link.l1 = "No, por supuesto que no, Padre.";
		link.l1.go = "ispoved_3";
		link.l2 = "Todo tipo de ellos, Padre...";
		link.l2.go = "ispoved_4";
		break;

	case "ispoved_3":
		dialog.text = "Entonces nuestro Señor te absolverá de esos pecados. Porque esta es una era cruel, y al destruir a los enemigos de tu soberano estás salvando las vidas de sus leales súbditos.";
		link.l1 = "Gracias, Padre, fue un gran consuelo... Me voy ahora.";
		link.l1.go = "exit";
		break;

	case "ispoved_4":
		dialog.text = "¡El Señor no te absolverá de tal pecado! ¡Ora y arrepiéntete, arrepiéntete y ora! Solo hay un camino para ti ahora: ¡al claustro!";
		link.l1 = "El claustro tendrá que esperar. No en esta vida, al menos. Adiós...";
		link.l1.go = "exit";
		npchar.quest.BadMeeting = lastspeak_date;
		break;

	case "work":
		if (CheckAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner") && NPChar.location == PChar.GenQuest.ChurchQuest_1.ToColony + "_church")
		{
			dialog.text = "Lo siento, " + GetSexPhrase("hijo mío", "hija mía") + ", pero todos los confesionarios están ocupados en este momento. Podré escuchar tu confesión en al menos media hora.";
			link.l1 = "Disculpe, " + RandPhraseSimple("padre", "Padre") + ", esto es un asunto diferente. Padre " + PChar.GenQuest.ChurchQuest_1.PriestName + ", de " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + ",   una vez te dio tesoros invaluables de la biblioteca teológica. Me pidió que los devolviera.";
			link.l1.go = "GenQuest_Church_1_Dialog_1";
			DeleteAttribute(PChar, "GenQuest.ChurchQuest_1.AskOwner");
			break;
		}
		dialog.text = "¿Qué clase de negocio te ha traído aquí, " + GetSexPhrase("hijo mío", "hija mía") + "?";
		link.l1 = "Quiero hacerle una pregunta, Padre...";
		link.l1.go = "quests"; // ссылка к НПС
		link.l2 = RandPhraseSimple("Quería hablar sobre trabajar para el bien de la iglesia de " + NationNameGenitive(sti(NPChar.nation)) + ".", "¿Cómo van las cosas en la parroquia? ¿Necesitáis alguna ayuda?");
		link.l2.go = "prihod";
		if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
		{
			link.l3 = RandPhraseSimple("Padre", "Padre") + ", quiero hablar contigo sobre asuntos financieros."; //(пересылка в кредиты)
			link.l3.go = "LoanForAll";
		}
		// -->
		if (stf(pchar.Health.HP) < 60.0)
		{
			link.l4 = "Necesito curación.";
			link.l4.go = "healthAdd_1";
		}

		// квест мэра - на связь с нашим шпионом
		if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "")
		{
			link.l7 = RandPhraseSimple("Padre", "Santo Padre") + ", estoy aquí por solicitud de un hombre. Su nombre es gobernador " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".";
			link.l7.go = "IntelligenceForAll";
		}
		//--> Jason Церковная депеша
		if (CheckAttribute(pchar, "GenQuest.Monkletter") && npchar.city == pchar.GenQuest.Monkletter.City)
		{
			link.l10 = "Padre, le he traído papeles de un monje en la ciudad de " + XI_ConvertString("Colony" + pchar.GenQuest.Monkletter.StartCity) + ".";
			link.l10.go = "Monkletter";
		}
		//<-- Церковная депеша
		//--> Jason Доставка молитвенников
		if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "go" && sti(npchar.nation) == sti(pchar.GenQuest.Churchbooks.Nation) && npchar.city != pchar.GenQuest.Churchbooks.StartCity)
		{
			link.l11 = "Padre, vine de la colonia de " + XI_ConvertString("Colony" + pchar.GenQuest.Churchbooks.StartCity) + "  La iglesia necesita más libros de oraciones, y el monje sugirió que hablara con usted al respecto.";
			link.l11.go = "Churchbooks";
		}
		if (CheckAttribute(pchar, "GenQuest.Churchbooks") && pchar.GenQuest.Churchbooks == "return" && npchar.city == pchar.GenQuest.Churchbooks.StartCity)
		{
			link.l11 = "Padre, he traído los libros de oraciones para su parroquia.";
			link.l11.go = "Churchbooks_2";
		}
		//<-- Доставка молитвенников
		link.l99 = "He cambiado de opinión, tengo mucho que hacer.";
		link.l99.go = "exit";
		break;

	case "prihod":
		if (!CheckAttribute(PChar, "GenQuest.ChurchQuest_1.StartQuest") && !CheckAttribute(PChar, "GenQuest.ChurchQuest_2.StartQuest") && NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam != iMonth && NPChar.GenQuest.ChurchQuest_1.GiveQuestDay != lastspeak_date && NPChar.location != "Panama_church" && rand(5) == 1)
		{
			dialog.text = "Eso es estupendo. Y aún así, en estos tiempos sombríos, " + GetSexPhrase("hijo mío", "hija mía") + ", no todos los visitantes del templo pueden ser útiles para nuestra Madre Iglesia.";
			link.l1 = LinkRandPhrase("Padre", "Padre", "Padre") + ", soy un verdadero cristiano, y mis intenciones de servir a nuestra Santa Madre Iglesia son las más sinceras." + GetSexPhrase(" ¿Quién la apoyará, si no su leal caballero, como yo?", "") + "";
			link.l1.go = "GenQuest_Church_1_Start_1";
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth; // Предлагает квест не чаще раза в месяц
		}
		else
		{
			NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date; // Если не дал сегодня, то токо на след день.
		}
		dialog.text = "Todo está tranquilo en la parroquia hasta ahora, " + GetSexPhrase("hijo mío", "hija mía") + "Gracias por la oferta.";
		link.l2 = "Bueno, si todo está bien, supongo que seguiré con mis asuntos.";
		link.l2.go = "exit";
		DeleteAttribute(npchar, "quest.add");
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDay = lastspeak_date; // Если не дал сегодня, то токо на след день.
		break;

	// Church GenQuest_1 -->
	case "GenQuest_Church_1_Start_1":
		dialog.text = "Bueno, tengo una misión delicada, que requeriría no solo pureza de intenciones, sino también gran valentía y considerable discreción...";
		link.l1 = LinkRandPhrase("Padre", "Padre", "Padre") + ", estaré feliz de brindarte cualquier servicio, ¡incluso si para este propósito tengo que dirigirme directamente al infierno! Que Dios me perdone por mis palabras impías.";
		link.l1.go = "GenQuest_Church_1_Start_2";
		break;

	case "GenQuest_Church_1_Start_2":
		PChar.GenQuest.ChurchQuest_1.QuestTown = NPChar.City;
		Church_GenQuest1_InitStartParam(NPChar);
		dialog.text = "¡Oh! Bien... Pero, de nuevo, esto es un asunto muy delicado... Hace algún tiempo el padre superior " + PChar.GenQuest.ChurchQuest_1.ToName + " de " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen") + " en " + XI_ConvertString(PChar.GenQuest.ChurchQuest_1.ToIsland + "Voc") + "tomó prestados algunos trabajos teológicos y manuscritos antiguos de la biblioteca de la iglesia para mí durante un tiempo. Porque la solicitud fue apoyada por la insistencia del arzobispo de no impedir la distribución del encantador brillo del conocimiento, no pude negarme, aunque supuse que las dificultades de los viajes por mar no le permitirían devolver los manuscritos a tiempo... ¿Podrías ayudarme a resolver este problema?";
		link.l1 = "Me temo, " + LinkRandPhrase("Padre", "Padre", "Santo Padre") + ", que no podré hacer eso por ti. Este es un asunto muy delicado, y solo un verdadero diplomático tendría éxito en resolverlo.";
		link.l1.go = "exit";
		link.l2 = LinkRandPhrase("Padre", "Padre", "Padre") + ", tu misión no me parece demasiado complicada. Me dirigiré allí de inmediato.";
		link.l2.go = "GenQuest_Church_1_Start_3";
		break;

	case "GenQuest_Church_1_Start_3": // Квест взят
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		PChar.GenQuest.ChurchQuest_1.StartQuest = true;
		PChar.GenQuest.ChurchQuest_1.PriestName = NPChar.name;
		PChar.GenQuest.ChurchQuest_1.Nation = sti(NPChar.nation);
		PChar.GenQuest.ChurchQuest_1.AskOwner = true;
		sQuestTitle = NPChar.City + "ChurchGenQuest1";
		ReOpenQuestHeader(sQuestTitle);
		AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "1");
		AddQuestUserDataForTitle(sQuestTitle, "sCity", XI_ConvertString("Colony" + NPChar.City + "Gen"));
		AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", ""));
		AddQuestUserData(sQuestTitle, "sName", NPChar.name);
		AddQuestUserData(sQuestTitle, "sOwnerCity", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.ToColony + "Gen"));
		break;

	case "GenQuest_Church_1_Dialog_1":
		if (CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2A_Scene")) // Сцена 2а
		{
			dialog.text = "¡Oh! Sí... De hecho, ahora recuerdo... Pero, " + GetSexPhrase("hijo mío", "hija mía") + ", ¡estos tesoros son más de naturaleza espiritual que material! ¡Ya han ayudado enormemente a mis feligreses y podrían seguir haciéndolo en el futuro!";
			link.l1 = "Pero, " + LinkRandPhrase("Padre", "Padre", "Padre") + ", los feligreses del Padre " + PChar.GenQuest.ChurchQuest_1.PriestName + " también necesitan salvación, y sin estas obras, carecerá del apoyo de los pilares de la teología, y sus sermones carecerán de inspiración.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_1";
		}
		else // Сцена 2б-а и 2б-б
		{
			dialog.text = "¡Oh, sí!.. ¡En efecto...!" + GetSexPhrase("Hijo mío", "Hija mía") + ", ¡estos tesoros son más de naturaleza espiritual que material! Ya han ayudado enormemente a mis feligreses, así que, para mi ignominia, he 'olvidado' devolverlos a su legítimo propietario...";
			link.l1 = "En efecto, " + RandPhraseSimple("Padre", "Padre", "Padre") + ", en efecto. Por eso Padre " + PChar.GenQuest.ChurchQuest_1.PriestName + " me pidió que le entregara estos libros personalmente.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2";
		}
		break;

	case "GenQuest_Church_1_Dialog_1_1": // Сцена 2а
		dialog.text = "Entiendo, hijo mío, pero ¿acaso no oramos a nuestro Señor cada día: 'y perdónanos nuestras ofensas, así como nosotros perdonamos a los que nos ofenden'? Y la iglesia de " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + " más rico que mi modesta parroquia.";
		link.l1 = "Tienes toda la razón, Padre, pero acabo de recordar otras líneas de la Sagrada Escritura: 'no busques un camino fácil, porque es allí donde el Diablo nos acecha, y su voz es aún más sutil y la tentación aún más fuerte, cuanto más fácil sea el camino!' Y padre " + PChar.GenQuest.ChurchQuest_1.PriestName + " ya iba a enviar un mensaje sobre tu olvidadizo comportamiento al arzobispo, apenas lo disuadí de ello.";
		link.l1.go = "GenQuest_Church_1_Dialog_1_1_1";
		break;

	case "GenQuest_Church_1_Dialog_1_1_1":
		dialog.text = "¿A-A-Al arzobispo?! ¡Por un asunto tan trivial!.. ¿Por qué? ¿De verdad? De todos modos, iba a enviar estas obras a mi amado hermano en Cristo; simplemente no había una buena oportunidad para entregárselas. Pero en ti, " + GetSexPhrase("hijo mío", "hija mía") + ", veo a un verdadero siervo digno de nuestro Señor. Aquí toma estos libros y manuscritos y por favor entrégalos al Padre " + PChar.GenQuest.ChurchQuest_1.PriestName + " sano y salvo. Y además, añade a eso mi más sincero agradecimiento.";
		link.l1 = "Por supuesto, " + LinkRandPhrase("Padre", "Padre", "Padre") + " . Por supuesto...";
		link.l1.go = "GenQuest_Church_1_Dialog_1_1_2";
		break;

	case "GenQuest_Church_1_Dialog_1_1_2":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		PChar.GenQuest.ChurchQuest_1.Complete.Short = true;
		sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
		AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "2");
		AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown));
		// Предмет "рукопись" -->
		AddItems(PChar, "Bible", 1);																				 // Даем рукописи
		items[FindItem("Bible")].Name = "itmname_ChurchGenQuest1Bible";												 // Меняем имя. Потом поменять обратно!
		ChangeItemDescribe("Bible", "itmdescr_ChurchGenQuest1Bible");												 // Меняем дескрайб. Потом поменять обратно!
		items[FindItem("Bible")].City = XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen"); // Переменная. Потом удалить!
																													 // <-- Предмет "рукопись"
		break;

	case "GenQuest_Church_1_Dialog_1_2": // Сцена 2б-а и 2б-б
		// Генерим кэпа -->
		sld = GetCharacter(NPC_GenerateCharacter("ChurchGenQuest1_Cap", "mercen_" + (rand(14) + 14), "man", "man", 15, NPChar.nation, -1, true, "quest"));
		FantomMakeCoolFighter(sld, 35, 40, 35, "blade_13", "pistol3", "grapeshot", 30);
		FantomMakeCoolSailor(sld, 7 + rand(2), "", CANNON_TYPE_CANNON_LBS16, 75, 70, 65);
		sld.Abordage.Enable = false;
		sld.ShipEnemyDisable = true; // флаг не обижаться на выстрелы
		LAi_SetImmortal(sld, true);
		sld.Dialog.FileName = "GenQuests_Dialog.c";
		sld.Dialog.CurrentNode = "ChurchGenQuest_1_DeckDialog_1";
		Group_FindOrCreateGroup("ChurchGenQuest1_CapGroup");
		Group_AddCharacter("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
		Group_SetType("ChurchGenQuest1_CapGroup", "trade");
		Group_SetGroupCommander("ChurchGenQuest1_CapGroup", "ChurchGenQuest1_Cap");
		Group_SetTaskNone("ChurchGenQuest1_CapGroup");
		Group_LockTask("ChurchGenQuest1_CapGroup");
		PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
		PChar.GenQuest.ChurchQuest_1.CurPortManColony = "";
		PChar.GenQuest.ChurchQuest_1.CapFullName = GetFullname(sld);
		PChar.GenQuest.ChurchQuest_1.CapShipName = sld.Ship.Name;
		PChar.GenQuest.ChurchQuest_1.NoCapColony = NPChar.city;
		PChar.GenQuest.ChurchQuest_1.CapColony = GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown);
		// <-- Генерим кэпа

		if (CheckAttribute(PChar, "GenQuest.ChurchQuest_1.2BA_Scene")) // Сцена 2б-а
		{
			dialog.text = "Pero, " + GetSexPhrase("hijo mío", "hija mía") + "... Verás, el asunto es que la semana pasada conocí a un capitán del navío '" + sld.Ship.Name + "', donde fui llamado para administrar la comunión de un marinero moribundo. Para mi gran alegría, capitán " + GetFullName(sld) + " me dijo que iba a " + XI_ConvertString("Colony" + GetColonyExpect2Colonies(NPChar.city, PChar.GenQuest.ChurchQuest_1.QuestTown)) + ". Y aunque no garantizó ninguna condición, aún así accedió a ayudar y me aseguró que el puerto de " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + " ciertamente visitará. Así que aproveché esta oportunidad, envié libros con ese buen hombre y entregué su destino futuro al Señor.";
			link.l1 = "¿Hmm, estás seguro de que se puede confiar en este capitán? ¿Se dio cuenta del valor de las obras que se le confiaron y de la importancia de esta misión?";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_1";
		}
		else // Сцена 2б-б
		{
			dialog.text = "Oh, " + GetSexPhrase("hijo mío", "hija mía") + "¡Llegas con varias horas de retraso! Ya he enviado los libros del Padre " + PChar.GenQuest.ChurchQuest_1.PriestName + " con capitán " + PChar.GenQuest.ChurchQuest_1.CapFullName + ". Esta mañana, ese hombre temeroso de Dios ha venido a confesarse y mencionó que hoy su navío iba a zarpar hacia " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.CapColony) + ". Y aunque el señor capitán no garantizó ningún término, aún así accedió a ayudar y me aseguró que el puerto de " + XI_ConvertString("Colony" + PChar.GenQuest.ChurchQuest_1.QuestTown + "Gen") + " ciertamente visitará.";
			link.l1 = LinkRandPhrase("Padre", "Padre", "Padre") + "... ¿estás seguro de que se puede confiar en este capitán? Y también quiero saber cómo se llama su barco.";
			link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_1";
		}
		break;

	case "GenQuest_Church_1_Dialog_1_2_1": // 2б-а
		dialog.text = "Confío en la gente, " + GetSexPhrase("hijo mío", "hija mía") + ", cada uno de nosotros es creado a imagen y semejanza de nuestro Señor, ¡y Su fuego sagrado arde en cada alma!";
		link.l1 = "Uf. Ese es un argumento de peso, sin duda. Bueno... Entonces bendíceme, Padre, y deséame suerte en mi búsqueda de ese capitán.";
		link.l1.go = "GenQuest_Church_1_Dialog_1_2_1_1";
		break;

	case "GenQuest_Church_1_Dialog_1_2_1_1":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
		PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
		PChar.GenQuest.ChurchQuest_1.CapFullInfo = true; // Полная инфа о кэпе
		sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
		AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_1");
		AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
		AddQuestUserData(sQuestTitle, "sShipName", PChar.GenQuest.ChurchQuest_1.CapShipName);
		break;

	case "GenQuest_Church_1_Dialog_1_2_2_1":
		dialog.text = "Deberías confiar en la gente, " + GetSexPhrase("hijo mío", "hija mía") + ". En cuanto a su barco, no tengo nada que decir.";
		link.l1 = "¿Y has entregado manuscritos preciosos a algún capitán sin siquiera molestarte en saber el nombre de su barco?!!";
		link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_2";
		break;

	case "GenQuest_Church_1_Dialog_1_2_2_2":
		dialog.text = "Verás, " + GetSexPhrase("hijo mío", "hija mía") + ", capitán " + PChar.GenQuest.ChurchQuest_1.CapFullName + " es muy temeroso de Dios...";
		link.l1 = "Bueno, ya he oído eso.";
		link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_3";
		break;

	case "GenQuest_Church_1_Dialog_1_2_2_3":
		dialog.text = "Paciencia, " + GetSexPhrase("joven", "dama joven") + "¡ Capitán " + PChar.GenQuest.ChurchQuest_1.CapFullName + " es una persona muy temerosa de Dios, y hasta el día de hoy su embarcación llevaba un nombre que el clero nunca debería pronunciar ni siquiera en pensamiento, ¡y mucho menos en voz alta! Y hoy, durante su confesión, se lo señalé. Porque, como dice la Biblia, la pureza del alma debe ser preservada por nosotros, pecadores, más que la pureza del cuerpo, pues nuestro Señor niega Su Reino a los de lengua sucia...";
		link.l1 = "Ya veo, " + LinkRandPhrase("Padre", "Padre", "Padre") + "¡Entiendo!" + PChar.GenQuest.ChurchQuest_1.CapFullName + ", un notorio jugador y borracho, conocido en todo el Caribe, ¿decidió renombrar su viejo cascarón por tu sugerencia?";
		link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_4";
		break;

	case "GenQuest_Church_1_Dialog_1_2_2_4":
		dialog.text = "Eres muy perspicaz, " + GetSexPhrase("hijo mío", "hija mía") + ". No sé el nuevo nombre de este barco, pero ciertamente es algo exaltado.";
		link.l1 = "Oh, " + RandPhraseSimple("Padre", "Padre", "Padre") + "... Gracias por todo. Y reza por mi alma pecadora...";
		link.l1.go = "GenQuest_Church_1_Dialog_1_2_2_5";
		break;

	case "GenQuest_Church_1_Dialog_1_2_2_5":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		PChar.GenQuest.ChurchQuest_1.AskPortMan = true;
		PChar.GenQuest.ChurchQuest_1.AskPortMan_InColony = NPChar.city;
		sQuestTitle = PChar.GenQuest.ChurchQuest_1.QuestTown + "ChurchGenQuest1";
		AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "3_2");
		AddQuestUserData(sQuestTitle, "sCapName", PChar.GenQuest.ChurchQuest_1.CapFullName);
		break;

	case "GenQuest_Church_1_Complete_1":
		dialog.text = "¡Oh, hijo mío! He estado rezando fervientemente, ¡y todo parece haberse resuelto de la mejor manera posible! Por tu ayuda y fe, " + GetSexPhrase("hijo mío", "hija mía") + ", el paraíso y el canto angelical ciertamente estarán esperando...";
		link.l1 = RandPhraseSimple("Padre.", "Padre.") + ", no voy a encontrarme con San Pedro pronto, Dios no lo quiera. En cuanto a los vivos, requieren muchas cosas materiales además de promesas de dicha celestial...";
		link.l1.go = "GenQuest_Church_1_Complete_2";
		break;

	case "GenQuest_Church_1_Complete_2":
		dialog.text = "Sí, sí, " + GetSexPhrase("hijo mío", "hija mía") + ", por supuesto. Te recompensaré merecidamente. Toma esto y recuerda que nuestro Señor castiga a aquellas almas necias, que ansían demasiado las bendiciones terrenales y adoran al diablo amarillo.";
		link.l1 = "Gracias, " + LinkRandPhrase("Padre", "Padre", "Santo Padre") + ". Por favor, toma tus libros y manuscritos tan esperados y reza por mi alma pecadora... ¡Adiós!";
		link.l1.go = "GenQuest_Church_1_Complete_3";
		break;

	case "GenQuest_Church_1_Complete_3":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		RemoveItems(PChar, "Bible", 1);
		items[FindItem("Bible")].Name = "itmname_bible";
		BackItemDescribe("Bible");
		DeleteAttribute(items[FindItem("Bible")], "City");
		ChangeCharacterComplexReputation(PChar, "nobility", 5);
		AddCharacterExpToSkill(PChar, "Leadership", 50); // Бонус в авторитет
		AddCharacterExpToSkill(PChar, "Fortune", 50);	 // Бонус в удачу
		TakeNItems(pchar, "chest", 3 + hrand(1));
		PlaySound("interface\important_item.wav");
		sQuestTitle = NPChar.City + "ChurchGenQuest1";
		characters[GetCharacterIndex("ChurchGenQuest1_Cap")].LifeDay = 0;
		Group_DeleteGroup("ChurchGenQuest1_CapGroup");					// Трем кэпа
		PChar.Quest.Church_GenQuest1_ChangeCapitanLocation.over = true; // Завершаем, если вдруг осталось
		AddQuestRecordEx(sQuestTitle, "ChurchGenQuest1", "7");
		AddQuestUserData(sQuestTitle, "sSex", GetSexPhrase("", ""));
		AddQuestUserData(sQuestTitle, "sColony", XI_ConvertString("Colony" + NPChar.City + "Gen"));
		AddQuestUserData(sQuestTitle, "sSumm", FindRussianMoneyString(sti(PChar.GenQuest.ChurchQuest_1.AwardSumm)));
		CloseQuestHeader(sQuestTitle);
		DeleteAttribute(PChar, "GenQuest.ChurchQuest_1");
		NPChar.GenQuest.ChurchQuest_1.GiveQuestDateParam = iMonth;
		addLiberMisBonus();
		break;
		// <-- Church GenQuest_1

	case "healthAdd_1":
		if (stf(pchar.Health.maxHP) == 60.0) // отлично
		{
			dialog.text = "Tu salud es " + GetHealthNameMaxSmall(pchar) + ", y las heridas se cerrarán por sí solas. Solo necesitas evitar el derramamiento de sangre y cuidar tu salud.";
			link.l1 = "Gracias, eso sin duda es un alivio. Intentaré contenerme de peleas por algún tiempo.";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "Tu salud es " + GetHealthNameMaxSmall(pchar) + ", y aunque las heridas se cerrarán por sí solas, deberías cuidarlas.";
			link.l1 = "¿Qué se necesita para eso?";
			link.l1.go = "healthAdd_2";
		}
		link.l2 = "¿Y por qué empeora mi salud?";
		link.l2.go = "healthAdd_info";
		break;

	case "healthAdd_info":
		dialog.text = "Eso es muy sencillo, " + GetSexPhrase("hijo mío", "hija mía") + "  Sufres daño cada vez que eres herido. Eso no pasa sin dejar rastro. Tu salud empeora con cada herida, y, como resultado, te vuelves más débil. Tu tripulación, al ver a un capitán débil, pierde el respeto por ti. Sin embargo, te vuelves más cauteloso, y la capacidad de defenderte aumenta temporalmente. Descansar y minimizar las heridas te ayudará a mantenerte con fuerza.";
		link.l1 = "Gracias por la iluminación.";
		link.l1.go = "exit";
		break;

	case "healthAdd_2":
		dialog.text = "Oraciones y abstinencia de la violencia, " + GetSexPhrase("hijo mío", "hija mía") + ". Entonces el Señor te devolverá lo que has perdido.";
		link.l1 = "¿Pero podrías orar por mí?";
		link.l1.go = "healthAdd_3";
		link.l2 = "Entonces, ¿no hay forma? Hmm... Realmente me has tranquilizado, gracias.";
		link.l2.go = "exit";
		break;

	case "healthAdd_3":
		if (npchar.quest.HealthMonth != iMonth)
		{
			dialog.text = "¿Yo? Esto es probablemente posible. Pero tendrás que hacer una donación a nuestra parroquia.";
			link.l1 = pcharrepphrase("¿Cuánto?", "¡Con gusto! ¿Cuánto?");
			link.l1.go = "healthAdd_4";
			link.l2 = "Supongo que me las arreglaré solo...";
			link.l2.go = "exit";
		}
		else
		{
			dialog.text = "" + GetSexPhrase("Hijo mío", "Hija mía") + ", ya estoy rezando por tu bienestar. Estas oraciones ocuparán todo mi tiempo hasta el final del mes.";
			link.l1 = "Gracias, " + RandPhraseSimple("padre.", "Santo Padre.");
			link.l1.go = "exit";
		}
		break;

	case "healthAdd_4":
		dialog.text = "Cien mil pesos serán un pago suficiente por el milagro de la curación.";
		link.l1 = pcharrepphrase("¿Qué? ¡¡¿Estás totalmente loco?!! ¡Pagaría tal suma solo después de robar un par de iglesias!", "Eso es demasiado para mí. Dicen la verdad: la salud no se puede comprar con dinero.");
		link.l1.go = "exit";
		if (sti(pchar.Money) >= 100000)
		{
			link.l2 = "¡De acuerdo!";
			link.l2.go = "healthAdd_5";
		}
		break;

	case "healthAdd_5":
		AddMoneyToCharacter(pchar, -100000);
		AddCharacterMaxHealth(pchar, 4); // можно не проверять, тк явно меньше 51
		npchar.quest.HealthMonth = iMonth;
		dialog.text = "Bien. Tu salud mejorará un poco. Pero aún necesitas evitar escaramuzas y cuidarte bien, o este efecto se desvanecerá. Tendré que pasar un mes entero en oraciones por tu cuerpo perecedero.";
		link.l1 = "Gracias. Si algo sucede, vendré a verte de nuevo en un mes.";
		link.l1.go = "exit";
		break;

	// квест пожертвования хозяйки борделя
	case "HostessChurch":
		dialog.text = "¿Y quién es esa alma caritativa que dona el dinero?";
		link.l1 = "Hum... Esa es la madame del burdel.";
		link.l1.go = "HostessChurch_call";
		link.l2 = "Preferiría mantener los nombres en secreto. Puede ser una donación anónima, ¿verdad?";
		link.l2.go = "HostessChurch_notCall";
		pchar.questTemp.different = "HostessChurch_return"; // флаг на возвращение
		break;

	case "HostessChurch_call":
		if (isBadReputation(pchar, 5))
		{
			if (rand(100) < GetCharacterSkill(pchar, "Fortune")) // рендом вешаем на удачу
			{
				dialog.text = "Eres un pecador, ¿y aún así pides? Más te vale pensar primero en tu alma, de hecho, ¡todos compareceremos ante el Señor!";
				link.l1 = "Eso es cierto. Espero que nuestro Señor sea misericordioso conmigo... Entonces, ¿qué hay de la donación?";
				link.l1.go = "HostessChurch_ok";
			}
			else
			{
				dialog.text = "¡Apártate de mí, Satanás!!! ¡Toma tu dinero impío y vete!";
				link.l1 = "¿Cómo es eso, Padre?! Vinimos a usted con el corazón abierto, y usted...";
				link.l1.go = "HostessChurch_bad";
			}
		}
		else
		{
			if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma")) // рендом вешаем на харизму
			{
				dialog.text = "Me alegra que estés ayudando a los pecadores a encontrar su camino hacia nuestro Señor. ¡Por ello serás recompensado en el Cielo!";
				link.l1 = "¡Eso sería genial! Entonces, ¿qué hay de la donación?";
				link.l1.go = "HostessChurch_ok";
			}
			else
			{
				dialog.text = "No puedo aceptar dinero conseguido en pecado. Devuélvelo a esa mujer caída, " + GetSexPhrase("hijo mío", "hija mía") + " Nadie puede encontrar el camino hacia Dios a través del dinero.";
				link.l1 = "Es una lástima que la rechaces. Una verdadera lástima.";
				link.l1.go = "HostessChurch_bad_1";
			}
		}
		break;

	case "HostessChurch_notCall":
		if (rand(10) < GetCharacterSPECIAL(pchar, "Charisma"))
		{
			dialog.text = "Tomar este dinero, sin siquiera saber de dónde vino...";
			link.l1 = "Sí, padre, exactamente. ¡Por favor, acepte esta contribución, hecha de corazón!";
			link.l1.go = "HostessChurch_ok_1";
		}
		else
		{
			dialog.text = "¿Tomar este dinero, sin siquiera saber de dónde vino? ¡¿Estás loco?! ¡Y qué si este dinero está manchado de sangre!";
			link.l1 = "Padre, todo dinero está manchado con sangre...";
			link.l1.go = "HostessChurch_bad_2";
		}
		break;

	case "HostessChurch_ok":
		dialog.text = "Lo acepto, " + GetSexPhrase("hijo mío", "hija mía") + "Ve y dile eso a tu mujer caída.";
		link.l1 = "Está bien, padre. Gracias.";
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
		AddCharacterExpToSkill(pchar, "Fortune", 20);
		// флаг удачная или неудачная попытка дачи
		characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;

	case "HostessChurch_ok_1":
		dialog.text = "Lo acepto, " + GetSexPhrase("hijo mío", "hija mía") + "Cuéntale a este donante tuyo sobre ello.";
		link.l1 = "Está bien, padre. Gracias.";
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, -sti(pchar.questTemp.different.HostessChurch.money));
		AddCharacterExpToSkill(pchar, "Fortune", 20);
		// флаг удачная или неудачная попытка дачи
		characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "yes";
		break;

	case "HostessChurch_bad":
		dialog.text = "¡Sal de aquí, vástago del Infierno, y no te atrevas a mostrar tu rostro aquí de nuevo!";
		link.l1 = "Je, como desees.";
		link.l1.go = "exit";
		AddCharacterExpToSkill(pchar, "Leadership", 50);
		npchar.quest.BadMeeting = lastspeak_date;
		// флаг удачная или неудачная попытка дачи
		characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;

	case "HostessChurch_bad_1":
		dialog.text = "Esta es mi decisión. Ve en paz, " + GetSexPhrase("hijo mío", "hija mía") + ".";
		link.l1 = "Adiós, padre.";
		link.l1.go = "exit";
		AddCharacterExpToSkill(pchar, "Leadership", 30);
		// флаг удачная или неудачная попытка дачи
		characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;

	case "HostessChurch_bad_2":
		dialog.text = "¿Eso es lo que piensas, blasfemo?! ¡Sal del templo de inmediato y no te atrevas a mostrar tu rostro aquí de nuevo!";
		link.l1 = "Oh, ¿de veras? No importa, me voy...";
		link.l1.go = "exit";
		AddCharacterExpToSkill(pchar, "Leadership", 40);
		npchar.quest.BadMeeting = lastspeak_date;
		// флаг удачная или неудачная попытка дачи
		characters[GetCharacterIndex(pchar.questTemp.different.HostessChurch.city + "_Hostess")].questChurch = "no";
		break;

	//--> Jason Церковная депеша
	case "Monkletter":
		if (CheckAttribute(pchar, "GenQuest.Monkletter.Late"))
		{
			dialog.text = "Casi había perdido la esperanza de volver a ver estos documentos. ¿Por qué tardaste tanto, hijo mío?";
			link.l1 = "Fueron... desarrollos imprevistos, Padre.";
			link.l1.go = "Monkletter_1";
		}
		else
		{
			dialog.text = "He estado esperando estos documentos, hijo. Gracias por la pronta entrega. Por favor, acepta estas monedas y ve con mi bendición.";
			link.l1 = "Gracias, Padre. ¡Fue un placer ayudar a la Santa Iglesia!";
			link.l1.go = "Monkletter_3";
		}
		break;

	case "Monkletter_1":
		dialog.text = "Todos estamos en manos de Dios, hijo mío... El hombre propone, pero Dios dispone. Entrégame estos papeles y ve en paz.";
		link.l1 = "Aquí tienes, padre. ¡Todo lo mejor para ti!";
		link.l1.go = "Monkletter_2";
		break;

	case "Monkletter_2":
		DialogExit();
		RemoveItems(PChar, "letter_church", 1); // заменить на нужный
		AddQuestRecord("Monkletter", "2");
		CloseQuestHeader("Monkletter");
		ChangeCharacterComplexReputation(pchar, "nobility", -1);
		DeleteAttribute(pchar, "GenQuest.Monkletter");
		break;

	case "Monkletter_3":
		dialog.text = "La bendición de Dios, hijo mío. ¡Que el Todopoderoso vele por ti en tus viajes!";
		link.l1 = "Adiós, Padre.";
		link.l1.go = "Monkletter_4";
		break;

	case "Monkletter_4":
		pchar.quest.Monkletter_Over.over = "yes"; // снять таймер
		DialogExit();
		RemoveItems(PChar, "letter_church", 1); // заменить на нужный
		AddQuestRecord("Monkletter", "3");
		CloseQuestHeader("Monkletter");
		TakeNItems(pchar, "gold_dublon", 10 + rand(5));
		ChangeCharacterComplexReputation(pchar, "nobility", 1);
		ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 5);
		AddCharacterExpToSkill(pchar, "Leadership", 50);
		AddCharacterExpToSkill(pchar, "Fortune", 50);
		DeleteAttribute(pchar, "GenQuest.Monkletter");
		addLiberMisBonus();
		break;
	//<-- Церковная депеша

	//--> Jason Доставить молитвенники
	case "Churchbooks":
		dialog.text = "Te han enviado a llevarse libros de oraciones de nosotros, para la iglesia de " + XI_ConvertString("Colony" + pchar.GenQuest.Churchbooks.StartCity + "Gen") + "¿Bien? Tengo un paquete con treinta libros de oraciones. Tómalo, hijo mío.";
		link.l1 = "Gracias, padre. ¡Adiós!";
		link.l1.go = "Churchbooks_1";
		break;

	case "Churchbooks_1":
		dialog.text = "¡Que el Señor vele por ti en tus viajes! Ve en paz...";
		link.l1 = "...";
		link.l1.go = "exit";
		AddQuestRecord("Churchbooks", "2");
		pchar.GenQuest.Churchbooks = "return";
		GiveItem2Character(pchar, "prayer_book"); // поставить соотв.предмет
		break;

	case "Churchbooks_2":
		if (CheckAttribute(pchar, "GenQuest.Churchbooks.Late"))
		{
			dialog.text = "Gracias por tu ayuda, hijo mío, aunque llegó con algo de retraso.";
			link.l1 = "Me retrasaron acontecimientos imprevistos, Padre.";
			link.l1.go = "Churchbooks_3";
		}
		else
		{
			dialog.text = "Gracias por tu ayuda, hijo mío. Has traído estos libros justo a tiempo. Por favor, acepta este amuleto santificado como recompensa, te salvará del peligro en la hora más oscura.";
			link.l1 = "Gracias, Padre. ¡Fue un placer ayudar a la Santa Iglesia!";
			link.l1.go = "Churchbooks_4";
		}
		break;

	case "Churchbooks_3":
		dialog.text = "Todo está en manos de Dios, hijo mío. ¡Ve en paz!";
		link.l1 = "Adiós, padre.";
		link.l1.go = "exit";
		RemoveItems(PChar, "prayer_book", 1); // заменить на нужный
		AddQuestRecord("Churchbooks", "3");
		CloseQuestHeader("Churchbooks");
		DeleteAttribute(pchar, "GenQuest.Churchbooks");
		break;

	case "Churchbooks_4":
		dialog.text = "La bendición de Dios, hijo mío. ¡Que el Todopoderoso te proteja de todo mal en tus caminos!";
		link.l1 = "Adiós, Padre.";
		link.l1.go = "Churchbooks_5";
		break;

	case "Churchbooks_5":
		pchar.quest.Churchbooks_Over.over = "yes"; // снять таймер patch-5
		DialogExit();
		RemoveItems(PChar, "prayer_book", 1); // заменить на нужный
		GiveItem2Character(pchar, pchar.GenQuest.Churchbooks.Item);
		Log_Info("Has recibido '" + XI_ConvertString(pchar.GenQuest.Churchbooks.Item) + "'");
		AddQuestRecord("Churchbooks", "4");
		CloseQuestHeader("Churchbooks");
		ChangeCharacterComplexReputation(pchar, "nobility", 1);
		ChangeCharacterNationReputation(pchar, sti(npchar.Nation), 1);
		AddCharacterExpToSkill(pchar, "Leadership", 50);
		AddCharacterExpToSkill(pchar, "Fortune", 50);
		DeleteAttribute(pchar, "GenQuest.Churchbooks");
		addLiberMisBonus();
		break;
	}
}

void ChurchGenQuest2_RemoveCup()
{
	RemoveItems(PChar, "Bible", 1);
	ref rItem = ItemsFromID("Bible");
	DeleteAttribute(rItem, "City");
	rItem.Weight = 2;
	rItem.Name = "itmname_Bible";
	rItem.picIndex = 6;
	rItem.picTexture = "ITEMS_9";
	BackItemDescribe("Bible");
}

void Church_GenQuest1_InitStartParam(ref chr)
{
	string sColony = SelectNotEnemyColony(chr);
	PChar.GenQuest.ChurchQuest_1.IslandId = colonies[FindColony(PChar.GenQuest.ChurchQuest_1.QuestTown)].Island;
	PChar.GenQuest.ChurchQuest_1.ToColony = sColony;
	PChar.GenQuest.ChurchQuest_1.ToIsland = colonies[FindColony(sColony)].Island;
	PChar.GenQuest.ChurchQuest_1.ToName = characters[GetCharacterIndex(sColony + "_Priest")].Name;

	// Чтоб жизнь медом не казалась... Какие сцены будут в квесте, определяем в самом начале.
	int iRand = Rand(2);
	switch (iRand)
	{
	case "0":
		PChar.GenQuest.ChurchQuest_1.2A_Scene = true;
		Log_TestInfo("Church generator 1: key scene - 2A (simplemente recoge el manuscrito del sacerdote).");
		break;

	case "1":
		PChar.GenQuest.ChurchQuest_1.2BA_Scene = true;
		Log_TestInfo("Church generator 1: key scene - 2B-A (búsqueda de un capitán. Hay información completa sobre él).");
		break;

	case "2": // Этот флаг уже не проверяем, т.к. если нет тех, что выше, по-любому есть этот
		PChar.GenQuest.ChurchQuest_1.2BB_Scene = true;
		Log_TestInfo("Church generator 1: key scene - 2B-B (búsqueda de un capitán. Se desconoce el nombre del barco).");
		break;
	}
}
