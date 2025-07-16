// Абигайль Шнеур
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
			{
				if (pchar.questTemp.HWIC.Holl == "AbbyInHouse")
				{
					dialog.text = "Buen día, señor. ¿Qué os trae a nuestro hogar?";
					link.l1 = "Buen día, Abigail. Mi nombre es "+GetFullName(pchar)+". Soy un capitán que trabaja por el bien de la República y la Compañía Holandesa de las Indias Occidentales.";
					link.l1.go = "AbbyAndLucas";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyFindScull" && makeint(Pchar.money) >= 200000)
				{
					dialog.text = "¡Dios mío, encontraste el dinero de mi padre? ¿Es cierto? ¡Ah, estoy tan contento! Rápido, ve a mi padre, quiere hablar contigo. ¡Ve a verlo!";
					link.l1 = "Estoy en camino, madame.";
					link.l1.go = "exit";
					DelLandQuestMark(npchar);
					break;
				}
				if (pchar.questTemp.HWIC.Holl == "AbbyLeavesMarried")
				{
					dialog.text = "¡Nos has salvado de la desesperación total, capitán! ¡Te estoy tan agradecido! ¡Ahora el buen nombre de la familia Shneur puede ser restaurado!";
					link.l1 = "Simplemente cumpliendo con mi deber como caballero, madame. Espero que no haya nada que le impida casarse con mi patrón.";
					link.l1.go = "AbbyAndLucas_8";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "¿Necesita algo, capitán?";
				link.l1 = "Ahora no, señora.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Eng"))
			{
				if (pchar.questTemp.HWIC.Eng == "AbigileInChurch")
				{
					dialog.text = "Salve, Reina Santa, nuestra vida, nuestra dulzura y nuestra esperanza. A ti clamamos, pobres hijos desterrados de Eva. A ti enviamos nuestros suspiros, gimiendo y llorando en este valle de lágrimas... ¡oh señor, me asustaste! ¿Qué te trae por aquí?";
					link.l1 = "Le ruego que me disculpe, ¿Abigail, supongo? Richard Fleetwood me envió...";
					link.l1.go = "Seek_Island";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "¿Deseáis algo, capitán?";
				link.l1 = "No ahora, madame.";
				link.l1.go = "exit";
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Self"))
			{
				if (pchar.questTemp.HWIC.Self == "toVillemstad")
				{
					dialog.text = "¿Qué está pasando aquí? ¿Qué es este ruido? Papá, ¿quién es este hombre extraño?";
					link.l1 = "Buen día, señora. ¿Abigail Schneur, supongo? Me alegra verla. Debe perdonar mi impertinencia, pero tengo aquí una carta urgente dirigida a usted de... bueno, me encantaría decírselo, pero su querido padre se niega a permitirme siquiera entrar a su casa, y mucho menos entregar este mensaje para usted.";
					link.l1.go = "Abigile_kidnapping";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileNextDay")
				{
					dialog.text = "Ah, aquí estás Charles. ¡Estoy listo para seguirte a cualquier parte!";
					link.l1 = "Vamos entonces.";
					link.l1.go = "Abigile_kidnapping_7";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileInCabin")
				{
					dialog.text = "¿Estamos ya en San Juan, Charles? ¿Veré a Richard pronto?";
					link.l1 = "Sí, madame, estamos en St. John's. Desafortunadamente, Richard no está en la ciudad en este momento, fue ordenado a patrullar cerca de Barbados hace dos días. No se preocupe, debería regresar en una semana.";
					link.l1.go = "Abigile_kidnapping_8";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbigileLie")
				{
					dialog.text = "¡Charles! ¡Estoy tan contento de verte! ¿Alguna noticia de Richard?";
					link.l1 = "¡Ay, mi querida madame! Richard tuvo que quedarse en Bridgetown por un tiempo para una misión secreta e importante, tiene algo que ver con los holandeses. Supongo que Richard le ha contado a qué se dedica, ¿verdad?";
					link.l1.go = "Abigile_kidnapping_13";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbiReturnHome")
				{
					DelLandQuestMark(npchar);
					dialog.text = "¡Charles! ¡Eres tú! ¡Por fin has vuelto!";
					link.l1 = "Saludos, madame. Me alegra verte.";
					link.l1.go = "Abigile_return";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "AbiReturnHomeGo")
				{
					dialog.text = "¡Ah, por fin estoy en casa! ¡Estoy tan contento de ver a papá de nuevo! ¡Charles, gracias por todo lo que has hecho por mí!";
					link.l1 = "Por favor, no hay necesidad de hablar así, madame. Solo cumplo con mi deber como caballero para una dama en apuros.";
					link.l1.go = "Abigile_return_6";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryNext")
				{
					dialog.text = "¡Papá, si recuerdas algo, por favor dilo! Charles, él es... se puede confiar en él. Me atrevo a decir que es el único que puede ayudarnos!";
					link.l1 = "";
					link.l1.go = "Abigile_return_12";
					pchar.questTemp.HWIC.Self = "SolomonHistoryAfter";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "SolomonHistoryEnd")
				{
					dialog.text = "¡Rezaré por ti día y noche! Dime... dime que lo harás. ¡Que encontrarás la isla!";
					link.l1 = "Haré lo que pueda, madame.";
					link.l1.go = "Abigile_return_13";
					break;
				}
				if (pchar.questTemp.HWIC.Self == "final" || pchar.questTemp.HWIC.Self == "VanbergDestroyed")
				{
					DelLandQuestMark(npchar);
					dialog.text = "¡Ah, Charles! ¡Has vuelto! Dime rápido, ¿has encontrado la isla? ¡No puedo esperar más!";
					if (makeint(Pchar.money) >= 200000)
					{
						link.l1 = "Sí, Abi. He encontrado la isla y el dinero de tu padre. Estoy aquí para devolvértelo.";
						link.l1.go = "Abigile_GiveMoney";
					}
					link.l2 = "¡Ay, madame! No logré encontrar ni al capitán Keller ni vuestra isla. Hice lo que pude, pero...";
					link.l2.go = "Abigile_NoMoney";
				break;
				}
				dialog.text = "¡Ah, eres tú, Charles! ¿Necesitas algo? ¿Puedo ofrecerte un poco de café?";
				link.l1 = "No, nada. Por favor, no te molestes.";
				link.l1.go = "exit";
				break;
			}
			dialog.text = "Buen día, señor. ¿Qué desea?";
			link.l1 = "Nada, madame. Debo pedirle disculpas. Adiós.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;

		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;

//-------------------------------------------------за Голландию-----------------------------------------------
		case "AbbyAndLucas":
			dialog.text = "Es un honor conocerte, Capitán "+GetFullName(pchar)+". He oído todo tipo de historias sobre ti de las otras damas del pueblo. Eres el hombre que capturó el barco fantasma pirata y lo trajo como premio a Willemstad. Dime capitán... ¿es cierto que este barco estaba bajo el mando de... Richard Fleetwood?";
			link.l1 = "Todo lo que ha oído es cierto, madame. Me sorprendí tanto como cualquiera al descubrir la verdad. ¡Es un escándalo! ¡Un oficial naval de la Mancomunidad Inglesa saqueando a los comerciantes de su propia nación como un pirata común! Ese canalla intentó ocultar sus viles acciones fingiendo ser un 'barco fantasma' renegado respaldado por la Compañía Holandesa de las Indias Occidentales. Usó esta tapadera para culpar a la Compañía y atacar también a los barcos holandeses.";
			link.l1.go = "AbbyAndLucas_1";
		break;
		
		case "AbbyAndLucas_1":
			dialog.text = "Me da vueltas la cabeza... Es difícil escuchar cosas tan horribles, capitán. Conocía a Richard Fleetwood personalmente, nunca habría pensado que él...";
			link.l1 = "Madame, he sido informado por mi patrón Lucas Rodenburg sobre su viaje a Curazao desde Recife. Ahora está claro. Fleetwood hundió su barco y luego regresó para 'salvarlos' a usted y a su padre de quedar abandonados en esa isla perdida. Yo mismo leí el diario del pirata, registró cada detalle en su bitácora.";
			link.l1.go = "AbbyAndLucas_2";
		break;
		
		case "AbbyAndLucas_2":
			dialog.text = "Qué pesadilla... Parece que mi papá tenía razón después de todo. Me ha estado diciendo que Richard era ese pirata que era la fuente de toda nuestra desgracia. Debería estar contenta de que la verdad haya salido a la luz... ah, lo siento, capitán. Es simplemente demasiado para mi pobre cabeza... ¿qué quiere un hombre tan importante como usted de una chica común?";
			link.l1 = "Abigail, estoy aquí por un asunto muy complicado y delicado. ¿Me escucharás?";
			link.l1.go = "AbbyAndLucas_3";
		break;
		
		case "AbbyAndLucas_3":
			dialog.text = "Por supuesto, señor. Soy todo oídos.";
			link.l1 = "Como he dicho, sirvo a la Compañía. Lucas Rodenburg no solo es mi comandante militar, sino también un buen amigo. Me envió a ti con un mensaje. Sería la mayor felicidad para ti consentir en su propuesta de matrimonio. Estoy aquí para pedirte que te cases con mi patrón. Está dispuesto a hacer cualquier cosa en el mundo por tu felicidad.";
			link.l1.go = "AbbyAndLucas_4";
		break;
		
		case "AbbyAndLucas_4":
			dialog.text = "¡Oh, capitán! Ahora veo por qué el señor Rodenburg no estaba dispuesto a hacerlo él mismo... Mi pobre papá estaría encantado, pero yo...";
			link.l1 = "Madame, puedo ver que algo le preocupa. ¿Duda de la sinceridad de Mynheer Rodenburg? Quizás podría ayudarle a cambiar de opinión?";
			link.l1.go = "AbbyAndLucas_5";
		break;
		
		case "AbbyAndLucas_5":
			dialog.text = "¡Oh, no capitán, no tengo ninguna duda de la sinceridad de Mynheer Rodenburg! Lucas ha hecho tanto por mí y mi papá, no sé qué sería de nosotros si no estuviera cuidando de nosotros. ¡Pero por favor, debe entender mi posición! \nMi familia no es de los Rothchilds, pero nunca hemos sido pobres. La familia Shneur es bien conocida entre las casas bancarias de Europa por nuestra fortuna... ¡pero ahora este horrible pirata nos ha arruinado! No puedo soportar más este chisme desagradable que sé que ocurre a nuestras espaldas. Cada ama de casa charlatana y sirvienta de esta ciudad piensa que solo busco a Mynheer Rodenburg por su dinero. 'Qué típico de una judía', dicen. ¡Los crueles miserables! ¡Si tan solo mi padre recordara la ubicación de la isla! Allí guardó lo que queda de la fortuna de nuestra familia para salvarla de las manos de esos malvados piratas que asesinaron a mis hermanas y mi hermano! \n¡Pero mi pobre padre no es marinero, simplemente no puede recordar dónde está esa isla y el dinero de nuestra familia! ¡Por favor hable con mi padre, capitán! Tal vez pueda recordar algo que sea útil para sus sentidos experimentados. ¡Por favor encuentre esa isla y nuestra fortuna! ¡Habrá salvado a una pobre chica de la vergüenza y la ignominia!";
			link.l1 = "Muy bien, Abigail. Hablaré con tu padre. Ten fe, chica, haré lo que pueda.";
			link.l1.go = "AbbyAndLucas_6";
		break;
		
		case "AbbyAndLucas_6":
			dialog.text = "Gracias, señor. Rezaré por usted día y noche. ¡Que el Dios de nuestros padres esté con usted!";
			link.l1 = "Adiós, Abigail. Volveré con buenas noticias, lo juro.";
			link.l1.go = "AbbyAndLucas_7";
		break;
		
		case "AbbyAndLucas_7":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-27");
			pchar.questTemp.HWIC.Holl = "AbbyFather";
			AddLandQuestMark(characterFromId("Solomon"), "questmarkmain");
		break;
		
		case "AbbyAndLucas_8":
			dialog.text = "¡Oh, sí! Mynheer Rodenburg es un hombre honorable y amable. Le daré mi consentimiento sin vacilar y seré feliz de llamarlo mi esposo.";
			link.l1 = "Entonces considero que mi recado está completo. Debo ir ahora a Mynheer Rodenburg y contarle las buenas nuevas. Le deseo sinceramente felicidad, señora.";
			link.l1.go = "AbbyAndLucas_9";
		break;
		
		case "AbbyAndLucas_9":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "1-33");
			pchar.questTemp.HWIC.Holl = "AbbyAgreeMarried";//теперь к Лукасу
			AddLandQuestMark(characterFromId("Lucas"), "questmarkmain");
		break;
		
//-------------------------------------------------за Англию-----------------------------------------
		case "Seek_Island":
			dialog.text = "¿Richard te envió?! ¡Bendita María, gracias! ¡Ah, señor! He oído que el pobre Richard fue herido y está cerca de la muerte. ¿Es cierto? ¡Dime, ¿está vivo?! ¡¿Está sano?!";
			link.l1 = "Richard está vivo y... mayormente sano. Aquí están las malas noticias primero: está un poco deteriorado y ha quedado temporalmente ciego, pero se está recuperando. Ahora las buenas noticias: Richard quiere que zarpe con él hacia Inglaterra donde se casarán. Su tiempo en el Caribe ha terminado y está esperando tu respuesta.";
			link.l1.go = "Seek_Island_1";
		break;
		
		case "Seek_Island_1":
			dialog.text = "Ah, mi querido mensajero, dile a Richard que por nuestra felicidad estoy lista para ir con él a donde quiera. Pero temo que nuestra fuga matará a mi pobre padre... Señor, estoy desesperada y no sé qué hacer. Ojalá Richard pudiera encontrar esa maldita isla y el cofre con nuestro oro familiar... Tal vez eso de alguna manera consolaría a mi papá en mi ausencia.";
			link.l1 = "Ya veo... Mi misión era llevarte a Antigua, pero esto complica las cosas un poco. Si encontrara la isla y el cofre y te lo trajera, ¿vendrías entonces conmigo a San Juan y Richard?";
			link.l1.go = "Seek_Island_2";
		break;
		
		case "Seek_Island_2":
			dialog.text = "¡Oh sí, señor, lo recordaría en nuestras oraciones familiares! ¡Nombraría a nuestro primogénito en su honor! ¡Muchas gracias, capitán! ¡Rezaré por usted! ¡Vaya, y que Cristo y la Santísima Madre estén con usted!";
			link.l1 = "No te haré esperar mucho tiempo, madame. Regresaré pronto.";
			link.l1.go = "Seek_Island_3";
		break;
		
		case "Seek_Island_3":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "2-18");
			pchar.questTemp.HWIC.Eng = "SeekIsland";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "Villemstad_houseSp2_bedroom", "goto", "goto1", "", -1);//Аби домой
			pchar.questTemp.HWIC_Coordinates = "true"; //атрибут координат на поиск острова через каюту
			DelMapQuestMarkCity("Villemstad");
		break;
		
//--------------------------------------------против всех------------------------------------------------
		case "Abigile_kidnapping":
			dialog.text = "Oh... ¿Tienes una carta de él? ¡Oh papá, no seas tan duro con nuestros invitados! ¡Me avergüenzas con tus fantasías neuróticas! Mynheer, por favor, sígueme, quiero hablar contigo.";
			link.l1 = "Gracias, señorita. Me alegra ver a alguien en esta casa hablando con sentido.";
			link.l1.go = "Abigile_kidnapping_1";
		break;
		
		case "Abigile_kidnapping_1":
			DialogExit();
			npchar.greeting = "abigile_3";
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "Abigile_Stay", -1);
			NextDiag.CurrentNode = "Abigile_kidnapping_2";
			pchar.questTemp.HWIC.Self = "AbigileTalk";
			AddLandQuestMark(npchar, "questmarkmain");
		break;
		
		case "Abigile_kidnapping_2":
			DelLandQuestMark(npchar);
			dialog.text = "Perdona a mi padre, señor. En verdad es un hombre bueno y amable, pero nuestras...desgracias lo han quebrado.";
			link.l1 = "Está bien, señora, lo entiendo. Permítame presentarme, soy Charlie el... Knippel. Estoy aquí por orden de Richard Fleetwood, él quiere que le lleve a usted con él. Aquí, por favor, lea la carta.";
			link.l1.go = "Abigile_kidnapping_3";
		break;
		
		case "Abigile_kidnapping_3":
			RemoveItems(PChar, "NPC_Letter", 1);
			dialog.text = "Oh Richard...(leyendo). ¡Oh, Dios! ¡Ha decidido... devolverle a mi padre todo su dinero perdido! ¡Qué generosidad! ¡Querido, dulce Richard! ¡Mynheer, traes buenas noticias como el mismo Gabriel! Richard, ¿dónde está? ¿Está en Curazao?";
			link.l1 = "No, señorita. Hubo un intento de asesinato y ha sido gravemente herido. Ahora está en Antigua... no has terminado la carta.";
			link.l1.go = "Abigile_kidnapping_4";
		break;
		
		case "Abigile_kidnapping_4":
			dialog.text = "¡Santa María concebida sin pecado, ruega por nosotros que recurrimos a ti! Dime, ¿está a salvo? ¿Es grave su herida?";
			link.l1 = "¡No se preocupe así, señorita! Richard no es el tipo de hombre que dejaría que unos canallas lo mataran así como así. Ahora está descansando y recuperándose. Quiere que la lleve a él. Luego ustedes dos navegarán a Londres... por favor, termine la carta, señorita, se está adelantando.";
			link.l1.go = "Abigile_kidnapping_5";
		break;
		
		case "Abigile_kidnapping_5":
			dialog.text = "Ah, sí... lo siento (leyendo). Myheer Knippel, estoy listo para zarpar con usted. Necesito un día para empacar mis cosas y hablar con mi papá. Vuelva mañana y me iré con usted.";
			link.l1 = "Está bien, dama. Estaré aquí mañana. No te preocupes, mi tripulación y yo te protegeremos de cualquier peligro durante nuestro viaje.";
			link.l1.go = "Abigile_kidnapping_6";
		break;
		
		case "Abigile_kidnapping_6":
			DialogExit();
			npchar.greeting = "abigile_2";
			NextDiag.CurrentNode = "First time";
			AddQuestRecord("Holl_Gambit", "3-22");
			pchar.quest.Abigile_Kidnap.win_condition.l1 = "Timer";
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.hour  = 7.0;
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.day   = GetAddingDataDay(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l1.date.year  = GetAddingDataYear(0, 0, 1);
			pchar.quest.Abigile_Kidnap.win_condition.l2 = "location";
			pchar.quest.Abigile_Kidnap.win_condition.l2.location = "Villemstad_houseSp2";
			pchar.quest.Abigile_Kidnap.function = "AbigileGoToShip";
			pchar.questTemp.HWIC.Self = "AbigileWaitNextDay";
			SetFunctionTimerCondition("AbigileGoToShipOver", 0, 0, 3, false);//таймер 3 дня, ибо нефиг
		break;
		
		case "Abigile_kidnapping_7":
			DialogExit();
			chrDisableReloadToLocation = true;
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "SetAbigileToCabin", -1);//Аби в каюту к ГГ поставим
			AddQuestRecord("Holl_Gambit", "3-23");
			pchar.questTemp.HWIC.Self = "AbigileOnShip";
			pchar.quest.AbigileGoToShipOver.over = "yes";//снять таймер
			SetFunctionTimerCondition("RemoveAbigileOver", 0, 0, 30, false);//таймер на 1 месяц, ибо нефиг
			pchar.quest.Abigile_died.win_condition.l1 = "NPC_Death";
			pchar.quest.Abigile_died.win_condition.l1.character = "Abigile";
			pchar.quest.Abigile_died.function = "AbigileDied";//специально для особо упоротых
			AddMapQuestMarkCity("SentJons", false);
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Abigile_kidnapping_8":
			DelLandQuestMark(npchar);
			dialog.text = "Ah, qué lástima. Pero creo que puedo esperar una semana más, como he estado esperando antes...";
			link.l1 = "Bien dicho, señorita. Y para aliviar su espera, propongo cambiar esta cabina más bien austera por la casa de mi amigo. Allí habrá una cama suave y buena comida preparada para usted.";
			link.l1.go = "Abigile_kidnapping_9";
		break;
		
		case "Abigile_kidnapping_9":
			dialog.text = "Eres tan amable, Charlie. Gracias. Será bueno tener tierra bajo mis pies... Me siento bastante mareado después de tanto zarandearme en las olas.";
			link.l1 = "Sígame por favor, señorita.";
			link.l1.go = "Abigile_kidnapping_10";
		break;
		
		case "Abigile_kidnapping_10":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			pchar.questTemp.HWIC.Self = "AbigileInHouse";
			AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;
		
		case "Abigile_kidnapping_11":
			dialog.text = "¡Me alegra conocerte, John. Gracias por vuestra amable hospitalidad, caballeros!";
			link.l1 = "...";
			link.l1.go = "Abigile_kidnapping_12";
		break;
		
		case "Abigile_kidnapping_12":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload3", "SentJons_HouseF3_Room2", "barmen", "bar1", "ContinueWithMerdok", -1);
			pchar.questTemp.HWIC.Self = "AbigileInRoom";
			NextDiag.CurrentNode = "First time";
			RemovePassenger(Pchar, npchar);
			pchar.quest.RemoveAbigileOver.over = "yes";//снять таймер
			sld = characterFromId("Merdok");
			LAi_SetActorType(sld);//чтобы геймер сам с ним не заговорил
		break;
		
		case "Abigile_kidnapping_13":
			DelLandQuestMark(npchar);
			dialog.text = "¡Oh Charlie, he visto a Richard solo unas pocas veces y no me contó mucho sobre lo que hace!";
			link.l1 = "Me sorprende bastante que él ocultara un secreto tan grande a la mujer que ama... Señorita, Richard no es solo un capitán ordinario. También es un agente especial del Consejo Privado inglés. Un hombre muy importante que se ocupa de tareas delicadas ordenadas directamente por el mismo Lord Protector. En este momento, su deber se centra en destruir el poder comercial de la Compañía Holandesa de las Indias Occidentales en el Caribe.";
			link.l1.go = "Abigile_kidnapping_14"
		break;
		
		case "Abigile_kidnapping_14":
			dialog.text = "Señor, ¿de qué está hablando?";
			link.l1 = "Sí, señorita. Tu amado Richard - mi amigo - es un hombre muy importante. Siempre estuve orgulloso de ser su amigo, pero se ha vuelto muy reservado incluso conmigo. Es obvio que está en alguna misión secreta. Lamento mucho que esta misión no le permita verte.";
			link.l1.go = "Abigile_kidnapping_15";
		break;
		
		case "Abigile_kidnapping_15":
			dialog.text = "Charlie, me estás asustando. ¿Estás seguro de que él está bien?";
			link.l1 = "Estoy seguro de eso. Solo que... no apruebo cómo te está tratando ahora. Entiendo que su misión es vital y no puede traicionar su deber ni siquiera por ti.";
			link.l1.go = "Abigile_kidnapping_16";
		break;
		
		case "Abigile_kidnapping_16":
			dialog.text = "Oh, mi amable Charlie... Esperaré a Richard hasta la Segunda Venida si es necesario. Tal vez podría quedarme encima de la taberna... No puedo seguir aprovechándome de la hospitalidad de John por tanto tiempo.";
			link.l1 = "¡Deja de hablar tonterías, dama! Tu presencia nos honra y no me llamo Charlie el Knippel si echo a la prometida de mi novia de mi querido amigo Richard Fleetwood de casa y hogar!";
			link.l1.go = "Abigile_kidnapping_17";
		break;
		
		case "Abigile_kidnapping_17":
			dialog.text = "Charlie... Estoy muy conmovida por tu actitud hacia mí. Solo soy una chica común y una judía además...";
			link.l1 = "¡Señorita! Sé que eso es una locura, ¡eres una joven cristiana ejemplar! ¡Y ni se te ocurra pensar en tabernas! Nunca me perdonaría si te fallara en mi servicio a Richard.";
			link.l1.go = "Abigile_kidnapping_18";
		break;
		
		case "Abigile_kidnapping_18":
			dialog.text = "Gracias, Charlie. Me alegra que seas un... buen hombre.";
			link.l1 = "Es mi deber, señorita. Ahora lo lamento, pero debo irme. Ahora puede pasear libremente por el pueblo, debe sentirse bastante sola confinada en esta casa, ¿verdad?";
			link.l1.go = "Abigile_kidnapping_19";
		break;
		
		case "Abigile_kidnapping_19":
			dialog.text = "Bueno... John es una compañía muy interesante. Puede hablar de sus polvos, mezclas y varias... enfermedades durante horas. También es un hombre educado y cortés. Además, voy regularmente a la iglesia, el sacerdote es bastante amable... pero, por supuesto, realmente extraño a Richard.";
			link.l1 = "Creo que volverá pronto. Charlie el Knippel está a tu servicio en caso de que necesites algo.";
			link.l1.go = "Abigile_kidnapping_20";
		break;
		
		case "Abigile_kidnapping_20":
			DialogExit();
			pchar.questTemp.HWIC.Self = "MeetTonzag";
			pchar.quest.Meet_Tonzag.win_condition.l1 = "location";
			pchar.quest.Meet_Tonzag.win_condition.l1.location = "SentJons_TownCave";
			pchar.quest.Meet_Tonzag.function = "TonzagMeetingInDange";
		break;
		
		case "Abigile_return":
			dialog.text = "Escuché rumores sobre Richard... que ha desaparecido. ¿Sabes algo al respecto, Charlie?";
			link.l1 = "Lo hago, Abigail. Lo siento... Richard Fleetwood se ha ido a Inglaterra y no volverá. Obtuvo un ascenso o traslado, algo así... de todos modos, después de lo que te ha hecho, no quiero saber nada de él.";
			link.l1.go = "Abigile_return_1";
		break;
		
		case "Abigile_return_1":
			dialog.text = "Ah, sabía que terminaría así....(sollozos) ¡Por qué no escuché a papá! Al menos, él estaría contento si me hubiera casado con Lucas Rodenburg.";
			link.l1 = "Perdóname de nuevo, señorita...";
			link.l1.go = "Abigile_return_2";
		break;
		
		case "Abigile_return_2":
			dialog.text = "¿Por qué, Charlie?   No tienes ninguna culpa. ¡No has sido más que amable conmigo!";
			link.l1 = "Para mí, contarte aún más malas noticias. Acabo de regresar de Curazao, Lucas Rodenburg ha sido arrestado por sedición y traición contra la República. Está siendo enviado de regreso a Ámsterdam encadenado para ser juzgado. Intentó asesinar a Peter Stuyvesant, director de la Compañía. Además de eso, intentó derrocar al gobernador de Willemstad y es sospechoso del asesinato de al menos otra persona, así que dudo que el Stadtholder le dé una simple palmada en la muñeca.";
			link.l1.go = "Abigile_return_3";
		break;
		
		case "Abigile_return_3":
			dialog.text = "¡Oh Dios! ¡Qué pesadilla! ¡Creo que voy a desmayarme! Charles, ¿es cierto? No, por favor di que no lo es.";
			link.l1 = "Lo siento, señorita, empeora. Se ha revelado durante la investigación de las acciones de Rodenburg que el pirata que hundió tu fluyt actuaba bajo las órdenes de Lucas Rodenburg. Estaba librando su propia guerra privada contra la navegación inglesa. Lo siento mucho, Abigail. Todos los hombres que has enfrentado aquí en el Caribe han sido mentirosos, ladrones y asesinos.";
			link.l1.go = "Abigile_return_4";
		break;
		
		case "Abigile_return_4":
			dialog.text = "Oh... estoy arruinado. Charles... por favor... llévame de vuelta a casa a Willemstad. Necesito a mi papá...";
			link.l1 = "Por supuesto, querida señorita. Desafortunadamente, no hay nada para usted aquí en Bridgetown. Vaya, haga sus maletas, despídase de John y zarparemos de inmediato.";
			link.l1.go = "Abigile_return_5";
		break;
		
		case "Abigile_return_5":
			DialogExit();
			AddQuestRecord("Holl_Gambit", "3-57");
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "", -1);
			LocatorReloadEnterDisable("SentJons_HouseF3", "reload4", false);//откроем комнату Аби
			AddPassenger(pchar, npchar, false);
			SetCharacterRemovable(npchar, false);
			pchar.questTemp.HWIC.Self = "AbiReturnHomeGo";
			pchar.quest.AbiReturn_Home.win_condition.l1 = "location";
			pchar.quest.AbiReturn_Home.win_condition.l1.location = "Villemstad_town";
			pchar.quest.AbiReturn_Home.function = "AbiGoInVillemstad";
			AddMapQuestMarkCity("Villemstad", true);
		break;
		
		case "Abigile_return_6":
			dialog.text = "No, Charlie, necesito darte las gracias. Si no fueras tú y John, ni siquiera sé qué me habría pasado. Sois los únicos hombres honestos que he conocido en el archipiélago.";
			link.l1 = "Hum... me haces sonrojar, Abigail. Me alegró poder ayudarte. Y lamento mucho todo este lío.";
			link.l1.go = "Abigile_return_7";
		break;
		
		case "Abigile_return_7":
			dialog.text = "Sabes, Charlie, he estado pensando mucho durante nuestro viaje a Curazao. Todo está claro ahora - Richard Fleetwood, Mynheer Rodenburg - todo parece ser solo una horrible pesadilla que finalmente ha terminado. Estoy con mi padre de nuevo y podemos volver a una vida normal\nNo será fácil, sin embargo - no tenemos dinero. Pero lo superaremos, todo va a estar bien. La Bendita Madre cuidará de nosotros, nunca olvida a sus hijos, incluso a mi obstinado viejo padre que niega a Su Hijo.";
			link.l1 = "Señorita Abigail, voy a ayudarla.";
			link.l1.go = "Abigile_return_8";
		break;
		
		case "Abigile_return_8":
			dialog.text = "¿Ayudarnos? ¿Pero cómo, Charlie?";
			link.l1 = "Richard me contó la historia de tu naufragio y tu rescate. Además, sé que tu padre pudo esconder sus pertenencias en una isla desconocida. Voy a encontrarla y traer de vuelta tu dinero.";
			link.l1.go = "Abigile_return_9";
		break;
		
		case "Abigile_return_9":
			dialog.text = "Oh Charlie... Ni mi padre ni yo podemos decirte dónde está esa isla maldita... No somos marineros. Además, estaba aterrorizado por mi vida durante el ataque, no recuerdo nada aparte de sangre y el olor a muerte.";
			link.l1 = "Abigail, intenta recordar. Por favor, cualquier detalle puede ayudarme, incluso los más pequeños. ¿Tal vez sucedió algo antes del ataque? ¿Cómo es esta isla?";
			link.l1.go = "Abigile_return_10";
		break;
		
		case "Abigile_return_10":
			dialog.text = "¿Isla... Parece una isla? Una bahía, junglas. Nada realmente me llamó la atención. ¡Oh, recuerdo! Quizás te ayude. Poco antes del ataque pirata, nos encontramos con un fluyt y saludamos a su capitán. Fue invitado a nuestro barco y cenó con nuestro capitán. Nosotros también estábamos allí. Quizás él sepa sobre esta isla.";
			link.l1 = "¡Eso es algo! ¿Cuáles eran los nombres del fluyt y de su capitán?";
			link.l1.go = "Abigile_return_11";
		break;
		
		case "Abigile_return_11":
			dialog.text = "No recuerdo, Charlie. Realmente no...";
			link.l1 = "¡Intenta recordar, Abi!";
			link.l1.go = "Abigile_return_12";
			pchar.questTemp.HWIC.Self = "SolomonHistory";
		break;
		
		case "Abigile_return_12":
			DialogExit();
			sld = characterFromId("Solomon");
			sld.greeting = "solomon_1";
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		break;
		
		case "Abigile_return_13":
			dialog.text = "Te estaremos esperando. Ayúdame, Charlie el Knippel. Eres nuestra única esperanza... ¡Rezaré por ti! ¡Que Dios te acompañe!";
			link.l1 = "Estoy en camino. Adiós, Abi. Adiós, Solomon.";
			link.l1.go = "Abigile_return_14";
		break;
		
		case "Abigile_return_14":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload2", "Villemstad_houseSp2_bedroom", "goto", "goto1", "ReturnAbiNormal", -1);
			pchar.questTemp.HWIC.Self = "SeekFleut";
			AddQuestRecord("Holl_Gambit", "3-58");
			AddLandQuestMark(characterFromId("Villemstad_PortMan"), "questmarkmain");
		break;
		
		case "Abigile_NoMoney":
			dialog.text = "Oh, querido...qué lástima. Teníamos esperanzas, pero... gracias de todos modos, Charlie, por siquiera intentar ayudarnos cuando nadie más lo haría. Parece que este es el destino que Dios ha dispuesto para mí.";
			link.l1 = "Adiós, Abigail. Espero que estés bien.";
			link.l1.go = "exit";
			npchar.dialog.currentnode = "Abigile_Poor";
		break;
		
		case "Abigile_GiveMoney":
			dialog.text = "¿Es... es cierto? ¿De verdad nos has devuelto nuestro dinero perdido? ¡Oh, Charlie!";
			link.l1 = "Sí, es cierto. Lo tengo. Aquí, tómalo. Todo esto es tuyo.";
			link.l1.go = "Abigile_GiveMoney_1";
		break;
		
		case "Abigile_GiveMoney_1":
			AddMoneyToCharacter(pchar, -200000);
			pchar.quest.MakeAbiPoor.over = "yes"; //снять прерывание
			ChangeCharacterComplexReputation(pchar, "nobility", 10);
			dialog.text = "¿Cómo puedo agradecerte?! ¿Cómo?!";
			link.l1 = "No necesito agradecimientos, Abi. Es lo mínimo que podría hacer por ti. Ahora puedes comenzar una nueva vida sin que ningún Rodenburg, Fleetwood, u otro hombre extraño trate de aprovecharse de ti. Estoy seguro de que tu padre encontrará la manera de hacer que este dinero genere más dinero... parece ser un rasgo heredado.";
			link.l1.go = "Abigile_GiveMoney_2";
		break;
		
		case "Abigile_GiveMoney_2":
			dialog.text = "¡Charlie, no seas tan descarado! Has hecho tanto por mí, por mí y por mi pobre padre. ¿Sabes? Me he acostumbrado a tu presencia en mi vida. He estado rezando incansablemente por ti cada día, ¡y seguiré rezando por ti y tu tripulación a la Bendita Madre todos los días por venir! Eres nuestro ángel guardián. El Señor mismo te ha enviado a nuestra familia, lo creas o no\nAntes de que te vayas, quiero que sepas que las puertas de nuestra casa estarán siempre abiertas para ti en cualquier momento. Y... por favor, déjame besarte, mi querido Charlie...";
			link.l1 = "Bueno... sí, claro Abi... si insistes.";
			link.l1.go = "Abigile_GiveMoney_3";
		break;
		
		case "Abigile_GiveMoney_3":
			DialogExit();
			npchar.greeting = "abigile_1";
			npchar.dialog.currentnode = "Abigile_AllRight";
			
			StartQuestMovie(true, false, true);
			LAi_SetActorType(pchar);
			LAi_Fade("AbiKiss", "");
		break;
		
		case "Abigile_Poor":
			dialog.text = "Que Dios te bendiga, Charles. Nada ha cambiado para nosotros... Mendigo por sobras afuera de la iglesia.";
			link.l1 = "Mantente fuerte, señorita. Que Dios esté contigo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abigile_Poor";
		break;
		
		case "Abigile_AllRight":
			dialog.text = "¡Charles, eres tú! ¡Me alegra tanto verte! ¡Por favor, siéntate! ¡Voy a preparar café!";
			link.l1 = "Me alegra verte también, Abi. Y me alegra que estés bien.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Abigile_AllRight";
		break;
		
		//--> блок реагирования на попытку залезть в сундук
		case "Woman_FackYou":
			dialog.text = "¡Ah, ¿así que es eso?! ¡Te recibí como mi huésped y decidiste robarme?! ¡Guardias!!!";
			link.l1 = "Cierra la boca, chica tonta.";
			link.l1.go = "exit";
			LAi_group_Attack(NPChar, Pchar);
		break;
		//<-- блок реагирования на попытку залезть в сундук
	}
}
