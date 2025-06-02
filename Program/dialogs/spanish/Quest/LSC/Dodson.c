// Акула: Стивен Додсон
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		// Jason НСО
		if (CheckAttribute(pchar, "questTemp.Patria.DodsonFail"))
		{
			dialog.text = "¡Charles, qué demonios!";
			link.l1 = "Steven, hubo una coincidencia. No pude venir ni informarte sobre mi ausencia...";
			link.l1.go = "patria_33";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.Patria.DodsonAgain"))
		{
			dialog.text = "¡Me alegra verte, amigo! ¿En qué puedo ayudarte? ";
			link.l1 = "Me alegra verte también. ¡Quería agradecerte por el espectáculo perfectamente llevado a cabo!";
			link.l1.go = "patria_29";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") && pchar.questTemp.Patria == "epizode_12_pirates")
		{
			dialog.text = "¡Me alegra verte, amigo! ¿En qué puedo ayudarte?";
			link.l1 = "Tengo una propuesta para ti. ¡Pirata, ya sabes!";
			link.l1.go = "patria";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.Patria.Saga.Shark") && pchar.questTemp.Patria == "epizode_12_talk")
		{
			dialog.text = "¡Ese es nuestro cliente! El trabajo está hecho, tu barón está sentado en una mazmorra bien custodiada. ¿Quizás te gustaría echar un vistazo, je-je?!";
			link.l1 = "Tendré mucho tiempo para hacer eso, ja-ja. ¿Lo tratan bien?";
			link.l1.go = "patria_10";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "begin" && !CheckAttribute(npchar, "quest.Tieyasal"))
		{
			dialog.text = "¡Me alegra verte, camarada! ¿Cómo puedo ayudarte?";
			link.l1 = "He venido de nuevo a pedir tu ayuda.";
			link.l1.go = "tieyasal";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.Guardoftruth.Archy") && pchar.questTemp.Guardoftruth.Archy == "islatesoro")
		{
			dialog.text = "¡Me alegra verte, camarada! ¿Cómo puedo ayudarte?";
			link.l1 = "Steven, tengo algo para ti.";
			link.l1.go = "guardoftruth";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.Saga.Shadows") && pchar.questTemp.Saga.Shadows == "islatesoro")
		{
			dialog.text = "¡Me alegra verte, amigo! ¿En qué puedo ayudarte?";
			link.l1 = "Steven, tengo que preguntarte algo. Puede que no te guste, pero necesito tu ayuda.";
			link.l1.go = "shadows";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.Terrapin") && pchar.questTemp.Terrapin == "islatesoro")
		{
			dialog.text = "Ja, aquí estás, " + pchar.name + ". Esperaba tu llegada. Forest Devil me habló de tus problemas con Tortuga...";
			link.l1 = "También me dijo que ya habías encontrado una solución. ¿Es cierto?";
			link.l1.go = "terrapin";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.Terrapin.Catherina") && pchar.questTemp.Terrapin == "tortuga")
		{
			dialog.text = "¿Cómo estamos, " + pchar.name + "?";
			link.l1 = "Secretos por todas partes... Necesito tu consejo, Steven.";
			link.l1.go = "terrapin_8";
			break;
		}
		// belamour legendary edition хвастовство "Фортуной"
		if (CheckShipTypeInSquadron(SHIP_FRIGATE_L) > 0 && !CheckAttribute(pchar, "questTemp.SharkFrigate"))
		{
			link.l2 = "Sí, quiero mostrarte algo... ¿Te gustaría caminar conmigo hasta el muelle?";
			link.l2.go = "check_out_my_frigate";
		}

		// belamour legendary edition на пару с Акулой
		if (CheckAttribute(pchar, "questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "toDodson")
		{
			dialog.text = "Ah, mi amigo " + GetFullName(pchar) + "¡Entra, es bueno verte! ¿Por qué has venido?";
			link.l1 = "¡Hola, Steven! Bueno, me presenté como prometí. ¿Está lista tu nave?";
			link.l1.go = "SharkGoldFleet";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.SharkGoldFleet") && pchar.questTemp.SharkGoldFleet == "RUinDeal")
		{
			link.l2 = "¿Y qué pasa con tu negocio? ¿No abandonaste esta empresa respecto a la 'Flota Dorada'?";
			link.l2.go = "SharkGoldFleet_10";
		}
		dialog.text = "Ah, mi amigo " + GetFullName(pchar) + "¡Entra, es bueno verte! ¿Por qué has venido?";
		link.l1 = "Sí, visité Isla Tesoro por negocios, y decidí pasar por aquí un minuto.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	// --------------------------------------вариант R-----------------------------------------------
	case "Chad_die":
		dialog.text = "¡Ja! ¿Supongo que eres nuestro visitante nocturno? Me informaron de este accidente demasiado tarde. Revisé tus pertenencias y encontré una carta de Forest Devil. Diablos, casi olía a las selvas de Tierra Firme\nTu nombre es " + GetFullName(pchar) + "¿ No te sorprendas, lo leí en la carta. Mi nombre es Steven Dodson. O simplemente Shark. Shark. Creo que ya has oído hablar de mí. Actualmente ocupo una posición de almirante en esta ciudad o isla, como quieras\nPido disculpas por las acciones de mis hombres anoche. Fue mi orden capturar a todos los que se cuelan en la bodega. Demasiados ladrones entre Narvales y Rivados\n¿Chad te dejó ir, supongo? Extraño. Sólo iba a enviarle una orden para liberarte. ¿Dónde está tu barco? Espero que esté bien?";
		link.l1 = "¿Chad? Por lo que entiendo, tu contramaestre nunca me dejaría salir de la prisión con vida. Lo hice yo mismo y también liberé a un tipo negro de esos... Rivados.";
		link.l1.go = "Chad_die_1";
		break;

	case "Chad_die_1":
		dialog.text = "Me estás contando cosas interesantes, compadre. ¿Y cómo lograste salir del 'Tártaro'? Parece que tendré una buena charla con Chad y sus guardianes de la prisión...";
		link.l1 = "No tendrás ninguna charla con ellos. Me temo que nunca volverán a hablar. Chad amenazó con mantenerme en la jaula para siempre. Me culpó por ser de los Rivados y exigió que lo desmintiera matando al mago negro Chimiset...";
		link.l1.go = "Chad_die_2";
		break;

	case "Chad_die_2":
		dialog.text = "¡¿Qué demonios?! ¡Qué insensata terquedad! Necesitamos a Chimiset vivo, ¡y Chad sabía eso perfectamente! ¿Y por qué asumiría que tú eras de los Rivados, si todos ellos son negros? ¿Qué está tramando, maldito sea?";
		link.l1 = "Está tramando algo que seguramente no te gustará, Steven. Chad me dio un machete y me envió al sótano para matar a Chimiset. Pero el viejo Negro me ha dicho algo importante, y me di cuenta de que si mato a Chimiset, seré el próximo...";
		link.l1.go = "Chad_die_3";
		break;

	case "Chad_die_3":
		dialog.text = "";
		link.l1 = "En lugar de matar al viejo, he abierto un cofre con municiones y he luchado con Chad y sus compinches. ¿Ves ahora por qué ya no puedes hablar con ellos? Todos están muertos.";
		link.l1.go = "Chad_die_4";
		break;

	case "Chad_die_4":
		dialog.text = "¡Maldición! ¡Las noticias son cada vez más aterradoras! ¿Y qué debo hacer con todo este lío?";
		link.l1 = "Escúchame, Steve. Chimiset me dijo que Chad tenía un trato con algunos Narvales - este es el otro clan, según entiendo. Chad planeaba matarte y tomar tu posición. Los Narvales están ansiosos por verte muerto, porque están seguros de que mataste a su líder Allen... o Alan, no recuerdo.";
		link.l1.go = "Chad_die_5";
		break;

	case "Chad_die_5":
		dialog.text = "¡Tonterías! ¡Yo no maté a Alan! Alguien más lo hizo, incluso los Narvales, quizás. ¡Creo que su líder actual - Donald Greenspen - mató a Alan!";
		link.l1 = "No. Chad lo asesinó. Chimiset fue testigo del crimen, por eso querían matarlo también. Chad no quería hacerlo él mismo por alguna razón; parece que temía una maldición de algún tipo. Por eso quería que yo hiciera el trabajo.";
		link.l1.go = "Chad_die_6";
		break;

	case "Chad_die_6":
		dialog.text = "No puedo creerlo... ¿Chad mató a Alan? ¿Pero por qué?";
		link.l1 = "Para dejarte la culpa y hacerte enemigos con los Narvales. Supongo que él fue quien difundió los rumores, porque ¿por qué los Narvales te culparían solo a ti? Steven, están planeando matarte. Y culparían al clan Rivados por eso, aunque no sé cómo van a hacerlo. Chimiset me habló de eso.";
		link.l1.go = "Chad_die_7";
		break;

	case "Chad_die_7":
		dialog.text = "";
		link.l1 = "Además, he encontrado esta carta en el cofre de Chad. Léela. Parece una prueba sólida, aunque sea indirecta.";
		link.l1.go = "Chad_die_8";
		break;

	case "Chad_die_8":
		RemoveItems(pchar, "letter_chad", 1);
		dialog.text = "...(leyendo)... ¡je! No me sorprende la traición de Chad. Ese hijo de perra siempre quiso poder en esta isla. ¡Pero los Narvales! ¡Creer seriamente que fui yo quien mató a Alan! Esto les costará el doble por las provisiones\nDe todos modos, estaba planeando liberar a Chimiset, ya es hora de hacer las paces con ellos. Me has sorprendido, compañero, para ser honesto...";
		link.l1 = "Entiendo, Steven. Tampoco me gusta, me metí en medio de algún lío político desde que llegué a la Isla. Solo vine aquí para encontrarte a ti y a Nathaniel Hawk...";
		link.l1.go = "Chad_die_9";
		break;

	// ноды пересечения
	case "Chad_die_9":
		dialog.text = "¿Qué? ¿Hawk? ¿No está en Jamaica? Es un barón de Maroon town, ¿por qué estaría aquí?";
		link.l1 = "No. Ahora Jackman está al mando allí. Pude averiguar que Hawk llegó allí de la misma manera que yo, a través del portal de Kukulcán.";
		link.l1.go = "Chad_die_10";
		break;

	case "Chad_die_10":
		dialog.text = "¿Qué es todo este disparate? ¿Qué portal? Y aún no has respondido, ¿dónde está tu barco?";
		link.l1 = "No hay barco. Entiendo, Steve, que es difícil de creer, pero realmente llegué aquí a través del ídolo indio desde el Continente... no me mires así, ¡no estoy loco! Yo mismo no entiendo cómo es posible, ¡pero lo es!";
		link.l1.go = "Chad_die_11";
		break;

	case "Chad_die_11":
		dialog.text = "";
		link.l1 = "El chamán en la aldea Miskito ha visto cómo Nathaniel Hawk, quien estaba escapando de los perseguidores, corrió hacia el ídolo indio, conocido como la estatua de Kukulcán, y de repente desapareció. Este chamán me dijo que él mismo había estado en esta Isla, y que llegó allí de la misma manera a través de la estatua...";
		link.l1.go = "Chad_die_12";
		break;

	case "Chad_die_12":
		dialog.text = "";
		link.l1 = "Estoy buscando a Nathan, por eso tuve que seguir sus pasos. Llegué a la estatua a medianoche, tal como me dijo el chamán. ¡No lo creerás, pero la cima de la estatua de piedra era dorada esa noche, y una luz misteriosa brillaba sobre ella!";
		link.l1.go = "Chad_die_13";
		break;

	case "Chad_die_13":
		dialog.text = "";
		link.l1 = "Tan pronto como toqué la estatua, un círculo de luz se formó alrededor del ídolo, el fuego se encendió, y entonces fui absorbido por la estatua. Me arrojaron aquí, en la bodega de carga de tu barco, abajo cerca de la proa, en la brecha...";
		link.l1.go = "Chad_die_14";
		break;

	case "Chad_die_14":
		dialog.text = "";
		link.l1 = "Apenas sobreviví a eso, gracias al chamán, quien me dio una poción especial. Al final, fui atacado por un monstruo, un cangrejo gigante. ¿Espero que ahora confíes en mí?";
		link.l1.go = "Chad_die_15";
		break;

	case "Chad_die_15":
		dialog.text = "¿Te refieres a la parte sobre el cangrejo? Te creo en eso. Hay muchos de esos monstruos alrededor de la isla. Los atraemos con un pez muerto, así que a menudo vigilan nuestra puerta trasera. Asustan a los ladrones hasta que se hacen caca encima. Y lo que has contado sobre el ídolo - aún no estoy loco\nPero tampoco rechazaré tu historia, los lugareños han estado chismeando sobre tales cosas durante varias docenas de años, además, yo mismo vi cosas extrañas hace mucho tiempo en los barcos de los Rivados... no importa.";
		link.l1 = "Juro que es toda la verdad.";
		link.l1.go = "Chad_die_16";
		break;

	case "Chad_die_16":
		dialog.text = "Está bien. Que así sea. Dime, ¿por qué me has estado buscando a mí y a Nathan? Según la carta de Jan, ¿querías que me convirtiera en el jefe de la Hermandad de la Costa?";
		link.l1 = "Exactamente. Muchas cosas han cambiado después de tu desaparición y la de Hawk. Jackman está intentando asumir el papel central entre los piratas. Planea convertirse en su líder, y lo logrará si Jan y yo no lo detenemos.";
		link.l1.go = "Chad_die_17";
		break;

	case "Chad_die_17":
		dialog.text = "";
		link.l1 = "Jackman está interesado en un juego serio y sangriento. Estoy seguro de que fue él quien organizó la emboscada y la caza de Nathaniel. También creo que mató a Blaze. Hacerte líder de la Hermandad de la Costa es la única forma de detenerlo.";
		link.l1.go = "Chad_die_18";
		break;

	case "Chad_die_18":
		dialog.text = "Mira, estaría encantado, pero primero necesitamos abandonar esta isla. Ya he tenido suficiente de ella. Más aún porque puedo dejar a Dexter aquí, él puede manejar los negocios en mi ausencia. No tenía la intención de quedarme aquí tanto tiempo, pero mi barco fue incendiado en una pelea contra los clanes\nNo voy a viajar a través de esos portales, ni siquiera trates de persuadirme, necesito un barco.";
		link.l1 = "No lo haré... Steven, el chamán miskito me dijo que había una estatua de Kukulcán aquí, en la Isla. Parece un ídolo de piedra común. ¿Sabes dónde puedo encontrarla?";
		link.l1.go = "Chad_die_19";
		break;

	case "Chad_die_19":
		dialog.text = "No lo sé. Nunca he visto estatuas así. Pregunta a alguien más.";
		link.l1 = "Verás, si encuentro esta estatua, podré salir de esta isla sin un barco. El viaje ya no me asusta. Y luego regresaría aquí de una manera normal y te llevaría de aquí.";
		if (pchar.questTemp.LSC == "entrance" || pchar.questTemp.LSC == "mary")
			link.l1.go = "entrance_4";
		else
			link.l1.go = "Chad_die_20";
		break;
		// ноды пересечения

	case "Chad_die_20":
		dialog.text = "Entiendo, pero no puedo ayudarte. Además, este asunto de asesinato es bastante perturbador. Chad está muerto, pero dudo que los Narvales abandonen su plan. No quiero vivir esperando recibir un disparo por la espalda cada día. Ya que me necesitas vivo y ya estás involucrado en este lío, te ofrezco investigar esta conspiración.\nEres un recién llegado, es una ventaja. Encuentra a los socios de Chad y tráelos a mí o mátalos donde estén, no me importa. Habla con Chimiset, el viejo negro sabe más de lo que ya nos ha contado.\nTen cuidado con los Narvales, no cruces sus fronteras a menos que tengas una contraseña. Cambian las contraseñas cada semana.\nUna vez que la amenaza sea eliminada, te proporcionaré las direcciones de navegación y toda la información que necesites.\nVe y encuentra a los responsables. Restaura el orden. Me aseguraré de que limpien la prisión después de ti. Y necesitamos un nuevo carcelero. Y necesito algo de ron, no me siento bien.";
		link.l1 = "Bien, Steven. Hagámoslo...";
		link.l1.go = "Chad_die_21";
		break;

	case "Chad_die_21":
		DialogExit();
		NextDiag.CurrentNode = "Total_wait";
		pchar.questTemp.LSC.rvd_friend = "true"; // флаг на проход по кораблям ривадос
		pchar.rvd_friend = true;				 // ривадосы не будут останавливать где просят пароль
		sld = characterFromId("Chimiset");
		sld.dialog.currentnode = "Friend"; // ноду Чимисету
		pchar.quest.LSC_Eddy.win_condition.l1 = "location";
		pchar.quest.LSC_Eddy.win_condition.l1.location = "ProtectorFisher";
		pchar.quest.LSC_Eddy.function = "LSC_EddyTalk"; // на разговор с Эдди
		AddQuestRecord("SharkHunt", "10");
		sld = characterFromId("Facio");
		sld.quest.parol = true;
		for (i = 7; i <= 12; i++)
		{
			sld = CharacterFromID("RivadosSold_" + i);
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
		}
		for (i = 4; i <= 8; i++)
		{
			sld = CharacterFromID("RivadosProt_" + i);
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
		}
		AddSimpleRumourCityTip("Imagínate: alguien ha matado al carcelero del almirante, Chad Kapper. ¡Imposible! Sin duda, ese era el trabajo del mago Rivados...", "LostShipsCity", 7, 2, "LSC", "");
		AddSimpleRumourCityTip("Escuché que Chad Kapper está muerto. No hubo declaración oficial; su cuerpo nunca fue encontrado, tampoco. ¿Quizás, el almirante simplemente le había dado una misión secreta?", "LostShipsCity", 7, 2, "LSC", "");
		AddSimpleRumourCityTip("No veo a nuestro carcelero Chad Kapper. Algunos dicen que fue asesinado y otros no están de acuerdo. De todos modos, nadie lo ha visto muerto.", "LostShipsCity", 7, 2, "LSC", "");
		AddSimpleRumourCityTip("¡Dicen que el almirante ha doblado los precios de las provisiones para narvales! ¡Ese pirata es realmente imprudente!", "LostShipsCity", 7, 3, "LSC", "");
		break;

	case "Mary_Die":
		dialog.text = "Bueno, ¿qué tienes, " + pchar.name + "¿Alguna noticia sobre los Narvales?";
		link.l1 = "Sí. Te alegrará saber, Steve, que la conspiración fue desvelada y los conspiradores están muertos. Tengo todas las pruebas.";
		link.l1.go = "Mary_Die_1";
		break;

	case "Mary_Die_1":
		if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack"))
			dialog.text = "Eso pensé cuando escuché el tiroteo... Cuéntame más, estoy escuchando.";
		else
			dialog.text = "¿Es así? ¡Me alegra mucho escuchar eso! Cuéntame más, estoy escuchando.";
		link.l1 = "Todo fue planeado por tu contramaestre, Chad Kapper. Mató a Alan Milrow en la prisión del 'Tártaro', y estaba difundiendo rumores sobre tu implicación. Creo que los Narvales estaban realmente enfadados, y fue un golpe duro para la novia de Alan, la Roja Mary...";
		link.l1.go = "Mary_Die_2";
		break;

	case "Mary_Die_2":
		dialog.text = "";
		link.l1 = "Mary estaba ansiosa por vengarse y Chad Kapper lo usó para sus propios fines. Hicieron un astuto plan para atentar contra tu vida. Todos aquí saben de tu hábito de pasear por la popa del 'San Augustine' cada noche.";
		link.l1.go = "Mary_Die_3";
		break;

	case "Mary_Die_3":
		dialog.text = "¡Eh! Reconsideraré mis costumbres... Adelante.";
		link.l1 = "Necesitaban un mosquete de largo alcance y precisión para llevar a cabo su plan, y así se lo proporcionó un tal Adolf Barbier. Pero su stutzen fue empeñado a Giuseppe Fazio, así que Mary y Chad le dieron suficiente dinero para recuperarlo. Adolf lo sacó del empeño...";
		link.l1.go = "Mary_Die_4";
		break;

	case "Mary_Die_4":
		dialog.text = "";
		link.l1 = "Hicieron que Cíclope Marcello, un ex cazador real, te matara. Tenía que recibir el rifle y dispararte hasta la muerte. Después de eso, Mary lo habría matado y usado su cadáver y rifle como prueba de que los Rivados eran responsables del ataque. Cíclope Marcello es un mulato, ¿sabes...?";
		link.l1.go = "Mary_Die_5";
		break;

	case "Mary_Die_5":
		dialog.text = "¡Qué bastardo tan listo!";
		link.l1 = "Después de eso, los Narvales y los piratas atacarían a los Rivados y los destruirían. Chad se convertiría en almirante y Mary sería su amante. Sin embargo, quizás él le cortaría la garganta, ya que sabía demasiado. Muy probablemente...";
		if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt.TownAttack"))
			link.l1.go = "Mary_Die_6a";
		else
			link.l1.go = "Mary_Die_6";
		break;

	case "Mary_Die_6":
		dialog.text = "";
		link.l1 = "De todos modos, ya se acabó. Adolf no era lo suficientemente hablador, y tuve que matarlo justo en su camarote. También tuve que lidiar con Mary y Cyclops, que habían venido a obtener el stutzen de Adolf. Se dieron cuenta de quién era yo de inmediato y me atacaron al instante.";
		link.l1.go = "Mary_Die_7";
		break;

	case "Mary_Die_7":
		dialog.text = "¿Así que están tumbados dentro de 'Santa Florentina', verdad?";
		link.l1 = "Sí. Los tres.";
		link.l1.go = "Mary_Die_8";
		break;

	case "Mary_Die_8":
		dialog.text = "Eso es bueno que ningún testigo esté involucrado en este desorden. Me encargaré de los cuerpos. Hiciste un buen trabajo, " + pchar.name + "¡Si estuvieras en mi tripulación, definitivamente te habría hecho mi primer oficial!";
		link.l1 = "Gracias por tan alta respuesta. Y, finalmente, echa un vistazo a estas cartas. Las tomé de los cuerpos de Cíclope y la pobre Mary...";
		link.l1.go = "Mary_Die_9";
		AddSimpleRumourCityTip("¿Lo has oído? Nuestra pendenciera y alocada Red Mary ha desaparecido. No me sorprendería que estuviera muerta...", "LostShipsCity", 10, 1, "LSC", "");
		AddSimpleRumourCityTip("Dicen que Red Mary ha desaparecido. ¿Te has enterado?", "LostShipsCity", 10, 1, "LSC", "");
		AddSimpleRumourCityTip("Mary Casper ha desaparecido. Algunos dicen que sigue en su cabaña, pero yo no lo creo. Ha pasado demasiado tiempo desde la última vez que hubo luz en ella.", "LostShipsCity", 10, 1, "LSC", "");
		AddSimpleRumourCityTip("Dicen que Red Mary fue asesinada. ¡Pobre chica! Sí, tenía un carácter duro, pero todo el mundo la quería. ¿Quién podría haber hecho algo tan terrible?", "LostShipsCity", 10, 1, "LSC", "");
		break;

	case "Mary_Die_6a":
		dialog.text = "";
		link.l1 = "De todas formas, ya se acabó. Adolf no fue lo suficientemente hablador, y tuve que matarlo justo en su camarote. También tuve que encargarme de Mary y Cyclops, que vinieron a buscar el stutzen de Adolf. Se dieron cuenta de quién era yo de inmediato y me atacaron enseguida.";
		link.l1.go = "Mary_Die_7a";
		break;

	case "Mary_Die_7a":
		dialog.text = "Es una lástima que hayas comenzado una pelea en 'Eva'. Ahora los Narvales saben que eres responsable de matar a sus hombres, tales acciones no mejorarán tu reputación. Lo mismo se puede decir de la mía. No los visites hasta que soluciones este conflicto.\nEn general, lo hiciste bien, " + pchar.name + "¡Si hubieras estado en mi tripulación, definitivamente te habría hecho mi primer oficial!";
		link.l1 = "¡Gracias por tan alta respuesta! Y, finalmente, echa un vistazo a estas cartas. Las tomé de los cuerpos de Cíclope y la pobre Mary...";
		link.l1.go = "Mary_Die_9";
		AddSimpleRumourCityTip("¡Qué masacre has hecho aquí! ¡Los narvales no lo olvidarán!", "LostShipsCity", 5, 2, "LSC", "");
		AddSimpleRumourCityTip("Entiendo matar a Cíclope y a dos bandidos Narval... Pero la chica, ¿por qué has matado a la chica? Pobre Mary...", "LostShipsCity", 7, 5, "LSC", "");
		break;

	case "Mary_Die_9":
		RemoveItems(pchar, "letter_chad", 1);
		RemoveItems(pchar, "letter_chad_1", 1);
		dialog.text = "¿Pobre Mary? ¿Sientes lástima por esa ramera?";
		link.l1 = "En verdad sí. Verás, Chad la engañó y la usó. Ella no pudo resistir sus sentimientos y su temperamento impulsivo... y ahí es donde la llevó.";
		link.l1.go = "Mary_Die_10";
		break;

	case "Mary_Die_10":
		TakeNItems(pchar, "gold_dublon", 500);
		Log_Info("Has recibido 500 doblones");
		PlaySound("interface\important_item.wav");
		CloseQuestHeader("SharkHunt");
		bDisableFastReload = false; // belamour legendary edition
		dialog.text = "Bueno, ve a ver al hermano Julián y enciende una vela... Yo no lo haré, sin embargo. Está bien, dejemos el tema. Te estoy agradecido, " + pchar.name + ", por tu ayuda. Ahora puedes contar con mi apoyo. Quiero pagarte por tu excelente trabajo. Aquí, toma quinientos doblones.";
		link.l1 = "¡Bien, gracias!";
		link.l1.go = "LSC_navy";
		AddSimpleRumourCityTip("Dicen que el almirante le respeta, señor...", "LostShipsCity", 15, 2, "LSC", "");
		AddSimpleRumourCityTip("Dicen que eres el amigo leal del almirante. ¿Es eso cierto?", "LostShipsCity", 15, 2, "LSC", "");
		break;

	// ----------------------------------------вариант N---------------------------------------------------
	case "entrance":
		dialog.text = "¿Qué quieres? No te recuerdo...";
		link.l1 = "Por supuesto que no, nunca nos hemos conocido antes, y yo he llegado aquí recientemente. ¡Hola, Steven! ¡Qué suerte tan rara! Te he encontrado después de todo, te he estado buscando aunque no esperaba encontrarte aquí!";
		link.l1.go = "entrance_1";
		break;

	case "entrance_1":
		dialog.text = "Espera, amigo, cálmate. ¿Buscándome a mí? No me gusta. ¿Por qué demonios has estado buscándome?";
		link.l1 = "Ya veo. Entonces intentemos de nuevo. Aquí, toma la carta. Está escrita por Jan Svenson para ti. Supongo que todas tus sospechas se disiparán después de leerla.";
		link.l1.go = "entrance_2";
		break;

	case "entrance_2":
		RemoveItems(pchar, "letter_svenson", 1);
		PlaySound("interface\important_item.wav");
		dialog.text = "(leyendo)... Hm. Eso explica mucho. Y pensé que me ibas a dar una marca negra por la muerte de Blaze. Sabes, últimamente ha habido muchos tipos ansiosos por hacer eso. ¿Dejaste tu barco en el anillo exterior? ¿Y cómo supiste que yo estaba aquí?";
		link.l1 = "No lo hice. Fue una oportunidad afortunada. Y sobre Blaze... Jan y yo pensamos que no eres responsable de su muerte.";
		link.l1.go = "entrance_3";
		break;

	case "entrance_3":
		dialog.text = "Y tienes razón. No lo soy. Alguien está intentando culparme, eso es cierto. Pero no lo maté.";
		link.l1 = "Eso es bueno. Interesante, vine aquí para encontrar a Nathaniel Hawk, ¡pero te he encontrado a ti en su lugar, ja-ja!";
		link.l1.go = "Chad_die_9";
		break;

	case "entrance_4":
		dialog.text = "Lo entiendo, pero no puedo ayudarte. Tienes que hablar de eso con los veteranos de esta Isla. Habla con el hechicero de Rivados, Chimiset. El viejo negro sabe mucho más de lo que dice.";
		link.l1 = "¿Y dónde puedo encontrar a este hechicero?";
		if (pchar.questTemp.LSC == "mary")
			link.l1.go = "mary";
		else
			link.l1.go = "entrance_5";
		break;

	case "entrance_5":
		dialog.text = "En mi prisión, en 'Tártaro'. De todos modos, estaba planeando liberarlo, es hora de mejorar nuestras relaciones con los Rivados. ¡Correcto! Ve a la prisión, dile a Chad Kapper, él es el carcelero, que he ordenado liberar a Chimiset. Dile al hombre negro por qué te envié, dile que lo liberaré si es lo suficientemente hablador. Estoy seguro de que esto lo hará hablar.";
		link.l1 = "Mm... Soy un novato aquí. ¿Dónde está la prisión?";
		link.l1.go = "entrance_6";
		break;

	case "entrance_6":
		dialog.text = "Mantén lo siguiente en mente. Sal de mi residencia, cruza el puente, gira a la izquierda, pasa por la fragata Carolina hacia el galeón Gloria y llegarás a Esmeralda. Busca un letrero de tienda y entra por las puertas que hay debajo. Pasa por la puerta en la parte de proa del barco y llegarás a Tártaro\nTen cuidado en Esmeralda, es propiedad del clan Narvales, aunque otros pueden visitarla. No cruces a sus luchadores y evita cualquier problema.";
		link.l1 = "¿Quiénes son esos Rivados y Narvales?";
		link.l1.go = "entrance_7";
		break;

	case "entrance_7":
		dialog.text = "Los clanes han estado viviendo aquí durante mucho tiempo. Representan a los descendientes de los primeros colonos. Los Narvales son principalmente ingleses, holandeses y franceses, los Rivados son todos negros. Cada clan tiene un líder, poseen varios barcos y no permiten que otros entren en su territorio\nDebes conocer las contraseñas para visitarlos. Cambian las contraseñas cada semana.";
		link.l1 = "Está bien. Me encargaré de eso. ¿Me dejarán entrar a la prisión?";
		link.l1.go = "entrance_8";
		break;

	case "entrance_8":
		dialog.text = "Lo harán. Aquí está la llave, así Chad sabrá que te he enviado allí. Tómala.";
		link.l1 = "Bien. Entonces hablaré con ese... Chimiset y luego volveré con los resultados.";
		link.l1.go = "entrance_9";
		break;

	case "entrance_9":
		DialogExit();
		GiveItem2Character(pchar, "key_capper");
		NextDiag.CurrentNode = "Total_wait";
		sld = characterFromId("Chimiset");
		sld.dialog.currentnode = "prisoner"; // даем ноду Чимисету
		sld.quest.chimiset_die = "true";
		ChangeCharacterAddressGroup(sld, "Tartarusprison", "quest", "prison2"); // в закрытую клетку
		LAi_SetGroundSitTypeNoGroup(sld);
		sld = characterFromId("Capper");
		sld.dialog.currentnode = "prisoner";										// даем ноду Капперу
		LAi_LocationFightDisable(&Locations[FindLocation("Tartarusprison")], true); // запретить драться
		// прерывания на локаторы тартаруса
		pchar.quest.LSC_TartarusEntrance1.win_condition.l1 = "locator";
		pchar.quest.LSC_TartarusEntrance1.win_condition.l1.location = "LostShipsCity_town";
		pchar.quest.LSC_TartarusEntrance1.win_condition.l1.locator_group = "reload";
		pchar.quest.LSC_TartarusEntrance1.win_condition.l1.locator = "reload51";
		pchar.quest.LSC_TartarusEntrance1.win_condition.l2 = "item";
		pchar.quest.LSC_TartarusEntrance1.win_condition.l2.item = "key_capper";
		pchar.quest.LSC_TartarusEntrance1.function = "LSC_TartarusEntrance1_Open";
		pchar.quest.LSC_TartarusEntrance2.win_condition.l1 = "locator";
		pchar.quest.LSC_TartarusEntrance2.win_condition.l1.location = "LostShipsCity_town";
		pchar.quest.LSC_TartarusEntrance2.win_condition.l1.locator_group = "reload";
		pchar.quest.LSC_TartarusEntrance2.win_condition.l1.locator = "reload52";
		pchar.quest.LSC_TartarusEntrance2.win_condition.l2 = "item";
		pchar.quest.LSC_TartarusEntrance2.win_condition.l2.item = "key_capper";
		pchar.quest.LSC_TartarusEntrance2.function = "LSC_TartarusEntrance2_Open";
		AddQuestRecord("SharkHunt", "19");
		break;

	case "entrance_10":
		dialog.text = "Entonces, ¿has estado en el 'Tártaro'?";
		link.l1 = "Sí. He dado tus órdenes a Chad y he hablado con el hombre negro.";
		link.l1.go = "entrance_11";
		break;

	case "entrance_11":
		dialog.text = "¿Te dijo algo interesante el mago?";
		link.l1 = "Oh, sí. Me dijo dónde encontrar el ídolo de teletransportación de Kukulcán. Estaba en el barco 'San Geronimo', que se había hundido en el bajío cerca del territorio de los Narvales.";
		link.l1.go = "entrance_12";
		break;

	case "entrance_12":
		dialog.text = "¡Ja-ja-ja, genial! ¿Así que tu 'portal' está en el fondo ahora? Bueno, amigo, me temo que estás atrapado en esta isla. Así que únete a mí y a mis hombres...";
		link.l1 = "Encontraré la manera de llegar al ídolo. Encontraré el camino. Ahora. Chimiset me dijo que no debes confiar en Kapper, porque vio a Chad matar a un tal Alan Milrow, el jefe de los Narvales, con sus propios ojos.";
		link.l1.go = "entrance_13";
		break;

	case "entrance_13":
		dialog.text = "¿Qué?! ¿Chad mató a Alan? ¡Ese brujo está loco! ¡Simplemente no puede ser verdad!";
		link.l1 = "Sabes, Steve, Chimiset está realmente asustado. No creo que me estuviera mintiendo.";
		link.l1.go = "entrance_14";
		break;

	case "entrance_14":
		dialog.text = "¡Maldita sea, eso sí que son malas noticias! El asesinato de Alan ya ha arruinado mi reputación entre los Narvales - algunos de ellos decidieron que yo era el responsable, ¡y ahora resulta que uno de mis oficiales podría haberlo hecho!";
		link.l1 = "Parece que la gente gusta de culparte por los pecados que no son tuyos...";
		link.l1.go = "entrance_15";
		break;

	case "entrance_15":
		dialog.text = "Sí, eso es preocupante...";
		link.l1 = "Y ahora, la 'mejor' noticia para ti: el viejo me dijo que había escuchado varias conversaciones y descubrió que algunos de tus hombres planeaban matarte. Te contará más solo después de que lo liberes, y en privado.";
		link.l1.go = "entrance_16";
		break;

	case "entrance_16":
		dialog.text = "¡Genial! ¡Y todo esto por tu culpa! Sin ofender, solo estoy bromeando. Mi cabeza da vueltas: Chad mató a Alan, mis hombres están planeando un intento contra mi vida... ¿Te ha contado el viejo negro algún detalle?";
		link.l1 = "No. Le teme demasiado a Chad, por lo que entendí.";
		link.l1.go = "entrance_17";
		break;

	case "entrance_17":
		dialog.text = "Está bien. Diré a Rivados que quiero reunirme con Chimiset. Veremos qué me dice. Y en cuanto al intento... está bien, tendré cuidado. Entonces, ¿qué vas a hacer ahora, " + pchar.name + "?";
		link.l1 = "No   en particular aún. Caminaré por la Isla y conoceré a los lugareños - quizás se me ocurra una idea de cómo salir de este lugar. Y primero necesito encontrar a Nathan Hawk, él es la razón por la que estoy aquí.";
		link.l1.go = "entrance_18";
		break;

	case "entrance_18":
		dialog.text = "Ya veo. No olvides visitarme cuando encuentres una salida de esta isla - te daré las direcciones de navegación, no podrás volver aquí sin ellas. También te contaré algunos detalles importantes.";
		link.l1 = "Está bien. ¡Te visitaré seguro, Steve!";
		link.l1.go = "entrance_19";
		break;

	case "entrance_19":
		DialogExit();
		NextDiag.CurrentNode = "Total_wait";
		sld = characterFromId("Facio");
		sld.quest.parol = true;
		// прерывание на вызов к Акуле
		pchar.quest.LSC_GotoShark.win_condition.l1 = "Timer";
		pchar.quest.LSC_GotoShark.win_condition.l1.date.hour = 9.00;
		pchar.quest.LSC_GotoShark.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.LSC_GotoShark.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.LSC_GotoShark.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.LSC_GotoShark.win_condition.l2 = "location";
		pchar.quest.LSC_GotoShark.win_condition.l2.location = "LostShipsCity_town";
		pchar.quest.LSC_GotoShark.function = "LSC_GotoShark";
		AddQuestRecord("SharkHunt", "21");
		break;

	case "entrance_20":
		dialog.text = "Es bueno que hayas venido, " + pchar.name + "Te he estado esperando. Malas noticias. Chimiset está muerto, Chad Kapper ha desaparecido sin dejar rastro.";
		link.l1 = "Maldita sea... Estoy seguro de que Chad ha matado a Chimiset. El viejo negro estaba tan asustado, y no sin razón.";
		link.l1.go = "entrance_21";
		break;

	case "entrance_21":
		dialog.text = "No tengo ninguna duda de eso. Demonios, la situación empeora cada hora. Casi había arreglado contactos sólidos y directos con Eddie el Negro y ahora esto. Bueno, podemos olvidarnos de la amistad con los Rivados.\nSaben que hablaste con Chimiset antes de que muriera, y te consideran uno de mis hombres, así que evita contactarlos.";
		link.l1 = "Sí, qué lástima...";
		link.l1.go = "entrance_22";
		break;

	case "entrance_22":
		dialog.text = "Te he pedido que vengas no solo para contarte noticias. He recibido una carta de nuestro mediador y diplomático, Giuseppe Fazio, me invita a visitar su cabaña en Carolina a medianoche. También menciona que debo ir solo, porque mi vida está en juego y no se puede confiar en nadie\nEsto tiene sentido, Chimiset nos advirtió sobre un traidor cercano a mí. Sin embargo, huele demasiado sospechoso... solo, a medianoche... Normalmente, el gordo viene a mí mismo. De todos modos, voy a pedir tu ayuda\nTécnicamente, no eres uno de mis hombres y eres nuevo aquí. Jan te caracterizó como un hombre ingenioso y valiente con buenas habilidades en esgrima. Quiero que me escoltes a la reunión a medianoche...";
		link.l1 = "No necesitas preguntarme, Steven. Estoy dentro. Tampoco me gusta esta invitación - huele a trampa.";
		link.l1.go = "entrance_23";
		break;

	case "entrance_23":
		dialog.text = "Quizás me equivoque y no haya trampa, pero será mejor que esté preparado. Me alegra que hayas aceptado. Ven a la cubierta del 'San Augustine' a medianoche, y iremos a ver a Fazio, su viejo cascarón no está lejos de aquí.";
		link.l1 = "Trato hecho. Estaré en la cubierta del 'San Augustine' a medianoche y bien armado.";
		link.l1.go = "entrance_24";
		break;

	case "entrance_24":
		DialogExit();
		NextDiag.CurrentNode = "Total_wait";
		pchar.quest.LSC_GotoShark.win_condition.l1 = "Timer";
		SetFunctionTimerCondition("LSC_MeetingSharkAugustine", 0, 0, 1, false); // таймер
		AddQuestRecord("SharkHunt", "22");
		break;

	case "caroline":
		dialog.text = "Me alegra verte, " + pchar.name + ". No perdamos tiempo y veamos qué tiene que decir ese gordo de Fazio. ¡Sígueme!";
		link.l1 = "Vamos, Steve. Mantén tu arma lista...";
		link.l1.go = "caroline_1";
		break;

	case "caroline_1":
		DialogExit();
		sld = characterFromId("Dodson");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload25", "CarolineBank", "barmen", "bar2", "LSC_CarolineOpen", -1);
		break;

	case "caroline_2":
		dialog.text = "¿Y dónde está ese maldito gordo? ¿A dónde se fue? Somos sus invitados y no nos está dando la bienvenida. ¿Lo ves, " + pchar.name + "? Quizás deberíamos revisar sus cofres, podría estar dentro de ellos...";
		link.l1 = "No podrá abrir ningún cofre en el mundo de todos modos. ¡Silencio! ¡Steven! Hay ruido afuera...";
		link.l1.go = "caroline_3";
		break;

	case "caroline_3":
		dialog.text = "¡Maldición! Tienes razón. Parece que estamos en problemas." + pchar.name + ".";
		link.l1 = "...";
		link.l1.go = "caroline_4";
		break;

	case "caroline_4":
		DialogExit();
		LAi_SetPlayerType(pchar);
		// запускаем Мэри, Чада и нарвалов - будет лютое рубилово
		sld = characterFromId("Capper");
		sld.cirassId = Items_FindItemIdx("cirass1");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload3");
		sld = characterFromId("Mary");
		sld.greeting = "mary_4";
		int iScl = MOD_SKILL_ENEMY_RATE * 10 + 2 * sti(pchar.rank);
		LAi_SetHP(sld, 250 + iScl, 250 + iScl); // усилим
		sld.dialog.currentnode = "caroline";
		ChangeCharacterAddressGroup(sld, "CarolineBank", "reload", "reload2");
		LAi_SetActorType(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

	case "caroline_5":
		dialog.text = "¡Argh! Lo hicimos... Para ser honesto, pensé que estábamos muertos por seguro.";
		link.l1 = "He estado en problemas peores que este. Pero admito, esos bastardos eran duros. Chimiset tenía razón al advertirnos: Chad es un traidor. ¿Quién era la chica que los comandaba?";
		link.l1.go = "caroline_6";
		break;

	case "caroline_6":
		dialog.text = "Su nombre es Mary Casper, también conocida como Mary la Roja, la exnovia del difunto Alan Milrow. Entiendo por qué Chad ha venido aquí, quería ganar mi posición pero ¿qué estaba haciendo ella aquí?";
		link.l1 = "Está bastante claro. Dijiste que ella era su amante, sus intenciones son claras - venganza. La pobre chica no sabía que estaba luchando del mismo lado que el asesino de su novio.";
		link.l1.go = "caroline_7";
		break;

	case "caroline_7":
		dialog.text = "Tiene sentido. ¡Pues ahora pagarán por todo! Dejaré de venderles suministros y provisiones... que se mueran de hambre. Mis hombres pueden soportar cualquier asedio, en caso de que los Narvales intenten asaltar el San Agustín, los dispararemos como perros.\nVan a lamentar haber actuado contra mí de manera tan vil. ¡Clavaré el gordo trasero de Fazio a la pared detrás de mi silla!";
		link.l1 = "Espera, Steve. Parece que no está tan claro. Dame un día y trataré de investigar este lío. Estoy seguro de que Chad es el único responsable. Mató a Milrow, difundió el rumor de que fuiste tú, usó a la novia de Alan...";
		link.l1.go = "caroline_8";
		break;

	case "caroline_8":
		dialog.text = "Bien. Investiga. Tal vez, no hayamos encontrado a todos los conspiradores aún. Y yo iré a tomar un poco de ron. Y, " + pchar.name + ": Te debo una. Puedes contar conmigo en todo. Obtendrías el puesto de contramaestre si hubieras estado en mi tripulación.";
		link.l1 = "¡Gracias por tan alta respuesta! Trabajaremos juntos cuando te conviertas en jefe de la Hermandad de la Costa de todos modos. Ve y descansa un poco, y revisaré esta cabaña, quizá encuentre algo útil.";
		link.l1.go = "caroline_9";
		break;

	case "caroline_9":
		dialog.text = "Bien. Enviaré a mis hombres aquí para limpiar antes del amanecer - no queremos asustar a la gente con cadáveres. ¡Bueno, los cangrejos tendrán una buena cena esta noche! ¡Nos vemos!";
		link.l1 = "Te veo...";
		link.l1.go = "caroline_10";
		break;

	case "caroline_10":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "SanAugustineResidence", "sit", "sit1", "LSC_SharkReturnSit", 10.0);
		AddQuestRecord("SharkHunt", "24");
		break;

	case "narval":
		dialog.text = "Bueno, " + pchar.name + ", ¿supongo que tu investigación fue fructífera?";
		link.l1 = "Puedes decirlo así. Los Narvales no están involucrados en el atentado contra tu vida. Excepto Mary y esos tipos que nos encontraron en el 'Carolina'. Creo que ella los instigó a atacarnos. Fazio se vio obligado a enviarte la invitación. He encontrado la carta en su camarote que explica mucho. Léela.";
		link.l1.go = "narval_1";
		break;

	case "narval_1":
		RemoveItems(pchar, "letter_chad_1", 1);
		dialog.text = "(leyendo)... Hum. Parece de Fazio. Claro, ¿qué podría hacer contra Chad...? Estaba salvando su pellejo gordo. Parece que todo fue por culpa de mi contramaestre...";
		link.l1 = "Ahora lo ves por ti mismo. Los motivos son claros, y sabemos por qué Chad mató a Chimiset y Alan. Kapper quería convertirse en el almirante de la isla. He visitado al jefe de los Narvales, Donald Greenspen. Juró que ni él ni ninguno de sus hombres estaban conspirando contra ti.";
		link.l1.go = "narval_2";
		break;

	case "narval_2":
		dialog.text = "¿Confías en él?";
		link.l1 = "Lo hago. Donald limpiará tu nombre de las acusaciones de la muerte de Alan. Está listo para visitarte personalmente y ofrecerte disculpas oficiales. Tú también fuiste culpado por nada, ¿recuerdas?";
		link.l1.go = "narval_3";
		break;

	case "narval_3":
		dialog.text = "Está bien, declarar una guerra sería un poco exagerado. No estamos en posición de comenzar un derramamiento de sangre. Además, parece que solo unos pocos canallas son responsables de esto, no todo el clan\n¿Dices que Donald está dispuesto a disculparse? Bien, usemos eso para establecer relaciones positivas con los Narvales, los Rivados están perdidos para nosotros de todos modos.";
		link.l1 = "Eso es un buen punto, Steven. Ahora es el momento perfecto para ello.";
		link.l1.go = "narval_4";
		break;

	case "narval_4":
		dialog.text = "Está bien. Dile a Donald que estoy listo para verlo y hacer las paces.";
		link.l1 = "Estoy en camino.";
		link.l1.go = "narval_5";
		break;

	case "narval_5":
		dialog.text = "Espera, " + pchar.name + "Lo hiciste bien y quiero pagarte con buenas monedas. Aquí, toma estos quinientos doblones.";
		link.l1 = "¡Gracias!";
		link.l1.go = "LSC_navy";
		TakeNItems(pchar, "gold_dublon", 500);
		Log_Info("Has recibido 500 doblones");
		PlaySound("interface\important_item.wav");
		AddQuestRecord("SharkHunt", "27");
		pchar.questTemp.Saga.SharkHunt = "find"; // флаг - покушение предотвращено
		sld = characterFromId("Grinspy");
		sld.dialog.currentnode = "shark_16";						  // ноду Дональду Гринспи
		SetFunctionTimerCondition("LSC_FacioReturn", 0, 0, 1, false); // вертаем на место Фацио через сутки
		AddSimpleRumourCityTip("Dicen que el almirante le respeta, señor...", "LostShipsCity", 15, 2, "LSC", "");
		AddSimpleRumourCityTip("Dicen que eres el amigo leal del almirante. ¿Es eso cierto?", "LostShipsCity", 15, 2, "LSC", "");
		break;

	// ----------------------------------------вариант M----------------------------------------------------
	case "mary":
		dialog.text = "En mi prisión 'Tártaro'. Puedes ir allí y verlo. Te daré la llave y Chad Kapper no pondrá obstáculos en tu camino...";
		link.l1 = "Espera, Steven. Creo que no debería ir a ver a Chad Kapper todavía...";
		link.l1.go = "mary_1";
		break;

	case "mary_1":
		dialog.text = "¿Y por qué no deberías? ¿Qué, no te gusta?";
		link.l1 = "En realidad, eres tú a quien no le gusta. Tengo malas noticias para ti. Chad Kapper está planeando atentar contra tu vida.";
		link.l1.go = "mary_2";
		break;

	case "mary_2":
		dialog.text = "¿Qué?! Explícate. ¿Quién dijo eso?";
		link.l1 = "Déjame contarte toda la historia. Eso sería mejor.";
		link.l1.go = "mary_3";
		break;

	case "mary_3":
		dialog.text = "Bueno, dime, entonces...";
		link.l1 = "Después de encontrarme en la bodega inundada, salí por el agujero y nadé entre los naufragios para encontrar un lugar seguro. Finalmente, subí al viejo filibote y entré en el barco. Había una pelea entre una chica con chaqueta roja y dos tipos grandes...";
		if (pchar.questTemp.LSC.Mary == "alive")
			link.l1.go = "mary_4"; // Мэри жива
		else
			link.l1.go = "mary_15";
		break;

	case "mary_4":
		dialog.text = "Je, parece que Mary la Roja finalmente ha cabreado a alguien.";
		link.l1 = "Le ayudé y terminamos con esos bastardos. Tuvimos una charla interesante después de eso... Dime, Steve, ¿quiénes son estos Narvales y Rivados? Ella usaba estas palabras tan a menudo que me dio vergüenza preguntarle qué significaban realmente.";
		link.l1.go = "mary_5";
		break;

	case "mary_5":
		dialog.text = "Los grupos de habitantes locales que han estado viviendo aquí durante mucho tiempo. Son los descendientes de los primeros colonos de la Isla Justicia. Los Narvales son principalmente ingleses, holandeses y franceses, mientras que los Rivados son todos negros. Estos clanes tienen sus propios líderes, sus propios varios barcos y no permiten que otros entren en sus territorios. Debes conocer sus contraseñas en caso de que quieras visitar los barcos de los clanes. Las cambian cada semana.";
		link.l1 = "Ya veo. ¿Supongo que Mary está con los Narvales?";
		link.l1.go = "mary_6";
		break;

	case "mary_6":
		dialog.text = "Sí, esa chica expresiva es de su clan. Entonces, ¿qué te dijo?";
		link.l1 = "Chad Kapper mató a Alan Milrow, su amante, quien fue capturado por ti. Después de eso, difundió rumores sobre tu implicación en esto. Chad engañó a Mary y trató de usar su ansia de venganza.";
		link.l1.go = "mary_7";
		break;

	case "mary_7":
		dialog.text = "¡Maldita sea! ¿Mató a Alan? ¿Pero por qué? ¿Para dejarme la culpa?";
		link.l1 = "Para hacer que los Narvales sean hostiles hacia ti y ganar su confianza. El objetivo final de Kapper es eliminarte y tomar tu posición. Mary se ha negado a participar en su plan y a convertirse en su amante - por eso ordenó a los Narvales que la mataran.";
		link.l1.go = "mary_8";
		break;

	case "mary_8":
		dialog.text = "¿Te lo dijo ella?";
		link.l1 = "Sí. Y no parecía que estuviera mintiendo. Además, me dio una carta de Chad Kapper. Ya la he leído, así que deberías hacer lo mismo.";
		link.l1.go = "mary_9";
		break;

	case "mary_9":
		RemoveItems(pchar, "letter_chad_1", 1);
		dialog.text = "Hm. Sí, estos son los escritos de Chad. Estoy muy familiarizado con su escritura campesina (leyendo) ¡Argh! ¡Increíble! ¡Bastardo! ¡Traidor! Bueno, ¡voy a colgarlo de sus propias tripas! ¡Layton! ¡Reúne a cinco hombres! Pensándolo bien, Layton, espera, ¡despedido!\nLo haremos de manera inteligente. He estado planeando mejorar nuestras relaciones con los Rivados, esta es una oportunidad. Su hechicero Chimiset está siendo retenido en el Tártaro. Una prisión. Vamos a dejar que los Rivados liberen a su hombre ellos mismos y en el acto, matarán al traidor. \n¡Layton! Ve al Tártaro y ¡toma a todos nuestros guardias de su cubierta superior! " + pchar.name + ", también participarás en esto y estoy a punto de asignarte un papel muy importante. Encuentra al líder de los Rivados, Eddie el Negro, y negocia con él...";
		link.l1 = "¿Yo? Hm. ¡Pero no conozco a nadie aquí!";
		link.l1.go = "mary_10";
		break;

	case "mary_10":
		dialog.text = "Así que pronto conocerás a algunas personas; en realidad, conocerás al primer hombre de todo el clan Rivados. Eres el candidato más adecuado para llevar a cabo la parte diplomática de mi plan. Mis piratas no podrán atravesar fácilmente los territorios de Rivados; tampoco tengo hombres con buenas dotes oratorias.";
		link.l1 = "Bueno, está bien. Estoy en ello. ¿Qué debo hacer?";
		link.l1.go = "mary_11";
		break;

	case "mary_11":
		GiveItem2Character(pchar, "key_capper");
		Log_Info("Has recibido 50 doblones");
		PlaySound("interface\important_item.wav");
		TakeNItems(pchar, "gold_dublon", 50);
		dialog.text = "Toma esta llave. Abre cada puerta en 'Tártaro'. También, toma estos cincuenta doblones. Primero debes ir a 'Carolina', comprar una contraseña para acceder al territorio de Rivados. Habla con Fazio, él es nuestro mediador, una contraseña te costará cincuenta doblones. Luego debes ir al 'Protector'\nEs una residencia de Eddie el Negro. Dile que Chad Kapper está del lado de los Narvales, dejó de seguir mis órdenes y va a asesinar a Chimiset. Dale la llave, dile que lleve un buen número de sus luchadores y ataque 'Tártaro'\nMatamos dos pájaros de un tiro: los Rivados nos considerarán sus aliados y Kapper morirá a manos de los Negros. No puedo decir que envidio al hombre. ¿Entendido?";
		if (pchar.questTemp.LSC.Mary == "alive") // Мэри жива
		{
			link.l1 = "Entiendo - pero ¿dónde encontrar 'Protector' y 'Carolina'?";
			link.l1.go = "mary_12";
		}
		else
		{
			link.l1 = "Escucha, Steve, dime quiénes son esos Rivados y Narvales. Hablas de ellos todo el tiempo, pero todavía no tengo idea de quiénes son.";
			link.l1.go = "mary_12_1";
		}
		break;

	case "mary_12_1":
		dialog.text = "Narvales y Rivados son los clanes locales. Los clanes han estado viviendo aquí por mucho tiempo. Representan a los descendientes de los primeros colonos. Los Narvales son principalmente ingleses, holandeses y franceses, los Rivados son todos negros. Cada clan tiene un líder, poseen varios barcos y no dejan que otros entren en su territorio\nDebes conocer las contraseñas para visitarlos. Cambian las contraseñas cada semana.";
		link.l1 = "Ahora veo. Dime, ¿dónde encontrar 'Protector' y 'Carolina'?";
		link.l1.go = "mary_12";
		break;

	case "mary_12":
		dialog.text = "Fácil como un pastel. Sal de mi residencia, cruza un puente y gira a la izquierda. Esto será Carolina. Encontrar al Protector es un poco más complicado: después de cruzar un puente, gira a la derecha y ve a Santa Florentina por las tablas.\nEncuentra a los soldados de Rivados allí. Te pedirán una contraseña. Dila fuerte y claro. Luego entra en Fury y entra al Protector por la popa.";
		link.l1 = "Bueno, ya veo. Creo que no los extrañaré.";
		link.l1.go = "mary_13";
		break;

	case "mary_13":
		dialog.text = "Muy bien, entonces. ¡Ponte a ello, amigo!";
		link.l1 = "¡Nos vemos!";
		link.l1.go = "mary_14";
		break;

	case "mary_14":
		DialogExit();
		NextDiag.CurrentNode = "dodson_warwait";
		AddQuestRecord("SharkHunt", "32");
		sld = characterFromId("Eddy");
		sld.dialog.currentnode = "capper"; // ноду Эдди
		sld = characterFromId("Facio");
		sld.quest.parol = true;
		pchar.questTemp.LSC = "mary_go"; // меняем флаг
		break;

	case "dodson_warwait":
		dialog.text = "¿Todavía estás aquí? ¡Ve a Rivados ahora!";
		link.l1 = "¡Estoy en camino!";
		link.l1.go = "exit";
		NextDiag.TempNode = "dodson_warwait";
		break;

	case "mary_15":
		dialog.text = "Je, parece que Mary la Roja finalmente ha cabreado a alguien.";
		link.l1 = "Sí. Ella enfureció a Chad Kapper. Me uní a la pelea, pero, desafortunadamente, no pude salvar a la chica, uno de los atacantes la cortó con su sable.";
		link.l1.go = "mary_16";
		break;

	case "mary_16":
		dialog.text = "Lamento lo de ella, claro, pero fue su culpa sin duda. Mary siempre estaba buscando problemas. ¿Y qué hay de Chad Kapper? Este es mi contramaestre, de hecho.";
		link.l1 = "¿Tu contramaestre? Je-je... Aquí, lee esta carta. La encontré en el cuerpo de la chica. Verás ahora quién ordenó matarla y por qué. Kapper está planeando un atentado contra tu vida.";
		link.l1.go = "mary_9";
		break;

	// Каппер сбежал
	case "Chad_escape":
		dialog.text = "¿Dónde has estado tanto tiempo? Me han dicho que los Rivados liberaron a su hechicero...";
		link.l1 = "Fui retenido como rehén en el 'Protector' para asegurar su seguridad de una emboscada. Han liberado a Chimiset, sí, pero Chad logró escapar.";
		link.l1.go = "Chad_escape_1";
		break;

	case "Chad_escape_1":
		dialog.text = "¡Mierda! Nunca trates con los negros, dicen... ¡No pudieron hacer ni siquiera una tarea tan simple! ¡Malditos Rivados!";
		link.l1 = "Chad se ha escondido entre los Narvales...";
		link.l1.go = "Chad_escape_2";
		break;

	case "Chad_escape_2":
		dialog.text = "¡Claro que sí, lo ha hecho! No es un tonto y se dio cuenta de que los Rivados no podrían haber entrado en el Tártaro sin mi ayuda. Ahora se esconderá y atacará desde las sombras. ¡Layton! ¡Fortifica los puestos! ¡Mantén los ojos abiertos todo el tiempo! ¡Pagaré una fortuna al hombre que se encargue de Kapper!";
		link.l1 = "Está bien, Steven. Necesito pensarlo. Tal vez pueda rastrear a Chad. Nos vemos.";
		link.l1.go = "Chad_escape_3";
		NextDiag.TempNode = "Total_wait";
		break;

	case "Chad_escape_3":
		DialogExit();
		if (pchar.questTemp.LSC.Mary == "alive")
		{
			pchar.questTemp.Saga.SharkHunt = "mary_whiskey"; // к Мэри
			AddQuestRecord("SharkHunt", "34");
		}
		else
		{													   // не уберег Мэри - допетривай сам, куда идти
			pchar.questTemp.Saga.SharkHunt = "trader_whiskey"; // флаг на магазин - поиск виски
		}
		NextDiag.CurrentNode = "Total_wait";
		// добавим немного атмосферы - уберем Акселя до утра
		sld = characterFromId("Axel");
		LAi_SetStayType(sld);
		ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "goto", "goto5");
		sld = GetCharacter(NPC_GenerateCharacter("AxelHelper", "citiz_52", "man", "man", 35, PIRATE, 1, true, "quest"));
		FantomMakeCoolFighter(sld, 35, 100, 100, "blade_21", "pistol4", "bullet", 200);
		sld.dialog.Filename = "Quest\LSC\OtherNPC.c";
		sld.dialog.currentnode = "AxelHelper";
		LAi_SetOwnerType(sld);
		ChangeCharacterAddressGroup(sld, "EsmeraldaStoreBig", "barmen", "stay");
		LAi_group_MoveCharacter(sld, "LSC_NARVAL");
		SetFunctionTimerCondition("LSC_AxelReturnStore", 0, 0, 1, false); // таймер на возврат Акселя
		break;

	case "whiskey":
		dialog.text = "¿Qué sucedió, " + pchar.name + "¿Parece que te persigue el mismo Lucifer?";
		link.l1 = "¿Te han traído un barril de whisky?";
		link.l1.go = "whiskey_1";
		break;

	case "whiskey_1":
		dialog.text = "¿Qué barril?";
		link.l1 = "¿TE HAN TRAÍDO UN BARRIL DE WHISKY?!";
		link.l1.go = "whiskey_2";
		break;

	case "whiskey_2":
		dialog.text = "¿Por qué gritas así, camarada? No, no lo han hecho. ¿Cuál es el asunto?";
		link.l1 = "Gracias a Dios que he llegado a tiempo... Chad Kapper compró un barril de Bushmills de Axel Yost...";
		link.l1.go = "whiskey_3";
		break;

	case "whiskey_3":
		dialog.text = "¿Bushmills? ¡Este es mi favorito! ¡No lo he bebido en años!";
		link.l1 = "Sí-sí. Y Kapper lo sabe también. También le pidió a su compinche, Marcello Cíclope, que comprara un poco de arsénico a Sancho Carpintero. ¿Ves por qué?";
		link.l1.go = "whiskey_4";
		break;

	case "whiskey_4":
		dialog.text = "¿Crees que me va a envenenar?";
		link.l1 = "¡Sin duda! Por eso tenía tanta prisa. Si te traen un barril de whisky, no lo bebas. Está envenenado.";
		link.l1.go = "whiskey_5";
		break;

	case "whiskey_5":
		dialog.text = "¡Je, gracias por la advertencia! Seré cuidadoso. Espera, ¿a dónde vas ahora?";
		link.l1 = "Tengo que encontrar a Kapper y Cíclope. Tengo una idea de dónde encontrarlos. ¡Nos vemos!";
		link.l1.go = "whiskey_6";
		break;

	case "whiskey_6":
		DialogExit();
		pchar.questTemp.LSC.Dodson_warning = "true"; // Акула предупрежден
		LAi_CharacterDisableDialog(npchar);			 // запрещаем диалог
		AddQuestRecord("SharkHunt", "45");
		break;

	case "whiskey_7":
		dialog.text = "¡Ja! ¡Me alegra verte, amigo! Parece que te debo la vida.";
		link.l1 = "¿Han traído whisky?";
		link.l1.go = "whiskey_8";
		break;

	case "whiskey_8":
		dialog.text = "¡Los tienen! Bushmills, tal como dijiste. Nuestro querido Fazio fue tan amable... Lo he arrestado para investigar...";
		link.l1 = "¿Ha confesado?";
		link.l1.go = "whiskey_9";
		break;

	case "whiskey_9":
		dialog.text = "Sí. Dice que Kapper lo obligó a hacerlo. Estaba asustado y... me trajo el barril como un regalo de los Narvales.";
		link.l1 = "Kapper está muerto. Lo he eliminado a él y a sus amigos Narvales. Ahora solo queda un bastardo - Cíclope Marcello... Estoy seguro de que este cerdo gordo está al tanto de su paradero. ¡Déjame presionarlo un poco!";
		link.l1.go = "whiskey_10";
		break;

	case "whiskey_10":
		dialog.text = "Claro. Solo intenta no matarlo, nuestro pobre Fazio está en bastante mal estado de salud.";
		link.l1 = "Seré amable... muy amable, ¡maldita sea!";
		link.l1.go = "whiskey_11";
		break;

	case "whiskey_11":
		DialogExit();
		LAi_CharacterDisableDialog(npchar); // запрещаем диалог
		chrDisableReloadToLocation = true;	// закрыть локацию
		sld = CharacterFromID("Facio");
		LAi_CharacterEnableDialog(sld);
		break;

	case "poison":
		pchar.questTemp.LSC.Dodson_poison = "true"; // разговор состоялся
		dialog.text = "Argh... " + pchar.name + ", amigo, algo está muy mal conmigo...";
		link.l1 = "¡Steven! ¿Te bebiste el whisky? ¡Maldita sea, ¿realmente te lo bebiste?!";
		link.l1.go = "poison_1";
		break;

	case "poison_1":
		dialog.text = "Sí... Este es el mejor whiskey irlandés... Giuseppe Fazio me lo trajo hoy. Dijo que era un regalo del líder de los Narvales... un símbolo de paz... oh, eso duele... Parece que este es mi fin.";
		link.l1 = "¡Maldita sea! ¡El whisky estaba envenenado con arsénico! ¡Chad Kapper y Marcello Cyclops hicieron eso!";
		link.l1.go = "poison_2";
		break;

	case "poison_2":
		dialog.text = "Argh... el contramaestre finalmente me ha atrapado... ¡maldita sea!";
		if (CheckCharacterItem(pchar, "ultimate_potion"))
		{
			link.l1 = "¡No vas a morir! ¿Me oyes? ¡No morirás! Rápido, toma esta botella. Esta es la poción de curación más poderosa del mundo, cura todo. Bébela... ¡ahora!";
			link.l1.go = "poison_3";
		}
		else
		{
			link.l1 = "¡Steven!";
			link.l1.go = "dodson_poison";
		}
		break;

	case "dodson_poison": // Акула умирает
		DialogExit();
		LAi_SetImmortal(npchar, false);
		LAi_KillCharacter(npchar);
		SetFunctionTimerCondition("LSC_SetDexterAdmiral", 0, 0, 1, false); // через день Декстера в адмиралы
		if (CheckAttribute(pchar, "questTemp.LSC.CapperDie_Aeva"))
		{
			AddQuestRecord("SharkHunt", "41");
			sld = CharacterFromID("Facio");
			sld.dialog.currentnode = "whiskey";
			sld.greeting = "facio_2";
			sld.quest.poisonnode = 1;
		}
		else
			AddQuestRecord("SharkHunt", "42");
		pchar.questTemp.Saga.DodsonDie = "true"; // атрибут Саге что Акула погиб
		break;

	case "poison_3":
		RemoveItems(pchar, "ultimate_potion", 1);
		Log_Info("Has utilizado una poción comanche");
		Log_Info("¡El veneno se ha neutralizado!");
		PlaySound("interface\notebook.wav");
		dialog.text = "Oh... " + pchar.name + ", realmente ayudó. Todavía me siento un poco enfermo, pero el dolor casi ha desaparecido...";
		link.l1 = "Esta poción neutraliza incluso los venenos más letales. ¡Bébelo todo! Sí...";
		link.l1.go = "poison_4";
		break;

	case "poison_4":
		LAi_SetStayType(npchar);
		dialog.text = "Un milagro... Estoy bien ahora. Gracias, amigo, nunca lo olvidaré...";
		if (CheckAttribute(pchar, "questTemp.LSC.CapperDie_Aeva"))
		{
			link.l1 = "Será mejor que descanses ahora. Pareces un muerto. Ese bastardo de Kapper no podrá amenazarnos más - me he encargado de él y de unos cuantos Narvales también. Solo queda Marcello Cíclope. Dijiste que Fazio te trajo el whisky, ¿verdad?";
			link.l1.go = "poison_5";
		}
		else
		{
			link.l1 = "Será mejor que descanses ahora. Pareces un muerto. Dijiste que Fazio te trajo el whisky, ¿verdad?";
			link.l1.go = "poison_7";
		}
		break;

	case "poison_5":
		dialog.text = "Sí. Realmente debí haber prestado atención a su rostro pálido y manos temblorosas...";
		link.l1 = "Parece que se vio obligado a hacerlo. Está bien, voy a visitar a ese cerdo gordo y obtener la información de él. Estoy seguro de que sabe lo que necesito. ¡Que te mejores! ";
		link.l1.go = "poison_6";
		break;

	case "poison_6":
		DialogExit();
		sld = CharacterFromID("Facio");
		sld.dialog.currentnode = "whiskey";
		sld.greeting = "facio_2";
		sld.quest.poisonnode = 1;
		LAi_CharacterDisableDialog(npchar); // запрещаем диалог
		AddQuestRecord("SharkHunt", "40");
		break;

	case "poison_7":
		dialog.text = "Sí. Realmente debí haber prestado atención a su rostro pálido y manos temblorosas...";
		link.l1 = "Parece que se vio obligado a hacerlo. Bien, eventualmente atraparé a ese cerdo gordo, pero ahora tengo que lidiar con Kapper y Cíclope. Sé dónde se están escondiendo. ¡Recupérate!";
		link.l1.go = "poison_8";
		break;

	case "poison_8":
		DialogExit();
		LAi_CharacterDisableDialog(npchar); // запрещаем диалог
		AddQuestRecord("SharkHunt", "43");
		break;

	case "clear":
		dialog.text = "¿Qué dices, " + pchar.name + "? Ya sé que has tratado con Kapper en 'Eva'. ¡Y ni siquiera limpiaste allí, ja-ja! Para ser honesto, ¡me admira! Matar a Chad y a sus hombres, ¡eso sí que es algo! Sí, Jan tenía razón al alabarte.";
		link.l1 = "No solo he tratado con Kapper, sino que también he prevenido un intento contra tu vida. Iban a envenenarte, Steven, pero he detenido a esos bastardos.";
		link.l1.go = "clear_1";
		break;

	case "clear_1":
		dialog.text = "¿Envenenarme? ¿Pero cómo?";
		link.l1 = "Chad compró un barril de whisky Irish Bushmills de Axel...";
		link.l1.go = "clear_2";
		break;

	case "clear_2":
		dialog.text = "¿Bushmills? ¡Este es mi favorito! ¡No lo he bebido en años!";
		link.l1 = "Sí-sí. Y Kapper también lo sabe. También le pidió a su amigo, Marcello Cíclope, que comprara algo de arsénico a Sancho Carpintero. Luego él y sus compinches tomaron a Fazio y bajaron a la bodega de carga del 'Eva'. Iba a envenenar el whisky y forzar a Fazio a llevarlo a ti como un regalo de los Narvales.";
		link.l1.go = "clear_3";
		break;

	case "clear_3":
		dialog.text = "¡Ja! Por supuesto, habría bebido una pinta del whisky de inmediato...";
		if (CheckCharacterItem(pchar, "cask_whisky"))
		{
			link.l1 = "Chad contaba con eso. Pero falló, ni siquiera tuvo tiempo de ponerle arsénico. Sí, y me llevé el barril conmigo. Puedes tenerlo como regalo.";
			link.l1.go = "clear_4";
		}
		else
		{
			link.l1 = "Chad contaba con eso. Pero falló, ni siquiera tuvo tiempo de ponerle arsénico.";
			link.l1.go = "clear_7";
		}
		break;

	case "clear_4":
		RemoveItems(pchar, "cask_whisky", 1);
		PlaySound("interface\notebook.wav");
		dialog.text = "Muéstrame... " + pchar.name + ", ¡esto es un verdadero Bushmills! ¡El mejor whiskey irlandés! ¡Argh, he estado soñando con él durante años! ¡Tú, tú... maldita sea! ¡Has eliminado a Chad y has encontrado un whiskey tan encantador!\nTe daré uno de mis mejores talismanes. Este es el Martillo de Thor, es eterno. ¡A tu artillero le encantará!";
		link.l1 = "¡Gracias! Yo también estoy muy contento.";
		link.l1.go = "clear_5";
		break;

	case "clear_5":
		GiveItem2Character(pchar, "talisman3");
		PlaySound("interface\notebook.wav");
		Log_Info("Has recibido el amuleto 'Martillo de Thor'");
		dialog.text = "Estoy deseando beberme una pinta de este magnífico whisky... " + pchar.name + ", ¡tendremos una fiesta esta noche! Y ven a verme mañana. Mientras tanto, pensaré en tus palabras y en las acciones de Chad...";
		link.l1 = "Está bien, Steven, no te molestaré mientras te... relajas, ¡ja-ja!";
		link.l1.go = "clear_6";
		AddQuestRecord("SharkHunt", "53");
		break;

	case "clear_6":
		DialogExit();
		NextDiag.CurrentNode = "Total_wait";
		DeleteAttribute(pchar, "questTemp.LSC.Whiskey_clear");
		if (CheckAttribute(pchar, "questTemp.LSC.CyclopDie"))
		{
			SetFunctionTimerCondition("LSC_WhiskeyStoryFinal_1", 0, 0, 1, false); // адмирал зовет
			DeleteAttribute(pchar, "questTemp.LSC.CyclopDie");
		}
		break;

	case "clear_7":
		dialog.text = "Me has dicho algo muy importante. Pensaré en tus palabras y en las acciones de Chad... y luego te llamaré.";
		link.l1 = "Está bien, Steven. ¡Estaré esperando!";
		link.l1.go = "clear_6";
		AddQuestRecord("SharkHunt", "54");
		break;

	case "whyskey_final":
		dialog.text = "Ja, ahí estás, " + pchar.name + ". Ahora todos están aquí y podemos comenzar. Les he convocado a ti y a Layton para discutir la situación y decidir qué hacer con los Narvales.";
		link.l1 = "¿Qué quieres decir - qué hacer con los Narvales?";
		link.l1.go = "whyskey_final_1";
		break;

	case "whyskey_final_1":
		dialog.text = "Un intento contra mi vida fue organizado por Chad, quien tuvo el apoyo directo de los Narvales. Lo reconozco como un acto de agresión abierta. Considerando el hecho de que tenemos una alianza a corto plazo con los Rivados, ofrezco lo siguiente\nFormamos una alianza con los Rivados, preparamos una operación y eliminamos al clan Narval de una vez por todas. He tenido suficiente de su actitud de bandidos. Tú, " + pchar.name + ", van a desempeñar el papel de diplomático una vez más\nHabla con Black Eddie y Chimiset, convéncelos para que se unan a nosotros en la batalla contra nuestro enemigo común. Creo que te escucharán, te consideran su aliado\nDexter desarrollará un plan de ataque, él conoce todo sobre la geografía de la Isla. Layton, ¿tienes ya alguna idea?";
		link.l1 = "";
		link.l1.go = "whyskey_final_2";
		break;

	case "whyskey_final_2": // перекидываем ноду Декстеру
		DialogExit();
		sld = characterFromId("Dexter");
		sld.greeting = "";
		LAi_SetActorType(sld);
		LAi_ActorSetHuberMode(sld);
		LAi_CharacterEnableDialog(sld);
		LAi_ActorDialogNow(sld, pchar, "", -1);
		break;

	case "whyskey_final_3":
		dialog.text = "Una idea sabia. Obligados a retirarse al San Gabriel, los Narvales quizás no se rendirán ante nuestras tropas demasiado pronto, pero morirán rápidamente sin suministros de provisiones o se verán obligados a lanzar un ataque desesperado. ¿Qué dices, " + pchar.name + "?";
		link.l1 = "¿Qué pienso yo? Digo que declarar una guerra contra los Narvales es un paso políticamente incorrecto.";
		link.l1.go = "whyskey_final_4";
		break;

	case "whyskey_final_4":
		dialog.text = "¿Y dices eso después de haber matado a todos los hombres de Chad? ¡No olvides que todos ellos eran Narvales!";
		link.l1 = "No todos ellos. Uno de los primeros de esos bastardos, Marcello Cyclops, no era un Narval. En realidad, era leal a los Rivados y, tal vez, planeaba unirse a ellos. Al fin y al cabo, es un mulato. Creo que los Narvales no son responsables del intento contra tu vida - solo unos pocos bastardos, que fueron reclutados por Kapper.";
		link.l1.go = "whyskey_final_5";
		break;

	case "whyskey_final_5":
		dialog.text = "¿Y qué sugieres? ¿Ignorar todo esto?";
		link.l1 = "Te sugiero que me mantengas en mi papel de diplomático, pero esta vez negociaré con el líder de los Narvales, Donald. Además, déjame contarte mi punto de vista sobre el posible resultado de atacar a los Narvales.";
		link.l1.go = "whyskey_final_6";
		break;

	case "whyskey_final_6":
		dialog.text = "Continúa.";
		link.l1 = "Por lo que veo, la paz en la Isla es posible solo debido a la rivalidad entre dos clanes que son casi iguales en sus fuerzas. Tus vanguardias son la tercera potencia, y pueden ayudar a cualquiera de ellos a lograr la victoria. Pero tanto los Rivados como los Narvales son fuertes y una victoria le costará demasiado al ganador en cualquier caso.";
		link.l1.go = "whyskey_final_7";
		break;

	case "whyskey_final_7":
		dialog.text = "";
		link.l1 = "El precio por la destrucción de los Narvales será muchas vidas de tus hombres y de los de Rivados. Además, Layton dijo que el asedio de San Gabriel llevará mucho tiempo, y también podríamos enfrentar posible agresión de los Rivados en caso de que perdamos demasiados hombres...";
		link.l1.go = "whyskey_final_8";
		break;

	case "whyskey_final_8":
		dialog.text = "";
		link.l1 = "No olvides que ambos clanes están ansiosos por dominar en la Isla y no hace mucho eran tus enemigos. Así que, en mi opinión, la carnicería sería una verdadera plaga para los habitantes comunes.";
		link.l1.go = "whyskey_final_9";
		break;

	case "whyskey_final_9":
		dialog.text = "Hum. Tus palabras suenan sabias, pero aún no me has convencido.";
		link.l1 = "También necesito salir de la Isla de alguna manera, así que tengo que llegar a la estatua de Kukulcán en el fondo del mar. Los Rivados no pueden ayudarme, ¿quizás los Narvales sí? Luchar contra ellos tampoco me ayudará.";
		link.l1.go = "whyskey_final_10";
		break;

	case "whyskey_final_10":
		if (pchar.questTemp.LSC.Mary != "die")
			sTemp = "¡Ja! Y supongo que hay una razón más por la que no quieres convertir a los Narvales en nuestros enemigos. Esa chica pelirroja de Ceres Smithy, ¿verdad, amigo? ¿Estoy en lo cierto? No te preocupes por ella, " + pchar.name + ", Ya que te preocupas tanto por ella, la llevaremos a un lugar seguro antes de que empiece la lucha.\n";
		else
			sTemp = "";
		dialog.text = "" + sTemp + " Pero estoy de acuerdo si estás tan decidido. Ve y habla con Donald Greenspen, el jefe de los Narvales. Su residencia está en la parte trasera de la Esmeralda. Veamos qué nos dirá ese canalla.";
		link.l1 = "Bien. Estoy en camino.";
		link.l1.go = "whyskey_final_11";
		break;

	case "whyskey_final_11":
		DialogExit();
		sld = characterFromId("Grinspy");
		sld.dialog.currentnode = "negotiations"; // ноду Гринспи
		sld = characterFromId("Dexter");
		LAi_SetHuberType(sld);
		LAi_SetHuberType(npchar);
		NextDiag.CurrentNode = "negotiations_wait";
		pchar.questTemp.LSC.Donald_enter = "true";
		AddQuestRecord("SharkHunt", "55");
		break;

	case "negotiations_wait":
		dialog.text = "Ve a ver a Donald, amigo, ¡y haz que te lama las botas, ja-ja! Te estaré esperando.";
		link.l1 = "Estoy en camino.";
		link.l1.go = "exit";
		NextDiag.TempNode = "negotiations_wait";
		break;

	case "peace":
		dialog.text = "¿Y qué, has hablado con Donald? Veo que sí...";
		link.l1 = "Sí. No ordenó a sus hombres hacerte daño. Todos los Narvales que participaron en el intento fueron reclutados por Chad Kapper. Está muy molesto y nos asegura que los Narvales no tienen malas intenciones hacia ti. Está dispuesto a ofrecerte sus disculpas personales por este intento contra tu vida y por sospecharte del asesinato de Alan.";
		link.l1.go = "peace_1";
		break;

	case "peace_1":
		dialog.text = "¿Está listo para venir aquí y decir todas estas cosas?";
		link.l1 = "Juró sobre la Biblia.";
		link.l1.go = "peace_2";
		break;

	case "peace_2":
		dialog.text = "Je, tal vez, eso sirva. Parece que el único bastardo a quien culpar es mi ex contramaestre.";
		link.l1 = "Estoy completamente seguro de eso, Steven. No necesitamos esta guerra. Nadie la necesita.";
		link.l1.go = "peace_3";
		break;

	case "peace_3":
		dialog.text = "¡Está bien! Trato hecho. Estoy dispuesto a aceptar a Donald con sus disculpas, pero será mejor que se apresure. Ve y dile eso.";
		link.l1 = "Enseguida, Steven.";
		link.l1.go = "peace_4";
		break;

	case "peace_4":
		if (pchar.questTemp.LSC.Mary == "alive")
			sTemp = "Lleva allí a esa Mary y vivid juntos, hay mucho espacio libre.";
		else
			sTemp = "";
		dialog.text = "¡Espera! " + pchar.name + ", me alegra mucho que hayas aparecido aquí, en la Isla. Jan te tiene en muy alta estima, pero has superado todas las expectativas. Si estuvieras en mi tripulación... de hecho, te ofrezco la posición de Kapper, mientras estés aquí. Comandarás mi guarnición en 'Tartarus'. " + sTemp + ".";
		if (pchar.questTemp.LSC.Mary == "alive")
			link.l1 = "No, Steven, muchas gracias, pero no voy a quedarme aquí por mucho tiempo. Encuentra a alguien más para eso. Y en cuanto a Mary, estamos bien en 'Ceres Smithy'.";
		else
			link.l1 = "No, Steven, muchas gracias, pero no voy a quedarme aquí por mucho tiempo. Encuentra a alguien más para eso.";
		link.l1.go = "peace_5";
		break;

	case "peace_5":
		TakeNItems(pchar, "gold_dublon", 500);
		Log_Info("Has recibido 500 doblones");
		PlaySound("interface\important_item.wav");
		dialog.text = "Lo que sea, amigo. Así sea. Por favor, acepta este regalo de mi parte. Creo que encontrarás útiles estos quinientos doblones.";
		link.l1 = "¡Gracias!";
		link.l1.go = "LSC_navy";
		AddQuestRecord("SharkHunt", "57");
		pchar.questTemp.Saga.SharkHunt = "find"; // флаг - покушение предотвращено
		sld = characterFromId("Grinspy");
		sld.dialog.currentnode = "negotiations_17"; // ноду Дональду Гринспи
		AddSimpleRumourCityTip("Dicen que el almirante le respeta, señor...", "LostShipsCity", 15, 2, "LSC", "");
		AddSimpleRumourCityTip("Dicen que eres el amigo leal del almirante. ¿Es eso cierto?", "LostShipsCity", 15, 2, "LSC", "");
		break;

	case "LSC_navy":
		dialog.text = "Hablemos de nuestro negocio... Toma estas instrucciones de navegación. Úsalas para regresar aquí en un barco y en una sola pieza\nSin ellas, o fallarás en encontrar un pasaje aquí debido a los arrecifes y tormentas alrededor de la Isla, por lo que tu barco probablemente se unirá a sus hermanas aquí. Recuerda que debes usar una embarcación relativamente pequeña para pasar los arrecifes. Lugre, goleta, bergantín, fragata... Cuarta clase, no más grande\nTu objetivo es dejar este lugar con estas instrucciones de navegación en el bolsillo y luego regresar por mí en un barco. Una vez que regrese, me uniré a ti y a Svenson en tu juego. Aunque no tengo idea de cómo puedes dejar la isla. Solo tú puedes ayudarte en este asunto, y, quizás, ese Kukulcán tuyo...";
		link.l1 = "Es curioso, pero en realidad cuento con su ayuda. Gracias por las instrucciones de navegación, Steven. Todavía encontraré la manera de salir de esta isla.";
		link.l1.go = "LSC_navy_1";
		break;

	case "LSC_navy_1":
		GiveItem2Character(pchar, "LSC_navigation_map");
		dialog.text = "Entonces te deseo suerte. Date prisa si puedes, mis almacenes se están vaciando rápidamente, y pronto no habrá provisiones en absoluto. Sabes de lo que son capaces los hombres hambrientos y armados, ¿verdad?";
		link.l1 = "Lo hago. Ahora tengo que irme. ¡Hasta luego!";
		link.l1.go = "exit";
		NextDiag.TempNode = "Dodson_wait";
		AddQuestRecord("LSC", "5");
		// убираем квестовые предметы
		sld = ItemsFromID("key_capper");
		sld.price = 10;
		if (CheckCharacterItem(pchar, "letter_chad"))
			RemoveItems(pchar, "letter_chad", 1);
		break;

	case "Dodson_wait":
		dialog.text = "¿Has encontrado la salida de la isla, " + pchar.name + "?";
		link.l1 = "Aún no, Steven. Todavía estoy en ello.";
		link.l1.go = "exit";
		NextDiag.TempNode = "Dodson_wait";
		break;

	// --> информационный блок
	case "Total_wait":
		dialog.text = "Bueno, ¿qué tienes, " + pchar.name + "¿Tienes alguna noticia interesante?";

		if (!CheckAttribute(npchar, "quest.items") && CheckAttribute(npchar, "quest.takeitems"))
		{
			link.l1 = "Steven, me gustaría pedirte que me devuelvas mis pertenencias confiscadas.";
			link.l1.go = "Items";
		}
		if (!CheckAttribute(npchar, "quest.story"))
		{
			link.l2 = "Steven, cuéntame más sobre esta isla.";
			link.l2.go = "Story_island";
		}
		if (!CheckAttribute(npchar, "quest.natan"))
		{
			link.l3 = "¿Estás seguro de que Hawk no está en la isla? Pasó por el portal, así que debe estar aquí.";
			link.l3.go = "Natan";
		}
		if (!CheckAttribute(npchar, "quest.whiteboy"))
		{
			link.l4 = "¿Conoces a un hombre apodado Chico Blanco?";
			link.l4.go = "Whiteboy";
		}
		if (!CheckAttribute(npchar, "quest.ships"))
		{
			link.l5 = "¿Qué territorios aquí pertenecen a los Narvales y los Rivados?";
			link.l5.go = "ships";
		}
		if (!CheckAttribute(npchar, "quest.parol"))
		{
			link.l6 = "¿Cómo puedo aprender las contraseñas para abordar los barcos del clan?";
			link.l6.go = "parol";
		}
		if (!CheckAttribute(npchar, "quest.map"))
		{
			link.l7 = "Escucha, ¿hay algún mapa de la Isla?";
			link.l7.go = "map";
		}
		if (!CheckAttribute(npchar, "quest.blade"))
		{
			link.l8 = "Tienes un mandoble tan interesante. Nunca he visto nada parecido antes...";
			link.l8.go = "blade";
		}
		link.l9 = "Sin preguntas todavía. Pero puede que tenga algunas pronto...";
		link.l9.go = "exit";
		NextDiag.TempNode = "Total_wait";
		break;

	case "Items":
		dialog.text = "¡Ah, sí, claro! Lo había olvidado por completo... Tus cosas están arriba en el cofre. Puedes tomarlas. Layton no te detendrá.";
		link.l1 = "¡Gracias!";
		link.l1.go = "exit";
		npchar.quest.items = "true";
		NextDiag.TempNode = "Total_wait";
		ref location = &Locations[FindLocation(pchar.location)];
		DeleteAttribute(location, "private1.key");
		for (i = 1; i <= 10; i++) // можно лезть в сундук
		{
			sld = characterFromId("SharkSoldInside_" + i);
			DeleteAttribute(sld, "watchBoxes");
		}
		break;

	case "Story_island":
		dialog.text = "Esta Isla debe ser muy antigua. He visto viejas carabelas en el anillo exterior, son de más de cien años de antigüedad. Su existencia es posible gracias a las aguas poco profundas y a la fuerte corriente que trae aquí los restos de barcos. La gente ha estado viviendo aquí durante mucho tiempo. Hay quienes nacieron aquí y nunca se fueron.\nLos clanes se formaron justo después de que la expedición de de Betancourt terminara aquí. Por cierto, el San Agustín y el Tártaro eran parte de esa expedición. El Tártaro tenía muchos esclavos negros en sus bodegas. Fundaron el clan Rivados en honor a Pedro Rivados, su líder. Él había comenzado un levantamiento e intentado capturar el Tártaro, pero fracasaron. El hombre fue condenado a una muerte lenta.\nLos esclavos obtuvieron su libertad aquí e inmediatamente se opusieron al resto de los locales. Su solicitud de dominio y las tradiciones africanas hicieron que la mayoría de los cristianos se unieran, formando un clan Narval.\nEl clan Narval tenía muchos mercenarios, soldados, oficiales y aventureros en sus filas, estaban reuniendo suministros y construyendo un pequeño ejército profesional listo para luchar contra los Rivados con su ventaja en números. Desde entonces, los Narval se han vuelto muy selectivos al aceptar nuevos reclutas y los Rivados han limitado sus ambiciones. Puedes ver los resultados ahora.";
		link.l1 = "¿Había alguna conexión entre la Isla y el mundo exterior?";
		link.l1.go = "Story_island_1";
		break;

	case "Story_island_1":
		dialog.text = "No ha habido conexiones durante los últimos diez años. Los lugareños comerciaban con Cuba en un momento, intercambiando oro y bienes valiosos por comida. Pero ya no lo hacen.";
		link.l1 = "Hum. Entonces parece que Svenson y Black Pastor tenían razón... ¿Y por qué la gente no abandonó la Isla cuando aún tenía la oportunidad?";
		link.l1.go = "Story_island_2";
		break;

	case "Story_island_2":
		dialog.text = "Algunas personas lo hicieron, pero la mayoría decidió quedarse. Muchos han encontrado un hogar aquí, muchos otros nacieron aquí. No quieren regresar. Este lugar parece ser mucho mejor para ellos... Algunas personas tienen demasiado miedo de viajar a través de la zona de tormentas en barcos viejos. En cuanto a los Rivados, no tienen más remedio que quedarse aquí.";
		link.l1 = "¿Y por qué viniste aquí? Abandonaste tu excelente fragata, eligiendo un bergantín en su lugar...";
		link.l1.go = "Story_island_3";
		break;

	case "Story_island_3":
		dialog.text = "Me acusaron del asesinato de Blaze Sharp. No tengo ni idea de por qué. Obviamente, alguien está jugando sucio. El número de mis enemigos comenzó a crecer rápidamente, así que tuve que dejar Isla Tesoro y esperar aquí. He sabido de este lugar desde hace mucho tiempo. Dejé mi fragata, porque era demasiado grande para pasar los arrecifes locales\nFui atacado por los Narvales y los Rivados tan pronto como llegué aquí. No apreciaron mi llegada. Se acercaron a mi barco de noche en botes largos y le prendieron fuego. Aplastamos sus bañeras con nuestros cañones y mosquetes. Pero el fuego hizo su trabajo: mi bergantín se quemó\nNos enfurecimos como demonios, invadimos la Isla, asaltamos el San Agustín y les mostramos cómo luchan los corsarios. No pudieron soportar nuestra presión y pronto mostraron sus espaldas como cobardes. Capturamos San Agustín, resultó que esos idiotas la usaban como almacén de provisiones. Ahora tienen que comprármelas al precio que yo diga\nTambién capturamos a los líderes locales: el jefe de los Narvales, Alan Milrow, y al líder espiritual de los Rivados, Chimiset. Layton pasó los siguientes días explorando el área y atacamos el Tártaro, un punto débil en sus defensas\nAhora tenemos dos de estos barcos y los clanes tienen que acostumbrarse a nuestra presencia. Hoy en día, tenemos una especie de paz aquí. En cuanto a los otros lugareños, parece que les gusta la idea de una tercera fuerza.";
		link.l1 = "Ahora veo. ¡Gracias por la historia!";
		link.l1.go = "exit";
		npchar.quest.story = "true";
		NextDiag.TempNode = "Total_wait";
		break;

	case "Natan":
		dialog.text = "No puedo decirlo con certeza, pero no lo he visto aquí, de todas formas. Ni en las calles, ni en la taberna, ni en los barcos del clan. Eres el primer hombre que me dijo que Hawk debería estar por aquí. Pero, como ya he dicho, lo dudo.";
		link.l1 = "Veo...";
		link.l1.go = "exit";
		npchar.quest.natan = "true";
		NextDiag.TempNode = "Total_wait";
		break;

	case "Whiteboy":
		dialog.text = "¿Chico blanco? Hm... No, no he oído hablar de él antes. Pero eso no significa que no esté aquí. No tengo que conocer a toda la escoria, ¿estás de acuerdo?";
		link.l1 = "Yo sí. Bien, le preguntaré a alguien más.";
		link.l1.go = "exit";
		npchar.quest.whiteboy = "true";
		NextDiag.TempNode = "Total_wait";
		break;

	case "ships":
		dialog.text = "La Isla está dividida por Narvales, Rivados y mis hombres. También hay un área neutral. Yo controlo San Agustín y Tártaro\nRivados tienen Protector que es su residencia, Fury - cuarteles, Velasco - almacén. Se prohíbe el paso a extraños, debes decir una contraseña especial para poder llegar allí\nNarvales tienen muchos barcos en su posesión. Esmeralda es una residencia de su líder y una tienda. Así llamado 'Centro de ciencias San Gabriel' y una plataforma Fénix. Por último, pero no menos importante, Ceres Herrería - su taller. Cada barco excepto Esmeralda es un área restringida, debes decir una contraseña antes de que te dejen entrar\nEl resto de los barcos se consideran neutrales, los ciudadanos locales viven dentro de ellos. La taberna de Sancho está ubicada en la carabela Fleron y el hermano Julián es el jefe de la iglesia en el galeón Gloria.";
		link.l1 = "¡Gracias por la información!";
		link.l1.go = "exit";
		npchar.quest.ships = "true";
		NextDiag.TempNode = "Total_wait";
		AddQuestRecord("LSC", "2");
		break;

	case "parol":
		dialog.text = "En realidad, se los dan a las personas que les interesan. Ay, no eres uno de ellos. Pero eso no es un problema. Ve a una vieja fragata llamada Carolinea. Allí vive un perro gordo y astuto llamado Giuseppe Fazio. Es una especie de diplomático aquí. No sé qué hizo antes de llegar aquí, pero el hombre tiene habilidad. Hace negocios con todos. Los clanes lo usan como mediador. Codicioso. Listo para devorarse a sí mismo por un solo doblón, pero nunca lo muestra. Pídele la contraseña actual, aunque te costará.";
		link.l1 = "¡Gracias! Recordaré eso.";
		link.l1.go = "exit";
		npchar.quest.parol = "true";
		NextDiag.TempNode = "Total_wait";
		AddQuestRecord("LSC", "3");
		break;

	case "map":
		dialog.text = "Dexter tiene uno. Es mi segundo al mando. Hizo un mapa detallado justo después de nuestra llegada. Sube las escaleras y habla con él si lo necesitas.";
		link.l1 = "Entendido. ¡Gracias!";
		link.l1.go = "exit";
		npchar.quest.map = "true";
		NextDiag.TempNode = "Total_wait";
		sld = characterFromId("Dexter");
		sld.quest.map = "true";
		break;

	case "blade":
		dialog.text = "¡Ja! Una fina espada ancha. Una hoja única de algún tipo... Un trofeo de Alan Milrow, jefe del clan Narval. Así la nombré. Jurgen, un armero Narval, la hizo de un metal asombroso que encontraron en el fondo del mar\nNo se oxida, nunca se desafila y corta todo y a todos de una vez. Estoy muy complacido con esta arma y no pienso dejarla atrás.";
		link.l1 = "Tengo curiosidad, ¿si Jurgen puede hacer otro sable como este? Por buen dinero, por supuesto...";
		link.l1.go = "blade_1";
		break;

	case "blade_1":
		dialog.text = "Bueno, seguro que puede hacer otro. Pero no lo hará. Jurgen es Narval, es leal a su clan y nunca hará nada para forasteros. Además, necesitarás un hierro muy especial para hacer la segunda espada. Este hierro solo se encuentra en el fondo, ¿y cómo podría alguien llegar allí? Así que olvídalo.";
		link.l1 = "Ya veo. Lástima.";
		link.l1.go = "exit";
		npchar.quest.blade = "true";
		NextDiag.TempNode = "Total_wait";
		if (CheckAttribute(pchar, "questTemp.LSC.Mary") && pchar.questTemp.LSC.Mary == "alive")
		{
			sld = characterFromId("Schmidt");
			sld.quest.narval_blade = "begin"; // возможность сделать 'Нарвал' для Мэри
		}
		break;
		// <-- информационный блок

	case "return":
		chrDisableReloadToLocation = true; // закрыть локацию
		dialog.text = "Ja, vi tus velas en el horizonte, " + pchar.name + "¡Me alegra verte, amigo! ¿Cómo fue el viaje?";
		link.l1 = "Estuvo bien.";
		link.l1.go = "return_1";
		break;

	case "return_1":
		dialog.text = "Bien. Bueno, estoy listo para subir a tu barco y navegar hacia Jan Svenson. Layton se quedará aquí como almirante, ¡ya ha tomado el mando, ja-ja! Parece que no tiene intención de dejar la Isla, le gusta este lugar.";
		link.l1 = "Dijiste una vez que le va muy bien.";
		link.l1.go = "return_2";
		break;

	case "return_2":
		dialog.text = "Sí, ciertamente lo es. Bueno, estoy listo. ¿Vamos?";
		link.l1 = "Sube a mi barco, Steven. Zarparemos tan pronto como termine mis asuntos aquí.";
		link.l1.go = "return_3";
		break;

	case "return_3":
		dialog.text = "¡Trato hecho! Eh, ¡ha pasado demasiado tiempo desde que sentí la cubierta de un barco decente bajo mis pies!";
		link.l1 = "...";
		link.l1.go = "return_4";
		break;

	case "return_4":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "LSC_SetDodsonPassenger", -1);
		break;

	case "return_5":
		dialog.text = "Aquí estamos, amigo. Bueno, iré a ver a Svenson. También deberías verle y discutir nuestros planes futuros. ¡Ja, ja! Nos esperan días calurosos, ¿eh?";
		link.l1 = "Sin duda. ¡Nos vemos, Steven!";
		link.l1.go = "return_6";
		break;

	case "return_6":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "houseS1", "none", "", "", "OpenTheDoors", -1);
		sld = ItemsFromID("LSC_navigation_map");
		sld.price = 1000; // лоцию можно выкладывать 270912
		sld = ItemsFromID("keys_skel");
		sld.price = 3000;				   // отмычки можно выкладывать 270912
		pchar.questTemp.LSC.Dios = "true"; // можно отдать лоцию Диосу
		CloseQuestHeader("LSC");		   // 280313
		break;

	// Тени прошлого
	case "shadows":
		dialog.text = "¡Claro, haré lo que pueda! Adelante.";
		link.l1 = "Steve, mira... Un diente de tiburón. ¡No me digas que no te resulta familiar!";
		link.l1.go = "shadows_1";
		break;

	case "shadows_1":
		RemoveItems(pchar, "shark_teeth", 1);
		dialog.text = "¡Ja! ¡Eres listo! Sí, es mi diente. Bueno, es el diente de un tiburón que maté para impresionar a una belleza. Me llaman Shark desde entonces. Solo unos pocos pudieron hacerlo bajo el agua con un simple sable, pero yo era joven y tonto, y Beatrice Sharp era la chica más hermosa del Caribe... ¿Cómo lo conseguiste?";
		link.l1 = "El ex verdugo de San Juan me lo dio. Un hombre fue masacrado con ella. Su nombre era... Joshua Leadbeater.";
		link.l1.go = "shadows_2";
		break;

	case "shadows_2":
		dialog.text = "Sí, lo hice. Le corté la garganta con este diente. Me horrorizó la muerte de Beatrice y creí que Leadbeater era el único responsable que quedaba con vida. Leí papeles que encontré en él más tarde. Bueno, él tenía todo el derecho a la venganza\nLa hermana de Blaze estaba en el lugar equivocado en el momento equivocado. No se puede culpar a Mask por su muerte, no la quería, solo Butcher era su objetivo. Lamento haberlo asesinado. La verdad es que esa perra Jessica lo planeó todo.";
		link.l1 = "¿Has guardado esos papeles?";
		link.l1.go = "shadows_3";
		break;

	case "shadows_3":
		dialog.text = "¿Por qué debería hacerlo? Por supuesto que no lo he hecho. No los necesitaba. Pero puedo decirte por qué Máscara estuvo persiguiendoa Butcher, si tienes tiempo.";
		link.l1 = "He tenido. Sepa que no es simplemente curiosidad, realmente estoy interesado. Estoy incluso dispuesto a escribir su historia.";
		link.l1.go = "shadows_4";
		break;

	case "shadows_4":
		dialog.text = "Lo sé, nunca pierdes el tiempo. Escucha entonces. Joshua Leadbeater era un capitán ordinario de la Marina Británica y estaba al mando de la fragata 'Neptune', que más tarde se convirtió en una leyenda...";
		link.l1 = "...";
		link.l1.go = "shadows_5";
		break;

	case "shadows_5":
		DialogExit();
		SetLaunchFrameFormParam("Una hora más tarde...", "Saga_FinalLedbitterStory", 0, 4);
		LaunchFrameForm();
		WaitDate("", 0, 0, 0, 1, 10); // крутим время
		RecalculateJumpTable();
		break;

	case "shadows_6":
		AddQuestRecordInfo("Mask", "1");
		dialog.text = "... Sin embargo, Leadbeater sobrevivió y fue rescatado por un barco que pasaba. Sus heridas hicieron su rostro feo, y desde entonces había estado usando una máscara. Encontrar y castigar al culpable de todas sus desgracias se había convertido en el sentido de su vida.";
		link.l1 = "Ya veo... Lo tengo anotado. Creo que debería leerlo para ver qué tengo. Es una historia muy triste. ¿Has visto a esa Jessica?";
		link.l1.go = "shadows_7";
		break;

	case "shadows_7":
		dialog.text = "¡Seguro! Ella acompañóa Butcher en todos sus viajes hasta que él la dejó por Beatrice. Jess no pudo perdonarlo por eso. La llamaban el talismán de Butcher, porque siempre tenía suerte mientras ella estaba con él. \nCréelo o no, pero tan pronto como se deshizo de ella en Barbados, su negocio fue mal, el botín se volvió pobre y el 'Neptune' se convirtió en un huésped frecuente en el astillero de Isla Tesoro. Aunque se puede explicar por el hecho de que Butcher había estado pasando la mayor parte de su tiempo con Beatrice en la cabina en lugar de en la toldilla. \nBeatrice no era como Jessica, no era adicta a las aventuras y la guerra, aunque Nicolas le enseñó esgrima y navegación. Sí, le gustaba el romance del mar, pero no tenía suficiente dureza de carácter. El 'Neptune' de Butcher no era el lugar adecuado para ella. Al final, ella la mató.";
		link.l1 = "¿Y qué hay de Jessica?";
		link.l1.go = "shadows_8";
		break;

	case "shadows_8":
		dialog.text = "Oh, ella era algo. Cada marinero del 'Neptune' obedecía sus órdenes y no solo porque era la novia del capitán. Jess había dominado la esgrima y la navegación, los esfuerzos de Butcher no fueron en vano. Era dura e imprudente, y también tenía un buen aspecto\nMuchos hombres querían acostarse con ella, pero solo queríaa Butcher, molestarla era realmente arriesgado: muchos probaron los resultados en sus propias espaldas literalmente, y para los más persistentes sus lecciones de esgrima resultaron ser las últimas de sus vidas\nJess poseía una espada muy especial, la única de su tipo en el Caribe, no tengo ni idea de dónde la consiguió. Espada de hoja llameante. Nadie puede agarrar su hoja y hasta el más leve toque deja una herida terrible\nJess era aventurera no de nacimiento, sino por vocación. Por cierto, si necesitas saber más sobre ella, puedes hablar con un conocido tuyo. Él puede contarte mucho más de lo que yo puedo.";
		link.l1 = "¿De veras? ¿Y quién es ese hombre?";
		link.l1.go = "shadows_9";
		break;

	case "shadows_9":
		dialog.text = "Jan Svenson. Forest Devil nunca lo admitirá, pero tenía planes para Jessica. Fue la época en que ya se había apoderado de Tierra Firme occidental y su fama era algo envidiable, así que la tigresa era tan buena como él\nDespués de que Butcher se deshiciera de Jess, Jan comenzó a visitar Barbados sospechosamente a menudo, sacudiendo la guarnición inglesa. Como sabes, Jessica era hija de un plantador de Bridgetown\nEn fin, sus planes eran bien conocidos en círculos privados, pero nadie se atrevía a hablar de ello, Jan puede estar sentado en sus laureles en Blueweld hoy en día, pero en aquel entonces cualquier palabra equivocada en su dirección podía resultar mal\nAl final, no funcionó para ellos. Jess no pudo vivir con la forma en que Butcher la trató y se vengó un año después con la ayuda de la Máscara. Esta venganza terminó terriblemente para todos: para Butcher, para Beatrice, para la Máscara y para ella misma. Todos murieron.";
		link.l1 = "No todos ellos. El Butcher sigue vivo.";
		link.l1.go = "shadows_10";
		break;

	case "shadows_10":
		dialog.text = "¿Qué? ¿Te he oído mal? ¡¿Está vivo?!";
		link.l1 = "Sí. El Capitán Butcher no fue ejecutado. Bueno, debería haberlo sido, pero sobrevivió gracias a Jacob Jackman y Henry el Verdugo, quienes intimidaron al verdugo. La ejecución fue una farsa. Tengo pruebas.";
		link.l1.go = "shadows_11";
		break;

	case "shadows_11":
		dialog.text = "¡Imposible! ¿Y dónde está ahora?";
		link.l1 = "Es conocido como Lawrence Beltrope y vive en Port Royal. Sin embargo, sigue siendo peligroso. Jackman, quien causó tantos problemas entre los Hermanos de la Costa, había estado actuando bajo su mando.";
		link.l1.go = "shadows_12";
		break;

	case "shadows_12":
		dialog.text = "¡Maldita sea! ¡El contramaestre había encontrado a su capitán después de tanto tiempo! Dices Beltrope... ¡espera! Ahora entiendo por qué había un extraño registro de interrogatorio entre los papeles de Blaze... Parece que Blaze también había descubierto sobre Butcher-Beltrope...";
		link.l1 = "¿De qué estás hablando?";
		link.l1.go = "shadows_13";
		break;

	case "shadows_13":
		dialog.text = "Después de haberme instalado en esta residencia, revisé los papeles del viejo Blaze. He encontrado un registro de interrogatorio de un tal Samuel Brooks. Había mucho sobre las aventuras de Thomas Beltrope y que es conocido como un pirata y un amigo cercano de Nicolas Sharp. Parece que era el padre de Butcher.";
		link.l1 = "Interesante. Parece que los hijos de Sharp y Beltrope continuaron el oficio de sus padres...";
		link.l1.go = "shadows_14";
		break;

	case "shadows_14":
		dialog.text = "Parece que sí... Pero dime, amigo, ¿por qué estás tan interesado en las hazañas de los que ya no están? ¿Cuál es tu preocupación?";
		link.l1 = "Necesito documentos que confirmen que Helen McArthur es la hija de Beatrice Sharp y que tiene todos los derechos sobre este apellido. No me importa que ella también sea Beltrope.";
		link.l1.go = "shadows_15";
		break;

	case "shadows_15":
		dialog.text = "No hay nada sobre Helen McArthur ni en los papeles de Leadbeater ni en los archivos de Blaze. Es extraño que Beatrice no le haya contado a Blaze sobre el nacimiento de su sobrina. No parece propio de ella.";
		link.l1 = "Escucha, ¿quizás hay algo más en los documentos de Sharp? ¡Necesito cada detalle!";
		link.l1.go = "shadows_16";
		break;

	case "shadows_16":
		dialog.text = "Mm, supongo. Según las notas de Blaze, había estado tratando de encontrar la isla donde murió su hermana. Hay documentos sobre la expedición punitiva de Leadbeater. Nada interesante, excepto por algunos números de latitud. \nEste paralelo cruza el mar Caribe en su parte norte. Pero no hay indicio de longitud. Obviamente, las búsquedas de Blaze fracasaron, ni siquiera puedes imaginar cuántas islas pequeñas hay en esa latitud.";
		link.l1 = "¿Y qué es?";
		link.l1.go = "shadows_17";
		break;

	case "shadows_17":
		dialog.text = "Veamos... aquí: latitud 21 grados 32' Norte. No sé cómo puede ayudarte.";
		link.l1 = "Lo hará. Bien, Steven, muchas gracias por tu honesta historia. ¡Hasta luego!";
		link.l1.go = "shadows_18";
		break;

	case "shadows_18":
		DialogExit();
		pchar.questTemp.Saga.Shadows = "jessika";
		AddQuestRecord("Shadows", "6");
		LAi_SetHuberType(npchar);
		NextDiag.CurrentNode = "First time";
		sld = characterFromId("Svenson");
		sld.quest.jessika = "true";
		// рифы доступны для посещения
		i = FindIsland("RockIsland");
		Islands[i].visible = true;
		Islands[i].reload_enable = true;
		// для любителей самостоятельно добавлять локаторы
		LAi_LocationDisableOfficersGen("Shore67", true); // офицеров не пускать
		// и сразу прерывание
		pchar.quest.Saga_Jess_Island.win_condition.l1 = "location";
		pchar.quest.Saga_Jess_Island.win_condition.l1.location = "Shore67";
		pchar.quest.Saga_Jess_Island.function = "Saga_JessikaIsland";
		// активируем квест хронометра Алекса
		pchar.questTemp.AlexClock = "dodson"; // 280912
		break;

	// суп из черепахи
	case "terrapin":
		dialog.text = "Podrías decir eso. Ahora, sobre Tortuga\nLa isla se llamó así porque casi parece una tortuga. Levasseur había estado engrosando el caparazón de la tortuga durante doce años - el fuerte La Roche. Un ataque frontal es suicida, los cañones pesados del fuerte no dejarán ninguna oportunidad. Así que, cocinar una sopa de esta belleza no será fácil. Los españoles lo han intentado durante mucho tiempo y nunca lo lograron.";
		link.l1 = "Por eso fui a Svenson. ¿Cuál es tu plan? ¡Vamos, Steven!";
		link.l1.go = "terrapin_1";
		break;

	case "terrapin_1":
		dialog.text = "Mis hombres han hecho un trabajo decente en Tortuga durante las últimas semanas, y obtuvieron mucha información interesante. ¡Así que tengo buenas noticias para ti, camarada! Parece que no tienes que lidiar con los cañones de La Roche, ya que no somos los únicos hartos de Levasseur. Hay gente entre sus amigos que también quiere verlo muerto.";
		link.l1 = "Sigue...";
		link.l1.go = "terrapin_2";
		break;

	case "terrapin_2":
		dialog.text = "Se sabe que Levasseur es aficionado a las jóvenes colonas. Desaparecen después de que él termina de divertirse con ellas. El principal proveedor de esclavos de Tortuga se llama Robert Marten del galeón Voltigeur\nSu compañero, el sobrino de Levasseur, Henri Thibaut, elige a las chicas blancas más bonitas directamente en el puerto para su patrón. Así que, no hace mucho, Marten tuvo en sus manos a una chica muy hermosa de un bergantín inglés. Se llama Molly Jones. No la entregó a Levasseur, sino a su sobrino, por la noche, en alguna gruta secreta de Tortuga\nA la tripulación se le dijo que la chica murió de un ataque al corazón y que su 'cuerpo' fue arrojado por la borda. Parece que nuestros amigos decidieron quedarse con una cosa bonita para ellos mismos. Si Levasseur se entera de Molly, estos dos tendrán problemas.";
		link.l1 = "¿Y cómo podemos confiar en esa información? Es obvio que ambos entienden que están jugando con fuego...";
		link.l1.go = "terrapin_3";
		break;

	case "terrapin_3":
		dialog.text = "Verdad. Pero toda cadena tiene un punto débil. Y he encontrado uno para ti. Hace tres días, un ex marinero del 'Voltigeur' llamado Fernand Lucas bebió demasiado y contó muchas cosas interesantes en la taberna de Basse-Terre\nResulta que Molly Jones le había pedido que pidiera ayuda a su hermano en St John's. Pero Lucas nunca llegó a su destino, se escapó de su capitán y está sentado en su trasero en Guadalupe, ahogando su cobardía en ron\nAntigua no es un lugar seguro para los piratas franceses. ¡Recuerda eso! El Coronel Fox está listo para colgarlos en cada palma de la isla después de que su esposa muriera a manos de un corsario francés. Y sus temidos marines harán todo lo que su comandante ordene.";
		link.l1 = "No entiendo todavía cómo está relacionado con nuestro asunto... Hablemos de nuestros muchachos, Marten y Thibaut. ¿Cuál es el sentido de tal riesgo? ¿Era el encanto de la mujer tan fuerte o esos esclavistas mostraron misericordia?";
		link.l1.go = "terrapin_4";
		break;

	case "terrapin_4":
		dialog.text = "Conozco muy bien a ese canalla de Marten. Si está arriesgándose, eso significa que hay oro de por medio o miedo por su pellejo. No sé qué tiene que ver nuestro prisionero con esto.\nQuizás Robert espera obtener un gran rescate por ella, lo cual es poco probable, la chica parecía una sirvienta. ¡O tal vez...! ¡Ja! ¡Me pregunto quién podría ser más temible para Marten que Levasseur!";
		link.l1 = "¿Y por qué crees que la señorita Jones sigue oculta del gobernador? ¿Quizás ya obtuvieron lo que querían de ella y la entregaron a Levasseur? Sí, ¿tienes algo específico que contar sobre este Thibaut?";
		link.l1.go = "terrapin_5";
		break;

	case "terrapin_5":
		dialog.text = "No sé mucho sobre el hombre. Solo sé que el tío confía en este cachorro lo suficiente como para hacerlo su heredero. Todavía tiene a una chica, de lo contrario, ¿por qué necesitarían toda esta conspiración?\nNo está claro dónde se encuentra la chica y por qué Thibaut permite a Marten tomar la delantera. Hay un misterio que puede ayudarnos a ganar este juego sin asaltar Tortuga. Eres francés, así que supongo que preferirías hacerlo de esa manera.\n¡Pero deberías apresurarte, los delirios ebrios de Lucas podrían ser escuchados por los agentes de Marten y Levasseur, puedes imaginarte las consecuencias!";
		link.l1 = "Lo entiendo. Entonces, ¿Thibaut es un heredero de Levasseur? ¿Y esconde a una esclava de su tío? Maldición, ¡supongo que el joven está ansioso por ver a su tío muerto lo antes posible!";
		link.l1.go = "terrapin_6";
		break;

	case "terrapin_6":
		dialog.text = "Verdadero. Según las palabras de Lucas, esta Molly es una rara pieza de belleza, nuestro valiente Thibaut podría enamorarse de ella. Sabes lo que la gente puede hacer por amor. Ve a Basse-Terre\nEncuentra a este idiota borracho y hazlo hablar. Además, también deberías aprender algo sobre Molly y su hermano. Quizás quieras visitar Antigua primero; Molly envió a Lucas allí con un propósito. Pero, ¿cuál es el propósito?";
		link.l1 = "Ya veo. No perdamos tiempo. Gracias, Steven.";
		link.l1.go = "terrapin_7";
		break;

	case "terrapin_7":
		DialogExit();
		AddMapQuestMarkCity("SentJons", true);
		AddMapQuestMarkCity("BasTer", true);
		AddQuestRecord("Terrapin", "1");
		pchar.questTemp.Terrapin = "baster";
		pchar.questTemp.Terrapin.SJ_count = 0;
		// прячем Фокса
		sld = characterFromId("Fox");
		ChangeCharacterAddressGroup(sld, "none", "", "");
		// садим в таверну Робера Мартэна
		float fMft = MOD_SKILL_ENEMY_RATE / 10;
		sld = GetCharacter(NPC_GenerateCharacter("Rober", "Marten", "man", "man", 30, FRANCE, -1, true, "quest"));
		FantomMakeCoolSailor(sld, SHIP_GALEON_L, "Voltigeur", CANNON_TYPE_CANNON_LBS20, 90, 90, 90);
		FantomMakeCoolFighter(sld, 30, 80, 80, "blade_19", "pistol5", "bullet", 150);
		sld.name = "Rober";
		sld.lastname = "Marten";
		sld.dialog.FileName = "Quest\Sharlie\Terrapin.c";
		sld.dialog.currentnode = "Rober";
		sld.greeting = "pirat_common";
		TakeNItems(sld, "potion2", 1);
		TakeNItems(sld, "potion3", 2);
		SetCharacterPerk(sld, "Energaiser");
		SetCharacterPerk(sld, "BasicDefense");
		SetCharacterPerk(sld, "AdvancedDefense");
		SetCharacterPerk(sld, "CriticalHit");
		SetCharacterPerk(sld, "Tireless");
		SetCharacterPerk(sld, "HardHitter");
		SetCharacterPerk(sld, "Sliding");
		SetCharacterPerk(sld, "BladeDancer");
		SetCharacterPerk(sld, "SwordplayProfessional");
		SetCharacterPerk(sld, "Gunman");
		SetCharacterPerk(sld, "GunProfessional");
		SetCharacterPerk(sld, "MusketsShoot");
		SetCharacterPerk(sld, "LongRangeGrappling");
		SetCharacterPerk(sld, "GrapplingProfessional");
		SetCharacterPerk(sld, "HullDamageUp");
		SetCharacterPerk(sld, "SailsDamageUp");
		SetCharacterPerk(sld, "CrewDamageUp");
		SetCharacterPerk(sld, "CriticalShoot");
		SetCharacterPerk(sld, "LongRangeShoot");
		SetCharacterPerk(sld, "BasicBattleState");
		SetCharacterPerk(sld, "AdvancedBattleState");
		SetCharacterPerk(sld, "ShipDefenseProfessional");
		SetCharacterPerk(sld, "ShipSpeedUp");
		SetCharacterPerk(sld, "ShipTurnRateUp");
		SetCharacterPerk(sld, "WindCatcher");
		SetCharacterPerk(sld, "SailsMan");
		SetCharacterPerk(sld, "Doctor1");
		SetCharacterPerk(sld, "Doctor2");
		sld.MultiFighter = 1.0 + fMft; // мультифайтер
		LAi_SetSitType(sld);
		UpgradeShipParameter(sld, "SpeedRate"); // апгрейдить скорость
		UpgradeShipParameter(sld, "TurnRate");	// манёвренность
		FreeSitLocator("Baster_tavern", "sit1");
		ChangeCharacterAddressGroup(sld, "Baster_tavern", "sit", "sit1");
		if (bImCasual)
		{
			NewGameTip("Modo exploración: se duplica la duración de las misiones");
			SetFunctionTimerCondition("Terrapin_LateBaster", 0, 0, 20, false); // таймер
		}
		else
			SetFunctionTimerCondition("Terrapin_LateBaster", 0, 0, 10, false); // таймер

		// Квест "Погасшая Звезда" провалена, всё удаляем
		if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway"))
		{
			CloseQuestHeader("PZ");
			DeleteAttribute(pchar, "questTemp.PZ_Etap5_Start");
			DeleteAttribute(pchar, "questTemp.PZ_Etap4_Start");
			DeleteQuestCondition("PZ_Etap5_Start");
			DeleteQuestCondition("PZ_LongwayCapstervilleDialog");
			DeleteQuestCondition("PZ_OhotaNaZvezdu_Kapstervil");
			DeleteQuestCondition("PZ_OhotaNaZvezdu_Yamaika");
			DeleteQuestCondition("PZ_Beliz_PoterpKrushenie");
			pchar.questTemp.PZ_ProvalFinal = true;
		}
		break;

	case "terrapin_8":
		dialog.text = "¡Adelante!";
		link.l1 = "He encontrado al hermano de Molly en San Juan. Es el asistente de Fox. Pero hay algo extraño. Su hermana Molly es una bruja fea muy conocida, casi tan alta como tú. Es la criada de la hija de Fox, Catherine, y había estado en Inglaterra con ella hasta hace poco...";
		link.l1.go = "terrapin_9";
		break;

	case "terrapin_9":
		dialog.text = "";
		link.l1 = "En cuanto a Catherine, de hecho es conocida por su belleza y iba a visitar a su padre en su cumpleaños, pero se retrasó debido al retraso del escuadrón en Londres...";
		link.l1.go = "terrapin_10";
		break;

	case "terrapin_10":
		dialog.text = "";
		link.l1 = "Su padre, quien tomó con pesar la muerte de su esposa debido al ataque del corsario francés, le ha prohibido estrictamente que salga de Inglaterra en un barco solitario. Así que Molly Jones no puede ser prisionera de Thibaut. Entonces, ¿quién es ella?";
		link.l1.go = "terrapin_11";
		break;

	case "terrapin_11":
		dialog.text = "Mm... Maldita sea si lo sé. Quizás ella sea otra Molly Jones, no la que has estado preguntando. Aunque... hay demasiadas coincidencias. ¡No creo que todo sea solo un accidente! Tengo algunas sospechas poco claras, pero... aunque muchas cosas extrañas pueden suceder.";
		link.l1 = "¿Qué quieres decir? ¡Dímelo!";
		link.l1.go = "terrapin_12";
		break;

	case "terrapin_12":
		dialog.text = "¿Y qué si la hija desobedeció las órdenes de su padre y zarpó sin escolta? El mes pasado fue bastante tormentoso, el Albatros podría haberse dañado y convertirse en una presa fácil para Marten. Sospecho que Catherine no dijo su verdadero nombre, deberías entender por qué, y está siendo retenida en Tortuga bajo el nombre de Molly. \nSabes lo que le espera si su verdadero nombre se ve comprometido. ¡Esto empieza a tener sentido!";
		link.l1 = "¡Maldita sea! ¡Nunca lo hubiera pensado! Molly... Catherine... ¡Pero todo coincide!";
		link.l1.go = "terrapin_13";
		break;

	case "terrapin_13":
		dialog.text = "De eso estoy hablando, amigo. No estoy seguro de que tengamos razón, pero...";
		link.l1 = "¡Pero lo cambia todo! ¿Quizás deberíamos pedir apoyo a los ingleses? ¡Para que las bayonetas de los marines nos abran camino!";
		link.l1.go = "terrapin_14";
		break;

	case "terrapin_14":
		dialog.text = "Calma, " + pchar.name + "¡Necesitamos pruebas más sólidas! No podemos saberlo con certeza. La verdadera Catherine podría estar en Londres, esperando que zarpe un escuadrón. Los británicos tienen sus propios problemas, no se arriesgarán a atacar La Roche. Pero si nuestras sospechas son ciertas y el coronel Fox descubre lo que le ha pasado a su hija...\n Establecerá un bloqueo alrededor de la isla y esperará la llegada del escuadrón. Luego atacará la ciudad. Los zorros marinos son una fuerza temible en combates cuerpo a cuerpo. Estoy seguro de que izará la bandera inglesa sobre las ruinas de Tortuga en tres días. ¿Realmente quieres esto?";
		link.l1 = "No, no es nuestro modo. Ahora veo de qué rescate está hablando Marten.";
		link.l1.go = "terrapin_15";
		break;

	case "terrapin_15":
		dialog.text = "Debemos actuar con cuidado. Ni siquiera estamos seguros de que Marten esté al tanto de la verdadera identidad de la verdadera Molly. Chantajear al coronel Fox sería una idea suicida. Especialmente cuando el escuadrón de Cromwell está llegando en breve\nSi Catherine muere, nosotros también perderemos. A nuestra Hermandad no le interesa hacer enojar al coronel Fox más de lo habitual. Este hombre puede causar muchos problemas. Si Catherine tiene que morir después de todo, debemos asegurarnos de que no muera por nuestras manos y después de que ella juegue su papel en nuestro juego\nPero sería mucho mejor entregar a la pobre chica a su padre. Su salvador será recompensado. Si no en este mundo, entonces en el otro.";
		link.l1 = "¡Por la voluntad de Dios... Steven, eres un genio! ¡Voy a Tortuga de inmediato! ¡Descubriré quién es esa Molly Jones! ¡Estoy malditamente seguro de que ella es Catie Fox!";
		link.l1.go = "terrapin_16";
		break;

	case "terrapin_16":
		dialog.text = "Quizás... No pierdas tiempo, " + pchar.name + ". Y si estaba en lo cierto, asegúrate de que siga viva.";
		link.l1 = "Haré lo que pueda. ¡Nos vemos!";
		link.l1.go = "terrapin_17";
		break;

	case "terrapin_17":
		DialogExit();
		AddQuestRecord("Terrapin", "7");
		pchar.questTemp.Terrapin = "tortuga1";
		pchar.questTemp.Terrapin.Room_close = "true" : // не пускать в комнату таверны
													   break;

	case "guardoftruth":
		dialog.text = "¡Ho-Ho! ¡Escúpelo, amigo! ¡Resolveremos cualquier problema, maldita sea!";
		link.l1 = "Voy a ir directo al grano, entonces. ¿Conoces a Miguel Dichoso?";
		link.l1.go = "guardoftruth_1";
		break;

	case "guardoftruth_1":
		dialog.text = "Lo conozco. Ese don español me vendió un gran barco - una fragata. Eh, qué nave era, solo imagínate...";
		link.l1 = "Déjame adivinar, un casco único, velocidad máxima de dieciséis nudos? ¿'Santa Quiteria'?";
		link.l1.go = "guardoftruth_2";
		break;

	case "guardoftruth_2":
		dialog.text = "Tienes razón sobre su casco y velocidad, pero el nombre era diferente - 'San Martin'. Le pagué una enorme cantidad de oro, era todo lo que tenía. Todos mis ahorros fueron directamente a los bolsillos de ese bribón.";
		link.l1 = "¿Estás seguro de que su nombre era San Martín y no Santa Quiteria? ¿Y cuándo lo compraste? ¿Y por qué lo llamas un bribón?";
		link.l1.go = "guardoftruth_3";
		break;

	case "guardoftruth_3":
		dialog.text = "¡Tantas preguntas! Las responderé todas en orden: Estoy seguro de que fue San Martín. Personalmente ayudé a los trabajadores de Alexus a deshacerse de una tabla con ese nombre papista de la popa. La llamé 'Fortuna' - un nombre mucho más adecuado para tal princesa.\nLa compré poco antes de que Blaze Sharp fuera asesinado en el invierno de 1654. ¿Por qué llamé así a Miguel? Porque ese hijo de perra logró robar el barco de la base militar española de Providence. Les organizamos todo un espectáculo, justo frente al fuerte de San Juan. Sacrifiqué dos balandros medio muertos para hacer la pelea más creíble. Quemamos e inundamos los barcos, simulando la batalla con la fragata. Y cuando descendió la oscuridad, llevamos el San Martín a Isla Tesoro.. Yo obtuve el barco y Dichoso obtuvo el dinero. Le dijo a su alto mando que la fragata se hundió en una batalla con piratas, el comandante de San Juan lo verificó.";
		link.l1 = "¡Así es como los hidalgos españoles llenan sus bolsillos! ¡Qué sinvergüenza! Dime, ¿realmente sucedió en el invierno de 1654? ¿Quizás en primavera? ¿Y fue la fragata dañada por tormentas?";
		link.l1.go = "guardoftruth_4";
		break;

	case "guardoftruth_4":
		dialog.text = "En invierno... Maldita sea, no estoy totalmente seguro - podría ser en primavera, también. Realmente no lo recuerdo. La fragata no estaba dañada, era completamente nueva. Parecía recién construida. Cuando pienso en ella, solo quiero llorar de rabia...";
		link.l1 = "¿Por qué? Sí, ¿y dónde está ahora tu hermoso bergantín?";
		link.l1.go = "guardoftruth_5";
		break;

	case "guardoftruth_5":
		dialog.text = "Porque ella se ha ido de mí. Me tendieron una trampa, pusieron mi talismán en el cadáver de Blaze y difundieron la palabra de que yo era el asesino. Luego escuché que Marcus Tyrex - nuestro guardián del código - iba a darme una marca negra. Así que decidí escapar de ese lío por un tiempo en la Isla Justicia, donde me encontraste. No pude llegar allí en una fragata, así que la comprometí con Black Pastor a cambio de un bergantín lleno de provisiones, no tenía mucho dinero después de mi trato con ese astuto Dichoso. Esperaba vender provisiones y regresar a Isla Tesoro en un mes o dos... Bueno, ya sabes el resto.";
		link.l1 = "Y Black Pastor no te esperó, así que la vendió";
		link.l1.go = "guardoftruth_6";
		break;

	case "guardoftruth_6":
		dialog.text = "Precisamente. Fue comprada por un inglés, o para ser más específicos, por un escocés, William Paterson. Podría intentar devolver a la chica, claro, pero este montañés es un pájaro serio, un capitán de la Royal Navy, buen amigo del coronel Fox. Además, hacía negocios con Jackman de la misma manera que tú con Svenson\nEl escocés tiene un escuadrón... al diablo, no volveré a ver mi barco.";
		link.l1 = "Ya veo. ¿No sabes dónde está ese Dichoso ahora?";
		link.l1.go = "guardoftruth_7";
		break;

	case "guardoftruth_7":
		dialog.text = "No tengo idea. Nunca lo he visto después de que compré mi Fortuna.";
		link.l1 = "¿Y por qué no le ofreció Miguel comprarlo a alguien más? ¿Qué tal Tyrex, Barbazon, Sharp? ¿O Paterson?";
		link.l1.go = "guardoftruth_8";
		break;

	case "guardoftruth_8":
		dialog.text = "No tengo ni idea. Paterson no estaba aquí esa vez, hasta donde recuerdo. Zachariah, Jacques y Marcus nunca habrían estado de acuerdo y yo... ¡Realmente me gustaba la fragata!";
		link.l1 = "Entiendo que... no entiendo nada. Rompecabezas por todas partes...";
		link.l1.go = "guardoftruth_9";
		break;

	case "guardoftruth_9":
		dialog.text = "¿Explorando el pasado otra vez? ¿Qué isla quieres tomar esta vez? ¡Ja-ja-ja!";
		link.l1 = "Hay una isla... Aunque todavía no puedo encontrar un camino hacia ella. ¡Bien, Steven, gracias por tu información! ¡Adiós!";
		link.l1.go = "guardoftruth_10";
		break;

	case "guardoftruth_10":
		dialog.text = "Buena suerte, " + pchar.name + ".";
		link.l1 = "... ";
		link.l1.go = "guardoftruth_11";
		break;

	case "guardoftruth_11":
		DialogExit();
		AddQuestRecord("Guardoftruth", "60");
		pchar.questTemp.Guardoftruth.Archy = "guadeloupe";
		// маленькая развлекуха
		pchar.quest.GuardOT_cabinattack.win_condition.l1 = "EnterToSea";
		pchar.quest.GuardOT_cabinattack.function = "GuardOT_PrepareCreateBandosInCabin";
		break;

	case "tieyasal":
		dialog.text = "Y me alegra ayudarte, como siempre. ¿Qué deseas esta vez, " + pchar.name + "?";
		link.l1 = "Es otra vez sobre tu viejo amigo Miguel Dichoso. Sé que lo vieron de nuevo en Isla Tesoro. ¿No puedes ayudarme a encontrarlo?";
		link.l1.go = "tieyasal_1";
		break;

	case "tieyasal_1":
		dialog.text = "¡Oh, amigo, no lo sabía, de hecho. No lo he visto aquí. No lo he visto desde que le compré la 'Fortuna'. ¿Y por qué necesitas a ese don español?";
		link.l1 = "Lo necesito. Miguel conoce el camino a una antigua ciudad india. Estoy realmente ansioso por llegar allí.";
		link.l1.go = "tieyasal_2";
		break;

	case "tieyasal_2":
		dialog.text = "Como siempre, amigo mío, te vas a meter en un lío. Ay, no puedo ayudarte. Te aconsejo que des una vuelta por el asentamiento y preguntes a la gente, quizás alguien lo haya visto. Es un hombre famoso aquí, ¿sabes?";
		link.l1 = "Hola, Steven, ¿puedes al menos decirme cómo se ve?";
		link.l1.go = "tieyasal_3";
		break;

	case "tieyasal_3":
		dialog.text = "Bueno, tiene entre veinticinco y veintiocho años, es más o menos de tu altura, ojos oscuros, sin peluca. Hay una cicatriz de sable en su mejilla derecha.";
		link.l1 = "Hum. Sabes, hay muchas personas que encajarían con esa descripción.";
		link.l1.go = "tieyasal_4";
		break;

	case "tieyasal_4":
		dialog.text = "No hay otros detalles únicos sobre él. Es seguro de sí mismo, insolente y muy peligroso. Había rumores sobre él...";
		link.l1 = "Ya veo. Bien, preguntaré sobre él. ¡Buena suerte, Steven!";
		link.l1.go = "tieyasal_5";
		break;

	case "tieyasal_5":
		DialogExit();
		AddQuestRecord("Tieyasal", "2");
		npchar.quest.tieyasal = "true";
		break;

	// Jason НСО
	case "patria":
		dialog.text = "¡Jo-jo! ¡Has venido al lugar correcto! ¡Suéltalo!";
		link.l1 = "Hay un tipo que no teme a los piratas. No los toma en serio. Necesita aprender una lección de respeto. Recuerda, no lo mates.";
		link.l1.go = "patria_1";
		break;

	case "patria_1":
		dialog.text = "¡Vaya! ¡No es otro que el viejo Charles! ¡Apuesto a que te has metido en algún lío otra vez! Vamos a los detalles, ¿quién es el objetivo esta vez y qué le enseñaremos?";
		link.l1 = "Un visitante de Europa, un inspector del Ministerio de Finanzas de Francia - barón Noel Forget. Quiere establecer una Compañía Comercial Francesa aquí, pero yo y un amigo cercano estamos en contra. Intentamos convencer al Barón de que comerciar aquí sería muy arriesgado debido a los holandeses, ingleses y especialmente los piratas después de que Levasseur fue derrotado, pero no escuchó. Necesitamos infundirle miedo, para que lo sienta en su propia piel.";
		link.l1.go = "patria_2";
		break;

	case "patria_2":
		dialog.text = "Sí-sí... ¡Un verdadero barón!.. ¿Asaltaremos su barco?";
		link.l1 = "Este es el plan: su nave partirá hacia Capsterville desde Puerto Príncipe pronto. Debes interceptar al Barón después de su partida y tomarlo como rehén. Sería mejor si no hundieras el barco y evitaras matar a la tripulación. Al fin y al cabo, los franceses son nuestros amigos. ¿Podrás manejar eso?";
		link.l1.go = "patria_3";
		break;

	case "patria_3":
		dialog.text = "Bueno, no puedo prometer nada. Pero lo intentaré. ¿Qué barco es?";
		link.l1 = "Una fragata llamada 'Favory'.";
		link.l1.go = "patria_4";
		break;

	case "patria_4":
		dialog.text = "Un bergantín no es rival para mi fragata. Nos ocuparemos de ellos fácilmente. Si se rinde, dejaré que todos vivan.";
		link.l1 = "Perfecto. Infunde miedo y ofréceles rendirse. Después, envía al Barón al almacén infestado de ratas. Trata de encontrar el lugar más sucio que puedas, pero no lo mantengas allí por más de un día, o podría enfermarse y morir. Luego acomódalo en la cabina, ve a la Isla Tesoro y enciérralo en algún lugar apartado. Viste a algunos de tus hombres como mercaderes franceses capturados y haz que actúen como tales. Durante tres días seguidos, deben contarle todo sobre cómo los despiadados piratas los persiguen, los roban, les exigen rescates, los torturan... con todos los detalles requeridos.";
		link.l1.go = "patria_5";
		break;

	case "patria_5":
		dialog.text = "¡Ja-ja-ja! ¡Este debe ser el trabajo más divertido que he aceptado desde hace mucho tiempo! Bueno, entonces, encontraré a esos actores, amigo. No lo dudes, después de sus historias tu barón se cagará en los pantalones. ¡Le mostrarán cicatrices de sables y baquetas calientes... ";
		link.l1 = "Lo has clavado. Entonces le obligarás a escribir una carta a Poincy, pidiendo un rescate. Treinta y cinco mil por un pez gordo como él no es tanto.";
		link.l1.go = "patria_6";
		break;

	case "patria_6":
		dialog.text = "Bien. ¿Qué haremos ahora?";
		link.l1 = "Y luego llevarás al Barón a los Turcos. Allí tomarás el rescate, y me entregarás al Barón. Y además, deberías mencionar que todos los franceses responderán por Tortuga y Levasseur.";
		link.l1.go = "patria_7";
		break;

	case "patria_7":
		dialog.text = "¡Ja-ja-ja! ¡Eso sí que es un truco del diablo! Nosotros personalmente, bueno, ya sabes lo que le hicimos a Levasseur, y ahora... ¡ja-ja-ja!.. Está bien, camarada. ¡Se hará! ¿Dices que el barco llegará pronto?";
		link.l1 = "Pronto. Necesitamos estar atentos.";
		link.l1.go = "patria_8";
		break;

	case "patria_8":
		dialog.text = "No te preocupes, no te defraudaré. Me encargaré personalmente. Cuando escuches el rumor de que este barón fue capturado, ven a mí.";
		link.l1 = "Bien. Mis agradecimientos, Steven.";
		link.l1.go = "patria_9";
		break;

	case "patria_9":
		DialogExit();
		AddQuestRecord("Patria", "70");
		pchar.questTemp.Patria = "epizode_12_wait";
		pchar.questTemp.Patria.Condotier.Success = "true";
		LocatorReloadEnterDisable("Pirates_town", "reload3_back", true);
		break;

	case "patria_10":
		dialog.text = "Por supuesto, camarada. Como acordado. Historias espeluznantes sobre piratas malvados, masacrando inocentes comerciantes franceses, los sonidos de un látigo, gemidos y gritos. Brasero con carbón y esposas chamuscadas. Tal como debe ser.";
		link.l1 = "¡Vaya! Aguanta tus caballos. Lo necesito vivo.";
		link.l1.go = "patria_11";
		break;

	case "patria_11":
		dialog.text = "No te preocupes, él seguirá con vida. Escribió esa carta con mano temblorosa. Aquí está.";
		link.l1 = "¿Qué está escrito allí? ¿Está rogándole a Poincy que lo saque de aquí?";
		link.l1.go = "patria_12";
		break;

	case "patria_12":
		dialog.text = "¡Exactamente, camarada! ¡Está suplicando!";
		link.l1 = "Tira esta carta, o mejor - quémala. Nos encontraremos en los Turcos en una semana. Debe parecer que necesitamos tiempo para reunir el rescate.";
		link.l1.go = "patria_13";
		break;

	case "patria_13":
		dialog.text = "Entendido. En una semana, en el golfo del Norte. No olvides llevar el dinero: esto debe lucir bonito. Después, ven a mí, lo solucionaremos.";
		link.l1 = "Por supuesto, apuesto a que incluso el erizo lo habría descubierto. ¡Nos vemos más tarde! ";
		link.l1.go = "patria_14";
		break;

	case "patria_14":
		DialogExit();
		AddQuestRecord("Patria", "73");
		pchar.questTemp.Patria = "epizode_12_terks";
		SetFunctionTimerCondition("Patria_CondotierTerks", 0, 0, 7, false);
		SetFunctionTimerCondition("Patria_CondotierTerksOver", 0, 0, 14, false);
		if (bImCasual)
			NewGameTip("Modo exploración: el temporizador no está desactivado. ¡Cumple el plazo!");
		break;

	case "patria_15":
		pchar.quest.Patria_CondotierTerksOver.over = "yes"; // снять таймер
		dialog.text = "¡Oye, comedor de ranas! ¡Detente!";
		link.l1 = "No me muevo.";
		link.l1.go = "patria_16";
		break;

	case "patria_16":
		dialog.text = "Aquí tienes a tu barón. Un poco desgastado, pero entero. ¿Es él?";
		link.l1 = "Sí.";
		link.l1.go = "patria_17";
		break;

	case "patria_17":
		dialog.text = "Perfecto. Ahora, ¡entrega el dinero o él está acabado! Y no intentes engañarnos, ¡te tenemos en la mira!";
		if (sti(pchar.money) >= 350000)
		{
			link.l1 = "Aquí.";
			link.l1.go = "patria_18";
		}
		else
		{
			link.l1 = "¡Maldita sea! Lo olvidé en el barco...";
			link.l1.go = "patria_22";
		}
		break;

	case "patria_18":
		AddMoneyToCharacter(pchar, -350000);
		dialog.text = "¡Ja-ja-ja! Eres un chico listo, franchute. Toma tu santidad. Y dile a Poincy que debe preparar el dinero: todos los bastardos franceses tendrán que pagar por lo que le hicisteis a Levasseur y Tortuga. Y vuestros comerciantes nos pagarán con sus bienes y barcos. ¡Ja-ja-ja! No olvidéis traernos más barones al archipiélago, nos traen mucho beneficio. ¡Ja-ja-ja!";
		link.l1 = "Por favor, ve a mi barco, Barón.";
		link.l1.go = "patria_19";
		break;

	case "patria_19":
		sld = CharacterFromID("Noel");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload1_back", "none", "", "", "", 10.0);
		dialog.text = "Y ni pienses en perseguirnos, capitán. Sabes quién soy. Tengo más comedores de ranas cautivos, y si no regreso a casa a tiempo, todos serán asesinados por mis hombres. ¿Entendido?";
		link.l1 = "¡Llegará el momento y nos ocuparemos de ustedes, malditos blasfemos!";
		link.l1.go = "patria_20";
		break;

	case "patria_20":
		dialog.text = "¡Ja-ja-ja-ja!";
		link.l1 = "...";
		link.l1.go = "patria_21";
		break;

	case "patria_21":
		DialogExit();
		LAi_SetPlayerType(pchar);
		AddQuestRecord("Patria", "74");
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
		sld = CharacterFromID("Terks_pirat");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
		pchar.questTemp.Patria = "epizode_12_baronalive";
		pchar.questTemp.Patria.DodsonAgain = "true";
		Island_SetReloadEnableGlobal("Bermudes", false); // закрыть остров до отвоза барона
		sld = CharacterFromID("Noel");
		AddPassenger(pchar, sld, false); // добавить пассажира
		SetCharacterRemovable(sld, false);
		pchar.quest.Patria_Condotier_toPuancie.win_condition.l1 = "location";
		pchar.quest.Patria_Condotier_toPuancie.win_condition.l1.location = "Charles_town";
		pchar.quest.Patria_Condotier_toPuancie.function = "Patria_CondotierEnCapstervil";
		// Теркс в норму
		LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
		LAi_LocationDisableOfficersGen("Shore56", false);
		break;

	case "patria_22":
		dialog.text = "¿Te estás burlando de mí?";
		link.l1 = "Un minuto, lo traeré...";
		link.l1.go = "patria_23";
		break;

	case "patria_23":
		DialogExit();
		LAi_SetPlayerType(pchar);
		sld = CharacterFromID("Terks_pirat");
		LAi_SetActorType(sld);
		LAi_ActorAnimation(sld, "Shot", "Patria_CondotierBaronDie", 1.0);
		break;

	case "patria_24":
		dialog.text = "";
		link.l1 = "¡Argh, Steven, qué ha hecho tu necio!";
		link.l1.go = "patria_25";
		break;

	case "patria_25":
		dialog.text = "Charles, ¿qué estabas haciendo? ¿Dónde está el dinero? No le dije a mis chicos que esto no era real... y entonces este idiota decidió que querías engañarlos...";
		link.l1 = "¡Qué lástima! El Barón está muerto... ¿Qué hará Poincy ahora?";
		link.l1.go = "patria_26";
		break;

	case "patria_26":
		dialog.text = "Bueno, amigo, es tu culpa, espero que lo entiendas. Tal vez, eso sea mejor para ti.";
		link.l1 = "¡Qué idiota soy! Arruiné todo. Bien, iré a Poincy... Perdóname por ser un tonto, Steven, nos vemos.";
		link.l1.go = "patria_27";
		break;

	case "patria_27":
		dialog.text = "Necesitas descansar, estás perdiendo tu toque. Ven a verme alguna vez, te conseguiré algo de ron y hermosas doncellas.";
		link.l1 = "Gracias, te haré una visita cuando pueda.";
		link.l1.go = "patria_28";
		break;

	case "patria_28":
		DialogExit();
		AddQuestRecord("Patria", "75");
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Patria_CondotierDodsonNorm", 10.0);
		sld = CharacterFromID("Terks_pirat");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 8.0);
		pchar.questTemp.Patria = "epizode_12_barondie";
		// Теркс в норму
		LAi_LocationFightDisable(&Locations[FindLocation("Shore56")], false);
		LAi_LocationDisableOfficersGen("Shore56", false);
		break;

	case "patria_29":
		dialog.text = "De nada, amigo. ¡Para mí esto ha sido lo más divertido que he tenido este año! Nos reímos tanto, yo y mis muchachos... ¡Así que me gustaría agradecerte por esto. Aquí tienes tu dinero.";
		link.l1 = "Deberías quedarte con una parte.";
		link.l1.go = "patria_30";
		break;

	case "patria_30":
		AddMoneyToCharacter(pchar, 350000);
		dialog.text = "Olvídalo. Hice esto por nuestra amistad. La Hermandad de la Costa te debe mucho más, sin embargo, no pediste ni un solo doblón.";
		link.l1 = "Aun así, toma al menos cincuenta mil por los servicios y la compensación. ¡Gracias, Steven! Me alegra que una vez te conocí en esa extraña Isla Justicia de los barcos perdidos.";
		link.l1.go = "patria_31";
		break;

	case "patria_31":
		AddMoneyToCharacter(pchar, -50000);
		dialog.text = "¡Y yo también! ¡Charles, visítame cuando tengas algo de tiempo!";
		link.l1 = "¡Con gusto!";
		link.l1.go = "patria_32";
		break;

	case "patria_32":
		DialogExit();
		DeleteAttribute(pchar, "questTemp.Patria.DodsonAgain");
		break;

	case "patria_33":
		dialog.text = "¡Llegas con una semana de retraso! No le dije a mis muchachos que esto no era real... ¡Se negaron a esperar más y decidieron acabar con tu barón!";
		link.l1 = "¡Qué idiota soy! ¡Lo arruiné todo! ¿Qué le voy a decir a Poincy?";
		link.l1.go = "patria_34";
		break;

	case "patria_34":
		dialog.text = "Bueno, camarada, es tu culpa, espero que lo entiendas. Quizás, sea lo mejor para ti.";
		link.l1 = "Está bien, iré a Poincy... Perdóname por ser un tonto, Steven, nos vemos...";
		link.l1.go = "patria_35";
		break;

	case "patria_35":
		dialog.text = "Necesitas descansar, estás perdiendo el toque. Ven a mí en algún momento, te conseguiré algo de ron y buenas doncellas";
		link.l1 = "Gracias, te haré una visita cuando pueda.";
		link.l1.go = "patria_36";
		break;

	case "patria_36":
		DialogExit();
		AddQuestRecord("Patria", "75");
		pchar.questTemp.Patria = "epizode_12_barondie";
		DeleteAttribute(pchar, "questTemp.Patria.DodsonFail");
		break;
	// belamour legendary edition хвастаемся Фортуной
	case "check_out_my_frigate":
		dialog.text = "Interesante, intrigado. Bueno, vamos a dar un paseo.";
		link.l1 = "...";
		link.l1.go = "check_out_my_frigate_01";
		break;

	case "check_out_my_frigate_01":
		DialogExit();
		chrDisableReloadToLocation = true;
		bDisableFastReload = true;
		DoQuestReloadToLocation("pirates_town", "reload", "reload3_back", "SharkFrigateToTown");
		pchar.questTemp.SharkFrigate = true;
		break;

	case "check_out_my_frigate_02":
		dialog.text = "¡Que me reviente el bazo! ¡No creo lo que ven mis ojos! ¿Es realmente ella? Dime, ¿es ella? ¿Es esta la 'Fortuna'?";
		link.l1 = "Sí, amigo mío, tus ojos no te engañan. Es ella. ¿La extrañaste?";
		link.l1.go = "check_out_my_frigate_03";
		break;

	case "check_out_my_frigate_03":
		dialog.text = "¡Ja, ja, ja, no puedo creerlo! ¡Mil demonios! ¿Pero de dónde lo sacaste?";
		link.l1 = "De un cierto escocés llamado William Paterson. Sí, sí, del mismo que lo compró al Black Pastor.";
		link.l1.go = "check_out_my_frigate_04";
		break;

	case "check_out_my_frigate_04":
		dialog.text = "Sopla, hombre... ¿Y qué, te vendió 'Fortuna'? ¿Un barco tan hermoso? ¿Después de que lo compraste?";
		link.l1 = "Hehe, bueno, casi. Pongámoslo de esta manera: no nos llevamos muy bien, y tomé el barco como compensación por los costos que incurrí como resultado de nuestro conflicto. De todos modos, él no necesita un barco.";
		link.l1.go = "check_out_my_frigate_05";
		break;

	case "check_out_my_frigate_05":
		dialog.text = "Me sorprendes aún más ... Es un capitán militar al servicio de Inglaterra. Su escuadrón de la colonia puede robar si lo desea. Incluso yo no me arriesgué a romperme los dientes con él. ¿Y cómo lo comprobaste? ¿Lograste despegar el 'Fortune' del escuadrón?";
		link.l1 = "No, el escuadrón se hundió. En realidad, no fue fácil. La batalla fue seria, pero tuvo lugar lejos de lugares habitados, y solo mis marineros y oficiales estuvieron entre los testigos. En general, no temo la persecución por parte de las autoridades británicas. William Paterson simplemente desapareció durante alguna aventura regular...";
		link.l1.go = "check_out_my_frigate_06";
		break;

	case "check_out_my_frigate_06":
		dialog.text = "Vaya... Hace mucho que perdí la esperanza de volver a ver mi golondrina. Bueno, espero que este barco te sirva fielmente. ¡Realmente me alegro por ti, amigo!";
		link.l1 = "¿Qué? ¿No lo necesitas? Quería devolverlo a su dueño legítimo...";
		link.l1.go = "check_out_my_frigate_07";
		break;

	case "check_out_my_frigate_07":
		if (CheckAttribute(pchar, "questTemp.SharkGoldFleet"))
		{
			dialog.text = "¡Ja-ja-ja, mi amigo, guarda la 'Fortuna' para ti mismo. Primero, eres su legítimo dueño. La conseguiste honestamente en batalla. No es bueno abandonar el barco después de esto. Y en segundo lugar, ya tengo un nuevo navío. Por supuesto, cuando compré la 'Fortuna', no pensé que alguna vez la cambiaría por otra cosa. Pero, como ya no esperaba volver a verla, encargué una nueva fragata a Alexus. Y sabes... Es condenadamente buena. Escuché, y en este caso no fue sin tu participación, ¡ja ja!";
		}
		else
		{
			dialog.text = "Ja-ja-ja, mi amigo, quédate con 'Fortuna' para ti. Primero, eres su legítimo dueño. La conseguiste honestamente en batalla. No es bueno abandonar el barco después de esto. Y en segundo lugar, ya se está construyendo un nuevo barco para mí. Por supuesto, cuando compré 'Fortuna', no pensé que alguna vez la cambiaría por otra cosa. Pero, como ya no esperaba volver a verla, encargué una nueva fragata a Alexus. Y espero con ansias poder pisar su cubierta.";
		}
		link.l1 = "¡Bueno, entonces no tengo más remedio que quedarme con este hermoso barco para mí, Steven!";
		link.l1.go = "check_out_my_frigate_08";
		break;

	case "check_out_my_frigate_08":
		dialog.text = "Exactamente. Lo único que te pido es que cuides de 'Fortuna'. Créeme, no encontrarás un barco así en ningún otro lugar. Es único. Y lo amo como un recuerdo. Y me alegraría saber que mi amigo posee este barco, y no algún sinvergüenza.";
		link.l1 = "Bien, Steven. Prometo que protegeré 'Fortuna'.";
		link.l1.go = "check_out_my_frigate_09";
		break;

	case "check_out_my_frigate_09":
		dialog.text = "Sí, y una cosa más...";
		link.l1 = "Escuchando.";
		link.l1.go = "check_out_my_frigate_10";
		break;

	case "check_out_my_frigate_10":
		dialog.text = "Ya que ahora tienes 'Fortuna', quiero ofrecerte un negocio.";
		link.l1 = "Te estoy escuchando MUY atentamente.";
		link.l1.go = "check_out_my_frigate_11";
		break;

	case "check_out_my_frigate_11":
		if (!CheckAttribute(pchar, "questTemp.SharkGoldFleet.KGBB"))
		{
			dialog.text = "Como dije, Alexus está construyendo actualmente una nueva fragata para mí. Él, por supuesto, es poco probable que supere al 'Fortuna' en velocidad, pero tampoco cederá mucho. Y solo por una cosa necesito un par de barcos poderosos, pero rápidos. Podría hacerlo solo, pero dos son mucho mejores.";
			link.l1 = "Estupendo. ¿Y de qué tipo de negocio se trata?";
			link.l1.go = "check_out_my_frigate_12";
		}
		else
		{
			dialog.text = "Como dije, Alexus recientemente me construyó una nueva fragata. Él, por supuesto, es poco probable que supere al 'Fortuna' en velocidad, pero tampoco cederá mucho. Y solo para una cosa necesito un par de barcos poderosos, pero rápidos. Podría ser capaz de hacerlo solo, pero dos son mucho mejor.";
			link.l1 = "Estupendo. ¿Y qué clase de negocio es este?";
			link.l1.go = "check_out_my_frigate_13";
		}
		break;
	// Фрегат Акулы не построен
	case "check_out_my_frigate_12":
		dialog.text = "Aún es demasiado pronto para hablar de ello, porque todavía no sé cuándo mi nuevo barco saldrá del astillero. Alexus parece tener algunas dificultades con la extracción de materiales. Por cierto, si tienes la oportunidad, podrías ayudarle. Estoy seguro de que te pagará decentemente: le di un adelanto muy serio. Después de que encuentre todos los materiales, creo que en un mes mi barco estará listo. Entonces te estaré esperando. Pero asegúrate de venir en el 'Fortuna' y equiparlo de antemano, ¡entonces habrá poco tiempo! Sí, y asegúrate de que los españoles no quieran ver tu cabeza en una bandeja de plata. Te contaré todos los detalles más tarde.";
		link.l1 = "Bueno, preguntaré a nuestro constructor naval qué ayuda podría necesitar. Y volveremos a nuestra conversación un mes después de que ayude a Alexus, cuando vuelvas a navegar.";
		link.l1.go = "check_out_my_frigate_14";
		break;

	// Фрегат Акулы построен
	case "check_out_my_frigate_13":
		dialog.text = "Es demasiado pronto para hablar de ello, porque mi barco ni siquiera ha salido del astillero todavía. Aún necesito equiparlo. Así que te espero no antes de un mes. Pero asegúrate de venir en el 'Fortuna' y equiparlo de antemano, ¡entonces habrá poco tiempo! Sí, y asegúrate de que los españoles no quieran ver tu cabeza en una bandeja de plata. Te contaré todos los detalles más tarde.";
		link.l1 = "Está bien, entonces volveremos a nuestra conversación más tarde, cuando estés navegando de nuevo.";
		link.l1.go = "check_out_my_frigate_14";
		break;

	case "check_out_my_frigate_14":
		dialog.text = "Bueno, está bien. Ahora voy a la residencia, si no te importa. Las cosas, como dicen, no esperan.";
		link.l1 = "¡Hasta pronto, Shark! No digo adiós.";
		link.l1.go = "check_out_my_frigate_15";
		break;

	case "check_out_my_frigate_15":
		DialogExit();
		sld = characterFromId("Dodson");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "reload", "reload3_back", "SharkFrigateEnd", -1);
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	// belamour legendary edition на пару с Акулой
	case "SharkGoldFleet":
		if (sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
		{
			dialog.text = "El mío está listo, ¿qué tal el tuyo? Te dije que vinieras en la 'Fortuna'. No sé dónde lo dejaste, pero es demasiado arriesgado embarcarse en tal apuesta en cualquier otro barco. Así que te espero en el barco en el que acordamos. Y no aprietes demasiado.";
			link.l1 = "¡Maldita sea, completamente lo olvidé, canalla! Espera: volveré al barco correcto.";
			link.l1.go = "exit";
			break;
		}
		if (GetCompanionQuantity(pchar) > 1)
		{
			dialog.text = "Charles, te dije que vinieras sin escuadrón. En el caso que quiero tratar contigo, definitivamente no se necesitan barcos extra. Mueve tu flotilla a algún lugar y regresa.";
			link.l1 = "Sí, lo olvidé por completo. Espera: volveré pronto sin una escuadra.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "¡Ah, ahí estás, amigo! ¡Por fin! Y luego comencé a preocuparme. Mi barco está casi listo. Ahora lo envié a Tirax: debe equiparlo con el calibre treinta y dos, que tomó del pesado galeón premio el mes pasado. Ya lo he llevado a los Turcos y de regreso, y debo decir que Alexus hizo un gran trabajo. Por cierto, todavía no he elegido un nombre adecuado para él, aunque tengo varias opciones. ¿Puedes ayudarme a elegir?";
		link.l1 = "¡Por supuesto que ayudaré! Como llames a un barco, así navegará, ¿verdad? ¿Cuáles son tus opciones?";
		link.l1.go = "SharkGoldFleet_01";
		break;

	case "SharkGoldFleet_01":
		dialog.text = "He decidido por tres opciones hasta ahora.";
		link.l1 = "...";
		link.l1.go = "SharkGoldFleet_02";
		break;

	case "SharkGoldFleet_02":
		dialog.text = "La primera opción es 'Fantasma'. La fragata es rápida y poderosa, y con ese nombre, todos los avaros desde La Habana hasta Cumaná temblarán con solo mencionarla.";
		link.l1 = "Sí, y también necesitas aparecer y desaparecer en la niebla para que los marineros definitivamente empiecen a persignarse, ¡ja ja! Buen nombre, me gusta.";
		link.l1.go = "SharkGoldFleet_03";
		break;

	case "SharkGoldFleet_03":
		dialog.text = "Me gusta también. La segunda opción es 'Shark'. ¿Y qué? ¿Por qué no darle a mi barco su propio apodo? ¡Vamos a ser tocayos con él, ja!";
		link.l1 = "Hay un Shark en el 'Shark'... Irónico. Pero todos sabrán exactamente quién es el dueño del barco.";
		link.l1.go = "SharkGoldFleet_04";
		break;

	case "SharkGoldFleet_04":
		dialog.text = "Aquí estoy más o menos igual. Y la tercera opción es 'Torbellino'. Para que todos tengan miedo de siquiera acercarse a mi barco, ¡ja ja ja!";
		link.l1 = "¿Porque puedes encontrarte con una ráfaga de balas desde el costado? Y qué, no está mal.";
		link.l1.go = "SharkGoldFleet_05";
		break;

	case "SharkGoldFleet_05":
		dialog.text = "¡Exactamente! Pero ahora no puedo decidir entre estos tres nombres. Así que vamos, ayuda. Como desees.";
		link.l1 = "Sugiero llamarlo 'Fantasma'. ¡Entonces todos los mercaderes izarán la bandera blanca tan pronto como te vean en el horizonte!";
		link.l1.go = "SharkGoldFleet_05f";
		link.l2 = "Me gusta el nombre 'Shark'. ¡Todos deben saber que el barco no es de un recién llegado, sino del mismo jefe de la Hermandad de la Costa!";
		link.l2.go = "SharkGoldFleet_05a";
		link.l3 = "Creo que 'Flurry' es un buen nombre. Cualquier guerrero, corsario o comerciante debería saber lo que ocurrirá si decide enfrentarse a este barco.";
		link.l3.go = "SharkGoldFleet_05s";
		break;

	case "SharkGoldFleet_05f":
		pchar.questTemp.SharkGoldFleet.KGBB = "Phantom";
		dialog.text = "¡Mira, incluso los militares empezarán a hacer lo mismo, ja! Entonces, está decidido. Sostén la jarra, amigo. Brindemos por mi nuevo barco. ¡Por 'Fantasma!'";
		link.l1 = "¡Por 'Fantasma!'";
		link.l1.go = "SharkGoldFleet_06";
		break;

	case "SharkGoldFleet_05a":
		pchar.questTemp.SharkGoldFleet.KGBB = "Shark";
		dialog.text = "¡Y que piensen tres veces antes de cruzarse en mi camino! Entonces, está decidido. Sostén la jarra, amigo. Brindemos por mi nuevo barco. ¡Por el 'Shark'!";
		link.l1 = "¡Por el 'Shark'!";
		link.l1.go = "SharkGoldFleet_06";
		break;

	case "SharkGoldFleet_05s":
		pchar.questTemp.SharkGoldFleet.KGBB = "Flurry";
		dialog.text = "Y si aún decide, tal ráfaga lo cubrirá que las tormentas tropicales parecerán una brisa ligera. Entonces, está decidido. Sostén la jarra, amigo. Brindemos por mi nuevo barco. ¡Por 'Ráfaga!'";
		link.l1 = "¡Por 'Flurry!'";
		link.l1.go = "SharkGoldFleet_06";
		break;

	case "SharkGoldFleet_06":
		dialog.text = "¡Y que este barco sirva fielmente y no conozca la amargura de la derrota! Bueno, ahora al grano.";
		link.l1 = "Te escucho con atención.";
		link.l1.go = "SharkGoldFleet_07";
		break;

	case "SharkGoldFleet_07":
		dialog.text = "Dime, Charles, ¿sabes qué es la 'Flota Dorada'?";
		link.l1 = "¡Ja-ja! .. Ya me he atragantado con ron. Steven, no me digas que estás en dos fragatas para robar el convoy más fuertemente armado del Caribe.";
		link.l1.go = "SharkGoldFleet_08";
		break;

	case "SharkGoldFleet_08":
		dialog.text = "Bueno, no, por supuesto, no soy suicida. Definitivamente no robaremos todo el convoy. Pero aquí podemos sacar algo de allí.";
		link.l1 = "Steven, lo siento, por supuesto, pero no estoy listo para esto. ¡Sí, los españoles nos quemarán vivos si nos metemos en su flota! Sigue sin mí.";
		link.l1.go = "SharkGoldFleet_09";
		link.l2 = "Está bien, donde no desaparecimos ... ¡Estoy listo para participar!";
		link.l2.go = "SharkGoldFleet_11";
		break;

	case "SharkGoldFleet_09":
		pchar.questTemp.SharkGoldFleet = "RUinDeal";
		dialog.text = "¡Argh! Es una lástima. Soy demasiado arriesgado sin ti. Está bien, ahora no te persuadiré, pero piénsalo, ¿de acuerdo? Si alguna vez decides hacerlo, por favor, házmelo saber.";
		link.l1 = "Si lo hago, entonces seguro. Lo siento, Steven.";
		link.l1.go = "exit";
		break;

	case "SharkGoldFleet_10":
		dialog.text = "¡Tales empresas no se rinden! Bueno, ¿y tú? ¿Quizás cambiaste de opinión?";
		link.l1 = "No, amigo, lo siento, pero aún paso.";
		link.l1.go = "exit";
		link.l2 = "Está bien, donde no desaparecimos... ¡Estoy listo para participar!";
		link.l2.go = "SharkGoldFleet_11";
		break;

	case "SharkGoldFleet_11":
		if (sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
		{
			dialog.text = "Puede que estés listo, pero tu barco no lo está. Te dije que vinieras en la 'Fortuna'. No sé dónde la dejaste, pero es demasiado arriesgado embarcarse en tal apuesta en cualquier otro barco. Así que te espero en el barco en el que acordamos. Y no te aprietes demasiado.";
			link.l1 = "Maldita sea, lo olvidé por completo, ¡torpe! Espera: regresaré al barco correcto.";
			link.l1.go = "exit";
			break;
		}
		if (GetCompanionQuantity(pchar) > 1)
		{
			dialog.text = "Pero no: no estás listo, Charles. Te dije que vinieras sin escuadrón. En el caso que quiero tratar contigo, barcos extra definitivamente no son necesarios. Mueve tu flota a otro lugar y regresa.";
			link.l1 = "Sí, lo olvidé por completo. Espera: volveré pronto sin un escuadrón.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "¡Mil demonios, eso es exactamente lo que quería oír! Entonces, sugiero que tú y yo arrebatemos un trozo del convoy. Mucho botín...";
		link.l1 = "¿Robar, dices? ¿Sin que te atrapen los barcos de guardia?";
		link.l1.go = "SharkGoldFleet_12";
		break;

	case "SharkGoldFleet_12":
		dialog.text = "Exactamente. Mira, como probablemente sabes, la 'Flota de Oro' se reúne en Portobello y de ahí va a La Habana. Después de La Habana, ya es inútil interceptarla: va a través del Atlántico a España con tal escolta que solo un completo cretino se atrevería a acercarse. En el momento de la transición de Portobello a La Habana, la situación no es mucho mejor. Por supuesto, puedes intentarlo, pero para ello necesitas reunir una escuadra capaz de romper fuertes como nueces. Pero en Portobello, los barcos convergen de toda Tierra Firme, y allí ya no están particularmente protegidos.";
		link.l1 = "Solo ahora el tiempo de la transición y los nombres de tales barcos están estrictamente clasificados. No vamos a quedarnos en Portobello durante medio año e interceptar todos los barcos españoles que van al puerto.";
		link.l1.go = "SharkGoldFleet_13";
		break;

	case "SharkGoldFleet_13":
		dialog.text = "Por supuesto que no lo haremos. Desde Cartagena, por ejemplo, los barcos van solos, y, como bien has señalado, sólo Dios sabe qué tipo de barcos son y cuándo irán. Pero desde Caracas, junto a la cual hay una mina española, y que se encuentra bastante lejos de Portobello, los barcos no están completamente solos.";
		link.l1 = "¿Cómo es que no está completamente solo?";
		link.l1.go = "SharkGoldFleet_14";
		break;

	case "SharkGoldFleet_14":
		dialog.text = "Logré averiguar que un barco cargado de mercancías sale de Caracas solo o con una pequeña escolta, pero en algún lugar en la longitud del Golfo de Maracaibo, los buques de guerra españoles lo encuentran para garantizar su seguridad posterior. ¿Cómo crees que saben cuándo y a quién necesitan encontrar allí?";
		link.l1 = "Debieron haberles dicho algo...";
		link.l1.go = "SharkGoldFleet_15";
		break;

	case "SharkGoldFleet_15":
		dialog.text = "Correcto. Antes de que el barco principal zarpe, un barco mensajero va de Caracas a Portobello, informando el lugar y la fecha de la reunión, así como el nombre del barco español. Luego regresa y lleva la confirmación de que el barco será recibido en el momento y lugar correctos. Solo después de eso, nuestro objetivo contigo se avanza desde Caracas.";
		link.l1 = "Pero si interceptamos al mensajero, entonces el barco en Caracas no recibirá confirmación y no saldrá del puerto. ¿Tienes alguna idea sobre esto? Además, ¿cómo vamos a atrapar al propio mensajero? Tampoco sabemos cuándo se irá.";
		link.l1.go = "SharkGoldFleet_16";
		break;

	case "SharkGoldFleet_16":
		dialog.text = "Y aquí hay un pequeño inconveniente. Los españoles, por supuesto, usan lanchas mensajeras para estos propósitos, pero esto es arriesgado: la probabilidad es demasiado alta de que sean interceptadas por el primer pirata que se cruce. Así que puedes esperar mucho tiempo antes de enviar el barco. Por lo tanto, si hay oportunidad, transmiten instrucciones junto con buenos barcos poderosos, pero rápidos, como mercantes, por ejemplo, o corsarios que van por la ruta correcta. \nTal como un correo sellado. Además, es mucho más barato que enviar un barco mensajero separado, incluso una lancha. Y a los avaros funcionarios españoles les gusta ahorrar dinero mientras se guardan algo en el bolsillo, jeje.";
		link.l1 = "¡Creo que entiendo! ¿Necesito convertirme en tal comerciante?";
		link.l1.go = "SharkGoldFleet_17";
		break;

	case "SharkGoldFleet_17":
		dialog.text = "¡Exactamente! Y tuvimos suerte: logré averiguar de una fuente confiable que en Caracas ahora están buscando un mensajero así para enviarlo con una carta en las próximas tres semanas. ¡Y tú justo tienes un barco poderoso y rápido, y además construido por los españoles! Obtén una licencia de GVIK, para mayor verosimilitud, por seis meses de una vez, compra suficientes mercancías en Caracas para una reventa lucrativa en Portobello, y luego acércate al jefe de la autoridad portuaria y pregunta si necesitas llevar algo por el camino. \nSi la Autoridad Portuaria pregunta, preséntate como español. Y sí, no pienses ni por un momento en llevarte un escuadrón contigo. No necesitamos llamar demasiado la atención, de lo contrario, toda la empresa podría venirse abajo.";
		link.l1 = "¿Y con los documentos que me darán, averiguaré la fecha y el lugar de la reunión del barco y el convoy?";
		link.l1.go = "SharkGoldFleet_18";
		break;

	case "SharkGoldFleet_18":
		dialog.text = "No tan simple. Te digo: los documentos están sellados. Y no puedes abrirlos tú mismo. Los abrirán en la autoridad portuaria de Portobello, y luego escribirán una respuesta y, si eres tan amable de decir que vuelves a Caracas, te pedirán que lo lleves allí. La respuesta, por supuesto, también estará sellada.";
		link.l1 = "¿Y cómo puedo averiguar entonces el lugar y la fecha de la reunión?";
		link.l1.go = "SharkGoldFleet_19";
		break;

	case "SharkGoldFleet_19":
		dialog.text = "Tendrás que ser astuto y de alguna manera espiarlo... Por ejemplo, en el momento en que se abran los documentos en Portobello y escriban la respuesta. O simplemente róbalos cuando te den una confirmación, que necesitarás llevar a Caracas. Pero esta no es una buena opción: después de esto, todo puede salir mal.";
		link.l1 = "Es difícil, por supuesto... Pero creo que puedo manejarlo.";
		link.l1.go = "SharkGoldFleet_20";
		break;

	case "SharkGoldFleet_20":
		dialog.text = "Yo, por mi parte, tomaré mi barco de Marcus y te esperaré anclado en el Cabo Santa María en Curazao. Cuando termines, solo muévete hacia mí. Interceptamos el barco en las coordenadas indicadas, y luego inmediatamente nos largamos de allí. ¿Ahora entiendes por qué se necesitan barcos poderosos, pero rápidos? No quiero pelear con el escuadrón militar español en absoluto. Tendrás que escapar de ellos.";
		link.l1 = "Entendido. Bueno, entonces me voy. ¡Encuéntrame en Cabo Santa María!";
		link.l1.go = "SharkGoldFleet_21";
		break;

	case "SharkGoldFleet_21":
		dialog.text = "Así es, nos encontraremos allí. ¡Buena suerte, amigo! Espero que nuestro negocio salga bien.";
		link.l1 = "Eso espero también. De todos modos, me voy.";
		link.l1.go = "SharkGoldFleet_22";
		break;

	case "SharkGoldFleet_22":
		DialogExit();
		AddQuestRecord("SharkGoldFleet", "1");
		pchar.questTemp.SharkGoldFleet = "start";
		SetFunctionExitFromLocationCondition("SharkGoldFleetStart", pchar.location, false);
		if (!bImCasual)
			SetFunctionTimerCondition("SharkGoldFleet21", 0, 0, 21, false);
		if (!bImCasual)
			SetFunctionTimerCondition("SharkGoldFleet30", 0, 0, 30, false);
		else
			NewGameTip("Modo exploración: el temporizador está desactivado.");
		break;
	// провал
	case "SharkGoldFleet_23":
		dialog.text = "¡Maldito Charles! ¡Pensé que nunca te volvería a ver! ¿Dónde has estado? Te estuve esperando en el lugar acordado, pero nunca llegaste. Y no hubo noticias tuyas.";
		link.l1 = "Lo siento, Steven. No pude completar mi tarea.";
		link.l1.go = "SharkGoldFleet_24";
		break;

	case "SharkGoldFleet_24":
		NextDiag.CurrentNode = "First time";
		dialog.text = "Eh, dejaron escapar tal pez... Está bien, no te desanimes. Mejor suerte la próxima vez.";
		link.l1 = "Eso espero.";
		link.l1.go = "exit";
		break;

	case "SharkGoldFleet_25":
		if (GetCompanionQuantity(pchar) > 1)
		{
			dialog.text = pchar.name + "¿Qué demonios? ¡Te dije que vinieras sin escuadrón! Entiende: ¡no necesitamos ningún lastre, de lo contrario, toda la operación puede fracasar! No sé qué te pasó por la cabeza, pero así no funcionará. Envía urgentemente tu caravana a algún lugar y regresa en un solo barco. Te estoy esperando aquí.";
			link.l1 = "Sí, solo pensé que esto es más probable... Está bien, te entiendo. ¡Espera aquí: ahora vuelvo!";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharkGoldFleet_25";
			break;
		}
		if (sti(RealShips[sti(pchar.ship.type)].basetype) != SHIP_FRIGATE_L)
		{
			dialog.text = pchar.name + ", ¿qué demonios? ¡Te dije que estuvieras en la 'Fortuna'! Entiende: necesitamos dos barcos rápidos y poderosos, de lo contrario toda la operación puede fracasar. No sé qué te ha pasado, pero así no funcionará. Cambia urgentemente tu cascarón por la 'Fortuna' y vuelve. Te espero aquí.";
			link.l1 = "Sí, solo pensé que este barco es mejor... Bien, te entiendo. Espera aquí: ¡ya vuelvo!";
			link.l1.go = "exit";
			NextDiag.TempNode = "SharkGoldFleet_25";
			break;
		}
		dialog.text = "¡Y aquí estás, mi amigo! Bueno, ¿qué opinas de mi apuesto?";
		link.l1 = "¡Hermosa fragata, Steven! No rechazaría esto...";
		link.l1.go = "SharkGoldFleet_26";
		break;

	case "SharkGoldFleet_26":
		dialog.text = "No, ahora tienes 'Fortuna', ¡jaja! Bueno, cuéntame cómo te fue.";
		if (pchar.questTemp.SharkGoldFleet == "LightVarToShark")
		{
			link.l1 = "Todo salió a la perfección: logré hacerme pasar por un comerciante honesto y confiable. Llevé los documentos a Portobello, donde logré distraer al jefe de la autoridad portuaria durante cinco minutos y reescribí para mí la fecha y las coordenadas de la reunión de los barcos con el cargamento y el escuadrón militar.";
			link.l1.go = "SharkGoldFleet_27";
		}
		else
		{
			link.l1 = "Hubo algunas complicaciones menores. La carta fue enviada a Portobello por mensajero. La intercepté, la entregué al destinatario e incluso recibí una respuesta, pero el jefe de la autoridad portuaria adivinó que yo no era la persona que debía traer los documentos. Tuve que salir de allí a la fuerza. Pero averigüé la fecha y las coordenadas de la reunión del barco con la carga y el escuadrón militar, y entregué la respuesta a Caracas, ¡así que la producción nos está esperando!";
			link.l1.go = "SharkGoldFleet_30";
		}
		break;

	case "SharkGoldFleet_27":
		dialog.text = "Espera un segundo. ¿Dijiste 'barcos'?";
		link.l1 = "¡Sí, Shark! ¡Habrá dos de ellos!";
		link.l1.go = "SharkGoldFleet_28";
		break;

	case "SharkGoldFleet_28":
		dialog.text = "Ja-ja-ja, ¡sí, daremos en el clavo! Bueno, mi bestia está lista para pasar por el bautismo de fuego. Pero aún no ha participado en las batallas, así que llevemos la batalla. Y por ahora, me uniré a tu escuadrón.";
		link.l1 = "¿Debo comandar al propio Steven Dodson, jefe de la Cofradía de la Costa? ¡En marcha!";
		link.l1.go = "SharkGoldFleet_29";
		break;

	case "SharkGoldFleet_29":
		NextDiag.TempNode = "SharkGoldFleet_33";
		pchar.questTemp.SharkGoldFleet.talk = true;
		AddQuestRecord("SharkGoldFleet", "22");
		AddQuestUserData("SharkGoldFleet", "date", pchar.questTemp.SharkGoldFleet.Date);
		SGF_SharkCompanion();
		pchar.quest.SGF_SharkDelGroup1.win_condition.l1 = "ExitFromSea";
		pchar.quest.SGF_SharkDelGroup1.function = "SGF_SharkDelGroup";
		if (bImCasual)
		{
			pchar.GenQuest.SeaHunter2Pause = true;
			SeaHunter_Delete();
		}
		dialog.text = "Bueno, no seas demasiado arrogante: es solo porque pelearé en mi barco por primera vez. Y asegúrate de la disponibilidad de oficiales libres para los barcos capturados. Porque sus bodegas estarán llenas, y ninguno de mi tripulación podrá manejar el barco por su cuenta... Bien, basta de rascarse la lengua. ¡El botín nos espera!";
		link.l1 = "¡Exactamente! Voy a mi barco.";
		link.l1.go = "exit";
		break;

	case "SharkGoldFleet_30":
		dialog.text = "Sí, heredaste ... Entonces necesitamos prepararnos para el hecho de que la escuadra llegará allí antes de la fecha acordada, y tendremos que luchar con todos a la vez.";
		link.l1 = "¿Por qué dices eso?";
		link.l1.go = "SharkGoldFleet_31";
		break;

	case "SharkGoldFleet_31":
		dialog.text = "Y tú reflexionas. En Portobello saben que el barco con el cargamento definitivamente saldrá de Caracas, porque llevaste la carta de respuesta allí. Pero como te has delatado, harán todo lo posible para impedir que intercepemos este barco. Creo que la escuadra llegará allí antes. Eso es lo que yo haría. Así que, prepárate para una dura pelea. Retirarse tarde.";
		link.l1 = "No te preocupes. Tú y yo somos dos lobos de mar, ¡no pasamos por esto!";
		link.l1.go = "SharkGoldFleet_32";
		break;

	case "SharkGoldFleet_32":
		dialog.text = "Tu verdad. Bueno, mi bestia está lista para someterse a un bautismo de fuego. Pero aún no ha participado en las batallas, así que tú lidera la batalla. Mientras tanto, me uniré a tu escuadrón.";
		link.l1 = "¿Estoy a punto de comandar al mismo Stephen Dodson, jefe de la Hermandad de la Costa? ¡En marcha!";
		link.l1.go = "SharkGoldFleet_29";
		break;

	case "SharkGoldFleet_33":
		NextDiag.TempNode = "SharkGoldFleet_33";
		dialog.text = "Sin tiempo para charlar, " + pchar.name + "¡Vamos por el botín!";
		link.l1 = "¡Y que la suerte esté con nosotros!";
		link.l1.go = "exit";
		break;
	// делим добычу на берегу
	case "SharkGoldFleet_34":
		if (makeint(pchar.questTemp.SharkGoldFleet) > 74)
		{
			dialog.text = "¡Mil demonios! ¡Gran trabajo, Charles! ¡El botín resultó ser mucho más rico de lo que pensé originalmente! Creo que todo este viaje definitivamente valió la pena.";
			link.l1 = "¡Estoy totalmente de acuerdo contigo, Steven! ¡Hoy es definitivamente nuestro día!";
			link.l1.go = "SharkGoldFleet_35";
		}
		else
		{
			if (makeint(pchar.questTemp.SharkGoldFleet) > 24)
			{
				dialog.text = "Buen trabajo, amigo. Aunque, debemos admitir que hemos perdido mucha presa.";
				link.l1 = "Estoy de acuerdo, Steven, podríamos hacerlo mejor. ¡Pero lo que hay también es bueno!";
				link.l1.go = "SharkGoldFleet_35";
			}
			else
			{
				dialog.text = "¡Maldita sea! Era una idea tan buena... Y como resultado, los gastos de esta campaña son más que las ganancias. ¡Charles, te di el mando y lograste perderlo todo!";
				link.l1 = "No digas nada... Yo mismo estoy malditamente enfadado. ¡Cuánta presa se nos ha escapado de las manos!..";
				link.l1.go = "SharkGoldFleet_37";
			}
		}
		break;

	case "SharkGoldFleet_35":
		dialog.text = "Bueno, ambos hicimos un buen trabajo. Yo ideé un plan y obtuve la información sobre el mensajero, y tú brillantemente llevaste a cabo ese plan. Y ambos luchamos en igualdad de condiciones por nuestra presa. Por lo tanto, propongo dividirla según las leyes de la Hermandad de la Costa: ¡igualitariamente!";
		link.l1 = "¡Lo haremos!";
		link.l1.go = "SharkGoldFleet_36";
		break;

	case "SharkGoldFleet_36":
		dialog.text = "Bueno, ahora me voy a Isla Tesoro. Necesito reparar el barco y celebrar debidamente el primer viaje exitoso en mi nuevo barco. ¡Buena suerte, amigo! ¡Siempre me alegra verte en mi residencia!";
		link.l1 = "Me alegra que nuestro negocio haya resultado tan rentable. Definitivamente te visitaré en algún momento. ¡Buena suerte!";
		link.l1.go = "SharkGoldFleet_39";
		break;

	case "SharkGoldFleet_37":
		dialog.text = "Está bien, guárdatelo todo. Si es que queda algo. No me importan estos pequeñuelos. Después de todo, te involucré en todo este asunto.";
		link.l1 = "Sí, mi error también... Lo siento, Steven.";
		link.l1.go = "SharkGoldFleet_38";
		break;

	case "SharkGoldFleet_38":
		dialog.text = "No te disculpes, todavía te debo la vida, y no lo olvidaré. Y ahora me voy a Isla Tesoro. Necesitamos reparar el barco y lavarlo... Aunque, qué hay que lavar... ¡Buena suerte, camarada! ¡Siempre encantado de verte en mi residencia!";
		link.l1 = "Está bien, cualquier cosa puede suceder, las derrotas ocurren. Lo principal es que estamos vivos. ¡Definitivamente te visitaré alguna vez, amigo! ¡Buena suerte!";
		link.l1.go = "SharkGoldFleet_39";
		break;

	case "SharkGoldFleet_39":
		if (makeint(pchar.questTemp.SharkGoldFleet) > 74)
		{
			AddQuestRecord("SharkGoldFleet", "34");
			ChangeCharacterComplexReputation(pchar, "fame", 10);
			ChangeCharacterComplexReputation(pchar, "authority", 5);
			ChangeOfficersLoyality("good_all", 2);
			AddComplexSeaExpToScill(150, 150, 150, 150, 150, 150, 0);
			AddCharacterExpToSkill(pchar, "Leadership", 300);
			AddCharacterExpToSkill(PChar, "Fortune", 300);
			AddCharacterExpToSkill(PChar, "Sneak", 300);
		}
		else
		{
			if (makeint(pchar.questTemp.SharkGoldFleet) > 24)
			{
				AddQuestRecord("SharkGoldFleet", "35");
				ChangeCharacterComplexReputation(pchar, "fame", 1);
				ChangeCharacterComplexReputation(pchar, "authority", 1);
				AddComplexSeaExpToScill(50, 50, 50, 50, 50, 50, 0);
				AddCharacterExpToSkill(pchar, "Leadership", 200);
				AddCharacterExpToSkill(PChar, "Fortune", 200);
				AddCharacterExpToSkill(PChar, "Sneak", 200);
			}
			else
			{
				AddQuestRecord("SharkGoldFleet", "36");
				AddCharacterExpToSkill(pchar, "Leadership", 100);
				AddCharacterExpToSkill(PChar, "Fortune", 100);
				AddCharacterExpToSkill(PChar, "Sneak", 100);
			}
		}
		if (makeint(pchar.questTemp.SharkGoldFleet) > 24)
		{
			if (GetSquadronGoods(pchar, GOOD_GOLD) > 0)
			{
				RemoveCharacterGoods(pchar, GOOD_GOLD, sti(makeint(pchar.questTemp.SharkGoldFleet.Gold) / 2));
			}
			if (GetSquadronGoods(pchar, GOOD_SILVER) > 0)
			{
				RemoveCharacterGoods(pchar, GOOD_SILVER, sti(makeint(pchar.questTemp.SharkGoldFleet.Silver) / 2));
			}
			if (GetSquadronGoods(pchar, GOOD_SANDAL) > 0)
			{
				RemoveCharacterGoods(pchar, GOOD_SANDAL, sti(makeint(pchar.questTemp.SharkGoldFleet.Sandal) / 2));
			}
			if (GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0)
			{
				RemoveCharacterGoods(pchar, GOOD_SHIPSILK, sti(makeint(pchar.questTemp.SharkGoldFleet.Silk) / 2));
			}
			if (GetSquadronGoods(pchar, GOOD_ROPES) > 0)
			{
				RemoveCharacterGoods(pchar, GOOD_ROPES, sti(makeint(pchar.questTemp.SharkGoldFleet.Ropes) / 2));
			}
			if (GetSquadronGoods(pchar, GOOD_OIL) > 0)
			{
				RemoveCharacterGoods(pchar, GOOD_OIL, sti(makeint(pchar.questTemp.SharkGoldFleet.Gold) / 2));
			}
		}
		SGF_GoodSwimReturn();
		SGF_DelAllSubAttributes(); // убираем все лишнее, чтобы не болталось
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "SGF_SharkToIT", -1);
		CloseQuestHeader("SharkGoldFleet");
		DialogExit();
		break;
	}
}
