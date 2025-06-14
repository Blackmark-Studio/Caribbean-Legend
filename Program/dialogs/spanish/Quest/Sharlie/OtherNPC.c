// диалог прочих и малозначимых НПС
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	bool bOk;
	int i, n, iTemp;
	string attrL;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	attrL = Dialog.CurrentNode;
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			dialog.text = "¿Hay algo que necesites?";
			link.l1 = "No, no ahora mismo.";
			link.l1.go = "exit";			
			NextDiag.TempNode = "First time";
		break;
		
		// --> матрос на корабле, прибытие в Сен-Пьер
		case "Startsailor":
			dialog.text = "¡Malditos sean mis ojos, tierra a la vista al fin! Despierta, Monsieur... como te llames... ¡Hemos llegado!";
			link.l1 = "¡A-ah! ¿Ya es de mañana? ¿Qué es este maldito calor y humedad?";
			link.l1.go = "Startsailor_1";
			link.l2 = "¡Por Dios! ¡Charles de Maure! Un noble, ¿sabes? ¿Cómo puedes siquiera beber con este calor? Yo preferiría un poco de agua, por el amor del cielo.";
			link.l2.go = "Startsailor_1a";
		break;
		
		case "Startsailor_1":
			dialog.text = "Acostúmbrese, Monsieur. Este es el único clima que tenemos aquí... siempre podría ser peor.";
			link.l1 = "¿Cómo podría empeorar!? ¡Solo llevo una camisa de lino y tengo el sudor corriendo por mi espalda!";
			link.l1.go = "Startsailor_2";			
		break;
		
		case "Startsailor_2":
			dialog.text = "¡Ya verás, jaja! ¡Podría ser temporada de huracanes! Date prisa, monsieur. El bote no va a esperarte. No querrás nadar hasta Martinica, ¿verdad?";
			link.l1 = "Solo dame un momento, ¿quieres? ¿Dónde está mi espada? Ah, aquí está...";
			link.l1.go = "Startsailor_3";			
		break;
		
		case "Startsailor_3":
			dialog.text = "Ya no estás en Europa... Ten cuidado, monsieur. Estos son tiempos difíciles. El rumor dice que la Compañía de las Islas Americanas vendió la isla de Martinica a unos fanáticos religiosos, cruzados o alguna tontería así. Aún no he notado nada inusual, al menos mirando a la costa desde la cubierta. Pero desde que nos fuimos por un tiempo, mucho podría haber cambiado en mi ausencia.";
			link.l1 = "¿Cruzados? ¡Tonterías!";
			link.l1.go = "Startsailor_4";			
		break;
		
		case "Startsailor_4":
			dialog.text = "Ya sean disparates o no, los rumores están desenfrenados. Ya tenemos suficientes problemas como están. Caníbales en la selva, fiebre tropical, piratas, bandidos en los callejones, por no hablar de los españoles y los ingleses...";
			link.l1 = "Oh, aquí vamos de nuevo... Ahora mismo el único tipo de problema que veo es el calor agobiante y los mosquitos... Muy bien, estoy listo. ¿Vamos?";
			link.l1.go = "Startsailor_5";			
		break;
		
		case "Startsailor_5":
			dialog.text = "Suba a cubierta y suba al bote, Monsieur. ¡Bienvenido al Caribe!";
			link.l1 = "";
			link.l1.go = "Startsailor_6";			
		break;
		
		case "Startsailor_1a":
			dialog.text = "No hay otro clima aquí, 'Su Señoría'. Si acaso, solo empeora.";
			link.l1 = "El clima es insoportable, al igual que mi compañía estos últimos meses. Espero que haya gente decente en el Archipiélago.";
			link.l1.go = "Startsailor_2a";
			AddCharacterExpToSkill(pchar, "Leadership", 10);
		break;
		
		case "Startsailor_2a":
			dialog.text = "Bueno, entonces, creo que todos estaremos encantados de verlo partir, monsieur. La barca está esperando. No saltes de alegría. Y no olvides tus pertenencias, el barco sigue avanzando, y también podrías olvidarlas si no lo haces.";
			link.l1 = "Como si los dejara para tu placer. Pesos, espada, parece que no me han robado.";
			link.l1.go = "Startsailor_3a";			
		break;
		
		case "Startsailor_3a":
			dialog.text = "Somos gente honesta, por supuesto, pero piensas bien: siempre mantén un ojo en tus cosas, o alguien podría vaciarte los bolsillos. Igual que en la vieja Europa. O en cualquier lugar, en realidad. Pero este lugar no es como casa. Algunos fanáticos han establecido una base aquí. Se dice que compraron toda la isla en secreto. Así que mantente alerta y no llames la atención.";
			link.l1 = "¡Qué tontería!";
			link.l1.go = "Startsailor_4a";			
		break;
		
		case "Startsailor_4a":
			dialog.text = "Eso es el rumor. Agradece que me tomé la molestia de compartirlo y mostrar preocupación por tu estancia aquí. De lo contrario, esa delicada rosa gascona tuya podría marchitarse bajo nuestro ardiente sol. Tonterías o no, mantén tus sentidos alerta, tenemos suficientes problemas sin los fanáticos. Bandidos en los callejones y la jungla, piratas en el mar, y caníbales de piel roja...";
			link.l1 = "¡Ahora, ahora! Me las arreglaré. Puede que esté un poco caluroso para mí ahora, pero estoy curtido por el sol en casa, a diferencia de, digamos, esos normandos. Y si algo se puede resolver con una espada, puedes contar conmigo. ¡Pero los mosquitos, ahora eso es puro tormento! Bueno, todas mis cosas están contabilizadas. ¿Dices que el barco está listo?";
			link.l1.go = "Startsailor_5a";			
		break;
		
		case "Startsailor_5a":
			dialog.text = "Esperando ansiosamente. ¿Espero que pueda venir usted mismo, monsieur? Cabeza en alto, y con suerte, no se perderá desde aquí. Ah, y bienvenido al Archipiélago, je-je.";
			link.l1 = "Sí, gracias. El único consuelo es que no estaré aquí por mucho tiempo.";
			link.l1.go = "Startsailor_6";			
		break;
		
		case "Startsailor_6":
			DialogExit();
			AddDialogExitQuestFunction("SharlieTutorial_StartGameInMartinique");
		break;
		// <-- матрос на корабле, прибытие в Сен-Пьер
		
		// горожанин знает Мишеля
		case "Benuatalker":
			DelLandQuestMark(npchar);
			link.l1 = "Disculpe, "+GetAddress_FormToNPC(NPChar)+", ¿podrías decirme dónde puedo encontrar a Michel de Monper? Tiene que estar en algún lugar de tu ciudad.";
            link.l1.go = "Benuatalker_1";
		break;
		
		case "Benuatalker_1":
			dialog.text = "Hmm... Veo que has llegado aquí recientemente, ya que preguntas tales cosas sin miedo... Te aconsejo que lo dejes o te meterás en problemas. Y sobre tu pregunta... Habla con el Abad. Puedes encontrarlo en la iglesia.";
			link.l1 = "¡Gracias!";
            link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			AddDialogExitQuest("Sharlie_SetBenua");
			QuestPointerToLoc("FortFrance_town", "reload", "reload7_back");
		break;
		
		// --> арест в резиденции
		case "Sharlie_arest":
			dialog.text = "¡Alto! ¡Entregad vuestras armas de inmediato, Monsieur, y seguidnos!";
			link.l1 = "¿Qué demonios es esto?";
			link.l1.go = "Sharlie_arest_1";
			if (CheckCharacterItem(PChar, "knife_03")) pchar.Sharlie.KnifeMonpe = true;
		break;
		
		case "Sharlie_arest_1":
			DialogExit();
			chrDisableReloadToLocation = false;
			DoFunctionReloadToLocation("FortFrance_prison", "goto", "goto9", "Puancie_InJail");
			WaitDate("", 0, 0, 2, 0, 10); //крутим время
			RecalculateJumpTable();
			RemoveAllCharacterItems(PChar, true);
			sld = characterFromId("Puancie");
			sld.dialog.currentnode = "Puancie_Jail"; 
			LAi_SetActorTypeNoGroup(sld);
			ChangeCharacterAddressGroup(sld, "FortFrance_prison", "goto", "goto13");
		break;
		// арест в резиденции
		
		// --> офицер базы
		case "Maltie_officer":
			ref location = &Locations[FindLocation(pchar.location)];
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "begin")
			{
				dialog.text = "Me alegra verte, Monsieur de Maure. ¿Cuál es la ocasión?";
				link.l1 = TimeGreeting()+", oficial. Me gustaría hablar con mi hermano, Michel de Monper. Fuera del registro, por supuesto. Estoy tratando de averiguar sobre su servicio aquí en el Caribe.";
				link.l1.go = "spanish";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.Guardoftruth") && pchar.questTemp.Guardoftruth == "think")
			{
				dialog.text = "¿Cómo fue el interrogatorio? ¿Encontraste algo de valor?";
				link.l1 = "¡Oh sí! Tanto que me llevo a este español conmigo de regreso a mi barco. Es un testigo importante y debe ser llevado a San Cristóbal para más interrogatorios.";
				link.l1.go = "spanish_10";
				break;
			}
			if (!CheckAttribute(location, "first_meeting"))
			{
				dialog.text = "¿Cuál es su negocio aquí, Monsieur?";
				link.l1 = "He venido a ver a mi hermano, Michel de Monper.";
				link.l1.go = "Maltie_officer_1";
				location.first_meeting = true;
			}
			else
			{
				dialog.text = "Monsieur, debo recordarle suavemente que se encuentra dentro de un cantón militar. Compórtese en consecuencia.";
				link.l1 = "Sí, señor. Por supuesto.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
			
			if (SandBoxMode)
			{
				dialog.text = "Monsieur, debo recordarle gentilmente que se encuentra dentro de un cantón militar. Compórtese en consecuencia.";
				link.l1 = "Sí, señor. Por supuesto.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Maltie_officer";
			}
		break;
		
		case "Maltie_officer_1":
			DelLandQuestMark(npchar);
			dialog.text = "Michel de Monper está actualmente bajo guardia en una de nuestras casamatas, retenido bajo la orden personal del Caballero Philippe de Poincy. Baja al nivel inferior. Encontrarás las casamatas que usamos para almacenamiento y celdas allí. Creo que puedes encontrar el camino.";
			link.l1 = "¡Gracias!";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_officer";
			QuestPointerToLoc("FortFrance_Dungeon", "quest", "quest1");
		break;
		// офицер базы
		
		// --> солдаты базы
		case "Maltie_soldier":
			dialog.text = "Hola, Monsieur. ¿Puedo ayudarle en algo?";
			link.l1 = "Gracias, soldado, pero no, estoy bastante bien. Sigue con lo tuyo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Maltie_soldier";
		break;
		// --> солдаты базы
		
		// --> мальтиец-проводник
		case "Sharlie_maltie":
			dialog.text = "Gracias por esperar, Monsieur. ¿Está buscando a Michel de Monper? ¿Es usted su hermano?";
			link.l1 = "Sí, eso es correcto. Soy su hermano Charles. Debo verlo de inmediato. ¿Está Michel en problemas?";
			link.l1.go = "Sharlie_maltie_1";			
		break;
		
		case "Sharlie_maltie_1":
			dialog.text = "Lamentablemente lo está, Monsieur. Michel está encerrado en una de las casamatas abajo. El Caballero de Poincy, el Gobernador General de las colonias francesas en el Nuevo Mundo, firmó personalmente la orden de su arresto. Todos nosotros quedamos impactados. ¡Tu hermano es un ejemplo de virtud masculina, disciplina y coraje, el orgullo de nuestra Orden! ¡Lo peor es que nosotros, sus amigos, tenemos que encerrarlo tras las rejas y vigilarlo como a un criminal común! Hacemos todo lo posible para que esté cómodo, pero... la prisión sigue siendo prisión.";
			link.l1 = "¿De qué se le acusa? ¿Ha cometido un crimen?";
			link.l1.go = "Sharlie_maltie_1_1";			
		break;
		
		case "Sharlie_maltie_1_1":
			dialog.text = "¡La oficina del Gobernador General acusó a Michel de malversación! ¡Qué ridículo! Todos nosotros aquí estamos convencidos de que es políticamente motivado. Te diré algo en confianza. Michel ha estado participando en ciertas acciones encubiertas en nombre de la Orden. Quizás descubrió más de lo que debía. O peor, enfureció a algunos hombres poderosos. ¿Pero robar dinero? Nadie cree eso. Es un pretexto, no una razón real, ¡un pretexto cobarde e innoble! Pero suficientes palabras. Tu hermano está deseando verte, estoy seguro de que él mismo te contará todo.";
			link.l1 = "Bien. ¿Dónde está ubicada tu prisión?";
			link.l1.go = "Sharlie_maltie_1_2";
		break;
		
		case "Sharlie_maltie_1_2":
			dialog.text = "En nuestro arsenal subterráneo, aquí mismo en la ciudad. Sígueme. Te mostraré el camino.";
			link.l1 = "...";
			link.l1.go = "Sharlie_maltie_2";
		break;
		
		case "Sharlie_maltie_2":
			DialogExit();
			LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "FortFrance_town", "officers", "reload7_1", "Maltie_GoTown", -1);
		break;
		
		case "Sharlie_maltie_3":
			DelLandQuestMark(npchar);
			AddLandQuestMark(characterFromId("Maltie_officer"), "questmarkmain");
			dialog.text = "Aquí estamos. Esta es nuestra base de operaciones: el Capítulo Caribeño de la Orden Militar Hospitalaria de San Juan de Jerusalén, de Rodas y de Malta. Las casamatas están debajo de nosotros. Baja por el pasillo, pasando el comedor y la capilla. Las escaleras allí te llevarán al nivel inferior. Busca un corredor lleno de celdas. Encontrarás a tu hermano en una cerca del fondo.\nVe, Charles, y que Dios esté contigo. ¡Por favor, ayuda a Michel! Él es inocente, todos aquí están listos para jurarlo.";
			link.l1 = "Todo el motivo por el que vine a este agujero de mierda es para ver a mi hermano. Espero poder sacarlo de este aprieto al menos.";
			link.l1.go = "Sharlie_maltie_4";
		break;
		
		case "Sharlie_maltie_4":
			DialogExit();
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.lifeday = 0;
			LAi_ActorGoToLocator(npchar, "goto", "goto1", "none", -1);
		break;
		
		//belamour cle -->
		case "Sharlie_maltieA":
			dialog.text = "¿Entonces estabas buscando a Michel de Monper? ¿Y tú eres su hermano?";
			link.l1 = "Sí, eso es correcto. Soy su hermano Charles. Necesito verlo de inmediato. Se ha metido en problemas, ¿verdad?";
			link.l1.go = "Sharlie_maltie_1a";			
		break;
		
		case "Sharlie_maltie_1a":
			dialog.text = "Desafortunadamente, así es, Monsieur. Michel está arrestado y encerrado en nuestra prisión. El propio Chevalier de Poincy, el gobernador general de las colonias francesas, dio y firmó las órdenes. Todos quedamos conmocionados. \n¡Su hermano es un ejemplo de hombría, firmeza y coraje, un orgullo de nuestra Orden! ¡La peor parte es que nosotros, sus amigos, tenemos que cerrar su celda y custodiarlo como a un criminal! Hacemos todo lo posible para aliviar su situación, pero... la prisión es la prisión.";
			link.l1 = "¿De qué se le acusa? ¿Ha cometido un crimen?";
			link.l1.go = "Sharlie_maltie_1_1a";			
		break;
		
		case "Sharlie_maltie_1_1a":
			dialog.text = "¡Tonterías! ¡Puras tonterías! Han acusado a Michel de peculado y de robar dinero del estado. ¡Ridículo! Todos estamos seguros de que es solo un juego político. Michel había estado participando en operaciones secretas de la Orden, quizás, aprendió más de lo que debía.\nO algo más. ¡Pero robar dinero! Nadie cree eso. Es solo un pretexto, no una razón, ¡un pretexto tan burdo y estúpido! Pero basta de palabras. Tu hermano está deseando verte, estoy seguro de que él mismo te contará todo.";
			link.l1 = "Bien. ¿Dónde se encuentra la prisión?";
			link.l1.go = "Sharlie_maltie_1_2a";
		break;
		
		case "Sharlie_maltie_1_2a":
			dialog.text = "Está ubicado en nuestra base subterránea, aquí en la ciudad. Sígueme. Te mostraré el camino.";
			link.l1 = "...";
			link.l1.go = "Sharlie_maltie_2a";
		break;
		
		case "Sharlie_maltie_2a":
			DialogExit();
			//LAi_ActorGoToLocation(npchar, "reload", "reloadPr1", "FortFrance_Dungeon", "reload", "reload1", "", -1);
			Pchar.quest.Sharlie_Maltie.win_condition.l1 = "location";
			Pchar.quest.Sharlie_Maltie.win_condition.l1.location = "FortFrance_town";
			Pchar.quest.Sharlie_Maltie.win_condition = "Maltie_GoBasement";
			QuestPointerDelLoc("FortFrance_prison", "reload", "reload1");
		break;
		//<-- cle
		// мальтиец-проводник
		
		// --> найм матросов
		case "Sharlie_sailor":
			DelLandQuestMark(npchar);
			dialog.text = "¡Y luego se asomó por la borda y echó tanto que hasta el Caribe se puso verde! ¡Ja, ja, ja!";
			link.l1 = "¿Alonso?";
			link.l1.go = "Sharlie_sailor_1";
		break;
		
		case "Sharlie_sailor_1":
			dialog.text = "¡Oh! Charles, justo estaba contando a los muchachos nuestras aventuras.";
			link.l1 = "Ya me di cuenta. Escucha, Alonso. Me he... convertido en capitán.";
			link.l1.go = "Sharlie_sailor_2";
		break;
		
		case "Sharlie_sailor_2":
			dialog.text = "¿Ya? ¡Pensé que le tomaría al menos un mes, ja, ja!";
			link.l1 = "¡Hablo en serio!";
			link.l1.go = "Sharlie_sailor_3";
		break;
		
		case "Sharlie_sailor_3":
			dialog.text = "Si solo fuera por mí, me uniría de inmediato. Pero tengo a cuarenta hombres de la Ulysse conmigo. Han confiado en mí su futuro; debo estar seguro de que no les fallará\n"+
			"¿Qué tipo de barco tiene?";
			link.l1 = "Un barco como cualquier otro, "+GetStrSmallRegister(XI_ConvertString(GetBaseShipParamFromType(sti(RealShips[sti(pchar.ship.type)].basetype), "Name")))+". ¿Es tan importante?";
			link.l1.go = "Sharlie_sailor_4";
		break;
		
		case "Sharlie_sailor_4":
			dialog.text = "Ya sabe, después de la Ulysse preferimos no servir en una simple barca o tartana. Ya hemos visto su barco y a los muchachos les gusta\n"+
			"Ahora, el dinero. Pedimos 4.800 pesos por adelantado. Después, como siempre, a partes. No pedimos nada excesivo, se lo aseguro. ¿Puede con ello?";
			if (sti(Pchar.money) >= 4800)
			{
				link.l1 = "¡Trato hecho! Aquí tiene su dinero.";
				link.l1.go = "Sharlie_sailor_5";
			}
			link.l2 = "Lamentablemente, no tengo tanto dinero conmigo en este momento.";
			link.l2.go = "Sharlie_sailor_nomoney";
		break;
		
		case "Sharlie_sailor_5":
			if (GetSquadronGoods(pchar, GOOD_FOOD) < 20 || GetSquadronGoods(pchar, GOOD_MEDICAMENT) < 30)
			{
				dialog.text = "¿Tienes víveres en la bodega, capitán? ¿Y medicinas? ¿No? Pues, eso no sirve. Sal a conseguir lo mínimo para nuestro viaje y luego regresa y hablaremos. Ve a la tienda y consigue lo que necesites.";
				link.l1 = "Mm. Tienes razón. De acuerdo, haré eso.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				AddMoneyToCharacter(pchar, -4800);
				dialog.text = "¡Vaya! ¡Felicidades... capitán! Reúno a los muchachos y vamos a su barco.";
				link.l1 = "Encantado de continuar nuestra aventura, Alonso. ¡Prepara el barco para zarpar!";
				link.l1.go = "Sharlie_sailor_6";
			}
		break;
		
		case "Sharlie_sailor_6":
			DialogExit();
			LAi_SetStayType(npchar);
			GetCharacterPos(pchar, &locx, &locy, &locz);
			ChangeCharacterAddressGroup(npchar, "Fortfrance_tavern", "goto", LAi_FindNearestFreeLocator("goto", locx, locy, locz));
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", 5);
			npchar.lifeday = 0;
			SetCrewQuantityOverMax(PChar, 40);
			pchar.Ship.Crew.Morale = 50;
			pchar.Ship.Crew.Exp.Sailors = 50;
			pchar.Ship.Crew.Exp.Cannoners = 50;
			pchar.Ship.Crew.Exp.Soldiers = 50;
			AddQuestRecord("Sharlie", "7");
			pchar.questTemp.Sharlie = "skiper";
			DeleteAttribute(pchar, "GenQuest.CannotWait");//снимаем запрет, если не был снят раньше
			AddLandQuestMark(characterFromId("FortFrance_tavernkeeper"), "questmarkmain");
		break;
		
		case "Sharlie_sailor_nomoney":
			dialog.text = "Bueno, tan pronto como encuentres suficiente dinero, vuelve. Nos encontrarás aquí en la taberna. No hay otros barcos alrededor de todos modos. Seguiremos bebiendo y derrochando nuestro dinero en mujeres, ¡harhar!";
			link.l1 = "Intentaré regresar lo antes posible.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Sharlie_sailor_again";
		break;
		
		case "Sharlie_sailor_again":
			dialog.text = "¿De vuelta, capitán? ¿Listo para contratarme a mí y a mis compañeros? ¡Nuestros bolsillos empiezan a sentirse ligeros, necesitamos sentir la brisa del mar en nuestras caras otra vez!";
			if (sti(Pchar.money) < 4800)
			{
				link.l1 = "Aún no, todavía estoy preparando todo.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Sharlie_sailor_again";
			}
			else
			{
				link.l1 = "Sí. Toma tu adelanto. Ahora estás a mi servicio.";
				link.l1.go = "Sharlie_sailor_5";
			}
		break;
		// найм матросов
		
		// наводчик на штурмана
		case "skipertalker":
			DelLandQuestMark(npchar);
			dialog.text = LinkRandPhrase("¡Ahoy, capitán! ¿Qué necesitas?","Hola Monsieur. ¿Qué puedo hacer por usted?","Buen día. ¿Qué quieres?");
			link.l1 = RandPhraseSimple("Tengo una pregunta para ti.","Necesito información sobre esta colonia.");
			link.l1.go = "skipertalker_1";
			link.l2 = "Solo diciendo hola. ¡Au revoir!";
			link.l2.go = "exit";
			NextDiag.TempNode = "skipertalker";
		break;
		
		case "skipertalker_1":
			dialog.text = RandPhraseSimple("¿Qué es?","¿Qué necesitas?");
			link.l1 = "Escucha, "+GetAddress_FormToNPC(NPChar)+", aquí está el asunto... Estoy buscando un navegante. ¿Quizás conoces a alguien apto para el trabajo aquí en el pueblo?";
			link.l1.go = "skipertalker_2";
		break;
		
		case "skipertalker_2":
			dialog.text = "¿Un navegante? Hm. Bueno, conozco a uno... Solo hay un problema: está en la cárcel, en prisión por deudas. El pobre desgraciado lleva encerrado en los casamatas casi un mes, hasta que él o alguien más pague lo que debe.";
			link.l1 = "¿Un deudor? Hm... ¿Cómo se llama?";
			link.l1.go = "skipertalker_3";
		break;
		
		case "skipertalker_3":
			dialog.text = "Su nombre es Folke Deluc. Pregunta al comandante de la prisión si deseas verlo. Pero no creo que lo dejen salir de allí a menos que pagues su deuda, porque él seguro que no lo hará, ¡jajaja!";
			link.l1 = "Tal vez lo haga. Gracias por la información, amigo.";
			link.l1.go = "exit";
			LAi_CharacterDisableDialog(npchar);
			npchar.lifeday = 0;
			pchar.questTemp.Sharlie = "jailskiper";
			AddQuestRecord("Sharlie", "8");
			LocatorReloadEnterDisable("Fortfrance_town", "reload_jail", false);
			SetFunctionLocationCondition("FortfranceJailOff_AddQuestMark", "fortfrance_prison", false);
		break;
		
		// --> штурман
		case "Folke":
			dialog.text = "¿A qué debo tal honor, Monsieur?";
			link.l1 = "Hola, Folke. Es simple, tengo un barco, pero no tengo navegante. Y necesito uno. Así que he pagado tu deuda...";
			link.l1.go = "Folke_1";
		break;
		
		case "Folke_1":
			dialog.text = "¿Estás diciendo que me sacaste de aquí para llevarme a tu tripulación?";
			link.l1 = "Exactamente. Creo que rápidamente compensarás el dinero que he gastado en ti. Bueno... ya veremos cómo va.";
			link.l1.go = "Folke_2";
		break;
		
		case "Folke_2":
			dialog.text = "Mi gratitud, Monsieur. Estoy harto de esta podrida y húmeda celda. Me daría un gran placer volver a bordo una vez más. Ah, el mar...";
			link.l1 = "Me alegra que hayamos llegado a un entendimiento, Folke. Una cosa más, ¿tienes alguna otra habilidad además de manejar un barco?";
			link.l1.go = "Folke_3";
		break;
		
		case "Folke_3":
			dialog.text = "Un poco de todo, capitán. Solía servir a bordo de un corsario para la Compañía Holandesa de las Indias Occidentales. Allí aprendí a manejar los cañones, así que puedo servir como artillero si me necesita. El comercio y el abordaje son mis puntos más débiles.";
			link.l1 = "Gracias por compartir, ahora sígueme al barco. Quiero que observes a la tripulación con tu ojo experimentado mientras preparan todo para la partida. Luego, quiero dirigirme a Guadalupe lo antes posible.";
			link.l1.go = "Folke_4";
		break;
		
		case "Folke_4":
			dialog.text = "¡Aye aye, capitán! Te esperaré en tu camarote. *Usa el menú de acciones mientras estés en el mar para acceder al camarote y otras áreas del barco*";
			link.l1 = "Gracias, Folke. Nos vemos a bordo.";
			link.l1.go = "Folke_5";
			Log_Info("Has recibido el amuleto 'Rosario del mercader'.");
			PlaySound("interface\important_item.wav");
			GiveItem2Character(pchar, "obereg_8");
			if(CheckAttribute(pchar,"systeminfo.tutorial.Amulet"))
			{
				DoQuestFunctionDelay("Tutorial_Amulet", 0.1);
			}
		break;
		
		case "Folke_5":
			DialogExit();
			EndQuestMovie();
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			AddQuestRecord("Sharlie", "10");
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.quest.Sharlie_skiper.win_condition.l1 = "location";
			pchar.quest.Sharlie_skiper.win_condition.l1.location = "My_Cabin_Small";
			pchar.quest.Sharlie_skiper.function = "Sharlie_SkiperTalk";
			//прерывание на засаду пиратов - принудительный квест
			pchar.quest.Sharlie_seabattle.win_condition.l1 = "location";
			pchar.quest.Sharlie_seabattle.win_condition.l1.location = "Fortfrance_town";
			pchar.quest.Sharlie_seabattle.function = "SharlieSeabattle_agent";
			
			pchar.quest.NewGameTip2.win_condition.l1 = "location";
			pchar.quest.NewGameTip2.win_condition.l1.location = "Martinique";
			pchar.quest.NewGameTip2.function = "ShowNewGameTip";
			pchar.quest.NewGameTip2.text = "Su primer oficial le está esperando. Utiliza el menú de acción (ENTER) para ir al camarote.";
		break;
		
		case "Folke_6":
			pchar.GenQuest.StoreGoods.StoreIdx = Fortfrance_STORE;
			pchar.GenQuest.StoreGoods.Starting = true; // заполняем магазин 250912
			dialog.text = "¡Un bonito lugre, capitán! Un pequeño barco bastante decente con buen aparejo y maderas sólidas. Con un barco como este no solo llegaremos a salvo a Guadalupe, sino que incluso podríamos navegar por todo el Caribe si así lo deseamos.";
			link.l1 = "Excelente. Al menos no desperdicié mi dinero en un cascarón con goteras... ¿Tienes algún consejo antes de zarpar, Folke?";
			link.l1.go = "Folke_8";
		break;
		
		case "Folke_7":
			dialog.text = "Maldita sea, este balandro está filtrando como un colador, capitán. Será un asunto complicado cruzar hasta Guadalupe. Si quieres llegar a Basse-Terre en una pieza, habrá que llevarla al astillero para reparaciones inmediatamente.";
			link.l1 = "¡No tuve elección, este era el único navío en venta! Y me cobraron un buen dineral por ella. Como sabes, no tenemos tiempo para repararla en este momento... ¿Tienes algún consejo antes de zarpar?";
			link.l1.go = "Folke_8";
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_BALLS) >= 80) && (GetSquadronGoods(pchar, GOOD_GRAPES) >= 80) && (GetSquadronGoods(pchar, GOOD_KNIPPELS) >= 80) && (GetSquadronGoods(pchar, GOOD_BOMBS) >= 80) && (GetSquadronGoods(pchar, GOOD_POWDER) >= 180);
		case "Folke_8":
			if (bOk)
			{
				dialog.text = "Bueno, tenemos suficiente pólvora y munición, capitán. Por ahora basta; solo recuerde reponer a tiempo.";
				link.l1 = "Bueno, eso ni se discute. ¿Algún otro comentario?";
				link.l1.go = "Folke_10";
				if (CheckCharacterItem(PChar, "BoxOfBalls"))
				{
					link.l2 = "¡Ah! Gracias por recordármelo. ¡Tengo una caja entera de balas conmigo!";
					link.l2.go = "Folke_8_1";
				}
			}
			else
			{
				dialog.text = "No tenemos suficiente munición en la santabárbara, capitán. Necesitamos tener al menos cien balas de cañón, disparos de cadena y bombas, así como cien bolsas de metralla y doscientos barriles de pólvora. Compre el material necesario, capitán. No costará mucho, pero nos salvará la vida si somos atacados por piratas o los españoles.";
				link.l1 = "Una inversión digna. Me voy al mercader.";
				link.l1.go = "Folke_9";
			}
		break;
		
		case "Folke_8_1":
			dialog.text = "...¿Y desde cuándo la lleva encima?";
			link.l1 = "Casi dos semanas.";
			link.l1.go = "Folke_8_2";
			TakeItemFromCharacter(pchar, "BoxOfBalls");
			//AddCharacterGoodsSimple(sld, GOOD_BALLS, 10);
			Achievment_Set("ach_CL_164");
		break;
		
		case "Folke_8_2":
			dialog.text = "¡Pero por qué, capitán!";
			link.l1 = "Me gusta coleccionar cachivaches. Nunca se sabe qué puede ser útil.";
			link.l1.go = "Folke_8_3";
		break;
		
		case "Folke_8_3":
			dialog.text = "Bueno, mala suerte. Estas balas no caben en nuestros cañones de juguete. Nunca vi balas tan grandes. Una de esas hundiría a la Adeline.";
			link.l1 = "...";
			link.l1.go = "Folke_10";
		break;
		
		case "Folke_9":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_1";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "12");
		break;
		
		case "Folke_goods_1":
			dialog.text = "¿Has terminado de comprar municiones, capitán?";
			if (bOk)
			{
				link.l1 = "Sí, los tengo. ¿Algún otro comentario?";
				link.l1.go = "Folke_10";
			}
			else
			{
				link.l1 = "Ahora no, todavía estoy trabajando en ello.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_1";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_WEAPON) >= 50);
		case "Folke_10":
			if (bOk)
			{
				dialog.text = "Bien hecho, has comprado suficientes armas para tu tripulación. Si no tenemos suficientes armas, perderemos a muchos más hombres durante las acciones de abordaje. Que Dios nos proteja de eso. No olvides revisar frecuentemente la cantidad en la bodega de carga.\nEs prudente mantener algunas armas de más. A esos malditos ratones les gusta roer los mangos y culatas de madera.";
				link.l1 = "Entendido. ¿Hay algo que desees agregar?";
				link.l1.go = "Folke_11";
			}
			else
			{
				dialog.text = "No tenemos suficientes armas a bordo para la tripulación. Si no tenemos suficientes armas, perderemos muchos más hombres durante los abordajes. Que Dios nos proteja de eso. Según entiendo, tienes cuarenta hombres en la tripulación\nCompra suficientes armas para cada uno, o incluso compra algunas más, cincuenta juegos deberían ser suficientes. Es prudente tener unas cuantas armas más de las que necesitaremos. A esos malditos ratones les gusta roer las culatas y los mangos de madera.";
				link.l1 = "Eso es lo que haré. Volveré pronto.";
				link.l1.go = "Folke_10_1";
			}
		break;
		
		case "Folke_10_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_2";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "13");
		break;
		
		case "Folke_goods_2":
			dialog.text = "¿Has terminado de comprar las armas, capitán?";
			if (bOk)
			{
				link.l1 = "Las armas están en la bodega. ¿Veo que aún hay algo que quieres añadir?";
				link.l1.go = "Folke_11";
			}
			else
			{
				link.l1 = "Ahora no, todavía estoy trabajando en ello.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_2";
			}
		break;
		
		bOk = (GetSquadronGoods(pchar, GOOD_FOOD) >= 100) && (GetSquadronGoods(pchar, GOOD_RUM) >= 10);
		case "Folke_11":
			if (bOk)
			{
				dialog.text = "No, creo que eso es todo. Tenemos suficiente comida, también te has encargado del ron para la tripulación. Eso es sabio, ya que no hay mejor cura para todos los males que un buen trago fresco de ron después de tu turno. Los marineros aman y respetan a los capitanes que les dan su ración diaria de ron. Nunca querrás escuchar a tus hombres preguntar: '¿Por qué se acabó el ron?'";
				link.l1 = "¿Podemos zarpar ahora?";
				link.l1.go = "Folke_12";
			}
			else
			{
				dialog.text = "Sí. Comida y ron. Es desastroso si no tienes suficiente comida a bordo. Siempre ten más víveres de los que crees necesitarás. Nunca sabes cuánto durará un viaje, una calma chicha o un fuerte vendaval pueden arruinar cualquier plan. Los hombres se amotinarán o morirán de hambre cuando se acaben las provisiones.\nEl suministro de ron no es tan crítico, pero recomiendo encarecidamente siempre tener algo a bordo, no hay mejor cura para todos los males que un buen trago de ron fresco después de tu turno. Los marineros aman y respetan a los capitanes que les dan su ración diaria de ron.\nAsí que ve y compra los suministros que necesitamos, al menos cien cajas de comida y diez barriles de ron. Nunca querrás oír a tus hombres preguntar: '¿Por qué se acabó el ron?'";
				link.l1 = "Supongo que tienes razón. Iré a visitar nuevamente al mercader.";
				link.l1.go = "Folke_11_1";
			}
		break;
		
		case "Folke_11_1":
			DialogExit();
			NextDiag.CurrentNode = "Folke_goods_3";
			LAi_SetStayType(npchar);
			AddQuestRecord("Sharlie", "14");
		break;
		
		case "Folke_goods_3":
			dialog.text = "¿Has terminado de comprar nuestra comida y ron, capitán?";
			if (bOk)
			{
				link.l1 = "Sí. ¿Podemos zarpar ahora?";
				link.l1.go = "Folke_12";
			}
			else
			{
				link.l1 = "No, todavía estoy trabajando en ello.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Folke_goods_3";
			}
		break;
		
		case "Folke_12":
			dialog.text = "Sí, capitán. Podemos levar anclas y dirigirnos al norte hacia Guadalupe, como usted deseaba.";
			// belamour legendary edition -->
			link.l1 = "Buen trabajo, Folke. No lo habría logrado sin ti.";
			link.l1.go = "Folke_13";
			link.l2 = "Está bien, pongámonos a trabajar, veamos si vales el dinero.";
			link.l2.go = "Folke_13a";
		break;
		
		case "Folke_13a":
			Npchar.loyality = makeint(Npchar.loyality) - 5;
			ChangeCharacterComplexReputation(pchar,"authority", 5);
			dialog.text = "Entonces ponme como navegante y me iré a mi lugar en cubierta.";
			link.l1 = "Estoy aquí para encontrar a mi hermano, Michel de Montpe.";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_13":
			Npchar.loyality = makeint(Npchar.loyality) + 5;
			AddCharacterExpToSkill(pchar, "Leadership", 150);
			// <-- legendary edition
			dialog.text = "Entonces ponme como navegante y me iré a mi puesto en cubierta.";
			link.l1 = "...";
			link.l1.go = "Folke_14";
		break;
		
		case "Folke_14":
			DialogExit();
			LAi_SetStayType(npchar);
			LAi_SetImmortal(npchar, false);
			AddQuestRecord("Sharlie", "15");
			pchar.questTemp.Sharlie = "seabattle";//в Ле Франсуа
			DeleteAttribute(pchar, "NoNavyPenalty"); // штрафуем за нехватку навигации
			
			npchar.quest.OfficerPrice = 20;
			npchar.loyality = 30;
			
			// --> копипаста LandEnc_OfficerHired
			AddPassenger(pchar, npchar, false);
			npchar.Payment = true;
			npchar.DontClearDead = true;
			SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
			// <--
			
			pchar.questTemp.HelenDrinking.TakeFolke = true;
			
			DoQuestFunctionDelay("Tutorial_Navigator2", 1.0);
			//DoQuestFunctionDelay("Ngt_FolkeEng", 3.0);
			//NewGameTip("Welcome aboard your new officer! Press F4 to assign him as your Navigator.");
			pchar.questTemp.Sharlie.FolkeWait = true;
			LocatorReloadEnterDisable("My_Cabin_Small", "reload1", true);
			NextDiag.CurrentNode = "Folke_wait";
		break;
		
		case "Folke_wait":
			dialog.text = "¡Listo para zarpar, capitán!";
			link.l1 = "...";
			
			if (!CheckAttribute(npchar, "navigator")) {
				dialog.text = "Capitán, ponme como navegante, de lo contrario encallaremos en un santiamén.";
				link.l1 = "Entendido, lo haré ahora.";
			}
			
			link.l1.go = "exit";
			NextDiag.TempNode = "Folke_wait";
		break;
	
		// штурман

	// --> пират-обманщик
		case "Seabattle_pirate":
			dialog.text = "Mis disculpas. ¿"+GetFullName(pchar)+"?";
			link.l1 = "Correcto. ¿A qué debo esta ocasión, señor?";
			link.l1.go = "Seabattle_pirate_1";
		break;
		
		case "Seabattle_pirate_1":
			dialog.text = "Permíteme presentarme, "+GetFullName(npchar)+"He sido enviado aquí por César Craig. Debes conocerlo. Es el dueño de la taberna en Le Francois. Hasta donde él sabe, estás a punto de partir a Guadalupe. Le gustaría ofrecerte algo de dinero fácil.";
			link.l1 = "Mm... ¡Interesante! ¿Y cómo es que César Craig se ha informado tan bien?";
			link.l1.go = "Seabattle_pirate_2";
		break;
		
		case "Seabattle_pirate_2":
			dialog.text = "Es simple, capitán. Tu barco es el único en Saint-Pierre en este momento, cualquiera con dos oídos y un ojo sabe todo sobre quién eres y adónde vas. Aquí en las colonias, los rumores vuelan más rápido que las gaviotas. Entonces, ¿estás interesado en escuchar nuestra oferta?";
			link.l1 = "Claro. Nunca me opongo a ganar algo de dinero.";
			link.l1.go = "Seabattle_pirate_3";
		break;
		
		case "Seabattle_pirate_3":
			dialog.text = "¡Ahora estamos hablando, camarada! Veo que tienes un fino olfato para los negocios. Aquí está el trato. César necesita urgentemente un lote de vino entregado a Guadalupe. Doscientos barriles, la bodega de tu barco puede llevar eso fácilmente. El pago es de diez mil pesos por un trabajo sencillo: César tiene prisa, y tu barco es el único en el puerto ahora mismo. Debes admitir, propuestas tan lucrativas son raras.";
			link.l1 = "¡Maldita sea!, ¿diez mil pesos? Bueno, ¡tenemos un trato!";
			link.l1.go = "Seabattle_pirate_4";
		break;
		
		case "Seabattle_pirate_4":
			dialog.text = "Dirígete a Le Francois y habla con César. Él se encargará de todo. Todo lo que tendrás que hacer es anclar en la bahía justo fuera de Le Francois. No me falles, camarada, César me prometió mil pesos si te convencía...";
			link.l1 = "No te preocupes, considérame convencido. Tan pronto como esté listo para partir, navegaré directamente a Le Francois.";
			link.l1.go = "Seabattle_pirate_5";
		break;
		
		case "Seabattle_pirate_5":
			dialog.text = "¡Hurra! Me voy a conseguir mis mil. ¡Gracias, compañero!";
			link.l1 = "De nada...";
			link.l1.go = "Seabattle_pirate_6";
		break;
		
		case "Seabattle_pirate_6":
			DialogExit();
			AddLandQuestMark(characterFromId("LeFransua_tavernkeeper"), "questmarkmain");
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "gate_back", "", "", "", "", -1);
			AddQuestRecord("Sharlie", "11");
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			chrDisableReloadToLocation = false;//открыть локацию
			npchar.location = "None";
		break;
	// пират-обманщик

	// офицер Гриффондора
		case "griffondor_officer":
			dialog.text = "";
			link.l1 = "";
			link.l1.go = "exit";
		break;

	// командир абордажной роты по защите Сен-Пьера
		case "rosetti":
			PlaySound("Voice\Spanish\EvilPirates01.wav");
			dialog.text = "¡Capitán, el grupo de abordaje está formado y listo! ¡Esperamos tus órdenes!";
			link.l1 = "";
			link.l1.go = "rosetti_1";
		break;
		
		case "rosetti_1":
			DialogExit();
			bDisableCharacterMenu = true;//лоченые интерфейсы
			ChangeShowIntarface();
			LAi_SetActorType(pchar);
			SetMainCharacterIndex(GetCharacterIndex("DefendSP_soldier_0"));
			PChar = GetMainCharacter();			
			LAi_SetPlayerType(PChar);
			sld = characterFromId("Blaze");
			sld.dialog.filename = "MainHero_dialog.c";
			sld.dialog.currentnode = "SP_defend";
			LAi_SetActorType(sld);
			LAi_ActorDialogDelay(sld, pchar, "", 0.5);
		break;
		
		case "rosetti_2":
			PlaySound("interface\abordage_wining.wav");
			dialog.text = "¡Sí, sí, capitán! ¡Prepárense muchachos, sigan al capitán! ¡Hut, uno-dos-tres!";
			link.l1 = "";
			link.l1.go = "rosetti_3";
		break;
		
		case "rosetti_3":
			DialogExit();
			PlaySound("interface\abordage_wining.wav");
			bDisableCharacterMenu = false;//лоченые интерфейсы
			ChangeShowIntarface();
			for (i=0; i<=12; i++)
			{
				sld = CharacterFromID("DefendSP_soldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// прерывание на джунгли перед выходом из города
			pchar.quest.DefendSP_jungle1.win_condition.l1 = "location";
			pchar.quest.DefendSP_jungle1.win_condition.l1.location = "Martinique_jungle_01";
			pchar.quest.DefendSP_jungle1.function = "DefendSP_SpainPatrol";
		break;
		
		case "spain_patrol":
			dialog.text = "¡Mierda, refuerzos franceses! ¡Formen filas! ¡Lorenzo, ve al campamento y da la alarma! ¡Muéranse, cabrones!";
			link.l1 = "...";
			link.l1.go = "spain_patrol_1";
		break;
		
		case "spain_patrol_1":
			DialogExit();
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);//разрешить драться
			for (i=1; i<=4; i++)
			{
				sld = CharacterFromID("DefendSP_spapatrol_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
				LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
				LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, true);
				LAi_group_SetCheck("EnemyFight", "DefendSP_SpaPatrolDie");
				AddDialogExitQuest("MainHeroFightModeOn");
			}
			sld = CharacterFromID("DefendSP_spapatrol_5");
			LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "DefendSP_GateAlarm", -1);
		break;

	// страж истины
		case "spanish":
			dialog.text = "¿Entiendes que no estoy autorizado para divulgar tal información?";
			link.l1 = "¿Entiendes que es solo gracias a mi oportuna intervención que Saint-Pierre no fue arrasada por los españoles? ¡Mi hermano ha desaparecido, abandonando la Orden! Debe haberlo hecho por una razón. ¡Yo, como representante de Sir Philippe de Poincy, estoy autorizado para investigar!";
			link.l1.go = "spanish_1";
		break;
		
		case "spanish_1":
			dialog.text = "Está bien, está bien, Monsieur de Maure. Responderé a tus preguntas. Primero cálmate. Ahora pregunta lo que quieras.";
			link.l1 = "¿Qué sucedió antes de que Michel fuera encerrado bajo custodia?";
			link.l1.go = "spanish_2";
		break;
		
		case "spanish_2":
			dialog.text = "Michel de Monper estaba negociando con algunos barones piratas para organizar un cambio de régimen en Tortuga.";
			link.l1 = "Eso ya lo sé. ¿Qué más?";
			link.l1.go = "spanish_3";
		break;
		
		case "spanish_3":
			dialog.text = "También estaba planeando una operación diferente contra los españoles. Para ser específico, la captura de un barco español con un valioso cargamento a bordo. Michel debía atraer al objetivo bajo los cañones de la fragata ligera 'Gryffondor'. No vimos rastro de él durante bastante tiempo mientras planeaba esto. Pero el plan salió mal. El transporte español no llegó y a Michel lo encontraron unos pescadores locales arrastrado por las olas en las costas de la Bahía de Le Marin, medio muerto. Parece que la operación fue un fracaso. La guerra es guerra, y las cosas salen mal. Fue un milagro que Michel sobreviviera en absoluto, pero el Caballero de Poincy se enfureció. Acusó a Michel de malversación de los fondos de la Orden y lo mandó encarcelar. Por supuesto, no creímos ni una palabra de esas acusaciones. Michel es un hombre honesto, un verdadero caballero de la Orden. Sólo Dios sabe qué enfureció al Gobernador General. Quizás, el Caballero de Poincy te lo diga él mismo.";
			link.l1 = "Posiblemente. ¿Eso es todo lo que sabes?";
			link.l1.go = "spanish_4";
		break;
		
		case "spanish_4":
			dialog.text = "Desafortunadamente, no hay nada más que decir. Los detalles de las operaciones de tu hermano solo eran conocidos por él mismo y el Caballero de Poincy. Somos caballeros de la Orden de San Juan de Malta. Cumplimos nuestras órdenes.";
			link.l1 = "Si el Caballero confía tanto en Michel, debe haber tenido éxito llevando a cabo sus planes secretos antes. ¿Conoces alguna acción exitosa que Michel haya logrado?";
			link.l1.go = "spanish_5";
		break;
		
		case "spanish_5":
			dialog.text = "Sin duda alguna. Este reciente fracaso de Michel de Monper fue también su primer fracaso, por lo que nos sorprendió la reacción del Chevalier. No hace mucho, el 'Gryffindor' capturó un galeón español de tesoro cargado de plata gracias a la cuidadosa planificación de Michel. Eso por sí solo debería haber compensado docenas de fracasos en el futuro. Y sin embargo, tu hermano fue arrestado.";
			link.l1 = "Ya veo. ¿Tienes alguna idea de por qué Michel huyó de Saint-Pierre?";
			link.l1.go = "spanish_6";
		break;
		
		case "spanish_6":
			dialog.text = "Sospecho que un conflicto interpersonal entre Michel y de Poincy fue la razón por la que fue arrestado. Obviamente, tu hermano teme que el Caballero continúe persiguiéndolo incluso después de su liberación, así que tomó medidas de precaución. ¿Y sabes qué, Monsieur de Maure? ¡Nadie aquí lo culpa por su decisión!\nEl hombre había estado trabajando valientemente por el bien de la Orden y, sin embargo, lo arrojaron a una celda fétida por su primer fracaso, ¡mientras estaba gravemente herido! ¡Un fracaso que ni siquiera fue tan grave, nadie murió y ningún barco se hundió!\nPor cierto, esta conversación es estrictamente confidencial y no repetiré lo que acabo de decir ni siquiera bajo juramento, ¿estamos claros en eso, Monsieur de Maure?";
			link.l1 = "Sí, señor. Ya he olvidado que tuvimos esta conversación. Dígame, ¿podría ser que el ataque español a Saint-Pierre fue provocado por el asalto de la Orden a los barcos españoles? ¿Quizás ese mismo galeón español con plata que mencionaste? Los castellanos fueron extremadamente celosos al buscar su base...";
			link.l1.go = "spanish_7";
		break;
		
		case "spanish_7":
			dialog.text = "Dudo de ello. Muy pocas personas saben sobre la presencia de la Orden en el Caribe y todas nuestras incursiones contra los españoles fueron cuidadosamente planeadas. Pregunta al oficial español que tomamos prisionero, está enfriando su ardiente temperamento castellano en nuestras mazmorras ahora mismo. Ya lo hemos interrogado. El ataque a Saint-Pierre fue un asalto ordinario, organizado por un gran barón español llamado Ramón de Mendoza y Riba con el propósito de su propio beneficio y para intimidar a las colonias francesas. También quería ganarse el favor del Escorial.";
			link.l1 = "Hablaré con este español. ¿Dónde puedo encontrarlo?";
			link.l1.go = "spanish_8";
		break;
		
		case "spanish_8":
			dialog.text = "Abajo, en la misma celda donde estaba detenido tu hermano.";
			link.l1 = "Conozco el camino. Regresaré después de interrogar al español. Puede que tenga algunas preguntas adicionales.";
			link.l1.go = "spanish_9";
		break;
		
		case "spanish_9":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "2");
			pchar.questTemp.Guardoftruth = "prisoner";
			sld = characterFromId("spa_baseprisoner");
			LAi_CharacterEnableDialog(sld);
			chrDisableReloadToLocation = true;//закрыть локацию
		break;
		
		case "spanish_10":
			dialog.text = "¡Vaya, esto sí que es algo! ¿Entiendes que no puedo liberar a ese prisionero, verdad? ¡Ese villano ayudó a liderar el ataque a Saint-Pierre!";
			link.l1 = "Oficial, este es un testigo importante. El ataque a Saint-Pierre no fue una simple incursión en busca de botín. Don Ramón Mendosa estaba buscando algo más. Necesitamos obtener un motivo definitivo. ¿Entonces me liberará a este español o tendré que exigir permiso de de Poincy?";
			link.l1.go = "spanish_11";
		break;
		
		case "spanish_11":
			dialog.text = "Por Dios Todopoderoso... Muy bien, llévenselo. De todas formas, estaba a punto de colgar a este bastardo en la plaza de San Pedro como al pirata común que es... Ahora es tu problema. ¡Asegúrate de que no escape de la justicia!";
			link.l1 = "Sin duda. Responderé por este español ante de Poincy. Haced que este cautivo sea encadenado y llevado a mi chalupa en el muelle de la ciudad.";
			link.l1.go = "spanish_12";
		break;
		
		case "spanish_12":
			dialog.text = "Muy bien, capitán.";
			link.l1 = "Una cosa más, oficial. ¿Te suena el nombre de Miguel Dichoso?";
			link.l1.go = "spanish_13";
		break;
		
		case "spanish_13":
			dialog.text = "No. Nunca lo he oído antes. ¿Por qué preguntas?";
			link.l1 = "¿Estás seguro? Entonces, ¿no has conocido a nadie con ese nombre, ni aquí en tu acantonamiento, ni en el palacio del gobernador, ni en ningún lugar de Saint-Pierre?";
			link.l1.go = "spanish_14";
		break;
		
		case "spanish_14":
			dialog.text = "No, no lo he hecho. No pensamos muy bien de los españoles de donde soy.";
			link.l1 = "Está bien. De todas formas, eso era de esperarse. Hubiera sido demasiado fácil... ¡Gracias, oficial! Has sido de gran ayuda.";
			link.l1.go = "spanish_15";
		break;
		
		case "spanish_15":
			dialog.text = "Bienvenido... ¿Qué piensa, Monsieur de Maure, dónde está su hermano ahora?";
			link.l1 = "Me gustaría saber la respuesta a esa pregunta yo mismo. Y lo averiguaré... tarde o temprano. ¡Au revoir!";
			link.l1.go = "spanish_16";
		break;
		
		case "spanish_16":
			DialogExit();
			NextDiag.CurrentNode = "Maltie_officer";
			AddQuestRecord("Guardoftruth", "3");
			pchar.questTemp.Guardoftruth = "toship";
			sld = characterFromId("spa_baseprisoner");
			sld.dialog.currentnode = "spa_prisoner_28";
			LAi_CharacterEnableDialog(sld);
		break;
		
	// монах-посланник от Винсенто
		case "monk_vinsento":
			dialog.text = TimeGreeting()+". ¿Eres el capitán "+GetFullName(pchar)+"?";
			link.l1 = "Sí, soy yo. ¿Qué puedo hacer por usted?";
			link.l1.go = "monk_vinsento_1";
		break;
		
		case "monk_vinsento_1":
			dialog.text = "Saludos, capitán. He sido enviado a usted por el Padre Vincento. Tengo algo para usted...";
			link.l1 = "¿Padre Vincento? Ya no trabajo para Su Excelencia. No después de que envió a Alonso de Maldonado, el hombre jurado de Diego de Montoya, a matarme. Puedes pasarle este mensaje al Reverendo Padre: fracasó.";
			link.l1.go = "monk_vinsento_2";
		break;
		
		case "monk_vinsento_2":
			dialog.text = "Espera, capitán. El padre Vincento esperaba tal reacción de usted y me advirtió de esto. Le aseguro que Su Gracia no le desea ningún mal. Por favor, lea esta carta. Es muy, muy importante.";
			link.l1 = "¿El Padre Vincento no me desea ningún mal? Hm. ¿Quizás tampoco te contó nada sobre mí y Don de Maldonado? Veo por qué debería creerte.";
			link.l1.go = "monk_vinsento_3";
		break;
		
		case "monk_vinsento_3":
			dialog.text = "Toma esta carta, capitán. Léela y toma tu propia decisión. Solo sabe que el destino de toda la cristiandad está en tus manos. No tomes esto a la ligera. ¡Que Dios te bendiga y guíe tus pasos por el camino recto!";
			link.l1 = "Está bien, dame la carta.";
			link.l1.go = "monk_vinsento_4";
		break;
		
		case "monk_vinsento_4":
			GiveItem2Character(pchar, "specialletter"); 
			ChangeItemDescribe("specialletter", "itmdescr_specialletter_vinsento");
			sld = ItemsFromID("specialletter");
			sld.text = "Letter_Vincento_last";
			dialog.text = "Aquí tienes. Rezo para que tomes la decisión correcta. Pax vobiscum.";
			link.l1 = "...";
			link.l1.go = "monk_vinsento_5";
		break;
		
		case "monk_vinsento_5":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4_back", "none", "", "", "", 30.0);
			ReOpenQuestHeader("Sharlie"); // patch-8
			AddQuestRecord("Sharlie", "40");
			CloseQuestHeader("Ksochitam");
		break;
		
	// падре Адриан
		case "adrian":
			dialog.text = "Saludos, hijo mío. Que el Señor esté contigo.";
			link.l1 = "Y también contigo, Padre Adrián. Su Gracia dijo que puedes proporcionarme amuletos y medicinas.";
			link.l1.go = "adrian_1";
		break;
		
		case "adrian_1":
			dialog.text = "Sí, por supuesto. He recibido un envío especial desde Santiago sólo para ti. Aquí tienes amuletos benditos y pociones curativas. Y para rematar, una rara y única tintura de Ometochtli que te hará invencible en combate. Todo esto es para ti, hijo mío. Toma y ve que el Señor es bueno.";
			link.l1 = "¡Gracias!";
			link.l1.go = "adrian_2";
		break;
		
		case "adrian_2":
			for(i=2; i<=10; i++)
			{
				if (i == 4 || i == 5 || i == 8 || i == 9) continue;
				TakeNItems(pchar, "amulet_"+i, 2);
			}
			TakeNItems(pchar, "potion2", 20);
			TakeNItems(pchar, "potion4", 10);
			TakeNItems(pchar, "potion7", 3);
			TakeNItems(pchar, "berserker_potion", 3);
			dialog.text = "Si necesitas más hierbas curativas, puedo proporcionarte un frasco de cada una todos los días. Prepararé tantas como necesites.";
			link.l1 = "Tienes mi gratitud, Padre Adrián. Lo tendré en cuenta.";
			link.l1.go = "exit";
			link.l2 = "Genial. Necesito un poco ahora mismo.";
			link.l2.go = "potion";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "adrian_3":
			dialog.text = "Que Dios te bendiga y te guarde, hijo mío. ¿Qué deseas?";
			link.l1 = "Me gustaría comprar algunas pociones curativas.";
			link.l1.go = "potion";
			link.l2 = "Nada en este momento, me estoy preparando para un viaje. Solo pasé a saludar y ver cómo estás.";
			link.l2.go = "exit";
			NextDiag.TempNode = "adrian_3";
		break;
		
		case "potion":
			dialog.text = "Por supuesto, hijo mío. ¿Qué medicina necesitas?";
			if (!CheckAttribute(npchar, "potion1_date") || GetNpcQuestPastDayParam(npchar, "potion1_date") >= 1)
			{
				link.l1 = "Solo un simple remedio.";
				link.l1.go = "potion1";
			}
			if (!CheckAttribute(npchar, "potion2_date") || GetNpcQuestPastDayParam(npchar, "potion2_date") >= 1)
			{
				link.l2 = "Un elixir salutífero.";
				link.l2.go = "potion2";
			}
			if (!CheckAttribute(npchar, "potion3_date") || GetNpcQuestPastDayParam(npchar, "potion3_date") >= 1)
			{
				link.l3 = "Un antídoto.";
				link.l3.go = "potion3";
			}
			if (!CheckAttribute(npchar, "potion4_date") || GetNpcQuestPastDayParam(npchar, "potion4_date") >= 1)
			{
				link.l4 = "Una mezcla de hierbas.";
				link.l4.go = "potion4";
			}
			link.l5 = "Perdóname por molestarte, padre. He cambiado de opinión.";
			link.l5.go = "exit";
		break;
		
		case "potion1":
			npchar.quest.price = 90;
			npchar.quest.type = 1;
			dialog.text = "¿Una esencia curativa? Eso son 90 pesos, hijo mío. Por los materiales, claro.";
			if (sti(Pchar.money) >= 90)
			{
				link.l1 = "Gracias, padre.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Desafortunadamente, no tengo el dinero... Volveré más tarde.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion2":
			npchar.quest.price = 500;
			npchar.quest.type = 2;
			dialog.text = "¿Un elixir que da salud? 500 pesos, hijo mío.";
			if (sti(Pchar.money) >= 500)
			{
				link.l1 = "Gracias, padre.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Lamentablemente, no tengo el dinero... Volveré más tarde.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion3":
			npchar.quest.price = 200;
			npchar.quest.type = 3;
			dialog.text = "¿Un antídoto? 200 pesos, hijo mío.";
			if (sti(Pchar.money) >= 200)
			{
				link.l1 = "Gracias, padre.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Desafortunadamente, no tengo el dinero... Volveré más tarde.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion4":
			npchar.quest.price = 900;
			npchar.quest.type = 4;
			dialog.text = "¿Una mezcla de hierbas? 900 pesos, hijo mío.";
			if (sti(Pchar.money) >= 900)
			{
				link.l1 = "Gracias, padre.";
				link.l1.go = "potion_pay";
			}
			else
			{
				link.l1 = "Desafortunadamente, no tengo el dinero... Volveré más tarde.";
				link.l1.go = "exit";
			}
		break;
		
		case "potion_pay":
			AddMoneyToCharacter(pchar, -sti(npchar.quest.price));
			iTemp = sti(npchar.quest.type);
			GiveItem2Character(pchar, "potion"+iTemp);
			PlaySound("interface\important_item.wav");
			dialog.text = "'Porque yo restituiré la salud a ti, y te sanaré de tus heridas, dice el Señor.' Aquí está tu medicina. ¡Dominus vobiscum!";
			link.l1 = "Gracias, Padre Adrián.";
			link.l1.go = "exit";
			SaveCurrentNpcQuestDateParam(npchar, "potion"+iTemp+"_date");
			NextDiag.TempNode = "adrian_3";
		break;
		
	// посланец Дичозо
		case "Dichoso_agent":
			dialog.text = "¿Capitán "+GetFullName(pchar)+"?";
			link.l1 = "Sí, soy yo. ¿Qué quieres?";
			link.l1.go = "Dichoso_agent_1";
		break;
		
		case "Dichoso_agent_1":
			dialog.text = "Tengo un mensaje para usted de parte del Capitán Miguel Dichoso. Dice que lo conoce.";
			link.l1 = "Sí, he oído hablar de él. Nunca tuve el honor de conocerlo en persona.";
			link.l1.go = "Dichoso_agent_2";
		break;
		
		case "Dichoso_agent_2":
			dialog.text = "El Capitán Dichoso quisiera cambiar eso. Quiere reunirse contigo cara a cara. Tiene una oferta para ti relacionada con una expedición a las profundidades del Caribe español, a la perdida ciudad india de Tayasal. Me dijo que tu experiencia combinada con su conocimiento producirá resultados gratificantes.";
			link.l1 = "¿Esas fueron sus palabras exactas?";
			link.l1.go = "Dichoso_agent_3";
		break;
		
		case "Dichoso_agent_3":
			dialog.text = "Correcto. El Capitán Dichoso te estará esperando en San Cristóbal. Te esperará en la gran cripta del cementerio de Capsterville, para evitar ojos y oídos curiosos.";
			link.l1 = "Mm...";
			link.l1.go = "Dichoso_agent_4";
		break;
		
		case "Dichoso_agent_4":
			dialog.text = "Dichoso me advirtió que dudarías. Me dijo que te ofreciera garantías de que no sufrirás daño alguno durante las negociaciones sin importar tu decisión. También añade que lo que encontraste en cierta isla fue solo un pequeño aperitivo considerando lo que encontrarías en Tayasal.";
			link.l1 = "¿Es así... eso es muy intrigante. Pero, ¿por qué el Capitán Dichoso no me visitó él mismo? ¿Por qué envió a un tercero?";
			link.l1.go = "Dichoso_agent_5";
		break;
		
		case "Dichoso_agent_5":
			dialog.text = "Don Dichoso primero te buscó en Isla Tesoro, luego aquí, y ahora se ha ido a San Cristóbal con la esperanza de encontrarte allí. ¿Eres un oficial del mismo Philippe de Poincy, no es así? Se suponía que debía esperarte aquí en caso de que llegaras a Blueweld.";
			link.l1 = "Entonces todo está claro. Bueno, está bien. No perderé tiempo, debo ir a Capsterville.";
			link.l1.go = "Dichoso_agent_6";
		break;
		
		case "Dichoso_agent_6":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4_back", "none", "", "", "Tieyasal_PrepareDichosoTrap", -1);
		break;
		
	// агент Дичозо
		case "Dichoso_crypt_agent":
			dialog.text = "Bueno, finalmente nos encontramos, capitán "+GetFullName(pchar)+"...";
			if (CheckAttribute(pchar, "questTemp.Tieyasal.MigelKnow")) 
			{
				link.l1 = "¿Dónde está Miguel Dichoso? Y no intentes escabullirte de esto. Sé quién es realmente y creo que tú también lo sabes.";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "¿Supongo que este es Miguel Dichoso en persona justo frente a mí?";
				link.l1.go = "Dichoso_crypt_agent_1";
			}
		break;
		
		case "Dichoso_crypt_agent_1":
			dialog.text = "Supones correctamente, capitán. Hemos estado pisándonos los talones durante mucho tiempo, ¿no es así?";
			if (CheckAttribute(pchar, "questTemp.Ksochitam.SQCapBookRead")) // прочел журнал Санта-Квитерии
			{
				link.l1 = "Puedo decir que estás mintiendo solo con mirarte, camarada. No eres Dichoso. He leído las entradas del diario del capitán de la 'Santa Quiteria' y he preguntado sobre su apariencia. No te pareces a él. Ni siquiera tienes una cicatriz en la cara de una espada de caballería. ¡Vamos, incluso un mimo podría al menos haber intentado dibujarla!";
				link.l1.go = "Dichoso_crypt_agent_2";
			}
			else
			{
				link.l1 = "Exactamente. Según entiendo, ¿estamos aquí para hablar sobre la ciudad perdida de Tayasal?";
				link.l1.go = "Dichoso_crypt_agent_7";
			}
		break;
		
		case "Dichoso_crypt_agent_2":
			dialog.text = "¡Ja! No tiene sentido continuar con esta farsa entonces. Miguel me advirtió que eras un pícaro astuto...";
			link.l1 = "¿Dónde está Miguel Dichoso?";
			link.l1.go = "Dichoso_crypt_agent_3";
		break;
		
		case "Dichoso_crypt_agent_3":
			dialog.text = "Él no está aquí. Estoy autorizado a encontrarme contigo y hablar en su nombre.";
			link.l1 = "No hablaré con un peón. Estoy aquí por el rey. ¿Dónde está?!";
			link.l1.go = "Dichoso_crypt_agent_4";
		break;
		
		case "Dichoso_crypt_agent_4":
			dialog.text = "No siendo un compañero de conversación agradable, capitán. Has perdido la compostura.";
			link.l1 = "Basta de juegos, lo entiendo. Es otra emboscada. Ustedes muchachos necesitan inventar algunos trucos nuevos.";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
		case "Dichoso_crypt_agent_5":
			dialog.text = "¡Jaja, correcto de nuevo, camarada! Mis hombres te esperan justo detrás de la puerta que lleva a las catacumbas. Además, tengo mosqueteros escondidos detrás de cada una de las lápidas, listos para disparar. No hay escapatoria. Así que, por más repetitivo que sea este truco, ¡has caído de lleno en él! ¡Tu deseo de ver Tayasal ha superado tu sentido común!";
			link.l1 = "Has elegido un gran lugar para una pelea, escoria. No tendré que ir lejos para enterrarte a ti y a tus amigos bandidos.";
			link.l1.go = "Dichoso_crypt_agent_6";
		break;
		
		case "Dichoso_crypt_agent_6":
			dialog.text = "¡Ja ja! ¡Me gusta tu ingenio! ¡Igual que el de Miguel! Di lo que quieras, ambos están cortados por la misma tijera... Haré justo lo que él ordenó: te enviaré al infierno lo más rápido y sin dolor posible. ¡A las armas, muchachos!";
			link.l1 = "Hombres mejores que tú lo han intentado. ¡Dale mis saludos al Diablo, canalla!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Tieyasal_StartCryptBattle");
		break;
		
		case "Dichoso_crypt_agent_7":
			dialog.text = "¿De verdad quieres llegar a la ciudad? Lo entiendo, capitán, pero no creo que sea una buena idea.";
			link.l1 = "Entonces, ¿de qué venimos a hablar?";
			link.l1.go = "Dichoso_crypt_agent_8";
		break;
		
		case "Dichoso_crypt_agent_8":
			dialog.text = "No estoy buscando entablar una larga y romántica conversación contigo. Estás aquí y eso para mí es suficiente.";
			link.l1 = "Basta de juegos, lo entiendo. Es otra emboscada. Ustedes muchachos necesitan inventar algunos trucos nuevos.";
			link.l1.go = "Dichoso_crypt_agent_5";
		break;
		
	// командир абордажников
		case "newcastle_officer":
			dialog.text = "¡Esperando tus órdenes, capitán!";
			link.l1 = "Nos dirigimos a través de la selva hacia el cementerio de Capsterville. Una vez que lleguemos allí, no entres al cementerio en sí. Toma posiciones de disparo justo fuera de la puerta y escucha atentamente cuando entre. Si escuchas lucha, entra de inmediato.";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_0":
			dialog.text = "¡Esperando tus órdenes, capitán!";
			link.l1 = "Nos dirigimos a través de la jungla hacia el cementerio de Capsterville. Una vez allí, no entres al cementerio en sí. Tomando posiciones de disparo a lo largo del sendero, rodea el cementerio y escucha atentamente cuando yo entre. Todo este plan apesta a emboscada. Tan pronto como veas al enemigo, ataca de inmediato.";
			link.l1.go = "newcastle_officer_1";
		break;
		
		case "newcastle_officer_1":
			dialog.text = "¡Sí, sí, capitán!";
			link.l1 = "Está bien. ¡Adelante!";
			link.l1.go = "newcastle_officer_2";
		break;
		
		case "newcastle_officer_2":
			DialogExit();
			chrDisableReloadToLocation = false;
			locations[FindLocation("Charles_exittown")].DisableEncounters = true; //энкаутеры закрыть
			locations[FindLocation("Charles_CaveEntrance")].DisableEncounters = true; //энкаутеры закрыть
			for(i=2; i<=4; i++)
			{
				locations[FindLocation("Charles_Jungle_0"+i)].DisableEncounters = true; //энкаутеры закрыть
			}
			LocatorReloadEnterDisable("Shore42", "boat", true);
			for(i=1; i<=iTotalTemp; i++)
			{
				sld = characterFromID("Tieyasal_Oursoldier_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			// на локацию перед кладбищем
			pchar.quest.Tieyasal_newcastle.win_condition.l1 = "location";
			pchar.quest.Tieyasal_newcastle.win_condition.l1.location = "Charles_exittown";
			pchar.quest.Tieyasal_newcastle.function = "Tieyasal_NewcastleGoJungle";
			// на крипту
			pchar.quest.Tieyasal_graveyard.win_condition.l1 = "location";
			pchar.quest.Tieyasal_graveyard.win_condition.l1.location = "Charles_CryptBig2";
			pchar.quest.Tieyasal_graveyard.function = "Tieyasal_InGraveyardCrypt";
		break;

case "Europe":
			PlaySound("Voice\Spanish\military01.wav");
			dialog.text = "¡Capitán Hobart! Según la información de nuestro espía, los rebeldes se esconden en esta hacienda. Hay cinco dragones a su disposición. ¡Registre el edificio y capture a cualquiera que esté adentro! No trate a esta escoria con guantes de seda. ¡Está actuando en nombre del Rey!";
			link.l1 = "¡Sí, señor!";
			link.l1.go = "Europe_1";
		break;
		
		case "Europe_1":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "Europe_SharlieFinal_1", 5);
		break;
		
		//Индеец по квесту "Знакомство с индейцами"
		case "ZsI_ListKakao":
			dialog.text = "¡Tsk! ¡Hijo del Mar!";
			link.l1 = "Eh... ¿qué? ¿Te diriges a mí?";
			link.l1.go = "ZsI_ListKakao_1";
			sld = characterFromId("Tichingitu");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "ZsI_ListKakao_1":
			dialog.text = "Correcto. Soy Hoja de Cacao. Tengo asuntos contigo, Hijo del Mar.";
			link.l1 = "No sé cómo luce el cacao, ni por qué te llamas así. Pero bien, dime qué necesitas, rápido.";
			link.l1.go = "ZsI_ListKakao_2";
		break;
		
		case "ZsI_ListKakao_2":
			dialog.text = "¡Tsk! Ve a la ciudad. Compra dos pistolas y diez pólvora y balas. Dámelos. Hay una recompensa. El Hijo del Mar estará complacido.";
			link.l1 = "¿Dos pistolas y veinte disparos? ¿Eso es todo? ¿Por qué no los compras tú mismo entonces?";
			link.l1.go = "ZsI_ListKakao_3";
		break;
		
		case "ZsI_ListKakao_3":
			dialog.text = "¿No lo entiendes, cara pálida? ¡¿Quién me vendería un arma de fuego?!";
			if (CheckAttribute(pchar, "questTemp.ZsI_Cannibals"))		//Sinistra Только если проходил квест "Каннибалы"
			{
				link.l1 = "Sabes, me he encontrado con tu tipo en Martinica antes... Caníbales. Secuestraron a una chica y dos hombres. Asaron y se comieron a uno de los hombres. Si alguno de ellos hubiera tenido un arma, no estaríamos teniendo esta conversación.";
				link.l1.go = "ZsI_ListKakao_3_1";
			}
			else
			{
				link.l1 = "¿Y por qué necesitas un arma de fuego, Hoja de Cacao? ¿Quieres matar a alguien?";
				link.l1.go = "ZsI_ListKakao_3_2";
			}
		break;
		
		case "ZsI_ListKakao_3_1":
			dialog.text = "¡Goo-oo! Hoja de Cacao no es un bandido, mi lucha es solo para los guerreros de tu tribu. Los rostros pálidos vienen a nuestra tierra, nos hacen esclavos. Hoja de Cacao lucha él mismo. Toma un esclavo. Ni bueno, ni malo. Así es como va. Indio, blanco, no hay diferencia. Las armas de fuego hacen la diferencia.";
			link.l1 = "¿Y para qué necesitas un arma de fuego, Hoja de Cacao? ¿Quieres matar a alguien?";
			link.l1.go = "ZsI_ListKakao_3_2";
		break;
		
		case "ZsI_ListKakao_3_2":
			dialog.text = "Pelear. Pero en igualdad de condiciones. Los rostros pálidos tienen armas de fuego, los indios no. Eso es injusto. Y tener un arma de fuego para un indio es una protección contra el trato injusto, la humillación o el insulto por parte de los rostros pálidos.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_4";
		break;
		
		case "ZsI_ListKakao_4":
			StartInstantDialog("Tichingitu", "ZsI_ListKakao_5", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_ListKakao_5":
			dialog.text = "Correcto, Capitán. Los rostros pálidos nos miran por encima del hombro.";
			link.l1 = "Lo he notado. En Europa, predican sobre enseñar a los indios la verdadera fe y cómo todos trabajamos juntos pacíficamente en las plantaciones...";
			link.l1.go = "ZsI_ListKakao_7";
		break;
		
		case "ZsI_ListKakao_7":
			dialog.text = "Tichingitu tal vez no entienda al capitán, pero entiende la hoja de cacao. Busca venganza.";
			link.l1 = "Parece que sí... ¿No quieres también vengarte de nuestros recientes captores?";
			link.l1.go = "ZsI_ListKakao_8";
		break;
		
		case "ZsI_ListKakao_8":
			dialog.text = "Quizás. Pero Tichingitu no recurrirá a eso. Tichingitu está contigo ahora. Y Tichingitu usa su propia cabeza. Habrá demasiada matanza. Sangre blanca. Sangre india. Demasiado sufrimiento. Eso no está bien.";
			link.l1 = "Sí, ya está mal, y ayudar a Hoja de Cacao a conseguir armas solo lo empeorará... Pero tiene razón. Y todavía tengo una tripulación que pronto debo pagar.";
			link.l1.go = "ZsI_ListKakao_9";
		break;
		
		case "ZsI_ListKakao_9":
			dialog.text = "Usa tu propia cabeza, Capitán.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_10";
		break;
		
		case "ZsI_ListKakao_10":
			StartInstantDialog("ListKakao", "ZsI_ListKakao_11", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_ListKakao_11":
			dialog.text = "El Hijo del Mar habla mucho. Parece una comadre con bigote.";
			link.l1 = "¿Quién? Explícame esto, Hoja de Cacao. Yo también soy un cara pálida y me estás pidiendo armas para luchar contra caras pálidas. ¿No es eso contradictorio? ¿Por qué acercarte a mí?";
			link.l1.go = "ZsI_ListKakao_12";
		break;
		
		case "ZsI_ListKakao_12":
			dialog.text = "Escuché tu conversación con ese indio vestido de manera extraña. No eres como los otros rostros pálidos. Entiendes a Tichingitu. Y entiendes la Hoja de Cacao, estoy seguro.";
			link.l1 = "Oh... ¿Qué ofrecerás por las armas, Hoja de Cacao?";
			link.l1.go = "ZsI_ListKakao_13";
		break;
		
		case "ZsI_ListKakao_13":
			dialog.text = "Las lágrimas de los dioses. Las llamáis perlas. Muchas perlas.";
			link.l1 = "He tomado mi decisión, Hoja de Cacao. Espera aquí, voy al mercader de armas. Compraré lo que necesito y regresaré.";
			link.l1.go = "ZsI_ListKakao_Soglasen_5";
			if (sti(pchar.items.pistol1) >= 2 && sti(pchar.items.GunPowder) >= 20 && sti(pchar.items.bullet) >= 20)
			{
				link.l2 = "He tomado mi decisión, Hoja de Cacao. Resulta que ya tengo lo que necesitas. Aquí tienes.";
				link.l2.go = "ZsI_ListKakao_Soglasen_2";
			}
			link.l3 = "He tomado mi decisión, Hoja de Cacao. No quiero atraer problemas innecesarios. No obtendrás armas de fuego de mí. Sigue tu camino.";
			link.l3.go = "ZsI_ListKakao_Otkaz";
			npchar.LifeDay = 1;
			SaveCurrentNpcQuestDateParam(npchar, "LifeTimeCreate");
		break;
		
		case "ZsI_ListKakao_Otkaz":
			dialog.text = "¡Tsk!";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_Otkaz_2";
		break;
		
		case "ZsI_ListKakao_Otkaz_2":
			DialogExit();
			
			ChangeIndianRelation(-3.0);
			ChangeCharacterComplexReputation(pchar, "authority", -1);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "ZsI_Mir", -1);
			LAi_SetImmortal(npchar, false);
			LAi_SetHP(npchar, 1.0, 1.0);
			npchar.lifeday = 0;
			PChar.quest.ZsI_Draka.win_condition.l1 = "NPC_Death";
			PChar.quest.ZsI_Draka.win_condition.l1.character = "ListKakao";
			PChar.quest.ZsI_Draka.win_condition = "ZsI_Draka";
			PChar.quest.ZsI_Mir.win_condition.l1 = "ExitFromLocation";
			PChar.quest.ZsI_Mir.win_condition.l1.location = PChar.location;
			PChar.quest.ZsI_Mir.win_condition = "ZsI_Mir";
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			sld = characterFromId("Tichingitu");
			LAi_SetOfficerType(sld);
			sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
			sld.Dialog.CurrentNode = "Tichingitu_officer";
			LaunchTutorial("Fighter", 1);
		break;
		
		case "ZsI_ListKakao_Soglasen_2":
			dialog.text = "¡Oh-oh! ¿Tiene el Hijo del Mar un mosquete? ¡Paga un alto precio por un mosquete!";
			link.l1 = "No, pero ¿servirá un cañón de mi barco? Márchate ahora, Hoja de Cacao, antes de que nos vean y arresten.";
			link.l1.go = "ZsI_ListKakao_Soglasen_3";
			AddCharacterExpToSkill(pchar, "Commerce", 50);
			ChangeIndianRelation(3.0);
			AddItems(pchar, "jewelry53", 180);
			Log_Info("Has recibido 180 pequeñas perlas");
			PlaySound("Interface\important_item.wav");
			DeleteAttribute(pchar, "questTemp.ZsI_PokupaemPistolety");
			if (sti(pchar.items.pistol1) >= 2 && sti(pchar.items.GunPowder) >= 20 && sti(pchar.items.bullet) >= 20)
			{
				RemoveCharacterEquip(PChar, GUN_ITEM_TYPE);
				RemoveItems(PChar, "pistol1", 2);
				RemoveItems(PChar, "GunPowder", 20);
				RemoveItems(PChar, "bullet", 20);
			}
		break;
		
		case "ZsI_ListKakao_Soglasen_3":
			dialog.text = "¡Buen trato! Hijo del Mar, si vas a la selva, lleva un arma de fuego. Si encuentras a un indio, será un buen trueque.";
			link.l1 = "Lo recordaré. Adiós, Hoja de Cacao.";
			link.l1.go = "ZsI_ListKakao_Soglasen_4";
		break;
		
		case "ZsI_ListKakao_Soglasen_4":
			DialogExit();
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			
			Return_TichingituOfficer();
			LaunchTutorial("Fighter", 1);
		break;
		
		case "ZsI_ListKakao_Soglasen_5":
			dialog.text = "La hoja de cacao esperará.";
			link.l1 = "";
			link.l1.go = "ZsI_ListKakao_Soglasen_6";
		break;
		
		case "ZsI_ListKakao_Soglasen_6":
			DoQuestReloadToLocation("BasTer_town", "reload", "gate_back", "ZsI_TPvGorod");
		break;

		case "ZsI_officer":
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				dialog.text = "¡Bah, parece que tenemos una reunión de nativos aquí!\n¿Quieres volver a la prisión, perro?\n¿Qué haces aquí, Monsieur?";
			}
			else
			{
				dialog.text = "¡Alto! ¿Qué hace usted aquí, Monsieur?";
			}
			link.l1 = "";
			link.l1.go = "ZsI_officer_2";
			sld = CharacterFromID("ListKakao");
			LAi_CharacterEnableDialog(sld);
			EndBattleLandInterface();
		break;
		
		case "ZsI_officer_2":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ListKakao"));
			dialog.text = "Eh, escoria, ¿estabas esperando a este ciudadano ejemplar?";
			link.l1 = "";
			link.l1.go = "ZsI_officer_3";
		break;
		
		case "ZsI_officer_3":
			DialogExit();
			StartInstantDialog("ListKakao", "ZsI_officer_4", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_officer_4":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ZsI_Patrul_off"));
			dialog.text = "Todos los rostros pálidos me parecen iguales. Pero nunca he visto a este. Tú, guerrero, haz lo que debas conmigo. Esto se está volviendo tedioso. Hoja de Cacao está listo para enfrentar a los espíritus del bosque.";
			link.l1 = "";
			link.l1.go = "ZsI_officer_5";
		break;
		
		case "ZsI_officer_5":
			DialogExit();
			StartInstantDialog("ZsI_Patrul_off", "ZsI_officer_6", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "ZsI_officer_6":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, CharacterFromID("ListKakao"));
			dialog.text = "El infierno te espera, no los espíritus del bosque.";
			link.l1 = "";
			link.l1.go = "ZsI_officer_7";
		break;
		
		case "ZsI_officer_7":
			LAi_SetActorType(npchar);
			LAi_ActorTurnToCharacter(npchar, pchar);
			dialog.text = "Capitán, está despedido. Manténgase fuera de mi camino. Proteger la ciudad es un asunto serio.";
			link.l1 = "Ya veo... Pero, ¿qué pasa con este indio?";
			link.l1.go = "ZsI_officer_8";
		break;
		
		case "ZsI_officer_8":
			dialog.text = "¿Cuál es su interés en los indios, Monsieur? Aunque... bueno, sí, acaba de llegar de Europa.\n¿Cómo está París? ¿Todavía aplastan ratas de ciudad, o ya las han invitado a la comunión? Verá, nosotros tenemos nativos en lugar de ratas. Hacen negocios con bucaneros, atacan a los leñadores, se comen a la gente, maldita sea.\nHace tres días, algún individuo brillante ya les había vendido un mosquete a estos. ¿Y adivine qué? Esos bastardos mataron a todos los soldados de la patrulla, liderada, por cierto, por mi amigo y camarada. Encontramos al traidor de la colonia y lo colgamos para que se secara al sol, para dar un ejemplo. ¡Dar armas de fuego a los indios! ¡Eso es traición! ¡Traición contra Francia! Hemos estado rastreando a ese mono de color por un tiempo ya que se ha convertido en una cara familiar en varios eventos.\nBueno, ahora encontrará su fin rápido y merecido. Puede seguir adelante, Capitán. No se involucre en asuntos que no le conciernen. No es parte de esta guerra... Aún... ¿O sí lo es?";
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l1 = "(De confianza) Verá, oficial... Soy el Capitán Charles de Maure, un invitado de Fadey Muscovita. Tenemos cierto interés en este indio... así que no interfiramos en los deberes del otro. ¿De acuerdo, Teniente?";
				link.l1.go = "ZsI_officer_Mir";
			}
			link.l2 = "Actitudes hacia los recién llegados, actitudes hacia los nativos... Colonos, nativos... No entiendo mucho de todo esto aún, pero en este momento, teniente, la comparación no te favorece... ¡A la batalla!";
			link.l2.go = "ZsI_officer_Draka";
			link.l3 = "Tiene razón, teniente, no lo soy. Adiós.";
			link.l3.go = "ZsI_officerKIll";
			StartBattleLandInterface();
		break;
		
		case "ZsI_officer_Mir":
			dialog.text = "¡Ejem! Entendido, Capitán. Por favor, transmita mis saludos al señor Fadey. ¡Escuadrón, reanuden el patrullaje!";
			link.l1 = "";
			link.l1.go = "ZsI_officer_Mir_2";
		break;
		
		case "ZsI_officer_Mir_2":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			sld.lifeday = 0;
			LAi_SetImmortal(sld, true);
			LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetActorType(sld);
				sld.lifeday = 0;
				LAi_SetImmortal(sld, true);
				LAi_ActorGoToLocation(sld, "reload", "reload4", "none", "", "", "", -1);
			}
			sld = CharacterFromID("ListKakao");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "ZsI_MirFinal";
			LAi_SetActorType(sld);
			LAi_SetActorType(pchar);
			SetActorDialogAny2Pchar(sld.id, "", 0.0, 0.0);
			LAi_ActorFollow(pchar, sld, "ActorDialog_Any2Pchar", 2.0);
			LAi_ActorFollow(sld, pchar, "ActorDialog_Any2Pchar", 2.0);
			
			AddCharacterExpToSkill(pchar, "Leadership", 30);
			AddCharacterExpToSkill(pchar, "Fortune", 30);
		break;
		
		case "ZsI_MirFinal":
			dialog.text = "¡Uh-oh!";
			link.l1 = "Sí, bueno, incluso yo estoy sorprendido de que funcionara. Aquí están tus mercancías, Hoja de Cacao.";
			link.l1.go = "ZsI_MirFinal_2";
		break;
		
		case "ZsI_MirFinal_2":
			dialog.text = "El Hijo del Mar habla bien. ¡Salvar a un indio es un gran asunto! ¡Gran recompensa!";
			link.l1 = "Vaya, eso es un buen botín... Y una piedra con un agujero, y una especie de amuleto.";
			link.l1.go = "ZsI_MirFinal_3";
			AddItems(pchar, "jewelry53", 180);
			AddItems(pchar, "cannabis1", 3);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "talisman11");
			Log_Info("Has recibido 180 pequeñas perlas");
			Log_info("Has recibido el amuleto 'Cascavella'");
			Log_info("Has recibido la 'Piedra víbora' de Ward");
			Log_info("Has recibido 3 hierbas Datura");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_MirFinal_3":
			dialog.text = "¿Tiene el Hijo del Mar un mosquete? ¡Paga un alto precio por un mosquete!";
			link.l1 = "No, ¿pero servirá un cañón de mi barco? Vete ahora, Hoja de Cacao, antes de que nos vean y arresten.";
			link.l1.go = "ZsI_MirFinal_4";
		break;
		
		case "ZsI_MirFinal_4":
			dialog.text = "¡Buen trato! Hijo del Mar, si te adentras en la selva, lleva un arma de fuego. Encuentra a un indio, habrá trato.";
			link.l1 = "Recordaré eso. Adiós, Hoja de Cacao.";
			link.l1.go = "ZsI_MirFinal_5";
		break;
		
		case "ZsI_MirFinal_5":
			DialogExit();
			
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			npchar.lifeday = 0;
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			LAi_SetPlayerType(pchar);
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "ZsI_officer_Draka":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			LAi_LocationFightDisable(&Locations[FindLocation("BasTer_ExitTown")], false);
			LAi_SetFightMode(pchar, true);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			ChangeCharacterComplexReputation(pchar, "authority", -2);	
			ChangeIndianRelation(5.0);
			ChangeCharacterNationReputation(pchar, FRANCE, -10);
			sld = CharacterFromID("ListKakao");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetImmortal(sld, false);
			for (i=1; i<=2; i++)
			{
				sld = CharacterFromID("ZsI_Patrul_"+i);
				LAi_SetWarriorType(sld);
				LAi_group_MoveCharacter(sld, "EnemyFight");
			}
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetWarriorType(sld);
			LAi_group_MoveCharacter(sld, "EnemyFight");
			
			LAi_group_SetRelation("EnemyFight", LAI_GROUP_PLAYER, LAI_GROUP_ENEMY);
			LAi_group_FightGroups("EnemyFight", LAI_GROUP_PLAYER, false);
			LAi_group_SetCheck("EnemyFight", "ZsI_officer_Draka_3");
		break;
		
		case "ZsI_Final":
			ChangeIndianRelation(5.0);
			dialog.text = "¡Uh-oh! Mala decisión, Hijo del Mar. ¿Por qué harías eso?";
			link.l1 = "Uf... Hace cinco minutos parecía correcto... Ahora ya no estoy tan seguro.... Después de todo, maté a los míos. ¿Qué se supone que debo hacer ahora? ¿Y si lo descubren? ¡Mierda! ¡Mierda!";
			link.l1.go = "ZsI_Final_2";
		break;
		
		case "ZsI_Final_2":
			dialog.text = "Ahora habrá un asalto. Los soldados matan a todos. Dos patrullas no perdonar. Hoja de Cacao huir. Y tú, Hijo del Mar... ¿por qué? Hoja de Cacao morir de todos modos. Los espíritus lo quieren así.";
			link.l1 = "Oh... ¿Nuestro trato sigue en pie?";
			link.l1.go = "ZsI_Final_3";
		break;
		
		case "ZsI_Final_3":
			dialog.text = "Mala decisión, Hijo del Mar. Pero gracias. Gran recompensa.";
			link.l1 = "No tan grande, considerando todo...";
			link.l1.go = "ZsI_Final_4";
			AddItems(pchar, "jewelry53", 180);
			AddItems(pchar, "cannabis1", 3);
			GiveItem2Character(pchar, "indian_10");
			GiveItem2Character(pchar, "talisman11");
			Log_Info("Has recibido 180 pequeñas perlas");
			Log_info("Has recibido el amuleto 'Cascavella'");
			Log_info("Has recibido la 'Piedra víbora' de Ward");
			Log_info("Has recibido 3 hierbas Datura");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "ZsI_Final_4":
			dialog.text = "Hijo del Mar, si sobrevives y luego vas a la selva, lleva un arma de fuego. Encuentra a un indio, haz un trato.";
			link.l1 = "Tendré eso en cuenta para el futuro. Adiós, Hoja de Cacao.";
			link.l1.go = "ZsI_Final_5";
		break;
		
		case "ZsI_Final_5":
			DialogExit();
			
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			LAi_SetImmortal(npchar, true);
			npchar.lifeday = 0;
		break;
		
		case "ZsI_officerKIll":
			DialogExit();
			
			DeleteAttribute(pchar, "questTemp.CameraDialogMode");
			sld = CharacterFromID("ZsI_Patrul_off");
			LAi_SetActorType(sld);
			LAi_ActorTurnToCharacter(sld, CharacterFromID("ListKakao"));
			LAi_SetActorType(pchar);
			DoQuestCheckDelay("ZsI_officerKIll_1", 0.1);
			DoQuestCheckDelay("ZsI_officerKIll_2", 1.3);
			AddItems(pchar, "pistol1", 2);
			AddItems(pchar, "GunPowder", 20);
			AddItems(pchar, "bullet", 20);
		break;
		
		//Торговец Барбье по квесту "Деньги на деревьях"
		case "MOT_Barbie":
			dialog.text = "Saludos, Capitán Charles de Maure. Mi nombre es Charles Barbier. ¿Podría disponer de un momento de su tiempo?";
			link.l1 = "Capitán de Maure... ¡En efecto, soy yo! Por favor, continúe, Monsieur Barbier.";
			link.l1.go = "MOT_Barbie_2";
		break;
		
		case "MOT_Barbie_2":
			dialog.text = "¡Siempre es un placer conocer a un colega, especialmente a uno con quien comparto nombre! Tengo una propuesta para usted, Capitán. Verá, necesito una escolta a Saint-Pierre, y...";
			link.l1 = "¡Conozco Saint-Pierre! ¡Pero eso es solo un viaje de dos días! Y debo confesar que todavía soy bastante inexperto para el papel de escolta. Solo asumí el mando de este barco hace una semana.";
			link.l1.go = "MOT_Barbie_3";
		break;
		
		case "MOT_Barbie_3":
			dialog.text = "Se aprecia tu honestidad, Capitán. Charles, perdona mi informalidad, pero eres precisamente la persona que necesito.";
			link.l1 = "Hmm... Recuerdo una proposición similar no hace mucho. Condujo a una emboscada pirata cerca de Le Francois.";
			link.l1.go = "MOT_Barbie_4";
		break;
		
		case "MOT_Barbie_4":
			dialog.text = "He oído hablar de ese incidente, por eso te busqué.\nPrimero, llevo una carga bastante valiosa, y siempre hay depredadores al acecho. Sin embargo, tu reciente triunfo sobre esos piratas cerca de Le Francois hará que los canallas allí se detengan.\nEn segundo lugar, tu asociación con Fadey Muscovita es una fuerte recomendación.";
			link.l1 = "Un argumento convincente, Monsieur. ¿Y qué compensación proponéis por este favor?";
			link.l1.go = "MOT_Barbie_5";
		break;
		
		case "MOT_Barbie_5":
			dialog.text = "No es un favor, Capitán, ¡sino una empresa mutuamente beneficiosa! Le pagaré cuarenta piezas de oro por escoltarme a Saint-Pierre a tiempo.";
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				notification("Trustworthy", "Trustworthy");
				link.l1 = "(Digno de confianza) Ya que me dirijo en la dirección opuesta, Monsieur, necesitaré el pago por adelantado.";
				link.l1.go = "MOT_Barbie_Torg";
			}
			link.l2 = "No es una mala propuesta, me dirijo en esa dirección de todos modos. ¡Trato hecho!";
			link.l2.go = "MOT_Barbie_Soglasen";
			link.l3 = "¿Carga valiosa, dices? Lamentablemente, Monsieur, ya he tenido suficientes aventuras por el momento.";
			link.l3.go = "MOT_Barbie_Otkaz";
		break;
		
		case "MOT_Barbie_Torg":
			dialog.text = "Es difícil negarse a un joven tan serio, Capitán. Aquí están sus cuarenta doblones. ¿Zarpamos sin demora? El tiempo es oro.";
			link.l1 = "No nos demoraremos mucho, Monsieur. Pronto zarpamos.";
			link.l1.go = "MOT_Barbie_Escadra";
			
			AddItems(pchar, "gold_dublon", 40);
			Log_info("Has recibido 40 doblones");
			PlaySound("Interface\important_item.wav");
			AddCharacterExpToSkill(pchar, "Leadership", 20);
			AddCharacterExpToSkill(pchar, "Commerce", 20);
		break;
		
		case "MOT_Barbie_Soglasen":
			dialog.text = "¡Excelente! Me prepararé para la partida de inmediato!";
			link.l3 = "";
			link.l3.go = "MOT_Barbie_Escadra";
		break;
		
		case "MOT_Barbie_Otkaz":
			dialog.text = "Entiendo, Capitán. No me interpondré. Adiós, y que tenga un buen día.";
			link.l3 = "";
			link.l3.go = "MOT_Barbie_Otkaz_2";
		break;
		
		case "MOT_Barbie_Otkaz_2":
			DialogExit();
			
			LAi_SetActorType(npchar);
			npchar.lifeday = 0;
			LAi_ActorRunToLocation(npchar, "reload", "reload6_back", "none", "", "", "", -1);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "MOT_Barbie_Escadra":
			DialogExit();
			
			SetQuestHeader("MoneyOnTrees");
			AddQuestRecord("MoneyOnTrees", "1");
			
			FantomMakeCoolSailor(npchar, SHIP_BARKENTINE, "Charles", CANNON_TYPE_CANNON_LBS3, 40, 33, 20);
			npchar.Ship.Mode = "trade";
			SetCharacterRemovable(npchar, false);
			SetCompanionIndex(pchar, -1, sti(npchar.index));
			npchar.CompanionEnemyEnable = true;
			SetCrewQuantity(npchar, 35);
			SetCharacterGoods(npchar, GOOD_ROPES, 30);
			LAi_SetImmortal(npchar, false);
			
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1_back", "", "", "", "", -1);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			SetTimerCondition("MOT_ZadanieProvaleno", 0, 0, 14, false);
			PChar.quest.MOT_Zahvatili.win_condition.l1 = "NPC_Death";
			PChar.quest.MOT_Zahvatili.win_condition.l1.character = "SharlieBarbie";
			PChar.quest.MOT_Zahvatili.win_condition = "MOT_Zahvatili";
			PChar.quest.MOT_Dostavili.win_condition.l1 = "location";
			PChar.quest.MOT_Dostavili.win_condition.l1.location = "FortFrance_town";
			PChar.quest.MOT_Dostavili.win_condition = "MOT_Dostavili";
		break;
		
		case "MOT_Barbie_101":
			if (IsCharacterPerkOn(Pchar, "Trustworthy"))
			{
				dialog.text = "Gracias por su escolta ejemplar, Capitán. Me complace que no hayamos encontrado incidentes.";
				link.l1 = "Un placer hacer negocios con usted, Monsieur. Ahora, si me disculpa, tengo mucho que atender.";
			}
			else
			{	
				dialog.text = "Gracias por tu escolta ejemplar, Capitán. Me complace que no hayamos encontrado incidentes. Aquí está tu pago, cuarenta doblones en su totalidad.";
				link.l1 = "Un placer hacer negocios con usted, Monsieur. Ahora, si me disculpa, tengo mucho que atender.";
				AddItems(pchar, "gold_dublon", 40);
				Log_info("Has recibido 40 doblones");
				PlaySound("Interface\important_item.wav");
			}
			link.l1.go = "MOT_Barbie_102";
		break;
		
		case "MOT_Barbie_102":
			dialog.text = "Charles...";
			link.l1 = "¿Sí, Charles? Pareces preocupado. ¿Algo anda mal?";
			link.l1.go = "MOT_Barbie_103";
			RemoveCharacterCompanion(pchar, npchar);
			npchar.lifeday = 0;
		break;
		
		case "MOT_Barbie_103":
			dialog.text = "Bueno, ya que eres un individuo confiable y conoces a Fadey... Mira, el comercio es un asunto arriesgado, ¿correcto?";
			link.l1 = "Si tú lo dices.";
			link.l1.go = "MOT_Barbie_104";
		break;
		
		case "MOT_Barbie_104":
			dialog.text = "Logré adquirir un lote de cuerdas a buen precio en Guadalupe de... ya sabes. Tenía la intención de venderlas rápidamente en Saint-Pierre y usar las ganancias para comprar café para revender en Willemstad. Parecía un plan sensato.";
			link.l1 = "No pongo en duda su integridad, Monsieur, pero todo esto suena bastante dudoso. Habla de su cargamento como si fuera oro. Mientras tanto, mi barco está cargado con estas cuerdas y son baratas como la tierra.";
			link.l1.go = "MOT_Barbie_106";
		break;
		
		case "MOT_Barbie_106":
			dialog.text = "Charles, estas cuerdas son de la más alta calidad, elaboradas con cáñamo superior y tejidas en las fábricas del zar de Moscú. Sirven para propósitos estratégicos y se utilizan en el aparejo de los buques de guerra. Los ingleses monopolizan las rutas comerciales con Moscovia, prohibiendo el libre comercio de tales cuerdas. Otras naciones compiten intensamente para asegurar la totalidad del suministro disponible para sus astilleros en Europa también.";
			link.l1 = "¿Así que esto es contrabando?";
			link.l1.go = "MOT_Barbie_107";
		break;
		
		case "MOT_Barbie_107":
			dialog.text = "Sí. Por desgracia, el año pasado tuve un desencuentro con los contrabandistas de Santiago. Casi lo había olvidado, pero estos individuos mantienen vínculos estrechos y una gran memoria. Un consejo: evite indignarlos e incumplir los tratos; es una situación que no podrá rectificar más adelante.";
			link.l1 = "Gracias, pero el contrabando no me interesa.";
			link.l1.go = "MOT_Barbie_108";
		break;
		
		case "MOT_Barbie_108":
			dialog.text = "¡Lástima! El comercio honesto puede traerle un buen beneficio, pero nunca acumularás una riqueza sustancial. Sin embargo, no inicié esta conversación algo precaria contigo sin razón. Te propongo que me compres un cargamento de cuerdas. Los contrabandistas locales frecuentan la taberna, y serán compradores ansiosos de esta carga. ¡Piénsalo! Hoy obtendrás una ganancia considerable sin aventurarte en alta mar.";
			link.l1 = "¿Cuánto pides por la carga?";
			link.l1.go = "MOT_Barbie_109";
		break;
		
		case "MOT_Barbie_109":
			dialog.text = "Diez mil pesos. Es una suma modesta, y revender las cuerdas a los contrabandistas generará considerables ganancias.";
			if (sti(pchar.Money) >= 10000)
			{
				link.l1 = "Jamás me perdonaría si dejara pasar una oportunidad como esta. Toma la plata y asegura que las mercancías sean entregadas puntualmente a mi embarcación.";
				link.l1.go = "MOT_Barbie_ContraSoglasen";
			}
			if (sti(pchar.Money) >= 7000)
			{
				link.l2 = "Este es un empeño precario, amigo mío. Encontrémonos a mitad de camino, ¿de acuerdo? Aceptaré tus cuerdas por siete mil.";
				link.l2.go = "MOT_Barbie_ContraTorg";
			}
			link.l3 = "Esa es una suma considerable, Monsieur. Simpatizo con su situación, pero no puedo aceptar tal riesgo.";
			link.l3.go = "MOT_Barbie_ContraOtkaz";
		break;
		
		case "MOT_Barbie_ContraSoglasen":
			dialog.text = "¡Mi gratitud, Charles! ¡Me has salvado de la ruina financiera! Las mercancías serán despachadas rápidamente y con la máxima precaución.\nPermíteme ofrecerte un consejo como colega comerciante: una vez que contrates a un buen intendente, adquiere café en Saint-Pierre y véndelo con ganancia en Willemstad. Las capitales locales pagan generosamente por los bienes coloniales, exportándolos a Europa para obtener ganancias sustanciales. ¡Buena suerte en tus empresas, amigo!";
			link.l1 = "Adiós, Monsieur.";
			link.l1.go = "MOT_Barbie_ContraSoglasen_2";
			AddCharacterGoodsSimple(pchar, GOOD_ROPES, 30);
			AddMoneyToCharacter(pchar, -10000);
			Log_info("Has recibido 30 cuerdas");
			PlaySound("Interface\important_item.wav");
		break;
		
		case "MOT_Barbie_ContraSoglasen_2":
			DialogExit();
			
			AddQuestRecord("MoneyOnTrees", "5");
			CloseQuestHeader("MoneyOnTrees");
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			
			sld = CharacterFromID("SharlieBarbie");
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		case "MOT_Barbie_ContraTorg":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 30)
			{
				notification("Skill Check Passed", SKILL_COMMERCE);
				dialog.text = "¡Mi gratitud, Charles! ¡Me has salvado de la ruina financiera! Las mercancías serán despachadas rápidamente y con la mayor precaución\nPermíteme ofrecerte un consejo como compañero comerciante: una vez que contrates a un intendente decente, adquiere café en Saint-Pierre y véndelo con ganancia en Willemstad. Las capitales locales pagan generosamente por los bienes coloniales, exportándolos a Europa con beneficios sustanciales. ¡Buena suerte en tus empresas, amigo!";
				link.l1 = "Adiós, Monsieur.";
				link.l1.go = "MOT_Barbie_ContraSoglasen_2";
				AddCharacterGoodsSimple(pchar, GOOD_ROPES, 30);
				AddMoneyToCharacter(pchar, -7000);
				Log_info("Has recibido 30 cuerdas");
				PlaySound("Interface\important_item.wav");
			}
			else
			{
				notification("Skill Check Failed (31)", SKILL_COMMERCE); 
				dialog.text = "No puedo, Capitán. Mi mercancía es seria y merece un trato serio. La mayoría de los capitanes libres no se atreven a comerciar con bienes estratégicos. Lamentablemente, el regateo no procede aquí.";
				if (sti(pchar.Money) >= 10000)
				{
					link.l1 = "Jamás me lo perdonaría si dejara pasar una oportunidad como esta. Toma la plata y asegúrate de que las mercancías se entreguen prontamente a mi navío.";
					link.l1.go = "MOT_Barbie_ContraSoglasen";
				}
				link.l2 = "Esa es una suma considerable, Monsieur. Simpatizo con su situación, pero no puedo aceptar tal riesgo.";
				link.l2.go = "MOT_Barbie_ContraOtkaz";
			}
		break;
		
		case "MOT_Barbie_ContraOtkaz":
			dialog.text = "¡Qué lástima! Hasta luego, Capitán.";
			link.l1 = "";
			link.l1.go = "MOT_Barbie_ContraOtkaz_2";
		break;
		
		case "MOT_Barbie_ContraOtkaz_2":
			DialogExit();
			
			AddQuestRecord("MoneyOnTrees", "4");
			CloseQuestHeader("MoneyOnTrees");
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			
			sld = CharacterFromID("SharlieBarbie");
			sld.lifeday = 0;
			LAi_SetCitizenType(sld);
			LAi_CharacterDisableDialog(sld);
			
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
		break;
		
		//Миниквест "Делюк"
		//Матрос Алонсо
		case "Del_Alonso":
			dialog.text = "Problemas, capitán.";
			link.l1 = "¿Y bien?";
			link.l1.go = "Del_Alonso_2";
		break;
		
		case "Del_Alonso_2":
			dialog.text = "Nuestro navegante ha sido arrestado y llevado a las mazmorras locales. Dicen que es por una cuestión de deudas.";
			link.l1 = "¿Qué, otra vez?!";
			link.l1.go = "Del_Alonso_3";
		break;
		
		case "Del_Alonso_3":
			dialog.text = "Es un pícaro travieso, Capitán.";
			link.l1 = "¡Qué momento tan terrible! Sin un navegante, estamos varados aquí. ¡Tendré que sacarlo de apuros otra vez! Hablaré con el comandante...";
			link.l1.go = "Del_Alonso_4";
		break;
		
		case "Del_Alonso_4":
			dialog.text = "¿Permiso para hablar, capitán?";
			link.l1 = "Adelante.";
			link.l1.go = "Del_Alonso_5";
		break;
		
		case "Del_Alonso_5":
			dialog.text = "¿Por qué pasar por todos estos problemas? Un hombre como él solo traerá problemas al barco.";
			link.l1 = "¿Tengo otra opción? Apenas hay otros navegantes disponibles, así que mis opciones son bastante limitadas.";
			link.l1.go = "Del_Alonso_6";
		break;
		
		case "Del_Alonso_6":
			dialog.text = "Es cierto, encontrar un navegante de primera clase es difícil, pero aún no necesitas un maestro, solo uno competente. Tu situación cambió en la última semana, ¿sabes esto, verdad? Ya no necesitas buscar en el fondo del barril para encontrar hombres para tu tripulación. La gente ahora habla de cómo derrotaste a ese pirata y las conexiones que tienes. La tripulación también está contigo, Capitán, nos agradas.";
			link.l1 = "Eso es reconfortante, Alonso. ¿Y qué opina la tripulación sobre Deluc?";
			link.l1.go = "Del_Alonso_7";
		break;
		
		case "Del_Alonso_7":
			dialog.text = "Aprende rápido, capitán. La tripulación dice que, aunque es buen oficial y nos trata bien, no vale la pena. Un gran mercante acaba de despedir a sus oficiales; tal vez busque en la taberna. Seguro que allí encuentra a quien necesita. Y olvídese de Deluc; eso opinan los hombres.";
			link.l1 = "Gracias por el consejo, Alonso. Sabía que podía contar contigo. Vuelve al barco y haz guardia mientras resuelvo esto.";
			link.l1.go = "Del_Alonso_8";
		break;
		
		case "Del_Alonso_8":
			dialog.text = "¡A la orden!";
			link.l1 = "...";
			link.l1.go = "Del_Alonso_9";
		break;
		
		case "Del_Alonso_9":
			DialogExit();
			SetQuestHeader("FolkeDeluc");
			AddQuestRecord("FolkeDeluc", "1");
			
			npchar.lifeday = 0;
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			SetFunctionLocationCondition("FortfranceJailOff_AddQuestMark", "fortfrance_prison", false);
			QuestCloseSeaExit();
			sld = CharacterFromID("Folke");
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Del_Folke_1";
			RemovePassenger(pchar, sld);
			LAi_SetStayType(sld);
			ChangeCharacterAddressGroup(sld, "FortFrance_prison", "goto", "goto9");
			bDisableFastReload = false;
			chrDisableReloadToLocation = false;
			pchar.questTemp.Del_Deluck = true;
			
			sld = GetCharacter(NPC_GenerateCharacter("Del_shturman", "mercen_4", "man", "man", 5, FRANCE, 3, false, "quest"));
			GiveItem2Character(sld, "blade_03");
			EquipCharacterByItem(sld, "blade_03");
			sld.Dialog.Filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "Del_shturman";
			LAi_SetSitType(sld);
			sld.greeting = "officer_hire";
			SetSelfSkill(sld, 21, 23, 18, 33, 25);
			SetShipSkill(sld, 25, 10, 8, 6, 35, 11, 13, 25, 14);
			SetSPECIAL(sld, 7, 10, 6, 8, 7, 8, 4);
			sld.rank = 5;
			SetCharacterPerk(sld, "ShipSpeedUp");
			SetCharacterPerk(sld, "HullDamageUp");
			SetCharacterPerk(sld, "BasicDefense");
			//sld.quest.officertype = "navigator";
			FreeSitLocator("FortFrance_tavern", "sit4");
			ChangeCharacterAddressGroup(sld, "FortFrance_tavern", "sit", "sit4");
			AddLandQuestMark(characterFromId("Del_shturman"), "questmarkmain");
		break;
		
		//Делюк
		case "Del_Folke_1":
			DelLandQuestMark(npchar);
			dialog.text = "Capitán...";
			link.l1 = "Tengo un millón de preguntas, pero haré solo una: ¿cómo lograste acumular nuevas deudas mientras has estado conmigo todo este tiempo, enseñándome la navegación?";
			link.l1.go = "Del_Folke_2";
		break;
		
		case "Del_Folke_2":
			dialog.text = "Me avergüenza admitirlo, Capitán, pero he estado pidiendo prestado a varios prestamistas mucho antes de unirme a su tripulación. Mi plan era mantenerme bajo perfil y trabajar en su barco hasta ganar lo suficiente para saldar todas mis deudas. Pero cometí el error de dejar el barco aquí para involucrarme con cierta mujer aquí en Saint-Pierre, y los soldados me apresaron justo debajo de ella. No contraje nuevas deudas en Martinica, ya que usted pagó la última, ¡lo juro!";
			link.l1 = "¡Eres un imbécil, Deluc, y me has convertido en el hazmerreír de Saint-Pierre!";
			link.l1.go = "Del_Folke_3a";
			link.l2 = "Impresionante, Folke. Gracias por la anécdota.";
			link.l2.go = "Del_Folke_3b";
		break;
		
		case "Del_Folke_3a":
			AddComplexSelfExpToScill(10, 10, 10, 10);
			dialog.text = "¿Qué harás, Capitán? ¿Puedes sacarme de nuevo? Encontrar un nuevo navegante no será fácil, ¿sabes...?";
			link.l1 = "Quédate quieto por ahora. Tomaré una decisión. Puede que visite al banquero de nuevo.";
			link.l1.go = "Del_Folke_4";
		break;
		
		case "Del_Folke_3b":
			AddCharacterExpToSkill(pchar, "Sailing", 10);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 10);//торговля
			dialog.text = "¿Qué harás, Capitán? ¿Puedes sacarme de apuros otra vez? Encontrar un nuevo navegador no será fácil, ¿sabes...?";
			link.l1 = "Quédate aquí por ahora. Tomaré una decisión. Puede que visite al banquero de nuevo.";
			link.l1.go = "Del_Folke_4";
		break;
		
		case "Del_Folke_4":
			dialog.text = "No es como si tuviera a dónde ir...";
			link.l1 = "...";
			link.l1.go = "Del_Folke_5";
		break;
		
		case "Del_Folke_5":
			DialogExit();
			
			pchar.questTemp.Del_Rostovshik = true;
			LAi_CharacterDisableDialog(npchar);
			AddLandQuestMark(characterFromId("FortFrance_usurer"), "questmarkmain");
		break;
		
		case "Del_Folke_10":
			dialog.text = "Capitán, gracias. Has saldado mis deudas, pero ahora te debo una deuda aún mayor: mi vida. ¡Y estoy verdaderamente agradecido por ello! Te aseguro que no encontrarás un hombre más leal en todo este mundo.";
			link.l1 = "Supongo que algunas deudas solo pueden pagarse incurriendo en otras. Volvamos al trabajo, Folke. Hay mucho por hacer en el mar.";
			link.l1.go = "Del_Folke_11a";
			link.l2 = "No lo olvides, Deluc. La próxima vez simplemente te dispararé.";
			link.l2.go = "Del_Folke_11b";
			
			chrDisableReloadToLocation = false;
			LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			QuestOpenSeaExit()
			sld = CharacterFromID("Del_shturman");
			sld.lifeday = 0;
			
			sld = CharacterFromID("Del_Ohranik");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload3", "none", "", "", "", -1);
		break;
		
		case "Del_Folke_11a":
			AddCharacterExpToSkill(pchar, "Sailing", 10);//навигация
			AddCharacterExpToSkill(pchar, "Commerce", 10);//торговля
			dialog.text = "¡Sí, sí, Capitán!";
			link.l1 = "...";
			link.l1.go = "Del_Folke_12";
		break;
		
		case "Del_Folke_11b":
			AddComplexSelfExpToScill(10, 10, 10, 10);
			dialog.text = "¡Aye aye, Capitán!";
			link.l1 = "...";
			link.l1.go = "Del_Folke_12";
		break;
		
		case "Del_Folke_12":
			DialogExit();
			EndQuestMovie();
			AddQuestRecord("FolkeDeluc", "3");
			CloseQuestHeader("FolkeDeluc");
			
			ChangeCharacterComplexReputation(pchar, "authority", -2);
			AddCrewMorale(Pchar, -30);
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "", "", "", "", -1);
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.quest.meeting = true;
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(npchar.id);
			npchar.OfficerWantToGo.DontGo = true;
			npchar.loyality = MAX_LOYALITY;
			AddPassenger(pchar, npchar, false);
			npchar.OfficerImmortal = true;
			npchar.Health.HP       = 60.0; 
			npchar.Health.maxHP    = 60.0;
			SetCharacterPerk(npchar, "ShipEscape");
			npchar.location = "None";
			npchar.Dialog.CurrentNode = "hired";
			npchar.Payment = true;
			SetCharacterPerk(npchar, "ByWorker");
			DeleteAttribute(npchar, "CompanionDisable");
		break;
		
		//Штурман из таверны. Стандартный диалог, но с некоторыми изменениями (обучение найма для новичков)
		case "Del_shturman":
			dialog.text = "¿Necesitáis un oficial, capitán?";
    		Link.l1 = "¿Un oficial? ¿Y en qué eres bueno?";
    		Link.l1.go = "Del_Node_2";
			Link.l2 = "No, tengo el juego completo.";
			Link.l2.go = "Exit";
			NextDiag.TempNode = "Del_OnceAgain";
		break;		
		case "Del_Node_2":
			dialog.text = "Soy el mejor navegante de estas aguas. Todavía sé un poco sobre medicina. Y estoy dispuesto a hacerte un favor y servir bajo tu mando.";
			Link.l1 = "¿Y cuánto quieres?";
			Link.l1.go = "Del_price";
			Link.l2 = "¿Y qué clase de especialista eres?";
			Link.l2.go = "Del_ShowParam_exit";
			Link.l3 = "¡Ay, ya tengo un navegante!";
			Link.l3.go = "Exit";
		break;		
		case "Del_price":
			dialog.text = "Creo que podemos acordar en 4000 pesos.";
			Link.l1 = "¿No es eso un poco exagerado?";
			Link.l1.go = "Del_trade";
			Link.l2 = "De acuerdo. Considérate parte de la tripulación.";
			Link.l2.go = "Del_hire";
			Link.l3 = "No vales este dinero.";
			Link.l3.go = "exit";
		break;	
		case "Del_ShowParam_exit":
			NextDiag.TempNode = "Del_OnceAgain";
			NPChar.quest.meeting = true;
			DialogExit();
			
			PChar.SystemInfo.OnlyShowCharacter = true;
            LaunchCharacter(NPChar);
		break;		
		case "Del_OnceAgain":
			NextDiag.TempNode = "Del_OnceAgain";
			dialog.text = "¿Has cambiado de opinión, capitán? ¿Decidiste que un nuevo navegante no vendría mal?";
			// boal -->
			if (FindFreeRandomOfficer() > 0)
			{
                Link.l1 = "Algo así. ¿Cuánto quieres?";
                Link.l1.go = "Del_price";
			}
			Link.l2 = "¿Y de qué eres capaz?";
			Link.l2.go = "Del_ShowParam_exit";
			// boal <--
			Link.l3 = "Tengo un juego completo. Nos vemos.";
			Link.l3.go = "exit";
		break;		
		case "Del_trade":
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) > 25)
			{
				dialog.text = "Está bien... Supongo que podría aceptar incluso 2500 pesos. ¿Qué dices?";
				Link.l1 = "Ahora eso está mejor. Estás dentro.";
				Link.l1.go = "Del_hire";
				pchar.questTemp.Del_SniziliTsenu = true;
			}
			else
			{
				dialog.text = "Lo siento, capitán, pero valgo exactamente tanto como pedí. Si es mucho para usted, entonces busque a alguien más.";
				Link.l1 = "Está bien, estoy de acuerdo. Te llevaré.";
				Link.l1.go = "Del_hire";				
				Link.l2 = "Eso es lo que voy a hacer. Adiós.";
				Link.l2.go = "exit";
			}
		break;		
		case "Del_hire":
			if (CheckAttribute(pchar, "questTemp.Del_SniziliTsenu"))
			{
				if (sti(pchar.Money) >= 2500)
				{
					AddMoneyToCharacter(pchar, -2500);
					NextDiag.TempNode = "OnboardSoon";
					dialog.text = "Gracias, capitán. No se arrepentirá de su elección.";
					Link.l1 = "Eso espero.";
					Link.l1.go = "Del_Exit_hire";
					DeleteAttribute(pchar, "questTemp.Del_SniziliTsenu");
				}
				else
				{
					dialog.text = "¡Veo que estás corto de dinero, capitán! Lo siento, pero no trabajo a crédito.";
					Link.l1 = "¡Oh, diablo!";
					Link.l1.go = "Exit";								
				}
			}
			else
			{
				if (sti(pchar.Money) >= 4000)
				{
					AddMoneyToCharacter(pchar, -4000);
					NextDiag.TempNode = "Del_OnboardSoon";
					dialog.text = "Gracias, capitán. No se arrepentirá de su elección.";
					Link.l1 = "Eso espero.";
					Link.l1.go = "Del_Exit_hire";
				}
				else
				{
					dialog.text = "¡Veo que andas corto de dinero, capitán! Lo siento, pero no trabajo a crédito.";
					Link.l1 = "¡Oh, demonio!";
					Link.l1.go = "Exit";								
				}
			}
		break;
		case "Del_OnboardSoon":			
			NextDiag.TempNode = "Del_OnboardSoon";
			dialog.text = "Solo terminaré mi bebida, capitán, y luego iré al barco. No te preocupes, estaré allí a tiempo.";
			Link.l1 = "Está bien. ¡Si llegas tarde, te haré fregar la cubierta!";
			Link.l1.go = "Exit";											
		break;
		case "Del_exit_hire":
			npchar.Dialog.Filename = "Enc_Officer_dialog.c";
			npchar.Dialog.CurrentNode = "hired";
			Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
			AddDialogExitQuestFunction("LandEnc_OfficerHired");
			NPChar.quest.meeting = true;
			npchar.loyality = 18;
			
			ChangeCharacterComplexReputation(pchar, "authority", 2);
			AddCrewMorale(Pchar, 30);
			QuestOpenSeaExit();
			DelLandQuestMark(npchar);
			pchar.quest.FortfranceJailOff_AddQuestMark.over = "yes";
			if (GetCharacterIndex("FortFranceJailOff") != -1)
			{
				DelLandQuestMark(characterFromId("FortFranceJailOff"));
			}
			sld = CharacterFromID("Folke");
			LAi_CharacterDisableDialog(sld);
			DeleteAttribute(pchar, "questTemp.Del_Deluck");
			DeleteAttribute(pchar, "questTemp.Del_DeluckSvoboda");
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik");
			DeleteAttribute(pchar, "questTemp.Del_Rostovshik_repeat");
			pchar.questTemp.Del_DeluckSiditTurma = true;
			AddQuestRecord("FolkeDeluc", "4");
			CloseQuestHeader("FolkeDeluc");
			DialogExit();
		break;
		
		//Квест "Травля крысы"
		//Капитан корабля Хейтер
		case "TK_Kapitan":
			dialog.text = "¡Está bien, está bien! Me rindo, ¡maldita sea!";
			link.l1 = "Ahora eres mi prisionero, pero pronto te encontrarás en Saint-Pierre frente a la horca.";
			link.l1.go = "TK_Kapitan_1";
			PChar.quest.TK_Potopil.over = "yes";
		break;
		
		case "TK_Kapitan_1":
			dialog.text = "Entonces eso es todo... ¿Cómo supiste dónde encontrarme?";
			link.l1 = "El Gobernador me informó personalmente sobre la situación.";
			link.l1.go = "TK_Kapitan_2";
		break;
		
		case "TK_Kapitan_2":
			dialog.text = "¡Qué imbécil! ¡Debe haberse enterado de mis planes y decidió joderme abiertamente justo frente a su guarida para dar un ejemplo a otras tripulaciones!";
			link.l1 = "Un insulto más a su Excelencia, y vuestro viaje a Saint-Pierre será rápido e inolvidable.";
			link.l1.go = "TK_Kapitan_3";
		break;
		
		case "TK_Kapitan_3":
			dialog.text = "¿Eh? No estoy hablando de vuestra excelencia, compañero. Estoy hablando de Jacques el Buen Hombre\n¡Maldita sea, los rumores eran ciertos! Barbazon se dio cuenta de que me estaba convirtiendo en una amenaza, así que me entregó al gobernador para mantenerme fuera de su camino. Por eso tenías mi ubicación exacta, ¡y me atrapaste con los pantalones abajo, ja ja!";
			link.l1 = "Estás delirando. ¡El Gobernador de Martinica no se rebajaría a tratar con un líder pirata!";
			link.l1.go = "TK_Kapitan_4";
		break;
		
		case "TK_Kapitan_4":
			dialog.text = "Sí, claro. Tal vez no directamente, pero creo que hizo un trato con Barbazon. Le conviene: un pirata peligroso es ahorcado, los informes se ven bien y los 'gastos por la operación militar' están justificados. He servido, ¿sabes? Así que sé cómo van las cosas allí. ¿Y tú? ¿Sirves en la guarnición?";
			link.l1 = "Sirvo a mi país, y esta conversación ha terminado. Bienvenido a la celda.";
			link.l1.go = "TK_Kapitan_5";
		break;
		
		case "TK_Kapitan_5":
			dialog.text = "Espera, compañero. No soy castellano, y hoy no estaba en el mar para saquear mercaderes franceses. ¡Tengo principios, maldita sea! Hagamos un trato, ¿de acuerdo?";
			link.l1 = "Estás malgastando el aliento, pirata. Al calabozo contigo.";
			link.l1.go = "TK_Kapitan_7_1";
			link.l2 = "¿Intentando evitar la horca?";
			link.l2.go = "TK_Kapitan_6";
		break;
		
		case "TK_Kapitan_6":
			dialog.text = "Tenía una pista sólida aquí, y te daré una parte si me dejas ir. Mi vida vale solo un par de miles en plata, pero puedo hacer que ganes mucho más, y libre de impuestos.";
			if (CheckAttribute(pchar, "questTemp.MOT_SharlyBad"))
			{
				link.l1 = "Esa es una oferta tentadora... Aunque la piratería no es precisamente mi fuerte.";
				link.l1.go = "TK_Kapitan_7";
			}
			else
			{
				link.l1 = "¡No soy un pirata!";
				link.l1.go = "TK_Kapitan_7";
			}
		break;
		
		case "TK_Kapitan_7":
			dialog.text = "Depende de ti, compañero. Si quieres ser un hombre de fortuna o un capitán sin un céntimo pero con principios. Si quieres dinero de verdad y libertad, tendrás que meterte un poco en todo. Aprovecha cualquier oportunidad.";
			link.l1 = "Tienes ciertamente una forma especial de hablar...";
			link.l1.go = "TK_Kapitan_8";
			link.l2 = "Ejém... Supongo que te llevaré a Saint-Pierre. Parece ser lo correcto.";
			link.l2.go = "TK_Kapitan_7_1";
		break;
		
		case "TK_Kapitan_7_1":
			dialog.text = "¡Que te jodan entonces!";
			link.l1 = "...";
			link.l1.go = "TK_Kapitan_Plen";
		break;
		
		case "TK_Kapitan_8":
			dialog.text = "Entonces, ¿tenemos un trato?";
			link.l1 = "Sí. Dime quién es tu contacto, y eres libre de irte.";
			link.l1.go = "TK_Kapitan_9";
		break;
		
		case "TK_Kapitan_9":
			dialog.text = "Hay un inglés listillo en el Henry, una barca. Está a punto de terminar su pequeño viaje comercial, llevando mercancías de las plantaciones francesas a Willemstad para obtener un buen beneficio. Pronto saldrá de Martinica hacia Curazao. Es un trabajo fácil: sin escolta, y la barca está cargada de objetos de valor a expensas de sus defensas. Se está tardando demasiado, así que los rumores se están extendiendo. ¿Mi consejo, camarada? No seas tímido en la taberna. Unos tragos para los locales, y te soltarán algunos secretos.";
			link.l1 = "¿Por qué no hay escolta?";
			link.l1.go = "TK_Kapitan_10";
		break;
		
		case "TK_Kapitan_10":
			dialog.text = "¿Cómo más podría un inglés llevar a cabo sus negocios discretamente en Curazao? Es una guerra abierta entre Inglaterra y los Países Bajos, y obtener una licencia de comercio es un engorro y es caro.";
			link.l1 = "Pero no hay guerra entre Francia e Inglaterra. ¿Cuáles son las consecuencias si ataco un navío neutral?";
			link.l1.go = "TK_Kapitan_11";
		break;
		
		case "TK_Kapitan_11":
			dialog.text = "Ninguno si eres discreto. La tripulación definitivamente presumirá de tus hazañas en el puerto más cercano, pero mientras no ataques regularmente barcos ingleses o holandeses, deberías estar bien. Acércate al Henry bajo la bandera francesa. Carga tus cañones con metralla, acorta la distancia, suelta el Negro, dispara unas cuantas andanadas y aborda a la maldita. Es simple, amigo.";
			link.l1 = "Ya veremos. Cumpliré mi palabra y te liberaré. No me des una razón para lamentarlo.";
			link.l1.go = "TK_Kapitan_12";
		break;
		
		case "TK_Kapitan_12":
			dialog.text = "No lo haré. Buena caza, camarada.";
			link.l1 = "...";
			link.l1.go = "TK_Kapitan_Otpustil";
		break;
		
		case "TK_Kapitan_Plen":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			sld.DontRansackCaptain = true;
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			
			sld = GetCharacter(NPC_GenerateCharacter("TK_Heiter2", "mercen_8", "man", "man", sti(PChar.rank), PIRATE, -1, false, "pirate"));
			sld.name = "Daniel";
			sld.lastname = "Montbars";
			AddPassenger(pchar, sld, false);
			SetCharacterRemovable(sld, false);
			ChangeCharacterAddressGroup(sld, "My_Deck", "goto", "goto7");
			LAi_SetGroundSitType(sld);
			LAi_CharacterDisableDialog(sld);
			DoQuestCheckDelay("TK_KapitanSidit_1", 0.8);
		break;
		
		case "TK_Kapitan_Otpustil":
			DialogExit();
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			sld = &Characters[sti(pchar.GenQuest.QuestAboardCabinDialogIdx)];
			Lai_SetPlayerType(pchar);
			LAi_RemoveCheckMinHP(sld);
			LAi_SetImmortal(sld, true);
			sld.ShipEnemyDisable  = true;
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			LAi_SetCitizenType(sld);
			sld.lifeday = 0;
			LAi_EnableReload();
			Log_SetActiveAction("Reload");
			pchar.questTemp.TK_Otpustil = true;
			AddQuestRecord("TravlyaKrys", "4");
			
			SetTimerCondition("TK_GenrihSpawn", 0, 0, 1, false);	
		break;
		
		//Диего и Гийом за столиком по квесту "Встреча с Диего"
		case "VsD_DiegoAndErnat":
			dialog.text = "... Me encargaré de tus problemas de juego. ¡Oye! ¡Mantén la compostura, hombre! O te controlas, o te haré entrar en razón yo mismo.";
			link.l1 = "";
			link.l1.go = "VsD_DiegoAndErnat_2";
			sld = CharacterFromID("GiumDyubua");
			LAi_CharacterEnableDialog(sld);
		break;
		
		case "VsD_DiegoAndErnat_2":
			DialogExit();
			StartInstantDialogNoType("GiumDyubua", "VsD_DiegoAndErnat_3", "Quest\Sharlie\OtherNPC.c");
		break;
		
		case "VsD_DiegoAndErnat_3":
			dialog.text = "Monsieur, mis disculpas, pero está siendo un poco molesto.";
			link.l1 = "Sí, por supuesto. Que tengan un agradable día, caballeros.";
			link.l1.go = "VsD_DiegoAndErnat_4";
		break;
		
		case "VsD_DiegoAndErnat_4":
			DialogExit();
			sld = CharacterFromID("Diego");
			LAi_CharacterDisableDialog(sld);
			sld = CharacterFromID("GiumDyubua");
			LAi_CharacterDisableDialog(sld);
		break;
		
		//Гийом Дюбуа по квесту "Встреча с Диего"
		case "VsD_GiumDyubua":
			dialog.text = "¡Capitán de Maure! ¡Espere!";
			link.l1 = "¿Sí, teniente?";
			link.l1.go = "VsD_GiumDyubua_2";
			DelLandQuestMark(npchar);
		break;
		
		case "VsD_GiumDyubua_2":
			dialog.text = "Apenas pude seguirte. Ha habido... un pequeño contratiempo, capitán. ¡Qué desastre!";
			link.l1 = "Toma un respiro y cálmate, por favor.";
			link.l1.go = "VsD_GiumDyubua_3";
		break;
		
		case "VsD_GiumDyubua_3":
			dialog.text = "Bien, bien. Escucha, después de cargar los cañones, ¿queda aún espacio en la bodega?";
			link.l1 = "Aún soy nuevo en esto, así que no estoy del todo seguro, pero supongo que debería haberlo.";
			link.l1.go = "VsD_GiumDyubua_4";
		break;
		
		case "VsD_GiumDyubua_4":
			dialog.text = "¡Excelente! El Comando quiere apoyar la operación en Portobello de cualquier manera posible, así que han ordenado que se entreguen doscientas medidas adicionales de pólvora al Belicoso. Puede que no parezca mucho, pero unas cuantas salvas extra podrían cambiar el curso de la batalla.";
			link.l1 = "Muy bien, teniente. Estoy listo para hacer mi parte. Carga la pólvora, no me molesta en absoluto.";
			link.l1.go = "VsD_GiumDyubua_5";
		break;
		
		case "VsD_GiumDyubua_5":
			dialog.text = "Gracias, Capitán. Informaré a nuestra tripulación de carga de inmediato. Afortunadamente, no han terminado con el '"+PChar.Ship.Name+"¡todavía.  Buena suerte en tu misión!";
			link.l1 = "Gracias, aunque hasta ahora ha sido bastante caótico. Adiós, teniente.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("VsD_GoToCity");
		break;
		
		//Фульк или Алонсо по квесту "Встреча с Диего"
		case "VsD_FolkeAlonso":
			dialog.text = "¡Jesús, Capitán! ¡Gracias al cielo que no estás herido!";
			link.l1 = "¿Qué demonios ha pasado?! ¿Qué le ha pasado a mi barco?!";
			link.l1.go = "VsD_FolkeAlonso_2";
		break;
		
		case "VsD_FolkeAlonso_2":
			dialog.text = "¡No lo sé, capitán! Solo me estaba despidiendo de una mujer que conocí recientemente... ¡Oh mierda! ¡Eugenie!";
			link.l1 = "Está muerta, "+npchar.name+". Lo siento, pero necesitamos concentrarnos y ver si alguno de nuestros tripulantes está herido.";
			link.l1.go = "VsD_FolkeAlonso_3";
		break;
		
		case "VsD_FolkeAlonso_3":
			dialog.text = "Apenas nos conocíamos... ¡Aaah! ¡Maldita sea! Informando, Capitán: la mayoría de la tripulación estaba en tierra cuando ocurrió la explosión, afortunadamente. Los muchachos estaban aprovechando un permiso en tierra antes de nuestro próximo gran viaje. Pero la guardia del barco... Temo que no hay sobrevivientes. ¡Solo mira alrededor! ¡Los escombros hirieron o mataron a personas incluso aquí, en este muelle! Es un milagro que los dos estemos ilesos.";
			link.l1 = "¿Qué pasa con el barco? ¿Está bien?!";
			link.l1.go = "VsD_FolkeAlonso_4";
		break;
		
		case "VsD_FolkeAlonso_4":
			dialog.text = "¿¡Está ella?! Mis disculpas, Capitán. Es difícil decirlo con certeza, pero parece que la explosión ocurrió en la cubierta superior, no abajo. No veo ningún incendio activo, y parece que hemos escapado de un daño mayor.";
			link.l1 = "...";
			link.l1.go = "VsD_FolkeAlonso_5";
			sld = GetCharacter(CreateCharacterClone(CharacterFromID("PortPaxAmmoOff"), 0));
			sld.id = "PortPaxAmmoOff_clone";
			LAi_LoginInCaptureTown(sld, true);
			ChangeCharacterAddressGroup(sld, "PortPax_town", "quest", "quest1");
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "VsD_FolkeAlonso_5":
			DialogExit();
			LAi_SetStayType(pchar);
			sld = CharacterFromID("PortPaxAmmoOff_clone");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "VsD_Komendant";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 3, 0);
		break;
		
		case "VsD_Komendant":
			dialog.text = "¡¿Qué diablos, Capitán?!";
			link.l1 = "¡Estoy preguntando lo mismo, Coronel!";
			link.l1.go = "VsD_Komendant_1";
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				LAi_SetActorType(sld);
				LAi_ActorGoToLocator(sld, "reload", "reload1", "", -1);
			}
		break;
		
		case "VsD_Komendant_1":
			dialog.text = "¡Cuídate, de Maure! ¡Aceptaste este trabajo de la Armada, cargaste cañones pesados, propiedad de la Corona, de importancia estratégica! ¿Comprendes la importancia de estos cañones para toda la operación? ¡Tu negligencia ha puesto en peligro a casi cuatrocientos hombres y un buque de guerra francés! ¡Te enfrentas a un juicio por traición aquí!";
			link.l1 = "¡Calma, coronel! Milagrosamente, parece que mi barco sobrevivió, y tu preciada carga está mayormente intacta... mayormente.";
			link.l1.go = "VsD_Komendant_2";
		break;
		
		case "VsD_Komendant_2":
			dialog.text = "¿Qué quieres decir con 'mayormente'?";
			link.l1 = "No puedo garantizar que las doscientas medidas de pólvora, cargadas en el último momento por uno de tus tenientes, no estuvieran dañadas. Debían cargarse al final, y probablemente fueron las que explotaron.";
			link.l1.go = "VsD_Komendant_3";
		break;
		
		case "VsD_Komendant_3":
			dialog.text = "¿Qué es este disparate, Charles? ¿Qué teniente? ¿Qué pólvora? ¡No di tal orden!";
			link.l1 = "Este teniente debe haber sido de tu guarnición. No pregunté su nombre, pero parecía estar al tanto de la operación.";
			link.l1.go = "VsD_Komendant_4";
		break;
		
		case "VsD_Komendant_4":
			dialog.text = "¡Ah, mierda! Parece que los castellanos también están inclinados a jugar sucio... Me encargaré de esta desafortunada situación, Capitán. No obstante, usted todavía tiene un trabajo que hacer: ¿está seguro de que su barco es apto para navegar?";
			link.l1 = "Está a flote, pero definitivamente necesita reparaciones significativas.";
			link.l1.go = "VsD_Komendant_5";
			SetMusic("classic_fra_music_day");
		break;
		
		case "VsD_Komendant_5":
			dialog.text = "No hay tiempo para eso, Capitán. Zarpe inmediatamente y complete la misión. Las apuestas son demasiado altas para retrasarse.";
			link.l1 = "¿No podemos tener al menos un día, por el amor de Dios? ¡El astillero podría hacer las reparaciones necesarias! ¿Y qué hay de mi tripulación?! ¡Seguramente hay bajas!";
			link.l1.go = "VsD_Komendant_6";
			sld = CharacterFromID("Tichingitu");
			if (sld.location == pchar.location && !LAi_IsDead(sld))
			{
				LAi_SetOfficerType(sld);
				sld.Dialog.Filename = "Quest\Sharlie\Tichingitu.c";
				sld.Dialog.CurrentNode = "Tichingitu_officer";
			}
			if (GetCharacterIndex("Folke") != -1 && CheckPassengerInCharacter(pchar, "Folke"))
			{
				sld = CharacterFromID("Folke");
				ChangeCharacterAddressGroup(sld, "none", "", "");
				sld.Dialog.Filename = "Enc_Officer_dialog.c";
				sld.Dialog.CurrentNode = "hired";
			}
			else
			{
				sld = CharacterFromID("Alonso");
				ChangeCharacterAddressGroup(sld, "none", "", "");
			}
		break;
		
		case "VsD_Komendant_6":
			dialog.text = "En caso de que no lo hayas notado, el astillero está en llamas. Aún estamos determinando si fue intencionado o un resultado secundario de la explosión. Sólo puedo prometerte que tus heridos recibirán atención médica, y la Corona asumirá el costo de enterrar a los muertos.";
			link.l1 = "¿Hablas en serio? ¿Eso es lo mejor que puedes ofrecer?";
			link.l1.go = "VsD_Komendant_7";
			sld = CharacterFromID("VsD_Tsyganka");
			ChangeCharacterAddressGroup(sld, "PortPax_town", "reload", "reload5_back");
			LAi_CharacterEnableDialog(sld);
			LAi_SetActorType(sld);
			LAi_ActorFollow(sld, pchar, "", -1);
		break;
		
		case "VsD_Komendant_7":
			dialog.text = "Capitán, Francia necesita urgentemente su asistencia. Le proporcionaré maderas, y si juega bien sus cartas, su barco estará casi totalmente reparado para cuando llegue a Jamaica.";
			link.l1 = "Perdóneme, pero ¿qué tablas? ¿Y por qué Jamaica?";
			link.l1.go = "VsD_Komendant_8";
			pchar.ship.HP = sti(pchar.ship.HP) / 2;
			pchar.Ship.Crew.Quantity = sti(pchar.ship.Crew.Quantity) - sti(pchar.ship.Crew.Quantity) / 7;
			AddCharacterGoodsSimple(pchar, GOOD_PLANKS, 100);
		break;
		
		case "VsD_Komendant_8":
			dialog.text = "Tu tripulación puede realizar reparaciones de emergencia en el mar con las tablas, un material de reparación principal. Y Jamaica está bastante cerca de una de las rutas que puedes tomar hacia Portobello. Si no pierdes tiempo, puedes terminar las reparaciones y reclutar una tripulación completa allí.";
			link.l1 = "Muy bien, entonces. Zarparé de inmediato, Coronel.";
			link.l1.go = "VsD_Komendant_9";
			
			sld = CharacterFromID("PortRoyal_shipyarder");
			sld.TrialDelQuestMark = true;
			AddLandQuestMark(sld, "questmarkmain");
			AddMapQuestMarkCity("PortRoyal", false);
		break;
		
		case "VsD_Komendant_9":
			DialogExit();
			LAi_SetStayType(pchar);
			
			sld = CharacterFromID("VsD_Tsyganka");
			sld.dialog.filename = "Quest\Sharlie\OtherNPC.c";
			sld.dialog.currentnode = "VsD_Tsyganka";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", 3, 0);
			
			sld = CharacterFromID("PortPaxAmmoOff_clone");
			sld.lifeday = 0;
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "gate_back", "none", "", "", "", -1);
		break;
		
		case "VsD_Tsyganka":
			dialog.text = "¿Por qué tanta prisa, querido?";
			link.l1 = "Querido, no tengo tiempo para esto ahora. ¿No ves lo que está pasando?";
			link.l1.go = "VsD_Tsyganka_1";
		break;
		
		case "VsD_Tsyganka_1":
			dialog.text = "¡Oh, los problemas actuales son graves, pero puedo decir por tu mano que se avecinan más en el horizonte!";
			link.l1 = "Cualquiera puede ver eso incluso sin mirar mi mano, que debo añadir, está en un guante. Bien, seguiré el juego: ¿cuál es el precio por evitar el desastre en estos días?";
			link.l1.go = "VsD_Tsyganka_2";
		break;
		
		case "VsD_Tsyganka_2":
			dialog.text = "No tengo ese poder, guapo. Y aunque lo tuviera, no podría permitírmelo. Pero aún puedo ayudarte... con tu barco. La chica está en un estado lamentable, querido.";
			link.l1 = "Jamás he conocido a tu grupo gitano para tener ambiciones en carpintería.";
			link.l1.go = "VsD_Tsyganka_3";
			
			for (i=3; i<=8; i++)
			{				
				sld = CharacterFromID("VsD_MirnyeMan_"+i);
				LAi_SetCitizenType(sld);
			}
			for (i=3; i<=6; i++)
			{				
				sld = CharacterFromID("VsD_MirnyeWoman_"+i);
				LAi_SetCitizenType(sld);
			}
			for (i=1; i<=6; i++)
			{				
				sld = CharacterFromID("VsD_Sold_"+i);
				LAi_SetCitizenType(sld);
			}
			//Возвращаем всё обратно
			chrDisableReloadToLocation = false;
			bDisableFastReload = false;
			bDisableCharacterMenu = false;
			SetLocationCapturedState("PortPax_town", false);
			Locations[FindLocation("PortPax_town")].locators_radius.quest.quest1 = 1.0;
			Locations[FindLocation("PortPax_town")].locators_radius.patrol.patrol14 = 0.5;
			LocatorReloadEnterDisable("PortPax_ExitTown", "reload2_back", false);
			LocatorReloadEnterDisable("PortPax_ExitTown", "reload1_back", false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_town")], false);
			LAi_LocationFightDisable(&Locations[FindLocation("PortPax_Fort")], false);
			
			for (i=1; i<=5; i++)
			{
				sld = CharacterFromID("VsD_Guard_"+i);
				sld.lifeday = 0;
			}
			//Диего исчезает
			sld = CharacterFromID("Diego");
			LAi_CharacterEnableDialog(sld);
			sld.location = "None";
			//Верфь закрывается
			LocatorReloadEnterDisable("PortPax_Town", "reload5_back", true);
			SetTimerCondition("VsD_VerfOtkryt", 0, 0, 7, false);
			//Труп предателя в джунглях
			PChar.quest.VsD_TrupPredatelya.win_condition.l1 = "location";
			PChar.quest.VsD_TrupPredatelya.win_condition.l1.location = "PortPax_ExitTown";
			PChar.quest.VsD_TrupPredatelya.win_condition = "VsD_TrupPredatelya";
			SetTimerCondition("VsD_TrupPredatelya_3", 0, 0, 60, false);
		break;
		
		case "VsD_Tsyganka_3":
			dialog.text = "Querido, apenas eres un carpintero tú mismo. ¿Crees que solo las tablas repararán el barco? Solo te pesarán a menos que tengas un maestro carpintero...";
			link.l1 = "¿O?";
			link.l1.go = "VsD_Tsyganka_4";
		break;
		
		case "VsD_Tsyganka_4":
			dialog.text = "Hay un amuleto potente, reverenciado por los lugareños. La madera se dobla a su voluntad, e incluso aquellos que no están familiarizados con la carpintería se encuentran hábiles una vez que lo llevan. Es tuyo por solo mil pesos, querido.";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Muy bien, tienes un trato. Necesito toda la ayuda que pueda conseguir.";
				link.l1.go = "VsD_Tsyganka_Da";
			}
			link.l2 = "No tengo tiempo para tus brujerías. Ve en paz, bruja, y no te entrometas.";
			link.l2.go = "VsD_Tsyganka_Net";
			npchar.lifeday = 0;
		break;
		
		case "VsD_Tsyganka_Net":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Trial", "7_1");
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
		
		case "VsD_Tsyganka_Da":
			DialogExit();
			LAi_SetPlayerType(pchar);
			AddQuestRecord("Trial", "7_1");
			AddCharacterExpToSkill(pchar, "Repair", 20);
			AddMoneyToCharacter(pchar, -1000);
			GiveItem2Character(PChar, "obereg_1");
			Log_info("Has recibido el amuleto 'Teredo'.");
			LAi_SetCitizenType(npchar);
			LAi_CharacterDisableDialog(npchar);
		break;
		
		//замечание по обнажённому оружию от персонажей типа citizen
		case "CitizenNotBlade":
			dialog.text = NPCharSexPhrase(NPChar,"Escúchame, soy un ciudadano respetuoso de la ley de esta ciudad. Debo pedirte que no andes con tu espada desenvainada como un ladrón.","Señor, por favor, la ley es clara en que los hombres no pueden andar con armas desenvainadas dentro de los muros de la ciudad.");
			link.l1 = LinkRandPhrase("Está bien.","Bien.","Como desees...");
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
			if (npchar.id == "GigoloMan") NextDiag.TempNode = "GigoloMan";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
