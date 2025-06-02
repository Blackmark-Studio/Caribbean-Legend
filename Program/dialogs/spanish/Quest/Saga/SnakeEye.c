// шаман команчей Змеиный Глаз
void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	switch (Dialog.CurrentNode)
	{
	case "First time":
		if (CheckAttribute(pchar, "questTemp.Tieyasal") && pchar.questTemp.Tieyasal == "calendar")
		{
			dialog.text = "Saludos, mi amigo pálido.";
			link.l2 = "Me alegra verte también, hermano piel roja. Tengo un asunto importante para ti nuevamente.";
			link.l2.go = "calendar";
			break;
		}
		dialog.text = "Saludos, mi pálido amigo.";
		link.l1 = "También me alegra verte, Ojo de Serpiente.";
		link.l1.go = "exit";
		if (CheckAttribute(npchar, "quest.amulet") && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Indian) && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Amulet) && CheckCharacterItem(pchar, pchar.questTemp.Saga.BaronReturn.Obereg))
		{
			link.l2 = "Te traje los amuletos que pediste. Vamos a comerciar.";
			link.l2.go = "SnakeEye_potion";
		}
		if (CheckAttribute(pchar, "questTemp.LSC")) // был в LSC
		{
			if (CheckAttribute(npchar, "quest.LSC_hello") && CheckCharacterItem(pchar, "buben"))
			{
				link.l2 = "He encontrado tu pandereta, Ojo de Serpiente. Échale un vistazo.";
				link.l2.go = "LSC_buben";
			}
			if (CheckAttribute(npchar, "quest.LSC_tube") && CheckCharacterItem(pchar, "smoking_tube"))
			{
				link.l2 = "He encontrado una interesante pipa india, Ojo de Serpiente. Échale un vistazo.";
				link.l2.go = "LSC_tube";
			}
			if (!CheckAttribute(npchar, "quest.LSC_hello"))
			{
				link.l2 = "Hola, chamán. He usado la estatua y experimentado un viaje increíble. Tenías toda la razón. ¡Encontré el cementerio de barcos, al capitán blanco e incluso la bodega con los suministros!";
				link.l2.go = "LSC_hello";
			}
			if (CheckAttribute(npchar, "quest.LSC_hello") && pchar.questTemp.Saga.BaronReturn == "shamane")
			{
				link.l3 = "Ojo de Serpiente, necesito tu ayuda.";
				link.l3.go = "Saga_nathaniel";
			}
		}
		NextDiag.TempNode = "First time";
		break;

		//---------------------------------------- первая встреча------------------------------------------------
	case "SnakeEye":
		dialog.text = "Saludos, mi pálido amigo.";
		link.l1 = "Hola, chamán. ¿Por qué asumes que soy tu amigo?";
		link.l1.go = "SnakeEye_1";
		break;

	case "SnakeEye_1":
		dialog.text = "Yo sé mucho, pero no siempre sé exactamente qué. Viniste aquí con un propósito. El destino te trajo aquí y yo te ayudo.";
		link.l1 = "¡Qué bueno saberlo! Estoy aquí precisamente para solicitar tu ayuda, mi amigo piel roja. Seré directo: ¿qué quisiste decir al contarle a la esposa de Hawk sobre Kukulcán?";
		link.l1.go = "SnakeEye_2";
		break;

	case "SnakeEye_2":
		dialog.text = "Incluso los peces muertos se dejan llevar por la corriente. Y el hombre vivo es guiado por el destino de meta en meta. La meta del capitán encadenado que fue perseguido por malas personas en la selva era la estatua de Kukulcán. Si se sacrificaba, podía estar lejos de aquí.";
		link.l1 = "No entendí nada. ¿De qué trata la estatua de tu dios y cómo pudo Hawk llegar tan lejos a pie que nadie puede encontrarlo incluso ahora?";
		link.l1.go = "SnakeEye_3";
		break;

	case "SnakeEye_3":
		dialog.text = "Si Kukulcán se comió al Halcón, entonces podría escupirlo en cualquier parte. Quizás incluso en otro mundo. Kukulcán me ha comido tres veces. Y cada vez estuve en lugares diferentes. Hace mucho tiempo llegué aquí y decidí no correr más riesgos. No fui a la boca de Kukulcán y no sé dónde escupe a sus víctimas.";
		link.l1 = "¡Jesús, esto está más allá de mi comprensión! ¿Me estás diciendo que el ídolo de piedra puede teletransportar a las personas muy lejos?";
		link.l1.go = "SnakeEye_4";
		break;

	case "SnakeEye_4":
		dialog.text = "No solo eso. Kukulcán no solo gobierna el espacio, sino también el tiempo. O incluso más. Le conté al capitán encadenado sobre la estatua de oro que devora a las personas. Quizás decidió arriesgarse cuando vio que los perseguidores estaban cerca...";
		link.l1 = "Espera, la estatua está hecha de piedra. Y estás hablando de una de oro...";
		link.l1.go = "SnakeEye_5";
		break;

	case "SnakeEye_5":
		dialog.text = "A medianoche el ídolo cobra vida y se convierte en oro. En ese momento el espíritu de Kukulcán vive en él. Teme acercarte a él o puedes ver el amanecer en un lugar diferente. Incluso las estrellas pueden cambiar de lugar en el cielo. Te encuentras con aquellos que aún no han nacido o ves el nacimiento de aquellos que murieron hace mucho tiempo o no han nacido en absoluto.";
		link.l1 = "¿Qué demonios... acertijos y más acertijos... Me intrigas, Ojo de Serpiente. Dijiste que has sobrevivido a tres encuentros con Kukulcán, el dios en el que crees. Entonces, ¿por qué no pruebo mi suerte con el ídolo del dios en el que no creo?";
		link.l1.go = "SnakeEye_6";
		break;

	case "SnakeEye_6":
		dialog.text = "Lástima. Lástima que no creas. Tal vez Kukulcán mismo te llamó y te hizo dejar la tierra de tus antepasados. Pero aún no lo escuchas. Todo sucede por una buena razón. Si decides arriesgarte, entonces debes saber que sobreviví cada vez solo porque tenía maravillosas pociones comanches.";
		link.l1 = "¿Comanche? ¿Es eso otra tribu?";
		link.l1.go = "SnakeEye_7";
		break;

	case "SnakeEye_7":
		dialog.text = "Así es como los enemigos llaman a mi gente a quienes nunca volveré a ver. La poción restaura la fuerza y la resistencia, y también cura y te salva de venenos fuertes. Necesitas varias frascos pero solo me quedan tres.\nHabía cuatro frascos pero perdí uno en un lugar extraño, parece un cementerio de barcos de hombres blancos. Allí comencé mi viaje en este mundo. Quizás Kukulcán escupió al capitán allí. Si es así, no lo envidio.";
		link.l1 = "¿Qué es este lugar? ¿El cementerio de barcos?";
		link.l1.go = "SnakeEye_8";
		break;

	case "SnakeEye_8":
		dialog.text = "Lugar extraño... No debería existir, pero existe. Allí viven personas que matan por el tono de piel. Guardan sus provisiones dentro de un gran barco donde Kukulcán me escupió. No entré en su bodega, la cual protegen de los ladrones, no son vecinos de confianza. Si llegas allí, encuentra otra salida, no entres en la bodega o habrá problemas.\nEl Chico Blanco te ayudará a encontrar otra estatua si aún vive. Dale este abalorio blanco. Le gustan.";
		link.l1 = "Mm. Ya me da vueltas la cabeza y esto se está poniendo cada vez más interesante. Continúa, hermano piel roja.";
		link.l1.go = "SnakeEye_9";
		break;

	case "SnakeEye_9":
		Log_Info("Has recibido una perla blanca");
		PlaySound("interface\important_item.wav");
		GiveItem2Character(pchar, "jewelry52");
		dialog.text = "Si encuentras al capitán con vida, podría estar muy enfermo. No tuve tiempo de darle la poción. Busca mi pandereta allí. La recibí de mi abuelo. Hay muchas cosas en la bolsa que perdí, pero solo necesito la pandereta. Es difícil hablar con los espíritus sin ella.";
		link.l1 = "¡Vaya, este lugar suena muy interesante! Esperemos que Hawk haya sido teletransportado allí... ¿Me darás tu poción?";
		link.l1.go = "SnakeEye_10";
		break;

	case "SnakeEye_10":
		dialog.text = "Te lo daré. Pero, me darás tres amuletos locales a cambio: " + XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Indian) + ", " + XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Amulet) + " y " + XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Obereg) + "  Un frasco por cada amuleto. Así es justo. Vuelve cuando tengas todos los amuletos. Entonces los intercambiaremos. No pienses que soy codicioso. O, quizá lo reconsideres mientras buscas los amuletos.";
		link.l1 = "No pensaré eso. Espérame, Ojo de Serpiente, volveré pronto.";
		link.l1.go = "SnakeEye_11";
		break;

	case "SnakeEye_11":
		DialogExit();
		NextDiag.CurrentNode = "First time";
		npchar.quest.amulet = "true";
		AddQuestRecord("BaronReturn", "3");
		AddQuestUserData("BaronReturn", "sItem1", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Indian));
		AddQuestUserData("BaronReturn", "sItem2", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Amulet));
		AddQuestUserData("BaronReturn", "sItem3", XI_ConvertString(pchar.questTemp.Saga.BaronReturn.Obereg));
		sld = characterFromId("Danielle");
		sld.quest.talk = "SnakeEye";
		pchar.quest.BaronReturn_out.win_condition.l1 = "ExitFromLocation";
		pchar.quest.BaronReturn_out.win_condition.l1.location = pchar.location;
		pchar.quest.BaronReturn_out.function = "Saga_DannyTalk";
		pchar.questTemp.HelenDrinking.GiveAmulets = true;

		// if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway") && CheckAttribute(pchar, "questTemp.PZ_Etap4_Start"))
		if (GetCharacterIndex("Longway") != -1 && CheckPassengerInCharacter(pchar, "Longway")) // Временно так
		{
			// Квест "Путеводная звезда", начало 4 этапа
			PChar.quest.PZ_Etap4_Start.win_condition.l1 = "location";
			PChar.quest.PZ_Etap4_Start.win_condition.l1.location = "Shore9";
			PChar.quest.PZ_Etap4_Start.win_condition = "PZ_Etap4_Start";
			locations[FindLocation("Shore9")].DisableEncounters = true;
		}
		break;

	// даёт зелья - идем на телепортацию
	case "SnakeEye_potion":
		dialog.text = "Bien, amigo mío. ¿Me trajiste amuletos para que puedas ir a Kukulcán?";
		link.l1 = "Sí. Estoy listo para hacer el mismo viaje que hizo Nathaniel, el capitán encadenado.";
		link.l1.go = "SnakeEye_potion_1";
		break;

	case "SnakeEye_potion_1":
		RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Indian, 1);
		RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Amulet, 1);
		RemoveItems(pchar, pchar.questTemp.Saga.BaronReturn.Obereg, 1);
		TakeNItems(pchar, "Ultimate_potion", 3);
		Log_Info("Has entregado amuletos");
		Log_Info("Has recibido tres pociones versátiles");
		PlaySound("interface\important_item.wav");
		dialog.text = "Toma estas pociones. Recuerda que debes beber una inmediatamente después de que Kukulcán te escupa, o morirás o quedarás muy, muy enfermo. También recuerda no ir a la bodega donde los rostros pálidos guardan sus provisiones. Hay otra forma de abandonar el barco. De hecho, hay dos maneras. Encuentra a la mujer roja la primera noche, es muy importante. Eso es todo lo que puedo decirte.";
		link.l1 = "Recordaré eso, hermano piel roja.";
		link.l1.go = "SnakeEye_potion_2";
		break;

	case "SnakeEye_potion_2":
		dialog.text = "Entonces ve. Toca a Kukulcán a medianoche y te devorará. Llamaré a los espíritus para que te guíen.";
		link.l1 = "Gracias, Ojo de Serpiente. No te preocupes por mí, todo irá bien. ¡Nos volveremos a encontrar!";
		link.l1.go = "SnakeEye_potion_3";
		break;

	case "SnakeEye_potion_3":
		DialogExit();
		NextDiag.CurrentNode = "First time";
		pchar.questTemp.Saga.BaronReturn = "first_teleport";
		pchar.questTemp.Dolly = true;							 // телепорты работают!
		LAi_LocationDisableOfficersGen("Pearl_jungle_03", true); // не пускать офицеров в локу телепорта
		DeleteAttribute(npchar, "quest.amulet");
		AddQuestRecord("BaronReturn", "4");
		sld = characterFromId("Danielle");
		sld.quest.talk = "teleport";
		pchar.quest.BaronReturn_out1.win_condition.l1 = "ExitFromLocation";
		pchar.quest.BaronReturn_out1.win_condition.l1.location = pchar.location;
		pchar.quest.BaronReturn_out1.function = "Saga_DannyTalk";
		QuestPointerToLoc("Pearl_Jungle_02", "reload", "reload1_back");
		QuestPointerToLoc("Pearl_Jungle_03", "camera", "dolly");
		break;

	// пришёл из LSC
	case "LSC_hello":
		dialog.text = "Me alegra verte, mi amigo. ¿Cómo regresaste del cementerio de barcos?";
		link.l1 = "He encontrado la estatua de Kukulcán allí, tal como me dijiste. Chico Blanco me ha ayudado, Ole Christiansen. La estatua estaba hundida en el mar, pero pude alcanzarla. Me teletransportó a un pueblo indígena en Dominica.";
		link.l1.go = "LSC_hello_1";
		npchar.quest.LSC_hello = "true";
		break;

	case "LSC_hello_1":
		dialog.text = "¿Te encontró Monkitekuvri allí?";
		link.l1 = "Mm. ¿Monkitekuvri? ¿Quién es ese?";
		link.l1.go = "LSC_hello_2";
		break;

	case "LSC_hello_2":
		dialog.text = "Él es el jefe del pueblo.";
		link.l1 = "No pregunté por su nombre. Quizás era Monkitekuvri, quizás no.";
		link.l1.go = "LSC_hello_3";
		break;

	case "LSC_hello_3":
		dialog.text = "¿Tenía un pomposo tocado hecho de plumas de ave en su cabeza?";
		link.l1 = "Claro, que sí. Un montón de plumas... Parece que desplumó a todos los loros de la jungla.";
		link.l1.go = "LSC_hello_4";
		break;

	case "LSC_hello_4":
		dialog.text = "Él se llama Monkitekuvri. No son plumas de loro sino plumas de águila. Este tocado es mi tocado. Se lo regalé a Monkitekuvri cuando Kukulcán me escupió de vuelta. Luego me llevaron a otra estatua...";
		link.l1 = "¡Vaya cosa! ¡También me han 'sacrificado' a Kukulcán! Y me he encontrado aquí, cerca de la primera estatua.";
		link.l1.go = "LSC_hello_5";
		break;

	case "LSC_hello_5":
		dialog.text = "Sí, mi pálido amigo. Mi viaje también terminó aquí.";
		link.l1 = "Los ídolos se teletransportan en un círculo... Pero ¿cuál es el sentido de eso? ¿Tienes alguna idea, Ojo de Serpiente?";
		link.l1.go = "LSC_hello_6";
		break;

	case "LSC_hello_6":
		dialog.text = "Supongo que las estatuas no funcionan bien. En este momento, mueven a las personas de un lugar a otro, pero deberían llevarlas a un solo lugar. Algo en ellas está roto.";
		link.l1 = "¿Qué te hace pensar de esta manera?";
		link.l1.go = "LSC_hello_7";
		break;

	case "LSC_hello_7":
		dialog.text = "Porque la teletransportación en círculo no tiene sentido. Kukulcán debe llevar a todas las víctimas a un lugar y no moverlas por ahí.";
		link.l1 = "¿Y dónde podría ser ese lugar?";
		link.l1.go = "LSC_hello_8";
		break;

	case "LSC_hello_8":
		dialog.text = "Este es un gran secreto, hermano blanco, incluso para mí.";
		link.l1 = "Ya veo. Bien, al diablo con los ídolos. Nunca me volveré a acercar a ellos. He encontrado al capitán encadenado, ya no hay necesidad de viajar a través de los portales.";
		link.l1.go = "LSC_hello_9";
		AddQuestRecord("BaronReturn", "12");
		break;

	case "LSC_hello_9":
		dialog.text = "Cuando estuviste en el cementerio de barcos. ¿Encontraste allí mi pandereta?";
		if (CheckCharacterItem(pchar, "buben"))
		{
			link.l1 = "Creo que sí. Echa un vistazo.";
			link.l1.go = "LSC_buben";
		}
		else
		{
			link.l1 = "No. Desafortunadamente no lo he encontrado. Pero sé dónde está la isla y puedo llegar a ella. Buscaré tu pandero.";
			link.l1.go = "LSC_hello_10";
		}
		break;

	case "LSC_hello_10":
		dialog.text = "Busca eso, mi pálido amigo. Te lo pido mucho. Sin mi pandereta no escucho bien a los espíritus.";
		link.l1 = "Está bien, Ojo de Serpiente. ¡Nos vemos!";
		link.l1.go = "exit";
		break;

	case "LSC_buben":
		RemoveItems(pchar, "buben", 1);
		PlaySound("interface\important_item.wav");
		dialog.text = "Ese es mi pandero. Gracias, mi amigo pálido. Puedo recompensarte. Te presento esta arma, que tu gente no tendrá por mucho tiempo desde ahora. Esta arma es un arma de los rostros pálidos de mi tiempo.";
		link.l1 = "¡Interesante! Muéstramelo, amigo piel roja...";
		link.l1.go = "LSC_buben_1";
		break;

	case "LSC_buben_1":
		GiveItem2Character(pchar, "pistol7");
		Log_Info("Has recibido un revólver Colt");
		PlaySound("interface\important_item.wav");
		TakeNItems(pchar, "shotgun_cartridge", 3);
		TakeNItems(pchar, "GunCap_colt", 3);
		dialog.text = "Tómalo. Solo quedan tres cargas, el resto las usé yo. Pero quizás aprendas a hacer cargas para él. Perdí unas pocas docenas de piezas para las cargas en el cementerio de barcos, puedes encontrarlas allí.";
		link.l1 = "¡Oh! ¡Eso es una pistola! Nunca he visto algo así antes... ¿qué máquina tan extraña? Algún mecanismo giratorio... ¡cinco cargas! ¡Bonito!";
		link.l1.go = "LSC_buben_2";
		break;

	case "LSC_buben_2":
		dialog.text = "Se llama revólver Colt. No hay otra pistola como esta en tu tiempo. Fácil de usar, levanta el percutor y aprieta el gatillo. Dispara bien.";
		link.l1 = "¡Gracias! ¡Gracias, Ojo de Serpiente! Será una agradable sorpresa para mis enemigos... Lástima que solo haya tres cargas...";
		link.l1.go = "LSC_buben_3";
		break;

	case "LSC_buben_3":
		dialog.text = "Intenta enseñarte a hacer cargas para el revólver Colt. Entonces serás un gran guerrero de tu tiempo. Ah, mi pálido hermano, olvidé pedirte que encontraras mi pipa en el cementerio de barcos. Era una pipa muy bonita.";
		if (CheckCharacterItem(pchar, "smoking_tube"))
		{
			link.l1 = "¡Ja! ¿Y yo preguntándome de quién podría ser esta pipa pintada? Echa un vistazo.";
			link.l1.go = "LSC_tube";
		}
		else
		{
			link.l1 = "Está bien. También buscaré tu pipa. ¡Nos vemos!";
			link.l1.go = "exit";
		}
		npchar.quest.LSC_tube = "true";
		break;

	case "LSC_tube":
		RemoveItems(pchar, "smoking_tube", 1);
		PlaySound("interface\important_item.wav");
		dialog.text = "Esta es mi pipa, hermano. Me alegra que la hayas encontrado. Y puedo darte otro regalo por ello. Este es un libro ingenioso de los rostros pálidos de mi tiempo. No puedo entenderlo. Intenta encontrar a un hombre listo que pueda leer y entender este libro.";
		link.l1 = "Gracias, Ojo de Serpiente. Creo que conozco a alguien que estará interesado en esto.";
		link.l1.go = "LSC_tube_1";
		break;

	case "LSC_tube_1":
		GiveItem2Character(pchar, "chemistry");
		Log_Info("Has recibido un libro de química de Lavoisier");
		PlaySound("interface\important_item.wav");
		dialog.text = "Entrégaselo, hermano blanco. Este libro contiene grandes secretos de la sabiduría de los rostros pálidos.";
		link.l1 = "Bien. ¡Nos vemos, Ojo de Serpiente!";
		link.l1.go = "exit";
		break;

	// лечение Натаниэля
	case "Saga_nathaniel":
		dialog.text = "Te estoy escuchando, hermano cara pálida.";
		link.l1 = "He traído al capitán encadenado, a quien buscaba en el cementerio de barcos, conmigo. Está muy enfermo. Sé que solo tú puedes sanarlo...";
		link.l1.go = "Saga_nathaniel_1";
		break;

	case "Saga_nathaniel_1":
		dialog.text = "Kukulcán consumió su salud. Creo que puedo ayudarle a sanar. Pero tomará no menos de una luna llena. Kukulcán devoró al capitán hace mucho tiempo y la enfermedad se extendió profundamente dentro de él.";
		link.l1 = "¡Por favor, cúralo, chamán! ¡Te traeré lo que necesites!";
		link.l1.go = "Saga_nathaniel_2";
		break;

	case "Saga_nathaniel_2":
		dialog.text = "Lo intentaré, hermano blanco. No tienes que traerme nada. Tengo todo. El tiempo hace que la enfermedad sea más fuerte, pero el capitán encadenado estará sano de nuevo en una luna.";
		link.l1 = "Gracias, hermano pielroja. Eres de nuevo mi salvador.";
		link.l1.go = "Saga_nathaniel_3";
		break;

	case "Saga_nathaniel_3":
		dialog.text = "Deja al capitán encadenado en mi choza, hermano blanco, y camina sin preocupaciones. Lleva también a su esposa, nadie puede ver mis ritos.";
		link.l1 = "Está bien, Ojo de Serpiente. Me llevaré a Danielle conmigo. ¡Nos vemos!";
		link.l1.go = "Saga_nathaniel_4";
		break;

	case "Saga_nathaniel_4":
		DialogExit();
		pchar.questTemp.Saga.BaronReturn = "treatment";
		sld = characterFromId("Nathaniel");
		RemovePassenger(Pchar, sld);
		LAi_SetStayType(sld);
		sld.location = "none";
		pchar.quest.Saga_NatanTreatment1.win_condition.l1 = "ExitFromLocation";
		pchar.quest.Saga_NatanTreatment1.win_condition.l1.location = pchar.location;
		pchar.quest.Saga_NatanTreatment1.function = "Saga_NatanTreatment";
		break;

	case "calendar":
		dialog.text = "Escucho, amigo mío.";
		link.l1 = "¿Recuerdas nuestra charla sobre las estatuas de Kukulcán? Dijiste 'deberían mover a la gente a un lugar especial'.";
		link.l1.go = "calendar_1";
		break;

	case "calendar_1":
		dialog.text = "Recuerdo, capitán blanco.";
		link.l1 = "Yo sé dónde esas estatuas debieron haber movido a las personas que fueron devoradas por Kukulcán.";
		link.l1.go = "calendar_2";
		break;

	case "calendar_2":
		dialog.text = "¿Dónde?";
		link.l1 = "A la antigua ciudad maya de Tayasal. Está situada en lo profundo de la jungla del continente.";
		link.l1.go = "calendar_3";
		break;

	case "calendar_3":
		dialog.text = "Muy interesante. ¿Cómo sabes esto?";
		link.l1 = "Es una larga historia, Ojo de Serpiente. También entiendo cómo llegaste aquí. Ni siquiera has nacido todavía, ¿verdad?";
		link.l1.go = "calendar_4";
		break;

	case "calendar_4":
		dialog.text = "Incluso mi padre no nació en tu tiempo. Pero yo vivo en tu tiempo y ese es un gran misterio.";
		link.l1 = "En realidad es explicable. Un sacerdote Itza llamado Kanek, que vive en Tayasal, invocó a Kukulcán para nacer como mortal en este mundo y absorber la sabiduría de la raza blanca. También creó un agujero temporal que teletransportó a algunos hombres del futuro a nuestro tiempo...";
		link.l1.go = "calendar_5";
		break;

	case "calendar_5":
		dialog.text = "¿Dejar que Kukulcán absorba la sabiduría de la gente del futuro?";
		link.l1 = "Sí. Y Kukulcán planea ir al pasado para entregar el conocimiento al pueblo maya que murió hace mucho tiempo. La historia cambiará y los mayas gobernarán América y tal vez incluso más...";
		link.l1.go = "calendar_6";
		break;

	case "calendar_6":
		dialog.text = "";
		link.l1 = "Pero algo ha sucedido con los portales y han comenzado a teletransportar a la gente en círculo en lugar de Tayasal. Y por eso estoy aquí, necesito tu consejo, Ojo de Serpiente.";
		link.l1.go = "calendar_7";
		break;

	case "calendar_7":
		dialog.text = "¿Por qué yo, capitán blanco?";
		link.l1 = "Porque has sido devorado por Kukulcán. Y porque la estatua de Kukulcán cerca de tu aldea tiene una marca extraña en este mapa, que está fuertemente conectada con los ritos de Kanek.";
		link.l1.go = "calendar_8";
		break;

	case "calendar_8":
		dialog.text = "¿Me muestras este mapa?";
		link.l1 = "Aquí, echa un vistazo...";
		link.l1.go = "calendar_9";
		break;

	case "calendar_9":
		RemoveItems(pchar, "skinmap", 1);
		dialog.text = "(mirando) ¿Este signo redondo, sí? ¿Y qué significa?";
		link.l1 = "No sé, chamán. Sé que solo una de las tres estatuas de Kukulcán tiene esta marca. Y que la estatua con la marca es la tuya. Concluyo que tu estatua es especial. ¿Tienes alguna idea?";
		link.l1.go = "calendar_10";
		break;

	case "calendar_10":
		dialog.text = "Dame tiempo hasta mañana por la mañana, hermano blanco. Déjame este mapa de cuero. Necesito preguntar a los espíritus. Vuelve mañana.";
		link.l1 = "Está bien, hermano piel roja. Estaré aquí mañana. Gracias por ayudarme.";
		link.l1.go = "calendar_11";
		break;

	case "calendar_11":
		DialogExit();
		SetFunctionTimerCondition("Tieyasal_CalendarThink", 0, 0, 1, false);
		pchar.questTemp.Tieyasal = "calendar_think";
		NextDiag.CurrentNode = "calendar_wait";
		break;

	case "calendar_wait":
		dialog.text = "Vuelve más tarde, hermano blanco. No me molestes ahora.";
		link.l1 = "Claro, chamán...";
		link.l1.go = "exit";
		NextDiag.TempNode = "calendar_wait";
		break;

	case "calendar_12":
		dialog.text = "Tengo algo que decirte, hermano blanco.";
		link.l1 = "¿Encontraste algo? ¿O tienes alguna suposición?";
		link.l1.go = "calendar_13";
		break;

	case "calendar_13":
		dialog.text = "Los espíritus ancestrales me dieron una visión y fui a Kukulcán con el mapa. Busqué y encontré. Debe ser lo que buscas, hermano blanco.";
		link.l1 = "¿Qué encontraste?";
		link.l1.go = "calendar_14";
		break;

	case "calendar_14":
		dialog.text = "La estatua de Kukulcán tiene dos abrazaderas de hierro y un hueco. El hueco tiene forma redonda y lisa. Se orienta hacia el objeto redondo y plano de tu mapa de cuero.";
		link.l1 = "¿Qué es?";
		link.l1.go = "calendar_15";
		break;

	case "calendar_15":
		dialog.text = "No lo sé. Solo sé que es redondo, plano, del tamaño de una calabaza pequeña y tal vez del grosor de un dedo. Puedes ir y mirar la cavidad y las abrazaderas por ti mismo. La abrazadera necesita sostenerlo.";
		link.l1 = "¿Tienes alguna idea? ¿O una suposición de lo que podría ser?";
		link.l1.go = "calendar_16";
		break;

	case "calendar_16":
		dialog.text = "La piedra tiene un rastro de fuego. Sé lo que le pasó. Una llama del cielo la golpeó.";
		link.l1 = "¿Un rayo? ¿Le cayó un rayo?";
		link.l1.go = "calendar_17";
		break;

	case "calendar_17":
		dialog.text = "Estoy seguro de eso. Le pregunté a Miskito sobre este ídolo. Un guerrero dijo que hace mucho tiempo se veían algunas cosas bonitas pintadas en la estatua. Muy similares a las piedras. Me dijo que eran unas piedras rojas muy bonitas. Un hombre blanco del pueblo las compró.";
		link.l1 = "Hum. Por lo que entiendo, parece que un rayo golpeó este 'algo' redondo, lo rompió en pedazos y luego esos pedazos fueron vendidos a algún tipo blanco.";
		link.l1.go = "calendar_18";
		break;

	case "calendar_18":
		dialog.text = "Parece que sí.";
		link.l1 = "¿Y quién era ese hombre blanco? ¿Te lo dijo tu guerrero?";
		link.l1.go = "calendar_19";
		break;

	case "calendar_19":
		dialog.text = "Me lo dijo. Era gran amigo de Miskito y vive en el pueblo de Blueweld. Su nombre es Forest Devil. Lo conozco, tú también debes conocerlo.";
		link.l1 = "¿Jan Svenson? Espera un segundo... ¿dijiste rocas pintadas de rojo? Parece que he tenido mucha suerte. Mira aquí, chamán, ¡mira estas rocas rojas que tengo! Forest Devil me las regaló.";
		link.l1.go = "calendar_20";
		break;

	case "calendar_20":
		Log_Info("Has entregado fragmentos con motivos ornamentales");
		RemoveItems(pchar, "splinter_js", 1);
		RemoveItems(pchar, "splinter_nh", 1);
		RemoveItems(pchar, "splinter_mt", 1);
		RemoveItems(pchar, "splinter_zm", 1);
		RemoveItems(pchar, "splinter_jb", 1);
		dialog.text = "Debe ser ellos. Cinco rocas. Echa un vistazo, hermano blanco. Si las colocas así... (juntándolas)";
		link.l1 = "...";
		link.l1.go = "calendar_21";
		break;

	case "calendar_21":
		dialog.text = "... entonces tenemos un objeto redondo. ¡Mira! Coinciden. Antes era un solo objeto.";
		link.l1 = "¡Maldita sea! Y estas cosas han estado en mi bolsillo tanto tiempo... Escucha, chamán, si pongo los fragmentos en la cavidad...";
		link.l1.go = "calendar_22";
		break;

	case "calendar_22":
		dialog.text = "Kukulcán escupirá a la víctima en la antigua ciudad india como dijiste.";
		link.l1 = "¡Eso sería genial! ¡Necesito llegar allí! ¿Crees que el adorno funcionará, si ha sido roto en pedazos?";
		link.l1.go = "calendar_23";
		break;

	case "calendar_23":
		dialog.text = "Creo que necesitamos reunirlos y luego colocar el adorno en el hueco.";
		link.l1 = "¿Reunirlos? Pero ¿cómo podemos juntarlos de nuevo?";
		link.l1.go = "calendar_24";
		break;

	case "calendar_24":
		dialog.text = "Déjamelo a mí y a los espíritus de los ancestros, hermano blanco. No son simples rocas. Es un objeto milagroso. Vuelve en tres noches, hermano blanco. Llamaré a los espíritus, la sabiduría y la destreza de los vivos, y trataré de unir los fragmentos.";
		link.l1 = "Increíble... ¿Cómo puedo pagarte alguna vez, Ojo de Serpiente?";
		link.l1.go = "calendar_25";
		break;

	case "calendar_25":
		dialog.text = "Agradécemelo después, hermano blanco. Vete ahora. Vuelve en tres noches.";
		link.l1 = "Bien. Espero que tengas éxito...";
		link.l1.go = "calendar_26";
		break;

	case "calendar_26":
		DialogExit();
		SetFunctionTimerCondition("Tieyasal_CalendarDone", 0, 0, 3, false);
		NextDiag.CurrentNode = "calendar_wait";
		break;

	case "calendar_28":
		dialog.text = "Puedo hacerte feliz, hermano blanco.";
		link.l1 = "¿Pudiste unir los fragmentos?";
		link.l1.go = "calendar_29";
		break;

	case "calendar_29":
		dialog.text = "Sí. No fue fácil y hay cicatrices en el calendario, pero ahora está completo.";
		link.l1 = "¿Calendario? ¿Por qué lo llamaste así?";
		link.l1.go = "calendar_30";
		break;

	case "calendar_30":
		dialog.text = "Porque esta cosa redonda es un calendario. Lo estudié cuidadosamente. Hay un conteo del tiempo en él. Los indios de la ciudad antigua cuentan noches, lunas, años y eras.";
		link.l1 = "Increíble... Aunque, pensando en lo que los sacerdotes mayas son capaces de hacer, la creación de este calendario no parece ser nada especial.";
		link.l1.go = "calendar_31";
		break;

	case "calendar_31":
		GiveItem2Character(pchar, "calendar_maya");
		sld = ItemsFromID("calendar_maya");
		sld.shown = "0";
		Log_Info("Has recibido un calendario Maya");
		dialog.text = "Tómalo, capitán blanco. Ponlo en el hueco de la estatua. Entonces quizás te escupa en la ciudad india.";
		link.l1 = "¿Cómo puedo pagarte, Ojo de Serpiente?";
		link.l1.go = "calendar_32";
		break;

	case "calendar_32":
		dialog.text = "Di 'Gracias'. Los dioses te guían en tu camino, aunque no lo veas. Los blancos dicen, destino. Kukulcán te llamó, los dioses te guían. Ahora ve. Haz tu trabajo y deja que los buenos espíritus te guíen.";
		link.l1 = "¡Gracias, Ojo de Serpiente! Nunca te olvidaré.";
		link.l1.go = "calendar_33";
		break;

	case "calendar_33":
		TakeNItems(pchar, "Ultimate_potion", 4);
		Log_Info("Has recibido cuatro pociones versátiles");
		PlaySound("interface\important_item.wav");
		dialog.text = "Espera. Casi olvidamos lo más importante. Kukulcán devora al hombre y consume su vida. He preparado pociones para ti. Pociones comanches. Te las doy. He hecho cuatro frascos, así puedes llevar contigo a tres compañeros leales y valientes.";
		link.l1 = "Has hecho tanto por mí, hermano piel roja...";
		link.l1.go = "calendar_34";
		break;

	case "calendar_34":
		dialog.text = "Hermano no es solo una palabra para los indios de la tribu Comanche. Cuando regreses de la ciudad de Kukulcán, visita nuestro pueblo. Cocinaremos mucho, mucho saraiaka. Estaré encantado de verte.";
		link.l1 = "¡Claro, hermano piel roja! ¡Sin duda te visitaré!";
		link.l1.go = "calendar_35";
		break;

	case "calendar_35":
		DialogExit();
		pchar.questTemp.Tieyasal = "calendar_place";
		NextDiag.CurrentNode = "First time";
		AddQuestRecord("Tieyasal", "17");
		sld = ItemsFromID("skinmap");
		sld.price = 100; // кожаную карту можно выкладывать 270912
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
