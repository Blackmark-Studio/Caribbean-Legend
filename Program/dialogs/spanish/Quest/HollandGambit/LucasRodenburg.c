// Лукас Роденбург - вице-директор ГВИК
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		if (CheckAttribute(pchar, "questTemp.HWIC.CanTake") && !CheckAttribute(pchar, "questTemp.HWIC.CanTake.Holl"))
		{
			dialog.text = "Habla, muchacho, pero sé rápido. Soy un hombre ocupado.";
			link.l1 = "He oído que estás contratando capitanes.";
			link.l1.go = "Holl_start";
			break;
		}
		dialog.text = "¿Tienes algún negocio para mí?";
		link.l1 = "No, lo siento. Me voy.";
		link.l1.go = "exit";
		NextDiag.TempNode = "First time";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;

	case "Second_time":
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl"))
		{
			if (pchar.questTemp.HWIC.Holl == "BaltazarEsc")
			{
				dialog.text = "Se suponía que ya estarías a mitad de camino hacia Sint Maarten, kapitein.";
				link.l1 = "Me estoy preparando para zarpar, señor.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "BaltazarCom")
			{
				dialog.text = "¡Ah, capitán, ahí estás! No te vi venir, acabo de terminar de leer la carta de Ridderbrock. Causaste una gran impresión. Te llama 'el guardián de los mercaderes y azote de los piratas. ¡El regalo de Dios para la Compañía!' ¿Qué dices a eso?";
				link.l1 = "Preferiría seguir siendo solo un capitán ordinario. Un capitán ordinario pero rico.";
				link.l1.go = "SantiagoTrip";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripBegin")
			{
				dialog.text = "¿Por qué sigues aquí y no rumbo a Cuba?!";
				link.l1 = "Sí, sí, estoy en camino, mynheer.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripFinal")
			{
				sld = characterFromId("Santiago_usurer");
				dialog.text = "¡Ah, kapitein! Admito que empezaba a preocuparme. ¿Cómo te fue?";
				link.l1 = "No fue sin problemas, pero te contaré sobre eso más tarde. Primero, negocios. Señor " + GetFullName(sld) + " me dijo que te dijera lo siguiente: 'este hombre tiene que morir'. Entonces Geraldi considerará el incidente resuelto. Además, dijo que esta decisión es la voluntad de su familia.";
				link.l1.go = "SantiagoTrip_8";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "SantiagoTripComplete")
			{
				dialog.text = "¡Me alegra verte, kapitein! Es bueno que vinieras a verme.";
				link.l1 = "Buen día, señor. ¿Supongo que tiene otro trabajo de la Compañía para mí?";
				link.l1.go = "JacobBerg";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "JacobTakeShip")
			{
				if (sti(Pchar.Ship.Type) != SHIP_NOTUSED)
				{
					dialog.text = "He dicho que amarres tu barco. ¿Eres demasiado estúpido o ignorante para seguir órdenes directas?";
					link.l1 = "Ni uno ni otro, mynheer. Estoy en camino.";
					link.l1.go = "exit";
				}
				else
				{
					dialog.text = "Entonces, has amarrado tu barco. Ahora te prestaré mi jabeque. ¿Estás listo para comenzar esta misión de inmediato? Mi barco está bien equipado y listo para zarpar, así que no hay nada de qué preocuparse para ti.";
					link.l1 = "Sí, claro. Estoy listo, Mynheer Rodenburg.";
					link.l1.go = "JacobBerg_6";
					DelLandQuestMark(npchar);
				}
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "JacobLongway")
			{
				dialog.text = "¿Por qué sigues aquí? Ve a ver a Longway de inmediato.";
				link.l1 = "Lo siento, estoy en camino.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MirageTake") // а вот теперь начинается дурдом с перебором кораблей
			{
				int iMir = 0;
				int iMef = 0;
				for (i = 0; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE)
							iMir = 1;
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MAYFANG)
							iMef = 1;
					}
				} // установили признак наличия кораблей в эскадре.
				RemoveItems(PChar, "JacobJournal", 1);	   // удалим журнал ван Берга
				pchar.quest.MirageConvoyOver.over = "yes"; // снять таймер
				if (iMir == 1 && iMef == 0)				   // потеряли Мейфенг
				{
					dialog.text = "Kapitein... Ya estoy al tanto de tu viaje.";
					link.l1 = "¿Oh, de verdad? Entonces debes saber que...";
					link.l1.go = "Jacob_lostMef";
					DelLandQuestMark(npchar);
					break;
				}
				if (iMir == 0 && iMef == 1) // потеряли Мираж
				{
					dialog.text = "Kapitein... Ya estoy al tanto de tu viaje.";
					link.l1 = "¿Es eso así? Entonces debes saber que...";
					link.l1.go = "Jacob_lostMir";
					DelLandQuestMark(npchar);
					break;
				}
				if (iMir == 0 && iMef == 0) // а это вообще плохо
				{
					dialog.text = "Kapitein... Ya estoy al tanto de su travesía.";
					link.l1 = "¿Es así? Entonces debes saber que...";
					link.l1.go = "Jacob_failFull";
					DelLandQuestMark(npchar);
					break;
				}
				dialog.text = "Aquí estás, Kapitein... Ya sé todo sobre tu viaje.";
				link.l1 = "¿Es así? Entonces debes saber que...";
				link.l1.go = "Jacob_complete";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "toAntigua")
			{
				dialog.text = "Ve a Antigua. Ahora.";
				link.l1 = "Lo siento, estoy en camino.";
				link.l1.go = "exit";
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "FleetwoodSink" || pchar.questTemp.HWIC.Holl == "FleetwoodCapture")
			{ // опять начинаем проверять корабли
				iMir = 0;
				for (i = 0; i < COMPANION_MAX; i++)
				{
					iTemp = GetCompanionIndex(PChar, i);
					if (iTemp > 0)
					{
						sld = GetCharacter(iTemp);
						pchar.questTemp.HWIC.Holl.CompanionIndex = sld.Index;
						if (sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_MIRAGE)
							iMir = 1;
					}
				} // установили признак наличия Миража в эскадре.
				pchar.quest.ToAntiguaOver.over = "yes"; // снять таймер
				if (iMir == 0)							// потеряли Мираж
				{
					dialog.text = "Fui informado de tu llegada, kapitein. También sé que has perdido mi Mirage en batalla.";
					link.l1 = "Está bien informado, Mynheer Rodenburg. A pesar de todos mis esfuerzos, no pudimos salvarla.";
					link.l1.go = "Fleetwood_fail";
					DelLandQuestMark(npchar);
				}
				else
				{
					dialog.text = "Fui informado de tu llegada, kapitein. Veo que el Mirage está atracado de manera segura. Esto es bueno.";
					link.l1 = "Todo fue según sus instrucciones, mynheer. Me ordenó matar a Fleetwood y está muerto. Me ordenó traer el Mirage de vuelta al puerto y aquí está.";
					link.l1.go = "Fleetwood_complete";
					DelLandQuestMark(npchar);
				}
				pchar.quest.Meifeng_fail.over = "yes";
				Group_DeleteGroup("Meifeng_Empty");
				sld = characterFromId("MeifengCap");
				sld.lifeday = 0; // зачистим Мейфенг без китайца
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "Abby_prepare")
			{
				dialog.text = "Ah, aquí estás. Es bueno verte. Tengo otra misión para ti, tal como prometí.";
				link.l1 = "Estoy escuchando, señor.";
				link.l1.go = "Abby";
				DelLandQuestMark(npchar);
				break;
			}
			if (!CheckAttribute(pchar, "questTemp.HWIC.Holl.LucasMoney") && pchar.questTemp.HWIC.Holl == "AbbyAgreeMarried")
			{
				dialog.text = "Ah, me alegra verte, muchacho. Llegaste tarde y empecé a preocuparme. ¿Pudiste conseguir algo de Abigail?";
				link.l1 = "No solo eso, también he resuelto tus otros problemas. He encontrado la isla y la fortuna perdida de Shneur. Salomón está feliz y Abigail dirá que sí a tu propuesta. ¡Felicidades, mynheer!";
				link.l1.go = "Abby_2";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "NotFindAbbyIsland")
			{
				dialog.text = "Ah, me alegra verte, amigo mío. ¿Pudiste conseguir algo de Abigail?";
				link.l1 = "Sí. Hablé con Abigail y su padre. Hay un problema, señor: la fortuna perdida de su padre. Abigail se siente indigna de ti, teme los chismes y rumores de la gente si ella, como una chica sin dote, se casara con un caballero como tú. Espero que lo entiendas.";
				link.l1.go = "Abby_6";
				DelLandQuestMark(npchar);
				break;
			}
			if (CheckAttribute(pchar, "questTemp.HWIC.Holl.LucasMoney") && pchar.questTemp.HWIC.Holl == "AbbyAgreeMarried")
			{
				dialog.text = "¡Ah, mi amigo! ¿Confío en que traes buenas noticias?";
				link.l1 = "Tu plan fue exitoso. Abigail dirá que sí. Felicitaciones, mynheer.";
				link.l1.go = "Abby_8";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MerdokStart")
			{
				dialog.text = "Te he estado esperando. Muchacho, estás en grave peligro.";
				link.l1 = "¿Qué quieres decir?";
				link.l1.go = "Merdok";
				DelLandQuestMark(npchar);
				break;
			}
			if (pchar.questTemp.HWIC.Holl == "MerdokDie")
			{
				dialog.text = "Mis agentes en el muelle me dijeron que habías llegado. ¿Está muerto Johan van Merden?";
				link.l1 = "Sí. Él y su cómplice se han ido. Fue una pelea dura, pero la superé.";
				link.l1.go = "Merdok_4";
				DelLandQuestMark(npchar);
				break;
			}
			dialog.text = "No tenemos nada más que discutir, kapitein.";
			link.l1 = "Entendido, me voy.";
			link.l1.go = "exit";
			break;
		}
		dialog.text = "¿Qué es? El tiempo es oro.";
		link.l1 = "Lo siento, me voy.";
		link.l1.go = "exit";
		break;

		//------------------------------------------------1 задание--------------------------------------------
	case "Holl_start":
		DelLandQuestMark(npchar);
		DelLandQuestMark(characterFromId("Bridgetown_tavernkeeper"));
		DelLandQuestMark(characterFromId("Knippel"));
		DelMapQuestMarkCity("Bridgetown");
		DelMapQuestMarkCity("Villemstad");
		DelMapQuestMarkCity("SentJons");
		dialog.text = "Tal vez. ¿Quién eres? Habla rápido, el tiempo es dinero.";
		link.l1 = "Soy capitán " + pchar.name + ", mi barco y  pueden ser útiles para ti.";
		link.l1.go = "Holl_start_0";
		break;

	case "Holl_start_0":
		dialog.text = "Hm, una aleación desconocida para ser ensayada en el crisol.";
		link.l1 = "Por eso estoy aquí, mynheer.";
		link.l1.go = "Holl_start_1";
		break;

	case "Holl_start_1":
		pchar.questTemp.HWIC.Holl.PirateName = "l" + rand(GetNamesCount(NAMETYPE_ORIG) - 1);
		dialog.text = "Muy bien, veremos de qué estás hecho. Bien, Kapetein como te llames, ¿conoces a Balthazar Ridderbrock? ¿No? Qué afortunado. Idiotas tan codiciosos, gruñones y de mal genio como él son una rara visión.\nPero parece que tales cualidades sobresalientes no fueron suficientes para el hombre, así que fue lo suficientemente inteligente como para ofender a un filibustero llamado " + GetName(NAMETYPE_ORIG, pchar.questTemp.HWIC.Holl.PirateName, NAME_NOM) + " en la taberna y llamó a la guardia en el mismo momento en que la parte ofendida tocó una espada...";
		link.l1 = "...¿y colgaron al pirata con la primera cuerda libre?";
		link.l1.go = "Holl_start_2";
		break;

	case "Holl_start_2":
		dialog.text = "No es tan sencillo. " + GetName(NAMETYPE_ORIG, pchar.questTemp.HWIC.Holl.PirateName, NAME_NOM) + " no es un pirata común, sino un corsario holandés, un veterano de las dos últimas guerras con los británicos. Los contribuyentes locales le tienen bastante aprecio. No puedo decir lo mismo de Ridderbrock.";
		link.l1 = "¿Así que nuestro corsario sigue vivo?";
		link.l1.go = "Holl_start_3";
		break;

	case "Holl_start_3":
		dialog.text = "Sí, pero está realmente enfadado. Por eso Ridderbrock está cagado de miedo.";
		link.l1 = "Supongo que mi buena fortuna está a punto de terminar. ¿Cuándo me encontraré con Mynheer Ridderbrock?";
		link.l1.go = "Holl_start_4";
		break;

	case "Holl_start_4":
		dialog.text = "Inminentemente. La buena gente de Philipsburg está esperando un cargamento de azúcar, uno que nuestro conocido mutuo Ridderbrock prometió entregar. No considero que el hombre valga el cuero de sus botas, pero ay, trabaja para nosotros, así que ve al despacho del puerto. Encuentra a Ridderbrock allí y dile que le ordené zarpar de inmediato.\nLo seguirás, y... lo escoltarás a Philipsburg en una pieza. No quiero " + GetName(NAMETYPE_ORIG, pchar.questTemp.HWIC.Holl.PirateName, NAME_NOM) + "  enviar la reputación de la Compañía al fondo del Caribe junto con su carga.";
		link.l1 = "Uf, una misión de escolta. ¿Qué hay del pago por esta...desagradable tarea?";
		link.l1.go = "Holl_start_5";
		break;

	case "Holl_start_5":
		dialog.text = "Kapitein, haz el trabajo primero. Balthazar te pagará en cuanto llegue a su destino. ¡En Philipsburg! ¡No en el Casillero de Davy Jones! Después, infórmame una vez que el trabajo esté hecho. Si tienes éxito, podrás contar con mi patrocinio y el de la Compañía. Despedido.";
		link.l1 = "Nos vemos, mynheer.";
		link.l1.go = "exit";
		AddDialogExitQuestFunction("Create_Baltazar");
		pchar.questTemp.HWIC.Holl = "BaltazarEsc";
		NextDiag.TempNode = "Second_time";
		pchar.quest.HWIC_ReturnOfficer.over = "yes"; // чтобы офицер не доставал
		pchar.questTemp.HWIC.CanTake.Holl = "true";	 // признак, что голландка уже бралась
		break;

		//----------------------------------------------задание 1а--------------------------------------------
	case "SantiagoTrip":
		dialog.text = "Sí, Ridderbrock es un avaro hijo de puta, incluso para un compañero holandés. Sea como sea, ya no es asunto mío. Hablemos de ti, Kapitein Como Te Llames. Me gusta tu estilo, así que voy a ofrecerte otro trabajo. Esta vez lo pagaré yo mismo.";
		link.l1 = "Estoy escuchando, mynheer.";
		link.l1.go = "SantiagoTrip_1";
		AddSimpleRumourCity("Ah, ¿así que tú eres el valiente kapitein que escoltó a ese canalla de Ridderbrock? Nos enteramos de todo... ¡Te pagó sólo cinco mil pesos! Ha estado presumiendo de ello sin parar en la taberna de Philipsburg borracho como una cuba. Si yo fuera su capitán, lo sacaría a la calle y le daría una paliza.", "Villemstad", 20, 3, ""); // слух по 1 заданию
		break;

	case "SantiagoTrip_1":
		dialog.text = "Necesito un hombre para un asunto muy importante. Hiciste bien con el caso Ridderbrock, así que la Compañía cree que puedo confiarte esto.";
		link.l1 = "Supongo que me siento honrado. ¿Qué ocurre?";
		link.l1.go = "SantiagoTrip_2";
		break;

	case "SantiagoTrip_2":
		sld = characterFromId("Santiago_usurer");
		dialog.text = "No puedo darte detalles exactos, pero ten en cuenta que esto no es mi trabajo, es de la Compañía, así que tienes una oportunidad de caer en nuestras buenas gracias, lo cual te aseguro es muy rentable.\nNavega a Santiago en Cuba y entrega este paquete a Don " + GetFullName(sld) + ". Tiene un alto cargo en el banco de Geraldi y también es mi... nuestro socio comercial. Debes entregarle este oro que te daré ahora mismo. Confío en tu honestidad, kapitein. Bueno, si no en tu honestidad, al menos en tu instinto de supervivencia. La Compañía siempre encuentra a aquellos que intentan robarnos.";
		link.l1 = "¿Dudas de mí, mynheer?";
		link.l1.go = "SantiagoTrip_3";
		break;

	case "SantiagoTrip_3":
		if (pchar.BaseNation == ENGLAND || pchar.BaseNation == FRANCE)
			sTemp = " También te concedo esta licencia comercial de la Compañía a corto plazo para evitarle cualquier enredo diplomático con los españoles. Esto le permitirá atracar en colonias españolas durante algún tiempo.";
		else
			sTemp = "";
		dialog.text = "Por el momento, no te dudo. Créeme, ni siquiera hablaría contigo sobre este asunto si lo hiciera. Sepas que hemos perdido mucho tiempo organizando este trabajo, así que solo tienes quince días para entregar." + sTemp + "\nMi mensaje y paquete deben ser entregados a tiempo. Esto es vital, muchacho. Date prisa, pero ten cuidado, esto no va a ser un simple recado.";
		link.l1 = "¿Algo más? ¿Por qué me adviertes, mynheer Rodenburg?";
		link.l1.go = "SantiagoTrip_4";
		break;

	case "SantiagoTrip_4":
		if (pchar.BaseNation == ENGLAND || pchar.BaseNation == FRANCE)
			GiveNationLicence(HOLLAND, 20);
		dialog.text = "Digamos que tengo mis sospechas. No te preocupes, si lo haces tan rápido como la última vez, entonces tendrás la oportunidad de convertirte en un agente valioso para los asuntos delicados de la Compañía.";
		link.l1 = "¿Todo lo que tengo que hacer es entregar este carta y dinero al banquero en Santiago en quince días? No parece demasiado difícil a primera vista.";
		link.l1.go = "SantiagoTrip_5";
		break;

	case "SantiagoTrip_5":
		dialog.text = "No tan rápido, muchacho... Me parece que no comprendes realmente la gravedad de esta situación. Hacer este trabajo me hará sentir muy agradecido contigo. Por otro lado, fallarlo me hará muy enfadado. En ese caso, entonces me mearé sobre ti. ¿Nos entendemos, kapitein?" + GetFullName(pchar) + "?";
		link.l1 = "Entendido. Tienes mi palabra. Haré lo mejor que pueda para mantenerte de buen humor.";
		link.l1.go = "SantiagoTrip_6";
		break;

	case "SantiagoTrip_6":
		dialog.text = "Muy bien. Ahora, toma la carta, estos cofres y recuerda los términos y condiciones. Y una cosa más: mantente alejado de problemas en Santiago.";
		link.l1 = "Muy bien.";
		link.l1.go = "SantiagoTrip_7";
		break;

	case "SantiagoTrip_7":
		DialogExit();
		GiveItem2Character(pchar, "NPC_Letter");
		ChangeItemDescribe("NPC_Letter", "itmdescr_NPC_Letter4");
		TakeNItems(pchar, "chest", 5);
		if (bImCasual)
		{
			NewGameTip("Modo exploración: se duplica la duración de las misiones");
			SetFunctionTimerCondition("SantiagoTripOver", 0, 0, 32, false);
		}
		else
			SetFunctionTimerCondition("SantiagoTripOver", 0, 0, 16, false); // таймер
		AddQuestRecord("Holl_Gambit", "1-43");
		pchar.questTemp.HWIC.Holl = "SantiagoTripBegin";
		AddMapQuestMarkCity("Santiago", true);
		AddLandQuestMark(characterFromId("Santiago_usurer"), "questmarkmain");
		break;

	case "SantiagoTrip_8":
		dialog.text = "'Tiene que morir'... así nada más. No esperaba eso. Hm. Has hecho bien tu trabajo, kapitein. Ahora dame un informe.";
		link.l1 = "Nada especial... fue un paseo por el parque.";
		link.l1.go = "SantiagoTrip_9";
		link.l2 = "Me sorprendió y secuestró un hombre en Santiago. Estaba muy interesado en tus asuntos con Geraldi. Logré escapar, pero primero tuve que matarlo. La única pista que dejó caer fue el nombre de un tal Gastón. No tengo ni idea de qué se trataba todo esto.";
		link.l2.go = "SantiagoTrip_10";
		link.l3 = "Me quedé atónito y fui secuestrado por un hombre en Santiago. Estaba muy interesado en tu negocio con Geraldi. Logré escapar, pero primero tuve que matarlo. No pude averiguar nada de él antes de enviarlo al infierno.";
		link.l3.go = "SantiagoTrip_11";
		break;

	case "SantiagoTrip_9":
		dialog.text = "La gratitud de la Compañía no se limita a meras palabras. Toma tu recompensa, te la has ganado.";
		link.l1 = "Trabajar para la Compañía es bastante rentable.";
		link.l1.go = "SantiagoTrip_12";
		break;

	case "SantiagoTrip_10":
		dialog.text = "¡Qué! Secuestro... Espera, aunque... ¡Gaston! Entiendo... Creo. Ay, muchacho, te han arrastrado a un asunto sórdido. Estamos en aguas desconocidas, así que tendremos que ver cómo se desarrolla. Me alegra que hayas llegado con vida.\nHablemos de cosas más agradables: acepta esta recompensa, bien merecida.";
		link.l1 = "Trabajar para la Compañía es bastante lucrativo";
		link.l1.go = "SantiagoTrip_12";
		break;

	case "SantiagoTrip_11":
		dialog.text = "¡Tonterías! Secuestrarte... aunque tengo algunas sospechas. Aprenderás más si continúas trabajando para mí. Tienes suerte y me alegra que lo hayas logrado.\nHablemos de cosas más agradables - acepta esta recompensa, bien merecida.";
		link.l1 = "Trabajar para la Compañía es bastante lucrativo";
		link.l1.go = "SantiagoTrip_12";
		break;

	case "SantiagoTrip_12":
		AddMoneyToCharacter(pchar, 25000);
		dialog.text = "¡Exactamente, muchacho! Puedes convertirte en un agente bien remunerado de la Compañía si seguimos trabajando juntos. Ahora ve, descansa de tu viaje. Has estado a la altura de mis expectativas. Te estaría muy agradecido si volvieras en una semana, aún nos queda mucho trabajo por hacer.";
		link.l1 = "Puedes contar conmigo, Mynheer Rodenburg.";
		link.l1.go = "SantiagoTrip_13";
		break;

	case "SantiagoTrip_13":
		DialogExit();
		pchar.questTemp.HWIC.Holl = "true";
		AddQuestRecord("Holl_Gambit", "1-46");
		AddCharacterExpToSkill(pchar, "Sailing", 100); // навигация
		AddCharacterExpToSkill(pchar, "Sneak", 100);   // скрытность
		AddCharacterExpToSkill(pchar, "Leadership", 80);
		AddSimpleRumourCity("Mi hermano de la Compañía dice que Mynheer Rodenburg está muy satisfecho con tu actuación, kapitein. No pierdas tu oportunidad, Lucas rara vez muestra tal favor.", "Villemstad", 10, 3, "");
		SetTimerFunction("GollandGambit_2_ZadanieStart", 0, 0, 7);
		break;

		//-----------------------------------------------2 задание--------------------------------------------
	case "JacobBerg":
		dialog.text = "Eres inteligente, capitán. Exactamente. Bueno, hablemos de los detalles de la próxima misión...";
		link.l1 = "Soy todo oídos.";
		link.l1.go = "JacobBerg_1";
		break;

	case "JacobBerg_1":
		dialog.text = "Tengo una misión muy seria e importante para ti y espero que hagas todo según mis instrucciones. Como sabes, la relación entre las Provincias Unidas e Inglaterra no es... cordial. Los británicos están seguros de que son ellos quienes deberían gobernar el mundo. El problema es que no todos tienden a estar de acuerdo con tal afirmación. Dondequiera que naveguen para hacer negocios, ten por seguro que la Compañía Holandesa de las Indias Occidentales ha llegado allí primero. Nosotros, los holandeses, tenemos la flota comercial más grande del mundo y nuestros escuadrones militares pueden defender los intereses de la República tanto aquí como en el extranjero. Los ingleses nos envidian por nuestro poder comercial y están haciendo lo que pueden para sabotear las actividades de la Compañía. Ahora, hay un cierto capitán de la marina inglesa llamado Richard Fleetwood. A pesar de ser un oficial comisionado de la Commonwealth, actualmente opera como pirata. Ataca y saquea cualquier barco que se atreva a navegar bajo la bandera holandesa en el Caribe. Explica sus acciones como medidas contra el 'barco fantasma' que hunde a los comerciantes ingleses. Afirma que este 'barco fantasma' es un corsario que navega bajo una patente de corso holandesa.\n¿Has oído hablar del 'barco fantasma', kapitein?";
		link.l1 = "Puedes escuchar ese tipo de tonterías en cualquier taberna. Solo compra un poco de ron para un viejo contramaestre y escucharás cualquier historia que desees...";
		link.l1.go = "JacobBerg_2";
		break;

	case "JacobBerg_2":
		dialog.text = "Este asunto no es una fantasía de borracho. He investigado las acciones de este 'barco fantasma'. Descubrí que es un barco de madera y lona tripulado por hombres comunes, un queche llamado 'Espejismo'. Está bajo el mando de un hombre llamado Jacob van Berg, quien la hace pasar por el legendario 'Holandés Errante'.";
		link.l1 = "¿Van Berg? Ese es un apellido holandés. ¿Un auténtico 'Holandés Errante', eh?";
		link.l1.go = "JacobBerg_3";
		break;

	case "JacobBerg_3":
		dialog.text = "Correcto. Jacob van Berg es un holandés, originario de Leiden. Pero la República lo sentenció a la horca hace mucho tiempo. Es un criminal fugitivo, un pirata que actúa solo por sus propios intereses. Richard Fleetwood está cazando a van Berg. Este hecho lo usaremos contra ese insolente inglés.\nPreferiría no matar a Fleetwood de inmediato, aunque se lo merecía hace mucho tiempo. La muerte no sería suficiente para él. Quiero no solo matarlo, sino también destruir su nombre y honor. Eso es lo que quiero. Eso también le enseñará una lección a otros cerdos ingleses arrogantes.\nHablemos de los detalles.";
		link.l1 = "Mynheer, esto empieza a sonar como algo personal...";
		link.l1.go = "JacobBerg_4";
		break;

	case "JacobBerg_4":
		dialog.text = "Eso no es de tu incumbencia. Seguirás órdenes, luego te pagarán. He descubierto dónde se esconde Jacob van Berg con su 'Mirage', gracias a mi agente. Opera desde una ciudad en la costa sur de España. Ve a él y averigua dónde ancló su barco fantasma. Luego mátalo, encuentra su 'Mirage', tómala como premio y tráela de vuelta aquí. Debes capturar la 'Mirage', ni siquiera pienses en hundirla.";
		link.l1 = "Parece bastante sencillo. ¿Dónde debería buscar a van Berg?";
		link.l1.go = "JacobBerg_5";
		break;

	case "JacobBerg_5":
		dialog.text = "Todos los detalles le serán proporcionados por mi agente. Su nombre es Longway, un chino. Le estoy proporcionando mi barco personal, el xebec 'Meifeng' para esta misión. Longway es su kapitein, pero tomará órdenes de usted.\nVaya a la oficina del puerto y amarre todos sus barcos allí. Regrese a mí una vez que esté hecho.";
		link.l1 = "Está bien, visitaré al maestro de puerto. No te haré esperar demasiado.";
		link.l1.go = "exit";
		pchar.questTemp.HWIC.Holl = "JacobTakeShip";
		AddLandQuestMark(characterFromId("Villemstad_portman"), "questmarkmain");
		break;

	case "JacobBerg_6":
		dialog.text = "Longway te espera afuera. Te mostrará tu nuevo barco y te dará información sobre la ubicación de van Berg. Buena suerte, kapitein, y no me decepciones. Recuerda que debes devolverme el 'Meifeng', así que intenta no hundirla mientras tomas el 'Mirage'.";
		link.l1 = "¡En camino!";
		link.l1.go = "JacobBerg_7";
		break;

	case "JacobBerg_7":
		DialogExit();
		pchar.quest.Create_Longway.win_condition.l1 = "location";
		pchar.quest.Create_Longway.win_condition.l1.location = "Villemstad_town";
		pchar.quest.Create_Longway.function = "Create_Longway";
		pchar.questTemp.HWIC.Holl = "JacobLongway";
		AddQuestRecord("Holl_Gambit", "1-7");
		pchar.questTemp.HWIC.TakeQuestShip = "true";	  // все ПУ недоступны для стоянки до поры, также корабль нельзя продать
		pchar.questTemp.HWIC.HollEquip = "true";		  // форма солдат
		DeleteAttribute(pchar, "questTemp.HWIC.CanTake"); // иные варианты более невозможны
		break;

	// дурдом продолжается
	case "Jacob_lostMir":
		dialog.text = "Eres un necio incompetente. Has fallado en tu misión de capturar el navío pirata. Todos mis planes están arruinados. Te quito 'Meifeng'. Lárgate, ya no te necesitamos.";
		link.l1 = "Lo siento. Adiós, señor Rodenburg.";
		link.l1.go = "Jacob_RemoveShip";
		pchar.questTemp.HWIC.Holl.ShipType = SHIP_MAYFANG;
		break;

	case "Jacob_lostMef":
		dialog.text = "Eres un idiota balbuceante. Has perdido el 'Meifeng'. Esto es inaceptable... Te quitaré el 'Mirage' y retendré tu pago como compensación por mi pérdida. Lárgate, ya no te necesitamos.";
		link.l1 = "Lo siento. Adiós, Señor Rodenburg.";
		link.l1.go = "Jacob_RemoveShip";
		pchar.questTemp.HWIC.Holl.ShipType = SHIP_MIRAGE;
		break;

	case "Jacob_failFull":
		dialog.text = "¡Dios mío, eres realmente un espécimen raro. Un inepto torpe Y un idiota. No lograste capturar el Mirage y perdiste el Meifeng junto con él. ¡Sal de mi oficina, maldita sea!";
		link.l1 = "Me voy.";
		link.l1.go = "exit";
		Pchar.questTemp.FiringOfficerIDX = GetCharacterIndex("Longway");
		AddDialogExitQuestFunction("LandEnc_OfficerFired"); // Лонгвэя из офицеров
		pchar.questTemp.HWIC.Holl = "end";
		CloseQuestHeader("Holl_Gambit");
		DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip"); // ПУ откроем
		DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
		pchar.questTemp.HWIC.Detector = "holl_fail";
		break;

	case "Jacob_complete":
		dialog.text = "Bien hecho. La noticia de tu éxito ya ha llegado a mis oídos. Van Berg está muerto y capturaste su barco. Tu pago es de 50,000 pesos, tómalo.\nEstoy recuperando el 'Meifeng' de ti. Ahora es el momento de que tomes el mando del 'Mirage', jugará un papel importante en la siguiente etapa. ¿Estás listo?";
		link.l1 = "Sí, Mynheer Rodenburg.";
		link.l1.go = "Fleetwood";
		pchar.questTemp.HWIC.Holl.ShipType = SHIP_MAYFANG;
		AddDialogExitQuestFunction("Jacob_RemoveShip");
		AddSimpleRumourCity("Dicen que estás en una misión especial para el mismísimo Mynheer Rodenburg. Algo sobre enviar a esos ingleses al fondo del mar. Parece que eres un hombre en ascenso, kapitein.", "Villemstad", 15, 3, "");
		break;

	case "Jacob_RemoveShip":
		DialogExit();
		AddDialogExitQuestFunction("Jacob_RemoveShip");
		sld = characterFromId("Longway");
		sld.lifeday = 0;
		pchar.questTemp.HWIC.Holl = "end";
		CloseQuestHeader("Holl_Gambit");
		DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip"); // ПУ откроем
		DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
		pchar.questTemp.HWIC.Detector = "holl_fail";
		AddSimpleRumourCity("Dicen que le has fallado al mismísimo Mynheer Rodenburg. Buena suerte, la necesitarás.", "Villemstad", 20, 3, "");
		break;

		//----------------------------------------------3 задание-------------------------------------------------

	case "Fleetwood":
		AddMoneyToCharacter(pchar, 50000);
		dialog.text = "Ahora nos ocupamos de Fleetwood. Vas a atraerlo usando el 'barco fantasma' Mirage que ha estado cazando con tanto entusiasmo. Coloca una trampa cerca de Dominica, el Mirage servirá como cebo.\nPrimero, harás saber a Fleetwood que el Mirage fue visto no muy lejos de Dominica. Nuestro valiente inglés dejará todo lo que esté haciendo y se apresurará inmediatamente a Dominica en busca de su presa. No hables con Fleetwood directamente o no sobrevivirás al encuentro. Encuentra la farmacia en St. John's. El boticario John Murdock es un viejo amigo mío.\nDile que actúas bajo mi mando y él te ayudará a encontrar oídos locales para llenar con jugosas mentiras sobre el 'barco fantasma' atacando a los mercaderes ingleses alrededor de Dominica.";
		link.l1 = "Puedo hacer eso. El objetivo es emboscar a Fleetwood en Dominica, ¿verdad?";
		link.l1.go = "Fleetwood_1";
		break;

	case "Fleetwood_1":
		dialog.text = "Exactamente. Longway y 'Meifeng' te esperarán cerca de Dominica. Los dos podréis encargaros fácilmente del perro inglés. Aborda su barco y registra su camarote. Quiero su cuaderno de bitácora. Pagaré extra por él.\nPero tu prioridad principal es matar a ese bastardo de Fleetwood, así que si abordarlo es poco práctico, mándalo al fondo del mar. Por encima de todo, debes preservar el 'Mirage' a toda costa. Ella tiene un papel crítico en la siguiente etapa del plan.";
		link.l1 = "Entendido.";
		link.l1.go = "Fleetwood_2";
		break;

	case "Fleetwood_2":
		dialog.text = "Un consejo, kapitein. No eches ancla en St. John's. Desembarca en una de las bahías de la isla y camina hacia la ciudad a través de la jungla, de lo contrario Juan no hablará contigo. Si llamas demasiado la atención, fingirá que no te conoce. Además, ten cuidado en el mar - el 'Mirage' es famoso entre las colonias inglesas, así que evita sus barcos de guerra y asentamientos si no quieres que una manada de lobos marinos te asedie. Eso es todo. Que Dios esté contigo.";
		link.l1 = "¡Aye aye!";
		link.l1.go = "Fleetwood_3";
		break;

	case "Fleetwood_3":
		DialogExit();
		pchar.questTemp.HWIC.Holl = "toAntigua";
		AddQuestRecord("Holl_Gambit", "1-15");
		DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
		SetFunctionTimerCondition("ToAntiguaOver", 0, 0, 60, false); // таймер 2 месяца
		AddMapQuestMarkShore("Shore1", false);
		AddMapQuestMarkShore("Shore2", false);
		AddLandQuestMark(characterFromId("Merdok"), "questmarkmain");
		break;

	case "Fleetwood_complete":
		if (pchar.questTemp.HWIC.Holl == "FleetwoodSink") // Флитвуд утоп с журналом
		{
			dialog.text = "Has regresado, kapitein... ¿Tienes el diario de Richard Fleetwood?";
			link.l1 = "Desafortunadamente no. No tuve oportunidad de abordar su barco antes de que él lo echara a pique.";
			link.l1.go = "Fleetwood_complete_1";
			break;
		}
		if (!CheckCharacterItem(pchar, "FleetwoodJournal"))
		{
			dialog.text = "Has regresado, kapitein... ¿Tienes el cuaderno de bitácora de Richard Fleetwood?";
			link.l1 = "Lamentablemente, no lo hice. Logré abordar el Valkyrie y matar al hombre en combate cuerpo a cuerpo, pero no encontré su diario. Uno de sus hombres disparó al polvorín y solo tuvimos segundos para escapar con vida.";
			link.l1.go = "Fleetwood_complete_1";
			break;
		}
		dialog.text = "Has regresado, kapitein... ¿Tienes el cuaderno de bitácora de Richard Fleetwood?";
		link.l1 = "Lo hice. Aquí está. Me las arreglé para abordar el Valkyrie, aunque fue una cosa muy ajustada. El bastardo disparó su polvorín y su barco voló por los aires. Apenas escapamos con vida.";
		link.l1.go = "Fleetwood_complete_2";
		break;

	case "Fleetwood_complete_1":
		AddMoneyToCharacter(pchar, 100000);
		dialog.text = "Eso es una maldita pena, habría respondido muchas preguntas que tenemos. Ahora no importa. Mataste a ese perro inglés insolente y eso es lo que más importa. Aquí está tu recompensa: 100,000 pesos. Te quito el 'Mirage', vamos a devolver este barco a Inglaterra.";
		link.l1 = "¡Qué demonios! Es un buen barco, ¡quería conservarlo!";
		link.l1.go = "Fleetwood_complete_3";
		break;

	case "Fleetwood_complete_2":
		AddMoneyToCharacter(pchar, 150000);
		RemoveItems(PChar, "FleetwoodJournal", 1);
		dialog.text = "¡Excelente! Eres un hombre muy capaz. Si todos nuestros capitanes fueran como tú, la República Holandesa sería la primera entre las más grandes naciones marítimas de la historia. Aquí tienes tu recompensa: 100,000 pesos y 50,000 pesos extra por el cuaderno de bitácora. Estoy tomando el 'Mirage' de ti, vamos a devolver este barco a Inglaterra.";
		link.l1 = "¡¿Qué demonios?! Es un buen barco, ¡quería quedármelo!";
		link.l1.go = "Fleetwood_complete_3";
		break;

	case "Fleetwood_complete_3":
		dialog.text = "Mi chico, eres un excelente soldado, pero confía en mí y en mi experiencia en asuntos de política. ¿Recuerdas lo que dije sobre Fleetwood? Voy a clavar su nombre y reputación a una piedra de molino y lanzarla a las profundidades. Y estos nobles arrogantes de Port Royal tendrán que tragar y ahogarse.\nVamos a hacer de Richard Fleetwood el capitán de la 'nave fantasma' Mirage, un hombre lobo que juega con las dos naciones de Inglaterra y los Países Bajos entre sí, saqueando, pillando y asesinando a ciudadanos pacíficos de ambas solo para enriquecerse él mismo. ¡Qué farsa! Ya he preparado pruebas y testigos, pero el 'Mirage' servirá como el evento principal de mi obra perfecta.";
		link.l1 = "Pues que me jodan entonces. ¡¿Vas a sacrificar mi excelente barco por tu plan!?";
		link.l1.go = "Fleetwood_complete_4";
		AddDialogExitQuestFunction("Lucas_ExangeShip");
		break;

	case "Fleetwood_complete_4":
		dialog.text = "Cuida tu lengua, muchacho, esto es guerra. A veces debemos sacrificar no solo hombres, sino también barcos y asentamientos ricos para lograr nuestros objetivos políticos. Toda guerra trae pérdidas... Hablando de pérdidas, tengo malas noticias para ti.\nMientras estabas fuera, Willemstad fue atacada por corsarios ingleses. El fuerte logró ahuyentarlos, pero no antes de que llegaran al puerto con barcos incendiarios.\nTu barco fue atrapado en ancla y quemado hasta la línea de flotación. Es una pérdida total.";
		link.l1 = "Mynheer, tienes que estar malditamente bromeando conmigo ahora. ¡Maldita sea todo al infierno! ¿Qué haré ahora?!";
		link.l1.go = "Fleetwood_complete_5";
		break;

	case "Fleetwood_complete_5":
		dialog.text = "No te enfades tanto, kapitein, también tengo buenas noticias. Para aliviar tu indignación, te entrego mi Viento Hermoso, el jabeque 'Meifeng'. Eres libre de usar el barco como desees, dentro de lo razonable. Además, encuéntrame mañana en la residencia del gobernador, has sido nominado para un premio estatal con el agradecimiento de la República Holandesa y la Compañía de las Indias Occidentales. No te vayas de la ciudad hasta que lo recibas, kapitein.";
		link.l1 = "Eso sí que alivia un poco el golpe de mis pérdidas. Estoy honrado. Por cierto, señor, ¿dónde se ha ido Longway?";
		link.l1.go = "Fleetwood_complete_6";
		break;

	case "Fleetwood_complete_6":
		dialog.text = "Longway desapareció repentinamente justo después de que le ordené navegar a Dominica. Tengo sospechas de que agentes ingleses lo han atacado... o quizás no. Estoy investigando.";
		link.l1 = "Ya veo. Su ayuda en Dominica habría sido muy bienvenida. Fleetwood y su 'Valkerie' eran una pareja temible. Espero que Longway aún esté vivo... ¡Tot zeins, mynheer!";
		link.l1.go = "Fleetwood_complete_7";
		pchar.questTemp.HWIC.Holl = "Award";
		AddQuestRecord("Holl_Gambit", "1-24");
		LocatorReloadEnterDisable("Villemstad_town", "reload1_back", true);
		LocatorReloadEnterDisable("Villemstad_town", "reload2_back", true);
		LocatorReloadEnterDisable("Villemstad_town", "gate_back", true);
		break;

	case "Fleetwood_complete_7":
		DialogExit();
		pchar.quest.Award_FromLucas.win_condition.l1 = "Timer";
		pchar.quest.Award_FromLucas.win_condition.l1.date.hour = 8.00;
		pchar.quest.Award_FromLucas.win_condition.l1.date.day = GetAddingDataDay(0, 0, 1);
		pchar.quest.Award_FromLucas.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 1);
		pchar.quest.Award_FromLucas.win_condition.l1.date.year = GetAddingDataYear(0, 0, 1);
		pchar.quest.Award_FromLucas.win_condition.l2 = "location";
		pchar.quest.Award_FromLucas.win_condition.l2.location = "Villemstad_townhall";
		pchar.quest.Award_FromLucas.function = "AwardFromFromLucas";
		AddSimpleRumour("Dígame capitán, ¿fue realmente ese maldito perro inglés Fleetwood el responsable del saqueo de mercaderes ingleses 'y' holandeses? ¿De verdad? ¡Un evasor tan astuto! Es bueno que haya eliminado a este bastardo. ¡Usted es un verdadero héroe, capitán!", HOLLAND, 10, 3);
		break;

	case "Fleetwood_fail":
		dialog.text = "No eres solo un payaso cualquiera, eres todo el circo. Estábamos tan cerca del acto final y lo echaste a perder... Te pagaré 30,000 pesos por la eliminación de Fleetwood. No tengo más misiones para ti y nuestro acuerdo ha terminado. Lárgate.";
		link.l1 = "Como desees.";
		link.l1.go = "Fleetwood_fail_1";
		break;

	case "Fleetwood_fail_1":
		AddMoneyToCharacter(pchar, 30000);
		dialog.text = "Tengo malas noticias para ti.\nMientras estabas fuera, Willemstad fue atacada por corsarios ingleses. El fuerte logró ahuyentarlos, pero no antes de que entraran en el puerto con barcos incendiarios.\nTu barco fue atrapado al ancla y quemado hasta la línea de flotación. Es una pérdida total.";
		link.l1 = "¡Supongo que entonces me iré a la mierda yo mismo! ¡Gracias por nada!";
		link.l1.go = "exit";
		DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip"); // можно пользоваться ПУ
		DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
		CloseQuestHeader("Holl_Gambit");
		pchar.questTemp.HWIC.Holl = "end";
		pchar.questTemp.HWIC.Detector = "holl_fail";
		AddSimpleRumour("Dígame, capitán, ¿es cierto que ha hundido a ese maldito perro inglés Fleetwood? ¿Es cierto? Es bueno que haya eliminado a este bastardo. ¡Hizo bien, capitán!", HOLLAND, 15, 3);
		break;

	case "LucasAward":
		dialog.text = "Kapitein " + GetFullName(pchar) + "¡Por eliminar a Richard Fleetwood, un peligroso criminal del estado, por exponer la traicionera conspiración inglesa contra la República, por su valentía y coraje, se le otorgan mil doblones de oro en nombre de la República Holandesa!\nTambién recibirá esta valiosa herramienta de navegación, el sueño de cualquier marinero militar.";
		link.l1 = "¡Estoy feliz de servir a la República!";
		link.l1.go = "LucasAward_1";
		break;

	case "LucasAward_1":
		DialogExit();
		LAi_SetPlayerType(pchar);
		sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
		LAi_SetActorType(sld);
		sld.Dialog.Filename = "Quest\HollandGambit\OtherNPC.c";
		sld.dialog.currentnode = "Bek_7";
		LAi_ActorDialog(sld, pchar, "", -1, 0);
		ChangeCharacterComplexReputation(pchar, "nobility", 10);
		GiveItem2Character(pchar, "bussol");
		break;

	case "LucasAward_2":
		dialog.text = "Felicidades de nuevo, mi amigo. Y por favor, visítame en una semana. Te necesitamos para un asunto sumamente delicado.";
		link.l1 = "Entendido, Mynheer Rodenburg. Lo visitaré en una semana.";
		link.l1.go = "LucasAward_3";
		break;

	case "LucasAward_3": // наведем порядок
		LAi_SetActorType(pchar);
		DialogExit();
		AddQuestRecord("Holl_Gambit", "1-25");
		sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
		LAi_ActorGoToLocator(sld, "goto", "goto6", "BekSitDown", -1);
		for (i = 1; i <= 3; i++)
		{
			sld = characterFromId("LucasGuard_" + i);
			sld.lifeday = 0; // подчистим солдат
		}
		sld = characterFromId("Lucas");
		LAi_ActorGoToLocator(sld, "reload", "reload1", "LucasReturnInCabinet", -1);
		bDisableFastReload = true;
		LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
		LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
		LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
		SetTimerFunction("GollandGambit_4_ZadanieStart", 0, 0, 7);
		AddSimpleRumourCity("Dicen que el mismísimo Matias Beck te concedió un premio estatal. ¡La República debería estar orgullosa de tener gente como tú, kapetein!", "Villemstad", 20, 4, "");
		break;

		//--------------------------------------------------4 задание----------------------------------------------

	case "Abby":
		dialog.text = "Déjame contarte una historia. Te ayudará a entender cuán delicada es tu próxima tarea. Hace unos meses, un fluyt que navegaba con la bandera inglesa rumbo a Willemstad fue atacado por el difunto Jacob van Berg. Se apoderó del barco y lo hundió no lejos de una isla que no aparece en ninguno de nuestros mapas. Solo dos de los pasajeros del fluyt sobrevivieron. Un judío llamado Solomon Shneur y su hija Abigail. Todos los demás pasajeros perecieron, incluyendo al resto de su familia. Nuestros dos judíos llegaron a la isla flotando en algunos restos. Solomon incluso logró arrastrar un cofre lleno del oro de la familia con ellos. Muy ahorrativo de su parte. Otro personaje de nuestra historia, Richard Fleetwood, navegaba cerca y escuchó los sonidos de la batalla. Llegó demasiado tarde para atrapar a van Berg, y el 'Mirage' huyó. Fleetwood decidió revisar la isla en busca de sobrevivientes. Salvó a Solomon y Abigail de una muerte segura en esa isla desierta. Desafortunadamente para el viejo judío, Solomon no tiene ojo de marinero. Confundió la 'Valkerie' de Richard con el 'Mirage' de Jacob y, aterrorizado de que el pirata regresara para terminar el trabajo, escondió su oro en algún lugar de la isla. Como resultado, él y su hija llegaron aquí sin un centavo, dejados por Fleetwood en la Laguna Blanca, cerca de Willemstad, su destino original. Solomon me contó esta historia. La República Holandesa apoya la práctica libre de la religión. Como parte de esa política, la Compañía apoya a la comunidad judía aquí. Por lo tanto, me aseguré de que tengan un techo sobre sus cabezas, y cosas para comer y vestir. Visité su lugar mucho. Abigail es una... joven extraordinaria. Sincera y confiada. No te mentiré, capitán, la quiero y tengo la intención de hacerla mi esposa. Ella me ama a cambio, pero algo se ha interpuesto entre nosotros.";
		link.l1 = "¿Su padre no está muy entusiasmado con un yerno goyim?";
		link.l1.go = "Abby_0";
		break;

	case "Abby_0":
		dialog.text = "¡Ja! El viejo Salomón estaría en el séptimo cielo si me casara con Abigail, yerno incircunciso o no. De hecho, él la empuja a aceptar mi propuesta. No, no, esto es algo que va más allá de judíos y gentiles. Te pido, muchacho, que resuelvas este problema por mí. Habla con Abigail y averigua qué está mal\nEres un extraño, podría decirte cosas que nunca contaría a gente familiar debido a su encantadora modestia. La casa de Shneur está ubicada a la derecha de la oficina de la compañía, si te paras de espaldas a ella. Sé que eres un hábil conversador\nPero recuerda una cosa: Richard Fleetwood fue el verdadero capitán del 'barco fantasma'... Tenlo en cuenta mientras hablas con Abigail.";
		link.l1 = "¡Ja! Claro que recuerdo eso, Mynheer Rodenburg. ¿No es eso el hecho oficialmente reconocido después de todo? No perderé tiempo entonces, iré a visitar a tu amado inmediatamente.";
		link.l1.go = "Abby_1";
		break;

	case "Abby_1":
		LocatorReloadEnterDisable("Villemstad_town", "houseSP2", false); // откроем дом Аби
		DialogExit();
		pchar.questTemp.HWIC.Holl = "AbbyInHouse";
		AddQuestRecord("Holl_Gambit", "1-26");
		AddLandQuestMark(characterFromId("Abigile"), "questmarkmain");
		break;

	case "Abby_2":
		dialog.text = "¿De verdad has encontrado la isla donde Salomón escondió su oro? ¡Esto es excelente! Empezaba a pensar que eres capaz de realizar cualquier tarea... ¿Has encontrado algo más en el escondite?";
		if (CheckAttribute(pchar, "questTemp.HWIC.Holl.ScullnotReturn"))
		{
			link.l1 = "No, nada más. Sólo dinero.";
			link.l1.go = "Abby_3";
		}
		else
		{
			link.l1 = "Había un artículo interesante: una calavera de jade. Se la di a Salomón, él dijo que era una reliquia familiar. También dijo que planeabas comprársela...";
			link.l1.go = "Abby_4";
		}
		break;

	case "Abby_3":
		pchar.questTemp.HWIC.Holl.LucasItem = "obereg_11";
		dialog.text = "Mm. Está bien entonces. Sin embargo, es bastante extraño. Como sea... Le debo, señor, y nunca lo olvidaré. He preparado una recompensa para usted - 50,000 pesos y este amuleto. Ahora es suyo.";
		link.l1 = "¡Gracias, señor Rodenburg!";
		link.l1.go = "Abby_5";
		break;

	case "Abby_4":
		pchar.questTemp.HWIC.Holl.LucasItem = "totem_04";
		dialog.text = "¡Excelente! Sí, voy a comprar este artefacto de Salomón, él no lo necesita y tengo un comprador muy generoso para él. He preparado una recompensa para ti: 50,000 pesos y este amuleto. Ahora es tuyo.";
		link.l1 = "¡Gracias, señor Rodenburg!";
		link.l1.go = "Abby_5";
		break;

	case "Abby_5":
		dialog.text = "No tengo ningún trabajo digno de un kapitein como tú en este momento. Pero no dejes Curazao por mucho tiempo, pronto necesitaré de tus servicios nuevamente.";
		link.l1 = "Lo tengo, mynheer. ¡Adiós!";
		link.l1.go = "exit";
		GiveItem2Character(pchar, pchar.questTemp.HWIC.Holl.LucasItem);
		AddMoneyToCharacter(pchar, 50000);
		pchar.quest.Merdok_prepare.win_condition.l1 = "Timer";
		pchar.quest.Merdok_prepare.win_condition.l1.date.hour = sti(GetTime());
		pchar.quest.Merdok_prepare.win_condition.l1.date.day = GetAddingDataDay(0, 0, 10);
		pchar.quest.Merdok_prepare.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 10);
		pchar.quest.Merdok_prepare.win_condition.l1.date.year = GetAddingDataYear(0, 0, 10);
		pchar.quest.Merdok_prepare.win_condition.l2 = "location";
		pchar.quest.Merdok_prepare.win_condition.l2.location = "Villemstad_town";
		pchar.quest.Merdok_prepare.function = "GiveTaskMerdok";
		pchar.questTemp.HWIC.Holl = "Merdok_wait";
		AddQuestRecord("Holl_Gambit", "1-34");
		DelMapQuestMarkCity("Villemstad");
		SetTimerFunction("GollandGambit_5_ZadanieStart", 0, 0, 10);
		AddSimpleRumourCity("¿Has oído las últimas noticias? Mynheer Rodenburg se va a casar con Abigail Shneur, la hermosa hija del viejo judío loco Salomón. Qué puedo decir, ella es una chica con suerte. Si Dios quiere, ¡será bautizada como una verdadera cristiana antes de la boda!", "Villemstad", 20, 3, "");
		break;

	case "Abby_6":
		dialog.text = "Ja, ¿y eso es todo? Patentemente absurdo... ¡cómo una mujer! Escucha, muchacho, este problema puede resolverse fácilmente. Sé cuánto dinero había en el escondite de Salomón: 200,000 pesos. Estoy dispuesto a destinar esta suma para mi felicidad y la de Abigail. Te daré el dinero y te irás de Curazao por una o dos semanas. Luego regresarás a Salomón y le darás el dinero. Finge que has encontrado el escondite. El lobo estará saciado y las ovejas intactas. Aquí, toma la suma requerida.";
		link.l1 = "Un plan bueno y sencillo. Hagámoslo.";
		link.l1.go = "Abby_7";
		break;

	case "Abby_7":
		dialog.text = "Navega hacia el mar abierto y regresa a mí en diez días. Haz algo productivo. Busca la Manga Rosa, fabrica algunos materiales, o algo así.";
		link.l1 = "Lo que usted diga, Mynheer Rodenburg.";
		link.l1.go = "exit";
		AddMoneyToCharacter(pchar, 200000);
		pchar.questTemp.HWIC.Holl = "GiveLucasMoney";
		SaveCurrentQuestDateParam("questTemp.HWIC.Holl.LucasMoney");
		pchar.questTemp.HWIC.Holl.LucasMoney = "true";
		AddQuestRecord("Holl_Gambit", "1-35");
		break;

	case "Abby_8":
		pchar.questTemp.HWIC.Holl.LucasItem = "obereg_11";
		dialog.text = "¡Espléndido! Una vez más, hiciste el trabajo a la perfección. Te debo una, mynheer, y nunca lo olvidaré. He preparado una recompensa para ti: 50,000 pesos y este amuleto. Ahora es tuyo.";
		link.l1 = "¡Gracias, Mynheer Rodenburg!";
		link.l1.go = "Abby_5";
		break;

		//-------------------------------------------5 задание-------------------------------------------------
	case "Merdok":
		dialog.text = "Sí, exactamente así. Mi amigo, a veces es difícil ver quién es tu amigo y quién es tu enemigo. A veces te pierdes el momento en que tu asociado más cercano se convierte en tu némesis. Nuestro conocido mutuo de St John's John Murdock - también conocido como Johan van Merden - es un ex-agente de la Compañía que se ha vendido a la Armada Inglesa.\nSu más reciente misión es eliminar una de las estrellas más brillantes de la Compañía... tú.";
		link.l1 = "Me halaga. Me alegra que me lo hayas dicho, de lo contrario no habría visto esto venir.";
		link.l1.go = "Merdok_1";
		break;

	case "Merdok_1":
		dialog.text = "Precisamente, kapitein. Es un perro astuto. Encuentra al bastardo y mátalo antes de que ataque. Navega a Antigua y busca una entrada secreta a su botica. Hay una trampilla frente a la iglesia que conduce a un túnel secreto. Úsala.";
		link.l1 = "Me encargaré de ello.";
		link.l1.go = "Merdok_2";
		break;

	case "Merdok_2":
		dialog.text = "Una cosa más, kapitein. Una vez que Johan esté muerto, registra su cadáver, la casa y el sótano. Tiene un archivo, un grueso libro de cuentas donde anotaba algunas notas condenatorias durante su trabajo para la Compañía. Esta información nos destruirá a todos si nuestros enemigos la encuentran.\nEncuentra ese maldito archivo y entrégamelo, te pagaré extra por ello. Ahora ve. Que Dios te acompañe, Kapitein " + pchar.name + ", y trata de volver en una pieza. ¡La República te necesita!";
		link.l1 = "¡Te prometo, mynheer, regresar entero. Eso es, sin duda, lo que más me conviene!";
		link.l1.go = "Merdok_3";
		break;

	case "Merdok_3":
		DialogExit();
		pchar.questTemp.HWIC.Holl = "KillMerdok";
		AddQuestRecord("Holl_Gambit", "1-42");
		LocatorReloadEnterDisable("Villemstad_town", "reload1_back", false);
		LocatorReloadEnterDisable("Villemstad_town", "reload2_back", false);
		LocatorReloadEnterDisable("Villemstad_town", "gate_back", false);
		bDisableFastReload = false;
		LocatorReloadEnterDisable("SentJons_HouseF3", "reload2", false);	   // откроем проход в подземелье из дома
		LocatorReloadEnterDisable("SentJons_TownCave", "reload1_back", false); // откроем проход в дом из подземелья
		LocatorReloadEnterDisable("SentJons_town", "HouseF3", true);		   // аптеку закроем
		pchar.quest.Merdok_inCave.win_condition.l1 = "location";
		pchar.quest.Merdok_inCave.win_condition.l1.location = "SentJons_TownCave";
		pchar.quest.Merdok_inCave.function = "MerdokInUndergroundCave";
		LAi_LocationDisableOfficersGen("SentJons_TownCave", true); // офицеров в шахту не пускать
		DelMapQuestMarkCity("Villemstad");
		AddMapQuestMarkCity("SentJons", false);
		break;

	case "Merdok_4":
		dialog.text = "¡Excelente, capitán! Me alegra, de verdad. ¿Encontraste su archivo?";
		if (CheckCharacterItem(pchar, "MerdokArchive")) // архив
		{
			link.l1 = "Sí, aquí está. No había otros documentos en el cadáver del químico ni en sus cofres.";
			link.l1.go = "Merdok_book";
		}
		link.l2 = "No. Lo busqué por todas partes pero no encontré nada.";
		link.l2.go = "Merdok_5";
		DeleteAttribute("SentJons_TownCave", "box2"); // если не нашли шифр - уже и не найдем
		break;

	case "Merdok_5":
		dialog.text = "Eso es una pena, sin duda, pero a mí me da igual. Estoy seguro de que Johan no tuvo tiempo suficiente para entregárselo a los ingleses, de lo contrario ya tendríamos la soga al cuello... Es probable que lo escondiera en algún escondite secreto... ¡que se quede allí para siempre! ¡Te felicito, kapitein, por la exitosa conclusión de nuestra misión!";
		link.l1 = "¡Gratitud!";
		link.l1.go = "Merdok_6";

		SetTimerCondition("PZ_LigaInJungle", 0, 0, 7, false); // проверку не прошёл, значит нападёт Лига через неделю, после чего начнётся таймер на 30 дней 1 этапа
		break;

	case "Merdok_book":
		dialog.text = "¡Espléndido! Ahora está a salvo donde pertenece. Has demostrado que eres el mejor una vez más... Dame el libro... Hay una recompensa por el archivo: este fino mosquete. Me ha servido con gran distinción y ahora es tuyo.";
		link.l1 = "";
		if (CheckAttribute(pchar, "questTemp.PZ_RodenburgUkradenaStranitsa"))
		{
			link.l1.go = "Merdok_book_2";
		}
		else
		{
			link.l1.go = "Merdok_book_6";
		}
		RemoveItems(PChar, "MerdokArchive", 1);
		break;

	case "Merdok_book_2":
		dialog.text = "¿Cuál es tu juego, Capitán? Faltan varias páginas, páginas que son muy importantes para mí. ¿Pensaste que no lo notaría para que pudieras usarlas contra mí? ¿O esperabas sacar más provecho de ello? Me temo que tengo que decepcionarte en ambos aspectos.";
		if (IsCharacterPerkOn(pchar, "Trustworthy"))
		{
			notification("Trustworthy", "Trustworthy");
			link.l1 = "(Digno de confianza) Me disculpo. Mi único error fue no haber revisado el archivo yo mismo de antemano.";
			link.l1.go = "VD_Merdok_book_3";
			SetTimerCondition("PZ_Etap1_Start", 0, 0, 30, false); // 1 этап стартует через 30 дней
		}
		else
		{
			notification("Perk check failed", "Trustworthy");
			link.l1 = "¿Realmente arrancaría las páginas y luego entregaría el archivo con una mirada despreocupada?";
			link.l1.go = "Merdok_book_3";
			SetTimerCondition("PZ_LigaInJungle", 0, 0, 7, false); // проверку не прошёл, значит нападёт Лига через неделю, после чего начнётся таймер на 30 дней 1 этапа
		}
		LAi_Fade("", "");
		break;

	case "Merdok_book_3":
		dialog.text = "La avaricia, la estupidez y la insolencia a veces llevan a la gente a los actos más insensatos, Capitán.";
		link.l1 = "Ninguno de esos tres me motivó, te lo aseguro.";
		link.l1.go = "Merdok_book_4";
		break;

	case "Merdok_book_4":
		dialog.text = "¿Entonces estás diciendo que van Merden quitó esas páginas y las escondió en otro lugar?";
		link.l1 = "Exactamente. Podría volver y buscarlos, poner la farmacia patas arriba, o incluso todo San Juan, si lo consideras necesario.";
		link.l1.go = "Merdok_book_5";
		break;

	case "Merdok_book_5":
		dialog.text = "No es necesario, señor. La mayoría de lo importante está aquí de todos modos, y sin las páginas faltantes, el resto no supone una amenaza para mí.";
		link.l1 = "";
		link.l1.go = "Merdok_book_6";
		break;

	case "VD_Merdok_book_3":
		dialog.text = "Entonces, ¿es más bien una falta de cuidado o curiosidad en lugar de deshonestidad o una agenda secreta? ¿Crees que ya estaba así cuando lo encontraste?";
		link.l1 = "Lo más probable, Mynheer Rodenburg. Quizás van Merden arrancó esas páginas de antemano. ";
		link.l1.go = "VD_Merdok_book_4";
		break;

	case "VD_Merdok_book_4":
		dialog.text = "Quizás sea lo mejor. Sin esas páginas, el resto del archivo no representa una amenaza para mí, especialmente en manos ignorantes.";
		link.l1 = "";
		if (IsCharacterPerkOn(pchar, "Trustworthy"))
			link.l1.go = "Merdok_book_6";
		else
			link.l1 = "Merdok_6";
		break;

	case "Merdok_book_6":
		dialog.text = "Hay una recompensa por el archivo: este fino mosquete. Me ha servido con gran distinción y ahora es tuyo.";
		link.l1 = "¡Gracias!";
		link.l1.go = "Merdok_6";
		GiveItem2Character(PChar, "mushket2");
		break;

	case "Merdok_6":
		dialog.text = "Hicimos bien, tú y yo, capitán. No es una exageración decir que nada de esto habría sucedido sin ti. Alcanzarás alturas increíbles en tu carrera si continúas sirviendo a la República, quizás incluso seas ennoblecido.";
		link.l1 = "Supongo que esto es un adiós, Mynheer Rodenburg.";
		link.l1.go = "Merdok_7";
		break;

	case "Merdok_7":
		dialog.text = "Es un adiós, " + pchar.name + ". He cumplido todo lo que quería aquí, así que parto hacia casa en Ámsterdam en una semana. Mi nueva esposa Abigail y mi suegro Solomon me acompañarán. Peter Stuyvesant ya ha encontrado un nuevo subdirector de la Compañía, así que habla con él si necesitas algo\nPor tus servicios te presento el Meifeng. Es tuyo ahora, kapitein, te lo mereces.";
		link.l1 = "Gracias, Mynheer Rodenburg. Me he encariñado bastante con el Meifeng y ya empecé a considerarla como mía.";
		link.l1.go = "Merdok_8";
		break;

	case "Merdok_8":
		dialog.text = "Y ahora tengo que pedirte que me dejes, muchacho. Tengo muchas cosas que hacer antes de zarpar... ¡Visítame en Ámsterdam algún día! Compartiremos una bebida y recordaremos los buenos viejos tiempos...";
		link.l1 = "¡Sí, señor! ¡Espero que todos sean felices y prósperos en su nueva vida! ¡Adiós!";
		link.l1.go = "Merdok_9";
		// belamour legendary edition -->
		link.l2 = "¡Aye, mynheer! ¡Espero que todos sean felices y prósperos en su nueva vida!\n(entre dientes) ... Espero que no nos volvamos a ver, pedante arrogante. Solo espera hasta que descubras las ";
		link.l2.go = "Merdok_9a";
		break;

	case "Merdok_9a":
		AddCharacterExpToSkill(pchar, "FencingL", 60);
		AddCharacterExpToSkill(pchar, "FencingS", 60);
		AddCharacterExpToSkill(pchar, "FencingH", 60);
		AddCharacterExpToSkill(pchar, "Pistol", 60);
		DialogExit();
		DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip"); // можно пользоваться ПУ
		DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
		pchar.questTemp.HWIC.Holl = "end";
		AddQuestRecord("Holl_Gambit", "1-41");
		CloseQuestHeader("Holl_Gambit");
		sld = characterFromId("Abigile"); // уберем Аби
		sld.lifeday = 0;
		sld = characterFromId("Solomon"); // уберем Соломона
		sld.lifeday = 0;
		pchar.quest.Lucas_quit.win_condition.l1 = "Timer";
		pchar.quest.Lucas_quit.win_condition.l1.date.hour = sti(GetTime());
		pchar.quest.Lucas_quit.win_condition.l1.date.day = GetAddingDataDay(0, 0, 7);
		pchar.quest.Lucas_quit.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
		pchar.quest.Lucas_quit.win_condition.l1.date.year = GetAddingDataYear(0, 0, 7);
		pchar.quest.Lucas_quit.function = "LucasQuit"; // прерывание на Лукаса
		pchar.questTemp.HWIC.Detector = "holl_win";
		CheckPortugalHWIC();
		sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
		sld.Dialog.Filename = "Common_Mayor.c";	   // patch-8
		sld.dialog.currentnode = "First time";
		sld.quest.meeting = "1";
		DelMapQuestMarkCity("Villemstad");
		AddMapQuestMarkCity("FortFrance", false);
		AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
		AddSimpleRumourCity("Mynheer Rodenburg se ha embarcado rumbo a Ámsterdam con su joven esposa y su suegro. ¿Es usted el nuevo vicedirector?", "Villemstad", 30, 3, "");
		AddSimpleRumour("Dicen, kapitein, que estás bien considerado por el gobernador general. Mynheer Rodenburg supuestamente te nombró su sucesor en la Compañía, ¿es así?", HOLLAND, 30, 3);
		break;

	case "Merdok_9":
		ChangeCharacterComplexReputation(pchar, "nobility", 1);
		AddCharacterExpToSkill(pchar, "Leadership", 120);
		// <-- legendary edition
		DialogExit();
		DeleteAttribute(pchar, "questTemp.HWIC.TakeQuestShip"); // можно пользоваться ПУ
		DeleteAttribute(pchar, "questTemp.HWIC.HollEquip");
		pchar.questTemp.HWIC.Holl = "end";
		AddQuestRecord("Holl_Gambit", "1-41");
		CloseQuestHeader("Holl_Gambit");
		sld = characterFromId("Abigile"); // уберем Аби
		sld.lifeday = 0;
		sld = characterFromId("Solomon"); // уберем Соломона
		sld.lifeday = 0;
		pchar.quest.Lucas_quit.win_condition.l1 = "Timer";
		pchar.quest.Lucas_quit.win_condition.l1.date.hour = sti(GetTime());
		pchar.quest.Lucas_quit.win_condition.l1.date.day = GetAddingDataDay(0, 0, 7);
		pchar.quest.Lucas_quit.win_condition.l1.date.month = GetAddingDataMonth(0, 0, 7);
		pchar.quest.Lucas_quit.win_condition.l1.date.year = GetAddingDataYear(0, 0, 7);
		pchar.quest.Lucas_quit.function = "LucasQuit"; // прерывание на Лукаса
		pchar.questTemp.HWIC.Detector = "holl_win";
		CheckPortugalHWIC();
		sld = characterFromId("Villemstad_Mayor"); // belamour legendary edition
		sld.Dialog.Filename = "Common_Mayor.c";	   // patch-8
		sld.dialog.currentnode = "First time";
		sld.quest.meeting = "1";
		DelMapQuestMarkCity("Villemstad");
		AddMapQuestMarkCity("FortFrance", false);
		AddLandQuestMark(characterFromId("Mishelle"), "questmarkmain");
		AddSimpleRumourCity("Mynheer Rodenburg se ha embarcado rumbo a Ámsterdam con su joven esposa y su suegro. ¿Es usted el nuevo vicedirector?", "Villemstad", 30, 3, "");
		AddSimpleRumour("Dicen, kapitein, que estás bien considerado por el gobernador general. Mynheer Rodenburg supuestamente te nombró su sucesor en la Compañía, ¿es así?", HOLLAND, 30, 3);
		break;

		//----------------------------------------------за Англию------------------------------------------------------
	case "Lucas_abordage":
		dialog.text = "¡Dios en el cielo! ¡Perro de Fleetwood! Puedes ganar hoy, pero Lucas Rodenburg venderá cara su vida.";
		link.l1 = "No lo creo. Me entregarás tu vida gratis, avaro holandés.";
		link.l1.go = "Lucas_abordage_1";
		break;

	case "Lucas_abordage_1":
		PlaySound("Voice\Spanish\hambit\Lucas Rodenburg-04.wav");
		dialog.text = "¡Desde las profundidades del infierno cagaré en tu boca! ¡Acabo de prender fuego a la bodega de carga y el incendio pronto se extenderá al polvorín! ¡Nuestros barcos están atrapados a corta distancia, así que no hay esperanza de escapar! ¡Arderás o alimentarás a los tiburones!";
		link.l1 = "¡Maldita sea! ¡Retirada hombres, debemos retirarnos!";
		link.l1.go = "Lucas_abordage_2";
		// belamour legendary edition -->
		link.l2 = "No me iré hasta que tu alma abandone tu cuerpo. Quédate quieto, esto dolerá.";
		link.l2.go = "Lucas_abordage_2a";
		break;

	case "Lucas_abordage_2a":
		AddCharacterExpToSkill(pchar, "FencingL", 60);
		AddCharacterExpToSkill(pchar, "FencingS", 60);
		AddCharacterExpToSkill(pchar, "FencingH", 60);
		AddCharacterExpToSkill(pchar, "Pistol", 60);
		LAi_SetCurHPMax(NPChar);
		LAi_GetCharacterMaxEnergy(NPChar);
		QuestAboardCabinDialogExitWithBattle("PrepareToBoom1");
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		pchar.GenQuest.Detonation = true; // patch-4
		break;

	case "Lucas_abordage_2":
		AddCharacterExpToSkill(pchar, "Leadership", 120);
		// <-- legendary edition
		LAi_SetCurHPMax(NPChar);
		LAi_GetCharacterMaxEnergy(NPChar);
		QuestAboardCabinDialogExitWithBattle("PrepareToBoom1");
		DialogExit();
		AddDialogExitQuest("MainHeroFightModeOn");
		pchar.GenQuest.Detonation = true; // patch-4
		break;

		//----------------------------------------------против всех--------------------------------------------------
	case "LucasPrisoner":
		dialog.text = "¿Por qué estás aquí, maldito bastardo? ¿Aquí para burlarte de mí? Tal vez me dirás al fin cuál es tu papel en esta obra. Fuiste tú quien capturó el bergantín, ¿verdad? ¿Era este tu plan desde el principio?";
		link.l1 = "Estoy aquí para darte algunos saludos, Lucas Rodenburg. Los mejores saludos de John Merdock, a quien traicionaste. Tú eras mi tarea y la cumplí. Adiós por ahora.";
		link.l1.go = "LucasPrisoner_1";
		break;

	case "LucasPrisoner_1":
		PlaySound("Voice\Spanish\hambit\Lucas Rodenburg-04.wav");
		dialog.text = "¿Johan? ¡Jaja! ¡Así que ese era el hombre detrás de todo esto! ¡Ese viejo sinvergüenza! Pero el juego aún no ha terminado. ¡Jacob van Berg viene por ti y no escaparás! ¡Tú y tu barco están perdidos, mendigo del mar patético!";
		link.l1 = "Guarda tu voz para el tribunal del verdugo, Rodenburg.";
		link.l1.go = "LucasPrisoner_2";
		break;

	case "LucasPrisoner_2":
		DialogExit();
		pchar.questTemp.jailCanMove = true; // разрешить пройти мимо стражи
		LAi_SetPlayerType(pchar);
		pchar.quest.Login_Joakim.win_condition.l1 = "location";
		pchar.quest.Login_Joakim.win_condition.l1.location = "Villemstad_town";
		pchar.quest.Login_Joakim.function = "Create_Joakim";
		pchar.questTemp.HWIC.Self = "JoakimMeeting";
		SetFunctionTimerCondition("LucasQuit", 0, 0, 7, false);
		break;
	}
}
