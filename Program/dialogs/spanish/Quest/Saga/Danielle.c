// Даниэль Хоук - жена Натаниэля Хоука
void ProcessDialogEvent()
{
	ref NPChar, sld, rItm, rItem;
	aref Link, NextDiag, rType;
	int i;
	bool bOk1, bOk2;
	string sTemp, sAttr, sGun, sBullet, attrL;

	DeleteAttribute(&Dialog, "Links");

	makeref(NPChar, CharacterRef);
	makearef(Link, Dialog.Links);
	makearef(NextDiag, NPChar.Dialog);

	sAttr = Dialog.CurrentNode;
	if (findsubstr(sAttr, "SetGunBullets1_", 0) != -1)
	{
		i = findsubstr(sAttr, "_", 0);
		NPChar.SetGunBullets = strcut(sAttr, i + 1, strlen(sAttr) - 1); // индекс в конце
		Dialog.CurrentNode = "SetGunBullets2";
	}

	switch (Dialog.CurrentNode)
	{
	case "First time": // первая встреча - знакомство
		PlaySound("Voice\Spanish\saga\Denny Hawk-08.wav");
		dialog.text = "¡Espera, guapo! Creo que deberíamos hablar. ¡No perdamos tiempo, capitán!";
		link.l1 = "¿Te conozco? De todos modos, siempre tengo unas cuantas horas extra para una dama.";
		link.l1.go = "meeting";
		NextDiag.TempNode = "First time";
		break;

	case "meeting":
		PlaySound("Voice\Spanish\saga\Denny Hawk-01.wav");
		dialog.text = "No se excite, capitán. Vaya a intentarlo con otra muchacha tonta, y más joven. Tengo un asunto para ti. En realidad, estoy casada. El nombre de mi marido es Nathaniel Hawk.";
		link.l1 = "¡Vaya! Entonces debes ser ese... eh, Dannie Hawk, el señor Svenson te mencionó.";
		link.l1.go = "meeting_1";
		break;

	case "meeting_1":
		dialog.text = "En carne y hueso. Sí, sé que Forest Devil no piensa mucho de mí, el sentimiento es mutuo, pero tuvo que advertirte que llevo mi sable no solo porque es bonito. Así que, ¡ve al grano, hijo!\nHe estado siguiendo a Svenson y sus visitantes por un tiempo porque él fue quien envió a mi esposo a la jungla a morir. Pensé que estaba trabajando con Jackman, pero ahora veo que no es así. Estaba escondida bajo la ventana durante tu conversación. No pude escuchar todo, pero aprendí mucha información útil.\n¿Realmente estás dispuesto a encontrar a mi esposo y patear el trasero de Jackman? ¿O solo estabas hablando por hablar?";
		link.l1 = "Escuchar a escondidas es malo, Madame Hawk. Pero te perdonaré si me hablas de una manera más respetuosa. Buscar a Hawk o no, eso es solo mi preocupación. Habla si tienes algo útil que decir o déjame en paz si no. No lo pediré dos veces.";
		link.l1.go = "meeting_2";
		break;

	case "meeting_2":
		dialog.text = "¡Ajá, qué cabeza caliente! Vamos, Capitán... Mi temperamento no te hace sentir cómodo, eso es seguro. Veo que no eres un cobarde y sabes lo que vales. Así que... familiaricémonos. Te prometo que tendré cuidado con lo que te digo. Te necesito y tú me necesitas. Compartimos objetivos. Llévame con tu tripulación y no te arrepentirás. Te serviré con buena fe y fidelidad hasta que encontremos a Nathan, tienes mi palabra.";
		link.l1 = "Considérate aceptada... Dannie. Svenson me dijo que ya has estado buscando a tu esposo. ¿Has encontrado algo de interés?";
		link.l1.go = "meeting_3";
		break;

	case "meeting_3":
		dialog.text = "No mucho, pero lo suficiente para acusar a Jackman de mentir. El bastardo dijo que los guardias de la mina, esos a los que se enfrentó mi Nathan, no tomaban prisioneros. Y aunque es cierto que nadie ha visto el cadáver de mi esposo en la bahía, ¿cómo podrían, si en realidad fue llevado a las minas como prisionero? Ojo de Serpiente, un chamán del pueblo Miskito, lo encontró allí.\nTambién organizó su escape. Pero dónde está mi esposo ahora, eso sigue siendo desconocido. El chamán estaba murmurando algo sobre un tal Kukulcán que se lo comió, pero no entendí nada. Además, el piel roja dejó bastante claro que las mujeres blancas no son más que una broma para él. Deberías hablar con él, tal vez sea más conversador contigo.";
		link.l1 = "¡Eso es algo al menos! Tales noticias me alegran. ¿Dónde puedo encontrar a este indio?";
		link.l1.go = "meeting_4";
		break;

	case "meeting_4":
		dialog.text = "Hay un pueblo en lo profundo de la jungla. Necesitamos desembarcar en la Bahía de Amatique y dirigirnos al oeste a través de la jungla. Te mostraré el camino si no lo encuentras tú mismo. Se puede encontrar un ídolo de piedra no muy lejos del pueblo y los salvajes lo veneran como su dios. He estado allí varias veces. Realmente nada especial. Solo una simple piedra cubierta de musgo.";
		link.l1 = "Interesante. Está bien, vamos. Hablaremos con el chamán y veremos qué hacer después. ¿Listo?";
		link.l1.go = "meeting_5";
		break;

	case "meeting_5":
		dialog.text = "¡Por supuesto! Claro, estoy listo. He estado viajando todo el tiempo desde que dejé Maroon Town. Además, no quiero ser solo otro de tus pasajeros.";
		link.l1 = "Está bien. Vamos a mi barco.";
		link.l1.go = "meeting_6";
		break;

	case "meeting_6":
		dialog.text = "¡Aye-aye, Capitán!";
		link.l1 = "...";
		link.l1.go = "meeting_7";
		break;

	case "meeting_7":
		DialogExit();
		chrDisableReloadToLocation = false; // открыть локацию
		npchar.quest.OfficerPrice = sti(pchar.rank) * 700;
		npchar.OfficerWantToGo.DontGo = true; // не пытаться уйти
		npchar.CompanionDisable = true;		  // нельзя в компаньоны - чтобы не утонула
		LAi_SetImmortal(npchar, false);
		npchar.HalfImmortal = true; // чтобы не убили в сухопутном бою
		npchar.loyality = MAX_LOYALITY;
		AddPassenger(pchar, npchar, false);
		SetCharacterRemovable(npchar, true);
		npchar.Payment = true;
		npchar.DontClearDead = true;
		NextDiag.CurrentNode = "Danielle_officer";
		npchar.HoldEquip = true; // лесник -  не отдавать саблю и пистоль
		SaveCurrentNpcQuestDateParam(npchar, "HiredDate");
		LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		AddQuestRecord("BaronReturn", "2");
		Saga_CreateSnakeEye();
		// выбираем амулеты
		pchar.questTemp.Saga.BaronReturn.Indian = "indian_" + (rand(10) + 1);
		pchar.questTemp.Saga.BaronReturn.Amulet = "amulet_" + (rand(10) + 1);
		pchar.questTemp.Saga.BaronReturn.Obereg = "obereg_" + (rand(10) + 1);
		// на локацию с истуканом
		npchar.quest.talk = "dolly";
		pchar.quest.Saga_Dolly.win_condition.l1 = "location";
		pchar.quest.Saga_Dolly.win_condition.l1.location = "Pearl_jungle_03";
		pchar.quest.Saga_Dolly.function = "Saga_DannyTalk";
		AddCharacterExpToSkill(pchar, "Fortune", 50); // везение
		AddCharacterExpToSkill(pchar, "Leadership", 50);
		npchar.greeting = "danny_1";
		break;

	// у истукана в джунглях
	case "Dolly":
		dialog.text = "" + pchar.name + "¡Vamos! Te mostraré el ídolo de piedra del que hablaba el chamán indio. Solo un pilar de piedra común. ¡Vamos!";
		link.l1 = "...";
		link.l1.go = "Dolly_1";
		break;

	case "Dolly_1":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocator(npchar, "item", "torch1", "Saga_ShowDolly", -1);
		break;

	case "Dolly_2":
		dialog.text = "¡Oye! Mira, es solo una estatua de piedra. Nada especial...";
		link.l1 = "Ya veo... Aunque la figura en la cima es un poco siniestra, ¿no crees? ";
		link.l1.go = "Dolly_3";
		break;

	case "Dolly_3":
		dialog.text = "Todas las estatuas indias son aterradoras y tienen un aspecto malvado. He visto algo similar antes. Todas son iguales. De todos modos, vamos, el pueblo está cerca.";
		link.l1 = "¡Vamos!";
		link.l1.go = "Dolly_4";
		break;

	case "Dolly_4":
		chrDisableReloadToLocation = false; // открыть локацию
		DialogExit();
		LAi_SetOfficerType(npchar);
		LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		npchar.dialog.currentnode = "Danielle_officer";
		break;

	// у мискито
	case "SnakeEye":
		dialog.text = "Entonces, ¿qué dices, " + pchar.name + "¿Qué te dijo ese ventrílocuo piel roja? ¿Conseguiste algo de sus palabras filosóficas?";
		link.l1 = "¿Estabas escuchando a escondidas otra vez, Dannie?";
		link.l1.go = "SnakeEye_1";
		break;

	case "SnakeEye_1":
		dialog.text = "Bueno... un poco. Sabes, nosotras las mujeres somos así. Pero debes entender - solo me preocupo por mi esposo. En realidad, lo amo. ¿Y qué si estoy espiando? De todos modos, ¿conseguiste algo útil?";
		link.l1 = "Estoy tratando de pensar... no fue fácil entender a Ojo de Serpiente. Sin embargo, parece que el ídolo que vimos en nuestro camino hacia el pueblo es una especie de portal mágico que puede teletransportar a la gente.";
		link.l1.go = "SnakeEye_2";
		break;

	case "SnakeEye_2":
		dialog.text = "";
		link.l1 = "No me mires así. No es idea mía y hasta ahora no tengo problemas con la cabeza. Me preguntaste qué me dijo el chamán, así que te lo estoy contando.";
		link.l1.go = "SnakeEye_3";
		break;

	case "SnakeEye_3":
		dialog.text = "Por favor, discúlpame. No te miraré así nunca más. Sigue.";
		link.l1 = "Dijo que cuando Nathan casi fue atrapado por sus perseguidores, el indígena le mostró la estatua como una forma de rescate, llamándola Kukulcán y diciendo que devoró a Nathan vivo y lo escupió en otro lugar. En pocas palabras, parece que Nathan fue teletransportado por la estatua.";
		link.l1.go = "SnakeEye_4";
		break;

	case "SnakeEye_4":
		dialog.text = "¡Dios, qué demonios... Nathan y yo ya hemos estado en un lío similar antes y ahora vuelve a suceder. Ya tuvimos suficientes aventuras con ese templo indio lleno de magia maya...";
		link.l1 = "¿Qué acabas de decir?";
		link.l1.go = "SnakeEye_5";
		break;

	case "SnakeEye_5":
		dialog.text = "Ah, no es nada, " + pchar.name + ", no importa. Solo recuerdos de mi ardiente juventud. Pero ¿cómo pudo hacer eso Nathan? Quiero decir, ¿teletransportarse? Acabamos de estar cerca de ese ídolo, estaba caminando alrededor y tocándolo... ¡es solo una piedra!";
		link.l1 = "La Serpiente de Ojo me dijo que el ídolo cobra vida a medianoche. Sólo entonces comienza a brillar en color dorado, cuando el espíritu de Kukulcán entra en él. Es el momento en que no debes tocarlo. O, por el contrario, deberías...";
		link.l1.go = "SnakeEye_6";
		break;

	case "SnakeEye_6":
		dialog.text = "Espeluznante... ¿Y ahora qué? ¿Esperamos hasta la medianoche y luego vamos a la jungla?";
		link.l1 = "No. El chamán dijo que el ídolo no solo teletransporta a las personas, sino que también devora sus vidas. Por lo que le entendí, quiso decir que drena su salud. Ojo de Serpiente ha pasado por estas estatuas tres veces y se ha curado con alguna poción única después de cada teletransportación.";
		link.l1.go = "SnakeEye_7";
		break;

	case "SnakeEye_7":
		dialog.text = "¿Le has pedido esta poción?";
		link.l1 = "Claro. Pero primero, solo quedan tres frascos y, en segundo lugar, él exigió tres amuletos a cambio de ellos.";
		link.l1.go = "SnakeEye_8";
		break;

	case "SnakeEye_8":
		dialog.text = "¿Qué tal si hacemos esto sin la poción? Vamos a la estatua por la noche y la tocamos...";
		link.l1 = "Demasiado arriesgado. Concedo que el indio está un poco fuera de sí y nos está engañando, pero no parece un psicópata, así que creo que está diciendo la verdad. Recuerdo que me mencionaste algo sobre la magia india... ¿Dudas de su existencia?";
		link.l1.go = "SnakeEye_9";
		break;

	case "SnakeEye_9":
		dialog.text = "Sí, lo estaba. No lo dudo porque lo vi con mis propios ojos. Así que, supongo que tienes razón, no tiene sentido arriesgarlo.";
		link.l1 = "Exactamente. Por eso encontraremos primero los amuletos, luego conseguiremos esa maravillosa poción del chamán y iremos a la estatua. Iré yo. Solo.";
		link.l1.go = "SnakeEye_10";
		break;

	case "SnakeEye_10":
		dialog.text = "¿Por qué es eso? ¿Y qué hay de mí?";
		link.l1 = "Te quedarás en mi barco y estarás a cargo mientras yo esté ausente. Ni siquiera intentes discutir, Dannie. Solo hay tres frascos de la poción. No se sabe a dónde lleva el portal en caso de que el chamán tenga razón y esta cosa funcione de verdad. Quizás, ni siquiera sea capaz de encontrar a Nathan allí.";
		link.l1.go = "SnakeEye_11";
		break;

	case "SnakeEye_11":
		dialog.text = "Eres igual que Nathan. Todos los hombres son iguales... Está bien, estoy de acuerdo.";
		link.l1 = "Es bueno que nos entendamos. Vamos ahora, necesitamos encontrar los amuletos.";
		link.l1.go = "Dolly_4";

		if (CheckAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets"))
		{
			DeleteAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets");
			if (CheckAttribute(pchar, "questTemp.Saga.HelenRelation") && sti(pchar.questTemp.Saga.HelenRelation) > 6)
			{
				AddDialogExitQuestFunction("HelenDrinking_GivePotionsDlg");
			}
		}
		break;

	// перед походом к истукану
	case "teleport":
		dialog.text = "¿Y qué? ¿Conseguiste las pociones?";
		link.l1 = "Sí. Tengo las pociones y algunas instrucciones. Lo único que queda por hacer es ir al ídolo a medianoche y tocarlo.";
		link.l1.go = "teleport_1";
		break;

	case "teleport_1":
		dialog.text = "¿Tienes miedo?";
		link.l1 = "Sí. Me temo que el chamán podría resultar simplemente estar loco y no habrá teletransportación.";
		link.l1.go = "teleport_2";
		break;

	case "teleport_2":
		dialog.text = "Vaya, vaya... ¿No tienes realmente miedo? ¿Ni un poquito?";
		link.l1 = "Dannie, no me presiones... Si realmente quieres saber, entonces sí, no me siento demasiado seguro, debo confesar.";
		link.l1.go = "teleport_3";
		break;

	case "teleport_3":
		dialog.text = "Iré contigo.";
		link.l1 = "¿Vas a empezar a discutir otra vez? Pensé que teníamos un trato...";
		link.l1.go = "teleport_4";
		break;

	case "teleport_4":
		dialog.text = "Me has entendido mal. Sólo me quedaré cerca de ti. Tendré que asegurarme de que la estatua funcione... o que no lo haga.";
		link.l1 = "No tengo objeciones. Pero ni se te ocurra seguirme en caso de que la estatua me 'devore'. ¿Me oyes?";
		link.l1.go = "teleport_5";
		break;

	case "teleport_5":
		dialog.text = "Hago. Prometo que no te seguiré... Capitán.";
		link.l1 = "Bien. Y, Dannie, parece que no eres tan perra como dicen.";
		link.l1.go = "teleport_6";
		break;

	case "teleport_6":
		dialog.text = "No me conoces muy bien, " + pchar.name + " Pero no hablemos de eso ahora.";
		link.l1 = "No vayamos... Bueno, ¡debemos prepararnos para nuestra travesía nocturna!";
		link.l1.go = "Dolly_4";
		npchar.quest.talk = "shadowstar";
		pchar.quest.Saga_Dolly1.win_condition.l1 = "location";
		pchar.quest.Saga_Dolly1.win_condition.l1.location = "Pearl_jungle_03";
		pchar.quest.Saga_Dolly1.win_condition.l2 = "Hour";
		pchar.quest.Saga_Dolly1.win_condition.l2.start.hour = 0.00;
		pchar.quest.Saga_Dolly1.win_condition.l2.finish.hour = 1.00;
		pchar.quest.Saga_Dolly1.function = "Saga_DannyTalk";

		if (CheckAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets"))
		{
			DeleteAttribute(pchar, "questTemp.HelenDrinking.GiveAmulets");
			if (CheckAttribute(pchar, "questTemp.Saga.HelenRelation") && sti(pchar.questTemp.Saga.HelenRelation) > 6)
			{
				AddDialogExitQuestFunction("HelenDrinking_GivePotionsDlg");
			}
		}
		break;

	// перед телепортацией
	case "shadowstar":
		dialog.text = "Mira, " + pchar.name + "¡Juro por todo lo sagrado, hay una luz extraña sobre la estatua!";
		link.l1 = "Parece que el chamán no mentía. Y, si la oscuridad no me engaña, la cima de la estatua ya no parece tan pétrea. ";
		link.l1.go = "shadowstar_1";
		QuestPointerDelLoc("Pearl_Jungle_02", "reload", "reload1_back");
		QuestPointerDelLoc("Pearl_Jungle_03", "camera", "dolly");
		break;

	case "shadowstar_1":
		dialog.text = "Exactamente... ¡Parece que está hecho de oro puro! ¡Increíble!";
		link.l1 = "Ha llegado el momento, Dannie. Deséame suerte y cruza los dedos por mí. ¡No te acerques al ídolo! Quédate aquí.";
		link.l1.go = "shadowstar_2";
		break;

	case "shadowstar_2":
		dialog.text = "Buena suerte, " + pchar.name + ". Esperemos que esto funcione... ¿Has preparado la poción del chamán?";
		link.l1 = "Sí, lo tengo aquí. Todo estará bien, Dannie. Bueno, ¡allá voy! (Presiona T para activar el ídolo)";
		link.l1.go = "shadowstar_3";
		break;

	case "shadowstar_3":
		DialogExit();
		LAi_group_MoveCharacter(npchar, LAI_GROUP_PLAYER);
		DoQuestReloadToLocation(pchar.location, pchar.location.group, pchar.location.locator, "");
		break;

	// прибыл назад
	case "arrive":
		dialog.text = "¿¿A-a-ah?! ¡Maldita sea! ¿¡Qué clase de monstruo eres, maldición?! ¡Al diablo contigo! ¡He visto peores criaturas en mi vida, incluyendo al mismísimo Van der Decken! ¡Ahora te daré lo que estás pidiendo!";
		link.l1 = "(débilmente) ¡Dannie, espera! ¡Detente! ¡Ahora!";
		link.l1.go = "arrive_1";
		// belamour legendary edition -->
		link.l2 = "(débilmente) ¿Van der Decken? ¡Ja-ja-ja! ¡Ese gusano ya me sirve! ¡Ahora es tu turno! ¡Inclínate ante mí, fiel servidor! ¡Liderarás mi ejército de los muertos!";
		link.l2.go = "arrive_1a";
		SetMusic("music_jungle");
		if (CheckCharacterItem(pchar, "Ultimate_potion"))
		{
			pchar.systeminfo.NoNotifications = true;
			RemoveItems(pchar, "Ultimate_potion", 1);
			DeleteAttribute(pchar, "systeminfo.NoNotifications");
			notification("Has utilizado una poción comanche", "None");
			LAi_SetCurHPMax(PChar);
			AddCharacterHealth(pchar, 50);
			DeleteAttribute(pchar, "chr_ai.poison");
			notification("¡Sientes que recuperas la salud!", "None");
			// Log_Info("A Comanche potion is used");
			// Log_Info("You are feeling that your health is restored!");
			// PlaySound("Ambient\Tavern\glotok_001.wav");
			PlaySound("Ambient\Horror\Fear_breath_01.wav");
		}
		break;

	case "arrive_1a":
		AddCharacterExpToSkill(pchar, "Leadership", 100);
		AddCharacterExpToSkill(pchar, "Sneak", 100);
		dialog.text = "¡A-A-A-A-A-A-A-A-A-A-A-A-A! ¡Aléjate! ¡Esto no puede estar pasando ahora mismo!";
		link.l1 = "(débilmente) ¡Dannie, espera! ¡Detente! ¡Ahora!";
		link.l1.go = "arrive_1";
		break;
	// <-- legendary edition
	case "arrive_1":
		dialog.text = "¿Ah?! ¿Qué dijiste?! ¿Dannie?";
		link.l1 = "(débilmente) ¡Detente inmediatamente! ¡Sujeta tu sable! ¡Déjame quitarme esta cosa!";
		link.l1.go = "arrive_2";
		break;

	case "arrive_2":
		dialog.text = "Maldita sea, ¡suenas como un monstruo... " + pchar.name + "!";
		link.l1 = "(débilmente) ¡Oh-oh... No me digas!";
		link.l1.go = "arrive_3";
		break;

	case "arrive_3":
		DialogExit();
		RemoveCharacterEquip(pchar, CIRASS_ITEM_TYPE);
		DoQuestCheckDelay("Pearl_TeleportArrive_1", 1.5);
		break;

	case "arrive_4":
		dialog.text = "¡Por todos los demonios, casi me matas del susto! ¡Estuve a punto de cortarte con mi sable!";
		link.l1 = "Vi eso... ¿y por qué estás tan fogoso, eh?";
		link.l1.go = "arrive_5";
		break;

	case "arrive_5":
		dialog.text = "Ese es quien soy... Oh, mi corazón aún late con fuerza fuera de mi pecho...";
		link.l1 = "Dannie, ¿dónde estamos ahora? No lejos del pueblo Miskito, ¿verdad?";
		link.l1.go = "arrive_6";
		break;

	case "arrive_6":
		dialog.text = "¡Dónde más podríamos estar! Esta es la estatua que te hizo desaparecer. ¡Eso fue espectacular! Lo recordaré por el resto de mi vida.";
		link.l1 = "Veo, ¿me has estado esperando aquí desde entonces?";
		link.l1.go = "arrive_7";
		break;

	case "arrive_7":
		dialog.text = "Dime, ¿qué más se suponía que debía hacer? Después de que la estatua te devorara, solo podía esperar que un día te escupiera de nuevo. Además, Ojo de Serpiente dijo que esto era lo más probable que sucediera. Viví con los Miskitos y observaba el ídolo cada día. ¿Por qué estamos hablando de tales tonterías? ¡Dime! ¿Qué pasó allá afuera? ¿Dónde has estado?";
		link.l1 = "Dannie, esta historia es demasiado larga, he visto tanto... Pero para desahogarme, te diré que ¡he encontrado a Nathaniel!";
		link.l1.go = "arrive_8";
		break;

	case "arrive_8":
		dialog.text = "¿Has encontrado a Nathan? ¿Dónde está? ¿Y cómo está?!";
		link.l1 = "No mentiré - está vivo, pero se siente realmente mal. No tuvo la poción del Comanche y el ídolo le ha drenado toda su salud. Está tumbado en una cabina de algún viejo y destartalado navío en la extraña Isla de los Barcos Abandonados. ¡Yo también fui teletransportado allí, así que Ojo de Serpiente tenía razón!";
		link.l1.go = "arrive_9";
		break;

	case "arrive_9":
		dialog.text = "Pobre Nathan... ¿Dónde está esa maldita isla? ¿Cómo llegamos allí? ¿Sólo a través del ídolo? ¡Intentaré comprar cada poción de salud de los Miskito e iré allí esta noche! De alguna manera lo lograré...";
		link.l1 = "¡Detente! ¡Espera! Nathan está enfermo, pero no hay amenaza para su vida. Un muchacho lo está cuidando y alimentando. Si pasas por el ídolo, arruinarás tu salud y la isla es realmente peligrosa. ¡Es demasiado arriesgado!";
		link.l1.go = "arrive_10";
		break;

	case "arrive_10":
		dialog.text = "¿Entonces qué estás sugiriendo? ¿No hacer nada mientras Nathan sufre o quizá muere?";
		link.l1 = "Deja de ser histérica. Primero, te dije que Nathan está enfermo pero no muriéndose. He hablado con él. Segundo, voy a zarpar hacia la Isla y tú vendrás conmigo.";
		link.l1.go = "arrive_11";
		break;

	case "arrive_11":
		dialog.text = "¿Sabes dónde está esa isla?";
		link.l1 = "¡Por supuesto que sí! No solo he encontrado a Nathan, sino también a Shark Dodson. He conseguido las coordenadas aproximadas de la Isla y las instrucciones de navegación para sortear los arrecifes que la rodean. Y ahora volvemos a mi barco y zarpamos hacia Blueweld...";
		link.l1.go = "arrive_12";
		break;

	case "arrive_12":
		dialog.text = "¿Con qué propósito? ¿Por qué no podemos zarpar directamente a la Isla ahora?";
		link.l1 = "Dannie, necesito organizar una expedición. Hay una enorme falta de provisiones en la Isla, así que compraré tanta comida como pueda. Luego tendré que elegir un barco para navegar allí, no todos los barcos podrán sortear los arrecifes de la Isla. Y también quiero hablar con Svenson primero...";
		link.l1.go = "arrive_13";
		break;

	case "arrive_13":
		dialog.text = "";
		link.l1 = "No tardará mucho en prepararse. La isla no está lejos de aquí, está al noroeste de La Habana, al este del Golfo de México.";
		link.l1.go = "arrive_14";
		break;

	case "arrive_14":
		dialog.text = "Bien... entonces hagámoslo. Has encontrado a Nathan y eso es lo más importante. ¡Gracias! ¿Se siente mal allí?";
		link.l1 = "Bueno... está enfermo. Y además de eso, también está deprimido y desesperado. Te extraña. Y sí, Nathan me pidió que te dijera que te quiere mucho.";
		link.l1.go = "arrive_15";
		break;

	case "arrive_15":
		dialog.text = "(limpiándose una lágrima) ¡Viejo tonto! Nunca me escuchó... " + pchar.name + ", ¡vamos a tu barco! ¡Quiero navegar allí lo más rápido posible!";
		link.l1 = "Claro, Dannie. Y te contaré sobre mis aventuras. ¡Vamos!";
		link.l1.go = "Dolly_4";
		AddQuestRecord("BaronReturn", "9");
		LAi_LocationDisableOfficersGen("Pearl_jungle_03", false);				   // пускать офицеров в локу телепорта
		LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false); // разрешить драться
		setCharacterShipLocation(pchar, "Shore9");								   // калеуче
		setWDMPointXZ("Shore9");												   // корабль в бухту Аматике
		bNoEatNoRats = false;													   // еду и крыс включить

		AddDialogExitQuestFunction("HelenDrinking_JungleDialog");
		break;

	// в LSC у причала
	case "nathaniel":
		dialog.text = "¡Nunca he visto un lugar como este antes! ¡Toda la isla está hecha de barcos!";
		link.l1 = "Te lo dije, Dannie...";
		link.l1.go = "nathaniel_1";
		break;

	case "nathaniel_1":
		dialog.text = "Pero ahora puedo verlo con mis propios ojos. De todos modos, dime dónde encontrar a Nathaniel.";
		link.l1 = "Está dentro de uno de los barcos. Pero debes nadar hasta allí.";
		link.l1.go = "nathaniel_2";
		break;

	case "nathaniel_2":
		dialog.text = "No me importa. Dime cómo llegar a este barco.";
		link.l1 = "Dannie, cálmate. Tú y Nathan habéis estado esperando mucho tiempo, así que ten un poco más de paciencia. Yo te llevaré hasta él, nunca lo encontrarás tú solo. No quiero que te topes con los Narwhals o los Rivados, empezarás a discutir con ellos y no terminará bien.";
		link.l1.go = "nathaniel_3";
		break;

	case "nathaniel_3":
		dialog.text = "Está bien, vamos entonces. Te seguiré.";
		link.l1 = "No olvides que tendremos que nadar mucho.";
		link.l1.go = "nathaniel_4";
		break;

	case "nathaniel_4":
		dialog.text = "Está bien, puedo manejarlo.";
		link.l1 = "Me alegra oír eso... ¡Pronto verás a tu esposo!";
		link.l1.go = "nathaniel_5";
		break;

	case "nathaniel_5":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorFollowEverywhere(npchar, "", -1);
		pchar.quest.LSC_Danny_Natan.win_condition.l1 = "location";
		pchar.quest.LSC_Danny_Natan.win_condition.l1.location = "FernandaDiffIndoor";
		pchar.quest.LSC_Danny_Natan.function = "LSC_DannyAndNatan";
		AddQuestRecord("LSC", "15");
		// следующая нода
		if (CheckCharacterItem(pchar, "keys_skel")) // идёт Оле
		{
			sld = characterFromId("Ole");
			LAi_SetActorType(sld);
			LAi_ActorDialog(sld, pchar, "", -1, 0);
		}
		else
		{
			if (GetCharacterIndex("Mary") != -1) // иначе Мэри
			{
				sld = characterFromId("Mary");
				LAi_SetActorType(sld);
				LAi_ActorDialog(sld, pchar, "", -1, 0);
			}
			else // иначе завершение
			{
				chrDisableReloadToLocation = false;
				LAi_LocationFightDisable(&Locations[FindLocation(pchar.location)], false);
			}
		}
		break;

	case "nathaniel_6":
		dialog.text = "Nathaniel... ¡Nathan! ¡Maldita sea! Mi amor...";
		link.l1 = "...";
		link.l1.go = "nathaniel_7";
		break;

	case "nathaniel_7":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_SetActorType(pchar);
		SetMusic("music_romantic");
		bDisableCharacterMenu = true; // лоченые интерфейсы
		locCameraRotateAroundHero(0.0, 2.0, 0.0, 0.005, 0.0, 2.0, 0.0, 1000);
		Pchar.FuncCameraFly = "";
		DoQuestCheckDelay("LSC_DanielleRomantic", 15.0);
		break;

	case "nathaniel_8":
		dialog.text = "Jesús, mírate a ti mismo... ¿Por qué te hiciste eso a ti mismo?...(llora) ¡Nunca me escuchas, nunca! ¡Te dije que no fueras a esa selva! ¡Pero fuiste de todos modos! ¿Por qué, Nathan?!";
		link.l1 = "Dannie... Lo siento. No tuve elección, lo sabes...";
		link.l1.go = "nathaniel_9";
		break;

	case "nathaniel_9":
		sld = characterFromId("Blaze");
		dialog.text = "¡Lo sé! ¡Oh, Dios, querido... qué te ha pasado! (entre lágrimas) Está bien, querido, todo va a estar bien... Estoy aquí. Te llevaremos a los Miskito, a Ojo de Serpiente." + sld.name + "  me dijo que el chamán podrá sanarte. Tenemos un barco... ¡Todo va a estar bien!";
		link.l1 = "Dannie, querida... ¡mi amor! Tu presencia solo me ha sanado a medias. Iremos a donde digas. Si es a Ojo de Serpiente, entonces a él.";
		link.l1.go = "nathaniel_10";
		break;

	case "nathaniel_10":
		dialog.text = "Empaca tus cosas. Oh, soy tan estúpido... No hay cosas que empacar excepto botellas vacías. Nathan...";
		link.l1 = "Dannie...";
		link.l1.go = "nathaniel_11";
		break;

	case "nathaniel_11": // перекидываем pchar
		DialogExit();
		LAi_SetStayType(pchar);
		DeleteAttribute(pchar, "GenQuest.MusicContinue");
		SetMainCharacterIndex(GetCharacterIndex("Blaze"));
		PChar = GetMainCharacter();
		LAi_SetPlayerType(PChar);
		sld = characterFromId("Danielle");
		sld.dialog.currentnode = "nathaniel_12";
		LAi_SetActorType(sld);
		LAi_ActorDialogDelay(sld, pchar, "", 1.2);
		break;

	case "nathaniel_12":
		dialog.text = "" + pchar.name + " ... perdóname a mí y a Nathan por la escena.";
		link.l1 = "¡Dannie! ¿Perdonarte por qué? Todo está bien. ¿Te avergüenzas de tus sentimientos?";
		link.l1.go = "nathaniel_13";
		break;

	case "nathaniel_13":
		dialog.text = "No, no soy... Es solo...";
		link.l1 = "Nadie sabrá nunca de esta escena. Lo prometo. Y nadie sabrá lo que le pasó a Nathan. ¡Los piratas de Maroon Town verán a un Nathaniel Hawk fuerte y formidable!";
		link.l1.go = "nathaniel_14";
		break;

	case "nathaniel_14":
		dialog.text = "Gracias, " + pchar.name + "¡Te debo... Llevaré a mi esposo al barco. No te preocupes, lograré llevarlo allí, recordé el camino. Lo pondré en una cama y me quedaré con él. Navegaremos a Ojo de Serpiente después de que termines con todo lo que necesitas hacer aquí. Creo en su capacidad para curar a Nathan.";
		link.l1 = "Está bien, Dannie. De todos modos, no nos quedaremos aquí mucho tiempo. ¿Estás seguro de que no necesitas ayuda?";
		link.l1.go = "nathaniel_15";
		break;

	case "nathaniel_15":
		dialog.text = "Estoy segura. Llegaremos al barco. ¡No te preocupes, no dejaré que mi esposo muera!";
		link.l1 = "¡Dannie, eres... maravillosa!";
		link.l1.go = "nathaniel_16";
		break;

	case "nathaniel_16":
		dialog.text = "(secándose una lágrima) Ve... solo ve, " + pchar.name + "... ¡y por favor no pierdas el tiempo aquí!";
		link.l1 = "...";
		link.l1.go = "nathaniel_17";
		break;

	case "nathaniel_17":
		chrDisableReloadToLocation = false; // открыть локацию
		bDisableCharacterMenu = false;		// лоченые интерфейсы
		EndQuestMovie();
		DialogExit();
		pchar.quest.LSC_NatanPassenger.win_condition.l1 = "ExitFromLocation";
		pchar.quest.LSC_NatanPassenger.win_condition.l1.location = pchar.location;
		pchar.quest.LSC_NatanPassenger.function = "LSC_SetNatanPassenger";
		pchar.quest.Saga_NatanTreatment.win_condition.l1 = "location";
		pchar.quest.Saga_NatanTreatment.win_condition.l1.location = "Miskito_village";
		pchar.quest.Saga_NatanTreatment.function = "Saga_NatanPrepareTreatment";
		pchar.questTemp.Saga.BaronReturn = "shamane";
		AddQuestRecord("BaronReturn", "11");
		// открываем вход к Мэри
		if (GetCharacterIndex("Mary") != -1)
		{
			for (i = 0; i <= 3; i++)
			{
				LocatorReloadEnterDisable("LostShipsCity_town", "reload6" + i, false);
			}
		}
		else
		{
			bQuestDisableMapEnter = false;				   // открыть карту
			DeleteAttribute(pchar, "GenQuest.CannotWait"); // можно мотать время
		}
		break;

	case "treatment":
		dialog.text = "¿Y qué? ¿Él curará a mi esposo? ¡Dime que lo curará!";
		link.l1 = "Dannie, Nathan tendrá que quedarse aquí. Solo. El chamán pidió no interrumpir sus ritos. Eso también te concierne. Ha prometido curar a Nathaniel en un mes.";
		link.l1.go = "treatment_1";
		break;

	case "treatment_1":
		dialog.text = "Sabes, " + pchar.name + ", ahora finalmente puedo respirar libremente otra vez. Creo firmemente que el chamán devolverá a mi esposo a su estado normal. Dejaré a Nathan aquí sin dudarlo porque si Ojo de Serpiente no puede curarlo, nadie podrá.";
		link.l1 = "Todo estará bien, Dannie. Ojo de Serpiente nunca me ha mentido. Confío en él.";
		link.l1.go = "treatment_2";
		break;

	case "treatment_2":
		dialog.text = "Yo también. Me quedaré contigo por un rato, " + pchar.name + "¿estás bien con eso? Todavía tenemos que encontrar a ese bastardo de Jackman, después de todo, él es responsable de todos nuestros problemas. ¡Él organizó la emboscada! ¡Tomó el lugar de Nathan en Maroon Town! ¡Robó nuestra fragata 'Centurion'!";
		link.l1 = "De acuerdo. Tenemos que ocuparnos de Jackman. Ninguno de nosotros estará a salvo hasta que Jackman esté muerto. Sin embargo, no será fácil matarlo.";
		link.l1.go = "treatment_3";
		break;

	case "treatment_3":
		if (!CheckAttribute(pchar, "questTemp.Saga.DodsonDie"))
			sTemp = "Shark Dodson";
		else
			sTemp = "Marcus Tyrex";
		dialog.text = "¿Tienes algún plan, " + pchar.name + "?";
		link.l1 = "Aún no. Necesito ir a Jan Svenson y pedirle consejo. Hagamos una cosa tras otra, tenemos que promover " + sTemp + " al jefe de la Cofradía de los Hermanos de la Costa primero. Así que, necesitamos obtener un voto de cada barón pirata para hacer eso.";
		link.l1.go = "treatment_4";
		break;

	case "treatment_4":
		dialog.text = "Está bien, vayamos a Svenson. Escuchemos lo que dice ese vejestorio...";
		link.l1 = "Sabes, no deberías ser tan negativo hacia Jan. En realidad, sería mucho mejor si hicieras las paces con él... después de todo, ¡todos compartimos el mismo objetivo!";
		link.l1.go = "treatment_5";
		break;

	case "treatment_5":
		dialog.text = "Pero solo porque te respeto... Está bien, " + pchar.name + ", lo siento. No quise insultar a Svenson, solo estoy nervioso. No volverá a suceder.";
		link.l1 = "Bien. Dannie, todo estará bien. ¡Te lo puedo prometer!";
		link.l1.go = "treatment_6";
		break;

	case "treatment_6":
		dialog.text = "Confío absolutamente en ti, " + pchar.name + "¿Vamos a Svenson?";
		link.l1 = "¡Vamos, Dannie!";
		link.l1.go = "Dolly_4";
		AddQuestRecord("BaronReturn", "13");
		break;

	case "islatesoro":
		dialog.text = "¿Sí? Estoy escuchando. ¿En qué puedo ayudarte?";
		link.l1 = "¿Tienes alguna idea de dónde podría esconderse Jackman? Conoces a ese bastardo mejor que yo. Tal vez tenga algún lugar, una base...";
		link.l1.go = "islatesoro_1";
		break;

	case "islatesoro_1":
		dialog.text = "¡Maldita sea si lo sé! Jacob siempre fue muy reservado. Nunca he oído hablar de su guarida. Probablemente sea mejor tratar de pensar lógicamente... Leamos la carta que recibiste de Knive nuevamente. Podríamos encontrar alguna pista allí.";
		link.l1 = "Intentemos...";
		link.l1.go = "islatesoro_2";
		break;

	case "islatesoro_2":
		RemoveItems(pchar, "letter_chad", 1);
		dialog.text = "Bueno... menciona Isla Tesoro y algún testamento... ¿Te suena familiar?";
		link.l1 = "Jan y yo pensamos que Blaze Sharp fue asesinado por Jackman en Isla Tesoro y que Shark fue culpado por ello. Y un testamento... una perra... debe ser sobre Helen... ¡Maldita sea, cómo no lo entendí antes! ¡Este bastardo debe estar navegando cerca de Isla Tesoro!";
		link.l1.go = "islatesoro_3";
		break;

	case "islatesoro_3":
		dialog.text = "No perdamos nuestro tiempo entonces, " + pchar.name + ".";
		link.l1 = "Sí. Vamos a Isla Tesoro. El viejo 'Marlin' nos ayudará en este asalto.";
		link.l1.go = "islatesoro_4";
		break;

	case "islatesoro_4":
		DialogExit();
		AddQuestRecord("BarbTemptation", "18");
		pchar.questTemp.Saga.BarbTemptation = "islatesoro";
		// ставим прерывание на Исла-Тесоро
		pchar.quest.Saga_AttackJackman.win_condition.l1 = "location";
		pchar.quest.Saga_AttackJackman.win_condition.l1.location = "Bermudes";
		pchar.quest.Saga_AttackJackman.function = "Saga_CheckJackmanBermudes";
		break;

	case "after_boarding":
		dialog.text = "Al fin, ese bastardo está muerto... No puedo creerlo, ¡estoy de nuevo en la cubierta del 'Centurión'! Conozco cada clavo de aquí y parece que el barco también me ha reconocido.";
		link.l1 = "Ella es tuya otra vez, Dannie. Tuya y de Nathaniel.";
		link.l1.go = "after_boarding_1";
		break;

	case "after_boarding_1":
		PlaySound("Voice\Spanish\saga\Denny Hawk-03.wav");
		dialog.text = "Mi Centurión me da la bienvenida. He esperado tanto tiempo para esto. Ni te imaginas cuánto me alegra. Nathaniel solía hablar a menudo de nuestro barco, se alegrará de saber que es nuestro una vez más.";
		link.l1 = "¿Qué vas a hacer ahora, Dannie?";
		link.l1.go = "after_boarding_2";
		break;

	case "after_boarding_2":
		dialog.text = "¿Yo? Llevaré el barco a Sharp town, contrataré al menos la tripulación mínima y navegaré hacia Blueweld. Pediré a Jan Svenson que cuide del 'Centurión', iré al pueblo Miskito y esperaré allí hasta que Ojo de Serpiente haya sanado a mi esposo.";
		link.l1 = "¿Realmente vas a visitar a Jan Svenson? Estoy sorprendido...";
		link.l1.go = "after_boarding_3";
		break;

	case "after_boarding_3":
		dialog.text = "" + pchar.name + ", todo es tu mérito. He estado pensando en tus palabras: 'todos compartimos el mismo objetivo'. ¿Recuerdas? Quiero hacer las paces con Svenson, después de todo, él ha ayudado a devolverme a Nathan. Es hora de dejar de discutir.";
		link.l1 = "¡Sabias palabras, Dannie! Nathaniel podrá retomar su posición en Maroon Town tan pronto como se sienta mejor.";
		link.l1.go = "after_boarding_4";
		break;

	case "after_boarding_4":
		dialog.text = "Quizás... el asunto es que el barón pirata es un cargo electivo. ¿Y si los otros deciden en contra?";
		link.l1 = "Deja que Svenson se encargue de ello. Él puede persuadir a cualquiera. La eliminación de Jackman también jugará su papel.";
		link.l1.go = "after_boarding_5";
		break;

	case "after_boarding_5":
		dialog.text = "Bien. De todas formas, necesito hacer de Svenson mi amigo... " + pchar.name + "¡Quiero agradecerte por todo lo que has hecho por mí y por Nathan! Has salvado a mi esposo y nos devolviste todo lo que habíamos perdido. Estoy en deuda contigo.";
		link.l1 = "Vamos, Dannie. Somos amigos.";
		link.l1.go = "after_boarding_6";
		break;

	case "after_boarding_6":
		dialog.text = "Quiero que sepas que siempre estaremos encantados de verte en Maroon Town. Encuéntranos allí cuando tengas algo de tiempo. Nathaniel y yo encontraremos una manera de recompensarte.";
		link.l1 = "¡Cielo santo, Dannie! Acepto tu invitación con placer. Nos sentaremos, beberemos y hablaremos de cómo tú y Nathan hundieron a Van der Decken...";
		link.l1.go = "after_boarding_7";
		break;

	case "after_boarding_7":
		dialog.text = "¿Él habló? Oh, no me lo recuerdes...";
		link.l1 = "Está bien, Dannie. Tienes mucho trabajo por delante y yo tengo que visitar a nuestros amigos jurados - Marcus y Barbazon. Espero que me dejes poner patas arriba esta cabina, estoy seguro de que hay muchas cosas interesantes en los cofres de Jackman.";
		link.l1.go = "after_boarding_8";
		break;

	case "after_boarding_8":
		dialog.text = "Claro, ¿de verdad crees que me opondría?";
		link.l1 = "Genial. En realidad es una pena separarse de ti, Dannie... ¡Nos vemos en Maroon Town!";
		link.l1.go = "after_boarding_9";
		break;

	case "after_boarding_9":
		DialogExit();
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1", "none", "", "", "OpenTheDoors", -1);
		LAi_SetHP(npchar, 280, 280);
		LAi_SetImmortal(npchar, false);							  // если сработало
		pchar.GenQuest.CannotTakeShip = true;					  // нельзя захватить
		DoQuestFunctionDelay("Saga_CheckJackmanCabinItems", 5.0); // первая проверка через 5 сек
		AddCharacterExpToSkill(pchar, "Leadership", 300);
		break;

	// в Марун-Тауне
	case "marun_town":
		dialog.text = "" + pchar.name + ", ¡me alegro mucho de verte! Estamos de vuelta en Maroon Town y Nathan está en su lugar legítimo otra vez. En realidad, todos en el pueblo están contentos por ello. ¡Ahora todo irá tan bien como solía ser! Estoy muy agradecido por tu desinteresada ayuda.\nQuiero darte un regalo. Aquí, tómalo. Este talismán puede hacer que una pelea sea mucho más fácil para ti. Y esta fórmula te permitirá hacer más de ellos para ti mismo.";
		link.l1 = "¡Gracias, Dannie!";
		link.l1.go = "marun_town_1";
		break;

	case "marun_town_1":
		GiveItem2Character(pchar, "totem_12");
		GiveItem2Character(pchar, "recipe_totem_12");
		Log_Info("Has recibido un talismán");
		Log_Info("Has recibido la receta del talismán");
		PlaySound("interface\important_item.wav");
		dialog.text = "No es todo. También he encontrado dos cofres llenos de oro aquí. Eran propiedad de Jackman, sin duda. Tómalos como muestra de mi gratitud. ¡Y no te atrevas a rechazarlo! Sé cuánto dinero has gastado para ayudarme a mí y a Nathan.";
		link.l1 = "Está bien, está bien, Dannie, ¡los acepto!";
		link.l1.go = "marun_town_2";
		break;

	case "marun_town_2":
		TakeNItems(pchar, "chest", 2);
		Log_Info("Has recibido dos cofres con doblones");
		PlaySound("interface\important_item.wav");
		dialog.text = "¡Excelente! " + pchar.name + ", quiero que sepas que a partir de ahora eres nuestro mejor amigo. ¡Nathan y yo siempre estaremos encantados de verte en Maroon Town! ¡Visítanos más a menudo!";
		link.l1 = "¡Gracias! Me alegrará verte de nuevo, ¡así que espérame!";
		link.l1.go = "exit";
		NextDiag.TempNode = "marun_town_3";
		break;

	case "marun_town_3":
		if (CheckAttribute(pchar, "GenQuest.MaruntownSex"))
		{
			dialog.text = "¿Qué podemos hacer por ti, " + pchar.name + "?";
			link.l1 = "Por desgracia, ya me voy... Adiós, Danny.";
			link.l1.go = "exit";
			if (CheckAttribute(pchar, "GenQuest.MaruntownSex2"))
			{
				dialog.text = "Y aquí está " + GetFullName(pchar) + "¡Se nota por tu cara que no has perdido el tiempo!";
				link.l1 = "Debo admitir, ¡sabes cómo divertirte! Gracias, lo pasé de maravilla.";
				link.l1.go = "marun_town_fuckgirl_3";
			}
			NextDiag.TempNode = "marun_town_3";
			break;
		}
		bOk1 = CheckAttribute(pchar, "questTemp.LSC.Mary_officer") && IsOfficer(characterFromId("Mary"));
		bOk2 = CheckAttribute(pchar, "questTemp.Saga.Helena_officer") && IsOfficer(characterFromId("Helena"));
		dialog.text = "Me alegra verte, " + pchar.name + "¡Ron, vino? ¿O una chica?";
		link.l1 = "¡Gracias, Dannie! Solo quería verte...";
		link.l1.go = "exit";
		if (bOk1 || bOk2)
		{
			link.l2 = "La chica? ¡Tranquilo, Danny! No querrás encontrarme cortado en pedazos y cuidadosamente doblado en tu puerta, ¿verdad? Ja-ja. Mi fiel dama, que está justo al otro lado de la puerta, no me perdonará por tales travesuras.";
			link.l2.go = "marun_town_fuckgirl_Otkaz_1";
		}
		else
		{
			link.l2 = "¿Una chica? Eso suena interesante, Danny. He estado anhelando... el latido de una mujer... Creo que debería echar un vistazo - no sugerirías a cualquiera, ¿verdad?";
			link.l2.go = "marun_town_fuckgirl_1";
		}
		NextDiag.TempNode = "marun_town_3";
		break;

	// Данни предлагает девочку
	case "marun_town_fuckgirl_Otkaz_1":
		dialog.text = "¿En serio? ¿Por qué estás tan pálido? Ja-ja, solo bromeaba. Cuida de ella, ¿me oyes?";
		link.l1 = "Por supuesto. ¡Ella es más preciosa para mí que todos los tesoros de estas tierras!";
		link.l1.go = "marun_town_fuckgirl_Otkaz_2";
		break;

	case "marun_town_fuckgirl_Otkaz_2":
		dialog.text = "Eso está mejor, ja-ja. Vamos, anda ya, tu querida probablemente se está poniendo nerviosa.";
		link.l1 = "Adiós, Danny. Y gracias por tu preocupación, ja-ja.";
		link.l1.go = "exit";
		break;

	case "marun_town_fuckgirl_1":
		dialog.text = "Os aseguro, esta joven belleza definitivamente sabe cómo brindaros un tiempo inolvidable, " + pchar.name + ". ¡Diviértete! Ella te estará esperando en la habitación de la taberna.";
		link.l1 = "Gracias, Danny. Estoy en camino. ¡No quiero perder ni un minuto!";
		link.l1.go = "marun_town_fuckgirl_2";
		break;

	case "marun_town_fuckgirl_3":
		dialog.text = "" + pchar.name + ", ¡siempre eres bienvenido en Maroon Town! ¡Las mejores chicas son tuyas!";
		link.l1 = "Oh, Danny. Te juro, este es mi segundo hogar.";
		link.l1.go = "exit";
		DeleteAttribute(pchar, "GenQuest.MaruntownSex2");

		break;

	case "marun_town_fuckgirl_2":
		DialogExit();
		pchar.GenQuest.MaruntownSex = "true";
		SetTimerCondition("MarunFuckGirl_4", 0, 0, 2, false);
		LocatorReloadEnterDisable("FortOrange_tavern", "reload2_back", false); // открыть комнату
		sld = GetCharacter(NPC_GenerateCharacter("MarunFuckGirl", "women_2" + (rand(6)), "woman", "woman", 1, PIRATE, 1, false, "quest"));
		sld.Dialog.Filename = "Quest\Saga\Danielle.c";
		sld.dialog.currentnode = "MarunFuckGirl";
		LAi_SetStayType(sld);
		ChangeCharacterAddressGroup(sld, "FortOrange_tavern_upstairs", "goto", "goto1");
		break;

	// Диалог с проституткой
	case "MarunFuckGirl":
		dialog.text = "Y aquí está mi capitán. ¡Hoy eres solo mío! Ven a mí, te he estado esperando tanto tiempo...";
		link.l1 = "¿Oh, es así? ¿No puedes esperar más? ¡Bueno, no perdamos tiempo!";
		link.l1.go = "MarunFuckGirl_2";
		LocatorReloadEnterDisable("FortOrange_tavern", "reload2_back", true); // закрыть комнату
		chrDisableReloadToLocation = true;
		break;

	case "MarunFuckGirl_2":
		DialogExit();

		StartQuestMovie(true, false, true);
		LAi_SetActorType(pchar);
		LAi_Fade("MarunFuckGirl", "");
		pchar.GenQuest.MaruntownSex2 = "true";
		break;

	case "MarunFuckGirl_3":
		dialog.text = RandPhraseSimple("Mi capitán... ¡realmente sabes cómo conquistar a las damas! ¡Nunca había experimentado algo así antes! ¿Quizás te quedes un par de horas más?", "¿Te vas ya, mi querido?");
		link.l1 = RandPhraseSimple("Sabía que no querrías dejarme ir tan fácilmente. Adiós, querida. Grandes cosas me esperan...", "¡Ay, el trabajo se interpone en el camino! Pero tal vez nos volvamos a encontrar...");
		link.l1.go = "MarunFuckGirl_4";
		break;

	case "MarunFuckGirl_4":
		DialogExit();
		chrDisableReloadToLocation = false;
		LAi_SetCitizenType(npchar);
		LAi_CharacterDisableDialog(npchar);
		break;

		// ------------------------------------------- провалы Саги ------------------------------------------------
	case "failcenturion":
		dialog.text = "¡Por fin Nathan y yo podemos respirar libremente de nuevo! ¡Ese maldito bastardo de Jackman está muerto! Me siento mal por el 'Centurión', pero ya había aceptado su pérdida cuando ese bastardo me la robó. Así que no me preocupo demasiado.";
		link.l1 = "Pero yo sí. ¡Soy un idiota! Todas las pruebas se han hundido en el fondo del mar junto con el barco. Podrían habernos ayudado en la votación para el nuevo líder de la Cofradía de los Hermanos de la Costa. Ahora... todo se ha perdido.";
		link.l1.go = "failcenturion_1";
		break;

	case "failcenturion_1":
		dialog.text = "¡No te pongas tan triste! Sucede. La próxima vez tendrás más suerte... Como sea. Quiero agradecerte por lo que has hecho por mí y Nathan. Has salvado la vida de mi esposo. Te debo mucho. \nQuiero que sepas que Maroon Town siempre estará encantada de verte. Visítanos a mí y a Nate cuando tengas tiempo. Encontraremos una manera de recompensarte.";
		link.l1 = "Está bien, Dannie. Te visitaré seguro. ¿Ya te vas?";
		link.l1.go = "failcenturion_2";
		break;

	case "failcenturion_2":
		dialog.text = "Sí, iré a los Miskito, espero que Ojo de Serpiente ya haya curado a Nathan. Luego volveremos a Maroon Town.";
		link.l1 = "Je, ya estoy tan acostumbrado a ti, es una pena que tenga que separarme de ti... ¡Buena suerte, Dannie!";
		link.l1.go = "failcenturion_3";
		break;

	case "failcenturion_3":
		DialogExit();
		RemovePassenger(pchar, npchar);
		LAi_SetActorType(npchar);
		LAi_ActorGoToLocation(npchar, "reload", "reload1_back", "none", "", "", "Saga_FailCenturion", 10.0);
		npchar.greeting = "danny_2";
		break;

	case "before_kiss":
		dialog.text = "Oh, no te hagas la tonta, querida. Charles, este bicho del amor daba vueltas alrededor de ese ídolo día y noche, y seguía molestando al pobre Ojo de Serpiente con preguntas. Y luego corrió a casa y le trajo algo, ¿no es así?";
		link.l1 = "";
		link.l1.go = "exit";

		AddDialogExitQuestFunction("HelenDrinking_JungleDialog2");
		break;

	case "after_kiss":
		dialog.text = "¡Oh, gracias por el espectáculo, Charles. Todo Maroon Town estará chismorreando sobre ello, ja-ja!";
		link.l1 = "No tengo duda de que es tu nueva prioridad - asegurarte de que suceda.";
		link.l1.go = "after_kiss_1";
		break;

	case "after_kiss_1":
		dialog.text = "En realidad, al final de mi lista. No te enfades con la chica, es su primera vez. Cuando Nathan y yo teníamos nuestras aventuras, todo el archipiélago también se reía de nosotros.";
		link.l1 = "Cambiemos de tema y de humor. Estoy harto de este ídolo, vámonos.";
		link.l1.go = "after_kiss_2";
		break;

	case "after_kiss_2":
		dialog.text = "De acuerdo, vamos, héroe.";
		link.l1 = "";
		link.l1.go = "Dolly_4";

		AddDialogExitQuestFunction("HelenDrinking_AfterKiss3");
		break;

	//--> ----------------------------------- офицерский блок ------------------------------------------
	case "Danielle_officer":
		dialog.text = "¿Qué quieres, capitán?";
		if (CheckAttribute(pchar, "questTemp.Saga.BarbTemptation") && pchar.questTemp.Saga.BarbTemptation == "danielle")
		{
			Link.l3 = "¡Dannie, quiero pedirte consejo!";
			Link.l3.go = "islatesoro";
		}
		Link.l1 = "¡Escucha mi orden!";
		Link.l1.go = "stay_follow";
		link.l2 = "¡No es nada. Despedido!";
		link.l2.go = "exit";
		NextDiag.TempNode = "Danielle_officer";
		sld = characterFromId("Danielle");
		sld.HoldEquip = true; // лесник -  не отдавать саблю и пистоль для текущей игры. поэтому так . другого способа не нашёл
		break;

	case "stay_follow":
		dialog.Text = "¿Órdenes?";
		Link.l1 = "¡Quédate aquí!";
		Link.l1.go = "Boal_Stay";
		Link.l2 = "¡Sígueme y no te quedes atrás!";
		Link.l2.go = "Boal_Follow";
		sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
		if (sGun != "")
		{
			rItm = ItemsFromID(sGun);
			if (CheckAttribute(NPChar, "chr_ai.gun.bulletNum") && sti(NPChar.chr_ai.gun.bulletNum) > 1)
			{
				Link.l3 = "Cambia el tipo de munición para tus armas de fuego.";
				Link.l3.go = "SetGunBullets";
			}
		}
		break;

	case "SetGunBullets":
		Dialog.Text = "Eligiendo el tipo de munición:";
		sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
		rItm = ItemsFromID(sGun);
		makearef(rType, rItm.type);
		for (i = 0; i < sti(NPChar.chr_ai.gun.bulletNum); i++)
		{
			sAttr = GetAttributeName(GetAttributeN(rType, i));
			sBullet = rItm.type.(sAttr).bullet;
			rItem = ItemsFromID(sBullet);
			attrL = "l" + i;
			Link.(attrL) = GetConvertStr(rItem.name, "ItemsDescribe.txt");
			;
			Link.(attrL).go = "SetGunBullets1_" + i;
		}
		break;

	case "SetGunBullets2":
		i = sti(NPChar.SetGunBullets) + 1;
		sGun = GetCharacterEquipByGroup(NPChar, GUN_ITEM_TYPE);
		rItm = ItemsFromID(sGun);
		sAttr = "t" + i;
		sBullet = rItm.type.(sAttr).bullet;
		LAi_SetCharacterUseBullet(NPChar, GUN_ITEM_TYPE, sBullet);
		LAi_GunSetUnload(NPChar, GUN_ITEM_TYPE);
		NextDiag.CurrentNode = NextDiag.TempNode;
		rItem = ItemsFromID(sBullet);
		notification(GetFullName(NPChar) + " " + XI_ConvertString("AmmoSelectNotif") + GetConvertStr(rItem.name, "ItemsDescribe.txt") + "", "AmmoSelect");
		DeleteAttribute(NPChar, "SetGunBullets");
		DialogExit();
		break;

	case "Boal_Stay":
		Pchar.questTemp.HiringOfficerIDX = GetCharacterIndex(Npchar.id);
		AddDialogExitQuestFunction("LandEnc_OfficerStay");
		dialog.Text = "¡Hay un cambio de disposición!";
		Link.l1 = "Retirado.";
		Link.l1.go = "Exit";
		Npchar.chr_ai.tmpl = LAI_TMPL_STAY;
		break;

	case "Boal_Follow":
		SetCharacterTask_FollowCharacter(Npchar, PChar);
		dialog.Text = "¡Hay un cambio de disposición!";
		Link.l1 = "Despedido.";
		Link.l1.go = "Exit";
		break;
		//<-- ----------------------------------- офицерский блок ----------------------------------------

	case "":
		dialog.text = "";
		link.l1 = "";
		link.l1.go = "";
		break;

	case "Exit":
		NextDiag.CurrentNode = NextDiag.TempNode;
		DialogExit();
		break;
	}
}
