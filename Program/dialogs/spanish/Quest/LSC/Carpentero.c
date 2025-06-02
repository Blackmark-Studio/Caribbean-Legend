// Санчо Карпентеро - бармен
#include "DIALOGS\%language%\Rumours\Common_rumours.c"
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

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
			dialog.text = "No quiero hablar contigo. Atacas a la gente pacífica sin motivo y los provocas a pelear. ¡Lárgate de mi taberna!";
			link.l1 = "Mm...";
			link.l1.go = "exit";
			break;
		}
		if (pchar.questTemp.LSC == "return" && !CheckAttribute(npchar, "quest.return_isl"))
		{
			dialog.text = "" + pchar.name + "¡Estoy tan contento de verte! ¡Sabía, sabía que los rumores eran una mentira! ¡Maldita sea, tenemos que beber por eso ahora mismo!";
			link.l1 = "¡Bueno, bebamos, camarada! ¡También me alegra muchísimo verte!";
			link.l1.go = "exit";
			npchar.quest.return_isl = "true";
			break;
		}
		// пей до дна
		if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "fail")
		{
			dialog.text = "" + pchar.name + "Lamento tu fracaso. Pocos pueden beber más que el gordo. ¿Cómo está tu cabeza?";
			link.l1 = "Sí, amigo, tienes un buen ron fuerte ahí. Te debo por las bebidas... ¿cuánto?";
			link.l1.go = "drunk_fail";
			break;
		}
		if (CheckAttribute(npchar, "quest.drink") && npchar.quest.drink == "win")
		{
			dialog.text = "Has vencido a Fazio, " + pchar.name + "¡Estoy sorprendido, solo unos pocos pudieron beber más que él! Aquí tienes tus doscientos doblones.";
			link.l1 = "¡Gracias por tus amables palabras, camarada!";
			link.l1.go = "drunk_win";
			break;
		}
		// крабовый салат
		if (CheckAttribute(npchar, "quest.crab") && npchar.quest.crab == "begin")
		{
			dialog.text = "" + pchar.name + "¿Dicen que te sumergiste hasta el fondo en un traje hecho por un mecánico Narval? ¿Es cierto o solo chismes, como de costumbre?";
			link.l1 = "Es cierto, camarada. Me zambullí allí de verdad.";
			link.l1.go = "crab";
			break;
		}
		if (npchar.quest.meeting == "0")
		{
			dialog.text = "¡Saludos al nuevo hombre en mi taberna! ¡Bienvenido! Siempre encontrarás bebidas en mi taberna, mis bodegas de vino están llenas, aunque no puedo decir lo mismo sobre la comida, ja-ja... Es broma. Me llamo Sancho Carpentero y soy el dueño de este lugar.";
			link.l1 = TimeGreeting() + ", Sancho. Mi nombre es " + GetFullName(pchar) + "Encantado de conocerte.";
			link.l1.go = "meeting";
			npchar.quest.meeting = "1";
		}
		else
		{
			dialog.text = "Ah, mi amigo " + pchar.name + "¡Me alegra verte en mi taberna! ¿Quieres beber algo?";
			// квестовые ветки
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_1" && !CheckAttribute(npchar, "quest.mushket"))
			{
				link.l6 = "Escucha, Sancho, ¿sabes dónde puedo conseguir un buen mosquete? No una pistola cualquiera de soldado, sino algo preciso, tal vez para cazar?";
				link.l6.go = "mushket";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "search_mush_2")
			{
				link.l6 = "Escucha, Sancho, tengo unas preguntas para ti. Estoy buscando a un hombre llamado Adolf Barbier. Dicen que a menudo visita este lugar...";
				link.l6.go = "adolf";
			}
			if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "barmen_whiskey")
			{
				link.l6 = "Escucha, Sancho, dicen que Chad Kapper te compró algo de arsénico...";
				link.l6.go = "whiskey";
			}
			if (CheckCharacterItem(pchar, "talisman1") && CheckAttribute(npchar, "quest.rat"))
			{
				link.l7 = "Sancho, ¿quieres que te muestre algo interesante? ¿Es esta la máscara de murciélago que tanto querías conseguir?";
				link.l7.go = "rat";
			}
			if (CheckCharacterItem(pchar, "talisman1") && CheckAttribute(npchar, "quest.ratmoney") && GetCharacterItem(pchar, "gold_dublon") >= 1)
			{
				if (GetCharacterItem(pchar, "gold_dublon") >= sti(npchar.quest.ratmoney))
				{
					if (!CheckAttribute(npchar, "quest.ratmoneyagain"))
						ChangeCharacterComplexReputation(pchar, "fame", 5);
					link.l7 = "Sancho, he venido por mi coraza. Aquí está el dinero.";
					link.l7.go = "rat_3";
				}
				else
				{
					npchar.quest.ratmoneyagain = true;
					link.l7 = "Sancho, he venido por mi coraza. Aquí está el dinero.";
					link.l7.go = "rat_take_money_not_all";
				}
			}
			if (makeint(pchar.money) >= 25)
			{
				link.l1 = "Sírvanme un poco de ron, Sancho.";
				link.l1.go = "drink";
			}
			if (makeint(pchar.money) >= 20)
			{
				link.l2 = "Quiero quedarme.";
				link.l2.go = "room";
			}
			if (stf(environment.time) >= 6.0 && stf(environment.time) <= 18.0 && makeint(pchar.money) >= 300)
			{
				link.l9 = "Aburrido... Sancho, quiero pasar el tiempo aquí con una botella de vino hasta la tarde...";
				link.l9.go = "drink_sit";
			}
			link.l3 = LinkRandPhrase("¿Tienes algo interesante que contar?", "¿Qué ha sucedido en la isla recientemente?", "¿Algún chisme?");
			link.l3.go = "rumours_LSC";
			if (CheckAttribute(npchar, "quest.crab") && npchar.quest.crab == "current" && CheckCharacterItem(pchar, "crab_pincers"))
			{
				link.l10 = "Sancho, quiero venderte garras de cangrejo.";
				link.l10.go = "crab_trade";
			}
			link.l4 = "Sancho, quiero preguntarte algo sobre la Isla.";
			link.l4.go = "int_quests"; // информационный блок
			link.l5 = "No, amigo. Solo quería ver cómo te va aquí.";
			link.l5.go = "exit";
		}
		NextDiag.TempNode = "First time";
		break;

	case "meeting":
		dialog.text = "Yo también. ¡Espero verte al menos cada dos días o incluso cada noche, ja-ja! Estoy sinceramente feliz de tener cualquier visitante en mi taberna.";
		if (makeint(pchar.money) >= 25)
		{
			link.l1 = "Sírveme un poco de ron, Sancho.";
			link.l1.go = "drink";
		}
		if (makeint(pchar.money) >= 20)
		{
			link.l2 = "Quiero quedarme.";
			link.l2.go = "room";
		}
		link.l3 = "Sancho, quiero preguntarte algo sobre la isla.";
		link.l3.go = "int_quests"; // информационный блок
		link.l4 = "¡Nos vemos, Sancho!";
		link.l4.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "mushket":
		dialog.text = "No, amigo, no puedo ayudarte. Sabes, soy un especialista en vasos de cerveza y botellas de vino, ¡pero no en mosquetes, ja-ja! Ve a la tienda, escuché que Axel a veces vende armas interesantes. Podrías encontrar lo que necesitas allí.";
		link.l1 = "Gracias por el consejo.";
		link.l1.go = "exit";
		npchar.quest.mushket = "true";
		break;

	case "adolf":
		dialog.text = "¿Adolf? Sí, me visita de vez en cuando, aunque no lo he visto en los últimos días. Ha estado desaparecido desde que habló con ese hombre gordo, Giuseppe.";
		link.l1 = "¿Giuseppe? ¿Te refieres a Giuseppe Fazio?";
		link.l1.go = "adolf_1";
		break;

	case "adolf_1":
		dialog.text = "Ja, amigo, solo hay un Giuseppe en la Isla - Giuseppe Fazio. Sí, ese es él. Estuvieron sentados unas horas bebiendo ron, teniendo una conversación muy animada.";
		link.l1 = "¿Estaban discutiendo?";
		link.l1.go = "adolf_2";
		break;

	case "adolf_2":
		dialog.text = "No. Parecía como si fueran viejos camaradas. Mira, solo visita a Fazio en la 'Caroline' y pregúntale sobre Adolf.";
		link.l1 = "Bien, haré eso.";
		link.l1.go = "adolf_3";
		break;

	case "adolf_3":
		dialog.text = "¿Eso es todo? Dijiste que tenías algunas preguntas...";
		link.l1 = "Sí. Dime, ¿quiénes son Mary la Roja y Cíclope Marcello?";
		link.l1.go = "adolf_4";
		break;

	case "adolf_4":
		dialog.text = "Red Mary es una de los Narvales. Joven y hermosa, pero completamente salvaje, sí. Sabe usar su espada y una pistola tan bien como cualquier hombre. Solía ser la novia de Alan Milrow, un exlíder del clan Narval, antes de que el almirante lo matara\nLa muerte de Alan la afectó mucho, la mayor parte del tiempo está llorando y maldiciendo a Shark en su camarote en el 'Ceres Smithy'... Pero lo superará, la vida continúa después de todo\nNo sé mucho sobre Marcello, lo he visto solo un par de veces. Tipo sospechoso. Dicen que solía ser un cazador real, perdió un ojo en una pelea y se fue a navegar como oficial de abordaje\nOdia a los piratas, parece que tiene un rencor contra ellos. No es sorprendente, dada su previa servidumbre en las partidas de abordaje de barcos comerciales.";
		link.l1 = "Ya veo. ¡Muchas gracias, Sancho, has ayudado mucho!";
		link.l1.go = "adolf_5";
		break;

	case "adolf_5":
		dialog.text = "De nada, amigo, ven a verme de nuevo, y tomaremos algo de cerveza juntos...";
		link.l1 = "¡Por supuesto!";
		link.l1.go = "adolf_6";
		break;

	case "adolf_6":
		DialogExit();
		pchar.questTemp.Saga.SharkHunt = "search_mush_3"; // флаг на Джузеппе
		AddQuestRecord("SharkHunt", "13");
		break;

	// виски для Акулы
	case "whiskey":
		dialog.text = "¿Kapper? No. No ha visitado la taberna recientemente. Marcello Cyclops compró un frasco de arsénico hace apenas quince minutos; él también está atormentado por las ratas. Lo entiendo perfectamente... Malditas ratas.";
		link.l1 = "¿Marcello Cyclops?";
		link.l1.go = "whiskey_1";
		break;

	case "whiskey_1":
		dialog.text = "Pues, sí. ¿Es eso extraño?";
		link.l1 = "¡No, por supuesto que no! Lo he estado buscando durante unos días y resulta que ha estado aquí recientemente. ¿Podrías decirme adónde fue?";
		link.l1.go = "whiskey_2";
		break;

	case "whiskey_2":
		dialog.text = "Estaba con Adolf Barbier, quien vive en la 'Santa Florentina'. Tal vez iban para allá.";
		link.l1 = "¡Gracias!";
		link.l1.go = "whiskey_3";
		break;

	case "whiskey_3":
		dialog.text = "Si necesitas algo de arsénico, entonces puedo vender una botella por veinte doblones.";
		link.l1 = "Está bien. Hablaremos de ello más tarde, Sancho. ¡Nos vemos!";
		link.l1.go = "whiskey_4";
		break;

	case "whiskey_4":
		DialogExit();
		pchar.questTemp.Saga.SharkHunt = "whiskey_poison"; // флаг - виски травят
		AddQuestRecord("SharkHunt", "37");
		sld = CharacterFromID("LSC_Adolf");
		LAi_SetActorType(sld);
		ChangeCharacterAddressGroup(sld, "SantaFlorentinaShipInside4", "goto", "goto2");
		sld = CharacterFromID("Dodson");
		sld.dialog.currentnode = "whiskey"; // ноду Акуле
		// важный момент! От дальнейшего поведения геймера зависит результат
		pchar.quest.LSC_Whiskeypoison_SF.win_condition.l1 = "location";
		pchar.quest.LSC_Whiskeypoison_SF.win_condition.l1.location = "SantaFlorentinaShipInside4";
		pchar.quest.LSC_Whiskeypoison_SF.function = "LSC_WhiskeyPoison_SF"; // прерывание на Санта-Флорентину
		pchar.quest.LSC_Whiskeypoison_AE.win_condition.l1 = "location";
		pchar.quest.LSC_Whiskeypoison_AE.win_condition.l1.location = "AvaShipInside3";
		pchar.quest.LSC_Whiskeypoison_AE.function = "LSC_WhiskeyPoison_AE"; // прерывание на Эву
		pchar.quest.LSC_Whiskeypoison_exit.win_condition.l1 = "location";
		pchar.quest.LSC_Whiskeypoison_exit.win_condition.l1.location = "LostShipsCity_town";
		pchar.quest.LSC_Whiskeypoison_exit.function = "LSC_Whiskeypoison_exit"; // прерывание на выход из таверны
		// закрываем вход к Фацио
		LocatorReloadEnterDisable("LostShipsCity_town", "reload20", true);
		LocatorReloadEnterDisable("LostShipsCity_town", "reload24", true);
		break;

	// пей до дна
	case "drunk_fail":
		dialog.text = "¡Vamos, amigo! No me debes nada. Ya has perdido cien doblones. Fue un error tratar con Fazio...";
		if (sti(pchar.money) >= 500)
		{
			link.l1 = "¡No, no, Sancho! Gracias y por favor, toma estos quinientos pesos. Eso debería cubrir el costo de las bebidas, según recuerdo. No quiero estar en deuda contigo.";
			AddMoneyToCharacter(pchar, -500);
		}
		else
			link.l1 = "Eh, gracias, Sancho. Tienes razón.";
		link.l1.go = "exit";
		DeleteAttribute(npchar, "quest.drink");
		break;

	case "drunk_win":
		DialogExit();
		TakeNItems(pchar, "gold_dublon", 200);
		Log_Info("Has recibido 200 doblones");
		PlaySound("interface\important_item.wav");
		DeleteAttribute(npchar, "quest.drink");
		break;

	// крабовый салат
	case "crab":
		dialog.text = "Hm... entonces tengo una propuesta para ti. ¿Has visto cangrejos gigantes allí?";
		link.l1 = "¿He visto cangrejos? ¡Había hordas de ellos! ¿Y de qué propuesta estás hablando?";
		link.l1.go = "crab_1";
		break;

	case "crab_1":
		dialog.text = "Si matas algunos cangrejos, asegúrate de traerme las pinzas. Te pagaré bien en doblones - cinco monedas por cada una. Axel Yost no pagará tanto, créeme. No te pido que caces cangrejos para esta tarea, pero si te encuentras con algunos, por favor tenlo en cuenta...";
		link.l1 = "¿Por qué las garras? ¿Qué pasa con las otras partes de un cangrejo? ¿Qué haces con ellas?";
		link.l1.go = "crab_2";
		break;

	case "crab_2":
		dialog.text = "¿Por qué las pinzas? Porque la mayor parte de la carne está en ellas. Los cangrejos no tienen mucha carne en sus patas y los cuerpos están cubiertos con un caparazón sólido. La carne de cangrejo es un manjar aquí, tiene un sabor exquisito y es muy nutritiva.\nTambién tengo una receta única para ella, así que te pagaré cinco doblones por cada pinza.";
		link.l1 = "Está bien. Lo tendré en cuenta.";
		link.l1.go = "crab_3";
		break;

	case "crab_3":
		DialogExit();
		npchar.quest.crab = "current";
		break;

	case "crab_trade":
		iTotalTemp = GetCharacterItem(pchar, "crab_pincers")
						 dialog.text = "¡Espléndido! ¿Cuántos tienes?";
		link.l1 = "" + FindRussianQtyString(iTotalTemp) + ".";
		link.l1.go = "crab_trade_1";
		link.l2 = "He cambiado de opinión.";
		link.l2.go = "exit";
		break;

	case "crab_trade_1":
		dialog.text = "Trato hecho. Aquí, toma tus doblones, " + FindRussianQtyString(iTotalTemp * 5) + " Gracias, amigo, si consigues más, tráemelos.";
		link.l1 = "Claro, amigo.";
		link.l1.go = "crab_trade_2";
		break;

	case "crab_trade_2":
		DialogExit();
		RemoveItems(pchar, "crab_pincers", iTotalTemp);
		TakeNItems(pchar, "gold_dublon", iTotalTemp * 5);
		PlaySound("interface\important_item.wav");
		Log_Info("Has recibido " + iTotalTemp * 5 + " doblones");
		break;

	// крыс
	case "rat":
		dialog.text = "¿Qué?! ¡Muéstramelo! ¡Déjame verlo!";
		link.l1 = "Claro.";
		link.l1.go = "rat_1";
		break;

	case "rat_1":
		PlaySound("interface\important_item.wav");
		dialog.text = "Esto es... ¡Realmente lo es! ¡Es exactamente igual al de la imagen que un marinero dibujó para mí! Amigo, debe haber una razón por la que me trajiste esto, ¿qué quieres por ello? ¿Cuánto?";
		link.l1 = "Por supuesto, te lo traje por una razón. Pero en cuanto a la recompensa, ¿qué puedes ofrecerme? Hasta donde recuerdo, me prometiste una recompensa real por esta cosa...";
		link.l1.go = "rat_2";
		link.l2 = "Lo siento, amigo, no está en venta. Lo necesito para mí. Solo quería asegurarme de que este es el talismán del que has estado hablando.";
		link.l2.go = "rat_exit";
		break;

	case "rat_exit":
		PlaySound("interface\important_item.wav");
		dialog.text = "Eh, qué lástima... Sí, muchacho, este es exactamente ese talismán. ¡Maldito suertudo! Ahora las ratas no te causarán más problemas. Y yo tendré que seguir exterminándolas con arsénico...";
		link.l1 = "Lo siento por burlarme de ti, Sancho. Nunca lo había visto antes, así que necesitaba una consulta. Lo siento.";
		link.l1.go = "exit";
		DeleteAttribute(npchar, "quest.rat");
		break;

	case "rat_2":
		dialog.text = "Para esto," + pchar.name + ", te ofreceré la oportunidad de adquirir el artículo más fino y valioso que poseo. Sería un excelente intercambio por este amuleto, especialmente para un valiente guerrero como tú. Déjame ir a buscarlo para ti.\nÉchale un vistazo: aquí tienes una coraza de Milán única y espléndida, ¡cuidadosamente elaborada! Ofrece una protección excepcional en batalla, permitiendo movimiento sin restricciones, y es ligera y cómoda. Armaduras de esta calidad son raras tanto en el Caribe como en Europa.\nMe encontré con esta coraza en los camarotes del capitán de un buque de guerra español hace varios años y la guardé precisamente para una ocasión como esta. Estoy dispuesto a vendértela por dos mil monedas de oro y el Dios Rata!";
		link.l1 = "Hum... ¡ESTA es una excelente coraza! Creo que este intercambio me conviene. Resolveré la situación con las ratas, pero encontrar otra coraza como esta sería casi imposible. Nunca antes había visto una igual. En verdad, es una pieza de armadura única.";
		link.l1.go = "rat_yes";
		link.l2 = "¿Cuánto? Sancho, ¿acaso tus ratas ya te han mordido unas cuantas veces esta mañana? ¿Qué quieres decir con dos mil? ¿Sabes siquiera lo que me costó conseguirte este ídolo? ¡Baja el precio ahora mismo!";
		link.l2.go = "rat_torg";
		link.l3 = "¿¡Cuánto?! Eres un tiburón, ¿lo sabías, Sancho? '¡Ofrecer una oportunidad para comprar!' ¡Ja! ¡Por esa cantidad de dinero, podría encargarme una armadura en el continente que desviara balas y me sanara al mismo tiempo! ¿Y para qué necesitarías tanto oro? ¿Para que Jurgen te haga una estatua y la exhiba a tamaño completo en 'San Agustín'?";
		link.l3.go = "rat_no";
		break;

	case "rat_yes":
		dialog.text = "Me alegra que estés a bordo, amigo mío. ¡Gracias por no olvidar mi problema! Así que, estaré esperando mis doblones. La armadura te estará esperando.";
		link.l1 = "¡Los traeré en breve!";
		link.l1.go = "rat_yes_1";
		break;

	case "rat_yes_1":
		DialogExit();
		DeleteAttribute(npchar, "quest.rat");
		npchar.quest.ratmoney = 2000;
		break;

	case "rat_torg":
		if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 60)
		{
			notification("Skill Check Failed (60)", SKILL_COMMERCE);
			dialog.text = "" + pchar.name + ", en otras circunstancias, exigiría cinco mil. El propio almirante ha mostrado interés, y no está solo, créeme. Tómate tu tiempo para decidir. La armadura te estará esperando todo el tiempo que necesites. Solo te la venderé a ti.";
			link.l1 = "Lo pensaré, Sancho. Lo meditaré largo y tendido.";
			link.l1.go = "rat_yes_1";
			AddCharacterExpToSkill(pchar, "Commerce", 400);
		}
		else
		{
			notification("Skill Check Passed", SKILL_COMMERCE);
			dialog.text = "" + pchar.name + ", en otras circunstancias, exigiría cinco mil. El almirante mismo ha mostrado interés, y no está solo, créeme. Bien, descontaré quinientos, considerando que no te has olvidado de mí y de mi problema. Parece que ha habido algunas aventuras en el camino.";
			link.l1 = "Eso es mejor. Pero aún no entiendo por qué debería pagar más en este intercambio de objetos igualmente únicos. Tal vez deberías ser tú quien me pague a mí, ¿eh Sancho?";
			link.l1.go = "rat_yes_1500";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		}
		break;

	case "rat_yes_1500":
		if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) < 90)
		{
			notification("Skill Check Failed (90)", SKILL_COMMERCE);
			dialog.text = "No, " + pchar.name + ", no va a suceder. Puedo lidiar con las ratas con veneno, pero esta armadura podría salvarte la vida algún día. Y te verás como un duque italiano llevándola. Mil quinientos, esa es mi oferta final. Tómate tu tiempo para pensarlo y avísame. La armadura te estará esperando el tiempo que necesites, la venderé solo a ti.";
			link.l1 = "Sancho, si no fueras el único tabernero en este lúgubre cementerio... Pensaré en tu oferta.";
			link.l1.go = "rat_yes_1500exit";
			AddCharacterExpToSkill(pchar, "Commerce", 600);
		}
		else
		{
			notification("Skill Check Passed", SKILL_COMMERCE);
			dialog.text = "¡Para ser un capitán militar y un pirata, sabes cómo negociar! ¿Recuerdas a Jost? Una vez logró comprarme todo el arsénico con descuento, mientras las ratas ya me atormentaban. Está bien, " + pchar.name + ", tú ganas. ¡Te descontaré otros quinientos! ¡Pero esa es mi última oferta!";
			link.l1 = "Sigue pareciendo una estafa, pero al menos ahora no me sentiré como la típica damisela en apuros en la jungla. Espera el dinero; lo traeré pronto.";
			link.l1.go = "rat_yes_1000exit";
			AddCharacterExpToSkill(pchar, "Commerce", 200);
		}
		break;

	case "rat_no":
		dialog.text = "Tranquilízate, " + pchar.name + "¡De cualquiera otro exigiría cinco mil! El almirante mismo ha mostrado interés, y no está solo, créeme. La armadura te esperará todo el tiempo que sea necesario. Eso también está incluido en el precio del ídolo.";
		link.l1 = "¡Qué honor! Sigue limpiando tus vasos, y yo me pondré en camino. ¡Dos mil!";
		link.l1.go = "rat_yes_1";
		break;

	case "rat_yes_1500exit":
		DialogExit();
		DeleteAttribute(npchar, "quest.rat");
		npchar.quest.ratmoney = 1500;
		break;

	case "rat_yes_1000exit":
		Achievment_SetStat(106, 1);
		DialogExit();
		DeleteAttribute(npchar, "quest.rat");
		npchar.quest.ratmoney = 1000;
		break;
	case "rat_3":
		dialog.text = "¡Hecho! Me alegra que hayas aceptado, camarada. ¡Gracias por no olvidar mi problema! Toma la coraza, y que te sirva bien en la batalla.";
		link.l1 = "Aquí, toma también tu talismán, ¡parece que se avecinan días oscuros para las ratas en tu taberna!";
		link.l1.go = "rat_4";
		break;

	case "rat_4":
		DialogExit();
		GiveItem2Character(pchar, "cirass4");
		RemoveItems(pchar, "talisman1", 1);
		RemoveItems(pchar, "gold_dublon", sti(npchar.quest.ratmoney));
		Log_Info("Has entregado el talismán Dios de las ratas");
		Log_Info("Has recibido una armadura milanesa");
		Log_Info("Has entregado " + FindRussianDublonString(sti(npchar.quest.ratmoney)) + "");
		PlaySound("interface\important_item.wav");
		DeleteAttribute(npchar, "quest.ratmoney");
		if (CheckAttribute(npchar, "quest.ratmoneyagain"))
			DeleteAttribute(npchar, "quest.ratmoneyagain");
		break;

	case "rat_take_money_not_all":
		npchar.quest.ratmoney = sti(npchar.quest.ratmoney) - GetCharacterItem(pchar, "gold_dublon");
		Log_Info("Has entregado " + FindRussianDublonString(GetCharacterItem(pchar, "gold_dublon")) + "");
		RemoveItems(pchar, "gold_dublon", GetCharacterItem(pchar, "gold_dublon"));
		PlaySound("interface\important_item.wav");
		dialog.text = "Todavía faltan " + FindRussianDublonString(sti(npchar.quest.ratmoney)) + ", " + pchar.name + ".";
		link.l1 = "¡No me lo recuerdes!";
		link.l1.go = "exit";
		break;

	//--> информационный блок
	case "int_quests":
		dialog.text = "Estoy escuchando.";
		if (!CheckAttribute(npchar, "quest.answer_1"))
		{
			link.l1 = "¿Qué es este lugar? ¿Puedes contarme más sobre él?";
			link.l1.go = "ansewer_1";
		}
		if (!CheckAttribute(npchar, "quest.answer_2"))
		{
			link.l2 = "¿Cómo puedo salir de la Isla?";
			link.l2.go = "ansewer_2";
		}
		if (!CheckAttribute(npchar, "quest.answer_3"))
		{
			link.l3 = "¿Qué debo saber sobre la Isla?";
			link.l3.go = "ansewer_3";
		}
		if (!CheckAttribute(npchar, "quest.answer_4"))
		{
			link.l4 = "¿Y cómo te va aquí? ¿Cómo está tu taberna?";
			link.l4.go = "ansewer_4";
		}
		link.l10 = "No tengo preguntas, no importa...";
		link.l10.go = "exit";
		break;

	case "ansewer_1":
		dialog.text = "¿Este lugar? Bueno, lo llaman la Isla Justicia, la Isla de los Barcos Abandonados o la Ciudad de los Barcos Abandonados, pero nosotros simplemente la llamamos la Isla. Está formada por los restos de barcos, que están varados en un banco de arena entre los arrecifes. La parte central de la Isla es una zona habitada y el anillo exterior está deshabitado. No ha habido conexión con el mundo exterior durante diez años.";
		link.l1 = "Entendido...";
		link.l1.go = "int_quests";
		npchar.quest.answer_1 = "true";
		break;

	case "ansewer_2":
		dialog.text = "Construye un bote largo o una balsa. Pero no te terminará bien. Hay una tormenta de anomalías alrededor de la Isla, no pasarás el anillo exterior sin arriesgar tu vida. Además, la Isla está rodeada por una fuerte corriente.\nNecesitas un equipo para tener siquiera una mínima oportunidad de sobrevivir. Y muy pocos lugareños están dispuestos a dejar este lugar. Incluso menos están dispuestos a correr cualquier riesgo. A la gente le gusta la forma de vida aquí. Pregunta por ahí si no me crees.";
		link.l1 = "Veo...";
		link.l1.go = "int_quests";
		npchar.quest.answer_2 = "true";
		break;

	case "ansewer_3":
		dialog.text = "Primero, debes recordar que hay varias áreas restringidas en la Isla. Dos clanes - Narvales y Rivados, han estado viviendo aquí por mucho tiempo, luchando entre ellos y protegiendo sin miedo los territorios que consideran suyos. Intenta visitarlos sin invitación y serás un hombre muerto\nDebes conocer la contraseña actual si quieres entrar en su territorio. No te preocupes por llegar allí por accidente, los guardias te darán varias advertencias antes de empezar a disparar.";
		link.l1 = "Tendré eso en mente...";
		link.l1.go = "int_quests";
		npchar.quest.answer_3 = "true";
		break;

	case "ansewer_4":
		dialog.text = "Sabes, amigo mío, está bien. Yo solía trabajar con comida y bebida: Trabajé como cocinero hace mucho tiempo en Europa, como intendente en una guarnición, tabernero y cocinero en un barco; así que lo primero que hice aquí fue montar una taberna. Me gusta mi trabajo y mi vida es extrañamente satisfactoria. La gente es amable aquí, en su mayoría. Al menos no se matan entre ellos con frecuencia. Los clanes no interfieren en mis actividades. En general, este es el mejor lugar de mi vida. Aquí soy libre y nadie me dice lo que tengo que hacer.\nLo único que me vuelve loco son las ratas. Me torturan, se comen mis provisiones y me estropean la vajilla. Me cuesta deshacerme de ellas.";
		link.l1 = "¿Ratas? Sí, son el problema de todos...";
		link.l1.go = "ansewer_4_1";
		break;

	case "ansewer_4_1":
		dialog.text = "¡Ay, soy la persona más desafortunada aquí cuando se trata de ratas! Otros barcos no están tan aterrorizados por las ratas y Axel Yost de alguna manera logró lidiar con ellas de una vez por todas. En cuanto a mí, tengo ejércitos de ratas arrastrándose aquí. Eh, me dijeron que hay un amuleto especial llamado el Dios de las Ratas.\nParece una máscara de cara de murciélago. Dicen que este amuleto asusta a las ratas a más no poder. Supongo que alguien le vendió a Axel este amuleto, él compra y revende cada pedazo de basura que encuentran en el anillo exterior.\n¡Ojalá alguien me trajera el amuleto, le ofrezco a esa persona una recompensa real!";
		link.l1 = "Interesante...";
		link.l1.go = "int_quests";
		npchar.quest.answer_4 = "true";
		npchar.quest.rat = "true";
		break;
	//<-- информационный блок

	//--> выпивка
	case "drink":
		if (CheckAttribute(pchar, "questTemp.Rum") && sti(pchar.questTemp.Rum) > 4)
		{
			dialog.text = "" + pchar.name + ", creo que deberías parar. Dios no quiera que te metas en problemas o caigas por la borda para convertirte en comida de cangrejos... No es buena idea beber demasiado por aquí, mucha gente ha muerto por eso.";
			link.l1 = "Hum... Supongo que tienes razón, Sancho... ya he tenido suficiente. ¡Gracias por tu preocupación!";
			link.l1.go = "exit";
		}
		else
		{
			AddMoneyToCharacter(pchar, -25);
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
			WaitDate("", 0, 0, 0, 0, 30);

			dialog.text = "¡Eres bienvenido, amigo! ¡Solo veinticinco pesos por una pinta de mi mejor ron!";
			link.l1 = RandPhraseSimple(LinkRandPhrase("¡Bueno, por tu salud y por la prosperidad de tu taberna, camarada!", "¡Pues, a aquellos que están en el mar!", "¡Bueno, a los habitantes de tu Isla!"), LinkRandPhrase("¡Bueno, a la Isla, y que esté por siempre!", "¡Pues que el viento siempre sea favorable en todas nuestras acciones!", "¡Bueno, por la suerte, la felicidad y... las mujeres!"));
			link.l1.go = "drink_1";
		}
		break;

	case "drink_1":
		DialogExit();
		LAi_Fade("", "");
		if (CheckAttribute(pchar, "questTemp.Rum"))
		{
			if (sti(pchar.questTemp.Rum) < 3)
				LAi_AlcoholSetDrunk(pchar, 51, 5600);
			else
				LAi_AlcoholSetDrunk(pchar, 71, sti(pchar.questTemp.Rum) * 2800);
		}
		break;

	case "drink_sit":
		if (chrDisableReloadToLocation || pchar.questTemp.Saga.SharkHunt == "barmen_whiskey" || pchar.questTemp.Saga.SharkHunt == "whiskey_poison") // идёт квест
		{
			dialog.text = "No creo que sea una buena idea que bebas ahora. Confía en mí...";
			link.l1 = "Bien.";
			link.l1.go = "exit";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.LSC.MaryBye") || CheckAttribute(pchar, "questTemp.LSC.MaryWait")) // подружился с Мэри
		{
			dialog.text = "Heh, eres un hombre extraño... ¿No tienes a nadie con quien pasar el tiempo aquí, en la Isla? Compañero, Mary me matará si te dejo quedarte aquí y emborracharte solo. Ven aquí juntos por la noche y diviértete hasta el amanecer, si lo deseas.";
			link.l1 = "Bien...";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "Sin problema, camarada. Por solo trescientos pesos obtendrás una buena botella de vino " + LinkRandPhrase("español", "italiano", "francés") + ". Diviértete tanto como quieras.";
			link.l1 = "¡Gracias!";
			link.l1.go = "drink_sit_1";
		}
		break;

	case "drink_sit_1":
		DialogExit();
		sld = ItemsFromID("potionrum");
		sld.shown = true;
		sld.startLocation = "FleuronTavern";
		sld.startLocator = "bottle";
		DoQuestReloadToLocation("FleuronTavern", "quest", "sit2", "LSC_DrinkSit");
		break;
	//<-- выпивка

	//--> сон в таверне
	case "room":
		if (chrDisableReloadToLocation || pchar.questTemp.Saga.SharkHunt == "barmen_whiskey" || pchar.questTemp.Saga.SharkHunt == "whiskey_poison") // идёт квест
		{
			dialog.text = "No creo que debas dormir ahora. Confía en mí...";
			link.l1 = "Bien.";
			link.l1.go = "exit";
			break;
		}
		if (CheckAttribute(pchar, "questTemp.LSC.MaryBye") || CheckAttribute(pchar, "questTemp.LSC.MaryWait")) // подружился с Мэри
		{
			if (!isDay())
			{
				dialog.text = "Jamás he conocido a un hombre tan extraño. Hay una hermosa muchacha esperándolo en la 'Herrería Ceres' y él va a pasar la noche en la taberna. Ni pienses que te dejaré dormir aquí. Mary me matará por eso.";
				link.l1 = "Bien...";
				link.l1.go = "exit";
			}
			else
			{
				dialog.text = "Puedes descansar arriba hasta la tarde. Pero no te dejaré pasar la noche aquí, Mary me matará por eso. Lo siento...";
				link.l1 = "Está bien. Me quedaré aquí hasta la noche...";
				link.l1.go = "hall_night_wait";
				link.l2 = "Está bien... Me las arreglaré sin dormir.";
				link.l2.go = "exit";
			}
			break;
		}
		dialog.text = "Puedes dormir en la cama de arriba por solo veinte pesos. ¿Cuándo debo despertarte?";
		if (!isDay())
		{
			link.l1 = "Por la mañana.";
			link.l1.go = "hall_day_wait";
		}
		else
		{
			link.l1 = "Antes del anochecer.";
			link.l1.go = "hall_night_wait";
			link.l2 = "A la mañana siguiente.";
			link.l2.go = "hall_day_wait";
		}
		link.l3 = "He cambiado de opinión. No quiero dormir.";
		link.l3.go = "exit";
		break;

	case "hall_night_wait":
		AddMoneyToCharacter(pchar, -20);
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		TavernWaitDate_LSC("wait_night");
		break;

	case "hall_day_wait":
		AddMoneyToCharacter(pchar, -20);
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		TavernWaitDate_LSC("wait_day");
		break;
		//<-- сон в таверне

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
