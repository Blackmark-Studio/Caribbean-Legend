// Ришард Шамбон - контрабандист
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	float locx, locy, locz;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		if (CheckAttribute(pchar, "GenQuest.CitizenConflict") && sti(pchar.GenQuest.CitizenConflict) > 3)
		{
			dialog.text = "No quiero hablar contigo. Atacas a civiles pacíficos sin razón y los provocas a pelear. ¡Piérdete!";
			link.l1 = "Hum...";
			link.l1.go = "exit";
			break;
		}
		// --> кольцо
		if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "find" && CheckAttribute(npchar, "quest.answer_2") && GetNpcQuestPastDayParam(npchar, "quest_date") >= 3 && !CheckAttribute(npchar, "quest.ring"))
		{
			dialog.text = "¡Oh! Aquí estás, amigo. Y yo pensando en encontrarte por mi cuenta. Te necesito, camarada.";
			link.l1 = "Eres sospechosamente amigable hoy, Richard. Bueno, te escucho.";
			link.l1.go = "ring";
			break;
		}
		// <-- кольцо
		if (npchar.quest.meeting == "0")
		{
			dialog.text = "¿Qué quieres? Para ser honesto, no estoy de buen humor hoy. En realidad, ya he olvidado cuándo fue la última vez que lo estuve.";
			link.l1 = "¿Es realmente tan malo, amigo?";
			link.l1.go = "meeting";
			npchar.quest.meeting = "1";
		}
		else
		{
			dialog.text = "¡Ah, "+GetFullName(pchar)+"! "+TimeGreeting()+". ¿Quieres algo?";
			link.l1 = LinkRandPhrase("¿Tienes algo interesante que decir?", "¿Ha sucedido algo nuevo en la isla?", "¿Me contarás los últimos chismes?");
			link.l1.go = "rumours_LSC";
			link.l2 = "Quiero hacerte unas preguntas sobre la isla.";
			link.l2.go = "int_quests"; // информационный блок
			link.l5 = "Solo quería saber cómo estás. ¡Nos vemos!";
			link.l5.go = "exit";
		}
		NextDiag.TempNode = "First time";
		break;

	case "meeting": // первая встреча
		dialog.text = "¿Malo? No, no es malo. Solo que no estoy de humor. ¿Qué es lo que querías?";
		link.l1 = "Solo quería conocerte. Soy un recién llegado aquí, así que solo estoy paseando por la Isla y conociendo a la gente.";
		link.l1.go = "meeting_1";
		break;

	case "meeting_1":
		dialog.text = "¿De verdad? Bien entonces. Soy Richard Shambon. Hace mucho tiempo comercié con algunas mercancías valiosas y algunas de ellas eran ilegales, pero llevo nueve años recogiendo restos de naufragios, buscando chatarra y cambiándola por comida y oro.";
		link.l1 = "Y yo soy " + GetFullName(pchar) + ", un capitán...";
		link.l1.go = "meeting_2";
		break;

	case "meeting_2":
		dialog.text = "¿Te refieres al ex capitán, ja-ja?";
		link.l1 = "Bueno, en realidad, mi barco está en Blueweld ahora. Y he navegado aquí en una tartana.";
		link.l1.go = "meeting_3";
		break;

	case "meeting_3":
		dialog.text = "¿De veras? ¡Imposible! ¿Y dónde está tu tartana ahora?";
		link.l1 = "Mm... en el fondo.";
		link.l1.go = "meeting_4";
		break;

	case "meeting_4":
		dialog.text = "A-ah... Y pensé... Lo que sea, camarada, mejor me tomo un poco de ron...";
		link.l1 = "Buena suerte con eso. Fue un placer hablar contigo. ¡Hasta luego!";
		link.l1.go = "exit";
		link.l2 = LinkRandPhrase("¿Tienes algo interesante que decir?", "¿Ha sucedido algo nuevo en la isla?", "¿Me contarás los últimos chismes?");
		link.l2.go = "rumours_LSC";
		link.l3 = "Quiero hacerte unas preguntas sobre la isla.";
		link.l3.go = "int_quests"; // информационный блок
		NextDiag.TempNode = "First time";
		break;

	// Кольцо
	case "ring":
		dialog.text = "¿Y era diferente antes? ¡Vamos, he tenido días malos, todos a veces los tienen! Dime, se rumorea en la Isla que eres un excelente luchador. ¿Es cierto?";
		link.l1 = "No sé lo que dicen, pero sé cómo manejar una espada si eso es lo que preguntas.";
		link.l1.go = "ring_1";
		npchar.quest.ring = "true";
		break;

	case "ring_1":
		dialog.text = "Entiendo. Veo que esos chismes eran ciertos... Escucha, " + pchar.name + ", ¿recuerdas que te hablé del anillo exterior? ¿Y sobre las cosas valiosas que puedes encontrar allí?";
		link.l1 = "Todos vosotros gustáis de hablar sobre ese anillo... Y todos decís lo mismo.";
		link.l1.go = "ring_2";
		break;

	case "ring_2":
		dialog.text = "¡Qué más se puede decir, ja-ja! Bien. Iré al grano. (bajando la voz) He encontrado un barco intacto en el anillo exterior, está en buen estado, lo cual es bastante raro.\nEl barco es grande, una pinaza. Fue traída aquí no hace mucho, alrededor de dos meses o incluso menos. Otros no la han encontrado aún, así que hay oportunidad de ganar buen dinero saqueando sus bodegas y camarotes.";
		link.l1 = "Bien, me alegro por ti. Pero ¿cómo me concierne esto? ¿Quieres pedirme que vaya contigo?";
		link.l1.go = "ring_3";
		break;

	case "ring_3":
		dialog.text = "¡Exactamente! Escucha. La proa de la pinaza está dañada. Esos malditos cangrejos usaron un agujero para entrar y construyeron un maldito nido dentro. Meterse mientras ellos están allí no es una opción y no tengo ni idea de cómo subir a la cubierta superior. Nunca he sido un buen luchador y no he tocado una espada en años, así que no podré matar a las criaturas por mi cuenta. Por eso vine a ti.";
		link.l1 = "Entonces, ¿me propones matar a todos los cangrejos dentro de ese barco, verdad?";
		link.l1.go = "ring_4";
		break;

	case "ring_4":
		dialog.text = "Sí. Tendremos un trato. Te mostraré el camino al barco y tú eliminarás los cangrejos. Compartiremos todo el botín que encontremos allí. Es un trato justo, yo he encontrado el barco y tú lo despejarás.";
		link.l1 = "No, camarada, no estoy interesado. No es mi estilo luchar contra cangrejos dentro de un barco medio hundido por algunos trofeos dudosos. Encuentra a otro valiente que saque las castañas del fuego por ti.";
		link.l1.go = "ring_exit";
		link.l2 = "Interesante... He estado pensando en inspeccionar el anillo exterior desde hace mucho tiempo. ¡Trato hecho! Mataré cangrejos.";
		link.l2.go = "ring_5";
		break;

	case "ring_exit":
		dialog.text = "Lástima... Has cometido un error. Hay muchas cosas jugosas en los barcos del anillo exterior... Y nadie ha estado en ese barco antes. Bien, es tu deseo. Adiós...";
		link.l1 = "Adiós, camarada...";
		link.l1.go = "exit";
		break;

	case "ring_5":
		dialog.text = "Me alegra haber acertado contigo, amigo. Tengo la sensación de que encontraremos muchas cosas interesantes dentro de ella...";
		link.l1 = "Veremos. ¿Sabes cuántos cangrejos hay allí?";
		link.l1.go = "ring_6";
		break;

	case "ring_6":
		dialog.text = "Pienso que unos cuatro o cinco de ellos... Bueno, en promedio.";
		link.l1 = "Me sirve. ¿Cuándo iremos?";
		link.l1.go = "ring_7";
		break;

	case "ring_7":
		dialog.text = "Vamos allí mañana, tenemos que prepararnos. Consigue algunos antídotos del hermano Julián, las mandíbulas del cangrejo son venenosas. La precaución es bienvenida. Reunámonos mañana a las ocho de la mañana en la 'cubierta oblicua'. ¿Sabes dónde está?";
		link.l1 = "No lo hago. Explica.";
		link.l1.go = "ring_8";
		break;

	case "ring_8":
		dialog.text = "Hay un naufragio de un viejo barco detrás del 'San Augustine'. Su proa está bajo el agua y su popa está levantada bien alto. Por eso la llaman la 'cubierta oblicua'. Solo puedes llegar allí nadando. Solo comienza a nadar desde el lugar bajo el puente y da la vuelta desde cualquier lado del 'San Augustine'. Nadaremos juntos desde allí.";
		link.l1 = "Bien. ¡Nos vemos mañana!";
		link.l1.go = "ring_9";
		break;

	case "ring_repeat":
		dialog.text = "8 en punto, 'cubierta oblicua'...";
		link.l1 = "Sí, sí, recuerdo eso...";
		link.l1.go = "exit";
		NextDiag.TempNode = "ring_repeat";
		break;

	case "ring_9":
		DialogExit();
		NextDiag.CurrentNode = "ring_repeat";
		pchar.quest.LSC_Ring_Start.win_condition.l1 = "Timer";
		pchar.quest.LSC_Ring_Start.win_condition.l1.date.hour = 7.0;
		pchar.quest.LSC_Ring_Start.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.LSC_Ring_Start.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.LSC_Ring_Start.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.LSC_Ring_Start.function = "LSC_RingStart"; // готовы
		pchar.quest.LSC_Ring_Over.win_condition.l1 = "Timer";
		pchar.quest.LSC_Ring_Over.win_condition.l1.date.hour = 10.0;
		pchar.quest.LSC_Ring_Over.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.LSC_Ring_Over.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.LSC_Ring_Over.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.LSC_Ring_Over.function = "LSC_RingOver"; // опоздание
		AddQuestRecord("LSC_Ring", "1");
		break;

	case "ring_10":
		dialog.text = "Ajá, aquí estás, amigo. ¿Listo para preparar una ensalada de cangrejo?";
		link.l1 = "¡Claro!";
		link.l1.go = "ring_11";
		break;

	case "ring_11":
		dialog.text = "Muy bien. Ahora gira la cabeza hacia el anillo exterior y mira. ¿Ves allí dos naufragios que sobresalen del agua?";
		link.l1 = "Mm... Sí, lo hago.";
		link.l1.go = "ring_12";
		break;

	case "ring_12":
		dialog.text = "Ahora mira entre ellos hacia el anillo exterior. ¿Ves el galeón con la proa levantada? Está justo hacia nosotros. Mira con cuidado.";
		link.l1 = "... ";
		link.l1.go = "ring_look";
		break;

	case "ring_look":
		DialogExit();
		LAi_SetActorType(pchar);
		LAi_ActorTurnToLocator(pchar, "reload", "reload_ring");
		DoQuestCheckDelay("LSC_RingTalkLook", 6.0);
		break;

	case "ring_13":
		dialog.text = "";
		link.l1 = "Creo que lo veo... ¡Sí!";
		link.l1.go = "ring_13a";
		break;

	case "ring_13a":
		dialog.text = "Es nuestro objetivo. Nada recto y no te desvíes. Te mostraré el camino de regreso cuando alcancemos el anillo exterior. La entrada a la bodega de carga es el agujero en la proa del barco. Sepas que no entraré hasta que mates a todos los cangrejos.";
		link.l1 = "Sí, tuvimos un trato ayer, lo recuerdo. Tú mostrarás el barco y yo mataré cangrejos. ¿Nadamos?";
		link.l1.go = "ring_14";
		break;

	case "ring_14":
		dialog.text = "¡Claro! Te seguiré.";
		link.l1 = "...";
		link.l1.go = "ring_swim";
		break;

	case "ring_swim":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorFollow(npchar, pchar, "", -1);
		LAi_SetImmortal(npchar, true);
		pchar.quest.LSC_Ring_enter.win_condition.l1 = "locator";
		pchar.quest.LSC_Ring_enter.win_condition.l1.location = "LostShipsCity_town";
		pchar.quest.LSC_Ring_enter.win_condition.l1.locator_group = "reload";
		pchar.quest.LSC_Ring_enter.win_condition.l1.locator = "reload_ring";
		pchar.quest.LSC_Ring_enter.function = "LSC_RingEnter";
		LSC_RingSetItems(); // раскладка итемзов
		AddQuestRecord("LSC_Ring", "3");
		break;

	case "ring_15":
		dialog.text = "¡Je, bien hecho! ¡Has matado a toda esta escoria!";
		link.l1 = "Recuerdo que alguien me habló de 'cuatro o cinco' cangrejos... Recuérdame, ¿quién fue?";
		link.l1.go = "ring_16";
		break;

	case "ring_16":
		dialog.text = "Amigo, nunca entré en la bodega para contarlos correctamente. Solo miré a través del agujero. No tenía intenciones de mentirte.";
		link.l1 = "Lo que sea. Vamos a revisar la bodega...";
		link.l1.go = "ring_17";
		break;

	case "ring_17":
		dialog.text = "¡Claro! Para eso estamos aquí, ¿verdad?";
		link.l1 = "¡Exactamente! No perdamos nuestro tiempo...";
		link.l1.go = "ring_18";
		break;

	case "ring_18":
		DialogExit();
		NextDiag.CurrentNode = "ring_wait";
		LAi_SetWarriorType(npchar);
		LAi_warrior_DialogEnable(npchar, true);
		LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
		DoQuestCheckDelay("LSC_RingDialog", 60.0); // 1 минуту на пошариться
		npchar.quest.diagnode = "ring_19";
		AddQuestRecord("LSC_Ring", "4");
		break;

	case "ring_wait":
		dialog.text = "Espera un poco, camarada, aún no he revisado todos los lugares que quería. Busca mejor, tal vez encuentres más cosas de valor.";
		link.l1 = "Bien...";
		link.l1.go = "exit";
		NextDiag.TempNode = "ring_wait";
		break;

	case "ring_19":
		dialog.text = "Nada especial. Es una lástima que no haya bienes valiosos aquí. Hay provisiones en barriles y copra en cajas. Sin embargo, he encontrado una caja con vino caro. ¿Y qué tienes tú?";
		link.l1 = "Nada interesante tampoco. Unas cajas son bastante valiosas, pero el resto es carne enlatada y copra como has dicho.";
		link.l1.go = "ring_20";
		break;

	case "ring_20":
		dialog.text = "No es suficiente... Vamos arriba y revisemos la cubierta superior y las cabinas.";
		link.l1 = "Vamos.";
		link.l1.go = "ring_21";
		break;

	case "ring_21":
		DialogExit();
		chrDisableReloadToLocation = false;
		LocatorReloadEnterDisable("ExternalRingInside", "reload1", true);
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		pchar.quest.LSC_Ring_deck.win_condition.l1 = "ExitFromLocation";
		pchar.quest.LSC_Ring_deck.win_condition.l1.location = pchar.location;
		pchar.quest.LSC_Ring_deck.win_condition = "LSC_RingEnterDeck";
		for (i = 1; i <= 3; i++)
		{
			sld = ItemsFromID("purse" + i);
			sld.shown = true;
			sld.startLocation = "ExternalRingDeck";
			sld.startLocator = "item" + i;
		}
		break;

	case "ring_22":
		dialog.text = "¡Maldita sea! ¡Mira eso! ¡Maldita mugre de cangrejo llegó a la cubierta! ¿Y cómo han logrado hacer tal truco?!";
		link.l1 = "¡No seas cobarde! Quédate aquí, no te muevas y no llames su atención. Me ocuparé de esas criaturas de inmediato...";
		link.l1.go = "ring_23";
		break;

	case "ring_23":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocator(npchar, "reload", "reload1", "", -1);
		break;

	case "ring_24":
		dialog.text = "¡Ah! ¡Así que las historias sobre tu habilidad en esgrima eran ciertas! Si estuviera aquí solo, me lanzaría por la borda...";
		link.l1 = "Escucha, ¿y cómo te convertiste en contrabandista en el pasado, eh? ¿O estabas huyendo de todos?";
		link.l1.go = "ring_25";
		break;

	case "ring_25":
		dialog.text = "Amigo, primero, era más joven, más fuerte y más imprudente. Segundo, no soy mercenario para pelear guerras - soy un contrabandista y siempre tratamos de evitar el derramamiento de sangre. Tercero, siempre fui por las velas y el timón, no por las espadas y pistolas. Y finalmente, años viviendo aquí me han vuelto blando. \nAsí que no me culpes. Vamos a revisar la cubierta superior. Parece que el barco ha estado en una pelea seria - mira el daño...";
		link.l1 = "Tienes razón. El barco definitivamente estaba bajo un fuego intenso. Bien, busquemos algo interesante.";
		link.l1.go = "ring_26";
		break;

	case "ring_26":
		dialog.text = "Sí. Y necesitamos encontrar entradas a las habitaciones interiores.";
		link.l1 = "Trato, no perdamos tiempo. Llámame si ves un cangrejo.";
		link.l1.go = "ring_27";
		break;

	case "ring_27":
		DialogExit();
		NextDiag.CurrentNode = "ring_wait";
		LAi_SetWarriorType(npchar);
		LAi_warrior_DialogEnable(npchar, true);
		LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
		DoQuestCheckDelay("LSC_RingDialog", 80.0); // 1.3 минуты на пошариться
		npchar.quest.diagnode = "ring_28";
		AddQuestRecord("LSC_Ring", "5");
		break;

	case "ring_28":
		dialog.text = "No hay nada valioso otra vez... He encontrado algunas cosillas interesantes y eso es todo. Pero está bien, por lo general no hay tesoros valiosos en las cubiertas. Lo mejor debe estar en las cabinas. Hay una entrada a los aposentos del capitán por allá. Vamos a echar un vistazo.";
		link.l1 = "Ten cuidado, ¿quién sabe qué nos espera allí? Quizás, debería entrar yo primero.";
		link.l1.go = "ring_29";
		break;

	case "ring_29":
		dialog.text = "Vámonos, " + pchar.name + "  Ya no me esconderé detrás de ti. Es una vergüenza, eso seguro... ";
		link.l1 = "Entonces, sigue adelante...";
		link.l1.go = "ring_30";
		break;

	case "ring_30":
		DialogExit();
		chrDisableReloadToLocation = true;
		LocatorReloadEnterDisable("ExternalRingDeck", "reload2", false);
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload2", "ExternalRingCabin1", "reload", "reload1", "OpenTheDoors", -1);
		pchar.quest.LSC_Ring_cabin.win_condition.l1 = "location";
		pchar.quest.LSC_Ring_cabin.win_condition.l1.location = "ExternalRingCabin1";
		pchar.quest.LSC_Ring_cabin.win_condition = "LSC_RingEnterCabin";
		sld = ItemsFromID("RingCapBook"); // кладем журнал 'Санта-Люсии'
		sld.shown = true;
		sld.startLocation = "ExternalRingCabin1";
		sld.startLocator = "item1";
		break;

	case "ring_31":
		dialog.text = "Parece que tuve suerte... ni cangrejos ni otra inmundicia aquí. Y ahora vamos a dar vuelta esta cabaña, carajo, juro que estoy empezando a enojarme. ¡He encontrado solo dos malditas docenas de doblones y algunas baratijas!";
		link.l1 = "Calma. Tenías razón, todos los objetos de valor siempre están guardados en la cabina del capitán. ¡Veamos qué tenemos!";
		link.l1.go = "ring_32";
		break;

	case "ring_32":
		DialogExit();
		NextDiag.CurrentNode = "ring_wait";
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocator(npchar, "goto", "goto2", "LSC_RingSetToBarman", -1);
		DoQuestCheckDelay("LSC_RingDialog", 30.0); // 30 сек на пошариться
		npchar.quest.diagnode = "ring_33";
		break;

	case "ring_33":
		dialog.text = "¡Ja, ja! ¡Tal como pensaba! Conozco los hábitos de los mercaderes, les gusta hacer escondites secretos y ocultar allí el tesoro del barco. ¡El capitán de esta pinaza era un bribón astuto, pero a mí no me engañarán tan fácilmente! ¡Mira lo que he encontrado! ¡Nunca habrías podido encontrarlo sin mí!";
		link.l1 = "¡Muéstrame!";
		link.l1.go = "ring_34";
		break;

	case "ring_34":
		dialog.text = "¡Cuarenta mil pesos, dos cofres llenos de doblones, un paquete de esmeraldas y un montón de joyas! El propietario era bastante rico... Bueno, al menos compensará nuestro esfuerzo, aunque esperaba obtener más cosas. Vamos a repartirlo justamente.";
		link.l1 = "¡Excelente, Richard. Al menos hemos ganado algo de dinero!";
		link.l1.go = "ring_35";
		break;

	case "ring_35":
		TakeNItems(pchar, "jewelry4", 25);
		TakeNItems(pchar, "chest", 1);
		TakeNItems(pchar, "icollection", 1);
		AddMoneyToCharacter(pchar, 20000);
		Log_Info("Has recibido un cofre con doblones");
		Log_Info("Has recibido 25 esmeraldas");
		Log_Info("Has recibido una colección de joyas");
		PlaySound("interface\important_item.wav");
		dialog.text = "Bueno, y mantengamos lo que cada uno de nosotros ha encontrado en las cubiertas para nosotros mismos. ¿Estás de acuerdo con eso? ¿Has encontrado algo útil en los cofres y en los armarios?";
		link.l1 = "Algunas cosas indias, amuletos, papeles y demás.";
		link.l1.go = "ring_36";
		break;

	case "ring_36":
		dialog.text = "Mantenlo para ti. Después de todo, has hecho el trabajo más arriesgado.";
		if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
		{
			link.l1 = "Bien. Y he encontrado algo más que un cazador de tesoros como tú podría encontrar útil. Aquí, había un diario de capitán sobre la mesa. La historia que está escrita allí es muy triste... pero nos concierne de alguna manera. ¡Hay una caja escondida en la bodega y está llena de oro! ¡Léelo!";
			link.l1.go = "ring_41";
		}
		else
		{
			if (CheckCharacterItem(pchar, "RingCapBook")) // взял журнал
			{
				link.l1 = "Bien. Pero he encontrado una cosa más: el diario del capitán.";
				link.l1.go = "ring_38";
			}
			else
			{
				link.l1 = "Está bien, estoy de acuerdo con tales términos, ja-ja. Entonces, ¿es hora de regresar?";
				link.l1.go = "ring_37";
			}
		}
		break;

	case "ring_37":
		dialog.text = "Sí. No le digas a nadie más sobre el barco, será nuestro secreto. Claro, no necesitamos copra, pero las provisiones nos serán útiles. Ya no tendremos que comprarlas al almirante.";
		link.l1 = "Está bien, estoy de acuerdo. Espero que otros no encuentren el barco pronto. ¡Vamos!";
		link.l1.go = "ring_cabin_exit";
		break;

	case "ring_38":
		dialog.text = "¿Lo leíste?";
		link.l1 = "Aún no...";
		link.l1.go = "ring_39";
		break;

	case "ring_39":
		dialog.text = "¡Así que leámoslo! Podemos aprender una información importante de ello. También será interesante saber cómo terminó aquí. ¡Léelo!";
		link.l1 = "Mm. Bien, lo leeré ahora...";
		link.l1.go = "ring_40";
		break;

	case "ring_40":
		DialogExit();
		NextDiag.CurrentNode = "book_wait";
		LAi_SetWarriorType(npchar);
		LAi_warrior_DialogEnable(npchar, true);
		LAi_group_MoveCharacter(npchar, "TMP_FRIEND");
		break;

	case "book_wait":
		dialog.text = "¿Lo leíste? ¿Qué hay allí?";
		if (CheckAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook")) // прочел журнал
		{
			link.l1 = "Bueno, escucha entonces... La historia es muy triste... pero nos concierne ahora de alguna manera. Tus habilidades para buscar tesoros podrían ayudarnos. ¡Hay una caja oculta llena de oro en la bodega de carga! ¡Léelo!";
			link.l1.go = "ring_41";
		}
		else
		{
			link.l1 = "Espera un segundo. Leeré y te diré...";
			link.l1.go = "exit";
			NextDiag.TempNode = "book_wait";
		}
		break;

	case "ring_41":
		dialog.text = "¿De veras? " + pchar.name + ", yo soy... bueno, no leo tan bien. Dime qué está escrito allí con detalles, ¿eh?";
		link.l1 = "Versión corta: este bergantín atravesaba el Mar Caribe desde el Continente Sur hasta la Nueva España. El capitán se casó con la princesa india de una tribu del bajo Orinoco. Ella le contó dónde su gente hacía sacrificios...";
		link.l1.go = "ring_42";
		break;

	case "ring_42":
		dialog.text = "";
		link.l1 = "Las pepitas de oro fueron sus sacrificios. Claro, nuestro valiente capitán ha robado este alijo de oro con la ayuda de su primer oficial y contramaestre. Lo han puesto en la bodega, en una de las cajas y lo han cubierto con copra...";
		link.l1.go = "ring_43";
		break;

	case "ring_43":
		dialog.text = "";
		link.l1 = "Pero parece que el robo del lugar sagrado indio fue castigado. El barco quedó en una calma chicha, las reservas de agua se estaban agotando, comenzó una epidemia de fiebre y los piratas atacaron el barco. Los marineros culparon a la chica india, la esposa del capitán, y exigieron lanzarla por la borda. Por supuesto, el capitán se negó y la tripulación inició un motín...";
		link.l1.go = "ring_44";
		break;

	case "ring_44":
		dialog.text = "";
		link.l1 = "El capitán perdió esa pelea. Según las últimas notas, se encerró con una chica india en el camarote y trató de disparar a los marineros enfurecidos que rompían la puerta. Y había una tormenta acercándose a ellos... parece que eso trajo el barco aquí. El final de la historia es claro: la chica fue disparada y el capitán seguramente fue asesinado por los rebeldes.";
		link.l1.go = "ring_45";
		break;

	case "ring_45":
		dialog.text = "Mm. Es realmente una historia triste. ¿Pero no me estarás tomando el pelo? ¿Hay una caja con oro en la bodega de carga? ¡No puedo creer lo que oigo! ¿Cuál de ellas? ¡Vamos allí! ¡Revisaré cada fardo, cada barril!";
		link.l1 = "Vamos. También estoy ansioso por empezar a buscar.";
		link.l1.go = "ring_seek_gold";
		break;

	case "ring_cabin_exit":
		DialogExit();
		chrDisableReloadToLocation = false;
		LocatorReloadEnterDisable("ExternalRingInside", "reload1", false);	   // открываем выход
		LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход // patch-2
		DoQuestReloadToLocation("ExternalRingDeck", "reload", "reload2", "LSC_RingFinalStage");
		sld = ItemsFromID("RingCapBook");
		sld.shown = false; // убираем журнал
		AddQuestRecord("LSC_Ring", "6");
		break;

	case "ring_seek_gold":
		DialogExit();
		chrDisableReloadToLocation = false;
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		// ставим прерывание на локатор
		pchar.quest.LSC_Ring_gold.win_condition.l1 = "locator";
		pchar.quest.LSC_Ring_gold.win_condition.l1.location = "ExternalRingInside";
		pchar.quest.LSC_Ring_gold.win_condition.l1.locator_group = "quest";
		pchar.quest.LSC_Ring_gold.win_condition.l1.locator = "gold";
		pchar.quest.LSC_Ring_gold.win_condition = "LSC_RingFindGold";
		// подменяем состав бокса
		pchar.GenQuestBox.ExternalRingInside = true;
		pchar.GenQuestBox.ExternalRingInside.box1.items.jewelry5 = 2522;
		AddQuestRecord("LSC_Ring", "7");
		break;

	case "ring_46":
		dialog.text = "¡Ja-ja! ¡Lo hemos encontrado! ¡Existe de verdad! ¡Mira esa enorme pila! ¡Toda la caja! ¡Hay cinco mil pepitas, no menos! ¡Nunca he visto tanto oro!";
		link.l1 = "Felicidades, compañero. Parece que nuestra empresa ha concluido con éxito... ¿Qué haremos con todo ese oro?";
		link.l1.go = "ring_47";
		break;

	case "ring_47":
		dialog.text = "¿Qué quieres decir? ¡Nos dividiremos a la mitad!";
		link.l1 = "Claro que sí. ¿Dónde quieres guardarlo? ¿Lo dejarás aquí?";
		link.l1.go = "ring_48";
		break;

	case "ring_48":
		dialog.text = "¡Ja! Seguramente, esconderé el oro en mis escondites y nadie los encontrará jamás. ¡Esconder es lo que sé hacer bien! Vamos a mover la mitad del oro a este barril, esa sería mi parte. Me lo llevaré antes del atardecer.\nPuedes hacer lo que quieras con tu parte. Pero será mejor que también lo muevas a tus propios escondites. No me culpes si encuentras que tu oro ha desaparecido. Soy un hombre honesto, a mi manera de honestidad, y no me atrevería a tomar tu parte. Pero otros, aquellos que vendrán aquí más tarde... ellos podrían encontrarlo.";
		link.l1 = "Está bien. Decidiré qué hacer con mi oro. Pongamos tu parte en un barril...";
		link.l1.go = "ring_49";
		break;

	case "ring_49":
		DialogExit();
		SetLaunchFrameFormParam("Dos horas después..." + NewStr() + "¡Has compartido el oro!", "", 0, 5); // табличка
		WaitDate("", 0, 0, 0, 2, 10);
		LaunchFrameForm();
		RecalculateJumpTable();
		sld = characterFromId("LSC_Rishard");
		sld.quest.diagnode = "ring_50";
		DoQuestCheckDelay("LSC_RingDialog", 5.0);
		break;

	case "ring_50":
		dialog.text = "Hecho... Gracias, " + pchar.name + ", por venir conmigo. No podría hacer esto sin ti. Ahora debería considerar construir una tartana... para zarpar de aquí... Ah, lo que sea. Pensaré en ello más tarde\nTengo un trabajo que hacer: mover el oro a lugares seguros. ¡Adiós, amigo, deseo que uses tu parte sabiamente!";
		link.l1 = "Adiós, Richard. Ha sido un día glorioso hoy. ¡Nos vemos!";
		link.l1.go = "ring_51";
		break;

	case "ring_51":
		DialogExit();
		LocatorReloadEnterDisable("ExternalRingInside", "reload1", false);	   // открываем выход
		LocatorReloadEnterDisable("LostShipsCity_town", "reload_ring", false); // открываем вход
		DoQuestCheckDelay("LSC_RingFinalStage", 0.5);
		DeleteAttribute(pchar, "questTemp.LSC.Ring.ReadCapBook");
		AddQuestRecord("LSC_Ring", "8");
		break;
		//--------------------------------------- блок вопросов и ответов ---------------------------------------------
	case "int_quests":
		dialog.text = "¿Preguntas? Oh, está bien, si realmente necesitas eso...";
		if (!CheckAttribute(npchar, "quest.answer_1"))
		{
			link.l1 = "¿Cómo llegaste aquí?";
			link.l1.go = "ansewer_1";
		}
		if (!CheckAttribute(npchar, "quest.answer_2"))
		{
			link.l2 = "¿Quieres dejar la Isla?";
			link.l2.go = "ansewer_2";
		}
		if (!CheckAttribute(npchar, "quest.answer_3"))
		{
			link.l3 = "¿Alguna vez has considerado unirte a uno de los clanes? ¿Narvales, por ejemplo?";
			link.l3.go = "ansewer_3";
		}
		if (!CheckAttribute(npchar, "quest.answer_4"))
		{
			link.l4 = "¿Es cierto que puedes encontrar muchas cosas interesantes en el anillo exterior?";
			link.l4.go = "ansewer_4";
		}
		link.l10 = "Sin preguntas. Perdón...";
		link.l10.go = "exit";
		break;

	case "ansewer_1":
		dialog.text = "Durante diez años, mis camaradas y yo navegamos desde Cuba hasta la Isla en una bien equipada tartana. Manteníamos la ubicación de la Isla en secreto - transportábamos cadáveres de toros y vendíamos carne fresca por bienes y oro de las bodegas de los barcos locales\n¡Buenos tiempos! Las provisiones siempre fueron un problema aquí, pan y carne salada principalmente, así que nos pagaban por carne jugosa con especias, ¡que cuestan una fortuna en Europa! Cada viaje hacía suficiente dinero para comprar a cada ramera de Tortuga\nPero todo tiene un fin, así como nuestra vida satisfecha. El clima empeoró - las tormentas se hicieron más fuertes, así que navegar hacia la Isla se volvió mucho más peligroso. Algunos de mis compañeros dejaron el negocio, pero no yo y una docena de hombres valientes\nFinalmente, fuimos lanzados a un arrecife a dos millas de la Isla. Todavía no entiendo cómo logré nadar a través del mar tormentoso. Así es como me convertí en uno de aquellos con los que comerciaba en el pasado.";
		link.l1 = "Historia interesante...";
		link.l1.go = "int_quests";
		npchar.quest.answer_1 = "true";
		break;

	case "ansewer_2":
		dialog.text = "¡Ja! ¡Saldré de aquí, maldita sea! Pero más tarde. ¿Qué haría yo en Cuba? No tengo amigos y mi bolsillo está vacío. Empezaré a construir un barco justo después de encontrar un barco con un cargamento valioso en el anillo exterior o un montón de doblones.";
		link.l1 = "Veo...";
		link.l1.go = "int_quests";
		npchar.quest.answer_2 = "true";
		SaveCurrentNpcQuestDateParam(npchar, "quest_date");
		break;

	case "ansewer_3":
		dialog.text = "¿Y por qué debería hacerlo? ¿Para hacer guardia como un idiota cada tercer día y mantener a la gente alejada del San Gabriel? Y no les gusta contratar a personas nuevas. Son nativos locales... Y los negros son lo mismo. No, mejor estaré solo.";
		link.l1 = "Entiendo...";
		link.l1.go = "int_quests";
		npchar.quest.answer_3 = "true";
		break;

	case "ansewer_4":
		dialog.text = "¡Claro! Eso es lo que mantiene viva la Isla y a los lugareños. ¿Sabes cuándo hay fiestas aquí? Cuando llega un nuevo barco. Pero de todos modos, hay muchos barcos intactos llenos de oro y mercancías en el anillo exterior\nEl problema es que el anillo exterior es casi imposible de explorar, las cosas están desordenadas allí afuera, si te enredas, resbalas o caes mal, puedes encontrarte en un agujero del que no puedes salir por ti mismo. Entonces estás acabado. Mucha gente murió de esa manera.";
		link.l1 = "Mm... Interesante.";
		link.l1.go = "int_quests";
		npchar.quest.answer_4 = "true";
		break;
		// <-- блок вопросов и ответов

		//----------------------------------------- специальные реакции -----------------------------------------------
		// обнаружение ГГ в сундуках
	case "Man_FackYou":
		dialog.text = LinkRandPhrase("¿Qué haces ahí, eh? ¡Ladrón!", "¡Solo mira eso! En cuanto me perdí en la contemplación, ¡decidiste revisar mi cofre!", "¿Has decidido revisar mis cofres? ¡No te saldrás con la tuya!");
		link.l1 = "¡Maldita sea!";
		link.l1.go = "fight";
		break;

	case "Woman_FackYou":
		dialog.text = "¿Qué?! ¿Decidiste revisar mis cofres? ¡No te saldrás con la tuya!";
		link.l1 = "¡Chica tonta!";
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
		dialog.text = LinkRandPhrase("Escucha, será mejor que guardes tu arma. Me pone nervioso.", "Sabes, correr con espada no se tolera aquí. Guárdala.", "Escucha, no juegues al caballero medieval corriendo con una espada. Guárdala, no te queda bien...");
		link.l1 = LinkRandPhrase("Bien.", "Está bien.", "Como tú digas...");
		link.l1.go = "exit";
		NextDiag.TempNode = "First Time";
		break;

	case "CitizenNotBlade":
		if (loadedLocation.type == "town")
		{
			dialog.text = NPCharSexPhrase(NPChar, "Escucha, soy ciudadano de la ciudad y te pediría que mantuvieras tu espada envainada.", "Escucha, soy ciudadano de la ciudad y te pediría que bajes tu espada.");
			link.l1 = LinkRandPhrase("Bien.", "Está bien.", "Como usted diga...");
		}
		else
		{
			dialog.text = NPCharSexPhrase(NPChar, "Ten cuidado, amigo, mientras corres con un arma. Puedo ponerme nervioso...", "No me gusta cuando los hombres pasan frente a mí con sus armas listas. Me asusta...");
			link.l1 = RandPhraseSimple("Entendido.", "Me lo estoy llevando.");
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
