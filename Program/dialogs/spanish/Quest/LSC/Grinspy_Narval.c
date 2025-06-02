// Дональд Гринспи - лидер нарвалов
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		if (npchar.quest.meeting == "0")
		{
			dialog.text = "¿Qué? ¿Qué quieres?";
			link.l1 = TimeGreeting() + ". Me llamo " + GetFullName(pchar) + " Quería conocer al líder del clan.";
			link.l1.go = "meeting";
			npchar.quest.meeting = "1";
		}
		else
		{
			dialog.text = "Ah, " + GetFullName(pchar) + ". ¿Quieres algo?";
			link.l5 = "Solo quería saludarte. ¡Nos vemos!";
			link.l5.go = "exit";
		}
		NextDiag.TempNode = "First time";
		break;

	case "meeting": // первая встреча
		dialog.text = "Ahora me conoces. Me llamo Donald Greenspen y no me hagas enfadar a mí ni a mis hombres. Y no intentes visitar el 'San Gabriel' hasta que tengas una contraseña. La tienda es libre de visitar, todos necesitan comerciar. ¿Alguna pregunta?";
		link.l2 = "No, lo tengo. Nos vemos.";
		link.l2.go = "exit";
		NextDiag.TempNode = "First time";
		break;

		// ----------------------------------после разгрома Чада и Мэри на Каролине---------------------------
	case "shark":
		dialog.text = "¿Qué asunto tienes para mí?";
		link.l1 = "Una muy desagradable, Donald. Anoche hubo un intento de asesinato contra Steven. Participaron luchadores de tu clan.";
		link.l1.go = "shark_1";
		break;

	case "shark_1":
		dialog.text = "No sé sobre eso. ¿Por qué piensas que eran mis hombres?";
		link.l1 = "Porque yo estuve allí. Podemos ver la diferencia entre tus hombres, piratas y Rivados. El grupo estaba liderado por Mary Casper y Chad Kapper. ¿Necesitas más pruebas?";
		link.l1.go = "shark_2";
		break;

	case "shark_2":
		dialog.text = "Solo puedo asegurarte que ni yo ni mis hombres tenemos nada que ver con eso.";
		link.l1 = "Tendrás que asegurárselo al almirante y no será fácil. Dodson está muy enfadado con todos los Narvales después del ataque. Va a declararte la guerra: dejará de proporcionarte provisiones y disparará a tus hombres siempre que se le presente la oportunidad. Y no son solo palabras.";
		link.l1.go = "shark_3";
		break;

	case "shark_3":
		dialog.text = "Espero que ese almirante entienda lo que va a hacer. ¿Acaso duda que mis hombres también pueden disparar?";
		link.l1 = "Creo que sí. Está listo para convertir el 'San Augustine' en una fortaleza y luchar hasta que todos mueran de hambre. Además, Dodson va a hablar con los Rivados y ofrecerles cooperación. No tendrán ninguna oportunidad contra el almirante y los Rivados juntos.";
		link.l1.go = "shark_4";
		break;

	case "shark_4":
		dialog.text = "¡Maldita sea! ¡Pero nosotros no somos parte de este intento! ¿Por qué todo el clan debe pagar por las acciones de esa estúpida chica Mary y un montón de canallas de mi tripulación?\nAdemás, hablemos de lógica, al matar a Marlow, Dodson mismo provocó a Mary y a mis soldados. Eso es exactamente lo que sucede cuando cometes tal bajeza.";
		link.l1 = "No entiendes nada. Te engañaron. ¿Por qué estás tan seguro de que Dodson ha matado a Alan? En realidad, él piensa que tú lo hiciste para tomar su posición...";
		link.l1.go = "shark_5";
		break;

	case "shark_5":
		dialog.text = "No me importa un carajo lo que él piense. Todas las pruebas están en su contra. Solo él y sus hombres tenían acceso a la prisión. Alan estaba en sus manos. Red Mary me contó mucho. Antes de que Alan fuera asesinado, Dodson visitó personalmente la prisión y no lo hace a menudo.";
		link.l1 = "¿Has visto su muerte?";
		link.l1.go = "shark_6";
		break;

	case "shark_6":
		dialog.text = "¡Tonterías! Por supuesto que no lo he hecho.";
		link.l1 = "Y Chimiset tienen. Sí-sí, el mago Rivados que había estado sentado junto a Alan. También fue asesinado allí recientemente. Estuve en la prisión un día antes de su muerte y hablé con él. Milrow fue asesinado por Chad Kapper, el contramaestre dShark.";
		link.l1.go = "shark_7";
		break;

	case "shark_7":
		dialog.text = "¿Es verdad?";
		link.l1 = "Piénsalo: a Chimiset no le importaba tu relación con el almirante. No tenía razón para mentir. El viejo hechicero tenía miedo de Chad, supuso que él sería el siguiente. Tenía razón, Chad lo asesinó tan pronto como supo que el almirante iba a liberarlo.";
		link.l1.go = "shark_8";
		break;

	case "shark_8":
		dialog.text = "¿Pero por qué Kapper quería la muerte de Alan?";
		link.l1 = "Maldita sea, ¿de verdad no entiendes? Te he dicho que Kapper estaba trabajando con la Roja Mary. Quería tomar la posición dShark y preparó un plan astuto para hacerlo. Matar a Alan Milrow y difundir chismes sobre la implicación dShark en su muerte hizo que el clan Narval se volviera hostil contra el almirante...";
		link.l1.go = "shark_9";
		break;

	case "shark_9":
		dialog.text = "";
		link.l1 = "La tonta de Mary confió en él y se puso del lado del verdadero asesino de su novio. Habían persuadido a algunos Narvales para unirse a ellos, debió ser fácil para Mary. Luego organizaron un ataque al almirante en la cabina de Fazio, quien fue obligado a escribir una invitación al almirante...";
		link.l1.go = "shark_10";
		break;

	case "shark_10":
		dialog.text = "";
		link.l1 = "Tengo una carta de Fazio que lo explica todo. Chimiset fue asesinado por Chad como un testigo peligroso. Estaba cooperando con los Narvales y los Rivados estarían realmente encantados de escuchar eso durante su charla con Shark. Demostraremos fácilmente a Eddie el Negro que Chad se ha convertido en uno de los tuyos mostrando esta carta.";
		link.l1.go = "shark_11";
		break;

	case "shark_11":
		dialog.text = "Mm. Tienes todas las cartas ganadoras, ¿qué haces aquí entonces? Quieres algo de mí, ¿verdad?";
		link.l1 = "Lo hago. Porque creo que todo fue plan de Chad y tú no estás involucrado. Chad engañó a Mary, ella llamó a sus amigos de tu clan para ayudarla, esa es toda la historia. Al menos, no he encontrado ninguna evidencia contra ti o cualquier otro Narval...";
		link.l1.go = "shark_12";
		break;

	case "shark_12":
		dialog.text = "";
		link.l1 = "Pero eso no significa que no queden otros conspiradores. Quiero que los busques. Entonces, tal vez, resolveremos las cosas sin una matanza.";
		link.l1.go = "shark_13";
		break;

	case "shark_13":
		dialog.text = "Ya te he dicho que ninguno más de mis hombres fue parte de esto. Después de la muerte de Marlow, Mary prácticamente dejó el clan y se encerró en su cabaña. De hecho, no tengo idea de cómo logró persuadir a otros para participar, pero parece que lo logró. Juro que ni yo ni nadie más de mi clan estamos actuando en contra del almirante.\nHemos perdido demasiados hombres recientemente, así que no queremos meternos en ningún asunto complicado ahora. No tengo miedo del ataque del almirante, incluso unido con los Rivados. Los Narvales son verdaderos guerreros y lo demostraremos en nuestra última batalla. Pero esto sería inútil.\nYa hemos decidido mantener la paz con el almirante. Los Rivados son otro asunto, no negociamos con Negros. Estoy dispuesto a disculparme personalmente con el almirante, a pedir perdón por mis sospechas causadas por la muerte de Milrow y por el ataque a su vida. Juraré sobre la Biblia para probar mi sinceridad. ¿Tú y Dodson están de acuerdo con eso?";
		link.l1 = "Lo estamos. ¿Estás seguro de que no hay trucos de tus hombres que debamos esperar?";
		link.l1.go = "shark_14";
		break;

	case "shark_14":
		dialog.text = "Absolutamente. Informaré a mi clan sobre el verdadero asesino de Alan Milrow. La relación de mis hombres con el almirante cambiará inmediatamente, te lo aseguro. Dime, ¿será necesaria una matanza después de eso?";
		link.l1 = "No, no lo hará. Estoy aquí para prevenirlo. Confío en ti, Donald, e intentaré persuadir a Shark. Me quedan algunos argumentos... ¡Nos vemos, Donald!";
		link.l1.go = "shark_15";
		break;

	case "shark_15":
		DialogExit();
		sld = characterFromId("Dodson");
		sld.dialog.currentnode = "narval"; // ноду Акуле
		AddQuestRecord("SharkHunt", "26");
		NextDiag.CurrentNode = "narval_wait";
		break;

	case "narval_wait":
		dialog.text = "¿Ya has hablado con el almirante? ¿Algún resultado?";
		link.l1 = "Estoy en proceso. Te veré más tarde...";
		link.l1.go = "exit";
		NextDiag.TempNode = "narval_wait";
		break;

	case "shark_16":
		dialog.text = "¿Ya has hablado con el almirante? ¿Algún resultado?";
		link.l1 = "Sí, lo he hecho. Tus disculpas son aceptadas, la acusación de tu clan queda anulada. Hay incluso más, Shark te ofrece venir a verle para discutir los términos del futuro acuerdo pacífico entre Narvales y piratas.";
		link.l1.go = "shark_17";
		break;

	case "shark_17":
		dialog.text = "Para ser honesto, no esperaba... Esto es una gran noticia. Tal vez incluso podamos reconsiderar los precios de las provisiones para nuestro clan y una nueva política respecto a los Rivados.";
		link.l1 = "Eso concierne solo a ti y al almirante.";
		link.l1.go = "shark_18";
		break;

	case "shark_18":
		dialog.text = "Sí, por supuesto. Has prestado un gran servicio al clan de los Narvales al prevenir el derramamiento de sangre inútil y quizás incluso la aniquilación total de mis hombres. Toma este mosquete de torre como muestra de mi gratitud, no encontrarás otra arma de este tipo\nAdemás, puedes visitar nuestras áreas restringidas como cualquier miembro del clan.";
		link.l1 = "¡Gracias! Por ahora, adiós, tengo muchas cosas que hacer.";
		link.l1.go = "shark_19";
		break;

	case "shark_19":
		GiveItem2Character(pchar, "mushket6");
		Log_Info("Has recibido un mosquete de torre");
		PlaySound("interface\important_item.wav");
		dialog.text = "Buena suerte. Ven a verme si tienes alguna pregunta.";
		link.l1 = "Entendido. ¡Nos vemos!";
		link.l1.go = "exit";
		CloseQuestHeader("SharkHunt");
		bDisableFastReload = false;				 // belamour legendary edition
		pchar.questTemp.LSC.nrv_friend = "true"; // флаг на проход по кораблям нарвалов
		NextDiag.TempNode = "grinspy_wait";
		for (i = 1; i <= 6; i++)
		{
			sld = CharacterFromID("NarvalSold_" + i);
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
		}
		for (i = 1; i <= 3; i++)
		{
			sld = CharacterFromID("NarvalProt_" + i);
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
		}
		AddSimpleRumourCityTip("Dicen que eres amigo de Donald, Greenspen, el líder de los Narvales. Bueno, los Rivados te odian ahora...", "LostShipsCity", 5, 2, "LSC", "");
		AddSimpleRumourCityTip("Dicen que ahora eres Narval. ¿O sirves bajo el mando del Almirante? No lo entiendo...", "LostShipsCity", 5, 2, "LSC", "");
		AddSimpleRumourCityTip("He oído que ha hecho la paz entre el almirante y los narvales. Hm, Rivados debe estar loco por eso...", "LostShipsCity", 5, 2, "LSC", "");
		AddSimpleRumourCityTip("¡Así que Chad Kapper fue el asesino de Alan Milrow! ¡Eso es sorprendente!", "LostShipsCity", 5, 2, "LSC", "");
		break;

	case "grinspy_wait": // стал другом
		if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
		{
			dialog.text = "¡Eh! " + GetFullName(pchar) + "¡Tú eres... no, es imposible! ¿Estás vivo?!";
			link.l1 = "¡Los rumores sobre mi muerte eran un poco erróneos, Donald. ¡Ja-ja, me alegra verte!";
			link.l1.go = "exit";
			npchar.quest.return_isl = "true";
			break;
		}
		dialog.text = "A-ah, mi amigo " + GetFullName(pchar) + ". ¿Necesitas algo?";
		link.l1 = "No, no lo hago. Solo quería saludarte.";
		link.l1.go = "exit";
		NextDiag.TempNode = "grinspy_wait";
		break;

	case "negotiations":
		dialog.text = "¿Qué asunto tienes para mí?";
		link.l1 = "Una muy desagradable, Donald. Se atentó contra la vida de Steven. Luchadores de tu clan participaron.";
		link.l1.go = "negotiations_1";
		break;

	case "negotiations_1":
		dialog.text = "No sé nada de eso. ¿Por qué crees que mis hombres estuvieron involucrados?";
		link.l1 = "Porque personalmente maté a algunos de ellos junto con Chad Kapper, el contramaestre del almirante que es responsable de todo este lío. No pudo hacerlo solo, así que tus hombres le ayudaron mucho. El almirante lo sabe y está muy, muy enfadado.";
		link.l1.go = "negotiations_2";
		break;

	case "negotiations_2":
		dialog.text = "¿Mis hombres? ¿Quiénes exactamente, puedes nombrarlos?";
		link.l1 = "No se presentaron. Solo estaban disparando y esgrimiendo. Tu gente es imprudente. Pueden atacar incluso a uno de los suyos. ¡Al diablo conmigo o con el almirante, ¿pero intentar matar a la chica?";
		link.l1.go = "negotiations_3";
		break;

	case "negotiations_3":
		dialog.text = "Mm. ¿De quién estás hablando?";
		if (pchar.questTemp.LSC.Mary == "alive")
		{
			link.l1 = "¿De quién estoy hablando? Estoy hablando del ataque a Mary la Roja. Dos Narvales intentaron matarla. Llegué a su camarote en un momento crítico por pura casualidad. La habrían matado si llegaba más tarde. No les pregunté sus nombres, lo siento, no tuve tiempo de hablar con ellos, pero Mary dijo que eran Narvales.";
			link.l1.go = "negotiations_4";
		}
		else
		{
			link.l1 = "¿De quién estoy hablando? Estoy hablando del ataque a Mary la Roja y esos dos Narvales que la mataron."
			link.l1.go = "negotiations_6";
		}
		break;

	case "negotiations_4":
		dialog.text = "¿Qué? ¡¿Por qué no me lo dijo?! ¡Habría actuado de inmediato!";
		link.l1 = "Recientemente tenía miedo incluso de salir de su camarote. Discutió contigo no hace mucho, así que ¿por qué debería correr hacia ti y pedirte ayuda?";
		link.l1.go = "negotiations_5";
		break;

	case "negotiations_5":
		dialog.text = "¡No tuve una discusión con ella! ¡Me exigió lo imposible, tuvimos una charla dura y la mandé lejos! Pero eso no significa que yo...";
		link.l1 = "Está bien, lo que sea. Después de todo, todos los problemas están resueltos ahora. Pero hay bastardos entre tus hombres, eso es un hecho.";
		link.l1.go = "negotiations_7";
		break;

	case "negotiations_6":
		dialog.text = "¿Qué? ¿Fue asesinada por los Narvales? ¿Por qué?";
		link.l1 = "Por orden de Chad Kapper, Donald. Sabía demasiado y no quería ayudar a Chad. ¡Y ahora la pobre chica está muerta!";
		link.l1.go = "negotiations_7";
		break;

	case "negotiations_7":
		dialog.text = "¡Lo juro, no lo sabía!";
		link.l1 = "Claro, no lo hiciste... Pero hablemos del almirante. Chad Kapper organizó el intento y tus hombres lo ayudaron. Intentaron envenenar a Dodson y apenas lo impedí.";
		link.l1.go = "negotiations_8";
		break;

	case "negotiations_8":
		dialog.text = "No ordené nada parecido. Dodson es consciente de que no apoyo la política del difunto Alan y creo que un compromiso austero es mejor que un pleito engorroso.";
		link.l1 = "Tendrás que asegurar al almirante en ello y no será fácil. Dodson está muy enfadado con todos los Narvales después del intento. Va a declararte la guerra.";
		link.l1.go = "negotiations_9";
		break;

	case "negotiations_9":
		dialog.text = "Espero que ese almirante entienda sus acciones. ¿Acaso duda que mis hombres puedan devolver el fuego?";
		link.l1 = "Lo hace. Piensa que tu clan es un grupo de bandidos y que debe ser destruido antes de que empiecen a matar a todos. Además, tenemos fuertes conexiones con los Rivados. Puedo simplemente hablar con Eddie el Negro y ofrecerle una alianza. No podrás enfrentarte a todos nosotros.";
		link.l1.go = "negotiations_10";
		break;

	case "negotiations_10":
		if (pchar.questTemp.LSC.Mary == "alive")
			sTemp = "Llama a Red Mary si no me crees y pregúntale. Ella se lo confirmará.";
		else
			sTemp = "Tengo una carta de Chad a Mary que lo prueba todo.";
		dialog.text = "¡Maldita sea! ¿Por qué todo el clan tiene que pagar por las acciones de unos pocos idiotas? No pienses que tengo miedo. Somos guerreros y lo demostraremos incluso en nuestra última batalla. Pero quiero justicia. De hecho, el almirante es responsable de matar a Alan Milrow en la prisión.";
		link.l1 = "¿Cómo puedes ser el líder, Donald...? No sabes ni de Mary ni de Alan. Chad Kapper lo mató." + sTemp + " Lo hizo para hacer que los Narvales fueran hostiles hacia el almirante y arrastrar a algunos de ellos a su lado.";
		link.l1.go = "negotiations_11";
		break;

	case "negotiations_11":
		dialog.text = "Ya veo. Está bien. Hablemos de otra manera. Estás aquí por algún propósito, ¿verdad? ¿Qué deseas?";
		link.l1 = "No quiero un maldito desastre en la Isla. No quiero que la gente muera. No me gusta la idea de eliminar a todos los Narvales, aunque te aseguro que los Rivados y nosotros somos capaces de hacerlo. También creo que todo el clan no debe responder por las acciones de algunos bastardos...";
		link.l1.go = "negotiations_12";
		break;

	case "negotiations_12":
		dialog.text = "";
		link.l1 = "Pero mi voto no será suficiente - deberías asegurar oficialmente al almirante que el intento no fue aprobado por ti y que tu clan no planea matar a Dodson.";
		link.l1.go = "negotiations_13";
		break;

	case "negotiations_13":
		dialog.text = "¿Qué puedo hacer? Estoy listo para disculparme por el intento y por mis sospechas sobre la muerte de Marlow. Puedo asegurarle que los Narvales no planean nada contra él y juraré sobre la sagrada Biblia. ¿Lo encontrarán suficiente tú y Dodson?";
		link.l1 = "Lo haré. Estoy seguro de que también funcionará para Dodson si lo visitas personalmente. Pero primero, le hablaré de tus intenciones y luego te visitaré de nuevo con los resultados.";
		link.l1.go = "negotiations_14";
		break;

	case "negotiations_14":
		dialog.text = "Está bien. Esperaré.";
		link.l1 = "Volveré pronto...";
		link.l1.go = "negotiations_15";
		break;

	case "negotiations_15":
		DialogExit();
		sld = characterFromId("Dodson");
		sld.dialog.currentnode = "peace"; // ноду Акуле
		sld = characterFromId("Dexter");
		sld.dialog.currentnode = "First time";
		LAi_SetStayTypeNoGroup(sld);
		ChangeCharacterAddressGroup(sld, "SanAugustineResidence", "goto", "goto11");
		AddQuestRecord("SharkHunt", "56");
		NextDiag.CurrentNode = "narval_wait";
		break;

	case "negotiations_17":
		dialog.text = "¿Has hablado ya con el almirante? ¿Algún resultado?";
		link.l1 = "Sí, lo he hecho. Si le haces una visita oficial, entonces el problema está resuelto.";
		link.l1.go = "negotiations_18";
		break;

	case "negotiations_18":
		dialog.text = "Para ser honesto, no esperaba... Esta es una gran noticia.";
		link.l1 = "Sí, sabes, yo también me alegro.";
		link.l1.go = "negotiations_19";
		break;

	case "negotiations_19":
		dialog.text = "Has hecho un gran servicio al clan Narval al prevenir una masacre sin sentido y, quizás, incluso el exterminio total de mi gente. Te concedo este mosquete de torre: no encontrarás otra arma como esta. También se te permite visitar nuestros barcos sin ninguna limitación.";
		if (pchar.questTemp.LSC.Mary == "alive")
		{
			link.l1 = "Gracias. Un regalo muy valioso. Sí, Donald, una cosa más: haz las paces con María la Roja. Es de temperamento ardiente, pero también es sincera y honesta. Discutir contigo la hizo apartarse del clan y casi le costó la vida.";
			link.l1.go = "negotiations_20";
		}
		else
		{
			link.l1 = "Gracias. Un regalo muy valioso. Y estoy realmente contento de que haya terminado tan bien.";
			link.l1.go = "negotiations_21";
		}
		break;

	case "negotiations_20":
		dialog.text = "Dile que le pido que me perdone por haberla lastimado y por esos dos canallas que se atrevieron a atacarla. Ustedes dos son... amigos, ¿verdad?";
		link.l1 = "Tienes razón, Donald. Se lo diré. Y realmente me alegra que todo haya terminado tan bien.";
		link.l1.go = "negotiations_21";
		break;

	case "negotiations_21":
		GiveItem2Character(pchar, "mushket6");
		Log_Info("Has recibido un mosquete de torre");
		PlaySound("interface\important_item.wav");
		dialog.text = "Buena suerte. Ven a verme si tienes alguna pregunta.";
		link.l1 = "Está bien. ¡Adiós!";
		link.l1.go = "exit";
		CloseQuestHeader("SharkHunt");
		bDisableFastReload = false;				 // belamour legendary edition
		pchar.questTemp.LSC.nrv_friend = "true"; // флаг на проход по кораблям нарвалов
		NextDiag.TempNode = "grinspy_wait";
		sld = characterFromId("Mary");
		sld.quest.donald = "true";
		LocatorReloadEnterDisable("CeresSmithy", "reload3", false);
		LocatorReloadEnterDisable("CeresSmithy", "reload4", false); // открываем Церес изнутри
		for (i = 1; i <= 6; i++)
		{
			sld = CharacterFromID("NarvalSold_" + i);
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
		}
		for (i = 1; i <= 3; i++)
		{
			sld = CharacterFromID("NarvalProt_" + i);
			LAi_SetWarriorType(sld);
			LAi_warrior_SetStay(sld, true);
		}
		// здесь почищу весь хлам, который накопился
		DeleteAttribute(pchar, "questTemp.LSC.Donald_enter"); // атрибут гардов
		DeleteAttribute(pchar, "questTemp.LSC.Florentina");
		DeleteAttribute(pchar, "questTemp.LSC.Dodson_poison");
		DeleteAttribute(pchar, "questTemp.LSC.Dodson_warning");
		DeleteAttribute(pchar, "questTemp.LSC.Whiskey_clear");
		DeleteAttribute(pchar, "questTemp.LSC.CapperDie_Aeva");
		AddSimpleRumourCityTip("Dicen que eres amigo de Donald, Greenspen, el líder de los Narvales. Bueno, los Rivados te odian ahora...", "LostShipsCity", 5, 2, "LSC", "");
		AddSimpleRumourCityTip("Dicen que ahora eres Narval. ¿O sirves bajo el mando del Almirante? No lo entiendo...", "LostShipsCity", 5, 2, "LSC", "");
		AddSimpleRumourCityTip("He oído que ha hecho la paz entre el almirante y los narvales. Hm, Rivados debe estar loco por eso...", "LostShipsCity", 5, 2, "LSC", "");
		AddSimpleRumourCityTip("¡Así que Chad Kapper fue el asesino de Alan Milrow! ¡Eso es sorprendente!", "LostShipsCity", 5, 2, "LSC", "");
		AddSimpleRumourCityTip("Cuida de Red Mary porque tienes suerte de estar con ella, ¡es tan temeraria! Siempre se mete en problemas...", "LostShipsCity", 20, 5, "LSC", "");
		break;
		//----------------------------------------- специальные реакции -----------------------------------------------
		// обнаружение ГГ в сундуках
	case "Man_FackYou":
		dialog.text = LinkRandPhrase("¿Qué estás haciendo ahí, eh? ¡Ladrón!", "¡Solo mira eso! Tan pronto como me perdí en la contemplación, ¡decidiste revisar mi cofre!", "¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!");
		link.l1 = "¡Mierda!";
		link.l1.go = "fight";
		break;

	case "Woman_FackYou":
		dialog.text = "¿Qué?! ¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!";
		link.l1 = "¡Chica insensata!";
		link.l1.go = "exit_setOwner";
		LAi_group_Attack(NPChar, Pchar);
		break;

	case "fight":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetOwnerTypeNoGroup(npchar);
		LAi_group_Attack(NPChar, Pchar);
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "exit_setOwner":
		LAi_SetOwnerTypeNoGroup(npchar);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	// замечание по обнажённому оружию
	case "LSCNotBlade":
		dialog.text = LinkRandPhrase("Escucha, será mejor que guardes tu arma. Me pone nervioso.", "Sabes, correr con cuchilla no se tolera aquí. Guárdala.", "Escucha, no juegues a ser un caballero medieval corriendo con una espada por ahí. Guárdala, no te queda bien...");
		link.l1 = LinkRandPhrase("Bien.", "Claro.", "Como dices...");
		link.l1.go = "exit";
		NextDiag.TempNode = "First Time";
		break;

	case "CitizenNotBlade":
		if (loadedLocation.type == "town")
		{
			dialog.text = NPCharSexPhrase(NPChar, "Escucha, soy ciudadano de la ciudad y te pediría que mantengas tu espada guardada.", "Escucha, soy ciudadano de la ciudad y te pediría que guardes tu espada.");
			link.l1 = LinkRandPhrase("Bien.", "Seguro.", "Como digas...");
		}
		else
		{
			dialog.text = NPCharSexPhrase(NPChar, "Ten cuidado, camarada, al correr con un arma. Puedo ponerme nervioso...", "No me gusta cuando los hombres caminan frente a mí con sus armas listas. Me asusta...");
			link.l1 = RandPhraseSimple("Entendido.", "Me lo llevo.");
		}
		link.l1.go = "exit";
		NextDiag.TempNode = "First Time";
		break;
		// <-- специальные реакции

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
