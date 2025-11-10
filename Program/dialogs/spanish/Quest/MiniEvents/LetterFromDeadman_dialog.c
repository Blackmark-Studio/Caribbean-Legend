void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp;
	
	DeleteAttribute(&Dialog,"Links");
	
	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
		
		case "First time":
			dialog.text = "¿Qué quieres?";
			link.l1 = "Nada.";
			link.l1.go = "exit";
		break;
		
		case "Sailor_1":
			dialog.text = "¿Qué quieres, "+GetSexPhrase("compañero","chica")+"¿ Si me ofreces ron, no voy a decir que no. He dado tantas vueltas por este maldito pueblo que siento que las piernas se me van a hacer un nudo. ¿Cómo te llamas, entonces?";
			link.l1 = "Capitán "+GetFullName(pchar)+". No eres del 'Eagle', ¿verdad?";
			link.l1.go = "Sailor_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Sailor_2":
			if (pchar.sex == "man")
			{
				dialog.text = "Y yo - "+GetFullName(npchar)+". Y sí, soy del 'Eagle'. ¿Le gusta nuestro barco, capitán?";
			}
			else
			{
				dialog.text = "¿Capitán? Vaya, vaya... Ejem... Soy Antonio Velenta. Y sí, vengo del 'Águila'. ¿Le llamó la atención nuestro barco, capitán?";
			}
			link.l1 = "Un barco es un barco. Será mejor que subas a bordo en vez de andar deambulando por el pueblo—tu capitán ya está echando chispas. Quiere zarpar antes de que baje la marea, y algo me dice, muchacho, que no va a esperarte.";
			link.l1.go = "Sailor_3";
		break;
		
		case "Sailor_3":
			dialog.text = "Maldición... Lo sé, lo sé... Pero aún tengo asuntos pendientes en esta ciudad. ¿Te gustaría ganar un par de doblones, eh, capitán?";
			link.l1 = "Las monedas de oro nunca están de más. Pero ganarlas — это одно, meterse en líos — otra cosa. ¿Cuál es el trabajo? Habla ya.";
			link.l1.go = "Sailor_4";
		break;
		
		case "Sailor_4":
			dialog.text = "Verás, mientras descargaba la bodega, me topé con una carta. No parecía que la hubieran escondido a propósito, simplemente estaba allí entre unos barriles viejos. Nuestro fluyt ha pasado por más de un abordaje, así que es imposible saber de dónde salió.";
			link.l1 = "Así que encontraste la carta, ¿y qué con eso?";
			link.l1.go = "Sailor_5";
		break;
		
		case "Sailor_5":
			dialog.text = "Está dirigida a cierta Marisa Caldera de Porto Bello. Sellada con cera... Lo presiento en las entrañas: esto no es cualquier tontería. Quizá sea de un capitán, quizá de un comerciante... pero seguro que no de un simple marinero como yo. Solo que no tendré tiempo de buscar a la destinataria: nuestro capitán no se anda con bromas.  ¿No quieres comprármela? Te la dejo por mil pesos. Eres capitán, para ti no será difícil dar con esta señorita. Y quién sabe, tal vez te recompense con oro, o con algo más... ya me entiendes.";
			if (sti(pchar.Money) >= 1000)
			{
				link.l1 = "Bueno, entonces tal vez encuentre a tu Marisa.  De cualquier modo, no tengo nada que perder. Excepto mil pesos. Dame la carta.";
				link.l1.go = "Sailor_6";
			}
			else
			{
				Notification_Money(false, 1000, "peso");
			}
			link.l2 = "Lo siento, amigo, pero tendrás que buscar a otra persona. Tengo cosas más importantes que hacer que entregar cartas.";
			link.l2.go = "Sailor_end";
		break;
		
		case "Sailor_end":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Sailor_end");
		break;
		
		case "Sailor_6":
			dialog.text = "Aquí tienes. Bueno, cuídate, "+GetSexPhrase("compañero","chica")+", debería irme – no quisiera que mis pertenencias zarparan con el 'Eagle'.";
			link.l1 = "...";
			link.l1.go = "Sailor_accept";
			GiveItem2Character(PChar, "LFD_letter");
			AddMoneyToCharacter(pchar, -1000);
		break;
		
		case "Sailor_accept":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Sailor_accept");
			AddQuestRecord("LFD", "2");
		break;
		
		case "Dolores_1":
			dialog.text = "¿Quién eres? ¿Qué quieres?";
			link.l1 = "Me llamo Capitán "+GetFullName(pchar)+". Busco a Marisa Caldera.";
			link.l1.go = "Dolores_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Dolores_2":
			sld = CharacterFromID("PortoBello_priest");
			dialog.text = "No conozco a ninguna Marisa. Te has equivocado de puerta. Márchate ahora antes de que llame a los guardias – te echarán en un abrir y cerrar de ojos.";
			link.l1 = "Padre "+sld.name+" me dijo que eres su amigo. Tengo una carta dirigida a ella. Por su aspecto, parece que llega con mucho retraso. Quiero entregársela en persona.";
			link.l1.go = "Dolores_3";
		break;
		
		case "Dolores_3":
			dialog.text = "Ah, padre... Es demasiado amable con todos, pero rara vez se equivoca con las personas. Puedes dejarme la carta. Me aseguraré de que llegue a sus manos.";
			link.l1 = "Perdóneme, señorita, pero preferiría entregarlo en persona. Puede que tenga preguntas sobre cómo lo conseguí y por qué tardó tanto en llegar.";
			link.l1.go = "Dolores_4";
		break;
		
		case "Dolores_4":
			dialog.text = "¿Y esperas que crea así como así en tus buenas intenciones? He visto a muchos bribones con cara de santos. Deja la carta o sigue tu camino.";
			link.l1 = "Te doy mi palabra de capitán de que no haré daño ni a ti ni a Marisa. Además, puedes invitar a la guardia o a cualquier otra persona hábil con las armas a nuestra reunión. No tengo otro propósito que entregar esta carta a Marisa en persona.";
			link.l1.go = "Dolores_5";
		break;
		
		case "Dolores_5":
			dialog.text = "De acuerdo. Ven mañana después de las once de la noche. No puedo prometer que acepte reunirse, pero le contaré todo lo que has dicho.";
			link.l1 = "Estaré allí. Nos vemos pronto.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Dolores_1");
		break;
		
		case "Marisa_1":
			dialog.text = "Hola, "+GetAddress_Form(NPChar)+" "+pchar.lastname+". Me estabas buscando, y aquí estoy. ¿Dolores dijo que tienes una carta para mí?";
			link.l1 = "Buenos días, señora Caldera. Así es, aquí está usted. Lamentablemente, parece que ha tardado bastante en llegarle.";
			link.l1.go = "Marisa_2";
			DelLandQuestMark(npchar);
			TakeItemFromCharacter(pchar, "LFD_letter");
			notification("Entregado: Carta para Marisa Caldera", "None");
		break;
		
		case "Marisa_2":
			dialog.text = "Dolores... Esta es su letra... ¡La letra de Ramiro!";
			link.l1 = "...";
			link.l1.go = "Marisa_2_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
			sld = CharacterFromID("LFD_Dolores");
			LAi_CharacterEnableDialog(sld);
		break;
		case "Marisa_2_1":
			StartInstantDialog("LFD_Dolores", "Marisa_3", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_3":
			dialog.text = "¿Pero cómo es posible? ¡Han pasado dos años!";
			link.l1 = "...";
			link.l1.go = "Marisa_3_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_3_1":
			StartInstantDialog("LFD_Marisa", "Marisa_4", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_4":
			dialog.text = ""+UpperFirst(GetAddress_Form(NPChar))+" Capitán... ¿Cómo lo consiguió? ¿Dónde lo encontró? ¡Debo saberlo todo! Por favor, cuénteme todo lo que sepa.";
			link.l1 = "Esta carta me la entregó un marinero. La encontró en un rincón oscuro de la bodega de su barco y quería dártela él mismo, pero tuvo que regresar a su nave apresuradamente. Así que me pidió que te buscara, y aquí estoy. Eso es todo lo que sé...";
			link.l1.go = "Marisa_5";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Marisa_5":
			dialog.text = "Gracias, "+GetAddress_Form(NPChar)+"¡ Muchas gracias! Por favor, no te vayas. Quiero seguir hablando contigo, pero primero... necesito leer esta carta.";
			link.l1 = "Por supuesto, Lady Caldera. Estaré aquí.";
			link.l1.go = "Marisa_6";
		break;
		
		case "Marisa_6":
			DialogExit();
			SetLaunchFrameFormParam("Pasaron veinte minutos, Marisa leyó la carta...", "Run_Function", 0, 4.0);
			SetLaunchFrameRunFunctionParam("LFD_Dolores_3", 0.0);
			LaunchFrameForm();
		break;
		
		case "Marisa_11":
			dialog.text = "Dolores... Escribió esta carta antes de su último viaje. Quería contarme que tenía la oportunidad de comprar un gran cargamento de ébano a un comerciante en Belice, pero no tenía suficiente dinero. Fue entonces cuando pidió este préstamo... Doscientos doblones... Por culpa de eso ahora no puedo encontrar paz.";
			link.l1 = "...";
			link.l1.go = "Marisa_11_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_11_1":
			StartInstantDialog("LFD_Dolores", "Marisa_12", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_12":
			dialog.text = "Eso lo explica todo... Pero, lamentablemente, no aliviará tu carga. Mantente fuerte, Marisa. La oscuridad no es eterna, y esta deuda no te perseguirá para siempre.";
			link.l1 = "...";
			link.l1.go = "Marisa_12_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_12_1":
			StartInstantDialog("LFD_Marisa", "Marisa_13", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_13":
			dialog.text = "No, Dolores, ¡no lo habrá! Ramiro escribió que tiene un escondite... en nuestro lugar. Si sigue intacto, quizá pueda saldar la deuda y por fin escapar de esta pesadilla.";
			link.l1 = "...";
			link.l1.go = "Marisa_13_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_13_1":
			StartInstantDialog("LFD_Dolores", "Marisa_14", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_14":
			dialog.text = "¡El Señor te ha mostrado misericordia! Ha escuchado nuestras plegarias...";
			link.l1 = "...";
			link.l1.go = "Marisa_14_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Dolores"));
			CharacterTurnByChr(CharacterFromID("LFD_Dolores"), CharacterFromID("LFD_Marisa"));
		break;
		case "Marisa_14_1":
			StartInstantDialog("LFD_Marisa", "Marisa_15", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Marisa_15":
			dialog.text = "Capitán, una vez más, gracias por traerme esta carta. Significa el mundo para mí... Pero debo pedirle un favor más. Verá, mi esposo Ramiro lo era todo para mí, y nunca busqué protección en ningún otro hombre. Ahora que él se ha ido, no me queda nadie a quien acudir, no tengo familia propia\nDebo llegar a su escondite – está fuera de la ciudad. Pero tengo demasiado miedo de ir sola, los acreedores de mi difunto esposo me persiguen. Usted actuó con honor al encontrarme para entregarme la carta... Por favor, ayúdeme una vez más.";
			link.l1 = "Por supuesto, Marisa, te acompañaré. ¿Cuándo quieres partir?";
			link.l1.go = "Marisa_16";
			link.l2 = "Lo siento, señora, pero mi estancia en su ciudad ya se ha prolongado demasiado. Los paseos por el campo no forman parte de mis planes.";
			link.l2.go = "Marisa_end_1";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Marisa_end_1":
			dialog.text = "Lo entiendo... Ya has hecho más por mí de lo que jamás habría esperado. Gracias, capitán, y adiós.";
			link.l1 = "Adiós.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_end");
		break;
		
		case "Marisa_16":
			dialog.text = "Gracias, Capitán. Ven mañana al amanecer, para las siete. Estaré listo.";
			link.l1 = "Entonces, hasta que nos volvamos a ver, señora.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_1");
		break;
		
		case "Marisa_21":
			if (GetHour() >= 7 && GetHour() <= 19)
			{
				if (pchar.sex == "man")
				{
					dialog.text = "Caballero, ahí está... ¡De verdad es usted un hombre de honor! Partamos. Nuestro camino atraviesa la selva hasta la gruta, no muy lejos de la Bahía de los Mosquitos.";
				}
				else
				{
					dialog.text = "Capitana, ahí está... Sabía que vendrías. Sabes, es la primera vez que conozco a una mujer que manda su propio barco. Y ya veo que eres tan digna y noble como cualquier hombre—¡en honor y en nobleza!";
				}
				link.l1 = "Excelente, señora. Entonces no perdamos tiempo. Manténgase cerca y no se aparte ni un momento.";
				link.l1.go = "Marisa_go_cove";
				if (startHeroType == 4) // если ГГ Элен
				{
					link.l1 = "Gracias, Marisa. Mi padre fue capitán y un hombre de honor, y desde niña me inculcó esos mismos ideales.";
					link.l1.go = "Marisa_22";
				}
			}
			else
			{
				dialog.text = "Ven al amanecer, a las siete en punto. Estaré listo.";
				link.l1 = "Nos vemos entonces, señora.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Marisa_21";
			}
		break;
		
		case "Marisa_22":
			dialog.text = "¿De verdad? ¿Corrió la misma suerte que mi Ramiro?";
			link.l1 = "Seguramente habría preferido encontrar su final con la espada en la mano o en medio de una tormenta. Pero el destino tenía otros planes: lo acabó una enfermedad de la que nunca habló con nadie.";
			link.l1.go = "Marisa_23";
		break;
		
		case "Marisa_23":
			dialog.text = "Lamento mucho tu pérdida, "+pchar.name+" El Señor se lleva a los mejores entre nosotros... Y aunque no siempre entendamos por qué, es Su voluntad. Todo lo que podemos hacer es rezar por el descanso de sus almas inmortales.";
			link.l1 = "...";
			link.l1.go = "Marisa_24";
		break;
		
		case "Marisa_24":
			dialog.text = "Sigamos nuestro camino. Nuestro rumbo nos lleva por la selva hasta la gruta, no muy lejos de la Bahía de los Mosquitos.";
			link.l1 = "Por supuesto. Quédate cerca y no te alejes ni un momento.";
			link.l1.go = "Marisa_go_cove";
		break;
		
		case "Marisa_go_cove":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Marisa_2");
		break;
		
		case "Marisa_31":
			dialog.text = "Aquí estamos... Ramiro y yo una vez nos refugiamos de la lluvia aquí, cuando éramos jóvenes, antes de que él se convirtiera en mi esposo. Fue entonces cuando me dijo que conquistaría mi corazón, sin importar lo que costara.";
			link.l1 = "Lamento que haya tenido que venir aquí sola, sin su esposo, señora. Lugares como este guardan muchos recuerdos. Demos una vuelta – quizá, además de recuerdos, encontremos lo que Ramiro guardó para los tiempos más difíciles.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_4");
		break;
		
		case "Marisa_32":
			dialog.text = ""+GetSexPhrase("Señor "+pchar.lastname+"",""+pchar.name+"")+"... ¿Encontraste algo? ¿Es lo que dejó Ramiro? Ni siquiera sé qué me asusta más: si que esté vacío, o que no alcance para saldar la deuda...";
			if (PCharDublonsTotal() >= 400 && GetCharacterItem(pchar, "jewelry2") >= 10 && GetCharacterItem(pchar, "jewelry3") >= 10 && CheckCharacterItem(PChar, "mushket1"))
			{
				link.l1 = "(muestra) Aquí, esto es todo lo que había en el cofre. Espero que sea suficiente para cambiar tu destino para bien.";
				link.l1.go = "Marisa_33";
				DelLandQuestMark(npchar);
			}
			else
			{
				link.l1 = "Sigo buscando en el cofre.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Marisa_32";
			}
		break;
		
		case "Marisa_33":
			dialog.text = "¡Ah, capitán! ¡Por supuesto! ¡Eso debería ser suficiente! Pero no puedo dejar tu ayuda sin recompensa. Toma cien doblones. Si no fuera por ti, nunca me habría enterado de este escondite y seguiría huyendo de los hombres enviados por el acreedor de Ramiro...";
			link.l1 = "Es usted muy generosa, señora, gracias. En nuestro oficio, el oro nunca se desperdicia.";
			link.l1.go = "Marisa_34";
			link.l2 = "No, señora. Usted necesita este dinero mucho más que yo. Lo importante es que ahora puede dejar atrás sus problemas y vivir en paz. Eso es más que suficiente para mí.";
			link.l2.go = "Marisa_35";
			RemoveDublonsFromPCharTotal(400);
			RemoveItems(pchar, "jewelry2", 10);
			RemoveItems(pchar, "jewelry3", 10);
			TakeItemFromCharacter(pchar, "mushket1");
			TakeItemFromCharacter(pchar, "obereg_7");
			TakeItemFromCharacter(pchar, "amulet_11");
			notification("Entregado: Amuleto 'Cimaruta'", "None");
			notification("Entregado: Amuleto 'Pescador'", "None");
			notification("Entregado: Mosquete de mecha", "None");
			notification("Entregado: Diamante (10)", "None");
			notification("Entregado: Rubí (10)", "None");
		break;
		
		case "Marisa_34":
			dialog.text = "Bueno, "+GetSexPhrase("señor",""+pchar.name+"")+", deberíamos ponernos en marcha. Si me vieron en el pueblo, puede que alguien nos esté siguiendo. Mejor no quedarnos aquí.";
			link.l1 = "Tienes razón, Marisa. Vamos.";
			link.l1.go = "Marisa_naemnik";
			TakeNItems(pchar, "gold_dublon", 100);
		break;
		
		case "Marisa_35":
			dialog.text = "Capitán, por favor... mi esposo guardaba esta arma para proteger a nuestra familia, y estoy segura de que—en sus manos—servirá a una causa justa. Ramiro se alegraría de saber que ha ido a la persona que me salvó cuando toda esperanza estaba perdida.";
			link.l1 = "Está bien, Marisa, gracias. Eres una mujer bondadosa y honorable, y de verdad lamento que el destino haya sido tan cruel contigo.";
			link.l1.go = "Marisa_36";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Marisa_36":
			dialog.text = "A veces el Señor nos envía días difíciles, o incluso años, para poner a prueba nuestra fe, pero nunca abandona a quienes siguen el camino recto. Te ha enviado para ayudarme, y ahora, espero, mi mayor problema pronto quedará atrás.  Pero por ahora, es hora de regresar. Ya hemos estado aquí suficiente tiempo, y podría ser peligroso, ya que todavía me están buscando.";
			link.l1 = "Por supuesto, señora, vamos.";
			link.l1.go = "Marisa_naemnik";
			GiveItem2Character(pchar, "mushket1");
			GiveItem2Character(pchar, "obereg_7");
			GiveItem2Character(pchar, "amulet_11");
		break;
		
		case "Marisa_naemnik":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Marisa_6");
		break;
		
		case "Naemnik_1":
			dialog.text = "¡Ja! ¡Así que aquí está nuestro desaparecido! ¿De verdad pensaste que podrías esconderte aquí, en este agujero como un ratón, y que no te encontraría? He puesto la ciudad patas arriba más de una vez, y aquí estabas todo el tiempo"+GetSexPhrase(", y encima, saliste con algún mocoso. ¿Dónde está mi dinero, pequeña zorra? Será mejor que me lo des ahora mismo, o esta cueva será tu tumba.",".")+"";
			link.l1 = "...";
			link.l1.go = "Naemnik_1_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		case "Naemnik_1_1":
			StartInstantDialog("LFD_Marisa", "Naemnik_2", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Naemnik_2":
			dialog.text = "Tú...";
			link.l1 = "...";
			link.l1.go = "Naemnik_2_1";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		case "Naemnik_2_1":
			StartInstantDialog("LFD_Naemnik", "Naemnik_3", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
		break;
		
		case "Naemnik_3":
			dialog.text = "...";
			link.l1 = "¿Así que eres tú quien se gana la vida extorsionando a mujeres por deudas? Por el oficio que elegiste, está claro que la inteligencia nunca fue tu punto fuerte. Es un milagro que hayas conseguido llegar hasta aquí solo, en vez de simplemente seguir a alguien más listo... como tu propia bota, por ejemplo.";
			link.l1.go = "Naemnik_4";
			CharacterTurnByChr(npchar, pchar);
		break;
		
		case "Naemnik_4":
			if (pchar.sex == "man")
			{
				dialog.text = "Cierra la boca, héroe. Tu momento llegará, pero primero me encargaré de ella. Debe quinientos veinticinco doblones, esa es su deuda con intereses. O paga todo, o se queda aquí para siempre, a alimentar a los gusanos. Pero ya que eres tan justo, puedes pagar por ella, y yo me iré.";
				if (PCharDublonsTotal() >= 525)
				{
					link.l1 = "¿Crees que puedes entrar aquí, insultar a una dama, ignorarme y salir de una pieza, y encima con los doblones? Parece que no eres muy listo. Pero no voy a armar una pelea delante de una mujer. Así que te lo pongo fácil: le pides disculpas a la señora Caldera, coges tus doblones y te largas de aquí. O tendré que enseñarte modales como corresponde.";
					link.l1.go = "Naemnik_5";
					Notification_Money(true, 525, "dublon");
				}
				else
				{
					Notification_Money(false, 525, "dublon");
				}
			}
			else
			{
				dialog.text = "Cierra la boca y espera tu turno. Ya me encargaré de ti después, cuando termine con esta desgraciada. Ella debe quinientos veinticinco doblones, esa es su deuda con intereses. Si eres tan justo, puedes pagar por ella, y me iré.";
				if (PCharDublonsTotal() >= 525)
				{
					link.l1 = "Bueno, estoy dispuesto a perdonar tus modales bruscos e incluso tu grosería hacia mí. Pero si quieres recibir tus doblones y salir de aquí entero, tendrás que disculparte con Lady Caldera. De lo contrario, veremos quién maneja mejor las armas. Y créeme, no llevo la mía solo para lucirla.";
					link.l1.go = "Naemnik_5";
					Notification_Money(true, 525, "dublon");
				}
				else
				{
					Notification_Money(false, 525, "dublon");
				}
			}
			link.l2 = "Está claro que no tienes mucha sesera si pensaste que iba a esperar mi turno. Y aún menos si creíste que iba a hacer la vista gorda ante todos los problemas que tú y los tuyos le habéis traído a Lady Caldera.";
			link.l2.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_5":
			dialog.text = "Está bien, hazlo a tu manera. Si podemos conseguir el dinero sin arriesgarnos más de la cuenta, no veo motivo para jugarme el cuello. Entrega los doblones y lárgate.";
			link.l1 = "Primero, discúlpate con la dama.";
			link.l1.go = "Naemnik_6";
		break;
		
		case "Naemnik_6":
			dialog.text = "Perdóneme, señora. El diablo se apoderó de mí.";
			link.l1 = "...";
			link.l1.go = "Naemnik_7";
			CharacterTurnByChr(CharacterFromID("LFD_Marisa"), CharacterFromID("LFD_Naemnik"));
			CharacterTurnByChr(CharacterFromID("LFD_Naemnik"), CharacterFromID("LFD_Marisa"));
		break;
		
		case "Naemnik_7":
			dialog.text = "Feliz"+GetSexPhrase("","")+"¿Entrega el oro y me marcho. Tengo mucho que hacer, no tengo tiempo para quedarme aquí intercambiando cortesías contigo.";
			link.l1 = "Llévate tus doblones y lárgate de aquí.";
			link.l1.go = "Naemnik_7_1";
			CharacterTurnByChr(npchar, pchar);
			RemoveDublonsFromPCharTotal(525);
		break;
		
		case "Naemnik_7_1":
			StartInstantDialog("LFD_Marisa", "Marisa_37", "Quest\MiniEvents\LetterFromDeadman_dialog.c");
			ChangeCharacterComplexReputation(pchar, "nobility", 5);
			ChangeCharacterNationReputation(pchar, SPAIN, 10);
		break;
		
		case "Marisa_37":
			dialog.text = "Capitán, de verdad, no entiendo... ¿Qué significa esto?";
			link.l1 = "Eso significa que ya no debes nada. Eres libre.";
			link.l1.go = "Marisa_38";
			CharacterTurnByChr(npchar, pchar);
			
			sld = CharacterFromID("LFD_Naemnik");
			LAi_SetActorType(sld);
			LAi_ActorGoToLocation(sld, "reload", "reload1", "none", "", "", "", 5);
			sld.lifeday = 0;
		break;
		
		case "Marisa_38":
			dialog.text = "Pero... no tengo todo el dinero para devolvértelo ahora mismo. Si pudieras esperar un poco...";
			link.l1 = "No lo entiendes, Marisa. No me debes nada. Ya no le debes nada a nadie. Y el dinero que encontraste te será muy útil. Vuelve a tu antigua vida: la iglesia te espera.";
			link.l1.go = "Marisa_39";
		break;
		
		case "Marisa_39":
			dialog.text = "Yo... yo simplemente no puedo creerlo. Cosas así no pasan, "+GetSexPhrase("caballero","señorita")+"¡ Pagaste una fortuna por mí... así sin más? ¿Y ahora se acabó todo? ¿Sin deudas, sin persecuciones? Dime, ¿es verdad?";
			link.l1 = "Es cierto, señora. Todo ha terminado. Ya no le debe nada a nadie.";
			link.l1.go = "Marisa_40";
		break;
		
		case "Marisa_40":
			dialog.text = "¡Oh, capitán, eres tan noble! ¡Siento como si hubieras sido enviado por Dios! Pero ni siquiera puedo imaginar cómo agradecerte. Has... cambiado mi vida por completo, y yo... ¿qué podría hacer por ti?";
			link.l1 = "No necesitas hacer nada, Marisa. Solo vive. Sin miedo, sin las cadenas del pasado. Vuelve a tu antigua vida y encuentra la felicidad en ella; esa será la mejor manera de darme las gracias. Ven, te acompaño hasta el pueblo.";
			link.l1.go = "Naemnik_mir";
		break;
		
		case "Naemnik_bitva":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Naemnik_bitva");
		break;
		
		case "Naemnik_mir":
			DialogExit();
			AddDialogExitQuestFunction("LFD_Naemnik_mir");
		break;
		
		case "Marisa_41":
			dialog.text = "¡Qué has hecho, capitán, lo has matado!";
			link.l1 = "Así es, señora. Tenía que protegerla a usted y su honor...";
			link.l1.go = "Marisa_42";
		break;
		
		case "Marisa_42":
			dialog.text = "¡Oh, Capitán, quitarle la vida a alguien, incluso a uno como él, es un pecado terrible y pesado! Tendrá que rezar día y noche para lavar aunque sea un poco de eso de su alma inmortal. Dios es mi testigo, podría haberle dado todo lo que tenía y se habría marchado... Pero ahora... ahora su sangre está en sus manos, y solo los cielos decidirán si será perdonado.";
			link.l1 = "Quizás fue la voluntad del Señor. Pero no pensemos más en eso. Mejor salgamos de esta cueva.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Naemnik_bitva_3");
		break;
		
		case "Marisa_51":
			dialog.text = "¡Capitán, permítame agradecerle una vez más! Rezaré por su salud y bienestar, "+pchar.name+". Por favor, ven a nuestra iglesia; que el Señor te conceda el perdón de todos tus pecados y su bendición.";
			link.l1 = "Quizá pase por allí algún día. Y tenlo en cuenta, Marisa, si no veo tu cara sonriente allí, me llevaré una gran decepción.";
			link.l1.go = "Marisa_52";
		break;
		
		case "Marisa_52":
			dialog.text = "Ah, "+GetAddress_Form(NPChar)+"... Eres muy amable conmigo. De verdad me alegrará verte de nuevo en nuestro pueblo. Pero por ahora, discúlpame, no puedo esperar para poner mi vida en orden y compartir las buenas noticias con Dolores.";
			link.l1 = "Por supuesto, Marisa. Adiós. Cuídate.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_In_Church");
		break;
		
		case "Marisa_54":
			dialog.text = "¡Capitán, permítame una vez más expresarle mi eterna gratitud! ¡Ha hecho lo imposible por mí! Por su bondad y nobleza, quiero contarle cómo logré evitar a los mercenarios durante estos dos últimos años. Quizás este conocimiento algún día también le sea útil a usted.";
			link.l1 = "Gracias, señora. En asuntos como estos, el conocimiento vale tanto como el oro. Le escucho.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Finish_In_Town_NaemnikAlive_2");
		break;
		
		case "Marisa_55":
			dialog.text = "Así pasé estos dos años. En un mundo donde la fuerza lo es todo, saber moverse en las sombras abre oportunidades con las que otros solo pueden soñar.";
			link.l1 = "Gracias por compartir tu historia, Marisa. Has pasado por mucho, y tu experiencia es realmente invaluable.";
			link.l1.go = "Marisa_56";
			AddCharacterExpToSkill(pchar, "Sneak", 500);
		break;
		
		case "Marisa_56":
			dialog.text = "Me alegrará mucho volver a verte en nuestro pueblo. Por favor, ven a nuestra iglesia—que el Señor te conceda el perdón de todos tus pecados y su bendición.";
			link.l1 = "Quizás pase por ahí algún día. Y tenlo en cuenta, Marisa, si no veo tu cara sonriente allí, me llevaré una gran decepción.";
			link.l1.go = "Marisa_57";
		break;
		
		case "Marisa_57":
			dialog.text = "Ah, Capitán... Eres tan amable conmigo. Pero ahora, discúlpame, no puedo esperar para poner mi vida en orden y compartir las buenas noticias con Dolores.";
			link.l1 = "Por supuesto, Marisa. Adiós. Cuídate.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LFD_Marisa_In_Church");
			
			//слухи
			AddSimpleRumourCity(""+GetSexPhrase("¿Has oído? ¡El capitán "+GetFullName(pchar)+" pagó de su propio bolsillo las deudas de la viuda de Calderón! Pocos estarían dispuestos a desprenderse de tal fortuna por un desconocido. ¡Todavía quedan verdaderos caballeros en España!", "Es un gozo ver que en España no solo hay caballeros honorables, sino también mujeres cuya valentía y honor no tienen nada que envidiar a los hombres.")+"", "PortoBello", 7, 1, "");
			AddSimpleRumourCity("Dicen que un capitán entregó su propio dinero para liberar a la viuda de Calderón de las deudas de su difunto esposo. ¡No cualquiera haría algo tan noble! Un verdadero hombre de honor, ¿no crees?", "PortoBello", 7, 1, "");
		break;
		
		case "Marisa_61":
			if (CheckAttribute(pchar, "questTemp.LFD_NaemnikDead"))
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "¡Capitán, es un placer volver a verle! Esperaba que pasara por aquí. ¿Quizá hoy tenga tiempo para quedarse un rato y rezar?";
						link.l1 = "Me alegro"+GetSexPhrase("","")+" encuentro, Marisa. Pero me temo que no puedo permitirme quedarme ahora mismo. Recuerdo mi deber ante el Señor, pero la oración tendrá que esperar.";
						link.l1.go = "Marisa_62";
					break;

					case 1:
						dialog.text = "¡Capitán, usted de nuevo! Siempre es un placer. Parece que el Señor no le deja olvidar el camino a la iglesia... ¿Quizás encuentre un momento para rezar después de todo?";
						link.l1 = "Marisa, me alegra verte. Pero no puedo quedarme – mis asuntos no pueden esperar. Creo que el Señor conoce mis pensamientos incluso sin oración.";
						link.l1.go = "Marisa_63";
					break;
				}
			}
			else
			{
				switch (rand(1))
				{
					case 0:
						dialog.text = "¡Capitán, qué alegría volver a verle! Cada día le doy gracias al Señor por su bondad. El mundo se volvió más luminoso cuando me ayudó.";
						link.l1 = "Me alegro"+GetSexPhrase("","")+"   Me alegra verte bien, Marisa. Espero que la vida no te haya dado más sorpresas desagradables. Te veo mucho más feliz.";
						link.l1.go = "Marisa_64";
					break;

					case 1:
						dialog.text = "¡Capitán, me alegra tanto verte! Cada vez que vienes a nuestra iglesia, siento una gran paz. Traes contigo la luz de las buenas acciones.";
						link.l1 = "Y me alegro"+GetSexPhrase("","")+" Me alegra verte, Marisa. ¿Te has acostumbrado ya a una vida tranquila, o a veces sigues mirando atrás?";
						link.l1.go = "Marisa_65";
					break;
				}
			}
			SetTimerFunction("LFD_Marisa_HelloAgain", 0, 0, 1);
		break;
		
		case "Marisa_62":	
			dialog.text = ""+pchar.name+", si todos siguieran posponiendo la oración, el mundo habría caído en la oscuridad hace mucho tiempo. Deja tus preocupaciones a un lado por un momento: el arrepentimiento te da fuerzas para seguir adelante.";
			link.l1 = "Lo entiendo, Marisa, pero de verdad no puedo ahora. Creo que el Señor me escuchará incluso sin palabras.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_62_1";
		break;
		
		case "Marisa_62_1":	
			dialog.text = ""+pchar.name+", ¿has cambiado de opinión? Los pecados no desaparecen por sí solos, y cuanto más esperas, más pesan.";
			link.l1 = "Ay, debo irme. Pero la próxima vez, te prometo que rezaré.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_62_1";
		break;
		
		case "Marisa_63":	
			dialog.text = "Pero la fe no es solo cuestión de saber, ¡sino de actuar! No puedes seguir posponiendo el camino hacia la redención para siempre. ¿No quieres sentir el alivio de liberarte del peso del pecado?";
			link.l1 = "Quizá, pero no ahora. Que el Señor me escuche, aunque la oración deba esperar.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_63_1";
		break;
		
		case "Marisa_63_1":	
			dialog.text = "Capitán, ¿no cree que posponer el arrepentimiento es un pecado en sí mismo? Algún día podría ser demasiado tarde.";
			link.l1 = "Quizás, pero me temo que hoy no tengo tiempo. La fe me acompaña, y el Señor ve mi arrepentimiento incluso sin oración.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_63_1";
		break;
		
		case "Marisa_64":	
			dialog.text = "Sí, gracias a ti puedo volver a respirar tranquilo. Que el Señor vele por ti y por tu viaje. ¿Quizás quieras rezar conmigo?";
			link.l1 = "Creo que tus oraciones ya son lo bastante poderosas. Lo más importante es que ahora solo te rodea la bondad.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_64_1";
		break;
		
		case "Marisa_64_1":	
			dialog.text = ""+pchar.name+", ¿has cambiado de opinión después de todo? ¿Rezamos a nuestro Creador?";
			link.l1 = "Lo siento, Marisa, tengo que irme ahora, tengo cosas que hacer.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_64_1";
		break;
		
		case "Marisa_65":	
			dialog.text = "Intento mirar solo hacia adelante. Ahora tengo un futuro, y todo es gracias a ti. ¿Quizás deberíamos agradecerle al Señor por esto juntos?";
			link.l1 = "Creo que lo harás mejor que yo. Lo importante es que tus oraciones te den paz.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_65_1";
		break;
		
		case "Marisa_65_1":	
			dialog.text = ""+pchar.name+", quizás pueda convencerte de que reces al menos una oración?";
			link.l1 = "Perdóname, Marisa, pero lamentablemente no tengo tiempo ahora. Reza también por mí.";
			link.l1.go = "exit";
			NextDiag.TempNode = "Marisa_65_1";
		break;
		
		case "Marisa_Ne_Ta_Peshera":	
			dialog.text = "Capitán, este no es el lugar. La cueva que buscamos está junto a la Bahía de los Mosquitos.";
			link.l1 = "...";
			link.l1.go = "Marisa_Ne_Ta_Peshera_1";
		break;
		
		case "Marisa_Ne_Ta_Peshera_1":	
			DialogExit();
			NextDiag.TempNode = "Marisa_31";
			DeleteQuestCondition("LFD_Ne_Ta_Peshera");
			
			sld = CharacterFromID("LFD_Marisa");
			LAi_SetActorType(sld);
			LAi_ActorFollowEverywhere(sld, "", -1);
		break;
		
	}
}