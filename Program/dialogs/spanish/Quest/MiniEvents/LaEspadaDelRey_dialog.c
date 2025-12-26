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
			dialog.text = "¿Qué quiere?";
			link.l1 = "Nada.";
			link.l1.go = "exit";
		break;
		
		case "LEDR_Gonsalo_1":
			if (pchar.sex == "man")
			{
				dialog.text = "¡Eh, chico! Veo que eres un marinero valiente, y seguro que también sabes pelear. ¿No me ayudarías a hacer una incursión en un lugarcito, eh?";
			}
			else
			{
				dialog.text = "¡Eh, guapa! Veo que no eres de las tímidas, si te has atrevido a venir aquí. ¿No me ayudarías a hacer una incursión en un sitio, eh?";
			}
			link.l1 = "Supongo que eres el viejo que busca un guía hacia el barco antiguo?";
			link.l1.go = "LEDR_Gonsalo_2";
			DelLandQuestMark(npchar);
		break;
		
		case "LEDR_Gonsalo_2":
			dialog.text = "Heh... Así que los rumores vuelan más rápido que el viento. Sí, soy yo. Gonzalo Peralta, el único que sigue con vida del naufragio de 'La Espada del Rey'.";
			link.l1 = "Y yo soy capitán "+GetFullName(pchar)+". ¿Quieres volver a ver tu barco?";
			link.l1.go = "LEDR_Gonsalo_3";
		break;

		case "LEDR_Gonsalo_3":
			dialog.text = "Sí. Verás, desde hace un tiempo me atormenta la misma pesadilla. Pero el asunto no es sólo eso... Créelo o no, pero cada mañana, apenas termina la pesadilla, me despierto y... frente a mí está un maldito esqueleto...";
			link.l1 = "Con atuendo indígena. Me dijeron que siempre cuentas esa historia a todo el mundo.";
			link.l1.go = "LEDR_Gonsalo_4";
		break;

		case "LEDR_Gonsalo_4":
			dialog.text = "¿Una historia? Je... Ojalá fuera solo una historia. Hace apenas un par de meses llevaba una vida tranquila, como corresponde a un viejo marinero retirado. Pero ahora ese saco de huesos viene a mí cada mañana, me mira, lanza un grito desgarrador... maldita sea, a cualquier contramaestre se le helaría la sangre en las venas... y luego se lanza al ataque. ¿Y sabes qué? Cada vez ataca con más furia. Por eso quiero llegar cuanto antes al barco: no me abandona la sensación de que allí debo encontrar algo.";
			link.l1 = " Hmm... Vaya situación. ¿Y qué esperas encontrar allí después de tanto tiempo?";
			link.l1.go = "LEDR_Gonsalo_5";
		break;
		
		case "LEDR_Gonsalo_5":
			dialog.text = "No lo sé, capitán, no lo sé... Pero algo me atrae hacia ese barco, como una vieja barcaza en medio de una tormenta. Mi sueño, ese esqueleto y esa extraña sensación... Por el mar, juro que están conectados de algún modo. Solo que no logro entender cómo.";
			link.l1 = "¿Qué ocurre exactamente en tu sueño? ¿Tiene algo que ver con los indios?";
			link.l1.go = "LEDR_Gonsalo_6";
			link.l2 = "Así que por las noches ves visiones y por las mañanas luchas contra un esqueleto, ¿eh? ¿Seguro que el problema no está en tu cabeza y que ya es hora de que te vea un médico? No voy a alimentar tus fantasías desatadas. Busca a otro tonto que crea en tus disparates.";
			link.l2.go = "LEDR_Gonsalo_6_end";
		break;
		
		case "LEDR_Gonsalo_6_end":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_End");
		break;
		
		case "LEDR_Gonsalo_6":
			dialog.text = "¡Y tanto que estoy relacionado, que me parta un rayo... En ese sueño estoy con la tripulación muerta  en 'La Espada del Rey'. Nosotros... saqueamos aldeas de caribes en La Española, matamos a todos sin distinción: hombres, mujeres, niños. A los que luchan y hasta a los que caen de rodillas, suplicando piedad. Arrasamos los asentamientos uno tras otro. Las flechas y garrotes de los indios contra nosotros son como una tartana agujereada frente a un galeón de guerra. Los caribes, desesperados, piden negociar, y entonces...";
			link.l1 = "¡Dios misericordioso! ¿Así que tú participaste en esas atrocidades? ¡Тебе no necesitas ayuda, sino una soga de cáñamo al cuello!";
			link.l1.go = "LEDR_Gonsalo_7";
		break;
		
		case "LEDR_Gonsalo_7":
			dialog.text = "¡No! ¡No, que me parta un rayo, no fue así, ¿entiendes?! No tengo ni idea de por qué sueño con todo esto... pero te juro por todos los santos que ni yo ni mi tripulación participamos en semejantes atrocidades.";
			link.l1 = "Más te vale que así sea de verdad. Continúa.";
			link.l1.go = "LEDR_Gonsalo_8";
		break;

		case "LEDR_Gonsalo_8":
			dialog.text = "Los caribes pidieron negociar, y el capitán aceptó. Invitó a todos ellos a una de esas chozas que 'nosotros' habíamos tomado. Los caciques vinieron — dos docenas de personas, no menos — encabezados por su reina, Anacaona. Pero el capitán mismo no entró... ninguno de nosotros entró. Apenas el último cacique cruzó el umbral, la puerta fue cerrada de golpe y atrancada con vigas. Y luego... maldita sea... la incendiaron. Sólo perdonaron a la reina, pero no por mucho tiempo. La obligaron a mirar cómo su pueblo ardía vivo... Y después la ahorcaron en un árbol.";
			link.l1 = "¿Y esto se repite cada noche? ¿El mismo sueño, una y otra vez? Sabes, no me sorprendería que después de todo eso, ese esqueleto no sea más que fruto de tu mente trastornada...";
			link.l1.go = "LEDR_Gonsalo_9";
		break;

		case "LEDR_Gonsalo_9":
			dialog.text = "Eso no es todo. Los caribes que sobrevivieron huyeron a Cuba, encontraron allí apoyo entre las tribus locales y pronto se reunieron en un solo ejército, bajo el mando de un jefe. Atuey, creo que así se llamaba. Lo seguían como a su última esperanza. Pero los derrotamos sin dificultad. Atuey fue capturado y preparado para la ejecución\nCuando lo ataron a la cruz, preparándose para quemarlo, un fraile le ofreció aceptar la verdadera fe, diciendo que así aliviaría su sufrimiento y alcanzaría el paraíso. Atuey le preguntó al fraile si el paraíso estaba abierto para los españoles\nY cuando éste respondió que, por supuesto, los buenos españoles tenían las puertas abiertas, el cacique, sin pensarlo mucho, contestó que en ese caso prefería el infierno, para no compartir morada con gente tan cruel. Después dijo unas palabras más en su lengua, y la hoguera fue encendida. No emitió ni un solo sonido cuando las llamas tocaron su carne\nPor el mar, no quisiera presenciar algo así en la vida real. Mi sueño siempre termina igual: el capitán está sentado, sin moverse. Sólo una vela humea a su lado, y él hojea un diario gastado. Despacio, como si cada palabra pesara oro, y murmura algo para sí. Incluso en sueños, "+GetSexPhrase("chico","chica")+", lo entiendo: es una señal. Es hora de empuñar la espada, porque él ya ataca\nAyúdame a librarme de esta pesadilla, capitán. Ven conmigo a la bahía. Yo solo no me atrevo a ir — ya no me queda pólvora en los cartuchos. Pero antes de que respondas, debo advertirte: no tengo con qué pagarte, si fuera de otra manera, ya habría una cola de ayudantes aquí. Así que sólo me queda confiar en la ayuda de un hermano marinero.";
			link.l1 = "Bueno, está bien. Si ir al barco te ayuda a librarte de esos sueños y visiones, te ayudaré. Sube a bordo. Tan pronto como termine mis asuntos, partiremos hacia la bahía.";
			link.l1.go = "LEDR_Gonsalo_10";
		break;
		
		case "LEDR_Gonsalo_10":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_1");
			AddQuestRecord("LEDR", "2");
			AddQuestUserData("LEDR", "sSex", GetSexPhrase("ся","ась"));
		break;
		
		case "LEDR_Gonsalo_11":
			if (GetHour() >= 7 && GetHour() <= 19)
			{
				dialog.text = "Ahí está... Alguna vez fue el orgullo de la flota mercante española, y ahora no es más que un montón de tablones podridos que apenas se mantienen unidos.";
				link.l1 = "Rara vez se ve a un gigante así derrotado, tendido en la orilla. ¿Cómo habrá acabado aquí?";
				link.l1.go = "LEDR_Gonsalo_12";
				link.l2 = "Entonces echemos un vistazo. Quizás realmente logres encontrar algo aquí.";
				link.l2.go = "LEDR_Gonsalo_20_1";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "No quiero parecer desagradecido ni cobarde... pero ahora mismo no me siento a gusto aquí. Volvamos cuando salga el sol.";
				link.l1 = "Está bien, amigo, como digas.";
				link.l1.go = "exit";
				NextDiag.TempNode = "LEDR_Gonsalo_11";
			}
		break;
		
		case "LEDR_Gonsalo_12":
			dialog.text = "Salimos entonces de Santiago y pusimos rumbo a Sevilla. No llevábamos mucha carga, pero sí un pasajero: un pez gordo, un obispo en persona. A la tripulación, para ser sincero, ese viaje no le hacía ninguna gracia... pero ¿cuándo nos han preguntado algo? Nunca llegamos al océano. Cerca de Turks nos atacó una goleta pirata: rápida, ágil, armada hasta los dientes. No eran unos muertos de hambre, sino auténticos lobos de mar. Al principio el capitán quiso dar media vuelta —no quería arriesgar la vida del obispo—. Pero con ese viento no podíamos virar, y desde el sur ya venía una tormenta. Así que no hubo elección: empezó la batalla.";
			link.l1 = "Quedar atrapado entre dos fuegos no es nada envidiable. ¿Y qué pasó después?";
			link.l1.go = "LEDR_Gonsalo_13";
			AddCharacterExpToSkill(pchar, "Sailing", 200);
		break;

		case "LEDR_Gonsalo_13":
			dialog.text = "La pelea no duró mucho. Logramos derribarles el palo de mesana, pero los piratas no se quedaron atrás: una bala perdida cortó el cabo del timón y, como si el mismísimo diablo lo hubiera querido, el barco quedó de proa hacia la tormenta que se acercaba. Venía tan rápido que los piratas —¡que les caiga un grillete en la vela mayor!— prefirieron huir y se escondieron en una de las bahías de Turcas. A nosotros no nos quedaba más que esperar a que la tormenta nos engullera. El capitán ordenó arriar las velas y reemplazar el cabo del timón, pero ya era demasiado tarde.";
			link.l1 = "Así que la tormenta los atrapó cerca de Turks, los arrastró hasta aquí y al final los arrojó a la orilla?";
			link.l1.go = "LEDR_Gonsalo_14";
		break;

		case "LEDR_Gonsalo_14":
			dialog.text = "Así fue exactamente. En el barco reinaba el verdadero infierno. El viento arrancaba los aparejos, los mástiles caían uno tras otro, destrozaban la cubierta y aplastaban a la gente. Al que no le daba tiempo a amarrarse, lo arrastraba la mar; al que sí, lo aplastaban los escombros. En la bodega no era mejor: cañones, cajas y balas iban de un lado a otro como demonios, triturando todo a su paso. Cuando, al final, nos arrojó la tormenta a la orilla, yo estaba inconsciente. Desperté ya en la arena. Me encontró el contramaestre Sergio. Con él iban otros dos.";
			link.l1 = "No es mucho, para un barco tan grande.";
			link.l1.go = "LEDR_Gonsalo_15";
		break;

		case "LEDR_Gonsalo_15":
			dialog.text = "Ah, capitán... Cuántos cadáveres había allí... Enseguida entendimos que no podíamos quedarnos. Las olas podían llevarse el barco y a nosotros detrás. Cerca encontramos una cueva; allí, agotados, nos dormimos apenas tocamos el suelo. Cuando desperté, en la cueva ya no estaban ni Sergio ni esos dos.\nRegistré toda la playa, pero lo juro por el trueno, no estaban allí. Subir solo al barco me resultó imposible, así que decidí adentrarme en la isla. Así llegué a Sharptown, donde por mi ingenuidad me metí en líos.\nQuería saber algo de los sobrevivientes, empecé a contarle a todos lo que nos había pasado. Pero a esos bribones no les interesaba ni yo ni la tripulación, sino el botín que podían saquear del barco. El rumor se esparció rápido por toda la isla y hordas de esos ladrones se lanzaron hacia allí.";
			link.l1 = "Entonces, ¿todavía no sabes qué fue de esas personas?";
			link.l1.go = "LEDR_Gonsalo_16";
		break;

		case "LEDR_Gonsalo_16":
			dialog.text = "Volver al barco era demasiado peligroso. Los que se atrevieron a ir allí en busca de botín podían no repartirse el tesoro y disparar a cualquiera que estuviera cerca... por accidente. O tal vez — y no tan accidentalmente\nPor el mar que me vio nacer, pasé una semana entera en la taberna, preguntando a todos los que habían estado en la bahía. Pero nadie había oído nada ni de mis muchachos, ni de lo que les pasó\nAl final, me resigné a la idea: parece que soy el único que sobrevivió a esa maldita tormenta. Simplemente la suerte estuvo más de mi lado que del resto. O quizá... todo se deba al amuleto que una vez me regaló el joven, por entonces capitán, Eugenio de la Torre. Siempre lo llevaba conmigo. Y, maldita sea, parece que de verdad traía buena fortuna.";
			link.l1 = "¿Y dónde está ahora? Parece que de los esqueletos no protege, je...";
			link.l1.go = "LEDR_Gonsalo_17";
		break;

		case "LEDR_Gonsalo_17":
			dialog.text = "Se me cayó del cuello cuando estábamos reforzando la parte superior del pozo en mi patio. Un tronco me rozó el cuello y el amuleto cayó al agua. El pozo ya estaba lleno, y nadie se pondría a vaciarlo por una simple baratija.";
			link.l1 = "¿Y desde entonces empezaste a tener pesadillas?";
			link.l1.go = "LEDR_Gonsalo_18";
		break;

		case "LEDR_Gonsalo_18":
			dialog.text = "¡Mil demonios!   Nunca lo había pensado, pero así fue.   En cuanto terminamos de construir el pozo, empezaron las pesadillas.";
			link.l1 = "Qué coincidencia curiosa. Bueno, ahora estás aquí, tal como querías. ¿Y qué piensas hacer ahora?";
			link.l1.go = "LEDR_Gonsalo_19";
		break;

		case "LEDR_Gonsalo_19":
			dialog.text = "No lo sé, capitán... No lo sé. Vamos a echar un vistazo primero; la sensación de que debo encontrar algo aquí solo se ha hecho más fuerte.";
			link.l1 = "Bien. Espero que no hayamos venido aquí en vano.";
			link.l1.go = "LEDR_Gonsalo_20";
		break;
		
		case "LEDR_Gonsalo_20":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_3");
		break;
		
		case "LEDR_Gonsalo_20_1":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_3");
			pchar.questTemp.LEDR_NoStory = true;
		break;
		
		case "LEDR_Gonsalo_21":
			dialog.text = "Escucha... Esta sensación no hace más que intensificarse. Es como si estuviera a un paso de algo que debo descubrir. Necesito subir a ese barco. Por el mar, juro que allí hay algo que me ayudará a entender por qué ese maldito esqueleto no me deja en paz.";
			link.l1 = "¿Así que quizás no te apresurabas a venir aquí sin motivo? ¿Escondiste algo valioso en el barco y ahora has decidido volver a por tu tesoro?";
			link.l1.go = "LEDR_Gonsalo_22";
		break;

		case "LEDR_Gonsalo_22":
			dialog.text = "¿Qué tontería es esa? ¿Crees que habría cruzado todo el archipiélago hasta aquí por un par de doblones después de cuarenta años? Si te hubiera tocado ver a ese esqueleto aunque fuera una vez, ni se te pasarían esas ideas por la cabeza.";
			link.l1 = "Vale, vale, no te enfades. ¿Y cómo piensas subir al barco?";
			link.l1.go = "LEDR_Gonsalo_23";
		break;

		case "LEDR_Gonsalo_23":
			dialog.text = "En la popa hay una puerta secreta. El capitán la hizo él mismo, por si el abordaje no sale a nuestro favor. Por todos los rayos, yo solo no podría arrastrar mi viejo cuerpo por ahí, pero entre dos...";
			link.l1 = "Bien, muéstrame el camino y terminemos con esto.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_5");
		break;
		
		case "LEDR_Gonsalo_24":
			DelLandQuestMark(npchar);
			dialog.text = "¡Un maldito cañonazo en el cuello, qué carnicería! Por suerte estos no eran tan salvajes como el que me visita cada mañana. ¿Y bien, ahora sí me crees?";
			link.l1 = "Después de ver eso, es difícil *no* creerte. ¿Estás bien?";
			link.l1.go = "LEDR_Gonsalo_24_1";
		break;

		case "LEDR_Gonsalo_24_1":
			dialog.text = "Creo que sí. Malditos no-muertos... las piernas se me doblaron como mástiles rotos.";
			link.l1 = "Bueno, si estás entero, basta de quedarte ahí tirado. Dame la mano, te ayudo a levantarte.";
			link.l1.go = "LEDR_Gonsalo_24_2";
		break;

		case "LEDR_Gonsalo_24_2":
			CharacterTurnByChr(npchar, CharacterFromID("blaze"));
			dialog.text = "...";
			link.l1 = "Mucho mejor. Parece que no somos los primeros que sabían cómo llegar aquí.";
			link.l1.go = "LEDR_Gonsalo_25";
			LAi_Fade("LEDR_GonsaloStay", "");
		break;
		
		case "LEDR_Gonsalo_25":
			dialog.text = "Parece que son mis muchachos. Los que sobrevivieron a la tormenta... Reconocí el chaleco de Sergio... o mejor dicho, lo que quedó de él. Así que volvieron, ya sea para buscar sobrevivientes o para enterrar a los muertos. Pero parece que esa misma criatura los mató a ellos también.";
			link.l1 = "Es sorprendente que sólo hayan quedado jirones del chaleco. Y nada más.";
			link.l1.go = "LEDR_Gonsalo_26";
		break;

		case "LEDR_Gonsalo_26":
			if(CheckAttribute(pchar, "questTemp.LEDR_NoStory"))
			{
			dialog.text = "Ni rastro de la sotana de nuestro pasajero — el obispo. Por la llave apretada en su mano, diría que ese pobre diablo de allá es él. Nunca se separaba de esa llave, ni un segundo. Parece que no tuvo más suerte que los demás. Por el mar — estos muertos vivientes no estaban aquí por casualidad. Algo los retiene... o están vigilando algo.";
			DeleteAttribute(pchar, "LEDR_NoStory");
			}
			else
			{
			dialog.text = "Ni rastro de la sotana del obispo. Por la llave apretada en su mano, diría que ese pobre diablo de allá es él. Nunca se separaba de esa llave, ni un segundo. Parece que no tuvo más suerte que los demás. Por el mar — estos muertos vivientes no estaban aquí por casualidad. Algo los retiene... o están vigilando algo.";
			}
			link.l1 = "Yo también tengo la sensación de que debemos encontrar algo aquí. Terminemos con esto cuanto antes — no quiero quedarme aquí más de lo necesario.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_8");
		break;
		
		case "LEDR_Gonsalo_27":
			dialog.text = "¿Y bien, capitán? ¿Ha conseguido encontrar algo?";
			link.l1 = "Parece que este era el cofre del obispo. Yo lo he enco"+GetSexPhrase("él","ла")+" hay algo en él. Mira.";
			link.l1.go = "LEDR_Gonsalo_28";
		break;

		case "LEDR_Gonsalo_28":
			dialog.text = "Velázquez... Rayos y centellas... ¡He visto este diario en mis sueños! ¡Era justo el que hojeaba el capitán antes de...";
			link.l1 = "...";
			link.l1.go = "LEDR_Gonsalo_29";
		break;

		case "LEDR_Gonsalo_29":
			dialog.text = "¡Demonios, es como si me quemara las manos!";
			link.l1 = "¿Te quema las manos? Vamos, no exageres, es sólo un viejo diario. ¿O de verdad crees que encierra alguna fuerza oscura?";
			link.l1.go = "LEDR_Gonsalo_30";
		break;

		case "LEDR_Gonsalo_30":
			dialog.text = "¡Lo juro por todos los santos, no estoy bromeando! Este maldito diario parece arderme en las manos. ¡Hay que destruirlo! Romperlo, quemarlo, hundirlo, ¡lo que sea! No, mejor quemarlo. Sí, quemarlo para que no quede ni ceniza de él.";
			link.l1 = "Como desees. Entonces vamos a la orilla, encenderemos una fogata y arrojaremos esta crónica de fechorías al fuego.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_10");
		break;
		
		case "LEDR_Gonsalo_31":
			dialog.text = "Bueno, eso es todo... Como si me hubieran quitado un peso del alma.";
			link.l1 = "¿Crees que ahora todo ha terminado?";
			link.l1.go = "LEDR_Gonsalo_32";
			TakeItemFromCharacter(pchar, "LEDR_book");
		break;

		case "LEDR_Gonsalo_32":
			dialog.text = "Quién sabe... Pero te juro por el mar, hacía mucho que no respiraba tan libremente. Como si por fin me hubieran perdonado una vieja deuda. Aunque aún así... Ojalá nunca hubiera visto ese maldito diario. Y no supiera lo que está escrito en él.";
			link.l1 = "No es de extrañar que hayas soñado con eso. Aunque no participaste en todo aquello, eres el único de los vivos que estuvo relacionado de alguna manera con el diario.";
			link.l1.go = "LEDR_Gonsalo_33";
		break;
		
		case "LEDR_Gonsalo_33":
			dialog.text = "Ni el oro ni la fe justifican lo que hicieron los hombres bajo el mando de Velázquez. Y me alegra que todo lo que podía recordarlo haya ardido. Cosas así no deben caer en manos de quienes quieran seguir su ejemplo.";
			link.l1 = "Velázquez es solo uno de muchos. ¿Quién sabe cuántos diarios como este andan circulando por la vieja Europa, alimentando la codicia y la impunidad de los nuevos conquistadores? Al menos hay algo que consuela: este ya no envenenará a nadie más. Por cierto, en el cofre del obispo no solo estaba el diario, sino también una buena reserva de doblones: trescientos. La mitad de ellos te corresponde por derecho.";
			link.l1.go = "LEDR_Gonsalo_34_share";
			link.l2 = "Velázquez pagó por sus pecados, y si alguien decide seguir su camino, le espera el mismo destino. Tarde o temprano, el destino le dará a cada uno lo que merece.";
			link.l2.go = "LEDR_Gonsalo_34_silence";
		break;
		
		case "LEDR_Gonsalo_34_share":
			dialog.text = "Si es así, no me niego. Todos necesitamos dinero, y yo ahora más que nunca. Ya no me aceptan como marinero en ningún barco, me he hecho viejo. Así que gracias, capitán, por no darme la espalda."+GetSexPhrase("ся","ась")+", como los demás.";
			link.l1 = "Confieso que al principio tu historia me pareció el delirio de un loco. Pero la contaste con tanta convicción que, quieras o no, uno acaba creyéndola. Aun así, la aparición de esos no-muertos indios me tomó por sorpresa.";
			link.l1.go = "LEDR_Gonsalo_35_1";
			link.l2 = "Solo quise comprobar si no estabas loco. Ya sabes, no es tan fácil creer en historias como esas.";
			link.l2.go = "LEDR_Gonsalo_35_2";
			RemoveDublonsFromPCharTotal(150);
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
			npchar.quest.LEDR_share = true;
		break;
		
		case "LEDR_Gonsalo_34_silence":
			dialog.text = "Quisiera creerlo... Pero te juro por el mar, he visto a demasiados a quienes la suerte sonreía, pese a todas sus malas acciones. Tal vez el castigo los alcance, pero ya será allá, en el mismísimo infierno. Y a ti, gracias, capitán. Por no darme la espalda, escucharme y acompañarme. Eso, sabes, vale mucho.";
			link.l1 = "Te confieso que al principio tu historia me pareció el delirio de un loco. Pero la contaste con tanta convicción que, quieras o no, uno acaba creyéndola. Aun así, la aparición de esos muertos vivientes indios me tomó por sorpresa.";
			link.l1.go = "LEDR_Gonsalo_35_1";
			link.l2 = "Solo quise comprobar si no estabas loco. Ya sabes, no es tan fácil creer en historias como esas.";
			link.l2.go = "LEDR_Gonsalo_35_2";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;

		case "LEDR_Gonsalo_35_1":
			dialog.text = "Ahora sabes lo que sentí cuando vi por primera vez a esos no-muertos. Espero que esto haya terminado para siempre... De lo contrario, dudo que sobreviva a otro encuentro así.";
			link.l1 = "Bueno, ya que hemos terminado aquí, es hora de irnos. Sube a bordo, te dejaré en el puerto de Sharptown.";
			link.l1.go = "LEDR_Gonsalo_36";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "LEDR_Gonsalo_35_2":
			dialog.text = "Ahora sabes lo que sentí cuando vi a esos no-muertos por primera vez. Espero que esto haya terminado para siempre... De lo contrario, dudo que sobreviva a otro encuentro así.";
			link.l1 = "Bueno, ya que hemos terminado aquí, es hora de irnos. Sube a bordo, te dejaré en el puerto de Sharptown.";
			link.l1.go = "LEDR_Gonsalo_36";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "LEDR_Gonsalo_36":
			DialogExit();
			AddDialogExitQuestFunction("LEDR_12");
		break;
		
		case "LEDR_Gonsalo_37":
			dialog.text = "Gracias otra vez, capitán "+GetFullName(pchar)+". Por el mar, esa extraña sensación se ha ido, y espero que se haya llevado consigo su maldito saco de huesos. ¿Quizá nos tomamos una jarra, eh?";
			link.l1 = "Gracias por la invitación, Gonzalo, pero todavía tengo mucho trabajo. Quizá en otra ocasión. Bebe por los dos.";
			link.l1.go = "LEDR_Gonsalo_38";
		break;
		
		case "LEDR_Gonsalo_38":
			if (CheckAttribute(npchar, "quest.LEDR_share"))
			{
				dialog.text = "Lo entiendo. Pero te diré algo, capitán: después de todo lo que hemos pasado juntos, no puedo irme así, sin darte las gracias. No sería de buen cristiano. Toma, aquí tienes. De joven más de una vez fui tras tesoros, te lo juro por el mar. Pero ahora la salud ya no es la misma, y la espalda me falla. En cambio tú eres joven, un lobo de mar experimentado. Lo conseguirás sin problema. Buena suerte, "+GetFullName(pchar)+", buen viento y siete pies bajo la quilla.";
				link.l1 = "Gracias, Gonzalo. Buena suerte para ti también, adiós.";
				AddMapPart();
			}
			else
			{
				dialog.text = "Bueno, parece que ha llegado la hora de despedirse. Buen viento y mar en calma, capitán "+GetFullName(pchar)+"!";
				link.l1 = "Que le vaya bien, Gonzalo.";
			}
			link.l1.go = "exit";
			AddDialogExitQuestFunction("LEDR_14");
		break;
		
		
		
	}
}