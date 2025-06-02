#include "DIALOGS\%language%\Common_Duel.c"			   //navy
#include "DIALOGS\%language%\Rumours\Common_rumours.c" //homo 25/06/06
void ProcessDialogEvent()
{
	ref NPChar, d;
	aref Link, Diag;
	string NPC_Meeting, TempInfoCharacterID_1, TempInfoCharacterID_2, sQuestTitle, sStr;
	int DonationSize;

	// Warship 18.05.08
	int iLa_Puesta; // La puesta - это ставка по-испански

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makeref(d, Dialog);
	makearef(Diag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, Diag); // homo 25/06/06
	ProcessDuelDialog(NPChar, Link, Diag);		   // navy

	int iEnemyDice, iPCDice;
	int d1, d2, d3, d4;
	bool ok;
	ref sld;

	if (npchar.quest.Meeting != LastSpeakDate())
	{
		npchar.quest.Meeting = LastSpeakDate();
		npchar.money = 100 + rand(10) * makeint(50 * sti(PChar.rank) * (10.0 / MOD_SKILL_ENEMY_RATE));
		if (sti(npchar.money) < 150)
			npchar.money = 150;
		if (bBettaTestMode)
		{
			Dialog.CurrentNode = "Beta_test";
		}
	}
	switch (Dialog.CurrentNode)
	{
	// -----------------------------------Диалог первый - первая встреча
	case "exit":
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		break;

	case "Beta_test":
		dialog.text = "Selección de tipo de borracho (beta)";
		link.l1 = "Borracho";
		link.l1.go = "Beta_test_alc";
		link.l2 = "Jugador de cartas";
		link.l2.go = "Beta_test_card";
		link.l3 = "Jugador de dados";
		link.l3.go = "Beta_test_dice";
		break;

	case "Beta_test_alc":
		dialog.text = "Borracho seleccionado";
		link.l1 = "Continuar";
		link.l1.go = "First time";
		npchar.quest.last_theme = 0;
		npchar.quest.last_theme_game = 0;
		break;

	case "Beta_test_card":
		dialog.text = "Jugador de cartas (30% de resentirse de inmediato)";
		link.l1 = "Continuar";
		link.l1.go = "First time";
		npchar.quest.last_theme = 1;
		npchar.quest.last_theme_game = 0;
		break;

	case "Beta_test_dice":
		dialog.text = "Jugador de dados (30% de resentimiento inmediato)";
		link.l1 = "Continúa";
		link.l1.go = "First time";
		npchar.quest.last_theme = 1;
		npchar.quest.last_theme_game = 1;
		break;

	case "First time":
		if (LAi_grp_playeralarm > 0)
		{
			dialog.text = LinkRandPhrase("Puede que esté borracho, pero no soy un idiota. Si bebo contigo ahora, al día siguiente los soldados me atraparán. ¡De ninguna manera!", "¡No soy un enemigo de mi propio pueblo. ¡No beberé contigo!", "" + GetSexPhrase("compañero", "chica") + ", sería mejor que abandonaras este lugar mientras aún puedas...");
			link.l1 = RandPhraseSimple("Bueno, como desees...", "Je, sabes, no necesito emborracharme tanto. No es el momento adecuado para ello.");
			link.l1.go = "exit";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.HabitueSpeakDisable") && rand(1) == 0) // если дуэлянт то каждый второй посылает нафик
		{
			dialog.text = "Ja, señor" + GetSexPhrase("", "ita") + ", seguramente he oído hablar de ti, je-je. La gente en las tabernas dice que eres un provocador y un duelista. Digo que nuestra gente no se asusta fácilmente, pero nadie quiere morir por una copa de ron. Me resulta temible incluso sentarme cerca de ti, así que mejor paso.";
			link.l1 = LinkRandPhrase("¡Buen viaje, entonces!", "Pírate, mientras aún estoy de buen humor...", "¡Vete, vete! ¡Piérdete, comida de peces!");
			link.l1.go = "exit";
			link.l2 = "Espera, quería hacer una pregunta....";
			link.l2.go = "talk_habitue_duel";
			break;
		}

		ok = CheckFreeSitFront(npchar);

		dialog.text = "¡No te pares en mi luz, no puedo ver las moscas en la jarra!";
		link.l1 = "No estoy de pie...";
		link.l1.go = "exit";
		if (!chrDisableReloadToLocation)
		{
			switch (npchar.quest.last_theme)
			{
			case "0": // пьяный.
				dialog.text = "¡Hip! Ah, " + GetSexPhrase("camarada, seguro que pareces un viejo lobo de mar curtido", "muchacha, seguro que pareces un viejo lobo de mar experimentado") + "¿Quizás, me comprarías un vaso de ron?";
				link.l1 = "Puede que sea un viejo lobo de mar, pero eso no significa que vaya a comprar licor para la chusma...";
				link.l1.go = "exit";

				if (makeint(pchar.money) >= 100 && ok) // только старые острова окучены на сесть
				{
					link.l2 = "Me uniría a tu compañía con gusto.";
					link.l2.go = "talk_with_alchogol";
				}
				else
				{
					link.l2 = "¿Y por qué es eso?";
					link.l2.go = "talk_with_alchogol_song";
				}
				break;

			case "1":
				if (rand(3) != 1 && ok)
				{
					switch (sti(npchar.quest.last_theme_game))
					{
					case 0:
						// Игра в карты boal 20/05/05 -->
						if (CheckNPCQuestDate(npchar, "Card_date_begin"))
						{
							Dialog.text = RandPhraseSimple("¿Una partida de cartas, tal vez? ¡Un juego muy interesante!", "Sugiero jugar una partida de cartas. ¿Qué dices?");
							link.l1 = "¿Y por qué no? Claro, juguemos.";
							link.l1.go = "Cards_begin";
							link.l2 = "¿Y cuáles son las reglas de tu juego?";
							link.l2.go = "Cards_Rule";
							link.l3 = "No ahora.";
							link.l3.go = "exit";
						}
						else
						{
							Dialog.text = "No, ya no jugaré cartas contigo.";
							link.l1 = "Como usted dice.";
							link.l1.go = "exit";
						}
						// Игра в карты boal 20/05/05 <--
						break;

					case 1:
						// кости
						// Игра в кости boal 13/07/05 -->
						if (CheckNPCQuestDate(npchar, "Dice_date_begin"))
						{
							Dialog.text = RandPhraseSimple("¿Una partida de dados, tal vez? ¡Un juego muy interesante!", "Sugiero lanzar algunos dados. ¿Qué dirás?");
							link.l1 = "¿Y por qué no? Claro, juguemos.";
							link.l1.go = "Dice_begin";
							link.l2 = "¿Y cuáles son las reglas de tu juego?";
							link.l2.go = "Dice_Rule";
							link.l3 = "No ahora.";
							link.l3.go = "exit";
						}
						else
						{
							Dialog.text = "No, ya no voy a lanzar los dados contigo.";
							link.l1 = "Como usted diga.";
							link.l1.go = "exit";
						}
						// Игра в кости boal 13/07/05 <--
						// navy --> Дуэли
						if (CheckAttribute(NPchar, "Quest.DiceCheats") && sti(NPchar.Quest.DiceCheats) >= 1)
						{
							link.l9 = RandSwear() + "¡¡¡Estabas haciendo trampa!!!";
							link.l9.go = "outraged";
						}
						// navy <--
						break;
					}
				}
				else
				{
					dialog.text = RandPhraseSimple("¡Apártate de mi mesa! ¡Ahora!", " ¿Oh? ¿Qué? ¿Quién es ese? Hic... ¡Piérdete!");
					link.l1 = RandPhraseSimple("¡Beber condena tu alma pecadora! ¡Recobra tus sentidos!", "No seas grosero conmigo.");
					link.l1.go = "exit";
					link.l2 = RandPhraseSimple("¡Cuida tu lengua, perro! O te enseñaré buenos modales.", "¿Y si te golpeo en la cabeza ahora, supongo que eso te ayudará a sobrioarte?");
					link.l2.go = "tavern_keeper";
				}
				break;
			}
		}
		Diag.TempNode = "First time";
		break;

	case "talk_habitue_duel":
		dialog.text = "No te diré nada, señor" + GetSexPhrase("", "ita") + ". ¡Y no creo que nadie más vaya a hablar contigo, ya que eso siempre significa problemas. Pero la gente tiende a tener mala memoria, así que en un mes o dos podrían olvidarse de tu aventura, si no se las recuerdas una vez más, claro, ¡je-je! Adiós, desgraciad" + GetSexPhrase("o", "a") + ".";
		link.l1 = "Está bien...";
		link.l1.go = "exit";
		break;

	// карты -->
	case "Cards_Rule":
		dialog.text = CARDS_RULE;
		link.l1 = "Bueno, entonces comencemos...";
		link.l1.go = "Cards_begin";
		link.l3 = "No, no es para mí...";
		link.l3.go = "exit";
		break;

	case "Cards_begin":
		Diag.tempnode = "Cards_Node";
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		pchar.questTemp.friend_in_tavern = npchar.id;
		AddDialogExitQuest("alc");
		break;

	case "Cards_Node":
		Diag.tempNode = "first time";

		Dialog.text = "Primero definamos la apuesta entonces (introduce la apuesta).";
		link.l1 = "100";
		link.l1.edit = 1;
		link.l1.go = "Cards_Node_2";
		link.l3 = "Supongo que tengo que irme.";
		link.l3.go = "exit_sit";
		break;

	case "Cards_Node_2":
		iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
		if (!CheckCardsGameSmallRate())
		{
			dialog.text = "Eres un tramposo notorio. No voy a apostar contigo.";
			link.l1 = "¡Todo son mentiras! Bueno, lo que sea.";
			link.l1.go = "exit_sit";
			break;
		}

		if (sti(PCHar.Money) < sti(iLa_Puesta) * 3)
		{
			dialog.text = "Veo que estás pelado, " + GetSexPhrase("amigo", "cariño") + ". Vuelve cuando te hagas rico.";
			link.l1 = "Bien.";
			link.l1.go = "exit_sit";
			break;
		}

		if (sti(NPChar.Money) < sti(iLa_Puesta) * 3)
		{
			dialog.text = "Ya he perdido todo lo que tenía. Hoy no es mi día de suerte.";
			link.l1 = "Bien.";
			link.l1.go = "exit_sit";
			break;
		}
		else
		{
			if (sti(iLa_Puesta) < 50)
			{
				dialog.text = "¿Te estás riendo de mí o qué?! Jugando para " + iLa_Puesta + "¿¡ pesos?! ¡Juguemos por apuestas razonables, o me retiro!";
				link.l1 = "Sí, tienes razón. Necesitamos aumentar un poco la apuesta.";
				link.l1.go = "Cards_begin_2";
				link.l2 = "Cambié de opinión, no voy a jugar.";
				link.l2.go = "exit_sit";
				break;
			}

			if (sti(iLa_Puesta) > 1000)
			{
				dialog.text = "¿Jugando por tanto dinero? No, pasaré, a menos que cambiemos la apuesta.";
				link.l1 = "Sí, tienes razón. Necesitamos bajar un poco la apuesta.";
				link.l1.go = "Cards_begin_2";
				link.l2 = "De hecho, decidí no jugar en absoluto.";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "Está bien, juguemos por " + iLa_Puesta + " monedas.";
			link.l1 = "¡Reparte las cartas!";
			link.l1.go = "Cards_begin_go";
			pchar.GenQuest.Cards.npcharIdx = npchar.index;
			pchar.GenQuest.Cards.iRate = sti(iLa_Puesta);
			pchar.GenQuest.Cards.SitType = true;
		}
		break;

	case "Cards_begin_2":
		dialog.text = "¿Entonces cuál es la apuesta? (Ingresa apuesta)";
		link.l1 = "50";
		link.l1.edit = 1;
		link.l1.go = "Cards_Node_2";
		link.l2 = "Creo que no jugaré, después de todo...";
		link.l2.go = "exit_sit";
		break;

	case "Cards_begin_go":
		// анлим игры в день SetNPCQuestDate(npchar, "Card_date_begin");
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		LaunchCardsGame();
		break;
	// карты <--
	// КОСТИ -->
	case "Dice_Rule":
		dialog.text = DICE_RULE;
		link.l1 = "Bueno, comencemos entonces...";
		link.l1.go = "Dice_begin";
		link.l3 = "No, no es para mí...";
		link.l3.go = "exit";
		break;

	case "Dice_begin":
		Diag.tempnode = "Dice_Node";
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		pchar.questTemp.friend_in_tavern = npchar.id;
		AddDialogExitQuest("alc");
		break;

	case "Dice_Node":
		Diag.tempNode = "first time";
		Dialog.text = "Definamos la apuesta (introduce la apuesta).";
		link.l1 = "50";
		link.l1.edit = 1;
		link.l1.go = "Dice_Node_2";
		link.l3 = "Supongo que tengo que irme.";
		link.l3.go = "exit_sit";
		break;

	case "Dice_Node_2":
		iLa_Puesta = GetStrSmallRegister(dialogEditStrings[1]);
		if (!CheckDiceGameSmallRate())
		{
			dialog.text = "Eres un tramposo notorio. No tiraré los dados contigo.";
			link.l1 = "¡Todo son mentiras! Bueno, lo que sea.";
			link.l1.go = "exit_sit";
			break;
		}

		if (sti(pchar.Money) < sti(iLa_Puesta) * 6)
		{
			dialog.text = "Veo que estás pelado, " + GetSexPhrase("amigo", "cariño") + ". Regresa cuando te hagas rico.";
			link.l1 = "Bien.";
			link.l1.go = "exit_sit";
			break;
		}

		if (sti(npchar.Money) < sti(iLa_Puesta) * 6)
		{
			dialog.text = "Ya he perdido todo lo que tenía. Hoy no es mi día de suerte.";
			link.l1 = "Bien.";
			link.l1.go = "exit_sit";
			break;
		}
		else
		{
			if (sti(iLa_Puesta) < 50)
			{
				dialog.text = "¿Te estás riendo de mí o qué?! Jugando para " + iLa_Puesta + "¿Pesos por día?! Juguemos con apuestas razonables, ¡o me retiro!";
				link.l1 = "Sí, tienes razón. Necesitamos aumentar un poco la apuesta.";
				link.l1.go = "Dice_begin_2";
				link.l2 = "Cambié de opinión, no voy a jugar.";
				link.l2.go = "exit_sit";
				break;
			}

			if (sti(iLa_Puesta) > 1000)
			{
				dialog.text = "¿Jugando a los dados por tanto dinero? No, paso, a menos que cambiemos la apuesta.";
				link.l1 = "Sí, tienes razón. Necesitamos reducir un poco la apuesta.";
				link.l1.go = "Dice_begin_2";
				link.l2 = "De hecho, decidí no jugar en absoluto.";
				link.l2.go = "exit_sit";
				break;
			}
			dialog.text = "Está bien, juguemos por " + iLa_Puesta + " monedas por dado.";
			link.l1 = "¡Vamos a rodar!";
			link.l1.go = "Dice_begin_go";
			pchar.GenQuest.Dice.npcharIdx = npchar.index;
			pchar.GenQuest.Dice.iRate = sti(iLa_Puesta);
			pchar.GenQuest.Dice.SitType = true;
		}
		break;

	case "Dice_begin_2":
		dialog.text = "¿Entonces cuál es la apuesta? (Ingresa apuesta)";
		link.l1 = "50";
		link.l1.edit = 1;
		link.l1.go = "Dice_Node_2";
		link.l2 = "Creo que no jugaré, después de todo...";
		link.l2.go = "exit_sit";
		break;

	case "Dice_begin_go":
		// анлим игры в день SetNPCQuestDate(npchar, "Dice_date_begin");
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		LaunchDiceGame();
		break;
	// КОСТИ <--

	/////////////////////////////////////////////
	case "talk_with_alchogol_song":
		dialog.text = "Bueno, h-hic! Las cosas van bien. Hic! No ves que viene. Hi-ic! Este ron está bueno. Ron negro de Jamaica. ¡hic!\nAquí, pon y sirve!";
		link.l1 = "Está bien, ¿por qué no?";
		link.l1.go = "talk_with_alchogol_song_2";
		link.l2 = "Lo siento, amigo, tengo que irme.";
		link.l2.go = "exit";
		break;

	case "talk_with_alchogol_song_2":
		dialog.text = "Jarras y caras vienen y van... Hic... Hasta que caigo al suelo. Bebo todo el tiempo... ¡Hic! Dónde está el licor... Y cuál es la rima...";
		link.l1 = "El licor está aquí y las chicas están bien, todas quieren un bucanero, pero solo el ron parece ser mío.";
		link.l1.go = "talk_with_alchogol_song_3";
		link.l2 = "No tengo tiempo para esto.";
		link.l2.go = "exit";
		break;

	case "talk_with_alchogol_song_3":
		dialog.text = "¡Cuando estés triste, no intentes pensar, ven, y déjanos beber! Todo seguro estará bien, soy tu amigo, y tú eres el mío!";
		link.l1 = "Tener un amigo seguro es genial, cuando te vas él esperará, con un amigo no hay odio, pero cuando se acaba el ron solo hay debate. Así que bebamos mate, antes de que me vaya y llegue tarde...";
		link.l1.go = "exit";
		break;

	case "talk_with_alchogol":
		Diag.TempNode = "begin_sit";
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		pchar.questTemp.friend_in_tavern = npchar.id;
		AddDialogExitQuest("alc");
		break;

	case "begin_sit":
		Diag.TempNode = "first time";
		dialog.snd = "Voice\HADI\HADI028";
		dialog.text = LinkRandPhrase("¡Hic! ¡Ahora eso es mejor! ¡Seguro que es mejor! ¿Entonces? ¿Me comprarás algo de ron o qué?", "Siéntate, " + GetAddress_Form(npchar) + ", vamos a echar atrás una copa de buen viejo ron jamaiquino. Eso nunca es malo para la salud. Y si te interesa lo que está pasando, nunca encontrarás un lugar mejor que esta taberna, te lo aseguro. Algo de dinero, un par de copas de ron decente y sabrás lo que necesitabas saber, e incluso más, confía en un viejo cliente...", "Heh, por favor, siéntate, " + GetSexPhrase("mi buen amigo", "señorita") + ", vamos a tomar una copa... ¿Por qué no tomar una copa en buena compañía? Puedes escuchar muchas cosas interesantes si tienes paciencia y bebes despacio, a pequeños sorbos... Hay capitanes alardeando de sus aventuras, hay muchos otros divulgando cosas importantes, cuando ya no se controlan... Mucha gente pasa su tiempo allí, y muchos tienen algo que contar, créeme, " + GetSexPhrase("mi buen amigo", "Señorita") + ".");
		link.l1 = "¡Y por qué no! ¡Camarero! ¡Ron, para los dos!";
		link.l1.go = "sit_2";
		break;

	// Церковный генератор. Квест №2 -->
	case "Alcogol_GenQuest_Church_2_1":
		dialog.text = "¡Claro! ¿Has oído?... unos bandidos han saqueado la iglesia.";
		link.l1 = "Bueno, eso suena como piratas, ¿quién más podría...?";
		link.l1.go = "Alcogol_GenQuest_Church_2_2";
		DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskPeople");
		DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskBarmen");
		DeleteAttribute(PChar, "GenQuest.ChurchQuest_2.AskAlcash");
		break;

	case "Alcogol_GenQuest_Church_2_2":
		dialog.text = "¿Cuáles piratas? Fueron personas locales... Si fueran piratas, no habrían sabido cuándo las arcas de la iglesia estaban llenas. Y difícilmente se meterían en ese lío, de todos modos.";
		link.l1 = "Fueron muy valientes, sin embargo. Abrieron una endeble barra de la puerta...";
		link.l1.go = "Alcogol_GenQuest_Church_2_3";
		break;

	case "Alcogol_GenQuest_Church_2_3":
		dialog.text = "Ja, ja. Y también astutos. ¿Quién se expondría de tal manera?";
		link.l1 = "Verdad. Toda la parroquia estaba ahorrando dinero para donar a la iglesia, ¿y ahora estos tipos listos se hicieron una fortuna con ello? Seguramente serán atrapados. Todo el mundo los estará buscando ahora.";
		link.l1.go = "Alcogol_GenQuest_Church_2_4";
		break;

	case "Alcogol_GenQuest_Church_2_4":
		dialog.text = "Apenas. ¿Quién buscará eso? Acaban de robar la iglesia y abandonar el pueblo, se fueron con el viento. La selva es grande, muy grande, los buscarías allí hasta el día del juicio final. Y después de un par de meses, la gente simplemente lo olvidará todo, ¡anota mis palabras!";
		link.l1 = "No lo creo. Tales cosas no pueden ser perdonadas.";
		link.l1.go = "Alcogol_GenQuest_Church_2_5";
		break;

	case "Alcogol_GenQuest_Church_2_5":
		dialog.text = "La memoria de un hombre es como un bote con fugas. La gente olvidará y perdonará. ¡¿Pero Dios?! Él lo ve todo. A él es a quien debes temer. Te digo, hace diez años le pasó algo terrible a un viejo amigo mío. Él también faltaba al respeto al Creador, y casi se fue directo al diablo del mar...";
		link.l1 = "Lo siento amigo, tengo que irme. Hablaremos de ese compañero tuyo en otra ocasión. Nos vemos.";
		link.l1.go = "Alcogol_GenQuest_Church_2_6";
		break;

	case "Alcogol_GenQuest_Church_2_6":
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		AddDialogExitQuest("exit_sit");
		string sGenLocation = QuestGetGangLocation(PChar.GenQuest.ChurchQuest_2.QuestTown);
		PChar.GenQuest.ChurchQuest_2.QuestGangJungle = sGenLocation;
		SetFunctionLocationCondition("Church_GenQuest2_GenerateBandits", sGenLocation, false);
		locations[FindLocation(sGenLocation)].DisableEncounters = true;
		PChar.GenQuest.ChurchQuest_2.WayOfShortVariant = true; // Нужно для проверки при убийстве банды
		SetFunctionTimerConditionParam("Church_GenQuest2_TimeIsLeft", 0, 0, 1, MakeInt(24 - GetHour()), false);
		Log_TestInfo("Los bandidos que asaltaron la iglesia estarán en, " + sGenLocation + " Tiempo para buscarlos - 1 día");
		sQuestTitle = PChar.GenQuest.ChurchQuest_2.QuestTown + "ChurchGenQuest2";
		AddQuestRecordEx(sQuestTitle, "ChurchGenQuest2", "2");
		break;
		// <-- Церковный генератор. Квест №2
		//--> работорговец
	case "Jamaica_ratH_1":
		dialog.text = "¡Oh Francois! Claro, recuerdo a ese tipo... No, no lo sé. Pero, sabes, puedes preguntarle a nuestra camarera sobre él. Durante todo el tiempo que vivió aquí, ella pasó todas las noches con él. Una zorra es, eso es seguro. Tal vez él le había soltado algo a ella.";
		link.l1 = "Gracias por el consejo, compañero. Iré a hablar con ella.";
		link.l1.go = "exit_sit";
		pchar.questTemp.Slavetrader = "FindRatJamaica_W";
		break;

	case "EscapeSlave_Villemstad_H1":
		dialog.text = "Sí, cosas muy extrañas pueden suceder en alta mar a veces. En mi último viaje vi algo real-mente...";
		link.l1 = "Adelante, dime, solo no exageres demasiado. Te traeré más ron mientras tanto.";
		link.l1.go = "EscapeSlave_Villemstad_H2";
		break;

	case "EscapeSlave_Villemstad_H2":
		dialog.text = "Juro por Dios, noble" + GetSexPhrase("señor", "dama") + ". Lo he visto con mis propios ojos... Un barco estaba navegando, pero en lugar de marineros había unos enormes simios... o macacos... monos, ya sabes.";
		link.l1 = "¿¡Qué?! Dime, amigo, ¿también estás bebiendo en la guardia?";
		link.l1.go = "EscapeSlave_Villemstad_H3";
		break;

	case "EscapeSlave_Villemstad_H3":
		dialog.text = "¡Que me deje ciego si miento! ¿Nunca has oído hablar del camarón mono? ¡Joder, camarón ja-ja! ... El barco mono.";
		link.l1 = "¿Qué barco de monos?";
		link.l1.go = "EscapeSlave_Villemstad_H4";
		break;

	case "EscapeSlave_Villemstad_H4":
		dialog.text = "¡Oh-hoe, digo que lo vi con mis propios ojos. Estaba lloviendo a cántaros. No se veía nada, y luego el barco apareció de la nada. Velas desgarradas. Tenía su foque roto así como la vela mayor, ¡y maldita sea todo estaba roto! ¡Y sin embargo, estaba avanzando contra el viento!\nY había monos en su cubierta... muchos de ellos como... ¡colonia de focas! ¡Y un gorila puro estaba al timón! Nueve pies, camisa roja y dientes de tiburón en lugar de la cruz en su pecho... Los ojos son rojos, colmillos relucientes, nos vio y gritó algo...";
		link.l1 = "Estás mintiendo descaradamente, amigo. Sabes, puedes ver cosas cuando estás borracho. Lo próximo que me dirás es que ella era el Holandés Volador.";
		link.l1.go = "EscapeSlave_Villemstad_H5";
		break;

	case "EscapeSlave_Villemstad_H5":
		dialog.text = "No, ella no era holandesa. ¡Te estoy diciendo la verdad! Era una barca, y en la popa había una inscripción, " + pchar.questTemp.Slavetrader.ShipName + ".";
		link.l1 = "¡Maldita sea! Creo que sé de qué 'monos' estás hablando. De hecho, el ron puede soltar lenguas, solo hay que escuchar...";
		link.l1.go = "EscapeSlave_Villemstad_H6";
		break;

	case "EscapeSlave_Villemstad_H6":
		dialog.text = "¡Mira, te lo estaba diciendo! ¡Y no me creías!.. Bueno, tomemos una última copa, y estoy listo para irme.";
		link.l1 = "Bueno, gracias por una historia interesante. Tengo que irme. Buena suerte para ti, compañero.";
		link.l1.go = "exit_sit";
		Pchar.quest.Slavetrader_EscapeSlave.win_condition.l1 = "location";
		Pchar.quest.Slavetrader_EscapeSlave.win_condition.l1.location = pchar.questTemp.Slavetrader.Island.Shore;
		Pchar.quest.Slavetrader_EscapeSlave.function = "Slavetrader_EscapeSlaveInShore";
		AddQuestRecord("Slavetrader", "22_4");
		AddQuestUserData("Slavetrader", "sAreal", pchar.questTemp.SlavetraderAreal.add);
		pchar.questTemp.Slavetrader = "FindMayak";
		break;

	// Голландский Гамбит, против всех
	case "Lucas_Tavern":
		DelMarkInTavernHWIC();
		dialog.text = "No, capitán. La vida de un marinero no es para mí. Sabes, yo también solía tener un barco una vez, pero... Tuve un golpe de muy mala suerte.";
		link.l1 = "Escucha, he visto un barco inusual anclado,'Meifeng' es su nombre. Nunca he visto un barco como ese antes. ¿Quién es el dueño? Tal vez, ¿está en venta? Echaría un vistazo.";
		link.l1.go = "Lucas_Tavern_1";
		break;

	case "Lucas_Tavern_1":
		dialog.text = "¡Ja! Difícilmente, capitán. No creo que el chino le venda su barco a usted ni a nadie más.";
		link.l1 = "¿Un chino? ¿Hay chinos en Curazao? ¿Y hasta un capitán de su propio barco?";
		link.l1.go = "Lucas_Tavern_2";
		break;

	case "Lucas_Tavern_2":
		dialog.text = "Existe, como puedes ver. Pero este no es su barco, en realidad pertenece a la Compañía de Comercio. Dicen, mi señor Rodenburg, el vice director y ahora gobernador en funciones, lo posee.";
		link.l1 = "¿Así que, Matthias Beck se retiró?";
		link.l1.go = "Lucas_Tavern_3";
		break;

	case "Lucas_Tavern_3":
		dialog.text = "¡Ja! Mynheer, realmente deberías visitar la tierra más a menudo, o al menos preocuparte por las noticias. Matthias Beck fue destituido y encerrado tras las rejas hasta que se aclaren todas las circunstancias.";
		link.l1 = "¡No me digas! De hecho, estoy pasando demasiado tiempo en el mar. ¿Y cuándo ha ocurrido eso?";
		link.l1.go = "Lucas_Tavern_4";
		break;

	case "Lucas_Tavern_4":
		dialog.text = "De hecho, hace apenas un par de días. Una brigantina mensajera llegó al puerto. No estaba en la mejor forma, claramente participó en un combate feroz. El capitán fue directo a ver a mi señor Rodenburg con su informe, y en solo unas pocas horas Matthias Beck fue arrestado por mi señor Rodenburg y el comandante bajo sospecha de colaborar con el servicio de inteligencia inglés.";
		link.l1 = "Estás diciendo cosas terribles. ¿Cómo puede ser un gobernador de Curazao un espía inglés?";
		link.l1.go = "Lucas_Tavern_5";
		break;

	case "Lucas_Tavern_5":
		dialog.text = "Sinceramente, yo tampoco lo creo mucho. Escuché que pronto el director de la Compañía, el mismo Peter Stuyvesant, llegará aquí. Aparentemente, él personalmente conducirá la investigación.";
		link.l1 = "Entonces tienes razón. Puede ser arriesgado molestar a mi señor Rodenburg en este momento.";
		link.l1.go = "Lucas_Tavern_6";
		break;

	case "Lucas_Tavern_6":
		dialog.text = "¡Buen pensamiento, capitán! Más aún que 'Meifeng' está siendo cargada actualmente. Acaba de regresar del viaje a la costa sur de Tierra Firme, y pronto zarpará de nuevo. Y, te digo, cosas extrañas están sucediendo allí. Marinos holandeses y guardias de la Compañía fueron relevados de sus funciones, y se está formando otra tripulación. Y juro por todas las copas de ron que he bebido en mi vida, esos nuevos voluntarios son algo completamente diferente, todos piratas, bandidos y degolladores!";
		link.l1 = "¡Un milagro, ciertamente! ¡Qué lástima! Un barco tan bonito... Bueno, el destino decretó de otra manera... ¡Gracias por una historia interesante y por las noticias! ¡Fue un placer hablar contigo!";
		link.l1.go = "Lucas_Tavern_7";
		break;

	case "Lucas_Tavern_7":
		dialog.text = "¡Bueno, gracias por la compañía y el ron, capitán! ¡Vuelve a visitarnos alguna vez!";
		link.l1 = "¡Claro que sí!";
		link.l1.go = "exit_sit";
		AddQuestRecord("Holl_Gambit", "3-44");
		pchar.questTemp.HWIC.Self = "AttackMeifeng";
		// ставим прерывание на выход в море Мейфенг
		pchar.quest.HWIC_Meifeng.win_condition.l1 = "Timer";
		pchar.quest.HWIC_Meifeng.win_condition.l1.date.hour = sti(GetTime());
		pchar.quest.HWIC_Meifeng.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.HWIC_Meifeng.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.HWIC_Meifeng.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.HWIC_Meifeng.function = "CreateMeifengOnMap";
		if (bImCasual)
			NewGameTip("Modo exploración: el temporizador no está desactivado. ¡Cumple el plazo!");
		SetFunctionTimerCondition("QuestShipsTerms_Over", 0, 0, 12, false); // таймер
		pchar.quest.Meifeng_fail.over = "yes";								// снять прерывание
		Group_DelCharacter("Meifeng_Empty", "Longway");
		Group_DeleteGroup("Meifeng_Empty"); // удалить Мейфенг из порта
		break;

		// Jason --> поиск дезертира
	case "FindFugitiveHb":
		npchar.quest.fugitive = "true";
		if (npchar.location == pchar.GenQuest.FindFugitive.City + "_tavern" && sti(pchar.GenQuest.FindFugitive.Chance) == 2)
		{
			pchar.GenQuest.FindFugitive.Shore = SelectQuestShoreLocation();
			dialog.text = "¡Ja! ¿" + pchar.GenQuest.FindFugitive.Name + "? Lo conozco, lo conozco... Es poco sociable, ese colega tuyo. Un lobo solitario, por así decirlo. Navega en su bote largo a lo largo de la costa de la isla todo el día hasta la noche. La gente piensa que es un pescador, pero en realidad es un pescador de perlas... ¡Je-je! ¡Estoy condenadamente seguro!";
			link.l1 = "¡Heh! Entonces... ¿puedes decirme dónde encontrarlo?";
			link.l1.go = "FindFugitiveHb_1";
		}
		else
		{
			dialog.text = "¿" + pchar.GenQuest.FindFugitive.Name + "? No, te juro que nunca he oído hablar de él... Pero... ¡hic!... puedes preguntarle a nuestro cantinero, ¡él debe saberlo con seguridad!";
			link.l1 = "Hmm... Está bien, preguntaré un poco más. Bueno, compañero, gracias por la compañía. ¡Nos vemos!";
			link.l1.go = "exit_sit";
		}
		break;

	case "FindFugitiveHb_1":
		dialog.text = "¡Por supuesto, puedo! Cada mañana se le puede encontrar en la orilla, en " + XI_ConvertString(pchar.GenQuest.FindFugitive.Shore + "Gen") + ". Solo ven tan pronto como sea posible, de lo contrario zarpará y tendrás que esperar hasta la próxima mañana.";
		link.l1 = "¡Gracias! Me has ayudado mucho, ¡amigo! ¡Nos vemos!";
		link.l1.go = "exit_sit";
		pchar.GenQuest.FindFugitive.Chance = 3; // чтобы никто больше не говорил
		AddQuestRecord("MayorsQuestsList", "12-3");
		AddQuestUserData("MayorsQuestsList", "sShore", XI_ConvertString(pchar.GenQuest.FindFugitive.Shore + "Gen"));
		sld = characterFromId("Fugitive");
		LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, true);
		sld.dialog.currentnode = "Fugitive_shore";
		LAi_SetLoginTime(sld, 4.0, 6.0);
		ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.Shore, "goto", "goto1");
		break;
	//<-- поиск дезертира

	// Карибские нравы
	case "trial_spy":
		dialog.text = "Estaba rondando en nuestro astillero, preguntándole a los carpinteros de barcos sobre esto y aquello. Y eso es lo que le jugó una mala pasada. Algunas personas alertaron al comandante sobre personas sospechosas rondando en la ciudad, así que lo detuvo, y luego se descubrió que en realidad no era comerciante en absoluto.";
		link.l1 = "Supongo que, ¿iba a robar algún proyecto secreto de tu carpintero de barcos?";
		link.l1.go = "trial_spy_1";
		break;

	case "trial_spy_1":
		dialog.text = "¿Quién sabe? Pero estoy bastante seguro de que él estaba interesado en el galeón 'Alacantara' en primer lugar! ¡Hic! ¡Puedo jurarlo! Este barco está siendo equipado por el señor gobernador mismo, así que apuesto a que ese granuja intentó husmear algo sobre ella.";
		link.l1 = "¡Ja! Eso es bastante probable. Seguramente el gobernador la estará cargando con algo valioso...";
		link.l1.go = "trial_spy_2";
		break;

	case "trial_spy_2":
		dialog.text = "¡Eso va sin decir! ¡Eso debería ser algo realmente digno de atención, te lo digo! Oh, y la gente decía que los pescadores han visto un barco militar extranjero en estas aguas... probablemente una fragata. ¿Quizás, de allí vino ese espía?";
		link.l1 = "¡Sí, puede ser... Bien, compañero, gracias por la compañía, pero tengo que irme!";
		link.l1.go = "exit_sit";
		pchar.questTemp.Trial = "spy_drink";

		if (CheckAttribute(pchar, "questTemp.trialHabitueId"))
		{
			if (GetCharacterIndex(pchar.questTemp.trialHabitueId) != -1)
			{
				sld = characterFromId(pchar.questTemp.trialHabitueId);
				sld.lifeday = 0;
				DeleteAttribute(pchar, "questTemp.trialHabitueId");
				LAi_CharacterDisableDialog(sld);
				DelLandQuestMark(sld);
			}
		}
		// belamour legendary edtion -->
		if (GetCharacterIndex("PortoBello_Poorman") < 0)
		{
			// новый нищий
			sld = GetCharacter(NPC_GenerateCharacter("PortoBello_Poorman", "panhandler_" + (rand(5) + 1), "man", "man", 5, SPAIN, -1, false, "slave"));
			sld.city = "PortoBello";
			sld.location = "PortoBello_town";
			sld.location.group = "goto";
			sld.location.locator = "goto15";
			sld.forStay.locator = "goto15"; // где генеримся в случае стояния
			sld.forSit.locator0 = "goto3";
			sld.forSit.locator1 = "goto25"; // три локатора, где генеримся в случае сидения
			sld.forSit.locator2 = "goto12";
			LAi_SetLoginTime(sld, 9.0, 21.99);
			sld.Dialog.Filename = "Common_poorman.c";
			LAi_SetPoorType(sld);
			LAi_SetHP(sld, 50.0, 50.0);
			sld.greeting = "poorman_male";
			LAi_group_MoveCharacter(sld, "SPAIN_CITIZENS");
		}
		sld = characterFromId("PortoBello_Poorman");
		LAi_RemoveLoginTime(sld);
		ChangeCharacterAddressGroup(sld, "Portobello_town", "goto", "goto15");
		AddLandQuestMark(sld, "questmarkmain");
		DelLandQuestMark(characterFromId("portobello_tavernkeeper"));
		// <-- legendary edtion
		AddQuestRecord("Trial", "14");
		break;

	case "sit_2":
		Statistic_AddValue(pchar, "TavernDrink", 1);
		AddMoneyToCharacter(pchar, -2);
		// navy --> Alcohol - rum count;
		if (!IsEquipCharacterByArtefact(pchar, "totem_01"))
		{
			if (CheckAttribute(pchar, "questTemp.Rum"))
			{
				pchar.questTemp.Rum = sti(pchar.questTemp.Rum) + 1;
			}
			else
				pchar.questTemp.Rum = 1;
		}
		else
		{
			if (CheckAttribute(pchar, "questTemp.Rum"))
				DeleteAttribute(pchar, "questTemp.Rum");
		}
		//<-- navy
		if (!CheckAttribute(pchar, "questTemp.TimeLock"))
			WaitDate("", 0, 0, 0, 0, 30);

		if (CheckAttribute(pchar, "questTemp.Rum"))
		{
			DeleteAttribute(pchar, "chr_ai.drunk");
			if (sti(pchar.questTemp.Rum) < 3)
				LAi_AlcoholSetDrunk(pchar, 51, 5600);
			else
			{
				LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum) * 2800);
				Pchar.GenQuest.CamShuttle = makeint(sti(pchar.questTemp.Rum) / 2); // Jason
			}
		}

		// Sinistra - Квест "Путеводная звезда" ==>
		if (CheckAttribute(pchar, "questTemp.PZ_BasTerAlkash") && npchar.city == "baster")
		{
			dialog.text = "¡Por tu salud y por tu generosidad!";
			link.l1 = "Compañero, ¿has visto a un chino por la ciudad?";
			link.l1.go = "PZ_BasTerAlkash_1";
			break;
		}
		// <== Квест "Путеводная звезда" - Sinistra

		dialog.text = LinkRandPhrase("Eres un " + GetSexPhrase("amigo verdadero", "gran chica") + "¡Encantado de conocerte! ¡Salud!", "¡Hip! ¡Eso es buen ron! Hip... ¡Salud!", "¡A tu salud y a tu generosidad!");
		link.l1 = "Je, eso es ron fuerte de verdad. Bueno, tengo que irme. ¡Pásalo bien!";
		link.l1.go = "exit_sit";
		if (makeint(pchar.money) >= 2)
		{
			link.l2 = "¿Una copa más, te importa?";
			link.l2.go = "sit_3";
		}

		link.l4 = LinkRandPhrase("Siento como si hubiera pasado una eternidad en el mar. ¿Algún noticia?", "¿Qué dice la gente? Por supuesto, te compraré unas bebidas.", "Dime, amigo, ¿qué historias son populares en las tabernas ahora?");
		link.l4.go = "rumours_habitue";
		break;

	case "sit_3":
		int iSituation;
		if (IsEquipCharacterByArtefact(pchar, "totem_01"))
			iSituation = makeint(rand(3));
		else
			iSituation = makeint(rand(5));
		switch (iSituation)
		{
		case 0:
			dialog.text = "¡Oh! ¡Una gran idea!";
			link.l1 = "¡Camarero! ¡Más ron!";
			link.l1.go = "sit_2";
			break;

		case 1:
			dialog.text = "¡A ti! ¡Oh, diablos! ¿Quién es ese?";
			link.l1 = "¿Eh? ¿Qué? ¿Dónde? Debo estar viendo cosas.";
			link.l1.go = "sit_2"; // to_do "sit_case_5_exit";
			break;

		case 2:
			dialog.text = "¡Bebamos, entonces! ¿Otra más?";
			link.l1 = "¡Adelante!";
			link.l1.go = "sit_2";
			break;

		case 3:
			if (rand(1) == 0)
			{
				dialog.text = RandPhraseSimple("Eh, " + GetAddress_Form(NPChar) + ", seguramente piensas que todos te admiran, ¿verdad? Bueno, si me preguntas, ¡eres solo un bandido común!.. ¡Y asesino! '¡Pirata noble'! ¡Ja! Un bandido es un bandido... Hic... Ya sea en tierra o en el mar..", "¡Hip! " + GetSexPhrase("Esco... Escoria", "Ba... Basura") + "¡Quieres que beba hasta que me desmaye, hip,  y luego me robarás todo mi dinero!");
				link.l1 = "Veo que ya has bebido suficiente... Vete a dormir... Y yo debo irme...";
				link.l1.go = "exit_sit";
				link.l2 = "No me gusta tu tono, compañero. Guarda tu lengua, ¿vale?";
				link.l2.go = "sit_case_2_enemy";
				link.l3 = "¿A quién acabas de llamar bandido, tú, perro de tierra?! ¡Vamos a ver qué vas a decir con un agujero en la barriga!";
				link.l3.go = "sit_case_2_enemy2";
				link.l4 = "¡Cálmate! ¿Lo olvidaste? ¡Soy tu único verdadero amigo!";
				link.l4.go = "sit_case_2_friend";
			}
			else
			{
				// Captain Beltrop, 27.06.21, новый вариант
				/* if (rand(1) == 0)
				{
					Diag.CurrentNode = Diag.TempNode;
					AddDialogExitQuestFunction("Tavern_SetBadHabitue");
					DialogExit();
				}
				else
				{ */
				dialog.text = RandPhraseSimple("¿Por qué me estás mirando? ¡Esperarás hasta que me desmaye y luego me robarás todo mi dinero! ¿¡De dónde salió toda esta chusma?! Hipo... ¿No hay lugar para una persona decente en esta taberna?", "¿Me respetas?.. ¡Sí, tú! ¿Me respetas?! ¡Más te vale cuidarte... No soy alguien con quien se pueda jugar... Un golpe entre los ojos... ¡Y estarás tan muerto como si lo estuvieras!");
				link.l1 = "Compañero, estás borracho como un cerdo. Vete a casa y duérmete... Y yo también tengo que irme...";
				link.l1.go = "exit_sit";
				link.l2 = "Aguanta tus caballos, compañero. Ten cuidado con a quién estás hablando.";
				link.l2.go = "sit_case_2_enemy1";
				link.l3 = "¿Qué acabas de decir?! ¡Te daré una lección!";
				link.l3.go = "sit_case_2_enemy2";
				link.l4 = "¡Cálmate! ¿Me has olvidado? ¡Soy tu único amigo verdadero!";
				link.l4.go = "sit_case_2_friend";
				//}
			}
			break;

		case 4:
			dialog.text = "¡Escucha! ¡Eres un buen hombre! Quizás, ¿me ayudarás... con un asunto?";
			link.l1 = "No, creo que tengo que irme ahora.";
			link.l1.go = "exit_sit";
			link.l2 = "¡Claro! ¡Hic! Somos amigos... ¿no es así? ¡Hic!";
			link.l2.go = "sit_case_3";
			break;

		case 5:
			if (GetSummonSkillFromName(pchar, SKILL_SNEAK) > rand(110))
			{
				dialog.text = "...Y entonces atrapé su s-sable por la h-hoja...";
				link.l1 = "...y entonces ella dijo...";
				link.l1.go = "sit_2";
			}
			else
			{
				dialog.text = "...Y entonces atrapé su sable por la h-hoja...";
				link.l1 = "...¡hic! ...y luego ella dijo...";
				link.l1.go = "sit_case_4_exit";
			}
			break;
		}
		break;

	case "sit_case_5_exit": // дуэль
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		AddDialogExitQuest("fighting");
		break;

	case "sit_case_4_exit":
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		pchar.questTemp.friend_in_tavern = npchar.id;
		AddDialogExitQuest("without_memory");
		break;

	case "sit_case_3":
		dialog.snd = "Voice\HADI\HADI037";
		dialog.text = "El p-punto es q-que uno de los s-soldados me insultó. ¡E-Eso es!";
		link.l1 = "¿Un s-soldado? N-No, creo que voy a pasar.";
		link.l1.go = "exit_sit";
		link.l2 = "¡Cálmate! ¿Me has olvidado? ¡Soy tu único verdadero amigo!";
		link.l2.go = "sit_2";
		break;

	case "sit_case_2_friend":
		dialog.snd = "Voice\HADI\HADI038";
		dialog.text = "¿Tú? ¿Qué tipo de amigo eres tú? ¡N-no! Tú... tú quieres matarme! ¡E-Eso es!";
		link.l1 = "Bueno, ciertamente ya has bebido suficiente. Adiós.";
		link.l1.go = "exit_sit";
		link.l2 = "¿Qué? ¡Te demostraré que no voy a matarte! Yo... ¡Te cortaré la mano!... Sin ella no puedes ser asesinado!... ¡Hic!";
		link.l2.go = "sit_case_2_friend_2";
		break;

	case "sit_case_2_friend_2":
		dialog.snd = "Voice\HADI\HADI039";
		dialog.text = "¡Aaaah! Toma " + GetSexPhrase("él", "ella") + "¡apártate de mí!";
		link.l1 = "Cálmate... hip... ¡No va a doler!... ¡Es menos doloroso que un afeitado!";
		link.l1.go = "tavern_keeper";
		break;

	case "sit_case_2_enemy":
		dialog.snd = "Voice\HADI\HADI040";
		dialog.text = "¡No intentes intimidarme! ¡Hic! ¡No me asusto tan fácilmente!.. Y tú, tú deberías estar colgado en la horca... Con todos los de tu especie, ¡hic! Puedes hinchar tus plumas todo lo que quieras, ¡pero aún hueles a pescado podrido! ¡Y no cuidaré mi lengua cuando... ¡hic!... hable con los de tu especie! ¡Todos me dan asco!";
		link.l1 = "Argh, por qué estoy hablando con un borracho de todos modos... Supongo que iré a tomar un respiro de aire fresco...";
		link.l1.go = "exit_sit1";
		link.l2 = "¡Eres demasiado atrevido, compañero! ¡Te haré tragar tus palabras!";
		link.l2.go = "sit_case_2_enemy3";
		break;

	case "sit_case_2_enemy1":
		dialog.snd = "Voice\HADI\HADI040";
		dialog.text = "¿¡Qu-qué?! ¡Te estrangularé con mis propias manos! Hic... ¡Nadie se me ha escapado... hic... hasta ahora!";
		link.l1 = "Eres un cerdo borracho... Estropeas una noche tan agradable... Bien, ve a atrapar tus cucarachas, yo me largo de aquí.";
		link.l1.go = "exit_sit1";
		link.l2 = RandSwear() + "Veo que no vas a quedarte quieto. Bueno, entonces es hora de una lección de buenos modales.";
		link.l2.go = "sit_case_2_enemy3";
		break;

	case "sit_case_2_enemy2":
		ChangeCharacterComplexReputation(pchar, "nobility", -2);
		if (rand(1) == 0)
		{
			dialog.text = LinkRandPhrase("¡Acércate, granuja! ¡Recibirás lo que te mereces!", RandSwear() + "¡Te daré lo que te mereces!", "¡Ja! Muy bien, perro de mar, veamos cómo te las arreglas en tierra firme!");
			link.l1 = RandPhraseSimple(RandPhraseSimple("¡Juro que te arrepentirás!", "¡Acortaré tu maldita lengua hasta las orejas!"), RandPhraseSimple("¡Te voy a desollar como a un cerdo, desde tu trasero hasta ese agujero de mierda que algunos llaman boca!", "¡Juro que te haré callar!"));
			link.l1.go = "fight_right_now";
		}
		else
		{
			dialog.text = "¡Eh, muchachos! ¡Vamos a barrer esta basura de nuestro pueblo!";
			link.l1 = RandPhraseSimple(RandSwear() + "¡Decid vuestras oraciones, bastardos!", "¡Oh, así que no estás solo! Bueno, mejor para ti, ¡tendrás compañía en el infierno!");
			link.l1.go = "fight_right_now_1";
		}
		break;

	case "sit_case_2_enemy3":
		ChangeCharacterComplexReputation(pchar, "nobility", 2);
		if (rand(1) == 0)
		{
			dialog.text = LinkRandPhrase("Acércate, granuja! Obtendrás lo que te mereces!", RandSwear() + "¡Te daré lo que te mereces!", "¡Ja! Muy bien, perro de mar, veamos cómo te va en tierra firme!");
			link.l1 = RandPhraseSimple(RandPhraseSimple("¡Juro que te arrepentirás!", "¡Acortaré tu lengua sucia hasta las orejas!"), RandPhraseSimple("¡Te desollaré como a un cerdo, desde tu trasero hacia tu cagadero que algunos llaman boca!", "¡Juro que te haré callar!"));
			link.l1.go = "fight_right_now";
		}
		else
		{
			dialog.text = "¡Eh, muchachos! ¡Vamos a barrer esta basura de nuestra ciudad!";
			link.l1 = RandPhraseSimple(RandSwear() + "¡Decid vuestras oraciones, bastardos!", "¡Oh, así que no estás solo! ¡Mejor para ti, tendrás compañía en el infierno!");
			link.l1.go = "fight_right_now_1";
		}
		break;

	case "exit_sit":
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		AddDialogExitQuest("exit_sit");
		break;

	case "exit_sit1":
		ChangeCharacterComplexReputationToNeutral(pchar, "nobility", 2.0);
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		AddDialogExitQuest("exit_sit");
		break;

	case "tavern_keeper":
		Diag.CurrentNode = Diag.TempNode;
		DialogExit();
		AddDialogExitQuest("tavern_keeper");
		break;

	// Captain Beltrop, 27.06.21, новый вариант
	case "bad_habitue":
		dialog.text = "¡Eh, no entendí algo! Tan pronto como doblé la esquina, algún novato desembarcó en mi lugar. ¡Lárgate de aquí!";
		link.l1 = "Siempre es así: apenas te sientas en la mesa y resulta que ya está ocupada... Guarda tu asiento, de todas formas estaba a punto de irme.";
		link.l1.go = "bad_habitue1";
		link.l2 = "Una oración más así de tu boca sucia y será lo último que digas en tu vida, ¿entiendes?";
		link.l2.go = "bad_habitue2";
		link.l3 = "No sé si este era realmente tu lugar, pero no te permitiré que me hables así. Cuida tus palabras.";
		link.l3.go = "bad_habitue3";
		break;

	case "bad_habitue1":
		DialogExit();
		pchar.questTemp.BadHabitueSit = true; // атрибут усаживания
		AddDialogExitQuest("exit_sit");
		break;

	case "bad_habitue2":
		ChangeCharacterComplexReputation(pchar, "nobility", -1);
		if (rand(1) == 0)
		{
			dialog.text = LinkRandPhrase("¡Vamos, granujas! ¡Estáis a punto de recibir vuestra ración!", RandSwear() + "¡Ahora te despojaré como es debido!", "¡Ja! Vamos, marinero, veamos lo que puedes hacer en tierra!");
			link.l1 = RandPhraseSimple(RandPhraseSimple("¡Juro que te arrepentirás de esto!", "¡Cortaré tu maldita lengua!"), RandPhraseSimple("¡Te desollaré como a un cerdo, desde tu trasero hasta ese agujero de mierda que algunos llaman boca!", "¡Juro que te haré callar!"));
			link.l1.go = "fight_right_now";
		}
		else
		{
			dialog.text = "¡Vamos chicos! ¡Saquemos esta escoria de nuestra ciudad!";
			link.l1 = RandPhraseSimple(RandSwear() + "¡Rezad, canallas!", "¡Oh, no estás solo! Bueno, tendrás compañía en el infierno!");
			link.l1.go = "fight_right_now_1";
		}
		break;

	case "bad_habitue3":
		ChangeCharacterComplexReputation(pchar, "nobility", 1);
		if (rand(1) == 0)
		{
			dialog.text = LinkRandPhrase("¡Vamos, granujas! ¡Estáis a punto de saciaros!", RandSwear() + "¡Ahora te despojaré como es debido!", "¡Ja! Vamos, marinero, veamos lo que puedes hacer en tierra!");
			link.l1 = RandPhraseSimple(RandPhraseSimple("¡Te juro que te arrepentirás de esto!", "¡Cortaré tu maldita lengua!"), RandPhraseSimple("¡Te destriparé como a un cerdo, desde tu trasero hasta tu cloaca que algunos llaman boca!", "¡Juro que te haré callar!"));
			link.l1.go = "fight_right_now";
		}
		else
		{
			dialog.text = "¡Vamos, chicos! ¡Saquemos a esta escoria de nuestra ciudad!";
			link.l1 = RandPhraseSimple(RandSwear() + "¡Rezad, canallas!", "¡Oh, no estás solo! Bueno, tendrás compañía en el infierno!");
			link.l1.go = "fight_right_now_1";
		}
		break;

	//--> Sinistra Длинные тени старых грехов
	case "DTSG_NightIskat":
		dialog.text = "Cl-claro, ¡todos nos conocemos! ¿Por qué preguntas?";
		link.l1 = "Quería visitar al prestamista y descubrí que vendió su antigua casa. ¿Sabes dónde vive ahora?";
		link.l1.go = "DTSG_NightIskat_2";
		break;

	case "DTSG_NightIskat_2":
		dialog.text = "¿Por qué lo necesitas a él a esta hora, hic? ¡Solo visita el banco por la mañana!";
		link.l1 = "Necesito dinero urgentemente. ¡Que el bolsillo trabaje por ello por una vez! Su tipo siempre nos llama gorrones que solo mendigamos, nos quejamos y nunca devolvemos lo que debemos.";
		link.l1.go = "DTSG_NightIskat_3";
		break;

	case "DTSG_NightIskat_3":
		dialog.text = "Ja-ja-ja, hip, sí, ¡déjalo trabajar! ¿Sabes dónde vivía nuestro glorioso capitán Fleetwood?";
		link.l1 = "Por supuesto, ¿quién no conocía a Richard? ¿Ahora el banquero vive allí?";
		link.l1.go = "DTSG_NightIskat_4";
		break;

	case "DTSG_NightIskat_4":
		dialog.text = "Tienes razón. Cuando estés allí, amigo, dile que se ha vuelto demasiado engreído.";
		link.l1 = "Je-je, seguro que lo haré. Adiós.";
		link.l1.go = "DTSG_NightIskat_5";
		break;

	case "DTSG_NightIskat_5":
		DialogExit();
		DeleteAttribute(pchar, "questTemp.DTSG_NightIskat");
		Diag.CurrentNode = Diag.TempNode;
		AddDialogExitQuest("exit_sit");

		chrDisableReloadToLocation = true;
		sld = CharacterFromID("Knippel");
		ChangeCharacterAddressGroup(sld, PChar.location, "goto", "goto4");
		sld.dialog.filename = "Quest\CompanionQuests\Knippel.c";
		sld.dialog.currentnode = "DTSG_Knippel_SluhSmertFleetWood";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
	//<-- Длинные тени старых грехов

	//--> Путеводная звезда
	case "PZ_BasTerAlkash_1":
		dialog.text = "Ja-ja-ja, ¿he visto a un chino? ¡Todos lo hemos visto!";
		link.l1 = "¿Qué es tan gracioso? No estoy hablando de un circo ambulante, si eso es lo que quieres decir. Hablo de un luchador, un oficial de la marina.";
		link.l1.go = "PZ_BasTerAlkash_2";
		break;

	case "PZ_BasTerAlkash_2":
		dialog.text = "¡Ah, ya veo a qué te refieres! Sí, lo vi. Incluso después de despejarme, no pude dejar de verlo... No puedo olvidarlo!";
		link.l1 = "Eso es interesante. Continúa. Tomemos otra copa, probablemente estés bebiendo ahora para olvidarlo todo. Dime qué viste antes de que lo hagas.";
		link.l1.go = "PZ_BasTerAlkash_3";
		break;

	case "PZ_BasTerAlkash_3":
		dialog.text = "¡Un circo ambulante, mi culo! Saltaba, giraba y arremolinaba esa sable. Nunca he visto a nadie tan hábil y aterrador con un arma.";
		link.l1 = "Eso suena como él. ¿Con quién estaba peleando? ¿Te acuerdas?";
		link.l1.go = "PZ_BasTerAlkash_4";
		break;

	case "PZ_BasTerAlkash_4":
		dialog.text = "¡Los guardias, compañero! ¡También les mira con ojos entrecerrados! Aunque, creo que siempre tiene esa mirada. ¿Qué piensas tú?";
		link.l1 = "No lo sé, compañero. Sigue adelante. ¿Pensaban que era un espía? ¿Por qué los guardias lo atacaron?";
		link.l1.go = "PZ_BasTerAlkash_5";
		break;

	case "PZ_BasTerAlkash_5":
		dialog.text = "¿Quién sabe? Estaban tratando de averiguar qué estaba haciendo en la ciudad...";
		link.l1 = "Entonces, ¿lo arrestaron? ¿O...?";
		link.l1.go = "PZ_BasTerAlkash_6";
		break;

	case "PZ_BasTerAlkash_6":
		dialog.text = "¡Ja, ni lo sueñes! No pudieron atraparlo. Acabó con los guardias de la ciudad y huyó a la jungla. Han enviado varios grupos tras él, pero ninguno ha regresado. ¿Puedes imaginarlo? ¡Ha convertido esa cueva en una verdadera fortaleza!";
		link.l1 = "Eso es algo. Descansa un poco e intenta olvidarlo. Creo que me iré ahora, me está dando vueltas la cabeza.";
		link.l1.go = "PZ_BasTerAlkash_7";
		break;

	case "PZ_BasTerAlkash_7":
		DialogExit();
		bDisableLandEncounters = true;
		DeleteAttribute(pchar, "questTemp.PZ_BasTerTavern");
		DeleteAttribute(pchar, "questTemp.PZ_BasTerAlkash");
		pchar.questTemp.PZ_BasTerAlkash2 = true;
		DeleteQuestCondition("PZ_BasTer_Opozdal");
		pchar.questTemp.PZ_BasTerTurma = true;
		AddLandQuestMarkToPhantom("baster_prison", "basterJailOff");
		DelMapQuestMarkIsland("Guadeloupe");
		AddQuestRecord("PZ", "3");
		Diag.CurrentNode = Diag.TempNode;
		AddDialogExitQuest("exit_sit");

		PChar.quest.PZ_BasTerPeshera.win_condition.l1 = "location";
		PChar.quest.PZ_BasTerPeshera.win_condition.l1.location = "Guadeloupe_CaveEntrance";
		PChar.quest.PZ_BasTerPeshera.win_condition = "PZ_BasTerPeshera";

		LAi_LocationDisableOfficersGen("Guadeloupe_jungle_02", false);
		LAi_LocationDisableOfficersGen("Guadeloupe_CaveEntrance", false);
		// LAi_LocationDisableOfficersGen("Guadeloupe_Cave", false);
		break;

	case "Sotta1":
		dialog.text = "No lo he visto yo mismo, ha estado rondando la oficina del gobernador, ¡eh! Pero su tripulación hizo una gran fiesta aquí.";
		link.l1 = "¿Es así?";
		link.l1.go = "Sotta2";
		break;

	case "Sotta2":
		dialog.text = "Todos dicen que es un comerciante. Pero su tripulación no parecía la escoria de una taberna, ¡te lo digo! Su aspecto era como si... como si... ¿cuál es la palabra...?";
		link.l1 = "Lo entiendo. Gracias por la compañía, compañero. Tómatelo con calma.";
		link.l1.go = "exit_sit";

		npchar.questTemp.Sotta = true;
		pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
		AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;

	case "Lutter1":
		dialog.text = "¡Estoy celebrando! ¿Y quién dice que estoy solo? ¡Estás aquí, compañero! Y en cuanto a Matt, estaba destinado a suceder tarde o temprano.";
		link.l1 = "¿Qué te hace decir eso? ¡He oído que era un pirata notablemente afortunado, favorecido por la Fortuna durante años!";
		link.l1.go = "Lutter2";
		break;

	case "Lutter2":
		dialog.text = "Je, ¡no fue solo la Fortuna, eh! Era un pirata solitario, ¡no un miembro de la Hermandad! Y esos no duran mucho ... Aunque, escuché rumores de que una vez estuvo bajo el ala de Levasseur.";
		link.l1 = "Eso es correcto, los solitarios no duran mucho. Bueno, celebra. Tengo que irme, compañero.";
		link.l1.go = "exit_sit";

		npchar.questTemp.Lutter = true;
		pchar.questTemp.PZ_BelizAskCitizens = sti(pchar.questTemp.PZ_BelizAskCitizens) + 1;
		AddDialogExitQuest("PZ_LongwayBelizDialog");
		break;

	case "Sepp1":
		dialog.text = "¡Ay, sí, n-no, nunca lo he visto. ¿Quién es él?";
		link.l1 = "Es el capitán de uno de los barcos más rápidos del Archipiélago, la fragata 'Banten'. ¿Has oído hablar de él?";
		link.l1.go = "Sepp2";
		break;

	case "Sepp2":
		pchar.questTemp.PZ.TortugaHabitueBlock = true;

		dialog.text = "Er, no, no me interesan los barcos, compañero, ¡ay! ¿Tomamos otra copa?";
		link.l1 = "No para mí. De todas formas, no obtuve lo que quería aquí.";
		link.l1.go = "exit_sit";
		break;
		//<-- Путеводная звезда
	}
}

bool CheckFreeSitFront(ref _npchar)
{
	ref rCharacter; // ищем
	int n;

	if (!CheckAttribute(_npchar, "Default.ToLocator"))
		return false;

	for (n = 0; n < MAX_CHARACTERS; n++)
	{
		makeref(rCharacter, Characters[n]);
		if (CheckAttribute(rCharacter, "location") && rCharacter.location == _npchar.location)
		{
			if (rCharacter.location.locator == _npchar.Default.ToLocator)
				return false;
		}
	}
	return true;
}
