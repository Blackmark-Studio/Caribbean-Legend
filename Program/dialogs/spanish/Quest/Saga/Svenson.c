// Ян Свенсон - пиратский барон Западного Мэйна
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, iTemp;
	string sTemp, sStr;

	DeleteAttribute(&Dialog,"Links");

	makeref(NPChar,CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);
	
	switch(Dialog.CurrentNode)
	{
		case "First time":
			if (CheckAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Svenson")) {
				if (pchar.questTemp.HelenDrinking.Result == "won") {
					dialog.text = "Ah, Charles. Gracias por venir. Solo quería agradecerte por pasar tiempo con Helen. La chica necesitaba sanar sus heridas, ¡y escuché que tú también lo pasaste bien, ja-ja! ¡Maldita sea, hasta estoy celoso!";
					link.l1 = "¿No estás molesto? ¿Por el barril y... todo lo demás?";
					link.l1.go = "after_drinking";
				} else {
					dialog.text = "Ah, Charles. Gracias por pasarte por aquí. Solo quería agradecerte por pasar tiempo con Helen. La muchacha necesitaba sanar sus heridas, y he oído que tú también lo pasaste bien, ¡ja-ja! ¡Buena suerte en Cartagena!";
					link.l1 = "Sí, también me alegra que todo haya salido bien ayer. Hasta que nos volvamos a encontrar, Jan.";
					link.l1.go = "exit";
				}
				
				DeleteAttribute(pchar, "questTemp.HelenDrinking.Dialogs.Svenson");
				break;
			}
		
			if(CheckAttribute(pchar, "questTemp.Saga"))
			{
				if (CheckAttribute(pchar, "questTemp.Saga_Late")) // отсекание при провале по времени
				{
					dialog.text = "Oh, mi amigo "+pchar.name+"¡Un placer verte! ¿Qué puedo hacer por ti?";
					link.l1 = "Solo pasaba a ver cómo te va.";
					link.l1.go = "exit";
					if(CheckAttribute(npchar, "quest.trade_bakaut")) // торговля бакаутом
					{
						if (GetDataDay() == 14 || GetDataDay() == 28)
						{
							link.l2 = "Jan, me gustaría comprar sándalo.";
							link.l2.go = "trade_bakaut";
						}
					}
					break;
				}
				if(pchar.questTemp.Saga == "svenson")
				{
					dialog.text = "¿Cómo puedo ayudarle, señor?";
					link.l1 = "Me gustaría pedir tu ayuda, Diablo del Bosque.";
					link.l1.go = "saga";
					break;
				}
				if(pchar.questTemp.Saga == "svenson1")
				{
					dialog.text = "Ajá, mi amigo "+pchar.name+"¡Qué novedades!";
					link.l1 = "He logrado aprender muchas cosas interesantes del Verdugo.";
					link.l1.go = "saga_11";
					break;
				}
				if(pchar.questTemp.Saga == "svenson2")
				{
					dialog.text = "Entonces, "+pchar.name+", ¿has hablado con Gladys?";
					link.l1 = "Sí, lo hice. Jan, echa un vistazo aquí... ¿Puedes decirme algo sobre este trozo de pergamino aquí?";
					link.l1.go = "saga_17";
					break;
				}
				if(pchar.questTemp.Saga == "helena1" || pchar.questTemp.Saga == "helena2" || pchar.questTemp.Saga == "svenson_wait")
				{
					dialog.text = "Aún no tengo nada nuevo que contarte, "+pchar.name+". Pero estoy trabajando en una solución para nuestro asunto. Vuelve más tarde.";
					link.l1 = "Está bien, Jan. Te veré más tarde.";
					link.l1.go = "exit";
					break;
				}
				if(pchar.questTemp.Saga == "baronsquests") // старт трех квестов баронов
				{
					// первая проверка времени. Свенсон очень недоволен растяпством ГГ. Счищаем Элен, к Свенсону доступ закроем
					if (CheckAttribute(pchar, "questTemp.Saga.Late"))
					{
						dialog.text = ""+pchar.name+", me has decepcionado por completo. Esperaba que fueras un hombre serio, pero resulta que eres solo un muchacho tonto. ¿Dónde has estado todo este tiempo, eh? ¡Los ingleses reclamaron Isla Tesoro mientras tú hacías Dios sabe qué!\n¡Todos mis planes están arruinados! Para ser honesto, casi me había olvidado de tu existencia y no quiero que me la recuerden. ¡Lárgate!";
						link.l1 = "¡No puedo creerlo!";
						link.l1.go = "saga_l1";
					}
					else
					{
						dialog.text = "Ahí estás, "+pchar.name+". He dado vueltas a nuestra situación un poco. No lo llamaría necesariamente un plan, pero...";
						link.l1 = "Soy todo oídos, Jan.";
						link.l1.go = "saga_25";
					}
					break;
				}
				if(pchar.questTemp.Saga == "baronsquests_1") // идут три квеста баронов
				{
					dialog.text = "¿Cómo van las cosas? ¿Hay algo en lo que pueda asistirte?";
					if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "after_marlow")
					{
						link.l3 = "He hablado con el Pastor Negro. Lamentablemente, el resultado de nuestra conversación me ha hecho volver a ti en busca de consejo, estoy perplejo.";
						link.l3.go = "shark_hunt_2";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.SharkHunt") && pchar.questTemp.Saga.SharkHunt == "LSC" && !CheckAttribute(pchar, "questTemp.Saga.BaronReturn"))
					{
						link.l3 = "He encontrado a Dios y tuvimos una charla agradable. Me contó muchas cosas interesantes, pero desafortunadamente no llegamos al meollo del asunto.";
						link.l3.go = "shark_hunt_7";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "third_teleport")
					{
						link.l3 = "Oh, Jan. Tengo tanto que contarte que me tomaría toda la noche transmitírtelo todo, así que seré breve.";
						link.l3.go = "return_LSC";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "shamane" && !CheckAttribute(npchar, "quest.shamane"))
					{
						link.l3 = "Recogí a Nathaniel Hawk de la Isla de la Justicia. Está en mi barco ahora mismo.";
						link.l3.go = "nathaniel";
					}
					if (CheckAttribute(pchar, "questTemp.Saga.BaronReturn") && pchar.questTemp.Saga.BaronReturn == "treatment")
					{
						link.l3 = "He dejado a Nathaniel Hawk en el pueblo Miskito para ser tratado por un chamán llamado Ojo de Serpiente. Me prometió restaurar la salud de Nathan.";
						link.l3.go = "nathaniel_2";
					}
					link.l4 = "No hay mucho que contarte en este momento. Solo pasaba para ver cómo estás.";
					link.l4.go = "exit";
					break;
				}
				if(pchar.questTemp.Saga == "fail_centurion") // провал - потоплен Центурион
				{
					dialog.text = "¿Cuáles son las noticias, "+pchar.name+"¿Cómo van las cosas?";
					link.l1 = "Ah, no podría ser peor. He hecho tanto trabajo... Encontré a Jackman, tiramos las vainas, y lo ahogué como al mayor imbécil junto con todo lo que podría haber estado dentro de su camarote. Ahora no tengo nada que me ayude a limpiar el nombre de Shark y ponerle presión a Barbazon. Me temo que es una causa perdida, Jan.";
					link.l1.go = "saga_f_1";
					break;
				}
				if(pchar.questTemp.Saga == "calendar") // квесты баронов завершены
				{
					// вторая проверка времени. Отбираем Элен, со Свенсоном нейтральные отношения - ну не выщло и не вышло, хоть попытались. Данни и Натана - в Марун-Таун
					if (CheckAttribute(pchar, "questTemp.Saga.Late"))
					{
						dialog.text = "¡He oído sobre tus heroicas hazañas! Dannie me contó la versión corta. Por cierto, ahora somos amigos. ¡Y Nathan ha cambiado por completo! Toda su depresión se desvaneció cuando vio su 'Centurión'.\nPero tengo malas noticias para ti, "+pchar.name+" Hemos perdido tanto tiempo que los derechos de herencia del testamento de Sharp se han esfumado hace tiempo y la Isla Tesoro se ha convertido en una base militar inglesa. Ya no puedo hacer nada para ayudarte con Levasseur."link.l1 ="Estoy absolutamente sin palabras... Hemos pasado por tantos problemas para nada. ¿Realmente no hay nada que podamos hacer?";
						link.l1.go = "saga_l2";
					}
					else
					{
						dialog.text = "¡He oído todo sobre tus heroicidades! Dannie me informó. Por cierto, ya hemos hecho las paces. No podrías ni reconocer a Nathan. Tan pronto como vio su 'Centurión', dejó atrás sus gruñidos como un mal sueño...";
						link.l1 = "¿Nathan está bien de nuevo? ¡Me alegra oírlo!";
						link.l1.go = "saga_26";
					}
					break;
				}
				if(pchar.questTemp.Saga == "mine") // рудник взят
				{
					dialog.text = "Aquí estás, "+pchar.name+"¡Ahora tengo algo que decirte!";
					link.l1 = "Hola, Jan. ¡Estoy eufórico! ¿Qué se dice? Espero que sea algo positivo.";
					link.l1.go = "saga_32";
					break;
				}
				if(pchar.questTemp.Saga == "mine_1") // рудник взят совместно
				{
					dialog.text = "Aquí estás, "+pchar.name+"¡Descansaste un poco? Y, ¿puedo concluir que estás una vez más listo para grandes aventuras?";
					link.l1 = "Hola, Jan. Sí, estoy listo.";
					link.l1.go = "saga_32a";
					break;
				}
				if(pchar.questTemp.Saga == "late_l3") // провал по времени у адвоката
				{
					dialog.text = "¿Qué noticias hay, "+pchar.name+"¿Cómo van las cosas?";
					link.l1 = "Oh. Las cosas están absolutamente horribles. He luchado con uñas y dientes, pero aún así terminé perdiendo. Como recordarás, el testamento de Sharp tenía un límite de tiempo. Bueno, ese tiempo se ha acabado y la Isla Tesoro es ahora una base militar inglesa. Es una causa perdida, Jan.";
					link.l1.go = "saga_l3";
					break;
				}
				if(pchar.questTemp.Saga == "bakaut") // пришёл от адвоката за деньгами
				{
					dialog.text = "Saludos, "+pchar.name+"¡Buenas noticias: se ha celebrado la reunión del Consejo y los Hermanos de la Costa han encontrado un nuevo líder!";
					link.l1 = "Buenas tardes, Jan. Estoy feliz por ti.";
					link.l1.go = "saga_44";
					break;
				}
				if(pchar.questTemp.Saga == "sellbakaut" && GetSquadronGoods(pchar, GOOD_SANDAL) >= 1) // отдает бакаут
				{
					dialog.text = "Bueno, "+pchar.name+" ¿Has alcanzado a Molligan?";
					link.l1 = "Lo hice. Él fue quien robó tu sándalo.";
					link.l1.go = "saga_55";
					break;
				}
				if(CheckAttribute(npchar, "quest.bakaut") && GetNpcQuestPastDayParam(npchar, "bakaut_date") >= 1) // за деньгами за бакаут
				{
					dialog.text = "A tiempo como siempre, "+pchar.name+". Vendí la sándalo que me trajiste.";
					link.l1 = "Excelente. ¿Cuánto dinero ganaste?";
					link.l1.go = "saga_57";
					break;
				}
				if(CheckAttribute(npchar, "quest.bakaut_sum")) // сам продал бакаут
				{
					dialog.text = "Bueno, "+pchar.name+"¿Alcanzaste a Molligan?";
					link.l1 = "Así fue. Él fue quien robó tu sándalo. También me encontré con su comprador. Era algún comandante militar holandés. Le vendí el producto a él.";
					link.l1.go = "saga_59";
					link.l2 = "Lo hice. Traté de obligarlo a mostrarme su bodega de carga... nos metimos en una refriega y... ahora no hay más Molligan. Pero no hay nada que puedas ver en la bodega excepto ébano y caoba.";
					link.l2.go = "saga_59_1";
					break;
				}
				if(CheckAttribute(npchar, "quest.jessika")) // информация о Джессике
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". ¿Qué hay de nuevo?";
					link.l1 = "Jan, me gustaría hablar contigo sobre un asunto. He estado investigando el pasado de la madre de Helen, Beatrice, y me encontré con alguien que conoces muy bien. Según me han dicho...";
					link.l1.go = "saga_62";
					break;
				}
				if(pchar.questTemp.Saga == "lastpages") 
				{
					dialog.text = TimeGreeting()+", "+pchar.name+". ¿Cómo van las cosas? ¿Puedo felicitarte, juzgando por tu cara? ";
					link.l1 = "Sí. Finalmente he logrado resolver este lío. Helen ha recibido todos los derechos sobre Isla Tesoro. ¡Nunca más nadie se atreverá a invadir el refugio de los Hermanos de la Costa!";
					link.l1.go = "saga_82";
					break;
				}
				if (pchar.questTemp.Saga == "end") sTemp = "¡Oh, mi amigo "+pchar.name+"! ¡Me alegro de verte! ¿Qué le trae por aquí?";
				else sTemp = "¿Qué deseas, "+pchar.name+"?";
				dialog.text = sTemp;
				link.l1 = "No, Jan. Nada en este momento.";
				link.l1.go = "exit";
				if(CheckAttribute(npchar, "quest.trade_bakaut")) // торговля бакаутом
				{
					if (GetDataDay() == 14 || GetDataDay() == 28)
					{
						link.l2 = "Jan, me gustaría comprar algo de tu sándalo.";
						link.l2.go = "trade_bakaut";
					}
				}
				NextDiag.TempNode = "First time";
			}
			else
			{
				// заглушка Элен
				if(startHeroType == 4)
				{
					dialog.text = "Elena, hola, querida. ¿Qué novedades tienes? ¿Había algo que querías?";
					link.l1 = "¡Hola, Jan! Todo igual, solo pasé a verte.";
					link.l1.go = "exit";
					NextDiag.TempNode = "First time";
					break;
				}
				dialog.text = "¿Puedo ayudarte con algo?";
				link.l1 = "No, estoy bien.";
				link.l1.go = "exit";
				NextDiag.TempNode = "First time";
			}
		break;
		
		case "saga":
			dialog.text = "¡Te conozco, maldita sea! ¡Eres el valiente capitán que salvó a Rumba y enfrentó de frente los cañones de la corbeta inglesa! ¡Qué alegría verte! Helen es como una hija para mí. A partir de hoy, te estaré eternamente agradecido. Puedes llamarme Jan o Svenson, si lo prefieres. ¿Qué puedo hacer por ti?";
			link.l1 = "Necesito eliminar a Levasseur, el gobernador de Tortuga. Sé que llegar a él en su isla no será tarea fácil, así que vine a ti por consejo.";
			link.l1.go = "saga_1";
		break;
		
		case "saga_1":
			dialog.text = "¡Santo Dios, dónde estabas hace un par de años! Yo mismo planeaba llevar a cabo la misma escapada. Él arruinó todo el juego para nosotros con los franceses. Pero en aquellos días todo era diferente. Blaze estaba vivo, Shark tenía algo de autoridad, y Nathan tomaba todas las decisiones en Maroon Town... Ahora todo ha cambiado y, Dios sabe, no para mejor. ¿Sabes algo de nosotros, de los Hermanos?";
			link.l1 = "Acabo de llegar aquí, así que no sé prácticamente nada. Además del hecho de que tú y Jackman son parte del Consejo.";
			link.l1.go = "saga_2";
		break;
		
		case "saga_2":
			dialog.text = "¡Oh, no soporto a ese Jackman! Cuando llegó fue cuando comenzaron todos nuestros problemas. Contemplaré tu solicitud. De inmediato, nada me viene a la mente.";
			link.l1 = "Tengo algo interesante sobre Jackman.";
			link.l1.go = "saga_3";
		break;
		
		case "saga_3":
			dialog.text = "Mm. ¿Qué es eso?";
			link.l1 = "Jackman está buscando a Gladys Chandler y a su hija. Después de hablar con Higgins, he comenzado a pensar que está buscando a Rumba. Parece que Gladys no es la madre biológica de Helen y su apellido era Chandler antes de casarse con Sean McArthur.";
			link.l1.go = "saga_4";
		break;
		
		case "saga_4":
			dialog.text = "¡Maldita sea! Eso son malas noticias. Jackman es más fuerte que nunca ahora. Además, tengo un mal presentimiento de que no está trabajando solo. Tiene una sombra bastante ominosa detrás de él. Si realmente necesita a Helen, entonces la chica necesita desesperadamente un protector. Me temo que soy un poco demasiado viejo para hacerlo yo mismo...";
			link.l1 = "Eso no es todo. Jackman también está buscando a alguien llamado Henry el Verdugo, antiguo contramaestre del 'Neptune', de la tripulación del capitán Carnicero.";
			link.l1.go = "saga_5";
		break;
		
		case "saga_5":
			dialog.text = "¡Caramba! ¡Mis peores sospechas se han hecho realidad! Ese Carnicero y su 'Neptune' solían mantener aterrorizado a todo el archipiélago. No había Hermanos en aquel entonces, todos estaban por su cuenta. Ese hombre hizo muchas cosas malas, una persona querida para mí murió por su culpa.\nNunca tuve la oportunidad de conocerlo. El 'Neptune' fue hundido por una fragata inglesa, y el Carnicero fue ejecutado en San Juan. ¡Qué alivio! Aunque había mucha gente que admiraba su suerte y su temeraria valentía.\nJackman mismo era su mano derecha y primer oficial en el 'Neptune'. ¿Sorprendido? ¡Los ex-criminales se han convertido en héroes de la Nación, todo gracias a Cromwell! ¿Dónde ha quedado la buena y vieja Inglaterra?\nDebemos encontrar a Henry el Verdugo antes de que lo hagan los hombres de Jackman. Tal vez, él tenga la clave de este misterio, si es que sigue vivo.";
			link.l1 = "Apuesto a que te resultaría más fácil encontrar una aguja en un pajar. ¿Tienes al menos alguna pista?";
			link.l1.go = "saga_6";
		break;
		
		case "saga_6":
			dialog.text = "Conocí a Henry cuando era un niño. El hijo de una ramera de Cartagena, medio español, aunque siempre lo mantuvo en secreto. ¡Su madre estaba caliente! No puedo decir que fuera bonita, pero había muy pocas bailarinas de flamenco como ella. Todo el burdel veía los espectáculos de la desnuda Chica Gonzales y sus castañuelas.\nPobre chica. Cogió una mala enfermedad y murió como una vela. Fue entonces cuando persuadí a Henry para ir a Providence, donde rápidamente se hizo un nombre y se unió a la tripulación de Thomas Beltrope, un amigo cercano de Nicolas Sharp. Esos dos fueron los últimos perros de la reina Isabel y siempre trabajaban juntos. ¡Buenos tiempos!\nThomas navegó de regreso a Inglaterra cuando su compañero murió. Se llevó a su tripulación con él, pero Henry se quedó en el Caribe. Navegó bajo diferentes capitanes hasta que apareció Butcher. Por cierto, obtuvo su apodo por un alfanje que siempre mantenía cerca.";
			link.l1 = "¿Y qué nos dice esta información?";
			link.l1.go = "saga_7";
		break;
		
		case "saga_7":
			dialog.text = "Si el Verdugo ha decidido esconderse de los piratas, el mejor lugar para él sería en una ciudad española. Especialmente en su hogar en Cartagena, donde tiene amigos y parientes. Enrique era bastante religioso. Así que es poco probable que vaya a una iglesia de un santo diferente. Probablemente aún conserva el mismo nombre que ha tenido desde que era un niño, Enrique.";
			link.l1 = "Sí... Las ganancias son escasas, pero al menos es mejor que nada.";
			link.l1.go = "saga_8";
		break;
		
		case "saga_8":
			dialog.text = "¡Trata de encontrarlo, Charles! Pocos conocen las raíces españolas de Henry, así que aquí tenemos una pequeña ventaja. Pensaré en cómo persuadir a Rumba para que se una a tu tripulación. La chica tiene agallas, nunca ha servido bajo el mando de nadie excepto el de su padre.\nPero no tiene ni barco ni tripulación, y necesita ganarse la vida. Claro, seguiré ayudando a Gladys, como siempre he hecho, pero no podré mantener a Helen en Blueweld por mucho tiempo. Y encontrarás a un oficial así muy útil. Sean le enseñó todo lo que sabía y la crió como a un chico.\nMe sentiría mejor si estuviera bajo el mando de un capitán como tú.";
			link.l1 = "La Rumba ha demostrado ser bastante digna. Necesito más personas como ella en mi tripulación. Así que, si logras convencerla, la haré oficial. Pero primero quiero entender quién es realmente y por qué Jackman la necesita. Me temo que, a diferencia de Donovan, él no está interesado en sus encantos. Así que intentaré encontrar al Ahorcado, aunque no puedo prometer nada.";
			link.l1.go = "saga_9";
		break;
		
		case "saga_9":
			dialog.text = "Bueno, espléndido. Toma esta licencia de la Compañía Holandesa de las Indias Occidentales por tres meses. Escribe tu nombre allí, podría serte útil en tus búsquedas. Mientras tanto, pensaré en lo que has dicho sobre Levasseur y Tortuga.";
			link.l1 = "¡Gracias un millón! Este papel me va a ser muy útil. En ese caso, me voy a Cartagena entonces.";
			link.l1.go = "saga_10";
		break;
		
		case "saga_10":
			DialogExit();
			GiveNationLicence(HOLLAND, 90);
			AddQuestRecord("Saga", "14");
			pchar.questTemp.Saga = "cartahena";//идем в Картахену
			pchar.quest.Saga_Gonsales.win_condition.l1 = "location";
			pchar.quest.Saga_Gonsales.win_condition.l1.location = "Cartahena_town";
			pchar.quest.Saga_Gonsales.function = "Saga_CreateGonsalesB";
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", false);//открыть спальню Элен
			LocatorReloadEnterDisable("FortOrange_town", "reload6", true); // закрыть резиденцию Джекмана
			npchar.greeting = "svenson_3";
			
			AddQuestRecord("HelenDrinking", "1");
			pchar.questTemp.HelenDrinking.CanDrink = true;
			SetFunctionTimerConditionParam("HelenDrinking_NoVisit", 0, 0, 1, 24 - GetHour(), false);
			
			pchar.questTemp.Saga.HelenRelation = 0;
		break;
		
		case "saga_11":
			dialog.text = "¿Henry está muerto?  Espera, ¿lo mataste tú?";
			link.l1 = "¡No me mires con esos ojos abiertos! No tuve nada que ver con eso. Murió por su cuenta, de su conciencia podrida y su miedo a Jackman. El viejo pirata tenía problemas con su corazón y no le quedaba mucho tiempo de vida. Esto es lo que logré averiguar...";
			link.l1.go = "saga_12";
		break;
		
		case "saga_12":
			dialog.text = "¡Por favor, cuéntame!";
			link.l1 = "Hace veinte años, Henry se suponía que debía entregar un cofre de oro en nombre del Capitán Carnicero a la madre adoptiva de su hija biológica. No hay absolutamente ninguna duda de que esta madre adoptiva era la señora McArthur. En ese momento ella llevaba el apellido Chandler y vivía en Belice. Pero las circunstancias retuvieron al Verdugo en San Juan un mes entero adicional y cuando finalmente llegó a Belice, estaba en ruinas tras ser asaltado por los españoles, y la tía Gladys y Sean ya habían emprendido el camino bajo tu protección.";
			link.l1.go = "saga_13";
		break;
		
		case "saga_13":
			dialog.text = "";
			link.l1 = "Pasaron a Helen como su hija biológica y la criaron como propia. Henry les perdió la pista y se mantuvo en la sombra, consciente de la venganza de Jackman y viviendo desde entonces todos esos veinte años con miedo. Resulta que Jackman está buscando a la hija de su capitán. Pero por qué, no lo sé.";
			link.l1.go = "saga_14";
		break;
		
		case "saga_14":
			dialog.text = "Tal vez esté cumpliendo las órdenes de alguien...";
			link.l1 = "Dudo de ello. ¿Quién podría darle órdenes? El Carnicero está muerto. Su muerte está confirmada por documentos oficiales. Docenas, si no cientos de personas, fueron testigos de su muerte.";
			link.l1.go = "saga_15";
		break;
		
		case "saga_15":
			dialog.text = "Tal vez no se trate de quién es el padre de Helen. Tal vez todo esto tenga que ver con su madre biológica. Ya puedo adivinar quién era, pero temo reconocerlo. ¡Pero Gladys! ¿Cómo pudo mantener esto en secreto durante tantos años sin siquiera revelarlo a su esposo? Sean McArthur seguramente me lo habría contado. Nunca hemos tenido secretos que no nos hayamos contado el uno al otro.";
			link.l1 = "Voy a tener una charla sincera con Gladys. Creo que tengo los medios para hacerla hablar. ¡Hasta la próxima, Jan!";
			link.l1.go = "saga_16";
		break;
		
		case "saga_16":
			DialogExit();
			pchar.questTemp.Saga = "gladis1";
			sld = characterFromId("Gladis");
			sld.dialog.currentnode = "Gladis_history";
			AddQuestRecord("Saga", "21");
		break;
		
		case "saga_17":
			dialog.text = "¿De dónde sacaste eso!?";
			link.l1 = "Gladys me lo dio. Dijo que era la 'herencia de la madre de Helen'. No sabe su nombre. Algo me dice que esto no es un simple pedazo de papel.";
			link.l1.go = "saga_18";
		break;
		
		case "saga_18":
			dialog.text = "¿Recuerdas cuando te dije que tenía una corazonada sobre quién era la verdadera madre de Helen? Ahora estoy seguro de ello. Su nombre era Beatrice Sharp. Era la hija biológica de mi maestro y amigo Nicholas Sharp, la hermana declarada del fundador de nuestra Hermandad, Blaze Sharp, y copropietaria de Isla Tesoro. Es este fragmento de mapa lo que Jackman busca.";
			link.l1 = "¡Pues, qué te parece eso! Pero ¿por qué necesitaría la mitad de un mapa de la isla?";
			link.l1.go = "saga_19";
		break;
		
		case "saga_19":
			dialog.text = "La isla fue descubierta por Nicolas Sharp. La nombró Isla Tesoro, la cartografió y tomó posesión de ella a través de la Providence Island Company, donde tenía buenas conexiones.\nNicolas escribió en su testamento que la isla solo puede ser heredada por aquellos que presenten dos partes del mapa. Lo hizo para evitar discordias. Entregó las partes a Beatrice y a su hijastro Blaze antes de morir trágicamente a manos españolas.";
			link.l1 = "¡Pues maldito sea yo! Qué extraño.";
			link.l1.go = "saga_20";
		break;
		
		case "saga_20":
			dialog.text = "Tienes razón. No fue la mejor idea. Y un astuto notario añadió que la isla pertenecerá a la corona inglesa si nadie presenta ambas partes del mapa dentro de un año después de la muerte de los herederos.\nNadie lo vio venir en aquel entonces. Y ahora estamos pagando el precio de nuestra estupidez. Beatrice murió hace veinte años. Todos estos años han pasado y todavía no tenemos idea de dónde están su tumba y su parte del mapa. Blaze Sharp fue asesinado hace poco. Su parte también ha desaparecido.\nSi nadie presenta el mapa completo de Isla Tesoro a las autoridades dentro de un año, entonces Sharptown será reclamado por Inglaterra. Enviarán un gobernador con una guarnición allí y la Hermandad estará acabada.";
			link.l1 = "¿Qué sugieres que hagamos?";
			link.l1.go = "saga_21";
		break;
		
		case "saga_21":
			dialog.text = "No podemos permitir que esto suceda. Te necesito, Charles, te necesito para prevenir tal curso de acciones. Y solo podré ayudarte a eliminar a Levasseur después de que tomemos el control de Isla Tesoro y elijamos a Shark Dodson como el nuevo líder de la Hermandad. Él es el más digno de nosotros. Te ofrezco una alianza.\nY, por cierto, he hablado con Helen. Ella acordó unirse a tu tripulación.";
			link.l1 = "Me dejas sin opciones, Jan. No puedo volver a Francia sin restaurar el honor de mi familia. Y para lograrlo, necesito eliminar a Levasseur con o sin tu ayuda. Las muertes innecesarias no son lo que quiero y espero que puedas idear cómo tomar Tortuga sin derramar mucha sangre. Aunque, debo admitir que me gustaría aclarar el nebuloso pasado que rodea la herencia de Sharps yo mismo.";
			link.l1.go = "saga_22";
		break;
		
		case "saga_22":
			dialog.text = "¡Es agradable escuchar pensamientos sensatos! Encontraremos la manera correcta de tomar Tortuga. Eso te lo prometo. ¿Entonces, vamos?";
			link.l1 = "¡Vamos! Volveré un poco más tarde. Por ahora, piensa en por dónde empezar a abordar el problema.";
			link.l1.go = "saga_23";
		break;
		
		case "saga_23":
			dialog.text = "Vuelve dentro de dos o tres días. Para entonces creo que mi plan habrá llegado a su culminación. Y no olvides llevar a Helen contigo en tu barco. La pobre chica se está consumiendo sin el mar. Será una asistente leal y no tendrás que pensarlo dos veces para confiar en ella.";
			link.l1 = "Está bien, Jan. Iré a buscarla ahora mismo.";
			link.l1.go = "saga_24";
		break;
		
		case "saga_24":
			DialogExit();
			pchar.questTemp.Saga = "helena1";
			LocatorReloadEnterDisable("SantaCatalina_town", "reload1_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "reload2_back", true);
			LocatorReloadEnterDisable("SantaCatalina_town", "gate_back", true);//закрыть выходы из города
			LocatorReloadEnterDisable("SantaCatalina_houseSp3", "reload2", true);//закрыть спальню Элен
			AddQuestRecord("Saga", "23");
		break;
		
		case "saga_25":
			dialog.text = "Primero, necesitas encontrar al Tiburón. Quería deshacerse de Levasseur él mismo y te aseguro que tiene algunas ideas brillantes. Por supuesto, también podríamos persuadir a Marcus para que acepte el liderazgo. Después de todo, él es el guardián del Codex. Pero dudo que sea de alguna ayuda, ha limitado intencionadamente cualquier contacto con Levasseur y Tortuga. Un hombre de principios.\nNo tengo idea de dónde se esconden Steven y sus hombres, pero su fragata 'Fortuna' fue vista en Puerto Príncipe. Quizás Zachary Marlow, también conocido como el Pastor Negro, pueda indicarnos dónde buscar al Tiburón. Segundo, tenemos que ganar el apoyo de los otros barones para elegir a Dodson. Y para hacer eso, necesitamos recolectar sus fragmentos indios - los votos. El nuevo líder debe tener los cinco. Eso es lo que el Código nos dice que hagamos en caso de que el líder anterior haya muerto.\n¡Ridículo! Es hora de cambiar las leyes, pero solo el nuevo líder puede hacerlo. Ya tenemos mi voto. Creo que al Pastor Negro no le importa un comino quién está sentado en Sharptown. Espero que Jackman no haya hablado con él primero. También tenemos que persuadir a Tyrex y a Jacques Barbazon, que se odian entre sí. Pero todo es irrelevante hasta que averigüemos qué ha pasado con el Tiburón. Tercero, un día tendremos que matar a Jackman y reemplazarlo por alguien más. No negociará con nosotros.\n¡Qué lástima que Hawk esté muerto! La gente confiaba en él y podríamos usar su palabra. No encontraremos un mejor barón para Maroon Town. Es posible que Jackman tenga algo que ver con el asesinato de Blaze, así que él también es la pista para encontrar la segunda parte del mapa. Jacob no confía en nadie y lo más probable es que guarde la parte del mapa en su camarote en el 'Centurión'.\nLa familia de Hawk solía poseer la fragata, pero Jackman la reclamó al igual que la baronía de Hawk. Si encontramos la segunda parte del mapa en posesión de Jackman, sería un gran argumento para la elección de Steven. Especialmente para Marcus Tyrex, el guardián del Código, y su excesiva escrupulosidad en términos de honor. Le devolveremos a Helen sus derechos sobre Isla Tesoro tan pronto como adquiramos ambas partes del mapa.\nSin embargo, debemos tener cuidado, Jackman no se quedará de brazos cruzados viendo cómo buscas.";
			link.l1 = "Bueno... Estoy a punto de visitar al Pastor Negro. Cuéntame sobre él.";
			link.l1.go = "shark_hunt";
			pchar.questTemp.Saga = "baronsquests_1";
		break;
		
		case "shark_hunt":
			dialog.text = "¡Ni idea de lo que pasa por su mente! A veces parece un completo loco, pero aún así, creo que esto es solo una actuación astuta. Además, sus hombres están listos para luchar contra el mismo diablo en honor a su amado Pastor.\nHan establecido una especie de secta protestante cerca de la inquisición española en Cuba. Así que ni se te ocurra empezar a hablar de asuntos teológicos allí, no los aprobarán.";
			link.l1 = "Tendré eso en cuenta...";
			link.l1.go = "shark_hunt_0";
		break;
		
		case "shark_hunt_0":
			dialog.text = "Y, "+pchar.name+": no desperdicies ni un minuto de tu tiempo. Lo digo en serio. ¿Recuerdas la cláusula en el testamento que dice que si los herederos no reclaman la isla dentro del plazo de un año, entonces Isla Tesoro pasará a la corona inglesa, verdad? Bueno, el tiempo no está de nuestro lado ahora mismo. Cuando tú y yo nos vimos por última vez, solo quedaban unos once meses hasta que se acabara el tiempo.";
			link.l1 = "Lo recuerdo, Jan. Tienes razón, el tiempo es oro. ¡Estoy en ello!";
			link.l1.go = "shark_hunt_1";
		break;
		
		case "shark_hunt_1":
			DialogExit();
			AddQuestRecord("SharkHunt", "1");
			pchar.questTemp.Saga.SharkHunt = "begin";
			pchar.GenQuest.LigaAttack = "true"; // киллеры Лиги активированы
		break;
		
		case "shark_hunt_2":
			dialog.text = "Mm... ¿Qué te dijo Zachary?";
			link.l1 = "Antes de su desaparición, Shark vino a visitarlo y dejó su fragata con Zachary como garantía por un bergantín con algo de comida, y luego zarpó hacia algún lugar al noroeste de Cuba.";
			link.l1.go = "shark_hunt_3";
		break;
		
		case "shark_hunt_3":
			dialog.text = "Eso realmente es sospechoso. Continúa.";
			link.l1 = "Un mes después Dodson no regresó y el Pastor, según los términos del acuerdo, se quedó con la fragata para sí mismo y la vendió por un buen precio a un tipo llamado Paterson. En cuanto a nuestros asuntos, Zachary mencionó que Shark podría haber partido hacia alguna legendaria Isla de la Justicia, supuestamente ubicada no muy lejos al noroeste de Cuba.";
			link.l1.go = "shark_hunt_4";
		break;
		
		case "shark_hunt_4":
			dialog.text = "He oído hablar de la Isla de la Justicia. Dicen que hay una isla donde blancos y negros viven en paz, juntos como iguales. Patrañas difundidas por todo tipo de soñadores. Pero existe la posibilidad de que alguna especie de base de contrabandistas exista hacia el noroeste. Sus barcazas solían verse en mar abierto regularmente hace diez años. Traían diferentes tipos de mercancías a Cuba a cambio de comida.";
			link.l1 = "¿Tesoros por comida? El Pastor también me ha hablado de los bucaneros que transportan carne. Es prácticamente una contradicción andante.";
			link.l1.go = "shark_hunt_5";
		break;
		
		case "shark_hunt_5":
			dialog.text = "Estos chismes deben tener una fuente, esas barcas de contrabandistas o bucaneros navegaban hacia esa región por alguna razón. Recuerdo que el Tiburón me contó historias sobre su juventud, era una especie de esclavo en una extraña formación hecha de naufragios en medio del mar.\n¿Quizás ese sea nuestro lugar? No tengo idea. De todos modos, el Pastor tiene razón, hay algo ahí afuera, ya sea una base secreta o una isla a la que el Tiburón podría haber ido. Escucha, navega a Santo Domingo y encuentra a un científico llamado José Dios.\nEs un cartógrafo español. Una vez lo salvé de una escoria sucia, respeto a las personas educadas. Te ayudará, solo dile mi nombre. Ve a La Española, encuentra a Dios y habla con él.\nConoce perfectamente la geografía de nuestra región y si él no puede ayudarte, nadie podrá.";
			link.l1 = "Está bien, Jan. Suena como un plan. ¡Allá voy!";
			link.l1.go = "shark_hunt_6";
		break;
		
		case "shark_hunt_6":
			DialogExit();
			pchar.questTemp.Saga.SharkHunt = "dios";
			AddQuestRecord("SharkHunt", "3");
		break;
		
		case "shark_hunt_7":
			dialog.text = "Eso es una lástima. Esperaba que José nos echara una mano.";
			link.l1 = "Yo también contaba con eso, pero ay. Bueno, no nos regodeemos en nuestra pena. Pasaré un tiempo más contemplando este asunto. Sí, Jan, dime, ¿cómo murió Hawk?";
			link.l1.go = "baron_return";
		break;
		
		case "baron_return":
			dialog.text = "Nadie fue testigo de su muerte, al igual que nadie ha visto su cuerpo. Simplemente desapareció hace varios meses. Desde entonces, ha sido lo mismo que con Shark, ni rastro ni señal. Pero a diferencia de Steven, Nathan no tenía razón para esconderse. Es por eso que todos pensaron que había fallecido en la selva. Si no fuera por eso, no habrían accedido a elegir a Jackman en su lugar.";
			link.l1 = "¿Qué diablos estaba haciendo Hawk en la selva?";
			link.l1.go = "baron_return_1";
		break;
		
		case "baron_return_1":
			dialog.text = "¡Fue culpa mía, soy un viejo tonto! Le había persuadido para que se encargara de los bandidos recién llegados. No tengo idea de quiénes son ni quién es su jefe. Normalmente no me importaría, pero empezaron a secuestrar a los amistosos Miskitos. Su jefe de guerra Kumvana amenazó con declarar la Senda de la Guerra y pidió mi ayuda. No tuve opción, más que intervenir.\nHalcón aterrizó con una pequeña unidad en la Costa de los Mosquitos, quedó atrapado por una emboscada excelentemente organizada y fue derrotado. Parecía que él y sus hombres esperaban que desembarcaran allí. El cadáver de Halcón no fue encontrado entre los otros en la jungla.";
			link.l1 = "¡Tienes todo tipo de travesuras sucediendo bajo tus narices! ¿Ninguno de los chicos de Hawk intentó manejar a los bandidos?";
			link.l1.go = "baron_return_2";
		break;
		
		case "baron_return_2":
			dialog.text = "Jackman se adelantó a todos. Anunció que él mismo resolvería el problema en el consejo de los Hermanos y tomó la decisión. Los miskitos dejaron de desaparecer, pero los bandidos se quedaron allí, manteniéndose relativamente ocultos.\nJackman dijo que no estaban reteniendo a nadie como rehén de aquellos que vinieron a atacarlos y que no había razón para que los Hermanos les declararan la guerra. Hawk los atacó primero, así que según nuestras leyes, los bandidos tenían derecho a defenderse. Todos estuvieron de acuerdo. Todos menos...";
			link.l1 = "¿Todos menos quién?";
			link.l1.go = "baron_return_3";
		break;
		
		case "baron_return_3":
			dialog.text = "Nathan tenía una esposa. Su nombre es Danielle Hawk y ¡es una perra dura! Dudo que alguna vez haya superado la pérdida de su capitán, sin mencionar el hecho de que sospechaba algo desde el principio e intentó disuadir a Hawk. Recuerdo que tuvieron una gran disputa al respecto, pero eso no era nada fuera de lo común para ellos.";
			link.l1 = "¿Y dónde está Danielle ahora?";
			link.l1.go = "baron_return_4";
		break;
		
		case "baron_return_4":
			dialog.text = "¡Quién sabe! Jackman se aseguró de que ella dejara Maroon Town. No me visita. Nunca nos llevamos bien, se ha vuelto aún más perra con los años, y ahora debe odiarme de verdad, porque probablemente crea que yo soy la razón de sus desgracias.\nQuizás esté buscando a Hawk por su cuenta, ¡pero qué puede hacer una mujer, aunque lleve pantalones y un sable! Por cierto, ha dominado el sable. No te recomiendo probarte contra ella si la encuentras. Sí, y tampoco tiene sentido hablar con los bandidos. Han montado un campamento muy impresionante allí y están armados hasta los dientes.\nParece que son exmilitares y conocen bien su negocio. No permiten a nadie en su territorio. Dicen que los españoles solían extraer oro allí. Pero el oro se agotó y abandonaron la mina. No tengo ni idea de qué están haciendo esos malditos allí.";
			link.l1 = "Bueno, ya que nadie ha visto el cadáver de Hawk, la esperanza de encontrarlo vivo continúa. Dios sabe, incluso podríamos devolverlo al baronato.";
			link.l1.go = "baron_return_5";
		break;
		
		case "baron_return_5":
			dialog.text = "Sí, qué te parece. Aquí, toma esta carta. Cuando te encuentres con Steve Dodson, entrégasela de inmediato. El contenido de esta carta garantizará tu seguridad. Bueno, por si acaso.";
			link.l1 = "¡Gracias, Jan. Me aseguraré de hacerlo!";
			link.l1.go = "baron_return_6";
		break;
		
		case "baron_return_6":
			DialogExit();
			GiveItem2Character(pchar, "letter_svenson");
			AddQuestRecord("BaronReturn", "1");
			pchar.questTemp.Saga.BaronReturn = "begin";
			pchar.quest.Saga_DannyMeeting.win_condition.l1 = "location";
			pchar.quest.Saga_DannyMeeting.win_condition.l1.location = "SantaCatalina_town";
			pchar.quest.Saga_DannyMeeting.function = "Saga_DannyMeeting";
		break;
		
		case "return_LSC":
			dialog.text = "Bueno, ¿por qué esa cara larga? ¿Estás cansado? ¿Quizás un vaso de ron para ti?";
			link.l1 = "No me importaría...";
			link.l1.go = "return_LSC_1";
		break;
		
		case "return_LSC_1":
			LAi_AlcoholSetDrunk(pchar, 51, 5600);
			dialog.text = "Aquí, toma un vaso. Ahora habla.";
			link.l1 = "(bebiendo) Ah, eso es mucho mejor... Bueno, Jan, tú y el Pastor Negro teníais razón. La Isla de la Justicia sí existe. Estuve allí.";
			link.l1.go = "return_LSC_2";
		break;
		
		case "return_LSC_2":
			dialog.text = "¡Te dije que se suponía, que había una base de contrabando por ahí!";
			link.l1 = "No hay, de hecho, ninguna base de ningún tipo. Y los rumores en el Caribe no mentían. Negros y blancos realmente están viviendo juntos allá, seguramente no necesariamente en paz, sino más como perros y gatos. Y la isla en sí consiste en una innumerable multitud de naufragios.";
			link.l1.go = "return_LSC_3";
		break;
		
		case "return_LSC_3":
			dialog.text = "¡No puedo creerlo! Jose Dios estará muy interesado en escuchar tu historia, estoy seguro de ello. Visítalo algún día, por cierto.";
			link.l1 = "Iré a visitarlo más tarde. No es el mejor momento para eso ahora mismo. Tengo asuntos más urgentes que atender en este momento. He encontrado a Nathaniel Hawk en la Isla.";
			link.l1.go = "return_LSC_4";
		break;
		
		case "return_LSC_4":
			dialog.text = "¿Has encontrado a Nathan? ¡Eso es extraordinario! ¿Cómo está él?";
			link.l1 = "Bueno... Está enfermo, constantemente borracho y profundamente deprimido.";
			link.l1.go = "return_LSC_5";
		break;
		
		case "return_LSC_5":
			dialog.text = "¡Maldita sea, eso es desalentador! ¿Dónde está? ¿En tu barco?";
			link.l1 = "No, él está en su propio barco. En la Isla.";
			link.l1.go = "return_LSC_6";
		break;
		
		case "return_LSC_6":
			dialog.text = "¿Qué, no lo trajiste aquí? ¿Por qué?";
			link.l1 = "Porque no había nada que lo enfrentara. Me dirigí a la isla sin un barco.";
			link.l1.go = "return_LSC_7";
		break;
		
		case "return_LSC_7":
			dialog.text = "¡Maldita sea, "+pchar.name+", apenas has bebido un vaso de ron y ya estás hablando tonterías como si te hubieras bebido hasta perder el sentido. ¿Qué, nadaste a través del Caribe? ¿O te ataste unas tortugas a los pies?";
			link.l1 = "No, no nadé. Jan, llegué a la isla directamente desde la jungla del continente, tal como lo hizo Nathan, a través de un ídolo indio mágico. Ya le he contado esta historia a tanta gente y estoy cansado de demostrar que no me he vuelto loco, así que todo lo que tengo que decir es: ¡simplemente créeme!, ¿está bien?";
			link.l1.go = "return_LSC_8";
		break;
		
		case "return_LSC_8":
			dialog.text = "¿Ídolo indio?";
			link.l1 = "Hay al menos tres ídolos en el Caribe conocidos como las estatuas de Kukulcán: uno cerca de la aldea miskita de Tierra Firme occidental, otro en el fondo de las aguas poco profundas de la Isla de la Justicia, y otro en la aldea caribeña de Dominica. Estos ídolos, con la ayuda de la magia india, son capaces de transferir instantáneamente a los seres humanos a través del tiempo y el espacio.";
			link.l1.go = "return_LSC_9";
		break;
		
		case "return_LSC_9":
			dialog.text = "";
			link.l1 = "Pasé por las tres estatuas en círculo y salí justo donde comencé mi viaje en el pueblo Miskito. ¡Si no me crees, puedo llamar a Danielle. Ella lo ha visto todo con sus propios ojos!";
			link.l1.go = "return_LSC_10";
		break;
		
		case "return_LSC_10":
			dialog.text = "¿Danielle? ¿La esposa de Hawk? ¿Estaba con vosotros?";
			link.l1 = "En parte, sí. Ella misma me encontró en Blueweld y me llevó al pueblo miskito, a un chamán que me envió a la estatua mágica. Ahora está sirviendo como uno de mis oficiales, temporalmente, por supuesto.";
			link.l1.go = "return_LSC_11";
		break;
		
		case "return_LSC_11":
			dialog.text = "Estoy absolutamente pasmado, "+pchar.name+"¡Es tal como dicen los ingleses! Te criaron con cuchara de plata. ¡Eres un suertudo hijo de perra! Bien, simplemente te creeré, aunque me cueste. Pero el asunto con Nathan sigue igual, necesita ser ayudado.";
			link.l1 = "Eso es lo que voy a hacer. Estoy preparando una expedición a la Isla de la Justicia. Ahora tengo todo lo que necesito: las coordenadas de la isla y las instrucciones de navegación.";
			link.l1.go = "return_LSC_12";
		break;
		
		case "return_LSC_12":
			dialog.text = "Fantástico. ¿Puedo hacer algo para ayudarte?";
			link.l1 = "No, gracias. Pero omití un pequeño detalle. Además de Nathan, también encontré a Tiburón Dodson en la isla.";
			link.l1.go = "return_LSC_13";
		break;
		
		case "return_LSC_13":
			dialog.text = "¡Entonces, realmente ha ido allí! Bueno, "+pchar.name+", has hecho un trabajo excelente. ¿Cómo está Dodson por allá? Has hablado con él, por supuesto, ¿no es así?";
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			{
				link.l1 = "No solo hablé con él. También nos hemos hecho amigos. Fue él quien me dio las instrucciones de navegación que necesitaré para regresar a la Isla. Steven ha accedido a intercambiar el camarote de su buque de guerra por la residencia de Sharptown.";
				link.l1.go = "return_LSC_14";
			}
			else
			{
				link.l1 = "Hablamos, sí, pero al final resultó ser inútil. Steven fue asesinado mientras yo estaba en la Isla, cuando una conspiración, organizada por su contramaestre, Chad Kapper, entró en acción.";
				link.l1.go = "return_LSC_17";
			}
		break;
		
		case "return_LSC_14":
			dialog.text = "¡Ja! ¿Y cómo logró Tiburón convertirse en capitán de un buque de guerra?";
			link.l1 = "La nave ha estado en una 'calma' interminable durante más de medio siglo. Está atrapado con su gente en la Isla. Por eso no se ha mostrado en el Caribe durante tanto tiempo. De todas formas, lo traeré aquí pronto y él mismo te contará sus aventuras.";
			link.l1.go = "return_LSC_15";
		break;
		
		case "return_LSC_15":
			dialog.text = "¡No puedo esperar por eso! Ahora las cosas están empezando a mejorar. Nos acabamos de volver más poderosos, "+pchar.name+"¿Cuándo piensas partir de regreso a la Isla?";
			link.l1 = "Ahora mismo. Solo vine aquí un minuto para contarte las novedades, mientras Danielle hace los preparativos para la expedición. Se muere por ver a su Nathan. Y ¿sabes qué, Jan? No es tan mala como parece.";
			link.l1.go = "return_LSC_16";
		break;
		
		case "return_LSC_16":
			dialog.text = "¿Sí?  Bueno, tal vez no tenía del todo razón sobre ella. Está bien, "+pchar.name+", no te retendré más. ¡Ve y que la suerte te acompañe! Estaré esperando tu regreso.";
			link.l1 = "Nos vemos, Jan.";
			link.l1.go = "return_LSC_19";
		break;
		
		case "return_LSC_17":
			dialog.text = "¿Chad Kapper? Maldita sea, conocía a ese tipo. ¿Mató a Steven? Ese bastardo...";
			link.l1 = "Kapper está muerto. Pero no podemos traer de vuelta a Steven, así que tenemos que pensar en una manera de seguir organizando nuestra política.";
			link.l1.go = "return_LSC_18";
		break;
		
		case "return_LSC_18":
			dialog.text = "¡Ja! Qué lástima... ¿Qué hay que pensar? Solo tendremos que convencer a Tyrex de que lidere la Hermandad. Además, después de Blaze, Tyrex, como guardián del Código, es nuestra figura más respetable. Pero primero necesitamos traer de vuelta a Hawk para al menos tener un as bajo la manga. ¿Cuándo te marchas a la Isla?";
			link.l1 = "Ahora mismo. Solo vine aquí por un minuto para contarte las noticias, mientras Danielle hace preparativos para la expedición. Está ansiosa por ver a su Nathan. ¿Y sabes qué, Jan? No es tan bruja como parece.";
			link.l1.go = "return_LSC_16";
		break;
		
		case "return_LSC_19":
			DialogExit();
			pchar.questTemp.Saga.BaronReturn = "return_LSC";
			// LSC ждёт своего героя!
			i = FindIsland("LostShipsCity");
			Islands[i].visible = true;
			Islands[i].reload_enable = true;
			pchar.quest.return_LSC.win_condition.l1 = "location";
			pchar.quest.return_LSC.win_condition.l1.location = "LostShipsCity";
			pchar.quest.return_LSC.function = "LSC_ReturnCheckShips"; // проверка типов кораблей
			pchar.quest.return_LSC_attack.win_condition.l1 = "location";
			pchar.quest.return_LSC_attack.win_condition.l1.location = "Beliz";
			pchar.quest.return_LSC_attack.function = "LSC_ReturnJackmanAttack"; // атака наймитов Джекмана
			pchar.quest.return_LSC_main.win_condition.l1 = "Ship_location";
			pchar.quest.return_LSC_main.win_condition.l1.location = "LostShipsCity_town";
			pchar.quest.return_LSC_main.function = "LSC_ReturnMain"; // основная функция возвращения
		break;
		
		case "nathaniel":
			dialog.text = "¿Cómo está él? Dijiste que no se sentía bien.";
			link.l1 = "Sí, eso es exactamente correcto. Voy a llevarlo conmigo para que lo trate Ojo de Serpiente, el chamán, en el pueblo Miskito.";
			link.l1.go = "nathaniel_1";
		break;
		
		case "nathaniel_1":
			dialog.text = "¡Entonces no hay tiempo que perder! Date prisa, "+pchar.name+"¡Tan pronto como entregues a Nathan a tu chamán, vuelve enseguida a mí!";
			link.l1 = "Está bien, Jan. Suena como un plan.";
			link.l1.go = "exit";
			npchar.quest.shamane = "true";
		break;
		
		case "nathaniel_2":
			if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) // Акула жив
			{
				if (CheckAttribute(npchar, "quest.shark")) //и на месте
				{
					dialog.text = "Muy bien. Steven ya se ha pasado a verme. Ahora finalmente podemos continuar discutiendo nuestros planes.";
					link.l1 = "Soy todo oídos, Jan.";
					link.l1.go = "barbazon";
				}
				else
				{
					dialog.text = "Eso es agradable, por supuesto, pero ¿por qué Dodson no ha venido a verme todavía? ¿Qué, lo has dejado en la isla?";
					link.l1 = "Hm... Estaba apurado llevando a Nathan a Ojo de Serpiente...";
					link.l1.go = "nathaniel_wait";
				}
			}
			else
			{
				dialog.text = "Muy bien. Mi corazón llora por Shark. Pero así es la vida, así que Tyrex tomará su lugar. Bueno, ahora finalmente podemos continuar discutiendo nuestros planes.";
				link.l1 = "Estoy todo oídos, Jan.";
				link.l1.go = "barbazon";
			}
		break;
		
		case "nathaniel_wait":
			dialog.text = "... ¿y olvidaste llevarte al Tiburón? No puedo creerlo, "+pchar.name+"¡Entrega a Steven a Blueweld ahora! ¿Me escuchas? ¡Ve!";
			link.l1 = "Tranquilo, Jan. Yo me encargaré de todo.";
			link.l1.go = "exit";
			NextDiag.TempNode = "nathaniel_wait_1";
		break;
		
		case "nathaniel_wait_1":
			if (CheckAttribute(npchar, "quest.shark"))
			{
				dialog.text = "Steven pasó a verme. Ahora finalmente podemos continuar discutiendo nuestros planes.";
				link.l1 = "Soy todo oídos, Jan.";
				link.l1.go = "barbazon";
			}
			else
			{
				dialog.text = "¡Oh, "+pchar.name+"... Me parece que has estado bebiendo demasiado ron últimamente. Verás, nunca termina bien. Primero tus manos comienzan a temblar, luego empiezas a perder la memoria, y después recibes una marca negra...";
				link.l1 = "Entendido, Jan. ¡Voy a buscar a Steven de inmediato!";
				link.l1.go = "exit";
				NextDiag.TempNode = "nathaniel_wait_1";
			}
		break;
		
		case "barbazon":
			dialog.text = "El Pastor Negro ha sido muy claro, solo está interesado en ese libro teológico. He enviado a mis hombres a buscarlo, tal vez alguien lo encuentre. Marcus Tyrex no es un problema, no tendremos dificultades para persuadirlo. Jackman dejó Maroon Town poco después de que lo visitaste. Navegó a algún lugar en el 'Centurion', la fragata de los Halcones.\nSolo queda Barbazon, también conocido como Jacques el Amable. Debemos encontrar una manera de hacer que coopere con nosotros. No estoy seguro de cómo hacerlo por ahora. Pero una cosa es obvia: deberías visitarlo.";
			link.l1 = "Háblame de Barbazon."; // Addon 2016-1 Jason пиратская линейка патч 17/1
			link.l1.go = "barbazon_1";
		break;
		
		case "barbazon_1":
			dialog.text = "Tipo reservado. Pretende ser pobre, pero posiblemente es el hombre más rico del Caribe. Controla todas las operaciones de contrabando del Este. Si no fuera por Marcus enfrentándose a él, gobernaría todo el tráfico de contrabando en las Islas de Barlovento. Tyrex es como una espina en su garganta.\nSiempre pelean en el consejo, pero Barbazon no tiene las agallas para declarar una guerra abierta. Quizás realmente fue una vez un pirata de Dunkerque como afirma, pero ahora me recuerda más a un usurero.";
			link.l1 = "¿Cómo diablos llegó a ser elegido como barón?";
			link.l1.go = "barbazon_2";
		break;
		
		case "barbazon_2":
			dialog.text = "Oro, mi amigo, gobierna todo y en todas partes, quien tiene el oro pone las reglas. Además, Barbazon es realmente bueno ideando todo tipo de operaciones lucrativas e ilegales. Él mismo no participa en ellas, pero siempre se lleva una parte. Así que siempre tiene a su alrededor a un montón de valientes matones, que en su mayoría son débiles de cabeza. Todos morirían de hambre o acabarían en el cadalso sin él.";
			if (CheckAttribute(pchar, "questTemp.Mtraxx") && pchar.questTemp.Mtraxx == "full_complete_end")
			{
				link.l1 = "Me recuerda a Marcus... Jan, el asunto es... No tengo ni idea de cómo acercarme a Barbazon. Hay un problema del cual no estás al tanto.";
				link.l1.go = "barbazon_5";
			}
			else
			{
				link.l1 = "¿Cómo llego a Barbazon?";
				link.l1.go = "barbazon_3";
			}
		break;
		
		case "barbazon_3":
			dialog.text = "Simplemente finge ser uno de esos imbéciles que necesitan una pista para un trabajo gordo. Ni siquiera pienses en intentar engañarlo con su parte. El Benévolo Barbazon no perdona.";
			link.l1 = "Eso ni se dice. No me estoy involucrando con él por mi propio beneficio. De todos modos, es hora de hacerle una visita.";
			link.l1.go = "barbazon_4";
		break;
		
		case "barbazon_4":
			DialogExit();
			AddQuestRecord("BarbTemptation", "1");
			pchar.questTemp.Saga.BarbTemptation = "begin";
			pchar.questTemp.Saga.BaronReturn = "barbazon";
			NextDiag.CurrentNode = "First time";
			// тут вычищаем квестовый мусор от LSC
			if (CheckCharacterItem(pchar, "letter_chad")) RemoveItems(pchar, "letter_chad", 1);
			if (CheckCharacterItem(pchar, "letter_chad_1")) RemoveItems(pchar, "letter_chad_1", 1);
		break;
		
		// Addon 2016-1 Jason пиратская линейка патч 17/1
		case "barbazon_5":
			dialog.text = "¿De veras? Dispara.";
			link.l1 = "¿Alguna vez has oído hablar de Charlie Prince?"; 
			link.l1.go = "barbazon_6";
		break;
		
		case "barbazon_6":
			dialog.text = "Sí, escuché los rumores. Este tipo trabajaba para Marcus Tyrex no hace mucho tiempo. Hizo bastante en muy poco tiempo, se hizo un nombre saqueando Cartagena. ¿Y qué?";
			link.l1 = "Este tipo soy yo. Soy Charlie Prince. Lo era. ¿Ves ahora?"; 
			link.l1.go = "barbazon_7";
		break;
		
		case "barbazon_7":
			dialog.text = "¡Maldita sea! ¿Eres Charlie Prince? ¡Qué giro!"+pchar.name+", ¡Estoy impresionado! Ahora veo de dónde proviene tu agarre... Pero, ¿qué tiene que ver Barbazon con esto?";
			link.l1 = "¿Qué te parecería si el Príncipe visitara a Barbazon, Jan?.."; 
			link.l1.go = "barbazon_8";
		break;
		
		case "barbazon_8":
			dialog.text = "Mm... Entiendo esto. ¿Has tenido tratos con él antes?";
			link.l1 = "No exactamente. Uno de sus matones llamado Ignacio Marco trató de joderme por órdenes directas de Barbazon. Era parte de su pequeña guerra."; 
			link.l1.go = "barbazon_9";
		break;
		
		case "barbazon_9":
			dialog.text = "¿Vio tu cara? ¿Te presentaste a él?";
			link.l1 = "No."; 
			link.l1.go = "barbazon_10";
		break;
		
		case "barbazon_10":
			dialog.text = "No veo problema aquí entonces. También oí hablar del corsario Charlie Prince, pero no sabía que eras tú antes de que me lo dijeras.";
			link.l1 = "¿Crees que Barbazon no verá a través de mí?"; 
			link.l1.go = "barbazon_11";
		break;
		
		case "barbazon_11":
			dialog.text = "¿Cómo podría hacerlo si nunca ha visto tu cara? Todo lo que hizo fue dar órdenes para deshacerse de uno de los empleados de Marcus.";
			link.l1 = "Hum... Podrías tener razón en esto."; 
			link.l1.go = "barbazon_12";
		break;
		
		case "barbazon_12":
			dialog.text = "No hay manera de que salgamos de esta sin Barbazon. Ve a verlo, pero ten cuidado. Corre si te reconoce, pensaremos en otra forma de acercarnos a él en ese caso.";
			link.l1 = "Bien. Debería irme ahora. He estado esperando conocer al bastardo."; 
			link.l1.go = "barbazon_13";
		break;
		
		case "barbazon_13":
			dialog.text = "No te hagas el tonto y no intentes joder a Jacques. Él nunca perdona. Actúa como un idiota ansioso por ganar dinero fácil.";
			link.l1 = "Mi papel favorito al parecer... ¡Adiós, Jan!"; 
			link.l1.go = "barbazon_4";
		break;
		
		case "saga_26":
			dialog.text = "Sí. El chamán indio hizo todo lo que pudo, Hawk está como nuevo. Se supone que ya está en el Pueblo de los Cimarrones con Dannie, así que si quieres, adelante y saluda. Estarían encantados de verte.";
			link.l1 = "Definitivamente pasaré para ver cómo están... Jan, ¡pude encontrar la segunda parte del mapa de Sharp! Estaba en la cabina de Jackman. Ahora no tendremos problema para probar los derechos de Helen sobre Isla Tesoro.";
			link.l1.go = "saga_27";
		break;
		
		case "saga_27":
			dialog.text = "Genial, muéstrame eso.\nTeníamos razón, Jacob fue quien mató a Blaze. Ahora la mancha en el nombre de Shark se eliminará para siempre. En cuanto a las pruebas, ese es un asunto más delicado. Y debe abordarse solo después de una contemplación muy minuciosa.";
			link.l1 = "Otra cosa, Jan. Echa un vistazo a esta nota. También estaba entre las cosas de Jackman.";
			link.l1.go = "saga_28";
		break;
		
		case "saga_28":
			RemoveItems(pchar, "letter_parol", 1); // удалить записку
			dialog.text = "Bueno, echemos un vistazo... ¡Ja, así que por eso los bandidos escucharon a Jackman y dejaron de secuestrar a los Miskitos! ¡No podía ser de otra manera! Ese canalla lo planeó todo y estaba varios pasos por delante.";
			link.l1 = "Sí, y también puedo ver por qué los hombres de Hawk fueron masacrados. Pero hay dos cosas que no entiendo: primero, ¿qué están haciendo los cómplices de Jackman en la mina y segundo, por qué estás reaccionando con tanta calma al hecho de que todo este lío está ocurriendo en tu territorio?";
			link.l1.go = "saga_29";
		break;
		
		case "saga_29":
			dialog.text = "Me da vergüenza... Tienes razón. Jackman realmente se ha descontrolado. Y sus secuaces no tienen nada que hacer en mi dominio. Parece que ha llegado el momento de recordarle al Caribe con quién están tratando.";
			link.l1 = "¿Qué tienes en mente, Jan?";
			link.l1.go = "saga_30";
		break;
		
		case "saga_30":
			dialog.text = "Revivir el pasado... Tengo la intención de organizar una expedición punitiva y eliminar a cada bandido en las minas. Ahora tenemos pruebas de que son hombres de Jackman y estoy obligado a limpiar mis territorios de esta escoria.\n"+pchar.name+", has hecho un excelente trabajo. Es hora de que me ponga en marcha. Ahora descansa un poco. Ve a visitar a los Halcones. ¡Vuelve en diez días!";
			link.l1 = "Está bien, Jan.  Lo haré. ¡Volveré exactamente en el tiempo que dijiste!";
			link.l1.go = "saga_31";
			link.l2 = "¡Ja! Yo también quiero participar en esta cruzada. ¿Por qué has decidido ponerme en tiempo de recreo?";
			link.l2.go = "saga_31_1";
		break;
		
		case "saga_31_1":
			dialog.text = "Perdóname, viejo amigo. Solo pensé que tal vez ya era hora de que hiciera algún trabajo y de que tú descansaras un poco. Pero si es tu deseo, ¡estaré más que feliz! ¡Enfrentemos la tormenta juntos! Y todo lo que encontremos en la mina lo dividiremos equitativamente entre nuestras tripulaciones, como está escrito en las leyes de la Hermandad.";
			link.l1 = "¡Trato hecho, Jan! ¿Cuándo partimos?";
			link.l1.go = "saga_31_2";
		break;
		
		case "saga_31_2":
			dialog.text = "Ven con tu gente a la Costa de los Mosquitos en tres días. Para entonces habré reunido a mi escuadrón y ya estaré listo, esperándote. ¡No llegues tarde!";
			link.l1 = "Está bien, Demonio del Bosque. ¡Estoy ansioso por entrar en batalla contigo, espalda con espalda! ¡Nos vemos pronto!";
			link.l1.go = "saga_31";
			npchar.quest.mine_tw = "true";
		break;
		
		case "saga_31": 
			chrDisableReloadToLocation = true;//закрыть локацию
			DialogExit();
			LAi_SetActorType(npchar);
			ChangeCharacterAddressGroup(npchar, pchar.location, "goto", "goto1");
			LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
			if (CheckAttribute(npchar, "quest.mine_tw"))
			{
				pchar.quest.Saga_MinePrepareAttack.win_condition.l1 = "location";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l1.location = "Shore53";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2 = "Timer";
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.hour  = sti(GetTime());
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.day   = GetAddingDataDay(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.month = GetAddingDataMonth(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.win_condition.l2.date.year  = GetAddingDataYear(0, 0, 3);
				pchar.quest.Saga_MinePrepareAttack.function = "Saga_MineBanditsPrepareAttack";
				SetFunctionTimerCondition("Saga_MineBanditsAttackOver", 0, 0, 4, false); // таймер
			}
			else SetFunctionTimerCondition("Saga_MineBanditsDestroyed", 0, 0, 10, false); // таймер
			sld = characterFromId("Nathaniel");
			sld.model = "Hawk_2";
			Characters_RefreshModel(sld); // наверно не нужно
			sld.greeting = "nathaniel_2";
			sld.dialog.currentnode = "marun_town";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // открыть резиденцию Хоука
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "marun_town";
			sld.greeting = "danny_2";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
			LAi_SetStayType(sld);
		break;
		
		case "saga_32a":
			dialog.text = "Excelente. He descubierto algo sobre el misterioso propietario de la mina, Lawrence Beltrope.";
			link.l1 = "Entonces, ¿quién es este pájaro?";
			link.l1.go = "saga_35";
		break;
		
		case "saga_32":
			dialog.text = "Se lo saqué a los secuaces de Jackman en la mina. Resultaron ser duros de roer, pero mis muchachos tampoco nacieron ayer. Además, pudimos bajarles la guardia después de decirles la contraseña de la nota que encontraste. Penetramos en la mina y les dimos una despedida ostentosa.";
			link.l1 = "¿Tomaste la mina? ¡Excepcional!";
			link.l1.go = "saga_33";
		break;
		
		case "saga_33":
			dialog.text = "¡Que esto sea una lección para cualquiera que piense que el Diablo del Bosque está oxidado! Realmente he holgazaneado demasiado en los últimos años y ¿mira lo que ha pasado? ¡Jackman estaba desplegando su malvado plan justo bajo mis narices!";
			link.l1 = "¿Qué viste en esa mina? ¡Cuéntamelo!";
			link.l1.go = "saga_34";
		break;
		
		case "saga_34":
			dialog.text = "La mina fue abandonada por los españoles de verdad, sin embargo, Lawrence Beltrope de Port Royal la compró por una miseria y continuó la explotación en secreto. Aparentemente, los españoles abandonaron el pozo demasiado pronto, ya que aunque nosotros mismos no encontramos oro allí, encontramos a varios esclavos que afirmaron que había oro hasta hace muy poco.";
			link.l1 = "¿Lawrence Beltrope? Nunca he oído hablar de él. ¿Quién es?";
			link.l1.go = "saga_35";
		break;
		
		case "saga_35":
			dialog.text = "Es un nativo, el hijo de Thomas Beltrope, hace mucho tiempo el hermano jurado de Nicholas Sharp y el corsario de la Compañía de la Isla Providencia. Yo mismo conocía muy bien a Thomas. Hace un año, Lawrence vino al Caribe una vez más. Resulta que Jackman estaba trabajando para él. ¡Tenlo en cuenta y mantén los ojos bien abiertos!";
			link.l1 = "Entonces el misterioso 'jefe' de Jackman, mencionado en esa carta, es Lawrence Beltrope... Está bien, recordaré ese nombre.";
			link.l1.go = "saga_36";
		break;
		
		case "saga_36":
			dialog.text = "Una cosa más. Recuerdo algo extraño. Blaze mencionó una vez alguna mina de oro española abandonada y que iba a invertir su oro en Sharptown. Pero el mapa de la mina desapareció después de que su hermana huyera con el capitán Butcher. ¿Quizás estaba hablando de nuestra mina?\nDe cualquier manera, fue hace mucho tiempo y no cambia mucho... Tú y yo deberíamos tratar con el Consejo. ¿Tienes los cinco fragmentos?";
			link.l1 = "Sí. Estos cuatro: Nathaniel, Tyrex, Marlow y Barbazon. Todos ellos han dado su sí.";
			link.l1.go = "saga_37";
		break;
		
		case "saga_37":
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			sTemp = "Shark";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Tyrex";
			dialog.text = "Estupendo. Estoy seguro de que no habrá ningún problema para elegir "+sTemp+"como cabeza de la Hermandad de la Costa. Inmediatamente trabajaré en convocar una reunión del Consejo.";
			link.l1 = "Entonces Jan, ¿podemos considerar que todos los problemas están bajo control por ahora? Nathaniel está en Maroon Town, Jackman está muerto y la Hermandad ahora tiene un nuevo líder... ¿Quizás es momento de regresar a donde empezamos, es decir, tomar Tortuga?";
			link.l1.go = "saga_38";
		break;
		
		case "saga_38":
			dialog.text = "Recuerdo, "+pchar.name+", pero necesitamos esperar un poco. Además, el tiempo para resolver la herencia de Sharp se está agotando y ese asunto, como sabes, necesita ser manejado con urgencia.";
			link.l1 = "¿Qué pasa con la herencia? Tengo ambas partes del mapa. Todo lo que realmente tenemos que hacer es presentarlas y eso es todo...";
			link.l1.go = "saga_39";
		break;
		
		case "saga_39":
			dialog.text = ""+pchar.name+", te aseguro que hoy en día no simplemente entregan islas a la gente. Incluso a los herederos legítimos con cada párrafo del testamento cumplido. Las autoridades inglesas desean esta isla con ansias, soy muy consciente de eso.\nNo creo que el coronel Doyle se quede de brazos cruzados mientras nosotros le quitamos la isla que ya considera propiedad inglesa. Además, tú y yo deberíamos permanecer en las sombras.";
			link.l1 = "¿Y qué sugieres?";
			link.l1.go = "saga_40";
		break;
		
		case "saga_40":
			dialog.text = "Dirígete a Port Royal y busca a un hombre llamado Albert Loxley allí. Es el mejor abogado de todo el Caribe. Se ha vuelto bastante hábil en asuntos turbios de todo tipo, así que aceptará cualquier tipo de trabajo si se le ofrece una tarifa exorbitante por ello. Tiene un apetito descomunal, pero vale la pena.";
			link.l1 = "¿Crees que el testamento de Sharp podría tener algunas trampas?";
			link.l1.go = "saga_41";
		break;
		
		case "saga_41":
			dialog.text = "No solo lo pienso, estoy seguro de ello. ¿Alguna vez has tenido que hacer negocios con funcionarios? Sepas que si quieren algo de ti, te sacarán el alma, te señalarán una coma fuera de lugar, interpretarán todo de la manera que necesiten y te dejarán tan desnudo como un gatito ciego.\nPor eso se crearon los abogados. Luchan contra los funcionarios con sus propias armas: la verborrea, la tinta derramada y la chicana. Por lo tanto, deberías visitar a Loxley y contratarlo para proteger nuestros intereses mientras yo me ocupo de las elecciones.";
			link.l1 = "Está bien. Me voy a Port Royal. ¿Cuánto tiempo tomará para que el Consejo se reúna y celebre una elección?";
			link.l1.go = "saga_42";
		break;
		
		case "saga_42":
			dialog.text = "Diez días. Así que no te molestes en buscarme en Blueweld antes.";
			link.l1 = "Entendido. Bueno, Jan. ¡En ese caso, nos vemos en un rato!";
			link.l1.go = "saga_43";
		break;
		
		case "saga_43":
			DialogExit();
			AddQuestRecord("Testament", "1");
			pchar.questTemp.Saga = "loxly"; // обновляем флаг
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			SetFunctionTimerCondition("Saga_GoldForLoxly", 0, 0, 10, false); // таймер
		break;
		
		case "saga_44":
			sTemp = "Steven Dodson";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus Tyrex";
			dialog.text = ""+sTemp+" envía sus más cálidos saludos. Siempre estará encantado de verte en su residencia en Isla Tesoro. Ve a visitarlo, si se presenta la oportunidad.";
			link.l1 = "Para asegurarse "+sTemp+" no dejará su nueva residencia, tú y yo, Jan, tenemos un poco de trabajo por delante.";
			link.l1.go = "saga_45";
		break;
		
		case "saga_45":
			sTemp = "four hundred and fifty";
			if(CheckAttribute(pchar,"questTemp.Mtraxx.Cartahena.Gold")) sTemp = "one thousand";
			dialog.text = "Tengo entendido que ya has visitado a Loxley...";
			link.l1 = "Sí, lo he hecho. Está tomando nuestro caso, pero exigió un montón de oro por sus servicios. "+sTemp+"   doblones por adelantado. ¡Adelante! Y también tendremos que pagarle aún más, dependiendo de cómo vaya la prueba de derechos de Helen. La suma se duplicará o triplicará, como él dijo.";
			link.l1.go = "saga_46";
		break;
		
		case "saga_46":
			dialog.text = "¡Ja! Bueno, no esperaba menos de un viejo tramposo como él. Huele la presa desde lejos, igual que una hiena. Por supuesto, estamos hablando de toda una isla aquí. Es ridículo pensar que Albert no pediría un par de cientos. Así que, la cantidad total podría estar alrededor de mil quinientos de oro...";
			link.l1 = "¡Jan, eso es un montón de dinero!";
			link.l1.go = "saga_47";
		break;
		
		case "saga_47":
			dialog.text = "Ya sé a dónde quieres llegar. Estoy de acuerdo en que no eres un gorila tonto que paga todo eso de su propio bolsillo. Pero, desafortunadamente, en este momento no tengo esa cantidad de oro guardada. Había planeado para tales gastos, sin embargo, la intervención de un sinvergüenza lo arruinó todo.";
			link.l1 = "¿De qué estás hablando?";
			link.l1.go = "saga_48";
		break;
		
		case "saga_48":
			dialog.text = "Escucha. Tal vez ya sepas que nuestro asentamiento es solo medio legal. Los ingleses mantienen una guarnición aquí y les proporcionamos caoba a buen precio. Pero hay un tipo de madera muy pesada y duradera - el Lignum Vitae, que deberías conocer como palo de hierro.\nEs rara y difícil de procesar incluso con acero endurecido. Dicen que hace mucho tiempo los Maya-Itza solían hacer sus temibles garrotes con ella. No puedes comprar palo de hierro en el mercado abierto y de contrabando cuesta su peso en plata.\nLos hombres de Doyle vienen ocasionalmente y compran toda la cantidad que hemos procesado, a bajo precio. Pero siempre logro guardar algo para mi propia necesidad.";
			link.l1 = "He oído hablar de este árbol. ¡Dicen que las balas de mosquete se hunden en su madera aceitosa como alquitrán! Su robustez es lo suficientemente buena como para fabricar engranajes para mecanismos de acero.";
			link.l1.go = "saga_49";
		break;
		
		case "saga_49":
			dialog.text = "Están mintiendo un poco sobre los equipos, pero el resto está en lo cierto. Así que, previendo gastos, preparé un gran lote de sándalo, pero algún bastardo vació mi almacén hace un par de días. Es alguien de los nuestros, lo sé. Tengo una sospecha, pero no puedo asegurarlo.";
			link.l1 = "¡Las ratas deben ser aplastadas! ¿A quién sospechas?";
			link.l1.go = "saga_50";
		break;
		
		case "saga_50":
			dialog.text = "Paul Molligan. Su 'Ostras' de la India Oriental navegó hacia Barbados ayer. No tuve la oportunidad de revisar sus bodegas. Pero no llevaría el sándalo a Bridgetown de todos modos, el lord Willoughby tiene oficiales de aduanas serios allí y el sándalo es una materia prima de importancia estratégica para la marina inglesa.\nSi realmente tiene mi sándalo, entonces lo venderá antes de llegar a Bridgetown. ¡Si tan solo pudieras interceptar a Molligan e inspeccionar sus bodegas!..";
			link.l1 = "¿Dices que partió hacia Bridgetown ayer? No todo está perdido aún. Intentaré alcanzarlo.";
			link.l1.go = "saga_51";
		break;
		
		case "saga_51":
			dialog.text = "Sabes qué hacer, si Molligan es la rata. Pero intenta averiguar el nombre de su cliente primero. Luego puedes entregar la carga al cliente tú mismo o devolvérmela.\nLleva la 'Oyster' a Blueweld también, es un buen barco, me gustaría quedármelo y reequiparlo para mis propias necesidades. A ti también se te permite tomar lo que quieras como premio... Y en caso de que Molligan no sea el culpable... no, estoy seguro de que es la rata que robó mi sándalo.";
			link.l1 = "¡Haré buen uso de mi tiempo!";
			link.l1.go = "saga_52";
		break;
		
		case "saga_52":
			dialog.text = "Si vendes el sándalo tú mismo, aparta mil quinientos doblones de oro para Loxley y el resto lo dividiremos a la mitad. Puedo confiar en ti para esto, ¿verdad?";
			link.l1 = "Por supuesto. No soy una rata.";
			link.l1.go = "saga_53";
		break;
		
		case "saga_53":
			dialog.text = "No tengo duda. Buena suerte, "+pchar.name+"¡Espero que te sonría esta vez!";
			link.l1 = "Gracias. ¡Hasta luego!";
			link.l1.go = "saga_54";
		break;
		
		case "saga_54":
			DialogExit();
			pchar.questTemp.Saga = "molligan"; // обновляем флаг
			AddQuestRecord("Testament", "3");
			if(bImCasual) NewGameTip("Modo exploración: el temporizador no está desactivado. ¡Cumple el plazo!");
			Saga_CreateMolliganInWorld(); // ставим корабль Моллигана на карту
		break;
		
		case "saga_55":
			npchar.quest.bakaut = GetSquadronGoods(pchar, GOOD_SANDAL);
			dialog.text = "Lo sabía. ¿Cuánto tenía en sus bodegas?";
			link.l1 = "He encontrado "+FindRussianQtyString(sti(npchar.quest.bakaut))+" en el 'Oyster'.";
			link.l1.go = "saga_56";
		break;
		
		case "saga_56":
			iTemp = sti(npchar.quest.bakaut);
			if (iTemp > 100)
			{
				dialog.text = "¡Vaya! Nunca había tenido tanto en mi almacén. Mira quién ha puesto sus dichosas manos en una fortuna. Gracias, "+pchar.name+", nunca me has defraudado. Venderé el producto de inmediato, ya tenemos un comprador. Tendré el dinero para ti mañana.";
				link.l1 = "Está bien. No te distraeré más entonces. Nos vemos mañana.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 90 && iTemp < 101)
			{
				dialog.text = "Sí, he tenido justo eso. ¡Pequeña rata! Gracias, "+pchar.name+", nunca me fallas. Venderé el producto de inmediato, ya tenemos comprador. Tendré el dinero para ti mañana.";
				link.l1 = "Está bien. No te distraeré más entonces. Nos vemos mañana.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 70 && iTemp < 90)
			{
				dialog.text = "Probablemente ya haya logrado vender una parte del cargamento a alguien, porque debería haber habido más. Pero no es gran cosa, recuperamos la mayor parte. Gracias, "+pchar.name+", venderé el producto de inmediato, ya tenemos un comprador. Tendré el dinero para ti mañana.";
				link.l1 = "Está bien. No te distraeré más entonces. Nos vemos mañana.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 50 && iTemp < 70)
			{
				dialog.text = "Maldita sea, ese bastardo ya pudo vender una buena parte del cargamento... Ah, qué lástima. Bueno, venderé lo que tengo, ya tengo un comprador. Tendré el dinero mañana.";
				link.l1 = "Está bien. No te distraeré más entonces. Nos vemos mañana.";
				link.l1.go = "saga_oust";
				break;
			}
			if (iTemp >= 20 && iTemp < 50)
			{
				dialog.text = "¡Maldita sea, eso es deplorable! Ese bastardo ya pudo vender más de la mitad del cargamento... Ah, qué pena. Bueno, venderé lo que tengo, ya he encontrado un comprador. Tendré el dinero mañana.";
				link.l1 = "Está bien. No te distraeré más entonces. Nos vemos mañana.";
				link.l1.go = "saga_oust";
				break;
			}
			dialog.text = "Hombre, simplemente estoy jodido. Ha vendido casi todo... Aquí, quédate con este sándalo para ti, "+pchar.name+", haz lo que quieras con él. Eres mi única esperanza de ganar algo de dinero ahora.";
			link.l1 = "Entendido. Bien, buscaré yo mismo. Esto no es mi primera corrida... Adiós, Jan.";
			link.l1.go = "saga_oust";
		break;
		
		case "saga_oust":
			if (CheckAttribute(npchar, "quest.bakaut"))
			{
				if (sti(npchar.quest.bakaut) < 20) DeleteAttribute(npchar, "quest.bakaut");
				else 
				{
					SaveCurrentNpcQuestDateParam(npchar, "bakaut_date");
					RemoveCharacterGoods(pchar, GOOD_SANDAL, sti(npchar.quest.bakaut));
				}
				pchar.questTemp.Saga = "removebakaut";
			}
			int iUst = 0;
			for(i = 0; i < COMPANION_MAX; i++)
			{
				iTemp = GetCompanionIndex(PChar, i);
				if(iTemp > 0)
				{
					sld = GetCharacter(iTemp);
					if(sti(RealShips[sti(sld.ship.type)].basetype) == SHIP_EASTINDIAMAN && sld.ship.name == "Oyster") iUst = 1;
				}
			} // есть ли у нас Устрица
			dialog.text = "¡Espera! ¿Capturaste el 'Oyster'?";
			if (iUst == 1)
			{
				link.l1 = "Sí. Ella está en el puerto ahora mismo. La anclé para ti, tal como pediste.";
				link.l1.go = "saga_oust_yes";
			}
			else
			{	
				link.l1 = "No. El barco estaba tan dañado durante la batalla que tuve que hundirlo.";
				link.l1.go = "saga_oust_no";
			}
		break;
		
		case "saga_oust_no":
			dialog.text = "Qué pena. Pero es lo que es. Hasta luego, "+pchar.name+".";
			link.l1 = "Adiós, Jan.";
			link.l1.go = "exit";
			NextDiag.TempNode = "First time";
		break;
		
		case "saga_oust_yes":
			dialog.text = "¡Notable! Equiparé esta belleza como se merece. Y más tarde siempre podrás tomarla prestada por un tiempo, tal como acordamos. Creo que en unos dos meses estará lista.";
			link.l1 = "Está bien. Un barco como este podría ser realmente útil a veces... ¡Nos vemos luego, Jan!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("Saga_RemoveOuster");
			npchar.quest.ouster = "true";
			SaveCurrentNpcQuestDateParam(npchar, "ouster_date"); // через 2 месяца
			NextDiag.TempNode = "First time";
		break;
		
		case "saga_57":
			int idlt;
			iTemp = sti(npchar.quest.bakaut)*30; // Ян за 1 шт бакаута даёт 30 дублонов
			if (iTemp > 1600)
			{
				idlt = makeint(iTemp-1500)/2; // доля Бонса :)
				dialog.text = "Recibí "+iTemp+" monedas por ello. Mil quinientos es para el abogado, más tu parte de doblones, "+idlt+"Aquí tienes.";
				link.l1 = "¡Loable! Ahora puedo partir fácilmente hacia Loxley.";
				link.l1.go = "saga_58";
				TakeNItems(pchar, "gold_dublon", 1500+idlt);
				break;
			}
			if (iTemp > 1450 && iTemp <= 1600)
			{
				dialog.text = "Recibí mil quinientos doblones por ello. Es justo lo suficiente para el abogado. Aquí tienes.";
				link.l1 = "Fantástico. Ahora puedo partir hacia Loxley.";
				link.l1.go = "saga_58";
				TakeNItems(pchar, "gold_dublon", 1500);
				break;
			}
			dialog.text = "Recibí "+iTemp+"  doblones por ello. Aquí tienes. Tendrás que desenterrar el resto por ti mismo.";
			link.l1 = "Bueno, si por mí mismo, entonces por mí mismo. Está bien, voy de camino a ver a Loxley.";
			link.l1.go = "saga_58";
			TakeNItems(pchar, "gold_dublon", iTemp);
		break;
		
		case "saga_58":
			DialogExit();
			PlaySound("interface\important_item.wav");
			DeleteAttribute(npchar, "quest.bakaut");
		break;
		
		case "saga_59":
			dialog.text = "¿Qué te parece eso? Eso es interesante. ¿Y cuánto está dispuesto a pagar el holandés por ello?";
			link.l1 = "Cuarenta doblones cada uno.";
			link.l1.go = "saga_60";
		break;
		
		case "saga_60":
			dialog.text = "¡Vaya! Mis compradores pagan menos...";
			link.l1 = "En total, tengo dos mil de oro para Loxley y "+sti(npchar.quest.bakaut_sum)*2+"doblones encima de eso.";
			link.l1.go = "saga_61";
		break;
		
		case "saga_61":
			dialog.text = "Bien. Entonces lo dividiremos por la mitad.";
			if (CheckCharacterItem(pchar, "gold_dublon"))
			{
				npchar.quest.bakaut_pay = GetCharacterItem(pchar, "gold_dublon"); // дублоны в кармане
				link.l1 = "Aquí tienes. He conseguido "+FindRussianQtyString(sti(npchar.quest.bakaut_pay))+".";
				link.l1.go = "bakaut_pay";
			}
			else
			{
				link.l1 = "Dejé los doblones en el barco. Haré una rápida visita y regresaré enseguida.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "saga_61_1":
			dialog.text = "Qué alegría. ¿Cuánto has traído?";
			if (CheckCharacterItem(pchar, "gold_dublon"))
			{
				npchar.quest.bakaut_pay = GetCharacterItem(pchar, "gold_dublon"); // дублоны в кармане
				link.l1 = "Aquí tienes. Tengo "+FindRussianQtyString(sti(npchar.quest.bakaut_pay))+".";
				link.l1.go = "bakaut_pay";
			}
			else
			{
				link.l1 = "¡Qué pasa con mi memoria! Es hora de dejar de jugar con este ron. Una vez más dejé los doblones en mi cofre. Haré una carrera rápida hasta allí y los traeré.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "bakaut_pay": // оплата
			if (sti(npchar.quest.bakaut_sum) < sti(npchar.quest.bakaut_pay)) // полная сумма
			{
				npchar.quest.bakaut_pay = sti(npchar.quest.bakaut_sum);
				iTemp = 0;
			}
			else iTemp = sti(npchar.quest.bakaut_sum)-sti(npchar.quest.bakaut_pay);
			npchar.quest.bakaut_sum = iTemp; // запоминаем остаток
			RemoveItems(pchar, "gold_dublon", sti(npchar.quest.bakaut_pay));
			Log_Info("Has dado "+sti(npchar.quest.bakaut_pay)+" doblones");
			PlaySound("interface\important_item.wav");
			if (iTemp == 0)
			{
				dialog.text = "Buen trabajo, "+pchar.name+"¡Una vez más me recuerdan que eres una buena persona con la que involucrarse!";
				link.l1 = "Lo intento, Jan...";
				link.l1.go = "bakaut_done";
			}
			else
			{
				dialog.text = "Estupendo. ¿Traerás el resto "+FindRussianQtyString(sti(npchar.quest.bakaut_sum))+"¿doblones después?";
				link.l1 = "Sí. Simplemente no podía acarrear un montón tan grande de oro de una sola vez.";
				link.l1.go = "exit";
				NextDiag.TempNode = "bakaut_pay_wait";
			}
		break;
		
		case "bakaut_pay_wait":
			dialog.text = "Entonces, "+pchar.name+", ¿cómo van mis doblones?";
			link.l1 = "Estoy dispuesto a darte un poco más de oro.";
			link.l1.go = "saga_61_1";
		break;
		
		case "bakaut_done": // рассчитались
			dialog.text = "Tengo una proposición para ti. Ya que pudiste encontrar un comprador lucrativo, entonces te podría vender un poco de sándalo. Solía recibir treinta doblones por pieza. Si quieres, puedes comprármelo a ese precio. Prefiero vendértelo a ti que a alguien más.";
			link.l1 = "¿Cuánto sándalo eres capaz de vender?";
			link.l1.go = "bakaut_done_1";
		break;
		
		case "bakaut_done_1":
			dialog.text = "Aviso de no acumular grandes lotes. Lo de Molligan fue una excepción. A las autoridades no les gustará la noticia de un mercado negro. Así que, aquí está el trato: Guardaré 25 piezas de sándalo para ti cada 14 y 24 del mes. \nSi quieres comprarlas, trae setecientos cincuenta doblones y llévate todo el lote. Si no apareces ese día, entonces se lo venderé a otro cliente. Así, podrás tener 50 piezas al mes. ¿Trato?";
			link.l1 = "¡Tienes un trato, Jan! Hagámoslo. Ahora, es hora de que me ponga en marcha...";
			link.l1.go = "saga_oust";
			DeleteAttribute(npchar, "quest.bakaut_sum");
			npchar.quest.trade_bakaut = "true"; // генератор купли-продажи бакаута
			AddQuestRecordInfo("Unique_Goods", "1");
		break;
		
		case "saga_59_1": // укрысил у Яна - нет генератора на бакаут, потерял больше
			dialog.text = "Ah, así que o no fue él o ya ha vendido el sándalo antes... Qué lástima. Bueno, ahora eres mi única esperanza para conseguir el dinero para el abogado.";
			link.l1 = "Estaré dispuesto a asumir esa responsabilidad. Este no es mi primer rodeo.";
			link.l1.go = "exit";
			// Ян расстроен и забыл про Устрицу - так что и Устрицы тоже не будет
			DeleteAttribute(npchar, "quest.bakaut_sum");
		break;
		
		case "saga_62":
			dialog.text = "¿Es así? Eso es interesante. Adelante, pregunta. ¿De quién quieres hablar?";
			link.l1 = "Sobre una chica. Su nombre era... Jessica Rose.";
			link.l1.go = "saga_63";
		break;
		
		case "saga_63":
			dialog.text = "Mm. ¿Te habló de ella el nuevo jefe de nuestra Hermandad?";
			link.l1 = "Él también lo hizo. Pero me enteré de ella por Baker, el viejo verdugo de St. John's. El mismo hombre que ejecutó al capitán Butcher.";
			link.l1.go = "saga_64";
		break;
		
		case "saga_64":
			dialog.text = "Bien. Hm. Bueno, han pasado más de veinte años desde que vi a Jessica por última vez. ¿Qué sabes de ella?";
			link.l1 = "Bueno, sé cómo terminó con el capitán Butcher y cómo piratearon juntos. Sé que él la dejó por Beatrice. Más tarde, ella se vengó de él por eso con la ayuda de un tal Joshua Leadbeater, también conocido como la Máscara...";
			link.l1.go = "saga_65";
		break;
		
		case "saga_65":
			dialog.text = "";
			link.l1 = "También sé que tú, Jan, perdona mi franqueza, estabas interesado en Jessica. Esta es la razón por la que vine a ti. Jessica es una figura importante en mis búsquedas. Fue ella quien asesinó a Beatrice Sharp, por celos, según entiendo.";
			link.l1.go = "saga_66";
		break;
		
		case "saga_66":
			dialog.text = "Bueno, sabes mucho. Sí, realmente había estado cortejando a Jess, pero no fue una sorpresa, todos los piratas de Isla Tesoro estaban divididos en dos grupos diferentes en ese entonces: aquellos que querían follar a Beatrice y aquellos que querían a Jessica.\nLa recuerdo bien... ¡Era hermosa, muy hermosa!..";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuest("Video_Jess");
			NextDiag.TempNode = "saga_66a";
		break;
		
		case "saga_66a":
			dialog.text = "Era especial... También es bastante probable que Jess matara a Beatrice. Después de que el Carnicero la echara del 'Neptune', probablemente no pensó en otra cosa más que en vengarse de él y de Beatrice. Por cierto, ¿sabes cómo se deshizo el Carnicero de Jessica?";
			link.l1 = "No. O la dejó en Barbados o la puso a pedir rescate.";
			link.l1.go = "saga_67";
		break;
		
		case "saga_67":
			dialog.text = "El segundo. La humilló más allá de lo creíble. Simplemente la encerró en el camarote, la llevó a Barbados, comenzó a negociar con su padre Oliver Rose y de hecho la vendió por un montón de doblones... después de todo lo que ella había hecho por él.";
			link.l1 = "Hm. Pensé que el Carnicero protegió su honor cuando los piratas capturaron el 'Neptune' de Joshua Leadbeater...";
			link.l1.go = "saga_68";
		break;
		
		case "saga_68":
			dialog.text = "Eso también es cierto. Pero ella también le pagó generosamente como recompensa. Jessica salvó la patética vida de ese canalla en varias ocasiones, levantándolo del lecho de clavos que él mismo se preparaba regularmente por su juerga y su feroz temperamento. Fue en realidad solo gracias a ella que alcanzó la gloria de un próspero pirata.";
			link.l1 = "Sí, sí, su 'talismán rojo'. Escuché sobre eso. Dicen que en cuanto el Carnicero echó a Jess, su suerte hizo lo mismo con él...";
			link.l1.go = "saga_69";
		break;
		
		case "saga_69":
			dialog.text = "Pero por supuesto. Sin Jessica, él se había convertido en otro corsario común, aunque muy valiente. Pero Jessica no estaba allí para él, ella era quien lo ayudaba a planear todas sus arriesgadas operaciones y siempre podía contar con su espada. Claro, Beatrice tampoco era una buena chica, pero no podía compararse con Jess, los encantos de Bea eran completamente diferentes... Cometió el error de meterse con el Carnicero.";
			link.l1 = "Ya he oído eso en algún lugar...";
			link.l1.go = "saga_70";
		break;
		
		case "saga_70":
			dialog.text = "Todos los piratas pensaban así, incluido Blaze Sharp, su hermano. No podía soportar al Carnicero... Pero volvamos a Jessica. Ni siquiera me atrevía a pensar en ella mientras estaba en el 'Neptune', nunca dejaría a su amado capitán. Pero cuando el Carnicero se deshizo de ella de una manera tan vil...\nLlegué a Barbados y me hice amigo de ella. No fue fácil para ella, amaba el mar y las aventuras peligrosas. Esa vida monótona de la colonia la estaba matando. Además, se había convertido en una persona muy infame en el Caribe mientras servía en el 'Neptune' y la gente de Bridgetown tenía razones para considerarla cómplice del Carnicero...";
			link.l1 = "Pero no pudieron probar una mierda...";
			link.l1.go = "saga_71";
		break;
		
		case "saga_71":
			dialog.text = "No. Pero tampoco nadie quería tener nada que ver con ella. La consideraban maldita, a pesar de su estatus en Bridgetown. Supongo que fui el único hombre que pasó más de media hora con Jessica allí.\nLe ofrecí venir conmigo al Oeste y comenzar una nueva vida allí. La vida que siempre deseó: el mar, los barcos, los viajes, las aventuras. Ya había establecido una gran operación en Blueweld para entonces y pude ofrecerle cien veces más que esa escoria de Butcher. Pero Jess estaba muy herida. No había perdonado a Butcher por su traición y por cómo la trató después. Y creo que todavía sentía algo por él, incluso entonces... A pesar de todos mis esfuerzos, no pude hacerla olvidar el pasado, estaba obsesionada con pensamientos de venganza.";
			link.l1 = "Sí, no la envidio. Pobre chica...";
			link.l1.go = "saga_72";
		break;
		
		case "saga_72":
			dialog.text = "Sentía lo mismo por ella. Y más tarde ella comenzó a interesarse por los antiguos cultos y rituales indios. Ocurrió después de que capturaron a un mago indio y lo trajeron de las profundidades de las selvas de Yucatán a la plantación. Jessica lo compró y le dio una casa en su plantación.\nPasaba mucho tiempo con el mago. Decía que todo era por su interés histórico en los rituales mágicos indios. La gente de Bridgetown se preocupó, especialmente el pastor. En realidad, él era uno de los pocos que fue amable con Jessica.\nEl sacerdote a menudo hablaba con ella, persuadiéndola para que se deshiciera del mago, amenazándola con peligros y la inquisición, pero tratar de asustar a Jessica era un ejercicio inútil. Una noche, unos extraños irrumpieron en la casa del mago y lo asesinaron.\nEsa misma noche, dos hombres atacaron a Jessica en su propia habitación, pero no les fue bien - nadie en Bridgetown sabía lo bien que Jess manejaba su espada con hoja de fuego. Literalmente los cortó en rebanadas.";
			link.l1 = "Sí, claro... ¡esa virago temeraria!";
			link.l1.go = "saga_73";
		break;
		
		case "saga_73":
			dialog.text = "Después de eso, todo el pueblo empezó a temerle. Y luego apareció la Máscara. Se encontraron bastante rápido.";
			link.l1 = "Según los escritos, la Máscara es Joshua Leadbeater, el antiguo capitán del 'Neptune'...";
			link.l1.go = "saga_74";
		break;
		
		case "saga_74":
			dialog.text = "Me enteré de eso mucho más tarde. Una semana después de la llegada de la Máscara, Jess tomó sus cosas, se despidió de mí y zarpó en una fragata militar hacia direcciones desconocidas. Nunca regresó... al igual que Beatrice nunca regresó a Isla Tesoro.\nPoco después, colgaron al Carnicero en St. John's, lo llevó allí la propia Máscara. Pero sobrevivió al Carnicero solo por un día.";
			link.l1 = "Sí... Nuestro Steven Dodson mostró clase...";
			link.l1.go = "saga_75";
		break;
		
		case "saga_75":
			dialog.text = "Sí, eso es lo que me dijeron. Vengó a Beatrice... Y así termina la historia de Jessica, falleció en algún lugar de una isla deshabitada en un enfrentamiento con los piratas de Butcher. Nadie sabe dónde está ese lugar. Butcher está muerto, y también lo están Jackman y Hangman.";
			link.l1 = "Ahí es donde te equivocas, Jan. El Carnicero está vivo.";
			link.l1.go = "saga_76";
		break;
		
		case "saga_76":
			dialog.text = "¿Qué!? ¡No puede ser! ¡Lo ahorcaron!";
			link.l1 = "Lee el testimonio de Raymond Baker. Es mejor que cualquier historia.";
			link.l1.go = "saga_77";
		break;
		
		case "saga_77":
			PlaySound("interface\important_item.wav");
			dialog.text = "Muéstrame eso...(leyendo) Hum. ¡Increíble! ¡Resulta que su ejecución fue fingida!";
			link.l1 = "Astuto, ¿eh? Pero eso no es todo. Conoces al Carnicero. Solo que no sabes quién es ahora.";
			link.l1.go = "saga_78";
		break;
		
		case "saga_78":
			dialog.text = "¿Sí? ¿Y quién es él?";
			link.l1 = "Lawrence Beltrope de Port Royal. El dueño de la mina, esa sombra muy misteriosa que está detrás de Jackman. Lo descubrí a través de Baker y Baker lo supo por la Máscara.";
			link.l1.go = "saga_79";
		break;
		
		case "saga_79":
			dialog.text = "¡Santo diablo! ¿Así que resulta que él es el que lo orquestó todo? Bueno, está bien... También nos dirigiremos al Carnicero. Meditaré sobre cómo deshacernos de este maldito embaucador. Aunque no será fácil, está bajo la protección sostenible de las autoridades inglesas.";
			link.l1 = "Su hora llegará, Jan. Pronto, se encontrará con su contramaestre y oficial de cubierta. Muy bien, gracias por la historia. Es hora de que me vaya.";
			link.l1.go = "saga_80";
		break;
		
		case "saga_80":
			dialog.text = "¿A dónde te diriges ahora mismo?";
			link.l1 = "A alguna isla. Creo que es el mismo lugar donde Jess y Beatrice fallecieron y donde la Máscara atacó a Carnicero-Beltrope. Necesito pruebas de que Helen pertenece a la familia Sharp y espero desenterrarlas allí.";
			link.l1.go = "saga_81";
		break;
		
		case "saga_81":
			dialog.text = "Está bien. Entonces, "+pchar.name+", mucha suerte para ti. Dame los detalles cuando regreses.";
			link.l1 = "Claro que sí. ¡Hasta luego, Jan!";
			link.l1.go = "saga_81a";
		break;
		
		case "saga_81a":
			DialogExit();
			LAi_SetHuberType(npchar);
			NextDiag.TempNode = "First time";
			NextDiag.CurrentNode = "First time";
			DeleteAttribute(npchar, "quest.jessika");
			npchar.quest.jessika_peace = "true"; // атрибут на мирное разрешение после боя
		break;
		
		case "saga_82":
			dialog.text = "Buen trabajo, "+pchar.name+". Has logrado lo imposible. Todos nosotros, barones de la Hermandad de la Costa, te estamos en deuda.";
			link.l1 = "Sí, el camino hacia la victoria fue estrecho. Si tan solo hubiera sabido de antemano que tendría que soportar tanto...";
			link.l1.go = "saga_83";
		break;
		
		case "saga_83":
			dialog.text = "¿Cómo está Helen? ¿Qué planea hacer?";
			if (CheckAttribute(pchar, "questTemp.Saga.Helena_officer"))
			{
				link.l1 = "Se queda en mi barco conmigo. Ya no es solo una oficial ordinaria. El control sobre la isla se dará al líder de la Hermandad, y lo único que ella recibirá es el alquiler. Helen lo ha decidido por sí misma.";
				link.l1.go = "saga_84";
			}
			else
			{
				link.l1 = "Se fue a Isla Tesoro para tomar el baronazgo en sus propias manos.";
				link.l1.go = "saga_85";
			}
		break;
		
		case "saga_84":
			dialog.text = "Bueno, "+pchar.name+"... ¡Enhorabuena! Muchos hombres han soñado con estar en tus zapatos. Me alegra que Helen haya elegido a un hombre que la merece. No podría haber un mejor candidato que tú para ser su compañero de vida.";
			link.l1 = "¡Gracias, Jan! Ahora me gustaría retomar nuestra conversación sobre Tortuga y Levasseur.";
			link.l1.go = "saga_86";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock"))
			{
				link.l1 = "¡Gracias, Jan!";
				link.l1.go = "saga_87";
			}
		break;
		
		case "saga_85":
			dialog.text = "Maravilloso. Ella se lo merece. Creo que el nuevo jefe de la Hermandad la ayudará a manejar sus asuntos. Es una chica joven, talentosa y brillante que puede captar rápidamente y aprender cualquier cosa. Gracias, "+pchar.name+"¡Helen es como una hija para mí y estoy encantado de que un futuro tan maravilloso se haya abierto para ella!";
			link.l1 = "De nada, Jan... De todos modos, me gustaría volver a nuestra conversación sobre Tortuga y Levasseur.";
			link.l1.go = "saga_86";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock"))
			{
				link.l1 = "De nada, Jan.";
				link.l1.go = "saga_87";
			}
		break;
		
		case "saga_86":
			sTemp = "Shark Dodson";
			if (CheckAttribute(pchar, "questTemp.Saga.DodsonDie")) sTemp = "Marcus Tyrex";
			dialog.text = "Mientras estabas fuera, "+sTemp+" y yo ya lo hemos discutido y llegamos a una opinión común respecto a la eliminación de Levasseur. Zarpa hacia Isla Tesoro y habla con nuestro nuevo jefe, él te dará los detalles de nuestro plan y te brindará toda la ayuda que pueda darte.";
			link.l1 = "¡Por fin huelo el aroma de la pólvora! No hay tiempo que perder, ¡me dirijo a Isla Tesoro!";
			link.l1.go = "saga_87";
		break;
		
		case "saga_87":
			dialog.text = ""+pchar.name+", espera un momento. Tengo un par de obsequios para ti por tu ayuda con Helen y los Hermanos. El primero es el amuleto encantado de Saraceno del lejano Oriente. Sus encantos fortifican la disciplina en el barco, verificado personalmente por mí. Aquí tienes.";
			link.l1 = "¡Gracias!";
			link.l1.go = "saga_88";
		break;
		
		case "saga_88":
			GiveItem2Character(pchar, "talisman4");
			Log_Info("Has recibido el amuleto 'Janissary'.");
			PlaySound("interface\important_item.wav");
			dialog.text = "El segundo es solo un recuerdo de aventuras pasadas. Convencí al Consejo de lanzar este ridículo vestigio de usar fragmentos de piedra al viento. Ya no son necesarios. Te los daré. Tal vez encuentres alguna manera de darles uso.";
			link.l1 = "¿Un uso para los fragmentos? Hm. No sé... ¡pero como recuerdo, estoy muy agradecido!";
			link.l1.go = "saga_89";
		break;
		
		case "saga_89":
			GiveItem2Character(pchar, "splinter_js"); 
			GiveItem2Character(pchar, "splinter_nh"); 
			GiveItem2Character(pchar, "splinter_mt"); 
			GiveItem2Character(pchar, "splinter_zm"); 
			GiveItem2Character(pchar, "splinter_jb"); 
			Log_Info("Has recibido cinco fragmentos de patrones ornamentales");
			dialog.text = "Bueno, no te olvides de tu amigo, "+pchar.name+". Pasa por mi lugar cuando ancles en Blueweld. Nos sentaremos y beberemos un poco de ron. Siempre me alegra verte.";
			link.l1 = "Definitivamente, Jan. Ahora tenemos algo que recordar, ¿verdad? ¡Ja-ja! De todos modos, debo irme.";
			link.l1.go = "saga_90";
		break;
		
		case "saga_90":
			dialog.text = "Buena suerte, "+pchar.name+".";
			link.l1 = "Nos vemos...";
			link.l1.go = "saga_91";
		break;
		
		case "saga_91":
			DialogExit();
			pchar.questTemp.Saga = "end";
			if (CheckAttribute(pchar, "questTemp.PZ_DialogSvensonBlock")) AddQuestRecord("Saga", "26_1");
			else 
			{
				AddQuestRecord("Saga", "26");
				pchar.questTemp.Terrapin = "islatesoro";
			}
			CloseQuestHeader("Saga");
			ChangeCharacterComplexReputation(pchar, "fame", 5);
		break;
		
	// --> провалы Саги
		case "saga_f_1":
			dialog.text = "Sí... Realmente parece que nuestro plan se ha venido abajo. Ahora no podremos poner a quien queríamos como jefe de la Hermandad. Jackman está muerto, eso está bien. Pero, ay, mi plan no va a funcionar ahora. Tendremos que elegir al jefe de la Hermandad de la manera habitual y Dios sabe qué tipo de giro va a tomar...";
			link.l1 = "Eso es desafortunado. Muy desafortunado. Y parece que Helen se quedará sin su herencia.";
			link.l1.go = "saga_f_2";
		break;
		
		case "saga_f_2":
			dialog.text = "Sí, "+pchar.name+"Y me gustaría ayudarte a tomar Tortuga, de verdad me gustaría, pero ahora ni siquiera sé cómo. Probablemente no hay nada que pueda hacer para ayudar. Parece que tendrás que confiar solo en tus propias fuerzas y tu habilidad para luchar.";
			link.l1 = "Parece que no queda otra opción... Está bien, Jan, iré a pensar qué hacer a continuación. Hasta luego...";
			link.l1.go = "saga_f_3";
		break;
		
		case "saga_f_3":
			dialog.text = "Detente por aquí, "+pchar.name+" Siempre me alegra verte.";
			link.l1 = "... ";
			link.l1.go = "exit";
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			CloseQuestHeader("Testament");
		break;
		
		case "saga_l1": // проход первый - отбираем Элен и закрываем вход к Свенсону
			DialogExit();
			LAi_CharacterDisableDialog(npchar);
			LocatorReloadEnterDisable("SantaCatalina_houseS1", "reload2", true); // закрыть кабинет Свенсона
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l1";
			pchar.quest.Saga_Late_1.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_1.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_1.function = "Saga_HelenaTalk";
			pchar.questTemp.Saga.Jackman = "true";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
		break;
		
		case "saga_l2": // проход второй - отбираем Элен, Натана и Данни в Марун-Таун, чистим квестовый лут
			dialog.text = "Pero ay, es demasiado tarde para hacer algo ahora. Isla Tesoro está oficialmente transferida a la autoridad de la corona inglesa. Hay una guarnición allí ahora. Este es un golpe pesado para la Hermandad, del cual, me temo, no podremos recuperarnos.";
			link.l1 = "Qué horrible... Ah, debería haber actuado más rápido. Entonces, ves, todo habría salido bien. Está bien, Jan, iré a pensar qué hacer a continuación. Nos vemos más tarde...";
			link.l1.go = "saga_l2_1";
		break;
		
		case "saga_l2_1":
			dialog.text = "Pasa por aquí, "+pchar.name+". Siempre me alegra verte.";
			link.l1 = "...";
			link.l1.go = "saga_l2_2";
		break;
		
		case "saga_l2_2":
			DialogExit();
			pchar.questTemp.Saga = "end";
			CloseQuestHeader("Saga");
			RemoveItems(pchar, "splinter_nh", 1);
			RemoveItems(pchar, "splinter_mt", 1);
			RemoveItems(pchar, "splinter_jb", 1);
			RemoveItems(pchar, "splinter_zm", 1);
			RemoveItems(pchar, "letter_parol", 1);
			RemoveItems(pchar, "map_sharp_full", 1);
			sld = characterFromId("Nathaniel");
			sld.model = "Hawk_2";
			Characters_RefreshModel(sld); // наверно не нужно
			sld.greeting = "nathaniel_2";
			sld.dialog.currentnode = "marun_town";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "sit", "sit1");
			LAi_SetHuberType(sld);
			LocatorReloadEnterDisable("FortOrange_town", "reload6", false); // открыть резиденцию Хоука
			sld = characterFromId("Danielle");
			sld.dialog.currentnode = "marun_town";
			sld.greeting = "danny_2";
			ChangeCharacterAddressGroup(sld, "FortOrange_townhall", "goto", "goto1");
			LAi_SetStayType(sld);
			// Элен - к разговору
			sld = characterFromId("Helena");
			sld.quest.talk = "late_l2";
			pchar.quest.Saga_Late_2.win_condition.l1 = "Location_Type";
			pchar.quest.Saga_Late_2.win_condition.l1.location_type = "town";
			pchar.quest.Saga_Late_2.function = "Saga_HelenaTalk";
			Saga_ChangesIslatesoro(); // вызов перестановки на Исла-Тесоро
			pchar.questTemp.Saga_Late = true; // второй атрибут, отсекающий диалоги, на всякий пожарный
		break;
		
		case "saga_l3":
			dialog.text = "Sí... Realmente acabamos de sufrir una dura derrota. Y lo peor de todo es que estábamos literalmente a un paso de la victoria. ¡Caramba! ¿Cómo pudo suceder esto, eh, "+pchar.name+"? Te esforzaste tanto, hiciste tanto y... ¡qué mala suerte!";
			link.l1 = "Soy el imbécil responsable de esto. Debería haber sido más rápido. Y gracias a mí, Helen va a perder su herencia. Y el plan de Tortuga nunca se realizará.";
			link.l1.go = "saga_f_2";
			pchar.questTemp.Saga_Late = true; // второй атрибут, отсекающий диалоги, на всякий пожарный
		break;
	// <-- провалы Саги
		
	//-----------------------------------генератор торговли бакаутом--------------------------------------------
		case "trade_bakaut":
			if (CheckAttribute(pchar, "questTemp.UpgradeBakaut"))
			{
				dialog.text = "Está bien, no me importa. Tengo veinticinco unidades en mi almacén. El precio, como recordarás, es de 3150 doblones.";
				if (PCharDublonsTotal() >= 3150)
				{
					link.l1 = "Está bien, trato hecho. Aquí tienes. Aquí 3150 doblones.";
					link.l1.go = "trade_bakaut_1";
				}
				else
				{
					link.l1 = "Vaya mala suerte. Olvidé mi dinero en mi barco. Volveré con él en un momento.";
					link.l1.go = "exit";
				}
			}
			else
			{
				dialog.text = "Está bien, no me importa. Tengo veinticinco unidades en mi almacén. El precio, como recordarás, es de treinta doblones por pieza.";
				if (PCharDublonsTotal() >= 750)
				{
					link.l1 = "Está bien, trato hecho. Aquí tienes. Aquí tienes setecientos cincuenta doblones.";
					link.l1.go = "trade_bakaut_1";
				}
				else
				{
					link.l1 = "Vaya mala suerte. Olvidé mi dinero en mi barco. Volveré con él en un momento.";
					link.l1.go = "exit";
				}
			}
			if(sti(pchar.questTemp.SvensonBakaut) >= 1 && !CheckAttribute(pchar, "questTemp.SvensonBakautBlock")) // увеличить объём поставок бакаута
			{
				link.l4 = "Jan, ¿sería posible aumentar el tamaño de los envíos de guayacán?";
				link.l4.go = "UpgradeBakaut";
			}
			if(sti(pchar.questTemp.SvensonBakaut) >= 1 && CheckAttribute(pchar, "questTemp.SvensonBakautPotom") && PCharDublonsTotal() >= 3000) // увеличить объём поставок бакаута, если в первый раз не принесли
			{
				link.l4 = "Jan, he reunido tres mil monedas de oro. Toma, puedes presentar este regalo a nuestros parásitos. Supongo que tendrán un día feliz hoy.";
				link.l4.go = "UpgradeBakaut_Agreed";
			}
		break;
		
		case "trade_bakaut_1":
			RemoveDublonsFromPCharTotal(750);
			Log_Info("Has dado 750 doblones");
			PlaySound("interface\important_item.wav");
			dialog.text = "Loable. Ordenaré a mi gente que transporte el sándalo a tu barco.";
			link.l1 = "¡Gracias!";
			link.l1.go = "trade_bakaut_2";
		break;
		
		case "trade_bakaut_2":
			dialog.text = "Si quieres comprar más, vuelve en dos semanas. Para entonces habré reunido otro lote.";
			link.l1 = "¡Está bien, Jan. ¡Hasta la próxima!";
			link.l1.go = "exit";
			AddCharacterGoods(pchar, GOOD_SANDAL, 25);
			DeleteAttribute(npchar, "quest.trade_bakaut");
			SetFunctionTimerCondition("Bakaut_SvensonAttrReturn", 0, 0, 1, false); // таймер
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;
		
		case "UpgradeBakaut": //
			if (startHeroType == 1) sStr = "amigo";
			if (startHeroType == 2) sStr = "amigo";
			if (startHeroType == 3) sStr = "amigo";
			if (startHeroType == 4) sStr = "Helen";
			if (GetSummonSkillFromName(pchar, SKILL_COMMERCE) >= 80)
			{
				dialog.text = "Me alegra que el guayacán sea de tu agrado, " + sStr + ". Aumentar los envíos no es problema, pero hay un 'pero', ya sabes. Con el aumento de volumen aparece también un rastro que puede atraer atención indeseada, especialmente de las autoridades inglesas. Pero si añadimos al negocio manos confiables, oídos fieles y personas en la residencia que ayuden a permanecer en las sombras, todo se puede arreglar. Claro que no saldrá barato - tres mil doblones para evitar el tesoro de la ciudad y las necesidades de Inglaterra. Entonces podré suministrarte cinco veces más. ¿Qué dices?";
				link.l1 = "¿Tres mil doblones? ¡Jan, eso es un robo a plena luz del día! ¿No podríamos arreglárnoslas con menos gastos? ¿Quizás haya una manera de resolver el asunto sin tales sumas fabulosas?";
				link.l1.go = "UpgradeBakaut_1";
				notification("Skill Check Passed", SKILL_COMMERCE);
			}
			else
			{
				dialog.text = "Buena idea, pero debo decir que para tales volúmenes en asuntos comerciales se necesita un poco más de experiencia y habilidad. Si te apresuras, hay más riesgo que beneficio. Hagamos esto: adquiere un poco más de experiencia, y cuando estés list"+GetSexPhrase("o","a")+" para lotes más grandes, vuelve. Entonces discutiremos todo adecuadamente.";
				link.l1 = "Hmm... Está bien. Volvamos a esta conversación más tarde.";
				link.l1.go = "exit";
				notification("Skill Check Failed (80)", SKILL_COMMERCE);
			}
		break;
		
		case "UpgradeBakaut_1":
			dialog.text = "Por desgracia, "+pchar.name+", ese es el precio de la paz hoy en día - los apetitos de esos señores con pelucas y uniformes crecen cada día. Nada les atrae más que los doblones que tintinean en sus arcas. Te garantizo un descuento del quince por ciento en todos los envíos posteriores, si eso te consuela.";
			link.l1 = "¡Malditos sean! ¡Pedir tales sumas! ¡Con tal codicia deberían estar comprando tesoros de reyes, no regateando por silencio! Jan, tal vez deberíamos... mostrarles quién es el verdadero poder en el archipiélago, ¿eh?";
			link.l1.go = "UpgradeBakaut_2";
		break;
		
		case "UpgradeBakaut_2":
			if (startHeroType == 1) sStr = "amigo";
			if (startHeroType == 2) sStr = "amigo";
			if (startHeroType == 3) sStr = "amigo";
			if (startHeroType == 4) sStr = "Helen";
			dialog.text = "¡Ja! ¡Qué entusiasmo tienes, " + sStr + "! Pero ir contra toda Inglaterra no me conviene ahora, y ya no soy tan joven como antes. Paguemos simplemente a estos chupasangres, y que se queden quietos - tenemos nuestro negocio que hacer. Reúne la suma necesaria, y nuestro camino estará libre, ¡sin preguntas innecesarias!";
			if (PCharDublonsTotal() >= 3000)
			{
				link.l1 = "Bueno, de acuerdo, Jan, me has convencido. Que así sea, ya que no hay otra manera. Aquí tienes tus tres mil doblones. Solo recuerda: no tengo intención de alimentar a estos avaros para siempre.";
				link.l1.go = "UpgradeBakaut_Agreed";
			}
			link.l2 = "¡Que el diablo se los lleve, Jan! ¿Realmente crees que no hay otra salida? Está bien. Encontraré esos doblones. Pero ahora mismo no tengo ese dinero.";
			link.l2.go = "UpgradeBakaut_4";
			link.l3 = "Maldita sea, Jan, ¿realmente quieres que alimente a estos funcionarios con sus refinadas damas? ¡Se sientan en sus sillas, no hacen nada, y solo exigen dinero! ¡No, no me gusta esto! ¡No voy a llenar sus bolsillos con mi sudor y sangre! Volvamos a los términos anteriores. Eso es suficiente para mí.";
			link.l3.go = "UpgradeBakaut_3";
		break;
		
		case "UpgradeBakaut_Agreed":
			dialog.text = "¡Ahora sí que hablamos! Con tu contribución nuestro negocio funcionará como la seda, y estos avaros recibirán lo suyo y dejarán incluso de mirar en dirección al guayacán. Te aseguro que pronto recuperaremos todas las inversiones multiplicadas por cien.";
			link.l1 = "Eso espero, Jan, eso espero.";
			link.l1.go = "UpgradeBakaut_Agreed_1";
			RemoveDublonsFromPCharTotal(3000);
			AddQuestRecordInfo("Unique_Goods", "1_1");
			pchar.questTemp.UpgradeBakaut = true;
			pchar.questTemp.SvensonBakautBlock = true;
			DeleteAttribute(pchar, "questTemp.SvensonBakautPotom");
		break;
		
		case "UpgradeBakaut_Agreed_1":
			dialog.text = "Los negocios irán como deben, no te preocupes. Y ahora, en cuanto a nuestros futuros tratos: mantendré listos para ti 125 troncos de guayacán, como antes, para el 14 y el 28 de cada mes. Puedes llevarte todo el lote por 3150 doblones.";
			link.l1 = "¡Me gustan mucho más estas conversaciones! ¿Ciento veinticinco troncos, entonces? Excelente, Jan. Bueno, hasta pronto, ¡esperaré el envío!";
			link.l1.go = "exit";
		break;
		
		case "UpgradeBakaut_3":
			if (startHeroType == 1) sStr = "amigo";
			if (startHeroType == 2) sStr = "amigo";
			if (startHeroType == 3) sStr = "amigo";
			if (startHeroType == 4) sStr = "Helen";
			dialog.text = "Como desees, " + sStr + ". Y no te alteres tanto. Así es como está organizado este mundo.";
			link.l1 = "Sí, Jan, sé cómo está organizado este mundo. Pero eso no significa que yo deba tolerarlo. Bien, debo irme.";
			link.l1.go = "exit";
			pchar.questTemp.SvensonBakautBlock = true;
		break;
		
		case "UpgradeBakaut_4":
			dialog.text = "Esperaré hasta que reúnas el dinero. Sé que encontrarás una manera. Tan pronto como estés list"+GetSexPhrase("o","a")+" - te esperaré con el dinero, y continuaremos.";
			link.l1 = "Muy bien.";
			link.l1.go = "exit";
			pchar.questTemp.SvensonBakautBlock = true;
			pchar.questTemp.SvensonBakautPotom = true;
		break;
		// <-- генератор бакаута
		
	//----------------------------------- штурм рудника --------------------------------------------
		case "mine_attack":
			dialog.text = "Me alegra verte, "+pchar.name+". Mis hombres están listos. ¿Hacia la selva?";
			link.l1 = "Sí, Jan. Mi escuadrón está listo para la batalla.";
			link.l1.go = "mine_attack_1";
		break;
		
		case "mine_attack_1":
			dialog.text = "Entonces, avancemos. La mina está en la gran profundidad de la jungla justo a lo largo de este sendero. Mantente a la derecha en la bifurcación. ¡Adelante!";
			link.l1 = "¡Adelante!";
			link.l1.go = "mine_attack_2";
		break;
		
		case "mine_attack_2":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Svensons_off_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
				LAi_group_MoveCharacter(sld, LAI_GROUP_PLAYER);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("shore53", "boat", true);
			LocatorReloadEnterDisable("mine_03", "reload3_back", true);
			LocatorReloadEnterDisable("mine_02", "reload3_back", true);
			pchar.quest.Saga_MineAttack_01.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_01.win_condition.l1.location = "Mine_02";
			pchar.quest.Saga_MineAttack_01.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_3":
			dialog.text = "Entonces, "+pchar.name+", es hora de discutir cómo vamos a llevar a cabo esta operación. Ya he enviado a varios indios miskitos de antemano para inspeccionar el área y he compuesto un plan de acción basado en sus observaciones.";
			link.l1 = "¡Ponme al corriente!";
			link.l1.go = "mine_attack_4";
		break;
		
		case "mine_attack_4":
			dialog.text = "La fosa representa la mina bajo las montañas en la jungla. Hay un campamento cerca de una entrada de la mina. Unas pocas casas y una empalizada. Hay un camino que lleva a la empalizada. Mira, lleva a un pequeño espacio despejado en la jungla no muy lejos de aquí. Ahí es donde se encuentra la entrada principal a la fosa.\nRepresenta un alto muro de piedra entre dos colinas empinadas, impidiendo que cualquiera se infiltre dentro. Las puertas están protegidas por una guardia de seis hombres. No es gran cosa, pero también han colocado dos cañones allí. Ese es el mayor problema.\nDos descargas de metralla pueden derribar a la mitad de nuestro escuadrón, lo cual sería un desastre, así que un ataque frontal no es una opción...";
			link.l1 = "¡Ja! Pero tenemos un as bajo la manga, sabemos la contraseña que nos permitirá entrar...";
			link.l1.go = "mine_attack_5";
		break;
		
		case "mine_attack_5":
			dialog.text = "Eso es correcto. Usaremos eso a nuestro favor, pero por ahora permíteme explicarte todo mi plan hasta el final.";
			link.l1 = "Claro, Jan. Soy todo oídos.";
			link.l1.go = "mine_attack_6";
		break;
		
		case "mine_attack_6":
			dialog.text = "Hay otra entrada a la mina, por ese sendero en la jungla. Rodea las colinas que protegen la mina y lleva a un pequeño y estrecho hueco que puede usarse para entrar. Pero los bandidos han levantado una alta cerca y han puesto guardias allí. La cerca tiene pequeñas puertas, pero están bloqueadas desde el otro lado.\nAhora escucha lo que vamos a hacer. Nos desharemos de aquellos que vigilan la segunda entrada a la mina. Parte de nuestro escuadrón se quedará allí y encontrarán algún tronco para usarlo como ariete.\nRegresaremos a la entrada principal y mataremos a los artilleros. La contraseña que tenemos nos ayudará dos veces. Luego atacaremos la mina desde dos lados. Yo lideraré la primera unidad de asalto y tú liderarás la segunda.";
			link.l1 = "Bueno, es lógico. Los haremos luchar contra nosotros en dos frentes. ¡Adelante!";
			link.l1.go = "mine_attack_7";
		break;
		
		case "mine_attack_7":
			DialogExit();
			LAi_SetActorType(npchar);
			npchar.quest.mine01 = "true";
			LAi_ActorFollowEverywhere(npchar, "", -1);
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", true);//офицеров не пускать
			pchar.quest.Saga_MineAttack_02.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_02.win_condition.l1.location = "Mine_04";
			pchar.quest.Saga_MineAttack_02.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_8":
			dialog.text = "Bien, aquí estamos... Este es el camino hacia la valla de los bandidos. Ahora debemos decidir cómo tratar con ellos. Si enviamos a todo el escuadrón allí, será demasiado sospechoso y darán la alarma.\nDeberíamos enviar un pequeño grupo de tres, no más, este grupo podrá acercarse lo suficiente sin levantar sospechas y atacar por sorpresa. Yo no puedo liderar el grupo, mi rostro es demasiado conocido por aquí.\nAsí que depende de ti, "+pchar.name+", porque eres el único en quien puedo confiar para comandar sin arriesgar toda la operación. Te daré a Gregory y a un mosquetero para que te asistan...";
			link.l1 = "¿Cuántos guardias hay en la valla de piquetes?";
			link.l1.go = "mine_attack_9";
		break;
		
		case "mine_attack_9":
			dialog.text = "Cuatro. Dos mosqueteros y dos soldados.";
			link.l1 = "Los tomaremos...";
			link.l1.go = "mine_attack_10";
		break;
		
		case "mine_attack_10":
			dialog.text = "Conociéndote, ni siquiera lo dudo por un segundo. Acércate a ellos y diles que te envió Jackman. Diles la contraseña. Y luego, cuando todos estén relajados... actúa según las circunstancias.";
			link.l1 = "Está bien. Los mantendremos alerta.";
			link.l1.go = "mine_attack_11";
		break;
		
		case "mine_attack_11":
			dialog.text = "Buena suerte, "+pchar.name+".";
			link.l1 = "... ";
			link.l1.go = "mine_attack_12";
		break;
		
		case "mine_attack_12":
			DialogExit();
			LAi_SetStayTypeNoGroup(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=1; i<=2; i++)
			{
				sld = characterFromId("Svensons_off_"+i);
				LAi_SetStayTypeNoGroup(sld);
				if (i == 2)
				{
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
				if (i == 12)
				{
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
				LAi_CharacterDisableDialog(sld);//запрет диалога
			}
			chrDisableReloadToLocation = false;//открыть локацию
			DeleteAttribute(npchar, "quest.mine01");
			npchar.quest.mine02 = "true";
			pchar.questTemp.Saga.MineAttack = "true";
			pchar.quest.Saga_MineAttack_03.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_03.win_condition.l1.location = "Mine_01";
			pchar.quest.Saga_MineAttack_03.function = "Saga_MineAttackTail";
		break;
		
		case "mine_attack_13":
			dialog.text = "Buen trabajo, "+pchar.name+"¡Has salido victorioso, como siempre! Ahora, mis muchachos se prepararán para iniciar una tormenta desde este lado de la mina y despejaremos la entrada principal.";
			link.l1 = "¿Entiendo que me acercaré a los guardias de nuevo?";
			if (GetCharacterIndex("Svensons_off_2") != -1 && GetCharacterIndex("Svensons_sold_12") != -1) link.l1.go = "mine_attack_14";
			else link.l1.go = "mine_attack_14a";
		break;
		
		case "mine_attack_14a":
			dialog.text = "Sí, "+pchar.name+", una vez más. Me encantaría ir yo mismo, pero seguramente me reconocerían y toda la operación se iría al traste. Será más peligroso ya que hay más enemigos, y no olvides las armas.";
			link.l1 = "Me llevaré a mis oficiales conmigo.";
			link.l1.go = "mine_attack_14_1";
		break;
		
		case "mine_attack_14":
			dialog.text = "Sí, "+pchar.name+", una vez más. Me encantaría ir yo mismo, pero seguramente me reconocerían y toda la operación se iría al traste. Será más peligroso ya que hay más enemigos, y no olvides las armas. ¿A quién llevarás contigo para ayudarte? ¿A tus oficiales o a Gregory y al mosquetero como la última vez?";
			link.l1 = "Llevaré a mis oficiales.";
			link.l1.go = "mine_attack_14_1";
			link.l2 = "Me llevaré a Gregory y al mosquetero.";
			link.l2.go = "mine_attack_14_2";
		break;
		
		case "mine_attack_14_1":
			dialog.text = "Muy bien. Tu propia gente es tu mejor respaldo. Ahora volveremos hacia la entrada principal. ¿Recuerdas el camino?";
			link.l1 = "Por supuesto. De vuelta por donde vinimos, luego mantente a la izquierda, y luego toma el sendero alrededor de la colina.";
			link.l1.go = "mine_attack_15";
			pchar.questTemp.Saga.MineAttack = "officer";
		break;
		
		case "mine_attack_14_2":
			dialog.text = "Está bien. Lo has logrado una vez, así que hacerlo por segunda vez debería ser pan comido. Ahora vamos a regresar a la entrada principal. ¿Recuerdas el camino?";
			link.l1 = "Por supuesto. Regresa por donde vinimos, luego mantente a la izquierda y toma el sendero alrededor de la colina.";
			link.l1.go = "mine_attack_15";
			pchar.questTemp.Saga.MineAttack = "soldiers";
		break;
		
		case "mine_attack_15":
			dialog.text = "Sin tiempo que perder. ¡En marcha!";
			link.l1 = "¡Adelante!";
			link.l1.go = "mine_attack_16";
		break;
		
		case "mine_attack_16":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorFollowEverywhere(npchar, "", -1);
			for (i=1; i<=2; i++)
			{
				if (GetCharacterIndex("Svensons_off_"+i) != -1)
				{
					sld = characterFromId("Svensons_off_"+i);
					LAi_SetActorType(sld);
					LAi_ActorFollowEverywhere(sld, "", -1);
				}
			}
			for (i=1; i<=12; i++)
			{
				sld = characterFromId("Svensons_sold_"+i);
				LAi_SetActorType(sld);
				if (pchar.questTemp.Saga.MineAttack == "soldiers" && i == 12) LAi_ActorFollowEverywhere(sld, "", -1);
				else LAi_ActorRunToLocation(sld, "reload", "reload3_back", "mine_01", "goto", "goto"+i, "", 5);
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetActorType(sld);
				LAi_ActorFollowEverywhere(sld, "", -1);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", false);//офицеров пускать
			if (pchar.questTemp.Saga.MineAttack == "soldiers") LAi_LocationDisableOfficersGen("mine_exit", true);//офицеров не пускать
			LocatorReloadEnterDisable("mine_03", "reload3_back", false);
			LocatorReloadEnterDisable("mine_02", "reload3_back", false);
			DeleteAttribute(npchar, "quest.mine02");
			npchar.quest.mine03 = "true";
			pchar.quest.Saga_MineAttack_05.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_05.win_condition.l1.location = "Mine_02";
			pchar.quest.Saga_MineAttack_05.function = "Saga_PrepareMineAttackTail";
		break;
		
		case "mine_attack_17":
			dialog.text = "Correcto, "+pchar.name+", escucha estas últimas instrucciones. Estos demonios que custodian las puertas son duros, así que no te será fácil. Tu objetivo principal es matar a los artilleros que están cerca de las puertas, porque no podremos venir a ayudarte si siguen respirando.\nUna vez que ambos estén muertos y no haya posibilidad de una descarga de cañón, todos vendremos y los mataremos en segundos. ¿Entendiste, "+pchar.name+"¿No juegues al héroe, mata a los artilleros y deja el resto a nosotros?";
			link.l1 = "Está bien, Jan. Intentaré hacer todo como lo planeamos. Y si algo sale mal, improvisaré.";
			link.l1.go = "mine_attack_18";
		break;
		
		case "mine_attack_18":
			dialog.text = "Suena bien. ¡Que Dios esté contigo!";
			link.l1 = "Gracias...";
			link.l1.go = "mine_attack_19";
		break;
		
		case "mine_attack_19":
			DialogExit();
			LAi_SetStayTypeNoGroup(npchar);
			LAi_CharacterDisableDialog(npchar);//запрет диалога
			for (i=1; i<=2; i++)
			{
				if (GetCharacterIndex("Svensons_off_"+i) != -1)
				{
					sld = characterFromId("Svensons_off_"+i);
					if (pchar.questTemp.Saga.MineAttack == "soldiers" && i == 2)
					{
						LAi_SetActorType(sld);
						LAi_ActorFollowEverywhere(sld, "", -1);
					}
					else LAi_SetStayTypeNoGroup(sld);
				}
			}
			for (i=1; i<=8; i++)
			{
				sld = characterFromId("Ourmine_sold_"+i);
				LAi_SetStayTypeNoGroup(sld);
			}
			chrDisableReloadToLocation = false;//открыть локацию
			LAi_LocationDisableOfficersGen("mine_01", false);//офицеров пускать
			DeleteAttribute(npchar, "quest.mine03");
			pchar.quest.Saga_MineAttack_06.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_06.win_condition.l1.location = "Mine_exit";
			pchar.quest.Saga_MineAttack_06.function = "Saga_MineAttackTail";
		break;
		
		case "mine_attack_20":
			dialog.text = "¡Uf! Acabamos con esos hijos de puta... Eran unos bribones peleones. Puedo decir que estos mercenarios solían servir en las tropas regulares. Hicimos algo de ruido aquí, me temo que nos habrán escuchado. ¡Ni un minuto que perder!"+pchar.name+", es hora de que ataquemos la mina.\nRegresaré con mi grupo en la segunda entrada - deben haber encontrado y preparado un tronco para embestir la cerca. Tú y tus hombres irán por las puertas centrales. Espéranos media hora, no ataquen de inmediato...";
			link.l1 = "Jan, si oyeron los disparos en la mina, no tenemos esta media hora. Esos bandidos podrían establecer una línea de defensa o probablemente venir directamente a las puertas centrales y atacar a mi grupo con todo lo que tienen...";
			link.l1.go = "mine_attack_21";
		break;
		
		case "mine_attack_21":
			dialog.text = "¡Maldición! Es bastante posible. ¿Qué sugieres que hagamos?";
			link.l1 = "Mm... ¡Ja! ¡Tengo una idea! ¡Cañones! Mira alrededor. ¡No solo hay metralla, sino que también se pueden encontrar bombas! ¡Ahora estos bandidos están acabados! ¿Por qué no se me ocurrió antes?!";
			link.l1.go = "mine_attack_22";
		break;
		
		case "mine_attack_22":
			dialog.text = "¿Qué crees que deberíamos hacer?";
			link.l1 = "Llevaremos un cañón. Con uno podremos movernos mucho más rápido y eficientemente. Lo rodaremos adentro, más allá de las puertas, hasta la mina y lo colocaremos en posición. Si ellos inician un ataque, recibirán un gran estruendo, y si se mantienen atrás, simplemente bombardearemos su campamento. ¿Puedes decirme dónde exactamente se encuentra el campamento detrás de las puertas?";
			link.l1.go = "mine_attack_23";
		break;
		
		case "mine_attack_23":
			dialog.text = "El campamento está en terreno bajo junto a una montaña. Hay un sendero justo más allá de las puertas que baja y serpentea alrededor de la colina. El campamento está ubicado justo detrás de esta colina.";
			link.l1 = "¡Espléndido! ¡Nos apostaremos en lo alto del sendero y lanzaremos un par de bombas sobre la colina hacia su nido! ¡Oh, los haremos bailar por todos lados!";
			link.l1.go = "mine_attack_24";
		break;
		
		case "mine_attack_24":
			dialog.text = "Maldita sea, "+pchar.name+", ¡bien hecho! ¡Toda velocidad adelante! Dejaré a Randolf bajo tu mando, es mi mejor artillero. Hazlo tu artillero y no te defraudará. Me voy a mi unidad ahora mismo.";
			link.l1 = "Está bien. Bombardearé sus posiciones hasta el infierno durante media hora hasta que rompas las puertas.";
			link.l1.go = "mine_attack_25";
		break;
		
		case "mine_attack_25":
			dialog.text = "Intentaré llegar a tiempo. ¡Nos vemos en el campamento!";
			link.l1 = "Trato hecho... ¡Escuadrón! ¡Escuchad mi orden! ¡Preparad el traslado del cañón a una nueva posición! ¡Llevad pólvora, bombas y metralla con vosotros! A la mina a través de las puertas. ¡Adelante, marcha!";
			link.l1.go = "mine_attack_26";
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload2_back", "none", "", "", "", 5);
			if (GetCharacterIndex("Svensons_off_2") != -1)
			{
				sld = characterFromId("Svensons_off_2");
				LAi_SetActorType(sld);
				LAi_ActorRunToLocation(sld, "reload", "reload2_back", "none", "", "", "", 5);
			}
		break;
		
		case "mine_attack_26":
			DialogExit();
			int n = Findlocation("mine_exit");
			DeleteAttribute(&locations[n], "mine_bandits");
			LocatorReloadEnterDisable("mine_exit", "reload1_back", false);
			pchar.quest.Saga_MineAttack_07.win_condition.l1 = "location";
			pchar.quest.Saga_MineAttack_07.win_condition.l1.location = "Mine";
			pchar.quest.Saga_MineAttack_07.function = "Saga_MineGunAttack";
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("mine_exit", "reload2_back", true);
			LAi_LocationDisableOfficersGen("mine_exit", false); // офицеров пускать
			n = Findlocation("mine");
			locations[n].models.always.Gun = "mortair";
			Locations[n].models.always.Gun.locator.group = "goto";
			Locations[n].models.always.Gun.locator.name = "fire"; // орудие - к бою!
			Locations[n].hidden_sound = true;
		break;
		
		case "mine_attack_27":
			dialog.text = "Uf, ¿no llegamos demasiado tarde, "+pchar.name+"?";
			link.l1 = "¡Jan, maldita sea! ¿Qué te tomó tanto tiempo? ¡Mi escuadrón acaba de recibir un golpe enorme!";
			link.l1.go = "mine_attack_28";
		break;
		
		case "mine_attack_28":
			dialog.text = "¡Esa maldita cerca de madera resultó ser realmente resistente! La rompimos a la fuerza... Oímos tu alboroto. ¡Parece que has limpiado bien este lugar! ¡Está ardiendo hasta los cimientos!";
			link.l1 = "Las andanzas de Randolf... ¡Ojalá hubieras visto cuántos bastardos habíamos enterrado antes de finalmente entrar en combate cuerpo a cuerpo!";
			link.l1.go = "mine_attack_29";
		break;
		
		case "mine_attack_29":
			dialog.text = "¡Caramba! Me quito el sombrero ante ti, "+pchar.name+". ¡Bien hecho! Bueno, sobre las pérdidas... las tienes cada vez que estás en guerra.";
			link.l1 = "Ahora lo que necesitamos hacer es limpiar la mina misma. Es posible que algunos sobrevivientes se estén escondiendo allí.";
			link.l1.go = "mine_attack_30";
		break;
		
		case "mine_attack_30":
			dialog.text = "Vamos solo nosotros dos. Exploremos la situación allí.";
			link.l1 = "¡Suena como un plan!";
			link.l1.go = "mine_attack_31";
		break;
		
		case "mine_attack_31":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_SetImmortal(npchar, false);
			LAi_SetCheckMinHP(npchar, 10, true, "");
			TakeNItems(npchar, "potion2", 8); 
			LAi_SetActorType(npchar);
			LAi_ActorRunToLocation(npchar, "reload", "reload4", "Mine_mines", "reload", "reload1", "", -1);
			LAi_LocationDisableOfficersGen("Mine_mines", true);//офицеров не пускать
			pchar.quest.Saga_MineAttack_08.win_condition.l1 = "locator";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.location = "mine";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.locator_group = "reload";
			pchar.quest.Saga_MineAttack_08.win_condition.l1.locator = "reload4";
			pchar.quest.Saga_MineAttack_08.function = "Saga_MineAttackMines";
		break;
		
		case "mine_attack_32a":
			dialog.text = "¡Todavía no hemos registrado toda la mina! Te garantizo que algunos de esos sinvergüenzas se están escondiendo aquí.";
			link.l1 = "...";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_attack_32a";
		break;
		
		case "mine_attack_32":
			dialog.text = "No creo que quede otro canalla...";
			link.l1 = "Jan, pensé que solo veníamos aquí para explorar la situación...";
			link.l1.go = "mine_attack_33";
		break;
		
		case "mine_attack_33":
			dialog.text = "Ja-ja, bueno, no te dije que esta sería una exploración especial, una exploración sangrienta... ¡Hace tiempo que no tenía un calentamiento así! ¡Ahora todos pueden estar seguros de que no hay un solo desgraciado que haya escapado de esta mina!";
			link.l1 = "¿Entonces qué haremos ahora, Jan?";
			link.l1.go = "mine_attack_34";
		break;
		
		case "mine_attack_34":
			dialog.text = "¿Qué quieres decir con qué vamos a hacer ahora? Vamos a buscar oro y plata. No creo que Jackman mantuviera este tipo de baluarte aquí por aburrimiento. Colocó toda una guarnición aquí. ¿Viste a los esclavos en la mina? Deberías averiguar dónde están almacenando las extracciones.";
			link.l1 = "Está bien. Entonces tú ve a interrogar a los esclavos y yo subiré a buscar en todas las casas del campamento, quizá encuentre algo.";
			link.l1.go = "mine_attack_35";
		break;
		
		case "mine_attack_35":
			dialog.text = "¡Te tengo! ¡Es hora de moverse!";
			link.l1 = "...";
			link.l1.go = "mine_attack_36";
		break;
		
		case "mine_attack_36":
			DialogExit();
			LAi_SetCurHPMax(npchar);
			LAi_SetImmortal(npchar, true);
			LAi_SetWarriorType(npchar);
			LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
			chrDisableReloadToLocation = false;//открыть локацию
			LocatorReloadEnterDisable("mine", "reload1", true);
			LocatorReloadEnterDisable("mine", "reload6", true);//закрыть выходы с рудника
			pchar.quest.Saga_Mine_letter.win_condition.l1 = "item";
			pchar.quest.Saga_Mine_letter.win_condition.l1.item = "letter_mine";
			pchar.quest.Saga_Mine_letter.function = "Saga_FindMineLetter";
			NextDiag.CurrentNode = "mine_attack_36a";
		break;
		
		case "mine_attack_36a":
			dialog.text = "Ve, camarada. ¡Y pon patas arriba estas miserables chozas!";
			link.l1 = "¡Estoy en camino!";
			link.l1.go = "exit";
			NextDiag.TempNode = "mine_attack_36a";
		break;
		
		case "mine_attack_37":
			dialog.text = "¡Ja, ja!"+pchar.name+", ¡es estupendo que te ofrecieras a venir conmigo a destrozar esta mina! Es otro claro indicador de que naciste bajo una estrella de la suerte.";
			link.l1 = "¿Has encontrado oro?";
			link.l1.go = "mine_attack_38";
		break;
		
		case "mine_attack_38":
			dialog.text = "¡Sí, maldita sea! No oro, sino plata, un buen montón de ella. Un día más tarde y la habrían sacado del campamento. Por eso había tantos matones aquí, eran un grupo de escolta.\nGracias a ti llegamos a tiempo, sin ti todavía estaría reuniendo gente. ¡Felicitaciones, compañero!";
			link.l1 = "¡Ja! Veo... ¿Cuánta plata tenemos?";
			link.l1.go = "mine_attack_39";
		break;
		
		case "mine_attack_39":
			dialog.text = "Tenemos alrededor de cuatro mil unidades. Lo dividiremos en dos partes: la mitad para mí, la mitad para ti, tal como acordamos.";
			link.l1 = "¡Excelente! ¡Podemos ganar un montón de dinero con esas cosas!";
			link.l1.go = "mine_attack_40";
		break;
		
		case "mine_attack_40":
			dialog.text = "Eso es seguro... ¿Encontraste algo valioso?";
			link.l1 = "No. No hay ni un solo doblón en estas chozas. Aunque encontré algunos papeles. Los leí y supe que el dueño de esta mina es un tal Lawrence Beltrope de Port Royal.";
			link.l1.go = "mine_attack_41";
		break;
		
		case "mine_attack_41":
			dialog.text = "¿Oh, de veras? Déjame ver esos documentos...";
			link.l1 = "Aquí tienes.";
			link.l1.go = "mine_attack_42";
		break;
		
		case "mine_attack_42":
			RemoveItems(pchar, "letter_mine", 1);
			dialog.text = "(leyendo)... Bien... ¿Beltrope? Conozco ese apellido de algún lado. ¡Ah, sí! ¡Thomas Beltrope! Eso es interesante... Está bien, revisaré esto cuando regrese a Blueweld. ¿Te importa si me quedo con estos documentos?";
			link.l1 = "No en absoluto. No los necesito para nada.";
			link.l1.go = "mine_attack_43";
		break;
		
		case "mine_attack_43":
			dialog.text = "Bien. Ahora, queda la mejor parte, voy a transportar la plata a los barcos. Los Miskitos nos ayudarán con eso. Armaremos un carro... Mientras tanto, tú solo ve y descansa un poco, "+pchar.name+". ¡Te lo has ganado más que nadie!";
			link.l1 = "Gracias, Jan. Haremos un campamento en esa colina, el olor a ceniza es demasiado. Sí, y necesitamos apagar los fuegos en estas chozas, quién sabe, tal vez nos sean útiles en el futuro...";
			link.l1.go = "mine_attack_44";
		break;
		
		case "mine_attack_44":
			dialog.text = "¿Pensando en reclamar la mina? ¡Ja-ja! Ya he estado considerando la idea, pero saquear es una cosa, tomarla como propiedad es otra. Amigo, ya tiene dueño. Podríamos meternos en problemas con las autoridades inglesas.\nAdemás, los esclavos con los que hablaba me dijeron que todas las vetas aquí estaban básicamente agotadas - grandes lotes de plata habían sido trasladados de aquí varias veces antes. Me temo que esta mina está acabada.";
			link.l1 = "Hm...  Veremos.  Quizás no todo esté agotado. Está bien, realmente debería descansar un poco. Nos vemos más tarde, Jan";
			link.l1.go = "mine_attack_45";
		break;
		
		case "mine_attack_45":
			dialog.text = "Adelante. Y no te preocupes por nada. Nos encargaremos de todo lo demás por nuestra cuenta.";
			link.l1 = "...";
			link.l1.go = "mine_attack_46";
		break;
		
		case "mine_attack_46":
			DialogExit();
			LAi_SetActorType(pchar);
			LAi_ActorGoToLocator(pchar, "rld", "attack1", "Saga_MineWaitTime", -1);
			n = Findlocation("mine");
			DeleteAttribute(&locations[n], "hidden_sound");
			DeleteAttribute(&locations[n], "hidden_fire");
			n = Findlocation("mine_exit");
			DeleteAttribute(&locations[n], "models.always.Gun1");
		break;
		
		case "mine_attack_47":
			dialog.text = "¿Descansaste bien, "+pchar.name+"?";
			link.l1 = "No estuvo mal... Aunque, honestamente, mataría por encontrarme una taberna, tomar una copa y dormir en una cama limpia.";
			link.l1.go = "mine_attack_48";
		break;
		
		case "mine_attack_48":
			dialog.text = "Los indios han entregado la plata a la orilla y la están cargando en tu barco bajo la supervisión de mis oficiales. Ya puedes regresar. Tu deseo de ron, una taberna y una cama pronto se hará realidad. Y me gustaría que pasaras por mi casa en cinco días, todavía tenemos muchas cosas que hacer.";
			link.l1 = "¡De acuerdo, Jan! ¡Nos vemos en Blueweld en cinco días! ¡Buena suerte!";
			link.l1.go = "mine_attack_49";
		break;
		
		case "mine_attack_49":
			DialogExit();
			LAi_SetActorType(npchar);
			LAi_ActorGoToLocation(npchar, "reload", "reload4", "none", "", "", "", 15.0);
			LocatorReloadEnterDisable("shore53", "boat", false);
			LocatorReloadEnterDisable("mine", "reload1", false);
			LocatorReloadEnterDisable("mine", "reload6", false);
			LocatorReloadEnterDisable("mine_01", "reload3_back", false);
			LocatorReloadEnterDisable("mine_exit", "reload2_back", false); //открыть выходы с рудника
			LAi_LocationDisableOfficersGen("mine_mines", false); // офицеров пускать
			DeleteAttribute(pchar, "GenQuest.CannotWait");//можно мотать время
			SetFunctionTimerCondition("Saga_ReturnFromMine", 0, 0, 5, false); // таймер
			pchar.questTemp.Saga.Mines = "true"; // после Саги рудник будет разрабатываться
			ChangeCharacterComplexReputation(pchar, "fame", 2);
			DoQuestReloadToLocation("Shore53", "goto", "goto6", "");
		break;
		// <-- штурм рудника
		
		case "helensleep":
			dialog.text = "";
			link.l1 = "Jan, no me grites. Arreglemos las cosas como personas razonables - recuerda, tenemos negocios que atender.";
			link.l1.go = "helensleep_1";
		break;
		
		case "helensleep_1":
			dialog.text = "¡Soltaré a mis perros sobre ti ahora mismo, sapo! ¡Olvídate de Levasseur y piérdete!";
			link.l1 = "¡Jan! Escúchame...";
			link.l1.go = "exit";
			
			AddDialogExitQuestFunction("HelenSleep_SvensonThrowOut");
		break;
		
		case "after_drinking":
			dialog.text = "¿Qué barril? En cuanto a Helen, me aseguraré de darle una buena paliza... ¡Es broma, Charles, es broma! Sé cómo va esto, y en cuanto a Joanna, espero que esta historia la haga reflexionar un poco - ha estado especialmente gruñona últimamente, ya sabes... Bueno, así es la vida. ¡De todos modos, buena suerte en Cartagena!";
			link.l1 = "Hasta que nos encontremos de nuevo, Jan.";
			link.l1.go = "exit";
		break;
		
		case "Exit":
			NextDiag.CurrentNode = NextDiag.TempNode;
			DialogExit();
		break;
	}
}
