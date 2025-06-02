// диалоги персонажей по пиратской линейке // Addon 2016-1 Jason пиратская линейка
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i;
	string sTemp, attrL;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	attrL = Dialog.CurrentNode;

	if (HasSubStr(attrL, "ShipStockManBack_"))
	{
		i = findsubstr(attrL, "_", 0);
		NPChar.ShipToStoreIdx = strcut(attrL, i + 1, strlen(attrL) - 1); // индех в конце
		Dialog.CurrentNode = "ShipStockManBack";
	}

	switch (Dialog.CurrentNode)
	{
	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "First time":
		dialog.text = "¿Qué quieres?";
		link.l1 = "Debería irme...";
		link.l1.go = "exit";
		break;

	// Лопе Монторо
	case "Mtr_officer":
		if (pchar.questTemp.Mtraxx != "fail" && pchar.questTemp.Mtraxx == "jewelry_5")
		{
			pchar.quest.Mtraxx_JewelryHavanaOver.over = "yes"; // снять таймер
			dialog.text = "¡Por el amor de Dios, ¿quién diablos eres?!";
			link.l1 = "Buen día, don Lope. Aunque aún no nos conocemos, ahora sería un buen momento como cualquier otro. Especialmente ahora que estoy tan ansioso por ayudarte a salir de esta situación difícil...";
			link.l1.go = "Mtr_officer_1";
		}
		else
		{
			dialog.text = "¿Qué quieres?";
			link.l1 = "Debería irme...";
			link.l1.go = "exit";
		}
		break;

	case "Mtr_officer_1":
		dialog.text = "¿Ayuda? ¿Yo? ¡Qué giro de los acontecimientos! ¿Me iluminaría, señor, de dónde proviene tal generosidad?";
		link.l1 = "Ciertamente. Estoy buscando a tu antiguo capitán, Esberdo Cabanas, y no tengo mucho tiempo... preferiblemente, me gustaría encontrarlo en ese lugar que mantiene en secreto. Aún mejor si llego allí antes que él.";
		link.l1.go = "Mtr_officer_2";
		DelLandQuestMark(npchar);
		break;

	case "Mtr_officer_2":
		dialog.text = "¡Ja, ja! ¡Le dije a este idiota patético que mantuviera la boca cerrada! El ámbar azul, ¿verdad?";
		link.l1 = "Estáis pensando en la dirección correcta, mi buen señor.";
		link.l1.go = "Mtr_officer_3";
		break;

	case "Mtr_officer_3":
		dialog.text = "Entonces apresurémonos. Me encantaría contarte hasta el último detalle si encuentras la forma de sacarme de aquí. ¿Sabes cómo terminé en este agujero?";
		link.l1 = "En general, sí, lo hago.";
		link.l1.go = "Mtr_officer_4";
		break;

	case "Mtr_officer_4":
		dialog.text = "Estaba borracho como una cuba cuando eso pasó. ¡Maldito sea ese camarero sangriento! No recuerdo nada. Me lo contaron todo solo cuando desperté en la bodega del 'Cantavro'. Todo quedaría atrás si simplemente zarpáramos, tanto el comandante como el alcalde estaban dispuestos a mirar para otro lado. Pero ese maldito don Esberdo simplemente me metió en la cárcel. ¿Crees que lo hizo 'para hacer lo correcto'? Ojalá, ese sinvergüenza solo quería quedarse con mi parte de los ámbares.\nFui yo quien mencionó que podría haber más ámbares bajo el agua, de los que encontramos en la playa. Fui yo quien encontró la manera de conseguirlo. Iba a recibir una buena tajada, pero... ¡oh, ese hijo de perra! Ugh, pero basta de eso. Ni el alcalde, ni el comandante, ni el don de Toledo están contentos con que me mantengan aquí pudriéndome. Si no fuera por ese campesino y su mujer vaca, que alborotaron los palomares... de cualquier manera, no se opondrán a que me ayudes.\nHabla con el gobernador, finge ser mi viejo amigo de Europa - yo mismo lo confirmaré. ¿Cuál es tu nombre, por cierto?";
		link.l1 = "" + GetFullName(pchar) + ".";
		link.l1.go = "Mtr_officer_5";
		break;

	case "Mtr_officer_5":
		dialog.text = "" + GetFullName(pchar) + ", maravilloso. Ve a ver a don Diego de Toledo y pídele consejo. Recuerda, solo tienes tres días, perseguir al 'Cantavro' sería inútil después de eso. Libérame y te daré todo lo que necesitas para ocuparte de ese bastardo, Cabañas.";
		link.l1 = "Iré a ver al gobernador de inmediato, don Lope. Haré todo lo posible para resolver esta situación por el bien de ambos.";
		link.l1.go = "Mtr_officer_6";
		break;

	case "Mtr_officer_6":
		DialogExit();
		pchar.questTemp.Mtraxx = "jewelry_6";
		LAi_CharacterDisableDialog(npchar);
		AddQuestRecord("Roger_1", "8");
		SetFunctionTimerCondition("Mtraxx_TimeclearPrison", 0, 0, 4, false); // таймер
		if (bImCasual)
			NewGameTip("Modo exploración: el temporizador no está desactivado. ¡Cumple el plazo!");
		AddLandQuestMark(characterFromId("Havana_Mayor"), "questmarkmain");
		break;

	case "Mtr_officer_7":
		pchar.quest.Mtraxx_TimeclearPrison.over = "yes"; // снять таймер
		dialog.text = "Entonces, el charlatán y su gallina relojeadora se vengaron, y finalmente terminé con este agujero. Tienes mi gratitud, señor, has cumplido tu parte. Ahora permíteme hacer la mía.";
		link.l1 = "¡Soy todo oídos!";
		link.l1.go = "Mtr_officer_8";
		DelLandQuestMark(npchar);
		break;

	case "Mtr_officer_8":
		dialog.text = "Bien. Durante nuestra patrulla anterior, nos golpeó una tormenta que nos hizo abandonar nuestro rumbo. Aterrizamos en la playa de Tierra Firme occidental, no lejos de la Costa de los Mosquitos, para conseguir un poco de agua fresca. Allí encontramos un buen depósito de ámbar azul. Hice algo de prospección y encontré un montón de él bajo el agua. Necesitábamos mejor equipo para recolectarlo, por eso decidimos regresar más tarde.\nEsberdo había comprado cinco lanchas largas en La Habana para que los indios bucearan y recogieran el ámbar. Sabes el resto de la historia: los desgraciados se deshicieron de mí y zarparon. Encuéntralo en la Costa de los Mosquitos al norte de Blueweld, y apresúrate: según mis cálculos, solo tienes unos siete días para llegar allí. Espero que atrapes al bastardo en medio de la recolección, le quites todo su ámbar y le apuñales el vientre numerosas veces. Sin embargo, ten cuidado, mi antiguo capitán es un luchador y un marinero hábil. Buena suerte, señor.";
		link.l1 = "Lo mismo para ti, Lope. ¡Adiós!";
		link.l1.go = "Mtr_officer_9";
		break;

	case "Mtr_officer_9":
		DialogExit();
		pchar.questTemp.Mtraxx = "jewelry_10";
		LAi_CharacterDisableDialog(npchar);
		npchar.lifeday = 0;
		AddQuestRecord("Roger_1", "12");
		SetFunctionTimerCondition("Mtraxx_TimeclearGulf", 0, 0, 7, false); // таймер
		pchar.quest.mtr_jewelry_gulf.win_condition.l1 = "location";
		pchar.quest.mtr_jewelry_gulf.win_condition.l1.location = "Santacatalina";
		pchar.quest.mtr_jewelry_gulf.function = "Mtraxx_JewelryGulf";
		DeleteAttribute(pchar, "GenQuest.PrisonQuestLock");
		DelMapQuestMarkCity("Havana");
		AddMapQuestMarkShore("Shore53", true);
		break;

	// Росарио Гусман
	case "Mtr_rosario":
		dialog.text = "¿Quiere preguntar algo, señor?";
		link.l1 = "Con respecto a don Montoro. Somos viejos conocidos y me sentí realmente disgustado cuando supe de sus desgracias. Don Diego de Toledo me ha enviado a usted, dijo que ya había intentado liberar a nuestro amigo en común...";
		link.l1.go = "Mtr_rosario_1";
		break;

	case "Mtr_rosario_1":
		dialog.text = "Mm... señor, esto es un poco... inesperado, pero me alegra conocer a un amigo de Lope. ¡Ha tenido mala suerte durante bastante tiempo ya y ahora esto...";
		link.l1 = "¿Qué podemos hacer por él? ¡De ninguna manera puede un noble hidalgo pudrirse entre la escoria de la sociedad!";
		link.l1.go = "Mtr_rosario_2";
		break;

	case "Mtr_rosario_2":
		dialog.text = "¡Un hombre de negocios! Es tanto fácil como difícil ayudar al pobre Lope. He hablado con el usurero con quien el pobre Lope tuvo la mala suerte de discutir. Ha accedido a encontrarse a mitad de camino por quinientos doblones. Toda una suma por sus 'sufrimientos' y los de su esposa. Por desgracia, solo he logrado reunir la mitad de la suma requerida: doscientos cincuenta doblones.";
		link.l1 = "Entonces, si te consigo otros doscientos cincuenta doblones, ¿don Lope será liberado?";
		link.l1.go = "Mtr_rosario_3";
		break;

	case "Mtr_rosario_3":
		dialog.text = "Sí. El bastardo codicioso me prometió difundir la palabra de que Lope le compensó todo el daño. También pedirá al gobernador que lo perdone.";
		if (PCharDublonsTotal() >= 250) // belamour legendary edition
		{
			link.l1 = "Tengo la suma requerida conmigo ahora mismo. Aquí, que este burgués codicioso se atragante con ella.";
			link.l1.go = "Mtr_rosario_4";
		}
		link.l2 = "Haré mi mejor esfuerzo para conseguir dinero lo antes posible.";
		link.l2.go = "Mtr_rosario_5";
		break;

	case "Mtr_rosario_4":
		RemoveDublonsFromPCharTotal(250); // belamour legendary edition
		PlaySound("interface\important_item.wav");
		dialog.text = "¡No puedo creer lo que escucho! ¡Señor, debe haber sido enviado por el Señor!";
		link.l1 = "¿Cuándo liberarán a nuestro hombre?";
		link.l1.go = "Mtr_rosario_8";
		DelLandQuestMark(npchar);
		break;

	case "Mtr_rosario_5":
		dialog.text = "Me alegra oírlo, señor. Eres un verdadero amigo de Lope y un verdadero noble.";
		link.l1 = "¡Adiós!";
		link.l1.go = "Mtr_rosario_6";
		break;

	case "Mtr_rosario_6":
		DialogExit();
		AddQuestRecord("Roger_1", "10");
		npchar.dialog.currentnode = "Mtr_rosario_7";
		break;

	case "Mtr_rosario_7":
		dialog.text = "¿Trajiste el dinero?";
		if (PCharDublonsTotal() >= 250) // belamour legendary edition
		{
			link.l1 = "Tengo la suma requerida conmigo ahora mismo. Aquí, que se atragante este burgués avaricioso con ella.";
			link.l1.go = "Mtr_rosario_4";
		}
		link.l2 = "Sigo en ello.";
		link.l2.go = "Mtr_rosario_7_1";
		break;

	case "Mtr_rosario_7_1":
		DialogExit();
		npchar.dialog.currentnode = "Mtr_rosario_7";
		break;

	case "Mtr_rosario_8":
		dialog.text = "Llevaré el dinero al maldito astuto esta noche. Creo que tendrán una orden para la liberación de nuestro amigo al mediodía. ¿Y espero que nos reunamos más tarde para celebrar?";
		link.l1 = "Claro, don Rosario. Debo irme ahora. ¡Hasta luego!";
		link.l1.go = "Mtr_rosario_9";
		break;

	case "Mtr_rosario_9":
		DialogExit();
		AddQuestRecord("Roger_1", "11");
		npchar.lifeday = 1;
		SaveCurrentNpcQuestDateParam(NPChar, "LifeTimeCreate");
		npchar.dialog.currentnode = "Mtr_rosario_10";
		pchar.quest.mtr_prisoner.win_condition.l1 = "Timer";
		pchar.quest.mtr_prisoner.win_condition.l1.date.hour = 12;
		pchar.quest.mtr_prisoner.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.mtr_prisoner.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.mtr_prisoner.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.mtr_prisoner.function = "Mtraxx_PrisonerFree";
		break;

	case "Mtr_rosario_10":
		dialog.text = "¡Pronto nuestro amigo será libre!";
		link.l1 = "...";
		link.l1.go = "exit";
		npchar.dialog.currentnode = "Mtr_rosario_10";
		break;

	// Лысый Джеффри
	case "Jeffry":
		pchar.quest.Mtraxx_SilkCPVOver.over = "yes"; // снять прерывание
		dialog.text = "¿Eh, qué demonios haces en mi barco? No creo que hayas recibido mi invitación, ¿eh?";
		link.l1 = "Calma, Geffrey. Soy de Tyrex respecto al negocio de la seda del barco.";
		link.l1.go = "Jeffry_1";
		break;

	case "Jeffry_1":
		dialog.text = "¡A-ah, bueno, hablemos entonces! ¿Qué está planeando? Ya he hablado con los contrabandistas, si me preguntas, ofrecen un buen precio por las mercancías...";
		link.l1 = "¿Y cuánto, si puedo preguntar?";
		link.l1.go = "Jeffry_2";
		break;

	case "Jeffry_2":
		dialog.text = "1300 pesos por un rollo. Creo que es un buen precio.";
		link.l1 = "Sí, y Tyrex quiere veinte piezas de oro por un rollo. Ni una moneda menos. Y me refiero a doblones. Me dio un trabajo para encontrar un comprador adecuado por ese precio.";
		link.l1.go = "Jeffry_3";
		break;

	case "Jeffry_3":
		dialog.text = "Ja-ja-ja, ¡chico, qué suerte tienes! ¡Marcus sí que tiene apetito! Bueno, ve a encontrar un comprador así, sería glorioso verte intentarlo.";
		link.l1 = "Sí, todo esto es muy jodidamente gracioso y desternillante. ¿Parezco feliz? No. Así que te sugiero que dejes de reírte y me eches una mano.";
		link.l1.go = "Jeffry_4";
		break;

	case "Jeffry_4":
		dialog.text = "Está bien, está bien, amigo... Jesús, no eres muy aficionado a las bromas, ¿eh? Pero lo entiendo, no se te puede culpar por las fantasías de Tyrex, todos obtendremos nuestra parte de esto, créeme. ¿Y cómo podría ayudarte yo? No puedes venderlo en las tiendas, la aduana tampoco es una opción, solo quedan los contrabandistas. ¿Quién más lo necesita? ¿Tienes alguna idea?";
		link.l1 = "He estado pensando en ello desde La Española... Lo que sea. Solo tengo dos meses para encontrar un comprador regular. Algo debe hacerse al respecto. Tus órdenes son desembarcar en la bahía más cercana y hacer reparaciones.";
		link.l1.go = "Jeffry_5";
		break;

	case "Jeffry_5":
		dialog.text = "¿Dos meses?! ¿Qué demonios? Ah, al diablo. La 'Serpiente' sí necesita una reparación y limpieza o no podrá perseguir ni siquiera un bergantín. ¡Eh, putas francesas! ¡La tripulación de Geffrey el Calvo se queda en Capsterville por dos meses! ¡Ja-ja-ja! Pues buena suerte, amigo, en esas búsquedas inútiles tuyas. Si encuentras a un idiota dispuesto a pagar el precio de Marcus por esta maldita seda, ya sabes dónde encontrarme.";
		link.l1 = "¡Espera! Dame un rollo de esta seda. Necesito mostrar las mercancías a los posibles compradores.";
		link.l1.go = "Jeffry_6";
		break;

	case "Jeffry_6":
		dialog.text = "Claro, ningún problema. Puedes llevarlo contigo en un bote... ¡Eh, muchachos! ¡Echad un fardo de seda en el bote del capitán!";
		link.l1 = "Bien. Bueno, ¡te veré cuando encuentre al comprador!";
		link.l1.go = "Jeffry_7";
		break;

	case "Jeffry_7":
		DialogExit();
		AddQuestRecord("Roger_2", "3");
		npchar.DeckDialogNode = "Jeffry_8";
		npchar.dialog.currentnode = "Jeffry_8";
		pchar.questTemp.Mtraxx = "silk_2";
		AddCharacterGoods(pchar, GOOD_SHIPSILK, 1);
		if (bImCasual)
			NewGameTip("Modo exploración: el temporizador no está desactivado. ¡Cumple el plazo!");
		SetFunctionTimerCondition("Mtraxx_SilkTimeOver", 0, 0, 61, false); // таймер
		break;

	case "Jeffry_8":
		dialog.text = "¿Algo más, amigo?";
		link.l1 = "Nada por el momento...";
		link.l1.go = "Jeffry_8_1";
		break;

	case "Jeffry_8_1":
		DialogExit();
		npchar.DeckDialogNode = "Jeffry_8";
		npchar.dialog.currentnode = "Jeffry_8";
		break;

	case "Jeffry_9":
		pchar.quest.Mtraxx_SilkTimeOver.over = "yes";
		dialog.text = "¿Cómo te va, amigo?";
		link.l1 = "Haciendo muy bien. He encontrado un comprador. Veinticinco doblones por un rollo. Creo que a Tyrex le gustará.";
		link.l1.go = "Jeffry_10";
		break;

	case "Jeffry_10":
		dialog.text = "¡De ninguna manera! ¡Eres el ingenioso hijo de un diablo! ¿Cómo lograste eso, eh?";
		link.l1 = "Es una larga historia, Geffrey. Ahora escucha. Debes llegar a Cabo Negril de Jamaica entre el 10 y el 15. Te estarán esperando allí por las noches. La contraseña es 'Un comerciante de Lyon'. ¿Entendido? Repite.";
		link.l1.go = "Jeffry_11";
		break;

	case "Jeffry_11":
		dialog.text = "Un mercader de Lyon. Lo tengo. Debería decirle a mi intendente que lo anote, él es el único hombre aquí que sabe escribir. ¡Ja-ja!";
		link.l1 = "¿Tienes cien rollos en la bodega de carga?";
		link.l1.go = "Jeffry_12";
		break;

	case "Jeffry_12":
		dialog.text = "Tengo aún más.";
		link.l1 = "Espléndido. Es hora de que levantes velas entonces. ¡No me defraudes!";
		link.l1.go = "Jeffry_13";
		break;

	case "Jeffry_13":
		dialog.text = "Relájate, camarada, todo se hará como debe hacerse.";
		link.l1 = "Vaya con Dios, Geffrey. Tal vez nos volvamos a encontrar.";
		link.l1.go = "Jeffry_14";
		break;

	case "Jeffry_14":
		DialogExit();
		AddQuestRecord("Roger_2", "22");
		pchar.questTemp.Mtraxx = "silk_14"; // к Тираксу
		sld = characterFromId("Terrax");
		sld.dialog.currentnode = "mtraxx_12";
		pchar.quest.mtraxx_hide_jeffry.win_condition.l1 = "MapEnter";
		pchar.quest.mtraxx_hide_jeffry.function = "Mtraxx_SilkHideJeffry";
		break;

	case "Jeffry_15":
		dialog.text = "¡Jo-jo-jo! ¡El astuto Charlie Prince, en carne y hueso! ¡Qué bueno verte de nuevo, camarada!";
		link.l1 = "¡Geffrey el Calvo! ¿Charlie Prince has dicho? ¡Ja!";
		link.l1.go = "Jeffry_15x";
		break;

	case "Jeffry_15x":
		dialog.text = "¿Nunca antes escuchaste tu segundo nombre? Así te llaman ahora en La Vega.";
		link.l1 = "Veo de dónde viene Charlie, pero ¿por qué Prince?";
		link.l1.go = "Jeffry_15y";
		break;

	case "Jeffry_15y":
		dialog.text = "¡Bueno, eres el único hijo de noble perra en La Vega! ¡Ja-ja-ja! ¿Cómo te va? ¿Has estado en la tienda de Pasquale? ¿Compraste suministros del viejo sinvergüenza?";
		link.l1 = "¡Nunca más!";
		link.l1.go = "Jeffry_16";
		break;

	case "Jeffry_16":
		dialog.text = "¡Ja-ja! ¿Por qué, no te gustó? ¿Te vendió carne salada al precio del ron?";
		link.l1 = "¡Peor! Me dio una pista sobre una caravana holandesa cargada de ébano. ¡No fue fácil encontrarla, abordar al mercante y luego proteger esa maldita madera de unas cuantas docenas de ratas! ¿Y adivina qué? ¡El bastardo me pagó 150 pesos por pieza. Por una pieza de maldito ébano, Geffrey!";
		link.l1.go = "Jeffry_17";
		break;

	case "Jeffry_17":
		dialog.text = "Sucede todo el tiempo, amigo, te lo aseguro. Lavoisier ya ha jodido a una docena de buenos muchachos como tú. En realidad, te pagó algo, lo cual es raro para él. No tomamos sus 'pistas' ni siquiera si nos estamos muriendo de hambre.";
		link.l1 = "Gracias, amigo mío, al menos ahora sé que no fui el primer ni el único idiota. ¡Pero esta vez el bastardo se ha jodido a sí mismo! Me aseguraré de que se arrepienta del día en que me vio.";
		link.l1.go = "Jeffry_18";
		break;

	case "Jeffry_18":
		dialog.text = "¡Eh-eh-eh! Espera, Prince, cálmate un poco. El buhonero es intocable aquí. Atrévete a saquearlo – Marcus te tendrá en la mira. Dime, ¿fue Tyrex quien te envió a Lavoisier?";
		link.l1 = "Mm. Sí... ¿Por qué?";
		link.l1.go = "Jeffry_19";
		break;

	case "Jeffry_19":
		dialog.text = "Escucha... (bajando la voz) Dicen que el cuatro-ojos comparte con Marcus. ¿Me entiendes ahora? Por eso ningún pirata se atreverá a atacar los barcos de Lavoisier, de lo contrario están acabados.";
		link.l1 = "Anotado. ¡Gracias por la advertencia, Geffrey. ¡Adiós y que Dios te acompañe!";
		link.l1.go = "Jeffry_20";
		break;

	case "Jeffry_20":
		dialog.text = "Lo mismo para ti, amigo.";
		link.l1 = "...";
		link.l1.go = "Jeffry_21";
		break;

	case "Jeffry_21":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "OpenTheDoors", 15.0);
		AddQuestRecord("Roger_4", "10");
		CloseQuestHeader("Roger_4");
		QuestSetCurrentNode("Terrax", "mtraxx_34"); // релиз-правка
		bDisableFastReload = false;
		pchar.questTemp.Mtraxx.CharleePrince = "true"; // атрибут - ГГ известный пират
		pchar.questTemp.CharleePrince = true;		   // атрибут для найма команды
		break;

	case "Jeffry_22":
		dialog.text = "¡Jo-jo-jo Prince! ¡Me preguntaba quién hizo los fuegos artificiales! Traje un escuadrón de mosqueteros por si eran los españoles.";
		link.l1 = "¿Geffrey? ¿Tú también estás aquí? ¿Pero cómo? ¿Compraste el mapa del tesoro también?";
		link.l1.go = "Jeffry_23";
		QuestPointerDelLoc("Judgement_dungeon_05", "reload", "reload1");
		QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload1");
		break;

	case "Jeffry_23":
		dialog.text = "Amigo, no malgasto mi dinero en porquerías así. Me entregaron el diario de un viajero que escribió sobre un paso seguro a estas mazmorras.";
		link.l1 = "¿Quién te lo trajo?";
		link.l1.go = "Jeffry_24";
		break;

	case "Jeffry_24":
		dialog.text = "Algún adicto. Todo lo que necesitaba eran cien pesos para un trago.";
		link.l1 = "¿Ocurrió en Tortuga?";
		link.l1.go = "Jeffry_25";
		break;

	case "Jeffry_25":
		dialog.text = "¿No? ¿Era Barbados? ¡Prince! ¿Por qué te preocupas tanto? ¡Cuantos más seamos, más rápido podremos llevar los tesoros!";
		link.l1 = "No me gusta esto. No creo en coincidencias así. ¿Podría ser el padre de Camilla quien escribió este diario?";
		link.l1.go = "Jeffry_26";
		break;

	case "Jeffry_26":
		dialog.text = "¿Quién es Camilla?";
		link.l1 = "¡La moza que me vendió un mapa de este lugar por doscientos pesos!";
		link.l1.go = "Jeffry_27";
		break;

	case "Jeffry_27":
		dialog.text = "Heh... Prince, piensas demasiado. Vamos a buscar tesoros. ¡Vamos!";
		link.l1 = "No hay necesidad. Ya los he encontrado... Están abajo en el calabozo, tras rejas de hierro. Tendremos que romperlas. Escucha, Geffrey, ¡hay algo más! ¡Pelly el Sable también estuvo aquí!";
		link.l1.go = "Jeffry_28";
		break;

	case "Jeffry_28":
		dialog.text = "¿Sable? ¡Pues entonces es nuestro día de suerte! Pero, ¿dónde está él ahora?";
		link.l1 = "Abajo... muerto. Lo encontré cerca del tesoro. Se volvió loco, empezó a gritar de codicia. Luego él y sus compañeros me atacaron.";
		link.l1.go = "Jeffry_29";
		break;

	case "Jeffry_29":
		dialog.text = "Mm... Pelly siempre tuvo mala suerte con el dinero. Debió volverse loco al ver la carga de oro.";
		link.l1 = "Puede ser así... ¡pero Geffrey, no lo entiendes! ¡Todos los tres llegamos aquí! ¡Y todos obtuvimos la misma pista! ¿Crees que fue por casualidad? Alguien claramente quiere que estemos todos en un solo lugar, y este lugar de verdad se siente como una tumba.";
		link.l1.go = "Jeffry_30";
		break;

	case "Jeffry_30":
		dialog.text = "¿Viste el oro, sin embargo?";
		link.l1 = "Lo vi con mis propios ojos. Varios cofres gigantes llenos de monedas y lingotes.";
		link.l1.go = "Jeffry_31";
		break;

	case "Jeffry_31":
		dialog.text = "Entonces, ¿por qué te preocupas, Prince? Guía el camino, echemos un vistazo a tus barras. Luego compartiremos el oro.";
		link.l1 = "Ah,  tal vez tengas razón,  lo que sea...  Vámonos.";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_RetributionWithJeffry");
		break;

	case "Jeffry_32":
		PlaySound("Voice\Spanish\LE\Jeffry\Jeffry_gold.wav");
		dialog.text = "¡Sí! ¡Esto sí que es algo memorable! ¡Menudo montón de oro! Ahora veo por qué Cutlass se volvió loco. ¡Somos muy afortunados, Prince! ¿Qué piensas, cuánto oro encontraremos aquí?";
		link.l1 = "Mucho. Lo sabremos con certeza cuando nos encarguemos de estas rejas.";
		link.l1.go = "Jeffry_33";
		break;

	case "Jeffry_33":
		dialog.text = "Sí, la celosía es muy fuerte, no la romperemos con las manos desnudas ni con espadas. Tienes razón, camarada - necesitamos encontrar algunas herramientas o mucha pólvora. ¡Oye, mira! ¿Qué es eso?";
		link.l1 = "...";
		link.l1.go = "Jeffry_34";
		break;

	case "Jeffry_34":
		DialogExit();
		LAi_SetActorType(pchar);
		DoQuestCheckDelay("Mtraxx_RetributionJeffryMushketer", 0.1);
		break;

	case "Jeffry_35":
		PlaySound("Voice\Spanish\LE\Jeffry\Jeffry_mozila.wav");
		dialog.text = RandSwear() + "¡Vaya que eres torpe y descuidado! ¡Has fallado!";
		link.l1 = "¡Maldita serpiente!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_RetributionJeffryFight");
		break;

	// Билли Сипатый
	case "Billy":
		pchar.quest.Mtraxx_BillySeaTimeOver.over = "yes"; // снять таймер
		PlaySound("VOICE\Spanish\LE\Billy\Billy_01.wav");
		dialog.text = "¡Que el tiburón me trague si ha pasado en el 'Pez Volador' este año... chicos, tenemos un invitado aquí! ¿Qué negocio malvado te trae a vieja nena?";
		link.l1 = "¡Saludos! Eres el que llaman Billy el Ronco, ¿no es así?";
		link.l1.go = "Billy_1";
		break;

	case "Billy_1":
		dialog.text = "¿No puedes adivinar por mi voz, capitán? Hace tiempo podía hacer que los mercaderes británicos y españoles se cagaran en los pantalones. ¡Tiempos gloriosos aquellos! Ahora el viejo Billy espera el final de su vida cerca de las costas de su isla favorita en su preciada chalupa...";
		link.l1 = "Tengo un negocio para ti, Billy. Me dijeron que sabes todo lo que sucede aquí alrededor de Jamaica. ¿Es eso cierto?";
		link.l1.go = "Billy_2";
		break;

	case "Billy_2":
		dialog.text = "Si te lo dijeron, entonces debe ser así, ¿no crees? No tires de un cangrejo por las bolas, habla. ¿Qué negocio tienes para mí?";
		link.l1 = "Muy bien. Hay un constructor de barcos en Port Royal. Proporciona a sus clientes servicios especiales, y necesita seda de barco para su producción y dichos servicios. Dado que comerciar con esta mercancía es ilegal aquí, se ha encontrado un vendedor ilegal. Quiero saber quién y cómo le está proporcionando seda de barco.";
		link.l1.go = "Billy_3";
		break;

	case "Billy_3":
		dialog.text = "¡Jo-jo-jo, mira esto! ¿Trabajando para el coronel D'Oyley, hijo?";
		link.l1 = "¡Aquí vamos de nuevo! No, trabajo con Marcus Tyrex. Quiere una parte en el mercado de la seda de barcos y este constructor naval está cagado de miedo para tratar con gente 'desconocida'...";
		link.l1.go = "Billy_4";
		break;

	case "Billy_4":
		dialog.text = "¡Oh, trabajas para el Guardián del Código! Estas son grandes noticias... si no estás mintiendo, por supuesto. Me importa un bledo los constructores de barcos, arresta a uno - vendrá otro. Me importa un comino mi vieja. El 'Pez Volador' está en mal estado. ¿Me entiendes?\nTráeme otro bote largo, uno nuevo, y un rollo de seda de barco, del mismo tipo del que hablas - Billy hará una vela decente con ella para poder burlarse de las patrullas, ¡ja-ja-ja! A cambio, Billy contará todo sobre el constructor de barcos y su fuente de seda. Confía en mí, hijo, sé todo lo que quieres saber, solo tengo que asegurarme de que eres un pirata honesto y no un lameculos de casaca roja.";
		link.l1 = "¿Un nuevo bote largo? ¿Qué tal si te doy suficiente dinero para comprarlo tú mismo? Incluso añadiré un extra.";
		link.l1.go = "Billy_5";
		break;

	case "Billy_5":
		dialog.text = "Je-je, capitán, el viejo Billy no es bienvenido en la ciudad. Me recuerdan demasiado bien en Port Royal y no me hace gracia la idea de ser colgado entre mis viejos amigos en esa roca. Así que, hijo, estoy esperando que me entregues un nuevo bote largo. Estaré esperando tres días en el Cabo Negril. ¡Y no te olvides de la seda!";
		link.l1 = "Muy bien, Billy. Tendrás tu bote largo y un rollo de seda de barco. Volveré pronto.";
		link.l1.go = "Billy_6";
		break;

	case "Billy_6":
		dialog.text = "Muy bien, Billy te estará esperando en la orilla, capitán. ¡Hasta pronto!";
		link.l1 = "...";
		link.l1.go = "Billy_7";
		break;

	case "Billy_7":
		DialogExit();
		AddQuestRecord("Roger_2", "8");
		npchar.dialog.currentnode = "Billy_8";
		pchar.questTemp.Mtraxx = "silk_7";
		SetFunctionTimerCondition("Mtraxx_BillyTimeOver", 0, 0, 3, false); // таймер
		pchar.quest.mtr_billy_coast.win_condition.l1 = "ExitFromLocation";
		pchar.quest.mtr_billy_coast.win_condition.l1.location = pchar.location;
		pchar.quest.mtr_billy_coast.function = "Mtraxx_BillyOnCoast";
		locations[FindLocation("shore35")].DisableEncounters = true; // энкаутеры закрыть
		npchar.DontDeskTalk = true;
		if (bImCasual)
			NewGameTip("Modo exploración: el temporizador no está desactivado. ¡Cumple el plazo!");
		break;

	case "Billy_8":
		PlaySound("VOICE\Spanish\LE\Billy\Billy_02.wav");
		dialog.text = "¿Qué? ¿Ya me has traído una barcaza?";
		link.l1 = "Eres un muchacho bromista, ¿eh, Billy?";
		link.l1.go = "exit";
		break;

	case "Billy_9":
		dialog.text = "Entonces, capitán, ¿qué hay de mi nueva barcaza?";
		if (Companion_CheckShipType(SHIP_TARTANE) && GetSquadronGoods(pchar, GOOD_SHIPSILK) > 0)
		{
			link.l1 = "Está hecho, Husky. Ella ha sido entregada junto con un rollo de seda de barco en su bodega. Eres libre de hundir tu vieja bañera.";
			link.l1.go = "Billy_11";
		}
		else
		{
			PlaySound("VOICE\Spanish\LE\Billy\Billy_02.wav");
			link.l1 = "Todavía estoy en ello. Espera.";
			link.l1.go = "Billy_10";
		}
		break;

	case "Billy_10":
		DialogExit();
		npchar.dialog.currentnode = "Billy_9";
		break;

	case "Billy_11":
		PlaySound("VOICE\Spanish\LE\Billy\Billy_03.wav");
		pchar.quest.Mtraxx_BillyTimeOver.over = "yes"; // снять прерывание
		dialog.text = "¡Maldita sea! ¡Eso es lo mejor que ha escuchado el Viejo Billy, en los últimos 3 años! Je, una buena razón para descorchar esta botella...";
		link.l1 = "Paso. Entonces, ¿sobre el proveedor de seda?";
		link.l1.go = "Billy_12";
		break;

	case "Billy_12":
		dialog.text = "Qué lástima, podríamos beber por mi nuevo y flamante 'Pez Volador'! De todos modos... Escucha, hijo\nUn bergantín bajo la bandera inglesa llega a Portland Cove a mediados de cada mes, entre el 10 y el 15. ¡No beberé ron hasta estar muerto si de verdad es inglés! Su nombre es el 'Utrecht' y llega desde el suroeste, donde se encuentra Curazao. Es claramente un barco holandés, capitán, puedes ver eso\nSiempre el mismo grupo de personas los recibe en la orilla, liderado por un astuto maestro constructor de barcos. Él es el receptor de la seda de barco que los holandeses descargan allí. Estoy seguro de que es la seda de barco, ya que solo los holandeses la embalan así.";
		link.l1 = "¿Cada mes dijiste?";
		link.l1.go = "Billy_13";
		break;

	case "Billy_13":
		dialog.text = "En efecto, mi chico, ni un solo mes perdido durante el último año. Si quieres charlar con esta sombría compañía barbuda, te sugiero que los esperes en Portland Cove del 10 al 15 de cada mes por las noches. ¡Lo juro por la fresca y nueva vela de seda de mi bote largo!";
		link.l1 = "¡Je! Parece que mi dinero fue gastado por una razón. Buena suerte, Billy, asegúrate de mantener tu viejo trasero a salvo de las patrullas, de lo contrario me harás realmente enfadar.";
		link.l1.go = "Billy_14";
		break;

	case "Billy_14":
		dialog.text = "¡Ja, el viejo Billy está a punto de divertirse de verdad por las costas de Jamaica! ¡Buen viento, capitán! ¡Buena caza!";
		link.l1 = "Lo mismo para ti, Billy!";
		link.l1.go = "Billy_15";
		break;

	case "Billy_15":
		DialogExit();
		npchar.lifeday = 0;
		pchar.questTemp.Mtraxx = "silk_8";
		chrDisableReloadToLocation = true;							  // закрыть локацию
		locations[FindLocation("shore35")].DisableEncounters = false; // энкаутеры открыть
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
		AddDialogExitQuestFunction("Mtraxx_BillyTakeShip");
		AddQuestRecord("Roger_2", "9");
		//
		if (GetDataDay() >= 1 && GetDataDay() <= 9)
		{
			DoQuestFunctionDelay("Mtraxx_SilkCreateSmuggler", 1.0);
		}

		if (GetDataDay() >= 10 && GetDataDay() <= 15)
		{
			int iRank = sti(pchar.rank) + MOD_SKILL_ENEMY_RATE + 2;
			if (iRank > 45)
				iRank = 45;
			Group_FindOrCreateGroup("Mtr_Utreht");
			sld = GetCharacter(NPC_GenerateCharacter("Cap_Utreht", "mercen_19", "man", "man", iRank, ENGLAND, -1, true, "quest"));
			FantomMakeCoolSailor(sld, SHIP_BRIGANTINE, "Utrecht", CANNON_TYPE_CULVERINE_LBS18, 50, 50, 50);
			FantomMakeCoolFighter(sld, iRank, 50, 50, "blade_13", "pistol5", "bullet", 100);
			sld.name = "Joachim";
			sld.lastname = "Gusen";
			sld.DontRansackCaptain = true;
			sld.AnalizeShips = true;
			sld.Coastal_Captain = true; // правки прогона 3
			DeleteAttribute(sld, "SaveItemsForDead");
			sld.Ship.Mode = "pirate";
			SetSailsColor(sld, 2);
			sld.ship.Crew.Morale = 40 + MOD_SKILL_ENEMY_RATE * 4;
			sld.Ship.Crew.Exp.Sailors = 60 + MOD_SKILL_ENEMY_RATE * 4;
			sld.Ship.Crew.Exp.Cannoners = 40 + MOD_SKILL_ENEMY_RATE * 4;
			sld.Ship.Crew.Exp.Soldiers = 40 + MOD_SKILL_ENEMY_RATE * 4;
			if (MOD_SKILL_ENEMY_RATE > 4)
				SetCharacterPerk(sld, "MusketsShoot");
			SetCharacterGoods(sld, GOOD_SHIPSILK, 80);

			Group_AddCharacter("Mtr_Utreht", "Cap_Utreht");
			Group_SetGroupCommander("Mtr_Utreht", "Cap_Utreht");
			Group_SetTaskAttackInMap("Mtr_Utreht", PLAYER_GROUP);
			Group_SetAddress("Mtr_Utreht", "Jamaica", "Quest_Ships", "Quest_Ship_4");
			Group_SetTaskRunaway("Mtr_Utreht", PLAYER_GROUP);
			Group_LockTask("Mtr_Utreht");

			pchar.quest.mtr_silksmuggler_AfterBattle.win_condition.l1 = "Group_Death";
			pchar.quest.mtr_silksmuggler_AfterBattle.win_condition.l1.group = "Mtr_Utreht";
			pchar.quest.mtr_silksmuggler_AfterBattle.function = "Mtraxx_SilkSmugglerAfterBattle";

			SetTimerFunction("Mtraxx_SilkSmugglerFail", 0, 0, 2);
		}

		if (GetDataDay() >= 16 && GetDataDay() <= 20)
		{
			SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 15);
		}
		if (GetDataDay() >= 21 && GetDataDay() <= 26)
		{
			SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 10);
		}
		if (GetDataDay() >= 27 && GetDataDay() <= 31)
		{
			SetTimerFunction("Mtraxx_SilkCreateSmuggler", 0, 0, 5);
		}
		break;

	// мастеровой с верфи Порт-Ройаля
	case "Mtr_acceptor_fight":
		LAi_group_Delete("EnemyFight");
		DialogExit();
		chrDisableReloadToLocation = true;
		LAi_LocationFightDisable(&Locations[FindLocation("shore36")], false);
		for (i = 1; i <= 4; i++)
		{
			sld = characterFromId("Mtr_acceptor_" + i);
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
		}
		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
		LAi_group_SetCheck("EnemyFight", "Mtraxx_SilkWrongTalk");
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "Mtr_acceptor":
		dialog.text = "Hola, marinero, ¿acabas de llegar a Jamaica, eh?";
		link.l1 = "Mm. Correcto. ¿Qué pasa?";
		link.l1.go = "Mtr_acceptor_1";
		break;

	case "Mtr_acceptor_1":
		dialog.text = "¿Has visto algo ocurrido en el mar cercano?";
		link.l1 = "Sí, lo he hecho. Un bergantín se enfrentó en combate con una corbeta de patrulla inglesa. Los británicos les dieron duro, los holandeses se deshicieron de su carga en un intento de huir.";
		link.l1.go = "Mtr_acceptor_2";
		break;

	case "Mtr_acceptor_2":
		dialog.text = "¿Por qué estás tan seguro de que ella era holandesa? Ningún holandés en su sano juicio siquiera pensaría en acercarse tanto a Port Royal...";
		link.l1 = "Tenía colores ingleses, pero el nombre... El 'Utrecht'. No muy británico, ¿eh? Eran holandeses, te digo, tal vez incluso contrabandistas. La patrulla seguramente los esperaba.";
		link.l1.go = "Mtr_acceptor_3";
		break;

	case "Mtr_acceptor_3":
		dialog.text = "¡Maldición!";
		link.l1 = "Parece que no estás exactamente contento con esto...";
		link.l1.go = "Mtr_acceptor_4_1";
		link.l2 = "¿Habías estado esperando por este bergantín aquí?";
		link.l2.go = "Mtr_acceptor_7";
		break;

	case "Mtr_acceptor_4_1":
		dialog.text = "¿Por qué lo estaría?";
		link.l1 = "Vamos. Sé quién eres. Eres un capataz del astillero de Port Royal y estás esperando que la goleta entregue la carga muy especial.";
		link.l1.go = "Mtr_acceptor_wrong";
		link.l2 = "¡Lo tienes escrito en la cara, justo ahí!";
		link.l2.go = "Mtr_acceptor_4_2";
		break;

	case "Mtr_acceptor_wrong":
		dialog.text = "¡Argh! ¡Chicos, esto es una patrulla disfrazada! ¡Acábalos y salgamos de aquí al infierno!";
		link.l1 = "¡Mierda! Espera, estás equivoc...";
		link.l1.go = "Mtr_acceptor_fight";
		break;

	case "Mtr_acceptor_4_2":
		dialog.text = "¿Siendo grosero, 'lobo de mar'? Cuida tu lengua o...";
		link.l1 = "Vamos. Obviamente pareces molesto. ¿Estabas realmente esperando a que llegaran esos holandeses?";
		link.l1.go = "Mtr_acceptor_4_3";
		link.l2 = "¿O qué? ¿Me darás una lección de vida?";
		link.l2.go = "Mtr_acceptor_6";
		break;

	case "Mtr_acceptor_4_3":
		dialog.text = "¿Y qué si lo fuera? ¿Por qué te importa?";
		if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
		{
			link.l1 = "No, realmente. Tú eres el que espera aquí, no yo. Tienes una eternidad por delante.";
			link.l1.go = "Mtr_acceptor_4_4";
		}
		link.l2 = "Oh, tengo todas las razones para preocuparme. Sé lo que había dentro de la bodega del bergantín. Seda de barco. Estás aquí por eso, ¿verdad?";
		link.l2.go = "Mtr_acceptor_wrong";
		break;

	case "Mtr_acceptor_4_4":
		dialog.text = "¿Hm... Eternidad?";
		link.l1 = "Se necesita una eternidad para regresar del fondo del mar. Tu bergantín fue hundido por una corbeta de patrulla, compadre. Así de simple. Aunque, la guerra trae tanto premios como pérdidas. Haré una buena moneda con ese holandés hundido.";
		link.l1.go = "Mtr_acceptor_4_5";
		break;

	case "Mtr_acceptor_4_5":
		dialog.text = "¿Y cómo exactamente, me pregunto?";
		link.l1 = "Venderé lo que arrojaron por la borda mientras intentaban huir. Casi todo está perdido, pero la preciosa seda del barco flotaba como... corcho. He rescatado la mayor parte, así que mañana me dirijo a la ciudad para encontrar un comprador. Nunca se sabe dónde se ganará y dónde se perderá.";
		link.l1.go = "Mtr_acceptor_4_6";
		break;

	case "Mtr_acceptor_4_6":
		dialog.text = "¡Espera!";
		link.l1 = "¡Caramba! ¿Y ahora qué?";
		link.l1.go = "Mtr_acceptor_4_7";
		break;

	case "Mtr_acceptor_4_7":
		dialog.text = "¿Cuánta seda lograste reunir?";
		link.l1 = "¿Y por qué te importa? ¡Esta es mi seda! ¿O eres el perro del gobernador? Tú eres de...";
		link.l1.go = "Mtr_acceptor_4_8";
		break;

	case "Mtr_acceptor_4_8":
		dialog.text = "Mantén tu espada envainada, marinero. No soy un perro y no soy un soplón. Trabajamos en el astillero... Esta seda era para nosotros y, según entiendo, ahora la tienes tú. Te la compraré toda, necesitamos esta seda, compadre.";
		link.l1 = "¿De verdad? Interesante... ¿Cuánto?";
		link.l1.go = "Mtr_acceptor_4_9";
		break;

	case "Mtr_acceptor_4_9":
		i = GetSquadronGoods(pchar, GOOD_SHIPSILK);
		dialog.text = "Dos mil quinientos por un rollo. Es un buen precio, no encontrarás mejor.";
		link.l1 = "¡Parece que tuve suerte! Tengo " + FindRussianQtyString(i) + "Muéstrame el dinero y ordenaré que lo entreguen en la orilla ahora mismo.";
		if (i > 80)
			link.l1.go = "Mtr_acceptor_4_11";
		else
			link.l1.go = "Mtr_acceptor_4_10";
		break;

	case "Mtr_acceptor_4_10":
		dialog.text = "¡Trato hecho!";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_CargoSilk");
		AddCharacterExpToSkill(pchar, "Fortune", 300); // везение
		AddCharacterExpToSkill(pchar, "Sneak", 300);   // скрытность
		break;

	case "Mtr_acceptor_4_11":
		dialog.text = "Hm... Joachim se suponía que debía entregar solo ochenta rollos - no hay manera de que pudieras rescatar tanto... lo que significa que o estás tratando de jugar un juego sucio aquí o... ¡eres un chivato! ¡Chicos, mátenlo y salgan de aquí al diablo!";
		link.l1 = "¡Maldición!";
		link.l1.go = "Mtr_acceptor_fight";
		break;

	case "Mtr_acceptor_5":
		dialog.text = "";
		link.l1 = "¡Un trato espléndido, camarada! ¿Por qué tan sombrío? ¿Preocupado por los holandeses en el fondo del mar? ¡Las cosas pasan, no te preocupes por eso!";
		link.l1.go = "Mtr_acceptor_5_1";
		break;

	case "Mtr_acceptor_5_1":
		dialog.text = "Sí, claro... Ellos eran nuestros proveedores habituales. ¿Dónde se supone que conseguiremos la seda ahora? Siempre estamos escasos de ella y todo el comercio está bajo el control directo del coronel D'Oyley. Bah, maldición...";
		link.l1 = "Hm... Escucha, amigo, supongo que puedo ayudarte con eso.";
		link.l1.go = "Mtr_acceptor_5_2";
		break;

	case "Mtr_acceptor_5_2":
		dialog.text = "¿Oh, de verdad? ¿Y cómo imaginas ayudarnos? ¿Nos entregarás un lote de cien rollos cada mes?";
		link.l1 = "¿Yo? Hmm, probablemente no, pero Marcus Tyrex lo haría. ¿Has oído hablar de él?";
		link.l1.go = "Mtr_acceptor_5_3";
		break;

	case "Mtr_acceptor_5_3":
		dialog.text = "¡K-ja! Entonces, ¿eres un pirata?";
		link.l1 = "No, solo hago negocios con ellos en ocasiones especiales. Sé con certeza que Marcus recibe lotes de seda de barco de manera constante y se la vende a cualquiera que pueda pagarla. Y no estoy hablando de 2500 pesos por un rollo aquí, diría que si puedes pagarle 25 doblones de oro por cada rollo, te ahogará en ellos, puedes contar con eso.";
		link.l1.go = "Mtr_acceptor_5_4";
		break;

	case "Mtr_acceptor_5_4":
		dialog.text = "Estas son noticias interesantes... ¿Marcus Tyrex dices? ¿Solo en doblones?..";
		link.l1 = "Vamos, amigo, ¿realmente te importa de quién obtienes tu seda? Y el dinero es dinero, siempre puedes cambiar pesos por doblones en un banco. Entonces, ¿qué tal si susurro una o dos palabras sobre ti en los oídos del guardián del código? De todos modos, voy a La Vega.";
		link.l1.go = "Mtr_acceptor_5_5";
		break;

	case "Mtr_acceptor_5_5":
		dialog.text = "Muy bien. Hagamos un trato. Estos son nuestros términos: un lote de cien rollos cada mes entre el 10 y el 15. Estaremos esperando aquí... espera, cambiemos el punto de encuentro, este lugar está comprometido ahora. Estaremos esperando en Cabo Negril, cerca del pueblo Maroon, debería ser más seguro allí. La contraseña es: 'Un mercader de Lyon'.";
		link.l1 = "Trato hecho, amigo. ¡Vaya viaje infernal fue ese! ¡Tyrex me pagará un doblón o dos por un comprador así! ¡Ja-ja! Muy bien, debo irme. Espera la nave de Tyrex el próximo mes. ¡Buena suerte a ti y a tu familia!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
		break;

	case "Mtr_acceptor_6":
		dialog.text = "No necesitarás lecciones de vida después de que te enseñemos a ser cortés.";
		link.l1 = "¿Actuando duro, carpintero? Bien, sigue esperando por tu bergantín, aunque tardará un tiempo.";
		link.l1.go = "Mtr_acceptor_6_1";
		if (GetSquadronGoods(pchar, GOOD_SHIPSILK) >= 20)
		{
			link.l2 = "¡Oye, maestro, yo también tengo unas lecciones para ti!";
			link.l2.go = "Mtr_acceptor_6_2";
		}
		break;

	case "Mtr_acceptor_6_1":
		dialog.text = "¿Carpintero? ¡Maldita sea, cómo lo sabes? ¡K-ha! Demonios, muchachos, ¡esto es una patrulla disfrazada! ¡Mátenlo y salgamos de aquí al diablo!";
		link.l1 = "¡Mierda!";
		link.l1.go = "Mtr_acceptor_fight";
		break;

	case "Mtr_acceptor_6_2":
		dialog.text = "¡Déjanos en paz, escama de pescado, no tenemos tiempo. ¡Piérdete!";
		link.l1 = "¿Estás ocupado esperando un cierto navío holandés? Buena suerte con eso. Tienes una eternidad por delante.";
		link.l1.go = "Mtr_acceptor_4_4";
		break;

	case "Mtr_acceptor_7":
		dialog.text = "¿Qué diablos estás diciendo?";
		link.l1 = "Ya veo. Pero, por si acaso lo eres, olvídalo. No vendrá gracias a una corbeta de patrulla. Vi a través de un catalejo el final de una pelea. Ocurrió tan rápido y no muy lejos de aquí";
		link.l1.go = "Mtr_acceptor_7_1";
		break;

	case "Mtr_acceptor_7_1":
		dialog.text = "De nuevo, no estamos esperando nada ni a nadie y...";
		link.l1 = "Mira, realmente no me importa una mierda. No pertenezco a la patrulla de la ciudad y no me interesan tus asuntos, yo tampoco soy un ángel. Si estás contrabandeando, es asunto tuyo. Solo quería advertirte. Buena suerte, amigo.";
		link.l1.go = "Mtr_acceptor_7_2";
		break;

	case "Mtr_acceptor_7_2":
		dialog.text = "Espera... ¿Estás seguro de que el 'Utrecht' se ha hundido?";
		link.l1 = "Absolutamente. Intentó huir, arrojó todo lo que tenía en sus bodegas, ni siquiera escatimaron la preciosa seda del barco, pero tales medidas drásticas no pudieron ayudar contra la ventaja de velocidad de una corbeta.";
		link.l1.go = "Mtr_acceptor_7_3";
		break;

	case "Mtr_acceptor_7_3":
		dialog.text = "Qué pena... ¿y qué se supone que haremos sin la seda? ¡Maldita sea!";
		link.l1 = "¿Necesitas seda para el barco?";
		link.l1.go = "Mtr_acceptor_7_4";
		break;

	case "Mtr_acceptor_7_4":
		dialog.text = "¿Por qué preguntas, la estás vendiendo?";
		link.l1 = "No, pero conozco a un hombre que sí. Está buscando a un comprador generoso y regular. ¿Crees que puedes encajar?";
		link.l1.go = "Mtr_acceptor_7_5";
		break;

	case "Mtr_acceptor_7_5":
		dialog.text = "¿Y quién es ese hombre?";
		link.l1 = "Marcus Tyrex, el barón de La Vega, mejor conocido como el Guardián del Código. Recibe lotes de seda de barco de manera constante, así que siempre tiene algo para vender. Supongo que también considerará vendértela si tu precio es lo suficientemente alto.";
		link.l1.go = "Mtr_acceptor_7_6";
		break;

	case "Mtr_acceptor_7_6":
		dialog.text = "¿Entonces eres un pirata?";
		link.l1 = "¿Por qué te importa? Puedo arreglar un trato entre tú y Tyrex si tienes agallas para eso. Si no, adiós entonces.";
		link.l1.go = "Mtr_acceptor_7_7";
		break;

	case "Mtr_acceptor_7_7":
		dialog.text = "Está bien, está bien, no te enfades. Claro que sí. Quiero hacer un trato con Tyrex. Pero, ¿qué ganas tú con esto?";
		link.l1 = "Si ofreces un buen precio por la carga, probablemente recibiré de Marcus una suma decente por mi ayuda. Entonces, ¿qué será?";
		link.l1.go = "Mtr_acceptor_7_8";
		break;

	case "Mtr_acceptor_7_8":
		dialog.text = "Veinticinco doblones por un rollo. Ese es el mejor precio que puedes conseguir, confía en mí.";
		link.l1 = "¿Veinticinco monedas de oro? Hm. No está mal. Creo que Tyrex me deberá mucho por semejante comprador. Muy buen trato, se lo haré saber. Sin embargo, si me mentiste sobre el precio, entonces tu pellejo estará en juego.";
		link.l1.go = "Mtr_acceptor_7_9";
		break;

	case "Mtr_acceptor_7_9":
		dialog.text = "No te preocupes, somos gente honesta. Estos son nuestros términos: un lote de cien rollos cada mes entre el 10 y el 15. Estaremos esperando aquí... espera, cambiemos el punto de encuentro, este lugar está comprometido ahora. Estaremos esperando en el Cabo Negril, cerca del pueblo Maroon, debería ser más seguro allí. La contraseña es: 'Un comerciante de Lyon'.";
		link.l1 = "Entendido. Espera el primer lote el próximo mes.";
		link.l1.go = "Mtr_acceptor_7_10";
		break;

	case "Mtr_acceptor_7_10":
		dialog.text = "Infórmale a Tyrex que puede traer más carga esta vez, nos hemos quedado sin seda para este mes.";
		link.l1 = "Iré. Buena suerte, amigo.";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_CargoSilkWin");
		AddCharacterExpToSkill(pchar, "Sneak", 300); // скрытность
		break;

	// Тесак Пелли
	case "Pelly":
		dialog.text = "¡Ahoy! ¿Qué te trajo a bordo de mi navío, amigo?";
		link.l1 = "Hola, Alfanje. Marcus Tyrex me envió. Nos espera una marcha hacia Maracaibo.";
		link.l1.go = "Pelly_1";
		break;

	case "Pelly_1":
		dialog.text = "A-ah, por fin. Entonces debes ser mi nuevo jefe para este viaje. Bien. ¿Cómo se llama mi nuevo almirante?";
		link.l1 = "Capitán " + GetFullName(pchar) + ".";
		link.l1.go = "Pelly_2";
		break;

	case "Pelly_2":
		dialog.text = "¿Órdenes, Almirante " + GetFullName(pchar) + "?";
		link.l1 = "Zarparemos hacia el Lago de Maracaibo por separado. Debes llegar allí por la noche y desembarcar en secreto en la Bahía de Guajira. Espérame allí y, mientras tanto, establece un pequeño campamento. Yo, por mi parte, desembarcaré en el puerto español.";
		link.l1.go = "Pelly_3";
		break;

	case "Pelly_3":
		dialog.text = "¡Sí, sí, almirante!";
		link.l1 = "¿Cuánto tiempo te tomará llegar allí?";
		link.l1.go = "Pelly_4";
		break;

	case "Pelly_4":
		dialog.text = "Hmmm... Debería ser alrededor de una semana. Un día menos, un día más, todo depende del viento.";
		link.l1 = "Bien. No perdamos tiempo entonces. Te veré en la Bahía de Guajira, amigo.";
		link.l1.go = "Pelly_5";
		break;

	case "Pelly_5":
		dialog.text = "¡A la orden, almirante!";
		link.l1 = "...";
		link.l1.go = "Pelly_6";
		break;

	case "Pelly_6":
		DialogExit();
		AddQuestRecord("Roger_3", "3");
		LAi_CharacterDisableDialog(npchar);
		npchar.DontDeskTalk = true;
		Mtraxx_PlantContinue();
		break;

	case "Pelly_7":
		dialog.text = "¿Órdenes, almirante?";
		link.l1 = "Nada por el momento. Estoy ocupado con nuestra operación.";
		link.l1.go = "Pelly_wait";
		if (pchar.questTemp.Mtraxx == "plant_3")
		{
			link.l1 = "Prepara un cofre espacioso en la orilla. Estaremos recogiendo armas, para nuestros hermanos encarcelados, en él.";
			link.l1.go = "Pelly_7_1";
		}
		if (pchar.questTemp.Mtraxx == "plant_6" && CheckAttribute(pchar, "questTemp.mtraxx_PlantInfoTovar"))
		{
			dialog.text = "Entonces, ¿cuál es el trato con Guapo? ¡Mis manos están ansiosas por derramar algo de sangre de Don!";
			link.l1 = "Es más complicado de lo que pensamos. Dijo que los guardias en la plantación están demasiado alerta. La única manera de infiltrar armas es ocultándolas en mercancías. Necesitaremos urgentemente conseguir un cargamento de café, copra o vainilla - el hacendado comercia con eso y nada más.";
			link.l1.go = "Pelly_70";
			DelLandQuestMark(npchar);
		}
		if (pchar.questTemp.Mtraxx == "plant_8" && pchar.location.from_sea == "Shore37")
		{
			link.l1 = "Deja el campamento y reúne un escuadrón de tormenta. Es hora de marchar, atacamos bajo el amparo de la oscuridad.";
			link.l1.go = "Pelly_11";
			DelLandQuestMark(npchar);
		}
		break;

	case "Pelly_wait":
		DialogExit();
		npchar.dialog.currentnode = "Pelly_7";
		break;

	case "Pelly_7_1":
		dialog.text = "Escucha, Almirante, he estado pensando...";
		link.l1 = "¿Qué es esto, Terrax te paga para pensar en lugar de blandir ese sable tuyo, eh, Cutlass?";
		link.l1.go = "Pelly_35";
		break;

	case "Pelly_8":
		dialog.text = "¡Oh! ¿Una rebelión en la plantación, tengo razón, almirante? ¡Llamas! ¡Vamos a sacar algo de oro de esto!";
		link.l1 = "Necesito un cofre en la orilla, Cutlass.";
		link.l1.go = "Pelly_9";
		break;

	case "Pelly_9":
		dialog.text = "¡Enseguida, Almirante!";
		link.l1 = "...";
		link.l1.go = "Pelly_10";
		break;

	case "Pelly_10":
		DialogExit();
		npchar.dialog.currentnode = "Pelly_7";
		pchar.questTemp.Mtraxx = "plant_4";
		pchar.questTemp.Mtraxx.Chest = "true";
		// подгружаем сундук в локу и меняем локаторы
		int n = Findlocation("Shore37");
		Locations[n].models.always.locators = "shore03_q_locators";
		locations[n].models.always.chest = "chest_quest";
		Locations[n].models.always.chest.locator.group = "box";
		Locations[n].models.always.chest.locator.name = "private1";
		Locations[n].models.always.chest.tech = "DLightModel";
		DoQuestReloadToLocation("Shore37", "goto", "goto5", "Mtraxx_PlantChestReady");
		break;

	case "Pelly_11":
		dialog.text = "¡Al instante, Almirante!";
		link.l1 = "";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_PlantPrepareMarch");
		break;

	case "Pelly_12":
		dialog.text = "¡Los hombres están listos y preparados, Almirante!";
		link.l1 = "¡Adelante!";
		link.l1.go = "Pelly_13";
		break;

	case "Pelly_13":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		chrDisableReloadToLocation = false;
		break;

	case "Pelly_14":
		dialog.text = "Almirante, parece que el amigo de Tyrex al que debíamos salvar está... algo muerto.";
		link.l1 = "Sí, pero no se podía hacer nada allí. Viste a los guardias, tuvimos suerte de seguir con vida.";
		link.l1.go = "Pelly_15";
		break;

	case "Pelly_15":
		dialog.text = "Almirante, Marcus se enfadará contigo. No vayas a verlo ahora. Me voy. Tú también deberías.";
		link.l1 = "Sí...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_PlantFailFinal");
		break;

	case "Pelly_16":
		dialog.text = "Malas noticias, Almirante. Hay un escuadrón español viniendo hacia nosotros desde el Este. No tenemos tiempo para huir.";
		link.l1 = "¿Cuántos de ellos?";
		link.l1.go = "Pelly_17";
		break;

	case "Pelly_17":
		dialog.text = "Tres barcos. Montones de cañones. Estamos jodidos."; // лесникПОСЛЕДНЕЕ
		link.l1 = "Veremos.";												// Жан, ты отправляйся на борт к Тесаку. Тесак, поднимешь испанский флаг и на всех парусах прочь отсюда - глядишь, за торговца сойдёшь. А я пойду прямо на испанцев - отвлеку их от вас. Увидимся в Ла Веге у Тиракса.";
		link.l1.go = "Pelly_181";
		break;
	case "Pelly_181":
		DialogExit();
		sld = characterFromId("Mrt_Rocur");
		sld.Dialog.currentnode = "Pelly_182";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
	case "Pelly_182":
		dialog.text = "";
		link.l1 = "Jean, ve al barco de Cutlass.";
		link.l1.go = "Pelly_183";
		break;
	case "Pelly_183":
		DialogExit();
		sld = characterFromId("Pelly");
		sld.Dialog.currentnode = "Pelly_18";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
	case "Pelly_18":
		dialog.text = "";																												 //"Но...";
		link.l1 = "Cutlass, deberías izar la bandera española y largarte de aquí. Yo los distraeré por ti. Nos vemos todos en La Vega."; //"Отставить! Тесак, за Жана Пикара отвечаешь головой перед Тираксом. Все на борт!";
		link.l1.go = "Pelly_19";
		break;

	case "Pelly_19":
		dialog.text = "Pero...";
		link.l1 = "¡Sin peros! ¡Cutlass, es tu trasero el que está en juego si Picard no llega al lugar de Tyrex. ¡Todos a bordo!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_PlantSeaEscape");
		break;

	case "Pelly_20":
		dialog.text = "¿Órdenes, Almirante?";
		link.l1 = "Prepárate para luchar. ¡Atácalos a mi orden!";
		link.l1.go = "Pelly_21";
		break;

	case "Pelly_21":
		dialog.text = "¡A la orden, almirante... a su mando!";
		link.l1 = "... ";
		link.l1.go = "Pelly_22";
		break;

	case "Pelly_22":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		chrDisableReloadToLocation = false;
		break;

	case "Pelly_23":
		dialog.text = "¡Jo-jo! Hola Prince. ¿Qué te trae a Tortuga?";
		link.l1 = "Otra tarea de Marcus. Escucha, Cutlass, ¿por qué el bastardo que vive en esta casa no me deja entrar?";
		link.l1.go = "Pelly_24";
		break;

	case "Pelly_24":
		dialog.text = "¿Gaspard Dientes de Oro? Él solo trabaja con compañeros de confianza. Otros necesitarían recomendaciones para trabajar con él. ¿Quieres vender algunas chucherías brillantes? Podría recomendarte si quieres...";
		link.l1 = "¿Entonces es un usurero? ¿Cuál es su interés?";
		link.l1.go = "Pelly_25";
		break;

	case "Pelly_25":
		dialog.text = "Hermano, te falta algo. Gaspard no es un usurero, deberías ir a " + GetFullName(characterFromId("Tortuga_usurero")) + " si necesitas uno. Goldenteeth compra piedras preciosas y joyas de todo tipo. Por cierto, paga bien y nunca hace preguntas tontas. Cada capitán pirata es su cliente.";
		link.l1 = "Ya veo... Me dijeron que algunos de ellos incluso le confían su dinero...";
		link.l1.go = "Pelly_26";
		break;

	case "Pelly_26":
		dialog.text = "¡Ja, ja! Fue un mentiroso quien te dijo eso, ve y escúpele en sus ojos descarados. Gaspard trabaja solo con joyas, siempre lo hacía. ¿Por qué necesitaría problemas con el dinero ajeno?";
		link.l1 = "Ya veo. ¡Gracias Espada, nos vemos en el mar!";
		link.l1.go = "Pelly_27";
		link.l2 = "Hmm, en efecto. Así que, ¿compra chucherías? Interesante... ¿Dices que puedes hablar bien de mí?";
		link.l2.go = "Pelly_27z";
		break;

	case "Pelly_27":
		dialog.text = "Nos vemos, Prince.";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_WolfreekReadLogbookThird");
		break;

	case "Pelly_27z":
		dialog.text = "¡Por supuesto! ¡Ya eres uno de los nuestros, jeje! Espera aquí un momento.";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_WolfreekPellyTalkGems");
		break;

	case "Pelly_28z":
		dialog.text = "¡Todo está arreglado! Ahora Dientedeoro sabe que Charlie Prince puede venir a él a vender baratijas. Solo ten en cuenta que su precio, aunque bueno, sigue siendo más bajo que el que pagan esos avaros usureros. ¡Pero compra todo por toneladas! Y sin preguntas innecesarias, como ya dije.";
		link.l1 = "¡Ese es mi apuesto muchacho! ¡Bien hecho, Paul! ¡Ahora tengo un lugar donde descargar todo el botín!";
		link.l1.go = "Pelly_29z";
		break;

	case "Pelly_29z":
		dialog.text = "No, Jean Picard es el 'Guapo', ¡yo soy el 'Sable', jaja! ¡Adiós, Prince!";
		link.l1 = "Gracias, Cutlass, ¡buena suerte en el mar!";
		link.l1.go = "Pelly_27";
		break;

	case "Pelly_28":
		PlaySound("VOICE\Spanish\LE\Pelly\Pelly_03.wav");
		dialog.text = "¡Mira a quien acabo de encontrar, Prince!. Los encontré escondidos en armarios y debajo de una cama. Cosas bonitas, ¿eh? ¡Ja-ja-ja!";
		link.l1 = "Yo digo que de hecho lo son. Y también están bien cuidados. Don Terco debe preocuparse mucho por ellos.";
		link.l1.go = "Pelly_29";
		break;

	case "Pelly_29":
		DialogExit();
		sld = CharacterFromID("Mtr_CartahenaMayorClone");
		sld.dialog.currentnode = "CartahenaMayor_8";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "Pelly_30":
		PlaySound("VOICE\Spanish\LE\Pelly\Pelly_04.wav");
		dialog.text = "¡Hey! ¿Qué diablos estás haciendo aquí, Prince?";
		link.l1 = "¿Alfanje?.. Estaba siguiendo las voces y el ruido, pero nunca pensé que serías tú. ¿Cómo demonios terminaste aquí?";
		link.l1.go = "Pelly_31";
		QuestPointerDelLoc("Judgement_dungeon_01", "reload", "reload2_back");
		QuestPointerDelLoc("Judgement_dungeon_02", "reload", "reload2");
		QuestPointerDelLoc("Judgement_dungeon_03", "reload", "reload2");
		QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload2");
		QuestPointerDelLoc("Judgement_dungeon_05", "quest", "pelly");
		break;

	case "Pelly_31":
		dialog.text = "¡No, por qué estás aquí! ¡Siempre estás rondando! Tyrex debe haberte enviado por este tesoro, ¿verdad? Caramba, llegué tarde, otra vez...";
		link.l1 = "¿Tirax? No... Compré un mapa de una ramera. Probablemente te vendió una copia a ti, ¿eh? ¿En Tortuga? Qué perra astuta. Pero no mintió, ¡mira esta pila de oro! Volveré con más gente para llevar todo esto...";
		link.l1.go = "Pelly_32";
		break;

	case "Pelly_32":
		dialog.text = "¡Claro que sí, es un montón de oro! ¡Pero no es tuyo ni de Tyrex! ¡Lo he encontrado primero! ¡Es mío! ¡No importa cómo me enteré de ello! ¡No es asunto tuyo!";
		link.l1 = "Tranquilo, Cutlass, ¿por qué estás tan enfurecido? Mira esta pila, ¡debe haber un millón allí! ¡Quizás incluso más! ¡Suficiente para ambos!";
		link.l1.go = "Pelly_33";
		break;

	case "Pelly_33":
		dialog.text = "¡Siempre te llevas la mejor parte del pastel, Prince! ¡Pero no esta vez! ¡El tesoro es mío! ¡Lo he encontrado primero!";
		link.l1 = "Maldita sea, Paul, ¿qué te pasa? ¿No podemos llegar a un acuerdo aquí? Incluso la mitad de este oro es una fortuna. Nunca has tenido una suma así en tus manos antes. Además, podría encontrar una pista rentable algún día y contártelo.";
		link.l1.go = "Pelly_34";
		break;

	case "Pelly_34":
		dialog.text = "¿Quieres joderme, Prince? ¡De ninguna manera! ¡No te voy a dar ni una sola moneda, ni un solo guinea! ¡Llegas tarde!\n¡Ah-ah, veo lo que tramas! ¡De ninguna manera obtendrás este oro!!!";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_RetributionPellyFight");
		break;

	case "Pelly_35": //
		dialog.text = "Hilarante. Verdaderamente. Eres un comediante, Almirante. Pero es cierto: a Marcus no le gustan aquellos que intentan ser más astutos que él, como tú. Pero valora a los hombres inteligentes.";
		link.l1 = "Está bien, está bien. Entonces, ¿qué tienes en mente?";
		link.l1.go = "Pelly_36";
		break;

	case "Pelly_36":
		dialog.text = "Algo que tú y Guapo claramente no consideraron. Están planeando una revuelta en la plantación. Gran idea, si el objetivo era saquear o causar caos. Pero...";
		link.l1 = "¿Pero qué? ¿Tú contra la revuelta? ¿Asustado?";
		link.l1.go = "Pelly_37";
		break;

	case "Pelly_37":
		dialog.text = "¿Yo? ¡Ja! Nunca. Pero piensa en lo que sucede si Handsome encuentra su fin durante la matanza. ¿Qué le decimos a Marcus? Te diré qué - no importará lo que digamos. Igual se quedará con nuestras pieles.";
		link.l1 = "Hmm. Entonces, ¿cuál es tu brillante plan? Necesitamos sacarlo de alguna manera.";
		link.l1.go = "Pelly_38";
		break;

	case "Pelly_38":
		dialog.text = "Lo hacemos. Por eso... ¿por qué no comprarlo? Oficialmente, es decir. Un puñado de oro puede comprar a cualquiera de estos bastardos, incluso a sus propias madres. ¿Qué decir del pobre Jean?";
		link.l1 = "¡Ja! Cutlass, ¿de verdad estás sugiriendo que entre en una plantación y pregunte por comprar a Picard? ¿Debería también decirles para quién trabajo, solo por diversión? ¿Has perdido la cabeza?";
		link.l1.go = "Pelly_39";
		break;

	case "Pelly_39":
		dialog.text = "No necesitas decir eso. De hecho, todo lo contrario, finge que eres un comerciante. Claro, no tienes el talante para el papel, pero tampoco pareces un pirata. Sin ofender, Almirante, pero es la verdad. Solo camina por esa plantación, actúa con confianza, y pregunta por Jean. El dueño podría sospechar quién eres, pero no lo mostrará. Como dije, un puñado de oro sella bocas.";
		link.l1 = "¿Y cuánto nos costaría esta... mano de oro? ¿Toda la montaña?";
		link.l1.go = "Pelly_40";
		break;

	case "Pelly_40":
		dialog.text = "Puede ser. Pero es mejor separarse del oro que de la cabeza. No he estado ocioso mientras estabas en tierra - me cambié a algo menos pirata y pregunté sobre la plantación y su humilde dueño.";
		link.l1 = "¿Y qué encontraste, Cutlass?";
		link.l1.go = "Pelly_41";
		break;

	case "Pelly_41":
		dialog.text = "Precios de mercado, por así decirlo. No es la primera vez que un prisionero valioso cae en sus manos. Usualmente, terminan en la horca o peor - en las mazmorras de la Inquisición.";
		link.l1 = "¿Y por cuánto los vende?";
		link.l1.go = "Pelly_42";
		break;

	case "Pelly_42":
		dialog.text = "¿Para alguien importante? Quinientas monedas. En doblones, por supuesto.";
		link.l1 = "¿¡QUINIENTOS?!";
		link.l1.go = "Pelly_43";
		break;

	case "Pelly_43":
		dialog.text = "Plantadores, ¿qué esperabas?";
		link.l1 = "¡Por ese precio, podría equipar un pequeño ejército! ¿Por qué demonios estoy acumulando un arsenal en mi barco para una revuelta entonces? Será suficiente para una pequeña guerra.";
		link.l1.go = "Pelly_44";
		break;

	case "Pelly_44":
		dialog.text = "Las armas serán útiles para tu tripulación más tarde, de todos modos. Entonces, ¿qué dices?";
		if (IsCharacterPerkOn(pchar, "Trustworthy"))
		{
			if (PCharDublonsTotal() >= 500)
			{
				link.l1 = "(Confiable) Sólo diré que sería gracioso si la recompensa de Terrax es menor de lo que gastamos aquí. Pero tienes razón, nuestras vidas valen más. Tengo los doblones.";
				link.l1.go = "Pelly_45";
			}
			link.l2 = "No tengo ese tipo de montaña dorada ahora mismo.";
			link.l2.go = "Pelly_44_1";
			notification("Trustworthy", "Trustworthy");
		}
		else
			notification("¡Comprobación de beneficios fallida!", "Trustworthy");
		link.l3 = "¿Sabes qué, Cutlass? Olvídalo. ¿Somos piratas o qué? ¿Y Jean? ¿O su bonita cara es su único recurso? Prepara un cofre - nos ceñiremos al plan original.";
		link.l3.go = "Pelly_62";
		break;

	case "Pelly_44_1":
		dialog.text = "Me sorprendería si lo hicieras, es una suma enorme. Bien, cuando estés listo, o si se te ocurre algo mejor, ven a buscarme.";
		link.l1 = "Lo haré. Espera aquí.";
		link.l1.go = "exit";
		NextDiag.TempNode = "Pelly_44_2";
		break;

	case "Pelly_44_2":
		dialog.text = "Bueno, Almirante, ¿ha reunido suficiente oro para salvar a Picard?";
		if (PCharDublonsTotal() >= 500)
		{
			link.l1 = "Sí, finalmente lo he hecho. Esperemos que esto funcione.";
			link.l1.go = "Pelly_45";
		}
		link.l2 = "Aún estoy trabajando en ello, Cutlass.";
		link.l2.go = "exit";
		link.l3 = "No voy a dar mi dinero ganado con tanto esfuerzo a esos codiciosos plantadores. Prepara el cofre - actuaremos como Caballeros de Fortuna. Esa es mi decisión.";
		link.l3.go = "Pelly_9";
		NextDiag.TempNode = "Pelly_44_2";
		break;

	case "Pelly_45":
		dialog.text = "¡Vaya! ¡Eres nuevo en nuestra tripulación y ya estás manejando esa cantidad de dinero!";
		link.l1 = "El dinero no lo es todo. ¿Pero disfrutar de la gloria de Terrax? No tiene precio.";
		link.l1.go = "Pelly_46";
		pchar.questTemp.mtraxx_PlantVykup = true;
		break;

	case "Pelly_46":
		dialog.text = "No puedo discutir con eso. Pero como dijiste, no se trata solo de dinero, hay algo más importante, almirante.";
		link.l1 = "Tengo curiosidad ahora. ¿Qué?";
		link.l1.go = "Pelly_47";
		break;

	case "Pelly_47":
		dialog.text = "Te dije que he investigado todo sobre la plantación. Incluyendo qué bienes se demandan aquí y circulan en el mercado. Si quieres hacerte pasar por un comerciante legítimo, será mejor que te abastezcas de esos en lugar de simplemente lanzar un montón de oro sobre el escritorio del plantador.";
		link.l1 = "Tiene sentido. ¿De qué tipo de mercancías estamos hablando?";
		link.l1.go = "Pelly_48";
		break;

	case "Pelly_48":
		dialog.text = "Bueno, aparte de la mercancía viva, je-je, el dueño de la plantación compra, comercia y revende café, copra y vainilla. Así que...";
		link.l1 = "Necesito abastecerme rápidamente de eso en algún lugar. O asaltar una caravana y esperar que lleve lo que necesito.";
		link.l1.go = "Pelly_49";
		break;

	case "Pelly_49":
		dialog.text = "No cualquier caravana. Odio separarme de ella, pero tengo una pista guardada para mí. Una caravana que lleva exactamente lo que necesitas aparecerá pronto. Pero hay una advertencia...";
		link.l1 = "¿Oh, qué ahora?";
		link.l1.go = "Pelly_50";
		break;

	case "Pelly_50":
		dialog.text = "Está bajo la bandera francesa.";
		link.l1 = "¿Qué?!";
		link.l1.go = "Pelly_51";
		break;

	case "Pelly_51":
		dialog.text = "Entiendo tu frustración, ja-ja. La decisión es tuya... Almirante. ¿Quieres los detalles?";
		link.l1 = "Maldición... Está bien, suéltalo. No tenemos mucho tiempo - si tú o yo no les damos un mordisco, alguien más lo hará.";
		link.l1.go = "Pelly_52";
		link.l2 = "No toco a los franceses a menos que no tenga otra opción. Fin de la discusión.";
		link.l2.go = "Pelly_51_1";
		break;

	case "Pelly_51_1":
		dialog.text = "Entonces será mejor que empieces a reunir todos esos bienes por tu cuenta y rápido antes de que Chico Guapo sea vendido a alguien. Yo tampoco puedo quedarme aquí para siempre.";
		link.l1 = "Me lo imaginaba.";
		link.l1.go = "Pelly_51_2";
		break;

	case "Pelly_51_2": // добываем товары сами
		DialogExit();

		LAi_SetActorType(npchar);
		AddQuestRecord("Roger_3", "28");
		SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe", 0, 0, 14, false);
		SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe_time", 0, 0, 45, false);
		// DoQuestCheckDelay("Mtraxx_PlantCaravanGuadeloupe", 1.0);
		break;

	case "Pelly_52":
		dialog.text = "¡Así me gusta! Sabía que lo llevabas dentro... Almirante. Entonces, aquí está el trato: mi contacto confiable informó recientemente que en unas dos semanas, aparecerá en las aguas de Guadalupe una caravana francesa que transporta café y especias. Es grande y bien armada, así que prepárate a fondo.";
		link.l1 = "Qué otra opción tengo.";
		link.l1.go = "Pelly_53";
		break;

	case "Pelly_53": // наводка на караван с нужными товарами
		DialogExit();

		LAi_SetActorType(npchar);
		AddQuestRecord("Roger_3", "28");
		// if (CheckAttribute(pchar, "questTemp.mtraxx_PlantVykup")) AddQuestUserData("Roger_3", "sText", "Who would've thought that among the captains of Terrax, there'd be someone with at least the spark of a negotiator or a true entrepreneurial streak? That person turned out to be my temporary companion, Paul "Cutlass." Understanding the consequences of Marcus's wrath if we fail his assignment, Cutlass suggested... officially buying Picard from the plantation owner. While I scouted the situation and spoke with Jean, Cutlass didn't waste time either. He discovered that the plantation owner frequently sells valuable captives, with the average price for such transactions being around 500 doblones - a small fortune. But Paul is right - it's better to do this than risk Picard being killed by a stray bullet or blade. Now all that's left is to load up on the plantation's usual trade goods - be it coffee, copra, or vanilla - in large quantities.");
		SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe", 0, 0, 14, false);
		SetTimerCondition("Mtraxx_PlantCaravanGuadeloupe_time", 0, 0, 45, false);
		// DoQuestCheckDelay("Mtraxx_PlantCaravanGuadeloupe", 1.0);
		break;

	case "Pelly_54": // провал выкупа Красавчика
		dialog.text = "Estás cabizbajo, Almirante. ¿Dónde está Guapo? ¿Todo se ha ido por la borda?";
		link.l1 = "En efecto. Gané una buena cantidad de dinero, pero ese mula testaruda se negó a venderme Picard, ¡incluso por un montón de doblones!";
		link.l1.go = "Pelly_55";
		break;

	case "Pelly_55":
		dialog.text = "¡Qué tonto! ¿Y ahora qué?";
		link.l1 = "Ya he arreglado con el plantador para descargar la mercancía. Tendremos que volver al plan original, ¡es ahora o nunca!";
		link.l1.go = "Pelly_56";
		break;

	case "Pelly_56":
		dialog.text = "¡Pero ni siquiera hemos preparado nada para Guapo y los demás!";
		link.l1 = "¡No hay tiempo! ¡Subid a los barcos! Meteremos armas y medicinas de nuestras bodegas en los sacos de mercancías. Y no olvidéis izar la bandera española.";
		link.l1.go = "Pelly_57";
		break;

	case "Pelly_57":
		dialog.text = "Parece un plan.";
		link.l1 = "De todos modos, no tenemos tiempo para nada más. ¡Muévete! La descarga ocurre pronto.";
		link.l1.go = "Pelly_58";
		break;

	case "Pelly_58":
		DialogExit();
		DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 1.0);
		break;

	case "Pelly_59":
		dialog.text = "¡Mira quién es! ¡Guapo! Y a juzgar por tu cara intacta y tu paso seguro, ¿supongo que todo fue sin problemas?";
		link.l1 = "Suavemente es quedarse corto - no solo evité una pelea y compré de vuelta a Jean, sino que también gané algo de dinero. Tu plan funcionó a la perfección, Paul. ¿Todo tranquilo en el horizonte?";
		link.l1.go = "Pelly_60";
		break;

	case "Pelly_60":
		dialog.text = "Tan silencioso como puede ser. ¿Vuelves con Marcus?";
		link.l1 = "Correcto.";
		link.l1.go = "Pelly_61";
		break;

	case "Pelly_61":
		DialogExit();
		chrDisableReloadToLocation = true;
		LocatorReloadEnterDisable("shore37", "boat", false);
		bQuestDisableMapEnter = false;
		AddQuestRecord("Roger_3", "29");
		pchar.questTemp.Mtraxx = "plant_success";
		QuestSetCurrentNode("Terrax", "mtraxx_27");
		// SetFunctionTimerCondition("Mtraxx_PlantGoHomeOver", 0, 0, 40, false);
		SetFunctionTimerCondition("Mtraxx_PlantOpenMaracaibo", 0, 0, 5, false);

		sld = characterFromId("Mtr_plantation_boss");
		sld.lifeday = 0;

		sld = &Locations[FindLocation("shore37")];
		sld.DisableEncounters = false;
		sld = ItemsFromID("fire");
		sld.shown = false;
		DeleteAttribute(sld, "fire");
		for (i = 1; i <= 4; i++)
		{
			if (GetCharacterIndex("Pelly_sailor_" + i) != -1)
			{
				sld = characterFromId("Pelly_sailor_" + i);
				sld.lifeday = 0;
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "", 5);
			}
		}
		sld = characterFromId("Pelly");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "OpenTheDoors", 5);
		sld = characterFromId("mrt_Rocur");
		LAi_SetActorType(sld);
		LAi_ActorRunToLocation(sld, "reload", "sea", "none", "", "", "", 5);
		break;

	case "Pelly_62":
		dialog.text = "Hmm, como desees, Almirante. Pero si algo le sucede al Guapo, me aseguraré de que Terrax sepa que ignoraste mi consejo. ¿Tienes todo listo para la fuga?";
		link.l1 = "Déjame comprobar y contar lo que tengo en el cofre.";
		link.l1.go = "Pelly_63";
		break;

	case "Pelly_63":
		dialog.text = "Estate seguro de ello. Puedo ayudar por una modesta tarifa y para cubrir mis esfuerzos, je-je.";
		link.l1 = "¿Cómo es eso?";
		link.l1.go = "Pelly_64";
		break;

	case "Pelly_64":
		dialog.text = "Tengo un contacto, un traficante de armas en Maracaibo. Me disfrazaré, entraré a hurtadillas, le pagaré y organizaré el contrabando de las armas aquí. Pero te costará - doblones de oro, para ser exactos.";
		link.l1 = "¿Y por qué no me has presentado a este tipo antes? ¿Cuánto me costará esto?";
		link.l1.go = "Pelly_65";
		break;

	case "Pelly_65":
		dialog.text = "¿Debería presentarte también a todos mis informantes? Está bien. Con gastos, riesgos y mi parte... costará más o menos lo mismo que el rescate de Guapo.";
		link.l1 = "¡Sable, teme a Dios...";
		link.l1.go = "Pelly_66";
		break;

	case "Pelly_66":
		dialog.text = "Ni a Dios ni a ti temo, Almirante. Pero la ira de Marcus si no logramos salvar a Jean? Esa es otra historia. Entonces, ¿qué será? ¿Necesitas ayuda con el cofre?";
		if (PCharDublonsTotal() >= 500)
		{
			link.l1 = "Está bien, adelante - ya se ha perdido suficiente tiempo. Aquí, esto debería ser la cantidad correcta.";
			link.l1.go = "Pelly_68";
		}
		link.l2 = "Es mucho dinero, Paul. Necesito pensarlo.";
		link.l2.go = "Pelly_67";
		link.l3 = "¡Es demasiado caro para un pequeño lote de armas que puedo comprar al por mayor mucho más barato! No, gracias, me encargaré de esto yo mismo.";
		link.l3.go = "Pelly_67_1";
		break;

	case "Pelly_67":
		dialog.text = "Bien, piensa lo que quieras. Pero recuerda—mientras piensas, la cantidad de moretones en la cara y el cuerpo de Guapito está aumentando cada hora, je-je-je.";
		link.l1 = "Te conseguiré los doblones...";
		link.l1.go = "exit";
		NextDiag.TempNode = "Pelly_67_2";
		break;

	case "Pelly_67_1":
		dialog.text = "No se trata del tamaño del cargamento—se trata del momento y los riesgos. Pero haz lo que quieras.";
		link.l1 = "Confía en mí, lo sé. Solo prepara el cofre - me encargaré de esto.";
		link.l1.go = "Pelly_10";
		break;

	case "Pelly_67_2":
		dialog.text = "¿Listo, almirante? ¿Necesita ayuda con las armas, o todavía le falta oro?";
		if (PCharDublonsTotal() >= 500)
		{
			link.l1 = "¡Finalmente tengo suficiente! Tómalo y resuelve esto de una vez - me está sacando de quicio.";
			link.l1.go = "Pelly_68";
		}
		link.l2 = "Cuida tu tono, Cutlass. Estoy listo, pero necesito más tiempo para reunir el dinero.";
		link.l2.go = "Pelly_67";
		link.l3 = "¡Eso es demasiado caro para un pequeño lote de armas que puedo comprar al por mayor mucho más barato! No, gracias, me encargaré de esto yo mismo.";
		link.l3.go = "Pelly_67_1";
		break;

	case "Pelly_68":
		dialog.text = "¡Oh, qué carga de doblones es esta! Pero no te preocupes, cada moneda se destinará al plan. De lo contrario, Marcus me desenterraría de la tumba más tarde, je-je. Ahora, ve a ver a Handsome, al Almirante, y dile que todo está listo.";
		link.l1 = "Soy yo quien da las órdenes aquí. Ahora, muévete.";
		link.l1.go = "Pelly_69";
		RemoveDublonsFromPCharTotal(500);
		break;

	case "Pelly_69":
		DialogExit();
		sld = characterFromId("Pelly");
		sld.dialog.currentnode = "Pelly_7";
		pchar.questTemp.Mtraxx = "plant_5";
		AddQuestRecord("Roger_3", "30");
		sld = characterFromId("Mrt_Rocur");
		LAi_CharacterEnableDialog(sld);
		sld.dialog.currentnode = "rocur_wait";
		sld.greeting = "Rocur_02";
		AddLandQuestMark(sld, "questmarkmain");
		break;

	case "Pelly_70":
		dialog.text = "Sí, ese es un problema. ¿Cuál es tu plan, Almirante?\nHe investigado todo sobre la plantación. Incluyendo qué bienes se demandan aquí y circulan en el mercado. Si quieres hacerte pasar por un comerciante legítimo, será mejor que te abastezcas de esos en lugar de simplemente lanzar un montón de oro sobre el escritorio del plantador.";
		link.l1 = "Tiene sentido. ¿De qué tipo de mercancías estamos hablando?";
		link.l1.go = "Pelly_48";
		DeleteAttribute(pchar, "questTemp.mtraxx_PlantInfoTovar");
		break;

	// Жан Пикар
	case "rocur":
		dialog.text = "¿Qué quieres de mí?";
		link.l1 = "Amigo mío, estoy buscando a Jean Picard. ¿Hay alguna posibilidad de que compartas el mismo nombre?";
		link.l1.go = "rocur_1";
		break;

	case "rocur_1":
		dialog.text = "Hay una posibilidad. Sin embargo, no recuerdo tu cara.";
		link.l1 = "No seas demasiado brusco, Jean. Marcus Tyrex me envió aquí. Mis órdenes son sacarte de aquí.";
		link.l1.go = "rocur_2";
		break;

	case "rocur_2":
		dialog.text = "¿Marcus? Tsh-sh... Silencio. Lo siento, amigo, no lo sabía. Pero no deberíamos hablar aquí, malditos guardias están por todas partes y siempre están escuchando... Veo que eres un invitado bienvenido entre los españoles, encuéntrame en una de las chozas por la noche y hablaremos. Te estaré esperando, hermano.";
		link.l1 = "...";
		link.l1.go = "rocur_3";
		break;

	case "rocur_3":
		DialogExit();
		AddQuestRecord("Roger_3", "6");
		LAi_CharacterDisableDialog(npchar);
		Mtraxx_PlantMakeMaxRocurClone();
		break;

	case "rocur_4":
		dialog.text = "Bueno, aquí es seguro... ¿Cuál es tu nombre, hermano?";
		link.l1 = "Capitán " + GetFullName(pchar) + "Ahora dime, ¿cómo terminaste en esta mierda? Tyrex quiere saberlo todo.";
		link.l1.go = "rocur_5";
		break;

	case "rocur_5":
		dialog.text = "Un desconocido se acercó a mí en una taberna de Willemstad... Me pidió que fuera su compañero para saquear una caravana holandesa. Yo tenía un bergantín, él tenía una polacra, una muy singular también. Así que perseguimos una caravana no lejos de Caracas y la saqueamos... Era de noche, estábamos dividiendo el botín cuando un enorme galeón español apareció en la oscuridad\nMi compañero huyó y yo también. Pero no había manera de que mi bergantín dañado escapara de un galeón y dos barcos más. Nos abordaron y vendieron a todos los sobrevivientes a este lugar como ganado.";
		link.l1 = "Ya veo. ¿Crees que fue un accidente? Estoy hablando del galeón.";
		link.l1.go = "rocur_6";
		break;

	case "rocur_6":
		dialog.text = "¡Maldita sea si lo supiera! Podrían haber oído un tiroteo, no estaba lejos de la calle principal.";
		link.l1 = "Hmm. Es posible. ¿Conociste a tu antiguo compañero antes? ¿Quién es él?";
		link.l1.go = "rocur_7";
		break;

	case "rocur_7":
		dialog.text = "Nunca lo había conocido antes. Dijo que su nombre era Ignacio Marco, un corsario de Inglaterra. Me dio la impresión de ser un hombre serio, por eso acepté participar en esta empresa. Es un marinero experimentado y un capitán, eso seguro, tiene una tripulación audaz a sus espaldas y su polacra es una belleza, no todos los días se ve un barco así.  ";
		link.l1 = "¿Ignacio Marco? ¿Un corsario inglés? ¿Es español?";
		link.l1.go = "rocur_8";
		break;

	case "rocur_8":
		dialog.text = "Es portugués, no español. ¿Qué tiene de malo una patente de corso británica? Tenemos muchos españoles entre los nuestros, lo sabes.";
		link.l1 = "Ya veo. Bien, hablemos de tu escape de aquí. ¿Alguna idea?";
		link.l1.go = "rocur_9";
		break;

	case "rocur_9":
		dialog.text = "¿Cuáles son tus números?";
		link.l1 = "Mi barco, una barquentina y hombres de Pelly el Sable. Mi embarcación está estacionada en el puerto de Maracaibo. El Sable ha desembarcado en la Bahía de Guajira y ha establecido un campamento allí.";
		link.l1.go = "rocur_10";
		break;

	case "rocur_10":
		dialog.text = "Hmm...";
		link.l1 = "¿Qué, esperabas que Tyrex enviara un navío de línea aquí?";
		link.l1.go = "rocur_11";
		break;

	case "rocur_11":
		dialog.text = "No esperaba nada. De hecho, me sorprende que Marcus no se haya olvidado de mí.";
		link.l1 = "Obviamente no lo hizo. Entonces, ¿alguna idea?";
		link.l1.go = "rocur_12";
		break;

	case "rocur_12":
		dialog.text = "No hay posibilidad de escapar de aquí, esta plantación está demasiado bien vigilada y hay junglas salvajes alrededor. Tampoco tiene sentido asaltarla, no tienes suficientes hombres, además hay un fuerte cerca. ";
		link.l1 = "Quizás, tú y tus muchachos podáis ayudarnos desde dentro. Atacadles fuerte por detrás.";
		link.l1.go = "rocur_13";
		break;

	case "rocur_13":
		dialog.text = "¿Con qué? ¿Manos desnudas y machetes oxidados?";
		link.l1 = "¿Y qué si tuvieras armas?";
		link.l1.go = "rocur_14";
		break;

	case "rocur_14":
		dialog.text = "Bueno, en ese caso les habríamos hecho ver su suerte. Sin embargo, hay un problema, revisan todo lo que traes adentro, no hay manera de que puedas contrabandear armas. Así que sugiero olvidarse de esto.";
		link.l1 = "Y aun así, esa es nuestra mejor opción por el momento. Pensaré en cómo entregarles a ti y a tus hombres armas... Dime, ¿cuántos de ustedes son capaces de luchar?";
		link.l1.go = "rocur_15";
		break;

	case "rocur_15":
		dialog.text = "Treinta cabezas, diría yo.";
		link.l1 = "Treinta sables entonces... Las pistolas también harían una diferencia, creo.";
		link.l1.go = "rocur_16";
		break;

	case "rocur_16":
		dialog.text = "Capitán, ¿hablas en serio sobre esto?";
		link.l1 = "Yo soy. He llegado aquí a propósito, no estoy bromeando. ¿Qué más podrías necesitar?";
		link.l1.go = "rocur_17";
		break;

	case "rocur_17":
		dialog.text = "Muy bien... Al menos intentémoslo. Necesitamos acero simple y frío: mis muchachos no están entrenados para trabajar con espadas elegantes y similares. Lo mismo se puede decir de las pistolas, las más baratas servirán perfectamente. Si nos consigues uno o dos mosquetes, eso nos ayudaría mucho también, tengo un par de muchachos que son buenos con los mosquetes. Balas, pólvora. Las pociones curativas son las más bienvenidas.";
		link.l1 = "Entendido. Las espadas y hachas se pueden tomar del arsenal del barco. El resto es más complicado de conseguir. Te avisaré cuando lo tenga todo.";
		link.l1.go = "rocur_18";
		break;

	case "rocur_18":
		dialog.text = "Por favor, date prisa, hermano. No tenemos medio año aquí, este maldito trabajo de ganado nos está matando uno por uno. Si me necesitas, ven a verme por las noches.";
		link.l1 = "Entendido, camarada. Espera, intentaré no hacerte esperar. Y ten cuidado, no les des razones para descartarte, aún.";
		link.l1.go = "rocur_19";
		break;

	case "rocur_19":
		DialogExit();
		AddQuestRecord("Roger_3", "7");
		npchar.dialog.currentnode = "rocur_wait";
		pchar.questTemp.Mtraxx = "plant_3";
		pchar.questTemp.Mtraxx.MagicBox = "Baster";
		AddLandQuestMark(characterFromId("Fadey"), "questmarkmain");
		AddMapQuestMarkCity("baster", false);
		pchar.quest.Mtraxx_PlantPrepareTimeOver.over = "yes";				 // снять таймер
		SetFunctionTimerCondition("Mtraxx_SeekWeaponOver", 0, 0, 30, false); // таймер
		break;

	case "rocur_wait":
		dialog.text = "¿Alguna novedad, camarada? ¿Has reunido las armas?";
		if (pchar.questTemp.Mtraxx == "plant_5")
		{
			link.l1 = "Sí. Un cofre con municiones está en la Bahía de Guajira. Todo lo que queda es encontrar una manera de meterlo furtivamente dentro de la plantación.";
			link.l1.go = "rocur_20";
		}
		else
		{
			link.l1 = "Estoy en ello. Espera.";
			link.l1.go = "rocur_wait_1";
		}
		break;

	case "rocur_wait_1":
		DialogExit();
		npchar.dialog.currentnode = "rocur_wait";
		break;

	case "rocur_20":
		dialog.text = "Muy bien, capitán. Ya he estado pensando en cómo llevar eso a cabo.";
		link.l1 = "Me alegra oír eso. ¿Qué tienes en mente?";
		link.l1.go = "rocur_21";
		DelLandQuestMark(npchar);
		break;

	case "rocur_21":
		dialog.text = "En esta plantación producen azúcar y cultivan granos de cacao. A veces su jefe vende las mercancías él mismo, es más rentable así. Hazle una oferta. Págale no con dinero sino con mercancías. Algo que puedas poner en cajas como copra, vainilla o café. Esfuérzate en regatear pero no te excedas\nEsconde armas en una o dos cajas y ponles marcas. Arregla un intercambio al atardecer para que tengan que dejar las cajas afuera durante la noche\nPor la noche encontraremos tus cajas marcadas, nos armaremos y daremos una buena paliza a los españoles. Con tu ayuda, por supuesto.";
		link.l1 = "¡Buen pensamiento aquí, hermano! Muy bien, me gusta este plan. Vamos a seguirlo.";
		link.l1.go = "rocur_22";
		break;

	case "rocur_22":
		dialog.text = "Una última cosa: ofrece solo un tipo de mercancía para intercambiar. Más tipos de mercancías - más cajas revisadas por los guardias.";
		link.l1 = "De acuerdo. Entonces elegiré solo un tipo. ¿Café, vainilla y copra, dijiste?";
		link.l1.go = "rocur_23";
		break;

	case "rocur_23":
		dialog.text = "Sí. Esto sonará como un buen trato para el jefe de la plantación.";
		link.l1 = "Entendido. Te avisaré cuando el trato esté hecho.";
		link.l1.go = "rocur_24";
		break;

	case "rocur_24":
		DialogExit();
		AddQuestRecord("Roger_3", "9");
		npchar.dialog.currentnode = "rocur_wait_2";
		pchar.questTemp.Mtraxx = "plant_6";
		pchar.questTemp.mtraxx_PlantInfoTovar = true;
		AddLandQuestMark(characterFromId("Pelly"), "questmarkmain");
		break;

	case "rocur_wait_2":
		dialog.text = "Ve, mi amigo, el tiempo es oro y no tenemos nada...";
		link.l1 = "";
		link.l1.go = "rocur_wait_3";
		break;

	case "rocur_wait_3":
		DialogExit();
		npchar.dialog.currentnode = "rocur_wait_2";
		break;

	case "rocur_25":
		dialog.text = "...";
		link.l1 = "(en voz baja) El trato está hecho. Las cajas se entregarán a la plantación mañana por la tarde. Las cajas que necesitas están marcadas con la letra 'W'. Las otras tienen el resto del alfabeto. Prepara a tus hombres. Atacaremos antes del amanecer, alrededor de las tres en punto.";
		link.l1.go = "rocur_25x";
		DelLandQuestMark(npchar);
		break;

	case "rocur_25x":
		dialog.text = "Comenzaremos con tu señal...";
		link.l1 = "";
		link.l1.go = "rocur_26";
		break;

	case "rocur_26":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		DoQuestFunctionDelay("Mtraxx_PlantWaitDay", 3.0);
		break;

	case "rocur_27":
		dialog.text = "¡Finalmente! ¡Estoy a punto de ver el mar de nuevo! Ya he olvidado su aspecto y su olor. ¡Bien hecho capitán! Te lo debo.";
		link.l1 = "No te preocupes por eso, lo arreglaremos más tarde... ¡Ahora embarquemos y salgamos de aquí!";
		link.l1.go = "rocur_28";
		break;

	case "rocur_28":
		DialogExit();
		sld = characterFromId("Pelly");
		sld.Dialog.currentnode = "Pelly_16";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

	case "rocur_29":
		dialog.text = "Saludos " + pchar.name + ". Me alegra verte de nuevo, también me alegra tenerte como compañero en esta aventura. Este trabajo va a ser duro, pero estoy seguro de que lo superaremos.";
		link.l1 = "Me alegra verte de nuevo, Picard. Estoy todo oídos, cuéntame sobre esa aventura tuya.";
		link.l1.go = "rocur_30";
		break;

	case "rocur_30":
		dialog.text = "He   contado ya a Marcus, ahora te lo diré a ti. Cuando era esclavo en la plantación en Maracaibo, aprendí algo de los españoles. Son bastante habladores cuando están borrachos... Escucha, al sureste de la bahía de Maracaibo hay un pequeño pueblo. Está escondido entre dos montañas en lo profundo de la jungla. Tiene un nombre del demonio: Santiago-de-Los-Caballeros-de-Mérida. Vamos a llamarlo Mérida\n¿No suena muy interesante todavía, eh? Las montañas que rodean el pueblo resultaron ser ricas en gemas. Esmeraldas, ópalos y legendarios ópalos de fuego\nPor lo que entiendo, los colonos de Mérida no le dijeron al gobernador general sobre estas gemas. Sin embargo, pronto lo sabrá, por eso deberíamos visitar Mérida antes de la llegada de los oficiales coloniales españoles.";
		link.l1 = "¿Quieres saquear el asentamiento?";
		link.l1.go = "rocur_31";
		break;

	case "rocur_31":
		dialog.text = "Exactamente. Está perdido entre selvas y montañas con una pequeña guarnición - una presa fácil para una unidad corsaria. Además, están lejos del mar, no esperan que nadie los ataque, excepto salvajes con lanzas y arcos.";
		link.l1 = "¿Cuánto estás seguro de que el asentamiento tiene piedras preciosas?";
		link.l1.go = "rocur_32";
		break;

	case "rocur_32":
		dialog.text = "Si nuestras aventuras resultan ser una falsa pista, yo mismo serviré en tu nave como oficial o como marinero, limpiaré cubiertas y lucharé en incontables abordajes hasta que mi deuda contigo y con Marcus sea saldada.";
		link.l1 = "Ya veo... Muy bien, ¿sabes cómo llegar a Mérida?";
		link.l1.go = "rocur_33";
		break;

	case "rocur_33":
		dialog.text = "Por supuesto que no conozco el camino exacto a través de las junglas, pero contrataremos a un guía de los indígenas. Debemos desembarcar al sur del lago de Maracaibo, encontrar una aldea india y buscar a aquellos que saben cómo llegar allí.";
		link.l1 = "...";
		link.l1.go = "rocur_34";
		break;

	case "rocur_34":
		DialogExit();
		sld = characterFromId("Terrax");
		sld.Dialog.currentnode = "mtraxx_38";
		LAi_SetActorType(sld);
		LAi_ActorSetHuberMode(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;

	case "rocur_35":
		dialog.text = "Capitán, lamento profundamente mi lenguaje, pero ¿por qué demonios aún no estamos en Mérida? ¿Eh? ¡Has escupido sobre nuestra causa común! Leprechaun y yo nos vamos sin ti. Le explicaré todo a Tyrex y tú deberías irte. Aquí, toma 50,000 pesos por tu ayuda en Maracaibo, los pedí prestados a amigos. Adiós, qué maldita vergüenza, pensaba mejor de ti.";
		link.l1 = "Hmm... Lo siento. ";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_MeridaTimeOverFail");
		break;

	case "rocur_36":
		dialog.text = "Aquí estamos.   Junglas por delante. Primero, deberíamos encontrar una aldea india y preguntar por un guía.";
		link.l1 = "Hagámoslo. Luke, ¿tienes algo que decir... o quizás un consejo?";
		link.l1.go = "rocur_37";
		break;

	case "rocur_37":
		DialogExit();
		sld = characterFromId("Lepricon");
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;

	case "rocur_38":
		dialog.text = "La guarnición de Mérida está acabada. No espero ninguna resistencia seria dentro del pueblo. ¡Vamos!";
		link.l1 = "¡Al ataque!!!";
		link.l1.go = "rocur_39";
		break;

	case "rocur_39":
		DialogExit();
		chrDisableReloadToLocation = false;
		LocatorReloadEnterDisable("Merida_ExitTown", "reload1_back", true);
		pchar.quest.mtraxx_merida_town.win_condition.l1 = "location";
		pchar.quest.mtraxx_merida_town.win_condition.l1.location = "Merida_Town";
		pchar.quest.mtraxx_merida_town.function = "Mtraxx_MeridaTown";
		Mtraxx_MeridaCheckOurWarriors();
		AddQuestRecord("Roger_5", "16");
		break;

	case "rocur_40":
		dialog.text = "¡Está hecho! No quedan héroes. Ahora debemos hablar con un gobernador de esta 'ciudad'. Espero que sea del tipo persuasible.";
		link.l1 = "¡De acuerdo, vamos a 'persuadirlo'! ¡Jean! ¡Sígueme!";
		link.l1.go = "rocur_41";
		break;

	case "rocur_41":
		DialogExit();
		chrDisableReloadToLocation = false;
		LocatorReloadEnterDisable("Merida_Town", "gate_back", true);
		pchar.quest.mtraxx_merida_townhall.win_condition.l1 = "location";
		pchar.quest.mtraxx_merida_townhall.win_condition.l1.location = "Merida_townhall";
		pchar.quest.mtraxx_merida_townhall.function = "Mtraxx_MeridaTownhall";
		sld = characterFromId("Mrt_Rocur");
		LAi_SetActorType(sld);
		LAi_ActorFollowEverywhere(sld, "", -1);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		sld = characterFromId("Lepricon");
		LAi_SetActorType(sld);
		LAi_ActorFollowEverywhere(sld, "", -1);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		AddQuestRecord("Roger_5", "17");
		break;

	case "rocur_42": // злой вариант
		DialogExit();
		chrDisableReloadToLocation = false;
		LocatorReloadEnterDisable("Merida_Town", "reload3", true);
		pchar.questTemp.Mtraxx = "merida_success";
		pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
		pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
		pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
		LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);

		sld = characterFromId("Merida_Head");
		LAi_SetActorType(sld);

		pchar.questTemp.Mtraxx_MeridaZloVariant = true;

		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "reload", "reload1", "Mtraxx_MeridaExitResidensia", -1);
		break;

	case "rocur_43": // мирный вариант
		DialogExit();
		chrDisableReloadToLocation = false;
		LocatorReloadEnterDisable("Merida_Town", "reload3", true);
		pchar.questTemp.Mtraxx = "merida_success";
		pchar.quest.mtraxx_merida_exit.win_condition.l1 = "location";
		pchar.quest.mtraxx_merida_exit.win_condition.l1.location = "Merida_Town";
		pchar.quest.mtraxx_merida_exit.function = "Mtraxx_MeridaExit";
		LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);

		sld = characterFromId("Merida_Head");
		LAi_SetActorType(sld);

		sld = characterFromId("Mrt_Rocur");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);

		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "reload", "reload1", "Mtraxx_MeridaExitResidensia", -1);
		break;

	case "rocur_44":
		if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
		{
			dialog.text = "Bien hecho, " + pchar.name + "¡Es hora de repartir las ganancias! Ya tengo los números. Había casi 2000 gemas en el cofre: 1560 esmeraldas, 1032 ópalos y 363 ópalos de fuego. Tu parte es la tercera: 350 esmeraldas, 244 ópalos y 63 ópalos de fuego. Aquí, tómalos.";
		}
		else
		{
			dialog.text = "Bien hecho, " + pchar.name + "¡Es hora de repartir el botín! Ya tengo los números. Había casi 2000 gemas en el cofre: 1050 esmeraldas, 732 ópalos y 189 ópalos de fuego. Tu parte es la tercera: 350 esmeraldas, 244 ópalos y 63 ópalos de fuego. Aquí, tómales.";
		}
		link.l1 = "¡Bien!";
		link.l1.go = "rocur_45";
		break;

	case "rocur_45":
		PlaySound("interface\important_item.wav");
		if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
		{
			TakeNItems(pchar, "jewelry4", 520);
			TakeNItems(pchar, "jewelry16", 334);
			TakeNItems(pchar, "jewelry14", 121);
		}
		else
		{
			TakeNItems(pchar, "jewelry4", 350);
			TakeNItems(pchar, "jewelry16", 244);
			TakeNItems(pchar, "jewelry14", 63);
		}
		dialog.text = "Ahora hablemos de mi deuda contigo por mi rescate. Entiendo que tuviste gastos serios. ¿Qué compensación considerarás justa? Estoy pagando de mi parte de las gemas.";
		link.l1 = "Un tercio de tu parte será suficiente. Tú también necesitas dinero, para comprar y equipar un barco, para pagar a tu tripulación...";
		link.l1.go = "rocur_46";
		break;

	case "rocur_46":
		PlaySound("interface\important_item.wav");
		if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaKamushki"))
		{
			TakeNItems(pchar, "jewelry4", 173);
			TakeNItems(pchar, "jewelry16", 111);
			TakeNItems(pchar, "jewelry14", 40);
		}
		else
		{
			TakeNItems(pchar, "jewelry4", 116);
			TakeNItems(pchar, "jewelry16", 81);
			TakeNItems(pchar, "jewelry14", 21);
		}
		dialog.text = "¡Gracias amigo! Pensé que pedirías no menos de la mitad. Ahora necesito dinero. Aquí, toma las gemas.";
		link.l1 = "¡Qué incursión, Jean! Vamos a La Española, a ver a Tyrex.";
		link.l1.go = "rocur_47";
		break;

	case "rocur_47":
		DialogExit();
		chrDisableReloadToLocation = false;
		pchar.questTemp.Mtraxx = "merida_gohome";
		AddQuestRecord("Roger_5", "18");
		sld = characterFromId("Mrt_Rocur");
		LAi_SetWarriorType(sld);
		LAi_CharacterDisableDialog(sld); // релиз-правка
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, false);
		sld = characterFromId("Lepricon");
		LAi_SetWarriorType(sld);
		LAi_CharacterDisableDialog(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		AddPassenger(pchar, sld, false);
		SetCharacterRemovable(sld, false);
		sld = characterFromId("Terrax");
		sld.dialog.currentnode = "mtraxx_40";
		pchar.quest.mtraxx_merida_lavega.win_condition.l1 = "location";
		pchar.quest.mtraxx_merida_lavega.win_condition.l1.location = "Hispaniola1";
		pchar.quest.mtraxx_merida_lavega.function = "Mtraxx_IgnasioKitty";
		// таймер на доплыть домой 40 дней
		SetFunctionTimerCondition("Mtraxx_MeridaReturnLate", 0, 0, 40, false);
		DeleteAttribute(pchar, "GenQuest.HunterLongPause");
		break;

	case "rocur_48":
		dialog.text = "¡Oh, qué encuentro! Un placer verte, " + pchar.name + "¿Cómo te va?";
		link.l1 = "Bastante bien. Encontré los tesoros del Lobo Rojo hace poco. Ahora me dirijo a Martinica para encontrarme con un amigo común nuestro. ¿Quieres ver a Tyrex?";
		link.l1.go = "rocur_49";
		break;

	case "rocur_49":
		dialog.text = "Sí. Quiero hablar con él sobre Pasquale Lavoisier. Marcus me envió a ese medio bandido-medio mercader. Hice lo que me pidió y él pagó con alguna mierda alegando que era un maldito buen pago. Yo mataría al cabrón justo donde estaba, pero Marcus pidió que lo tratara con respeto... entonces es él quien debe lidiar con este problema.";
		link.l1 = "Lo siento, pero Marcus no hará nada. Cuatro-ojos está en negocios con él.";
		link.l1.go = "rocur_50";
		break;

	case "rocur_50":
		dialog.text = "¿Qué demonios?";
		link.l1 = "Sí, pero no te dije nada de esto, ¿de acuerdo? Lavoisier también me engañó hace no mucho. Tyrex me pidió que le ayudara, igual que te pidió a ti. Me advirtieron en Isla Tesoro que cruzarse con el cuatro ojos es lo mismo que cruzarse con Marcus. Así que te sugiero que te olvides de esto. No eres ni el primero ni el último en esto.";
		link.l1.go = "rocur_51";
		break;

	case "rocur_51":
		dialog.text = "Ya veo. ¿Tú también fuiste engañado por esos dos?";
		link.l1 = "Bueno, sí. Estaba pensando en causarle algunos problemas al cuatro-ojos también antes de aprender más sobre él. No vale la pena.";
		link.l1.go = "rocur_52";
		break;

	case "rocur_52":
		dialog.text = "¿Intentarías devolverle el favor al bastardo si supieras que nadie jamás lo descubrirá?";
		link.l1 = "¡Ja! ¡Claro que lo haría! Aunque no sé cómo. Ataca los filibotes de Lavoisier y un buen día tus marineros se emborracharán y soltarán todo. ¿No sabes cómo funciona?";
		link.l1.go = "rocur_53";
		break;

	case "rocur_53":
		dialog.text = "¿Vas rumbo a Martinica ahora? ¿Cuándo volverás a llegar a La Vega?";
		link.l1 = "Marcus me dio tres semanas.";
		link.l1.go = "rocur_54";
		break;

	case "rocur_54":
		dialog.text = "Intenta hacerlo en dos. Lo pensaré... Encuéntrame en la Bahía de Gonaives en 14 días. Dirígete allí, y no entres en La Vega.";
		link.l1 = "Veo que estás tramando algo, ja-ja. Está bien. Lo intentaré.";
		link.l1.go = "rocur_55";
		break;

	case "rocur_55":
		dialog.text = "Más te vale hacerlo. ¡Nos vemos!";
		link.l1 = "...";
		link.l1.go = "rocur_56";
		break;

	case "rocur_56":
		DialogExit();
		chrDisableReloadToLocation = false;
		bDisableFastReload = false;
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload3", "none", "", "", "", 10.0);
		LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		ReOpenQuestHeader("Roger_4");
		AddQuestRecord("Roger_4", "11");
		pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1 = "Timer";
		pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.hour = 1.0;
		pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.day = GetAddingDataDay(0, 0, 14);
		pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 14);
		pchar.quest.mtraxx_pasq_gonaiv.win_condition.l1.date.year = GetAddingDataYear(0, 0, 14);
		pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2 = "location";
		pchar.quest.mtraxx_pasq_gonaiv.win_condition.l2.location = "Shore34";
		pchar.quest.mtraxx_pasq_gonaiv.function = "Mtraxx_PasqualeJanGonaiv";
		SetFunctionTimerCondition("Mtraxx_PasqualeJanTimer", 0, 0, 10, false); // правки прогона 3
		SetFunctionTimerCondition("Mtraxx_PasqualeJanTimeOver", 0, 0, 15, false);
		if (bImCasual)
			NewGameTip("Modo exploración: el temporizador no está desactivado. ¡Cumple el plazo!");
		pchar.questTemp.Mtraxx.Pasquale.Grabbing = "true";
		break;

	case "rocur_57":
		if (pchar.location.from_sea != "Shore34")
		{
			dialog.text = RandSwear() + "¿Dónde está tu barco? ¿Llegaste aquí desde La Vega? ¡Merde! Te pedí que vinieras aquí sin ser visto y en secreto. Mi plan está arruinado ahora. ¡Maldita sea!";
			link.l1 = "Mm...";
			link.l1.go = "rocur_58";
		}
		if (GetOfficersQuantity(pchar) > 0)
		{
			dialog.text = "Ahí estás, " + pchar.name + "Es bueno que estés aquí. Envía a tus compañeros de regreso al barco. Es una conversación privada.";
			link.l1 = "Muy bien.";
			link.l1.go = "rocur_59";
		}
		else
		{
			dialog.text = "Ahí estás, " + pchar.name + "  Es bueno que estés aquí.  Tengo un negocio para ti. ¿Listo para escucharlo?";
			link.l1 = "¡Claro!";
			link.l1.go = "rocur_61";
		}
		break;

	case "rocur_58":
		DialogExit();
		Group_DelCharacter("RocurSeaGroup", "Mrt_Rocur");
		Group_DeleteGroup("RocurSeaGroup");
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 10.0);
		AddQuestRecord("Roger_4", "14");
		CloseQuestHeader("Roger_4");
		break;

	case "rocur_59":
		DialogExit();
		LAi_SetStayType(npchar);
		npchar.dialog.currentnode = "rocur_60";
		break;

	case "rocur_60":
		if (GetOfficersQuantity(pchar) > 0)
		{
			dialog.text = "¡Ya te lo dije, despide a tus oficiales!";
			link.l1 = "Sí-sí, lo tengo.";
			link.l1.go = "rocur_59";
		}
		else
		{
			dialog.text = "Genial. Ahora podemos hablar libremente. Tengo un asunto para ti. ¿Listo para escucharlo?";
			link.l1 = "¡Seguro!";
			link.l1.go = "rocur_61";
		}
		break;

	case "rocur_61":
		dialog.text = "¿Conoces bien La Vega?";
		link.l1 = "Bueno... creo que sí. ¿Por qué preguntas?";
		link.l1.go = "rocur_62";
		npchar.greeting = "";
		break;

	case "rocur_62":
		dialog.text = "¿Has notado alguna vez el almacén a la derecha de la tienda? La única casa grande entre las chozas.";
		link.l1 = "¿El que siempre está cerrado? Sí, lo he visto. ¿Por qué lo mencionas?";
		link.l1.go = "rocur_63";
		break;

	case "rocur_63":
		dialog.text = "Bien observado - siempre está cerrado. Mientras estabas en tu misión en Martinica, nuestro amigo en común Lavoisier estuvo aquí durante tres días como invitado de Marcus Tyrex. Pasaron su tiempo en esta casa bebiendo ron y divirtiéndose.";
		link.l1 = "Hum...";
		link.l1.go = "rocur_64";
		break;

	case "rocur_64":
		dialog.text = "Entonces los hombres de Lavoisier arrastraron algunas cajas y paquetes dentro de la casa. Luego se fue. En cuanto a Marcus, él se queda en ese lugar todos los días durante varias horas.";
		link.l1 = "¿Alguna sugerencia?";
		link.l1.go = "rocur_65";
		break;

	case "rocur_65":
		dialog.text = "¿Qué sugerencias? Estoy seguro de que esta casa debe ser una base de Lavoisier en La Vega. No vi mucho a través de la ventana pero hay mercancías almacenadas allí. Creo que el cuatro-ojos tiene los medios para pagar lo que nos debe.";
		link.l1 = "Vaya, vaya... ¿Quieres entrar a la fuerza? ¿Y la puerta cerrada? Es pesada y robusta, no hay manera de que entremos sin hacer ruido.";
		link.l1.go = "rocur_66";
		break;

	case "rocur_66":
		dialog.text = "" + pchar.name + ", ¿me tomas por idiota? Ya lo he resuelto. He hecho la llave usando un molde de cera de la cerradura. Me costó un buen dineral, pero es mi problema.";
		link.l1 = "¡Je! ¿Por qué esperar por mí entonces?";
		link.l1.go = "rocur_67";
		break;

	case "rocur_67":
		dialog.text = "Será más seguro de esa manera, además eres el único en quien podría confiar. Una cabeza es buena, dos cabezas son mejores, y cuatro ojos son mejor que dos.";
		link.l1 = "¡Pues sí, cruzarse con Lavoisier requerirá tantos ojos como tenga, ¡ja-ja-ja! Pero, ¿qué hay de Tyrex? ¿Y si entra en la casa mientras revisamos las pertenencias de Pasquale?";
		link.l1.go = "rocur_68";
		break;

	case "rocur_68":
		dialog.text = "No lo hará. Siempre regresa a su propia casa antes de medianoche. ¿Listo para ir a La Vega la próxima noche? Nunca se darán cuenta de quién los fastidió: tú aún estás en Martinica y yo dejé La Vega hace una semana.";
		link.l1 = "Me encantaría joder al enculé de cuatro ojos. Pero dime Jean, ¿cómo se supone que vamos a llevar los barriles y cofres desde la casa?";
		link.l1.go = "rocur_69";
		break;

	case "rocur_69":
		dialog.text = "Estoy seguro de que encontraremos allí objetos más valiosos que cofres y barriles con mercancías, que serán mucho más ligeros. Entonces, ¿estás dentro?";
		link.l1 = "¡Claro que sí!";
		link.l1.go = "rocur_70";
		break;

	case "rocur_70":
		dialog.text = "Estupendo, me alegra no haberme equivocado contigo. Descansemos ahora, nos dirigimos a La Vega a medianoche.";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_PasqualeNight");
		break;

	case "rocur_71":
		dialog.text = "Es hora de irnos. Deberíamos robar a este bastardo y largarnos de allí antes del amanecer.";
		link.l1 = "¡Adelante!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_PasqualeNightMarch");
		SetLocationCapturedState("LaVega_town", true);
		LAi_LoginInCaptureTown(npchar, true);
		break;

	case "rocur_72":
		dialog.text = "Silencio... Ahora muévete, con calma, a la casa de Pasquale. Sígueme.";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_PasqualeNightToHouse");
		break;

	case "rocur_73":
		dialog.text = "Mira esto - tantas cosas por aquí. Comencemos. Revisa un cofre cerca de la puerta, luego sube y encárgate de una habitación. Yo me quedaré aquí: conozco los trucos de esconder objetos de valor entre la basura. Mantén los ojos y oídos abiertos y mantente alejado de las ventanas.";
		link.l1 = "Está bien...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_PasqualeNightInHouse");
		break;

	case "rocur_74":
		dialog.text = "" + pchar.name + ", ¿qué tienes? ¿Algo de interés?";
		link.l1 = "Ven y mira. Esto es algo.";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_PasqualeJanSeeGirl");
		break;

	case "rocur_75":
		dialog.text = "¡Maldita sea! Ahora veo por qué Tyrex viene a este lugar todos los días. No es solo el almacén del cuatro ojos, sino también un burdel.";
		link.l1 = "Parece que ella es una esclava aquí.";
		link.l1.go = "rocur_76";
		break;

	case "rocur_76":
		dialog.text = "Claro que sí. Mírala, es una obvia ramera del puerto... Mala suerte para nosotros. Tenemos que matarla.";
		link.l1 = "¿De verdad?";
		link.l1.go = "rocur_77";
		break;

	case "rocur_77":
		dialog.text = "Vio nuestras caras y oyó tu nombre. Le contará todo a Tyrex.";
		link.l1 = "Mm...";
		link.l1.go = "rocur_78";
		break;

	case "rocur_78":
		dialog.text = "Es tu elección. Su vida puede costarte la tuya.";
		link.l1 = "";
		link.l1.go = "rocur_79";
		break;

	case "rocur_79":
		DialogExit();
		sld = characterFromId("Mirabella");
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;

	case "rocur_80":
		dialog.text = "No pienses ni por un momento en confiar en esta ramera. Mañana Tyrex lo sabrá todo. ¿Quieres recibir una marca negra?";
		link.l1 = "No, no lo hago. Y no quiero matar a la moza - tengo un uso para ella. Ella viene conmigo.";
		link.l1.go = "rocur_81";
		break;

	case "rocur_81":
		dialog.text = "¡No seas idiota! Ella se escapará en cuanto tenga la oportunidad. Mira su frente, ¿ves la marca? Es una ladrona.";
		link.l1 = "Mm. Probablemente tienes razón, Jean. Muy bien, acaba con ella y vámonos de aquí.";
		link.l1.go = "rocur_82";
		link.l2 = "No planeo mantenerla en mi barco. Tengo un lugar para ella de donde nunca escapará, y tampoco hay oídos para escuchar sus gritos. También seguirá haciendo su trabajo allí... Una ramera personal, sin cargo, ¡ja, ja!";
		link.l2.go = "rocur_84";
		break;

	case "rocur_82":
		DialogExit();
		LAi_SetActorType(pchar);
		LAi_ActorGoToLocator(pchar, "goto", "goto6", "", 5);
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocator(npchar, "goto", "goto7", "Mtraxx_PasqualeJanKillGirl", 5);
		break;

	case "rocur_83":
		ChangeCharacterComplexReputation(pchar, "nobility", -10);
		dialog.text = "Eso es, no hay manera de que ella le diga algo a Marcus ahora...";
		link.l1 = "Pobre chica... ja, bueno, como dicen, la dama fortuna es una perra...";
		link.l1.go = "rocur_86";
		break;

	case "rocur_84":
		DialogExit();
		sld = characterFromId("Mirabella");
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;

	case "rocur_85":
		dialog.text = "Eres un hombre amable, " + pchar.name + ". ¿Por qué quieres molestarte con ella? Ah, lo que sea, es tu elección. Asegúrate de que esté callada mientras nos vamos.";
		link.l1 = "Si no lo será - está muerta.";
		link.l1.go = "rocur_86";
		break;

	case "rocur_86":
		if (CheckAttribute(pchar, "questTemp.Mtraxx.Pasquale.Grabbing.Chest"))
			sTemp = "Un poco. Un cofre lleno de doblones, un puñado de rubíes, un mapa de La Española y algo de ron.";
		else
			sTemp = "Nada de valor.";
		dialog.text = "¿Qué encontraste?";
		link.l1 = sTemp;
		link.l1.go = "rocur_87";
		break;

	case "rocur_87":
		Log_Info("Has recibido dos colecciones de tesoros.");
		PlaySound("interface\important_item.wav");
		TakeNItems(pchar, "icollection", 2);
		dialog.text = "Más suerte de mi lado. Aquí, toma tu parte. Nunca lograría llevarlo todo conmigo a la orilla. El de cuatro ojos nos pagó en su totalidad.";
		link.l1 = "¡Espléndido! ¡Bien hecho, Jean!";
		link.l1.go = "rocur_88";
		break;

	case "rocur_88":
		dialog.text = "¡Ahora vete!";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_PasqualeNightOutHouse");
		break;

	case "rocur_89":
		PlaySound("VOICE\Spanish\LE\Rocur\Rocur_04.wav");
		dialog.text = "Bien hecho, amigo mío. Tranquilo y sin ruido. Ahora, volvamos a los barcos.";
		link.l1 = "Ja, buena idea.";
		link.l1.go = "rocur_89_1";
		// AddDialogExitQuestFunction("Mtraxx_PasqualeNightGulf");
		break;

	case "rocur_89_1":
		DialogExit();
		DoFunctionReloadToLocation("shore34", "goto", "goto13", "Mtraxx_PasqualeFinal");
		break;

	case "rocur_90":
		PlaySound("VOICE\Spanish\LE\Rocur\Rocur_05.wav");
		dialog.text = "Bueno, " + pchar.name + "Es hora de que nos separemos, Prince. No estoy seguro de que nos volvamos a encontrar, pero debes saber que fue un placer conocerte, amigo.";
		link.l1 = "Ah, vamos. Nos veremos a menudo en La Vega.";
		link.l1.go = "rocur_91";
		SetLocationCapturedState("LaVega_town", false);
		LAi_LoginInCaptureTown(npchar, false);
		break;

	case "rocur_91":
		dialog.text = "No. He terminado con Tyrex. Este lío con Lavoisier fue la gota que colmó el vaso.";
		link.l1 = "Hmm... Veo, solo olvídalo. Hemos conseguido lo que era nuestro por derecho. ¿Tyrex da pistas rentables, no? La última vez gané más de medio millón con el tesoro del Lobo Rojo.";
		link.l1.go = "rocur_92";
		break;

	case "rocur_92":
		dialog.text = "Dime entonces, ¿pusiste mucho esfuerzo en encontrarlo?";
		link.l1 = "Bueno... No fue fácil. Pensé mucho, viajé y peleé. Valió la pena, creo.";
		link.l1.go = "rocur_93";
		break;

	case "rocur_93":
		dialog.text = "¿Cuánto pagaste a Tyrex?";
		link.l1 = "Un tercio.";
		link.l1.go = "rocur_94";
		break;

	case "rocur_94":
		dialog.text = "¿Cuál fue su parte en este asunto? ¿Qué hizo Marcus exactamente?";
		link.l1 = "Hm... Me ha dado el diario del Lobo Rojo...";
		link.l1.go = "rocur_95";
		break;

	case "rocur_95":
		dialog.text = "¿Y eso es todo? ¿Verdad?";
		link.l1 = "Bueno... Nunca habría aprendido sobre el capitán Wulfric de otro modo...";
		link.l1.go = "rocur_96";
		break;

	case "rocur_96":
		dialog.text = "" + pchar.name + ", ¿no ves que Tyrex hace que otros hagan el trabajo sucio? ¿Crees que te daría la tarea de encontrar ese tesoro si pudiera hacerlo él mismo? ¡Claro que no! Apuesto a que intentó hacerlo él primero y cuando lo arruinó todo, te llamó para que hicieras el trabajo. Y mientras tú estabas pensando, pasando semanas en el mar, peleando y arriesgando tu propia vida, este bastardo junto a su asqueroso amigo de cuatro ojos estaban jodiendo a la puta en La Vega. Y por esto también consiguió un cuarto de millón de pesos. Así nomás\n¿Crees que envió a su perro Leprechaun para ayudarnos en nuestra incursión por Mérida? No, quería asegurarse de que sus intereses estuvieran seguros. Todo lo que Marcus puede hacer por sí mismo, lo hace, ya sea solo o con la ayuda de Cutlasses, Balds, Leprechauns y otros idiotas tontos que trabajan para él por migajas. Gente como tú y yo recibimos pistas que Marcus es demasiado estúpido para ejecutar por su cuenta\n¿Recuerdas todas las tareas que hiciste para él? Cuenta cuánto ganó contigo. Ya he tenido suficiente de esto. Ahora tengo el dinero, un gran corbeta, y una tripulación leal... de ahora en adelante soy un freelance. Me dirijo a Jamaica, quizás allí reciba una patente de corso.";
		link.l1 = "No creo que tengas toda la razón sobre Tyrex... ¡Pero te deseo suerte, Jean! Espero que encuentres el éxito en Jamaica.";
		link.l1.go = "rocur_97";
		break;

	case "rocur_97":
		dialog.text = "Lo haré. Buena suerte para ti también y piensa en lo que te he dicho. Ser el lacayo de Marcus no es el mejor papel para ti, sé que eres capaz de mucho más. Bueno... ¡adiós hermano! ¡Que Dios te acompañe!";
		link.l1 = "¡Buena caza, Jean!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_PasqualeAddComplete");
		break;

	case "rocur_98":
		dialog.text = "" + pchar.name + ", dime, ¿cómo pasamos tanto tiempo en la jungla? Ahora mi plan está arruinado. Eh... Adiós, amigo...";
		link.l1 = "Je...";
		link.l1.go = "rocur_99";
		break;

	case "rocur_99":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(sld, "reload", "reload1", "none", "", "", "", 10.0);
		sld.lifeday = 0;
		Group_DeleteGroup("RocurSeaGroup");
		AddQuestRecord("Roger_4", "18");
		CloseQuestHeader("Roger_4");
		break;

	case "rocur_100":
		if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZloVariant"))
		{
			dialog.text = "Es hora de irnos, muchachos. Maldita sea, Prince, me sorprendiste. Quemaste toda una ciudad, pero te negaste a ensuciarte las manos cuando importaba.";
			link.l1 = "¡No ordené que quemaran la ciudad!";
			link.l1.go = "rocur_101";
		}
		else
		{
			dialog.text = "Es hora de irse, muchachos. Lucas, te lo perdiste. ¡El Prince lo manejó brillantemente y obtuvo una buena ganancia!";
			link.l1 = "¿Qué pasa con la ciudad, Guapo?! ¡Di mi palabra!";
			link.l1.go = "rocur_102";
		}
		sld = CharacterFromID("Lepricon");
		CharacterTurnToLoc(sld, "reload", "reload3");
		break;

	case "rocur_101":
		dialog.text = "Al menos no intentaste salvarlo. De lo contrario, nuestros hombres te habrían destripado primero. Ha sido un día duro para ellos. Merecían desahogarse un poco. Te acostumbrarás. Tienes todas las cualidades para ello.";
		link.l1 = "Gracias por el consejo, pero no recuerdo haberlo pedido. Vámonos.";
		link.l1.go = "rocur_103";
		break;

	case "rocur_102":
		dialog.text = "Pensé que estabas bromeando. Bueno... fuiste demasiado apresurado. La ciudad está acabada. Así es siempre cuando los Hermanos de la Costa se ponen a trabajar. Te acostumbrarás.";
		link.l1 = "No estoy seguro de que lo haré. Está bien, vamos.";
		link.l1.go = "rocur_103";
		break;

	case "rocur_103":
		DialogExit();
		LAi_SetPlayerType(pchar);
		DeleteAttribute(pchar, "questTemp.lockedMusic");
		EndQuestMovie();
		locCameraTarget(PChar);
		locCameraFollow();
		sld = characterFromId("Tagofa");
		LAi_SetActorType(sld);
		LAi_ActorFollowEverywhere(sld, "", -1);
		Mtraxx_MeridaCheckOurWarriors();
		AddQuestRecord("Roger_5", "12");
		break;

	case "rocur_104":
		dialog.text = "Compañero... ¿qué fue eso justo ahora?";
		link.l1 = "¿Qué, no lo entendiste? Te compré. Una vez dijiste que tenía acceso a los españoles, así que lo utilicé.";
		link.l1.go = "rocur_105";
		break;

	case "rocur_105":
		dialog.text = "Entendí eso - no soy un idiota. ¿Pero no estábamos trabajando en un plan diferente?";
		link.l1 = "Bueno, Cutlass y yo pensamos que no estaría bien que terminaras muerto durante un levantamiento o una persecución, así que decidimos comprarte directamente.";
		link.l1.go = "rocur_106";
		break;

	case "rocur_106":
		dialog.text = "Jah, no me insultes. Soy uno de los capitanes de Terrax, después de todo. Sé cómo manejar una espada.";
		link.l1 = "No lo dudo, pero ¿de verdad te molesta ser libre?";
		link.l1.go = "rocur_107";
		break;

	case "rocur_107":
		dialog.text = "No, no - estoy agradecido. Es solo que... ¿no fue un poco demasiado gastar todo ese oro? Me siento enfermo solo de pensarlo. El plantador, por otro lado, parecía tan brillante como una bandeja de plata pulida.";
		link.l1 = "Sí, 'El Trato del Siglo', de verdad. Duele un poco, claro. Pero el tiempo es más precioso que el oro, Jean. Buscando pistolas y medicinas para todos ustedes...";
		link.l1.go = "rocur_108";
		break;

	case "rocur_108":
		dialog.text = "Estoy agradecido, pero compañero, eres un tonto - sin ofender. Te dije que mis muchachos no son buenos con las espadas. Pero cualquiera puede apretar un gatillo. Podrías haber traído cualquier pistola y medicina de la bodega, como con los sables y hachas - no son exigentes.";
		link.l1 = "Hmm, honestamente, no había pensado en eso... De todos modos, vamos - probablemente Cutlass se está impacientando.";
		link.l1.go = "rocur_109";
		break;

	case "rocur_109":
		DialogExit();
		DoFunctionReloadToLocation("Shore37", "goto", "goto6", "Mtraxx_PlantPlantVykup_3");
		break;

	// Люк Лепрекон
	case "lepricon":
		dialog.text = "Saludos, capitán " + GetFullName(pchar) + "¡Luke el Duende a tu servicio! Me han dicho que vamos a las junglas del Sur Principal.";
		link.l1 = "Precisamente. Embarca en los botes largos, nos vamos de inmediato.";
		link.l1.go = "lepricon_1";
		break;

	case "lepricon_1":
		dialog.text = "Deja que un viejo bucanero te dé un consejo, capitán. Ya que nos dirigimos a la selva, seguramente nos encontraremos con los indios. Lleva regalos para ellos contigo. Los guerreros indios adoran las hermosas pistolas, especialmente las de duelo. También les gustan las brújulas y los catalejos. Los tratan como si fueran objetos mágicos.\nSus mujeres prefieren joyas baratas y chucherías como espejos y peinetas. Si nos enfrentamos a ellos en una pelea, usa trombones y arcabuces: el perdigón en general es muy bueno contra enemigos que no llevan armaduras. En cuanto al asentamiento en sí, sugiero armas que puedan usar cartuchos de papel.";
		link.l1 = "Muy bien, Luke. Tus palabras son anotadas. Bienvenido a bordo.";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_MeridaSail");
		break;

	case "lepricon_2":
		dialog.text = "Ve al jefe tan pronto como lleguemos al pueblo. Y trae regalos, de lo contrario es inútil. Asegúrate de preguntar si alguien entre su gente sabe de pasadizos secretos en las selvas por delante, y pregunta por aquellos que no tienen miedo de viajar. Vendré contigo, dirígete a mí si enfrentas alguna dificultad.";
		link.l1 = "¡Vamos! Jean, Luke, ¡síganme!";
		link.l1.go = "exit";
		npchar.greeting = "Lepricon_02";
		AddDialogExitQuestFunction("Mtraxx_MeridaSeekVillage");
		break;

	case "lepricon_3":
		dialog.text = "¿Alguna pregunta, capitán?";
		link.l1 = "Ninguna por ahora, Luke.";
		link.l1.go = "lepricon_3x";
		if (pchar.questTemp.Mtraxx == "merida_advice")
		{
			link.l1 = "¡Sí! Hablé con su cacique, le hice un regalo y luego convocó a sus pieles rojas para una reunión. Hay entre ellos quienes saben cómo llegar a Mérida, pero nadie está dispuesto a ir; temen a otra tribu llamada Capongs. Esos asustan a los lugareños hasta hacerlos cagarse de miedo. El maldito piel roja dice que no tenemos ninguna posibilidad de encontrar el camino por nuestra cuenta y que no hay guía que podamos contratar. Entonces, ¿qué se supone que hagamos ahora, eh?!";
			link.l1.go = "lepricon_4";
		}
		if (CheckAttribute(pchar, "questTemp.Mtraxx.Merida.Potion") && GetCharacterItem(pchar, "potion3") >= 12)
		{
			link.l2 = "Tengo antídotos conmigo.";
			if (GetCharacterItem(pchar, "potion3") > 42)
				link.l2.go = "lepricon_7";
			else
				link.l2.go = "lepricon_6";
		}
		break;

	case "lepricon_3x":
		DialogExit();
		npchar.dialog.currentnode = "lepricon_3";
		break;

	case "lepricon_4":
		dialog.text = "Hmm, ya veo... Capitán, debes saber que la cobardía a menudo es vencida por la avaricia. Promete una recompensa tan generosa que un hombre aceptará el trabajo... ¿Sabes qué? Intenta una opción más astuta: sus mujeres. Regálales algo y pregunta por sus hombres, y es probable que encuentres al guía que necesitamos. Prométele montones de cuentas y espejos a cambio de la ayuda de su marido. Sé generoso y promete mucho, persuádelas.";
		link.l1 = "¡Je! Bueno, lo mínimo que puedo hacer es intentarlo, aunque no estoy seguro de si funcionará...";
		link.l1.go = "lepricon_5_1";
		DelLandQuestMark(npchar);
		break;

	case "lepricon_5_1":
		dialog.text = "Bueno, hay otra opción... Pero no es precisamente la mejor, si entiendes mi punto.";
		link.l1 = "¿Otra opción? ¡Dímelo! No estoy muy entusiasmado con la idea de ir a las mujeres indias y suplicarles que convenzan a sus maridos de unirse a nosotros.";
		link.l1.go = "lepricon_5_2";
		break;

	case "lepricon_5_2":
		dialog.text = "Esta opción es tan antigua como el tiempo. Muéstrales que deben temerte más de lo que temen a los Kapongs. Sabes... Podrías decirle al jefe lo que tus piratas podrían hacerle a todas las mujeres de la aldea, especialmente a su esposa y a sus hijas. Incluso podrías lanzar algunas amenazas de torturan\De todos modos, estoy seguro de que se te ocurrirá algo para que estos indios te teman. Personalmente, no soy fan de esta ruta, y hay razones para ello.";
		link.l1 = "¿Razones? ¿Como cuáles? En mi opinión, parece una solución bastante efectiva y directa.";
		link.l1.go = "lepricon_5_3";
		break;

	case "lepricon_5_3":
		dialog.text = "Para empezar, no seremos precisamente el brindis de la ciudad después de eso. Podríamos terminar cayendo en una trampa o en alguna otra situación desagradable. Y en segundo lugar, bueno... simplemente no se siente bien. Una cosa es enfrentarse a oponentes armados, pero es otra cosa completamente diferente amenazar a mujeres. Sugeriría encontrar una manera de tratar con los indios de forma más... diplomática.";
		link.l1 = "Entendido, lo pensaré. Tal vez intente cortejar a alguna dama con cuentas... O quizás invente algunas maneras imaginativas de tortura para las hijas del jefe, ¡jaja!";
		link.l1.go = "lepricon_5";
		break;

	case "lepricon_5":
		dialog.text = "Una cosa más, capitán, según el jefe, podemos enfrentarnos a una tribu hostil de indios en la jungla, es muy probable que sean solo un pequeño grupo de caníbales, pero más vale prevenir que lamentar. Si es una tribu guerrera, envenenarán sus armas, así que asegúrate de proveer a tus hombres con antídotos.\nMis hombres y yo siempre llevamos muchas pociones con nosotros. En cuanto a tus piratas... Solo tráeme los antídotos y me encargaré de distribuirlos entre tus hombres. Necesito al menos una docena de pociones para esto. Asegúrate de traer algunas para ti y tus oficiales también.";
		link.l1 = "Está bien. Traeré los antídotos.";
		link.l1.go = "lepricon_5x";
		break;

	case "lepricon_5x":
		DialogExit();
		npchar.dialog.currentnode = "lepricon_3";
		pchar.questTemp.Mtraxx = "merida_advice2";
		pchar.questTemp.Mtraxx.Merida.Women = "true";
		pchar.questTemp.Mtraxx.Merida.Potion = "true";
		AddQuestRecord("Roger_5", "8");
		sld = characterFromId("Hayamee");
		LAi_CharacterEnableDialog(sld);
		AddLandQuestMark(sld, "questmarkmain");
		// LocatorReloadEnterDisable("Shore_ship3", "boat", false);
		bQuestDisableMapEnter = false;
		DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");				   // выпустим в море
		SetFunctionTimerCondition("Mtraxx_MeridaPotionLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;

	case "lepricon_6":
		i = GetCharacterItem(pchar, "potion3");
		RemoveItems(pchar, "potion3", i);
		pchar.questTemp.Mtraxx.Merida.Antidote = i;
		dialog.text = "Muy bien. Dámelos. Haré el resto.";
		link.l1 = "Ahí...";
		link.l1.go = "lepricon_8";
		break;

	case "lepricon_7":
		RemoveItems(pchar, "potion3", 42);
		pchar.questTemp.Mtraxx.Merida.Antidote = 42;
		dialog.text = "Cuarenta y dos pociones serán suficientes. El resto deberías guardarlo para ti mismo.";
		link.l1 = "Está bien...";
		link.l1.go = "lepricon_8";
		break;

	case "lepricon_8":
		DialogExit();
		npchar.dialog.currentnode = "lepricon_3";
		DeleteAttribute(pchar, "questTemp.Mtraxx.Merida.Potion");
		break;

	case "lepricon_9":
		dialog.text = "Capitán, tus indios - Hayami y Tagofa han estado esperando demasiado tiempo para que les entregues los regalos que les prometiste y se han ido a otra aldea a bailar y beber kasheeri. Tengo la sensación de que tu manera de hacer negocios no nos hará ningún bien. Lo siento, pero estás fuera de esto. Picard liderará la expedición.";
		link.l1 = "¡Al diablo con todos ustedes entonces!";
		link.l1.go = "exit";
		AddQuestRecord("Roger_5", "19");
		AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;

	case "lepricon_10":
		dialog.text = "Capitán, ¿qué demonios? ¡Hemos perdido demasiado tiempo por nada! Tengo la sensación de que tu manera de hacer negocios no nos hará ningún bien. Lo siento, pero estás fuera de esto. Picard liderará la expedición.";
		link.l1 = "¡Al diablo con todos ustedes entonces!";
		link.l1.go = "exit";
		AddQuestRecord("Roger_5", "20");
		AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;

	case "lepricon_11":
		dialog.text = "Capitán, ¿qué demonios? Tenías diez días para encontrar cuero y tablones. ¡La ciudad de Maracaibo no está lejos de aquí! Tengo la sensación de que tu forma de hacer negocios no nos traerá nada bueno. Lo siento, pero estás fuera de esto. Picard liderará la expedición.";
		link.l1 = "¡Al diablo con todos ustedes entonces!";
		link.l1.go = "exit";
		AddQuestRecord("Roger_5", "20");
		AddDialogExitQuestFunction("Mtraxx_MeridaHayameeFail");
		break;

	case "lepricon_12":
		dialog.text = "Capitán, lo siento, pero se suponía que debía estar en La Vega hace mucho tiempo, al igual que usted, en realidad. Debe haber olvidado mi existencia y la de Marcus. De todos modos, me voy. Debería seguir haciendo lo que esté haciendo y yo le explicaré todo a Marcus. Adiós, es una lástima, pensé mejor de usted.";
		link.l1 = "Hmph...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_MeridaReturnFail");
		break;

	case "lepricon_13":
		PlaySound("VOICE\Spanish\LE\Leprikon\Lepricon_03.wav");
		dialog.text = "Entonces, por lo que entiendo, ustedes tuvieron una pelea. No acordaron dividir el botín, ¿verdad, Charlie Prince?";
		link.l1 = "¿Duende? Estás aquí... Aunque no es gran sorpresa. Sí, los bastardos codiciosos escupieron sobre el Código e intentaron matarme.";
		link.l1.go = "lepricon_14";
		QuestPointerDelLoc("Judgement_dungeon_05", "reload", "reload1");
		QuestPointerDelLoc("Judgement_dungeon_04", "reload", "reload1");
		QuestPointerDelLoc("Judgement_dungeon_03", "reload", "reload1");
		QuestPointerDelLoc("Judgement_dungeon_02", "reload", "reload1");
		QuestPointerDelLoc("Judgement_dungeon_01", "quest", "lepricon");
		break;

	case "lepricon_14":
		dialog.text = "Sí, te dieron una buena paliza, Prince. Pareces mierda mojada\n¿Qué dijiste sobre el Código? Déjame iluminarte: He estado trabajando con Marcus, quien supuestamente es el Guardián de este Código, he visto a hombres escupir sobre él tantas veces que no me atrevería a contar. Algunos de esos hombres pagaron un precio terrible. Algunos de ellos no\nPuedes hacer lo que quieras, si el premio lo cubre. Especialmente si nadie está mirando.";
		link.l1 = "Así que... ¿tú también estás aquí por el tesoro?";
		link.l1.go = "lepricon_15";
		break;

	case "lepricon_15":
		dialog.text = "Qué pregunta tan estúpida. ¿Qué más estaría haciendo aquí, tan lejos de mi tierra natal en La Española? Aunque después de todo, soy más inteligente que todos ustedes: conociendo su podrida naturaleza pirata. Solo esperé, dejando que ustedes, ratas, se despedazaran entre sí, dejando solo un enemigo vivo, pero herido y cansado.";
		link.l1 = "¿Enemigo? ¿Así es como sigues el Código de tu patrón? ¡Él mata a la gente por esto!";
		link.l1.go = "lepricon_16";
		break;

	case "lepricon_16":
		dialog.text = "No soy un sujeto del Código Prince, no soy un pirata. Ni siquiera poseo un barco - tuve que alquilar una bañera para llegar aquí. No soy más que un bucanero en resumen. Soy un cazador, cazo búfalos y hago bucan. Malditos españoles que afirman que nosotros, los bucaneros franceses, arruinamos su vida, me hicieron buscar apoyo y protección de Marcus. Le ayudo en su negocio por eso a veces\nAunque no soy un pirata, mis hombres y yo luchamos bien, nos has visto en acción.";
		link.l1 = "Estuvimos saqueando y luchando juntos, Leprechaun. Nos cubríamos las espaldas, arriesgando nuestras vidas para salvarnos mutuamente. ¿Es todo eso nada para ti?";
		link.l1.go = "lepricon_17";
		break;

	case "lepricon_17":
		PlaySound("VOICE\Spanish\LE\Leprikon\Lepricon_04.wav");
		dialog.text = "Seré honesto contigo, Prince: nunca me has agradado. Eres un advenedizo. Un joven insolente, aficionado a las bebidas y a las mujeres de mala reputación, que hizo algunos trabajos lucrativos para Tyrex y se creyó un gran pirata\nAdemás, eres un carnicero por naturaleza. ¿Crees que Cartagena te dio más peso entre los Hermanos? Jo-jo, oh infiernos no, solo entre los monstruos como tú.";
		link.l1 = "¡Oh, esto es hilarante! ¡Ja-ja-ja dicho por un verdadero ángel! ¡Viejo bastardo!";
		link.l1.go = "lepricon_18";
		break;

	case "lepricon_18":
		dialog.text = "Creo que ya hemos despejado todo. Es hora de terminar esta comedia. Los demonios te han estado esperando demasiado tiempo en el infierno.";
		link.l1 = "... ";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_RetributionLepriconFight");
		break;

	case "lepricon_19":
		if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZapugivanieIndeets"))
		{
			dialog.text = "¿Te gusta, eh?";
			link.l1 = "¡Retrocede!";
			link.l1.go = "lepricon_20";
		}
		else
		{
			dialog.text = "Bueno, ¿qué piensas?";
			link.l1 = "Esto no es gracioso, Leprechaun. ¿Qué demonios?! ¡No ordené una masacre! ¿No crees que esto es demasiado?! ¡Terrax no estará complacido!";
			link.l1.go = "lepricon_24";
		}
		break;

	case "lepricon_20":
		dialog.text = "¿Entonces, por qué esa mirada culpable? ¿No lo estás disfrutando? Déjame decirte - las cosas solo empeorarán. ¿Piensas que la masacre de hoy ocurrió solo porque es uno de esos días? Jajaja, claro. Esto es rutina. Picard ni siquiera parpadeó. Para ellos, es solo otro día haciendo lo que aman.";
		link.l1 = "¿Y tú? ¿Sólo de paso?";
		link.l1.go = "lepricon_21";
		break;

	case "lepricon_21":
		dialog.text = "Yo no soy pirata. Y preferiría no haber sido parte de los eventos de hoy. Y... si estás tan molesto por la vista de los cuerpos de mujeres en el suelo ennegrecido de Mérida, ¿por qué actuaste de la manera en que lo hiciste con los indios, Prince?";
		link.l1 = "¿Qué se suponía que debía hacer? ¿Dejar todo y arrastrarme hasta Marcus con una disculpa?";
		link.l1.go = "lepricon_22";
		break;

	case "lepricon_22":
		dialog.text = "Solo pensé que lo habrías abrazado completamente, empezando a pensar y actuar como los capitanes de Tirax. Pero no, ¡ja! Eres demasiado blando para este tipo de trabajo. Estarías mejor entregando tu parte a Marcus y yéndote con el rabo entre las piernas. Esto no es lo tuyo.";
		link.l1 = "No te corresponde decidir por mí, Duende. Y ciertamente no tienes derecho a insultarme. No cederé mi parte a nadie. La dividiré justamente con Terrax.";
		link.l1.go = "lepricon_23";
		break;

	case "lepricon_23":
		dialog.text = "Claro. Pero será mejor que nos vayamos antes de que te desmayes.";
		link.l1 = "Eso no es gracioso, maldita sea.";
		link.l1.go = "lepricon_30";
		break;

	case "lepricon_24":
		dialog.text = "Entonces no lo conoces bien. Aún así, ya que los eventos de hoy no te traen alegría, escucha lo que tengo para ofrecerte.";
		link.l1 = "¿Qué podrías ofrecer después de esto?!";
		link.l1.go = "lepricon_25";
		break;

	case "lepricon_25":
		dialog.text = "Será mejor que te esfuerces por escuchar, muchacho.";
		link.l1 = "Hum, no me gusta tu tono, Lucas, pero bien, sigue adelante.";
		link.l1.go = "lepricon_26";
		break;

	case "lepricon_26":
		dialog.text = "Puedo permitírmelo - he vivido más que tú, Prince. Así que tengo buen ojo, no solo para disparar. ¿Quieres saber qué he notado?";
		link.l1 = "¡Solo dilo!";
		link.l1.go = "lepricon_27";
		break;

	case "lepricon_27":
		dialog.text = "Estás fuera de lugar. Sí, eres bueno. Estás progresando. Pero sólo porque eres un capitán fuerte, no porque esto sea verdaderamente tu vocación. No sé cómo llegaste a Terrax, o por qué, pero créeme, esto no es lo tuyo.";
		link.l1 = "Tengo... un objetivo. No puedo decirte cuál es.";
		link.l1.go = "lepricon_28";
		break;

	case "lepricon_28":
		dialog.text = "¿Y te has acercado a ello?";
		link.l1 = "Todavía no.";
		link.l1.go = "lepricon_29";
		break;

	case "lepricon_29":
		dialog.text = "Bueno, si ni siquiera hoy te acercó más, no hay nada más que ganar aquí. Eres un buen tipo, Prince. Trataste a los indios como humanos. Es irónico que terminaras aquí con nosotros. Mi consejo: dale tu parte a Terrax para evitar problemas, y aléjate de todo esto - salva tu alma mientras puedas.";
		link.l1 = "Lo pensaré.";
		link.l1.go = "lepricon_30";
		break;

	case "lepricon_30":
		DialogExit();
		locCameraFromToPos(21.35, 1.54, 0.05, true, 25.55, 0.46, -0.91);
		if (CheckAttribute(pchar, "questTemp.Mtraxx_MeridaZloVariant"))
		{
			PlaySound("People Fight\PistolShot.wav");
			DoQuestFunctionDelay("Mtraxx_MeridaGorit_5", 2.0);
		}
		else
		{
			DoQuestFunctionDelay("Mtraxx_MeridaGorit_5", 0.5);
		}
		break;

	// Тагофа - проводник к Мериде
	case "tagofa":
		dialog.text = "Tagofa te saluda, hijo del mar. ¿Quieres que te muestre el camino al asentamiento español en las montañas?";
		link.l1 = "Correcto. Veo que eres bueno con nuestro idioma a diferencia del resto de tu gente.";
		link.l1.go = "tagofa_1";
		break;

	case "tagofa_1":
		dialog.text = "Tagofa a menudo tenía tratos con yalanaui... La mayor parte del camino viajaremos por un río. Necesitarás barcos largos. ¿Los tienes?";
		link.l1 = "¿De veras? Podríamos tomarlas prestadas por un ratito...";
		link.l1.go = "tagofa_2";
		break;

	case "tagofa_2":
		dialog.text = "Nuestro pueblo es pequeño, tenemos muy pocos botes largos y todos ellos son útiles solo para la pesca. Ahora, necesitamos buenos botes largos, aquellos que soporten un largo viaje, como los de tus barcos.";
		link.l1 = "Hmm... Necesitaremos seis botes largos entonces. El barco no tiene tantos.";
		link.l1.go = "tagofa_3";
		break;

	case "tagofa_3":
		dialog.text = "Entonces constrúyelos. Vosotros, los blancos, podéis reparar vuestros gigantescos navíos en tierra, seguramente podéis hacer unas pocas chalupas.";
		link.l1 = "Heh, parece que tienes razón, Tagofa. Llévanos al río, espero que no esté lejos de aquí.";
		link.l1.go = "tagofa_4";
		break;

	case "tagofa_4":
		dialog.text = "No lo es. Sígueme.";
		link.l1 = "...";
		link.l1.go = "tagofa_5";
		break;

	case "tagofa_5":
		DialogExit();
		chrDisableReloadToLocation = true;
		npchar.dialog.currentnode = "tagofa_6";
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_MeridaGotoRiver", 5.0);
		break;

	case "tagofa_6":
		dialog.text = "Aquí está el río del que te hablé. Comenzaremos nuestro viaje desde aquí. Tú construyes los botes y luego empezaremos.";
		link.l1 = "Entendido, Tagofa. Te avisaré cuando esté hecho.";
		link.l1.go = "tagofa_7";
		break;

	case "tagofa_7":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		npchar.dialog.currentnode = "tagofa_8";
		LAi_SetWarriorType(npchar);
		LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		pchar.questTemp.Mtraxx = "merida_boats";
		pchar.questTemp.Mtraxx.Boats = "true";
		chrDisableReloadToLocation = false;
		DoQuestCheckDelay("TalkSelf_Quest", 2.0);
		// Лепрекона - гулять
		sld = characterFromId("Lepricon");
		sld.dialog.currentnode = "lepricon_3";
		LAi_SetWarriorType(sld);
		LAi_warrior_DialogEnable(sld, true);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
		SetFunctionTimerCondition("Mtraxx_MeridaBoatLate", 0, 0, 10, false); // таймер, чтобы не ходил долго
		break;

	case "tagofa_8":
		dialog.text = "¿Están listos los botes, jefe blanco?";
		link.l1 = "Sí. Mis hombres están a punto de abordarlos.";
		link.l1.go = "tagofa_9";
		break;

	case "tagofa_9":
		dialog.text = "Muy bien. Súbete al primero junto conmigo. Tagofa mostrará el camino.";
		link.l1 = "";
		link.l1.go = "tagofa_10";
		break;

	case "tagofa_10":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "Mtraxx_MeridaRiverTrip", -1);
		chrDisableReloadToLocation = true;
		break;

	case "tagofa_11":
		dialog.text = "La parte del río está hecha. No estamos lejos del asentamiento español desde aquí. Ahí está el sendero, síguelo y no nos perderemos. Hemos logrado rodear un bosque lleno de cazadores de Capong, pero aquí también es su tierra. Debemos tener cuidado.";
		link.l1 = "No te preocupes. Los eliminaremos tan pronto como nos muestren sus feas caras pintadas.";
		link.l1.go = "tagofa_12";
		break;

	case "tagofa_12":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		pchar.quest.mtraxx_merida_warning.win_condition.l1 = "locator";
		pchar.quest.mtraxx_merida_warning.win_condition.l1.location = "Serpentine2";
		pchar.quest.mtraxx_merida_warning.win_condition.l1.locator_group = "quest";
		pchar.quest.mtraxx_merida_warning.win_condition.l1.locator = "detector1";
		pchar.quest.mtraxx_merida_warning.function = "Mtraxx_MeridaWarning";
		chrDisableReloadToLocation = false;
		break;

	case "tagofa_13":
		StartQuestMovie(true, false, true);
		dialog.text = "";
		link.l1 = "¡Oye! ¡Tagofa! ¡Mira! ¿Qué es eso... en medio del camino? Alguna cosa india.";
		link.l1.go = "tagofa_14";
		locCameraFromToPos(7.63, 9.07, 11.73, true, 2.97, 9.02, 7.70);
		CharacterTurnToLoc(pchar, "quest", "quest1");
		break;

	case "tagofa_14":
		DialogExit();
		LAi_SetActorType(pchar);
		LAi_FadeLong("Mtraxx_MeridaWarningCutscene", "");
		locCameraSleep(true);
		break;

	case "tagofa_15":
		dialog.text = "Es una señal de los Capongs. Una advertencia. Te dice que te detengas y no sigas adelante. Los Capongs ya nos han visto.";
		link.l1 = "¿Y qué si vamos más allá? ¿Nos atacarán?";
		link.l1.go = "tagofa_16";
		break;

	case "tagofa_16":
		dialog.text = "Sí, jefe blanco. Debes parecerles amenazante ya que no nos atacaron todavía. Y aun así, pusieron un signo para ti.";
		link.l1 = "Al diablo con la señal. Seguimos adelante... ¡Todos escuchen! ¡A las armas! ¡Preparaos! ¡Estad alerta! ¡Si esos salvajes nos muestran sus feas caras, los mataremos a todos!";
		link.l1.go = "tagofa_17";
		break;

	case "tagofa_17":
		DialogExit();
		EndQuestMovie();
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		pchar.quest.mtraxx_merida_capong.win_condition.l1 = "location";
		pchar.quest.mtraxx_merida_capong.win_condition.l1.location = "Merida_jungle_01";
		pchar.quest.mtraxx_merida_capong.function = "Mtraxx_MeridaPrepareCapongAttack";
		break;

	case "tagofa_18":
		dialog.text = "El jefe blanco y sus hombres aplastaron a los capongas, Tagofa está impresionado. La ciudad española está cerca. Hay un valle donde verás una cascada. Tagofa no irá a los españoles. Te estaré esperando cerca de la cascada.";
		link.l1 = "Muy bien. ¡Adelante!";
		link.l1.go = "tagofa_19";
		break;

	case "tagofa_19":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		chrDisableReloadToLocation = false;
		pchar.quest.mtraxx_merida_exittown.win_condition.l1 = "location";
		pchar.quest.mtraxx_merida_exittown.win_condition.l1.location = "Merida_ExitTown";
		pchar.quest.mtraxx_merida_exittown.function = "Mtraxx_MeridaExitTown";
		Mtraxx_MeridaCheckOurWarriors();
		AddQuestRecord("Roger_5", "15");
		break;

	case "tagofa_20":
		dialog.text = "Hemos regresado, jefe blanco. Tagofa hizo lo que prometió.";
		link.l1 = "Gratitud, Tagofa. Lo hiciste bien.";
		link.l1.go = "tagofa_21";
		break;

	case "tagofa_21":
		dialog.text = "Tagofa debería irse. Hayami me está esperando mucho. Adiós hijo del mar.";
		link.l1 = "Buena suerte, hijo de la selva. Manda mis saludos a tu esposa. Y gracias por ayudarnos.";
		link.l1.go = "tagofa_22";
		break;

	case "tagofa_22":
		DialogExit();
		chrDisableReloadToLocation = false;
		npchar.lifeday = 0;
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 20.0);
		LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		pchar.quest.mtraxx_merida_final.win_condition.l1 = "location";
		pchar.quest.mtraxx_merida_final.win_condition.l1.location = "Shore_ship3";
		pchar.quest.mtraxx_merida_final.function = "Mtraxx_MeridaFinal";
		ChangeIndianRelation(7.0);
		break;

	// дозорный у Мериды
	case "merida_guard":
		dialog.text = "¡Eh! ¿Quién eres y qué quieres?";
		link.l1 = "Necesitamos llegar a Mérida y tener una charla con tu gobernador o quien sea que tengas en su lugar...";
		link.l1.go = "merida_guard_1";
		break;

	case "merida_guard_1":
		dialog.text = "No dejamos entrar a extraños a Mérida. ¡Fuera!";
		link.l1 = "Compañero, estuvimos remando con fuerza durante dos días y luego luchando contra hordas de indios para no irnos así como así. ¡Repito, quiero hablar con el jefe de tu aldea! Tenemos una... propuesta de negocio para él, ¡sí! Y si todos estamos de acuerdo, tu aldea permanecerá intacta.";
		link.l1.go = "merida_guard_2";
		break;

	case "merida_guard_2":
		dialog.text = "¿Estás haciendo amenazas, ladrón?";
		link.l1 = "¿Cómo lo averiguaste? Ah, sí, en efecto, estoy haciendo amenazas. O conseguimos lo que vinimos a buscar aquí en paz o por la fuerza, y tienes el honor de decidir el destino de tu aldea.";
		link.l1.go = "merida_guard_3";
		break;

	case "merida_guard_3":
		dialog.text = "¡Nunca entrarás en Mérida, maldito pirata! ¡Alarma! ¡Enemigo a las puertas!";
		link.l1 = "Qué caballero tan irrazonable...";
		link.l1.go = "merida_guard_4";
		break;

	case "merida_guard_4":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload2", "none", "", "", "", 10.0);
		DoQuestFunctionDelay("Mtraxx_MeridaHouseGuards", 5.0);
		break;

	// мэр Мериды
	case "merida_head":
		dialog.text = "¡Malditos ladrones! ¿Qué quieren de nosotros?! Este es un asentamiento pequeño y modesto. ¡No tenemos ni oro ni plata! ¿Cómo se enteraron siquiera de nosotros?";
		link.l1 = "Oh, no juegues a ser inocente y despistado, Su Excelencia. Todo el mundo ya está lleno de rumores sobre tus ópalos.";
		link.l1.go = "merida_head_1";
		break;

	case "merida_head_1":
		dialog.text = "¿Y causaste esta masacre impía por... rumores?! ¡No perdonaste a nadie! Bestias... Déjame decirte: los depósitos están muy lejos de aquí. No hay nada que puedas ganar aquí. Vete.";
		link.l1 = "Comenzaste esta masacre impía. Los civiles lucharon junto a tus soldados. Nunca creeré que sea posible semejante heroísmo sin sentido solo para proteger unas pocas paredes desnudas.";
		link.l1.go = "merida_head_2";
		break;

	case "merida_head_2":
		dialog.text = "¿Sabes cuánto esfuerzo se necesitó para construir estos muros? No contratamos constructores externos, los construimos nosotros mismos, ladrillo por ladrillo. Cada uno de los residentes. Incluso yo, con estas mismas manos.";
		link.l1 = "Qué historia tan conmovedora... ¿Y qué hay del mobiliario? ¿También lo hicieron ustedes mismos? Qué silla tan finamente tallada. Y la mesa. Y los armarios. ¿Es roble teñido? ¿O ébano? Un poco demasiado lujoso para un 'asentamiento modesto', ¿no crees?";
		link.l1.go = "merida_head_3";
		break;

	case "merida_head_3":
		dialog.text = "La avaricia ha nublado tu mente, ladrón.";
		link.l1 = "No hay necesidad de complicar las cosas, señor Gobernador. O lo lamentarás.";
		link.l1.go = "merida_head_4";
		break;

	case "merida_head_4":
		dialog.text = "¿Vas a torturarme, maldito pirata? Lástima para ti, yo creo en Dios Todopoderoso. Y ascenderé como mártir si te pasas de la raya.";
		link.l1 = "Mm-m...";
		link.l1.go = "merida_head_5";
		break;

	case "merida_head_5":
		StartInstantDialog("Mrt_Rocur", "merida_head_6", "Quest\Roger.c");
		break;

	case "merida_head_6":
		dialog.text = "Mi amigo, no va a hablar de esta manera. Déjame manejarlo.";
		link.l1 = "¿Oh?";
		link.l1.go = "merida_head_7";
		break;

	case "merida_head_7":
		dialog.text = "Recuerdo todo lo que esos españoles engreídos me hicieron en esa maldita plantación. Estaré encantado de mostrártelo, Prince. Y te contaré algunas historias mientras lo hago. No te aburrirás.";
		link.l1 = "¿Y qué si te dejas llevar?";
		link.l1.go = "merida_head_8";
		break;

	case "merida_head_8":
		dialog.text = "No hablará amablemente. Conozco a su tipo.";
		if (IsCharacterPerkOn(pchar, "Trustworthy") && sti(pchar.reputation.nobility) >= 50 && GetSummonSkillFromName(pchar, SKILL_Leadership) >= 50)
		{
			link.l1 = "(Confiable) (Honor) (Liderazgo) Ya es suficiente sangre por hoy, Jean. Me encargaré de esto yo mismo.";
			link.l1.go = "merida_head_dobro_1";
			notification("Trustworthy", "Trustworthy");
			notification("¡Comprobación de reputación aprobada!", "None");
			notification("¡Prueba de habilidad aprobada!", SKILL_Leadership);
		}
		else
		{
			if (!IsCharacterPerkOn(pchar, "Trustworthy"))
				notification("¡Comprobación de beneficios fallida!", "Trustworthy");
			if (sti(pchar.reputation.nobility) < 50)
				notification("¡Reputación demasiado baja! (" + XI_ConvertString(GetReputationName(50)) + ")", "None");
			if (GetCharacterSkill(pchar, SKILL_LEADERSHIP) < 50)
				notification("¡Prueba de habilidad fallida! (50)", SKILL_LEADERSHIP);
		}
		link.l2 = "Hazlo. No me voy a involucrar. Y tampoco voy a mirar.";
		link.l2.go = "merida_head_zlo_1";
		break;

	case "merida_head_zlo_1":
		dialog.text = "Si no estuviera en deuda contigo, tendría unas cuantas palabras para ti... Maldita sea. Adelante. Ahora es el momento del verdadero trabajo.";
		link.l1 = "No te esfuerces demasiado.";
		link.l1.go = "rocur_42";
		break;

	case "merida_head_dobro_1":
		dialog.text = "Como desees, mi amigo. Será divertido de ver.";
		link.l1 = "No te rías demasiado pronto.";
		link.l1.go = "merida_head_dobro_2";
		break;

	case "merida_head_dobro_2":
		StartInstantDialog("Merida_Head", "merida_head_dobro_3", "Quest\Roger.c");
		break;

	case "merida_head_dobro_3":
		dialog.text = "¿Dices que lo manejarás tú mismo, sin derramamiento de sangre, maldito ladrón? ¡No hay nada que puedas decir para hacer aparecer piedras de la nada!";
		link.l1 = "Mejor que aparezcan, Gobernador. De lo contrario, arrasaremos la ciudad y mataremos a todos menos a usted. No me gusta esta solución, pero estoy dispuesto a comprometer mi honor por mi causa. Su deber, por otro lado, es proteger a los civiles, soldados sobrevivientes y trabajadores de Mérida. ¿O preferiría 'ascender como mártir' a costa de su sufrimiento? Eso no me suena muy divino.";
		link.l1.go = "merida_head_dobro_4";
		break;

	case "merida_head_dobro_4":
		dialog.text = "Maldición...\nAllí... en el cofre. ¡Sólo perdona a los habitantes del pueblo!";
		if (GetSummonSkillFromName(pchar, SKILL_Sneak) >= 50)
		{
			link.l1 = "¿Está todo en el cofre?";
			link.l1.go = "merida_head_dobro_vnimatelnost_1";
			notification("¡Prueba de habilidad aprobada!", SKILL_Sneak);
		}
		else
		{
			link.l1 = "Mantengo mi palabra. Adiós, Gobernador.";
			link.l1.go = "merida_head_dobro_5";
			notification("¡Prueba de habilidad fallida! (50)", SKILL_SNEAK);
		}
		break;

	case "merida_head_dobro_vnimatelnost_1":
		dialog.text = "¡Maldito seas al infierno!\nEl cofre también tiene un fondo falso. ¡Toma todo!!";
		link.l1 = "Estoy aquí para ver a Marcus.";
		link.l1.go = "merida_head_dobro_vnimatelnost_2";
		pchar.questTemp.Mtraxx_MeridaKamushki = true;
		break;

	case "merida_head_dobro_vnimatelnost_2":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocator(npchar, "goto", "goto2", "Mtraxx_MeridaOpenChest", -1);
		sld = characterFromId("Mrt_Rocur");
		LAi_SetActorType(sld);
		break;

	case "merida_head_dobro_vnimatelnost_3":
		dialog.text = "Despacio, Prince. Perdón por subestimarte.";
		link.l1 = "¿Satisfecho?";
		link.l1.go = "merida_head_dobro_7";
		break;

	case "merida_head_dobro_5":
		StartInstantDialog("Mrt_Rocur", "merida_head_dobro_6", "Quest\Roger.c");
		break;

	case "merida_head_dobro_6":
		dialog.text = "Tranquilo, Prince.";
		link.l1 = "¿Satisfecho?";
		link.l1.go = "merida_head_dobro_7";
		break;

	case "merida_head_dobro_7":
		dialog.text = "Más que eso. Pero... ya lo verás por ti mismo. Ve tú; yo indagaré un poco más.";
		link.l1 = "...";
		link.l1.go = "rocur_43";
		break;

		/*case "merida_head_99999":
			DialogExit();
			sld = characterFromId("Mrt_Rocur");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocator(sld, "goto", "goto2", "Mtraxx_MeridaGiveJewelry", -1);
		break;*/

	case "merida_head_sleep":
		dialog.text = "Prometiste dejar la ciudad una vez que tuvieras las gemas... ¡Ahora las tienes y tus ladrones han incendiado nuestras casas! ¡Eres un mentiroso y un vil pirata! ¡Espero que las llamas del infierno sean así de calientes para ti!!!";
		link.l1 = "";
		link.l1.go = "exit";
		locCameraFromToPos(19.18, 1.28, -0.28, true, 24.88, 1.62, -1.19);
		AddDialogExitQuest("Mtraxx_RetributionSleep2");
		break;

	// капитан пинаса Китти
	case "kittycap":
		dialog.text = TimeGreeting() + ", buen señor. ¿Cuál es tu propósito aquí?";
		link.l1 = "Soy de Tyrex. Me dijeron que escoltara tu navío hasta Bridgetown. ¿Estás listo?";
		link.l1.go = "kittycap_1";
		break;

	case "kittycap_1":
		dialog.text = "¡Pues, finalmente! ¡Sí, mi tripulación está lista para zarpar de inmediato!";
		link.l1 = "Espléndido. Prepara las velas, capitán. ¡Pongámonos en marcha!";
		link.l1.go = "kittycap_2";
		break;

	case "kittycap_2":
		DialogExit();
		LAi_CharacterDisableDialog(npchar);
		Group_DelCharacter("Mtr_Kitty", "Mtr_KittyCap");
		SetCharacterRemovable(npchar, false);
		npchar.CompanionEnemyEnable = false; // всегда друзья
		LAi_SetImmortal(npchar, false);
		SetCompanionIndex(pchar, -1, sti(npchar.index));
		npchar.loyality = MAX_LOYALITY;
		pchar.quest.mtraxx_ignasio_sail.win_condition.l1 = "location";
		pchar.quest.mtraxx_ignasio_sail.win_condition.l1.location = "Bridgetown_town";
		pchar.quest.mtraxx_ignasio_sail.function = "Mtraxx_IgnasioArrive";
		SetFunctionTimerCondition("Mtraxx_IgnasioTimeOver", 0, 0, 30, false);
		pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1 = "NPC_Death";
		pchar.quest.mtraxx_ignasio_sinkkitty.win_condition.l1.character = "Mtr_KittyCap";
		pchar.quest.mtraxx_ignasio_sinkkitty.function = "Mtraxx_IgnasioKittySink";
		bQuestDisableMapEnter = false; // открыть карту
		DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;

	case "kittycap_3":
		dialog.text = "¡Gracias por ayudarme, capitán! A tu lado estaba tan seguro como si estuviera detrás de las murallas del fuerte.";
		link.l1 = "¡Ja, no lo menciones, camarada! Todo está a cargo de Marcus. ¡Buena suerte, compañero!";
		link.l1.go = "kittycap_4";
		break;

	case "kittycap_4":
		DialogExit();
		npchar.lifeday = 0;
		RemoveCharacterCompanion(pchar, npchar);
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
		Mtraxx_IgnasioCreateMarko();
		AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;

	// Игнасио Марко
	case "ignasio":
		PlaySound("Voice\Spanish\LE\Ignasio_Marko\Ignasio_01.wav");
		dialog.text = "¡Ah, valiente capitán! Permítame presentarme: soy un corsario de Inglaterra, Ignacio Marco. A su servicio.";
		link.l1 = TimeGreeting() + ", amigo. Capitán " + GetFullName(pchar) + " a su servicio. ¿Cómo puedo ayudarle?";
		link.l1.go = "ignasio_1";
		break;

	case "ignasio_1":
		PlaySound("Voice\Spanish\LE\Ignasio_Marko\Ignasio_02.wav");
		dialog.text = "¡Oh, lo conozco! Monsieur " + GetFullName(pchar) + "¡Los rumores sobre sus recursos y mecenas me han estado llegando por todo el Archipiélago. Tengo una propuesta para usted capitán, que le resultará muy elegante.";
		link.l1 = "¿Qué oferta?";
		link.l1.go = "ignasio_2";
		break;

	case "ignasio_2":
		dialog.text = "Vamos a una taberna a tomar un trago. Te lo contaré todo. No es conversación de calle.";
		link.l1 = "Muy bien... ¡Vamos!";
		link.l1.go = "ignasio_3";
		break;

	case "ignasio_3":
		DialogExit();
		FreeSitLocator("Bridgetown_tavern", "sit_front2");
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "Bridgetown_tavern", "sit", "sit_front2", "Mtraxx_IgnasioInTavern", -1);
		break;

	case "ignasio_4":
		LAi_SetSitType(pchar);
		dialog.text = "¿Una ronda, capitán?";
		link.l1 = "¡Claro!";
		link.l1.go = "ignasio_5";
		break;

	case "ignasio_5":
		LAi_Fade("", "");
		dialog.text = "Heh, aquí de hecho no mezclan el ron con agua...";
		link.l1 = "Y no trates a los clientes con pescado podrido, sí-sí. Entonces, ¿cuál es el trato?";
		link.l1.go = "ignasio_6";
		break;

	case "ignasio_6":
		dialog.text = "Me gusta tu franqueza, monsieur. Dime, ¿estás al tanto de la guerra comercial entre los ingleses y los holandeses?";
		link.l1 = "Lo estoy. Tuve el placer de participar en ella.";
		link.l1.go = "ignasio_7";
		break;

	case "ignasio_7":
		PlaySound("Voice\Spanish\LE\Ignasio_Marko\Ignasio_02.wav");
		dialog.text = "Entonces no hace falta explicarlo. Siendo un corsario inglés, lucho en esta guerra de su lado. Usted es más bien un alma libre. Le es indiferente en qué lado combatir...";
		link.l1 = "Casi. No peleo contra Francia, lo siento.";
		link.l1.go = "ignasio_8";
		break;

	case "ignasio_8":
		dialog.text = "¡Capitán, no hace falta ni aclararlo! En fin, al grano: hay una pequeña isla habitada entre Curazao y Trinidad, no está en los mapas... Desde hace poco, diría que muy poco, los holandeses han comenzado a usarla como parada temporal para reabastecerse y reparar. Parece que creen que solo ellos conocen esta isla. Equivocados. Ja-ja.\nHace un par de días, una caravana de plata fue atrapada por una... tormenta, y ahora los holandeses están reparando sus barcos en esta isla. El buque insignia perdió su mástil, por lo que tomará algún tiempo repararlo. Los holandeses están ocupados con las reparaciones, y las tripulaciones están mayormente dispersas por la isla...";
		link.l1 = "¿Y entonces de repente aparecemos para salvar el día?";
		link.l1.go = "ignasio_9";
		break;

	case "ignasio_9":
		dialog.text = "Exactamente, capitán. No puedo hacer esto solo, pero contigo - es una historia totalmente diferente. ¿Te arriesgarás? Tengo un gran barco, la tripulación es excelente y tengo una buena cantidad de experiencia. Tu destreza... también es encomiable.";
		link.l1 = "¿Cuánto tiempo tenemos?";
		link.l1.go = "ignasio_10";
		break;

	case "ignasio_10":
		dialog.text = "Mucho, si no lo desperdiciamos y nos ponemos en marcha inmediatamente.";
		link.l1 = "Entonces, reaprovisionémonos con municiones y armas, capitán Ignacio Marco, y levantemos velas. ¿Cuáles son las coordenadas exactas de la isla?";
		link.l1.go = "ignasio_11";
		break;

	case "ignasio_11":
		dialog.text = "12'40 Norte, 64'11 Oeste. ¿Entendido?";
		if (CheckAttribute(pchar, "questTemp.HWIC.Isladecoche"))
			link.l1 = "¡Ja! Deja vu... Entendido.";
		else
			link.l1 = "Entendido.";
		link.l1.go = "ignasio_12";
		break;

	case "ignasio_12":
		dialog.text = "Rumbo al 'Torero'. ¡Te estaré esperando, capitán!";
		link.l1 = "... ";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_IgnasioAddMarko");
		break;

	case "ignasio_13":
		PlaySound("Voice\Spanish\LE\Ignasio_Marko\Ignasio_03.wav");
		dialog.text = "Un combate duro, ¿eh? Ahora pasemos a la mejor parte: nos repartimos el botín. La mitad va para mí y mis hombres.";
		link.l1 = "Muy bien, hagámoslo...";
		link.l1.go = "ignasio_14";
		break;

	case "ignasio_14":
		LAi_Fade("", "");
		WaitDate("", 0, 0, 0, 3, 10);
		pchar.questTemp.Mtraxx.Silver = GetSquadronGoods(pchar, GOOD_SILVER) - sti(pchar.questTemp.Mtraxx.Silver);
		pchar.questTemp.Mtraxx.Mahogany = GetSquadronGoods(pchar, GOOD_MAHOGANY) - sti(pchar.questTemp.Mtraxx.Mahogany);
		if (sti(pchar.questTemp.Mtraxx.Silver) < 100)
		{
			dialog.text = "Capitán, ¿qué sucede? ¿Dónde está nuestra plata? ¿Hundiste nuestro premio?";
			if (sti(pchar.questTemp.Mtraxx.Mahogany) < 200)
			{
				link.l1 = "Mm...";
				link.l1.go = "ignasio_15_1";
			}
			else
			{
				link.l1 = "La plata se desperdició de alguna manera aunque conseguimos un poco de caoba. Vamos a dividirla.";
				link.l1.go = "ignasio_15_11";
			}
			break;
		}
		if (sti(pchar.questTemp.Mtraxx.Silver) < 300 && sti(pchar.questTemp.Mtraxx.Silver) > 100)
		{
			dialog.text = "Mm.. Esto es pobre. Pensé que habría mucho más.";
			link.l1 = "Tenemos lo que tenemos.";
			link.l1.go = "ignasio_15_2";
			break;
		}
		if (sti(pchar.questTemp.Mtraxx.Silver) < 700 && sti(pchar.questTemp.Mtraxx.Silver) > 300)
		{
			dialog.text = "No está mal, no está mal. Aunque pensé que habría más.";
			link.l1 = "Tenemos lo que tenemos.";
			link.l1.go = "ignasio_15_3";
			break;
		}
		dialog.text = "Bien hecho, Monseñor. Este es un buen premio...";
		link.l1 = "No puedo estar en desacuerdo contigo en esto, capitán.";
		link.l1.go = "ignasio_15_4";
		break;

	case "ignasio_15_1":
		dialog.text = "Parece que tienes un serio problema con la cabeza. ¡Nos vamos! ¡Chicos!";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;

	case "ignasio_15_11":
		RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany) / 2));
		dialog.text = "Al menos conseguimos algo de esto... ¡Chicos! ¡Vámonos!";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;

	case "ignasio_15_2":
		RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver) / 2));
		RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany) / 2));
		dialog.text = "Es algo.  Sigamos nuestros caminos.";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;

	case "ignasio_15_3":
		RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver) / 2));
		RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany) / 2));
		dialog.text = "Es algo. Vamos a separarnos. Es un éxito después de todo, ¡jeh!";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;

	case "ignasio_15_4":
		RemoveCharacterGoods(pchar, GOOD_SILVER, makeint(sti(pchar.questTemp.Mtraxx.Silver) / 2));
		RemoveCharacterGoods(pchar, GOOD_MAHOGANY, makeint(sti(pchar.questTemp.Mtraxx.Mahogany) / 2));
		dialog.text = "¡Hemos tenido una reunión muy provechosa! Quizás, no sea la última vez que hagamos negocios juntos, ¡capitán!";
		link.l1 = "¡Llámame si encuentras más comerciantes gordos, je-je!";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_IgnasioEscape");
		break;

	case "ignasio_boarding":
		PlaySound("Voice\Spanish\LE\Ignasio_Marko\Ignasio_04.wav");
		dialog.text = "Supongo que, no nos conocimos por casualidad, ¿verdad, capitán?";
		link.l1 = "No serías inteligente si no lo vieras. Me debes por el montaje. Sabes de qué estoy hablando. Además, me debes por tenderle una trampa a mi amigo Jean Picard. Fue vendido a la plantación después de tu esquema... Perdiste a Ignacio. Voy a colgarte, pero puedes aliviar tu castigo...";
		link.l1.go = "ignasio_boarding_1";
		break;

	case "ignasio_boarding_1":
		dialog.text = "Me pregunto incluso, ¿qué podría hacer para que sientas lástima por mí?";
		link.l1 = "Necesito información. Te meteré en mi bodega de carga donde hablaremos de tus planes en La Habana...";
		link.l1.go = "ignasio_boarding_2";
		break;

	case "ignasio_boarding_2":
		dialog.text = RandSwear() + " ¡No vi esto venir! Ni lo pienses. Barbazon se enterará de mi traición en un santiamén. Más te vale no saber lo que hace a quienes lo traicionan. Lo he visto.";
		link.l1 = "¿Así que ser ahorcado es una mejor opción?";
		link.l1.go = "ignasio_boarding_3";
		break;

	case "ignasio_boarding_3":
		dialog.text = "¡Prefiero morir en combate!";
		link.l1 = "...";
		link.l1.go = "ignasio_boarding_4";
		break;

	case "ignasio_boarding_4":
		DialogExit();
		LAi_SetCurHPMax(npchar);
		LAi_GetCharacterMaxEnergy(npchar);
		QuestAboardCabinDialogFree();
		LAi_group_SetRelation(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups(LAI_GROUP_BRDENEMY, LAI_GROUP_PLAYER, true);
		AddDialogExitQuest("MainHeroFightModeOn");
		break;

	case "spy_sailor":
		dialog.text = "¡Capitán! ¡Capitán! ¡Rápido! ¡La escuadra militar española nos persigue!";
		link.l1 = RandSwear() + "Esperaba esto... La misma historia le pasó a Picard. ¿Viste cuántos de ellos estaban allá afuera?";
		link.l1.go = "spy_sailor_1";
		break;

	case "spy_sailor_1":
		dialog.text = "Sí, capitán. Tres barcos. Su buque insignia es un galeón, el más grande que jamás haya visto y se mueve rápido, los otros dos son una corbeta y un jabeque.";
		link.l1 = "Todos a bordo.  Todavía podríamos estar en posición de huir.";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_IgnasioOurEscape");
		break;

	// индей-кариб в гроте Порто-Белло
	case "grot_canib":
		dialog.text = "¡Haya! ¡Maldito yalanaui viene a nuestro bosque! ¡Mátenlo! ¡Haya!";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_WolfreekGrotFight");
		break;

	// бандит у пещеры Панамы
	case "cave_bandit":
		dialog.text = "¡Oye! ¿Qué demonios haces aquí? ¿A-ah, robando las pertenencias de otros? ¡Pues estás jodido!";
		link.l1 = "...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_WolfreekCaveFight");
		break;

	case "carpenter":
		dialog.text = "¡Oye! ¡Todos quietos ahí! ¡O los llevaré a todos con una descarga de metralla!" + RandSwear() + "";
		link.l1 = "Ahora mismo no vamos a movernos a ningún lado. Pero escucha, camarada: no hay manera de que nos mates a todos de un solo disparo. Algunos de nosotros te haremos pedazos mientras recargas. Será mejor que hablemos ahora mismo.";
		link.l1.go = "carpenter_1";
		locCameraFromToPos(-71.57, 14.57, -130.20, true, -63.78, 11.36, -125.50);
		break;

	case "carpenter_1":
		dialog.text = "¿Estás a cargo aquí? ¡Respóndeme!";
		link.l1 = "Soy capitán " + GetFullName(pchar) + ". Y tú debes ser el segundo al mando del Lobo Rojo mientras él está fuera de aquí, ¿verdad?";
		link.l1.go = "carpenter_2";
		break;

	case "carpenter_2":
		dialog.text = "¿Qué haces aquí capitán " + GetFullName(pchar) + "? ¡No invitamos a huéspedes a este lugar!";
		link.l1 = "¿Cuál es tu nombre? Quiero saber con quién estoy hablando.";
		link.l1.go = "carpenter_3";
		break;

	case "carpenter_3":
		dialog.text = "Me llamo Rodgar Janssen.";
		link.l1 = "Veo que ustedes están en la oscuridad aquí. Ya no tienen capitán. Y su corbeta también se ha ido. La 'Freyja' fue bombardeada hasta el infierno por los españoles no lejos de La Española. Su tripulación fue aniquilada hasta el último...";
		link.l1.go = "carpenter_4";
		break;

	case "carpenter_4":
		dialog.text = RandSwear() + "Wulfric... ¡Aahhh-ghhhhh! ... Pero, ¿cómo puedo saber que dices la verdad?";
		link.l1 = "Tengo el diario de tu ex-capitán. Hemos conseguido algunos objetos de los restos del Freyja. Gracias al diario he encontrado esta isla y este... tesoro tuyo.";
		link.l1.go = "carpenter_5";
		break;

	case "carpenter_5":
		dialog.text = "¡Je! Todavía me debes una respuesta: ¿por qué estás aquí en esta tierra desconocida?";
		link.l1 = "No voy a mentir, amigo. Dicen que el Lobo Rojo poseía una gran fortuna. Estoy aquí para encontrarla ya que no se encontró tal tesoro en su barco. Creo que debería pertenecer a la buena gente, ya no le sirve de nada a Wulfric.";
		link.l1.go = "carpenter_6";
		break;

	case "carpenter_6":
		dialog.text = "¡Ja! Compañero, voy a decepcionarte: ni yo ni nadie más de la tripulación jamás vimos los tesoros de Wolf. Era demasiado arriesgado preguntárselo.";
		link.l1 = "Entonces, probablemente debería buscarlos en tu aldea. ¿Apartarás tu arma o debería empezar a asaltar la aldea? No tienes oportunidad, Rodgar. Traeré armas y más hombres si es necesario.";
		link.l1.go = "carpenter_7";
		break;

	case "carpenter_7":
		dialog.text = "¡Antes de morir, llevaremos a muchos de vosotros, bastardos, al infierno! ¡Quizás a ti también!";
		link.l1 = "¿Estás seguro? No tienes capitán, ni barco y nadie vendrá a salvarte. ¡Incluso si me voy, todos morirán de hambre pronto!";
		link.l1.go = "carpenter_8";
		break;

	case "carpenter_8":
		dialog.text = "Mm... ¿tienes alguna sugerencia?";
		link.l1 = "Sí, lo hago. Aléjate del cañón y mantén a tus hombres bajo control. Te juro que no te haré daño a ti ni a tus hombres. Si lo deseas, puedes unirte a mi tripulación o te llevaremos a alguna civilización.";
		link.l1.go = "carpenter_9";
		break;

	case "carpenter_9":
		dialog.text = "¡Júralo ante tus hombres en voz alta y clara!";
		link.l1 = "¡Lo juro! Tienes mi palabra: tú y tus hombres no serán dañados.";
		link.l1.go = "carpenter_10";
		break;

	case "carpenter_10":
		DialogExit();
		npchar.dialog.currentnode = "carpenter_11";
		LAi_SetActorType(npchar);
		LAi_ActorDialog(npchar, pchar, "", -1, 0);
		for (i = 1; i <= 2; i++) //
		{
			sld = CharacterFromID("Islamona_fort_pirate_" + i);
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		break;

	case "carpenter_11":
		dialog.text = "Espero que mantengas tu palabra, capitán.";
		link.l1 = "Siempre lo hago. ¿Cuántos de ustedes quedan?";
		link.l1.go = "carpenter_12";
		break;

	case "carpenter_12":
		dialog.text = "Nos ves a todos. Tres. El resto murió en las selvas atacándote. Les dije que no lo hicieran, pero no escucharon...";
		link.l1 = "Ya veo...";
		link.l1.go = "carpenter_13";
		break;

	case "carpenter_13":
		dialog.text = "Se nos acababa la comida. Empezamos a cazar loros. El 'Freyja' estuvo ausente demasiado tiempo. Teníamos nuestras sospechas y se hicieron realidad.";
		link.l1 = "Gracias a Dios por mi decisión de ir a buscar tesoros. ¿Dónde crees que los escondió?";
		link.l1.go = "carpenter_14";
		break;

	case "carpenter_14":
		dialog.text = "Ya te lo dije: nadie los ha visto jamás. Wulfric fue cuidadoso con su parte, nunca la dejó desperdiciar. Fue justo con nosotros, pero todos los que intentaron encontrar su alijo desaparecieron. Eres libre de buscar en el pueblo si así lo deseas.";
		link.l1 = "Ése es mi plan. ¿Dónde está la casa de Lobo Rojo?";
		link.l1.go = "carpenter_15";
		break;

	case "carpenter_15":
		dialog.text = "El único edificio de dos pisos que tenemos aquí.";
		link.l1 = "Bien. Por cierto, ¿cuál es tu ocupación?";
		link.l1.go = "carpenter_16";
		break;

	case "carpenter_16":
		worldMap.labels.islamona.icon = 5;
		worldMap.labels.islamona.text = CheckingTranslate(LanguageOpenFile("LocLables.txt"), "Islamona");
		dialog.text = "Soy carpintero y estos dos son mis ayudantes. Solíamos reparar y acondicionar la 'Freyja' antes. Podríamos ser de utilidad en tu tripulación.";
		link.l1 = "Entiendo. Muy bien, estás dentro, hablaremos de los detalles más tarde. Toma esta pistola de la entrada. Y Rodgar, no dejes el pueblo mientras busco el alijo.";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_WolfreekInFort");
		break;

	case "carpenter_17":
		dialog.text = "¿Órdenes, capitán?";
		if (CheckAttribute(pchar, "questTemp.Mtraxx.WolfreekGord"))
		{
			link.l1 = "Sí. Se han encontrado los tesoros de tu capitán. Los escondió bien, ¡pero lo he superado en astucia!";
			link.l1.go = "carpenter_18";
			break;
		}
		// Jason Исла Мона -->
		if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "start")
		{
			link.l1 = "Rodgar, ¿qué piensas, hay algo más que podamos hacer con esta base?";
			link.l1.go = "IslaMona";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "get_tools")
		{
			link.l1 = "Rodgar, traje las herramientas. Ya deberían haberte sido entregadas.";
			link.l1.go = "IslaMona_8";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "himenes")
		{
			link.l1 = "¡Bienvenido! Este es Rodrigo Jiménez, el líder de una pequeña pero muy trabajadora comunidad de Cádiz. El señor Jiménez amablemente aceptó asentarse temporalmente en nuestra tierra y ayudarnos con la construcción.";
			link.l1.go = "IslaMona_12";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "nextday")
		{
			link.l1 = "Rodgar, ¿cómo estás? ¿Tienes algún buen consejo para mí?";
			link.l1.go = "IslaMona_18";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "stalk")
		{
			link.l1 = "Rodgar, necesito un favor.";
			link.l1.go = "IslaMona_20";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "dublon_wait" && GetCharacterItem(pchar, "gold_dublon") >= 600)
		{
			link.l1 = "Te he traído los doblones, solo no los malgastes en ron de inmediato.";
			link.l1.go = "IslaMona_24";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "storage" && !CheckAttribute(pchar, "questTemp.IslaMona.Food") && IslaMona_CheckFood())
		{
			link.l1 = "Rodgar, revisa el almacén. He traído las medicinas y provisiones.";
			link.l1.go = "IslaMona_30";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.IslaMona") && pchar.questTemp.IslaMona == "village")
		{
			link.l1 = "Hola, Rodgar, ¿cómo van las cosas en el nuevo asentamiento?";
			link.l1.go = "IslaMona_32";
			break;
		}
		if (!CheckAttribute(npchar, "quest.stalk")) // ремонт кораблей
		{
			link.l2 = "Rodgar, mi barco necesita reparaciones. ¿Estáis listos tú y tus hombres?";
			link.l2.go = "repair";
		}
		link.l3 = "Rodgar, me gustaría dejar uno de mis barcos aquí.";
		if (CheckAttribute(npchar, "portman.info"))
			link.l3.go = "shipstock";
		else
			link.l3.go = "shipstock_info";
		if (CheckAttribute(npchar, "portman") && sti(npchar.portman > 0))
		{
			link.l4 = "Rodgar, me gustaría recuperar uno de mis barcos.";
			link.l4.go = "shipstockreturn";
		}
		if (!CheckAttribute(npchar, "storadge"))
		{
			link.l5 = "Mira, ¿hay algún edificio vacío que pueda usar como almacén?";
			link.l5.go = "storadge";
		}
		if (CheckAttribute(npchar, "storadge"))
		{
			link.l5 = "Rodgar, quiero ver un almacén.";
			link.l5.go = "storadge_3";
		}
		if (CheckAttribute(npchar, "crew"))
		{
			link.l6 = "Rodgar, quiero dejar a una parte de la tripulación en la isla.";
			link.l6.go = "crew";
		}
		if (CheckAttribute(npchar, "crew") && sti(npchar.crew.qty) > 0)
		{
			link.l7 = "Rodgar, quiero llevarme a mis marineros de vuelta al mar.";
			link.l7.go = "crew_3";
		} // <-- Исла Мона
		link.l99 = "Aún nada...";
		link.l99.go = "carpenter_exit";
		break;

	case "Crew":
		DialogExit();
		npchar.dialog.currentnode = "carpenter_17";
		LaunchHireCrew();
		break;

	case "carpenter_exit":
		DialogExit();
		npchar.dialog.currentnode = "carpenter_17";
		break;

	case "carpenter_18":
		dialog.text = "Felicidades, capitán. ¿Qué hacemos ahora? ¿Nos vamos?";
		link.l1 = "¿Has estado aquí por mucho tiempo?";
		link.l1.go = "carpenter_19";
		break;

	case "carpenter_19":
		dialog.text = "Por demasiado tiempo. Ha pasado un año desde que Wulfric me puso a cargo aquí.";
		link.l1 = "He decidido que esta base secreta es demasiado buena para ser desperdiciada. El pueblo es mío ahora. Puedo dejarte a ti y a tus hombres aquí si quieres. Ron, provisiones, medicinas - todo tuyo.";
		link.l1.go = "carpenter_20";
		break;

	case "carpenter_20":
		dialog.text = "Eso sería genial, capitán. Me acostumbré a la vida en esta playa, en esta isla.";
		link.l1 = "Espléndido. Por cierto, ¿cómo se llama la isla?";
		link.l1.go = "carpenter_21";
		break;

	case "carpenter_21":
		dialog.text = "Isla Mona.";
		link.l1 = "Isla Mona... Quizás algún día construiremos más casas y estructuras aquí... Pero más tarde. Por ahora, mantendrás el mismo papel aquí, pero bajo un nuevo capitán.";
		link.l1.go = "carpenter_22";
		break;

	case "carpenter_22":
		dialog.text = "Trato hecho. Solo cuídate, capitán, y no olvides abastecernos de provisiones.";
		link.l1 = "Claro que sí, Rodgar. Buena suerte, debo zarpar hacia La Vega.";
		link.l1.go = "carpenter_exit";
		npchar.portman = 0;
		AddDialogExitQuestFunction("Mtraxx_WolfreekComplete");
		break;
	//------------------------------------------------------------ Исла Мона ------------------------------------
	case "IslaMona":
		sTemp = "";
		if (GetCharacterIndex("Mirabella") != -1)
			sTemp = ", no dar cuenta de tu mujer";
		dialog.text = "Es difícil decirlo, capitán. El difunto Wulfric nunca dejó más de dos docenas de personas aquí. Ahora mismo, solo somos tres," + sTemp + "  No podemos hacer mucho.";
		link.l1 = "¿Quieres decir que si más gente viviera aquí, podrías convertir este lugar en un asentamiento completo?";
		link.l1.go = "IslaMona_1";
		break;

	case "IslaMona_1":
		dialog.text = "La isla es pequeña, así que no puedes construir una colonia en ella, ¡pero un asentamiento es totalmente posible! Puedes pescar, cazar aves y cabras, recoger frutas. Podemos mantenernos, pero no nos enriqueceremos con ello.\nPero hay algo que no entiendo del todo, capitán. ¿Para qué necesitas esto?";
		link.l1 = "Esta es mi casa y mi tierra, mi gente. ¿Qué me hace si no los cuido?";
		link.l1.go = "IslaMona_2_1";
		link.l2 = "Quiero invertir dinero en un negocio que valga la pena.";
		link.l2.go = "IslaMona_2_2";
		link.l3 = "Esta pequeña isla está justo en el corazón de esta región. Sería prudente convertirla en una base militar completa y secreta.";
		link.l3.go = "IslaMona_2_3";
		link.l4 = "Tengo miedo por ti, Rodgar, todos ustedes se han vuelto completamente salvajes en este punto.";
		link.l4.go = "IslaMona_2_4";
		break;

	case "IslaMona_2_1":
		dialog.text = "Eres un tipo extraño. Bueno, no importa. Al menos habrá algo que hacer...";
		link.l1 = "";
		link.l1.go = "IslaMona_3";
		AddCharacterExpToSkill(pchar, "Defence", 2000); // защита
		break;

	case "IslaMona_2_2":
		dialog.text = "Eres un tipo extraño. Bueno, no importa. Al menos habrá algo que hacer...";
		link.l1 = "";
		link.l1.go = "IslaMona_3";
		AddCharacterExpToSkill(pchar, "Commerce", 1500); // торговля
		break;

	case "IslaMona_2_3":
		dialog.text = "Eres un tipo extraño. Bueno, no importa. Al menos habrá algo que hacer...";
		link.l1 = "";
		link.l1.go = "IslaMona_3";
		AddComplexSelfExpToScill(250, 250, 250, 250); // оружие
		break;

	case "IslaMona_2_4":
		dialog.text = "Eres un tipo extraño. Bueno, no importa. Al menos habrá algo que hacer...";
		link.l1 = "";
		link.l1.go = "IslaMona_3";
		AddCharacterExpToSkill(pchar, "Leadership", 1000); // авторитет
		break;

	case "IslaMona_3":
		dialog.text = "En primer lugar, tendrás que encontrar individuos muy especiales. Aquellos que puedan ser persuadidos para mudarse a este desierto y vivir y trabajar aquí durante años, en completo aislamiento del mundo exterior. Ese es el tipo de personas especiales que tendrás que buscar. Con suerte, no solo uno. Después de todo, no puedes ordenar a tu tripulación que viva aquí, al menos no todavía. Los colonos no querrían dejar sus hogares establecidos y trabajos estables. Y nosotros mismos no necesitamos vagabundos y otros inadaptados aquí.\nAdemás, el asunto del secreto que rodea a esta isla siempre estará presente. Si le cuentas a alguien, inmediatamente existirá la amenaza de cazadores buscando investigar.";
		link.l1 = "Entiendo, ¿alguna sugerencia?";
		link.l1.go = "IslaMona_4";
		break;

	case "IslaMona_4":
		dialog.text = "No, Capitán. He estado aquí demasiado tiempo y he perdido completamente el contacto con la vida civilizada.";
		link.l1 = "¡Estupendo, eso es útil!";
		link.l1.go = "IslaMona_5";
		break;

	case "IslaMona_5":
		dialog.text = "Trabajo con madera, no con personas. ¡Y estoy muy contento por eso, ja-ja! Por cierto, además de las personas, también necesitarás traer aquí un conjunto de herramientas de forja y construcción de alta calidad. Solo se fabrican en la vieja Europa, así que te costarán un buen pellizco. Pregunta a los dueños de los astilleros, los más grandes.";
		link.l1 = "Todo está claro. Resumamos: si quiero convertir esta base en algo más grande, ¿necesito traer aquí más colonos y herramientas?";
		link.l1.go = "IslaMona_6";
		break;

	case "IslaMona_6":
		dialog.text = "¡Eso es correcto!";
		link.l1 = "Veré qué puedo hacer.";
		link.l1.go = "IslaMona_7";
		break;

	case "IslaMona_7":
		DialogExit();
		npchar.dialog.currentnode = "carpenter_17";
		AddQuestRecord("IslaMona", "1");
		pchar.questTemp.IslaMona = "tools";
		IslaMona_SelectShipyard();
		break;

	case "IslaMona_8":
		dialog.text = "¡Aye, Capitán! ¡Un equipo de primera, estamos listos para construir una colonia! ¿Fue caro?";
		link.l1 = "¡Me costó una fortuna, espero que haya valido la pena!";
		link.l1.go = "IslaMona_9_1";
		link.l2 = "Hace un par de años, habría dicho que era muy caro. Pero ahora... ni siquiera lo sé.";
		link.l2.go = "IslaMona_9_2";
		break;

	case "IslaMona_9_1":
		AddCharacterExpToSkill(pchar, "Commerce", 600);
		dialog.text = "¿No podías conformarte con lo que ya tenías, verdad? En cualquier caso, prepárate para que tus gastos solo crezcan. ¿Has resuelto el asunto con los colonos?";
		link.l1 = "No, Rodgar. Todavía no he averiguado dónde encontrarlos. Después de todo, no tengo los derechos soberanos para establecer asentamientos en estas aguas.";
		link.l1.go = "IslaMona_10";
		break;

	case "IslaMona_9_2":
		AddCharacterExpToSkill(pchar, "Leadership", 300);
		dialog.text = "¿No podías conformarte con lo que ya tenías, verdad? En cualquier caso, prepárate para que tus gastos solo aumenten. ¿Has resuelto el asunto con los colonos?";
		link.l1 = "No, Rodgar. Todavía no he averiguado dónde encontrarlos. Después de todo, no tengo los derechos soberanos para establecer asentamientos en estas aguas.";
		link.l1.go = "IslaMona_10";
		break;

	case "IslaMona_10":
		dialog.text = "En estas aguas, Capitán, el caos reina cada día. Escucha lo que dice la gente, puede que veas una oportunidad oculta. Me encargaré de las herramientas por ahora.";
		link.l1 = "Está bien, estaré atento a ese tipo de información.";
		link.l1.go = "IslaMona_11";
		break;

	case "IslaMona_11":
		DialogExit();
		npchar.dialog.currentnode = "carpenter_17";
		AddQuestRecord("IslaMona", "3");
		RemoveItems(pchar, "islamona_toolbox", 1);
		pchar.questTemp.IslaMona = "rumours";
		AddRumor("¡Dicen que algunos criminales han sido expulsados a una de las islas deshabitadas! ¡Parece que son monstruos tan feroces que ni siquiera el verdugo y los santos padres querrían tratar con ellos! ¡¿Pero por qué siempre nos traen a gente así?!", 1, "all", "none", 0, (2022 - STARTGAME_YEAR) * 365, "IslaMona_TerksRumour", "none");
		break;

	case "IslaMona_12":
		dialog.text = "¿Españoles? Debes estar bromeando, Capitán. Pensé que traerías vagos de Le Francois, no a estos...";
		link.l1 = "";
		link.l1.go = "IslaMona_13";
		break;

	case "IslaMona_13":
		DialogExit();
		LAi_SetActorType(npchar);
		sld = characterFromId("Himenes");
		sld.dialog.currentnode = "Himenes_18";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;

	case "IslaMona_14":
		dialog.text = "¿Eres de Europa? Jeje, no es difícil de adivinar. No te preocupes, te acostumbrarás.";
		link.l1 = "Jimenez, te quedarás en mi casa por un tiempo. Hay un sótano allí, mucho espacio. Rodgar, traje las herramientas, y también a los colonos. ¿Qué sigue?";
		link.l1.go = "IslaMona_15";
		break;

	case "IslaMona_15":
		DialogExit();
		sld = characterFromId("Himenes");
		sld.dialog.currentnode = "Himenes_20";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;

	case "IslaMona_16":
		dialog.text = "Nos vemos mañana, Capitán. Hablaremos en un día, una vez que estos... colonos se asienten con sus tesoros...";
		link.l1 = "Está bien, continuaremos mañana.";
		link.l1.go = "IslaMona_17";
		break;

	case "IslaMona_17":
		DialogExit();
		npchar.dialog.currentnode = "carpenter_17";
		LAi_SetWarriorType(npchar);
		IslaMona_HimenesWait();
		break;

	case "IslaMona_18":
		dialog.text = "Capitán, habla con el español. Ya está completamente enfrascado en su trabajo.";
		link.l1 = "Entendido, lo haré.";
		link.l1.go = "IslaMona_19";
		link.l2 = "¿Algo va mal?";
		link.l2.go = "IslaMona_18_1";
		break;

	case "IslaMona_18_1":
		AddCharacterExpToSkill(pchar, "Leadership", 100);
		dialog.text = "Capitán, he estado holgazaneando con los muchachos aquí durante unos años. Ahora, la bulliciosa actividad de los españoles me está poniendo de los nervios.";
		link.l1 = "¡No conflictos! Y te prohíbo a ti y a tus chicos siquiera mirar en dirección a sus mujeres. Al menos, por ahora... Si las cosas se calientan, toma un esquife y ve... a pescar por un par de días.";
		link.l1.go = "IslaMona_18_2";
		break;

	case "IslaMona_18_2":
		dialog.text = "¡Aye, aye, señor!";
		link.l1 = "Perfecto. Muy bien, iré a ver qué está tramando.";
		link.l1.go = "IslaMona_19";
		break;

	case "IslaMona_19":
		DialogExit();
		npchar.dialog.currentnode = "carpenter_17";
		IslaMona_SetHimenesNextDay();
		break;

	case "IslaMona_20":
		dialog.text = "Ya lo sé, Capitán. ¿El español quiere que exploremos la isla? ¿Saltar por las rocas con un mapa como un montón de idiotas?";
		link.l1 = "Eso es correcto, Rodgar.";
		link.l1.go = "IslaMona_21";
		break;

	case "IslaMona_21":
		dialog.text = "Seiscientos doblones y lo haré.";
		link.l1 = "¿Estás loco? ¿Te picó una araña o una serpiente venenosa? ¿Qué vas a hacer con un cofre de oro en una isla deshabitada? ¿Enterrarlo?";
		link.l1.go = "IslaMona_22";
		break;

	case "IslaMona_22":
		dialog.text = "Vamos, Capitán. Un día dejaremos este lugar, ¿y quién nos necesitará en el gran mundo sin monedas? Por supuesto, tenemos un pequeño alijo escondido, pero no es ni de cerca suficiente. Wulfric nunca saldó sus deudas conmigo y los muchachos por sus últimas aventuras.\nUna cosa es holgazanear en la playa durante meses y atender tu flota una vez cada seis meses. ¡Pero trabajar duro en tierra firme cada día, como un bucanero maldito, es una historia completamente diferente! Eso es un trabajo, y los trabajos pagan. Tú pagas a tu tripulación, ¿verdad, Capitán?";
		link.l1 = "Parece razonable. Te conseguiré los 600 doblones. Espero que no esperes el pago por adelantado, ¿verdad?";
		link.l1.go = "IslaMona_23";
		link.l2 = "Tengo otra propuesta. Trabajas en tierra, no rascando percebes de los barcos en el mar. Ahora mismo, necesitamos urgentemente ese tipo de trabajo.";
		link.l2.go = "IslaMona_25";
		break;

	case "IslaMona_23":
		ChangeCharacterComplexReputation(pchar, "nobility", 10);
		AddCharacterExpToSkill(pchar, "Leadership", 500);
		AddQuestRecord("IslaMona", "7");
		dialog.text = "Capitán, estoy listo para comenzar ahora mismo, pero mis hombres trabajarán mucho más duro cuando vean doblones en sus manos. Prometo que no dejaremos ni un solo trozo de tierra inexplorado en esta isla.";
		if (PCharDublonsTotal() >= 600)
		{
			link.l1 = "Muy bien. Aquí está tu oro. Solo no lo desperdicies en bebidas de inmediato.";
			link.l1.go = "IslaMona_24";
		}
		else
		{
			link.l1 = "Está bien, te traeré tus doblones.";
			link.l1.go = "IslaMona_24_1";
		}
		break;

	case "IslaMona_24_1":
		DialogExit();
		npchar.dialog.currentnode = "carpenter_17";
		pchar.questTemp.IslaMona = "dublon_wait";
		break;

	case "IslaMona_24":
		RemoveDublonsFromPCharTotal(600);
		Log_Info("Has entregado fuera 600 doblones");
		PlaySound("interface\important_item.wav");
		dialog.text = "¡Ja, ja! ¡Tienes razón, Capitán! Oh, y casi lo olvido. Ahora hay bastantes personas viviendo aquí, y necesitan algo para comer. ¿Has visto a esas damas? No están acostumbradas a sobrevivir y alimentarse de la tierra. No serán de mucha ayuda.";
		link.l1 = "Solo no me digas que tendré que encontrar más bucaneros para ayudarte.";
		link.l1.go = "IslaMona_26";
		break;

	case "IslaMona_25":
		ChangeCharacterComplexReputation(pchar, "nobility", -5);
		ChangeCharacterComplexReputation(pchar, "authority", 5);
		pchar.questTemp.IslaMona.Nodublon = "true"; // дублоны не заплатил
		AddQuestRecord("IslaMona", "8");
		dialog.text = "¡Sí, sí, Capitán! ¡Estamos listos para trabajar en tierra! Ah, y una cosa más, casi lo olvido. Ahora hay bastante gente viviendo aquí, y necesitan algo para comer. ¿Has visto a esas damas? No están acostumbradas a sobrevivir y alimentarse de la tierra. No serán de mucha ayuda.";
		link.l1 = "Solo no me digas que tendré que buscar también bucaneros para ayudarles.";
		link.l1.go = "IslaMona_26";
		break;

	case "IslaMona_26":
		dialog.text = "No, ¿por qué lo haríamos? Entrenaremos y prepararemos a los más capaces entre ellos para ganarse la vida. Pero hasta que llegue ese maravilloso momento, tendrás que proporcionarnos comida. Un par de miles de provisiones de barco serán suficientes. Y un quintal de medicinas para el futuro. Descarga todo esto de los barcos a nuestro almacén en la isla.";
		link.l1 = "Lo haré. ¿Cuánto tiempo necesitas para la misión de reconocimiento?";
		link.l1.go = "IslaMona_27";
		break;

	case "IslaMona_27":
		dialog.text = "Terminaremos en dos o tres días, ya hemos encontrado algunas cosas interesantes.";
		link.l1 = "¡Estupendo!";
		link.l1.go = "IslaMona_28";
		break;

	case "IslaMona_28":
		dialog.text = "Tan pronto como terminemos, dirígete directamente a ese español risueño. El loco necesita sacar conclusiones de nuestro trabajo.";
		link.l1 = "Veo que ya casi son amigos. Lo visitaré en tres días entonces. Bueno, ¡a trabajar! ¡Buena suerte para todos nosotros!";
		link.l1.go = "IslaMona_29";
		break;

	case "IslaMona_29":
		DialogExit();
		npchar.dialog.currentnode = "carpenter_17";
		npchar.quest.stalk = "true";
		AddQuestRecord("IslaMona", "9");
		pchar.questTemp.IslaMona = "storage";
		SetFunctionTimerCondition("IslaMona_StalkFin", 0, 0, 3, false);
		break;

	case "IslaMona_30":
		dialog.text = "¡Wow! Gracias, Capitán. Ahora tenemos tiempo para preparar a las damas para esta vida loca en la naturaleza.";
		link.l1 = "¡Solo ten cuidado de no convertirlos en piratas! Gracias, Rodgar";
		link.l1.go = "IslaMona_31";
		break;

	case "IslaMona_31":
		DialogExit();
		npchar.dialog.currentnode = "carpenter_17";
		pchar.questTemp.IslaMona.Food = "true";
		AddQuestRecord("IslaMona", "10");
		IslaMona_RemoveFood();
		break;

	case "IslaMona_32":
		dialog.text = "¡Capitán! Debo decir que he empezado a sentirme bastante incómodo viviendo aquí.";
		link.l1 = "¿Por qué es eso, Rodgar? ¿Extrañas el encanto de la pobreza y la ruina?";
		link.l1.go = "IslaMona_33";
		break;

	case "IslaMona_33":
		dialog.text = "Podrías decir eso. Ahora la civilización está llegando incluso aquí. Y personas como yo no tienen lugar en ella.";
		link.l1 = "Compra un jabot y un bastón. Encajarás perfectamente.";
		link.l1.go = "IslaMona_34";
		break;

	case "IslaMona_34":
		dialog.text = "Más bien, vayamos a ver a tu español y discutir los resultados del reconocimiento. Tengo una idea loca más...";
		link.l1 = "¡Acabo de hablar con él! Está bien, vamos, Rodgar.";
		link.l1.go = "IslaMona_37";
		link.l2 = "¿Cómo disfrutas trabajar con él?";
		link.l2.go = "IslaMona_35";
		break;

	case "IslaMona_35":
		dialog.text = "¡Gente muy educada y trabajadora! Y Jimenez es realmente un maestro. En los viejos tiempos, uno podría haber obtenido una buena cantidad de oro por personas así. Y sus chicas son hermosas, también...";
		link.l1 = "¡No quiero oír nada de eso, Rodgar! Vamos a hablar con ese amo nuestro";
		link.l1.go = "IslaMona_36_1";
		link.l2 = "Si no pueden manejar el trabajo, los venderemos. ¡Pero quedémonos con las chicas, ja-ja! Vamos a ver al maestro... ";
		link.l2.go = "IslaMona_36_2";
		break;

	case "IslaMona_36_1":
		ChangeCharacterComplexReputation(pchar, "nobility", 6);
		dialog.text = "¿En serio, Capitán? Solo estaba bromeando, vamos...";
		link.l1 = "";
		link.l1.go = "IslaMona_37";
		break;

	case "IslaMona_36_2":
		ChangeCharacterComplexReputation(pchar, "nobility", -6);
		dialog.text = "¡Sabía que me apoyarías, capitán! Vamos...";
		link.l1 = "";
		link.l1.go = "IslaMona_37";
		break;

	case "IslaMona_37":
		DialogExit();
		DoQuestReloadToLocation("IslaMona_TwoFloorHouse", "goto", "goto5", "IslaMona_HouseDialog");
		break;

	case "IslaMona_38":
		dialog.text = "Él no se ríe, cap...";
		link.l1 = "";
		link.l1.go = "IslaMona_39";
		break;

	case "IslaMona_39":
		DialogExit();
		sld = characterFromId("Himenes");
		sld.dialog.currentnode = "Himenes_48";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "IslaMona_40":
		dialog.text = "Eso también, capitán. Lo discutiremos más tarde...";
		link.l1 = "";
		link.l1.go = "IslaMona_41";
		break;

	case "IslaMona_41":
		DialogExit();
		sld = characterFromId("Himenes");
		sld.dialog.currentnode = "Himenes_52";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "IslaMona_42":
		dialog.text = "El caballero tiene un punto, Capitán. Ninguno de nosotros se romperá la espalda en la jungla. El negocio puede ser sucio, pero no sacarás nada más de este lugar que un nido de piratas de otra manera.";
		link.l1 = "";
		link.l1.go = "IslaMona_43";
		break;

	case "IslaMona_43":
		DialogExit();
		sld = characterFromId("Himenes");
		sld.dialog.currentnode = "Himenes_58";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "IslaMona_44":
		dialog.text = "Capitán, cuando construya la fábrica, los esclavos necesitarán protección. Mis chicos se encargarán de eso. Uno de ellos incluso dispara como Thor con un rayo. Nada motiva más al trabajo que un visor de caza. Ya tenemos un arma; ahora necesitamos una segunda. Cualquier mosquete servirá.";
		link.l1 = "";
		link.l1.go = "IslaMona_45";
		break;

	case "IslaMona_45":
		DialogExit();
		sld = characterFromId("Himenes");
		sld.dialog.currentnode = "Himenes_60";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "IslaMona_46":
		dialog.text = "Y mis muchachos necesitarán la misma cantidad de oro y otra docena de botellas de buen ron.";
		link.l1 = "¿Cuánta madera podrás proporcionar en cada lote? ¿Y por qué necesitas oro?";
		link.l1.go = "IslaMona_47";
		break;

	case "IslaMona_47":
		DialogExit();
		sld = characterFromId("Himenes");
		sld.dialog.currentnode = "Himenes_62";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "IslaMona_48":
		dialog.text = "Bueno, en primer lugar, la vida sin ocio no tiene sentido, y pronto incluso los piadosos, jeje, católicos empezarán a trepar por las paredes. Y en segundo lugar, si hay una taberna en la isla, podrás dejar parte de la tripulación aquí en espera. Verás, convencer a la gente de vivir como salvajes gratis en chozas en la playa durante todo un año es bastante difícil. Pero si hay un asentamiento con una taberna, comida caliente, música y entretenimiento cerca... ¿Qué más necesita un marinero en tierra?";
		link.l1 = "¿Rameras?";
		link.l1.go = "IslaMona_49";
		link.l2 = "¿Bebidas?";
		link.l2.go = "IslaMona_49";
		break;

	case "IslaMona_49":
		dialog.text = "Tienes razón, pero resolvamos los problemas uno a la vez. Primero, reconstruiremos tu casa...";
		link.l1 = "...";
		link.l1.go = "IslaMona_50";
		break;

	case "IslaMona_50":
		DialogExit();
		sld = characterFromId("Himenes");
		sld.dialog.currentnode = "Himenes_65";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "IslaMona_51":
		dialog.text = "No lo pensó ni por un momento, capitán.";
		link.l1 = "Gracias, Rodgar. Entiendo que ahora podré atender más barcos en esta pequeña bahía, ¿verdad?";
		link.l1.go = "IslaMona_52";
		break;

	case "IslaMona_52":
		DialogExit();
		sld = characterFromId("Himenes");
		sld.dialog.currentnode = "Himenes_harbour_4";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "IslaMona_53":
		dialog.text = "¡Saludos, Capitán! ¿Ha venido a discutir el trabajo?";
		link.l1 = "No, en absoluto. Solo extrañaba tu fisonomía del norte.";
		link.l1.go = "IslaMona_54";
		break;

	case "IslaMona_54":
		dialog.text = "¿Vamos a caminar? Te mostraré tu fábrica.";
		link.l1 = "Lidera el camino.";
		link.l1.go = "IslaMona_55";
		break;

	case "IslaMona_55":
		DialogExit();
		IslaMona_PlantationGo();
		break;

	case "IslaMona_56":
		dialog.text = "¡H-hip! ¡Capitán, estamos celebrando!";
		link.l1 = "¡Rodgar! ¡Rodrigo! ¡Maldita sea!";
		link.l1.go = "IslaMona_57";
		break;

	case "IslaMona_57":
		dialog.text = "¿Qué pasa, c-c-capitán? ¿No le gusta el color de las paredes?";
		link.l1 = "¡Apenas ahora me doy cuenta de que ustedes dos comparten el mismo nombre! ¡Ja-ja-ja! ¡Un español y un pirata, con el mismo nombre, construyeron una taberna en una isla desierta y beben juntos como si los dioses indios fueran a devorar a todos y acabar con el mundo al amanecer! ¡Ja-ja! ¡Estoy con ustedes!";
		link.l1.go = "IslaMona_58";
		break;

	case "IslaMona_58":
		dialog.text = "¡Ja-ja-ja! ¡Tan cierto! ¡Salud!";
		link.l1 = "¡Salud!";
		link.l1.go = "IslaMona_59";
		break;

	case "IslaMona_59":
		DialogExit();
		npchar.dialog.currentnode = "IslaMona_60";
		IslaMona_ReloadTavern();
		break;

	case "IslaMona_60":
		dialog.text = "¿Quieres un trago, capitán?";
		link.l1 = "¿Te estás convirtiendo en tabernero, Rodgar?";
		link.l1.go = "IslaMona_61";
		break;

	case "IslaMona_61":
		dialog.text = "¡Temporalmente! A los españoles especialmente les gusta tener un pirata atendiendo el bar - es el verdadero exotismo y aventura para ellos. Pero en general, es agradable aquí. Si decides dejar a alguno de tu tripulación en reserva en este asentamiento, solo házmelo saber - lo arreglaré.";
		link.l1 = "¿Dónde vivirán entonces?";
		link.l1.go = "IslaMona_62";
		break;

	case "IslaMona_62":
		dialog.text = "Simple - construiremos algunas chozas en la playa. De esa manera, estarán corriendo de la taberna a la orilla. Solo un recordatorio, esta isla no acomodará a más de trescientas personas, así que tenlo en cuenta para el futuro. A veces te pediremos que traigas ron y vino, así que sería genial si tú, Capitán, pudieras almacenar las mercancías en el almacén de antemano.";
		link.l1 = "Lo recordaré. Pues bien, compadre. Entretiene a los españoles y tómate un descanso. Solo, por favor, no bebas hasta que todo el pueblo arda, ¡no podría soportar ver eso!";
		link.l1.go = "IslaMona_63";
		break;

	case "IslaMona_63":
		DialogExit();
		npchar.dialog.currentnode = "carpenter_17";
		// LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload1", false);
		// LocatorReloadEnterDisable("IslaMona_TwoFloorHouse", "reload3", false);
		npchar.crew = "true"; // можно оставлять матросов
		npchar.crew.qty = 0;
		pchar.questTemp.IslaMona.Tavern = "done"; // флаг - таверна построена и сдана
		// belamour обнулим матросов-->
		ref rTown = GetColonyByIndex(FindColony(loadedLocation.fastreload));
		rTown.Ship.crew.quantity = 0;
		rTown.Ship.crew.morale = 0;
		rTown.Ship.Crew.Exp.Sailors = 0;
		rTown.Ship.Crew.Exp.Cannoners = 0;
		rTown.Ship.Crew.Exp.Soldiers = 0;
		ChangeCrewExp(rTown, "Sailors", 0); // приведение к 1-100
		ChangeCrewExp(rTown, "Cannoners", 0);
		ChangeCrewExp(rTown, "Soldiers", 0);

		break;

	case "IslaMona_64":
		dialog.text = "¡Capitán! ¡Maldita sea, me alegra verte! ¡Gracias a Freyja, has llegado justo a tiempo!";
		link.l1 = "¡Ay, nos hemos metido en otro buen lío. Hola, Rodrigo!";
		link.l1.go = "IslaMona_65";
		break;

	case "IslaMona_65":
		DialogExit();
		sld = characterFromId("Himenes");
		sld.dialog.currentnode = "Himenes_church_13";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "IslaMona_66":
		dialog.text = "Sin bajas. Los españoles sobrevivientes llegaron a nosotros primero, informaron de la posibilidad de encontrarnos con más invitados, y logramos traer casi todas las provisiones y equipos de la zona al asentamiento. La situación con los esclavos no resultó muy bien, por supuesto.";
		link.l1 = "";
		link.l1.go = "IslaMona_67";
		break;

	case "IslaMona_67":
		DialogExit();
		sld = characterFromId("Himenes");
		sld.dialog.currentnode = "Himenes_church_16";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "IslaMona_68":
		dialog.text = "¿Y si nos arrastran a un asalto abierto?";
		link.l1 = "Entonces trabajamos sin armas. Como en un desfile, marchamos juntos hacia las puertas y luego simplemente los golpeamos por detrás. Tú mantienes las puertas y brindas apoyo. Eso es todo, ¡buena suerte para nosotros!";
		link.l1.go = "IslaMona_69";
		break;

	case "IslaMona_69":
		DialogExit();
		AddQuestRecord("IslaMona", "21");
		pchar.quest.islamona_def_jungle1.win_condition.l1 = "locator";
		pchar.quest.islamona_def_jungle1.win_condition.l1.location = "IslaMona_jungle_01";
		pchar.quest.islamona_def_jungle1.win_condition.l1.locator_group = "encdetector";
		pchar.quest.islamona_def_jungle1.win_condition.l1.locator = "enc04";
		pchar.quest.islamona_def_jungle1.function = "IslaMona_DefSoldiersInJungle";		// встреча с французами
		LAi_LocationFightDisable(&Locations[FindLocation("IslaMona_jungle_01")], true); // запретить драться
		break;

	case "IslaMona_70":
		dialog.text = "¡Hurra, Capitán!";
		link.l1 = "¡De acuerdo! ¡Eso fue un estruendo tan grande que yo mismo sentí ganas de tirarme al suelo! Chicos, ¿qué cargaron ahí?";
		link.l1.go = "IslaMona_71";
		break;

	case "IslaMona_71":
		dialog.text = "¡Carga doble, Capitán. Para que un solo disparo los desanime a seguir peleando!";
		link.l1 = "¿No te preocupaba que el cañón explotara por un manejo tan delicado?";
		link.l1.go = "IslaMona_72";
		break;

	case "IslaMona_72":
		dialog.text = "Tengo un talismán especial que quedó de Wulfric. Un recuerdo de nuestra querida Dinamarca. ¿Vamos todos a la taberna, Capitán? Todos estamos cansados después de hoy.";
		link.l1 = "Sí, eso sería estupendo. Juguemos a las cartas - apostaremos en tu talismán milagroso.";
		link.l1.go = "IslaMona_73";
		break;

	case "IslaMona_73":
		dialog.text = "¡Ja, ja, después de tan divina actuación hoy, Capitán, podría incluso considerar esa opción!";
		link.l1 = "";
		link.l1.go = "IslaMona_74";
		break;

	case "IslaMona_74":
		DialogExit();
		sld = characterFromId("IM_fraofficer");
		sld.dialog.currentnode = "FraOfficer_18";
		LAi_CharacterEnableDialog(sld);
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "IslaMona_75":
		dialog.text = "Capitán, ¿oíste eso? Todavía tengo un zumbido en mis oídos. ¿De quién es esa voz lastimera?";
		link.l1 = "Ese, Rodgar, es un asunto candente. Llévalo a la fábrica, ponlo en una cadena y espera más instrucciones.";
		link.l1.go = "IslaMona_76";
		break;

	case "IslaMona_76":
		dialog.text = "¡Sí, sí, capitán!";
		link.l1 = "";
		link.l1.go = "IslaMona_77";
		break;

	case "IslaMona_77":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "", 5.0);
		sld = characterFromId("IM_fraofficer");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
		for (i = 1; i <= 5; i++)
		{
			sld = characterFromId("IM_soldier_" + i);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
		}
		for (i = 4; i <= 7; i++)
		{
			sld = characterFromId("IM_fra_sailor_" + i);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1_back", "none", "", "", "", 5.0);
		}
		sld = characterFromId("Himenes");
		sld.dialog.currentnode = "Himenes_church_20";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

	case "IslaMona_78":
		dialog.text = "Capitán, ¿ha venido a resolver el asunto con el prisionero? Estoy cansado de estar aquí de guardia.";
		link.l1 = "Tendremos que matarlo. El riesgo es demasiado grande, así que no tenemos opción. De lo contrario, sería mejor que no mostrara mi cara en las colonias francesas.";
		link.l1.go = "IslaMona_79";
		link.l2 = "No puedo dejarlo ir, de lo contrario es mejor que no muestre mi cara en las colonias francesas. Ponlo en grilletes y deja que trabaje en la fábrica. Es mejor que matarlo.";
		link.l2.go = "IslaMona_80";
		break;

	case "IslaMona_79":
		dialog.text = "¡Entendido! Hagámoslo rápidamente. Adelante, Capitán. Nos vemos mañana.";
		link.l1 = "";
		link.l1.go = "IslaMona_81";
		break;

	case "IslaMona_80":
		dialog.text = "Vaya. Eres todo un genio malvado. No quisiera ser tu enemigo. Pues bien, primero tendremos que llevar a cabo algún trabajo explicativo con él. Adelante, Capitán. Nos vemos mañana.";
		link.l1 = "";
		link.l1.go = "IslaMona_81";
		pchar.questTemp.IslaMona.Fraprisoner = "true";
		break;

	case "IslaMona_81":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload2", "none", "", "", "IslaMona_DefFraPrisonerFin", 10.0); /// идёт внутрь фактории - УСТАНОВИТЬ ЛОКАТОР
		break;

	case "IslaMona_82":
		dialog.text = "¡Qué matanza! Lástima que no pudimos disparar desde el cañón, pero se lanzaron directamente a tu emboscada, ¡fue un placer verlo!";
		link.l1 = "Sí, derramamos mucha sangre en esta tierra. Pero al parecer, no hay otra manera de construir un hogar en este mundo.";
		link.l1.go = "IslaMona_83";
		break;

	case "IslaMona_83":
		dialog.text = "No le des demasiadas vueltas, Capitán. El destino mismo los trajo a Isla Mona. ¡Y déjame decirte, el destino puede ser una perra!";
		link.l1 = "¿El destino, o la isla?";
		link.l1.go = "IslaMona_84";
		break;

	case "IslaMona_84":
		dialog.text = "Ambos desempeñaron su papel.";
		link.l1 = "¡Jaja! ¡Y ambas son hermosas! Muy bien, valiente vikingo. Recolecta los trofeos y retira estos cuerpos. Entiérralos con dignidad. Son de los nuestros, después de todo...";
		link.l1.go = "IslaMona_85";
		break;

	case "IslaMona_85":
		DialogExit();
		sld = characterFromId("Himenes");
		sld.dialog.currentnode = "Himenes_church_20a";
		LAi_SetActorType(sld);
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;

	case "IslaMona_86":
		dialog.text = "Sí, Capitán. ¡Así es! Rodrigo lo dijo tan hermosamente que me sacó una lágrima. ¡Está claro por qué los santos padres quieren poner su trasero en una pica!";
		link.l1 = "";
		link.l1.go = "IslaMona_87";
		locCameraFromToPos(1.36, 1.32, 0.31, true, 3.44, 0.20, -0.50);
		break;

	case "IslaMona_87":
		DialogExit();
		if (GetCharacterIndex("Mirabella") != -1)
		{
			sld = characterFromId("Mirabella");
			sld.dialog.currentnode = "mirabelle_46";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		}
		else
		{
			if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
			{
				sld = characterFromId("Mary");
				sld.dialog.currentnode = "IslaMona_2";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
			else
			{
				if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
				{
					sld = characterFromId("Helena");
					sld.dialog.currentnode = "IslaMona_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
				else
				{
					sld = characterFromId("Himenes_companion_1");
					sld.dialog.currentnode = "island_man_2";
					LAi_SetActorType(sld);
					LAi_ActorDialogDelay(sld, pchar, "", 0.0);
				}
			}
		}
		break;

	case "IslaMona_88":
		dialog.text = "Rodrigo, y aquí me topé directamente con nuestro prelado en el boudoir... ¡Y déjame decirte, es el mejor establecimiento en Santiago!";
		link.l1 = "El mejor lugar si te gustan los prelados también.";
		link.l1.go = "IslaMona_89";
	break

		case "IslaMona_89":
		DialogExit();
		sld = characterFromId("Himenes");
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "IslaMona_90":
		dialog.text = "Sí, convertí a ese canalla y hereje Rodrigo en un auténtico pirata, de verdad.";
		link.l1 = "Por cierto, ilumíname, Rodgar. ¿Por qué hay tan pocos piratas españoles?";
		link.l1.go = "IslaMona_91";
		break;

	case "IslaMona_91":
		dialog.text = "¿Por qué tan pocos? Ah, ¿te refieres a los capitanes piratas? Bueno, hay muchos de ellos, solo que la mayoría opera bajo la Casa de Contratación en Sevilla. Es como la inteligencia militar, pero por alguna razón lo llaman una casa de comercio...";
		link.l1 = "";
		link.l1.go = "IslaMona_92";
		break;

	case "IslaMona_92":
		DialogExit();
		sld = characterFromId("Himenes");
		sld.dialog.currentnode = "Himenes_77";
		LAi_ActorSetSitMode(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "IslaMona_93":
		dialog.text = "Sí, ¿por qué no enviarles un mensaje e invitarlos a venir? Bueno, todos tienen patentes, y también son idealistas. Por lo general, no roban a los suyos, solo si la incursión no fue exitosa, ¡ja, ja! Solo pasan por Puerto Príncipe y constantemente chocan con Pastor.\nRecientemente, uno se destacó... Diego de Montoya. Justo cuando fui en campaña con Wulfric, escuché mucho sobre sus aventuras. Tú, capitán, tienes algo en común con él. Y al mismo tiempo, eres muy diferente... En fin, ¿de qué estoy hablando? Tomemos otra ronda y juguemos unas cartas.";
		link.l1 = "No tienes dinero. No estarás apostando doblones, ¿verdad?";
		link.l1.go = "IslaMona_94";
		break;

	case "IslaMona_94":
		dialog.text = "Apostamos un peso cada uno. ¿Jugamos hasta veinte? Hymenes, ¿te animas?";
		link.l1 = "";
		link.l1.go = "IslaMona_95";
		break;

	case "IslaMona_95":
		DialogExit();
		sld = characterFromId("Himenes");
		sld.dialog.currentnode = "Himenes_79";
		LAi_ActorSetSitMode(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "IslaMona_96":
		dialog.text = "¿Jugamos, capitán?";
		if (sti(pchar.money) >= 20)
		{
			link.l1 = "¡Empiézalo!";
			link.l1.go = "IslaMona_97";
		}
		link.l2 = "Yo también paso, Rodgar. Pesos o no, la gente pierde barcos así. Con islas. Diviértete aquí, y yo seguiré explorando un poco más.";
		link.l2.go = "IslaMona_98";
		break;

	case "IslaMona_97": // игра в карты
		DialogExit();
		pchar.questTemp.GoldenGirl.Game.IslaMona = "true"; // атрибут квестовой игры
		npchar.money = 20;
		pchar.questTemp.IslaMona.Money = sti(pchar.money);
		pchar.money = 20;
		// вызов интерфейса игры
		pchar.GenQuest.Cards.npcharIdx = npchar.index;
		pchar.GenQuest.Cards.iRate = 1; // ставка
		LaunchCardsGame();
		break;

	case "IslaMona_98": // выход из-за стола
		DialogExit();
		IslaMona_ChurchTavernStandUp();
		break;

	case "IslaMona_99":
		if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Win"))
		{
			dialog.text = "¡Paso! ¡Bueno, bueno, ya no juego contigo! ¡Estoy seguro de que hiciste trampa, capitán! ¡Y dejar a un tramposo así no estaría bien!";
			link.l1 = "Te escucho, Rodgar.";
		}
		else
		{
			if (CheckAttribute(pchar, "questTemp.GoldenGirl.Game.Fail"))
			{
				dialog.text = "¡Gané, capitán! Pero no puedo dejar que te vayas con las manos vacías, ¡jaja!";
				link.l1 = "Está bien, bribón. Será una lección para mí...";
			}
			else
			{
				dialog.text = "¡He ganado, capitán! Pero no puedo dejar que te vayas con las manos vacías así, ¡jajaja!";
				link.l1 = "Está bien, canalla. Será una lección para mí...";
			}
		}
		link.l1.go = "IslaMona_100";
		break;

	case "IslaMona_100":
		dialog.text = "¡Ah, vamos! Nos has dado a mí y a mi tripulación una oportunidad de una vida real lejos de cuartos estrechos, agua rancia y el riesgo de recibir una astilla en... el cráneo. Aquí. Este amuleto fue traído por Wulfric desde la lejana Dinamarca y luego me lo entregó para que yo... je, no tuviera que adentrarme demasiado en su sótano. Ya no lo necesito, pero tú - oh, te será bastante útil.";
		link.l1 = "Gracias, Rodgar. En verdad, un objeto útil. Y hermoso también...";
		link.l1.go = "IslaMona_101_1";
		link.l2 = "Manténlo, Rodgar. Sin ti, este lugar no existiría. Que sea un recordatorio de tu tierra natal.";
		link.l2.go = "IslaMona_101_2";
		break;

	case "IslaMona_101_1":
		GiveItem2Character(pchar, "talisman3");
		Log_Info("Has recibido el 'Martillo de Thor'");
		PlaySound("interface\important_item.wav");
		dialog.text = "Me alegra que lo hayas disfrutado, Capitán. ¿Otra ronda?";
		link.l1 = "Vosotros relajaos aquí, y yo daré una vuelta por los alrededores.";
		link.l1.go = "IslaMona_102";
		break;

	case "IslaMona_101_2":
		ChangeCharacterComplexReputation(pchar, "nobility", 10);
		AddCharacterExpToSkill(pchar, "Fortune", 2000);
		dialog.text = "¡Como desees! ¡Entonces brindaré por la dama fortuna, jaja! ¿Otra ronda?";
		link.l1 = "Vosotros relajaos aquí, y yo echaré un vistazo más.";
		link.l1.go = "IslaMona_102";
		break;

	case "IslaMona_102":
		DialogExit();
		DeleteAttribute(pchar, "questTemp.GoldenGirl.Game");
		DeleteAttribute(pchar, "GenQuest.Cards");
		pchar.money = sti(pchar.money) + sti(pchar.questTemp.IslaMona.Money);
		DeleteAttribute(pchar, "questTemp.IslaMona.Money");
		IslaMona_ChurchTavernStandUp();
		break;

	case "IslaMona_103":
		dialog.text = "Bueno, Capitán. Has arreglado las cosas con el español, hemos tenido nuestra celebración y el dolor de cabeza ha disminuido un poco. ¡La vida es buena!";
		link.l1 = "¿Qué estás tramando, Rodgar?";
		link.l1.go = "IslaMona_104";
		break;

	case "IslaMona_104":
		sTemp = "";
		if (CheckAttribute(pchar, "questTemp.IslaMona.MiraRodgar"))
			sTemp = "Me llevaré bien con la mujer. ";
		dialog.text = "Estaré cazando como de costumbre, vigilando mi... nuestra taberna, pateando a los esclavos en la fábrica. Perfecto retiro.";
		link.l1 = "Eres solo cinco años mayor que yo, Rodgar. ¿Y tú, Rodrigo? ¿Cómo te va?";
		link.l1.go = "IslaMona_105";
		break;

	case "IslaMona_105":
		DialogExit();
		sld = characterFromId("Himenes");
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;
		// <-- Исла Мона

	case "repair":
		if (CheckSelfRepairConditions())
		{
			dialog.text = "¡Por supuesto, capitán! Todo lo que necesitamos son tablones y lonas de vela. Ve a tu lugar de desembarco y ordena a la tripulación que prepare los materiales.";
			link.l1 = "En camino. Hazlo rápido.";
			link.l1.go = "repair_1";
		}
		else
		{
			dialog.text = "Claro, capitán, pero como lo veo yo, su barco no necesita reparaciones ahora.";
			link.l1 = "Solo pregunté...";
			link.l1.go = "carpenter_exit";
		}
		break;

	case "repair_1":
		DialogExit();
		npchar.dialog.currentnode = "carpenter_17";
		chrDisableReloadToLocation = true;
		DoQuestReloadToLocation(Pchar.location.from_sea, "reload", "sea", "Mtraxx_WolfreekRepairShore");
		break;

	case "shipstock_info":
		npchar.portman.info = "true";
		dialog.text = "Es posible, capitán. Pero hay algunas limitaciones: solo hay dos lugares en esta isla adecuados para esto. Además, no puedes dejar aquí a nadie más que un solo oficial por cada barco. Simplemente no tenemos suficientes recursos para mantener a las tripulaciones aquí. Aún. Finalmente, no hay espacio para barcos de primera categoría.";
		link.l1 = "Entendido. Estoy listo para dejar un barco aquí.";
		link.l1.go = "shipstock";
		link.l2 = "Muy bien, la prepararé.";
		link.l2.go = "carpenter_exit";
		break;

	case "shipstock":
		if (CheckAttribute(pchar, "questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done")
		{
			if (sti(npchar.portman) == 3)
			{
				dialog.text = "Capitán, ya hay tres de sus barcos anclados en el muelle. No hay más espacio disponible.";
				link.l1 = "Tienes razón, lo olvidé.";
				link.l1.go = "carpenter_exit";
				break;
			}
			else
			{
				if (CheckAttribute(npchar, "FstClassInHarbour") && sti(npchar.portman) > 0)
				{
					dialog.text = "Capitán, ya hay un barco de primera categoría anclado en el muelle. No hay más espacio disponible.";
					link.l1 = "Tienes razón, lo olvidé.";
					link.l1.go = "carpenter_exit";
					break;
				}
			}
		}
		else
		{
			if (sti(npchar.portman) == 2)
			{
				dialog.text = "Capitán, dos de tus barcos ya están anclados en el muelle. No hay más espacio disponible.";
				link.l1 = "Tienes razón, lo olvidé.";
				link.l1.go = "carpenter_exit";
				break;
			}
		}
		if (GetCompanionQuantity(pchar) < 2)
		{
			dialog.text = "Capitán, solo tienes un barco.";
			link.l1 = "Mm... Debería beber menos...";
			link.l1.go = "carpenter_exit";
			break;
		}
		dialog.text = "¿Qué barco quieres dejar aquí?";
		for (i = 1; i < COMPANION_MAX; i++)
		{
			int cn = GetCompanionIndex(PChar, i);
			if (cn > 0)
			{
				ref chref = GetCharacter(cn);
				if (!GetRemovable(chref))
					continue;

				attrL = "l" + i;
				Link.(attrL) = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
				Link.(attrL).go = "ShipStockMan_" + i;
			}
		}
		Link.l9 = "Espera, he cambiado de opinión.";
		Link.l9.go = "carpenter_exit";
		break;

	case "ShipStockMan_1":
		NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 1);
		dialog.text = "Vamos a ver...";
		Link.l1 = "Muy bien.";
		Link.l1.go = "ShipStock_2";
		Link.l2 = "Espera, he cambiado de opinión.";
		Link.l2.go = "carpenter_exit";
		break;

	case "ShipStockMan_2":
		NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 2);
		dialog.text = "Veamos...";
		Link.l1 = "Muy bien.";
		Link.l1.go = "ShipStock_2";
		Link.l2 = "Espera, he cambiado de opinión.";
		Link.l2.go = "carpenter_exit";
		break;

	case "ShipStockMan_3":
		NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 3);
		dialog.text = "Veamos...";
		Link.l1 = "Muy bien.";
		Link.l1.go = "ShipStock_2";
		Link.l2 = "Espera, he cambiado de opinión.";
		Link.l2.go = "carpenter_exit";
		break;

	case "ShipStockMan_4":
		NPChar.ShipToStoreIdx = GetCompanionIndex(PChar, 4);
		dialog.text = "Vamos a ver...";
		Link.l1 = "Muy bueno.";
		Link.l1.go = "ShipStock_2";
		Link.l2 = "Espera, he cambiado de opinión.";
		Link.l2.go = "carpenter_exit";
		break;

	case "ShipStock_2":
		chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
		if (CheckAttribute(pchar, "questTemp.IslaMona.Harbour") && pchar.questTemp.IslaMona.Harbour == "done")
		{
			if (sti(RealShips[sti(chref.Ship.Type)].Class) < 2 && sti(npchar.portman) > 0)
			{
				dialog.text = "Capitán, he mencionado antes que nuestro fondeadero solo puede acomodar un barco de primera clase. Es demasiado grande para el espacio disponible.";
				Link.l1 = "Tienes razón, lo olvidé.";
				Link.l1.go = "carpenter_exit";
				break;
			}
		}
		else
		{
			if (sti(RealShips[sti(chref.Ship.Type)].Class) < 2)
			{
				dialog.text = "Capitán, los navíos de primera clase son demasiado grandes para nuestras costas. Ya te lo he dicho.";
				Link.l1 = "Tienes razón, lo olvidé.";
				Link.l1.go = "carpenter_exit";
				break;
			}
		}
		if (sti(chref.Ship.Crew.Quantity) > 0)
		{
			dialog.text = "Capitán, lleva a toda su tripulación a tu buque insignia excepto a un oficial.";
			Link.l1 = "¡Ah, cierto! ¡Haré eso!";
			Link.l1.go = "carpenter_exit";
			break;
		}
		dialog.Text = "Entonces, hemos de mantener aquí un" + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName + "Acc") + " llamado '" + chref.Ship.Name + "'. ¿Verdad?";
		Link.l1 = "Correcto.";
		Link.l1.go = "ShipStock_3";
		Link.l2 = "Espera, he cambiado de opinión.";
		Link.l2.go = "carpenter_exit";
		break;

	case "ShipStock_3":
		chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
		chref.ShipInStockMan = NPChar.id;
		chref.ShipInStockMan.MoneyForShip = 0;
		chref.ShipInStockMan.AltDate = GetQuestBookDataDigit();
		SaveCurrentNpcQuestDateParam(chref, "ShipInStockMan.Date");
		RemoveCharacterCompanion(pchar, chref);
		chref.location = "";
		chref.location.group = "";
		chref.location.locator = "";
		if (sti(RealShips[sti(chref.Ship.Type)].Class) < 2)
		{
			npchar.FstClassInHarbour = 1;
		}
		npchar.portman = sti(npchar.portman) + 1;
		pchar.ShipInStock = sti(pchar.ShipInStock) + 1;
		dialog.text = "Muy bien, la llevaremos a un puerto seguro.";
		Link.l1 = "¡Excelente!";
		Link.l1.go = "carpenter_exit";
		break;

	case "shipstockreturn":
		if (GetCompanionQuantity(pchar) < COMPANION_MAX)
		{
			dialog.text = "¿Qué barco vas a tomar, capitán?";
			cn = 1;
			for (i = 1; i < MAX_CHARACTERS; i++)
			{
				makeref(chref, Characters[i]);
				if (CheckAttribute(chref, "ShipInStockMan"))
				{
					if (chref.ShipInStockMan == NPChar.id)
					{
						attrL = "l" + cn;
						Link.(attrL) = XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
						Link.(attrL).go = "ShipStockManBack_" + i;
						cn++;
					}
				}
			}
			link.l9 = "Espera, he cambiado de opinión.";
			link.l9.go = "carpenter_exit";
		}
		else
		{
			dialog.text = "Capitán, no tienes espacio en tu escuadrón para un barco más.";
			link.l1 = "Mm. Parece que tienes razón.";
			link.l1.go = "carpenter_exit";
		}
		break;

	case "ShipStockManBack":
		chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
		dialog.Text = "¿La estás llevando?";
		link.l1 = "Sí.";
		link.l1.go = "ShipStockManBack2";
		link.l2 = "Espera, he cambiado de opinión.";
		link.l2.go = "carpenter_exit";
		break;

	case "ShipStockManBack2":
		DialogExit();
		npchar.dialog.currentnode = "carpenter_17";
		if (CheckAttribute(npchar, "FstClassInHarbour"))
			DeleteAttribute(npchar, "FstClassInHarbour");
		chref = GetCharacter(sti(NPChar.ShipToStoreIdx));
		DeleteAttribute(chref, "ShipInStockMan");
		SetCompanionIndex(pchar, -1, sti(NPChar.ShipToStoreIdx));
		npchar.portman = sti(npchar.portman) - 1;
		pchar.ShipInStock = sti(pchar.ShipInStock) - 1;
		break;

	case "storadge":
		dialog.text = "Aquí? No. Pero Wulfric había construido un gran granero no lejos de aquí. Un edificio sólido, bien cubierto con hojas de palma y lona alquitranada. Tiene un candado y una habitación para una carga suficiente para llenar una docena de barcos mercantes\nAhora está vacío, pero tengo la llave si quieres examinarlo. ¿Vamos?";
		link.l1 = "¡Claro! Por cierto: ¿qué hay de las ratas en esta isla? ¿Echarán a perder mis mercancías en el granero?";
		link.l1.go = "storadge_1";
		break;

	case "storadge_1":
		dialog.text = "Lobo lo tenía cubierto también: trajo dos gatos aquí desde el continente. Sin embargo, se olvidó de los machos, así que estas locas perras peludas hacen sonidos horribles cada vez que llega su temporada. Pero cazan ratones y ratas bastante bien. No te preocupes por eso, capitán. Tus mercancías estarán a salvo de plagas y vientos.";
		link.l1 = "¡Estupendo! Haré buen uso de ello. Guarda tu llave y muéstrame este almacén.";
		link.l1.go = "storadge_2";
		break;

	case "storadge_2":
		DialogExit();
		npchar.dialog.currentnode = "carpenter_17";
		npchar.city = "islamona";
		npchar.Storage.Activate = true;
		SaveCurrentNpcQuestDateParam(npchar, "Storage.Date");
		npchar.MoneyForStorage = 0;
		npchar.storadge = true;
		LaunchStorage(29);
		break;

	case "storadge_3":
		dialog.text = "Sígueme, capitán.";
		link.l1 = "...";
		link.l1.go = "storadge_4";
		break;

	case "storadge_4":
		DialogExit();
		npchar.dialog.currentnode = "carpenter_17";
		LaunchStorage(29);
		break;

	// Мирабель
	case "mirabelle":
		PlaySound("Voice\Spanish\Girl_Q.wav");
		dialog.text = "Ah...";
		link.l1 = "Bueno ahora... Una chica... ¿Qué haces aquí?";
		link.l1.go = "mirabelle_1";
		break;

	case "mirabelle_1":
		PlaySound("Voice\Spanish\Girl_Q.wav");
		dialog.text = "Oh...";
		link.l1 = "... ";
		link.l1.go = "mirabelle_2";
		break;

	case "mirabelle_2":
		DialogExit();
		npchar.dialog.currentnode = "mirabelle_3";
		sld = characterFromId("Mrt_Rocur");
		sld.dialog.currentnode = "rocur_74";
		ChangeCharacterAddressGroup(sld, "LaVega_TwoFloorHouse", "goto", "goto8");
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.5);
		break;

	case "mirabelle_3":
		PlaySound("Voice\Spanish\LE\Mirabel\Mirabel_01.wav");
		dialog.text = "¡Señor! ¡Señor " + pchar.name + " ¡tenga piedad, por favor! ¡Se lo ruego! ¡Permaneceré en silencio! ¡Odio a esa bestia de Tyrex! ¡Se lo ruego, por favor!";
		link.l1 = "...";
		link.l1.go = "mirabelle_4";
		break;

	case "mirabelle_4":
		DialogExit();
		npchar.dialog.currentnode = "mirabelle_5";
		npchar.greeting = "mirabella_goodgirl";
		sld = characterFromId("Mrt_Rocur");
		sld.dialog.currentnode = "rocur_80";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;

	case "mirabelle_5":
		dialog.text = "";
		link.l1 = "¡Eh, muchacha! ¿Oíste eso? Vendrás conmigo o este bastardo brutal te matará.";
		link.l1.go = "mirabelle_6";
		break;

	case "mirabelle_6":
		dialog.text = "¡Iré con usted, señor, ¡a donde sea que me lleve!";
		link.l1 = "Está bien. Cierra la boca, o te mataré si empiezas a gritar o llamar a Tyrex. ¿Cómo te llamas?";
		link.l1.go = "mirabelle_7";
		break;

	case "mirabelle_7":
		dialog.text = "Mirabelle...";
		link.l1 = "Compórtate bien, Mirabelle, y esto terminará bien para ti. Mantente cerca de mí y no hagas ruido.";
		link.l1.go = "mirabelle_8";
		break;

	case "mirabelle_8":
		dialog.text = "Juro que no lo haré, señor.";
		link.l1 = "...";
		link.l1.go = "mirabelle_9";
		break;

	case "mirabelle_9":
		DialogExit();
		npchar.dialog.currentnode = "mirabelle_10";
		LAi_SetImmortal(npchar, true);
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		sld = characterFromId("Mrt_Rocur");
		sld.dialog.currentnode = "rocur_85";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		pchar.questTemp.Mtraxx.Mirabella = "true";
		break;

	case "mirabelle_10":
		dialog.text = "¿Señor?";
		link.l1 = "Lo hiciste bien, chica, me gustas por eso. Ahora vamos a mi barco donde te pondrán en un pequeño camarote por un tiempo. Lo siento, pero no quiero que corras a Tyrex y le cuentes algo.";
		link.l1.go = "mirabelle_11";
		break;

	case "mirabelle_11":
		dialog.text = "¡De ninguna manera, señor! ¡Nunca iría con Tyrex, ese bastardo! ¡Lo odio! ¡¡¡Lo odio!!!";
		link.l1 = "¡Caray! ¿Qué te hizo?";
		link.l1.go = "mirabelle_12";
		break;

	case "mirabelle_12":
		dialog.text = "¡Mucho... ¡lo odio, lo odio!";
		link.l1 = "Ya veo. Una vez que lleguemos, vivirás en una casa bastante lujosa. Sola. Manténme de buen humor y nadie te hará daño. Ahora ve al bote... Mirabelle.";
		link.l1.go = "mirabelle_13";
		break;

	case "mirabelle_13":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "sea", "none", "", "", "OpenTheDoors", 20.0);
		pchar.quest.mtraxx_pasq_mirabella.win_condition.l1 = "location";
		pchar.quest.mtraxx_pasq_mirabella.win_condition.l1.location = "Shore75";
		pchar.quest.mtraxx_pasq_mirabella.function = "Mtraxx_PasqualeMirabella";
		pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1 = "location";
		pchar.quest.mtraxx_pasq_mirabella1.win_condition.l1.location = "Shore77";
		pchar.quest.mtraxx_pasq_mirabella1.function = "Mtraxx_PasqualeMirabella";
		AddPassenger(pchar, npchar, false); // добавить пассажира
		SetCharacterRemovable(npchar, false);
		SetFunctionTimerCondition("Mtraxx_MirabellaSailOver", 0, 0, 30, false); // месяц на доплыть до Исла Моны
		break;

	case "mirabelle_14":
		dialog.text = "¿Hemos llegado, señor?";
		link.l1 = "Sí, cariño. Este es mi pueblo y mi casa. Soy el dueño del lugar. Aunque soy un huésped poco frecuente aquí, demasiado trabajo por ahí. Asegúrate de mantener mi casa limpia mientras vivas en ella o te entregaré a Rodgar y sus carpinteros. Siéntete libre de pasear por la isla, es muy hermosa, pero no hay escapatoria de ella de todas formas.";
		link.l1.go = "mirabelle_15";
		// belamour legendary edition -->
		link.l2 = "Bueno, aquí estamos. Esta es mi casa. Todo en esta isla me pertenece. No vengo aquí a menudo - después de todo, vivo en el barco, pero alguien necesita cuidar de la casa. Rodgar amablemente accedió a cederte este papel honorífico. Puedes pasear tanto como quieras, incluso en las junglas o en las playas, pero asegúrate de tener a alguien como compañero, todavía hay animales salvajes por aquí. De todos modos, no puedes irte de aquí sin un barco.";
		link.l2.go = "mirabelle_15a";
		break;

	case "mirabelle_15a":
		ChangeCharacterComplexReputation(pchar, "nobility", -1);
		dialog.text = "No tengo adónde ir, señor " + pchar.name + ". No tengo a nadie, y nadie me necesita. A menos que me venda a un burdel...";
		link.l1 = "En el hogar hay una trampilla que lleva al subsuelo, no vayas allí, caerás en la cueva y te romperás los huesos, o no podrás regresar y podrías morir de hambre. Y entonces será una pena que te haya salvado en vano.";
		link.l1.go = "mirabelle_16";
		break;

	case "mirabelle_15":
		ChangeCharacterComplexReputation(pchar, "nobility", -10);
		// <-- legendary edition
		dialog.text = "No tengo adónde ir, señor " + pchar.name + " No tengo familia ni utilidad. Podría terminar en un burdel otra vez.";
		link.l1 = "Hay una trampilla que lleva a la cueva, aléjate de ella. Es oscuro y peligroso ahí abajo.";
		link.l1.go = "mirabelle_16";
		break;

	case "mirabelle_16":
		dialog.text = "Me mantendré alejada, señor.";
		link.l1 = "También hay un dormitorio arriba. Sígueme.";
		link.l1.go = "mirabelle_17";
		break;

	case "mirabelle_17":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorFollow(npchar, pchar, "", -1);
		pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1 = "location";
		pchar.quest.mtraxx_islamona_mirabella1.win_condition.l1.location = "IslaMona_TwoFloorRoom";
		pchar.quest.mtraxx_islamona_mirabella1.function = "Mtraxx_PasqualeMirabellaRoom";
		break;

	case "mirabelle_18":
		dialog.text = "";
		link.l1 = "Listo. Te he mostrado toda la casa. No es peor que el lugar de Tyrex en el que vivías antes. Espero que te guste.";
		link.l1.go = "mirabelle_19";
		break;

	case "mirabelle_19":
		dialog.text = "Sí, señor. Tiene una gran casa. Prometo cuidarla bien en su ausencia.";
		link.l1 = "Me alegra que seas tan cooperativa conmigo. Espero que estés siendo honesta. Sé honesta conmigo o te arrepentirás de no serlo. Sé una buena chica y no me pongas triste y yo seré bueno contigo. ¡Charlie Prince honra su palabra!";
		link.l1.go = "mirabelle_20";
		// belamour legendary edition -->
		link.l2 = "Te creo, querida. Creo que estarás más segura aquí que encadenada en ese oscuro almacén donde Tyrex te mantenía.";
		link.l2.go = "mirabelle_20a";
		break;

	case "mirabelle_20a":
		ChangeCharacterComplexReputation(pchar, "nobility", 2);
		dialog.text = "Gracias, señor " + pchar.name + ". Gracias por no dejar que su... compañero me matara. Usted es muy amable conmigo...";
		link.l1 = "Heh, y eres graciosa... Y tu cara es bonita también, incluso con una marca en la frente. Espero que todo lo demás esté en su lugar también... Bueno, ahora muestra a tu capitán lo que puedes hacer. Relajémonos un par de horas después del balanceo del mar.";
		link.l1.go = "mirabelle_21";
		link.l2 = "Muy bien. Eso es todo, tengo - mucho trabajo por hacer. Y tú acomódate, conoce a Rodgar y a los muchachos. Cuando regrese, charlaremos un poco más.";
		link.l2.go = "mirabelle_21a";
		break;

	case "mirabelle_20":
		ChangeCharacterComplexReputation(pchar, "nobility", -5);
		// <-- legendary edition
		dialog.text = "Gracias, señor " + pchar.name + ". Gracias por no permitir que su... compañero me matase. Es un hombre muy amable.";
		link.l1 = "Heh, eres muy dulce y divertida... Una cara bonita también a pesar de la marca. Espero que el resto esté en su lugar también... Ahora muestra a tu capitán de lo que eres capaz.";
		link.l1.go = "mirabelle_21";
		// belamour legendary edition -->
		link.l2 = "Muy bien. Eso es todo, tengo - mucho trabajo que hacer. Y tú acomódate, conoce a Rodgar y los muchachos. Cuando regrese, charlaremos un poco más.";
		link.l2.go = "mirabelle_21a";
		break;

	case "mirabelle_21a":
		AddCharacterExpToSkill(pchar, "Leadership", 400);
		AddCharacterExpToSkill(pchar, "Fortune", 400);
		pchar.questTemp.Mtraxx.MirabellaFirstTimeSex = true;
		DialogExit();
		npchar.InOurHouse = true;
		npchar.dialog.currentnode = "mirabelle_26";
		chrDisableReloadToLocation = false;
		pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
		pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
		bQuestDisableMapEnter = false; // открыть карту
		DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;

	case "mirabelle_21":
		DialogExit();

		pchar.questTemp.Mtraxx.MirabellaFirstTimeKiss = true;
		sld = characterFromId("Mirabella");
		LAi_SetActorType(sld);
		LAi_ActorTurnToCharacter(sld, pchar);
		StartQuestMovie(true, false, true);
		LAi_SetActorType(pchar);
		LAi_Fade("IslaMona_MirabelleKiss", "");
		break;

	case "mirabelle_22":
		PlaySound("Voice\Spanish\LE\Mirabel\Mirabel_07.wav");
		dialog.text = "Capitán " + pchar.name + ", estuvo muy bien, señor... Espero que le haya gustado también. He trabajado muy duro. Debe haber llegado de Europa hace poco.";
		link.l1 = "Adúlame, pequeña mentirosa, me lo estoy creyendo. Je, eres buena, ¡Mirabelle! Tyrex tiene buen gusto, je-je...";
		link.l1.go = "mirabelle_23";
		locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;

	case "mirabelle_23":
		dialog.text = "No lo soy. Y usted es un caballero. Pero está pretendiendo ser grosero por alguna razón. Mhmm... Me gustó mucho. Estaré esperando verle de nuevo...";
		link.l1 = "Ah sí, un caballero... un caballero de fortuna, ¡ja-ja! Muy bien, querida, instálate aquí por ahora.";
		link.l1.go = "mirabelle_24";
		break;

	case "mirabelle_24":
		dialog.text = "Adiós, señor.";
		link.l1 = "...";
		// belamour legendary edition -->
		if (CheckAttribute(pchar, "questTemp.Mtraxx.MirabellaFirstTimeSex"))
		{
			link.l1.go = "mirabelle_28";
			DeleteAttribute(pchar, "questTemp.Mtraxx.MirabellaFirstTimeSex");
		}
		else
			link.l1.go = "mirabelle_25";
		// <-- legendary edition
		break;

	case "mirabelle_25":
		DialogExit();
		npchar.InOurHouse = true;
		npchar.dialog.currentnode = "mirabelle_26";
		LAi_SetStayType(npchar);
		chrDisableReloadToLocation = false;
		pchar.quest.mtraxx_mirabella_setlife.win_condition.l1 = "MapEnter";
		pchar.quest.mtraxx_mirabella_setlife.function = "Mtraxx_MirabellaSetLife";
		bQuestDisableMapEnter = false; // открыть карту
		DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		break;

	case "mirabelle_26":
		dialog.text = TimeGreeting() + ", señor " + pchar.name + "¡Qué alegría volver a verlo! ¿Se encuentra bien?";
		link.l1 = RandSwear() + "" + RandPhraseSimple("¡Temblad mis maderos, temblad mi alma!", "¡Oh, mejor vivir y morir bajo la valiente bandera negra que ondeo!") + " Charlie Prince está bien, cariño.";
		link.l1.go = "mirabelle_26x";
		if (!CheckAttribute(pchar, "questTemp.MirabelleBlock"))
		{
			if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
			{
				link.l2 = "Corazón, ¿qué te parece hacer a un capitán un poco más feliz?";
				link.l2.go = "mirabelle_sex";
			}
		}
		break;

	case "mirabelle_26x":
		DialogExit();
		npchar.dialog.currentnode = "mirabelle_26";
		break;

	case "mirabelle_sex":
		dialog.text = "¡Lo que sea por usted, señor!";
		link.l1 = RandPhraseSimple("¡Preparen los garfios!", "¡Abórdenlos!");
		link.l1.go = "mirabelle_sex_1";
		break;

	case "mirabelle_sex_1":
		DialogExit();

		StartQuestMovie(true, false, true);
		LAi_SetActorType(pchar);
		LAi_Fade("", "");

		LAi_SetActorType(npchar);
		// belamour legendary edition -->
		if (CheckAttribute(pchar, "questTemp.Mtraxx.MirabellaFirstTimeSex"))
			npchar.dialog.currentnode = "mirabelle_22";
		else
			npchar.dialog.currentnode = "mirabelle_27";
		// <-- legendary edition
		if (pchar.location == "IslaMona_TwoFloorRoom")
			DoQuestCheckDelay("IslaMona_MirabelleKiss", 0.5);
		else
			DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "IslaMona_MirabelleKiss");
		break;

	case "mirabelle_27":
		dialog.text = "Mhm... ¡Señor, eres un mago! ¿Espero que a usted también le haya gustado? Estaba haciendo lo mejor que podía.";
		link.l1 = "Lo hiciste genial, cariño.";
		link.l1.go = "mirabelle_28";
		locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;

	case "mirabelle_28":
		DialogExit();
		npchar.dialog.currentnode = "mirabelle_26";
		LAi_SetStayType(npchar);
		SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;

	case "mirabelle_sleep":
		dialog.text = "¡Esto no es cierto, no es cierto! Señor " + pchar.name + " ¡es bueno y amable! ¡Sólo está fingiendo ser un malvado pirata! Usted es, ¿" + pchar.name + "?";
		link.l1 = "";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionSleep6_1");
		break;

	case "mirabelle_29":
		dialog.text = TimeGreeting() + ", señor " + pchar.name + "¡Estoy muy feliz de verte! ¿Cómo estás? ¿Por qué estás tan triste?";
		link.l1 = "Hola, Mirabelle. ¿Por qué crees que estoy triste?";
		link.l1.go = "mirabelle_30";
		break;

	case "mirabelle_30":
		dialog.text = "Bueno, lo veo. No eres el de siempre. ¿Quieres que te anime? ¡Vamos! He recogido algunas frutas realmente dulces de la jungla y el pescado que Rodgar y sus muchachos pescaron ayer está asado y todavía caliente.";
		link.l1 = "Espera. Quiero hablar contigo.";
		link.l1.go = "mirabelle_31";
		break;

	case "mirabelle_31":
		dialog.text = "Por supuesto, señor, lo que usted diga. Estoy todo oídos";
		link.l1 = "Dime, ¿cómo caíste en las manos de Tyrex y por qué tienes la marca de un ladrón en la frente? No temas, nunca te haré daño. Solo necesito escuchar tu historia.";
		link.l1.go = "mirabelle_32";
		break;

	case "mirabelle_32":
		dialog.text = "¡Ah, señor! Mi historia es breve y aburrida. Nací en Puerto Rico, mi padre era un caballero blanco, mi madre - una india. Nunca vi a mi papá. Cuando era niño era sirviente y cuando crecí cometí la locura de robar las joyas de mi amo. Nunca tuve nada propio y quería uno con tantas ganas, solo para probarlo por un día. Por supuesto, lo descubrieron todo\nHubo un juicio, fui azotado, marcado y encarcelado en San Juan. No estuve allí demasiado tiempo: uno de los oficiales hizo un trato con un jefe y fui vendido a un burdel de Philipsburg por un puñado de doblones de oro\nPasé allí un año más o menos. Un día desafortunado recibimos la visita de Tyrex y su asqueroso amigo con gafas.";
		link.l1 = "Pasquale Lavoisier...";
		link.l1.go = "mirabelle_33";
		break;

	case "mirabelle_33":
		dialog.text = "Sí-sí, su nombre era señor Pasquale Lavoisier. No tengo ni idea de qué vieron en mí, pero poco después de su visita, Tyrex me compró a Madame Johanna y me encerró en una casa llena de cofres y mercancías. Fue el peor momento de mi vida, incluso peor que los días pasados en la prisión de San Juan. Tyrex me visitaba todos los días a menos que estuviera en el mar y entonces podía respirar libremente, pero cada vez que venía el señor Lavoisier yo... yo.... Era lo peor de todo. Señor " + pchar.name + ", por favor, ¿puedo no hablar de esto?\nNo sé cuánto tiempo estuve allí. Y luego viniste y me sacaste de esa casa horrible. Tuve mucha suerte de que fueras tan amable.";
		link.l1 = "¿Amable? Mirabelle, pero te hice exactamente lo mismo: te llevé a una isla y te encerré en una casa.";
		link.l1.go = "mirabelle_34";
		break;

	case "mirabelle_34":
		dialog.text = "No, señor, no es cierto. ¿Estoy encerrado aquí? Doy un paseo por la isla todos los días. Es un lugar maravilloso y tranquilo. ¿Tengo que hacer mucho trabajo doméstico? En absoluto, y me acostumbro de todos modos. Y no eres como Tyrex, ni como su amigo comerciante. Siempre me alegra verte, eres tan joven y apuesto. Y un caballero también...";
		link.l1 = "Mirabelle, ¿quieres que te lleve a alguna ciudad? Te daré suficiente dinero. ¿A dónde? Elige cualquier colonia.";
		link.l1.go = "mirabelle_35";
		break;

	case "mirabelle_35":
		dialog.text = "Señor, ¿quiere ahuyentarme? Por favor, no lo haga, ¡te lo ruego!";
		link.l1 = "Bueno... Pensé que querrías volver a la vida normal...";
		link.l1.go = "mirabelle_36";
		break;

	case "mirabelle_36":
		dialog.text = "Ah, señor " + pchar.name + ", ¿y qué hay para mí? ¿Cómo me casaré siendo una mestiza marcada? Me venderán a un burdel de nuevo. Por favor, no me envíes lejos. Me gusta este lugar, no me he sentido tan en paz y segura en ningún otro sitio como aquí. Rodgar y sus chicos son buenos tipos, somos amigos y nunca me han hecho daño, cada uno de ellos arriesgaría su vida por mí. Me gusta pasar tiempo con ellos y ¡es divertido! A veces hacemos una fogata en la playa y bailo samba. Por favor, señor, haré cualquier cosa por usted, solo déjeme quedarme.";
		link.l1 = "Bien, Mirabelle, quédate aquí ya que te gusta tanto este lugar. Solo debes saber que no eres prisionera aquí, siempre puedes pedirme que te lleve lejos de aquí.";
		link.l1.go = "mirabelle_37";
		break;

	case "mirabelle_37":
		dialog.text = "¡Mi querido y buen señor, gracias! ¡Gracias! ¡Gracias! Nunca te pediré algo así - quiero quedarme prisionero de esta isla... y tu prisionero, je-je... ¡Eres tan amable pero hoy estás triste! No cantas ni maldices como sueles hacerlo.";
		link.l1 = "Podría cantar pero no más juramentos, Mirabelle. Y... lo siento si alguna vez fui grosero contigo.";
		link.l1.go = "mirabelle_38";
		break;

	case "mirabelle_38":
		dialog.text = "¿Serás severo y estricto como un lord inglés?.. Ah... señor, ¿quieres que baile y cante esta noche? Solo para ti. Ahora ven conmigo! No hay mejor cura para la tristeza que el amor. Te he echado tanto de menos.";
		link.l1 = "¡Ja! Buen punto, mi querida muchacha... Vamos.";
		link.l1.go = "mirabelle_39";
		break;

	case "mirabelle_39":
		DialogExit();
		LAi_SetActorType(npchar);
		npchar.dialog.currentnode = "mirabelle_40";
		if (pchar.location == "IslaMona_TwoFloorRoom")
			DoQuestCheckDelay("IslaMona_MirabelleKiss", 0.5);
		else
			DoQuestReloadToLocation("IslaMona_TwoFloorRoom", "goto", "goto2", "IslaMona_MirabelleKiss");
		break;

	case "mirabelle_40":
		PlaySound("Voice\Spanish\LE\Mirabel\Mirabel_07.wav");
		dialog.text = "Ah, señor " + pchar.name + ", fuiste tan gentil hoy, mhm... ¿Estás complacido conmigo, mi querido capitán?";
		link.l1 = "Todo fue encantador, Mirabelle.";
		link.l1.go = "mirabelle_41";
		locCameraFromToPos(0.55, 1.64, -1.09, true, 0.63, -0.30, -3.12);
		break;

	case "mirabelle_41":
		DialogExit();
		npchar.dialog.currentnode = "mirabelle_42";
		LAi_SetStayType(npchar);
		SaveCurrentNpcQuestDateParam(npchar, "sex_date");
		break;

	case "mirabelle_42":
		bool bMary = GetCharacterIndex("Mary") != -1 && CheckAttribute(pchar, "questTemp.LSC.Mary_officer");
		bool bHelena = GetCharacterIndex("Helena") != -1 && CheckAttribute(pchar, "questTemp.Saga.Helena_officer");
		dialog.text = TimeGreeting() + ", señor " + pchar.name + "¡Estoy tan feliz de verte! ¿Cómo te va?";
		link.l1 = "" + LinkRandPhrase("Me alegra verte también, muchacha.", "Hola, Mirabelle. Siempre eres la misma, alegre y hermosa, qué vista tan agradable.", "Hola, preciosa. ¡Te ves impresionante!") + "Estoy bien. Espero que tú también estés bien.";
		link.l1.go = "mirabelle_42x";
		if (!bMary && !bHelena && !CheckAttribute(npchar, "quest.rodgar")) // прогона 3
		{
			if (!CheckAttribute(npchar, "sex_date") || GetNpcQuestPastDayParam(npchar, "sex_date") >= 1)
			{
				link.l2 = "Mirabelle, ya te echo de menos a ti y a tu comadreja. ¿Besará a tu lobo de mar?";
				link.l2.go = "mirabelle_43";
			}
		}
		break;

	case "mirabelle_42x":
		DialogExit();
		npchar.dialog.currentnode = "mirabelle_42";
		break;

	case "mirabelle_43":
		dialog.text = "¡Ah, mi dulce capitán, yo también te he extrañado! ¡Vamos, estoy al límite!";
		link.l1 = "...";
		link.l1.go = "mirabelle_39";
		break;

	// Jason Исла Мона
	case "mirabelle_44":
		dialog.text = "¡Señor Capitán! Capitán " + pchar.name + "¡Estoy tan feliz! ¡Nos salvarás!";
		link.l1 = "Me alegra verte también, Mirabelle. Entonces, ¿qué hay de las pérdidas?";
		link.l1.go = "mirabelle_45";
		break;

	case "mirabelle_45":
		DialogExit();
		npchar.dialog.currentnode = "mirabelle_42";
		sld = characterFromId("Islamona_carpenter");
		sld.dialog.currentnode = "IslaMona_66";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.0);
		break;

	case "mirabelle_46":
		dialog.text = "¡Capitán, Capitán, gracias! ¡Eres el mejor, el más amable! ¡No solo me salvaste de los monstruos, sino que también me diste una nueva vida! ¡A todos nosotros!";
		link.l1 = "";
		link.l1.go = "mirabelle_47";
		locCameraFromToPos(1.25, 1.28, 0.71, false, 2.28, -0.20, 1.91);
		break;

	case "mirabelle_47":
		DialogExit();
		npchar.dialog.currentnode = "mirabelle_42";
		if (CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && GetCharacterIndex("Mary") != -1)
		{
			sld = characterFromId("Mary");
			sld.dialog.currentnode = "IslaMona_2";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.0);
		}
		else
		{
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && GetCharacterIndex("Helena") != -1)
			{
				sld = characterFromId("Helena");
				sld.dialog.currentnode = "IslaMona_2";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
			else
			{
				sld = characterFromId("Himenes_companion_1");
				sld.dialog.currentnode = "island_man_2";
				LAi_SetActorType(sld);
				LAi_ActorDialogDelay(sld, pchar, "", 0.0);
			}
		}
		break;

	case "mirabelle_48":
		dialog.text = "¡Señor Capitán!";
		link.l1 = "Hola a ti también, belleza. ¿No estás aburrida, verdad?";
		link.l1.go = "mirabelle_49";
		break;

	case "mirabelle_49":
		dialog.text = "¡Ah, Capitán! Desde que me rescataste de esa casa espantosa, mi vida ha ganado color y alegría.";
		link.l1 = "¿Estás feliz?";
		link.l1.go = "mirabelle_50";
		break;

	case "mirabelle_50":
		dialog.text = "¡Por supuesto! Y me gustaría compartir esta felicidad contigo... Te estaré esperando en tu habitación, arriba.";
		link.l1 = "Qué mujer...";
		link.l1.go = "mirabelle_51";
		break;

	case "mirabelle_51":
		DialogExit();
		LAi_SetActorType(npchar);
		npchar.dialog.currentnode = "mirabelle_40";
		DoQuestFunctionDelay("IslaMona_ChurchReloadToRoom", 0.5);
		pchar.questTemp.IslaMona.Mirabelle = "true";
		break;

	case "mirabelle_52":
		dialog.text = "¡Señor Capitán!";
		link.l1 = "Hola a ti también, belleza. ¿No estás aburrida, verdad?";
		link.l1.go = "mirabelle_53";
		break;

	case "mirabelle_53":
		dialog.text = "¡Ah, Capitán! Desde que me rescataste de aquella casa espantosa, mi vida ha ganado color y alegría.";
		link.l1 = "¿Estás feliz?";
		link.l1.go = "mirabelle_54";
		break;

	case "mirabelle_54":
		dialog.text = "¡Mucho! Excepto...";
		link.l1 = "Ya veo, ¿quieres pedirme algo?";
		link.l1.go = "mirabelle_55";
		break;

	case "mirabelle_55":
		dialog.text = "¡Sí, Capitán! Me gustaría... compartir mi felicidad con cierto hombre...";
		link.l1 = "¿Le importará?";
		link.l1.go = "mirabelle_56";
		break;

	case "mirabelle_56":
		dialog.text = "No, no, Capitán. Seríamos felices juntos, lo sé con certeza. Solo... ¿lo permitirás?";
		link.l1 = "Tú más que nadie mereces esto. ¡Pero no voy a casar a los dos, ni lo pienses!";
		link.l1.go = "mirabelle_57";
		break;

	case "mirabelle_57":
		dialog.text = "¡Ja, ja! ¡Mi caballero! Gracias, Señor Capitán. No sé qué dicen de usted en el gran mundo, pero siempre vi en usted a la persona más amable y luminosa.";
		link.l1 = "Buena suerte, Mirabelle.";
		link.l1.go = "mirabelle_58";
		break;

	case "mirabelle_58":
		DialogExit();
		npchar.quest.rodgar = true;
		npchar.dialog.currentnode = "mirabelle_42";
		break;

	// губернатор Картахены
	case "CartahenaMayor":
		dialog.text = "¡Malditos ladrones! No importa, nuestro mensajero ya está en camino a Portobello. Pronto nuestra escuadra llegará y...";
		link.l1 = TimeGreeting() + ", su Alteza. Un placer verle en tan hermosa mansión. Espero que la conserve después de que nos vayamos. Si yo fuera usted, no contaría con el escuadrón, además no nos quedaremos aquí más de tres días. Apuesto a que entiende que los nobles dones de Portobello no llegarán aquí para ayudarle tan pronto. Así que, vayamos directamente al grano, ¿de acuerdo?";
		link.l1.go = "CartahenaMayor_1";
		break;

	case "CartahenaMayor_1":
		dialog.text = "¿Ya hablando de negocios? ¡Mira por la ventana! ¡Mira lo que tus matones están haciendo en las calles y en las casas!";
		link.l1 = "Oh, su Alteza, esto no es nada comparado con lo que harán si no coopera lo suficiente. Espero que entienda quiénes son estos hombres...";
		link.l1.go = "CartahenaMayor_2";
		break;

	case "CartahenaMayor_2":
		dialog.text = "¡Sé de lo que es capaz el malvado pirata Charlie Prince! ¡Sé quién es su jefe! ¡Con el tiempo, quemaremos su guarida de bandidos en La Española! ¿Cuánto?";
		link.l1 = "No malgastes palabras, mi querido gobernador. Será mejor que me consigas 250 000 pesos.";
		link.l1.go = "CartahenaMayor_3";
		break;

	case "CartahenaMayor_3":
		dialog.text = "¿Qué?! ¡Tu insolencia no tiene límites! ¡Esto es un robo!";
		link.l1 = "Es un robo, por supuesto. ¿Qué más podría ser? Reúne a tus élites, tus mercaderes y comerciantes, junta oro en un gran cofre porque de lo contrario... lo haré mucho peor para ti y tu gente.";
		link.l1.go = "CartahenaMayor_4";
		break;

	case "CartahenaMayor_4":
		dialog.text = "¡Maldito pirata! ¡Bastardo! ¡Hereje! ¡Vete a la mierda!";
		link.l1 = "Por tu lengua sucia, aumento el rescate hasta 300 000.";
		link.l1.go = "CartahenaMayor_5";
		break;

	case "CartahenaMayor_5":
		dialog.text = "¡QUEMA EN EL INFIERNO, HIJO DE PUTA!!!";
		link.l1 = "350 000. ¿Quieres continuar?";
		link.l1.go = "CartahenaMayor_6";
		break;

	case "CartahenaMayor_6":
		dialog.text = "¡No hay tal dinero en la ciudad!";
		link.l1 = "Mientes. Simplemente no puede ser. Aquí podemos reunir al menos un millón, pero me temo que no tenemos tiempo suficiente para hacerlo. Por lo tanto, seré amable y generoso. Conoces la suma. Ve a conseguirla.";
		link.l1.go = "CartahenaMayor_7";
		break;

	case "CartahenaMayor_7":
		dialog.text = "Te lo digo de nuevo, Charlie Prince: ¡no hay tal dinero en Cartagena!";
		link.l1 = "Oh... cómo puedes ser tan aburrido. ¡Alfanje! Busca por ahí y trae aquí a todos los que encuentres. ¡Busca bien! Y esperaremos aquí por ahora, su gracia...";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_CartahenaInResidence");
		break;

	case "CartahenaMayor_8":
		dialog.text = "";
		link.l1 = "¡Oye, señor 'Testarudo'! ¿No has cambiado de opinión respecto a la recolección de dinero en la buena ciudad de Cartagena?... ¿Qué pasó, por qué estás tan serio de repente? ¿Estás bien? ¿Debería traerte un poco de agua?";
		link.l1.go = "CartahenaMayor_9";
		break;

	case "CartahenaMayor_9":
		dialog.text = "";
		link.l1 = "Por lo que entiendo, estas dos damas son tu esposa y tu hija, ¿verdad? La tercera chica parece una sirvienta, parece que no te importa un carajo, así que no le haremos daño, pero estas dos bellezas pueden atraer la atención de mi hermano de armas, señor Sable. Parece que le gustan, señor. Entonces, ¿qué? ¿Vas a manejar el rescate?";
		link.l1.go = "CartahenaMayor_10";
		break;

	case "CartahenaMayor_10":
		dialog.text = "Yo... necesitaré tiempo.";
		link.l1 = "¡Ajá! ¡Ahora hablas en serio! ¿Entonces quién es el bastardo aquí? No te importó un carajo que mis hombres aterrorizaran a tus ciudadanos, pero tus dos mujeres son un asunto completamente diferente, ¿verdad? ¿Te atreviste a negociar conmigo, imbécil? ¡Te mostraré lo que significa cruzarse con Charlie Prince!";
		link.l1.go = "CartahenaMayor_10x";
		break;

	case "CartahenaMayor_10x":
		dialog.text = "";
		link.l1 = "Ve y reúne el maldito rescate. 350 000 y ni un peso menos. Tienes un día. Nos quedaremos aquí para beber un poco de vino y mezclarnos con estas dulces mujeres... Apresúrate amigo, o yo y mi amigo aquí, señor Cutlass, podríamos enamorarnos de tus bellezas y entonces tendrás que rescatarlas también. ¡Adelante! ¡Marcha!";
		link.l1.go = "CartahenaMayor_11";
		break;

	case "CartahenaMayor_11":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "Mtraxx_CartahenaResidenceWait", 5.0);
		break;

	case "CartahenaMayor_12":
		AddMoneyToCharacter(pchar, 350000);
		dialog.text = "¡Toma tu dinero ensangrentado, Charlie Prince!";
		link.l1 = "¿Reuniste un rescate? ¡Espléndido! Pero llegas una hora tarde, mi querido gobernador. Esta hora extra me dio a mí y al Cutlass la comprensión de que nuestras vidas serían demasiado aburridas sin estas bellezas que fueron tan amables y habladoras con nosotros...";
		link.l1.go = "CartahenaMayor_13";
		break;

	case "CartahenaMayor_13":
		dialog.text = "¡Tú... tú!";
		link.l1 = "Ah, estás demasiado nervioso por tu trabajo, mi amigo. Estaba bromeando... ¡Al sable! ¡Vámonos, nos vamos!";
		link.l1.go = "CartahenaMayor_14";
		break;

	case "CartahenaMayor_14":
		DialogExit();
		AddQuestRecord("Roger_9", "7");
		AddDialogExitQuestFunction("Mtraxx_CartahenaToFort");
		break;

	// Камилла
	case "camilla":
		PlaySound("Voice\Spanish\Girls_3.wav");
		dialog.text = "¡Hola! ¡Así que este es Charlie Prince, el famoso pirata, el terror del Mar del Sur español!";
		link.l1 = RandSwear() + "Heh, no tenía idea de que soy tan popular en Tortuga. ¿Cómo te llamas, dulce niña?";
		link.l1.go = "camilla_1";
		break;

	case "camilla_1":
		dialog.text = "Mi nombre es Camilla.";
		link.l1 = "Camilla... solía conocer a una chica con el mismo nombre en Francia. ¡Fue hace tanto tiempo!";
		link.l1.go = "camilla_2";
		break;

	case "camilla_2":
		PlaySound("ambient\tavern\orijka_003.wav");
		dialog.text = "";
		link.l1 = "(vomitando) ... maldita sea... Lo siento, princesa, pero Prince está un poco borracho esta noche. Entonces... eh.. ¿por qué viniste a verme?";
		link.l1.go = "camilla_3";
		break;

	case "camilla_3":
		dialog.text = "Por varias razones. O tal vez sin razón alguna.";
		link.l1 = "Por Dios, esto es demasiado complicado. Pareces ser un misterio, muchacha.";
		link.l1.go = "camilla_4";
		break;

	case "camilla_4":
		dialog.text = "Cada dama debe tener un misterio.";
		link.l1 = "Parece que quieres que resuelva este misterio. ¿No? ¡Soy un maestro en resolver misterios de damas, lo juro! ¿Deberíamos ir a la taberna y beber algo de vino? ¡Te conseguiré el mejor regalo!";
		link.l1.go = "camilla_5";
		break;

	case "camilla_5":
		dialog.text = "Mmm... Me gustan los tipos duros. Pero no beberé vino abajo cerca de borrachos de baja estofa. Consíguenos una habitación, beberemos y hablaremos allí.";
		link.l1 = RandSwear() + "¡Estás ardiente! ¡Sígueme!";
		link.l1.go = "camilla_6";
		break;

	case "camilla_6":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		pchar.quest.mtraxx_retribution_tavern.win_condition.l1 = "locator";
		pchar.quest.mtraxx_retribution_tavern.win_condition.l1.location = "Tortuga_town";
		pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator_group = "reload";
		pchar.quest.mtraxx_retribution_tavern.win_condition.l1.locator = "reload4_back";
		pchar.quest.mtraxx_retribution_tavern.function = "Mtraxx_RetributionToTavern";
		break;

	case "camilla_7":
		PlaySound("Voice\Spanish\Gr_officiant_1.wav");
		dialog.text = "¡Ah, capitán! Sabes como acercarte a una dama. Vamos... ¡Llénalo, no hagas esperar a esta señorita!";
		link.l1 = "¡Por supuesto, mi dulzura!";
		link.l1.go = "camilla_8";
		break;

	case "camilla_8":
		LAi_Fade("", "");
		PlaySound("ambient\tavern\krujki_005.wav");
		PlaySound("ambient\tavern\naliv_003.wav");
		PlaySound("ambient\tavern\glotok_001.wav");
		WaitDate("", 0, 0, 0, 1, 5);
		dialog.text = "Mmm... Solo de pensarlo, estoy aquí completamente solo con Charlie Prince, bebiendo un vino excelente...";
		link.l1 = "¡Vas a disfrutar este viaje conmigo, oh te lo prometo! Charlie Prince es amable y gentil con las damas que se le someten. ¿Te someterás, princesa?";
		link.l1.go = "camilla_9";
		break;

	case "camilla_9":
		dialog.text = "Tee-hee... ¡Por supuesto, cariño! Tus promesas suenan tan tentadoras, ¿sabes...?";
		link.l1 = "Bueno, ¿entonces no perdamos tiempo, belleza?";
		link.l1.go = "camilla_10";
		break;

	case "camilla_10":
		dialog.text = "¡Oh! ¡Me encantan! ¡Hombres de verdad!";
		link.l1 = "... ";
		link.l1.go = "camilla_11";
		break;

	case "camilla_11":
		DialogExit();
		pchar.GenQuest.FrameLockEsc = true;
		bDisableCharacterMenu = true;
		ResetSound();
		WaitDate("", 0, 0, 0, 2, 30);
		SetLaunchFrameFormParam("", "", 0, 5.1);
		SetLaunchFrameFormPic("loading\inside\censored1.tga");
		PlayStereoSound("sex\sex2.wav");
		LaunchFrameForm();
		if (IsEquipCharacterByArtefact(pchar, "totem_03"))
		{
			AddCharacterHealth(pchar, 6);
			AddCharacterMaxHealth(pchar, 1.0);
		}
		else
			AddCharacterHealth(pchar, 3);
		LAi_SetCurHPMax(pchar);
		DoQuestCheckDelay("Mtraxx_RetributionRoomSex", 5.1);
		break;

	case "camilla_12":
		dialog.text = "Mmm...";
		link.l1 = "¿Te gustó, mi princesa?";
		link.l1.go = "camilla_13";
		break;

	case "camilla_13":
		dialog.text = "¡Por supuesto! Espero que yo también te haya gustado.";
		link.l1 = "¡Eh! ¡Incluso mi cabeza está ahora más clara que el cristal!";
		link.l1.go = "camilla_14";
		break;

	case "camilla_14":
		dialog.text = "Prince, tengo una petición para ti. ¿Me ayudarás?";
		link.l1 = "¡Conseguiré una estrella del cielo para ti, ja, ja! Adelante.";
		link.l1.go = "camilla_15";
		break;

	case "camilla_15":
		dialog.text = "Necesito llegar a La Vega, para ver a Tyrex. Le temo, pero ustedes hacen negocios juntos. Por favor, llévame con él.";
		link.l1 = "¡Mira esto! ¿Y por qué una chica tan dulce y frágil querría ver al Guardián del Código?";
		link.l1.go = "camilla_16";
		break;

	case "camilla_16":
		dialog.text = "Esta dulce y frágil muchacha quisiera ganar unas monedas. Mi difunto padre y hermanos no me dejaron mucho dinero. Tyrex puede arreglar esto.";
		link.l1 = "¿Oh, de verdad? ¿Y cómo? ¿Quieres una pista para un galeón español? ¡Ja-ja!";
		link.l1.go = "camilla_17";
		break;

	case "camilla_17":
		dialog.text = "Saqueando caravanas y ciudades es un negocio para tipos duros, como tú, cariño. Tengo otro negocio para Marcus. Él compra y vende información, ¿verdad? Tengo algo... No hay manera de que pueda usarlo yo mismo, pero él sí podría. Estaré bastante contento con solo obtener un pequeño interés de ello.";
		link.l1 = "¡Interesante! Cuéntame más.";
		link.l1.go = "camilla_18";
		break;

	case "camilla_18":
		dialog.text = "Hm... No sé...";
		link.l1 = "Oh, vamos. Considérame la mano derecha de Tyrex, he hecho mucho trabajo para él hasta ahora, créeme. Si tu información lo vale, la compraré yo mismo.";
		link.l1.go = "camilla_19";
		break;

	case "camilla_19":
		dialog.text = "Está bien. Te contaré más, pero sin detalles hasta que reciba el dinero. ¿Trato, cariño?";
		link.l1 = "Claro, preciosura. Charlie Prince no jode a sus socios... sabes a lo que me refiero, ¡ja-ja-ja! Adelante, soy todo oídos.";
		link.l1.go = "camilla_20";
		break;

	case "camilla_20":
		dialog.text = "... Mi padre era capitán de un bergantín mercante. Un día, de alguna manera, se enteró de un antiguo asentamiento minero español que se encontraba en lo profundo de las selvas del continente. Hace veinte años fue destruido por un terremoto. Los mineros lo abandonaron y los pasadizos secretos fueron olvidados. Excepto uno. Mi padre lo encontró\nLlevó a mis hermanos y a un guía allí y encontraron el lugar lleno de oro extraído y fundido hace años. Mucho oro. Al menos un millón de pesos. Padre regresó al barco para conseguir hombres que transportaran el oro, pero se sorprendió al descubrir que había desaparecido. Parece que su primer oficial había iniciado un motín y los dejaron a él y a mis hermanos en costas desiertas\nConstruyeron un bote y navegaron a lo largo de la costa buscando desesperadamente un lugar habitado, pero... (sollozos) una tormenta los golpeó y mis (sollozos) hermanos murieron. Padre sobrevivió pero no vivió mucho después de regresar a casa - la muerte de mis hermanos lo estaba matando lentamente día a día. Antes de fallecer, hizo un mapa y me lo dio\nMe dijo que cuando me casara, mi esposo debería ir allí, conseguir el oro y viviríamos nuestras vidas como reyes. Claro que sí, pero no dejaré que mi hombre entre en esas junglas malditas. ¡No otra vez! Un millón de pesos, dijo mi padre, pero simplemente no es de mi liga. Tal premio, sólo los mejores y más duros hombres pueden conseguirlo - hombres como Marcus Tyrex. Por eso voy a encontrarme con él.";
		link.l1 = "¿Cuánto quieres por el mapa?";
		link.l1.go = "camilla_21";
		break;

	case "camilla_21":
		dialog.text = "Doscientos doblones de oro. No es nada comparado con el premio. Tyrex estará de acuerdo con esto, estoy seguro. Es tan rico como Craso.";
		link.l1 = "¡Je! ¿Y si todo esto es un engaño?";
		link.l1.go = "camilla_22";
		break;

	case "camilla_22":
		dialog.text = "¿Parezco suicida? ¿Intentar cruzar a Tyrex? Querido, es mejor vivir en la pobreza que no vivir en absoluto. Entonces, ¿me llevarás allí? Por favor...";
		link.l1 = "¿Dónde está el mapa? ¿Me lo mostrarás?";
		link.l1.go = "camilla_23";
		break;

	case "camilla_23":
		dialog.text = "Mi sacerdote lo guarda a salvo. Te lo mostraré por 200 doblones.";
		link.l1 = "¡Muy bien! Lo compro. Los desconocidos en las tabernas a veces piden mucho más por basura.";
		link.l1.go = "camilla_24";
		break;

	case "camilla_24":
		dialog.text = "¿Eres tú? ¿Es cierto, cariño? Estoy tan feliz de no ir a La Vega. Para ser honesta, temo a Marcus. También te temo, por cierto... pero un poco menos.";
		link.l1 = "Una niña tan dulce no necesita temerme. ¿Dónde debo llevar el dinero?";
		link.l1.go = "camilla_25";
		break;

	case "camilla_25":
		dialog.text = "Hagamos un trato: encuéntrame en nuestra iglesia cualquier día desde las diez de la mañana hasta la una de la tarde. Me sentiré mucho más seguro bajo la protección de este lugar sagrado. Allí concluiremos nuestro trato.";
		link.l1 = "¿Todavía me temes? ¡Ja, ja! No, Camilla, no te engañaré. Charlie Prince no haría algo tan bajo por doscientos doblones, además quiero ayudarte.";
		link.l1.go = "camilla_26";
		break;

	case "camilla_26":
		dialog.text = "Maravilloso. Muy bien, guapo, te estaré esperando... ¡Gracias por el tiempo increíble que pasamos juntos esta noche! ¡Estoy tan feliz de habernos conocido!";
		link.l1 = "Nos vemos pronto, hermosa.";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Mtraxx_RetributionOutRoom");
		break;

	case "camilla_27":
		PlaySound("Voice\Spanish\Girls_3.wav");
		dialog.text = "¡Hola! ¿Y bien? ¿Trajiste el dinero, cariño?";
		if (PCharDublonsTotal() >= 200) // belamour legendary edition
		{
			link.l1 = "Sí. Toma tu oro y ahora dame el mapa.";
			link.l1.go = "camilla_28";
		}
		else
		{
			link.l1 = "Voy justo después de eso.";
			link.l1.go = "camilla_27x";
		}
		break;

	case "camilla_27x":
		DialogExit();
		npchar.dialog.currentnode = "camilla_27";
		break;

	case "camilla_28":
		RemoveDublonsFromPCharTotal(200); // belamour legendary edition
		GiveItem2Character(pchar, "mapEnrico");
		dialog.text = "Gracias, cariño... Aquí, tómalo. Juro por la memoria de mi padre - este mapa no es falso, te llevará directamente a donde debes ir...";
		link.l1 = "Bien, cariño. ¿Qué tal si celebramos nuestro trato como la última vez?";
		link.l1.go = "camilla_29";
		break;

	case "camilla_29":
		dialog.text = "Me gustaría, Prince, pero me estoy preparando para una confesión ante mi sacerdote, por lo tanto, estoy obligado a mantenerme alejado de cualquier tentación ahora mismo. Hagámoslo la próxima vez.";
		link.l1 = "Eh, me estás provocando, muchacha. ¡Está bien! No hay tiempo que perder: estamos a punto de zarpar. Juro que duplicaré tu interés si el mapa de tu padre realmente me lleva al oro.";
		link.l1.go = "camilla_30";
		break;

	case "camilla_30":
		dialog.text = "Eres tan generoso, cariño. ¡Buen viaje!";
		link.l1 = "¡Yo-ho-ho!";
		link.l1.go = "camilla_31";
		break;

	case "camilla_31":
		DialogExit();
		npchar.lifeday = 0;
		LAi_CharacterDisableDialog(npchar);
		AddQuestRecord("Roger_10", "2");
		bQuestDisableMapEnter = false; // открыть карту
		DeleteAttribute(pchar, "GenQuest.MapClosedNoBattle");
		pchar.quest.mtraxx_retribution_carataska.win_condition.l1 = "location";
		pchar.quest.mtraxx_retribution_carataska.win_condition.l1.location = "shore10";
		pchar.quest.mtraxx_retribution_carataska.function = "Mtraxx_RetributionCarataska";
		pchar.questTemp.Mtraxx.Retribution = "carataska";
		break;

	case "camilla_sleep":
		dialog.text = "Vuestros bastardos mataron a mi padre y a mis hermanos. Vuestro ataque a Cartagena ha traído dolor a cada familia allí. Espero que ahora estés asustado, tan asustado como nosotros, los ciudadanos de Cartagena, cuando vuestros brutos se divertían en las calles y en las casas. Arderás en el infierno, Charlie Prince.";
		link.l1 = "";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionSleep4");
		break;

	// дон Энрико - народный мститель
	case "enrico":
		PlaySound("Voice\Spanish\LE\Zorro\Don_Enriko_01.wav");
		dialog.text = "¡Tan pocas cosas en este mundo me alegran tanto como ver a las ratas en la caja despedazándose entre sí!\nSolo la rata más fuerte y asquerosa sobrevive. Entonces, lo único que hay que hacer es exprimirla...";
		link.l1 = "¡Argh! ¿Quién eres?!";
		link.l1.go = "enrico_1";
		break;

	case "enrico_1":
		PlaySound("Voice\Spanish\LE\Zorro\Don_Enriko_02.wav");
		dialog.text = "Soy don Enrico. La escoria inglesa me llama Fox, los holandeses me llaman Vos, los franceses me llaman Renaud. Pero prefiero mi apodo español de casa - Zorro. Castigo al mal que tortura y aterroriza a la gente común, la parte menos protegida del pueblo.\nEste juicio de hoy juzgará a cuatro piratas de Marcus Tyrex: Jeffry el Audaz, Pelly el Alfanje, Luke el Duende y Charlie Prince - estos bandidos son responsables de una masacre en Mérida y Cartagena. El último bastardo llamado Jean Handsome no se presentó aquí, debe ser el más listo de tu grupo.";
		link.l1 = "¿Qué?!";
		link.l1.go = "enrico_2";
		break;

	case "enrico_2":
		dialog.text = "Eres un canalla, Charlie Prince, pero no eres un idiota. Ya lo he descubierto, creo. Es una trampa para todos ustedes montada por mí con la ayuda de mapas falsos, documentos, palabras y promesas de oro y plata. Los he atraído a todos a estas mazmorras donde se destruyeron entre sí impulsados por sus repugnantes rasgos: envidia, avaricia, mezquindad y falta de escrúpulos. ¡Fue realmente una némesis justa!";
		link.l1 = "Camilla... ¡Debí haber sabido que había algo malo con esa chica!";
		link.l1.go = "enrico_3";
		break;

	case "enrico_3":
		dialog.text = "Una chica llamada Camilla había estado viviendo una vida pacífica en Cartagena con su padre y hermanos, estaba a punto de casarse cuando tú y tus demonios atacaron la ciudad. Tus piratas mataron a todos los que estaban cerca de ella, así que juró hacer lo que fuera necesario para vengarlos. Fue un papel difícil de interpretar para ella. Incluso tuvo que acostarse con un bastardo responsable de las muertes de su familia. Temo imaginar lo que ella sentía durante el acto.\nLa pobre chica pasó días en la iglesia rezando por el perdón. Donó los doblones sangrientos que le diste a las víctimas que más sufrieron por tu ataque. Ahora está en un monasterio, pobre alma. ¡Has destrozado su vida, escoria! ¡Piénsalo! ¡Piensa en cuántas Camillas, Isabelas, Rositas has violado y dejado viudas! ¡Cuántos Juans, Carloses, Pedros tus bastardos han matado y torturado!\n¡Recuerda Mérida! ¡Recuerda cómo prometiste al jefe del pueblo no prenderle fuego y luego quemaste todo el lugar hasta los cimientos!";
		link.l1 = "¡Nunca pretendí hacerlo! Cuando salí de la residencia, el fuego ya estaba por todas partes. No ordené esto...";
		link.l1.go = "enrico_4";
		break;

	case "enrico_4":
		dialog.text = "Eres responsable de los actos de tus piratas. ¡Hombres muertos cuelgan de tu cuello y pronto te arrastrarán al infierno!";
		link.l1 = "¡Ven entonces! ¿Eh? ¡Lucha conmigo! ¡Esto es lo que quieres, ¿verdad?! ¡Hagámoslo entonces!";
		link.l1.go = "enrico_5";
		break;

	case "enrico_5":
		PlaySound("Voice\Spanish\LE\Zorro\Don_Enriko_03.wav");
		if (CharacterIsAlive("Tonzag") && CheckPassengerInCharacter(pchar, "Tonzag"))
		{
			dialog.text = "No, Charlie Prince. No agarres tu arma, es inútil... Podría matarte fácilmente, sin embargo, una muerte rápida no es suficiente para un bastardo como tú. Te quedarás en este calabozo para siempre. La puerta por la que entraste aquí está bloqueada por una piedra afuera, la puerta detrás de mí también será bloqueada, además hay también barras sólidas protegiéndola. Esto es todo, no hay salida excepto por estas dos puertas.\n¿Qué demonios...? ¡Cerré todas las puertas!";
			link.l1 = "¿Qué está pasando...?";
			link.l1.go = "exit";
			AddDialogExitQuest("Mtraxx_RetributionEnricoAndTonzag");
		}
		else
		{
			dialog.text = "No, Charlie Prince. No saques tu arma, es inútil... Podría matarte fácilmente, sin embargo, una muerte rápida no es suficiente para un bastardo como tú. Te quedarás en este calabozo para siempre. La puerta por la que entraste está bloqueada por una piedra afuera, la puerta detrás de mí también será bloqueada, además, hay rejas robustas protegiéndola. Esto es todo, no hay salida excepto por estas dos puertas.\nHay agua abajo, así que tendrás suficiente tiempo para reflexionar sobre tus acciones. Completamente solo aquí, en la oscuridad, quizás te arrepientas de lo que has hecho antes de morir de hambre o enloquecer.\nUna última cosa: el tesoro abajo es falso. Los lingotes de oro no son más que plomo pintado. Sin embargo, los doblones son reales, pero solo hay unos pocos, suficientes para cubrir las rocas dentro de los cofres. Un final digno para piratas, ¿eh? Se mataron entre ustedes por un tesoro falso, Prince. Adiós ahora. Reza por tu alma pecadora, Charlie Prince, si aún recuerdas cómo...";
			// belamour legendary edition -->
			link.l1 = "¡Acabo de matar a toda la vanguardia de Marcus Tyrex! ¿Crees que estas barras oxidadas me detendrán? ¡Las romperé con tu propia cabeza!";
			link.l1.go = "enrico_5a";
			link.l2 = "Tal vez lo merecía. ¡Pero no me rendiré, ¿me oyes?! ¡Encontraré una manera, siempre lo hago!";
			link.l2.go = "enrico_5b";
		}
		break;

	case "enrico_5a":
		AddCharacterHealth(pchar, 5);
		AddCharacterExpToSkill(pchar, "FencingL", 400);
		AddCharacterExpToSkill(pchar, "FencingS", 400);
		AddCharacterExpToSkill(pchar, "FencingH", 400);
		AddCharacterExpToSkill(pchar, "Pistol", 400);
		DialogExit();
		AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;

	case "enrico_5b":
		AddCharacterExpToSkill(pchar, "Leadership", 1200);
		ChangeCharacterComplexReputation(pchar, "nobility", 15);
		DialogExit();
		AddDialogExitQuestFunction("Mtraxx_RetributionEnricoGo");
		break;
		// <-- legendary edition

	case "enrico_Tonzag_1":
		dialog.text = "Tienes razón, la puerta es confiable, aunque vieja. Gracias por no bajar la reja—me habría retrasado. Pero no por mucho tiempo.";
		link.l1 = "¡Hércules Tonzag, Gastón Calvo! Debería haber adivinado que alguien como tú se uniría a Prince y toda su calaña. Suerte la mía encontrarte aquí, también.";
		link.l1.go = "enrico_Tonzag_2";
		sld = CharacterFromID("Zorro");
		CharacterTurnToLoc(sld, "quest", "door");
		break;

	case "enrico_Tonzag_2":
		dialog.text = "¿Afortunado, dices? Bueno, si tienes prisa por morir... Aunque pensé que no, ya que lo dejaste morir de hambre en lugar de enfrentarlo.";
		link.l1 = "¿Acusarme de cobardía? Qué insensato de tu parte. Como le dije a Prince, la muerte es un castigo demasiado fácil para él. No es rival para mí.";
		link.l1.go = "enrico_Tonzag_3";
		break;

	case "enrico_Tonzag_3":
		dialog.text = "Y no eres rival para mí, Don.";
		link.l1 = "Hace diez años? Ciertamente. ¿Ahora? Apenas. Además...";
		link.l1.go = "enrico_Tonzag_4";
		break;

	case "enrico_Tonzag_4":
		dialog.text = "¿Además de qué? ¿Por qué la pausa dramática? Aunque, considerando tu máscara de carnaval... Un poco pronto para descartarme, ¿no crees?";
		link.l1 = "Has roto la puerta, pero la fuerza bruta no será suficiente conmigo. ¿Cómo están tus reflejos? ¿Tu visión? Con un solo ojo. Yo todavía tengo los dos.";
		link.l1.go = "enrico_Tonzag_5";
		break;

	case "enrico_Tonzag_5":
		dialog.text = "Bueno, por ahora, de todos modos. Je-je.";
		link.l1 = "¡Por Portobello, mereces un tormento peor que el de Prince!";
		link.l1.go = "enrico_Tonzag_6";
		break;

	case "enrico_Tonzag_6":
		dialog.text = "¿Oh, así que has oído lo que hice? Supongo que seguirán chismeando sobre eso entre los tuyos por un tiempo. Entonces sabes por lo que he pasado.";
		link.l1 = "Eres viejo, Tonzag, y esta vez tu arrogancia será tu perdición. Y sí, no solo lo oí - Cartagena y Mérida son obra tuya. Al igual que Portobello.";
		link.l1.go = "enrico_Tonzag_7";
		break;

	case "enrico_Tonzag_7":
		dialog.text = "Lo habría tomado como un halago, pero no, no es obra mía. Aunque puede parecer similar, desde lejos. Demasiado amateur. Sin embargo, incluso en Portobello, hubo... incidentes.";
		link.l1 = "¿¡Incidentes?! Ese día, una persona murió... Y considerando que tú comenzaste esa masacre, aún te culpo por ello, incluso si no mataste a todos tú mismo. Te culpo por cada 'incidente'.";
		link.l1.go = "enrico_Tonzag_8";
		break;

	case "enrico_Tonzag_8":
		dialog.text = "Una persona, dices... Muchos murieron ese día. Sé específico.";
		link.l1 = "¡Verdaderamente, no tienes corazón si puedes decir eso! Pero responderé: aquel que no deberías haber matado. Mi padre, Don de la Vega. Si él estuviera vivo, no habría tomado este camino, y todos ustedes seguirían con vida.";
		link.l1.go = "enrico_Tonzag_9";
		break;

	case "enrico_Tonzag_9":
		dialog.text = "Cierra la boca, mocoso. Mi querida esposa... también murió allí.";
		link.l1 = "¿Esperas condolencias? No las obtendrás. Esa es la condena del Señor para ti. Parece que sí tienes un corazón, pequeño y negro. Y lo encontraré con mi espada.";
		link.l1.go = "enrico_Tonzag_10";
		break;

	case "enrico_Tonzag_10":
		dialog.text = "¡Oh, los dramas sobre mi corazón! Te equivocas si piensas que has visto peor de lo que yo he visto.";
		link.l1 = "¿Crees que soy solo un joven rico y mimado derrochando dinero? ¡Sepas esto: no he gastado ni un doblón en juegos de azar o mujeres! ¡Lo he invertido todo en la lucha contra tipos como tú y he dedicado mi vida a ello!";
		link.l1.go = "enrico_Tonzag_11";
		break;

	case "enrico_Tonzag_11":
		dialog.text = "¿Y para qué? No parece muy exitoso. Las rutas comerciales todavía están llenas de piratas. Estás solo en tu cruzada. Y ellos son toda una legión.";
		link.l1 = "Alguien tiene que hacerlo. Al menos alguien. Y tal vez, matando solo a un capitán pirata, salvaré algunas vidas.";
		link.l1.go = "enrico_Tonzag_12";
		break;

	case "enrico_Tonzag_12":
		dialog.text = "Insensato. Idealista. Y... en cierto modo, noble, diría yo, si no fuera por tus métodos. Deshonroso, como tus enemigos. Al final, no eres... mejor.";
		link.l1 = "¡No me sermonees! El honor es para aquellos que siguen sus leyes. Te entiendo. Pienso como tú. Y castigo.";
		link.l1.go = "enrico_Tonzag_13";
		break;

	case "enrico_Tonzag_13":
		dialog.text = "Tienes razón. Enseñarte es inútil. Así que no nos separaremos pacíficamente. Pero me importas un bledo, Don Enrico. Ni siquiera vales mi tiempo.";
		link.l1 = "¿Qué quieres de...?";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionEnricoAndTonzag2");
		break;

	case "enrico_Tonzag_14": // после выстрела в Зорро в подземелье
		dialog.text = "¿Está bien, Capitán? Le advertí que tuviera cuidado. Debería haber escuchado mi instinto.";
		link.l1 = "Sí, estoy bien. Gracias, Hércules. Solo un poco...";
		link.l1.go = "enrico_Tonzag_15";
		break;

	case "enrico_Tonzag_15":
		dialog.text = "...¿conmocionado? No tengas miedo de admitirlo, es normal para alguien de tu edad y en una situación como esta. Además, ese Don es un buen manipulador.";
		link.l1 = "Ajá. Aunque, parecía tenerte miedo. Eso me sorprendió. Pero también me hizo volver en sí. Por cierto, ¿todavía está vivo? Parece que sí. No deberías darle la espalda.";
		link.l1.go = "enrico_Tonzag_16";
		break;

	case "enrico_Tonzag_16":
		dialog.text = "Vivo, pero aturdido. Recuperando el sentido. Debería haber apuntado a la cabeza, no al torso - resulta que nuestro noble hidalgo lleva una coraza ligera pero resistente bajo su abrigo. Je, incluso Fleetwood se conformó con un simple jubón. De lo contrario, ya habría un charco de sangre aquí.";
		link.l1 = "¿Y cómo terminaste aquí? ¿En el mismo lugar que él?";
		link.l1.go = "enrico_Tonzag_17";
		break;

	case "enrico_Tonzag_17":
		dialog.text = "Ahora no hay tiempo para eso. Pronto se pondrá de pie. Por ahora, levantaremos esta puerta.";
		link.l1 = "Nosotros... ¿qué?? Claro, podrías ser Hércules, pero...";
		link.l1.go = "enrico_Tonzag_18";
		break;

	case "enrico_Tonzag_18":
		dialog.text = "Los hombres de mi juventud fueron forjados duros. Estas bisagras tienen pernos cortos. Vamos, échame una mano, Capitán - podría ser Hércules, pero estoy envejeciendo.";
		link.l1 = "¡Bien, a la de tres! ¡Y levanta!";
		link.l1.go = "enrico_Tonzag_19";
		break;

	case "enrico_Tonzag_19":
		DialogExit();
		locCameraSleep(true);
		LAi_FadeLong("Mtraxx_RetributionEnricoAndTonzag6", "");
		break;

	case "enrico_Tonzag_20": // окружили Зорро
		dialog.text = "¿Crees que has arruinado todos mis planes y ganado? Eso fue inesperado, por supuesto, ¡pero aún he tenido en cuenta mucho!";
		link.l1 = "Como esa coraza ligera bajo tus ropas. ¿Por qué esa y no una completa encima? ¿Sólo para lucir tu abrigo?";
		link.l1.go = "enrico_Tonzag_21";
		break;

	case "enrico_Tonzag_21":
		dialog.text = "No soy una doncella, Prince. Mis razones son puramente prácticas: una coraza completa restringe demasiado mis movimientos. Cada quien tiene su propio enfoque.";
		link.l1 = "Sin embargo, aquí estoy, un francés, ya acostumbrado a llevar corazas, a diferencia de un español. La ironía. Entonces, ¿qué ahora? No pudiste atraparnos. Te has preparado para todo... ¿Figuraba un duelo entre las posibilidades? ¿O es la espada - e incluso la coraza - para todo excepto las peleas reales?";
		link.l1.go = "enrico_Tonzag_22";
		break;

	case "enrico_Tonzag_22":
		dialog.text = "¿Intentas llamarme cobarde también? Como dije, mereces un largo sufrimiento, no la muerte en un duelo. ¿Cuál es el sentido si tus almas no tendrán tiempo de soportar y comprender todos tus pecados aquí, en la Tierra?";
		link.l1 = "El camino al infierno está empedrado de buenas intenciones, como dicen... ¿Y no mancillaría atormentar a tus víctimas tu propia alma?";
		link.l1.go = "enrico_Tonzag_23";
		break;

	case "enrico_Tonzag_23":
		dialog.text = "Jamás. Nunca. Porque sigo fiel a mí mismo y a mis principios.";
		link.l1 = "Ajá, no como nosotros. Has dicho tanto sobre cómo somos una vil escoria sin un ápice de honor, así que... ¿por qué no estar a la altura de tus expectativas? Nos encargaremos de ti nosotros mismos. Juntos.";
		link.l1.go = "enrico_Tonzag_24";
		link.l2 = "Tengo una propuesta para usted, Don Enrico. Le desafío a un duelo, aquí y ahora. Como noble a noble.";
		link.l2.go = "enrico_Tonzag_26";
		break;

	case "enrico_Tonzag_24":
		dialog.text = "Hm-m. De lo contrario, no tendrías ninguna oportunidad. Tonzag será complicado, por supuesto... Así que me ocuparé de ti primero.";
		link.l1 = "Como si te dejara hacer eso.";
		link.l1.go = "enrico_Tonzag_25";
		ChangeCharacterComplexReputation(pchar, "nobility", -5);
		AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

	case "enrico_Tonzag_25":
		DialogExit();
		EndQuestMovie();
		LAi_SetFightMode(pchar, true);

		sld = CharacterFromID("Tonzag");
		LAi_SetImmortal(sld, false);
		LAi_SetCheckMinHP(sld, 1, true, "TonzagRanen");
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);

		sld = CharacterFromID("Zorro");
		LAi_SetImmortal(sld, false);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");

		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionEnricoAndTonzag7");
		break;

	case "enrico_Tonzag_26":
		dialog.text = "¿Tú? ¿Un noble? Tal vez seas un 'Prince', pero dudo que haya una gota de sangre noble en ti.";
		link.l1 = "Me has revelado tu verdadero nombre. Te revelaré el mío. Soy Charles de Maure. Y hemos insultado el honor del otro lo suficiente como para que cada uno de nosotros, tenga el derecho de exigir satisfacción. Defiéndete, Don Enrico.";
		link.l1.go = "enrico_Tonzag_27";
		ChangeCharacterComplexReputation(pchar, "nobility", 5);
		AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;

	case "enrico_Tonzag_27":
		dialog.text = "Pero no te arrepientas de tu decisión más tarde.";
		link.l1 = "He lamentado muchas decisiones en mi vida, pero esta no será una de ellas. ¡En guardia!";
		link.l1.go = "enrico_Tonzag_28";
		break;

	case "enrico_Tonzag_28":
		DialogExit();
		EndQuestMovie();
		LAi_SetFightMode(pchar, true);

		sld = CharacterFromID("Tonzag");
		LAi_SetImmortal(sld, true);
		LAi_SetActorType(sld);

		sld = CharacterFromID("Zorro");
		LAi_SetImmortal(sld, false);
		LAi_SetWarriorType(sld);
		LAi_group_MoveCharacter(sld, "EnemyFight");

		LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
		LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
		LAi_group_SetCheck("EnemyFight", "Mtraxx_RetributionEnricoAndTonzag7");
		break;

	case "enrico_Tonzag_29": // после победы над Зорро
		dialog.text = "¿Está bien, capitán? Nuestro noble hidalgo no solo llevaba una coraza, sino que también envenenó su hoja. Aquí, tome esto. Siempre llevo un par conmigo cuando camino por la jungla; nunca se sabe cuándo puede morder una serpiente o un piel roja puede lanzar un dardo envenenado.";
		link.l1 = "Gracias, Hércules. Estoy bien. Tu llegada oportuna me ayudó a recomponerme.";
		link.l1.go = "enrico_Tonzag_30";
		GiveItem2Character(PChar, "potion3");
		LAi_UseAtidoteBottle(pchar);
		LAi_UseAtidoteBottle(npchar);
		break;

	case "enrico_Tonzag_30":
		dialog.text = "No lo menciones. Vamos, te sacaré de aquí, mencionó bloquear la entrada con piedras. Encontré otro pasaje, un atajo.";
		link.l1 = "Dime, Hércules... ¿qué sucedió exactamente en Portobello? ¿Y cuándo?";
		link.l1.go = "enrico_Tonzag_31";
		break;

	case "enrico_Tonzag_31":
		dialog.text = "No estoy de humor para hablar de eso hoy. Pero quizá algún día, con una copa de vino o algo más fuerte. Por ahora, salgamos de aquí, el mocoso tenía razón, me estoy haciendo viejo. Quiero descansar en el barco.";
		link.l1 = "Entonces guía el camino.";
		link.l1.go = "enrico_Tonzag_32";
		break;

	case "enrico_Tonzag_32":
		DoQuestReloadToLocation("Shore10", "goto", "goto2", "Mtraxx_RetributionEnricoAndTonzag8");
		break;

	case "mishelle_sleep":
		dialog.text = "Cuéntame, hermano, ¿cómo te convertiste en tal abominación? Cuando te dije que te familiarizaras con los piratas, no me refería a quemar ciudades, matar a civiles inocentes y torturar mujeres. Incluso una guerra se puede pelear con honor y dignidad.\nEres una vergüenza para nuestra familia. Menos mal que nuestro padre no está aquí: habría muerto de vergüenza al saber que su hijo se había convertido en un pirata y bandido.";
		link.l1 = "";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionSleep5");
		break;

	case "mishelle_sleep_1":
		dialog.text = "¡Hermano! ¡Hermano!\n¿Puedes oírme?\nHay un pasaje detrás de una de las dos puertas. La puerta se puede abrir. ¡Una llave está cerca de ti!\nEncuéntrala en las escaleras. ¡En las escaleras!";
		link.l1 = "";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionSleep7");
		break;

	case "terrax_sleep":
		dialog.text = "¡Ja-ja-ja, hola, mi valiente filibustero! ¿Por qué estás tan triste? El mar, el oro, el ron y las mujeres, ¿qué más te falta? ¿Recuerdas nuestro primer encuentro? Te dije entonces - necesito hombres que no teman el olor de la pólvora ni desangrar ríos rojos. ¡Has superado todas mis expectativas! ¡Te has convertido en un verdadero pirata, Charlie Prince! ¡Ja-ja-ja!";
		link.l1 = "";
		link.l1.go = "terrax_sleep_1";
		locCameraSleep(false);
		break;

	case "terrax_sleep_1":
		dialog.text = "¡Un verdadero maldito pirata! ¡Ah-ah-ja-ja!";
		link.l1 = "";
		link.l1.go = "terrax_sleep_2";
		break;

	case "terrax_sleep_2":
		Mtraxx_RetributionSleepSkeletons();
		dialog.text = "¡Ua-ja-ja-ja-ja-ja!!!";
		link.l1 = "";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionSleep6");
		break;

	// belamour legendary edition -->
	case "SlavesTrader":
		dialog.text = "¿Quién eres? ¿Qué haces aquí? ¡Responde rápido!";
		link.l1 = "Soy de Fadey, vine por un lote de huesos negros. Debería haberte advertido.";
		link.l1.go = "SlavesTrader_1";
		break;

	case "SlavesTrader_1":
		dialog.text = "¡Ja! No te preocupes por la piel, amigo. Te reconocimos, Moscovit dio una descripción con gran detalle. También pidió que no te ofendieras por el precio. Así que, teniendo en cuenta el pago anticipado ya hecho, son 10 000 de plata. O, si pagas en oro, entonces solo 50 doblones. Bueno, ¿qué has decidido? ¡No le tires del rabo al gato!";
		if (PCharDublonsTotal() >= 50)
		{
			link.l1 = "Pagaré 50 doblones. Es más rentable.";
			link.l1.go = "SlavesTrader_Dub";
		}
		if (sti(Pchar.money) >= 10000)
		{
			link.l2 = "Pagaré 10 000 pesos.";
			link.l2.go = "SlavesTrader_P";
		}
		link.l3 = "Lo siento, pero no puedo permitirme esclavos en este momento.";
		link.l3.go = "SlavesTrader_X";
		break;

	case "SlavesTrader_Dub":
		RemoveDublonsFromPCharTotal(50);
		dialog.text = "Eso es genial. Señala a tus hombres que tomen las mercancías.";
		link.l1 = "Por supuesto.";
		link.l1.go = "SlavesTrader_End";
		break;

	case "SlavesTrader_P":
		AddMoneyToCharacter(pchar, -10000);
		dialog.text = "Eso es genial. Da la señal a tus hombres para que tomen la mercancía.";
		link.l1 = "Ciertamente.";
		link.l1.go = "SlavesTrader_End";
		break;

	case "SlavesTrader_End":
		DialogExit();
		AddQuestRecord("Roger_3", "25");
		pchar.questTemp.Mtraxx.GiveMeSlaves = "Deal";
		SetCharacterGoods(pchar, GOOD_SLAVES, (GetCargoGoods(pchar, GOOD_SLAVES) + 50));
		Log_Info("Has enviado cincuenta esclavos a " + PChar.Ship.Name);
		for (i = 1; i <= 3; i++)
		{
			sld = characterFromId("Mtraxx_SlavesSeller" + i);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
		}
		chrDisableReloadToLocation = false;
		LAi_LocationFightDisable(&Locations[FindLocation("Shore29")], false);
		DeleteAttribute(&locations[FindLocation("Shore29")], "DisableEncounters"); // энкаунтеры открыть
		break;

	case "SlavesTrader_X":
		dialog.text = "Bueno, como desees. Siempre habrá un comprador para este producto. Nos vemos, amigo.";
		link.l1 = "Adiós.";
		link.l1.go = "SlavesTrader_EndX";
		break;

	case "SlavesTrader_EndX":
		DialogExit();
		AddQuestRecord("Roger_3", "26");
		pchar.questTemp.Mtraxx.GiveMeSlaves = "WithoutSlaves";
		for (i = 1; i <= 3; i++)
		{
			sld = characterFromId("Mtraxx_SlavesSeller" + i);
			ChangeCharacterAddressGroup(sld, "none", "", "");
			sld.lifeday = 0;
		}
		chrDisableReloadToLocation = false;
		LAi_LocationFightDisable(&Locations[FindLocation("Shore29")], false);
		DeleteAttribute(&locations[FindLocation("Shore29")], "DisableEncounters"); // энкаунтеры открыть
		break;
	// диалог Гаспара Златозубого Xenon
	case "GasparGold_meeting":
		dialog.text = "Saludos, Capitán. ¿Eres Charlie Prince si no me equivoco? No te preocupes, mis paredes no tienen oídos. Honestamente, no me importa cuál sea tu nombre. Lo que importa es que me recomendaron, lo que significa que podemos hacer negocios.";
		link.l1 = "Saludos a ti también, Gaspard 'Dientedeoro'. Aunque, pensándolo bien, tampoco me importa cómo te llames. ¿Escuché que podrías estar interesado en comprar algunas chucherías?";
		link.l1.go = "GasparGold_meeting_01";
		break;

	case "GasparGold_meeting_01":
		dialog.text = "Eso es correcto. Nadie te ofrecerá un mejor precio que yo. Bueno, tal vez los prestamistas, pero no compran mucho. Estoy listo para comprar todo lo que ofrezcas. Ni siquiera tienes que llevarme los objetos de valor personalmente: tengo una puerta trasera que lleva a un muelle apartado. No dudes en venderme todas las chucherías que tienes guardadas en los cofres de tu barco.";
		link.l1 = "¡Bueno, eso es excelente! Encantado de conocerte.";
		link.l1.go = "GasparGold";
		break;

	case "GasparGold_story":
		npchar.mtraxx.story = true;
		dialog.text = "Ahora, eso es asunto mío personal. Prefiero que no te entrometas. Solo diré que tengo todo bajo control, así que puedes comerciar conmigo sin riesgos. El resto no es de tu incumbencia.";
		link.l1 = "¡Bueno, lo que más importa es que no haya riesgos! Hay algo más que quería preguntar...";
		link.l1.go = "GasparGold";
		break;

	case "GasparGold":
		NextDiag.TempNode = "GasparGold";
		dialog.text = "¿Cómo puedo ayudar? ¿Quieres deshacerte de algunas perlas o gemas extra? ¿Quizás oro, plata, joyas? Lo compraré todo.";
		if (!CheckAttribute(npchar, "mtraxx.story"))
		{
			link.l1 = "Di, ¿cómo es ser un comprador de bienes robados? ¿No temes a las autoridades?";
			link.l1.go = "GasparGold_story";
		}
		link.l2 = "Tengo algo aquí... Quiero cambiarlo por unas monedas de verdad.";
		link.l2.go = "GasparGold_01";
		break;

	case "GasparGold_01":
		dialog.text = "Bueno, hagamos el intercambio. ¿Doblones o pesos?";
		link.l1 = "Vayamos con pesos - no hay necesidad de doblones. El dinero corriente es aceptado en todas partes.";
		link.l1.go = "GasparGold_peso";
		link.l2 = "Adivinaste, necesito específicamente doblones. Así que solo venderé por ellos.";
		link.l2.go = "GasparGold_dub";
		link.l3 = "No tengo nada a la venta ahora mismo. Solo quería asegurarme de que estés listo para comprar artículos preciosos cuando los tenga. ¡Hasta la próxima!";
		link.l3.go = "exit";
		break;

	// окно торговли
	case "GasparGold_peso":
		Nextdiag.CurrentNode = Nextdiag.TempNode;
		DialogExit();
		LaunchItemsTrade(NPChar, 0);
		break;

	case "GasparGold_dub":
		Nextdiag.CurrentNode = Nextdiag.TempNode;
		DialogExit();
		LaunchItemsTrade(NPChar, 1);
		break;

	// Диалоги после угроз вождю индейцев Кумване
	case "MeridaObsuzhdenie_Bad_1":
		dialog.text = "¿Todavía has recurrido a la intimidación, Cap? Escuché amenazas incluso desde afuera.";
		link.l1 = "Me dejaron sin elección. Le ofrecí regalos a la esposa de este Tagofa por su ayuda. Ni siquiera quiso escucharme. Ahora deja que el jefe hable con ellos. Y si no logra hacer entrar en razón a estos testarudos, le arrancaré el corazón del pecho con mis propias manos. Y, por cierto, ¿quién es Yahahu?";
		link.l1.go = "MeridaObsuzhdenie_Bad_2";
		ChangeShowIntarface();
		break;

	case "MeridaObsuzhdenie_Bad_2":
		dialog.text = "No deberías haber arruinado las relaciones con los indios. Nosotros, los piratas, tenemos solo una espada y un barco como aliados. Pero si esta es tu decisión, que así sea. Y Yahahu es un demonio maligno. No sé nada más sobre él.";
		link.l1 = "...";
		link.l1.go = "MeridaObsuzhdenie_Bad_3";
		break;

	case "MeridaObsuzhdenie_Bad_3":
		StartInstantDialog("Mrt_Rocur", "MeridaObsuzhdenie_Bad_4", "Quest\Roger.c");
		break;

	case "MeridaObsuzhdenie_Bad_4":
		dialog.text = "Perder tiempo en la persuasión, Leprechaun - es insensato. ¿O prefieres renunciar al rico botín y mantener buenas relaciones con los indios?";
		link.l1 = "...";
		link.l1.go = "MeridaObsuzhdenie_Bad_5";
		break;

	case "MeridaObsuzhdenie_Bad_5":
		StartInstantDialog("Lepricon", "MeridaObsuzhdenie_Bad_6", "Quest\Roger.c");
		break;

	case "MeridaObsuzhdenie_Bad_6":
		dialog.text = "Preferiría conseguir ambos.";
		link.l1 = "No funcionará tener un pie en ambos campamentos. No esta vez. Basta de discusiones, ya todo está hecho. Mañana el jefe nos informará de la decisión de Tagofa, y espero que no me decepcione. De lo contrario... Tendré que tomar medidas extremas. Lo cual me gustaría evitar, por supuesto.";
		link.l1.go = "MeridaObsuzhdenie_Bad_7";
		break;

	case "MeridaObsuzhdenie_Bad_7":
		DialogExit();
		chrDisableReloadToLocation = false;
		DeleteAttribute(pchar, "GenQuest.CannotWait"); // разрешить отдыхать
		ChangeShowIntarface();

		sld = characterFromId("Lepricon");
		sld.dialog.Filename = "Quest\Roger.c";
		sld.dialog.currentnode = "lepricon_3";
		LAi_SetWarriorType(sld);

		sld = characterFromId("Mrt_Rocur");
		LAi_SetActorType(sld);
		LAi_ActorFollowEverywhere(sld, "", -1);
		break;

	case "MeridaObsuzhdenie_Good_1":
		dialog.text = "Bueno, ¿cómo van las cosas? ¿Tendremos un guía?";
		link.l1 = "No, Jean, no lo haremos. El jefe y toda la tribu temen a los Kapongs como el diablo teme al incienso. Parece que tendremos que abandonar nuestro plan.";
		link.l1.go = "MeridaObsuzhdenie_Good_2";
		ChangeShowIntarface();
		break;

	case "MeridaObsuzhdenie_Good_2":
		StartInstantDialog("Lepricon", "MeridaObsuzhdenie_Good_3", "Quest\Roger.c");
		break;

	case "MeridaObsuzhdenie_Good_3":
		dialog.text = "Terrax no estará contento con este giro de los acontecimientos.";
		link.l1 = "¿Crees que estoy increíblemente feliz de que las cosas resultaran así? Los cobardes Lokono no quieren meterse con los Kapongs. No se sienten tentados ni por la persuasión ni por las recompensas.";
		link.l1.go = "MeridaObsuzhdenie_Good_4";
		break;

	case "MeridaObsuzhdenie_Good_4":
		StartInstantDialog("Mrt_Rocur", "MeridaObsuzhdenie_Good_5", "Quest\Roger.c");
		break;

	case "MeridaObsuzhdenie_Good_5":
		dialog.text = "Entonces tendremos que usar amenazas. Diles que quemarás su maldito pueblo hasta los cimientos y torturarás a los que sobrevivan hasta que alguien acepte guiarnos.";
		link.l1 = "Jean, ¿has perdido completamente la cabeza? No voy a quemar las casas de gente inocente. Y ciertamente no voy a torturarlos.";
		link.l1.go = "MeridaObsuzhdenie_Good_6";
		break;

	case "MeridaObsuzhdenie_Good_6":
		dialog.text = "Charlie Prince es un modelo de benefactor. Nunca esperé tales arrebatos de ternura de ti.";
		link.l1 = "Esto no es ternura, Guapo. Bueno, torturaremos a un indio hasta la muerte. Por venganza, él nos llevará directamente a las manos de los Kapongs y desaparecerá por senderos que solo él conoce. No arriesgaré las vidas de mi gente así.";
		link.l1.go = "MeridaObsuzhdenie_Good_7";
		break;

	case "MeridaObsuzhdenie_Good_7":
		dialog.text = "En ese caso, Leprechaun y yo nos vamos. Aquí tienes cincuenta mil de plata por liberarme de las plantaciones de Maracaibo. Lo estaba guardando para un nuevo barco. Y mi consejo para ti: mantente fuera de la vista de Marcus por un tiempo. Adiós, Charles Prince.";
		link.l1 = "Adiós, Jean.";
		link.l1.go = "MeridaObsuzhdenie_Good_8";
		AddMoneyToCharacter(pchar, 50000);
		break;

	case "MeridaObsuzhdenie_Good_8":
		DialogExit();
		chrDisableReloadToLocation = false;
		ChangeShowIntarface();
		AddQuestRecord("Roger_5", "8b");
		CloseQuestHeader("Roger_5");

		sld = characterFromId("Lepricon");
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
		sld.location = "None";
		RemovePassenger(pchar, sld);

		sld = characterFromId("Mrt_Rocur");
		LAi_type_actor_Reset(sld);
		LAi_SetActorType(sld);
		LAi_ActorGoToLocation(sld, "reload", "reload1", "", "", "", "", -1);
		sld.location = "None";
		RemovePassenger(pchar, sld);

		sld = characterFromId("Terrax");
		sld.dialog.currentnode = "First time";
		break;

	// Немезида. Диалоги с офицерами после взрыва бочонков с порохом
	// Тонзаг
	case "Nemezida_Tonzag_1":
		dialog.text = "¡Todos de la zona vendrán corriendo aquí ahora! ¿Estás seguro de que volar esos árboles fue una buena idea, Capitán?";
		link.l1 = "¡Maldita sea! Quizás hubiera sido mejor si todos trabajaran con hachas... Pero es demasiado tarde para eso ahora.";
		link.l1.go = "Nemezida_Tonzag_2";
		break;

	case "Nemezida_Tonzag_2":
		dialog.text = "Es cierto. Tendremos que arreglarnos con lo que tenemos. Prepárate.";
		link.l1 = "Tú también, Hércules.";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;

	case "Nemezida_Tonzag_3":
		dialog.text = "Siguen viniendo por este camino. Entonces, ¿deberíamos encargarnos también de estos?";
		link.l1 = "¿Y si no hay fin para ellos? No estamos aquí para este tipo de problemas.";
		link.l1.go = "Nemezida_Tonzag_4";
		PlaySound("interface\abordage_wining.wav");
		break;

	case "Nemezida_Tonzag_4":
		dialog.text = "Bueno, todo tiene un final... Pero tienes razón. Retirémonos. Y rápido.";
		link.l1 = "¡Apresurémonos!";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;

	case "Nemezida_Tonzag_5":
		dialog.text = "Tan implacables, nos han alcanzado. Hay un camino aquí, ¿deberíamos entrar? Será más fácil mantener la línea.";
		link.l1 = "Espera, Hercule. ¿Lo oyes? Ya hay alguien ahí dentro. Tú y los chicos encargaos de las cosas aquí. Yo entraré antes de que se lleven el tesoro; dudo que alguien haya entrado ahí por casualidad.";
		link.l1.go = "Nemezida_Tonzag_6";
		PlaySound("interface\abordage_wining.wav");
		break;

	case "Nemezida_Tonzag_6":
		dialog.text = "Está bien. Pero ten cuidado, tengo un mal presentimiento sobre esto.";
		link.l1 = "¡Tú también! Voy para allá.";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;

	case "Nemezida_Tonzag_7": // на берегу
		dialog.text = "¿Quieres decir algo, capitán? Has estado muy pensativo durante todo nuestro camino hasta el barco.";
		link.l1 = "Así es. He estado pensando en lo que he estado haciendo recientemente. Sobre Terrax y... a dónde me ha llevado. ¿He estado más cerca de salvar a mi hermano? ¿O de volver a casa?..";
		link.l1.go = "Nemezida_Tonzag_8";
		break;

	case "Nemezida_Tonzag_8":
		dialog.text = "Hm-m. Buenas preguntas. ¿Y cuáles son tus respuestas?";
		link.l1 = "Solo otra pregunta. Si antes no tenía sentido, ¿volverá a no tenerlo? Terrax no me ayudará. Ni con mi hermano, ni con Tortuga.";
		link.l1.go = "Nemezida_Tonzag_9";
		break;

	case "Nemezida_Tonzag_9":
		dialog.text = "Probablemente no. No le sirve de nada. Sorprendente que apenas te hayas dado cuenta. Pero ¿cuál es tu próxima pregunta?";
		link.l1 = "¿Por qué diablos estaba corriendo tras Terrax como un perrito faldero, sacándole las castañas del fuego todo este tiempo?!";
		link.l1.go = "Nemezida_Tonzag_10";
		break;

	case "Nemezida_Tonzag_10":
		dialog.text = "Ahora, esa es una buena pregunta. Una adecuada. ¿Tienes una respuesta esta vez?";
		link.l1 = "Más bien como una resolución. Tuve suerte hoy. ¿Pero tendré suerte de nuevo? Es importante saber cuándo detenerse. Y... respetarse a uno mismo. Ya he tenido suficiente.";
		link.l1.go = "Nemezida_Tonzag_11";
		break;

	case "Nemezida_Tonzag_11":
		dialog.text = "¿Has decidido terminar tu asociación con Terrax?";
		link.l1 = "Sí. Tengo cosas más importantes que hacer. Familia, amigos. Con ellos, lograré mis objetivos. Y no de esta manera. Y aunque lo haga... no será con Marcus. Seré mi propio amo. Tomaré mis propias decisiones.";
		link.l1.go = "Nemezida_Tonzag_12";
		break;

	case "Nemezida_Tonzag_12":
		dialog.text = "El hombre al que una vez seguí está hablando de nuevo. No te enredes otra vez con la gente equivocada. No desperdicies el potencial que una vez me intrigó.";
		link.l1 = "Entendido, Hércules. Y gracias de nuevo. Esta vez, por ayudarme a darme cuenta plenamente. Ya no soy el tal 'Prince', sólo un lacayo. Soy Charles de Maure, un noble orgulloso. Abordemos el barco - ambos estamos cansados.";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionFinal_Tonzag");
		break;

	// Книппель
	case "Nemezida_Knippel_1":
		dialog.text = "¡Eso fue un maldito estallido, señor - knippel a mi popa! Sonó justo como una andanada del Valkyrie. Pero me temo que esos tipos de allí también lo notaron...";
		link.l1 = "Si lo notaron, ese es su problema. Nadie los invitó aquí. ¿Listo para darles una lección, Charlie?";
		link.l1.go = "Nemezida_Knippel_2";
		break;

	case "Nemezida_Knippel_2":
		dialog.text = "¡Siempre listo, señor!";
		link.l1 = "Excelente. Vamos a ello.";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;

	case "Nemezida_Knippel_3":
		dialog.text = "Tengo miedo de que vayamos a tener más compañía, Capitán. ¿Cuáles son sus órdenes?";
		link.l1 = "Iremos más adentro en la jungla y nos esconderemos... No hay manera de defendernos de todos, y de todos modos no estamos aquí para eso.";
		link.l1.go = "Nemezida_Knippel_4";
		PlaySound("interface\abordage_wining.wav");
		break;

	case "Nemezida_Knippel_4":
		PlaySound("VOICE\Spanish\hambit\Charlie Knippel-08.wav");
		dialog.text = "¡Sí, capitán!";
		link.l1 = "¡Muy bien, andando!";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;

	case "Nemezida_Knippel_5":
		dialog.text = "¡Nos han rastreado, Capitán! Pero podemos refugiarnos aquí, parece que este camino lleva a algún lugar, aunque creo que ya hay alguien ahí.";
		link.l1 = "¡No vamos a refugiarnos! Parece que alguien más se enteró del tesoro. Aquí está el plan: Iré a ver qué está pasando antes de que se lo lleven todo, y tú los retendrás aquí con los muchachos.";
		link.l1.go = "Nemezida_Knippel_6";
		PlaySound("interface\abordage_wining.wav");
		break;

	case "Nemezida_Knippel_6":
		PlaySound("VOICE\Spanish\hambit\Charlie Knippel-08.wav");
		dialog.text = "Sí, capitán.";
		link.l1 = "Excelente. ¡Bajo ahora! Confío en que manejarás las cosas aquí.";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;

	case "Nemezida_Knippel_7": // на берегу
		dialog.text = "Khe-khe... ¿Está... bien, señor?";
		link.l1 = "¡Charlie! Has elegido el momento perfecto para preocuparte por mí. Guarda tus palabras. ¿Estás aguantando? Debería haberte dejado en el barco y haber llevado más hombres en su lugar...";
		link.l1.go = "Nemezida_Knippel_8";
		break;

	case "Nemezida_Knippel_8":
		dialog.text = "Ah, solo un rasguño, señor. Un poco cansado. ¡Nunca he peleado así, ni siquiera en mis días de juventud! ¡Pero les di tal paliza que oirán los knippels por la eternidad!";
		link.l1 = "¡Marina Real, a la antigua! Parece que luchaste como un león, Charlie. Pero aún así, apenas puedes mantenerte en pie. No presumas, ¿qué tan grave es la herida?";
		link.l1.go = "Nemezida_Knippel_9";
		break;

	case "Nemezida_Knippel_9":
		dialog.text = "No es nada grave, Capitán, solo agotamiento. La entrada detrás de usted colapsó casi de inmediato, y seguimos defendiéndonos de todos esos hombres durante mucho tiempo. Al final, me quedé solo, herido. Así que, hice mi camino aquí para despejar el camino y recibir primeros auxilios.";
		link.l1 = "Ya veo. Bien, hiciste tu parte hoy. En cuanto a mí... fracasé. Todos fuimos engañados y puestos unos contra otros para el entretenimiento de alguien—ni siquiera había ningún tesoro. Y no fui el único tonto allí.";
		link.l1.go = "Nemezida_Knippel_10";
		break;

	case "Nemezida_Knippel_10":
		dialog.text = "¿Fallaste?.. Pero estás vivo, señor. ¿Qué pasó? ¿Escapaste?";
		link.l1 = "No, pero aún había algo de correr involucrado. Lo siento, viejo amigo, pero lo que sucedió allí, no se lo contaré a nadie, ni siquiera a mis amigos más cercanos. Sin embargo, he sacado las conclusiones necesarias.";
		link.l1.go = "Nemezida_Knippel_11";
		break;

	case "Nemezida_Knippel_11":
		dialog.text = "¿Qué tipo de conclusiones, señor? No siempre entiendo tu razonamiento. Mi filosofía es simple: una buena culebrina y knippels en el mástil.";
		link.l1 = "Dime, debes haber matado a españoles antes, como yo hice recientemente. En tus días de la Armada Real. Y más tarde, con Fleetwood.";
		link.l1.go = "Nemezida_Knippel_12";
		break;

	case "Nemezida_Knippel_12":
		dialog.text = "Lo hice. Españoles, holandeses... y muchos otros también. Como Dick me dijo una vez, nuestro servicio es peligroso y exigente. Pero, ¿por qué preguntas? ¿Cuál es tu punto?";
		link.l1 = "Te explicaré. Pero primero, otra pregunta. ¿Alguna vez dudaste de lo que estabas haciendo y por qué lo hacías, Charlie?";
		link.l1.go = "Nemezida_Knippel_13";
		break;

	case "Nemezida_Knippel_13":
		dialog.text = "Mm-m. Me dije a mí mismo que actuaba por el bien de la Corona. Preocuparse por las órdenes es un trabajo ingrato; tienes que seguirlas de todos modos.";
		link.l1 = "La Corona... Bueno, tenías tus razones. Yo ni siquiera tenía eso - Michel me dijo que me acercara a Terrax. Pero ¿valieron la pena todos los sacrificios? ¿Me ayudó a mí o a él? Sí, sí, no nos gustan los dones... pero todos somos humanos.";
		link.l1.go = "Nemezida_Knippel_14";
		break;

	case "Nemezida_Knippel_14":
		dialog.text = "Creo que empiezo a entender a qué se refiere, señor.";
		link.l1 = "Bien. Dime, cuando Fleetwood se fue, ¿te alegraste de no tener que disparar más a los mercaderes holandeses? Algunos de ellos eran gente honesta.";
		link.l1.go = "Nemezida_Knippel_15";
		break;

	case "Nemezida_Knippel_15":
		dialog.text = "Nunca lo pensé, capitán. Pero diré esto: siempre he disfrutado servir con usted, señor. ¡Que me condenen con un nudo corredizo alrededor de mi cuello si estoy mintiendo! ";
		link.l1 = "Ja-ja-ja, está bien. Pero dime esto, ¿quién crees que lo tuvo peor? ¿Tú, siguiendo órdenes? ¿O yo, que no fui obligado a hacer lo que hice?";
		link.l1.go = "Nemezida_Knippel_16";
		break;

	case "Nemezida_Knippel_16":
		dialog.text = "No lo sé, señor...";
		link.l1 = "Ni yo. Pero no importa. Lo que importa es que ya no quiero tener nada que ver con Terrax. Basta es basta. No más Charlie Prince. Solo Charles de Maure.";
		link.l1.go = "Nemezida_Knippel_17";
		break;

	case "Nemezida_Knippel_17":
		dialog.text = "¿Pero no era esta parte de tu plan para salvar a tu hermano?";
		link.l1 = "Lo fue. Pero al final, no me ayudó en absoluto. Así que si alguna vez tengo que hacer algo así de nuevo, será solo mi decisión. Y solo si realmente me acerca a mi objetivo.";
		link.l1.go = "Nemezida_Knippel_18";
		break;

	case "Nemezida_Knippel_18":
		dialog.text = "Espero que sepas lo que estás haciendo, Capitán. Y que no termines como Terrax. O en la horca.";
		link.l1 = "Yo también lo espero. Pero de lo que estoy seguro es que mis objetivos e intereses serán lo primero de ahora en adelante. Ahora, ocupémonos de tus heridas.";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;

	// Лонгвэй
	case "Nemezida_Longway_1":
		dialog.text = "Tu explosión ha atraído atención, Lord Capitán. Parece que un escuadrón enemigo se está acercando a nosotros.";
		link.l1 = "¡Maldita sea! ...¿Crees que había una mejor manera de tratar con esos árboles? ¿Y qué habrías hecho tú?";
		link.l1.go = "Nemezida_Longway_2";
		break;

	case "Nemezida_Longway_2":
		dialog.text = "No lo sé. Pero sí sé qué hacer ahora: tratar con esa gente.";
		link.l1 = "Bueno, justo. Supongo que eso es exactamente lo que haremos.";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;

	case "Nemezida_Longway_3":
		dialog.text = "Nueva gente llega, Lord Capitán.";
		link.l1 = "Sí, lo he notado, gracias, Longway. Pero no tenemos tiempo para estos, así que retirémonos en la jungla - tal vez nos pierdan.";
		link.l1.go = "Nemezida_Longway_4";
		PlaySound("interface\abordage_wining.wav");
		break;

	case "Nemezida_Longway_4":
		dialog.text = "Hmm, podríamos manejarlos, por supuesto, pero como tú digas.";
		link.l1 = "No necesitamos esta pelea, así que movámonos.";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;

	case "Nemezida_Longway_5":
		dialog.text = "¡No nos darán tregua y nos atraparán, mi Señor Capitán! Te dije, deberíamos haberlos matado antes. ¿Deberíamos preparar una emboscada en esa cueva? Aunque parece que alguien ya está allí.";
		link.l1 = "¡Mejor preparar una emboscada aquí con los muchachos! Lo que no voy a perder es ese tesoro. Parece que alguien más se enteró del botín... Así que iré a echar un vistazo yo mismo.";
		link.l1.go = "Nemezida_Longway_6";
		PlaySound("interface\abordage_wining.wav");
		break;

	case "Nemezida_Longway_6":
		dialog.text = "Ten cuidado, Lord Capitán. Recuerda, incluso un gran dragón murió una vez sobre una montaña de oro.";
		link.l1 = "Tendré eso en cuenta, Longway. Tratemos todos de no morir hoy.";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;

	case "Nemezida_Longway_7": // на берегу
		dialog.text = "Señor Capitán, parece que logró escapar de allí.";
		link.l1 = "¿Sorprendido, Longway? Aunque debo admitir que yo mismo estoy algo sorprendido. Parece que eres el único que salió con vida. ¿Pero cómo lo lograste?";
		link.l1.go = "Nemezida_Longway_8";
		break;

	case "Nemezida_Longway_8":
		dialog.text = "Un grupo de gatos escuálidos no puede derrotar a un tigre. Un nido de serpientes no puede derribar a un dragón. Entre los hombres blancos, pocos son rivales dignos para mí.";
		link.l1 = "Pero recuerda, Longway, una jauría de perros puede destrozar a un león.";
		link.l1.go = "Nemezida_Longway_9";
		break;

	case "Nemezida_Longway_9":
		dialog.text = "¿Ahora el Capitán Señor comparte su sabiduría con Longway? Lástima que no escuchaste mi consejo antes.";
		link.l1 = "¿Sobre el dragón en la montaña de oro? Es cierto, casi me convertí en uno - casi muero, de hecho. Pero no en una montaña de oro - no había nada de eso. Lo que encontré en su lugar fue otra cosa, igualmente importante.";
		link.l1.go = "Nemezida_Longway_10";
		break;

	case "Nemezida_Longway_10":
		dialog.text = "La próxima vez, 'casi' podría no suceder. ¿Qué encontraste, Lord Capitán?";
		link.l1 = "Sí, ahora lo veo. Lo que encontré fue... sabiduría. Experiencia. Comprensión. Una decisión. Dime, Longway, ¿qué hemos estado haciendo últimamente?";
		link.l1.go = "Nemezida_Longway_11";
		break;

	case "Nemezida_Longway_11":
		dialog.text = "Somos piratas. Trabajando para tu nuevo amo, Lord Terrax. Contrabando, saqueo de pueblos, matanza, salvación y ayuda a su gente.";
		link.l1 = "Él no es mi amo, ¿sabes? ¡Pero maldita sea, lo has descrito todo tan perfectamente! Olvidé el orgullo, el respeto propio, y lo seguí como un perrito faldero.";
		link.l1.go = "Nemezida_Longway_12";
		break;

	case "Nemezida_Longway_12":
		dialog.text = "Longway te comprende, Lord Capitán. Yo también trabajé para van Merden y Rodenburg, olvidando el honor, el orgullo y el respeto por el bien de un objetivo querido.";
		link.l1 = "Cuéntame, ¿te condenas por eso? ¿Te odias a ti mismo?";
		link.l1.go = "Nemezida_Longway_13";
		break;

	case "Nemezida_Longway_13":
		dialog.text = "¿Condenar? A veces. ¿Odiar? No. Yo sé y recuerdo quién soy. Recuerdo mi meta, mi estrella guía. Nada es más importante en la vida. ¿Y tú tienes una meta?";
		link.l1 = "No una estrella guía como tú, pero aún así un objetivo importante, sí - rescatar a mi hermano. Pero me desvié de ese objetivo. Y eso es algo que no puedo permitirme repetir.";
		link.l1.go = "Nemezida_Longway_14";
		break;

	case "Nemezida_Longway_14":
		dialog.text = "Permíteme compartir contigo otra pieza de sabiduría del Imperio Celestial. No hay personas completamente buenas o malas. Cada persona posee tanto Yin, oscuridad e ignorancia, como Yang, luz y sabiduría. El equilibrio cambia dentro de cada uno.";
		link.l1 = "Así que, mi Yang es Charles de Maure. Y mi Yin es Charlie Prince. Aunque tal vez incluso Charles de Maure tendrá que tomar decisiones oscuras y difíciles algún día.";
		link.l1.go = "Nemezida_Longway_15";
		break;

	case "Nemezida_Longway_15":
		dialog.text = "Así es la vida, mi Señor Capitán. Cada persona está destinada a tomar decisiones tanto oscuras como luminosas.";
		link.l1 = "Aún así, la máscara de 'Prince' casi se fundió conmigo. Pero me la quitaré. Charles de Maure es un noble, no un chico de los mandados. De ahora en adelante, solo será así. Reclamo mi orgullo y dignidad. A partir de ahora, soy mi propio amo.";
		link.l1.go = "Nemezida_Longway_16";
		break;

	case "Nemezida_Longway_16":
		dialog.text = "Longway aprueba tu decisión, mi Lord Capitán.";
		link.l1 = "Gracias, Longway. Por cierto, ¿no te arrepientes de no ser un capitán libre? ¿Sirviéndome, como dices, 'a tu amo'?";
		link.l1.go = "Nemezida_Longway_17";
		break;

	case "Nemezida_Longway_17":
		dialog.text = "Hum. Longway extraña comandar su propio barco. Pero el mío reconoce el tuyo. Por mostrar respeto y sabiduría al mío, a diferencia del típico bárbaro blanco. Quizás el mío quisiera una vida diferente. Pero el mío no se arrepiente de ayudarte.";
		link.l1 = "Me alegra oír eso, Longway. Ahora... dejemos este lugar y el camino del Yin. Y traigamos más Yang a nuestras vidas. ¿Lo he dicho bien?";
		link.l1.go = "Nemezida_Longway_18";
		break;

	case "Nemezida_Longway_18":
		dialog.text = "Sí, eso es correcto. Espero que sigas un Dao mucho mejor de ahora en adelante.";
		link.l1 = "¿Dao?";
		link.l1.go = "Nemezida_Longway_19";
		break;

	case "Nemezida_Longway_19":
		dialog.text = "El Camino, Lord Capitán. O la Esencia. Pero en nuestro caso - el Camino.";
		link.l1 = "Sea cual sea el camino que me depare el futuro, no me desviaré nuevamente de lo que realmente importa. Vámonos de aquí, Longway.";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;

	// Тичингиту
	case "Nemezida_Tichingitu_1":
		dialog.text = "Capitán Charles, mucha gente viene en esta dirección. Tu señal de humo los ha atraído. Y claramente no son amigos nuestros.";
		link.l1 = "¡Oh, si tan solo fuera solo una 'señal de humo', como lo llamaste - resonó por toda la jungla. No hay elección - defendámonos. Definitivamente no necesitamos un ataque por la retaguardia de todo un escuadrón.";
		link.l1.go = "Nemezida_Tichingitu_2";
		break;

	case "Nemezida_Tichingitu_2":
		dialog.text = "¡Sí, Capitán Charles. Ataca primero!";
		link.l1 = "¡Ataquen! ¡No escatimen las balas!";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;

	case "Nemezida_Tichingitu_3":
		dialog.text = "¡Vienen más! Incluso más gente.";
		link.l1 = "¡Retírate a la jungla, Tichingitu! Nos esconderemos y esperaremos. ¡He venido por el tesoro, no para pelear!";
		link.l1.go = "Nemezida_Tichingitu_4";
		PlaySound("interface\abordage_wining.wav");
		break;

	case "Nemezida_Tichingitu_4":
		dialog.text = "Si es necesario, podemos tender una emboscada en la jungla.";
		link.l1 = "Cierto. Ahora, movámonos - rápidamente, pero en silencio.";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;

	case "Nemezida_Tichingitu_5":
		dialog.text = "¡Capitán Charles, mira! Hay un pasaje adelante. Y puedo escuchar pasos y voces desde allí.";
		link.l1 = "¿Alguien más se enteró del tesoro? ¡Maldita sea! ¿También oyes ese ruido detrás de nosotros? Parece que nos han alcanzado. ¡Tichingitu! Iré a ver qué hay delante. ¡Tú aguántalos con los muchachos!";
		link.l1.go = "Nemezida_Tichingitu_6";
		PlaySound("interface\abordage_wining.wav");
		break;

	case "Nemezida_Tichingitu_6":
		dialog.text = "¡Lo intentamos! ¡Tú ve!";
		link.l1 = "¡Cuento contigo!";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;

	case "Nemezida_Tichingitu_7": // на берегу
		dialog.text = "¡Capitán Charles! ¡Sobrevives! Tichingitu estará feliz por esto.";
		link.l1 = "Gracias, amigo mío. Yo también estoy feliz. Me alegra haber sobrevivido, y que tú estés bien. Parece que eres el único que queda de todo el escuadrón. ¿Eran muchos? Realmente los contuviste bien.";
		link.l1.go = "Nemezida_Tichingitu_8";
		break;

	case "Nemezida_Tichingitu_8":
		dialog.text = "Muchos. Pero el mío es uno de los mejores guerreros de nuestro pueblo Maskog. ¿Qué te pasó allí? ¿Encontraste el tesoro que buscabas?";
		link.l1 = "No, Tichingitu. Nos engañaron - no había tesoro. Dime, ¿qué piensas de lo que hemos estado haciendo últimamente?";
		link.l1.go = "Nemezida_Tichingitu_9";
		break;

	case "Nemezida_Tichingitu_9":
		dialog.text = "¿Qué hemos estado haciendo, Capitán Charles? Navegar. Derrotar a tus enemigos.";
		link.l1 = "Parece que no me entiendes.  Dime entonces, ¿estás triste por haber sido exiliado de tu tribu? ¿Quieres regresar, extrañas a tus hermanos? ";
		link.l1.go = "Nemezida_Tichingitu_10";
		break;

	case "Nemezida_Tichingitu_10":
		dialog.text = "Por supuesto, echo de menos a mis amigos y familia. Pero ¿volver? Mi hogar ya no existe sin... ella. Además, ¡está ese maldito coyote, el chamán!";
		link.l1 = "Lo siento, no quise mencionar eso. Sabes, recientemente me uní a una tribu, por así decirlo. Una tribu de capitanes como yo. Pero al final, me di cuenta de que era solo una manada de chacales que se creen lobos de mar...";
		link.l1.go = "Nemezida_Tichingitu_11";
		break;

	case "Nemezida_Tichingitu_11":
		dialog.text = "¿Y qué pasó? ¿Qué hacemos ahora?";
		link.l1 = "Buena pregunta. Casi me convierto en un chacal yo mismo con esos chacales. Así que, eso es suficiente para mí. Mis amigos y mi tripulación - esa es mi 'tribu'.";
		link.l1.go = "Nemezida_Tichingitu_12";
		break;

	case "Nemezida_Tichingitu_12":
		dialog.text = "Tichingitu está feliz de que hayas encontrado a tu tribu, Capitán Charles.";
		link.l1 = "Gracias, mi amigo. Necesitaba decir eso. Tú y yo somos nuestros propios líderes y tribu. Y ahora es momento de volver a asuntos realmente importantes.";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;

	// Айронс
	case "Nemezida_Irons_1":
		dialog.text = "¡Alguien se acerca! Y, a juzgar por el sonido, no viene a unirse a nosotros para celebrar el Día de Acción de Gracias.";
		link.l1 = "¡Malditas raíces! Muy bien, tendremos que lidiar con estos bribones ahora, mejor ahora que cuando carguemos el tesoro al barco.";
		link.l1.go = "Nemezida_Irons_2";
		break;

	case "Nemezida_Irons_2":
		dialog.text = "Tienes razón. ¿Listo?";
		link.l1 = "No tenías que preguntar. No es como si tuviéramos opción.";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;

	case "Nemezida_Irons_3":
		dialog.text = "¡Están por todas partes, como ratas en los barrios bajos de Londres, Su Señoría! ¿Cuál es el plan - deberíamos mantener nuestra posición y enfrentarnos a tiros con los muchachos?";
		link.l1 = "¡No ahora, retrocedan! ¡Estamos aquí por el tesoro, no para luchar!";
		link.l1.go = "Nemezida_Irons_4";
		PlaySound("interface\abordage_wining.wav");
		break;

	case "Nemezida_Irons_4":
		dialog.text = "Heh, no hay objeciones aquí.";
		link.l1 = "¡Entonces acelera el paso!";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;

	case "Nemezida_Irons_5":
		dialog.text = "¡Oye, Capitán, mira - parece que este camino lleva a alguna parte. Y suena bastante animado por allí, a juzgar por el ruido!";
		link.l1 = "¿Podría ser que alguien más se enteró del tesoro? Tommy, ¿oyes eso? Nos han alcanzado. Muy bien, voy hacia adelante, y ustedes denles una bienvenida adecuada aquí.";
		link.l1.go = "Nemezida_Irons_6";
		PlaySound("interface\abordage_wining.wav");
		break;

	case "Nemezida_Irons_6":
		dialog.text = "¡Ahora lo escucho! Quienesquiera que sean, será mejor que te apresures, je-je. ¡De lo contrario, ¿cuál fue el punto de hacer todo este camino hasta aquí?!";
		link.l1 = "Oh, odiaría que ese fuera el caso.";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;

	case "Nemezida_Irons_7": // на берегу
		dialog.text = "Ah, ¡eres tú, capitán! Vaya, sobreviviste. No voy a mentir, no lo esperaba. Pero me alegra, no me malinterpretes, je-je.";
		link.l1 = "Tampoco lo esperaba, no te mentiré. Pero el hecho de que sobrevivieras, no me sorprende en absoluto. ¿Huiste?";
		link.l1.go = "Nemezida_Irons_8";
		break;

	case "Nemezida_Irons_8":
		dialog.text = "¡Me haces mal! ¡Tommy Irons nunca huye! Solo regresa por refuerzos. Pero no fue necesario, mis chicos y yo lo manejamos por nuestra cuenta, aunque, una vez más, soy el único que salió con vida, jeh...";
		link.l1 = "Tal vez esta vez deberías haber ido a buscar refuerzos. Pero yo... yo huí.";
		link.l1.go = "Nemezida_Irons_9";
		break;

	case "Nemezida_Irons_9":
		dialog.text = "¿Te escapaste? Je, me has sorprendido de nuevo. Pero en realidad quería correr hacia ti tan pronto como terminara. Soy mejor que cualquier refuerzo, ¿sabes? Es solo que...";
		link.l1 = "¿Qué pasa, Tom?";
		link.l1.go = "Nemezida_Irons_10";
		break;

	case "Nemezida_Irons_10":
		dialog.text = "Maldita sea, mientras estaba perdiendo el tiempo, la entrada detrás de ti se bloqueó con rocas. No pude pasar. Es hasta vergonzoso que me tomara tanto tiempo despejarla y no pudiera ayudarte allí. Me perdí un poco yo solo mientras intentaba regresar para buscar a los muchachos y ayudar a mover las rocas... Para cuando regresé, ya habías vuelto.";
		link.l1 = "Sí,   tal vez me avergüence admitir lo que me ocurrió hoy.";
		link.l1.go = "Nemezida_Irons_11";
		break;

	case "Nemezida_Irons_11":
		dialog.text = "¿Y qué pasó? No tengas miedo, cuéntamelo. Pero si es algo gracioso, me voy a reír, solo para que lo sepas. ¿Cómo debería ser de otra manera? Un amigo te ofrece su hombro y te da un codazo riendo.";
		link.l1 = "Bueno, seguro que sabes cómo consolar. Dime, Tommy. Dijiste que te gustaba la piratería. ¿Te alegraste de volver a ello conmigo?";
		link.l1.go = "Nemezida_Irons_12";
		break;

	case "Nemezida_Irons_12":
		dialog.text = "Lo pondré así. Sea pirata o no, lo que siempre he adorado, maldita sea, es la aventura. Veo que mi respuesta no te satisface. Estas cosas, los grandes asuntos, no son lo mío.";
		link.l1 = "No es que no me satisfaga. Pero eso no es lo que quería discutir. Sabes... Me di cuenta de que con los Tiraqs, me desvié completamente de mis objetivos. Además... Charlie Prince era una especie de lacayo, no un valiente capitán pirata, ¿lo entiendes, Tom? Eso es suficiente para mí.";
		link.l1.go = "Nemezida_Irons_13";
		break;

	case "Nemezida_Irons_13":
		dialog.text = "Lo entiendo. Por eso me sorprendió que dejaras que Terrax te controlara así. Ni siquiera parecías tú.";
		link.l1 = "Tal vez realmente fui Charlie Prince en aquel entonces. ¡Pero si volvemos a la piratería o no, lo decidiré yo! ¡Y sólo si realmente sirve a mis intereses y me acerca a mi objetivo!";
		link.l1.go = "Nemezida_Irons_14";
		break;

	case "Nemezida_Irons_14":
		dialog.text = "¡Ahora eso es más parecido! Pero quiero decir, ya sea Charlie Prince o Charles de Maure, sigue siendo tú. ¡Así que contigo, siempre fue malditamente interesante!";
		link.l1 = "Me alegra oír eso, Tommy.";
		link.l1.go = "Nemezida_Irons_15";
		break;

	case "Nemezida_Irons_15":
		dialog.text = "Recuerda, casi nadie te ayudará excepto tú mismo. ¡Es mejor hacer lo que amas, incluso solo, que dejar que otros tomen decisiones por ti!";
		link.l1 = "Verdad. Eso es exactamente lo que sentí con Tira. Incluso si termino siguiendo a alguien de nuevo, solo será bajo términos dignos, ¡no como un maldito chico de los recados!";
		link.l1.go = "Nemezida_Irons_16";
		break;

	case "Nemezida_Irons_16":
		dialog.text = "¡Tienes razón! Ahora, vámonos de aquí, mis piernas ya están temblando.";
		link.l1 = "Eh, estaba a punto de decir eso, ja-ja. Pero tienes razón, vamos. Tenemos mucho trabajo importante por delante, Tom. No este tipo de cosas.";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionFinal_Officers");
		break;

	// Алонсо
	case "Nemezida_Alonso_1":
		dialog.text = "¡Capitán, parece que tenemos compañía! No estamos solos aquí.";
		link.l1 = "Justo lo que necesitábamos... Bien, tratemos con ellos ahora. Más tarde, solo serán más problemas.";
		link.l1.go = "Nemezida_Alonso_2";
		break;

	case "Nemezida_Alonso_2":
		dialog.text = "¡Aye, Capitán!";
		link.l1 = "¡Prepárate!";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionZasada2");
		break;

	case "Nemezida_Alonso_3":
		dialog.text = "¡Cada vez hay más de ellos!";
		link.l1 = "¡Entonces no tiene sentido continuar con esto! ¡Retrocedan! ¡Los perderemos y nos dirigiremos directamente al tesoro!";
		link.l1.go = "Nemezida_Alonso_4";
		PlaySound("interface\abordage_wining.wav");
		break;

	case "Nemezida_Alonso_4":
		dialog.text = "¡Aye, Capitán!";
		link.l1 = "¡Muévanse, muévanse!";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionZasada4");
		break;

	case "Nemezida_Alonso_5":
		dialog.text = "¡Capitán, parece que hay una entrada aquí! Y alguien ya está adentro.";
		link.l1 = "Escuchad bien - nos han seguido. Entraré a echar un vistazo mientras vosotros mantenéis esta posición. ¡Cubridme, muchachos!";
		link.l1.go = "Nemezida_Alonso_6";
		PlaySound("interface\abordage_wining.wav");
		break;

	case "Nemezida_Alonso_6":
		dialog.text = "¡Aye, Capitán!";
		link.l1 = "¡Mantén tu posición. Buena suerte para ti, para todos nosotros!";
		link.l1.go = "exit";
		AddDialogExitQuest("Mtraxx_RetributionZasada6");
		break;

	//--> блок реагирования на попытку залезть в сундук
	case "Man_FackYou":
		dialog.text = LinkRandPhrase("Eres " + GetSexPhrase("¡un ladrón, veo! Guardias, apresadlo", "¡una ladrona, veo! Guardias, ¡prendedla!") + "¡¡¡!!!", "¡No lo puedo creer! Me di la vuelta un segundo, ¡y ya estás hurgando en mis pertenencias! ¡Detengan al ladrón!!!", "¡Guardias! ¡Robo! ¡Detengan al ladrón!!!");
		link.l1 = "¡Aaaah, demonio!!!";
		link.l1.go = "fight";
		break;

	case "fight":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LAi_SetOwnerTypeNoGroup(npchar);
		LAi_group_Attack(NPChar, Pchar);
		if (rand(3) != 1)
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		AddDialogExitQuest("MainHeroFightModeOn");
		break;
		//<-- блок реагирования на попытку залезть в сундук

		// <-- legendary edition
	}
}
