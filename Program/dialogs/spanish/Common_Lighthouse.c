#include "DIALOGS\%language%\Rumours\Common_rumours.c" //Jason
// Jason общий диалог смотрителей маяков
void ProcessDialogEvent()
{
	ref NPChar;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Lighthouse\" + NPChar.City + "_Lighthouse.c ";
						 if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}
	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag);

	int iTest, iTemp;
	string sTemp;
	bool ok;
	iTest = FindColony(NPChar.City); // город
	ref rColony;
	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}
	switch (Dialog.CurrentNode)
	{
	case "First time":
		if (LAi_grp_playeralarm > 0)
		{
			dialog.text = PCharRepPhrase(LinkRandPhrase("Se ha dado la alarma en el pueblo. Aparentemente, es hora de que yo también tome las armas...", "¿No estarán los guardias de la ciudad corriendo detrás de ti, por casualidad?", "No encontrarás refugio aquí, ¡pero puedes encontrar varias pulgadas de acero frío bajo tu costilla!"), LinkRandPhrase("¿Qué necesitas, " + GetSexPhrase("granuja", "granuja") + "? ¡Los guardias te están rastreando, no llegarás lejos, " + GetSexPhrase("sucio pirata", "apestosa") + "!", "" + GetSexPhrase("¡Sucio asesino", "¡Sucia asesina") + "! ¡Guardias!", "No te temo, " + GetSexPhrase("apestoso", "alimaña") + ". ¡Pronto serás colgado en nuestro fuerte, no llegarás lejos!"));
			link.l1 = PCharRepPhrase(RandPhraseSimple("Veo que estás cansado de vivir...", "Así parece, no hay gente pacífica en " + XI_ConvertString("Colony" + npchar.city + "Gen") + "¡, todos quieren ser un héroe!"), RandPhraseSimple("¡Vete al infierno!", "Je, estos serán los últimos segundos de tu vida..."));
			link.l1.go = PCharRepPhrase("exit_setOwner", "fight");
			break;
		}
		// belamour legendary edtion карибские нравы
		if (npchar.quest.meeting != "0" && CheckAttribute(npchar, "quest.trial_usurer"))
		{
			dialog.text = "¿Qué te trae a mí esta vez?";
			link.l1 = "Creo que conoces a un caballero llamado Gerard LeCroix, ¿cierto? Debería haber dejado una recompensa para mí...";
			link.l1.go = "Trial";
			DelLandQuestMark(npchar);
			break;
		}
		// <-- legendary edition
		if (npchar.quest.meeting == "0")
		{
			dialog.text = RandPhraseSimple("¡Buenas tardes, marinero! Mi nombre es " + GetFullName(npchar) + ", y yo soy el guardián de este faro. ¿Qué viento te ha traído aquí?", "¡Hola! Ha pasado bastante tiempo desde la última vez que vi caras nuevas en mi faro... Permíteme presentarme, " + GetFullName(npchar) + ", y este faro es mi hogar y mi trabajo. ¿Qué puedo hacer por ti?");
			link.l1 = "Hola, " + npchar.name + "¡ Mi nombre es " + GetFullName(pchar) + ", soy un capitán de barco. Estaba dando un paseo por esta maravillosa cala y decidí detenerme para ver quién vive allí.";
			link.l1.go = "Lightman_meeting";
			npchar.quest.meeting = "1";
		}
		else
		{
			dialog.text = "¡Oh, mi viejo amigo, capitán " + GetFullName(pchar) + "¡ Entra, entra! ¿Qué te ha traído aquí esta vez?";
			link.l1 = "¡Salud a ti, viejo salado! ¿No estás lamentándote en soledad aquí en tu faro?";
			link.l1.go = "Lightman_talk";
		}
		NextDiag.TempNode = "First time";
		break;

	case "Lightman_meeting":
		dialog.text = "Ahora lo sabes. Solía ser un marinero, igual que tú, pero ha pasado mucho tiempo desde que pisé por última vez la cubierta de un barco. Ahora este faro está a mi cargo, y también vendo algunas cosas...";
		link.l1 = "¿Y qué exactamente estás vendiendo?";
		link.l1.go = "trade_info";
		NextDiag.TempNode = "First time";
		break;

	case "Lightman_talk":
		dialog.text = "¿Qué te ha traído aquí esta vez?";
		link.l1 = RandPhraseSimple("¿Puedes decirme si ha ocurrido algo interesante recientemente en tu colonia?", "No he pisado tierra firme desde hace bastante tiempo... ¿Qué está pasando aquí?");
		link.l1.go = "rumours_lighthouse";
		link.l2 = "Veamos lo que tienes a la venta.";
		link.l2.go = "Trade_lighthouse";
		if (CheckAttribute(npchar, "artefact"))
		{
			if (CheckAttribute(npchar, "quest.art"))
			{
				link.l3 = "Entonces, " + npchar.name + ", ¿ya ha llegado mi amuleto?";
				link.l3.go = "Trade_artefact_3";
			}
			else
			{
				link.l3 = "" + npchar.name + ", quiero encargar un amuleto de ti.";
				link.l3.go = "Trade_artefact_1";
			}
			// калеуче
			if (CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "amulet" && !CheckAttribute(npchar, "quest.Caleuche"))
			{
				link.l5 = "Escucha, " + npchar.name + ", sé que te dedicas a la entrega de amuletos por encargo. Así que, seguramente sabes mucho sobre ellos. Mira, esta pequeña cosa, ¿qué puedes decirme sobre ella?";
				link.l5.go = "Caleuche";
			}
			if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster && CheckAttribute(pchar, "questTemp.Caleuche") && pchar.questTemp.Caleuche == "mayak")
			{
				link.l5 = "Amigo, estoy aquí de nuevo para preguntarte sobre esos extraños amuletos";
				link.l5.go = "Caleuche_9";
			}
		}
		link.l4 = "Hay algo que iba a preguntarte...";
		link.l4.go = "quests";
		link.l9 = "Solo eché un vistazo...";
		link.l9.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "trade_info":
		dialog.text = "A veces voy a la orilla y recojo conchas, hay un lugar bastante bonito no muy lejos de aquí, así que siempre puedes comprarme perlas. Cada tormenta trae ámbar, también lo vendo, aunque te costará mucho.\nA veces las olas traen todo tipo de trinketes interesantes de barcos hundidos y mis viejos compañeros me traen artículos especiales. Estoy interesado en amuletos encantados, los hombres sabios pagan buena moneda por ellos.\nTambién ofrezco armas en ocasiones especiales, no me preguntes de dónde las obtengo. Un comerciante de la ciudad compra toda la mierda de mí, las cosas buenas las vendo yo mismo después de repararla y limpiarla.\nEstoy interesado en el ron. No estoy hablando de la meada que sirven en la taberna por dos pesos la jarra. Estoy hablando de auténtico ron jamaicano embotellado. Sana y resucita a las personas. Pagaré diez veces más por cada botella que traigas. Piénsalo.";
		link.l1 = "Escucha, " + npchar.name + ", dijiste que tenías viejos amigos marineros, quienes te traen amuletos encantados. ¿Es posible encargar un amuleto específico de ti? Lo pagaré generosamente.";
		link.l1.go = "Trade_artefact";
		break;

	case "Trade_lighthouse":
		// иногда продает корабельные товары // Addon-2016 Jason
		npchar.quest.goods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE));
		npchar.quest.goodsqty = 50 + hrand(100);
		if (sti(npchar.quest.goods) == GOOD_EBONY || sti(npchar.quest.goods) == GOOD_MAHOGANY)
			npchar.quest.goodsqty = 25 + hrand(50);
		npchar.quest.goodsprice = makeint(sti(Goods[sti(npchar.quest.goods)].Cost) / 4);	// цена единицы товара
		npchar.quest.goodscost = sti(npchar.quest.goodsprice) * sti(npchar.quest.goodsqty); // стоимость товара
		ok = (!CheckAttribute(npchar, "goods_date")) || (GetNpcQuestPastDayParam(npchar, "goods_date") >= 10) if (hrand(4) == 1 && makeint(GetCharacterFreeSpace(pchar, sti(npchar.quest.goods))) > sti(npchar.quest.goodsqty) && sti(pchar.money) >= sti(npchar.quest.goodscost) && ok)
		{
			dialog.text = "Capitán, recientemente una cantidad de mercancías fue arrastrada a la orilla, " + GetGoodsNameAlt(sti(npchar.quest.goods)) + ". Algunas partes se echaron a perder por el agua salada, pero " + FindRussianQtyString(sti(npchar.quest.goodsqty)) + "Logré guardar en gran estado. ¿Quieres comprar algo? Los venderé barato, solo por " + FindRussianMoneyString(sti(npchar.quest.goodsprice)) + " por unidad.";
			link.l1 = "Nah. Muéstrame tus recientes adquisiciones.";
			link.l1.go = "Trade_lighthouse_double";
			link.l2 = "Hm... Una oferta honesta, estoy de acuerdo. Supongo que podría revenderlo por algo de beneficio. Veamos... Eso ascenderá a " + FindRussianMoneyString(sti(npchar.quest.goodscost)) + ". ¿Es eso correcto?";
			link.l2.go = "Trade_goods";
			SaveCurrentNpcQuestDateParam(npchar, "goods_date");
		}
		else
		{
			DialogExit();
			if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
			{
				GiveItemToTrader(npchar);
				SaveCurrentNpcQuestDateParam(npchar, "trade_date");
			}
			LaunchItemsTrade(npchar, 0);
		}
		break;

	case "Trade_lighthouse_double":
		DialogExit();
		if (!CheckAttribute(npchar, "trade_date") || GetNpcQuestPastDayParam(npchar, "trade_date") >= 10)
		{
			GiveItemToTrader(npchar);
			SaveCurrentNpcQuestDateParam(npchar, "trade_date");
		}
		LaunchItemsTrade(npchar, 0);
		break;

	case "Trade_goods":
		AddCharacterGoods(pchar, sti(npchar.quest.goods), sti(npchar.quest.goodsqty));
		AddMoneyToCharacter(pchar, -sti(npchar.quest.goodscost));
		AddMoneyToCharacter(npchar, sti(npchar.quest.goodscost));
		dialog.text = "Lo has entendido bien, capitán. ¡Un gran trato! Ambos hemos obtenido un beneficio decente de ello...";
		link.l1 = "Muy bien, entonces. Enviaré a los marineros para llevar la carga a mi barco. Ahora muéstrame lo que has reunido para vender.";
		link.l1.go = "Trade_lighthouse_double";
		break;
		//------------------------------------------------заказ артефактов------------------------------------------------
	case "Trade_artefact":
		if (CheckAttribute(npchar, "artefact")) // Addon-2016 Jason за дублоны
		{
			dialog.text = "Bueno, no todos ellos, pero algunos objetos son traídos más frecuentemente que otros, así que supongo que podría ayudarte. Pero te advierto: todos los amuletos ordenados de esta manera te costarán 100 doblones. Deberías entender...";
			link.l1 = "El precio no es un problema. ¿Qué amuletos puedes entregar?";
			link.l1.go = "Trade_artefact_1";
			link.l2 = "¡Pff! Uno podría comprar un barco con ese tipo de dinero. Es demasiado caro. Supongo que me las arreglaré bien yo solo...";
			link.l2.go = "exit_artefact";
		}
		else
		{
			dialog.text = "No, capitán. Tales cosas solo se pueden encontrar puramente por casualidad, por lo que es imposible hacer pedidos de ellas con anticipación. Y también tendrías que esperarlas un poco menos que para siempre...";
			link.l1 = "Bueno, si ese es el caso, no hay nada que hacer.";
			link.l1.go = "exit_artefact";
		}
		break;

	case "exit_artefact":
		if (CheckAttribute(npchar, "artefact"))
			dialog.text = "Como desees. Ven a verme si cambias de opinión.";
		else
			dialog.text = "¿Le gustaría ver lo que tengo a la venta hoy, capitán? Si no encuentra nada digno, regrese pronto, podría tener algo más en venta.";
		// belamour legendary edition карибские нравы -->
		if (CheckAttribute(npchar, "quest.trial_usurer"))
		{
			link.l1 = "Todo esto, por supuesto, es bueno, pero aquí está lo que quería preguntar: supongo que conoces a un caballero llamado Gerard Lecroix, ¿cierto? Debería haber dejado una recompensa para mí...";
			link.l1.go = "Trial";
			DelLandQuestMark(npchar);
			break;
		}
		// <-- legendary edition
		link.l1 = "Muéstrame tus artículos.";
		link.l1.go = "Trade_lighthouse";
		link.l2 = "Solo dime, ¿qué cosas interesantes han ocurrido recientemente en tu colonia?";
		link.l2.go = "rumours_lighthouse";
		link.l3 = "El comercio es comercio, pero quería preguntar algo.";
		link.l3.go = "quests";
		link.l4 = "Que tengas un buen día, " + npchar.name + "¡Fue un placer conocerte! Pasaré en otra ocasión...";
		link.l4.go = "exit";
		break;

	case "Trade_artefact_1":
		dialog.text = "Haz tu elección.";
		iTemp = 1;
		string sArt;
		if (CheckAttribute(npchar, "artefact.indian"))
			sArt = "indian_";
		if (CheckAttribute(npchar, "artefact.amulet"))
			sArt = "amulet_";
		if (CheckAttribute(npchar, "artefact.obereg"))
			sArt = "obereg_";
		for (i = 11; i >= 1; i--)
		{
			sTemp = "l" + iTemp;
			link.(sTemp) = XI_ConvertString(sArt + i);
			link.(sTemp).go = sArt + i;
			iTemp++;
		}
		link.l12 = "Lamentablemente, nada de esta lista me interesa hasta ahora.";
		link.l12.go = "exit";
		break;

	// группа indian
	case "indian_1":
		dialog.text = "¿Una muñeca de vudú? ¿Te gustan las armas de fuego? Bien...";
		link.l1 = "¿Cuándo debería volver a recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "indian_1";
		break;

	case "indian_2":
		dialog.text = "¿Un probador de pólvora? Ser un buen tirador es clave para tener éxito en cualquier escaramuza. Interesante...";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "indian_2";
		break;

	case "indian_3":
		dialog.text = "¿Un cuchillo ritual? ¿Te gusta desgarrar a tus enemigos con poderosos golpes de una espada ancha pesada? Eso es para ti, entonces. Bueno... ";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "indian_3";
		break;

	case "indian_4":
		dialog.text = "¿Un hacha de asta? ¡Un golpe de arriba hacia abajo de un enorme hacha aplastará a cualquier enemigo! Bueno...";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "indian_4";
		break;

	case "indian_5":
		dialog.text = "¿Una tsantsa? Ahora eso puede asustar incluso al pirata más temerario. Bueno...";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "indian_5";
		break;

	case "indian_6":
		dialog.text = "¿Un coral? ¡Los perdigones de tus cañones volarán directo al objetivo! Bueno...";
		link.l1 = "¿Cuándo debería regresar para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "indian_6";
		break;

	case "indian_7":
		dialog.text = "¿Jorobado? La incansabilidad es la mejor amiga del guerrero. Bueno...";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "indian_7";
		break;

	case "indian_8":
		dialog.text = "¿Xiuhtecuhtli? ¡Que el casco del barco enemigo se desmorone hasta convertirse en polvo! Bien...";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "indian_8";
		break;

	case "indian_9":
		dialog.text = "¿Baldo? ¡Pon a Baldo y todos los balones de cañón volarán directamente al blanco! Bueno...";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "indian_9";
		break;

	case "indian_10":
		dialog.text = "¿Cascavella? El veneno de serpiente es lo más peligroso. Bueno...";
		link.l1 = "¿Cuándo debería volver a recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "indian_10";
		break;

	case "indian_11":
		dialog.text = "¿Máscara de Ngombo? ¡Baja la vigilancia de tus enemigos, ja-ja! Bueno...";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "indian_11";
		break;

	// группа amulet
	case "amulet_1":
		dialog.text = "¿Escudo Ngombo? Si no lograste esquivar una bala, este amuleto puede salvar tu vida. Bueno...";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "amulet_1";
		break;

	case "amulet_2":
		dialog.text = "¿Eucologio? Una buena oración incluso puede desviar una bala. Bueno...";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "amulet_2";
		break;

	case "amulet_3":
		dialog.text = "¿Un crucifijo? Este ayudará mucho a un cristiano en combate cuerpo a cuerpo. Bueno...";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "amulet_3";
		break;

	case "amulet_4":
		dialog.text = "¿El Trozo? Este hará que una herida mortal sea solo un rasguño. Bueno...";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "amulet_4";
		break;

	case "amulet_5":
		dialog.text = "¿Sogbo? ¡Y que los cañones siempre estén listos para la batalla! Bueno...";
		link.l1 = "¿Cuándo debería volver a recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "amulet_5";
		break;

	case "amulet_6":
		dialog.text = "¿Madonna? El semblante de la Santísima Virgen posee poderosas propiedades curativas. Bueno...";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "amulet_6";
		break;

	case "amulet_7":
		dialog.text = "¿Agua bendita? ¡Incluso un debilucho rociado con agua bendita se convertirá en un héroe épico! Bueno...";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "amulet_7";
		break;

	case "amulet_8":
		dialog.text = "¿Un ancla? ¡Y que tu barco se mantenga a flote incluso bajo una lluvia de balas de cañón, ja-ja! Bueno...";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "amulet_8";
		break;

	case "amulet_9":
		dialog.text = "¿Encolpion? Tus velas no temerán ningún viento, mientras poseas este amuleto. Bueno...";
		link.l1 = "¿Cuándo debería volver a recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "amulet_9";
		break;

	case "amulet_10":
		dialog.text = "¿Hacedor de milagros? ¡Que el Señor cuide de tu tripulación tanto en tierra como en mar! Bueno...";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "amulet_10";
		break;

	case "amulet_11":
		dialog.text = "¿Cimaruta? ¡Las balas de mosquete volarán sobre tu cabeza, sin causarte daño! ¡Bien...";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "amulet_11";
		break;

	// группа obereg
	case "obereg_1":
		dialog.text = "¿Teredo? Cada carpintero de barcos sueña con ese. Bueno...";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "obereg_1";
		break;

	case "obereg_2":
		dialog.text = "¿Xochipilli? Eso ahorrará algo de tiempo remendando las velas. Bueno...";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "obereg_2";
		break;

	case "obereg_3":
		dialog.text = "¿Un mono? ¡Diría que un mulo de carga! Bueno...";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "obereg_3";
		break;

	case "obereg_4":
		dialog.text = "¿Abanico de gitana? ¡Ponle las anteojeras a los ojos de un patrullero! Bueno...";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "obereg_4";
		break;

	case "obereg_5":
		dialog.text = "¿Una tortuga de jade? ¡Esa es tu carta maestra en un mazo de cartas! Bueno...";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "obereg_5";
		break;

	case "obereg_6":
		dialog.text = "¿Un puño de mono? Como dicen, ¡haz que te respeten! Bueno...";
		link.l1 = "¿Cuándo debería regresar para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "obereg_6";
		break;

	case "obereg_7":
		dialog.text = "¿Un pescador? Eso es el sueño de todo navegante. Bueno...";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "obereg_7";
		break;

	case "obereg_8":
		dialog.text = "¿Cuentas de mercader? Al dinero le gusta ser contado, ¿no es así? Bueno...";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "obereg_8";
		break;

	case "obereg_9":
		dialog.text = "¿Ehecatl? ¡Cualquier viejo cacharro de baja velocidad volará más rápido que el viento! Bueno...";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "obereg_9";
		break;

	case "obereg_10":
		dialog.text = "¿Pendiente de marinero? ¡Dáselo a tu timonel! Bueno...";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "obereg_10";
		break;

	case "obereg_11":
		dialog.text = "¿Peregrino? El viento de frente se vuelve viento de cola. Bueno...";
		link.l1 = "¿Cuándo debería volver para recoger mi pedido?";
		link.l1.go = "Trade_artefact_2";
		npchar.quest.art = "obereg_11";
		break;

	case "Trade_artefact_2":
		dialog.text = "En dos meses, no antes. Creo que para entonces me lo habrán traído. Así que te estaré esperando con el dinero en dos meses.";
		link.l1 = "¡Genial! ¡Estaré allí! Gracias, " + npchar.name + "¡!";
		link.l1.go = "exit";
		SaveCurrentNpcQuestDateParam(npchar, "art_date");
		npchar.quest.artday = rand(20) + 50;
		sTemp = "Amulet_" + npchar.location;
		AddQuestRecord(sTemp, "1");
		ReOpenQuestHeader(sTemp);
		AddQuestUserData(sTemp, "sAml", XI_ConvertString(npchar.quest.art)); // dlc
		break;

	case "Trade_artefact_3":
		if (CheckAttribute(npchar, "art_date") && GetNpcQuestPastDayParam(npchar, "art_date") >= sti(npchar.quest.artday))
		{
			dialog.text = "Sí, lo tengo. ¿Has preparado 100 doblones, capitán?"; // Addon-2016 Jason
			// belamour legendary edition -->
			if (PCharDublonsTotal() >= 100)
			{
				link.l1 = "¡Claro! Aquí tienes, como acordamos.";
				link.l1.go = "Trade_artefact_4";
			}
			else
			{
				link.l1 = "¡Oh, he olvidado el dinero en el barco! Lo traeré pronto.";
				link.l1.go = "exit";
			}
			// <-- legendary edition
		}
		else
		{
			dialog.text = "Aún no. Ven a verme más tarde. Y no te preocupes, tu amuleto seguramente llegará.";
			link.l1 = "Bien.";
			link.l1.go = "exit";
		}
		break;

	case "Trade_artefact_4":
		RemoveItems(pchar, "gold_dublon", 100); // Addon-2016 Jason
		Log_Info("Has entregado 100 dobloness");
		dialog.text = "Todo parece estar bien. Aquí está tu amuleto. ¡Buena suerte con él!";
		link.l1 = "Gracias, " + npchar.name + ".";
		link.l1.go = "Trade_artefact_5";
		break;

	case "Trade_artefact_5":
		DialogExit();
		Log_Info("Has recibido " + XI_ConvertString(npchar.quest.art) + "");
		PlaySound("interface\important_item.wav");
		TakeNItems(pchar, npchar.quest.art, 1);
		DeleteAttribute(npchar, "quest.art");
		sTemp = "Amulet_" + npchar.location;
		AddQuestRecord(sTemp, "2");
		CloseQuestHeader(sTemp);
		break;

	// --> калеуче
	case "caleuche":
		PlaySound("interface\important_item.wav");
		dialog.text = "Muestra lo que tienes ahí.";
		link.l1 = "Aquí, parece un antiguo amuleto indio. Pero no tengo idea de cómo usarlo o de su poder oculto.";
		link.l1.go = "caleuche_1";
		npchar.quest.caleuche = "true";
		break;

	case "caleuche_1":
		if (npchar.id == pchar.questTemp.Caleuche.Amuletmaster)
		{
			dialog.text = "Bueno-bueno. Eres la tercera persona que me ha mostrado algo así, compañero. Este amuleto fue traído aquí desde la salvaje selva del Sur Principal. Hay indios no muy lejos de Panamá que llevan trinketes como este. Los pieles rojas dicen que esto es un legado de sus 'grandes ancestros.'\nNo tengo idea de quiénes fueron sus ancestros o qué tipo de legado dejaron, pero puedo darte un consejo sobre dónde preguntar. ¿Interesado?";
			link.l1 = "¡Ciertamente!";
			link.l1.go = "caleuche_2";
			DelLandQuestMark(npchar);
			if (npchar.id == "BasTer_Lightman")
				DelMapQuestMarkShore("Mayak4");
			if (npchar.id == "Santiago_Lightman")
				DelMapQuestMarkShore("Mayak9");
		}
		else
		{
			dialog.text = "Hmm... He tenido muchos amuletos en mis manos, pero este, lo veo por primera vez en el Caribe. Lo siento, amigo, no puedo ayudarte; no conozco este tipo de cosas. Pero no es una cosa sencilla; eso es un hecho. Pregúntale a otro. Sé con certeza que hay otros fareros como yo que no saben menos de amuletos.";
			link.l1 = "Perdóneme... Entonces seguiré preguntando.";
			link.l1.go = "exit";
		}
		break;

	case "caleuche_2":
		dialog.text = "Hay un pueblo caribe en Dominica, y el jefe se llama Moknitekuvri. Tienen un chamán llamado Tuttuathapak, un indio muy respetado. No es uno de los caribes; es de ese lugar del que ya te he hablado. Él puede decirte más sobre este amuleto que yo. Pero ten cuidado, Tuttuathapak odia a los blancos. Realmente los odia. Después de todo, una vez lo esclavizaron y lo alejaron de su hogar...";
		link.l1 = "¿Supongo que llegó al Caribe de esa manera?";
		link.l1.go = "caleuche_3";
		break;

	case "caleuche_3":
		dialog.text = "Sí. Esta es una historia bastante interesante. El barco, que transportaba esclavos indios, quedó atrapado por una calma chicha cerca de Marie Galante y la mitad de la tripulación murió de fiebre repentina. ¡Sin embargo, ni un solo indio se enfermó!\nDespués, el capitán enloqueció y prendió fuego a su barco. Como resultado, los indios encarcelados comenzaron un motín y masacraron a la tripulación. ¿Adivinas quién era su líder?";
		link.l1 = "Yo sí...";
		link.l1.go = "caleuche_4";
		break;

	case "caleuche_4":
		dialog.text = "Eso es. Apuesto a que fue un hechizo de chamán el que calmó el mar como si fuera un muerto, e infectó a la tripulación con una enfermedad mortal. Este indio es muy astuto y muy peligroso. Si vas con él, compórtate cortésmente y cuida tu lengua, de lo contrario, habrá muchos problemas para ti. Además, ni siquiera te hablará sin una ofrenda para él.";
		link.l1 = "¿Y qué tipo de ofrenda podría él exigir?";
		link.l1.go = "caleuche_5";
		break;

	case "caleuche_5":
		dialog.text = "No podrás sobornarlo con alguna porquería. Según sé, envía a sus soldados caribes a los asentamientos de blancos para comprar armas de fuego. Tráele un mosquete como regalo y entonces, creo, estará complacido y te prestará un poco de su atención.";
		link.l1 = "¡Gracias! Haré como dices... Dime, compañero, ¿cómo sabes todo esto?";
		link.l1.go = "caleuche_6";
		break;

	case "caleuche_6":
		dialog.text = "Mi amigo era un marinero en el barco condenado. Afortunadamente, logró sobrevivir en ese infierno... Vi en él un amuleto como el tuyo, parece que el difunto capitán también agarró las pertenencias de los indios. Estoy seguro de que tu amuleto es de su colección, cuando el capitán se volvió loco y prendió fuego a su barco, sus marineros lo mataron y luego saquearon los cofres en la cabina.";
		link.l1 = "Entendido. Entonces solo tengo que ir con un regalo a Dominica. ¡Gracias por tu ayuda y por la interesante historia!";
		link.l1.go = "caleuche_7";
		break;

	case "caleuche_7":
		dialog.text = "Buena suerte, mi amigo, y ten cuidado con este diablo de piel roja...";
		link.l1 = "...";
		link.l1.go = "caleuche_8";
		break;

	case "caleuche_8":
		DialogExit();
		AddQuestRecord("Caleuche", "2");
		pchar.questTemp.Caleuche = "dominica";
		Caleuche_CreateShamane();
		break;

	case "caleuche_9":
		dialog.text = "¿Sí? Has hablado con Tuttuathapak, ¿estoy en lo correcto?";
		link.l1 = "Exactamente. Y ahora quiero encontrar dos amuletos más. Dijiste que era el tercero que te mostró este artefacto. ¿Y quiénes eran los otros dos?";
		link.l1.go = "caleuche_10";
		break;

	case "caleuche_10":
		dialog.text = "Uno es mi amigo, el marinero de aquel barco que trajo a Tuttuathapak a las islas del Caribe. Desde aquel incidente, no ha pisado la cubierta de ningún barco. No lo he visto en un tiempo, pero sé dónde vive. Búscalo al oeste en Tierra Firme, en Belice, ahora es cazador y deambula por las selvas. Su nombre es Fergus Hooper.";
		link.l1 = "Bien. ¿Y el segundo?";
		link.l1.go = "caleuche_11";
		break;

	case "caleuche_11":
		dialog.text = "Sé sobre el segundo solo un poco. Ya sea que su nombre sea Jack o Jackson, y si es un corsario, o un pequeño empresario, o simplemente un aventurero. Él posee una xebec con un nombre extraño... hmm... su nombre es... ¡Maldita sea, lo olvidé! Pero el nombre es algo demoníaco. Le pregunté qué significaba, y él dijo que era una mujer-pájaro, nacida por dioses del mar. ¡Bah! Sin Dios...";
		link.l1 = "Empollón... ¿Así que no recuerdas su nombre?";
		link.l1.go = "caleuche_12";
		break;

	case "caleuche_12":
		dialog.text = "No, que me golpee el trueno, no lo recuerdo. Oh, y cuando se presentó, mencionó que era de Barbados.";
		link.l1 = "¡Eso es algo! Bien, intentaré encontrar a este amante de las mujeres emplumadas hasta que alguien más lo encuentre... ¡Gracias, compañero, me has ayudado mucho!";
		link.l1.go = "caleuche_13";
		break;

	case "caleuche_13":
		dialog.text = "De nada, capitán. Vuelva pronto y charlemos.";
		link.l1 = "¡Claro!";
		link.l1.go = "caleuche_14";
		break;

	case "caleuche_14":
		DialogExit();
		AddQuestRecord("Caleuche", "7");
		pchar.questTemp.Caleuche = "hunting";
		pchar.questTemp.Caleuche.Belizterms = rand(4) + 3;
		pchar.quest.caleuche_prepare_beliz.win_condition.l1 = "location";
		pchar.quest.caleuche_prepare_beliz.win_condition.l1.location = "Beliz";
		pchar.quest.caleuche_prepare_beliz.function = "Caleuche_PrepareBeliz";
		break;

	case "fight":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		LAi_group_Attack(NPChar, Pchar);
		if (rand(3) != 1)
			SetNationRelation2MainCharacter(sti(npchar.nation), RELATION_ENEMY);
		LAi_SetOwnerType(NPChar); // belamour иначе обижается навсегда
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
		dialog.text = LinkRandPhrase("Tú eres " + GetSexPhrase("¡un ladrón, querida mía! Guardias, ¡capturadlo!", "¡ladrón! Guardias, atrapadla") + "!!!", "¡Vaya! Me distraje un poco, ¡y ya estás metiendo la cabeza en el cofre! ¡Detén al ladrón!", "¡Guardias! ¡Robo! ¡Detengan al ladrón!");
		link.l1 = "¡Argh, mierda!";
		link.l1.go = "fight";
		break;

	// belamour legendary edition карибские нравы
	case "Trial":
			dialog.text = "¡Ah, así que tú eres ese capitán! Sí, te he estado esperando. Gerard también te esperaba, pero tuvo que ir urgentemente a alguna expedición, así que me pidió que te entregara el pago. Dijo que vendrías. Aquí hay cuatrocientos doblones, si te parece bien.");
			link.l1 = "¡Gracias! Es agradable tratar con personas honestas.";
			link.l1.go = "Trial_1";
			break;

	case "Trial_1":
		DialogExit();
		TakeNItems(pchar, "gold_dublon", 400);
		Log_Info("Has recibido 400 doblones");
		PlaySound("interface\important_item.wav");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DeleteAttribute(pchar, "questTemp.Trial");
		DeleteAttribute(npchar, "quest.trial_usurer");
		pchar.questTemp.IslamonaSpaOfficer = true;
		CloseQuestHeader("Trial");
		pchar.questTemp.TrialEnd = true;
		break;
		// <-- legendary edition
	}
}
