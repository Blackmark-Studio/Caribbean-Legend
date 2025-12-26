void ProcessDialogEvent()
{
	ref NPChar, sld;
	aref Link, NextDiag;
	int i, n;
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
		
		// =================================================================
		// ================== ЭТАП 1. «ЛОЩИНА ВЛЮБЛЁННЫХ» ==================
		// =================================================================
		case "Mary_1":
			dialog.text = ""+pchar.name+"¡Mira aquí!";
			link.l1 = "Más despacio, "+npchar.name+", puede que no estemos solos aquí.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_3");
		break;
		
		case "Mary_2":
			dialog.text = ""+pchar.name+"!";
			link.l1 = ""+npchar.name+"¿ Oye, me seguiste todo el tiempo, sí, ¿eh?";
			link.l1.go = "Mary_3";
		break;
		
		case "Mary_3":
			dialog.text = "Y, parece que no en vano, sí, ¿eh? ¿Qué ha pasado aquí?";
			link.l1 = "Si lo hubiera sabido, "+npchar.name+", si lo hubiera sabido...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_3");
		break;
		
		case "Mary_4":
			dialog.text = "Dios mío...";
			link.l1 = "Sí, pobrecillo, parece que le tocó sufrir antes de morir. No le desearía un final así ni a mi peor enemigo...";
			link.l1.go = "Mary_5";
		break;
		
		case "Mary_5":
			dialog.text = "¿Y ese de ahí quién es, su marido? ¿Qué demonios hacen metiéndose en la selva? ¿Acaso no han oído hablar de los esclavos fugitivos?";
			link.l1 = "Me temo que a esa pregunta ya no podrán responder...";
			link.l1.go = "Mary_6";
		break;
		
		case "Mary_6":
			dialog.text = "¿Crees que quien hizo esto todavía anda por aquí?";
			link.l1 = "Es muy probable. Por eso, tú y yo deberíamos andar con más cuidado – tenemos que verlos antes nosotros.";
			link.l1.go = "Mary_7";
		break;
		
		case "Mary_7":
			dialog.text = "Demasiado tarde, "+pchar.name+". Parece que ya nos han visto. Mira allí.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_6");
		break;
		
		case "Naemnik_1":
			dialog.text = "Así, así, chicos, mirad nada más. Esto parece un valle de enamorados, no hay duda, je-je. Apenas dos tortolitos entregaron el alma a Dios, y ya vienen otros dos a ocupar su lugar...";
			if (GetOfficersQuantity(pchar) >= 2)
			{
				link.l1 = "Muy ingenioso. Pero tú, al parecer, no sabes contar: a diferencia de esos pobres, nosotros aquí no estamos solos en absoluto.";
				link.l1.go = "Naemnik_2";
			}
			else
			{
				link.l1 = "Bueno, con nosotros será un poquito más difícil, sí, ¿eh? Créeme...";
				link.l1.go = "Naemnik_4";
			}
		break;
		
		case "Naemnik_2":
			dialog.text = "Diría que ustedes son más listos que ellos, pero sería una maldita mentira. Ni siquiera con tantos podrían vencer a esos bastardos. Y a tu belleza le habría tocado el mismo destino que a esa chica ahí, a tus pies...";
			link.l1 = "¿Hablas de los esclavos fugitivos? ¿Éste es uno de ellos? Entonces, ¿sois gente de Bishop?";
			link.l1.go = "Naemnik_3";
		break;
		
		case "Naemnik_3":
			dialog.text = "A todas las preguntas, sí. Más de dos días estuvimos junto con los soldados persiguiéndolos por toda la isla. Luego los desgraciados se dividieron. Unos se retiraron hacia la cueva — tras ellos fue la guardia, los demás huyeron hacia la bahía. Como resultado de su emboscada a media milla al oeste de aquí, perdimos a varios muchachos, y mientras nos recuperábamos y nos reorganizábamos, ellos se divirtieron con esa tonta...";
			link.l1 = "...";
			link.l1.go = "Naemnik_6_add";
		break;
		
		case "Naemnik_4":
			dialog.text = "No toques tu mondadientes, mocoso, no me pongas nerviosa a mí ni a los chicos. Me gustaría ver cómo te habría ayudado si te hubieras visto rodeado por una docena de esos desgraciados que tumbamos en la bahía. Mira, sólo uno tuvo suerte, pero no por mucho tiempo... En cuanto ese bastardo caiga en manos de Bishop...";
			link.l1 = "¿Así que ustedes son sus mercenarios?";
			link.l1.go = "Naemnik_5";
		break;
		
		case "Naemnik_5":
			dialog.text = "Pues está claro que no son soldados de guarnición. Si no fuera por esos blandengues, habríamos atrapado a los desgraciados ayer mismo — y ese idiota con su mujercita seguirían vivos...";
			link.l1 = "Así que no es cosa de tus manos...";
			link.l1.go = "Naemnik_6";
		break;
		
		case "Naemnik_6":
			dialog.text = "¿Por quién nos tomas, eh? Claro que no somos ángeles, pero si nos da la gana, vamos a un burdel, no a...";
			link.l1 = "...";
			link.l1.go = "Naemnik_6_add";
		break;
		case "Naemnik_6_add":
			StartInstantDialog("WildRose_Naemnik_Rab", "Naemnik_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_7":
			dialog.text = "¡Miente todo el tiempo, miente, ese canalla despreciable! No le escuches, "+GetAddress_Form(NPChar)+"¡Ni siquiera tocamos a esos pobres desgraciados!";
			link.l1 = "¿Ah, sí? ¿Y por qué deberíamos creerte a ti y no a él?";
			link.l1.go = "Naemnik_8";
			link.l2 = "¿Sí, eh? ¿Y si la que miente eres tú? No pareces precisamente una santa.";
			link.l2.go = "Naemnik_9";
		break;
		
		case "Naemnik_8":
			dialog.text = "Bueno, piénsalo tú mismo, ¡por el amor de Dios! Huíamos de esa bestia de Bishop, llevábamos dos días corriendo por la selva, confundiendo las huellas, ¿para qué? ¿Para ahora abusar de una pobre dama y dejar que esos sanguijuelas nos alcancen? ¡Mis amigos apenas pudieron arrastrarse hasta esa playa, "+GetAddress_Form(NPChar)+"¡ No teníamos ni fuerzas para disparar nuestros mosquetes, de lo contrario no habríamos dejado que esos canallas hicieran su fechoría... Fueron ellos, los vimos!.. ";
			link.l1 = "...";
			link.l1.go = "Naemnik_9_add";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Naemnik_9":
			dialog.text = "Bueno, piénsalo tú mismo, ¡por Dios! Huíamos de esa bestia de Bishop, pasamos dos días corriendo por la selva, perdiendo el rastro, ¿para qué? ¿Para ahora abusar de una pobre dama y dejar que esos sanguijuelas nos alcancen? ¡Mis amigos apenas pudieron arrastrarse hasta esa playa, "+GetAddress_Form(NPChar)+"¡ No teníamos ni fuerzas para disparar nuestros mosquetes, si no, no habríamos dejado que esos canallas hicieran su fechoría... Fueron ellos, los vimos!.. ";
			link.l1 = "...";
			link.l1.go = "Naemnik_9_add";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		case "Naemnik_9_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_10", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_10":
			dialog.text = "¡Cállate, Casper, perro sarnoso!";
			link.l1 = "...";
			link.l1.go = "Naemnik_10_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_Rab"));
		break;
		case "Naemnik_10_add":
			StartInstantDialog("Mary", "Naemnik_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_11":
			dialog.text = "¿Qué dijiste?!";
			link.l1 = "...";
			link.l1.go = "Naemnik_11_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
		break;
		case "Naemnik_11_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_12":
			dialog.text = "¿Qué pasa, señorita, tienes problemas de oído? Le dije que cerrara la boca. Nuestro Jerry puede pasarse horas contando cuentos - ¡vaya si tiene talento para eso! Bishop quería cortarle la lengua y obligarlo a tragársela, pero luego se arrepintió - y fue un error, maldita sea.";
			link.l1 = "...";
			link.l1.go = "Naemnik_12_add";
			CharacterTurnByChr(npchar, CharacterFromID("Mary"));
		break;
		case "Naemnik_12_add":
			StartInstantDialog("Mary", "Naemnik_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_13":
			dialog.text = "Pero... Lo llamaste Casper, sí, ¿eh...";
			link.l1 = "...";
			link.l1.go = "Naemnik_13_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
		break;
		case "Naemnik_13_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_14":
			dialog.text = "Escucha, chico, explícale a tu amiguita que la gente, incluso alguien tan inútil como ese mocoso, además de nombre también tiene apellido. He oído más de una vez que las mujeres guapas pueden ser tan tontas como un saco de paja, pero que yo me muera...";
			link.l1 = "...";
			link.l1.go = "Naemnik_14_add";
			CharacterTurnByChr(npchar, pchar);
		break;
		case "Naemnik_14_add":
			StartInstantDialog("Mary", "Naemnik_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_15":
			dialog.text = "¡Eso mismo es lo que voy a darte ahora, sí, ¿eh?!";
			link.l1 = "¡Mary, espera! Yo me encargaré de esto. Guarda el arma en la funda. Ahora mismo.";
			link.l1.go = "Naemnik_15_add";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_1"));
			LAi_SetActorType(npchar);
			LAi_ActorAnimation(npchar, "normal to fight", "1", 2.5);
			DoQuestFunctionDelay("WildRose_Etap1_EscapeSlaves_6_1", 3.0);
		break;
		case "Naemnik_15_add":
			StartInstantDialog("WildRose_Naemnik_1", "Naemnik_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Naemnik_16":
			dialog.text = "Oh, tenemos aquí a un caballero noble. Pues bien, tu comportamiento sí que es más digno que los chillidos de ese gusano. Gritaba más fuerte que su pobre mujercita — tanto, que se oía incluso desde detrás de aquella colina. Para ser sincero, hasta nos ayudó — fue así como rastreamos a esos desgraciados...";
			link.l1 = "Aquí, en el Caribe, la nobleza es algo bastante raro. Ahora, respiremos todos - no hay nada noble en irse al otro mundo aquí y ahora.";
			link.l1.go = "Naemnik_17";
			link.l2 = "Los únicos canallas aquí sois vosotros. Pídele disculpas a Mary ahora mismo y, quizá, podamos evitar el derramamiento de sangre.";
			link.l2.go = "Naemnik_22";
		break;
		
		case "Naemnik_17":
			dialog.text = "Es difícil no estar de acuerdo. Pero primero calma a tu...";
			link.l1 = "Se llama Mary Casper. Creo que eso aclarará muchas cosas.";
			link.l1.go = "Naemnik_18";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;
		
		case "Naemnik_18":
			dialog.text = "¿Casper? ¿Acaso es su hija, ja, ja?";
			link.l1 = "Dudo mucho que sea así. Pero espero que ahora tengas suficiente sentido común para retirar tus palabras.";
			link.l1.go = "Naemnik_19";
		break;
		
		case "Naemnik_19":
			dialog.text = "¿De vuelta? ¿Y si no qué? ¿Me retarás a un duelo? Adelante... Si no tienes miedo de dejar a tu adorada completamente sola, en medio de la selva, je, je. Los chicos y yo estaremos muuuuy contentos con ese giro.";
			link.l1 = "Ya has mostrado tu verdadera cara. No fingías tan bien, sí, ¿eh?";
			link.l1.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_22":
			dialog.text = "Usted, señor, es todo un manojo de contradicciones — tan pacífico y, al mismo tiempo, un grosero. Sin embargo, me intriga: ¿está rogando el perdón de esa pelirroja chiflada?";
			link.l1 = "Se llama Mary Casper, y si ahora mismo no...";
			link.l1.go = "Naemnik_23";
		break;
		
		case "Naemnik_23":
			dialog.text = "¿Casper? ¡Que me parta un rayo! Jerry, ¿no será esta tu hija, eh? ¡Ja-ja-ja-ja! ¡No me lo puedo creer! ¡Cosas que pasan!";
			link.l1 = "¿Y sabes qué más pasa? Los tipos como tú — tontos que sólo han oído hablar del honor de oídas — se comportan con las damas como si hubieran nacido en un establo. Aunque, ¿de qué sorprenderse? Cuando en vez de cerebro tienes serrín, los modales no pueden aparecer de la nada.";
			link.l1.go = "Naemnik_24";
		break;
		
		case "Naemnik_24":
			dialog.text = "Vaya... Qué gusano tan insolente. Dime, amigo, ¿es buena tu chica en la hamaca? Aunque, pensándolo bien, estoy seguro de que no — y con gusto lo comprobaré por mí mismo...";
			link.l1 = "Ya te descubriste. No te duró mucho, sí, ¿eh? ¡A luchar!";
			link.l1.go = "Naemnik_bitva";
		break;
		
		case "Naemnik_bitva":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_7");
		break;
		
		case "Djerry_1":
			dialog.text = "Vaya que les diste una buena paliza, sí, ¿eh? "+GetAddress_Form(NPChar)+", - a esos desgraciados. ¡Ojalá ardan en el infierno! Lástima que no llegué a ayudarte. El mosquete que vi de camino hasta aquí estaba demasiado lejos. Parece que alguno de los nuestros lo perdió cuando huíamos. Me habría gustado dispararle a ese bastardo de Primer con mis propias manos.";
			link.l1 = "Parece que Primer te fastidió bastante para que decidieras volver.";
			link.l1.go = "Djerry_2";
		break;
		
		case "Djerry_2":
			dialog.text = "Vaya si me fastidiaba. Por culpa de ese desgraciado tengo toda la espalda llena de marcas. Pero lo peor era que podía prohibirnos beber agua cuando le daba la gana.";
			link.l1 = "Qué lástima que ninguno de esos canallas haya quedado con vida. Podríamos haberlo entregado a los soldados, que seguro vendrán pronto por aquí.";
			link.l1.go = "Djerry_3_1";
		break;
		
		case "Djerry_3_1":
			dialog.text = "No entiendo muy bien para qué, eh, "+GetAddress_Form(NPChar)+"...";
			link.l1 = "Bueno, ya sabes... El comandante le habría sacado una confesión, limpiando vuestros nombres — el tuyo y el de tus amigos caídos.";
			link.l1.go = "Djerry_4";
		break;
		
		case "Djerry_4":
			dialog.text = "Sí, claro, jaja. Y luego William Bishop me arrancará la piel a tiras — me lo contó un negro de una plantación... Bishop no se anda con rodeos con los fugitivos — seas negro o blanco, no hace diferencia.";
			link.l1 = "Me temo que, de una forma u otra, tendrás que volver a la plantación...";
			link.l1.go = "Djerry_5";
			link.l2 = "Entonces, ¿no vas a volver a la plantación por tu propia voluntad, sí, ¿eh?";
			link.l2.go = "Djerry_6";
		break;
		
		case "Djerry_5":
			dialog.text = "Eres un buen bromista, ¿te lo han dicho alguna vez, sí, ¿eh? "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Sin bromas, "+npchar.name+". ¿Crees que terminé aquí por casualidad? Fui a la selva para buscar a tu grupo, llevarlos de vuelta a la plantación... y de paso ganar algo de oro. Pero sólo quedas tú. Por ti no sacaré mucho, así que quizá te deje ir. Pero dime, ¿en qué demonios estabas pensando? Te has quedado solo. Todos los demás están muertos. ¿A qué esperas aferrarte, maldita sea? ¿A esconderte en las montañas y entre los arbustos hasta que te alcance una bala, te mate la fiebre o termines siendo comida de jaguares?";
			link.l1.go = "Djerry_8";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Djerry_6":
			dialog.text = "Eres un bromista encantador, ¿te lo han dicho alguna vez, sí, ¿eh? "+GetAddress_Form(NPChar)+"?";
			link.l1 = "Nada de bromas, "+npchar.name+". ¿Crees que estoy aquí por casualidad? Me interné en la selva para buscar a tu escuadrón, devolverlos a la plantación — y, de paso, ganar algo de oro. Pero sólo quedas tú. No sacaré mucho por ti, así que puede que te deje libre. Pero dime, ¿en qué demonios estabas pensando? Te quedaste solo. Todos los demás están muertos. ¿A qué esperas, maldita sea? ¿A esconderte entre montañas y arbustos hasta que te alcance una bala, mueras de fiebre o acabes siendo comida de jaguares?";
			link.l1.go = "Djerry_8";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Djerry_8":
			dialog.text = "Mejor así, por Dios, "+GetAddress_Form(NPChar)+" - para mí, esto es mucho mejor que morir sufriendo como quería Bishop. Pero en realidad, no está tan mal: cerca del cabo Ragged Point tengo escondida una barca con vela.";
			link.l1 = "Las tierras más cercanas a Barbados son Dominica, con sus aborígenes, y Tobago, con los españoles. Ni siquiera sé qué sería para ti... peor.";
			link.l1.go = "Djerry_9";
		break;
		
		case "Djerry_9":
			dialog.text = "Creo que me arriesgaré con los don, en Tobago suelen fondear contrabandistas y piratas. Oh, veo que desapruebas mi elección, "+GetAddress_Form(NPChar)+". He servido a mi país con honestidad, sí, ¿eh? —pero ¿qué puedo hacer, si ella me mandó a las canteras?";
			link.l1 = "No te juzgo, "+npchar.name+". Cada uno tiene su propio camino. Ahora toma más pólvora y balas, y vete. Antes de que lleguen los soldados.";
			link.l1.go = "Djerry_10";
		break;
		
		case "Djerry_10":
			dialog.text = "Gracias, "+GetAddress_Form(NPChar)+". Y a usted, joven dama, eh, Mary. (hace una reverencia). Claro, no somos parientes, pero encontrar a alguien con el mismo apellido en una, eh, situación así... es bastante inesperado y...";
			link.l1 = "...";
			link.l1.go = "Djerry_10_add";
		break;
		case "Djerry_10_add":
			StartInstantDialog("Mary", "Djerry_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Djerry_11":
			dialog.text = "Supongo que sí, ¿eh? Y ahora, adiós, Jerry.";
			link.l1 = "...";
			link.l1.go = "Djerry_12";
			CharacterTurnByChr(npchar, CharacterFromID("WildRose_Naemnik_Rab_mushketer"));
		break;
		
		case "Djerry_12":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_9");
		break;
		
		case "Mary_11":
			dialog.text = "...";
			link.l1 = ""+npchar.name+", ¿estás preocupada por algo? Te despediste de tu tocayo con demasiada prisa, sí, ¿eh?";
			link.l1.go = "Mary_12";
		break;
		
		case "Mary_12":
			dialog.text = "Solo quería librarme cuanto antes de la compañía de ese hombre... Su historia está llena de mentiras, sí, ¿eh?";
			link.l1 = "¿De qué hablas, querida?";
			link.l1.go = "Mary_13";
		break;
		
		case "Mary_13":
			dialog.text = "Después de lo que escuché de boca de ese lacayo de Bishop, no me queda duda de que esos pobres desgraciados murieron precisamente por su culpa. Pero antes de eso... Casper, ¿tú escuchaste con atención lo que él decía?";
			link.l1 = "¿Y qué es lo que no te gustó, cariño?";
			link.l1.go = "Mary_14";
		break;
		
		case "Mary_14":
			dialog.text = "Asegura que hay un bote escondido en la playa. Pero de la plantación escaparon más de veinte personas. Así que el bote debe de ser bastante grande, ¿verdad? Jerry es un desertor de la marina, no puede no entender que manejar una embarcación grande él solo le va a resultar complicado, sí, ¿eh?...";
			link.l1 = "Solo tendrá que izar la vela y tomar rumbo, lo demás lo hará el viento. Sí, ¿eh? Se está jugando la vida, pero supongo que morir en el mar de verdad es mejor que caer en manos de un verdugo plantador.";
			link.l1.go = "Mary_15";
		break;
		
		case "Mary_15":
			dialog.text = "Vale. Pero ahora me he dado cuenta de que hay algo más que tampoco encaja... Según él, él y sus amigos observaron desde lejos cómo los mercenarios abusaban de esa pobre desgraciada...";
			link.l1 = "En vez de salir corriendo hacia mi bote... Sí, ya veo a dónde quieres llegar, "+npchar.name+". Quizá valga la pena hacerle un par de preguntas más al señor Casper...";
			link.l1.go = "Mary_15_add";
		break;
		case "Mary_15_add":
			StartInstantDialog("WildRose_Naemnik_Rab_mushketer", "Mary_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Mary_16":
			dialog.text = "...";
			link.l1 = " Eh, "+npchar.name+", ¡amigo! Espera un momento...";
			link.l1.go = "Mary_17";
		break;
		
		case "Mary_17":
			dialog.text = "...";
			link.l1 = " ¡Maldición! ¡Mary, cuidado!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_11");
		break;
		
		case "Mary_21":
			dialog.text = "¡Maldito canalla!   ¡Le salvamos la vida, y él!   ¿Qué se supone que significa esto, "+pchar.name+"¿Entonces...";
			link.l1 = "Sí, "+npchar.name+", ya no queda vivo nadie que supiera la verdad de lo que ocurrió...";
			link.l1.go = "Mary_22";
		break;
		
		case "Mary_22":
			dialog.text = "Deberíamos largarnos de aquí, "+pchar.name+". Si los soldados nos encuentran aquí, lo vamos a pasar mal, sí, ¿eh?";
			link.l1 = "Tienes razón, Mary. Vamos...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_EscapeSlaves_15");
		break;
		
		case "Mary_23":
			dialog.text = "Sabes, "+pchar.name+", después de todo esto, me gustaría tomarme un buen trago, sí, ¿eh?";
			link.l1 = "No voy a protestar, querida. Yo mismo tengo ganas de mojarme la garganta. Vamos a pasar por el 'Cornudo Irlandés'.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_2");
		break;
		
		case "Barmen_1":
			dialog.text = "Perdone que le haya despertado, capitán...";
			if (sti(pchar.reputation.nobility) >= 40)
			{
				link.l1 = "Llamaste a la puerta, y gracias por eso. Ahora dime, ¿qué es lo que quieres de mí?";
				link.l1.go = "Barmen_2";
			}
			else
			{
				link.l1 = "Bien que hayas tenido la decencia de llamar, amigo. Si hubieras entrado sin más, ya estarías rodando por las escaleras\n¿Qué miras? Anda, suelta para qué has traído aquí tu pellejo.";
				link.l1.go = "Barmen_2";
			}
		break;
		
		case "Barmen_2":
			dialog.text = "Uno de los habitantes quiere verte: Lewis Garnon. Dice que tiene una conversación importante contigo.";
			link.l1 = "Es la primera vez que oigo ese nombre. Espero que de verdad tenga algo importante, para interrumpirme así de... mis asuntos. Que pase...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_5");
		break;
		
		case "Lewis_1":
			dialog.text = "Hola, señor "+pchar.lastname+". Señorita... Casper.";
			link.l1 = ""+TimeGreeting()+", señor "+npchar.lastname+". No recuerdo que nos hayamos visto antes. ¿De dónde nos conoce?";
			link.l1.go = "Lewis_2";
		break;
		
		case "Lewis_2":
			dialog.text = "¿No lo recuerda? Ah, entiendo... Mi cara estaba manchada de sangre y polvo, yo mismo me asusté cuando hace unas horas me vi en el espejo...";
			link.l1 = "...";
			link.l1.go = "Lewis_2_add";
		break;
		case "Lewis_2_add":
			StartInstantDialog("Mary", "Lewis_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_3":
			dialog.text = "Tú... tú eres ese hombre, sí, ¿eh? Te encontramos y...";
			link.l1 = "...";
			link.l1.go = "Lewis_3_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_3_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_4":
			dialog.text = "Y a mi Susan. A mi pobre Suzy...";
			link.l1 = "...";
			link.l1.go = "Lewis_4_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_4_add":
			StartInstantDialog("Mary", "Lewis_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_5":
			dialog.text = "Pensábamos que habías muerto. Igual que... Ella era tu esposa, sí, ¿eh?";
			link.l1 = "...";
			link.l1.go = "Lewis_5_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_5_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_6", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_6":
			dialog.text = "Sí, señora. Ella era mi esposa, y yo me quedé paralizado de miedo... y no pude hacer nada. Dios mío, Dios mío...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_8");
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		
		case "Lewis_7":
			dialog.text = "(llora) Me golpearon y me obligaron a mirar...";
			link.l1 = "Levántate, "+GetAddress_Form(NPChar)+". Usted no tiene la culpa de nada. Nadie habría resistido solo contra tantos canallas.";
			link.l1.go = "Lewis_8";
		break;
		
		case "Lewis_8":
			dialog.text = "Eran tantos, tantos... Pero aún así yo...";
			link.l1 = "Pero al menos usted sobrevivió, y los asesinos de su esposa arden en el infierno. Es un consuelo débil, pero al menos es algo, señor "+npchar.lastname+". Sin embargo, quería preguntarte algo...";
			link.l1.go = "Lewis_9";
			LAi_ActorAnimation(npchar, "ground_standup", "WildRose_Etap1_City_8_1", 7);
		break;
		
		case "Lewis_9":
			dialog.text = "Sí, señor "+pchar.lastname+"?";
			link.l1 = "¿Quiénes eran? ¿Mercenarios de Bishop o esclavos fugitivos?";
			link.l1.go = "Lewis_10";
		break;
		
		case "Lewis_10":
			dialog.text = "Eso lo hicieron Jerry Casper y los demás fugitivos. Acusaron en vano a Bruce Primer y a su gente.";
			link.l1 = "¿Mercenarios de Bishop?";
			link.l1.go = "Lewis_11";
		break;
		
		case "Lewis_11":
			dialog.text = "Sí. Bruce, claro, era todo un sinvergüenza y hacía mucho trabajo sucio para Bishop, sí, ¿eh? — pero nunca fue un violador.";
			link.l1 = "No me lo ha parecido, la verdad. Pero no voy a discutir con usted, "+npchar.name+". Sin embargo, ya que estaba consciente y lo vio todo, podría haberse levantado y...";
			link.l1.go = "Lewis_12";
		break;
		
		case "Lewis_12":
			dialog.text = "Perdóneme, "+GetAddress_Form(NPChar)+". Puede considerarme un cobarde patético — pero estaba tan asustado que no podía moverme. Cuando esos desgraciados nos bloquearon el paso a Susie y a mí, lo primero que hice fue gritar con todas mis fuerzas, intentando pedir ayuda.";
			link.l1 = "¿Y ellos le pegaron?";
			link.l1.go = "Lewis_13";
		break;
		
		case "Lewis_13":
			dialog.text = "Jerry me dio un culatazo con el mosquete y luego dijo que me cortaría en pedazos, justo delante de Susan. Yo... me da vergüenza admitirlo, pero creo que por un par de segundos hasta perdí el conocimiento del miedo. Y mientras tanto ellos...";
			link.l1 = "Lo entiendo, señor "+npchar.lastname+". No hay nada vergonzoso en su comportamiento. No cualquiera podría soportar algo así. Lástima que no interviniera, pero lo hecho, hecho está. Sin embargo, me alegra que al menos hayamos enviado al otro mundo a uno de los asesinos de su esposa, aunque casi logra engañarnos.";
			link.l1.go = "Lewis_14";
			link.l2 = "Así que casi caemos luchando contra los mercenarios de Bishop — sólo porque tenía miedo, ¿eh? Bonita excusa, "+npchar.name+". Menos mal que al menos, aunque tarde, logramos entender la situación...";
			link.l2.go = "Lewis_15";
		break;
		
		case "Lewis_14":
			dialog.text = "Sí, "+GetAddress_Form(NPChar)+". He venido a daros las gracias por esto. Aunque al principio le creísteis...";
			link.l1 = "Bruce Primer se esforzó bastante para lograrlo. Debería tener más cuidado con lo que dice...";
			link.l1.go = "Lewis_16";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Lewis_15":
			dialog.text = "Sí, "+GetAddress_Form(NPChar)+". He venido a daros las gracias por esto. Aunque al principio le creísteis...";
			link.l1 = "Bruce Primer se esforzó mucho para lograrlo. Debería tener más cuidado con lo que dice...";
			link.l1.go = "Lewis_16";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "Lewis_16":
			dialog.text = "Por desgracia, todos cometimos errores aquel día... Susan y yo no debimos salir de paseo a Ragged Point, Bruce debió morderse la lengua a tiempo... Y tú no debiste confiar en Jeremy. Pero gracias a la señorita Casper, la justicia fue restaurada.";
			link.l1 = "...";
			link.l1.go = "Lewis_16_add";
		break;
		case "Lewis_16_add":
			StartInstantDialog("Mary", "Lewis_17", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_17":
			sld = CharacterFromID("WildRose_Lewis");
			dialog.text = "Me imagino de qué quiere preguntarme, señor "+sld.lastname+". Pero yo no tengo nada que ver con esa persona.";
			link.l1 = "...";
			link.l1.go = "Lewis_17_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_17_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_18":
			dialog.text = "Lo sé, señorita. Lo entendí en cuanto entré en esta habitación. Usted y él no tienen ni el más mínimo parecido. Y aun así, Susan... estaba convencida de que nada en este mundo sucede por casualidad.";
			link.l1 = "...";
			link.l1.go = "Lewis_18_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_18_add":
			StartInstantDialog("Mary", "Lewis_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_19":
			dialog.text = "Tu esposa tenía razón. Yo misma lo he comprobado muchas veces, sí, ¿eh? Y "+pchar.name+" también.";
			link.l1 = "...";
			link.l1.go = "Lewis_19_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Lewis"));
		break;
		case "Lewis_19_add":
			StartInstantDialog("WildRose_Lewis", "Lewis_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Lewis_20":
			dialog.text = "...";
			link.l1 = "Correcto. Sin embargo, no creo que ahora sea momento para conversaciones filosóficas. Difícilmente eso les ayudará, "+npchar.name+". Solo el tiempo puede ayudar a sobrellevar algo así.";
			link.l1.go = "Lewis_21";
			CharacterTurnByChr(CharacterFromID("WildRose_Lewis"), pchar);
			CharacterTurnByChr(CharacterFromID("Mary"), pchar);
		break;
		
		case "Lewis_21":
			dialog.text = "Supongo que tiene razón, señor "+pchar.lastname+". Bueno, gracias de nuevo y adiós. Rezaré por usted y por la señorita Casper.";
			link.l1 = "Que te vaya bien, "+npchar.name+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_City_10");
		break;
		
		case "Mary_31":
			dialog.text = ""+pchar.name+"...";
			link.l1 = "Lo sé, cariño, casi dejo escapar a ese bastardo...";
			link.l1.go = "Mary_32";
		break;
		
		case "Mary_32":
			dialog.text = "Al bastardo llamado Jerry Casper.";
			link.l1 = "Es cierto... Espera... ¿acaso piensas que él...";
			link.l1.go = "Mary_33";
		break;
		
		case "Mary_33":
			dialog.text = "Lo sé, es muy tonto...";
			link.l1 = "¡Y tanto! ¿Y si te apellidaras Smith o Jones? De esos hay a montones por las calles, sí, ¿eh? Y seguro que alguno de ellos anda haciendo maldades... Y ese Jerry, que arda en el fuego del infierno, sí, ¿eh? Igual ni siquiera es ningún Casper...";
			link.l1.go = "Mary_34";
			link.l2 = "Así es, querida. Ese maldito Jerry bien podría haberse hecho llamar con otro apellido, y ya está.";
			link.l2.go = "Mary_35";
		break;
		
		case "Mary_34":
			dialog.text = "Y aun así... Sé que no me entiendes, pero solo imagina qué pensarías tú si él tuviera tu apellido "+pchar.lastname+".";
			link.l1 = "No es lo mismo, Mary. "+pchar.lastname+" - apellido noble, ¿eh?...";
			link.l1.go = "Mary_36";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Mary_35":
			dialog.text = "Y aún así... Sé que no me entiendes, pero solo imagina qué pensarías tú si él tuviera tu apellido "+pchar.lastname+".";
			link.l1 = "No es lo mismo, Mary. "+pchar.lastname+" - un apellido noble, ¿eh?...";
			link.l1.go = "Mary_36";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Mary_36":
			dialog.text = "¿Y los Casper qué? Gente sin linaje, sin familia, sí, ¿eh? Supongo que debería dar gracias al Señor cada día porque te has fijado en mí, y no en alguna presumida...";
			link.l1 = ""+npchar.name+", yo no quise decir eso en absoluto, sí, ¿eh? Los miembros de una familia noble están unidos por lazos de sangre, y eso no es lo mismo que simplemente compartir un apellido con alguien. Además, como ya he dicho, ese alguien podría haberse apropiado de ese apellido...";
			link.l1.go = "Mary_37";
		break;
		
		case "Mary_37":
			dialog.text = "No se trata solo de eso, "+pchar.name+"...";
			link.l1 = "Cariño, hemos tenido un día largo y difícil. Hemos recorrido más de una milla por la selva, pudimos haber muerto... y luego ni siquiera nos dejaron dormir bien. No es de extrañar que se te hayan metido en la cabeza pensamientos raros. Los dos solo necesitamos dormir bien, sí, ¿eh?";
			link.l1.go = "Mary_38";
		break;
		
		case "Mary_38":
			dialog.text = "No creo que sea raro en absoluto, pero bueno... hablemos mañana.";
			link.l1 = "Con la cabeza despejada, resolveremos todo más rápido. Acuéstate, querida, tenemos que dejar este día atrás.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_1");
		break;
		
		case "Waitress_1":
			dialog.text = "¿Está todo bien contigo, "+GetAddress_Form(NPChar)+"¿Tiene una cara extraña, como si hubiera visto un fantasma. ¿Quizá le apetece un poco de ron? ¿O vino? Tenemos una excelente selección, no le vendría mal relajarse.";
			link.l1 = "A la mierda la bebida. Estoy buscando a una chica...";
			link.l1.go = "Waitress_2";
		break;
		
		case "Waitress_2":
			dialog.text = "Entonces aquí se ha equivocado de sitio, capitán. Esto es una taberna, no un burdel. Salga a la calle y justo enfrente verá...";
			link.l1 = "Escucha, no estoy para bromas. Busco a una chica pelirroja, con un jubón rojo, va armada. Se llama Mary Casper.";
			link.l1.go = "Waitress_3";
		break;
		
		case "Waitress_3":
			dialog.text = "Bueno, si no están para bromas, entonces no tengo nada que decirles. Mi turno empezó hace una hora y no he visto a ninguna pelirroja con una casaca roja por aquí.";
			link.l1 = "Así que se fue por la noche... ¡¿Pero adónde podría haber ido?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_4");
		break;
		
		case "Mary_41":
			dialog.text = "¡Buenos días, amor! Has dormido mucho tiempo...";
			link.l2 = "Vaya que sí lograste preocuparme, sí, ¿eh? "+npchar.name+". No vuelvas a desaparecer así, sin avisar...";
			link.l2.go = "Mary_43";
			DelLandQuestMark(npchar);
		break;
		
		case "Mary_43":
			dialog.text = "No quería despertarte. Y además, tú también a veces desapareces así, sin decir ni una palabra...";
			link.l1 = "¿Y has decidido corresponderme?";
			link.l1.go = "Mary_44";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;
		
		case "Mary_44":
			dialog.text = "La verdad, solo necesitaba estar a solas con mis pensamientos, sí, ¿eh? No quería que te preocuparas.";
			link.l1 = "¿Te preocupa algo?";
			link.l1.go = "Mary_46";
		break;
		
		case "Mary_46":
			dialog.text = "Nuestra conversación de ayer. Sobre los apellidos, los lazos de sangre...";
			link.l1 = "Así que, al final sí te has enfadado conmigo...";
			link.l1.go = "Mary_47";
		break;
		
		case "Mary_47":
			dialog.text = "No, mi amor, no es eso en absoluto. Es solo que de repente me di cuenta de que no sé absolutamente nada sobre mi familia. Mira, tú eres hijo de una familia noble. Los chicos del barco de vez en cuando cuentan algo sobre sus familias. Y yo no tengo nada que contar, nunca conocí a mis padres. Maldita sea, ni siquiera sé dónde nací...";
			link.l1 = "¿No es en la Isla de la Justicia?";
			link.l1.go = "Mary_48";
		break;
		
		case "Mary_48":
			dialog.text = "Eric, el hombre que me crió, siempre lo decía. Pero si es así, ¿por qué ninguno de los habitantes de la Isla jamás habló de mis padres, ni siquiera los mencionó? Una vez le pregunté a Donald Greenspy sobre esto, pero no me dijo nada claro.";
			link.l1 = "O tal vez no quiso hablar.";
			link.l1.go = "Mary_49";
		break;
		
		case "Mary_49":
			dialog.text = "¡Eso! Y yo pensé lo mismo, sí, ¿eh? Sabes, antes vivía mi vida sin preocuparme mucho por esas cosas. Pero ayer, cuando nos topamos con ese desgraciado de Jerry... me pregunté: ¿quién era mi padre? ¿Y mi madre? ¿Por qué nunca me hablaron de ellos, como si no hubieran existido? ¿Y si mi padre era un canalla igual que ese Jerry?";
			link.l1 = "No tiene ninguna importancia, "+npchar.name+". Te criaron otras personas, y lo hicieron dignamente.";
			link.l1.go = "Mary_50";
			link.l1 = "Dudo que sea así. Y no entiendo muy bien qué importancia tiene, considerando que antes, por alguna razón, ni siquiera te lo habías planteado.";
			link.l1.go = "Mary_51";
		break;
		
		case "Mary_50":
			dialog.text = "Pero para mí es importante, "+pchar.name+", sí, ¿eh? Quiero, tengo derecho a saber quiénes fueron mis padres. ¿No estás de acuerdo conmigo, sí, ¿eh?";
			link.l1 = "Por supuesto, estoy de acuerdo, no puede ser de otra manera. Pero si intentamos averiguar algo sobre tu padre y tu madre, solo puede ser en la Isla de la Justicia. Al fin y al cabo, ni siquiera sabes sus nombres, ¿verdad?";
			link.l1.go = "Mary_52";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		
		case "Mary_51":
			dialog.text = "Pero para mí es importante, "+pchar.name+", sí, ¿eh? Quiero, tengo derecho a saber quiénes fueron mis padres. ¿No estás de acuerdo conmigo, sí, ¿eh?";
			link.l1 = "Por supuesto, estoy de acuerdo, no puede ser de otra manera. Pero si intentamos averiguar algo sobre tu padre y tu madre, solo puede ser en la Isla de la Justicia. Al fin y al cabo, ni siquiera sabes sus nombres, ¿verdad?";
			link.l1.go = "Mary_52";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
		break;
		
		case "Mary_52":
			dialog.text = "Así es, cariño. Nunca los mencionaron conmigo, sí, ¿eh?";
			link.l1 = "Así que todavía es pronto para ir a los archivos de las colonias inglesas. Primero tendremos que volver a ese cementerio de barcos e intentar encontrar alguna pista sobre tu linaje allí.";
			link.l1.go = "Mary_53";
		break;
		
		case "Mary_53":
			dialog.text = "Me alegra que me entiendas, "+pchar.name+". Gracias a ti.";
			link.l1 = ""+npchar.name+", de verdad que me sorprendes. Es lo menos que puedo hacer por ti, querida.";
			link.l1.go = "Mary_54";
		break;
		
		case "Mary_54":
			dialog.text = "De alguna manera he vivido casi veinte años sin saber nada de ellos...";
			// dialog.text = "Al fin y al cabo, durante más de veinte años esto no me preocupó en absoluto...";
			link.l1 = "...";
			link.l1.go = "Mary_55";
		break;
		
		case "Mary_55":
			dialog.text = "Así que puedo aguantar un poco más, sí, ¿eh?";
			link.l1 = "Veo que esto es importante y necesario para ti, "+npchar.name+". Así que intentaré no hacerte esperar. Ahora vamos, tenemos que volver al barco. Allí me siento más tranquila por ti, al menos.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap1_Morning_6");
		break;
		
		// ============================================================
		// ================== ЭТАП 2. «ДИТЯ ОСТРОВА» ==================
		// ============================================================
		case "Mary_61":
			dialog.text = "Las costas de mi tierra... ¿Sabes, "+pchar.name+", me parece que, si volviéramos aquí dentro de diez años, todo esto se vería exactamente igual que ahora, sí, ¿eh?";
			link.l1 = "Tal vez, "+npchar.name+", tal vez. Los barcos del anillo interior seguirán a flote, pero la gente aquí ya será otra, sí, ¿eh?";
			link.l1.go = "Mary_62";
			link.l2 = "Dudo mucho que sí, ¿eh? Aquí todo se sostiene ya solo por la palabra de honor. Y por el genio del Mecánico.";
			link.l2.go = "Mary_63";
		break;
		
		case "Mary_62":
			dialog.text = "Y la verdad es que apenas recuerdo a quienes vivían en estos restos de barcos hace diez o quince años. Sólo a las personas más cercanas a mí: Alan, Eric...";
			link.l1 = "Supongo que así debe ser. No se puede recordar todo ni a todos. A mí también se me borran de la memoria nombres y rostros — de los tiempos de París, y ni hablar de Gascuña. Y yo pensaba que eso solo les pasaba a los viejos.";
			link.l1.go = "Mary_64";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Mary_63":
			dialog.text = "Y la verdad es que apenas recuerdo a quienes vivían en estos restos de barcos hace diez o quince años. Sólo a las personas más cercanas a mí: Alan, Eric...";
			link.l1 = "Supongo que así debe ser. No se puede recordar todo ni a todos. A mí también se me borran de la memoria nombres y rostros — de los tiempos de París, y ni hablar de Gascuña. Y yo pensaba que eso sólo les pasaba a los viejos.";
			link.l1.go = "Mary_64";
			AddCharacterExpToSkill(pchar, "Repair", 100);
		break;
		
		case "Mary_64":
			dialog.text = "Pero este lugar... Es como otro mundo, ¿sí, eh? Imagínate, algunos de los que llegaron aquí no hace mucho aseguran que el tiempo aquí pasa casi tres veces más rápido que en Tierra Firme...";
			link.l1 = "Jajaja, ¿entonces cuántos años tienes tú?";
			link.l1.go = "Mary_65";
		break;
		
		case "Mary_65":
			dialog.text = "Lo decía en serio, sí, ¿eh? "+pchar.name+", ¡sí, ¿eh?!";
			link.l1 = "Bueno, ya en serio, es hora de ponerse manos a la obra. ¿Hay entre los narvales alguien mayor que Grinspie, sí, ¿eh?";
			link.l1.go = "Mary_66";
		break;
		
		case "Mary_66":
			dialog.text = "Mmm, no, creo que no. Pero ya te he dicho que no me dijo nada cuando le pregunté sobre eso.";
			link.l1 = "Y aun así, no tengo otras ideas sobre quién podría ayudarnos a entender lo que pasó hace veinte años. Al menos, por ahora. Así que ponemos rumbo a la 'Esmeralda'.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_2");
		break;
		
		case "Schmidt_1":
			dialog.text = "Ah, "+pchar.name+" ¡Y Mary, qué encuentro! Me alegra veros aquí... y vivos, je, je. En el último mes, dos o tres barcos se han estrellado en el anillo exterior: el mar está endemoniadamente agitado últimamente. Sí, ¿eh? Y no intentéis forzar la puerta cerrada, que igual rompéis la cerradura y luego me toca arreglarla. ¿Vais a ver a Donald, verdad?";
			link.l1 = "Y que tengas un buen día, amigo. A él mismo. Pero, por lo que veo la puerta está cerrada, o bien se ha mudado a otro barco, o no quiere ver a viejos amigos.";
			link.l1.go = "Schmidt_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Schmidt_2":
			dialog.text = "Ni lo uno ni lo otro, ja, ja. Grinspie está ahora en el anillo exterior, en unos ejercicios.";
			link.l1 = "¿Ejercicios? ¿De verdad? ¿Acaso se está preparando para una nueva guerra con los rivados?";
			link.l1.go = "Schmidt_3";
		break;
		
		case "Schmidt_3":
			dialog.text = "La verdad es que nunca se detuvo, "+pchar.name+". Últimamente, sí, ¿eh?, hay bastantes menos peleas que antes. Pero aun así, en la taberna de Sancho, cada dos por tres alguien le suelta un puñetazo a otro... y a veces hasta aparece algún cuchillo, sí, ¿eh?";
			link.l1 = "Mm, parece que antes los miembros de los clanes no solían aparecer en la taberna.";
			link.l1.go = "Schmidt_4";
		break;
		
		case "Schmidt_4":
			dialog.text = "Bueno, algunas cosas han cambiado desde que partiste de la Isla. Donald y Eddie logran mantener a la gente a raya. Por ahora. Pero, ¿quién sabe qué pasará mañana? Por eso el viejo Donnie empezó todo esto...";
			link.l1 = "¿Con tanto esfuerzo evité una masacre en la Isla, para que ahora vuelvan a jugar aquí a los soldaditos? ¿Y desde cuándo lleva él rondando el anillo exterior?";
			link.l1.go = "Schmidt_5";
			link.l2 = "Los entrenamientos están bien, pero ¿no pondrán en peligro la ya frágil tregua? ¿Y cuánto tiempo lleva Greenspy entrenando a los chicos?";
			link.l2.go = "Schmidt_6";
		break;
		
		case "Schmidt_5":
			dialog.text = "Hace tres días que se fue. Debe regresar mañana antes del mediodía. ¡Con el entusiasmo con que están limpiando los mosquetes allá, para mañana no les quedará nada con qué disparar! ¡Ja, ja!";
			link.l1 = "...";
			link.l1.go = "Schmidt_5_add";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Schmidt_6":
			dialog.text = "Hace tres días que se fue. Debe regresar mañana antes del mediodía. ¡Con el entusiasmo con que están limpiando los mosquetes allá, para mañana no les quedará nada con qué disparar! ¡Ja, ja!";
			link.l1 = "...";
			link.l1.go = "Schmidt_5_add";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "Schmidt_5_add":
			StartInstantDialog("Mary", "Schmidt_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_7":
			dialog.text = "¿Mi camarote en el 'Ceres Smithy' sigue libre? ¿O ya se ha instalado alguien allí?";
			link.l1 = "...";
			link.l1.go = "Schmidt_7_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
		break;
		case "Schmidt_7_add":
			StartInstantDialog("Schmidt_Clone", "Schmidt_8", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_8":
			dialog.text = "Todo sigue igual que el día en que estuviste allí por última vez. Ni siquiera hemos abierto la puerta. Para serte sincero, tampoco hemos limpiado ni engrasado la cerradura en todo este tiempo. Así que, si hay que forzarla, sólo dilo.";
			link.l1 = "...";
			link.l1.go = "Schmidt_8_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
		break;
		case "Schmidt_8_add":
			StartInstantDialog("Mary", "Schmidt_9", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Schmidt_9":
			dialog.text = "Por supuesto. Gracias, Jürgen.";
			link.l1 = "...";
			link.l1.go = "exit";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Schmidt_Clone"));
			CharacterTurnByChr(CharacterFromID("Schmidt_Clone"), CharacterFromID("Mary"));
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_3");
			
			//доп
		break;
		
		case "Mary_71":
			dialog.text = "Y de verdad, todo sigue igual que antes. Todas las cosas están en su sitio, como si nunca me hubiera ido de aquí... Aquí fue donde nos conocimos por primera vez, "+pchar.name+". ¿Recuerdas?";
			link.l1 = "¡Por supuesto! Les diste tal paliza a esos dos que pensé: ¡a ver si no termino yo en su lugar!";
			link.l1.go = "Mary_72";
			DelLandQuestMark(npchar);
		break;
		
		case "Mary_72":
			dialog.text = "¡Pero si todo fue muy distinto, sí, ¿eh?! ¡Tú literalmente me arrancaste de las garras de la muerte!";
			link.l1 = "Parece que aquel encuentro me lo tenía reservado el destino, sí, ¿eh?";
			link.l1.go = "Mary_73";
		break;
		
		case "Mary_73":
			dialog.text = "¿De verdad lo crees, cariño?";
			link.l1 = "Por supuesto, mi amor. Y desde entonces, cada día le agradezco por haberme llevado directamente al 'Ceres Smithy'.";
			link.l1.go = "Mary_74";
		break;
		
		case "Mary_74":
			dialog.text = ""+pchar.name+"... Dime, ¿qué pensaste cuando me viste por primera vez?";
			link.l1 = "Bueno... Solo recuerdo que, cuando pasó, sentí el corazón a punto de salirse del pecho. Eras tan...";
			link.l1.go = "Mary_75";
		break;
		
		case "Mary_75":
			dialog.text = "¿Cuál?";
			link.l1 = "No te pareces a ninguna de las que he conocido antes. Tu gracia, tu voz... y ese jubón rojo. No tuve ni una sola oportunidad de resistirme a ti. Lo admito, siempre me ha intrigado: ¿por qué precisamente ese? ¿Por qué el jubón rojo y no un vestido, una camisa o un corsé?";
			link.l1.go = "Mary_76";
		break;
		
		case "Mary_76":
			dialog.text = "Lo encontré cuando tenía nueve años, en el anillo exterior. Por aquel entonces me encantaba pasear por allí: explorar todo lo nuevo, encontrar objetos que no había en la isla, sobre todo libros. Me moría de ganas de probármelo, pero entonces lo único que podía era ahogarme en él. Lo escondí donde guardaba todos mis hallazgos: en uno de los nidos de cuervos que sobresalen del agua.";
			link.l1 = "¿Y cuando te vino bien, te acordaste de él?";
			link.l1.go = "Mary_77";
		break;
		
		case "Mary_77":
			dialog.text = "Hace unos años, vagando por el anillo, me topé con un libro sobre un valiente capitán con chaqueta roja. No temía a nada, luchaba contra cientos de enemigos por el amor de su vida y no conocía el miedo. Fue entonces cuando me lo probé por primera vez. Me da confianza...";
			link.l1 = "¡Y un encanto único, querida! Pero ¿sabes qué? Ahora mismo solo quiero una cosa... quitártelo...";
			link.l1.go = "Mary_78";
		break;
		
		case "Mary_78":
			dialog.text = "¿Entonces a qué esperas, mi valiente capitán?";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_5");
		break;
		
		case "Mary_81":
			dialog.text = "Buenos días, querido. Los narvales acaban de regresar a la 'Esmeralda' y la 'San Gabriel', y Donald está con ellos. Lo vi en uno de los botes, sí, ¿eh?";
			link.l1 = "Buenos días, buenos días... La verdad, después de una noche así yo dormiría hasta el mediodía, y tú ya estás en pie, revoloteando.";
			link.l1.go = "Mary_82";
		break;
		
		case "Mary_82":
			dialog.text = "Ayer hablamos del jubón y del nido de cuervos, donde solía esconderlo... Y de repente me invadió una nostalgia tremenda por aquellos tiempos en los que me escondía allí de todos para leer en silencio libros sobre el gran mundo... No pude resistirme y fui hasta allí. Antes podía quedarme horas, pero hoy... simplemente vi el amanecer desde allí. Y entendí: lo que más deseo en el mundo es estar a tu lado.";
			link.l1 = "Y yo contigo, "+npchar.name+". ¿Vamos con Donald? Tendremos de qué hablar con él.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_7");
		break;
		
		case "Grinspy_1":
			dialog.text = ""+pchar.name+", Mary, ¡me alegra verla! Ya me informaron de su visita de ayer. Pensaba pasarme yo mismo por el 'Ceres Smithy', pero se me adelantó, jovencita. Ay, quién tuviera sus años...";
			link.l1 = "Bueno, tú también tienes energía de sobra, como ya vimos. ¿Cómo fueron los entrenamientos?";
			link.l1.go = "Grinspy_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Grinspy_2":
			dialog.text = "Mejor de lo que esperaba. Practicamos el abordaje a los barcos enemigos, el asalto a los camarotes... En fin, trabajamos de lo lindo. Claro, yo apreté bastante a los muchachos, pero sólo les vino bien. Hacía tiempo que no estiraban los huesos, vaya que hacía tiempo, ja, ja.";
			link.l1 = "¿Y entonces, si me permites preguntar, qué te llevó a semejantes hazañas? ¿Te aburriste en la Isla, sí, ¿eh?";
			link.l1.go = "Grinspy_3";
		break;
		
		case "Grinspy_3":
			dialog.text = "Mm, me parece oír descontento en tu voz, "+pchar.name+". Puedo, claro, entender sus razones...";
			link.l1 = "¿De verdad, "+npchar.name+"?";
			link.l1.go = "Grinspy_4";
		break;
		
		case "Grinspy_4":
			dialog.text = "Tuviste que correr bastante por estos cascos podridos de barcos para que no nos matáramos entre nosotros aquí – no lo he olvidado. Nadie lo ha olvidado.";
			link.l1 = "¡Y así es como pagaste por mis esfuerzos! Parece que es cierto lo que dicen: el mundo solo es una carga para un verdadero guerrero.";
			link.l1.go = "Grinspy_5";
			link.l2 = "Y debo decir que confiaba mucho más en tu sensatez que en la de los piratas o los rivados.";
			link.l2.go = "Grinspy_6";
		break;
		
		case "Grinspy_5":
			dialog.text = "Déjame terminar. Sí, conseguimos mantener la paz, pero nuestras diferencias no han desaparecido. Al menos, no con esos infieles de piel oscura. La semana pasada, uno de los narvales fue asesinado en una pelea en la taberna. Pero tampoco nos quedamos de brazos cruzados...";
			link.l1 = "Sí, sí, así es como suele empezar todo.";
			link.l1.go = "Grinspy_7";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Grinspy_6":
			dialog.text = "Déjame terminar. Sí, logramos mantener la paz, pero nuestras diferencias no han desaparecido. Al menos, no con esos infieles de piel oscura. La semana pasada, uno de los narvales fue asesinado en una pelea en la taberna. Pero tampoco nos quedamos de brazos cruzados...";
			link.l1 = "Sí, sí, así es como suele empezar todo, sí, ¿eh?";
			link.l1.go = "Grinspy_7";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Grinspy_7":
			dialog.text = "Te equivocas en dos cosas, "+pchar.name+". Primero, esto no está empezando — está continuando. Si ingenuamente creías que habías puesto fin a todo esto, estás equivocado. Y segundo, no soy un santo para poner la otra mejilla. Los negros se han vuelto a desmandar, y eso no me agrada. A Dexter, por cierto, tampoco, pero se cree un gran político y prefiere mantenerse al margen. Por eso, tras meditarlo un poco, elegí la forma que me pareció más... indolora de mantener una paz frágil.";
			link.l1 = "¿Has decidido asustar a los rivados con tus enseñanzas?";
			link.l1.go = "Grinspy_8";
		break;
		
		case "Grinspy_8":
			dialog.text = "Hace un par de semanas, un galeón inglés con un cargamento militar fue arrastrado hasta el anillo exterior — llevaba de todo... Pero lo más importante eran medio centenar de fusiles nuevos y buena pólvora. Y también botes... ¡La pintura ni siquiera había terminado de secarse en ellos! Los viejos ya estaban hechos polvo, y después de las tormentas, no quedan muchas barcas enteras, te lo digo yo...";
			link.l1 = "¿Y todo eso pasó a ser propiedad de los narvales?";
			link.l1.go = "Grinspy_9";
		break;
		
		case "Grinspy_9":
			dialog.text = "Yo, tal vez, se lo habría contado al Almirante, pero ya que él se cree el más listo, yo tampoco quiero quedar como un tonto. Mi plan, por cierto, funcionó, así que eso.";
			link.l1 = "¿El Negro Eddie te mandó una carta prometiendo que ya no va a apuñalar a tus muchachos?";
			link.l1.go = "Grinspy_10";
		break;
		
		case "Grinspy_10":
			dialog.text = "Eddie el Negro ordenó a sus negros que se calmaran. Temía que en mi ausencia aumentaran sus provocaciones — pero fue todo lo contrario: los rivadeños están quietos y se mantienen alejados tanto de mis hombres como de los civiles, a quienes también solían molestar de vez en cuando. Los negros son lo que son — sólo entienden la fuerza. Eso decía Alan, ¡y que este bote se hunda ahora mismo si estaba equivocado!";
			link.l1 = "¿Y si dentro de un tiempo vuelven a hacer de las suyas, vas a asustarlos descargando una lluvia de plomo sobre la 'Furia' y el 'Protector' con tus nuevos mosquetes, sí, ¿eh?";
			link.l1.go = "Grinspy_11";
		break;
		
		case "Grinspy_11":
			dialog.text = "Es una idea audaz y atrevida, pero no creo que llegue a tanto. Tal vez sólo hagamos ver que planeamos un ataque contra sus barcos — y entonces Leighton se armará de valor y por fin intervendrá. Aunque está algo engreído, sigue siendo un hombre previsor. Ni la destrucción de nuestro clan ni la de los negros le conviene — tres centros de poder más o menos iguales mantienen un mínimo equilibrio. Si uno cae, todo se irá al demonio. Estoy seguro de que lo entiende — pero, por alguna razón, tengo que hacer su trabajo yo.";
			link.l1 = "Quizás pase a verlo mientras estemos aquí, si es que no empieza con sus sermones en respuesta, ja-ja.";
			link.l1.go = "Grinspy_12";
			link.l2 = "Intentaré pasar a verlo cuando tenga ocasión, hablar de este asunto. A lo mejor me escucha, sí, ¿eh?";
			link.l2.go = "Grinspy_13";
		break;
		
		case "Grinspy_12":
			dialog.text = "Si alguien puede convencerlo de mantener a los negros a raya, eres tú, "+pchar.name+". Sin embargo, por sus caras veo que no han venido a charlar sobre política. Digan lo que quieren.";
			link.l1 = "...";
			link.l1.go = "Grinspy_12_add";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		case "Grinspy_12_add":
			StartInstantDialog("Mary", "Grinspy_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_13":
			dialog.text = "Mis padres, Donald.";
			link.l1 = "...";
			link.l1.go = "Grinspy_13_add";
		break;
		case "Grinspy_13_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_14":
			dialog.text = "No entiendo muy bien qué quieres de mí, Mary.";
			link.l1 = "...";
			link.l1.go = "Grinspy_14_add";
		break;
		case "Grinspy_14_add":
			StartInstantDialog("Mary", "Grinspy_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_15":
			dialog.text = "Cuéntame sobre ellos, te lo ruego, sí, ¿eh? ¡Tú los conociste! Ya te había preguntado por ellos antes, pero no quisiste responder a mis preguntas...";
			link.l1 = "...";
			link.l1.go = "Grinspy_15_add";
		break;
		case "Grinspy_15_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_16":
			dialog.text = "¿Y por eso decidiste traer aquí a Charles, ja-ja-ja? ¡Vaya, sí que eres valiente, chica, que me parta un rayo! Si no te hablé de tu padre y tu madre, fue solo porque nunca los conocí, eso es todo.";
			link.l1 = "...";
			link.l1.go = "Grinspy_16_add";
		break;
		case "Grinspy_16_add":
			StartInstantDialog("Mary", "Grinspy_17", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_17":
			dialog.text = "Pero si eres el miembro más mayor de nuestro clan, sí, ¿eh? Has estado aquí desde que tengo memoria...";
			link.l1 = "...";
			link.l1.go = "Grinspy_17_add";
		break;
		case "Grinspy_17_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_18":
			dialog.text = "Aparecí en la Isla hace un poco menos de veinte años, ya después de tu nacimiento. Eras una pequeñita, corriendo y gateando bajo las mesas y los taburetes, sin dejar en paz a Éric Udet... Por supuesto, le pregunté de dónde había salido una criatura tan inquieta, y me respondió que habías nacido en la Isla hacía unos años. No mencionó nada sobre tu padre ni sobre tu madre. Y si lo hizo, o no lo recuerdo, o ya lo he olvidado...";
			link.l1 = "...";
			link.l1.go = "Grinspy_18_add";
		break;
		case "Grinspy_18_add":
			StartInstantDialog("Mary", "Grinspy_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_19":
			dialog.text = "Han pasado tantos años... Lo entiendo, Donald, sí, ¿eh?";
			link.l1 = "...";
			link.l1.go = "Grinspy_19_add";
		break;
		case "Grinspy_19_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_20":
			dialog.text = "Lástima que Éric no esté con nosotros — él conocía este lugar mucho antes que yo. Por cierto, cuando hablaba de tus nuevas andanzas, solía mencionar a Aurélie Bertin. Esa anciana te adoraba, eso sí lo recuerdo bien... Nunca me lo había planteado, pero creo que cuando naciste, ella ya vivía en la Isla. Quizás pueda ayudarte.";
			link.l1 = "...";
			link.l1.go = "Grinspy_20_add";
		break;
		case "Grinspy_20_add":
			StartInstantDialog("Mary", "Grinspy_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_21":
			dialog.text = "Puede ser. Es una buena excusa para visitarla, ni siquiera recuerdo cuándo fue la última vez que pasé por su casa. No estuvo bien, sí, ¿eh?";
			link.l1 = "...";
			link.l1.go = "Grinspy_21_add";
		break;
		case "Grinspy_21_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_22", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_22":
			dialog.text = "No creo que esté enfadada contigo. Pero no la agobies demasiado - he oído que está indispuesta. No vaya a ser que...";
			link.l1 = "...";
			link.l1.go = "Grinspy_22_add";
		break;
		case "Grinspy_22_add":
			StartInstantDialog("Mary", "Grinspy_23", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_23":
			dialog.text = "Cállate, Donald, ¡vas a atraer problemas! Aurélie nos va a sobrevivir a todos, sí, ¿eh?";
			link.l1 = "...";
			link.l1.go = "Grinspy_24";
		break;
		
		case "Grinspy_24":
			dialog.text = "Vamos, "+pchar.name+"!";
			link.l1 = "...";
			link.l1.go = "Grinspy_24_add";
		break;
		case "Grinspy_24_add":
			StartInstantDialogNoType("Grinspy", "Grinspy_25", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Grinspy_25":
			dialog.text = "...";
			link.l1 = "Adiós, "+npchar.name+". Nos vemos pronto.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_9");
		break;
		
		//
		case "Jillian_1":
			dialog.text = "Dios misericordioso, casi se me sale el corazón del pecho. ¿Se puede asustar así a la gente?..";
			link.l1 = "...";
			link.l1.go = "Jillian_1_add";
			DelLandQuestMark(npchar);
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_1_add":
			StartInstantDialog("Mary", "Jillian_2", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_2":
			dialog.text = "¡Jillian! No esperaba verte aquí, sí, ¿eh? ¿Qué haces aquí? ¿Y dónde está Aurélie?";
			link.l1 = "...";
			link.l1.go = "Jillian_2_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_2_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_3":
			dialog.text = "Y hola para ti también, Mary. Y para usted, "+pchar.name+". Aurelie está enferma, ¿no lo sabías? La cuido por encargo del hermano Julian. Él me pasa unas pócimas con las que intento curarla, pero... parece que no le hacen mucho efecto. Ahora está en el camarote, en la popa, durmiendo. La llevé allí para poder limpiar aquí.";
			link.l1 = "...";
			link.l1.go = "Jillian_3_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_3_add":
			StartInstantDialog("Mary", "Jillian_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_4":
			dialog.text = "Nos enteramos recién hoy, sí, ¿eh? Donald nos lo contó. ¿Cómo está ella?";
			link.l1 = "...";
			link.l1.go = "Jillian_4_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_4_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_5":
			dialog.text = "Mal. Se queja de debilidad en el cuerpo, casi no se levanta de la cama. A veces murmura algo ininteligible, alguna tontería... Ya he escuchado tantas historias de tiempos pasados que he perdido la cuenta.";
			link.l1 = "...";
			link.l1.go = "Jillian_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_5_add":
			StartInstantDialog("Mary", "Jillian_6", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_6":
			dialog.text = "Pues, justo por una historia así hemos venido. Espero que no se niegue a hablar con nosotros...";
			link.l1 = "...";
			link.l1.go = "Jillian_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_6_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_7", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_7":
			dialog.text = "¿De verdad es tan necesario, Mary? No creo que debamos molestarla en ese estado.";
			link.l1 = "...";
			link.l1.go = "Jillian_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_7_add":
			StartInstantDialog("Mary", "Jillian_8", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_8":
			dialog.text = "Se trata de mis padres. Aurélie podría haberlos conocido. Para mí es muy importante, Gillian, sí, ¿eh?";
			link.l1 = "...";
			link.l1.go = "Jillian_9";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		
		case "Jillian_9":
			dialog.text = "¿No hay en la isla algún remedio que pueda mejorar su estado?";
			link.l1 = "...";
			link.l1.go = "Jillian_9_add";
		break;
		case "Jillian_9_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_10", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_10":
			dialog.text = "El hermano Julián le prepara infusiones. Pero sólo la alivian por un tiempo. Y aun así, ella se niega a tomarlas, y tengo que obligarla a beberlas casi a la fuerza. A veces temo que pueda atragantarse con ellas — todavía tengo que conseguir que lo trague todo...";
			link.l1 = "...";
			link.l1.go = "Jillian_10_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_10_add":
			StartInstantDialog("Mary", "Jillian_11", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_11":
			dialog.text = "¡Pobre Aurélie! ¿De verdad nadie en la Isla puede ayudarla?";
			link.l1 = "...";
			link.l1.go = "Jillian_11_add";
		break;
		case "Jillian_11_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_12":
			dialog.text = "Ya sabes que aquí no hay ningún médico de verdad.   ¿Y qué podrías hacer tú aquí? La vejez, como bien sabes, no perdona a nadie...";
			link.l1 = "...";
			link.l1.go = "Jillian_12_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		case "Jillian_12_add":
			StartInstantDialog("Mary", "Jillian_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_13":
			dialog.text = ""+pchar.name+", ¿quizá traer a alguien de nuestro barco?";
			link.l1 = "Me temo, "+npchar.name+", aquí no hace falta un cirujano naval, sino un médico experimentado.";
			link.l1.go = "Jillian_14";
		break;
		
		case "Jillian_14":
			dialog.text = "Ahora mismo estoy dispuesta a creer incluso en la magia, si eso ayuda, sí, ¿eh?";
			link.l1 = "¿Hmm... Magia? Quizás debería acudir a Chimiset...";
			link.l1.go = "Jillian_14_add";
		break;
		case "Jillian_14_add":
			StartInstantDialog("LSC_Jillian_clone", "Jillian_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Jillian_15":
			dialog.text = "¿A Chimisetu? ¿Al brujo negro? "+pchar.name+"¿En serio, ustedes?";
			link.l1 = "Como nunca. Sea negro o blanco, es lo último que me importa ahora. No sé quién más podría ayudar a Aurélie. Creo que ustedes tampoco. Así que apártense y ni se les ocurra interponerse en mi camino.";
			link.l1.go = "Jillian_16";
			link.l2 = "Más que eso. A Aurélie no le ayudan ni las medicinas ni las oraciones del hermano Julián. Chimiset es nuestra última esperanza.";
			link.l2.go = "Jillian_17";
		break;
		
		case "Jillian_16":
			dialog.text = "¡No puedo creer lo que oigo! ¡Pero si es... un hereje!";
			link.l1 = "Y esta es una mujer moribunda, que está a punto de olvidar hasta su propio nombre. Sí, ¿eh?, él es un brujo, pero he oído que ellos son capaces de mucho, de muchísimo. Y si logra devolverle la razón, ¿realmente importa ahora a qué fe pertenece?";
			link.l1.go = "Jillian_18";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Jillian_17":
			dialog.text = "¡No puedo creer lo que oigo! ¡Pero si es... un descreído!";
			link.l1 = "Y esta es una mujer moribunda, que está a punto de olvidar hasta su propio nombre. Sí, ¿eh?, él es un brujo, pero he oído que ellos son capaces de mucho, de muchísimo. Y si logra devolverle la razón, ¿realmente importa ahora a qué fe pertenece?";
			link.l1.go = "Jillian_18";
			AddCharacterExpToSkill(pchar, "Repair", 100);
		break;
		
		case "Jillian_18":
			dialog.text = ""+pchar.name+", escúcheme, yo también aprecio mucho a Aurélie... ¡Dios es testigo de que hago todo lo que puedo para aliviar su sufrimiento! Pero, ¿de verdad piensa permitir que ese hereje negro realice su ritual en esta cabina? ¿Y si durante el ritual prende fuego al barco o decide sacrificar a alguien?";
			link.l1 = "No vamos a permitirlo, "+npchar.name+", se lo aseguro.";
			link.l1.go = "Jillian_19";
		break;
		
		case "Jillian_19":
			dialog.text = "Y yo les aseguro a ambos que si alguien se entera de esto... ¿Se imaginan lo que podría pasar aquí? A los demás habitantes no les va a gustar, y a los narvales, mucho menos.";
			link.l1 = "En eso tiene razón. No hay que traer a Chimiseta aquí, sino llevar a Aurélie con él.";
			link.l1.go = "Jillian_20";
		break;
		
		case "Jillian_20":
			dialog.text = "¿No la viste? La vieja apenas se sostiene en pie. Será un milagro si no se cae por la borda.";
			link.l1 = "Bueno, a veces sólo nos queda confiar en un milagro. Sí, ¿eh? Y, Gillian...";
			link.l1.go = "Jillian_21";
		break;
		
		case "Jillian_21":
			dialog.text = "¿Qué más?";
			link.l1 = "Espero que guarde silencio sobre esto. Usted es una mujer inteligente y ha juzgado todo correctamente... Las tensiones en la Isla pueden fácilmente convertirse en un derramamiento de sangre, y nadie quiere eso, ¿verdad?";
			link.l1.go = "Jillian_22";
			link.l2 = "No se lo digas a nadie, ¿entendido? Hemos confiado en ustedes, no nos hagan arrepentirnos de ello. Creo que comprenden que, si nuestro plan deja de ser un secreto, en la Isla empezará una matanza como nunca antes se ha visto.";
			link.l2.go = "Jillian_23";
		break;
		
		case "Jillian_22":
			dialog.text = "Está bien. Pero entonces asegúrense de que nadie vea cómo la llevan al 'Protector'... Si no, me tocará responder preguntas incómodas.";
			link.l1 = "Les ahorraremos la molestia de dar respuestas incómodas. Lo haremos por la noche.";
			link.l1.go = "Jillian_24";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Jillian_23":
			dialog.text = "Bien. Pero entonces asegúrense de que nadie vea cómo la llevan al 'Protector'... Si no, me tocará responder preguntas incómodas.";
			link.l1 = "No lo permitiremos. Lo haremos por la noche.";
			link.l1.go = "Jillian_24";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			AddComplexSelfExpToScill(100, 100, 100, 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -5);
		break;
		
		case "Jillian_24":
			dialog.text = "Vengan después de la medianoche. Ella estará aquí. Y por el amor de Dios, tengan cuidado.";
			link.l1 = "No tienes que preocuparte, "+npchar.name+", seremos sumamente cuidadosos.";
			link.l1.go = "Jillian_25";
		break;
		
		case "Jillian_25":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_10");
		break;
		
		case "Jillian_26":
			if (GetHour() >= 3 && GetHour() <= 24)
			{
				dialog.text = "Ven después de la medianoche. Ella estará aquí...";
				link.l1 = "Bien.";
				link.l1.go = "exit";
				NextDiag.TempNode = "Jillian_26";
			}
			else
			{
				dialog.text = "Aurélie está lista. Pueden llevarla.";
				link.l1 = "Perfecto. Entonces, vamos.";
				link.l1.go = "exit";
				DelLandQuestMark(npchar);
				AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_10_2");
			}
		break;
		
		case "Oreli_1":
			dialog.text = "Chicos, ¿a dónde... a dónde vamos?! ¡Este es el barco de los Rivadós! ¿Dónde está Eric?!";
			link.l1 = "¿Eric se hizo amigo de Eddie Black, no lo sabías?";
			link.l1.go = "Oreli_2";
		break;
		
		case "Oreli_2":
			dialog.text = "¡Pero qué dices, muchacho! Sí, ¿eh? ¡Erik no soporta a los negros ni de lejos!";
			link.l1 = "¡Vaya! Pues vamos a preguntarle, sí, ¿eh?, qué demonios está haciendo aquí entonces.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_11");
		break;
		
		case "Eddy_1":
			dialog.text = "¡Miren quién ha venido a visitarnos! "+GetFullName(pchar)+" ¡En persona! Me alegra saludar a mi hermano blanco, ¡ja, ja! Cuéntame, ¿a qué has venido?";
			link.l1 = "Y hola a ti, "+npchar.name+"Me encantaría pasar solo por una jarra de ron, pero me temo que tengo un asunto urgente contigo, o mejor dicho, con Chimiseto.";
			link.l1.go = "Eddy_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Eddy_2":
			dialog.text = "Te debemos una que no podremos pagar jamás, amigo mío. Haremos todo lo que esté en nuestras manos.";
			link.l1 = "Bueno, si es así. Porque ya no tengo a nadie más en quien confiar, sí, ¿eh?";
			link.l1.go = "Eddy_3";
		break;
		
		case "Eddy_3":
			dialog.text = "¿Con cuál de estas damas necesitas ayuda, "+pchar.name+"?";
			link.l1 = "No sé si hablas en serio o estás bromeando, "+npchar.name+", pero no estoy para bromas. La que necesita ayuda es Aurélie, claro.";
			link.l1.go = "Eddy_3_add";
		break;
		case "Eddy_3_add":
			StartInstantDialog("LSC_Oreli", "Eddy_4", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Eddy_4":
			dialog.text = "¡Eric! ¡ERIC! ¡Asómate, viejo bribón! ¿Qué clase de payasadas son estas? ¡Trae aquí tu flaco trasero ahora mismo!";
			link.l1 = "...";
			link.l1.go = "Eddy_4_add";
		break;
		case "Eddy_4_add":
			StartInstantDialog("Eddy", "Eddy_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Eddy_5":
			dialog.text = "Así que era cierto... Mis hombres me informaron que esa vieja está mal de la cabeza. Ahora veo que decían la verdad. Pero no entiendo del todo qué quieres de los rivadeños...";
			link.l1 = "Déjame hablar con Chimiset y lo entenderás todo...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_12");
		break;
		
		case "Chimset_1":
			dialog.text = "Habla, mi querido amigo. Estoy listo para escucharte con atención.";
			link.l1 = "Seré breve, Chimiset. Aurélie posee la información que Mary y yo necesitamos. Pero debido a su estado, provocado, si entiendo bien, simplemente por la edad, no podemos ni obtener esos datos de ella ni estar seguros de su veracidad. He oído hablar de los milagros que pueden lograr tanto los chamanes indígenas como los africanos — por eso vengo a pedirte ayuda, Chimiset.";
			link.l1.go = "Chimset_2";
			DelLandQuestMark(npchar);
		break;
		
		case "Chimset_2":
			dialog.text = "Te he escuchado, amigo mío. Los chamanes poseen poderes misteriosos y enigmáticos, a menudo incomprensibles y fuera del alcance de los forasteros, incluso de sus propios hermanos de tribu, y mucho menos de los blancos. Algunos lo llaman brujería, otros, milagro. De verdad que somos capaces de mucho, pero nadie puede hacer que un río corra hacia atrás... Ni detenerlo, tampoco.";
			link.l1 = "¿Qué quieres decir, Chimisette?";
			link.l1.go = "Chimset_3";
		break;
		
		case "Chimset_3":
			dialog.text = "Hablo del río del tiempo, amigo mío. O del río de la vida, como prefieras. Verás, tienes toda la razón: la raíz de la enfermedad de esta pobre muchacha está precisamente en sus años, y en nada más.";
			link.l1 = "He oído un poco sobre eso. Sólo sé que no es un problema tan raro.";
			link.l1.go = "Chimset_4";
		break;
		
		case "Chimset_4":
			dialog.text = "Tienes razón. La gente de su edad a menudo se pierde en los valles de los sueños, y a veces en los del horror. Vuelven de allí, solo para marcharse de nuevo, no tanto por su propia voluntad, sino por fuerzas desconocidas que los arrastran. Con el tiempo, la enfermedad se hace más fuerte, y entonces la persona ya no recuerda ni a sí misma ni a sus amigos.";
			link.l1 = "¿Entonces no puedes hacer nada con eso?";
			link.l1.go = "Chimset_5";
		break;
		
		case "Chimset_5":
			dialog.text = "Expulsar la enfermedad, no. Eso está fuera de mi alcance. Pero puedo hacer otra cosa...";
			link.l1 = "¿Qué exactamente?";
			link.l1.go = "Chimset_6";
		break;
		
		case "Chimset_6":
			dialog.text = "En cuanto esta mujer recobre el sentido, haré un ritual rápido para el que ya me habré preparado...";
			link.l1 = "¿Él, si no la detiene, al menos ralentizará el avance de la enfermedad?";
			link.l1.go = "Chimset_7";
		break;
		
		case "Chimset_7":
			dialog.text = "No exactamente. La obligará a reunir todas sus fuerzas vitales para conservar la cordura el mayor tiempo posible.";
			link.l1 = "¿Cuánto tiempo es «lo más posible»?";
			link.l1.go = "Chimset_8";
		break;
		
		case "Chimset_8":
			dialog.text = "Eso no depende del ritual, sino de la persona. Algunos tienen fuerzas para una semana, otros para un mes... He oído hablar de un hombre que vivió en su sano juicio y con la memoria intacta casi más de un año... Y, cuando todos ya pensaban que estaba curado, la enfermedad volvió y se lo llevó esa misma noche.";
			link.l1 = "Para averiguar lo que necesitamos, una hora será suficiente. ¿Cuándo podrás hacer el ritual, Chimiset?";
			link.l1.go = "Chimset_9";
		break;
		
		case "Chimset_9":
			dialog.text = "Me llevaré a la mujer ahora mismo, la llevaré a la bodega — allí hay un santuario preparado... justo para este tipo de cosas. A partir de ahí, todo dependerá de cuándo recupere su estado normal... Pero creo que para la mañana habremos terminado.";
			link.l1 = "Entonces no voy a estorbarte. Y que te ayude... tu Dios, Chimiset.";
			link.l1.go = "Chimset_10";
		break;
		
		case "Chimset_10":
			dialog.text = "¡Gracias! Ayúdame a llevar a la mujer blanca a la bodega.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_13");
		break;
		
		case "Chimset_11":
			dialog.text = "Todo salió bien, hermano blanco. Lo logramos...";
			link.l1 = "...";
			link.l1.go = "Chimset_11_add";
			DelLandQuestMark(npchar);
		break;
		case "Chimset_11_add":
			StartInstantDialog("LSC_Oreli", "Chimset_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Chimset_12":
			dialog.text = "Oh, "+GetFullName(pchar)+"¡ No sabía que tú y Mary habíais vuelto a la Isla! ¡Qué encuentro tan agradable!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_14_1");
		break;
		
		case "Chimset_13":
			dialog.text = "...";
			link.l1 = "¡Chimiset, gracias! Ni siquiera sé cómo agradecerte...";
			link.l1.go = "Chimset_14";
			link.l2 = "Vaya, Chimiset, ¡lo lograste! Bueno, yo no dudaba de ti...";
			link.l2.go = "Chimset_15";
		break;
		
		case "Chimset_14":
			dialog.text = "¡Todos los Rivadós te debemos una eterna gratitud, amigo mío! Las puertas del 'Protector' siempre estarán abiertas para ti.";
			link.l1 = "Espero no tener que molestarlos más... Mary, Aurélie, tenemos que volver al 'Plutón'.";
			link.l1.go = "Chimset_15_add";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Chimset_15":
			dialog.text = "¡Todos los Rivadós te estaremos eternamente en deuda, amigo mío! Las puertas del 'Protector' siempre estarán abiertas para ti.";
			link.l1 = "Espero no tener que molestarlos más... Mary, Aurélie, tenemos que volver al 'Plutón'.";
			link.l1.go = "Chimset_15_add";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;
		case "Chimset_15_add":
			StartInstantDialog("LSC_Oreli", "Chimset_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Chimset_16":
			dialog.text = "Ya ni me acuerdo de cómo salí de mi camarote... Ay, esta vejez: la memoria ya no sirve para nada, sí, ¿eh? ";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_15");
		break;
		
		case "Oreli_11":
			dialog.text = "Bueno, bueno, señorita, ¿y qué se le ha perdido a usted en mi camarote?";
			link.l1 = "...";
			link.l1.go = "Oreli_11_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_11_add":
			StartInstantDialog("LSC_Jillian_clone", "Oreli_12", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_12":
			dialog.text = "Aurélie, yo...";
			link.l1 = "...";
			link.l1.go = "Oreli_12_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_12_add":
			StartInstantDialog("Mary", "Oreli_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_13":
			dialog.text = "Aurélie, le pedí que limpiara aquí mientras no estabas. No tienes por qué agacharte con las rodillas malas...";
			link.l1 = "...";
			link.l1.go = "Oreli_13_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
			
		break;
		case "Oreli_13_add":
			StartInstantDialog("LSC_Jillian_clone", "Oreli_14", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_14":
			dialog.text = "¿Limpiar?! Tú...";
			link.l1 = "Jillian, gracias por tu trabajo. (en susurros) Todo salió bien. Chimiset lo logró.";
			link.l1.go = "Oreli_15";
		break;
		
		case "Oreli_15":
			dialog.text = "No puede ser...";
			link.l1 = "Como ves. Ahora, por favor, déjanos hablar.";
			link.l1.go = "Oreli_15_add";
		break;
		case "Oreli_15_add":
			StartInstantDialog("LSC_Oreli", "Oreli_16", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_16":
			dialog.text = "Bueno, jóvenes, gracias por acompañar a esta vieja. Me temo que pronto dejaré de salir por completo. Mis piernas, mis piernas...";
			link.l1 = "Si me lo permite, "+npchar.name+", nos quedaremos con usted, pero solo un momento. Tenemos un asunto muy importante con usted, Mary y yo, sí, ¿eh?";
			link.l1.go = "Oreli_17";
		break;
		
		case "Oreli_17":
			dialog.text = "Si no tengo que arrastrarme otra vez a otro barco, te ayudaré en lo que pueda. Te escucho.";
			link.l1 = "...";
			link.l1.go = "Oreli_17_add";
		break;
		case "Oreli_17_add":
			StartInstantDialog("Mary", "Oreli_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_18":
			dialog.text = "Aurélie, quiero que me hables de mis padres. Y del día en que nací. Eso ocurrió aquí, en la Isla, ¿verdad? Donald asegura que fue así, pero él ni siquiera estaba aquí en aquel entonces, así que no puede saberlo con certeza. Tú, en cambio, llevas viviendo aquí mucho más tiempo que él, ¿no es cierto? ¡Más de veinte años, ¿verdad?!";
			link.l1 = "...";
			link.l1.go = "Oreli_18_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_18_add":
			StartInstantDialog("LSC_Oreli", "Oreli_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_19":
			dialog.text = "Tranquila, tranquila, niña, no hables tan rápido, te lo ruego. Si no, no puedo seguirte el ritmo...";
			link.l1 = "...";
			link.l1.go = "Oreli_19_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_19_add":
			StartInstantDialog("Mary", "Oreli_20", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_20":
			dialog.text = "Entiendo, sí, ¿eh? Bien, vamos otra vez...";
			link.l1 = "...";
			link.l1.go = "Oreli_20_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_20_add":
			StartInstantDialog("LSC_Oreli", "Oreli_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_21":
			dialog.text = "No hace falta, Mary, todavía no estoy tan mal, ja, ja... He escuchado lo que me dijiste. Pero, ya que de verdad llevo más tiempo que nadie en la Isla, espero que trates mi edad con respeto y comprensión...";
			link.l1 = "...";
			link.l1.go = "Oreli_21_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_21_add":
			StartInstantDialog("Mary", "Oreli_22", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_22":
			dialog.text = "¡Por supuesto, Aurélie! ¿Cómo pudiste pensar otra cosa?";
			link.l1 = "...";
			link.l1.go = "Oreli_22_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_22_add":
			StartInstantDialog("LSC_Oreli", "Oreli_23", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_23":
			dialog.text = "Ah, veo a la juventud de hoy y... no, no, nosotros no nos comportábamos así con los mayores. Pero eso no va por ti, claro. Solo quería decir que nos será más fácil si respondo a tus preguntas una por una, y no todas de golpe...";
			link.l1 = "...";
			link.l1.go = "Oreli_23_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_23_add":
			StartInstantDialog("Mary", "Oreli_24", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_24":
			dialog.text = "Lo entiendo, Aurélie. Como prefieras, sí, ¿eh? Entonces, ¿estuviste en la Isla cuando nací? Si es que fue aquí, claro...";
			link.l1 = "...";
			link.l1.go = "Oreli_24_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_24_add":
			StartInstantDialog("LSC_Oreli", "Oreli_25", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_25":
			dialog.text = "Llegué a la Isla en 1633, a veces todavía sueño con ese día en mis pesadillas. Una tormenta, nuestro 'Reprisal', un fluyt en el que mi esposo y yo navegábamos hacia la Florida, se sacudía sobre las olas, a punto de volcarse quilla arriba, y nosotros recordábamos todas las oraciones que sabíamos y hasta inventábamos nuevas... Y luego, un crujido y...";
			link.l1 = "...";
			link.l1.go = "Oreli_25_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_25_add":
			StartInstantDialog("Mary", "Oreli_26", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_26":
			dialog.text = "Así que llegaste aquí cinco años antes de que yo naciera, sí, ¿eh?";
			link.l1 = "...";
			link.l1.go = "Oreli_26_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_26_add":
			StartInstantDialog("LSC_Oreli", "Oreli_27", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_27":
			dialog.text = "Más o menos. En aquel entonces todo era un poco distinto por aquí — el 'San Jerónimo' aún flotaba, y el anillo exterior de barcos era una vez y media, si no el doble, más pequeño... ¡Y eso que aún no todos los barcos se han hundido! Les diré algo, jóvenes: si miran al fondo en un día claro, se van a espantar al ver cuántos cascos de barcos hay allá abajo...";
			link.l1 = "...";
			link.l1.go = "Oreli_27_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_27_add":
			StartInstantDialog("Mary", "Oreli_28", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_28":
			dialog.text = "Nos interesa el barco en el que llegaron aquí mis padres. Conmigo... o sin mí?";
			link.l1 = "...";
			link.l1.go = "Oreli_28_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_28_add":
			StartInstantDialog("LSC_Oreli", "Oreli_29", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_29":
			dialog.text = "Contigo, chica, contigo.";
			link.l1 = "...";
			link.l1.go = "Oreli_29_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_29_add":
			StartInstantDialog("Mary", "Oreli_30", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_30":
			dialog.text = "¿Entonces, al final nací en Tierra Firme?";
			link.l1 = "...";
			link.l1.go = "Oreli_30_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_30_add":
			StartInstantDialog("LSC_Oreli", "Oreli_31", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_31":
			dialog.text = "No, me refería a 'contigo' en otro sentido. Estabas en el vientre de tu madre y naciste una semana después.";
			link.l1 = "¿Le parece gracioso, Aurélie?";
			link.l1.go = "Oreli_32";
			link.l2 = "Y con los años no ha perdido el sentido del humor, Aurélie.";
			link.l2.go = "Oreli_33";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "Oreli_32":
			dialog.text = "Bueno, me río de mí misma mucho más seguido que de los demás. Perdona, Mary, no quería ofenderte.";
			link.l1 = "...";
			link.l1.go = "Oreli_33_add";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		
		case "Oreli_33":
			dialog.text = "Bueno, me río de mí misma mucho más seguido que de los demás. Perdóname, Mary, no quería ofenderte.";
			link.l1 = "...";
			link.l1.go = "Oreli_33_add";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		case "Oreli_33_add":
			StartInstantDialog("Mary", "Oreli_34", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_34":
			dialog.text = "Todo está bien, Aurélie. Por favor, sigue, sí, ¿eh? ¿Qué pasó con mis padres después de mi nacimiento?";
			link.l1 = "...";
			link.l1.go = "Oreli_34_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_34_add":
			StartInstantDialog("LSC_Oreli", "Oreli_35", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_35":
			dialog.text = "¿Después? Cariño, ¡que ambos sobrevivieran hasta ese momento ya fue un milagro! ¡Qué tormenta tan terrible rugió aquella noche de junio! Cuando por la mañana el bote trajo a tu madre al anillo interior, pocos creyeron de inmediato lo que veían: que una mujer a punto de dar a luz, que estaba a punto de parir, hubiera sobrevivido a un naufragio tan espantoso. La pobre Teresa, lo recuerdo como si fuera hoy...";
			link.l1 = "...";
			link.l1.go = "Oreli_35_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_35_add":
			StartInstantDialog("Mary", "Oreli_36", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_36":
			dialog.text = "¿Teresa? ¿Así se llamaba?";
			link.l1 = "...";
			link.l1.go = "Oreli_36_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_36_add":
			StartInstantDialog("LSC_Oreli", "Oreli_37", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_37":
			dialog.text = "Sí, así se presentó — y eso fue casi todo lo que dijo. Al final del día cayó en un delirio que duró hasta el mismo momento del parto. Nadie estaba seguro de que pudiera dar a luz, y mucho menos de que el niño naciera con vida — después de todo lo que había pasado. Pero Teresa lo logró. Lo logró... y exhaló su último aliento. Que Dios guarde su alma...";
			link.l1 = "...";
			link.l1.go = "Oreli_37_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_37_add":
			StartInstantDialog("Mary", "Oreli_38", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_38":
			dialog.text = "Mamá murió, ¿y yo me quedé con mi padre? Pero entonces, ¿por qué todos decían que me crió Erik Udett? Y...";
			link.l1 = "...";
			link.l1.go = "Oreli_38_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_38_add":
			StartInstantDialog("LSC_Oreli", "Oreli_39", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_39":
			dialog.text = "Mary, cariño, te lo pedí... No me agobies con tantas preguntas...";
			link.l1 = "...";
			link.l1.go = "Oreli_39_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_39_add":
			StartInstantDialog("Mary", "Oreli_40", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_40":
			dialog.text = "Perdona, Aurélie, me distraje, sí, ¿eh? Mi padre, él también sobrevivió a un naufragio?";
			link.l1 = "...";
			link.l1.go = "Oreli_40_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_40_add":
			StartInstantDialog("LSC_Oreli", "Oreli_41", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_41":
			dialog.text = "Tu padre... Sabes, puedo decir muy poco sobre tu padre — salvo que no le desearía un padre así ni a mi peor enemigo. Unos días después de tu nacimiento, desapareció, dejándote a tu suerte. Tuviste suerte de que Éric tuviera un corazón tan bondadoso y tierno — como un bizcocho empapado en una jarra de grog...";
			link.l1 = "...";
			link.l1.go = "Oreli_41_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_41_add":
			StartInstantDialog("Mary", "Oreli_42", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_42":
			dialog.text = "Dime al menos cómo se llamaba, sí, ¿eh?";
			link.l1 = "...";
			link.l1.go = "Oreli_42_add";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		case "Oreli_42_add":
			StartInstantDialog("LSC_Oreli", "Oreli_43", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "Oreli_43":
			dialog.text = "Oh... ¿Era Jeffrey o John? Que Dios me dé memoria...";
			link.l1 = "¿Así que no lo recuerdas? ¿Verdad, sí, eh? "+npchar.name+"?";
			link.l1.go = "Oreli_44";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Oreli"));
		break;
		
		case "Oreli_44":
			dialog.text = "¿Dudas de mis palabras, joven?!";
			link.l1 = "Silencio, "+npchar.name+", tranquilo. No quería ofenderte. Simplemente me pareció que recuerdas bastante bien aquellos días, eso es todo.";
			link.l1.go = "Oreli_45";
			link.l2 = "No dudo de nada, "+npchar.name+". Simplemente intento recordar bien todos los detalles, nada más. Pero toda esta confusión complica un poco la tarea.";
			link.l2.go = "Oreli_46";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;
		
		case "Oreli_45":
			dialog.text = "La memoria es una dama caprichosa, "+pchar.name+", bastante selectiva. Más aún, cuando han pasado tantos años. Es difícil olvidar a Teresa: ¡la vi sufrir toda la semana! ¡Ay, cuánto la compadecí!";
			link.l1 = "¿Y su marido, acaso no estaba junto a ella?";
			link.l1.go = "Oreli_47";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;
		
		case "Oreli_46":
			dialog.text = "La memoria es una dama caprichosa, "+pchar.name+", bastante selectiva. Más aún, cuando han pasado tantos años. Es difícil olvidar a Teresa: ¡la vi sufrir toda la semana! ¡Ay, cuánto la compadecí!";
			link.l1 = "¿Y su marido, acaso no estaba junto a ella?";
			link.l1.go = "Oreli_47";
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Oreli_47":
			dialog.text = "Muy rara vez. Casi toda la semana desaparecía por ahí, buscando medicinas y pociones, que entonces escaseaban mucho en la Isla...";
			link.l1 = "Así que era un buen marido, si intentó ayudar a su esposa.";
			link.l1.go = "Oreli_48";
		break;
		
		case "Oreli_48":
			dialog.text = "Puede que fuera un buen marido. No he dicho lo contrario, permítame señalarlo. ¡No intente confundirme, joven!";
			link.l1 = "Ni en sueños se me pasó por la cabeza, te lo aseguro, "+npchar.name+". Simplemente es obvio que no tiene la mejor opinión sobre él. Y el hecho de que ni siquiera recuerde su nombre...";
			link.l1.go = "Oreli_49";
		break;
		
		case "Oreli_49":
			dialog.text = "He visto a ese hombre casi de pasada, en la oscuridad del camarote del 'Ceres Smitty', allí donde ahora vive el señor Jürgen. Solo venía de noche, y su rostro lo recuerdo muy vagamente. En cuanto a su nombre, nadie lo llamaba por su nombre, solo por su apellido. Que si Casper esto, Casper lo otro...";
			link.l1 = "Lo entiendo, "+npchar.name+". Así que Mary nació, y a los pocos días él desapareció sin dejar rastro. ¿Lo mataron?";
			link.l1.go = "Oreli_50";
		break;
		
		case "Oreli_50":
			dialog.text = "Pregunta difícil, joven. Verá, en este lugar es bastante complicado guardar un secreto — todos están siempre a la vista de todos. Cuando hay una disputa, incluso dentro de los barcos, al día siguiente ya lo sabe toda la Isla.";
			link.l1 = "No me sorprende.";
			link.l1.go = "Oreli_51";
		break;
		
		case "Oreli_51":
			dialog.text = "No siempre se encuentran los cuerpos de los asesinados — los comerciantes experimentados los hunden atándoles cadenas de bolas o fijándoles cañones o piedras a brazos y piernas. Los cangrejos en el fondo terminan el trabajo. Sin embargo, las pertenencias de los muertos, tarde o temprano, vuelven a salir a flote.";
			link.l1 = "¿¡¿Desde el fondo?!?";
			link.l1.go = "Oreli_52";
		break;
		
		case "Oreli_52":
			dialog.text = "¡Por supuesto que no! Quise decir que a veces llaman la atención — un anillo, una pistola con nombre, un sable de premio... Rara vez preguntan sobre eso. Al fin y al cabo, a la persona ya no la devuelves, y los conflictos de más no le sirven a nadie.";
			link.l1 = "¿Jeffrey o John Casper tenían alguna cosa que los distinguiera?";
			link.l1.go = "Oreli_53";
		break;
		
		case "Oreli_53":
			dialog.text = ""+pchar.name+", ¡Dios mío, ni siquiera puedo recordar su nombre, y tú me haces esas preguntas! Si algo pasó, no oí que esa cosa estuviera en manos de otro habitante de la Isla. Por entonces yo trabajaba de camarera en la taberna, y casi ningún rumor se me escapaba. Pero eso no significa en absoluto que lo supiera todo, ¿eh?";
			link.l1 = "Cuando dicen que la gente desaparece sin dejar rastro, normalmente quieren decir que los han matado. Pero en el caso del señor Casper, está claro que usted no está tan seguro de eso...";
			link.l1.go = "Oreli_54";
		break;
		
		case "Oreli_54":
			dialog.text = "Solo digo que 'desaparecido' no significa necesariamente 'muerto'. Especialmente en aquellos años, cuando entre la Isla y Cuba iban y venían tartanas de contrabandistas y traficantes de cosas robadas... ¿Sabe? No recuerdo sus rasgos, pero su mirada... Era la mirada de un hombre que no se perdería en ningún lado. O al menos, alguien que realmente lo cree.";
			link.l1 = "Tartanas, tartanas... Nada es imposible. Si supiéramos su nombre, podríamos revisar los archivos coloniales de aquellos años. Pero sería mucho más fácil si tuviéramos el tipo y el nombre del barco en el que 'llegó' aquí.";
			link.l1.go = "Oreli_55";
		break;
		
		case "Oreli_55":
			dialog.text = "¿Y qué me miras así, muchacho? ¿Crees que voy a recordarlo?";
			link.l1 = "Eso esperamos, "+npchar.name+" - teniendo en cuenta todo lo que ya nos ha contado.";
			link.l1.go = "Oreli_56";
			link.l2 = "Hum... Tengo serias dudas al respecto.";
			link.l2.go = "Oreli_57";
		break;
		
		case "Oreli_56":
			dialog.text = "¿Quizá también quiere preguntar cuántos cañones llevaba y de qué calibre eran? Mi querido, ¿sabe cuántos barcos se han perdido aquí a lo largo de los años? ¿Y cree que los recuerdo todos? Además, de ese barco apenas sobrevivieron unos pocos - ni un día logró mantenerse a flote, seguro...";
			link.l1 = "Ya veo... Es comprensible, han pasado veinte años. Gracias por no olvidar al menos lo que nos contaron.";
			link.l1.go = "Oreli_58";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;
		
		case "Oreli_57":
			dialog.text = "¿Quizás también quiera saber cuántos cañones llevaba y de qué calibre eran? Querido mío, ¿sabe usted cuántos barcos se han perdido aquí a lo largo de los años? ¿Y de verdad cree que los recuerdo todos? Además, de ese barco sólo se salvaron unos pocos – ni un día logró mantenerse a flote, imagínese...";
			link.l1 = "Está claro... Tiene sentido, han pasado veinte años. Gracias por no haber olvidado al menos lo que nos contaron.";
			link.l1.go = "Oreli_58";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Oreli_58":
			dialog.text = "Espero que no estén bromeando ni intentando burlarse de una anciana cuya memoria se ha vuelto un colador.";
			link.l1 = "De ninguna manera, "+npchar.name+". De verdad nos habéis ayudado muchísimo. Que os recuperéis. Bueno, nosotros nos vamos.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_16");
		break;
		
		case "Mary_91":
			dialog.text = "Así que Teresa... Así se llamaba. Mi pobre madre, sí, ¿eh?...";
			link.l1 = "Bueno, al menos ahora sabemos de quién heredaste tanta fuerza y terquedad. Una mujer embarazada en un barco naufragando... Me da escalofríos solo de imaginarlo, sí, ¿eh?";
			link.l1.go = "Mary_92";
		break;
		
		case "Mary_92":
			dialog.text = "Pero ¿qué hacía ella en ese estado en este barco, "+pchar.name+"¡¿Hay que estar loca para atreverse a algo así?!";
			link.l1 = "Solo tu padre puede responder a esa pregunta: John, Jack, Jacob, Jasper, Jordan...";
			link.l1.go = "Mary_94";
		break;
		
		case "Mary_94":
			dialog.text = "¿Has decidido recordar todos los nombres ingleses que empiezan por «J»? Aurélie solo mencionó a Jeffrey y John, sí, ¿eh?";
			link.l1 = "Quizá simplemente no recordó a los demás, como yo. Ya sabes, la edad y todo eso...";
			link.l1.go = "Mary_95";
		break;
		
		case "Mary_95":
			dialog.text = ""+pchar.name+", tú piensas...";
			link.l1 = "No confiaría plenamente en su memoria ahora mismo. Pero incluso si es así, tendremos que consultar no sólo los archivos coloniales, sino los navales del año 1638, lo cual es mucho más complicado: son datos de carácter confidencial, sobre todo si se trata de oficiales. Y dudo mucho que a un simple marinero le hubieran permitido llevar a su esposa a bordo.";
			link.l1.go = "Mary_96";
		break;
		
		case "Mary_96":
			dialog.text = "Por otro lado, encontrar información sobre un oficial es mucho más fácil que sobre un simple marinero.";
			link.l1 = "Si sabes el nombre del barco. O su nombre completo. Y no 'Jeffrey o John o, en el peor de los casos, Jack...'. Eso todavía sería suerte, si el barco fuera militar. Los mercantes con las listas de tripulación lo tienen mucho peor.";
			link.l1.go = "Mary_97";
		break;
		
		case "Mary_97":
			dialog.text = "¿Pero qué vamos a hacer entonces, "+pchar.name+"¿ Hablar con Aurélie otra vez? Ya le sacamos todo lo que podíamos, ¿no te parece?";
			link.l1 = "No con Aurélie. Con Donald.";
			link.l1.go = "Mary_98";
		break;
		
		case "Mary_98":
			dialog.text = "¿Y en qué nos va a ayudar? Él mismo dijo que en 1638 ni siquiera estaba cerca de la Isla de la Justicia, sí, ¿eh?";
			link.l1 = "Pero los otros narvales sí que estuvieron aquí, ¿verdad?";
			link.l1.go = "Mary_99";
		break;
		
		case "Mary_99":
			dialog.text = "No entiendo muy bien a dónde quieres llegar.";
			link.l1 = "Ya verás, querida, ya verás. Hay otro hilo del que podemos tirar. Vamos.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_17");
		break;
		
		case "Grinspy_31":
			dialog.text = "¡Ah, otra vez usted! Bueno, ¿y cómo van sus búsquedas?";
			link.l1 = "Hola, "+npchar.name+". Podría ser mejor: de momento vagamos como si estuviéramos en esta cueva de misterios y enigmas. Pero siento que la salida ya está cerca.";
			link.l1.go = "Grinspy_32";
			link.l2 = "Y hola a ti, "+npchar.name+"Mejor de lo que podría haber imaginado al principio. La situación... no es tan desesperada, sí, ¿eh?";
			link.l2.go = "Grinspy_33";
			DelLandQuestMark(npchar);
		break;
		
		case "Grinspy_32":
			dialog.text = "Me alegra oírlo. De verdad. Pero, otra vez los dos necesitan algo de mí, ¿verdad? ¿Qué han averiguado?";
			link.l1 = "Mary nació aquí, en la Isla, en junio de 1638. Su madre, Teresa, falleció justo después del parto. El padre —alguien de apellido Casper— desapareció como si se lo hubiera tragado la tierra unos días después de que Mary viniera al mundo. No sabemos nada de él, salvo que su nombre empieza por 'J.'. Hay quien piensa que no acabó siendo pasto de los cangrejos en los bajíos locales, sino que abandonó la Isla en una de las tartanas de los contrabandistas...";
			link.l1.go = "Grinspy_34";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;
		
		case "Grinspy_33":
			dialog.text = "Me alegra oírlo. De verdad. Sin embargo, los dos otra vez necesitan algo de mí, ¿verdad? ¿Qué han averiguado?";
			link.l1 = "Mary nació aquí, en la Isla, en junio de 1638. Su madre, Teresa, falleció justo después del parto. El padre, un tal Casper, desapareció sin dejar rastro a los pocos días de que Mary viniera al mundo. No sabemos nada de él, salvo que su nombre empieza por 'J.'. Se cree que no terminó siendo pasto de los cangrejos en los bajíos locales, sino que abandonó la Isla en una de las tartanas de los contrabandistas...";
			link.l1.go = "Grinspy_34";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;
		
		case "Grinspy_34":
			dialog.text = "¿Y dejó a su hija? Qué cosa más rara.";
			link.l1 = "Así es. Pero nadie, salvo ese tal señor J., podrá explicarlo.";
			link.l1.go = "Grinspy_35";
		break;
		
		case "Grinspy_35":
			dialog.text = "¿Y creen que aún está vivo? ¿Por eso lo buscan?";
			link.l1 = "No solo por eso. Queremos saber quién era, cómo vivía. Para Mary eso es muy importante.";
			link.l1.go = "Grinspy_36";
		break;
		
		case "Grinspy_36":
			dialog.text = "Mm, lo entiendo. Y lamento no poder ayudarles realmente en nada...";
			link.l1 = "En realidad, puedes. Dime, los narvales llevan algún tipo de registro de los barcos que se hundieron cerca de la Isla, ¿sí, eh?";
			link.l1.go = "Grinspy_37";
		break;
		
		case "Grinspy_37":
			dialog.text = "No entiendo muy bien a qué te refieres, "+pchar.name+".";
			link.l1 = "Grinspie, Grinspie... No olvides que sigues calentando esa silla sólo gracias a mí. Así que hazme el favor - no pongas a prueba mi paciencia.";
			link.l1.go = "Grinspy_38";
			link.l2 = "Seguro que lo entiendes, Donald. Y en nombre de nuestra amistad no vas a andarte con rodeos.";
			link.l2.go = "Grinspy_39";
		break;
		
		case "Grinspy_38":
			dialog.text = "Mm...";
			link.l1 = "A veces, los barcos llegan hasta el anillo exterior. Algunos se hunden de inmediato, otros logran mantenerse a flote un tiempo: los registran y les quitan todo lo valioso. No sé cómo lo hacen los Rivadós, pero dudo que los Narvales peleen por cada baratija que encuentran a bordo; lo más probable es que echen todo al montón común, luego hacen un inventario de absolutamente todo y solo después reparten el botín.";
			link.l1.go = "Grinspy_40";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
			ChangeCharacterComplexReputation(pchar, "nobility", -2);
		break;
		
		case "Grinspy_39":
			dialog.text = "Mm...";
			link.l1 = "A veces, barcos llegan al anillo exterior. Algunos se hunden enseguida, otros flotan un tiempo: los registran y se llevan todo lo valioso. No sé cómo lo hacen los Rivadós, pero dudo que los narvales peleen por cada baratija encontrada a bordo; lo más probable es que lo echen todo a un fondo común, luego hagan un inventario de todo, y solo después repartan el botín.";
			link.l1.go = "Grinspy_40";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;
		
		case "Grinspy_40":
			dialog.text = "No eres tonto, "+pchar.name+". A diferencia de muchos aquí. Sí, más o menos así es como sucede todo. Personalmente, me repugna toda esta escritura, pero ya se hacía en tiempos de Alan Milrow y de quienes lideraban el clan 'Narval' antes que él. Llevamos estos registros —y más aún: anotamos incluso aquellos barcos a los que llegaron primero los rivados o los piratas. Pero en esos casos, por supuesto, no sabemos quién ni qué había a bordo...";
			link.l1 = "Si los padres de Mary fueron llevados al 'Ceres Smithy' tras el naufragio, eso significa que su barco fue encontrado por los narvales. Y por lo tanto, debe existir un registro al respecto.";
			link.l1.go = "Grinspy_41";
		break;
		
		case "Grinspy_41":
			dialog.text = "Puede que sí. No puedo decirlo con certeza. Y no podré.";
			link.l1 = "Ahora soy yo la que no entiende a qué te refieres, "+npchar.name+".";
			link.l1.go = "Grinspy_42";
		break;
		
		case "Grinspy_42":
			dialog.text = "Registros de los barcos perdidos. Cuando Leighton Dexter se convirtió en Almirante tras la partida de Dodson, nos quitó estos documentos.";
			link.l1 = "¿Simplemente lo tomó y se lo llevó? ¿Y tú no dijiste nada?";
			link.l1.go = "Grinspy_43";
		break;
		
		case "Grinspy_43":
			dialog.text = "Bueno, para empezar, fue bastante cortés. En segundo lugar, prometió devolvérmelos pronto. Y en tercer lugar... ¿para qué demonios necesito yo esos papeles, sí, ¿eh?";
			link.l1 = "No son las notas más inútiles, sí, ¿eh?";
			link.l1.go = "Grinspy_44";
		break;
		
		case "Grinspy_44":
			dialog.text = "Te digo, es solo una tradición, pensada principalmente para que los miembros de nuestro clan no se degüellen entre sí por el botín de los barcos. El barco llegó a la orilla, le quitamos todo lo que pudimos, hicimos un inventario, algo repartimos, algo escondimos en nuestras bodegas - y ya está. ¿Para qué llenar los armarios? Ahora hay un poco más de espacio en ellos - quizás incluso debería agradecerle al Almirante por eso.";
			link.l1 = "Bueno, está claro. Entonces ponemos rumbo a 'San Agustín'. Pero quizá todavía pasemos a verte, "+npchar.name+".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_18");
		break;
		
		case "WildRose_Dexter_1":
            dialog.text = "Ah, "+pchar.name+", pasa, pasa. ¿Vienes a verme por algo en especial, amigo, o solo has venido a saludar?";
            link.l1 = "Esta vez, es por un asunto. Digamos que es algo personal.";
            link.l1.go = "WildRose_Dexter_2";
			DelLandQuestMark(npchar);
        break;

        case "WildRose_Dexter_2":
            dialog.text = "Y lo bastante importante para ti, por lo alterado que pareces, sí, ¿eh?";
            link.l1 = "¿De verdad? Más bien cansado. He tenido que recorrer bastante tus dominios en estos días. Ya me empiezan a doler las articulaciones — y yo, tan ingenuo, pensaba que eso solo les pasaba a viejos como tú.";
            link.l1.go = "WildRose_Dexter_3_1";
            link.l2 = "Me he quedado un poco sin aliento, eso es todo. Verás, no paso todo el tiempo sentado en una silla. Pero a ti, veo que las piernas ya no te sostienen en absoluto, ¡ja-ja-ja!";
            link.l2.go = "WildRose_Dexter_3_2";
        break;

        case "WildRose_Dexter_3_1":
            dialog.text = "¿Y tú qué creías, por qué me quedé pegado a esta silla, je, je? Sabes, la visión del mundo puede cambiar mucho cuando entiendes que la salud no se compra ni con todas las riquezas de esta Isla.";
            link.l1 = "Curioso, justo de eso venía a hablar.";
            link.l1.go = "WildRose_Dexter_4";
			AddCharacterExpToSkill(pchar, "Defence", 100);
        break;
		
		case "WildRose_Dexter_3_2":
            dialog.text = "¿Y tú qué creías, por qué me he pegado el trasero a esta silla, je, je? Sabes, la forma de ver el mundo puede cambiar mucho cuando entiendes que la salud no se compra ni con todas las riquezas de esta Isla.";
            link.l1 = "Curioso, justo de eso venía a hablar.";
            link.l1.go = "WildRose_Dexter_4";
			AddComplexSelfExpToScill(100, 100, 100, 100);
        break;

        case "WildRose_Dexter_4":
            dialog.text = "¿Sobre mi salud?";
            link.l1 = "No, sobre las riquezas de la Isla. Y para ser un poco más precisa, sobre su inventario. Y para ser completamente precisa, sobre los diarios que contienen ese inventario.";
            link.l1.go = "WildRose_Dexter_5";
        break;

        case "WildRose_Dexter_5":
            dialog.text = "Ejem, ejem... "+pchar.name+", no acabo de entender de qué hablas, ¿sí, eh?";
            link.l1 = "No hace mucho, te llevaste de los narvales los registros de los barcos encallados en la Isla...";
            link.l1.go = "WildRose_Dexter_6";
        break;

        case "WildRose_Dexter_6":
            dialog.text = "¿Así que ese tonto de Greenspy decidió enviarte a por ellos? Vaya descarado.";
            link.l1 = "Para nada, "+npchar.name+", Donald no tiene nada que ver con esto. Fui a preguntarle, y él me envió contigo. Pero debo admitir que tu reacción me hizo gracia. ¿No quieres contarme para qué necesitas los registros de los narvales?";
			link.l1.go = "WildRose_Dexter_7";
        break;

        case "WildRose_Dexter_7":
            dialog.text = "¿Por qué no lo cuentas tú? A mí, como habrás notado, los propios barcos me importan un comino. Y las riquezas con las que están llenas sus bodegas, en realidad, tampoco me interesan mucho. Aquí hay suficiente para todos, si no te vuelves codicioso, eso creo yo. Lo que de verdad me interesa es el armamento: mosquetes, sables... cañones, al fin y al cabo. Sí, esos listillos a veces también se los llevan. A los necios de piel oscura no les da la cabeza para eso, pero a los narvales...";
            link.l1 = "¿Y has decidido comprobar hasta qué punto la gente de Greenspy está preparada para una nueva ronda de enfrentamiento?";
            link.l1.go = "WildRose_Dexter_8";
        break;

        case "WildRose_Dexter_8":
           dialog.text = "Y dejar claro que yo y mis muchachos estamos atentos. El mensaje es bastante transparente, pero considerando ese circo que montó Donald con sus ejercicios, no me sorprendería que haya pensado que estoy tras su dinerito.";
			link.l1 = "Bueno, veo que la situación se está desarrollando un poco distinto a lo que esperabas, sí, ¿eh? ¿Y qué hay de los rivados? ¿El Negro Eddie no está dando problemas?";
            link.l1.go = "WildRose_Dexter_9";
        break;

        case "WildRose_Dexter_9":
            dialog.text = "Rivados, Eddie... Asquerosos negros, no es de extrañar que el Tiburón los odiara tanto.";
            link.l1 = "Así que te gusta, sí, ¿eh?";
            link.l1.go = "WildRose_Dexter_10";
        break;

        case "WildRose_Dexter_10":
            dialog.text = "¡Ahí está el problema, que no, maldita sea! Los morenos se callaron y se atrincheraron en sus barcos...";
            link.l1 = "¿Y entonces qué demonios es lo que no te convence, "+npchar.name+"?";
            link.l1.go = "WildRose_Dexter_11";
        break;

        case "WildRose_Dexter_11":
            dialog.text = "Cómo podría explicártelo, "+pchar.name+"... Verás, esto es como el viento en mar abierto. A veces sopla suave, a veces fuerte, y en ocasiones se desata una tormenta. Pero, de una forma u otra, el viento impulsa el barco hacia adelante, y un buen capitán sabe cómo dominarlo.";
            link.l1 = "Una brisa suave siempre es mejor que una tormenta feroz.";
            link.l1.go = "WildRose_Dexter_12";
        break;

        case "WildRose_Dexter_12":
			dialog.text = "Sí. Pero a veces pasa que no hay viento en absoluto. Calma total — y con eso ningún capitán puede hacer un carajo. Sólo te sientas en la popa, miras la superficie del agua y te preguntas qué demonios va a pasar. Con Eddie y su amiguito Chimiset es igual — están tramando algo, lo siento en las tripas, ¡y no es nada bueno, lo juro por el trueno!";
			link.l1 = "Quizás deberías levantar el trasero del sillón e ir a hablar cara a cara con Edward. Mejor aún — júntense los tres, también con Donald, y hablen con franqueza. Es mucho mejor que volver a hundir la Isla en sangre. Pero bueno... volvamos al motivo por el que vine.";
			link.l1.go = "WildRose_Dexter_13";
		break;

		case "WildRose_Dexter_13":
			dialog.text = "Así que te interesan los tesoros de los narvales, ¿verdad? ¿Qué esperas encontrar allí?";
			link.l1 = "Me interesan las listas de barcos hundidos aquí. Específicamente — del año 1638. Verás, estamos tratando de encontrar información sobre los padres de Mary. Con la madre todo está más o menos claro — pero del padre no se puede decir lo mismo. Los datos sobre él son bastante vagos, ni siquiera sabemos su nombre, y lo único a lo que podemos aferrarnos es al nombre del barco que naufragó en el anillo exterior en junio de 1638...";
			link.l1.go = "WildRose_Dexter_14";
		break;

        case "WildRose_Dexter_14":
            dialog.text = "Es una causa noble: yo mismo, en su día, me atormentaba pensando en quién fue mi propio padre. Pero no puedo ayudaros, no está en mis manos.";
            link.l1 = "¿Y por qué, si no es un secreto?";
            link.l1.go = "WildRose_Dexter_15";
        break;

        case "WildRose_Dexter_15":
            dialog.text = "De ti no hay secretos, "+pchar.name+". No se trata de mí, sino de Donald: él solo me entregó los papeles a partir de 1651. Le pregunté qué pasaba con los registros más antiguos, al menos de la década anterior, y me respondió que no había más documentos. Eso es todo lo que él heredó en ese aspecto de Alan Milrow, o al menos eso fue lo que dijo.";
            link.l1 = "No creo que tuviera razones para mentir.";
            link.l1.go = "WildRose_Dexter_16";
        break;

        case "WildRose_Dexter_16":
            dialog.text = "Pienso lo mismo, amigo. Teniendo en cuenta que me entregó los nuevos registros sin hacer ninguna pregunta. Es más, me pareció que incluso estaba, en cierto modo, contento de deshacerse de esa porquería... Quién sabe, quizá Milrow simplemente se libró de los papeles de décadas pasadas... Los quemó, o tal vez...";
            link.l1 = "No, eso no puede ser.";
            link.l1.go = "WildRose_Dexter_16_Add";
        break;

        case "WildRose_Dexter_16_Add":
            StartInstantDialog("Mary", "WildRose_Dexter_17", "Quest\CompanionQuests\WildRose.c");
        break;

        case "WildRose_Dexter_17":
            dialog.text = "No, eso no puede ser. Alan no haría algo así.";
            link.l1 = "¿Por qué estás tan segura de eso, "+npchar.name+"?";
            link.l1.go = "WildRose_Dexter_17_1";
            link.l2 = "Me parecía que él era más de cuchillo y hacha que de toda esa burocracia. Me sorprende que supiera leer, sí, ¿eh?";
            link.l2.go = "WildRose_Dexter_17_2";
        break;

        case "WildRose_Dexter_17_1":
            dialog.text = "Él trataba con mucho cuidado todos los registros relacionados con la Isla. Los consideraba parte de su historia. Y la historia, no sólo de este lugar, era una verdadera pasión para Alan, sí, ¿eh? Estudiaba todos los documentos históricos y libros que tenía a su alcance... A veces me parecía que habría sido mucho mejor erudito que espadachín — incluso una vez se lo dije.";
            link.l1 = "...";
            link.l1.go = "WildRose_Dexter_18";
        break;

        case "WildRose_Dexter_17_2":
			dialog.text = "Él trataba con mucho cuidado todos los registros relacionados con la Isla. Los consideraba parte de su historia. Y la historia, no solo de este lugar, era una verdadera pasión para Alan, ¿sí, eh? Estudiaba todos los documentos históricos y libros que tenía a su alcance... A veces me parecía que habría sido mucho mejor erudito que guerrero; una vez hasta se lo dije.";
			link.l1 = "Quizás realmente debería haber elegido los lentes, el papel y la pluma en lugar del sable y la pistola — quién sabe, tal vez aún estaría caminando sobre las podridas tablas de estos barcos. Pero si Milroe era tan amante de los archivos, ¿dónde están esos registros? Digamos que una hoja pudo mancharla con tinta por accidente — pero eran decenas, si no cientos, ¿verdad?";
			link.l1.go = "WildRose_Dexter_18";
		break;

		case "WildRose_Dexter_18":
			dialog.text = "Solo sé que guardaba ese tipo de documentos con más celo que su propia vida. Tal vez alguien los robó, o tal vez él mismo se los entregó a alguien...";
			link.l1 = "¿Robados? ¿Quién podría estar interesado en datos sobre barcos desmantelados desde la cubierta hasta la quilla? Que los haya entregado — eso es mucho más probable, pero ¿a quién y con qué propósito?";
			link.l1.go = "WildRose_Dexter_19_Add";
		break;

        case "WildRose_Dexter_19_Add":
            StartInstantDialogNoType("Dexter", "WildRose_Dexter_20", "Quest\CompanionQuests\WildRose.c");
        break;

        case "WildRose_Dexter_20":
            dialog.text = "A algún otro aficionado a la historia, ¡ja, ja, ja! Estoy de acuerdo con Charles: no tengo ni idea de quién más podría necesitar esos viejos garabatos.";
            link.l1 = "A alguien, sin embargo, le hicieron falta. Habrá que pensar un poco en eso. Bueno, "+npchar.name+", no te distraemos más. Nos volveremos a ver.";
            link.l1.go = "Exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_19");
        break;
		
		case "WildRose_Betancur_1":
			dialog.text = ""+pchar.name+", me alegro de verte de nuevo. ¿Cómo van las cosas con Mary?";
			link.l1 = "Y nos alegra verte, "+npchar.name+". Ahora, cómo nos irá a nosotros - eso dependerá de ti.";
			link.l1.go = "WildRose_Betancur_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Betancur_2":
			dialog.text = "Un comienzo intrigante para una conversación, debo admitir. Y algo inquietante, considerando la expresión en sus rostros.";
			link.l1 = "No te asustes, "+npchar.name+", porque no tienes la culpa de esto. Simplemente estamos un poco cansados de correr por estos crujientes restos de barcos. Y además, hoy el día está algo bochornoso, ¿no te parece, sí, ¿eh?";
			link.l1.go = "WildRose_Betancur_3_1";
			link.l2 = "Este calor no nos da precisamente fuerzas. Y además, tuvimos que recorrer media Isla buscándote — necesitamos tu ayuda.";
			link.l2.go = "WildRose_Betancur_3_2";
		break;

		case "WildRose_Betancur_3_1":
			dialog.text = "Hum, sí, ¿eh?, una brisa ligera ahora mismo no vendría nada mal. Entonces, ¿qué puedo hacer por vosotros?";
			link.l1 = "Verás, Mary y yo hemos comenzado una investigación para arrojar luz sobre unos hechos ocurridos hace veinte años.";
			link.l1.go = "WildRose_Betancur_4";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "WildRose_Betancur_3_2":
			dialog.text = "Ejem, sí, ¿eh?, una brisa ligera ahora mismo no vendría nada mal. Entonces, ¿qué puedo hacer por ustedes?";
			link.l1 = "Verás, Mary y yo hemos comenzado una investigación para arrojar luz sobre unos hechos ocurridos hace veinte años.";
			link.l1.go = "WildRose_Betancur_4";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Betancur_4":
			dialog.text = "Suena interesante. ¿Y de qué se trata?";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_4_add";
		break;
		
		case "WildRose_Betancur_4_add":
			StartInstantDialog("Mary", "WildRose_Betancur_5", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_5":
			dialog.text = "A mis padres, Antonio. Charles y yo intentamos averiguar quiénes eran. Y qué les pasó. Mi madre murió al darme a luz, eso ya lo descubrimos. Pero con mi padre no es tan sencillo...";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_5_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_6":
			dialog.text = "¿En qué año naciste, recuérdame...?";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_6_add":
			StartInstantDialog("Mary", "WildRose_Betancur_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_7":
			dialog.text = "En 1638. En junio.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_7_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_8":
			dialog.text = "Tenía solo doce años entonces, Mary. No recuerdo muy bien aquellos días. Algunos recuerdos, claro, me vienen ahora a la mente, pero unirlos en un solo cuadro, la verdad, sería un poco complicado. Perdóname, pero dudo que pueda ayudarte...";
			link.l1 = "No necesitamos exactamente eso de ti, Antonio. Aunque, si recuerdas algo de lo que pasó aquel día cuando nació Mary, te lo agradeceremos mucho.";
			link.l1.go = "WildRose_Betancur_9";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;
		
		case "WildRose_Betancur_9":
			dialog.text = "Entonces, ¿en qué puedo ayudarles, "+pchar.name+"?";
			link.l1 = "Me contaste que te interesa la historia. Tanto la mundial, en general, como la de la Isla, en particular.";
			link.l1.go = "WildRose_Betancur_10";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), pchar);
		break;

		case "WildRose_Betancur_10":
			dialog.text = "Es verdad. He leído todo tipo de libros, he estudiado todos los manuscritos que pude conseguir...";
			link.l1 = "Se trata precisamente de los manuscritos. Además de ti, en la Isla solo había una persona tan apasionada por la historia como tú...";
			link.l1.go = "WildRose_Betancur_12";
		break;

		case "WildRose_Betancur_12":
			dialog.text = "Alan Milrow. Sí, ¿eh? Hablamos de eso cuando no estaba ocupado ideando planes para destruir a los Rivadós y, más tarde, a los piratas. Era un tipo listo, con talentos bastante fuera de lo común.";
			link.l1 = "No lo dudo, el chico era de los buenos. Tenía algo que podría ayudarnos. Al mismo tiempo, no tiene ningún valor práctico para nadie en la Isla de la Justicia, salvo para vosotros dos. Los registros de los barcos naufragados cerca de la Isla, que también contienen descripciones de las cargas y riquezas recuperadas, y, tal vez, los nombres de los pasajeros...";
			link.l1.go = "WildRose_Betancur_13";
		break;

		case "WildRose_Betancur_13":
			dialog.text = "Así es.";
			link.l1 = "¿Entonces los viste?";
			link.l1.go = "WildRose_Betancur_14";
		break;

		case "WildRose_Betancur_14":
			dialog.text = "No solo los vi, sino que copiaba la información que contenían en mis propias notas. Durante una de nuestras charlas, él mencionó la existencia de esos diarios, y le pedí que me los prestara para estudiarlos; estoy intentando componer algo así como las Crónicas de la Isla de la Justicia, y esos registros me vinieron muy bien\nA Alan le entusiasmó mi idea de escribir la historia de este lugar. Es cierto que no me dio todos los registros, se quedó con los de la década de 1650, pero en ese momento me bastó con el resto.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_14_add";
		break;
		
		case "WildRose_Betancur_14_add":
			StartInstantDialog("Mary", "WildRose_Betancur_15", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_15":
			dialog.text = "¿Ahí hay registros del año 1638? Por favor, dime que sí, sí, ¿eh?";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_15_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_15_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_16", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_16":
			dialog.text = "Tengo toda una pila de esos diarios, desde el año 1620. Fue entonces, según Alan, cuando empezaron a llevar estos registros. Y sí, el año 1638 también está ahí, Mary.";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_16_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_16_add":
			StartInstantDialog("Mary", "WildRose_Betancur_17", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Betancur_17":
			dialog.text = "¿Nos dejarás revisarlos?";
			link.l1 = "...";
			link.l1.go = "WildRose_Betancur_17_add";
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;
		
		case "WildRose_Betancur_17_add":
			if (PChar.location == "PlutoStoreSmall") StartInstantDialog("LSC_Betancur", "WildRose_Betancur_18", "Quest\CompanionQuests\WildRose.c");
			else StartInstantDialog("LSC_Betancur", "WildRose_Betancur_19", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_18":
			dialog.text = "¡No parece que tenga elección, ja-ja-ja! Un segundo. Están todos aquí, en el cajón de abajo de este armario.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_19_1");
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Betancur"));
		break;

		case "WildRose_Betancur_19":
			dialog.text = "Por favor. Pónganse cómodos, exploren...";
			link.l1 = "Eso es lo que vamos a hacer.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_20");
			AddQuestRecordInfo("WildRose_Records", "1");
			CharacterTurnByChr(CharacterFromID("LSC_Betancur"), pchar);
		break;
		
		case "WildRose_Mary_101":
			dialog.text = "Aquí, "+pchar.name+", ¡mira, sí, ¿eh?! ¡Joshua y Teresa Casper! No puedo creerlo, lo logramos, lo logramos, sí, ¿eh?! Y el nombre del barco es 'Wrangler'! Ahora podemos averiguar todo sobre mi padre: quién era, cómo terminó aquí...";
			link.l1 = "Me temo, "+npchar.name+", vas demasiado deprisa... Puede que no sea tan sencillo como parece. El barco de Su Majestad... Habrá que pensar quién podría ayudarnos a conseguir información de los archivos de la Marina Real...";
			link.l1.go = "WildRose_Mary_102";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Mary_102":
			dialog.text = "¡Vamos a pensar! Pensaremos y conseguiremos, "+pchar.name+"¡ Lo más difícil ya ha pasado, sí, ¿eh?!";
			link.l1 = "Tal vez también tenga sentido hablar con los señores Young y Friddicks. Sin embargo, no recuerdo haber visto a personas con esos nombres en la Isla.";
			link.l1.go = "WildRose_Betancur_20_add";
		break;
		
		case "WildRose_Betancur_20_add":
			StartInstantDialog("LSC_Betancur", "WildRose_Betancur_21", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Betancur_21":
			dialog.text = "Porque aquí no hay ninguno, "+pchar.name+". Estos dos murieron la noche siguiente después de que los salvaran junto con los Casper, sí, ¿eh?";
			link.l1 = "Curioso. Una mujer embarazada vivió una semana más, y dos marineros de la Flota Real murieron de repente...";
			link.l1.go = "WildRose_Betancur_22";
		break;

		case "WildRose_Betancur_22":
			dialog.text = "Eran malos de por sí, según recuerdo. Ahora lo recordé, "+pchar.name+" - yo estaba cerca del 'Ceres Smithy' cuando los subieron a bordo... Sí, yo estaba en la 'Esmeralda', junto con Aurélie Bertin, creo. Y también estaba allí Chimiset, el chamán de esos negros paganos, que vino a la tienda por alguna razón. Al principio me pareció que esos dos marineros ya estaban muertos, pero en realidad murieron solo un día después...";
			link.l1 = "Bueno, no se puede hacer nada. Pero ya hemos averiguado bastante. Gracias por tu ayuda, Antonio.";
			link.l1.go = "WildRose_Betancur_23";
		break;

		case "WildRose_Betancur_23":
			dialog.text = "Yo no tengo nada que ver, "+pchar.name+". Todo esto es gracias a Alan, es su mérito: pocos de esos coraceros habrían podido comprender el verdadero valor de estos documentos. ¡Y es precisamente por documentos como estos que se reconstruye la historia!";
			link.l1 = "Espero que algún día Mary y yo leamos tus Crónicas, amigo. Toma el diario, no lo pierdas. Bueno, nos tenemos que ir. Quizá nos volvamos a ver, compañero.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_21");
		break;
		
		case "WildRose_Betancur_21":
			dialog.text = "Porque aquí no hay ninguno, "+pchar.name+". Estos dos murieron la noche siguiente después de que los salvaran junto con los Casper.";
			link.l1 = "Curioso.   Una mujer embarazada sobrevivió una semana más, y dos marineros de la Flota Real fallecieron de repente...";
			link.l1.go = "WildRose_Betancur_22";
		break;
		
		case "WildRose_Chimiset_21":
			dialog.text = "Me alegra verte de nuevo, amigo mío. ¿A qué has venido?";
			link.l1 = "Con una petición, "+npchar.name+"... Más bien, con una pregunta.";
			link.l1.go = "WildRose_Chimiset_22";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Chimiset_22":
			dialog.text = "Haz tu pregunta. O dime lo que necesitas. Haré todo lo que esté en mis manos para ayudarte.";
			link.l1 = "Bien. ¿Cuánto tiempo llevas viviendo en la Isla?";
			link.l1.go = "WildRose_Chimiset_23";
		break;

		case "WildRose_Chimiset_23":
			dialog.text = "Décadas y décadas, amigo mío. Llegué aquí siendo un niño, aunque ya bastante despierto — a bordo de un barco negrero. Mi historia no difiere mucho de tantas otras que habrás escuchado por aquí. Un vendaval, un naufragio... El galeón inglés en cuyo calabozo estaba encerrado ni siquiera alcanzó el anillo exterior: se partió en dos tras estrellarse contra uno de los arrecifes, arrastrado por una ola.";
			link.l1 = "¿Cómo lograste sobrevivir? Los arrecifes están bastante lejos del anillo exterior, y llegar nadando desde allí entre las olas de la tormenta es, seamos sinceros, una tarea nada sencilla...";
			link.l1.go = "WildRose_Chimiset_24";
		break;

		case "WildRose_Chimiset_24":
			dialog.text = "Los dioses estaban de mi lado aquella noche. Logré liberarme de los grilletes y luego aferrarme a los restos de lo que alguna vez fue un bote. Conmigo estaba un compañero de tribu, Asana; juntos luchamos contra las olas hasta que perdimos el conocimiento por el cansancio.";
			link.l1 = "¿Te arrastró hasta uno de los barcos?";
			link.l1.go = "WildRose_Chimiset_25";
		break;

		case "WildRose_Chimiset_25":
			dialog.text = "Sí, nos metimos en un agujero en la bodega... Y allí volví a perder el conocimiento, de tan débil que estaba. Lo recuperé cuando Asana empezó a gritar — un cangrejo gigante lo estaba despedazando, allí mismo, en el barco al que habíamos sido arrastrados. Y yo lo miraba, sabiendo que sería el siguiente — paralizado por el miedo y la debilidad, no podía moverme.";
			link.l1 = "Podrías haber intentado ayudar a tu amigo. Pero entonces ahora no estaríamos hablando tú y yo. ¿Cómo lograste escapar?";
			link.l1.go = "WildRose_Chimiset_26_1";
			link.l2 = "Tuviste suerte de que no empezara contigo, "+npchar.name+". ¿Cómo lograste salvarte: saltaste de nuevo al agua y nadaste lejos?";
			link.l2.go = "WildRose_Chimiset_26_2";
		break;

		case "WildRose_Chimiset_26_1":
			dialog.text = "Los gritos de Asana fueron oídos por varios rivados que habían salido a buscar botín en las bodegas de los barcos después del último huracán. Rodearon a la bestia y la mataron. Para Asana ya no había salvación, pero yo tuve mucha más suerte. Así fue como acabé aquí. Pero ahora respóndeme tú, amigo mío: ¿por qué querías saber todo esto?";
			link.l1 = "En realidad, "+npchar.name+", yo quería saber no cómo acabaste aquí, sino cuándo ocurrió eso.";
			link.l1.go = "WildRose_Chimiset_27";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "WildRose_Chimiset_26_2":
			dialog.text = "Los gritos de Asana fueron escuchados por varios rivados que habían salido a cazar entre las bodegas de los barcos tras el último huracán. Rodearon a la bestia y la mataron. Para Asana ya no había esperanza, pero yo tuve mucha más suerte. Así fue como terminé aquí. Pero dime ahora tú, amigo mío — ¿por qué querías saber todo esto?";
			link.l1 = "En realidad, "+npchar.name+", no quería saber cómo terminaste aquí, sino cuándo sucedió.";
			link.l1.go = "WildRose_Chimiset_27";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "WildRose_Chimiset_27":
			dialog.text = "Pues, según vuestro calendario era el año 1623, finales del verano... No podría decirlo con más precisión, sí, ¿eh?";
			link.l1 = "Eso ni siquiera es necesario. Entonces, en 1638 ya llevabas quince años en la Isla.";
			link.l1.go = "WildRose_Chimiset_28";
		break;

		case "WildRose_Chimiset_28":
			dialog.text = "Parece que sí, amigo mío.";
			link.l1 = "En junio de aquel año, el huracán arrojó contra el anillo exterior al bergantín 'Wrangler', un barco de la flota de Su Majestad Carlos I, rey de Inglaterra. De toda la tripulación sólo sobrevivieron cuatro personas, entre ellas los padres de Mary: Joshua y Teresa Casper.";
			link.l1.go = "WildRose_Chimiset_29";
		break;

		case "WildRose_Chimiset_29":
			dialog.text = "Sí, lo recuerdo, amigo mío. Vagamente, como si fuera en una niebla, pero lo recuerdo...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_29_add";
		break;
		
		case "WildRose_Chimiset_29_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_30", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_30":
			dialog.text = "¿De verdad lo recuerdas? ¡Cuéntamelo, sí, ¿eh?!";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_30_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_30_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_31", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_31":
			dialog.text = "Puedo contar poco. Cuatro personas: un oficial, su esposa y dos marineros. La mujer estaba embarazada, y quienes los rescataron pensaron que no sobreviviría hasta la mañana, pero resultó ser fuerte como una leona, mientras que esos dos marineros dejaron este mundo en menos de un día... Yo los vi: estaban débiles, pero aún les quedaba bastante fuerza vital...";
			link.l1 = "¿Insinúas que los mataron?";
			link.l1.go = "WildRose_Chimiset_32";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_32":
			dialog.text = "Si así fue, no hubo testigos de ello, ni heridas en sus cuerpos, amigo mío...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_32_add";
		break;
		
		case "WildRose_Chimiset_32_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_33", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_33":
			dialog.text = "¿Dijiste 'oficial', sí, ¿eh?... ¿De verdad mi padre era oficial?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_33_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_33_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_34", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_34":
			dialog.text = "Llevaba un uniforme de oficial; eso es, quizás, lo único que recuerdo cuando intento acordarme de cómo era.";
			link.l1 = "Si era oficial, no podía vestir otra cosa, dudo que su guardarropa fuera muy variado... ¿Quizá recuerdas algún otro detalle, "+npchar.name+"? ¿Señas particulares... Digamos, una cicatriz en la cara o alguna otra marca... ";
			link.l1.go = "WildRose_Chimiset_35";
		break;
		
		case "WildRose_Chimiset_35":
			dialog.text = "No recuerdo nada de eso, amigo mío. Su rostro casi se ha borrado de mi memoria: han pasado ya dos decenas de años... Pero su mirada, esa sí la recuerdo muy bien. Sólo hablé con ese hombre una vez, pero la mirada de sus ojos grises —como los de Mary— no la olvidaré jamás. En ella se mezclaban la desesperación, el miedo de una gacela acorralada, y al mismo tiempo la furia y la determinación dignas de un león...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_35_add";
		break;
		
		case "WildRose_Chimiset_35_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_36", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_36":
			dialog.text = "¿Has hablado con él, sí, ¿eh? ¿De qué?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_36_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_36_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_37", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_37":
			dialog.text = "Eso ocurrió unas horas antes de tu nacimiento. Él vino aquí, al 'Protector', y exigió verme. El jefe de los rivadeños, Mogedi, quedó sorprendido por su atrevimiento — pero aquel hombre despertó mi curiosidad. Cuando estuvo ante mí, cayó de rodillas y me suplicó que salvara a su esposa... Alguien, en el poco tiempo que llevaban aquí, le habló de mí. Acepté ayudarlo, aunque Mogedi se opusiera...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_37_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_37_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_38", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_38":
			dialog.text = "Así que te debo la vida, ¿eh?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_38_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_38_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_39", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_39":
			dialog.text = "No tiene sentido mentir: conseguimos llegar hasta tu madre, pero demasiado tarde; los narvales se negaban a dejarme subir al 'Ceres Smithy'. Tu padre logró... convencerlos, pero a la pobre Teresa la vi sólo en su último aliento. Alcanzó a darte a luz, y si yo hubiera llegado antes, quizá habría podido salvarle la vida, pero...";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_39_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_39_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_40", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_40":
			dialog.text = "Mamá murió, sí, ¿eh?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_40_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_40_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_41", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_41":
			dialog.text = "Por desgracia. Te miró y exhaló su último aliento, pero antes de eso, como si reuniera fuerzas, llamó a un tal Rupert. Gritó su nombre con todas sus fuerzas, como pidiendo ayuda, y murió.";
			link.l1 = "¿Ruperta? ¿No Joshua?";
			link.l1.go = "WildRose_Chimiset_42";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;
		
		case "WildRose_Chimiset_42":
			dialog.text = "Mientras te contaba esto, amigo mío, era como si reviviera ese momento. Nunca lo olvidaré: ni su grito antes de morir, ni su rostro desfigurado por el sufrimiento. Y sí, lo último que salió de sus labios fue precisamente 'Rupert'.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_42_add";
		break;
		
		case "WildRose_Chimiset_42_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_43", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_43":
			dialog.text = "¿Era guapa mi madre? ¿Puedes describirme cómo era, Chimiset?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_43_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_43_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_44", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_44":
			dialog.text = "No tiene sentido, Mary. Solo tienes que mirarte al espejo: tú y ella sois como dos gotas de agua. Solo esa mirada penetrante la heredaste de tu padre.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_44_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_44_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_45", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_45":
			dialog.text = "¿Y él, qué fue de él? Pudimos averiguar que unos días después de mi nacimiento desapareció sin dejar rastro, sí, ¿eh? ¡Pero no lo mataron, ¿verdad?!";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_45_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_45_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_46", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_46":
			dialog.text = "En cuanto le dijeron que Teresa estaba al borde de la muerte, Joshua se enfureció de verdad — te juro que ni los leones en la sabana atacan a su presa con tanta rabia como la que mostró tu padre al lanzarse contra esos narvales que me impedían subir al fluyt... Hicieron falta al menos media docena de hombres para detenerlo — ¡y eso después de que arrojara al agua a dos guerreros del clan con todo su equipo!";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_46_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_46_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_47", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_47":
			dialog.text = "¿Y qué le hicieron - dime, anda!";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_47_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_47_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_48", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_48":
			dialog.text = "Lo arrojaron a una de las celdas en el 'Tartarus'. Nadie se atrevió a juzgarlo: querían que esa historia se calmara primero... Casi todos sentían compasión por él, pero pocos deseaban vivir al lado de una persona así. Joshua desapareció a los pocos días; justo entonces, varias barcazas de contrabandistas partieron de la Isla. Nadie lo vio en los botes, y eso fue lo que dio origen a los rumores sobre su muerte.";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_48_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_48_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_49", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_49":
			dialog.text = "Entonces, ¿crees que está vivo, sí, ¿eh?";
			link.l1 = "...";
			link.l1.go = "WildRose_Chimiset_49_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Chimiset"));
		break;

		case "WildRose_Chimiset_49_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_50", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Chimiset_50":
			dialog.text = "Solo diré lo que seguramente otros ya les dirán: nadie ha encontrado su cuerpo. Tal vez aún esté escondido en el fondo de alguna barca, o quizá le cortaron el cuello en esa celda y se lo dieron de comer a los cangrejos...";
			link.l1 = "El hecho de que desapareciera justo cuando esos comerciantes zarparon apunta más bien a la primera opción — no existen coincidencias así. Y, tal vez, ¿mencionó sus planes a alguien? Si huyó, lo hizo dejando atrás a su hija recién nacida, lo cual, en cierto modo, tiene sentido — una criatura así quizá no habría sobrevivido al viaje hasta las costas de Cuba en una chalupa frágil... Pero estoy seguro de que pensaba regresar por ella.";
			link.l1.go = "WildRose_Chimiset_51";
		break;
		
		case "WildRose_Chimiset_51":
			dialog.text = "No lo sé, amigo mío. Si Joshua Casper habló con alguien en aquellos días, sería solo con sus carceleros, pero todos ellos hace mucho que dejaron este mundo pecador. Ah, sí, un día vino a verlo el padre Domingo: él era el sacerdote de los blancos antes que el hermano Julián...";
			link.l1 = "¿Acaso decidió confesarse? Parece que tenía miedo de morir durante la huida.";
			link.l1.go = "WildRose_Chimiset_52";
		break;

		case "WildRose_Chimiset_52":
			dialog.text = "No puedo arrojar luz sobre lo que no sé, amigo mío. Y tampoco Domingo podrá contarles ya nada – se ahogó hace unos quince años, sí, ¿eh? Que si le dieron un golpe en la cabeza, que si solo se emborrachó – eso sí que le gustaba...";
			link.l1 = "Pero, tal vez Domingo llevaba un diario... o le contó a su hermano Julián sobre esa conversación con Joshua?";
			link.l1.go = "WildRose_Chimiset_52_add";
		break;
		
		case "WildRose_Chimiset_52_add":
			StartInstantDialog("Mary", "WildRose_Chimiset_53", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_53":
			dialog.text = "Hay que hablar con él, "+pchar.name+", sí, ¿eh? Y cuanto antes. No quiero ni pensar en volver al barco hasta que no resolvamos esto.";
			link.l1 = "Si es que queda algo por aclarar. Julián puede que ni lo sepa, pero lo vamos a averiguar, sí, ¿eh? Gracias, Chimiset.";
			link.l1.go = "WildRose_Chimiset_53_add";
		break;
		
		case "WildRose_Chimiset_53_add":
			StartInstantDialogNoType("Chimiset", "WildRose_Chimiset_54", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Chimiset_54":
			dialog.text = "Siempre estoy a tu disposición, amigo mío. Pero permíteme darte un consejo a ambos.";
			link.l1 = "¿Y cuál es?";
			link.l1.go = "WildRose_Chimiset_55";
		break;
		
		case "WildRose_Chimiset_55":
			dialog.text = "Cuando salgáis de caza, no os adentréis demasiado en la maleza: puede que no logréis salir de allí.";
			link.l1 = "Lo recordaremos, chamán. Y ahora, adiós.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_22");
		break;
		
		case "WildRose_Julian_1":
			dialog.text = "Os saludo bajo el amparo de la casa de Dios, hijos míos. ¿Habéis venido a confesaros o solo queréis rezar?";
			link.l1 = "Hola, hermano Julián. Me temo que enumerar nuestros pecados tomaría demasiado tiempo, del cual, por desgracia, carecemos. Pero puede estar seguro de que, como buenos católicos, visitamos la iglesia en cada puerto.";
			link.l1.go = "WildRose_Julian_2_1";
			link.l2 = "Saludos, hermano Julián. Con una oración a nuestro Señor, como buenos católicos, comenzamos el día y con ella también lo terminamos.";
			link.l2.go = "WildRose_Julian_2_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Julian_2_1":
			dialog.text = "Buenos católicos, viviendo bajo el mismo techo sin estar casados... Eso es casi una blasfemia, hijo mío. Y eso, te recuerdo, es un pecado mortal.";
			link.l1 = "¿Y acaso no está escrito en las Escrituras que el amor cubre todos los pecados?";
			link.l1.go = "WildRose_Julian_3";
			ChangeCharacterComplexReputation(pchar, "nobility", 1);
		break;

		case "WildRose_Julian_2_2":
			dialog.text = "Buenos católicos, viviendo bajo el mismo techo sin estar casados... Eso es casi una blasfemia, hijo mío. Y eso, te recuerdo, es un pecado mortal.";
			link.l1 = "¿Y acaso no está escrito en las Escrituras que el amor cubre todos los pecados?";
			link.l1.go = "WildRose_Julian_3";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Julian_3":
			dialog.text = "El amor consiste en que obedezcamos Sus mandamientos, ¿debo recordártelos, hijo mío?";
			link.l1 = "Quizá en otra ocasión. Estamos aquí por otro asunto.";
			link.l1.go = "WildRose_Julian_4";
		break;

		case "WildRose_Julian_4":
			dialog.text = "A las almas perdidas nunca les es tarde para volver al buen camino... Pero os escucho, hijos míos.";
			link.l1 = "De verdad que nos hemos perdido un poco, hermano Julián. En la espesura del pasado. Y esperamos que esté en su poder ayudarnos a encontrar el camino hacia la luz.";
			link.l1.go = "WildRose_Julian_5";
		break;

		case "WildRose_Julian_5":
			dialog.text = "Muy ingenioso, hijo mío. Debes recordar que no es el hombre quien guía hacia la luz, sino el Señor; y, al seguirle, recuerda que inescrutables son Sus caminos.";
			link.l1 = "Seré breve, hermano Julián. Estamos tratando de averiguar todo lo posible sobre los padres de Mary. Con su madre, Teresa, todo está más o menos claro — llegó a la Isla con su esposo y murió una semana después, al dar a luz. Pero el padre... Desapareció unos días después del nacimiento de Mary, escapando del 'Tartarus'. Según los rumores, la última persona con la que habló aquí fue el padre Domingo — su antecesor.";
			link.l1.go = "WildRose_Julian_6";
		break;

		case "WildRose_Julian_6":
			dialog.text = "Entonces han llegado con más de una década y media de retraso, hijos míos.";
			link.l1 = "Sí, sabemos que el padre falleció hace ya bastante tiempo. Y en aquel entonces, hermano Julián, usted era aún demasiado joven para estar en la Isla con el rango correspondiente, ¿verdad?";
			link.l1.go = "WildRose_Julian_7";
		break;

		case "WildRose_Julian_7":
			dialog.text = "Me encontré aquí varios años después de su muerte. Me costó mucho trabajo poner todo en orden aquí, en este barco, pero con la ayuda de Dios lo logré, hijo mío.";
			link.l1 = "Cuando estabas revisando aquí, ¿no encontraste ningún registro del padre Domingo?";
			link.l1.go = "WildRose_Julian_8";
		break;

		case "WildRose_Julian_8":
			dialog.text = "¿Tiene usted algo concreto en mente, hijo mío?";
			link.l1 = "Nos interesan los diarios o algún libro de registro... Hay poca esperanza de un milagro, pero el padre podría haber dejado el contenido de esa conversación en alguna de sus anotaciones. Suponemos que el padre de Mary abandonó la isla en una de las barcazas de los contrabandistas —quizá le insinuó al padre adónde pensaba ir y cuándo volvería por su hija?";
			link.l1.go = "WildRose_Julian_9";
		break;

		case "WildRose_Julian_9":
			dialog.text = "No he encontrado diarios ni nada parecido, eso seguro, pero sí varios apuntes... En cuanto a los asuntos de la iglesia, era bastante meticuloso: no a cada siervo suyo el Señor le da tal pedantería. Pero sus papeles contienen solo cifras secas y nombres, nada más.";
			link.l1 = "Hasta donde pudimos averiguar, Joshua Casper — así se llamaba — en un arrebato de ira provocado por la muerte de su esposa, mató a dos miembros del clan ‘Narval’ que se negaron a dejar pasar al brujo rivados Chimiseta hasta la madre de Mary...";
			link.l1.go = "WildRose_Julian_10";
		break;

		case "WildRose_Julian_10":
			dialog.text = "¡Han actuado como hijos de la verdadera iglesia! ¡A este sirviente del Diablo le esperan los calabozos de la Inquisición!";
			link.l1 = "Dios mío, creo que se horrorizaría si supiera cuánta gente ha sido torturada en Su nombre. Casper tuvo más suerte: lo arrojaron a una celda en el 'Tartarus', pero nunca llegó a ser sentenciado.";
			link.l1.go = "WildRose_Julian_11_1";
			link.l2 = "Sí, sí, sin duda. A Casper la encerraron en una de las celdas del 'Tartarus', pero no hubo sentencia: no todos condenaron el acto de un marido que perdió a su esposa.";
			link.l2.go = "WildRose_Julian_11_2";
		break;

		case "WildRose_Julian_11_1":
			dialog.text = "¿Y qué pasó después, ese hereje escapó?";
			link.l1 = "Menos de una semana después, Joshua desapareció. Y la noche anterior, el padre Domingo fue a visitarlo. Surge la pregunta: ¿para qué? Difícilmente un protestante, que seguramente era Casper, se confesaría con un sacerdote católico, ¿no cree?";
			link.l1.go = "WildRose_Julian_12";
			ChangeCharacterComplexReputation(pchar, "nobility", -1);
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Julian_11_2":
			dialog.text = "¿Y qué pasó después, ese hereje escapó?";
			link.l1 = "Menos de una semana después, Joshua desapareció. Y la noche anterior, fue visitado por el padre Domingo. Surge la pregunta: ¿para qué? Difícilmente un protestante, como seguramente era Casper, se confesaría con un sacerdote católico, ¿no lo creen?";
			link.l1.go = "WildRose_Julian_12";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Julian_12":
			dialog.text = "Nunca es tarde para volver a la verdadera fe, hijo mío. Pero piensas bien. Si no necesitaba confesarse, tal vez hablaba con el padre sobre el funeral de su esposa, si es que ella era católica. O sobre el bautizo de su hija, o mejor dicho, sobre la negativa a bautizarla, ya que los protestantes no bautizan a los bebés, pues creen que la persona debe tomar la decisión del bautismo por sí misma y de manera consciente.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_12_add";
		break;
		
		case "WildRose_Julian_12_add":
			StartInstantDialog("Mary", "WildRose_Julian_13", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Julian_13":
			dialog.text = "Pero estoy bautizada, hermano Julián. Eric Udett me habló de eso.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_13_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_13_add":
			StartInstantDialog("Julian", "WildRose_Julian_14", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_14":
			dialog.text = "Son solo mis conjeturas, hija mía. La verdad me es desconocida. El Señor solo nos abre los ojos a lo que realmente importa y necesitamos.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_14_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_14_add":
			StartInstantDialog("Mary", "WildRose_Julian_15", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_15":
			dialog.text = "Y para mí así es, sí, ¿eh? Quizá en las páginas de los registros del padre Domingo aún quede algo que no notaste, hermano Julián. Porque solo las hojeaste, ¿verdad?";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_15_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_15_add":
			StartInstantDialog("Julian", "WildRose_Julian_16", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_16":
			dialog.text = "No tenía nada que buscar allí, hija mía. Veo que lleváis mucho tiempo y con esmero ocupándoos de este asunto: el Señor os guía por este camino espinoso. Si te está destinado encontrar lo que buscas, esa es Su voluntad, y no me corresponde a mí oponerme a ella. Puedo daros los registros de Domingo del año de tu nacimiento, quizá en ellos encontréis algo útil.";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_16_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;

		case "WildRose_Julian_16_add":
			StartInstantDialog("Mary", "WildRose_Julian_17", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Julian_17":
			dialog.text = "Eso sería muy generoso de su parte, hermano Julián. ¿Se han conservado los registros del año 1638?";
			link.l1 = "...";
			link.l1.go = "WildRose_Julian_17_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("Julian"));
			CharacterTurnByChr(CharacterFromID("Julian"), CharacterFromID("Mary"));
		break;
		
		case "WildRose_Julian_17_add":
			StartInstantDialog("Julian", "WildRose_Julian_18", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Julian_18":
			dialog.text = "Veamos... (sopla el polvo). Parece que es esto. El libro de cuentas del año 1638 después de Cristo.";
			link.l1 = "Permítame, hermano Julián...";
			link.l1.go = "exit";
			AddQuestRecordInfo("WildRose_Records_2", "1");
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_23");
		break;
		
		case "WildRose_Mary_111":
			dialog.text = "Mira, "+pchar.name+": 3 de agosto. Ese día nos bautizaron a Fabián y a mí. Pero nací el 22 de junio. Y sobre mi padre, ni una palabra, sí, ¿eh?";
			link.l1 = "Todo, tal como decía el hermano Julián: cifras secas y nombres. Lo curioso es que el padre Domingo se entregó tanto a su celo, que incluso oficiaba funerales para protestantes; dudo mucho que van Ekkus, Young y Friddicks fueran católicos.";
			link.l1.go = "WildRose_Mary_111_add";
			DelLandQuestMark(npchar);
		break;
		
		case "WildRose_Mary_111_add":
			StartInstantDialog("Julian", "WildRose_Mary_112", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_112":
			dialog.text = "Bien podrían haberse vuelto a la verdadera fe al estar a punto de entrar en el Reino de Dios, hijo mío.";
			link.l1 = "Por supuesto, hermano Julián, ¿a qué más podían dedicarse? Sobre todo si murieron como Sorrén y Rojas; supongo que esos son los mismos narvales que le cerraron el paso a Chimiseto.";
			link.l1.go = "WildRose_Mary_112_add";
		break;
		
		case "WildRose_Mary_112_add":
			StartInstantDialog("Mary", "WildRose_Mary_113", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_113":
			dialog.text = "Ojalá el padre Domingo escribiera los segundos nombres completos, sí, ¿eh? ¿Qué significan esas «V.» y «J.» después de los nombres de mi madre y míos?";
			link.l1 = "¿Y quién es ese Fabián, que fue bautizado contigo el mismo día?";
			link.l1.go = "WildRose_Mary_114";
		break;
		
		case "WildRose_Mary_114":
			dialog.text = "El hijo de Cécile Gallard. ¡Ay, justo ahora lo recordé! Ella me crió, aunque nunca fue especialmente cariñosa conmigo. Seguro que fue porque yo sobreviví y Fabián no. Él murió a los pocos meses de nacer, sí, ¿eh?";
			link.l1 = "Quizá valga la pena hablar con ella, ya que de este librito no hemos sacado casi nada útil, salvo, claro, las fechas de tu nacimiento y bautizo.";
			link.l1.go = "WildRose_Mary_115";
		break;

		case "WildRose_Mary_115":
			dialog.text = "No es mucho más joven que Aurélie, "+pchar.name+". Solo queda esperar que al menos ella tenga la cabeza en su sitio. Pero, ¿qué piensas averiguar de ella?";
			link.l1 = "Bueno, si fue tu nodriza, bien podría haber sabido algo de aquella conversación entre el padre Domingo y Joshua. ¿A quién, sino a ella, podría habérselo contado? Tal vez también a Aurélie o a Éric. Pero me da la impresión de que ya sacamos todo lo posible de la primera, y el segundo ya no podrá decirle nada a nadie.";
			link.l1.go = "WildRose_Mary_115_add";
		break;
		
		case "WildRose_Mary_115_add":
			StartInstantDialog("Julian", "WildRose_Mary_116", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_116":
			dialog.text = "Esta buena mujer es una fiel feligresa de esta casa de Dios. No se pierde ni una sola misa y se confiesa con regularidad. Creo que de verdad puede ayudarles, hijos míos.";
			link.l1 = "Gracias, padre. Adiós.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_24");
		break;
		
		case "WildRose_Sesil_1":
			dialog.text = ""+GetFullName(pchar)+" y Mary Casper. ¡Qué encuentro tan agradable!";
			link.l1 = "Mutuo, "+npchar.name+". En realidad, venimos a usted. Quisiéramos discutir algo con usted.";
			link.l1.go = "WildRose_Sesil_2";
			DelLandQuestMark(npchar);
			LAi_SetStayType(npchar);
		break;
		
		case "WildRose_Sesil_2":
			dialog.text = "¿Ah, sí? Bueno, soy toda oídos.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_2_add";
		break;
		
		case "WildRose_Sesil_2_add":
			StartInstantDialog("Mary", "WildRose_Sesil_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Sesil_3":
			dialog.text = "Esto tiene que ver con mis padres, Cécile. Sobre mi madre, ya averiguamos todo lo posible... Murió justo después de que yo naciera. Pero mi padre... desapareció sin dejar rastro a los pocos días. Tendemos a pensar que no murió, sí, ¿eh?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_3_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_3_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_4", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_4":
			dialog.text = "Vaya, para mandar al otro mundo a alguien como él, había que esforzarse, sí, ¿eh?...";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_4_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_4_add":
			StartInstantDialog("Mary", "WildRose_Sesil_5", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_5":
			dialog.text = "¿Lo has visto?! ¿Has hablado con él?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_5_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_5_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_6":
			dialog.text = "Chiquilla, yo vi cómo se las arregló con dos narvales casi con las manos desnudas...";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_6_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_6_add":
			StartInstantDialog("Mary", "WildRose_Sesil_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_7":
			dialog.text = "¿Con Sorrento y Rojas?";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_7_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_7_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_8":
			dialog.text = "En aquel entonces ya tenía demasiadas cosas en la cabeza como para recordar los nombres de esos sinvergüenzas, y ahora ni siquiera podría acordarme de ellos.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_8_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_8_add":
			StartInstantDialog("Mary", "WildRose_Sesil_9", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_9":
			dialog.text = "Bueno, no importa. Continúa, por favor, Cécile.";
			link.l1 = "...";
			link.l1.go = "WildRose_Sesil_9_add";
			CharacterTurnByChr(CharacterFromID("LSC_Sesil"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Sesil"));
		break;

		case "WildRose_Sesil_9_add":
			StartInstantDialog("LSC_Sesil", "WildRose_Sesil_10", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Sesil_10":
			dialog.text = "¿Y qué había que seguir? Él tiró a esos dos al agua, se hundieron como piedras, y a él lo ataron y lo llevaron al 'Tartarus'. Y bien hecho — quién sabe a cuántos más ese matón habría decidido ahogar...";
			link.l1 = "¿Un asesino? Suena un poco brusco, ¿no le parece, señora Gallard? Estamos hablando de una persona, de un oficial que acaba de perder a su esposa...";
			link.l1.go = "WildRose_Sesil_11_1";
			link.l2 = "Veo que no tienen la mejor opinión sobre él; no de cada oficial se diría algo así.";
			link.l2.go = "WildRose_Sesil_11_2";
		break;

		case "WildRose_Sesil_11_1":
			dialog.text = "Oficial, bueno, bueno. Llevaba un uniforme de primera, lo recuerdo como si fuera ayer. Casi nuevo, recién estrenado. Pero he visto a muchos oficiales, joven. Y todos ellos se comportaban con mucha más dignidad que este... caballero.";
			link.l1 = "¿Hizo algo más? ¿Aparte de matar a esos dos?";
			link.l1.go = "WildRose_Sesil_12";
			ChangeCharacterComplexReputation(pchar, "honor", 1);
		break;

		case "WildRose_Sesil_11_2":
			dialog.text = "Oficial, bueno, bueno. Su uniforme era de los buenos, lo recuerdo como si fuera ayer. Casi impecable. Pero he visto a muchos oficiales, joven. Y todos ellos se comportaban mucho más dignamente que ese... caballero.";
			link.l1 = "¿Hizo algo más? ¿Aparte de matar a esos dos?";
			link.l1.go = "WildRose_Sesil_12";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Sesil_12":
			dialog.text = "Pidió que le trajeran a un sacerdote a su celda: al padre De la Cruz...";
			link.l1 = "¡Vaya, qué coincidencia! Justo de eso queríamos hablar con usted. ¿Le son conocidos los detalles de esa conversación?";
			link.l1.go = "WildRose_Sesil_13";
		break;

		case "WildRose_Sesil_13":
			dialog.text = "¡Pues claro, joven! Ese bribón protestante le exigió al padre que no bautizara a su hija, aunque su madre era irlandesa, o sea, católica.";
			link.l1 = "Casi nunca he oído a una inglesa hablar así de un protestante... Ejem, perdón por interrumpir, señora "+npchar.lastname+".";
			link.l1.go = "WildRose_Sesil_14";
		break;

		case "WildRose_Sesil_14":
			dialog.text = "En su día yo también fui protestante, para qué ocultarlo. Pero el hermano Julián logró guiarme por el camino correcto.";
			link.l1 = "Vaya, así que es eso... De verdad eres un siervo capaz del Señor. Pero nos hemos desviado. Así que, Casper quería que su hija creciera en la fe protestante.";
			link.l1.go = "WildRose_Sesil_15";
		break;

		case "WildRose_Sesil_15":
			dialog.text = "Así mismo se lo dijo a nuestro padre De la Cruz. Y además, ordenó que llamaran a la niña Julia...";
			link.l1 = "Así que eso es lo que significa esa 'J.'. Mary Julia Casper... Pero entonces, ¿por qué la llamaron Mary?";
			link.l1.go = "WildRose_Sesil_16";
		break;

		case "WildRose_Sesil_16":
			dialog.text = "Porque así lo quiso su madre, por eso. Cuando sacaron a la niña de su vientre, susurró un nombre: Mary. Yo no fui testigo de eso, pero Aurélie Bertin sí estuvo presente en el parto. Pueden preguntarle a ella, si quieren...";
			link.l1 = "Así que tuvieron en cuenta precisamente el deseo de la madre.";
			link.l1.go = "WildRose_Sesil_17";
		break;

		case "WildRose_Sesil_17":
			dialog.text = "¿Y acaso podía ser de otra manera? Ese padre de pacotilla como si se lo hubiera tragado la tierra, sí, ¿eh?";
			link.l1 = "Teniendo en cuenta... los talentos del padre De la Cruz, dudo que la opinión de su padre hubiera sido tomada en cuenta, incluso si se hubiera quedado sentado en el 'Tartarus'. ¿Domingo no compartió con usted - él no estaba al tanto de los planes de Casper respecto a la fuga y el posible regreso por la niña?";
			link.l1.go = "WildRose_Sesil_18_1";
			link.l2 = "Puede que tenga razón. Pero, volviendo a la conversación del padre Domingo con el señor Casper, ¿el sacerdote no mencionó si Joshua habló con él sobre su huida y una posible fecha para regresar por su hija?";
			link.l2.go = "WildRose_Sesil_18_2";
		break;

		case "WildRose_Sesil_18_1":
			dialog.text = "No contaba nada de eso. Sí, ¿eh? Y piénsalo tú mismo, "+npchar.name+", si estuvieras planeando escapar de la cárcel, ¿le contarías eso al primer desconocido que te encuentres? Ese tipo seguro que no lo haría, ya te lo digo.";
			link.l1 = "Así que este hilo tampoco nos llevó a ninguna parte. Bueno, gracias por su tiempo, señora "+npchar.lastname+". Nos volveremos a ver.";
			link.l1.go = "WildRose_Sesil_19";
			ChangeCharacterComplexReputation(pchar, "honor", -1);
			AddCharacterExpToSkill(pchar, "charisma", 100);
		break;

		case "WildRose_Sesil_18_2":
			dialog.text = "No contaba nada de eso. Sí, ¿eh? Y piénsalo tú mismo, "+pchar.name+" , si estuvieras planeando escapar de la cárcel, ¿le contarías eso al primer desconocido que te cruzaras? Ese tipo, desde luego, no lo haría, ya te lo digo yo.";
			link.l1 = "Así que este hilo tampoco nos llevó a ninguna parte. Bueno, gracias por su tiempo, señora "+npchar.lastname+". Nos volveremos a ver.";
			link.l1.go = "WildRose_Sesil_19";
			ChangeCharacterComplexReputation(pchar, "honor", 1);
		break;
		
		case "WildRose_Sesil_19":
			StartInstantDialog("Mary", "WildRose_Mary_121", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Mary_121":
			dialog.text = "Hemos averiguado muchas cosas interesantes, "+pchar.name+". Pero prácticamente no hemos avanzado nada, sí, ¿eh?";
			link.l1 = "Y hasta se han liado un poco. ¿Quién será ese Rupert al que tu madre llamó antes de morir, sí, ¿eh?";
			link.l1.go = "WildRose_Mary_122";
		break;

		case "WildRose_Mary_122":
			dialog.text = "¿Quizá un hermano o... un amigo cercano?";
			link.l1 = "¿Amigo, dices, eh...? Me pregunto si Joshua sabía de él...";
			link.l1.go = "WildRose_Mary_123";
		break;

		case "WildRose_Mary_123":
			dialog.text = "¿A qué estás insinuando, "+pchar.name+"?";
			link.l1 = "Que todo esto hay que pensarlo bien. Por suerte, tendremos tiempo de sobra mientras buscamos a alguien que pueda ayudarnos en esta tarea. Hemos avanzado mucho. Pero aún no hemos llegado al final. No tenemos acceso directo a la oficina del Almirantazgo, y además está al otro lado del océano, en Londres... ¿Tienes alguna idea de quién podría echarnos una mano con eso?";
			link.l1.go = "WildRose_Mary_127";
		break;
		
		case "WildRose_Mary_127":
			dialog.text = "¿Qué hay de Serge Benoit, Charles?";
			link.l1 = "¿El abad? Tiene muchos contactos, sí, ¿eh?, pero dudo que pueda acceder a los archivos de la Flota Real.";
			link.l1.go = "WildRose_Mary_128";
		break;
		
		case "WildRose_Mary_128":
			dialog.text = "No podrá hacerlo él mismo, pero quizás nos ponga en contacto con alguien que sí pueda, sí, ¿eh?";
			link.l1 = "Supongo que sí. Entonces, ponemos rumbo a Saint-Pierre.";
			AddDialogExitQuestFunction("WildRose_Etap2_IslandOfJustice_25");
		break;
		
		// =================================================================
		// =================== ЭТАП 3. «БУМАЖНАЯ РАБОТА» ===================
		// =================================================================
		
		case "WildRose_Mary_131":
			dialog.text = "Bueno, ahora solo nos queda esperar, sí, ¿eh?";
			link.l1 = "Seguro que lo averiguará todo, "+npchar.name+". El tiempo pasará volando, ni te darás cuenta. Y mientras tanto, tenemos cosas que hacer.";
			link.l1.go = "WildRose_Mary_132";
		break;

		case "WildRose_Mary_132":
			dialog.text = "¿Insinúas algo en particular, cariño?";
			link.l1 = "Tenemos un montón de cosas que hacer, pero ¿por qué no volvemos ahora mismo al barco, cerramos la puerta y nos dedicamos un tiempo el uno al otro? ¿Qué dices?";
			link.l1.go = "WildRose_Mary_133";
		break;

		case "WildRose_Mary_133":
			dialog.text = "¡Sabía que lo ibas a proponer, sí, ¿eh?! Te diré una cosa: ¡no vamos a perder el tiempo!";
			link.l1 = "Vamos, mi adorada.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_3");
		break;
		
		case "WildRose_Mary_134":
			dialog.text = "Oh, "+pchar.name+", no te imaginas, simplemente no te imaginas el peso que acaba de quitarse de mi alma, sí, ¿eh?";
			link.l1 = "Me lo imagino perfectamente, querida: ¡estás literalmente radiante, ja, ja! Como ves, todo valió la pena.";
			link.l1.go = "WildRose_Mary_135";
		break;

		case "WildRose_Mary_135":
			dialog.text = "¡Mi padre fue un oficial famoso, imagínate! Pero qué pena que nunca llegamos a conocernos. Y ni siquiera supimos si logró llegar a Tierra Firme, sí, ¿eh?...";
			link.l1 = "Si eso hubiera pasado, seguro que habría vuelto al servicio, y en algún sitio se habría oído algo de él, ¿sí, eh? Difícilmente un hombre así se quedaría quieto en un solo lugar — si no, ¿de quién heredaste eso?";
			link.l1.go = "WildRose_Mary_136";
		break;

		case "WildRose_Mary_136":
			dialog.text = "¿De verdad crees que murió? ¿Que cayó en manos de los españoles en Cuba, o que incluso fue asesinado en la Isla de la Justicia?";
			link.l1 = "Intento mirar la verdad a los ojos con claridad, "+npchar.name+". En aquellos años, existía al menos alguna comunicación con la Isla; los contrabandistas iban allí en sus tartanas con envidiable regularidad. Si él hubiera logrado abandonar la Isla, no me cabe duda de que, pasado un tiempo, habría regresado allí por ti.";
			link.l1.go = "WildRose_Mary_137";
		break;

		case "WildRose_Mary_137":
			dialog.text = "Para sacarme de allí. Pero entonces no nos habríamos conocido, sí, ¿eh?";
			link.l1 = "Así es la vida, querida. Nunca sabes dónde encontrarás algo y dónde lo perderás. Espero que no te arrepientas de estar aquí conmigo, ahora mismo.";
			link.l1.go = "WildRose_Mary_138";
		break;

		case "WildRose_Mary_138":
			dialog.text = "Jamás he oído una tontería más grande, sí, ¿eh? "+pchar.name+"¡Eres el mejor, eres increíble! Gracias por haberte esforzado tanto para ayudarme a descubrir todo esto. Es tan importante para mí, sí, ¿eh? Pero vamos a revisar los documentos, quizá encontremos ahí algo que nuestro amigo no nos contó...";
			link.l1 = "Buena idea. Ahora mismo empezamos.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_7");
		break;
		
		case "WildRose_Mary_139":
			dialog.text = "Bueno, "+pchar.name+"¿has notado algo interesante?";
			link.l1 = "Sí, "+npchar.name+". Algo hay...";
			link.l1.go = "WildRose_Mary_140";
		break;

		case "WildRose_Mary_140":
			dialog.text = "Pareces haber visto un fantasma, sí, ¿eh?";
			link.l1 = "Aquí se menciona a cierto Rupert Northwood.";
			link.l1.go = "WildRose_Mary_141";
		break;

		case "WildRose_Mary_141":
			dialog.text = "¿Rupert Northwood?! ¿De verdad es él?";
			link.l1 = "Silencio, "+npchar.name+" - no grites así. Mmm... Creo que sí, ¿eh? Es esa persona de la que hablaba Chimiset. No puede ser de otra manera, esas coincidencias no existen.";
			link.l1.go = "WildRose_Mary_142";
		break;

		case "WildRose_Mary_142":
			dialog.text = "¿Y tú qué piensas de todo esto, "+pchar.name+"?";
			link.l1 = "Esta historia se está volviendo cada vez más confusa. Resulta que... desde Plymouth zarpó el 'Cornwall', también fue el 'Cornwall' el que llegó a Antigua, pero el que naufragó en los arrecifes de la Isla de la Justicia fue el 'Wrangler' — con ese mismo Joshua Casper al mando, quien logró casarse en secreto, a espaldas del Almirantazgo, con una mujer que, en su agonía, llamaba a alguien llamado Rupert.";
			link.l1.go = "WildRose_Mary_143";
		break;

		case "WildRose_Mary_143":
			dialog.text = "No entiendo nada. Ni siquiera sé quién más podría arrojar aunque sea un poco de luz sobre él. Cuanto más intentamos averiguar algo sobre mi padre, más nos hundimos en un pantano de misterios y secretos que no dejan de aparecer, ¿sí, eh?";
			link.l1 = "Si alguien puede aclarar algo — ese es Joshua Casper o Rupert Northwood.";
			link.l1.go = "WildRose_Mary_144";
		break;

		case "WildRose_Mary_144":
			dialog.text = "¿Northwood? Pero si murió, sí, ¿eh? No pensarás que el informe redactado tras la llegada del 'Cornwall' a Saint John's contiene información falsa, ¿verdad?";
			link.l1 = "Oh, esa ingenuidad tuya, "+npchar.name+"... Empiezo a pensar que toda esta historia está literalmente impregnada de mentiras. Piénsalo tú misma: Joshua Casper era un oficial ejemplar: muchas condecoraciones y ni una sola amonestación. No encaja mucho con lo que averiguamos sobre él en la Isla de la Justicia, donde, sin dudarlo, mandó al otro mundo a dos personas, ¿no te parece?";
			link.l1.go = "WildRose_Mary_145";
		break;

		case "WildRose_Mary_145":
			dialog.text = "Luchó por la vida de su esposa, mi madre, "+pchar.name+"!";
			link.l1 = "Sin duda, pero pensemos, ¿de dónde salió todo esto? Y lo principal, ¿por qué ocultó su matrimonio al Almirantazgo? Un militar hasta la médula, un oficial fiel al reglamento y al deber —de lo contrario, su expediente no habría brillado con tanta pulcritud— y, de repente, semejante locura.";
			link.l1.go = "WildRose_Mary_146";
		break;

		case "WildRose_Mary_146":
			dialog.text = "¿Y si detrás de esto se esconde alguna historia bonita y romántica? Porque, aunque sea raro, a veces pasa, sí, ¿eh?";
			link.l1 = "No me malinterpretes, Mary, pero todo esto no parece una historia romántica. Más bien parece una especie de teatro, y ni siquiera queda claro con qué propósito fue montado. ¿Para qué cambiarle el nombre al barco en ruta hacia Providencia? Se trata de un buque militar — por una jugarreta así uno puede acabar ante un tribunal.";
			link.l1.go = "WildRose_Mary_147";
		break;

		case "WildRose_Mary_147":
			dialog.text = "De acuerdo, es una buena pregunta.";
			link.l1 = "Y con ese Rupert Northwood claramente hay algo turbio. En la batalla cayó casi la mitad de la tripulación, pero, curiosamente, ni un solo oficial, salvo él. ¿Y por qué tu madre, antes de morir, llamó precisamente a Rupert y no a su esposo Joshua?";
			link.l1.go = "WildRose_Mary_148";
		break;

		case "WildRose_Mary_148":
			dialog.text = "Entonces, ¿estás seguro de que el primer oficial no murió en combate contra los españoles, sí? ¿Y que yo no soy hija de Joshua Casper, sino de Rupert Northwood? ¿Es a eso a lo que quieres llegar?";
			link.l1 = "Como ya dije — la verdad sólo la conoce una persona. O bien Joshua Casper, que por alguna razón llamó esposa a Teresa, o bien Rupert Northwood, que también, por motivos desconocidos, se hizo pasar por su propio capitán.";
			link.l1.go = "WildRose_Mary_149";
		break;

		case "WildRose_Mary_149":
			dialog.text = "¡Vaya demonios, sí, ¿eh?! ¿Y ahora qué vamos a hacer, "+pchar.name+"¿Ahora tengo aún más ganas de llegar al fondo de la verdad, sí, ¿eh? Pero ya hemos sacado de todos todo lo que podíamos.";
			link.l1 = "Si hay algún lugar donde estén las respuestas, es en la Isla de la Justicia; ya no quedan personas, salvo quizá al otro lado del océano, que hayan conocido a tus padres, aunque fuera de pasada. Creo que deberíamos hablar una vez más con Aurélie Bertin; tal vez recuerde algo más a lo que podamos aferrarnos.";
			link.l1.go = "WildRose_Mary_150";
		break;

		case "WildRose_Mary_150":
			dialog.text = "¿Pero qué quieres averiguar de ella? Me parece que ya nos contó todo lo que sabía.";
			link.l1 = "Ella contó lo que le preguntamos, pero bien podría haber pasado por alto algún detalle importante. Tal vez tu padre tenía una cicatriz en la cara, o le faltaba un dedo en la mano... Dudo mucho que alguien capaz de idear todos esos trucos con el cambio de nombre del barco y, posiblemente, hasta de su propia identidad, haya acabado de forma miserable en alguna isla o en los calabozos de los castellanos.";
			link.l1.go = "WildRose_Mary_151";
		break;

		case "WildRose_Mary_151":
			dialog.text = "Supongo que tienes razón...";
			link.l1 = "Y si decidimos seguir buscando — ya no en los polvorientos estantes del Almirantazgo, sino aquí, en el Archipiélago, necesitaremos algo más que un simple nombre, y encima uno falso, sí, ¿eh?";
			link.l1.go = "WildRose_Mary_152";
		break;

		case "WildRose_Mary_152":
			dialog.text = "Sabes, todo esto me pone la piel de gallina, sí, ¿eh? No sé si es por lo emocionante que resulta todo esto... o por pensar que mi padre quizá no era tan distinto de ese bastardo de la plantación de Bishop.";
			link.l1 = "De todos modos, te lo prometo, haremos todo lo posible para aclarar todo. Así que, no perdamos tiempo. ¡En marcha!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap3_Paperwork_9");
		break;
		
		// =================================================================
		// ==================== ЭТАП 4. «ПУТЬ К СВЕТУ» =====================
		// =================================================================
		case "WildRose_Mary_161":
			dialog.text = "Vamos, "+pchar.name+", no vamos a perder el tiempo en vano, sí, ¿eh?";
			link.l1 = "Espero que Aurélie esté en su camarote y que no tengamos que recorrer toda la Isla buscándola...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_2");
		break;
		
		case "WildRose_Mary_162":
			dialog.text = "Parece que otra vez no hemos tenido suerte, sí, ¿eh? ¿Y adónde habrá podido ir?";
			link.l1 = "Espero que la enfermedad no haya vuelto a apoderarse de su mente...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_4");
		break;
		
		case "WildRose_Jillian_31":
			dialog.text = "Ah, ¿de nuevo por aquí? Bueno, hola... ¿Qué ocurre, necesitas a Aurélie otra vez?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_31_add";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Jillian_31_add":
			StartInstantDialog("Mary", "WildRose_Jillian_32", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_32":
			dialog.text = "No se puede negar que eres lista, Jillian. ¿No sabrás por casualidad dónde está ella?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_32_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_32_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_33", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_33":
			dialog.text = "En la iglesia, iba a confesarse. Si se dan prisa, la encontrarán allí.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_33_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_33_add":
			StartInstantDialog("Mary", "WildRose_Jillian_34", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_34":
			dialog.text = "Bueno, si está confesando, entonces seguro que está en su sano juicio y con la memoria bien clara, sí, ¿eh?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_34_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_34_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_35", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_35":
			dialog.text = "Es difícil decirlo... Los últimos tres días no ha sido ella misma, no encuentra su lugar. ¿Sabe? Se puso terriblemente nerviosa por alguna razón cuando vio los mástiles de su barco más allá del anillo exterior.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_35_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_35_add":
			StartInstantDialog("Mary", "WildRose_Jillian_36", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_36":
			dialog.text = "Me pregunto por qué será eso, sí, ¿eh?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_36_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_36_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_37", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_37":
			dialog.text = "Bueno, supongo que le desagrada la idea de que puedas interrogarla de nuevo. Pero, ¿cuándo te han importado los problemas ajenos, sí, ¿eh?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_37_add";
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;

		case "WildRose_Jillian_37_add":
			StartInstantDialog("Mary", "WildRose_Jillian_38", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_38":
			dialog.text = "No te atrevas a hablarme en ese tono, Jillian. Te perdono esta vez, pero atrévete a decir algo así otra vez...";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_5");
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
		break;
		
		case "WildRose_Jillian_41":
			dialog.text = "Vaya persona más nerviosa, en cuanto algo no es como quiere, ¿verdad?";
			link.l1 = "No conviene provocarla sin motivo, "+npchar.name+". Ya saben que no lleva la espada solo por adorno, sí, ¿eh?";
			link.l1.go = "WildRose_Jillian_42";
		break;
		
		case "WildRose_Jillian_42":
			dialog.text = "¿Y dejarían que algo así pasara, "+pchar.name+"?";
			link.l1 = "No has visto a Mary en combate, "+npchar.name+". De lo contrario, no se harían ilusiones de que alguien o algo pueda detenerla. Nos veremos de nuevo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_7");
		break;
		
		case "WildRose_Mary_163":
			dialog.text = "Seguro que quieres preguntarme algo, sí, ¿eh? "+pchar.name+", sí, ¿eh?...";
			link.l1 = "Si te soy sincera, no me importa mucho qué pasó entre vosotros, aunque me imagino cómo se llamaba esa gata. Mejor dicho, cómo se llamaba antes. ¿De verdad quieres hablar de esto?";
			link.l1.go = "WildRose_Mary_164_1";
			link.l2 = "¿Tú y Gillian no os lleváis bien por algo? ¿O, mejor dicho, por alguien?";
			link.l2.go = "WildRose_Mary_164_2";
		break;

		case "WildRose_Mary_164_1":
			dialog.text = "Pues, en realidad, no.";
			link.l1 = "Como digas. Ahora vamos a buscar a Aurélie.";
			link.l1.go = "WildRose_Mary_165";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Mary_164_2":
			dialog.text = "Esa sabandija nunca me va a perdonar que Alan me eligiera a mí en vez de a ella. Aunque podría hacerlo, considerando que él ya no está... La verdad es que, "+pchar.name+", preferiría no hablar de eso, sí, ¿eh?";
			link.l1 = "Como digas, preciosa. Entonces vamos a buscar a Aurélie.";
			link.l1.go = "WildRose_Mary_165";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;
		
		case "WildRose_Mary_165":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_9");
		break;
		
		case "WildRose_Oreli_61":
			dialog.text = ""+pchar.name+"¡Mary!   ¡Has vuelto a la Isla, qué alegría!";
			link.l1 = "Nos alegra ver que goza de buena salud, "+npchar.name+". En realidad, vinimos a la Isla para hablar con usted otra vez. Pero no se preocupe, no nos llevará mucho tiempo.";
			link.l1.go = "WildRose_Oreli_62";
			DelLandQuestMark(npchar);
		break;
		
		case "WildRose_Oreli_62":
			dialog.text = "Oh, chicos, no tenéis ninguna piedad con una vieja. Pero sentía que usted vendría. ¿Es otra vez sobre tus padres, sí, Mary?";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_62_add";
		break;

		case "WildRose_Oreli_62_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_63", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_63":
			dialog.text = "Por favor, Aurélie. Entiendo que te cuesta recordarlo, teniendo en cuenta cuánto tiempo ha pasado, pero intenta una vez más, ¿sí, eh?";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_63_add";
		break;

		case "WildRose_Oreli_63_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_64", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_64":
			dialog.text = "Ya les conté todo lo que recuerdo. No entiendo qué más quieren sacarme, sí, ¿eh?";
			link.l1 = "Vamos a hacerle un par de preguntas, "+npchar.name+". Por favor, intente recordar algo, algún detalle o particularidad. No vamos a presionarla...";
			link.l1.go = "WildRose_Oreli_65";
		break;

		case "WildRose_Oreli_65":
			dialog.text = "¿Y acaso no es eso lo que están haciendo ahora mismo?";
			link.l1 = "Ya has hecho tanto por nosotros, "+npchar.name+"... Solo esperamos que en los laberintos de tu memoria se encuentre algo más que nos ayude mucho.";
			link.l1.go = "WildRose_Oreli_66_1";
			link.l2 = "Hemos recorrido un largo camino, "+npchar.name+". Ni se imagina cuánto esfuerzo y tiempo nos costó. Pero nos perdimos, y sólo usted y su memoria pueden guiarnos de nuevo por el camino de la verdad.";
			link.l2.go = "WildRose_Oreli_66_2";
			CharacterTurnByChr(CharacterFromID("LSC_Oreli"), pchar);
		break;

		case "WildRose_Oreli_66_1":
			dialog.text = "A la memoria... ¿Qué queda de ella, de esa memoria? A veces, por las mañanas, ni siquiera puedo recordar cómo me llamo, y ustedes quieren que les cuente detalles — de cosas que pasaron hace veinte años. Pero bueno, pregunten.";
			link.l1 = "Nos interesa el señor Casper, el padre de Mary. ¿Puede recordar algo llamativo de su aspecto? Tal vez tenía una cicatriz en la cara, o cojeaba mucho...";
			link.l1.go = "WildRose_Oreli_67";
			ChangeCharacterComplexReputation(pchar, "nobility", 2);
		break;

		case "WildRose_Oreli_66_2":
			dialog.text = "¿La memoria... Qué queda de ella, de esa memoria. A veces por las mañanas ni siquiera recuerdo cómo llegar al retrete, y ustedes quieren que les cuente detalles de lo que pasó aquí, entre estos restos de barcos, hace ya veinte años. Pero bueno, está bien, pregunten.";
			link.l1 = "Nos interesa el señor Casper, el padre de Mary. ¿Puede recordar algo llamativo de su aspecto? Tal vez tenía una cicatriz en la cara, o cojeaba mucho...";
			link.l1.go = "WildRose_Oreli_67";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Oreli_67":
			dialog.text = "Oh... Creo que ya mencioné que lo vi solo en la más absoluta oscuridad, en la bodega del 'Ceres Smithy', donde prepararon un lecho para la pobre Teresa. No cojeaba, eso seguro; al contrario, era un hombre bastante ágil.";
			link.l1 = "¿Y su edad? ¿Era joven o ya tenía sus años?";
			link.l1.go = "WildRose_Oreli_68";
		break;

		case "WildRose_Oreli_68":
			dialog.text = "No lo llamaría viejo, precisamente... Pero no le presté mucha atención: me preocupaba más Teresa. Desde luego, tenía un aspecto lamentable, parecía un fantasma. Aunque, ten en cuenta que durante toda la semana en que su esposa estuvo a punto de dar a luz, apenas pegó ojo... No paraba de correr por la Isla, sin descanso.";
			link.l1 = "A la esposa, entonces, la quería mucho. Y usted pasaba mucho tiempo a su lado, ¿no? ¿Ella no decía nada sobre su marido?";
			link.l1.go = "WildRose_Oreli_69";
		break;

		case "WildRose_Oreli_69":
			dialog.text = "Teresa preguntaba por él todo el tiempo. Dormía mucho, a veces deliraba, pero en cuanto volvía en sí, enseguida preguntaba dónde estaba. Y la pobrecita lo esperaba con tantas, tantas ganas. Pero en el momento más importante, él nunca llegó.";
			link.l1 = "Entiendo. Por lo visto, su amor era mutuo... Bueno, gracias, Aurélie. Nos ha ayudado mucho.";
			link.l1.go = "WildRose_Oreli_70";
		break;

		case "WildRose_Oreli_70":
			dialog.text = "¿Y eso es todo? Pensé que nuestra charla se alargaría una hora o dos.";
			link.l1 = "Prometimos no hacerles sufrir mucho. Cuídese, "+npchar.name+". Que te vaya bien.";
			link.l1.go = "WildRose_Oreli_71";
		break;

		case "WildRose_Oreli_71":
			dialog.text = "¡Esperen, jóvenes! Tengo algo más para ustedes... Bueno, en realidad, para ti, Mary.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_72_a";
			NPCsLookEachOther("LSC_Oreli", "Mary");
		break;
		
		case "WildRose_Oreli_72_a": //
			dialog.text = "Aquí tienes, niña mía, toma... En cuanto vi las velas de su barco, tomé este sombrero conmigo para no olvidarlo. Pero salir al muelle... no me atreví.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_72_add";
		break;

		case "WildRose_Oreli_72_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_73", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_73":
			dialog.text = "¿Qué es eso, Aurélie? ¿Un sombrero?..";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_73_add";
		break;

		case "WildRose_Oreli_73_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_74", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_74":
			dialog.text = "El sombrero de tu madre, Teresa. Lo tenía consigo cuando trajeron a los supervivientes del naufragio al 'Ceres Smitty'. Cuando Teresa falleció, recogí ese sombrero del suelo junto a su cama — y luego me olvidé de él... Solo me acordé hoy, durante nuestra conversación.";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_74_add";
		break;

		case "WildRose_Oreli_74_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_75", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_75":
			dialog.text = "Orélie... ¡La guardaste todos estos años! Y... y no la tiraste, no la vendiste... ¡Gracias, gracias de verdad! Ni te imaginas lo mucho que esto... significa para mí, sí, ¿eh?";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_75_add";
		break;

		case "WildRose_Oreli_75_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Oreli_76", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;

		case "WildRose_Oreli_76":
			dialog.text = "Perdóname, Mary, debí habértela dado hace mucho tiempo... Pero mi memoria ya es como un colador viejo, sí, ¿eh?...";
			link.l1 = "...";
			link.l1.go = "WildRose_Oreli_76_add";
		break;

		case "WildRose_Oreli_76_add":
			StartInstantDialogTurnToNPC("Mary", "WildRose_Oreli_77", "Quest\CompanionQuests\WildRose.c", "LSC_Oreli");
		break;

		case "WildRose_Oreli_77":
			dialog.text = "¡No hay mejor momento, Aurélie! Me la pruebo ahora mismo, sí, ¿eh?";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_hat_1");
		break;
		
		case "WildRose_Mary_166":
			dialog.text = "Bueno, cariño, ¿qué te parezco?..";
			link.l1 = "Eres preciosa. Y el sombrero... aún no ha pasado de moda, así que también te queda de maravilla, sí, ¿eh?";
			link.l1.go = "WildRose_Mary_167";
		break;
		
		case "WildRose_Mary_167":
			dialog.text = "¿De verdad? Me alegra tanto que te guste, sí, ¿eh?";
			link.l1 = "¿Y acaso podría ser de otra manera?";
			link.l1.go = "WildRose_Mary_167_add";
		break;
		
		case "WildRose_Mary_167_add":
			StartInstantDialogTurnToNPC("LSC_Oreli", "WildRose_Mary_168", "Quest\CompanionQuests\WildRose.c", "Mary");
		break;
		
		case "WildRose_Mary_168":
			dialog.text = "...";
			link.l1 = "Gracias otra vez, Aurélie — ¡ha hecho este día un poco más luminoso! Que le vaya bien, descanse.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_10");
		break;
		
		case "WildRose_Mary_171":
			dialog.text = "Así que al final sí fue Rupert. Rupert Northwood, sí, ¿eh?";
			link.l1 = "Obviamente que sí, querida. Hizo todo lo posible por salvar a su esposa... o a su amada, no lo sé. En realidad, eso no importa. Lo principal es que ahora sabemos a quién debemos buscar.";
			link.l1.go = "WildRose_Mary_172";
		break;

		case "WildRose_Mary_172":
			dialog.text = "¿Pero qué pasó con el verdadero Joshua Casper, el capitán del 'Cornwall'?";
			link.l1 = "Buena pregunta, pero no es la principal ahora. Lo que realmente importa es por qué Rupert no volvió por ti, si tanto amaba a Teresa — eso sí que es interesante. Y eso será lo primero que le preguntemos. Si es que sigue vivo y logramos encontrarlo. Una cosa está clara: no regresó a la Armada. No tenía sentido arriesgarse así.";
			link.l1.go = "WildRose_Mary_174";
		break;

		case "WildRose_Mary_174":
			dialog.text = "¿Qué pudo haberle hecho tomar el nombre de Joshua Casper? ¿Qué ocurrió a bordo del 'Cornwall', que luego fue el 'Wrangler'? ¿De verdad mi padre es un criminal, "+pchar.name+"?";
			link.l1 = "Me temo que tampoco podemos descartar esa posibilidad, sí, ¿eh? "+npchar.name+". Deberíamos estar preparados absolutamente para todo.";
			link.l1.go = "WildRose_Mary_175";
		break;

		case "WildRose_Mary_175":
			dialog.text = "No quiero ni pensar en eso...";
			link.l1 = "Por ahora tenemos que pensar en otra cosa: dónde buscarlo. Podría haberse unido a los piratas o contrabandistas. O quizá se instaló en alguna ciudad y no se deja ver. Todo es posible.";
			link.l1.go = "WildRose_Mary_176";
		break;
		
		case "WildRose_Mary_176":
			dialog.text = "¿Y qué propones que hagamos? ¿Cómo vamos a encontrarlo? ¿Entrar a cada colonia, decir su nombre y esperar que alguien haya oído algo de Rupert Northwood?";
			link.l1 = "O Joshua Casper. Perfectamente pudo seguir viviendo bajo la identidad de su antiguo capitán, que probablemente ya estaba muerto. Pero eso conllevaba ciertos riesgos, porque podían empezar a buscar la goleta desaparecida. Más aún teniendo en cuenta que llevaba un cofre de plata destinado a la guarnición de Providencia.";
			link.l1.go = "WildRose_Mary_177";
		break;

		case "WildRose_Mary_177":
			dialog.text = "Tienes razón, sí, ¿eh?";
			link.l1 = "En cambio, Rupert Northwood, supuestamente muerto cerca de las Azores, difícilmente habría sido de interés para alguien. Aunque, sin duda, aún hay mucho en qué pensar.";
			link.l1.go = "WildRose_Mary_178";
		break;

		case "WildRose_Mary_178":
			dialog.text = "¿Cuánto tiempo más tendremos que gastar en esto, "+pchar.name+"¿?! Porque puede estar en cualquier parte, en cualquier colonia, sí, ¿eh?";
			link.l1 = "Si es que sobrevivió, claro. Pero no estoy de acuerdo contigo. Difícilmente hablaba español con soltura, así que no tendría nada que hacer ni en Cuba ni en La Española. Podía chapurrear francés y marcharse a la Tortuga o a alguna de las colonias de las Pequeñas Antillas. O podría haberse instalado en la Costa de los Mosquitos, bajo la protección de sus compatriotas. De verdad podríamos pasar meses buscándolo, y ni siquiera es seguro que tengamos éxito.";
			link.l1.go = "WildRose_Mary_179";
		break;

		case "WildRose_Mary_179":
			dialog.text = "Pero no quiero rendirme, "+pchar.name+". ¡Pero no ahora, cuando ya hemos descubierto tanto, sí, ¿eh?!";
			link.l1 = "Yo tampoco te lo estaba proponiendo, "+npchar.name+". No necesitamos buscarlo nosotros mismos: es mejor acudir a alguien con contactos. Ya funcionó una vez, ¿por qué no intentarlo de nuevo?";
			link.l1.go = "WildRose_Mary_180";
		break;

		case "WildRose_Mary_180":
			dialog.text = "¿Me sugieres que volvamos a pedirle ayuda al abad? Creí que nos dejó claro que no podíamos contar con más apoyo de su parte en este asunto, sí, ¿eh?";
			link.l1 = "Eso sería demasiado descarado con el viejo, tienes razón.";
			link.l1.go = "WildRose_Mary_181";
		break;

		case "WildRose_Mary_181":
			dialog.text = "¿Pero entonces a quién podemos acudir? ¿Quién tiene el dinero y los contactos para algo así?";
			link.l1 = "Bueno, está claro que nosotros tendremos que financiar la búsqueda. En cuanto a los contactos... Supongo que Fadey Moscovita podría ayudarnos. Seguro que conoce a gente competente que podríamos enviar a las colonias. O, al menos, sabrá decirnos a quién acudir.";
			link.l1.go = "WildRose_Mary_182";
		break;

		case "WildRose_Mary_182":
			dialog.text = "¿Entonces vamos a Basseterre?";
			link.l1 = "Sí, vamos a ver a nuestro amigo. No creo que sea una tarea muy difícil para él, sí, ¿eh?";
			link.l1.go = "WildRose_Mary_183";
		break;

		case "WildRose_Mary_183":
			dialog.text = "¿Levantamos anclas mañana, qué te parece? Me gustaría pasar el resto de este día y la noche contigo a solas, en el 'Ceres Smithy'.";
			link.l1 = "De esas propuestas no se rechaza, preciosa. Los dos nos hemos ganado un pequeño descanso, sí, ¿eh?";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_12");
		break;
		
		case "WildRose_Jillian_51":
			dialog.text = "¿Qué, ya se marchan de la Isla? ¿De verdad ni siquiera se quedarán para el funeral?";
			link.l1 = "¿Un funeral?..";
			link.l1.go = "WildRose_Jillian_52";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Jillian_52":
			dialog.text = "Ah, así que no lo sabías. Entiendo... Aurélie Bertin falleció esta noche.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_52_add";
		break;

		case "WildRose_Jillian_52_add":
			StartInstantDialog("Mary", "WildRose_Jillian_53", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_53":
			dialog.text = "¿Qué?! No puede ser — si justo ayer hablamos con ella, y estaba viva y bien. ¿O alguien la...";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_53_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_53_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_54", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_54":
			dialog.text = "No, Mary. Aurélie murió mientras dormía. Hoy fui a verla, para llevarle unas pomadas para las articulaciones que preparó el hermano Julian, y la encontré así. Estaba acostada en la cama, con una sonrisa extraña en el rostro. Pero ya estaba pálida y fría.\nLa última semana la anciana no era ella misma, incluso pensé que la enfermedad que expulsó el brujo negro había regresado. Pero su mente estaba bastante clara y, al parecer, no deliraba.";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_54_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_54_add":
			StartInstantDialog("Mary", "WildRose_Jillian_55", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_55":
			dialog.text = "Al menos no sufrió, sí, ¿eh?";
			link.l1 = "...";
			link.l1.go = "WildRose_Jillian_55_add";
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("LSC_Jillian_clone"));
			CharacterTurnByChr(CharacterFromID("LSC_Jillian_clone"), CharacterFromID("Mary"));
		break;

		case "WildRose_Jillian_55_add":
			StartInstantDialog("LSC_Jillian_clone", "WildRose_Jillian_56", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Jillian_56":
			dialog.text = "¿Entonces se quedarán para el funeral? Será mañana, en el arrecife más lejano: allí el agua es lo bastante profunda y los cangrejos no llegan, sí, ¿eh?";
			link.l1 = "Nos quedaremos, Gillian. Aurélie hizo tanto por Mary que no podemos hacer otra cosa. Si nadie se opone, organizaremos la procesión en nuestro barco. La enterraremos en mar abierto, con todos los honores.";
			link.l1.go = "WildRose_Jillian_57";
		break;
		
		case "WildRose_Jillian_57":
			dialog.text = "Nadie se va a oponer. Es más cómodo y, al final, más seguro que andar trepando entre los restos.";
			link.l1 = "Entonces encárguense de organizar el funeral: Mary les ayudará. Yo tengo que hablar con alguien...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_14");
		break;
		
		case "WildRose_Chimiset_61":
			dialog.text = "¡Y otra vez estás aquí, mi querido amigo! ¿Qué puedo hacer por ti esta vez?";
			link.l1 = "Hola, "+npchar.name+". ¿Ya has oído lo que pasó esta noche?";
			link.l1.go = "WildRose_Chimiset_62";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Chimiset_62":
			dialog.text = "¿Hablas de la muerte de Aurélie? Veo que sí. Claro que lo he oído. Ella vivía en el 'Plutón', que prácticamente es territorio de los Rivadós. Y la gente en los demás barcos no habla de otra cosa.";
			link.l1 = "Nos vimos con ella no más tarde que ayer, y estaba bien de salud, salvo, claro, que llevaba toda la última semana algo inquieta. Y cuando vio nuestro barco, se puso aún más nerviosa.";
			link.l1.go = "WildRose_Chimiset_63";
		break;

		case "WildRose_Chimiset_63":
			dialog.text = "El ser humano siente cuando el río de su vida se está secando. Algunos lo muestran a todos a su alrededor, otros lo guardan en su interior, pero todos lo sienten, de una forma u otra, especialmente quienes saben escuchar a su corazón.";
			link.l1 = "Me pareció que estaba sana, casi como una cervatilla joven, "+npchar.name+". Y aquí hay algo que no encaja...";
			link.l1.go = "WildRose_Chimiset_64_1";
			link.l2 = "Y aun así, claramente no estaba dando su último aliento, "+npchar.name+".";
			link.l2.go = "WildRose_Chimiset_64_2";
		break;

		case "WildRose_Chimiset_64_1":
			dialog.text = "Amigo mío, la mente y el cuerpo son cosas de un orden completamente distinto. La mente dirige al cuerpo, y a veces el cuerpo intenta dominar la mente. Están estrechamente conectados, pero no son una sola cosa. Un hombre puede parecer completamente sano por fuera, y aun así su alma ya estar caminando por el sendero de la muerte.";
			link.l1 = "Eres listo, amigo mío, muy listo. Si sientes que la verdad ronda cerca, la perseguirás como un león a una cebra, y no pararás hasta atraparla. Lo entendí en cuanto te vi, en ese mismo instante.";
			link.l1.go = "WildRose_Chimiset_65";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Chimiset_64_2":
			dialog.text = "Amigo mío, la mente y el cuerpo son cosas de un orden completamente distinto. La mente dirige al cuerpo, a veces el cuerpo intenta tomar el control de la mente. Están estrechamente ligados, pero no son un todo único. Una persona puede parecer completamente sana por fuera, pero su alma ya va por el sendero de la muerte.";
			link.l1 = "¿Sabes? Se me ocurrió que Aurélie como si nos hubiera estado esperando, como si supiera que íbamos a venir. La anciana podría haber muerto un día antes o después, pero sucedió casi justo después de que nos contara algo importante sobre el padre de Mary.";
			link.l1.go ="WildRose_Chimiset_65";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Chimiset_65":
			dialog.text = "Eres listo, amigo mío, muy listo. Si sientes que la verdad ronda cerca, la persigues como un león a una cebra, y no te detienes hasta atraparla. Lo entendí enseguida, en el mismo instante en que te vi.";
			link.l1 = "No... Espera. Entonces, ese ritual que hiciste en la bodega del 'Protector'... no frenó el avance de la enfermedad de Aurélie, ¿verdad? ¿Pero qué fue lo que hiciste entonces?";
			link.l1.go = "WildRose_Chimiset_66";
		break;

		case "WildRose_Chimiset_66":
			dialog.text = "Puedes llenar un río de piedras, pero eso no detendrá su cauce. Sabía que necesitaban algo importante de Aurélie — y también que no lo conseguirían de inmediato. Pero cuánto tiempo les tomaría, eso me era desconocido. Por eso levanté una represa, invocando todas sus fuerzas vitales para contener la enfermedad hasta que cumpliera con su propósito. Y, en cuanto eso ocurrió, la barrera se derrumbó...";
			link.l1 = "Entonces, ¿resulta que Aurélie... en el momento de su muerte no estaba en sí misma, no se daba cuenta de sí misma, como pensábamos?";
			link.l1.go = "WildRose_Chimiset_67";
		break;

		case "WildRose_Chimiset_67":
			dialog.text = "Puso todas sus fuerzas en mantenerse en su sano juicio y con la memoria lúcida, y cuando eso ya no fue necesario, la enfermedad cayó sobre ella como una gran ola, llevándola al valle de la muerte. ¿Fue su muerte tranquila, o partió hacia su Dios atormentada por fantasmas del pasado y horribles pesadillas? No lo sé, amigo mío, porque eso me está vedado.";
			link.l1 = "Tú sabías perfectamente a qué iba a llevar todo esto, ¿verdad? ¡¿Por qué demonios no me advertiste de las consecuencias?! ¡Vamos, habla!";
			link.l1.go = "WildRose_Chimiset_68_1";
			link.l2 = "Sabías lo que hacías, "+npchar.name+". ¿Por qué no me avisaste de a qué podía llevar todo esto?";
			link.l2.go = "WildRose_Chimiset_68_2";
		break;

		case "WildRose_Chimiset_68_1":
			dialog.text = "Porque decidí ayudarte, amigo mío, a descubrir lo que necesitaban saber, y a ella, a cumplir su destino. Si te hubiese dicho lo que le esperaba, podrías no haber dado el paso — y Aurélie se habría llevado sus secretos a la tumba. ¿De qué habría servido? Habría muerto en vano. Como una gacela abatida por un león, pero no devorada, y en su lugar dejada a los buitres.";
			link.l1 = "Destino, utilidad... Eres todo un hacedor de destinos, "+npchar.name+". Dios en forma humana.";
			link.l1.go = "WildRose_Chimiset_69";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;

		case "WildRose_Chimiset_68_2":
			dialog.text = "Porque decidí ayudarte, amigo mío, a descubrir lo que necesitaban saber, y a ella, a cumplir su destino. Si te hubiese dicho lo que le esperaba, podrías no haber dado el paso — y Aurélie se habría llevado sus secretos a la tumba. ¿De qué habría servido? Habría muerto en vano. Como una gacela abatida por un león, pero no devorada, y en su lugar dejada a los buitres.";
			link.l1 = "Destino, utilidad... Eres todo un hacedor de destinos, "+npchar.name+". Dios en forma humana.";
			link.l1.go = "WildRose_Chimiset_69";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;

		case "WildRose_Chimiset_69":
			dialog.text = "Me parece oír descontento en tu voz, amigo mío. Pero no, en absoluto me considero un dios, y créeme, ni siquiera él es todopoderoso. Ni aquel en quien creéis vosotros, ni aquellos a quienes adoramos nosotros. Los dioses no pueden dar a una persona más fuerza de la que le fue concedida al nacer. Nosotros, los chamanes, solo podemos encauzar esa fuerza en una dirección u otra, y nada más.";
			link.l1 = "Y les dejaste seguir un rumbo que la condenó a la muerte...";
			link.l1.go = "WildRose_Chimiset_70";
		break;

		case "WildRose_Chimiset_70":
			dialog.text = "Yo solo orienté a Aurélie hacia el camino que, al recorrerlo, le permitió ayudar a Mary — una persona con la que estaba profundamente unida desde el mismo momento de su nacimiento. Tu compañera nació delante de sus propios ojos. Te lo ruego, no me mires como a un loco. No vas a decir, ¿verdad?, que me viste como a un hechicero bonachón capaz de hacer que el río del tiempo corra hacia atrás con un simple gesto de la mano.";
			link.l1 = "No sé qué decirte, "+npchar.name+". Quizás todo esto de verdad no fue en vano. Pero así no debía ser. Tenías que decírmelo, y yo - tomar la decisión. Pero lo hecho, hecho está. Bueno, adiós, amigo.";
			link.l1.go = "WildRose_Chimiset_71";
		break;

		case "WildRose_Chimiset_71":
			dialog.text = "Ah, no me imaginaba nuestro último encuentro así, amigo mío...";
			link.l1 = "¿Por qué crees que ella es la última?";
			link.l1.go = "WildRose_Chimiset_72";
		break;

		case "WildRose_Chimiset_72":
			dialog.text = "Algunos ríos desembocan en otros y se hacen parte de ellos, otros se secan, y algunos — como el nuestro — encuentran su final en forma de una enorme cascada...";
			link.l1 = "¿Otra vez acertijos, Chimiset? Creo que por hoy ya tuve suficiente. Pienso que nos volveremos a ver.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_15");
		break;
		
		case "WildRose_Mary_191":
			dialog.text = "Ya sabía que te encontraría aquí, sí, ¿eh? ¿Qué querías de Chimiset, "+pchar.name+"¿Qué te dijo?";
			link.l1 = "No es exactamente lo que esperaba —o mejor dicho, quería— oír. Pero de lo que, en el fondo, tenía una vaga sospecha.";
			link.l1.go = "WildRose_Mary_192";
		break;

		case "WildRose_Mary_192":
			dialog.text = "Me lo contarás, sí, ¿eh?";
			link.l1 = "No, "+npchar.name+". Esta vez, no. Todo lo dicho en el camarote del 'Protector' ahí se quedará, entre Chimiset y yo.";
			link.l1.go = "WildRose_Mary_193";
		break;

		case "WildRose_Mary_193":
			dialog.text = "Hacía tiempo que no oía tanta determinación en tu voz, "+pchar.name+". Pero bueno, tenemos otras preocupaciones, sí, ¿eh? El funeral será mañana, al atardecer, a las siete.";
			link.l1 = "Vamos, les ayudaré a prepararlo todo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_17");
		break;
		
		case "WildRose_Mary_201":
			dialog.text = "Parece que todos los que querían ya se han reunido, sí, ¿eh?";
			link.l1 = "Pensé que habría más gente. Al menos, de los pacíficos.";
			link.l1.go = "WildRose_Mary_202";
			CharacterTurnToLoc(npchar, "quest", "quest1");
			CharacterTurnToLoc(pchar, "quest", "quest1");
		break;

		case "WildRose_Mary_202":
			dialog.text = "Bueno, a Kuranai nadie lo invitó, igual que a los rivadeños. Abbot, ese pavo arrogante y repugnante, dijo que tenía asuntos más importantes que enterrar a una católica; algo parecido soltaron Lauderdale y Muskett. Cassel, ese patán, simplemente dijo que no vendría. Y todos los demás están aquí.";
			link.l1 = "Algunas cosas siempre estarán más allá de mi comprensión. Bueno, que Dios los juzgue. Y aquí está el hermano Julián... Ahora todo va a empezar.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_2");
		break;
		
		case "WildRose_funeral_1":
			dialog.text = "Aunque nuestros corazones estén llenos de pesar, demos gracias a Dios por todos los bienes con los que Él bendijo a la difunta Aurélie, y exclamemos: Te damos gracias, Dios, Padre nuestro\n"+"Durante todos los años y días que Aurélie vivió  con nosotros\n"+"Por el gran don del santo bautismo, gracias al cual Aurélie se convirtió en Tu hija\n"+"Por las habilidades y conocimientos con los que la has dotado\n"+"Por su servicio al bienestar de la familia y de los demás\n"+"Por su paciencia con nuestros errores\n"+"Oremos a Dios para que reciba en Su gloria a nuestra difunta hermana Aurélie y digamos: Te lo pedimos, Señor\n"+"Que las buenas obras de Aurélie den frutos abundantes\n"+"Que lo que ella empezó, siga adelante\n"+"Perdona los pecados que ha cometido\n"+"Que su recuerdo viva en nuestros corazones\n"+"Oremos a Dios para que fortalezca la fe y la esperanza de los que sufren, y clamemos a Él: Señor, aumenta nuestra fe\n"+"Por medio de Tu Hijo, hecho hombre\n"+"Por medio de Tu Hijo, Jesucristo, que nos ha amado infinitamente\n"+"Por tu Hijo, que aceptó la muerte por nuestros pecados y resucitó para nuestra salvación\n"+"Por medio de Tu Hijo, que nos abrió el camino al cielo\n"+"Junto con todos los fieles que nos han precedido en la morada celestial, oremos como nos enseñó el Salvador.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_7");
			
			WildRose_Etap4_PathToLight_18_funeral_6_1();
		break;
		
		case "WildRose_funeral_2":
			dialog.text = "Dios todopoderoso, escucha nuestras oraciones, elevadas con fe en Tu Hijo resucitado, y fortalece nuestra esperanza de que, junto con Tu sierva difunta, todos nosotros también seamos dignos de la resurrección. Por nuestro Señor Jesucristo, Tu Hijo, que vive y reina contigo en la unidad del Espíritu Santo, Dios por los siglos de los siglos. Amén.";
			link.l1 = "Dios, Padre Todopoderoso, el misterio de la cruz es nuestra fuerza y la Resurrección de Tu Hijo es el fundamento de nuestra esperanza; libera a Tu sierva difunta de las ataduras de la muerte y únela al coro de los salvados. Por Cristo, nuestro Señor. Amén.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_8");
			WildRose_Etap4_PathToLight_18_funeral_7_1();
		break;
		
		case "WildRose_funeral_3":
			dialog.text = ""+pchar.name+", vamos rápido a la cabina, sí, ¿eh? Estoy a punto de echarme a llorar... No quiero que nadie lo vea.";
			link.l1 = "Por supuesto, "+npchar.name+". Vamos.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_18_funeral_13");
		break;
		
		case "WildRose_Mary_211":
			dialog.text = "Dicen que solo empiezas a valorar de verdad a una persona después de su muerte, ¿lo habías oído, sí, ¿eh? "+pchar.name+"?";
			link.l1 = "Sí, y no una sola vez.";
			link.l1.go = "WildRose_Mary_212";
		break;

		case "WildRose_Mary_212":
			dialog.text = "Eric solía repetirlo mucho. Creo que hablaba de su familia. Nunca le pregunté sobre ella, pensaba que aún habría tiempo. Y luego murió, sí, ¿eh? Ahora tampoco está Aurélie, y recién ahora me doy cuenta de lo poco que le dedicaba tiempo y atención. Mucho menos de lo que realmente merecía.";
			link.l1 = "No tienes la culpa de nada. No podemos saber cuándo el Señor se llevará a nuestros seres queridos. Y nunca es suficiente el tiempo que pasamos con ellos. Nunca.";
			link.l1.go = "WildRose_Mary_213";
		break;

		case "WildRose_Mary_213":
			dialog.text = "Puede que sí, ¿eh? Además, Erik solía decir —y Aurélie estaba de acuerdo con él— que cualquier lugar, antes que nada, son las personas. No las casas, ni los árboles, ni los caminos, sino la gente. Cuando piensas en algún punto del mapa, lo primero que recuerdas son precisamente quienes viven allí. O vivieron.";
			link.l1 = "Nunca lo había pensado. Pero supongo que Erik tenía razón: al fin y al cabo, ¿de qué sirve una casa si, al entrar en ella, ya no te encuentras con tu padre o tu hermano?";
			link.l1.go = "WildRose_Mary_214_1";
			link.l2 = "Yo no estaría tan seguro. Cuando recuerdo, por ejemplo, París, me vienen a la cabeza las calles, los olores... De las personas, sólo me acuerdo de unos pocos; los demás casi han desaparecido de mi memoria, aunque sólo han pasado unos pocos años.";
			link.l2.go = "WildRose_Mary_214_2";
		break;

		case "WildRose_Mary_214_1":
			dialog.text = "Creo que Eric y Aurélie hablaban de la Isla, sí, ¿eh? Y de esa gente que vivía aquí hace mucho, mucho tiempo. Yo era pequeña y no lo entendía, pero ahora... ahora lo comprendo del todo. Porque Antonio, Cécile... y algunos rivados como Chimiseta llevan aquí más tiempo que yo, pero nunca he sido cercana a ninguno de ellos. Los demás: Eric, Aurélie, Alan y muchos otros, están muertos.";
			link.l1 = "Entiendo. El mundo se ha vuelto... un poquito más pequeño, ¿verdad?";
			link.l1.go = "WildRose_Mary_215";
			AddCharacterExpToSkill(pchar, "Sneak", 100);
		break;

		case "WildRose_Mary_214_2":
			dialog.text = "Creo que Eric y Aurélie hablaban de la Isla, sí, ¿eh? Y de aquella gente que vivía aquí, hace mucho, mucho tiempo. Yo era pequeña y no lo entendía, pero ahora lo he comprendido del todo. Porque Antonio, Cécile... y algunos rivados como Chimiseta llevan aquí más tiempo que yo, pero nunca fui cercana a ninguno de ellos. Los demás: Eric, Aurélie, Alan y muchos otros, están muertos.";
			link.l1 = "Entiendo. El mundo se ha vuelto... un poco más pequeño, ¿verdad?";
			link.l1.go = "WildRose_Mary_215";
			AddCharacterExpToSkill(pchar, "Leadership", 100);
		break;

		case "WildRose_Mary_215":
			dialog.text = "Más bien se ha vaciado. Este mundo es lo que está dentro del anillo exterior. Se ha vaciado, sí, ¿eh? Y pronto puede que desaparezca por completo.";
			link.l1 = "¿De qué hablas, Mary?.";
			link.l1.go = "WildRose_Mary_216";
		break;

		case "WildRose_Mary_216":
			dialog.text = "¿No lo sentiste, sí, ¿eh? "+pchar.name+"¿Ahora, cuando estábamos junto a la tumba de Aurélie?";
			link.l1 = "¿Qué exactamente?";
			link.l1.go = "WildRose_Mary_217";
		break;

		case "WildRose_Mary_217":
			dialog.text = "No sé cómo explicarlo. ¿Sabes cómo huele el aire antes de una tormenta? Recuerda: cuando llegaste aquí por primera vez, qué tensión se sentía en el ambiente... Todos estaban listos para arrancarse la garganta, muchos creían oler pólvora y sangre. Después de que mataste a Chad, todo cambió: era como si respirar se hubiera vuelto más fácil... Pero ahora, esa sensación ha vuelto.";
			link.l1 = "Sí, sentí algo parecido. Pero, ¿quizá sea por el ambiente? Al fin y al cabo, es un funeral...";
			link.l1.go = "WildRose_Mary_218_1";
			link.l2 = "Estás agotada, "+npchar.name+". Descansarás y te sentirás mejor. Sí, ¿eh? Y dime, ¿acaso se puede sentir de otra manera en un funeral?";
			link.l2.go = "WildRose_Mary_218_2";
		break;

		case "WildRose_Mary_218_1":
			dialog.text = "Cuando entregábamos al mar a Erik y a muchos otros habitantes de la Isla, no era así, te lo digo. Se sentía una especie de... unión. Pero hoy, algunos casi se miraban como lobos, aunque rezaban la misma oración.";
			link.l1 = "¿Hablas de Leighton y Donald, sí, ¿eh?";
			link.l1.go = "WildRose_Mary_219";
			AddCharacterExpToSkill(pchar, "Commerce", 100);
		break;

		case "WildRose_Mary_218_2":
			dialog.text = "Cuando entregábamos al mar a Erik y a muchos otros habitantes de la Isla, no era así, te lo digo. Se sentía una especie de... unión. Pero hoy, algunos casi se miraban como lobos, aunque rezaban la misma oración.";
			link.l1 = "¿Hablas de Leighton y Donald, sí, ¿eh?";
			link.l1.go = "WildRose_Mary_219";
			AddCharacterExpToSkill(pchar, "Defence", 100);
		break;

		case "WildRose_Mary_219":
			dialog.text = "Así que tú también lo notaste, sí, ¿eh?";
			link.l1 = "Dexter reacciona con nerviosismo ante los intentos de Greenspy de organizar ejercicios, ¿y cómo no?";
			link.l1.go = "WildRose_Mary_220";
		break;

		case "WildRose_Mary_220":
			dialog.text = "Esto no va a acabar bien, sí, ¿eh?";
			link.l1 = "Si es así, hoy no solo se celebró el funeral de Aurélie Bertin, sino también el de esta... Ciudad de los Barcos Abandonados.";
			link.l1.go = "WildRose_Mary_221";
		break;

		case "WildRose_Mary_221":
			dialog.text = "¿La Ciudad de los Barcos Perdidos?";
			link.l1 = "Perdóname, Mary, pero no me atrevo a llamar este lugar la Isla de la Justicia, sí, ¿eh?";
			link.l1.go = "WildRose_Mary_222";
		break;

		case "WildRose_Mary_222":
			dialog.text = "Ahora que he visto el mundo y me he dado cuenta de lo grande que es, este lugar me parece... una prisión, sí, ¿eh? Cuesta creer que crecí aquí.";
			link.l1 = "Y no puedo creer que entre estos restos de barcos pudiera florecer una rosa tan salvaje y hermosa como tú.";
			link.l1.go = "WildRose_Mary_223";
		break;

		case "WildRose_Mary_223":
			dialog.text = "Quiero despedirme de este lugar, "+pchar.name+"... Supongo que no volveremos aquí nunca más, sí, ¿eh?   No quiero volver.   No quiero ver con mis propios ojos lo que podría pasar aquí.";
			link.l1 = "Hablaré con Eddie y Donald. A lo mejor consigo enfriarles un poco los ánimos, sí, ¿eh?";
			link.l1.go = "WildRose_Mary_224";
		break;

		case "WildRose_Mary_224":
			dialog.text = "No lo entiendes... Esto solo retrasará lo inevitable, así que no vale la pena tu esfuerzo. Llegará el día en que volveremos - y aquí\nAsí será mejor, "+pchar.name+", sí... Ya no tengo nada que me retenga aquí.";
			link.l1 = "Como digas, querida. Terminaremos todos los asuntos y nos iremos de aquí para siempre.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap4_PathToLight_20");
		break;
		
		// =================================================================
		// ==================== ЭТАП 5. «ЧУЖИМИ РУКАМИ» ====================
		// =================================================================
		case "WildRose_Mary_231":
			dialog.text = "¿Rupert Casper? ¿Joshua Northwood, sí, ¿eh? ";
			link.l1 = "He estado pensando en eso todo el camino, "+npchar.name+". Y llegué a la conclusión de que tu padre no se habría ocultado bajo un nombre y apellido que ya había usado. Al mismo tiempo, puede que no se atreviera a renunciar a su verdadero nombre o apellido: ¿qué pasaría si en un momento inoportuno no respondiera a un nombre ajeno?";
			link.l1.go = "WildRose_Mary_232";
		break;

		case "WildRose_Mary_232":
			dialog.text = "Podría haberse llamado como quisiera, sí, ¿eh?";
			link.l1 = "Claro que pudo. Y tal vez eso fue exactamente lo que hizo. Si logró sobrevivir en Cuba, a donde llegó en la tartana de los contrabandistas. Si es que llegó, y no terminó como comida para cangrejos en la Isla de la Justicia. Ahora solo nos queda esperar — por suerte, no tanto como la vez anterior. Creo que un mes podremos soportarlo sin problema.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_3");
		break;

		case "WildRose_Mary_235":
			dialog.text = "Mi padre está vivo, "+pchar.name+". ¡Pero si yo siempre lo supe, sí, ¿eh!";
			link.l1 = "Como yo, querida. Bueno, ha llegado la hora de ver a ese Jérôme, sí, ¿eh? Y cuanto antes.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap5_Fadey_7");
		break;
		
		// =================================================================
		// ================= ЭТАП 6. «ЖИЗНЬ ПОСЛЕ СМЕРТИ» ==================
		// =================================================================
		case "WildRose_Mary_241":
			dialog.text = "Por fin hemos llegado, sí, ¿eh? ¿Y ahora qué, "+pchar.name+"?";
			link.l1 = "Hay que encontrar a Jérôme. O está descansando en una habitación de la taberna, o ha alquilado una casita; seguro que tiene dinero para eso, sí, ¿eh?";
			link.l1.go = "WildRose_Mary_242";
		break;

		case "WildRose_Mary_242":
			dialog.text = "Teniendo en cuenta cuánto le pagó Fadéi... Creo que seguramente prefirió la segunda opción.";
			link.l1 = "De acuerdo. Podemos preguntarle por él al dueño del 'Ojo de Cristal', o averiguar algo entre la gente del pueblo. Vamos, el tiempo apremia.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_2");
		break;
		
		case "WildRose_BanditBeliz_1":
			dialog.text = "Veamos, veamos, veamos... Aquí están nuestros tortolitos. Vamos, chicos, hagamos el trabajo y le informamos.";
			link.l1 = "¿Jerome Sauvernier? ¡¿Qué demonios está pasando aquí?!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_5");
		break;
		
		case "WildRose_BanditBeliz_2":
			if (!CharacterIsAlive("WildRose_Bandit_1") && !CharacterIsAlive("WildRose_Bandit_2"))
			{
				dialog.text = "Malditos bastardos, cof-cof. Pero bueno...";
				link.l1 = "Te aconsejo que te muerdas la lengua si te importa tu propio pellejo... ";
				link.l1.go = "WildRose_BanditBeliz_2_1";
				DelLandQuestMark(npchar);
			}
			else
			{
				dialog.text = "...";
				link.l1 = "...";
				link.l1.go = "exit";
			}
		break;
		
		case "WildRose_BanditBeliz_2_1":
			dialog.text = "...";
			link.l1 = "Eso también. Y ahora suéltalo: ¿por qué demonios nos atacaron - y encima junto con Sovereignet...";
			link.l1.go = "WildRose_BanditBeliz_3";
		break;

		case "WildRose_BanditBeliz_3":
			dialog.text = "Ese Sovereigne suyo es un cobarde y codicioso hijo de perra. Bastó con que Casper le diera una buena paliza y luego le prometiera algo de dinero — y el muy arrastrado enseguida escribió la cartita, ja-ja... kja-kja...";
			link.l1 = "Así que de verdad lo encontró.";
			link.l1.go = "WildRose_BanditBeliz_4";
		break;

		case "WildRose_BanditBeliz_4":
			dialog.text = "He encontrado, he encontrado. Así que pronto vas a morir. Igual que tu amiguita. Casper os va a hacer pedazos a los dos, je, je. Yo ya estoy muerto en vida, pero te ayudaré a encontrar tu muerte. Lástima que no escucharé cómo suplicaréis piedad cuando caigáis en sus manos...";
			link.l1 = "Sí, no me queda mucho, eso es cierto. Así que habla rápido, antes de que entregue el alma, sí, ¿eh?";
			link.l1.go = "WildRose_BanditBeliz_6";
		break;

		case "WildRose_BanditBeliz_6":
			dialog.text = "¿Queréis encontrarlo? Id a la bahía de Chetumal, él vive allí. No tendréis que buscarlo, él mismo os encontrará.";
			link.l1 = "Pues perfecto. Ahora puedes morirte cuanto quieras. Y yo me voy.";
			link.l1.go = "WildRose_BanditBeliz_Just_Deth";
			link.l2 = "Eso espero.   Ahora vete al infierno.";
			link.l2.go = "WildRose_BanditBeliz_Hit_Deth";
		break;
		
		case "WildRose_BanditBeliz_Just_Deth":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_8");
		break;
		
		case "WildRose_BanditBeliz_Hit_Deth":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_7");
		break;
		
		case "WildRose_Mary_251":
			dialog.text = "Dios, "+pchar.name+"... ¡No puedo creerlo, simplemente no puedo, sí, ¿eh?! ¿Fue mi padre quien hizo esto?!";
			link.l1 = "Parece que sí, ¿eh? "+npchar.name+". No sé qué les movía ni quién demonios era él... Pero dudo mucho que sea otro Rupert Casper. Esas coincidencias no existen.";
			link.l1.go = "WildRose_Mary_252";
		break;

		case "WildRose_Mary_252":
			dialog.text = "¿Y ahora qué hacemos? ¿Qué le voy a decir cuando lo mire a los ojos?";
			link.l1 = "Primero hay que llegar hasta él. Probablemente se ha puesto fuera de la ley, ya que su búsqueda ha provocado... una reacción tan nerviosa. Pero, sea como sea, sigue siendo tu padre. En cuya búsqueda hemos gastado un montón de esfuerzos, tiempo y dinero.";
			link.l1.go = "WildRose_Mary_253";
		break;

		case "WildRose_Mary_253":
			dialog.text = "¿Pero qué pasa si ni siquiera quiere hablarnos? ¿Por qué ordenó matarnos?";
			link.l1 = "Aunque sea porque él podría no saber quién lo busca exactamente. Fadéi podría haberle dicho solo el nombre y omitir los detalles sobre ti. De lo contrario, creo que ahora no tendríamos que manchar las hojas de sangre.";
			link.l1.go = "WildRose_Mary_254";
		break;

		case "WildRose_Mary_254":
			dialog.text = "¿Y ahora qué? ¿Vamos a ir a la bahía de Chetumal? Pero si nos tendió una trampa aquí... quién sabe qué nos espera allí.";
			link.l1 = "Tenemos ventaja de tiempo, hasta que él se entere de lo que ha pasado aquí. Aprovechémosla. Iremos en barco a la bahía, y para ayudarnos enviaremos un destacamento por tierra al mando de uno de los oficiales.";
			link.l1.go = "WildRose_Mary_255";
		break;

		case "WildRose_Mary_255":
			dialog.text = "Suena razonable, sí, ¿eh? Pero ¿quién lo va a liderar?";
			if (CheckPassengerInCharacter(pchar, "Tichingitu"))
			{
				link.l1 = "Tichingitu. En las peleas en tierra está curtido. Nadie lo hace mejor que él.";
				link.l1.go = "WildRose_Etap6_Tichingitu";
			}
			if (CheckPassengerInCharacter(pchar, "Duran"))
			{
				link.l2 = "Claude. Claro que no le va a hacer mucha gracia, pero bueno, lo superará.";
				link.l2.go = "WildRose_Etap6_Duran";
			}
			if (CheckPassengerInCharacter(pchar, "Tonzag"))
			{
				link.l3 = "Hercule. Él sí que sabe cómo se hacen estas cosas.";
				link.l3.go = "WildRose_Etap6_Tonzag";
			}
			if (CheckPassengerInCharacter(pchar, "Irons"))
			{
				link.l4 = "Tommy. Incluso si algo no sale según lo planeado, ese chico sabrá arreglárselas, créeme.";
				link.l4.go = "WildRose_Etap6_Irons";
			}
			if (CheckPassengerInCharacter(pchar, "Longway"))
			{
				link.l5 = "Longway. No es la primera vez que sigue a un enemigo en la selva.";
				link.l5.go = "WildRose_Etap6_Longway";
			}
			if (!CheckPassengerInCharacter(pchar, "Tichingitu") && !CheckPassengerInCharacter(pchar, "Duran") && !CheckPassengerInCharacter(pchar, "Tonzag") && !CheckPassengerInCharacter(pchar, "Irons") && !CheckPassengerInCharacter(pchar, "Longway"))
			{
				link.l99 = "Alonso. Maneja la espada con destreza, sí, ¿eh? Y tampoco le faltan sesos.";
				link.l99.go = "WildRose_Etap6_Alonso";
			}
		break;
		
		case "WildRose_Etap6_Tichingitu":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Tichingitu");
		break;
		
		case "WildRose_Etap6_Duran":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Duran");
		break;
		
		case "WildRose_Etap6_Tonzag":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Tonzag");
		break;
		
		case "WildRose_Etap6_Irons":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Irons");
		break;
		
		case "WildRose_Etap6_Longway":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Longway");
		break;
		
		case "WildRose_Etap6_Alonso":
			DialogExit();
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_10_Alonso");
		break;
		
		//
		case "WildRose_Tichingitu_1":
			dialog.text = "Tichinguito escucha con atención, capitán "+pchar.name+".";
			link.l1 = "Amigo mío, tienes una misión importante. En la bahía de Chetumal se ha escondido una banda de canallas. Debes rastrearlos y acabar con ellos. Nosotros nos acercaremos en nuestro barco desde el mar.";
			link.l1.go = "WildRose_Tichingitu_2";
		break;

		case "WildRose_Tichingitu_2":
			dialog.text = "";
			link.l1 = "Te toca liderar a nuestro grupo de combatientes y atravesar la selva para salirle a esos canallas por la retaguardia. ¿Tienes alguna pregunta para mí?";
			link.l1.go = "WildRose_Tichingitu_3";
		break;

		case "WildRose_Tichingitu_3":
			dialog.text = "Los indígenas no tienen objeciones. Mañana al mediodía, el grupo estará en posición y esperará allí en emboscada.";
			link.l1 = "Muy bien, Tichingitu. Buena suerte.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Duran_1":
			dialog.text = "¿Me llamabas, capitán?";
			link.l1 = "Tengo un asunto para ti, Claude.";
			link.l1.go = "WildRose_Duran_2";
		break;

		case "WildRose_Duran_2":
			dialog.text = "";
			link.l1 = "Hay que reunir un grupo de combatientes y, al mando de él, llegar a la bahía de Chetumal atravesando la selva. Allí nos espera la banda de cierto Rupert Casper. Quieren darnos una desagradable sorpresa. Pero en realidad la sorpresa se la daremos nosotros, o mejor dicho, tú. Atacarás cuando yo te dé la señal. ¿Alguna pregunta?";
			link.l1.go = "WildRose_Duran_3";
		break;

		case "WildRose_Duran_3":
			dialog.text = "Odio andar por la selva. Pero, como dicen, una orden es una orden. Nos vemos en el lugar, creo que será mañana al mediodía.";
			link.l1 = "Buena suerte, Claude.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Tonzag_1":
			dialog.text = "Te escucho, capitán.";
			link.l1 = "Erkyl, tengo un trabajo para ti.";
			link.l1.go = "WildRose_Tonzag_2";
		break;

		case "WildRose_Tonzag_2":
			dialog.text = "¿Hace falta meterle un par de balas en la cabeza a algún idiota? Eso siempre conmigo, tú ya lo sabes.";
			link.l1 = "Casi acertaste. Tienes que liderar un grupo de combatientes de nuestro barco y guiarlos por la selva hasta la bahía de Chetumal. Allí prepararéis una emboscada para la banda que, según creo, nos estará esperando allí.";
			link.l1.go = "WildRose_Tonzag_3";
		break;

		case "WildRose_Tonzag_3":
			dialog.text = "Pensé que hablabas de un asunto serio, capitán. Pero resulta que casi propones ir a la taberna. Mañana al mediodía, cuenta con que estaremos allí.";
			link.l1 = "Nos vemos allí. Suerte, Hércules.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Irons_1":
			dialog.text = "Ja, capitán, ¿por qué estás tan serio? Pareces de camino a un funeral, sí, ¿eh?";
			link.l1 = "¿Sigues bromeando, Tommy? ¿Quieres que yo también haga una broma? No vas a recibir tu paga de este mes. Ni la del próximo, tampoco. ¿Por qué te pusiste tan tenso?";
			link.l1.go = "WildRose_Irons_2";
		break;

		case "WildRose_Irons_2":
			dialog.text = "Ni bromear se puede...";
			link.l1 = "Todo a su tiempo, Tommy. Eso aún tienes que aprenderlo bien. Ahora escúchame con atención: reúne a tu grupo y avanza por la selva hasta la bahía de Chetumal. Cuando lleguéis, esperad mi señal.";
			link.l1.go = "WildRose_Irons_3";
		break;

		case "WildRose_Irons_3":
			dialog.text = "¿Atravesar la selva? Pero no llegaremos allí antes de mañana al mediodía, sí, ¿eh?";
			link.l1 = "Entonces, nos vemos allí mañana al mediodía. Sin orden, no entres en combate ni abandones tu posición. ¿Entendido? Ya veo que sí. Ahora, manos a la obra.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Longway_1":
			dialog.text = "Longway escucha a usted, señor capitán.";
			link.l1 = "Amigo, tengo una tarea para ti.";
			link.l1.go = "WildRose_Longway_2";
		break;

		case "WildRose_Longway_2":
			dialog.text = "...";
			link.l1 = "Debes liderar el grupo de nuestros hombres que atravesará la selva hasta la bahía de Chetumal. Allí puede haber un enfrentamiento con el enemigo, así que prepara bien a tu gente.";
			link.l1.go = "WildRose_Longway_3";
		break;

		case "WildRose_Longway_3":
			dialog.text = "Longwei entender todo, no preocuparse, señor capitán. Nosotros llegar al lugar más o menos mañana al mediodía.";
			link.l1 = "Ve y ten cuidado.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Alonso_1":
			dialog.text = "¿Me llamaba, capitán?";
			link.l1 = "Sí. Escucha con atención, Alonso.";
			link.l1.go = "WildRose_Alonso_2";
		break;
		
		case "WildRose_Alonso_2":
			dialog.text = "";
			link.l1 = "Tú, al mando de un grupo de combatientes, deberás atravesar la jungla y llegar a la bahía de Chetumal. Allí probablemente nos espera una banda de desgraciados. Tendrás que tomar posiciones y atacarles por la retaguardia a mi señal.";
			link.l1.go = "WildRose_Alonso_3";
		break;

		case "WildRose_Alonso_3":
			dialog.text = "Pan comido, capitán. Pero no desembarquen en la bahía antes del mediodía de mañana — mis muchachos y yo no llegaremos antes.";
			link.l1 = "Prepárate bien, Alonso. Y que Dios nos ayude.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_14");
		break;
		
		case "WildRose_Mary_256":
			dialog.text = "Charles, ¿lo has visto, sí, ¿eh?";
			link.l1 = "Parece que ya nos están esperando. Seguro que están al acecho tras esa curva.";
			link.l1.go = "WildRose_Mary_257";
		break;

		case "WildRose_Mary_257":
			dialog.text = "Pero aún no nos han hecho un colador. Ni siquiera lo intentan, sí, ¿eh?";
			link.l1 = "Tal vez primero quiera hablar con nosotros. No lo provoquemos, vamos nosotros mismos, nuestro grupo nos cubrirá. Vamos, acabemos con todo esto.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_18_1");
		break;
		
		case "WildRose_Rupert_1":
			dialog.text = "¡Quieto! ¡Ni un paso más! Chicos, si ese mocoso se mueve, llenadlo de agujeros. A la chica, ni la toquéis.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_1_add";
			// link.l1.go = "WildRose_Rupert_87";
		break;

		case "WildRose_Rupert_1_add":
			StartInstantDialog("Mary", "WildRose_Rupert_2", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_2":
			dialog.text = "¿Papá?..";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_2_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_2_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_3", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_3":
			sld = CharacterFromID("Mary");
			if (CheckCharacterItem(sld, "hat11")) // У Мэри есть своя шляпа
			{
				dialog.text = "Vaya, he visto mucho en mi larga y dura vida. Siempre pienso que ya nada puede sorprenderme — y siempre me equivoco. Así que lograste sobrevivir allá... Y hasta conservaste el sombrero de Teresa. Ya no creí que alguna vez volvería a verlo.";
				link.l1 = "...";
				link.l1.go = "WildRose_Rupert_3_1_add";
			}
			else
			{
				dialog.text = "Vaya, he visto mucho en mi larga y difícil vida. Cada vez pienso que ya nada puede sorprenderme, y cada vez me equivoco. Así que lograste sobrevivir allí, Julia...";
				link.l1 = "...";
				link.l1.go = "WildRose_Rupert_3_add";
			}
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_1_add":
			StartInstantDialog("Mary", "WildRose_Rupert_3_2", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_3_2":
			dialog.text = "Me la entregó Aurélie, antes de su... fallecimiento.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_3_2_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_2_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_3_3", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_3_3":
			dialog.text = "Qué conmovedor... Estoy a punto de llorar. Y yo que pensaba que Teresa había sido enterrada con ella. No se separaba de ese sombrero ni un segundo desde que se lo regalé. Tu madre, aunque era solo una mesera, tenía un espíritu aventurero que casi se le salía por las orejas. Cuando la encontré durante la toma del 'Fleur-de-Lys', supe de inmediato que Teresa se volvería loca por ella. Le quedaba graciosa, pero a ella no le importaba: solo se lo quitaba para dormir. Pero a ti, Julia, te queda de maravilla.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_3_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_3_add":
			StartInstantDialog("Mary", "WildRose_Rupert_4", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_4":
			dialog.text = "¿Julia? No, se equivoca, me llamo Mary...";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_4_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_4_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_5", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_5":
			dialog.text = "Hmm, ya veo. Así que esos desgraciados se pasaron mis palabras por alto y actuaron por su cuenta. Bueno, no se podía esperar otra cosa de esos perros católicos.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_5_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_5_add":
			StartInstantDialog("Mary", "WildRose_Rupert_6", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_6":
			dialog.text = "¿Usted... Tú... Tú eres de verdad mi padre?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_6_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_6_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_7", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_7":
			dialog.text = "Bueno, si no fuera así, tú y tu amiguito ya estaríais tirados en el suelo, llenos de plomo. Hace tiempo que no creo ni en Dios ni en el Diablo, pero supongo que sí existen. El primero seguro, porque te regaló la cara de Teresa. Y eso te acaba de salvar la vida. Como dicen: los caminos del Señor son inescrutables, ¿sí, eh? ¡Ja, ja, ja!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_7_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_7_add":
			StartInstantDialog("Mary", "WildRose_Rupert_8", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_8":
			dialog.text = "Papi... Yo... yo no entiendo, sí, ¿eh?...";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_8_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_8_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_9", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_9":
			dialog.text = "Pero qué vas a entender tú, sí, ¿eh?...";
			link.l1 = "No parece que esté muy contento de ver a su hija, señor Casper. Y eso que usted mismo la reconoció.";
			link.l1.go = "WildRose_Rupert_10";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_10":
			dialog.text = "No te falta ingenio, chiquillo... ¿Cómo dices que te llamas?";
			link.l1 = ""+GetFullName(pchar)+". Mientras lo buscábamos, nos preguntábamos cómo habría vivido todo este tiempo. Si es que seguía con vida, claro. Pero veo que aquí no le ha ido nada mal, señor... Northwood.";
			link.l1.go = "WildRose_Rupert_11";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_11":
			dialog.text = "Ah, así que incluso llegaron hasta eso. Mis respetos, monsieur come-ranas, ¿qué más puedo decir? — considerando que me aseguré de cortar todos los cabos sueltos.";
			link.l1 = "No solo antes de eso. Sabemos también sobre el 'Cornwall', sobre su carga, y sobre Joshua Casper, cuyo nombre tomaste prestado por un tiempo, y su apellido — al parecer, para siempre.";
			link.l1.go = "WildRose_Rupert_12";
		break;

		case "WildRose_Rupert_12":
			dialog.text = "Bravo (aplaude). Estoy impresionado. ¿Tú solo llegaste a todo esto, o mi adorada criatura también puso su granito de arena?";
			link.l1 = "Sin Mary no lo habría conseguido. Ella quería saberlo todo sobre sus padres. Averiguar el destino de Teresa no fue difícil, pero seguir tu pista nos llevó bastante tiempo...";
			link.l1.go = "WildRose_Rupert_13";
		break;
		
		case "WildRose_Rupert_13":
			dialog.text = "Todo esto es tan tierno que hasta dan ganas de llorar. Bueno, hija, ¿estás satisfecha? ¿Contenta? ¿Quieres abrazar a tu papá?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_13_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_13_add":
			StartInstantDialog("Mary", "WildRose_Rupert_14", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_14":
			dialog.text = "No entiendo, padre... ¿Por qué te burlas de mí? ¿Por qué?! (grita) ¡Si fuiste tú quien me dejó allí, entre esos restos de barcos! Y luego ni siquiera pensaste en volver, sí, ¿eh? ¿Por qué? ¿Quién eres tú en realidad, quiénes son esas personas detrás de ti?";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_14_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_14_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_15", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_15":
			dialog.text = "Dime, "+pchar.lastname+", ¿ella suele ponerse así de histérica? Eso lo sacó de su madre. Teresa era una chica maravillosa, la mejor que he conocido. Pero le encantaba llorar y armar berrinches, sí, ¿eh?... Qué te voy a decir... irlandesa.";
			link.l1 = "¡No se atrevan a insultarla! Mary no tiene la culpa de sus desgracias y desde luego no merece que la traten así.";
			link.l1.go = "WildRose_Rupert_16";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;
		
		case "WildRose_Rupert_16":
			dialog.text = "¿¡Pensaste en callarme, mocoso?!";
			link.l1 = "Al contrario. Quiero que nos cuente su historia. Para Mary es muy importante saberla. Pero no voy a permitir que la humille. Así que contrólese.";
			link.l1.go = "WildRose_Rupert_17";
		break;
		
		case "WildRose_Rupert_17":
			dialog.text = "¿Crees que tengo muchas ganas de llorarte en el hombro? Mi vida salió como salió y, como decís vosotros, papistas, — Dios es testigo — no me arrepiento de nada. Excepto de haber perdido a Teresa entonces — por su culpa. ¿Te odio, hija mía? Puede que alguna vez fuera así, pero ahora me importas un comino.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_17_add";
		break;

		case "WildRose_Rupert_17_add":
			StartInstantDialog("Mary", "WildRose_Rupert_18", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_18":
			dialog.text = "¿Tú me culpas de la muerte de mamá?! Tú... ¿De qué soy culpable: de haber nacido, sí, ¿eh? Está bien, padre, "+pchar.name+", tienes razón - cuéntanoslo todo, y luego nos daremos la vuelta y nos iremos. Y yo nunca más volveré a aparecer ante ti, ya que tú... (empieza a llorar).";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_18_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_18_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_19", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_19":
			dialog.text = "Vaya, eres igualita a Teresa. Es como si hubiera vuelto veinte años atrás, ja-ja. Maldita sea. No quería recordar todo esto... Así que, si al final de esta historia decido meterte una bala en la frente, querida — será culpa tuya.";
			link.l1 = "Entonces la bala la recibirá usted también, Rupert. Y me parece que eso no entra en sus planes, porque usted parece una persona que valora su vida.";
			link.l1.go = "WildRose_Rupert_20";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_20": //
			dialog.text = "Sé lo que vale, chico. Pero eso es otra cosa. ¿Y cómo esperas que lo entienda alguien como tú? En fin, vayamos al grano. ¿Quieren saber todo sobre mí? Muy bien. Nací en una granja, cerca de Eastbourne — un pueblucho en la costa del Canal de la Mancha — en 1611. Tal vez un año antes o después — mi vieja siempre se equivocaba con las fechas, lo cual no sorprende, considerando la cantidad de alcohol que se metía entre pecho y espalda.";
			link.l1 = "¿Infancia difícil? Entiendo.";
			link.l1.go = "WildRose_Rupert_21";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_21":
			dialog.text = "Si querías saberlo, escucha con la boca cerrada y sin hacerte el gracioso. No tuve padre, y ni siquiera sabía por qué — pero, a diferencia de ti, muchachita, no me importaba. El apellido que me dejó me servía perfectamente. Cuando tenía trece años, una noche desembarcaron corsarios de Dunkerque en la costa. Sí, hoy en día a nadie le gusta recordar eso, pero no sólo los holandeses sufrieron con ellos — también nosotros, los que vivíamos en la costa este de la vieja Inglaterra.";
			link.l1 = "He oído hablar de eso. Esos tipos no perdonaban a nadie. ¿Cómo lograste sobrevivir?";
			link.l1.go = "WildRose_Rupert_22_1";
			link.l2 = "Conozco sus atrocidades. No tuvieron piedad de nadie, ni de ancianos ni de niños. Por eso me sorprende aún más que hayas logrado salir de allí.";
			link.l2.go = "WildRose_Rupert_22_2";
		break;

		case "WildRose_Rupert_22_1":
			dialog.text = "Esa noche esa escoria papista quemó varias granjas, incluida la nuestra. Yo logré salir, pero mi madre, que se había atiborrado de sidra tanto que no podía ni levantar su trasero gordo de la cama, se quemó allí mismo. Ella misma tuvo la culpa, claro, pero aun así era mi madre.";
			link.l1 = "¿Y entonces odiaste a todos los papistas?";
			link.l1.go = "WildRose_Rupert_23";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Rupert_22_2":
			dialog.text = "Esa noche esa escoria papista quemó varias granjas, incluida la nuestra. Yo logré escapar, pero mi madre, que se había atiborrado de sidra tanto que no podía levantar su trasero gordo de la cama, se quemó allí mismo. Fue culpa suya, claro, pero aun así era mi madre.";
			link.l1 = "¿Y entonces odiaste a todos los papistas?";
			link.l1.go = "WildRose_Rupert_23";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_23":
			dialog.text = "Fue entonces cuando aprendí a odiar el hambre, graciosillo. Tú seguramente no sabes lo que es eso, pero yo lo viví en carne propia. Me fui al norte, a la capital, donde me alisté en la marina — allí repartían más latigazos que comida, pero con un par de docenas bastó para que espabilara, y luego le tomé el gusto — llegué a amar la vida a bordo. Más aún, porque aburrirse no era una opción...";
			link.l1 = "Sí, ¿eh? Lo creo sin dudar. La fama de la flota inglesa la precede.";
			link.l1.go = "WildRose_Rupert_24";
		break;

		case "WildRose_Rupert_24":
			dialog.text = "En 1633 aprobé el examen para el rango de teniente y recibí mi destino en la goleta 'Cornwall'.";
			link.l1 = "Bajo el mando de Joshua Casper.";
			link.l1.go = "WildRose_Rupert_26";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_26":
			dialog.text = "Oh, sííí... Joshua Casper... No había una escoria igual en toda la maldita flota, sí, ¿eh? Han pasado tantos años, y ese desgraciado todavía me visita en sueños.";
			link.l1 = "¿Y en qué se destacó? ¿Te ponía de guardia extra por demasiado celo? ¿O en secreto era papista?";
			link.l1.go = "WildRose_Rupert_27";
		break;

		case "WildRose_Rupert_27":
			dialog.text = "Este cruel canalla entrenaba a la tripulación hasta tal punto que la gente, de puro agotamiento, empezaba a caer por la borda. Si sabes su nombre y que fue comandante del 'Cornwall', seguro que viste sus papeles: relucientes, como el culo de un gato recién lamido. Nuestro heroico Joshua tenía una caja entera de medallas. Muchos muchachos ingenuos como tú soñaban con servir bajo su mando —y mira que no te miento, a vosotros, los franceses, os segaba como una hoz afilada la hierba mojada tras la lluvia— pero, al llegar al 'Cornwall', muy pronto se daban cuenta de su error. Estábamos mortalmente cansados de soportarlo, "+pchar.lastname+". Alguien incluso escribió peticiones de traslado, pero desaparecían en los estantes del Almirantazgo o en sus hornos. Sin embargo, la vida aún nos dio una oportunidad: no nos trasladaron a nosotros del 'Cornwall', sino a otro, a él. John Lawson, el favorito de Cromwell, seguro que has oído hablar de él.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_28";
		break;

		case "WildRose_Rupert_28":
			dialog.text = "Ya entonces sabía cómo lamerle el trasero a cualquiera — y puede que él y Casper hubieran acabado llevándose bien, pero yo no lo permití. Le tendí una trampa al pequeño Johnny, y Joshua, sin entender nada, le dio una paliza con su bastón, ciego de rabia.";
			link.l1 = "Una verdadera humillación para un oficial. ¿Y Lawson se lo contó todo a mi padre?";
			link.l1.go = "WildRose_Rupert_32";
		break;

		case "WildRose_Rupert_32":
			dialog.text = "Por supuesto. Pero, verás, el sistema no puede devorarse a sí mismo. El asunto nunca salió a la luz — a Lawson le ofrecieron un ascenso anticipado, y a Joshua y al 'Cornwall' los mandaron a la sombra — nos trasladaron de Londres a Plymouth, en el sur de Inglaterra. Podríamos haber seguido infundiendo miedo a ustedes, los tragadores de ranas, pero al 'Cornwall' lo convirtieron en un buque de intendencia que transportaba suministros militares a Dundalk, un pueblucho irlandés.";
			link.l1 = "¿Y fue allí donde conociste a Teresa?";
			link.l1.go = "WildRose_Rupert_33";
		break;

		case "WildRose_Rupert_33":
			dialog.text = "En nuestra primera visita allí. Teresa O'Fatt, como ya te dije, era camarera en una de las tabernas locales. Nos bastaron tres días para darnos cuenta de que estábamos hechos el uno para el otro. Creo que aquí también me entenderás, "+pchar.lastname+", ¿verdad?";
			link.l1 = "Supongo que sí, ¿eh?";
			link.l1.go = "WildRose_Rupert_34_1";
			link.l2 = "Mirándote ahora, no diría que conoces la palabra 'amor'.";
			link.l2.go = "WildRose_Rupert_34_2";
		break;

		case "WildRose_Rupert_34_1":
			dialog.text = "No he conocido a nadie más hermosa – ni antes, ni en los veinte años que siguieron. Creo que por primera vez en mi vida me sentí realmente feliz, y ella también – o al menos eso decía.";
			link.l1 = "¿Y le propusiste irse contigo?";
			link.l1.go = "WildRose_Rupert_35";
			AddCharacterExpToSkill(pchar, "Fortune", 100);
		break;

		case "WildRose_Rupert_34_2":
			dialog.text = "No he conocido a nadie más hermosa - ni antes, ni en los veinte años siguientes. Creo que por primera vez en mi vida me sentí verdaderamente feliz, y ella también - o al menos eso decía.";
			link.l1 = "¿Y le propusiste irse contigo?";
			link.l1.go = "WildRose_Rupert_35";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;

		case "WildRose_Rupert_35":
			dialog.text = "Por supuesto que no — era imposible, el 'Cornwall' seguía siendo un buque de guerra con un bastardo de capitán al mando. Después de una semana que nos pareció una eternidad, nuestro bergantín zarpó de vuelta a Plymouth. Regresamos a Dundalk dos meses después — y Teresa me dejó de piedra con la noticia: estaba embarazada.";
			link.l1 = "Sí, eso pasa cuando acuestas a una chica en la cama, sí, ¿eh?";
			link.l1.go = "WildRose_Rupert_36";
		break;

		case "WildRose_Rupert_36":
			dialog.text = "No te hagas el listo, gabacho. Teresa lloraba en mi hombro, y yo pensaba qué hacer con eso. Quería quedarme con ella, de verdad lo quería — pero ya entonces sentía que de esa criatura no saldría nada bueno. Intenté convencer a Teresa de deshacerse de ella, antes de que fuera demasiado tarde — pero en vez de eso me topé con un ataque de histeria aún más feroz. No supimos qué hacer entonces — decidimos esperar dos meses más, hasta el próximo regreso del 'Cornwall' a Dundalk, porque en ese momento el Almirantazgo aún no había cambiado su ira hacia Casper por clemencia\nTras nuestro regreso no la encontré de inmediato — el embarazo de Teresa ya era evidente, y, según me dijo el posadero donde trabajaba, su miserable padre la había apaleado y encerrado bajo llave en la casa. No hace falta decir que arreglé cuentas con ese hijo de perra de tal forma que casi vomitó sus propias entrañas. Por supuesto que no había opción de que continuara viviendo en esa casa.";
			link.l1 = "¿Y la trajisteis al 'Cornualles'?";
			link.l1.go = "WildRose_Rupert_37";
		break;

		case "WildRose_Rupert_37":
			dialog.text = "La decisión hubo que tomarla rápido. Entendía que Casper no toleraría a una mujer a bordo, y pensaba, la noche siguiente a zarpar, robar un bote y llegar con él hasta Dublín, que justo nos quedaría a estribor.";
			link.l1 = "¿Y qué pasó? ¿Os atraparon?";
			link.l1.go = "WildRose_Rupert_38";
		break;

		case "WildRose_Rupert_38":
			dialog.text = "Exactamente. Casper ya se había empinado una ración de whisky y no quería escuchar a nadie — ordenó simplemente tirar a la chica por la borda. Por más que le rogué, solo se reía a carcajadas — maldita sea, lo estoy contando y todavía escucho su risa en mi cabeza...";
			link.l1 = "¿Y entonces decidisteis amotinaros?";
			link.l1.go = "WildRose_Rupert_39";
		break;

		case "WildRose_Rupert_39":
			dialog.text = "No me quedaba otra opción. Le quité la pistola del cinturón al vigía que tenía al lado y le volé la frente al bastardo. Enseguida estalló una masacre a bordo — nadie quería al capitán, pero el miedo al tribunal era más fuerte. Casi un tercio de la tripulación murió — cuando por fin recuperamos el control, la cubierta del 'Cornwall' estaba bañada en sangre y cubierta de los cadáveres de nuestros propios compañeros.";
			link.l1 = "Después de eso, claro que decidisteis no volver a Inglaterra. Allí os esperaba la horca, ¿sí, eh?";
			link.l1.go = "WildRose_Rupert_40";
		break;

		case "WildRose_Rupert_40":
			dialog.text = "Estaba seguro de que guiaría la 'Cornwell' a través del océano. Aquí nuestras caras no eran conocidas por nadie, y eso nos dio la oportunidad de comenzar una nueva vida. Convencer a los otros oficiales no fue difícil — importó menos mi autoridad que el contenido de un par de cofres, que los marineros comunes no sabían. La tripulación decidió que Joshua Kasper debía vivir. Nosotros, los oficiales de las montañas, decidimos ganar tiempo, sacrificar uno de los cofres y atracar en Antigua, donde asumiría su nombre. Luego planeábamos poner rumbo a Providence.\n Y así fue: nadie sospechó el cambio. Pero cuando faltaban solo un par de días para Providence, algún bastardo habló sobre el segundo cofre — y eso provocó una división en la tripulación.";
			link.l1 = "¿Ahora han levantado una rebelión contra ti?";
			link.l1.go = "WildRose_Rupert_45";
		break;

		case "WildRose_Rupert_45":
			dialog.text = "No, pero el número de quienes querían seguir sirviendo a nuestro glorioso rey disminuyó drásticamente. Tampoco había muchos dispuestos a hacerse piratas. Así que encontramos una opción intermedia: decidimos echar el ancla en uno de los puertos franceses. Allí planeábamos vender el barco, repartir el dinero obtenido por él y el que había en el cofre, y después, separarnos.";
			link.l1 = "¿Y no le importó tener que vivir entre esos católicos a los que tanto odia?";
			link.l1.go = "WildRose_Rupert_46";
		break;

		case "WildRose_Rupert_46":
			dialog.text = "Ya me daba igual dónde desembarcar. Teresa, aunque se esforzaba por aparentar entereza, se sentía como cualquier mujer embarazada tras tres meses seguidos de mareo constante. Y, al igual que tres meses antes, no tenía nada en contra de estar entre católicos — con tal de estar a su lado.";
			link.l1 = "Pero en el noroeste del mar Caribe no hay ni ha habido asentamientos franceses.";
			link.l1.go = "WildRose_Rupert_47";
		break;

		case "WildRose_Rupert_47":
			dialog.text = "Para cuando la situación a bordo del 'Cornualles' llegó al punto de ebullición, ya habíamos recorrido la mitad del camino con viento favorable, que ahora ya no nos permitía poner rumbo a San Cristóbal...";
			link.l1 = "¿Y han elegido Tortuga como destino?";
			link.l1.go = "WildRose_Rupert_48";
		break;

		case "WildRose_Rupert_48":
			dialog.text = "En aquellos años, aún era solo una aldea. Para retrasar una posible persecución por parte de las autoridades, cambiamos la tablilla de popa con el nombre del bergantín; así, el 'Cornwall' se convirtió en el 'Wrangler'.";
			link.l1 = "Pero, por alguna razón, nunca llegasteis a la Tortuguita. No pudieron haberse equivocado tanto de rumbo como para acabar al oeste de Cuba en vez de Tortuga, ¿verdad?";
			link.l1.go = "WildRose_Rupert_49";
		break;

		case "WildRose_Rupert_49":
			dialog.text = "Para que lo sepas, soy una navegante experimentada, muy por encima de muchos otros. No hubo ningún error, manteníamos el rumbo exactamente al norte. Pero apenas entramos en el Estrecho de Barlovento, se desató un vendaval terrible. Todavía me pregunto por qué milagro no nos estrellamos contra la costa cubana, sino que nos arrastró a lo largo de ella...";
			link.l1 = "Un verdadero milagro, no hay otra explicación.";
			link.l1.go = "WildRose_Rupert_50";
		break;

		case "WildRose_Rupert_50":
			dialog.text = "Abrazando a la llorosa Teresa, rogaba fervientemente al Señor, suplicándole que nos enviara la salvación. Y vaya que nos echó una mano.";
			link.l1 = "Has llegado a la Isla de la Justicia.";
			link.l1.go = "WildRose_Rupert_51";
		break;

		case "WildRose_Rupert_51":
			dialog.text = "¿Justicia? ¡Oh, sí! El 'Wrangler' se partió en dos al chocar contra los arrecifes, pero de forma asombrosa se mantuvo a flote — lo suficiente como para ser arrastrado hasta una pila de otros barcos encallados unos sobre otros. La tormenta rugió casi dos días más, y cuando finalmente se calmó — los habitantes de esa pobre islita nos rescataron.";
			link.l1 = "A usted, a Teresa y a otros dos marineros. De lo que pasó después, tenemos una idea. Mejor cuéntenos cómo logró salir de la cárcel y abandonar la isla.";
			link.l1.go = "WildRose_Rupert_63";
		break;

		case "WildRose_Rupert_63":
			dialog.text = "Hubiera sido mejor que me fusilaran en ese momento... Si hubiera sabido lo que me esperaba, me habría encadenado yo mismo a los barrotes y no me habría movido.";
			link.l1 = "¿De verdad la tartana no era tan cómoda como el bergantín, sí, ¿eh? "+npchar.name+"?";
			link.l1.go = "WildRose_Rupert_64_1";
			link.l2 = "No me digan que encima se metieron en una tormenta en una tartana.";
			link.l2.go = "WildRose_Rupert_64_2";
		break;

		case "WildRose_Rupert_64_1":
			dialog.text = "¿Tartana? Ja, ja, ja... Sí, ese era mi plan. Creía haber tenido suerte. El jefe de la guardia de la prisión resultó ser un antiguo oficial de la Marina inglesa, que se compadeció de mi situación. Él fue quien me habló de las tartanas de los contrabandistas cubanos, y de que me querían ejecutar. Tal vez se le pueda llamar un hombre de honor — él mismo propuso dejarme ir para que me entregara al destino.";
			link.l1 = "No lo entiendo... Si no fue en tartanas, ¿entonces cómo salieron de la isla?";
			link.l1.go = "WildRose_Rupert_68";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_64_2":
			dialog.text = "¿Tartana? Ja-ja-ja... Sííí, ese era mi plan. Creía que había tenido suerte. El jefe de la guardia de la prisión resultó ser un exoficial de la marina inglesa, que se conmovió con mi desgracia. Fue él quien me habló de las tartanas de los contrabandistas cubanos y de que planeaban ejecutarme. Supongo que podría llamársele un hombre de honor: él mismo se ofreció a dejarme salir, para que pusiera mi destino en manos del azar.";
			link.l1 = "No entiendo... Si no fue en tartanas, ¿entonces cómo dejaron la isla?";
			link.l1.go = "WildRose_Rupert_68";
			AddCharacterExpToSkill(pchar, "sneak", 100);
		break;
		
		case "WildRose_Rupert_68":
			dialog.text = "Si te callas y escuchas, lo entenderás. Nadé hacia las tartanas, nadé durante mucho tiempo — hasta que, a través de la cortina de lluvia, vi una luz. Era algo absolutamente increíble, maldita sea. Brillaba como el sol en la cubierta de uno de los galeones medio hundidos, y me dirigí hacia ella. Aún sin saber que estaba cometiendo el peor error de mi vida. Subí por la escala del costado — y allí estaba, frente a la luz. Resplandecía sobre una estatua de oro y...";
			link.l1 = "El ídolo de Kukulkán. Sí, ¿eh?, en aquel entonces el 'San Jerónimo' aún no se había hundido...";
			link.l1.go = "WildRose_Rupert_69";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), pchar);
		break;

		case "WildRose_Rupert_69":
			dialog.text = "Así que tú también lo viste, "+pchar.lastname+"?";
			link.l1 = "No solo lo vi. Me desplacé por el espacio con su ayuda, y más de una vez.";
			link.l1.go = "WildRose_Rupert_70";
		break;

		case "WildRose_Rupert_70":
			dialog.text = "¡Mientes! ¿Dices que varias veces, eh?! ¿¡Entonces cómo puedes estar aquí, tan lleno de vida?!";
			link.l1 = "Después de trasladarme, bebí una poción india, y fue eso lo que me ayudó a sobrevivir y recuperar fuerzas.";
			link.l1.go = "WildRose_Rupert_71";
		break;

		case "WildRose_Rupert_71":
			dialog.text = "Ah, ya veo cómo es. ¿Y sabes cuánto tiempo estuve recuperando fuerzas? ¿Lo sabes?!";
			link.l1 = "Me lo imagino. Tocaste el ídolo, y te llevó a Dominica, a la aldea de los indios, allí te ofrecieron como sacrificio a la estatua y acabaste en el Main, ¿verdad?";
			link.l1.go = "WildRose_Rupert_72";
		break;

		case "WildRose_Rupert_72":
			dialog.text = "Exacto. Nunca antes había sentido tanto dolor como en aquel momento, tirado junto a esa estatua. No sé con qué compararlo. Tal vez, ni siquiera si una casa de piedra se te cayera encima experimentarías semejante sufrimiento. Apenas recobré el sentido, vi venir de nuevo a un grupo de aborígenes. Si hubiese hablado su lengua — lo juro, les habría rogado que me mataran ahí mismo.";
			link.l1 = "¿Eran misquitos de la aldea cercana?";
			link.l1.go = "WildRose_Rupert_76";
		break;

		case "WildRose_Rupert_76":
			dialog.text = "Ellos mismos. Me arrastraron hasta una de las chozas, donde un aborigen extraño, que no se parecía a los demás, me echó algo directamente en la boca. El dolor se calmó un poco, pero no desapareció del todo. Al anochecer me sacaron junto a la hoguera, y ese desgraciado pintarrajeado comenzó a hacer algún tipo de ritual. Un maldito bastardo.";
			link.l1 = "El Ojo de Serpiente... Deberías estarle agradecido por salvarte el pellejo.";
			link.l1.go = "WildRose_Rupert_77";
		break;

		case "WildRose_Rupert_77":
			dialog.text = "¿Salvarme?.. Tres años, "+pchar.lastname+". Durante tres años estuve casi sin moverme, defecando y orinando debajo de mí, despertando en mi propio vómito, porque ya no soportaba todas esas pociones y tinturas apestosas que me obligaban a tragar a la fuerza. ¡Y luego pasé casi un año más aprendiendo a caminar de nuevo!";
			link.l1 = "Una historia desgarradora. Pero en serio, hasta me dan lástima, sí, ¿eh?";
			link.l1.go = "WildRose_Rupert_78";
		break;

		case "WildRose_Rupert_78":
			dialog.text = "Métete tu lástima por el culo católico y gordo de tu Papa. No necesito la compasión de nadie. ¿Sigo, o necesitas un rato para llorar, mocoso?";
			link.l1 = "Este viaje no le ha añadido modales, desde luego. Pero bueno, por Mary lo aguantaré. Aunque lo principal, supongo, ya lo hemos averiguado — aun así, le escucharemos hasta el final.";
			link.l1.go = "WildRose_Rupert_79";
		break;

		case "WildRose_Rupert_79":
			dialog.text = "Me alcé como pude y abandoné esa maldita aldea hasta llegar a la costa, a la bahía de Amatique. Allí encontré contrabandistas cuyo barco había echado ancla cerca, y me uní a ellos, llamándome Rupert Casper — no renuncié a mi nombre, pero sí mantuve el apellido de uno de los culpables de todas mis desgracias. Para no olvidar por qué terminé aquí.";
			link.l1 = "Siempre culpas a los demás, Northwood... Menos a ti mismo. Aunque se puede entender — años de humillaciones y sufrimiento, y ahora te escondes en estos bosques. ¿Cómo no volverte loco aquí?";
			link.l1.go = "WildRose_Rupert_80_1";
			link.l2 = "Has pasado por mucho, Northwood — no lo niego. Y mira dónde terminaste... En los bosques, al borde de la civilización. Aquí, ¿cómo no perder la cabeza?";
			link.l2.go = "WildRose_Rupert_80_2";
		break;

		case "WildRose_Rupert_80_1":
			dialog.text = "Soy el dueño de estos bosques, "+pchar.lastname+". En más de quince años, recorrí el camino desde un simple marinero en un barco de contrabandistas hasta convertirme en su jefe. No el capitán de un barquito cualquiera, sino el dueño de toda la costa, desde la bahía de Amatique hasta el golfo de la Perdición.";
			link.l1 = "Bueno, un renacimiento digno, lo reconozco.";
			link.l1.go = "WildRose_Rupert_81";
			AddCharacterExpToSkill(pchar, "leadership", 100);
		break;

		case "WildRose_Rupert_80_2":
			dialog.text = "Yo soy el dueño de estos bosques, "+pchar.lastname+". Durante más de quince años recorrí el camino desde un simple marinero en un barco de contrabandistas hasta convertirme en su jefe. No el capitán de algún barquito, sino el dueño de toda la costa, desde la bahía de Amatique hasta el golfo de la Perdición.";
			link.l1 = "Bueno, un renacimiento digno, lo reconozco.";
			link.l1.go = "WildRose_Rupert_81";
			AddComplexSelfExpToScill(100, 100, 100, 100);
		break;
		
		case "WildRose_Rupert_81":
			dialog.text = "Algunos dicen que estas son tierras del Demonio del Bosque... ¡Una vil mentira! Estas son mis tierras. Y Svenson lo sabe, ja-ja-ja. Más de una vez ha enviado aquí a sus hombres para averiguar quién soy — y ninguno ha regresado con vida, je-je. Se pueden contar con los dedos de una mano los que conocen el nombre con el que empecé mi carrera como contrabandista... y el lugar exacto de estos bosques donde vivo.";
			link.l1 = "Así que ahora se hacen llamar de otra manera. Ahora entiendo por qué la noticia de que alguien anda buscando a Rupert Casper les puso tan nerviosos, sí, ¿eh?";
			link.l1.go = "WildRose_Rupert_82";
		break;
		
		case "WildRose_Rupert_82":
			dialog.text = "¿Pánico? ¿En serio, chico? El único que está entrando en pánico aquí eres tú, en mi territorio, rodeado de mi gente, completamente bajo mi control. Puedo hacer contigo lo que me dé la gana. Y con ella también, solo porque fue la causa de todas esas penurias que tuve que pasar.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_82_add";
		break;

		case "WildRose_Rupert_82_add":
			StartInstantDialog("Mary", "WildRose_Rupert_83", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_83":
			dialog.text = "Estás loco, simplemente loco y ya está, sí, ¿eh? No conozco medicina ni médico capaz de curarte, ¡Rupert Northwood! Has pasado por tormentos terribles, pero... ¿cómo puedes culparme de todo a mí?!";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_83_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;

		case "WildRose_Rupert_83_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_84", "Quest\CompanionQuests\WildRose.c");
		break;

		case "WildRose_Rupert_84":
			dialog.text = "Ya te lo dije: si no hubieras estado tú, nada de esto habría pasado. Solo admítelo, y ya está.";
			link.l1 = "...";
			link.l1.go = "WildRose_Rupert_84_add";
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Rupert_84_add":
			StartInstantDialog("Mary", "WildRose_Rupert_85", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_85":
			dialog.text = "...";
			link.l1 = "Déjalo, "+npchar.name+". Ya hemos oído suficiente. Hay caminos que de verdad no merece la pena recorrer hasta el final. Tenía un mal presentimiento cuando decidimos meternos en todo esto. Pero no le hice caso. Qué lástima.";
			link.l1.go = "WildRose_Rupert_85_add";
		break;
		
		case "WildRose_Rupert_85_add":
			StartInstantDialog("WildRose_Rupert", "WildRose_Rupert_86", "Quest\CompanionQuests\WildRose.c");
		break;
		
		case "WildRose_Rupert_86":
			dialog.text = "Sí-i-i, entonces los dos no estaríais aquí, atrapados, sin poder hacer nada. Siente ahora en tu propia piel, hijita, lo que yo sentí.";
			link.l1 = "¿Y quién te dijo que somos incapaces de hacer algo? ¡Desple-e-e-gue, al combate!";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_20");
		break;
		
		case "WildRose_Rupert_87":
			dialog.text = "¿Qué pasa, novato? ¿Perdiste a alguien? Ja-ja-ja... Ja-ja-ja. ¡¡¡JA-JA-JA-JA-JA-JA!!! Oh, si pudieras ver tu cara ahora mismo, idiota. Eh, Mason, trae aquí mi regalo para nuestros invitados.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_22");
		break;
		
		case "WildRose_Rupert_88":
			dialog.text = "...";
			link.l1 = "¡Canalla! ¿Dónde están mis hombres?";
			link.l1.go = "WildRose_Rupert_89";
		break;
		
		case "WildRose_Rupert_89":
			dialog.text = "¿Hablas de ese puñado de idiotas que pensaron tenderme una emboscada? Mi amigo el tabernero me avisó a tiempo de tu llegada a la ciudad, y los recibí como se debe... Algunos lograron escabullirse. Pero no te preocupes, capturé a uno con vida. Para que veas con tus propios ojos el destino que les espera hoy.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_25");
			
			// WildRose_Etap6_LifeAfterDeath_24_1();
		break;
		
		case "WildRose_Rupert_90":
			dialog.text = "¡Canalla! ¡Vas a pagar por esto! (llora) ¡Lo juro, sí, ¿eh?!";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_29");
			CharacterTurnByChr(CharacterFromID("WildRose_Rupert"), CharacterFromID("Mary"));
			CharacterTurnByChr(CharacterFromID("Mary"), CharacterFromID("WildRose_Rupert"));
		break;
		
		case "WildRose_Alonso_11":
			dialog.text = "...";
			link.l1 = "¡Alonso! ¡Qué alegría verte!";
			link.l1.go = "WildRose_Alonso_12";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Alonso_12":
			dialog.text = "¡Qué alegría verlo, capitán! Ese miserable alguien le susurró que lo buscaban — y nos recibieron a cañonazos casi a mitad del camino. Con unos cuantos hombres logré retroceder, y corrimos al puerto para dar la voz de alerta. Por suerte, el vigilante de guardia, al ver el barcazo que compré apresuradamente en la ciudad, comprendió enseguida de qué iba todo esto. Rápidamente reunió gente — y partimos aquí para socorrer.";
			link.l1 = "Gracias, amigo. Nos has salvado de una muerte segura.";
			link.l1.go = "WildRose_Alonso_13";
		break;

		case "WildRose_Alonso_13":
			dialog.text = "Sin importancia. ¿Qué vamos a hacer ahora, capitán?";
			link.l1 = "Reúne a la gente y vayan al barco. Mary y yo necesitamos estar a solas.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		case "WildRose_Mary_261":
			dialog.text = "Dios mío, "+pchar.name+"... Todavía no puedo, simplemente no puedo creerlo. Mi padre... Es un monstruo... ¿Por qué me hace esto? ¿De verdad se ha vuelto loco?";
			link.l1 = "Tuvo que pasar por sufrimientos terribles. El motín en el 'Cornualles', la huida a través del Atlántico, la tormenta y la muerte de tu madre. No me imagino cómo logró sobrevivir al viaje por los portales de esos ídolos sin la poción de los comanches — pero eso fue lo que acabó con su cordura.";
			link.l1.go = "WildRose_Mary_262";
			locCameraFromToPos(-3.80, 1.10, 52.00, false, 0.61, 0.27, 49.69);
			LAi_ActorAnimation(pchar, "sharle_mary_sit", "", 50.0);
			LAi_ActorAnimation(npchar, "sharle_mary_sit", "", 50.0);
			CharacterTurnAy(pchar, 6.00);
			CharacterTurnAy(npchar, 6.00);
		break;

		case "WildRose_Mary_262":
			dialog.text = "¿Y si él siempre fue así? ¿O era igual de canalla, solo un poco más suave, pero amaba sinceramente a mi madre? ¿Y si estos acontecimientos solo liberaron lo que llevaba dentro? Y si es así... ¿qué tal si yo también tengo algo de él? Eso también puede ser, "+pchar.name+", ¿sí, eh?";
			link.l1 = "Definitivamente has heredado algo de él, "+npchar.name+". En la batalla de hoy lo noté — luchas con la misma determinación, con ese fuego en los ojos y con esa furia que lo caracterizaba. Pero no tienes su locura. Tú eres diferente. Viva, abierta, con el corazón en la mano. Y por eso me enamoré de ti. Y parece que Northwood tenía razón: en carácter, te pareces más a tu madre.";
			link.l1.go = "WildRose_Mary_263";
		break;

		case "WildRose_Mary_263":
			dialog.text = "¿De verdad lo piensas así, cariño?";
			link.l1 = "Por supuesto, mi amor. Si lo hubiera conocido así, sin saber quién es, nunca habría pensado que sois parientes.";
			link.l1.go = "WildRose_Mary_264";
		break;

		case "WildRose_Mary_264":
			dialog.text = "Sabes, en la Isla de la Justicia no hay tantas diversiones. Desde niña me enamoré de la esgrima: primero luchaba con los chicos, con palos de madera, y luego ya con hombres adultos, con espadas de verdad, sí, ¿eh? Siempre quise estar a la par con ellos... pero como si siempre me sintiera más débil, incluso cuando salía ganando.   Entonces simplemente volvía a casa y seguía practicando. Entrenaba durante horas, hasta que las manos me empezaban a temblar, sí, ¿eh? ¿Es ese el fuego? ¿Esa furia de la que hablas?";
			link.l1 = "En cierto modo, sí. Me parece que ese fuego te da mucha más fuerza de la que tú misma ves en ti. Y, quieras o no, es un don de tu padre. Aunque él no tuviera intención de regalarte nada.";
			link.l1.go = "WildRose_Mary_265";
			locCameraSleep(false);
			locCameraFromToPos(-1.95, 1.81, 48.29, true, -2.11, -0.04, 52.55);
		break;

		case "WildRose_Mary_265":
			dialog.text = "¿Crees que hicimos bien en remover el pasado, sí, ¿eh?";
			link.l1 = "Ahora que lo sabemos todo... no parece una idea tan buena. Pero si quieres conocer la verdad, tienes que estar preparado para que quizá no te guste.";
			link.l1.go = "WildRose_Mary_266";
		break;

		case "WildRose_Mary_266":
			dialog.text = "Tienes razón, "+pchar.name+", sí... Quedémonos aquí un poco más. No quiero volver al barco ahora. Solo quiero... quedarme aquí, en silencio.";
			link.l1 = "Por supuesto, querida. Yo mismo quería proponértelo.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_38");
		break;
		
		// Тичингиту
		case "WildRose_Tichingitu_Final_1":  
			dialog.text = npchar.name+", llegar a tiempo, capitán "+pchar.name+".";
			link.l1 = "Sabía que podía contar contigo, amigo mío. Gracias a ti — nadie lo habría hecho mejor.";
			link.l1.go = "WildRose_Tichingitu_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Tichingitu_Final_2":
			dialog.text = "Selva es el hogar de "+npchar.name+". "+npchar.name+" feliz de luchar en la selva. La selva da fuerza a "+npchar.name+".";
			link.l1 = "Por eso te envié al frente del pelotón. Y no fue en vano — como ves, nos esperaban con los brazos abiertos.";
			link.l1.go = "WildRose_Tichingitu_Final_3";
		break;

		case "WildRose_Tichingitu_Final_3":
			dialog.text = "¿Qué planea hacer el capitán "+pchar.name+" ahora?";
			link.l1 = "Mary y yo necesitamos un momento a solas. Reúne a todos los heridos y llévalos al barco; también traigan a los muertos — los enterramos en el mar. Y, "+npchar.name+"... dile a Alonso que el padre de Mary debe ser enterrado conforme al rito protestante, aquí, en la selva, lejos de ojos curiosos. Que sólo él y tú sepan dónde será el entierro. No hablar de ese lugar con nadie, ni siquiera con Mary. No necesita atormentarse con recuerdos.";
			link.l1.go = "WildRose_Tichingitu_Final_4";
		break;

		case "WildRose_Tichingitu_Final_4":
			dialog.text = npchar.name+" entender, capitán "+pchar.name+". Tichingitu hará todo.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Дюран
		case "WildRose_Duran_Final_1":   
			dialog.text = "Mierdas duras... Pero los engañamos, ja-ja. Que se pudran aquí y piensen si valió la pena meterse con nosotros.";
			link.l1 = "Gracias, "+npchar.name+", buen trabajo. Da miedo pensar qué habría pasado con Mary... y conmigo... si no te hubiera enviado a cubrir la retaguardia...";
			link.l1.go = "WildRose_Duran_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Duran_Final_2":
			dialog.text = "Ja, capitán, tú te las habrías arreglado, ya te conozco. ¿Viste el machete que llevaba su jefe? No le quité el ojo. Si no te gusta — no me ofenderé si me lo regalas.";
			link.l1 = "Hm... Veremos, amigo, veremos. Por ahora reúne a los que sobrevivieron y llévalos al barco. También traigan a los fallecidos — los entregaremos al mar. Y una cosa más... ese líder era el padre de Mary. Lleva a Alonso y entiérralo según el rito protestante, por aquí. Que nadie sepa dónde está la tumba. Especialmente Mary. No quiero que ella se torture con recuerdos.";
			link.l1.go = "WildRose_Duran_Final_3";
		break;

		case "WildRose_Duran_Final_3":
			dialog.text = "Se hará, capitán. Espera... Bueno... me voy.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;

		// Тонзаг
		case "WildRose_Tonzag_Final_1": 
			dialog.text = "Hace calor por aquí, capitán. Los bastardos recibieron lo que merecían. ¿Viste cómo se deformó la cara de ese enano cuando aparecimos?";
			link.l1 = "Ese giro de los acontecimientos claramente no lo esperaba. Ni Mary ni yo anticipamos lo miserable que resultaría ser. Pero mi instinto no me falló cuando decidí cubrir la retaguardia.";
			link.l1.go = "WildRose_Tonzag_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Tonzag_Final_2":
			dialog.text = "Llevas tiempo en el Caribe, no eres novato. Ya estás acostumbrado a la escoria que habita aquí y sientes el truco antes de que pase. ¿Qué ordenas ahora? ¿Volvemos al barco?";
			link.l1 = "Recoge a los heridos, los muertos también, y subid al barco. A los que cayeron los entregaremos al mar, como verdaderos hijos suyos. Mary y yo iremos después — necesitamos estar a solas. Y una cosa más: entierra al padre de Mary según el rito protestante. Puedes tomar a Alonso para ayudarte. Pero asegúrate de que nadie sepa dónde estará la tumba. Especialmente Mary. No quiero que se atormente con recuerdos.";
			link.l1.go = "WildRose_Tonzag_Final_3";
		break;

		case "WildRose_Tonzag_Final_3":
			dialog.text = "Tienes razón. No hace falta que venga aquí a llorar. No te preocupes, haremos todo correctamente — y ni un alma viviente lo sabrá.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
		
		// Айронс
		case "WildRose_Irons_Final_1":
			dialog.text = "Capitán‑señor, permiso para informar: la emboscada funcionó, los canallas fueron exterminados, el capitán está a salvo.";
			link.l1 = "No es momento de bromear, ¿eh? Mala idea eso. ¿Quieres fregar la cubierta frente a la tripulación? Oh, se divertirían muchísimo... No te recomiendo que pongas a prueba mi paciencia otra vez. Especialmente hoy.";
			link.l1.go = "WildRose_Irons_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Irons_Final_2":
			dialog.text = "Eh... en realidad soy un oficial, y...";
			link.l1 = "De momento. Hoy oficial — mañana marino, pasado mañana mendigo.";
			link.l1.go = "WildRose_Irons_Final_3";
		break;

		case "WildRose_Irons_Final_3":
			dialog.text = "Entendido: " + GetFullName(pchar) + " — capitán de verdad. Basta de bromas. ¿Órdenes, señor?";
			link.l1 = "Reúne a los heridos y llévalos al barco. Dile a Alonso que tome un equipo y recoja los cuerpos de nuestros hombres — los entregaremos al mar. También que entierre al padre de Mary según las tradiciones protestantes. Sólo él y quien le ayude deben saber dónde estará la tumba. Mary no debe enterarse. No quiero que se atormente con recuerdos.";
			link.l1.go = "WildRose_Irons_Final_4";
		break;

		case "WildRose_Irons_Final_4":
			dialog.text = "Muy bien... Se hará. Y no te preocupes, sé cuándo mantener la boca cerrada.";
			link.l1 = "...";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;

		// Лонгвэй
		case "WildRose_Longway_Final_1":
			dialog.text = "Señor capitán, hemos ganado. Ni un perro logró escapar.";
			link.l1 = "Buen trabajo, " + npchar.name + ", gracias. Sabía que podía contar contigo. Lleva a todos los sobrevivientes al barco. Mary y yo nos quedaremos un rato en la costa.";
			link.l1.go = "WildRose_Longway_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Longway_Final_2":
			dialog.text = "¿Qué hacemos con los cuerpos de los caídos?";
			link.l1 = "Los entregaremos al mar. Dile a Alonso que se encargue de prepararlos para el entierro. Y una cosa más: dile que entierre al padre de Mary según las tradiciones protestantes, aquí en la selva, lejos de miradas curiosas. Nadie debe saber dónde está la tumba — especialmente Mary. Conociéndola, querrá volver aquí, y eso no le hará ningún bien.";
			link.l1.go = "WildRose_Longway_Final_3";
		break;

		case "WildRose_Longway_Final_3":
			dialog.text = "Lo transmitiré todo. ¿Alguna otra orden?";
			link.l1 = "Eso es todo, amigo. Vete, descansa y cura tus heridas.";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;

		// Алонсо
		case "WildRose_Alonso_Final_1":
			dialog.text = "Qué carnicería... ¿Estás bien, capitán?";
			link.l1 = "Estoy bien, salvo por el hecho de que Mary y yo tuvimos que matar a su padre...";
			link.l1.go = "WildRose_Alonso_Final_2";
			DelLandQuestMark(npchar);
		break;

		case "WildRose_Alonso_Final_2":
			dialog.text = "Parece que el bastardo era realmente despreciable...";
			link.l1 = "Tienes razón, " + npchar.name + ". Tienes razón. Pero sea como sea, debemos enterrarlo como corresponde — según el rito protestante. Encárgate tú mismo. Nadie debe saber dónde estará esa tumba. Especialmente Mary.";
			link.l1.go = "WildRose_Alonso_Final_3";
		break;

		case "WildRose_Alonso_Final_3":
			dialog.text = "¿Quieres protegerla de los malos recuerdos?";
			link.l1 = "Y de tormentos inútiles. A los demás, llévalos al barco para que se curen. Lleva también a los muertos — los enterraremos en el mar cuando Mary y yo regresemos. Ahora necesitamos estar solos.";
			link.l1.go = "WildRose_Alonso_Final_4";
		break;

		case "WildRose_Alonso_Final_4":
			dialog.text = "Les diré a los chicos que no los busquen.";
			link.l1 = "Gracias, " + npchar.name + ".";
			link.l1.go = "exit";
			AddDialogExitQuestFunction("WildRose_Etap6_LifeAfterDeath_31");
		break;
	}
} 
