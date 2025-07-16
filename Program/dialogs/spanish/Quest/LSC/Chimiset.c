// колдун ривадос - Чимисет
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		dialog.text = "¿Quieres algo?";
		link.l1 = "No, no importa.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	//-------------------------------------в тюрьме на Тартарусе-----------------------------
	// вариант R
	case "KillChad":
		dialog.text = "¡Espera! Detente... Te ruego que me escuches antes de cometer un error.";
		link.l1 = "Estoy escuchando... Espero que tengas un argumento razonable para detenerme de...";
		link.l1.go = "KillChad_1";
		LAi_RemoveCheckMinHP(npchar); // убираем проверяльщик, если еще есть
		break;

	case "KillChad_1":
		dialog.text = "¿De matarme, verdad? Te he oído hablar con Chad arriba y no te culpo, cualquiera haría lo mismo. Pero te equivocas al pensar que Chad te dejará ir después de matarme.";
		link.l1 = "Mm... Interesante, ¿y por qué no lo hará? Lo único que sé es que tendré que sudar para salir de aquí, si no simplemente te mato.";
		link.l1.go = "KillChad_2";
		break;

	case "KillChad_2":
		dialog.text = "No tendrás ningún futuro si me matas. Escucha, los Narvales y Chad están dispuestos a deshacerse de mí, pero tienen demasiado miedo para hacerlo ellos mismos - mi asesino será maldito para siempre. Así que quieren que tú hagas todo el trabajo sucio\nChad sabe que no eres Rivados, te está engañando. Una vez que me mates, te harán lo mismo a ti y usarán tu cadáver para engañar al Shark.";
		link.l1 = "¿Shark? ¿Steve Dodson? ¿Está realmente aquí? Y explícame de una vez, ¿quiénes diablos son esos Rivados?";
		link.l1.go = "KillChad_3";
		break;

	case "KillChad_3":
		dialog.text = "Heh,  parece que no vives aquí, en efecto... Pero no es el momento adecuado para contar historias. Tenemos que salvarnos. Tengo un plan.";
		link.l1 = "¿Sabes qué, hechicero? Recientemente hice un viaje a través de algún portal místico y apenas sobreviví, así que tus maldiciones no me asustan. He tenido suficiente, es hora de acabar contigo.";
		link.l1.go = "KillChad_fightfail";
		link.l2 = "Está bien, confío en ti. ¿Cuál es el plan?";
		link.l2.go = "KillChad_4";
		break;

	case "KillChad_fightfail":
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		LAi_SetActorType(npchar);
		LAi_ActorAnimation(npchar, "afraid", "", -1);
		LAi_SetImmortal(npchar, false);
		pchar.quest.LSC_fightfail.win_condition.l1 = "NPC_Death";
		pchar.quest.LSC_fightfail.win_condition.l1.character = "Chimiset";
		pchar.quest.LSC_fightfail.function = "LSC_Fightfail_Final";
		break;

	case "KillChad_4":
		dialog.text = "Hay un cofre allí. Contiene armas decentes y pociones. Está cerrado, pero la cerradura es vieja y está dañada, así que busca una palanca para romperla\nToma todo del cofre, ármate y ve hacia las escaleras. Es una buena posición defensiva, estarán obligados a enfrentarte uno por uno, solo ten cuidado con los mosqueteros\nEspero que seas hábil con la espada, yo soy demasiado viejo para ayudarte a pelear. Si logras matarlos a todos y sobrevivir en el proceso, te garantizo la protección de los Rivados, mi familia...";
		link.l1 = "Bien. Reza a tus dioses por mí - la pelea va a ser dura. Esos muchachos arriba parecen realmente serios.";
		link.l1.go = "KillChad_5";
		break;

	case "KillChad_5":
		DialogExit();
		pchar.quest.LSC_fightfail.over = "yes"; // снять прерывание
		LAi_SetImmortal(npchar, true);
		ref location = &Locations[FindLocation(pchar.location)];
		location.private1.key = "crowbar";
		location.private1.key.delItem = true;
		NextDiag.CurrentNode = "KillChad_6";
		break;

	case "KillChad_6":
		dialog.text = "¡No pierdas el tiempo! Fuerza la cerradura rápidamente...";
		link.l1 = "Sí, sí, estoy en camino.";
		link.l1.go = "exit";
		NextDiag.TempNode = "KillChad_6";
		break;

	case "Chad_die":
		dialog.text = "¡Bien hecho! Eres realmente un maestro de la esgrima. Te debo una, forastero. Dime, ¿cuál es tu nombre?";
		link.l1 = "" + pchar.name + ". " + GetFullName(pchar) + "¿Y cuál es el tuyo?";
		link.l1.go = "Chad_die_1";
		break;

	case "Chad_die_1":
		dialog.text = "Mi nombre es Chimiset, soy un chamán de los Rivados y consejero de nuestro jefe - Eddie el Negro. Se alegrará de saber que me has liberado y salvado la vida. Eres amigo de Chimiset, Eddie el Negro y todos los Rivados. A partir de ahora siempre serás un huésped bienvenido en nuestro Protector...";
		link.l1 = "Espera... Chimiset, en caso de que aún no entiendas, han pasado solo unas pocas horas desde que llegué aquí. ¿Puedes explicarme dónde estoy, quiénes son los Rivados y dónde puedo encontrar al Shark Dodson?";
		link.l1.go = "Chad_die_2";
		break;

	case "Chad_die_2":
		dialog.text = "Este lugar se llama la Ciudad de los Barcos Abandonados. Aunque suena más como una burla. No es mucho de una ciudad. Este lugar es una isla formada por cientos de barcos muertos. El centro es adecuado para el espacio habitable. Está habitado por personas que sobrevivieron a los naufragios inexplicables causados por tormentas que los llevaron aquí\nRivados es un clan, un grupo de personas que han estado viviendo juntos durante mucho tiempo. También hay otros tres grupos viviendo aquí: el clan Narval, son nuestros enemigos, los piratas de Shark Dodson y la gente común. Shark es básicamente el jefe de la isla, se llama a sí mismo un almirante\nHa llegado hace poco y ha tomado el poder de manera violenta. Capturó el 'San Augustine' donde estábamos almacenando nuestras provisiones de comida. Ahora tenemos que comprar provisiones a los precios que nombra Shark. Parece que ya has estado en ese almacén\nChad Kapper era el contramaestre de Shark y el jefe de la prisión. Layton Dexter solía ser el primer oficial de Shark, él también tiene algo de influencia. Estos tres y sus piratas son una fuerza dominante en toda la isla, enfrentándose tanto a Rivados como a Narval.";
		link.l1 = "¿Por qué Chad Kapper quería que te matara?";
		link.l1.go = "Chad_die_3";
		break;

	case "Chad_die_3":
		dialog.text = "Chad había establecido contactos con los Narvales, nuestros enemigos. Iba a matar a Shark con su ayuda y tomar su lugar. Los Narvales guardan rencor contra el almirante por la muerte de Alan Milrow, su antiguo líder. Creen que Shark es responsable de su muerte, pero están equivocados. Yo sé quién lo hizo. Fue Chad. Soy el único testigo de este crimen. Por eso Chad no podía dejarme libre, pero también temía hacerme daño. Los piratas son intrépidos en las batallas, pero son muy supersticiosos. Así que quería usarte a ti. Chad y los Narvales matarían a Shark y culparían a los Rivados.";
		link.l1 = "¿Es así? Dime por qué...";
		link.l1.go = "Chad_die_4";
		break;

	case "Chad_die_4":
		dialog.text = "" + pchar.name + ", mi amigo, hablemos más tarde. Tenemos que darnos prisa, antes de que aparezcan los piratas de Shark. Busca el cuerpo de Chad y toma sus llaves. Pero primero, revisa su escritorio, podría tener papeles interesantes allí.\nVe a Shark Dodson, lo encontrarás en el 'San Augustine', un gran barco, estrellado a una distancia de los demás, hay un puente que lleva hacia ella desde el barco llamado 'Pluto'. Dile que Chad estaba tramando una traición, y di que los Narvales están detrás de todo esto, y que nosotros, los Rivados, no tenemos nada que ver con ello.\nCon gusto te daré cualquier información que necesites sobre esta isla, sobre mi clan y otros, una vez que llegues a nuestra residencia en el Protector. ¡Salgamos de aquí!";
		link.l1 = "Está bien, Chimiset. Te encontraré más tarde en el... 'Protector'. ¡Salgamos de aquí!";
		link.l1.go = "Chad_die_5";
		break;

	case "Chad_die_5":
		dialog.text = "Una cosa más. Nuestros barcos, incluido el 'Protector', están restringidos a los extraños. Debes ser Rivados o conocer una contraseña para poder entrar. Te la diría, pero cambia cada semana y he estado aquí demasiado tiempo, así que no sé la contraseña activa\n Deberías visitar primero el 'San Augustine'. Informaré a nuestra gente sobre quién eres, mientras hablas con Shark, te estarán esperando. Pero no vayas al 'Protector' ahora, primero, habla con Shark, y déjame reunir a mi gente primero, de lo contrario los Rivados serán hostiles hacia ti";
		link.l1 = "Ya veo. Me dirijo a 'San Augustine'. ¡Hasta luego!";
		link.l1.go = "Chad_die_6";
		break;

	case "Chad_die_6":
		DialogExit();
		DeleteAttribute(pchar, "GenQuest.Notsearchbody");
		LAi_SetActorType(npchar);
		LAi_ActorFollow(npchar, pchar, "", -1);
		pchar.quest.LSC_LetterChad.win_condition.l1 = "item";
		pchar.quest.LSC_LetterChad.win_condition.l1.item = "letter_chad";
		pchar.quest.LSC_LetterChad.function = "LSC_LetterChad_Find";
		sld = characterFromId("SharkMush_17");
		sld.lifeday = 0;
		for (i = 1; i <= 2; i++)
		{
			sld = characterFromId("SharkSold_1" + (i + 3));
			sld.lifeday = 0;
		}
		AddSimpleRumourCityTip("Ja, dicen que eres amigo del clan Rivados. Esto es interesante. Felicidades...", "LostShipsCity", 5, 1, "LSC", "");
		AddSimpleRumourCityTip("Dicen que has salvado al mago Rivados Chimiset del 'Tártaro'. Ahora eres un huésped bienvenido en sus barcos.", "LostShipsCity", 5, 1, "LSC", "");
		AddSimpleRumourCityTip("¡Así que has sido tú quien ha liberado a Chimiset! Interesante. Ahora eres amigo de Rivados pero enemigo de Narvales. No estoy seguro si felicitarte o simpatizar...", "LostShipsCity", 5, 1, "LSC", "");
		break;

	// вариант N
	case "prisoner":
		dialog.text = "¿Qué quieres de mí, forastero?";
		link.l1 = "Tu nombre es Chimiset, ¿verdad?";
		link.l1.go = "prisoner_1";
		break;

	case "prisoner_1":
		dialog.text = "Sí, soy yo. ¿Tienes negocios conmigo o solo quieres hablar?";
		link.l1 = "Tengo algunos asuntos que discutir. Vine aquí de parte del Almirante, Shark Dodson. He traído una orden para liberarte, pero con una condición: debes responder a varias de mis preguntas.";
		link.l1.go = "prisoner_2";
		break;

	case "prisoner_2":
		dialog.text = "¿Ha decidido Dodson liberarme? Me alegra escuchar eso. Haz tus preguntas. Espero que no haya engaños en esto, de lo contrario mi emoción habrá sido en vano.";
		link.l1 = "Sin trucos, solo necesito tu ayuda. Dime, Chimiset, ¿hay un extraño ídolo de piedra en esta isla? Se convierte en oro a medianoche. No me tomes por loco...";
		link.l1.go = "Friend_2";
		break;

	case "prisoner_3":
		dialog.text = "¿Alguna otra pregunta?";
		link.l1 = "Sí. ¿Conoces a un hombre llamado el Chico Blanco?";
		link.l1.go = "prisoner_4";
		break;

	case "prisoner_4":
		dialog.text = "¿Chico blanco? Claro, lo conozco. Ese es el apodo de Olle Christiansen, nuestro idiota. Ya es adulto y no parece un chico, aunque su mente sigue siendo infantil.";
		link.l1 = "¿Es así? Dime, ¿dónde puedo encontrarlo?";
		link.l1.go = "prisoner_5";
		break;

	case "prisoner_5":
		dialog.text = "En cualquier lugar de nuestra ciudad. A menudo se le podía encontrar en la tienda, la taberna o caminando por las calles. Tiene el pelo blanco, lo reconocerás.";
		link.l1 = "¡Excelente! Una pregunta más: ¿has conocido aquí a un hombre llamado Nathaniel Hawk? Debió haber aparecido aquí hace algún tiempo, y podría estar gravemente enfermo.";
		link.l1.go = "prisoner_6";
		break;

	case "prisoner_6":
		dialog.text = "No puedo ayudarte con eso, forastero. No conozco a un hombre con tal nombre. Te puedo asegurar que no está en los barcos de los Rivados, tampoco debería estar en el área neutral. No puedo decir lo mismo sobre los territorios de los Narvales, sin embargo, los Rivados no los visitan.";
		link.l1 = "Bueno, gracias de todos modos... ¡Me has ayudado mucho, Chimiset!";
		link.l1.go = "prisoner_7";
		break;

	case "prisoner_7":
		dialog.text = "¿Eso es todo? ¿Me liberará Shark ahora?";
		link.l1 = "Sí. No tengo nada más que preguntarte. Chad Kapper te liberará. Bueno, tengo que irme...";
		link.l1.go = "prisoner_8";
		break;

	case "prisoner_8":
		dialog.text = "¡Detente! Espera... Vuelve.";
		link.l1 = "¿Tienes algo más que contarme?";
		link.l1.go = "prisoner_9";
		break;

	case "prisoner_9":
		dialog.text = "No exactamente... (bajando la voz) Veo que no eres uno de los hombres de Kapper. No confíes en él. Es una escoria inmunda. No hace mucho, mató sin piedad a Alan Milrow desarmado con una espada ancha. Era el líder del clan Narval. No lo vi venir, Chad simplemente se acercó a su celda y lo ejecutó. También he oído algunos rumores de que los propios hombres del Almirante planean asesinarlo. Dile a Shark sobre esto. Y dile que diré más cuando hablemos cara a cara.";
		link.l1 = "Mm. Bien, se lo diré a Dodson. ¡Nos vemos!";
		link.l1.go = "prisoner_10";
		break;

	case "prisoner_10":
		DialogExit();
		sld = characterFromId("Capper");
		sld.quest.chimiset_talk = "true"; // разговор с Чимисетом состоялся
		if (!CheckAttribute(npchar, "quest.capper_talk"))
			chrDisableReloadToLocation = true; // закрыть локацию
		else
			chrDisableReloadToLocation = false; // открыть локацию
		sld = characterFromId("Dodson");
		sld.dialog.currentnode = "entrance_10"; // ноду Акуле
		LSC_SetWhiteBoy();						// поставим белого мальчика
		NextDiag.CurrentNode = "prisoner_11";
		AddQuestRecord("SharkHunt", "20");
		break;

	case "prisoner_11":
		dialog.text = "Ve a Shark y cuéntale todo lo que te he dicho. Eh, espero que abran esta jaula pronto...";
		link.l1 = "Sí, sí. Estoy en camino.";
		link.l1.go = "exit";
		NextDiag.TempNode = "prisoner_11";
		break;

	//------------------------беседа на Протекторе, если был старт через Тартарус-----------------
	case "Friend":
		dialog.text = "Ahí estás, mi querido amigo. Gracias de nuevo por salvarme y confiar en mí, en vez de en Kapper. Te daré estos amuletos como recompensa. Estoy seguro de que los encontrarás útiles.";
		link.l1 = "¡Gracias! No esperaba eso...";
		link.l1.go = "Friend_1";
		break;

	case "Friend_1":
		GiveItem2Character(pchar, "indian_1");
		GiveItem2Character(pchar, "indian_11");
		GiveItem2Character(pchar, "amulet_1");
		PlaySound("interface\important_item.wav");
		dialog.text = "Y ahora estoy listo para escucharte. Querías preguntarme algo, ¿verdad?";
		link.l1 = "Tienes razón, Chimiset. Necesito tu ayuda. Primero, necesito saber, ¿hay un extraño ídolo de piedra en esta isla? Se convierte en oro a medianoche. No pienses que estoy loco...";
		link.l1.go = "Friend_2";
		break;

	// нода пересечения
	case "Friend_2":
		dialog.text = "Ay, veo a qué te refieres, mi amigo. He visto esta estatua de dioses indios con mis propios ojos. Aunque se convierte en oro solo bajo los rayos del sol de la mañana, y no de la luna... muchas veces sacrificamos malvados Narvales y el dios los devoró a todos. Pero ya no está en la Isla.";
		link.l1 = "¿Cómo que no es así?! ¿Estás diciendo que desapareció de repente?!";
		link.l1.go = "Friend_3";
		break;

	case "Friend_3":
		dialog.text = "No exactamente así. Esta estatua estaba dentro del 'San Geronimo'. Este barco se hundió con la estatua hace varios años.";
		link.l1 = "¡Qué mala suerte! Parece que ahora es imposible abandonar la isla... ¿Y dónde estaba ese barco?";
		link.l1.go = "Friend_4";
		break;

	case "Friend_4":
		dialog.text = "No muy lejos de los territorios de los Narvales, cerca de los restos del barco llamado 'Fénix'. Puedes ver el barco descansando en el lecho marino en un buen día.";
		link.l1 = "¡Ja! ¿Así que está encallado en el bajío? Entonces puedo nadar hasta allí...";
		link.l1.go = "Friend_5";
		break;

	case "Friend_5":
		dialog.text = "No puedes, amigo mío. Primero, es demasiado profundo ahí abajo; segundo, hay muchos cangrejos gigantes. Te destrozarán antes de que llegues al 'San Gerónimo'.";
		link.l1 = "Hm. Bueno, lo pensaré. Al menos, sé que la estatua existe, y eso es lo más importante.";
		if (CheckAttribute(npchar, "quest.chimiset_die"))
			link.l1.go = "prisoner_3";
		else
		{
			if (CheckAttribute(pchar, "questTemp.LSC.Mary"))
				link.l1.go = "freedom_1";
			else
				link.l1.go = "Friend_6";
		}
		AddQuestRecord("LSC", "4");
		break;
		// нода пересечения

	case "Friend_6":
		dialog.text = "Veo que tienes más preguntas. No dudes en preguntar, mi amigo.";
		link.l1 = "Shark Dodson me pidió que encontrara a los cómplices de Chad en el crimen. He encontrado una carta en el cofre de Chad. Hay algo sobre un francotirador y un arma. Parece que quieren asesinar al Shark desde la distancia. ¿Tienes algo en mente?";
		link.l1.go = "Friend_7";
		break;

	case "Friend_7":
		dialog.text = "Mm. ¿Van a disparar al almirante? Necesito pensar... El asunto es que el almirante casi nunca sale de su residencia, y cuando lo hace, está protegido por media docena de piratas. Pero tiene una costumbre, le gusta pasear por la popa tarde en las noches.\nHay dos posiciones para que un francotirador dispare a la residencia del Almirante: la proa del 'Santa Florentina' y un mástil del 'Furia'. Pero un francotirador aún no podrá matar al Almirante desde esas posiciones, debe tener una vista de águila para realizar tal disparo. Además, necesitaría un excelente fusil. Deberías preguntar por la isla sobre personas que tengan acceso a tales armas de fuego.";
		link.l1 = "Je, parece que tienes razón, hay algo sobre un arma en la carta... ¿Has visto a alguien con tal arma?";
		link.l1.go = "Friend_8";
		break;

	case "Friend_8":
		dialog.text = "No. Ni siquiera he visto un arma como esa en mi vida. Pregunta a la gente, tal vez alguien pueda decirte.";
		link.l1 = "Está bien... De todos modos, tu información es valiosa, ¡gracias! Bueno, la última pregunta ahora, aunque no espero que respondas... ¿Has oído hablar del Chico Blanco?";
		link.l1.go = "Friend_9";
		break;

	case "Friend_9":
		dialog.text = "¿Chico blanco? Claro, lo conozco. Ese es el apodo de Olle Christiansen, nuestro idiota. Ahora es un adulto y ya no parece un chico, aunque su mente sigue siendo infantil.";
		link.l1 = "¿Es así? Dime, ¿dónde puedo encontrarlo?";
		link.l1.go = "Friend_10";
		break;

	case "Friend_10":
		dialog.text = "En cualquier lugar de nuestra ciudad. A menudo se le puede encontrar en la tienda, la taberna o en las calles. Tiene el pelo blanco, seguro que lo reconocerás.";
		link.l1 = "¡Estupendo! Gracias, Chimiset, me has ayudado mucho.";
		link.l1.go = "Friend_11";
		break;

	case "Friend_11":
		dialog.text = "¡Siempre me alegra ayudar! Ven a verme si tienes más preguntas.";
		link.l1 = "¡Claro! Tengo que irme ahora. ¡Nos vemos!";
		if (CheckAttribute(pchar, "questTemp.LSC.Mary"))
			link.l1.go = "freedom_2";
		else
			link.l1.go = "Friend_12";
		break;

	case "Friend_12":
		DialogExit();
		NextDiag.CurrentNode = "Chimiset_wait";
		LSC_SetWhiteBoy();								  // ставим Белого Мальчика в магазин
		pchar.questTemp.Saga.SharkHunt = "search_mush_1"; // флаг на магазин - поиск мушкета
		AddQuestRecord("SharkHunt", "11");
		break;

	case "freedom":
		dialog.text = "Y ahí está mi querido amigo a quien le debo mi libertad y quizás hasta mi vida. Gracias por ayudar a mis hermanos a salvarme de ese asqueroso Kapper. Te daré estos amuletos como recompensa. Estoy seguro de que los encontrarás útiles.";
		link.l1 = "¡Gracias! No esperaba eso...";
		link.l1.go = "Friend_1";
		break;

	case "freedom_1":
		dialog.text = "¿Tienes algo más que preguntar, amigo blanco?";
		link.l1 = "Dime, Chimiset, ¿conoces al Chico Blanco?";
		link.l1.go = "Friend_9";
		break;

	case "freedom_2":
		DialogExit();
		NextDiag.CurrentNode = "Chimiset_wait";
		LSC_SetWhiteBoy(); // ставим Белого Мальчика в магазин
		break;

	//--> информационный блок
	case "Chimiset_wait": // стал другом
		if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
		{
			dialog.text = "¡Oh! Mi amigo blanco " + pchar.name + ". ¡No te ahogaste! Los espíritus te salvaron, lo sé...";
			link.l1 = "Estoy bien y vivo, Chimiset. ¿Espíritus? Tal vez tengas razón, todo ha sucedido por culpa de Kukulcán...";
			link.l1.go = "exit";
			npchar.quest.return_isl = "true";
			break;
		}
		dialog.text = "¿Qué te trae por aquí, mi buen amigo?";
		/*if (!CheckAttribute(npchar, "quest.story"))
		{
			link.l1 = "Cuéntame cómo murió el líder de los Narvales. Tú fuiste el único que vio eso.";
			link.l1.go = "story";
		}*/
		if (!CheckAttribute(npchar, "quest.crab"))
		{
			link.l2 = "Has mencionado los cangrejos en el fondo cerca del 'San Geronimo'. ¿Puedes describir esos monstruos?";
			link.l2.go = "crab";
		}
		link.l9 = "Nada especial, Chimiset. Solo quería verte.";
		link.l9.go = "exit";
		NextDiag.TempNode = "Chimiset_wait";
		break;

	case "story":
		dialog.text = "Una historia sobre la muerte de Alan Milrow será escrita aquí.";
		link.l1 = "¡Está bien!";
		link.l1.go = "exit";
		npchar.quest.story = "true";
		NextDiag.TempNode = "Chimiset_wait";
		break;

	case "crab":
		dialog.text = "Nadie sabe de dónde vinieron, ni por qué han alcanzado un tamaño tan gigantesco. No sabemos mucho sobre estas bestias. Existen, mucha gente las ha visto. Se pueden encontrar grupos de ellas entre los restos de barcos en aguas poco profundas. Acechan en el fondo del mar, cazando peces y comiendo toda la basura que tiramos. Son una verdadera amenaza. Sus pinzas pueden infligir heridas graves, y sus mandíbulas liberan un veneno peligroso, similar al veneno de los peces marinos. Si uno se envenena y no se trata, encontrará a su creador. Afortunadamente, la toxina puede neutralizarse con un antídoto hecho de hierbas locales. Había un cazador de cangrejos entre nosotros. Solía traer su carne, un plato endiabladamente delicioso. Pero lo más importante: a menudo traía las garras de esos monstruos y mandíbulas con veneno. eran los principales ingredientes en algunas de mis pociones. Lástima, hace mucho que nadie me trae alguno de esos...";
		link.l1 = "¿Y dónde está ese cazador ahora?";
		link.l1.go = "crab_1";
		break;

	case "crab_1":
		dialog.text = "Toma el aviso. Debes estar preparado para convertirte en presa tú mismo mientras cazas a esas bestias. Un día simplemente no regresó. Por eso te advierto que seas cuidadoso y atento con esas criaturas.";
		link.l1 = "Veo...";
		link.l1.go = "exit";
		npchar.quest.crab = "true";
		NextDiag.TempNode = "Chimiset_wait";
		break;
		//<-- информационный блок

	case "":
		dialog.text = "";
		link.l1 = "";
		link.l1.go = "";
		break;

	case "":
		dialog.text = "";
		link.l1 = "";
		link.l1.go = "";
		break;

	case "":
		dialog.text = "";
		link.l1 = "";
		link.l1.go = "";
		break;

	case "":
		dialog.text = "";
		link.l1 = "";
		link.l1.go = "";
		break;

	case "":
		dialog.text = "";
		link.l1 = "";
		link.l1.go = "";
		break;

	case "":
		dialog.text = "";
		link.l1 = "";
		link.l1.go = "";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
