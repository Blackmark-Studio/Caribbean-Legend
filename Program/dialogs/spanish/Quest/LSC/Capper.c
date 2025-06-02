// Чад Каппер - боцман Акулы и тюремщик
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
		dialog.text = "¿Quieres algo?";
		link.l1 = "No, no es nada.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	// вариант R
	case "Chimiset":
		dialog.text = "Bueno, bueno... ¿Así que tú eres el misterioso ladrón? Hm... No pareces un miserable ratero.";
		link.l1 = "Escuche, señor, está equivocado. Soy un recién llegado aquí, así que ¿cómo podría saber que la bodega donde su gente me atrapó era su zona privada?";
		link.l1.go = "Chimiset_1";
		break;

	case "Chimiset_1":
		dialog.text = "¿En serio? Buen intento, amigo... ¿De dónde vienes entonces?";
		link.l1 = "Desde Tierra Firme... A través de una extraña estatua. Yo mismo no sé cómo explicar lo que ha sucedido.";
		link.l1.go = "Chimiset_2";
		break;

	case "Chimiset_2":
		dialog.text = "¿Estatua? ¡Ja-ja! Eres un chico gracioso, ¿verdad? ... Está bien, te lo explicaré yo mismo: nadaste por el agujero en el barco y querías colarte en nuestro almacén. ¿Cómo es que no reconozco tu cara? Conozco a todos los Rivados...";
		link.l1 = "¿Qué Rivados? ¡No sé de qué estás hablando! Escucha, llegué aquí hace aproximadamente una hora...";
		link.l1.go = "Chimiset_3";
		break;

	case "Chimiset_3":
		dialog.text = "No grites, no soy un idiota. Sí, he escuchado suficiente de tus gilipolleces sobre la estatua y lo encuentro bastante divertido. Lo encuentro jodidamente hilarante. ¿Qué tal si nos reímos juntos de eso? ¡Ja-ja-ja!... ¿Por qué no te estás riendo? Era una buena broma... Rivados. Pero las bromas se han acabado ahora. Te dejaré pudrirte en la cárcel, amigo.";
		link.l1 = "¡No soy de los Rivados! ¡Mi nombre es Charles de Maure!";
		link.l1.go = "Chimiset_4";
		break;

	case "Chimiset_4":
		dialog.text = "¿Primera vez, eh? Hm... quizá estés diciendo la verdad. Respóndeme, ¿eres uno de ellos?!";
		link.l1 = "Te juro que nunca he oído ese nombre antes, ¡no soy uno de ellos!";
		link.l1.go = "Chimiset_5";
		break;

	case "Chimiset_5":
		dialog.text = "¿De verdad? Bien. Demuéstralo. Baja las escaleras, hay un Rivados sentado en una jaula. Es un hechicero peligroso. Mátalo, solo entonces estaré convencido. También olvidaré tu intrusión ilegal en nuestro almacén.\nEntonces, ¿estás listo? No te asustes, el hechicero está desarmado y débil. Bueno, podría convertirte en polvo con algún hechizo, como el que te llevó al calabozo de San Agustín...";
		link.l1 = "Si hubieras visto ese hechizo en acción, no serías tan escéptico. Dudo que siquiera hubieras sobrevivido...";
		link.l1.go = "Chimiset_6";
		break;

	case "Chimiset_6":
		dialog.text = "¡Basta de hablar! ¿Vas a hacer esto o no? Si es así, toma este machete y acaba con el hechicero. De lo contrario, pasarás el resto de tu vida en una jaula. ¿Entendido?";
		link.l1 = "De dos males, elijo el menor. Dame el machete.";
		link.l1.go = "Chimiset_7";
		break;

	case "Chimiset_7":
		PlaySound("interface\important_item.wav");
		GiveItem2Character(pchar, "slave_02");
		EquipCharacterbyItem(pchar, "slave_02");
		dialog.text = "Buen chico. Tómalo, ve y mata al hombre negro. Su jaula está abierta. ¡No intentes nada estúpido ahora, no dudaremos en acabar contigo si siquiera lo piensas! ¡Ahora ve!";
		link.l1 = "¿Por qué? ¿Tienes miedo de que destripe a tus muchachos con este pedazo de basura metálica oxidada?";
		link.l1.go = "Chimiset_8";
		break;

	case "Chimiset_8":
		dialog.text = "Mi paciencia se está agotando. ¡Dirígete a la bodega de carga y haz lo que se te dice!";
		link.l1 = "Está bien, está bien, relájate. Me voy...";
		link.l1.go = "exit";
		NextDiag.TempNode = "Chimiset_9";
		LAi_SetPlayerType(pchar);
		bDisableCharacterMenu = false; // разлочим Ф2
		break;

	case "Chimiset_9":
		dialog.text = "¡Estás poniendo a prueba mi paciencia, bastardo! No querrás irritarme...";
		link.l1 = "Está bien, está bien, relájate.";
		link.l1.go = "exit";
		NextDiag.TempNode = "Chimiset_9";
		break;

	case "Fightfail_Final":
		dialog.text = "¿Has matado a ese brujo negro? Bien... Me alegra. Has demostrado que no eres de los Rivados.";
		link.l1 = "¿Cuándo me liberarán finalmente de esta maldita bañera? Necesito encontrarme con Shark de inmediato.";
		link.l1.go = "Fightfail_Final_1";
		break;

	case "Fightfail_Final_1":
		dialog.text = "Lo conocerás, seguro... ¡Lo encontrarás en el camino al infierno!";
		link.l1 = "¿Qué?!";
		link.l1.go = "Fightfail_Final_2";
		break;

	case "Fightfail_Final_2":
		DialogExit();
		DoQuestCheckDelay("LSC_ChadGuardAttack_Fail", 0.1);
		break;

	// вариант N
	case "prisoner":
		dialog.text = "¡Ja! Mira esto. ¿Qué haces aquí en mi prisión?";
		link.l1 = "Tu nombre es Chad Kapper, ¿verdad? Mi nombre es " + GetFullName(pchar) + "y estoy aquí en nombre de Shark Dodson. Él me dio las llaves.";
		link.l1.go = "prisoner_1";
		break;

	case "prisoner_1":
		dialog.text = "¿Del almirante? Hm, ya veo. ¿Eres su nuevo chico de los recados?";
		link.l1 = "Muestre algo de respeto, señor. No estoy sirviendo a nadie, ni al Shark ni a usted, y no voy a tolerar ese lenguaje.";
		link.l1.go = "prisoner_2";
		break;

	case "prisoner_2":
		dialog.text = "¡Ja, ja, me caes bien, amigo! Olvida lo que dije... Entonces, ¿qué te trae por aquí?";
		link.l1 = "Shark ha dado la orden de liberar a Chimiset, está encarcelado aquí.";
		link.l1.go = "prisoner_3";
		break;

	case "prisoner_3":
		dialog.text = "¿El hechicero de los Rivados? Hm. Eso es extraño, me sorprende mucho escuchar eso...";
		link.l1 = "Shark dio una orden. Quiere hacer las paces con los Rivados.";
		link.l1.go = "prisoner_4";
		break;

	case "prisoner_4":
		dialog.text = "Ah, veo ahora. Bien, enviaré a un hombre a los Rivados. Vendrán aquí y se llevarán a su bufón.";
		link.l1 = "¿Por qué no puedes simplemente dejarlo ir?";
		link.l1.go = "prisoner_5";
		break;

	case "prisoner_5":
		dialog.text = "Podría, pero esto sería demasiado peligroso para él. Chimiset es conocido por aquí, su vida no valdrá nada una vez que pise la 'Esmeralda', un territorio de sus enemigos, los Narvales. No hay otro camino desde el Tártaro, ¡no podemos dejar que el viejo nade alrededor de la isla!\nY si alguien lo mata, los Rivados nos culparán a nosotros, ¡específicamente a mí! Verás, no quiero problemas que se puedan evitar. Así que lo dejaré salir solo bajo la protección de los luchadores de su clan. Quizás, deseas hablar con Chimiset tú mismo. ¡Es un tipo divertido...";
		if (CheckAttribute(npchar, "quest.chimiset_talk"))
			link.l1 = "Ya he hablado con él, realmente es un hombre extraño. De todos modos, tengo que irme. ¡Nos vemos, Chad!";
		else
			link.l1 = "Eso es lo que pretendía. Iré a hablar con él.";
		link.l1.go = "prisoner_6";
		break;

	case "prisoner_6":
		DialogExit();
		sld = characterFromId("Chimiset");
		sld.quest.capper_talk = "true"; // разговор с Каппером состоялся
		if (!CheckAttribute(npchar, "quest.chimiset_talk"))
			chrDisableReloadToLocation = true; // закрыть локацию
		else
			chrDisableReloadToLocation = false; // открыть локацию
		NextDiag.CurrentNode = "prisoner_7";
		break;

	case "prisoner_7":
		dialog.text = "Enviaré un mensajero a los Rivados y ellos se llevarán a su hechicero. No te preocupes, camarada, puedes irte.";
		link.l1 = "Bien.";
		link.l1.go = "exit";
		NextDiag.TempNode = "prisoner_7";
		break;

	// вариант M
	case "Aeva_attack":
		dialog.text = "...ya debe haber abierto el barril, estoy seguro. Este es su whiskey favorito, maldito irlandés. Pronto se acabará, he puesto suficiente arsénico para matar a una manada...";
		link.l1 = "";
		link.l1.go = "Aeva_attack_1";
		CharacterTurnToLoc(npchar, "quest", "quest2");
		break;

	case "Aeva_attack_1":
		dialog.text = "¿Ah? ¡Maldita sea, qué haces aquí? ¡Lárgate!";
		link.l1 = "Te he estado buscando durante mucho tiempo... envenenador. Eso es extraño, no veo al Cíclope. Querías tomar la posición dShark, ¿verdad?";
		link.l1.go = "Aeva_attack_2";
		CharacterTurnByChr(npchar, pchar);
		break;

	case "Aeva_attack_2":
		dialog.text = "¡Ja, ja, Shark debe estar muerto ya! ¡Y tú lo seguirás pronto, espía!";
		link.l1 = "...";
		link.l1.go = "Aeva_attack_fight";
		break;

	case "Aeva_attack_fight":
		DialogExit();
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, "EnemyFight");
		for (i = 1; i <= 3; i++)
		{
			sld = CharacterFromID("ChadNarval_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "LSC_CapperDieAeva");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "Aeva_attack_2":
		dialog.text = "... esto va a ser una maldita bebida. Ese maldito irlandés ha estado soñando con este whisky durante mucho tiempo, así que se lo tragará todo en un segundo. ¿Dónde está el arsénico? Echa más, solo para estar seguro... Y luego nuestro amigo Fazio entregará este barril al almirante como un regalo de los Narvales, ¡ja-ja! ¿Tengo razón, querido Giuseppe? ¿Quieres vivir?\n¡Argh! ¡Mira, tenemos invitados! ¿Qué quieres, imbécil? ¡Lárgate antes de que te clavemos en el suelo!";
		link.l1 = "Tu plan ha fallado, Kapper. Estaba siguiendo tus pasos y sé lo que tú y tu compinche Cíclope van a hacer. ¡Tira el arsénico! ¡No envenenarás a Shark!";
		link.l1.go = "Aeva_attack_3";
		break;

	case "Aeva_attack_3":
		dialog.text = "¡Ah, sabueso! ¡Bueno, entonces tú mueres primero! ¡Muchachos, a las armas!";
		link.l1 = "...";
		link.l1.go = "Aeva_attack_fight";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
