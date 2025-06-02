// Jason общий диалог смотрителей кладбищ
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Cemetery\" + NPChar.City + "_cemetery.c ";
						 if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--

	int iTemp;
	string sTemp;
	bool ok;

	switch (Dialog.CurrentNode)
	{
	case "First time":
		if (LAi_grp_playeralarm > 0)
		{
			dialog.text = PCharRepPhrase(LinkRandPhrase("La ciudad está en alerta. Parece que es hora de que yo también tome las armas...", "¿No estás siendo perseguido por toda la guardia del pueblo?. ¡A mí, soldados!", "No encontrarás refugio aquí. ¡Pero encontrarás unas cuantas pulgadas de acero frío debajo de una costilla!"), LinkRandPhrase("¿Qué quieres, malandrín? Un guardia municipal ya ha tomado tu rastro, no escaparás muy lejos, " + GetSexPhrase("¡sucio pirata", "¡granuja") + "!", "¡Alto! " + GetSexPhrase("¡Asesino sucio! ¡Guardia!", "¡No tengo miedo de ti! Pronto estarás colgado en nuestro fuerte, no hay lugar donde esconderte...")));
			link.l1 = PCharRepPhrase(RandPhraseSimple("Parece que estás cansado de vivir...", "¿Y por qué no queréis vivir tranquilamente, ciudadanos..." + XI_ConvertString("Colony" + npchar.city + "Gen") + "?"), RandPhraseSimple("¡Vete al infierno!", "Te quedan unos pocos segundos en este mundo..."));
			link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
			break;
		}
		if (!CheckAttribute(pchar, "questTemp.Lantern"))
		{
			dialog.text = "¡A-a-ah! Ah, eres tú... ¿Quién eres? ¿Qué has venido a hacer al cementerio?";
			link.l1 = "Mi nombre es " + GetFullName(pchar) + "¿Y quién eres tú y qué estás haciendo aquí? ¿Y por qué estás tan asustado?";
			link.l1.go = "Lantern_01";
			npchar.quest.meeting = "1";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.Lantern") && pchar.questTemp.Lantern == "ToCrypt")
		{
			dialog.text = "Entonces, ¿cómo fue? ¿Lo comprobaste? ¿Me crees ahora?";
			link.l1 = "No, aún no he bajado a la cripta. Espera un poco más, lo revisaré todo.";
			link.l1.go = "exit";
			break;
		}

		if (CheckAttribute(pchar, "questTemp.Lantern") && pchar.questTemp.Lantern == "ToKeeper")
		{
			dialog.text = "¿Y bien? ¿Echaste un vistazo? ¿Lo viste?";
			link.l1 = "¡Sí, seguro que sí! ¡Tenías razón!";
			link.l1.go = "Lantern_10";
			link.l2 = "No era exactamente lo que pensabas.";
			link.l2.go = "Lantern_14";
			break;
		}
		if (npchar.quest.meeting == "0")
		{
			dialog.text = RandPhraseSimple("Hola, marinero! Mi nombre es " + GetFullName(npchar) + ", y soy la única alma viviente aquí. En realidad, todos vamos a morir, ja-ja-ja! ¿Por qué has venido?", "¡Hola! No he visto a un hombre vivo durante mucho tiempo... Permíteme presentarme, " + GetFullName(npchar) + ", y este cementerio es mi último refugio. Aparentemente, seré enterrado aquí. ¿Cómo puedo ayudarte?");
			link.l1 = "Hola, " + npchar.name + "¡ Mi nombre es " + GetFullName(pchar) + ", y soy un capitán. Caminé a través de la selva y llegué aquí. Pensé que echaría un vistazo dentro de esta cómoda casa, para ver quién no tiene miedo de vivir aquí...";
			link.l1.go = "meeting";
			npchar.quest.meeting = "1";
		}
		else
		{
			dialog.text = "Ah, mi viejo amigo, capitán " + GetFullName(pchar) + "¡ Entra, entra!";
			link.l1 = "¡Bienvenido, amigo! Muy contento de verte. ¿No ves esqueletos danzando por las noches y muertos con monedas de cobre en los ojos en tus sueños?";
			link.l1.go = "talk";
		}
		NextDiag.TempNode = "First time";
		break;

	case "meeting":
		dialog.text = "¿Y por qué debería tener miedo, capitán? Es necesario temer a los vivos, los muertos no muerden. ¡Eh! Una vez tuve una vida bastante diferente, y ahora soy guardián de este cementerio. Cuido tumbas. Y también comercio con algunos trastos a veces...";
		link.l1 = "¿Y qué artículos comercias, dime, por favor?";
		link.l1.go = "trade_info";
		break;

	case "talk":
		dialog.text = "¿Qué te trae a mí esta vez?";
		link.l1 = "Muéstrame lo que tienes a la venta hoy.";
		link.l1.go = "trade";
		link.l2 = "Quiero hacerte una pregunta...";
		link.l2.go = "quests";
		link.l3 = "Nada serio. Simplemente vine a saludarte.";
		link.l3.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "trade_info":
		dialog.text = "Tengo mucho tiempo libre, por eso me gusta caminar por la selva para recolectar plantas útiles y piedras elegantes. Luego los vendo en el pueblo. No cuestan mucho, pero es mejor que nada. Y consigo una variedad de cosas de mis amigos...";
		link.l1 = "¿Amigos? ¿Quieres decir, revendes lo que otros te traen?";
		link.l1.go = "trade_info_1";
		break;

	case "trade_info_1":
		dialog.text = "O-ho-ho... No, me dan todo gratis. ¿Quién puede ser amigo de un vigilante de cementerio, si no los difuntos?";
		link.l1 = "¿Eh... Robas cadáveres?";
		link.l1.go = "trade_info_2";
		break;

	case "trade_info_2":
		dialog.text = "Yo no robo, sólo quito cosas a quienes ya no las necesitan. Aquí están enterradas muchas personas diferentes, algunas desconocidas y que no son de nuestras tierras. El comandante trae un cadáver de la ciudad y dice: 'Esto es para ti', " + npchar.name + ", envíalo a su último viaje.Desamparados, piratas ahorcados, bandidos asesinados por guardianes... todos están enterrados aquí.Y los viejos " + npchar.name + " entierra sus cuerpos según la costumbre cristiana.";
																																																																																				   link.l1 = "Ya veo. Bueno, el dinero es dinero, muéstrame lo que tienes.";
		link.l1.go = "trade";
		link.l2 = "Entendido. Tengo que irme. Me alegró conocerte.";
		link.l2.go = "exit";
		break;

	case "trade":
		DialogExit();
		if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
		{
			GiveItemToTrader(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "trade_date");
		}
		LaunchItemsTrade(npchar, 0);
		NextDiag.TempNode = "First time";
		break;

	case "fight":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		LAi_group_Attack(NPChar, Pchar);
		if (rand(3) != 1)
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "exit_setOwner":
		LAi_SetOwnerTypeNoGroup(npchar);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "Man_FackYou": // реакция на попытку залезть в сундук
		dialog.text = LinkRandPhrase("Y tú, " + GetFullName(pchar) + ", ¡eres un ladrón! ¡¡¡Guardias!!!", "¡Por el amor de Dios! Desvié la mirada por un momento y ya estás intentando robar lo que me pertenece! ¡Detengan al ladrón!!!", "¡Guardia! ¡Robo!!! ¡Atrapa al ladrón!!!");
		link.l1 = "¡Oh mierda!!!";
		link.l1.go = "fight";
		break;
	// belamour квест на получение фонаря -->
	case "Lantern_01":
		dialog.text = "Uf, así que solo eres un viajero... Mi nombre es " + GetFullName(npchar) + ", soy el cuidador de este lugar olvidado por Dios.";
		link.l1 = "¿Por qué te sientes así acerca del cementerio? Al contrario, es de aquí de donde nuestro Señor se lleva a los justos después del entierro.";
		link.l1.go = "Lantern_02";
		break;

	case "Lantern_02":
		dialog.text = "Pero los injustos, al parecer, se quedan aquí después del entierro. Durante las últimas noches, ha habido ruidos provenientes de la cripta. Y los lamentos son tan escalofriantes que me dan escalofríos... ¡Parece que una alma perdida no puede encontrar paz! Ahora solo duermo durante el día, por la noche, no puedo abandonar mi puesto ni pegar ojo...";
		link.l1 = "¿Ruidos? ¿Gemidos? Pero allí no hay nadie excepto los difuntos.";
		link.l1.go = "Lantern_03";
		break;

	case "Lantern_03":
		dialog.text = "Eso es lo que estoy diciendo, ¿sabes? Será mejor que te vayas de aquí antes de que el fantasma te perciba... De lo contrario, no podrás dormir, al igual que yo.";
		link.l1 = "Hm, sí, creo que sería mejor que abandone este lugar.";
		link.l1.go = "Lantern_04";
		link.l2 = "¿Quizás puedo ayudarte? Permíteme investigar esos ruidos extraños esta noche.";
		link.l2.go = "Lantern_05";
		break;

	case "Lantern_04":
		pchar.questTemp.Lantern = "NoLantern";
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "Lantern_05":
		dialog.text = "¿Estás fuera de tu mente?! Veo que tienes un arma, pero ¿cómo planeas luchar contra los muertos vivientes con ella? ¿Y si acabas estirando la pata allí, qué entonces? El fantasma vagará libre, ¡y hasta podría resucitarte como su sirviente!";
		link.l1 = "Bueno, eso es solo superstición...";
		link.l1.go = "Lantern_06";
		break;

	case "Lantern_06":
		dialog.text = "¿Qué superstición? ¡Esto no es la piadosa tierra de Europa, maldita sea... Los nativos, esos rostros colorados, pueden conjurar cualquier cosa, y ahora tenemos que vivir aquí!";
		link.l1 = "Aún así, déjame intentarlo. Esperaré hasta el anochecer y luego bajaré a la cripta.";
		link.l1.go = "Lantern_07";
		break;

	case "Lantern_07":
		dialog.text = "Bien, haz lo que quieras. Pero si no vuelves al amanecer, cerraré todo, lo barricaré y me iré de aquí por mi cuenta. ¡Ya sea fregando la cubierta como marinero o transportando cajas como estibador, no volveré aquí de todas formas!";
		link.l1 = "Solo cálmate... Todo estará bien.";
		link.l1.go = "Lantern_08";
		break;

	case "Lantern_08":
		dialog.text = "Espera... Toma esta linterna. Tengo una de repuesto. La necesitarás allí. ¡Está oscuro como boca de lobo!";
		link.l1 = "Gracias, realmente una linterna será útil en un lugar como ese.";
		link.l1.go = "Lantern_09";
		break;

	case "Lantern_09":
		GiveItem2Character(pchar, "lantern_belt");
		Log_Info("Has recibido la 'Linterna'");
		PlaySound("interface\important_item.wav");
		if (npchar.city == "Charles")
			SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Charles_CryptBig2", true);
		if (npchar.city == "Havana")
			SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Havana_CryptBig2", true);
		if (npchar.city == "Villemstad" || npchar.city == "PortRoyal")
			SetFunctionLocationCondition("NoiseCemetery_toCrypt", "Common_CryptBig2", true);
		pchar.quest.NoiseCemetery_SeaExit.win_condition.l1 = "EnterToSea";
		pchar.quest.NoiseCemetery_SeaExit.function = "NoiseCemetery_SeaExit";
		pchar.questTemp.Lantern = "ToCrypt";
		pchar.questTemp.Lantern.nation = npchar.nation;
		AddQuestRecord("NoiseCemetery", "1");
		AddQuestUserData("NoiseCemetery", "sCity", XI_ConvertString(loadedlocation.islandId));
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "Lantern_10":
		dialog.text = "¿Verdad? ¿Qué había allí? ¡Dime!";
		link.l1 = "¡Había el espíritu inquieto de una mujer! Afortunadamente, tuve al sacerdote para bendecir mi espada para castigar a los malvados, así que todo salió bien. Ese espíritu no te molestará más.";
		link.l1.go = "Lantern_11";
		break;

	case "Lantern_11":
		dialog.text = "¡Oh Señor, salva nuestras almas pecadoras! ¡Te lo advertí! ¡Y no me creíste!";
		link.l1 = "Sí, y sinceramente lamento eso. Pero ahora todo está bien: rocié este lugar con agua bendita, y ningún espíritu se atreverá a levantarse de la tumba. Puedes dormir tranquilo.";
		link.l1.go = "Lantern_12";
		break;

	case "Lantern_12":
		dialog.text = "¡Muchas gracias! ¡No tienes idea de lo que esto significa para mí! Aquí, por favor toma esto. No es mucho, pero no puedo dejarte ir sin una recompensa.";
		link.l1 = "Gracias, no puedo rechazar. ¡Buena suerte para ti!";
		link.l1.go = "Lantern_13";
		break;

	case "Lantern_13":
		pchar.quest.NoiseCemetery_SeaExit.over = "yes";
		AddMoneyToCharacter(PChar, 1000);
		pchar.questTemp.Lantern = "Done";
		AddQuestRecord("NoiseCemetery", "3");
		CloseQuestHeader("NoiseCemetery");
		NextDiag.TempNode = "First time";
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "Lantern_14":
		dialog.text = "¿No? Entonces qué demonios... quiero decir, en nombre de Dios, ¿qué pasó allí?";
		link.l1 = "No había ningún fantasma en absoluto. Una joven pareja eligió esta cripta como lugar para sus citas. Sus padres están en contra de esta unión, así que estaban buscando un lugar para estar solos.";
		link.l1.go = "Lantern_15";
		break;

	case "Lantern_15":
		dialog.text = "¿Solo?.. ¡Por qué esos jóvenes! ¡Que solo intenten venir aquí de nuevo! ¡Los ahuyentaré a ambos con un látigo o los encerraré en la cripta para que se queden allí!!!";
		link.l1 = "No volverán aquí nunca más. Les dije que sus pequeñas escapadas realmente asustaron a la guardia. Pretenden hacer eso. Y por cierto, la cerradura de la puerta está rota de todos modos.";
		link.l1.go = "Lantern_16";
		break;

	case "Lantern_16":
		dialog.text = "Sin problema, lo reemplazaré. Pero si alguna vez los atrapo...";
		link.l1 = "No te enfades tanto. Todos hemos tenido esa edad. No vinieron aquí porque este fuera el mejor lugar para citas.";
		link.l1.go = "Lantern_17";
		break;

	case "Lantern_17":
		dialog.text = "Justo suficiente... Bueno, que el Señor esté con ellos. Gracias por no dejar a un viejo en problemas. Aquí, por favor toma esto. No es mucho, pero no puedo dejarte ir sin una recompensa.";
		link.l1 = "Gracias, no puedo rechazar. ¡Buena suerte a ti!";
		link.l1.go = "Lantern_18";
		break;

	case "Lantern_18":
		DialogExit();
		pchar.quest.NoiseCemetery_SeaExit.over = "yes";
		AddMoneyToCharacter(PChar, 1000);
		pchar.questTemp.Lantern = "Done";
		AddQuestRecord("NoiseCemetery", "4");
		CloseQuestHeader("NoiseCemetery");
		NextDiag.TempNode = "First time";
		NextDiag.CurrentNode = NextDiag.TempNode;
		break;
		// <-- квест на получение фонаря
	}
}
