// Глэдис МакАртур - приемная мать Элен
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
	case "First time":
		if (pchar.questTemp.Saga == "helena1")
		{
			dialog.text = "¡Ah, Capitán! Sabes, le he contado todo a Helen. ¡No puedes imaginar qué peso me he quitado de encima!";
			link.l1 = "Has hecho todo bien, señorita McArthur. La chica necesita saber la verdad. Y estoy aquí por ella.";
			link.l1.go = "Helena_hire";
		}
		else
		{
			dialog.text = "Saludos, " + pchar.name + "¡Me alegra verte! ¿Quieres un poco de ron?";
			link.l1 = "Gracias, señorita McArthur, pero estoy demasiado ocupado ahora mismo.";
			link.l1.go = "exit";
		}
		NextDiag.TempNode = "First time";
		break;

	case "FindHelena":
		dialog.text = "¿Qué quiere, señor?";
		link.l1 = "¿Eres Gladys McArthur?";
		link.l1.go = "FindHelena_1";
		break;

	case "FindHelena_1":
		dialog.text = "Lo soy. No te recuerdo, joven. ¿Te importaría explicar qué quieres de mí?";
		link.l1 = "Me interesa la historia de la desaparición de su hija, señorita McArthur. ¿Qué le hizo pensar que ella desapareció? He oído que Helen tenía una tripulación muy hábil...";
		link.l1.go = "FindHelena_2";
		break;

	case "FindHelena_2":
		dialog.text = "¡Ah, estoy absolutamente segura! Mira, el aniversario de la muerte de mi difunto esposo fue hace cinco días. Helen adoraba a su padre y nunca se perdería esta fecha. Sólo se había ido por unos días para recibir un cargamento de madera roja de los amistosos Miskitos.\nLos indios respetan y temen a nuestro patrón Jan Svenson, nunca le harían daño. El señor Svenson ya ha hablado con ellos. La madera fue cargada el mismo día. Nadie ha visto a Helen desde entonces.";
		link.l1 = "¿Acaso los piratas la atacaron?";
		link.l1.go = "FindHelena_3";
		break;

	case "FindHelena_3":
		dialog.text = "¡Tonterías! Ya debes saber que el señor Svenson es uno de los cinco barones piratas y miembro del consejo de los Hermanos de la Costa. Ningún pirata puede cazar aquí sin su permiso. Aunque podría ser un novato...";
		link.l1 = "¿Y qué pasa con los españoles? ¿Podría haberse enfrentado a una patrulla española?";
		link.l1.go = "FindHelena_4";
		break;

	case "FindHelena_4":
		dialog.text = "No soy bueno con la política, pero dicen que las minas de oro y plata locales están completamente agotadas, no quedan muchos tesoros para arriesgar la vida de nobles hidalgos por ellos. Así que son huéspedes raros aquí. Además, los indígenas son hostiles hacia ellos.\nUn encuentro fortuito con una patrulla española no podría haber terminado mal para Helen, ella no hizo nada ilegal desde su punto de vista. 'Arcoíris' estaba bajo bandera holandesa y todos los papeles de Helen estaban en orden, incluyendo una licencia de comercio.";
		link.l1 = "¿Sucedió algo especial antes de su último viaje? ¿Quizás algún evento extraño que hayas pasado por alto?";
		link.l1.go = "FindHelena_5";
		break;

	case "FindHelena_5":
		dialog.text = "¡Ah, no! Gracias a Dios, llevamos vidas tranquilas aquí. Sin embargo, hace unas semanas Helen recibió una carta de otro admirador no deseado suplicando una cita. Es una chica bonita, pero no rica.\nAsí que tiene un montón de admiradores, aunque a ella no le gusta ninguno y no quiere casarse. Ya ha engañado a mucha gente de esta manera. ¡Tan frívola, igual que su madre!";
		link.l1 = "No parece ser ese tipo de mujer, señorita McArthur...";
		link.l1.go = "FindHelena_6";
		break;

	case "FindHelena_6":
		dialog.text = "¿Qué? Ah, lo que sea, estoy desolado. ¿Qué estaba diciendo? Ah, sí, la carta. De todos modos, esa carta fue escrita por Jimmy Higgins. Es uno de los hombres de Jackman y vive en Maroon Town. Visita nuestro pueblo bastante a menudo. Jackman también es un barón pirata, pero al señor Svenson no le gusta, no sé por qué.";
		link.l1 = "¿Y Helen?";
		link.l1.go = "FindHelena_7";
		break;

	case "FindHelena_7":
		dialog.text = "Oh, ella se reía a carcajadas. Había recibido una propuesta del capitán de una corbeta inglesa un día antes y rechazó incluso a él. ¿Y ahora este simple contramaestre de una vieja bañera pirata...? ¡Ni pensarlo, la hija de Sean McArthur exige un esposo más imponente!";
		link.l1 = "¿Y cómo se llamaba ese capitán inglés?";
		link.l1.go = "FindHelena_8";
		break;

	case "FindHelena_8":
		dialog.text = "Oh, ¿cómo lo sabría yo? Los caballeros de verdad son raros invitados aquí. Lo siento, no quería ofenderte. Pregunta a ese Higgins. Debe recordar su nombre. Jimmy intentaba batirse en duelo con ese capitán por Helen. Sus compañeros apenas lograron detenerlo. Pero ambos dejaron Blueveld unos días antes de que Helen zarpara.";
		link.l1 = "Bueno, gracias por tu historia. Intentaré encontrar a tu ser querido. Si aprendo algo, te lo diré a ti o al señor Svenson. Espero encontrar a tu hija viva y en una pieza.";
		link.l1.go = "FindHelena_9";
		break;

	case "FindHelena_9":
		dialog.text = "¿Vas a buscarla? ¡Que Dios te acompañe, te guíe y fortalezca tu mano! ¡Estaré rezando por ti! Dime tu nombre, honorable hombre.";
		link.l1 = "" + pchar.name + ". " + GetFullName(pchar) + "Espero regresar con buenas noticias pronto, señorita McArthur. ¡Adiós!";
		link.l1.go = "FindHelena_10";
		break;

	case "FindHelena_10":
		DialogExit();
		NextDiag.CurrentNode = "FindHelena_wait";
		AddQuestRecord("Saga", "1");
		pchar.questTemp.Saga = "maruntown"; // идем к Джекману
		SetFunctionTimerCondition("Gladis_SetHome", 0, 0, 1, false);
		int iTime = 25 - MOD_SKILL_ENEMY_RATE;
		if (bImCasual)
		{
			NewGameTip("Modo exploración: se duplica la duración de las misiones");
			SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime * 2, false);
		}
		else
			SetFunctionTimerCondition("Helena_AntiguaOver", 0, 0, iTime, false);
		break;

	case "FindHelena_wait":
		dialog.text = "¿Tienes alguna nueva información sobre mi pobre hija, " + pchar.name + "?";
		link.l1 = "Lo siento, señorita McArthur, no tengo nada nuevo que contarle hasta ahora, pero no se desespere. Continuaré mi búsqueda. La falta de malas noticias también son buenas noticias en sí mismas.";
		link.l1.go = "exit";
		NextDiag.TempNode = "FindHelena_wait";
		break;

	case "Helena_die":
		dialog.text = "Eras demasiado tarde, Capitán. El cuerpo de mi pobre hija fue encontrado en las costas de Antigua. ¡Señor, cómo la torturaron antes de su muerte! He fallado en preservar a mi hermosa niña...";
		link.l1 = "Lo siento. No había nada que pudiera hacer...";
		link.l1.go = "exit";
		NextDiag.TempNode = "Gladis_exit";
		break;

	case "Gladis_exit":
		dialog.text = "Ah, joven, por favor, déjame solo con mi pena...";
		link.l1 = "...";
		link.l1.go = "exit";
		NextDiag.TempNode = "Gladis_exit";
		break;

	case "Gladis_regard":
		dialog.text = "No sé ni cómo agradecerle, Capitán, por salvar a mi hija. Ella me lo ha contado todo y admiro su valentía y honor. Aquí, tome estos doblones de oro. No es mucho, pero se los ofrezco con toda sinceridad. ¡Y ni se le ocurra rechazarlos!";
		link.l1 = "Está bien, Gladys, no lo haré. Pero he salvado a tu hija no por monedas y espero que lo sepas.";
		link.l1.go = "Gladis_regard_1";
		link.l2 = "Mantén este dinero para ti, Gladys. Lo necesitas más que yo.";
		link.l2.go = "Gladis_regard_2";
		sld = characterFromId("Helena");
		LAi_SetStayType(sld);
		AddCharacterExpToSkill(pchar, "Leadership", 50);
		// открыть город
		LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", false);
		LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", false);
		LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", false);
		break;

	case "Gladis_regard_1":
		TakeNItems(pchar, "gold_dublon", 100);
		dialog.text = "Me alegra haber podido de alguna manera recompensarte por tu honorable acto. Las puertas de mi hogar siempre están abiertas para ti. Helen y yo estaremos encantados de verte en cualquier momento.";
		link.l1 = "Gracias, señorita McArthur. Os visitaré a vos y a Helen cuando haya oportunidad.";
		link.l1.go = "exit";
		NextDiag.TempNode = "Gladis_wait";
		break;

	case "Gladis_regard_2":
		dialog.text = "Ah, por favor... Solo quería recompensarte por tu honorable acto. Sabe que las puertas de mi hogar siempre estarán abiertas para ti. Helen y yo estaremos encantados de verte en cualquier momento.";
		link.l1 = "Gracias, Señorita McArthur. Os visitaré a usted y a Helen cuando haya una oportunidad.";
		link.l1.go = "exit";
		NextDiag.TempNode = "Gladis_wait";
		pchar.questTemp.Saga.Helena_friend = "true"; // атрибут поведения Элен в будущем
		break;

	case "Gladis_wait":
		if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Gladys"))
		{
			dialog.text = "¡Capitán, siempre es bienvenido en nuestro hogar! ¿Ha venido por Helen? Me temo que se encerró en su habitación, debe estar agotada por los últimos días. No se preocupe, a veces le sucede.";
			link.l1 = "¿De verdad? ¿Estás seguro, ella está bien?";
			link.l1.go = "after_drinking";

			DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Gladys");
			break;
		}

		dialog.text = "¡Ah, Monsieur de Maure! Siempre me alegra ver al salvador de mi hija en mi casa. ¿Deseas ver a Helen? Ella está arriba en su habitación. Después de la pérdida del 'Arcoíris' y su maravilloso rescate, evita salir. Es la primera vez que la veo en tal estado de confusión...";
		link.l1 = "Gracias, señorita McArthur.";
		link.l1.go = "exit";
		NextDiag.TempNode = "Gladis_wait";
		break;

	case "Gladis_history":
		dialog.text = "¡Ah, Monsieur de Maure! Siempre me alegra ver al salvador de mi hija en mi casa. ¿Quieres ver a Helen?";
		link.l1 = "No. Quiero hacerte unas preguntas y realmente confío en tu sinceridad. La seguridad de Helen depende de ello. ¿Te resulta familiar este anillo?";
		link.l1.go = "Gladis_history_1";
		break;

	case "Gladis_history_1":
		RemoveItems(pchar, "bucher_ring", 1);
		PlaySound("interface\important_item.wav");
		dialog.text = "¡Santo cielo! ¡Este es... el anillo de su padre!";
		link.l1 = "¿Del señor McArthur?";
		link.l1.go = "Gladis_history_2";
		break;

	case "Gladis_history_2":
		dialog.text = "No. Helen es nuestra hijastra, pero ella no lo sabe, sus padres murieron así que he decidido tomarla como mi hija. Sean la adoptó, pero ni siquiera él sabía que no es mi hija.";
		link.l1 = "¿Quiénes son sus verdaderos padres?";
		link.l1.go = "Gladis_history_3";
		break;

	case "Gladis_history_3":
		dialog.text = "Yo sé que su padre era un pirata llamado 'Butcher' en la fragata 'Neptune'. Solo lo vi dos veces. Y su madre era una joven hermosa, pelo rojo, vestida con ropa de hombre. Eso es prácticamente todo lo que puedo decirte sobre ella, excepto que fue una mala madre.\nNunca dejaría a un bebé así en manos de extraños. Ambos murieron trágicamente. Y el mensajero prometido se ha mostrado veinte años después y resultó ser tú. ¿Te envió Butcher? ¿Está vivo?";
		link.l1 = "¡Cálmate, señorita Gladys! No hay razones para sospechar que Butcher ha revivido, aunque usted es la segunda persona que ha tenido esta idea. Recientemente me encontré con un hombre que se suponía debía mostrarle este anillo...";
		link.l1.go = "Gladis_history_4";
		break;

	case "Gladis_history_4":
		dialog.text = "";
		link.l1 = "Un simple incidente le había impedido hacerlo a tiempo y estaba sufriendo toda su vida porque había fallado la última orden de su capitán. Murió no hace mucho y... bueno, ya basta de noticias tristes. Dime, Gladys, ¿acaso la madre de Helen no dejó ningún recuerdo a su hija en su memoria? ¿Alguna cosilla tal vez?";
		link.l1.go = "Gladis_history_5";
		break;

	case "Gladis_history_5":
		dialog.text = "Me dejó un extraño pedazo de un mapa viejo. Bromeó diciendo que era su legado. ¿De qué puede servir ese pedazo de papel? Creo que solo fue una mala broma. Estaba demasiado excitada y un poco fuera de sí. Pero conservé este 'regalo'.\nQuién sabe... Si quieres, puedo dártelo si prometes contarme toda la historia algún día.";
		link.l1 = "Absolutamente, señorita McArthur. Me llevaré este trozo conmigo por un tiempo. Necesito hablar con el señor Svenson.";
		link.l1.go = "Gladis_history_6";
		break;

	case "Gladis_history_6":
		GiveItem2Character(pchar, "map_half_beatriss"); // половинка карты
		PlaySound("interface\important_item.wav");
		dialog.text = "¡Nos has ayudado de nuevo, Monsieur de Maure! Y no tengo ni idea de cómo agradecerte. Toma la pistola de mi marido, al menos. Siempre estuvo orgulloso de ella y me decía que es muy rara. Ha estado aquí tirada mucho tiempo. ¡Que te sirva a ti! ¡Tómala, tómala!";
		link.l1 = "Gracias, Gladys. Esta pistola es realmente excelente. Gracias y adiós.";
		link.l1.go = "Gladis_history_7";
		if (CheckCharacterItem(pchar, "chest"))
		{
			link.l2 = "Que esta pistola sirva a Helen. Ya tengo suficiente armamento.";
			link.l2.go = "Gladis_history_8_1";
		}
		break;

	case "Gladis_history_7":
		DialogExit();
		PlaySound("interface\important_item.wav");
		GiveItem2Character(pchar, "pistol5");
		pchar.questTemp.Saga = "svenson2";
		NextDiag.CurrentNode = "First time";
		DeleteAttribute(pchar, "questTemp.Saga.Helena_friend");
		AddQuestRecord("Saga", "22");
		AddCharacterExpToSkill(pchar, "Leadership", 50);
		break;

	case "Gladis_history_8_1":
		dialog.text = "¿Pero por qué sigues rechazando mis regalos? Me haces enfadar...";
		link.l1 = "Creo que ahora podré hacerte feliz. Voy a devolver el oro que el mensajero debía entregarte por el digno cuidado de la hija del capitán Butcher. Claro, estos doblones no pagarán todo tu amor y lealtad, pero te pertenecen de todas formas. Puedes hacer lo que quieras con ellos.";
		link.l1.go = "Gladis_history_8";
		break;

	case "Gladis_history_8":
		dialog.text = "¡Ah, Capitán! No sé qué decir... ¡No podía imaginar que tales... hombres honorables existieran! Ve a mi hija y dale las buenas nuevas.";
		link.l1 = "Estoy en camino, señorita McArthur.";
		link.l1.go = "Gladis_history_9";
		break;

	case "Gladis_history_9":
		DialogExit();
		RemoveItems(pchar, "chest", 1);
		pchar.questTemp.Saga = "svenson2";
		NextDiag.CurrentNode = "First time";
		AddQuestRecord("Saga", "22");
		sld = characterFromId("Helena");
		GiveItem2Character(sld, "pistol5");
		EquipCharacterbyItem(sld, "pistol5");
		ChangeCharacterComplexReputation(pchar, "nobility", 5);
		AddCharacterExpToSkill(pchar, "Leadership", 100);

		pchar.questTemp.Saga.HelenRelation = sti(pchar.questTemp.Saga.HelenRelation) + 1;
		break;

	case "Helena_hire":
		dialog.text = "¿Hablas en serio? ¿Qué quieres decir?";
		link.l1 = "Según la demanda del señor Svenson, voy a emplear a Helen en mi barco como oficial. Ella está en gran peligro. Helen necesitará una protección sólida mientras Jan y yo lidiamos con este asunto. Espero poder brindar tal protección.";
		link.l1.go = "Helena_hire_1";
		break;

	case "Helena_hire_1":
		dialog.text = "¡Ah, eso es tan bueno! No me atrevería a pedírtelo yo mismo. Será la mejor protección para mi chica. ¡Helen estará tan contenta de navegar de nuevo!";
		link.l1 = "Gracias por su cumplido, señorita McArthur. Y ahora tengo que ver a su... hijastra.";
		link.l1.go = "exit";
		LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false); // открыть спальню Элен
		sld = characterFromId("Helena");
		sld.dialog.currentnode = "Helena_hire";
		pchar.questTemp.Saga = "helena2";
		break;

	case "saw_sex":
		dialog.text = "¡Oh, Dios! ¡Mi niñita!";
		link.l1 = "¡Gladys, ¿no sabes llamar a la puerta?!";
		link.l1.go = "saw_sex_1";
		break;

	case "saw_sex_1":
		dialog.text = "¡Oh, perdonadme, jóvenes! ¡Me voy! Helen, recuerda lo que te dije!";
		link.l1 = "";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("HelenDrinking_AfterCaveGladysTalk");
		break;

	case "after_drinking":
		dialog.text = "Creo que esta vez simplemente se agotó de tanto trabajar. ¡Me lo contó todo, capitán! ¡Gracias por ayudarla a elegir un nuevo barco ayer!";
		link.l1 = "¿Eh? Hm, de nada. Adiós, señora MacArthur.";
		link.l1.go = "exit";

		NextDiag.TempNode = "Gladis_wait";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
