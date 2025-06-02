// boal 08/04/04 общий диалог торговцев
#include "DIALOGS\%language%\Rumours\Common_rumours.c" //homo 25/06/06

void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	string iDay, iMonth, sTemp, sMoney, attrL;

	iDay = environment.date.day;
	iMonth = environment.date.month;
	string lastspeak_date = iday + " " + iMonth;

	int iMoney, iQuantityGoods, iTradeGoods, iTmp;

	bool ok;

	int iTest, cn, i;
	iTest = FindColony(NPChar.City); // город магазина
	ref rColony, chref;

	if (iTest != -1)
	{
		rColony = GetColonyByIndex(iTest);
	}

	int iSeaGoods = LanguageOpenFile("ShipEatGood.txt"); // нужно заменить на GetGoodsNameAlt(idx)

	if (!CheckAttribute(npchar, "quest.trade_date"))
	{
		npchar.quest.trade_date = "";
	}

	// вызов диалога по городам -->
	NPChar.FileDialog2 = "DIALOGS\" + LanguageGetLanguage() + "\Store\" + NPChar.City + "_Store.c ";
						 if (LoadSegment(NPChar.FileDialog2))
	{
		ProcessCommonDialog(NPChar, Link, NextDiag);
		UnloadSegment(NPChar.FileDialog2);
	}

	// вызов диалога по городам <--
	ProcessCommonDialogRumors(NPChar, Link, NextDiag); // homo 25/06/06

	string attrLoc = Dialog.CurrentNode;

	if (HasSubStr(attrLoc, "TransferGoodsTo_"))
	{
		NPChar.CharToTransferGoodsID = FindStringAfterChar(attrLoc, "_");
		Dialog.CurrentNode = "TransferGoods_Start";
	}

	switch (Dialog.CurrentNode)
	{
	case "First time":
		if (LAi_grp_playeralarm > 0)
		{
			dialog.text = NPCharRepPhrase(pchar, LinkRandPhrase("Se ha dado la alarma en el pueblo, y todos te están buscando. Si yo fuera tú, no me quedaría allí.", "¡Toda la guardia de la ciudad está rastreando el pueblo buscándote! ¡No soy un tonto y no hablaré contigo!", "Corre, " + GetSexPhrase("compañero", "muchacha") + ", antes de que los soldados te conviertan en un colador..."), LinkRandPhrase("¿Qué necesitas, " + GetSexPhrase("canalla", "canalla") + "? ¡Los guardias de la ciudad ya tienen tu rastro, no llegarás lejos, " + GetSexPhrase("pirata inmundo", "suciedad asesina") + "!", "¡Asesino sucio, sal de mi casa de inmediato! ¡Guardias!", "No te temo, " + GetSexPhrase("despreciable", "apestoso") + "¡Pronto serás colgado en nuestro fuerte, no llegarás lejos..."));
			link.l1 = NPCharRepPhrase(pchar, RandPhraseSimple("Heh, una alarma nunca es un problema para mí...", " Nunca me atraparán."), RandPhraseSimple("Cierra tu maldita boca, " + GetWorkTypeOfMan(npchar, "") + ", ¡o te arrancaré esa sucia lengua!", "Heh, " + GetWorkTypeOfMan(npchar, "") + ", y todos allí, ¡están aquí para atrapar piratas! Te diré esto, camarada: siéntate en silencio y no morirás..."));
			link.l1.go = "fight";
			break;
		}
		if (sti(pchar.GenQuest.Piratekill) > 20 && sti(npchar.nation) == PIRATE)
		{
			dialog.text = RandPhraseSimple("¡Eh, bastardo! ¿Crees que puedes tomar lo que quieras? ¡Ciertamente no! ¡Chicos! ¡A las armas! ¡Corten al loco!", "¡Si quieres algo, cómpralo, bestia! ¡Ahora te enseñaré quién manda aquí! ¡Chicos, agarren las armas! ¡Alerta!");
			link.l1 = RandPhraseSimple("¿Eh? ¿Qué?", "Uh, ¿por qué estás haciendo esto?");
			link.l1.go = "fight";
			bDisableFastReload = true; // закрыть переход
			pchar.quest.pirate_in_town.win_condition.l1 = "ExitFromLocation";
			pchar.quest.pirate_in_town.win_condition.l1.location = pchar.location;
			pchar.quest.pirate_in_town.function = "TownPirate_battle";
			break;
		}
		//--> Jason Бремя гасконца
		if (CheckAttribute(pchar, "questTemp.Sharlie.Lock"))
		{
			// Jason --> мини-квест Дефицитный товар
			if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "Me gustaría comprar un lote de vino europeo, cincuenta o sesenta botellas. Me dijeron que tenías suficiente en stock.";
				link.l13.go = "Wine_Trader";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "Hola de nuevo. Por favor, echa un vistazo a esta carta, quizás reconsideres tu posición respecto a venderme vino.";
				link.l13.go = "Wine_Repeat2";
			}
			if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
			{
				link.l13 = "Soy yo otra vez. ¿Podemos reanudar nuestro negocio de vino interrumpido? Logré reunir suficiente dinero.";
				link.l13.go = "Wine_Price";
			}
			// <-- мини-квест Дефицитный товар
			dialog.text = "¿Quería comprar algo, monsieur?";
			Link.l1 = "Por supuesto que lo hice, ¿para qué más son las tiendas? Muéstrame tus mercancías.";
			Link.l1.go = "trade_1";
			Link.l2 = "Vengo por un propósito de negocio particular...";
			Link.l2.go = "quests";
			Link.l3 = "Lo siento, pero tengo que irme.";
			Link.l3.go = "exit";
			// туториал Мартиника
			if (NPChar.City == "FortFrance")
			{
				if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
				{
					Link.l2 = "Escuche, monsieur, estoy buscando un trabajo. No un trabajo a tiempo completo o cargar sacos de carga, sino más bien hacer recados, por así decirlo. ¿Necesita alguna asistencia?";
					Link.l2.go = "Sharlie_storehelper";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
				{
					Link.l2 = "He completado tu encargo. Encontré a Gralam Lavoie.";
					Link.l2.go = "Sharlie_storehelper_2";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
				{
					Link.l2 = "Conoce a tu nuevo asistente, monsieur.";
					Link.l2.go = "Sharlie_storehelper_11";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
				{
					Link.l2 = "Soy yo de nuevo, monsieur. He venido por mi recompensa.";
					Link.l2.go = "Sharlie_storehelper_13";
				}
				if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
				{
					link.l4 = "Échale un vistazo a estos pendientes, monsieur. Los encontré en el cuerpo de un bandido que fue asesinado en la jungla. Esto es claramente obra de un fino joyero que, estoy seguro, no es de por aquí. ¿Hay algo que pueda decir sobre estos pendientes?";
					link.l4.go = "Sharlie_junglejew";
				}
			}
			break;
		}
		//<-- Бремя гасконца

		// Warship, 29.05.11. Дело чести - трусливый фехтовальщик.
		if (CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
		{
			dialog.text = "Capitán, gracias por salvarme.";
			Link.l1 = "Oh, de nada.";
			Link.l1.go = "exit";
			DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
			break;
		}
		// Карибские нравы
		if (CheckAttribute(npchar, "quest.trial_usurer"))
		{
			dialog.text = "¿Qué pasa, capitán? ¿Ha perdido algo? ¿Por qué está corriendo así por mi tienda?";
			Link.l1 = "Bueno, imagínate eso, ¡de verdad lo tengo! ¿Dónde está ese maldito Gerard LeCroix? He cumplido todas las tareas que me dio Florian Shoke, y que me trague entero un tiburón, ¡tuve un maldito trabajo duro haciéndolo! Y ahora, cuando vengo a recoger mi recompensa, ¡resulta que este pájaro ha volado!";
			Link.l1.go = "trial";
			// belamour legendary edition -->
			Link.l2 = "¿Cómo puedo decírtelo... Perdido. ¿Has visto a mi cliente? Su nombre es Gerard LeCroix.";
			Link.l2.go = "trialA";
			//<-- legendary edition
			DelLandQuestMark(npchar);
			break;
		}
		// belamour legendary edition Бесчестный конкурент -->
		if (!CheckAttribute(pchar, "questTemp.Shadowtrader") && sti(npchar.nation) != PIRATE && npchar.location == "baster_store")
		{
			dialog.text = "Capitán, quiero pedirle un favor. ¿Me ayudará?";
			link.l1 = "¿Cómo puedo ayudarle?";
			link.l1.go = "Shadowtrader_begin";
			break;
		}
		// <-- legendary edition
		dialog.Text = GetNatPhrase(npchar, LinkRandPhrase("¡Encantado de conocerte, señor! ¿Eres nuevo en estas tierras?", "¡Bienvenido, capitán! Mi tienda está a su servicio, señor.", "¡Señor, por favor, pase! Me complace ofrecerle las mejores mercancías que puede comprar en este archipiélago."), LinkRandPhrase("¡Oh, monsieur capitán! ¡Las mejores mercancías de todas las colonias francesas, aquí y ahora, y exclusivamente para usted!", "¡Qué agradable encuentro, monsieur! ¡La mejor tienda con las mejores mercancías francesas a su servicio!", "¿Nos hemos conocido antes, monsieur capitán? ¡Sabéis, mi tienda es tan buena como las mejores tiendas en la madre patria!"), LinkRandPhrase("¡Oh! ¡Señor capitán! ¡Me alegra tanto verte en mi tienda!", "Me alegra saludar a tan brillante caballero en la mejor tienda de todas las colonias españolas.", "¡Oh, noble hidalgo! ¡El destino mismo te ha traído a mi humilde tienda! ¡Aquí encontrarás lo que desees!"), LinkRandPhrase("Buenas tardes, señor capitán. ¿Es esta su primera visita aquí?", "Hola, señor. ¿Ha venido aquí por primera vez? ¡Le aseguro que la calidad de nuestros productos holandeses le sorprenderá gratamente!", "¡Por favor, pase, señor capitán! Las mejores mercancías a los precios más bajos disponibles, ¡esa es la forma holandesa de comerciar!"));
		Link.l1 = LinkRandPhrase("Encantado de conocerte también. Mi nombre es " + GetFullName(pchar) + " y soy bastante nuevo en estas tierras. ¡Bueno, muéstrame las riquezas del archipiélago!", "Un placer conocerte también. Yo soy " + GetFullName(pchar) + ". Capitán del barco '" + pchar.ship.name + "'. Entonces, ¿cuáles son las ofertas calientes?", "" + GetFullName(pchar) + ", capitán del barco '" + pchar.ship.name + ", un placer conocerte. Entonces, ¿qué puedes ofrecerme?");
		link.l1.go = "node_1";

		if (startHeroType == 4 && NPChar.location == "SantaCatalina_store")
		{
			dialog.text = "¡Capitana Helen! Siempre un placer.";
			link.l1 = "Y yo a usted, gracias.";
			link.l1.go = "Helen_node_1";
		}
		NextDiag.TempNode = "Second time";
		break;

	case "second time":
		if (LAi_group_GetPlayerAlarm() > 0)
		{
			dialog.text = NPCharRepPhrase(pchar, LinkRandPhrase("Se ha dado la alarma en el pueblo, y todos te están buscando. Si yo fuera tú, no me quedaría allí.", "Todos los guardias de la ciudad están recorriendo el pueblo buscándote. ¡No soy un tonto y no hablaré contigo!", "Corre, " + GetSexPhrase("compañero", "muchacha") + ", antes de que los soldados te conviertan en un colador..."), LinkRandPhrase("¿Qué necesitas, " + GetSexPhrase("bribón", "canalla") + "? ¡Los guardias de la ciudad ya tienen tu olor, no llegarás lejos, " + GetSexPhrase("sucio pirata", "escoria") + "!", "¡Asesino inmundo, sal de mi casa de inmediato! ¡Guardias!", "No te temo, " + GetSexPhrase("arrastrado", "apestosa") + ". ¡Pronto serás ahorcado en nuestro fuerte, no llegarás lejos!"));
			link.l1 = NPCharRepPhrase(pchar, RandPhraseSimple("Heh, una alarma nunca es un problema para mí...", "Nunca me atraparán."), RandPhraseSimple("Cierra la boca, " + GetWorkTypeOfMan(npchar, "") + ", ¡o te arrancaré la sucia lengua!", "Heh, " + GetWorkTypeOfMan(npchar, "") + ", y todos allí, ¡están aquí para cazar piratas! Te diré esto, camarada: siéntate en silencio y no morirás..."));
			link.l1.go = "fight";
			break;
		}

		//--> Jason, Сомнительное предложение
		if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader.busy"))
		{
			dialog.text = "Por favor, discúlpame, pero no tengo tiempo para ti ahora.";
			link.l1 = "Sí, claro. Pasaré en otro momento, entonces.";
			link.l1.go = "exit";
			break;
		}
		//<-- Сомнительное предложение

		// Warship, 29.05.11. Дело чести - трусливый фехтовальщик.
		if (CheckAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk"))
		{
			dialog.text = "Capitán, gracias por salvarme.";
			Link.l1 = "Oh, de nada.";
			Link.l1.go = "exit";
			DeleteAttribute(PChar, "QuestTemp.AffairOfHonor.CowardFencer.CanTraderTalk");
			break;
		}
		// Карибские нравы
		if (CheckAttribute(npchar, "quest.trial_usurer"))
		{
			dialog.text = "¿Qué pasa, capitán? ¿Ha perdido algo? ¿Por qué corre por mi tienda así?";
			Link.l1 = "Bueno, imagina eso, ¡en realidad lo tengo! ¿Dónde está ese maldito Gerard LeCroix? He cumplido todas las tareas que me encomendó Florian Shoke, ¡y que el tiburón me trague entero, me costó un maldito trabajo hacerlo! ¡Y ahora, cuando vengo a recoger mi recompensa, resulta que este pájaro ha volado!";
			Link.l1.go = "trial";
			// belamour legendary edition -->
			Link.l2 = "¿Cómo puedo decírtelo... Perdido. ¿Has visto a mi cliente? Se llama Gerard LeCroix.";
			Link.l2.go = "trialA";
			//<-- legendary edition
			DelLandQuestMark(npchar);
			break;
		}
		// belamour legendary edition Бесчестный конкурент -->
		if (!CheckAttribute(pchar, "questTemp.Shadowtrader") && sti(npchar.nation) != PIRATE && npchar.location == "baster_store")
		{
			dialog.text = "Capitán, quiero pedirle un favor. ¿Me ayudará?";
			link.l1 = "¿Cómo puedo ayudarle?";
			link.l1.go = "Shadowtrader_begin";
			break;
		}
		// <-- legendary edition
		dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("¡Oh, mira quién está ahí! Bueno, como dicen, el dinero no huele, así que entra, capitán, y hagamos negocios...", "No puedo decir que me alegra verte, " + GetFullName(pchar) + "... Pero aún puedo comerciar contigo.", "Je-je... Bueno, no te invitaría a mi casa, capitán, pero mi tienda sigue a tu servicio."), LinkRandPhrase("¡Oh, mira quién está ahí! ¿No es ese " + GetFullName(pchar) + "¡Quieres comerciar o solo llevarte algunas cosas gratis? Oye, solo bromeo...", "No puedo decir que me alegra verte aquí, " + GetAddress_Form(NPChar) + "Pero si tienes dinero para gastar, entra, entra...", "¿Quieres comerciar, capitán " + GetFullName(pchar) + "¿Si es así, podría darse prisa, por favor? Otros clientes le están evitando, y esto es malo para mi negocio,"), LinkRandPhrase("¿Quiere comerciar, señor? Un momento, voy a hacer cuentas como sabe, hay tipos dudosos por aquí... ¡Por supuesto, no me refiero a usted, capitán!", "Si te viera en mar abierto, " + GetAddress_Form(NPChar) + ", probablemente ordenaría añadir velas... Pero aquí, en mi tienda, puedo ofrecerte comerciar.", "Capitán, te advertiré de inmediato: si la tela está manchada de sangre y el café apesta a pólvora, no lo aceptaré. De lo contrario, echa un vistazo y elige lo que quieras.")), LinkRandPhrase(LinkRandPhrase("Y me alegra saludarte de nuevo, " + GetAddress_Form(NPChar) + "¡Comprando o vendiendo, siempre estoy feliz de ayudarte!", "¡Te lo ruego, " + GetAddress_Form(NPChar) + ", entra! Siempre me alegra ver a mi cliente favorito aquí. ¿Qué será esta vez, comprar o vender?", "Oh, " + GetAddress_Form(NPChar) + " " + GetFullName(pchar) + " ¡Estoy tan feliz de verte de nuevo! ¿Qué será esta vez, comprar o vender?"), LinkRandPhrase("¿Te gustan nuestras mercancías, " + GetAddress_Form(NPChar) + " " + GetFullName(pchar) + "? Siempre estoy a tu servicio, echa un vistazo y elige.", "Hola, " + GetAddress_Form(NPChar) + " " + GetFullName(pchar) + ". ¡Me alegra verte de nuevo! ¿Quieres echar un vistazo al surtido de nuestras mercancías?", "¡Me alegra verte, capitán! Sabía que te gustarían nuestros productos de calidad. ¿Quieres echar un vistazo a lo nuevo?"), LinkRandPhrase("Oh, " + GetAddress_Form(NPChar) + " " + GetFullName(pchar) + " ¡Por favor, entra! ¡Todos estos artículos son solo para tí y cuentan con grandes descuentos en esta ocasión!", "Capitán " + GetFullName(pchar) + ", una vez más me has hecho feliz con tu visita. ¡Por favor, elige lo que quieras!", "¿Qué le gustaría esta vez, capitán? Me alegra que aún recuerde cómo encontrarme. ¡Tenemos todas las mercancías que pueda necesitar, de la mejor calidad!")));
		Link.l1 = pcharrepphrase(RandPhraseSimple(RandPhraseSimple("¿Así es como me das la bienvenida, compadre? Bueno, recordaré eso si nos encontramos en el mar... Deja de temblar, solo estaba bromeando. Muéstrame lo que tienes.", "Está bien, camarada. Puede que necesite tus mercancías, pero no necesito tu lengua. ¿Puedes callarte o necesitarás ayuda con eso? Cállate y muéstrame tus mercancías."), RandPhraseSimple("Acerquémonos al negocio, mercachifle. No tengo tiempo para discutir cuestiones morales contigo, así que comerciemos como personas decentes.", "Tranquilo, amigo. Las bromas están bien, pero ten en cuenta que puedo enfadarme... Así que deja de irritarme y simplemente muéstrame tus mercancías.")), RandPhraseSimple(RandPhraseSimple("Siempre encantado de visitarte, amigo. ¿Qué tienes en stock que valga la pena para mí?", "Siempre es bueno verte, camarada. Entonces, ¿qué hay de nuevo para los errantes del mar que no han pisado tierra firme en meses?"), RandPhraseSimple("Y una vez más estoy en " + XI_ConvertString("Colony" + npchar.City + "Acc") + " ¡Me alegra no haberlo olvidado! Pero, ¿queda algo en tus almacenes para mí? ¿Todo está organizado?", "¿Cómo no has venido? Siempre me complaces más que eso. Bueno, ¿qué tienes ahí?")));
		link.l1.go = "node_1";
		NextDiag.TempNode = "Second time";
		break;

	case "node_1":
		dialog.text = NPCStringReactionRepeat(NPCharRepPhrase(npchar, pcharrepphrase(RandPhraseSimple("¡Todos a cubierta! ", "¡Alto para inspección! ") + LinkRandPhrase("¿Qué hace un " + GetSexPhrase("caballero", "caballero, oh, perdóneme eres una dama") + " de fortuna necesitan en mi tienda, je-je?", "¡Qué sorpresa para un pobre viejo tendero! ¡Je-je!", "Entonces, ¿qué buen viento te ha traído a mi tienda?"), LinkRandPhrase("¡Abrir los puertos!", "¡Ganchos a los lados!", "¡Navega recto!") + RandPhraseSimple(" Aquí encontrarás ", " Mi tienda tiene ") + LinkRandPhrase("los mejores precios de toda la isla.", "un excelente surtido de bienes.", "las mercancías de la mejor calidad disponible.") + RandPhraseSimple(" Estoy a su servicio", "Lo que quieras") + ", ¡capitán!"), pcharrepphrase(RandPhraseSimple("¿Algún producto para " + GetSexPhrase("caballeros", "caballeros y damas") + " de la fortuna! ¡Je-je! ¡Hasta que los cuelguen para secar al sol!", "El viento balancea a los ahorcados en el puerto y lleva el tintineo de las cadenas. Pero el dinero no tiene olor, ¿verdad?"), "¿Te gustaría " + LinkRandPhrase("comprar las mejores mercancías de " + NationNameGenitive(sti(NPChar.nation)), "comprar o vender tu cargamento", "? ¿Tienes un flete rentable?") + RandPhraseSimple(" ¿Estoy a su servicio?", " ¿Mi tienda está a su servicio?") + RandPhraseSimple(" Encantado de verte", " Tú mismo") + ", capitán!")), NPCharRepPhrase(npchar, pcharrepphrase("Si quieres mi consejo, capitán, no escatimes en metralla. Sabes, ¡a los muertos es mucho más fácil registrar!", "Me he dado cuenta enseguida de que eres " + GetSexPhrase("un astuto camarada", "una muchacha astuta") + ". " + RandPhraseSimple("Pero ahora puedo ver que eres un verdadero " + GetSexPhrase("héroe", "temerario") + ".", "Eres joven, pero " + RandPhraseSimple("mantén tu ingenio contigo.", "ciertamente no puedes ser engañado fácilmente."))), pcharrepphrase("Estoy dispuesto a comprarte toda la carga de los premios capturados. ¿Quieres en plata o en oro? Ese material siempre es costoso.", "La navegación comercial es un negocio lucrativo, capitán " + GetFullName(pchar) + ", ¿no es así?")), NPCharRepPhrase(npchar, RandPhraseSimple("¡Los envolvimos bien apretados en el foque con veinte vueltas de cabo y los lanzamos por la borda fuera de vista! ", RandPhraseSimple("¡Quince hombres sobre el cofre del muerto!", "¡Bebed y el diablo se encargará del resto!") + "¡Yo ho ho y una botella de ron!") + RandPhraseSimple("¿Qué tal, capitán?", "¿Busca comprar algo, capitán?"), pcharrepphrase("Veo que eres todo un regateador, capitán " + GetFullName(pchar) + " . ¡Dado que eres un cliente habitual, te ofrezco precios muy buenos!", "Está bien, capitán " + GetFullName(pchar) + ", en deferencia a usted puedo ofrecer un poquito más! ¿Qué le gustaría?")), NPCharRepPhrase(npchar, "Juro que hablar contigo me enferma. " + LinkRandPhrase("Compra un par de cacahuetes. A los cerdos les gusta esa cosa. ", "¿Esperas que alguien pula tus botas con ron aquí? ", pcharrepphrase("Conozco tu tipo. Te cargas de ron, y directo al patíbulo.", "¡Me pregunto cómo permitió tu madre que te convirtieras en marinero! ¡Un marinero! Serías un sastre mucho mejor...")), pcharrepphrase(RandPhraseSimple("Pensé que ", "Esperaba que ") + RandPhraseSimple("habías abandonado nuestra isla para siempre.", " Nunca te volvería a ver.") + RandPhraseSimple(" Los muertos cuelgan de tu cuello como piedras de molino...", " ¿Cuántos marineros has dejado pudrirse entre los corales?!"), "Capitán " + GetFullName(pchar) + ", ¡tu pasión por el comercio ha superado todas mis expectativas!" + RandPhraseSimple(" ¿Quieres hacer compras de última hora antes de zarpar?", " ¿Buscas algo especial?"))), "cycle", 10, npchar, Dialog.CurrentNode);
		// belamour legendary edition на пару с Акулой -->
		if (CheckAttribute(pchar, "questTemp.SharkGoldFleet") && npchar.location == "caracas_store")
		{
			if (pchar.questTemp.SharkGoldFleet == "start" || pchar.questTemp.SharkGoldFleet == "afterGvik")
			{
				dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("¡Oh, mira quién está aquí! Bueno, como dicen, el dinero no huele, así que entra, capitán, y hagamos negocios...", "No puedo decir que me alegra verte, " + GetFullName(pchar) + "... Pero aún puedo comerciar contigo.", "He-he... Bueno, no te invitaría a mi casa, capitán, pero mi tienda sigue a tu servicio."), LinkRandPhrase("¡Oh, mira quién está allí! ¿No es ese " + GetFullName(pchar) + "¡Quieres comerciar o solo llevarte algo gratis? Oye, solo bromeaba...", "No puedo decir que me alegra verte aquí, " + GetAddress_Form(NPChar) + ". Pero si tienes dinero para gastar, entra, entra...", "¿Quieres comerciar, capitán " + GetFullName(pchar) + "¿Si es así, podrías darte prisa? Otros clientes te evitan, y esto es malo para mi negocio,"), LinkRandPhrase("¿Quieres comerciar, señor? Un momento, voy a hacer caja hay tipos dudosos por aquí... Por supuesto, no me refiero a usted, capitán!", "Si te viera en alta mar, " + GetAddress_Form(NPChar) + ", probablemente ordenaría añadir velas... Pero aquí, en mi tienda, puedo ofrecerte comerciar.", "Capitán, te advertiré de inmediato: si la tela está manchada de sangre y el café apesta a pólvora, no lo aceptaré. De lo contrario, echa un vistazo y haz tu elección.")), LinkRandPhrase(LinkRandPhrase("Y me alegra saludarte de nuevo, " + GetAddress_Form(NPChar) + "¡Comprando o vendiendo, siempre estoy encantado de ayudarte!", "¡Te lo ruego, " + GetAddress_Form(NPChar) + ", entra! Siempre me alegra ver a mi cliente favorito aquí. ¿Qué será esta vez, comprar o vender?", "Oh, " + GetAddress_Form(NPChar) + " " + GetFullName(pchar) + " ¡Estoy tan feliz de verte de nuevo! ¿ Qué será esta vez, comprar o vender?"), LinkRandPhrase("¿Te gustan nuestras mercancías, " + GetAddress_Form(NPChar) + " " + GetFullName(pchar) + "? Siempre estoy a tu servicio, echa un vistazo y elige.", "Hola, " + GetAddress_Form(NPChar) + " " + GetFullName(pchar) + ". ¡Me alegra verte de nuevo! ¿Quieres echar un vistazo al surtido de nuestras mercancías?", "¡Me alegra verte, capitán! Sabía que te gustarían nuestros productos de calidad. ¿Quieres echar un vistazo a lo nuevo?"), LinkRandPhrase("Oh, " + GetAddress_Form(NPChar) + " " + GetFullName(pchar) + "¡Por favor, entre! ¡¡Todos estos artículos son solo para tí y cuentan con grandes descuentos en esta ocasión!", "Capitán " + GetFullName(pchar) + "¡Una vez más me has alegrado con tu visita! Por favor, elige lo que te guste.", "¿Qué desea esta vez, capitán? Me alegra que aún recuerde cómo encontrarme. Tenemos todas las mercancías que pueda necesitar, ¡de la mejor calidad!")));
				link.l14 = "Escucha, estoy a punto de partir hacia Portobello ahora y me gustaría comprar un cargamento de café y cacao de ti. Digamos, trescientas unidades de ambos.";
				link.l14.go = "SharkGoldFleet";
			}
		}
		if (CheckAttribute(pchar, "questTemp.SharkGoldFleet") && npchar.location == "caracas_store" && pchar.questTemp.SharkGoldFleet == "buyincar")
		{
			dialog.Text = pcharrepphrase(LinkRandPhrase(LinkRandPhrase("¡Oh, mira quién está aquí! Bueno, como dicen, el dinero no huele, así que entra, capitán, y comerciemos...", "No puedo decir que me alegra verte, " + GetFullName(pchar) + "... Pero todavía puedo comerciar contigo.", "He-he... Bueno, no te invitaría a mi casa, capitán, pero mi tienda sigue a tu servicio."), LinkRandPhrase("¡Oh, mira quién está ahí! ¿No es ese " + GetFullName(pchar) + "¡¿Quieres comerciar o solo llevarte algunas cosas gratis? Eh, solo bromeaba...", "No puedo decir que me alegra verte aquí, " + GetAddress_Form(NPChar) + ". Pero si tienes dinero para gastar, entra, entra...", "¿Quieres comerciar, capitán " + GetFullName(pchar) + "¿Si es así, podrías hacerlo rápido? Otros clientes te evitan, y esto es malo para mi negocio,"), LinkRandPhrase("¿Quiere comerciar, señor? Un segundo, voy a hacer caja hay tipos dudosos por aquí... Por supuesto, no me refiero a usted, capitán!", "Si te viera en mar abierto, " + GetAddress_Form(NPChar) + ", probablemente ordenaría agregar velas... Pero aquí, en mi tienda, puedo ofrecerte comerciar.", "Capitán, te advertiré de inmediato: si la tela está manchada de sangre y el café apesta a pólvora, no lo aceptaré. De lo contrario, echa un vistazo y elige.")), LinkRandPhrase(LinkRandPhrase("Y me alegra saludarte de nuevo, " + GetAddress_Form(NPChar) + "¡Comprando o vendiendo, siempre estoy encantado de ayudarte!", "¡Te lo ruego, " + GetAddress_Form(NPChar) + ", entra! Siempre me alegra ver a mi cliente favorito aquí. ¿Qué será esta vez, comprar o vender?", "Oh, " + GetAddress_Form(NPChar) + " " + GetFullName(pchar) + " ¡Estoy tan feliz de verte de nuevo! ¿Qué será esta vez, comprar o vender?"), LinkRandPhrase("¿Te gustan nuestras mercancías, " + GetAddress_Form(NPChar) + " " + GetFullName(pchar) + "? Siempre estoy a tu servicio, echa un vistazo y elige.", "Hola, " + GetAddress_Form(NPChar) + " " + GetFullName(pchar) + ". ¡Me alegra verte de nuevo! ¿Quieres echar un vistazo a nuestro surtido de mercancías?", "¡Me alegra verte, capitán! Sabía que te gustarían nuestros productos de calidad. ¿Quieres echar un vistazo a lo nuevo?"), LinkRandPhrase("Oh, " + GetAddress_Form(NPChar) + " " + GetFullName(pchar) + "¡Por favor, pasa! ¡Todos estos artículos son solo para tí y cuentan con grandes descuentos en esta ocasión!", "Capitán " + GetFullName(pchar) + "¡ , una vez más me has hecho feliz con tu visita! Por favor, elige lo que quieras, lo que más te guste!", "¿Qué desearía esta vez, capitán? Me alegra que aún recuerde cómo encontrarme. ¡Tenemos todas las mercancías que pueda necesitar, de la mejor calidad!")));
			link.l14 = "Estoy aquí por café y cacao. ";
			link.l14.go = "SharkGoldFleet_again";
		}

		// <-- на пару с Акулой
		link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar, pcharrepphrase("¡Muéstrame lo que tienes, viejo pirata!", "Solo quería echar un vistazo a tus mercancías, buen hombre."), pcharrepphrase("Lo juro por la horca, " + GetFullName(npchar) + ", ¡no dejaré que me engañes! ¡Muéstrame tus mercancías ahora mismo!", "Echemos un vistazo a tus mercancías, " + GetAddress_FormToNPC(NPChar) + ".")), NPCharRepPhrase(npchar, pcharrepphrase("¡Eso es seguro! ¡Los muertos no morderán! Ahora, ¿qué tienes en tu bodega?", "Será mejor que te ocupes de tus asuntos, buen hombre. ¿Qué tipo de mercancías puedes ofrecerme?"), pcharrepphrase("Vendrá un día en que te conviertas en mi premio, je-je. Es broma. Muéstrame tus mercancías.", "Hablemos de nuestros asuntos comerciales, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + "")), NPCharRepPhrase(npchar, pcharrepphrase("¿Qué quiero? ¡Quiero comprar algo!", "Beber te llevará a la tumba, " + GetFullName(npchar) + ". Quiero echar un vistazo a tus mercancías."), pcharrepphrase("¡Conozco tus descuentos! ¡Dos libras de cacao al precio de tres! Ahora muéstrame tus mercancías.", "Eso siempre es bueno. Regateemos, entonces.")), "Muéstrame tus mercancías. Menos se dice, más rápido se remedia. Tengo prisa.", npchar, Dialog.CurrentNode);
		link.l1.go = "market";
		link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar, pcharrepphrase("Oh, realmente me gustaría apuñalar a alguien, Bien, vamos al grano.", "Pasemos a otros asuntos, mi buen hombre."), pcharrepphrase("¡Caramba! ¡Estoy aquí por un negocio diferente!", "Quiero hablar contigo sobre un negocio particular, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + ".")), NPCharRepPhrase(npchar, pcharrepphrase("¡Tengo negocios contigo, viejo pirata!", "¡Pongámonos manos a la obra, camarada!"), pcharrepphrase("¡Juro por el diablo, no me engañarás, granuja! ¡Tengo asuntos diferentes contigo!", "Estoy totalmente de acuerdo, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + ", quería discutir otros asuntos contigo.")), NPCharRepPhrase(npchar, pcharrepphrase("¿Ya estás cargado? Tengo asuntos contigo.", "Vine aquí no para comerciar, buen hombre. Tengo otros asuntos."), pcharrepphrase("¡Que el trueno te parta por precios como esos! Tengo negocios contigo.", "Los descuentos siempre son agradables, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + ", pero tengo un negocio diferente contigo.")), NPCharRepPhrase(npchar, pcharrepphrase("¡Muerde la lengua, viejo borracho, tengo asuntos contigo!", "Estás enfermo por el ron, supongo. No es que me caigas bien, tampoco. Vamos al grano."), pcharrepphrase("¡Ya me has estafado, granuja! Tengo asuntos contigo.", "Tu ironía es inapropiada. Tengo otros asuntos contigo.")), npchar, Dialog.CurrentNode);
		link.l2.go = "business";
		/*link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar,pcharrepphrase("Primero los negocios, luego la diversión. Quiero preguntarte algo.","Ahora no. Necesito información."),pcharrepphrase("¡Al diablo con tus precios! Primero vas a decirme todo lo que necesito.","Con gusto. Quería preguntar algo.")),NPCharRepPhrase(npchar,pcharrepphrase("Gracias por el consejo, viejo asesino. Quería preguntarte algo.","Tenía una pregunta particular."),pcharrepphrase("Oro puede esperar. Quería preguntarte algo.","Sí, estoy de acuerdo. Quería preguntarte algo.")),NPCharRepPhrase(npchar,pcharrepphrase("Creo que sabes lo que iba a preguntar.","Espero que respondas a mi pregunta."),pcharrepphrase("¿Puedes pensar en algo más aparte de tus etiquetas de precio? Porque de eso iba a preguntarte.","Eso no me interesa. Necesito información.")),NPCharRepPhrase(npchar,pcharrepphrase("¡No te emociones demasiado, amigo! Solo iba a hacerte una pregunta.","No te emociones demasiado, o te dará un ataque. Solo responde una pregunta y me iré"),pcharrepphrase("No espero que digas algo inteligente, ya que tienes el cerebro de una cucaracha. Pero seguramente debes saber algo."," No te retrasaré por mucho tiempo. Solo una pregunta.")),npchar,Dialog.CurrentNode);*/
		// link.l3 = "Estoy en otro asunto.";
		// link.l3.go = "quests";
		//  --> Jason, генер почтового курьера 2 уровня
		if (CheckAttribute(PChar, "questTemp.WPU.Postcureer.LevelUp"))
		{
			if (pchar.questTemp.WPU.Postcureer.TargetPortmanID == npchar.id)
			{
				link.l12 = "He traído una lista de precios de la ciudad de " + XI_ConvertString("Colony" + pchar.questTemp.WPU.Postcureer.StartCity + "Gen") + ".";
				link.l12.go = "Postcureer_LevelUp_ForAll";
			}
		}
		//<--генер почтового курьера 2 уровня

		// Jason --> мини-квест Дефицитный товар
		if (CheckAttribute(pchar, "questTemp.Wine.Trader") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
		{
			link.l13 = "Me gustaría comprar un lote de vino europeo, cincuenta o sesenta botellas. Me dijeron que tenías suficiente en stock..";
			link.l13.go = "Wine_Trader";
		}
		if (CheckAttribute(pchar, "questTemp.Wine.Repeat2") && NPChar.location == pchar.questTemp.Wine.City + "_store" && CheckCharacterItem(pchar, "letter_1") && !CheckAttribute(pchar, "questTemp.Wine.fail"))
		{
			link.l13 = "Hola de nuevo. Por favor, echa un vistazo a esta carta, quizás reconsideres tu posición respecto a venderme vino.";
			link.l13.go = "Wine_Repeat2";
		}
		if (CheckAttribute(pchar, "questTemp.Wine.wait") && NPChar.location == pchar.questTemp.Wine.City + "_store" && !CheckAttribute(pchar, "questTemp.Wine.fail"))
		{
			link.l13 = "Soy yo otra vez. ¿Podemos reanudar nuestro trato interrumpido de vino? Logré reunir suficiente dinero.";
			link.l13.go = "Wine_Price";
		}
		// <-- мини-квест Дефицитный товар

		// туториал Мартиника
		if (CheckAttribute(pchar, "questTemp.Sharlie.Lock") && NPChar.City == "FortFrance")
		{
			if (!CheckAttribute(npchar, "quest.storehelper") && pchar.questTemp.Sharlie == "ship")
			{
				Link.l2 = "Escuche, monsieur, estoy buscando un trabajo. No como un trabajo a tiempo completo o cargar sacos de carga, sino más bien hacer recados, por así decirlo. ¿Por casualidad necesita asistencia?";
				Link.l2.go = "Sharlie_storehelper";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "return")
			{
				Link.l2 = "He completado tu recado. Encontré a Gralam Lavoie.";
				Link.l2.go = "Sharlie_storehelper_2";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "choise")
			{
				Link.l2 = "Conozca a su nuevo asistente, monsieur.";
				Link.l2.go = "Sharlie_storehelper_11";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Storehelper") && pchar.questTemp.Sharlie.Storehelper == "final")
			{
				Link.l2 = "Soy yo otra vez, monsieur. He venido por mi recompensa.";
				Link.l2.go = "Sharlie_storehelper_13";
			}
			if (CheckAttribute(pchar, "questTemp.Sharlie.Junglejew") && !CheckAttribute(npchar, "quest.junglejew"))
			{
				link.l4 = "Échale un vistazo a estos pendientes, monsieur. Los encontré en el cuerpo de un bandido que fue asesinado en la jungla. Es claramente el trabajo de un fino joyero que, estoy seguro, no es de por aquí. ¿Hay algo que puedas decir sobre estos pendientes?";
				link.l4.go = "Sharlie_junglejew";
			}
		}

		if (CheckAttribute(pchar, "GenQuest.EncGirl"))
		{
			if (pchar.GenQuest.EncGirl == "toLoverFather" && pchar.GenQuest.EncGirl.LoverFather == "store_keeper" && pchar.GenQuest.EncGirl.LoverCity == npchar.city)
			{
				link.l9 = "Hola, vine por invitación de su hijo.";
				link.l9.go = "EncGirl_4";
				pchar.quest.EncGirl_GetLoverFather.over = "yes";
			}
			if (pchar.GenQuest.EncGirl == "toParents" || pchar.GenQuest.EncGirl == "FindLover")
			{
				if (pchar.GenQuest.EncGirl.Father == "store_keeper" && npchar.city == pchar.GenQuest.EncGirl.city)
				{
					link.l9 = "Esto es sobre tu hija...";
					link.l9.go = "EncGirl_1";
				}
			}
		}
		link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar, pcharrepphrase("Nos vemos, viejo borracho.", "Que tengas un buen día, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + "."), pcharrepphrase("¡Caramba! No te vayas a ninguna parte, volveré de nuevo.", "Fue un placer tenerte aquí, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + "¡Adiós!")), NPCharRepPhrase(npchar, pcharrepphrase("¡Zarpad!", "Adiós, buen hombre."), pcharrepphrase("¡Eh! ¿Qué estás escondiendo ahí? ¿Ron? ¿No?! Está bien, iré a humedecerme la garganta.", "Lo siento, pero tengo un asunto urgente en la ciudad.")), NPCharRepPhrase(npchar, pcharrepphrase("¡Eh! ¡Bueno, nos vemos!", "Tengo que irme. Adiós, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + "."), pcharrepphrase("¡Y ni se te ocurra discutir conmigo! ¡No tengo tiempo para esto!", "Tal vez, necesito ir y ver qué sucede en mi barco. Adiós, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + ".")), NPCharRepPhrase(npchar, pcharrepphrase("¿Qué tal, viejo amigo? Soy yo, " + GetFullName(pchar) + "¡Vete a dormir para despejarte, volveré más tarde!", "Me temo que tu hígado te acabará antes de que tenga la oportunidad de volver a verte."), pcharrepphrase("¡Sigue contando tus guineas y doblones, viejo zorro! Volveré.", "¡Me alegró verte, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + "!")), npchar, Dialog.CurrentNode);
		link.l5.go = "exit";
		break;

	case "Helen_node_1":
		dialog.text = "¿Qué puedo hacer por ti? ¿Abastecer el Arcoíris, vender algo de botín? Dudo que estés interesado en los fletes rentables actuales, ja-ja.";
		link.l1 = HeroStringReactionRepeat(NPCharRepPhrase(npchar, pcharrepphrase("¡Muéstrame lo que tienes, viejo pirata!", "Solo quería echar un vistazo a sus mercancías, buen hombre."), pcharrepphrase("Juro por la horca, " + GetFullName(npchar) + ", ¡no dejaré que me distraigas! ¡Enséñame tus mercancías ahora mismo!", "Echemos un vistazo a tus mercancías, " + GetAddress_FormToNPC(NPChar) + ".")), NPCharRepPhrase(npchar, pcharrepphrase("¡Eso es seguro! ¡Los muertos no morderán! Ahora, ¿qué tienes en tu bodega?", "Será mejor que te ocupes de tus asuntos, buen hombre. ¿Qué tipo de mercancías puedes ofrecerme?"), pcharrepphrase("Vendrá un día en que te conviertas en mi premio, je-je. Solo bromeo. Muéstrame tus mercancías.", "Hablemos de nuestros asuntos comerciales, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + "")), NPCharRepPhrase(npchar, pcharrepphrase("¿Qué quiero? ¡Quiero comprar algo!", "Beber te llevará a la tumba, " + GetFullName(npchar) + ". Quiero echar un vistazo a tus mercancías."), pcharrepphrase("¡Conozco tus descuentos! ¡Dos libras de cacao al precio de tres! Ahora muéstrame tus mercancías.", "Eso siempre es bueno. Regateemos, entonces.")), "Muéstrame tus mercancías. Menos se dice, antes se remienda. Tengo prisa.", npchar, Dialog.CurrentNode);
		link.l1.go = "market";
		link.l2 = HeroStringReactionRepeat(NPCharRepPhrase(npchar, pcharrepphrase(" Oh, me gustaría apuñalar a alguien, Muy bien, vamos a entrar en materia. ", "Pasemos a otros asuntos, buen hombre."), pcharrepphrase("¡Caramba! ¡Estoy aquí por un negocio diferente!", "Quiero hablar contigo sobre un negocio en particular, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + ".")), NPCharRepPhrase(npchar, pcharrepphrase("¡Tengo asuntos contigo, viejo pirata!", "¡Vamos al grano, camarada!"), pcharrepphrase("¡Juro por el diablo, que no me engañarás, bribón! ¡Tengo asuntos diferentes contigo!", "Estoy completamente de acuerdo, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + ", quería discutir otros asuntos contigo.")), NPCharRepPhrase(npchar, pcharrepphrase("¿Ya has cargado todo? Tengo negocios contigo.", "No vine aquí para comerciar, buen hombre. Tengo otros asuntos."), pcharrepphrase("¡Que el trueno te parta por esos precios! Tengo negocios contigo.", "Los descuentos siempre son agradables, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + ", pero tengo un negocio diferente contigo.")), NPCharRepPhrase(npchar, pcharrepphrase("¡Aguanta la lengua, viejo borracho, tengo negocios contigo!", "Estás enfermo por culpa del ron, supongo. Tampoco es que me agrades mucho. Vamos a lo que importa."), pcharrepphrase("¡Ya me has timado, granuja! Tengo asuntos contigo.", "Tu ironía es inapropiada. Tengo otros asuntos contigo.")), npchar, Dialog.CurrentNode);
		link.l2.go = "business";
		link.l3 = HeroStringReactionRepeat(NPCharRepPhrase(npchar, pcharrepphrase("Primero negocios, luego diversión. Quiero preguntarte algo.", "Ahora no. Necesito información."), pcharrepphrase("¡Al diablo con tus precios! Primero me vas a decir todo lo que necesito.", "Con mucho gusto. Quería preguntar algo.")), NPCharRepPhrase(npchar, pcharrepphrase("Gracias por el consejo, viejo asesino. Quería preguntarte algo.", "Tenía una pregunta en particular."), pcharrepphrase("El oro puede esperar. Quería preguntarte algo.", "Sí, estoy de acuerdo. Quería preguntarte algo.")), NPCharRepPhrase(npchar, pcharrepphrase("Creo que sabes lo que iba a preguntar.", "Espero que respondas a mi pregunta."), pcharrepphrase("¿Puedes pensar en algo además de tus etiquetas de precio? Porque de eso quería preguntarte.", "Eso no me interesa. Necesito información.")), NPCharRepPhrase(npchar, pcharrepphrase("¡No te emociones demasiado, amigo! Solo iba a hacerte una pregunta.", "No te emociones demasiado, o te dará un ataque. Solo responde una pregunta, y me iré"), pcharrepphrase("No espero que digas algo inteligente, ya que tienes el cerebro de una cucaracha. Pero seguramente debes saber algo.", "No te retrasaré mucho. Solo una pregunta.")), npchar, Dialog.CurrentNode);
		link.l3.go = "quests";
		link.l5 = HeroStringReactionRepeat(NPCharRepPhrase(npchar, pcharrepphrase("Nos vemos, viejo borracho.", "Que tengas un buen día, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + "."), pcharrepphrase("¡Caramba! No te vayas a ninguna parte, volveré de nuevo.", "Fue un placer tenerte aquí, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + "¡Adiós!")), NPCharRepPhrase(npchar, pcharrepphrase("¡Levamos anclas!", "Adiós, buen hombre."), pcharrepphrase("¡Eh! ¿Qué estás escondiendo ahí? ¿Ron? ¿No?! Está bien, voy a humedecer mi garganta.", "Lo siento, pero tengo asuntos urgentes en la ciudad.")), NPCharRepPhrase(npchar, pcharrepphrase("¡Eh! ¡Bueno, nos vemos!", "Tengo que irme. Adiós, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + "."), pcharrepphrase("¡Y ni se te ocurra discutir conmigo! ¡No tengo tiempo para esto!", "Tal vez, necesito ir y ver qué pasa en mi barco. Adiós, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + ".")), NPCharRepPhrase(npchar, pcharrepphrase("¿Qué tal, viejo amigo? Soy yo, " + GetFullName(pchar) + "¡Duerme hasta que se te pase la borrachera, volveré más tarde!", "Me temo que tu hígado te acabará antes de que tenga la oportunidad de volver a verte."), pcharrepphrase("¡Sigue contando tus guineas y doblones, viejo zorro! Volveré.", "¡Me alegró verte, " + GetAddress_FormToNPC(NPChar) + " " + GetFullName(npchar) + "!")), npchar, Dialog.CurrentNode);
		link.l5.go = "exit";
		break;

	case "market":
		// navy -->
		// занят ПГГ
		if (CheckFreeServiceForNPC(NPChar, "Store") != -1) // to_do имя сунуть
		{
			dialog.text = "Lo siento, pero estoy demasiado ocupado en este momento. ¡Tantos clientes! Vuelve mañana.";
			link.l1 = "¿Oh, de veras? Bueno, volveré más tarde, entonces.";
			link.l1.go = "exit";
			break;
		}
		// navy <--
		dialog.text = RandPhraseSimple("Tengo balas redondas, lonas, medicinas, madera preciosa y otros bienes. ¿En qué estás interesado?", "¿Quieres comprar azúcar y especias? ¿O quizás ron y pólvora?");
		link.l1 = pcharrepphrase(LinkRandPhrase("Tengo un montón de botín en mi bodega! El dinero no tiene olor, ¿verdad?", "Necesito deshacerme del botín en mi bodega y llenarla con tu oro. ¡Ja-ja!", "¡Oh, sé que venderías a tu madre por un saco de doblones de peso completo! Pero solo necesito reponer mis provisiones."), LinkRandPhrase("Quiero vender mi cargamento y reponer suministros.", "Quiero comprar mercancías para la venta.", "Muéstrame las balas de cañón, las bombas y cosas así."));
		link.l1.go = "trade_1";

		if (CheckFunctionalTreasurer() && CheckAttribute(PChar, "TransferGoods.Enable")) // Автозакупка товаров
		{
			link.l5 = "Mi intendente hará todas las compras necesarias...";
			link.l5.go = "TransferGoods";
		}

		link.l3 = pcharrepphrase(RandPhraseSimple("Me voy sin comerciar. ¡Nos vemos!", "Iré a humedecer mi garganta. ¡Tú quédate ahí!"), RandPhraseSimple("No, no tengo tiempo para comerciar en este momento. Adiós.", "Lo siento, tengo asuntos urgentes que atender. ¡Adiós!"));
		link.l3.go = "exit";
		break;

	case "EncGirl_1":
		dialog.text = "Soy todo oídos.";
		link.l1 = "He traído a tu fugitivo.";
		link.l1.go = "EncGirl_2";
		break;

	case "EncGirl_2":
		dialog.text = "¡Oh, capitán, muchas gracias! ¿Cómo está ella? ¿Está herida? Ha pasado un día desde que se escapó, maldita chica. ¿Parece que voy a hacerle algún daño? Le he encontrado un esposo. He arreglado un matrimonio. Un prometido rico y joven. Puede que tenga mal aspecto, pero a quién diablos le importa la cara. ¡No! Siempre intenta salirse con la suya. Igual que su madre siempre lo hacía, ¡llamas!\nAunque, no habría nacido si su madre no hubiera huido con algún idiota prometedor hace tiempo... bueno, lo que sea... La juventud es ingenua, estúpida y cruel.";
		link.l1 = "Por supuesto, tú eres el padre y te corresponde decidir, pero yo no me apresuraría con la boda...";
		link.l1.go = "EncGirl_3";
		break;

	case "EncGirl_3":
		dialog.text = "¿Qué sabes tú? ¿Tienes hijos propios? ¿No? Háblame cuando los tengas... Sí... Prometí una recompensa al hombre que la traiga de vuelta, aquí, tómala.";
		link.l1 = "Gracias. Y mantén un ojo en ella. Tengo el presentimiento de que no se detendría ahí.";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("EncGirl_ToLoverParentsExit");
		break;

	case "EncGirl_4":
		if (sti(pchar.GenQuest.EncGirl.LoverFatherAngry) == 0)
		{
			dialog.text = "Oh, entonces eres " + GetSexPhrase("ese capitán, que trajo", "esa muchacha, que trajo") + " ¿mi hijo pródigo con una joven novia?";
			link.l1 = "Sí, les ayudé a escapar.";
			link.l1.go = "EncGirl_5";
		}
		else
		{
			dialog.text = "Oh, allí " + GetSexPhrase("él es, nuestro benefactor", "ella es, nuestra benefactora") + "¿Esperando una recompensa, me imagino?";
			link.l1 = "Bueno, estoy bien sin recompensa, pero con tus gracias bastará.";
			link.l1.go = "EncGirl_6";
		}
		break;

	case "EncGirl_5":
		dialog.text = "Le estoy muy agradecido por no haber abandonado a mi hijo en momentos difíciles y haberle ayudado a encontrar una salida a una situación delicada. Permítame agradecerle y por favor acepte esta modesta suma y un regalo de mi parte personalmente.";
		link.l1 = "Gracias. Ayudar a esta joven pareja fue un placer.";
		link.l1.go = "EncGirl_5_1";
		break;

	case "EncGirl_6":
		dialog.text = "¿Gracias? ¿Qué gracias?! ¡Ese cabezahueca ha estado holgazaneando sin trabajo durante medio año y míralo, tiene suficiente tiempo para amoríos! ¡Cuando yo tenía su edad, ya dirigía mi propio negocio! ¡Pff! Un gobernador tiene una hija casadera y ese zoquete ha traído a una buscona sin familia ni raíces a mi casa y se ha atrevido a pedir mi bendición!";
		link.l1 = "Hmm... ¿Aparentemente, no crees en los sentimientos sinceros?";
		link.l1.go = "EncGirl_6_1";
		break;

	case "EncGirl_5_1":
		AddMoneyToCharacter(pchar, sti(pchar.GenQuest.EncGirl.sum));
		GiveItem2Character(pchar, pchar.GenQuest.EncGirl.item);
		AddQuestRecord("JungleGirl", "18");
		CloseQuestHeader("JungleGirl");
		DeleteAttribute(pchar, "GenQuest.EncGirl");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "EncGirl_6_1":
		dialog.text = "¿Qué sentimientos? ¿De qué clase de sentimientos estás hablando? Sentimientos... ¡cómo se puede ser tan frívolo a tu edad! ¡Qué vergüenza que complazcas a los jóvenes en sus caprichos y actúes como un alcahuete! No solo has sacado a una chica de su hogar, sino que también arruinaste la vida de mi novato. No habrá agradecimientos para ti. Adiós.";
		link.l1 = "Está bien, y lo mismo para usted...";
		link.l1.go = "EncGirl_6_2";
		break;

	case "EncGirl_6_2":
		ChangeCharacterComplexReputation(pchar, "nobility", -1);
		AddQuestRecord("JungleGirl", "19");
		AddQuestUserData("JungleGirl", "sSex", GetSexPhrase("", ""));
		AddQuestUserData("JungleGirl", "sSex1", GetSexPhrase("", ""));
		CloseQuestHeader("JungleGirl");
		DeleteAttribute(pchar, "GenQuest.EncGirl");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	// Warship. Автозакупка товаров -->
	case "TransferGoods":
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);

		if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
		{
			dialog.text = LinkRandPhrase("...Ya está hecho. Ahora lo único que queda es decidir qué barco cargar.", "Tu tesorero ya ha hecho eso. Decidamos ahora, qué barco será cargado.", "Sí, " + PChar.name + ", lo sé. Ya me hizo una visita. Ahora, ¿qué barco vamos a cargar?");

			for (i = 0; i < COMPANION_MAX; i++)
			{
				cn = GetCompanionIndex(PChar, i);
				if (cn > 0)
				{
					chref = GetCharacter(cn);
					if (!GetRemovable(chref))
						continue;

					attrL = "l" + i;
					Link.(attrL) = "It will be " + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
					Link.(attrL).go = "TransferGoodsTo_" + chref.id;
				}
			}

			Link.l99 = "He cruzado mi mente, nada necesita.";
			Link.l99.go = "exit";
		}
		else // Корабля нету
		{
			dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("¿Me estás tomando el pelo? ¿Dónde está tu barco? ¡No la veo en el muelle!", "¡Juro por el diablo, no me engañarás! ¡Tu barco no está en el muelle!"), pcharrepphrase("No veo tu barco en el puerto, capitán " + GetFullName(pchar) + ". Espero que no sea el 'Holandés Errante'?", "Capitán, es mucho más fácil cargar la mercancía desde el muelle. Y prefiero hacerlo de esa manera. Traiga su barco rápido y regrese."));
			link.l1 = NPCharRepPhrase(npchar, pcharrepphrase(" " + RandSwear() + "¡Qué problema! Está bien, viejo astuto, ¡nos vemos pronto!", "No quería engañarte, " + GetFullName(npchar) + ", un barco está al otro lado de la isla."), pcharrepphrase("No. Mi barco se llama 'Perla Negra'. ¿Por qué te pusiste pálido? ¡Jaja! ¡Solo bromeo!", "Gracias por el consejo, necesariamente lo usaré."));
			link.l1.go = "exit";
		}
		break;

	case "TransferGoods_2": // Тут уже не проверяем, есть корабль или нету (выбрали корабль, в который груз не помещается)
		dialog.text = LinkRandPhrase("Entonces, capitán, ¿qué barco vamos a cargar?", "Entonces, ¿cuál barco debe ser cargado?", PChar.name + ", ¿en cuál bodega del barco cargaremos las mercancías?");

		for (i = 0; i < COMPANION_MAX; i++)
		{
			cn = GetCompanionIndex(PChar, i);
			if (cn > 0)
			{
				chref = GetCharacter(cn);
				if (!GetRemovable(chref))
					continue; // Если квестовый - пропускаем

				attrL = "l" + i;
				Link.(attrL) = "It will be " + XI_ConvertString(RealShips[sti(chref.Ship.Type)].BaseName) + " '" + chref.Ship.Name + "'.";
				Link.(attrL).go = "TransferGoodsTo_" + chref.id;
			}
		}

		Link.l99 = "He cambiado de opinión, no necesito nada.";
		Link.l99.go = "exit";
		break;

	case "TransferGoods_Start":
		chref = CharacterFromID(NPChar.CharToTransferGoodsID);

		iQuantityGoods = TransferGoods_CalculateWeight(chref);

		if (GetCargoFreeSpace(chref) >= iQuantityGoods)
		{
			if (TransferGoods_StartTransfer(chref, NPChar.City) != 0)
			{
				dialog.text = LinkRandPhrase("¡Todo está listo! La carga del barco seleccionado ha comenzado.", "Está bien, la carga de mercancías en el barco seleccionado ha comenzado.", "  Capitán,   la carga de mercancías en el barco seleccionado ha comenzado.");
				link.l1 = "Gracias. Un placer hacer negocios contigo.";
				link.l1.go = "exit";
				SetPriceListByStoreMan(rColony); // mitrokosta обновляем список цен
				WaitDate("", 0, 0, 0, 1, 0);	 // Крутим время
			}
			else
			{
				dialog.text = LinkRandPhrase("¡Capitán, todos los bienes solicitados por su tesorero ya están a bordo del barco que indicó!", "¡Capitán, todas las mercancías ya están a bordo del barco que indicaste!", "Capitán, ese barco no necesita servicio, ya que todas las mercancías ya están allí.");
				link.l1 = "Sí, claro.";
				link.l1.go = "exit";
				link.l2 = "Supongo que tendré que elegir otro barco, entonces.";
				link.l2.go = "TransferGoods_2";
			}
		}
		else
		{
			dialog.text = LinkRandPhrase("Me temo que un barco de ese tipo simplemente no puede llevar tanto.", "¡Capitán, tu barco no podrá contener tanta carga!", "¡Capitán, la bodega de su barco no puede llevar tanto cargamento!");
			link.l1 = "Sí, tienes razón. Necesitaré elegir otro barco.";
			link.l1.go = "TransferGoods_2";
			link.l2 = "He estado pensando... No necesito comprar nada.";
			link.l2.go = "exit";
		}
		break;
		// <-- Автозакупка товаров

	case "trade_1":
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
		{
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
			Pchar.PriceList.StoreManIdx = rColony.index; // boal 27.02.05
			LaunchStore(sti(rColony.StoreNum));
		}
		else
		{
			dialog.text = NPCharRepPhrase(npchar, pcharrepphrase("¿Me estás tomando el pelo? ¿Dónde está tu barco? ¡No la veo en el muelle!", "¡Juro por el diablo, no me engañarás! ¡Tu barco no está en el muelle!"), pcharrepphrase("No veo tu barco en el puerto, capitán " + GetFullName(pchar) + ". Espero que no sea el 'Holandés Errante'?", "Capitán, es mucho más fácil cargar la mercancía desde el muelle. Trae tu barco rápido y regresa."));
			link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" + RandSwear() + "¡Qué problema! Está bien, viejo pillo, ¡nos vemos pronto!", "No quería engañarte, " + GetFullName(npchar) + ", un barco está al otro lado de la isla."), pcharrepphrase("No. Mi barco se llama 'Perla Negra'. ¿Por qué te pusiste pálido? ¡Ja ja! ¡Solo bromeaba!", "Gracias por el consejo, lo usarán."));
			link.l1.go = "exit"; //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		}
		break;

	case "storage_0":
		NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage);
		if (sti(NPChar.MoneyForStorage) > 0)
		{
			dialog.text = "En cuanto al alquiler, todavía me debes " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ".";
			if (sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Está bien, pagaré el alquiler ahora.";
				link.l1.go = "storage_3";
			}
			else
			{
				link.l1 = "Volveré más tarde.";
				link.l1.go = "exit";
			}
		}
		else
		{
			dialog.text = "Ven.";
			link.l1 = "Gracias.";
			link.l1.go = "storage_2";
		}
		link.l2 = "No, he cambiado de opinión.";
		link.l2.go = "exit";
		break;

	case "storage_01":
		NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
		dialog.text = "Sí, tengo un almacén en el puerto, puede contener 50000 quintales de carga. Para " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + " por mes puedo proporcionar custodia de tus bienes. " + "Esto incluye la vigilancia, protección contra la humedad y luchar contra las ratas. ¿Qué dices? Además... necesitaré el pago de un mes por adelantado.";
		link.l1 = "Traje. ¿Puedo echarle un vistazo? ¿Tienes muchas ratas allí?";
		link.l1.go = "storage_1";
		link.l2 = "No, solo estoy preguntando. Puedo usarlo cuando sea necesario...";
		link.l2.go = "exit";
		break;

	case "storage_1":
		NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
		dialog.text = "Como dije, requiero el pago de un mes por adelantado. ¡Y nada de ratas!";
		if (sti(pchar.money) >= sti(NPChar.MoneyForStorage))
		{
			link.l1 = "Eres... bastante mercantil, debo decir. Aquí tienes tu dinero, alquilaré este cobertizo.";
			link.l1.go = "storage_11";
		}
		else
		{
			link.l1 = "Es usted... bastante mercantil, debo decir. Muy bien, regresaré pronto con el dinero.";
			link.l1.go = "exit";
		}
		break;

	case "storage_11":
		AddMoneyToCharacter(pchar, -makeint(NPChar.MoneyForStorage));
		NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
		NPChar.Storage.Activate = true;
		Achievment_Set("ach_67"); // ugeen 2016
		SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LaunchStorage(sti(rColony.StoreNum));
		break;

	case "storage_2":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LaunchStorage(sti(rColony.StoreNum));
		break;

	case "storage_3":
		AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage));
		NPChar.MoneyForStorage = GetStoragePriceExt(NPChar, pchar);
		NPChar.Storage.MoneyForStorage = NPChar.MoneyForStorage;
		SaveCurrentNpcQuestDateParam(NPChar, "Storage.Date");
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		LaunchStorage(sti(rColony.StoreNum));
		break;

	case "storage_04":
		dialog.text = "¿Ya te vas? Qué lástima, es realmente un lugar excelente en condiciones inmejorables. Te aseguro que no encontrarás una oferta como esta en ninguna otra parte del Caribe.";
		link.l1 = "Dije, absolver. ¿O me estás sugiriendo que pague por almacenar aire? Busca otro arrendatario.";
		link.l1.go = "storage_4";
		link.l2 = "¿En ningún lugar del Caribe, dices? Muy bien, lo dejaré de lado por un tiempo, entonces.";
		link.l2.go = "exit";
		break;

	case "storage_4":
		NPChar.MoneyForStorage = GetNpcQuestPastMonthParam(NPChar, "Storage.Date") * sti(NPChar.Storage.MoneyForStorage);
		if (sti(NPChar.MoneyForStorage) > 0)
		{
			dialog.text = "Y por el alquiler, todavía me debes " + FindRussianMoneyString(sti(NPChar.MoneyForStorage)) + ".";
			if (sti(pchar.money) >= sti(NPChar.MoneyForStorage))
			{
				link.l1 = "Bien.";
				link.l1.go = "storage_5";
			}
		}
		else
		{
			dialog.text = "Recoge tus mercancías, y cerraré el almacén.";
			link.l1 = "Bien.";
			link.l1.go = "storage_6";
		}
		break;

	case "storage_5":
		SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
		AddMoneyToCharacter(pchar, -sti(NPChar.MoneyForStorage));
		NPChar.Storage.NoActivate = true;
		DeleteAttribute(NPChar, "Storage.Activate");
		DialogExit();
		break;

	case "storage_6":
		SetStorageGoodsToShip(&stores[sti(rColony.StoreNum)]);
		DeleteAttribute(NPChar, "Storage.Activate");
		NPChar.Storage.NoActivate = true;
		DialogExit();
		break;

	case "business":
		iTest = 0;

		// Jason --> генератор Сомнительное предложение
		/*if (hrand(3) == 1 && !CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && !CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && sti(npchar.nation) != PIRATE && 7-sti(RealShips[sti(pchar.ship.type)].Class) > 0)
		{
			if (!CheckAttribute(npchar, "Contraoffer") || GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30)
			{
				dialog.text = "¡Oh! Llegas justo a tiempo, capitán. Me gustaría pedirte que me hagas un favor.";
				link.l1 = "Escuchemos.";
				link.l1.go = "Contraoffer";
				break;
			}
		}

		if (CheckAttribute(pchar, "GenQuest.Contraoffer.Trader") && NPChar.location == pchar.GenQuest.Contraoffer.Trader.City + "_store")
		{
			dialog.text = "Soy todo oídos, capitán.";
			link.l5 = "He traído tu pedido.";
			link.l5.go = "Contraoffer_check";
		}

		if (!CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves") && sti(npchar.quest.Contraoffer.chance) == 2 && GetNpcQuestPastDayParam(npchar, "Contraoffer") >= 30) //единичный вариант за всю игру, ака 'пасхалка'
		{
			dialog.text = "¡Oh! Llegas justo a tiempo, capitán. Necesito un favor especial.";
			link.l5 = "Escuchemos.";
			link.l5.go = "Contraoffer_slaves";
			break;
		}

		if (CheckAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes") && NPChar.location == pchar.GenQuest.Contraoffer.Slaves.City + "_store")
		{
			dialog.text = "Soy todo oídos, capitán.";
			link.l5 = "Te he traído los esclavos.";
			link.l5.go = "Contraoffer_slaves_check";
		}*/
		// <-- генератор Сомнительное предложение

		// Jason --> генератор Неудачливый вор
		if (CheckAttribute(pchar, "GenQuest.Device.Shipyarder") && NPChar.location == pchar.GenQuest.Device.Shipyarder.City + "_store" && pchar.GenQuest.Device.Shipyarder == "begin" && !CheckAttribute(npchar, "quest.Device"))
		{
			link.l16 = "Escucha, estás comerciando con todo tipo de mercancías... ¿Ayer o hoy alguien te ofreció comprar " + pchar.GenQuest.Device.Shipyarder.Type + "?";
			link.l16.go = "Device_Trader";
		}
		// <-- генератор Неудачливый вор

		// Jason --> генератор Место под солнцем
		//  belamour legendary edition втречается чаще
		if (!CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && !CheckAttribute(npchar, "quest.Sunplace") && sti(npchar.nation) != PIRATE && sti(pchar.rank) < 20 && hrand(2) == 2 && !CheckAttribute(pchar, "questTemp.Shadowtrader_Block"))
		{
			dialog.text = "Capitán, me gustaría pedirle un favor y estoy dispuesto a pagarle generosamente, si acepta.";
			link.l1 = "Interesante. Bueno, ¿cuál es el problema?";
			link.l1.go = "Sunplace_begin";
			break;
		}

		if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store")
		{
			dialog.text = "Capitán, me alegra verte. Ya sé que has cumplido mi solicitud respecto a " + pchar.GenQuest.Sunplace.Trader.Enemyname + ".";
			link.l1 = "¡Je! Eso es seguro. " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name"))) + " " + pchar.GenQuest.Sunplace.Trader.ShipName + " y la carga, " + GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods)) + ", ya no pertenecen a tu rival.";
			link.l1.go = "Sunplace_complete";
			break;
		}

		if (CheckAttribute(pchar, "GenQuest.Sunplace.Trader") && pchar.GenQuest.Sunplace.Trader == "complete_murder" && npchar.location == pchar.GenQuest.Sunplace.Trader.City + "_store")
		{
			dialog.text = "Mi Señor, capitán... ¿Por qué lo mataste? ¡Solo te pedí que hundieras su barco! Santa Virgen, ahora tengo la sangre de un hombre inocente en mis manos...";
			link.l1 = "¡Eh! ¿Qué te pasa, " + npchar.name + "¿A quién le importa?, nunca más te molestará, ¡y eso es lo que importa!";
			link.l1.go = "Sunplace_complete_murder";
			break;
		}
		// <-- генератор Место под солнцем

		// navy -->
		// занят ПГГ
		iTmp = CheckAvailableTaskForNPC(NPChar, PGG_TASK_WORKONSTORE);
		if (iTmp != -1)
		{
			dialog.text = "Tenía un trabajo, pero " + GetFullName(&Characters[iTmp]) + "ya se ha comprometido a hacerlo por mí.";
			link.l1 = "¿Ah, de veras? Bueno, volveré más tarde, entonces.";
			link.l1.go = "exit";
			break;
		}
		// navy <--
		dialog.text = NPCharRepPhrase(npchar, "¿Qué negocio? ¡Cuéntamelo todo!", "Estoy escuchando. ¿De qué trato hablas?");
		ok = (rColony.from_sea == "") || (Pchar.location.from_sea == rColony.from_sea);
		if (sti(Pchar.Ship.Type) != SHIP_NOTUSED && ok)
		{
			if (CheckQuestAttribute("generate_trade_quest_progress", "begin") || CheckQuestAttribute("generate_trade_quest_progress", "failed"))
			{
				if (pchar.CargoQuest.TraderID == npchar.id)
				{
					link.l1 = RandPhraseSimple("Tengo un lote de mercancías para tu tienda en la bodega de mi barco.", "Mi barco fue fletado para entregar las mercancías a tu tienda. Los productos están siendo descargados ahora.");
					link.l1.go = "generate_quest_2";
				}
				else
				{
					if (!CheckQuestAttribute("generate_trade_quest_progress", "failed") && pchar.CargoQuest.GiveTraderID == npchar.id && GetNationRelation2MainCharacter(sti(characters[GetCharacterIndex(pchar.CargoQuest.TraderID)].nation)) == RELATION_ENEMY)
					{
						link.l1 = "Lamentablemente, me veo obligado a abandonar sus compromisos. La situación política no me permite entregar las mercancías.";
						link.l1.go = "generate_quest_cannot_done";
					}
					else
					{
						if (rand(1) == 1)
						{
							link.l1 = RandPhraseSimple("Puedo ofrecerte alquilar mi barco para transportar carga.", "Tengo un gran barco y puedo entregar cualquier carga donde lo necesites.");
							link.l1.go = "generate_quest_not_closed";
						}
					}
				}
			}
			else
			{
				link.l1 = "¿Te gustaría fletar un barco, " + GetAddress_FormToNPC(NPChar) + "? Tengo un navío fiable y una tripulación experimentada.";
				link.l1.go = "generate_quest";
			}
			link.l22 = "Estoy en otro asunto.";
			link.l22.go = "quests";
			// --> на кредитный генератор
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l3 = pcharrepphrase(RandPhraseSimple(" Oh,  realmente me agoté en el mar... Bueno,  camarada,  el dinero es un verdadero problema para mí en este momento. ", "Está bien, viejo zorro, discutamos nuestros asuntos financieros."), RandPhraseSimple("Me gustaría discutir los asuntos financieros contigo.", "Hablemos de asuntos financieros, tenemos que hablar de ellos."));
				,

					link.l3.go = "LoanForAll";
			}
			// квест мэра - на связь с нашим шпионом
			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "")
			{
				link.l4 = RandPhraseSimple("Estoy aquí a petición de un hombre. Su nombre es gobernador " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " me envió a ti. Se supone que debo recoger algo...");
				link.l4.go = "IntelligenceForAll";
			}

			// homo 25/06/06 слухи
			link.l6 = pcharrepphrase(RandPhraseSimple("¿Puedes contarme los últimos chismes? De todas formas, estás por aquí todo el día.", "No hagas alboroto, viejo embustero, mejor dime qué hay de nuevo en tierra firme."), RandPhraseSimple("Me parece que pasé una eternidad en el mar. ¿Qué hay de nuevo en tu región?", "Probablemente conoces las últimas noticias ¿Qué asunto de importancia ha acontecido?"));
			,

				link.l6.go = "rumours_trader";

			// ugeen --> склад товаров для ГГ
			if (CheckAttribute(NPChar, "Storage") && Pchar.location.from_sea == "Pirates_town")
			{
				if (CheckAttribute(NPChar, "Storage.Activate"))
				{
					link.l7 = "Llévame al almacén. Quiero ver en qué estado se encuentra.";
					link.l7.go = "storage_0";
					link.l8 = "He decidido liberar el almacén. No lo necesito ahora.";
					link.l8.go = "storage_04";
				}
				else
				{
					if (!CheckAttribute(NPChar, "Storage.NoActivate"))
					{
						link.l7 = "Disculpe, buen hombre, ¿no estará alquilando almacenes, por casualidad?";
						link.l7.go = "storage_01";
					}
				}
			}
			// <-- ugeen
			// Jason --> квест губера на поиск дезертира
			if (CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE)
			{
				link.l8 = "Verás, estoy tratando de encontrar a mi compañero, " + pchar.GenQuest.FindFugitive.Name + " es su nombre. En Port-Royal, la gente en la taberna me dijo que se dirigía a tu asentamiento. ¿Lo has conocido, por casualidad?";
				link.l8.go = "FindFugitiveSt";
			}
			//<-- поиск дезертира

			// <-- homo
			link.l99 = "No hay tiempo para charlas ahora.";
			link.l99.go = "no_quests";
		}
		else
		{
			link.l1 = NPCharRepPhrase(npchar, pcharrepphrase("" + RandSwear() + "Dejé el barco en el otro lado de la isla. ¡Volveré más tarde!", "Le ruego me disculpe, " + GetFullName(npchar) + ", volveré más tarde. Mi barco aún no ha llegado al muelle."), pcharrepphrase("¡Demonios! ¡Estos idiotas no prepararon el barco para la carga! ¡Volveré más tarde!", "Disculpe, debo dar órdenes para amarrar mi barco en el muelle."));
			link.l1.go = "exit";
			link.l22 = "Estoy en otro asunto.";
			link.l22.go = "quests";
			// --> на кредитный генератор
			if (CheckAttribute(pchar, "GenQuest.LoanChest.TakeChest") && sti(pchar.GenQuest.LoanChest.TargetIdx) == sti(NPChar.index))
			{
				link.l3 = pcharrepphrase(RandPhraseSimple("Oh, realmente estaba agotado en el mar... Bueno, camarada, el dinero es un verdadero problema para mí ahora mismo.", "Está bien, viejo zorro,   discutamos nuestros asuntos financieros."), RandPhraseSimple("Me gustaría discutir contigo los asuntos financieros.", "Discutamos asuntos financieros, tenemos que hablar."));
				,

					link.l3.go = "LoanForAll";
			}
			// квест мэра - на связь с нашим шпионом
			if (CheckAttribute(pchar, "GenQuest.Intelligence") && pchar.GenQuest.Intelligence.SpyId == npchar.id && pchar.GenQuest.Intelligence == "")
			{
				link.l7 = RandPhraseSimple("Estoy aquí por petición de un hombre. Su nombre es gobernador " + GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + ".", GetFullName(characterFromId(pchar.GenQuest.Intelligence.MayorId)) + " me envió a ti. Se supone que debo recoger algo...");
				link.l7.go = "IntelligenceForAll";
			}
			// Jason --> квест губера на поиск дезертира
			if (CheckAttribute(pchar, "GenQuest.FindFugitive") && sti(NPChar.nation) == PIRATE)
			{
				link.l8 = "Verás, estoy tratando de encontrar a mi compañero, " + pchar.GenQuest.FindFugitive.Name + " es su nombre. En Port-Royal, la gente en la taberna me dijo que se dirigía a tu asentamiento. ¿Lo has encontrado, por casualidad?";
				link.l8.go = "FindFugitiveSt";
			}
			//<-- поиск дезертира
		}
		break;

	case "generate_quest":
		if (npchar.quest.trade_date != lastspeak_date || bBettaTestMode)
		{
			npchar.quest.trade_date = lastspeak_date;
			// проверка враждебности нам страны торговца
			if (sti(NPChar.nation) != PIRATE && GetNationRelation2MainCharacter(sti(NPChar.nation)) == RELATION_ENEMY)
			{
				dialog.text = "¡No, no necesito tus servicios! Al menos, mientras seas enemigo de " + NationNameAblative(sti(NPChar.nation)) + ".";
				link.l1 = "En ese caso, adiós.";
				link.l1.go = "exit";
			}
			else
			{
				// проверка на проф пригодность -->
				if (isBadReputation(pchar, 42))
				{
					dialog.text = RandSwear() + "Eres " + GetFullName(pchar) + ", ¿no es así? Dicen " + RandPhraseSimple("muchas cosas aterradoras sobre ti", "muchas cosas feas sobre ti") + ", y no quiero tratar contigo.";
					link.l1 = RandPhraseSimple("Por supuesto, cometes un error una vez, y todos estarán encantados de escupirte.", RandSwear() + "Bueno, hay cosas mejores que hacer en el mar, " + GetFullName(npchar) + ".");
					link.l1.go = "exit";
					break;
				}
				// проверка на проф пригодность <--
				int iTradeNation = GenerateNationTrade(sti(NPChar.nation));

				if (iTradeNation < 0)
				{
					dialog.text = NPCharRepPhrase(npchar, "Heh, " + GetAddress_Form(NPChar) + " No tengo tiempo para fletes hoy. Vuelve mañana.", "Vuelve mañana. Tal vez te haga una oferta ventajosa.");
					link.l1 = "Muy bien, regresaré mañana.";
					link.l1.go = "exit";
				}
				else
				{
					int storeMan = findStoreMan(NPChar, iTradeNation);
					if (storeMan > 0)
					{
						// проверяем импорт/экспорт
						iTradeGoods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE)); // Jason
						// проверяем свободное место (при этом должно вмещаться по меньшей мере 100 единиц выбранного груза
						RecalculateSquadronCargoLoad(pchar); // fix неверное место
						iQuantityGoods = GetSquadronFreeSpace(pchar, iTradeGoods);
						if (sti(Goods[iTradeGoods].Weight) / sti(Goods[iTradeGoods].Units) * sti(iQuantityGoods) > 1500)
							iQuantityGoods = makeint(1500 / (sti(Goods[iTradeGoods].Weight) / sti(Goods[iTradeGoods].Units))); // Jason: больше 1500 массы не дадим - большие фрахты только через ПУ
						if (iQuantityGoods < 100)																			   // это в шт. товара
						{
							dialog.text = NPCharRepPhrase(npchar, "Tu miserable vieja bañera no puede contener todo el lote, así que no habrá trato hoy.", "Lamentablemente, capitán " + GetFullName(pchar) + ", necesitaré un barco más espacioso para mi entrega.");
							link.l1 = NPCharRepPhrase(npchar, "Mi barco es decente, pero entiendo tu punto. Adiós.", "Entiendo tu punto, los negocios son los negocios. Adiós.");
							link.l1.go = "exit";
						}
						else
						{
							iQuantityGoods = iQuantityGoods - rand(makeint(iQuantityGoods / 3)) - 10;
							iMoney = makeint((iQuantityGoods * sti(Goods[iTradeGoods].Weight) / sti(Goods[iTradeGoods].Units)) * (4 + rand(3) + GetSummonSkillFromNameToOld(pchar, SKILL_COMMERCE)) + 0.5);

							pchar.CargoQuest.iTradeGoods = iTradeGoods;
							pchar.CargoQuest.iQuantityGoods = iQuantityGoods;
							pchar.CargoQuest.iMoney = iMoney;
							pchar.CargoQuest.iTradeNation = iTradeNation;
							pchar.CargoQuest.iDaysExpired = 25 + rand(5);

							pchar.CargoQuest.iTradeColony = Characters[storeMan].city;
							pchar.CargoQuest.iTradeIsland = GetIslandByCityName(Characters[storeMan].city);
							pchar.CargoQuest.TraderID = Characters[storeMan].id;
							pchar.CargoQuest.GiveTraderID = NPChar.id;
							SaveCurrentQuestDateParam("CargoQuest");
							string sNation = XI_ConvertString("Colony" + Characters[storeMan].city);
							sTemp = "";
							if (pchar.CargoQuest.iTradeIsland != Characters[storeMan].city)
							{
								sTemp = ", que está en " + XI_ConvertString(pchar.CargoQuest.iTradeIsland + "Dat");
							}
							dialog.text = "¡Oh! Estaba a punto de pedirte un favor. Verás, necesito entregar una carga de " + GetGoodsNameAlt(iTradeGoods) + " en la cantidad de " + FindRussianQtyString(iQuantityGoods) + "  a la ciudad de " + sNation + sTemp + ", y cuanto antes mejor. Si logras hacerlo en menos de " + FindRussianDaysString(makeint(pchar.CargoQuest.iDaysExpired)) + ", entonces al llegar recibirás " + FindRussianMoneyString(iMoney) + " como tu recompensa. ¿Qué dices?";
							link.l1 = "Creo que estoy de acuerdo.";
							link.l1.go = "exit_trade";
							link.l2 = "Esto probablemente no sea para mí.";
							link.l2.go = "exit";
						}
					}
					else
					{
						dialog.text = "Las realidades políticas en el archipiélago no me permiten comerciar. " + XI_ConvertString(NationShortName(sti(NPChar.nation)) + "hunter") + " está en hostilidad con todos y me dejó solo en la tienda.";
						link.l1 = "¡Oh! Lo siento. Buena suerte.";
						link.l1.go = "exit";
					}
				}
			}
		}
		else
		{
			dialog.text = NPCharRepPhrase(npchar, "¡Piérdete, no tengo tiempo para charlas ociosas!", "Ya te he dicho que no tengo nada para ti.");
			link.l1 = NPCharRepPhrase(npchar, "¡Debes ser cortés, o te enseñaré a ser educado!", "¡Oh, lo siento!");
			link.l1.go = "exit";
		}
		break;

	case "exit_trade":
		AddDialogExitQuest("trade_quest_open");
		Nextdiag.CurrentNode = Nextdiag.TempNode;
		DialogExit();
		break;

	case "generate_quest_2":
		if (pchar.quest.generate_trade_quest_progress == "failed")
		{
			dialog.text = RandSwear() + "¿No crees que te acordaste de ese trato un poco tarde? Tuve que pedir las mercancías de nuevo. Adiós.";
			link.l1 = "Perdóname, pero tenía prisa. ¿Quizás si cubro tus pérdidas, mi reputación se restaurará?";
			link.l1.go = "generate_quest_failed";
			link.l9 = "Todo lo mejor.";
			link.l9.go = "exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		}
		else
		{
			iTradeGoods = makeint(pchar.CargoQuest.iTradeGoods);
			iQuantityGoods = makeint(pchar.CargoQuest.iQuantityGoods);

			dialog.text = "¡De hecho! He estado esperando por ello bastante tiempo. Tienes que entregarme un cargamento de " + GetGoodsNameAlt(iTradeGoods) + " en cantidad de " + FindRussianQtyString(iQuantityGoods) + " y recibir por ello " + FindRussianMoneyString(sti(pchar.CargoQuest.iMoney)) + ".";
			link.l1 = "Exactamente.";
			link.l1.go = "generate_quest_ready";
		}
		break;

	case "generate_quest_ready":
		iTradeGoods = makeint(pchar.CargoQuest.iTradeGoods);
		iQuantityGoods = makeint(pchar.CargoQuest.iQuantityGoods);
		// блок кидалова нас на бабки -->
		if (rand(8) == 1 && sti(Goods[iTradeGoods].Cost) <= 44 && GetQuestPastDayParam("CargoQuest") > 5)
		{
			dialog.text = RandSwear() + "Debo disculparme contigo, " + GetAddress_Form(NPChar) + ".  Verás, el problema es que yo estaba " + RandPhraseSimple("en una situación embarazosa y no podré pagarte", "ya compré esa carga de otro vendedor por un mejor precio") + " . Como pago por tu carta de navegación, sugiero que te quedes con toda la carga que estabas entregando.";
			link.l1 = RandSwear() + RandPhraseSimple("¡Y he estado protegiendo esa maldita carga de todos los peligros! ¡Maté doscientos ratas por ello!", "Me has puesto en un punto muerto, y tendré que aceptar.");
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
			AddCharacterExpToSkill(pchar, "Sailing", 60);
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddCharacterExpToSkill(pchar, "COMMERCE", 15);

			pchar.quest.generate_trade_quest_progress = "";
			pchar.quest.generate_trade_quest.over = "yes";

			AddQuestRecord("DELIVERY_TRADE_QUEST", "4");
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony", XI_ConvertString("Colony" + pchar.CargoQuest.iTradeColony + "Gen")); // belamour gen
			CloseQuestHeader("DELIVERY_TRADE_QUEST");
			break;
		}
		// блок кидалова нас на бабки <--
		if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
		{
			iTmp = iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods);
			dialog.text = "¡Eso no es todo el lote! Según nuestro trato, necesito " + FindRussianQtyString(iTmp) + " unidades más.";
			link.l9 = RandPhraseSimple("Sí, en efecto. Tendré que compensar la escasez entonces. Hasta luego.", RandSwear() + "Estas malditas ratas han echado a perder la carga. Compensaré la escasez y volveré de nuevo.");
			link.l9.go = "exit";
			AddQuestRecord("DELIVERY_TRADE_QUEST", "8");
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sHaveNotQty", iTmp);
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
		}
		else
		{
			dialog.text = "¡Excelente! Aquí está tu recompensa, capitán " + GetFullName(pchar) + ".";
			link.l1 = "Fue un placer trabajar contigo.";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar, "nobility", 3);
			AddCharacterExpToSkill(pchar, "Sailing", 100);
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "COMMERCE", 100);

			AddMoneyToCharacter(pchar, makeint(pchar.CargoQuest.iMoney));
			pchar.quest.generate_trade_quest_progress = "";
			pchar.quest.generate_trade_quest.over = "yes";
			RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));

			OfficersReaction("good");

			AddQuestRecord("DELIVERY_TRADE_QUEST", "2");
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony", XI_ConvertString("Colony" + pchar.CargoQuest.iTradeColony + "Gen"));
			CloseQuestHeader("DELIVERY_TRADE_QUEST");
		}
		break;

	case "generate_quest_failed":
		iTradeGoods = makeint(pchar.CargoQuest.iTradeGoods);
		iQuantityGoods = makeint(pchar.CargoQuest.iQuantityGoods);
		iMoney = 3 * makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
		dialog.text = "Está bien... La suma de " + FindRussianMoneyString(iMoney) + " cubrirá solo los daños causados por la violación de los términos de nuestro trato.";
		link.l1 = "¡Vaya! ¡No, eso no servirá! ¡Nunca más volveré a entregar ninguna carga! ¡Ya hay suficiente de esa porquería en el mar!";
		link.l1.go = "exit";
		if (sti(pchar.Money) >= iMoney)
		{
			link.l2 = "Aquí está la cantidad requerida";
			link.l2.go = "generate_quest_failed_2";
		}
		else
		{
			AddQuestRecord("DELIVERY_TRADE_QUEST", "7");
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony", XI_ConvertString("Colony" + pchar.CargoQuest.iTradeColony + "Gen"));
		}
		break;

	case "generate_quest_failed_2":
		iTradeGoods = makeint(pchar.CargoQuest.iTradeGoods);
		iQuantityGoods = makeint(pchar.CargoQuest.iQuantityGoods);
		iMoney = 3 * makeint(iQuantityGoods * sti(Goods[iTradeGoods].Cost) / sti(Goods[iTradeGoods].Units));
		dialog.text = "Excelente. Ahora puedo decirles a mis colegas que todavía eres razonable para tratar.";
		link.l1 = "¡Gracias! No te fallaré de nuevo.";
		link.l1.go = "exit";
		ChangeCharacterComplexReputation(pchar, "nobility", 10);
		AddCharacterExpToSkill(pchar, "Sailing", -100);
		AddCharacterExpToSkill(pchar, "Leadership", -50);
		AddCharacterExpToSkill(pchar, "COMMERCE", -100);

		AddMoneyToCharacter(pchar, -iMoney);
		pchar.quest.generate_trade_quest_progress = "";
		pchar.quest.generate_trade_quest.over = "yes";

		AddQuestRecord("DELIVERY_TRADE_QUEST", "5");
		AddQuestUserData("DELIVERY_TRADE_QUEST", "sMoney", FindRussianMoneyString(iMoney));
		AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
		AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony", XI_ConvertString("Colony" + pchar.CargoQuest.iTradeColony + "Gen"));
		CloseQuestHeader("DELIVERY_TRADE_QUEST");
		break;

	case "generate_quest_not_closed":
		iTradeGoods = makeint(pchar.CargoQuest.iTradeGoods);
		iQuantityGoods = makeint(pchar.CargoQuest.iQuantityGoods);

		dialog.text = "Hmm. He oído que no has cumplido con tus obligaciones estipuladas en el contrato anterior, ¿y estás pidiendo otro? Tenías que entregar la carga de " + LanguageConvertString(iSeaGoods, "seg_" + Goods[iTradeGoods].Name) + " a " + XI_ConvertString("Colony" + pchar.CargoQuest.iTradeColony) + ".";
		link.l1 = "¡Sí, en efecto! ¡Tienes razón!";
		link.l1.go = "exit";
		break;

	case "generate_quest_cannot_done":
		dialog.text = RandSwear() + GetAddress_Form(NPChar) + ", ¡me estás decepcionando!!! ¿Quizás harás algo para resolver este problema?";
		link.l1 = "Está bien. Haré todo lo posible para entregar el cargamento.";
		link.l1.go = "exit";
		link.l2 = "No, no puedo. Lo siento";
		link.l2.go = "generate_quest_cannot_done_2";

		break;

	case "generate_quest_cannot_done_2":
		iTradeGoods = makeint(pchar.CargoQuest.iTradeGoods);
		iQuantityGoods = makeint(pchar.CargoQuest.iQuantityGoods);
		if (GetSquadronGoods(pchar, iTradeGoods) < iQuantityGoods)
		{
			dialog.text = "¡Espera! ¡No hay suficientes mercancías a bordo de tu barco! No tienes " + FindRussianQtyString(iQuantityGoods - GetSquadronGoods(pchar, iTradeGoods)) + " unidades de carga.";
			link.l9 = RandPhraseSimple("Sí, en efecto. Tendré que compensar por la escasez entonces.", RandSwear() + "Las ratas han echado a perder la carga. Compraré la cantidad faltante y regresaré de nuevo.");
			link.l9.go = "exit";
		}
		else
		{
			dialog.text = "Ya veo, ya veo... Aceptaré el envío de vuelta.";
			link.l1 = "¡Gracias! ¡No te fallaré de nuevo!";
			link.l1.go = "exit";
			ChangeCharacterComplexReputation(pchar, "nobility", -3);

			pchar.quest.generate_trade_quest_progress = "";
			pchar.quest.generate_trade_quest.over = "yes";
			RemoveCharacterGoods(pchar, makeint(pchar.CargoQuest.iTradeGoods), makeint(pchar.CargoQuest.iQuantityGoods));

			AddQuestRecord("DELIVERY_TRADE_QUEST", "6");
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodQty", FindRussianQtyString(sti(pchar.CargoQuest.iQuantityGoods)));
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sGoodGen", GetGoodsNameAlt(iTradeGoods));
			AddQuestUserData("DELIVERY_TRADE_QUEST", "sTargetColony", XI_ConvertString("Colony" + pchar.CargoQuest.iTradeColony + "Gen")); // belamour gen
			CloseQuestHeader("DELIVERY_TRADE_QUEST");
		}
		break;

		// Jason --> мини-квест Дефицитный товар
	case "Wine_Trader":
		dialog.text = "¿De qué estás hablando? Claramente, te han engañado, nunca he comerciado con vino europeo en tales cantidades. Una o dos botellas, no más. Pero el vino es otra historia, tengo suficiente de esa mercancía, y se vende por garrafones, no por botellas!";
		link.l1 = "¡Maldita sea! Pero me dijeron...";
		link.l1.go = "Wine_Trader_1";
		break;

	case "Wine_Trader_1":
		dialog.text = "No tengo idea de lo que te hayan dicho, pero lo diré de nuevo: No tengo vino europeo en stock. Eso es todo lo que tengo que decir respecto a este asunto.";
		link.l1 = "De acuerdo... Entonces, iré a solucionarlo, ¡entonces!";
		link.l1.go = "exit";
		AddQuestRecord("Wine", "5");
		AddQuestUserData("Wine", "sName", pchar.questTemp.Wine.Name);
		DeleteAttribute(pchar, "questTemp.Wine.Trader");
		pchar.questTemp.Wine.Repeat1 = "true";
		break;

	case "Wine_Repeat2":
		RemoveItems(PChar, "letter_1", 1);
		PlaySound("interface\important_item.wav");
		dialog.text = "Ahora esa es una historia diferente. Sabes, varios tipos vienen aquí, haciendo preguntas innecesarias. Entonces, ¿regateamos, eh?";
		link.l1 = "¡Por supuesto!";
		link.l1.go = "Wine_Price";
		pchar.questTemp.Wine.wait = "true";
		DeleteAttribute(pchar, "questTemp.Wine.Repeat2");
		SetFunctionTimerCondition("Wine_wait", 0, 0, 7, false);
		DelLandQuestMark(npchar);
		AddLandQuestMark(characterFromId(pchar.questTemp.Wine.ItemTraderID), "questmarkmain");
		break;

	case "Wine_Price":
		dialog.text = "¿Cuántas botellas necesitas? El precio de una botella es de 500 pesos, y el lote mínimo es de 20 botellas.";
		link.l1 = "";
		Link.l1.edit = 4;
		link.l1.go = "Wine_Qty";
		link.l2 = "No tengo suficiente dinero ahora mismo. Volveré más tarde.";
		link.l2.go = "Wine_Qty_exit";
		break;

	case "Wine_Qty":
		int iQty = sti(dialogEditStrings[4]);
		pchar.questTemp.Wine.Qty = sti(iQty);
		if (iQty < 20)
		{
			dialog.text = "No soy un buhonero, capitán. Según recuerdo, ¿no hablaba usted de un lote más grande?";
			link.l1 = "Lo siento... Entonces reconsideremos la cantidad.";
			link.l1.go = "Wine_Price";
			break;
		}
		if (iQty > 70)
		{
			dialog.text = "Lamentablemente, no tengo tanto.";
			link.l1 = "Lástima... Reconsideremos la cantidad, entonces.";
			link.l1.go = "Wine_Price";
			break;
		}
		pchar.questTemp.Wine.Summ = sti(iQty) * 500;
		dialog.text = "" + sti(iQty) + " ¿Botellas? Bien. Eso te costará " + FindRussianMoneyString(sti(pchar.questTemp.Wine.Summ)) ".";
		if (makeint(Pchar.money) >= sti(pchar.questTemp.Wine.Summ))
		{
			link.l1 = "Aquí tienes.";
			link.l1.go = "Wine_Qty_1";
		}
		link.l2 = "No tengo suficiente dinero ahora. Volveré más tarde.";
		link.l2.go = "Wine_Qty_exit";
		break;

	case "Wine_Qty_exit":
		dialog.text = "Está bien, pero trata de no tardar mucho. Estas cosas son bastante populares aquí.";
		link.l1 = "¡Volveré pronto!";
		link.l1.go = "exit";
		break;

	case "Wine_Qty_1":
		AddMoneyToCharacter(pchar, -sti(pchar.questTemp.Wine.Summ));
		dialog.text = "Veamos... Todo parece en orden. Puedes recoger tu compra.";
		link.l1 = "¡Gracias! ¡Buena suerte!";
		link.l1.go = "Wine_Qty_2";
		break;

	case "Wine_Qty_2":
		pchar.quest.Wine_wait.over = "yes"; // снять прерывание
		DeleteAttribute(pchar, "questTemp.Wine.wait");
		TakeNItems(pchar, "potionwine", sti(pchar.questTemp.Wine.Qty));
		PlaySound("interface\important_item.wav");
		Log_Info("Has recibido vino");
		AddQuestRecord("Wine", "8");
		DelLandQuestMark(npchar);
		DialogExit();
		break;
		// <-- мини-квест Дефицитный товар

		// Jason --> -------------------------генератор Сомнительное предложение----------------------------------------
		int iCGood, amount;
	case "Contraoffer":
		pchar.GenQuest.Contraoffer.Trader.Goods = SelectContrabandGoods(pchar);
		while (sti(pchar.GenQuest.Contraoffer.Trader.Goods) == -1)
		{
			pchar.GenQuest.Contraoffer.Trader.Goods = SelectContrabandGoods(pchar);
		}
		iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
		pchar.GenQuest.Contraoffer.Trader.Qty = makeint(15 * (sti(pchar.rank) + 30) / (sti(Goods[iCGood].Weight) / sti(Goods[iCGood].Units)) * (8 - sti(RealShips[sti(pchar.ship.type)].Class))); // количество
		pchar.GenQuest.Contraoffer.Trader.Price = sti(Goods[iCGood].Cost) / sti(Goods[iCGood].Units) * 3;																						  // цена единицы товара
		pchar.GenQuest.Contraoffer.Trader.Summ = sti(pchar.GenQuest.Contraoffer.Trader.Price) * sti(pchar.GenQuest.Contraoffer.Trader.Qty);														  // сумма
		pchar.GenQuest.Contraoffer.Trader.Days = 30 + hrand(20);																																  // срок
		pchar.GenQuest.Contraoffer.Trader.Chance = rand(5);																																		  // 17% вероятности, что патруль накроет
		dialog.text = "Planeaba cerrar un buen trato, pero aún necesito una mercancía en particular para ello, " + GetGoodsNameAlt(iCGood) + ". El problema es que esta mercancía es un contrabando en nuestra colonia, así que no puedo contar con comprarla de los capitanes comerciantes\nTodo lo que necesito son " + FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty)) + " unidades de ello. ¿Quizás podrías entregármelo? Te pagaré bien, " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Price)) + " por unidad, lo que sumará a " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)) + ". Oh, y lo necesito a más tardar en " + FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days)) + "Entonces, ¿me ayudarás?";
		link.l1 = "Hmm... Suena interesante. ¡Estoy de acuerdo!";
		link.l1.go = "Contraoffer_1";
		link.l2 = "¿Entregando mercancías de contrabando? Lo siento, no estoy interesado.";
		link.l2.go = "exit";
		SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
		break;

	case "Contraoffer_1":
		dialog.text = "Excelente. Me alegra que hayas aceptado. Estaré esperando tu regreso con la mercancía.";
		link.l1 = "¡Pronto estaré de vuelta!";
		link.l1.go = "exit";
		rColony = GetColonyByIndex(FindColony(npchar.city));
		SetNull2StoreGood(rColony, sti(pchar.GenQuest.Contraoffer.Trader.Goods)); // нулим товар
		pchar.GenQuest.Contraoffer = "begin";
		pchar.GenQuest.Contraoffer.Trader = "true";
		pchar.GenQuest.Contraoffer.Trader.City = npchar.city;
		pchar.GenQuest.Contraoffer.Trader.Nation = npchar.nation;
		iCGood = pchar.GenQuest.Contraoffer.Trader.Goods;
		ReOpenQuestHeader("Contraoffer");
		AddQuestRecord("Contraoffer", "1");
		AddQuestUserData("Contraoffer", "sGoods", GetGoodsNameAlt(iCGood));
		AddQuestUserData("Contraoffer", "sGoodQty", FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Trader.Qty)));
		AddQuestUserData("Contraoffer", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)));
		AddQuestUserData("Contraoffer", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Contraoffer.Trader.City + "Gen"));
		AddQuestUserData("Contraoffer", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Trader.Days)));
		SetFunctionTimerCondition("Contraoffer_Over", 0, 0, sti(pchar.GenQuest.Contraoffer.Trader.Days), false);
		break;

	case "Contraoffer_check":
		iCGood = sti(pchar.GenQuest.Contraoffer.Trader.Goods);
		amount = sti(pchar.GenQuest.Contraoffer.Trader.Qty) - GetSquadronGoods(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Goods));
		if (amount > 0)
		{
			dialog.text = "¿Estás bromeando? ¡No tienes la cantidad completa de mercancías que necesito!";
			link.l1 = "Lo siento, mi error...";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "Veamos, entonces. Se suponía que debías entregar una carga de " + GetGoodsNameAlt(iCGood) + " en cantidad de " + FindRussianQtyString(pchar.GenQuest.Contraoffer.Trader.Qty) + ". ¿Correcto?";
			link.l1 = "Exactamente, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "Contraoffer_pay";
		}
		break;

	case "Contraoffer_pay":
		dialog.text = "Gracias por tu trabajo. Por favor, toma tu pago de " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Trader.Summ)) + ".";
		link.l1 = "¡Gracias! Un placer hacer negocios contigo.";
		link.l1.go = "Contraoffer_complete";
		break;

	case "Contraoffer_complete":
		pchar.quest.Contraoffer_Over.over = "yes";
		RemoveCharacterGoods(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Goods), sti(pchar.GenQuest.Contraoffer.Trader.Qty));
		AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Contraoffer.Trader.Summ));
		SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
		npchar.quest.Contraoffer.chance = rand(2);		 // личный шанс торговца для 'пасхалки'
		AddCharacterExpToSkill(pchar, "Sailing", 100);	 // навигация
		AddCharacterExpToSkill(pchar, "Commerce", 100);	 // торговля
		AddCharacterExpToSkill(pchar, "Leadership", 50); // авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 100);	 // везение
		ChangeCharacterComplexReputation(pchar, "nobility", -1);
		if (pchar.GenQuest.Contraoffer.Trader.Chance == 3)
		{
			dialog.text = "Vaya... Capitán, parece que tenemos un problema aquí...";
			link.l1 = "¿Qué es de nuevo?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Contraoffer_Patrol");
			pchar.GenQuest.Contraoffer.Trader.busy = "true";
			pchar.quest.Contraoffer_busy.win_condition.l1 = "ExitFromLocation";
			pchar.quest.Contraoffer_busy.win_condition.l1.location = pchar.location;
			pchar.quest.Contraoffer_busy.function = "Trader_free";
		}
		else
		{
			DialogExit();
			AddQuestRecord("Contraoffer", "3");
			CloseQuestHeader("Contraoffer");
			DeleteAttribute(pchar, "GenQuest.Contraoffer.Trader");
		}
		break;

	case "Contraoffer_slaves": // единичный вариант за всю игру, ака 'пасхалка'
		pchar.GenQuest.Contraoffer.Slaves.Name = GetFullName(npchar);
		pchar.GenQuest.Contraoffer.Slaves.Price = 300;			// цена на рабов, пока фиксированная, можно подставить формулу
		pchar.GenQuest.Contraoffer.Slaves.Qty = 300 + rand(50); // количество
		pchar.GenQuest.Contraoffer.Slaves.Days = 14 + rand(6);	// срок
		pchar.GenQuest.Contraoffer.Slaves.Money = sti(pchar.GenQuest.Contraoffer.Slaves.Qty) * sti(pchar.GenQuest.Contraoffer.Slaves.Price);
		dialog.text = "Necesito urgentemente un lote de esclavos, " + sti(pchar.GenQuest.Contraoffer.Slaves.Qty) + " cabezas. Estoy listo para pagar " + sti(pchar.GenQuest.Contraoffer.Slaves.Price) + " monedas por alma, lo que ascenderá a " + sti(pchar.GenQuest.Contraoffer.Slaves.Money) + " pesos en total. En un plazo de " + FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days)) + ".";
		link.l1 = "Creo que voy a estar de acuerdo. Es un negocio molesto, pero muy lucrativo.";
		link.l1.go = "Contraoffer_slaves_1";
		link.l2 = "No estoy interesado.";
		link.l2.go = "exit";
		pchar.GenQuest.Contraoffer.Slaves = "begin";
		break;

	case "Contraoffer_slaves_1":
		dialog.text = "Exactamente, es muy rentable, de hecho. Bueno, entonces estaré esperando tu regreso con mis esclavos.";
		link.l1 = "No te haré esperar mucho. ¡Nos vemos!";
		link.l1.go = "exit";
		pchar.GenQuest.Contraoffer.Slaves.Yes = "begin";
		pchar.GenQuest.Contraoffer.Slaves.City = npchar.city;
		ReOpenQuestHeader("Contraoffer");
		AddQuestRecord("Contraoffer", "4");
		AddQuestUserData("Contraoffer", "sDays", FindRussianDaysString(sti(pchar.GenQuest.Contraoffer.Slaves.Days)));
		AddQuestUserData("Contraoffer", "sGoodQty", FindRussianQtyString(sti(pchar.GenQuest.Contraoffer.Slaves.Qty)));
		AddQuestUserData("Contraoffer", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money)));
		AddQuestUserData("Contraoffer", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Contraoffer.Slaves.City + "Gen"));
		SetFunctionTimerCondition("Contraoffer_Over", 0, 0, sti(pchar.GenQuest.Contraoffer.Slaves.Days), false);
		break;

	case "Contraoffer_slaves_check":
		amount = sti(pchar.GenQuest.Contraoffer.Slaves.Qty) - GetSquadronGoods(pchar, GOOD_SLAVES);
		if (amount > 0)
		{
			dialog.text = "¿Estás bromeando? ¡No tienes todos los esclavos que necesito!";
			link.l1 = "Lo siento, mi error...";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "Veamos, entonces. Ibas a entregarme un lote de esclavos por la cantidad de " + FindRussianQtyString(pchar.GenQuest.Contraoffer.Slaves.Qty) + ". ¿Correcto?";
			link.l1 = "Exactamente, " + GetAddress_FormToNPC(NPChar) + ".";
			link.l1.go = "Contraoffer_slaves_pay";
		}
		break;

	case "Contraoffer_slaves_pay":
		dialog.text = "Gracias por tu trabajo. Por favor, toma tu pago de " + FindRussianMoneyString(sti(pchar.GenQuest.Contraoffer.Slaves.Money)) + "Además, por favor, acepta esto. Estoy seguro de que lo encontrarás útil.";
		link.l1 = "¡Gracias! Un placer hacer negocios contigo.";
		link.l1.go = "Contraoffer_slaves_complete";
		break;

	case "Contraoffer_slaves_complete":
		DialogExit();
		pchar.quest.Contraoffer_Over.over = "yes";
		RemoveCharacterGoods(pchar, GOOD_SLAVES, sti(pchar.GenQuest.Contraoffer.Slaves.Qty));
		AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Contraoffer.Slaves.Money));
		AddQuestRecord("Contraoffer", "5");
		CloseQuestHeader("Contraoffer");
		SaveCurrentNpcQuestDateParam(npchar, "Contraoffer");
		AddCharacterExpToSkill(pchar, "Sailing", 150);	 // навигация
		AddCharacterExpToSkill(pchar, "Commerce", 200);	 // торговля
		AddCharacterExpToSkill(pchar, "Leadership", 50); // авторитет
		AddCharacterExpToSkill(pchar, "Fortune", 150);	 // везение
		TakeNItems(pchar, "cirass3", 1);
		ChangeCharacterComplexReputation(pchar, "nobility", -3);
		DeleteAttribute(pchar, "GenQuest.Contraoffer.Slaves.Yes");
		break;
	// <-- генератор Сомнительное предложение

	// Jason --> генератор Неудачливый вор
	case "Device_Trader":
		dialog.text = "Mm, " + pchar.GenQuest.Device.Shipyarder.Type + "¿Nunca he oído hablar de eso antes... ¿Qué es exactamente? Nunca he oído hablar de tal cosa en todo mi tiempo.";
		link.l1 = "Bueno, es una herramienta de constructor naval, " + pchar.GenQuest.Device.Shipyarder.Describe + ". ¿Alguien te ofreció algo así?";
		link.l1.go = "Device_Trader_1";
		npchar.quest.Device = "true";
		break;

	case "Device_Trader_1":
		if (sti(pchar.GenQuest.Device.Shipyarder.Chance1) == 0)
		{
			dialog.text = "Mm... Sí, hubo un tipo extraño. Pero no me dijo qué era esa cosa, solo intentó vendérmela. Pero, ¿para qué la necesitaría si no tengo idea de para qué sirve? ¿Cómo la revendería? Así que simplemente me negué.";
			link.l1 = "¿Y cómo lucía y a dónde fue? Necesito ese instrumento con urgencia.";
			link.l1.go = "Device_Common";
		}
		else
		{
			dialog.text = "No, nada de eso. Lo siento, no puedo ayudarte. Pregunta por ahí.";
			link.l1 = "Ya veo. ¡Bueno, es hora de preguntar por ahí!";
			link.l1.go = "exit";
		}
		break;
	// <-- генератор Неудачливый вор

	// Jason --> генератор Место под солнцем
	case "Sunplace_begin":
		dialog.text = "La competencia... No hay negocio sin ella. Malditos codiciosos que se esfuerzan por meterse en tu acogedor negocio y usan todo tipo de métodos nefastos para atraer clientes hacia ellos.\nPero eso es otra historia. Y de hecho, me gustaría pedirte que me ayudes a deshacerme de uno de esos competidores míos. No, no es necesario matarlo. Simplemente captura o hunde su barco con la carga.";
		link.l1 = "Hmm... bueno, si estás pagando bien, puedo arreglar esto.";
		link.l1.go = "Sunplace_1";
		link.l2 = "No, no me entrometeré en tus querellas mercantiles. Ve a hundir a tu rival sin mi ayuda.";
		link.l2.go = "Sunplace_exit";
		break;

	case "Sunplace_exit": // если отказал - этот непись больше никогда не даст
		npchar.quest.Sunplace = "true";
		DialogExit();
		break;

	case "Sunplace_1":
		GetSunplaceShore();																					// бухта и остров
		pchar.GenQuest.Sunplace.Trader.Enemyname = GenerateRandomName_Generator(sti(npchar.nation), "man"); // имя конкурента
		pchar.GenQuest.Sunplace.Trader.Nation = npchar.nation;												// нация общая для торговца и конкурента
		pchar.GenQuest.Sunplace.Trader.City = npchar.City;													// город квестодателя
		pchar.GenQuest.Sunplace.Trader.CityT = findSunplaceCity(NPChar);									// город конкурента
		pchar.GenQuest.Sunplace.Trader.Shiptype = Sunplace_Shiptype();										// тип корабля
		pchar.GenQuest.Sunplace.Trader.ShipName = GenerateRandomNameToShip(sti(NPChar.nation));				// имя корабля
		pchar.GenQuest.Sunplace.Trader.DaysQty = 5 + hrand(5);												// дни
		pchar.GenQuest.Sunplace.Trader.Money = sti(pchar.GenQuest.Sunplace.Trader.Shiptype) * 3000;			// оплата
		pchar.GenQuest.Sunplace.Trader.Goods = GOOD_COFFEE + hrand(sti(GOOD_PAPRIKA - GOOD_COFFEE));		// товар
		dialog.text = "Muy bien. Entonces, el nombre de tu hombre es " + pchar.GenQuest.Sunplace.Trader.Enemyname + ". Recientemente había enviado " + GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name") + "Acc")) + " '" + pchar.GenQuest.Sunplace.Trader.ShipName + " con un cargamento de " + GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods)) + ". Pagó una suma bastante decente por este cargamento, así que perderlo será un golpe bastante fuerte para su bolsa.";
		link.l1 = "¿Y podrías decirme, dónde exactamente buscar a ese 'amigo' tuyo?";
		link.l1.go = "Sunplace_2";
		break;

	case "Sunplace_2":
		dialog.text = "Mi 'amigo' se encuentra actualmente en su hogar en " + XI_ConvertString("Colony" + pchar.GenQuest.Sunplace.Trader.CityT + "Voc") + ". No lo necesitas a él, necesitas su barco, el cual, como descubrí después de aproximadamente " + FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)) + " pasará cerca " + XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore + "Gen") + ". Puedes hundirlo, abordarlo, no importa. Lo principal es asegurarse de que el barco y la carga ya no sean propiedad de " + pchar.GenQuest.Sunplace.Trader.Enemyname + ". Y no me importa quién lo reclame, tú o el mar. Por ese trabajo te pagaré " + FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money)) ".";
		link.l1 = "Lo tengo. ¡Bien, es hora de partir entonces!";
		link.l1.go = "Sunplace_3";
		break;

	case "Sunplace_3":
		DialogExit();
		pchar.GenQuest.Sunplace.Trader = "true";
		if (sti(pchar.GenQuest.Sunplace.Chance) == 1 && sti(pchar.rank) > 9)
			pchar.GenQuest.Sunplace.Bonus = "true";
		ReOpenQuestHeader("Sunplace");
		AddQuestRecord("Sunplace", "1");
		AddQuestUserData("Sunplace", "sGoods", GetGoodsNameAlt(sti(pchar.GenQuest.Sunplace.Trader.Goods)));
		AddQuestUserData("Sunplace", "sDay", FindRussianDaysString(sti(pchar.GenQuest.Sunplace.Trader.DaysQty)));
		AddQuestUserData("Sunplace", "sMoney", FindRussianMoneyString(sti(pchar.GenQuest.Sunplace.Trader.Money)));
		AddQuestUserData("Sunplace", "sCity", XI_ConvertString("Colony" + pchar.GenQuest.Sunplace.Trader.City + "Gen"));
		AddQuestUserData("Sunplace", "sType", GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(pchar.GenQuest.Sunplace.Trader.ShipType), "Name") + "Acc")));
		AddQuestUserData("Sunplace", "sSName", pchar.GenQuest.Sunplace.Trader.ShipName);
		AddQuestUserData("Sunplace", "sName", GetFullName(npchar));
		AddQuestUserData("Sunplace", "sShore", XI_ConvertString(pchar.GenQuest.Sunplace.Trader.Shore + "Gen"));
		SetFunctionTimerCondition("Sunplace_Over", 0, 0, sti(pchar.GenQuest.Sunplace.Trader.DaysQty), false);
		pchar.quest.Sunplace_Trader.win_condition.l1 = "location";
		pchar.quest.Sunplace_Trader.win_condition.l1.location = pchar.GenQuest.Sunplace.Trader.Island;
		pchar.quest.Sunplace_Trader.win_condition.l2 = "Timer";
		pchar.quest.Sunplace_Trader.win_condition.l2.date.hour = sti(GetTime());
		pchar.quest.Sunplace_Trader.win_condition.l2.date.day = GetAddingDataDay(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty) - 2));
		pchar.quest.Sunplace_Trader.win_condition.l2.date.month = GetAddingDataMonth(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty) - 2));
		pchar.quest.Sunplace_Trader.win_condition.l2.date.year = GetAddingDataYear(0, 0, makeint(sti(pchar.GenQuest.Sunplace.Trader.DaysQty) - 2));
		pchar.quest.Sunplace_Trader.function = "Sunplace_CreateTraderShip";
		break;

	case "Sunplace_complete":
		dialog.text = "¡Excelente! Sabía que podía contar contigo. Supongo que no preguntaré sobre el paradero de ese barco y la carga. Después de todo, no es asunto mío. Y mi amigo necesitará bastante tiempo para recuperarse de semejante golpe, je-je. Aquí, por favor, toma tu dinero, y gracias por un trabajo excelente.";
		link.l1 = "De nada... ¡Nos vemos, " + npchar.name + "!";
		link.l1.go = "Sunplace_complete_1";
		break;

	case "Sunplace_complete_1":
		AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Sunplace.Trader.Money));
		AddQuestRecord("Sunplace", "12");
		CloseQuestHeader("Sunplace");
		pchar.GenQuest.Sunplace.Chance = rand(2);
		AddComplexSeaExpToScill(50, 50, 50, 50, 50, 0, 0);
		AddComplexSelfExpToScill(20, 20, 20, 20);
		AddCharacterExpToSkill(pchar, "Fortune", 100); // везение
		DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
		DialogExit();
		break;

	case "Sunplace_complete_murder":
		dialog.text = "Pobre " + pchar.GenQuest.Sunplace.Trader.Enemyname + ", ¡qué destino tan espantoso! Y aunque de manera indirecta, ¡yo soy la causa de su muerte! ¡No entiendes, capitán! ¿Te pedí que lo mataras? Planeaba que después de la pérdida del dinero gastado en la carga él nuevamente tendría que... bueno, no importa... Tú...";
		link.l1 = "Oye, escucha, deja de quejarte, ¿de acuerdo? Me pediste que te librara de un rival, y lo hice. Aún mejor, tras perder la carga, aún podría hacerse rico de nuevo y seguir perjudicando tu negocio. Ahora no hay mucho que pueda hacer siendo un hombre muerto.";
		link.l1.go = "Sunplace_complete_murder_1";
		break;

	case "Sunplace_complete_murder_1":
		dialog.text = "¡Eso es! ¡Basta! ¡No quiero escuchar más estos discursos blasfemos! ¡Toma tu maldito dinero y sal de mi tienda de inmediato!";
		link.l1 = "Hola, " + npchar.name + ", cálmate, ¿quieres? ¡O enfriaré tu temperamento yo mismo, mi sable siempre está a mi lado! Está bien, no te asustes, solo estaba bromeando. Escucha, lamento que haya resultado así, pero fuiste tú quien me engañó desde el principio. Adiós.";
		link.l1.go = "Sunplace_complete_murder_2";
		break;

	case "Sunplace_complete_murder_2":
		AddMoneyToCharacter(pchar, sti(pchar.GenQuest.Sunplace.Trader.Money));
		AddQuestRecord("Sunplace", "13");
		AddQuestUserData("Sunplace", "sName", GetFullName(npchar));
		CloseQuestHeader("Sunplace");
		npchar.quest.Sunplace = "true"; // этот непись повторно квест больше не даст
		AddComplexSeaExpToScill(50, 50, 50, 50, 50, 0, 0);
		AddComplexSelfExpToScill(30, 30, 30, 30);
		AddCharacterExpToSkill(pchar, "Fortune", 50); // везение
		DeleteAttribute(pchar, "GenQuest.Sunplace.Trader");
		DialogExit();
		break;

	// Jason --> поиск дезертира
	case "FindFugitiveSt":
		if (NPChar.city == pchar.GenQuest.FindFugitive.City && sti(pchar.GenQuest.FindFugitive.Chance) == 1)
		{
			dialog.text = NPCStringReactionRepeat("¿" + pchar.GenQuest.FindFugitive.Name + "? Sí, lo conozco. Me compró provisiones para su bote largo. Durante el día suele estar pescando en calas apartadas, pero cada noche se le puede encontrar en la taberna.", "¡Ya me has preguntado sobre ese hombre, y te dije todo lo que sabía!", "¿Te estás burlando de mí o eres realmente un idiota? ¡Ya estás haciendo todas las mismas preguntas por tercera vez!", "Solo pensar, cómo un idiota así se convirtió en capitán...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("¡Gracias, me has ayudado inmensamente!", "Sí, sí, bien.", "Ahora, ahora, no te emociones tanto. Simplemente lo olvidé.", "Bueno, lo hizo, como puedes ver...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("FindFugitiveSt_1", "exit", "", "", npchar, Dialog.CurrentNode);
		}
		else
		{
			dialog.text = NPCStringReactionRepeat("No sé qué decían en la taberna de Port Royal, pero nunca vi a ese hombre en mi tienda. De hecho, nunca lo he visto en ningún lado. Pregunta por el pueblo, quizás alguien te diga algo...", "Ya me has preguntado por ese hombre, y te dije: ¡no lo sé!", "¿Me estás tomando el pelo o eres un idiota?! ¡Ya estás haciendo las mismas preguntas por tercera vez!", "Solo pensar, cómo semejante idiota se convirtió en capitán...", "block", 1, npchar, Dialog.CurrentNode);
			link.l1 = HeroStringReactionRepeat("Ya veo. Bueno, gracias de todas formas.", "Sí, sí, está bien.", "Ahora, ahora, no te emociones tanto. Simplemente lo olvidé.", "Bueno, lo hizo, como puedes ver...", npchar, Dialog.CurrentNode);
			link.l1.go = DialogGoNodeRepeat("exit", "", "", "", npchar, Dialog.CurrentNode);
		}
		break;

	case "FindFugitiveSt_1":
		DialogExit();
		AddQuestRecord("MayorsQuestsList", "12-2");
		sld = characterFromId("Fugitive");
		LAi_SetSitType(sld);
		sld.dialog.currentnode = "Fugitive_tavern";
		LAi_SetLoginTime(sld, 20.0, 23.99);
		FreeSitLocator(pchar.GenQuest.FindFugitive.City + "_tavern", "sit_front1");
		ChangeCharacterAddressGroup(sld, pchar.GenQuest.FindFugitive.City + "_tavern", "sit", "sit_front1");
		break;
	//<-- поиск дезертира

	// --> Карибские нравы - временное завершение
	// belamour legendary edition -->
	case "trial":
		dialog.text = "¡Por Dios, joven, qué modales! Por favor, sea más comedido y elija sus palabras con cuidado al hablar de personas respetadas. Gerard LeCroix partió de Guadalupe con una expedición al continente, pero dejó aquí su recompensa para usted. ¿Está satisfecho ahora?";
		link.l1 = "Hm... Por favor, discúlpeme, monsieur. Me exalté un poco...";
		link.l1.go = "trial_1";
		break;

	case "trial_1":
		dialog.text = "Muy bien. El señor Lecroix dejó su recompensa al farero, son viejos amigos. Solo necesita visitarlo y recoger el pago debido. Monsieur Lecroix es un hombre honesto, así que creo que quedará satisfecho con su recompensa.";
		link.l1 = "¡Entendido, gracias! Entonces voy al guardián del faro. Ahora déjame tomar un descanso.";
		link.l1.go = "trial_2";
		break;

	case "trial_2":
		// TakeNItems(pchar, "gold_dublon", 400);
		link.l1 = "...";
		link.l1.go = "trial_3";
		break;

	case "trial_3":
		DialogExit();
		AddQuestRecord("Trial", "22");
		ChangeCharacterComplexReputation(pchar, "nobility", -1);
		AddCharacterExpToSkill(pchar, "FencingL", 20);
		AddCharacterExpToSkill(pchar, "FencingS", 20);
		AddCharacterExpToSkill(pchar, "FencingH", 20);
		AddCharacterExpToSkill(pchar, "Pistol", 20);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DeleteAttribute(pchar, "questTemp.Trial");
		DeleteAttribute(npchar, "quest.trial_usurer");
		sld = characterFromId("BasTer_Lightman");
		sld.quest.trial_usurer = true;
		AddLandQuestMark(sld, "questmarkmain");
		break;

	case "trialA":
		dialog.text = "Sí, él estuvo aquí, esperándote. Pero, probablemente, la tarea que te encomendó resultó ser más difícil de lo que se esperaba originalmente, así que no esperó y se fue en una expedición al continente. Dejó tu recompensa con una persona de confianza.";
		link.l1 = "Sí, realmente tuve circunstancias imprevistas, pero completé la tarea con éxito. Me alegra saber que mi pago me está esperando. ¿De quién puedo recibirlo?";
		link.l1.go = "trialA_1";
		break;

	case "trialA_1":
		dialog.text = "El señor Lecroix dejó tu recompensa al guardián del faro, son viejos amigos. Solo necesitas visitarlo y recoger el pago debido. Monsieur Lecroix es un hombre honesto, así que creo que estarás satisfecho con tu recompensa.";
		link.l1 = "¡Entendido, gracias! Entonces voy al farero. Ahora déjame descansar.";
		link.l1.go = "trialA_2";
		break;

	case "trialA_2":
		dialog.text = "Buena suerte, monsieur.";
		link.l1 = "...";
		link.l1.go = "trialA_3";
		break;

	case "trialA_3":
		DialogExit();
		AddQuestRecord("Trial", "22");
		ChangeCharacterComplexReputation(pchar, "nobility", 1);
		AddCharacterExpToSkill(pchar, "Commerce", 80);
		NextDiag.CurrentNode = NextDiag.TempNode;
		DeleteAttribute(pchar, "questTemp.Trial");
		DeleteAttribute(npchar, "quest.trial_usurer");
		sld = characterFromId("BasTer_Lightman");
		sld.quest.trial_usurer = true;
		AddLandQuestMark(sld, "questmarkmain");
		break;
	// <-- legendary edition
	/*case "trial":
		dialog.text = "¡Dios, por qué eres tan ruidoso, joven! ¡Cálmate y mide tus palabras al hablar de personas respetadas! Gerard LeCroix dejó Guadalupe con una expedición al continente, pero para ti dejó un mensaje\n¿Te has calmado, señor? ¿Listo para escucharme?";
		link.l1 = "Hm... Por favor, discúlpeme, monsieur. Me exalté un poco. Estoy escuchando.";
		link.l1.go = "trial_1";
	break;

	case "trial_1":
		dialog.text = "Muy bien. La próxima vez intenta preguntar primero, y luego gritar a todo pulmón. De acuerdo... ¿Conoces a un hombre llamado Simon Maurois?";
		link.l1 = "¡Ja! ¡Todos han oído hablar de Simon Maurois! Por supuesto que lo conozco.";
		link.l1.go = "trial_2";
		link.l2 = "  Nunca he oído hablar de él. ¿Quién es? ";
		link.l2.go = "trial_3";
	break;

	case "trial_2":
		dialog.text = "Excelente. Ve a él, entonces. Fue él quien financió la expedición del monsieur Shoke, así que puedes recoger tu recompensa de él. Entonces, ¿era realmente necesario ponerse tan alterado?";
		link.l1 = "Una vez más, le ruego que me disculpe... Gracias por su ayuda, monsieur. ¡Veré a monsieur Maurois de inmediato!";
		link.l1.go = "trial_exit";
	break;

	case "trial_3":
		dialog.text = "Él es el dueño de la casa bancaria Maurois y el jefe de la sucursal en Capsterville. Así que tendrás que ir a Saint-Christopher y visitar el banco de Capsterville. Fue monsieur Maurois quien financió la expedición de monsieur Shoke, así que puedes cobrar tu recompensa de él. Entonces, ¿realmente era necesario ponerse tan furioso?";
		link.l1 = "Una vez más, le pido disculpas... Gracias por su ayuda, monsieur. ¡Iré a ver a monsieur Maurois de inmediato!";
		link.l1.go = "trial_exit";
	break;

	case "trial_exit":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		DeleteAttribute(npchar, "quest.trial_usurer");
		pchar.questTemp.Trial = "usurer";
		AddQuestRecord("Trial", "22");
	break;*/

	// belamour legendary edition на пару с Акулой -->
	case "SharkGoldFleet":
		dialog.text = "Ah, ¡el comerciante emprendedor! Se nota enseguida el enfoque comercial. Lo respeto. Claro, tengo la mercancía que necesitas.";
		link.l1 = "Estoy seguro de que puedo venderlo con ganancia. Hasta donde sé, hay una buena demanda de este producto en Portobello. ¿Cuánto me costará?";
		link.l1.go = "SharkGoldFleet_01";
		break;

	case "SharkGoldFleet_01":
		pchar.questTemp.SharkGoldFleet = "buyincar";
		dialog.text = "Regular... Entonces, trescientas unidades de café... Y la misma cantidad de cacao... Te costará..." + sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)) + " ¡pesos!";
		if (pchar.money < sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
		{
			link.l1 = "Hmm... Disculpe, parece que no tengo suficiente dinero. Espere, por favor: corro al barco por dinero ahora mismo, ¡y regresaré enseguida!";
			link.l1.go = "exit";
		}
		else
		{
			link.l1 = "Aquí tienes.";
			link.l1.go = "SharkGoldFleet_02";
		}
		break;

	case "SharkGoldFleet_02":
		if (GetCargoFreeSpace(pchar) < 1200)
		{
			dialog.text = "Un momento, señor. Parece que no tienes suficiente espacio en tu barco para tal grupo. Despeja la bodega y regresa.";
			link.l1 = "¡Oh, olvidé descargar! Espera un minuto, ¡ya voy!";
			link.l1.go = "exit";
		}
		else
		{
			dialog.text = "¡Estupendo! Inmediatamente daré la orden para que las mercancías sean cargadas en tu barco. ¡Es un placer hacer negocios contigo!";
			link.l1 = "¡Mutuamente, señor! Y ahora permítame retirarme: las cosas no esperan.";
			link.l1.go = "SharkGoldFleet_03";
		}
		break;

	case "SharkGoldFleet_03":
		DialogExit();
		AddMoneyToCharacter(pchar, -sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
			SetCharacterGoods(pchar, GOOD_COFFEE, GetCargoGoods(pchar, GOOD_COFFEE) + 300);
		SetCharacterGoods(pchar, GOOD_CHOCOLATE, GetCargoGoods(pchar, GOOD_CHOCOLATE) + 300);
		AddQuestRecord("SharkGoldFleet", "4");
		pchar.questTemp.SharkGoldFleet = "toCarPortOffice";
		break;

	case "SharkGoldFleet_again":
		dialog.text = "Las mercancías te están esperando. ¿Trajiste dinero?";
		if (pchar.money < sti(GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_COFFEE, PRICE_TYPE_BUY, pchar, 300) + GetStoreGoodsPrice(&stores[sti(rColony.StoreNum)], GOOD_CHOCOLATE, PRICE_TYPE_BUY, pchar, 300)))
		{
			link.l1 = "Aún no. Solo quería asegurarme de que tu oferta sigue en pie. Y el dinero llegará pronto.";
			link.l1.go = "exit";
		}
		else
		{
			link.l1 = "Aquí tienes.";
			link.l1.go = "SharkGoldFleet_02";
		}
		break;
	//<-- на пару с Акулой
	case "no_quests":
		dialog.text = "En este momento no necesito de tus servicios.";
		link.l1 = "Lástima. Cambiemos de tema.";
		link.l1.go = "node_1";
		break;

	case "fight":
		DialogExit();
		NextDiag.CurrentNode = NextDiag.TempNode;
		LAi_group_Attack(NPChar, Pchar);
		break;

	case "Exit":
		Nextdiag.CurrentNode = Nextdiag.TempNode;
		DialogExit();
		break;
	}
	LanguageCloseFile(iSeaGoods);
}

int findStoreMan(ref NPChar, int iTradeNation)
{
	ref ch;
	int n;
	int storeArray[30];
	int howStore = 0;

	for (n = 0; n < MAX_CHARACTERS; n++)
	{
		makeref(ch, Characters[n]);
		if (CheckAttribute(ch, "Dialog.Filename") && ch.Dialog.Filename == "Common_Store.c") // магазин
		{
			if (sti(ch.nation) != iTradeNation)
				continue;
			if (NPChar.id == ch.id)
				continue;
			if (NPChar.id == "Panama_trader" || ch.id == "Panama_trader")
				continue; // нельзя доплыть
			if (NPChar.id == "SanAndres_trader" || ch.id == "SanAndres_trader")
				continue; // fix 2016-03-07
			if (ch.location == "none")
				continue; // фикс для новых, невидимых до поры островов
			if (GetIslandByCityName(ch.city) == GetIslandByCityName(NPChar.city))
				continue; // хрен вам, а не читы!
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0)
	{
		return -1;
	}
	else
	{
		return storeArray[rand(howStore - 1)];
	}
}

int Sunplace_Shiptype() // new
{
	int i;

	if (sti(pchar.rank) >= 1 && sti(pchar.rank) < 6)
		i = SHIP_SCHOONER;
	if (sti(pchar.rank) >= 6 && sti(pchar.rank) < 11)
		i = SHIP_FLEUT;
	if (sti(pchar.rank) >= 11 && sti(pchar.rank) < 18)
		i = SHIP_PINNACE;
	if (sti(pchar.rank) >= 18)
		i = SHIP_GALEON_L;

	return i;
}

string findSunplaceCity(ref NPChar) // new
{
	int n, nation;
	int storeArray[2];
	SetArraySize(&storeArray, MAX_COLONIES);
	int howStore = 0;

	for (n = 0; n < MAX_COLONIES; n++)
	{
		nation = GetNationRelation(sti(pchar.nation), sti(colonies[n].nation));
		if (nation != RELATION_ENEMY && colonies[n].id != "Panama" && colonies[n].id != "LosTeques" && colonies[n].id != "SanAndres" && colonies[n].nation != "none" && GetIslandByCityName(npchar.city) != colonies[n].islandLable) // на свой остров
		{
			storeArray[howStore] = n;
			howStore++;
		}
	}
	if (howStore == 0)
		return "none";
	nation = storeArray[hrand(howStore - 1)];
	return colonies[nation].id;
}
